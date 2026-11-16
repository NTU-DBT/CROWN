#pragma once
#if !defined(CROWN_ACCOUNTED_PLAN_TESTING) || CROWN_ACCOUNTED_PLAN_TESTING != 1
#error "Plan storage construction shim is test-executable-only"
#endif
#include "crown/storage/accounted_plan.hpp"
namespace crown::storage::detail {
// Lets the allocation tracer test metadata construction without linking the
// SQL compiler into its three collision/production profiles. The separate
// physical-plan test uses the actual public opaque-PhysicalPlan constructor.
class AccountedPlanStorageTesting {
 public:
  static AccountedPlanStorage create(const resource::MemoryAccount& account,
      PhysicalRoute route, std::string_view identity, std::span<const TupleLayout> layouts,
      std::span<const PhysicalRelation> relations, std::span<const IndexRequirement> indexes,
      std::optional<IndexedBackendSpec> indexed, IndexWorkAllowance* work) {
    AccountedPlanStorage::Inputs input{route, identity,
        indexed ? "indexed_chained_v1" : "reference_ordered_v1", layouts, relations, indexes, indexed};
#ifdef CROWN_ACCOUNTED_COLLISION_PROFILE
    input.collision_profile = CROWN_ACCOUNTED_COLLISION_PROFILE;
#endif
    return AccountedPlanStorage(account, input, work);
  }
};
}
