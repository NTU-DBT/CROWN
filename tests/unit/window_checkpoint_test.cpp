#include "crown/runtime/delta.hpp"
#include "crown/runtime/window.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <stdexcept>
using namespace crown;
using namespace crown::runtime;
namespace {
void check(bool value,const char* message){if(!value)throw std::runtime_error(message);}
PhysicalPlan plan(bool indexed) {
  Catalog catalog{7,{}};
  for(const char* name:{"r","s"})catalog.tables.push_back({name,{{"x",ScalarType::int64},{"text",ScalarType::string},
      {"flag",ScalarType::boolean},{"day",ScalarType::date},{"value",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}}}});
  Query query{{{"x",ScalarType::int64},{"text",ScalarType::string},{"flag",ScalarType::boolean},{"day",ScalarType::date},{"value",ScalarType::decimal}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}}}},{{VariableId{0},"x"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}},{},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
WindowOptions options(WindowFifoPolicy fifo) {
  WindowOptions result;result.managed_tables.reserve(9);result.managed_tables={TableId{0},TableId{1}};result.width=10;result.fifo=fifo;return result;
}
Row row(std::int64_t id) {return {id,std::string(8192,'w')+std::string("\0\xff",2),true,Date::parse("0001-01-01"),
    Decimal::parse("123456789012345678901234567890123456.12")};}
using Output=std::set<std::pair<SetOperation,Row>>;
Output accept(DeltaRuntime& runtime,WindowController& window,const io::WindowCommand& command) {
  Output result;
  do {
    auto prepared=window.prepare(command,runtime.sequence()+1);
    if(prepared.update()) {
      auto pending=runtime.begin_view(*prepared.update());pending.drain();auto epoch=pending.commit();
      {s04_alloc::Scope deny(0);prepared.publish();}
      while(auto value=epoch.next())check(result.emplace(value->operation,storage::export_row(value->tuple.values())).second,"duplicate window output");
    }else {s04_alloc::Scope deny(0);prepared.publish();}
  }while(window.progress().active_command_sequence);
  return result;
}
io::WindowCommand insert(std::uint64_t sequence,std::uint64_t label,TableId table,std::uint64_t timestamp) {
  return {sequence,io::WindowInsert{label,table,row(table.value?2:1),timestamp},{}};
}
template<class Action> void rejected(Action action) {
  bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}
  check(failed,"invalid window checkpoint accepted");
}
void scenario(bool indexed,WindowFifoPolicy fifo) {
  const auto artifact=plan(indexed);const auto compiler=CompiledProgram::standalone(artifact);
  DeltaRuntime source(artifact);const auto original=source.plan().account();WindowController window(original,source.plan().source_catalog(),options(fifo));
  accept(source,window,insert(1,1,TableId{0},0));accept(source,window,insert(2,2,TableId{0},1));
  accept(source,window,{3,io::WindowWithdraw{1},{}});accept(source,window,insert(4,3,TableId{1},2));
  accept(source,window,{5,io::AdvanceWatermark{2},{}});
  const auto canonical=window.canonical_state();const auto runtime_state=source.canonical_state();
  check(canonical.counts.at(0).id==1 && canonical.labels.at(0).label==2,"orphaned original count-ID fixture missing");
  const auto before=original.statistics();std::optional<WindowCheckpoint> snapshot;std::size_t captures=0;
  {s04_alloc::Scope count;snapshot=window.checkpoint_state();captures=s04_alloc::calls;}
  check(captures==original.statistics().successful_allocations-before.successful_allocations && captures>0,"window state escaped original account");
  const auto image=source.checkpoint_image();auto restored=DeltaRuntime::restore_image(compiler,{image.bytes.data(),image.bytes.size()});
  const auto target=restored.plan().account();const auto target_before=target.statistics();std::size_t restores=0;
  std::optional<WindowController> native;
  {s04_alloc::Scope count;native.emplace(target,restored.plan().source_catalog(),*snapshot);restores=s04_alloc::calls;}
  check(restores==target.statistics().successful_allocations-target_before.successful_allocations,"window restore escaped receiving account");
  check(native->canonical_state()==canonical && restored.canonical_state()==runtime_state,"window restore lost exact indices/count IDs/progress");
  const auto steady=original.statistics().current;
  for(unsigned i=0;i<20;++i){auto repeat=window.checkpoint_state();}
  check(original.statistics().current==steady,"repeated window snapshots grew resident storage");
  for(std::size_t point=0;point<captures;++point) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto state=window.checkpoint_state();}catch(const std::bad_alloc&){failed=true;}}
    check(failed && original.statistics().current==steady && window.canonical_state()==canonical,"window capture OOM changed committed state");
  }
  const auto target_steady=target.statistics().current;
  for(std::size_t point=0;point<restores;++point) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{WindowController value(target,restored.plan().source_catalog(),*snapshot);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && target.statistics().current==target_steady && native->canonical_state()==canonical,"window restore OOM leaked or changed existing state");
  }
  WindowStateLimits exact;exact.work=snapshot->work;{auto value=window.checkpoint_state(exact);}
  --exact.work;{s04_alloc::Scope deny(0);rejected([&]{auto state=window.checkpoint_state(exact);});}
  for(const bool labels:{false,true}) {
    WindowStateLimits low;if(labels)low.labels=1;else low.counts=1;
    {s04_alloc::Scope deny(0);rejected([&]{auto value=window.checkpoint_state(low);});
      rejected([&]{WindowController value(target,restored.plan().source_catalog(),*snapshot,low);});}
  }
  for(unsigned corruption=0;corruption<9;++corruption) {
    auto bad=window.checkpoint_state();
    if(corruption==0)++bad.counts[0].count;
    if(corruption==1)bad.labels[0].count_id=999;
    if(corruption==2)++bad.labels[0].deadline;
    if(corruption==3)bad.catalog_sha256[0]^=1;
    if(corruption==4)bad.progress.last_label=0;
    if(corruption==5)bad.progress.active_command_sequence=6;
    if(corruption==6)bad.progress.completed_steps=1;
    if(corruption==7)bad.progress.completed_watermark=20;
    if(corruption==8){bad.counts[1].table=bad.counts[0].table;bad.counts[1].values=bad.counts[0].values.clone(original);}
    rejected([&]{WindowController value(target,restored.plan().source_catalog(),bad);});
    check(target.statistics().current==target_steady && native->canonical_state()==canonical,"malformed restore changed existing window");
  }
  {
    std::uint64_t peak=0;
    {auto account=resource::MemoryAccount::create(64*1024*1024);WindowController value(account,restored.plan().source_catalog(),*snapshot);peak=account.statistics().peak_requested_bytes;}
    {auto account=resource::MemoryAccount::create(peak);WindowController value(account,restored.plan().source_catalog(),*snapshot);check(value.canonical_state()==canonical,"exact native window restore cap failed");}
    {auto account=resource::MemoryAccount::create(peak-1);bool failed=false;
      try{WindowController value(account,restored.plan().source_catalog(),*snapshot);}catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
      check(failed && account.statistics().current.allocations==1,"one-under native window restore cap leaked");}
  }
  {auto prepared=window.prepare({6,io::AdvanceWatermark{20},{}},source.sequence()+1);rejected([&]{auto state=window.checkpoint_state();});}
  {auto prepared=window.prepare({6,io::AdvanceWatermark{20},{}},source.sequence()+1);
    check(!prepared.completes_command(),"multi-step watermark fixture missing");
    auto pending=source.begin_view(*prepared.update());pending.drain();auto epoch=pending.commit();epoch.discard();prepared.publish();
    check(window.progress().active_command_sequence.has_value(),"active watermark was cleared too early");rejected([&]{auto state=window.checkpoint_state();});}
  // Bring both sides through the same remaining watermark, preserving its
  // command boundary even though one source physical step already committed.
  accept(source,window,{6,io::AdvanceWatermark{20},{}});accept(restored,*native,{6,io::AdvanceWatermark{20},{}});
  check(window.canonical_state()==native->canonical_state() && source.canonical_state()==restored.canonical_state(),"restored watermark expiration differs");
  check(accept(source,window,insert(7,4,TableId{0},20))==accept(restored,*native,insert(7,4,TableId{0},20)),"next insertion output differs");
  check(accept(source,window,{8,io::AdvanceWatermark{30},{}})==accept(restored,*native,{8,io::AdvanceWatermark{30},{}}),"next expiration output differs");
  check(window.canonical_state()==native->canonical_state() && source.canonical_state()==restored.canonical_state(),"next window state differs");
  window.stop();auto stopped=window.checkpoint_state();WindowController terminal(target,restored.plan().source_catalog(),stopped);
  check(terminal.canonical_state()==window.canonical_state(),"stopped window state lost progress");
  std::cout<<(indexed?"indexed":"reference")<<" fifo="<<static_cast<unsigned>(fifo)<<" window native state: "<<captures<<" capture/"<<restores
      <<" restore persistent faults, exact indices/count-ID/metadata progress, active watermark barrier and next updates passed\n";
}
// Independent full-state reference: physical births are an insertion-order
// list of distinct (table,row) pairs, not the native count-ID representation.
struct LifetimeReference {
  using Key=std::pair<TableId,std::int64_t>;
  struct Label {Key row;std::uint64_t timestamp;};
  std::map<std::uint64_t,Label> labels;
  std::map<Key,std::size_t> counts;
  std::vector<Key> births;
  std::uint64_t watermark=0;
  bool per_relation;
  bool remove(std::uint64_t id) {
    const auto found=labels.find(id);const auto key=found->second.row;
    if(counts.at(key)==1) {
      const auto first=std::find_if(births.begin(),births.end(),[&](const Key& live) {
        return !per_relation || live.first==key.first;
      });
      if(*first!=key)return false;
      births.erase(first);counts.erase(key);
    }else --counts.at(key);
    labels.erase(found);return true;
  }
  bool apply(const io::WindowCommand& command) {
    if(const auto* value=std::get_if<io::WindowInsert>(&command.command)) {
      const Key key{value->table,std::get<std::int64_t>(value->values[0])};
      if(++counts[key]==1)births.push_back(key);
      labels.emplace(value->label,Label{key,value->timestamp});return true;
    }
    if(const auto* value=std::get_if<io::WindowWithdraw>(&command.command))return remove(value->label);
    const auto mark=std::get<io::AdvanceWatermark>(command.command).watermark;
    std::vector<std::pair<std::uint64_t,std::uint64_t>> expiration;
    for(const auto& [id,label]:labels)if(label.timestamp+10<=mark)expiration.emplace_back(label.timestamp+10,id);
    std::sort(expiration.begin(),expiration.end());
    for(const auto& [deadline,id]:expiration){static_cast<void>(deadline);if(!remove(id))return false;}
    watermark=mark;return true;
  }
};
void compare_lifetimes(const LifetimeReference& expected,DeltaRuntime& runtime,const WindowController& window) {
  const auto actual=window.canonical_state();
  check(actual.labels.size()==expected.labels.size() && actual.counts.size()==expected.counts.size(),"physical FIFO reference sizes differ");
  check(actual.completed_watermark==expected.watermark,"physical FIFO watermark differs");
  for(const auto& label:actual.labels) {
    const auto& reference=expected.labels.at(label.label);
    check(label.table==reference.row.first && label.values==row(reference.row.second) && label.timestamp==reference.timestamp,
        "physical FIFO label state differs");
  }
  for(const auto& count:actual.counts) {
    const LifetimeReference::Key key{count.table,std::get<std::int64_t>(count.values[0])};
    check(count.count==expected.counts.at(key),"physical FIFO row reference count differs");
  }
  std::set<Row> wanted,results;
  for(const auto& [key,count]:expected.counts){static_cast<void>(count);if(key.first==TableId{0})wanted.insert(Row{key.second});}
  auto cursor=runtime.results();while(auto result=cursor.next())results.insert(storage::export_row(result->values()));
  check(results==wanted,"physical FIFO native query result differs from full-state reference");
}
void lifetime_reference(bool indexed,WindowFifoPolicy fifo) {
  DeltaRuntime runtime(plan(indexed));WindowController window(runtime.plan().account(),runtime.plan().source_catalog(),options(fifo));
  LifetimeReference expected{{},{},{},0,fifo==WindowFifoPolicy::physical_per_relation};
  std::minstd_rand random(731);std::uint64_t label=0;std::size_t accepted=0,rejected_count=0;
  for(unsigned step=0;step<120;++step) {
    io::WindowCommand command;command.sequence=window.progress().completed_command_sequence+1;
    const auto operation=random()%3;
    if(expected.labels.empty() || operation==0)
      command.command=io::WindowInsert{++label,TableId{random()%2},row(static_cast<std::int64_t>(random()%5)),expected.watermark+random()%7};
    else if(operation==1) {
      auto chosen=expected.labels.begin();std::advance(chosen,random()%expected.labels.size());
      command.command=io::WindowWithdraw{chosen->first};
    }else command.command=io::AdvanceWatermark{expected.watermark+1+random()%6};
    auto proposal=expected;const bool allowed=proposal.apply(command);
    const auto before=window.canonical_state();const auto native=runtime.canonical_state();const auto memory=runtime.plan().account().statistics().current;
    if(allowed){accept(runtime,window,command);expected=std::move(proposal);++accepted;}
    else {
      bool failed=false;try{auto pending=window.prepare(command,runtime.sequence()+1);}
      catch(const Error& error){failed=error.code()=="window_fifo_violation";}
      check(failed,"physical FIFO reference rejection was accepted");
      check(window.canonical_state()==before && runtime.canonical_state()==native && runtime.plan().account().statistics().current==memory,
          "physical FIFO rejection changed state or retained scratch");++rejected_count;
    }
    compare_lifetimes(expected,runtime,window);
  }
  check(accepted>0 && rejected_count>0,"physical FIFO generated trace missed an outcome");
  std::cout<<"physical FIFO indexed="<<indexed<<" policy="<<window_fifo_name(fifo)<<" independent reference "<<accepted<<" accepted/"<<rejected_count<<" rejected commands passed\n";
}
void lifetime_preflight(bool indexed,WindowFifoPolicy fifo) {
  DeltaRuntime runtime(plan(indexed));WindowController window(runtime.plan().account(),runtime.plan().source_catalog(),options(fifo));
  accept(runtime,window,{1,io::WindowInsert{1,TableId{0},row(1),0},{}});
  accept(runtime,window,{2,io::WindowInsert{2,TableId{0},row(2),1},{}});
  accept(runtime,window,{3,io::WindowInsert{3,TableId{0},row(1),2},{}});
  const auto before=window.canonical_state();const auto state=runtime.canonical_state();
  // A1 expires before B2, but A3 retains the older physical row. Rejection must
  // precede even A1's metadata-only effect, not merely the later B2 erase.
  bool failed=false;try{auto pending=window.prepare({4,io::AdvanceWatermark{11},{}},runtime.sequence()+1);}
  catch(const Error& error){failed=error.code()=="window_fifo_violation";}
  check(failed && window.canonical_state()==before && runtime.canonical_state()==state,"physical FIFO watermark published a rejected prefix");
  // Removing A3 is legal metadata-only work despite its newer label.
  accept(runtime,window,{4,io::WindowWithdraw{3},{}});
  const io::WindowCommand watermark{5,io::AdvanceWatermark{11},{}};
  const auto unchanged=window.canonical_state();const auto memory=runtime.plan().account().statistics().current;
  std::size_t preparations=0;
  {s04_alloc::Scope measure;auto pending=window.prepare(watermark,runtime.sequence()+1);preparations=s04_alloc::calls;}
  for(std::size_t point=0;point<preparations;++point) {
    bool denied=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
      try{auto pending=window.prepare(watermark,runtime.sequence()+1);}catch(const std::bad_alloc&){denied=true;}}
    check(denied && window.canonical_state()==unchanged && runtime.plan().account().statistics().current==memory,
        "physical FIFO preparation failure changed state or leaked scratch");
  }
  accept(runtime,window,watermark);check(window.metrics().live_labels==0,"physical FIFO retry did not remove the valid lifetime prefix");
  const auto exact_work=window.metrics().last_command_work;
  for(const auto shortfall:{std::uint64_t{0},std::uint64_t{1}}) {
    auto limit=options(fifo);limit.command_work_limit=exact_work-shortfall;
    DeltaRuntime candidate(plan(indexed));WindowController bounded(candidate.plan().account(),candidate.plan().source_catalog(),limit);
    accept(candidate,bounded,{1,io::WindowInsert{1,TableId{0},row(1),0},{}});
    accept(candidate,bounded,{2,io::WindowInsert{2,TableId{0},row(2),1},{}});
    accept(candidate,bounded,{3,io::WindowInsert{3,TableId{0},row(1),2},{}});
    accept(candidate,bounded,{4,io::WindowWithdraw{3},{}});
    const auto previous=bounded.canonical_state();const auto previous_native=candidate.canonical_state();bool denied=false;
    try{accept(candidate,bounded,watermark);}catch(const Error& error){denied=error.code()=="resource_limit";}
    check(denied==(shortfall==1),"physical FIFO exact/one-under work boundary differs");
    if(shortfall)check(bounded.canonical_state()==previous && candidate.canonical_state()==previous_native,
        "physical FIFO work denial published a watermark prefix");
    else check(bounded.metrics().live_labels==0 && bounded.metrics().last_command_work==exact_work,"exact physical FIFO work cap failed");
  }
  std::cout<<"physical FIFO indexed="<<indexed<<" policy="<<window_fifo_name(fifo)<<" whole-watermark rejection/"<<preparations<<" persistent preparation faults/retry passed\n";
}
}
int main() {
  try{for(const bool indexed:{false,true}) {
    for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation,WindowFifoPolicy::physical_global,WindowFifoPolicy::physical_per_relation})scenario(indexed,fifo);
    for(const auto fifo:{WindowFifoPolicy::physical_global,WindowFifoPolicy::physical_per_relation}){lifetime_reference(indexed,fifo);lifetime_preflight(indexed,fifo);}
  }}
  catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
