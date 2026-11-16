#include "crown/io/checkpoint.hpp"
#include "crown/runtime/delta.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
using namespace crown;
namespace {
void check(bool value,const char* message){if(!value)throw std::runtime_error(message);}
PhysicalPlan plan(bool indexed=false) {
  Catalog catalog{3,{{"r",{{"text",ScalarType::string},{"n",ScalarType::int64}}}}};
  return planner::lower_tree(catalog,Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():PhysicalOptions{});
}
const std::string source_name=std::string(8192,'s');
const Row first{std::string("alpha"),std::int64_t{7}},second{std::string("beta,tail"),std::int64_t{8}};
template<class Action> void rejected(Action action) {
  bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}
  check(failed,"invalid native source state accepted");
}
struct Profile {io::InputOptions options;std::string prefix,tail;};
Profile profile(io::InputFormat format,const program::Catalog& catalog) {
  Profile result;auto& options=result.options;options.format=format;options.limits.source_bytes=16384;
  options.limits.records=2;
  if(format==io::InputFormat::jsonl || format==io::InputFormat::binary) {
    const io::InputEvent a{{1,TableId{0},SetOperation::insert,first},io::SourcePosition{source_name,10}};
    const io::InputEvent b{{2,TableId{0},SetOperation::insert,second},io::SourcePosition{source_name,20}};
    if(format==io::InputFormat::jsonl){result.prefix=io::write_input_json(a,catalog,options.limits)+"\n";result.tail=io::write_input_json(b,catalog,options.limits)+"\n";}
    else {result.prefix=io::write_input_binary(a,catalog,options.limits);result.tail=io::write_input_binary(b,catalog,options.limits);}
  }else {
    options.source=source_name;
    if(format!=io::InputFormat::legacy_relations)options.table=TableId{0};
    if(format==io::InputFormat::csv){result.prefix="n,text\n7,alpha\n";result.tail="8,\"beta,tail\"\n";options.byte_offset=111;}
    if(format==io::InputFormat::legacy_signed){result.prefix="+,alpha,7\n";result.tail="+,\"beta,tail\",8\n";}
    if(format==io::InputFormat::legacy_relations){options.relation_tokens.emplace("R",TableId{0});result.prefix="+,R,alpha,7\n";result.tail="+,R,\"beta,tail\",8\n";}
    if(format==io::InputFormat::legacy_insert_only){result.prefix="alpha,7\n";result.tail="\"beta,tail\",8\n";}
    if(format==io::InputFormat::legacy_flags){result.prefix="1,alpha,7\n";result.tail="1,\"beta,tail\",8\n";}
    if(format==io::InputFormat::legacy_timestamp_flags){result.prefix="10,1,alpha,7\n";result.tail="20,1,\"beta,tail\",8\n";}
  }
  options.limits.total_bytes=result.prefix.size()+result.tail.size();return result;
}
void reader(io::InputFormat format) {
  const auto artifact=plan();runtime::DeltaRuntime owner(artifact),receiving(artifact);
  const auto account=owner.plan().account(),target=receiving.plan().account();
  const auto input_profile=profile(format,owner.plan().source_catalog());std::istringstream input(input_profile.prefix+input_profile.tail);
  io::EventReader original(input,owner.plan(),input_profile.options);
  check(original.peek()->update.values==first,"reader first record differs");
  rejected([&]{auto value=original.checkpoint_state();});original.acknowledge();
  const auto accepted=original.progress().export_value();
  const auto before=account.statistics();std::size_t captures=0;std::optional<io::ReaderCheckpoint> snapshot;
  {s04_alloc::Scope count;snapshot=original.checkpoint_state();captures=s04_alloc::calls;}
  check(captures==account.statistics().successful_allocations-before.successful_allocations && snapshot->bytes==input_profile.prefix.size(),"reader capture bytes/account differ");
  std::istringstream continuation(input_profile.tail);const auto target_before=target.statistics();std::size_t restores=0;
  std::optional<io::EventReader> restored;
  {s04_alloc::Scope count;restored=io::EventReader::restore_state(continuation,receiving.plan(),*snapshot);restores=s04_alloc::calls;}
  check(restores==target.statistics().successful_allocations-target_before.successful_allocations && restored->account().statistics().owner==target.statistics().owner,"reader restore escaped receiving account");
  check(restored->progress()==accepted && restored->bytes_read()==snapshot->bytes && restored->records_read()==1,"reader restore lost source progress/counters");
  const auto resident=account.statistics().current;
  for(std::size_t point=0;point<captures;++point) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=original.checkpoint_state();}catch(const std::bad_alloc&){failed=true;}}
    check(failed && account.statistics().current==resident && original.progress()==accepted,"reader snapshot OOM changed source");
  }
  const auto target_resident=target.statistics().current;
  for(std::size_t point=0;point<restores;++point) {
    std::istringstream tail(input_profile.tail);bool failed=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=io::EventReader::restore_state(tail,receiving.plan(),*snapshot);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && target.statistics().current==target_resident && restored->progress()==accepted,"reader restore OOM retained source storage");
  }
  for(unsigned corruption=0;corruption<4;++corruption) {
    auto bad=*snapshot;
    if(corruption==0)bad.catalog_sha256[0]^=1;
    if(corruption==1)bad.records=3;
    if(corruption==2)bad.bytes=*bad.options.get().limits.total_bytes+1;
    if(corruption==3){bad.header_read=!bad.header_read;}
    std::istringstream tail(input_profile.tail);rejected([&]{auto value=io::EventReader::restore_state(tail,receiving.plan(),bad);});
    check(target.statistics().current==target_resident,"malformed reader restore leaked");
  }
  io::SourceStateLimits zero;zero.work=0;
  {s04_alloc::Scope deny(0);rejected([&]{auto value=original.checkpoint_state(zero);});
    rejected([&]{auto value=io::EventReader::restore_state(continuation,receiving.plan(),*snapshot,zero);});}
  if(format==io::InputFormat::csv) {
    auto low=io::SourceStateLimits{};low.csv_fields=1;
    rejected([&]{auto value=original.checkpoint_state(low);});
    rejected([&]{auto value=io::EventReader::restore_state(continuation,receiving.plan(),*snapshot,low);});
  }
  const auto* a=original.peek();const auto* b=restored->peek();
  check(a && b && a->update.sequence==2 && b->update.sequence==2 && a->update.values==second && b->update.values==second && a->source_position==b->source_position,"continued reader record/position differs");
  original.acknowledge();restored->acknowledge();
  check(original.progress()==restored->progress() && original.bytes_read()==restored->bytes_read() && original.records_read()==restored->records_read(),"reader continuation reset origin or accepted positions");
  check(!original.peek() && !restored->peek(),"reader continuation EOF differs");
  auto ended=restored->checkpoint_state();std::istringstream ignored(input_profile.prefix);
  auto at_end=io::EventReader::restore_state(ignored,receiving.plan(),ended);check(!at_end.peek(),"restored EOF consumed new input");
  {s04_alloc::Scope deny(0);auto progress=original.close();check(progress.sequence==2,"reader close lost accepted sequence");}
  check(snapshot->progress==accepted && snapshot->options.get().format==format,"reader snapshot lost lifetime after close");
  std::cout<<"reader profile="<<static_cast<unsigned>(format)<<" native state: "<<captures<<" capture/"<<restores<<" restore persistent faults; exact CSV/counters/positions/EOF continuation passed\n";
}
void queue(io::QueueMode mode,bool closed) {
  const auto artifact=plan();runtime::DeltaRuntime owner(artifact),receiving(artifact);
  const auto account=owner.plan().account(),target=receiving.plan().account();io::InputLimits limits;limits.source_bytes=16384;limits.records=2;
  io::TypedQueue original(owner.plan(),mode,{},limits);
  const auto item=[&](std::uint64_t sequence)->io::InputItem {
    if(mode==io::QueueMode::physical)return io::InputEvent{{sequence,TableId{0},SetOperation::insert,first},io::SourcePosition{source_name,sequence*10}};
    return io::WindowCommand{sequence,io::AdvanceWatermark{sequence},io::SourcePosition{source_name,sequence*10}};
  };
  io::TransportBatch batch({item(1)});check(original.enqueue(batch)==io::Admission::accepted,"queue fixture not admitted");
  rejected([&]{auto state=original.checkpoint_state();});check(original.peek()!=nullptr,"queue fixture disappeared");original.acknowledge();
  if(closed){original.finish();}
  const auto accepted=original.progress().export_value();
  const auto before=account.statistics();std::size_t captures=0;std::optional<io::QueueCheckpoint> snapshot;
  {s04_alloc::Scope count;snapshot=original.checkpoint_state();captures=s04_alloc::calls;}
  check(captures==account.statistics().successful_allocations-before.successful_allocations,"queue capture escaped original grant");
  const auto target_before=target.statistics();std::size_t restores=0;std::optional<io::TypedQueue> restored;
  {s04_alloc::Scope count;restored.emplace(receiving.plan(),*snapshot);restores=s04_alloc::calls;}
  check(restores==target.statistics().successful_allocations-target_before.successful_allocations && restored->progress()==accepted && restored->closed()==closed,"queue restore lost progress/closed state or account");
  const auto resident=account.statistics().current,target_resident=target.statistics().current;
  for(std::size_t point=0;point<captures;++point) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto state=original.checkpoint_state();}catch(const std::bad_alloc&){failed=true;}}
    check(failed && account.statistics().current==resident && original.progress()==accepted,"queue snapshot OOM changed source");
  }
  for(std::size_t point=0;point<restores;++point) {
    bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{io::TypedQueue value(receiving.plan(),*snapshot);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && target.statistics().current==target_resident && restored->progress()==accepted,"queue restore OOM retained native state");
  }
  auto bad=*snapshot;bad.catalog_sha256[0]^=1;rejected([&]{io::TypedQueue value(receiving.plan(),bad);});
  io::SourceStateLimits zero;zero.work=0;{s04_alloc::Scope deny(0);rejected([&]{auto state=original.checkpoint_state(zero);});rejected([&]{io::TypedQueue value(receiving.plan(),*snapshot,zero);});}
  if(!closed) {
    io::TransportBatch next({item(2)});check(restored->enqueue(next)==io::Admission::accepted && restored->peek()!=nullptr,"restored queue rejected next sequence");
    {s04_alloc::Scope deny(0);restored->acknowledge();}check(restored->progress().sequence==2,"restored queue did not publish next sequence");
  }
  {s04_alloc::Scope deny(0);auto progress=original.close();check(progress==accepted,"queue close lost progress");}
  check(snapshot->progress==accepted,"queue snapshot lost lifetime");
  std::cout<<"queue mode="<<static_cast<unsigned>(mode)<<" closed="<<closed<<" native state: "<<captures<<" capture/"<<restores<<" restore persistent faults and next source continuity passed\n";
}
void large_positions() {
  const auto artifact=plan();runtime::DeltaRuntime owner(artifact),receiving(artifact);
  io::InputLimits input_limits;input_limits.sources=2048;input_limits.records=std::nullopt;
  io::TypedQueue original(owner.plan(),io::QueueMode::physical,{},input_limits);
  std::vector<io::InputItem> events;events.reserve(1025);
  for(std::uint64_t i=1;i<=1025;++i)events.emplace_back(io::InputEvent{{i,TableId{0},SetOperation::insert,first},
      io::SourcePosition{"source"+std::to_string(i),i}});
  io::TransportBatch batch(std::move(events));check(original.enqueue(batch)==io::Admission::accepted,"large source fixture not admitted");
  while(original.peek())original.acknowledge();
  rejected([&]{auto value=original.checkpoint_state();});
  io::SourceStateLimits limits;limits.positions=2048;auto snapshot=original.checkpoint_state(limits);
  rejected([&]{io::TypedQueue value(receiving.plan(),snapshot);});
  io::TypedQueue restored(receiving.plan(),snapshot,limits);
  check(restored.progress()==original.progress() && restored.progress().source_positions.size()==1025,"custom source limits narrowed the supported queue state");
}
}
int main() {
  try {
    for(const auto format:{io::InputFormat::jsonl,io::InputFormat::binary,io::InputFormat::csv,io::InputFormat::legacy_signed,
        io::InputFormat::legacy_relations,io::InputFormat::legacy_insert_only,io::InputFormat::legacy_flags,io::InputFormat::legacy_timestamp_flags})reader(format);
    for(const auto mode:{io::QueueMode::physical,io::QueueMode::window})for(const bool closed:{false,true})queue(mode,closed);
    large_positions();
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
