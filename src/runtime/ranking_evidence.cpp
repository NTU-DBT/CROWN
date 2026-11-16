#include "crown/runtime/ranking_evidence.hpp"
#include "ranking_evidence_detail.hpp"
#include "../planner/ranking_detail.hpp"
#include "crown/api/error.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>
#include <array>
#include <new>

namespace crown::runtime::ranking {
namespace rd=::crown::planner::ranking::detail;
namespace detail {
struct OwnerAccess {
  static const CompiledProgram& program(const PhysicalRuntime& owner) {return owner.compiled_program();}
  static const CompiledProgram& program(const DeltaRuntime& owner) {return owner.compiled_program();}
};
struct Data {
  pr::Evidence inputs;
  std::optional<statistics::CombinedCapture> captured;
  std::optional<SessionStatisticsContext> session;
  Data(pr::Evidence value,std::optional<statistics::CombinedCapture> c,std::optional<SessionStatisticsContext> s)
      :inputs(std::move(value)),captured(std::move(c)),session(std::move(s)) {}
};
struct Factory {static RuntimeEvidence make(std::shared_ptr<const Data> value){return RuntimeEvidence(std::move(value));}};
}
const pr::Evidence& RuntimeEvidence::inputs() const noexcept{return data_->inputs;}
const std::optional<statistics::CombinedCapture>& RuntimeEvidence::captured() const noexcept{return data_->captured;}
const std::optional<SessionStatisticsContext>& RuntimeEvidence::session_context() const noexcept{return data_->session;}
namespace {
using pr::Reason;using pr::Reasons;using pr::reason;
template<class T> using Scratch=std::vector<T,resource::MemoryAllocator<T>>;
template<class T> resource::MemoryAllocator<T> scratch_allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account,resource::MemoryPurpose::scratch,rd::evidence_memory_owner);
}
void require(bool value,pr::Stop stop=pr::Stop::internal_error){if(!value){throw rd::Failure{stop};}}
CompiledProgram actual_plan(const PhysicalRuntime& owner){return detail::OwnerAccess::program(owner);}
CompiledProgram actual_plan(const DeltaRuntime& owner){return detail::OwnerAccess::program(owner);}
CompiledProgram actual_plan(const QuerySession& owner){return owner.report_metadata().plan();}
struct NativeCapture {std::optional<statistics::CombinedCapture> combined;std::optional<SessionStatisticsContext> session;};
NativeCapture actual_capture(const PhysicalRuntime& owner,statistics::OwnerRequestView r,statistics::Limits l){return {owner.capture_combined_statistics_view(r,l),{}};}
NativeCapture actual_capture(const DeltaRuntime& owner,statistics::OwnerRequestView r,statistics::Limits l){return {owner.capture_combined_statistics_view(r,l),{}};}
NativeCapture actual_capture(const QuerySession& owner,statistics::OwnerRequestView r,statistics::Limits l){
  auto context=owner.capture_statistics_context_view(r,l);return {context.combined(),std::move(context)};
}
std::optional<statistics::Freshness> actual_freshness(const PhysicalRuntime& owner,const statistics::OwnerCapture& c){return owner.statistics_freshness(c,0);}
std::optional<statistics::Freshness> actual_freshness(const DeltaRuntime& owner,const statistics::OwnerCapture& c){return owner.statistics_freshness(c,0);}
std::optional<statistics::Freshness> actual_freshness(const QuerySession& owner,const statistics::OwnerCapture& c){return owner.statistics_freshness(c,0);}
pr::ModeIdentity modes(const workload::ModeFacts& m) {
  return {m.delta_owner,static_cast<std::uint64_t>(m.requested_mode),static_cast<std::uint64_t>(m.resolved_mode),
    static_cast<std::uint64_t>(m.requested_completion),static_cast<std::uint64_t>(m.resolved_completion),
    static_cast<std::uint64_t>(m.live_maintenance),static_cast<std::uint64_t>(m.view)};
}
pr::EvidenceIdentity identity(const statistics::CombinedCapture& c) {
  const auto& s=c.workload().stamp();const auto& o=c.workload().options();
  return {s.owner.value,s.committed_epoch,s.interval_start_epoch,s.reset_generation,s.configuration_generation,s.segment,s.format_version,
    static_cast<std::uint64_t>(o.mode),static_cast<std::uint64_t>(o.max_cells),o.period,o.offset,o.detail_budget,modes(c.workload().modes()),
    c.workload().pending(),s.reset_saturated,s.configuration_saturated,s.segment_saturated};
}
Reasons interval_saturated(const workload::Snapshot& s){const auto& x=s.stamp();return x.reset_saturated || x.configuration_saturated || x.segment_saturated?reason(Reason::interval_saturated):0;}
using Census=detail::Census;
Census census(const workload::Snapshot& s,rd::Budget& b) {
  // Exact input census uses all physical roots, including no-ops. Numeric
  // reasons preserve unavailable facts; they never create a height proof.
  const auto account=s.plan().account();Census out(account);
  if(s.options().mode==workload::Mode::off){out.reasons=reason(Reason::disabled);return out;}
  out.reasons|=interval_saturated(s);
  if(s.pending()){out.reasons|=reason(Reason::pending);}
  const auto& m=s.metadata();if(m.invalid_descriptor || m.protocol_error || m.ordinal_exhausted){out.reasons|=reason(Reason::protocol);}
  const auto tables=s.plan().source_catalog().tables.size();const auto descriptors=s.descriptors();const auto cells=s.cells();
  if(descriptors.size()!=cells.size()){out.reasons|=reason(Reason::root_incomplete);return out;}
  b.vector_items<pr::InputWeight>(tables);b.vector_items<std::array<bool,2>>(tables);b.vector_items<std::size_t>(descriptors.size());
  Scratch<std::array<bool,2>> seen(tables,std::array<bool,2>{},scratch_allocator<std::array<bool,2>>(account));
  Scratch<std::size_t> roots(scratch_allocator<std::size_t>(account));roots.reserve(descriptors.size());out.weights.reserve(tables);
  for(std::size_t t=0;t<tables;++t){b.work();out.weights.push_back({TableId{t},0,0,0,0});}
  bool denominator_overflow=false;
  for(std::size_t i=0;i<descriptors.size();++i){b.work();const auto& d=descriptors[i];if(d.kind!=workload::Kind::physical){continue;}
    if(d.role!=workload::Role::input || d.input_scope!=workload::InputScope::physical_table || d.table>=tables ||
        (d.operation!=workload::Operation::insert && d.operation!=workload::Operation::erase)){
      out.reasons|=reason(Reason::root_incomplete);continue;
    }
    const auto t=static_cast<std::size_t>(d.table);const auto op=d.operation==workload::Operation::insert?std::size_t{0}:std::size_t{1};
    if(seen[t][op]){out.reasons|=reason(Reason::root_incomplete);continue;}
    seen[t][op]=true;roots.push_back(i);const auto& cell=cells[i];auto& w=out.weights[t];
    if(cell.saturated){out.reasons|=reason(Reason::root_saturated);}
    if(cell.changed>cell.inputs || cell.noop!=cell.inputs-cell.changed){out.reasons|=reason(Reason::root_incomplete);}
    if(op==0){w.inserts=cell.inputs;}else{w.erases=cell.inputs;}
    if(cell.inputs>UINT64_MAX-out.total){denominator_overflow=true;}else{out.total+=cell.inputs;}
    if(cell.changed>UINT64_MAX-w.changed || cell.noop>UINT64_MAX-w.noop){out.reasons|=reason(Reason::root_saturated);}
    else{w.changed+=cell.changed;w.noop+=cell.noop;}
  }
  for(const auto& present:seen){b.work();if(!present[0] || !present[1]){out.reasons|=reason(Reason::root_incomplete);}}
  if(denominator_overflow){out.reasons|=reason(Reason::denominator_unavailable);out.total=0;}
  if(!denominator_overflow && out.total==0){out.reasons|=reason(Reason::empty_census);}
  for(const auto i:roots){
    // Native input_share examines every descriptor. Account for that actual
    // scan instead of hiding the repeated native helper calls as O(1).
    b.work(static_cast<std::uint64_t>(descriptors.size()));const auto f=s.input_share(i);
    if(f.denominator_scope!=workload::DenominatorScope::all_committed_physical_inputs || f.numerator!=cells[i].inputs || f.denominator!=out.total){out.reasons|=reason(Reason::denominator_unavailable);}
    if(f.availability!=workload::Availability::exact && out.total!=0){out.reasons|=reason(Reason::denominator_unavailable);}
  }
  return out;
}
struct SourceSelections {
  std::array<statistics::Selection,256> values{};
  std::size_t count{};
  statistics::OwnerRequestView view() const {return statistics::OwnerRequestView(std::span<const statistics::Selection>(values.data(),count));}
};
SourceSelections selections(const CompiledProgram& p,bool wanted,rd::Budget& b,Reasons& reasons) {
  SourceSelections out;
  if(!wanted){reasons=reason(Reason::not_captured);return out;}
  b.vector_items<unsigned char>(p.source_catalog().tables.size());
  Scratch<unsigned char> used(p.source_catalog().tables.size(),0,scratch_allocator<unsigned char>(p.account()));std::size_t count=0;
  for(const auto& input:p.inputs()){b.work();require(input.base.value<used.size());if(!used[input.base.value]){used[input.base.value]=1;++count;}}
  if(count>256){reasons=reason(Reason::source_limit);return out;}
  b.vector_items<statistics::Selection>(count);
  for(std::size_t i=0;i<used.size();++i){b.work();if(used[i]){out.values[out.count++]={statistics::SourceScope{TableId{i}},std::nullopt};}}
  return out;
}
pr::CaptureState capture_state(statistics::Availability a) {
  switch(a){case statistics::Availability::available:return pr::CaptureState::available;
    case statistics::Availability::budget_exhausted:return pr::CaptureState::budget_exhausted;
    case statistics::Availability::pending_private_state:return pr::CaptureState::pending_private_state;
    case statistics::Availability::unavailable:case statistics::Availability::not_applicable:return pr::CaptureState::unavailable;}
  return pr::CaptureState::unavailable;
}
void state(const statistics::CombinedCapture& native,statistics::OwnerRequestView request,rd::EvidenceData& data,rd::Budget& b) {
  const auto& s=native.state();
  data.accounting.state=capture_state(s.availability());data.accounting.requested_components=s.requested_components();data.accounting.returned_components=s.components().size();
  b.vector_items<pr::SourceObservation>(s.components().size());data.source_observations.reserve(s.components().size());
  for(const auto& c:s.components()){
    b.work();const auto* scope=std::get_if<statistics::SourceScope>(&c.selection.scope);
    if(scope){data.source_observations.push_back({scope->table,capture_state(c.availability),c.cardinality});}
    else{data.memory_reasons|=reason(Reason::source_incomplete);}
  }
  if(s.stamp().layer!=statistics::OwnerLayer::physical || s.physical_source_scope()!=statistics::Availability::available){data.memory_reasons|=reason(Reason::source_scope);data.depth_reasons|=reason(Reason::source_scope);}
  if(s.availability()==statistics::Availability::pending_private_state || native.workload().pending()){
    data.memory_reasons|=reason(Reason::pending);data.depth_reasons|=reason(Reason::pending);return;
  }
  if(data.memory_reasons){return;}
  if(s.availability()==statistics::Availability::budget_exhausted){data.memory_reasons|=reason(Reason::source_budget_exhausted);return;}
  if(s.availability()!=statistics::Availability::available || s.requested_components()!=request.selections.size() || s.components().size()!=request.selections.size()){
    data.memory_reasons|=reason(Reason::source_incomplete);return;
  }
  b.vector_items<pr::SourceCardinality>(s.components().size());data.sources.reserve(s.components().size());
  for(std::size_t i=0;i<s.components().size();++i){b.work();const auto& c=s.components()[i];const auto* expected=std::get_if<statistics::SourceScope>(&request.selections[i].scope);const auto* actual=std::get_if<statistics::SourceScope>(&c.selection.scope);
    if(!actual || !expected || actual->table!=expected->table || c.selection.fields || c.availability!=statistics::Availability::available || !c.cardinality){data.memory_reasons|=reason(Reason::source_incomplete);continue;}
    data.sources.push_back({actual->table,*c.cardinality});
  }
}
template<class Owner> CaptureAttempt capture_impl(const planner::CandidateSnapshot& snapshot,const Owner& owner,const CaptureOptions& options) noexcept {
  // Explicit actual-owner diagnostic: bind metadata, capture native facts and
  // fund immutable evidence on that plan account before returning a handle.
  CaptureAttempt result;std::optional<rd::Budget> budget;
  try{
    budget.emplace(options.processing);auto& b=*budget;b.work();require(snapshot.valid(),pr::Stop::invalid_handle);
    const auto proof=snapshot.original_proof();require(proof.valid(),pr::Stop::invalid_handle);const auto original=proof.binding();
    const auto plan=actual_plan(owner);const auto account=plan.account();auto encoded=rd::binding(original.catalog(),original.query(),b,account);
    require(rd::equal_bytes(encoded,rd::binding(plan.catalog(),plan.query(),b,account),b),pr::Stop::binding_mismatch);
    Reasons memory_reasons=0;const auto selected=selections(plan,options.source_cardinalities,b,memory_reasons);const auto request=selected.view();
    b.bytes(sizeof(rd::EvidenceData));b.bytes(sizeof(detail::Data));
    auto native=actual_capture(owner,request,options.state_limits);b.time();
    auto data=resource::make_accounted_shared<rd::EvidenceData>(rd::evidence_memory_owner,account,resource::MemoryPurpose::capture,plan);
    data->binding=std::move(encoded);data->memory_reasons=memory_reasons;data->depth_reasons=0;
    auto& a=data->accounting;a.processing_limits=options.processing;a.state_requested=options.source_cardinalities;a.state_work_limit=options.state_limits.work;a.state_rows_limit=options.state_limits.rows;
    a.state_keys_limit=options.state_limits.distinct_keys;a.state_bytes_limit=options.state_limits.accounted_bytes;
    a.state_projection_width=options.state_limits.projection_width;a.state_heavy_keys=options.state_limits.heavy_keys;
    if(native.combined){
      require(native.combined->state().plan().physical_sha256()==plan.physical_sha256(),pr::Stop::binding_mismatch);
      data->identity=identity(*native.combined);auto weights=census(native.combined->workload(),b);
      data->depth_reasons=weights.reasons;data->denominator=weights.total;data->weights=std::move(weights.weights);
      state(*native.combined,request,*data,b);
      const auto& u=native.combined->state().usage();a.state_work=u.work;a.state_rows=u.rows;a.state_keys=u.distinct_keys;a.state_bytes=u.accounted_bytes;
      a.snapshot_descriptors=native.combined->workload().descriptors().size();a.snapshot_cells=native.combined->workload().cells().size();
    }else{
      data->depth_reasons=reason(Reason::released);data->memory_reasons=reason(Reason::released);
      a.state=pr::CaptureState::released;
      require(native.session.has_value());data->identity.owner=native.session->metadata().owner().value;data->identity.epoch=native.session->metadata().sequence();
    }
    const auto inputs=rd::Factory::evidence(data);
    auto ready=resource::make_accounted_shared<detail::Data>({resource::MemoryOwnerKind::capture,10},account,
        resource::MemoryPurpose::capture,inputs,std::move(native.combined),std::move(native.session));
    b.time();data->preparation=b.usage;
    result.evidence=detail::Factory::make(std::move(ready));
    result.stop=pr::Stop::complete;
  }catch(const rd::Failure& failure){result.stop=failure.stop;}
   catch(const std::bad_alloc&){result.stop=pr::Stop::allocation_failure;}
   catch(...){result.stop=pr::Stop::internal_error;}
  if(budget){result.usage=budget->usage;}
  return result;
}
Reasons freshness(std::optional<statistics::Freshness> f) {
  if(!f){return reason(Reason::released);}
  switch(*f){case statistics::Freshness::current:return 0;
    case statistics::Freshness::within_lag:case statistics::Freshness::stale:return reason(Reason::stale);
    case statistics::Freshness::foreign_owner:return reason(Reason::foreign_owner);
    case statistics::Freshness::future_sequence:return reason(Reason::future_sequence);
    case statistics::Freshness::scope_mismatch:return reason(Reason::layer_mismatch);}
  return reason(Reason::read_failed);
}
template<class Owner> Revalidation revalidate_impl(const RuntimeEvidence& old,const Owner& owner) noexcept {
  // Boundary, depth and memory remain separate. A depth-only census failure
  // must not erase independently valid owner/memory observations.
  Revalidation out{0,old.inputs().depth_reasons(),old.inputs().memory_reasons()};
  try{
    if(!old.captured()){out.boundary=reason(Reason::released);out.depth|=out.boundary;out.memory|=out.boundary;return out;}
    out.boundary=freshness(actual_freshness(owner,old.captured()->state()));
    const auto current=actual_capture(owner,{},statistics::Limits{});
    if(!current.combined){out.boundary|=reason(Reason::released);}
    else{
      const auto& c=*current.combined;
      if(c.state().availability()==statistics::Availability::pending_private_state || c.workload().pending()){out.boundary|=reason(Reason::pending);}
      if(c.state().plan().physical_sha256()!=old.inputs().plan().physical_sha256()){out.boundary|=reason(Reason::source_scope);}
      const auto& a=old.captured()->workload().stamp();const auto& z=c.workload().stamp();
      if(a.owner!=z.owner || a.committed_epoch!=z.committed_epoch || a.interval_start_epoch!=z.interval_start_epoch ||
          a.reset_generation!=z.reset_generation || a.configuration_generation!=z.configuration_generation || a.segment!=z.segment || a.format_version!=z.format_version){out.depth|=reason(Reason::interval_changed);}
      if(old.captured()->workload().options()!=c.workload().options() || old.captured()->workload().modes()!=c.workload().modes()){out.depth|=reason(Reason::mode_changed);}
      out.depth|=interval_saturated(c.workload());
      try{rd::Budget b(pr::Limits{});out.depth|=census(c.workload(),b).reasons;}
      catch(...){out.depth|=reason(Reason::read_failed);}
    }
  }catch(...){out.boundary|=reason(Reason::read_failed);}
  out.depth|=out.boundary;out.memory|=out.boundary;return out;
}
template<class Owner> pr::Attempt current_impl(const planner::CandidateSnapshot& snapshot,const Owner& owner,const pr::Request& request,statistics::Limits state_limits) noexcept {
  if(request.policy==pr::Policy::height_only){
    try{const auto plan=actual_plan(owner);return pr::rank_with_account(plan.account(),snapshot,request);}
    catch(const std::bad_alloc&){return {pr::Stop::allocation_failure,{},{},0,0};}
    catch(...){return {pr::Stop::internal_error,{},{},0,0};}
  }
  CaptureOptions options;options.source_cardinalities=request.policy==pr::Policy::tuple_index_slots;options.state_limits=state_limits;options.processing=request.limits;
  const auto facts=capture_impl(snapshot,owner,options);
  if(!facts.evidence){return {facts.stop,{},facts.usage,0,facts.reasons};}
  return pr::rank(snapshot,request,facts.evidence->inputs());
}
} // namespace
detail::Census detail::classify_census(const workload::Snapshot& s,rd::Budget& b){return census(s,b);}
CaptureAttempt capture(const planner::CandidateSnapshot& s,const PhysicalRuntime& o,const CaptureOptions& l) noexcept{return capture_impl(s,o,l);}
CaptureAttempt capture(const planner::CandidateSnapshot& s,const DeltaRuntime& o,const CaptureOptions& l) noexcept{return capture_impl(s,o,l);}
CaptureAttempt capture(const planner::CandidateSnapshot& s,const QuerySession& o,const CaptureOptions& l) noexcept{return capture_impl(s,o,l);}
Revalidation revalidate(const RuntimeEvidence& e,const PhysicalRuntime& o) noexcept{return revalidate_impl(e,o);}
Revalidation revalidate(const RuntimeEvidence& e,const DeltaRuntime& o) noexcept{return revalidate_impl(e,o);}
Revalidation revalidate(const RuntimeEvidence& e,const QuerySession& o) noexcept{return revalidate_impl(e,o);}
pr::Attempt rank_current(const planner::CandidateSnapshot& s,const PhysicalRuntime& o,const pr::Request& r,statistics::Limits l) noexcept{return current_impl(s,o,r,l);}
pr::Attempt rank_current(const planner::CandidateSnapshot& s,const DeltaRuntime& o,const pr::Request& r,statistics::Limits l) noexcept{return current_impl(s,o,r,l);}
pr::Attempt rank_current(const planner::CandidateSnapshot& s,const QuerySession& o,const pr::Request& r,statistics::Limits l) noexcept{return current_impl(s,o,r,l);}
} // namespace crown::runtime::ranking
