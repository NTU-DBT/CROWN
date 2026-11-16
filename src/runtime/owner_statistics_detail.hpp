#pragma once
#include "crown/runtime/owner_statistics.hpp"
namespace crown::runtime::statistics::detail {
// Internal synchronous composition: request_ borrows the caller span; output_ owns
// captured values. budget_/account() reuse the existing capture/query allowances.
class OwnerBuilder {
 public:
  OwnerBuilder(OwnerStamp,const CompiledProgram&,OwnerRequestView,Limits,bool pending);
  bool active() const noexcept;
  const OwnerRequestView& request() const noexcept { return request_; }
  Component* append(const Selection&);
  void table(Component&,const storage::AccountedStorageTable&,const storage::TupleLayout&,storage::IndexWorkAllowance*);
  void index(Component&,const storage::AccountedStorageTable&,IndexId,const storage::Projection&,storage::IndexWorkAllowance*);
  Budget& budget() noexcept { return budget_; }
  const resource::MemoryAccount& account() const noexcept { return output_.plan().account(); }
  OwnerCapture finish();
 private:
  OwnerRequestView request_; Budget budget_; OwnerCapture output_;
};
}
