#include "crown/api/error.hpp"
#include "crown/io/document.hpp"
#include "crown/io/oracle.hpp"
#include "crown/planner/oracle.hpp"
#include "evaluator.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using io::Json;
void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
void rejects(const std::function<void()>& action, const std::string& code) {
  try { action(); }
  catch (const Error& error) { check(error.code() == code, "wrong rejection: " + error.code() + ", expected " + code); return; }
  throw std::runtime_error("expected rejection: " + code);
}
void exact_decimals() {
  auto original = Decimal::parse("-12.3400");
  const auto transferred = std::move(original);
  check(original.to_string() == "-12.34" && original == transferred,
        "rvalue construction preserves canonical decimal values in both objects");
  Decimal assigned;
  assigned = std::move(original);
  check(assigned == original && value_hash(Value{assigned}) == value_hash(Value{original}),
        "rvalue assignment preserves scalar equality and hashing");
  for (const auto& spelling : {"0", "-0", "+000", "-0000.0000", "+0.000"}) {
    const auto value = Decimal::parse(spelling);
    check(value == Decimal{} && value.to_string() == "0", "unique zero representation");
  }
  check(Decimal::parse("+001.2300").to_string() == "1.23", "strip insignificant zeros without rounding");
  check(Decimal::parse("-000.0100").to_string() == "-0.01", "negative fractions retain sign and place");
  for (const auto& value : {"99999999999999999999999999999999999999", "-99999999999999999999999999999999999999",
                             "0.00000000000000000000000000000000000001", "-0.00000000000000000000000000000000000001"}) {
    check(Decimal::parse(value).to_string() == value, "38-digit/scale boundary is exact");
  }
  for (const auto& invalid : {"", "+", "-", ".1", "1.", "1e2", "NaN", "Infinity", " 1", "1 ", "1.2.3", "++1", "1_000"}) {
    rejects([&] { static_cast<void>(Decimal::parse(invalid)); }, "invalid_scalar");
  }
  for (const auto& overflow : {"100000000000000000000000000000000000000", "0.000000000000000000000000000000000000001"}) {
    rejects([&] { static_cast<void>(Decimal::parse(overflow)); }, "scalar_overflow");
  }
  const std::vector<std::string> order{"-100", "-9.999", "-1", "-0.1", "-0.00001", "0", "0.00001", "0.1", "1", "1.001", "1.01", "1.1", "2", "10", "100"};
  for (std::size_t i = 0; i < order.size(); ++i) {
    for (std::size_t j = 0; j < order.size(); ++j) {
      check((Decimal::parse(order[i]) <=> Decimal::parse(order[j])) == (i <=> j), "hand numeric order including zero/sign/exponents");
    }
  }

  // An independent bounded rational grid compares scaled int64 numerators,
  // rather than reusing the production decimal comparator or normalization.
  std::map<std::int64_t, Decimal> rational_order;
  std::set<Decimal> decimal_order;
  std::unordered_set<Value, ValueHash> hashed_values;
  for (std::int64_t coefficient = -250; coefficient <= 250; ++coefficient) {
    std::int64_t denominator = 1;
    for (std::size_t scale = 0; scale <= 3; ++scale) {
      const auto magnitude = coefficient < 0 ? -coefficient : coefficient;
      auto digits = std::to_string(magnitude);
      if (scale > 0) {
        if (digits.size() <= scale) digits.insert(0, scale + 1 - digits.size(), '0');
        digits.insert(digits.size() - scale, ".");
      }
      if (coefficient < 0) digits.insert(0, "-");
      const auto value = Decimal::parse(digits);
      const auto numerator = coefficient * (1000 / denominator);
      const auto [it, inserted] = rational_order.emplace(numerator, value);
      if (!inserted) {
        check(value == it->second && value_hash(Value{value}) == value_hash(Value{it->second}), "equal rational values compare/hash equally");
      }
      decimal_order.insert(value);
      hashed_values.insert(Value{value});
      denominator *= 10;
    }
  }
  check(decimal_order.size() == rational_order.size() && hashed_values.size() == rational_order.size(), "ordered and hashed decimal sets agree with rational equality");
  auto actual = decimal_order.begin();
  for (const auto& [numerator, expected] : rational_order) {
    static_cast<void>(numerator);
    check(actual != decimal_order.end() && *actual++ == expected, "numeric decimal order agrees with rational grid");
  }
}
void dates_and_hashes() {
  check(Date{}.to_string() == "1970-01-01" && Date::parse("1970-01-01").epoch_days() == 0, "date epoch convention");
  check(Date::parse("1969-12-31").epoch_days() == -1, "pre-epoch dates are signed");
  for (const auto& value : {"0001-01-01", "9999-12-31", "2000-02-29", "2024-02-29", "1900-03-01", "2026-11-05"}) {
    check(Date::parse(value).to_string() == value, "date range/leap roundtrip");
  }
  for (const auto& invalid : {"0000-01-01", "10000-01-01", "1900-02-29", "2023-02-29", "2024-04-31", "2024-13-01",
                             "2024-00-01", "2024-01-00", "2024-1-01", "2024-01-1", "infinity", "2024-01-01Z", " 2024-01-01"}) {
    rejects([&] { static_cast<void>(Date::parse(invalid)); }, "invalid_scalar");
  }
  check(Date::parse("0001-01-01") < Date{} && Date{} < Date::parse("9999-12-31"), "chronological date order");
  const std::vector<Value> values{std::int64_t{-1}, std::int64_t{0}, std::string("a\0b", 3), false, true,
                                Date::parse("1969-12-31"), Decimal::parse("1.20")};
  for (const auto& value : values) check(value_hash(value) == value_hash(Value{value}), "equal typed values hash consistently");
  check(type_of(values[5]) == ScalarType::date && type_of(values[6]) == ScalarType::decimal, "new types cannot fall through to bool");
  const Row left{Decimal::parse("+001.200"), Date::parse("2024-02-29")};
  const Row right{Decimal::parse("1.2"), Date::parse("2024-02-29")};
  check(left == right && row_hash(left) == row_hash(right), "typed row equality/hash consistency");
  const std::unordered_set<Row, RowHash> rows{left, right};
  check(rows.size() == 1, "hash keys collapse exact aliases");
  rejects([] { static_cast<void>(type_name(static_cast<ScalarType>(99))); }, "invalid_cq");
}
Json document_json() {
  return Json::parse(R"({"schema_version":2,"semantics":"set",
    "catalog":{"version":7,"tables":[{"name":"R","columns":[{"name":"d","type":"decimal"},{"name":"day","type":"date"},{"name":"hidden","type":"int64"}]}]},
    "query":{"variables":[{"name":"d","type":"decimal"},{"name":"day","type":"date"}],
      "atoms":[{"id":"r","table":"R","terms":[{"var":"d"},{"var":"day"},{"ignore":true}]}],"head":[{"var":"d"},{"var":"day"},{"var":"d"}]},
    "initial":[{"table":"R","rows":[[{"decimal":"+001.200"},{"date":"2024-02-29"},1],[{"decimal":"1.20"},{"date":"2024-02-29"},2]]}],
    "updates":[{"schema_version":2,"sequence":1,"table":"R","op":"delete","values":[{"decimal":"1.2000"},{"date":"2024-02-29"},1]},
      {"schema_version":2,"sequence":2,"table":"R","op":"delete","values":[{"decimal":"1.2"},{"date":"2024-02-29"},2]}]})");
}
void codecs_and_reference() {
  const auto document = io::read_document(document_json().dump());
  const auto canonical = io::write_document(document).dump();
  check(io::read_document(canonical).schema_version == 2 && io::write_document(io::read_document(canonical)).dump() == canonical, "v2 preserves format and exact scalar semantics");
  check(canonical.find("+001.200") == std::string::npos, "canonical decimal encoding");
  reference::Session session(document.catalog, document.query, document.initial);
  check(session.snapshot().size() == 1 && session.snapshot().begin()->size() == 3, "hidden physical witnesses and repeated outputs");
  const auto first = session.apply(document.updates[0]);
  check(first.input_changed && first.delta.removed.empty() && first.current.size() == 1, "one decimal/date witness deletion preserves output");
  const auto last = session.apply(document.updates[1]);
  check(last.current.empty() && last.delta.removed.size() == 1, "last exact scalar witness removes output");
  check(first.current.size() == 1, "owned typed output survives later update");
  auto invalid = document;
  invalid.schema_version = 1;
  rejects([&] { static_cast<void>(io::write_document(invalid)); }, "unsupported_version");
  auto json = document_json();
  json["schema_version"] = 1;
  rejects([&] { static_cast<void>(io::read_document(json.dump())); }, "unsupported_type");
  json = document_json();
  json["updates"][0]["schema_version"] = 1;
  rejects([&] { static_cast<void>(io::read_document(json.dump())); }, "unsupported_version");
  json = document_json();
  json["initial"][0]["rows"][0][0] = "1.2";
  rejects([&] { static_cast<void>(io::read_document(json.dump())); }, "invalid_update");

  // Structural math is type-agnostic, but its exact certificate binding must
  // retain typed schema content and must reject a date/decimal change.
  const auto optimum = planner::minimum_tree(document.catalog, document.query);
  check(optimum.certificate_verified && optimum.minimum_height == 1, "typed CQ structural optimum is checked");
  const auto certificate_json = io::write_oracle(optimum, document.catalog, document.query).at("certificate");
  check(certificate_json.at("query_binding").at("schema_version") == 2, "typed certificate uses v2 query binding");
  const auto certificate = io::read_height_certificate(certificate_json.dump(), document.catalog, document.query);
  check(planner::verify_height_certificate(document.catalog, document.query, certificate).valid, "v2 certificate binding roundtrip/replay");
}
}  // namespace

int main() {
  try {
    exact_decimals();
    dates_and_hashes();
    codecs_and_reference();
    std::cout << "Exact scalar comparison, hashing, codecs and reference updates passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
