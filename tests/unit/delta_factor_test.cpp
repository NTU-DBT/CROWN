#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
using namespace crown::runtime;
void check(bool condition,const std::string& message) { if (!condition) throw std::runtime_error(message); }
template<class Action> void error(Action&& action,std::string_view code) {
  try { action(); }
  catch (const Error& failure) { check(failure.code()==code,"unexpected error "+failure.code()); return; }
  throw std::runtime_error("expected error "+std::string(code));
}
Row row(std::initializer_list<std::int64_t> values) { Row result; for (const auto value : values) result.emplace_back(value); return result; }
Relation drain(SupportRuntime::ResultCursor cursor) {
  Relation result;
  while (auto tuple=cursor.next()) {
    check(tuple->layout().same_token(cursor.layout()),"factor result layout token");
    check(result.insert(crown::storage::export_row(tuple->values())).second,"duplicate factor key");
  }
  return result;
}
PhysicalPlan plan() {
  Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}},{"s",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0}}},{"s",TableId{1},{VariableId{0},VariableId{1}}}},
      {{VariableId{1},"y"},{VariableId{0},"x"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{0},VariableId{1}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree);
}
void unlive_factor() {
  SupportRuntime runtime(plan());
  static_cast<void>(runtime.apply({1,NodeId{1},SetOperation::insert,row({3,11})}));
  auto view=runtime.current_view();
  check(!view.has_answer(),"unlive child made global truth true");
  check(drain(view.results()).empty(),"empty global query");
  check(drain(view.visible_keys(NodeId{0})).empty(),"root E should be empty");
  auto child=view.visible_keys(NodeId{1});
  check(child.layout().same_token(runtime.plan().relations()[runtime.plan().nodes()[1].visible_relation->value].layout),"factor must use its own E layout");
  check(child.layout().fields()[0].variable==VariableId{0} && child.layout().fields()[1].variable==VariableId{1},"full sorted E schema");
  view.close();
  check(!runtime.ready(),"factor cursor must retain the view lease");
  check(drain(std::move(child))==Relation{row({3,11})},"factor scan dropped a globally dead key");
  check(runtime.ready(),"factor scan leaked a reader");
  auto retry=runtime.current_view();
  error([&] { static_cast<void>(retry.visible_keys(NodeId{99})); },"invalid_fragment");
  error([&] { static_cast<void>(retry.visible_keys(NodeId{1},{{0}})); },"resource_limit");
  check(retry.valid(),"failed cursor construction invalidated view"); retry.close();
  error([&] { static_cast<void>(retry.has_answer()); },"invalid_snapshot");
}
void whole_epoch_and_rollback() {
  SupportRuntime runtime(plan());
  static_cast<void>(runtime.apply({1,NodeId{1},SetOperation::insert,row({1,10})}));
  static_cast<void>(runtime.apply({2,NodeId{0},SetOperation::insert,row({1})}));
  auto pending=runtime.begin_epoch(3,SetOperation::erase);
  check(pending.stage(NodeId{0},row({1})),"first erase stage");
  auto before=pending.view(SnapshotSide::before);
  check(before.has_answer(),"old truth was not retained");
  auto held=before.visible_keys(NodeId{0}); before.close();
  error([&] { static_cast<void>(pending.stage(NodeId{1},row({1,10}))); },"runtime_busy");
  check(pending.active(),"prefix-busy rejection aborted epoch");
  check(drain(std::move(held))==Relation{row({1})},"deleted factor key was not pinned");
  check(pending.stage(NodeId{1},row({1,10})),"second erase stage");
  auto old=pending.view(SnapshotSide::before); auto after=pending.view(SnapshotSide::after);
  check(old.has_answer() && !after.has_answer(),"whole-epoch old/new truth");
  check(drain(old.visible_keys(NodeId{0}))==Relation{row({1})},"whole-epoch before lost first stage");
  check(drain(old.visible_keys(NodeId{1}))==Relation{row({1,10})},"whole-epoch before lost last stage");
  check(drain(old.results())==Relation{row({10,1})},"whole-epoch output order");
  check(drain(after.visible_keys(NodeId{1})).empty(),"after factor still contains erased key");
  auto retained=old.visible_keys(NodeId{1}); old.close(); after.close();
  const auto committed=pending.commit(); check(committed.sequence==3,"committed sequence");
  check(!runtime.ready(),"committed factor cursor lost its reader guard");
  check(drain(std::move(retained))==Relation{row({1,10})},"committed old factor view became unreadable");
  check(runtime.ready(),"committed factor reader leaked");
  static_cast<void>(runtime.apply({4,NodeId{1},SetOperation::insert,row({2,20})}));
  auto abort=runtime.begin_epoch(5,SetOperation::erase);
  check(abort.stage(NodeId{1},row({2,20})),"rollback erase stage");
  auto image=abort.view(SnapshotSide::before); auto cursor=image.visible_keys(NodeId{1});
  abort.rollback();
  check(!image.valid() && cursor.state()==ResultCursorState::failed,"rollback did not close factor cursor");
  error([&] { static_cast<void>(image.has_answer()); },"invalid_snapshot");
  check(runtime.ready() && runtime.sequence()==4,"rollback did not restore writer readiness");
  static_cast<void>(runtime.apply({5,NodeId{1},SetOperation::erase,row({2,20})}));
}
void nullary_and_outside() {
  Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  SupportRuntime runtime(planner::lower_tree(catalog,query,tree));
  static_cast<void>(runtime.apply({1,NodeId{0},SetOperation::insert,row({1})}));
  static_cast<void>(runtime.apply({2,NodeId{0},SetOperation::insert,row({2})}));
  auto view=runtime.current_view();
  check(drain(view.visible_keys(NodeId{0}))==Relation{Row{}},"nullary E was not projected to one key");
  view.close();
  Query hidden{{{"x",ScalarType::int64},{"z",ScalarType::int64},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1},VariableId{2}}}},{{VariableId{0},"x"}},false};
  Catalog two{1,{{"r",{{"x",ScalarType::int64},{"z",ScalarType::int64}}},{"s",{{"z",ScalarType::int64},{"y",ScalarType::int64}}}}};
  FreeConnexTree child{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1},VariableId{2}},{},1,{}}},{},{}};
  SupportRuntime local(planner::lower_tree(two,hidden,child)); auto context=local.current_view();
  check(!local.plan().nodes()[1].connex,"test needs an outside-C* factor");
  error([&] { static_cast<void>(context.visible_keys(NodeId{1})); },"invalid_fragment");
}
std::uint64_t eager_cost(std::size_t count) {
  DeltaOptions options; options.mode=DeltaMode::maintenance; options.live_maintenance=LiveMaintenance::eager;
  options.completion=DeltaCompletion::root_first;
  DeltaRuntime runtime(plan(),options);
  std::uint64_t sequence=0;
  for (std::size_t i=0;i<count;++i) {
    auto input=runtime.apply({++sequence,TableId{1},SetOperation::insert,row({static_cast<std::int64_t>(i+1),10})});
    check(!input.active(),"maintenance epoch produced output");
  }
  const auto bootstrap=runtime.set_mode(DeltaMode::delta);
  check(bootstrap.e_rows_scanned==count && bootstrap.live_rows==0 && bootstrap.parent_live_rows==0,"dead-factor bootstrap scan accounting");
  check(bootstrap.candidates==0 && bootstrap.accepted==0 && bootstrap.spool_rows==0,"bootstrap enumerated query output");
  auto empty=runtime.apply({++sequence,TableId{0},SetOperation::insert,row({100})});
  const auto scanned=empty.metrics().work;
  check(!empty.active() && empty.metrics().stages==1 && empty.metrics().changed_keys==0,"empty delta stage completion");
  check(empty.metrics().e_rows_scanned==count && empty.metrics().live_rows==0,"empty delta concealed its E scan");
  check(runtime.live_snapshot()->sequence==sequence,"empty delta did not advance live tag");
  auto activated=runtime.apply({++sequence,TableId{1},SetOperation::insert,row({100,20})});
  const auto metrics=activated.metrics();
  check(metrics.changed_keys==2 && metrics.live_witnesses==2 && metrics.candidates==2 && metrics.accepted==1 && metrics.rejected==1,"ancestor/child ownership counters");
  check(metrics.earlier_probes==1 && metrics.e_rows_scanned==count+2 && metrics.parent_live_rows==1 && metrics.separator_fields==count+2,"eager semijoin scan/field accounting");
  check(metrics.live_rows_copied==2 && metrics.live_rows==2 && metrics.peak_live_rows==2,"first live image accounting");
  check(metrics.spool_rows==1 && metrics.spool_capacity_rows>=1 && metrics.spool_bytes<=options.spool_byte_limit,"bounded spool accounting");
  check(metrics.cursor_startup_work>0 && metrics.cursor_results_work>0 && metrics.cursor_termination_work>0,"cursor phase work was not charged");
  check(activated.stages().size()==1 && !activated.stages()[0].before_answer && activated.stages()[0].after_answer,"adjacent-prefix truth diagnostics");
  check(!runtime.ready(),"undelivered output did not gate input");
  auto output=activated.next();
  check(output && output->ordinal==1 && output->operation==SetOperation::insert && output->tuple.values()==row({20,100}),"accepted output/layout order");
  check(!activated.next() && runtime.ready(),"last output did not release barrier");
  auto shared=runtime.apply({++sequence,TableId{0},SetOperation::insert,row({1})});
  check(shared.metrics().changed_keys==1 && shared.metrics().accepted==1 && shared.metrics().live_rows==4 && shared.metrics().peak_live_rows==6,"retained committed/working live images");
  check(shared.next()->tuple.values()==row({10,1}),"unchanged child E did not become live");
  const auto before=runtime.live_snapshot()->factors;
  auto noop=runtime.apply({++sequence,TableId{0},SetOperation::insert,row({1})});
  check(!noop.active() && noop.metrics().stages==0 && noop.metrics().e_rows_scanned==0,"certified source no-op scanned E");
  check(runtime.live_snapshot()->factors==before && runtime.live_snapshot()->sequence==sequence,"no-op cache membership/tag");
  runtime.check_invariants(); return scanned;
}
void typed_projection() {
  Catalog catalog{1,{{"r",{{"day",ScalarType::date},{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}},
      {"name",ScalarType::string},{"flag",ScalarType::boolean},{"witness",ScalarType::int64}}}}};
  Query query{{{"day",ScalarType::date},{"amount",ScalarType::decimal},{"name",ScalarType::string},
      {"flag",ScalarType::boolean},{"witness",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}}}},
      {{VariableId{2},"name"},{VariableId{0},"day"},{VariableId{1},"amount"},{VariableId{3},"flag"},{VariableId{1},"again"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}},{},0,{}}},{},{}};
  DeltaRuntime runtime(planner::lower_tree(catalog,query,tree));
  const Value day=Date::parse("2026-11-06"), amount=Decimal::parse("12345678901234567890.12"), name=std::string(80,'x');
  Row first{day,amount,name,Value{true},Value{std::int64_t{10}}}, second=first; second.back()=std::int64_t{20};
  const Row expected{name,day,amount,Value{true},amount};
  auto inserted=runtime.apply({1,TableId{0},SetOperation::insert,first});
  check(inserted.metrics().spool_bytes>=80+64+expected.size()*sizeof(Value)+sizeof(SignedResult),"wide scalar spool accounting");
  auto plus=inserted.next();
  check(plus && plus->tuple.values()==expected && plus->operation==SetOperation::insert,"typed reordered/repeated delta");
  check(plus->tuple.layout().same_token(runtime.result_layout()),"typed result layout token");
  auto collision=runtime.apply({2,TableId{0},SetOperation::insert,second});
  check(collision.remaining()==0 && collision.metrics().changed_keys==0,"typed hidden collision emitted output");
  auto nonlast=runtime.apply({3,TableId{0},SetOperation::erase,first});
  check(nonlast.remaining()==0,"typed nonlast deletion emitted output");
  auto erased=runtime.apply({4,TableId{0},SetOperation::erase,second}); auto minus=erased.next();
  check(minus && minus->tuple.values()==expected && minus->operation==SetOperation::erase,"typed last deletion output");
  check(plus->tuple.values()==expected && runtime.ready(),"returned typed row lost ownership after later epochs");
  runtime.check_invariants();
}
}  // namespace
int main() {
  try {
    unlive_factor(); whole_epoch_and_rollback(); nullary_and_outside(); typed_projection();
    const auto small=eager_cost(1), larger=eager_cost(8);
    check(larger>small,"eager no-delta scan cost did not grow with E");
    std::cout<<"E-factor context, lease, rollback and eager-cost checks passed; empty-delta work "<<small<<" -> "<<larger<<'\n';
  }
  catch (const std::exception& failure) { std::cerr<<failure.what()<<'\n'; return 1; }
}
