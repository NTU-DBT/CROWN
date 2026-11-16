#include "selection_detail.hpp"
#include "crown/planner/lower.hpp"
#include "crown/api/error.hpp"
#include <new>

namespace crown::planner::selection {
const CandidateSnapshot& Selection::snapshot() const noexcept { return data_->snapshot; }
const MinimumHeightCandidate& Selection::selected() const noexcept { return *data_->chosen; }
std::size_t Selection::selected_index() const noexcept { return data_->selected; }
const PhysicalPlan& Selection::plan() const noexcept { return *data_->plan; }
const Source& Selection::source() const noexcept { return data_->source; }
const Request& Selection::request() const noexcept { return data_->request; }
const std::vector<Assessment>& Selection::assessments() const noexcept { return data_->assessments; }
const std::vector<CandidateDecision>& Selection::decisions() const noexcept { return data_->decisions; }
const std::optional<rank::Evidence>& Selection::evidence() const noexcept { return data_->evidence; }
EvidenceUse Selection::evidence_use() const noexcept { return data_->evidence ? EvidenceUse::as_of : EvidenceUse::absent; }
rank::Policy Selection::effective_policy() const noexcept { return data_->effective; }
rank::Reasons Selection::fallback_reasons() const noexcept { return data_->fallback; }
const rank::Usage& Selection::usage() const noexcept { return data_->usage; }
PreparationTiming Selection::preparation_timing() const noexcept { return data_->timing; }
const CacheObservation& Selection::cache_observation() const noexcept { return data_->cache; }
const std::optional<std::string>& Selection::cache_binding() const noexcept { return data_->key; }
namespace detail {
namespace {
void strings(const io::CachePolicy& policy, Budget& b) {
  for (const auto* value : {&policy.arithmetic, &policy.planner, &policy.optimization, &policy.cost_model}) {
    b.work(static_cast<std::uint64_t>(value->size())); b.bytes(static_cast<std::uint64_t>(value->size()));
  }
}
PhysicalPlan lower_winner(const MinimumHeightCandidate& candidate, const Source& source, Budget& b) {
  b.sample();
  const auto* basis = std::get_if<PhysicalBasis>(&source);
  const auto& options = basis ? basis->plan.options() : std::get<DirectCQ>(source).options;
  if (basis) source_payload(candidate, basis->plan, b);
  else {
    direct_source_payload(candidate, b);
    // This known copy is distinct from SelectionData's copied DirectCQ. The
    // compiled walker later conservatively includes the options again.
    b.work(); b.bytes(sizeof(PhysicalOptions)); strings(options.policy, b);
  }
  const auto prior = b.usage;
  PhysicalLimits host;
  host.work_limit = b.limits.lowering_work - prior.lowering_work;
  host.identity.work_limit = b.limits.identity_work - prior.identity_work;
  io::ProgramReadLimits replay;
  replay.binding.work_limit = b.limits.binding_replay_work - prior.binding_replay_work;
  replay.normalization.work_limit = b.limits.normalization_work - prior.normalization_work;
  const bool normalized = basis && basis->plan.normalized().has_value();
  if (normalized) {
    replay.binding.expression_limit = basis->plan.normalized()->binding.limits.expression_limit;
    replay.binding.recursion_limit = basis->plan.normalized()->binding.limits.recursion_limit;
  }
  b.usage.lowering_work = b.limits.lowering_work;
  b.usage.identity_work = b.limits.identity_work;
  if (normalized) {
    b.usage.binding_replay_work = b.limits.binding_replay_work;
    b.usage.normalization_work = b.limits.normalization_work;
  }
  auto result = normalized ? lower_normalized(*basis->plan.normalized(), candidate.tree(), options, replay, host) :
      lower_tree(candidate.catalog(), candidate.query(), candidate.tree(), options, host);
  b.usage.lowering_work = prior.lowering_work;
  b.usage.identity_work = prior.identity_work;
  Budget::add(b.usage.lowering_work, result.work(), b.limits.lowering_work, Resource::lowering);
  Budget::add(b.usage.identity_work, result.identity().work, b.limits.identity_work, Resource::identity);
  if (normalized) {
    b.usage.binding_replay_work = prior.binding_replay_work;
    b.usage.normalization_work = prior.normalization_work;
    Budget::add(b.usage.binding_replay_work, result.normalized()->binding.work, b.limits.binding_replay_work, Resource::binding_replay);
    Budget::add(b.usage.normalization_work, result.normalized()->work, b.limits.normalization_work, Resource::normalization);
  }
  b.sample();
  if (!basis) identity_payload(result.identity(), b);
  compiled_payload(result, b);
  return result;
}
}
Operation::Operation(const CandidateSnapshot& s, const Source& p, const Request& r,
    const std::optional<rank::Evidence>& e, PlanCache* c, CacheUse use, Origin o)
    : snapshot(s), source(p), request(r), cache(use == CacheUse::bypass ? nullptr : Factory::cache(c)),
      cache_use(use), origin(o), evidence(e), budget(r.limits.aggregate, e ? e->preparation_usage() : rank::Usage{}) {
  if (use != CacheUse::bypass) require(c != nullptr, Stop::invalid_request);
  diagnostic.preparation_timing = preparation_timing(e);
}
void Operation::admit() {
  diagnostic.stage = Stage::admission;
  budget.work();
  require(request.policy == Policy::height_only || request.policy == Policy::committed_input_native_depth ||
      request.policy == Policy::tuple_index_slots || request.policy == Policy::maintenance_cost, Stop::invalid_request);
  if (request.policy == Policy::maintenance_cost) throw Failure{Stop::unsupported_model, Resource::none, {}, 0};
  if (std::holds_alternative<AllocatorByteLimit>(request.constraint))
    throw Failure{Stop::unsupported_memory_prediction, Resource::none, {}, 0};
  require(!source.valueless_by_exception() && !request.constraint.valueless_by_exception(), Stop::invalid_request);
  if (request.layout != LayoutPolicy::native_layout_v1 || request.indexes != IndexPolicy::share_identical_requirements_v1)
    throw Failure{Stop::unsupported_layout, Resource::none, {}, 0};
  require(request.fallback == rank::Fallback::height_only || request.fallback == rank::Fallback::require_evidence, Stop::invalid_request);
  require(request.family == FamilyPolicy::retained_prefix || request.family == FamilyPolicy::require_exhausted_family, Stop::invalid_request);
  require(cache_use == CacheUse::bypass || cache_use == CacheUse::read_only || cache_use == CacheUse::read_write, Stop::invalid_request);
  if (cache_use != CacheUse::bypass) require(cache != nullptr, Stop::invalid_handle);
  require(snapshot.valid(), Stop::invalid_handle);
  require(snapshot.original_proof().valid(), Stop::invalid_handle);
  diagnostic.retained = snapshot.candidate_count();
  if (diagnostic.retained > budget.limits.candidates) throw Failure{Stop::resource_limit, Resource::candidates, {}, 0};
  require(diagnostic.retained != 0, Stop::no_candidates);
  if (request.family == FamilyPolicy::require_exhausted_family) require(snapshot.family_exhausted(), Stop::incomplete_family);
  if (const auto* cap = std::get_if<TupleIndexSlotLimit>(&request.constraint)) validate_slot_limit(cap->maximum, budget);
}
void Operation::attach(const rank::Evidence& value) {
  require(!evidence.has_value()); evidence = value;
  diagnostic.preparation_timing = preparation_timing(evidence);
}
bool Operation::needs_sources() const noexcept {
  return request.policy == Policy::tuple_index_slots || std::holds_alternative<TupleIndexSlotLimit>(request.constraint);
}
Prepared Operation::prepare() {
  diagnostic.stage = Stage::source_binding;
  source_binding(snapshot, source, evidence, budget);
  budget.bytes(sizeof(SelectionData));
  if (const auto* direct = std::get_if<DirectCQ>(&source)) strings(direct->options.policy, budget);
  if (const auto* cap = std::get_if<TupleIndexSlotLimit>(&request.constraint)) {
    budget.work(static_cast<std::uint64_t>(cap->maximum.size())); budget.bytes(static_cast<std::uint64_t>(cap->maximum.size()));
  }
  Prepared prepared;
  prepared.data = std::make_shared<SelectionData>(snapshot, source, request, evidence);
  auto& data = *prepared.data; data.timing = diagnostic.preparation_timing;
  const bool constrained = std::holds_alternative<TupleIndexSlotLimit>(request.constraint);
  const bool memory = request.policy == Policy::tuple_index_slots;
  const bool depth = request.policy == Policy::committed_input_native_depth;
  const auto assessment_count = constrained && depth ? std::size_t{2} : std::size_t{1};
  budget.vector<Assessment>(assessment_count); data.assessments.reserve(assessment_count);
  budget.vector<CandidateDecision>(diagnostic.retained); data.decisions.reserve(diagnostic.retained);
  const auto preparation = evidence ? evidence->preparation_usage() : rank::Usage{};
  const auto assess = [&](rank::Policy policy, rank::Fallback fallback, AssessmentPurpose purpose) {
    diagnostic.stage = purpose == AssessmentPurpose::slot_constraint || purpose == AssessmentPurpose::primary_and_constraint ?
        Stage::constraint_assessment : Stage::primary_assessment;
    rank::Request next; next.policy = policy; next.fallback = fallback;
    next.limits = budget.begin_delegate(preparation);
    auto result = rank::rank(snapshot, next, evidence);
    if (purpose != AssessmentPurpose::primary) diagnostic.constraint_evaluated = result.evaluated;
    if (purpose != AssessmentPurpose::slot_constraint) diagnostic.primary_evaluated = result.evaluated;
    budget.end_delegate(result.usage, preparation);
    if (result.stop != rank::Stop::complete) component_failure(result.stop, result.reasons);
    require(result.result.has_value());
    const auto index = data.assessments.size();
    data.assessments.push_back({purpose, *result.result});
    return index;
  };
  std::optional<std::size_t> slots;
  std::size_t primary = 0;
  if (memory || constrained) {
    slots = assess(rank::Policy::tuple_index_slots, constrained ? rank::Fallback::require_evidence : request.fallback,
        memory ? (constrained ? AssessmentPurpose::primary_and_constraint : AssessmentPurpose::primary) : AssessmentPurpose::slot_constraint);
  }
  diagnostic.stage = Stage::decision;
  bool any = false;
  for (std::size_t i = 0; i < diagnostic.retained; ++i) {
    budget.work(); auto eligibility = Eligibility::unconstrained;
    if (constrained) {
      require(slots.has_value()); const auto& assessed = data.assessments[*slots].result;
      require(assessed.effective_policy() == rank::Policy::tuple_index_slots && assessed.scores().size() == diagnostic.retained);
      eligibility = decimal_compare(assessed.scores()[i].slots, std::get<TupleIndexSlotLimit>(request.constraint).maximum, budget) <= 0 ?
          Eligibility::within_slot_limit : Eligibility::above_slot_limit;
    }
    any = any || eligibility != Eligibility::above_slot_limit;
    data.decisions.push_back({i, eligibility});
  }
  require(any, Stop::constraint_unsatisfied);
  if (depth) primary = assess(rank::Policy::committed_input_native_depth, request.fallback, AssessmentPurpose::primary);
  else if (!slots) primary = assess(rank::Policy::height_only, request.fallback, AssessmentPurpose::primary);
  else primary = *slots;
  const auto& ranked = data.assessments[primary].result;
  const auto& scores = ranked.scores(); require(scores.size() == diagnostic.retained);
  data.effective = request.policy == Policy::height_only ? rank::Policy::height_only : ranked.effective_policy();
  data.fallback = request.policy == Policy::height_only ? 0 : ranked.fallback_reasons();
  diagnostic.stage = Stage::decision;
  std::optional<std::size_t> chosen;
  for (std::size_t i = 0; i < diagnostic.retained; ++i) {
    budget.work(); if (data.decisions[i].eligibility == Eligibility::above_slot_limit) continue;
    if (!chosen) { chosen = i; continue; }
    int comparison = 0;
    if (data.effective == rank::Policy::committed_input_native_depth) {
      require(equal_bytes(scores[i].denominator, scores[*chosen].denominator, budget));
      comparison = decimal_compare(scores[i].numerator, scores[*chosen].numerator, budget);
    } else if (data.effective == rank::Policy::tuple_index_slots)
      comparison = decimal_compare(scores[i].slots, scores[*chosen].slots, budget);
    if (comparison < 0 || (comparison == 0 && key_less(scores[i].structural_key, scores[*chosen].structural_key, budget))) chosen = i;
  }
  require(chosen.has_value()); data.selected = *chosen; data.chosen = snapshot.candidate(*chosen); require(data.chosen.has_value());
  diagnostic.primary_evaluated = diagnostic.retained;
  if (cache_use != CacheUse::bypass && cache && cache->limits.entries) {
    diagnostic.stage = Stage::cache_key; data.key = cache_binding(data, origin, budget);
  }
  diagnostic.stage = Stage::cache_lookup; prepare_cache(prepared, cache, cache_use, budget);
  if (!data.plan) {
    if (slots && data.assessments[*slots].result.effective_policy() == rank::Policy::tuple_index_slots) {
      data.plan = data.assessments[*slots].result.scores()[data.selected].modeled_plan;
      require(data.plan.has_value());
    } else {
      diagnostic.stage = Stage::lowering; data.plan = lower_winner(*data.chosen, source, budget);
    }
  }
  diagnostic.stage = Stage::source_binding; compiled_binding(snapshot, source, *data.chosen, *data.plan, budget);
  diagnostic.stage = Stage::cache_admission; stage_cache_entry(prepared, budget);
  diagnostic.stage = Stage::publication;
  return prepared;
}
void Operation::finalize(Prepared& prepared) {
  diagnostic.stage = Stage::publication; budget.sample();
  prepared.data->usage = budget.usage;
  diagnostic.usage = budget.usage; diagnostic.stop = Stop::complete;
  prepared.commit();
  // Publication and the following shared-handle copies cannot fail. Destruction
  // can cross a soft deadline; it cannot revoke an already committed result.
  budget.running = false;
}
void Operation::note(const Failure& failure) noexcept {
  diagnostic.stop = failure.stop; diagnostic.resource = failure.resource;
  diagnostic.component_stop = failure.component; diagnostic.reasons = failure.reasons;
}
void Operation::note(rank::Stop stop) noexcept {
  try { component_failure(stop); } catch (const Failure& failure) { note(failure); }
}
void Operation::finish() noexcept { budget.finish(); diagnostic.usage = budget.usage; }
} // namespace detail
Attempt select(const CandidateSnapshot& snapshot, const Source& source, const Request& request,
    const std::optional<rank::Evidence>& evidence, PlanCache* cache, CacheUse use) noexcept {
  Attempt out;
  out.usage = evidence ? evidence->preparation_usage() : rank::Usage{};
  out.preparation_timing = detail::preparation_timing(evidence);
  std::optional<detail::Operation> operation;
  try {
    operation.emplace(snapshot, source, request, evidence, cache, use, evidence ? detail::Origin::as_of : detail::Origin::absent);
    operation->admit(); auto prepared = operation->prepare();
    auto result = detail::Factory::selection(prepared.data);
    operation->finalize(prepared);
    operation->diagnostic.selection = std::move(result);
  } catch (const detail::Failure& failure) {
    if (operation) operation->note(failure);
    else { out.stop = failure.stop; out.resource = failure.resource; out.component_stop = failure.component; out.reasons = failure.reasons; }
  } catch (const detail::rd::Failure& failure) {
    if (operation) operation->note(failure.stop);
  } catch (const std::bad_alloc&) {
    if (operation) operation->note({Stop::allocation_failure, Resource::none, {}, 0}); else out.stop = Stop::allocation_failure;
  } catch (const Error& error) {
    if (operation) {
      if (error.code() == "resource_limit") operation->note(rank::Stop::lowering_limit);
      else operation->note({error.code() == "invalid_physical_plan" ? Stop::invalid_handle : Stop::lowering_failure, Resource::none, {}, 0});
    }
  } catch (...) {
    if (operation) operation->note({Stop::internal_error, Resource::none, {}, 0});
  }
  if (operation) { operation->finish(); return operation->diagnostic; }
  return out;
}
} // namespace crown::planner::selection
