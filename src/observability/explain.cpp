#include "crown/observability/explain.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <type_traits>
#include <utility>

namespace crown::observability {
namespace {
void require(bool condition,const char* code,const char* message) {
  if (!condition) throw Error(code,message);
}
template<class A,class B,class Equal> bool same_range(const A& a,const B& b,Equal equal) {
  if (a.size()!=b.size()) return false;
  for (std::size_t i=0;i<a.size();++i) if (!equal(a[i],b[i])) return false;
  return true;
}
template<class A,class B> bool equal_items(const A& a,const B& b) {return std::ranges::equal(a,b);}
template<class A,class B> bool equal_optional_items(const A& a,const B& b) {
  return a.has_value()==b.has_value() && (!a || equal_items(*a,*b));
}
template<class A,class B> bool same_constraint(const A& a,const B& b) {
  if(a.index()!=b.index())return false;
  if(const auto* x=std::get_if<0>(&a)) {
    const auto& y=std::get<0>(b);
    return x->name==y.name && equal_items(x->columns,y.columns) && x->status==y.status;
  }
  const auto& x=std::get<1>(a);const auto& y=std::get<1>(b);
  return x.name==y.name && equal_items(x.columns,y.columns) && x.status==y.status &&
      x.referenced_table==y.referenced_table && equal_items(x.referenced_columns,y.referenced_columns);
}
// Exact ordered metadata, including hints/statistics and constraint status;
// compare borrowed carriers directly, without JSON, hashes or deep exports.
template<class A,class B> bool same_catalog(const A& a,const B& b) {
  return a.version==b.version && same_range(a.tables,b.tables,[](const auto& x,const auto& y) {
    return x.name==y.name && x.source_schema_version==y.source_schema_version &&
      same_range(x.columns,y.columns,[](const auto& c,const auto& d) {
        return c.name==d.name && c.type==d.type && c.nullable==d.nullable && c.collation==d.collation && c.decimal==d.decimal;
      }) && same_range(x.constraints,y.constraints,[](const auto& c,const auto& d) {return same_constraint(c,d);}) &&
      x.statistics.row_count==y.statistics.row_count &&
      same_range(x.statistics.distinct_counts,y.statistics.distinct_counts,[](const auto& c,const auto& d) {
        return equal_items(c.columns,d.columns) && c.estimate==d.estimate;
      }) && same_range(x.key_hints,y.key_hints,[](const auto& c,const auto& d) {
        return equal_items(c.columns,d.columns) && c.reason==d.reason;
      });
  });
}
template<class Scalar> storage::ScalarView scalar_view(const Scalar& value) {
  if constexpr(std::is_same_v<Scalar,Value>)return storage::borrow_scalar(value);
  else return value;
}
template<class A,class B> bool same_term(const A& a,const B& b) {
  if(a.index()!=b.index())return false;
  if(const auto* id=std::get_if<0>(&a))return *id==std::get<0>(b);
  if(const auto* value=std::get_if<1>(&a))return scalar_view(*value)==scalar_view(std::get<1>(b));
  return true;
}
template<class A,class B> bool same_query(const A& a,const B& b) {
  return a.contradiction==b.contradiction &&
    same_range(a.variables,b.variables,[](const auto& x,const auto& y) {return x.name==y.name && x.type==y.type;}) &&
    same_range(a.atoms,b.atoms,[](const auto& x,const auto& y) {
      return x.occurrence==y.occurrence && x.table==y.table &&
          same_range(x.terms,y.terms,[](const auto& c,const auto& d) {return same_term(c,d);});
    }) && same_range(a.head,b.head,[](const auto& x,const auto& y) {return x.variable==y.variable && x.alias==y.alias;});
}
// Claim metadata and ordering are part of this exact tree comparison.
template<class A,class B> bool same_tree(const A& a,const B& b) {
  return a.root==b.root && equal_optional_items(a.claimed_connex,b.claimed_connex) && a.claimed_native_height==b.claimed_native_height &&
    same_range(a.nodes,b.nodes,[](const auto& x,const auto& y) {
      return x.id==y.id && x.kind==y.kind && equal_items(x.scope,y.scope) && equal_items(x.children,y.children) &&
          x.occurrence==y.occurrence && equal_optional_items(x.claimed_separator,y.claimed_separator);
    });
}
void binding(const runtime::CompiledProgram& plan,const planner::SearchBinding& value) {
  require(value.valid() && same_catalog(plan.catalog(),value.catalog()) && same_query(plan.query(),value.query()),
      "explain_binding","height evidence is not bound to the exact original core catalog/query");
}
void context(const runtime::CompiledProgram& plan,const planner::CandidateContext& value) {
  const auto& policy=plan.options().policy;
  require(value.updates==planner::CandidateUpdateProfile::mixed_full_row_set_v1 &&
      value.arithmetic==policy.arithmetic && value.planner==policy.planner &&
      value.optimization==policy.optimization && value.cost_model==policy.cost_model &&
      value.canonicalization=="structural-tree-key-v1","explain_context","candidate context differs from selected physical policy");
}
std::optional<planner::VerifiedOptimum> proof(const HeightEvidence& evidence) {
  if (const auto* value=std::get_if<planner::VerifiedOptimum>(&evidence)) return *value;
  if (const auto* value=std::get_if<planner::MinimumHeightCandidate>(&evidence)) return value->original_proof();
  return {};
}
}
struct ModeDescriptor::Data {
  runtime::CompiledProgram plan;
  bool running=false;
  std::uint64_t owner=0,sequence=0;
  std::optional<runtime::DeltaState> state;
  RuntimePresence presence=RuntimePresence::compile_only;
  std::optional<runtime::DeltaOptions> options;
  std::optional<runtime::DeltaRuntimeProfile> profile;
  explicit Data(runtime::CompiledProgram value):plan(std::move(value)) {}
};
ModeDescriptor::ModeDescriptor(std::shared_ptr<const Data> value):data_(std::move(value)) {}
const ModeDescriptor::Data& ModeDescriptor::data() const { require(bool(data_),"invalid_explanation","moved-from mode descriptor"); return *data_; }
ModeDescriptor ModeDescriptor::compile_only(PhysicalPlan plan) {
  // Compiler-only reports own standalone immutable metadata. Runtime captures
  // instead share the query program and its original account/finite grant.
  auto account=resource::MemoryAccount::create(UINT64_MAX);
  storage::IndexWorkAllowance work(storage::IndexWork{UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX,UINT64_MAX});
  auto compiled=runtime::CompiledProgram::freeze(account,plan,&work);
  return ModeDescriptor(resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::capture,6},account,
      resource::MemoryPurpose::capture,std::move(compiled)));
}
ModeDescriptor ModeDescriptor::compile_only(runtime::CompiledProgram plan) {
  const auto account=plan.account();
  return ModeDescriptor(resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::capture,6},account,
      resource::MemoryPurpose::capture,std::move(plan)));
}
ModeDescriptor ModeDescriptor::capture(const runtime::DeltaRuntime& runtime) {
  const auto account=runtime.compiled_program().account();
  auto result=resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::capture,6},account,
      resource::MemoryPurpose::capture,runtime.compiled_program());result->running=true;result->presence=RuntimePresence::live;
  result->owner=runtime.owner().value; result->sequence=runtime.sequence(); result->state=runtime.state();
  result->options=runtime.options(); result->profile=runtime.profile();
  return ModeDescriptor(std::move(result));
}
ModeDescriptor ModeDescriptor::capture(const runtime::QuerySession& session) {
  const auto meta=session.report_metadata();const auto status=session.status();
  return from_session(meta,status);
}
// running records retained native state; a stopped session can still have it.
// Lifecycle presence remains a separate current/retained metadata field.
ModeDescriptor ModeDescriptor::from_session(const runtime::SessionReportMetadata& meta,const runtime::SessionStatus& status) {
  auto result=resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::capture,6},meta.plan().account(),
      resource::MemoryPurpose::capture,meta.plan());result->running=meta.state().has_value();
  result->owner=meta.owner().value;result->sequence=meta.sequence();result->state=meta.state();
  result->options=meta.options();result->profile=meta.profile();
  result->presence=status.state==runtime::SessionState::dropped?RuntimePresence::released:
      status.state==runtime::SessionState::stopped?RuntimePresence::stopped_retained:RuntimePresence::live;
  return ModeDescriptor(std::move(result));
}
const runtime::CompiledProgram& ModeDescriptor::plan() const { return data().plan; }
bool ModeDescriptor::running() const { return data().running; }
std::uint64_t ModeDescriptor::owner() const { return data().owner; }
std::uint64_t ModeDescriptor::sequence() const { return data().sequence; }
std::optional<runtime::DeltaState> ModeDescriptor::state() const { return data().state; }
RuntimePresence ModeDescriptor::presence() const { return data().presence; }
const std::optional<runtime::DeltaOptions>& ModeDescriptor::options() const { return data().options; }
const std::optional<runtime::DeltaRuntimeProfile>& ModeDescriptor::profile() const { return data().profile; }
struct PlanExplanation::Data {
  ModeDescriptor mode;
  HeightEvidence evidence;
  std::optional<planner::CandidateSnapshot> family;
  std::optional<runtime::ObservationSnapshot> observation;
  ExplanationKind kind=ExplanationKind::physical;
  GaugeAvailability gauge_availability=GaugeAvailability::compile_only;
  std::optional<runtime::CapturedStateGauges> gauges;
  std::optional<runtime::CursorObservation> cursor;
  std::optional<runtime::SessionStatus> session;
  runtime::CapturedTraceRecords trace;
  HeightStatus status=HeightStatus::checked_upper;
  std::size_t height=0;
  Data(ModeDescriptor m,HeightEvidence e,std::optional<planner::CandidateSnapshot> f,
      std::optional<runtime::ObservationSnapshot> o):mode(std::move(m)),evidence(std::move(e)),family(std::move(f)),observation(std::move(o)),
      trace(resource::OwnerAllocator<runtime::TraceRecord>(mode.plan().account(),resource::MemoryPurpose::capture,{resource::MemoryOwnerKind::capture,3})) {}
};
PlanExplanation::PlanExplanation(std::shared_ptr<const Data> value):data_(std::move(value)) {}
const PlanExplanation::Data& PlanExplanation::data() const { require(bool(data_),"invalid_explanation","moved-from plan explanation"); return *data_; }
PlanExplanation PlanExplanation::make(ModeDescriptor mode,HeightEvidence evidence,
    std::optional<planner::CandidateSnapshot> family,std::optional<runtime::ObservationSnapshot> observation,ExplainLimits limits,
    ExplanationKind kind,GaugeAvailability gauge_availability,std::optional<runtime::CapturedStateGauges> gauges,
    std::optional<runtime::CursorObservation> cursor,std::optional<runtime::SessionStatus> session,
    runtime::CapturedTraceRecords trace) {
  const auto& plan=mode.plan();
  require(plan.tree().nodes.size()<=limits.nodes,"resource_limit","EXPLAIN node limit exceeded");
  require(plan.validation().valid && plan.validation().native_height.has_value(),"explain_plan","physical plan has no checked height");
  // P08's immutable handle is the authority for validity. No report or imported
  // JSON validation flag can enter this factory in its place.
  // A minimum proof binds the original query and height; its witness may differ.
  // An explicit incumbent/candidate must also match the actual selected tree.
  std::visit([&](const auto& value) {
    using T=std::decay_t<decltype(value)>;
    if constexpr (!std::is_same_v<T,std::monostate>) {
      require(value.valid(),"explain_evidence","moved-from height evidence");
      if constexpr (std::is_same_v<T,planner::MinimumHeightCandidate>) {
        binding(plan,value.original_proof().binding()); context(plan,value.context());
        require(same_tree(plan.tree(),value.tree()),"explain_candidate","candidate is not the selected tree");
      } else binding(plan,value.binding());
      if constexpr (std::is_same_v<T,planner::ValidatedIncumbent>)
        require(same_tree(plan.tree(),value.tree()),"explain_upper","incumbent is not the selected tree");
      require(value.height()==*plan.validation().native_height,"explain_height","evidence and selected height differ");
    }
  },evidence);
  if (const auto original=proof(evidence))
    require(original->upper().tree().nodes.size()<=limits.nodes,"resource_limit","EXPLAIN original witness node limit exceeded");
  if (family) {
    require(family->valid(),"explain_family","moved-from candidate family");
    const auto original=proof(evidence);
    require(original.has_value(),"explain_family","family metadata requires explicit original minimum-height evidence");
    binding(plan,family->original_proof().binding()); context(plan,family->context());
    require(family->original_proof().height()==original->height(),"explain_family","family proof height differs");
    if (const auto* selected=std::get_if<planner::MinimumHeightCandidate>(&evidence))
      require(family->family()==selected->provenance().family,"explain_family","candidate and reported family differ");
  }
  const auto account=plan.account();
  auto result=resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::capture,7},account,resource::MemoryPurpose::capture,
      std::move(mode),std::move(evidence),std::move(family),std::move(observation));
  result->kind=kind;result->gauge_availability=gauge_availability;result->gauges=std::move(gauges);
  result->cursor=std::move(cursor);result->session=std::move(session);
  // Keep the receiving trace allocator when no funded incoming vector exists.
  if(trace.get_allocator().account())result->trace=std::move(trace);
  result->height=*result->mode.plan().validation().native_height;
  if(result->mode.plan().route()==PhysicalRoute::constant_false && std::holds_alternative<std::monostate>(result->evidence))
    result->status=HeightStatus::checked_constant_operator;
  if (proof(result->evidence)) result->status=HeightStatus::verified_original_minimum;
  return PlanExplanation(std::move(result));
}
PlanExplanation PlanExplanation::create(PhysicalPlan plan,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  return make(ModeDescriptor::compile_only(std::move(plan)),std::move(evidence),std::move(family),{},limits);
}
PlanExplanation PlanExplanation::create(runtime::CompiledProgram plan,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  return make(ModeDescriptor::compile_only(std::move(plan)),std::move(evidence),std::move(family),{},limits);
}
PlanExplanation PlanExplanation::capture(const runtime::DeltaRuntime& runtime,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  require(runtime.workload_statistics_options().mode==runtime::workload::Mode::off,
      "explain_statistics_version","C01 collection requires StatisticsExplanation; legacy v2 omits this instrumentation");
  // Caller serializes capture with owner advance, mode changes, drains and callbacks.
  auto mode=ModeDescriptor::capture(runtime); auto trace=runtime.capture_observation_trace();
  auto observation=std::move(trace.snapshot);
  require(observation.options==runtime.options().physical.support.observation,"explain_mode","runtime observation options differ");
  const auto state=runtime.state();
  const bool private_work=state!=runtime::DeltaState::ready && state!=runtime::DeltaState::committed_output;
  // Legacy gauges read node/base table sizes into funded arrays, not row payloads.
  // This diagnostic work precedes make() node-limit admission and has no work grant.
  std::optional<runtime::CapturedStateGauges> gauges;
  if(!private_work)gauges=runtime.capture_state_gauges();
  auto cursor=runtime.last_cursor_observation();
  return make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits,
      ExplanationKind::runtime,private_work?GaugeAvailability::pending_private_state:GaugeAvailability::available,
      std::move(gauges),std::move(cursor),{},std::move(trace.records));
}
PlanExplanation PlanExplanation::capture(const runtime::QuerySession& session,HeightEvidence evidence,
    std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  require(session.workload_statistics_options().mode==runtime::workload::Mode::off,
      "explain_statistics_version","C01 collection requires StatisticsExplanation; legacy v2 omits this instrumentation");
  auto mode=ModeDescriptor::capture(session);auto trace=session.capture_observation_trace();
  auto observation=std::move(trace.snapshot);
  auto status=session.status();auto gauges=session.capture_state_gauges();auto cursor=session.last_cursor_observation();
  const auto availability=gauges?GaugeAvailability::available:
      status.state==runtime::SessionState::dropped?GaugeAvailability::runtime_released:GaugeAvailability::pending_private_state;
  return make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits,
      ExplanationKind::session,availability,std::move(gauges),std::move(cursor),status,std::move(trace.records));
}
const runtime::CapturedTraceRecords& PlanExplanation::trace_records() const { return data().trace; }
PlanExplanation PlanExplanation::capture_statistics_context(const runtime::DeltaRuntime& runtime,ExplainLimits limits) {
  auto mode=ModeDescriptor::capture(runtime);auto trace=runtime.capture_observation_trace();
  require(trace.snapshot.options==runtime.options().physical.support.observation,"explain_mode","runtime observation options differ");
  const auto state=runtime.state();const bool pending=state!=runtime::DeltaState::ready && state!=runtime::DeltaState::committed_output;
  // Skip legacy node/base gauge traversal; v3 admits its own state-capture work.
  // Trace ownership remains captured here; this context is never serialized v2.
  return make(std::move(mode),{},{},std::move(trace.snapshot),limits,ExplanationKind::runtime,
      pending?GaugeAvailability::pending_private_state:GaugeAvailability::available,
      {},runtime.last_cursor_observation(),{},std::move(trace.records));
}
ExplanationKind PlanExplanation::kind() const { return data().kind; }
GaugeAvailability PlanExplanation::gauge_availability() const { return data().gauge_availability; }
const std::optional<runtime::CapturedStateGauges>& PlanExplanation::gauges() const { return data().gauges; }
const std::optional<runtime::CursorObservation>& PlanExplanation::cursor() const { return data().cursor; }
const std::optional<runtime::SessionStatus>& PlanExplanation::session_status() const { return data().session; }
const runtime::CompiledProgram& PlanExplanation::plan() const { return data().mode.plan(); }
const ModeDescriptor& PlanExplanation::mode() const { return data().mode; }
HeightStatus PlanExplanation::height_status() const { return data().status; }
std::size_t PlanExplanation::selected_height() const { return data().height; }
const HeightEvidence& PlanExplanation::evidence() const { return data().evidence; }
std::optional<planner::VerifiedOptimum> PlanExplanation::optimum() const { return proof(data().evidence); }
const std::optional<planner::CandidateSnapshot>& PlanExplanation::family() const { return data().family; }
const std::optional<runtime::ObservationSnapshot>& PlanExplanation::observation() const { return data().observation; }
} // namespace crown::observability
