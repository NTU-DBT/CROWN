#include "crown/storage/accounted_layout.hpp"
#include "crown/storage/accounted_projection.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/io/document.hpp"
#include "indexed_runtime_fixture.hpp"
#include "runtime_probe.hpp"
#include "index_allocation.hpp"

#include <array>
#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::storage;
using namespace crown::runtime;
namespace {
void check(bool value,std::string_view message) {
  if(!value)throw std::runtime_error(std::string(message));
}
resource::MemoryAccount unlimited(){return resource::MemoryAccount::create(UINT64_MAX);}
constexpr resource::MemoryAttribution output{resource::MemoryOwnerKind::output,9};
TupleLayout source_layout() {
  return {LayoutId{3},{{ScalarType::int64},{ScalarType::string,{},VariableId{0}},
      {ScalarType::boolean},{ScalarType::date},{ScalarType::decimal,DecimalSpec{38,0}},
      {ScalarType::string,{},VariableId{0}}},{7,std::string("layout\0binding",14)}};
}
Row scalars(std::size_t length=4096) {
  const auto text=std::string("left\0right",10)+std::string(length,'v');
  return {std::int64_t{-7},text,true,Date::parse("2026-11-09"),
      Decimal::parse("-12345678901234567890123456789012345678"),text};
}
void reconcile(const resource::MemoryAccount& account) {
  account.check_invariants();const auto state=account.statistics();resource::MemoryUsage purposes{},lifetimes{};
  const auto add=[](auto& a,const auto& b){a.allocations+=b.allocations;a.requested_bytes+=b.requested_bytes;a.payload_bytes+=b.payload_bytes;};
  for(const auto& value:state.by_purpose)add(purposes,value);
  for(const auto& value:state.by_lifetime)add(lifetimes,value);
  check(purposes==state.current && lifetimes==state.current,"public tuple allocations do not reconcile");
  check(state.current.requested_bytes<=state.limit_bytes && state.peak_requested_bytes<=state.limit_bytes,
      "public tuple exceeded the original query cap");
}
void controller_only(const resource::MemoryAccount& account) {
  reconcile(account);const auto state=account.statistics();
  check(state.current.allocations==1 && state.current.requested_bytes==resource::MemoryAccount::control_bytes(),
      "public tuple/view retained bytes after final release");
}
template<class F>void denied(F&& operation) {
  try{operation();}catch(const resource::MemoryFailure& failure) {
    check(failure.fault()==resource::MemoryFault::limit,"unexpected public tuple rejection");return;
  }
  throw std::runtime_error("expected actual public tuple byte-limit rejection");
}
void native_views() {
  auto account=unlimited();TupleValuesView retained;
  const auto expected=scalars();const auto expected_hash=row_hash(expected);
  {
    const auto source=source_layout();auto layout=AccountedLayout::freeze(account,source);
    const auto metadata=account.statistics().current;
    auto input=layout.tuple(expected,output);const auto* original=input.values().cells().data();
    auto tuple=Tuple::from_accounted(std::move(input));
    check(tuple.is_accounted() && tuple.account_statistics().owner==account.statistics().owner,
        "public payload was not allocated under its original account");
    check(tuple.values().native_view() && tuple.values().native_view()->cells().data()==original,
        "native/public conversion copied row descriptors or strings");
    check(tuple.layout().same_token(layout) && tuple.values()==expected && tuple.hash()==expected_hash,
        "public values, hash or original layout token changed");
    const auto current=account.statistics().current;const auto usage=tuple.memory_usage();
    check(usage.allocations==current.allocations-metadata.allocations &&
        usage.requested_bytes==current.requested_bytes-metadata.requested_bytes &&
        usage.payload_bytes==current.payload_bytes-metadata.payload_bytes,
        "public tuple usage is not its actual scalar/object/control allocation charge");
    {
      s04_alloc::Scope no_allocation(0);
      auto copy=tuple;copy=tuple;retained=copy.values();
      check(copy==tuple && copy.hash()==expected_hash && retained==expected,"immutable native copy/view changed values");
      check(account.statistics().current==current && s04_alloc::calls==0,
          "native copy, comparison, hash or read-only view allocated or cloned payloads");
    }
    auto descriptor=layout.descriptor();auto through_descriptor=descriptor.tuple(expected);
    check(through_descriptor.is_accounted() && through_descriptor.layout().same_token(tuple.layout()) &&
        through_descriptor.account_statistics().owner==account.statistics().owner,
        "readable native descriptor discarded its account/token when making a public tuple");
    auto through_view=descriptor.tuple_view(tuple.values());
    check(through_view.is_accounted() && through_view.values()==expected,"native descriptor view input changed values");
    const std::array fields{layout.fields()[1],layout.fields()[4],layout.fields()[5]};
    auto target=AccountedLayout::make(account,LayoutId{4},fields,layout.context());
    const std::array mapping{FieldId{1},FieldId{4},FieldId{5}};
    auto projection=AccountedProjection::freeze(layout,target,mapping).descriptor();
    const auto before_projection=account.statistics().successful_allocations;
    std::optional<Tuple> projected;std::size_t upstream_calls=0;
    {s04_alloc::Scope count_allocations;projected=projection.apply(tuple);upstream_calls=s04_alloc::calls;}
    const auto native_calls=account.statistics().successful_allocations-before_projection;
    check(upstream_calls==native_calls && native_calls>=2,
        "native public projection created an unaccounted legacy row/string scratch mirror");
    check(projected->is_accounted() && projected->layout().same_token(target) &&
        projected->values()==Row{expected[1],expected[4],expected[5]},"native public projection changed values or target token");
    for(std::size_t i=0;i<expected.size();++i)check(io::write_scalar_view(retained[i])==io::write_scalar(expected[i]),
        "public scalar view changed the exact external JSON encoding");
  }
  check(retained==expected,"read-only values did not survive source/layout/tuple destruction");
  check(account.statistics().current.requested_bytes>resource::MemoryAccount::control_bytes(),
      "retained value view was not charged after tuple destruction");
  {s04_alloc::Scope no_allocation(0);retained={};check(s04_alloc::calls==0,"final public value view cleanup allocated");}
  controller_only(account);
}
void limits_and_failures() {
  const auto source=source_layout();const auto expected=scalars();std::uint64_t peak=0;
  {
    auto account=unlimited();auto layout=AccountedLayout::freeze(account,source);
    auto tuple=layout.descriptor().tuple(expected);peak=account.statistics().peak_requested_bytes;
    check(tuple.is_accounted(),"native descriptor payload was unaccounted");
  }
  {
    auto account=resource::MemoryAccount::create(peak);
    {auto layout=AccountedLayout::freeze(account,source);auto tuple=layout.descriptor().tuple(expected);
      check(tuple.values()==expected && account.statistics().peak_requested_bytes==peak,"exact public tuple cap was not admitted");}
    controller_only(account);
  }
  {
    auto account=resource::MemoryAccount::create(peak-1);
    {
      auto layout=AccountedLayout::freeze(account,source);const auto before=account.statistics().current;
      denied([&]{static_cast<void>(layout.descriptor().tuple(expected));});
      check(account.statistics().current==before,"one-byte public tuple denial leaked scalar/shared owner bytes");
      auto retry=layout.descriptor().tuple(scalars(1));
      check(retry.values()==scalars(1) && retry.account_statistics().limit_bytes==peak-1,
          "smaller public tuple retry failed or minted another memory grant");
    }
    controller_only(account);
  }
  std::size_t failures=0;bool finished=false;
  for(std::ptrdiff_t fail=0;fail<32;++fail) {
    auto account=unlimited();
    {
      auto layout=AccountedLayout::freeze(account,source);const auto before=account.statistics().current;
      bool failed=false;
      {s04_alloc::Scope fault(fail);try{static_cast<void>(layout.descriptor().tuple(expected));}catch(const std::bad_alloc&){failed=true;}}
      if(failed) {
        ++failures;check(account.statistics().current==before,"persistent public tuple allocation failure leaked retained bytes");
        auto retry=layout.descriptor().tuple(expected);check(retry.values()==expected,"same-input public tuple retry failed");
      }else finished=true;
      reconcile(account);
    }
    controller_only(account);if(finished)break;
  }
  check(finished && failures>=2,"public tuple scalar and shared-control allocation faults were not exercised");
  std::cout<<"public native tuple exact/one-under peak="<<peak<<"; persistent faults="<<failures<<'\n';
}
PhysicalPlan query(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::string},{"y",ScalarType::int64}}},{"s",{{"y",ScalarType::int64}}}}};
  const Query query{{{"x",ScalarType::string},{"y",ScalarType::int64}},
      {{"r",TableId{0},{VariableId{0},VariableId{1}}},{"s",TableId{1},{VariableId{1}}}},
      {{VariableId{0},"x"},{VariableId{1},"y"}},false};
  const FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1}},{NodeId{1}},0,{}},
      {"s",NodeKind::native,{VariableId{1}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
Row parent(){return {std::string("binary\0value",12)+std::string(16384,'r'),std::int64_t{42}};}
Row child(){return {std::int64_t{42}};}
DeltaOptions options(std::uint64_t cap=UINT64_MAX) {
  DeltaOptions options;options.physical.support.memory_limit_bytes=cap;return options;
}
resource::MemoryAccount memory(DeltaRuntime& runtime) {
  return RuntimeTestProbe::memory_account(RuntimeTestProbe::support(RuntimeTestProbe::physical(runtime)));
}
void output_transfer(bool indexed) {
  resource::MemoryAccount account;TupleValuesView held;
  {
    DeltaRuntime runtime(query(indexed),options());account=memory(runtime);
    {auto first=runtime.apply({1,TableId{0},SetOperation::insert,parent()});first.discard();}
    auto pending=runtime.begin({2,TableId{1},SetOperation::insert,child()});pending.drain();
    std::optional<DeltaRuntime::Epoch> epoch;std::optional<SignedResult> record;
    {
      s04_alloc::Scope no_allocation(0);epoch.emplace(pending.commit());
      const auto before=account.statistics().current;
      record=epoch->next();const auto after=account.statistics().current;
      check(record && record->tuple.is_accounted(),"committed public output has no native payload owner");
      const auto node_bytes=before.requested_bytes-after.requested_bytes;
      check(before.allocations==after.allocations+1 &&
          epoch->metrics().spool_bytes==node_bytes+record->tuple.memory_usage().requested_bytes,
          "spool bytes do not reconcile with the actual node release and retained output payload");
      held=record->tuple.values();check(s04_alloc::calls==0,"prepared commit, public output transfer or view allocated");
    }
    check(record->tuple.values()==parent() && held==parent() && !epoch->active(),"public output values or lease release changed");
    record.reset();epoch.reset();reconcile(account);
  }
  check(held==parent(),"public output values did not survive the query facade");
  {s04_alloc::Scope no_allocation(0);held={};check(s04_alloc::calls==0,"post-facade output release allocated");}
  controller_only(account);
}
void retained_output_cap(bool indexed) {
  const auto compiled=query(indexed);std::uint64_t peak=0;
  {
    DeltaRuntime runtime(compiled,options());
    {auto epoch=runtime.apply({1,TableId{0},SetOperation::insert,parent()});epoch.discard();}
    {auto epoch=runtime.apply({2,TableId{1},SetOperation::insert,child()});epoch.discard();}
    {auto epoch=runtime.apply({3,TableId{1},SetOperation::erase,child()});epoch.discard();}
    peak=runtime.accounted_memory_statistics().peak_requested_bytes;
  }
  resource::MemoryAccount account;
  {
    DeltaRuntime runtime(compiled,options(peak));account=memory(runtime);
    {auto epoch=runtime.apply({1,TableId{0},SetOperation::insert,parent()});epoch.discard();}
    TupleValuesView retained;
    {auto epoch=runtime.apply({2,TableId{1},SetOperation::insert,child()});auto record=epoch.next();
      check(bool(record),"retained output fixture produced no row");retained=record->tuple.values();}
    const auto before=runtime.canonical_state();
    denied([&]{auto epoch=runtime.apply({3,TableId{1},SetOperation::erase,child()});epoch.discard();});
    check(runtime.ready() && runtime.canonical_state()==before && retained==parent(),
        "retained output byte denial damaged the query or existing caller values");
    {s04_alloc::Scope no_allocation(0);retained={};check(s04_alloc::calls==0,"retained output release allocated");}
    {auto retry=runtime.apply({3,TableId{1},SetOperation::erase,child()});check(retry.remaining()==1,"same-sequence retry lost deletion output");retry.discard();}
    check(runtime.sequence()==3 && account.statistics().owner==runtime.accounted_memory_statistics().owner,
        "retained output retry replaced the original query account");reconcile(account);
  }
  controller_only(account);
  std::cout<<(indexed?"indexed":"reference")<<" caller-retained native output charges original crossing peak="<<peak<<'\n';
}
} // namespace
int main() {
  try {
    native_views();limits_and_failures();
    for(const bool indexed:{false,true}){output_transfer(indexed);retained_output_cap(indexed);}
    std::cout<<"public native tuples: exact payload/control bytes, immutable views, limits, faults, transfer and retained ownership passed\n";
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
