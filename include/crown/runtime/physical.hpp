#pragma once

#include "crown/runtime/support.hpp"
#include "crown/runtime/update_view.hpp"
#include "crown/storage/accounted_table.hpp"
#include "crown/recovery/image.hpp"
#include "crown/runtime/source_image.hpp"
#include <functional>

namespace crown::runtime {
struct WindowCheckpoint;
namespace ranking::detail {struct OwnerAccess;}
namespace reoptimization::detail {class Budget;}
class DeltaRuntime;
struct PhysicalRuntimeOptions {
  SupportOptions support;
  // Abstract coordinator work, including all staged logical support work.
  // Full reference constraint checks have additional comparison/scan costs.
  std::optional<std::uint64_t> work_limit = 1000000;
  std::uint64_t derivation_limit = std::numeric_limits<std::uint64_t>::max();
};
struct PhysicalMetrics {
  std::uint64_t work = 0;
  std::uint64_t source_changes = 0;
  std::uint64_t aliases_visited = 0;
  std::uint64_t aliases_filtered = 0;
  std::uint64_t derivation_changes = 0;
  std::uint64_t native_crossings = 0;
  std::uint64_t constraint_rows = 0;
  std::uint64_t constraint_validations = 0;
};
struct DerivationChange {
  OccurrenceId occurrence;
  NodeId node;
  storage::Tuple tuple;  // Final native scope, not an earlier SQL projection.
  std::uint64_t before, after;
  bool native_changed;
};
struct SourceRowChange {
  TupleHandle handle;
  storage::AccountedTupleArena::Pin retained;
  [[nodiscard]] const storage::AccountedTuple& tuple() const & { return retained.get(); }
  const storage::AccountedTuple& tuple() const && = delete;
};
struct PhysicalPreview {
  std::uint64_t sequence;
  TableId table;
  SetOperation operation;
  bool physical_changed;
  PhysicalMetrics metrics;
  std::optional<SourceRowChange> source;
  std::vector<DerivationChange,resource::OwnerAllocator<DerivationChange>> derivations;  // Compiled occurrence order.
};
struct PhysicalEpoch {
  PhysicalPreview input;
  SupportEpoch support;  // Local changes only; not full-query output deltas.
};
struct DerivationSnapshot {
  storage::Tuple tuple;
  std::uint64_t count;
};
struct PhysicalSnapshot {
  std::uint64_t sequence;
  Database physical;
  SupportSnapshot support;
  std::vector<std::vector<DerivationSnapshot>> derivations;
};
struct PhysicalStorageStatistics {
  storage::ArenaStatistics source, support;
  std::size_t derivation_keys = 0;
};

// Full-source-row coordinator over the selected native storage backend.
// Constructors start empty; initialize() builds a validated whole database.
// Source and derivation undo stay open beside one logical PendingEpoch until
// the final publication barrier. No internal kernel/table reference is exposed.
class PhysicalRuntime {
  friend struct memory::detail::Access;
  struct Impl;
 public:
  class PendingUpdate {
   public:
    PendingUpdate(const PendingUpdate&) = delete;
    PendingUpdate& operator=(const PendingUpdate&) = delete;
    PendingUpdate(PendingUpdate&&) noexcept;
    PendingUpdate& operator=(PendingUpdate&&) noexcept;
    ~PendingUpdate();
    [[nodiscard]] bool active() const noexcept;
    // Owner-only views, unpublished until commit. References expire on close.
    [[nodiscard]] const PhysicalPreview& preview() const;
    [[nodiscard]] const SupportEpoch& support() const;
    [[nodiscard]] PhysicalSnapshot snapshot() const;
    // Funded full after-state sources after all alias routes have drained.
    // Uses this token's retained indexed operation grant; never replenishes it.
    // Refusal preserves the active token; abandoning that token rolls it back.
    [[nodiscard]] physical::SourceImage source_image(physical::SourceImageLimits = {}) const;
    [[nodiscard]] SupportRuntime::EpochView view(SnapshotSide side, EpochViewOptions options = {});
    // Stage external output privately before this barrier. All throwing output
    // preparation must finish first. Valid commit/rollback allocate nothing.
    [[nodiscard]] PhysicalEpoch commit();
    void rollback() noexcept;
   private:
    friend class PhysicalRuntime;
    friend class DeltaRuntime;
    // Delta owns one drained alias prefix at a time. The callback may retain
    // its views, but must retire them before staging another route.
    [[nodiscard]] bool stage_next(const std::function<void(OccurrenceId, std::uint64_t,
        const SupportRuntime::EpochView&, const SupportRuntime::EpochView&,
        std::span<const JournalRecord>)>& observer, EpochViewOptions options);
    struct Data;
    explicit PendingUpdate(resource::AccountedUnique<Data> data) noexcept;
    resource::AccountedUnique<Data> data_;
  };
  explicit PhysicalRuntime(PhysicalPlan plan, PhysicalRuntimeOptions options = {});
  explicit PhysicalRuntime(CompiledProgram plan,PhysicalRuntimeOptions options = {});
  [[nodiscard]] static PhysicalRuntime initialize(PhysicalPlan plan,const Database& database,
      PhysicalRuntimeOptions options={},BuildOptions build={});
  [[nodiscard]] static PhysicalRuntime initialize(CompiledProgram plan,const Database& database,
      PhysicalRuntimeOptions options={},BuildOptions build={});
  [[nodiscard]] PhysicalRuntime rebuilt(BuildOptions build={}) const;
  ~PhysicalRuntime();
  PhysicalRuntime(const PhysicalRuntime&) = delete;
  PhysicalRuntime& operator=(const PhysicalRuntime&) = delete;
  PhysicalRuntime(PhysicalRuntime&&) noexcept;
  PhysicalRuntime& operator=(PhysicalRuntime&& other) noexcept;
  [[nodiscard]] const CompiledProgram& plan() const;
  // Native allocations routed to this query account, including retained state
  // and outputs; requested bytes are distinct from process RSS.
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
  [[nodiscard]] ObservationSnapshot observations() const;
  void configure_workload_statistics(const workload::Options&);
  void reset_workload_statistics();
  [[nodiscard]] workload::Snapshot workload_statistics() const;
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
  [[nodiscard]] CommittedStateGauges committed_state_gauges() const;
  [[nodiscard]] CapturedStateGauges capture_state_gauges() const;
  [[nodiscard]] statistics::OwnerCapture capture_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
  [[nodiscard]] statistics::OwnerCapture capture_statistics_view(statistics::OwnerRequestView,statistics::Limits limits={}) const;
  [[nodiscard]] statistics::Freshness statistics_freshness(const statistics::OwnerCapture&,std::uint64_t max_event_lag=0) const;
  [[nodiscard]] statistics::CombinedCapture capture_combined_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
  [[nodiscard]] statistics::CombinedCapture capture_combined_statistics_view(statistics::OwnerRequestView,statistics::Limits limits={}) const;
  [[nodiscard]] ObservationTrace observation_trace() const;
  [[nodiscard]] CapturedObservationTrace capture_observation_trace() const;
  [[nodiscard]] const PhysicalRuntimeOptions& options() const;
  [[nodiscard]] SupportOwnerId owner() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] bool ready() const;
  [[nodiscard]] bool has_answer() const;
  [[nodiscard]] const storage::TupleLayout& source_layout(TableId table) const;
  [[nodiscard]] const storage::TupleLayout& result_layout(ResultView view = ResultView::sql) const;
  [[nodiscard]] PendingUpdate prepare(const PhysicalSetUpdate& update);
  [[nodiscard]] PhysicalEpoch apply(const PhysicalSetUpdate& update);
  [[nodiscard]] PhysicalEpoch apply_view(const PhysicalUpdateView& update);
  // SQL plans map ordered/repeated/constant outputs and scalar EXISTS. Direct
  // CQ plans retain core output order. Both pin the committed logical epoch.
  [[nodiscard]] SupportRuntime::ResultCursor results(ResultCursorOptions options = {}) const;
  [[nodiscard]] SupportRuntime::ResultCursor core_results(ResultCursorOptions options = {}) const;
  [[nodiscard]] SupportRuntime::EpochView current_view(EpochViewOptions options = {}) const;
  [[nodiscard]] SupportRuntime::ResultCursor completions(const FixedAssignment& fixed, VisibleFragment fragment = {}, ResultCursorOptions options = {}) const;
  [[nodiscard]] SupportRuntime::ResultCursor witnesses(const FixedAssignment& fixed = {}, WitnessFragment fragment = {}, ResultCursorOptions options = {}) const;
  [[nodiscard]] PhysicalSnapshot snapshot() const;  // Owning diagnostic copy.
  // Charged native source data only: no ordinary Database/string export and
  // no source mutation. This is one explicit capture operation, with its own
  // selected image budget and the original backend's operation ceiling.
  [[nodiscard]] physical::SourceImage source_image(physical::SourceImageLimits = {}) const;
  [[nodiscard]] std::uint64_t derivation_count(OccurrenceId occurrence, const Row& native_values) const;
  [[nodiscard]] std::optional<TupleHandle> find_source(TableId table, const Row& values) const;
  [[nodiscard]] std::optional<storage::AccountedTuple> get_source(TableId table, TupleHandle handle) const;
  [[nodiscard]] std::optional<SupportHandle> find_support(NodeId node, SupportRole role, const Row& values) const;
  [[nodiscard]] std::optional<storage::Tuple> get_support(SupportHandle handle) const;
  [[nodiscard]] PhysicalStorageStatistics storage_statistics() const;
  [[nodiscard]] const BuildMetrics& initialization_metrics() const;
  [[nodiscard]] InitializationContext initialization_context() const;
  [[nodiscard]] CanonicalPhysicalState canonical_state() const;
  [[nodiscard]] InvariantReport inspect_invariants(InspectionOptions options={}) const;
  void check_invariants() const;
 private:
  friend class DeltaRuntime;
  friend struct ranking::detail::OwnerAccess;
  [[nodiscard]] bool same_sources(const PhysicalRuntime&,reoptimization::detail::Budget&) const;
  [[nodiscard]] const CompiledProgram& compiled_program() const;
#ifdef CROWN_RUNTIME_TESTING
  friend class RuntimeTestProbe;
#endif
  using PlanSource=std::variant<PhysicalPlan,CompiledProgram>;
  [[nodiscard]] static PhysicalRuntime initialize_at(PlanSource plan,const Database& database,
      PhysicalRuntimeOptions options,BuildOptions build,std::uint64_t sequence,BuildMetrics prefix={},
      std::shared_ptr<detail::StorageWorkContext> context={});
  [[nodiscard]] recovery::EncodedImage checkpoint_image(const recovery::ImageBinding&,recovery::ImageLimits) const;
  [[nodiscard]] static PhysicalRuntime restore_image(CompiledProgram,std::string_view,
      PhysicalRuntimeOptions,BuildOptions,recovery::ImageLimits,const recovery::ImageBinding&,
      std::shared_ptr<detail::StorageWorkContext>,const WindowCheckpoint*,std::uint64_t matching_work);
  template<class DatabaseView>
  [[nodiscard]] static PhysicalRuntime initialize_data(PlanSource,const DatabaseView&,
      PhysicalRuntimeOptions,BuildOptions,std::uint64_t,BuildMetrics,
      std::shared_ptr<detail::StorageWorkContext>);
  PhysicalRuntime(PlanSource,PhysicalRuntimeOptions,std::shared_ptr<detail::StorageWorkContext>);
  [[nodiscard]] PhysicalRuntime rebuilt(BuildOptions,std::shared_ptr<detail::StorageWorkContext>) const;
  [[nodiscard]] PhysicalRuntime rebuilt_for(const planner::MinimumHeightCandidate&,BuildOptions,
      const program::ReplanLimits&,std::shared_ptr<detail::StorageWorkContext>) const;
  [[nodiscard]] PhysicalRuntime rebuilt_with_program(CompiledProgram,BuildOptions,
      std::shared_ptr<detail::StorageWorkContext>) const;
  [[nodiscard]] std::shared_ptr<detail::StorageWorkContext> storage_context() const;
  using RouteObserver = std::function<void(OccurrenceId, std::uint64_t, const SupportRuntime::EpochView&,
      const SupportRuntime::EpochView&, std::span<const JournalRecord>)>;
  [[nodiscard]] PendingUpdate prepare_observed(const PhysicalSetUpdate& update,
      const RouteObserver& observer, EpochViewOptions options);
  [[nodiscard]] PendingUpdate begin_staged(const PhysicalSetUpdate& update);
  [[nodiscard]] PendingUpdate begin_staged(const PhysicalUpdateView& update);
  [[nodiscard]] std::shared_ptr<detail::ObservationState> observation_state() const;
  [[nodiscard]] workload::detail::State& workload_state() const;
  [[nodiscard]] Impl& impl() const;
  std::shared_ptr<Impl> impl_;
};
}  // namespace crown::runtime
