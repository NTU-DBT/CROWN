#include "crown/catalog/catalog.hpp"
#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/oracle.hpp"
#include "crown/planner/oracle.hpp"
#include "evaluator.hpp"

#include <functional>
#include <array>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
using io::Json;
void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
void rejects(const std::function<void()>& action, const std::string& code, const std::string& detail = "") {
  try { action(); }
  catch (const Error& error) {
    check(error.code() == code, "wrong rejection: " + error.code() + ", expected " + code + ": " + error.what());
    check(std::string(error.what()).find(detail) != std::string::npos, "diagnostic lacks " + detail);
    return;
  }
  throw std::runtime_error("expected rejection: " + code);
}
Value integer(std::int64_t value) { return Value{value}; }
Json input() {
  return Json::parse(R"({"schema_version":3,"semantics":"set",
    "catalog":{"version":9,"tables":[
      {"name":"P","columns":[{"name":"a","type":"int64"},{"name":"b","type":"int64"},{"name":"tag","type":"string"}],
       "source_schema_version":4,"constraints":[{"kind":"unique","name":"pk","columns":["a","b"],"status":"enforced"}]},
      {"name":"C","columns":[{"name":"b","type":"int64"},{"name":"a","type":"int64"},{"name":"w","type":"int64"}],
       "constraints":[{"kind":"foreign_key","name":"fk","columns":["b","a"],"status":"enforced","references":{"table":"P","columns":["b","a"]}}]}
    ]},
    "query":{"variables":[{"name":"a","type":"int64"},{"name":"b","type":"int64"}],
      "atoms":[{"id":"p","table":"P","terms":[{"var":"a"},{"var":"b"},{"ignore":true}]},
               {"id":"c","table":"C","terms":[{"var":"b"},{"var":"a"},{"ignore":true}]}],"head":[{"var":"a"}]},
    "initial":[{"table":"P","rows":[[1,2,"x"]]},{"table":"C","rows":[[2,1,10],[2,1,11]]}]})");
}
void constraints_and_atomicity() {
  const auto document = io::read_document(input().dump());
  reference::Session session(document.catalog, document.query, document.initial);
  const auto before = session.database().tables;
  const auto before_answer = session.snapshot();
  rejects([&] { static_cast<void>(session.apply({1, TableId{0}, SetOperation::erase, {integer(1), integer(2), std::string("x")}})); }, "constraint_violation", "C.fk");
  rejects([&] { static_cast<void>(session.apply({1, TableId{0}, SetOperation::insert, {integer(1), integer(2), std::string("different")}})); }, "constraint_violation", "P.pk");
  rejects([&] { static_cast<void>(session.apply({1, TableId{1}, SetOperation::insert, {integer(9), integer(8), integer(7)}})); }, "constraint_violation", "C.fk");
  check(session.sequence() == 0 && session.database().tables == before && session.snapshot() == before_answer,
        "all rejected constraint transitions preserve database, sequence and output");
  const auto duplicate = session.apply({1, TableId{0}, SetOperation::insert, {integer(1), integer(2), std::string("x")}});
  check(!duplicate.input_changed && duplicate.delta.added.empty() && duplicate.delta.removed.empty(), "duplicate full physical row remains a no-op under a unique key");
  const auto first = session.apply({2, TableId{1}, SetOperation::erase, {integer(2), integer(1), integer(10)}});
  check(first.input_changed && first.delta.removed.empty(), "one of two physical witnesses preserves projected membership");
  const auto last = session.apply({3, TableId{1}, SetOperation::erase, {integer(2), integer(1), integer(11)}});
  check(last.current.empty() && last.delta.removed == before_answer, "last witness removal changes result");
  const auto parent = session.apply({4, TableId{0}, SetOperation::erase, {integer(1), integer(2), std::string("x")}});
  check(parent.input_changed && parent.current.empty(), "referenced row becomes deletable after all children disappear");
  check(duplicate.current == before_answer, "owned output survives later constraint transitions");
  auto bad = input();
  bad["initial"][0]["rows"].push_back({1,2,"different"});
  rejects([&] { static_cast<void>(io::read_document(bad.dump())); }, "constraint_violation");
  bad = input(); bad["initial"][0]["rows"] = Json::array();
  rejects([&] { static_cast<void>(io::read_document(bad.dump())); }, "constraint_violation");

  auto untrusted = document;
  for (auto& table : untrusted.catalog.tables) for (auto& constraint : table.constraints) {
    std::visit([](auto& item) { item.status = ConstraintStatus::untrusted; }, constraint);
  }
  untrusted.catalog.tables[0].statistics.row_count = 0;
  untrusted.catalog.tables[0].statistics.distinct_counts = {{{ColumnId{0}}, 1}};
  untrusted.catalog.tables[0].key_hints = {{{ColumnId{0}}, "approximate guessed key"}};
  untrusted.initial.tables[0].insert({integer(1), integer(2), std::string("different")});
  untrusted.initial.tables[1].insert({integer(9), integer(8), integer(7)});
  reference::Session permissive(untrusted.catalog, untrusted.query, untrusted.initial);
  check(permissive.snapshot() == before_answer, "untrusted constraints, contradictory estimates and hints do not become facts");
  const auto canonical = io::write_document(untrusted);
  check(canonical.at("query").at("atoms").size() == 2, "metadata does not eliminate mutable atoms");
}
void self_reference_and_empty_keys() {
  Catalog catalog;
  Table node{"Node", {{"id", ScalarType::int64}, {"parent", ScalarType::int64}}};
  node.constraints.emplace_back(UniqueConstraint{"pk", {ColumnId{0}}, ConstraintStatus::enforced});
  node.constraints.emplace_back(ForeignKeyConstraint{"self", {ColumnId{1}}, TableId{0}, {ColumnId{0}}, ConstraintStatus::enforced});
  catalog.tables.push_back(node);
  Query query{{{"x", ScalarType::int64}, {"p", ScalarType::int64}}, {{"n", TableId{0}, {VariableId{0}, VariableId{1}}}}, {{VariableId{0}, "x"}}};
  reference::Session session(catalog, query, Database{{Relation{}}});
  const auto insertion = session.apply({1, TableId{0}, SetOperation::insert, {integer(1), integer(1)}});
  check(insertion.current == Relation{{integer(1)}}, "self-referencing row is checked against one atomic after-state");
  const auto deletion = session.apply({2, TableId{0}, SetOperation::erase, {integer(1), integer(1)}});
  check(deletion.current.empty(), "self-referencing row deletion checks proposed after-state");

  Table singleton{"One", {{"x", ScalarType::int64}}};
  singleton.constraints.emplace_back(UniqueConstraint{"at_most_one", {}, ConstraintStatus::enforced});
  Catalog one{1, {singleton}};
  validate_database(one, Database{{Relation{{integer(1)}}}});
  rejects([&] { validate_database(one, Database{{Relation{{integer(1)}, {integer(2)}}}}); }, "constraint_violation");
  Table exists{"Exists", {}};
  exists.constraints.emplace_back(ForeignKeyConstraint{"needs_one", {}, TableId{0}, {}, ConstraintStatus::enforced});
  one.tables.push_back(exists);
  validate_database(one, Database{{Relation{{integer(1)}}, Relation{Row{}}}});
  rejects([&] { validate_database(one, Database{{Relation{}, Relation{Row{}}}}); }, "constraint_violation");
}
void types_names_and_metadata() {
  const std::vector<ScalarType> kinds{ScalarType::int64, ScalarType::string, ScalarType::boolean, ScalarType::date, ScalarType::decimal};
  for (const auto from : kinds) for (const auto to : kinds) {
    if (from == to) catalog::require_identity_cast(from, to);
    else rejects([&] { catalog::require_identity_cast(from, to); }, "unsupported_cast");
  }
  Column fixed{"d", ScalarType::decimal, false, Collation::binary, DecimalSpec{4,2}};
  check(catalog::decimal_fits(Decimal::parse("99.99"), *fixed.decimal), "fixed-scale precision boundary");
  check(!catalog::decimal_fits(Decimal::parse("100"), *fixed.decimal) && !catalog::decimal_fits(Decimal::parse("0.001"), *fixed.decimal), "fixed-scale overflow never rounds");
  check(catalog::decimal_fits(Decimal::parse("0"), {38,38}) && !catalog::decimal_fits(Decimal::parse("1"), {38,38}), "zero and no-integer-digit decimal domain");
  const std::array<std::int64_t, 7> powers{1,10,100,1000,10000,100000,1000000};
  for (std::int64_t coefficient = -200; coefficient <= 200; ++coefficient) {
    for (std::size_t input_scale = 0; input_scale <= 3; ++input_scale) {
      auto spelling = std::to_string(coefficient < 0 ? -coefficient : coefficient);
      if (input_scale > 0) {
        if (spelling.size() <= input_scale) spelling.insert(0, input_scale + 1 - spelling.size(), '0');
        spelling.insert(spelling.size() - input_scale, ".");
      }
      if (coefficient < 0) spelling.insert(0, "-");
      const auto value = Decimal::parse(spelling);
      for (std::uint32_t precision = 1; precision <= 6; ++precision) {
        for (std::uint32_t scale = 0; scale <= precision; ++scale) {
          const auto numerator = coefficient * powers[scale];
          const auto denominator = powers[input_scale];
          const bool expected = numerator % denominator == 0 && numerator / denominator > -powers[precision] && numerator / denominator < powers[precision];
          check(catalog::decimal_fits(value, {precision,scale}) == expected,
                "fixed-decimal fit agrees with independent integer divisibility/range");
        }
      }
    }
  }
  auto changed_scale = fixed; changed_scale.decimal = DecimalSpec{5,3};
  rejects([&] { catalog::require_identity_cast(fixed, changed_scale); }, "unsupported_cast");
  auto changed_nullability = fixed; changed_nullability.nullable = true;
  rejects([&] { catalog::require_identity_cast(changed_nullability, fixed); }, "unsupported_nullability");
  rejects([&] { catalog::require_identity_cast(fixed, changed_nullability); }, "unsupported_nullability");
  catalog::require_identity_cast(fixed, fixed);
  auto invalid_spec = fixed; invalid_spec.decimal = DecimalSpec{1,2};
  rejects([&] { catalog::require_identity_cast(invalid_spec, invalid_spec); }, "invalid_catalog");
  Catalog metadata{1, {Table{"T", {fixed, {"text", ScalarType::string}}}}};
  validate_row(metadata, TableId{0}, {Decimal::parse("+001.200"), std::string("x")});
  rejects([&] { validate_row(metadata, TableId{0}, {Decimal::parse("100"), std::string("x")}); }, "scalar_overflow");
  Query constant{{}, {{"t", TableId{0}, {Value{Decimal::parse("0.001")}, IgnoredColumn{}}}}, {}};
  rejects([&] { validate(metadata, constant); }, "scalar_overflow");
  metadata.tables[0].columns[0].nullable = true;
  catalog::validate_catalog(metadata);
  rejects([&] { validate(metadata, Query{}); }, "unsupported_nullability", "T.d");
  check(io::read_catalog(io::write_catalog(metadata).dump()).tables[0].columns[0].nullable, "nullable source metadata can roundtrip without entering the core");
  metadata.tables[0].columns[0].nullable = false;
  metadata.tables[0].columns[1].collation = static_cast<Collation>(99);
  rejects([&] { catalog::validate_catalog(metadata); }, "unsupported_collation");

  const auto document = io::read_document(input().dump());
  const std::vector<catalog::RelationBinding> bindings{{TableId{0}, "left"}, {TableId{0}, "right"}};
  check(catalog::find_table(document.catalog, "P") == TableId{0}, "catalog table name resolves to typed ID");
  rejects([&] { static_cast<void>(catalog::find_table(document.catalog, "p")); }, "unknown_table");
  check(catalog::resolve_column(document.catalog, bindings, "right", "a") == catalog::ColumnReference{1,ColumnId{0}}, "self-join bindings retain different identities");
  rejects([&] { static_cast<void>(catalog::resolve_column(document.catalog, bindings, {}, "a")); }, "ambiguous_column", "left.a and right.a");
  rejects([&] { static_cast<void>(catalog::resolve_column(document.catalog, bindings, "P", "a")); }, "unknown_qualifier");
  rejects([&] { static_cast<void>(catalog::resolve_column(document.catalog, bindings, "left", "missing")); }, "unknown_column");
  const std::vector<catalog::RelationBinding> duplicate{{TableId{0}, "same"}, {TableId{1}, "same"}};
  rejects([&] { static_cast<void>(catalog::resolve_column(document.catalog, duplicate, {}, "a")); }, "duplicate_alias");
}
void codecs_and_binding() {
  const auto document = io::read_document(input().dump());
  const auto encoded = io::write_document(document);
  check(encoded.at("schema_version") == 3 && io::write_document(io::read_document(encoded.dump())).dump() == encoded.dump(), "CQ metadata roundtrip preserves deterministic v3");
  auto standalone = io::write_catalog(document.catalog);
  standalone["catalog"]["version"] = std::numeric_limits<std::uint64_t>::max();
  standalone["catalog"]["tables"][0]["source_schema_version"] = std::numeric_limits<std::uint64_t>::max();
  const auto wide_version = io::read_catalog(standalone.dump());
  check(io::write_catalog(wide_version).dump() == standalone.dump(), "catalog and source versions retain unsigned64 precision");
  auto old = document; old.schema_version = 2;
  rejects([&] { static_cast<void>(io::write_document(old)); }, "unsupported_version");
  rejects([] { static_cast<void>(io::read_catalog("{\"schema_version\":1,\"schema_version\":1}")); }, "invalid_document");
  auto bad = standalone; bad["catalog"]["tables"][0]["constraints"][0]["status"] = "trusted";
  rejects([&] { static_cast<void>(io::read_catalog(bad.dump())); }, "invalid_catalog");
  bad = standalone; bad["catalog"]["tables"][0]["columns"][0]["collation"] = "binary";
  rejects([&] { static_cast<void>(io::read_catalog(bad.dump())); }, "unsupported_collation");
  auto broken = document.catalog;
  std::get<UniqueConstraint>(broken.tables[0].constraints[0]).status = ConstraintStatus::untrusted;
  rejects([&] { catalog::validate_catalog(broken); }, "invalid_catalog", "enforced unique target");
  const auto optimum = planner::minimum_tree(document.catalog, document.query);
  check(optimum.certificate_verified, "catalog metadata does not replace structural proof replay");
  const auto certificate = io::write_oracle(optimum, document.catalog, document.query).at("certificate");
  check(certificate.at("query_binding").at("schema_version") == 3, "certificate preserves nondefault catalog metadata");
  static_cast<void>(io::read_height_certificate(certificate.dump(), document.catalog, document.query));
  auto changed = document.catalog; ++changed.tables[0].source_schema_version;
  rejects([&] { static_cast<void>(io::read_height_certificate(certificate.dump(), changed, document.query)); }, "certificate_binding");
}
}  // namespace
int main() {
  try {
    constraints_and_atomicity();
    self_reference_and_empty_keys();
    types_names_and_metadata();
    codecs_and_binding();
    std::cout << "Catalog typing, names, versions, provenance and atomic constraints passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
