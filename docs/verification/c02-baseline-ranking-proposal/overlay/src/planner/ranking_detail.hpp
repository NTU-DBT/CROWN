#pragma once
#include "crown/planner/ranking.hpp"
#include <array>
#include <limits>
#include <utility>

namespace crown::planner::ranking::detail {
struct Failure {Stop stop;};
struct Budget {
  Limits limits; Usage usage;
  std::chrono::steady_clock::time_point started{};
  std::uint64_t carried_active{};
  explicit Budget(const Limits& value,Usage initial={}):limits(value),usage(initial),carried_active(initial.active_nanoseconds) {
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
 private:
  std::array<std::uint32_t,16> limbs_{};
  void check(const Budget&) const;
};
struct EvidenceData {
  PhysicalPlan plan;
  std::string binding;
  std::vector<InputWeight> weights;
  std::vector<SourceCardinality> sources;
  std::vector<SourceObservation> source_observations;
  EvidenceIdentity identity;
  CaptureAccounting accounting;
  Reasons depth_reasons=reason(Reason::not_captured),memory_reasons=reason(Reason::not_captured);
  std::uint64_t denominator{};
  Usage preparation;
  explicit EvidenceData(PhysicalPlan p):plan(std::move(p)) {}
};
struct ResultData {
  CandidateSnapshot snapshot;
  Request request;
  Policy effective;
  Reasons fallback{};
  std::optional<Evidence> evidence;
  std::vector<CandidateScore> scores;
  std::size_t selected{};
  Usage usage;
  ResultData(CandidateSnapshot s,Request r,std::optional<Evidence> e)
      :snapshot(std::move(s)),request(std::move(r)),effective(request.policy),evidence(std::move(e)) {}
};
struct Factory {
  static Evidence evidence(std::shared_ptr<const EvidenceData> p){return Evidence(std::move(p));}
  static const EvidenceData& data(const Evidence& x){return *x.data_;}
  static Result result(std::shared_ptr<const ResultData> p){return Result(std::move(p));}
};
std::string binding(const Catalog&,const Query&,Budget&);
bool equal_bytes(const std::string&,const std::string&,Budget&);
} // namespace crown::planner::ranking::detail
