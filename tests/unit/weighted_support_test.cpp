#include "weighted_bag_fixture.hpp"
#include "crown/runtime/sql_rows.hpp"
#include "crown/planner/oracle.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <span>
#include <string>
#include <utility>
#include <vector>

// Independent full-assignment joins and SQL source loops check endpoint output;
// no factor/support traversal is reused by these test oracles.
namespace {
using namespace crown;
using namespace crown::weighted_test;
using Signed=std::pair<bool,std::uint64_t>;
using Deltas=std::map<Row,Signed>;
std::uint64_t transactions=0,stages=0;

Deltas read(std::span<const w::BagDelta> rows,bool support) {
  Deltas result;
  for(const auto& row:rows) {
    check(row.change.magnitude.present(),"zero captured change");
    check(!support || row.change.magnitude.value==1,"support change was not unit");
    check(result.emplace(storage::export_row(row.tuple.values()),
        Signed{row.change.negative,row.change.magnitude.value}).second,"duplicate change key");
  }
  return result;
}
Deltas support_difference(const Counts& before,const Counts& after) {
  Deltas result;
  for(const auto& [row,count]:before) {
    check(count!=0,"oracle retained zero");
    if(!after.contains(row))result.emplace(row,Signed{true,1});
  }
  for(const auto& [row,count]:after) {
    check(count!=0,"oracle retained zero");
    if(!before.contains(row))result.emplace(row,Signed{false,1});
  }
  return result;
}
std::uint64_t total(const Counts& rows) {
  std::uint64_t result=0;
  for(const auto& [row,count]:rows) {static_cast<void>(row);result=add(result,count);}
  return result;
}
struct Edit {std::size_t node;Row row;std::uint64_t after;};
w::Epoch transaction(Model& model,const std::vector<Edit>& edits) {
  const auto before=bag_oracle(model.runtime.structural_program(),model.inputs);
  auto staged=model.inputs;
  const auto capture_bytes=model.runtime.accounted_memory_statistics().by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::capture)].requested_bytes;
  auto pending=model.runtime.begin_epoch(model.runtime.sequence()+1,w::DeltaCapture::support);
  check(pending.support_delta_preview().has_value() && !pending.bag_delta_preview(),"capture meanings overlap");
  for(const auto& edit:edits) {
    auto& table=staged.at(edit.node);
    const auto old=table.contains(edit.row)?table.at(edit.row):0;
    static_cast<void>(pending.stage({NodeId{edit.node},edit.row,{old},{edit.after}}));
    if(edit.after)table[edit.row]=edit.after;else table.erase(edit.row);
    const auto after=bag_oracle(model.runtime.structural_program(),staged);
    check(read(*pending.support_delta_preview(),true)==support_difference(before,after),"prepared support differs from full join");
    check(pending.preview().before.value==total(before) && pending.preview().after.value==total(after),"numeric root endpoints changed meaning");
    check(!pending.preview().bag_deltas && !pending.preview().support_deltas,"owning delta published before commit");
    check(model.runtime.accounted_memory_statistics().by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::capture)].requested_bytes==capture_bytes,"support stage copied native diagnostic state");
    ++stages;
  }
  auto epoch=pending.commit();
  check(bool(epoch.support_deltas) && !epoch.bag_deltas,"support commit published wrong handle");
  const auto after=bag_oracle(model.runtime.structural_program(),staged);
  check(read(epoch.support_deltas.entries(),true)==support_difference(before,after),"committed support differs from full join");
  check(epoch.support_deltas.metrics().multiplications==0,"support capture multiplied numeric factors");
  for(const auto& row:epoch.support_deltas.entries())
    check(row.tuple.layout().account_statistics().owner==model.runtime.owner(),"support tuple changed account");
  model.inputs=std::move(staged);
  auto cursor=model.runtime.results();
  check(drain(cursor)==after,"numeric result cursor changed under support capture");
  ++transactions;return epoch;
}

void basic_and_private_stages(bool indexed) {
  Model one(unary(indexed));
  auto inserted=transaction(one,{{0,{n(7)},9}});
  check(read(inserted.support_deltas.entries(),true)==Deltas{{Row{n(7)},{false,1}}},"insert unit");
  const auto positive=transaction(one,{{0,{n(7)},2}});
  check(positive.support_deltas.entries().empty() && positive.support_deltas.metrics().rows_visited==0 &&
      positive.support_deltas.metrics().terms==0,"positive-to-positive capture walked rows");
  check(positive.before.value==9 && positive.after.value==2 && positive.metrics.native_changes>0,"capture skipped kernel arithmetic");
  const auto restored=transaction(one,{{0,{n(7)},0},{0,{n(7)},5}});
  check(restored.support_deltas.entries().empty(),"private loss/restore did not cancel");
  const auto canceled=transaction(one,{{0,{n(8)},3},{0,{n(8)},0}});
  check(canceled.support_deltas.entries().empty(),"private add/remove did not cancel");
  static_cast<void>(transaction(one,{{0,{n(7)},0}}));
  auto disabled=one.runtime.begin_epoch(one.runtime.sequence()+1);
  const auto allocation=one.runtime.accounted_memory_statistics().by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::delta_state)].requested_bytes;
  check(!disabled.bag_delta_preview() && !disabled.support_delta_preview(),"default capture enabled");
  static_cast<void>(disabled.stage({NodeId{0},{n(4)},{0},{1}}));
  check(one.runtime.accounted_memory_statistics().by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::delta_state)].requested_bytes==allocation,"uncaptured stage allocated delta state");
  const auto uncaptured=disabled.commit();
  check(!uncaptured.bag_deltas && !uncaptured.support_deltas,"uncaptured commit exposed output");
}

// Four mutable unary atoms under a genuine generalized node exercise arbitrary
// fan-out; the exhaustive full-join oracle remains independent of that node.
PhysicalPlan four_children(bool indexed) {
  Catalog catalog;Query query;query.variables={{"x",ScalarType::int64}};query.head={{VariableId{0},"x"}};
  FreeConnexTree tree;tree.root=NodeId{0};tree.nodes.push_back({"g",NodeKind::generalized,{VariableId{0}},{},{},{}});
  for(std::size_t i=0;i<4;++i) {
    const auto name="child"+std::to_string(i);catalog.tables.push_back({name,{{"x",ScalarType::int64}}});
    query.atoms.push_back({name,TableId{i},{VariableId{0}}});
    tree.nodes[0].children.push_back(NodeId{i+1});tree.nodes.push_back({name,NodeKind::native,{VariableId{0}},{},i,{}});
  }
  return planner::lower_tree(catalog,query,tree,options(indexed));
}
void hidden_nary_and_disconnected(bool indexed) {
  Model hidden(counted_path(indexed,true,true));
  static_cast<void>(transaction(hidden,{{0,{n(1),n(7),n(10)},2},{0,{n(1),n(7),n(11)},3},
      {1,{n(7),n(20)},5},{1,{n(7),n(21)},7},{2,{n(20)},2},{2,{n(21)},1}}));
  static_cast<void>(transaction(hidden,{{0,{n(1),n(7),n(10)},0}}));
  static_cast<void>(transaction(hidden,{{2,{n(20)},0},{2,{n(21)},0},{2,{n(21)},4}}));
  static_cast<void>(transaction(hidden,{{0,{n(1),n(7),n(11)},0}}));
  Model four(four_children(indexed));
  static_cast<void>(transaction(four,{{1,{n(7)},2},{2,{n(7)},3},{3,{n(7)},5},{4,{n(7)},7}}));
  static_cast<void>(transaction(four,{{1,{n(7)},0},{2,{n(7)},0},{1,{n(7)},2},{2,{n(7)},3}}));
  static_cast<void>(transaction(four,{{4,{n(7)},0}}));
  Model nary(fanout(indexed));
  static_cast<void>(transaction(nary,{{1,{n(7),n(10),n(30)},2},{1,{n(7),n(10),n(31)},3},
      {2,{n(10)},5},{3,{n(7)},7}}));
  static_cast<void>(transaction(nary,{{2,{n(10)},0},{3,{n(7)},0},{2,{n(10)},2},{3,{n(7)},3}}));
  Model parts(disconnected_bag(indexed));
  static_cast<void>(transaction(parts,{{1,{n(1)},2},{1,{n(2)},3},{2,{n(8)},5},{2,{n(9)},7}}));
  static_cast<void>(transaction(parts,{{1,{n(1)},0},{2,{n(8)},0},{1,{n(1)},1},{2,{n(8)},1}}));
  Model empty(unary(indexed,false,true));
  static_cast<void>(transaction(empty,{{0,{n(1)},2},{0,{n(2)},3}}));
  static_cast<void>(transaction(empty,{{0,{n(1)},0},{0,{n(2)},0}}));
}

void random_hidden(bool indexed) {
  Model model(counted_path(indexed));std::mt19937 random(6291);
  for(unsigned epoch=0;epoch<96;++epoch) {
    std::vector<Edit> edits;
    const auto count=1+random()%3;
    for(unsigned j=0;j<count;++j) {
      const std::size_t node=random()%2;
      Row row=node==0?Row{n(static_cast<std::int64_t>(random()%2)),n(7),n(static_cast<std::int64_t>(random()%3))}:Row{n(7),n(static_cast<std::int64_t>(random()%3))};
      edits.push_back({node,std::move(row),random()%4});
    }
    static_cast<void>(transaction(model,edits));
  }
}

void numeric_wide_and_lifetime(bool indexed) {
  Model model(unary(indexed));const auto wide=(std::uint64_t{1}<<63)+1;
  auto numeric=model.runtime.begin_epoch(1,w::DeltaCapture::enabled);
  check(!numeric.support_delta_preview() && numeric.bag_delta_preview().has_value(),"old numeric preview changed");
  static_cast<void>(numeric.stage({NodeId{0},{n(1)},{0},{wide}}));
  const auto inserted=numeric.commit();
  check(!inserted.support_deltas && read(inserted.bag_deltas.entries(),false)==Deltas{{Row{n(1)},{false,wide}}},"wide numeric insertion narrowed");
  auto retract=model.runtime.begin_epoch(2,w::DeltaCapture::enabled);
  static_cast<void>(retract.stage({NodeId{0},{n(1)},{wide},{0}}));
  check(read(*retract.bag_delta_preview(),false)==Deltas{{Row{n(1)},{true,wide}}},"wide numeric retraction narrowed");
  const auto removed=retract.commit();check(!removed.support_deltas,"numeric commit gained support handle");
  w::SupportDeltas retained;resource::MemoryAccount account;
  {
    Model strings(typed_bag(indexed));typed_inputs(strings);
    account=strings.runtime.structural_program().account();
    const auto name=std::string(256,'x')+"0";
    auto epoch=transaction(strings,{{0,{Value{name},n(7),Value{Date::parse("2026-11-11")}},0}});
    retained=epoch.support_deltas;
  }
  check(retained.entries().size()==2,"support payload lost after runtime destruction");
  for(const auto& row:retained.entries())check(row.change.negative && std::get<std::string_view>(row.tuple.values()[1]).size()==257,"support string payload lifetime");
  retained={};
  check(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),"support handle leaked query memory");
}

std::uint64_t work_scenario(bool indexed,std::optional<std::uint64_t> cap,bool fail) {
  w::Options options;options.work_limit=cap;
  Model model(counted_path(indexed),options);
  auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::support);
  bool failed=false;std::uint64_t work=0;
  try {
    static_cast<void>(pending.stage({NodeId{0},{n(1),n(7),n(10)},{0},{2}}));
    static_cast<void>(pending.stage({NodeId{1},{n(7),n(20)},{0},{3}}));
    work=pending.preview().metrics.work;
  } catch(const Error& error) {check(error.code()=="resource_limit","unexpected budget failure");failed=true;}
  check(failed==fail,"support work exact/one-under boundary");
  if(failed) {
    check(!pending.active() && model.runtime.ready() && model.runtime.sequence()==0 && model.runtime.root_weight().value==0,"budget failure published source/native state");
  } else static_cast<void>(pending.commit());
  return work;
}
void budgets_rollback_and_publication(bool indexed) {
  const auto used=work_scenario(indexed,{},false);
  check(work_scenario(indexed,used,false)==used,"exact support work changed");
  static_cast<void>(work_scenario(indexed,used-1,true));
  Model model(unary(indexed));
  {
    auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::support);
    static_cast<void>(pending.stage({NodeId{0},{n(5)},{0},{3}}));
  }
  check(model.runtime.ready() && model.runtime.sequence()==0 && model.runtime.root_weight().value==0,"RAII support rollback failed");
  auto pending=model.runtime.begin_epoch(1,w::DeltaCapture::support);
  static_cast<void>(pending.stage({NodeId{0},{n(5)},{0},{3}}));
  w::Epoch epoch;
  bool allocated=false;
  {s04_alloc::Scope denied(0);epoch=pending.commit();allocated=s04_alloc::triggered;}
  check(!allocated,"support publication allocated");
  check(epoch.support_deltas.entries().size()==1,"funded support commit lost changes");
}

// Repeated private support crossings spend one original indexed allowance.
// Exact and one-under trials compare the same final quiescent source state.
std::uint64_t indexed_grant(std::optional<std::uint64_t> cap,bool expect_failure) {
  const auto base=counted_path(true);auto physical=options(true);
  if(cap)physical.indexed_storage->per_operation.structural_steps=*cap;
  Model model(planner::lower_tree(base.catalog(),base.query(),base.tree(),physical));
  model.set(0,{n(1),n(7),n(10)},2);model.set(1,{n(7),n(20)},3);
  auto pending=model.runtime.begin_epoch(3,w::DeltaCapture::support);
  std::uint64_t previous=0;bool failed=false;
  try {
    for(unsigned stage=0;stage<64;++stage) {
      const std::uint64_t old=stage%2?0:3,next=stage%2?3:0;
      static_cast<void>(pending.stage({NodeId{1},{n(7),n(20)},{old},{next}}));
      const auto used=pending.preview().metrics.native_grant_consumed.structural_steps;
      check(used>previous,"support stages refilled the indexed grant");previous=used;
    }
  } catch(const storage::IndexFailure& error) {check(error.code()=="storage_work_limit","unexpected indexed grant failure");failed=true;}
  check(failed==expect_failure,"indexed support grant exact/one-under boundary");
  if(failed)check(!pending.active() && model.runtime.ready() && model.runtime.sequence()==2,"indexed failure published private state");
  else {const auto epoch=pending.commit();check(epoch.support_deltas.entries().empty(),"indexed cancellation retained support change");}
  auto cursor=model.runtime.results();check(drain(cursor)==bag_oracle(model.runtime.structural_program(),model.inputs),"indexed grant trial changed source results");
  return previous;
}
using SqlRow=runtime::aggregate::Row;
using SqlBag=std::map<SqlRow,std::uint64_t>;
using SqlDelta=std::map<SqlRow,Signed>;
using Cells=std::vector<runtime::sql_rows::Cell>;
SqlBag sql_results(const runtime::SqlRowsRuntime& owner) {
  SqlBag result;auto cursor=owner.results();
  while(auto row=cursor.next())check(result.emplace(row->tuple.export_values(),row->multiplicity).second,"SQL duplicate output");
  return result;
}
SqlBag sql_oracle(const std::map<SqlRow,std::uint64_t>& source,bool selfjoin) {
  SqlBag result;
  for(const auto& [a,wa]:source) {
    bool present=!selfjoin;
    if(selfjoin)for(const auto& [b,wb]:source) {
      if(wa && wb && a[0]==b[0] && std::get<std::int64_t>(*b[0])>=0)present=true;
    }
    if(present)result[{a[1],a[2],Value{std::int64_t{17}},a[1]}]=1;
  }
  return result;
}
SqlDelta sql_difference(const SqlBag& before,const SqlBag& after) {
  SqlDelta result;
  for(const auto& [row,count]:before) {static_cast<void>(count);if(!after.contains(row))result.emplace(row,Signed{true,1});}
  for(const auto& [row,count]:after) {static_cast<void>(count);if(!before.contains(row))result.emplace(row,Signed{false,1});}
  return result;
}
SqlDelta sql_decode(const frontend::SqlRowsProgram& program,const w::SupportDeltas& deltas) {
  SqlDelta result;
  for(const auto& delta:deltas.entries()) {
    SqlRow row;
    for(const auto& column:program.outputs()) {
      runtime::sql_rows::Cell cell;
      if(const auto* field=std::get_if<frontend::SqlRowsResultField>(&column.value)) {
        if(!field->presence || std::get<bool>(delta.tuple.values()[*field->presence]))cell=delta.tuple.values()[field->payload];
      } else cell=program.initial_values()[std::get<frontend::ExpressionId>(column.value).value];
      if(cell)row.emplace_back(std::in_place,storage::export_scalar(*cell));else row.emplace_back();
    }
    check(delta.change.magnitude.value==1,"SQL DISTINCT support was nonunit");
    check(result.emplace(std::move(row),Signed{delta.change.negative,1}).second,"injective SQL mapping collided");
  }
  return result;
}
void sql_distinct_mapping(bool indexed,bool selfjoin) {
  const Catalog catalog{1,{{"r",{{"id",ScalarType::int64,false},{"x",ScalarType::int64,true},{"t",ScalarType::string,true}}}}};
  const std::string query=selfjoin?
      "SELECT DISTINCT a.x,a.t,17,a.x FROM r a JOIN r b ON a.id=b.id WHERE b.id>=0":
      "SELECT DISTINCT x,t,17,x FROM r";
  auto bound=frontend::bind_sql_rows(query,catalog);
  check(std::holds_alternative<frontend::SqlRowsProgram>(bound),"support SQL did not bind");
  const auto program=std::get<frontend::SqlRowsProgram>(std::move(bound));
  const auto core=program.export_core();const auto tree=planner::minimum_tree(core.catalog,core.query);
  check(tree.status==planner::OracleStatus::proven_minimum && tree.tree.has_value(),"support SQL lacks genuine minimum tree");
  runtime::SqlRowsRuntime owner(program,*tree.tree,options(indexed));
  const auto integer=[](std::int64_t n){return runtime::sql_rows::Cell{storage::ScalarView{n}};};
  const auto text=[](std::string_view s){return runtime::sql_rows::Cell{storage::ScalarView{s}};};
  const std::string long_text(256,'q');
  const std::array<Cells,4> rows{Cells{integer(1),{},text(long_text)},Cells{integer(1),integer(0),{}},
      Cells{integer(2),{},text(long_text)},Cells{integer(-1),integer(9),text("filtered")}};
  std::map<SqlRow,std::uint64_t> source;
  const auto run=[&](const std::vector<std::pair<std::size_t,std::uint64_t>>& changes) {
    const auto before=sql_oracle(source,selfjoin);auto staged=source;
    std::vector<runtime::sql_rows::SourceReplacement> replacements;
    for(const auto& [id,next]:changes) {
      SqlRow full;
      for(const auto& cell:rows[id]) {
        if(cell)full.emplace_back(std::in_place,storage::export_scalar(*cell));else full.emplace_back();
      }
      const auto old=staged.contains(full)?staged.at(full):0;
      replacements.push_back({TableId{0},rows[id],old,next});
      if(next)staged[full]=next;else staged.erase(full);
    }
    auto batch=owner.prepare_batch({owner.sequence()+1,replacements},w::DeltaCapture::support);
    check(!batch.native_bag_delta_preview(),"support capture impersonated SQL native bag changes");
    auto epoch=batch.commit();const auto after=sql_oracle(staged,selfjoin);
    check(epoch.native.support_deltas && !epoch.native.bag_deltas,"SQL support handle meaning");
    check(sql_decode(program,epoch.native.support_deltas)==sql_difference(before,after),"SQL DISTINCT presentation differs from independent physical oracle");
    check(sql_results(owner)==after,"SQL DISTINCT cursor differs from independent physical oracle");
    source=std::move(staged);++transactions;
  };
  run({{0,2},{1,3},{2,5},{3,7}});run({{0,9}});run({{0,0}});run({{2,0}});
  run({{1,0},{1,4}});run({{1,0},{3,0}});run({});
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      basic_and_private_stages(indexed);hidden_nary_and_disconnected(indexed);random_hidden(indexed);
      numeric_wide_and_lifetime(indexed);budgets_rollback_and_publication(indexed);
      sql_distinct_mapping(indexed,false);sql_distinct_mapping(indexed,true);
    }
    const auto grant=indexed_grant({},false);
    check(indexed_grant(grant,false)==grant,"exact indexed support grant changed work");
    static_cast<void>(indexed_grant(grant-1,true));
    std::cout<<"weighted support capture PASS transactions="<<transactions<<" native_stages="<<stages
        <<" backends=reference,indexed sql=nullable,constant,repeated,selfjoin numeric_wide=9223372036854775809\n";
  } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
