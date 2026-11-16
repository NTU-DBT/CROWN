#pragma once

#include "crown/planner/selection.hpp"
#include "ranking_detail.hpp"
#include <limits>

namespace crown::planner::selection::detail {
namespace rd = ::crown::planner::ranking::detail;
// Attribute selection result, cache and scratch allocations to the selection capture owner.
// See docs/query_memory.md.
inline constexpr resource::MemoryAttribution selection_memory_owner{resource::MemoryOwnerKind::capture,12};
// Build a transferable selection allocator retaining the supplied account. See
// docs/query_memory.md.
template<class T> resource::OwnerAllocator<T> selection_allocator(const resource::MemoryAccount& account) {
  return resource::OwnerAllocator<T>(account,resource::MemoryPurpose::capture,selection_memory_owner);
}
// Carry fixed selection stop/resource/component diagnostics through unwinding. See
// docs/selection.md.
struct Failure {
  Stop stop;
  Resource resource = Resource::none;
  std::optional<rank::Stop> component;
  rank::Reasons reasons{};
};
void require(bool, Stop = Stop::internal_error);
[[nodiscard]] Failure component_diagnostic(rank::Stop, rank::Reasons = 0) noexcept;
[[noreturn]] void component_failure(rank::Stop, rank::Reasons = 0);

// Own one aggregate logical-processing grant and optional active timer. See
// docs/selection_accounting.md.
struct Budget {
  rank::Limits limits;
  rank::Usage usage;
  resource::MemoryAccount memory;
  std::chrono::steady_clock::time_point started{};
  bool running{};
  explicit Budget(const rank::Limits&, rank::Usage = {},const resource::MemoryAccount& = {});
  void check() const;
  void sample();
  void finish() noexcept;
  static void add(std::uint64_t&, std::uint64_t, std::uint64_t, Resource);
  void work(std::uint64_t = 1);
  void cells(std::uint64_t = 1);
  void bytes(std::uint64_t);
  void keys(std::uint64_t);
  // Admit logical vector cells and element-storage bytes before allocation. See
  // docs/selection_accounting.md.
  template<class T> void vector(std::size_t n) {
    if (n > UINT64_MAX / sizeof(T)) throw Failure{Stop::resource_limit, Resource::payload_bytes, {}, 0};
    cells(static_cast<std::uint64_t>(n));
    bytes(static_cast<std::uint64_t>(n) * sizeof(T));
  }
  // Run a synchronous borrowed C02 visitor under the same cumulative Usage. See
  // docs/selection_accounting.md.
  template<class Function> void borrowed(Function&& function) {
    sample();
    auto caps = limits;
    caps.active_time.reset();
    rd::Budget inner(caps, usage,memory);
    try { function(inner); }
    catch (...) { usage = inner.usage; throw; }
    usage = inner.usage;
    sample();
  }
  // The stopped outer timer measures the whole synchronous delegated phase.
  // Its difference from the component's own elapsed value is outer overhead.
  rank::Limits begin_delegate(const rank::Usage& preparation = {});
  void end_delegate(const rank::Usage&, const rank::Usage& preparation = {});
};

// Scope artifact evidence origin for cache-key reproduction. See docs/selection_binding.md.
enum class Origin { absent, as_of, physical, delta, session };
// Own one FIFO key and complete native plan with logical retention charge. See
// docs/selection_accounting.md.
struct Entry {
  SelectionText key;
  CompiledProgram plan;
  std::uint64_t payload;
  resource::AccountedUnique<Entry> next;
  Entry(const resource::MemoryAccount& account,std::string_view k,CompiledProgram p,std::uint64_t bytes)
      :key(k,selection_allocator<char>(account)),plan(std::move(p)),payload(bytes) {}
};
// Each FIFO node keeps its allocating query account. Splicing never transfers a
// node to an unrelated container allocator; clearing destroys long chains iteratively.
// Manage account-preserving FIFO links without recursive chain teardown. See
// docs/selection_accounting.md.
class Entries {
 public:
  struct Iterator {
    const Entry* value{};
    const Entry& operator*() const noexcept {return *value;}
    const Entry* operator->() const noexcept {return value;}
    Iterator& operator++() noexcept {value=value->next.get();return *this;}
    bool operator==(const Iterator&) const=default;
  };
  Entries()=default;
  Entries(const Entries&)=delete;
  Entries& operator=(const Entries&)=delete;
  // Transfer a chain while resetting source tail/count. See docs/selection_accounting.md.
  Entries(Entries&& other) noexcept
      :first_(std::move(other.first_)),last_(std::exchange(other.last_,nullptr)),size_(std::exchange(other.size_,0)) {}
  ~Entries() {clear();}
  std::size_t size() const noexcept {return size_;}
  bool empty() const noexcept {return !first_;}
  Iterator begin() const noexcept {return {first_.get()};}
  Iterator end() const noexcept {return {};}
  // Link one prepared detached node at the FIFO tail. See docs/selection_accounting.md.
  void push_back(resource::AccountedUnique<Entry> entry) noexcept {
    auto* raw=entry.get();if(last_)last_->next=std::move(entry);else first_=std::move(entry);
    last_=raw;++size_;
  }
  // Retire a funded front node into another list without destruction. See
  // docs/selection_accounting.md.
  void move_front_to(Entries& destination) noexcept {
    auto entry=std::move(first_);first_=std::move(entry->next);--size_;if(!first_)last_=nullptr;
    destination.push_back(std::move(entry));
  }
  // Splice a disjoint prepared list onto this FIFO. See docs/selection_accounting.md.
  void append(Entries& other) noexcept {
    if(other.empty())return;
    if(last_)last_->next=std::move(other.first_);else first_=std::move(other.first_);
    last_=std::exchange(other.last_,nullptr);size_+=std::exchange(other.size_,0);
  }
  // Destroy FIFO nodes iteratively while preserving no-allocation cleanup. See
  // docs/selection_accounting.md.
  void clear() noexcept {
    while(first_) {auto entry=std::move(first_);first_=std::move(entry->next);}
    last_=nullptr;size_=0;
  }
 private:
  resource::AccountedUnique<Entry> first_;
  Entry* last_{};
  std::size_t size_{};
};
// Own cache configuration, committed statistics and FIFO entries. See
// docs/selection_accounting.md.
struct CacheData {
  CacheLimits limits;
  CacheStatistics statistics;
  Entries entries;
  explicit CacheData(CacheLimits value) : limits(value) {}
};
// Own all unpublished/published selection context in one account-backed backing object. See
// docs/selection.md.
struct SelectionData {
  resource::MemoryAccount account;
  CandidateSnapshot snapshot;
  CapturedSource source;
  CapturedRequest request;
  std::optional<rank::Evidence> evidence;
  SelectionVector<Assessment> assessments;
  SelectionVector<CandidateDecision> decisions;
  SelectionVector<patterns::Analysis> pattern_analyses;
  std::optional<MinimumHeightCandidate> chosen;
  std::optional<CompiledProgram> plan;
  std::size_t selected{};
  rank::Policy effective = rank::Policy::height_only;
  rank::Reasons fallback{};
  rank::Usage usage;
  PreparationTiming timing = PreparationTiming::absent;
  CacheObservation cache;
  std::optional<SelectionText> key;
  SelectionData(const resource::MemoryAccount&,const CandidateSnapshot&,const Source&,const Request&,
      const std::optional<rank::Evidence>&);
};
struct Factory {
  static Selection selection(std::shared_ptr<const SelectionData> data) noexcept { return Selection(std::move(data)); }
  static CacheData* cache(PlanCache* value) noexcept { return value ? value->data_.get() : nullptr; }
};
// Keep speculative result/cache statistics and funded list changes private. See
// docs/selection_accounting.md.
struct Prepared {
  std::shared_ptr<SelectionData> data;
  CacheData* cache{};
  CacheStatistics next;
  Entries insertion;
  Entries retired;
  std::size_t evictions{};
  void commit() noexcept;
};

PreparationTiming preparation_timing(const std::optional<rank::Evidence>&) noexcept;
void validate_slot_limit(std::string_view, Budget&);
int decimal_compare(std::string_view, std::string_view, Budget&);
bool key_less(std::string_view, std::string_view, Budget&);
bool equal_bytes(std::string_view, std::string_view, Budget&, std::uint64_t* compared = nullptr);
void source_binding(const CandidateSnapshot&, const Source&, const std::optional<rank::Evidence>&, Budget&);
void compiled_binding(const CandidateSnapshot&, const Source&, const MinimumHeightCandidate&, const CompiledProgram&, Budget&);
SelectionText cache_binding(const SelectionData&, Origin, Budget&);
// Diagnostic record encoders used by private framing/mutation consumers. They
// return bytes only; they cannot create a proof, Selection or cache entry.
std::string scalar_binding_record(const Value&, Budget&);
std::string tree_binding_record(const FreeConnexTree&, Budget&);
std::string program_binding_record(const frontend::NormalizedSql&, Budget&);
std::string core_binding_record(const Catalog&, const Query&, Budget&);
void direct_source_payload(const MinimumHeightCandidate&, Budget&);
void identity_payload(const io::QueryIdentity&, Budget&);
void identity_payload(const program::QueryIdentity&, Budget&);
void source_payload(const MinimumHeightCandidate&, const PhysicalPlan&, Budget&);
void source_payload(const MinimumHeightCandidate&, const CompiledProgram&, Budget&);
void compiled_payload(const PhysicalPlan&, Budget&);
void compiled_payload(const CompiledProgram&, Budget&);
std::uint64_t cache_plan_payload(const MinimumHeightCandidate&, const CompiledProgram&, Budget&);
void prepare_cache(Prepared&, CacheData*, CacheUse, Budget&);
void stage_cache_entry(Prepared&, Budget&);

// Own one synchronous selection transaction over caller inputs. See docs/selection.md.
struct Operation {
  const CandidateSnapshot& snapshot;
  const Source& source;
  const Request& request;
  CacheData* cache{};
  CacheUse cache_use;
  Origin origin;
  std::optional<rank::Evidence> evidence;
  Attempt diagnostic;
  Budget budget;
  Operation(const CandidateSnapshot&, const Source&, const Request&,
      const std::optional<rank::Evidence>&, PlanCache*, CacheUse, Origin,const resource::MemoryAccount& = {});
  void admit();
  void attach(const rank::Evidence&);
  bool needs_sources() const noexcept;
  Prepared prepare();
  void finalize(Prepared&);
  void note(const Failure&) noexcept;
  void note(rank::Stop) noexcept;
  void finish() noexcept;
};
} // namespace crown::planner::selection::detail
