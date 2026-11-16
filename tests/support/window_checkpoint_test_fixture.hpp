#pragma once
#include "crown/runtime/session_checkpoint.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <thread>
namespace crown::window_checkpoint_test {
using namespace crown;
using namespace crown::runtime;
inline void check(bool value,const char* message){if(!value)throw std::runtime_error(message);}
using Output=std::set<std::pair<SetOperation,Row>>;
inline PhysicalPlan plan(bool indexed) {
  Catalog catalog{9,{{"r",{{"x",ScalarType::int64}}},{"s",{{"x",ScalarType::int64}}}}};
  Query query{{{"x",ScalarType::int64}},{{"r",TableId{0},{VariableId{0}}}},{{VariableId{0},"x"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0}},{},0,{}}},{},{}};
  return planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
}
// Spare capacity seven is deliberate copy/checkpoint accounting coverage.
inline WindowOptions config(WindowFifoPolicy fifo) {
  WindowOptions result;result.managed_tables.reserve(7);result.managed_tables={TableId{0},TableId{1}};result.width=10;result.fifo=fifo;return result;
}
inline void grant(const QuerySession& session,bool indexed) {
#ifdef CROWN_RUNTIME_TESTING
  const auto value=RuntimeTestProbe::index_work(session);
  check(indexed?(value && value->fresh_operations==1):!value,"window session restore refilled indexed admission");
#else
  static_cast<void>(session);static_cast<void>(indexed);
#endif
}
inline Relation rows(const QuerySession& session) {
  const auto snapshot=session.snapshot();Relation result;
  for(const auto& row:snapshot.rows)check(result.insert(storage::export_row(row.values())).second,"duplicate window result");
  return result;
}
inline void enqueue(QuerySession& session,io::WindowCommand command) {
  command.source_position=io::SourcePosition{"window",command.sequence*10};io::TransportBatch batch({std::move(command)});
  check(session.enqueue(batch)==io::Admission::accepted && batch.empty(),"window command not admitted");
}
inline Output finish(QuerySession& session) {
  while(session.step()!=DeltaStep::prepared){}session.commit();Output result;std::uint64_t ordinal=0;
  while(auto value=session.next_output()) {
    check(value->ordinal==++ordinal && result.emplace(value->operation,storage::export_row(value->tuple.values())).second,"duplicate/noncontiguous window delta");
  }
  return result;
}
// One command may span epochs; signed-set union is not a counted delivery oracle.
inline Output command(QuerySession& session,io::WindowCommand value) {
  const auto sequence=value.sequence;enqueue(session,std::move(value));Output result;
  do {
    check(session.begin_next(),"window command disappeared");const auto output=finish(session);result.insert(output.begin(),output.end());
  }while(session.progress().sequence<sequence);
  return result;
}
io::WindowCommand insertion(std::uint64_t sequence,std::uint64_t label,TableId table,std::int64_t value,std::uint64_t timestamp) {
  return {sequence,io::WindowInsert{label,table,{value},timestamp},{}};
}
inline void seed(QuerySession& session) {
  session.start();command(session,insertion(1,1,TableId{0},1,0));command(session,insertion(2,2,TableId{0},1,1));
  command(session,{3,io::WindowWithdraw{1},{}});command(session,insertion(4,3,TableId{1},2,2));command(session,{5,io::AdvanceWatermark{2},{}});
}
template<class Action> void rejected(Action action) {
  bool failed=false;try{action();}catch(const recovery::ImageFailure&){failed=true;}catch(const Error&){failed=true;}
  check(failed,"inconsistent session state accepted");
}
} // namespace crown::window_checkpoint_test
