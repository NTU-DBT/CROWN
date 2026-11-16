#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/physical.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"

#include <cstdint>
#include <iterator>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition,const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
template<class Action> void error(Action&& action,std::string_view code) {
  try { action(); }
  catch (const Error& failure) {
    check(failure.code()==code,"expected "+std::string(code)+", got "+failure.code());
    return;
  }
  throw std::runtime_error("missing error "+std::string(code));
}
Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }

Relation drain_unique(SupportRuntime::ResultCursor& cursor) {
  Relation result;
  while (auto row=cursor.next()) {
    check(row->layout().same_token(cursor.layout()),"returned row does not retain the cursor output layout");
    check(result.insert(crown::storage::export_row(row->values())).second,"cursor emitted a duplicate projected row");
  }
  check(cursor.state()==ResultCursorState::exhausted && !cursor.active(),"cursor did not close on exhaustion");
  check(!cursor.next(),"exhausted cursor did not keep returning nullopt");
  return result;
}

void insert(PhysicalRuntime& runtime,Database& database,std::uint64_t& sequence,TableId table,Row row) {
  const auto result=runtime.apply({++sequence,table,SetOperation::insert,row});
  check(result.input.physical_changed,"fixture source row was not inserted");
  check(database.tables.at(table.value).insert(std::move(row)).second,"duplicate fixture source row");
}

PhysicalPlan one_column_plan() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"witness",ScalarType::string}}}}};
  const Query query{{{"x",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},IgnoredColumn{}}}},
      {{VariableId{0},"x"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree);
}

PhysicalPlan shared_key_plan(std::size_t arity) {
  check(arity>=2,"shared-key plan needs at least two children");
  Catalog catalog; catalog.version=1;
  Query query; query.variables={{"x",ScalarType::int64}};
  for (std::size_t i=0;i<arity;++i) query.variables.push_back({"z"+std::to_string(i),ScalarType::int64});
  for (std::size_t i=0;i<arity;++i) query.variables.push_back({"h"+std::to_string(i),ScalarType::int64});
  const auto last_z=VariableId{arity};
  query.head.push_back({last_z,"last"});
  query.head.push_back({VariableId{0},"x"});
  for (std::size_t i=0;i+1<arity;++i) query.head.push_back({VariableId{i+1},"z"+std::to_string(i)});
  query.head.push_back({last_z,"again_last"});
  std::vector<NodeId> children;
  for (std::size_t i=0;i<arity;++i) {
    catalog.tables.push_back({"t"+std::to_string(i),{{"key",ScalarType::int64},{"value",ScalarType::int64},
        {"hidden_witness",ScalarType::int64},{"payload",ScalarType::string}}});
    query.atoms.push_back({"t"+std::to_string(i),TableId{i},
        {VariableId{0},VariableId{i+1},VariableId{arity+i+1},IgnoredColumn{}}});
    children.push_back(NodeId{i+1});
  }
  FreeConnexTree tree;
  tree.root=NodeId{0};
  tree.nodes.push_back({"join",NodeKind::generalized,{VariableId{0}},children,{},{}});
  for (std::size_t i=0;i<arity;++i)
    tree.nodes.push_back({"t"+std::to_string(i),NodeKind::native,
        {VariableId{0},VariableId{i+1},VariableId{arity+i+1}},{},i,{}});
  return planner::lower_tree(catalog,query,tree);
}

PhysicalPlan disconnected_plan(std::vector<Output> head) {
  Catalog catalog{1,{{"x_source",{{"value",ScalarType::int64},{"witness",ScalarType::string}}},
                     {"y_source",{{"value",ScalarType::int64},{"witness",ScalarType::string}}},
                     {"z_source",{{"value",ScalarType::int64},{"witness",ScalarType::string}}}}};
  Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64},{"z",ScalarType::int64}},
      {{"x_source",TableId{0},{VariableId{0},IgnoredColumn{}}},
       {"y_source",TableId{1},{VariableId{1},IgnoredColumn{}}},
       {"z_source",TableId{2},{VariableId{2},IgnoredColumn{}}}},std::move(head),false};
  const FreeConnexTree tree{NodeId{0},
      {{"product",NodeKind::generalized,{},
         {NodeId{1},NodeId{2},NodeId{3}},{},{}},
       {"x_source",NodeKind::native,{VariableId{0}},{},0,{}},
       {"y_source",NodeKind::native,{VariableId{1}},{},1,{}},
       {"z_source",NodeKind::native,{VariableId{2}},{},2,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree);
}

PhysicalPlan native_chain_plan() {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64},{"y",ScalarType::int64}}},
                           {"s",{{"y",ScalarType::int64},{"z",ScalarType::int64}}},
                           {"t",{{"z",ScalarType::int64},{"w",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::int64},{"y",ScalarType::int64},
                     {"z",ScalarType::int64},{"w",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},
       {"s",TableId{1},{VariableId{1},VariableId{2}}},
       {"t",TableId{2},{VariableId{2},VariableId{3}}}},
      {{VariableId{3},"w"},{VariableId{0},"x"},{VariableId{2},"z"},
       {VariableId{1},"y"},{VariableId{3},"again_w"}},false};
  const FreeConnexTree tree{NodeId{0},
      {{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
       {"s",NodeKind::native,{VariableId{1},VariableId{2}},{NodeId{2}},1,{}},
       {"t",NodeKind::native,{VariableId{2},VariableId{3}},{},2,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree);
}

PhysicalPlan nullary_atom_plan() {
  const Catalog catalog{1,{{"flags",{{"tag",ScalarType::string}}}}};
  const Query query{{},{{"flags",TableId{0},{IgnoredColumn{}}}},{},false};
  const FreeConnexTree tree{NodeId{0},{{"flags",NodeKind::native,{}, {},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree);
}

PhysicalPlan constant_plan(bool contradiction) {
  const Catalog catalog{1,{{"unused",{{"id",ScalarType::int64}}}}};
  const Query query{{},{},{},contradiction};
  return planner::lower_tree(catalog,query,FreeConnexTree{});
}

std::optional<VariableId> variable_term(const Term& term) {
  if (const auto* variable=std::get_if<VariableId>(&term)) return *variable;
  return {};
}
FreeConnexTree sql_tree(const Query& query) {
  FreeConnexTree tree;
  if (query.contradiction || query.atoms.empty()) return tree;
  std::vector<VariableSet> scopes(query.atoms.size());
  for (std::size_t i=0;i<query.atoms.size();++i) {
    for (const auto& term : query.atoms[i].terms) if (const auto variable=variable_term(term)) {
      scopes[i].insert(*variable);
    }
  }
  if (query.atoms.size()==1) {
    tree.root=NodeId{0};
    tree.nodes.push_back({query.atoms[0].occurrence,NodeKind::native,scopes[0],{},0,{}});
    return tree;
  }
  VariableSet common=scopes.front();
  for (std::size_t i=1;i<scopes.size();++i) {
    VariableSet overlap;
    std::set_intersection(common.begin(),common.end(),scopes[i].begin(),scopes[i].end(),
        std::inserter(overlap,overlap.end()));
    common=std::move(overlap);
  }
  std::vector<NodeId> children;
  for (std::size_t i=0;i<query.atoms.size();++i) children.push_back(NodeId{i+1});
  tree.root=NodeId{0};
  tree.nodes.push_back({"sql_product",NodeKind::generalized,common,children,{},{}});
  for (std::size_t i=0;i<query.atoms.size();++i)
    tree.nodes.push_back({query.atoms[i].occurrence,NodeKind::native,scopes[i],{},i,{}});
  return tree;
}
PhysicalPlan normalized_plan(std::string_view sql,const Catalog& catalog) {
  const auto binding=frontend::bind_sql(sql,catalog);
  if (const auto* failure=std::get_if<frontend::BindingDiagnostic>(&binding))
    throw std::runtime_error(failure->diagnostic.code+": "+failure->diagnostic.message);
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  if (const auto* failure=std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code+": "+failure->diagnostic.message);
  auto program=std::get<frontend::NormalizedSql>(std::move(normalized));
  auto tree=sql_tree(program.core);
  return planner::lower_normalized(program,tree);
}

Relation normalized_core_reference(const auto& plan,const Database& physical) {
  const auto& program=reference::input::normalized(*plan.normalized());
  Database logical; logical.tables.resize(program.core_catalog.tables.size());
  for (std::size_t i=0;i<program.adapters.size();++i) {
    const auto& adapter=program.adapters[i];
    const auto occurrence=adapter.occurrence.value;
    const auto target=program.core.atoms.at(occurrence).table.value;
    for (const auto& row : physical.tables.at(adapter.base.value))
      if (auto mapped=frontend::adapt_row(program,adapter.occurrence,row))
        logical.tables.at(target).insert(std::move(*mapped));
  }
  return reference::evaluate(program.core_catalog,program.core,logical);
}

Relation cursor_matches_reference(PhysicalRuntime& runtime,const Database& database) {
  const auto expected=reference::evaluate(reference::input::catalog(runtime.plan().catalog()),reference::input::query(runtime.plan().query()),database);
  auto cursor=runtime.core_results();
  check(cursor.sequence()==runtime.sequence() && cursor.owner()==runtime.owner(),"core cursor did not pin its source epoch identity");
  const auto actual=drain_unique(cursor);
  check(actual==expected,"core cursor differs from the A04 materializing reference evaluator");
  return actual;
}

void shared_key_and_product_differential(std::size_t arity) {
  auto plan=shared_key_plan(arity);
  PhysicalRuntime runtime(std::move(plan));
  Database database; database.tables.resize(arity);
  std::uint64_t sequence=0;
  for (std::size_t i=0;i<arity;++i) {
    for (std::int64_t choice=1;choice<=2;++choice) for (std::int64_t hidden=1;hidden<=2;++hidden)
      insert(runtime,database,sequence,TableId{i},
          {n(7),n(static_cast<std::int64_t>(i*10)+choice),n(hidden),s("common-"+std::to_string(choice)+"-"+std::to_string(hidden))});
    insert(runtime,database,sequence,TableId{i},
        {n(static_cast<std::int64_t>(100+i)),n(static_cast<std::int64_t>(i*10)+3),n(1),s("unmatched")});
  }
  const auto expected=reference::evaluate(reference::input::catalog(runtime.plan().catalog()),reference::input::query(runtime.plan().query()),database);
  auto cursor=runtime.core_results();
  const auto step_count=runtime.plan().enumeration().steps.size();
  check(step_count>=arity+1,"N-ary product plan did not include the root and each child frame");
  const auto actual=drain_unique(cursor);
  check(actual==expected && actual.size()==(std::size_t{1}<<arity),
      "shared-key N-ary product differs from the A04 reference or has duplicate projections");
  check(cursor.metrics().results.rows_emitted==actual.size() && cursor.metrics().results.selected_rows>=step_count &&
        cursor.metrics().results.cursor_opens>=step_count,
      "cursor result work did not visit the N-ary product's root and child frames");
  for (const auto& row : actual)
    check(row.front()==row.back() && row.at(1)==n(7),"reordered/repeated N-ary head columns were assembled incorrectly");
}

Database disconnected_database() {
  Database database; database.tables.resize(3);
  database.tables[0]={{n(1),s("x-a")},{n(1),s("x-b")},{n(2),s("x-c")}};
  database.tables[1]={{n(10),s("y-a")},{n(20),s("y-b")},{n(20),s("y-c")},{n(30),s("y-d")}};
  database.tables[2]={{n(7),s("z-a")},{n(8),s("z-b")},{n(8),s("z-c")}};
  return database;
}
void fill_disconnected(PhysicalRuntime& runtime,const Database& database,std::uint64_t& sequence) {
  for (std::size_t table=0;table<database.tables.size();++table)
    for (const auto& row : database.tables[table]) {
      const auto result=runtime.apply({++sequence,TableId{table},SetOperation::insert,row});
      check(result.input.physical_changed,"disconnected fixture row was not inserted");
    }
}
void disconnected_products_and_projections() {
  const auto database=disconnected_database();
  {
    auto plan=disconnected_plan({{VariableId{2},"z"},{VariableId{0},"x"},
        {VariableId{2},"again_z"},{VariableId{1},"y"}});
    PhysicalRuntime runtime(std::move(plan)); std::uint64_t sequence=0; fill_disconnected(runtime,database,sequence);
    const auto actual=cursor_matches_reference(runtime,database);
    check(actual.size()==12,"disconnected product cardinality did not multiply its three distinct projections");
    check(actual.contains(Row{n(7),n(1),n(7),n(10)}) && actual.contains(Row{n(8),n(2),n(8),n(30)}),
        "reordered or repeated core head columns were assembled incorrectly");
  }
  {
    auto plan=disconnected_plan({{VariableId{0},"x"}});
    PhysicalRuntime runtime(std::move(plan)); std::uint64_t sequence=0; fill_disconnected(runtime,database,sequence);
    const auto actual=cursor_matches_reference(runtime,database);
    check(actual==Relation{{n(1)},{n(2)}},"root projection retained duplicates from hidden product variables");
  }
}

void native_chain_differential() {
  PhysicalRuntime runtime(native_chain_plan());
  Database database; database.tables.resize(3);
  std::uint64_t sequence=0;
  for (const auto& row : {Row{n(1),n(10)},Row{n(2),n(20)}})
    insert(runtime,database,sequence,TableId{0},row);
  for (const auto& row : {Row{n(10),n(100)},Row{n(10),n(200)},Row{n(20),n(300)}})
    insert(runtime,database,sequence,TableId{1},row);
  for (const auto& row : {Row{n(100),n(7)},Row{n(100),n(70)},Row{n(200),n(8)},
                          Row{n(200),n(80)},Row{n(300),n(9)}})
    insert(runtime,database,sequence,TableId{2},row);

  const auto& steps=runtime.plan().enumeration().steps;
  check(steps.size()==3 && steps[1].parent_step==0 && steps[2].parent_step==1,
      "native chain enumeration did not retain its depth-three parent steps");
  check(steps[1].parent_key && steps[1].parent_key->fields().size()==1 &&
        steps[1].parent_key->fields()[0].value==1 && steps[1].bucket_index &&
        steps[2].parent_key && steps[2].parent_key->fields().size()==1 &&
        steps[2].parent_key->fields()[0].value==1 && steps[2].bucket_index,
      "native chain did not select its second-level separator fields by numeric position");

  const auto expected=reference::evaluate(reference::input::catalog(runtime.plan().catalog()),reference::input::query(runtime.plan().query()),database);
  auto cursor=runtime.core_results();
  const auto actual=drain_unique(cursor);
  check(actual==expected && actual.size()==5,
      "depth-three chain cursor differs from the A04 reference or repeated-head projection");
  check(actual.contains(Row{n(7),n(1),n(100),n(10),n(7)}) &&
        actual.contains(Row{n(80),n(1),n(200),n(10),n(80)}) &&
        actual.contains(Row{n(9),n(2),n(300),n(20),n(9)}),
      "depth-three chain failed to follow the distinct y and z separator keys");
  check(cursor.metrics().results.bucket_lookups>0 && cursor.metrics().results.rows_emitted==5,
      "depth-three cursor did not charge its keyed child traversals");
}

void nullary_and_constant_routes() {
  {
    PhysicalRuntime runtime(nullary_atom_plan()); Database database; database.tables.resize(1);
    check(cursor_matches_reference(runtime,database).empty(),"empty nullary atom emitted an empty tuple");
    std::uint64_t sequence=0;
    insert(runtime,database,sequence,TableId{0},{s("first")});
    insert(runtime,database,sequence,TableId{0},{s("second")});
    check(cursor_matches_reference(runtime,database)==Relation{{}},"nonempty nullary atom did not emit exactly one empty tuple");
  }
  for (const bool contradiction : {false,true}) {
    auto plan=constant_plan(contradiction);
    PhysicalRuntime runtime(std::move(plan)); Database database; database.tables.resize(1);
    const auto actual=cursor_matches_reference(runtime,database);
    check(actual==(contradiction?Relation{}:Relation{{}}),"constant route did not return the correct nullary truth row");
  }
}

void lease_reads_writes_and_pending_creation() {
  PhysicalRuntime runtime(one_column_plan()); Database database; database.tables.resize(1);
  std::uint64_t sequence=0; insert(runtime,database,sequence,TableId{0},{n(5),s("one")});
  auto first=runtime.core_results();
  auto second=runtime.core_results();
  const auto owner=runtime.owner();
  check(first.active() && second.active() && first.state()==ResultCursorState::active &&
        first.owner()==owner && first.sequence()==sequence,"new result cursors did not capture active owner and epoch");
  check(first.layout().fields().size()==1 && !runtime.ready(),"active result lease did not pin readiness and output layout");
  check(runtime.has_answer() && runtime.snapshot().sequence==sequence &&
        runtime.derivation_count(OccurrenceId{0},{n(5)})==1 && runtime.storage_statistics().derivation_keys==1,
        "read-only runtime APIs failed while result cursors were active");
  runtime.check_invariants();
  error([&] { static_cast<void>(runtime.apply({sequence+1,TableId{0},SetOperation::insert,{n(5),s("one")}})); },"runtime_busy");
  error([&] { static_cast<void>(runtime.prepare({sequence+1,TableId{0},SetOperation::erase,{n(99),s("missing")}})); },"runtime_busy");

  auto owned=first.next();
  check(owned && owned->values()==Row{n(5)},"first simultaneous cursor returned the wrong row");
  first.cancel();
  check(first.state()==ResultCursorState::cancelled && !first.active() && !first.next() && !first.next(),
      "cancelled cursor did not close and return nullopt repeatedly");
  check(!runtime.ready(),"cancelling one cursor released another cursor's read lease");
  check(drain_unique(second)==Relation{{n(5)}},"second simultaneous cursor returned the wrong relation");
  check(runtime.ready(),"exhaustion did not release the last result lease");

  {
    auto pending=runtime.prepare({sequence+1,TableId{0},SetOperation::insert,{n(6),s("pending")}});
    check(!runtime.ready(),"prepared update did not mark the runtime busy");
    error([&] { static_cast<void>(runtime.core_results()); },"runtime_busy");
  }
  check(runtime.ready(),"pending update destruction did not restore readiness");
  const auto next=runtime.apply({sequence+1,TableId{0},SetOperation::insert,{n(6),s("committed")}});
  check(next.input.physical_changed && runtime.sequence()==sequence+1,"cancelled prepare changed the next committed sequence");
  check(owned && owned->values()==Row{n(5)},"returned tuple did not own its row past cursor cancellation and update");
}

void cursor_moves_and_facade_lifetime() {
  {
    PhysicalRuntime original(one_column_plan());
    static_cast<void>(original.apply({1,TableId{0},SetOperation::insert,{n(11),s("move")}}));
    const auto owner=original.owner();
    auto cursor=original.core_results();
    auto moved_cursor=std::move(cursor);
    error([&] { static_cast<void>(cursor.next()); },"invalid_cursor");
    check(!cursor.active() && moved_cursor.active() && moved_cursor.owner()==owner,
        "moving a cursor lost the leased runtime identity");
    PhysicalRuntime moved_runtime(std::move(original));
    error([&] { static_cast<void>(original.sequence()); },"invalid_runtime");
    check(!moved_runtime.ready() && moved_cursor.sequence()==1,"moving the facade invalidated its live cursor");
    auto saved=moved_cursor.next();
    check(saved && saved->values()==Row{n(11)},"moved cursor could not continue on the moved facade");
    moved_cursor.cancel();
    static_cast<void>(moved_runtime.apply({2,TableId{0},SetOperation::erase,{n(11),s("move")}}));
    check(saved->values()==Row{n(11)},"row returned before a runtime move did not remain owning");
  }
  {
    PhysicalRuntime runtime(one_column_plan());
    static_cast<void>(runtime.apply({1,TableId{0},SetOperation::insert,{n(13),s("move-assign")}}));
    {
      auto abandoned=runtime.core_results();
      check(!runtime.ready(),"new cursor did not acquire a destructor-managed lease");
    }
    check(runtime.ready(),"cursor destruction did not release its read lease");
    auto destination=runtime.core_results();
    auto source=runtime.core_results();
    destination=std::move(source);
    error([&] { static_cast<void>(source.state()); },"invalid_cursor");
    check(destination.active() && !runtime.ready(),"cursor move assignment lost the transferred lease");
    destination.cancel();
    check(runtime.ready(),"cursor move assignment retained the replaced lease");
  }
  {
    std::optional<SupportRuntime::ResultCursor> cursor;
    {
      auto facade=std::make_unique<PhysicalRuntime>(one_column_plan());
      static_cast<void>(facade->apply({1,TableId{0},SetOperation::insert,{n(12),s("facade-death")}}));
      cursor.emplace(facade->core_results());
      facade.reset();
    }
    check(cursor && cursor->active(),"cursor lease did not keep its runtime state alive after facade destruction");
    auto saved=cursor->next();
    check(saved && saved->values()==Row{n(12)},"cursor could not finish after its facade was destroyed");
    check(!cursor->next() && cursor->state()==ResultCursorState::exhausted,
        "cursor did not release its state after facade destruction");
  }
}

void work_metrics_handtrace_and_cap() {
  PhysicalRuntime runtime(one_column_plan());
  static_cast<void>(runtime.apply({1,TableId{0},SetOperation::insert,{n(1),s("metrics")}}));
  auto cursor=runtime.core_results();
  const auto steps=runtime.plan().enumeration().steps.size();
  const auto& startup=cursor.metrics().startup;
  check(startup.work==1+steps && startup.route_checks==1 && startup.frame_initializations==steps,
      "cursor startup work did not match route and query frame initialization");
  check(startup.cursor_opens==0 && startup.cursor_advances==0 && startup.tuple_lookups==0 &&
        startup.selected_rows==0 && startup.rows_emitted==0 && cursor.metrics().total_work==startup.work,
      "cursor startup visited or advanced a row");
  check(cursor.metrics().last.work==0 && cursor.metrics().results.work==0 && cursor.metrics().termination.work==0,
      "cursor charged work to a result phase before next()");
  auto result=cursor.next();
  check(result && result->values()==Row{n(1)},"metrics hand trace did not emit its only row");
  const auto emitted=cursor.metrics().last;
  check(emitted.work==7 && emitted.calls==1 && emitted.cursor_opens==1 && emitted.cursor_advances==1 &&
        emitted.tuple_lookups==1 && emitted.selected_rows==1 && emitted.output_fields==1 && emitted.rows_emitted==1,
      "single-row result work did not match the hand trace");
  check(cursor.metrics().results.work==7 && cursor.metrics().max_result_work==7 &&
        cursor.metrics().total_work==startup.work+7,"result phase totals or maximum work differ from the hand trace");
  check(!cursor.next(),"one-row cursor did not terminate");
  const auto terminal=cursor.metrics().last;
  check(terminal.work==3 && terminal.calls==1 && terminal.cursor_advances==1 && terminal.frame_closes==1,
      "termination phase work did not match the hand trace");
  check(cursor.metrics().termination.work==3 && cursor.metrics().results.work==7 &&
        cursor.metrics().max_result_work==7 && cursor.metrics().total_work==startup.work+10 &&
        cursor.metrics().last.work==terminal.work,"result and termination metrics were not kept in separate phases");

  PhysicalRuntime limited(one_column_plan());
  static_cast<void>(limited.apply({1,TableId{0},SetOperation::insert,{n(2),s("limited")}}));
  auto failing=limited.core_results(ResultCursorOptions{4});
  check(failing.metrics().startup.work==2 && !limited.ready(),"work-cap cursor startup did not take its exact budget");
  error([&] { static_cast<void>(failing.next()); },"resource_limit");
  check(failing.state()==ResultCursorState::failed && !failing.active() && limited.ready(),
      "work-cap failure did not close its result lease");
  check(failing.metrics().failed.work==2 && failing.metrics().failed.calls==1 &&
        failing.metrics().failed.cursor_opens==1 && failing.metrics().failed.cursor_advances==0 &&
        failing.metrics().last.work==2 && failing.metrics().total_work==4 &&
        failing.metrics().cleanup_frames==1,"failed work was not recorded or cleaned up accurately");
  error([&] { static_cast<void>(failing.next()); },"invalid_cursor");
  static_cast<void>(limited.apply({2,TableId{0},SetOperation::insert,{n(2),s("limited")}}));
  limited.check_invariants();
}

void sql_results_and_exists_mapping() {
  const Catalog catalog{9,{{"lefts",{{"x",ScalarType::int64},{"witness",ScalarType::string}}},
                           {"rights",{{"x",ScalarType::int64},{"witness",ScalarType::string}}}}};
  auto plan=normalized_plan("SELECT DISTINCT r.x, l.x, r.x AS again, 7 AS fixed FROM lefts l, rights r",catalog);
  PhysicalRuntime runtime(std::move(plan)); Database database; database.tables.resize(2);
  std::uint64_t sequence=0;
  insert(runtime,database,sequence,TableId{0},{n(1),s("left-a")});
  insert(runtime,database,sequence,TableId{0},{n(1),s("left-b")});
  insert(runtime,database,sequence,TableId{0},{n(2),s("left-c")});
  insert(runtime,database,sequence,TableId{1},{n(10),s("right-a")});
  insert(runtime,database,sequence,TableId{1},{n(20),s("right-b")});
  insert(runtime,database,sequence,TableId{1},{n(20),s("right-c")});
  const auto core=normalized_core_reference(runtime.plan(),database);
  const auto sql_expected=frontend::map_sql_result(reference::input::normalized(*runtime.plan().normalized()),core);
  auto first=runtime.results();
  auto second=runtime.results();
  check(first.layout().fields().size()==4 && first.layout().same_token(second.layout()),
      "concurrent SQL cursors did not share the runtime's ordered output layout");
  auto retained=first.next();
  check(retained && retained->values().size()==4 && retained->layout().same_token(second.layout()),
      "SQL cursor did not map repeated and constant outputs into its shared layout");
  first.cancel();
  check(drain_unique(second)==sql_expected && sql_expected.size()==4,
      "SQL result cursor differs from frontend::map_sql_result for repeated and constant outputs");
  auto core_cursor=runtime.core_results();
  check(drain_unique(core_cursor)==core,"PhysicalRuntime::core_results did not preserve the normalized core result");

  insert(runtime,database,sequence,TableId{0},{n(3),s("left-new")});
  const auto next_core=normalized_core_reference(runtime.plan(),database);
  const auto next_expected=frontend::map_sql_result(reference::input::normalized(*runtime.plan().normalized()),next_core);
  auto next_sql=runtime.results();
  check(retained->layout().same_token(next_sql.layout()),"SQL output layout token changed across committed epochs");
  check(drain_unique(next_sql)==next_expected,"SQL cursor changed output mapping after an epoch update");

  const Catalog exists_catalog{3,{{"r",{{"x",ScalarType::int64}}}}};
  auto exists_plan=normalized_plan("SELECT EXISTS(SELECT NULL FROM r)",exists_catalog);
  PhysicalRuntime exists(std::move(exists_plan)); Database exists_database; exists_database.tables.resize(1);
  auto check_exists=[&](bool expected_value) {
    const auto expected_core=normalized_core_reference(exists.plan(),exists_database);
    const auto expected_sql=frontend::map_sql_result(reference::input::normalized(*exists.plan().normalized()),expected_core);
    check(expected_sql==Relation{{Value{expected_value}}},"EXISTS frontend mapper returned the wrong Boolean row");
    auto core_rows=exists.core_results();
    check(drain_unique(core_rows)==expected_core,"EXISTS core_results did not expose its inner core relation");
    auto sql_rows=exists.results();
    check(sql_rows.layout().fields().size()==1 && sql_rows.layout().fields()[0].type==ScalarType::boolean,
        "EXISTS cursor did not expose a single Boolean SQL column");
    check(drain_unique(sql_rows)==expected_sql,"EXISTS SQL cursor differs from frontend::map_sql_result");
  };
  check_exists(false);
  std::uint64_t exists_sequence=0;
  insert(exists,exists_database,exists_sequence,TableId{0},{n(44)});
  check_exists(true);
}

void sql_constant_only_rows() {
  const Catalog source_catalog{5,{{"r",{{"x",ScalarType::int64}}}}};
  auto source_plan=normalized_plan("SELECT DISTINCT 7 AS fixed FROM r",source_catalog);
  check(source_plan.route()==PhysicalRoute::tree && source_plan.query().atoms.size()==1 &&
        source_plan.tree().nodes.size()==1 && source_plan.tree().nodes[0].scope.empty(),
      "constant-only source query did not lower to a nullary native projection");
  PhysicalRuntime source(std::move(source_plan)); Database source_database; source_database.tables.resize(1);
  const auto empty_core=normalized_core_reference(source.plan(),source_database);
  const auto empty_expected=frontend::map_sql_result(reference::input::normalized(*source.plan().normalized()),empty_core);
  check(empty_expected.empty(),"empty source unexpectedly mapped a constant output row");
  auto empty_first=source.results();
  auto empty_second=source.results();
  const auto source_layout=empty_first.layout();
  check(empty_first.layout().same_token(empty_second.layout()),"empty constant SQL cursors did not share their layout token");
  check(drain_unique(empty_first).empty() && drain_unique(empty_second).empty(),
      "constant-only SQL query returned a row for an empty source");

  std::uint64_t sequence=0;
  insert(source,source_database,sequence,TableId{0},{n(1)});
  insert(source,source_database,sequence,TableId{0},{n(2)});
  check(source.derivation_count(OccurrenceId{0},{})==2,
      "distinct physical rows did not accumulate two nullary native derivations");
  const auto core=normalized_core_reference(source.plan(),source_database);
  check(core==Relation{{}},"constant-only SQL core did not retain one nullary row");
  const auto expected=frontend::map_sql_result(reference::input::normalized(*source.plan().normalized()),core);
  check(expected==Relation{{n(7)}},"frontend SQL mapper did not produce the one constant output row");
  auto first=source.results();
  auto second=source.results();
  check(first.layout().same_token(second.layout()) && first.layout().same_token(source_layout),
      "constant SQL layout token changed across cursors or committed epochs");
  auto retained=first.next();
  check(retained && retained->values()==Row{n(7)} && retained->layout().same_token(source_layout),
      "constant-only SQL cursor did not emit its owning constant row");
  first.cancel();
  check(drain_unique(second)==expected,"constant-only SQL cursor did not collapse nullary projection counts");
  auto core_cursor=source.core_results();
  check(drain_unique(core_cursor)==core,"constant-only SQL core_results did not preserve its nullary core row");

  const Catalog empty_catalog{1,{}};
  auto source_free_plan=normalized_plan("SELECT DISTINCT 7 AS fixed",empty_catalog);
  check(source_free_plan.route()==PhysicalRoute::constant_true && source_free_plan.tree().nodes.empty(),
      "source-free SQL constant did not lower to an empty constant-true tree");
  PhysicalRuntime source_free(std::move(source_free_plan)); Database no_sources;
  const auto source_free_core=normalized_core_reference(source_free.plan(),no_sources);
  const auto source_free_expected=frontend::map_sql_result(reference::input::normalized(*source_free.plan().normalized()),source_free_core);
  check(source_free_expected==Relation{{n(7)}},"source-free SQL constant mapper returned the wrong row");
  auto source_free_cursor=source_free.results();
  auto source_free_tuple=source_free_cursor.next();
  check(source_free_tuple && source_free_tuple->values()==Row{n(7)} && source_free_cursor.next()==std::nullopt,
      "source-free constant SQL route did not emit exactly one constant row");
  check(source_free_cursor.state()==ResultCursorState::exhausted &&
        source_free_tuple->layout().same_token(source_free_cursor.layout()),
      "source-free constant SQL result did not retain its shared output layout");

  auto contradiction_plan=normalized_plan("SELECT DISTINCT 7 AS fixed FROM r WHERE FALSE",source_catalog);
  check(contradiction_plan.route()==PhysicalRoute::constant_false && contradiction_plan.tree().nodes.empty(),
      "false SQL constant did not lower through the grounded empty tree");
  PhysicalRuntime contradiction(std::move(contradiction_plan)); Database contradiction_database; contradiction_database.tables.resize(1);
  const auto contradiction_core=normalized_core_reference(contradiction.plan(),contradiction_database);
  const auto contradiction_expected=frontend::map_sql_result(reference::input::normalized(*contradiction.plan().normalized()),contradiction_core);
  check(contradiction_expected.empty(),"frontend SQL mapper emitted a constant row for contradiction");
  auto contradiction_cursor=contradiction.results();
  check(drain_unique(contradiction_cursor).empty(),"constant-false SQL route emitted a row");
}

}  // namespace

int main() {
  static_assert(!std::is_copy_constructible_v<SupportRuntime::ResultCursor>);
  static_assert(std::is_nothrow_move_constructible_v<SupportRuntime::ResultCursor>);
  static_assert(std::is_nothrow_move_assignable_v<SupportRuntime::ResultCursor>);
  try {
    shared_key_and_product_differential(3);
    shared_key_and_product_differential(8);
    disconnected_products_and_projections();
    native_chain_differential();
    nullary_and_constant_routes();
    lease_reads_writes_and_pending_creation();
    cursor_moves_and_facade_lifetime();
    work_metrics_handtrace_and_cap();
    sql_results_and_exists_mapping();
    sql_constant_only_rows();
    std::cout<<"result cursor differential, lifecycle, SQL mapping, and work metrics PASS\n";
  } catch (const std::exception& failure) {
    std::cerr<<failure.what()<<'\n';
    return 1;
  }
}
