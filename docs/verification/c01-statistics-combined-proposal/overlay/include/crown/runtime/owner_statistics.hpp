#pragma once
#include "crown/runtime/support.hpp"
#include <variant>

namespace crown::runtime::statistics {
struct SourceScope { TableId table; };
struct NodeScope { NodeId node; SupportRole role; };
struct OccurrenceScope { OccurrenceId occurrence; };
struct IndexScope { IndexRequirementId requirement; };
using Scope=std::variant<SourceScope,NodeScope,OccurrenceScope,IndexScope>;
struct Selection {
  Scope scope;
  // nullopt: cardinality only for tables; native multiplicities for P/E and
  // occurrences; degree distribution for indices. Explicit fields: table NDV.
  std::optional<std::vector<FieldId>> fields;
};
struct OwnerRequest { std::vector<Selection> selections; }; // Maximum 256.
enum class Availability { available, budget_exhausted, pending_private_state, unavailable, not_applicable };
enum class OwnerLayer { support, physical };
struct OwnerStamp { SupportOwnerId owner; std::uint64_t sequence; OwnerLayer layer; };
struct Component {
  Selection selection;
  Availability availability=Availability::available;
  std::optional<NodeKind> node_kind;
  // Population layout; explicit selection.fields describes the ordered key
  // projection. For P/E, occurrence and index populations this is the full key.
  std::optional<storage::TupleLayout> layout;
  std::optional<std::uint64_t> cardinality;
  std::optional<Distribution> distribution;
  // Storage invalidation evidence only. Rollback may advance it; owner
  // freshness always uses OwnerStamp's committed event sequence instead.
  std::optional<Stamp> storage_invalidation;
};
namespace detail { class OwnerBuilder; }
class OwnerCapture {
 public:
  OwnerCapture(const OwnerCapture&)=default;
  OwnerCapture(OwnerCapture&&) noexcept=default;
  // A failed owning copy must not pair a new stamp with old component facts.
  OwnerCapture& operator=(const OwnerCapture& other) {
    if(this!=&other){OwnerCapture next(other);*this=std::move(next);}return *this;
  }
  OwnerCapture& operator=(OwnerCapture&&) noexcept=default;
  const OwnerStamp& stamp() const noexcept { return stamp_; }
  const PhysicalPlan& plan() const noexcept { return plan_; }
  Availability availability() const noexcept { return availability_; }
  Availability physical_source_scope() const noexcept { return physical_source_scope_; }
  const std::vector<Component>& components() const noexcept { return components_; }
  const Usage& usage() const noexcept { return usage_; }
  const Limits& limits() const noexcept { return limits_; }
  std::size_t requested_components() const noexcept { return requested_components_; }
  static constexpr std::uint32_t format_version=1;
 private:
  friend class detail::OwnerBuilder;
  OwnerCapture(OwnerStamp stamp,const PhysicalPlan& plan,Limits limits,std::size_t requested)
      :stamp_(stamp),plan_(plan),physical_source_scope_(stamp.layer==OwnerLayer::physical?Availability::available:Availability::unavailable),limits_(limits),requested_components_(requested) {}
  OwnerStamp stamp_; PhysicalPlan plan_;
  Availability availability_=Availability::available;
  Availability physical_source_scope_;
  std::vector<Component> components_; Usage usage_;
  Limits limits_; std::size_t requested_components_;
};
enum class Freshness { current, within_lag, stale, foreign_owner, future_sequence, scope_mismatch };
Freshness compare_freshness(const OwnerStamp& captured,const OwnerStamp& actual,std::uint64_t max_event_lag);
}
