#include "statistics_report_fixture.hpp"
#include <cstdlib>
#include <iostream>
#include <new>
namespace fault {
thread_local bool active=false;
thread_local std::size_t remaining=0;
[[gnu::noinline]] void* allocate(std::size_t n){if(active){if(remaining==0)throw std::bad_alloc{};--remaining;}if(auto* p=std::malloc(n?n:1))return p;throw std::bad_alloc{};}
}
void* operator new(std::size_t n){return fault::allocate(n);}
void* operator new[](std::size_t n){return fault::allocate(n);}
void operator delete(void* p) noexcept{std::free(p);}
void operator delete[](void* p) noexcept{std::free(p);}
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
using namespace report_fixture;
template<class Operation,class Verify>void sweep(const char* label,Operation operation,Verify verify){
  std::size_t failures=0;bool completed=false;
  for(std::size_t position=0;position<2048;++position){
    fault::active=true;fault::remaining=position;
    try{operation();fault::active=false;completed=true;}
    catch(const std::bad_alloc&){fault::active=false;++failures;}
    catch(...){fault::active=false;throw;}
    verify();operation();verify();if(completed)break;
  }
  check(completed && failures>0);std::cout<<label<<" injected failures="<<failures<<'\n';
}
int main(){
  const auto p=plan();auto db=database();const auto scan=requested(p);
  auto options=wf::delta_options();options.physical.support.observation.mode=ObservationMode::counters;
  auto runtime=DeltaRuntime::initialize(p,db,options);runtime.configure_workload_statistics(wf::enabled());wf::apply(runtime,1,SetOperation::insert,{n(8)});db.tables[1].insert(Row{n(8)});
  const auto old=Report::capture(runtime,scan);static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  const auto retained=Report::capture(runtime,scan,&old);const auto encoded=io::write_statistics_json(retained).text;
  const auto native=runtime.canonical_state();const auto owner=runtime.owner();
  const auto verify=[&]{check(runtime.owner()==owner && runtime.sequence()==1 && runtime.canonical_state()==native);runtime.check_invariants();
    check(io::write_statistics_json(retained).text==encoded);const auto recovered=Report::capture(runtime,scan,&old);literal(recovered,db,1);same_workload(retained.combined()->workload(),recovered.combined()->workload());};
  sweep("actual-owner report capture",[&]{static_cast<void>(Report::capture(runtime,scan,&old));},verify);
  sweep("bounded JSON export",[&]{static_cast<void>(io::write_statistics_json(retained));},verify);
  sweep("bounded human export",[&]{static_cast<void>(io::write_statistics_text(retained));},verify);
  SessionOptions session_options;session_options.delta=options;auto session=QuerySession::create_typed(p,db,{},session_options);session->configure_workload_statistics(wf::enabled());
  enqueue(*session,{1,TableId{1},SetOperation::erase,{n(8)}});session->start();check(session->begin_next());
  const auto pending=Report::capture(*session,scan);const auto pending_bytes=io::write_statistics_json(pending).text;
  const auto verify_session=[&]{check(session->status().committed_sequence==0 && session->status().phase==SessionPhase::pending);
    check(io::write_statistics_json(pending).text==pending_bytes);check(io::write_statistics_json(Report::capture(*session,scan)).text==pending_bytes);};
  sweep("guarded private session report",[&]{static_cast<void>(Report::capture(*session,scan));},verify_session);
  session->stop();session->drop();const auto dropped=Report::capture(*session,scan);check(!dropped.combined());check(io::write_statistics_json(pending).text==pending_bytes);
  std::cout<<"4 report allocation sweeps completed\n";
}
