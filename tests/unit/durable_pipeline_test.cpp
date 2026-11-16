#include "local_sink_fixture.hpp"
#include "crown/api/error.hpp"
#include "journal_file_probe.hpp"
#include "local_sink_probe.hpp"
#include <cerrno>
#include <sys/wait.h>
using namespace crown;
using namespace crown::runtime;
using namespace crown::local_sink_test;
namespace {
struct Pipeline {
  Fixture fixture;
  CompiledProgram program;
  Database database;
  Relation before,after;
  typed::Output expected;
  std::string prefix;
  explicit Pipeline(bool indexed):fixture(indexed,1),program(CompiledProgram::standalone(fixture.query.test.plan)) {
    database.tables.resize(1);for(std::size_t i=0;i<2;++i){fixture.commit(i);static_cast<void>(fixture.query.session->deliver_local_epoch());apply(database,fixture.query.test.updates[i]);}
    fixture.query.session->rotate_generation();before=typed::oracle(fixture.query.test,database);auto next=database;apply(next,fixture.query.test.updates[2]);after=typed::oracle(fixture.query.test,next);expected=typed::difference(before,after);prefix=contents(fixture.path);
    check(expected.size()==3,"loop-edge fixture did not exercise both aliases and new-new output");
  }
  QuerySession& session(){return *fixture.query.session;}
  void offer(){typed::enqueue(session(),io::InputEvent{fixture.query.test.updates[2],io::SourcePosition{"feed",30}});}
  void begin(){check(session().begin_next(),"durable loop-edge input missing");}
  void restore(){fixture.query.session.reset();fixture.query.session=QuerySession::restore_generation_with_local_sink(program,fixture.query.name,generation_test::recovery_options(),fixture.path,options());}
  void unchanged() {
    check(session().status().committed_sequence==2 && session().progress().sequence==2 && session().local_sink_state().persisted.sequence==2 &&
        session().progress().source_positions.at("feed")==20 && contents(fixture.path)==prefix,"private fan-out changed native/source/durable output boundary");
  }
  void recover(bool committed,bool pending) {
    restore();const auto stored=session().local_sink_state().persisted.sequence;check(stored>=2 && stored<=(committed?3U:2U) && contents(fixture.path).substr(0,prefix.size())==prefix,"restart changed accepted output prefix");
    check(session().status().committed_sequence==(committed?3U:2U) && session().progress().sequence==(committed?3U:2U) && typed::rows(session())==(committed?after:before) &&
        session().progress().source_positions.at("feed")== (committed?30U:20U) && session().recovery_status().pending_input_sequence.has_value()==pending,"restart recovered half-applied fan-out or wrong retained input");
    session().start();if(!committed){if(!pending)offer();begin();finish(session());}
    const auto delivered=session().deliver_local_epoch();check(delivered.kind==(stored==3?LocalDeliveryKind::idle:LocalDeliveryKind::published) &&
        (stored==3 || (delivered.sequence==3 && delivered.generation==2)) && output(session().read_local_epoch(3))==expected &&
        typed::rows(session())==after && session().progress().sequence==3 && session().progress().source_positions.at("feed")==30,"fan-out replay lost/duplicated canonical whole-epoch output or source");
    next_and_retire(false);
  }
  void next_and_retire(bool queued) {
    apply(database,fixture.query.test.updates[2]);const auto old=typed::oracle(fixture.query.test,database);apply(database,fixture.query.test.updates[3]);const auto next=typed::oracle(fixture.query.test,database);
    if(queued){begin();finish(session());}else fixture.commit(3);
    static_cast<void>(session().deliver_local_epoch());check(typed::rows(session())==next && session().progress().sequence==4 && session().progress().source_positions.at("feed")==40 && output(session().read_local_epoch(4))==typed::difference(old,next),"fan-out retry changed next update");
    session().retire_generation_history();restore();check(session().generation_state().selected.first_generation==2 && session().local_sink_receipt().sequence()==4 && session().progress().source_positions.at("feed")==40 && typed::rows(session())==next,"fan-out retry/checkpoint/sink retirement restart lost committed state");
  }
  void retry(bool pending=true){recover(false,pending);}
};
std::size_t steps(bool indexed) {
  Pipeline f(indexed);f.offer();f.begin();std::size_t count=0;while(++count<10000)if(f.session().step()==DeltaStep::prepared)return count;
  throw std::runtime_error("bounded fan-out calibration did not prepare");
}
void cancellations(bool indexed) {
  const auto count=steps(indexed);
  for(std::size_t prefix=0;prefix<=count;++prefix) {
    Pipeline f(indexed);f.offer();f.begin();for(std::size_t step=0;step<prefix;++step)static_cast<void>(f.session().step());f.unchanged();
    bool hidden=false;try{static_cast<void>(f.session().deliver_local_epoch());}catch(const Error&){hidden=true;}check(hidden,"private self-join output reached durable sink");
    hidden=false;try{static_cast<void>(f.session().next_output());}catch(const Error&){hidden=true;}check(hidden,"private self-join output reached ordinary transfer");
    f.session().pause();f.session().stop();f.unchanged();check(typed::rows(f.session())==f.before,"fan-out cancellation did not roll back whole native epoch");f.retry();
  }
  std::cout<<"durable pipeline indexed="<<indexed<<" private prefixes="<<count+1<<" pause/stop/whole-native rollback/sink invisibility/replay/next update/retirement passed\n";
}
void allocations(bool indexed) {
  std::size_t count=0;{Pipeline f(indexed);f.offer();{s04_alloc::Scope scope;f.begin();finish(f.session());count=s04_alloc::calls;}}
  std::size_t cached=0;
  for(std::size_t point=0;point<count;++point) {
    const auto ambient=descriptors();Pipeline f(indexed);f.offer();bool failed=false;
    {s04_alloc::Scope scope(static_cast<std::ptrdiff_t>(point));try{f.begin();finish(f.session());}catch(const std::bad_alloc&){failed=true;f.session().stop();}}
    check(failed,"durable fan-out allocation fault missed");f.unchanged();check(typed::rows(f.session())==f.before,"durable fan-out OOM published an alias prefix");
    const bool pending=f.session().journal_state().pending_input.has_value();if(pending)++cached;
    f.fixture.query.session.reset();check(descriptors()==ambient,"fan-out OOM retained query file ownership after destruction");f.retry(pending);
  }
  std::cout<<"durable pipeline indexed="<<indexed<<" allocation points="<<count<<" logged pending="<<cached<<" persistent OOM/whole-state rollback/no sink bytes/native recovery passed\n";
}
void crashes(bool indexed) {
  const auto count=steps(indexed);std::size_t cases=0;
  for(std::size_t prefix=0;prefix<=count+1;++prefix) {
    Pipeline f(indexed);f.fixture.query.session.reset();const auto child=::fork();check(child>=0,"durable fan-out fork failed");
    if(child==0){try{f.restore();f.session().start();f.offer();if(prefix){f.begin();for(std::size_t step=1;step<prefix;++step)static_cast<void>(f.session().step());}::_exit(77);}catch(...){::_exit(3);}}
    int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"durable fan-out process prefix missed");
    check(contents(f.fixture.path)==f.prefix,"process exit exposed an uncommitted self-join epoch");f.retry(prefix!=0);++cases;
  }
  std::cout<<"durable pipeline indexed="<<indexed<<" process exits="<<cases<<" each public preparation prefix/logged-input recovery/no partial sink/next update/retirement passed (not power loss)\n";
}
enum class WriterPhase {input,decision,sink};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;bool after=false;
  void visit(bool done) noexcept {if(!done)++count;if(count==crash && done==after)::_exit(77);}
  template<class T> T decision(bool done) const noexcept {T value;if(!done && count==fail){if(after)value.error_after=EIO;else value.error_before=EIO;}return value;}
  static recovery::journal::testing::FileDecision journal(const recovery::journal::testing::FileEvent& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<recovery::journal::testing::FileDecision>(event.after);}
  static sk::testing::Decision sink(const sk::testing::Event& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<sk::testing::Decision>(event.after);}
};
struct Installed {
  Installed(Hook& h,WriterPhase phase){if(phase==WriterPhase::sink)sk::testing::set_hook(Hook::sink,&h);else recovery::journal::testing::set_file_hook(Hook::journal,&h);}
  ~Installed(){sk::testing::set_hook(nullptr,nullptr);recovery::journal::testing::set_file_hook(nullptr,nullptr);}
};
void prepare(Pipeline& f,WriterPhase phase) {
  f.offer();if(phase!=WriterPhase::input){f.begin();while(f.session().step()!=DeltaStep::prepared){}if(phase==WriterPhase::sink)f.session().commit();}
}
void perform(Pipeline& f,WriterPhase phase){if(phase==WriterPhase::input)f.begin();else if(phase==WriterPhase::decision)f.session().commit();else static_cast<void>(f.session().deliver_local_epoch());}
Hook trace(bool indexed,WriterPhase phase){Pipeline f(indexed);prepare(f,phase);Hook h;{Installed installed(h,phase);perform(f,phase);}return h;}
std::pair<bool,bool> persisted(const Pipeline& f) {
  const auto log=generation_test::path(f.fixture.query.name,2,".wal"),bytes=contents(log);const auto state=recovery::journal::scan(bytes);check(state.physical_sequence==2 || state.physical_sequence==3,"writer fault produced an invalid native epoch");return {state.physical_sequence==3,state.pending.has_value()};
}
void writer_failures(bool indexed) {
  std::size_t cases=0;
  for(const auto phase:{WriterPhase::input,WriterPhase::decision}) {
    const auto baseline=trace(indexed,phase);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Pipeline f(indexed);prepare(f,phase);Hook h;h.fail=point;h.after=after;bool failed=false;
      {Installed installed(h,phase);try{perform(f,phase);}catch(const recovery::journal::FileFailure&){failed=true;}}
      check(failed && f.session().journal_state().recovery_required,"writer fault allowed uncertain continuation");f.unchanged();bool blocked=false;try{static_cast<void>(f.session().begin_next_result());}catch(const SessionJournalFailure&){blocked=true;}check(blocked,"unknown writer completion admitted more input");
      const auto [committed,pending]=persisted(f);f.recover(committed,pending);++cases;
    }
  }
  std::cout<<"durable pipeline indexed="<<indexed<<" writer errors="<<cases<<" every input/decision I/O boundary/actual native recovery/whole output/next update passed\n";
}
void sink_reopen(bool indexed) {
  const auto baseline=trace(indexed,WriterPhase::sink);std::size_t cases=0;
  for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
    Pipeline f(indexed);prepare(f,WriterPhase::sink);Hook h;h.fail=point;h.after=after;bool failed=false;
    {Installed installed(h,WriterPhase::sink);try{perform(f,WriterPhase::sink);}catch(const sk::Failure&){failed=true;}}
    const auto state=f.session().local_sink_state();check(failed && state.recovery_required && state.verified_sequence==2 && f.session().status().output_remaining==3 && f.session().progress().sequence==3,"sink error removed whole native output or advanced verification");
    const bool visible=contents(f.fixture.path).size()>f.prefix.size();const auto spent=state.delivery_work;const auto blocked=f.session().local_sink_state().blocked_inputs;
    typed::enqueue(f.session(),io::InputEvent{f.fixture.query.test.updates[3],io::SourcePosition{"feed",40}});
    for(unsigned i=0;i<4;++i)check(f.session().begin_next_result()==SessionBegin::would_block && f.session().progress().sequence==3 && f.session().progress().source_positions.at("feed")==30 && f.session().status().queue->events==1,"poisoned sink admitted or peeked at owned queued input");
    check(f.session().local_sink_state().blocked_inputs==blocked+4,"poisoned-sink backpressure did not hold admission");
    f.session().open_local_sink(f.fixture.path,options());check(!f.session().local_sink_state().recovery_required && f.session().local_sink_state().delivery_work==spent && f.session().local_sink_state().verified_sequence==2,"same-owner sink reopen refilled work or acknowledged unknown output");
    const auto delivery=f.session().deliver_local_epoch();check(delivery.kind==(visible?LocalDeliveryKind::duplicate:LocalDeliveryKind::published) && delivery.sequence==3 && output(f.session().read_local_epoch(3))==f.expected && f.session().status().output_remaining==0,"same-owner sink retry lost or duplicated fan-out output");
    check(f.session().status().queue->events==1,"same-owner reopen removed an admitted queued event");f.next_and_retire(true);++cases;
  }
  std::cout<<"durable pipeline indexed="<<indexed<<" same-owner sink errors="<<cases<<" poisoned backpressure/retained output/work/reopen/exact retry/native continuation passed\n";
}
void io_crashes(bool indexed) {
  std::size_t cases=0;
  for(const auto phase:{WriterPhase::input,WriterPhase::decision,WriterPhase::sink}) {
    const auto baseline=trace(indexed,phase);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Pipeline f(indexed);f.fixture.query.session.reset();const auto child=::fork();check(child>=0,"durable writer/sink fork failed");
      if(child==0){try{f.restore();f.session().start();prepare(f,phase);Hook h;h.crash=point;h.after=after;Installed installed(h,phase);perform(f,phase);}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"writer/sink process boundary missed");
      const auto [committed,pending]=persisted(f);f.recover(committed,pending);++cases;
    }
  }
  std::cout<<"durable pipeline indexed="<<indexed<<" I/O process exits="<<cases<<" every writer/sink boundary/actual native/source/whole output/retry/retirement passed (not power loss)\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected durable pipeline mode");for(const bool indexed:{false,true})if(std::string_view(argv[1])=="crash"){crashes(indexed);io_crashes(indexed);}else{cancellations(indexed);allocations(indexed);writer_failures(indexed);sink_reopen(indexed);}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
