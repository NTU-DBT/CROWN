#pragma once

#include "crown/ir/tree.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace crown::reference {

// Deliberately small operational limits for this blocking reference routine.
// Hitting either limit is a resource stop, never a semantic unsupported result.
inline constexpr std::size_t normal_form_reference_native_cap = 3;
inline constexpr std::size_t normal_form_reference_active_variable_cap = 3;

struct NormalFormCollectionLimits {
  // Counts reference-level transitions. validate_tree is a bounded blocking
  // call under the two arity caps and is charged as one transition.
  std::uint64_t max_work_units = 5'000'000;
};

enum class NormalFormCollectionStop {
  none,
  work_limit,
  native_occurrence_cap,
  active_variable_cap,
  work_counter_overflow,
  allocation_failure,
  container_limit,
};

struct NormalFormReferencePlan {
  // Equality evidence local to the supplied Catalog/Query and requested
  // height. This is not a production plan key or a global cache identity.
  std::string signature;
  FreeConnexTree representative;
};

struct NormalFormCollectionResult {
  std::vector<NormalFormReferencePlan> plans;
  std::uint64_t work_units = 0;
  // True only after every member of the finite requested-height family was
  // visited. A resource-limited prefix always leaves this false.
  bool exhausted = false;
  bool resource_limited = false;
  NormalFormCollectionStop stop = NormalFormCollectionStop::none;
};

// Collect the P02-valid, literal normal-form family for exactly the supplied
// native height. The height is only an enumeration filter; it is not proof of
// feasibility, minimum height, or global cost optimality. The binding is the
// exact Catalog/Query passed to the independent P02 validator for each draft.
[[nodiscard]] NormalFormCollectionResult collect_normal_form_plan_set(
    const Catalog& catalog, const Query& query, std::size_t supplied_native_height,
    NormalFormCollectionLimits limits = {});

// Sign a tree only after the caller has accepted it with P02 against the
// intended Catalog/Query binding. This structural signature establishes no
// validation, minimum-height authority, or global identity by itself.
[[nodiscard]] std::string normal_form_reference_signature(const FreeConnexTree& checked_tree);

}  // namespace crown::reference
