#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/workload_statistics.hpp"

#include <algorithm>
#include <array>
#include <charconv>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
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
namespace workload = crown::runtime::workload;

constexpr std::uint64_t fnv_offset = 14695981039346656037ULL;
constexpr std::uint64_t fnv_prime = 1099511628211ULL;
constexpr std::size_t table_r = 0;
constexpr std::size_t table_s = 1;
constexpr std::size_t table_unused = 2;
constexpr std::size_t slot_count = 96;
constexpr std::size_t key_count = 8;

struct Hash64 {
  std::uint64_t value{fnv_offset};

  void byte(std::uint8_t input) noexcept {
    value ^= input;
    value *= fnv_prime;
  }

  void u64(std::uint64_t input) noexcept {
    for (unsigned shift = 0; shift < 64U; shift += 8U) {
      const auto part = static_cast<std::uint8_t>((input >> shift) & 0xffU);
      byte(part);
    }
  }

  void signed_value(std::int64_t input) noexcept {
    u64(static_cast<std::uint64_t>(input));
  }
};

std::string hex64(std::uint64_t value) {
  std::ostringstream output;
  output << std::hex << std::setfill('0') << std::setw(16) << value;
  return output.str();
}

void hash_row(Hash64& hash, const Row& row) {
  hash.u64(static_cast<std::uint64_t>(row.size()));
  for (const auto& value : row) {
    hash.signed_value(std::get<std::int64_t>(value));
  }
}

Value integer(std::int64_t value) { return Value{value}; }

Row r_row(std::int64_t slot) {
  const auto y = slot % static_cast<std::int64_t>(key_count);
  const auto ignored = slot * 31 + 7;
  return Row{integer(slot), integer(y), integer(ignored)};
}

Row s_row(std::int64_t y) { return Row{integer(y)}; }

Row unused_row(std::int64_t value) { return Row{integer(value)}; }

Database make_initial_database() {
  Database database;
  database.tables.resize(3);
  for (std::int64_t slot = 0; slot < 48; ++slot) {
    database.tables[table_r].insert(r_row(slot));
  }
  for (const std::int64_t y : std::array<std::int64_t, 4>{0, 2, 4, 6}) {
    database.tables[table_s].insert(s_row(y));
  }
  database.tables[table_unused].insert(unused_row(777));
  return database;
}

struct Fixture {
  Catalog catalog;
  Query query;
  PhysicalPlan plan;
  Database initial;

  Fixture()
      : catalog{1,
            {{"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"ignored", ScalarType::int64}}},
             {"S", {{"y", ScalarType::int64}}},
             {"unused", {{"u", ScalarType::int64}}}}},
        query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
              {{"R", TableId{0},
                {VariableId{0}, VariableId{1}, IgnoredColumn{}}},
               {"S", TableId{1}, {VariableId{1}}}},
              {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false},
        plan(planner::lower_tree(
            catalog, query,
            FreeConnexTree{
                NodeId{0},
                {{"R", NodeKind::native,
                  VariableSet{VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
                 {"S", NodeKind::native, VariableSet{VariableId{1}}, {}, 1, {}}},
                {}, {}})),
        initial(make_initial_database()) {}
};

struct TraceSummary {
  std::uint64_t r_insert{};
  std::uint64_t r_erase{};
  std::uint64_t s_insert{};
  std::uint64_t s_erase{};
  std::uint64_t changed_inputs{};
  std::uint64_t noop_inputs{};
  std::uint64_t changed_s_inputs{};
  std::set<std::uint64_t> changed_s_bucket_sizes;
  std::uint64_t checksum{};
};

bool apply_literal(Database& database, const PhysicalSetUpdate& update) {
  const auto table_index = static_cast<std::size_t>(update.table.value);
  Relation& relation = database.tables.at(table_index);
  if (update.operation == SetOperation::insert) {
    return relation.insert(update.values).second;
  }
  return relation.erase(update.values) != 0U;
}

std::uint64_t bucket_size(const Database& database, std::int64_t y) {
  std::uint64_t result = 0;
  for (const auto& row : database.tables[table_r]) {
    if (std::get<std::int64_t>(row.at(1)) == y) {
      ++result;
    }
  }
  return result;
}

std::uint64_t splitmix64(std::uint64_t& state) noexcept {
  state += 0x9e3779b97f4a7c15ULL;
  std::uint64_t value = state;
  value = (value ^ (value >> 30U)) * 0xbf58476d1ce4e5b9ULL;
  value = (value ^ (value >> 27U)) * 0x94d049bb133111ebULL;
  return value ^ (value >> 31U);
}

std::vector<PhysicalSetUpdate> make_trace(std::size_t event_count,
                                          std::uint64_t seed,
                                          const Database& initial,
                                          TraceSummary& summary) {
  std::vector<PhysicalSetUpdate> events;
  events.reserve(event_count);
  Database generation_state = initial;
  std::uint64_t random_state = seed;
  Hash64 trace_hash;

  for (std::size_t index = 0; index < event_count; ++index) {
    const auto block = static_cast<std::int64_t>(index / 40U);
    const auto phase = index % 40U;
    TableId table{0};
    SetOperation operation = SetOperation::insert;
    Row values;

    if (phase <= 7U) {
      table = TableId{static_cast<std::uint64_t>(table_r)};
      if (phase == 0U || phase == 1U || phase == 5U || phase == 6U) {
        operation = SetOperation::insert;
      } else {
        operation = SetOperation::erase;
      }
      values = r_row(0);
      if (phase == 3U) {
        const auto absent_slot = 1000000 + block;
        values = r_row(absent_slot);
      }
    } else if (phase >= 8U && phase <= 15U) {
      table = TableId{static_cast<std::uint64_t>(table_s)};
      if (phase == 8U || phase == 9U || phase == 13U || phase == 14U) {
        operation = SetOperation::insert;
      } else {
        operation = SetOperation::erase;
      }
      values = s_row(0);
      if (phase == 11U) {
        values = s_row(1000000 + block);
      }
    } else if (phase == 16U || phase == 17U || phase == 19U) {
      table = TableId{static_cast<std::uint64_t>(table_r)};
      operation = phase == 17U ? SetOperation::insert : SetOperation::erase;
      values = r_row(8);
    } else if (phase == 18U || phase == 20U) {
      table = TableId{static_cast<std::uint64_t>(table_s)};
      operation = phase == 18U ? SetOperation::insert : SetOperation::erase;
      values = s_row(0);
    } else {
      const std::uint64_t choice = splitmix64(random_state);
      if ((choice & 3U) == 0U) {
        table = TableId{static_cast<std::uint64_t>(table_s)};
        const auto y = static_cast<std::int64_t>(splitmix64(random_state) % key_count);
        values = s_row(y);
      } else {
        table = TableId{static_cast<std::uint64_t>(table_r)};
        const auto slot = static_cast<std::int64_t>(splitmix64(random_state) % slot_count);
        values = r_row(slot);
      }
      operation = (splitmix64(random_state) & 1U) == 0U
          ? SetOperation::insert : SetOperation::erase;
    }

    if (table.value == static_cast<std::uint64_t>(table_s) && values.size() == 1U) {
      const auto y = std::get<std::int64_t>(values.front());
      const auto degree_before = bucket_size(generation_state, y);
      const bool changed = apply_literal(
          generation_state,
          PhysicalSetUpdate{static_cast<std::uint64_t>(index) + 1U, table,
                            operation, values});
      if (changed) {
        ++summary.changed_s_inputs;
        summary.changed_s_bucket_sizes.insert(degree_before);
      }
      if (changed) {
        ++summary.changed_inputs;
      } else {
        ++summary.noop_inputs;
      }
    } else {
      const bool changed = apply_literal(
          generation_state,
          PhysicalSetUpdate{static_cast<std::uint64_t>(index) + 1U, table,
                            operation, values});
      if (changed) {
        ++summary.changed_inputs;
      } else {
        ++summary.noop_inputs;
      }
    }

    if (table.value == static_cast<std::uint64_t>(table_r)) {
      if (operation == SetOperation::insert) {
        ++summary.r_insert;
      } else {
        ++summary.r_erase;
      }
    } else {
      if (operation == SetOperation::insert) {
        ++summary.s_insert;
      } else {
        ++summary.s_erase;
      }
    }

    trace_hash.u64(static_cast<std::uint64_t>(index) + 1U);
    trace_hash.u64(table.value);
    trace_hash.u64(operation == SetOperation::insert ? 1U : 2U);
    hash_row(trace_hash, values);
    events.push_back(PhysicalSetUpdate{
        static_cast<std::uint64_t>(index) + 1U, table, operation, std::move(values)});
  }

  summary.checksum = trace_hash.value;
  return events;
}

Database replay_literal(const Database& initial,
                        const std::vector<PhysicalSetUpdate>& events) {
  Database result = initial;
  for (const auto& update : events) {
    static_cast<void>(apply_literal(result, update));
  }
  return result;
}

Relation independent_answer(const Database& database) {
  Relation result;
  for (const auto& source : database.tables[table_r]) {
    const auto y = std::get<std::int64_t>(source.at(1));
    if (database.tables[table_s].contains(s_row(y))) {
      result.insert(Row{source.at(0), source.at(1)});
    }
  }
  return result;
}

std::uint64_t hash_database(const Database& database) {
  Hash64 hash;
  hash.u64(0x534f55524345ULL);
  hash.u64(static_cast<std::uint64_t>(database.tables.size()));
  for (std::size_t table = 0; table < database.tables.size(); ++table) {
    hash.u64(static_cast<std::uint64_t>(table));
    hash.u64(static_cast<std::uint64_t>(database.tables[table].size()));
    for (const auto& row : database.tables[table]) {
      hash_row(hash, row);
    }
  }
  return hash.value;
}

std::uint64_t hash_relation(const Relation& relation, std::uint64_t tag) {
  Hash64 hash;
  hash.u64(tag);
  hash.u64(static_cast<std::uint64_t>(relation.size()));
  for (const auto& row : relation) {
    hash_row(hash, row);
  }
  return hash.value;
}

struct RecordFact {
  std::uint64_t satisfied{};
  std::vector<bool> child_present;
  bool survives{};
};

using RecordMap = std::map<Row, RecordFact>;
using KeyCountMap = std::map<Row, std::uint64_t>;

RecordMap expected_records(const Database& database, bool root) {
  RecordMap result;
  if (root) {
    for (const auto& source : database.tables[table_r]) {
      const Row key{source.at(0), source.at(1)};
      const auto y = std::get<std::int64_t>(source.at(1));
      const bool child = database.tables[table_s].contains(s_row(y));
      const std::vector<bool> children{child};
      const auto inserted = result.emplace(
          key, RecordFact{child ? 1U : 0U, children, child});
      if (!inserted.second) {
        throw std::runtime_error("literal root projection unexpectedly duplicated");
      }
    }
  } else {
    for (const auto& row : database.tables[table_s]) {
      const bool inserted = result.emplace(
          row, RecordFact{0U, {}, true}).second;
      if (!inserted) {
        throw std::runtime_error("literal S source unexpectedly duplicated");
      }
    }
  }
  return result;
}

KeyCountMap expected_key_counts(const std::vector<ProjectionKeySnapshot>& input) {
  KeyCountMap result;
  for (const auto& item : input) {
    if (!result.emplace(item.key.values(), item.support.value).second) {
      throw std::runtime_error("support snapshot has duplicate projection keys");
    }
  }
  return result;
}

Relation expected_survivors(const Database& database, bool root) {
  Relation result;
  if (root) {
    for (const auto& source : database.tables[table_r]) {
      const auto y = std::get<std::int64_t>(source.at(1));
      if (database.tables[table_s].contains(s_row(y))) {
        result.insert(Row{source.at(0), source.at(1)});
      }
    }
  } else {
    result = database.tables[table_s];
  }
  return result;
}

KeyCountMap expected_child_parent_counts(const Relation& child_survivors) {
  KeyCountMap result;
  for (const auto& row : child_survivors) {
    // The admitted S(y) leaf has local scope {y} and separator {y}; its P
    // population therefore comes from every local S survivor, including keys
    // that do not join to any R row.
    ++result[Row{row.at(0)}];
  }
  return result;
}

KeyCountMap expected_root_visible_counts(const Relation& answer) {
  KeyCountMap result;
  for (const auto& row : answer) {
    ++result[row];
  }
  return result;
}

KeyCountMap expected_root_parent_counts(const Relation& answer) {
  KeyCountMap result;
  if (!answer.empty()) {
    result.emplace(Row{}, static_cast<std::uint64_t>(answer.size()));
  }
  return result;
}

RecordMap actual_records(const NodeSupportSnapshot& node) {
  RecordMap result;
  for (const auto& record : node.records) {
    RecordFact fact{static_cast<std::uint64_t>(record.satisfied.value),
                    record.child_present, record.survives};
    if (!result.emplace(record.tuple.values(), std::move(fact)).second) {
      throw std::runtime_error("support snapshot has duplicate record tuples");
    }
  }
  return result;
}

Relation actual_survivors(const NodeSupportSnapshot& node) {
  Relation result;
  for (const auto& row : node.survivors) {
    if (!result.insert(row.values()).second) {
      throw std::runtime_error("support snapshot has duplicate survivors");
    }
  }
  return result;
}

std::uint64_t hash_record_map(const RecordMap& records, std::uint64_t tag) {
  Hash64 hash;
  hash.u64(tag);
  hash.u64(static_cast<std::uint64_t>(records.size()));
  for (const auto& [row, fact] : records) {
    hash_row(hash, row);
    hash.u64(fact.satisfied);
    hash.u64(static_cast<std::uint64_t>(fact.child_present.size()));
    for (const bool child : fact.child_present) {
      hash.u64(child ? 1U : 0U);
    }
    hash.u64(fact.survives ? 1U : 0U);
  }
  return hash.value;
}

std::uint64_t hash_key_counts(const KeyCountMap& values, std::uint64_t tag) {
  Hash64 hash;
  hash.u64(tag);
  hash.u64(static_cast<std::uint64_t>(values.size()));
  for (const auto& [row, count] : values) {
    hash_row(hash, row);
    hash.u64(count);
  }
  return hash.value;
}

std::uint64_t hash_support_facts(const RecordMap& root_records,
                                 const Relation& root_survivors,
                                 const KeyCountMap& root_parent,
                                 const KeyCountMap& root_visible,
                                 const RecordMap& child_records,
                                 const Relation& child_survivors,
                                 const KeyCountMap& child_parent) {
  Hash64 hash;
  hash.u64(hash_record_map(root_records, 0x52524f4f54ULL));
  hash.u64(hash_relation(root_survivors, 0x5253555256ULL));
  hash.u64(hash_key_counts(root_parent, 0x5250415245ULL));
  hash.u64(hash_key_counts(root_visible, 0x5256495349ULL));
  hash.u64(hash_record_map(child_records, 0x53434849ULL));
  hash.u64(hash_relation(child_survivors, 0x5353555256ULL));
  hash.u64(hash_key_counts(child_parent, 0x5350415245ULL));
  return hash.value;
}

struct Validation {
  std::uint64_t source_checksum{};
  std::uint64_t support_checksum{};
  std::uint64_t result_checksum{};
  std::uint64_t semantic_checksum{};
  std::uint64_t source_r_rows{};
  std::uint64_t source_s_rows{};
  std::uint64_t unused_rows{};
  std::uint64_t root_records{};
  std::uint64_t root_survivors{};
  std::uint64_t child_records{};
  std::uint64_t child_survivors{};
  std::uint64_t result_rows{};
};

template <class Runtime>
Validation validate_runtime(Runtime& runtime,
                            const Database& expected_database,
                            const std::vector<PhysicalSetUpdate>& events,
                            std::uint64_t trace_checksum) {
  if (!runtime.ready()) {
    throw std::runtime_error("runtime was not ready after the update stream");
  }
  if (runtime.sequence() != static_cast<std::uint64_t>(events.size())) {
    throw std::runtime_error("runtime committed sequence differs from event count");
  }

  const PhysicalSnapshot actual = runtime.snapshot();
  if (actual.sequence != static_cast<std::uint64_t>(events.size()) ||
      actual.physical.tables != expected_database.tables) {
    throw std::runtime_error("actual full-row source state differs from literal replay");
  }

  const Relation expected_answer = independent_answer(expected_database);
  Relation actual_answer;
  auto cursor = runtime.results();
  while (auto tuple = cursor.next()) {
    if (!actual_answer.insert(tuple->values()).second) {
      throw std::runtime_error("runtime result cursor returned a duplicate set answer");
    }
  }
  if (actual_answer != expected_answer || actual.support.sequence != actual.sequence ||
      actual.support.has_answer != !expected_answer.empty() ||
      actual.support.nodes.size() != 2U) {
    throw std::runtime_error("actual query/support summary differs from independent join");
  }

  const auto& root = actual.support.nodes.at(0);
  const auto& child = actual.support.nodes.at(1);
  if (root.node.value != 0U || child.node.value != 1U ||
      root.kind != NodeKind::native || child.kind != NodeKind::native) {
    throw std::runtime_error("native R-root/S-child plan shape changed");
  }

  const RecordMap expected_root_records = expected_records(expected_database, true);
  const RecordMap expected_child_records = expected_records(expected_database, false);
  const RecordMap found_root_records = actual_records(root);
  const RecordMap found_child_records = actual_records(child);
  if (found_root_records.size() != expected_root_records.size() ||
      found_child_records.size() != expected_child_records.size()) {
    throw std::runtime_error("actual source projections differ from literal record maps");
  }
  for (const auto& [key, expected] : expected_root_records) {
    const auto found = found_root_records.find(key);
    if (found == found_root_records.end() ||
        found->second.satisfied != expected.satisfied ||
        found->second.child_present != expected.child_present ||
        found->second.survives != expected.survives) {
      throw std::runtime_error("actual root record flags differ from literal R/S join");
    }
  }
  for (const auto& [key, expected] : expected_child_records) {
    const auto found = found_child_records.find(key);
    if (found == found_child_records.end() ||
        found->second.survives != expected.survives) {
      throw std::runtime_error("actual S leaf records differ from literal source set");
    }
  }

  const Relation expected_root_survivors = expected_survivors(expected_database, true);
  const Relation expected_child_survivors = expected_survivors(expected_database, false);
  const Relation found_root_survivors = actual_survivors(root);
  const Relation found_child_survivors = actual_survivors(child);
  const KeyCountMap expected_root_parent = expected_root_parent_counts(expected_answer);
  const KeyCountMap expected_child_parent =
      expected_child_parent_counts(expected_child_survivors);
  const KeyCountMap expected_root_visible = expected_root_visible_counts(expected_answer);
  const KeyCountMap found_root_parent = expected_key_counts(root.parent_keys);
  const KeyCountMap found_child_parent = expected_key_counts(child.parent_keys);
  if (!root.visible_keys.has_value()) {
    throw std::runtime_error("root E population is unexpectedly absent for head x,y");
  }
  const KeyCountMap found_root_visible = expected_key_counts(*root.visible_keys);
  if (found_root_survivors != expected_root_survivors ||
      found_child_survivors != expected_child_survivors ||
      found_root_parent != expected_root_parent ||
      found_child_parent != expected_child_parent ||
      found_root_visible != expected_root_visible) {
    throw std::runtime_error("actual S/P/E support populations differ from literal counts");
  }

  Validation result;
  result.source_checksum = hash_database(actual.physical);
  result.support_checksum = hash_support_facts(
      found_root_records, found_root_survivors, found_root_parent,
      found_root_visible, found_child_records, found_child_survivors,
      found_child_parent);
  result.result_checksum = hash_relation(actual_answer, 0x414e53574552ULL);
  Hash64 semantic;
  semantic.u64(trace_checksum);
  semantic.u64(result.source_checksum);
  semantic.u64(result.support_checksum);
  semantic.u64(result.result_checksum);
  result.semantic_checksum = semantic.value;
  result.source_r_rows = static_cast<std::uint64_t>(actual.physical.tables[table_r].size());
  result.source_s_rows = static_cast<std::uint64_t>(actual.physical.tables[table_s].size());
  result.unused_rows = static_cast<std::uint64_t>(actual.physical.tables[table_unused].size());
  result.root_records = static_cast<std::uint64_t>(found_root_records.size());
  result.root_survivors = static_cast<std::uint64_t>(found_root_survivors.size());
  result.child_records = static_cast<std::uint64_t>(found_child_records.size());
  result.child_survivors = static_cast<std::uint64_t>(found_child_survivors.size());
  result.result_rows = static_cast<std::uint64_t>(actual_answer.size());
  return result;
}

struct MandatoryTotals {
  std::uint64_t physical_work{};
  std::uint64_t support_work{};
  std::uint64_t delta_work{};
  std::uint64_t source_changes{};
  std::uint64_t aliases_visited{};
  std::uint64_t aliases_filtered{};
  std::uint64_t derivation_changes{};
  std::uint64_t native_crossings{};
  std::uint64_t native_record_visits{};
  std::uint64_t child_key_probes{};
  std::uint64_t child_key_events{};
  std::uint64_t survivor_transitions{};
  std::uint64_t parent_key_transitions{};
  std::uint64_t visible_key_transitions{};
  std::uint64_t storage_changes{};
  std::uint64_t journal_records{};
  std::uint64_t events_applied{};
  std::uint64_t delta_candidates{};
  std::uint64_t delta_accepted{};
  std::uint64_t delta_rejected{};
  std::uint64_t delta_spool_rows{};
  std::uint64_t drained_output_records{};
  bool operator==(const MandatoryTotals&) const = default;
};

void add_physical(MandatoryTotals& totals, const PhysicalEpoch& epoch) {
  const auto& physical = epoch.input.metrics;
  const auto& support = epoch.support.metrics;
  totals.physical_work += physical.work;
  totals.support_work += support.work;
  totals.source_changes += physical.source_changes;
  totals.aliases_visited += physical.aliases_visited;
  totals.aliases_filtered += physical.aliases_filtered;
  totals.derivation_changes += physical.derivation_changes;
  totals.native_crossings += physical.native_crossings;
  totals.native_record_visits += support.native_record_visits;
  totals.child_key_probes += support.child_key_probes;
  totals.child_key_events += support.child_key_events;
  totals.survivor_transitions += support.survivor_transitions;
  totals.parent_key_transitions += support.parent_key_transitions;
  totals.visible_key_transitions += support.visible_key_transitions;
  totals.storage_changes += support.storage_changes;
  totals.journal_records += support.journal_records;
  totals.events_applied += support.events_applied;
}

void add_delta(MandatoryTotals& totals, const DeltaRuntime::Epoch& epoch) {
  add_physical(totals, epoch.input());
  const auto& delta = epoch.metrics();
  totals.delta_work += delta.work;
  totals.delta_candidates += delta.candidates;
  totals.delta_accepted += delta.accepted;
  totals.delta_rejected += delta.rejected;
  totals.delta_spool_rows += static_cast<std::uint64_t>(delta.spool_rows);
}

template <class Runtime, class AfterEpoch>
void process_physical_stream(Runtime& runtime,
                             const std::vector<PhysicalSetUpdate>& events,
                             AfterEpoch&& after) {
  for (const auto& update : events) {
    const PhysicalEpoch epoch = runtime.apply(update);
    after(epoch);
  }
}

template <class AfterEpoch, class AfterRecord>
void process_delta_stream(DeltaRuntime& runtime,
                          const std::vector<PhysicalSetUpdate>& events,
                          AfterEpoch&& after,
                          AfterRecord&& after_record) {
  for (const auto& update : events) {
    auto pending = runtime.begin(update);
    pending.drain();
    auto epoch = pending.commit();
    after(epoch);
    while (auto output = epoch.next()) {
      after_record(*output);
    }
  }
}

enum class Scenario { physical, delta_maintenance };
enum class C01Profile { off, census, sampled };

const char* scenario_name(Scenario value) noexcept {
  switch (value) {
    case Scenario::physical: return "physical_runtime_apply";
    case Scenario::delta_maintenance: return "delta_runtime_maintenance_begin_drain_commit";
  }
  return "unknown";
}

const char* mode_name(workload::Mode value) noexcept {
  switch (value) {
    case workload::Mode::off: return "off";
    case workload::Mode::counters: return "counters";
  }
  return "unknown";
}

const char* observation_name(ObservationMode value) noexcept {
  switch (value) {
    case ObservationMode::off: return "off";
    case ObservationMode::counters: return "counters";
    case ObservationMode::timed: return "timed";
    case ObservationMode::trace: return "trace";
  }
  return "unknown";
}

workload::Options c01_options(C01Profile profile) {
  workload::Options result{};
  result.max_cells = 4096U;
  result.detail_budget = 1000000U;
  if (profile == C01Profile::off) {
    result.mode = workload::Mode::off;
    result.period = 1U;
    result.offset = 0U;
  } else {
    result.mode = workload::Mode::counters;
    result.period = profile == C01Profile::census ? 1U : 64U;
    result.offset = 0U;
  }
  return result;
}

ObservationOptions o07_options() {
  ObservationOptions result{};
  result.mode = ObservationMode::off;
  result.trace_timings = false;
  return result;
}

PhysicalRuntimeOptions physical_options() {
  PhysicalRuntimeOptions result{};
  result.support.observation = o07_options();
  result.support.capture_transitions = false;
  return result;
}

DeltaOptions delta_options() {
  DeltaOptions result{};
  result.mode = DeltaMode::maintenance;
  result.completion = DeltaCompletion::ordered_replay;
  result.physical.support.observation = o07_options();
  result.physical.support.capture_transitions = false;
  return result;
}

struct O07Facts {
  ObservationOptions options;
  bool capture_transitions{};
  bool delta_owner{};
  std::optional<DeltaMode> delta_mode;
  std::optional<LiveMaintenance> live_maintenance;
  std::optional<DeltaCompletion> completion;
  std::optional<ResultView> result_view;
};

struct TrialResult {
  std::uint64_t duration_ns{};
  Validation validation;
  workload::Snapshot collector;
  O07Facts o07;
  std::optional<MandatoryTotals> mandatory;
};

O07Facts physical_o07_facts(const PhysicalRuntime& runtime) {
  const auto& options = runtime.options();
  return O07Facts{options.support.observation,
                  options.support.capture_transitions, false,
                  std::nullopt, std::nullopt, std::nullopt, std::nullopt};
}

O07Facts delta_o07_facts(const DeltaRuntime& runtime) {
  const auto& options = runtime.options();
  const auto profile = runtime.profile();
  return O07Facts{options.physical.support.observation,
                  options.physical.support.capture_transitions, true,
                  runtime.mode(), profile.live_maintenance, runtime.completion(),
                  profile.view};
}

void validate_collector_snapshot(const workload::Snapshot& snapshot,
                                 const workload::Options& requested,
                                 std::size_t event_count) {
  if (snapshot.options() != requested || snapshot.pending()) {
    throw std::runtime_error("actual C01 options or pending status differs");
  }
  const auto& metadata = snapshot.metadata();
  if (requested.mode == workload::Mode::off) {
    if (snapshot.detail_availability() != workload::Availability::disabled ||
        !snapshot.descriptors().empty() || !snapshot.cells().empty() ||
        metadata.attempts != 0U || metadata.committed != 0U ||
        metadata.guards != 0U || metadata.detail_actions != 0U ||
        metadata.cleared_cells != 0U || metadata.merged_cells != 0U) {
      throw std::runtime_error("C01 off mode did not remain explicitly disabled");
    }
    return;
  }

  const std::uint64_t event_total = static_cast<std::uint64_t>(event_count);
  const std::uint64_t expected_selected =
      (event_total - 1U) / requested.period + 1U;
  const workload::Availability expected_availability =
      requested.period == 1U ? workload::Availability::exact
                             : workload::Availability::sampled;
  if (snapshot.descriptors().empty() ||
      snapshot.descriptors().size() != snapshot.cells().size() ||
      snapshot.detail_availability() != expected_availability ||
      metadata.attempts != event_total || metadata.committed != event_total ||
      metadata.aborted != 0U || metadata.selected != expected_selected ||
      metadata.complete != expected_selected || metadata.aborted_selected != 0U ||
      metadata.truncated != 0U || metadata.committed_truncated != 0U ||
      metadata.invalid_descriptor || metadata.protocol_error ||
      metadata.ordinal_exhausted) {
    throw std::runtime_error("enabled C01 coverage differs from complete trace replay");
  }
}

template <class Clock>
std::uint64_t elapsed_ns(typename Clock::time_point start,
                         typename Clock::time_point stop) {
  const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
  if (elapsed <= 0) {
    throw std::runtime_error("external steady_clock returned a non-positive interval");
  }
  return static_cast<std::uint64_t>(elapsed);
}

TrialResult run_physical(const Fixture& fixture,
                         const std::vector<PhysicalSetUpdate>& events,
                         const Database& expected,
                         std::uint64_t trace_checksum,
                         C01Profile profile,
                         bool measure,
                         bool collect_mandatory) {
  PhysicalRuntime runtime = PhysicalRuntime::initialize(
      fixture.plan, fixture.initial, physical_options());
  const workload::Options requested = c01_options(profile);
  runtime.configure_workload_statistics(requested);
  const O07Facts o07 = physical_o07_facts(runtime);
  if (o07.options.mode != ObservationMode::off || o07.capture_transitions) {
    throw std::runtime_error("physical O07 observation is not actually off");
  }

  MandatoryTotals totals;
  const auto collect = [&totals](const PhysicalEpoch& epoch) {
    add_physical(totals, epoch);
  };
  const auto ignore = [](const PhysicalEpoch&) noexcept {};
  std::uint64_t duration = 0;
  if (measure) {
    const auto start = std::chrono::steady_clock::now();
    if (collect_mandatory) {
      process_physical_stream(runtime, events, collect);
    } else {
      process_physical_stream(runtime, events, ignore);
    }
    const auto stop = std::chrono::steady_clock::now();
    duration = elapsed_ns<std::chrono::steady_clock>(start, stop);
  } else if (collect_mandatory) {
    process_physical_stream(runtime, events, collect);
  } else {
    process_physical_stream(runtime, events, ignore);
  }

  Validation validation = validate_runtime(runtime, expected, events, trace_checksum);
  workload::Snapshot snapshot = runtime.workload_statistics();
  validate_collector_snapshot(snapshot, requested, events.size());
  std::optional<MandatoryTotals> mandatory;
  if (collect_mandatory) {
    mandatory = totals;
  }
  return TrialResult{duration, validation, std::move(snapshot), o07, mandatory};
}

TrialResult run_delta(const Fixture& fixture,
                      const std::vector<PhysicalSetUpdate>& events,
                      const Database& expected,
                      std::uint64_t trace_checksum,
                      C01Profile profile,
                      bool measure,
                      bool collect_mandatory) {
  DeltaRuntime runtime = DeltaRuntime::initialize(
      fixture.plan, fixture.initial, delta_options());
  const workload::Options requested = c01_options(profile);
  runtime.configure_workload_statistics(requested);
  const O07Facts o07 = delta_o07_facts(runtime);
  if (o07.options.mode != ObservationMode::off || o07.capture_transitions ||
      !o07.delta_owner || !o07.delta_mode.has_value() ||
      *o07.delta_mode != DeltaMode::maintenance) {
    throw std::runtime_error("Delta O07 or maintenance configuration differs");
  }

  MandatoryTotals totals;
  const auto collect = [&totals](const DeltaRuntime::Epoch& epoch) {
    add_delta(totals, epoch);
  };
  const auto ignore = [](const DeltaRuntime::Epoch&) noexcept {};
  const auto collect_record = [&totals](const SignedResult&) {
    ++totals.drained_output_records;
  };
  const auto ignore_record = [](const SignedResult&) noexcept {};
  std::uint64_t duration = 0;
  if (measure) {
    const auto start = std::chrono::steady_clock::now();
    if (collect_mandatory) {
      process_delta_stream(runtime, events, collect, collect_record);
    } else {
      process_delta_stream(runtime, events, ignore, ignore_record);
    }
    const auto stop = std::chrono::steady_clock::now();
    duration = elapsed_ns<std::chrono::steady_clock>(start, stop);
  } else if (collect_mandatory) {
    process_delta_stream(runtime, events, collect, collect_record);
  } else {
    process_delta_stream(runtime, events, ignore, ignore_record);
  }

  if (collect_mandatory && totals.drained_output_records != 0U) {
    throw std::runtime_error("maintenance mode unexpectedly produced signed output");
  }

  Validation validation = validate_runtime(runtime, expected, events, trace_checksum);
  workload::Snapshot snapshot = runtime.workload_statistics();
  validate_collector_snapshot(snapshot, requested, events.size());
  std::optional<MandatoryTotals> mandatory;
  if (collect_mandatory) {
    mandatory = totals;
  }
  return TrialResult{duration, validation, std::move(snapshot), o07, mandatory};
}

struct Parameters {
  std::size_t events{5000U};
  std::size_t warmups{2U};
  std::size_t repetitions{9U};
  std::uint64_t seed{2026110707ULL};
};

std::uint64_t parse_unsigned(std::string_view text, std::string_view flag) {
  std::uint64_t value = 0;
  const char* begin = text.data();
  const char* end = text.data() + text.size();
  const auto parsed = std::from_chars(begin, end, value);
  if (parsed.ec != std::errc{} || parsed.ptr != end) {
    throw std::runtime_error("invalid unsigned integer for " + std::string(flag));
  }
  return value;
}

Parameters parse_parameters(int argc, char** argv) {
  Parameters parameters;
  for (int index = 1; index < argc; ++index) {
    const std::string_view flag{argv[index]};
    if (index + 1 >= argc) {
      throw std::runtime_error("missing value after " + std::string(flag));
    }
    const std::string_view value{argv[++index]};
    const std::uint64_t parsed = parse_unsigned(value, flag);
    if (flag == "--events") {
      if (parsed < 40U || parsed > static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max())) {
        throw std::runtime_error("--events must be at least 40 and fit size_t");
      }
      parameters.events = static_cast<std::size_t>(parsed);
    } else if (flag == "--warmups") {
      if (parsed == 0U || parsed > 1000U || parsed > static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max())) {
        throw std::runtime_error("--warmups must be in [1,1000]");
      }
      parameters.warmups = static_cast<std::size_t>(parsed);
    } else if (flag == "--repetitions") {
      if (parsed == 0U || parsed > 1000U || parsed > static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max())) {
        throw std::runtime_error("--repetitions must be in [1,1000]");
      }
      parameters.repetitions = static_cast<std::size_t>(parsed);
    } else if (flag == "--seed") {
      parameters.seed = parsed;
    } else {
      throw std::runtime_error("unknown argument " + std::string(flag));
    }
  }
  return parameters;
}

const char* operation_name(workload::Operation value) noexcept {
  return value == workload::Operation::insert ? "insert" : "erase";
}

const char* kind_name(workload::Kind value) noexcept {
  switch (value) {
    case workload::Kind::physical: return "physical";
    case workload::Kind::occurrence: return "occurrence";
    case workload::Kind::support: return "support";
    case workload::Kind::degree: return "degree";
    case workload::Kind::logical: return "logical";
  }
  return "unknown";
}

const char* role_name(workload::Role value) noexcept {
  switch (value) {
    case workload::Role::input: return "input";
    case workload::Role::adapter: return "adapter";
    case workload::Role::derivation: return "derivation";
    case workload::Role::survivor: return "survivor";
    case workload::Role::parent_support: return "parent_support";
    case workload::Role::visible_support: return "visible_support";
    case workload::Role::native_touched_degree: return "native_touched_degree";
    case workload::Role::generalized_probe: return "generalized_probe";
  }
  return "unknown";
}

const char* input_scope_name(workload::InputScope value) noexcept {
  return value == workload::InputScope::physical_table ? "physical_table" : "logical_epoch";
}

const char* availability_name(workload::Availability value) noexcept {
  switch (value) {
    case workload::Availability::disabled: return "disabled";
    case workload::Availability::unavailable: return "unavailable";
    case workload::Availability::exact: return "exact";
    case workload::Availability::sampled: return "sampled";
    case workload::Availability::incomplete: return "incomplete";
    case workload::Availability::lower_bound: return "lower_bound";
  }
  return "unknown";
}

void write_optional_id(std::ostream& output, const std::optional<std::size_t>& value) {
  if (value.has_value()) {
    output << static_cast<std::uint64_t>(*value);
  } else {
    output << "null";
  }
}

void write_optional_id(std::ostream& output, const std::optional<NodeId>& value) {
  if (value.has_value()) {
    output << value->value;
  } else {
    output << "null";
  }
}

void write_optional_id(std::ostream& output, const std::optional<OccurrenceId>& value) {
  if (value.has_value()) {
    output << value->value;
  } else {
    output << "null";
  }
}

void write_optional_id(std::ostream& output,
                       const std::optional<IndexRequirementId>& value) {
  if (value.has_value()) {
    output << value->value;
  } else {
    output << "null";
  }
}

void write_optional_operation(std::ostream& output,
                              const std::optional<workload::Operation>& value) {
  if (value.has_value()) {
    output << '"' << operation_name(*value) << '"';
  } else {
    output << "null";
  }
}

void write_cell(std::ostream& output, const workload::Cell& cell) {
  output << "{\"inputs\":" << cell.inputs
         << ",\"changed\":" << cell.changed
         << ",\"noop\":" << cell.noop
         << ",\"visited\":" << cell.visited
         << ",\"accepted\":" << cell.accepted
         << ",\"rejected\":" << cell.rejected
         << ",\"complete_detail_inputs\":" << cell.complete_detail_inputs
         << ",\"changes\":" << cell.changes
         << ",\"zero_to_positive\":" << cell.zero_to_positive
         << ",\"positive_to_zero\":" << cell.positive_to_zero
         << ",\"bins\":[";
  for (std::size_t index = 0; index < cell.bins.size(); ++index) {
    if (index != 0U) output << ',';
    output << cell.bins[index];
  }
  output << "],\"count\":" << cell.count
         << ",\"sum\":" << cell.sum
         << ",\"min\":" << cell.min
         << ",\"max\":" << cell.max
         << ",\"saturated\":" << (cell.saturated ? "true" : "false")
         << '}';
}

void write_collector(std::ostream& output, const workload::Snapshot& snapshot) {
  const auto& options = snapshot.options();
  const auto& modes = snapshot.modes();
  const auto& metadata = snapshot.metadata();
  const auto& memory = snapshot.memory();
  output << "{\"options\":{\"mode\":\"" << mode_name(options.mode)
         << "\",\"max_cells\":" << static_cast<std::uint64_t>(options.max_cells)
         << ",\"period\":" << options.period
         << ",\"offset\":" << options.offset
         << ",\"detail_budget\":" << options.detail_budget
         << "},\"mode_facts\":{\"delta_owner\":" << (modes.delta_owner ? "true" : "false")
         << ",\"requested_mode\":\"" << (modes.requested_mode == DeltaMode::maintenance ? "maintenance" : "delta")
         << "\",\"resolved_mode\":\"" << (modes.resolved_mode == DeltaMode::maintenance ? "maintenance" : "delta")
         << "\",\"requested_completion\":\""
         << (modes.requested_completion == DeltaCompletion::automatic ? "automatic" :
             modes.requested_completion == DeltaCompletion::ordered_replay ? "ordered_replay" :
             modes.requested_completion == DeltaCompletion::anchored ? "anchored" : "root_first")
         << "\",\"resolved_completion\":\""
         << (modes.resolved_completion == DeltaCompletion::automatic ? "automatic" :
             modes.resolved_completion == DeltaCompletion::ordered_replay ? "ordered_replay" :
             modes.resolved_completion == DeltaCompletion::anchored ? "anchored" : "root_first")
         << "\",\"live_maintenance\":\""
         << (modes.live_maintenance == LiveMaintenance::on_output ? "on_output" :
             modes.live_maintenance == LiveMaintenance::incremental ? "incremental" : "eager")
         << "\",\"view\":\"" << (modes.view == ResultView::sql ? "sql" : "core")
         << "\"},\"pending\":" << (snapshot.pending() ? "true" : "false")
         << ",\"detail_availability\":\"" << availability_name(snapshot.detail_availability())
         << "\",\"coverage\":{\"status\":\""
         << (options.mode == workload::Mode::off ? "unavailable_disabled"
                                                   : availability_name(snapshot.detail_availability()))
         << "\",\"attempts\":";
  if (options.mode == workload::Mode::off) output << "null";
  else output << metadata.attempts;
  output << ",\"committed\":";
  if (options.mode == workload::Mode::off) output << "null";
  else output << metadata.committed;
  output << ",\"selected\":";
  if (options.mode == workload::Mode::off) output << "null";
  else output << metadata.selected;
  output << ",\"complete\":";
  if (options.mode == workload::Mode::off) output << "null";
  else output << metadata.complete;
  output << "},\"metadata\":{\"attempts\":" << metadata.attempts
         << ",\"committed\":" << metadata.committed
         << ",\"aborted\":" << metadata.aborted
         << ",\"selected\":" << metadata.selected
         << ",\"complete\":" << metadata.complete
         << ",\"aborted_selected\":" << metadata.aborted_selected
         << ",\"truncated\":" << metadata.truncated
         << ",\"committed_truncated\":" << metadata.committed_truncated
         << ",\"guards\":" << metadata.guards
         << ",\"detail_actions\":" << metadata.detail_actions
         << ",\"cleared_cells\":" << metadata.cleared_cells
         << ",\"merged_cells\":" << metadata.merged_cells
         << ",\"saturated\":" << (metadata.saturated ? "true" : "false")
         << ",\"invalid_descriptor\":" << (metadata.invalid_descriptor ? "true" : "false")
         << ",\"protocol_error\":" << (metadata.protocol_error ? "true" : "false")
         << ",\"ordinal_exhausted\":" << (metadata.ordinal_exhausted ? "true" : "false")
         << "},\"memory\":{\"object_bytes\":" << static_cast<std::uint64_t>(memory.object_bytes)
         << ",\"descriptors_bytes\":" << static_cast<std::uint64_t>(memory.descriptors_bytes)
         << ",\"committed_bytes\":" << static_cast<std::uint64_t>(memory.committed_bytes)
         << ",\"attempt_bytes\":" << static_cast<std::uint64_t>(memory.attempt_bytes)
         << ",\"previous_bytes\":" << static_cast<std::uint64_t>(memory.previous_bytes)
         << ",\"retained_payload_bytes\":" << static_cast<std::uint64_t>(memory.retained_payload_bytes)
         << ",\"routes_bytes\":" << static_cast<std::uint64_t>(memory.routes_bytes)
         << "},\"descriptor_count\":" << static_cast<std::uint64_t>(snapshot.descriptors().size())
         << ",\"cell_count\":" << static_cast<std::uint64_t>(snapshot.cells().size())
         << ",\"descriptors\":[";
  const auto descriptors = snapshot.descriptors();
  const auto cells = snapshot.cells();
  if (descriptors.size() != cells.size()) {
    throw std::runtime_error("C01 descriptor and cell vectors differ in length");
  }
  for (std::size_t index = 0; index < descriptors.size(); ++index) {
    if (index != 0U) output << ',';
    const auto& descriptor = descriptors[index];
    output << "{\"kind\":\"" << kind_name(descriptor.kind)
           << "\",\"table\":" << descriptor.table
           << ",\"scope\":" << descriptor.scope
           << ",\"operation\":\"" << operation_name(descriptor.operation)
           << "\",\"input_scope\":\"" << input_scope_name(descriptor.input_scope)
           << "\",\"role\":\"" << role_name(descriptor.role)
           << "\",\"node\":";
    write_optional_id(output, descriptor.node);
    output << ",\"occurrence\":";
    write_optional_id(output, descriptor.occurrence);
    output << ",\"edge\":";
    write_optional_id(output, descriptor.edge);
    output << ",\"index\":";
    write_optional_id(output, descriptor.index);
    output << ",\"event_operation\":";
    write_optional_operation(output, descriptor.event_operation);
    output << ",\"cell\":";
    write_cell(output, cells[index]);
    output << '}';
  }
  output << "]}";
}

void write_o07(std::ostream& output, const O07Facts& facts) {
  output << "{\"observation_mode\":\"" << observation_name(facts.options.mode)
         << "\",\"trace_capacity\":" << static_cast<std::uint64_t>(facts.options.trace_capacity)
         << ",\"sample_period\":" << facts.options.sample_period
         << ",\"sample_offset\":" << facts.options.sample_offset
         << ",\"trace_timings\":" << (facts.options.trace_timings ? "true" : "false")
         << ",\"capture_transitions\":" << (facts.capture_transitions ? "true" : "false")
         << ",\"delta_owner\":" << (facts.delta_owner ? "true" : "false")
         << ",\"delta_mode\":";
  if (facts.delta_mode.has_value()) {
    output << '"' << (*facts.delta_mode == DeltaMode::maintenance ? "maintenance" : "delta") << '"';
  } else output << "null";
  output << ",\"live_maintenance\":";
  if (facts.live_maintenance.has_value()) {
    output << '"' << (*facts.live_maintenance == LiveMaintenance::on_output ? "on_output" :
                        *facts.live_maintenance == LiveMaintenance::incremental ? "incremental" : "eager") << '"';
  } else output << "null";
  output << ",\"completion\":";
  if (facts.completion.has_value()) {
    const auto value = *facts.completion;
    output << '"' << (value == DeltaCompletion::automatic ? "automatic" :
                        value == DeltaCompletion::ordered_replay ? "ordered_replay" :
                        value == DeltaCompletion::anchored ? "anchored" : "root_first") << '"';
  } else output << "null";
  output << ",\"result_view\":";
  if (facts.result_view.has_value()) {
    output << '"' << (*facts.result_view == ResultView::sql ? "sql" : "core") << '"';
  } else output << "null";
  output << '}';
}

void write_mandatory(std::ostream& output, const MandatoryTotals& totals) {
  output << "{\"physical_work\":" << totals.physical_work
         << ",\"support_work\":" << totals.support_work
         << ",\"delta_work\":" << totals.delta_work
         << ",\"source_changes\":" << totals.source_changes
         << ",\"aliases_visited\":" << totals.aliases_visited
         << ",\"aliases_filtered\":" << totals.aliases_filtered
         << ",\"derivation_changes\":" << totals.derivation_changes
         << ",\"native_crossings\":" << totals.native_crossings
         << ",\"native_record_visits\":" << totals.native_record_visits
         << ",\"child_key_probes\":" << totals.child_key_probes
         << ",\"child_key_events\":" << totals.child_key_events
         << ",\"survivor_transitions\":" << totals.survivor_transitions
         << ",\"parent_key_transitions\":" << totals.parent_key_transitions
         << ",\"visible_key_transitions\":" << totals.visible_key_transitions
         << ",\"storage_changes\":" << totals.storage_changes
         << ",\"journal_records\":" << totals.journal_records
         << ",\"events_applied\":" << totals.events_applied
         << ",\"delta_candidates\":" << totals.delta_candidates
         << ",\"delta_accepted\":" << totals.delta_accepted
         << ",\"delta_rejected\":" << totals.delta_rejected
         << ",\"delta_spool_rows\":" << totals.delta_spool_rows
         << ",\"drained_output_records\":" << totals.drained_output_records << '}';
}

void write_validation(std::ostream& output, const Validation& validation) {
  output << "{\"source_checksum\":\"" << hex64(validation.source_checksum)
         << "\",\"support_checksum\":\"" << hex64(validation.support_checksum)
         << "\",\"result_checksum\":\"" << hex64(validation.result_checksum)
         << "\",\"semantic_checksum\":\"" << hex64(validation.semantic_checksum)
         << "\",\"source_rows\":{\"R\":" << validation.source_r_rows
         << ",\"S\":" << validation.source_s_rows
         << ",\"unused\":" << validation.unused_rows
         << "},\"support_rows\":{\"R_records\":" << validation.root_records
         << ",\"R_survivors\":" << validation.root_survivors
         << ",\"S_records\":" << validation.child_records
         << ",\"S_survivors\":" << validation.child_survivors
         << "},\"result_rows\":" << validation.result_rows << '}';
}

std::uint64_t median(std::vector<std::uint64_t> values) {
  std::sort(values.begin(), values.end());
  const std::size_t middle = values.size() / 2U;
  if ((values.size() % 2U) == 1U) return values[middle];
  return values[middle - 1U] + (values[middle] - values[middle - 1U]) / 2U;
}

struct ProfileResults {
  Scenario scenario{};
  C01Profile profile{};
  std::vector<std::uint64_t> durations;
  std::vector<Validation> validations;
  workload::Snapshot collector;
  O07Facts o07;
  MandatoryTotals mandatory;
};

ProfileResults run_profile(const Fixture& fixture,
                           const std::vector<PhysicalSetUpdate>& events,
                           const Database& expected,
                           std::uint64_t trace_checksum,
                           Scenario scenario,
                           C01Profile profile,
                           const Parameters& parameters,
                           std::optional<MandatoryTotals>& scenario_mandatory_baseline,
                           std::optional<Validation>& global_validation_baseline) {
  std::optional<MandatoryTotals> collected_mandatory;
  std::optional<Validation> profile_validation;
  std::optional<workload::Snapshot> final_snapshot;
  std::optional<O07Facts> final_o07;
  std::vector<std::uint64_t> durations;
  std::vector<Validation> validations;
  durations.reserve(parameters.repetitions);
  validations.reserve(parameters.repetitions);

  for (std::size_t warmup = 0; warmup < parameters.warmups; ++warmup) {
    const bool collect = warmup == 0U;
    TrialResult trial = scenario == Scenario::physical
        ? run_physical(fixture, events, expected, trace_checksum, profile, false, collect)
        : run_delta(fixture, events, expected, trace_checksum, profile, false, collect);
    if (collect) {
      if (!trial.mandatory.has_value()) {
        throw std::runtime_error("untimed mandatory-work warmup did not collect its totals");
      }
      collected_mandatory = trial.mandatory;
      profile_validation = trial.validation;
    } else if (profile_validation.has_value() &&
               trial.validation.semantic_checksum != profile_validation->semantic_checksum) {
      throw std::runtime_error("warmup semantic checksum differs within a profile");
    }
  }

  if (!collected_mandatory.has_value() || !profile_validation.has_value()) {
    throw std::runtime_error("at least one warmup is required for mandatory-work capture");
  }
  if (scenario_mandatory_baseline.has_value() &&
      *scenario_mandatory_baseline != *collected_mandatory) {
    throw std::runtime_error("mandatory work changed across C01 collection profiles");
  }
  scenario_mandatory_baseline = collected_mandatory;
  if (global_validation_baseline.has_value() &&
      global_validation_baseline->semantic_checksum != profile_validation->semantic_checksum) {
    throw std::runtime_error("source/support/result checksum changed across profiles");
  }
  global_validation_baseline = profile_validation;

  for (std::size_t repetition = 0; repetition < parameters.repetitions; ++repetition) {
    TrialResult trial = scenario == Scenario::physical
        ? run_physical(fixture, events, expected, trace_checksum, profile, true, false)
        : run_delta(fixture, events, expected, trace_checksum, profile, true, false);
    if (trial.duration_ns == 0U ||
        trial.validation.semantic_checksum != profile_validation->semantic_checksum) {
      throw std::runtime_error("measured repetition duration or semantic guard differs");
    }
    durations.push_back(trial.duration_ns);
    validations.push_back(trial.validation);
    final_snapshot = std::move(trial.collector);
    final_o07 = trial.o07;
  }
  if (!final_snapshot.has_value() || !final_o07.has_value()) {
    throw std::runtime_error("measured repetitions did not produce configuration snapshots");
  }
  return ProfileResults{scenario, profile, std::move(durations), std::move(validations),
                        std::move(*final_snapshot), *final_o07,
                        *collected_mandatory};
}

void write_profile(std::ostream& output,
                   const ProfileResults& result,
                   const Parameters& parameters) {
  const auto& validation = result.validations.back();
  const auto& options = result.collector.options();
  const std::uint64_t median_ns = median(result.durations);
  std::vector<std::uint64_t> deviations;
  deviations.reserve(result.durations.size());
  for (const auto value : result.durations) {
    deviations.push_back(value > median_ns ? value - median_ns : median_ns - value);
  }
  const std::uint64_t mad_ns = median(deviations);
  const auto [min_it, max_it] = std::minmax_element(result.durations.begin(),
                                                   result.durations.end());
  const double throughput = static_cast<double>(parameters.events) * 1000000000.0 /
                            static_cast<double>(median_ns);

  output << "{\"scenario\":\"" << scenario_name(result.scenario)
         << "\",\"c01_mode_from_snapshot\":\"" << mode_name(options.mode)
         << "\",\"o07_configuration_from_owner\":";
  write_o07(output, result.o07);
  output << ",\"warmups\":" << static_cast<std::uint64_t>(parameters.warmups)
         << ",\"repetitions\":" << static_cast<std::uint64_t>(parameters.repetitions)
         << ",\"timing_scope\":\"update_stream_only\",\"durations_ns\":[";
  for (std::size_t index = 0; index < result.durations.size(); ++index) {
    if (index != 0U) output << ',';
    output << result.durations[index];
  }
  output << "],\"summary\":{\"median_ns\":" << median_ns
         << ",\"min_ns\":" << *min_it
         << ",\"max_ns\":" << *max_it
         << ",\"median_absolute_deviation_ns\":" << mad_ns
         << ",\"median_events_per_second\":" << std::setprecision(12) << throughput
         << "},\"mandatory_work_from_untimed_warmup\":";
  write_mandatory(output, result.mandatory);
  output << ",\"validation\":";
  write_validation(output, validation);
  output << ",\"collector_from_last_repetition\":";
  write_collector(output, result.collector);
  output << ",\"run_checksums\":[";
  for (std::size_t index = 0; index < result.validations.size(); ++index) {
    if (index != 0U) output << ',';
    output << "{\"source\":\"" << hex64(result.validations[index].source_checksum)
           << "\",\"support\":\"" << hex64(result.validations[index].support_checksum)
           << "\",\"result\":\"" << hex64(result.validations[index].result_checksum)
           << "\",\"semantic\":\"" << hex64(result.validations[index].semantic_checksum)
           << "\"}";
  }
  output << "]}";
}

void write_trace_summary(std::ostream& output,
                         const TraceSummary& summary,
                         std::size_t events) {
  output << "{\"events\":" << static_cast<std::uint64_t>(events)
         << ",\"seeded_trace_checksum\":\"" << hex64(summary.checksum)
         << "\",\"R_insert\":" << summary.r_insert
         << ",\"R_erase\":" << summary.r_erase
         << ",\"S_insert\":" << summary.s_insert
         << ",\"S_erase\":" << summary.s_erase
         << ",\"changed_inputs\":" << summary.changed_inputs
         << ",\"noop_inputs\":" << summary.noop_inputs
         << ",\"changed_S_inputs\":" << summary.changed_s_inputs
         << ",\"changed_S_parent_bucket_sizes\":[";
  std::size_t index = 0;
  for (const auto size : summary.changed_s_bucket_sizes) {
    if (index != 0U) output << ',';
    output << size;
    ++index;
  }
  output << "]}";
}

void write_parameters(std::ostream& output, const Parameters& parameters) {
  output << "{\"events\":" << static_cast<std::uint64_t>(parameters.events)
         << ",\"warmups\":" << static_cast<std::uint64_t>(parameters.warmups)
         << ",\"repetitions\":" << static_cast<std::uint64_t>(parameters.repetitions)
         << ",\"seed\":" << parameters.seed << '}';
}

void write_environment_value(std::ostream& output, const char* name) {
  const char* value = std::getenv(name);
  if (value == nullptr) {
    output << "null";
    return;
  }
  output << '"';
  for (const char* current = value; *current != '\0'; ++current) {
    if (*current == '"' || *current == '\\') {
      output << '\\' << *current;
    } else if (*current == '\n') {
      output << "\\n";
    } else if (*current == '\r') {
      output << "\\r";
    } else if (*current == '\t') {
      output << "\\t";
    } else {
      output << *current;
    }
  }
  output << '"';
}

int run(const Parameters& parameters) {
  Fixture fixture;
  TraceSummary trace_summary;
  const auto events = make_trace(parameters.events, parameters.seed,
                                 fixture.initial, trace_summary);
  const Database expected = replay_literal(fixture.initial, events);

  constexpr std::array<Scenario, 2> scenarios{
      Scenario::physical, Scenario::delta_maintenance};
  constexpr std::array<C01Profile, 3> profiles{
      C01Profile::off, C01Profile::census, C01Profile::sampled};
  std::vector<ProfileResults> results;
  results.reserve(scenarios.size() * profiles.size());
  std::optional<Validation> validation_baseline;
  for (const auto scenario : scenarios) {
    std::optional<MandatoryTotals> mandatory_baseline;
    for (const auto profile : profiles) {
      results.push_back(run_profile(
          fixture, events, expected, trace_summary.checksum, scenario, profile,
          parameters, mandatory_baseline, validation_baseline));
    }
  }
  if (trace_summary.changed_s_bucket_sizes.size() < 2U) {
    throw std::runtime_error("input trace did not vary S changes across reverse-index degrees");
  }

  std::cout << "{\"format\":\"crown_c01_native_statistics_benchmark_v1\""
            << ",\"benchmark_kind\":\"native_update_stream\""
            << ",\"compiler\":{\"version\":\"" << __VERSION__
            << "\",\"standard\":\"C++23\",\"runtime_flags\":\"-std=c++23 -O3 -DNDEBUG -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror -pthread\"}"
            << ",\"machine\":";
  write_environment_value(std::cout, "CROWN_BENCH_MACHINE");
  std::cout << ",\"run_condition\":";
  write_environment_value(std::cout, "CROWN_BENCH_RUN_CONDITION");
  std::cout << ",\"parameters\":";
  write_parameters(std::cout, parameters);
  std::cout << ",\"input_trace\":";
  write_trace_summary(std::cout, trace_summary, parameters.events);
  std::cout << ",\"fixture\":{\"query\":\"R(x,y,ignored) join S(y), output (x,y)\",\"tree\":\"native R root with native S child\",\"catalogued_unused_table\":true,\"R_slots\":"
            << static_cast<std::uint64_t>(slot_count)
            << ",\"S_keys\":" << static_cast<std::uint64_t>(key_count)
            << ",\"setup_timed\":false,\"plan_lowering_timed\":false,\"owner_initialization_timed\":false,\"collector_configuration_timed\":false}"
            << ",\"profiles\":[";
  for (std::size_t index = 0; index < results.size(); ++index) {
    if (index != 0U) std::cout << ',';
    write_profile(std::cout, results[index], parameters);
  }
  std::cout << "]}\n";
  return 0;
}
}  // namespace

int main(int argc, char** argv) {
  try {
    return run(parse_parameters(argc, argv));
  } catch (const std::exception& error) {
    std::cerr << "crown_c01_native_benchmark: " << error.what() << '\n';
    return 1;
  }
}
