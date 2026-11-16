#include "crown/io/sql.hpp"

namespace crown::io {
nlohmann::json write_sql_parse(const frontend::SqlParseResult& result) {
  // Syntax export deep-copies the ordinary AST/source; semantic admission is separate.
  using Json = nlohmann::json;
  Json output{{"schema_version", 1}, {"parser", "libpg_query"}, {"parser_version", "18.1.0"},
              {"postgres_version", 180006}, {"admission_status", "not_checked"}};
  if (const auto* syntax = std::get_if<frontend::SqlSyntax>(&result)) {
    output["syntax_valid"] = true;
    output["source"] = syntax->source;
    output["statement"] = {{"begin", syntax->statement.begin}, {"end", syntax->statement.end}};
    output["ast"] = syntax->ast;
  } else {
    const auto& diagnostic = std::get<frontend::SqlDiagnostic>(result);
    output["syntax_valid"] = false;
    const auto optional = [](std::optional<std::size_t> value) { return value ? Json(*value) : Json(nullptr); };
    output["diagnostic"] = {{"code", diagnostic.code}, {"message", diagnostic.message},
        {"byte_offset", optional(diagnostic.byte_offset)}, {"character_position", optional(diagnostic.character_position)},
        {"line", optional(diagnostic.line)}, {"column", optional(diagnostic.column)}};
  }
  return output;
}
}  // namespace crown::io
