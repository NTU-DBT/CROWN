#include "crown/storage/arena.hpp"
#include "crown/storage/reference.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <new>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// This test binary fails one intercepted scalar/array global-new attempt.
// Aligned/nothrow overloads are not independently replaced; direct libc and
// exception-ABI allocation are outside the count.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
[[gnu::noinline]] void* allocate(std::size_t bytes) {
  if (fail_after >= 0 && fail_after-- == 0) throw std::bad_alloc{};
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}

class AllocationFailureScope {
 public:
  explicit AllocationFailureScope(std::ptrdiff_t step) noexcept { fail_after = step; }
  ~AllocationFailureScope() { fail_after = -1; }
  AllocationFailureScope(const AllocationFailureScope&) = delete;
  AllocationFailureScope& operator=(const AllocationFailureScope&) = delete;
};
}  // namespace

void* operator new(std::size_t bytes) { return allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocate(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::storage;

void check(bool value, const char* message) {
  if (!value) throw std::runtime_error(message);
}

Value n(std::int64_t value) { return value; }
Value text(std::string value) { return value; }

TupleLayout source() {
  return {LayoutId{1}, {{ScalarType::int64}, {ScalarType::string}, {ScalarType::int64}}};
}

Tuple row(const TupleLayout& layout, std::int64_t id, char fill = 'a') {
  return layout.tuple({n(id), text(std::string(320, fill) + std::to_string(id)), n(id * 3)});
}

// Arm one failure at the next intercepted new call, then reset on either exit.
// No attempts are counted; a callback catching bad_alloc can hide the probe.
template <class Function>
auto without_allocations(Function&& function) {
  using Result = std::invoke_result_t<Function>;
  fail_after = 0;
  try {
    if constexpr (std::is_void_v<Result>) {
      std::forward<Function>(function)();
      fail_after = -1;
      return;
    } else {
      auto result = std::forward<Function>(function)();
      fail_after = -1;
      return result;
    }
  } catch (...) {
    fail_after = -1;
    throw;
  }
}

void check_arena_preserved(const TupleArena& arena,
                           const ArenaStatistics& statistics,
                           const std::vector<ArenaHandle>& handles,
                           const std::vector<const Tuple*>& addresses,
                           const std::vector<TupleArena::Pin>& pins,
                           const std::vector<const Tuple*>& pin_addresses,
                           const std::optional<ArenaHandle>& erased_handle) {
  check(arena.statistics() == statistics, "failed arena insertion changed statistics");
  check(handles.size() == addresses.size(), "arena test fixture is inconsistent");
  for (std::size_t i = 0; i < handles.size(); ++i) {
    check(arena.contains(handles[i]), "failed arena insertion invalidated a prior handle");
    check(&arena.get(handles[i]) == addresses[i], "failed arena insertion moved a prior tuple");
  }
  check(pins.size() == pin_addresses.size(), "arena pin test fixture is inconsistent");
  for (std::size_t i = 0; i < pins.size(); ++i) {
    check(pins[i].is_live(), "failed arena insertion changed a live pin");
    check(pins[i].handle() == handles[i], "failed arena insertion changed a pin handle");
    check(&pins[i].get() == pin_addresses[i], "failed arena insertion moved a pinned tuple");
  }
  if (erased_handle) check(!arena.contains(*erased_handle), "failed arena insertion revived an erased generation");
  arena.check_invariants();
}

std::size_t arena_insert_failures(std::size_t initial_rows, bool reuse_slot) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 1024; ++step) {
    const auto layout = source();
    TupleArena arena{layout};
    std::vector<ArenaHandle> handles;
    handles.reserve(initial_rows);
    for (std::size_t i = 0; i < initial_rows; ++i) {
      const auto value = row(layout, static_cast<std::int64_t>(i + 1));
      handles.push_back(arena.insert(value));
    }

    std::optional<ArenaHandle> erased_handle;
    if (reuse_slot) {
      check(initial_rows > 1, "reuse sweep needs a live row to retain");
      erased_handle = handles.back();
      check(arena.erase(*erased_handle), "could not create a free arena slot");
      handles.pop_back();
    }

    std::vector<const Tuple*> addresses;
    addresses.reserve(handles.size());
    for (const auto handle : handles) addresses.push_back(&arena.get(handle));
    std::vector<TupleArena::Pin> pins;
    pins.reserve(handles.size());
    std::vector<const Tuple*> pin_addresses;
    pin_addresses.reserve(handles.size());
    for (const auto handle : handles) {
      pins.push_back(arena.pin(handle));
      pin_addresses.push_back(&pins.back().get());
    }

    const auto before = arena.statistics();
    const auto candidate = row(layout, 9000, 'z');
    bool failed = false;
    std::optional<ArenaHandle> inserted;
    {
      [[maybe_unused]] AllocationFailureScope failure_scope{step};
      try {
        inserted = arena.insert(candidate);
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }

    if (failed) {
      ++failures;
      check_arena_preserved(arena, before, handles, addresses, pins, pin_addresses, erased_handle);
      const auto retry = arena.insert(candidate);
      check(arena.get(retry) == candidate, "arena retry did not insert the same tuple");
      if (reuse_slot) {
        check(erased_handle.has_value(), "reuse sweep lost its erased handle");
        check(retry.slot == erased_handle->slot && retry.generation == erased_handle->generation + 1,
              "failed reuse insertion consumed or changed a slot generation");
      } else {
        check(retry.slot.value == before.slots, "failed fresh insertion consumed a slot");
      }
      arena.check_invariants();
      continue;
    }

    check(inserted.has_value(), "arena insertion returned no handle");
    check(arena.get(*inserted) == candidate, "arena insertion did not preserve the owned tuple");
    if (reuse_slot) {
      check(erased_handle.has_value(), "reuse sweep lost its erased handle");
      check(inserted->slot == erased_handle->slot && inserted->generation == erased_handle->generation + 1,
            "arena reuse did not advance the slot generation");
    } else {
      check(inserted->slot.value == before.slots, "fresh arena insertion did not append a slot");
    }
    arena.check_invariants();
    return failures;
  }
  throw std::runtime_error("arena insertion fault sweep did not reach success");
}

void arena_pin_paths_do_not_allocate() {
  const auto layout = source();
  TupleArena arena{layout};
  const auto first = arena.insert(row(layout, 1));
  const auto second = arena.insert(row(layout, 2));
  auto first_pin = without_allocations([&] { return arena.pin(first); });
  auto second_pin = without_allocations([&] { return arena.pin(second); });
  check(arena.statistics().pins == 2, "pin creation did not update pin statistics");

  const auto first_value = first_pin.get();
  const bool erased = without_allocations([&] { return arena.erase(first); });
  check(erased, "erase unexpectedly failed");
  check(!first_pin.is_live() && first_pin.get() == first_value, "pin did not retain its erased tuple");
  check(arena.statistics() == ArenaStatistics{2, 1, 1, 2, 0, 0}, "erase did not retain only its pinned record");

  without_allocations([&] { first_pin.reset(); });
  check(arena.statistics() == ArenaStatistics{2, 1, 0, 1, 1, 0}, "pin release did not free the retired slot");

  without_allocations([&] { arena.clear(); });
  check(!second_pin.is_live() && second_pin.get() == row(layout, 2), "clear did not retain its pinned tuple");
  check(arena.statistics() == ArenaStatistics{2, 0, 1, 1, 1, 0}, "clear did not retain exactly the pinned record");
  without_allocations([&] { second_pin.reset(); });
  check(arena.statistics() == ArenaStatistics{2, 0, 0, 0, 2, 0}, "final pin release left a retained record");
  arena.check_invariants();
}

std::size_t reference_insert_failures() {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 1024; ++step) {
    const auto layout = source();
    ReferenceTable table{RelationId{1}, layout};
    const std::vector<std::vector<FieldId>> index_fields{{FieldId{0}}, {FieldId{1}}, {}};
    for (std::size_t i = 0; i < index_fields.size(); ++i) {
      const auto& fields = index_fields[i];
      Projection projection{layout, projected_layout(LayoutId{10 + i}, layout, fields), fields};
      static_cast<void>(table.add_index(std::move(projection)));
    }
    const auto first_value = row(layout, 1);
    const auto second_value = row(layout, 2);
    const auto first = table.insert(first_value).handle;
    const auto second = table.insert(second_value).handle;
    auto pin = table.pin(first);
    const auto pin_handle = pin.handle();
    const auto* first_address = table.get(first);
    const auto* second_address = table.get(second);
    const auto rows = table.snapshot();
    const auto before_revision = table.revision();
    const auto before_statistics = table.arena_statistics();
    const auto candidate = row(layout, 9001, 'z');
    bool failed = false;
    std::optional<InsertResult> inserted;
    {
      [[maybe_unused]] AllocationFailureScope failure_scope{step};
      try {
        inserted = table.insert(candidate);
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }

    if (failed) {
      ++failures;
      check(table.size() == rows.size(), "failed table insert changed row count");
      check(table.snapshot() == rows, "failed table insert changed existing rows");
      check(table.revision() == before_revision, "failed table insert changed revision");
      check(table.find(first_value) == first && table.find(second_value) == second,
            "failed table insert changed a prior tuple ID");
      check(!table.find(candidate), "failed table insert published the candidate row");
      const auto after_statistics = table.arena_statistics();
      check(after_statistics.live_records == before_statistics.live_records &&
                after_statistics.retained_records == before_statistics.retained_records &&
                after_statistics.pins == before_statistics.pins,
            "failed table insert changed live, retained, or pin counts");
      check(pin.handle() == pin_handle && pin.is_live(), "failed table insert changed an existing pin");
      check(&pin.get() == first_address && table.get(first) == first_address && table.get(second) == second_address,
            "failed table insert moved an existing pinned or borrowed tuple");
      table.check_invariants();

      const auto retry = table.insert(candidate);
      check(retry.inserted && retry.handle.tuple.value == 3,
            "failed table insert consumed an ID or retry did not commit");
      check(table.revision() == before_revision + 1, "table retry did not advance revision exactly once");
      table.check_invariants();
      continue;
    }

    check(inserted.has_value() && inserted->inserted, "table insertion did not eventually commit");
    check(inserted->handle.tuple.value == 3, "table insertion assigned an unexpected tuple ID");
    check(table.size() == rows.size() + 1 && table.revision() == before_revision + 1,
          "table insertion did not commit exactly once");
    table.check_invariants();
    return failures;
  }
  throw std::runtime_error("reference insertion fault sweep did not reach success");
}

void reference_pins_survive_retirement_and_destruction() {
  const auto layout = source();
  auto first_value = row(layout, 1);
  auto second_value = row(layout, 2);
  TupleArena::Pin erased_pin = [&] {
    ReferenceTable table{RelationId{2}, layout};
    const auto erased = table.insert(first_value).handle;
    const auto cleared = table.insert(second_value).handle;
    auto first = without_allocations([&] { return table.pin(erased); });
    auto second = without_allocations([&] { return table.pin(cleared); });
    check(table.erase(erased), "could not erase a pinned reference row");
    check(!first.is_live() && first.get() == first_value, "reference pin did not survive erase");
    check(table.arena_statistics().live_records == 1 && table.arena_statistics().retained_records == 1,
          "reference erase left unexpected arena counts");
    table.clear();
    check(!second.is_live() && second.get() == second_value, "reference pin did not survive clear");
    check(table.arena_statistics().live_records == 0 && table.arena_statistics().retained_records == 2,
          "reference clear left unexpected retained counts");
    second.reset();
    check(table.arena_statistics().retained_records == 1, "releasing a cleared pin left it retained");
    return first;
  }();
  check(!erased_pin.is_live() && erased_pin.get() == first_value,
        "reference pin did not survive table destruction");
  erased_pin.reset();
}
}  // namespace

int main() {
  try {
    const auto fresh = arena_insert_failures(2, false);
    const auto reused = arena_insert_failures(4, true);
    const auto vector_growth = arena_insert_failures(128, false);
    arena_pin_paths_do_not_allocate();
    const auto reference = reference_insert_failures();
    reference_pins_survive_retirement_and_destruction();
    check(fresh > 0 && reused > 0 && vector_growth > 0 && reference > 0,
          "allocation fault sweep did not exercise failure paths");
    std::cout << "arena allocation rollback points: fresh=" << fresh << " reused=" << reused
              << " vector_growth=" << vector_growth << " reference=" << reference << '\n';
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
