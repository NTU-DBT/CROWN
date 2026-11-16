#include "selection_detail.hpp"
#include "compiled_source.hpp"
#include "update_pattern_detail.hpp"
#include "crown/planner/lower.hpp"
#include "crown/api/error.hpp"
#include <new>

namespace crown::planner::selection {
// Copy all physical policy text into the receiving account. See docs/selection.md.
CapturedCachePolicy::CapturedCachePolicy(const resource::MemoryAccount& account,const io::CachePolicy& value)
    :arithmetic(value.arithmetic,detail::selection_allocator<char>(account)),
     planner(value.planner,detail::selection_allocator<char>(account)),
     optimization(value.optimization,detail::selection_allocator<char>(account)),
     cost_model(value.cost_model,detail::selection_allocator<char>(account)) {}
CapturedPhysicalOptions::CapturedPhysicalOptions(const resource::MemoryAccount& account,const PhysicalOptions& value)
    :policy(account,value.policy),limits(value.limits),indexed_storage(value.indexed_storage) {}
// Capture an admitted request with native slot-cap text. See docs/selection.md.
CapturedRequest::CapturedRequest(const resource::MemoryAccount& account,const Request& value)
    :policy(value.policy),fallback(value.fallback),family(value.family),layout(value.layout),indexes(value.indexes),limits(value.limits) {
  if(const auto* cap=std::get_if<TupleIndexSlotLimit>(&value.constraint))
    constraint=CapturedTupleIndexSlotLimit{SelectionText(cap->maximum,detail::selection_allocator<char>(account))};
  else if(const auto* cap=std::get_if<AllocatorByteLimit>(&value.constraint))constraint=*cap;
  if (value.update_patterns)
    update_patterns = patterns::Declaration::copy_of(account, *value.update_patterns);
}
const CandidateSnapshot& Selection::snapshot() const noexcept { return data_->snapshot; }
const MinimumHeightCandidate& Selection::selected() const noexcept { return *data_->chosen; }
std::size_t Selection::selected_index() const noexcept { return data_->selected; }
const CompiledProgram& Selection::plan() const noexcept { return *data_->plan; }
const CapturedSource& Selection::source() const noexcept { return data_->source; }
const CapturedRequest& Selection::request() const noexcept { return data_->request; }
const resource::MemoryAccount& Selection::account() const & noexcept {return data_->account;}
// Export explicit caller-owned source configuration. See docs/selection.md.
Source Selection::export_source() const {
  if(const auto* direct=std::get_if<CapturedDirectCQ>(&data_->source)) {
    const auto& p=direct->options;PhysicalOptions out;
    out.policy={std::string(p.policy.arithmetic),std::string(p.policy.planner),std::string(p.policy.optimization),std::string(p.policy.cost_model)};
    out.limits=p.limits;out.indexed_storage=p.indexed_storage;return DirectCQ{std::move(out)};
  }
  return std::get<PhysicalBasis>(data_->source);
}
// Export captured request into ordinary caller storage. See docs/selection.md.
Request Selection::export_request() const {
  const auto& r=data_->request;Request out{r.policy,r.fallback,r.family,r.layout,r.indexes,{},r.limits,r.update_patterns};
  if(const auto* cap=std::get_if<CapturedTupleIndexSlotLimit>(&r.constraint))out.constraint=TupleIndexSlotLimit{std::string(cap->maximum)};
  else if(const auto* cap=std::get_if<AllocatorByteLimit>(&r.constraint))out.constraint=*cap;
  return out;
}
const SelectionVector<Assessment>& Selection::assessments() const noexcept { return data_->assessments; }
const SelectionVector<CandidateDecision>& Selection::decisions() const noexcept { return data_->decisions; }
const SelectionVector<patterns::Analysis>& Selection::pattern_analyses() const noexcept { return data_->pattern_analyses; }
std::optional<PatternGuarantee> Selection::pattern_guarantee() const noexcept {
  if (data_->pattern_analyses.empty() ||
      data_->pattern_analyses[data_->selected].sufficient == patterns::SufficientCase::unknown) return {};
  return PatternGuarantee(data_);
}
const patterns::Analysis& PatternGuarantee::analysis() const & noexcept { return data_->pattern_analyses[data_->selected]; }
const CompiledProgram& PatternGuarantee::plan() const & noexcept { return *data_->plan; }
const std::optional<rank::Evidence>& Selection::evidence() const noexcept { return data_->evidence; }
EvidenceUse Selection::evidence_use() const noexcept { return data_->evidence ? EvidenceUse::as_of : EvidenceUse::absent; }
rank::Policy Selection::effective_policy() const noexcept { return data_->effective; }
rank::Reasons Selection::fallback_reasons() const noexcept { return data_->fallback; }
const rank::Usage& Selection::usage() const noexcept { return data_->usage; }
PreparationTiming Selection::preparation_timing() const noexcept { return data_->timing; }
const CacheObservation& Selection::cache_observation() const noexcept { return data_->cache; }
const std::optional<SelectionText>& Selection::cache_binding() const noexcept { return data_->key; }
namespace detail {
// Prepare account-backed result storage with complete source/request/evidence owners. See
// docs/query_memory.md.
SelectionData::SelectionData(const resource::MemoryAccount& a,const CandidateSnapshot& s,const Source& p,
    const Request& r,const std::optional<rank::Evidence>& e)
    :account(a),snapshot(s),source(std::visit([&](const auto& input)->CapturedSource {
      if constexpr(std::is_same_v<std::remove_cvref_t<decltype(input)>,DirectCQ>)return CapturedDirectCQ{CapturedPhysicalOptions(a,input.options)};
      else return input;
    },p)),request(a,r),evidence(e),assessments(selection_allocator<Assessment>(a)),decisions(selection_allocator<CandidateDecision>(a)),
     pattern_analyses(selection_allocator<patterns::Analysis>(a)) {}
namespace {
void strings(const io::CachePolicy& policy, Budget& b) {
  for (const auto* value : {&policy.arithmetic, &policy.planner, &policy.optimization, &policy.cost_model}) {
    b.work(static_cast<std::uint64_t>(value->size())); b.bytes(static_cast<std::uint64_t>(value->size()));
  }
}
// Choose the receiving allocation account without minting an internal query refill. See
// docs/query_memory.md.
resource::MemoryAccount operation_account(const Source& source,const std::optional<rank::Evidence>& evidence,
    const resource::MemoryAccount& receiving) {
  if(receiving)return receiving;
  if(evidence)return evidence->plan().account();
  if(const auto* basis=std::get_if<PhysicalBasis>(&source))
    if(const auto* native=std::get_if<CompiledProgram>(&basis->plan)) {
      require(bool(*native),Stop::invalid_handle);return native->account();
    }
  // This entry point also serves a standalone compiler, before a query exists.
  return resource::MemoryAccount::create(UINT64_MAX);
}
// Lower/replan exactly the chosen candidate under remaining aggregate native work. See
// docs/selection_accounting.md.
CompiledProgram lower_winner(const MinimumHeightCandidate& candidate, const Source& source,
    const std::optional<rank::Evidence>& evidence,Budget& b) {
  b.sample();
  const auto* basis = std::get_if<PhysicalBasis>(&source);
  if (basis) std::visit([&](const auto& plan){source_payload(candidate,plan,b);},basis->plan);
  else {
    direct_source_payload(candidate, b);
    // This known copy is distinct from SelectionData's copied DirectCQ. The
    // compiled walker later conservatively includes the options again.
    b.work(); b.bytes(sizeof(PhysicalOptions)); strings(std::get<DirectCQ>(source).options.policy, b);
  }
  const auto prior = b.usage;
  PhysicalLimits host;
  host.work_limit = b.limits.lowering_work - prior.lowering_work;
  host.identity.work_limit = b.limits.identity_work - prior.identity_work;
  io::ProgramReadLimits replay;
  replay.binding.work_limit = b.limits.binding_replay_work - prior.binding_replay_work;
  replay.normalization.work_limit = b.limits.normalization_work - prior.normalization_work;
  const bool normalized = basis && std::visit([](const auto& plan){return plan.normalized().has_value();},basis->plan);
  if (normalized) {
    std::visit([&](const auto& plan){
      replay.binding.expression_limit=plan.normalized()->binding.limits.expression_limit;
      replay.binding.recursion_limit=plan.normalized()->binding.limits.recursion_limit;
    },basis->plan);
  }
  b.usage.lowering_work = b.limits.lowering_work;
  b.usage.identity_work = b.limits.identity_work;
  if (normalized) {
    b.usage.binding_replay_work = b.limits.binding_replay_work;
    b.usage.normalization_work = b.limits.normalization_work;
  }
  std::optional<CompiledProgram> admitted;
  const CompiledProgram* native=evidence?&evidence->plan():nullptr;
  if(!native && basis)std::visit([&](const auto& plan) {
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(plan)>,CompiledProgram>)native=&plan;
    else {
      admitted=CompiledProgram::compile(b.memory,plan);native=&*admitted;
    }
  },basis->plan);
  CompiledProgram result;
  if(native) {
    program::ReplanLimits limits{host,replay.binding.work_limit,replay.normalization.work_limit};
    try {result=CompiledProgram::replan_into(b.memory,*native,candidate,limits);}
    catch(const program::ReplanFailure& failure) {
      if(failure.fault()==program::ReplanFault::binding)throw Failure{Stop::binding_mismatch,Resource::none,{},0};
      const auto resource=failure.fault()==program::ReplanFault::identity_work?Resource::identity:
          failure.fault()==program::ReplanFault::binding_replay_work?Resource::binding_replay:
          failure.fault()==program::ReplanFault::normalization_work?Resource::normalization:Resource::lowering;
      throw Failure{Stop::resource_limit,resource,rank::Stop::lowering_limit,0};
    }
  }else {
    // DirectCQ without runtime evidence is the explicit initial compiler API.
    // Its compiler workspace precedes execution admission; the published artifact
    // is frozen into this standalone component account without a retained DTO.
    // Choose an operator input explicitly; the public lowerer still rejects
    // nonempty supplied trees for a contradiction. Both operands are borrows.
    const FreeConnexTree empty;
    const auto& query=candidate.query();
    const auto& tree=query.contradiction && !query.atoms.empty()?empty:candidate.tree();
    const auto compiled=lower_tree(candidate.catalog(),query,tree,std::get<DirectCQ>(source).options,host);
    result=CompiledProgram::compile(b.memory,compiled);
  }
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
// Bind one synchronous transaction and its initial preparation usage/account. See
// docs/selection.md.
Operation::Operation(const CandidateSnapshot& s, const Source& p, const Request& r,
    const std::optional<rank::Evidence>& e, PlanCache* c, CacheUse use, Origin o,const resource::MemoryAccount& receiving)
    : snapshot(s), source(p), request(r), cache(use == CacheUse::bypass ? nullptr : Factory::cache(c)),
      cache_use(use), origin(o), evidence(e), budget(r.limits.aggregate, e ? e->preparation_usage() : rank::Usage{},operation_account(p,e,receiving)) {
  if (use != CacheUse::bypass) require(c != nullptr, Stop::invalid_request);
  diagnostic.preparation_timing = preparation_timing(e);
}
// Validate supported request and the typed original-proof family before speculative work. See
// docs/selection.md.
void Operation::admit() {
  diagnostic.stage = Stage::admission;
  budget.work();
  require(request.policy == Policy::height_only || request.policy == Policy::committed_input_native_depth ||
      request.policy == Policy::tuple_index_slots || request.policy == Policy::maintenance_cost, Stop::invalid_request);
  if (request.policy == Policy::maintenance_cost) throw Failure{Stop::unsupported_model, Resource::none, {}, 0};
  if (std::holds_alternative<AllocatorByteLimit>(request.constraint))
    throw Failure{Stop::unsupported_memory_prediction, Resource::none, {}, 0};
  require(!source.valueless_by_exception() && !request.constraint.valueless_by_exception(), Stop::invalid_request);
  if(const auto* basis=std::get_if<PhysicalBasis>(&source))
    if(const auto* native=std::get_if<CompiledProgram>(&basis->plan))require(bool(*native),Stop::invalid_handle);
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
  if (request.update_patterns) {
    require(bool(*request.update_patterns), Stop::invalid_handle);
    const auto* basis = std::get_if<PhysicalBasis>(&source);
    require(basis && std::holds_alternative<CompiledProgram>(basis->plan), Stop::unsupported_model);
  }
  if (const auto* cap = std::get_if<TupleIndexSlotLimit>(&request.constraint)) validate_slot_limit(cap->maximum, budget);
}
// Attach a freshly prepared runtime-bridge evidence owner exactly once. See
// docs/selection.md.
void Operation::attach(const rank::Evidence& value) {
  require(!evidence.has_value()); evidence = value;
  diagnostic.preparation_timing = preparation_timing(evidence);
}
bool Operation::needs_sources() const noexcept {
  return request.policy == Policy::tuple_index_slots || std::holds_alternative<TupleIndexSlotLimit>(request.constraint);
}
// Evaluate the full retained family, choose an eligible winner and privately prepare its
// exact artifact/cache action. See docs/selection.md.
Prepared Operation::prepare() {
  diagnostic.stage = Stage::source_binding;
  source_binding(snapshot, source, evidence, budget);
  if (request.update_patterns) {
    const auto& native = std::get<CompiledProgram>(std::get<PhysicalBasis>(source).plan);
    budget.work(64);
    require(request.update_patterns->matches(native), Stop::binding_mismatch);
    const auto copy = request.update_patterns->copy_usage();
    budget.work(copy.work);
    budget.cells(copy.cells);
    budget.bytes(copy.payload_bytes);
  }
  budget.bytes(sizeof(SelectionData));
  if (const auto* direct = std::get_if<DirectCQ>(&source)) strings(direct->options.policy, budget);
  if (const auto* cap = std::get_if<TupleIndexSlotLimit>(&request.constraint)) {
    budget.work(static_cast<std::uint64_t>(cap->maximum.size())); budget.bytes(static_cast<std::uint64_t>(cap->maximum.size()));
  }
  Prepared prepared;
  prepared.data = resource::make_accounted_shared<SelectionData>(selection_memory_owner,budget.memory,
      resource::MemoryPurpose::capture,budget.memory,snapshot,source,request,evidence);
  auto& data = *prepared.data; data.timing = diagnostic.preparation_timing;
  // Full source/declaration binding was checked once above. The private visitor
  // reuses it and charges each candidate's edge/transfer work to this grant.
  if (data.request.update_patterns) {
    diagnostic.stage = Stage::pattern_analysis;
    const auto& native = std::get<CompiledProgram>(std::get<PhysicalBasis>(source).plan);
    budget.vector<patterns::Analysis>(diagnostic.retained);
    data.pattern_analyses.reserve(diagnostic.retained);
    budget.borrowed([&](rd::Budget& inner) {
      for (std::size_t i = 0; i < diagnostic.retained; ++i) {
        inner.work();
        const auto candidate = snapshot.candidate(i);
        require(candidate.has_value());
        data.pattern_analyses.push_back(patterns::detail::analyse_bound(
            budget.memory, native, *candidate, *data.request.update_patterns, inner));
      }
    });
  }
  const bool constrained = std::holds_alternative<TupleIndexSlotLimit>(request.constraint);
  const bool memory = request.policy == Policy::tuple_index_slots;
  const bool depth = request.policy == Policy::committed_input_native_depth;
  const auto assessment_count = constrained && depth ? std::size_t{2} : std::size_t{1};
  budget.vector<Assessment>(assessment_count); data.assessments.reserve(assessment_count);
  budget.vector<CandidateDecision>(diagnostic.retained); data.decisions.reserve(diagnostic.retained);
  const auto preparation = evidence ? evidence->preparation_usage() : rank::Usage{};
  // Delegate one complete C02 assessment from the remaining aggregate grant. See
  // docs/selection_accounting.md.
  const auto assess = [&](rank::Policy policy, rank::Fallback fallback, AssessmentPurpose purpose) {
    diagnostic.stage = purpose == AssessmentPurpose::slot_constraint || purpose == AssessmentPurpose::primary_and_constraint ?
        Stage::constraint_assessment : Stage::primary_assessment;
    rank::Request next; next.policy = policy; next.fallback = fallback;
    next.limits = budget.begin_delegate(preparation);
    auto result = rank::rank_with_account(budget.memory,snapshot, next, evidence);
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
    if (eligibility != Eligibility::above_slot_limit && !data.pattern_analyses.empty() &&
        data.pattern_analyses[i].sufficient == patterns::SufficientCase::unknown)
      eligibility = Eligibility::pattern_unproved;
    any = any || (eligibility != Eligibility::above_slot_limit && eligibility != Eligibility::pattern_unproved);
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
    budget.work(); if (data.decisions[i].eligibility == Eligibility::above_slot_limit ||
        data.decisions[i].eligibility == Eligibility::pattern_unproved) continue;
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
      diagnostic.stage = Stage::lowering; data.plan = lower_winner(*data.chosen, source,evidence,budget);
    }
  }
  diagnostic.stage = Stage::source_binding; compiled_binding(snapshot, source, *data.chosen, *data.plan, budget);
  diagnostic.stage = Stage::cache_admission; stage_cache_entry(prepared, budget);
  diagnostic.stage = Stage::publication;
  return prepared;
}
// Publish result/cache only after the final cooperative deadline check. See
// docs/selection_accounting.md.
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
  note(component_diagnostic(stop));
}
// Capture final diagnostic elapsed/usage after success or failure. See
// docs/selection_accounting.md.
void Operation::finish() noexcept { budget.finish(); diagnostic.usage = budget.usage; }
} // namespace detail
// Execute pure synchronous selection as an atomic result/cache transaction. See
// docs/selection.md.
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
  } catch (const storage::IndexFailure& failure) {
    if(operation) {
      const auto code=failure.code();
      if(code=="storage_work_limit" || code=="storage_capacity" || code=="storage_overflow")operation->note(rank::Stop::lowering_limit);
      else operation->note({Stop::internal_error,Resource::none,{},0});
    }
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
