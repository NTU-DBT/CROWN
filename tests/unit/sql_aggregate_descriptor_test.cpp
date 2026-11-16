#include "crown/recovery/sql_aggregate_descriptor.hpp"
#include "crown/ir/digest.hpp"
#include "crown/io/document.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <cassert>
#include <fstream>
#include <iostream>

namespace {
using namespace crown;
namespace ar = recovery::sql_aggregate;
using Cell = runtime::sql_rows::Cell;
using Json = io::Json;
constexpr std::uint64_t memory=64ULL*1024*1024;
Catalog catalog(bool opaque=false) {
  Catalog schema{1,{{"r",{{"id",ScalarType::int64},{"g",ScalarType::string,true},
      {"x",ScalarType::int64,true},{"flag",ScalarType::boolean}}},{"unused",{{"z",ScalarType::int64}}}}};
  if(opaque)schema.tables[0].key_hints.push_back({{ColumnId{0}},std::string(1,static_cast<char>(0xff))});
  return schema;
}
frontend::SqlAggregateProgram bind(bool opaque=false,std::string_view sql=
    "SELECT a.g,COUNT(*),SUM(a.x),AVG(a.x) FROM r a WHERE a.id>$1 AND a.flag GROUP BY a.id,a.g") {
  frontend::SqlAggregateBindOptions options;options.source.binding.parameters={{"threshold",ScalarType::int64}};
  options.source.parameters={Value{std::int64_t{2}}};options.kernel.average_scale=2;
  const auto schema=catalog(opaque);auto result=frontend::bind_sql_aggregate(sql,schema,options);
  assert(std::holds_alternative<frontend::SqlAggregateProgram>(result));return std::get<frontend::SqlAggregateProgram>(std::move(result));
}
FreeConnexTree tree(const frontend::SqlAggregateProgram& program) {
  if(program.source_program().contradiction())return {};
  const auto core=program.source_program().export_core();const auto selected=planner::minimum_tree(core.catalog,core.query);
  assert(selected.tree);return *selected.tree;
}
runtime::sql_aggregate::Options normal() {
  runtime::sql_aggregate::Options options;options.capture_changes=true;options.count_limit=10;
  options.source.native.multiplicity_limit=30;options.group_work_limit=200000;
  options.source.source_work_limit={200000,200000,8ULL*1024*1024,0,0};return options;
}
Cell number(std::int64_t value) {return storage::ScalarView{value};}
// Independent test framing permits checksum-valid hostile CBOR without codec
// encoder authority. This follows the documented 148-byte protected envelope.
void word(std::string& out,std::uint64_t value) {for(unsigned i=0;i<8;++i)out+=static_cast<char>(value>>(8*i));}
std::string envelope(std::string_view binding,std::string_view recipe) {
  std::string body;word(body,binding.size());body+=binding;word(body,recipe.size());body+=recipe;
  std::string result("CROWNAD2\x01\x00\x00\x00",12);word(result,body.size());
  const auto hash=sha256_fixed(body);result.append(hash.data(),hash.size());
  const auto prefix=sha256_fixed(result);result.append(prefix.data(),prefix.size());return result+body;
}
std::string bytes(const std::vector<std::uint8_t>& value) {return {reinterpret_cast<const char*>(value.data()),value.size()};}
template<class Action> void wire_rejected(Action action) {
  bool failed=false;{s04_alloc::Scope deny(0);try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(s04_alloc::calls==0);}assert(failed);
}
template<class Action> void refused(Action action) {
  bool failed=false;try{action();}catch(const std::exception&){failed=true;}assert(failed);
}
void cbor_and_frame(const char* fixture) {
  const auto valid=envelope(std::string_view("\xa0",1),std::string_view("\xa0",1));
  std::ifstream file(fixture);std::string hex;file>>hex;assert(hex.size()==valid.size()*2);
  constexpr std::string_view digits="0123456789abcdef";
  for(std::size_t i=0;i<valid.size();++i){const auto byte=static_cast<unsigned char>(valid[i]);assert(hex[2*i]==digits[byte>>4] && hex[2*i+1]==digits[byte&15]);}
  ar::InspectedDescriptor inspected{};{s04_alloc::Scope deny(0);inspected=ar::inspect_descriptor(valid);assert(s04_alloc::calls==0);}
  assert(inspected.sha256==sha256_fixed(valid) && inspected.binding_image==std::string_view("\xa0",1));
  for(std::size_t cut=0;cut<valid.size();++cut)wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(std::string_view(valid).substr(0,cut)));});
  for(std::size_t i=0;i<valid.size();++i){auto bad=valid;bad[i]^=1;wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(bad));});}
  const std::array bad{
      std::string("\xbf\xff",2),std::string("\x18\x01",2),std::string("\x59\x01\x00",3),
      std::string("\xc0\x00",2),std::string("\xf9\x3c\x00",3),std::string("\xf7",1),
      std::string("\xa2\x61\x61\x01\x61\x61\x02",7),std::string("\xa2\x61\x62\x01\x61\x61\x02",7),
      std::string("\xa1\x61\xff\x00",4),std::string("\x3b\x80\x00\x00\x00\x00\x00\x00\x00",9),
      std::string("\x9b\xff\xff\xff\xff\xff\xff\xff\xff",9)};
  for(const auto& cbor:bad){const auto hostile=envelope(cbor,std::string_view("\xa0",1));wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(hostile));});}
  std::string deep(130,static_cast<char>(0x81));deep+=static_cast<char>(0xf6);const auto nested=envelope(deep,std::string_view("\xa0",1));
  wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(nested));});
  const auto opaque=envelope(std::string("\x61\xff",2),std::string_view("\xa0",1));static_cast<void>(ar::inspect_descriptor(opaque));
  ar::DescriptorLimits exact;exact.image.bytes=valid.size();exact.image.work=inspected.statistics.work;exact.cbor_items=2;exact.cbor_depth=0;
  static_cast<void>(ar::inspect_descriptor(valid,exact));
  for(unsigned i=0;i<4;++i){auto low=exact;if(i==0)--low.image.bytes;if(i==1)--low.image.work;if(i==2)--low.cbor_items;if(i==3)low.cbor_depth=257;
    wire_rejected([&]{static_cast<void>(ar::inspect_descriptor(valid,low));});}
}
void genuine_round_trip(bool indexed,bool opaque) {
  const auto original=bind(opaque);auto physical=indexed?s04_runtime::options():PhysicalOptions{};
  // Finite host replay admits original unlimited producer compile policies.
  physical.limits.work_limit.reset();physical.limits.identity.work_limit.reset();
  const auto account=resource::MemoryAccount::create(memory);auto admitted=ar::admit_into(account,original,tree(original),physical,normal());
  const auto receiver=resource::MemoryAccount::create(memory);auto restored=ar::rebind_into(receiver,admitted.descriptor.bytes());
  assert(restored.descriptor.bytes()==admitted.descriptor.bytes());assert(restored.descriptor.program().binding_image()==original.binding_image());
  assert(restored.descriptor.native_binding()==admitted.descriptor.native_binding());assert(restored.descriptor.native_program().account().statistics().owner==receiver.statistics().owner);
  assert(restored.descriptor.options().count_limit==10 && restored.descriptor.options().source.native.multiplicity_limit==30 &&
      restored.descriptor.options().source.source_work_limit==normal().source.source_work_limit && restored.descriptor.options().group_work_limit==200000);
  assert(!restored.descriptor.native_program().options().limits.work_limit && !restored.descriptor.native_program().options().limits.identity.work_limit);
  const std::array<Cell,4> row{number(3),{},number(5),storage::ScalarView{true}};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
  const auto a=admitted.runtime.prepare_batch({1,edits}).commit(),b=restored.runtime.prepare_batch({1,edits}).commit();
  assert(a.output.size()==1 && b.output.size()==1 && a.output[0].key==b.output[0].key && a.output[0].after==b.output[0].after);
  const auto frame=ar::encode(receiver,original,1,ar::GroupEpochView{7,1,1,restored.descriptor.sha256(),b.changed,b.group_changed,b.output});
  static_cast<void>(ar::inspect(original,frame.bytes()));
  auto metadata=restored.descriptor;restored=ar::rebind_into(receiver,metadata.bytes());assert(restored.runtime.sequence()==0);
  ar::AdmissionLimits exact;exact.descriptor.image.work=restored.statistics.work;
  {auto pass=ar::rebind_into(receiver,metadata.bytes(),exact);assert(pass.statistics.work==restored.statistics.work);}
  const auto baseline=receiver.statistics().current;--exact.descriptor.image.work;
  refused([&]{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);});assert(receiver.statistics().current==baseline);
  exact={};exact.lowering.work_limit=0;refused([&]{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);});
  exact={};exact.binding.work_limit.reset();refused([&]{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);});
  // Each finite receiving binder grant can refuse valid bytes without corruption.
  for(unsigned phase=0;phase<4;++phase) {
    exact={};
    if(phase==0)exact.binding.work_limit=0;
    else if(phase==1)exact.binding.source.work_limit=0;
    else if(phase==2)exact.binding.source.binding.limits.work_limit=0;
    else exact.binding.kernel.limits.work_limit=0;
    bool work_refused=false;
    try{auto denied=ar::rebind_into(receiver,metadata.bytes(),exact);}
    catch(const recovery::ImageFailure& error){work_refused=error.fault()==recovery::ImageFault::work;}
    assert(work_refused && receiver.statistics().current==baseline);
  }
  auto stored=ar::inspect_descriptor(metadata.bytes());const auto binding=stored.binding_image;
  auto recipe=Json::from_cbor(stored.recipe.begin(),stored.recipe.end());
  for(const auto* key:{"schema_version","records","arithmetic","output","physical_sha256","source_sha256","weighted_shape_sha256","weighted_sha256","multiplicity_limit"}) {
    auto changed=recipe;changed[key]=changed[key].is_string()?Json("forged"):Json(999);
    const auto hostile=envelope(binding,bytes(Json::to_cbor(changed)));const auto before=receiver.statistics().current;
    refused([&]{auto value=ar::rebind_into(receiver,hostile);});assert(receiver.statistics().current==before);
  }
  auto changed_binding=Json::from_cbor(binding.begin(),binding.end());changed_binding["decode"]["encoding"]="forged";
  const auto hostile=envelope(bytes(Json::to_cbor(changed_binding)),stored.recipe);
  refused([&]{auto value=ar::rebind_into(receiver,hostile);});
  auto no_capture=normal();no_capture.capture_changes=false;
  refused([&]{auto value=ar::admit_into(receiver,original,tree(original),physical,no_capture);});
  account.check_invariants();receiver.check_invariants();
}
void receiving_caps() {
  const auto original=bind();const auto producer=resource::MemoryAccount::create(memory);
  const auto admitted=ar::admit_into(producer,original,tree(original),{},normal());std::uint64_t peak=0;
  {auto trial=resource::MemoryAccount::create(memory);{auto value=ar::rebind_into(trial,admitted.descriptor.bytes());peak=trial.statistics().peak_requested_bytes;}
    assert(trial.statistics().current.allocations==1);}
  {auto exact=resource::MemoryAccount::create(peak);auto value=ar::rebind_into(exact,admitted.descriptor.bytes());assert(exact.statistics().peak_requested_bytes==peak);}
  {auto low=resource::MemoryAccount::create(peak-1);bool failed=false;
    try{auto value=ar::rebind_into(low,admitted.descriptor.bytes());}catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
    assert(failed && low.statistics().current.allocations==1);low.check_invariants();}
}
} // namespace
int main(int argc,char** argv) {
  assert(argc==2);cbor_and_frame(argv[1]);
  for(const bool indexed:{false,true})for(const bool opaque:{false,true})genuine_round_trip(indexed,opaque);
  receiving_caps();std::cout<<"R2 genuine descriptor/binding/native/options; opaque metadata; finite host/unlimited producer; nullable next epoch; hostile CBOR/checksums/caps passed\n";
}
