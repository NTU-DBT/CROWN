#include "crown/runtime/session.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>

using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool condition,std::string_view message) {if(!condition)throw std::runtime_error(std::string(message));}
Catalog schema() {
  return Catalog{1,{{"input",{{"id",ScalarType::int64},{"text",ScalarType::string},{"flag",ScalarType::boolean},
      {"day",ScalarType::date},{"amount",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}}}}}};
}
PhysicalPlan plan(bool indexed) {
  return planner::lower_tree(schema(),Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():PhysicalOptions{});
}
DeltaOptions options(std::uint64_t cap=64*1024*1024) {DeltaOptions result;result.physical.support.memory_limit_bytes=cap;return result;}
Row row(std::int64_t id,std::size_t bytes=8192) {
  Row result{id,std::string("\0typed",6)+std::string(bytes,'q'),true,Date::parse("2026-11-09"),
      Decimal::parse("123456789012345678901234567890123456.12")};result.reserve(16);return result;
}
io::TransportBatch batch(std::size_t count=13,std::size_t bytes=8192,std::uint64_t first=1) {
  std::vector<io::InputItem> input;
  for(std::size_t i=0;i<count;++i) {
    const auto seq=first+i;
    input.emplace_back(io::InputEvent{{seq,TableId{0},SetOperation::insert,row(static_cast<std::int64_t>(seq),bytes)},
        io::SourcePosition{std::string(120,'s'),seq}});
  }
  return io::TransportBatch(std::move(input));
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();const auto usage=account.statistics().current;
  check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(),"typed queue/progress survived its final owner");
}
void accept(io::TypedQueue& queue,DeltaRuntime& runtime) {
  const auto* item=queue.peek();check(item,"typed queue lost its head");const auto* event=std::get_if<io::InputEventView>(item);
  check(event,"typed queue changed its input kind");auto pending=runtime.begin_view(event->update);pending.drain();
  {s04_alloc::Scope no_allocation(0);auto epoch=pending.commit();queue.acknowledge();epoch.discard();}
}
void ownership_and_requests(bool indexed) {
  resource::MemoryAccount account;io::AccountedInputProgress held,closed;
  {
    DeltaRuntime runtime(plan(indexed),options());account=runtime.plan().account();
    std::optional<io::TypedQueue> queue;auto before=account.statistics().successful_allocations;std::size_t calls=0;
    {s04_alloc::Scope count;queue.emplace(runtime.plan(),io::QueueMode::physical);calls=s04_alloc::calls;}
    check(calls==account.statistics().successful_allocations-before,"native queue constructor allocated ordinary catalog/progress/control storage");
    auto offered=batch(2);const auto baseline=account.statistics().current.requested_bytes;before=account.statistics().successful_allocations;
    {s04_alloc::Scope count;check(queue->enqueue(offered)==io::Admission::accepted,"native queue refused a valid batch");calls=s04_alloc::calls;}
    check(offered.empty() && calls==account.statistics().successful_allocations-before &&
        account.statistics().current.requested_bytes-baseline==queue->stats().accounted_bytes,
        "typed admission actual requests, row/source payloads or byte preflight did not reconcile");
    before=account.statistics().successful_allocations;
    const io::InputItemView* head=nullptr;
    {s04_alloc::Scope count;head=queue->peek();calls=s04_alloc::calls;}
    check(head && queue->peek()==head && calls==account.statistics().successful_allocations-before,
        "native head validation/progress staging allocated unaccounted decimal or source storage");
    accept(*queue,runtime);before=account.statistics().successful_allocations;
    {s04_alloc::Scope count;held=queue->progress();calls=s04_alloc::calls;}
    check(calls==account.statistics().successful_allocations-before && calls>0,"native progress snapshot hid unaccounted node/key/control copies");
    accept(*queue,runtime);check(held.sequence==1 && held.source_positions.at(std::string(120,'s'))==1,
        "native progress copy changed with its source");
    {s04_alloc::Scope no_allocation(0);closed=queue->close();queue.reset();}
  }
  check(closed.sequence==2 && closed.source_positions.at(std::string(120,'s'))==2 && held.sequence==1,
      "native accepted progress did not survive queue/runtime destruction");
  {s04_alloc::Scope no_allocation(0);held=io::AccountedInputProgress{};closed=io::AccountedInputProgress{};}
  controller_only(account);
}
void component_and_query_limits(bool indexed) {
  std::uint64_t peak=0;std::size_t bytes=0;
  {
    DeltaRuntime runtime(plan(indexed),options());io::TypedQueue queue(runtime.plan(),io::QueueMode::physical);auto offered=batch();
    const auto setup=runtime.plan().account().statistics().peak_requested_bytes;
    check(queue.enqueue(offered)==io::Admission::accepted,"native byte calibration failed");
    bytes=queue.stats().accounted_bytes;peak=runtime.plan().account().statistics().peak_requested_bytes;check(peak>setup,"native input fixture did not exceed setup peak");
  }
  for(const bool exact:{true,false}) {
    DeltaRuntime runtime(plan(indexed),options());io::QueueLimits limits;limits.bytes=exact?bytes:bytes-1;
    io::TypedQueue queue(runtime.plan(),io::QueueMode::physical,limits);auto offered=batch();const auto original=offered.accounted_bytes();
    const auto usage=runtime.plan().account().statistics().current;io::Admission result;std::size_t calls=0;
    {s04_alloc::Scope count;result=queue.enqueue(offered);calls=s04_alloc::calls;}
    if(exact)check(result==io::Admission::accepted && offered.empty() && queue.stats().accounted_bytes==bytes,"exact native queue component cap changed");
    else check(result==io::Admission::full && calls==0 && offered.size()==13 && offered.accounted_bytes()==original &&
        queue.stats()==io::QueueStats{} && runtime.plan().account().statistics().current==usage,
        "one-byte-short component rejection copied payload or changed caller/queue state");
  }
  {DeltaRuntime runtime(plan(indexed),options(peak));io::TypedQueue queue(runtime.plan(),io::QueueMode::physical);auto offered=batch();
   check(queue.enqueue(offered)==io::Admission::accepted && runtime.plan().account().statistics().peak_requested_bytes==peak,"exact original query input cap changed");}
  resource::MemoryAccount account;
  {
    DeltaRuntime runtime(plan(indexed),options(peak-1));account=runtime.plan().account();io::TypedQueue queue(runtime.plan(),io::QueueMode::physical);
    auto offered=batch();const auto original=offered.accounted_bytes();const auto usage=account.statistics().current;bool denied=false;
    try{static_cast<void>(queue.enqueue(offered));}catch(const resource::MemoryFailure& failure){check(failure.fault()==resource::MemoryFault::limit,"wrong native input byte fault");denied=true;}
    check(denied && offered.size()==13 && offered.accounted_bytes()==original && queue.stats()==io::QueueStats{} && account.statistics().current==usage,
        "query cap failed to preserve caller batch and prior queue allocation state");
    auto smaller=batch(1);check(queue.enqueue(smaller)==io::Admission::accepted,"smaller same-sequence native input retry failed");
    accept(queue,runtime);check(runtime.sequence()==1 && queue.progress().sequence==1 && account.statistics().limit_bytes==peak-1,
        "native input retry replaced its allowance or lost accepted progress");
  }
  controller_only(account);
  std::cout<<(indexed?"indexed":"reference")<<" native input component bytes="<<bytes<<"; query exact/one-under peak="<<peak<<'\n';
}
void persistent_failures(bool indexed) {
  for(int scenario=0;scenario<3;++scenario) {
    std::size_t faults=0;bool complete=false;
    for(std::ptrdiff_t point=0;point<1024;++point) {
      DeltaRuntime runtime(plan(indexed),options());const auto account=runtime.plan().account();
      io::TypedQueue queue(runtime.plan(),io::QueueMode::physical);auto offered=batch(scenario==0?3:1);
      if(scenario>=1)check(queue.enqueue(offered)==io::Admission::accepted,"fault seed admission failed");
      if(scenario==2)accept(queue,runtime);
      const auto usage=account.statistics().current;const auto stats=queue.stats();const auto before=queue.progress();
      io::AccountedInputProgress copied;bool failed=false;
      // Snapshot construction above is outside the injected operation. Keep its
      // real original-account bytes in the calibrated pre-operation baseline.
      const auto operation_usage=account.statistics().current;
      {s04_alloc::Scope fault(point);try {
        if(scenario==0)static_cast<void>(queue.enqueue(offered));
        else if(scenario==1)static_cast<void>(queue.peek());
        else copied=queue.progress();
      }catch(const std::bad_alloc&){failed=true;}}
      if(failed) {
        ++faults;check(!queue.failed() && queue.stats()==stats && queue.progress()==before &&
            account.statistics().current==operation_usage,"native input fault leaked tentative ownership or changed accepted state");
        if(scenario==0) {
          check(offered.size()==3,"failed native admission consumed caller data");
          check(queue.enqueue(offered)==io::Admission::accepted,"unchanged offered batch did not retry");
        }else if(scenario==1)check(queue.peek()!=nullptr,"unchanged native head did not retry");
        else {check(copied==io::InputProgress{},"failed progress value copy changed the destination");copied=queue.progress();}
      }else complete=true;
      check(usage.requested_bytes<=account.statistics().peak_requested_bytes,"native input history counters lost actual requests");
      account.check_invariants();if(complete)break;
    }
    check(complete && faults>0,"native typed input persistent fault sweep incomplete");
    std::cout<<(indexed?"indexed":"reference")<<" native input scenario="<<scenario<<" persistent faults="<<faults<<'\n';
  }
}
struct FailingDecimal {operator Decimal() const {throw std::bad_alloc{};}};
template<class Action> std::pair<std::string,std::string> diagnostic(Action&& action) {
  try{action();return {};}catch(const Error& error){return {error.code(),error.what()};}
}
void late_error_parity(bool indexed) {
  const auto catalog=schema();
  for(int scenario=0;scenario<8;++scenario) {
    io::InputEvent event{{2,TableId{0},SetOperation::insert,row(2)},io::SourcePosition{std::string(120,'s'),2}};
    io::InputLimits limits;
    if(scenario==0)event.update.table=TableId{99};
    if(scenario==1)event.update.values.pop_back();
    if(scenario==2)event.update.values[2]=std::int64_t{7};
    if(scenario==3)event.update.values[4]=Decimal::parse("0.001");
    if(scenario==4) {
      try{event.update.values[0].emplace<Decimal>(FailingDecimal{});}catch(const std::bad_alloc&){}
      check(event.update.values[0].valueless_by_exception(),"invalid-scalar fixture did not become valueless");
    }
    if(scenario==5){event.update.values[2]=std::int64_t{7};limits.columns=4;}
    if(scenario==6){event.update.values[2]=std::int64_t{7};event.update.sequence=0;}
    if(scenario==7){event.update.values[2]=std::int64_t{7};event.update.operation=static_cast<SetOperation>(99);}
    const auto expected=diagnostic([&]{io::validate_input_event(event,catalog,limits);});check(!expected.first.empty(),"late error fixture was valid");
    DeltaRuntime runtime(plan(indexed),options());io::TypedQueue queue(runtime.plan(),io::QueueMode::physical,{},limits);
    auto prefix=batch(1);check(queue.enqueue(prefix)==io::Admission::accepted,"late error prefix admission failed");
    if(scenario==5) {
      // This profile rejects even the first row by column count. Use a fresh
      // queue so the deferred malformed event is still tested at the head.
      auto progress=queue.close();check(progress.sequence==0,"unread prefix was acknowledged");
    }
    if(scenario==5) {
      io::TypedQueue limited(runtime.plan(),io::QueueMode::physical,{},limits);
      io::TransportBatch offered({event});check(limited.enqueue(offered)==io::Admission::accepted,"invalid native import rejected early");
      check(diagnostic([&]{static_cast<void>(limited.peek());})==expected,"native column-limit/deferred-row precedence differs");
    }else {
      accept(queue,runtime);const auto committed=runtime.canonical_state();
      io::TransportBatch offered({event});check(queue.enqueue(offered)==io::Admission::accepted,"malformed future row was rejected before its head");
      check(diagnostic([&]{static_cast<void>(queue.peek());})==expected && queue.failed() && queue.progress().sequence==1 &&
          runtime.canonical_state()==committed,"native late row diagnostic/code/order or prior epoch differs from reference");
      check(diagnostic([&]{static_cast<void>(queue.peek());}).first=="input_failed","native malformed head was not sticky");
    }
  }
}
} // namespace
int main() {
  try {
    for(const bool indexed:{false,true}) {
      ownership_and_requests(indexed);component_and_query_limits(indexed);persistent_failures(indexed);late_error_parity(indexed);
    }
    std::cout<<"native typed input: actual grant/bytes, transactional ownership, retained progress, late errors and fault recovery passed\n";
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
