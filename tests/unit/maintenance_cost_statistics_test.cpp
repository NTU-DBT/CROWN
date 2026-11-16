#include "ranking_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "crown/runtime/maintenance_cost.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <array>
#include <iostream>

namespace {
using namespace c02_test;
namespace cost=runtime::cost;
namespace ws=runtime::workload;
using C=cost::Component;
using Ratio=cost::Ratio;
std::vector<cost::CalibrationSample> rates() {
  std::vector<cost::CalibrationSample> result;
  for(std::size_t i=0;i<cost::component_count;++i)result.push_back({static_cast<C>(i),1,1});
  return result;
}
std::vector<cost::InputDemand> demand(std::uint64_t inserts,std::uint64_t erases=0) {
  return {{{0},ws::Operation::insert,inserts},{{0},ws::Operation::erase,erases},
    {{1},ws::Operation::insert,0},{{1},ws::Operation::erase,0},{{2},ws::Operation::insert,0},{{2},ws::Operation::erase,0}};
}
std::size_t native_index(const planner::CandidateSnapshot& set) {
  for(std::size_t i=0;i<set.candidate_count();++i)if(shape(set.candidate(i)->tree())==0)return i;
  throw std::runtime_error("native candidate absent");
}
void apply(runtime::PhysicalRuntime& owner,SetOperation operation,std::int64_t value) {
  static_cast<void>(owner.apply({owner.sequence()+1,{0},operation,Row{value}}));
}
void test_backend(bool indexed) {
  const auto f=fixture();const auto set=candidates(f);const auto index=native_index(set);
  const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(index)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
  auto owner=runtime::PhysicalRuntime::initialize(plan,f.database);
  ws::Options options;options.mode=ws::Mode::counters;options.period=2;owner.configure_workload_statistics(options);
  // Global attempts1/3 are sampled and change R. Attempts2/4 are unsampled
  // duplicate no-ops. No S bucket has key2 or3. This is deliberately biased:
  // observed sample support work must not be labelled a population fact.
  apply(owner,SetOperation::insert,2);apply(owner,SetOperation::insert,2);
  apply(owner,SetOperation::insert,3);apply(owner,SetOperation::insert,3);
  const auto captured=cost::capture(set,index,owner);check(captured.profile.has_value(),"sampled native profile missing");
  const auto& snapshot=captured.profile->evidence().captured()->workload();
  check(snapshot.detail_availability()==ws::Availability::sampled,"sampling status lost");
  check(cost::features(snapshot).stop==planner::ranking::Stop::evidence_unavailable,"sampled profile admitted as exact timing features");
  auto account=resource::MemoryAccount::create(32U*1024U*1024U);
  const auto calibration=cost::calibrate(account,"literal unit rates; no performance claim",plan.guarantee().storage_backend,rates());
  check(calibration.calibration.has_value(),"backend calibration failed");
  auto inputs=demand(8);cost::Request request;request.input=inputs;
  const std::array<cost::Profile,1> profiles{*captured.profile};
  const auto attempt=cost::estimate(account,set,profiles,*calibration.calibration,request);
  check(attempt.result.has_value(),"sampled estimate failed");const auto& estimate=attempt.result->candidates()[index];
  // Future8 inputs: base dispatch8, full-census changes(2/4)*8=4,
  // sampled adapter/derivation/survivor/parent-change/parent-crossing/edge
  // work each(2/2)*8=8. Six detail groups48 + census12 =60.
  check(estimate.total_ns==Ratio{60,1} && estimate.maintenance_ns==Ratio{60,1} && estimate.issues==0,"sampled/no-op literal60 forecast differs");
  bool census=false,adapter=false;
  for(const auto& term:estimate.terms)if(term.descriptor) {
    const auto& descriptor=snapshot.descriptors()[*term.descriptor];
    if(descriptor.table!=0 || descriptor.operation!=ws::Operation::insert)continue;
    if(term.component==C::base_change) {
      check(term.units==Ratio{4,1} && term.confidence.basis==cost::Basis::observed_census &&
        term.confidence.availability==ws::Availability::exact && term.confidence.complete_inputs==4 && term.confidence.observed_events==2,"no-ops lost from exact census denominator");census=true;
    }
    if(term.component==C::adapter_visit) {
      check(term.units==Ratio{8,1} && term.confidence.basis==cost::Basis::observed_complete_detail &&
        term.confidence.availability==ws::Availability::sampled && term.confidence.complete_inputs==2 && term.confidence.observed_events==2,"sampled detail denominator/status is not explicit");adapter=true;
    }
  }
  check(census && adapter,"required decomposed confidence terms absent");
  const auto recorded=[&](std::uint64_t period,std::uint64_t offset) {
    auto other=runtime::PhysicalRuntime::initialize(plan,f.database);ws::Options collection;
    collection.mode=ws::Mode::counters;collection.period=period;collection.offset=offset;other.configure_workload_statistics(collection);
    apply(other,SetOperation::insert,2);apply(other,SetOperation::insert,2);
    apply(other,SetOperation::insert,3);apply(other,SetOperation::insert,3);
    const auto capture=cost::capture(set,index,other);check(capture.profile.has_value(),"comparison profile missing");return *capture.profile;
  };
  // Complete detail sees two changes across four inputs, so six detail groups
  // contribute4 each:24 + census12 =36. Sampling only the duplicate no-ops
  // sees zero detail across TWO eligible inputs:0 + census12 =12. Neither
  // sampled forecast is a confidence bound on the actual population.
  const auto full=recorded(1,0),noops=recorded(2,1);
  const std::array<cost::Profile,1> full_profile{full},noop_profile{noops};
  const auto exact=cost::estimate(account,set,full_profile,*calibration.calibration,request);
  const auto noop=cost::estimate(account,set,noop_profile,*calibration.calibration,request);
  check(exact.result && exact.result->candidates()[index].total_ns==Ratio{36,1},"complete no-op detail denominator differs from literal36");
  check(noop.result && noop.result->candidates()[index].total_ns==Ratio{12,1},"selected no-ops disappeared from detail denominator");
  bool selected_noops=false;
  for(const auto& term:noop.result->candidates()[index].terms)if(term.component==C::adapter_visit && term.descriptor) {
    const auto& descriptor=noops.evidence().captured()->workload().descriptors()[*term.descriptor];
    if(descriptor.table==0 && descriptor.operation==ws::Operation::insert) {
      check(term.units==Ratio{} && term.confidence.complete_inputs==2 && term.confidence.observed_events==0 &&
        term.confidence.availability==ws::Availability::sampled,"selected no-op sample presented as empty or exact");selected_noops=true;
    }
  }
  check(selected_noops,"selected no-op confidence term absent");
  inputs=demand(8,1);request.input=inputs;
  const auto unknown=cost::estimate(account,set,profiles,*calibration.calibration,request);
  check(unknown.result && !unknown.result->candidates()[index].total_ns &&
    (unknown.result->candidates()[index].issues&cost::issue(cost::Issue::stratum_unobserved)),"unobserved delete stratum got a fabricated cost");
  const auto foreign=cost::calibrate(account,"deliberately wrong backend",indexed?"reference_ordered_v1":"indexed_chained_v1",rates());
  inputs=demand(8);request.input=inputs;
  const auto mismatch=cost::estimate(account,set,profiles,*foreign.calibration,request);
  check(mismatch.result && !mismatch.result->candidates()[index].total_ns &&
    (mismatch.result->candidates()[index].issues&cost::issue(cost::Issue::calibration_backend)),"backend coefficients silently transferred");
  options.period=1;options.detail_budget=0;owner.configure_workload_statistics(options);apply(owner,SetOperation::insert,4);
  const auto truncated=cost::capture(set,index,owner);check(truncated.profile.has_value(),"truncated profile missing");
  const std::array<cost::Profile,1> incomplete{*truncated.profile};
  const auto rejected=cost::estimate(account,set,incomplete,*calibration.calibration,request);
  check(rejected.result && !rejected.result->candidates()[index].total_ns && rejected.result->candidates()[index].issues!=0,"truncated observations priced as complete");
  inputs=demand(0);request.input=inputs;
  const auto idle=cost::estimate(account,set,incomplete,*calibration.calibration,request);
  check(idle.result && idle.result->candidates()[index].total_ns==Ratio{},"zero declared work inferred from observations instead of demand");
  options.detail_budget=65536;owner.configure_workload_statistics(options);
  auto pending=owner.prepare({owner.sequence()+1,{0},SetOperation::insert,Row{std::int64_t{5}}});
  const auto hidden=cost::capture(set,index,owner);
  check(hidden.stop==planner::ranking::Stop::evidence_unavailable && !hidden.profile,"private owner state became a published cost profile");pending.rollback();
  check(owner.sequence()==5 && owner.has_answer(),"cost capture/estimate changed live state");owner.check_invariants();
  std::cout<<"C03 indexed="<<indexed<<" exact-census4/2 sampled-detail2/2 literal60/36/12 unknown/truncated/backend/pending/zero-demand passed\n";
}
#ifdef CROWN_RUNTIME_TESTING
void saturation(bool indexed) {
  const auto f=fixture();const auto set=candidates(f);const auto index=native_index(set);
  const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(index)->tree(),indexed?s04_runtime::options():PhysicalOptions{});
  auto owner=runtime::DeltaRuntime::initialize(plan,f.database);ws::Options options;options.mode=ws::Mode::counters;owner.configure_workload_statistics(options);
  auto epoch=owner.apply({1,{0},SetOperation::insert,Row{std::int64_t{2}}});epoch.discard();
  runtime::RuntimeTestProbe::seed_c01_report_saturation(owner);
  const auto captured=cost::capture(set,index,owner);check(captured.profile.has_value(),"saturated actual-owner profile absent");
  const auto& snapshot=captured.profile->evidence().captured()->workload();check(snapshot.detail_availability()==ws::Availability::lower_bound,"saturated counters presented as exact");
  check(cost::features(snapshot).stop==planner::ranking::Stop::evidence_unavailable,"saturated counters became calibration measurements");
  auto account=resource::MemoryAccount::create(32U*1024U*1024U);const auto calibration=cost::calibrate(account,"saturation boundary, synthetic rates",plan.guarantee().storage_backend,rates());
  auto inputs=demand(8);cost::Request request;request.input=inputs;const std::array<cost::Profile,1> profiles{*captured.profile};
  const auto rejected=cost::estimate(account,set,profiles,*calibration.calibration,request);
  check(rejected.result && !rejected.result->candidates()[index].total_ns && rejected.result->candidates()[index].issues!=0,"saturated capped counters became a complete forecast");
  std::cout<<"C03 indexed="<<indexed<<" actual test-ABI saturation unavailable for fit/complete forecast passed\n";
}
#endif
}
int main(){try{for(bool indexed:{false,true})test_backend(indexed);
#ifdef CROWN_RUNTIME_TESTING
  for(bool indexed:{false,true})saturation(indexed);
#endif
}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
