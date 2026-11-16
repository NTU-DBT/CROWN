# Decision 0011: reference support maintenance over logical updates

Historical working-copy decision. The current runtime transaction replaces
whole-state copies with [affected-record journals](0013-support-journals.md).

Status: R01–R03 verified, 2026-11-05. This records the reference logical
support-maintenance kernel; release and runtime-performance gates remain open.

## Decision

Build the initial kernel on the validated `PhysicalPlan` and standard-container
`ReferencePlanStorage`. Its external update unit is one logical native tuple
for one physical tree node. The full scoped tuple is ordered by ascending core
variable ID. Sequence numbers start at 1 and must be contiguous. Duplicate
inserts and absent erases are valid no-ops that advance sequence without
cloning state or propagating support events. Generalized nodes are derived
from child support and reject external writes.

Native survivors are controlled by exact child-key presence. Generalized
candidates are the child-key union and survive on the child-key intersection;
zero-presence candidates are reclaimed. Each node keeps distinct exact
`P_v` parent-support and, only inside `C*`, `E_v` visible-projection counters.
`uint64_t` projection supports have a positive configurable limit and never
wrap. Propagation emits local membership changes only at zero crossings.
Optional per-response transition capture owns its keys and is neither a full
answer delta nor persistent event history.

For every real update, stage a complete copy of the reference relation/index
storage and mutable node metadata. The copy gives each backend table a fresh
storage owner while preserving live tuple/index IDs and their allocation
counters. Support handles use a separate logical runtime owner, so handles for
still-live entries survive backend replacement and positive support-count
changes. Deleted IDs are not reused; reinsertion creates a new ID. Commit by
swapping the state pointer only after all propagation succeeds.

Use an iterative local `std::deque` scheduler with selectable FIFO or LIFO
draining. Native insertion checks each child projection; later child-key
transitions visit the matching reverse separator bucket. Generalized updates
change candidate flags without forming Cartesian products. This loop is
separate from R04's affected-record epoch journal and pinned retention.
Durable recovery remains later O04/O05 work.

## Consequences and limits

The working copy gives per-call failure atomicity for support overflow,
work-limit stops, allocation failures, and propagation errors. It also makes
the current cost explicit: every real update copies all populated reference
relations, index memberships, and mutable node metadata before incremental
propagation. The runtime reports these copy counts and total abstract work;
this is a correctness-first reference path and establishes no CROWN update
bound or memory-byte bound. The default work limit is 1,000,000 abstract units,
including copy cells and excluding allocator overhead, JSON processing, and
CPU time. The default positive support limit is `uint64_t` maximum.

The C++ API and `support-trace` diagnostic expose logical state. `has_answer` reports root-survivor
nonemptiness (or a constant route), not an enumerable result. There is no
physical-row or SQL alias routing (R05), bulk initialization, result/delta
cursor, pinning, recovery, or persisted transition journal. Constant physical
routes have no node ports. The version-1 diagnostic schema defines logical
input traces and reports; it is not a resumable checkpoint or importer.

The empty-head rule follows the compiled `C*` definition: traverse an edge
when its separator is contained in the head. Therefore an empty separator is
traversable when the head is empty, and each reachable child has a nullary
`E_v` whose support equals its survivor count. `visible_keys` is absent only
outside `C*`, not merely because `F ∩ B_v` is empty.

Independent subtree/A04 comparisons, manual traces, exact P/E/empty-key checks,
failure sweeps and all 33 tests pass across GCC Debug/Release/sanitizers,
Clang and clean source build. See the [runtime support contract](../runtime_support.md),
[Refactor.md §§6.1, 6.3, and R01–R03](../../Refactor.md),
[physical lowering contract](../physical_plans.md), [manual fixtures](../../tests/runtime/support/manifest.json),
and the [support verification packet](../verification/support-2026-11-05.md).
The conditional maintenance argument is in
[support_invariants.md](../support_invariants.md). Internal review does not
replace the outstanding G2/V02 external mathematical review.
