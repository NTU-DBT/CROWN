#include "crown/frontend/parser.hpp"
#include "crown/io/sql.hpp"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace {
using namespace crown::frontend;
void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
const SqlSyntax& syntax(const SqlParseResult& result) {
  if (const auto* parsed = std::get_if<SqlSyntax>(&result)) return *parsed;
  throw std::runtime_error("unexpected parse failure: " + std::get<SqlDiagnostic>(result).message);
}
const SqlDiagnostic& failure(const SqlParseResult& result, std::string_view code) {
  check(std::holds_alternative<SqlDiagnostic>(result), "expected failure: " + std::string(code));
  const auto& diagnostic = std::get<SqlDiagnostic>(result);
  check(diagnostic.code == code, "wrong failure: " + diagnostic.code + ", expected " + std::string(code));
  return diagnostic;
}
void ownership_and_boundaries() {
  auto owned = parse_sql(std::string("/* comment */ SELECT DISTINCT \"x\" AS \"Result\" FROM \"R\"; -- tail"));
  const auto snapshot = crown::io::write_sql_parse(owned).dump();
  check(syntax(owned).source.ends_with("-- tail"), "source text retained after temporary input dies");
  check(syntax(owned).ast.at("version") == 180006, "pinned PostgreSQL AST");
  check(syntax(owned).ast.at("stmts").size() == 1, "one raw statement");
  for (std::size_t i = 0; i < 500; ++i) {
    check(syntax(parse_sql("SELECT 1")).statement == SourceRange{0, 8}, "zero raw length consumes remainder");
    static_cast<void>(failure(parse_sql("SELECT FROM;"), "sql_syntax_error"));
    static_cast<void>(failure(parse_sql("SELECT 1; SELECT 2"), "multiple_statements"));
    // This throws inside JSON conversion after ParseOwner was constructed.
    static_cast<void>(failure(parse_sql("SELECT 1", {1024, 0}), "resource_limit"));
  }
  check(crown::io::write_sql_parse(owned).dump() == snapshot, "prior AST and source survive later success/error calls");
  auto copy = owned;
  auto moved = std::move(owned);
  check(crown::io::write_sql_parse(copy).dump() == snapshot && crown::io::write_sql_parse(moved).dump() == snapshot,
        "parse results have ordinary owning copy/move lifetimes");

  for (const auto& text : {"", "   ", ";;;", "-- comment", "/* nested /* inner */ outer */ ;"}) {
    static_cast<void>(failure(parse_sql(text), "empty_sql"));
  }
  for (const auto& text : {"SELECT ';'", "SELECT 1; -- ; SELECT 2", ";;SELECT 1;;", "SELECT $$a;b$$", "SELECT E'a;\\nb'"}) {
    static_cast<void>(syntax(parse_sql(text)));
  }
  const auto multiple = parse_sql("SELECT 1; SELECT 2");
  check(failure(multiple, "multiple_statements").byte_offset == 10, "second raw statement location preserved");
  static_cast<void>(failure(parse_sql("SELECT 1; SELECT FROM;"), "sql_syntax_error"));
  static_cast<void>(failure(parse_sql("SELECT 1 /* unclosed"), "sql_syntax_error"));
  for (const auto& text : {"SELECT x FROM r", "SELECT NULL", "CREATE TABLE t(x int)", "SELECT count(*) FROM r"}) {
    const auto result = crown::io::write_sql_parse(parse_sql(text));
    check(result.at("syntax_valid") == true && result.at("admission_status") == "not_checked", "syntax alone confers no SQL semantics/admission");
  }
}
void encoding_and_locations() {
  const std::string text = "SELECT 'é',\n FROM t";
  const auto result = parse_sql(text);
  const auto& diagnostic = failure(result, "sql_syntax_error");
  check(diagnostic.byte_offset == text.find("FROM"), "Unicode cursor maps to byte offset");
  check(diagnostic.character_position == text.find("FROM"), "one-based character position accounts for extra UTF-8 byte");
  check(diagnostic.line == 2 && diagnostic.column == 2, "line/Unicode column mapped from source");
  const auto end = parse_sql("SELECT (");
  check(failure(end, "sql_syntax_error").byte_offset == 8, "EOF error has offset at source end");
  const std::string embedded("SELECT 1\0; DELETE FROM r", 24);
  check(failure(parse_sql(embedded), "invalid_encoding").byte_offset == 8, "NUL never truncates input at C boundary");
  for (const auto& invalid : {std::string("\xc0\xaf", 2), std::string("\xed\xa0\x80", 3), std::string("\xf4\x90\x80\x80", 4),
                              std::string("\xe2\x82", 2), std::string("\x80", 1), std::string("\xc2x", 2)}) {
    const auto bad = parse_sql(invalid);
    const auto& error = failure(bad, "invalid_encoding");
    check(error.byte_offset.has_value() && !error.character_position && !error.line && !error.column, "invalid bytes have no invented Unicode coordinates");
  }
  for (const auto& valid : {"SELECT 'é'", "SELECT \"名\" FROM r", "SELECT '😀'", "-- \x7f\nSELECT 1"}) {
    static_cast<void>(syntax(parse_sql(valid)));
  }
  static_cast<void>(failure(parse_sql("SELECT 1", {7, 256}), "resource_limit"));
  static_cast<void>(syntax(parse_sql("SELECT 1", {8, 256})));
}
void concurrent_callers() {
  std::vector<std::thread> workers;
  std::vector<std::exception_ptr> errors(4);
  for (std::size_t worker = 0; worker < errors.size(); ++worker) {
    workers.emplace_back([worker, &errors] {
      try {
        for (std::size_t i = 0; i < 25; ++i) {
          static_cast<void>(syntax(parse_sql("SELECT 1")));
          static_cast<void>(failure(parse_sql("SELECT FROM"), "sql_syntax_error"));
        }
      } catch (...) { errors[worker] = std::current_exception(); }
    });
  }
  for (auto& worker : workers) worker.join();
  for (const auto& error : errors) if (error) std::rethrow_exception(error);
}
}  // namespace

int main() {
  try {
    ownership_and_boundaries();
    encoding_and_locations();
    concurrent_callers();
    std::cout << "SQL parser ownership, encoding, boundaries and locations passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
