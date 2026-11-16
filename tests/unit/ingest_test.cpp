#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include "crown/io/ingest.hpp"
#include "crown/ir/digest.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/replay.hpp"
#include "evaluator.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using io::InputEvent;
using io::InputFormat;
using io::InputOptions;
using io::InputProgress;
using io::Json;
using SignedRow = std::pair<SetOperation, Row>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void rejects(Action&& action, std::string_view label) {
  try {
    action();
  } catch (const Error&) {
    return;
  }
  throw std::runtime_error("expected rejection: " + std::string(label));
}

template <class Action>
void rejects_code(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error " + std::string(code));
}

Catalog typed_catalog() {
  return {41, {{"Typed", {{"id", ScalarType::int64},
                           {"text", ScalarType::string},
                           {"enabled", ScalarType::boolean},
                           {"day", ScalarType::date},
                           {"amount", ScalarType::decimal}},
                   7}}};
}

Catalog fingerprint_catalog() {
  Table parent{"Parent \"雪\\root\n", {
      {"id", ScalarType::int64},
      {"label\"候補", ScalarType::string, true},
      {"active", ScalarType::boolean},
      {"day", ScalarType::date},
      {"amount", ScalarType::decimal, false, Collation::binary, DecimalSpec{12, 2}}}};
  parent.source_schema_version = 8;
  parent.constraints.emplace_back(UniqueConstraint{
      "pk \"雪\\id", {ColumnId{0}}, ConstraintStatus::enforced});
  parent.statistics.row_count = 17;
  parent.statistics.distinct_counts.push_back({{ColumnId{0}}, 17});
  parent.key_hints.push_back(
      {{ColumnId{0}}, "estimated \"key\" \\ 候補\nfrom source"});

  Table child{"Child\\branch \"行\"", {
      {"id", ScalarType::int64},
      {"parent_id", ScalarType::int64},
      {"note 雪", ScalarType::string, true}}};
  child.source_schema_version = 9;
  child.constraints.emplace_back(UniqueConstraint{
      "child_pk", {ColumnId{0}}, ConstraintStatus::enforced});
  child.constraints.emplace_back(ForeignKeyConstraint{
      "fk \"parent\" 雪", {ColumnId{1}}, TableId{0}, {ColumnId{0}},
      ConstraintStatus::enforced});
  child.statistics.row_count = 11;
  child.statistics.distinct_counts.push_back({{ColumnId{1}}, 9});
  child.key_hints.push_back({{ColumnId{0}}, "observed \\ key \"hint\" 雪"});

  return {73, {std::move(parent), std::move(child)}};
}

Row typed_row(std::int64_t id, std::string text, bool enabled, Date day,
              Decimal amount) {
  return {id, std::move(text), enabled, day, amount};
}

InputEvent event(std::uint64_t sequence,
                 Row values,
                 SetOperation operation = SetOperation::insert,
                 std::optional<io::SourcePosition> position = std::nullopt) {
  return {PhysicalSetUpdate{sequence, TableId{0}, operation, std::move(values)},
          std::move(position)};
}

std::string json_line(const Catalog& catalog, std::uint64_t sequence,
                      Row values,
                      SetOperation operation = SetOperation::insert,
                      std::optional<io::SourcePosition> position = std::nullopt) {
  return io::write_input_json(event(sequence, std::move(values),
                                    operation, std::move(position)), catalog);
}

void append_le(std::string& out, std::uint64_t value, std::size_t bytes) {
  for (std::size_t i = 0; i < bytes; ++i) {
    out.push_back(static_cast<char>(value & 0xff));
    value >>= 8;
  }
}

void append_bytes(std::string& out, std::string_view value) {
  out.append(value.data(), value.size());
}

void append_string(std::string& out, std::string_view value) {
  check(value.size() <= std::numeric_limits<std::uint32_t>::max(),
        "golden binary fixture string is too large");
  append_le(out, value.size(), 4);
  append_bytes(out, value);
}

void append_binary_value(std::string& out, const Value& value) {
  if (const auto* integer = std::get_if<std::int64_t>(&value)) {
    out.push_back('\0');
    append_le(out, static_cast<std::uint64_t>(*integer), 8);
  } else if (const auto* text = std::get_if<std::string>(&value)) {
    out.push_back('\1');
    append_string(out, *text);
  } else if (const auto* boolean = std::get_if<bool>(&value)) {
    out.push_back('\2');
    out.push_back(*boolean ? '\1' : '\0');
  } else if (const auto* date = std::get_if<Date>(&value)) {
    out.push_back('\3');
    append_bytes(out, date->to_string());
  } else {
    out.push_back('\4');
    append_string(out, std::get<Decimal>(value).to_string());
  }
}

std::string golden_binary(const InputEvent& input, const Catalog& catalog) {
  std::string payload;
  append_le(payload, catalog.version, 8);
  append_le(payload, catalog.tables.at(input.update.table.value).source_schema_version,
            8);
  append_bytes(payload, io::input_catalog_sha256(catalog));
  append_le(payload, input.update.sequence, 8);
  append_string(payload, catalog.tables.at(input.update.table.value).name);
  payload.push_back(input.update.operation == SetOperation::insert ? '\1' : '\2');
  payload.push_back(input.source_position ? '\1' : '\0');
  if (input.source_position) {
    append_string(payload, input.source_position->source);
    append_le(payload, input.source_position->offset, 8);
  }
  append_le(payload, input.update.values.size(), 4);
  for (const auto& value : input.update.values) append_binary_value(payload, value);

  std::string frame("CROWNUPD", 8);
  append_le(frame, 1, 2);
  append_le(frame, payload.size(), 4);
  append_bytes(frame, payload);
  return frame;
}

bool same_event(const auto& left, const InputEvent& right) {
  return left.update.sequence == right.update.sequence &&
      left.update.table == right.update.table &&
      left.update.operation == right.update.operation &&
      left.update.values == right.update.values &&
      left.source_position == right.source_position;
}

void json_contract_and_typed_scalars() {
  const auto catalog = typed_catalog();
  const auto hash = io::input_catalog_sha256(catalog);
  check(hash.size() == 64 &&
            hash.find_first_not_of("0123456789abcdef") == std::string::npos,
        "input catalog binding is a lowercase SHA-256 digest");

  // This is a hand-authored JSONL record. It checks the public spelling and
  // F01's typed representations independently of the writer.
  const std::string raw =
      std::string(R"({"schema_version":1,"catalog_version":41,"source_schema_version":7,"catalog_sha256":")") +
      hash +
      R"(","sequence":1,"table":"Typed","operation":"insert","values":[9223372036854775807,"A\u0000B",true,{"date":"0001-01-01"},{"decimal":"0.00000000000000000000000000000000000001"}],"source_position":{"source":"源.csv","offset":18446744073709551615}})";
  const auto decoded = io::read_input_json(raw, catalog);
  const auto expected = event(1,
      typed_row(std::numeric_limits<std::int64_t>::max(),
                std::string("A\0B", 3), true, Date::parse("0001-01-01"),
                Decimal::parse("0.00000000000000000000000000000000000001")),
      SetOperation::insert,
      io::SourcePosition{"源.csv", std::numeric_limits<std::uint64_t>::max()});
  check(same_event(decoded, expected),
        "raw JSON preserves int64, embedded NUL, Unicode position, date, decimal and uint64 maximum");

  const auto canonical = io::write_input_json(decoded, catalog);
  const auto reread = io::read_input_json(canonical, catalog);
  check(same_event(decoded, reread),
        "JSON writer canonical output decodes to the same exact physical event");
  check(canonical.find("\\u0000") != std::string::npos &&
            canonical.find("0.00000000000000000000000000000000000001") !=
                std::string::npos,
        "JSON writer keeps embedded NUL escaped and decimal exact");
  io::InputLimits four_columns;
  four_columns.columns = 4;
  rejects([&] { static_cast<void>(io::read_input_json(raw, catalog, four_columns)); },
          "physical column limit");

  const auto max_decimal = Decimal::parse(
      "99999999999999999999999999999999999999");
  const auto min_scale = Decimal::parse(
      "0.00000000000000000000000000000000000001");
  check(max_decimal.to_string() ==
            "99999999999999999999999999999999999999" &&
            min_scale.to_string() ==
                "0.00000000000000000000000000000000000001",
        "decimal domain boundaries remain exact at 38 digits and scale");

  auto bad = Json::parse(raw);
  bad["catalog_version"] = 40;
  rejects([&] { static_cast<void>(io::read_input_json(bad.dump(), catalog)); },
          "catalog version mismatch");
  bad = Json::parse(raw);
  bad["source_schema_version"] = 6;
  rejects([&] { static_cast<void>(io::read_input_json(bad.dump(), catalog)); },
          "source schema mismatch");
  bad = Json::parse(raw);
  bad["catalog_sha256"] = std::string(64, '0');
  rejects([&] { static_cast<void>(io::read_input_json(bad.dump(), catalog)); },
          "catalog digest mismatch");
  bad = Json::parse(raw);
  bad["table"] = "typed";
  rejects([&] { static_cast<void>(io::read_input_json(bad.dump(), catalog)); },
          "physical table names are exact");
  bad = Json::parse(raw);
  bad.erase("catalog_sha256");
  rejects([&] { static_cast<void>(io::read_input_json(bad.dump(), catalog)); },
          "catalog digest is required");
  bad = Json::parse(raw);
  bad["extra"] = true;
  rejects([&] { static_cast<void>(io::read_input_json(bad.dump(), catalog)); },
          "unknown JSON fields are rejected");
  rejects([&] {
    const auto duplicate =
        std::string(R"({"schema_version":1,"schema_version":1,"catalog_version":41,"source_schema_version":7,"catalog_sha256":")") +
        hash +
        R"(","sequence":1,"table":"Typed","operation":"insert","values":[1,"x",true,{"date":"2024-01-01"},{"decimal":"1"}]})";
    static_cast<void>(io::read_input_json(duplicate, catalog));
  }, "duplicate JSON fields are rejected");

  const std::vector<std::function<void(Json&)>> mutations{
      [](Json& value) { value["schema_version"] = 2; },
      [](Json& value) { value["sequence"] = 0; },
      [](Json& value) { value["sequence"] = -1; },
      [](Json& value) { value["sequence"] = 1.5; },
      [](Json& value) { value["operation"] = "erase"; },
      [](Json& value) { value["operation"] = "upsert"; },
      [](Json& value) { value["values"][0] = 1.5; },
      [](Json& value) { value["values"][0] = nullptr; },
      [](Json& value) { value["values"][0] = true; },
      [](Json& value) { value["values"][0] = std::uint64_t{9223372036854775808ULL}; },
      [](Json& value) { value["values"].erase(4); },
      [](Json& value) { value["values"][3] = Json{{"date", "1900-02-29"}}; },
      [](Json& value) { value["values"][4] = Json{{"decimal", "1e2"}}; },
      [](Json& value) { value["values"][4] = Json{{"decimal", "100000000000000000000000000000000000000"}}; },
      [](Json& value) { value["source_position"]["source"] = ""; },
      [](Json& value) { value["source_position"]["offset"] = -1; },
      [](Json& value) { value["source_position"]["other"] = 1; },
  };
  for (const auto& mutate : mutations) {
    auto invalid = Json::parse(raw);
    mutate(invalid);
    rejects([&] { static_cast<void>(io::read_input_json(invalid.dump(), catalog)); },
            "malformed typed JSON event");
  }
  rejects_code([&] {
    auto invalid = Json::parse(raw);
    invalid["operation"] = "*";
    static_cast<void>(io::read_input_json(invalid.dump(), catalog));
  }, "unsupported_input_operation");

  auto invalid_utf8 = expected;
  invalid_utf8.source_position = io::SourcePosition{std::string("\xc0\xaf", 2), 0};
  rejects([&] { static_cast<void>(io::write_input_json(invalid_utf8, catalog)); },
          "invalid UTF-8 source position");

  auto changed = catalog;
  ++changed.tables[0].source_schema_version;
  check(io::input_catalog_sha256(changed) != hash,
        "catalog binding includes per-table source schema versions");
}

void catalog_fingerprint_matches_existing_serializer() {
  const auto catalog = fingerprint_catalog();
  const auto serialized = io::write_catalog(catalog).dump();
  const auto expected = sha256(serialized);
  check(io::input_catalog_sha256(catalog) == expected,
        "input catalog fingerprint is exactly SHA-256 of the existing canonical catalog serializer");
  check(serialized.find("\\\"") != std::string::npos &&
            serialized.find("\\\\") != std::string::npos &&
            serialized.find("\\n") != std::string::npos &&
            serialized.find("雪") != std::string::npos &&
            serialized.find("foreign_key") != std::string::npos &&
            serialized.find("decimal") != std::string::npos &&
            serialized.find("distinct_counts") != std::string::npos &&
            serialized.find("key_hints") != std::string::npos,
        "fingerprint fixture exercises escaped Unicode metadata for every catalog feature");
}

void binary_golden_and_frames() {
  const auto catalog = typed_catalog();
  const auto input = event(9,
      typed_row(std::numeric_limits<std::int64_t>::min(),
                std::string("nul\0雪", 7), false, Date::parse("9999-12-31"),
                Decimal::parse("-0.00000000000000000000000000000000000001")),
      SetOperation::erase, io::SourcePosition{"feed", 0x0102030405060708ULL});
  const auto golden = golden_binary(input, catalog);
  const auto encoded = io::write_input_binary(input, catalog);
  check(encoded == golden,
        "binary writer matches independently assembled version-one frame bytes");
  const auto decoded = io::read_input_binary(golden, catalog);
  check(same_event(decoded, input),
        "manual binary frame preserves every F01 type, negative zero-free decimal, NUL and UTF-8");

  auto invalid = golden;
  invalid[0] = 'X';
  rejects([&] { static_cast<void>(io::read_input_binary(invalid, catalog)); },
          "binary magic");
  invalid = golden;
  invalid[8] = 2;
  rejects([&] { static_cast<void>(io::read_input_binary(invalid, catalog)); },
          "binary version");
  rejects([&] {
    static_cast<void>(io::read_input_binary(
        std::string_view(golden.data(), golden.size() - 1), catalog));
  }, "truncated binary frame");
  invalid = golden;
  const std::size_t payload = 14;
  const std::size_t operation = payload + 8 + 8 + 64 + 8 + 4 + 5;
  invalid[operation] = 3;
  rejects([&] { static_cast<void>(io::read_input_binary(invalid, catalog)); },
          "unknown binary operation tag");
  invalid = golden;
  const std::size_t has_position = operation + 1;
  invalid[has_position] = 2;
  rejects([&] { static_cast<void>(io::read_input_binary(invalid, catalog)); },
          "invalid binary position flag");
  invalid = golden;
  const std::size_t first_value = payload + 8 + 8 + 64 + 8 + 4 + 5 + 1 + 1 +
      4 + 4 + 8 + 4;
  const std::size_t boolean_value = first_value + 1 + 8 + 1 + 4 + 7 + 1;
  invalid[boolean_value] = 2;
  rejects([&] { static_cast<void>(io::read_input_binary(invalid, catalog)); },
          "binary bool payload is exactly zero or one");

  const auto first = io::write_input_binary(
      event(1, typed_row(1, "one", true, Date::parse("2020-01-01"),
                                 Decimal::parse("1")),
            SetOperation::insert, io::SourcePosition{"stream", 4}), catalog);
  const auto second = io::write_input_binary(
      event(2, typed_row(2, "two", false, Date::parse("2020-01-02"),
                                 Decimal::parse("2")),
            SetOperation::erase, io::SourcePosition{"stream", 10}), catalog);
  std::istringstream concatenated(first + second);
  InputOptions options;
  options.format = InputFormat::binary;
  io::EventReader reader(concatenated, catalog, options);
  reader.acknowledge();
  const auto* cached = reader.peek();
  check(cached && cached == reader.peek() && cached->update.sequence == 1,
        "binary reader caches one independently framed event across repeated peek");
  check(reader.records_read() == 1 && reader.bytes_read() == first.size() &&
            reader.progress().sequence == 0,
        "fully decoded cached binary record counts as read but not accepted");
  reader.acknowledge();
  check(reader.progress().sequence == 1 &&
            reader.progress().source_positions.at("stream") == 4,
        "acknowledgement alone advances sequence and source offset");
  const auto* next = reader.peek();
  check(next && next->update.sequence == 2 &&
            next->update.operation == SetOperation::erase &&
            next->source_position->offset == 10,
        "concatenated binary frames preserve gaps and delete operation");
  reader.acknowledge();
  check(reader.progress().sequence == 2 && reader.records_read() == 2 &&
            reader.bytes_read() == first.size() + second.size() &&
            reader.peek() == nullptr && !reader.failed(),
        "binary EOF follows the final acknowledged frame cleanly");
  reader.acknowledge();
  check(reader.progress().sequence == 2,
        "acknowledging without a cached record is an idempotent no-op");
}

void jsonl_progress_failures_and_limits() {
  const auto catalog = typed_catalog();
  const auto row = typed_row(1, "v", true, Date::parse("2024-02-29"),
                             Decimal::parse("1.20"));
  const auto line1 = json_line(catalog, 41, row, SetOperation::insert,
                               io::SourcePosition{"source-A", 3});
  const auto line2 = json_line(catalog, 42, row, SetOperation::erase,
                               io::SourcePosition{"source-A", 9});
  InputProgress initial;
  initial.sequence = 40;
  initial.source_positions.emplace("source-A", 1);
  std::istringstream stream(line1 + "\n" + line2 + "\n");
  io::EventReader reader(stream, catalog, {}, initial);
  reader.acknowledge();
  const auto* first = reader.peek();
  check(first && first == reader.peek() && first->update.sequence == 41 &&
            first->source_position->offset == 3,
        "JSONL starts at last accepted sequence plus one and permits position gaps");
  check(reader.progress() == initial && reader.records_read() == 1 &&
            reader.bytes_read() == line1.size() + 1,
        "peek reads without mutating accepted progress and counts consumed bytes");
  reader.acknowledge();
  check(reader.progress().sequence == 41 &&
            reader.progress().source_positions.at("source-A") == 3,
        "JSONL acknowledgement advances its source position");
  reader.acknowledge();
  check(reader.progress().sequence == 41,
        "second acknowledgement without a new peek does not skip input");
  const auto* second = reader.peek();
  check(second && second->update.sequence == 42 &&
            second->source_position->offset == 9,
        "next JSONL record follows the acknowledged sequence");
  reader.acknowledge();
  check(reader.peek() == nullptr && reader.records_read() == 2 &&
            reader.bytes_read() == line1.size() + line2.size() + 2,
        "JSONL reader reaches clean EOF with exact record and byte counts");

  std::istringstream independent_sources(
      json_line(catalog, 1, row, SetOperation::insert,
                io::SourcePosition{"source-A", 100}) + "\n" +
      json_line(catalog, 2, row, SetOperation::insert,
                io::SourcePosition{"source-B", 0}) + "\n");
  io::EventReader unordered_across_sources(independent_sources, catalog);
  check(unordered_across_sources.peek() != nullptr,
        "first independent source position is readable");
  unordered_across_sources.acknowledge();
  check(unordered_across_sources.peek() != nullptr,
        "another source may begin at a lower byte offset");
  unordered_across_sources.acknowledge();
  check(unordered_across_sources.progress().source_positions.at("source-A") == 100 &&
            unordered_across_sources.progress().source_positions.at("source-B") == 0,
        "offset ordering is tracked independently per source");

  std::istringstream skipped_sequence(
      json_line(catalog, 2, row) + "\n");
  io::EventReader skipped(skipped_sequence, catalog);
  rejects([&] { static_cast<void>(skipped.peek()); },
          "JSONL sequence must be contiguous from initial progress");

  const auto duplicate_offset =
      json_line(catalog, 1, row, SetOperation::insert,
                io::SourcePosition{"same", 5}) + "\n" +
      json_line(catalog, 2, row, SetOperation::insert,
                io::SourcePosition{"same", 5}) + "\n";
  std::istringstream decreasing(duplicate_offset);
  io::EventReader monotone(decreasing, catalog);
  check(monotone.peek() != nullptr, "first source position is readable");
  monotone.acknowledge();
  rejects([&] { static_cast<void>(monotone.peek()); },
          "source offsets must strictly increase");
  check(monotone.failed() && monotone.progress().sequence == 1 &&
            monotone.progress().source_positions.at("same") == 5,
        "non-increasing offset fails without changing accepted progress");
  rejects_code([&] { static_cast<void>(monotone.peek()); }, "input_failed");

  const auto valid = json_line(catalog, 1, row);
  std::istringstream tiny_record(valid + "\n");
  InputOptions tiny;
  tiny.limits.record_bytes = 8;
  io::EventReader bounded_record(tiny_record, catalog, tiny);
  rejects([&] { static_cast<void>(bounded_record.peek()); }, "record byte limit");
  check(bounded_record.failed() && bounded_record.records_read() == 0,
        "record limit fails before a malformed or oversized record is counted");

  std::istringstream tiny_field(valid + "\n");
  InputOptions field_limit;
  field_limit.limits.field_bytes = 2;
  io::EventReader bounded_field(tiny_field, catalog, field_limit);
  rejects([&] { static_cast<void>(bounded_field.peek()); }, "field byte limit");

  std::istringstream tiny_total(valid + "\n");
  InputOptions total_limit;
  total_limit.limits.total_bytes = 4;
  io::EventReader bounded_total(tiny_total, catalog, total_limit);
  rejects([&] { static_cast<void>(bounded_total.peek()); }, "total byte limit");

  std::istringstream no_records(valid + "\n");
  InputOptions record_count_limit;
  record_count_limit.limits.records = 0;
  io::EventReader bounded_records(no_records, catalog, record_count_limit);
  rejects([&] { static_cast<void>(bounded_records.peek()); }, "record count limit");

  InputProgress full_sources;
  full_sources.source_positions.emplace("old", 7);
  InputOptions source_count_limit;
  source_count_limit.limits.sources = 1;
  std::istringstream too_many_sources(
      json_line(catalog, 1, row, SetOperation::insert,
                io::SourcePosition{"new", 1}) + "\n");
  io::EventReader bounded_sources(too_many_sources, catalog, source_count_limit,
                                  full_sources);
  rejects([&] { static_cast<void>(bounded_sources.peek()); },
          "source-position map count limit");
  check(bounded_sources.progress() == full_sources,
        "source map limit does not alter accepted progress");

  InputOptions source_name_limit;
  source_name_limit.limits.source_bytes = 2;
  std::istringstream long_source(
      json_line(catalog, 1, row, SetOperation::insert,
                io::SourcePosition{"long", 1}) + "\n");
  io::EventReader bounded_source_name(long_source, catalog, source_name_limit);
  rejects([&] { static_cast<void>(bounded_source_name.peek()); },
          "source-name byte limit");

  InputProgress too_late;
  too_late.sequence = std::numeric_limits<std::uint64_t>::max() - 1;
  const auto last_line = json_line(catalog,
      std::numeric_limits<std::uint64_t>::max(), row);
  std::istringstream last_stream(last_line + "\n");
  io::EventReader last_reader(last_stream, catalog, {}, too_late);
  check(last_reader.peek() && last_reader.peek()->update.sequence ==
            std::numeric_limits<std::uint64_t>::max(),
        "maximum sequence can be accepted as the final representable event");
  last_reader.acknowledge();
  check(last_reader.peek() == nullptr &&
            last_reader.progress().sequence ==
                std::numeric_limits<std::uint64_t>::max(),
        "maximum accepted sequence can be followed by EOF");

  InputProgress at_maximum;
  at_maximum.sequence = std::numeric_limits<std::uint64_t>::max();
  std::istringstream overflow_stream(valid + "\n");
  io::EventReader overflow(overflow_stream, catalog, {}, at_maximum);
  rejects([&] { static_cast<void>(overflow.peek()); }, "sequence overflow");
  check(overflow.progress() == at_maximum,
        "a record after maximum sequence is rejected without wrapping");
}

void jsonl_object_budget_excludes_framing() {
  const auto catalog = typed_catalog();
  const auto values = typed_row(7, "budget", true, Date::parse("2024-02-29"),
                                Decimal::parse("12.34"));
  const auto input_event = event(1, values);
  const auto object = io::write_input_json(input_event, catalog);
  InputOptions exact;
  exact.format = InputFormat::jsonl;
  exact.limits.record_bytes = object.size();
  check(io::write_input_json(input_event, catalog, exact.limits) == object &&
            same_event(io::read_input_json(object, catalog, exact.limits), input_event),
        "standalone JSON object writer and reader accept an exactly-at-limit object");

  for (const std::string& terminator : {std::string("\n"), std::string("\r\n")}) {
    auto framed_options = exact;
    framed_options.limits.total_bytes = object.size() + terminator.size();
    std::istringstream framed(object + terminator);
    io::EventReader reader(framed, catalog, framed_options);
    const auto* decoded = reader.peek();
    check(decoded && same_event(*decoded, input_event) &&
              reader.records_read() == 1 &&
              reader.bytes_read() == object.size() + terminator.size(),
          "JSONL LF and CRLF terminators are excluded from object size but counted as raw bytes");
    reader.acknowledge();
    check(reader.peek() == nullptr &&
              reader.bytes_read() == object.size() + terminator.size(),
          "framed JSONL record reaches EOF at its exact raw total-byte limit");
  }

  io::InputLimits below = exact.limits;
  --below.record_bytes;
  rejects_code([&] { static_cast<void>(io::read_input_json(object, catalog, below)); },
               "resource_limit");
  rejects_code([&] { static_cast<void>(io::write_input_json(input_event, catalog, below)); },
               "resource_limit");
  InputOptions below_reader_options;
  below_reader_options.format = InputFormat::jsonl;
  below_reader_options.limits.record_bytes = below.record_bytes;
  std::istringstream below_reader_stream(object + "\n");
  io::EventReader below_reader(below_reader_stream, catalog, below_reader_options);
  rejects_code([&] { static_cast<void>(below_reader.peek()); }, "resource_limit");

  InputOptions raw_total = exact;
  raw_total.limits.total_bytes = object.size();
  std::istringstream framing_over_budget(object + "\n");
  io::EventReader total_limited(framing_over_budget, catalog, raw_total);
  rejects_code([&] { static_cast<void>(total_limited.peek()); }, "resource_limit");
  check(total_limited.failed() && total_limited.bytes_read() == object.size() &&
            total_limited.records_read() == 0,
        "total byte cap includes the LF framing byte even though record_bytes does not");
}

void nondefault_options_are_format_scoped() {
  const auto catalog = typed_catalog();
  using Configure = std::function<void(InputOptions&)>;
  const std::vector<Configure> wire_incompatibilities{
      [](InputOptions& options) { options.table = TableId{0}; },
      [](InputOptions& options) { options.source = "wire-source"; },
      [](InputOptions& options) { options.byte_offset = 1; },
      [](InputOptions& options) { options.null_token = "NULL"; },
      [](InputOptions& options) { options.relation_tokens.emplace("Typed", TableId{0}); },
      [](InputOptions& options) { options.delimiter = '|'; },
      [](InputOptions& options) { options.header = false; },
      [](InputOptions& options) { options.csv_operation = SetOperation::erase; },
  };
  for (const auto format : {InputFormat::jsonl, InputFormat::binary}) {
    for (const auto& configure : wire_incompatibilities) {
      InputOptions options;
      options.format = format;
      configure(options);
      std::istringstream empty;
      rejects_code([&] {
        io::EventReader reader(empty, catalog, options);
      }, "invalid_input_options");
    }
  }

  const std::vector<InputFormat> legacy_formats{
      InputFormat::legacy_signed, InputFormat::legacy_relations,
      InputFormat::legacy_insert_only, InputFormat::legacy_flags,
      InputFormat::legacy_timestamp_flags};
  for (const auto format : legacy_formats) {
    auto valid_base = [&] {
      InputOptions options;
      options.format = format;
      options.delimiter = '|';
      if (format == InputFormat::legacy_relations)
        options.relation_tokens.emplace("Typed", TableId{0});
      else
        options.table = TableId{0};
      if (format == InputFormat::legacy_timestamp_flags)
        options.source = "timestamp-source";
      return options;
    };
    auto header_disabled = valid_base();
    header_disabled.header = false;
    std::istringstream empty_header;
    rejects_code([&] {
      io::EventReader reader(empty_header, catalog, header_disabled);
    }, "invalid_input_options");

    auto delete_operation = valid_base();
    delete_operation.csv_operation = SetOperation::erase;
    std::istringstream empty_operation;
    rejects_code([&] {
      io::EventReader reader(empty_operation, catalog, delete_operation);
    }, "invalid_input_options");
  }

  for (const auto format : {InputFormat::csv, InputFormat::legacy_signed,
                            InputFormat::legacy_insert_only,
                            InputFormat::legacy_flags,
                            InputFormat::legacy_timestamp_flags}) {
    InputOptions options;
    options.format = format;
    options.table = TableId{0};
    options.relation_tokens.emplace("Typed", TableId{0});
    std::istringstream empty;
    rejects_code([&] {
      io::EventReader reader(empty, catalog, options);
    }, "invalid_input_options");
  }
  InputOptions relation_profile;
  relation_profile.format = InputFormat::legacy_relations;
  relation_profile.relation_tokens.emplace("Typed", TableId{0});
  std::istringstream no_relation_table;
  io::EventReader relations_accept_map(no_relation_table, catalog,
                                       relation_profile);
  check(relations_accept_map.peek() == nullptr,
        "relation-token mapping is the explicit legacy_relations option");
}

void timestamp_flag_legacy_profile() {
  const auto catalog = typed_catalog();
  const auto inserted = typed_row(1, "first", true, Date::parse("2024-01-01"),
                                  Decimal::parse("1.2"));
  const auto erased = typed_row(2, "second", false, Date::parse("2024-01-02"),
                                Decimal::parse("2.3"));
  std::istringstream stream(
      "100|1|1|first|true|2024-01-01|1.2\n"
      "101|0|2|second|false|2024-01-02|2.3\n");
  InputOptions options;
  options.format = InputFormat::legacy_timestamp_flags;
  options.table = TableId{0};
  options.delimiter = '|';
  options.source = "timestamp-feed";
  io::EventReader reader(stream, catalog, options);
  const auto* first = reader.peek();
  check(first && first->update.sequence == 1 &&
            first->update.operation == SetOperation::insert &&
            first->update.values == inserted &&
            first->source_position == io::SourcePosition{"timestamp-feed", 100},
        "timestamp/flag profile retains timestamp as source offset and flag 1 inserts");
  reader.acknowledge();
  const auto* second = reader.peek();
  check(second && second->update.sequence == 2 &&
            second->update.operation == SetOperation::erase &&
            second->update.values == erased &&
            second->source_position == io::SourcePosition{"timestamp-feed", 101},
        "timestamp/flag profile assigns contiguous sequence and flag 0 deletes");
  reader.acknowledge();
  check(reader.peek() == nullptr && reader.progress().sequence == 2 &&
            reader.progress().source_positions.at("timestamp-feed") == 101,
        "timestamp profile reaches EOF after the final accepted record");

  for (const auto& timestamp : {std::string("100"), std::string("99")}) {
    std::istringstream nonmonotone(
        "100|1|1|first|true|2024-01-01|1.2\n" + timestamp +
        "|0|2|second|false|2024-01-02|2.3\n");
    io::EventReader monotone(nonmonotone, catalog, options);
    check(monotone.peek() != nullptr,
          "first timestamped legacy record is available");
    monotone.acknowledge();
    rejects_code([&] { static_cast<void>(monotone.peek()); },
                 "invalid_source_position");
    check(monotone.failed() && monotone.progress().sequence == 1 &&
              monotone.progress().source_positions.at("timestamp-feed") == 100,
          "repeated or backward timestamps fail sticky without acknowledging");
    rejects_code([&] { static_cast<void>(monotone.peek()); }, "input_failed");
  }

  auto missing_source = options;
  missing_source.source.reset();
  std::istringstream source_required;
  rejects_code([&] {
    io::EventReader invalid(source_required, catalog, missing_source);
  }, "invalid_input_options");
  auto missing_table = options;
  missing_table.table.reset();
  std::istringstream table_required;
  rejects_code([&] {
    io::EventReader invalid(table_required, catalog, missing_table);
  }, "invalid_input_options");
}

void csv_and_legacy_profiles() {
  const auto catalog = typed_catalog();
  const std::string header = "day|enabled|text|id|amount\r\n";
  const std::string first_record =
      "2024-02-29|true|\"cell|line\n\"\"雪\"\"\"|+9223372036854775807|0.00000000000000000000000000000000000001\r\n";
  const std::string second_record =
      "2025-03-01|false||-9223372036854775808|-0.1\n";
  std::istringstream csv_stream(header + first_record + second_record);
  InputOptions csv;
  csv.format = InputFormat::csv;
  csv.table = TableId{0};
  csv.delimiter = '|';
  csv.csv_operation = SetOperation::erase;
  csv.source = "edges.csv";
  csv.byte_offset = 500;
  InputProgress csv_progress;
  csv_progress.sequence = 20;
  io::EventReader csv_reader(csv_stream, catalog, csv, csv_progress);
  const auto* csv_first = csv_reader.peek();
  check(csv_first && csv_first->update.sequence == 21 &&
            csv_first->update.operation == SetOperation::erase &&
            csv_first->update.values == typed_row(
                std::numeric_limits<std::int64_t>::max(),
                "cell|line\n\"雪\"", true, Date::parse("2024-02-29"),
                Decimal::parse("0.00000000000000000000000000000000000001")) &&
            csv_first->source_position ==
                io::SourcePosition{"edges.csv", 500 + header.size()},
        "CSV binds a permuted full header, quoted delimiter/newline and typed values");
  const auto second_offset = 500 + header.size() + first_record.size();
  csv_reader.acknowledge();
  const auto* csv_second = csv_reader.peek();
  check(csv_second && csv_second->update.sequence == 22 &&
            csv_second->update.values == typed_row(
                std::numeric_limits<std::int64_t>::min(), "", false,
                Date::parse("2025-03-01"), Decimal::parse("-0.1")) &&
            csv_second->source_position ==
                io::SourcePosition{"edges.csv", second_offset},
        "CSV empty string stays a string and CRLF/LF offsets use raw byte starts");
  csv_reader.acknowledge();
  check(csv_reader.peek() == nullptr && csv_reader.records_read() == 2,
        "CSV excludes its header from decoded data-record count");

  std::istringstream no_header("+9|\"x\"|true|2020-01-01|1.2\n");
  InputOptions canonical_order;
  canonical_order.format = InputFormat::csv;
  canonical_order.table = TableId{0};
  canonical_order.delimiter = '|';
  canonical_order.header = false;
  io::EventReader no_header_reader(no_header, catalog, canonical_order);
  const auto* no_header_event = no_header_reader.peek();
  check(no_header_event && no_header_event->update.values == typed_row(
            9, "x", true, Date::parse("2020-01-01"), Decimal::parse("1.2")),
        "headerless CSV uses canonical physical-column order and strict typed parsing");

  const auto legacy_values =
      "+|17|alpha|true|2024-01-01|0.1\n-|18|beta|false|2024-01-02|-0.2\n";
  std::istringstream signed_stream(legacy_values);
  InputOptions signed_options;
  signed_options.format = InputFormat::legacy_signed;
  signed_options.table = TableId{0};
  signed_options.delimiter = '|';
  signed_options.source = "legacy-feed";
  signed_options.byte_offset = 120;
  io::EventReader signed_reader(signed_stream, catalog, signed_options);
  const auto* signed_insert = signed_reader.peek();
  check(signed_insert && signed_insert->update.sequence == 1 &&
            signed_insert->update.operation == SetOperation::insert &&
            signed_insert->source_position ==
                io::SourcePosition{"legacy-feed", 120} &&
            signed_insert->update.values == typed_row(
                17, "alpha", true, Date::parse("2024-01-01"), Decimal::parse("0.1")),
        "explicit signed profile maps plus to insert");
  signed_reader.acknowledge();
  const auto* signed_delete = signed_reader.peek();
  check(signed_delete && signed_delete->update.sequence == 2 &&
            signed_delete->update.operation == SetOperation::erase &&
            signed_delete->source_position == io::SourcePosition{
                "legacy-feed", 120 + std::string("+|17|alpha|true|2024-01-01|0.1\n").size()} &&
            signed_delete->update.values == typed_row(
                18, "beta", false, Date::parse("2024-01-02"), Decimal::parse("-0.2")),
        "explicit signed profile maps minus to delete");

  std::istringstream relation_stream("+|typed|19|gamma|false|2024-01-03|0.3\n");
  InputOptions relation_options;
  relation_options.format = InputFormat::legacy_relations;
  relation_options.delimiter = '|';
  relation_options.relation_tokens.emplace("typed", TableId{0});
  io::EventReader relation_reader(relation_stream, catalog, relation_options);
  const auto* relation_event = relation_reader.peek();
  check(relation_event && relation_event->update.table == TableId{0} &&
            relation_event->update.operation == SetOperation::insert &&
            relation_event->update.values == typed_row(
                19, "gamma", false, Date::parse("2024-01-03"), Decimal::parse("0.3")),
        "explicit relation profile resolves only its configured physical token");
  std::istringstream unknown_relation("+|Typed|19|gamma|false|2024-01-03|0.3\n");
  io::EventReader unknown_relation_reader(unknown_relation, catalog, relation_options);
  rejects([&] { static_cast<void>(unknown_relation_reader.peek()); },
          "unmapped legacy relation token");

  std::istringstream insert_only_stream("20|delta|true|2024-01-04|0.4\n");
  InputOptions insert_only_options;
  insert_only_options.format = InputFormat::legacy_insert_only;
  insert_only_options.table = TableId{0};
  insert_only_options.delimiter = '|';
  io::EventReader insert_only_reader(insert_only_stream, catalog,
                                     insert_only_options);
  const auto* insert_only = insert_only_reader.peek();
  check(insert_only && insert_only->update.operation == SetOperation::insert &&
            insert_only->update.values == typed_row(
                20, "delta", true, Date::parse("2024-01-04"), Decimal::parse("0.4")),
        "explicit unsigned legacy profile means insert only");

  std::istringstream flags_stream(
      "1|21|epsilon|false|2024-01-05|0.5\n0|21|epsilon|false|2024-01-05|0.5\n");
  InputOptions flags_options;
  flags_options.format = InputFormat::legacy_flags;
  flags_options.table = TableId{0};
  flags_options.delimiter = '|';
  io::EventReader flags_reader(flags_stream, catalog, flags_options);
  const auto* flag_insert = flags_reader.peek();
  check(flag_insert && flag_insert->update.operation == SetOperation::insert,
        "legacy flag 1 denotes insert");
  flags_reader.acknowledge();
  const auto* flag_delete = flags_reader.peek();
  check(flag_delete && flag_delete->update.operation == SetOperation::erase,
        "legacy flag 0 denotes delete");

  std::istringstream wildcard("*|1|x|true|2024-01-01|1\n");
  io::EventReader wildcard_reader(wildcard, catalog, signed_options);
  rejects_code([&] { static_cast<void>(wildcard_reader.peek()); },
               "unsupported_input_control");
  std::istringstream bad_flag("2|1|x|true|2024-01-01|1\n");
  io::EventReader bad_flag_reader(bad_flag, catalog, flags_options);
  rejects_code([&] { static_cast<void>(bad_flag_reader.peek()); },
               "unsupported_input_operation");

  std::istringstream wrong_header("id|text\n1|x\n");
  io::EventReader wrong_header_reader(wrong_header, catalog, csv);
  rejects([&] { static_cast<void>(wrong_header_reader.peek()); },
          "CSV header must name every physical column");
  std::istringstream guessed_null("id|text|enabled|day|amount\n1|NULL|true|2024-01-01|1\n");
  io::EventReader null_word_reader(guessed_null, catalog, csv);
  const auto* null_word = null_word_reader.peek();
  check(null_word && std::get<std::string_view>(null_word->update.values[1]) == "NULL",
        "CSV does not guess a special SQL NULL spelling for strings");

  InputOptions semicolon_options = canonical_order;
  semicolon_options.delimiter = ';';
  std::istringstream semicolon("1;x;true;2020-01-01;1\n");
  io::EventReader semicolon_reader(semicolon, catalog, semicolon_options);
  const auto* semicolon_event = semicolon_reader.peek();
  check(semicolon_event && semicolon_event->update.values == typed_row(
            1, "x", true, Date::parse("2020-01-01"), Decimal::parse("1")),
        "explicit semicolon separator parses a complete typed CSV row");
  InputOptions tab_options = canonical_order;
  tab_options.delimiter = '\t';
  std::istringstream tabbed("2\ty\tfalse\t2020-01-02\t2\n");
  io::EventReader tab_reader(tabbed, catalog, tab_options);
  const auto* tab_event = tab_reader.peek();
  check(tab_event && tab_event->update.values == typed_row(
            2, "y", false, Date::parse("2020-01-02"), Decimal::parse("2")),
        "explicit tab separator parses a complete typed CSV row");
  for (const char forbidden : {'"', '\r', '\n', '\0', static_cast<char>(0xc2)}) {
    InputOptions invalid_delimiter = canonical_order;
    invalid_delimiter.delimiter = forbidden;
    std::istringstream forbidden_stream("1|x|true|2020-01-01|1\n");
    rejects_code([&] {
      io::EventReader unsupported(forbidden_stream, catalog, invalid_delimiter);
      static_cast<void>(unsupported.peek());
    }, "invalid_input_options");
  }
}

PhysicalPlan edge_self_join_plan() {
  const Catalog catalog{17, {{"Edge", {{"x", ScalarType::int64},
                                       {"y", ScalarType::int64},
                                       {"payload", ScalarType::string}}, 3}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}},
                    {{"left", TableId{0},
                      {VariableId{0}, VariableId{1}, IgnoredColumn{}}},
                     {"right", TableId{0},
                      {VariableId{1}, VariableId{2}, IgnoredColumn{}}}},
                    {{VariableId{0}, "x"}, {VariableId{1}, "y"},
                     {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"left", NodeKind::native, {VariableId{0}, VariableId{1}},
        {NodeId{1}}, 0, {}},
       {"right", NodeKind::native, {VariableId{1}, VariableId{2}},
        {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

Row edge(std::int64_t x, std::int64_t y, std::string payload) {
  return {x, y, std::move(payload)};
}

std::string edge_json_line(const Catalog& catalog, std::uint64_t sequence,
                           SetOperation operation, Row values) {
  return io::write_input_json(
      {PhysicalSetUpdate{sequence, TableId{0}, operation, std::move(values)},
       io::SourcePosition{"edge-feed", sequence * 11}}, catalog);
}

std::vector<Row> replay_rows() {
  return {edge(1, 2, "left-a"), edge(2, 3, "right-a"),
          edge(1, 2, "left-b"), edge(1, 2, "left-a"),
          edge(2, 3, "right-b"), edge(2, 3, "right-a"),
          edge(2, 3, "right-b"), edge(99, 100, "missing")};
}

std::vector<SetOperation> replay_operations() {
  return {SetOperation::insert, SetOperation::insert, SetOperation::insert,
          SetOperation::erase, SetOperation::insert, SetOperation::erase,
          SetOperation::erase, SetOperation::erase};
}

std::string replay_stream(const Catalog& catalog) {
  const auto rows = replay_rows();
  const auto operations = replay_operations();
  std::string contents;
  for (std::size_t i = 0; i < rows.size(); ++i) {
    contents += edge_json_line(catalog, i + 1, operations[i], rows[i]);
    contents.push_back('\n');
  }
  return contents;
}

void physical_replay_preserves_source_rows_and_counts() {
  const auto plan = edge_self_join_plan();
  const auto catalog = plan.catalog();
  const auto rows = replay_rows();
  const auto operations = replay_operations();
  std::istringstream stream(replay_stream(catalog));
  io::EventReader reader(stream, catalog);
  OrderedReplay replay(std::move(reader));
  PhysicalRuntime runtime(plan);
  Database database;
  database.tables.resize(1);

  for (std::size_t i = 0; i < rows.size(); ++i) {
    const auto* next = replay.peek();
    check(next && next->update.sequence == i + 1 &&
              next->update.values == rows[i] &&
              next->update.operation == operations[i],
          "ordered replay exposes the next full physical source event");
    const bool changed = operations[i] == SetOperation::insert
        ? database.tables[0].insert(rows[i]).second
        : database.tables[0].erase(rows[i]) != 0;
    auto epoch = replay.apply_next(runtime);
    check(epoch && epoch->input.sequence == i + 1 &&
              epoch->input.physical_changed == changed &&
              runtime.sequence() == i + 1 &&
              replay.progress().sequence == i + 1,
          "physical runtime commit and replay acknowledgement advance together");
    const auto snapshot = runtime.snapshot();
    check(snapshot.physical.tables == database.tables,
          "runtime keeps every full source row, including unused payload columns");
    runtime.check_invariants();
    if (i == 1) {
      check(runtime.derivation_count(OccurrenceId{0}, {std::int64_t{1}, std::int64_t{2}}) == 1 &&
                runtime.derivation_count(OccurrenceId{1}, {std::int64_t{1}, std::int64_t{2}}) == 1,
            "self-join routes each physical row to each alias");
    }
    if (i == 2) {
      check(changed && database.tables[0].size() == 3 &&
                runtime.derivation_count(OccurrenceId{0}, {std::int64_t{1}, std::int64_t{2}}) == 2 &&
                runtime.derivation_count(OccurrenceId{1}, {std::int64_t{1}, std::int64_t{2}}) == 2,
            "distinct full rows with the same projection increase both alias counts");
      check(database.tables[0].contains(edge(1, 2, "left-a")) &&
                database.tables[0].contains(edge(1, 2, "left-b")),
            "unused payload distinguishes physical source rows");
    }
    if (i == 3) {
      check(runtime.derivation_count(OccurrenceId{0}, {std::int64_t{1}, std::int64_t{2}}) == 1 &&
                runtime.derivation_count(OccurrenceId{1}, {std::int64_t{1}, std::int64_t{2}}) == 1 &&
                database.tables[0].contains(edge(1, 2, "left-b")) &&
                !database.tables[0].contains(edge(1, 2, "left-a")),
            "deleting one full row preserves the other payload witness and decrements counts");
    }
    if (i == 4) {
      check(changed &&
                runtime.derivation_count(OccurrenceId{0}, {std::int64_t{2}, std::int64_t{3}}) == 2 &&
                runtime.derivation_count(OccurrenceId{1}, {std::int64_t{2}, std::int64_t{3}}) == 2,
            "distinct full rows with the same right-alias projection increase both counts");
    }
    if (i == 5) {
      check(runtime.derivation_count(OccurrenceId{0}, {std::int64_t{2}, std::int64_t{3}}) == 1 &&
                runtime.derivation_count(OccurrenceId{1}, {std::int64_t{2}, std::int64_t{3}}) == 1 &&
                database.tables[0].contains(edge(2, 3, "right-b")) &&
                !database.tables[0].contains(edge(2, 3, "right-a")),
            "deleting one right-alias witness preserves the other full source row");
    }
    if (i == 7) {
      check(!changed && runtime.sequence() == 8 && database.tables[0].size() == 1,
            "physical set no-op still commits its ordered sequence without changing rows");
    }
  }
  check(replay.peek() == nullptr && !replay.failed() && replay.progress().sequence == 8,
        "physical ordered replay reaches clean EOF after all accepted events");
}

std::set<SignedRow> expected_delta(const Relation& before,
                                   const Relation& after) {
  std::set<SignedRow> result;
  for (const auto& row : after)
    if (!before.contains(row)) result.emplace(SetOperation::insert, row);
  for (const auto& row : before)
    if (!after.contains(row)) result.emplace(SetOperation::erase, row);
  return result;
}

std::set<SignedRow> drain_delta(DeltaRuntime::Epoch& epoch) {
  std::set<SignedRow> result;
  while (auto record = epoch.next()) {
    check(result.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          "ordered replay emitted a duplicate signed answer row");
  }
  check(!epoch.active() && epoch.remaining() == 0,
        "consuming D06 output closes its epoch before the next input");
  return result;
}

DeltaOptions ordered_delta_options() {
  DeltaOptions options;
  options.mode = DeltaMode::maintenance;
  options.live_maintenance = LiveMaintenance::on_output;
  options.completion = DeltaCompletion::ordered_replay;
  return options;
}

void ordered_delta_replay_matches_a04() {
  const auto plan = edge_self_join_plan();
  const auto catalog = plan.catalog();
  const auto rows = replay_rows();
  const auto operations = replay_operations();
  std::istringstream stream(replay_stream(catalog));
  io::EventReader reader(stream, catalog);
  OrderedReplay replay(std::move(reader));
  auto options = ordered_delta_options();
  DeltaRuntime runtime(plan, options);
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  Database database;
  database.tables.resize(1);

  for (std::size_t i = 0; i < rows.size(); ++i) {
    const auto before = reference::evaluate(plan.catalog(), plan.query(), database);
    if (operations[i] == SetOperation::insert)
      database.tables[0].insert(rows[i]);
    else
      database.tables[0].erase(rows[i]);
    const auto after = reference::evaluate(plan.catalog(), plan.query(), database);
    const auto expected = expected_delta(before, after);
    auto epoch = replay.apply_next(runtime);
    check(epoch && epoch->sequence() == i + 1 &&
              runtime.sequence() == i + 1 &&
              replay.progress().sequence == i + 1,
          "ordered DeltaRuntime applies then acknowledges exactly one physical event");
    const auto actual = drain_delta(*epoch);
    check(actual == expected,
          "raw native D06 deltas match independent A04 before/after evaluation");
    if (i == 2 || i == 3 || i == 4 || i == 5)
      check(actual.empty(),
            "projection-only duplicate and one-witness deletions preserve set answers");
  }
  check(replay.peek() == nullptr && runtime.ready(),
        "delta replay reaches EOF only after each output epoch is consumed");
}

void replay_retry_busy_owner_and_later_malformed_record() {
  const auto plan = edge_self_join_plan();
  const auto catalog = plan.catalog();
  const auto first_row = edge(1, 2, "left");
  const auto second_row = edge(2, 3, "right");

  // A prepared physical epoch holds the target runtime busy. The exact cached
  // input remains available after the engine refuses it.
  std::istringstream retry_stream(
      edge_json_line(catalog, 1, SetOperation::insert, first_row) + "\n");
  io::EventReader retry_reader(retry_stream, catalog);
  OrderedReplay retry(std::move(retry_reader));
  PhysicalRuntime retry_runtime(plan);
  const auto* cached = retry.peek();
  check(cached != nullptr, "retry fixture has one pending source record");
  {
    auto pending = retry_runtime.prepare(
        {1, TableId{0}, SetOperation::insert, first_row});
    check(pending.active(), "fixture prepared update holds its runtime busy");
    rejects_code([&] { static_cast<void>(retry.apply_next(retry_runtime)); },
                 "runtime_busy");
    check(retry.peek() == cached && retry.progress().sequence == 0 &&
              retry_runtime.sequence() == 0,
          "engine rejection retains cached record and unacknowledged progress");
  }
  const auto accepted = retry.apply_next(retry_runtime);
  check(accepted && retry.progress().sequence == 1 &&
            retry_runtime.snapshot().physical.tables[0].contains(first_row),
        "same event retries successfully after the engine becomes ready");

  // The first successful application binds this reader to one runtime owner.
  std::istringstream owner_stream(
      edge_json_line(catalog, 1, SetOperation::insert, first_row) + "\n" +
      edge_json_line(catalog, 2, SetOperation::insert, second_row) + "\n");
  io::EventReader owner_reader(owner_stream, catalog);
  OrderedReplay owner_replay(std::move(owner_reader));
  PhysicalRuntime first_owner(plan);
  PhysicalRuntime other_owner(plan);
  static_cast<void>(owner_replay.apply_next(first_owner));
  const auto* owner_cached = owner_replay.peek();
  check(owner_cached != nullptr, "owner fixture has a second pending event");
  rejects([&] { static_cast<void>(owner_replay.apply_next(other_owner)); },
          "reader cannot switch runtime owner");
  check(owner_replay.peek() == owner_cached &&
            owner_replay.progress().sequence == 1 &&
            other_owner.sequence() == 0,
        "owner mismatch does not consume the event or mutate the other runtime");
  static_cast<void>(owner_replay.apply_next(first_owner));
  check(first_owner.sequence() == 2 && owner_replay.progress().sequence == 2,
        "bound owner can retry and apply the retained event");

  auto mismatched_catalog = catalog;
  ++mismatched_catalog.tables[0].source_schema_version;
  std::istringstream mismatch_stream(
      edge_json_line(mismatched_catalog, 1, SetOperation::insert, first_row) + "\n");
  io::EventReader mismatch_reader(mismatch_stream, mismatched_catalog);
  OrderedReplay mismatch(std::move(mismatch_reader));
  PhysicalRuntime mismatch_runtime(plan);
  rejects_code([&] { static_cast<void>(mismatch.apply_next(mismatch_runtime)); },
               "catalog_mismatch");
  check(mismatch.progress().sequence == 0 && mismatch_runtime.sequence() == 0 &&
            mismatch.peek() != nullptr,
        "catalog mismatch is checked before applying or acknowledging an event");

  // A malformed later line cannot undo or hide a prior committed event.
  std::istringstream malformed_stream(
      edge_json_line(catalog, 1, SetOperation::insert, first_row) + "\n{\"schema_version\":\n");
  io::EventReader malformed_reader(malformed_stream, catalog);
  OrderedReplay malformed(std::move(malformed_reader));
  PhysicalRuntime committed_runtime(plan);
  static_cast<void>(malformed.apply_next(committed_runtime));
  const auto committed_image = committed_runtime.snapshot();
  rejects([&] { static_cast<void>(malformed.apply_next(committed_runtime)); },
          "malformed second JSONL record");
  check(malformed.failed() && malformed.progress().sequence == 1 &&
            committed_runtime.sequence() == 1 &&
            committed_runtime.snapshot().physical.tables ==
                committed_image.physical.tables,
        "malformed later record leaves prior runtime commit and progress intact");
  rejects_code([&] { static_cast<void>(malformed.peek()); }, "input_failed");

  // D06 output is an explicit barrier: a second input can be decoded and
  // cached, while engine rejection leaves it pending until output is drained.
  std::istringstream busy_stream(
      edge_json_line(catalog, 1, SetOperation::insert, first_row) + "\n" +
      edge_json_line(catalog, 2, SetOperation::insert, second_row) + "\n" +
      edge_json_line(catalog, 3, SetOperation::insert, edge(3, 4, "last")) + "\n");
  io::EventReader busy_reader(busy_stream, catalog);
  OrderedReplay busy_replay(std::move(busy_reader));
  auto options = ordered_delta_options();
  DeltaRuntime busy_runtime(plan, options);
  static_cast<void>(busy_runtime.set_mode(DeltaMode::delta));
  auto no_output = busy_replay.apply_next(busy_runtime);
  check(no_output && drain_delta(*no_output).empty(),
        "first single edge has no self-join output");
  auto visible_output = busy_replay.apply_next(busy_runtime);
  check(visible_output && visible_output->remaining() == 1,
        "second edge commits one D06 answer and retains its output lease");
  const auto* busy_cached = busy_replay.peek();
  rejects_code([&] { static_cast<void>(busy_replay.apply_next(busy_runtime)); },
               "runtime_busy");
  check(busy_cached && busy_replay.peek() == busy_cached &&
            busy_replay.progress().sequence == 2 &&
            busy_runtime.sequence() == 2,
        "D06 busy rejection retains the next input without advancing progress");
  static_cast<void>(drain_delta(*visible_output));
  auto after_drain = busy_replay.apply_next(busy_runtime);
  check(after_drain && after_drain->sequence() == 3 &&
            busy_replay.progress().sequence == 3,
        "draining D06 output releases the barrier and permits retry");
  static_cast<void>(drain_delta(*after_drain));
}

}  // namespace

int main() {
  try {
    json_contract_and_typed_scalars();
    catalog_fingerprint_matches_existing_serializer();
    binary_golden_and_frames();
    jsonl_progress_failures_and_limits();
    jsonl_object_budget_excludes_framing();
    nondefault_options_are_format_scoped();
    timestamp_flag_legacy_profile();
    csv_and_legacy_profiles();
    physical_replay_preserves_source_rows_and_counts();
    ordered_delta_replay_matches_a04();
    replay_retry_busy_owner_and_later_malformed_record();
    std::cout << "Ingest codecs, ordered input progress and runtime replay passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
