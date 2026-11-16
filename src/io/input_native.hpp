#pragma once
#include "crown/io/input_view.hpp"
#include "crown/io/ingest.hpp"

namespace crown::io::input_detail {
// A permanent row rejection can be retained instead of an unusable caller Row.
// Its envelope/column-limit precedence is replayed only when it reaches the head.
enum class RowProblem {none,table,arity,scalar,type,decimal_catalog,decimal_domain};
struct RowIssue {RowProblem problem=RowProblem::none;std::size_t arity=0,field=0;};
[[nodiscard]] RowIssue row_issue(const Catalog&,TableId,storage::TupleValuesView);
[[nodiscard]] RowIssue row_issue(const program::Catalog&,TableId,storage::TupleValuesView);
void validate(const InputEventView&,const Catalog&,const InputLimits&,RowIssue);
void validate(const InputEventView&,const program::Catalog&,const InputLimits&,RowIssue);
void validate(const WindowCommandView&,const Catalog&,const InputLimits&,RowIssue);
void validate(const WindowCommandView&,const program::Catalog&,const InputLimits&,RowIssue);
} // namespace crown::io::input_detail
