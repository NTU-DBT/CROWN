#pragma once

#include "crown/runtime/weighted.hpp"
#include "crown/api/error.hpp"
#include "storage_work.hpp"
#include <map>

// Internal shared state for maintenance and committed cursor translation units.
// It introduces no second owner, runtime registry, allocator or exception layer.
namespace crown::runtime::weighted_detail {
template<class T> using Vector=std::vector<T,resource::MemoryAllocator<T>>;
template<class T> using Map=std::map<TupleId,T,std::less<TupleId>,
    resource::MemoryAllocator<std::pair<const TupleId,T>>>;
inline void require(bool condition, std::string_view code, std::string_view message) {
  if (!condition) throw Error(std::string(code),std::string(message));
}
struct Node {
  resource::MemoryAttribution attribution;
  Map<weighted::RecordValue> records;
  Map<weighted::Multiplicity> messages, factors;
  Vector<std::size_t> children;
  std::size_t factor_begin=0, factor_end=0;
  Node(const resource::MemoryAccount&, NodeId, std::size_t arity);
  void lifetime(const void*, resource::AllocationLifetime) const;
};

// The exact existing iterative backtracking kernel, shared by the two native
// walkers. It opens no engine/reader/grant; select/close remain concrete methods.
template<class Walker, class Steps>
bool advance_visible(Walker& walker, const Steps& steps) {
  if (walker.resume) {walker.position=walker.frames.size()-1;walker.resume=false;}
  for (;;) {
    if (walker.position==walker.frames.size()) {walker.resume=true;return true;}
    auto& frame=walker.frames[walker.position];
    if (walker.select(frame,steps[walker.position])) ++walker.position;
    else {
      walker.close_frame(frame);
      if (!walker.position) return false;
      --walker.position;
    }
  }
}
} // namespace crown::runtime::weighted_detail

namespace crown::runtime {
struct WeightedRuntime::Impl {
  weighted::Options options;
  std::shared_ptr<detail::StorageWorkContext> context;
  CompiledProgram program;
  storage::AccountedPlanStorage storage;
  annotations::MultiplicityPolicy policy;
  weighted::Binding binding;
  weighted_detail::Vector<weighted_detail::Node> nodes;
  weighted_detail::Vector<std::optional<std::size_t>> incoming;
  weighted_detail::Vector<std::size_t> factor_slots;
  std::uint64_t sequence=0, readers=0;
  bool updating=false;
  std::optional<weighted::Attempt> last;

  Impl(CompiledProgram, weighted::Options, std::shared_ptr<detail::StorageWorkContext>);
  // Closed initial sequence belongs to a fresh unpublished owner only.
  Impl(CompiledProgram, weighted::Options, std::shared_ptr<detail::StorageWorkContext>,
      storage::AccountedPlanStorage, std::uint64_t initial_sequence);
  [[nodiscard]] const resource::MemoryAccount& account() const;
  [[nodiscard]] storage::IndexWorkAllowance* allowance() const;
  void readable() const;
  [[nodiscard]] weighted::Multiplicity summary() const noexcept;
  template<class Shape> static std::shared_ptr<Impl> create(const Shape&,weighted::Options,
      const resource::MemoryAccount& = {});
};
} // namespace crown::runtime
