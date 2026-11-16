#include "crown/runtime/sql_aggregate.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <string>

namespace {
using namespace crown;
using namespace crown::runtime;
using Cells=std::vector<sql_rows::Cell>;
using Results=std::map<aggregate::Row,aggregate::Row>;
constexpr std::uint64_t bytes=64ULL*1024*1024;
sql_rows::Cell n(std::int64_t value) {return storage::ScalarView{value};}
sql_rows::Cell text(std::string_view value) {return storage::ScalarView{value};}
Catalog catalog() {
  return {1,{{"r",{{"id",ScalarType::int64,true},{"g",ScalarType::string,true},
      {"x",ScalarType::int64,true},{"flag",ScalarType::boolean}}},
      {"s",{{"id",ScalarType::int64,true},{"y",ScalarType::int64,true}}},
      {"unused",{{"z",ScalarType::int64}}}}};
}
frontend::SqlAggregateProgram bind(std::string_view sql,const Catalog& schema=catalog(),
    const frontend::SqlAggregateBindOptions& options={}) {
  auto result=frontend::bind_sql_aggregate(sql,schema,options);
  if(const auto* error=std::get_if<frontend::BindingDiagnostic>(&result))
    throw Error(error->diagnostic.code,error->diagnostic.message);
  return std::get<frontend::SqlAggregateProgram>(std::move(result));
}
FreeConnexTree tree(const frontend::SqlAggregateProgram& program) {
  if(program.source_program().contradiction())return {};
  const auto core=program.source_program().export_core();
  const auto chosen=planner::minimum_tree(core.catalog,core.query);
  assert(chosen.status==planner::OracleStatus::proven_minimum && chosen.tree);return *chosen.tree;
}
SqlAggregateRuntime create(const frontend::SqlAggregateProgram& program,bool indexed,
    sql_aggregate::Options options={}) {
  return SqlAggregateRuntime(program,tree(program),indexed?s04_runtime::options():PhysicalOptions{},options);
}
sql_aggregate::RebuildLimits limits(bool indexed) {
  sql_aggregate::RebuildLimits result;
  result.source.source_work={10000000,10000000,64ULL*1024*1024,10000000,10000000};
  result.source.native_work=10000000;result.group_work=10000000;
  if(indexed)result.source.indexed_work=storage::IndexWork{1000000000,1000000000,1000000000,1000000000,1000000000};
  return result;
}
Results groups(const SqlAggregateRuntime& runtime) {
  Results result;
  for(const auto& group:runtime.snapshot().groups)
    assert(result.emplace(group.key.export_values(),group.values.export_values()).second);
  return result;
}
template<std::size_t N> sql_aggregate::Epoch apply(SqlAggregateRuntime& runtime,
    const std::array<sql_rows::SourceReplacement,N>& edits) {
  return runtime.prepare_batch({runtime.sequence()+1,edits}).commit();
}
template<class Action> void rejected(Action action,std::string_view code) {
  try {action();} catch(const Error& error) {
    if (error.code()!=code) std::cerr << "expected " << code << ", received " << error.code() << ": " << error.what() << '\n';
    assert(error.code()==code);return;
  }
  assert(false && "expected cold rebuild rejection");
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();assert(account.statistics().current.allocations==1);
  assert(account.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes());
}

// Actual original SQL/planner/source image, including full hidden separator
// keys, equal projected groups, nullable keys, filters and an unused table.
void joined_round_trip(bool indexed) {
  const auto program=bind("SELECT a.g,COUNT(*),COUNT(b.y),SUM(b.y),AVG(b.y),SUM(1) "
      "FROM r a JOIN s b ON a.id=b.id WHERE a.flag GROUP BY a.id,a.g");
  sql_aggregate::Options options;options.capture_changes=true;
  auto live=create(program,indexed,options);
  const std::string owned(200,'q');
  const Cells a{n(1),text(owned),n(9),storage::ScalarView{true}};
  const Cells b{n(2),text(owned),{},storage::ScalarView{true}};
  const Cells c{n(3),{},n(7),storage::ScalarView{true}};
  const Cells filtered{n(1),text("filtered"),n(5),storage::ScalarView{false}};
  const Cells null_id{{},text("null id"),n(1),storage::ScalarView{true}};
  const Cells x{n(1),n(5)},y{n(2),n(5)},z{n(3),{}},unused{n(8)};
  const std::array seed{sql_rows::SourceReplacement{TableId{0},a,0,2},
      sql_rows::SourceReplacement{TableId{0},b,0,2},sql_rows::SourceReplacement{TableId{0},c,0,1},sql_rows::SourceReplacement{TableId{0},filtered,0,7},
      sql_rows::SourceReplacement{TableId{0},null_id,0,3},sql_rows::SourceReplacement{TableId{1},x,0,3},sql_rows::SourceReplacement{TableId{1},y,0,3},sql_rows::SourceReplacement{TableId{1},z,0,4},
      sql_rows::SourceReplacement{TableId{2},unused,0,5}};
  static_cast<void>(apply(live,seed));
  const std::array<sql_rows::SourceReplacement,0> empty{};static_cast<void>(apply(live,empty));
  const auto before=groups(live);assert(before.size()==3);
  auto image=live.source_snapshot();assert(image.source.rows.size()==9 && image.source.sequence==2);
  auto receiver=resource::MemoryAccount::create(bytes);sql_aggregate::RebuildMetrics work;
  {
    auto source=SqlRowsRuntime::rebuild_into(receiver,image.source,options.source,limits(indexed).source);
    assert(source.sequence()==2 && source.root_weight()==live.root_weight());
    assert(source.source_weight(TableId{2},unused)==5);
  }
  controller_only(receiver);
  {
    auto rebuilt=SqlAggregateRuntime::rebuild_into(receiver,image,options,limits(indexed),&work);
    assert(rebuilt.ready() && rebuilt.sequence()==2 && groups(rebuilt)==before);
    assert(rebuilt.root_weight()==live.root_weight());assert(rebuilt.source_weight(TableId{2},unused)==5);
    const auto again=rebuilt.source_snapshot();
    assert(again.source.sequence==2 && again.source.native_binding==image.source.native_binding);
    assert(again.source.native_program.physical_sha256()==image.source.native_program.physical_sha256());
    const std::array change{sql_rows::SourceReplacement{TableId{0},a,2,0}};
    const auto expected=apply(live,change),actual=apply(rebuilt,change);
    assert(actual.sequence==3 && actual.native.sequence==3 && !actual.native.bag_deltas);
    assert(actual.output.size()==expected.output.size() && groups(rebuilt)==groups(live));
    for(std::size_t i=0;i<actual.output.size();++i) {
      assert(actual.output[i].key==expected.output[i].key);
      assert(actual.output[i].before==expected.output[i].before && actual.output[i].after==expected.output[i].after);
    }
  }
  controller_only(receiver);
  assert(work.groups.work && work.source.native_work && work.source.source_work.structural_steps);
  assert(bool(work.source.indexed_work.structural_steps)==indexed);
}

// Qualified/unqualified origin identity, genuine self joins, and full source
// aliases are admitted by their real factories, then rebuilt without row mirrors.
void alias_round_trip(bool indexed) {
  for(const auto sql:{"SELECT a.g,COUNT(*),COUNT(a.x),SUM(a.x),AVG(a.x) FROM r a "
      "JOIN r b ON a.id=b.id GROUP BY a.g", "SELECT r.g,COUNT(*) FROM r GROUP BY g"}) {
    const auto program=bind(sql);auto original=create(program,indexed);
    const Cells a{n(7),text("same"),n(-3),storage::ScalarView{true}};
    const Cells b{n(7),{},n(5),storage::ScalarView{true}};
    const std::array seed{sql_rows::SourceReplacement{TableId{0},a,0,2},sql_rows::SourceReplacement{TableId{0},b,0,3}};
    static_cast<void>(apply(original,seed));auto image=original.source_snapshot();
    auto receiver=resource::MemoryAccount::create(bytes);
    {
      auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));
      assert(groups(restored)==groups(original) && restored.root_weight()==original.root_weight());
    }
    controller_only(receiver);
  }
}

void empty_static_and_terminal(bool indexed) {
  for(const auto sql:{"SELECT COUNT(*),SUM(1),AVG(1) FROM r", "SELECT COUNT(*) FROM r GROUP BY g",
      "SELECT COUNT(*),SUM(1),AVG(1)", "SELECT COUNT(*) WHERE FALSE"}) {
    const auto program=bind(sql);auto original=create(program,indexed);
    auto image=original.source_snapshot();assert(image.source.sequence==0 && image.source.rows.empty());
    auto receiver=resource::MemoryAccount::create(bytes);
    {
      auto initial=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));
      assert(initial.sequence()==0 && groups(initial)==groups(original));
      const std::array<sql_rows::SourceReplacement,0> empty{};
      static_cast<void>(apply(original,empty));image=original.source_snapshot();
      auto after=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));
      assert(after.sequence()==1 && groups(after)==groups(original));
      image.source.sequence=UINT64_MAX; // Decoded checkpoint C, never a live setter.
      auto terminal=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));
      assert(terminal.sequence()==UINT64_MAX && groups(terminal)==groups(original));
      rejected([&]{static_cast<void>(terminal.prepare_batch({0,empty}));},"invalid_sequence");
    }
    controller_only(receiver);
  }
}

void invalid_images_and_domains(bool indexed) {
  const auto program=bind("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g");
  auto original=create(program,indexed);const Cells row{n(1),text("g"),n(3),storage::ScalarView{true}};
  const std::array seed{sql_rows::SourceReplacement{TableId{0},row,0,2}};static_cast<void>(apply(original,seed));
  const auto valid=original.source_snapshot();auto receiver=resource::MemoryAccount::create(bytes);
  auto attempt=[&](const sql_aggregate::SourceSnapshot& image,sql_aggregate::Options options={}) {
    static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,options,limits(indexed)));
  };
  {auto image=valid;image.source.rows[0].weight=0;rejected([&]{attempt(image);},"invalid_sql_rows_snapshot");}
  {auto image=valid;image.source.rows.push_back(image.source.rows[0]);
    rejected([&]{attempt(image);},"sql_rows_weight_mismatch");}
  {auto image=valid;image.source.sequence=0;rejected([&]{attempt(image);},"invalid_sql_rows_snapshot");}
  {auto image=valid;image.source.rows[0].source=TableId{99};
    rejected([&]{attempt(image);},"invalid_sql_rows_source");}
  {auto image=valid;const Cells wrong{n(1)};
    image.source.rows[0].row=aggregate::Tuple::copy_of(receiver,wrong);
    rejected([&]{attempt(image);},"invalid_sql_rows_row");}
  {auto image=valid;const Cells wrong{n(1),n(8),n(3),storage::ScalarView{true}};
    image.source.rows[0].row=aggregate::Tuple::copy_of(receiver,wrong);
    rejected([&]{attempt(image);},"invalid_sql_rows_row");}
  {auto image=valid;auto other=create(bind("SELECT COUNT(*) FROM r WHERE x=9"),indexed);
    image.source.native_program=other.source_snapshot().source.native_program;
    // The genuine lowerer rejects this foreign tree before snapshot hash checks.
    rejected([&]{attempt(image);},"invalid_plan");}
  {auto image=valid;image.program=bind("SELECT COUNT(*) FROM s");
    rejected([&]{attempt(image);},"invalid_sql_aggregate_snapshot");}
  {auto image=valid;image.source.native_binding.weighted_sha256[0]^=1;
    rejected([&]{attempt(image);},"sql_rows_snapshot_binding");}
  {sql_aggregate::Options options;options.count_limit=1;
    rejected([&]{attempt(valid,options);},"aggregate_overflow");}
  {sql_aggregate::Options options;options.source.native.multiplicity_limit=1;
    rejected([&]{attempt(valid,options);},"sql_rows_snapshot_binding");}
  assert(original.sequence()==1 && original.source_weight(TableId{0},row)==2);controller_only(receiver);
}

void final_source_constraints(bool indexed) {
  Catalog schema{1,{{"p",{{"id",ScalarType::int64,false}}},
      {"c",{{"pid",ScalarType::int64,true},{"tag",ScalarType::string,false}}}}};
  schema.tables[0].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
  schema.tables[1].constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{0}},TableId{0},
      {ColumnId{0}},ConstraintStatus::enforced});
  auto original=create(bind("SELECT tag,COUNT(*) FROM c JOIN p ON c.pid=p.id GROUP BY tag",schema),indexed);
  const Cells parent{n(1)},child{n(1),text("child")},null_fk{{},text("null FK")};
  const std::array seed{sql_rows::SourceReplacement{TableId{1},child,0,2},
      sql_rows::SourceReplacement{TableId{0},parent,0,1},sql_rows::SourceReplacement{TableId{1},null_fk,0,3}};
  static_cast<void>(apply(original,seed));auto image=original.source_snapshot();
  std::reverse(image.source.rows.begin(),image.source.rows.end());
  auto receiver=resource::MemoryAccount::create(bytes);
  {auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));assert(groups(restored)==groups(original));}
  {auto wrong=image;wrong.source.rows.erase(std::find_if(wrong.source.rows.begin(),wrong.source.rows.end(),
      [](const auto& entry){return entry.source==TableId{0};}));
    rejected([&]{static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,wrong,{},limits(indexed)));},"foreign_key_violation");}
  {auto wrong=image;for(auto& entry:wrong.source.rows)if(entry.source==TableId{0})entry.weight=2;
    rejected([&]{static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,wrong,{},limits(indexed)));},"unique_violation");}
  controller_only(receiver);
}

void restores_operational_work(bool indexed) {
  auto original=create(bind("SELECT COUNT(*) FROM r"),indexed);const auto image=original.source_snapshot();
  auto receiver=resource::MemoryAccount::create(bytes);
  for(unsigned kind=0;kind<3;++kind) {
    sql_aggregate::Options options;
    if(kind==0)options.group_work_limit=0;
    if(kind==1)options.source.source_work_limit={};
    if(kind==2)options.source.native.work_limit=0;
    auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,options,limits(indexed));
    const std::array<sql_rows::SourceReplacement,0> empty{};
    if(kind==0)rejected([&]{static_cast<void>(restored.prepare_batch({1,empty}));},"aggregate_work_limit");
    else if(kind==1) {
      const Cells row{n(1),text("g"),n(3),storage::ScalarView{true}};
      const std::array edit{sql_rows::SourceReplacement{TableId{0},row,0,1}};
      try {static_cast<void>(restored.prepare_batch({1,edit}));assert(false);}
      catch(const storage::IndexFailure& error) {assert(error.code()=="storage_work_limit");}
    } else rejected([&]{static_cast<void>(restored.prepare_batch({1,empty}));},"resource_limit");
    assert(restored.ready() && restored.sequence()==0);
  }
  controller_only(receiver);
}

void exact_numeric_metadata(bool indexed) {
  for(std::uint8_t scale=0;scale<=18;++scale) {
    frontend::SqlAggregateBindOptions binding;binding.kernel.average_scale=scale;
    auto original=create(bind("SELECT COUNT(x),SUM(x),AVG(x) FROM r",catalog(),binding),indexed);
    const Cells a{n(1),text("g"),n(-2),storage::ScalarView{true}},
        b{n(2),text("g"),n(3),storage::ScalarView{true}},c{n(3),text("g"),{},storage::ScalarView{true}};
    const std::array seed{sql_rows::SourceReplacement{TableId{0},a,0,1},
        sql_rows::SourceReplacement{TableId{0},b,0,2},sql_rows::SourceReplacement{TableId{0},c,0,7}};
    static_cast<void>(apply(original,seed));const auto image=original.source_snapshot();
    auto receiver=resource::MemoryAccount::create(bytes);
    {auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));
      assert(restored.program().kernel_program().average_scale()==scale && groups(restored)==groups(original));}
    controller_only(receiver);
  }
  const Cells minimum{n(1),text("wide"),n(INT64_MIN),storage::ScalarView{true}};
  auto wide=create(bind("SELECT COUNT(*),SUM(x),AVG(x) FROM r"),indexed);
  const std::array seed{sql_rows::SourceReplacement{TableId{0},minimum,0,INT64_MAX}};
  static_cast<void>(apply(wide,seed));auto image=wide.source_snapshot();
  auto receiver=resource::MemoryAccount::create(bytes);
  {auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));assert(groups(restored)==groups(wide));}
  image.source.rows[0].weight=(std::uint64_t{1}<<63)+17;
  rejected([&]{static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed)));},"aggregate_overflow");
  auto literal=create(bind("SELECT SUM(2147483647) FROM r"),indexed);
  constexpr std::uint64_t boundary=4294967298ULL;
  const std::array literal_seed{sql_rows::SourceReplacement{TableId{0},minimum,0,boundary}};
  static_cast<void>(apply(literal,literal_seed));image=literal.source_snapshot();
  {auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));assert(groups(restored)==groups(literal));}
  image.source.rows[0].weight=boundary+1;
  rejected([&]{static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed)));},"aggregate_overflow");
  controller_only(receiver);
}

// Exact/one-under grant checks repeat the same whole image. A failed factory
// exposes no runtime, leaves the image intact and writes no success report.
void cold_work_and_account_limits(bool indexed) {
  auto original=create(bind("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g"),indexed);
  // Four distinct rows span repeated, distinct and NULL groups under one grant.
  const Cells row{n(1),text("work"),n(-5),storage::ScalarView{true}};
  const Cells second{n(2),text("other"),n(7),storage::ScalarView{true}};
  const Cells third{n(3),text("work"),{},storage::ScalarView{true}};
  const Cells fourth{n(4),{},n(-11),storage::ScalarView{false}};
  const std::array seed{sql_rows::SourceReplacement{TableId{0},row,0,4},
      sql_rows::SourceReplacement{TableId{0},second,0,3},
      sql_rows::SourceReplacement{TableId{0},third,0,2},
      sql_rows::SourceReplacement{TableId{0},fourth,0,1}};
  static_cast<void>(apply(original,seed));
  const auto image=original.source_snapshot();auto receiver=resource::MemoryAccount::create(bytes);
  sql_aggregate::RebuildMetrics used;
  {auto run=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed),&used);assert(run.sequence()==1);}
  controller_only(receiver);assert(used.groups.work && used.source.native_work);
  auto exact=limits(indexed);exact.source.source_work=used.source.source_work;
  exact.source.native_work=used.source.native_work;exact.group_work=used.groups.work;
  if(indexed)exact.source.indexed_work=used.source.indexed_work;
  {auto run=SqlAggregateRuntime::rebuild_into(receiver,image,{},exact);assert(groups(run)==groups(original));}
  controller_only(receiver);
  auto source_short=exact;--source_short.source.source_work.structural_steps;
  try {static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,{},source_short));assert(false);}
  catch(const storage::IndexFailure& error) {assert(error.code()=="storage_work_limit");}
  auto native_short=exact;--native_short.source.native_work;
  rejected([&]{static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,{},native_short));},"resource_limit");
  auto group_short=exact;--group_short.group_work;
  rejected([&]{static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,{},group_short));},"aggregate_work_limit");
  if(indexed) {
    auto index_short=exact;--index_short.source.indexed_work->structural_steps;
    try {static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,{},index_short));assert(false);}
    catch(const storage::IndexFailure& error) {assert(error.code()=="storage_work_limit");}
  }
  controller_only(receiver);
  auto tiny=resource::MemoryAccount::create(resource::MemoryAccount::control_bytes());
  try {static_cast<void>(SqlAggregateRuntime::rebuild_into(tiny,image,{},limits(indexed)));assert(false);}
  catch(const resource::MemoryFailure& error) {assert(error.fault()==resource::MemoryFault::limit);}
  controller_only(tiny);
}

// A genuine image built through 128 small public epochs can exceed the bound
// operation grant at cold reconstruction. The new owner must subsequently use
// the original cap; it cannot keep the large cold lease or change plan identity.
void separate_indexed_build_grant() {
  const auto program=bind("SELECT COUNT(*) FROM r");
  auto probe=create(program,true);auto zero=probe.source_snapshot();
  auto receiver=resource::MemoryAccount::create(bytes);sql_aggregate::RebuildMetrics startup;
  {auto cold=SqlAggregateRuntime::rebuild_into(receiver,zero,{},limits(true),&startup);assert(cold.sequence()==0);}
  auto ceiling=startup.source.indexed_work;
  const auto widen=[](std::uint64_t value){assert(value<=(UINT64_MAX-256)/2);return value*2+256;};
  ceiling={widen(ceiling.structural_steps),widen(ceiling.scalar_fields),widen(ceiling.scalar_bytes),
      widen(ceiling.pointer_slots),widen(ceiling.link_actions)};
  auto physical=s04_runtime::options();physical.indexed_storage->per_operation=ceiling;
  auto original=SqlAggregateRuntime(program,tree(program),physical);
  for(std::int64_t i=0;i<128;++i) {
    const Cells row{n(i),text("g"),n(i),storage::ScalarView{true}};
    const std::array edit{sql_rows::SourceReplacement{TableId{0},row,0,1}};static_cast<void>(apply(original,edit));
  }
  const auto image=original.source_snapshot();sql_aggregate::RebuildMetrics built;
  {
    auto restored=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(true),&built);
    const auto spent=built.source.indexed_work;
    assert(spent.structural_steps>ceiling.structural_steps || spent.scalar_fields>ceiling.scalar_fields ||
        spent.scalar_bytes>ceiling.scalar_bytes || spent.pointer_slots>ceiling.pointer_slots || spent.link_actions>ceiling.link_actions);
    const auto again=restored.source_snapshot();
    assert(again.source.native_program.options().indexed_storage->per_operation==ceiling);
    assert(again.source.native_binding==image.source.native_binding && restored.sequence()==128);
    const Cells next{n(200),text("g"),n(200),storage::ScalarView{true}};
    const std::array edit{sql_rows::SourceReplacement{TableId{0},next,0,1}};
    const auto epoch=apply(restored,edit);assert(epoch.sequence==129);
    const auto used=epoch.native.metrics.native_grant_consumed;
    assert(used.structural_steps<=ceiling.structural_steps && used.scalar_fields<=ceiling.scalar_fields &&
        used.scalar_bytes<=ceiling.scalar_bytes && used.pointer_slots<=ceiling.pointer_slots && used.link_actions<=ceiling.link_actions);
  }
  controller_only(receiver);
}

// Covered C++ allocation failures include metadata imports, complete source
// preparation, final group state and fresh normal context creation. This is
// separate from libc/parser allocation behavior and from receiver byte limits.
void allocation_failure_and_lifetime(bool indexed) {
  auto original=create(bind("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g"),indexed);
  const std::string long_name(256,'n');const Cells row{n(1),text(long_name),n(5),storage::ScalarView{true}};
  const std::array seed{sql_rows::SourceReplacement{TableId{0},row,0,2}};static_cast<void>(apply(original,seed));
  const auto image=original.source_snapshot();auto receiver=resource::MemoryAccount::create(bytes);
  std::size_t allocations;
  {s04_alloc::Scope count;auto run=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));allocations=s04_alloc::calls;}
  assert(allocations && allocations<8192);controller_only(receiver);
  for(std::size_t cut=0;cut<allocations;++cut) {
    bool failed=false;sql_aggregate::RebuildMetrics report;report.source.native_work=887;
    {
      s04_alloc::Scope fail_after(static_cast<std::ptrdiff_t>(cut));
      try {static_cast<void>(SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed),&report));}
      catch(const std::bad_alloc&) {failed=true;}
      assert(failed && s04_alloc::triggered);
    }
    assert(report.source.native_work==887);controller_only(receiver);
  }
  std::optional<sql_aggregate::Snapshot> held;
  {
    auto run=SqlAggregateRuntime::rebuild_into(receiver,image,{},limits(indexed));held=run.snapshot();
    auto moved=std::move(run);assert(moved.ready() && moved.sequence()==1);
  }
  assert(!held->groups.empty() && std::get<std::string_view>(*held->groups[0].key.view()[0])==long_name);
  held.reset();controller_only(receiver);
}
}  // namespace

int main() {
  for(const bool indexed:{false,true}) {
    joined_round_trip(indexed);alias_round_trip(indexed);empty_static_and_terminal(indexed);
    invalid_images_and_domains(indexed);final_source_constraints(indexed);restores_operational_work(indexed);
    exact_numeric_metadata(indexed);cold_work_and_account_limits(indexed);allocation_failure_and_lifetime(indexed);
  }
  separate_indexed_build_grant();
  std::cout<<"sql aggregate closed cold rebuild controls passed\n";
}
