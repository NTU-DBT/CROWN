#include "crown/api/error.hpp"
#include "crown/storage/arena.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::storage;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == code, "wrong arena error: " + failure.code());
    return;
  }
  throw std::runtime_error("expected arena error: " + std::string(code));
}

TupleLayout arena_layout(LayoutId id = LayoutId{71}) {
  return TupleLayout{id,
    {{ScalarType::int64}, {ScalarType::string}, {ScalarType::boolean},
     {ScalarType::date}, {ScalarType::decimal, DecimalSpec{38, 5}}},
    LayoutContext{23, "arena-model"}};
}

Row make_row(std::int64_t integer, std::string text, bool flag,
             std::string_view day = "2024-02-29",
             std::string_view amount = "12345678901234567890.00001") {
  return Row{Value{integer}, Value{std::move(text)}, Value{flag},
             Value{Date::parse(day)}, Value{Decimal::parse(amount)}};
}

std::size_t pick(std::mt19937_64& random, std::size_t bound) {
  return static_cast<std::size_t>(random() % static_cast<std::uint64_t>(bound));
}

Row random_row(std::mt19937_64& random, std::uint64_t serial) {
  static const std::array<std::string, 7> strings{
    "", "alpha", "beta", "123", "same-looking-number", std::string("n\0ul", 4), "é"};
  static const std::array<std::string_view, 4> dates{
    "1969-12-31", "2000-02-29", "2024-02-29", "9999-12-31"};
  static const std::array<std::string_view, 5> decimals{
    "0", "-2.50000", "1", "1.00000", "100000000000000000000.00001"};
  const auto integer = static_cast<std::int64_t>(random() % 101U) - 50;
  std::string text = strings[pick(random, strings.size())];
  if ((serial % 7U) == 0U) text += "/" + std::to_string(serial);
  return make_row(integer, std::move(text), (random() & 1U) != 0U,
                  dates[pick(random, dates.size())],
                  decimals[pick(random, decimals.size())]);
}

void type_contract_and_stable_addresses() {
  static_assert(!std::is_copy_constructible_v<TupleArena>);
  static_assert(!std::is_copy_assignable_v<TupleArena>);
  static_assert(std::is_nothrow_move_constructible_v<TupleArena>);
  static_assert(std::is_nothrow_move_assignable_v<TupleArena>);
  static_assert(!std::is_copy_constructible_v<TupleArena::Pin>);
  static_assert(!std::is_copy_assignable_v<TupleArena::Pin>);
  static_assert(std::is_nothrow_move_constructible_v<TupleArena::Pin>);
  static_assert(std::is_nothrow_move_assignable_v<TupleArena::Pin>);
  static_assert(noexcept(std::declval<TupleArena::Pin&>().reset()));

  const auto layout = arena_layout();
  TupleLayout shared_token = layout;
  const auto equivalent_descriptor = arena_layout();
  check(layout.same_token(shared_token), "layout copies share the exact runtime token");
  check(layout.same_descriptor(equivalent_descriptor) &&
        !layout.same_token(equivalent_descriptor),
        "equal layout descriptions keep distinct runtime tokens");

  TupleArena arena(layout);
  const std::string long_text(128U * 1024U, 'x');
  const auto expected = make_row(std::numeric_limits<std::int64_t>::min(), long_text,
                                 true, "0001-01-01", "-99999999999999999999.99999");
  const auto handle = arena.insert(layout.tuple(expected));
  check(arena.layout().same_token(layout), "arena retains the exact layout token");
  check(arena.get(handle).layout().same_token(layout), "stored tuple retains the exact layout token");
  check(arena.get(handle).values() == expected,
        "arena owns long strings and exact tagged scalar values");

  const auto* stable = &arena.get(handle);
  for (std::size_t index = 0; index < 2048U; ++index) {
    const auto serial = static_cast<std::int64_t>(index);
    const auto row = make_row(serial, "growth/" + std::to_string(index),
                              (index & 1U) != 0U);
    static_cast<void>(arena.insert(layout.tuple(row)));
  }
  check(&arena.get(handle) == stable && stable->values() == expected,
        "slot payload address stays stable while slot metadata grows");
  arena.check_invariants();

  const auto before = arena.statistics();
  expect_error([&] {
    static_cast<void>(arena.insert(equivalent_descriptor.tuple(expected)));
  }, "layout_mismatch");
  check(arena.statistics() == before, "rejected foreign layout does not publish a slot");
}

void handle_errors_and_immediate_invalidation() {
  const auto layout = arena_layout();
  TupleArena arena(layout);
  const auto row = make_row(7, "live-row", false);
  const auto handle = arena.insert(layout.tuple(row));
  const auto foreign = ArenaHandle{ArenaOwnerId{arena.owner().value + 1U}, handle.slot,
                                   handle.generation};

  expect_error([&] { static_cast<void>(arena.contains(foreign)); }, "foreign_handle");
  expect_error([&] { static_cast<void>(arena.get(foreign)); }, "foreign_handle");
  expect_error([&] { static_cast<void>(arena.pin(foreign)); }, "foreign_handle");
  expect_error([&] { static_cast<void>(arena.erase(foreign)); }, "foreign_handle");

  const auto zero_generation = ArenaHandle{arena.owner(), handle.slot, 0};
  const auto out_of_range = ArenaHandle{
    arena.owner(), TupleSlotId{std::numeric_limits<std::size_t>::max()}, 1};
  for (const auto malformed : {zero_generation, out_of_range}) {
    check(!arena.contains(malformed), "malformed same-owner handle is not live");
    check(!arena.erase(malformed), "malformed same-owner handle cannot erase a slot");
    expect_error([&] { static_cast<void>(arena.get(malformed)); }, "stale_handle");
    expect_error([&] { static_cast<void>(arena.pin(malformed)); }, "stale_handle");
  }

  check(arena.erase(handle), "live handle erases once");
  check(!arena.contains(handle), "erase immediately invalidates ordinary membership");
  check(!arena.erase(handle), "repeated erase of a stale handle is a no-op");
  expect_error([&] { static_cast<void>(arena.get(handle)); }, "stale_handle");
  expect_error([&] { static_cast<void>(arena.pin(handle)); }, "stale_handle");
  arena.check_invariants();
}

void pins_retirement_and_clear_generation() {
  const auto layout = arena_layout();
  TupleArena arena(layout);
  const auto row = make_row(41, "retained-across-erase", true);
  const auto handle = arena.insert(layout.tuple(row));
  auto first_pin = arena.pin(handle);
  auto second_pin = arena.pin(handle);
  check(first_pin.handle() == handle && second_pin.handle() == handle,
        "multiple pins identify the same immutable row");
  check(first_pin.is_live() && second_pin.is_live(), "pins report live membership before erase");
  check(arena.statistics() == ArenaStatistics{1, 1, 0, 2, 0, 0},
        "statistics count each pin object");

  check(arena.erase(handle), "pinned row erases from membership");
  check(!first_pin.is_live() && !second_pin.is_live(),
        "erase immediately invalidates membership through all pins");
  check(first_pin.get().values() == row && second_pin.get().values() == row,
        "each pin retains the old tuple after erase");
  check(!arena.contains(handle), "ordinary handle is stale while pins retain payload");
  expect_error([&] { static_cast<void>(arena.get(handle)); }, "stale_handle");
  check(arena.statistics() == ArenaStatistics{1, 0, 1, 2, 0, 0},
        "erased row is counted once as retained with both pins");

  const auto while_pinned = arena.insert(layout.tuple(make_row(42, "another-slot", false)));
  check(while_pinned.slot != handle.slot,
        "retained slot is not reused while any pin remains");
  first_pin.reset();
  check(arena.statistics() == ArenaStatistics{2, 1, 1, 1, 0, 0},
        "releasing one of several pins preserves row retention");
  const auto while_one_pin = arena.insert(layout.tuple(make_row(43, "third-slot", true)));
  check(while_one_pin.slot != handle.slot,
        "retained slot stays unavailable until its last pin releases");
  second_pin.reset();
  check(arena.statistics() == ArenaStatistics{3, 2, 0, 0, 1, 0},
        "last pin release reclaims the payload and makes metadata reusable");
  expect_error([&] { static_cast<void>(first_pin.handle()); }, "invalid_pin");
  expect_error([&] { static_cast<void>(first_pin.get()); }, "invalid_pin");
  expect_error([&] { static_cast<void>(first_pin.is_live()); }, "invalid_pin");

  const auto reused = arena.insert(layout.tuple(make_row(44, "reused", false)));
  check(reused.slot == handle.slot && reused.generation == handle.generation + 1U,
        "last-pin reclamation permits same-slot reuse with advanced generation");
  check(!arena.contains(handle) && arena.contains(reused),
        "generation distinguishes old and reused handles");

  TupleArena cleared(layout);
  const auto initial = cleared.insert(layout.tuple(make_row(1, "before-clear", false)));
  check(cleared.erase(initial), "prepare the slot for a pre-clear reuse");
  const auto second_generation = cleared.insert(layout.tuple(make_row(2, "before-second-clear", true)));
  check(second_generation.slot == initial.slot &&
        second_generation.generation == initial.generation + 1U,
        "test setup advances a reusable slot generation");
  auto clear_pin = cleared.pin(second_generation);
  cleared.clear();
  check(!cleared.contains(second_generation) && !clear_pin.is_live(),
        "clear immediately invalidates handles while preserving pinned payloads");
  expect_error([&] { static_cast<void>(cleared.get(second_generation)); }, "stale_handle");
  check(clear_pin.get().values() == make_row(2, "before-second-clear", true),
        "pin reads its tuple after clear");
  check(cleared.statistics() == ArenaStatistics{1, 0, 1, 1, 0, 0},
        "clear retains only the pinned record");
  clear_pin.reset();
  const auto after_clear = cleared.insert(layout.tuple(make_row(3, "after-clear", false)));
  check(after_clear.slot == second_generation.slot &&
        after_clear.generation == second_generation.generation + 1U,
        "clear preserves free metadata and advances, rather than resetting, generation");
  cleared.check_invariants();
}

void moves_and_owner_lifetimes() {
  const auto layout = arena_layout();
  TupleArena source(layout);
  const auto source_handle = source.insert(layout.tuple(make_row(10, "move-source", true)));
  const auto source_owner = source.owner();
  auto source_pin = source.pin(source_handle);
  TupleArena moved(std::move(source));
  check(moved.owner() == source_owner && moved.get(source_handle).values() == source_pin.get().values(),
        "arena move construction transfers owner identity and records");
  check(source_pin.is_live(), "pin remains attached to a moved arena state");
  expect_error([&] { static_cast<void>(source.owner()); }, "invalid_arena");
  expect_error([&] { static_cast<void>(source.layout()); }, "invalid_arena");
  expect_error([&] { static_cast<void>(source.statistics()); }, "invalid_arena");
  expect_error([&] { static_cast<void>(source.insert(layout.tuple(make_row(11, "x", false)))); }, "invalid_arena");
  expect_error([&] { static_cast<void>(source.contains(source_handle)); }, "invalid_arena");
  expect_error([&] { static_cast<void>(source.get(source_handle)); }, "invalid_arena");
  expect_error([&] { static_cast<void>(source.pin(source_handle)); }, "invalid_arena");
  expect_error([&] { static_cast<void>(source.erase(source_handle)); }, "invalid_arena");
  expect_error([&] { source.clear(); }, "invalid_arena");
  expect_error([&] { source.check_invariants(); }, "invalid_arena");

  auto* moved_alias = &moved;
  moved = std::move(*moved_alias);
  check(moved.owner() == source_owner && moved.contains(source_handle),
        "arena self-move preserves owner and membership");

  const auto other_layout = arena_layout(LayoutId{72});
  TupleArena destination(other_layout);
  const auto displaced_handle = destination.insert(other_layout.tuple(make_row(20, "displaced", false)));
  auto displaced_pin = destination.pin(displaced_handle);
  TupleArena replacement(layout);
  const auto replacement_handle = replacement.insert(layout.tuple(make_row(30, "replacement", true)));
  const auto replacement_owner = replacement.owner();
  destination = std::move(replacement);
  check(destination.owner() == replacement_owner &&
        destination.get(replacement_handle).values() == make_row(30, "replacement", true),
        "move assignment replaces the arena owner and transfers live rows");
  check(!displaced_pin.is_live() && displaced_pin.get().values() == make_row(20, "displaced", false),
        "pins retain displaced rows after move assignment");
  expect_error([&] { static_cast<void>(replacement.owner()); }, "invalid_arena");
  expect_error([&] { static_cast<void>(destination.get(displaced_handle)); }, "foreign_handle");

  std::optional<TupleArena::Pin> orphan;
  ArenaHandle destroyed_owner_handle{};
  const auto destroyed_row = make_row(99, "owner-destroyed", true);
  {
    TupleArena temporary(layout);
    destroyed_owner_handle = temporary.insert(layout.tuple(destroyed_row));
    orphan.emplace(temporary.pin(destroyed_owner_handle));
  }
  check(orphan.has_value() && orphan->handle() == destroyed_owner_handle &&
        !orphan->is_live() && orphan->get().values() == destroyed_row,
        "pin keeps its immutable tuple after owner destruction");
  orphan->reset();
  orphan.reset();

  auto pin_a = moved.pin(source_handle);
  auto pin_b = moved.pin(source_handle);
  auto* pin_alias = &pin_a;
  pin_a = std::move(*pin_alias);
  check(moved.statistics().pins == 3U && pin_a.is_live(),
        "pin self-move preserves its reference count and payload");
  pin_a = std::move(pin_b);
  check(moved.statistics().pins == 2U && pin_a.is_live(),
        "pin move assignment releases its old pin and transfers the source pin");
  expect_error([&] { static_cast<void>(pin_b.handle()); }, "invalid_pin");
  expect_error([&] { static_cast<void>(pin_b.get()); }, "invalid_pin");
  expect_error([&] { static_cast<void>(pin_b.is_live()); }, "invalid_pin");
  pin_b.reset();
  pin_a.reset();
  check(moved.statistics().pins == 1U,
        "reset on moved-from and live pins releases only live pin objects");
}

struct ModelSlot {
  std::uint64_t generation = 0;
  bool known = false;
  bool live = false;
  std::size_t pin_count = 0;
  Row value;
};

struct ModelPin {
  TupleArena::Pin pin;
  ArenaHandle handle;
};

class ArenaModel {
 public:
  ArenaModel(const TupleLayout& layout, TupleArena& arena)
      : layout_(layout), arena_(arena), owner_(arena.owner()) {}

  ArenaHandle insert(Row row) {
    const auto handle = arena_.insert(layout_.tuple(row));
    check(handle.owner == owner_, "insert returns this model's owner ID");
    if (handle.slot.value == slots_.size()) {
      check(handle.generation == 1U, "first allocation starts at generation one");
      slots_.push_back(ModelSlot{handle.generation, true, true, 0, row});
    } else {
      check(handle.slot.value < slots_.size(), "new slot metadata is contiguous");
      auto& slot = slots_[handle.slot.value];
      check(slot.known && !slot.live && slot.pin_count == 0U,
            "reused slot was free and unpinned in the independent model");
      check(slot.generation != std::numeric_limits<std::uint64_t>::max() &&
            handle.generation == slot.generation + 1U,
            "reused slot generation advances exactly once");
      slot.generation = handle.generation;
      slot.live = true;
      slot.value = row;
    }
    seen_handles_.push_back(handle);
    return handle;
  }

  bool erase(ArenaHandle handle) {
    const auto expected = is_live(handle);
    const auto actual = arena_.erase(handle);
    check(actual == expected, "erase result matches independent slot/generation model");
    if (expected) slots_[handle.slot.value].live = false;
    return expected;
  }

  void clear() {
    arena_.clear();
    for (auto& slot : slots_) slot.live = false;
  }

  void add_pin(std::size_t id, ArenaHandle handle) {
    check(is_live(handle), "model only adds pins to live handles");
    auto pin = arena_.pin(handle);
    check(pin.handle() == handle && pin.is_live() && pin.get().values() == value(handle),
          "new pin starts attached to the selected live tuple");
    ++slots_[handle.slot.value].pin_count;
    const auto [entry, inserted] = pins_.emplace(id, ModelPin{std::move(pin), handle});
    static_cast<void>(entry);
    check(inserted, "pin model IDs are unique");
  }

  void release_pin(std::size_t id) {
    const auto found = pins_.find(id);
    check(found != pins_.end(), "selected model pin exists");
    const auto handle = found->second.handle;
    check(slots_[handle.slot.value].pin_count > 0U, "model pin count does not underflow");
    --slots_[handle.slot.value].pin_count;
    pins_.erase(found);
  }

  [[nodiscard]] const std::vector<ArenaHandle>& seen_handles() const noexcept {
    return seen_handles_;
  }
  [[nodiscard]] const std::map<std::size_t, ModelPin>& pins() const noexcept { return pins_; }
  [[nodiscard]] std::vector<ArenaHandle> live_handles() const {
    std::vector<ArenaHandle> result;
    for (const auto handle : seen_handles_) {
      if (is_live(handle)) result.push_back(handle);
    }
    return result;
  }
  [[nodiscard]] std::vector<std::size_t> pin_ids() const {
    std::vector<std::size_t> result;
    for (const auto& [id, pin] : pins_) {
      static_cast<void>(pin);
      result.push_back(id);
    }
    return result;
  }
  [[nodiscard]] bool is_live(ArenaHandle handle) const {
    return handle.owner == owner_ && handle.slot.value < slots_.size() &&
           slots_[handle.slot.value].known && slots_[handle.slot.value].live &&
           slots_[handle.slot.value].generation == handle.generation;
  }
  [[nodiscard]] const Row& value(ArenaHandle handle) const {
    return slots_.at(handle.slot.value).value;
  }

  void compare(std::string_view where) const {
    arena_.check_invariants();
    std::size_t live_count = 0;
    std::size_t retained_count = 0;
    std::size_t free_count = 0;
    for (const auto& slot : slots_) {
      check(slot.known && slot.generation > 0U, std::string(where) + ": model slot metadata exists");
      if (slot.live) ++live_count;
      else if (slot.pin_count > 0U) ++retained_count;
      else ++free_count;
    }
    const ArenaStatistics expected{slots_.size(), live_count, retained_count,
                                   pins_.size(), free_count, 0};
    check(arena_.statistics() == expected,
          std::string(where) + ": all arena statistics match slot/pin model");
    check(expected.slots == expected.live_records + expected.retained_records +
          expected.free_slots + expected.exhausted_slots,
          std::string(where) + ": slot accounting invariant holds");

    for (const auto handle : seen_handles_) {
      const bool expected_live = is_live(handle);
      check(arena_.contains(handle) == expected_live,
            std::string(where) + ": historical handle membership matches its generation");
      if (expected_live) {
        check(arena_.get(handle).values() == value(handle),
              std::string(where) + ": live row values match the independent model");
      } else {
        expect_error([&] { static_cast<void>(arena_.get(handle)); }, "stale_handle");
      }
    }
    for (const auto& [id, modeled_pin] : pins_) {
      static_cast<void>(id);
      const bool expected_live = is_live(modeled_pin.handle);
      check(modeled_pin.pin.handle() == modeled_pin.handle &&
            modeled_pin.pin.is_live() == expected_live &&
            modeled_pin.pin.get().values() == value(modeled_pin.handle),
            std::string(where) + ": pin liveness and retained value match the model");
    }
  }

 private:
  const TupleLayout& layout_;
  TupleArena& arena_;
  ArenaOwnerId owner_;
  std::vector<ModelSlot> slots_;
  std::vector<ArenaHandle> seen_handles_;
  std::map<std::size_t, ModelPin> pins_;
};

void churn_seed(std::uint64_t seed) {
  const auto layout = arena_layout(LayoutId{static_cast<std::size_t>(100U + seed)});
  TupleArena arena(layout);
  ArenaModel model(layout, arena);
  std::mt19937_64 random(seed);
  std::size_t next_pin_id = 1;
  std::uint64_t serial = 0;

  constexpr std::size_t operations = 650;
  for (std::size_t operation = 0; operation < operations; ++operation) {
    const auto choice = pick(random, 100U);
    const auto live = model.live_handles();
    const auto pins = model.pin_ids();
    if (choice < 32U || live.empty()) {
      static_cast<void>(model.insert(random_row(random, serial)));
      ++serial;
    } else if (choice < 51U) {
      if ((random() & 1U) != 0U || model.seen_handles().empty()) {
        static_cast<void>(model.erase(live[pick(random, live.size())]));
      } else {
        const auto& history = model.seen_handles();
        static_cast<void>(model.erase(history[pick(random, history.size())]));
      }
    } else if (choice < 57U) {
      model.clear();
    } else if (choice < 75U) {
      const auto handle = live[pick(random, live.size())];
      model.add_pin(next_pin_id, handle);
      ++next_pin_id;
    } else if (choice < 88U && !pins.empty()) {
      model.release_pin(pins[pick(random, pins.size())]);
    } else if (choice < 94U && !model.seen_handles().empty()) {
      const auto& history = model.seen_handles();
      const auto stale = history[pick(random, history.size())];
      if (!model.is_live(stale)) {
        check(!arena.contains(stale), "random stale probe remains absent");
        expect_error([&] { static_cast<void>(arena.pin(stale)); }, "stale_handle");
      } else {
        static_cast<void>(model.erase(stale));
      }
    } else {
      const ArenaHandle malformed{arena.owner(),
                                  TupleSlotId{std::numeric_limits<std::size_t>::max()}, 0};
      check(!arena.contains(malformed) && !arena.erase(malformed),
            "random malformed handle stays absent and harmless");
      expect_error([&] { static_cast<void>(arena.get(malformed)); }, "stale_handle");
    }

    const auto where = "seed " + std::to_string(seed) + ", operation " + std::to_string(operation);
    model.compare(where);
  }
}

void randomized_independent_model() {
  churn_seed(0x51A03U);
  churn_seed(0xC0FFEEU);
  churn_seed(0xBADC0DEU);
}
}  // namespace

int main() {
  try {
    type_contract_and_stable_addresses();
    handle_errors_and_immediate_invalidation();
    pins_retirement_and_clear_generation();
    moves_and_owner_lifetimes();
    randomized_independent_model();
    std::cout << "tuple arena model checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
