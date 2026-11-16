#include "crown/storage/indexed.hpp"
#include "index_allocation.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "indexed_testing.hpp"
#endif
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && !defined(CROWN_STORAGE_TESTING)
#error "Collision copy fixture requires the coherent testing storage library"
#endif

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
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
IndexedLimits limits() { return {16, 8, 64, 128, 256, 2048, 32, 8}; }

void checked_sparse_copy_and_faults() {
  TupleLayout layout(LayoutId{1}, {{ScalarType::int64}, {ScalarType::int64}});
  TupleLayout key_layout(LayoutId{2}, {{ScalarType::int64}});
  Projection group(layout, key_layout, {FieldId{1}}), dummy(layout, key_layout, {FieldId{0}});
  IndexedTable source(RelationId{1}, layout, limits());auto work = ample();
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
  detail::IndexedTesting::collisions(source, detail::CollisionMode::same_bucket);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 2
  detail::IndexedTesting::collisions(source, detail::CollisionMode::same_full_hash);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE)
#error "Unknown collision copy fixture profile"
#endif
  const auto removed_index = source.add_index(dummy, work);verify(source.drop_index(removed_index, work), "index-gap fixture failed");
  const auto index = source.add_index(group, work);
  const auto highest_index = source.add_index(dummy, work);verify(source.drop_index(highest_index, work), "index high-water fixture failed");
  const auto a = layout.tuple(Row{std::int64_t{1}, std::int64_t{9}});
  const auto b = layout.tuple(Row{std::int64_t{2}, std::int64_t{10}});
  const auto c = layout.tuple(Row{std::int64_t{3}, std::int64_t{9}});
  const auto d = layout.tuple(Row{std::int64_t{4}, std::int64_t{11}});
  const auto a_id = source.insert(a, work).handle, b_id = source.insert(b, work).handle;
  const auto c_id = source.insert(c, work).handle, d_id = source.insert(d, work).handle;
  auto live_pin = source.pin(b_id, work), retired_pin = source.pin(d_id, work);
  verify(source.erase(a_id, work) && source.erase(d_id, work), "sparse-row fixture failed");
  // Current rows are B,C, but key9 stayed live through C after A disappeared.
  // Its first-live position predates key10; a plain index rebuild gives10,9.
  const auto expected_keys = std::vector<Tuple>{key_layout.tuple(Row{std::int64_t{9}}),
      key_layout.tuple(Row{std::int64_t{10}})};
  verify(source.keys(index, work) == expected_keys && source.snapshot(work) == std::vector<Tuple>{b, c},
         "historical key order did not differ from current row order");
  const auto initial_stats = source.statistics();const auto initial_revision = source.revision();
  const auto retained_address = &retired_pin.get();auto untouched_cursor = source.live(work);

  auto check_source = [&] {
    verify(source.statistics() == initial_stats && source.revision() == initial_revision &&
        source.snapshot(work) == std::vector<Tuple>{b, c} && source.keys(index, work) == expected_keys &&
        source.find(b, work) == b_id && source.find(c, work) == c_id &&
        &retired_pin.get() == retained_address && retired_pin.get() == d && !retired_pin.is_live() && live_pin.is_live(),
        "copy attempt changed source data, IDs, counters, revision or retained pins");
    source.check_invariants();
  };
  auto check_copy = [&](IndexedTable& copy, std::uint64_t expected_revision) {
    verify(copy.owner() != source.owner() && copy.revision() == expected_revision &&
        copy.snapshot(work) == std::vector<Tuple>{b, c} && copy.indices(work) == std::vector<IndexId>{index} &&
        copy.keys(index, work) == expected_keys && copy.projection(index, work).same_token(group),
        "owning copy changed owner boundary, sparse index or traversal order");
    const auto copied_b = copy.find(b, work), copied_c = copy.find(c, work);
    verify(copied_b && copied_c && copied_b->tuple == b_id.tuple && copied_c->tuple == c_id.tuple &&
        copy.get(*copied_b, work) != source.get(b_id, work), "owning copy renumbered/aliased tuple allocations");
    rejects("foreign_handle", [&] { static_cast<void>(copy.get(b_id, work)); });
    const auto stats = copy.statistics();
    verify(stats.arena.slots == 2 && stats.arena.live_records == 2 && stats.arena.retained_records == 0 &&
        stats.arena.pins == 0 && stats.copied_rows == 2 && stats.copied_indices == 1 && stats.committed == IndexedActions{},
        "copy inherited retired payloads/pins or source-owner committed actions");
#ifdef CROWN_STORAGE_COLLISION_PROFILE
    const auto missing = layout.tuple(Row{std::int64_t{9}, std::int64_t{999}});
#if CROWN_STORAGE_COLLISION_PROFILE == 1
    verify((b.hash() & ~std::uint64_t{0xffff}) != (missing.hash() & ~std::uint64_t{0xffff}) &&
        (c.hash() & ~std::uint64_t{0xffff}) != (missing.hash() & ~std::uint64_t{0xffff}),
        "copy bucket-only fixture accidentally has an equal full hash");
    IndexWorkAllowance collision(IndexWork{4, 4, 26, 0, 0});
#else
    IndexWorkAllowance collision(IndexWork{4, 20, 90, 0, 0});
#endif
    verify(!copy.find(missing, collision) && collision.remaining() == IndexWork{},
           "owning copy did not preserve the actual collision profile/path");
#endif
    copy.check_invariants();
  };

  std::size_t positions = 0;
  auto measured_copy = [&] {
    auto allowance = ample();s04_alloc::Scope measure;
    auto result = source.snapshot_copy(allowance);positions = s04_alloc::calls;return result;
  }();
  verify(positions > 0 && !s04_alloc::triggered, "copy allocation baseline did not complete");
  check_copy(measured_copy, initial_revision);check_source();
  verify(untouched_cursor.next(work)->handle == b_id, "successful copy invalidated a source cursor");
  for (std::size_t position = 0; position < positions; ++position) {
    verify(position <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()), "fault position exceeds injector domain");
    auto cursor = source.live(work);auto allowance = ample();bool failed = false;
    try {
      s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(position));
      auto abandoned = source.snapshot_copy(allowance);static_cast<void>(abandoned);
    } catch (const std::bad_alloc&) { failed = true; }
    verify(failed && s04_alloc::triggered, "copy failed to reach or propagate a persistent fault position");
    check_source();verify(cursor.next(work)->handle == b_id, "failed copy invalidated an existing source cursor");
  }
  IndexWorkAllowance no_body(IndexWork{10'000, 10'000, 0, 100'000, 100'000});
  rejects("storage_work_limit", [&] { static_cast<void>(source.snapshot_copy(no_body)); });check_source();
  auto retry_work = ample();auto retry = source.snapshot_copy(retry_work);check_copy(retry, initial_revision);check_source();
  const auto next = layout.tuple(Row{std::int64_t{5}, std::int64_t{12}});
  verify(retry.insert(next, work).handle.tuple.value == d_id.tuple.value + 1,
         "owning copy lost a deleted tuple-ID high-water counter");
  verify(retry.add_index(dummy, work).value == highest_index.value + 1,
         "owning copy lost a deleted index-ID high-water counter");
  retry.check_invariants();check_source();
  retry.clear(work);retry.check_invariants();
  verify(source.snapshot(work) == std::vector<Tuple>{b, c}, "copy clear changed the source");
  // Recopy an owner with a copied baseline and later committed mutations.
  const auto temporary = measured_copy.insert(next, work).handle;
  verify(measured_copy.erase(temporary, work), "copied-owner mutation fixture failed");
  measured_copy.check_invariants();
  auto third_work = ample();auto third = measured_copy.snapshot_copy(third_work);
  check_copy(third, measured_copy.revision());third.check_invariants();
  verify(third.insert(next, work).handle.tuple.value == temporary.tuple.value + 1,
         "copy of a copied owner lost later logical-ID history");
  third.check_invariants();check_source();
}
}  // namespace

int main() {
  checked_sparse_copy_and_faults();
  std::cout << "S04 owning copy draft: sparse identity/order, fresh owners, all observed persistent faults and retry passed\n";
}
