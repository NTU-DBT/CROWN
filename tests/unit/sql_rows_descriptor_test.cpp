#include "crown/recovery/sql_rows_descriptor.hpp"
#include "crown/ir/digest.hpp"
#include "crown/io/document.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace {
using namespace crown;
namespace rr = recovery::sql_rows;
using Json=io::Json;
using Cell=runtime::sql_rows::Cell;
constexpr std::uint64_t memory=64ULL*1024*1024;
Catalog schema() {
  Catalog value{1,{{"r",{{"id",ScalarType::int64},{"g",ScalarType::string,true},{"flag",ScalarType::boolean}}},
      {"unused",{{"x",ScalarType::int64}}}}};
  value.tables[0].key_hints.push_back({{ColumnId{0}},std::string(1,static_cast<char>(0xff))});return value;
}
frontend::SqlRowsProgram bind(bool retain=true) {
  frontend::SqlRowsBindOptions options;options.retain_binding_image=retain;
  options.binding.parameters={{"threshold",ScalarType::int64},{"label",ScalarType::string,true}};
  options.parameters={Value{std::int64_t{2}},Value{std::string("kept")}};
  auto result=frontend::bind_sql_rows("SELECT id,g,$2::text AS label FROM r WHERE id>$1 AND flag",schema(),options);
  assert(std::holds_alternative<frontend::SqlRowsProgram>(result));return std::get<frontend::SqlRowsProgram>(std::move(result));
}
FreeConnexTree tree(const frontend::SqlRowsProgram& program) {
  const auto core=program.export_core();const auto chosen=planner::minimum_tree(core.catalog,core.query);
  assert(chosen.tree && chosen.certificate_verified);return *chosen.tree;
}
void integer(std::string& out,std::uint64_t value) {for(unsigned i=0;i<8;++i)out.push_back(static_cast<char>(value>>(8*i)));}
std::string bytes(const std::vector<std::uint8_t>& value) {return {reinterpret_cast<const char*>(value.data()),value.size()};}
// Independent protected framing supports checksum-valid semantic/CBOR forgeries.
std::string envelope(std::string_view binding,std::string_view recipe) {
  std::string body;integer(body,binding.size());body+=binding;integer(body,recipe.size());body+=recipe;
  std::string result("CROWNRD2\x01\x00\x00\x00",12);integer(result,body.size());
  const auto hash=sha256_fixed(body);result.append(hash.data(),hash.size());
  const auto prefix=sha256_fixed(result);result.append(prefix.data(),prefix.size());return result+body;
}
template<class Action> void rejected(Action action) {
  bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}assert(failed);
}
void cbor_and_frame() {
  const auto valid=envelope(std::string_view("\xa0",1),std::string_view("\xa0",1));
  rr::InspectedDescriptor inspected{};
  {s04_alloc::Scope deny(0);inspected=rr::inspect_descriptor(valid);assert(s04_alloc::calls==0);}
  assert(valid.size()==166 && inspected.sha256==sha256_fixed(valid));
  for(std::size_t size=0;size<valid.size();++size)
    rejected([&]{static_cast<void>(rr::inspect_descriptor(std::string_view(valid).substr(0,size)));});
  for(std::size_t i=0;i<valid.size();++i) {auto bad=valid;bad[i]^=1;rejected([&]{static_cast<void>(rr::inspect_descriptor(bad));});}
  const std::array malformed{std::string("\xbf\xff",2),std::string("\x18\x01",2),std::string("\xc0\x00",2),
      std::string("\xf9\x3c\x00",3),std::string("\xa2\x61\x61\x01\x61\x61\x02",7),
      std::string("\xa2\x61\x62\x01\x61\x61\x02",7),std::string("\xa1\x61\xff\x00",4)};
  for(const auto& bad:malformed)rejected([&]{static_cast<void>(rr::inspect_descriptor(envelope(bad,std::string_view("\xa0",1))));});
  rr::DescriptorLimits exact;exact.image.bytes=valid.size();exact.image.work=inspected.statistics.work;exact.cbor_items=2;exact.cbor_depth=0;
  static_cast<void>(rr::inspect_descriptor(valid,exact));auto low=exact;--low.image.work;
  rejected([&]{static_cast<void>(rr::inspect_descriptor(valid,low));});low=exact;--low.cbor_items;
  rejected([&]{static_cast<void>(rr::inspect_descriptor(valid,low));});
}
void genuine_round_trip(bool indexed) {
  const auto program=bind();auto physical=indexed?s04_runtime::options():PhysicalOptions{};
  physical.limits.work_limit.reset();physical.limits.identity.work_limit.reset();
  runtime::sql_rows::Options normal;normal.native.work_limit.reset();normal.native.multiplicity_limit=30;
  normal.source_work_limit={200000,200000,8ULL*1024*1024,0,0};const runtime::sql_rows::OutputLimits output{15,3000};
  const auto sender=resource::MemoryAccount::create(memory),receiver=resource::MemoryAccount::create(memory);
  auto original=rr::admit_into(sender,program,tree(program),physical,normal,output);
  auto restored=rr::rebind_into(receiver,original.descriptor.bytes());
  assert(restored.descriptor.bytes()==original.descriptor.bytes());
  assert(restored.descriptor.program().binding_image()==program.binding_image() && restored.descriptor.native_binding()==original.descriptor.native_binding());
  assert(restored.descriptor.native_program().account().statistics().owner==receiver.statistics().owner);
  assert(restored.descriptor.output_limits()==output && restored.descriptor.options().native.multiplicity_limit==30 &&
      !restored.descriptor.options().native.work_limit && restored.descriptor.options().source_work_limit==normal.source_work_limit);
  assert(!restored.descriptor.native_program().options().limits.work_limit && !restored.descriptor.native_program().options().limits.identity.work_limit);
  const std::array<Cell,3> row{storage::ScalarView{std::int64_t{3}},Cell{},storage::ScalarView{true}};
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},row,0,2}};
  auto a=original.runtime.prepare_output_batch({1,edits},original.descriptor.output_limits());
  auto b=restored.runtime.prepare_output_batch({1,edits},restored.descriptor.output_limits());
  std::array<Cell,3> left{},right{};const auto x=a.output_change(0,left),y=b.output_change(0,right);
  assert(x.values.size()==3 && y.values.size()==3 && std::equal(x.values.begin(),x.values.end(),y.values.begin()));
  assert(x.change.magnitude.value==2 && y.change.magnitude.value==2 && !x.change.negative && !y.change.negative);
  assert(std::get<std::string_view>(*x.values[2])=="kept");static_cast<void>(a.commit());static_cast<void>(b.commit());
  const auto inspected=rr::inspect_descriptor(original.descriptor.bytes());
  const auto recipe=Json::from_cbor(inspected.recipe.begin(),inspected.recipe.end());
  assert(recipe.at("parser_archive")=="2d3486cf6a9d3955b53e66235db39d62b54216c820cd392ab66dc842c5b1316d" && recipe.at("pg_version")==180006);
  for(const auto key:{"parser_archive","pg_version"}) {
    auto wrong=recipe;
    if(std::string_view(key)=="parser_archive")wrong[key]=std::string(64,'0');
    else wrong[key]=180005;
    const auto hostile=envelope(inspected.binding_image,bytes(Json::to_cbor(wrong)));
    static_cast<void>(rr::inspect_descriptor(hostile));rejected([&]{auto denied=rr::rebind_into(receiver,hostile);});
  }
  rr::AdmissionLimits no_work;no_work.binding.work_limit=0;
  const auto receiving_before=receiver.statistics().current;bool work_refused=false;
  try {auto denied=rr::rebind_into(receiver,original.descriptor.bytes(),no_work);}
  catch(const recovery::ImageFailure& failure) {work_refused=failure.fault()==recovery::ImageFault::work;}
  assert(work_refused && receiver.statistics().current==receiving_before && original.runtime.sequence()==1 && restored.runtime.sequence()==1);
  auto forged=Json::from_cbor(inspected.recipe.begin(),inspected.recipe.end());forged["weighted_sha256"]=std::string(64,'0');
  const auto hostile=envelope(inspected.binding_image,bytes(Json::to_cbor(forged)));
  static_cast<void>(rr::inspect_descriptor(hostile));rejected([&]{auto refused=rr::rebind_into(receiver,hostile);});
  const auto fresh=rr::rebind_into(receiver,original.descriptor.bytes());rr::AdmissionLimits exact;
  exact.descriptor.image.work=fresh.statistics.work;
  {auto allowed=rr::rebind_into(receiver,original.descriptor.bytes(),exact);assert(allowed.statistics.work==fresh.statistics.work);}
  --exact.descriptor.image.work;rejected([&]{auto refused=rr::rebind_into(receiver,original.descriptor.bytes(),exact);});
  // Output policy is part of descriptor identity without changing native shape.
  auto wider=rr::admit_into(sender,program,tree(program),physical,normal,{16,3000});
  assert(wider.descriptor.sha256()!=original.descriptor.sha256() && wider.descriptor.native_binding()==original.descriptor.native_binding());
}
void binding_opt_in() {
  const auto ordinary=bind(false),retained=bind();const auto chosen=tree(ordinary);
  assert(ordinary.binding_image().empty() && !retained.binding_image().empty());
  assert(ordinary.source_sha256()==retained.source_sha256());
  const auto account=resource::MemoryAccount::create(memory);const auto before=account.statistics().current;
  bool denied=false;
  try {auto invalid=rr::admit_into(account,ordinary,chosen,{}, {}, {});}
  catch(const recovery::ImageFailure& error) {denied=error.fault()==recovery::ImageFault::binding;}
  assert(denied && account.statistics().current==before);
}
void receiving_caps() {
  const auto program=bind();const auto chosen=tree(program);std::uint64_t peak=0;
  const auto account=resource::MemoryAccount::create(memory);
  {auto admitted=rr::admit_into(account,program,chosen,{}, {}, {});peak=account.statistics().peak_requested_bytes;}
  assert(account.statistics().current.allocations==1);
  for(const bool exact:{true,false}) {
    const auto receiver=resource::MemoryAccount::create(exact?peak:peak-1);bool failed=false;
    try {auto admitted=rr::admit_into(receiver,program,chosen,{}, {}, {});}
    catch(const resource::MemoryFailure& error) {failed=error.fault()==resource::MemoryFault::limit;}
    assert(failed!=exact && receiver.statistics().current.allocations==1);receiver.check_invariants();
  }
}
} // namespace
int main() {
  try {cbor_and_frame();for(const bool indexed:{false,true})genuine_round_trip(indexed);binding_opt_in();receiving_caps();
    std::cout<<"plain SQL row descriptors: genuine rebind, policy identity and finite receivers\n";
  } catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
