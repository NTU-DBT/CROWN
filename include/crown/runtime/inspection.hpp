#pragma once

#include "crown/ir/model.hpp"
#include "crown/ir/tree.hpp"
#include "crown/storage/accounted_row.hpp"
#include "crown/resource/owner_allocator.hpp"

namespace crown::runtime {
enum class InvariantComponent {
  source,derivation,record,survivor,parent,visible,sequence,storage,
  live_factor,live_parent,live_child,live_totals
};
enum class InvariantCode {
  missing_record,unexpected_record,missing_metadata,orphan_metadata,
  child_presence,satisfied_count,support_count,derivation_count,membership,
  sequence,storage,invalid_source,aggregate_count
};
inline constexpr resource::MemoryAttribution invariant_attribution{resource::MemoryOwnerKind::capture,15};
// Localized diagnostic keys retain compact values under their original query
// account. Copies deep-copy under that same account; moves/release allocate
// nothing. Explicit writers can export ordinary caller-owned scalar values.
class InvariantKey {
 public:
  InvariantKey() noexcept=default;
  InvariantKey(const InvariantKey& other):account_(other.account_) {
    if(!other.row_.empty())row_=other.row_.clone(account_,invariant_attribution);
  }
  InvariantKey& operator=(const InvariantKey& other) {
    if(this!=&other){InvariantKey copy(other);*this=std::move(copy);}return *this;
  }
  InvariantKey(InvariantKey&&) noexcept=default;
  InvariantKey& operator=(InvariantKey&&) noexcept=default;
  [[nodiscard]] static InvariantKey copy_of(const resource::MemoryAccount& account,storage::RowView values) {
    InvariantKey out;out.account_=account;
    if(!values.empty())out.row_=storage::AccountedRow::copy_of(account,values,invariant_attribution);
    return out;
  }
  [[nodiscard]] storage::RowView view() const & noexcept{return row_.view();}
  storage::RowView view() const &&=delete;
  [[nodiscard]] const resource::MemoryAccount& account() const & noexcept{return account_;}
  const resource::MemoryAccount& account() const &&=delete;
  [[nodiscard]] bool operator==(const Row& other) const{return row_.view()==other;}
  [[nodiscard]] bool operator==(const InvariantKey& other) const noexcept{return row_.view()==other.row_.view();}
 private:
  resource::MemoryAccount account_;
  storage::AccountedRow row_;
};
struct InvariantIssue {
  InvariantCode code;
  InvariantComponent component;
  std::optional<TableId> table=std::nullopt;
  std::optional<OccurrenceId> occurrence=std::nullopt;
  std::optional<NodeId> node=std::nullopt;
  std::optional<std::size_t> child_slot=std::nullopt;
  InvariantKey key;
  std::optional<std::uint64_t> expected=std::nullopt,actual=std::nullopt;
};
struct InspectionOptions {
  std::optional<std::uint64_t> work_limit=1000000;
  std::size_t issue_limit=128;
};
struct RuntimeStateStatistics {
  std::size_t source_rows=0,derivation_keys=0,native_records=0,generalized_records=0;
  std::size_t survivors=0,parent_keys=0,visible_keys=0,child_flags=0;
  std::size_t source_storage_records=0,support_storage_records=0,index_memberships=0;
  std::size_t live_rows=0,live_parent_rows=0,live_child_rows=0;
  std::size_t live_parent_buckets=0,live_child_buckets=0;
};
struct InvariantReport {
  // Copies duplicate funded issue/key payload; moves transfer its actual owner.
  // valid() checks these public flags only; it does not authenticate an inspection.
  bool complete=true;
  std::uint64_t work=0;
  RuntimeStateStatistics statistics;
  std::vector<InvariantIssue,resource::OwnerAllocator<InvariantIssue>> issues;
  InvariantReport()=default;
  explicit InvariantReport(const resource::MemoryAccount& account)
      :issues(resource::OwnerAllocator<InvariantIssue>(account,resource::MemoryPurpose::capture,invariant_attribution)) {}
  [[nodiscard]] bool valid() const noexcept { return complete && issues.empty(); }
};
struct CanonicalCount {
  Row key;
  std::uint64_t count;
  bool operator==(const CanonicalCount&) const=default;
};
struct CanonicalRecord {
  Row values;
  std::size_t satisfied;
  std::vector<bool> child_present;
  bool survives;
  bool operator==(const CanonicalRecord&) const=default;
};
struct CanonicalNode {
  NodeId node;
  NodeKind kind;
  std::vector<CanonicalRecord> records;
  Relation survivors;
  std::vector<CanonicalCount> parent;
  std::optional<std::vector<CanonicalCount>> visible;
  bool operator==(const CanonicalNode&) const=default;
};
struct CanonicalSupportState {
  // Explicit ordinary DTO: copying nested rows/strings/containers may allocate.
  // Hash/arithmetic labels do not admit native state or carry proof authority.
  std::string physical_sha256;
  std::uint64_t catalog_version,sequence;
  bool has_answer;
  std::vector<CanonicalNode> nodes;
  std::string arithmetic="exact-nonnull-v1";
  bool operator==(const CanonicalSupportState&) const=default;
};
struct CanonicalPhysicalState {
  CanonicalSupportState support;
  std::uint64_t sequence;
  std::vector<Relation> sources;
  std::vector<std::vector<CanonicalCount>> derivations;
  bool operator==(const CanonicalPhysicalState&) const=default;
};
struct CanonicalBucket {
  Row key;
  std::uint64_t count;
  Relation rows;
  bool operator==(const CanonicalBucket&) const=default;
};
struct CanonicalLiveFactor {
  NodeId node;
  Relation rows;
  std::vector<CanonicalBucket> parents,children;
  bool operator==(const CanonicalLiveFactor&) const=default;
};
struct CanonicalLiveState {
  std::uint64_t sequence;
  std::vector<CanonicalLiveFactor> factors;
  std::size_t rows,parent_rows,child_rows;
  bool operator==(const CanonicalLiveState&) const=default;
};
struct CanonicalDeltaState {
  CanonicalPhysicalState physical;
  bool delta_maintained,sql_view;
  std::optional<CanonicalLiveState> live;
  bool operator==(const CanonicalDeltaState&) const=default;
};
}  // namespace crown::runtime
