#pragma once
#include "crown/storage/reference.hpp"

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
namespace detail {
// Internal ordered-field scan. The owning owner report keeps the source layout
// and its exact ordered FieldIds; this scan constructs no new schema metadata.
Distribution projected_fields(const storage::ReferenceTable&,std::span<const FieldId>,Budget&);
class WeightedBuilder {
 public:
  explicit WeightedBuilder(Budget&);
  ~WeightedBuilder();
  WeightedBuilder(const WeightedBuilder&)=delete;
  WeightedBuilder& operator=(const WeightedBuilder&)=delete;
  bool add(const Row&,std::uint64_t);
  void stop() noexcept;
  Distribution finish();
 private:
  struct Data; std::unique_ptr<Data> data_;
};
}
struct Capture {
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
}
