#pragma once

#include <compare>
#include <cstddef>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

namespace crown::frontend {
// Offsets are bytes into the owned UTF-8 source, with an exclusive end.
// PostgreSQL node `location` fields remain byte offsets in the untouched AST.
struct SourceRange {
  std::size_t begin = 0;
  std::size_t end = 0;
  auto operator<=>(const SourceRange&) const = default;
};
struct SqlDiagnostic {
  std::string code;
  std::string message;
  std::optional<std::size_t> byte_offset;
  std::optional<std::size_t> character_position;  // One based, as in PostgreSQL.
  std::optional<std::size_t> line;                // One based.
  std::optional<std::size_t> column;              // One based, Unicode code points.
};
struct SqlSyntax {
  std::string source;
  nlohmann::json ast;
  SourceRange statement;
};
struct ParseLimits {
  std::size_t source_bytes = 1024 * 1024;
  std::size_t ast_depth = 256;
};
using SqlParseResult = std::variant<SqlSyntax, SqlDiagnostic>;

// Exactly one nonempty statement; parsing grants no semantic admission.
// Both alternatives own all data. No libpg_query pointer escapes this call.
[[nodiscard]] SqlParseResult parse_sql(std::string_view source, ParseLimits limits = {});
}  // namespace crown::frontend
