#pragma once

#include "crown/ir/physical.hpp"
#include "crown/storage/accounted_table.hpp"
#include <array>

namespace crown::runtime::detail { class SqlColdRebuild; }
namespace crown::storage {
// Immutable compilation borrows its own fixed-diagnostic work grant. Indexed
// execution checks the advertised operation cap; reference execution is not
// metered by IndexWork. No factory creates a replacement execution grant.
enum class MetadataWork { execution, compiler };
namespace detail { class AccountedPlanStorageTesting; }
struct PlanStorageMemoryStatistics {
  std::size_t layouts = 0, relations = 0, index_bindings = 0;
  resource::AttributedMemoryStatistics shared_metadata;
  resource::AttributedMemoryStatistics instance;
  // Sum of these two attribution owners, once each. Table payloads and shared
  // tokens attributed to another owner are excluded. Collecting these snapshots
  // scans all live account allocations twice; this is an explicit report.
  resource::MemoryUsage owned;
  auto operator<=>(const PlanStorageMemoryStatistics&) const = default;
};

// Native storage binding. Constructor spans are borrowed only during import;
// the binding retains funded immutable layouts/projections and numeric identity.
// AccountedPlanStorage adds mutable native tables; CompiledProgram separately
// owns executable metadata under the same account. No borrowed plan is retained.
class AccountedPlanStorage {
  struct Metadata;
  struct Inputs {
    PhysicalRoute route;
    std::string_view identity, guarantee;
    std::span<const TupleLayout> layouts;
    std::span<const PhysicalRelation> relations;
    std::span<const IndexRequirement> indexes;
    std::optional<IndexedBackendSpec> indexed;
    std::uint8_t collision_profile = 0; // Test shim only; public plan constructor always uses zero.
  };
 public:
  struct RelationBinding {
    RelationRole role;
    LayoutId layout;
    std::optional<NodeId> node;
    std::optional<TableId> base;
  };
  struct FrozenIndexBinding {RelationId relation;AccountedProjection projection;};
  // Immutable binding ownership without retaining any mutable table instance.
  // Rebuilds share its canonical layout/projection tokens and the same account.
  class Binding {
   public:
    Binding() noexcept=default;
    [[nodiscard]] explicit operator bool() const noexcept {return bool(metadata_);}
    [[nodiscard]] const resource::MemoryAccount& account() const &;
    const resource::MemoryAccount& account() const &&=delete;
    [[nodiscard]] std::span<const AccountedLayout> layouts() const &;
    std::span<const AccountedLayout> layouts() const &&=delete;
    [[nodiscard]] const AccountedLayout& layout(LayoutId) const &;
    const AccountedLayout& layout(LayoutId) const &&=delete;
    [[nodiscard]] const AccountedProjection& projection(IndexRequirementId) const &;
    const AccountedProjection& projection(IndexRequirementId) const &&=delete;
    [[nodiscard]] PhysicalRoute route() const;
    [[nodiscard]] std::string_view physical_identity() const &;
    std::string_view physical_identity() const &&=delete;
    [[nodiscard]] std::size_t relation_count() const;
    [[nodiscard]] std::size_t index_count() const;
   private:
    friend class AccountedPlanStorage;
    explicit Binding(std::shared_ptr<const Metadata> metadata) noexcept:metadata_(std::move(metadata)) {}
    [[nodiscard]] const Metadata& metadata() const;
    std::shared_ptr<const Metadata> metadata_;
  };
  // The source and its spans are borrowed only for this constructor call.
  AccountedPlanStorage(const resource::MemoryAccount& account, const PhysicalPlan& plan,
      IndexWorkAllowance* work = nullptr)
      : AccountedPlanStorage(account, Inputs{plan.route(), plan.physical_sha256(),
          plan.guarantee().storage_backend, plan.layouts(), plan.relations(),
          plan.indexes(), plan.options().indexed_storage}, work) {}
  [[nodiscard]] static Binding freeze_binding(const resource::MemoryAccount& account,
      const PhysicalPlan& plan,IndexWorkAllowance* work=nullptr,MetadataWork mode=MetadataWork::execution) {
    AccountedPlanStorage metadata(account,Inputs{plan.route(),plan.physical_sha256(),
        plan.guarantee().storage_backend,plan.layouts(),plan.relations(),plan.indexes(),
        plan.options().indexed_storage},work,false,mode);
    return metadata.binding();
  }
  // Native compiler metadata already owns these tokens under this account.
  // This copies numeric bindings and aliases funded layout/projection controls.
  [[nodiscard]] static Binding freeze_native_binding(const resource::MemoryAccount&,
      PhysicalRoute,std::string_view identity,std::string_view guarantee,
      std::span<const AccountedLayout>,std::span<const RelationBinding>,
      std::span<const FrozenIndexBinding>,const std::optional<IndexedBackendSpec>&,
      IndexWorkAllowance* =nullptr,MetadataWork =MetadataWork::execution);
  // Explicit deep clone: new layout/projection tokens use the receiver account.
  // Sharing a Binding instead preserves its canonical tokens without a clone.
  [[nodiscard]] static Binding clone_binding(const resource::MemoryAccount&,const Binding&,
      IndexWorkAllowance* =nullptr);
  // Creates empty mutable tables from an already-owned immutable program.
  explicit AccountedPlanStorage(Binding binding,IndexWorkAllowance* work=nullptr);
  AccountedPlanStorage(const AccountedPlanStorage&) = delete;
  AccountedPlanStorage& operator=(const AccountedPlanStorage&) = delete;
  AccountedPlanStorage(AccountedPlanStorage&&) noexcept = default;
  AccountedPlanStorage& operator=(AccountedPlanStorage&&) noexcept;
  ~AccountedPlanStorage() = default;

  [[nodiscard]] StorageOwnerId owner() const;
  [[nodiscard]] Binding binding() const &;
  Binding binding() const &&=delete;
  [[nodiscard]] StorageBackend backend() const;
  [[nodiscard]] PhysicalRoute route() const;
  [[nodiscard]] std::string_view physical_identity() const &;
  std::string_view physical_identity() const && = delete;
  [[nodiscard]] std::span<const AccountedLayout> layouts() const &;
  std::span<const AccountedLayout> layouts() const && = delete;
  [[nodiscard]] const AccountedLayout& layout(LayoutId) const &;
  const AccountedLayout& layout(LayoutId) const && = delete;
  [[nodiscard]] const RelationBinding& relation(RelationId) const &;
  const RelationBinding& relation(RelationId) const && = delete;
  [[nodiscard]] const AccountedProjection& projection(IndexRequirementId) const &;
  const AccountedProjection& projection(IndexRequirementId) const && = delete;
  [[nodiscard]] AccountedStorageTable& table(RelationId) &;
  [[nodiscard]] const AccountedStorageTable& table(RelationId) const &;
  const AccountedStorageTable& table(RelationId) const && = delete;
  [[nodiscard]] IndexId index(IndexRequirementId) const;
  [[nodiscard]] std::size_t relation_count() const;
  [[nodiscard]] std::size_t index_count() const;
  [[nodiscard]] PlanStorageMemoryStatistics memory_statistics() const;
  [[nodiscard]] AccountedPlanStorage snapshot_copy(IndexWorkAllowance* = nullptr) const;
  // Full diagnostic: only index-binding probes debit this grant; table/layout scans are not wholly IndexWork-metered.
  void check_invariants(IndexWorkAllowance* = nullptr) const;
 private:
  friend class detail::AccountedPlanStorageTesting;
  friend class ::crown::runtime::detail::SqlColdRebuild;
  // Only the closed unpublished SQL rebuild can materialize under a separate
  // build grant. Metadata/backend/table domains retain their original meaning.
  struct ColdRebuild {};
  AccountedPlanStorage(Binding, IndexWorkAllowance*, ColdRebuild);
  void materialize(IndexWorkAllowance*);
  AccountedPlanStorage(const resource::MemoryAccount&, const Inputs&, IndexWorkAllowance*,bool materialize=true,
      MetadataWork =MetadataWork::execution);
  AccountedPlanStorage(std::shared_ptr<const Metadata>, StorageOwnerId,
      AccountedVector<AccountedStorageTable>, AccountedVector<IndexId>) noexcept;
  [[nodiscard]] const Metadata& metadata() const;
  std::shared_ptr<const Metadata> metadata_;
  StorageOwnerId owner_{};
  AccountedVector<AccountedStorageTable> tables_;
  AccountedVector<IndexId> indexes_;
};
}  // namespace crown::storage
