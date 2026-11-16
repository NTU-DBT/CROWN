#include "crown/io/input_view.hpp"
#include "crown/io/batch.hpp"
#include "crown/ir/program_model.hpp"
#include "input_native.hpp"
#include "ingest_text.hpp"
#include <array>
#include <limits>

namespace crown::io {
namespace {
std::optional<SourcePositionView> borrow_position(const std::optional<SourcePosition>& source) noexcept {
  if(!source)return {};
  return SourcePositionView{source->source,source->offset};
}
}
bool SourcePositionView::operator==(const SourcePosition& other) const {return source==other.source && offset==other.offset;}
InputEventView InputEventView::borrow(const InputEvent& source) noexcept {
  return {runtime::PhysicalUpdateView::borrow(source.update),borrow_position(source.source_position)};
}
WindowCommandView WindowCommandView::borrow(const WindowCommand& source) noexcept {
  WindowCommandView result;result.sequence=source.sequence;result.source_position=borrow_position(source.source_position);
  if(const auto* insert=std::get_if<WindowInsert>(&source.command))
    result.command=WindowInsertView{insert->label,insert->table,storage::TupleValuesView::borrow(insert->values),insert->timestamp};
  else if(const auto* withdraw=std::get_if<WindowWithdraw>(&source.command))result.command=*withdraw;
  else if(const auto* watermark=std::get_if<AdvanceWatermark>(&source.command))result.command=*watermark;
  return result;
}
namespace input_detail {
namespace {
void require(bool condition,std::string_view code,std::string_view message) {
  if(!condition)throw Error(std::string(code),std::string(message));
}
template<class CatalogView> RowIssue issue_for(const CatalogView& catalog,TableId table,storage::TupleValuesView values) {
  RowIssue issue{RowProblem::none,values.size(),0};
  if(table.value>=catalog.tables.size()){issue.problem=RowProblem::table;return issue;}
  const auto& columns=catalog.tables[table.value].columns;
  if(values.size()!=columns.size()){issue.problem=RowProblem::arity;return issue;}
  for(std::size_t field=0;field<values.size();++field) {
    issue.field=field;
    if(const auto* legacy=values.legacy_row();legacy && (*legacy)[field].valueless_by_exception()) {
      issue.problem=RowProblem::scalar;return issue;
    }
    const auto scalar=values[field];
    if(storage::type_of(scalar)!=columns[field].type){issue.problem=RowProblem::type;return issue;}
    if(!columns[field].decimal)continue;
    if(columns[field].type!=ScalarType::decimal){issue.problem=RowProblem::decimal_catalog;return issue;}
    const auto parts=std::get<storage::InlineDecimal>(scalar).parts();const auto spec=*columns[field].decimal;
    const auto integer_digits=parts.digits=="0" || parts.digits.size()<=parts.scale?std::size_t{0}:parts.digits.size()-parts.scale;
    if(parts.scale>spec.scale || integer_digits+spec.scale>spec.precision){issue.problem=RowProblem::decimal_domain;return issue;}
  }
  return issue;
}
template<class CatalogView> void reject_row(const CatalogView& catalog,TableId table,RowIssue issue) {
  switch(issue.problem) {
    case RowProblem::none:return;
    case RowProblem::table:throw Error("invalid_update","table ID out of range");
    case RowProblem::arity:throw Error("invalid_update","row arity differs from physical schema");
    case RowProblem::scalar:throw Error("invalid_cq","value has no scalar type");
    case RowProblem::type:throw Error("invalid_update","row type differs at column "+std::string(catalog.tables[table.value].columns[issue.field].name));
    case RowProblem::decimal_catalog:throw Error("invalid_catalog","decimal specification requires a decimal column");
    case RowProblem::decimal_domain:throw Error("scalar_overflow","row cannot be represented exactly by decimal specification at column "+std::string(catalog.tables[table.value].columns[issue.field].name));
  }
  std::terminate();
}
void position(const std::optional<SourcePositionView>& source,const InputLimits& limits) {
  if(!source)return;
  require(source->source.size()<=limits.source_bytes,"resource_limit","input source identifier exceeds its byte limit");
  require(!source->source.empty() && source->source.find('\0')==std::string_view::npos,
      "invalid_source_position","source identifier must be nonempty and contain no NUL");
  ingest_detail::require_utf8(source->source);
}
void payload(storage::TupleValuesView values,const InputLimits& limits,bool window) {
  // Typed payload units differ from wire length; preserve the established UTF-8 error order.
  std::size_t total=0;
  for(const auto scalar:values) {
    std::size_t bytes=1;
    const auto* text=std::get_if<std::string_view>(&scalar);
    if(text){bytes=text->size();if(window)ingest_detail::require_utf8(*text);}
    else if(std::holds_alternative<Date>(scalar))bytes=10; // Fixed finite YYYY-MM-DD domain.
    else if(const auto* decimal=std::get_if<storage::InlineDecimal>(&scalar)) {
      std::array<char,storage::InlineDecimal::text_capacity> encoded{};bytes=decimal->render(encoded);
    }
    if(!std::holds_alternative<std::int64_t>(scalar) && !std::holds_alternative<bool>(scalar))
      require(bytes<=limits.field_bytes,"resource_limit",window?"window input scalar field exceeds its byte limit":"physical input scalar field exceeds its byte limit");
    require(bytes<=std::numeric_limits<std::size_t>::max()-total,"resource_limit",window?"typed input size accounting exhausted":"input size accounting exhausted");
    total+=bytes;
    require(total<=limits.record_bytes,"resource_limit",window?"window input payload exceeds its record byte limit":"physical input payload exceeds its record byte limit");
    if(text && !window)ingest_detail::require_utf8(*text);
  }
}
template<class CatalogView> void event(const InputEventView& value,const CatalogView& catalog,const InputLimits& limits,RowIssue issue) {
  require(value.update.table.value<catalog.tables.size(),"unknown_table","physical input table ID is outside the catalog");
  require(value.update.sequence!=0,"invalid_sequence","input sequence must be positive");
  require(value.update.operation==SetOperation::insert || value.update.operation==SetOperation::erase,
      "unsupported_input_operation","physical input supports only insert and delete");
  require(issue.arity<=limits.columns,"resource_limit","physical input column limit exceeded");
  reject_row(catalog,value.update.table,issue);payload(value.update.values,limits,false);
  require(catalog.tables[value.update.table.value].name.size()<=limits.field_bytes,"resource_limit","physical table name exceeds field byte limit");
  position(value.source_position,limits);
}
template<class CatalogView> void command(const WindowCommandView& value,const CatalogView& catalog,const InputLimits& limits,RowIssue issue) {
  require(!value.command.valueless_by_exception() && !std::holds_alternative<std::monostate>(value.command),
      "invalid_window_command","window command has no payload");
  require(value.sequence!=0,"invalid_sequence","window command sequence must be positive");
  if(const auto* insert=std::get_if<WindowInsertView>(&value.command)) {
    require(insert->table.value<catalog.tables.size(),"unknown_table","window input table is outside the catalog");
    require(issue.arity<=limits.columns,"resource_limit","window input column limit exceeded");
    reject_row(catalog,insert->table,issue);payload(insert->values,limits,true);
    require(catalog.tables[insert->table.value].name.size()<=limits.field_bytes,"resource_limit","window input table name exceeds field byte limit");
  }
  position(value.source_position,limits);
}
} // namespace
RowIssue row_issue(const Catalog& catalog,TableId table,storage::TupleValuesView values){return issue_for(catalog,table,values);}
RowIssue row_issue(const program::Catalog& catalog,TableId table,storage::TupleValuesView values){return issue_for(catalog,table,values);}
void validate(const InputEventView& value,const Catalog& catalog,const InputLimits& limits,RowIssue issue){event(value,catalog,limits,issue);}
void validate(const InputEventView& value,const program::Catalog& catalog,const InputLimits& limits,RowIssue issue){event(value,catalog,limits,issue);}
void validate(const WindowCommandView& value,const Catalog& catalog,const InputLimits& limits,RowIssue issue){command(value,catalog,limits,issue);}
void validate(const WindowCommandView& value,const program::Catalog& catalog,const InputLimits& limits,RowIssue issue){command(value,catalog,limits,issue);}
} // namespace input_detail
} // namespace crown::io
