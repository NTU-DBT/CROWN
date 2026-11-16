#include "crown/runtime/physical.hpp"
#include "crown/planner/lower.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace {
using namespace crown;
std::uint64_t checks=0;
void check(bool condition,const char* message) {
  if(!condition)throw std::runtime_error(message);
  ++checks;
}
template<class F> void refusal(F action,std::string_view code={}) {
  bool failed=false;
  try{action();}
  catch(const Error& e){failed=true;check(code.empty()||e.code()==code,"unexpected Error category");}
  catch(const storage::IndexFailure& e){failed=true;check(code.empty()||e.code()==code,"unexpected index category");}
  catch(const resource::MemoryFailure&){failed=true;check(code.empty(),"unexpected memory failure");}
  check(failed,"capture did not refuse");
}
Catalog catalog() {
  return {1,{{"rows",{{"id",ScalarType::int64},{"text",ScalarType::string}}},
      {"unused",{{"id",ScalarType::int64}}}}};
}
PhysicalPlan plan(bool indexed,std::optional<std::uint64_t> scalar_limit={}) {
  auto options=indexed?s04_runtime::options():PhysicalOptions{};
  if(scalar_limit)options.indexed_storage->per_operation.scalar_bytes=*scalar_limit;
  return planner::lower_tree(catalog(),Query{},FreeConnexTree{},options);
}
Row row(std::int64_t id,std::string text=std::string("a\0b",3)) {return {Value{id},Value{std::move(text)}};}
Relation exported(const runtime::physical::SourceImage& image,std::size_t table=0) {
  Relation out;for(const auto& tuple:image.tables.at(table))out.insert(storage::export_row(tuple.values()));return out;
}
void same_account(const runtime::physical::SourceImage& image) {
  const auto id=image.program.account().statistics().owner;
  check(image.tables.get_allocator().account().statistics().owner==id,"image directory has foreign account");
  for(const auto& table:image.tables) {
    check(table.get_allocator().account().statistics().owner==id,"image rows have foreign account");
    for(const auto& tuple:table)check(tuple.layout().account_statistics().owner==id,"image tuple has foreign account");
  }
}
void epochs(bool indexed) {
  runtime::PhysicalRuntime owner(plan(indexed));
  auto empty=owner.source_image();check(empty.sequence==0&&empty.tables.size()==2,"empty capture metadata differs");
  check(empty.tables[0].empty()&&empty.tables[1].empty(),"empty capture has rows");same_account(empty);
  (void)owner.apply({1,TableId{0},SetOperation::insert,row(7)});
  auto pending=owner.prepare({2,TableId{0},SetOperation::insert,row(8,"new")});
  refusal([&]{(void)owner.source_image();},"runtime_busy");
  refusal([&]{(void)pending.source_image({65536,0});},"source_image_work_limit");
  check(pending.active(),"image-work failure closed pending token");
  refusal([&]{(void)pending.source_image({1,1000000});},"source_image_row_limit");
  check(pending.active(),"image-row failure closed pending token");
  auto after=pending.source_image();check(after.sequence==2&&exported(after)==Relation{row(7),row(8,"new")},"pending after-image differs");
  same_account(after);pending.rollback();
  check(owner.ready()&&owner.sequence()==1,"rollback advanced source epoch");
  check(exported(owner.source_image())==Relation{row(7)},"rollback changed committed sources");
  check(exported(after)==Relation{row(7),row(8,"new")},"owned after-image changed after rollback");
  auto erase=owner.prepare({2,TableId{0},SetOperation::erase,row(7)});
  auto absent=erase.source_image();check(absent.sequence==2&&absent.tables[0].empty(),"pending deletion image differs");
  (void)erase.commit();
  auto noop=owner.prepare({3,TableId{0},SetOperation::erase,row(7)});
  check(!noop.preview().physical_changed&&noop.source_image().tables[0].empty(),"no-op pending image differs");
  (void)noop.commit();check(owner.sequence()==3,"no-op source epoch did not advance");
  (void)owner.apply({4,TableId{1},SetOperation::insert,{Value{std::int64_t{99}}}});
  auto unused=owner.source_image();check(unused.tables[1].size()==1,"image omitted unused source table");
  refusal([&]{(void)owner.source_image({0,1000000});},"source_image_row_limit");
  check(owner.ready()&&owner.sequence()==4,"committed capture refusal changed owner");
  owner.check_invariants();
}
void indexed_lease() {
  // Each explicit image has a fresh selected grant, but all captures inside
  // one pending update MUST spend the same immutable five-domain index lease.
  runtime::PhysicalRuntime owner(plan(true,8192));const std::string payload(256,'x');
  (void)owner.apply({1,TableId{0},SetOperation::insert,row(1,payload)});
  (void)owner.apply({2,TableId{0},SetOperation::insert,row(2,payload)});
  auto pending=owner.prepare({3,TableId{0},SetOperation::insert,row(3,payload)});
  std::size_t captures=0;bool exhausted=false;
  for(std::size_t i=0;i<100;++i) {
    try{auto image=pending.source_image();check(image.tables[0].size()==3,"repeated after-image differs");++captures;}
    catch(const Error& e){check(e.code()=="storage_work_limit","unexpected lease Error");exhausted=true;break;}
    catch(const storage::IndexFailure& e){check(e.code()=="storage_work_limit","unexpected lease index failure");exhausted=true;break;}
  }
  check(captures>0&&exhausted,"repeated captures replenished original indexed grant");
  check(pending.active(),"native capture exhaustion closed pending token");pending.rollback();
  check(owner.ready()&&owner.sequence()==2&&owner.source_image().tables[0].size()==2,"lease refusal/rollback changed owner");
  std::cout<<"source image shared indexed lease successful captures="<<captures<<'\n';
}
void allocation_cuts(bool indexed,bool unpublished) {
  const auto make=[&]{auto owner=std::make_unique<runtime::PhysicalRuntime>(plan(indexed));
    (void)owner->apply({1,TableId{0},SetOperation::insert,row(1)});return owner;};
  std::size_t allocations=0;
  {auto owner=make();
    if(unpublished){auto pending=owner->prepare({2,TableId{0},SetOperation::insert,row(2)});s04_alloc::Scope count;auto image=pending.source_image();allocations=s04_alloc::calls;(void)image;}
    else{s04_alloc::Scope count;auto image=owner->source_image();allocations=s04_alloc::calls;(void)image;}}
  check(allocations>0,"capture control observed no allocations");
  for(std::size_t cut=0;cut<allocations;++cut) {
    auto owner=make();bool failed=false,triggered=false;
    if(unpublished) {
      auto pending=owner->prepare({2,TableId{0},SetOperation::insert,row(2)});
      {s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(cut));try{(void)pending.source_image();}catch(...){failed=true;}triggered=s04_alloc::triggered;}
      check(failed&&triggered&&pending.active(),"pending capture allocation denial was not preserved");
      auto retry=pending.source_image();check(retry.tables[0].size()==2,"same-token capture retry differs");pending.rollback();
    } else {
      {s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(cut));try{(void)owner->source_image();}catch(...){failed=true;}triggered=s04_alloc::triggered;}
      check(failed&&triggered,"committed capture allocation denial was not authenticated");
    }
    check(owner->ready()&&owner->sequence()==1&&exported(owner->source_image())==Relation{row(1)},"capture failure changed committed source");
  }
  std::cout<<"source image allocation cuts indexed="<<indexed<<" pending="<<unpublished<<" count="<<allocations<<'\n';
}
void lifetime() {
  auto image=[]{runtime::PhysicalRuntime owner(plan(false));(void)owner.apply({1,TableId{0},SetOperation::insert,row(9,"owned")});return owner.source_image();}();
  check(exported(image)==Relation{row(9,"owned")},"image payload did not survive runtime teardown");same_account(image);
}
} // namespace
static_assert(std::is_nothrow_move_constructible_v<runtime::physical::SourceImage>);
int main() {
  try{lifetime();for(bool indexed:{false,true}){epochs(indexed);allocation_cuts(indexed,false);allocation_cuts(indexed,true);}indexed_lease();
    std::cout<<"accounted physical source images, private after-state, original lease and refusal checks="<<checks<<'\n';return 0;}
  catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
