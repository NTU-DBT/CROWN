#include "crown/frontend/parser.hpp"
#include "parser_detail.hpp"

#include "crown/api/error.hpp"
#include <limits>
#include <mutex>
#include <pg_query.h>
#include <utility>

namespace crown::frontend {
std::mutex& parser_detail::mutex() { static std::mutex value; return value; }
namespace {
static_assert(PG_VERSION_NUM == 180006, "SQL AST contract requires PostgreSQL 18.6");

class ParseOwner {
 public:
  explicit ParseOwner(const char* source) : result_(pg_query_parse(source)) {}
  ~ParseOwner() { pg_query_free_parse_result(result_); }
  ParseOwner(const ParseOwner&) = delete;
  ParseOwner& operator=(const ParseOwner&) = delete;
  [[nodiscard]] const PgQueryParseResult& get() const { return result_; }
 private:
  PgQueryParseResult result_;
};

bool continuation(unsigned char byte) { return byte >= 0x80 && byte <= 0xbf; }
// A strict UTF-8 boundary is required before the NUL-terminated C parser and
// before interpreting PostgreSQL character positions. Reject overlong forms,
// surrogate code points and values above U+10FFFF as well as truncated input.
std::optional<std::size_t> invalid_utf8(std::string_view source) {
  for (std::size_t i = 0; i < source.size();) {
    const auto byte = static_cast<unsigned char>(source[i]);
    if (byte < 0x80) { ++i; continue; }
    std::size_t length = 0;
    if (byte >= 0xc2 && byte <= 0xdf) length = 2;
    else if (byte >= 0xe0 && byte <= 0xef) length = 3;
    else if (byte >= 0xf0 && byte <= 0xf4) length = 4;
    else return i;
    if (source.size() - i < length) return i;
    for (std::size_t j = 1; j < length; ++j) {
      if (!continuation(static_cast<unsigned char>(source[i + j]))) return i + j;
    }
    const auto second = static_cast<unsigned char>(source[i + 1]);
    if ((byte == 0xe0 && second < 0xa0) || (byte == 0xed && second >= 0xa0) ||
        (byte == 0xf0 && second < 0x90) || (byte == 0xf4 && second >= 0x90)) return i;
    i += length;
  }
  return std::nullopt;
}
SqlDiagnostic diagnostic_at(std::string code, std::string message, std::string_view source,
                            std::optional<std::size_t> offset = std::nullopt) {
  SqlDiagnostic result{std::move(code), std::move(message), offset, {}, {}, {}};
  if (!offset) return result;
  result.character_position = 1;
  result.line = 1;
  result.column = 1;
  for (std::size_t i = 0; i < *offset; ++i) {
    if (source[i] == '\n') { ++*result.line; result.column = 1; }
    else if (!continuation(static_cast<unsigned char>(source[i]))) ++*result.column;
    if (!continuation(static_cast<unsigned char>(source[i]))) ++*result.character_position;
  }
  return result;
}
std::optional<std::size_t> byte_position(std::string_view source, int character_position) {
  if (character_position <= 0) return std::nullopt;
  const auto wanted = static_cast<std::size_t>(character_position);
  std::size_t position = 1;
  for (std::size_t i = 0; i < source.size(); ++i) {
    if (!continuation(static_cast<unsigned char>(source[i]))) {
      if (position == wanted) return i;
      ++position;
    }
  }
  if (wanted == position) return source.size();  // Error at end of input.
  return std::nullopt;
}
std::size_t statement_offset(const nlohmann::json& statement, const char* field) {
  if (!statement.contains(field)) return 0;  // Upstream omits zero fields.
  const auto& value = statement.at(field);
  if (!value.is_number_integer() || value.get<std::int64_t>() < 0) {
    throw Error("parser_contract", std::string("invalid upstream ") + field);
  }
  return value.get<std::size_t>();
}
}  // namespace

SqlParseResult parse_sql(std::string_view source, ParseLimits limits) {
  if (source.size() > limits.source_bytes || source.size() > static_cast<std::size_t>(std::numeric_limits<int>::max())) {
    return diagnostic_at("resource_limit", "SQL source exceeds the configured byte limit", source);
  }
  if (const auto offset = invalid_utf8(source)) {
    // Coordinates on malformed UTF-8 would imply a nonexistent character map.
    return SqlDiagnostic{"invalid_encoding", "SQL source must be valid UTF-8", offset, {}, {}, {}};
  }
  if (const auto offset = source.find('\0'); offset != std::string_view::npos) {
    return diagnostic_at("invalid_encoding", "SQL source contains an embedded NUL byte", source, offset);
  }
  SqlSyntax syntax{std::string(source), {}, {}};
  // Isolate upstream initialization and parser state from concurrent wrapper
  // calls. The upstream per-thread top context is cached until thread exit;
  // every result and per-call memory context is freed before returning.
  const std::lock_guard lock(parser_detail::mutex());
  const ParseOwner owner(syntax.source.c_str());
  const auto& parsed = owner.get();
  if (parsed.error) {
    const std::string message = parsed.error->message ? parsed.error->message : "SQL parser failed";
    const auto code = message.find("stack depth limit") != std::string::npos ||
                      message.find("memory exhausted") != std::string::npos ||
                      message.find("out of memory") != std::string::npos ? "resource_limit" : "sql_syntax_error";
    return diagnostic_at(code, message, source, byte_position(source, parsed.error->cursorpos));
  }
  if (!parsed.parse_tree) throw Error("parser_contract", "libpg_query returned neither an AST nor an error");
  try {
    const auto depth_limit = limits.ast_depth;
    syntax.ast = nlohmann::json::parse(parsed.parse_tree,
        [depth_limit](int depth, nlohmann::json::parse_event_t, nlohmann::json&) {
          if (static_cast<std::size_t>(depth) > depth_limit) throw Error("resource_limit", "SQL AST exceeds the configured nesting limit");
          return true;
        });
  } catch (const Error& error) {
    if (error.code() != "resource_limit") throw;
    return diagnostic_at(error.code(), error.what(), source);
  } catch (const nlohmann::json::exception& error) {
    throw Error("parser_contract", std::string("invalid upstream AST JSON: ") + error.what());
  }
  if (!syntax.ast.is_object() || !syntax.ast.contains("version") ||
      !syntax.ast.at("version").is_number_integer() || syntax.ast.at("version").get<std::int64_t>() != PG_VERSION_NUM ||
      !syntax.ast.contains("stmts") || !syntax.ast.at("stmts").is_array()) {
    throw Error("parser_contract", "unexpected libpg_query AST version or envelope");
  }
  const auto& statements = syntax.ast.at("stmts");
  if (statements.empty()) return diagnostic_at("empty_sql", "expected one nonempty SQL statement", source, 0);
  if (statements.size() != 1) {
    const auto offset = statement_offset(statements[1], "stmt_location");
    return diagnostic_at("multiple_statements", "expected exactly one SQL statement", source, offset);
  }
  const auto& statement = statements[0];
  if (!statement.is_object() || !statement.contains("stmt") || !statement.at("stmt").is_object()) {
    throw Error("parser_contract", "missing upstream statement node");
  }
  syntax.statement.begin = statement_offset(statement, "stmt_location");
  const auto length = statement_offset(statement, "stmt_len");
  if (syntax.statement.begin > source.size() || length > source.size() - syntax.statement.begin) {
    throw Error("parser_contract", "upstream statement range exceeds source");
  }
  // A zero stmt_len means the remainder of input, not an empty statement.
  syntax.statement.end = length == 0 ? source.size() : syntax.statement.begin + length;
  return syntax;
}
}  // namespace crown::frontend
