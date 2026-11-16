#pragma once

#include "crown/api/error.hpp"
#include "crown/ir/digest.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/recovery/sql_rows_session.hpp"
#include "indexed_runtime_fixture.hpp"
#include "sql_aggregate_file_fixture.hpp"
#include <array>
#include <bit>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <map>
#include <optional>
#include <span>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace crown::sql_rows_session_test {
namespace sr = recovery::sql_rows;
using Cell = runtime::sql_rows::Cell;
using Cells = std::vector<Cell>;
using Row = runtime::aggregate::Row;
using Bag = std::map<Row, std::uint64_t>;
using Signed = std::pair<bool, std::uint64_t>; // negative, exact unsigned magnitude
using Changes = std::map<Row, Signed>;
using sql_aggregate_file_test::Directory;
using sql_aggregate_file_test::contents;
using sql_aggregate_file_test::put;
using sql_aggregate_file_test::number;
using sql_aggregate_file_test::refused;
using sql_aggregate_file_test::reseal;

inline Cell text(std::string_view value) { return storage::ScalarView{value}; }

inline Catalog bag_schema() {
  return {1, {{"r", {{"k", ScalarType::int64, false},
      {"id", ScalarType::int64, false}, {"x", ScalarType::int64, true},
      {"tag", ScalarType::string, true}}}}};
}

inline frontend::SqlRowsProgram compile_rows(const resource::MemoryAccount& account,
    std::string_view sql, const Catalog& catalog) {
  frontend::SqlRowsBindOptions options;
  options.retain_binding_image = true;
  auto result = frontend::bind_sql_rows_into(account, sql, catalog, options);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result))
    throw Error(failure->diagnostic.code, failure->diagnostic.message);
  return std::get<frontend::SqlRowsProgram>(std::move(result));
}

inline FreeConnexTree tree_for(const frontend::SqlRowsProgram& program) {
  if (program.contradiction()) return {};
  const auto core = program.export_core();
  const auto selected = planner::minimum_tree(core.catalog, core.query);
  assert(selected.status == planner::OracleStatus::proven_minimum && selected.tree);
  return *selected.tree;
}

// Genuine public session factories own every mutable native/source state used
// by the assertions. The fixture keeps only compiler metadata and fixed options.
struct Fixture {
  Directory directory;
  std::string root = directory.file("rows.root"), sink = directory.file("rows.sink");
  resource::MemoryAccount account = resource::MemoryAccount::create(128ULL * 1024 * 1024);
  frontend::SqlRowsProgram program;
  FreeConnexTree tree;
  PhysicalOptions physical;
  runtime::sql_rows::Options normal;
  runtime::sql_rows::OutputLimits output_limits;
  sr::SessionLimits limits;
  sr::SessionIdentity identity;

  explicit Fixture(bool indexed = false, Catalog catalog = bag_schema(),
      std::string_view sql = "SELECT x FROM r",
      runtime::sql_rows::Options options = {}, runtime::sql_rows::OutputLimits outputs = {})
      : program(compile_rows(account, sql, catalog)), tree(tree_for(program)),
        physical(indexed ? s04_runtime::options() : PhysicalOptions{}),
        normal(std::move(options)), output_limits(outputs) {
    if (indexed)
      limits.rebuild.indexed_work = storage::IndexWork{
          100000000, 100000000, 256ULL * 1024 * 1024, 100000000, 100000000};
    identity.query_id.fill('1');
    identity.sink_id.fill('2');
  }

  [[nodiscard]] sr::Session create() {
    return sr::Session::create_into(account, {root, sink}, identity, program,
        tree, physical, normal, output_limits, limits);
  }
  [[nodiscard]] sr::Session recover() {
    return sr::Session::recover_into(account, {root, sink}, identity.query_id, limits);
  }
};

inline void state(const sr::Session& session, std::uint64_t w, std::uint64_t i,
    std::uint64_t c, std::uint64_t d) {
  const auto value = session.state();
  assert(value.logged == w && value.disposed == i &&
      value.committed == c && value.delivered == d);
}

inline Row own_row(std::span<const Cell> cells) {
  Row result;
  result.reserve(cells.size());
  for (const auto& cell : cells) {
    if (cell) result.emplace_back(storage::export_scalar(*cell));
    else result.emplace_back(std::nullopt);
  }
  return result;
}

inline Bag current_bag(sr::Session& session) {
  Bag result;
  auto cursor = session.results();
  while (const auto item = cursor.next())
    assert(result.emplace(item->tuple.export_values(), item->multiplicity).second);
  return result;
}

inline std::uint64_t add(std::uint64_t a, std::uint64_t b) {
  assert(b <= UINT64_MAX - a);
  return a + b;
}
inline std::uint64_t multiply(std::uint64_t a, std::uint64_t b) {
  assert(!a || b <= UINT64_MAX / a);
  return a * b;
}

inline Changes difference(const Bag& before, const Bag& after) {
  Changes result;
  for (const auto& [tuple, old_weight] : before) {
    const auto found = after.find(tuple);
    const auto new_weight = found == after.end() ? 0 : found->second;
    if (old_weight != new_weight)
      result.emplace(tuple, Signed{old_weight > new_weight,
          old_weight > new_weight ? old_weight - new_weight : new_weight - old_weight});
  }
  for (const auto& [tuple, new_weight] : after)
    if (!before.contains(tuple)) result.emplace(tuple, Signed{false, new_weight});
  return result;
}

struct DecodedRowEpoch {
  std::uint64_t generation = 0, input_sequence = 0, physical_sequence = 0;
  bool changed = false, output_changed = false;
  std::vector<std::pair<Row, Signed>> rows;
};

inline std::uint64_t read_le(std::string_view bytes, std::size_t& at, unsigned width) {
  assert(width == 1 || width == 4 || width == 8);
  assert(at <= bytes.size() && width <= bytes.size() - at);
  std::uint64_t result = 0;
  for (unsigned i = 0; i < width; ++i)
    result |= std::uint64_t(static_cast<unsigned char>(bytes[at++])) << (8 * i);
  return result;
}

inline std::string_view take(std::string_view bytes, std::size_t& at, std::size_t count) {
  assert(at <= bytes.size() && count <= bytes.size() - at);
  const auto value = bytes.substr(at, count);
  at += count;
  return value;
}

inline Date date_from_days(std::int32_t count) {
  const std::chrono::sys_days point{std::chrono::days{count}};
  const std::chrono::year_month_day ymd{point};
  assert(ymd.ok());
  std::ostringstream text;
  text << std::setfill('0') << std::setw(4) << static_cast<int>(ymd.year()) << '-'
       << std::setw(2) << static_cast<unsigned>(ymd.month()) << '-'
       << std::setw(2) << static_cast<unsigned>(ymd.day());
  return Date::parse(text.str());
}

inline runtime::aggregate::SqlValue read_cell(std::string_view bytes, std::size_t& at) {
  const auto present = read_le(bytes, at, 1);
  assert(present <= 1);
  if (!present) return std::nullopt;
  switch (read_le(bytes, at, 1)) {
    case 0:
      return Value{std::bit_cast<std::int64_t>(read_le(bytes, at, 8))};
    case 1: {
      const auto size = read_le(bytes, at, 8);
      assert(size <= SIZE_MAX);
      const auto value = take(bytes, at, static_cast<std::size_t>(size));
      return Value{std::string(value)};
    }
    case 2: {
      const auto value = read_le(bytes, at, 1);
      assert(value <= 1);
      return Value{value != 0};
    }
    case 3:
      return Value{date_from_days(std::bit_cast<std::int32_t>(
          static_cast<std::uint32_t>(read_le(bytes, at, 4))))};
    case 4: {
      const auto size = read_le(bytes, at, 1);
      const auto value = take(bytes, at, static_cast<std::size_t>(size));
      return Value{Decimal::parse(value)};
    }
    default:
      assert(false && "unknown row epoch scalar tag");
      return std::nullopt;
  }
}

// This deliberately decodes the row payload without calling the row codec's
// output decoder. `inspect` is used separately for envelope/schema validity;
// this parser supplies the test's independent values and signed magnitudes.
inline DecodedRowEpoch decode_row_epoch(const frontend::SqlRowsProgram& program,
    std::string_view frame) {
  constexpr std::size_t header = sr::frame_header_size;
  assert(frame.size() >= header + 107 && frame.substr(0, 8) == "CROWNRW2");
  const auto inspected = sr::inspect(program, frame);
  assert(inspected.kind == sr::Kind::row_epoch);
  const auto& metadata = std::get<sr::RowInfo>(inspected.payload);

  std::size_t at = header;
  assert(read_le(frame, at, 1) == static_cast<std::uint8_t>(sr::Kind::row_epoch));
  static_cast<void>(read_le(frame, at, 8)); // Frame ordinal.
  DecodedRowEpoch result;
  result.generation = read_le(frame, at, 8);
  result.input_sequence = read_le(frame, at, 8);
  result.physical_sequence = read_le(frame, at, 8);
  static_cast<void>(take(frame, at, 64)); // Input body SHA-256.
  const auto changed = read_le(frame, at, 1), output_changed = read_le(frame, at, 1);
  assert(changed <= 1 && output_changed <= 1);
  result.changed = changed != 0;
  result.output_changed = output_changed != 0;
  const auto count = read_le(frame, at, 8);
  assert(count <= frame.size() / 9);
  std::string previous_key;
  for (std::uint64_t i = 0; i < count; ++i) {
    const auto row_start = at;
    const auto fields = read_le(frame, at, 8);
    assert(fields == program.outputs().size());
    Row tuple;
    tuple.reserve(static_cast<std::size_t>(fields));
    for (std::uint64_t field = 0; field < fields; ++field)
      tuple.push_back(read_cell(frame, at));
    const auto key_end = at;
    const auto negative = read_le(frame, at, 1);
    const auto magnitude = read_le(frame, at, 8);
    assert(negative <= 1 && magnitude != 0);
    std::string key(frame.substr(row_start, key_end - row_start));
    if (i) assert(previous_key < key);
    previous_key = std::move(key);
    result.rows.emplace_back(std::move(tuple), Signed{negative != 0, magnitude});
  }
  assert(at == frame.size());
  assert(metadata.generation == result.generation &&
      metadata.input_sequence == result.input_sequence &&
      metadata.physical_sequence == result.physical_sequence &&
      metadata.rows == result.rows.size() && metadata.changed == result.changed &&
      metadata.output_changed == result.output_changed);
  assert(result.output_changed == !result.rows.empty());
  return result;
}

inline Changes changes(const DecodedRowEpoch& epoch) {
  Changes result;
  for (const auto& [tuple, change] : epoch.rows)
    assert(result.emplace(tuple, change).second);
  return result;
}

inline std::string generation_file(const Fixture& fixture, std::uint64_t generation,
    std::string_view suffix = ".wal") {
  std::ostringstream out;
  out << fixture.root << ".g" << std::hex << std::setw(16) << std::setfill('0')
      << generation << suffix;
  return out.str();
}

inline std::vector<std::string> frames(std::string_view bytes) {
  std::vector<std::string> result;
  std::size_t at = 0;
  while (at < bytes.size()) {
    assert(bytes.size() - at >= sr::frame_header_size);
    std::uint64_t body = 0;
    for (unsigned i = 0; i < 8; ++i)
      body |= std::uint64_t(static_cast<unsigned char>(bytes[at + 12 + i])) << (8 * i);
    assert(body <= bytes.size() - at - sr::frame_header_size);
    const auto size = sr::frame_header_size + static_cast<std::size_t>(body);
    result.emplace_back(bytes.substr(at, size));
    at += size;
  }
  return result;
}

inline std::string join(const std::vector<std::string>& parts, std::size_t count) {
  std::string result;
  for (std::size_t i = 0; i < count; ++i) result += parts[i];
  return result;
}

} // namespace crown::sql_rows_session_test
