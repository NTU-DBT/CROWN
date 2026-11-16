// Exercise the common types and shared-owner native interfaces.
#include "crown/storage/indexed.hpp"
#include "crown/storage/reference.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

using namespace crown;
using namespace crown::storage;

namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
template <class Function>
void rejects(std::string_view code, Function&& function) {
  bool rejected = false;
  try { function(); }
  catch (const Error& error) { verify(error.code() == code, "wrong error code");rejected = true; }
  verify(rejected, "operation unexpectedly succeeded");
}
IndexWorkAllowance ample() {
  return IndexWorkAllowance(IndexWork{100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000});
}
IndexedLimits limits() { return {64, 8, 256, 512, 1024, 4096, 96, 32}; }

void foreign_owners_and_tokens() {
  TupleLayout layout(LayoutId{1}, {{ScalarType::int64}});
  // Run first in this executable. Two independently initialized owner counters
  // would both issue1 here; different logical tuple IDs cannot hide the defect.
  IndexedTable indexed(RelationId{1}, layout, limits());
  ReferenceTable reference(RelationId{1}, layout);
  verify(indexed.owner() != reference.owner(), "reference/optimized owners collided");
  const auto tuple = layout.tuple(Row{std::int64_t{7}});auto work = ample();
  const auto native = indexed.insert(tuple, work), oracle = reference.insert(tuple);
  verify(native.handle.tuple == oracle.handle.tuple, "fresh logical tuple IDs differ");
  rejects("foreign_handle", [&] { static_cast<void>(indexed.get(oracle.handle, work)); });
  rejects("foreign_handle", [&] { static_cast<void>(reference.get(native.handle)); });
  rejects("foreign_handle", [&] {
    auto handle = native.handle;handle.relation = RelationId{99};static_cast<void>(indexed.get(handle, work));
  });
  TupleLayout reconstructed(LayoutId{1}, std::vector<Field>(layout.fields().begin(),layout.fields().end()));
  const auto foreign = reconstructed.tuple(Row{std::int64_t{7}});
  const auto before = indexed.statistics();
  rejects("layout_mismatch", [&] { static_cast<void>(indexed.insert(foreign, work)); });
  rejects("layout_mismatch", [&] { static_cast<void>(indexed.find(foreign, work)); });
  verify(indexed.statistics() == before, "foreign layout changed optimized state");
  indexed.check_invariants();reference.check_invariants();
}

void literal_membership_and_lifecycle() {
  TupleLayout layout(LayoutId{11}, {{ScalarType::int64}, {ScalarType::string}});
  TupleLayout integer_key(LayoutId{12}, {{ScalarType::int64}});
  TupleLayout empty_key(LayoutId{13}, {});
  Projection integer(layout, integer_key, {FieldId{0}}), empty(layout, empty_key, {});
  Projection independent(layout, integer_key, {FieldId{0}});
  IndexedTable table(RelationId{1}, layout, limits());auto work = ample();
  const auto integer_index = table.add_index(integer, work);
  verify(table.add_index(integer, work) == integer_index, "same projection token was not idempotent");
  const auto separate_index = table.add_index(independent, work), nullary = table.add_index(empty, work);
  verify(separate_index != integer_index, "independent equal projection shared an index ID");
  const std::int64_t large = (std::int64_t{1} << 53U) + 116;
  const auto zero = layout.tuple(Row{std::int64_t{0}, std::string("zero")});
  const auto first = layout.tuple(Row{large, std::string("z\0\xff", 3)});
  const auto second = layout.tuple(Row{large + 1, std::string("next")});
  const auto a = table.insert(zero, work), b = table.insert(first, work), c = table.insert(second, work);
  const auto before_duplicate = table.statistics();const auto revision = table.revision();
  verify(!table.insert(first, work).inserted && table.find(first, work) == b.handle,
         "duplicate insertion changed membership/identity");
  verify(table.statistics() == before_duplicate && table.revision() == revision, "duplicate changed counters/revision");
  verify(table.bucket(integer_index, integer_key.tuple(Row{large}), work) == std::vector<TupleHandle>{b.handle} &&
      table.bucket(integer_index, integer_key.tuple(Row{large + 1}), work) == std::vector<TupleHandle>{c.handle},
      "distinct integers above double precision were merged");
  verify(table.bucket(integer_index, integer_key.tuple(Row{std::int64_t{0}}), work) == std::vector<TupleHandle>{a.handle},
         "zero payload became an absence sentinel");
  verify(table.bucket(nullary, empty_key.tuple({}), work) == std::vector<TupleHandle>{a.handle, b.handle, c.handle},
         "nullary bucket membership/order differs");
  const auto snapshot = table.snapshot(work);
  verify(snapshot.size() == 3 && snapshot[0] == zero && snapshot[1] == first && snapshot[2] == second,
         "live snapshot insertion order differs");
  auto retained = table.pin(b.handle, work);const auto arena_identity = retained.handle();
  verify(table.erase_key(integer_index, integer_key.tuple(Row{large}), work) == 1 && !table.get(b.handle, work),
         "key erase did not remove exactly its row");
  verify(retained.get() == first && !retained.is_live(), "erase lost pinned payload or retained membership");
  verify(table.erase_key(integer_index, integer_key.tuple(Row{large}), work) == 0, "absent key erase changed membership");
  const auto before_absent = table.statistics();
  verify(!table.erase(b.handle, work) && !table.drop_index(IndexId{999}, work), "absent operation reported a change");
  verify(table.statistics() == before_absent, "absent operation changed counters");
  verify(table.drop_index(separate_index, work), "registered index did not drop");
  const auto recreated = table.add_index(independent, work);
  verify(recreated.value > nullary.value && table.projection(recreated, work).same_token(independent),
         "dropped index ID was reused or projection token changed");
  table.clear(work);verify(table.size() == 0 && table.key_count(integer_index, work) == 0,
                           "clear retained public rows/keys");
  verify(retained.get() == first && retained.handle() == arena_identity, "clear changed pinned allocation identity");
  table.check_invariants();
  const auto next = table.insert(first, work);
  verify(next.handle.tuple.value > c.handle.tuple.value, "committed clear reused a logical ID");
  IndexedTable moved(std::move(table));
  verify(moved.get(next.handle, work) && retained.get() == first, "move changed actual owner/pin lifetime");
  rejects("invalid_storage", [&] { static_cast<void>(table.size()); });
  moved.check_invariants();
}

void literal_work_and_capacity_boundaries() {
  TupleLayout layout(LayoutId{21}, {{ScalarType::int64}});
  const auto tuple = layout.tuple(Row{std::int64_t{0}});
  const IndexedLimits one{1, 0, 0, 0, 1, 16, 1, 0};
  // One empty primary and one ID directory: two eight-slot arrays, four fixed
  // structural phases, two scalar passes for hash/copy, and two nine-link inserts.
  const IndexWork exact{4, 4, 25, 16, 18};
  {
    IndexedTable table(RelationId{1}, layout, one);IndexWorkAllowance work(exact);
    verify(table.insert(tuple, work).inserted && work.remaining() == IndexWork{}, "literal exact insertion work differs");
    table.check_invariants();
  }
  for (int domain = 0; domain != 5; ++domain) {
    auto limit = exact;
    if (domain == 0) --limit.structural_steps;
    if (domain == 1) --limit.scalar_fields;
    if (domain == 2) --limit.scalar_bytes;
    if (domain == 3) --limit.pointer_slots;
    if (domain == 4) --limit.link_actions;
    IndexedTable table(RelationId{1}, layout, one);const auto before = table.statistics();IndexWorkAllowance work(limit);
    rejects("storage_work_limit", [&] { static_cast<void>(table.insert(tuple, work)); });
    verify(table.statistics() == before && table.revision() == 0, "one-under work limit published partial state");
    table.check_invariants();
  }
  for (int domain = 0; domain != 4; ++domain) {
    auto config = one;
    if (domain == 0) config.rows = 0;
    if (domain == 1) config.nodes = 0;
    if (domain == 2) config.directory_slots = 15;
    if (domain == 3) config.arena_slots = 0;
    IndexedTable table(RelationId{1}, layout, config);const auto before = table.statistics();auto work = ample();
    rejects("storage_capacity", [&] { static_cast<void>(table.insert(tuple, work)); });
    verify(table.statistics() == before, "one-under component limit published partial state");
    table.check_invariants();
  }
}

void atomic_index_build_and_pin_retention() {
  TupleLayout layout(LayoutId{31}, {{ScalarType::int64}});
  TupleLayout key_layout(LayoutId{32}, {{ScalarType::int64}});Projection projection(layout, key_layout, {FieldId{0}});
  auto config = limits();config.keys = 1;
  IndexedTable table(RelationId{1}, layout, config);auto work = ample();
  const auto first = table.insert(layout.tuple(Row{std::int64_t{1}}), work);
  const auto second = table.insert(layout.tuple(Row{std::int64_t{2}}), work);
  const auto before = table.statistics();
  rejects("storage_capacity", [&] { static_cast<void>(table.add_index(projection, work)); });
  verify(table.statistics() == before && table.indices(work).empty(), "failed index build changed existing rows/counters");
  table.check_invariants();verify(table.erase(second.handle, work), "failed build damaged original row identity");
  verify(table.add_index(projection, work) == IndexId{1} && table.get(first.handle, work),
         "failed index build consumed an ID or prevented a valid retry");
  table.check_invariants();

  IndexedLimits tight{1, 0, 0, 0, 1, 16, 1, 1};
  IndexedTable pinned(RelationId{1}, layout, tight);
  const auto original = layout.tuple(Row{std::int64_t{7}});const auto original_handle = pinned.insert(original, work).handle;
  auto pin = pinned.pin(original_handle, work);const auto allocation = pin.handle();
  rejects("storage_capacity", [&] { static_cast<void>(pinned.pin(original_handle, work)); });
  pinned.clear(work);
  const auto retained = pinned.statistics();
  rejects("storage_capacity", [&] { static_cast<void>(pinned.insert(layout.tuple(Row{std::int64_t{8}}), work)); });
  verify(pinned.statistics() == retained && pin.get() == original && !pin.is_live(),
         "external retention exceeded its slot cap or lost the old tuple");
  pin.reset();const auto next = pinned.insert(layout.tuple(Row{std::int64_t{8}}), work).handle;
  auto next_pin = pinned.pin(next, work);
  verify(next.tuple.value == original_handle.tuple.value + 1 && next_pin.handle().slot == allocation.slot &&
      next_pin.handle().generation != allocation.generation, "released slot did not reuse with a fresh allocation/logical ID");
  pinned.check_invariants();
}
}  // namespace

int main() {
  foreign_owners_and_tokens();literal_membership_and_lifecycle();
  literal_work_and_capacity_boundaries();atomic_index_build_and_pin_retention();
  std::cout << "S04 typed table draft: exact membership, atomic limits, shared owners and retained pins passed\n";
}
