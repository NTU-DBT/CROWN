#pragma once
#include "crown/runtime/owner_statistics.hpp"
#include "crown/runtime/workload_statistics.hpp"

namespace crown::runtime { class QuerySession; }
namespace crown::runtime::statistics {
// One synchronous actual-owner read under the native single-writer contract.
// The availability/interval domains stay independent. Captured keys own copies;
// no live source-row pins, mutable owner pointers, cursors or leases are retained.
class CombinedCapture {
 public:
  CombinedCapture(const CombinedCapture&) noexcept=default;
  CombinedCapture(CombinedCapture&& other) noexcept:data_(other.data_) {}
  CombinedCapture& operator=(const CombinedCapture&) noexcept=default;
  CombinedCapture& operator=(CombinedCapture&& other) noexcept {data_=other.data_;return *this;}
  const OwnerCapture& state() const noexcept;
  const ::crown::runtime::workload::Snapshot& workload() const noexcept;
  static constexpr std::uint32_t format_version=1;
 private:
  friend class ::crown::runtime::SupportRuntime;
  friend class ::crown::runtime::PhysicalRuntime;
  friend class ::crown::runtime::DeltaRuntime;
  friend class ::crown::runtime::QuerySession;
  CombinedCapture(OwnerCapture,::crown::runtime::workload::Snapshot);
  struct Data;
  std::shared_ptr<const Data> data_;
};
}
