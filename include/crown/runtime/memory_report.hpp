#pragma once

#include "crown/storage/accounted_table.hpp"
#include "crown/ir/physical.hpp"
#include "crown/resource/owner_allocator.hpp"
#include <array>
#include <optional>
#include <variant>

namespace crown::runtime {class SupportRuntime;class PhysicalRuntime;class DeltaRuntime;class QuerySession;}
namespace crown::runtime::memory {
namespace detail {struct Data;struct Access;class Builder;}
enum class Layer {support,physical,delta,session};
enum class Availability {committed,pending,released};
enum class Stop {complete,invalid_handle,work_limit,owner_limit,table_limit,operator_limit,allocation_failure,overflow,inconsistent};
struct Limits {
  std::uint64_t work=16'000'000;
  std::size_t owners=65'536,tables=65'536,operators=65'536;
};
struct Usage {std::uint64_t work=0;std::size_t owners=0,tables=0,operators=0;};
struct Snapshot {
  Layer layer;
  Availability availability;
  std::uint64_t runtime_owner=0,sequence=0;
  std::array<char,64> physical_sha256{};
  resource::MemoryStatistics account;
};
enum class TableScope {support,physical_source};
struct Table {
  TableScope scope;
  RelationId relation;
  RelationRole role;
  std::optional<NodeId> node;
  std::optional<TableId> base;
  StorageOwnerId storage_owner;
  storage::StorageBackend backend;
  std::uint64_t live_records;
  storage::AccountedStorageTable::MemoryStatistics memory;
};
struct SupportNode {
  NodeId node;
  resource::MemoryAttribution attribution;
  std::uint64_t records,survivors,parent_keys;
  std::optional<std::uint64_t> visible_keys;
  std::uint64_t child_flags;
};
struct Derivations {
  OccurrenceId occurrence;
  resource::MemoryAttribution attribution;
  std::uint64_t keys;
};
struct FactorCounts {std::uint64_t rows,parent_keys,parent_rows,child_keys,child_rows;};
struct DeltaFactor {
  NodeId node;
  resource::MemoryAttribution attribution;
  std::optional<FactorCounts> materialized;
};
struct Coordinator {Layer layer;resource::MemoryAttribution attribution;};
using Operator=std::variant<SupportNode,Derivations,DeltaFactor,Coordinator>;
template<class T> using Vector=std::vector<T,resource::OwnerAllocator<T>>;
// The allocation partition is account-wide, including held generations, reports,
// cursors and outputs. Operator counts describe only the recorded committed
// runtime. Owner keys may be shared by bindings; bytes occur once in owners().
class Report {
  // Copies and copy-like moves share actual funded arrays; views borrow Data.
  // The last owner frees those arrays/control; getters do not recapture memory.
 public:
  Report(const Report&) noexcept=default;
  Report& operator=(const Report&) noexcept=default;
  Report(Report&& other) noexcept:data_(other.data_) {}
  Report& operator=(Report&& other) noexcept {data_=other.data_;return *this;}
  const Snapshot& snapshot() const noexcept;
  const Vector<resource::AttributedMemoryStatistics>& owners() const noexcept;
  const Vector<Table>& tables() const noexcept;
  const Vector<Operator>& operators() const noexcept;
  const Usage& usage() const noexcept;
  const resource::MemoryAccount& account() const & noexcept;
  const resource::MemoryAccount& account() const &&=delete;
  static constexpr unsigned format_version=1;
 private:
  friend class detail::Builder;
  explicit Report(std::shared_ptr<const detail::Data> data) noexcept:data_(std::move(data)) {}
  std::shared_ptr<const detail::Data> data_;
};
struct Attempt {Stop stop=Stop::inconsistent;std::optional<Report> report;Usage usage;};
[[nodiscard]] Attempt capture(const SupportRuntime&,Limits={}) noexcept;
[[nodiscard]] Attempt capture(const PhysicalRuntime&,Limits={}) noexcept;
[[nodiscard]] Attempt capture(const DeltaRuntime&,Limits={}) noexcept;
[[nodiscard]] Attempt capture(const QuerySession&,Limits={}) noexcept;
} // namespace crown::runtime::memory
