#include "crown/planner/search.hpp"

#include "crown/api/error.hpp"
#include "continuation_budget.hpp"
#include "continuation_machine.hpp"

#include <limits>
#include <new>
#include <utility>

namespace crown::planner {
namespace cd = continuation_detail;
namespace {
// Require a live artifact owner before borrowing payload; this does not revalidate its proof.
// See docs/planner_continuations.md, lifetime.
template <class T> const T& require_handle(const std::shared_ptr<const T>& value) {
  if (!value) throw Error("invalid_search_handle", "search artifact was moved from");
  return *value;
}
// Freeze the exact supplied model; no normalization or prefix-to-original authority
// conversion happens at admission. See docs/planner_continuations.md, grants.
std::shared_ptr<const cd::BindingData> admit(Catalog catalog, Query query) {
  validate(catalog, query);
  return std::make_shared<const cd::BindingData>(cd::BindingData{
      std::move(catalog), std::move(query), AccountingVersion::continuation_v1});
}
// Validate both phase durations before creating a search owner. See
// docs/planner_continuations.md, resource accounting.
void validate_limits(const ContinuationLimits& limits) {
  if (!cd::valid_ceiling(limits.producer) || !cd::valid_ceiling(limits.replay))
    throw Error("invalid_search_limits", "negative active search time limit");
}
// Admit nonnegative replay time ceilings; zero remains an operational ceiling. See
// docs/planner_continuations.md, resource accounting.
void validate_limits(const ReplayOptions& limits) {
  if (!cd::valid_ceiling(limits.limits))
    throw Error("invalid_search_limits", "negative active replay time limit");
}
// Return static stop text; allocating compatibility messages are assembled by the caller. See
// docs/planner_continuations.md, resource accounting.
std::string_view reason_text(StopReason reason) noexcept {
  switch (reason) {
    case StopReason::total_work: return "cumulative search work limit reached";
    case StopReason::total_time: return "cumulative active search time limit reached";
    case StopReason::depth_limit: return "logical search depth limit reached";
    case StopReason::allocation_failure: return "search allocation failed; continuation retained";
    case StopReason::counter_overflow: return "search work counter exhausted";
    case StopReason::invalid_certificate: return "invalid exact-search certificate";
    case StopReason::internal_failure: return "internal search invariant failed";
    case StopReason::cancelled: return "search cancelled";
    case StopReason::moved_from: return "search owner was moved from";
    default: return "search incomplete";
  }
}
// Check legacy time range before multiplying milliseconds into nanoseconds. See
// docs/planner_continuations.md, resource accounting.
std::optional<std::chrono::nanoseconds> legacy_time(const SearchLimits& limits) {
  if (!limits.time_limit) return {};
  const auto value = limits.time_limit->count();
  constexpr auto maximum = std::numeric_limits<std::int64_t>::max() / 1'000'000;
  if (value < 0 || value > maximum)
    throw Error("invalid_search_limits", "search time limit cannot be represented in nanoseconds");
  return std::chrono::nanoseconds{value * 1'000'000};
}
// Map legacy work/time independently to both phase ledgers; literal_scope_limit belongs to
// the literal oracle. See docs/planner_continuations.md, resource accounting.
ContinuationLimits legacy_limits(const SearchLimits& limits) {
  const PhaseCeiling phase{limits.work_limit, legacy_time(limits)};
  return {phase, phase, limits.recursion_limit};
}

template <class Owner>
// Charge attempted units, preserve retryable allocation/depth stops and keep per-call grants
// separate from cumulative ledgers. See docs/planner_continuations.md, resource accounting.
StopReason run_quantum(Owner& owner, WorkQuantum quantum) noexcept {
  // This path deliberately precedes terminal checks and every clock sample.
  if (quantum.active_time && quantum.active_time->count() < 0)
    return StopReason::invalid_quantum;
  if (quantum.work == 0) return StopReason::quantum_work;
  if (quantum.active_time && quantum.active_time->count() == 0)
    return StopReason::quantum_time;
  if (owner.terminal()) return owner.terminal_reason();
  const auto started = std::chrono::steady_clock::now();
  cd::ActiveMeter meter(owner.ledger());
  std::uint64_t used = 0;
  const auto stop = [&](StopReason reason) noexcept {
    owner.last_stop = reason;
    return reason;
  };
  for (;;) {
    auto& ledger = owner.ledger();
    meter.switch_to(ledger);
    meter.sample();
    if (used >= quantum.work) return stop(StopReason::quantum_work);
    if (quantum.active_time && std::chrono::steady_clock::now() - started >= *quantum.active_time)
      return stop(StopReason::quantum_time);
    const auto ceiling = ledger.check();
    if (ceiling != StopReason::none) {
      if (ceiling == StopReason::counter_overflow) owner.fail(ceiling);
      return stop(ceiling);
    }
    ++ledger.counters.attempted;
    ++used;
    try {
      const auto result = owner.unit();
      ledger.depth(owner.current_depth());
      if (result.event == cd::UnitEvent::depth_blocked) return stop(StopReason::depth_limit);
      ++ledger.counters.committed_transitions;
      if (owner.terminal()) return stop(owner.terminal_reason());
    } catch (const std::bad_alloc&) {
      cd::saturating_add(ledger.counters.allocation_failures, 1);
      ledger.depth(owner.current_depth());
      return stop(StopReason::allocation_failure);
    } catch (...) {
      owner.fail(StopReason::internal_failure);
      return stop(StopReason::internal_failure);
    }
  }
}
}  // namespace

namespace continuation_detail {
// Private wrapping does not perform validation; callers must already hold the matching
// checked authority. See docs/planner_continuations.md, authority.
struct ArtifactFactory {
  static SearchBinding binding(std::shared_ptr<const BindingData> p) noexcept { return SearchBinding(std::move(p)); }
  static ValidatedIncumbent incumbent(std::shared_ptr<const IncumbentData> p) noexcept { return ValidatedIncumbent(std::move(p)); }
  static VerifiedOptimum optimum(std::shared_ptr<const OptimumData> p) noexcept { return VerifiedOptimum(std::move(p)); }
  static VerifiedInfeasible infeasibility(std::shared_ptr<const InfeasibleData> p) noexcept { return VerifiedInfeasible(std::move(p)); }
  static CheckedCertificate checked(std::shared_ptr<const CheckedCertificateData> p) noexcept { return CheckedCertificate(std::move(p)); }
};
}
SearchBinding::SearchBinding(std::shared_ptr<const cd::BindingData> p) noexcept : data_(std::move(p)) {}
bool SearchBinding::valid() const noexcept { return static_cast<bool>(data_); }
const Catalog& SearchBinding::catalog() const { return require_handle(data_).catalog; }
const Query& SearchBinding::query() const { return require_handle(data_).query; }
AccountingVersion SearchBinding::accounting() const { return require_handle(data_).accounting; }
ValidatedIncumbent::ValidatedIncumbent(std::shared_ptr<const cd::IncumbentData> p) noexcept : data_(std::move(p)) {}
bool ValidatedIncumbent::valid() const noexcept { return static_cast<bool>(data_); }
SearchBinding ValidatedIncumbent::binding() const { return cd::ArtifactFactory::binding(require_handle(data_).upper->binding); }
const FreeConnexTree& ValidatedIncumbent::tree() const { return *require_handle(data_).upper->tree; }
std::size_t ValidatedIncumbent::height() const { return require_handle(data_).upper->height; }
VerifiedOptimum::VerifiedOptimum(std::shared_ptr<const cd::OptimumData> p) noexcept : data_(std::move(p)) {}
bool VerifiedOptimum::valid() const noexcept { return static_cast<bool>(data_); }
SearchBinding VerifiedOptimum::binding() const { return cd::ArtifactFactory::binding(require_handle(data_).upper->upper->binding); }
ValidatedIncumbent VerifiedOptimum::upper() const { return cd::ArtifactFactory::incumbent(require_handle(data_).upper); }
std::size_t VerifiedOptimum::height() const { return require_handle(data_).upper->upper->height; }
const HeightCertificate& VerifiedOptimum::certificate() const { return *require_handle(data_).proof; }
VerifiedInfeasible::VerifiedInfeasible(std::shared_ptr<const cd::InfeasibleData> p) noexcept : data_(std::move(p)) {}
bool VerifiedInfeasible::valid() const noexcept { return static_cast<bool>(data_); }
SearchBinding VerifiedInfeasible::binding() const { return cd::ArtifactFactory::binding(require_handle(data_).binding); }
const HeightCertificate& VerifiedInfeasible::certificate() const { return *require_handle(data_).proof; }
CheckedCertificate::CheckedCertificate(std::shared_ptr<const cd::CheckedCertificateData> p) noexcept : data_(std::move(p)) {}
bool CheckedCertificate::valid() const noexcept { return static_cast<bool>(data_); }
SearchBinding CheckedCertificate::binding() const { return cd::ArtifactFactory::binding(require_handle(data_).checked->binding); }
const HeightCertificate& CheckedCertificate::certificate() const { return *require_handle(data_).checked->proof; }
std::optional<VerifiedOptimum> CheckedCertificate::optimum() const {
  const auto& p = require_handle(data_).optimum;
  if (!p) return {};
  return cd::ArtifactFactory::optimum(p);
}
std::optional<VerifiedInfeasible> CheckedCertificate::infeasibility() const {
  const auto& p = require_handle(data_).infeasibility;
  if (!p) return {};
  return cd::ArtifactFactory::infeasibility(p);
}

// Retain worker state and separate upper publication from final independent-proof authority.
// See docs/planner_continuations.md, authority.
struct ExactSearch::Impl {
  // Keep allocation-safe driver stages and withhold prepared final authority until
  // publish_final. See docs/planner_continuations.md, grants.
  enum class Stage {
    producer_shell, producer, witness_shell, witness, validation_shell, validation,
    publish_incumbent, accept_incumbent, replay_shell, replay,
    final_incumbent, final_result, publish_final, complete, failed, cancelled
  };
  std::shared_ptr<const cd::BindingData> input;
  SearchOptions options;
  cd::ResourceLedger producer_ledger;
  cd::ResourceLedger replay_ledger;
  Stage stage = Stage::producer_shell;
  StopReason last_stop = StopReason::none;
  StopReason failure = StopReason::none;
  std::uint64_t revision = 0;
  bool producer_finished = false;
  SearchStatistics retained_statistics;
  std::unique_ptr<cd::ProducerMachine> producer;
  std::unique_ptr<cd::WitnessMachine> witness;
  std::unique_ptr<cd::ValidationMachine> validation;
  std::unique_ptr<cd::ReplayMachine> replay;
  std::shared_ptr<const cd::FrozenCandidate> candidate;
  std::shared_ptr<const FreeConnexTree> tree;
  std::shared_ptr<const cd::CheckedUpper> checked_upper;
  std::shared_ptr<const HeightCertificate> proof;
  std::shared_ptr<const cd::CheckedProof> checked_proof;
  std::shared_ptr<const cd::IncumbentData> incumbent;
  std::shared_ptr<const cd::IncumbentData> final_upper;
  std::shared_ptr<const cd::OptimumData> optimum;
  std::shared_ptr<const cd::InfeasibleData> infeasibility;

  Impl(std::shared_ptr<const cd::BindingData> value, SearchOptions opts)
      : input(std::move(value)), options(opts), producer_ledger(opts.limits.producer), replay_ledger(opts.limits.replay) {}
  bool terminal() const noexcept { return stage == Stage::complete || stage == Stage::failed || stage == Stage::cancelled; }
  StopReason terminal_reason() const noexcept {
    return stage == Stage::complete ? StopReason::complete :
           stage == Stage::cancelled ? StopReason::cancelled : failure;
  }
  bool replay_phase() const noexcept { return stage >= Stage::replay_shell; }
  cd::ResourceLedger& ledger() noexcept { return replay_phase() ? replay_ledger : producer_ledger; }
  // Report active-worker depth only; parked owners remain retained separately. See
  // docs/planner_continuations.md, resource accounting.
  std::size_t current_depth() const noexcept {
    if (stage == Stage::producer && producer) return producer->current_depth();
    if (stage == Stage::witness && witness) return witness->current_depth();
    if (stage == Stage::validation && validation) return validation->current_depth();
    if (stage == Stage::replay && replay) return replay->current_depth();
    return 0;
  }
  void fail(StopReason reason) noexcept { failure = reason; stage = Stage::failed; }
  cd::UnitResult unit() {
    const cd::UnitContext context{options.limits.logical_depth};
    switch (stage) {
      // Prepare the producer before installing its stage. See docs/planner_continuations.md,
      // grants.
      case Stage::producer_shell: {
        auto next = std::make_unique<cd::ProducerMachine>(input);
        producer = std::move(next); stage = Stage::producer; break;
      }
      // Delegate one producer unit and receive candidate or completed certificate. See
      // docs/planner_continuations.md, grants.
      case Stage::producer: {
        const auto result = producer->step(context);
        if (result.event == cd::UnitEvent::candidate_ready) {
          candidate = producer->candidate();
          if (!candidate) { fail(StopReason::internal_failure); break; }
          stage = Stage::witness_shell;
        } else if (result.event == cd::UnitEvent::producer_complete) {
          proof = producer->completed_proof();
          if (!proof) { fail(StopReason::internal_failure); break; }
          producer_finished = true;
          stage = Stage::replay_shell;
        }
        return result;
      }
      // Prepare an arena-retaining candidate materializer. See docs/planner_continuations.md,
      // grants.
      case Stage::witness_shell: {
        auto next = std::make_unique<cd::WitnessMachine>(input, candidate);
        witness = std::move(next); stage = Stage::witness; break;
      }
      // Copy one saved candidate-tree action before P02 checking. See
      // docs/planner_continuations.md, grants.
      case Stage::witness: {
        const auto result = witness->step(context);
        if (result.event == cd::UnitEvent::witness_complete) {
          tree = witness->tree();
          if (!tree) { fail(StopReason::internal_failure); break; }
          stage = Stage::validation_shell;
        }
        return result;
      }
      // Prepare the independent P02 validator for the whole candidate. See
      // docs/planner_continuations.md, grants.
      case Stage::validation_shell: {
        auto next = std::make_unique<cd::ValidationMachine>(input, tree);
        validation = std::move(next); stage = Stage::validation; break;
      }
      // Drive independent upper checking before incumbent preparation. See
      // docs/planner_continuations.md, grants.
      case Stage::validation: {
        const auto result = validation->step(context);
        if (result.event == cd::UnitEvent::upper_invalid) fail(StopReason::internal_failure);
        else if (result.event == cd::UnitEvent::upper_valid) {
          checked_upper = validation->checked();
          if (!checked_upper) { fail(StopReason::internal_failure); break; }
          stage = Stage::publish_incumbent;
        }
        return result;
      }
      // Prepare complete owning upper publication before acknowledging the producer. See
      // docs/planner_continuations.md, grants.
      case Stage::publish_incumbent: {
        auto next = std::make_shared<const cd::IncumbentData>(cd::IncumbentData{checked_upper});
        incumbent = std::move(next); stage = Stage::accept_incumbent; break;
      }
      // Complete the producer handshake only after incumbent ownership is ready. See
      // docs/planner_continuations.md, grants.
      case Stage::accept_incumbent:
        producer->accept_upper(checked_upper);
        producer->acknowledge_candidate();
        candidate.reset(); stage = Stage::producer; break;
      // Prepare independent whole-certificate replay after producer completion. See
      // docs/planner_continuations.md, grants.
      case Stage::replay_shell: {
        auto next = std::make_unique<cd::ReplayMachine>(input, proof);
        replay = std::move(next); stage = Stage::replay; break;
      }
      // Drive one saved independent lower-proof action. See docs/planner_continuations.md,
      // grants.
      case Stage::replay: {
        const auto result = replay->step(context);
        if (result.event == cd::UnitEvent::proof_invalid) fail(StopReason::internal_failure);
        else if (result.event == cd::UnitEvent::proof_valid) {
          checked_proof = replay->checked();
          if (!checked_proof) { fail(StopReason::internal_failure); break; }
          stage = Stage::final_incumbent;
        }
        return result;
      }
      // Prepare the final independently replayed upper wrapper when finite. See
      // docs/planner_continuations.md, grants.
      case Stage::final_incumbent:
        if (checked_proof->upper) {
          auto next = std::make_shared<const cd::IncumbentData>(cd::IncumbentData{checked_proof->upper});
          final_upper = std::move(next);
        }
        stage = Stage::final_result; break;
      // Prepare finite optimum or infeasibility data for the admitted model. See
      // docs/planner_continuations.md, grants.
      case Stage::final_result:
        if (final_upper) {
          auto next = std::make_shared<const cd::OptimumData>(cd::OptimumData{final_upper, proof});
          optimum = std::move(next);
        } else {
          auto next = std::make_shared<const cd::InfeasibleData>(cd::InfeasibleData{input, proof});
          infeasibility = std::move(next);
        }
        stage = Stage::publish_final; break;
      // Commit completed exact authority after every required owner exists. See
      // docs/planner_continuations.md, grants.
      case Stage::publish_final:
        if (final_upper) incumbent = final_upper;
        stage = Stage::complete; break;
      case Stage::complete: case Stage::failed: case Stage::cancelled: break;
    }
    return {};
  }
  SearchPhase phase() const noexcept {
    switch (stage) {
      case Stage::producer_shell: return SearchPhase::admitted;
      case Stage::producer: return producer->phase();
      case Stage::witness_shell: case Stage::witness: return SearchPhase::build_incumbent;
      case Stage::validation_shell: case Stage::validation:
      case Stage::publish_incumbent: case Stage::accept_incumbent: return SearchPhase::validate_incumbent;
      case Stage::complete: return SearchPhase::complete;
      case Stage::failed: return SearchPhase::failed;
      case Stage::cancelled: return SearchPhase::cancelled;
      default: return SearchPhase::replay;
    }
  }
};
ExactSearch::ExactSearch(std::unique_ptr<Impl> p) noexcept : data_(std::move(p)) {}
// Release retained workers and payloads; separately retained immutable artifacts survive. See
// docs/planner_continuations.md, lifetime.
ExactSearch::~ExactSearch() = default;
ExactSearch::ExactSearch(ExactSearch&&) noexcept = default;
// Move assignment can destroy the previous destination session; its cost follows retained
// state. See docs/planner_continuations.md, lifetime.
ExactSearch& ExactSearch::operator=(ExactSearch&&) noexcept = default;
// Admit the exact supplied query after validating options; physical normalization and
// original-prefix scope remain separate. See docs/planner_continuations.md, grants.
ExactSearch ExactSearch::create(Catalog catalog, Query query, SearchOptions options) {
  validate_limits(options.limits);
  if (options.policy != SearchPolicy::strict && options.policy != SearchPolicy::best_found)
    throw Error("invalid_search_policy", "unknown exact-search policy");
  auto input = admit(std::move(catalog), std::move(query));
  return ExactSearch(std::make_unique<Impl>(std::move(input), options));
}
// Advance only saved work; moved-from detection precedes quantum validation and snapshots
// allocate no evidence. See docs/planner_continuations.md, resource accounting.
SearchAdvance ExactSearch::advance(WorkQuantum quantum) noexcept {
  if (!data_) return {StopReason::moved_from, progress()};
  const auto stopped = run_quantum(*data_, quantum);
  return {stopped, progress()};
}
// Report universal versus complete lower evidence explicitly; moved-from has no model-bound
// lower and strict may show scalar upper. See docs/planner_continuations.md, authority.
SearchProgress ExactSearch::progress() const noexcept {
  SearchProgress report;
  if (!data_) { report.phase = SearchPhase::moved_from; report.last_stop = StopReason::moved_from; report.result = ResultKind::failed; return report; }
  const auto& p = *data_;
  report.phase = p.phase(); report.last_stop = p.last_stop;
  report.heights.lower = p.input->query.atoms.empty() ? 0 : 1;
  if (p.incumbent) report.heights.upper = p.incumbent->upper->height;
  if (p.stage == Impl::Stage::complete) {
    report.proof_complete = true;
    if (p.optimum) {
      report.result = ResultKind::verified_optimum;
      report.heights.lower = p.optimum->upper->upper->height;
      report.heights.lower_evidence = BoundEvidence::independently_checked;
    } else {
      report.result = ResultKind::verified_infeasible;
      report.heights = {{}, {}, BoundEvidence::independently_checked, true};
    }
  } else if (p.stage == Impl::Stage::failed) report.result = ResultKind::failed;
  report.producer_complete = p.producer_finished;
  report.producer = p.producer_ledger.counters; report.replay = p.replay_ledger.counters;
  report.structural = p.producer ? p.producer->statistics() : p.retained_statistics;
  report.structural.work = report.producer.attempted;
  report.structural.certificate_work = report.replay.attempted;
  report.limit_revision = p.revision;
  return report;
}
SearchBinding ExactSearch::binding() const {
  if (!data_) throw Error("invalid_search_handle", "exact-search owner was moved from");
  return cd::ArtifactFactory::binding(data_->input);
}
SearchPolicy ExactSearch::policy() const {
  if (!data_) throw Error("invalid_search_handle", "exact-search owner was moved from");
  return data_->options.policy;
}
ContinuationLimits ExactSearch::limits() const {
  if (!data_) throw Error("invalid_search_handle", "exact-search owner was moved from");
  return data_->options.limits;
}
// Expose best_found checked uppers across pauses/failure/cancellation; strict always
// withholds this handle. See docs/planner_continuations.md, authority.
std::optional<ValidatedIncumbent> ExactSearch::incumbent() const noexcept {
  if (!data_ || data_->options.policy != SearchPolicy::best_found || !data_->incumbent) return {};
  return cd::ArtifactFactory::incumbent(data_->incumbent);
}
// Expose optimum only after final publication and only for this exact query scope. See
// docs/planner_continuations.md, authority.
std::optional<VerifiedOptimum> ExactSearch::optimum() const noexcept {
  if (!data_ || data_->stage != Impl::Stage::complete || !data_->optimum) return {};
  return cd::ArtifactFactory::optimum(data_->optimum);
}
// Expose no-tree authority only at complete publication, never from a resource stop or absent
// upper. See docs/planner_continuations.md, authority.
std::optional<VerifiedInfeasible> ExactSearch::infeasibility() const noexcept {
  if (!data_ || data_->stage != Impl::Stage::complete || !data_->infeasibility) return {};
  return cd::ArtifactFactory::infeasibility(data_->infeasibility);
}
// Apply only monotone ceilings above consumed values; accepted equality still advances
// revision and never resets work. See docs/planner_continuations.md, resource accounting.
LimitChange ExactSearch::raise_limits(ContinuationLimits value) noexcept {
  if (!data_ || data_->terminal()) return LimitChange::terminal;
  if (!cd::valid_ceiling(value.producer) || !cd::valid_ceiling(value.replay)) return LimitChange::invalid;
  const auto& old = data_->options.limits;
  if (!cd::monotone_phase(old.producer, value.producer) || !cd::monotone_phase(old.replay, value.replay) ||
      !cd::monotone_ceiling(old.logical_depth, value.logical_depth)) return LimitChange::not_monotone;
  if (data_->producer_ledger.below_consumed(value.producer) || data_->replay_ledger.below_consumed(value.replay)) return LimitChange::below_consumed;
  if (data_->revision == std::numeric_limits<std::uint64_t>::max()) return LimitChange::invalid;
  data_->options.limits = value; data_->producer_ledger.limit = value.producer; data_->replay_ledger.limit = value.replay;
  ++data_->revision;
  return LimitChange::applied;
}
// Cancel only nonterminal work; preserve incumbent/input/counters, and leave already terminal
// owners unchanged. See docs/planner_continuations.md, lifetime.
void ExactSearch::cancel() noexcept {
  if (!data_ || data_->terminal()) return;
  if (data_->producer) data_->retained_statistics = data_->producer->statistics();
  data_->stage = Impl::Stage::cancelled; data_->last_stop = StopReason::cancelled;
  data_->producer.reset(); data_->witness.reset(); data_->validation.reset(); data_->replay.reset();
  data_->candidate.reset(); data_->tree.reset(); data_->checked_upper.reset(); data_->proof.reset();
  data_->checked_proof.reset(); data_->final_upper.reset();
  data_->optimum.reset(); data_->infeasibility.reset();
  data_->producer_ledger.depth(0); data_->replay_ledger.depth(0);
}

// Retain checking separately from final artifact preparation; checked() stays empty until
// publish. See docs/planner_continuations.md, authority.
struct CertificateReplay::Impl {
  enum class Stage { shell, replay, upper, result, artifact, publish, complete, failed, cancelled };
  std::shared_ptr<const cd::BindingData> input;
  std::shared_ptr<const HeightCertificate> proof;
  ReplayOptions options;
  cd::ResourceLedger resource;
  Stage stage = Stage::shell;
  StopReason last_stop = StopReason::none;
  StopReason failure = StopReason::none;
  std::uint64_t revision = 0;
  std::size_t retained_checked_claims = 0;
  std::unique_ptr<cd::ReplayMachine> replay;
  std::shared_ptr<const cd::CheckedProof> checked_proof;
  std::shared_ptr<const cd::IncumbentData> upper;
  std::shared_ptr<const cd::OptimumData> optimum;
  std::shared_ptr<const cd::InfeasibleData> infeasibility;
  std::shared_ptr<const cd::CheckedCertificateData> prepared;
  std::shared_ptr<const cd::CheckedCertificateData> published;
  Impl(std::shared_ptr<const cd::BindingData> value, std::shared_ptr<const HeightCertificate> claim, ReplayOptions opts)
      : input(std::move(value)), proof(std::move(claim)), options(opts), resource(opts.limits) {}
  bool terminal() const noexcept { return stage == Stage::complete || stage == Stage::failed || stage == Stage::cancelled; }
  StopReason terminal_reason() const noexcept { return stage == Stage::complete ? StopReason::complete : stage == Stage::cancelled ? StopReason::cancelled : failure; }
  cd::ResourceLedger& ledger() noexcept { return resource; }
  // Report active checker depth; post-check owner preparation is depth zero while evidence
  // remains retained. See docs/planner_continuations.md, resource accounting.
  std::size_t current_depth() const noexcept { return stage == Stage::replay && replay ? replay->current_depth() : 0; }
  void fail(StopReason reason) noexcept { failure = reason; stage = Stage::failed; }
  cd::UnitResult unit() {
    switch (stage) {
      // Prepare independent claim-checking worker. See docs/planner_continuations.md, grants.
      case Stage::shell: {
        auto next = std::make_unique<cd::ReplayMachine>(input, proof);
        replay = std::move(next); stage = Stage::replay; break;
      }
      // Drive a saved independent certificate-check action. See
      // docs/planner_continuations.md, grants.
      case Stage::replay: {
        const auto result = replay->step(cd::UnitContext{options.logical_depth});
        if (result.event == cd::UnitEvent::proof_invalid) fail(StopReason::invalid_certificate);
        else if (result.event == cd::UnitEvent::proof_valid) {
          checked_proof = replay->checked();
          if (!checked_proof) { fail(StopReason::internal_failure); break; }
          stage = Stage::upper;
        }
        return result;
      }
      // Prepare finite checked-upper owner when present. See docs/planner_continuations.md,
      // grants.
      case Stage::upper:
        if (checked_proof->upper) {
          auto next = std::make_shared<const cd::IncumbentData>(cd::IncumbentData{checked_proof->upper});
          upper = std::move(next);
        }
        stage = Stage::result; break;
      // Prepare the typed optimum or empty-family result. See docs/planner_continuations.md,
      // grants.
      case Stage::result:
        if (upper) {
          auto next = std::make_shared<const cd::OptimumData>(cd::OptimumData{upper, proof}); optimum = std::move(next);
        } else {
          auto next = std::make_shared<const cd::InfeasibleData>(cd::InfeasibleData{input, proof}); infeasibility = std::move(next);
        }
        stage = Stage::artifact; break;
      // Prepare the complete replay artifact control block. See
      // docs/planner_continuations.md, grants.
      case Stage::artifact: {
        auto next = std::make_shared<const cd::CheckedCertificateData>(cd::CheckedCertificateData{checked_proof, optimum, infeasibility});
        prepared = std::move(next); stage = Stage::publish; break;
      }
      // Commit fully prepared independent replay authority. See
      // docs/planner_continuations.md, grants.
      case Stage::publish: published = std::move(prepared); stage = Stage::complete; break;
      case Stage::complete: case Stage::failed: case Stage::cancelled: break;
    }
    return {};
  }
};
CertificateReplay::CertificateReplay(std::unique_ptr<Impl> p) noexcept : data_(std::move(p)) {}
// Release unfinished replay while externally retained checked artifacts survive. See
// docs/planner_continuations.md, lifetime.
CertificateReplay::~CertificateReplay() = default;
CertificateReplay::CertificateReplay(CertificateReplay&&) noexcept = default;
// Move assignment may tear down the complete previous destination replay. See
// docs/planner_continuations.md, lifetime.
CertificateReplay& CertificateReplay::operator=(CertificateReplay&&) noexcept = default;
// Own the supplied claim and exact model; structural checking waits for advance and
// serialized binding belongs to IO. See docs/planner_continuations.md, grants.
CertificateReplay CertificateReplay::create(Catalog catalog, Query query, HeightCertificate proof, ReplayOptions options) {
  validate_limits(options);
  auto input = admit(std::move(catalog), std::move(query));
  auto claim = std::make_shared<const HeightCertificate>(std::move(proof));
  return CertificateReplay(std::make_unique<Impl>(std::move(input), std::move(claim), options));
}
// Advance retained replay only; moved-from detection precedes quantum handling. See
// docs/planner_continuations.md, resource accounting.
ReplayAdvance CertificateReplay::advance(WorkQuantum quantum) noexcept {
  if (!data_) return {StopReason::moved_from, progress()};
  const auto stopped = run_quantum(*data_, quantum);
  return {stopped, progress()};
}
// Keep checked-prefix progress separate from final valid artifact; failed may be complete but
// invalid. See docs/planner_continuations.md, authority.
ReplayProgress CertificateReplay::progress() const noexcept {
  ReplayProgress report;
  if (!data_) { report.phase = ReplayPhase::moved_from; report.last_stop = StopReason::moved_from; return report; }
  const auto& p = *data_;
  report.last_stop = p.last_stop; report.work = p.resource.counters; report.limit_revision = p.revision;
  report.checked_claims = p.replay ? p.replay->checked_claims() : p.retained_checked_claims;
  if (p.stage == Impl::Stage::complete) { report.phase = ReplayPhase::complete; report.complete = true; report.valid = true; }
  else if (p.stage == Impl::Stage::failed) { report.phase = ReplayPhase::failed; report.complete = true; }
  else if (p.stage == Impl::Stage::cancelled) report.phase = ReplayPhase::cancelled;
  else if (p.stage == Impl::Stage::shell) report.phase = ReplayPhase::admitted;
  else if (p.stage == Impl::Stage::replay) report.phase = p.replay->phase();
  else report.phase = ReplayPhase::match_root;
  return report;
}
SearchBinding CertificateReplay::binding() const {
  if (!data_) throw Error("invalid_search_handle", "certificate-replay owner was moved from");
  return cd::ArtifactFactory::binding(data_->input);
}
// Expose only the fully published artifact, not a successful checker prefix or private
// prepared result. See docs/planner_continuations.md, authority.
std::optional<CheckedCertificate> CertificateReplay::checked() const noexcept {
  if (!data_ || !data_->published) return {};
  return cd::ArtifactFactory::checked(data_->published);
}
ReplayOptions CertificateReplay::limits() const {
  if (!data_) throw Error("invalid_search_handle", "certificate-replay owner was moved from");
  return data_->options;
}
// Raise only monotone ceilings above consumption without replacing the claim or resetting
// counters. See docs/planner_continuations.md, resource accounting.
LimitChange CertificateReplay::raise_limits(ReplayOptions value) noexcept {
  if (!data_ || data_->terminal()) return LimitChange::terminal;
  if (!cd::valid_ceiling(value.limits)) return LimitChange::invalid;
  if (!cd::monotone_phase(data_->options.limits, value.limits) ||
      !cd::monotone_ceiling(data_->options.logical_depth, value.logical_depth)) return LimitChange::not_monotone;
  if (data_->resource.below_consumed(value.limits)) return LimitChange::below_consumed;
  if (data_->revision == std::numeric_limits<std::uint64_t>::max()) return LimitChange::invalid;
  data_->options = value; data_->resource.limit = value.limits; ++data_->revision;
  return LimitChange::applied;
}
// Cancel nonterminal replay and retain diagnostics; already terminal owners remain unchanged.
// See docs/planner_continuations.md, lifetime.
void CertificateReplay::cancel() noexcept {
  if (!data_ || data_->terminal()) return;
  if (data_->replay) data_->retained_checked_claims = data_->replay->checked_claims();
  data_->stage = Impl::Stage::cancelled; data_->last_stop = StopReason::cancelled;
  data_->replay.reset(); data_->proof.reset(); data_->checked_proof.reset(); data_->upper.reset();
  data_->optimum.reset(); data_->infeasibility.reset(); data_->prepared.reset();
  data_->resource.depth(0);
}

// Keep the owner alive while borrowing its final proof for allocating strict export; resource
// stops expose no partial certificate. See docs/planner_continuations.md, authority.
OracleResult minimum_tree(const Catalog& catalog, const Query& query, const SearchLimits& limits) {
  auto owner = ExactSearch::create(catalog, query, SearchOptions{SearchPolicy::strict, legacy_limits(limits)});
  SearchAdvance advanced;
  do { advanced = owner.advance(WorkQuantum{4096, {}}); }
  while (advanced.stopped_for == StopReason::quantum_work || advanced.stopped_for == StopReason::quantum_time);
  OracleResult result;
  result.algorithm = "crown_partition_exact_v2"; result.limits = limits;
  result.statistics = owner.progress().structural;
  const HeightCertificate* proof = nullptr;
  if (const auto optimum = owner.optimum()) proof = &optimum->certificate();
  if (const auto infeasible = owner.infeasibility()) proof = &infeasible->certificate();
  if (proof) {
    // Allocating compatibility conversion is assembled privately before return.
    result.minimum_height = proof->minimum_height; result.tree = proof->tree; result.lower_bounds = proof->lower_bounds;
    result.certificate_verified = true;
    result.status = proof->tree ? OracleStatus::proven_minimum : OracleStatus::unsupported;
    result.reason = proof->tree ? "minimum height and upper witness independently checked" : "no admissible CROWN tree exists for this body/head";
  } else {
    if (advanced.stopped_for == StopReason::internal_failure)
      throw Error("invalid_search_invariant", "exact continuation or its independent proof failed");
    result.status = OracleStatus::resource_limit;
    if (owner.progress().producer_complete) result.reason = "certificate replay: ";
    result.reason += reason_text(advanced.stopped_for);
  }
  return result;
}
// Summarize independent replay without exposing partial authority; finite and no-tree success
// need distinct diagnostic wording. See docs/planner_continuations.md, authority.
CertificateReport verify_height_certificate(const Catalog& catalog, const Query& query,
                                            const HeightCertificate& proof, const SearchLimits& limits) {
  const auto mapped = legacy_limits(limits);
  auto owner = CertificateReplay::create(catalog, query, proof, ReplayOptions{mapped.replay, mapped.logical_depth});
  ReplayAdvance advanced;
  do { advanced = owner.advance(WorkQuantum{4096, {}}); }
  while (advanced.stopped_for == StopReason::quantum_work || advanced.stopped_for == StopReason::quantum_time);
  CertificateReport result;
  result.work = owner.progress().work.attempted;
  const auto checked = owner.checked();
  result.valid = checked.has_value();
  result.resource_limit = advanced.stopped_for == StopReason::total_work || advanced.stopped_for == StopReason::total_time ||
      advanced.stopped_for == StopReason::depth_limit || advanced.stopped_for == StopReason::allocation_failure ||
      advanced.stopped_for == StopReason::counter_overflow;
  result.message = result.valid
      ? (checked->certificate().tree ? "upper tree and independent lower bound verified"
                                    : "empty admissible family independently verified")
      : reason_text(advanced.stopped_for);
  return result;
}
}  // namespace crown::planner
