#include "crown/storage/indexed.hpp"
#include "index_allocation.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

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
IndexedLimits limits() { return {256, 8, 1024, 2048, 4096, 16384, 512, 128}; }
template <class Cursor>
auto no_allocation_step(Cursor& cursor, IndexWorkAllowance& work) {
  s04_alloc::Scope denied(0);
  return cursor.next(work);
}
void allocation_free_result() {
  verify(s04_alloc::calls == 0 && !s04_alloc::triggered, "successful live step allocated");
}

void retained_capacity_and_step_boundaries() {
  TupleLayout layout(LayoutId{1}, {{ScalarType::int64}, {ScalarType::string}, {ScalarType::decimal}});
  TupleLayout nullary_layout(LayoutId{2}, {}), integer_layout(LayoutId{3}, {{ScalarType::int64}});
  TupleLayout decimal_layout(LayoutId{4}, {{ScalarType::decimal}});
  Projection empty(layout, nullary_layout, {}), integer(layout, integer_layout, {FieldId{0}});
  Projection decimal(layout, decimal_layout, {FieldId{2}});
  IndexedTable table(RelationId{1}, layout, limits());auto work = ample();
  const auto nullary = table.add_index(empty, work), by_integer = table.add_index(integer, work);
  const auto by_decimal = table.add_index(decimal, work);
  const std::string wide(1024, 'x');
  const auto exact = Decimal::parse("12345678901234567890123456789012345678");
  for (std::int64_t value = 0; value < 128; ++value)
    static_cast<void>(table.insert(layout.tuple(Row{value, wide, exact}), work));
  table.clear(work);
  const auto tuple = layout.tuple(Row{std::int64_t{7}, wide, exact});
  const auto handle = table.insert(tuple, work).handle;
  verify(table.statistics().directory_slots > 512 && table.size() == 1, "retained-capacity fixture did not retain large directories");
  auto live = table.live(work);IndexWorkAllowance denied(IndexWork{});
  rejects("storage_work_limit", [&] { static_cast<void>(live.next(denied)); });
  IndexWorkAllowance first(IndexWork{.structural_steps = 1});
  const auto row = no_allocation_step(live, first);allocation_free_result();
  verify(row.has_value() && row->handle == handle && &row->tuple == table.get(handle, work) && row->tuple == tuple &&
      first.remaining() == IndexWork{}, "one-step borrow/order differs after denied advance");
  IndexWorkAllowance end(IndexWork{.structural_steps = 1});
  verify(!no_allocation_step(live, end) && end.remaining() == IndexWork{}, "empty/end traversal did not cost one step");
  allocation_free_result();

  auto bucket = table.bucket_cursor(nullary, nullary_layout.tuple({}), work);
  IndexWorkAllowance member_step(IndexWork{.structural_steps = 1});
  const auto member = no_allocation_step(bucket, member_step);allocation_free_result();
  verify(member && member->handle == handle && &member->tuple == &row->tuple,
         "bucket cursor added an ID lookup/copy or wrong row");
  auto key_cursor = table.index_keys(by_decimal, work);
  IndexWorkAllowance key_step(IndexWork{.structural_steps = 1});
  const auto key = no_allocation_step(key_cursor, key_step);allocation_free_result();
  verify(key && key->degree == 1 && key->key.layout().same_token(decimal_layout) &&
      std::get<Decimal>(crown::storage::export_row(key->key.values())[0]) == exact, "key cursor degree/binding differs");
  IndexWorkAllowance key_end(IndexWork{.structural_steps = 1});
  verify(!no_allocation_step(key_cursor, key_end), "key traversal scanned retired capacity");allocation_free_result();
  auto missing = table.bucket_cursor(by_integer, integer_layout.tuple(Row{std::int64_t{999}}), work);
  IndexWorkAllowance missing_step(IndexWork{.structural_steps = 1});
  verify(!no_allocation_step(missing, missing_step), "missing bucket was not empty");allocation_free_result();

  auto preserved = table.live(work);const auto before = table.statistics();
  bool failed = false;
  try {
    s04_alloc::Scope allocation_failure(0);static_cast<void>(table.live(work));
  } catch (const std::bad_alloc&) { failed = true; }
  verify(failed && s04_alloc::triggered && s04_alloc::calls == 1 && table.statistics() == before,
         "failed cursor allocation changed owner state or missed its injection");
  verify(preserved.next(work)->handle == handle, "failed cursor allocation invalidated a previous cursor");
  auto after_failed_insert = table.live(work);IndexWorkAllowance too_small(IndexWork{.structural_steps = 1});
  rejects("storage_work_limit", [&] {
    static_cast<void>(table.insert(layout.tuple(Row{std::int64_t{8}, wide, exact}), too_small));
  });
  verify(after_failed_insert.next(work)->handle == handle && table.statistics() == before,
         "failed mutation preparation invalidated a cursor or changed owner state");
  table.check_invariants();
}

void noops_mutation_moves_and_owner_loss() {
  TupleLayout layout(LayoutId{11}, {{ScalarType::int64}});
  TupleLayout key_layout(LayoutId{12}, {{ScalarType::int64}});Projection projection(layout, key_layout, {FieldId{0}});
  const auto first = layout.tuple(Row{std::int64_t{1}}), second = layout.tuple(Row{std::int64_t{2}});
  IndexedTable table(RelationId{1}, layout, limits());auto work = ample();
  const auto index = table.add_index(projection, work);const auto handle = table.insert(first, work).handle;
  auto live = table.live(work);auto bucket = table.bucket_cursor(index, key_layout.tuple(Row{std::int64_t{1}}), work);
  auto keys = table.index_keys(index, work);
  verify(!table.insert(first, work).inserted && !table.erase(second, work) && !table.drop_index(IndexId{999}, work),
         "no-op fixture changed owner state");
  auto pin = table.pin(handle, work);pin.reset();
  verify(live.next(work)->handle == handle && bucket.next(work)->handle == handle && keys.next(work)->degree == 1,
         "no-op/pin bookkeeping invalidated live cursors");
  static_cast<void>(table.insert(second, work));
  rejects("invalid_cursor", [&] { static_cast<void>(live.next(work)); });
  rejects("invalid_cursor", [&] { static_cast<void>(bucket.next(work)); });
  rejects("invalid_cursor", [&] { static_cast<void>(keys.next(work)); });
  auto follows_owner = table.live(work);IndexedTable moved(std::move(table));
  verify(follows_owner.next(work)->handle == handle, "facade move invalidated the same actual owner");
  auto original = moved.live(work);auto moved_cursor = std::move(original);
  rejects("invalid_cursor", [&] { static_cast<void>(original.next(work)); });
  verify(moved_cursor.next(work)->handle == handle, "cursor move lost its position");
  auto dropped_key_cursor = moved.index_keys(index, work);
  verify(moved.drop_index(index, work), "index drop fixture failed");
  rejects("invalid_cursor", [&] { static_cast<void>(dropped_key_cursor.next(work)); });
  moved.check_invariants();

  auto expired_with_pin = [&] {
    IndexedTable local(RelationId{1}, layout, limits());
    const auto saved = local.insert(first, work).handle;
    return std::pair{local.live(work), local.pin(saved, work)};
  }();
  verify(expired_with_pin.second.get() == first && !expired_with_pin.second.is_live(),
         "owner teardown lost pinned payload or retained membership");
  rejects("invalid_cursor", [&] { static_cast<void>(expired_with_pin.first.next(work)); });
}
}  // namespace

int main() {
  retained_capacity_and_step_boundaries();noops_mutation_moves_and_owner_loss();
  std::cout << "S04 cursor draft: allocation-free live steps, retained capacity, invalidation and weak lifetime passed\n";
}
