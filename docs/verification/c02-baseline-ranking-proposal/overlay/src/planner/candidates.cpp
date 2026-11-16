#include "crown/planner/candidates.hpp"
#include "candidate_machine.hpp"
#include "candidate_key.hpp"
#include "candidate_binding.hpp"
#include "continuation_budget.hpp"
#include "crown/api/error.hpp"

#include <algorithm>
#include <climits>
#include <list>
#include <limits>
#include <new>
#include <set>
#include <string_view>
#include <utility>
#include <vector>

namespace crown::planner {
namespace cd = continuation_detail;
namespace cand = candidate_detail;
namespace {
// Admission serialization, snapshots and cache operations are explicit allocating
// work outside advance(). Keep complete binding bytes: a digest or an alpha-
// equivalent binding is not authority to reuse an original-query certificate.
constexpr auto maximum = std::numeric_limits<std::uint64_t>::max();
struct Stopped { CandidateStop reason; };
void room(std::uint64_t value) {
  if (value == maximum) throw Stopped{CandidateStop::counter_overflow};
}
template<class T> const T& require(const std::shared_ptr<const T>& p) {
  if (!p) throw Error("invalid_candidate_handle", "candidate artifact was moved from");
  return *p;
}
void context_valid(const CandidateContext& c) {
  if (c.updates != CandidateUpdateProfile::mixed_full_row_set_v1 ||
      c.arithmetic != "exact-nonnull-v1" || c.planner != "crown-tree-v1" ||
      c.optimization != "structural-height-v1" || c.cost_model != "no-cost-v1" ||
      c.canonicalization != "structural-tree-key-v1")
    throw Error("invalid_candidate_context", "unsupported candidate context/version");
}
bool same_context(const CandidateContext& a, const CandidateContext& b) noexcept {
  return a.updates == b.updates && a.arithmetic == b.arithmetic && a.planner == b.planner &&
      a.optimization == b.optimization && a.cost_model == b.cost_model &&
      a.canonicalization == b.canonicalization;
}
std::string binding_bytes(const Catalog& catalog, const Query& query) {
  return binding_detail::encode(catalog,query);
}
CandidateStop translate(cand::GeneratorStop reason) noexcept {
  switch (reason) {
    case cand::GeneratorStop::depth_limit: return CandidateStop::depth_limit;
    case cand::GeneratorStop::record_limit: return CandidateStop::record_limit;
    case cand::GeneratorStop::cell_limit: return CandidateStop::cell_limit;
    case cand::GeneratorStop::counter_overflow: return CandidateStop::counter_overflow;
    case cand::GeneratorStop::none: return CandidateStop::internal_failure;
  }
  return CandidateStop::internal_failure;
}
CandidateStop translate(cand::KeyStop reason) noexcept {
  switch (reason) {
    case cand::KeyStop::depth_limit: return CandidateStop::depth_limit;
    case cand::KeyStop::record_limit: return CandidateStop::record_limit;
    case cand::KeyStop::cell_limit: return CandidateStop::cell_limit;
    case cand::KeyStop::counter_overflow: return CandidateStop::counter_overflow;
    default: return CandidateStop::internal_failure;
  }
}
CandidateStop translate(StopReason reason) noexcept {
  switch (reason) {
    case StopReason::total_work: return CandidateStop::total_work;
    case StopReason::total_time: return CandidateStop::total_time;
    case StopReason::counter_overflow: return CandidateStop::counter_overflow;
    default: return CandidateStop::internal_failure;
  }
}
}  // namespace

namespace candidate_detail {
// No live facade, seed holder or SnapshotData is reachable from InputData.
struct InputData {
  VerifiedOptimum proof;
  CandidateContext context;
  std::shared_ptr<const cd::BindingData> binding;
  std::string binding_bytes;
  std::size_t height;
};
struct CandidateData {
  std::shared_ptr<const InputData> input;
  std::shared_ptr<const cd::CheckedUpper> upper;
  std::shared_ptr<const std::string> key;
  CandidateProvenance provenance;
};
enum class ReuseOutcome { pending, published, duplicate, rejected, taller };
struct ReuseEvent {
  std::size_t prefix_index;
  CandidateProvenance generation;
  ReuseOutcome outcome = ReuseOutcome::pending;
};
struct SnapshotData {
  std::shared_ptr<const InputData> input;
  std::vector<MinimumHeightCandidate> candidates;
  std::vector<ReuseEvent> reuse;
  bool exhausted = false;
};
struct Factory {
  static MinimumHeightCandidate candidate(std::shared_ptr<const CandidateData> p) noexcept {
    return MinimumHeightCandidate(std::move(p));
  }
  static CandidateSnapshot snapshot(std::shared_ptr<const SnapshotData> p) noexcept {
    return CandidateSnapshot(std::move(p));
  }
  static const SnapshotData& snapshot_data(const CandidateSnapshot& s) { return require(s.data_); }
  static std::shared_ptr<const FreeConnexTree> tree(const MinimumHeightCandidate& c) {
    return require(c.data_).upper->tree;
  }
};
}  // namespace candidate_detail

MinimumHeightCandidate::MinimumHeightCandidate(
    std::shared_ptr<const cand::CandidateData> p) noexcept : data_(std::move(p)) {}
bool MinimumHeightCandidate::valid() const noexcept { return bool(data_); }
const Catalog& MinimumHeightCandidate::catalog() const { return require(data_).input->binding->catalog; }
const Query& MinimumHeightCandidate::query() const { return require(data_).input->binding->query; }
const FreeConnexTree& MinimumHeightCandidate::tree() const { return *require(data_).upper->tree; }
std::size_t MinimumHeightCandidate::height() const { return require(data_).upper->height; }
const std::string& MinimumHeightCandidate::structural_key() const { return *require(data_).key; }
const CandidateContext& MinimumHeightCandidate::context() const { return require(data_).input->context; }
CandidateProvenance MinimumHeightCandidate::provenance() const { return require(data_).provenance; }
VerifiedOptimum MinimumHeightCandidate::original_proof() const { return require(data_).input->proof; }
CandidateSnapshot::CandidateSnapshot(
    std::shared_ptr<const cand::SnapshotData> p) noexcept : data_(std::move(p)) {}
bool CandidateSnapshot::valid() const noexcept { return bool(data_); }
std::size_t CandidateSnapshot::candidate_count() const { return require(data_).candidates.size(); }
std::optional<MinimumHeightCandidate> CandidateSnapshot::candidate(std::size_t i) const {
  const auto& d = require(data_);
  if (i >= d.candidates.size()) return {};
  return d.candidates[i];
}
bool CandidateSnapshot::family_exhausted() const { return require(data_).exhausted; }
CandidateFamily CandidateSnapshot::family() const {
  (void)require(data_); return CandidateFamily::exact_seed_residual_seed_normal_form_v1;
}
const CandidateContext& CandidateSnapshot::context() const { return require(data_).input->context; }
VerifiedOptimum CandidateSnapshot::original_proof() const { return require(data_).input->proof; }

// One unit dispatches one saved stage or delegated worker step. Full-key set
// comparisons, vector relocation, allocation and cleanup have variable physical
// cost within a unit and count toward active time, without a hard time bound.
//
// Shared logical charges include worker shells (one record), reuse entries (one
// record/cell), immutable candidate payloads (one record), and publication (one
// record/two cells). Discarded construction remains charged. Admission copies,
// P02 scratch/reports, container capacity, allocator metadata, scalar widths,
// caller-retained history, snapshots and cache storage are separate costs.
struct CandidateProvider::Impl {
  enum class Stage {
    exact, residual, cache, generator_shell, generate, proposed,
    validator_shell, validate, height, key_shell, key, dedup,
    reserve, payload, publish, release, complete, failed, cancelled
  };
  enum class Origin { exact, residual, cache, generated };
  struct KeyLess {
    bool operator()(const std::shared_ptr<const std::string>& a,
                    const std::shared_ptr<const std::string>& b) const noexcept {
      return *a < *b;
    }
  };
  std::shared_ptr<const cand::InputData> input;
  // These holders never become part of InputData or a new candidate payload.
  std::shared_ptr<const ResidualCandidate> residual;
  std::optional<CandidateSnapshot> prefix;
  std::shared_ptr<cand::ContentBudget> budget;
  CandidateLimits limits;
  cd::ResourceLedger ledger;
  Stage stage = Stage::exact;
  Origin origin = Origin::exact;
  CandidateStop last_stop = CandidateStop::none, failure = CandidateStop::none;
  CandidateStatistics stats;
  std::uint64_t revision = 0;
  std::size_t prefix_pos = 0;
  std::vector<MinimumHeightCandidate> published;
  std::set<std::shared_ptr<const std::string>, KeyLess> seen;
  std::vector<cand::ReuseEvent> reuse;
  std::optional<std::size_t> reuse_pos;
  std::unique_ptr<cand::NormalFormGenerator> generator;
  std::unique_ptr<cd::ValidationMachine> validator;
  std::unique_ptr<cand::StructuralKeyMachine> canonicalizer;
  std::shared_ptr<const FreeConnexTree> draft;
  std::shared_ptr<const cd::CheckedUpper> upper;
  std::shared_ptr<const std::string> key;
  std::shared_ptr<const cand::CandidateData> payload;
  CandidateProvenance provenance;
  bool family_complete = false;

  Impl(std::shared_ptr<const cand::InputData> in, CandidateLimits l,
       std::shared_ptr<const ResidualCandidate> r, std::optional<CandidateSnapshot> p)
      : input(std::move(in)), residual(std::move(r)), prefix(std::move(p)),
        budget(std::make_shared<cand::ContentBudget>(cand::ContentLimits{l.records, l.cells})),
        limits(l), ledger(l.enumeration) {}
  bool terminal() const noexcept {
    return stage == Stage::complete || stage == Stage::failed || stage == Stage::cancelled;
  }
  CandidateStop terminal_reason() const noexcept {
    return stage == Stage::complete ? CandidateStop::exhausted :
        stage == Stage::cancelled ? CandidateStop::cancelled : failure;
  }
  void fail(CandidateStop r) noexcept { stage = Stage::failed; failure = r; }
  std::size_t depth() const noexcept {
    if (stage == Stage::validate && validator) return validator->current_depth();
    if (stage == Stage::key && canonicalizer) return canonicalizer->current_depth();
    if (stage == Stage::generate && generator) return generator->current_depth();
    return 0;
  }
  CandidatePhase phase() const noexcept {
    switch (stage) {
      case Stage::exact: return CandidatePhase::exact_seed;
      case Stage::residual: return CandidatePhase::residual_seed;
      case Stage::cache: case Stage::generator_shell: case Stage::generate:
        return CandidatePhase::enumerate;
      case Stage::proposed: case Stage::validator_shell: case Stage::validate: case Stage::height:
        return CandidatePhase::validate;
      case Stage::key_shell: case Stage::key: return CandidatePhase::canonicalize;
      case Stage::dedup: case Stage::reserve: case Stage::payload:
      case Stage::publish: case Stage::release:
        return CandidatePhase::publish;
      case Stage::complete: return CandidatePhase::exhausted;
      case Stage::failed: return CandidatePhase::failed;
      case Stage::cancelled: return CandidatePhase::cancelled;
    }
    return CandidatePhase::failed;
  }
  void outcome(cand::ReuseOutcome o) noexcept {
    if (reuse_pos) reuse[*reuse_pos].outcome = o;
  }
  void discard() noexcept {
    payload.reset(); key.reset(); upper.reset(); draft.reset();
    canonicalizer.reset(); validator.reset(); reuse_pos.reset();
    provenance = {};
  }
  CandidateStop unit() {
    const cd::UnitContext ctx{limits.logical_depth};
    switch (stage) {
      case Stage::exact:
        draft = std::shared_ptr<const FreeConnexTree>(input, &input->proof.upper().tree());
        provenance = {}; origin = Origin::exact; stage = Stage::proposed; break;
      case Stage::residual:
        if (residual) {
          draft = std::shared_ptr<const FreeConnexTree>(residual, &residual->tree());
          provenance = {CandidateSource::residual_seed,
              CandidateFamily::exact_seed_residual_seed_normal_form_v1, stats.proposed,
              residual->origin(), residual->trace()};
          origin = Origin::residual; stage = Stage::proposed;
        } else stage = Stage::cache;
        break;
      case Stage::cache:
        if (prefix && prefix_pos < prefix->candidate_count()) {
          room(stats.cache_seeded);
          if (reuse.size() == reuse.max_size()) throw Stopped{CandidateStop::counter_overflow};
          auto c = *prefix->candidate(prefix_pos);
          auto tree = cand::Factory::tree(c);
          auto generation = c.provenance();
          budget->prepare(1, 1);
          reuse.push_back({prefix_pos, generation, cand::ReuseOutcome::pending});
          budget->commit(1, 1);
          reuse_pos = reuse.size() - 1;
          draft = std::move(tree); provenance = std::move(generation);
          ++stats.cache_seeded; origin = Origin::cache; stage = Stage::proposed;
        } else stage = Stage::generator_shell;
        break;
      case Stage::generator_shell: {
        budget->prepare(1, 0);
        auto next = std::make_unique<cand::NormalFormGenerator>(input->binding, input->height, budget);
        generator = std::move(next); budget->commit(1, 0); stage = Stage::generate; break;
      }
      case Stage::generate: {
        const auto result = generator->step(ctx);
        const auto& gs = generator->statistics();
        stats.topologies = gs.topologies_examined; stats.scope_tuples = gs.drafts_ready;
        if (result.event == cand::GeneratorEvent::stopped) {
          return translate(result.reason);
        }
        if (result.event == cand::GeneratorEvent::exhausted) {
          family_complete = true; stage = Stage::complete; break;
        }
        if (result.event == cand::GeneratorEvent::draft_ready) {
          draft = generator->draft();
          if (!draft) throw Stopped{CandidateStop::internal_failure};
          provenance = {CandidateSource::normal_form,
              CandidateFamily::exact_seed_residual_seed_normal_form_v1, stats.proposed, {}, {}};
          origin = Origin::generated; stage = Stage::proposed;
        }
        break;
      }
      case Stage::proposed:
        room(stats.proposed); ++stats.proposed; stage = Stage::validator_shell; break;
      case Stage::validator_shell: {
        budget->prepare(1, 0);
        auto next = std::make_unique<cd::ValidationMachine>(input->binding, draft);
        validator = std::move(next); budget->commit(1, 0); stage = Stage::validate; break;
      }
      case Stage::validate: {
        const auto result = validator->step(ctx);
        if (result.event == cd::UnitEvent::depth_blocked) {
          return CandidateStop::depth_limit;
        }
        if (result.event == cd::UnitEvent::upper_valid) {
          upper = validator->checked(); stage = Stage::height;
        } else if (result.event == cd::UnitEvent::upper_invalid) {
          // Save the completed invalid check before a possible counter stop.
          stage = Stage::height;
        } else if (result.event != cd::UnitEvent::advanced)
          throw Stopped{CandidateStop::internal_failure};
        break;
      }
      case Stage::height:
        if (!upper) {
          room(stats.rejected); ++stats.rejected; outcome(cand::ReuseOutcome::rejected);
          if (origin != Origin::generated) throw Stopped{CandidateStop::internal_failure};
          stage = Stage::release; break;
        }
        if (upper->binding != input->binding || !upper->tree || !upper->report || !upper->report->valid)
          throw Stopped{CandidateStop::internal_failure};
        if (upper->height < input->height) throw Stopped{CandidateStop::internal_failure};
        if (upper->height > input->height) {
          room(stats.taller); ++stats.taller; outcome(cand::ReuseOutcome::taller);
          stage = Stage::release; break;
        }
        stage = Stage::key_shell; break;
      case Stage::key_shell: {
        budget->prepare(1, 0);
        auto next = std::make_unique<cand::StructuralKeyMachine>(upper->tree, budget);
        canonicalizer = std::move(next); budget->commit(1, 0); stage = Stage::key; break;
      }
      case Stage::key: {
        const auto result = canonicalizer->step(ctx);
        if (result.event == cand::KeyEvent::stopped) {
          return translate(result.reason);
        }
        if (result.event == cand::KeyEvent::key_ready) {
          key = canonicalizer->key();
          if (!key) throw Stopped{CandidateStop::internal_failure};
          stage = Stage::dedup;
        }
        break;
      }
      case Stage::dedup:
        // Ordered-container structural comparisons have explicit variable-width
        // cost. This performs no worker restart or blocking search/drain.
        if (seen.find(key) != seen.end()) {
          room(stats.duplicates); ++stats.duplicates; outcome(cand::ReuseOutcome::duplicate);
          stage = Stage::release;
        } else stage = Stage::reserve;
        break;
      case Stage::reserve:
        if (limits.retained_candidates && published.size() >= *limits.retained_candidates)
          return CandidateStop::candidate_capacity;
        if (published.size() == published.max_size()) throw Stopped{CandidateStop::counter_overflow};
        published.reserve(published.size() + 1); stage = Stage::payload; break;
      case Stage::payload: {
        budget->prepare(1, 0);
        auto next = std::make_shared<const cand::CandidateData>(cand::CandidateData{input, upper, key, provenance});
        payload = std::move(next); budget->commit(1, 0); stage = Stage::publish; break;
      }
      case Stage::publish: {
        room(stats.published);
        if (seen.size() == seen.max_size()) throw Stopped{CandidateStop::counter_overflow};
        budget->prepare(1, 2); // seen record plus seen-key and output-handle cells
        const auto result = seen.insert(key);
        if (!result.second) throw Stopped{CandidateStop::internal_failure};
        // Publication cannot throw after committed seen membership: capacity is
        // reserved and the only element operation is a noexcept handle move.
        published.push_back(cand::Factory::candidate(payload));
        budget->commit(1, 2); ++stats.published;
        outcome(cand::ReuseOutcome::published); stage = Stage::release;
        return CandidateStop::candidate_ready;
      }
      case Stage::release: {
        const auto old = origin;
        discard();
        if (old == Origin::generated) { generator->consume_draft(); stage = Stage::generate; }
        else if (old == Origin::exact) stage = Stage::residual;
        else if (old == Origin::residual) stage = Stage::cache;
        else {
          if (prefix_pos == std::numeric_limits<std::size_t>::max()) throw Stopped{CandidateStop::counter_overflow};
          ++prefix_pos; stage = Stage::cache;
        }
        break;
      }
      case Stage::complete: case Stage::failed: case Stage::cancelled:
        throw Stopped{CandidateStop::internal_failure};
    }
    return CandidateStop::none;
  }
};
CandidateProvider::CandidateProvider(std::unique_ptr<Impl> p) noexcept : data_(std::move(p)) {}
CandidateProvider::~CandidateProvider() = default;
CandidateProvider::CandidateProvider(CandidateProvider&&) noexcept = default;
CandidateProvider& CandidateProvider::operator=(CandidateProvider&&) noexcept = default;
CandidateProvider CandidateProvider::create(VerifiedOptimum proof, CandidateContext context,
    CandidateLimits limits, std::optional<ResidualCandidate> residual, std::optional<CandidateSnapshot> prefix) {
  context_valid(context);
  if (!proof.valid()) throw Error("invalid_candidate_proof", "original verified optimum is required");
  if (!cd::valid_ceiling(limits.enumeration)) throw Error("invalid_candidate_limits", "negative active time limit");
  const auto binding = proof.binding();
  auto bytes = binding_bytes(binding.catalog(), binding.query());
  if (residual && (!residual->valid() || binding_bytes(residual->catalog(), residual->query()) != bytes))
    throw Error("candidate_binding", "residual seed does not have the exact original binding");
  if (prefix) {
    if (!prefix->valid()) throw Error("candidate_binding", "invalid cache prefix");
    const auto& s = cand::Factory::snapshot_data(*prefix);
    if (s.input->binding_bytes != bytes || !same_context(s.input->context, context) || s.input->height != proof.height())
      throw Error("candidate_binding", "cache prefix binding/context differs from original");
  }
  auto owned_binding = std::make_shared<const cd::BindingData>(cd::BindingData{
      binding.catalog(), binding.query(), AccountingVersion::continuation_v1});
  const auto height = proof.height();
  auto input = std::make_shared<const cand::InputData>(cand::InputData{
      std::move(proof), std::move(context), std::move(owned_binding), std::move(bytes), height});
  std::shared_ptr<const ResidualCandidate> seed;
  if (residual) seed = std::make_shared<const ResidualCandidate>(std::move(*residual));
  return CandidateProvider(std::make_unique<Impl>(std::move(input), limits, std::move(seed), std::move(prefix)));
}
CandidateAdvance CandidateProvider::advance(WorkQuantum quantum) noexcept {
  const auto answer = [&](CandidateStop s) noexcept { return CandidateAdvance{s, progress()}; };
  if (!data_) return answer(CandidateStop::moved_from);
  if (quantum.active_time && quantum.active_time->count() < 0) return answer(CandidateStop::invalid_quantum);
  if (!quantum.work) return answer(CandidateStop::quantum_work);
  if (quantum.active_time && quantum.active_time->count() == 0) return answer(CandidateStop::quantum_time);
  auto& d = *data_;
  if (d.terminal()) return answer(d.terminal_reason());
  CandidateStop stop = CandidateStop::none;
  {
    cd::ActiveMeter meter(d.ledger);
    const auto start = std::chrono::steady_clock::now();
    std::uint64_t used = 0;
    for (;;) {
      meter.sample();
      // Logical counters cannot wrap; active_nanoseconds remains a saturating
      // diagnostic and is still checked against any finite total-time ceiling.
      if (d.ledger.counters.attempted == maximum ||
          d.ledger.counters.committed_transitions == maximum) {
        stop = CandidateStop::counter_overflow; d.fail(stop); break;
      }
      if (used >= quantum.work) { stop = CandidateStop::quantum_work; break; }
      if (quantum.active_time && std::chrono::steady_clock::now() - start >= *quantum.active_time) {
        stop = CandidateStop::quantum_time; break;
      }
      const auto limit = d.ledger.check();
      if (limit != StopReason::none) { stop = translate(limit); break; }
      ++used; ++d.ledger.counters.attempted;
      try {
        const auto result = d.unit();
        // A blocked push owns no requested frame. Sample only saved worker
        // state, including stopped transitions that do not commit work.
        d.ledger.depth(d.depth());
        if (result != CandidateStop::none && result != CandidateStop::candidate_ready) {
          stop = result;
          if (stop == CandidateStop::counter_overflow || stop == CandidateStop::internal_failure) d.fail(stop);
          break;
        }
        ++d.ledger.counters.committed_transitions;
        if (result == CandidateStop::candidate_ready) { stop = result; break; }
        if (d.terminal()) { stop = d.terminal_reason(); break; }
      } catch (const cand::ContentStop& e) {
        d.ledger.depth(d.depth());
        stop = translate(e.reason);
        if (stop == CandidateStop::counter_overflow) d.fail(stop);
        break;
      } catch (const Stopped& e) {
        d.ledger.depth(d.depth());
        stop = e.reason;
        if (stop == CandidateStop::counter_overflow || stop == CandidateStop::internal_failure) d.fail(stop);
        break;
      } catch (const std::bad_alloc&) {
        d.ledger.depth(d.depth());
        if (d.ledger.counters.allocation_failures == maximum) {
          stop = CandidateStop::counter_overflow; d.fail(stop);
        } else { ++d.ledger.counters.allocation_failures; stop = CandidateStop::allocation_failure; }
        break;
      } catch (...) {
        d.ledger.depth(d.depth());
        stop = CandidateStop::internal_failure; d.fail(stop); break;
      }
    }
  }
  d.last_stop = stop;
  return answer(stop);
}
CandidateProgress CandidateProvider::progress() const noexcept {
  CandidateProgress p;
  if (!data_) { p.phase = CandidatePhase::moved_from; p.last_stop = CandidateStop::moved_from; return p; }
  const auto& d = *data_;
  p.phase = d.phase(); p.last_stop = d.last_stop; p.verified_original_height = d.input->height;
  p.family_exhausted = d.family_complete; p.work = d.ledger.counters; p.statistics = d.stats;
  p.records = d.budget->records(); p.cells = d.budget->cells(); p.limit_revision = d.revision;
  p.candidate_count = d.published.size(); return p;
}
std::size_t CandidateProvider::candidate_count() const noexcept { return data_ ? data_->published.size() : 0; }
std::optional<MinimumHeightCandidate> CandidateProvider::candidate(std::size_t i) const noexcept {
  if (!data_ || i >= data_->published.size()) return {};
  return data_->published[i];
}
VerifiedOptimum CandidateProvider::original_proof() const {
  if (!data_) throw Error("invalid_candidate_provider", "provider was moved from");
  return data_->input->proof;
}
const CandidateContext& CandidateProvider::context() const {
  if (!data_) throw Error("invalid_candidate_provider", "provider was moved from");
  return data_->input->context;
}
CandidateLimits CandidateProvider::limits() const {
  if (!data_) throw Error("invalid_candidate_provider", "provider was moved from");
  return data_->limits;
}
LimitChange CandidateProvider::raise_limits(CandidateLimits next) noexcept {
  if (!data_ || data_->terminal()) return LimitChange::terminal;
  auto& d = *data_; const auto& old = d.limits;
  if (!cd::valid_ceiling(next.enumeration)) return LimitChange::invalid;
  if (!cd::monotone_phase(old.enumeration, next.enumeration) ||
      !cd::monotone_ceiling(old.logical_depth, next.logical_depth) ||
      !cd::monotone_ceiling(old.records, next.records) || !cd::monotone_ceiling(old.cells, next.cells) ||
      !cd::monotone_ceiling(old.retained_candidates, next.retained_candidates)) return LimitChange::not_monotone;
  if (d.ledger.below_consumed(next.enumeration) || (next.records && *next.records < d.budget->records()) ||
      (next.cells && *next.cells < d.budget->cells()) ||
      (next.retained_candidates && *next.retained_candidates < d.published.size())) return LimitChange::below_consumed;
  if (d.revision == maximum) {
    d.fail(CandidateStop::counter_overflow);
    d.last_stop = CandidateStop::counter_overflow;
    return LimitChange::terminal;
  }
  if (!d.budget->raise_limits({next.records, next.cells})) return LimitChange::invalid;
  d.limits = next; d.ledger.limit = next.enumeration; ++d.revision; return LimitChange::applied;
}
void CandidateProvider::cancel() noexcept {
  if (!data_ || data_->terminal()) return;
  auto& d = *data_;
  if (d.generator) d.generator->cancel();
  if (d.canonicalizer) d.canonicalizer->cancel();
  d.discard(); d.generator.reset(); d.prefix.reset(); d.residual.reset();
  d.stage = Impl::Stage::cancelled; d.last_stop = CandidateStop::cancelled; d.ledger.depth(0);
}
CandidateSnapshot CandidateProvider::snapshot() const {
  if (!data_) throw Error("invalid_candidate_provider", "provider was moved from");
  const auto& d = *data_;
  return cand::Factory::snapshot(std::make_shared<const cand::SnapshotData>(cand::SnapshotData{
      d.input, d.published, d.reuse, d.family_complete}));
}

struct CandidateCache::Impl {
  std::size_t capacity;
  std::list<CandidateSnapshot> fifo;
  CandidateCacheStatistics stats;
  explicit Impl(std::size_t c) : capacity(c) {}
};
CandidateCache::CandidateCache(std::unique_ptr<Impl> p) noexcept : data_(std::move(p)) {}
CandidateCache::~CandidateCache() = default;
CandidateCache::CandidateCache(CandidateCache&&) noexcept = default;
CandidateCache& CandidateCache::operator=(CandidateCache&&) noexcept = default;
CandidateCache CandidateCache::create(std::size_t capacity) { return CandidateCache(std::make_unique<Impl>(capacity)); }
std::optional<CandidateSnapshot> CandidateCache::lookup(const VerifiedOptimum& proof, const CandidateContext& context) {
  if (!data_) throw Error("invalid_candidate_cache", "cache was moved from");
  context_valid(context);
  if (!proof.valid()) throw Error("invalid_candidate_proof", "original verified optimum is required");
  auto& d = *data_;
  const auto binding = proof.binding();
  const auto bytes = binding_bytes(binding.catalog(), binding.query());
  for (const auto& snapshot : d.fifo) {
    const auto& input = *cand::Factory::snapshot_data(snapshot).input;
    if (input.binding_bytes == bytes && same_context(input.context, context)) {
      if (input.height != proof.height())
        throw Error("candidate_proof_conflict", "exact binding has conflicting verified heights");
      if (d.stats.hits == maximum) throw Error("candidate_cache_overflow", "cache counter exhausted");
      ++d.stats.hits; return snapshot;
    }
  }
  if (d.stats.misses == maximum) throw Error("candidate_cache_overflow", "cache counter exhausted");
  ++d.stats.misses; return {};
}
CandidateCacheInstall CandidateCache::install(const CandidateSnapshot& snapshot) {
  if (!data_) throw Error("invalid_candidate_cache", "cache was moved from");
  const auto& incoming = cand::Factory::snapshot_data(snapshot);
  auto& d = *data_;
  if (!d.capacity) return CandidateCacheInstall::disabled;
  for (auto& current : d.fifo) {
    const auto& old = cand::Factory::snapshot_data(current);
    if (old.input->binding_bytes == incoming.input->binding_bytes &&
        same_context(old.input->context, incoming.input->context)) {
      if (old.input->height != incoming.input->height)
        throw Error("candidate_proof_conflict", "exact binding has conflicting verified heights");
      if (d.stats.replacements == maximum) throw Error("candidate_cache_overflow", "cache counter exhausted");
      auto prepared = snapshot; // immutable owning handle; cannot throw
      current = std::move(prepared); ++d.stats.replacements;
      return CandidateCacheInstall::replaced; // preserves original FIFO position
    }
  }
  const bool evict = d.fifo.size() == d.capacity;
  if (d.stats.insertions == maximum || (evict && d.stats.evictions == maximum) ||
      d.fifo.size() == d.fifo.max_size())
    throw Error("candidate_cache_overflow", "cache counter exhausted");
  // Allocate the complete node first. A failure keeps both FIFO and counters.
  std::list<CandidateSnapshot> prepared;
  prepared.push_back(snapshot);
  d.fifo.splice(d.fifo.end(), prepared);
  if (evict) { d.fifo.pop_front(); ++d.stats.evictions; }
  ++d.stats.insertions; return CandidateCacheInstall::inserted;
}
CandidateCacheStatistics CandidateCache::statistics() const noexcept {
  if (!data_) return {};
  auto stats = data_->stats; stats.entries = data_->fifo.size(); return stats;
}
void CandidateCache::clear() noexcept { if (data_) data_->fifo.clear(); }
}  // namespace crown::planner
