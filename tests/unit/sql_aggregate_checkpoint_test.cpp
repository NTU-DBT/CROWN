#include "crown/recovery/sql_aggregate_checkpoint.hpp"
#include "crown/api/error.hpp"
#include "crown/io/document.hpp"
#include "crown/ir/digest.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>

namespace {
using namespace crown;
namespace ar=recovery::sql_aggregate;
using Cell=runtime::sql_rows::Cell;
using Groups=std::map<runtime::aggregate::Row,runtime::aggregate::Row>;
constexpr std::uint64_t memory=64ULL*1024*1024;
Cell number(std::int64_t value) {return storage::ScalarView{value};}
Cell text(std::string_view value) {return storage::ScalarView{value};}
frontend::SqlAggregateProgram bind(std::string_view sql,const Catalog& catalog) {
  auto result=frontend::bind_sql_aggregate(sql,catalog);assert(std::holds_alternative<frontend::SqlAggregateProgram>(result));
  return std::get<frontend::SqlAggregateProgram>(std::move(result));
}
ar::Admitted admit(const resource::MemoryAccount& account,const frontend::SqlAggregateProgram& program,bool indexed) {
  FreeConnexTree tree;
  if(!program.source_program().contradiction()) {
    const auto core=program.source_program().export_core();const auto chosen=planner::minimum_tree(core.catalog,core.query);assert(chosen.tree);tree=*chosen.tree;
  }
  runtime::sql_aggregate::Options options;options.capture_changes=true;
  return ar::admit_into(account,program,tree,indexed?s04_runtime::options():PhysicalOptions{},options);
}
runtime::sql_aggregate::RebuildLimits limits(bool indexed) {
  runtime::sql_aggregate::RebuildLimits result;result.source.source_work={10000000,10000000,64ULL*1024*1024,10000000,10000000};
  result.source.native_work=10000000;result.group_work=10000000;
  if(indexed)result.source.indexed_work=storage::IndexWork{1000000000,1000000000,1000000000,1000000000,1000000000};
  return result;
}
ar::CheckpointMetadata metadata(const ar::Descriptor& descriptor,std::uint64_t c,std::uint64_t i) {
  ar::CheckpointMetadata value;value.binding.query_id.fill('0');value.binding.descriptor_sha256=descriptor.sha256();
  value.generation=7;value.physical_sequence=c;value.command_sequence=i;
  value.delivery.sink_id.fill('2');value.delivery.sequence=c;value.delivery.bytes=1234;value.delivery.content_sha256.fill('c');return value;
}
void position(io::AccountedInputProgress& progress,std::string_view name,std::uint64_t offset) {
  auto node=progress.source_positions.prepare(name,offset);progress.source_positions.publish(node);
}
Groups groups(const runtime::SqlAggregateRuntime& runtime) {
  Groups values;for(const auto& group:runtime.snapshot().groups)assert(values.emplace(group.key.export_values(),group.values.export_values()).second);return values;
}
template<class Action> void wire_rejected(Action action) {
  bool rejected=false;{s04_alloc::Scope deny(0);try{action();}catch(const recovery::ImageFailure&){rejected=true;}assert(s04_alloc::calls==0);}assert(rejected);
}
template<class Action> void refused(Action action) {
  bool rejected=false;try{action();}catch(const std::exception&){rejected=true;}assert(rejected);
}
void receiving_caps(const ar::Descriptor& descriptor,std::string_view wire,const ar::CheckpointMetadata& expected,bool indexed) {
  std::uint64_t peak=0;
  {auto account=resource::MemoryAccount::create(memory);{auto restored=ar::restore_checkpoint_into(account,descriptor,wire,expected,limits(indexed));peak=account.statistics().peak_requested_bytes;}
    assert(account.statistics().current.allocations==1);}
  {auto account=resource::MemoryAccount::create(peak);auto restored=ar::restore_checkpoint_into(account,descriptor,wire,expected,limits(indexed));assert(account.statistics().peak_requested_bytes==peak);}
  {auto account=resource::MemoryAccount::create(peak-1);bool rejected=false;
    try{auto restored=ar::restore_checkpoint_into(account,descriptor,wire,expected,limits(indexed));}
    catch(const resource::MemoryFailure& error){rejected=error.fault()==resource::MemoryFault::limit;}
    assert(rejected && account.statistics().current.allocations==1);account.check_invariants();}
}
void round_trip(bool indexed) {
  const Catalog catalog{1,{{"r",{{"id",ScalarType::int64,true},{"g",ScalarType::string,true},{"x",ScalarType::int64,true},{"flag",ScalarType::boolean}}},
      {"s",{{"id",ScalarType::int64,true},{"y",ScalarType::int64,true}}},{"unused",{{"z",ScalarType::int64}}}}};
  const auto program=bind("SELECT a.g,COUNT(*),SUM(b.y),AVG(b.y) FROM r a JOIN s b ON a.id=b.id WHERE a.flag GROUP BY a.id,a.g",catalog);
  const auto sender=resource::MemoryAccount::create(memory);auto live=admit(sender,program,indexed);
  const std::array<Cell,4> a{number(1),text("same"),number(7),storage::ScalarView{true}},
      b{number(2),text("same"),number(9),storage::ScalarView{true}},null_id{Cell{},Cell{},number(8),storage::ScalarView{true}},
      filtered{number(1),text("filtered"),number(8),storage::ScalarView{false}},c{number(3),{},{},storage::ScalarView{true}};
  const std::array<Cell,2> x{number(1),number(5)},y{number(2),number(5)},z{number(3),{}};const std::array<Cell,1> unused{number(42)};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},a,0,2},runtime::sql_rows::SourceReplacement{TableId{0},b,0,2},
      runtime::sql_rows::SourceReplacement{TableId{0},null_id,0,4},runtime::sql_rows::SourceReplacement{TableId{0},filtered,0,7},
      runtime::sql_rows::SourceReplacement{TableId{0},c,0,1},runtime::sql_rows::SourceReplacement{TableId{1},x,0,3},
      runtime::sql_rows::SourceReplacement{TableId{1},y,0,3},runtime::sql_rows::SourceReplacement{TableId{1},z,0,4},
      runtime::sql_rows::SourceReplacement{TableId{2},unused,0,5}};
  static_cast<void>(live.runtime.prepare_batch({1,edits}).commit());static_cast<void>(live.runtime.prepare_batch({2,{}}).commit());
  auto source=live.runtime.source_snapshot();assert(source.source.rows.size()==9 && groups(live.runtime).size()==3);
  io::AccountedInputProgress progress(sender);progress.sequence=5;position(progress,"feed-r",30);position(progress,"s-ø",40);
  const auto header=metadata(live.descriptor,2,5);const ar::ReaderPosition reader{200,5};
  const auto image=ar::encode_checkpoint(sender,live.descriptor,source,header,progress,reader);
  const auto inspected=ar::inspect_checkpoint(live.descriptor,image.bytes());assert(inspected.rows==9 && inspected.sources==2 && inspected.reader==reader);
  std::reverse(source.source.rows.begin(),source.source.rows.end());const auto reversed=ar::encode_checkpoint(sender,live.descriptor,source,header,progress,reader);
  assert(reversed.bytes()==image.bytes());source.source.rows.push_back(source.source.rows[0]);
  refused([&]{auto duplicate=ar::encode_checkpoint(sender,live.descriptor,source,header,progress,reader);});source.source.rows.pop_back();
  auto receiver=resource::MemoryAccount::create(memory);std::string wire(image.bytes());auto restored=ar::restore_checkpoint_into(receiver,live.descriptor,wire,header,limits(indexed));
  assert(restored.runtime.sequence()==2 && restored.progress.sequence==5 && restored.reader==reader && restored.progress.source_positions==progress.source_positions);
  assert(groups(restored.runtime)==groups(live.runtime));assert(restored.runtime.source_snapshot().source.rows.size()==9);
  assert(restored.runtime.program().account().statistics().owner==receiver.statistics().owner);
  auto wrong=header;++wrong.command_sequence;wire_rejected([&]{auto rejected=ar::restore_checkpoint_into(receiver,live.descriptor,wire,wrong,limits(indexed));});
  ar::CheckpointLimits exact;exact.image.work=restored.statistics.work;{auto value=ar::restore_checkpoint_into(receiver,live.descriptor,wire,header,limits(indexed),exact);assert(value.statistics.work==restored.statistics.work);}
  --exact.image.work;const auto before=receiver.statistics().current;refused([&]{auto value=ar::restore_checkpoint_into(receiver,live.descriptor,wire,header,limits(indexed),exact);});assert(receiver.statistics().current==before);
  receiving_caps(live.descriptor,wire,header,indexed);wire.assign(wire.size(),'x');
  const std::array next{runtime::sql_rows::SourceReplacement{TableId{1},x,3,1}};
  const auto left=live.runtime.prepare_batch({3,next}).commit(),right=restored.runtime.prepare_batch({3,next}).commit();
  assert(left.output.size()==1 && right.output.size()==1 && left.output[0].key==right.output[0].key && left.output[0].before==right.output[0].before && left.output[0].after==right.output[0].after);
  assert(groups(restored.runtime)==groups(live.runtime));
  const auto info=ar::inspect_checkpoint(live.descriptor,image.bytes());
  exact={};exact.image.bytes=image.bytes().size();exact.image.work=info.statistics.work;exact.image.rows=9;exact.image.tables=3;exact.image.fields=4;exact.sources=2;
  static_cast<void>(ar::inspect_checkpoint(live.descriptor,image.bytes(),exact));
  for(unsigned which=0;which<6;++which) {auto low=exact;if(which==0)--low.image.bytes;if(which==1)--low.image.work;if(which==2)--low.image.rows;if(which==3)--low.image.tables;if(which==4)--low.image.fields;if(which==5)--low.sources;
    wire_rejected([&]{static_cast<void>(ar::inspect_checkpoint(live.descriptor,image.bytes(),low));});}
  for(std::size_t cut=0;cut<image.bytes().size();++cut)wire_rejected([&]{static_cast<void>(ar::inspect_checkpoint(live.descriptor,image.bytes().substr(0,cut)));});
  for(std::size_t i=0;i<image.bytes().size();++i){std::string bad(image.bytes());bad[i]^=1;wire_rejected([&]{static_cast<void>(ar::inspect_checkpoint(live.descriptor,bad));});}
  sender.check_invariants();receiver.check_invariants();
}
void terminal_and_empty() {
  const Catalog catalog{1,{{"r",{{"id",ScalarType::int64}}}}};const auto program=bind("SELECT COUNT(*)",catalog);
  auto account=resource::MemoryAccount::create(memory);auto live=admit(account,program,false);io::AccountedInputProgress progress(account);progress.sequence=3;
  const auto zero=ar::encode_checkpoint(account,live.descriptor,live.runtime.source_snapshot(),metadata(live.descriptor,0,3),progress,ar::ReaderPosition{0,0});
  auto restored=ar::restore_checkpoint_into(account,live.descriptor,zero.bytes(),zero.info().metadata,limits(false));assert(restored.runtime.sequence()==0 && restored.progress.sequence==3 && restored.runtime.root_weight()==annotations::Multiplicity{1});
  auto source=live.runtime.source_snapshot();source.source.sequence=UINT64_MAX;progress.sequence=UINT64_MAX;
  const auto last=ar::encode_checkpoint(account,live.descriptor,source,metadata(live.descriptor,UINT64_MAX,UINT64_MAX),progress);
  auto terminal=ar::restore_checkpoint_into(account,live.descriptor,last.bytes(),last.info().metadata,limits(false));assert(terminal.runtime.sequence()==UINT64_MAX);
  refused([&]{auto pending=terminal.runtime.prepare_batch({0,{}});});
  auto no_work=limits(false);no_work.group_work=0;const auto before=account.statistics().current;
  refused([&]{auto value=ar::restore_checkpoint_into(account,live.descriptor,zero.bytes(),zero.info().metadata,no_work);});assert(account.statistics().current==before);
}
// Well-typed mutable image rows still require the actual source constraints and
// aggregate arithmetic. Rejection leaves the fresh receiving owner unpublished.
void semantic_rows() {
  for(unsigned kind=0;kind<3;++kind) {
    Catalog catalog{1,{{"r",{{"id",ScalarType::int64}}}}};
    if(kind!=0)catalog.tables[0].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
    if(kind==2) {
      catalog.tables.push_back({"s",{{"id",ScalarType::int64}}});
      catalog.tables[1].constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced});
    }
    const auto program=bind(kind==2?"SELECT COUNT(*) FROM s":"SELECT COUNT(*) FROM r",catalog);
    const auto producer=resource::MemoryAccount::create(memory);auto live=admit(producer,program,false);auto source=live.runtime.source_snapshot();source.source.sequence=1;
    const std::array<Cell,1> row{number(7)};
    source.source.rows.push_back({TableId{kind==2?1U:0U},runtime::aggregate::Tuple::copy_of(producer,row),kind==0?UINT64_MAX:kind==1?2U:1U});
    io::AccountedInputProgress progress(producer);progress.sequence=1;const auto header=metadata(live.descriptor,1,1);
    const auto image=ar::encode_checkpoint(producer,live.descriptor,source,header,progress);
    const auto receiver=resource::MemoryAccount::create(memory);bool failed=false;
    try{auto value=ar::restore_checkpoint_into(receiver,live.descriptor,image.bytes(),header,limits(false));}
    catch(const Error& error){failed=error.code()==(kind==0?"aggregate_overflow":kind==1?"unique_violation":"foreign_key_violation");}
    assert(failed && receiver.statistics().current.allocations==1 && live.runtime.sequence()==0);receiver.check_invariants();
  }
}
// Emit a known complete physical image. Python reconstructs every wire byte
// independently using only this declared fixture and SHA256(descriptor bytes).
void emit(const char* directory) {
  const Catalog catalog{1,{{"r",{{"k",ScalarType::int64},{"t",ScalarType::string,true},{"b",ScalarType::boolean},
      {"d",ScalarType::date},{"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{6,2}}}},{"unused",{{"z",ScalarType::int64}}}}};
  const auto program=bind("SELECT COUNT(*) FROM r",catalog);auto account=resource::MemoryAccount::create(memory);auto live=admit(account,program,false);
  const std::array<Cell,5> a{number(-7),text("µ"),storage::ScalarView{true},storage::ScalarView{Date::parse("2024-02-29")},storage::ScalarView{storage::InlineDecimal::parse("-1.25")}},
      b{number(8),{},storage::ScalarView{false},storage::ScalarView{Date::parse("2000-01-01")},storage::ScalarView{storage::InlineDecimal::parse("0")}};
  const std::array<Cell,1> z{number(-1)};const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},a,0,2},runtime::sql_rows::SourceReplacement{TableId{0},b,0,1},runtime::sql_rows::SourceReplacement{TableId{1},z,0,3}};
  static_cast<void>(live.runtime.prepare_batch({1,edits}).commit());io::AccountedInputProgress progress(account);progress.sequence=4;
  position(progress,"feed α",9);position(progress,"feed-z",20);
  const auto image=ar::encode_checkpoint(account,live.descriptor,live.runtime.source_snapshot(),metadata(live.descriptor,1,4),progress,ar::ReaderPosition{200,3});
  std::filesystem::create_directories(directory);
  for(const auto& [name,bytes]:{std::pair{"descriptor.bin",live.descriptor.bytes()},std::pair{"checkpoint.bin",image.bytes()}}) {
    std::ofstream out(std::filesystem::path(directory)/name,std::ios::binary);out.write(bytes.data(),static_cast<std::streamsize>(bytes.size()));assert(out);
  }
}
} // namespace
int main(int argc,char** argv) {
  assert(argc==1 || argc==2);for(const bool indexed:{false,true})round_trip(indexed);terminal_and_empty();semantic_rows();if(argc==2)emit(argv[1]);
  std::cout<<"R2 complete physical checkpoint/cold restore; C/I progress; both backends; full NULL keys/filtered/unused bags; next delta; caps/corruption passed\n";
}
