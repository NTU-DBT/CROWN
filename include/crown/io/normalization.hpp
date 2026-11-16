#pragma once

#include "crown/frontend/normalize.hpp"
#include "crown/io/document.hpp"

namespace crown::io {
[[nodiscard]] Json write_sql_normalization(const frontend::SqlNormalizeResult& result);
struct ProgramReadLimits {
  frontend::BindLimits binding;
  frontend::NormalizeLimits normalization;
};
// Reconstruct owned executable state by replay; diagnostic envelopes are not
// programs. Host limits cap serialized limits without changing stored policy.
[[nodiscard]] frontend::NormalizedSql read_sql_normalization(std::string_view text, const ProgramReadLimits& limits = {});
[[nodiscard]] frontend::NormalizedSql upgrade_sql_normalization(const frontend::NormalizedSql& program, std::uint64_t target_version, const ProgramReadLimits& limits = {});
// Strict v1 envelope {schema_version:1, values:[typed scalar or NULL,...]}.
[[nodiscard]] std::vector<frontend::SqlValue> read_parameter_values(std::string_view text);
}  // namespace crown::io
