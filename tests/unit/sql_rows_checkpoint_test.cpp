#include "crown/recovery/sql_rows_checkpoint.hpp"
#include "crown/io/document.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>

namespace {
using namespace crown;
namespace rr=recovery::sql_rows;
using Cell=runtime::sql_rows::Cell;
using Bag=std::map<std::string,std::uint64_t>;
constexpr std::uint64_t memory=64ULL*1024*1024;
Cell n(std::int64_t x) {return storage::ScalarView{x};}
Cell text(std::string_view x) {return storage::ScalarView{x};}
Cell flag(bool x) {return storage::ScalarView{x};}
frontend::SqlRowsProgram bind(std::string_view sql,const Catalog& catalog) {
  frontend::SqlRowsBindOptions options;options.retain_binding_image=true;
  auto result=frontend::bind_sql_rows(sql,catalog,options);assert(std::holds_alternative<frontend::SqlRowsProgram>(result));
  return std::get<frontend::SqlRowsProgram>(std::move(result));
}
FreeConnexTree tree(const frontend::SqlRowsProgram& program) {
  const auto core=program.export_core();if(program.contradiction() || core.query.atoms.empty())return {};
  const auto chosen=planner::minimum_tree(core.catalog,core.query);assert(chosen.tree);return *chosen.tree;
}
Bag rows(runtime::SqlRowsRuntime& runtime) {
  Bag result;auto cursor=runtime.results();
  while(const auto next=cursor.next()) {
    auto values=io::Json::array();for(const auto& value:next->tuple.view())values.push_back(value?io::write_scalar_view(*value):io::Json{});
    assert(result.emplace(values.dump(),next->multiplicity).second);
  }
  return result;
}
rr::CheckpointMetadata metadata(const rr::Descriptor& descriptor,std::uint64_t c,std::uint64_t i) {
  rr::Id query{},sink{};query.fill('1');sink.fill('2');rr::Hash hash{};hash.fill('3');
  return {{query,descriptor.sha256()},2,c,i,{sink,c,1,hash}};
}
runtime::sql_rows::RebuildLimits build(bool indexed) {
  runtime::sql_rows::RebuildLimits limits;
  if(indexed)limits.indexed_work=storage::IndexWork{1000000000,1000000000,1000000000,1000000000,1000000000};
  return limits;
}
template<class Action> void rejected(Action action) {
  bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(failed);
}
template<class Action> void refused(Action action) {
  bool failed=false;try{action();}catch(const std::exception&){failed=true;}assert(failed);
}
void round_trip(bool indexed) {
  const Catalog catalog{1,{{"r",{{"id",ScalarType::int64,true},{"g",ScalarType::string,true},{"tag",ScalarType::string,true},{"keep",ScalarType::boolean}}},
      {"s",{{"id",ScalarType::int64,true},{"y",ScalarType::int64,true}}},{"unused",{{"x",ScalarType::int64}}}}};
  const auto program=bind("SELECT a.id,a.g,b.y FROM r a JOIN s b ON a.id=b.id WHERE a.keep",catalog);
  const auto account=resource::MemoryAccount::create(memory);auto live=rr::admit_into(account,program,tree(program),indexed?s04_runtime::options():PhysicalOptions{}, {}, {});
  const std::array<Cell,4> a{n(1),Cell{},text("a"),flag(true)},b{n(1),Cell{},text("b"),flag(true)},c{n(2),text(""),Cell{},flag(true)},
      null_id{Cell{},Cell{},text("null"),flag(true)},filtered{n(1),text("filtered"),Cell{},flag(false)};
  const std::array<Cell,2> x{n(1),n(7)},y{n(2),n(7)},z{Cell{},n(8)};const std::array<Cell,1> unused{n(42)};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},a,0,2},runtime::sql_rows::SourceReplacement{TableId{0},b,0,3},
      runtime::sql_rows::SourceReplacement{TableId{0},c,0,1},runtime::sql_rows::SourceReplacement{TableId{0},null_id,0,11},
      runtime::sql_rows::SourceReplacement{TableId{0},filtered,0,7},runtime::sql_rows::SourceReplacement{TableId{1},x,0,2},
      runtime::sql_rows::SourceReplacement{TableId{1},y,0,4},runtime::sql_rows::SourceReplacement{TableId{1},z,0,13},
      runtime::sql_rows::SourceReplacement{TableId{2},unused,0,9}};
  static_cast<void>(live.runtime.prepare_batch({1,edits}).commit());static_cast<void>(live.runtime.prepare_batch({2,{}}).commit());
  const Bag expected{{"[1,null,7]",10},{"[2,\"\",7]",4}};assert(rows(live.runtime)==expected);
  auto source=live.runtime.source_snapshot();assert(source.rows.size()==9);
  io::AccountedInputProgress progress(account);progress.sequence=5;
  auto r=progress.source_positions.prepare("feed-r",30);progress.source_positions.publish(r);
  auto s=progress.source_positions.prepare("feed-s",40);progress.source_positions.publish(s);
  const auto header=metadata(live.descriptor,2,5);const rr::ReaderPosition reader{200,5};
  const auto image=rr::encode_checkpoint(account,live.descriptor,source,header,progress,reader);
  std::reverse(source.rows.begin(),source.rows.end());const auto reversed=rr::encode_checkpoint(account,live.descriptor,source,header,progress,reader);
  assert(image.bytes()==reversed.bytes());source.rows.push_back(source.rows[0]);
  rejected([&]{auto bad=rr::encode_checkpoint(account,live.descriptor,source,header,progress,reader);});source.rows.pop_back();
  const auto receiver=resource::MemoryAccount::create(memory);std::string wire(image.bytes());
  auto restored=rr::restore_checkpoint_into(receiver,live.descriptor,wire,header,build(indexed));
  assert(restored.runtime.sequence()==2 && restored.progress.sequence==5 && restored.reader==reader && rows(restored.runtime)==expected);
  assert(restored.progress.source_positions==progress.source_positions && restored.runtime.source_snapshot().rows.size()==9);
  for(const auto& entry:source.rows)assert(restored.runtime.source_weight(entry.source,entry.row.view())==entry.weight);
  auto wrong=header;++wrong.command_sequence;const auto before=receiver.statistics().current;
  rejected([&]{auto bad=rr::restore_checkpoint_into(receiver,live.descriptor,wire,wrong,build(indexed));});assert(receiver.statistics().current==before);
  wire.assign(wire.size(),'x'); // All restored TEXT and rows now have independent receiving ownership.
  const std::array next{runtime::sql_rows::SourceReplacement{TableId{1},x,2,1}};
  auto left=live.runtime.prepare_output_batch({3,next}),right=restored.runtime.prepare_output_batch({3,next});
  rr::Hash input{};input.fill('a');const auto l=rr::encode(account,program,3,rr::RowEpochView{2,6,3,input,true,&left});
  const auto q=rr::encode(receiver,program,3,rr::RowEpochView{2,6,3,input,true,&right});assert(l.bytes()==q.bytes());
  static_cast<void>(left.commit());static_cast<void>(right.commit());assert((rows(restored.runtime)==Bag{{"[1,null,7]",5},{"[2,\"\",7]",4}}));
  const auto inspected=rr::inspect_checkpoint(live.descriptor,image.bytes());rr::CheckpointLimits exact;
  exact.image.bytes=image.bytes().size();exact.image.work=inspected.statistics.work;exact.image.rows=9;exact.image.tables=3;exact.image.fields=4;exact.sources=2;
  static_cast<void>(rr::inspect_checkpoint(live.descriptor,image.bytes(),exact));
  for(unsigned which=0;which<6;++which) {
    auto low=exact;
    if(which==0)--low.image.bytes;
    if(which==1)--low.image.work;
    if(which==2)--low.image.rows;
    if(which==3)--low.image.tables;
    if(which==4)--low.image.fields;
    if(which==5)--low.sources;
    rejected([&]{static_cast<void>(rr::inspect_checkpoint(live.descriptor,image.bytes(),low));});
  }
  {s04_alloc::Scope deny(0);static_cast<void>(rr::inspect_checkpoint(live.descriptor,image.bytes()));assert(s04_alloc::calls==0);}
  for(std::size_t size=0;size<image.bytes().size();++size)
    rejected([&]{static_cast<void>(rr::inspect_checkpoint(live.descriptor,image.bytes().substr(0,size)));});
  for(std::size_t i=0;i<image.bytes().size();++i) {std::string bad(image.bytes());bad[i]^=1;rejected([&]{static_cast<void>(rr::inspect_checkpoint(live.descriptor,bad));});}
}
void static_and_terminal() {
  for(const bool truth:{false,true}) {
    const auto program=bind(truth?"SELECT NULL::text,TRUE":"SELECT NULL::text,TRUE WHERE false",{});
    const auto account=resource::MemoryAccount::create(memory);auto live=rr::admit_into(account,program,{}, {}, {}, {});
    io::AccountedInputProgress progress(account);auto source=live.runtime.source_snapshot();const auto header=metadata(live.descriptor,0,0);
    const auto image=rr::encode_checkpoint(account,live.descriptor,source,header,progress);
    auto restored=rr::restore_checkpoint_into(account,live.descriptor,image.bytes(),header,{});
    assert(rows(restored.runtime)==(truth?Bag{{"[null,true]",1}}:Bag{}));
    source.sequence=UINT64_MAX;progress.sequence=UINT64_MAX;const auto terminal=metadata(live.descriptor,UINT64_MAX,UINT64_MAX);
    const auto final=rr::encode_checkpoint(account,live.descriptor,source,terminal,progress);
    auto end=rr::restore_checkpoint_into(account,live.descriptor,final.bytes(),terminal,{});
    assert(end.runtime.sequence()==UINT64_MAX);refused([&]{auto next=end.runtime.prepare_batch({0,{}});});
  }
}
void semantic_rows() {
  Catalog catalog{1,{{"u",{{"id",ScalarType::int64},{"tag",ScalarType::string}}}}};
  catalog.tables[0].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
  const auto program=bind("SELECT id FROM u",catalog);const auto account=resource::MemoryAccount::create(memory);
  auto live=rr::admit_into(account,program,tree(program),{}, {}, {});auto source=live.runtime.source_snapshot();source.sequence=1;
  const std::array<Cell,2> a{n(7),text("a")},b{n(7),text("b")};
  source.rows.push_back({TableId{0},runtime::sql_rows::Tuple::copy_of(account,a),1});
  source.rows.push_back({TableId{0},runtime::sql_rows::Tuple::copy_of(account,b),1});
  io::AccountedInputProgress progress(account);progress.sequence=1;const auto header=metadata(live.descriptor,1,1);
  const auto image=rr::encode_checkpoint(account,live.descriptor,source,header,progress);static_cast<void>(rr::inspect_checkpoint(live.descriptor,image.bytes()));
  const auto receiver=resource::MemoryAccount::create(memory);
  refused([&]{auto invalid=rr::restore_checkpoint_into(receiver,live.descriptor,image.bytes(),header,{});});
  assert(receiver.statistics().current.allocations==1);receiver.check_invariants();
}
} // namespace
int main() {
  try {for(const bool indexed:{false,true})round_trip(indexed);static_and_terminal();semantic_rows();
    std::cout<<"plain SQL row checkpoints: exact physical bags, nullable results and genuine cold rebuild\n";
  } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
