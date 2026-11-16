#include "crown/io/ingest.hpp"
#include "crown/io/input_options.hpp"
#include "native_input.hpp"
#include "checkpoint_detail.hpp"
#include "input_native.hpp"
#include "catalog_source.hpp"
#include "ingest_text.hpp"
#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include <algorithm>
#include <charconv>
#include <limits>
#include <type_traits>

namespace crown::io {
namespace {
void require(bool ok,std::string_view code,std::string_view message) {
  if(!ok)throw Error(std::string(code),std::string(message));
}
void bounded(std::size_t size,std::size_t limit,std::string_view message) {require(size<=limit,"resource_limit",message);}
std::size_t sum(std::size_t a,std::size_t b) {
  require(b<=std::numeric_limits<std::size_t>::max()-a,"resource_limit","input size accounting exhausted");return a+b;
}
[[noreturn]] void invalid_document(const char* message) {throw Error("invalid_document",message);}
[[noreturn]] void resource_limit(const char* message) {throw Error("resource_limit",message);}
[[noreturn]] void invalid_scalar(const char* message) {throw Error("invalid_scalar",message);}
void source_name(std::string_view name,const InputLimits& limits) {
  bounded(name.size(),limits.source_bytes,"input source identifier exceeds its byte limit");
  require(!name.empty() && name.find('\0')==std::string_view::npos,"invalid_source_position","source identifier must be nonempty and contain no NUL");
  ingest_detail::require_utf8(name);
}
const auto& table_at(const auto& catalog,TableId id) {
  require(id.value<catalog.tables.size(),"unknown_table","physical input table ID is outside the catalog");return catalog.tables[id.value];
}
using ingest_detail::require_utf8;
std::int64_t parse_int64(std::string_view text) {
  if (text.empty()) invalid_scalar("int64 must contain an optional sign and digits");

  std::size_t position = 0;
  bool negative = false;
  if (text[position] == '+' || text[position] == '-') {
    negative = text[position] == '-';
    ++position;
  }
  if (position == text.size()) invalid_scalar("int64 sign must be followed by digits");

  constexpr auto positive_limit = static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max());
  constexpr auto negative_limit = positive_limit + 1U;
  const auto limit = negative ? negative_limit : positive_limit;
  std::uint64_t magnitude = 0;
  for (; position < text.size(); ++position) {
    const char character = text[position];
    if (character < '0' || character > '9') {
      invalid_scalar("int64 admits only an optional ASCII sign and digits");
    }
    const auto digit = static_cast<std::uint64_t>(character - '0');
    if (magnitude > (limit - digit) / 10U) {
      throw Error("scalar_overflow", "int64 value is outside the signed 64-bit range");
    }
    magnitude = magnitude * 10U + digit;
  }

  if (!negative) return static_cast<std::int64_t>(magnitude);
  if (magnitude == negative_limit) return std::numeric_limits<std::int64_t>::min();
  return -static_cast<std::int64_t>(magnitude);
}

template<class Read>
std::optional<input_detail::Vector<resource::AccountedText>> read_delimited_native(const resource::MemoryAccount& account,
    const Read& read, char delimiter, const InputLimits& limits) {
  if (delimiter == '"' || delimiter == '\r' || delimiter == '\n' || delimiter == '\0') {
    throw Error("invalid_input_options", "delimited input separator cannot be quote, CR, LF, or NUL");
  }

  enum class FieldState { start, unquoted, quoted, after_quote };
  FieldState state = FieldState::start;
  input_detail::Vector<resource::AccountedText> fields(input_detail::allocator<resource::AccountedText>(account));
  input_detail::Buffer field(account);
  std::size_t record_bytes = 0;
  bool saw_record_byte = false;

  const auto next_byte = [&]() -> std::optional<char> {
    const auto value = read();
    if (!value) return std::nullopt;
    if (record_bytes >= limits.record_bytes) {
      resource_limit("delimited record exceeds configured byte limit");
    }
    ++record_bytes;
    saw_record_byte = true;
    return value;
  };

  const auto append_field_byte = [&](char value) {
    if (field.size() >= limits.field_bytes) {
      resource_limit("decoded delimited field exceeds configured byte limit");
    }
    field.push_back(value);
  };

  const auto finish_field = [&]() {
    if (fields.size() >= limits.columns) {
      resource_limit("delimited record exceeds configured column limit");
    }
    ingest_detail::require_utf8(field.view());
    fields.push_back(resource::AccountedText::copy_of(account,field.view(),input_detail::memory_owner));
    field.clear();
  };

  const auto finish_record = [&]() -> std::optional<input_detail::Vector<resource::AccountedText>> {
    finish_field();
    return std::optional<input_detail::Vector<resource::AccountedText>>(std::move(fields));
  };

  for (;;) {
    const auto byte = next_byte();
    if (!byte) {
      if (!saw_record_byte) return std::nullopt;
      if (state == FieldState::quoted) invalid_document("unterminated quoted delimited field");
      return finish_record();
    }

    const char value = *byte;
    if (state == FieldState::quoted) {
      if (value == '"') {
        state = FieldState::after_quote;
      } else {
        append_field_byte(value);
      }
      continue;
    }

    if (state == FieldState::after_quote) {
      if (value == '"') {
        append_field_byte('"');
        state = FieldState::quoted;
        continue;
      }
      if (value == delimiter) {
        finish_field();
        state = FieldState::start;
        continue;
      }
      if (value == '\n') return finish_record();
      if (value == '\r') {
        const auto lf = next_byte();
        if (!lf || *lf != '\n') invalid_document("bare CR outside a quoted delimited field");
        return finish_record();
      }
      invalid_document("unexpected byte after closing delimited quote");
    }

    if (value == '\n') return finish_record();
    if (value == '\r') {
      const auto lf = next_byte();
      if (!lf || *lf != '\n') invalid_document("bare CR outside a quoted delimited field");
      return finish_record();
    }
    if (value == delimiter) {
      finish_field();
      state = FieldState::start;
      continue;
    }
    if (value == '"') {
      if (state != FieldState::start) invalid_document("quote inside an unquoted delimited field");
      state = FieldState::quoted;
      continue;
    }

    append_field_byte(value);
    state = FieldState::unquoted;
  }
}

 storage::ScalarView read_native_cell(std::string_view text,const auto& column,const InputLimits& limits) {
  bounded(text.size(),limits.field_bytes,"decoded text cell exceeds configured byte limit");require_utf8(text);
  switch(column.type) {
    case ScalarType::int64:return parse_int64(text);
    case ScalarType::string:return text;
    case ScalarType::boolean:
      if(text=="true")return true;
      if(text=="false")return false;
      invalid_scalar("boolean text must be exactly true or false");
    case ScalarType::date:return Date::parse(text);
    case ScalarType::decimal: {
      const auto value=storage::InlineDecimal::parse(text);
      if(column.decimal) {
        const auto parts=value.parts();const auto spec=*column.decimal;
        const auto integer_digits=parts.digits=="0" || parts.digits.size()<=parts.scale?std::size_t{0}:parts.digits.size()-parts.scale;
        require(parts.scale<=spec.scale && integer_digits+spec.scale<=spec.precision,"scalar_overflow","decimal value does not fit its declared precision and scale");
      }
      return value;
    }
  }
  throw Error("unsupported_type","unsupported text cell scalar type");
}
} // namespace
// Accepted progress is separate from decoded bytes/records and cached input.
// Moving the facade preserves this heap-stable state and its options reference.
struct EventReader::Data {
  resource::MemoryAccount account;
  std::istream* input;
  CatalogSource catalog;
  AccountedInputOptions retained_options;
  const AccountedInputOptions::Values& options;
  AccountedInputProgress progress;
  resource::AccountedText fingerprint;
  std::optional<input_detail::Decoded> cached;
  InputPositions::Prepared prepared_position;
  input_detail::Vector<std::size_t> fields;
  std::uint64_t bytes=0,records=0;
  bool broken=false,ended=false,header_read=false;
  template<class Progress> Data(const resource::MemoryAccount& memory,std::istream& stream,CatalogSource schema,
      const AccountedInputOptions& config,const Progress& initial,bool admitted)
      :account(memory),input(&stream),catalog(std::move(schema)),retained_options(config),options(retained_options.get()),
       progress(account,initial),fingerprint(input_detail::catalog_fingerprint(account,catalog,admitted)),fields(input_detail::allocator<std::size_t>(account)) {
    catalog_source_detail::read(catalog,[&](const auto& schema_view){initialize(schema_view,options,progress);});
  }
  static void initialize(const auto& catalog,const AccountedInputOptions::Values& options,const AccountedInputProgress& progress) {
    const auto format=options.format;
    require(format==InputFormat::jsonl || format==InputFormat::binary || format==InputFormat::csv ||
        format==InputFormat::legacy_signed || format==InputFormat::legacy_relations || format==InputFormat::legacy_insert_only ||
        format==InputFormat::legacy_flags || format==InputFormat::legacy_timestamp_flags,"invalid_input_options","unknown physical input format");
    if (format==InputFormat::jsonl || format==InputFormat::binary) {
      require(!options.table && options.relation_tokens.empty() && !options.source && !options.null_token &&
          options.byte_offset==0 && options.delimiter==',' && options.header,
          "invalid_input_options","wire records carry their own table/position; text-profile options do not apply");
    } else {
      require(format==InputFormat::legacy_relations || options.relation_tokens.empty(),
          "invalid_input_options","relation token mapping applies only to the legacy_relations profile");
      require(format==InputFormat::csv || options.header,
          "invalid_input_options","header option applies only to CSV; legacy profiles are always headerless");
    }
    bounded(progress.source_positions.size(),options.limits.sources,"retained source-position limit exceeded");
    for (const auto& [name,offset] : progress.source_positions) { static_cast<void>(offset); source_name(name,options.limits); }
    if (options.source) source_name(*options.source,options.limits);
    if (options.null_token) { bounded(options.null_token->size(),options.limits.field_bytes,"null spelling exceeds field limit"); require_utf8(*options.null_token); }
    if (format==InputFormat::legacy_timestamp_flags) {
      require(options.source.has_value(),"invalid_input_options","timestamp/flag traces require an explicit source ID to retain their position");
      require(options.byte_offset==0,"invalid_input_options","timestamp positions are retained verbatim; byte_offset does not apply");
    }
    if (format==InputFormat::csv || format==InputFormat::legacy_signed || format==InputFormat::legacy_insert_only ||
        format==InputFormat::legacy_flags || format==InputFormat::legacy_timestamp_flags) {
      require(options.table.has_value(),"invalid_input_options","this input profile needs an explicit physical table");
      bounded(table_at(catalog,*options.table).columns.size(),options.limits.columns,"table arity exceeds input column limit");
    }
    if (format==InputFormat::legacy_relations) {
      require(!options.table && !options.relation_tokens.empty(),"invalid_input_options","relation traces require an explicit token-to-table mapping");
      for (const auto& [name,id] : options.relation_tokens) {
        require(!name.empty(),"invalid_input_options","legacy relation token must not be empty"); require_utf8(name);
        bounded(name.size(),options.limits.field_bytes,"legacy relation token exceeds field limit");
        bounded(table_at(catalog,id).columns.size(),options.limits.columns,"table arity exceeds input column limit");
      }
    }
    if (format!=InputFormat::jsonl && format!=InputFormat::binary) {
      require(static_cast<unsigned char>(options.delimiter)<128 && options.delimiter!='\0' && options.delimiter!='\r' && options.delimiter!='\n' && options.delimiter!='"',
          "invalid_input_options","invalid delimited input separator");
    }
    require(options.csv_operation==SetOperation::insert || options.csv_operation==SetOperation::erase,
        "invalid_input_options","unknown CSV set operation");
    require(format==InputFormat::csv || options.csv_operation==SetOperation::insert,
        "invalid_input_options","csv_operation applies only to the CSV profile");
  }
  std::optional<char> byte() {
    std::istream::int_type next;
    // Throwing streams can signal clean EOF; real I/O errors retain their category.
    try { next=input->peek(); }
    catch (const std::ios_base::failure&) {
      if (input->eof() && !input->bad()) return {};
      throw Error("input_io_error","input stream read failed");
    }
    if (std::istream::traits_type::eq_int_type(next,std::istream::traits_type::eof())) {
      require(input->eof() && !input->bad(),"input_io_error","input stream failed before clean EOF"); return {};
    }
    require(bytes!=std::numeric_limits<std::uint64_t>::max() &&
        (!options.limits.total_bytes || bytes<*options.limits.total_bytes),"resource_limit","input total byte limit exceeded");
    char value=0;
    try { input->get(value); }
    catch (const std::ios_base::failure&) { throw Error("input_io_error","input stream read failed"); }
    require(bool(*input),"input_io_error","input stream read failed"); ++bytes; return value;
  }
  std::optional<input_detail::Buffer> line() {
    input_detail::Buffer value(account); bool any=false,cr=false;
    const auto append=[&](char item) {
      bounded(sum(value.size(),1),options.limits.record_bytes,"JSONL input record exceeds its byte limit"); value.push_back(item);
    };
    while (auto next=byte()) {
      any=true;
      // A single LF or CRLF frames the JSON object and is not part of its
      // encoded-record budget. Hold one CR without growing the body buffer.
      if (*next=='\n') return value;
      if (cr) append('\r');
      cr=*next=='\r';
      if (!cr) append(*next);
    }
    if (cr) append('\r');
    return any?std::optional<input_detail::Buffer>{std::move(value)}:std::nullopt;
  }
  std::optional<input_detail::Buffer> frame() {
    const auto first=byte();if(!first)return {};
    constexpr std::size_t header_size=14;
    bounded(header_size,options.limits.record_bytes,"binary header exceeds record limit");
    input_detail::Buffer data(account);data.push_back(*first);
    while(data.size()<header_size) {
      const auto next=byte();require(next.has_value(),"invalid_document","truncated binary frame header");data.push_back(*next);
    }
    const auto header=data.view();require(header.substr(0,8)=="CROWNUPD","invalid_document","invalid binary input magic");
    const auto integer=[&](std::size_t start,std::size_t length) {
      std::uint64_t value=0;for(std::size_t i=0;i<length;++i)value|=static_cast<std::uint64_t>(static_cast<unsigned char>(header[start+i]))<<(i*8U);return value;
    };
    require(integer(8,2)==1,"unsupported_version","unsupported binary input schema version");const auto length=integer(10,4);
    require(length<=options.limits.record_bytes-header_size,"resource_limit","binary payload exceeds record limit");
    // All header-view reads finish before reserve can relocate its bytes.
    const auto size=header_size+static_cast<std::size_t>(length);data.reserve(size);
    while(data.size()<size) {
      const auto next=byte();require(next.has_value(),"invalid_document","truncated binary frame payload");data.push_back(*next);
    }
    return data;
  }
  std::uint64_t offset() const {
    require(bytes<=std::numeric_limits<std::uint64_t>::max()-options.byte_offset,"resource_limit","input byte offset exhausted");
    return options.byte_offset+bytes;
  }
  std::uint64_t next_sequence() const {
    require(progress.sequence!=std::numeric_limits<std::uint64_t>::max(),"sequence_overflow","physical input sequence exhausted");
    return progress.sequence+1;
  }
  std::optional<input_detail::Decoded> delimited(const auto& catalog) {
    for (;;) {
      const auto beginning=offset();
      auto limits=options.limits;
      limits.columns=sum(limits.columns,options.format==InputFormat::legacy_relations || options.format==InputFormat::legacy_timestamp_flags?2:1);
      const auto record=read_delimited_native(account,[this] { return byte(); },options.delimiter,limits);
      if (!record) return {};
      const auto format=options.format; TableId table=options.table.value_or(TableId{0});
      std::size_t start=0; SetOperation operation=options.csv_operation;
      std::optional<std::uint64_t> timestamp;
      if (format!=InputFormat::csv && !record->empty() && (*record)[0]=="*")
        throw Error("unsupported_input_control","legacy enumeration markers are control records, not physical updates");
      if (format==InputFormat::csv && options.header && !header_read) {
        const auto& columns=table_at(catalog,table).columns;
        const bool nullary=columns.empty() && record->size()==1 && (*record)[0].empty();
        require(nullary || record->size()==columns.size(),"invalid_document","CSV header must name every physical source column");
        // Explicit one-time header mapping scans names per column (O(C^2)).
        fields.reserve(columns.size());
        for (const auto& column : columns) {
          const auto found=std::find(record->begin(),record->end(),std::string_view(column.name));
          require(found!=record->end() && std::count(record->begin(),record->end(),std::string_view(column.name))==1,
              "invalid_document","CSV header has missing or duplicate physical column names");
          fields.push_back(static_cast<std::size_t>(found-record->begin()));
        }
        header_read=true; continue;
      }
      if (format==InputFormat::legacy_signed || format==InputFormat::legacy_relations || format==InputFormat::legacy_flags ||
          format==InputFormat::legacy_timestamp_flags) {
        require(!record->empty(),"invalid_document","empty legacy input record");
        if (format==InputFormat::legacy_timestamp_flags) {
          require(record->size()>=2,"invalid_document","timestamp/flag record is incomplete");
          const auto text=(*record)[0].view(); std::uint64_t value=0;
          const auto parsed=std::from_chars(text.data(),text.data()+text.size(),value);
          require(!text.empty() && parsed.ec==std::errc{} && parsed.ptr==text.data()+text.size(),
              "invalid_source_position","legacy timestamp must be an unsigned 64-bit integer");
          timestamp=value;
        }
        const auto& sign=(*record)[timestamp?1:0];
        if (format==InputFormat::legacy_flags || format==InputFormat::legacy_timestamp_flags) {
          require(sign=="0" || sign=="1","unsupported_input_operation","legacy flag must be 0 (delete) or 1 (insert)"); operation=sign=="1"?SetOperation::insert:SetOperation::erase;
        } else {
          require(sign=="+" || sign=="-","unsupported_input_operation","legacy operation must be + or -"); operation=sign=="+"?SetOperation::insert:SetOperation::erase;
        }
        start=timestamp?2:1;
        if (format==InputFormat::legacy_relations) {
          require(record->size()>=2,"invalid_document","legacy record has no physical relation token");
          const auto found=options.relation_tokens.find((*record)[1].view());
          require(found!=options.relation_tokens.end(),"unknown_table","unmapped legacy physical relation token"); table=found->second; start=2;
        }
      }
      const auto& columns=table_at(catalog,table).columns;
      const bool nullary=format==InputFormat::csv && columns.empty() && record->size()==1 && (*record)[0].empty();
      require(nullary || record->size()-start==columns.size(),"invalid_document","delimited input must contain the complete physical source row");
      input_detail::Vector<storage::ScalarView> values(input_detail::allocator<storage::ScalarView>(account));values.reserve(columns.size());
      for (std::size_t i=0;i<columns.size();++i) {
        const auto& value=(*record)[format==InputFormat::csv && options.header?fields[i]:start+i];
        require(!options.null_token || value.view()!=options.null_token->view(),"unsupported_input_null","configured upstream NULL marker is unsupported by the nonnull engine");
        values.push_back(read_native_cell(value.view(),columns[i],options.limits));
      }
      input_detail::Decoded decoded;
      decoded.row=storage::AccountedRow::copy_of(account,storage::RowView::borrow(values),input_detail::memory_owner);
      decoded.event.update={next_sequence(),table,operation,storage::TupleValuesView::borrow(decoded.row.view())};
      if(options.source) {
        decoded.source=resource::AccountedText::copy_of(account,options.source->view(),input_detail::memory_owner);
        decoded.event.source_position=SourcePositionView{decoded.source.view(),timestamp.value_or(beginning)};
      }
      input_detail::validate(decoded.event,catalog,options.limits,input_detail::row_issue(catalog,table,decoded.event.update.values));return decoded;
    }
  }
  // Prepare a new source node before engine work; accepted offsets stay unchanged
  // until acknowledge links that node or publishes an existing scalar offset.
  void order(const InputEventView& event) {
    require(event.update.sequence==next_sequence(),"invalid_sequence","physical input sequence must be contiguous after the last accepted input");
    if(!event.source_position)return;
    const auto& position=*event.source_position;
    const auto found=progress.source_positions.find(position.source);
    if(found!=progress.source_positions.end())require(position.offset>found->second,"invalid_source_position","source offsets must increase strictly for each source");
    else bounded(sum(progress.source_positions.size(),1),options.limits.sources,"retained source-position limit exceeded");
    prepared_position=progress.source_positions.prepare(position.source,position.offset);
  }
};
EventReader::EventReader(std::istream& input,CatalogSource catalog,InputOptions options,InputProgress progress)
    :EventReader(resource::MemoryAccount::create(std::numeric_limits<std::uint64_t>::max()),input,std::move(catalog),std::move(options),std::move(progress),false) {}
EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,InputOptions options,InputProgress progress,bool admitted)
    :EventReader(account,input,std::move(catalog),AccountedInputOptions(account,options),std::move(progress),admitted) {}
EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,const AccountedInputOptions& options,InputProgress progress,bool admitted)
    :data_(resource::make_accounted_unique<Data>(input_detail::memory_owner,account,resource::MemoryPurpose::support_metadata,
        account,input,std::move(catalog),options,progress,admitted)) {}
EventReader::~EventReader()=default;
void EventReader::validate_options(const CatalogSource& catalog,const AccountedInputOptions& options,const AccountedInputProgress& progress) {
  catalog_source_detail::read(catalog,[&](const auto& schema){Data::initialize(schema,options.get(),progress);});
}
EventReader::EventReader(const resource::MemoryAccount& account,std::istream& input,CatalogSource catalog,
    const ReaderCheckpoint& state,const SourceStateLimits& limits,bool admitted)
    :data_([&] {
      checkpoint_detail::Budget budget{limits};budget.positions(state.progress,state.options.get().limits);budget.options(state.options.get());
      checkpoint_detail::require(state.csv_fields.size()<=budget.limits.csv_fields,recovery::ImageFault::limit);
      budget.charge(state.csv_fields.size());
      const auto options=AccountedInputOptions(account,state.options);
      auto result=resource::make_accounted_unique<Data>(input_detail::memory_owner,account,resource::MemoryPurpose::support_metadata,
          account,input,std::move(catalog),options,state.progress,admitted);
      checkpoint_detail::require(checkpoint_detail::hash(result->fingerprint.view())==state.catalog_sha256,recovery::ImageFault::binding);
      checkpoint_detail::require(!result->options.limits.total_bytes || state.bytes<=*result->options.limits.total_bytes);
      checkpoint_detail::require(!result->options.limits.records || state.records<=*result->options.limits.records);
      if(result->options.format==InputFormat::csv && result->options.header) {
        const auto columns=catalog_source_detail::read(result->catalog,[&](const auto& schema){return table_at(schema,*result->options.table).columns.size();});
        checkpoint_detail::require(!state.records || state.header_read);
        checkpoint_detail::require(state.csv_fields.size()==(state.header_read?columns:0));
        for(std::size_t i=0;i<state.csv_fields.size();++i) {
          checkpoint_detail::require(state.csv_fields[i]<columns);
          for(std::size_t j=0;j<i;++j){budget.charge(1);checkpoint_detail::require(state.csv_fields[i]!=state.csv_fields[j]);}
        }
      }else checkpoint_detail::require(!state.header_read && state.csv_fields.empty());
      result->fields.assign(state.csv_fields.begin(),state.csv_fields.end());
      result->bytes=state.bytes;result->records=state.records;result->header_read=state.header_read;result->ended=state.ended;
      return result;
    }()) {}
ReaderCheckpoint EventReader::checkpoint_state() const {return checkpoint_state(SourceStateLimits{});}
ReaderCheckpoint EventReader::checkpoint_state(const SourceStateLimits& limits) const {
  checkpoint_detail::require(bool(data_));const auto& d=*data_;
  checkpoint_detail::require(!d.cached && !d.broken);
  checkpoint_detail::Budget budget{limits};budget.positions(d.progress,d.options.limits);budget.options(d.options);
  checkpoint_detail::require(d.fields.size()<=limits.csv_fields,recovery::ImageFault::limit);budget.charge(d.fields.size());
  ReaderCheckpoint result{d.retained_options,AccountedInputProgress(d.account,d.progress),
      recovery::ImageVector<std::size_t>(recovery::image_allocator<std::size_t>(d.account)),d.bytes,d.records,d.header_read,d.ended,
      checkpoint_detail::hash(d.fingerprint.view()),budget.used};
  result.csv_fields.assign(d.fields.begin(),d.fields.end());return result;
}
EventReader::EventReader(EventReader&&) noexcept=default;
EventReader& EventReader::operator=(EventReader&&) noexcept=default;
const InputEventView* EventReader::peek() {
  require(bool(data_),"invalid_input_reader","moved-from physical input reader");auto& d=*data_;
  require(!d.broken,"input_failed","physical input reader failed; recreate it explicitly to retry corrected input");
  if(d.cached)return &d.cached->event;
  if(d.ended)return nullptr;
  // Failure during peek preparation may follow byte consumption. Only a complete
  // cached event is retryable after engine rejection; latch every preparation error.
  try {
    std::optional<input_detail::Decoded> event;
    if(d.options.format==InputFormat::jsonl) {
      auto text=d.line();if(text)event=input_detail::decode_json(d.account,text->view(),d.catalog,d.options.limits,d.fingerprint.view());
    }else if(d.options.format==InputFormat::binary) {
      auto text=d.frame();if(text)event=input_detail::decode_binary(d.account,text->view(),d.catalog,d.options.limits,d.fingerprint.view());
    }else event=catalog_source_detail::read(d.catalog,[&](const auto& schema){return d.delimited(schema);});
    if(!event){d.ended=true;return nullptr;}
    require(d.records!=std::numeric_limits<std::uint64_t>::max() && (!d.options.limits.records || d.records<*d.options.limits.records),
        "resource_limit","physical input record limit exceeded");
    d.order(event->event);d.cached.emplace(std::move(*event));++d.records;return &d.cached->event;
  }catch(...){d.broken=true;throw;}
}
// No input read or allocation: publish only the already prepared acceptance.
// Releasing cached payload still has its ordinary account/cleanup cost.
void EventReader::acknowledge() noexcept {
  if(!data_ || !data_->cached)return;
  auto& d=*data_;
  if(d.cached->event.source_position)d.progress.source_positions.publish(d.prepared_position);
  d.progress.sequence=d.cached->event.update.sequence;d.cached.reset();d.prepared_position=InputPositions::Prepared{};
}
std::uint64_t EventReader::stage_replay(const InputEventView& event,ReaderPositionView position,const SourceStateLimits& limits) {
  using checkpoint_detail::require;
  require(bool(data_));auto& d=*data_;require(!d.cached && !d.broken && !d.ended);
  checkpoint_detail::Budget budget{limits};checkpoint_detail::replay_input(budget,InputItemView{event},d.options.limits,d.progress.source_positions);
  std::uint64_t minimum_header=0,maximum_header=0;
  require(d.records<UINT64_MAX && position.records==d.records+1 && event.update.sequence==position.records);
  require(position.bytes>d.bytes && (!d.options.limits.total_bytes || position.bytes<=*d.options.limits.total_bytes));
  require(!d.options.limits.records || position.records<=*d.options.limits.records);
  require(position.csv_fields.size()<=limits.csv_fields,recovery::ImageFault::limit);budget.charge(position.csv_fields.size());
  catalog_source_detail::read(d.catalog,[&](const auto& schema) {
    input_detail::validate(event,schema,d.options.limits,input_detail::row_issue(schema,event.update.table,event.update.values));
    if(d.options.format==InputFormat::csv && d.options.header) {
      const auto columns=table_at(schema,*d.options.table).columns.size();require(position.header_read && position.csv_fields.size()==columns);
      for(std::size_t i=0;i<columns;++i){require(position.csv_fields[i]<columns);for(std::size_t j=0;j<i;++j){budget.charge(1);require(position.csv_fields[i]!=position.csv_fields[j]);}}
      if(d.header_read){budget.charge(columns);require(std::equal(d.fields.begin(),d.fields.end(),position.csv_fields.begin(),position.csv_fields.end()),recovery::ImageFault::binding);}
      else {
        minimum_header=std::max<std::uint64_t>(1,columns); // delimiters plus mandatory header terminator
        std::uint64_t optional_quotes=columns==0?1:0;
        for(const auto& column:table_at(schema,*d.options.table).columns) {
          const std::string_view name=column.name;budget.charge(name.size());budget.charge(name.size());require(name.size()<=UINT64_MAX-minimum_header);minimum_header+=name.size();
          if(name.find_first_of(std::string_view{"\r\n\""})!=std::string_view::npos || name.find(d.options.delimiter)!=std::string_view::npos) {
            budget.charge(name.size());const auto quotes=static_cast<std::uint64_t>(std::count(name.begin(),name.end(),'"'));require(quotes<=UINT64_MAX-2 && quotes+2<=UINT64_MAX-minimum_header);minimum_header+=quotes+2;
          }else ++optional_quotes;
        }
        require(minimum_header<UINT64_MAX && optional_quotes<=(UINT64_MAX-minimum_header-1)/2);maximum_header=std::min<std::uint64_t>(d.options.limits.record_bytes,minimum_header+2*optional_quotes+1);
        require(minimum_header<=d.options.limits.record_bytes && minimum_header<position.bytes-d.bytes);
      }
    }else require(!position.header_read && position.csv_fields.empty());
  });
  const auto format=d.options.format;
  if(format!=InputFormat::jsonl && format!=InputFormat::binary) {
    require(event.source_position.has_value()==d.options.source.has_value());
    if(d.options.source){require(event.source_position->source==*d.options.source,recovery::ImageFault::binding);
      if(format!=InputFormat::legacy_timestamp_flags){require(position.bytes<=UINT64_MAX-d.options.byte_offset);
        const auto origin=d.options.byte_offset+d.bytes;
        if(minimum_header==0)require(event.source_position->offset==origin,recovery::ImageFault::binding);
        else require(event.source_position->offset>=origin+minimum_header && event.source_position->offset-origin<=maximum_header && event.source_position->offset<d.options.byte_offset+position.bytes);
      }}
    if(d.options.table)require(event.update.table==*d.options.table,recovery::ImageFault::binding);
    else {budget.charge(d.options.relation_tokens.size());require(std::any_of(d.options.relation_tokens.begin(),d.options.relation_tokens.end(),[&](const auto& entry){return entry.second==event.update.table;}),recovery::ImageFault::binding);}
    if(format==InputFormat::csv)require(event.update.operation==d.options.csv_operation,recovery::ImageFault::binding);
    if(format==InputFormat::legacy_insert_only)require(event.update.operation==SetOperation::insert);
  }
  input_detail::Decoded owned;owned.row=storage::AccountedRow::copy_view(d.account,event.update.values,input_detail::memory_owner);
  if(event.source_position)owned.source=resource::AccountedText::copy_of(d.account,event.source_position->source,input_detail::memory_owner);
  owned.event=event;owned.event.update.values=storage::TupleValuesView::borrow(owned.row.view());
  if(owned.event.source_position)owned.event.source_position->source=owned.source.view();
  input_detail::Vector<std::size_t> fields(input_detail::allocator<std::size_t>(d.account));fields.assign(position.csv_fields.begin(),position.csv_fields.end());
  // order finishes throwing preparation; swaps/moves below publish owned
  // decoder state without reading the stream or acknowledging source progress.
  d.order(owned.event);d.fields.swap(fields);d.cached.emplace(std::move(owned));d.bytes=position.bytes;d.records=position.records;d.header_read=position.header_read;return budget.used;
}
ReaderPositionView EventReader::decoder_position() const & {
  require(bool(data_),"invalid_input_reader","moved-from physical input reader");const auto& d=*data_;
  return {d.bytes,d.records,d.header_read,d.fields};
}
bool EventReader::failed() const noexcept {return data_ && data_->broken;}
// Move accepted native ownership out; discard cached input without acceptance.
AccountedInputProgress EventReader::close() noexcept {
  static_assert(std::is_nothrow_move_constructible_v<AccountedInputProgress>);
  if(!data_)return {};
  auto result=std::move(data_->progress);data_.reset();return result;
}
const AccountedInputProgress& EventReader::progress() const {require(bool(data_),"invalid_input_reader","moved-from physical input reader");return data_->progress;}
const CatalogSource& EventReader::catalog() const {require(bool(data_),"invalid_input_reader","moved-from physical input reader");return data_->catalog;}
std::string_view EventReader::catalog_sha256() const {require(bool(data_),"invalid_input_reader","moved-from physical input reader");return data_->fingerprint.view();}
const resource::MemoryAccount& EventReader::account() const {require(bool(data_),"invalid_input_reader","moved-from physical input reader");return data_->account;}
const AccountedInputOptions& EventReader::native_options() const & {require(bool(data_),"invalid_input_reader","moved-from physical input reader");return data_->retained_options;}
std::uint64_t EventReader::bytes_read() const {require(bool(data_),"invalid_input_reader","moved-from physical input reader");return data_->bytes;}
std::uint64_t EventReader::records_read() const {require(bool(data_),"invalid_input_reader","moved-from physical input reader");return data_->records;}
} // namespace crown::io
