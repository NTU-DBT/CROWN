#pragma once
#include "crown/runtime/memory_report.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>

namespace crown::runtime::memory::detail {
inline constexpr resource::MemoryAttribution report_owner{resource::MemoryOwnerKind::capture,14};
template<class T> resource::OwnerAllocator<T> allocator(const resource::MemoryAccount& account) {
  return resource::OwnerAllocator<T>(account,resource::MemoryPurpose::capture,report_owner);
}
struct Failure {Stop stop;};
// Numeric report arrays retain the original account; no live table/owner pointer escapes.
struct Data {
  resource::MemoryAccount account;
  Snapshot snapshot;
  Vector<resource::AttributedMemoryStatistics> owners;
  Vector<Table> tables;
  Vector<Operator> operators;
  Usage usage;
  Data(const resource::MemoryAccount& a,Layer layer,Availability availability,std::uint64_t owner,std::uint64_t sequence,std::string_view hash)
      :account(a),snapshot{layer,availability,owner,sequence,{},{}},owners(allocator<resource::AttributedMemoryStatistics>(a)),
       tables(allocator<Table>(a)),operators(allocator<Operator>(a)) {
    if(hash.size()!=snapshot.physical_sha256.size())throw Failure{Stop::inconsistent};
    std::copy(hash.begin(),hash.end(),snapshot.physical_sha256.begin());
  }
};
// Usage is borrowed from the enclosing Attempt and must outlive this builder.
// finish reconciles actual account ledgers after releasing diagnostic scratch.
class Builder {
 public:
  explicit Builder(const resource::MemoryAccount&,Layer,Availability,std::uint64_t,std::uint64_t,std::string_view,Limits,Usage&);
  void work(std::uint64_t=1);
  void table(TableScope,const storage::AccountedStorageTable&,RelationRole,std::optional<NodeId> = {},std::optional<TableId> = {});
  void operation(Operator);
  std::uint64_t records(TableScope,RelationId);
  static std::uint64_t add(std::uint64_t,std::uint64_t);
  Report finish();
 private:
  std::shared_ptr<Data> data_;
  Limits limits_;
  Usage& usage_;
};
struct Access {
  static void append(Builder&,const SupportRuntime&);
  static void append(Builder&,const PhysicalRuntime&);
  static void append(Builder&,const DeltaRuntime&);
  static Attempt capture(const SupportRuntime&,Limits) noexcept;
  static Attempt capture(const PhysicalRuntime&,Limits) noexcept;
  static Attempt capture(const DeltaRuntime&,Limits) noexcept;
  static Attempt capture(const QuerySession&,Limits) noexcept;
};
// One best-effort noexcept boundary: never publish a partial reconciled report.
template<class Function> Attempt attempt(Function function) noexcept {
  Attempt out;
  try {out.report=function(out.usage);out.stop=Stop::complete;}
  catch(const Failure& e){out.stop=e.stop;}
  catch(const resource::MemoryFailure& e){out.stop=e.fault()==resource::MemoryFault::overflow?Stop::overflow:
      e.fault()==resource::MemoryFault::contract?Stop::inconsistent:Stop::allocation_failure;}
  catch(const std::bad_alloc&){out.stop=Stop::allocation_failure;}
  catch(...){out.stop=Stop::inconsistent;}
  return out;
}
} // namespace crown::runtime::memory::detail
