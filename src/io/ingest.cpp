#include "crown/io/ingest.hpp"

#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include "crown/io/catalog.hpp"
#include "crown/ir/digest.hpp"
#include "ingest_text.hpp"
#include "catalog_source.hpp"
#include "json.hpp"
#include "native_input.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <charconv>
#include <limits>
#include <type_traits>
#include <utility>

namespace crown::io {
namespace {
using ingest_detail::require_utf8;
constexpr std::string_view magic="CROWNUPD";
constexpr std::size_t frame_header=14;
static_assert(std::variant_size_v<Value> == 5 &&
    std::is_same_v<std::variant_alternative_t<0,Value>,std::int64_t> &&
    std::is_same_v<std::variant_alternative_t<1,Value>,std::string> &&
    std::is_same_v<std::variant_alternative_t<2,Value>,bool> &&
    std::is_same_v<std::variant_alternative_t<3,Value>,Date> &&
    std::is_same_v<std::variant_alternative_t<4,Value>,Decimal>,
    "physical wire v1 scalar tags require explicit review when Value changes");
void require(bool condition,std::string_view code,std::string_view message) {
  if (!condition) throw Error(std::string(code),std::string(message));
}
void bounded(std::size_t size,std::size_t limit,std::string_view description) {
  require(size<=limit,"resource_limit",description);
}
std::size_t sum(std::size_t left,std::size_t right) {
  require(right<=std::numeric_limits<std::size_t>::max()-left,"resource_limit","input size accounting exhausted");
  return left+right;
}
void source_name(std::string_view name,const InputLimits& limits) {
  bounded(name.size(),limits.source_bytes,"input source identifier exceeds its byte limit");
  require(!name.empty() && name.find('\0')==std::string_view::npos,"invalid_source_position","source identifier must be nonempty and contain no NUL");
  require_utf8(name);
}
const auto& table_at(const auto& catalog,TableId table) {
  require(table.value<catalog.tables.size(),"unknown_table","physical input table ID is outside the catalog");
  return catalog.tables[table.value];
}
void validate_event(const InputEvent& event,const auto& catalog,const InputLimits& limits) {
  const auto& table=table_at(catalog,event.update.table);
  require(event.update.sequence!=0,"invalid_sequence","input sequence must be positive");
  require(event.update.operation==SetOperation::insert || event.update.operation==SetOperation::erase,
      "unsupported_input_operation","physical input supports only insert and delete");
  bounded(event.update.values.size(),limits.columns,"physical input column limit exceeded");
  validate_row(catalog,event.update.table,event.update.values);
  std::size_t minimum_payload=0;
  for (const auto& value : event.update.values) {
    std::size_t bytes=1;  // A lower bound valid in every admitted encoding.
    if (const auto* text=std::get_if<std::string>(&value)) bytes=text->size();
    else if (const auto* date=std::get_if<Date>(&value)) bytes=date->to_string().size();
    else if (const auto* decimal=std::get_if<Decimal>(&value)) bytes=decimal->to_string().size();
    // Fixed scalar words are not string fields; zero field bytes still permits
    // int64/bool, while date/decimal need their encoded textual field budget.
    if (!std::holds_alternative<std::int64_t>(value) && !std::holds_alternative<bool>(value))
      bounded(bytes,limits.field_bytes,"physical input scalar field exceeds its byte limit");
    minimum_payload=sum(minimum_payload,bytes);
    bounded(minimum_payload,limits.record_bytes,"physical input payload exceeds its record byte limit");
    if (const auto* text=std::get_if<std::string>(&value)) require_utf8(*text);
  }
  bounded(table.name.size(),limits.field_bytes,"physical table name exceeds field byte limit");
  if (event.source_position) source_name(event.source_position->source,limits);
}
void check_binding(std::uint64_t catalog_version,std::uint64_t source_version,std::string_view fingerprint,
    TableId id,const auto& catalog,std::string_view expected) {
  require(catalog_version==catalog.version && source_version==table_at(catalog,id).source_schema_version && fingerprint==expected,
      "catalog_mismatch","input catalog or source schema binding differs from the supplied catalog");
}
// Public DTO codecs use SAX and direct canonical output, without a JSON DOM.
// Partial values are ordinary strings/vectors; unwinding publishes no event.
// Native reader ownership and acceptance are handled separately in EventReader.
template<class String=std::string> struct JsonWriter {
  String output;
  std::size_t limit=std::numeric_limits<std::size_t>::max();
  void raw(std::string_view text) {
    bounded(sum(output.size(),text.size()),limit,"JSON output exceeds record byte limit"); output.append(text);
  }
  void text(std::string_view value) {
    require_utf8(value); raw("\"");
    constexpr char hex[]="0123456789abcdef";
    for (const auto character : value) {
      const auto byte=static_cast<unsigned char>(character);
      switch (byte) {
        case '"': raw("\\\""); break;
        case '\\': raw("\\\\"); break;
        case '\b': raw("\\b"); break;
        case '\f': raw("\\f"); break;
        case '\n': raw("\\n"); break;
        case '\r': raw("\\r"); break;
        case '\t': raw("\\t"); break;
        default:
          if (byte<32) { const char encoded[]={'\\','u','0','0',hex[byte>>4],hex[byte&15]}; raw(std::string_view(encoded,6)); }
          else raw(std::string_view(&character,1));
      }
    }
    raw("\"");
  }
  void number(std::uint64_t value) {
    char buffer[32]; const auto result=std::to_chars(std::begin(buffer),std::end(buffer),value);
    raw(std::string_view(buffer,static_cast<std::size_t>(result.ptr-buffer)));
  }
  void signed_number(std::int64_t value) {
    char buffer[32]; const auto result=std::to_chars(std::begin(buffer),std::end(buffer),value);
    raw(std::string_view(buffer,static_cast<std::size_t>(result.ptr-buffer)));
  }
};
void names(auto& out,const auto& table,const auto& columns) {
  out.raw("["); bool first=true;
  for (const auto id : columns) { if (!first) { out.raw(","); } first=false; out.text(table.columns[id.value].name); }
  out.raw("]");
}
// Full metadata, including hints/statistics and constraint status, binds v1.
// Callers validate the catalog or retain an already admitted immutable owner.
void canonical_catalog_to(const auto& catalog,auto& out) {
  out.raw("{\"catalog\":{\"tables\":["); bool first_table=true;
  for (const auto& table : catalog.tables) {
    if (!first_table) { out.raw(","); } first_table=false;
    out.raw("{\"columns\":["); bool first_column=true;
    for (const auto& column : table.columns) {
      if (!first_column) { out.raw(","); } first_column=false; out.raw("{");
      if (column.type==ScalarType::string) out.raw("\"collation\":\"binary\",");
      if (column.decimal) {
        out.raw("\"decimal\":{\"precision\":"); out.number(column.decimal->precision);
        out.raw(",\"scale\":"); out.number(column.decimal->scale); out.raw("},");
      }
      out.raw("\"name\":"); out.text(column.name); out.raw(",\"nullable\":"); out.raw(column.nullable?"true":"false");
      out.raw(",\"type\":"); out.text(type_name(column.type)); out.raw("}");
    }
    out.raw("],\"constraints\":["); bool first_constraint=true;
    for (const auto& constraint : table.constraints) {
      if (!first_constraint) { out.raw(","); } first_constraint=false;
      std::visit([&](const auto& item) {
        out.raw("{\"columns\":"); names(out,table,item.columns); out.raw(",\"kind\":");
        out.text(requires{item.referenced_columns;}?"foreign_key":"unique"); out.raw(",\"name\":"); out.text(item.name);
        if constexpr (requires{item.referenced_columns;}) {
          const auto& target=catalog.tables[item.referenced_table.value];
          out.raw(",\"references\":{\"columns\":"); names(out,target,item.referenced_columns);
          out.raw(",\"table\":"); out.text(target.name); out.raw("}");
        }
        out.raw(",\"status\":"); out.text(item.status==ConstraintStatus::enforced?"enforced":"untrusted"); out.raw("}");
      },constraint);
    }
    out.raw("],\"key_hints\":["); bool first_hint=true;
    for (const auto& hint : table.key_hints) {
      if (!first_hint) { out.raw(","); } first_hint=false;
      out.raw("{\"columns\":"); names(out,table,hint.columns); out.raw(",\"reason\":"); out.text(hint.reason); out.raw("}");
    }
    out.raw("],\"name\":"); out.text(table.name); out.raw(",\"source_schema_version\":"); out.number(table.source_schema_version);
    out.raw(",\"statistics\":{\"distinct_counts\":["); bool first_estimate=true;
    for (const auto& estimate : table.statistics.distinct_counts) {
      if (!first_estimate) { out.raw(","); } first_estimate=false;
      out.raw("{\"columns\":"); names(out,table,estimate.columns); out.raw(",\"estimate\":"); out.number(estimate.estimate); out.raw("}");
    }
    out.raw("]"); if (table.statistics.row_count) { out.raw(",\"row_count\":"); out.number(*table.statistics.row_count); }
    out.raw("}}");
  }
  out.raw("],\"version\":"); out.number(catalog.version); out.raw("},\"schema_version\":1}");
}
std::string canonical_catalog(const auto& catalog) {
  catalog::validate_catalog(catalog);JsonWriter<> out;canonical_catalog_to(catalog,out);return std::move(out.output);
}
// Public owning DTO parser; operational readers use the funded JsonReader.
struct EventSax : nlohmann::json_sax<Json> {
  enum class Context { none, root, values, scalar, source, done };
  enum class Key { hash, catalog_version, operation, version, sequence, source, source_version, table, values, none };
  const InputLimits& limits;
  Context context=Context::none;
  Key root_key=Key::none;
  unsigned seen=0,source_seen=0;
  unsigned source_key=0;
  std::string scalar_key,hash,table,operation;
  std::optional<Value> scalar;
  std::uint64_t version=0,catalog_version=0,source_version=0;
  InputEvent event{{0,TableId{0},SetOperation::insert,{}},{}};
  explicit EventSax(const InputLimits& budget):limits(budget) {}
  [[noreturn]] static void invalid() { throw Error("invalid_document","input JSON token does not match the physical event schema"); }
  void value(Value item) {
    bounded(sum(event.update.values.size(),1),limits.columns,"physical input column limit exceeded");
    event.update.values.push_back(std::move(item));
  }
  bool unsigned_value(std::uint64_t item) {
    if (context==Context::values) {
      require(item<=static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()),"invalid_document","input integer exceeds int64 range");
      value(Value{static_cast<std::int64_t>(item)}); return true;
    }
    if (context==Context::source && source_key==2) { event.source_position->offset=item; return true; }
    if (context!=Context::root) invalid();
    switch (root_key) {
      case Key::version: version=item; break;
      case Key::catalog_version: catalog_version=item; break;
      case Key::source_version: source_version=item; break;
      case Key::sequence: event.update.sequence=item; break;
      default: invalid();
    }
    return true;
  }
  bool null() override { invalid(); }
  bool boolean(bool item) override { if (context!=Context::values) invalid(); value(Value{item}); return true; }
  bool number_integer(number_integer_t item) override {
    if (context==Context::values) { value(Value{item}); return true; }
    if (item<0) invalid();
    return unsigned_value(static_cast<std::uint64_t>(item));
  }
  bool number_unsigned(number_unsigned_t item) override { return unsigned_value(item); }
  bool number_float(number_float_t,const string_t&) override { invalid(); }
  bool string(string_t& item) override {
    if (context==Context::values) {
      bounded(item.size(),limits.field_bytes,"input string field exceeds its byte limit"); value(Value{item}); return true;
    }
    if (context==Context::scalar) {
      bounded(item.size(),limits.field_bytes,"tagged input field exceeds its byte limit");
      if (scalar_key=="date") scalar=Value{Date::parse(item)};
      else if (scalar_key=="decimal") scalar=Value{Decimal::parse(item)};
      else invalid();
      return true;
    }
    if (context==Context::source && source_key==1) {
      source_name(item,limits); event.source_position->source=item; return true;
    }
    if (context!=Context::root) invalid();
    switch (root_key) {
      case Key::hash: require(item.size()==64,"catalog_mismatch","input catalog fingerprint must have 64 hexadecimal characters"); hash=item; break;
      case Key::table: bounded(item.size(),limits.field_bytes,"physical table name exceeds field byte limit"); table=item; break;
      case Key::operation: require(item=="insert" || item=="delete","unsupported_input_operation","physical input operation must be insert or delete"); operation=item; break;
      default: invalid();
    }
    return true;
  }
  bool binary(binary_t&) override { invalid(); }
  bool start_object(std::size_t) override {
    if (context==Context::none) context=Context::root;
    else if (context==Context::root && root_key==Key::source) { context=Context::source; event.source_position=SourcePosition{"",0}; }
    else if (context==Context::values) { context=Context::scalar; scalar_key.clear(); scalar.reset(); }
    else invalid();
    return true;
  }
  bool key(string_t& item) override {
    if (context==Context::root) {
      constexpr std::array<std::string_view,9> names={"catalog_sha256","catalog_version","operation","schema_version","sequence","source_position","source_schema_version","table","values"};
      const auto found=std::find(names.begin(),names.end(),item); if (found==names.end()) invalid();
      const auto index=static_cast<unsigned>(found-names.begin());
      require((seen&(1U<<index))==0,"invalid_document","duplicate input JSON field"); seen|=1U<<index; root_key=static_cast<Key>(index);
    } else if (context==Context::source) {
      source_key=item=="source"?1U:item=="offset"?2U:0U;
      require(source_key!=0 && (source_seen&source_key)==0,"invalid_document","unknown or duplicate source-position field"); source_seen|=source_key;
    } else if (context==Context::scalar) {
      require(scalar_key.empty() && (item=="date" || item=="decimal"),"invalid_document","tagged input scalar needs exactly one date/decimal field"); scalar_key=item;
    } else invalid();
    return true;
  }
  bool end_object() override {
    if (context==Context::root) {
      constexpr auto required=((1U<<9)-1U)&~(1U<<static_cast<unsigned>(Key::source));
      require((seen&required)==required,"invalid_document","physical input JSON is missing required fields"); context=Context::done;
    } else if (context==Context::source) {
      require(source_seen==3,"invalid_document","source_position requires source and offset"); context=Context::root;
    } else if (context==Context::scalar) {
      require(scalar.has_value(),"invalid_document","empty tagged input scalar"); value(std::move(*scalar)); scalar.reset(); context=Context::values;
    } else invalid();
    return true;
  }
  bool start_array(std::size_t) override {
    if (context!=Context::root || root_key!=Key::values) { invalid(); }
    context=Context::values; return true;
  }
  bool end_array() override { if (context!=Context::values) invalid(); context=Context::root; return true; }
  bool parse_error(std::size_t,const std::string&,const nlohmann::detail::exception& error) override {
    throw Error("invalid_document",error.what());
  }
};
InputEvent json_event(std::string_view text,const auto& catalog,const InputLimits& limits,std::string_view fingerprint) {
  bounded(text.size(),limits.record_bytes,"JSON input record exceeds its byte limit");
  EventSax sax(limits);
  require(Json::sax_parse(text,&sax) && sax.context==EventSax::Context::done,"invalid_document","invalid physical event JSON");
  require(sax.version==1,"unsupported_version","unsupported physical input schema version");
  sax.event.update.table=catalog::find_table(catalog,sax.table);
  check_binding(sax.catalog_version,sax.source_version,sax.hash,sax.event.update.table,catalog,fingerprint);
  sax.event.update.operation=sax.operation=="insert"?SetOperation::insert:SetOperation::erase;
  validate_event(sax.event,catalog,limits); return std::move(sax.event);
}
struct BinaryReader {
  std::string_view input;
  std::size_t position=0;
  std::string_view take(std::size_t count) {
    require(count<=input.size()-position,"invalid_document","truncated binary input record");
    const auto result=input.substr(position,count); position+=count; return result;
  }
  std::uint64_t integer(std::size_t bytes) {
    const auto value=take(bytes); std::uint64_t result=0;
    for (std::size_t i=0;i<bytes;++i) result|=static_cast<std::uint64_t>(static_cast<unsigned char>(value[i]))<<(i*8);
    return result;
  }
  std::string string(std::size_t limit) {
    const auto count=integer(4); require(count<=limit,"resource_limit","binary field exceeds its byte limit");
    const auto value=take(static_cast<std::size_t>(count)); require_utf8(value); return std::string(value);
  }
};
InputEvent binary_event(std::string_view bytes,const auto& catalog,const InputLimits& limits,std::string_view fingerprint) {
  bounded(bytes.size(),limits.record_bytes,"binary input record exceeds its byte limit");
  BinaryReader input{bytes}; require(input.take(magic.size())==magic,"invalid_document","invalid binary input magic");
  require(input.integer(2)==1,"unsupported_version","unsupported binary input schema version");
  const auto length=input.integer(4);
  require(length==bytes.size()-input.position,"invalid_document","binary frame length differs from the complete record");
  const auto version=input.integer(8),source_version=input.integer(8);
  const auto hash=input.take(64); const auto sequence=input.integer(8);
  const auto table=catalog::find_table(catalog,input.string(limits.field_bytes));
  check_binding(version,source_version,hash,table,catalog,fingerprint);
  const auto operation=input.integer(1);
  require(operation==1 || operation==2,"unsupported_input_operation","unknown binary input operation");
  InputEvent event{{sequence,table,operation==1?SetOperation::insert:SetOperation::erase,{}},{}};
  const auto has_position=input.integer(1); require(has_position<=1,"invalid_document","invalid binary source-position flag");
  if (has_position) event.source_position=SourcePosition{input.string(limits.source_bytes),input.integer(8)};
  const auto fields=input.integer(4); require(fields<=limits.columns,"resource_limit","binary input column limit exceeded");
  require(fields==table_at(catalog,table).columns.size(),"invalid_update","binary row arity differs from physical schema");
  require(fields<=(bytes.size()-input.position)/2,"invalid_document","binary field count exceeds its remaining payload");
  event.update.values.reserve(static_cast<std::size_t>(fields));
  for (std::uint64_t i=0;i<fields;++i) {
    switch (input.integer(1)) {
      case 0: event.update.values.emplace_back(std::bit_cast<std::int64_t>(input.integer(8))); break;
      case 1: event.update.values.emplace_back(input.string(limits.field_bytes)); break;
      case 2: {
        const auto value=input.integer(1); require(value<=1,"invalid_document","binary Boolean must be zero or one");
        event.update.values.emplace_back(value!=0); break;
      }
      case 3: {
        bounded(10,limits.field_bytes,"date field exceeds its byte limit"); event.update.values.emplace_back(Date::parse(input.take(10))); break;
      }
      case 4: {
        const auto text=input.string(limits.field_bytes); const auto value=Decimal::parse(text);
        require(value.to_string()==text,"invalid_document","binary decimal text must be canonical"); event.update.values.emplace_back(value); break;
      }
      default: throw Error("invalid_document","unsupported binary scalar tag");
    }
  }
  require(input.position==bytes.size(),"invalid_document","binary input record has trailing bytes");
  validate_event(event,catalog,limits); return event;
}
struct BinaryWriter {
  std::string output;
  std::size_t limit;
  void raw(std::string_view bytes) {
    bounded(sum(output.size(),bytes.size()),limit,"binary input record exceeds its byte limit"); output.append(bytes);
  }
  void integer(std::uint64_t value,std::size_t count) {
    bounded(sum(output.size(),count),limit,"binary input record exceeds its byte limit");
    for (std::size_t i=0;i<count;++i) output.push_back(static_cast<char>((value>>(8*i))&255U));
  }
  void string(std::string_view value) {
    bounded(value.size(),std::numeric_limits<std::uint32_t>::max(),"binary string length exceeds uint32");
    integer(static_cast<std::uint64_t>(value.size()),4); raw(value);
  }
};
}  // namespace

namespace input_detail {
template<class CatalogView> std::array<char,64> native_catalog_digest(const resource::MemoryAccount& account,const CatalogView& schema,bool admitted) {
  if(!admitted)catalog::validate_catalog(schema);
  JsonWriter<Buffer> out{Buffer(account)};canonical_catalog_to(schema,out);return sha256_fixed(out.output.view());
}
std::array<char,64> catalog_digest(const resource::MemoryAccount& account,const Catalog& schema,bool admitted) {
  return native_catalog_digest(account,schema,admitted);
}
std::array<char,64> catalog_digest(const resource::MemoryAccount& account,const program::Catalog& schema,bool admitted) {
  return native_catalog_digest(account,schema,admitted);
}
resource::AccountedText catalog_fingerprint(const resource::MemoryAccount& account,const CatalogSource& catalog,bool admitted) {
  return catalog_source_detail::read(catalog,[&](const auto& schema) {
    if(!admitted)catalog::validate_catalog(schema);
    JsonWriter<Buffer> out{Buffer(account)};canonical_catalog_to(schema,out);
    const auto hash=sha256_fixed(out.output.view());
    return resource::AccountedText::copy_of(account,{hash.data(),hash.size()},memory_owner,resource::MemoryPurpose::immutable_metadata);
  });
}
} // namespace input_detail

template<class CatalogView> std::string input_catalog_sha256_impl(const CatalogView& catalog) {
  return sha256(canonical_catalog(catalog));
}
std::string input_catalog_sha256(const Catalog& catalog){return input_catalog_sha256_impl(catalog);}
std::string input_catalog_sha256(const program::Catalog& catalog){return input_catalog_sha256_impl(catalog);}

template<class CatalogView> void validate_input_event_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limits) {
  validate_event(event,catalog,limits);
}
void validate_input_event(const InputEvent& event,const Catalog& catalog,InputLimits limits){return validate_input_event_impl(event,catalog,limits);}
void validate_input_event(const InputEvent& event,const program::Catalog& catalog,InputLimits limits){return validate_input_event_impl(event,catalog,limits);}

template<class CatalogView> InputEvent read_input_json_impl(std::string_view text,const CatalogView& catalog,InputLimits limits) {
  bounded(text.size(),limits.record_bytes,"JSON input record exceeds its byte limit");
  return json_event(text,catalog,limits,input_catalog_sha256(catalog));
}
InputEvent read_input_json(std::string_view text,const Catalog& catalog,InputLimits limits){return read_input_json_impl(text,catalog,limits);}
InputEvent read_input_json(std::string_view text,const program::Catalog& catalog,InputLimits limits){return read_input_json_impl(text,catalog,limits);}

template<class CatalogView> std::string write_input_json_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limits) {
  const auto hash=input_catalog_sha256(catalog); validate_event(event,catalog,limits);
  JsonWriter<> out{{},limits.record_bytes};
  out.raw("{\"catalog_sha256\":"); out.text(hash); out.raw(",\"catalog_version\":"); out.number(catalog.version);
  out.raw(",\"operation\":"); out.text(event.update.operation==SetOperation::insert?"insert":"delete");
  out.raw(",\"schema_version\":1,\"sequence\":"); out.number(event.update.sequence);
  if (event.source_position) {
    out.raw(",\"source_position\":{\"offset\":"); out.number(event.source_position->offset);
    out.raw(",\"source\":"); out.text(event.source_position->source); out.raw("}");
  }
  out.raw(",\"source_schema_version\":"); out.number(table_at(catalog,event.update.table).source_schema_version);
  out.raw(",\"table\":"); out.text(table_at(catalog,event.update.table).name); out.raw(",\"values\":[");
  bool first=true;
  for (const auto& value : event.update.values) {
    if (!first) { out.raw(","); } first=false;
    std::visit([&](const auto& cell) {
      using T=std::decay_t<decltype(cell)>;
      if constexpr (std::is_same_v<T,std::int64_t>) out.signed_number(cell);
      else if constexpr (std::is_same_v<T,std::string>) out.text(cell);
      else if constexpr (std::is_same_v<T,bool>) out.raw(cell?"true":"false");
      else if constexpr (std::is_same_v<T,Date>) { out.raw("{\"date\":"); out.text(cell.to_string()); out.raw("}"); }
      else { out.raw("{\"decimal\":"); out.text(cell.to_string()); out.raw("}"); }
    },value);
  }
  out.raw("]}"); return std::move(out.output);
}
std::string write_input_json(const InputEvent& event,const Catalog& catalog,InputLimits limits){return write_input_json_impl(event,catalog,limits);}
std::string write_input_json(const InputEvent& event,const program::Catalog& catalog,InputLimits limits){return write_input_json_impl(event,catalog,limits);}

template<class CatalogView> InputEvent read_input_binary_impl(std::string_view bytes,const CatalogView& catalog,InputLimits limits) {
  bounded(bytes.size(),limits.record_bytes,"binary input record exceeds its byte limit");
  return binary_event(bytes,catalog,limits,input_catalog_sha256(catalog));
}
InputEvent read_input_binary(std::string_view bytes,const Catalog& catalog,InputLimits limits){return read_input_binary_impl(bytes,catalog,limits);}
InputEvent read_input_binary(std::string_view bytes,const program::Catalog& catalog,InputLimits limits){return read_input_binary_impl(bytes,catalog,limits);}

template<class CatalogView> std::string write_input_binary_impl(const InputEvent& event,const CatalogView& catalog,InputLimits limits) {
  const auto hash=input_catalog_sha256(catalog); validate_event(event,catalog,limits);
  BinaryWriter out{{},limits.record_bytes}; out.raw(magic); out.integer(1,2); out.integer(0,4);
  out.integer(catalog.version,8); out.integer(table_at(catalog,event.update.table).source_schema_version,8);
  out.raw(hash); out.integer(event.update.sequence,8); out.string(table_at(catalog,event.update.table).name);
  out.integer(event.update.operation==SetOperation::insert?1:2,1); out.integer(event.source_position?1:0,1);
  if (event.source_position) { out.string(event.source_position->source); out.integer(event.source_position->offset,8); }
  bounded(event.update.values.size(),std::numeric_limits<std::uint32_t>::max(),"binary column count exceeds uint32");
  out.integer(static_cast<std::uint64_t>(event.update.values.size()),4);
  for (const auto& value : event.update.values) {
    out.integer(value.index(),1);
    std::visit([&](const auto& cell) {
      using T=std::decay_t<decltype(cell)>;
      if constexpr (std::is_same_v<T,std::int64_t>) out.integer(std::bit_cast<std::uint64_t>(cell),8);
      else if constexpr (std::is_same_v<T,std::string>) out.string(cell);
      else if constexpr (std::is_same_v<T,bool>) out.integer(cell?1:0,1);
      else if constexpr (std::is_same_v<T,Date>) out.raw(cell.to_string());
      else out.string(cell.to_string());
    },value);
  }
  const auto length=out.output.size()-frame_header;
  bounded(length,std::numeric_limits<std::uint32_t>::max(),"binary payload exceeds uint32");
  for (std::size_t i=0;i<4;++i) out.output[10+i]=static_cast<char>((static_cast<std::uint64_t>(length)>>(8*i))&255U);
  return std::move(out.output);
}
std::string write_input_binary(const InputEvent& event,const Catalog& catalog,InputLimits limits){return write_input_binary_impl(event,catalog,limits);}
std::string write_input_binary(const InputEvent& event,const program::Catalog& catalog,InputLimits limits){return write_input_binary_impl(event,catalog,limits);}


} // namespace crown::io
