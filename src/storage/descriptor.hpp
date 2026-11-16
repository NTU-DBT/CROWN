#pragma once
#include "crown/storage/layout.hpp"

namespace crown::storage::detail {
struct DescriptorEquality {FieldId first,repeated;};
// Shared handles keep the original concrete control block/deleter. Compiler
// descriptors own standard storage; runtime descriptors own accounted blocks.
// These bases expose only immutable ranges, so a runtime view needs no mirror.
struct LayoutDescriptor {
  LayoutId layout_id{0};
  std::span<const Field> field_view;
  LayoutContextView context_view{1,{}};
  std::optional<LayoutOrigin> origin_value;
  std::span<const DescriptorEquality> equality_view;
  Tuple (*make_native_tuple)(const TupleLayout&,TupleValuesView)=nullptr;
};
struct ProjectionDescriptor {
  TupleLayout source,target;
  std::span<const FieldId> field_view;
  Tuple (*apply_native_tuple)(const Projection&,const Tuple&)=nullptr;
  ProjectionDescriptor(TupleLayout from,TupleLayout to) noexcept:source(std::move(from)),target(std::move(to)) {}
};
} // namespace crown::storage::detail
