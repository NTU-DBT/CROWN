#include "ranking_fixture.hpp"
#include "ranking_detail.hpp"
#include "crown/runtime/ranking_evidence.hpp"
#include <iostream>

namespace {
using namespace c02_test;
namespace pr=planner::ranking;
namespace rr=runtime::ranking;
pr::Result memory(const planner::CandidateSnapshot& set,const runtime::PhysicalRuntime& owner){
  pr::Request request;request.policy=pr::Policy::tuple_index_slots;
  const auto attempt=rr::rank_current(set,owner,request);
  check(attempt.result.has_value(),"normalized payload baseline failed");return *attempt.result;
}
struct NormalizedFixture {planner::CandidateSnapshot set;runtime::PhysicalRuntime owner;};
NormalizedFixture sql(std::size_t padding){
  const auto f=fixture();
  const auto source=std::string("/*")+std::string(padding,'p')+"*/ SELECT EXISTS (SELECT 1 FROM \"R\" JOIN \"S\" ON \"R\".x=\"S\".x JOIN \"T\" ON \"S\".y=\"T\".y)";
  auto binding=frontend::bind_sql(source,f.catalog);check(std::holds_alternative<frontend::BoundSql>(binding),"SQL payload binding failed");
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(binding));check(std::holds_alternative<frontend::NormalizedSql>(normalized),"SQL payload normalization failed");
  const auto program=std::get<frontend::NormalizedSql>(std::move(normalized));
  Fixture logical{program.core_catalog,program.core,{}};auto set=candidates(logical);
  const auto plan=planner::lower_normalized(program,set.candidate(0)->tree());
  return {std::move(set),runtime::PhysicalRuntime::initialize(plan,f.database)};
}
}
int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;
  // All three separately owned plans retain the long source text. Comments
  // change that payload without changing the literal query or score terms.
  auto short_sql=sql(0);auto long_sql=sql(16'384);
  const auto small=memory(short_sql.set,short_sql.owner);const auto large=memory(long_sql.set,long_sql.owner);
  check(large.scores().size()==3 && large.usage().payload_bytes>=small.usage().payload_bytes+3*16'384,"source payload was charged once instead of per candidate");
  for(const auto& score:large.scores())check(score.slots==(shape(score.candidate.tree())==0?"24":"32"),"source padding changed unitless proxy");
  pr::Request request;request.policy=pr::Policy::tuple_index_slots;request.fallback=pr::Fallback::height_only;
  request.limits.payload_bytes=large.usage().payload_bytes;
  const auto exact=rr::rank_current(long_sql.set,long_sql.owner,request);check(exact.result && exact.usage.payload_bytes==request.limits.payload_bytes,"exact retained payload ceiling failed");
  --request.limits.payload_bytes;
  const auto short_cap=rr::rank_current(long_sql.set,long_sql.owner,request);check(!short_cap.result && short_cap.stop==pr::Stop::byte_limit,"retained plan payload limit invoked fallback or published");
  check(long_sql.owner.sequence()==0 && long_sql.owner.has_answer() && large.scores().size()==3,"payload failure changed prior artifact or owner");

  Fixture typed;typed.catalog.tables={{"typed",{{"x",ScalarType::int64},{"d",ScalarType::decimal}}}};
  const auto coefficient=Decimal::parse("-99999999999999999999999999999999999999");
  typed.query.variables={{"x",ScalarType::int64}};
  typed.query.atoms={{"typed",TableId{0},{Term{VariableId{0}},Term{Value{coefficient}}}}};
  typed.query.head={{VariableId{0},"first"},{VariableId{0},"second"},{VariableId{0},"third"}};
  typed.database.tables={Relation{Row{std::int64_t{1},coefficient},Row{std::int64_t{2},coefficient}}};
  const auto typed_set=candidates(typed,1,0);
  auto typed_owner=runtime::PhysicalRuntime::initialize(planner::lower_tree(typed.catalog,typed.query,typed_set.candidate(0)->tree()),typed.database);
  const auto typed_result=memory(typed_set,typed_owner);const auto& selected=typed_result.scores()[typed_result.selected_index()];
  check(selected.slots=="13" && selected.modeled_plan->result_layout().fields().size()==3,"repeated head/Decimal literal proxy mismatch");
  check(std::get<Decimal>(selected.modeled_plan->inputs()[0].constants[0].value)==coefficient,"retained 38-digit Decimal copy changed");
  request.limits.payload_bytes=typed_result.usage().payload_bytes;
  check(rr::rank_current(typed_set,typed_owner,request).result.has_value(),"typed exact payload cap failed");
  --request.limits.payload_bytes;const auto typed_short=rr::rank_current(typed_set,typed_owner,request);
  check(!typed_short.result && typed_short.stop==pr::Stop::byte_limit,"typed retained payload escaped cap");

  const auto f=fixture();const auto set=candidates(f);auto owner=runtime::PhysicalRuntime::initialize(planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree()),f.database);
  rr::CaptureOptions options;options.processing.active_time=std::chrono::minutes{10};
  const auto captured=rr::capture(set,owner,options);check(captured.evidence.has_value(),"timed capture failed");
  check(captured.usage.active_nanoseconds==captured.evidence->inputs().preparation_usage().active_nanoseconds,"capture lost its measured active work");
  request.limits=options.processing;
  const auto ranked=pr::rank(set,request,captured.evidence->inputs());check(ranked.result && ranked.usage.active_nanoseconds>=captured.usage.active_nanoseconds,"split rank discarded captured active work");
  request.limits.active_time=std::chrono::nanoseconds{static_cast<std::chrono::nanoseconds::rep>(captured.usage.active_nanoseconds)};
  const auto time_stop=pr::rank(set,request,captured.evidence->inputs());check(!time_stop.result && time_stop.stop==pr::Stop::time_limit && time_stop.usage.active_nanoseconds==captured.usage.active_nanoseconds,"carried exact time ceiling did not stop before ranking");
  pr::Limits limits;limits.active_time=std::chrono::nanoseconds{11};pr::Usage past;past.active_nanoseconds=11;
  bool stopped=false;try{pr::detail::Budget budget(limits,past);static_cast<void>(budget);}catch(const pr::detail::Failure& e){stopped=e.stop==pr::Stop::time_limit;}
  check(stopped,"time carry boundary was not transactional");
  std::cout<<"C02 per-candidate owned payload and aggregate active-time boundaries passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
