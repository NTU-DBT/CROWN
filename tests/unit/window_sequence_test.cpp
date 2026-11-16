#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"
#include "runtime_probe.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
using namespace crown;
using namespace crown::runtime;
void check(bool yes,const char* message) { if (!yes) throw std::runtime_error(message); }
PhysicalPlan plan() {
  Catalog c{1,{{"R",{{"x",ScalarType::int64}}}}};
  Query q{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
  FreeConnexTree t{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  return planner::lower_tree(c,q,t);
}
void enqueue(QuerySession& session,io::WindowCommand command) {
  std::vector<io::InputItem> items; items.emplace_back(std::move(command));
  io::TransportBatch batch(std::move(items));
  check(session.enqueue(batch)==io::Admission::accepted,"sequence fixture admission failed");
}
void commit_next(QuerySession& session) {
  check(session.begin_next_result()==SessionBegin::pending,"expected a prepared source step");
  while (session.step()!=DeltaStep::prepared) {}
  session.commit();
  while (session.next_output()) {}
}
void run() {
  WindowOptions options; options.managed_tables={TableId{0}}; options.width=10;
  auto session=QuerySession::create_windowed(plan(),options); session->start();
  enqueue(*session,{1,io::WindowInsert{1,TableId{0},{std::int64_t{7}},0},io::SourcePosition{"window",10}});
  commit_next(*session);
  const auto maximum=std::numeric_limits<std::uint64_t>::max();
  // Only the testing archive defines this setup: all real support/physical/
  // live/window/session sequence tags agree. No production seed API exists.
  RuntimeTestProbe::seed_session_physical_sequence(*session,maximum);

  enqueue(*session,{2,io::WindowInsert{2,TableId{0},{std::int64_t{7}},0},io::SourcePosition{"window",20}});
  commit_next(*session);
  check(session->status().committed_sequence==maximum && session->progress().sequence==2,
      "duplicate-row label incorrectly required or advanced physical sequence");
  enqueue(*session,{3,io::WindowWithdraw{1},io::SourcePosition{"window",30}});
  commit_next(*session);
  check(session->status().committed_sequence==maximum && session->snapshot().rows.size()==1,
      "count-only withdrawal changed physical sequence or deleted a supported row");
  enqueue(*session,{4,io::AdvanceWatermark{0},io::SourcePosition{"window",40}});
  commit_next(*session);
  check(session->status().committed_sequence==maximum && session->progress().sequence==4,
      "empty watermark could not commit at physical sequence maximum");

  enqueue(*session,{5,io::WindowWithdraw{2},io::SourcePosition{"window",50}});
  const auto before=*session->window_state();
  const auto before_progress=session->progress();
  try {
    static_cast<void>(session->begin_next_result());
    throw std::runtime_error("physical sequence exhaustion accepted an actual deletion");
  } catch (const Error& failure) {
    check(failure.code()=="resource_limit","physical exhaustion had the wrong error category");
  }
  check(!session->status().input_failed && session->status().phase==SessionPhase::ready,
      "physical exhaustion poisoned or retained private input");
  check(*session->window_state()==before && session->progress()==before_progress &&
      session->snapshot().rows.size()==1,"physical exhaustion changed the committed prefix");
  check(session->status().queue->events==1,"exhaustion released the retryable source head");

  RuntimeTestProbe::seed_session_physical_sequence(*session,maximum-1);
  commit_next(*session);
  check(session->snapshot().rows.empty() && session->progress().sequence==5 &&
      session->status().committed_sequence==maximum,"same cached physical deletion did not retry at the boundary");
  enqueue(*session,{6,io::AdvanceWatermark{100},io::SourcePosition{"window",60}});
  commit_next(*session); session->finish_input();
  check(session->begin_next_result()==SessionBegin::end && session->progress().sequence==6 &&
      session->status().window->completed_watermark==100 &&
      session->status().committed_sequence==maximum,"final metadata barrier was confused with physical exhaustion");
}
}
int main() {
  try { run(); std::cout<<"window physical sequence boundary passed\n"; }
  catch (const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
