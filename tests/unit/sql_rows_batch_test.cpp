#include "crown/api/error.hpp"
#include "crown/runtime/sql_rows.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using Cell = sql_rows::Cell;
using Cells = std::vector<Cell>;
using SqlRow = aggregate::Row;
using Bag = std::map<SqlRow,std::uint64_t>;
using CoreRow = std::vector<Value>;
using Signed = std::pair<bool,std::uint64_t>; // negative, magnitude
using CoreDelta = std::map<CoreRow,Signed>;

Cell n(std::int64_t value) { return storage::ScalarView{value}; }
Cell s(std::string_view value) { return storage::ScalarView{value}; }
Value v(std::int64_t value) { return value; }

frontend::SqlRowsProgram compile_rows(std::string_view sql, const Catalog& catalog) {
  auto result=frontend::bind_sql_rows(sql,catalog);
  if (const auto* failure=std::get_if<frontend::BindingDiagnostic>(&result))
    throw Error(failure->diagnostic.code,failure->diagnostic.message);
  return std::get<frontend::SqlRowsProgram>(std::move(result));
}

FreeConnexTree tree_for(const frontend::SqlRowsProgram& program) {
  if (program.contradiction()) return {};
  const auto core=program.export_core();
  const auto result=planner::minimum_tree(core.catalog,core.query);
  assert(result.status==planner::OracleStatus::proven_minimum && result.tree);
  return *result.tree;
}

SqlRowsRuntime create(const frontend::SqlRowsProgram& program, bool indexed,
    sql_rows::Options options={}) {
  return SqlRowsRuntime(program,tree_for(program),
      indexed?s04_runtime::options():PhysicalOptions{},options);
}

Bag drain(SqlRowsRuntime::ResultCursor& cursor) {
  Bag result;
  while (const auto row=cursor.next()) {
    const auto [position,inserted]=result.emplace(row->tuple.export_values(),row->multiplicity);
    static_cast<void>(position);assert(inserted);
  }
  return result;
}

Bag results(const SqlRowsRuntime& runtime) {
  auto cursor=runtime.results();return drain(cursor);
}

template<class Action> void error(Action action, std::string_view expected) {
  try { action(); }
  catch (const Error& failure) { assert(failure.code()==expected);return; }
  assert(false && "expected SQL rows error");
}

sql_rows::SourceReplacement edit(std::size_t source, const Cells& row,
    std::uint64_t before, std::uint64_t after) {
  return {TableId{source},std::span<const Cell>(row),before,after};
}

template<std::size_t N> SqlRowsRuntime::PreparedBatch prepare_at(SqlRowsRuntime& runtime,
    std::uint64_t sequence, const std::array<sql_rows::SourceReplacement,N>& edits,
    weighted::DeltaCapture capture=weighted::DeltaCapture::disabled) {
  return runtime.prepare_batch({sequence,std::span<const sql_rows::SourceReplacement>(edits)},capture);
}

template<std::size_t N> SqlRowsRuntime::PreparedBatch prepare(SqlRowsRuntime& runtime,
    const std::array<sql_rows::SourceReplacement,N>& edits,
    weighted::DeltaCapture capture=weighted::DeltaCapture::disabled) {
  return prepare_at(runtime,runtime.sequence()+1,edits,capture);
}

sql_rows::Epoch replace(SqlRowsRuntime& runtime, std::size_t source, const Cells& row,
    std::uint64_t before, std::uint64_t after) {
  return runtime.apply({runtime.sequence()+1,TableId{source},row,before,after});
}

CoreDelta read_core_delta(std::span<const weighted::BagDelta> entries,
    std::optional<std::uint64_t> expected_owner={}) {
  CoreDelta result;
  for (const auto& entry:entries) {
    assert(entry.change.magnitude.present());
    const auto row=storage::export_row(entry.tuple.values());
    assert(result.emplace(row,Signed{entry.change.negative,entry.change.magnitude.value}).second);
    if (expected_owner)
      assert(entry.tuple.layout().account_statistics().owner==*expected_owner);
  }
  return result;
}

CoreDelta preview_core_delta(const SqlRowsRuntime::PreparedBatch& batch,
    std::uint64_t expected_owner) {
  const auto preview=batch.native_bag_delta_preview();
  assert(preview.has_value());
  return read_core_delta(*preview,expected_owner); // Copy the borrowed span now.
}

void assert_committed_core_delta(const sql_rows::Epoch& epoch, const CoreDelta& expected,
    std::uint64_t expected_owner) {
  assert(epoch.native.bag_deltas);
  assert(read_core_delta(epoch.native.bag_deltas.entries(),expected_owner)==expected);
}

Catalog nonnull_rows_schema() {
  return {1,{{"r",{{"x",ScalarType::int64,false},{"s",ScalarType::string,false}}}}};
}

Catalog unique_schema() {
  Catalog catalog{1,{{"r",{{"id",ScalarType::int64,false},{"u",ScalarType::int64,false}}}}};
  catalog.tables[0].constraints.push_back(
      UniqueConstraint{"uk",{ColumnId{1}},ConstraintStatus::enforced});
  return catalog;
}

void exact_chains_noops_and_cancellation(bool indexed) {
  sql_rows::Options options;options.native.multiplicity_limit=3;
  const auto program=compile_rows("SELECT x FROM r",nonnull_rows_schema());
  auto runtime=create(program,indexed,options);
  const Cells row{n(7),s("row")}, absent{n(8),s("absent")};
  const std::array chain{edit(0,row,0,5),edit(0,row,5,5),edit(0,row,5,2)};
  auto prepared=prepare(runtime,chain,weighted::DeltaCapture::enabled);
  assert(prepared.active() && prepared.sequence()==1);
  assert(prepared.native_preview().metrics.native_inputs==1);
  const auto owner=runtime.program().account().statistics().owner;
  const CoreDelta expected{{CoreRow{v(7)},Signed{false,2}}};
  assert(preview_core_delta(prepared,owner)==expected);
  const auto committed=prepared.commit();
  assert(committed.changed && runtime.sequence()==1);
  assert_committed_core_delta(committed,expected,owner);
  assert(runtime.source_weight(TableId{0},row)==2);
  assert((results(runtime)==Bag{{SqlRow{v(7)},2}}));

  const std::array noops{edit(0,absent,0,0),edit(0,row,2,2)};
  auto same=prepare(runtime,noops,weighted::DeltaCapture::enabled);
  assert(same.native_preview().metrics.native_inputs==0);
  assert(preview_core_delta(same,owner).empty());
  const auto unchanged=same.commit();
  assert(!unchanged.changed && unchanged.native.changed==false);
  assert_committed_core_delta(unchanged,{},owner);
  assert(runtime.sequence()==2 && runtime.source_weight(TableId{0},row)==2);

  const std::array<sql_rows::SourceReplacement,0> empty{};
  const auto empty_epoch=prepare(runtime,empty).commit();
  assert(!empty_epoch.changed && runtime.sequence()==3);
  assert(runtime.source_weight(TableId{0},absent)==0);

  const std::array cancel{edit(0,row,2,4),edit(0,row,4,2),
      edit(0,absent,0,2),edit(0,absent,2,0)};
  auto canceled=prepare(runtime,cancel,weighted::DeltaCapture::enabled);
  assert(canceled.native_preview().metrics.native_inputs==0);
  assert(preview_core_delta(canceled,owner).empty());
  const auto canceled_epoch=canceled.commit();
  assert(!canceled_epoch.changed && runtime.sequence()==4);
  assert_committed_core_delta(canceled_epoch,{},owner);
  assert(runtime.source_weight(TableId{0},row)==2 && runtime.source_weight(TableId{0},absent)==0);
  assert((results(runtime)==Bag{{SqlRow{v(7)},2}}));
}

void wrong_chain_rolls_back_and_reuses_sequence(bool indexed) {
  sql_rows::Options options;options.native.multiplicity_limit=3;
  const auto program=compile_rows("SELECT x FROM r",nonnull_rows_schema());
  auto runtime=create(program,indexed,options);
  const Cells row{n(7),s("row")};
  const std::array stale{edit(0,row,0,5),edit(0,row,4,2)};
  error([&]{static_cast<void>(prepare(runtime,stale));},"sql_rows_weight_mismatch");
  assert(runtime.ready() && runtime.sequence()==0 && runtime.root_weight().value==0);
  assert(runtime.source_weight(TableId{0},row)==0 && results(runtime).empty());

  const std::array retry{edit(0,row,0,2)};
  auto pending=prepare(runtime,retry);
  assert(!pending.native_bag_delta_preview() && !pending.native_preview().bag_deltas);
  const auto committed=pending.commit();
  assert(committed.changed && runtime.sequence()==1);
  assert(runtime.source_weight(TableId{0},row)==2);
  assert((results(runtime)==Bag{{SqlRow{v(7)},2}}));
}

void final_unique_swap_and_violations(bool indexed) {
  const auto program=compile_rows("SELECT id, u FROM r",unique_schema());
  auto runtime=create(program,indexed);
  const Cells old_a{n(1),n(10)},old_b{n(2),n(20)};
  const Cells new_a{n(1),n(20)},new_b{n(2),n(10)};
  replace(runtime,0,old_a,0,1);replace(runtime,0,old_b,0,1);
  const auto owner=runtime.program().account().statistics().owner;
  // Both additions precede both removals in the input span; only final keys
  // are constrained, and decreases are normalized before increases.
  const std::array swap{edit(0,new_a,0,1),edit(0,new_b,0,1),
      edit(0,old_a,1,0),edit(0,old_b,1,0)};
  auto prepared=prepare(runtime,swap,weighted::DeltaCapture::enabled);
  const CoreDelta expected{{CoreRow{v(1),v(20)},Signed{false,1}},
      {CoreRow{v(2),v(10)},Signed{false,1}},
      {CoreRow{v(1),v(10)},Signed{true,1}},
      {CoreRow{v(2),v(20)},Signed{true,1}}};
  assert(preview_core_delta(prepared,owner)==expected);
  const auto committed=prepared.commit();
  assert(committed.changed && runtime.sequence()==3);
  assert_committed_core_delta(committed,expected,owner);
  assert(runtime.source_weight(TableId{0},old_a)==0 && runtime.source_weight(TableId{0},old_b)==0);
  assert(runtime.source_weight(TableId{0},new_a)==1 && runtime.source_weight(TableId{0},new_b)==1);
  assert((results(runtime)==Bag{{SqlRow{v(1),v(20)},1},{SqlRow{v(2),v(10)},1}}));

  const Cells duplicate{n(3),n(10)};
  const std::array duplicate_key{edit(0,duplicate,0,1)};
  error([&]{static_cast<void>(prepare(runtime,duplicate_key));},"unique_violation");
  const std::array weight_two{edit(0,new_b,1,2)};
  error([&]{static_cast<void>(prepare(runtime,weight_two));},"unique_violation");
  assert(runtime.ready() && runtime.sequence()==3 && runtime.source_weight(TableId{0},duplicate)==0);
  assert(runtime.source_weight(TableId{0},new_b)==1);
  assert((results(runtime)==Bag{{SqlRow{v(1),v(20)},1},{SqlRow{v(2),v(10)},1}}));
}

void foreign_key_final_order_and_untouched_child(bool indexed) {
  Catalog catalog{1,{{"p",{{"id",ScalarType::int64,false}}},
      {"c",{{"pid",ScalarType::int64,true},{"tag",ScalarType::string,false}}}}};
  catalog.tables[0].constraints.push_back(
      UniqueConstraint{"pkey",{ColumnId{0}},ConstraintStatus::enforced});
  catalog.tables[1].constraints.push_back(
      ForeignKeyConstraint{"fk",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced});
  const auto program=compile_rows("SELECT pid FROM c",catalog);
  auto runtime=create(program,indexed);
  const Cells parent{n(2)},child{n(2),s("c")},other_child{n(2),s("d")};
  const std::array add_reverse{edit(1,child,0,1),edit(0,parent,0,1),edit(1,other_child,0,1)};
  const auto added=prepare(runtime,add_reverse).commit();
  assert(added.changed && runtime.source_weight(TableId{0},parent)==1);
  assert(runtime.source_weight(TableId{1},child)==1 && runtime.source_weight(TableId{1},other_child)==1);
  assert((results(runtime)==Bag{{SqlRow{v(2)},2}}));
  const std::array child_weight{edit(1,child,1,100)};
  static_cast<void>(prepare(runtime,child_weight).commit());
  assert(runtime.source_weight(TableId{1},child)==100);
  assert((results(runtime)==Bag{{SqlRow{v(2)},101}}));
  const std::array one_child_delete{edit(0,parent,1,0),edit(1,child,100,0)};
  error([&]{static_cast<void>(prepare(runtime,one_child_delete));},"foreign_key_violation");
  assert(runtime.ready() && runtime.sequence()==2 && runtime.source_weight(TableId{1},other_child)==1);
  const std::array delete_parent_first{edit(0,parent,1,0),edit(1,child,100,0),
      edit(1,other_child,1,0)};
  const auto deleted=prepare(runtime,delete_parent_first).commit();
  assert(deleted.changed && runtime.source_weight(TableId{0},parent)==0);
  assert(runtime.source_weight(TableId{1},child)==0 && runtime.source_weight(TableId{1},other_child)==0);
  assert(results(runtime).empty());

  const Cells one_parent{n(1)},one_child{n(1),s("one")};
  replace(runtime,0,one_parent,0,1);replace(runtime,1,one_child,0,1);
  const std::array untouched_delete{edit(0,one_parent,1,0)};
  error([&]{static_cast<void>(prepare(runtime,untouched_delete));},"foreign_key_violation");
  assert(runtime.ready() && runtime.sequence()==5);
  assert(runtime.source_weight(TableId{0},one_parent)==1 && runtime.source_weight(TableId{1},one_child)==1);
  assert((results(runtime)==Bag{{SqlRow{v(1)},1}}));
  const std::array retry_delete{edit(0,one_parent,1,0),edit(1,one_child,1,0)};
  static_cast<void>(prepare(runtime,retry_delete).commit());
  assert(runtime.sequence()==6 && results(runtime).empty());
}

void self_reference_and_two_table_cycles(bool indexed) {
  Catalog self{1,{{"node",{{"id",ScalarType::int64,false},{"parent",ScalarType::int64,true}}}}};
  self.tables[0].constraints={
      UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"self",{ColumnId{1}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced}};
  auto self_runtime=create(compile_rows("SELECT id FROM node",self),indexed);
  const Cells loop{n(1),n(1)};
  const std::array self_insert{edit(0,loop,0,1)};
  const auto self_added=prepare(self_runtime,self_insert).commit();
  assert(self_added.changed && self_runtime.source_weight(TableId{0},loop)==1);
  assert((results(self_runtime)==Bag{{SqlRow{v(1)},1}}));
  const std::array self_delete{edit(0,loop,1,0)};
  static_cast<void>(prepare(self_runtime,self_delete).commit());
  assert(self_runtime.source_weight(TableId{0},loop)==0 && results(self_runtime).empty());

  Catalog cycle{1,{{"a",{{"id",ScalarType::int64,false},{"b_id",ScalarType::int64,true}}},
      {"b",{{"id",ScalarType::int64,false},{"a_id",ScalarType::int64,true}}}}};
  cycle.tables[0].constraints={
      UniqueConstraint{"a_pk",{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"a_to_b",{ColumnId{1}},TableId{1},{ColumnId{0}},ConstraintStatus::enforced}};
  cycle.tables[1].constraints={
      UniqueConstraint{"b_pk",{ColumnId{0}},ConstraintStatus::enforced},
      ForeignKeyConstraint{"b_to_a",{ColumnId{1}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced}};
  auto runtime=create(compile_rows("SELECT id FROM a",cycle),indexed); // b is an unused catalog source.
  const Cells a{n(1),n(2)},b{n(2),n(1)};
  const std::array create_cycle{edit(0,a,0,1),edit(1,b,0,1)};
  static_cast<void>(prepare(runtime,create_cycle).commit());
  assert(runtime.source_weight(TableId{0},a)==1 && runtime.source_weight(TableId{1},b)==1);
  assert((results(runtime)==Bag{{SqlRow{v(1)},1}}));
  const std::array delete_cycle{edit(1,b,1,0),edit(0,a,1,0)};
  static_cast<void>(prepare(runtime,delete_cycle).commit());
  assert(runtime.source_weight(TableId{0},a)==0 && runtime.source_weight(TableId{1},b)==0);
  assert(results(runtime).empty());

  const Cells unused_b{n(9),Cell{}}; // Null FK is MATCH SIMPLE exempt.
  const std::array unused_insert{edit(1,unused_b,0,1)};
  auto unused_pending=prepare(runtime,unused_insert,weighted::DeltaCapture::enabled);
  assert(unused_pending.native_preview().metrics.native_inputs==0);
  assert(preview_core_delta(unused_pending,runtime.program().account().statistics().owner).empty());
  const auto unused_epoch=unused_pending.commit();
  assert(unused_epoch.changed && !unused_epoch.native.changed && runtime.sequence()==3);
  assert(runtime.source_weight(TableId{1},unused_b)==1 && results(runtime).empty());
  const std::array unused_delete{edit(1,unused_b,1,0)};
  static_cast<void>(prepare(runtime,unused_delete).commit());

  const Cells missing{n(3),n(4)};
  const std::array one_sided{edit(0,missing,0,1)};
  error([&]{static_cast<void>(prepare(runtime,one_sided));},"foreign_key_violation");
  assert(runtime.ready() && runtime.sequence()==4 && runtime.source_weight(TableId{0},missing)==0);
}

void nullable_composite_keys_and_empty_keys(bool indexed) {
  Catalog catalog{1,{{"p",{{"id",ScalarType::int64,false},{"flag",ScalarType::boolean,true},
      {"a",ScalarType::int64,true}}},
      {"c",{{"a",ScalarType::int64,true},{"flag",ScalarType::boolean,true}}}}};
  catalog.tables[0].constraints.push_back(
      UniqueConstraint{"uk",{ColumnId{1},ColumnId{2}},ConstraintStatus::enforced});
  // The child physical order is (a,flag); FK key order is (flag,a), matching
  // the target's reversed composite key and mixing bool with int64 values.
  catalog.tables[1].constraints.push_back(
      ForeignKeyConstraint{"fk",{ColumnId{1},ColumnId{0}},TableId{0},
          {ColumnId{1},ColumnId{2}},ConstraintStatus::enforced});
  auto runtime=create(compile_rows("SELECT a, flag FROM c",catalog),indexed);
  const Cells parent{n(1),Cell{storage::ScalarView{true}},n(1)};
  const Cells child{n(1),Cell{storage::ScalarView{true}}};
  const Cells null_flag_a{n(2),Cell{},n(1)},null_flag_b{n(3),Cell{},n(1)};
  const Cells null_child_a{n(999),Cell{}},null_child_b{Cell{},Cell{storage::ScalarView{true}}};
  const std::array rows{edit(1,child,0,1),edit(0,parent,0,1),
      edit(0,null_flag_a,0,1),edit(0,null_flag_b,0,1),
      edit(1,null_child_a,0,1),edit(1,null_child_b,0,1)};
  static_cast<void>(prepare(runtime,rows).commit());
  assert(runtime.source_weight(TableId{0},null_flag_a)==1 && runtime.source_weight(TableId{0},null_flag_b)==1);
  assert(runtime.source_weight(TableId{1},null_child_a)==1 && runtime.source_weight(TableId{1},null_child_b)==1);
  assert((results(runtime)==Bag{
      {SqlRow{v(1),Value{true}},1},
      {SqlRow{v(999),std::nullopt},1},
      {SqlRow{std::nullopt,Value{true}},1}}));
  const Cells duplicate{n(4),Cell{storage::ScalarView{true}},n(1)};
  const std::array duplicate_key{edit(0,duplicate,0,1)};
  error([&]{static_cast<void>(prepare(runtime,duplicate_key));},"unique_violation");
  assert(runtime.ready() && runtime.sequence()==1 && runtime.source_weight(TableId{0},duplicate)==0);

  Catalog unit{1,{{"p",{{"flag",ScalarType::boolean,true}}},
      {"c",{{"flag",ScalarType::boolean,true}}}}};
  unit.tables[0].constraints.push_back(
      UniqueConstraint{"unit_pk",{},ConstraintStatus::enforced});
  unit.tables[1].constraints.push_back(
      ForeignKeyConstraint{"unit_fk",{},TableId{0},{},ConstraintStatus::enforced});
  auto empty_keys=create(compile_rows("SELECT 1 FROM c",unit),indexed);
  const Cells parent_null{Cell{}},parent_true{Cell{storage::ScalarView{true}}};
  const Cells child_null{Cell{}},child_true{Cell{storage::ScalarView{true}}};
  const std::array missing_parent{edit(1,child_null,0,1)};
  error([&]{static_cast<void>(prepare(empty_keys,missing_parent));},"foreign_key_violation");
  assert(empty_keys.ready() && empty_keys.sequence()==0);
  const std::array add_unit{edit(1,child_null,0,1),edit(0,parent_null,0,1)};
  static_cast<void>(prepare(empty_keys,add_unit).commit());
  assert(empty_keys.source_weight(TableId{0},parent_null)==1 &&
      empty_keys.source_weight(TableId{1},child_null)==1);
  assert((results(empty_keys)==Bag{{SqlRow{v(1)},1}}));
  const std::array duplicate_unit{edit(0,parent_true,0,1)};
  error([&]{static_cast<void>(prepare(empty_keys,duplicate_unit));},"unique_violation");
  const std::array weight_two{edit(0,parent_null,1,2)};
  error([&]{static_cast<void>(prepare(empty_keys,weight_two));},"unique_violation");
  const std::array untouched_child{edit(0,parent_null,1,0)};
  error([&]{static_cast<void>(prepare(empty_keys,untouched_child));},"foreign_key_violation");
  const std::array add_second_child{edit(1,child_true,0,1)};
  static_cast<void>(prepare(empty_keys,add_second_child).commit());
  assert((results(empty_keys)==Bag{{SqlRow{v(1)},2}}));
  const std::array remove_unit{edit(0,parent_null,1,0),edit(1,child_null,1,0),
      edit(1,child_true,1,0)};
  static_cast<void>(prepare(empty_keys,remove_unit).commit());
  assert(results(empty_keys).empty());
}

void cap_safe_decrease_before_increase(bool indexed) {
  sql_rows::Options options;options.native.multiplicity_limit=3;
  const auto program=compile_rows("SELECT x FROM r",nonnull_rows_schema());
  auto runtime=create(program,indexed,options);
  const Cells old_row{n(7),s("old")},new_row{n(7),s("new")};
  replace(runtime,0,old_row,0,2);
  assert(runtime.root_weight().value==2 && (results(runtime)==Bag{{SqlRow{v(7)},2}}));
  // The replacement order adds first. Staging that increase against the old
  // count would transiently produce 5, above this tuple's native cap of 3.
  const std::array replacements{edit(0,new_row,0,3),edit(0,old_row,2,0)};
  auto prepared=prepare(runtime,replacements,weighted::DeltaCapture::enabled);
  const auto owner=runtime.program().account().statistics().owner;
  const CoreDelta expected{{CoreRow{v(7)},Signed{false,1}}};
  assert(prepared.native_preview().before.value==2 && prepared.native_preview().after.value==3);
  assert(preview_core_delta(prepared,owner)==expected);
  const auto committed=prepared.commit();
  assert_committed_core_delta(committed,expected,owner);
  assert(runtime.source_weight(TableId{0},old_row)==0 && runtime.source_weight(TableId{0},new_row)==3);
  assert(runtime.root_weight().value==3 && (results(runtime)==Bag{{SqlRow{v(7)},3}}));
}

void unsigned_delta_magnitude(bool indexed) {
  const auto program=compile_rows("SELECT x FROM r",nonnull_rows_schema());
  auto runtime=create(program,indexed);
  const Cells row{n(7),s("wide-count")};
  const auto amount=(std::uint64_t{1}<<63)+17;
  const std::array insert{edit(0,row,0,amount)};
  auto prepared=prepare(runtime,insert,weighted::DeltaCapture::enabled);
  const auto owner=runtime.program().account().statistics().owner;
  const CoreDelta expected{{CoreRow{v(7)},Signed{false,amount}}};
  assert(preview_core_delta(prepared,owner)==expected);
  const auto epoch=prepared.commit();
  assert_committed_core_delta(epoch,expected,owner);
  assert(runtime.source_weight(TableId{0},row)==amount && runtime.root_weight().value==amount);
  assert((results(runtime)==Bag{{SqlRow{v(7)},amount}}));
}

void filtered_and_contradictory_sources(bool indexed) {
  const auto catalog=nonnull_rows_schema();
  const Cells filtered{n(-1),s("filtered")};
  auto all_filtered=create(compile_rows(
      "SELECT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.x > 0 AND b.x > 0",catalog),indexed);
  const std::array filtered_edit{edit(0,filtered,0,4)};
  auto filtered_pending=prepare(all_filtered,filtered_edit,weighted::DeltaCapture::enabled);
  assert(filtered_pending.native_preview().metrics.native_inputs==0);
  assert(preview_core_delta(filtered_pending,all_filtered.program().account().statistics().owner).empty());
  const auto filtered_epoch=filtered_pending.commit();
  assert(filtered_epoch.changed && !filtered_epoch.native.changed && all_filtered.sequence()==1);
  assert(all_filtered.source_weight(TableId{0},filtered)==4 && results(all_filtered).empty());

  // Equality to NULL is an existing binder contradiction. Its unused source
  // still accepts a source replacement, but creates no native input/output.
  auto contradiction=create(compile_rows("SELECT x FROM r WHERE x = NULL",catalog),indexed);
  assert(contradiction.program().contradiction());
  const Cells row{n(7),s("contradiction")};
  const std::array contradiction_edit{edit(0,row,0,2)};
  auto contradictory=prepare(contradiction,contradiction_edit,weighted::DeltaCapture::enabled);
  assert(contradictory.native_preview().metrics.native_inputs==0);
  assert(preview_core_delta(contradictory,contradiction.program().account().statistics().owner).empty());
  const auto contradiction_epoch=contradictory.commit();
  assert(contradiction_epoch.changed && !contradiction_epoch.native.changed);
  assert(contradiction.source_weight(TableId{0},row)==2 && results(contradiction).empty());
}

void aliases_single_native_epoch_and_delta_wrappers(bool indexed) {
  const auto catalog=nonnull_rows_schema();
  auto program=compile_rows("SELECT a.x FROM r a JOIN r b ON a.x=b.x",catalog);
  auto runtime=create(program,indexed);
  const Cells first{n(7),s("a")},second{n(7),s("b")};
  replace(runtime,0,first,0,2);replace(runtime,0,second,0,3);
  assert((results(runtime)==Bag{{SqlRow{v(7)},25}}));
  const auto owner=runtime.program().account().statistics().owner;
  // Increase is first in the borrowed input, but every alias decrease is
  // staged before any increase under one native pending epoch.
  const std::array edits{edit(0,second,3,5),edit(0,first,2,1)};
  auto prepared=prepare(runtime,edits,weighted::DeltaCapture::enabled);
  assert(!runtime.ready() && prepared.native_preview().sequence==3);
  assert(prepared.native_preview().metrics.native_inputs==4);
  assert(prepared.native_preview().before.value==25 && prepared.native_preview().after.value==36);
  const CoreDelta native_delta{{CoreRow{v(7)},Signed{false,11}}};
  assert(preview_core_delta(prepared,owner)==native_delta);
  const auto committed=prepared.commit();
  assert(committed.changed && committed.native.metrics.native_inputs==4);
  assert_committed_core_delta(committed,native_delta,owner);
  assert(runtime.source_weight(TableId{0},first)==1 && runtime.source_weight(TableId{0},second)==5);
  assert((results(runtime)==Bag{{SqlRow{v(7)},36}}));

  auto distinct=create(compile_rows("SELECT DISTINCT x FROM r",catalog),indexed);
  assert(distinct.program().semantics()==frontend::SqlSemantics::set);
  assert(distinct.program().export_core().query.head.size()==1 && results(distinct).empty());
  const Cells distinct_a{n(7),s("a")},distinct_b{n(7),s("b")};
  const std::array distinct_edits{edit(0,distinct_a,0,2),edit(0,distinct_b,0,3)};
  const auto distinct_owner=distinct.program().account().statistics().owner;
  auto distinct_pending=prepare(distinct,distinct_edits,weighted::DeltaCapture::enabled);
  const CoreDelta encoded_bag{{CoreRow{v(7)},Signed{false,5}}};
  assert(preview_core_delta(distinct_pending,distinct_owner)==encoded_bag);
  const auto distinct_epoch=distinct_pending.commit();
  assert_committed_core_delta(distinct_epoch,encoded_bag,distinct_owner);
  assert((results(distinct)==Bag{{SqlRow{v(7)},1}}));
  assert(distinct.source_weight(TableId{0},distinct_a)==2 && distinct.source_weight(TableId{0},distinct_b)==3);

  auto exists=create(compile_rows("SELECT EXISTS(SELECT FROM r WHERE x>0)",catalog),indexed);
  assert(exists.program().export_core().query.head.empty());
  assert((results(exists)==Bag{{SqlRow{Value{false}},1}}));
  const Cells exists_row{n(7),s("exists")};
  const std::array exists_edit{edit(0,exists_row,0,3)};
  const auto exists_owner=exists.program().account().statistics().owner;
  auto exists_pending=prepare(exists,exists_edit,weighted::DeltaCapture::enabled);
  const CoreDelta encoded_exists{{CoreRow{},Signed{false,3}}};
  assert(preview_core_delta(exists_pending,exists_owner)==encoded_exists);
  const auto exists_epoch=exists_pending.commit();
  assert_committed_core_delta(exists_epoch,encoded_exists,exists_owner);
  assert((results(exists)==Bag{{SqlRow{Value{true}},1}}));
  assert(exists.source_weight(TableId{0},exists_row)==3);
}

void one_source_allowance_and_retry(bool indexed) {
  const auto program=compile_rows(
      "SELECT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.x>0 AND b.x>0",nonnull_rows_schema());
  const Cells first{n(7),s("a")},second{n(7),s("b")};
  const std::array both{edit(0,first,0,2),edit(0,second,0,3)};
  const std::array only_first{edit(0,first,0,2)};
  auto probe=create(program,indexed);
  auto full=prepare(probe,both);
  const auto full_work=full.source_work();
  const auto measured=full.commit();
  assert(measured.source_work.structural_steps==full_work.structural_steps &&
      measured.source_work.scalar_fields==full_work.scalar_fields &&
      measured.source_work.scalar_bytes==full_work.scalar_bytes);
  assert((results(probe)==Bag{{SqlRow{v(7)},25}}));

  auto one_probe=create(program,indexed);
  const auto one_work=prepare(one_probe,only_first).commit().source_work;
  assert(full_work.structural_steps>1 && one_work.structural_steps<full_work.structural_steps-1);
  sql_rows::Options exact;exact.source_work_limit=full_work;
  auto accepted=create(program,indexed,exact);
  auto exact_batch=prepare(accepted,both);
  assert(exact_batch.source_work().structural_steps==full_work.structural_steps);
  static_cast<void>(exact_batch.commit());
  assert((results(accepted)==Bag{{SqlRow{v(7)},25}}));

  auto one_under=exact;
  --one_under.source_work_limit.structural_steps;
  auto retry=create(program,indexed,one_under);
  bool rejected=false;
  try { static_cast<void>(prepare(retry,both)); }
  catch (const storage::IndexFailure& failure) {
    assert(failure.code()=="storage_work_limit");rejected=true;
  }
  assert(rejected && retry.ready() && retry.sequence()==0 && retry.root_weight().value==0);
  assert(retry.source_weight(TableId{0},first)==0 && retry.source_weight(TableId{0},second)==0);
  assert(results(retry).empty());
  const auto retry_epoch=prepare(retry,only_first).commit();
  assert(retry_epoch.changed && retry.sequence()==1 && retry.source_weight(TableId{0},first)==2);
  assert(retry.source_weight(TableId{0},second)==0);
  assert((results(retry)==Bag{{SqlRow{v(7)},4}}));
}

void native_overflow_rolls_back_then_retries(bool indexed) {
  const auto program=compile_rows("SELECT a.x FROM r a JOIN r b ON a.x=b.x",nonnull_rows_schema());
  auto runtime=create(program,indexed);
  const Cells row{n(7),s("same")};
  replace(runtime,0,row,0,2);
  assert(runtime.root_weight().value==4 && runtime.sequence()==1);
  const std::array overflow{edit(0,row,2,std::numeric_limits<std::uint64_t>::max())};
  error([&]{static_cast<void>(prepare(runtime,overflow));},"annotation_overflow");
  assert(runtime.ready() && runtime.sequence()==1 && runtime.root_weight().value==4);
  assert(runtime.source_weight(TableId{0},row)==2);
  assert((results(runtime)==Bag{{SqlRow{v(7)},4}}));
  const std::array retry{edit(0,row,2,3)};
  const auto committed=prepare(runtime,retry).commit();
  assert(committed.changed && runtime.sequence()==2 && runtime.root_weight().value==9);
  assert(runtime.source_weight(TableId{0},row)==3);
  assert((results(runtime)==Bag{{SqlRow{v(7)},9}}));
}

void preparation_allocation_cuts_rollback_and_retry(bool indexed) {
  const auto program=compile_rows("SELECT a.x, a.s FROM r a JOIN r b ON a.x=b.x",nonnull_rows_schema());
  const Cells old_row{n(7),s("old")},new_row{n(7),s("new")};
  const std::array update{edit(0,new_row,0,3)};
  std::size_t allocations=0;
  {
    auto runtime=create(program,indexed);
    replace(runtime,0,old_row,0,2);
    {
      s04_alloc::Scope measure;
      auto prepared=prepare(runtime,update,weighted::DeltaCapture::enabled);
      allocations=s04_alloc::calls;
      prepared.rollback();
    }
  }
  assert(allocations>0);
  for (std::size_t cut=0;cut<allocations;++cut) {
    auto runtime=create(program,indexed);
    replace(runtime,0,old_row,0,2);
    bool failed=false;
    {
      s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(cut));
      try {auto prepared=prepare(runtime,update,weighted::DeltaCapture::enabled);prepared.rollback();}
      catch (const std::bad_alloc&) {failed=true;}
      assert(s04_alloc::triggered==failed);
    }
    assert(failed && runtime.ready() && runtime.sequence()==1 && runtime.root_weight().value==4);
    assert(runtime.source_weight(TableId{0},old_row)==2 && runtime.source_weight(TableId{0},new_row)==0);
    assert((results(runtime)==Bag{{SqlRow{v(7),Value{std::string("old")}},4}}));
    const auto committed=prepare(runtime,update,weighted::DeltaCapture::enabled).commit();
    assert(committed.changed && runtime.sequence()==2 && runtime.root_weight().value==25);
    assert(runtime.source_weight(TableId{0},old_row)==2 && runtime.source_weight(TableId{0},new_row)==3);
    assert((results(runtime)==Bag{
        {SqlRow{v(7),Value{std::string("old")}},10},
        {SqlRow{v(7),Value{std::string("new")}},15}}));
  }
}

void close_releases_prepared_workspace_without_new(bool indexed) {
  const auto program=compile_rows("SELECT x, s FROM r",nonnull_rows_schema());
  const Cells row{n(7),s("pending-workspace")};
  const std::array update{edit(0,row,0,2)};
  const auto exercise=[&](bool commit) {
    auto runtime=create(program,indexed);
    const auto resident=runtime.accounted_memory_statistics().current.requested_bytes;
    std::uint64_t closed=0;
    {
      auto prepared=prepare(runtime,update,weighted::DeltaCapture::enabled);
      const auto pending=runtime.accounted_memory_statistics().current.requested_bytes;
      assert(prepared.active() && pending>resident);
      std::optional<sql_rows::Epoch> committed;
      {
        s04_alloc::Scope deny(0);
        if (commit) committed.emplace(prepared.commit());
        else prepared.rollback();
        assert(s04_alloc::calls==0 && !s04_alloc::triggered);
      }
      assert(!prepared.active());
      if (commit) {
        assert(committed && committed->changed && runtime.sequence()==1);
        assert(runtime.source_weight(TableId{0},row)==2);
      } else {
        assert(!committed && runtime.sequence()==0 && runtime.source_weight(TableId{0},row)==0);
      }
      committed.reset(); // Drop returned delta payloads before measuring closed-token residency.
      closed=runtime.accounted_memory_statistics().current.requested_bytes;
      assert(closed<pending);
      assert(runtime.ready());
      if (commit) assert((results(runtime)==Bag{{SqlRow{v(7),Value{std::string("pending-workspace")}},2}}));
      else assert(results(runtime).empty());
    } // Destroy the closed facade after measuring its released workspace.
    assert(runtime.accounted_memory_statistics().current.requested_bytes==closed);
  };
  exercise(true);
  exercise(false);
}

void prepared_owner_busy_abandonment_and_move_assignment(bool indexed) {
  const auto program=compile_rows("SELECT x, s FROM r",nonnull_rows_schema());
  std::optional<SqlRowsRuntime::PreparedBatch> detached;
  resource::MemoryAccount owner_account;
  std::uint64_t owner=0;
  const std::string expected_text(300,'q');
  {
    auto runtime=create(program,indexed);
    owner_account=runtime.program().account();owner=owner_account.statistics().owner;
    detached.emplace([&] {
      // Both caller string and Cell storage die after prepare_batch returns.
      std::string text(300,'q');
      const Cells row{n(7),s(text)};
      const std::array edits{edit(0,row,0,3)};
      auto token=prepare(runtime,edits,weighted::DeltaCapture::enabled);
      assert(token.active() && token.sequence()==1 && token.program().source_sha256()==program.source_sha256());
      assert(token.native_preview().sequence==1 && token.source_work().structural_steps>0);
      const CoreDelta expected{{CoreRow{v(7),Value{text}},Signed{false,3}}};
      assert(preview_core_delta(token,owner)==expected);
      assert(!token.native_preview().bag_deltas);

      const Cells busy_row{n(8),s("busy")};
      const std::array<sql_rows::SourceReplacement,0> empty{};
      assert(!runtime.ready() && runtime.sequence()==0);
      assert(runtime.program().source_sha256()==program.source_sha256());
      static_cast<void>(runtime.accounted_memory_statistics());
      error([&]{static_cast<void>(replace(runtime,0,busy_row,0,1));},"runtime_busy");
      error([&]{static_cast<void>(runtime.results());},"runtime_busy");
      error([&]{static_cast<void>(runtime.root_weight());},"runtime_busy");
      error([&]{static_cast<void>(runtime.source_weight(TableId{0},busy_row));},"runtime_busy");
      error([&]{static_cast<void>(prepare_at(runtime,1,empty));},"runtime_busy");
      assert(token.active() && runtime.sequence()==0);
      return token;
    }());
    assert(detached->active());
    auto moved=std::move(runtime);
    assert(!moved.ready());
  } // The moved facade is gone; the prepared token still owns the SQL/native state.
  assert(detached->active() && detached->program().source_sha256()==program.source_sha256());
  const auto committed=detached->commit();
  const CoreDelta expected{{CoreRow{v(7),Value{expected_text}},Signed{false,3}}};
  assert_committed_core_delta(committed,expected,owner);
  const auto entries=committed.native.bag_deltas.entries();
  assert(entries.size()==1 && entries[0].tuple.layout().account_statistics().owner==owner);
  const auto copied=storage::export_row(entries[0].tuple.values());
  assert(copied.size()==2 && std::get<std::string>(copied[1])==expected_text);
  assert(!detached->active());
  error([&]{static_cast<void>(detached->sequence());},"invalid_sql_rows_batch");
  detached->rollback();detached->rollback();

  auto first=create(program,indexed),second=create(program,indexed);
  const auto first_owner=first.program().account().statistics().owner;
  const auto second_owner=second.program().account().statistics().owner;
  assert(first_owner!=second_owner);
  const Cells first_row{n(1),s("first")},second_row{n(2),s("second")};
  const std::array first_edit{edit(0,first_row,0,1)},second_edit{edit(0,second_row,0,1)};
  auto old_token=prepare(first,first_edit,weighted::DeltaCapture::enabled);
  auto token=prepare(second,second_edit,weighted::DeltaCapture::enabled);
  old_token=std::move(token); // Destroys/rolls back the old token on first's owner.
  assert(first.ready() && first.sequence()==0);
  assert(!second.ready() && second.sequence()==0 && !token.active());
  assert(old_token.active() && old_token.program().account().statistics().owner==second_owner);
  old_token.rollback();old_token.rollback();
  assert(second.ready() && second.sequence()==0 && second.source_weight(TableId{0},second_row)==0);
  error([&]{static_cast<void>(old_token.program());},"invalid_sql_rows_batch");

  {
    const std::array abandoned{edit(0,first_row,0,1)};
    auto token_abandoned=prepare(first,abandoned);
    assert(!first.ready() && token_abandoned.active());
  }
  assert(first.ready() && first.sequence()==0 && first.source_weight(TableId{0},first_row)==0);
  assert(results(first).empty());
}

} // namespace

int main() {
  try {
    for (const bool indexed:{false,true}) {
      exact_chains_noops_and_cancellation(indexed);
      wrong_chain_rolls_back_and_reuses_sequence(indexed);
      final_unique_swap_and_violations(indexed);
      foreign_key_final_order_and_untouched_child(indexed);
      self_reference_and_two_table_cycles(indexed);
      nullable_composite_keys_and_empty_keys(indexed);
      cap_safe_decrease_before_increase(indexed);
      unsigned_delta_magnitude(indexed);
      filtered_and_contradictory_sources(indexed);
      aliases_single_native_epoch_and_delta_wrappers(indexed);
      one_source_allowance_and_retry(indexed);
      native_overflow_rolls_back_then_retries(indexed);
      preparation_allocation_cuts_rollback_and_retry(indexed);
      close_releases_prepared_workspace_without_new(indexed);
      prepared_owner_busy_abandonment_and_move_assignment(indexed);
    }
    std::cout<<"SQL source net batches match final source and explicit SQL bags\n";
  } catch (const std::exception& failure) { std::cerr<<failure.what()<<'\n';return 1; }
}
