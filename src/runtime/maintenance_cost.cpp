#include "crown/runtime/maintenance_cost.hpp"
#include "../planner/ranking_detail.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>
#include <bit>
#include <cmath>
#include <numeric>

namespace crown::runtime::cost {
namespace rd = ::crown::planner::ranking::detail;
namespace detail {
inline constexpr resource::MemoryAttribution memory_owner{resource::MemoryOwnerKind::capture,42};
template<class T> auto allocator(const resource::MemoryAccount& a) {
  return resource::OwnerAllocator<T>(a,resource::MemoryPurpose::capture,memory_owner);
}
struct CalibrationData {
  resource::OwnerText context,backend;
  std::array<std::optional<Coefficient>,component_count> coefficients;
  CalibrationOrigin origin{CalibrationOrigin::isolated_measurement_ratios};
  std::optional<FitSummary> summary;
  pr::ScoreVector<FitObservation> observations;
  explicit CalibrationData(const resource::MemoryAccount& a):context(allocator<char>(a)),backend(allocator<char>(a)),observations(allocator<FitObservation>(a)) {}
};
struct ProfileData {
  planner::MinimumHeightCandidate candidate;
  runtime::ranking::RuntimeEvidence evidence;
  resource::MemoryStatistics memory;
};
struct ResultData {
  Calibration calibration;
  pr::ScoreVector<CandidateEstimate> candidates;
  pr::ScoreVector<InputDemand> input;
  OutputDemand output;
  pr::Usage usage;
  ResultData(const resource::MemoryAccount& a,Calibration c,OutputDemand o)
      :calibration(std::move(c)),candidates(allocator<CandidateEstimate>(a)),input(allocator<InputDemand>(a)),output(o) {}
};
struct Factory {
  static Calibration calibration(std::shared_ptr<const CalibrationData> p){return Calibration(std::move(p));}
  static Profile profile(std::shared_ptr<const ProfileData> p){return Profile(std::move(p));}
  static Result result(std::shared_ptr<const ResultData> p){return Result(std::move(p));}
};
}
const std::array<std::optional<Coefficient>,component_count>& Calibration::coefficients() const noexcept{return data_->coefficients;}
std::string_view Calibration::context() const noexcept{return data_->context;}
std::string_view Calibration::backend() const noexcept{return data_->backend;}
CalibrationOrigin Calibration::origin() const noexcept{return data_->origin;}
const std::optional<FitSummary>& Calibration::fit_summary() const noexcept{return data_->summary;}
std::span<const FitObservation> Calibration::fit_observations() const noexcept{return data_->observations;}
const planner::MinimumHeightCandidate& Profile::candidate() const noexcept{return data_->candidate;}
const runtime::ranking::RuntimeEvidence& Profile::evidence() const noexcept{return data_->evidence;}
const resource::MemoryStatistics& Profile::memory_at_capture() const noexcept{return data_->memory;}
CandidateEstimate::CandidateEstimate(const resource::MemoryAccount& a,planner::MinimumHeightCandidate c)
    :candidate(std::move(c)),terms(detail::allocator<Term>(a)) {}
const pr::ScoreVector<CandidateEstimate>& Result::candidates() const noexcept{return data_->candidates;}
const Calibration& Result::calibration() const noexcept{return data_->calibration;}
const pr::Usage& Result::usage() const noexcept{return data_->usage;}
std::span<const InputDemand> Result::input_demand() const noexcept{return data_->input;}
const OutputDemand& Result::output_demand() const noexcept{return data_->output;}
std::string_view component_name(Component c) noexcept {
  constexpr std::array<std::string_view,component_count> names{"base_input","base_change","adapter_visit",
    "derivation_change","survivor_transition","parent_count_update","parent_presence_transition","visible_count_update","visible_presence_transition","edge_lookup",
    "native_bucket_touch","generalized_hit","annotation_change","snapshot_start","snapshot_row",
    "snapshot_end","delta_start","delta_row","delta_end","encoded_byte","checkpoint_start","checkpoint_byte"};
  const auto i=static_cast<std::size_t>(c);return i<names.size()?names[i]:"invalid";
}
namespace {
void require(bool value,pr::Stop stop=pr::Stop::invalid_limits){if(!value)throw rd::Failure{stop};}
U64 add(U64 a,U64 b) {require(b<=UINT64_MAX-a,pr::Stop::bit_limit);return a+b;}
U64 multiply(U64 a,U64 b) {require(!a || b<=UINT64_MAX/a,pr::Stop::bit_limit);return a*b;}
Ratio ratio(U64 n,U64 d=1) {require(d!=0);const auto g=std::gcd(n,d);return {n/g,d/g};}
Ratio times(Ratio a,Ratio b) {
  const auto x=std::gcd(a.numerator,b.denominator),y=std::gcd(b.numerator,a.denominator);
  return ratio(multiply(a.numerator/x,b.numerator/y),multiply(a.denominator/y,b.denominator/x));
}
Ratio plus(Ratio a,Ratio b) {
  const auto g=std::gcd(a.denominator,b.denominator);
  const auto n=add(multiply(a.numerator,b.denominator/g),multiply(b.numerator,a.denominator/g));
  // Cancel before the final denominator multiplication.
  const auto h=std::gcd(n,g);return {n/h,multiply(a.denominator/g,b.denominator/h)};
}
void check_bits(Ratio value,const rd::Budget& budget) {
  require(static_cast<unsigned>(std::bit_width(value.numerator))<=budget.limits.score_bits &&
      static_cast<unsigned>(std::bit_width(value.denominator))<=budget.limits.score_bits,pr::Stop::bit_limit);
}
bool same_candidate(const planner::MinimumHeightCandidate& a,const planner::MinimumHeightCandidate& b,rd::Budget& budget) {
  return a.valid() && b.valid() && rd::equal_bytes(a.structural_key(),b.structural_key(),budget);
}
template<class Append> void components(const workload::Descriptor& descriptor,const workload::Cell& cell,Append append) {
  switch(descriptor.kind) {
    case workload::Kind::physical:append(Component::base_input,cell.inputs);append(Component::base_change,cell.changed);break;
    case workload::Kind::occurrence:append(Component::adapter_visit,cell.visited);break;
    case workload::Kind::support:
      if(descriptor.role==workload::Role::derivation)append(Component::derivation_change,cell.changes);
      else if(descriptor.role==workload::Role::survivor)append(Component::survivor_transition,cell.changes);
      else if(descriptor.role==workload::Role::parent_support){append(Component::parent_count_update,cell.changes);append(Component::parent_presence_transition,add(cell.zero_to_positive,cell.positive_to_zero));}
      else if(descriptor.role==workload::Role::visible_support){append(Component::visible_count_update,cell.changes);append(Component::visible_presence_transition,add(cell.zero_to_positive,cell.positive_to_zero));}
      else throw rd::Failure{pr::Stop::binding_mismatch};
      break;
    case workload::Kind::degree:
      append(Component::edge_lookup,cell.count);
      append(descriptor.role==workload::Role::native_touched_degree?Component::native_bucket_touch:Component::generalized_hit,cell.sum);break;
    case workload::Kind::logical:throw rd::Failure{pr::Stop::binding_mismatch};
  }
}
template<class Owner> CaptureAttempt capture_impl(const planner::CandidateSnapshot& snapshot,std::size_t index,const Owner& owner,pr::Limits limits) noexcept {
  // Explicit cold diagnostic: capture and re-lower against the actual owner.
  // Query updates do not execute this account/capture/binding scan.
  CaptureAttempt out;std::optional<rd::Budget> budget;
  try {
    require(snapshot.valid(),pr::Stop::invalid_handle);const auto candidate=snapshot.candidate(index);require(candidate.has_value(),pr::Stop::invalid_handle);
    // Read the operator account before allocating this profiling evidence.
    const auto memory=owner.accounted_memory_statistics();
    resource::MemoryStatistics actual;
    if constexpr(std::is_same_v<Owner,QuerySession>){require(memory.has_value(),pr::Stop::evidence_unavailable);actual=*memory;}
    else actual=memory;
    runtime::ranking::CaptureOptions options;options.source_cardinalities=false;options.processing=limits;
    const auto captured=runtime::ranking::capture(snapshot,owner,options);out.usage=captured.usage;
    if(!captured.evidence){out.stop=captured.stop;return out;}
    const auto& evidence=*captured.evidence;const auto& plan=evidence.inputs().plan();
    budget.emplace(limits,captured.usage,plan.account());auto& b=*budget;
    require(evidence.captured().has_value() && !evidence.captured()->workload().pending(),pr::Stop::evidence_unavailable);
    program::ReplanLimits repl;
    repl.physical.work_limit=limits.lowering_work-b.usage.lowering_work;
    repl.physical.identity.work_limit=limits.identity_work-b.usage.identity_work;
    repl.binding_replay_work=limits.binding_replay_work-b.usage.binding_replay_work;
    repl.normalization_work=limits.normalization_work-b.usage.normalization_work;
    const auto prior=b.usage;
    b.usage.lowering_work=limits.lowering_work;b.usage.identity_work=limits.identity_work;
    b.usage.binding_replay_work=limits.binding_replay_work;b.usage.normalization_work=limits.normalization_work;
    const auto checked=CompiledProgram::replan(plan,*candidate,repl);
    require(rd::equal_bytes(checked.physical_sha256(),plan.physical_sha256(),b),pr::Stop::binding_mismatch);
    b.usage.lowering_work=prior.lowering_work;b.usage.identity_work=prior.identity_work;
    rd::Budget::add(b.usage.lowering_work,checked.work(),limits.lowering_work,pr::Stop::lowering_limit);
    rd::Budget::add(b.usage.identity_work,checked.identity().work,limits.identity_work,pr::Stop::lowering_limit);
    b.usage.binding_replay_work=prior.binding_replay_work;b.usage.normalization_work=prior.normalization_work;
    if(checked.normalized()) {
      rd::Budget::add(b.usage.binding_replay_work,checked.normalized()->binding.work,limits.binding_replay_work,pr::Stop::lowering_limit);
      rd::Budget::add(b.usage.normalization_work,checked.normalized()->work,limits.normalization_work,pr::Stop::lowering_limit);
    }
    b.bytes(sizeof(detail::ProfileData));b.work();
    auto data=resource::make_accounted_shared<detail::ProfileData>(detail::memory_owner,plan.account(),resource::MemoryPurpose::capture,
        detail::ProfileData{*candidate,evidence,actual});
    b.time();out.profile=detail::Factory::profile(std::move(data));out.stop=pr::Stop::complete;
  }catch(const rd::Failure& e){out.stop=e.stop;}
   catch(const program::ReplanFailure& e){out.stop=e.fault()==program::ReplanFault::binding?pr::Stop::binding_mismatch:pr::Stop::lowering_limit;}
   catch(const std::bad_alloc&){out.stop=pr::Stop::allocation_failure;}
   catch(...){out.stop=pr::Stop::internal_error;}
  if(budget)out.usage=budget->usage;
  return out;
}
enum class Group { maintenance,snapshot,delta,encoding,checkpoint,annotation,count };
Group group(Component c) {
  if(c==Component::annotation_change)return Group::annotation;
  if(c>=Component::snapshot_start && c<=Component::snapshot_end)return Group::snapshot;
  if(c>=Component::delta_start && c<=Component::delta_end)return Group::delta;
  if(c==Component::encoded_byte)return Group::encoding;
  if(c>=Component::checkpoint_start)return Group::checkpoint;
  return Group::maintenance;
}
struct Sums {std::array<Ratio,static_cast<std::size_t>(Group::count)> values{};std::array<bool,static_cast<std::size_t>(Group::count)> unknown{};};
void term(CandidateEstimate& out,Sums& sums,const Calibration& calibration,Component component,
    std::optional<Ratio> units,Confidence confidence,Issues issues,rd::Budget& budget,std::optional<std::size_t> descriptor={}) {
  budget.work();
  Term value{component,descriptor,units,{},confidence,issues};
  if(units && units->numerator==0)value.nanoseconds=Ratio{};
  else if(units) {
    const auto& coefficient=calibration.coefficients()[static_cast<std::size_t>(component)];
    if(coefficient)value.nanoseconds=times(*units,coefficient->nanoseconds_per_unit);
    else value.issues|=issue(Issue::calibration_missing);
  }
  for(const auto& amount:{value.units,value.nanoseconds})if(amount)check_bits(*amount,budget);
  out.issues|=value.issues;const auto g=static_cast<std::size_t>(group(component));
  if(value.nanoseconds){sums.values[g]=plus(sums.values[g],*value.nanoseconds);check_bits(sums.values[g],budget);}
  else sums.unknown[g]=true;
  out.terms.push_back(value);
}
U64 demanded(std::span<const InputDemand> demand,const workload::Descriptor& descriptor,rd::Budget& budget) {
  for(const auto& d:demand){budget.work();if(d.table.value==descriptor.table && d.operation==descriptor.operation)return d.inputs;}
  throw rd::Failure{pr::Stop::binding_mismatch};
}
std::optional<std::size_t> root_descriptor(const workload::Snapshot& snapshot,const workload::Descriptor& d,rd::Budget& budget) {
  const auto descriptors=snapshot.descriptors();
  for(std::size_t i=0;i<descriptors.size();++i){budget.work();const auto& x=descriptors[i];
    if(x.kind==workload::Kind::physical && x.table==d.table && x.operation==d.operation)return i;}
  return {};
}
void evaluate(CandidateEstimate& out,const Profile& profile,const Calibration& calibration,const Request& request,rd::Budget& budget) {
  // Price immutable stratum observations under caller demand assumptions.
  // Descriptor/root/demand searches are linear; this is not an update hook.
  const auto& evidence=profile.evidence();const auto& snapshot=evidence.captured()->workload();
  out.observations=profile;
  const auto descriptors=snapshot.descriptors();const auto cells=snapshot.cells();
  require(descriptors.size()==cells.size(),pr::Stop::binding_mismatch);
  out.observed_stamp=snapshot.stamp();out.observed_modes=snapshot.modes();out.memory_at_capture=profile.memory_at_capture();
  out.memory_budget_bytes=request.memory_budget_bytes;
  if(profile.memory_at_capture().current.requested_bytes>request.memory_budget_bytes)out.issues|=issue(Issue::memory_budget);
  if(calibration.backend()!=evidence.inputs().plan().guarantee().storage_backend)out.issues|=issue(Issue::calibration_backend);
  if(calibration.fit_summary() && calibration.fit_summary()->options.modes &&
      *calibration.fit_summary()->options.modes!=snapshot.modes())out.issues|=issue(Issue::calibration_mode);
  if(request.output.delta_epochs || request.output.delta_rows) {
    if(!snapshot.modes().delta_owner || snapshot.modes().resolved_mode!=DeltaMode::delta)out.issues|=issue(Issue::incompatible_output_mode);
  }
  Sums sums;
  std::size_t term_count=10;
  if(descriptors.empty())term_count=static_cast<std::size_t>(add(term_count,multiply(request.input.size(),2)));
  for(const auto& descriptor:descriptors){budget.work();const bool two=descriptor.kind==workload::Kind::physical || descriptor.kind==workload::Kind::degree ||
      descriptor.role==workload::Role::parent_support || descriptor.role==workload::Role::visible_support;
    term_count=static_cast<std::size_t>(add(term_count,two?2:1));}
  budget.vector_items<Term>(term_count);out.terms.reserve(term_count);
  if(descriptors.empty()) {
    for(const auto& demand:request.input) {
      const Confidence unavailable{Basis::observed_census,workload::Availability::disabled,0,0};
      term(out,sums,calibration,Component::base_input,ratio(demand.inputs),unavailable,0,budget);
      term(out,sums,calibration,Component::base_change,demand.inputs?std::nullopt:std::optional<Ratio>{Ratio{}},unavailable,
          demand.inputs?issue(Issue::detail_unavailable):0,budget);
    }
  }
  for(std::size_t i=0;i<descriptors.size();++i) {
    budget.work();const auto& descriptor=descriptors[i];const auto& cell=cells[i];
    require(descriptor.input_scope==workload::InputScope::physical_table,pr::Stop::binding_mismatch);
    const auto inputs=demanded(request.input,descriptor,budget);const auto root=root_descriptor(snapshot,descriptor,budget);
    require(root.has_value(),pr::Stop::binding_mismatch);const auto& base=cells[*root];
    const bool census=descriptor.kind==workload::Kind::physical;
    const auto available=census?(evidence.inputs().depth_reasons()==0?workload::Availability::exact:workload::Availability::unavailable):snapshot.detail_availability();
    const auto denominator=census?base.inputs:base.complete_detail_inputs;
    const bool usable=(available==workload::Availability::exact || available==workload::Availability::sampled) && !cell.saturated && !base.saturated && denominator;
    auto append=[&](Component component,U64 events,bool direct=false) {
      Confidence confidence{direct?Basis::declared_demand:census?Basis::observed_census:Basis::observed_complete_detail,available,denominator,events};
      std::optional<Ratio> units;Issues issues=0;
      if(!inputs)units=Ratio{};
      else if(direct)units=ratio(inputs);
      else if(usable)units=times(ratio(events,denominator),ratio(inputs));
      else issues=issue(denominator?Issue::detail_unavailable:Issue::stratum_unobserved);
      term(out,sums,calibration,component,units,confidence,issues,budget,i);
    };
    // count is the event multiset; sum is conditional on actual events.
    components(descriptor,cell,[&](Component c,U64 n){append(c,n,c==Component::base_input);});
  }
  const auto& output=request.output;
  const Confidence assumed{Basis::declared_demand,workload::Availability::unavailable,0,0};
  auto output_term=[&](Component c,U64 n){term(out,sums,calibration,c,ratio(n),assumed,0,budget);};
  output_term(Component::annotation_change,output.annotation_changes);
  output_term(Component::snapshot_start,output.snapshot_requests);
  output_term(Component::snapshot_row,output.snapshot_rows_total?*output.snapshot_rows_total:multiply(output.snapshot_requests,output.snapshot_rows_per_request));
  output_term(Component::snapshot_end,output.snapshot_requests);
  output_term(Component::delta_start,output.delta_epochs);output_term(Component::delta_row,output.delta_rows);output_term(Component::delta_end,output.delta_epochs);
  output_term(Component::encoded_byte,output.encoded_bytes);
  output_term(Component::checkpoint_start,output.checkpoint_requests);output_term(Component::checkpoint_byte,output.checkpoint_bytes);
  const auto finish=[&](Group g)->std::optional<Ratio>{const auto index=static_cast<std::size_t>(g);return sums.unknown[index]?std::nullopt:std::optional<Ratio>{sums.values[index]};};
  out.maintenance_ns=finish(Group::maintenance);out.snapshot_ns=finish(Group::snapshot);out.delta_ns=finish(Group::delta);
  out.encoding_ns=finish(Group::encoding);out.checkpoint_ns=finish(Group::checkpoint);out.annotation_ns=finish(Group::annotation);
  if(out.issues==0 && std::none_of(sums.unknown.begin(),sums.unknown.end(),[](bool x){return x;})) {
    Ratio total;for(const auto& value:sums.values){total=plus(total,value);check_bits(total,budget);}out.total_ns=total;
  }
}
}
FeatureAttempt features(const workload::Snapshot& snapshot,pr::Limits limits) noexcept {
  FeatureAttempt out;std::optional<rd::Budget> budget;
  try {
    budget.emplace(limits);auto& b=*budget;b.work();const auto& stamp=snapshot.stamp();
    require(!snapshot.pending() && snapshot.detail_availability()==workload::Availability::exact &&
        !stamp.reset_saturated && !stamp.configuration_saturated && !stamp.segment_saturated,pr::Stop::evidence_unavailable);
    FeatureCensus result;result.stamp=stamp;result.modes=snapshot.modes();
    const auto descriptors=snapshot.descriptors();const auto cells=snapshot.cells();require(descriptors.size()==cells.size(),pr::Stop::binding_mismatch);
    for(std::size_t i=0;i<descriptors.size();++i){b.work();require(descriptors[i].input_scope==workload::InputScope::physical_table,pr::Stop::binding_mismatch);
      components(descriptors[i],cells[i],[&](Component c,U64 n){b.work();auto& value=result.units[static_cast<std::size_t>(c)];value=add(value,n);});}
    b.time();out.census=result;out.stop=pr::Stop::complete;
  }catch(const rd::Failure& e){out.stop=e.stop;}
   catch(...){out.stop=pr::Stop::internal_error;}
  if(budget)out.usage=budget->usage;
  return out;
}
CalibrationAttempt calibrate(const resource::MemoryAccount& account,std::string_view context,std::string_view backend,
    std::span<const CalibrationSample> samples,pr::Limits limits) noexcept {
  CalibrationAttempt out;std::optional<rd::Budget> budget;
  try {
    budget.emplace(limits,pr::Usage{},account);auto& b=*budget;require(bool(account) && !context.empty() && !backend.empty());
    b.bytes(sizeof(detail::CalibrationData));b.bytes(context.size());b.bytes(backend.size());b.work(context.size()+backend.size());
    auto data=resource::make_accounted_shared<detail::CalibrationData>(detail::memory_owner,account,resource::MemoryPurpose::capture,account);
    data->context.assign(context);data->backend.assign(backend);
    for(const auto& sample:samples) {
      b.work();const auto index=static_cast<std::size_t>(sample.component);require(index<component_count && sample.units && sample.elapsed_ns);
      auto& value=data->coefficients[index];if(!value)value=Coefficient{};
      value->samples=add(value->samples,1);value->units=add(value->units,sample.units);value->elapsed_ns=add(value->elapsed_ns,sample.elapsed_ns);
      value->nanoseconds_per_unit=ratio(value->elapsed_ns,value->units);
      check_bits(value->nanoseconds_per_unit,b);
    }
    b.time();out.calibration=detail::Factory::calibration(std::move(data));out.stop=pr::Stop::complete;
  }catch(const rd::Failure& e){out.stop=e.stop;}
   catch(const std::bad_alloc&){out.stop=pr::Stop::allocation_failure;}
   catch(...){out.stop=pr::Stop::internal_error;}
  if(budget)out.usage=budget->usage;
  return out;
}
CalibrationAttempt fit(const resource::MemoryAccount& account,std::string_view context,std::string_view backend,
    std::span<const FitObservation> observations,const FitOptions& options,pr::Limits limits) noexcept {
  // Floating fitting is an inference over caller timings. Published rates are
  // quantized exact ratios; rank and residuals do not certify future accuracy.
  CalibrationAttempt out;std::optional<rd::Budget> budget;
  try {
    budget.emplace(limits,pr::Usage{},account);auto& b=*budget;
    require(bool(account) && !context.empty() && !backend.empty() && !observations.empty());
    require(options.max_iterations && options.quantization_denominator && options.ridge.denominator &&
        std::isfinite(options.relative_tolerance) && options.relative_tolerance>0 &&
        std::isfinite(options.rank_tolerance) && options.rank_tolerance>0 && options.rank_tolerance<1);
    b.bytes(sizeof(detail::CalibrationData));b.bytes(context.size());b.bytes(backend.size());b.work(context.size()+backend.size());
    b.vector_items<FitObservation>(observations.size());
    auto data=resource::make_accounted_shared<detail::CalibrationData>(detail::memory_owner,account,resource::MemoryPurpose::capture,account);
    data->context.assign(context);data->backend.assign(backend);data->origin=CalibrationOrigin::fitted_linear_assumption;
    data->observations.assign(observations.begin(),observations.end());
    FitSummary summary;summary.options=options;summary.observations=observations.size();
    using Column=std::array<double,component_count>;
    std::array<Column,component_count> gram{};
    Column norm{},rhs{},beta{};
    std::array<U64,component_count> units{},samples{};
    for(const auto& observation:observations) {
      b.work();summary.total_elapsed_ns=add(summary.total_elapsed_ns,observation.elapsed_ns);
      bool any=false;
      for(std::size_t j=0;j<component_count;++j){b.work();const auto x=static_cast<double>(observation.units[j]);any=any || observation.units[j]!=0;
        units[j]=add(units[j],observation.units[j]);if(observation.units[j])samples[j]=add(samples[j],1);
        rhs[j]+=x*static_cast<double>(observation.elapsed_ns);
        for(std::size_t k=0;k<=j;++k){b.work();gram[j][k]+=x*static_cast<double>(observation.units[k]);}}
      require(any);
    }
    for(std::size_t j=0;j<component_count;++j){b.work();norm[j]=std::sqrt(gram[j][j]);
      if(norm[j]>0){++summary.observed_features;rhs[j]/=norm[j];}
      for(std::size_t k=0;k<j;++k)gram[k][j]=gram[j][k];}
    for(std::size_t j=0;j<component_count;++j)for(std::size_t k=0;k<component_count;++k){b.work();
      gram[j][k]=norm[j]>0 && norm[k]>0?gram[j][k]/norm[j]/norm[k]:0;
      require(std::isfinite(gram[j][k]) && std::isfinite(rhs[j]),pr::Stop::bit_limit);}
    // Numerical rank uses the unregularized normalized design Gram matrix.
    // Its tolerance/algorithm are retained; this is not an exact rank proof.
    auto elimination=gram;std::size_t row=0;
    for(std::size_t column=0;column<component_count && row<component_count;++column) {
      std::size_t pivot=row;
      for(std::size_t r=row;r<component_count;++r){b.work();if(std::abs(elimination[r][column])>std::abs(elimination[pivot][column]))pivot=r;}
      if(std::abs(elimination[pivot][column])<=options.rank_tolerance)continue;
      std::swap(elimination[row],elimination[pivot]);const auto divisor=elimination[row][column];
      for(std::size_t k=column;k<component_count;++k){b.work();elimination[row][k]/=divisor;}
      for(std::size_t r=row+1;r<component_count;++r){const auto multiple=elimination[r][column];
        for(std::size_t k=column;k<component_count;++k){b.work();elimination[r][k]-=multiple*elimination[row][k];}}
      ++row;
    }
    summary.numerical_rank=row;summary.underdetermined=row<summary.observed_features;
    const auto ridge=static_cast<double>(options.ridge.numerator)/static_cast<double>(options.ridge.denominator);
    bool converged=false;
    for(std::size_t iteration=0;iteration<options.max_iterations;++iteration) {
      double change=0,magnitude=1;
      for(std::size_t j=0;j<component_count;++j){b.work();if(norm[j]==0)continue;
        auto residual=rhs[j];
        for(std::size_t k=0;k<component_count;++k){b.work();if(k!=j)residual-=gram[j][k]*beta[k];}
        const auto next=std::max(0.0,residual/(gram[j][j]+ridge));require(std::isfinite(next),pr::Stop::bit_limit);
        change=std::max(change,std::abs(next-beta[j]));magnitude=std::max(magnitude,next);beta[j]=next;
      }
      summary.iterations=iteration+1;
      if(change<=options.relative_tolerance*magnitude){converged=true;break;}
    }
    require(converged,pr::Stop::work_limit);
    for(std::size_t j=0;j<component_count;++j){b.work();if(norm[j]==0)continue;
      const auto scaled=static_cast<long double>(beta[j]/norm[j])*static_cast<long double>(options.quantization_denominator);
      const auto rounded=std::floor(scaled+0.5L);
      require(std::isfinite(rounded) && rounded>=0 && rounded<std::ldexp(1.0L,64),pr::Stop::bit_limit);
      const auto rate=ratio(static_cast<U64>(rounded),options.quantization_denominator);check_bits(rate,b);
      data->coefficients[j]=Coefficient{rate,samples[j],units[j],0};
    }
    long double squared_error=0;
    for(const auto& observation:observations){b.work();long double predicted=0;
      for(std::size_t j=0;j<component_count;++j){b.work();if(data->coefficients[j]){
        const auto rate=data->coefficients[j]->nanoseconds_per_unit;
        predicted+=static_cast<long double>(observation.units[j])*static_cast<long double>(rate.numerator)/static_cast<long double>(rate.denominator);}}
      const auto error=predicted-static_cast<long double>(observation.elapsed_ns);squared_error+=error*error;
      summary.maximum_absolute_error_ns=std::max(summary.maximum_absolute_error_ns,static_cast<double>(std::abs(error)));
    }
    summary.root_mean_square_error_ns=static_cast<double>(std::sqrt(squared_error/static_cast<long double>(observations.size())));
    require(std::isfinite(summary.root_mean_square_error_ns) && std::isfinite(summary.maximum_absolute_error_ns),pr::Stop::bit_limit);
    data->summary=summary;b.time();out.calibration=detail::Factory::calibration(std::move(data));out.stop=pr::Stop::complete;
  }catch(const rd::Failure& e){out.stop=e.stop;}
   catch(const std::bad_alloc&){out.stop=pr::Stop::allocation_failure;}
   catch(...){out.stop=pr::Stop::internal_error;}
  if(budget)out.usage=budget->usage;
  return out;
}
CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const PhysicalRuntime& o,pr::Limits l) noexcept{return capture_impl(s,i,o,l);}
CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const DeltaRuntime& o,pr::Limits l) noexcept{return capture_impl(s,i,o,l);}
CaptureAttempt capture(const planner::CandidateSnapshot& s,std::size_t i,const QuerySession& o,pr::Limits l) noexcept{return capture_impl(s,i,o,l);}
runtime::ranking::Revalidation revalidate(const Profile& p,const PhysicalRuntime& o) noexcept{return runtime::ranking::revalidate(p.evidence(),o);}
runtime::ranking::Revalidation revalidate(const Profile& p,const DeltaRuntime& o) noexcept{return runtime::ranking::revalidate(p.evidence(),o);}
runtime::ranking::Revalidation revalidate(const Profile& p,const QuerySession& o) noexcept{return runtime::ranking::revalidate(p.evidence(),o);}
Attempt estimate(const resource::MemoryAccount& account,const planner::CandidateSnapshot& snapshot,
    std::span<const Profile> profiles,const Calibration& calibration,const Request& request) noexcept {
  // Build the complete receiving-account result privately. The existing outer
  // noexcept boundary returns stops; no query state needs local rollback.
  Attempt out;std::optional<rd::Budget> budget;
  try {
    budget.emplace(request.limits,pr::Usage{},account);auto& b=*budget;
    require(bool(account) && request.memory_budget_bytes>0);require(snapshot.valid(),pr::Stop::invalid_handle);
    const auto count=snapshot.candidate_count();require(count<=request.limits.candidates,pr::Stop::candidate_limit);
    require(count!=0,pr::Stop::no_candidates);const auto first=snapshot.candidate(0);require(first.has_value(),pr::Stop::invalid_handle);
    // Source catalog can include physical SQL tables not used by the core CQ.
    require(request.input.size()%2==0,pr::Stop::binding_mismatch);
    const auto tables=request.input.size()/2;
    for(const auto& p:profiles){b.work();const auto& plan=p.evidence().inputs().plan();
      require(plan.source_catalog().tables.size()==tables,pr::Stop::binding_mismatch);
      const auto& first_plan=profiles.front().evidence().inputs().plan();
      require(rd::equal_bytes(plan.physical_source_sha256(),first_plan.physical_source_sha256(),b) &&
          rd::equal_bytes(plan.identity().semantic_sha256,first_plan.identity().semantic_sha256,b) &&
          rd::equal_bytes(plan.identity().output_contract_sha256,first_plan.identity().output_contract_sha256,b),pr::Stop::binding_mismatch);
    }
    for(const auto& profile:profiles) {
      bool member=false;
      for(std::size_t i=0;i<count;++i){b.work();const auto candidate=snapshot.candidate(i);require(candidate.has_value(),pr::Stop::invalid_handle);
        if(same_candidate(*candidate,profile.candidate(),b))member=true;}
      require(member,pr::Stop::binding_mismatch);
    }
    for(std::size_t i=0;i<request.input.size();++i){b.work();const auto& d=request.input[i];
      require(d.table.value<tables && (d.operation==workload::Operation::insert || d.operation==workload::Operation::erase),pr::Stop::binding_mismatch);
      for(std::size_t j=0;j<i;++j){b.work();require(d.table!=request.input[j].table || d.operation!=request.input[j].operation,pr::Stop::binding_mismatch);}}
    b.bytes(sizeof(detail::ResultData));b.vector_items<InputDemand>(request.input.size());b.vector_items<CandidateEstimate>(count);
    auto data=resource::make_accounted_shared<detail::ResultData>(detail::memory_owner,account,resource::MemoryPurpose::capture,account,calibration,request.output);
    data->input.assign(request.input.begin(),request.input.end());data->candidates.reserve(count);
    for(std::size_t i=0;i<count;++i) {
      b.work();const auto candidate=snapshot.candidate(i);require(candidate.has_value(),pr::Stop::invalid_handle);
      const Profile* profile=nullptr;
      for(const auto& p:profiles){b.work();if(same_candidate(*candidate,p.candidate(),b)){require(!profile,pr::Stop::binding_mismatch);profile=&p;}}
      data->candidates.emplace_back(account,*candidate);auto& value=data->candidates.back();value.memory_budget_bytes=request.memory_budget_bytes;
      if(!profile){value.issues=issue(Issue::profile_missing);continue;}
      // Catalog/query equality, not a structural key alone, grants binding.
      auto a=rd::binding(candidate->catalog(),candidate->query(),b,account);
      auto z=rd::binding(profile->evidence().inputs().plan().catalog(),profile->evidence().inputs().plan().query(),b,account);
      require(rd::equal_bytes(a,z,b),pr::Stop::binding_mismatch);
      evaluate(value,*profile,calibration,request,b);
    }
    b.time();data->usage=b.usage;out.result=detail::Factory::result(std::move(data));out.stop=pr::Stop::complete;
  }catch(const rd::Failure& e){out.stop=e.stop;}
   catch(const std::bad_alloc&){out.stop=pr::Stop::allocation_failure;}
   catch(...){out.stop=pr::Stop::internal_error;}
  if(budget)out.usage=budget->usage;
  return out;
}
} // namespace crown::runtime::cost
