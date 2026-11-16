#include "crown/runtime/combined_statistics.hpp"
#include "crown/api/error.hpp"

namespace crown::runtime::statistics {
struct CombinedCapture::Data {
  OwnerCapture state;
  ::crown::runtime::workload::Snapshot workload;
};
CombinedCapture::CombinedCapture(OwnerCapture state,::crown::runtime::workload::Snapshot events) {
  // Factory inputs have private construction authority; this also catches a
  // future owner-forwarding regression before publishing a mismatched pair.
  if(state.stamp().owner!=events.stamp().owner || state.stamp().sequence!=events.stamp().committed_epoch ||
      state.plan().physical_sha256()!=events.plan().physical_sha256() ||
      (state.availability()==Availability::pending_private_state)!=events.pending())
    throw Error("statistics_binding","state and workload captures do not describe one owner boundary");
  data_=std::make_shared<const Data>(Data{std::move(state),std::move(events)});
}
const OwnerCapture& CombinedCapture::state() const noexcept {return data_->state;}
const ::crown::runtime::workload::Snapshot& CombinedCapture::workload() const noexcept {return data_->workload;}
}
namespace crown::runtime {
statistics::CombinedCapture SupportRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  auto state=capture_statistics(request,limits);auto events=workload_statistics();
  return statistics::CombinedCapture(std::move(state),std::move(events));
}
statistics::CombinedCapture PhysicalRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  auto state=capture_statistics(request,limits);auto events=workload_statistics();
  return statistics::CombinedCapture(std::move(state),std::move(events));
}
statistics::CombinedCapture DeltaRuntime::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  auto state=capture_statistics(request,limits);auto events=workload_statistics();
  return statistics::CombinedCapture(std::move(state),std::move(events));
}
}
