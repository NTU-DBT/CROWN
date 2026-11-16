#include "selection_independent_fixture.hpp"
#include "selection_detail.hpp"

#include <iostream>
#include <limits>

namespace {
using namespace c05_independent;
namespace budget_detail = crown::planner::selection::detail;
using Counter=std::uint64_t rank::Usage::*;
using Ceiling=std::uint64_t rank::Limits::*;
constexpr std::array<Counter,8> counters_by_field{&rank::Usage::work,&rank::Usage::cells,
    &rank::Usage::binding_key_bytes,&rank::Usage::payload_bytes,&rank::Usage::lowering_work,
    &rank::Usage::identity_work,&rank::Usage::binding_replay_work,&rank::Usage::normalization_work};
constexpr std::array<Ceiling,8> limits_by_field{&rank::Limits::work,&rank::Limits::cells,
    &rank::Limits::binding_key_bytes,&rank::Limits::payload_bytes,&rank::Limits::lowering_work,
    &rank::Limits::identity_work,&rank::Limits::binding_replay_work,&rank::Limits::normalization_work};

void fixed_preparation_algebra() {
  // Resource numbers are deliberately synthetic. They create no semantic
  // Evidence, Selection, proof or private cache entry. The independent oracle
  // is plain integer arithmetic: P=7, own=3, V1=17, V2=27 => U=40, not47/54.
  rank::Limits limits;
  rank::Usage preparation;
  for (std::size_t i=0;i<counters_by_field.size();++i) {
    limits.*limits_by_field[i]=100;
    preparation.*counters_by_field[i]=7;
  }
  budget_detail::Budget budget(limits,preparation);
  for (auto field:counters_by_field) budget.usage.*field+=3;
  const auto first=budget.begin_delegate(preparation);
  for (auto field:limits_by_field) check(first.*field==97,"first delegated limit did not add back exactly one P");
  auto returned=preparation;
  for (auto field:counters_by_field) returned.*field=17;
  budget.end_delegate(returned,preparation);
  for (auto field:counters_by_field) check(budget.usage.*field==20,"first complete assessment counted preparation twice");
  const auto second=budget.begin_delegate(preparation);
  for (auto field:limits_by_field) check(second.*field==87,"second assessment received a fresh full grant");
  for (auto field:counters_by_field) returned.*field=27;
  budget.end_delegate(returned,preparation);
  budget.finish();
  for (auto field:counters_by_field) check(budget.usage.*field==40,"two-assessment aggregate is not P+3+(17-P)+(27-P)");
  check(budget.usage.active_nanoseconds==0,"timing-off neutral accounting invented elapsed time");
  std::uint64_t used=std::numeric_limits<std::uint64_t>::max()-1;
  budget_detail::Budget::add(used,1,std::numeric_limits<std::uint64_t>::max(),s::Resource::work);
  check(used==std::numeric_limits<std::uint64_t>::max(),"exact U64 boundary failed");
  bool stopped=false;
  try {budget_detail::Budget::add(used,1,std::numeric_limits<std::uint64_t>::max(),s::Resource::work);}
  catch (const budget_detail::Failure& error) {stopped=error.stop==s::Stop::resource_limit && error.resource==s::Resource::work;}
  check(stopped && used==std::numeric_limits<std::uint64_t>::max(),"U64 charge wrapped or mutated on overflow");
}

void complete_dual_usage_and_boundaries(const BooleanFixture& f) {
  auto owner=r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")),f.initial);
  hot(owner,f);
  const auto facts=capture_checked(f.all,owner);
  const s::Source source{s::DirectCQ{}};
  auto request=depth();request.constraint=s::TupleIndexSlotLimit{"24"};
  const auto full=s::select(f.all,source,request,facts.inputs());
  const auto& result=complete(full);
  check(result.assessments().size()==2 && result.assessments()[0].purpose==s::AssessmentPurpose::slot_constraint &&
        result.assessments()[1].purpose==s::AssessmentPurpose::primary,
        "dual assessment order differs from constraint then complete primary");
  const auto& first=result.assessments()[0].result;
  const auto& second=result.assessments()[1].result;
  literal_slots(f,first);literal_depth(f,second);
  const auto& prepared=facts.inputs().preparation_usage();
  for (std::size_t i=0;i<counters_by_field.size();++i) {
    const auto field=counters_by_field[i];const auto limit=limits_by_field[i];
    const auto p=prepared.*field,v1=first.usage().*field,v2=second.usage().*field,u=result.usage().*field;
    check(v1>=p && v2>=p,"complete component usage omitted carried preparation");
    check(u>=p && u-p>=v1-p && u-p-(v1-p)>=v2-p,"aggregate omitted complete assessment cost");
    check(first.request().limits.*limit<=request.limits.aggregate.*limit &&
          second.request().limits.*limit<=first.request().limits.*limit &&
          first.request().limits.*limit-second.request().limits.*limit>=v1-p,
          "second delegated grant did not reflect first complete cost");
  }
  check(result.usage().active_nanoseconds==0 && result.preparation_timing()==s::PreparationTiming::unmeasured,
        "untimed as-of preparation was represented as measured zero");
  for (std::size_t i=0;i<counters_by_field.size();++i) {
    const auto consumed=result.usage().*counters_by_field[i];
    if (consumed==0) continue;
    auto exact=request;exact.limits.aggregate.*limits_by_field[i]=consumed;
    const auto fitted=s::select(f.all,source,exact,facts.inputs());
    check(fitted.stop==s::Stop::complete && fitted.selection && label(f,*fitted.selection)=="native_s",
          "exact aggregate resource boundary failed or changed the literal constrained choice");
    --(exact.limits.aggregate.*limits_by_field[i]);
    exact.fallback=rank::Fallback::height_only;
    const auto shortfall=s::select(f.all,source,exact,facts.inputs());
    check(shortfall.stop==s::Stop::resource_limit && !shortfall.selection,
          "one-under aggregate resource boundary published partial choice or used fallback");
  }
  for (const auto score_bits:{0U,513U}) {
    auto invalid=request;invalid.limits.aggregate.score_bits=score_bits;
    const auto stopped=s::select(f.all,source,invalid,facts.inputs());
    check(stopped.stop==s::Stop::invalid_request && !stopped.selection,"invalid score width reached ranking");
  }
  auto too_few=request;too_few.limits.aggregate.candidates=2;
  const auto candidate_stop=s::select(f.all,source,too_few,facts.inputs());
  check(candidate_stop.stop==s::Stop::resource_limit && !candidate_stop.selection,
        "candidate cap used a convenient prefix as a complete constrained winner");
}

void current_capture_and_time(const BooleanFixture& f) {
  auto owner=r::PhysicalRuntime::initialize(lower(f.by_label.at("native_s")),f.initial);
  hot(owner,f);
  const s::Source source{s::DirectCQ{}};
  const auto state=owner.canonical_state();
  const auto workload=owner.workload_statistics();
  auto request=depth();request.constraint=s::TupleIndexSlotLimit{"24"};
  r::statistics::Limits no_rows;no_rows.rows=0;no_rows.distinct_keys=0;
  const auto cardinality=current::select_current(f.all,source,owner,request,no_rows);
  const auto& captured=complete(cardinality).capture().inputs();
  check(captured.memory_reasons()==0 && captured.capture_accounting().state_rows==0 &&
        captured.capture_accounting().state_keys==0 && captured.sources().size()==3,
        "cardinality-only selection scanned rows/keys or lost exact source counts");
  for (const bool byte_limit:{false,true}) {
    auto limits=no_rows;
    if (byte_limit) limits.accounted_bytes=0;else limits.work=0;
    const auto unavailable=current::select_current(f.all,source,owner,request,limits);
    check(unavailable.stop==s::Stop::evidence_unavailable && !unavailable.selection &&
          has(unavailable.reasons,rank::Reason::source_budget_exhausted),
          "source-capture exhaustion was confused with an ordinary processing stop");
  }
  auto no_work=request;no_work.limits.aggregate.work=0;no_work.fallback=rank::Fallback::height_only;
  const auto processing=current::select_current(f.all,source,owner,no_work);
  check(processing.stop==s::Stop::resource_limit && !processing.selection && processing.resource==s::Resource::work,
        "zero C05 processing work became statistical fallback");
  const auto untimed=capture_checked(f.all,owner);
  check(untimed.inputs().preparation_usage().active_nanoseconds==0 &&
        !untimed.inputs().capture_accounting().processing_limits.active_time,"untimed preparation fixture is not untimed");
  auto timed=depth();timed.limits.aggregate.active_time=std::chrono::seconds{60};
  const auto historical=s::select(f.all,source,timed,untimed.inputs());
  check(complete(historical).preparation_timing()==s::PreparationTiming::unmeasured &&
        historical.selection->usage().active_nanoseconds>0,
        "timed as-of call fabricated measurement of prior untimed capture");
  const auto now=current::select_current(f.all,source,owner,timed);
  check(complete(now).selection().preparation_timing()==s::PreparationTiming::measured &&
        now.selection->capture().inputs().capture_accounting().processing_limits.active_time.has_value() &&
        now.selection->selection().usage().active_nanoseconds>=now.selection->capture().inputs().preparation_usage().active_nanoseconds,
        "current timed selection failed to time/carry its fresh preparation");
  capture::CaptureOptions measured;measured.processing.active_time=std::chrono::seconds{60};
  const auto saved=capture_checked(f.all,owner,measured);
  timed.limits.aggregate.active_time=std::chrono::nanoseconds{
      static_cast<std::chrono::nanoseconds::rep>(saved.inputs().preparation_usage().active_nanoseconds)};
  const auto carried=s::select(f.all,source,timed,saved.inputs());
  check(carried.stop==s::Stop::resource_limit && !carried.selection && carried.resource==s::Resource::active_time,
        "already-consumed carried time allowed fresh selection work");
  timed.limits.aggregate.active_time=std::chrono::nanoseconds{-1};
  const auto negative=s::select(f.all,source,timed,untimed.inputs());
  check(negative.stop==s::Stop::invalid_request && !negative.selection,"negative duration was admitted");
  check(owner.canonical_state()==state && same_workload(workload,owner.workload_statistics()),
        "resource/timing experiments changed complete owner or workload state");
}
} // namespace

int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: selection_resources_independent_test REPOSITORY_ROOT");
    const auto fixture=boolean_fixture(argv[1]);
    fixed_preparation_algebra();
    complete_dual_usage_and_boundaries(fixture);
    current_capture_and_time(fixture);
    std::cout<<"C05 independent resources groups=3 additive_dimensions=8 literal_aggregate=40 cap=24 source_rows=0\n";
  } catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
