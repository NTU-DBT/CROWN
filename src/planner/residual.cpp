#include "crown/planner/residual.hpp"

#include "crown/api/error.hpp"
#include "continuation_budget.hpp"
#include "residual_machine.hpp"
#include <algorithm>
#include <limits>
#include <new>
#include <utility>

namespace crown::planner {
namespace rd = residual_detail;
namespace cd = continuation_detail;
namespace {
// Public artifact getters borrow from a live owning handle. Only this null
// guard is needed here; publication already established the payload invariants.
template<class T> const T& require(const std::shared_ptr<const T>& value) {
  if (!value) throw Error("invalid_residual_handle", "residual artifact was moved from");
  return *value;
}
void validate_limits(const ResidualLimits& value) {
  if (!cd::valid_ceiling(value.residual) || !cd::valid_ceiling(value.exact.producer) ||
      !cd::valid_ceiling(value.exact.replay)) throw Error("invalid_residual_limits", "negative active time limit");
}
bool monotone_exact(const ContinuationLimits& a, const ContinuationLimits& b) noexcept {
  return cd::monotone_phase(a.producer, b.producer) && cd::monotone_phase(a.replay, b.replay) &&
         cd::monotone_ceiling(a.logical_depth, b.logical_depth);
}
ResidualStatistics add(ResidualStatistics a, const ResidualStatistics& b) noexcept {
#define ADD(name) cd::saturating_add(a.name, b.name)
  ADD(hierarchy_tests); ADD(rounds); ADD(eligibility_pairs); ADD(deletions);
  ADD(restorations); ADD(drafts); ADD(rejected_drafts); ADD(generalized_grafts);
  ADD(exact_repairs); ADD(original_exact_runs); ADD(candidate_publications); ADD(admissions);
#undef ADD
  return a;
}
ResidualStopReason ordinary_stop(StopReason value) noexcept {
  switch (value) {
    case StopReason::total_work: return ResidualStopReason::total_work;
    case StopReason::total_time: return ResidualStopReason::total_time;
    case StopReason::counter_overflow: return ResidualStopReason::counter_overflow;
    default: return ResidualStopReason::internal_failure;
  }
}
} // namespace
namespace residual_detail {
struct ArtifactFactory {
  static ResidualTrace trace(std::shared_ptr<const TraceData> value) noexcept { return ResidualTrace(std::move(value)); }
  static ResidualCandidate candidate(std::shared_ptr<const CandidateData> value) noexcept { return ResidualCandidate(std::move(value)); }
};
}
ResidualTrace::ResidualTrace(std::shared_ptr<const rd::TraceData> value) noexcept : data_(std::move(value)) {}
bool ResidualTrace::valid() const noexcept { return static_cast<bool>(data_); }
const Catalog& ResidualTrace::catalog() const { return require(data_).binding->catalog; }
const Query& ResidualTrace::query() const { return require(data_).binding->query; }
const ResidualTraceRecord& ResidualTrace::record() const { return *require(data_).record; }
ResidualCandidate::ResidualCandidate(std::shared_ptr<const rd::CandidateData> value) noexcept : data_(std::move(value)) {}
bool ResidualCandidate::valid() const noexcept { return static_cast<bool>(data_); }
const Catalog& ResidualCandidate::catalog() const { return require(data_).binding->catalog; }
const Query& ResidualCandidate::query() const { return require(data_).binding->query; }
const FreeConnexTree& ResidualCandidate::tree() const {
  const auto& p = require(data_);
  return p.checked ? *p.checked->tree : p.exact_upper->tree();
}
std::size_t ResidualCandidate::height() const {
  const auto& p = require(data_);
  return p.checked ? p.checked->height : p.exact_upper->height();
}
ResidualOrigin ResidualCandidate::origin() const { return require(data_).origin; }
ResidualTrace ResidualCandidate::trace() const { return rd::ArtifactFactory::trace(require(data_).trace); }

struct ResidualSearch::Impl {
  enum class Stage {
    reduction_shell, reduction, trace_shell, trace_replay, trace_publish,
    reconstruction_shell, reconstruction, publish_candidate, original_shell,
    original, exact_candidate, finish, complete, failed, cancelled
  };
  std::shared_ptr<const cd::BindingData> binding;
  ResidualOptions options;
  std::shared_ptr<rd::ConstructionBudget> construction;
  cd::ResourceLedger ledger;
  Stage stage = Stage::reduction_shell;
  ResidualStopReason last_stop = ResidualStopReason::none;
  StopReason exact_stop = StopReason::none;
  ResidualStopReason failure = ResidualStopReason::none;
  std::uint64_t revision = 0;
  ResidualStatistics own_statistics, retained_statistics;
  SearchProgress retained_exact;
  bool original_scope = false;
  bool trace_was_complete = false;
  std::unique_ptr<rd::ReductionMachine> reduction;
  std::unique_ptr<rd::TraceReplayMachine> checker;
  std::unique_ptr<rd::ReconstructionMachine> reconstruction;
  std::unique_ptr<ExactSearch> original;
  std::shared_ptr<const ResidualTraceRecord> record;
  std::shared_ptr<const rd::TraceData> trace_data;
  std::shared_ptr<const cd::CheckedUpper> checked;
  std::shared_ptr<const rd::CandidateData> candidate_data;
  std::optional<VerifiedOptimum> exact_optimum;
  std::optional<VerifiedInfeasible> exact_infeasibility;

  Impl(std::shared_ptr<const cd::BindingData> input, ResidualOptions value)
      : binding(std::move(input)), options(value),
        construction(std::make_shared<rd::ConstructionBudget>(value.limits)), ledger(value.limits.residual) {}
  bool terminal() const noexcept { return stage == Stage::complete || stage == Stage::failed || stage == Stage::cancelled; }
  ResidualStopReason terminal_reason() const noexcept {
    return stage == Stage::complete ? ResidualStopReason::complete :
           stage == Stage::cancelled ? ResidualStopReason::cancelled : failure;
  }
  void fail(ResidualStopReason value) noexcept { failure = value; stage = Stage::failed; }
  ResidualStatistics statistics() const noexcept {
    auto result = add(own_statistics, retained_statistics);
    if (reduction) result = add(result, reduction->statistics());
    if (reconstruction) result = add(result, reconstruction->statistics());
    return result;
  }
  SearchProgress exact_progress() const noexcept {
    if (original) return original->progress();
    if (reconstruction) return reconstruction->exact_progress();
    return retained_exact;
  }
  std::size_t depth() const noexcept {
    if (stage == Stage::reduction && reduction) return reduction->current_depth();
    if (stage == Stage::trace_replay && checker) return checker->current_depth();
    if (stage == Stage::reconstruction && reconstruction) return reconstruction->current_depth();
    return 0;
  }
  ResidualPhase phase() const noexcept {
    switch (stage) {
      case Stage::reduction_shell: return ResidualPhase::admitted;
      case Stage::reduction: return reduction->phase();
      case Stage::trace_shell: case Stage::trace_replay: case Stage::trace_publish: return ResidualPhase::trace_replay;
      case Stage::reconstruction_shell: return ResidualPhase::seed;
      case Stage::reconstruction: return reconstruction->phase();
      case Stage::publish_candidate: return ResidualPhase::validate_candidate;
      case Stage::original_shell: case Stage::original: case Stage::exact_candidate: case Stage::finish: return ResidualPhase::exact_original;
      case Stage::complete: return ResidualPhase::complete;
      case Stage::failed: return ResidualPhase::failed;
      case Stage::cancelled: return ResidualPhase::cancelled;
    }
    return ResidualPhase::failed;
  }
  void record_counter_room(std::uint64_t value) const {
    if (value == std::numeric_limits<std::uint64_t>::max()) throw rd::Limited(ResidualStopReason::counter_overflow);
  }
  // One retained worker/publication operation. Never upgrade a prefix proof:
  // only a final original P02 tree can publish an upper, and only the separate
  // full-original ExactSearch can publish minimum/infeasibility authority.
  rd::Step unit() {
    const cd::UnitContext context{options.limits.logical_depth};
    switch (stage) {
      case Stage::reduction_shell: {
        auto next = std::make_unique<rd::ReductionMachine>(binding, construction);
        reduction = std::move(next); stage = Stage::reduction; break;
      }
      case Stage::reduction: {
        const auto step = reduction->step(context);
        if (step.event == rd::Event::complete) {
          record = reduction->trace_record();
          if (!record) { fail(ResidualStopReason::internal_failure); break; }
          trace_was_complete = true; stage = Stage::trace_shell;
        }
        return step;
      }
      case Stage::trace_shell: {
        auto next = std::make_unique<rd::TraceReplayMachine>(binding, record, construction);
        checker = std::move(next); stage = Stage::trace_replay; break;
      }
      case Stage::trace_replay: {
        const auto step = checker->step(context);
        if (step.event == rd::Event::invalid_trace) fail(ResidualStopReason::invalid_trace);
        else if (step.event == rd::Event::complete) {
          if (!checker->report().valid) { fail(ResidualStopReason::invalid_trace); break; }
          stage = Stage::trace_publish;
        }
        return step;
      }
      case Stage::trace_publish: {
        construction->prepare(1, 0);
        auto next = std::make_shared<const rd::TraceData>(rd::TraceData{binding, record});
        trace_data = std::move(next); construction->commit(1, 0);
        stage = Stage::reconstruction_shell; break;
      }
      case Stage::reconstruction_shell: {
        auto next = std::make_unique<rd::ReconstructionMachine>(binding, record, construction);
        reconstruction = std::move(next); stage = Stage::reconstruction; break;
      }
      case Stage::reconstruction: {
        const auto step = reconstruction->step(context);
        if (step.event == rd::Event::need_original_exact) stage = Stage::original_shell;
        else if (step.event == rd::Event::checked_upper || step.event == rd::Event::complete) {
          checked = reconstruction->checked_upper();
          if (!checked || checked->binding != binding || !checked->report || !checked->report->valid || !checked->tree) {
            fail(ResidualStopReason::internal_failure); break;
          }
          stage = Stage::publish_candidate;
        }
        return step;
      }
      case Stage::publish_candidate: {
        construction->prepare(1, 0); record_counter_room(own_statistics.candidate_publications);
        auto next = std::make_shared<const rd::CandidateData>(rd::CandidateData{
            binding, trace_data, checked, {}, reconstruction->origin()});
        candidate_data = std::move(next); construction->commit(1, 0);
        ++own_statistics.candidate_publications;
        stage = options.mode == ResidualMode::require_exact_original ? Stage::original_shell : Stage::complete;
        break;
      }
      case Stage::original_shell: {
        // Explicit owned subsearch admission: catalog/query copy and validation
        // are separate costs, as in P06. No search runs inside create().
        construction->prepare(1, 0);
        record_counter_room(own_statistics.original_exact_runs); record_counter_room(own_statistics.admissions);
        auto next = std::make_unique<ExactSearch>(ExactSearch::create(binding->catalog, binding->query,
            SearchOptions{SearchPolicy::strict, options.limits.exact}));
        original = std::move(next); construction->commit(1, 0);
        ++own_statistics.original_exact_runs; ++own_statistics.admissions;
        original_scope = true; stage = Stage::original; break;
      }
      case Stage::original: {
        const auto update = original->advance(WorkQuantum{1, {}});
        if (update.stopped_for == StopReason::quantum_work || update.stopped_for == StopReason::quantum_time) break;
        if (update.stopped_for == StopReason::complete) {
          exact_optimum = original->optimum(); exact_infeasibility = original->infeasibility();
          if (exact_optimum) stage = Stage::exact_candidate;
          else if (exact_infeasibility && !candidate_data) stage = Stage::finish;
          else fail(ResidualStopReason::internal_failure);
          break;
        }
        if (update.stopped_for == StopReason::internal_failure || update.stopped_for == StopReason::invalid_certificate ||
            update.stopped_for == StopReason::cancelled || update.stopped_for == StopReason::moved_from) {
          fail(ResidualStopReason::internal_failure); break;
        }
        if (update.stopped_for == StopReason::counter_overflow)
          return {rd::Event::stopped, ResidualStopReason::counter_overflow, update.stopped_for, 0};
        return {rd::Event::stopped, ResidualStopReason::exact_limit, update.stopped_for, 0};
      }
      case Stage::exact_candidate: {
        if (candidate_data) {
          const auto old_height = candidate_data->checked ? candidate_data->checked->height : candidate_data->exact_upper->height();
          if (old_height < exact_optimum->height()) { fail(ResidualStopReason::internal_failure); break; }
          if (old_height == exact_optimum->height()) { stage = Stage::finish; break; }
        }
        construction->prepare(1, 0); record_counter_room(own_statistics.candidate_publications);
        auto next = std::make_shared<const rd::CandidateData>(rd::CandidateData{
            binding, trace_data, {}, exact_optimum->upper(), ResidualOrigin::exact_original});
        candidate_data = std::move(next); construction->commit(1, 0);
        ++own_statistics.candidate_publications; stage = Stage::finish; break;
      }
      case Stage::finish: stage = Stage::complete; break;
      case Stage::complete: case Stage::failed: case Stage::cancelled: break;
    }
    return {};
  }
};
ResidualSearch::ResidualSearch(std::unique_ptr<Impl> value) noexcept : data_(std::move(value)) {}
ResidualSearch::~ResidualSearch() = default;
ResidualSearch::ResidualSearch(ResidualSearch&&) noexcept = default;
ResidualSearch& ResidualSearch::operator=(ResidualSearch&&) noexcept = default;
// Input ownership/validation and initial allocations precede work metering;
// no reduction or delegated exact search runs inside admission.
ResidualSearch ResidualSearch::create(Catalog catalog, Query query, ResidualOptions options) {
  validate_limits(options.limits);
  if (options.mode != ResidualMode::candidates_with_exact_repair && options.mode != ResidualMode::require_exact_original)
    throw Error("invalid_residual_mode", "unknown residual planning mode");
  validate(catalog, query);
  auto input = std::make_shared<const cd::BindingData>(cd::BindingData{
      std::move(catalog), std::move(query), AccountingVersion::continuation_v1});
  return ResidualSearch(std::make_unique<Impl>(std::move(input), options));
}
// Keep limit/bad_alloc catches: pending closures remain retryable. The final
// catch protects this noexcept boundary and terminalizes internal invariant
// failures; stop reporting is fixed-size and allocates no error message.
ResidualAdvance ResidualSearch::advance(WorkQuantum quantum) noexcept {
  const auto answer = [&](ResidualStopReason reason, StopReason exact = StopReason::none) noexcept {
    return ResidualAdvance{reason, exact, progress()};
  };
  if (!data_) return answer(ResidualStopReason::moved_from);
  if (quantum.active_time && quantum.active_time->count() < 0) return answer(ResidualStopReason::invalid_quantum);
  if (quantum.work == 0) return answer(ResidualStopReason::quantum_work);
  if (quantum.active_time && quantum.active_time->count() == 0) return answer(ResidualStopReason::quantum_time);
  auto& d = *data_;
  if (d.terminal()) return answer(d.terminal_reason(), d.exact_stop);
  ResidualStopReason stop = ResidualStopReason::none;
  StopReason exact = StopReason::none;
  {
    cd::ActiveMeter meter(d.ledger);
    const auto started = std::chrono::steady_clock::now();
    std::uint64_t used = 0;
    for (;;) {
      meter.sample();
      if (used >= quantum.work) { stop = ResidualStopReason::quantum_work; break; }
      if (quantum.active_time && std::chrono::steady_clock::now() - started >= *quantum.active_time) {
        stop = ResidualStopReason::quantum_time; break;
      }
      const auto ceiling = d.ledger.check();
      if (ceiling != StopReason::none) { stop = ordinary_stop(ceiling); if (ceiling == StopReason::counter_overflow) d.fail(stop); break; }
      ++used; ++d.ledger.counters.attempted;
      try {
        const auto result = d.unit();
        d.ledger.depth(d.depth());
        if (result.event == rd::Event::stopped) {
          stop = result.reason; exact = result.exact_reason;
          if (stop == ResidualStopReason::allocation_failure || exact == StopReason::allocation_failure)
            cd::saturating_add(d.ledger.counters.allocation_failures, 1);
          if (stop == ResidualStopReason::counter_overflow) d.fail(stop);
          break;
        }
        ++d.ledger.counters.committed_transitions;
        if (d.terminal()) { stop = d.terminal_reason(); break; }
      } catch (const rd::Limited& error) {
        stop = error.reason; d.ledger.depth(d.depth());
        if (stop == ResidualStopReason::counter_overflow) d.fail(stop);
        break;
      } catch (const std::bad_alloc&) {
        stop = ResidualStopReason::allocation_failure; d.ledger.depth(d.depth());
        cd::saturating_add(d.ledger.counters.allocation_failures, 1); break;
      } catch (...) { stop = ResidualStopReason::internal_failure; d.fail(stop); break; }
    }
  }
  d.last_stop = stop; d.exact_stop = exact;
  return answer(stop, exact);
}
// Report original bounds only; prefix exact diagnostics never raise lower.
// A completed trace and a checked tree are separate publication milestones.
ResidualProgress ResidualSearch::progress() const noexcept {
  ResidualProgress p;
  if (!data_) { p.phase = ResidualPhase::moved_from; p.last_stop = ResidualStopReason::moved_from; p.result = ResidualResult::failed; return p; }
  const auto& d = *data_;
  p.phase = d.phase(); p.last_stop = d.last_stop; p.exact_stop = d.exact_stop;
  p.heights.lower = d.binding->query.atoms.empty() ? 0 : 1;
  p.trace_complete = d.trace_was_complete; p.trace_verified = static_cast<bool>(d.trace_data);
  p.proof_status = d.trace_data ? ResidualProofStatus::trace_verified : ResidualProofStatus::none;
  if (d.candidate_data) {
    p.heights.upper = d.candidate_data->checked ? d.candidate_data->checked->height : d.candidate_data->exact_upper->height();
    p.proof_status = ResidualProofStatus::checked_upper_only;
  }
  if (d.stage == Impl::Stage::complete) {
    if (d.exact_optimum) {
      p.result = ResidualResult::verified_optimum; p.proof_status = ResidualProofStatus::exact_original_verified;
      p.heights.lower = d.exact_optimum->height(); p.heights.lower_evidence = BoundEvidence::independently_checked;
    } else if (d.exact_infeasibility) {
      p.result = ResidualResult::verified_infeasible; p.proof_status = ResidualProofStatus::exact_original_verified;
      p.heights = {{}, {}, BoundEvidence::independently_checked, true};
    } else p.result = ResidualResult::checked_candidate;
  } else if (d.stage == Impl::Stage::failed) p.result = ResidualResult::failed;
  p.work = d.ledger.counters; p.statistics = d.statistics();
  p.records = d.construction->records; p.cells = d.construction->cells; p.limit_revision = d.revision;
  p.exact_scope_original = d.original_scope; p.exact_progress = d.exact_progress();
  return p;
}
ResidualOptions ResidualSearch::options() const {
  if (!data_) throw Error("invalid_residual_handle", "residual search was moved from");
  return data_->options;
}
const Catalog& ResidualSearch::catalog() const {
  if (!data_) throw Error("invalid_residual_handle", "residual search was moved from");
  return data_->binding->catalog;
}
const Query& ResidualSearch::query() const {
  if (!data_) throw Error("invalid_residual_handle", "residual search was moved from");
  return data_->binding->query;
}
std::optional<ResidualTrace> ResidualSearch::trace() const noexcept {
  if (!data_ || !data_->trace_data) return {};
  return rd::ArtifactFactory::trace(data_->trace_data);
}
std::optional<ResidualCandidate> ResidualSearch::candidate() const noexcept {
  if (!data_ || !data_->candidate_data) return {};
  return rd::ArtifactFactory::candidate(data_->candidate_data);
}
std::optional<VerifiedOptimum> ResidualSearch::exact_original() const noexcept {
  if (!data_ || data_->stage != Impl::Stage::complete) return {};
  return data_->exact_optimum;
}
std::optional<VerifiedInfeasible> ResidualSearch::infeasibility() const noexcept {
  if (!data_ || data_->stage != Impl::Stage::complete) return {};
  return data_->exact_infeasibility;
}
LimitChange ResidualSearch::raise_limits(ResidualLimits value) noexcept {
  if (!data_ || data_->terminal()) return LimitChange::terminal;
  if (!cd::valid_ceiling(value.residual) || !cd::valid_ceiling(value.exact.producer) || !cd::valid_ceiling(value.exact.replay)) return LimitChange::invalid;
  auto& d = *data_; const auto& old = d.options.limits;
  if (!cd::monotone_phase(old.residual, value.residual) || !cd::monotone_ceiling(old.logical_depth, value.logical_depth) ||
      !cd::monotone_ceiling(old.record_limit, value.record_limit) || !cd::monotone_ceiling(old.cell_limit, value.cell_limit) ||
      !monotone_exact(old.exact, value.exact)) return LimitChange::not_monotone;
  if (d.ledger.below_consumed(value.residual) || (value.record_limit && d.construction->records > *value.record_limit) ||
      (value.cell_limit && d.construction->cells > *value.cell_limit)) return LimitChange::below_consumed;
  if (d.revision == std::numeric_limits<std::uint64_t>::max()) return LimitChange::invalid;
  if (d.original && !d.original->progress().proof_complete && d.original->progress().result != ResultKind::failed) {
    const auto result = d.original->raise_limits(value.exact);
    if (result != LimitChange::applied && result != LimitChange::terminal) return result;
  } else if (d.reconstruction) {
    const auto result = d.reconstruction->raise_exact_limits(value.exact);
    if (result != LimitChange::applied && result != LimitChange::terminal) return result;
  }
  d.options.limits = value; d.construction->limits = value; d.ledger.limit = value.residual;
  ++d.revision; return LimitChange::applied;
}
// Snapshot worker history before release. Published immutable handles keep
// their data; cleanup may traverse retained state and is outside work grants.
void ResidualSearch::cancel() noexcept {
  if (!data_ || data_->terminal()) return;
  auto& d = *data_;
  if (d.reduction) d.retained_statistics = add(d.retained_statistics, d.reduction->statistics());
  if (d.reconstruction) d.retained_statistics = add(d.retained_statistics, d.reconstruction->statistics());
  d.retained_exact = d.exact_progress();
  if (d.original) { d.original->cancel(); d.retained_exact = d.original->progress(); }
  else if (d.reconstruction) {
    d.retained_exact.phase = SearchPhase::cancelled; d.retained_exact.last_stop = StopReason::cancelled;
    d.retained_exact.producer.current_depth = 0; d.retained_exact.replay.current_depth = 0;
  }
  d.stage = Impl::Stage::cancelled; d.last_stop = ResidualStopReason::cancelled;
  d.reduction.reset(); d.checker.reset(); d.reconstruction.reset(); d.original.reset();
  d.record.reset(); d.checked.reset(); d.exact_optimum.reset(); d.exact_infeasibility.reset();
  d.ledger.depth(0);
}
} // namespace crown::planner
