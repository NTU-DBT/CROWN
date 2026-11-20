#include "crown/api/error.hpp"
#include "crown/resource/memory.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <limits>
#include <map>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "crown/resource/allocator.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/storage/accounted_row.hpp"
#include "crown/storage/accounted_layout.hpp"
#include "crown/storage/accounted_projection.hpp"
#include "crown/storage/accounted_arena.hpp"
#include "crown/storage/accounted_reference.hpp"
#include "crown/storage/accounted_indexed.hpp"
#include "crown/storage/accounted_table.hpp"
#include "crown/storage/accounted_plan.hpp"
#include "accounted_plan_testing.hpp"
#include "crown/storage/reference.hpp"
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
#include "accounted_indexed_testing.hpp"
#include "accounted_table_testing.hpp"
#endif

// Test-executable-only replacement new/delete. The registry and observation
// buffers are fixed storage so the tracer does not allocate recursively.
namespace memory_trace {
inline constexpr std::size_t record_capacity = 2048;
inline constexpr std::size_t attempt_capacity = 256;
struct Record { void* address = nullptr; std::size_t bytes = 0; };
inline std::array<Record, record_capacity> records{};
inline std::uint64_t live_bytes = 0;
inline thread_local std::uint64_t peak_live_bytes = 0;
inline thread_local bool enabled = false;
inline thread_local std::ptrdiff_t remaining = -1;
inline thread_local std::size_t calls = 0;
inline thread_local std::size_t successful_calls = 0;
inline thread_local std::size_t freed_calls = 0;
inline thread_local std::uint64_t successful_bytes = 0;
inline thread_local std::uint64_t freed_bytes = 0;
inline thread_local std::array<std::size_t, attempt_capacity> attempts{};
inline thread_local std::size_t attempt_count = 0;
inline thread_local bool attempt_overflow = false;
inline thread_local bool record_overflow = false;
inline thread_local bool triggered = false;

struct Observation {
  std::size_t calls = 0;
  std::size_t successful_calls = 0;
  std::size_t freed_calls = 0;
  std::uint64_t successful_bytes = 0;
  std::uint64_t freed_bytes = 0;
  std::array<std::size_t, attempt_capacity> attempts{};
  std::size_t attempt_count = 0;
  bool attempt_overflow = false;
  bool record_overflow = false;
  bool triggered = false;
};

inline Observation observe() noexcept {
  return {calls, successful_calls, freed_calls, successful_bytes, freed_bytes,
          attempts, attempt_count, attempt_overflow, record_overflow, triggered};
}

inline void position(std::size_t bytes) {
  if (!enabled) return;
  if (calls != std::numeric_limits<std::size_t>::max()) ++calls;
  else throw std::bad_alloc{};
  if (attempt_count < attempts.size()) attempts[attempt_count++] = bytes;
  else attempt_overflow = true;
  if (remaining == 0) { triggered = true; throw std::bad_alloc{}; }
  if (remaining > 0) --remaining;
}

inline void remember(void* address, std::size_t bytes) noexcept {
  if (!enabled) return;
  for (auto& record : records) {
    if (record.address == nullptr) {
      record = {address, bytes};
      ++successful_calls;
      successful_bytes += static_cast<std::uint64_t>(bytes);
      live_bytes += static_cast<std::uint64_t>(bytes);
      if (live_bytes > peak_live_bytes) peak_live_bytes = live_bytes;
      return;
    }
  }
  record_overflow = true;
}

inline void forget(void* address) noexcept {
  if (address == nullptr) return;
  for (auto& record : records) {
    if (record.address == address) {
      const auto bytes = record.bytes;
      record = {};
      live_bytes -= static_cast<std::uint64_t>(bytes);
      if (enabled) {
        ++freed_calls;
        freed_bytes += static_cast<std::uint64_t>(bytes);
      }
      return;
    }
  }
}

[[gnu::noinline]] inline void* allocate(std::size_t bytes) {
  position(bytes);
  if (void* address = std::malloc(bytes == 0 ? 1 : bytes)) {
    remember(address, bytes);
    return address;
  }
  throw std::bad_alloc{};
}

[[gnu::noinline]] inline void* aligned(std::size_t bytes, std::size_t alignment) {
  position(bytes);
  const auto actual = bytes == 0 ? std::size_t{1} : bytes;
  if (alignment <= alignof(std::max_align_t)) {
    if (void* address = std::malloc(actual)) {
      remember(address, bytes);
      return address;
    }
    throw std::bad_alloc{};
  }
  const auto remainder = actual % alignment;
  if (remainder != 0 && actual > std::numeric_limits<std::size_t>::max() - (alignment - remainder))
    throw std::bad_alloc{};
  const auto rounded = remainder == 0 ? actual : actual + (alignment - remainder);
  if (void* address = std::aligned_alloc(alignment, rounded)) {
    remember(address, bytes);
    return address;
  }
  throw std::bad_alloc{};
}

[[gnu::noinline]] inline void release(void* address) noexcept {
  forget(address);
  std::free(address);
}

class Scope {
 public:
  explicit Scope(std::ptrdiff_t fail_after = -1) noexcept {
    if (enabled) std::terminate();
    remaining = fail_after;
    calls = successful_calls = freed_calls = 0;
    successful_bytes = freed_bytes = 0;
    peak_live_bytes = live_bytes;
    attempt_count = 0;
    attempt_overflow = record_overflow = triggered = false;
    enabled = true;
  }
  Scope(const Scope&) = delete;
  Scope& operator=(const Scope&) = delete;
  ~Scope() { enabled = false; remaining = -1; }
};
} // namespace memory_trace

[[gnu::noinline]] void* operator new(std::size_t n) { return memory_trace::allocate(n); }
[[gnu::noinline]] void* operator new[](std::size_t n) { return memory_trace::allocate(n); }
[[gnu::noinline]] void* operator new(std::size_t n, const std::nothrow_t&) noexcept { try { return memory_trace::allocate(n); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new[](std::size_t n, const std::nothrow_t&) noexcept { try { return memory_trace::allocate(n); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t a) { return memory_trace::aligned(n, static_cast<std::size_t>(a)); }
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t a) { return memory_trace::aligned(n, static_cast<std::size_t>(a)); }
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t a, const std::nothrow_t&) noexcept { try { return memory_trace::aligned(n, static_cast<std::size_t>(a)); } catch (...) { return nullptr; } }
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t a, const std::nothrow_t&) noexcept { try { return memory_trace::aligned(n, static_cast<std::size_t>(a)); } catch (...) { return nullptr; } }
[[gnu::noinline]] void operator delete(void* p) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete[](void* p) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::size_t) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::size_t) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete(void* p, const std::nothrow_t&) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete[](void* p, const std::nothrow_t&) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::align_val_t) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::size_t, std::align_val_t) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::size_t, std::align_val_t) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept { memory_trace::release(p); }
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t, const std::nothrow_t&) noexcept { memory_trace::release(p); }

namespace {
using crown::resource::AllocationLifetime;
using crown::resource::MemoryAccount;
using crown::resource::MemoryBlock;
using crown::resource::MemoryPurpose;
using crown::resource::MemoryStatistics;
std::array<std::size_t, memory_trace::attempt_capacity> observed_large_block_requests{};
std::size_t observed_large_block_request_count = 0;

void verify(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}

template<class Action>
bool rejects_as(Action&& action, std::string_view category) {
  try { action(); }
  catch (const crown::resource::MemoryFailure& error) { return error.code() == category; }
  catch (const crown::storage::TupleValidationFailure& error) { return error.code() == category; }
  catch (const crown::storage::ProjectionValidationFailure& error) { return error.code() == category; }
  catch (const crown::storage::ArenaValidationFailure& error) { return error.code() == category; }
  catch (const crown::storage::TableValidationFailure& error) { return error.code() == category; }
  catch (const crown::storage::IndexFailure& error) { return error.code() == category; }
  catch (const crown::Error& error) { return error.code() == category; }
  catch (...) { return false; }
  return false;
}

template<class Action>
bool throws_bad_alloc(Action&& action) {
  try { action(); }
  catch (const crown::resource::MemoryFailure&) { return false; }
  catch (const std::bad_alloc&) { return true; }
  catch (...) { return false; }
  return false;
}

bool contains_any(const memory_trace::Observation& observation,
                  const std::array<std::size_t, memory_trace::attempt_capacity>& sizes,
                  std::size_t size_count) {
  for (std::size_t i = 0; i < observation.attempt_count; ++i)
    for (std::size_t j = 0; j < size_count; ++j)
      if (observation.attempts[i] == sizes[j]) return true;
  return false;
}

bool contains_any_since(const memory_trace::Observation& observation, std::size_t begin,
                        const std::array<std::size_t, memory_trace::attempt_capacity>& sizes,
                        std::size_t size_count) {
  for (std::size_t i = begin; i < observation.attempt_count; ++i)
    for (std::size_t j = 0; j < size_count; ++j)
      if (observation.attempts[i] == sizes[j]) return true;
  return false;
}

void verify_observation(const memory_trace::Observation& observation) {
  verify(!observation.attempt_overflow && !observation.record_overflow,
         "fixed allocation observation storage overflowed");
}

void verify_unchanged(const MemoryAccount& account, const MemoryStatistics& before,
                      const char* message) {
  verify(account.statistics() == before, message);
}

void test_measurement_and_limits() {
  using namespace memory_trace;
  const auto baseline_live = live_bytes;
  MemoryAccount measured;
  MemoryBlock measured_block;
  MemoryStatistics measured_stats;
  std::uint64_t control_observed = 0;
  std::size_t controller_calls = 0;
  std::array<std::size_t, attempt_capacity> controller_requests{};
  std::size_t controller_request_count = 0;
  std::array<std::size_t, attempt_capacity> data_requests{};
  std::size_t data_request_count = 0;
  Observation combined;
  {
    Scope scope;
    measured = MemoryAccount::create(std::numeric_limits<std::uint64_t>::max());
    control_observed = successful_bytes;
    controller_calls = successful_calls;
    controller_requests = attempts;
    controller_request_count = attempt_count;
    const auto block_attempt_offset = attempt_count;
    measured_block = measured.allocate(4096, 256, MemoryPurpose::tuple_values);
    for (std::size_t i = block_attempt_offset; i < attempt_count; ++i)
      data_requests[data_request_count++] = attempts[i];
    measured_stats = measured.statistics();
  }
  combined = observe();
  observed_large_block_requests = data_requests;
  observed_large_block_request_count = data_request_count;
  verify_observation(combined);
  verify(control_observed == MemoryAccount::control_bytes(),
         "control_bytes did not match the observed controller request");
  verify(data_request_count > 0 && combined.successful_bytes > control_observed,
         "the aligned data block produced no observed upstream request");
  const auto data_observed = combined.successful_bytes - control_observed;
  verify(measured_stats.current.requested_bytes == combined.successful_bytes &&
         measured_stats.current.allocations == combined.successful_calls,
         "current statistics did not reconcile with successful upstream requests");
  verify(measured_stats.peak_requested_bytes == combined.successful_bytes &&
         measured_stats.successful_allocations == combined.successful_calls,
         "peak or successful history did not reconcile with observed requests");
  verify(measured_stats.current.payload_bytes == 4096 && measured_block.size() == 4096,
         "payload accounting did not preserve the requested block size");
  verify(measured_stats.by_purpose[static_cast<std::size_t>(MemoryPurpose::control)].requested_bytes == control_observed &&
         measured_stats.by_purpose[static_cast<std::size_t>(MemoryPurpose::tuple_values)].requested_bytes == data_observed,
         "purpose totals did not reconcile with observed request groups");
  verify(measured_stats.by_lifetime[static_cast<std::size_t>(AllocationLifetime::active)] == measured_stats.current,
         "new allocations were not classified as active");
  verify(live_bytes == baseline_live + combined.successful_bytes,
         "tracer outstanding bytes did not retain the measured allocations");
  verify(control_observed > 0 && controller_calls > 0, "no real controller allocation was observed");
  for (const auto limit : std::array<std::uint64_t, 2>{0, control_observed - 1}) {
    const auto prior_live = live_bytes;
    bool rejected = false;
    Observation seen;
    {
      Scope scope;
      rejected = rejects_as([&] { (void)MemoryAccount::create(limit); }, "memory_limit");
      seen = observe();
    }
    verify_observation(seen);
    verify(rejected && !contains_any(seen, controller_requests, controller_request_count),
           "zero/controller-one-under limit attempted the controller allocation");
    verify(live_bytes == prior_live, "failed controller admission retained observed memory");
  }

  // Fresh account: the previously measured real request total is the limit.
  MemoryAccount exact;
  MemoryBlock exact_block;
  MemoryStatistics exact_stats;
  Observation exact_observation;
  {
    Scope scope;
    exact = MemoryAccount::create(combined.successful_bytes);
    exact_block = exact.allocate(4096, 256, MemoryPurpose::tuple_values);
    exact_stats = exact.statistics();
  }
  exact_observation = observe();
  verify_observation(exact_observation);
  verify(exact_observation.successful_bytes == combined.successful_bytes &&
         exact_stats.current.requested_bytes == combined.successful_bytes &&
         exact_stats.limit_bytes == combined.successful_bytes,
         "fresh exact-limit account did not admit the measured real request");
  verify(exact_stats.current.allocations == exact_observation.successful_calls &&
         exact_stats.peak_requested_bytes == exact_observation.successful_bytes,
         "exact-limit accounting did not match its observed upstream requests");

  // A copied handle shares the same exhausted aggregate budget.
  MemoryAccount shared = exact;
  const auto full_stats = exact.statistics();
  bool limited = false;
  Observation limit_observation;
  {
    Scope scope;
    limited = rejects_as([&] { (void)shared.allocate(1, 8, MemoryPurpose::scratch); }, "memory_limit");
  }
  limit_observation = observe();
  verify_observation(limit_observation);
  verify(limited, "shared handle did not report aggregate exhaustion");
  verify_unchanged(exact, full_stats, "limit rejection changed shared account statistics");
  verify(!contains_any(limit_observation, data_requests, data_request_count),
         "limit rejection attempted the previously measured data allocation");

  // Classification preserves current bytes and cannot refill an exhausted cap.
  const auto active_index = static_cast<std::size_t>(AllocationLifetime::active);
  const auto retained_index = static_cast<std::size_t>(AllocationLifetime::retained);
  const auto pool_index = static_cast<std::size_t>(AllocationLifetime::free_pool);
  const crown::resource::MemoryUsage data_usage{combined.successful_calls - controller_calls, data_observed, 4096};
  const crown::resource::MemoryUsage controller_usage{controller_calls, control_observed, 0};
  MemoryStatistics pool_stats;
  bool no_allocations = false;
  {
    Scope scope;
    exact_block.set_lifetime(AllocationLifetime::retained);
    auto expected = full_stats;
    expected.by_lifetime[active_index] = controller_usage;
    expected.by_lifetime[retained_index] = data_usage;
    verify(exact_block.account_statistics() == expected, "retained classification lost conservation or attribution");
    exact_block.set_lifetime(AllocationLifetime::free_pool);
    expected.by_lifetime[retained_index] = {};
    expected.by_lifetime[pool_index] = data_usage;
    pool_stats = exact_block.account_statistics();
    verify(pool_stats == expected, "free-pool classification lost conservation or attribution");
    exact.check_invariants();
    MemoryAccount copied = exact;
    verify(copied.statistics() == pool_stats, "handle copy changed shared statistics");
    no_allocations = calls == 0;
  }
  verify(no_allocations, "classification, copy, or invariant diagnostic allocated upstream memory");
  verify(pool_stats.current == full_stats.current && pool_stats.limit_bytes == full_stats.limit_bytes,
         "classification refilled or changed the exhausted account");
  limited = false;
  {
    Scope scope;
    limited = rejects_as([&] { (void)exact.allocate(1, 8, MemoryPurpose::scratch); }, "memory_limit");
  }
  limit_observation = observe();
  verify(limited && !contains_any(limit_observation, data_requests, data_request_count),
         "classification restored capacity in a full account");
  verify_unchanged(exact, pool_stats, "post-classification exhaustion changed statistics");
  {
    Scope scope;
    exact_block.set_lifetime(AllocationLifetime::active);
    verify(exact_block.account_statistics() == full_stats, "active reclassification failed to restore attribution");
    verify(calls == 0, "active reclassification allocated memory");
  }

  // The same fresh controller plus block is one byte over this limit.
  MemoryAccount under;
  MemoryStatistics under_before;
  {
    Scope scope;
    under = MemoryAccount::create(combined.successful_bytes - 1);
  }
  under_before = under.statistics();
  limited = false;
  {
    Scope scope;
    limited = rejects_as([&] { (void)under.allocate(4096, 256, MemoryPurpose::tuple_values); }, "memory_limit");
  }
  limit_observation = observe();
  verify_observation(limit_observation);
  verify(limited, "one-byte-under account admitted the measured request");
  verify_unchanged(under, under_before, "one-byte-under rejection changed statistics");
  verify(!contains_any(limit_observation, data_requests, data_request_count),
         "one-byte-under rejection attempted a data-sized upstream allocation");

  // Check observed frees and history after releasing the measured block.
  const auto before_reset = measured.statistics();
  Observation reset_observation;
  {
    Scope scope;
    measured_block.reset();
    const auto after_reset = measured.statistics();
    const auto seen = observe();
    verify(after_reset.current.requested_bytes == control_observed &&
           after_reset.current.payload_bytes == 0,
           "reset did not remove the block's current request and payload bytes");
    verify(after_reset.successful_allocations == before_reset.successful_allocations &&
           after_reset.freed_allocations == before_reset.freed_allocations + seen.freed_calls,
           "reset history did not reconcile with observed deallocations");
    verify(after_reset.peak_requested_bytes == before_reset.peak_requested_bytes,
           "reset lowered the historical peak");
    verify(after_reset.current.allocations == combined.successful_calls - seen.freed_calls,
           "post-reset current allocation count did not reconcile with the tracer");
  }
  reset_observation = observe();
  verify_observation(reset_observation);
  verify(reset_observation.calls == 0 && reset_observation.freed_bytes == data_observed,
         "reset did not free the observed data request bytes");
}

void test_alignment_zero_and_invalid_requests() {
  using namespace memory_trace;
  MemoryAccount account;
  std::array<MemoryBlock, 5> blocks;
  MemoryStatistics stats;
  Observation observation;
  constexpr std::array<std::size_t, 5> alignments{1, 8, 64, 256, 64};
  {
    Scope scope;
    account = MemoryAccount::create(1U << 20);
    for (std::size_t i = 0; i < 4; ++i)
      blocks[i] = account.allocate(37, alignments[i], MemoryPurpose::scratch);
    blocks[4] = account.allocate(0, alignments[4], MemoryPurpose::observation);
    stats = account.statistics();
  }
  observation = observe();
  verify_observation(observation);
  for (std::size_t i = 0; i < alignments.size(); ++i)
    verify(blocks[i] && reinterpret_cast<std::uintptr_t>(blocks[i].data()) % alignments[i] == 0,
           "block data did not satisfy its requested alignment");
  for (auto& block : blocks) {
    auto* bytes = static_cast<unsigned char*>(block.data());
    for (std::size_t i = 0; i < block.size(); ++i) bytes[i] = static_cast<unsigned char>(i % 251);
  }
  verify(blocks[4].size() == 0 && stats.current.payload_bytes == 148,
         "zero-sized block changed payload accounting");
  verify(stats.current.requested_bytes == observation.successful_bytes &&
         stats.current.allocations == observation.successful_calls,
         "alignment and zero-size requests did not reconcile with observed upstream bytes");

  const auto before = account.statistics();
  bool contract = false;
  {
    Scope scope;
    contract = rejects_as([&] { (void)account.allocate(4, 3, MemoryPurpose::scratch); }, "memory_contract");
  }
  auto failure_observation = observe();
  verify(contract, "non-power-of-two alignment was not rejected as a contract error");
  verify_unchanged(account, before, "invalid alignment changed account statistics");
  verify(!contains_any(failure_observation, observed_large_block_requests,
                       observed_large_block_request_count),
         "invalid alignment attempted the measured large data allocation");

  contract = false;
  {
    Scope scope;
    contract = rejects_as([&] { (void)account.allocate(4, 8, MemoryPurpose::control); }, "memory_contract");
  }
  failure_observation = observe();
  verify(contract, "data request with controller purpose was not rejected");
  verify_unchanged(account, before, "reserved-purpose rejection changed account statistics");
  verify(!contains_any(failure_observation, observed_large_block_requests,
                       observed_large_block_request_count),
         "reserved-purpose rejection attempted the measured large data allocation");

  contract = false;
  {
    Scope scope;
    contract = rejects_as([&] {
      blocks[0].set_lifetime(static_cast<AllocationLifetime>(AllocationLifetime::count));
    }, "memory_contract");
  }
  failure_observation = observe();
  verify(contract, "invalid lifetime classification was not rejected");
  verify_unchanged(account, before, "invalid lifetime rejection changed account statistics");
  verify(!contains_any(failure_observation, observed_large_block_requests,
                       observed_large_block_request_count),
         "invalid lifetime attempted the measured large data allocation");

  bool overflow = false;
  {
    Scope scope;
    overflow = rejects_as([&] {
      (void)MemoryAccount::allocation_bytes(std::numeric_limits<std::size_t>::max(), 256);
    }, "memory_overflow");
  }
  failure_observation = observe();
  verify(overflow, "overflowing allocation size did not report memory_overflow");
  verify_unchanged(account, before, "allocation-size overflow changed account statistics");
  verify(!contains_any(failure_observation, observed_large_block_requests,
                       observed_large_block_request_count),
         "allocation-size overflow attempted the measured large data allocation");

  overflow = false;
  {
    Scope scope;
    overflow = rejects_as([&] {
      (void)account.allocate(std::numeric_limits<std::size_t>::max(), 256, MemoryPurpose::scratch);
    }, "memory_overflow");
  }
  failure_observation = observe();
  verify(overflow, "overflowing block request did not report memory_overflow");
  verify_unchanged(account, before, "block-size overflow changed account statistics");
  verify(!contains_any(failure_observation, observed_large_block_requests,
                       observed_large_block_request_count),
         "overflowing block request attempted a large data allocation");

  MemoryAccount empty;
  contract = false;
  {
    Scope scope;
    contract = rejects_as([&] { (void)empty.allocate(1); }, "memory_contract");
  }
  failure_observation = observe();
  verify(contract, "empty account request was not rejected as a contract error");
  verify(!contains_any(failure_observation, observed_large_block_requests,
                       observed_large_block_request_count),
         "empty account request attempted the measured large data allocation");
}

void test_moves_and_orphaned_block() {
  using namespace memory_trace;
  MemoryAccount first;
  MemoryAccount second;
  MemoryAccount moved_to;
  MemoryBlock source;
  MemoryBlock destination;
  std::uint64_t first_owner = 0;
  std::uint64_t second_owner = 0;
  {
    Scope scope;
    first = MemoryAccount::create(1U << 18);
    second = MemoryAccount::create(1U << 18);
    source = first.allocate(48, 64, MemoryPurpose::primary_node);
    destination = second.allocate(24, 8, MemoryPurpose::scratch);
    first_owner = first.statistics().owner;
    second_owner = second.statistics().owner;
  }
  verify(first_owner != second_owner, "independent accounts reused an owner identifier");

  const auto first_data = source.data();
  const auto second_owner_stats = second.statistics();
  bool moved_without_allocation = false;
  {
    Scope scope;
    MemoryAccount copied = first;
    MemoryAccount constructed(std::move(copied));
    verify(!copied && constructed.statistics().owner == first_owner,
           "account move construction did not empty its source");
    moved_to = std::move(constructed);
    verify(!constructed, "account move assignment did not empty the constructed handle");
    MemoryAccount assignment_target = second;
    assignment_target = std::move(moved_to);
    verify(!moved_to && assignment_target.statistics().owner == first_owner,
           "account move assignment did not transfer its source");
    moved_to = std::move(assignment_target);
    MemoryBlock move_constructed(std::move(source));
    verify(!source && move_constructed.data() == first_data,
           "block move construction did not empty its source");
    destination = std::move(move_constructed);
    verify(!move_constructed && destination.data() == first_data && destination.size() == 48,
           "block move assignment did not replace its destination");
    moved_without_allocation = calls == 0;
  }
  verify(moved_without_allocation, "account or block moves allocated upstream memory");
  verify(!source && moved_to.statistics().owner == first_owner,
         "moved account state was not retained");
  const auto second_after = second.statistics();
  verify(second_after.owner == second_owner && second_after.current.payload_bytes == 0 &&
         second_after.current.allocations + 1 == second_owner_stats.current.allocations &&
         second_after.freed_allocations == second_owner_stats.freed_allocations + 1 &&
         second_after.current.requested_bytes == second_owner_stats.by_purpose[
             static_cast<std::size_t>(MemoryPurpose::control)].requested_bytes,
         "block move assignment did not release its destination's original account allocation");

  MemoryAccount orphan_owner;
  MemoryBlock survivor;
  MemoryStatistics orphan_stats;
  const auto orphan_baseline = live_bytes;
  {
    Scope scope;
    orphan_owner = MemoryAccount::create(1U << 18);
    survivor = orphan_owner.allocate(96, 64, MemoryPurpose::directory);
    orphan_stats = survivor.account_statistics();
  }
  const auto owner = orphan_stats.owner;
  verify(live_bytes == orphan_baseline + orphan_stats.current.requested_bytes,
         "orphan setup did not match observed outstanding bytes");
  orphan_owner = MemoryAccount{};
  verify(!orphan_owner && survivor && survivor.account_statistics().owner == owner,
         "live block did not retain its controller after handle destruction");
  verify(live_bytes == orphan_baseline + orphan_stats.current.requested_bytes,
         "destroying the last handle reclaimed a controller retained by a block");
  survivor.reset();
  verify(live_bytes == orphan_baseline,
         "final block release did not reclaim the retained controller and block");
}

void test_upstream_failures() {
  using namespace memory_trace;
  const auto baseline = live_bytes;
  bool bad_alloc = false;
  Observation failed_controller;
  {
    Scope scope(0);
    bad_alloc = throws_bad_alloc([&] { (void)MemoryAccount::create(std::numeric_limits<std::uint64_t>::max()); });
  }
  failed_controller = observe();
  verify_observation(failed_controller);
  verify(bad_alloc && failed_controller.triggered && failed_controller.calls == 1 &&
         failed_controller.successful_calls == 0 && failed_controller.attempt_count == 1,
         "controller upstream failure was wrapped or retried");
  verify(failed_controller.attempts[0] == MemoryAccount::control_bytes(),
         "controller failure did not target the observed controller request size");
  verify(live_bytes == baseline, "failed controller allocation leaked observed bytes");

  MemoryAccount account;
  MemoryBlock prior;
  {
    Scope scope;
    account = MemoryAccount::create(1U << 20);
    prior = account.allocate(64, 64, MemoryPurpose::scratch);
  }
  const auto before = account.statistics();
  auto* prior_data = static_cast<unsigned char*>(prior.data());
  for (std::size_t i = 0; i < prior.size(); ++i) prior_data[i] = static_cast<unsigned char>(i % 251);
  bool block_bad_alloc = false;
  Observation failed_block;
  {
    Scope scope(0); // Every attempt fails until the scope closes.
    block_bad_alloc = throws_bad_alloc([&] {
      (void)account.allocate(4096, 256, MemoryPurpose::tuple_values);
    });
  }
  failed_block = observe();
  verify_observation(failed_block);
  verify(block_bad_alloc && failed_block.triggered && failed_block.calls == 1 &&
         failed_block.successful_calls == 0 && failed_block.attempt_count == 1,
         "data-block upstream failure was wrapped or retried");
  verify(contains_any(failed_block, observed_large_block_requests,
                      observed_large_block_request_count),
         "data-block failure did not target the measured large upstream request");
  verify_unchanged(account, before, "failed upstream block allocation changed account statistics");
  verify(prior.data() == prior_data && prior.size() == 64,
         "failed upstream allocation changed the prior block identity");
  for (std::size_t i = 0; i < prior.size(); ++i)
    verify(prior_data[i] == static_cast<unsigned char>(i % 251), "upstream failure changed prior payload bytes");
  verify(live_bytes >= baseline + before.current.requested_bytes,
         "prior allocations were lost while a later upstream request failed");
  auto retry = account.allocate(32, 8, MemoryPurpose::tuple_values);
  verify(account.statistics().current.payload_bytes == before.current.payload_bytes + 32,
         "smaller allocation retry failed after persistent upstream failure");
  retry.reset();
  verify(account.statistics().current == before.current,
         "retry release did not restore prior current allocation totals");
}

void test_fixed_current_churn() {
  using namespace memory_trace;
  const auto original_live = live_bytes;
  Observation final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 20);
      const auto initial = account.statistics();
      std::uint64_t first_peak = 0;
      for (std::uint64_t round = 0; round < 128; ++round) {
        auto block = account.allocate(33, 64, MemoryPurpose::scratch);
        auto* bytes = static_cast<unsigned char*>(block.data());
        for (std::size_t i = 0; i < block.size(); ++i) bytes[i] = static_cast<unsigned char>(i % 251);
        if (round == 0) first_peak = account.statistics().peak_requested_bytes;
        block.reset();
        const auto current = account.statistics();
        verify(current.current == initial.current && current.by_purpose == initial.by_purpose &&
               current.by_lifetime == initial.by_lifetime, "churn retained current allocation state");
        verify(current.successful_allocations == initial.successful_allocations + round + 1 &&
               current.freed_allocations == initial.freed_allocations + round + 1 &&
               current.peak_requested_bytes == first_peak, "churn history/peak diverged from fixed current state");
        account.check_invariants();
      }
    }
    final = observe();
  }
  verify_observation(final);
  verify(final.successful_calls == final.freed_calls && final.successful_bytes == final.freed_bytes &&
         live_bytes == original_live, "final account release leaked observed upstream allocations");
}

void test_allocator_rebind_and_equality() {
  using namespace memory_trace;
  using crown::resource::MemoryAllocator;
  const auto baseline = live_bytes;
  Observation final;
  {
    Scope scope;
    {
      auto first = MemoryAccount::create(1U << 18);
      auto second = MemoryAccount::create(1U << 18);
      using IntAlloc = MemoryAllocator<int>;
      using Pair = std::pair<const int, int>;
      using PairAlloc = typename std::allocator_traits<IntAlloc>::template rebind_alloc<Pair>;
      using LongAlloc = typename std::allocator_traits<IntAlloc>::template rebind_alloc<long>;
      const auto purpose = MemoryPurpose::primary_node;
      IntAlloc original{first, purpose};
      PairAlloc pair_rebound{original};
      LongAlloc long_rebound{original};
      IntAlloc other_purpose{first, MemoryPurpose::scratch};
      IntAlloc other_account{second, purpose};
      verify(original == pair_rebound && original == long_rebound,
             "same account/purpose did not compare equal across rebinds");
      verify(original != other_purpose && original != other_account,
             "allocator equality ignored purpose or account identity");
      verify(std::allocator_traits<IntAlloc>::select_on_container_copy_construction(original) == original,
             "copy selection changed allocator account or purpose");
      IntAlloc moved{std::move(original)};
      verify(moved == original && moved.account().statistics().owner == first.statistics().owner,
             "allocator move did not leave both handles sharing the account");
      const auto before = first.statistics();
      const auto observation_before = observe();
      int* raw = moved.allocate(2);
      original.deallocate(raw, 2);
      const auto after = first.statistics();
      const auto observation_after = observe();
      verify(after.current == before.current &&
             after.successful_allocations == before.successful_allocations + 1 &&
             after.freed_allocations == before.freed_allocations + 1,
             "moved allocator handles did not share allocation/deallocation accounting");
      verify(observation_after.successful_bytes - observation_before.successful_bytes ==
                 observation_after.freed_bytes - observation_before.freed_bytes &&
             observation_after.successful_calls - observation_before.successful_calls ==
                 observation_after.freed_calls - observation_before.freed_calls,
             "rebound allocator request did not return all observed bytes");
      MemoryAllocator<int> empty;
      verify(throws_bad_alloc([&] { (void)empty.allocate(1); }),
             "default allocator silently allocated without an account");
    }
    final = observe();
  }
  verify_observation(final);
  verify(final.successful_calls == final.freed_calls && final.successful_bytes == final.freed_bytes &&
         live_bytes == baseline, "allocator equality test did not reclaim both account controllers");
}

void test_vector_map_allocator_accounting() {
  using namespace memory_trace;
  using crown::resource::MemoryAllocator;
  const auto baseline = live_bytes;
  Observation vector_final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 20);
      const auto initial = account.statistics();
      const auto before_alloc = observe();
      {
        std::vector<int, MemoryAllocator<int>> values{
            MemoryAllocator<int>{account, MemoryPurpose::table_state}};
        values.reserve(48);
        for (int i = 0; i < 48; ++i) values.push_back(i * 3);
        const auto allocated = observe();
        const auto current = account.statistics();
        const auto requested = allocated.successful_bytes - before_alloc.successful_bytes;
        const auto count = allocated.successful_calls - before_alloc.successful_calls;
        verify(values.size() == 48 && current.current.requested_bytes - initial.current.requested_bytes == requested &&
               current.current.allocations - initial.current.allocations == count,
               "vector current bytes did not reconcile with observed upstream requests");
        verify(current.by_purpose[static_cast<std::size_t>(MemoryPurpose::table_state)].requested_bytes == requested,
               "vector buffer was charged to the wrong purpose");
        for (int i = 0; i < 48; ++i) verify(values[static_cast<std::size_t>(i)] == i * 3,
                                             "vector population changed a value");
        {
          std::vector<int, MemoryAllocator<int>> empty{values.get_allocator()};
          empty.swap(values);
        }
        const auto cleared = account.statistics();
        verify(cleared.current == initial.current && cleared.by_purpose == initial.by_purpose,
               "vector buffer release did not restore current account bytes");
      }
    }
    vector_final = observe();
  }
  verify_observation(vector_final);
  verify(vector_final.successful_calls == vector_final.freed_calls &&
         vector_final.successful_bytes == vector_final.freed_bytes && live_bytes == baseline,
         "vector/account destruction did not reclaim every observed upstream request");

  const auto map_baseline = live_bytes;
  Observation map_final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 20);
      using Pair = std::pair<const int, int>;
      using PairAlloc = MemoryAllocator<Pair>;
      const auto purpose = MemoryPurpose::secondary_node;
      PairAlloc values_alloc{account, purpose};
      MemoryAllocator<int> rebound{values_alloc};
      verify(values_alloc == rebound && rebound.purpose() == purpose,
             "map value/node rebind changed account purpose or equality");
      const auto initial = account.statistics();
      const auto before_alloc = observe();
      {
        std::map<int, int, std::less<int>, PairAlloc> values{std::less<int>{}, values_alloc};
        for (int i = 0; i < 40; ++i) values.emplace(i, i * 5);
        const auto allocated = observe();
        const auto current = account.statistics();
        const auto requested = allocated.successful_bytes - before_alloc.successful_bytes;
        const auto count = allocated.successful_calls - before_alloc.successful_calls;
        verify(values.size() == 40 && current.current.requested_bytes - initial.current.requested_bytes == requested &&
               current.current.allocations - initial.current.allocations == count,
               "map node bytes did not reconcile with observed upstream requests");
        verify(current.by_purpose[static_cast<std::size_t>(purpose)].requested_bytes == requested,
               "rebound map nodes were charged to the wrong purpose");
        for (int i = 0; i < 40; ++i) {
          const auto found = values.find(i);
          verify(found != values.end() && found->second == i * 5, "map population changed a value");
        }
        values.clear();
        const auto cleared = account.statistics();
        verify(cleared.current == initial.current && cleared.by_purpose == initial.by_purpose,
               "map node release did not restore current account bytes");
      }
    }
    map_final = observe();
  }
  verify_observation(map_final);
  verify(map_final.successful_calls == map_final.freed_calls &&
         map_final.successful_bytes == map_final.freed_bytes && live_bytes == map_baseline,
         "map/account destruction did not reclaim every observed upstream request");
}

void test_vector_copy_budget_and_unequal_move() {
  using namespace memory_trace;
  using crown::resource::MemoryAllocator;
  using Alloc = MemoryAllocator<int>;
  constexpr int purpose_value = static_cast<int>(MemoryPurpose::tuple_values);
  const auto baseline = live_bytes;
  std::uint64_t measured_total = 0;
  std::array<std::size_t, attempt_capacity> vector_requests{};
  std::size_t vector_request_count = 0;
  Observation sample_final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(std::numeric_limits<std::uint64_t>::max());
      const auto before_alloc = observe();
      {
        std::vector<int, Alloc> sample{Alloc{account, static_cast<MemoryPurpose>(purpose_value)}};
        sample.reserve(32);
        while (sample.size() < sample.capacity()) sample.push_back(static_cast<int>(sample.size() + 7));
        const auto allocated = observe();
        const auto stats = account.statistics();
        measured_total = stats.current.requested_bytes;
        for (std::size_t i = before_alloc.attempt_count; i < allocated.attempt_count; ++i)
          vector_requests[vector_request_count++] = allocated.attempts[i];
        verify(stats.current.requested_bytes == allocated.successful_bytes &&
               stats.current.allocations == allocated.successful_calls && sample.size() == sample.capacity(),
               "vector copy budget sample did not measure its real controller and buffer requests");
        {
          std::vector<int, Alloc> empty{sample.get_allocator()};
          empty.swap(sample);
        }
      }
    }
    sample_final = observe();
  }
  verify_observation(sample_final);
  verify(measured_total > MemoryAccount::control_bytes() &&
         sample_final.successful_calls == sample_final.freed_calls &&
         sample_final.successful_bytes == sample_final.freed_bytes && live_bytes == baseline,
         "vector budget sample was not fully measured and reclaimed");

  MemoryAccount exact;
  Observation failed_copy;
  bool exhausted = false;
  Observation exact_final;
  {
    Scope scope;
    exact = MemoryAccount::create(measured_total);
    {
      std::vector<int, Alloc> source{Alloc{exact, static_cast<MemoryPurpose>(purpose_value)}};
      source.reserve(32);
      while (source.size() < source.capacity()) source.push_back(static_cast<int>(source.size() + 7));
      const auto full = exact.statistics();
      verify(full.current.requested_bytes == measured_total && full.limit_bytes == measured_total,
             "fresh vector account did not reproduce the measured exact aggregate");
      const auto* source_data = source.data();
      const auto source_size = source.size();
      const auto selected = std::allocator_traits<Alloc>::select_on_container_copy_construction(source.get_allocator());
      verify(selected == source.get_allocator(), "vector copy selection minted or changed its account");
      const auto before_failure = observe();
      exhausted = rejects_as([&] { std::vector<int, Alloc> copy(source); (void)copy; }, "memory_limit");
      failed_copy = observe();
      verify(exhausted && exact.statistics() == full,
             "shared quota copy rejection changed account statistics");
      verify(!contains_any_since(failed_copy, before_failure.attempt_count,
                                 vector_requests, vector_request_count),
             "failed vector copy attempted a data-sized upstream allocation");
      verify(source.data() == source_data && source.size() == source_size,
             "failed vector copy changed the source buffer or size");
      for (std::size_t i = 0; i < source.size(); ++i)
        verify(source[i] == static_cast<int>(i + 7), "failed vector copy changed a source value");
      {
        std::vector<int, Alloc> empty{source.get_allocator()};
        empty.swap(source);
      }
      verify(exact.statistics().current.requested_bytes == MemoryAccount::control_bytes(),
             "vector source release retained container bytes");
    }
    exact = MemoryAccount{};
    exact_final = observe();
  }
  verify_observation(failed_copy);
  verify_observation(exact_final);
  verify(exhausted && exact_final.successful_calls == exact_final.freed_calls &&
         exact_final.successful_bytes == exact_final.freed_bytes && live_bytes == baseline,
         "exact-budget vector failure path leaked observed requests");

  const auto move_baseline = live_bytes;
  Observation move_final;
  {
    Scope scope;
    {
      auto source_account = MemoryAccount::create(1U << 20);
      auto destination_account = MemoryAccount::create(1U << 20);
      const auto purpose = MemoryPurpose::tuple_values;
      const Alloc source_alloc{source_account, purpose};
      const Alloc destination_alloc{destination_account, purpose};
      verify(source_alloc != destination_alloc, "move-assignment setup did not use unequal accounts");
      std::vector<int, Alloc> source{source_alloc};
      std::vector<int, Alloc> destination{destination_alloc};
      source.reserve(16);
      for (int i = 0; i < 16; ++i) source.push_back(i + 100);
      destination.reserve(1);
      destination.push_back(-1);
      const auto source_address = reinterpret_cast<std::uintptr_t>(source.data());
      const auto source_owner = source_account.statistics().owner;
      const auto destination_before = destination_account.statistics();
      const auto both_before = source_account.statistics().current.requested_bytes +
                               destination_before.current.requested_bytes;
      const auto requests_before = observe();
      destination = std::move(source);
      const auto requests_after = observe();
      const auto destination_after = destination_account.statistics();
      const auto source_after = source_account.statistics();
      verify(destination.get_allocator() == destination_alloc &&
             destination.get_allocator().account().statistics().owner == destination_before.owner,
             "unequal-allocator move assignment changed the destination allocator/account");
      verify(source.get_allocator() == source_alloc && source_account.statistics().owner == source_owner,
             "unequal-allocator move assignment changed the source allocator/account");
      verify(reinterpret_cast<std::uintptr_t>(destination.data()) != source_address &&
             destination.size() == 16 && destination_after.successful_allocations > destination_before.successful_allocations,
             "unequal-allocator move assignment stole the source buffer instead of allocating at destination");
      for (int i = 0; i < 16; ++i)
        verify(destination[static_cast<std::size_t>(i)] == i + 100, "unequal-account move lost a source value");
      const auto both_after = source_after.current.requested_bytes + destination_after.current.requested_bytes;
      verify(both_before + (requests_after.successful_bytes - requests_before.successful_bytes) ==
                 both_after + (requests_after.freed_bytes - requests_before.freed_bytes),
             "unequal-account move did not reconcile both accounts with observed requests");
    }
    move_final = observe();
  }
  verify_observation(move_final);
  verify(move_final.successful_calls == move_final.freed_calls &&
         move_final.successful_bytes == move_final.freed_bytes && live_bytes == move_baseline,
         "unequal-account move test did not reclaim both accounts and buffers");
}

void test_open_nested_string_coverage_gap_witness() {
  using namespace memory_trace;
  using crown::resource::MemoryAllocator;
  const auto baseline = live_bytes;
  Observation final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 20);
      std::vector<std::string, MemoryAllocator<std::string>> rows{
          MemoryAllocator<std::string>{account, MemoryPurpose::tuple_values}};
      rows.reserve(1);
      const auto outer_stats = account.statistics();
      const auto before_nested = observe();
      rows.emplace_back(4096, 'x');
      const auto after_nested = observe();
      // Negative witness only: the adapter does not redirect nested string payloads.
      // This records an open integration gap, not a full-budget S05 acceptance.
      verify(rows.size() == 1 && rows[0].size() == 4096 && rows[0][0] == 'x',
             "nested string witness was not constructed");
      verify(outer_stats.current.requested_bytes == before_nested.successful_bytes,
             "outer vector request was not fully charged before nested payload creation");
      verify(account.statistics() == outer_stats &&
             after_nested.successful_bytes > before_nested.successful_bytes &&
             after_nested.successful_bytes > outer_stats.current.requested_bytes,
             "nested string payload did not appear outside outer-container accounting");
    }
    final = observe();
  }
  verify_observation(final);
  verify(final.successful_calls == final.freed_calls && final.successful_bytes == final.freed_bytes &&
         live_bytes == baseline, "nested string coverage witness did not reclaim its observed allocations");
}

void test_admission_failures_without_upstream_attempts() {
  using namespace memory_trace;
  auto full = MemoryAccount::create(MemoryAccount::control_bytes());
  const auto before = full.statistics();
  Observation rejected;
  bool limit = false, overflow = false, contract = false;
  {
    Scope scope(0); // Every ordinary allocation would fail persistently.
    limit = rejects_as([&] { (void)full.allocate(1); }, "memory_limit");
    overflow = rejects_as([&] {
      (void)full.allocate(std::numeric_limits<std::size_t>::max(), 256);
    }, "memory_overflow");
    contract = rejects_as([&] { (void)full.allocate(1, 3); }, "memory_contract");
    rejected = observe();
  }
  verify_observation(rejected);
  verify(limit && overflow && contract && rejected.calls == 0 &&
         rejected.attempt_count == 0 && full.statistics() == before,
         "resource admission diagnostics attempted an ordinary upstream allocation");
}

void test_inline_decimal_without_allocating_temporaries() {
  using crown::storage::InlineDecimal;
  constexpr std::array<std::string_view, 11> inputs{
      "-99999999999999999999999999999999999999", "-1.23",
      "-0.00000000000000000000000000000000000001", "-0.000", "+001.2300",
      "0.00000000000000000000000000000000000001", "9.9", "10",
      "99999999999999999999999999999999999999", "0.1", "1.2300"};
  // Reference parsing/formatting belongs to fixture setup, outside the scope
  // that prohibits every ordinary upstream allocation.
  std::array<crown::Decimal, inputs.size()> reference;
  std::array<std::string, inputs.size()> canonical;
  for (std::size_t i = 0; i < inputs.size(); ++i) {
    reference[i] = crown::Decimal::parse(inputs[i]);
    canonical[i] = reference[i].to_string();
  }
  memory_trace::Observation observation;
  {
    memory_trace::Scope scope(0);
    std::array<InlineDecimal, inputs.size()> actual;
    for (std::size_t i = 0; i < inputs.size(); ++i) {
      actual[i] = InlineDecimal::copy_of(reference[i]);
      std::array<char, InlineDecimal::text_capacity> buffer{};
      const auto size = actual[i].render(buffer);
      verify(std::string_view(buffer.data(), size) == canonical[i],
             "inline Decimal changed canonical formatting");
    }
    for (std::size_t i = 0; i < inputs.size(); ++i)
      for (std::size_t j = 0; j < inputs.size(); ++j)
        verify((actual[i] <=> actual[j]) == (reference[i] <=> reference[j]) &&
               (actual[i] == actual[j]) == (reference[i] == reference[j]),
               "inline Decimal ordering/equality differs from the independent scalar");
    std::array<char, 2> too_short{'#', '#'};
    verify(rejects_as([&] { (void)actual[0].render(too_short); }, "memory_contract") &&
           too_short[0] == '#' && too_short[1] == '#',
           "short Decimal output was not rejected before writing");
    observation = memory_trace::observe();
  }
  verify_observation(observation);
  verify(observation.calls == 0, "inline Decimal operations made an ordinary upstream request");
}

void test_accounted_row_payload_limits_and_lifetime() {
  using namespace memory_trace;
  using crown::storage::AccountedRow;
  std::string binary(4096, 'x');
  binary[1] = '\0';binary.back() = static_cast<char>(0xff);
  crown::Row input{std::numeric_limits<std::int64_t>::min(), std::int64_t{9007199254740993LL},
      binary, std::string{}, false, crown::Date::parse("0001-01-01"),
      crown::Decimal::parse("-99999999999999999999999999999999999999"),
      crown::Decimal::parse("-0.00000000000000000000000000000000000001")};
  const auto expected_hash = crown::row_hash(input);
  const auto baseline = live_bytes;
  std::uint64_t measured_limit = 0;
  Observation sample_final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 22);
      const auto before = observe();
      auto stored = AccountedRow::copy_of(account, input);
      const auto after = observe();
      const auto stats = account.statistics();
      measured_limit = stats.current.requested_bytes;
      verify(after.successful_calls == before.successful_calls + 1 &&
             stats.current.requested_bytes == after.successful_bytes &&
             stats.current.allocations == after.successful_calls,
             "accounted row did not reconcile its single payload block and controller");
      const auto view = stored.view();
      const auto text = std::get<std::string_view>(view[2]);
      verify(view.size() == input.size() && view.hash() == expected_hash && text == binary &&
             text.data() != std::get<std::string>(input[2]).data(),
             "accounted row did not own the complete exact binary input");
      std::get<std::string>(input[2])[0] = 'Z';
      verify(text[0] == 'x' && view.hash() == expected_hash,
             "caller mutation changed the retained accounted row");
      std::get<std::string>(input[2])[0] = 'x';
      auto same = stored.clone(account);
      auto other_account = MemoryAccount::create(1U << 22);
      auto foreign = stored.clone(other_account);
      verify(same.view() == view && foreign.view() == view &&
             same.view().cells().data() != view.cells().data() &&
             std::get<std::string_view>(same.view()[2]).data() != text.data() &&
             std::get<std::string_view>(foreign.view()[2]).data() != text.data() &&
             foreign.account_statistics().owner == other_account.statistics().owner,
             "explicit clone aliased payload bytes or ignored its destination account");
      const auto observation = observe();
      verify(account.statistics().current.requested_bytes + other_account.statistics().current.requested_bytes ==
                 observation.successful_bytes - observation.freed_bytes,
             "two clone accounts did not reconcile with all observed live requests");
    }
    sample_final = observe();
  }
  verify_observation(sample_final);
  verify(sample_final.successful_calls == sample_final.freed_calls &&
         sample_final.successful_bytes == sample_final.freed_bytes && live_bytes == baseline,
         "accounted row/clone destruction left observed bytes");

  MemoryAccount exact;
  AccountedRow prior;
  {
    Scope scope;
    exact = MemoryAccount::create(measured_limit);
    prior = AccountedRow::copy_of(exact, input);
  }
  const auto full = exact.statistics();
  const auto* old_data = prior.view().cells().data();
  bool rejected = false;
  Observation failed;
  {
    Scope scope(0);
    rejected = rejects_as([&] { (void)prior.clone(exact); }, "memory_limit");
    verify(prior.view().hash() == expected_hash && prior.view().cells().data() == old_data,
           "row quota failure changed the prior row");
    failed = observe();
  }
  verify_observation(failed);
  verify(rejected && failed.calls == 0 && exact.statistics() == full &&
         full.current.requested_bytes == measured_limit,
         "exact row limit was refilled by clone or attempted an upstream allocation");
  prior = AccountedRow{};exact = MemoryAccount{};
  verify(live_bytes == baseline, "exact-limit row was not reclaimed");
  {
    Scope scope;
    exact = MemoryAccount::create(measured_limit - 1);
  }
  const auto under_before = exact.statistics();
  {
    Scope scope(0);
    rejected = rejects_as([&] { (void)AccountedRow::copy_of(exact, input); }, "memory_limit");
    failed = observe();
  }
  verify_observation(failed);
  verify(rejected && failed.calls == 0 && exact.statistics() == under_before,
         "one-byte-under row limit allocated or changed the account");
  exact = MemoryAccount{};

  {
    Scope scope;
    exact = MemoryAccount::create(1U << 22);
    prior = AccountedRow::copy_of(exact, input);
  }
  const auto upstream_before = exact.statistics();
  {
    Scope scope(0);
    rejected = throws_bad_alloc([&] { (void)prior.clone(exact); });
    failed = observe();
  }
  verify_observation(failed);
  verify(rejected && failed.triggered && failed.calls == 1 && failed.successful_calls == 0 &&
         exact.statistics() == upstream_before && prior.view().hash() == expected_hash,
         "upstream row failure retried, changed accounting, or damaged the prior row");
  const crown::Row empty;
  {
    Scope scope;
    auto retry = AccountedRow::copy_of(exact, empty);
    verify(retry.view().empty() && retry.view().hash() == crown::row_hash(empty),
           "empty smaller row retry changed empty-row identity");
  }
  prior = AccountedRow{};exact = MemoryAccount{};
  verify(live_bytes == baseline, "row fault and retry paths leaked observed bytes");

  Observation retained_final;
  {
    Scope scope;
    exact = MemoryAccount::create(1U << 22);
    prior = AccountedRow::copy_of(exact, input);
    const auto row_owner = exact.statistics().owner;
    prior.set_lifetime(AllocationLifetime::retained);
    exact = MemoryAccount{};
    verify(prior.account_statistics().owner == row_owner && prior.view().hash() == expected_hash &&
           prior.lifetime() == AllocationLifetime::retained,
           "retained accounted row lost its controller or payload after owner release");
    prior = AccountedRow{};
    retained_final = observe();
  }
  verify_observation(retained_final);
  verify(retained_final.successful_calls == retained_final.freed_calls &&
         retained_final.successful_bytes == retained_final.freed_bytes && live_bytes == baseline,
         "last retained row did not reclaim both payload and controller");

  Observation churn_final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 22);
      auto row = AccountedRow::copy_of(account, input);
      const auto fixed = account.statistics().current;
      for (unsigned i = 0; i < 64; ++i) {
        auto next = AccountedRow::copy_of(account, input);
        row = std::move(next);
        verify(account.statistics().current == fixed && row.view().hash() == expected_hash &&
               next.view().empty(), "fixed-cardinality accounted-row churn retained prior state");
      }
      account.check_invariants();
    }
    churn_final = observe();
  }
  verify_observation(churn_final);
  verify(churn_final.successful_calls == churn_final.freed_calls &&
         churn_final.successful_bytes == churn_final.freed_bytes && live_bytes == baseline,
         "accounted row churn did not reclaim all historical allocations");
  std::printf("S05 prototype row measured_exact_upstream_limit=%llu retained_release_and_churn=passed\n",
              static_cast<unsigned long long>(measured_limit));
}

void test_accounted_row_order_matches_public_rows() {
  using crown::storage::AccountedRow;
  const std::array<crown::Row, 11> rows{
      crown::Row{}, crown::Row{std::numeric_limits<std::int64_t>::min()},
      crown::Row{std::numeric_limits<std::int64_t>::max()},
      crown::Row{std::string("a\0", 2)}, crown::Row{std::string("a\xff", 2)},
      crown::Row{false}, crown::Row{true}, crown::Row{crown::Date::parse("9999-12-31")},
      crown::Row{crown::Decimal::parse("-0.00000000000000000000000000000000000001")},
      crown::Row{crown::Decimal::parse("12345678901234567890123456789012345678")},
      crown::Row{std::int64_t{0}, std::string{}}};
  std::array<std::uint64_t, 11> hashes{};
  for (std::size_t i = 0; i < rows.size(); ++i) hashes[i] = crown::row_hash(rows[i]);
  const auto baseline = memory_trace::live_bytes;
  MemoryAccount account;
  std::array<AccountedRow, 11> stored;
  {
    memory_trace::Scope scope;
    account = MemoryAccount::create(1U << 20);
    for (std::size_t i = 0; i < rows.size(); ++i) stored[i] = AccountedRow::copy_of(account, rows[i]);
  }
  memory_trace::Observation comparison;
  {
    memory_trace::Scope scope(0);
    for (std::size_t i = 0; i < rows.size(); ++i) {
      verify(stored[i].view().hash() == hashes[i], "accounted row changed canonical hash framing");
      for (std::size_t j = 0; j < rows.size(); ++j)
        verify((stored[i].view() <=> stored[j].view()) == (rows[i] <=> rows[j]) &&
               (stored[i].view() == stored[j].view()) == (rows[i] == rows[j]),
               "accounted row changed lexicographic typed-row ordering/equality");
    }
    account.check_invariants();
    comparison = memory_trace::observe();
  }
  verify_observation(comparison);
  verify(comparison.calls == 0, "row hashing/comparison/diagnostics made an ordinary upstream request");
  for (auto& row : stored) row = AccountedRow{};
  account = MemoryAccount{};
  verify(memory_trace::live_bytes == baseline, "row ordering fixture leaked accounted storage");
}

class ForwardDeclaredOwner {
  struct Data;
  crown::resource::AccountedUnique<Data> data_;
 public:
  explicit ForwardDeclaredOwner(const MemoryAccount&);
  ~ForwardDeclaredOwner();
  [[nodiscard]] int value() const noexcept;
};
struct ForwardDeclaredOwner::Data { int value; };
ForwardDeclaredOwner::ForwardDeclaredOwner(const MemoryAccount& account)
    : data_(crown::resource::make_accounted_unique<Data>(account, MemoryPurpose::cursor, 37)) {}
ForwardDeclaredOwner::~ForwardDeclaredOwner() = default;
int ForwardDeclaredOwner::value() const noexcept { return data_->value; }

struct ProbeConstructionFailure {};
struct alignas(64) OwnershipProbe {
  inline static unsigned completed = 0;
  inline static unsigned destroyed = 0;
  std::vector<int, crown::resource::MemoryAllocator<int>> values;
  OwnershipProbe(const MemoryAccount& account, bool fail, crown::resource::MemoryAttribution attribution = {})
      : values(crown::resource::MemoryAllocator<int>(account, MemoryPurpose::scratch, attribution)) {
    values.resize(96, 37);
    if (fail) throw ProbeConstructionFailure{};
    ++completed;
  }
  ~OwnershipProbe() noexcept { ++destroyed; }
};

void test_accounted_unique_and_shared_lifetimes() {
  using namespace crown::resource;
  using namespace memory_trace;
  const auto baseline = live_bytes;
  const auto destroyed_before = OwnershipProbe::destroyed;
  Observation unique_final;
  std::size_t unique_before_release_calls = 0;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 20);
      const auto empty = account.statistics().current;
      {
        ForwardDeclaredOwner cursor_owner(account);
        verify(cursor_owner.value() == 37, "forward-declared accounted owner lost its object");
      }
      verify(account.statistics().current == empty,
             "forward-declared accounted owner did not reclaim its object");
      const auto before_unique = observe();
      auto owned = make_accounted_unique<OwnershipProbe>(account, MemoryPurpose::table_state, account, false);
      const auto allocated = observe();
      verify(account.statistics().current.requested_bytes ==
                 empty.requested_bytes + allocated.successful_bytes - before_unique.successful_bytes &&
             account.statistics().current.allocations ==
                 empty.allocations + allocated.successful_calls - before_unique.successful_calls && owned->values[42] == 37 &&
             reinterpret_cast<std::uintptr_t>(owned.get()) % alignof(OwnershipProbe) == 0,
             "unique object/member allocations did not reconcile with actual upstream requests");
      const auto before_move = observe();
      auto moved = std::move(owned);
      verify(!owned && moved->values.size() == 96 && observe().calls == before_move.calls,
             "unique ownership move allocated or lost its nested state");
      account = MemoryAccount{};
      verify(moved.get_deleter().account().statistics().current.requested_bytes ==
                 allocated.successful_bytes - allocated.freed_bytes,
             "unique deleter did not retain the object account after owner release");
      unique_before_release_calls = observe().calls;
      moved.reset();
      verify(observe().calls == unique_before_release_calls,
             "unique object/member destruction attempted an ordinary allocation");
    }
    unique_final = observe();
  }
  verify_observation(unique_final);
  verify(unique_final.successful_calls == unique_final.freed_calls &&
         unique_final.successful_bytes == unique_final.freed_bytes && live_bytes == baseline &&
         OwnershipProbe::destroyed == destroyed_before + 1 && unique_final.calls == unique_before_release_calls,
         "unique object/member/controller destruction did not fully reclaim storage");

  Observation weak_final;
  const auto shared_destroyed_before = OwnershipProbe::destroyed;
  {
    Scope scope;
    auto account = MemoryAccount::create(1U << 20);
    auto shared = make_accounted_shared<OwnershipProbe>(account, MemoryPurpose::table_state, account, false);
    const auto full = account.statistics();
    const auto allocated = observe();
    verify(full.current.requested_bytes == allocated.successful_bytes &&
           full.current.allocations == allocated.successful_calls &&
           reinterpret_cast<std::uintptr_t>(shared.get()) % alignof(OwnershipProbe) == 0,
           "shared object/control/member allocations escaped the query account");
    const auto before_share = observe();
    std::weak_ptr<OwnershipProbe> weak = shared;
    std::shared_ptr<int> alias(shared, &shared->values[42]);
    shared.reset();
    verify(!weak.expired() && *alias == 37 && observe().calls == before_share.calls,
           "alias/weak ownership allocated or prematurely destroyed the shared object");
    const auto before_strong_release_calls = observe().calls;
    alias.reset();
    const auto weak_only = account.statistics();
    const auto observed_weak_only = observe();
    verify(weak.expired() && !weak.lock() && OwnershipProbe::destroyed == shared_destroyed_before + 1 &&
           observed_weak_only.calls == before_strong_release_calls &&
           weak_only.current.requested_bytes < full.current.requested_bytes &&
           weak_only.current.requested_bytes > MemoryAccount::control_bytes() &&
           weak_only.by_purpose[static_cast<std::size_t>(MemoryPurpose::scratch)] == crown::resource::MemoryUsage{} &&
           weak_only.current.requested_bytes == observed_weak_only.successful_bytes - observed_weak_only.freed_bytes,
           "final strong release failed to free members or retain/account the weak control block");
    account = MemoryAccount{};
    verify(live_bytes == baseline + weak_only.current.requested_bytes,
           "last explicit account release lost memory still retained by a weak pointer");
    const auto before_weak_release_calls = observe().calls;
    weak.reset();
    weak_final = observe();
    verify(weak_final.calls == before_weak_release_calls,
           "final weak control-block/controller release attempted an ordinary allocation");
  }
  verify_observation(weak_final);
  verify(weak_final.successful_calls == weak_final.freed_calls &&
         weak_final.successful_bytes == weak_final.freed_bytes && live_bytes == baseline,
         "last weak release leaked its rebound control block or account controller");
}

void test_accounted_factory_construction_failures() {
  using namespace crown::resource;
  using namespace memory_trace;
  // Both variants have an accounted nested vector. Each failed allocation
  // must unwind all successfully prepared storage without a recovery request.
  for (const bool shared_mode : {false, true}) {
    const auto baseline = live_bytes;
    const auto build = [shared_mode](const MemoryAccount& account, bool constructor_failure) {
      if (shared_mode) {
        auto object = make_accounted_shared<OwnershipProbe>(account, MemoryPurpose::table_state,
                                                           account, constructor_failure);
        verify(object->values[42] == 37, "shared factory changed a nested value");
      } else {
        auto object = make_accounted_unique<OwnershipProbe>(account, MemoryPurpose::table_state,
                                                           account, constructor_failure);
        verify(object->values[42] == 37, "unique factory changed a nested value");
      }
    };
    std::size_t positions = 0;
    std::uint64_t measured_peak = 0;
    {
      Scope scope;
      {
        auto account = MemoryAccount::create(1U << 20);
        const auto start = observe();
        build(account, false);
        const auto finish = observe();
        positions = finish.successful_calls - start.successful_calls;
        measured_peak = account.statistics().peak_requested_bytes;
        verify(account.statistics().current.requested_bytes == MemoryAccount::control_bytes() &&
               finish.successful_bytes - start.successful_bytes == finish.freed_bytes - start.freed_bytes,
               "successful factory sample did not reclaim all object/member allocations");
      }
    }
    verify(positions > 0 && live_bytes == baseline, "factory allocation-position sample was empty or leaked");
    for (std::size_t position = 0; position < positions; ++position) {
      auto account = MemoryAccount::create(1U << 20);
      const auto before = account.statistics();
      bool failed = false;
      Observation fault;
      {
        Scope scope(static_cast<std::ptrdiff_t>(position));
        failed = throws_bad_alloc([&] { build(account, false); });
        fault = observe();
      }
      verify_observation(fault);
      const auto after = account.statistics();
      verify(failed && fault.triggered && fault.calls == position + 1 &&
             fault.successful_calls == position && fault.freed_calls == position &&
             fault.successful_bytes == fault.freed_bytes && after.current == before.current &&
             after.by_purpose == before.by_purpose && after.by_lifetime == before.by_lifetime,
             "persistent factory failure leaked state, changed current attribution, or allocated in recovery");
      account.check_invariants();
    }
    {
      auto account = MemoryAccount::create(1U << 20);
      const auto before = account.statistics();
      bool rejected = false;
      Observation failure;
      {
        Scope scope;
        try { build(account, true); }
        catch (const ProbeConstructionFailure&) { rejected = true; }
        failure = observe();
      }
      verify_observation(failure);
      verify(rejected && failure.calls == positions && failure.successful_calls == failure.freed_calls &&
             failure.successful_bytes == failure.freed_bytes && account.statistics().current == before.current,
             "throwing constructor did not unwind its object/control/member storage without recovery allocation");
      account.check_invariants();
    }
    // Use the measured simultaneous object+control+member peak, never an
    // inferred sizeof formula, to exercise aggregate admission on this ABI.
    for (const bool under : {false, true}) {
      auto account = MemoryAccount::create(measured_peak - (under ? 1U : 0U));
      bool limited = false;
      {
        Scope scope;
        if (under) limited = rejects_as([&] { build(account, false); }, "memory_limit");
        else build(account, false);
      }
      verify(!under || limited, "one-byte-under factory peak did not reject its nested allocation");
      verify(account.statistics().current.requested_bytes == MemoryAccount::control_bytes(),
             "factory byte-limit unwind retained object/control/member bytes");
      account.check_invariants();
    }
    verify(live_bytes == baseline, "factory failure/budget samples leaked observed requests");
    std::printf("S05 prototype factory=%s observed_allocation_positions=%zu measured_peak_upstream_bytes=%llu\n",
                shared_mode ? "shared" : "unique", positions, static_cast<unsigned long long>(measured_peak));
  }
}

void verify_attribution_partition(const MemoryAccount& account,
                                  std::span<const crown::resource::MemoryAttribution> owners) {
  using crown::resource::MemoryUsage;
  MemoryUsage total;
  std::array<MemoryUsage, crown::resource::memory_purpose_count> purposes{};
  std::array<MemoryUsage, crown::resource::allocation_lifetime_count> lifetimes{};
  const auto accumulate = [](MemoryUsage& sum, const MemoryUsage& part) {
    sum.allocations += part.allocations;
    sum.requested_bytes += part.requested_bytes;
    sum.payload_bytes += part.payload_bytes;
  };
  const auto before = account.statistics();
  const auto calls_before = memory_trace::observe().calls;
  for (const auto owner : owners) {
    const auto stats = account.statistics_for(owner);
    verify(stats.account_owner == before.owner && stats.attribution == owner,
           "operator byte report lost account or attribution identity");
    accumulate(total, stats.current);
    for (std::size_t i = 0; i < purposes.size(); ++i) accumulate(purposes[i], stats.by_purpose[i]);
    for (std::size_t i = 0; i < lifetimes.size(); ++i) accumulate(lifetimes[i], stats.by_lifetime[i]);
  }
  verify(total == before.current && purposes == before.by_purpose && lifetimes == before.by_lifetime &&
         account.statistics() == before && memory_trace::observe().calls == calls_before,
         "operator partitions failed to reconcile, changed accounting, or allocated while reporting");
}

void test_operator_attribution_without_separate_grants() {
  using namespace crown::resource;
  using namespace memory_trace;
  using crown::storage::AccountedRow;
  constexpr MemoryAttribution first{MemoryOwnerKind::support_node, 7};
  constexpr MemoryAttribution second{MemoryOwnerKind::support_node, 9};
  constexpr MemoryAttribution physical{MemoryOwnerKind::physical_source, 7};
  constexpr MemoryAttribution absent{MemoryOwnerKind::storage_table, 7};
  constexpr std::array<MemoryAttribution, 5> owners{MemoryAttribution{}, first, second, physical, absent};
  const crown::Row input{std::int64_t{9007199254740993LL}, std::string("binary\0payload", 14)};
  const auto expected_hash = crown::row_hash(input);
  const auto baseline = live_bytes;
  Observation final;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 22);
      std::array<MemoryBlock, 3> blocks;
      std::array<std::uint64_t, 3> measured_bytes{};
      for (std::size_t i = 0; i < blocks.size(); ++i) {
        const auto before = observe();
        blocks[i] = account.allocate(64 + i, 64, MemoryPurpose::support_metadata, owners[i + 1]);
        const auto after = observe();
        measured_bytes[i] = after.successful_bytes - before.successful_bytes;
        const auto stats = account.statistics_for(owners[i + 1]);
        verify(stats.current.allocations == 1 && stats.current.requested_bytes == measured_bytes[i] &&
               stats.current.payload_bytes == 64 + i && blocks[i].attribution() == owners[i + 1],
               "operator block bytes do not match the independently observed upstream request");
      }
      verify(account.statistics_for({}).current.requested_bytes == MemoryAccount::control_bytes() &&
             account.statistics_for(absent).current == MemoryUsage{},
             "controller attribution or empty distinct owner report is wrong");
      const auto before_lifetime = account.statistics_for(first);
      blocks[0].set_lifetime(AllocationLifetime::retained);
      blocks[1].set_lifetime(AllocationLifetime::free_pool);
      const auto retained = account.statistics_for(first);
      verify(retained.current == before_lifetime.current && retained.by_purpose == before_lifetime.by_purpose &&
             retained.by_lifetime[static_cast<std::size_t>(AllocationLifetime::retained)].requested_bytes == measured_bytes[0] &&
             blocks[0].attribution() == first && blocks[1].attribution() == second,
             "lifetime relabeling changed operator ownership or physical reservation");
      using Alloc = MemoryAllocator<int>;
      const Alloc first_alloc(account, MemoryPurpose::primary_node, first);
      const Alloc second_alloc(account, MemoryPurpose::primary_node, second);
      const MemoryAllocator<long> rebound(first_alloc);
      verify(first_alloc == rebound && first_alloc != second_alloc && rebound.attribution() == first,
             "allocator rebind/equality lost immutable operator attribution");
      std::vector<int, Alloc> source(first_alloc), destination(second_alloc);
      source.reserve(16);
      for (int i = 0; i < 16; ++i) source.push_back(37 + i);
      destination.reserve(1);destination.push_back(-1);
      const auto old_source = reinterpret_cast<std::uintptr_t>(source.data());
      const auto before_move = account.statistics_for(second);
      destination = std::move(source);
      verify(destination.get_allocator().attribution() == second &&
             reinterpret_cast<std::uintptr_t>(destination.data()) != old_source &&
             destination.size() == 16 && destination[15] == 52 &&
             account.statistics_for(second).current.requested_bytes > before_move.current.requested_bytes,
             "same-account unequal-operator move stole attribution instead of allocating at destination");
      auto row = AccountedRow::copy_of(account, input, first);
      auto same = row.clone(account);
      auto other = row.clone(account, second);
      verify(row.attribution() == first && same.attribution() == first && other.attribution() == second &&
             row.view().hash() == expected_hash && same.view() == row.view() && other.view() == row.view(),
             "compact-row clone lost its explicit/preserved operator attribution or values");
      const auto physical_before = account.statistics_for(physical).current;
      const auto before_factories = observe();
      auto unique = make_accounted_unique<OwnershipProbe>(physical, account, MemoryPurpose::table_state,
                                                         account, false, physical);
      auto shared = make_accounted_shared<OwnershipProbe>(physical, account, MemoryPurpose::table_state,
                                                         account, false, physical);
      const auto physical_after = account.statistics_for(physical).current;
      const auto after_factories = observe();
      verify(physical_after.requested_bytes == physical_before.requested_bytes +
                 after_factories.successful_bytes - before_factories.successful_bytes &&
             physical_after.allocations == physical_before.allocations +
                 after_factories.successful_calls - before_factories.successful_calls,
             "object/control/member allocator rebind lost operator attribution for an observed request");
      std::weak_ptr<OwnershipProbe> weak = shared;
      verify(unique.get_deleter().attribution() == physical,
             "unique ownership deleter lost its operator attribution");
      unique.reset();shared.reset();
      verify(weak.expired(), "attributed shared object survived its final strong release");
      verify_attribution_partition(account, owners);
      const auto observed = observe();
      verify(account.statistics().current.requested_bytes == observed.successful_bytes - observed.freed_bytes,
             "operator/account total omitted an actual outstanding upstream request");
      const auto steady = account.statistics().current;
      for (std::uint64_t i = 0; i < 48; ++i) {
        const MemoryAttribution transient_owner{MemoryOwnerKind::support_node, 1000 + i};
        {
          auto transient = account.allocate(8, 8, MemoryPurpose::scratch, transient_owner);
          verify(account.statistics_for(transient_owner).current.allocations == 1,
                 "transient operator report missed its real allocation");
        }
        verify(account.statistics_for(transient_owner).current == MemoryUsage{} &&
               account.statistics().current == steady,
               "historical operator attribution retained an allocation after real release");
      }
      const auto before_invalid = account.statistics();
      const auto calls_before_invalid = observe().calls;
      const MemoryAttribution invalid_query{MemoryOwnerKind::query, 1};
      const MemoryAttribution invalid_kind{MemoryOwnerKind::count, 0};
      verify(rejects_as([&] { (void)account.allocate(8, 8, MemoryPurpose::scratch, invalid_query); }, "memory_contract") &&
             rejects_as([&] { (void)account.statistics_for(invalid_kind); }, "memory_contract") &&
             rejects_as([&] { (void)Alloc(account, MemoryPurpose::primary_node, invalid_kind); }, "memory_contract") &&
             account.statistics() == before_invalid && observe().calls == calls_before_invalid,
             "invalid operator attribution allocated or changed the account");
      verify_attribution_partition(account, owners);
      account.check_invariants();
    }
    final = observe();
  }
  verify_observation(final);
  verify(final.successful_calls == final.freed_calls && final.successful_bytes == final.freed_bytes &&
         live_bytes == baseline, "operator-attributed allocations/control blocks were not fully reclaimed");

  MemoryAccount full;
  {
    Scope scope;
    full = MemoryAccount::create(MemoryAccount::control_bytes());
  }
  const auto full_before = full.statistics();
  Observation rejected;
  bool all_limited = true;
  {
    Scope scope(0);
    for (const auto owner : owners)
      all_limited = rejects_as([&] { (void)full.allocate(1, 8, MemoryPurpose::scratch, owner); }, "memory_limit") && all_limited;
    rejected = observe();
  }
  verify_observation(rejected);
  verify(all_limited && rejected.calls == 0 && full.statistics() == full_before,
         "an operator attribution minted a fresh grant on a full aggregate account");
  full = MemoryAccount{};
  verify(live_bytes == baseline, "operator limit fixture retained the account controller");
  std::puts("S05 prototype operator_partition=passed shared_limit=passed historical_tag_churn=passed");
}

crown::storage::TupleLayout metadata_fixture() {
  using namespace crown;
  using namespace crown::storage;
  std::string binding(4096, 'b');binding[9] = '\0';binding.back() = static_cast<char>(0xff);
  return TupleLayout(LayoutId{37}, {
      {ScalarType::int64, {}, VariableId{7}}, {ScalarType::string, {}, VariableId{8}},
      {ScalarType::decimal, DecimalSpec{38, 38}, VariableId{9}},
      {ScalarType::int64, {}, VariableId{7}}, {ScalarType::boolean, {}, {}}, {ScalarType::date, {}, {}},
      {ScalarType::decimal, DecimalSpec{38, 0}, VariableId{10}}},
      LayoutContext{11, std::move(binding)}, LayoutOrigin{TableId{3}, 19});
}
crown::Row metadata_row_fixture() {
  std::string binary(4096, 'v');binary[11] = '\0';binary.back() = static_cast<char>(0xff);
  return {std::int64_t{9007199254740993LL}, std::move(binary),
      crown::Decimal::parse("-0.00000000000000000000000000000000000001"),
      std::int64_t{9007199254740993LL}, true, crown::Date::parse("9999-12-31"),
      crown::Decimal::parse("99999999999999999999999999999999999999")};
}

void test_accounted_layout_identity_validation_and_retention() {
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  std::optional<TupleLayout> first(metadata_fixture()), separate(metadata_fixture());
  std::optional<std::array<TupleLayout, 3>> sources(std::in_place, std::array<TupleLayout, 3>{*first, *first, *separate});
  const auto row = metadata_row_fixture();
  auto wrong_kind = row;wrong_kind[0] = std::string("wrong");
  auto wrong_equality = row;wrong_equality[3] = std::int64_t{9};
  auto wrong_decimal = row;wrong_decimal[2] = crown::Decimal::parse("1");
  const crown::Row wrong_arity{std::int64_t{1}};
  const auto expected_hash = crown::row_hash(row);
  const LayoutContext expected_context{first->context().catalog_version,
      std::string(first->context().binding)};
  const auto baseline = live_bytes;
  MemoryAccount account;
  AccountedLayout survivor;
  std::optional<AccountedTuple> tuple;
  {
    Scope scope;
    account = MemoryAccount::create(1U << 22);
    {
      LayoutFreezeRegistry registry(account, *sources);
      auto owned = registry.get(0);
      const auto before_alias = observe().calls;
      auto alias = registry.get(1);
      verify(owned.same_token(alias) && observe().calls == before_alias,
             "source token alias was copied into another metadata allocation");
      auto independent = registry.get(2);
      verify(owned.same_descriptor(independent) && !owned.same_token(independent) &&
             owned.fields().data() != first->fields().data() && owned.context().binding.data() != first->context().binding.data() &&
             owned.context().binding == expected_context.binding && owned.id() == first->id() && owned.origin() == first->origin(),
             "frozen layout retained input storage or confused descriptor equality with token identity");
      const auto before_validation = observe().calls;
      verify(owned.validation_issue(row).ok() &&
             owned.validation_issue(wrong_arity).problem == TupleProblem::arity &&
             owned.validation_issue(wrong_kind).problem == TupleProblem::scalar_kind &&
             owned.validation_issue(wrong_equality).problem == TupleProblem::repeated_variable &&
             owned.validation_issue(wrong_equality).field == crown::FieldId{3} &&
             owned.validation_issue(wrong_decimal).problem == TupleProblem::decimal_domain &&
             rejects_as([&] { (void)owned.tuple(wrong_kind); }, "invalid_tuple") &&
             rejects_as([&] { (void)owned.tuple(wrong_decimal); }, "scalar_overflow") &&
             observe().calls == before_validation,
             "compiled tuple validation changed semantics or allocated diagnostics");
      const MemoryAttribution operator_owner{MemoryOwnerKind::support_node, 0};
      tuple.emplace(owned.tuple(row, operator_owner));
      auto clone = tuple->clone();
      auto other_token_tuple = independent.tuple(row, operator_owner);
      verify(tuple->hash() == expected_hash && tuple->attribution() == operator_owner &&
             *tuple == clone && !(*tuple == other_token_tuple) &&
             tuple->values().cells().data() != clone.values().cells().data() &&
             owned.validation_issue(tuple->values()).ok(),
             "accounted tuple clone lost values, token identity, attribution, or independent payload ownership");
      auto destination_account = MemoryAccount::create(1U << 22);
      auto destination_layout = owned.clone_to(destination_account);
      auto destination_tuple = destination_layout.tuple(tuple->values(), operator_owner);
      verify(destination_layout.same_descriptor(owned) && !destination_layout.same_token(owned) &&
             destination_tuple.values() == tuple->values() &&
             destination_layout.account_statistics().owner == destination_account.statistics().owner &&
             destination_layout.fields().data() != owned.fields().data(),
             "cross-account metadata clone retained source storage or used a foreign limit");
      survivor = owned;
      account.check_invariants();
      destination_account.check_invariants();
      const auto observation = observe();
      verify(account.statistics().current.requested_bytes + destination_account.statistics().current.requested_bytes ==
                 observation.successful_bytes - observation.freed_bytes,
             "metadata/registry/tuple/control allocation bytes did not reconcile with observed requests");
    }
  }
  sources.reset();
  // Drop both remaining public input tokens outside the trace; source input
  // allocations were never engine-owned accounting samples.
  first.reset();separate.reset();
  // New owned storage is distinct from those tokens and remains independently
  // valid; the source registry has already been destroyed.
  const auto before_reads = account.statistics();
  Observation read_only;
  {
    Scope scope(0);
    verify(survivor.context().binding == expected_context.binding && survivor.validation_issue(tuple->values()).ok() &&
           tuple->hash() == expected_hash, "owned layout/tuple depended on a destroyed registry");
    read_only = observe();
  }
  verify_observation(read_only);
  verify(read_only.calls == 0 && account.statistics() == before_reads,
         "metadata/tuple read path allocated or changed accounting");
  account = MemoryAccount{};
  verify(survivor.account_statistics().current.requested_bytes == live_bytes - baseline,
         "retained metadata/tuple lost its account after public handle release");
  {
    Scope scope;
    tuple.reset();survivor = AccountedLayout{};
  }
  verify(live_bytes == baseline, "final metadata/tuple release retained accounted controller or storage");
}

void test_accounted_layout_full_allocation_failure_sweep() {
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  const auto source = metadata_fixture();
  const auto baseline = live_bytes;
  std::size_t positions = 0;
  std::uint64_t measured_peak = 0;
  {
    Scope scope;
    {
      auto account = MemoryAccount::create(1U << 22);
      auto prior = account.allocate(64, 64, MemoryPurpose::table_state);
      const auto before = observe();
      {
        auto frozen = AccountedLayout::freeze(account, source);
        const auto after = observe();
        positions = after.successful_calls - before.successful_calls;
        measured_peak = account.statistics().peak_requested_bytes;
        verify(measured_peak == peak_live_bytes - baseline &&
               account.statistics().current.requested_bytes == after.successful_bytes - after.freed_bytes,
               "metadata peak/current did not reconcile with independent raw allocation events");
      }
    }
  }
  verify(positions > 2 && live_bytes == baseline, "metadata sample missed scratch/control allocation positions");
  for (std::size_t position = 0; position < positions; ++position) {
    MemoryAccount account;
    MemoryBlock prior;
    {
      Scope scope;
      account = MemoryAccount::create(1U << 22);
      prior = account.allocate(64, 64, MemoryPurpose::table_state);
    }
    auto* bytes = static_cast<unsigned char*>(prior.data());
    for (std::size_t i = 0; i < prior.size(); ++i) bytes[i] = static_cast<unsigned char>(i);
    const auto before = account.statistics();
    Observation failed;
    bool rejected = false;
    {
      Scope scope(static_cast<std::ptrdiff_t>(position));
      rejected = throws_bad_alloc([&] { (void)AccountedLayout::freeze(account, source); });
      failed = observe();
    }
    verify_observation(failed);
    const auto after = account.statistics();
    verify(rejected && failed.triggered && failed.calls == position + 1 &&
           failed.successful_calls == failed.freed_calls && failed.successful_bytes == failed.freed_bytes &&
           after.current == before.current && after.by_purpose == before.by_purpose && after.by_lifetime == before.by_lifetime,
           "metadata failure did not unwind scratch/descriptor/control storage without recovery allocation");
    for (std::size_t i = 0; i < prior.size(); ++i)
      verify(bytes[i] == static_cast<unsigned char>(i), "metadata failure changed prior state bytes");
    account.check_invariants();
  }
  verify(live_bytes == baseline, "metadata failure sweep retained prior/controller storage");
  for (const bool under : {false, true}) {
    MemoryAccount account;
    MemoryBlock prior;
    {
      Scope scope;
      account = MemoryAccount::create(measured_peak - (under ? 1U : 0U));
      prior = account.allocate(64, 64, MemoryPurpose::table_state);
    }
    const auto before = account.statistics().current;
    bool limited = false;
    {
      Scope scope;
      if (under) limited = rejects_as([&] { (void)AccountedLayout::freeze(account, source); }, "memory_limit");
      else { auto frozen = AccountedLayout::freeze(account, source); verify(bool(frozen), "exact metadata peak failed"); }
    }
    verify((!under || limited) && account.statistics().current == before,
           "exact/one-byte-under metadata peak boundary failed or retained scratch state");
  }
  verify(live_bytes == baseline, "metadata byte-limit fixtures retained allocations");
  std::printf("S05 prototype metadata observed_allocation_positions=%zu measured_peak_upstream_bytes=%llu\n",
              positions, static_cast<unsigned long long>(measured_peak));
}

void test_accounted_projection_values_tokens_and_retention() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  const auto baseline = live_bytes;
  std::array<FieldId, 5> fields{FieldId{1}, FieldId{0}, FieldId{2}, FieldId{3}, FieldId{1}};
  std::optional<TupleLayout> native_source(metadata_fixture());
  std::optional<TupleLayout> native_target(projected_layout(LayoutId{88}, *native_source, fields));
  const auto row = metadata_row_fixture();
  Row expected;
  {
    const Projection oracle(*native_source, *native_target, std::vector<FieldId>(fields.begin(), fields.end()));
    expected = crown::storage::export_row(oracle.apply(native_source->tuple(row)).values());
  }
  const auto expected_hash = row_hash(expected);
  MemoryAccount account;
  AccountedProjection survivor;
  std::optional<AccountedTuple> retained;
  {
    Scope scope;
    account = MemoryAccount::create(1U << 22);
    auto source = AccountedLayout::freeze(account, *native_source);
    auto target = AccountedLayout::freeze(account, *native_target);
    const MemoryAttribution input_owner{MemoryOwnerKind::support_node, 0};
    const MemoryAttribution output_owner{MemoryOwnerKind::delta_node, 0};
    const auto input = source.tuple(row, input_owner);
    auto projection = AccountedProjection::freeze(source, target, fields);
    const auto before_alias = observe().calls;
    const auto alias = projection;
    verify(projection.same_token(alias) && observe().calls == before_alias &&
           projection.fields().data() != fields.data(), "projection copy allocated or retained caller mapping storage");
    fields[0] = FieldId{99};
    retained.emplace(projection.apply(input, output_owner));
    const auto duplicate = projection.apply(input);
    verify(retained->hash() == expected_hash && *retained == duplicate &&
           retained->attribution() == output_owner && duplicate.attribution() == input_owner &&
           target.same_token(retained->layout()) && target.validation_issue(retained->values()).ok() &&
           std::get<std::string_view>(retained->values()[0]).data() != std::get<std::string_view>(input.values()[1]).data() &&
           std::get<std::string_view>(retained->values()[0]).data() != std::get<std::string_view>(retained->values()[4]).data(),
           "projection values/domain/token/attribution or independent repeated payloads differ from native oracle");
    auto other = AccountedLayout::freeze(account, *native_source);
    const auto wrong_token = other.tuple(row);
    const auto before_rejection = account.statistics();
    const auto before_calls = observe().calls;
    verify(rejects_as([&] { (void)projection.apply(wrong_token); }, "layout_mismatch") &&
           rejects_as([&] { (void)AccountedProjection::freeze(AccountedLayout{}, target, projection.fields()); }, "invalid_projection") &&
           rejects_as([&] { (void)AccountedProjection::freeze(source, target, fields); }, "invalid_projection") &&
           observe().calls == before_calls && account.statistics() == before_rejection,
           "projection mismatch/invalid mapping diagnostics allocated or changed prior state");
    {
      auto foreign = MemoryAccount::create(1U << 22);
      auto foreign_target = target.clone_to(foreign);
      const auto calls_before_foreign = observe().calls;
      verify(rejects_as([&] { (void)AccountedProjection::freeze(source, foreign_target, projection.fields()); }, "invalid_projection") &&
             observe().calls == calls_before_foreign,
             "projection admitted a foreign account or allocated its rejection diagnostic");
      foreign.check_invariants();
    }
    survivor = projection;
    account.check_invariants();
    const auto observation = observe();
    verify(account.statistics().current.requested_bytes == observation.successful_bytes - observation.freed_bytes,
           "projection mapping/scratch/control/output requests did not reconcile with independent observations");
  }
  native_source.reset();native_target.reset();
  {
    Scope scope(0);
    verify(survivor.target().same_token(retained->layout()) && retained->hash() == expected_hash &&
           survivor.fields()[0] == FieldId{1} && survivor.target().validation_issue(retained->values()).ok(),
           "retained projection/output depended on original metadata, mapping or source row");
    verify(observe().calls == 0, "retained projection read path allocated");
  }
  verify(account.statistics().current.requested_bytes == live_bytes - baseline,
         "retained projection lost physical accounting after caller metadata destruction");
  account = MemoryAccount{};
  retained.reset();survivor = AccountedProjection{};
  verify(live_bytes == baseline, "final projection/output release retained mapping/metadata/controller storage");
}

void test_accounted_projection_rejected_mapping_contracts() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  const auto native_source = metadata_fixture();
  const std::vector<FieldId> fields{FieldId{1}, FieldId{0}, FieldId{2}, FieldId{3}, FieldId{1}};
  const auto native_target = projected_layout(LayoutId{88}, native_source, fields);
  const LayoutContext context{native_target.context().catalog_version,std::string(native_target.context().binding)};
  auto different_context = context;++different_context.catalog_version;
  const std::vector<Field> target_fields(native_target.fields().begin(),native_target.fields().end());
  auto narrow_fields = target_fields;narrow_fields[2].decimal = DecimalSpec{38, 0};
  auto renamed_fields = target_fields;renamed_fields[0].variable = VariableId{999};
  struct Case { TupleLayout source;TupleLayout target;std::vector<FieldId> fields;ProjectionProblem expected; };
  const std::array<Case, 6> cases{{
      {native_source, TupleLayout(LayoutId{90}, target_fields, different_context), fields, ProjectionProblem::context},
      {native_source, native_target, {FieldId{1}}, ProjectionProblem::arity},
      {native_source, TupleLayout(LayoutId{91}, narrow_fields, context), fields, ProjectionProblem::scalar_domain},
      {native_source, TupleLayout(LayoutId{92}, renamed_fields, context), fields, ProjectionProblem::variable_identity},
      {TupleLayout(LayoutId{93}, {{ScalarType::int64, {}, {}}, {ScalarType::int64, {}, {}}}),
       TupleLayout(LayoutId{94}, {{ScalarType::int64, {}, VariableId{7}}, {ScalarType::int64, {}, VariableId{7}}}),
       {FieldId{0}, FieldId{1}}, ProjectionProblem::repeated_variable},
      {native_source, native_target, {FieldId{0}, FieldId{0}, FieldId{2}, FieldId{3}, FieldId{1}}, ProjectionProblem::scalar_domain}
  }};
  for (const auto& test : cases)
    verify(rejects_as([&] { (void)Projection(test.source, test.target, test.fields); }, "invalid_projection"),
           "invalid projection fixture was accepted by native reference oracle");
  const auto baseline = live_bytes;
  for (const auto& test : cases) {
    Scope scope;
    auto account = MemoryAccount::create(1U << 22);
    auto source = AccountedLayout::freeze(account, test.source);
    auto target = AccountedLayout::freeze(account, test.target);
    const auto before = account.statistics();
    bool rejected = false;
    try { (void)AccountedProjection::freeze(source, target, test.fields); }
    catch (const ProjectionValidationFailure& error) { rejected = error.issue() == test.expected; }
    const auto after = account.statistics();
    verify(rejected && after.current == before.current && after.by_purpose == before.by_purpose &&
           after.by_lifetime == before.by_lifetime,
           "projection descriptor proof accepted a bad mapping or retained temporary validation state");
    account.check_invariants();
    verify_observation(observe());
  }
  verify(live_bytes == baseline, "rejected projection proof retained metadata or map storage");
}

void test_accounted_projection_full_allocation_failure_sweep() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  const auto native_source = metadata_fixture();
  const std::array<FieldId, 5> fields{FieldId{1}, FieldId{0}, FieldId{2}, FieldId{3}, FieldId{1}};
  const auto native_target = projected_layout(LayoutId{88}, native_source, fields);
  const auto row = metadata_row_fixture();
  const auto baseline = live_bytes;
  std::size_t positions = 0;
  std::uint64_t measured_peak = 0;
  {
    Scope scope;
    auto account = MemoryAccount::create(1U << 22);
    auto prior = account.allocate(64, 64, MemoryPurpose::table_state);
    auto source = AccountedLayout::freeze(account, native_source);
    auto target = AccountedLayout::freeze(account, native_target);
    const auto input = source.tuple(row);
    const auto before = observe();
    auto projection = AccountedProjection::freeze(source, target, fields);
    const auto output = projection.apply(input);
    const auto after = observe();
    positions = after.successful_calls - before.successful_calls;
    measured_peak = account.statistics().peak_requested_bytes;
    verify(measured_peak == peak_live_bytes - baseline &&
           account.statistics().current.requested_bytes == after.successful_bytes - after.freed_bytes,
           "projection/output current or simultaneous peak differs from actual raw requests");
  }
  verify(positions > 2 && live_bytes == baseline, "projection sample missed scratch/control/output allocation positions");
  for (std::size_t position = 0; position < positions; ++position) {
    MemoryAccount account;
    AccountedLayout source, target;
    std::optional<AccountedTuple> input;
    {
      Scope scope;
      account = MemoryAccount::create(1U << 22);
      source = AccountedLayout::freeze(account, native_source);
      target = AccountedLayout::freeze(account, native_target);
      input.emplace(source.tuple(row));
    }
    const auto before = account.statistics();
    const auto old_hash = input->hash();
    Observation failed;
    bool rejected = false;
    {
      Scope scope(static_cast<std::ptrdiff_t>(position));
      rejected = throws_bad_alloc([&] {
        auto projection = AccountedProjection::freeze(source, target, fields);
        (void)projection.apply(*input);
      });
      failed = observe();
    }
    verify_observation(failed);
    const auto after = account.statistics();
    verify(rejected && failed.triggered && failed.calls == position + 1 &&
           failed.successful_calls == failed.freed_calls && failed.successful_bytes == failed.freed_bytes &&
           after.current == before.current && after.by_purpose == before.by_purpose && after.by_lifetime == before.by_lifetime &&
           input->hash() == old_hash && source.same_token(input->layout()),
           "projection/output failure changed prior tuple state or attempted allocating recovery");
    account.check_invariants();
  }
  verify(live_bytes == baseline, "projection failure sweep retained prior tuple/metadata storage");
  for (const bool under : {false, true}) {
    MemoryAccount account;
    MemoryBlock prior;
    {
      Scope scope;
      account = MemoryAccount::create(measured_peak - (under ? 1U : 0U));
      prior = account.allocate(64, 64, MemoryPurpose::table_state);
    }
    const auto before = account.statistics().current;
    bool limited = false;
    {
      Scope scope;
      auto construct = [&] {
        auto source = AccountedLayout::freeze(account, native_source);
        auto target = AccountedLayout::freeze(account, native_target);
        const auto input = source.tuple(row);
        auto projection = AccountedProjection::freeze(source, target, fields);
        (void)projection.apply(input);
      };
      if (under) limited = rejects_as(construct, "memory_limit");
      else construct();
    }
    verify((!under || limited) && account.statistics().current == before,
           "exact/one-byte-under complete metadata/projection/output peak failed or leaked storage");
  }
  verify(live_bytes == baseline, "projection byte-limit fixtures retained allocations");
  std::printf("S05 prototype projection observed_allocation_positions=%zu measured_peak_upstream_bytes=%llu\n",
              positions, static_cast<unsigned long long>(measured_peak));
}

void test_exact_allocation_usage_views() {
  using namespace crown::resource;
  using namespace memory_trace;
  const auto baseline = live_bytes;
  MemoryAccount account, foreign;
  MemoryBlock block;
  using Vector = std::vector<std::uint64_t, MemoryAllocator<std::uint64_t>>;
  std::optional<Vector> vector;
  MemoryUsage block_usage, vector_usage;
  {
    Scope scope;
    account = MemoryAccount::create(1U << 20);foreign = MemoryAccount::create(1U << 20);
    const auto before = observe();
    block = account.allocate(23, 64, MemoryPurpose::scratch);
    const auto after = observe();block_usage = block.usage();
    verify(block_usage == MemoryUsage{1, after.successful_bytes - before.successful_bytes, 23},
           "block usage did not report the independently observed real request");
    vector.emplace(MemoryAllocator<std::uint64_t>(account, MemoryPurpose::directory));
    const auto before_vector = observe();vector->reserve(17);const auto after_vector = observe();
    vector_usage = vector->get_allocator().allocation_usage(vector->data(), vector->capacity());
    verify(vector_usage.allocations == 1 && vector_usage.requested_bytes ==
               after_vector.successful_bytes - before_vector.successful_bytes &&
           vector_usage.payload_bytes == vector->capacity() * sizeof(std::uint64_t),
           "container usage was a capacity estimate rather than its actual request");
  }
  const auto before = account.statistics();
  Observation observed;
  {
    Scope scope(0);
    const MemoryAllocator<std::uint64_t> other(foreign, MemoryPurpose::directory);
    verify(block.usage() == block_usage && vector->get_allocator().allocation_usage(vector->data(), vector->capacity()) == vector_usage &&
           vector->get_allocator().allocation_usage(nullptr, 0) == MemoryUsage{} &&
           rejects_as([&] { (void)vector->get_allocator().allocation_usage(vector->data(), vector->capacity() + 1); }, "memory_contract") &&
           rejects_as([&] { (void)other.allocation_usage(vector->data(), vector->capacity()); }, "memory_contract"),
           "allocation introspection accepted wrong size/owner or changed its stored request");
    block.set_lifetime(AllocationLifetime::retained);
    verify(block.usage() == block_usage, "lifetime classification changed actual allocation usage");
    block.set_lifetime(AllocationLifetime::active);account.check_invariants();observed = observe();
  }
  verify_observation(observed);
  verify(observed.calls == 0 && account.statistics() == before, "allocation usage diagnostics allocated or mutated accounting");
  vector.reset();block.reset();account = MemoryAccount{};foreign = MemoryAccount{};
  verify(live_bytes == baseline, "allocation usage fixtures retained storage");
}

void test_accounted_arena_retention_generations_and_reports() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  auto native = metadata_fixture();auto row = metadata_row_fixture();const auto expected_hash = row_hash(row);
  TupleArena legacy(native);const auto old_handle = legacy.insert(native.tuple(row));
  const auto baseline = live_bytes;
  MemoryAccount account;
  AccountedLayout layout;
  std::optional<AccountedTuple> input;
  std::optional<AccountedTupleArena> arena;
  std::optional<AccountedTupleArena::Pin> first_pin, retained_pin;
  MemoryAttribution arena_owner;
  ArenaHandle second_handle;
  {
    Scope scope;
    account = MemoryAccount::create(1U << 22);layout = AccountedLayout::freeze(account, native);
    input.emplace(layout.tuple(row));
    const auto before_arena_live = live_bytes;
    arena.emplace(layout);arena_owner = arena->attribution();
    verify(arena->owner() != legacy.owner() && arena_owner == MemoryAttribution{MemoryOwnerKind::tuple_arena, arena->owner().value},
           "legacy/accounted arena identities collide or attribution is not the native owner");
    const auto before_wrong_owner = observe().calls;
    verify(rejects_as([&] { (void)arena->contains(old_handle); }, "foreign_handle") && observe().calls == before_wrong_owner,
           "accounted arena foreign-owner rejection allocated");
    {
      const auto unrelated = AccountedLayout::freeze(account, native);
      const auto wrong_tuple = unrelated.tuple(row);
      const auto before = account.statistics();const auto calls_before = observe().calls;
      verify(rejects_as([&] { (void)arena->insert(wrong_tuple); }, "layout_mismatch") &&
             observe().calls == calls_before && account.statistics() == before,
             "arena accepted a descriptor-equal foreign token or allocated its rejection");
    }
    const auto first = arena->insert(*input);first_pin.emplace(arena->pin(first));
    verify(arena->erase(first) && !arena->contains(first) && !first_pin->is_live() && first_pin->get().hash() == expected_hash,
           "erased arena pin lost payload or preserved live membership");
    auto memory = arena->memory_statistics();
    verify(memory.records == ArenaStatistics{1, 0, 1, 1, 0, 0} && memory.retained_slots.allocations == 1 &&
           memory.retained_values.allocations == 1 && memory.owner.current.requested_bytes == live_bytes - before_arena_live,
           "retained record/slot/row requests do not reconcile with raw allocations");
    second_handle = arena->insert(*input);const auto* second_address = &arena->get(second_handle);
    const auto third = arena->insert(*input);
    memory = arena->memory_statistics();
    verify(&arena->get(second_handle) == second_address && second_handle.slot != first.slot &&
           memory.records == ArenaStatistics{3, 2, 1, 1, 0, 0} && memory.directory_capacity >= 3 &&
           memory.directory_spare_payload_bytes <= memory.directory.payload_bytes &&
           memory.owner.current.requested_bytes == live_bytes - before_arena_live,
           "directory growth moved payloads, reused retained slots or hid reserved storage");
    const auto retained_bytes = memory.retained_values.requested_bytes;
    const auto before_unpin = memory.owner.current.requested_bytes;
    first_pin->reset();memory = arena->memory_statistics();
    verify(memory.records.free_slots == 1 && memory.records.retained_records == 0 &&
           memory.owner.current.requested_bytes + retained_bytes == before_unpin &&
           memory.owner.by_lifetime[static_cast<std::size_t>(AllocationLifetime::free_pool)] == memory.free_slots,
           "last unpin failed to release values or report retained reusable metadata");
    const auto before_reuse = observe().calls;auto reused = arena->insert(*input);
    verify(reused.slot == first.slot && reused.generation == first.generation + 1 && observe().calls == before_reuse + 1 &&
           !arena->contains(first), "free-slot reuse allocated metadata or failed to advance generation");
    const auto stable_memory = arena->memory_statistics();
    for (std::size_t round = 0; round < 64; ++round) {
      verify(arena->erase(reused), "arena churn erase failed");reused = arena->insert(*input);
      verify(arena->memory_statistics() == stable_memory, "fixed-cardinality arena churn leaked logical or physical state");
    }
    const auto before_move = observe().calls;
    AccountedTupleArena moved(std::move(*arena));
    verify(moved.owner() == ArenaOwnerId{arena_owner.id} && observe().calls == before_move &&
           rejects_as([&] { (void)arena->statistics(); }, "invalid_arena"), "arena move allocated or left an accessible moved-from owner");
    retained_pin.emplace(moved.pin(second_handle));moved.clear();
    verify(!retained_pin->is_live() && retained_pin->get().hash() == expected_hash && !moved.contains(third),
           "clear lost the pinned value or retained live membership");
    moved.check_invariants();account.check_invariants();
    const auto observation = observe();
    verify(account.statistics().current.requested_bytes == observation.successful_bytes - observation.freed_bytes,
           "arena query current bytes differ from all actual outstanding requests");
  }
  verify(rejects_as([&] { (void)legacy.contains(second_handle); }, "foreign_handle"),
         "legacy arena accepted an accounted owner's handle");
  input.reset();layout = AccountedLayout{};arena.reset();
  std::get<std::string>(row[1]) = "caller changed";
  {
    Scope scope(0);
    verify(retained_pin->get().hash() == expected_hash && !retained_pin->is_live(),
           "pin depended on destroyed owner, input tuple or caller string");
    verify(observe().calls == 0, "retained arena pin reads allocated");
  }
  account = MemoryAccount{};
  verify(retained_pin->get().layout().account_statistics().current.requested_bytes == live_bytes - baseline,
         "retained pin lost its complete query account after public handle release");
  {
    Scope scope(0);retained_pin.reset();first_pin.reset();
    verify(observe().calls == 0, "final arena pin/controller teardown allocated");
  }
  verify(live_bytes == baseline, "final arena pin release retained slots, directory, metadata or controller");
}

void test_accounted_arena_allocation_failures_and_limits() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  const auto native = metadata_fixture();const auto row = metadata_row_fixture();
  auto small_row = row;std::get<std::string>(small_row[1]) = "small";
  const auto baseline = live_bytes;
  struct Fixture {
    MemoryAccount account;
    AccountedLayout layout;
    std::optional<AccountedTuple> input, small;
    std::optional<AccountedTupleArena> arena;
    ArenaHandle first;
  };
  const auto prepare = [&](Fixture& fixture, std::uint64_t limit) {
    fixture.account = MemoryAccount::create(limit);fixture.layout = AccountedLayout::freeze(fixture.account, native);
    fixture.input.emplace(fixture.layout.tuple(row));fixture.small.emplace(fixture.layout.tuple(small_row));
    fixture.arena.emplace(fixture.layout);fixture.first = fixture.arena->insert(*fixture.input);
  };
  {
    MemoryAccount account;AccountedLayout layout;
    { Scope scope;account = MemoryAccount::create(1U << 22);layout = AccountedLayout::freeze(account, native); }
    const auto before = account.statistics();Observation failed;bool rejected = false;
    {
      Scope scope(0);
      rejected = throws_bad_alloc([&] { AccountedTupleArena unavailable(layout); });failed = observe();
    }
    verify_observation(failed);
    verify(rejected && failed.triggered && failed.calls == 1 && failed.successful_calls == 0 &&
           account.statistics() == before, "arena State/control construction failure changed accounting or allocated recovery");
  }
  verify(live_bytes == baseline, "failed arena construction retained metadata/controller");
  std::size_t growth_positions = 0, reuse_positions = 0;
  std::uint64_t observed_peak = 0;
  for (const bool reuse : {false, true}) {
    std::size_t positions = 0;
    {
      Scope scope;Fixture sample;prepare(sample, 1U << 22);
      if (reuse) verify(sample.arena->erase(sample.first), "arena reuse fixture erase failed");
      const auto before = observe();const auto next = sample.arena->insert(*sample.input);const auto after = observe();
      positions = after.successful_calls - before.successful_calls;
      if (!reuse) {
        observed_peak = sample.account.statistics().peak_requested_bytes;
        verify(observed_peak == peak_live_bytes - baseline, "arena simultaneous peak differs from raw allocation events");
      }
      verify(sample.arena->get(next).hash() == sample.input->hash() &&
             sample.account.statistics().current.requested_bytes == after.successful_bytes - after.freed_bytes,
             "arena allocation sample lost rows or outstanding request reconciliation");
    }
    verify(positions > 0 && live_bytes == baseline, "arena allocation sample leaked or had no positions");
    if (reuse) reuse_positions = positions;else growth_positions = positions;
    for (std::size_t position = 0; position < positions; ++position) {
      Fixture fixture;
      {
        Scope scope;prepare(fixture, 1U << 22);
        if (reuse) verify(fixture.arena->erase(fixture.first), "arena reuse fault fixture erase failed");
      }
      const auto before = fixture.account.statistics();const auto before_arena = fixture.arena->memory_statistics();
      const auto* before_address = reuse ? nullptr : &fixture.arena->get(fixture.first);
      const auto old_hash = fixture.input->hash();
      bool rejected = false;Observation failed;
      {
        Scope scope(static_cast<std::ptrdiff_t>(position));
        rejected = throws_bad_alloc([&] { (void)fixture.arena->insert(*fixture.input); });
        fixture.arena->check_invariants();failed = observe();
      }
      verify_observation(failed);const auto after = fixture.account.statistics();
      verify(rejected && failed.triggered && failed.calls == position + 1 &&
             failed.successful_calls == failed.freed_calls && failed.successful_bytes == failed.freed_bytes &&
             after.current == before.current && after.by_purpose == before.by_purpose && after.by_lifetime == before.by_lifetime &&
             after.successful_allocations == before.successful_allocations + failed.successful_calls &&
             after.freed_allocations == before.freed_allocations + failed.freed_calls &&
             fixture.arena->memory_statistics() == before_arena && fixture.input->hash() == old_hash,
             "arena allocation failure changed prior slots/counters/bytes or allocated recovery");
      if (!reuse) verify(&fixture.arena->get(fixture.first) == before_address && fixture.arena->get(fixture.first).hash() == old_hash,
                         "failed growth changed previous payload identity");
      else verify(!fixture.arena->contains(fixture.first), "failed reuse resurrected the stale generation");
      ArenaHandle retried;
      { Scope scope;retried = fixture.arena->insert(*fixture.small); }
      verify(fixture.arena->get(retried).hash() == fixture.small->hash() &&
             (!reuse || (retried.slot == fixture.first.slot && retried.generation == fixture.first.generation + 1)),
             "arena retry lost values or advanced generation during failure");
    }
    verify(live_bytes == baseline, "arena allocation failure sweep retained state");
  }
  for (const bool under : {false, true}) {
    Fixture fixture;
    { Scope scope;prepare(fixture, observed_peak - (under ? 1U : 0U)); }
    const auto before = fixture.account.statistics();const auto arena_before = fixture.arena->memory_statistics();
    const auto* old = &fixture.arena->get(fixture.first);Observation admission;bool rejected = false;
    {
      Scope scope;
      if (under) rejected = rejects_as([&] { (void)fixture.arena->insert(*fixture.input); }, "memory_limit");
      else { const auto handle = fixture.arena->insert(*fixture.input);verify(fixture.arena->contains(handle), "exact arena cap failed"); }
      admission = observe();
    }
    verify_observation(admission);
    if (under) {
      const auto after = fixture.account.statistics();
      verify(rejected && admission.calls == admission.successful_calls && admission.successful_bytes == admission.freed_bytes &&
             after.current == before.current && after.by_purpose == before.by_purpose && after.by_lifetime == before.by_lifetime &&
             fixture.arena->memory_statistics() == arena_before && &fixture.arena->get(fixture.first) == old,
             "one-byte-under arena peak allocated diagnostics or failed to preserve the previous state");
      { Scope scope;const auto smaller = fixture.arena->insert(*fixture.small);verify(fixture.arena->contains(smaller), "smaller arena cap retry failed"); }
    }
    fixture.arena->check_invariants();
  }
  verify(live_bytes == baseline, "arena exact/under-limit fixtures retained allocations");
  std::printf("S05 prototype arena growth_positions=%zu reuse_positions=%zu observed_peak_upstream_bytes=%llu\n",
              growth_positions, reuse_positions, static_cast<unsigned long long>(observed_peak));
}

void test_accounted_arena_bounded_churn_model() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  constexpr std::size_t keys = 16, pins = 8, steps = 512;
  const auto native = metadata_fixture();
  std::array<Row, keys> rows;std::array<std::uint64_t, keys> expected_hash{};
  for (std::size_t i = 0; i < keys; ++i) {
    rows[i] = metadata_row_fixture();rows[i][0] = rows[i][3] = static_cast<std::int64_t>(1000 + i);
    expected_hash[i] = row_hash(rows[i]);
  }
  const auto baseline = live_bytes;
  MemoryAccount account;
  AccountedLayout layout;
  std::array<std::optional<AccountedTuple>, keys> inputs;
  std::optional<AccountedTupleArena> arena;
  std::array<std::optional<ArenaHandle>, keys> live{};
  std::array<std::optional<AccountedTupleArena::Pin>, pins> retained;
  std::array<std::size_t, pins> retained_key{};
  std::uint64_t before_arena = 0, maximum_observed = baseline;
  {
    Scope scope;account = MemoryAccount::create(1U << 22);layout = AccountedLayout::freeze(account, native);
    for (std::size_t i = 0; i < keys; ++i) inputs[i].emplace(layout.tuple(rows[i]));
    before_arena = live_bytes;arena.emplace(layout);maximum_observed = peak_live_bytes;
  }
  std::uint32_t random = 0x41c0ffeeU;std::size_t maximum_slots = 0;
  for (std::size_t step = 0; step < steps; ++step) {
    random = random * 1664525U + 1013904223U;
    const auto key = static_cast<std::size_t>((random >> 8) % keys);
    const auto pin_slot = static_cast<std::size_t>((random >> 16) % pins);
    {
      Scope scope;
      switch (random % 5) {
        case 0: if (!live[key]) live[key] = arena->insert(*inputs[key]);break;
        case 1: if (live[key]) { verify(arena->erase(*live[key]), "arena model erase failed");live[key].reset(); }break;
        case 2:
          if (live[key]) { retained[pin_slot].reset();retained[pin_slot].emplace(arena->pin(*live[key]));retained_key[pin_slot] = key; }
          break;
        case 3: retained[pin_slot].reset();break;
        case 4: if (step % 37 == 0) { arena->clear();for (auto& handle : live) handle.reset(); }break;
      }
      if (peak_live_bytes > maximum_observed) maximum_observed = peak_live_bytes;
      verify_observation(observe());
    }
    std::size_t expected_live = 0, expected_pins = 0, expected_retained = 0;
    std::array<ArenaHandle, pins> distinct_retained{};
    {
      Scope scope(0);
      for (std::size_t i = 0; i < keys; ++i) if (live[i]) {
        ++expected_live;verify(arena->contains(*live[i]) && arena->get(*live[i]).hash() == expected_hash[i], "arena model live payload mismatch");
      }
      for (std::size_t i = 0; i < pins; ++i) if (retained[i]) {
        ++expected_pins;const auto handle = retained[i]->handle();const auto source = retained_key[i];
        const bool is_live = live[source] && *live[source] == handle;
        verify(retained[i]->is_live() == is_live && retained[i]->get().hash() == expected_hash[source], "arena model pin lifetime mismatch");
        if (!is_live) {
          bool seen = false;
          for (std::size_t j = 0; j < expected_retained; ++j) if (distinct_retained[j] == handle) seen = true;
          if (!seen) distinct_retained[expected_retained++] = handle;
        }
      }
      const auto memory = arena->memory_statistics();
      verify(memory.records.live_records == expected_live && memory.records.pins == expected_pins &&
             memory.records.retained_records == expected_retained && memory.records.slots <= keys + pins &&
             memory.live_values.allocations == expected_live && memory.retained_values.allocations == expected_retained &&
             memory.owner.current.requested_bytes == live_bytes - before_arena,
             "arena model record census or actual requested bytes diverged");
      if (memory.records.slots > maximum_slots) maximum_slots = memory.records.slots;
      arena->check_invariants();verify(observe().calls == 0, "arena model diagnostics allocated");
    }
  }
  {
    Scope scope(0);arena->clear();for (auto& pin : retained) pin.reset();
    const auto memory = arena->memory_statistics();
    verify(memory.records.live_records == 0 && memory.records.retained_records == 0 &&
           memory.records.free_slots == memory.records.slots && memory.live_values == MemoryUsage{} && memory.retained_values == MemoryUsage{},
           "arena churn retained logical records or values after final clear");
    for (std::size_t i = 0; i < 64; ++i) arena->clear();
    verify(arena->memory_statistics() == memory && observe().calls == 0, "no-op clear allocated or changed reserved metadata");
  }
  verify(account.statistics().peak_requested_bytes == maximum_observed - baseline, "arena churn peak history differs from independent observed maxima");
  arena.reset();for (auto& input : inputs) input.reset();layout = AccountedLayout{};account = MemoryAccount{};
  verify(live_bytes == baseline, "arena churn fixture retained query storage");
  std::printf("S05 prototype arena_model steps=%zu maximum_slots=%zu\n", steps, maximum_slots);
}

struct NativeTableInput {
  using TupleLayout = crown::storage::TupleLayout;
  inline static constexpr std::array<crown::FieldId, 1> first{{{0}}}, second{{{1}}}, third{{{2}}};
  TupleLayout layout{crown::LayoutId{6001}, {{crown::ScalarType::int64}, {crown::ScalarType::string}, {crown::ScalarType::boolean}}};
  std::array<TupleLayout, 3> targets{
    crown::storage::projected_layout(crown::LayoutId{6002}, layout, first),
    crown::storage::projected_layout(crown::LayoutId{6003}, layout, second),
    crown::storage::projected_layout(crown::LayoutId{6004}, layout, third)};
  std::array<crown::Row, 4> rows{
    crown::Row{std::int64_t{1}, std::string(4096, 'k'), true},
    crown::Row{std::int64_t{1}, std::string(4096, 'k'), false},
    crown::Row{std::int64_t{2}, std::string(4096, 'k'), true},
    crown::Row{std::int64_t{3}, std::string("small"), true}};
};
struct NativeAccountedTableFixture {
  crown::resource::MemoryAccount account;
  crown::storage::AccountedLayout layout;
  std::array<crown::storage::AccountedLayout, 3> targets;
  std::array<crown::storage::AccountedProjection, 3> projections;
  std::array<std::optional<crown::storage::AccountedTuple>, 4> input;
  std::optional<crown::storage::AccountedReferenceTable> table;
  std::optional<crown::storage::AccountedReferenceTable::Journal> journal;
  std::array<crown::TupleHandle, 2> handles{};
  std::array<crown::IndexId, 2> indices{};
  std::uint64_t before_table_live = 0;
  void prepare_metadata(const NativeTableInput& native, std::uint64_t limit = 1U << 24) {
    using namespace crown::storage;
    account = crown::resource::MemoryAccount::create(limit);layout = AccountedLayout::freeze(account, native.layout);
    const std::array<std::span<const crown::FieldId>, 3> fields{native.first, native.second, native.third};
    for (std::size_t i = 0; i < targets.size(); ++i) {
      targets[i] = AccountedLayout::freeze(account, native.targets[i]);
      projections[i] = AccountedProjection::freeze(layout, targets[i], fields[i]);
    }
    for (std::size_t i = 0; i < input.size(); ++i) input[i].emplace(layout.tuple(native.rows[i]));
    before_table_live = memory_trace::live_bytes;
  }
  void prepare(const NativeTableInput& native, std::uint64_t limit = 1U << 24) {
    prepare_metadata(native, limit);
    table.emplace(crown::RelationId{6001}, layout);
    for (std::size_t i = 0; i < indices.size(); ++i) indices[i] = table->add_index(projections[i]);
    for (std::size_t i = 0; i < handles.size(); ++i) handles[i] = table->insert(*input[i]).handle;
  }
};

void test_native_table_ownership_journals_and_cursors() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;
  ReferenceTable oracle(RelationId{6001}, native.layout);
  const auto legacy = oracle.insert(native.layout.tuple(native.rows[0])).handle;
  const auto baseline = live_bytes;
  std::optional<AccountedTupleArena::Pin> pin;
  std::optional<AccountedReferenceTable::Cursor> retained_cursor;
  std::optional<AccountedReferenceTable::Journal> history;
  std::optional<AccountedVector<AccountedTuple>> snapshot;
  std::optional<AccountedVector<AccountedTuple>> keys;
  MemoryAccount observer;
  {
    NativeAccountedTableFixture f;
    {
      Scope scope;f.prepare(native);observer = f.account;
      const auto memory = f.table->memory_statistics();
      verify(memory.live_records == 2 && memory.indices == 2 && memory.secondary_keys == 2 && memory.memberships == 4 &&
             memory.owned.requested_bytes == live_bytes - f.before_table_live && f.table->owner() != legacy.owner &&
             f.table->attribution() == MemoryAttribution{MemoryOwnerKind::storage_table, f.table->owner().value},
             "native accounted table state/indices/rows do not reconcile with raw requests or owner identity");
      auto cursor = f.table->live();auto key_cursor = f.table->index_keys(f.indices[0]);
      const auto before_noop = observe().calls;
      verify(!f.table->insert(*f.input[0]).inserted && !f.table->erase(TupleHandle{f.table->owner(), f.table->relation(), TupleId{999}}) &&
             f.table->add_index(f.projections[0]) == f.indices[0] && !f.table->drop_index(IndexId{999}) && observe().calls == before_noop,
             "native table no-ops allocate or change registered index identity");
      verify(cursor.next().has_value() && key_cursor.next()->degree == 2, "no-op invalidated native cursors");
      const auto pointer = f.table->get(f.handles[0]);pin.emplace(f.table->pin(f.handles[0]));const auto generation = pin->handle();
      auto transaction = f.table->journal();
      verify(rejects_as([&] { (void)f.table->live(); }, "storage_busy"), "exclusive table journal allowed a public cursor");
      verify(transaction.erase(f.handles[0]) && transaction.change(0).tuple.hash() == row_hash(native.rows[0]), "native erase journal lost before payload");
      auto tentative = transaction.live();
      const auto retained = f.table->memory_statistics();
      verify(retained.live_records == 1 && retained.active_undo_entries == 1 && retained.arena.records.retained_records == 1 &&
             retained.table.by_lifetime[static_cast<std::size_t>(AllocationLifetime::retained)].allocations >= 5,
             "detached standard-container nodes or undo keys were not physically reported as retained");
      const auto before_rollback = observe().calls;transaction.rollback();
      verify(observe().calls == before_rollback && f.table->get(f.handles[0]) == pointer && pin->handle() == generation && pin->is_live() &&
             rejects_as([&] { (void)tentative.next(); }, "invalid_cursor") &&
             rejects_as([&] { (void)cursor.next(); }, "invalid_cursor"), "native rollback allocated, changed payload/generation or preserved invalid cursors");
      f.table->check_invariants();
      auto committed = f.table->journal();verify(committed.erase(f.handles[0]), "committed erase failed");committed.commit();
      verify(!committed.active() && committed.size() == 1 && !pin->is_live() && f.table->memory_statistics().retained_undo_entries == 1,
             "committed journal failed to retain its history under the query account");
      history.emplace(std::move(committed));snapshot.emplace(f.table->snapshot());keys.emplace(f.table->keys(f.indices[0]));
      verify(snapshot->size() == 1 && keys->size() == 1 && snapshot->get_allocator().attribution().kind == MemoryOwnerKind::output &&
             snapshot->front().attribution() == snapshot->get_allocator().attribution(), "snapshot/key exports lost their controlled output owner");
      retained_cursor.emplace(f.table->live());f.table->clear();
      verify(f.table->size() == 0 && f.table->key_count(f.indices[0]) == 0, "native clear retained index membership");
      f.table->check_invariants();
      const auto observation = observe();verify_observation(observation);
      verify(f.account.statistics().current.requested_bytes == observation.successful_bytes - observation.freed_bytes,
             "native table, retained history or output bytes escaped the query account");
    }
    f.table.reset();
    verify(rejects_as([&] { (void)retained_cursor->next(); }, "invalid_cursor"), "cursor outlived native table facade");
    verify(history->change(0).tuple.hash() == row_hash(native.rows[0]) && snapshot->front().hash() == row_hash(native.rows[1]),
           "committed change/output depended on destroyed native table");
  }
  verify(observer.statistics().current.requested_bytes == live_bytes - baseline, "orphaned native history/output/weak controls are unaccounted");
  {
    Scope scope(0);history.reset();retained_cursor.reset();snapshot.reset();keys.reset();pin.reset();
    observer.check_invariants();verify(observe().calls == 0, "native final journal/cursor/output/pin release allocated");
  }
  observer = MemoryAccount{};verify(live_bytes == baseline, "native table ownership fixture leaked");
}

void perform_native_table_operation(NativeAccountedTableFixture& f, std::size_t operation) {
  switch (operation) {
    case 0: (void)f.table->insert(*f.input[2]);break;
    case 1: (void)f.table->add_index(f.projections[2]);break;
    case 2: (void)f.table->erase(f.handles[0]);break;
    case 3: { const auto key = f.projections[0].apply(*f.input[0]);(void)f.table->erase_key(f.indices[0], key);break; }
    case 4: (void)f.journal->insert(*f.input[2]);break;
    case 5: (void)f.journal->erase(f.handles[0]);break;
    case 6: (void)f.table->snapshot();break;
    case 7: (void)f.table->snapshot_copy();break;
    case 8: (void)f.table->keys(f.indices[0]);break;
    case 9: { const auto key = f.projections[0].apply(*f.input[0]);(void)f.table->bucket(f.indices[0], key);break; }
    case 10: (void)f.table->live();break;
    case 11: (void)f.table->journal();break;
    case 12: { crown::storage::AccountedReferenceTable temporary(crown::RelationId{6002}, f.layout);break; }
    default: verify(false, "unknown native table allocation operation");
  }
}

void test_native_table_allocation_failure_sweeps() {
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  const NativeTableInput native;const auto baseline = live_bytes;
  std::size_t total_positions = 0;std::uint64_t insertion_peak = 0;
  for (std::size_t operation = 0; operation < 13; ++operation) {
    std::size_t positions = 0;
    {
      Scope scope;NativeAccountedTableFixture f;f.prepare(native);
      if (operation == 4 || operation == 5) f.journal.emplace(f.table->journal());
      const auto before = observe();perform_native_table_operation(f, operation);const auto after = observe();
      positions = after.successful_calls - before.successful_calls;
      if (operation == 0) {
        insertion_peak = f.account.statistics().peak_requested_bytes;
        verify(insertion_peak == peak_live_bytes - baseline, "native table peak differs from independent upstream events");
      }
    }
    verify(positions > 0 && live_bytes == baseline, "native table allocation sample leaked or has no real positions");
    total_positions += positions;
    for (std::size_t position = 0; position < positions; ++position) {
      NativeAccountedTableFixture f;
      { Scope scope;f.prepare(native);if (operation == 4 || operation == 5) f.journal.emplace(f.table->journal()); }
      const auto before = f.account.statistics();const auto table_before = f.table->memory_statistics();
      const auto* address = f.table->get(f.handles[0]);const auto hash = address->hash();Observation failed;bool rejected = false;
      {
        Scope scope(static_cast<std::ptrdiff_t>(position));
        rejected = throws_bad_alloc([&] { perform_native_table_operation(f, operation); });
        f.table->check_invariants();failed = observe();
      }
      verify_observation(failed);const auto after = f.account.statistics();
      if (!(rejected && failed.triggered && failed.calls == position + 1 && failed.successful_bytes == failed.freed_bytes &&
             failed.successful_calls == failed.freed_calls && before.current == after.current && before.by_purpose == after.by_purpose &&
             before.by_lifetime == after.by_lifetime && f.table->memory_statistics() == table_before &&
             f.table->get(f.handles[0]) == address && address->hash() == hash))
        std::fprintf(stderr, "native table failure operation=%zu position=%zu\n", operation, position);
      verify(rejected && failed.triggered && failed.calls == position + 1 && failed.successful_bytes == failed.freed_bytes &&
             failed.successful_calls == failed.freed_calls && before.current == after.current && before.by_purpose == after.by_purpose &&
             before.by_lifetime == after.by_lifetime && f.table->memory_statistics() == table_before &&
             f.table->get(f.handles[0]) == address && address->hash() == hash,
             "native table failure changed prior rows/handles/indexes/bytes or allocated recovery");
      if (f.journal) verify(f.journal->active() && f.journal->size() == 0, "failed journal operation published an undo entry");
      { Scope scope;perform_native_table_operation(f, operation); }
    }
    verify(live_bytes == baseline, "native table allocation-failure sweep retained query storage");
    std::printf("S05 native table operation=%zu positions=%zu\n", operation, positions);
  }
  for (const bool under : {false, true}) {
    NativeAccountedTableFixture f;
    { Scope scope;f.prepare(native, insertion_peak - (under ? 1U : 0U)); }
    const auto before = f.account.statistics();const auto table_before = f.table->memory_statistics();
    bool rejected = false;Observation observed;
    {
      Scope scope;
      if (under) rejected = rejects_as([&] { (void)f.table->insert(*f.input[2]); }, "memory_limit");
      else verify(f.table->insert(*f.input[2]).inserted, "native exact-cap insert failed");
      observed = observe();
    }
    verify_observation(observed);
    if (under) {
      verify(rejected && observed.calls == observed.successful_calls && observed.successful_bytes == observed.freed_bytes &&
             before.current == f.account.statistics().current && before.by_lifetime == f.account.statistics().by_lifetime &&
             f.table->memory_statistics() == table_before, "native one-byte-under admission did not restore all previous allocations");
      { Scope scope;verify(f.table->insert(*f.input[3]).inserted, "native smaller-row cap retry failed"); }
    }
    f.table->check_invariants();
  }
  verify(live_bytes == baseline, "native exact/under-cap fixtures leaked");
  std::printf("S05 native table operations=13 total_positions=%zu insertion_peak_upstream_bytes=%llu\n", total_positions,
              static_cast<unsigned long long>(insertion_peak));
}

void test_native_table_bounded_model_and_same_account_copy() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;ReferenceTable oracle(RelationId{6001}, native.layout);
  const auto oracle_index = oracle.add_index(Projection(native.layout, native.targets[0], {FieldId{0}}));
  const auto baseline = live_bytes;NativeAccountedTableFixture f;
  { Scope scope;f.prepare(native);f.table->clear(); }
  std::array<std::optional<TupleHandle>, 4> handles{}, oracle_handles{};
  std::uint32_t random = 0x51e0cafeU;
  for (std::size_t step = 0; step < 256; ++step) {
    random = random * 1664525U + 1013904223U;const auto key = static_cast<std::size_t>((random >> 8) % 4);
    const auto operation = random % 4;
    if (operation == 0) oracle_handles[key] = oracle.insert(native.layout.tuple(native.rows[key])).handle;
    if (operation == 1 && oracle_handles[key]) { verify(oracle.erase(*oracle_handles[key]), "native oracle erase failed");oracle_handles[key].reset(); }
    if (operation == 2 && step % 17 == 0) { oracle.clear();for (auto& handle : oracle_handles) handle.reset(); }
    {
      Scope scope;
      if (operation == 0) handles[key] = f.table->insert(*f.input[key]).handle;
      if (operation == 1 && handles[key]) { verify(f.table->erase(*handles[key]), "accounted model erase failed");handles[key].reset(); }
      if (operation == 2 && step % 17 == 0) { f.table->clear();for (auto& handle : handles) handle.reset(); }
      if (operation == 3) {
        auto transaction = f.table->journal();(void)transaction.insert(*f.input[key]);
        for (const auto& handle : handles) if (handle) { (void)transaction.erase(*handle);break; }
        transaction.rollback();
      }
      verify_observation(observe());
    }
    std::size_t expected_size = 0;
    {
      Scope scope(0);
      for (std::size_t i = 0; i < handles.size(); ++i) {
        verify(handles[i].has_value() == oracle_handles[i].has_value(), "native table model membership differs from reference oracle");
        if (handles[i]) {
          ++expected_size;verify(f.table->get(*handles[i])->hash() == oracle.get(*oracle_handles[i])->hash(), "native table model row differs from oracle");
        }
      }
      const auto memory = f.table->memory_statistics();
      verify(f.table->size() == expected_size && memory.memberships == expected_size * 2 && memory.active_undo_entries == 0 &&
             memory.retained_undo_entries == 0 && memory.arena.records.slots <= 5 &&
             memory.owned.requested_bytes == live_bytes - f.before_table_live,
             "native table churn leaked logical history, slots or actual requests");
      f.table->check_invariants();verify(observe().calls == 0, "native table model diagnostics allocated");
    }
    const auto oracle_keys = oracle.keys(oracle_index);
    { Scope scope;const auto actual = f.table->keys(f.indices[0]);verify(actual.size() == oracle_keys.size(), "native key census differs from oracle"); }
  }
  {
    Scope scope;auto copy = f.table->snapshot_copy();
    verify(copy.owner() != f.table->owner() && copy.layout().same_token(f.table->layout()) &&
           copy.layout().account_statistics().owner == f.account.statistics().owner && copy.size() == f.table->size() &&
           copy.revision() == f.table->revision(), "native snapshot copy minted an account or changed token/ID counters");
    copy.check_invariants();
    for (const auto& handle : handles) if (handle) {
      const TupleHandle copied{copy.owner(), copy.relation(), handle->tuple};
      verify(copy.get(copied)->hash() == f.table->get(*handle)->hash(), "native snapshot copy changed a logical tuple ID");
    }
  }
  f.table.reset();f.journal.reset();for (auto& input : f.input) input.reset();
  for (auto& projection : f.projections) projection = AccountedProjection{};
  for (auto& target : f.targets) target = AccountedLayout{};
  f.layout = AccountedLayout{};f.account = MemoryAccount{};
  verify(live_bytes == baseline, "native table model or same-account clone leaked");
  std::puts("S05 native table_model steps=256 maximum_slots_bound=5");
}

void test_native_journal_replacements_and_owner_lifetime() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;const auto baseline = live_bytes;
  {
    NativeAccountedTableFixture f;std::optional<AccountedTupleArena::Pin> original;
    { Scope scope;f.prepare(native);original.emplace(f.table->pin(f.handles[0])); }
    const auto* first = f.table->get(f.handles[0]);const auto* second = f.table->get(f.handles[1]);
    const auto allocation = original->handle();
    {
      Scope scope;auto transaction = f.table->journal();
      verify(transaction.erase(f.handles[0]), "replacement journal original erase failed");
      const auto replacement = transaction.insert(*f.input[0]).handle;
      verify(replacement != f.handles[0] && transaction.erase(replacement), "replacement reused a live identity or could not erase its own insert");
      const auto another = transaction.insert(*f.input[0]).handle;
      verify(another != replacement && transaction.erase(f.handles[1]), "second replacement or adjacent erase failed");
      (void)transaction.insert(*f.input[2]);auto tentative = transaction.live();
      const auto before = observe().calls;transaction.rollback();
      verify(observe().calls == before && f.table->size() == 2 && f.table->get(f.handles[0]) == first &&
             f.table->get(f.handles[1]) == second && original->is_live() && original->handle() == allocation &&
             f.table->get(replacement) == nullptr && f.table->get(another) == nullptr &&
             rejects_as([&] { (void)tentative.next(); }, "invalid_cursor"),
             "multi-operation rollback lost original addresses/generation or retained tentative rows");
      f.table->check_invariants();
      const auto retried = f.table->insert(*f.input[2]);
      verify(retried.handle.tuple.value == f.handles[1].tuple.value + 1, "rollback failed to restore the last committed tuple ID");
    }
    std::optional<AccountedReferenceTable::Journal> first_history, second_history;
    {
      Scope scope;first_history.emplace(f.table->journal());(void)first_history->erase(f.handles[0]);first_history->commit();
      second_history.emplace(f.table->journal());(void)second_history->erase(f.handles[1]);second_history->commit();
      verify(f.table->memory_statistics().retained_undo_entries == 2, "multiple committed histories were not reported together");
    }
    {
      Scope scope(0);first_history.reset();
      verify(f.table->memory_statistics().retained_undo_entries == 1 && original->get().hash() == row_hash(native.rows[0]),
             "releasing one history lost another history or an external pin");
      second_history.reset();verify(f.table->memory_statistics().retained_undo_entries == 0, "released history count remained live");
      f.table->check_invariants();verify(observe().calls == 0, "committed history release allocated");
    }
  }
  verify(live_bytes == baseline, "replacement/multiple-history fixture leaked");
  {
    NativeAccountedTableFixture f;std::optional<AccountedReferenceTable::Journal> transaction;
    std::optional<AccountedReferenceTable::Cursor> cursor;
    {
      Scope scope;f.prepare(native);transaction.emplace(f.table->journal());(void)transaction->erase(f.handles[0]);
      (void)transaction->insert(*f.input[2]);cursor.emplace(transaction->live());
    }
    {
      Scope scope(0);f.table.reset();
      verify(transaction->active() && transaction->change(0).tuple.hash() == row_hash(native.rows[0]) &&
             rejects_as([&] { (void)cursor->next(); }, "invalid_cursor"),
             "active writer failed to retain unpublished state or exposed a destroyed facade through its cursor");
      transaction->rollback();transaction.reset();cursor.reset();
      f.account.check_invariants();verify(observe().calls == 0, "orphaned writer rollback/destruction allocated");
    }
  }
  verify(live_bytes == baseline, "active writer outliving facade leaked native state");
}

void test_containing_allocation_classification() {
  using namespace crown::resource;
  using namespace memory_trace;
  const auto baseline = live_bytes;MemoryAccount account, other;MemoryBlock block;
  { Scope scope;account = MemoryAccount::create(1U << 20);other = MemoryAccount::create(1U << 20);block = account.allocate(32); }
  const auto before = account.statistics();Observation result;
  {
    Scope scope(0);const auto* interior = static_cast<const unsigned char*>(block.data()) + 7;
    account.set_lifetime_containing(interior, MemoryPurpose::scratch, {}, AllocationLifetime::retained);
    verify(block.lifetime() == AllocationLifetime::retained, "portable interior classification did not affect the actual block");
    verify(rejects_as([&] { other.set_lifetime_containing(interior, MemoryPurpose::scratch, {}, AllocationLifetime::active); }, "memory_contract") &&
           rejects_as([&] { account.set_lifetime_containing(interior, MemoryPurpose::primary_node, {}, AllocationLifetime::active); }, "memory_contract") &&
           rejects_as([&] { account.set_lifetime_containing(interior, MemoryPurpose::scratch, {MemoryOwnerKind::storage_table, 99}, AllocationLifetime::active); }, "memory_contract"),
           "portable interior lookup accepted a different owner/account/purpose");
    account.set_lifetime_containing(interior, MemoryPurpose::scratch, {}, AllocationLifetime::active);result = observe();
  }
  verify_observation(result);verify(result.calls == 0 && account.statistics() == before, "portable classification allocated or changed physical byte history");
  block.reset();account = MemoryAccount{};other = MemoryAccount{};verify(live_bytes == baseline, "portable classification fixture leaked");
}

// Cached-offset classification must agree with the ledger search for every
// node of a container, reject foreign owners, and restore exact statistics.
void test_containing_site_classification() {
  using namespace crown::resource;
  using Value = std::pair<const int, std::array<char, 40>>;
  using Map = std::map<int, std::array<char, 40>, std::less<int>, MemoryAllocator<Value>>;
  const MemoryAttribution tag{MemoryOwnerKind::storage_table, 7};
  auto fast = MemoryAccount::create(1U << 22), slow = MemoryAccount::create(1U << 22), other = MemoryAccount::create(1U << 22);
  {
    Map fast_map(std::less<int>{}, MemoryAllocator<Value>(fast, MemoryPurpose::primary_node, tag));
    Map slow_map(std::less<int>{}, MemoryAllocator<Value>(slow, MemoryPurpose::primary_node, tag));
    for (int i = 0; i < 300; ++i) { fast_map.emplace(i, std::array<char, 40>{}); slow_map.emplace(i, std::array<char, 40>{}); }
    static MemoryAccount::ContainingSite site;
    const auto initial = fast.statistics();
    for (const auto life : {AllocationLifetime::retained, AllocationLifetime::active}) {
      for (int i = 0; i < 300; i += 3) {
        fast.set_lifetime_containing(&fast_map.find(i)->second, site, MemoryPurpose::primary_node, tag, life);
        slow.set_lifetime_containing(&slow_map.find(i)->second, MemoryPurpose::primary_node, tag, life);
        verify(site.offset.load() >= 0, "containing site did not calibrate its offset");
        verify(fast.statistics().by_lifetime == slow.statistics().by_lifetime,
            "cached containing classification differs from the ledger search");
      }
      // Extracted nodes keep their layout, so the cached offset still applies.
      auto node = fast_map.extract(1);
      fast.set_lifetime_containing(&node.mapped(), site, MemoryPurpose::primary_node, tag, life);
      fast_map.insert(std::move(node));
      fast.set_lifetime_containing(&fast_map.find(1)->second, site, MemoryPurpose::primary_node, tag, AllocationLifetime::active);
    }
    verify(fast.statistics() == initial, "cached containing classification did not restore statistics");
    const auto* element = &fast_map.find(5)->second;
    verify(rejects_as([&] { other.set_lifetime_containing(element, site, MemoryPurpose::primary_node, tag, AllocationLifetime::retained); }, "memory_contract") &&
           rejects_as([&] { fast.set_lifetime_containing(element, site, MemoryPurpose::scratch, tag, AllocationLifetime::retained); }, "memory_contract") &&
           rejects_as([&] { fast.set_lifetime_containing(element, site, MemoryPurpose::primary_node, {}, AllocationLifetime::retained); }, "memory_contract"),
           "cached containing classification accepted a different account/purpose/owner");
    verify(fast.statistics() == initial, "rejected cached classification changed statistics");
    fast.check_invariants();slow.check_invariants();
  }
  verify(fast.statistics().current.allocations == 1 && slow.statistics().current.allocations == 1, "containing site fixture leaked");
}

constexpr crown::storage::IndexWork indexed_test_work() {
  return {1000000000, 1000000000, 1000000000, 1000000000, 1000000000};
}
constexpr crown::storage::IndexedLimits indexed_test_limits() {
  return {80, 4, 256, 320, 640, 4096, 96, 192, 128};
}
struct AccountedIndexedFixture {
  NativeAccountedTableFixture metadata;
  crown::storage::AccountedIndexWork work;
  std::optional<crown::storage::AccountedIndexedTable> table;
  std::optional<crown::storage::AccountedIndexedTable::Journal> journal;
  std::array<crown::TupleHandle, 2> handles{};
  std::array<crown::IndexId, 2> indices{};
  std::uint64_t before_table_live = 0;
  void prepare(const NativeTableInput& native, std::uint64_t cap = 1U << 24,
               crown::storage::IndexedLimits limits = indexed_test_limits()) {
    using namespace crown::storage;
    metadata.prepare_metadata(native, cap);work = AccountedIndexWork::create(metadata.account, indexed_test_work());
    before_table_live = memory_trace::live_bytes;
    table.emplace(crown::RelationId{6001}, metadata.layout, limits);
#ifdef CROWN_ACCOUNTED_COLLISION_PROFILE
    detail::AccountedIndexedTesting::collisions(*table, CROWN_ACCOUNTED_COLLISION_PROFILE == 1 ?
        detail::AccountedCollisionMode::same_bucket : detail::AccountedCollisionMode::same_full_hash);
#endif
    IndexWorkAllowance grant(indexed_test_work(), true);
    for (std::size_t i = 0; i < indices.size(); ++i) indices[i] = table->add_index(metadata.projections[i], grant);
    for (std::size_t i = 0; i < handles.size(); ++i) handles[i] = table->insert(*metadata.input[i], grant).handle;
  }
};

void test_accounted_indexed_work_and_allocation_identity() {
  using namespace crown::resource;
  using namespace crown::storage;
  using namespace memory_trace;
  const auto baseline = live_bytes;
  MemoryAccount account, other;std::optional<std::vector<int, MemoryAllocator<int>>> values;
  AccountedIndexWork work, copy, foreign;
  {
    Scope scope;account = MemoryAccount::create(1U << 20);other = MemoryAccount::create(1U << 20);
    values.emplace(MemoryAllocator<int>(account, MemoryPurpose::primary_node));values->reserve(7);
    work = AccountedIndexWork::create(account, IndexWork{3, 4, 5, 6, 7});copy = work;
    foreign = AccountedIndexWork::create(other, indexed_test_work());
  }
  const auto before = account.statistics();Observation observation;
  {
    Scope scope(0);
    auto allocator = values->get_allocator();const auto usage = allocator.allocation_usage(values->data(), values->capacity());
    allocator.set_allocation_lifetime(values->data(), values->capacity(), AllocationLifetime::retained);
    verify(account.statistics().by_lifetime[static_cast<std::size_t>(AllocationLifetime::retained)] == usage,
           "direct allocator classification did not report its real allocation");
    verify(rejects_as([&] { allocator.set_allocation_lifetime(values->data(), values->capacity()+1, AllocationLifetime::active); }, "memory_contract") &&
           rejects_as([&] { MemoryAllocator<int>(other, MemoryPurpose::primary_node).set_allocation_lifetime(values->data(), values->capacity(), AllocationLifetime::active); }, "memory_contract"),
           "direct header classification accepted wrong count or account");
    allocator.set_allocation_lifetime(values->data(), values->capacity(), AllocationLifetime::active);
    verify(copy.get() == work.get() && copy.same_account(account) && !copy.same_account(other) && !foreign.same_account(account),
           "owning index work copy changed grant identity or admitted a different query");
    work.get()->admit(IndexWork{1, 2, 3, 4, 5});
    const auto remaining = copy.get()->remaining();
    verify(remaining == IndexWork{2, 2, 2, 2, 2} && rejects_as([&] { copy.get()->admit(IndexWork{1, 3, 1, 1, 1}); }, "storage_work_limit") &&
           copy.get()->remaining() == remaining, "work alias minted allowance or partial multi-domain denial consumed earlier fields");
    observation = observe();
  }
  verify_observation(observation);verify(observation.calls == 0 && account.statistics() == before, "direct classification/work diagnostics allocated or changed byte history");
  values.reset();work = {};copy = {};foreign = {};account = {};other = {};
  verify(live_bytes == baseline, "owning work/direct header fixture leaked");
}

void test_accounted_indexed_journals_and_retention() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;const auto baseline = live_bytes;
  std::optional<AccountedIndexedTable::Journal> history;
  std::optional<AccountedIndexedTable::Cursor> cursor;
  std::optional<AccountedTupleArena::Pin> pin;
  std::optional<AccountedVector<AccountedTuple>> snapshot;
  MemoryAccount observer;
  {
    AccountedIndexedFixture f;
    {
      Scope scope;f.prepare(native);observer = f.metadata.account;IndexWorkAllowance grant(indexed_test_work(), true);
      const auto memory = f.table->memory_statistics();
      verify(memory.records.rows == 2 && memory.records.memberships == 4 && memory.records.live_keys == 2 &&
             memory.owned.requested_bytes == live_bytes - f.before_table_live && memory.directories.allocations == 5,
             "indexed owned records/directories differ from independent requests");
      const auto* first = f.table->get(f.handles[0], grant);pin.emplace(f.table->pin(f.handles[0], grant));const auto generation = pin->handle();
      auto transaction = f.table->journal(f.work);
      verify(transaction.erase(f.handles[0]), "indexed journal erase failed");
      const auto replacement = transaction.insert(*f.metadata.input[0]).handle;
      verify(replacement != f.handles[0] && transaction.erase(replacement), "indexed replacement journal lost identity");
      (void)transaction.insert(*f.metadata.input[0]);(void)transaction.erase(f.handles[1]);
      auto tentative = transaction.live();auto key_cursor = transaction.index_keys(f.indices[0]);
      f.table->check_invariants();
      IndexWorkAllowance wrong(indexed_test_work(), true);const auto wrong_before = wrong.remaining();
      verify(rejects_as([&] { (void)tentative.next(wrong); }, "storage_contract") && wrong.remaining() == wrong_before,
             "journal cursor accepted a different work object");
      const auto calls_before = observe().calls;transaction.rollback();
      verify(observe().calls == calls_before && f.table->get(f.handles[0], grant) == first && pin->is_live() && pin->handle() == generation &&
             rejects_as([&] { (void)tentative.next(*f.work); }, "invalid_cursor") &&
             rejects_as([&] { (void)key_cursor.next(*f.work); }, "invalid_cursor"),
             "indexed rollback allocated, changed old identity/address or preserved tentative cursors");
      f.table->check_invariants();
      auto committed = f.table->journal(f.work);(void)committed.erase(f.handles[0]);committed.commit();
      verify(!committed.active() && committed.size() == 1 && !pin->is_live() && f.table->memory_statistics().retained_history_entries == 1 &&
             f.table->statistics().retained_rows == 0, "committed index history retained structural authority or lost byte ownership");
      history.emplace(std::move(committed));snapshot.emplace(f.table->snapshot(grant));cursor.emplace(f.table->live(grant));
      verify(snapshot->size() == 1 && snapshot->front().hash() == row_hash(native.rows[1]) &&
             snapshot->get_allocator().attribution().kind == MemoryOwnerKind::output, "indexed snapshot lost accounted deep output");
      const auto raw = observe();verify_observation(raw);
      verify(f.metadata.account.statistics().current.requested_bytes == raw.successful_bytes - raw.freed_bytes,
             "indexed deep data/control/history escaped its shared query account");
    }
    f.table.reset();
    {
      Scope scope(0);IndexWorkAllowance grant(indexed_test_work(), true);
      verify(rejects_as([&] { (void)cursor->next(grant); }, "invalid_cursor") && history->change(0).tuple.hash() == row_hash(native.rows[0]),
             "indexed cursor outlived facade or retained history lost values");
    }
  }
  verify(observer.statistics().current.requested_bytes == live_bytes - baseline, "orphaned indexed controls/history/output are unaccounted");
  { Scope scope(0);history.reset();cursor.reset();pin.reset();snapshot.reset();observer.check_invariants();verify(observe().calls == 0, "indexed final release allocated"); }
  observer = {};verify(live_bytes == baseline, "indexed lifecycle fixture leaked");
  {
    AccountedIndexedFixture f;std::optional<AccountedIndexedTable::Journal> writer;std::optional<AccountedIndexedTable::Cursor> tentative;
    { Scope scope;f.prepare(native);writer.emplace(f.table->journal(f.work));(void)writer->erase(f.handles[0]);(void)writer->insert(*f.metadata.input[2]);tentative.emplace(writer->live()); }
    { Scope scope(0);f.table.reset();verify(rejects_as([&] { (void)tentative->next(*f.work); }, "invalid_cursor"), "orphaned writer exposed destroyed facade");writer->rollback();writer.reset();tentative.reset();f.metadata.account.check_invariants();verify(observe().calls == 0, "orphaned indexed rollback allocated"); }
  }
  verify(live_bytes == baseline, "orphaned indexed writer leaked");
}

void prepare_indexed_operation(AccountedIndexedFixture& f, std::size_t operation) {
  if (operation == 4 || operation == 5 || (operation >= 15 && operation <= 17) || operation == 19 || operation == 20) {
    f.journal.emplace(f.table->journal(f.work));
    if (operation == 19 || operation == 20) (void)f.journal->insert(*f.metadata.input[2]);
  }
}
void perform_indexed_operation(AccountedIndexedFixture& f, std::size_t operation, crown::storage::IndexWorkAllowance& work) {
  using namespace crown::storage;
  switch (operation) {
    case 0: (void)f.table->insert(*f.metadata.input[2], work);break;
    case 1: (void)f.table->add_index(f.metadata.projections[2], work);break;
    case 2: (void)f.table->erase(f.handles[0], work);break;
    case 3: { const auto key = f.metadata.projections[0].apply(*f.metadata.input[0]);(void)f.table->erase_key(f.indices[0], key, work);break; }
    case 4: (void)f.journal->insert(*f.metadata.input[2]);break;
    case 5: (void)f.journal->erase(f.handles[0]);break;
    case 6: (void)f.table->snapshot(work);break;
    case 7: (void)f.table->snapshot_copy(work);break;
    case 8: (void)f.table->keys(f.indices[0], work);break;
    case 9: { const auto key = f.metadata.projections[0].apply(*f.metadata.input[0]);(void)f.table->bucket(f.indices[0], key, work);break; }
    case 10: (void)f.table->live(work);break;
    case 11: (void)f.table->journal(f.work);break;
    case 12: { AccountedIndexedTable temporary(crown::RelationId{6002}, f.metadata.layout, indexed_test_limits());break; }
    case 13: { const auto key = f.metadata.projections[0].apply(*f.metadata.input[0]);(void)f.table->bucket_cursor(f.indices[0], key, work);break; }
    case 14: (void)f.table->index_keys(f.indices[0], work);break;
    case 15: (void)f.journal->live();break;
    case 16: { const auto key = f.metadata.projections[0].apply(*f.metadata.input[0]);(void)f.journal->bucket_cursor(f.indices[0], key);break; }
    case 17: (void)f.journal->index_keys(f.indices[0]);break;
    case 18: (void)AccountedIndexWork::create(f.metadata.account, indexed_test_work());break;
    case 19: (void)f.journal->insert(*f.metadata.input[3]);break;
    case 20: (void)f.journal->erase(f.handles[0]);break;
    case 21: (void)f.table->drop_index(f.indices[0], work);break;
    case 22: f.table->clear(work);break;
    default: verify(false, "unknown accounted indexed operation");
  }
}

void test_accounted_indexed_persistent_failures_and_peak() {
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;const auto baseline = live_bytes;std::size_t total = 0;std::uint64_t peak = 0;
  for (std::size_t operation = 0; operation < 23; ++operation) {
    std::size_t positions = 0;
    {
      Scope scope;AccountedIndexedFixture f;f.prepare(native);prepare_indexed_operation(f, operation);IndexWorkAllowance work(indexed_test_work(), true);
      const auto before = observe();perform_indexed_operation(f, operation, work);const auto after = observe();positions = after.successful_calls - before.successful_calls;
      if (operation == 0) { peak = f.metadata.account.statistics().peak_requested_bytes;verify(peak == peak_live_bytes - baseline, "indexed real peak differs from independent requests"); }
    }
    verify(live_bytes == baseline, "indexed allocation sample leaked");total += positions;
    for (std::size_t position = 0; position < positions; ++position) {
      AccountedIndexedFixture f;
      { Scope scope;f.prepare(native);prepare_indexed_operation(f, operation); }
      IndexWorkAllowance probe(indexed_test_work(), true);const auto* address = f.table->get(f.handles[0], probe);const auto hash = address->hash();
      const auto before = f.metadata.account.statistics();const auto memory = f.table->memory_statistics();const auto entries = f.journal ? f.journal->size() : 0;
      Observation failed;bool rejected = false;
      {
        Scope scope(static_cast<std::ptrdiff_t>(position));IndexWorkAllowance work(indexed_test_work(), true);
        rejected = throws_bad_alloc([&] { perform_indexed_operation(f, operation, work); });f.table->check_invariants();failed = observe();
      }
      const auto after = f.metadata.account.statistics();verify_observation(failed);
      const bool restored = rejected && failed.triggered && failed.calls == position + 1 && failed.successful_bytes == failed.freed_bytes &&
          failed.successful_calls == failed.freed_calls && before.current == after.current && before.by_purpose == after.by_purpose &&
          before.by_lifetime == after.by_lifetime && f.table->memory_statistics() == memory && f.table->get(f.handles[0], probe) == address &&
          address->hash() == hash && (!f.journal || (f.journal->active() && f.journal->size() == entries));
      if (!restored) std::fprintf(stderr, "indexed allocation failure operation=%zu position=%zu\n", operation, position);
      verify(restored, "indexed failure changed prior bytes/rows/indexes or allocated recovery");
      { Scope scope;IndexWorkAllowance work(indexed_test_work(), true);perform_indexed_operation(f, operation, work); }
    }
    verify(live_bytes == baseline, "indexed persistent failure sweep leaked");
    std::printf("S05 accounted indexed operation=%zu positions=%zu\n", operation, positions);
  }
  for (const bool under : {false, true}) {
    AccountedIndexedFixture f;{ Scope scope;f.prepare(native, peak - (under ? 1U : 0U)); }
    const auto before = f.metadata.account.statistics();const auto memory = f.table->memory_statistics();Observation observed;bool rejected = false;
    {
      Scope scope;IndexWorkAllowance work(indexed_test_work(), true);
      if (under) rejected = rejects_as([&] { (void)f.table->insert(*f.metadata.input[2], work); }, "memory_limit");
      else verify(f.table->insert(*f.metadata.input[2], work).inserted, "indexed exact byte cap rejected the sample");
      observed = observe();
    }
    verify_observation(observed);
    if (under) {
      verify(rejected && observed.calls == observed.successful_calls && observed.successful_bytes == observed.freed_bytes &&
             before.current == f.metadata.account.statistics().current && f.table->memory_statistics() == memory,
             "indexed one-byte-under admission lost old state or allocated diagnostics");
      { Scope scope;IndexWorkAllowance work(indexed_test_work(), true);verify(f.table->insert(*f.metadata.input[3], work).inserted, "indexed smaller cap retry failed"); }
    }
  }
  verify(live_bytes == baseline, "indexed exact/under-cap fixture leaked");
  std::printf("S05 accounted indexed operations=23 total_positions=%zu insertion_peak_upstream_bytes=%llu\n", total, static_cast<unsigned long long>(peak));
}

void test_accounted_indexed_work_and_component_limits() {
  using namespace crown;
  using namespace crown::storage;
  using namespace memory_trace;
  NativeTableInput native;const auto baseline = live_bytes;std::size_t boundaries = 0;
  constexpr std::array<std::size_t, 11> operations{0, 1, 2, 3, 6, 7, 10, 13, 14, 21, 22};
  const std::array<std::uint64_t IndexWork::*, 5> domains{&IndexWork::structural_steps, &IndexWork::scalar_fields,
      &IndexWork::scalar_bytes, &IndexWork::pointer_slots, &IndexWork::link_actions};
  for (const auto operation : operations) {
    IndexWork cost;
    {
      Scope scope;AccountedIndexedFixture f;f.prepare(native);const auto limit = indexed_test_work();IndexWorkAllowance grant(limit, true);
      perform_indexed_operation(f, operation, grant);
      for (const auto domain : domains) cost.*domain = limit.*domain - grant.remaining().*domain;
    }
    for (std::size_t domain = 0; domain < domains.size(); ++domain) if (cost.*domains[domain] != 0) {
      for (const bool under : {false, true}) {
        AccountedIndexedFixture f;{ Scope scope;f.prepare(native); }
        IndexWork limit = cost;if (under) --(limit.*domains[domain]);IndexWorkAllowance grant(limit, true);
        const auto memory = f.table->memory_statistics();bool rejected = false;Observation observed;
        {
          Scope scope;
          if (under) rejected = rejects_as([&] { perform_indexed_operation(f, operation, grant); }, "storage_work_limit");
          else perform_indexed_operation(f, operation, grant);
          f.table->check_invariants();observed = observe();
        }
        verify_observation(observed);
        if (under) verify(rejected && observed.calls == observed.successful_calls && observed.successful_bytes == observed.freed_bytes &&
                          f.table->memory_statistics() == memory, "one-unit-under work denial changed owned state or allocated diagnostics");
      }
      ++boundaries;
    }
  }
  const std::array<std::size_t IndexedLimits::*, 9> components{&IndexedLimits::rows, &IndexedLimits::indices, &IndexedLimits::keys,
      &IndexedLimits::memberships, &IndexedLimits::nodes, &IndexedLimits::directory_slots, &IndexedLimits::arena_slots,
      &IndexedLimits::arena_pins, &IndexedLimits::journal_entries};
  constexpr std::array<std::size_t, 9> exact{2,2,2,4,10,40,2,0,0};
  for (std::size_t component = 0; component < components.size(); ++component) {
    auto limits = indexed_test_limits();limits.*components[component] = exact[component];AccountedIndexedFixture f;
    { Scope scope;f.prepare(native, 1U << 24, limits); }
    const auto before = f.table->memory_statistics();bool rejected = false;
    {
      Scope scope;IndexWorkAllowance grant(indexed_test_work(), true);
      rejected = rejects_as([&] {
        if (component == 1 || component == 5) (void)f.table->add_index(f.metadata.projections[2], grant);
        else if (component == 7) (void)f.table->pin(f.handles[0], grant);
        else if (component == 8) { auto journal = f.table->journal(f.work);(void)journal.insert(*f.metadata.input[2]); }
        else (void)f.table->insert(*f.metadata.input[2], grant);
      }, "storage_capacity");
      verify_observation(observe());
    }
    verify(rejected && f.table->memory_statistics() == before, "finite indexed component denial changed previous state or byte partition");
    { Scope scope(0);IndexWorkAllowance grant(indexed_test_work(), true);verify(f.table->find(*f.metadata.input[0], grant) == f.handles[0], "capacity failure lost old lookup");f.table->check_invariants();verify(observe().calls == 0, "capacity-failure read/recovery allocated"); }
  }
  {
    AccountedIndexedFixture f;resource::MemoryAccount other;AccountedIndexWork foreign;
    { Scope scope;f.prepare(native);other = resource::MemoryAccount::create(1U << 20);foreign = AccountedIndexWork::create(other, indexed_test_work()); }
    const auto before = f.table->memory_statistics();
    {
      Scope scope(0);IndexWorkAllowance legacy(indexed_test_work());
      verify(rejects_as([&] { (void)f.table->insert(*f.metadata.input[2], legacy); }, "storage_contract") &&
             rejects_as([&] { (void)f.table->journal(foreign); }, "storage_contract") && f.table->memory_statistics() == before &&
             legacy.remaining() == indexed_test_work() && observe().calls == 0, "indexed table accepted an allocating diagnostic mode or foreign owning grant");
    }
  }
#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
  for (const auto counter : {detail::AccountedIndexedTesting::Exhausted::tuple_id, detail::AccountedIndexedTesting::Exhausted::index_id,
       detail::AccountedIndexedTesting::Exhausted::revision}) {
    AccountedIndexedFixture f;{ Scope scope;f.prepare(native); }
    detail::AccountedIndexedTesting::exhaust(*f.table, counter);const auto before = f.table->memory_statistics();
    {
      Scope scope(0);IndexWorkAllowance grant(indexed_test_work(), true);
      const bool rejected = rejects_as([&] {
        if (counter == detail::AccountedIndexedTesting::Exhausted::index_id) (void)f.table->add_index(f.metadata.projections[2], grant);
        else (void)f.table->insert(*f.metadata.input[2], grant);
      }, "storage_overflow");
      verify(rejected && f.table->memory_statistics() == before && observe().calls == 0, "exhausted ID/revision wrapped or allocated diagnostics");
      f.table->check_invariants();
    }
  }
#endif
  verify(live_bytes == baseline, "indexed work/component/overflow fixtures leaked");
  std::printf("S05 accounted indexed work_boundaries=%zu component_boundaries=9\n", boundaries);
}

void test_accounted_indexed_churn_and_sparse_cursors() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;ReferenceTable oracle(RelationId{6001}, native.layout);
  const auto oracle_index = oracle.add_index(Projection(native.layout, native.targets[0], {FieldId{0}}));
  const auto baseline = live_bytes;
  {
    AccountedIndexedFixture f;{ Scope scope;f.prepare(native);IndexWorkAllowance grant(indexed_test_work(), true);f.table->clear(grant); }
    std::array<std::optional<TupleHandle>, 4> handles{}, reference{};std::uint32_t random = 0x521a0ffeU;
    for (std::size_t step = 0; step < 256; ++step) {
      random = random * 1664525U + 1013904223U;const auto key = static_cast<std::size_t>((random >> 8) % 4);const auto op = random % 4;
      if (op == 0) reference[key] = oracle.insert(native.layout.tuple(native.rows[key])).handle;
      if (op == 1 && reference[key]) { (void)oracle.erase(*reference[key]);reference[key].reset(); }
      if (op == 2 && step % 17 == 0) { oracle.clear();for (auto& h : reference) h.reset(); }
      {
        Scope scope;IndexWorkAllowance grant(indexed_test_work(), true);
        if (op == 0) handles[key] = f.table->insert(*f.metadata.input[key], grant).handle;
        if (op == 1 && handles[key]) { verify(f.table->erase(*handles[key], grant), "indexed model erase failed");handles[key].reset(); }
        if (op == 2 && step % 17 == 0) { f.table->clear(grant);for (auto& h : handles) h.reset(); }
        if (op == 3) { auto journal = f.table->journal(f.work);(void)journal.insert(*f.metadata.input[key]);for (const auto& h : handles) if (h) { (void)journal.erase(*h);break; }journal.rollback(); }
        verify_observation(observe());
      }
      const auto reference_keys = oracle.keys(oracle_index);
      {
        Scope scope;IndexWorkAllowance grant(indexed_test_work(), true);const auto actual_keys = f.table->keys(f.indices[0], grant);
        verify(actual_keys.size() == reference_keys.size(), "indexed model key census differs from reference");
      }
      {
        Scope scope(0);IndexWorkAllowance grant(indexed_test_work(), true);std::size_t count = 0;
        for (std::size_t i = 0; i < handles.size(); ++i) {
          verify(handles[i].has_value() == reference[i].has_value(), "indexed model membership differs from reference");
          if (handles[i]) { ++count;verify(f.table->get(*handles[i], grant)->hash() == oracle.get(*reference[i])->hash(), "indexed model row differs from reference"); }
        }
        const auto memory = f.table->memory_statistics();
        verify(memory.records.rows == count && memory.records.memberships == count * 2 && memory.records.journal_entries == 0 &&
               memory.retained_history_entries == 0 && memory.arena.records.slots <= 5 && memory.owned.requested_bytes == live_bytes - f.before_table_live,
               "indexed churn leaked logical history, rows or accounted bytes");
        f.table->check_invariants();verify(observe().calls == 0, "indexed model diagnostic allocated");
      }
    }
  }
  verify(live_bytes == baseline, "indexed differential model leaked");
  std::array<Row, 64> rows;
  for (std::size_t i = 0; i < rows.size(); ++i) rows[i] = Row{static_cast<std::int64_t>(1000+i), std::string(4096, 's'), true};
  std::array<std::uint64_t, 2> startup{};
  for (std::size_t population = 0; population < 2; ++population) {
    AccountedIndexedFixture f;{ Scope scope;f.prepare(native);IndexWorkAllowance grant(indexed_test_work(), true);f.table->clear(grant); }
    const auto total = population ? rows.size() : std::size_t{8};std::array<TupleHandle, 64> handles{};
    for (std::size_t i = 0; i < total; ++i) {
      Scope scope;IndexWorkAllowance grant(indexed_test_work(), true);const auto tuple = f.metadata.layout.tuple(rows[i]);handles[i] = f.table->insert(tuple, grant).handle;verify_observation(observe());
    }
    for (std::size_t i = 0; i < total - 8; ++i) { Scope scope(0);IndexWorkAllowance grant(indexed_test_work(), true);verify(f.table->erase(handles[i], grant), "indexed sparse erase failed");verify(observe().calls == 0, "cached optimized erase allocated"); }
    {
      Scope scope;IndexWorkAllowance grant(indexed_test_work(), true);const auto before = grant.remaining();auto cursor = f.table->live(grant);
      startup[population] = before.pointer_slots - grant.remaining().pointer_slots;
      const auto calls_before = observe().calls;IndexWorkAllowance denied(IndexWork{}, true);
      verify(rejects_as([&] { (void)cursor.next(denied); }, "storage_work_limit"), "zero-work cursor step advanced");
      std::size_t count = 0;const auto steps_before = grant.remaining().structural_steps;
      while (const auto row = cursor.next(grant)) {
        verify(row->tuple.hash() == row_hash(rows[total-8+count]), "sparse cursor changed live order or advanced during denial");++count;
      }
      verify(count == 8 && steps_before - grant.remaining().structural_steps == 9 && observe().calls == calls_before,
             "indexed cursor scanned historical slots, performed lookup or allocated during next");
      f.table->check_invariants();
    }
  }
  verify(startup[0] == startup[1], "indexed cursor startup grew with reserved capacity");
  verify(live_bytes == baseline, "indexed sparse fixture leaked");
  std::printf("S05 accounted indexed model_steps=256 sparse_live=8 sparse_populations=8,64 startup_pointer_words=%llu\n", static_cast<unsigned long long>(startup[0]));
}

struct AccountedDispatchFixture {
  NativeAccountedTableFixture metadata;
  crown::storage::AccountedIndexWork work;
  std::optional<crown::storage::AccountedStorageTable> table;
  std::optional<crown::storage::AccountedStorageTable::Journal> journal;
  std::array<crown::TupleHandle, 2> handles{};
  std::array<crown::IndexId, 2> indices{};
  std::uint64_t before_table_live = 0;
  void prepare(const NativeTableInput& native, crown::storage::StorageBackend backend) {
    using namespace crown::storage;
    metadata.prepare_metadata(native);work = AccountedIndexWork::create(metadata.account, indexed_test_work());
    before_table_live = memory_trace::live_bytes;
    if (backend == StorageBackend::indexed_chained_v1) table.emplace(crown::RelationId{6001}, metadata.layout, indexed_test_limits());
    else table.emplace(crown::RelationId{6001}, metadata.layout);
#ifdef CROWN_ACCOUNTED_COLLISION_PROFILE
    if (backend == StorageBackend::indexed_chained_v1)
      detail::AccountedStorageTableTesting::collisions(*table, CROWN_ACCOUNTED_COLLISION_PROFILE == 1 ?
          detail::AccountedCollisionMode::same_bucket : detail::AccountedCollisionMode::same_full_hash);
#endif
    IndexWorkAllowance grant(indexed_test_work(), true);
    for (std::size_t i = 0; i < indices.size(); ++i) indices[i] = table->add_index(metadata.projections[i], &grant);
    for (std::size_t i = 0; i < handles.size(); ++i) handles[i] = table->insert(*metadata.input[i], &grant).handle;
  }
};

template<class T> concept TemporaryTableBorrow = requires(const T&& table, crown::TupleHandle handle) {
  std::move(table).get(handle);
};
template<class T> concept TemporaryTableBorrowWithWork = requires(const T&& table, crown::TupleHandle handle,
    crown::storage::IndexWorkAllowance* work) { std::move(table).get(handle, work); };
static_assert(!TemporaryTableBorrow<crown::storage::AccountedStorageTable> &&
              !TemporaryTableBorrowWithWork<crown::storage::AccountedStorageTable>);

void test_accounted_native_dispatch_and_composed_journals() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;const auto baseline = live_bytes;
  for (const auto backend : {StorageBackend::reference_ordered_v1, StorageBackend::indexed_chained_v1}) {
    {
      AccountedDispatchFixture f;{ Scope scope;f.prepare(native, backend);verify_observation(observe()); }
      auto& table = *f.table;IndexWorkAllowance grant(indexed_test_work(), true);
      const auto* first = table.get(f.handles[0], &grant);
      {
        Scope scope(0);const auto report = table.memory_statistics();
        verify(table.backend() == backend && table.relation() == RelationId{6001} && table.size() == 2 &&
               table.layout().same_token(f.metadata.layout) && table.find(*f.metadata.input[0], &grant) == f.handles[0] &&
               table.projection(f.indices[0], &grant).same_token(f.metadata.projections[0]) &&
               table.key_count(f.indices[0], &grant) == 1 && table.arena_statistics().live_records == 2 &&
               table.indexed_limits().has_value() == (backend == StorageBackend::indexed_chained_v1) &&
               table.indexed_statistics().has_value() == (backend == StorageBackend::indexed_chained_v1),
               "accounted dispatch changed backend, identities or metadata");
        std::visit([&](const auto& memory) { verify(memory.owned.requested_bytes == live_bytes - f.before_table_live,
            "accounted dispatch report lost actual backend ownership"); }, report);
        auto pin = table.pin(f.handles[0], &grant);
        verify(&pin.get() == first && pin.get().hash() == row_hash(native.rows[0]), "dispatch pin or borrowed value copied payload");
        table.check_invariants();verify(observe().calls == 0, "dispatch probes/report/pin/diagnostic allocated");
      }
      {
        Scope scope;const auto indices = table.indices(&grant);const auto keys = table.keys(f.indices[0], &grant);
        const auto key = f.metadata.projections[0].apply(*f.metadata.input[0]);
        const auto handles = table.bucket(f.indices[0], key, &grant);const auto snapshot = table.snapshot(&grant);
        verify(indices.size() == 2 && keys.size() == 1 && handles.size() == 2 && snapshot.size() == 2,
               "accounted dispatch collections changed logical contents");
        verify(indices.get_allocator().attribution().kind == MemoryOwnerKind::output &&
               snapshot.get_allocator().attribution().kind == MemoryOwnerKind::output,
               "accounted dispatch output collection lost accounted export owner");
        auto cursor = table.live(&grant);auto bucket = table.bucket_cursor(f.indices[0], key, &grant);
        auto key_cursor = table.index_keys(f.indices[0], &grant);const auto before = observe().calls;
        const auto entry = cursor.next_entry(&grant);const auto bucket_entry = bucket.next_entry(&grant);
        const auto indexed_key = key_cursor.next(&grant);
        const auto live_first = backend == StorageBackend::reference_ordered_v1 ? f.handles[1] : f.handles[0];
        const auto live_second = backend == StorageBackend::reference_ordered_v1 ? f.handles[0] : f.handles[1];
        verify(entry && bucket_entry && indexed_key && entry->handle == live_first &&
               &entry->tuple == table.get(live_first, &grant) && &bucket_entry->tuple == first &&
               indexed_key->degree == 2 && cursor.next(&grant) == live_second && !cursor.next(&grant) &&
               bucket.next(&grant) == f.handles[1] && !bucket.next(&grant) && !key_cursor.next(&grant) &&
               observe().calls == before, "dispatch cursor copied payload, reordered rows or allocated during next");
        auto copy = table.snapshot_copy(&grant);
        verify(copy.backend() == backend && copy.owner() != table.owner() && copy.revision() == table.revision() &&
               copy.layout().same_token(table.layout()) && copy.size() == 2, "dispatch copy changed backend/accounted metadata");
        const TupleHandle copied{copy.owner(), copy.relation(), f.handles[0].tuple};
        verify(copy.get(copied, &grant)->hash() == first->hash(), "dispatch copy lost stable logical IDs");
        const auto third_index = copy.add_index(f.metadata.projections[2], &grant);
        verify(copy.drop_index(third_index, &grant) && copy.erase(*f.metadata.input[0], &grant) &&
               copy.erase_key(f.indices[0], key, &grant) == 1 && copy.size() == 0,
               "dispatch index/drop/erase paths used the wrong backend");
        (void)copy.insert(*f.metadata.input[3], &grant);copy.clear(&grant);verify(copy.size() == 0, "dispatch clear left rows");
        verify_observation(observe());
      }
      MemoryAccount foreign;AccountedIndexWork foreign_work;
      { Scope scope;foreign = MemoryAccount::create(1U << 20);foreign_work = AccountedIndexWork::create(foreign, indexed_test_work()); }
      {
        Scope scope(0);verify(rejects_as([&] { (void)table.journal(foreign_work); }, "storage_contract"),
            "dispatch journal retained a foreign query work control");
        if (backend == StorageBackend::indexed_chained_v1) {
          verify(rejects_as([&] { (void)table.find(*f.metadata.input[0]); }, "storage_contract") &&
                 rejects_as([&] { (void)table.journal(); }, "storage_contract"), "dispatch invented an indexed work allowance");
        }
        verify(observe().calls == 0, "dispatch contract denial allocated");
      }
      std::optional<AccountedStorageTable::Cursor> stale;
      {
        Scope scope;auto journal = table.journal(f.work);verify(journal.erase(f.handles[0]), "dispatch writer erase failed");
        (void)journal.insert(*f.metadata.input[2]);stale.emplace(journal.live());
        verify(journal.size() == 2 && !journal.change(0).inserted && journal.change(0).tuple.hash() == first->hash(),
               "dispatch change view lost retained deleted value");
        if (backend == StorageBackend::indexed_chained_v1)
          verify(rejects_as([&] { (void)stale->next(&grant); }, "storage_contract"), "dispatch journal cursor accepted replacement work");
        const auto before = observe().calls;journal.rollback();
        verify(observe().calls == before && table.get(f.handles[0], &grant) == first && table.size() == 2 &&
               rejects_as([&] { (void)stale->next(); }, "invalid_cursor"), "dispatch rollback failed stable restoration/cursor invalidation");
      }
      std::optional<AccountedStorageTable::Journal> history;std::optional<AccountedTupleArena::Pin> pin;
      {
        Scope scope;history.emplace(table.journal(f.work));pin.emplace(table.pin(f.handles[0], &grant));
        verify(history->erase(f.handles[0]), "dispatch committed erase failed");history->commit();
        verify(!history->active() && history->change(0).tuple.hash() == first->hash() && !pin->is_live(),
               "dispatch commit failed to preserve retained value");
      }
      {
        Scope scope(0);f.table.reset();
        verify(history->change(0).tuple.hash() == row_hash(native.rows[0]) && pin->get().hash() == row_hash(native.rows[0]),
               "dispatch facade destruction dropped retained history/pin");
        history.reset();pin.reset();stale.reset();verify(observe().calls == 0, "dispatch retained teardown allocated");
      }
    }
    verify(live_bytes == baseline, "accounted dispatch backend fixture leaked");
  }
  {
    AccountedDispatchFixture f;std::optional<AccountedStorageTable> second;
    std::optional<AccountedStorageTable::Journal> first_writer, second_writer;
    {
      Scope scope;f.prepare(native, StorageBackend::indexed_chained_v1);
      second.emplace(RelationId{6002}, f.metadata.layout, indexed_test_limits());
      IndexWorkAllowance grant(indexed_test_work(), true);(void)second->insert(*f.metadata.input[0], &grant);
      first_writer.emplace(f.table->journal(f.work));second_writer.emplace(second->journal(f.work));
      verify(first_writer->erase(f.handles[0]), "composed dispatch first mutation failed");
    }
    f.work.get()->admit(f.work.get()->remaining());
    {
      Scope scope(0);verify(rejects_as([&] { (void)second_writer->insert(*f.metadata.input[2]); }, "storage_work_limit"),
          "second dispatched journal minted another grant");
      second_writer->rollback();first_writer->rollback();
      verify(f.work.get()->remaining() == IndexWork{} && f.table->size() == 2 && second->size() == 1,
             "composed dispatch rollback refilled work or changed committed state");
      f.table->check_invariants();second->check_invariants();verify(observe().calls == 0, "composed denial/rollback allocated");
    }
  }
  verify(live_bytes == baseline, "composed dispatch fixture leaked");
  std::puts("S05 accounted dispatch backends=2 composed_grant=shared borrowed_payloads=stable");
}

void test_accounted_native_dispatch_allocation_failures() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativeTableInput native;const auto baseline = live_bytes;std::size_t total_positions = 0;
  constexpr std::size_t operations = 7;
  const auto invoke = [&](AccountedDispatchFixture& f, std::size_t operation, StorageBackend backend) {
    IndexWorkAllowance grant(indexed_test_work(), true);
    switch (operation) {
      case 0:
        if (backend == StorageBackend::indexed_chained_v1) { AccountedStorageTable second(RelationId{6002}, f.metadata.layout, indexed_test_limits()); }
        else { AccountedStorageTable second(RelationId{6002}, f.metadata.layout); }
        break;
      case 1: (void)f.table->add_index(f.metadata.projections[2], &grant);break;
      case 2: (void)f.table->insert(*f.metadata.input[2], &grant);break;
      case 3: f.journal.emplace(f.table->journal(f.work));break;
      case 4: (void)f.journal->insert(*f.metadata.input[2]);break;
      case 5: { const auto copy = f.table->snapshot_copy(&grant);verify(copy.size() == 2, "dispatch copy sample lost rows");break; }
      case 6: { const auto output = f.table->snapshot(&grant);verify(output.size() == 2, "dispatch snapshot sample lost rows");break; }
      default: std::abort();
    }
  };
  for (const auto backend : {StorageBackend::reference_ordered_v1, StorageBackend::indexed_chained_v1}) {
    for (std::size_t operation = 0; operation < operations; ++operation) {
      std::size_t positions = 0;
      {
        AccountedDispatchFixture f;{ Scope scope;f.prepare(native, backend);if (operation == 4) f.journal.emplace(f.table->journal(f.work)); }
        { Scope scope;invoke(f, operation, backend);positions = observe().calls;verify_observation(observe()); }
      }
      verify(positions > 0 && positions < attempt_capacity && live_bytes == baseline, "dispatch allocation sample missing or leaked");
      total_positions += positions;
      for (std::size_t failed_at = 0; failed_at < positions; ++failed_at) {
        AccountedDispatchFixture f;{ Scope scope;f.prepare(native, backend); }
        IndexWorkAllowance grant(indexed_test_work(), true);
        const auto* first = f.table->get(f.handles[0], &grant);const auto* second = f.table->get(f.handles[1], &grant);
        if (operation == 4) { Scope scope;f.journal.emplace(f.table->journal(f.work)); }
        const auto current = f.metadata.account.statistics();const auto report = f.table->memory_statistics();
        bool denied = false;
        {
          Scope scope(static_cast<std::ptrdiff_t>(failed_at));
          try { invoke(f, operation, backend); } catch (const std::bad_alloc&) { denied = true; }
          const auto observation = observe();verify(denied && observation.triggered, "dispatch did not persistently fail an observed position");
          verify_observation(observation);
        }
        {
          Scope scope(0);const auto after = f.metadata.account.statistics();
          verify(after.current == current.current && after.by_purpose == current.by_purpose && after.by_lifetime == current.by_lifetime &&
                 f.table->memory_statistics() == report &&
                 (f.journal || (f.table->get(f.handles[0], &grant) == first && f.table->get(f.handles[1], &grant) == second)) &&
                 f.table->size() == 2 && (!f.journal || f.journal->size() == 0),
                 "dispatch allocation failure changed previous state or retained temporary bytes");
          f.table->check_invariants();verify(observe().calls == 0, "dispatch failure validation allocated");
        }
        { Scope scope;invoke(f, operation, backend);verify_observation(observe()); }
      }
      verify(live_bytes == baseline, "dispatch failure sweep retained a native owner");
    }
  }
  std::printf("S05 accounted dispatch operations_per_backend=%zu backends=2 total_positions=%zu\n", operations, total_positions);
}

struct NativePlanStorageInput {
  using TupleLayout = crown::storage::TupleLayout;
  inline static constexpr std::array<crown::FieldId, 1> first{{{0}}}, second{{{1}}};
  std::string identity = std::string(64, 'a');
  TupleLayout source{crown::LayoutId{0}, {{crown::ScalarType::int64}, {crown::ScalarType::string},
      {crown::ScalarType::boolean}}, {77, identity}};
  TupleLayout key = crown::storage::projected_layout(crown::LayoutId{1}, source, first);
  TupleLayout unused = crown::storage::projected_layout(crown::LayoutId{2}, source, second);
  crown::storage::Projection shared{source, key, {crown::FieldId{0}}};
  std::array<TupleLayout, 3> layouts{source, key, unused};
  std::array<crown::PhysicalRelation, 3> relations{{
    {crown::RelationId{0}, crown::RelationRole::native_records, source, crown::NodeId{0}, {}},
    {crown::RelationId{1}, crown::RelationRole::survivors, source, crown::NodeId{0}, {}},
    {crown::RelationId{2}, crown::RelationRole::parent_support, source, crown::NodeId{0}, {}}}};
  std::array<crown::IndexRequirement, 3> indexes{{
    {crown::IndexRequirementId{0}, crown::RelationId{0}, shared, {}},
    {crown::IndexRequirementId{1}, crown::RelationId{1}, shared, {}},
    {crown::IndexRequirementId{2}, crown::RelationId{2}, crown::storage::Projection(source, key, {crown::FieldId{0}}), {}}}};
  std::array<crown::Row, 3> rows{
    crown::Row{std::int64_t{1}, std::string(4096, 'p'), true},
    crown::Row{std::int64_t{1}, std::string(4096, 'p'), false},
    crown::Row{std::int64_t{3}, std::string("small"), true}};
  [[nodiscard]] std::optional<crown::storage::IndexedBackendSpec> specification(crown::storage::StorageBackend backend) const {
    if (backend == crown::storage::StorageBackend::reference_ordered_v1) return {};
    return crown::storage::IndexedBackendSpec{indexed_test_limits(), indexed_test_work()};
  }
  [[nodiscard]] crown::storage::AccountedPlanStorage create(const crown::resource::MemoryAccount& account,
      crown::storage::StorageBackend backend, crown::storage::IndexWorkAllowance* work) const {
    return crown::storage::detail::AccountedPlanStorageTesting::create(account, crown::PhysicalRoute::tree,
        identity, layouts, relations, indexes, specification(backend), work);
  }
};
struct AccountedPlanFixture {
  crown::resource::MemoryAccount account;
  std::optional<crown::storage::AccountedPlanStorage> plan;
  std::array<std::optional<crown::storage::AccountedTuple>, 3> input;
  std::array<std::array<crown::TupleHandle, 2>, 3> handles{};
  void prepare(const NativePlanStorageInput& native, crown::storage::StorageBackend backend,
      std::uint64_t cap = 1U << 24) {
    using namespace crown::storage;
    account = crown::resource::MemoryAccount::create(cap);IndexWorkAllowance work(indexed_test_work(), true);
    plan.emplace(native.create(account, backend, &work));
    for (std::size_t i = 0; i < input.size(); ++i) input[i].emplace(plan->layout(crown::LayoutId{0}).tuple(native.rows[i]));
    for (std::size_t r = 0; r < handles.size(); ++r)
      for (std::size_t i = 0; i < handles[r].size(); ++i) handles[r][i] = plan->table(crown::RelationId{r}).insert(*input[i], &work).handle;
  }
};
template<class T> concept TemporaryPlanBorrow = requires(const T&& plan) { std::move(plan).table(crown::RelationId{0}); };
static_assert(!TemporaryPlanBorrow<crown::storage::AccountedPlanStorage>);

void test_accounted_compiled_plan_binding_and_lifetimes() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  const auto baseline = live_bytes;std::size_t boundaries = 0;
  for (const auto backend : {StorageBackend::reference_ordered_v1, StorageBackend::indexed_chained_v1}) {
    {
      std::optional<NativePlanStorageInput> source;source.emplace();
      const auto first_hash = row_hash(source->rows[0]);AccountedPlanFixture f;
      { Scope scope;f.prepare(*source, backend);verify_observation(observe()); }
      source.reset();IndexWorkAllowance grant(indexed_test_work(), true);
      const auto metadata_owner = f.plan->memory_statistics().shared_metadata.attribution;
      {
        Scope scope(0);const auto report = f.plan->memory_statistics();
        verify(f.plan->backend() == backend && f.plan->route() == PhysicalRoute::tree &&
               f.plan->physical_identity() == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" &&
               report.layouts == 3 && report.relations == 3 && report.index_bindings == 3 &&
               f.plan->projection(IndexRequirementId{0}).same_token(f.plan->projection(IndexRequirementId{1})) &&
               !f.plan->projection(IndexRequirementId{0}).same_token(f.plan->projection(IndexRequirementId{2})),
               "plan binding retained source metadata or collapsed distinct projection tokens");
        auto bytes = report.owned.requested_bytes;
        for (const auto& input : f.input) bytes += input->memory_usage().requested_bytes;
        for (std::size_t r = 0; r < f.handles.size(); ++r) {
          const auto& table = f.plan->table(RelationId{r});
          verify(table.layout().same_token(f.plan->layout(LayoutId{0})) && table.get(f.handles[r][0], &grant)->hash() == first_hash &&
                 table.projection(f.plan->index(IndexRequirementId{r}), &grant).same_token(f.plan->projection(IndexRequirementId{r})),
                 "plan binding lost source aliases/native row or index identities");
          std::visit([&](const auto& memory) { bytes += memory.owned.requested_bytes; }, table.memory_statistics());
        }
        verify(bytes + MemoryAccount::control_bytes() == f.account.statistics().current.requested_bytes &&
               f.account.statistics().current.requested_bytes == live_bytes - baseline,
               "plan metadata/instance/table/arena/input records did not reconcile with actual requests");
        f.plan->check_invariants(&grant);verify(observe().calls == 0, "plan binding diagnostics allocated");
      }
      std::optional<AccountedPlanStorage> copy;std::optional<AccountedTupleArena::Pin> pin;
      {
        Scope scope;pin.emplace(f.plan->table(RelationId{0}).pin(f.handles[0][0], &grant));
        verify(f.plan->table(RelationId{0}).erase(f.handles[0][1], &grant), "plan sparse copy setup failed");
        copy.emplace(f.plan->snapshot_copy(&grant));
        verify(copy->owner() != f.plan->owner() && copy->layout(LayoutId{0}).same_token(f.plan->layout(LayoutId{0})) &&
               copy->memory_statistics().shared_metadata.attribution == metadata_owner &&
               copy->memory_statistics().instance.attribution != f.plan->memory_statistics().instance.attribution,
               "plan copy duplicated metadata, changed tokens or reused instance authority");
        for (std::size_t r = 0; r < f.handles.size(); ++r) {
          const auto& table = copy->table(RelationId{r});const TupleHandle handle{table.owner(), table.relation(), f.handles[r][0].tuple};
          verify(table.get(handle, &grant)->hash() == first_hash && table.owner() != f.plan->table(RelationId{r}).owner(),
                 "plan copy renumbered sparse rows or lost fresh native owners");
        }
        copy->check_invariants(&grant);verify_observation(observe());
      }
      {
        Scope scope(0);f.plan.reset();copy->check_invariants(&grant);
        copy.reset();for (auto& input : f.input) input.reset();
        verify(pin->get().hash() == first_hash && f.account.statistics_for(metadata_owner).current.requested_bytes > 0,
               "last native pin lost charged frozen layout metadata");
        pin.reset();verify(f.account.statistics_for(metadata_owner).current == MemoryUsage{} &&
            f.account.statistics().current.requested_bytes == MemoryAccount::control_bytes() && observe().calls == 0,
            "plan/control/frozen metadata release allocated or retained ownership");
      }
    }
    verify(live_bytes == baseline, "plan source/copy/pin lifetime fixture leaked");
    {
      NativePlanStorageInput native;AccountedPlanFixture left, right;
      { Scope scope;left.prepare(native, backend);right.prepare(native, backend); }
      const auto owner = left.plan->owner();
      {
        Scope scope(0);for (auto& input : right.input) input.reset();
        *right.plan = std::move(*left.plan);
        verify(right.plan->owner() == owner && right.plan->layout(LayoutId{0}).account_statistics().owner == left.account.statistics().owner &&
               right.account.statistics().current.requested_bytes == MemoryAccount::control_bytes() &&
               rejects_as([&] { (void)left.plan->owner(); }, "invalid_storage") && observe().calls == 0,
               "cross-account plan move allocated, kept old ownership or exposed moved state");
      }
    }
    verify(live_bytes == baseline, "cross-account plan move leaked");
  }
  {
    NativePlanStorageInput native;MemoryAccount account;
    { Scope scope;account = MemoryAccount::create(1U << 24); }
    IndexWork used;
    { Scope scope;IndexWorkAllowance work(indexed_test_work(), true);const auto plan = native.create(account, StorageBackend::indexed_chained_v1, &work);
      const auto left = work.remaining();const auto cap = indexed_test_work();
      used = {cap.structural_steps-left.structural_steps, cap.scalar_fields-left.scalar_fields, cap.scalar_bytes-left.scalar_bytes,
          cap.pointer_slots-left.pointer_slots, cap.link_actions-left.link_actions}; }
    const std::array<std::uint64_t IndexWork::*, 5> domains{&IndexWork::structural_steps, &IndexWork::scalar_fields,
        &IndexWork::scalar_bytes, &IndexWork::pointer_slots, &IndexWork::link_actions};
    for (const auto field : domains) if (used.*field) {
      auto cap = indexed_test_work();cap.*field = used.*field;
      { Scope scope;IndexWorkAllowance work(cap, true);const auto plan = native.create(account, StorageBackend::indexed_chained_v1, &work); }
      --(cap.*field);const auto before = account.statistics();
      { Scope scope;IndexWorkAllowance work(cap, true);verify(rejects_as([&] { (void)native.create(account, StorageBackend::indexed_chained_v1, &work); }, "storage_work_limit"), "plan one-under work limit admitted"); }
      verify(account.statistics().current == before.current, "plan work denial retained temporary metadata");++boundaries;
    }
    {
      Scope scope(0);IndexWorkAllowance zero(IndexWork{}, true), legacy(indexed_test_work());auto too_large = indexed_test_work();++too_large.structural_steps;
      IndexWorkAllowance oversized(too_large, true);
      verify(rejects_as([&] { (void)native.create(account, StorageBackend::indexed_chained_v1, &zero); }, "storage_work_limit") &&
             rejects_as([&] { (void)native.create(account, StorageBackend::indexed_chained_v1, &legacy); }, "storage_contract") &&
             rejects_as([&] { (void)native.create(account, StorageBackend::indexed_chained_v1, &oversized); }, "storage_contract") &&
             rejects_as([&] { (void)native.create(account, StorageBackend::indexed_chained_v1, nullptr); }, "storage_contract") && observe().calls == 0,
             "plan storage minted a grant or allocating diagnostic");
    }
  }
  verify(live_bytes == baseline, "plan metadata/work boundary fixtures leaked");
  std::printf("S05 accounted plan backends=2 source_released=1 aliases=preserved work_boundaries=%zu\n", boundaries);
}

void test_accounted_compiled_plan_allocation_failures_and_peak() {
  using namespace crown;
  using namespace crown::storage;
  using namespace crown::resource;
  using namespace memory_trace;
  NativePlanStorageInput native;const auto baseline = live_bytes;std::size_t total_positions = 0;
  const auto invoke = [&](AccountedPlanFixture& f, StorageBackend backend, std::size_t operation) {
    IndexWorkAllowance work(indexed_test_work(), true);
    if (operation == 0) { const auto second = native.create(f.account, backend, &work); }
    else { const auto copy = f.plan->snapshot_copy(&work); }
  };
  for (const auto backend : {StorageBackend::reference_ordered_v1, StorageBackend::indexed_chained_v1}) {
    for (std::size_t operation = 0; operation < 2; ++operation) {
      std::size_t positions = 0;
      { AccountedPlanFixture f;{ Scope scope;f.prepare(native, backend); }
        { Scope scope;invoke(f, backend, operation);positions = observe().calls;verify_observation(observe()); } }
      verify(positions > 0 && positions < attempt_capacity && live_bytes == baseline, "plan allocation sample missing or leaked");total_positions += positions;
      for (std::size_t failed_at = 0; failed_at < positions; ++failed_at) {
        AccountedPlanFixture f;{ Scope scope;f.prepare(native, backend); }
        const auto before = f.account.statistics();const auto report = f.plan->memory_statistics();
        IndexWorkAllowance work(indexed_test_work(), true);
        const auto* first = f.plan->table(RelationId{0}).get(f.handles[0][0], &work);bool denied = false;
        { Scope scope(static_cast<std::ptrdiff_t>(failed_at));try { invoke(f, backend, operation); } catch (const std::bad_alloc&) { denied = true; }
          verify(denied && observe().triggered, "plan missed persistent failure at observed request");verify_observation(observe()); }
        { Scope scope(0);const auto after = f.account.statistics();
          verify(after.current == before.current && after.by_purpose == before.by_purpose && after.by_lifetime == before.by_lifetime &&
                 f.plan->memory_statistics() == report && f.plan->table(RelationId{0}).get(f.handles[0][0], &work) == first,
                 "failed plan constructor/copy changed existing ownership/rows");
          f.plan->check_invariants(&work);verify(observe().calls == 0, "plan failure invariant allocated"); }
        { Scope scope;invoke(f, backend, operation);verify_observation(observe()); }
      }
      verify(live_bytes == baseline, "plan failure sweep leaked");
      std::printf("S05 accounted plan backend=%s operation=%zu positions=%zu\n", backend == StorageBackend::indexed_chained_v1 ? "indexed" : "reference", operation, positions);
    }
    std::uint64_t peak = 0;
    { AccountedPlanFixture f;Scope scope;f.prepare(native, backend);peak = peak_live_bytes - baseline;
      verify(f.account.statistics().peak_requested_bytes == peak, "plan fixture peak differs from actual simultaneous requests"); }
    { AccountedPlanFixture f;Scope scope;f.prepare(native, backend, peak);verify_observation(observe()); }
    {
      AccountedPlanFixture f;bool denied = false;
      { Scope scope;try { f.prepare(native, backend, peak-1); } catch (const std::bad_alloc&) { denied = true; } }
      verify(denied && f.plan && f.input[2], "plan one-under fixture was admitted or failed before retry preparation");
      { Scope scope;IndexWorkAllowance work(indexed_test_work(), true);
        verify(f.plan->table(RelationId{2}).insert(*f.input[2], &work).inserted, "smaller plan-table retry failed");f.plan->check_invariants(&work); }
    }
    verify(live_bytes == baseline, "plan exact/one-under fixture leaked");
    std::printf("S05 accounted plan backend=%s fixture_peak_requested_bytes=%llu\n", backend == StorageBackend::indexed_chained_v1 ? "indexed" : "reference", static_cast<unsigned long long>(peak));
  }
  std::printf("S05 accounted plan operations_per_backend=2 backends=2 total_positions=%zu\n", total_positions);
}

void test_empty_handle_and_unique_current_bytes() {
  MemoryAccount empty;
  const bool contract = rejects_as([&] { (void)empty.statistics(); }, "memory_contract");
  verify(contract, "empty handle statistics were not rejected as a contract error");
}
} // namespace

int main() {
  test_measurement_and_limits();
  test_alignment_zero_and_invalid_requests();
  test_moves_and_orphaned_block();
  test_upstream_failures();
  test_fixed_current_churn();
  test_allocator_rebind_and_equality();
  test_vector_map_allocator_accounting();
  test_vector_copy_budget_and_unequal_move();
  test_open_nested_string_coverage_gap_witness();
  test_admission_failures_without_upstream_attempts();
  test_inline_decimal_without_allocating_temporaries();
  test_accounted_row_payload_limits_and_lifetime();
  test_accounted_row_order_matches_public_rows();
  test_accounted_unique_and_shared_lifetimes();
  test_accounted_factory_construction_failures();
  test_operator_attribution_without_separate_grants();
  test_accounted_layout_identity_validation_and_retention();
  test_accounted_layout_full_allocation_failure_sweep();
  test_accounted_projection_values_tokens_and_retention();
  test_accounted_projection_rejected_mapping_contracts();
  test_accounted_projection_full_allocation_failure_sweep();
  test_exact_allocation_usage_views();
  test_accounted_arena_retention_generations_and_reports();
  test_accounted_arena_allocation_failures_and_limits();
  test_accounted_arena_bounded_churn_model();
  test_containing_allocation_classification();
  test_containing_site_classification();
  test_native_table_ownership_journals_and_cursors();
  test_native_table_allocation_failure_sweeps();
  test_native_table_bounded_model_and_same_account_copy();
  test_native_journal_replacements_and_owner_lifetime();
  test_accounted_indexed_work_and_allocation_identity();
  test_accounted_indexed_journals_and_retention();
  test_accounted_indexed_persistent_failures_and_peak();
  test_accounted_indexed_work_and_component_limits();
  test_accounted_indexed_churn_and_sparse_cursors();
  test_accounted_native_dispatch_and_composed_journals();
  test_accounted_native_dispatch_allocation_failures();
  test_accounted_compiled_plan_binding_and_lifetimes();
  test_accounted_compiled_plan_allocation_failures_and_peak();
  test_empty_handle_and_unique_current_bytes();
  std::puts("S05 prototype component checks passed; whole-query acceptance is recorded separately");
}
