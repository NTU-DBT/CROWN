#pragma once

#include <compare>
#include <cstddef>
#include <cstdint>

namespace crown {
// Plan/catalog ID wrappers carry scalar values scoped to a compiled document;
// they do not check range or establish that a value belongs to that document.
struct TableId { std::size_t value; auto operator<=>(const TableId&) const = default; };
struct ColumnId { std::size_t value; auto operator<=>(const ColumnId&) const = default; };
struct VariableId { std::size_t value; auto operator<=>(const VariableId&) const = default; };
struct OccurrenceId { std::size_t value; auto operator<=>(const OccurrenceId&) const = default; };
struct NodeId { std::size_t value; auto operator<=>(const NodeId&) const = default; };
struct RelationId { std::size_t value; auto operator<=>(const RelationId&) const = default; };
struct LayoutId { std::size_t value; auto operator<=>(const LayoutId&) const = default; };
struct FieldId { std::size_t value; auto operator<=>(const FieldId&) const = default; };
struct IndexRequirementId { std::size_t value; auto operator<=>(const IndexRequirementId&) const = default; };
// Runtime IDs are monotonic within one storage owner; zero is not allocated.
struct TupleId { std::uint64_t value; auto operator<=>(const TupleId&) const = default; };
struct IndexId { std::uint64_t value; auto operator<=>(const IndexId&) const = default; };
struct StorageOwnerId { std::uint64_t value; auto operator<=>(const StorageOwnerId&) const = default; };
// Arena slots may be reused. Their allocation identity includes a generation;
// logical TupleId values above remain independent and monotonic.
struct ArenaOwnerId { std::uint64_t value; auto operator<=>(const ArenaOwnerId&) const = default; };
struct TupleSlotId { std::size_t value; auto operator<=>(const TupleSlotId&) const = default; };
struct ArenaHandle {
  ArenaOwnerId owner;
  TupleSlotId slot;
  std::uint64_t generation;
  auto operator<=>(const ArenaHandle&) const = default;
};
struct TupleHandle {
  StorageOwnerId owner;
  RelationId relation;
  TupleId tuple;
  auto operator<=>(const TupleHandle&) const = default;
};
}  // namespace crown
