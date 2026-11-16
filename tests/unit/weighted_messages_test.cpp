#include "weighted_fixture.hpp"
#include "crown/api/error.hpp"
#include <iostream>
#include <random>

namespace {
using namespace crown;
using namespace crown::weighted_test;

template<class Action>
void error(Action action, std::string_view code) {
  try {action();}
  catch (const Error& failure) {check(failure.code()==code,"unexpected error: "+failure.code());return;}
  catch (const storage::TupleValidationFailure& failure) {check(failure.code()==code,"unexpected tuple error");return;}
  throw std::runtime_error("expected error "+std::string(code));
}

void native_numeric(bool indexed) {
  Model model(path(indexed));
  model.set(0,{n(1),n(10)},2);model.set(0,{n(1),n(11)},3);
  model.set(1,{n(10),n(100)},5);model.set(1,{n(10),n(101)},7);
  model.set(1,{n(11),n(100)},11);
  model.set(2,{n(100)},13);model.set(2,{n(101)},17);
  check(model.runtime.root_weight().value==797,"native hidden-witness sum/product");
  const auto numeric=model.set(2,{n(100)},19);
  check(numeric.changed && numeric.before.value==797 && numeric.after.value==1055,"numeric propagation");
  check(numeric.metrics.row_membership_changes==0 && numeric.metrics.message_membership_changes==0,
      "numeric-only change spuriously altered membership");
  check(numeric.metrics.child_slots_copied==0 && !numeric.journal,"default updates copied diagnostic arrays");
  model.set(1,{n(10),n(100)},0);model.set(2,{n(101)},0);
  model.set(0,{n(1),n(11)},0);model.set(0,{n(1),n(10)},0);
  check(model.runtime.root_weight().value==0,"native deletion retained root weight");
  const auto noop=model.set(0,{n(9),n(9)},0);
  check(!noop.changed && noop.metrics.native_inputs==1 && noop.metrics.native_changes==0,"no-op contract");
}

void generalized_sums(bool indexed) {
  Model model(generalized(indexed));
  model.set(1,{n(1)},11);
  model.set(3,{n(1),n(10),n(100)},2);model.set(3,{n(1),n(20),n(200)},3);
  model.set(4,{n(1),n(10),n(300)},5);model.set(4,{n(1),n(20),n(400)},7);
  check(model.runtime.root_weight().value==341,"G(x,z) did not sum products before projecting to x");
  const auto numeric=model.set(3,{n(1),n(10),n(100)},4);
  check(numeric.after.value==451 && numeric.metrics.message_membership_changes==0,"generalized numeric update");
  model.set(4,{n(1),n(10),n(300)},0);
  auto snapshot=model.runtime.snapshot();
  check(snapshot.nodes[2].records.size()==2,"partial candidate was discarded");
  model.set(3,{n(1),n(10),n(100)},0);
  snapshot=model.runtime.snapshot();
  check(snapshot.nodes[2].records.size()==1,"unsupported candidate was retained");
  model.set(3,{n(1),n(20),n(200)},0);model.set(4,{n(1),n(20),n(400)},0);
  check(model.runtime.snapshot().nodes[2].records.empty(),"last candidate not reclaimed");
}

void causal_fifo(bool indexed) {
  w::Options opts;opts.capture_events=true;
  Model model(fanout(indexed),opts);
  for (std::int64_t z=0;z<4;++z) model.set(1,{n(1),n(7),n(z)},static_cast<std::uint64_t>(z+2));
  // No B key yet: the first Q event creates G after the actual Q message has
  // already advanced through every row. It must seed the first event's value.
  const auto creation=model.set(2,{n(7)},3);
  check(creation.journal && !creation.journal->events.empty(),"event capture missing");
  std::uint64_t ordinal=0;
  for (const auto& event:creation.journal->events) {
    check(event.applied_ordinal==++ordinal,"FIFO event ordinal");
    check(event.cause<event.id,"event cause is not earlier than effect");
  }
  model.set(3,{n(1)},5);
  check(model.runtime.root_weight().value==210,"FIFO creation weight");
  const auto retained=model.runtime.snapshot();const auto journal=creation.journal;
  const auto changed=model.set(2,{n(7)},7);
  check(changed.after.value==490 && changed.metrics.row_membership_changes==0,"same-key causal numeric chain");
  check(journal->phase==w::Phase::committed && retained.root.value==210,"owning captures changed later");
  model.set(2,{n(7)},0);model.set(3,{n(1)},0);
}

void random_model(bool indexed) {
  Model model(generalized(indexed));std::mt19937_64 random(0x7202);
  for (unsigned step=0;step<350;++step) {
    const auto source=random()%3;const auto x=static_cast<std::int64_t>(random()%3);
    const auto weight=random()%6;
    if (source==0) model.set(1,{n(x)},weight);
    else model.set(source==1 ? 3 : 4,{n(x),n(static_cast<std::int64_t>(random()%3)),
        n(static_cast<std::int64_t>(random()%2))},weight);
  }
}

void private_epochs(bool indexed) {
  runtime::WeightedRuntime runtime(unary(indexed));
  static_cast<void>(runtime.apply({1,{NodeId{0},{n(1)},{0},{2}}}));
  auto pending=runtime.begin_epoch(2);
  check(pending.stage({NodeId{0},{n(1)},{2},{5}}),"private replacement");
  check(pending.preview().after.value==5 && runtime.sequence()==1,"premature publication");
  error([&]{static_cast<void>(runtime.root_weight());},"runtime_busy");
  auto private_copy=pending.snapshot();check(private_copy.tentative && private_copy.root.value==5,"private snapshot");
  error([&]{static_cast<void>(pending.stage({NodeId{0},{n(2)},{9},{1}}));},"weight_conflict");
  check(!pending.active() && runtime.ready() && runtime.root_weight().value==2 && runtime.sequence()==1,
      "second-stage failure did not undo the first stage");
  check(private_copy.root.value==5,"aborted private snapshot ceased owning its value");
  auto owner_token=runtime.begin_epoch(2);check(owner_token.stage({NodeId{0},{n(1)},{2},{7}}),"move fixture");
  auto moved=std::move(runtime);auto moved_token=std::move(owner_token);
  check(!owner_token.active() && moved_token.commit().after.value==7 && moved.sequence()==2,"owner/token move");
  {auto abandoned=moved.begin_epoch(3);check(abandoned.stage({NodeId{0},{n(1)},{7},{11}}),"abandon fixture");}
  check(moved.ready() && moved.root_weight().value==7 && moved.sequence()==2,"destructor rollback");
  error([&]{static_cast<void>(moved.begin_epoch(4));},"invalid_sequence");
  error([&]{static_cast<void>(moved.apply({3,{NodeId{8},{n(1)},{0},{1}}}));},"invalid_native_update");
  error([&]{static_cast<void>(moved.apply({3,{NodeId{0},{Value{std::string("bad")}},{0},{1}}}));},"invalid_tuple");
  error([&]{static_cast<void>(moved.snapshot({0}));},"snapshot_limit");
  check(moved.ready() && moved.sequence()==2,"read rejection affected owner");
}

// Distinct physical rows can project to the same native tuple. The adapter
// keeps those identities; this port updates their combined weight in place.
void contributions(bool indexed) {
  w::Options opts;opts.capture_events=true;
  Model model(path(indexed),opts);
  model.set(0,{n(1),n(10)},9);model.set(1,{n(10),n(20)},3);model.set(2,{n(20)},2);
  std::array<storage::ScalarView,2> cells{std::int64_t{1},std::int64_t{10}};
  const auto values=storage::TupleValuesView::borrow(storage::RowView::borrow(cells));
  auto pending=model.runtime.begin_epoch(4);
  check(pending.stage_contribution(NodeId{0},values,{2},{5}),"first source contribution");
  check(pending.preview().after.value==72,"contribution did not propagate");
  check(pending.stage_contribution(NodeId{0},values,{7},{0}),"second source retraction");
  check(!pending.stage_contribution(NodeId{0},values,{4},{4}),"equal contribution changed native state");
  check(pending.stage({NodeId{0},{n(1),n(10)},{5},{11}}),"mixed absolute replacement");
  const auto epoch=pending.commit();model.inputs[0][Row{n(1),n(10)}]=11;
  compare(model.runtime.snapshot(),recompute(model.runtime.structural_program(),model.inputs));
  std::vector<std::pair<std::uint64_t,std::uint64_t>> native;
  for (const auto& event:epoch.journal->events) if (event.kind==w::EventKind::native_weight)
    native.emplace_back(event.before.value,event.after.value);
  check(native==std::vector<std::pair<std::uint64_t,std::uint64_t>>{{9,12},{12,5},{5,5},{5,11}},
      "captured contributions are not actual logical totals");
  auto rejected=model.runtime.begin_epoch(5);
  check(rejected.stage_contribution(NodeId{0},values,{2},{8}),"private contribution before rejection");
  error([&]{static_cast<void>(rejected.stage_contribution(NodeId{0},values,{18},{0}));},"annotation_underflow");
  check(!rejected.active() && model.runtime.ready() && model.runtime.sequence()==4,"contribution failure published");
  compare(model.runtime.snapshot(),recompute(model.runtime.structural_program(),model.inputs));
  auto removed=model.runtime.begin_epoch(5);
  check(removed.stage_contribution(NodeId{0},values,{11},{0}),"last contribution removal");
  static_cast<void>(removed.commit());model.inputs[0].clear();
  compare(model.runtime.snapshot(),recompute(model.runtime.structural_program(),model.inputs));
}

// Import compiler artifacts into one caller-owned account. Retained native
// metadata belongs to that receiver and survives destruction of the compiler.
void receiving_account(bool indexed) {
  const auto plan=unary(indexed);const auto source=CompiledProgram::standalone(plan);
  const auto source_before=source.account().statistics();
  const auto account=resource::MemoryAccount::create(8ULL*1024*1024);
  for (const bool native:{false,true}) {
    w::Options opts;opts.memory_limit_bytes=1;
    auto runtime=native ? runtime::WeightedRuntime::create_into(account,source,opts) :
        runtime::WeightedRuntime::create_into(account,plan,opts);
    check(runtime.owner()==account.statistics().owner &&
        runtime.options().memory_limit_bytes==account.statistics().limit_bytes,"receiver account/limit changed");
    static_cast<void>(runtime.apply({1,{NodeId{0},{n(3)},{0},{7}}}));
    check(runtime.root_weight().value==7,"receiver runtime did not execute");
  }
  check(source.account().statistics()==source_before,"runtime import changed compiler account");
  {
    auto held=[&] {
      const auto temporary=CompiledProgram::standalone(plan);
      return runtime::WeightedRuntime::create_into(account,temporary);
    }();
    static_cast<void>(held.apply({1,{NodeId{0},{n(4)},{0},{8}}}));
    check(held.root_weight().value==8,"receiver retained a borrowed compiler artifact");
  }
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),"receiver retained state");
  // A shared compiler/execution account is also valid; its allocations are
  // intentionally visible in that account rather than called compiler-only.
  const auto shared=resource::MemoryAccount::create(8ULL*1024*1024);
  const auto artifact=CompiledProgram::compile(shared,plan);
  const auto baseline=shared.statistics().current;
  {auto runtime=runtime::WeightedRuntime::create_into(shared,artifact);
    check(runtime.owner()==shared.statistics().owner,"shared receiver owner changed");}
  check(shared.statistics().current==baseline,"shared receiver import leaked");
}

// Only the call borrows native cells/string bytes. Mutating the caller's
// buffer afterward must not change retained keys or the compressed result.
void typed_contribution(bool indexed) {
  const Catalog catalog{1,{{"r",{{"s",ScalarType::string},{"b",ScalarType::boolean},
      {"d",ScalarType::date},{"n",ScalarType::decimal}}}}};
  const Query query{{{"s",ScalarType::string},{"b",ScalarType::boolean},
      {"d",ScalarType::date},{"n",ScalarType::decimal}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3}}}},
      {{VariableId{0},"s"},{VariableId{1},"b"},{VariableId{2},"d"},{VariableId{3},"n"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,
      {VariableId{0},VariableId{1},VariableId{2},VariableId{3}},{},0,{}}},{},{}};
  runtime::WeightedRuntime runtime(planner::lower_tree(catalog,query,tree,options(indexed)));
  std::string text(192,'x');text[40]='\0';const auto expected=text;
  const auto date=Date::parse("2024-02-29");
  const auto decimal=storage::InlineDecimal::parse("99999999999999999999999999999999999999");
  std::array<storage::ScalarView,4> cells{std::string_view(text),true,date,decimal};
  auto pending=runtime.begin_epoch(1);
  check(pending.stage_contribution(NodeId{0},
      storage::TupleValuesView::borrow(storage::RowView::borrow(cells)),{0},{13}),"typed contribution rejected");
  text.assign(text.size(),'y');cells[1]=false;
  static_cast<void>(pending.commit());
  auto cursor=runtime.results();const auto row=cursor.next();
  check(row && row->multiplicity.value==13,"typed contribution missing from cursor");
  const auto values=row->tuple.values();
  check(std::get<std::string_view>(values[0])==expected && std::get<bool>(values[1]) &&
      std::get<Date>(values[2])==date && std::get<storage::InlineDecimal>(values[3])==decimal,
      "retained contribution still borrows caller cells");
  check(!cursor.next(),"typed contribution cursor duplicate");
}

void boundaries(bool indexed) {
  for (const bool nullary:{false,true}) {
    Model model(unary(indexed,nullary,true));const Row row=nullary ? Row{} : Row{n(17)};
    model.set(0,row,UINT64_C(9007199254740993));
    check(model.runtime.root_weight().value==UINT64_C(9007199254740993),"lost integer precision above 2^53");
    model.set(0,row,0);
  }
  for (const bool contradiction:{false,true}) {
    Query query;query.contradiction=contradiction;
    const auto plan=planner::lower_tree(Catalog{},query,FreeConnexTree{},options(indexed));
    runtime::WeightedRuntime runtime(plan);
    check(runtime.root_weight().value==(contradiction ? 0U : 1U),"constant route summary");
  }
  runtime::WeightedRuntime g(generalized(indexed));
  error([&]{static_cast<void>(g.apply({1,{NodeId{2},{n(1),n(2)},{0},{1}}}));},"invalid_native_update");
  runtime::WeightedRuntime a(unary(indexed)),b(unary(indexed),w::Options{.multiplicity_limit=101});
  check(a.binding().weighted_sha256!=b.binding().weighted_sha256,"counter bound absent from weighted identity");
  check(a.binding().shape_sha256==b.binding().shape_sha256,"numeric bound changed structural binding");
  check(runtime::WeightedRuntime::profile().semantics=="exact_nonnegative_multiplicity","wrong weighted profile");
}

// Empty generalized scope represents the product of three disconnected
// components. Typed hidden keys must survive native storage and snapshots.
void disconnected_three(bool indexed) {
  const Catalog catalog{1,{{"a",{{"x",ScalarType::int64}}},
      {"b",{{"y",ScalarType::string}}},{"c",{{"z",ScalarType::boolean}}}}};
  const Query query{{{"x",ScalarType::int64},{"y",ScalarType::string},{"z",ScalarType::boolean}},
      {{"a",TableId{0},{VariableId{0}}},{"b",TableId{1},{VariableId{1}}},
       {"c",TableId{2},{VariableId{2}}}},{},false};
  const FreeConnexTree tree{NodeId{0},{
      {"unit",NodeKind::generalized,{}, {NodeId{1},NodeId{2},NodeId{3}},{},{}},
      {"a",NodeKind::native,{VariableId{0}},{},0,{}},
      {"b",NodeKind::native,{VariableId{1}},{},1,{}},
      {"c",NodeKind::native,{VariableId{2}},{},2,{}}},{},{}};
  Model model(planner::lower_tree(catalog,query,tree,options(indexed)));
  model.set(1,{n(1)},2);model.set(1,{n(2)},3);
  model.set(2,{Value{std::string("hidden")}},7);model.set(3,{Value{true}},11);
  check(model.runtime.root_weight().value==385,"three-component empty-key product");
  model.set(3,{Value{false}},13);model.set(2,{Value{std::string("hidden")}},0);
  check(model.runtime.root_weight().value==0 && model.runtime.snapshot().nodes[0].records.size()==1,
      "empty-key partial candidate");
  model.set(1,{n(1)},0);model.set(1,{n(2)},0);
  model.set(3,{Value{true}},0);model.set(3,{Value{false}},0);
  check(model.runtime.snapshot().nodes[0].records.empty(),"empty-key candidate was not reclaimed");
}

// Runtime propagation is iterative in tree depth. Use unit native factors to
// keep the exhaustive assignment oracle bounded while visiting every message.
void deep_chain() {
  constexpr std::size_t length=256;
  Catalog catalog;Query query;query.variables={{"x",ScalarType::int64}};query.head={{VariableId{0},"x"}};
  FreeConnexTree tree;tree.root=NodeId{0};
  for (std::size_t i=0;i<length;++i) {
    const auto name="n"+std::to_string(i);catalog.tables.push_back({name,{{"x",ScalarType::int64}}});
    query.atoms.push_back({name,TableId{i},{VariableId{0}}});
    tree.nodes.push_back({name,NodeKind::native,{VariableId{0}},{},i,{}});
    if (i) tree.nodes[i-1].children.push_back(NodeId{i});
  }
  Model model(planner::lower_tree(catalog,query,tree));
  // Stage all unit inputs in one bounded transaction, comparing its final state.
  auto pending=model.runtime.begin_epoch(1);
  for (std::size_t i=0;i<length;++i) {
    static_cast<void>(pending.stage({NodeId{i},{n(1)},{0},{1}}));model.inputs[i][Row{n(1)}]=1;
  }
  static_cast<void>(pending.commit());
  compare(model.runtime.snapshot(),recompute(model.runtime.structural_program(),model.inputs));
  const auto changed=model.set(length-1,{n(1)},2);
  check(changed.metrics.events_applied==length && changed.after.value==2,"deep numeric queue");
  model.set(length-1,{n(1)},0);
}
} // namespace

int main() {
  try {
    for (const bool indexed:{false,true}) {
      native_numeric(indexed);generalized_sums(indexed);causal_fifo(indexed);
      random_model(indexed);private_epochs(indexed);boundaries(indexed);disconnected_three(indexed);
      contributions(indexed);receiving_account(indexed);typed_contribution(indexed);
    }
    deep_chain();
    std::cout<<"weighted messages: independent state after every update, both backends\n";
  } catch (const std::exception& failure) {std::cerr<<failure.what()<<'\n';return 1;}
}
