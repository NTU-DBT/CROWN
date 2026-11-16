#pragma once

// Per-query allocation account used by the native runtime. Owners route every
// nested allocation through the same account; allocator propagation is explicit.
// Usage, ownership and costs: docs/code_specs/primitives.md#memory-account.
#include <array>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <new>
#include <span>
#include <string_view>

namespace crown::resource {

enum class MemoryFault : std::uint8_t { limit, overflow, contract };
// The resource path carries a fixed diagnostic and never constructs owning
// strings. C++ exception-runtime storage is outside operator-new accounting.
// An external presentation boundary can format this after the epoch unwinds.
class MemoryFailure final : public std::bad_alloc {
 public:
  explicit MemoryFailure(MemoryFault fault) noexcept : fault_(fault) {}
  [[nodiscard]] MemoryFault fault() const noexcept { return fault_; }
  [[nodiscard]] std::string_view code() const noexcept {
    switch (fault_) {
      case MemoryFault::limit: return "memory_limit";
      case MemoryFault::overflow: return "memory_overflow";
      case MemoryFault::contract: return "memory_contract";
    }
    return "memory_contract";
  }
  [[nodiscard]] const char* what() const noexcept override {
    switch (fault_) {
      case MemoryFault::limit: return "memory account allocation limit exhausted";
      case MemoryFault::overflow: return "memory account size or history overflow";
      case MemoryFault::contract: return "memory account contract violation";
    }
    return "memory account contract violation";
  }
 private:
  MemoryFault fault_;
};

enum class MemoryPurpose : std::uint8_t {
  control, table_state, arena_slot, tuple_values, scalar_payload, primary_node,
  secondary_node, directory, support_metadata, source_counts, delta_state,
  journal_undo, cursor, observation, capture, immutable_metadata, output_buffer,
  recovery_log, scratch, count
};
enum class AllocationLifetime : std::uint8_t { active, retained, free_pool, count };
inline constexpr auto memory_purpose_count = static_cast<std::size_t>(MemoryPurpose::count);
inline constexpr auto allocation_lifetime_count = static_cast<std::size_t>(AllocationLifetime::count);

// IDs are scoped to this query account and supplied by the owning compiled
// operator/component. Attribution is immutable for an allocation. It neither
// creates a separate limit nor changes when a block becomes undo/retained.
enum class MemoryOwnerKind : std::uint8_t {
  query, physical_source, support_node, delta_node, storage_table, session,
  cursor, immutable_metadata, observation, capture, output, recovery, tuple_arena, count
};
struct MemoryAttribution {
  MemoryOwnerKind kind = MemoryOwnerKind::query;
  std::uint64_t id = 0;
  [[nodiscard]] constexpr bool valid() const noexcept {
    return static_cast<std::size_t>(kind) < static_cast<std::size_t>(MemoryOwnerKind::count) &&
        (kind != MemoryOwnerKind::query || id == 0);
  }
  auto operator<=>(const MemoryAttribution&) const = default;
};

// Requested upstream bytes include this component's own headers, alignment
// allowance and controller. Payload bytes are the caller's requested size.
// These are not allocator usable-size, resident bytes, or logical tuple bytes.
struct MemoryUsage {
  std::uint64_t allocations = 0;
  std::uint64_t requested_bytes = 0;
  std::uint64_t payload_bytes = 0;
  auto operator<=>(const MemoryUsage&) const = default;
};
struct MemoryStatistics {
  std::uint64_t owner = 0;
  std::uint64_t limit_bytes = 0;
  MemoryUsage current;
  std::uint64_t peak_requested_bytes = 0;
  std::uint64_t successful_allocations = 0;
  std::uint64_t freed_allocations = 0;
  std::array<MemoryUsage, memory_purpose_count> by_purpose{};
  std::array<MemoryUsage, allocation_lifetime_count> by_lifetime{};
  auto operator<=>(const MemoryStatistics&) const = default;
};
struct AttributedMemoryStatistics {
  std::uint64_t account_owner = 0;
  MemoryAttribution attribution;
  MemoryUsage current;
  std::array<MemoryUsage, memory_purpose_count> by_purpose{};
  std::array<MemoryUsage, allocation_lifetime_count> by_lifetime{};
  auto operator<=>(const AttributedMemoryStatistics&) const = default;
};

class MemoryBlock;
template<class T> class MemoryAllocator;
// One mutating thread per account; shared handles, blocks and observations
// require external synchronization. An upstream allocator must not reenter
// this account to release/reclassify its blocks. Nested allocation is rejected
// before it can overcommit an in-flight admission; copies/observations are safe.
class MemoryAccount {
  struct Control;
  struct BlockData;
 public:
  MemoryAccount() noexcept = default;
  [[nodiscard]] static MemoryAccount create(std::uint64_t limit_bytes);
  [[nodiscard]] static std::uint64_t control_bytes() noexcept;
  [[nodiscard]] static std::uint64_t allocation_bytes(std::size_t payload_bytes, std::size_t alignment);
  MemoryAccount(const MemoryAccount&) noexcept;
  MemoryAccount& operator=(const MemoryAccount&) noexcept;
  MemoryAccount(MemoryAccount&&) noexcept;
  MemoryAccount& operator=(MemoryAccount&&) noexcept;
  ~MemoryAccount();
  [[nodiscard]] explicit operator bool() const noexcept { return control_ != nullptr; }
  [[nodiscard]] MemoryStatistics statistics() const;
  // Explicit diagnostic O(outstanding allocations), with no allocation or
  // per-owner registry/history growth. Includes controller bytes for query:0.
  // Native bindings supply operator IDs; standalone callers supply their own.
  // Attribution partitions this account, without creating another byte allowance.
  [[nodiscard]] AttributedMemoryStatistics statistics_for(MemoryAttribution) const;
  // Copies one owner key per current allocation, including the controller.
  // The caller supplies capacity >= statistics().current.allocations. This
  // explicit diagnostic allocates nothing and exports no allocation addresses.
  [[nodiscard]] std::size_t copy_attributions(std::span<MemoryAttribution>) const;
  // Portable standard-container bridge: the address is a live value inside
  // the allocation (for example a map node's key). Searches the outstanding
  // ledger in O(allocations), without dereferencing the supplied address or
  // allocating. Slow reference-storage undo uses this explicit cost; indexed
  // storage can classify its directly owned MemoryBlocks in O(1).
  void set_lifetime_containing(const void*, MemoryPurpose, MemoryAttribution,
      AllocationLifetime) const;
  [[nodiscard]] MemoryBlock allocate(std::size_t bytes,
      std::size_t alignment = alignof(std::max_align_t), MemoryPurpose = MemoryPurpose::scratch,
      MemoryAttribution = {}) const;
  // Explicit whole-account diagnostic. Success allocates nothing; it is not
  // an operational scan and must not implement an owner mutation/cursor.
  void check_invariants() const;
 private:
  friend class MemoryBlock;
  template<class T> friend class MemoryAllocator;
  explicit MemoryAccount(Control*) noexcept;
  [[nodiscard]] void* allocate_raw(std::size_t, std::size_t, MemoryPurpose, MemoryAttribution) const;
  [[nodiscard]] MemoryUsage allocation_usage_raw(const void*, std::size_t, std::size_t,
      MemoryPurpose, MemoryAttribution) const;
  void set_lifetime_raw(void*, std::size_t, std::size_t, MemoryPurpose,
      MemoryAttribution, AllocationLifetime) const;
  void deallocate_raw(void*, std::size_t, std::size_t, MemoryPurpose, MemoryAttribution) const noexcept;
  [[nodiscard]] Control& required() const;
  static void retain(Control*) noexcept;
  static void release(Control*) noexcept;
  static void free(BlockData*) noexcept;
  Control* control_ = nullptr;
};

class MemoryBlock {
 public:
  MemoryBlock() noexcept = default;
  MemoryBlock(const MemoryBlock&) = delete;
  MemoryBlock& operator=(const MemoryBlock&) = delete;
  MemoryBlock(MemoryBlock&&) noexcept;
  MemoryBlock& operator=(MemoryBlock&&) noexcept;
  ~MemoryBlock();
  [[nodiscard]] explicit operator bool() const noexcept { return data_ != nullptr; }
  [[nodiscard]] void* data() noexcept;
  [[nodiscard]] const void* data() const noexcept;
  [[nodiscard]] std::size_t size() const noexcept;
  // Exact stored request, not a recomputed capacity estimate. Empty/moved
  // blocks report zero; a real zero-payload allocation still reports one block.
  [[nodiscard]] MemoryUsage usage() const noexcept;
  [[nodiscard]] MemoryPurpose purpose() const;
  [[nodiscard]] MemoryAttribution attribution() const;
  [[nodiscard]] AllocationLifetime lifetime() const;
  [[nodiscard]] MemoryStatistics account_statistics() const;
  // Classification changes never free bytes or refill the account. They
  // describe allocation lifetime, not the number of live elements in a buffer.
  void set_lifetime(AllocationLifetime) const;
  void reset() noexcept;
 private:
  friend class MemoryAccount;
  explicit MemoryBlock(MemoryAccount::BlockData*) noexcept;
  [[nodiscard]] MemoryAccount::BlockData& required() const;
  MemoryAccount::BlockData* data_ = nullptr;
};

}  // namespace crown::resource
