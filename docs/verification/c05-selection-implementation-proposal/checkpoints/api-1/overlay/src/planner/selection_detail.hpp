#pragma once

#include "crown/planner/selection.hpp"
#include "ranking_detail.hpp"
#include <list>
#include <limits>

namespace crown::planner::selection::detail {
namespace rd = ::crown::planner::ranking::detail;
struct Failure {
  Stop stop;
  Resource resource = Resource::none;
  std::optional<rank::Stop> component;
  rank::Reasons reasons{};
};
void require(bool, Stop = Stop::internal_error);
[[noreturn]] void component_failure(rank::Stop, rank::Reasons = 0);

struct Budget {
  rank::Limits limits;
  rank::Usage usage;
  std::chrono::steady_clock::time_point started{};
  bool running{};
  explicit Budget(const rank::Limits&, rank::Usage = {});
  void check() const;
  void sample();
  void finish() noexcept;
  static void add(std::uint64_t&, std::uint64_t, std::uint64_t, Resource);
  void work(std::uint64_t = 1);
  void cells(std::uint64_t = 1);
  void bytes(std::uint64_t);
  void keys(std::uint64_t);
  template<class T> void vector(std::size_t n) {
    if (n > UINT64_MAX / sizeof(T)) throw Failure{Stop::resource_limit, Resource::payload_bytes, {}, 0};
    cells(static_cast<std::uint64_t>(n));
    bytes(static_cast<std::uint64_t>(n) * sizeof(T));
  }
  template<class Function> void borrowed(Function&& function) {
    sample();
    auto caps = limits;
    caps.active_time.reset();
    rd::Budget inner(caps, usage);
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

enum class Origin { absent, as_of, physical, delta, session };
struct Entry { std::string key; PhysicalPlan plan; std::uint64_t payload; };
struct CacheData {
  CacheLimits limits;
  CacheStatistics statistics;
  std::list<Entry> entries;
  explicit CacheData(CacheLimits value) : limits(value) {}
};
struct SelectionData {
  CandidateSnapshot snapshot;
  Source source;
  Request request;
  std::optional<rank::Evidence> evidence;
  std::vector<Assessment> assessments;
  std::vector<CandidateDecision> decisions;
  std::optional<MinimumHeightCandidate> chosen;
  std::optional<PhysicalPlan> plan;
  std::size_t selected{};
  rank::Policy effective = rank::Policy::height_only;
  rank::Reasons fallback{};
  rank::Usage usage;
  PreparationTiming timing = PreparationTiming::absent;
  CacheObservation cache;
  std::optional<std::string> key;
  SelectionData(const CandidateSnapshot& s, const Source& p, const Request& r,
      const std::optional<rank::Evidence>& e) : snapshot(s), source(p), request(r), evidence(e) {}
};
struct Factory {
  static Selection selection(std::shared_ptr<const SelectionData> data) noexcept { return Selection(std::move(data)); }
  static CacheData* cache(PlanCache* value) noexcept { return value ? value->data_.get() : nullptr; }
};
struct Prepared {
  std::shared_ptr<SelectionData> data;
  CacheData* cache{};
  CacheStatistics next;
  std::list<Entry> insertion;
  std::list<Entry> retired;
  std::size_t evictions{};
  void commit() noexcept;
};

PreparationTiming preparation_timing(const std::optional<rank::Evidence>&) noexcept;
void validate_slot_limit(const std::string&, Budget&);
int decimal_compare(const std::string&, const std::string&, Budget&);
bool key_less(const std::string&, const std::string&, Budget&);
bool equal_bytes(const std::string&, const std::string&, Budget&, std::uint64_t* compared = nullptr);
void source_binding(const CandidateSnapshot&, const Source&, const std::optional<rank::Evidence>&, Budget&);
void compiled_binding(const CandidateSnapshot&, const Source&, const MinimumHeightCandidate&, const PhysicalPlan&, Budget&);
std::string cache_binding(const SelectionData&, Origin, Budget&);
// Diagnostic record encoders used by private framing/mutation consumers. They
// return bytes only; they cannot create a proof, Selection or cache entry.
std::string scalar_binding_record(const Value&, Budget&);
std::string tree_binding_record(const FreeConnexTree&, Budget&);
std::string program_binding_record(const frontend::NormalizedSql&, Budget&);
std::string core_binding_record(const Catalog&, const Query&, Budget&);
void direct_source_payload(const MinimumHeightCandidate&, Budget&);
void identity_payload(const io::QueryIdentity&, Budget&);
void source_payload(const MinimumHeightCandidate&, const PhysicalPlan&, Budget&);
void compiled_payload(const PhysicalPlan&, Budget&);
std::uint64_t cache_plan_payload(const MinimumHeightCandidate&, const PhysicalPlan&, Budget&);
void prepare_cache(Prepared&, CacheData*, CacheUse, Budget&);
void stage_cache_entry(Prepared&, Budget&);

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
      const std::optional<rank::Evidence>&, PlanCache*, CacheUse, Origin);
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
