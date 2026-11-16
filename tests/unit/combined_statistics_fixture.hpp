#pragma once
#include "owner_statistics_fixture.hpp"
#include "workload_statistics_fixture.hpp"
#include "crown/runtime/combined_statistics.hpp"

namespace combined_fixture {
using namespace owner_fixture;
namespace wf=workload_fixture;
namespace ws=crown::runtime::workload;
inline void binding(const stats::CombinedCapture& report,std::uint64_t sequence,bool pending=false){
  check(report.state().stamp().owner==report.workload().stamp().owner);
  check(report.state().stamp().sequence==sequence && report.workload().stamp().committed_epoch==sequence);
  check(report.state().plan().physical_sha256()==report.workload().plan().physical_sha256());
  check((report.state().availability()==stats::Availability::pending_private_state)==pending);
  check(report.workload().pending()==pending);
}
inline void facts(const stats::CombinedCapture& report,const Database& db,std::uint64_t sequence){
  binding(report,sequence);fixture_facts(report.state(),db);
}
inline void same_workload(const ws::Snapshot& a,const ws::Snapshot& b){
  check(a.stamp().owner==b.stamp().owner && a.stamp().committed_epoch==b.stamp().committed_epoch);
  check(a.stamp().configuration_generation==b.stamp().configuration_generation && a.stamp().reset_generation==b.stamp().reset_generation && a.stamp().segment==b.stamp().segment);
  check(a.metadata().attempts==b.metadata().attempts && a.metadata().committed==b.metadata().committed && a.metadata().aborted==b.metadata().aborted);
  check(a.metadata().guards==b.metadata().guards && a.metadata().detail_actions==b.metadata().detail_actions);
  check(a.options()==b.options() && a.modes()==b.modes() && a.previous_modes()==b.previous_modes());
  check(wf::same_cells(a.cells(),b.cells()) && wf::same_cells(a.previous_cells(),b.previous_cells()));
  check(a.has_previous()==b.has_previous() && a.pending()==b.pending());
}
}
