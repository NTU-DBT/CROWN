#include "owner_statistics_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <optional>

using namespace crown;
using namespace crown::runtime;
namespace st=crown::runtime::statistics;
namespace {
constexpr resource::MemoryAttribution capture_owner{resource::MemoryOwnerKind::capture,2};
constexpr std::uint64_t allowance=64*1024*1024;
void check(bool ok,std::string_view message) {if(!ok)throw std::runtime_error(std::string(message));}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto current=account.statistics().current;
  check(current.allocations==1 && current.requested_bytes==resource::MemoryAccount::control_bytes(),"owner capture retained native storage after final release");
}
PhysicalPlan plan(bool indexed) {
  Catalog catalog{1,{{"R",{{"x",ScalarType::int64},{"s",ScalarType::string},{"b",ScalarType::boolean},
      {"d",ScalarType::date},{"n",ScalarType::decimal},{"witness",ScalarType::int64}}},{"S",{{"x",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64},{"s",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4},IgnoredColumn{}}},
       {"s",TableId{1},{VariableId{0}}}},
      {{VariableId{0},"x"},{VariableId{1},"s"},{VariableId{2},"b"},{VariableId{3},"d"},{VariableId{4},"n"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}},
      {NodeId{1}},0,{}},{"s",NodeKind::native,{VariableId{0}},{},1,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
std::string text(std::size_t i,std::size_t width) {
  std::string result(width,'Q');result[0]=static_cast<char>(i*3);result[width/2]='\0';result.back()=static_cast<char>(255);return result;
}
Database database(std::size_t rows,std::size_t width) {
  Database result{{{}, {}}};
  for(std::size_t i=0;i<rows;++i) {
    const auto x=static_cast<std::int64_t>(i);const auto s=text(i,width);
    for(std::int64_t witness=0;witness<2;++witness)
      result.tables[0].insert({x,s,i%2==0,Date::parse("2024-02-29"),Decimal::parse("99999999999999999999999999999999999999"),witness});
    result.tables[1].insert({x});
  }
  return result;
}
PhysicalRuntime runtime(bool indexed,std::uint64_t cap=allowance,std::size_t rows=4,std::size_t width=96) {
  PhysicalRuntimeOptions options;options.support.memory_limit_bytes=cap;options.support.capture_transitions=false;
  return PhysicalRuntime::initialize(plan(indexed),database(rows,width),options);
}
st::Limits limits() {st::Limits result;result.work=8000000;result.heavy_keys=64;return result;}
std::vector<FieldId> fields() {return {{1},{4},{2},{3},{0},{1}};}
st::OwnerRequest request(const CompiledProgram& program,std::size_t repeats=1) {
  st::OwnerRequest result;
  for(std::size_t i=0;i<repeats;++i)result.selections.push_back({st::SourceScope{TableId{0}},fields()});
  result.selections.push_back({st::OccurrenceScope{OccurrenceId{0}},{}});
  result.selections.push_back({st::NodeScope{NodeId{0},SupportRole::records},fields()});
  result.selections.push_back({st::NodeScope{NodeId{0},SupportRole::survivors},fields()});
  result.selections.push_back({st::NodeScope{NodeId{0},SupportRole::parent_support},{}});
  result.selections.push_back({st::NodeScope{NodeId{0},SupportRole::visible},{}});
  for(const auto& index:program.indexes())result.selections.push_back({st::IndexScope{index.id},{}});
  return result;
}
Row first_key(std::size_t width) {
  const auto s=text(0,width);return {s,Decimal::parse("99999999999999999999999999999999999999"),true,Date::parse("2024-02-29"),std::int64_t{0},s};
}
void facts(const st::OwnerCapture& value,std::size_t rows,std::size_t width) {
  check(value.availability()==st::Availability::available && !value.components().empty(),"native owner fixture did not finish");
  const auto& distribution=*value.components().front().distribution;
  check(distribution.completion==st::Completion::exact && distribution.visited==rows*2 && distribution.ndv==rows &&
      distribution.heavy_keys && distribution.heavy_keys->size()==rows && distribution.heavy_keys->front().key==first_key(width) &&
      distribution.heavy_keys->front().count==2,"native heavy key scalar/byte/decimal facts changed");
}
std::uint64_t retained_blocks(const st::OwnerCapture& value) {
  std::uint64_t result=value.components().capacity()?1:0;
  for(const auto& component:value.components()) {
    if(component.selection.fields && component.selection.fields->capacity())++result;
    if(!component.distribution)continue;
    const auto& distribution=*component.distribution;
    if(distribution.histogram.capacity())++result;
    if(distribution.heavy_keys) {
      if(distribution.heavy_keys->capacity())++result;
      for(const auto& heavy:*distribution.heavy_keys)result+=heavy.key.memory_usage().allocations;
    }
  }
  return result;
}
void requests_lifetimes_and_pending(bool indexed) {
  resource::MemoryAccount account;std::optional<st::OwnerCapture> held,copy;
  {
    auto owner=runtime(indexed);account=owner.plan().account();auto wanted=request(owner.plan());
    const auto before=account.statistics();std::size_t calls=0;
    {s04_alloc::Scope count;held.emplace(owner.capture_statistics(wanted,limits()));calls=s04_alloc::calls;}
    const auto after=account.statistics();const auto retained=account.statistics_for(capture_owner).current;
    check(calls>0 && calls==after.successful_allocations-before.successful_allocations &&
        retained.requested_bytes==after.current.requested_bytes-before.current.requested_bytes &&
        retained.allocations==retained_blocks(*held),"owner capture components/fields/group scratch/keys/arrays allocated outside original account");
    facts(*held,4,96);wanted.selections.front().fields->clear();
    check(held->components().front().selection.fields->size()==6,"captured fields borrow the caller request");
    const auto before_copy=account.statistics();
    {s04_alloc::Scope count;copy.emplace(*held);calls=s04_alloc::calls;}
    check(calls==account.statistics().successful_allocations-before_copy.successful_allocations && calls==retained.allocations,
        "owning capture copy hid requests or omitted a deep native block");
    owner_fixture::same_facts(*held,*copy);
    const auto pending_input=PhysicalSetUpdate{1,TableId{1},SetOperation::insert,{std::int64_t{9}}};
    auto pending=owner.prepare(pending_input);
    const auto before_pending=account.statistics();bool denied=false;
    for(std::ptrdiff_t point=0;point<(indexed?2:1);++point) {
      denied=false;
      {s04_alloc::Scope fault(point);try{const auto private_value=owner.capture_statistics(wanted,limits());}
        catch(const std::bad_alloc&){denied=true;}}
      check(denied==indexed && account.statistics().current==before_pending.current && owner.sequence()==0,
          "pending metadata work-grant denial changed the private or accepted state");
    }
    const auto before_read=account.statistics();std::optional<st::OwnerCapture> private_value;
    {s04_alloc::Scope count;private_value=owner.capture_statistics(wanted,limits());calls=s04_alloc::calls;}
    // Indexed reads retain no component graph, but their existing StorageOperation
    // still acquires a temporary original-account work grant: the lease
    // object/control and its AccountedIndexWork object/control are two requests.
    check(calls==(indexed?2U:0U) && calls==account.statistics().successful_allocations-before_read.successful_allocations &&
        account.statistics().current==before_read.current && private_value->availability()==st::Availability::pending_private_state &&
        private_value->components().empty(),"pending metadata hid an ordinary request or exposed private component facts");
    {s04_alloc::Scope none(0);private_value.reset();pending.rollback();}
  }
  facts(*held,4,96);facts(*copy,4,96);
  check(held->plan().account().statistics().owner==account.statistics().owner,"retained capture lost its original query account");
  {s04_alloc::Scope none(0);held.reset();copy.reset();}controller_only(account);
}
void caps(bool indexed,bool copying) {
  std::uint64_t peak=0;
  {
    auto owner=runtime(indexed,allowance,48,1536);const auto account=owner.plan().account();const auto wanted=request(owner.plan(),8);
    const auto held=owner.capture_statistics(wanted,limits());const auto pin=owner.capture_statistics(wanted,limits());
    const auto before=account.statistics().peak_requested_bytes;
    {const auto candidate=copying?st::OwnerCapture(held):owner.capture_statistics(wanted,limits());facts(candidate,48,1536);}
    peak=account.statistics().peak_requested_bytes;check(peak>before,"owner capture cap fixture did not exceed prior initialization/capture peak");
  }
  for(const bool exact:{true,false}) {
    auto owner=runtime(indexed,exact?peak:peak-1,48,1536);const auto account=owner.plan().account();const auto wanted=request(owner.plan(),8);
    const auto held=owner.capture_statistics(wanted,limits());std::optional<st::OwnerCapture> pin(owner.capture_statistics(wanted,limits()));
    const auto before=account.statistics().current;bool denied=false;
    try{const auto candidate=copying?st::OwnerCapture(held):owner.capture_statistics(wanted,limits());facts(candidate,48,1536);}
    catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong native owner query-cap error");denied=true;}
    check(denied!=exact && owner.sequence()==0 && account.statistics().current==before,"owner exact/one-under cap changed committed state or leaked tentative data");
    facts(held,48,1536);
    if(!exact) {
      {s04_alloc::Scope none(0);pin.reset();}
      const auto retry=copying?st::OwnerCapture(held):owner.capture_statistics(wanted,limits());facts(retry,48,1536);
      check(account.statistics().limit_bytes==peak-1,"native owner retry replaced the query allowance");
    }
    account.check_invariants();
  }
  std::cout<<(indexed?"indexed":"reference")<<" owner phase="<<(copying?"copy":"capture")<<" exact/one-under peak="<<peak<<'\n';
}
void persistent_capture_and_cross_account_assignment(bool indexed) {
  auto source=runtime(indexed);auto destination=runtime(indexed);const auto a=source.plan().account(),b=destination.plan().account();
  const auto wanted=request(source.plan());const auto held=source.capture_statistics(wanted,limits());const auto old=destination.capture_statistics(wanted,limits());
  std::size_t capture_calls=0,copy_calls=0;
  {s04_alloc::Scope count;const auto calibration=source.capture_statistics(wanted,limits());capture_calls=s04_alloc::calls;}
  {s04_alloc::Scope count;const auto calibration=st::OwnerCapture(held);copy_calls=s04_alloc::calls;}
  check(capture_calls>0 && copy_calls>0 && capture_calls<4096 && copy_calls<4096,"native owner failure fixture has invalid request count");
  for(const bool copying:{false,true}) {
    const auto expected=copying?copy_calls:capture_calls;std::size_t failed=0;
    for(std::size_t point=0;point<=expected;++point) {
      std::optional<st::OwnerCapture> output;if(copying)output=old;
      const auto before_a=a.statistics(),before_b=b.statistics();bool denied=false;std::size_t calls=0;
      {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
        try{if(copying)*output=held;else output=source.capture_statistics(wanted,limits());}catch(const std::bad_alloc&){denied=true;}
        calls=s04_alloc::calls;
      }
      if(denied) {
        ++failed;check(point<expected && calls==point+1 && a.statistics().current==before_a.current && b.statistics().current==before_b.current,
            "persistent native owner failure leaked requests or changed another query account");
        if(copying){owner_fixture::same_facts(*output,old);check(output->stamp().owner==old.stamp().owner && output->plan().account().statistics().owner==b.statistics().owner,
            "failed cross-query capture assignment changed destination stamp/account");}
        if(copying)*output=held;else output=source.capture_statistics(wanted,limits());
      }else {
        check(point==expected && calls==expected && a.statistics().successful_allocations-before_a.successful_allocations==calls &&
            b.statistics().successful_allocations==before_b.successful_allocations,"capture/cross-query copy requests did not all use the source query grant");
      }
      owner_fixture::same_facts(*output,held);
      check(output->plan().account().statistics().owner==a.statistics().owner && source.sequence()==0 && destination.sequence()==0,
          "capture/copy changed original account or accepted epoch");
      {s04_alloc::Scope none(0);output.reset();}a.check_invariants();b.check_invariants();
    }
    check(failed==expected,"native owner persistent sweep missed a request frontier");
    std::cout<<(indexed?"indexed":"reference")<<" owner phase="<<(copying?"cross-account-copy":"capture")<<" persistent faults="<<failed<<'\n';
  }
}
}
int main() {
  try{for(const bool indexed:{false,true}){requests_lifetimes_and_pending(indexed);caps(indexed,false);caps(indexed,true);persistent_capture_and_cross_account_assignment(indexed);}
    std::cout<<"native owner capture: original requests, nested blocks, exact caps, cross-account copies, pending metadata, retained lifetime and persistent failures passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
