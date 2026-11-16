#pragma once

#include "crown/ir/update_pattern.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>

namespace crown::patterns::detail {
// Attribution identifies this component inside the original query cap.
inline constexpr resource::MemoryAttribution owner{resource::MemoryOwnerKind::capture, 16};
template<class T> using Vector = std::vector<T, resource::OwnerAllocator<T>>;
template<class T> resource::OwnerAllocator<T> allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::capture) {
  return resource::OwnerAllocator<T>(account, purpose, owner);
}
inline void require(bool value) {
  if (!value) throw Failure(Fault::invalid_declaration);
}
// Store a canonical, immutable declaration; no observed row history is retained.
struct Data {
  std::array<char, 64> source;
  std::uint64_t tables = 0;
  bool constrained = false;
  Usage usage;
  Vector<TableRule> rules;
  Data(const resource::MemoryAccount& account, std::array<char, 64> hash, std::uint64_t count)
      : source(hash), tables(count), rules(allocator<TableRule>(account)) {}
};
// One validated builder and one already-validated account transfer, without a
// generic callback framework or another exception translation layer.
struct Factory {
  static Declaration make(const resource::MemoryAccount&, std::array<char, 64>, std::uint64_t,
      std::span<const TableRule>, const Limits&);
  static Declaration copy(const resource::MemoryAccount&, const Declaration&);
};
} // namespace crown::patterns::detail
