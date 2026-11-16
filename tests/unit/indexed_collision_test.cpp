#include "indexed_testing.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

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
  return IndexWorkAllowance(IndexWork{1'000'000, 1'000'000, 1'000'000, 1'000'000, 1'000'000});
}

void exact_collision_paths(detail::CollisionMode mode) {
  TupleLayout layout(LayoutId{1}, {{ScalarType::int64}});
  TupleLayout target(LayoutId{2}, {{ScalarType::int64}});Projection projection(layout, target, {FieldId{0}});
  IndexedTable table(RelationId{1}, layout, IndexedLimits{8, 1, 8, 8, 32, 64, 8, 0});
  detail::IndexedTesting::collisions(table, mode);auto work = ample();
  const auto index = table.add_index(projection, work);
  const auto missing = layout.tuple(Row{std::int64_t{9}});
  for (std::int64_t value = 0; value < 6; ++value) {
    const auto tuple = layout.tuple(Row{value});
    if (mode == detail::CollisionMode::same_bucket)
      verify((tuple.hash() & ~std::uint64_t{0xffff}) != (missing.hash() & ~std::uint64_t{0xffff}),
             "bucket-only fixture accidentally has an equal full hash");
    verify(table.insert(tuple, work).inserted, "collision insert merged distinct integer rows");
  }
  table.check_invariants();const auto before = table.statistics();auto cursor = table.live(work);
  // Six actual nodes share bucket0. A different full hash performs no equality
  // bodies; a full collision must admit all six pairs of exact scalar bodies.
  const bool full = mode == detail::CollisionMode::same_full_hash;
  const IndexWork primary_cost{8, full ? 26U : 2U, full ? 113U : 17U, 0, 0};
  IndexWorkAllowance primary(primary_cost);
  verify(!table.find(missing, primary) && primary.remaining() == IndexWork{},
         "primary lookup did not visit the expected real collision/equality path");
  auto short_cost = primary_cost;--short_cost.structural_steps;IndexWorkAllowance short_lookup(short_cost);
  rejects("storage_work_limit", [&] { static_cast<void>(table.find(missing, short_lookup)); });
  // Secondary startup adds one index-directory lookup (startup plus its node).
  const IndexWork secondary_cost{10, full ? 26U : 2U, full ? 113U : 17U, 0, 0};
  IndexWorkAllowance secondary(secondary_cost);
  verify(table.bucket(index, target.tuple(Row{std::int64_t{9}}), secondary).empty() && secondary.remaining() == IndexWork{},
         "secondary lookup skipped its actual collision/equality path");
  verify(table.statistics() == before && cursor.next(work)->handle.tuple == TupleId{1},
         "failed/read-only collision lookup changed counters or invalidated a cursor");
  for (std::int64_t value = 0; value < 6; ++value)
    verify(table.erase(layout.tuple(Row{value}), work), "exact collision erase lost or selected another row");
  verify(table.size() == 0 && table.key_count(index, work) == 0, "collision erase retained public membership");
  table.check_invariants();
  rejects("storage_contract", [&] { detail::IndexedTesting::collisions(table, mode); });
}
}  // namespace

int main() {
  exact_collision_paths(detail::CollisionMode::same_bucket);
  exact_collision_paths(detail::CollisionMode::same_full_hash);
  std::cout << "S04 collision draft: primary/secondary real chains, exact equality bodies and one-under work limits passed\n";
}
