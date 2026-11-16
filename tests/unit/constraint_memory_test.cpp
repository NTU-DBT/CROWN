#include "constraint_validation.hpp"
#include "crown/catalog/catalog.hpp"
#include "crown/runtime/physical.hpp"
#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool value,std::string_view message) {
  if(!value)throw std::runtime_error(std::string(message));
}
PhysicalRuntimeOptions options(std::uint64_t cap=64*1024*1024) {
  PhysicalRuntimeOptions value;value.support.memory_limit_bytes=cap;return value;
}
Catalog schema(bool trusted=true) {
  const auto status=trusted?ConstraintStatus::enforced:ConstraintStatus::untrusted;
  Catalog catalog{1,{{"source",{{"id",ScalarType::int64},{"key",ScalarType::string},
      {"day",ScalarType::date},{"flag",ScalarType::boolean},{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}}}},
      {"target",{{"key",ScalarType::string},{"day",ScalarType::date}}},
      {"unused",{{"id",ScalarType::int64},{"payload",ScalarType::string}}}}};
  catalog.tables[0].constraints={UniqueConstraint{"pk",{ColumnId{0}},status},
      UniqueConstraint{"all_scalars",{ColumnId{1},ColumnId{2},ColumnId{3},ColumnId{4}},status},
      ForeignKeyConstraint{"fk",{ColumnId{1},ColumnId{2}},TableId{1},{ColumnId{0},ColumnId{1}},status}};
  catalog.tables[1].constraints={UniqueConstraint{"target_key",{ColumnId{0},ColumnId{1}},status}};
  catalog.tables[2].constraints={UniqueConstraint{"hint",{ColumnId{0}},ConstraintStatus::untrusted}};
  return catalog;
}
PhysicalPlan plan(bool indexed,const Catalog& catalog) {
  return planner::lower_tree(catalog,Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():PhysicalOptions{});
}
Database database(std::size_t rows=13) {
  Database data;data.tables.resize(3);
  for(std::size_t i=0;i<rows;++i) {
    const auto key=std::to_string(i)+std::string("\0key",4)+std::string(8192,'k');const auto day=Date::parse("2026-11-09");
    data.tables[0].insert({static_cast<std::int64_t>(i),key,day,i%2!=0,
        Decimal::parse("123456789012345678901234567890123456.12")});
    data.tables[1].insert({key,day});
  }
  return data;
}
resource::MemoryAccount memory(const PhysicalRuntime& runtime) {
  return RuntimeTestProbe::memory_account(RuntimeTestProbe::support(const_cast<PhysicalRuntime&>(runtime)));
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto current=account.statistics().current;
  check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "validation/rebuild scratch survived final owner release");
}
template<class F>void denied(F&& action) {
  try{action();}catch(const resource::MemoryFailure& failure) {
    check(failure.fault()==resource::MemoryFault::limit,"unexpected native validation byte fault");return;
  }
  throw std::runtime_error("expected original-account validation/rebuild denial");
}
template<class F>auto diagnostic(F&& action) {
  try{action();return std::pair<std::string,std::string>{};}
  catch(const Error& error){return std::pair{error.code(),std::string(error.what())};}
}
void semantic_and_allocation_parity(bool indexed) {
  for(const bool trusted:{false,true}) {
    const auto catalog=schema(trusted);PhysicalRuntime runtime(plan(indexed,catalog),options());
    const auto account=memory(runtime);const auto valid=database(3);
    for(int scenario=0;scenario<7;++scenario) {
      auto input=valid;
      if(scenario==1)input.tables.pop_back();
      if(scenario>=2) {
        auto row=*input.tables[0].begin();
        if(scenario==2){input.tables[0].erase(input.tables[0].begin());row.pop_back();}
        if(scenario==3){input.tables[0].erase(input.tables[0].begin());row[2]=std::int64_t{7};}
        if(scenario==4){input.tables[0].erase(input.tables[0].begin());row[4]=Decimal::parse("0.001");}
        if(scenario==5)row[3]=!std::get<bool>(row[3]);
        if(scenario==6){input.tables[0].erase(input.tables[0].begin());row[1]=std::string("missing");}
        input.tables[0].insert(std::move(row));
      }
      const auto expected=diagnostic([&]{validate_database(catalog,input);});
      const auto before=account.statistics().current;
      const auto actual=diagnostic([&]{detail::validate_native_database(runtime.plan().source_catalog(),input,account,{});});
      check(actual==expected,"native validation changed reference error code/message/order or trust semantics");
      check(account.statistics().current==before,"native validation left projection/key scratch after success or rejection");
    }
    const auto before=account.statistics();std::size_t calls=0;
    {s04_alloc::Scope count;detail::validate_native_database(runtime.plan().source_catalog(),valid,account,{});calls=s04_alloc::calls;}
    const auto after=account.statistics();
    check(calls==after.successful_allocations-before.successful_allocations && after.current==before.current,
        "native validation allocated an ordinary Row/string/catalog/key mirror");
    if(trusted)check(calls>0,"enforced key scratch was not exercised");
  }
  Catalog empty{1,{{"target",{{"x",ScalarType::int64}}},{"source",{{"x",ScalarType::int64}}}}};
  empty.tables[0].constraints={UniqueConstraint{"unit",{},ConstraintStatus::enforced}};
  empty.tables[1].constraints={ForeignKeyConstraint{"unit_fk",{},TableId{0},{},ConstraintStatus::enforced}};
  PhysicalRuntime runtime(plan(indexed,empty),options());const auto account=memory(runtime);
  for(int scenario=0;scenario<3;++scenario) {
    Database input;input.tables.resize(2);input.tables[1].insert({std::int64_t{1}});
    if(scenario>=1)input.tables[0].insert({std::int64_t{7}});
    if(scenario==2)input.tables[0].insert({std::int64_t{8}});
    check(diagnostic([&]{validate_database(empty,input);})==diagnostic([&]{
      detail::validate_native_database(runtime.plan().source_catalog(),input,account,{});}),
      "native zero-column uniqueness/FK semantics differ from the reference");
  }
}
void validator_limits(bool indexed) {
  const auto catalog=schema();const auto compiled=plan(indexed,catalog);const auto input=database();std::uint64_t peak=0;
  {
    PhysicalRuntime runtime(compiled,options());const auto account=memory(runtime);
    const auto setup=account.statistics().peak_requested_bytes;
    detail::validate_native_database(runtime.plan().source_catalog(),input,account,{});peak=account.statistics().peak_requested_bytes;
    check(peak>setup,"constraint fixture did not exceed construction peak");
  }
  {
    PhysicalRuntime runtime(compiled,options(peak));const auto account=memory(runtime);const auto before=account.statistics().current;
    detail::validate_native_database(runtime.plan().source_catalog(),input,account,{});
    check(account.statistics().peak_requested_bytes==peak && account.statistics().current==before,"exact native validator budget changed");
  }
  resource::MemoryAccount account;
  {
    PhysicalRuntime runtime(compiled,options(peak-1));account=memory(runtime);const auto before=account.statistics().current;
    denied([&]{detail::validate_native_database(runtime.plan().source_catalog(),input,account,{});});
    check(account.statistics().current==before && runtime.sequence()==0,"one-byte validation rejection leaked or changed runtime state");
    detail::validate_native_database(runtime.plan().source_catalog(),database(1),account,{});
    check(account.statistics().limit_bytes==peak-1,"validation retry replaced its original allowance");
  }
  controller_only(account);
  std::cout<<(indexed?"indexed":"reference")<<" native constraint scratch exact/one-under peak="<<peak<<'\n';
}
void update_and_rebuild(bool indexed) {
  const auto compiled=plan(indexed,schema());const auto input=database();
  std::uint64_t update_peak=0,rebuild_peak=0;
  const Row extra{std::int64_t{9},std::string(12000,'u')};
  // Caller input construction is outside the engine's allocation boundary.
  const PhysicalSetUpdate update{1,TableId{2},SetOperation::insert,extra};
  {
    auto runtime=PhysicalRuntime::initialize(compiled,input,options());const auto account=memory(runtime);
    const auto before=account.statistics().successful_allocations;std::size_t calls=0;
    {s04_alloc::Scope count;auto epoch=runtime.apply(update);calls=s04_alloc::calls;}
    check(calls==account.statistics().successful_allocations-before,
        "actual constrained update retained unaccounted operational row/key scratch");
    update_peak=account.statistics().peak_requested_bytes;
  }
  {
    auto runtime=PhysicalRuntime::initialize(compiled,input,options(update_peak));
    {auto epoch=runtime.apply({1,TableId{2},SetOperation::insert,extra});}
    check(runtime.accounted_memory_statistics().peak_requested_bytes==update_peak,"exact constrained update budget changed");
  }
  {
    auto runtime=PhysicalRuntime::initialize(compiled,input,options(update_peak-1));const auto before=runtime.canonical_state();
    denied([&]{auto epoch=runtime.apply({1,TableId{2},SetOperation::insert,extra});});
    check(runtime.ready() && runtime.canonical_state()==before,"constrained update byte denial changed its prior epoch");
    {auto retry=runtime.apply({1,TableId{2},SetOperation::erase,extra});check(!retry.input.physical_changed,"smaller same-sequence update retry failed");}
  }
  {
    auto runtime=PhysicalRuntime::initialize(compiled,input,options());const auto account=memory(runtime);
    auto scalar_row=*input.tables[0].begin();scalar_row[0]=std::int64_t{777};scalar_row[3]=!std::get<bool>(scalar_row[3]);
    const PhysicalSetUpdate scalar_update{1,TableId{0},SetOperation::insert,std::move(scalar_row)};
    const auto before=account.statistics().successful_allocations;std::size_t calls=0;
    {s04_alloc::Scope count;auto epoch=runtime.apply(scalar_update);calls=s04_alloc::calls;}
    check(calls==account.statistics().successful_allocations-before,
        "actual five-scalar/38-digit decimal row validation allocated unaccounted formatting scratch");
  }
  for(const auto method:{BuildMethod::direct,BuildMethod::insertion_replay}) {
    BuildOptions build;build.method=method;
    {
      auto runtime=PhysicalRuntime::initialize(compiled,input,options(),build);const auto account=memory(runtime);
      auto rebuilt=runtime.rebuilt(build);rebuild_peak=account.statistics().peak_requested_bytes;
      check(rebuilt.snapshot().physical.tables==input.tables && rebuilt.sequence()==runtime.sequence() &&
          rebuilt.accounted_memory_statistics().owner==account.statistics().owner,"native rebuild changed rows, sequence or account");
    }
    {
      auto runtime=PhysicalRuntime::initialize(compiled,input,options(rebuild_peak),build);auto rebuilt=runtime.rebuilt(build);
      check(runtime.accounted_memory_statistics().peak_requested_bytes==rebuild_peak,"exact native rebuild budget changed");
    }
    resource::MemoryAccount account;
    {
      auto runtime=PhysicalRuntime::initialize(compiled,input,options(rebuild_peak-1),build);account=memory(runtime);
      const auto before=runtime.canonical_state();const auto usage=account.statistics().current;
      denied([&]{auto rebuilt=runtime.rebuilt(build);});
      check(runtime.ready() && runtime.canonical_state()==before && account.statistics().current==usage,
          "native rebuild byte denial leaked scratch/new state or changed the old runtime");
    }
    controller_only(account);
  }
  std::cout<<(indexed?"indexed":"reference")<<" constrained update peak="<<update_peak<<"; replay rebuild overlap peak="<<rebuild_peak<<'\n';
}
void persistent_failures(bool indexed) {
  const auto compiled=plan(indexed,schema());const auto input=database(2);const Row row{std::int64_t{1},std::string(8192,'f')};
  const PhysicalSetUpdate update{1,TableId{2},SetOperation::insert,row};
  for(const bool rebuild:{false,true}) {
    std::size_t failures=0;bool complete=false;
    for(std::ptrdiff_t point=0;point<2048;++point) {
      auto runtime=PhysicalRuntime::initialize(compiled,input,options());const auto account=memory(runtime);
      const auto before=runtime.canonical_state();const auto usage=account.statistics().current;bool failed=false;
      {s04_alloc::Scope fault(point);try {
        if(rebuild){auto fresh=runtime.rebuilt();}
        else {auto epoch=runtime.apply(update);}
      }catch(const std::bad_alloc&){failed=true;}}
      if(failed) {
        ++failures;check(runtime.ready() && runtime.canonical_state()==before,"native scratch allocation failure changed the old epoch");
        if(rebuild)check(account.statistics().current==usage,"failed rebuild retained native scratch or partial target ownership");
        if(rebuild){auto retry=runtime.rebuilt();check(retry.sequence()==0,"same-state rebuild retry failed");}
        else {auto retry=runtime.apply({1,TableId{2},SetOperation::insert,row});check(runtime.sequence()==1,"same-input constraint retry failed");}
      }else complete=true;
      account.check_invariants();if(complete)break;
    }
    check(complete && failures>0,"native validation/rebuild persistent failure sweep was incomplete");
    std::cout<<(indexed?"indexed":"reference")<<(rebuild?" native rebuild":" native constrained update")<<" persistent faults="<<failures<<'\n';
  }
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      semantic_and_allocation_parity(indexed);validator_limits(indexed);update_and_rebuild(indexed);persistent_failures(indexed);
    }
    std::cout<<"native constraint validation and rebuild scratch: semantics, real budgets, no mirrors and failure recovery passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
