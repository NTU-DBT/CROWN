from pathlib import Path
import hashlib,json
H=Path(__file__).resolve().parent;R=H.parents[2];V=H.parent
roots=[V/'o07-cursor-observation-proposal/overlay',V/'o07-run-context-proposal/overlay',V/'o07-mode-binding-proposal/overlay',V/'o07-runtime-proposal/overlay',V/'o07-explain-proposal/overlay',V/'o07-query-explain-proposal/overlay',R]
paths=['include/crown/runtime/session.hpp','src/runtime/session.cpp','include/crown/observability/explain.hpp','src/observability/explain.cpp','include/crown/io/explain.hpp','src/io/explain.cpp']
pins={}
for rel in paths:
 src=next(p/rel for p in roots if (p/rel).is_file());dst=H/'overlay'/rel;dst.parent.mkdir(parents=True,exist_ok=True);dst.write_bytes(src.read_bytes())
for name in ['o07-runtime-proposal','o07-mode-binding-proposal','o07-explain-proposal','o07-run-context-proposal','o07-cursor-observation-proposal','o07-query-explain-proposal']:
 for p in (V/name/'overlay').rglob('*'):
  if p.is_file():pins[str(p.relative_to(R))]=hashlib.sha256(p.read_bytes()).hexdigest()
 baseline=V/name/'baseline-sha256.json'
 if baseline.is_file():pins.update(json.loads(baseline.read_text()))
(H/'baseline-sha256.json').write_text(json.dumps(pins,indent=2)+'\n')
def edit(rel,old,new):
 p=H/'overlay'/rel;s=p.read_text();assert old in s,(rel,old[:100]);p.write_text(s.replace(old,new))
session='include/crown/runtime/session.hpp'
edit(session,'// Synchronous, creator-thread writer ownership.','''// Immutable metadata-only handle, created by a real session. PhysicalPlan owns
// compiled schema/tree metadata, never runtime tables, rows, journals or leases.
class SessionReportMetadata {
 public:
  SessionReportMetadata(const SessionReportMetadata&) noexcept = default;
  SessionReportMetadata& operator=(const SessionReportMetadata&) noexcept = default;
  [[nodiscard]] const PhysicalPlan& plan() const noexcept { return plan_; }
  [[nodiscard]] const DeltaOptions& options() const noexcept { return options_; }
  [[nodiscard]] const DeltaRuntimeProfile& profile() const noexcept { return profile_; }
  [[nodiscard]] SupportOwnerId owner() const noexcept { return owner_; }
  [[nodiscard]] std::uint64_t sequence() const noexcept { return sequence_; }
  [[nodiscard]] std::optional<DeltaState> state() const noexcept { return state_; }
 private:
  friend class QuerySession;
  SessionReportMetadata(PhysicalPlan plan,DeltaOptions options,DeltaRuntimeProfile profile,
      SupportOwnerId owner,std::uint64_t sequence,std::optional<DeltaState> state) noexcept
      :plan_(std::move(plan)),options_(options),profile_(profile),owner_(owner),sequence_(sequence),state_(state) {}
  PhysicalPlan plan_;
  DeltaOptions options_;
  DeltaRuntimeProfile profile_;
  SupportOwnerId owner_;
  std::uint64_t sequence_;
  std::optional<DeltaState> state_;
};

// Synchronous, creator-thread writer ownership.''')
edit(session,'  [[nodiscard]] SessionStatus status() const;','''  [[nodiscard]] SessionStatus status() const;
  [[nodiscard]] SessionReportMetadata report_metadata() const;
  // Null while private session work exists or after runtime release. This
  // explicit allocating committed read never advances/drains the session.
  [[nodiscard]] std::optional<CommittedStateGauges> report_gauges() const;''')
p='src/runtime/session.cpp'
edit(p,'  ObservationSnapshot retained_observation;','  ObservationSnapshot retained_observation;\n  std::optional<SessionReportMetadata> retained_report_metadata;')
edit(p,'    reader.emplace(*input,runtime->plan().source_catalog(),std::move(options.input));','    reader.emplace(*input,runtime->plan().source_catalog(),std::move(options.input));\n    retain_report_metadata();')
edit(p,'        limits,options.input.limits);','        limits,options.input.limits);\n    retain_report_metadata();')
edit(p,'  void retain_observation() noexcept {','''  void retain_report_metadata() noexcept {
    if(runtime)retained_report_metadata=SessionReportMetadata(runtime->plan(),runtime->options(),
        runtime->profile(),runtime->owner(),runtime->sequence(),runtime->state());
  }
  void retain_observation() noexcept {
    retain_report_metadata();''')
edit(p,'std::optional<CursorObservation> QuerySession::last_cursor_observation() const {','''SessionReportMetadata QuerySession::report_metadata() const {
  auto& d=*data_;Impl::Guard guard(d);
  if(d.runtime)return SessionReportMetadata(d.runtime->plan(),d.runtime->options(),
      d.runtime->profile(),d.runtime->owner(),d.runtime->sequence(),d.runtime->state());
  const auto& saved=*d.retained_report_metadata;
  return SessionReportMetadata(saved.plan(),saved.options(),saved.profile(),saved.owner(),saved.sequence(),{});
}
std::optional<CommittedStateGauges> QuerySession::report_gauges() const {
  auto& d=*data_;Impl::Guard guard(d);
  if(!d.runtime || d.has_private())return {};
  return d.runtime->committed_state_gauges();
}
std::optional<CursorObservation> QuerySession::last_cursor_observation() const {''')
p='include/crown/observability/explain.hpp'
edit(p,'#include "crown/runtime/delta.hpp"','#include "crown/runtime/session.hpp"')
edit(p,'// Mode identity is captured from a real runtime. It is not a history of prior\n// attempts: the current observation overlay has no per-attempt mode generation.','''enum class RuntimePresence { compile_only, live, stopped_retained, released };
enum class ExplanationKind { physical, runtime, session };
enum class GaugeAvailability { available, compile_only, pending_private_state, runtime_released };
// Current/retained owner configuration is separate from immutable begin-bound
// attempt configuration. No arbitrary public metadata constructor exists.''')
edit(p,'  [[nodiscard]] static ModeDescriptor capture(const runtime::DeltaRuntime&);','  [[nodiscard]] static ModeDescriptor capture(const runtime::DeltaRuntime&);\n  [[nodiscard]] static ModeDescriptor capture(const runtime::QuerySession&);')
edit(p,'  [[nodiscard]] runtime::DeltaState state() const;','  [[nodiscard]] std::optional<runtime::DeltaState> state() const;\n  [[nodiscard]] RuntimePresence presence() const;')
edit(p,'  [[nodiscard]] static PlanExplanation capture(const runtime::DeltaRuntime&,HeightEvidence={},\n      std::optional<planner::CandidateSnapshot> family={},ExplainLimits={});','''  [[nodiscard]] static PlanExplanation capture(const runtime::DeltaRuntime&,HeightEvidence={},
      std::optional<planner::CandidateSnapshot> family={},ExplainLimits={});
  // Uses the session's actual owning typed plan; no supplied-plan/hash join.
  [[nodiscard]] static PlanExplanation capture(const runtime::QuerySession&,HeightEvidence={},
      std::optional<planner::CandidateSnapshot> family={},ExplainLimits={});''')
edit(p,'  [[nodiscard]] const PhysicalPlan& plan() const;\n  [[nodiscard]] const ModeDescriptor& mode() const;','''  [[nodiscard]] const PhysicalPlan& plan() const;
  [[nodiscard]] ExplanationKind kind() const;
  [[nodiscard]] GaugeAvailability gauge_availability() const;
  [[nodiscard]] const std::optional<runtime::CommittedStateGauges>& gauges() const;
  [[nodiscard]] const std::optional<runtime::CursorObservation>& cursor() const;
  [[nodiscard]] const std::optional<runtime::SessionStatus>& session_status() const;
  [[nodiscard]] const ModeDescriptor& mode() const;''')
edit(p,'std::optional<planner::CandidateSnapshot>,std::optional<runtime::ObservationSnapshot>,ExplainLimits);','''std::optional<planner::CandidateSnapshot>,std::optional<runtime::ObservationSnapshot>,ExplainLimits,
      ExplanationKind=ExplanationKind::physical,GaugeAvailability=GaugeAvailability::compile_only,
      std::optional<runtime::CommittedStateGauges>={},std::optional<runtime::CursorObservation>={},
      std::optional<runtime::SessionStatus>={});''')
p='src/observability/explain.cpp'
edit(p,'  runtime::DeltaState state=runtime::DeltaState::ready;','  std::optional<runtime::DeltaState> state;\n  RuntimePresence presence=RuntimePresence::compile_only;')
edit(p,'  auto result=std::make_shared<Data>(runtime.plan()); result->running=true;','  auto result=std::make_shared<Data>(runtime.plan()); result->running=true; result->presence=RuntimePresence::live;')
edit(p,'const PhysicalPlan& ModeDescriptor::plan() const {','''ModeDescriptor ModeDescriptor::capture(const runtime::QuerySession& session) {
  const auto meta=session.report_metadata();const auto status=session.status();
  auto result=std::make_shared<Data>(meta.plan());result->running=meta.state().has_value();
  result->owner=meta.owner().value;result->sequence=meta.sequence();result->state=meta.state();
  result->options=meta.options();result->profile=meta.profile();
  result->presence=status.state==runtime::SessionState::dropped?RuntimePresence::released:
      status.state==runtime::SessionState::stopped?RuntimePresence::stopped_retained:RuntimePresence::live;
  return ModeDescriptor(std::move(result));
}
const PhysicalPlan& ModeDescriptor::plan() const {''')
edit(p,'runtime::DeltaState ModeDescriptor::state() const { return data().state; }','std::optional<runtime::DeltaState> ModeDescriptor::state() const { return data().state; }\nRuntimePresence ModeDescriptor::presence() const { return data().presence; }')
edit(p,'  std::optional<runtime::ObservationSnapshot> observation;','''  std::optional<runtime::ObservationSnapshot> observation;
  ExplanationKind kind=ExplanationKind::physical;
  GaugeAvailability gauge_availability=GaugeAvailability::compile_only;
  std::optional<runtime::CommittedStateGauges> gauges;
  std::optional<runtime::CursorObservation> cursor;
  std::optional<runtime::SessionStatus> session;''')
edit(p,'    std::optional<planner::CandidateSnapshot> family,std::optional<runtime::ObservationSnapshot> observation,ExplainLimits limits) {','''    std::optional<planner::CandidateSnapshot> family,std::optional<runtime::ObservationSnapshot> observation,ExplainLimits limits,
    ExplanationKind kind,GaugeAvailability gauge_availability,std::optional<runtime::CommittedStateGauges> gauges,
    std::optional<runtime::CursorObservation> cursor,std::optional<runtime::SessionStatus> session) {''')
edit(p,'  result->height=*result->mode.plan().validation().native_height;','''  result->kind=kind;result->gauge_availability=gauge_availability;result->gauges=std::move(gauges);
  result->cursor=std::move(cursor);result->session=std::move(session);
  result->height=*result->mode.plan().validation().native_height;''')
edit(p,'  return make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits);','''  const auto state=runtime.state();
  const bool private_work=state!=runtime::DeltaState::ready && state!=runtime::DeltaState::committed_output;
  std::optional<runtime::CommittedStateGauges> gauges;
  if(!private_work)gauges=runtime.committed_state_gauges();
  auto cursor=runtime.last_cursor_observation();
  return make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits,
      ExplanationKind::runtime,private_work?GaugeAvailability::pending_private_state:GaugeAvailability::available,
      std::move(gauges),std::move(cursor));''')
edit(p,'const PhysicalPlan& PlanExplanation::plan() const {','''PlanExplanation PlanExplanation::capture(const runtime::QuerySession& session,HeightEvidence evidence,
    std::optional<planner::CandidateSnapshot> family,ExplainLimits limits) {
  auto mode=ModeDescriptor::capture(session);auto observation=session.observations();
  auto status=session.status();auto gauges=session.report_gauges();auto cursor=session.last_cursor_observation();
  const auto availability=gauges?GaugeAvailability::available:
      status.state==runtime::SessionState::dropped?GaugeAvailability::runtime_released:GaugeAvailability::pending_private_state;
  return make(std::move(mode),std::move(evidence),std::move(family),std::move(observation),limits,
      ExplanationKind::session,availability,std::move(gauges),std::move(cursor),status);
}
ExplanationKind PlanExplanation::kind() const { return data().kind; }
GaugeAvailability PlanExplanation::gauge_availability() const { return data().gauge_availability; }
const std::optional<runtime::CommittedStateGauges>& PlanExplanation::gauges() const { return data().gauges; }
const std::optional<runtime::CursorObservation>& PlanExplanation::cursor() const { return data().cursor; }
const std::optional<runtime::SessionStatus>& PlanExplanation::session_status() const { return data().session; }
const PhysicalPlan& PlanExplanation::plan() const {''')
p='include/crown/io/explain.hpp'
edit(p,'#include "crown/observability/explain.hpp"','#include "crown/observability/explain.hpp"\n#include "crown/observability/query_explain.hpp"')
edit(p,'} // namespace crown::io','''[[nodiscard]] std::string write_explain_tree_json(const observability::PlanExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_json(const observability::QueryExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_text(const observability::QueryExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_dot(const observability::QueryExplanation&,ExplainTextLimits={});
[[nodiscard]] std::string write_explain_tree_json(const observability::QueryExplanation&,ExplainTextLimits={});
} // namespace crown::io''')
