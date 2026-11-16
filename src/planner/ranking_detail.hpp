#pragma once
#include "crown/planner/ranking.hpp"
#include <array>
#include <limits>
#include <utility>

namespace crown::planner::ranking::detail {
inline constexpr resource::MemoryAttribution evidence_memory_owner{resource::MemoryOwnerKind::capture,9};
inline constexpr resource::MemoryAttribution score_memory_owner{resource::MemoryOwnerKind::capture,11};
template<class T> resource::OwnerAllocator<T> score_allocator(const resource::MemoryAccount& account) {
  return resource::OwnerAllocator<T>(account,resource::MemoryPurpose::capture,score_memory_owner);
}
template<class T> using Scratch=std::vector<T,resource::MemoryAllocator<T>>;
template<class T> resource::MemoryAllocator<T> scratch_allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account,resource::MemoryPurpose::scratch,score_memory_owner);
}
template<class T> resource::OwnerAllocator<T> evidence_allocator(const resource::MemoryAccount& account) {
  return resource::OwnerAllocator<T>(account,resource::MemoryPurpose::capture,evidence_memory_owner);
}
struct Failure {Stop stop;};
// Logical debits are cumulative, not transactional: later byte rejection can
// leave earlier work/cells spent. Actual account capacity is a separate limit.
struct Budget {
  Limits limits; Usage usage;
  resource::MemoryAccount memory;
  std::chrono::steady_clock::time_point started{};
  std::uint64_t carried_active{};
  explicit Budget(const Limits& value,Usage initial={},const resource::MemoryAccount& account={})
      :limits(value),usage(initial),memory(account),carried_active(initial.active_nanoseconds) {
    if(limits.score_bits==0 || limits.score_bits>512 ||
        (limits.active_time && limits.active_time->count()<0)) throw Failure{Stop::invalid_limits};
    if(limits.active_time)started=std::chrono::steady_clock::now();
    check_all();
  }
  void time() {
    if(!limits.active_time){return;}
    const auto elapsed=std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now()-started).count();
    if(elapsed<0){throw Failure{Stop::internal_error};}
    const auto n=static_cast<std::uint64_t>(elapsed);
    usage.active_nanoseconds=n>UINT64_MAX-carried_active?UINT64_MAX:carried_active+n;
    if(usage.active_nanoseconds>=static_cast<std::uint64_t>(limits.active_time->count())){throw Failure{Stop::time_limit};}
  }
  static void add(std::uint64_t& value,std::uint64_t n,std::uint64_t cap,Stop stop) {
    if(value>cap || n>cap-value){throw Failure{stop};}
    value+=n;
  }
  void work(std::uint64_t n=1){time();add(usage.work,n,limits.work,Stop::work_limit);}
  void cells(std::uint64_t n=1){add(usage.cells,n,limits.cells,Stop::cell_limit);}
  void bytes(std::uint64_t n){add(usage.payload_bytes,n,limits.payload_bytes,Stop::byte_limit);}
  void keys(std::uint64_t n){work(n);add(usage.binding_key_bytes,n,limits.binding_key_bytes,Stop::byte_limit);}
  void check_all() const {
    if(usage.work>limits.work)throw Failure{Stop::work_limit};
    if(usage.cells>limits.cells)throw Failure{Stop::cell_limit};
    if(usage.binding_key_bytes>limits.binding_key_bytes || usage.payload_bytes>limits.payload_bytes)throw Failure{Stop::byte_limit};
    if(usage.lowering_work>limits.lowering_work || usage.identity_work>limits.identity_work ||
        usage.binding_replay_work>limits.binding_replay_work || usage.normalization_work>limits.normalization_work)throw Failure{Stop::lowering_limit};
    if(limits.active_time && usage.active_nanoseconds>=static_cast<std::uint64_t>(limits.active_time->count()))throw Failure{Stop::time_limit};
  }
  template<class T> void vector_items(std::size_t n) {
    if(n>std::numeric_limits<std::uint64_t>::max()/sizeof(T))throw Failure{Stop::byte_limit};
    cells(static_cast<std::uint64_t>(n));bytes(static_cast<std::uint64_t>(n)*sizeof(T));
  }
};
// Little-endian base-2^32; all published values have at most 512 bits.
class UInt {
 public:
  UInt()=default;
  static UInt from(std::uint64_t,Budget&);
  static UInt add(const UInt&,const UInt&,Budget&);
  static UInt multiply(const UInt&,const UInt&,Budget&);
  static int compare(const UInt&,const UInt&,Budget&);
  bool zero() const noexcept;
  unsigned bits() const noexcept;
  std::string decimal(Budget&) const;
  ScoreText decimal(Budget&,const resource::MemoryAccount&) const;
 private:
  struct Digits {std::array<char,155> bytes{};std::size_t count=0;};
  Digits digits(Budget&) const;
  std::array<std::uint32_t,16> limbs_{};
  void check(const Budget&) const;
};
struct EvidenceData {
  CompiledProgram plan;
  EvidenceText binding;
  EvidenceVector<InputWeight> weights;
  EvidenceVector<SourceCardinality> sources;
  EvidenceVector<SourceObservation> source_observations;
  EvidenceIdentity identity;
  CaptureAccounting accounting;
  Reasons depth_reasons=reason(Reason::not_captured),memory_reasons=reason(Reason::not_captured);
  std::uint64_t denominator{};
  Usage preparation;
  explicit EvidenceData(CompiledProgram p):plan(std::move(p)),binding(evidence_allocator<char>(plan.account())),
      weights(evidence_allocator<InputWeight>(plan.account())),sources(evidence_allocator<SourceCardinality>(plan.account())),
      source_observations(evidence_allocator<SourceObservation>(plan.account())) {}
  explicit EvidenceData(const PhysicalPlan& p):EvidenceData(CompiledProgram::standalone(p)) {}
};
struct ResultData {
  resource::MemoryAccount account;
  CandidateSnapshot snapshot;
  Request request;
  Policy effective;
  Reasons fallback{};
  std::optional<Evidence> evidence;
  ScoreVector<CandidateScore> scores;
  std::size_t selected{};
  Usage usage;
  ResultData(const resource::MemoryAccount& a,CandidateSnapshot s,Request r,std::optional<Evidence> e)
      :account(a),snapshot(std::move(s)),request(std::move(r)),effective(request.policy),evidence(std::move(e)),scores(score_allocator<CandidateScore>(a)) {}
};
struct Factory {
  static Evidence evidence(std::shared_ptr<const EvidenceData> p){return Evidence(std::move(p));}
  static const EvidenceData& data(const Evidence& x){return *x.data_;}
  static Result result(std::shared_ptr<const ResultData> p){return Result(std::move(p));}
};
std::string binding(const Catalog&,const Query&,Budget&);
std::string binding(const program::Catalog&,const program::Query&,Budget&);
EvidenceText binding(const Catalog&,const Query&,Budget&,const resource::MemoryAccount&);
EvidenceText binding(const program::Catalog&,const program::Query&,Budget&,const resource::MemoryAccount&);
ScoreText score_binding(const Catalog&,const Query&,Budget&,const resource::MemoryAccount&);
ScoreText score_binding(const program::Catalog&,const program::Query&,Budget&,const resource::MemoryAccount&);
bool equal_bytes(std::string_view,std::string_view,Budget&);
} // namespace crown::planner::ranking::detail
