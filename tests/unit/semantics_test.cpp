#include "crown/api/error.hpp"
#include "crown/io/document.hpp"
#include "evaluator.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
using namespace crown;
using crown::io::Json;
void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
void rejects(const std::function<void()>& action, const std::string& code) {
  try { action(); }
  catch (const Error& error) { check(error.code() == code, "wrong rejection: " + error.code() + " expected " + code); return; }
  throw std::runtime_error("expected rejection: " + code);
}
Value integer(std::int64_t value) { return Value{value}; }
Json input() {
  return Json::parse(R"({
    "schema_version":1,"semantics":"set",
    "catalog":{"version":1,"tables":[{"name":"R","columns":[{"name":"x","type":"int64"},{"name":"z","type":"int64"}]}]},
    "query":{"variables":[{"name":"x","type":"int64"},{"name":"z","type":"int64"}],
      "atoms":[{"id":"r","table":"R","terms":[{"var":"x"},{"var":"z"}]}],"head":[{"var":"x"}]}
  })");
}
void atomicity_and_ownership() {
  const auto document = io::read_document(input().dump());
  reference::Session session(document.catalog, document.query, document.initial);
  const auto first = session.apply({1, TableId{0}, SetOperation::insert, {integer(7), integer(1)}});
  const Relation answer{{integer(7)}};
  check(first.current == answer && first.delta.added == answer && first.delta.removed.empty(), "first support adds output");
  const auto second = session.apply({2, TableId{0}, SetOperation::insert, {integer(7), integer(2)}});
  check(second.input_changed && second.delta.added.empty() && second.delta.removed.empty(), "second witness has empty delta");
  rejects([&] { static_cast<void>(session.apply({4, TableId{0}, SetOperation::erase, {integer(7), integer(1)}})); }, "invalid_sequence");
  rejects([&] { static_cast<void>(session.apply({3, TableId{0}, SetOperation::erase, {std::string("7"), integer(1)}})); }, "invalid_update");
  rejects([&] { static_cast<void>(session.apply({3, TableId{0}, static_cast<SetOperation>(42), {integer(7), integer(1)}})); }, "invalid_update");
  check(session.sequence() == 2 && session.database().tables[0].size() == 2 && session.snapshot() == answer, "failed update is atomic");
  const auto duplicate = session.apply({3, TableId{0}, SetOperation::insert, {integer(7), integer(1)}});
  check(!duplicate.input_changed && duplicate.delta.added.empty() && duplicate.delta.removed.empty(), "duplicate insert no-op");
  static_cast<void>(session.apply({4, TableId{0}, SetOperation::erase, {integer(7), integer(1)}}));
  const auto last = session.apply({5, TableId{0}, SetOperation::erase, {integer(7), integer(2)}});
  check(last.current.empty() && last.delta.removed == answer, "last support removes output");
  check(first.current == answer && first.delta.added == answer, "prior epoch owns its output after later mutations");
  const auto absent = session.apply({6, TableId{0}, SetOperation::erase, {integer(7), integer(2)}});
  check(!absent.input_changed && absent.sequence == 6 && absent.current.empty(), "absent delete commits a no-op epoch");
}
void exact_values_and_roundtrip() {
  auto data = input();
  data["initial"] = Json::array({{{"table", "R"}, {"rows", {{std::numeric_limits<std::int64_t>::max(), std::numeric_limits<std::int64_t>::min()}, {9007199254740993LL, 0}}}}});
  data["query"]["head"] = Json::array({{{"var", "x"}, {"alias", "first"}}, {{"var", "x"}, {"alias", "again"}}});
  const auto document = io::read_document(data.dump());
  auto malformed = document;
  malformed.updates.push_back({2, TableId{0}, SetOperation::insert, {integer(1), integer(1)}});
  rejects([&] { static_cast<void>(io::write_document(malformed)); }, "invalid_sequence");
  malformed.updates[0].sequence = 1;
  malformed.updates[0].operation = static_cast<SetOperation>(42);
  rejects([&] { static_cast<void>(io::write_document(malformed)); }, "invalid_update");
  const auto canonical = io::write_document(document).dump();
  const auto copy = io::read_document(canonical);
  check(io::write_document(copy).dump() == canonical, "canonicalization is idempotent");
  check(copy.initial.tables == document.initial.tables, "exact integers survive roundtrip");
  const auto answer = reference::evaluate(copy.catalog, copy.query, copy.initial);
  check(answer.size() == 2 && answer.begin()->at(0) == integer(9007199254740993LL), "no double conversion above 2^53");
  check(answer.begin()->at(0) == answer.begin()->at(1), "repeated output positions preserved");
  check(copy.query.head[1].alias == "again", "output alias retained independently");

  data = input();
  data["catalog"]["tables"][0]["columns"][0]["type"] = "bool";
  data["catalog"]["tables"][0]["columns"][1]["type"] = "string";
  data["query"]["variables"][0]["type"] = "bool";
  data["query"]["variables"][1]["type"] = "string";
  data["query"]["head"].push_back({{"var", "z"}});
  data["initial"] = Json::array({{{"table", "R"}, {"rows", {{true, std::string("a\0b", 3)}, {false, "é"}}}}});
  const auto typed = io::read_document(data.dump());
  check(reference::evaluate(typed.catalog, typed.query, typed.initial).size() == 2, "bool and binary strings admitted without casts");
  check(std::get<std::string>(typed.initial.tables[0].rbegin()->at(1)).size() == 3, "embedded NUL bytes survive parsing");
}
void empty_and_wide_queries() {
  Catalog catalog;
  Query query;
  Database database;
  check(reference::evaluate(catalog, query, database) == Relation{Row{}}, "empty body is one nullary tuple");
  query.contradiction = true;
  check(reference::evaluate(catalog, query, database).empty(), "contradictory empty body is false");

  Table table{"wide", {}};
  Atom atom{"wide0", TableId{0}, {}};
  query = {};
  Row row;
  for (std::size_t i = 0; i < 70; ++i) {
    const auto name = "v" + std::to_string(i);
    table.columns.push_back({name, ScalarType::int64});
    query.variables.push_back({name, ScalarType::int64});
    atom.terms.emplace_back(VariableId{i});
    query.head.push_back({VariableId{i}, name});
    row.push_back(integer(static_cast<std::int64_t>(i)));
  }
  catalog.tables.push_back(std::move(table));
  query.atoms.push_back(std::move(atom));
  database.tables.push_back(Relation{row});
  check(reference::evaluate(catalog, query, database) == Relation{row}, "70 variables use dynamic storage");
}
void schema_rejections() {
  auto bad = input();
  const auto reject_document = [](const Json& value, const std::string& code) {
    rejects([&] { static_cast<void>(io::read_document(value.dump())); }, code);
  };
  bad["schema_version"] = 4; reject_document(bad, "unsupported_version");
  bad = input(); bad["schema_version"] = 1.0; reject_document(bad, "invalid_document");
  bad = input(); bad["semantics"] = "bag"; reject_document(bad, "unsupported_semantics");
  bad = input(); bad["unexpected"] = false; reject_document(bad, "invalid_document");
  bad = input(); bad["query"]["atoms"][0]["table"] = "missing"; reject_document(bad, "invalid_document");
  bad = input(); bad["query"]["atoms"].push_back(bad["query"]["atoms"][0]); reject_document(bad, "invalid_cq");
  bad = input(); bad["query"]["variables"][0]["type"] = "string"; reject_document(bad, "invalid_cq");
  bad = input(); bad["query"]["atoms"][0]["terms"][0] = {{"var", "x"}, {"const", 1}}; reject_document(bad, "invalid_document");
  bad = input(); bad["catalog"]["tables"][0]["columns"][0]["type"] = "decimal"; reject_document(bad, "unsupported_type");
  bad = input(); bad["initial"] = Json::array({{{"table", "R"}, {"rows", {{nullptr, 1}}}}}); reject_document(bad, "invalid_document");
  bad["initial"][0]["rows"][0][0] = 1.0; reject_document(bad, "invalid_document");
  bad["initial"][0]["rows"][0][0] = 9223372036854775808ULL; reject_document(bad, "invalid_document");
  bad["initial"][0]["rows"][0][0] = true; reject_document(bad, "invalid_update");
  bad = input(); bad["updates"] = Json::array({{{"schema_version", 1}, {"sequence", 2}, {"table", "R"}, {"op", "insert"}, {"values", {1, 2}}}}); reject_document(bad, "invalid_sequence");
  rejects([] { static_cast<void>(io::read_document("{\"schema_version\":1,\"schema_version\":1}")); }, "invalid_document");
  rejects([] { static_cast<void>(io::read_document("{\"x\":[]}")); }, "invalid_document");
  rejects([] { static_cast<void>(io::read_document("{")); }, "invalid_document");
  rejects([] { static_cast<void>(io::read_document("[]")); }, "invalid_document");
}
}  // namespace

int main() {
  try {
    atomicity_and_ownership();
    exact_values_and_roundtrip();
    empty_and_wide_queries();
    schema_rejections();
    std::cout << "exact semantics, epoch ownership, atomic failures and strict schema checks passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
