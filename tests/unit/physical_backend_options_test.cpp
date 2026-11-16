#include "crown/api/error.hpp"
#include "crown/io/physical.hpp"
#include "crown/ir/physical.hpp"
#include "crown/storage/backend.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>

namespace {
using crown::PhysicalOptions;
using crown::io::Json;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

void expect_error(std::string_view text, const std::string& message) {
  try {
    static_cast<void>(crown::io::read_physical_options(text));
  } catch (const crown::Error&) {
    return;
  } catch (const std::exception& failure) {
    throw std::runtime_error(message + ": reader threw a non-Crown exception: " + failure.what());
  }
  throw std::runtime_error(message + ": expected crown::Error");
}

void expect_error(const std::string& text, const std::string& message) {
  expect_error(std::string_view{text}, message);
}

void expect_error(const Json& value, const std::string& message) {
  expect_error(value.dump(), message);
}

void replace_once(std::string& text, const std::string& needle, const std::string& replacement) {
  const auto position = text.find(needle);
  check(position != std::string::npos, "cannot find expected JSON fragment: " + needle);
  check(text.find(needle, position + needle.size()) == std::string::npos,
        "JSON fragment is ambiguous: " + needle);
  text.replace(position, needle.size(), replacement);
}

Json reference_v1_expected() {
  return Json{{"schema_version", 1},
              {"policy", {{"arithmetic", "exact-nonnull-v1"},
                          {"planner", "crown-tree-v1"},
                          {"optimization", "structural-height-v1"},
                          {"cost_model", "no-cost-v1"}}},
              {"limits", {{"work", 1000000}, {"identity_work", 1000000}}}};
}

void reference_options_keep_v1_bytes() {
  const PhysicalOptions defaults;
  check(!defaults.indexed_storage.has_value(), "default physical options select no indexed backend");

  // This is the frozen compact v1 object, with its exact historical defaults.
  const std::string expected_bytes =
      R"({"limits":{"identity_work":1000000,"work":1000000},"policy":{"arithmetic":"exact-nonnull-v1","cost_model":"no-cost-v1","optimization":"structural-height-v1","planner":"crown-tree-v1"},"schema_version":1})";
  const auto expected = reference_v1_expected();
  const auto encoded = crown::io::write_physical_options(defaults);
  check(encoded == expected, "reference options match the independently written v1 object");
  check(encoded.dump() == expected_bytes, "absent indexed storage preserves the exact historical v1 bytes");

  const auto decoded = crown::io::read_physical_options(expected_bytes);
  check(!decoded.indexed_storage.has_value(), "v1 options decode without selecting indexed storage");
  check(crown::io::write_physical_options(decoded).dump() == expected_bytes,
        "v1 options reserialize byte-for-byte with their frozen defaults");
}

constexpr std::uint64_t kAboveExactInteger = 9007199254740993ULL;
constexpr std::uint64_t kAboveExactInteger2 = 9007199254740995ULL;
constexpr std::uint64_t kAboveExactInteger3 = 9007199254740997ULL;
constexpr std::uint64_t kAboveExactInteger4 = 9007199254740999ULL;
constexpr std::uint64_t kMaxU64 = std::numeric_limits<std::uint64_t>::max();
constexpr std::size_t kMaxSize = std::numeric_limits<std::size_t>::max();
static_assert(sizeof(std::size_t) == sizeof(std::uint64_t), "this boundary test requires a 64-bit size_t host");

crown::storage::IndexedBackendSpec indexed_spec() {
  crown::storage::IndexedBackendSpec spec;
  spec.per_table = {
      std::size_t{0},
      static_cast<std::size_t>(kAboveExactInteger),
      kMaxSize,
      static_cast<std::size_t>(kAboveExactInteger2),
      std::size_t{0},
      std::size_t{17},
      kMaxSize,
      std::size_t{1},
      static_cast<std::size_t>(kAboveExactInteger4)};
  spec.per_operation = {kMaxU64, kAboveExactInteger, 0, kAboveExactInteger2, kMaxU64};
  return spec;
}

PhysicalOptions indexed_options() {
  PhysicalOptions options;
  options.policy = {"exact-nonnull-v1", "crown-tree-v77", "height-policy-v4", "cost-model-v2"};
  options.limits.work_limit = kAboveExactInteger3;
  options.limits.identity.work_limit = 29;
  options.indexed_storage = indexed_spec();
  return options;
}

Json indexed_expected() {
  // Keep this oracle independent of write_physical_options and of the spec encoder.
  return Json{
      {"schema_version", 2},
      {"policy", {{"arithmetic", "exact-nonnull-v1"},
                  {"planner", "crown-tree-v77"},
                  {"optimization", "height-policy-v4"},
                  {"cost_model", "cost-model-v2"}}},
      {"limits", {{"work", kAboveExactInteger3}, {"identity_work", 29}}},
      {"indexed_storage", {
          {"algorithm", "indexed_chained_v1"},
          {"traversal", "insertion_first_live_key_v1"},
          {"component_scope", "per_table_including_undo"},
          {"work_scope", "operation_aggregate"},
          {"limits", {{"rows", std::uint64_t{0}},
                      {"indices", kAboveExactInteger},
                      {"keys", kMaxSize},
                      {"memberships", kAboveExactInteger2},
                      {"nodes", std::uint64_t{0}},
                      {"directory_slots", std::uint64_t{17}},
                      {"arena_slots", kMaxSize},
                      {"arena_pins", std::uint64_t{1}},
                      {"journal_entries", kAboveExactInteger4}}},
          {"work", {{"structural_steps", kMaxU64},
                     {"scalar_fields", kAboveExactInteger},
                     {"scalar_bytes", std::uint64_t{0}},
                     {"pointer_slots", kAboveExactInteger2},
                     {"link_actions", kMaxU64}}}}}};
}

void indexed_options_round_trip_exactly() {
  const auto options = indexed_options();
  const auto expected = indexed_expected();
  const auto expected_bytes = expected.dump();

  const auto encoded = crown::io::write_physical_options(options);
  check(encoded == expected, "indexed options have the full independently specified schema-v2 object");
  check(encoded.dump() == expected_bytes, "indexed options serialize in canonical JSON form");

  const auto decoded = crown::io::read_physical_options(expected_bytes);
  check(decoded.policy.arithmetic == options.policy.arithmetic &&
            decoded.policy.planner == options.policy.planner &&
            decoded.policy.optimization == options.policy.optimization &&
            decoded.policy.cost_model == options.policy.cost_model,
        "schema v2 retains all policy values");
  check(decoded.limits.work_limit == options.limits.work_limit &&
            decoded.limits.identity.work_limit == options.limits.identity.work_limit,
        "schema v2 retains both physical work limits exactly");
  check(decoded.indexed_storage.has_value(), "schema v2 restores its required indexed specification");
  const auto wanted = indexed_spec();
  const auto& actual = *decoded.indexed_storage;
  check(actual.per_table == wanted.per_table && actual.per_operation == wanted.per_operation,
        "indexed limits and operation work survive the round trip exactly");
  check(crown::io::write_physical_options(decoded).dump() == expected_bytes,
        "indexed options reserialize to the exact canonical bytes, including values above 2^53 and u64 maxima");
}

void strict_schema_rejects_unknown_missing_and_wrong_fields() {
  const auto valid = indexed_expected();

  auto unknown_version = valid;
  unknown_version["schema_version"] = 99;
  expect_error(unknown_version, "unknown schema version is rejected");

  auto schema_one_with_indexed = valid;
  schema_one_with_indexed["schema_version"] = 1;
  expect_error(schema_one_with_indexed, "schema v1 rejects indexed_storage");

  auto missing_indexed = valid;
  missing_indexed.erase("indexed_storage");
  expect_error(missing_indexed, "schema v2 requires indexed_storage");

  auto null_indexed = valid;
  null_indexed["indexed_storage"] = nullptr;
  expect_error(null_indexed, "schema v2 rejects null indexed_storage");

  const std::array<std::string_view, 4> root_fields{
      "schema_version", "policy", "limits", "indexed_storage"};
  for (const auto field : root_fields) {
    auto missing = valid;
    missing.erase(std::string(field));
    expect_error(missing, "missing root field is rejected: " + std::string(field));
    auto unknown = valid;
    unknown["unexpected_root"] = true;
    expect_error(unknown, "unknown root field is rejected");
  }

  const std::array<std::string_view, 4> policy_fields{
      "arithmetic", "planner", "optimization", "cost_model"};
  for (const auto field : policy_fields) {
    auto missing = valid;
    missing["policy"].erase(std::string(field));
    expect_error(missing, "missing policy field is rejected: " + std::string(field));
  }
  {
    auto unknown = valid;
    unknown["policy"]["unexpected_policy"] = "value";
    expect_error(unknown, "unknown policy field is rejected");
  }

  const std::array<std::string_view, 2> option_limit_fields{"work", "identity_work"};
  for (const auto field : option_limit_fields) {
    auto missing = valid;
    missing["limits"].erase(std::string(field));
    expect_error(missing, "missing physical limit is rejected: " + std::string(field));
  }
  {
    auto unknown = valid;
    unknown["limits"]["unexpected_limit"] = 1;
    expect_error(unknown, "unknown physical limit is rejected");
  }

  const std::array<std::string_view, 6> indexed_fields{
      "algorithm", "traversal", "component_scope", "work_scope", "limits", "work"};
  for (const auto field : indexed_fields) {
    auto missing = valid;
    missing["indexed_storage"].erase(std::string(field));
    expect_error(missing, "missing indexed_storage field is rejected: " + std::string(field));
    auto unknown = valid;
    unknown["indexed_storage"]["unexpected_indexed_field"] = 1;
    expect_error(unknown, "unknown indexed_storage field is rejected");
  }

  for (const auto field : {std::string_view{"algorithm"}, std::string_view{"traversal"},
                           std::string_view{"component_scope"}, std::string_view{"work_scope"}}) {
    auto wrong_tag = valid;
    wrong_tag["indexed_storage"][std::string(field)] = "wrong-tag";
    expect_error(wrong_tag, "unknown indexed tag is rejected: " + std::string(field));
  }

  const std::array<std::string_view, 9> table_limit_fields{
      "rows", "indices", "keys", "memberships", "nodes", "directory_slots", "arena_slots",
      "arena_pins", "journal_entries"};
  for (const auto field : table_limit_fields) {
    auto missing = valid;
    missing["indexed_storage"]["limits"].erase(std::string(field));
    expect_error(missing, "missing per-table limit is rejected: " + std::string(field));
  }
  {
    auto unknown = valid;
    unknown["indexed_storage"]["limits"]["unexpected_component"] = 1;
    expect_error(unknown, "unknown per-table limit is rejected");
  }

  const std::array<std::string_view, 5> work_fields{
      "structural_steps", "scalar_fields", "scalar_bytes", "pointer_slots", "link_actions"};
  for (const auto field : work_fields) {
    auto missing = valid;
    missing["indexed_storage"]["work"].erase(std::string(field));
    expect_error(missing, "missing operation work field is rejected: " + std::string(field));
  }
  {
    auto unknown = valid;
    unknown["indexed_storage"]["work"]["unexpected_work"] = 1;
    expect_error(unknown, "unknown operation work field is rejected");
  }
}

void indexed_numbers_must_be_unsigned_integer_u64_values() {
  const auto valid = indexed_expected();
  const std::array<Json, 6> invalid_numbers{
      Json(-1), Json(1.25), Json(1.0), Json(false), Json(nullptr), Json("1")};
  const std::array<std::string_view, 9> table_limit_fields{
      "rows", "indices", "keys", "memberships", "nodes", "directory_slots", "arena_slots",
      "arena_pins", "journal_entries"};
  const std::array<std::string_view, 5> work_fields{
      "structural_steps", "scalar_fields", "scalar_bytes", "pointer_slots", "link_actions"};

  for (const auto field : table_limit_fields) {
    for (const auto& invalid : invalid_numbers) {
      auto changed = valid;
      changed["indexed_storage"]["limits"][std::string(field)] = invalid;
      expect_error(changed, "per-table field must be a nonnegative integer u64: " + std::string(field));
    }
  }
  for (const auto field : work_fields) {
    for (const auto& invalid : invalid_numbers) {
      auto changed = valid;
      changed["indexed_storage"]["work"][std::string(field)] = invalid;
      expect_error(changed, "work field must be a nonnegative integer u64: " + std::string(field));
    }
  }

  const std::string overflow = "18446744073709551616";
  for (const auto field : table_limit_fields) {
    auto changed = valid;
    changed["indexed_storage"]["limits"][std::string(field)] = 0;
    auto text = changed.dump();
    replace_once(text, "\"" + std::string(field) + "\":0", "\"" + std::string(field) + "\":" + overflow);
    expect_error(text, "per-table field above u64 max is rejected: " + std::string(field));
  }
  for (const auto field : work_fields) {
    auto changed = valid;
    changed["indexed_storage"]["work"][std::string(field)] = 0;
    auto text = changed.dump();
    replace_once(text, "\"" + std::string(field) + "\":0", "\"" + std::string(field) + "\":" + overflow);
    expect_error(text, "work field above u64 max is rejected: " + std::string(field));
  }
}

void duplicate_object_keys_are_rejected() {
  auto root_duplicate = indexed_expected().dump();
  replace_once(root_duplicate, "\"schema_version\":2",
               "\"schema_version\":2,\"schema_version\":2");
  expect_error(root_duplicate, "duplicate root member is rejected");

  auto nested_duplicate = indexed_expected().dump();
  replace_once(nested_duplicate, "\"rows\":0", "\"rows\":0,\"rows\":0");
  expect_error(nested_duplicate, "duplicate nested indexed limit is rejected");
}

}  // namespace

int main() {
  try {
    reference_options_keep_v1_bytes();
    indexed_options_round_trip_exactly();
    strict_schema_rejects_unknown_missing_and_wrong_fields();
    indexed_numbers_must_be_unsigned_integer_u64_values();
    duplicate_object_keys_are_rejected();
    std::cout << "physical backend options codec checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
