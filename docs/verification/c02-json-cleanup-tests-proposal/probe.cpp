#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <new>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

namespace cleanup_probe {

using Counter = std::uint64_t;

std::atomic<Counter> total_new_attempts{0};
std::atomic<Counter> total_successful_allocations{0};
std::atomic<Counter> total_deallocations{0};
std::atomic<Counter> live_allocations{0};
std::atomic<Counter> injected_failures{0};

std::atomic<Counter> cleanup_new_attempts{0};
std::atomic<Counter> cleanup_successful_allocations{0};
std::atomic<Counter> cleanup_deallocations{0};
std::atomic<Counter> cleanup_injected_failures{0};

std::atomic<bool> observe_cleanup{false};
std::atomic<bool> inject_failure{false};
std::atomic<Counter> allowed_new_before_failure{0};

bool before_new() noexcept {
  total_new_attempts.fetch_add(1, std::memory_order_relaxed);
  if (observe_cleanup.load(std::memory_order_relaxed)) {
    cleanup_new_attempts.fetch_add(1, std::memory_order_relaxed);
  }

  if (!inject_failure.load(std::memory_order_relaxed)) {
    return false;
  }

  Counter remaining = allowed_new_before_failure.load(std::memory_order_relaxed);
  while (true) {
    if (remaining == 0) {
      injected_failures.fetch_add(1, std::memory_order_relaxed);
      if (observe_cleanup.load(std::memory_order_relaxed)) {
        cleanup_injected_failures.fetch_add(1, std::memory_order_relaxed);
      }
      return true;
    }
    if (allowed_new_before_failure.compare_exchange_weak(
            remaining, remaining - 1, std::memory_order_relaxed)) {
      return false;
    }
  }
}

void allocation_succeeded() noexcept {
  total_successful_allocations.fetch_add(1, std::memory_order_relaxed);
  live_allocations.fetch_add(1, std::memory_order_relaxed);
  if (observe_cleanup.load(std::memory_order_relaxed)) {
    cleanup_successful_allocations.fetch_add(1, std::memory_order_relaxed);
  }
}

void deallocated() noexcept {
  total_deallocations.fetch_add(1, std::memory_order_relaxed);
  live_allocations.fetch_sub(1, std::memory_order_relaxed);
  if (observe_cleanup.load(std::memory_order_relaxed)) {
    cleanup_deallocations.fetch_add(1, std::memory_order_relaxed);
  }
}

struct Counts {
  Counter successful_allocations{};
  Counter deallocations{};
  Counter live{};
  Counter injected{};
};

struct Window {
  Counter new_attempts{};
  Counter successful_allocations{};
  Counter deallocations{};
  Counter injected{};
};

Counts counts() noexcept {
  return {total_successful_allocations.load(std::memory_order_relaxed),
          total_deallocations.load(std::memory_order_relaxed),
          live_allocations.load(std::memory_order_relaxed),
          injected_failures.load(std::memory_order_relaxed)};
}

Window window() noexcept {
  return {cleanup_new_attempts.load(std::memory_order_relaxed),
          cleanup_successful_allocations.load(std::memory_order_relaxed),
          cleanup_deallocations.load(std::memory_order_relaxed),
          cleanup_injected_failures.load(std::memory_order_relaxed)};
}

void begin_cleanup_window() noexcept {
  cleanup_new_attempts.store(0, std::memory_order_relaxed);
  cleanup_successful_allocations.store(0, std::memory_order_relaxed);
  cleanup_deallocations.store(0, std::memory_order_relaxed);
  cleanup_injected_failures.store(0, std::memory_order_relaxed);
  observe_cleanup.store(true, std::memory_order_relaxed);
}

void end_cleanup_window() noexcept {
  observe_cleanup.store(false, std::memory_order_relaxed);
}

void fail_after(Counter allowed) noexcept {
  allowed_new_before_failure.store(allowed, std::memory_order_relaxed);
  inject_failure.store(true, std::memory_order_relaxed);
}

void stop_failure() noexcept {
  inject_failure.store(false, std::memory_order_relaxed);
}

}  // namespace cleanup_probe

void* operator new(std::size_t size) {
  if (cleanup_probe::before_new()) {
    throw std::bad_alloc{};
  }
  void* result = std::malloc(size == 0 ? 1 : size);
  if (result == nullptr) {
    throw std::bad_alloc{};
  }
  cleanup_probe::allocation_succeeded();
  return result;
}

void* operator new[](std::size_t size) {
  return ::operator new(size);
}

void* operator new(std::size_t size, std::align_val_t alignment) {
  if (cleanup_probe::before_new()) {
    throw std::bad_alloc{};
  }
  const auto alignment_size = static_cast<std::size_t>(alignment);
  std::size_t allocation_size = size == 0 ? 1 : size;
  const std::size_t remainder = allocation_size % alignment_size;
  if (remainder != 0) {
    const std::size_t extra = alignment_size - remainder;
    if (allocation_size > std::numeric_limits<std::size_t>::max() - extra) {
      throw std::bad_alloc{};
    }
    allocation_size += extra;
  }
  void* result = std::aligned_alloc(alignment_size, allocation_size);
  if (result == nullptr) {
    throw std::bad_alloc{};
  }
  cleanup_probe::allocation_succeeded();
  return result;
}

void* operator new[](std::size_t size, std::align_val_t alignment) {
  return ::operator new(size, alignment);
}

void operator delete(void* pointer) noexcept {
  if (pointer != nullptr) {
    cleanup_probe::deallocated();
    std::free(pointer);
  }
}

void operator delete[](void* pointer) noexcept {
  ::operator delete(pointer);
}

void operator delete(void* pointer, std::size_t) noexcept {
  ::operator delete(pointer);
}

void operator delete[](void* pointer, std::size_t) noexcept {
  ::operator delete(pointer);
}

void operator delete(void* pointer, std::align_val_t) noexcept {
  ::operator delete(pointer);
}

void operator delete[](void* pointer, std::align_val_t) noexcept {
  ::operator delete(pointer);
}

void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
  ::operator delete(pointer);
}

void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
  ::operator delete(pointer);
}

namespace cleanup_probe {

template <class T>
class ProbeAllocator {
 public:
  using value_type = T;

  ProbeAllocator() noexcept = default;

  template <class U>
  ProbeAllocator(const ProbeAllocator<U>&) noexcept {}

  [[nodiscard]] T* allocate(std::size_t count) {
    return std::allocator<T>{}.allocate(count);
  }

  void deallocate(T* pointer, std::size_t count) noexcept {
    std::allocator<T>{}.deallocate(pointer, count);
  }
};

template <class T, class U>
bool operator==(const ProbeAllocator<T>&, const ProbeAllocator<U>&) noexcept {
  return true;
}

template <class T, class U>
bool operator!=(const ProbeAllocator<T>&, const ProbeAllocator<U>&) noexcept {
  return false;
}

template <class T, class Allocator = std::allocator<T>>
class ProbeArray : public std::vector<T, Allocator> {
  using Base = std::vector<T, Allocator>;

 public:
  using Base::Base;
  using Base::operator=;

  ProbeArray() = default;
};

using DefaultJson = nlohmann::json;
using OrderedJson = nlohmann::ordered_json;
using CustomArrayJson = nlohmann::basic_json<
    std::map, ProbeArray, std::string, bool, std::int64_t, std::uint64_t, double,
    ProbeAllocator>;

enum class Shape : std::uint8_t {
  empty,
  scalar,
  string_value,
  binary_value,
  wide_array,
  long_key_object,
  growth_array,
  growth_object,
  mixed_nested,
  deep_chain
};

constexpr std::array<Shape, 10> all_shapes{
    Shape::empty,         Shape::scalar,       Shape::string_value,
    Shape::binary_value,  Shape::wide_array,   Shape::long_key_object,
    Shape::growth_array,  Shape::growth_object, Shape::mixed_nested,
    Shape::deep_chain};

constexpr std::array<Shape, 9> serializable_shapes{
    Shape::empty,         Shape::scalar,      Shape::string_value,
    Shape::binary_value,  Shape::wide_array,  Shape::long_key_object,
    Shape::growth_array,  Shape::growth_object, Shape::mixed_nested};

constexpr std::string_view shape_name(Shape shape) noexcept {
  switch (shape) {
    case Shape::empty:
      return "empty";
    case Shape::scalar:
      return "scalar";
    case Shape::string_value:
      return "string";
    case Shape::binary_value:
      return "binary";
    case Shape::wide_array:
      return "wide-array";
    case Shape::long_key_object:
      return "long-key-object";
    case Shape::growth_array:
      return "growth-array";
    case Shape::growth_object:
      return "growth-object";
    case Shape::mixed_nested:
      return "mixed-nested";
    case Shape::deep_chain:
      return "deep-chain";
  }
  return "unknown";
}

template <class Json>
Json make_binary() {
  typename Json::binary_t::container_type bytes;
  bytes.reserve(2048);
  for (std::uint32_t i = 0; i < 2048; ++i) {
    bytes.push_back(static_cast<std::uint8_t>(i & 0xffU));
  }
  return Json(Json::binary(std::move(bytes)));
}

template <class Json>
Json make_case(Shape shape) {
  switch (shape) {
    case Shape::empty:
      return Json{};

    case Shape::scalar:
      return Json(std::uint64_t{42});

    case Shape::string_value:
      return Json(std::string(4096, 's'));

    case Shape::binary_value:
      return make_binary<Json>();

    case Shape::wide_array: {
      Json value = Json::array();
      for (std::size_t i = 0; i < 512; ++i) {
        value.push_back(static_cast<std::uint64_t>(i));
      }
      return value;
    }

    case Shape::long_key_object: {
      Json value = Json::object();
      for (std::size_t i = 0; i < 96; ++i) {
        std::string key(192, 'k');
        key += std::to_string(i);
        value[std::move(key)] = static_cast<std::uint64_t>(i);
      }
      return value;
    }

    case Shape::growth_array: {
      Json value = Json::array();
      for (std::size_t i = 0; i < 8; ++i) {
        value.push_back(static_cast<std::uint64_t>(i));
      }
      Json branch = Json::array();
      for (std::size_t i = 0; i < 4096; ++i) {
        branch.push_back(static_cast<std::uint64_t>(i));
      }
      value.push_back(std::move(branch));
      return value;
    }

    case Shape::growth_object: {
      Json value = Json::object();
      for (std::size_t i = 0; i < 8; ++i) {
        std::string key = "a";
        key += std::to_string(i);
        value[std::move(key)] = static_cast<std::uint64_t>(i);
      }
      Json branch = Json::array();
      for (std::size_t i = 0; i < 4096; ++i) {
        branch.push_back(static_cast<std::uint64_t>(i));
      }
      value["z_branch"] = std::move(branch);
      return value;
    }

    case Shape::mixed_nested: {
      Json value = Json::object();
      value["empty"] = Json::object();
      value["scalar"] = std::uint64_t{7};
      value["string"] = std::string(1024, 'm');
      value["binary"] = make_binary<Json>();
      Json rows = Json::array();
      for (std::size_t i = 0; i < 64; ++i) {
        Json row = Json::object();
        row["id"] = static_cast<std::uint64_t>(i);
        row["payload"] = std::string(48, 'p');
        rows.push_back(std::move(row));
      }
      value["rows"] = std::move(rows);
      return value;
    }

    case Shape::deep_chain: {
      Json root = Json::array();
      for (std::size_t i = 0; i < 4096; ++i) {
        Json parent = Json::array();
        parent.push_back(std::move(root));
        root = std::move(parent);
      }
      return root;
    }
  }
  return Json{};
}

void prime_output(const DefaultJson& value, Shape shape) {
  if (shape != Shape::deep_chain) {
    const auto serialized = value.dump();
    (void)serialized.size();
  }
}

template <class Json>
void prime_output(const Json& value, Shape shape) {
  if (shape != Shape::deep_chain) {
    const auto serialized = value.dump();
    (void)serialized.size();
  }
}

struct CaseOutcome {
  bool valid{};
  Counter cleanup_allocation_points{};
  Counter fault_points_tested{};
  Counter injected_failures{};
  Counter normal_cleanup_frees{};
  Counter fault_new_attempts{};
  Counter fault_successful_allocations{};
  Counter fault_frees{};
  bool normal_live_restored{};
  bool fault_live_restored{true};
};

bool balanced(const Counts& before, const Counts& after) noexcept {
  if (after.successful_allocations < before.successful_allocations ||
      after.deallocations < before.deallocations) {
    return false;
  }
  return after.live == before.live &&
         after.successful_allocations - before.successful_allocations ==
             after.deallocations - before.deallocations;
}

template <class Json>
CaseOutcome run_case(Shape shape) {
  CaseOutcome outcome{true, 0, 0, 0, 0, 0, 0, 0, false, true};

  const Counts normal_before = counts();
  std::optional<Json> normal_value;
  normal_value.emplace(make_case<Json>(shape));
  prime_output(*normal_value, shape);
  begin_cleanup_window();
  normal_value.reset();
  end_cleanup_window();
  const Counts normal_after = counts();
  const Window normal_window = window();
  outcome.cleanup_allocation_points = normal_window.new_attempts;
  outcome.normal_cleanup_frees = normal_window.deallocations;
  outcome.normal_live_restored = normal_after.live == normal_before.live;
  outcome.valid = balanced(normal_before, normal_after) &&
                  normal_window.successful_allocations == normal_window.new_attempts &&
                  outcome.normal_live_restored;

  if (outcome.cleanup_allocation_points > 64) {
    outcome.valid = false;
    return outcome;
  }

  const Counter trials = outcome.cleanup_allocation_points == 0
                             ? Counter{1}
                             : outcome.cleanup_allocation_points;
  for (Counter fail_after_count = 0; fail_after_count < trials;
       ++fail_after_count) {
    const Counts before = counts();
    std::optional<Json> value;
    value.emplace(make_case<Json>(shape));
    prime_output(*value, shape);

    begin_cleanup_window();
    fail_after(fail_after_count);
    value.reset();
    stop_failure();
    end_cleanup_window();

    const Counts after = counts();
    const Window observed = window();
    const bool has_cleanup_allocation = outcome.cleanup_allocation_points != 0;
    const Counter expected_attempts =
        has_cleanup_allocation ? fail_after_count + 1 : Counter{0};
    const Counter expected_successes = has_cleanup_allocation ? fail_after_count : Counter{0};
    const Counter expected_failures = has_cleanup_allocation ? Counter{1} : Counter{0};
    const bool one_failure_and_no_retry =
        observed.new_attempts == expected_attempts &&
        observed.successful_allocations == expected_successes &&
        observed.injected == expected_failures;

    outcome.valid = outcome.valid && balanced(before, after) && one_failure_and_no_retry;
    outcome.fault_new_attempts += observed.new_attempts;
    outcome.fault_successful_allocations += observed.successful_allocations;
    outcome.fault_frees += observed.deallocations;
    outcome.fault_live_restored =
        outcome.fault_live_restored && after.live == before.live;
    ++outcome.fault_points_tested;
    outcome.injected_failures += observed.injected;
  }

  if ((shape == Shape::growth_array || shape == Shape::growth_object) &&
      outcome.cleanup_allocation_points <= 2) {
    outcome.valid = false;
  }
  outcome.valid = outcome.valid && outcome.fault_live_restored;
  return outcome;
}

template <class Json>
bool cleanup_type(std::string_view label, Counter& cases, Counter& points) {
  bool valid = true;
  for (const Shape shape : all_shapes) {
    const CaseOutcome outcome = run_case<Json>(shape);
    ++cases;
    points += outcome.fault_points_tested;
    valid = valid && outcome.valid;
    std::cout << "cleanup-case " << label << '/' << shape_name(shape)
              << " normal-new-points=" << outcome.cleanup_allocation_points
              << " normal-free-calls=" << outcome.normal_cleanup_frees
              << " normal-live-restored=" << (outcome.normal_live_restored ? "yes" : "no")
              << " persistent-fault-points=" << outcome.fault_points_tested
              << " fault-new-attempts=" << outcome.fault_new_attempts
              << " fault-successful-allocations=" << outcome.fault_successful_allocations
              << " fault-free-calls=" << outcome.fault_frees
              << " injected-failures=" << outcome.injected_failures
              << " fault-live-restored=" << (outcome.fault_live_restored ? "yes" : "no")
              << " result=" << (outcome.valid ? "pass" : "fail") << '\n';
  }
  return valid;
}

template <class Json>
void serialize_type(std::string_view label) {
  std::cout << "sizeof " << label << ' ' << sizeof(Json) << '\n';
  for (const Shape shape : serializable_shapes) {
    Json value = make_case<Json>(shape);
    const std::string serialized = value.dump();
    std::cout << "case " << label << ' ' << shape_name(shape) << ' '
              << serialized.size() << '\n';
    std::cout.write(serialized.data(), static_cast<std::streamsize>(serialized.size()));
    std::cout.put('\n');
  }
  std::cout << "case " << label << " deep-chain 4096 serialization-omitted\n";
}

int serialize_all() {
  serialize_type<DefaultJson>("json");
  serialize_type<OrderedJson>("ordered_json");
  serialize_type<CustomArrayJson>("deque_json");
  return std::cout ? 0 : 2;
}

int cleanup_all() {
  Counter cases = 0;
  Counter points = 0;
  const bool default_ok = cleanup_type<DefaultJson>("json", cases, points);
  const bool ordered_ok = cleanup_type<OrderedJson>("ordered_json", cases, points);
  const bool custom_ok = cleanup_type<CustomArrayJson>("deque_json", cases, points);
  const bool valid = default_ok && ordered_ok && custom_ok;
  std::cout << "cleanup-summary cases=" << cases << " fault-points=" << points
            << " result=" << (valid ? "pass" : "fail") << '\n';
  return valid ? 0 : 1;
}

}  // namespace cleanup_probe

int main(int argc, char** argv) {
  if (argc == 2 && std::strcmp(argv[1], "--serialize") == 0) {
    return cleanup_probe::serialize_all();
  }
  if (argc == 2 && std::strcmp(argv[1], "--cleanup") == 0) {
    return cleanup_probe::cleanup_all();
  }
  std::cerr << "usage: json_cleanup_probe --serialize|--cleanup\n";
  return 2;
}
