#include "crown/observability/explain.hpp"
#include "crown/api/error.hpp"
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
bool same_constraint(const Constraint& a,const Constraint& b) {
  if (a.index()!=b.index()) return false;
  if (const auto* x=std::get_if<UniqueConstraint>(&a)) {
    const auto& y=std::get<UniqueConstraint>(b);
    return x->name==y.name && x->columns==y.columns && x->status==y.status;
  }
  const auto& x=std::get<ForeignKeyConstraint>(a); const auto& y=std::get<ForeignKeyConstraint>(b);
  return x.name==y.name && x.columns==y.columns && x.status==y.status &&
      x.referenced_table==y.referenced_table && x.referenced_columns==y.referenced_columns;
}
bool same_catalog(const Catalog& a,const Catalog& b) {
  return a.version==b.version && same_range(a.tables,b.tables,[](const Table& x,const Table& y) {
    return x.name==y.name && x.source_schema_version==y.source_schema_version &&
      same_range(x.columns,y.columns,[](const Column& c,const Column& d) {
        return c.name==d.name && c.type==d.type && c.nullable==d.nullable && c.collation==d.collation && c.decimal==d.decimal;
      }) && same_range(x.constraints,y.constraints,same_constraint) &&
      x.statistics.row_count==y.statistics.row_count &&
      same_range(x.statistics.distinct_counts,y.statistics.distinct_counts,[](const DistinctEstimate& c,const DistinctEstimate& d) {
        return c.columns==d.columns && c.estimate==d.estimate;
      }) && same_range(x.key_hints,y.key_hints,[](const KeyHint& c,const KeyHint& d) {
        return c.columns==d.columns && c.reason==d.reason;
      });
  });
}
bool same_term(const Term& a,const Term& b) {
  if (a.index()!=b.index()) return false;
  if (const auto* id=std::get_if<VariableId>(&a)) return *id==std::get<VariableId>(b);
  if (const auto* value=std::get_if<Value>(&a)) return *value==std::get<Value>(b);
  return true; // Both are IgnoredColumn, the third closed variant alternative.
}
bool same_query(const Query& a,const Query& b) {
  return a.contradiction==b.contradiction &&
    same_range(a.variables,b.variables,[](const Variable& x,const Variable& y) { return x.name==y.name && x.type==y.type; }) &&
    same_range(a.atoms,b.atoms,[](const Atom& x,const Atom& y) {
      return x.occurrence==y.occurrence && x.table==y.table && same_range(x.terms,y.terms,same_term);
    }) && same_range(a.head,b.head,[](const Output& x,const Output& y) { return x.variable==y.variable && x.alias==y.alias; });
}
bool same_tree(const FreeConnexTree& a,const FreeConnexTree& b) {
  return a.root==b.root && a.claimed_connex==b.claimed_connex && a.claimed_native_height==b.claimed_native_height &&
    same_range(a.nodes,b.nodes,[](const TreeNode& x,const TreeNode& y) {
      return x.id==y.id && x.kind==y.kind && x.scope==y.scope && x.children==y.children &&
        x.occurrence==y.occurrence && x.claimed_separator==y.claimed_separator;
    });
}
void binding(const PhysicalPlan& plan,const planner::SearchBinding& value) {
  require(value.valid() && same_catalog(plan.catalog(),value.catalog()) && same_query(plan.query(),value.query()),
      "explain_binding","height evidence is not bound to the exact original core catalog/query");
}
void context(const PhysicalPlan& plan,const planner::CandidateContext& value) {
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
  PhysicalPlan plan;
  bool running=false;
  std::uint64_t owner=0,sequence=0;
  std::optional<runtime::DeltaState> state;
  RuntimePresence presence=RuntimePresence::compile_only;
  std::optional<runtime::DeltaOptions> options;
  std::optional<runtime::DeltaRuntimeProfile> profile;
  explicit Data(PhysicalPlan value):plan(std::move(value)) {}
};
ModeDescriptor::ModeDescriptor(std::shared_ptr<const Data> value):data_(std::move(value)) {}
const ModeDescriptor::Data& ModeDescriptor::data() const { require(bool(data_),"invalid_explanation","moved-from mode descriptor"); return *data_; }
ModeDescriptor ModeDescriptor::compile_only(PhysicalPlan plan) { return ModeDescriptor(std::make_shared<const Data>(std::move(plan))); }
ModeDescriptor ModeDescriptor::capture(const runtime::DeltaRuntime& runtime) {
  auto result=std::make_shared<Data>(runtime.plan()); result->running=true; result->presence=RuntimePresence::live;
  result->owner=runtime.owner().value; result->sequence=runtime.sequence(); result->state=runtime.state();
  result->options=runtime.options(); result->profile=runtime.profile();
  return ModeDescriptor(std::move(result));
}
ModeDescriptor ModeDescriptor::capture(const runtime::QuerySession& session) {
  const auto meta=session.report_metadata();const auto status=session.status();
  auto result=std::make_shared<Data>(meta.plan());result->running=meta.state().has_value();
  result->owner=meta.owner().value;result->sequence=meta.sequence();result->state=meta.state();
  result->options=meta.options();result->profile=meta.profile();
  result->presence=status.state==runtime::SessionState::dropped?RuntimePresence::released:
      status.state==runtime::SessionState::stopped?RuntimePresence::stopped_retained:RuntimePresence::live;
  return ModeDescriptor(std::move(result));
}
const PhysicalPlan& ModeDescriptor::plan() const { return data().plan; }
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
  std::optional<runtime::CommittedStateGauges> gauges;
  std::optional<runtime::CursorObservation> cursor;
  std::optional<runtime::SessionStatus> session;
  std::vector<runtime::TraceRecord> trace;
  HeightStatus status=HeightStatus::checked_upper;
  std::size_t height=0;
  Data(ModeDescriptor m,HeightEvidence e,std::optional<planner::CandidateSnapshot> f,
      std::optional<runtime::ObservationSnapshot> o):mode(std::move(m)),evidence(std::move(e)),family(std::move(f)),observation(std::move(o)) {}
};
PlanExplanation::PlanExplanation(std::shared_ptr<const Data> value):data_(std::move(value)) {}
const PlanExplanation::Data& PlanExplanation::data() const { require(bool(data_),"invalid_explanation","moved-from plan explanation"); return *data_; }
PlanExplanation PlanExplanation::make(ModeDescriptor mode,HeightEvidence evidence,
    std::optional<planner::CandidateSnapshot> family,std::optional<runtime::ObservationSnapshot> observation,ExplainLimits limits,
    ExplanationKind kind,GaugeAvailability gauge_availability,std::optional<runtime::CommittedStateGauges> gauges,
    std::optional<runtime::CursorObservation> cursor,std::optional<runtime::SessionStatus> session,
    std::vector<runtime::TraceRecord> trace) {
  const auto& plan=mode.plan();
  require(plan.tree().nodes.size()<=limits.nodes,"resource_limit","EXPLAIN node limit exceeded");
  require(plan.validation().valid && plan.validation().native_height.has_value(),"explain_plan","physical plan has no checked height");
  // P08's immutable handle is the authority for validity. No report or imported
  // JSON validation flag can enter this factory in its place.
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
  }
  auto result=std::make_shared<Data>(std::move(mode),std::move(evidence),std::move(family),std::move(observation));
  result->kind=kind;result->gauge_availability=gauge_availability;result->gauges=std::move(gauges);
  result->cursor=std::move(cursor);result->session=std::move(session);result->trace=std::move(trace);
  result->height=*result->mode.plan().validation().native_height;
  if(result->mode.plan().route()==PhysicalRoute::constant_false && std::holds_alternative<std::monostate>(result->evidence))
    result->status=HeightStatus::checked_constant_operator;
  if (proof(result->evidence)) result->status=HeightStatus::verified_original_minimum;
  return PlanExplanation(std::move(result));
}
PlanExplanation PlanExplanation::create(PhysicalPlan plan,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  return make(ModeDescriptor::compile_only(std::move(plan)),std::move(evidence),std::move(family),{},limits);
}
PlanExplanation PlanExplanation::capture(const runtime::DeltaRuntime& runtime,HeightEvidence evidence,std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  // Exclusive owner call: no advance, mode change, drain, inspection, or callback.
  auto mode=ModeDescriptor::capture(runtime); auto trace=runtime.observation_trace();
  auto observation=std::move(trace.snapshot);
  require(observation.options==runtime.options().physical.support.observation,"explain_mode","runtime observation options differ");
  const auto state=runtime.state();
  const bool private_work=state!=runtime::DeltaState::ready && state!=runtime::DeltaState::committed_output;
  std::optional<runtime::CommittedStateGauges> gauges;
  if(!private_work)gauges=runtime.committed_state_gauges();
  auto cursor=runtime.last_cursor_observation();
  return make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits,
      ExplanationKind::runtime,private_work?GaugeAvailability::pending_private_state:GaugeAvailability::available,
      std::move(gauges),std::move(cursor),{},std::move(trace.records));
}
PlanExplanation PlanExplanation::capture(const runtime::QuerySession& session,HeightEvidence evidence,
    std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  auto mode=ModeDescriptor::capture(session);auto trace=session.observation_trace();
  auto observation=std::move(trace.snapshot);
  auto status=session.status();auto gauges=session.report_gauges();auto cursor=session.last_cursor_observation();
  const auto availability=gauges?GaugeAvailability::available:
      status.state==runtime::SessionState::dropped?GaugeAvailability::runtime_released:GaugeAvailability::pending_private_state;
  return make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits,
      ExplanationKind::session,availability,std::move(gauges),std::move(cursor),status,std::move(trace.records));
}
const std::vector<runtime::TraceRecord>& PlanExplanation::trace_records() const { return data().trace; }
ExplanationKind PlanExplanation::kind() const { return data().kind; }
GaugeAvailability PlanExplanation::gauge_availability() const { return data().gauge_availability; }
const std::optional<runtime::CommittedStateGauges>& PlanExplanation::gauges() const { return data().gauges; }
const std::optional<runtime::CursorObservation>& PlanExplanation::cursor() const { return data().cursor; }
const std::optional<runtime::SessionStatus>& PlanExplanation::session_status() const { return data().session; }
const PhysicalPlan& PlanExplanation::plan() const { return data().mode.plan(); }
const ModeDescriptor& PlanExplanation::mode() const { return data().mode; }
HeightStatus PlanExplanation::height_status() const { return data().status; }
std::size_t PlanExplanation::selected_height() const { return data().height; }
const HeightEvidence& PlanExplanation::evidence() const { return data().evidence; }
std::optional<planner::VerifiedOptimum> PlanExplanation::optimum() const { return proof(data().evidence); }
const std::optional<planner::CandidateSnapshot>& PlanExplanation::family() const { return data().family; }
const std::optional<runtime::ObservationSnapshot>& PlanExplanation::observation() const { return data().observation; }
} // namespace crown::observability
