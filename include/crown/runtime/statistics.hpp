#pragma once
#include "crown/storage/reference.hpp"
#include "crown/storage/table.hpp"
#include "crown/storage/accounted_row.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "crown/resource/ownership.hpp"

namespace crown::storage { class AccountedStorageTable; class RowView; }
namespace crown::runtime::statistics {
namespace detail { struct Exhausted {}; }
// Storage-only scope: revision is an invalidation stamp, NOT a committed epoch.
struct Stamp { StorageOwnerId owner; RelationId relation; std::uint64_t revision; };
enum class Completion { exact, budget_exhausted };
struct Limits {
  std::uint64_t work=1000000, rows=65536, distinct_keys=65536;
  std::uint64_t accounted_bytes=8*1024*1024;
  std::size_t projection_width=256, heavy_keys=16;
};
struct Usage {
  std::uint64_t work=0, rows=0, distinct_keys=0, accounted_bytes=0;
  std::size_t max_row_capacity=0, max_histogram_capacity=0, max_heavy_capacity=0;
};
// One caller-owned budget composes sequential captures. Failed components consume
// work already performed. No allocation or clocks in budget accounting.
class Budget {
 public:
  explicit Budget(Limits limits={}):limits_(limits) {}
  const Limits& limits() const { return limits_; }
  const Usage& usage() const { return usage_; }
  void work(std::uint64_t n=1);
  void row();
  void key();
  void bytes(std::uint64_t n);
  void observe_capacities(std::size_t row,std::size_t histogram,std::size_t heavy) noexcept;
 private:
  Limits limits_; Usage usage_;
};
struct HeavyKey { Row key; std::uint64_t count; };
struct Distribution {
  Completion completion=Completion::budget_exhausted;
  std::uint64_t visited=0;
  std::optional<std::uint64_t> ndv;
  // Exact multiplicity -> number of keys. Empty when incomplete.
  std::vector<std::pair<std::uint64_t,std::uint64_t>> histogram;
  std::optional<std::vector<HeavyKey>> heavy_keys;
};
// Query-owned captures use compact native keys and original-account arrays.
// The ordinary Distribution above remains the explicit standalone table export.
namespace detail {
inline constexpr resource::MemoryAttribution owner_capture_memory{resource::MemoryOwnerKind::capture,2};
template<class T> resource::OwnerAllocator<T> capture_allocator(const resource::MemoryAccount& account) {
  return resource::OwnerAllocator<T>(account,resource::MemoryPurpose::capture,owner_capture_memory);
}
}
template<class T> using CaptureVector=std::vector<T,resource::OwnerAllocator<T>>;
class CapturedKey {
 public:
  CapturedKey(const resource::MemoryAccount&,storage::AccountedRow);
  CapturedKey(const CapturedKey&);
  CapturedKey(CapturedKey&&) noexcept=default;
  CapturedKey& operator=(const CapturedKey& other) {
    if(this!=&other){CapturedKey next(other);*this=std::move(next);}return *this;
  }
  CapturedKey& operator=(CapturedKey&&) noexcept=default;
  storage::RowView view() const & noexcept { return row_.view(); }
  storage::RowView view() const &&=delete;
  std::size_t size() const noexcept { return row_.size(); }
  bool empty() const noexcept { return row_.empty(); }
  const storage::ScalarView& operator[](std::size_t i) const noexcept { return row_.view()[i]; }
  bool operator==(const CapturedKey& other) const noexcept { return view()==other.view(); }
  bool operator==(const Row& other) const { return view()==other; }
  resource::MemoryUsage memory_usage() const noexcept { return row_.memory_usage(); }
 private:
  resource::MemoryAccount account_;
  storage::AccountedRow row_;
};
struct CapturedHeavyKey { CapturedKey key; std::uint64_t count; };
struct CapturedDistribution {
  // This owning value copies funded vectors/keys and may allocate on that account.
  // Unknown completion keeps NDV/top-K absent; visited is only scan progress.
  Completion completion=Completion::budget_exhausted;
  std::uint64_t visited=0;
  std::optional<std::uint64_t> ndv;
  CaptureVector<std::pair<std::uint64_t,std::uint64_t>> histogram;
  std::optional<CaptureVector<CapturedHeavyKey>> heavy_keys;
  CapturedDistribution()=default; // Empty incomplete facts require no allocation.
  explicit CapturedDistribution(const resource::MemoryAccount& account)
      :histogram(detail::capture_allocator<std::pair<std::uint64_t,std::uint64_t>>(account)) {}
};
namespace detail {
// Internal ordered-field scan. The owning owner report keeps the source layout
// and its exact ordered FieldIds; this scan constructs no new schema metadata.
Distribution projected_fields(const storage::ReferenceTable&,std::span<const FieldId>,Budget&);
Distribution projected_fields(const storage::StorageTable&,std::span<const FieldId>,Budget&,storage::IndexWorkAllowance*);
Distribution projected_fields(const storage::AccountedStorageTable&,std::span<const FieldId>,Budget&,storage::IndexWorkAllowance*);
CapturedDistribution native_projected_fields(const storage::AccountedStorageTable&,std::span<const FieldId>,
    Budget&,storage::IndexWorkAllowance*,const resource::MemoryAccount&);
CapturedDistribution native_index(const storage::AccountedStorageTable&,IndexId,const storage::Projection&,
    Budget&,storage::IndexWorkAllowance*,const resource::MemoryAccount&);
class WeightedBuilder {
 public:
  WeightedBuilder(Budget&,const resource::MemoryAccount&);
  ~WeightedBuilder();
  WeightedBuilder(const WeightedBuilder&)=delete;
  WeightedBuilder& operator=(const WeightedBuilder&)=delete;
  bool add(storage::RowView,std::uint64_t);
  void stop() noexcept;
  CapturedDistribution finish();
 private:
  struct Data; resource::AccountedUnique<Data> data_;
};
}
struct Capture {
  // Layout/projection handles share metadata; Distribution owns ordinary exports.
  // Copying the distribution may allocate without rescanning the native table.
  Stamp stamp;
  storage::TupleLayout source_layout;
  std::optional<storage::Projection> projection;
  std::optional<IndexId> index;
  std::size_t cardinality;
  Distribution distribution;
};
// Explicit synchronous reads of quiescent tables; active journal is rejected.
// The immutable projection is already compiled; no hidden index registration.
Capture projection(const storage::ReferenceTable&, const storage::Projection&, Budget&);
Capture index(const storage::ReferenceTable&, IndexId, Budget&);
Capture projection(const storage::StorageTable&,const storage::Projection&,Budget&,storage::IndexWorkAllowance*);
Capture index(const storage::StorageTable&,IndexId,Budget&,storage::IndexWorkAllowance*);
// Native DTO compatibility requires full descriptors and ordered fields to
// match the actual index; recreated tokens are accepted. Incomplete scans
// retain actual metadata and expose no prefix as an exact distribution.
Capture index(const storage::AccountedStorageTable&,IndexId,const storage::Projection&,Budget&,storage::IndexWorkAllowance*);
}
