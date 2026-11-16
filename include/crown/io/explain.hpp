#pragma once
#include "crown/observability/explain.hpp"
#include "crown/observability/query_explain.hpp"

namespace crown::io {
struct ExplainTextLimits { std::size_t bytes=16*1024*1024; };
// Strict UTF-8 text transport. Native admission remains arbitrary-byte safe.
// Invalid UTF-8 or encoded-byte exhaustion fails this export only. No JSON DOM
// is built, and returned strings contain a complete artifact or are not returned.
// Encoded-byte caps do not bound buffer capacity or retained report storage.
[[nodiscard]] std::string write_explain_json(const observability::PlanExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_text(const observability::PlanExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_dot(const observability::PlanExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_tree_json(const observability::PlanExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_json(const observability::QueryExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_text(const observability::QueryExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_dot(const observability::QueryExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_tree_json(const observability::QueryExplanation&,ExplainTextLimits={});
} // namespace crown::io
