#include "weighted_bag_fixture.hpp"
#include "crown/api/error.hpp"
#include <iostream>
#include <random>

namespace {
using namespace crown;
using namespace crown::weighted_test;

template<class Action> void error(Action action, std::string_view code) {
  try {action();}
  catch (const Error& failure) {check(failure.code()==code,"unexpected weighted error: "+failure.code());return;}
  throw std::runtime_error("expected "+std::string(code));
}

void counted_path_case(bool indexed, bool hidden, bool repeated) {
  BagModel model(counted_path(indexed,hidden,repeated));
  model.set(0,{n(1),n(10),n(100)},2);model.set(0,{n(1),n(10),n(101)},3);
  model.set(1,{n(10),n(20)},5);model.set(1,{n(10),n(21)},7);
  if (hidden) {model.set(2,{n(20)},13);model.set(2,{n(21)},17);}
  const auto expected=hidden?920U:60U;
  check(model.runtime.root_weight().value==expected,"mandatory counted path hand result");
  const auto state=model.runtime.snapshot();
  check(state.nodes[0].factors.size()==1 && state.nodes[0].factors[0].value.value==5,
      "parent factor double-counted its enumerated child");
  const auto numeric=model.set(1,{n(10),n(20)},11);
  check(numeric.metrics.factor_replacements>0 && numeric.metrics.factor_membership_changes==0,
      "numeric local factor change was lost or changed membership");
  const auto after=model.runtime.snapshot();
  check(after.nodes[0].factors[0].value.value==5,"inside-child numeric change altered parent factor");
  model.set(1,{n(10),n(20)},0);model.set(1,{n(10),n(21)},0);
  check(model.runtime.snapshot().nodes[0].factors.empty(),"last child support retained parent factor");
  model.set(1,{n(10),n(21)},4);
  model.set(0,{n(1),n(10),n(100)},0);model.set(0,{n(1),n(10),n(101)},0);
}

void generalized_case(bool indexed) {
  BagModel model(generalized(indexed));
  model.set(1,{n(1)},11);
  model.set(3,{n(1),n(10),n(100)},2);model.set(3,{n(1),n(20),n(200)},3);
  model.set(4,{n(1),n(10),n(300)},5);model.set(4,{n(1),n(20),n(400)},7);
  const auto snapshot=model.runtime.snapshot();
  check(snapshot.nodes[0].factors[0].value.value==1,"generalized connector must be a unit factor");
  check(snapshot.nodes[2].factors[0].value.value==31,"hidden generalized scope was not summed to visible x");
  check(model.runtime.root_weight().value==341,"generalized projected bag hand result");
  model.set(3,{n(1),n(10),n(100)},4);
  model.set(4,{n(1),n(10),n(300)},0);model.set(4,{n(1),n(20),n(400)},0);
  model.set(4,{n(1),n(20),n(400)},9);
}

void random_cases(bool indexed) {
  BagModel model(counted_path(indexed,true));std::mt19937_64 random(0x7303);
  for (unsigned step=0;step<400;++step) {
    const auto node=random()%3;
    Row row;
    if (node==0) row={n(static_cast<std::int64_t>(random()%3)),n(static_cast<std::int64_t>(random()%3)),
        n(static_cast<std::int64_t>(random()%2))};
    else if (node==1) row={n(static_cast<std::int64_t>(random()%3)),n(static_cast<std::int64_t>(random()%3))};
    else row={n(static_cast<std::int64_t>(random()%3))};
    model.set(node,std::move(row),random()%7);
  }
  BagModel sole(path(indexed));
  sole.set(0,{n(1),n(10)},2);sole.set(0,{n(1),n(11)},3);sole.set(0,{n(2),n(11)},5);
  sole.set(1,{n(10),n(20)},7);sole.set(1,{n(11),n(20)},11);sole.set(2,{n(20)},13);
}

void duplicate_bags_and_self_join(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64}},
      {{"a",TableId{0},{VariableId{0}}},{"b",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{
      {"g",NodeKind::generalized,{VariableId{0}},{NodeId{1},NodeId{2}},{},{}},
      {"a",NodeKind::native,{VariableId{0}},{},0,{}},
      {"b",NodeKind::native,{VariableId{0}},{},1,{}}},{},{}};
  BagModel model(planner::lower_tree(catalog,query,tree,options(indexed)));
  Counts raw;
  // Fold raw duplicates into native logical weights; no physical bag router or
  // SQL admission is claimed. Every occurrence receives the same source bag.
  for (const auto value:{1,1,1,2,2}) ++raw[Row{n(value)}];
  auto pending=model.runtime.begin_epoch(1);
  for (std::size_t node=1;node<=2;++node) for (const auto& [row,count]:raw) {
    static_cast<void>(pending.stage({NodeId{node},row,{0},{count}}));model.inputs[node][row]=count;
  }
  static_cast<void>(pending.commit());compare_bag(model.runtime,model.inputs);
  auto cursor=model.runtime.results();
  check(drain(cursor)==Counts{{Row{n(1)},9},{Row{n(2)},4}},"duplicate native bag occurrences were deduplicated");
}

void lifetime(bool indexed) {
  BagModel model(unary(indexed));model.set(0,{n(1)},2);model.set(0,{n(2)},3);
  auto first=model.runtime.results(),second=model.runtime.results();
  check(!model.runtime.ready(),"weighted cursor did not lease writer");
  error([&]{static_cast<void>(model.runtime.apply({3,{NodeId{0},{n(1)},{2},{2}}}));},"runtime_busy");
  auto retained=first.next();check(retained.has_value(),"cursor missed first row");
  const auto old=storage::export_row(retained->tuple.values());
  first.cancel();check(!model.runtime.ready(),"one cancellation released another reader");
  second.cancel();check(model.runtime.ready(),"cancellation retained reader");
  const auto spent=first.metrics().work;
  check(!first.next() && first.metrics().work==spent,"closed next spent work");
  model.set(0,{n(1)},0);check(storage::export_row(retained->tuple.values())==old,"owning emitted row changed");
  auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1);
  error([&]{static_cast<void>(model.runtime.results());},"runtime_busy");pending.rollback();
  auto active=model.runtime.results();auto moved=std::move(active);
  check(!active.active(),"moved-from cursor remained active");
  error([&]{static_cast<void>(active.state());},"invalid_cursor");
  auto facade=std::move(model.runtime);check(drain(moved)==Counts{{Row{n(2)},3}},"cursor facade move lifetime");
  check(facade.ready(),"moved facade retained reader");
}

void constants_and_large(bool indexed) {
  for (const bool nullary:{false,true}) {
    BagModel model(unary(indexed,nullary,true));
    model.set(0,nullary?Row{}:Row{n(7)},UINT64_C(9007199254740993));
    model.set(0,nullary?Row{}:Row{n(7)},UINT64_MAX);
  }
  for (const bool contradiction:{false,true}) {
    Query query;query.contradiction=contradiction;
    BagModel model(planner::lower_tree(Catalog{},query,FreeConnexTree{},options(indexed)));
    compare_bag(model.runtime,model.inputs);
  }
}

void typed_and_deep(bool indexed) {
  BagModel typed(typed_bag(indexed));typed_inputs(typed);compare_bag(typed.runtime,typed.inputs);
  typed.set(1,{n(7),Value{true}},7);
  const Catalog catalog{1,{{"amounts",{{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{10,2}}}}}};
  const Query query{{{"amount",ScalarType::decimal}},{{"amounts",TableId{0},{VariableId{0}}}},
      {{VariableId{0},"amount"}},false};
  const FreeConnexTree tree{NodeId{0},{{"amounts",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  BagModel decimals(planner::lower_tree(catalog,query,tree,options(indexed)));
  decimals.set(0,{Value{Decimal::parse("12.34")}},3);decimals.set(0,{Value{Decimal::parse("-7.5")}},5);
  constexpr std::size_t length=96;
  for (const bool hidden:{false,true}) {
    BagModel model(deep_bag(length,hidden,indexed));
    model.set(0,hidden?Row{n(1),n(7)}:Row{n(7)},2);
    if (hidden) model.set(0,{n(2),n(7)},3);
    for (std::size_t node=1;node<length;++node) model.set(node,{n(7)},1);
    model.set(length-1,{n(7)},13);
    auto cursor=model.runtime.results();const auto actual=drain(cursor);
    check(actual==(hidden?Counts{{Row{n(1)},26},{Row{n(2)},39}}:Counts{{Row{n(7)},26}}),"deep visible/hidden factorization");
    check(cursor.metrics().frame_initializations==(hidden?1:length),"cursor traversed hidden witnesses");
    model.set(length-1,{n(7)},0);
  }
}
} // namespace

int main() {
  try {
    for (const bool indexed:{false,true}) {
      counted_path_case(indexed,false,false);counted_path_case(indexed,true,false);
      counted_path_case(indexed,true,true);generalized_case(indexed);random_cases(indexed);
      duplicate_bags_and_self_join(indexed);lifetime(indexed);constants_and_large(indexed);
      typed_and_deep(indexed);
    }
    std::cout<<"weighted projected bags and component factors agree with exhaustive native joins\n";
  } catch (const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}
