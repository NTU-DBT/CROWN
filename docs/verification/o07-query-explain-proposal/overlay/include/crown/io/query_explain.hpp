#pragma once
#include "crown/observability/query_explain.hpp"
namespace crown::io {
struct QueryExplainTextLimits { std::size_t bytes=16*1024*1024; };
// Separate allocating, bounded strict UTF-8 transport; never admission/unwind.
[[nodiscard]] std::string write_query_explain_json(const observability::QueryExplanation&,QueryExplainTextLimits={});
[[nodiscard]] std::string write_query_explain_text(const observability::QueryExplanation&,QueryExplainTextLimits={});
// Both tree exports reject when no genuine checked witness was published.
[[nodiscard]] std::string write_query_explain_tree_json(const observability::QueryExplanation&,QueryExplainTextLimits={});
[[nodiscard]] std::string write_query_explain_dot(const observability::QueryExplanation&,QueryExplainTextLimits={});
} // namespace crown::io
