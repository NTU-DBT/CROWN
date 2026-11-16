#include "crown/io/sql_aggregate_input.hpp"
#include "crown/io/document.hpp"
#include "crown/api/error.hpp"
#include "../frontend/sql_rows_value.hpp"
#include <algorithm>
#include <limits>

namespace crown::io {
namespace {
namespace ar=recovery::sql_aggregate;
using Cell=runtime::sql_rows::Cell;
template<class T> using Items=std::vector<T,resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account,resource::MemoryPurpose::scratch);
}
void require(bool valid,const char* code,const char* message) {
  if(!valid)throw Error(code,message);
}
void fields(const Json& value,std::initializer_list<std::string_view> required,
    std::initializer_list<std::string_view> optional={}) {
  require(value.is_object(),"invalid_document","aggregate input requires an object");
  for(const auto key:required)
    require(value.contains(key),"invalid_document","aggregate input is missing a field");
  for(auto it=value.begin();it!=value.end();++it)
    require(std::find(required.begin(),required.end(),it.key())!=required.end() ||
        std::find(optional.begin(),optional.end(),it.key())!=optional.end(),
        "invalid_document","unknown aggregate input field");
}
std::uint64_t number(const Json& value) {
  require(value.is_number_unsigned() || (value.is_number_integer() && value.get<std::int64_t>()>=0),
      "invalid_document","aggregate input requires an unsigned integer");
  return value.get<std::uint64_t>();
}
const std::string& text(const Json& value) {
  require(value.is_string(),"invalid_document","aggregate input requires a string");
  return value.get_ref<const std::string&>();
}
// Inline scalars borrow only the DOM's TEXT. All such borrows are copied into
// the command's single text buffer before the temporary DOM is released.
Cell scalar(const Json& value,std::size_t field_bytes) {
  if(value.is_null())return {};
  if(value.is_string()) {
    require(text(value).size()<=field_bytes,"resource_limit","aggregate scalar string byte limit exceeded");
    return storage::ScalarView{std::string_view(text(value))};
  }
  if(value.is_boolean())return storage::ScalarView{value.get<bool>()};
  if(value.is_number_unsigned()) {
    const auto n=number(value);
    require(n<=INT64_MAX,"invalid_document","SQL integer exceeds int64");
    return storage::ScalarView{static_cast<std::int64_t>(n)};
  }
  if(value.is_number_integer())return storage::ScalarView{value.get<std::int64_t>()};
  require(value.is_object() && value.size()==1,"invalid_document","expected a nullable exact SQL scalar");
  const auto tag=value.begin();const auto& tagged=text(tag.value());
  require(tagged.size()<=field_bytes,"resource_limit","aggregate tagged scalar byte limit exceeded");
  if(value.contains("date"))return storage::ScalarView{Date::parse(tagged)};
  require(value.contains("decimal"),"invalid_document","unknown SQL scalar tag");
  return storage::ScalarView{storage::InlineDecimal::parse(tagged)};
}
const frontend::SqlRowsSource& source(const frontend::SqlAggregateProgram& program,const Json& name) {
  const auto& exact=text(name);
  const auto sources=program.source_program().sources();
  const auto found=std::find_if(sources.begin(),sources.end(),[&](const auto& s){return s.name==exact;});
  require(found!=sources.end(),"unknown_table","aggregate input table is not a physical source name");
  return *found;
}
} // namespace

struct SqlAggregateJsonCommand::Data {
  std::uint64_t sequence;
  ar::ReaderPosition reader;
  Items<char> text;
  Items<Cell> cells;
  Items<runtime::sql_rows::SourceReplacement> replacements;
  std::optional<ar::SourcePosition> source;
  Data(const resource::MemoryAccount& account,std::uint64_t next,ar::ReaderPosition position)
      :sequence(next),reader(position),text(allocator<char>(account)),cells(allocator<Cell>(account)),
       replacements(allocator<runtime::sql_rows::SourceReplacement>(account)) {}
  std::string_view copy(std::string_view value) {
    const auto begin=text.size();text.insert(text.end(),value.begin(),value.end());
    // Empty TEXT needs no pointer arithmetic on an empty vector's null data.
    return value.empty()?std::string_view{}:std::string_view(text.data()+begin,value.size());
  }
};
struct SqlAggregateJsonlReader::Data {
  std::istream& input;
  resource::MemoryAccount account;
  frontend::SqlAggregateProgram program;
  SqlAggregateJsonlLimits limits;
  std::uint64_t logged;
  ar::ReaderPosition position;
  Items<char> line;
  bool poison=false,ended=false;
  Data(std::istream& stream,const resource::MemoryAccount& owner,
      const frontend::SqlAggregateProgram& schema,std::uint64_t w,ar::ReaderPosition origin,
      SqlAggregateJsonlLimits admitted)
      :input(stream),account(owner),program(frontend::SqlAggregateProgram::freeze(owner,schema)),
       limits(admitted),logged(w),position(origin),line(allocator<char>(owner)) {
    require(limits.record_bytes<std::numeric_limits<std::size_t>::max(),"invalid_options","record byte limit is too large");
    require(origin.bytes<=limits.bytes && origin.records<=limits.records && origin.records<=logged &&
        ((origin.bytes==0)==(origin.records==0)),"invalid_input_progress","invalid aggregate reader origin");
  }
};

SqlAggregateJsonCommand::SqlAggregateJsonCommand(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
SqlAggregateJsonCommand::~SqlAggregateJsonCommand()=default;
SqlAggregateJsonCommand::SqlAggregateJsonCommand(SqlAggregateJsonCommand&&) noexcept=default;
SqlAggregateJsonCommand& SqlAggregateJsonCommand::operator=(SqlAggregateJsonCommand&&) noexcept=default;
ar::InputView SqlAggregateJsonCommand::view() const & {
  require(bool(data_),"invalid_input_state","aggregate command is moved from");
  return {data_->sequence,data_->replacements,data_->source,data_->reader};
}
SqlAggregateJsonlReader::SqlAggregateJsonlReader(std::istream& stream,const resource::MemoryAccount& account,
    const frontend::SqlAggregateProgram& program,std::uint64_t logged,ar::ReaderPosition origin,SqlAggregateJsonlLimits limits)
    :data_(resource::make_accounted_unique<Data>(account,resource::MemoryPurpose::scratch,
        stream,account,program,logged,origin,limits)) {}
SqlAggregateJsonlReader::~SqlAggregateJsonlReader()=default;
SqlAggregateJsonlReader::SqlAggregateJsonlReader(SqlAggregateJsonlReader&&) noexcept=default;
SqlAggregateJsonlReader& SqlAggregateJsonlReader::operator=(SqlAggregateJsonlReader&&) noexcept=default;
bool SqlAggregateJsonlReader::requires_reopen() const noexcept {return !data_ || data_->poison;}
ar::ReaderPosition SqlAggregateJsonlReader::position() const {
  require(data_ && !data_->poison,"invalid_input_state","aggregate reader requires reopen");return data_->position;
}

std::optional<SqlAggregateJsonCommand> SqlAggregateJsonlReader::next() {
  require(data_ && !data_->poison,"invalid_input_state","aggregate reader requires reopen");
  auto& d=*data_;if(d.ended)return {};
  d.poison=true;d.line.clear();auto next=d.position;
  // Bound the line during framing, including one optional trailing CR. Logical
  // counters include LF/CRLF and never depend on stream read-ahead/tellg state.
  for(;;) {
    const auto c=d.input.get();
    if(c==std::char_traits<char>::eof()) {
      require(!d.input.bad() && d.input.eof(),"io_error","failed reading aggregate input");
      d.ended=true;break;
    }
    require(next.bytes<d.limits.bytes,"resource_limit","aggregate input byte limit exceeded");++next.bytes;
    if(c=='\n')break;
    require(d.line.size()<=d.limits.record_bytes,"resource_limit","aggregate JSON record byte limit exceeded");
    d.line.push_back(static_cast<char>(c));
  }
  if(d.line.empty() && d.ended && next==d.position) {d.poison=false;return {};}
  if(!d.line.empty() && d.line.back()=='\r')d.line.pop_back();
  require(d.line.size()<=d.limits.record_bytes,"resource_limit","aggregate JSON record byte limit exceeded");
  require(next.records<d.limits.records && d.logged<UINT64_MAX,"resource_limit","aggregate input record/sequence limit exceeded");
  ++next.records;
  const auto json=read_json({d.line.data(),d.line.size()});
  fields(json,{"schema_version","binding_sha256","sequence","replacements"},{"source_position"});
  require(number(json.at("schema_version"))==1,"unsupported_version","unsupported aggregate JSON schema version");
  const auto& binding=d.program.identity().binding;
  require(text(json.at("binding_sha256"))==std::string_view(binding.data(),binding.size()),
      "input_binding","aggregate input belongs to another genuine SQL binding");
  const auto sequence=number(json.at("sequence"));
  require(sequence==d.logged+1,"invalid_input_sequence","aggregate input must continue logged W+1");
  const auto& edits=json.at("replacements");
  require(edits.is_array(),"invalid_document","aggregate replacements must be an array");
  require(edits.size()<=d.limits.replacements,"resource_limit","aggregate replacement limit exceeded");
  std::size_t cells=0,text_bytes=0;
  for(const auto& edit:edits) {
    fields(edit,{"table","source_schema_version","values","before","after"});
    const auto& table=source(d.program,edit.at("table"));
    require(number(edit.at("source_schema_version"))==table.schema_version,"input_binding","physical source schema version differs");
    const auto& values=edit.at("values");
    require(values.is_array() && values.size()==table.columns.size(),"invalid_input_row","aggregate input requires the complete physical row");
    require(values.size()<=d.limits.cells-cells,"resource_limit","aggregate input cell limit exceeded");cells+=values.size();
    for(std::size_t i=0;i<values.size();++i) {
      const auto cell=scalar(values[i],d.limits.field_bytes);
      require(frontend::rows_detail::fits(cell,table.columns[i].type),"invalid_input_row","aggregate input scalar differs from its SQL source type");
      if(cell && std::holds_alternative<std::string_view>(*cell)) {
        const auto bytes=std::get<std::string_view>(*cell).size();
        require(bytes<=d.limits.field_bytes && bytes<=d.limits.record_bytes-text_bytes,"resource_limit","aggregate TEXT byte limit exceeded");text_bytes+=bytes;
      }
    }
    (void)number(edit.at("before"));(void)number(edit.at("after"));
  }
  std::string_view name;std::uint64_t offset=0;
  if(json.contains("source_position")) {
    const auto& position=json.at("source_position");fields(position,{"source","offset"});
    name=text(position.at("source"));offset=number(position.at("offset"));
    require(!name.empty() && frontend::rows_detail::text_fits(name),"invalid_source_position","source name must be nonempty SQL UTF8 TEXT");
    require(name.size()<=d.limits.source_bytes && name.size()<=d.limits.record_bytes-text_bytes,"resource_limit","source name byte limit exceeded");text_bytes+=name.size();
  }
  auto command=resource::make_accounted_unique<SqlAggregateJsonCommand::Data>(d.account,
      resource::MemoryPurpose::scratch,d.account,sequence,next);
  command->text.reserve(text_bytes);command->cells.reserve(cells);command->replacements.reserve(edits.size());
  for(const auto& edit:edits) {
    const auto& table=source(d.program,edit.at("table"));const auto begin=command->cells.size();
    for(const auto& value:edit.at("values")) {
      auto cell=scalar(value,d.limits.field_bytes);
      if(cell && std::holds_alternative<std::string_view>(*cell))cell=storage::ScalarView{command->copy(std::get<std::string_view>(*cell))};
      command->cells.push_back(cell);
    }
    command->replacements.push_back({table.table,std::span<const Cell>(command->cells).subspan(begin,table.columns.size()),
        number(edit.at("before")),number(edit.at("after"))});
  }
  if(!name.empty())command->source=ar::SourcePosition{command->copy(name),offset};
  d.position=next;d.logged=sequence;d.poison=false;
  return SqlAggregateJsonCommand(std::move(command));
}
} // namespace crown::io
