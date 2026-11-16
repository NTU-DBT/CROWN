#pragma once
#include "crown/runtime/owner_statistics.hpp"
namespace crown::runtime::statistics::detail {
// Internal owner-only composition; public clients receive read-only reports.
class OwnerBuilder {
 public:
  OwnerBuilder(OwnerStamp,const PhysicalPlan&,const OwnerRequest&,Limits,bool pending);
  bool active() const noexcept;
  const OwnerRequest& request() const noexcept { return request_; }
  Component* append(const Selection&);
  void table(Component&,const storage::ReferenceTable&);
  void index(Component&,const storage::ReferenceTable&,IndexId);
  Budget& budget() noexcept { return budget_; }
  OwnerCapture finish();
 private:
  const OwnerRequest& request_; Budget budget_; OwnerCapture output_;
};
}
