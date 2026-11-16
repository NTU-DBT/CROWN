# P06 implementation seams, 2026-11-06

Design only. Native files were read, not changed; no build/test executed. Root's
six decisions in the saved transition plan are settled, not approval questions.

## 1. Resolve symbol ownership before parallel implementation

Current CMake compiles `src/planner/exact.cpp` twice: in `crown_core` and in
`crown_planner_testing` with `CROWN_PLANNER_TESTING`. The test copy exports both
`minimum_tree` and `testing::minimum_tree_baseline`; archive extraction order
currently prevents the production exact object from also being extracted.

Once `search_session.cpp` owns the strict public `minimum_tree`, that arrangement
is unsafe: a test baseline reference extracts the test exact object, while a new
ExactSearch reference extracts search_session, producing two public minimum_tree
definitions if the old definition remains. Similarly, compiling the new producer
implementation in both archives can duplicate its machine definitions when core
references require the second object. Do not rely on archive order or weak symbols.

Recommended one-time integration change:

- Extract the actual pre-P06 **unoptimized v1 producer** into
  `tests/support/planner_exact_baseline.cpp`, exporting only
  `crown::planner::testing::minimum_tree_baseline`. Preserve its recurrence,
  exhaustive root/partition behavior, tree construction and v1 proof export.
  Strip the unused optimized path rather than retaining dependencies on mutable
  fast_paths interfaces. Retain its old budget implementation privately in
  `tests/support/planner_baseline_budget.hpp` if the production budget changes.
- Keep its helper types/functions in an anonymous or baseline-private namespace.
  It continues to call public independent `verify_height_certificate` with v1
  proof semantics. It must not call ExactSearch or the new producer machine.
- Change `crown_planner_testing` to compile only this baseline source, retaining
  its `PUBLIC CROWN_PLANNER_TESTING` definition because existing exception tests
  conditionally exercise it. Keep `tests/support/planner_probe.hpp` declarations.
- Compile production `exact.cpp`, `search_session.cpp`, `certificate.cpp`, and
  `verify.cpp` exactly once in crown_core. No production baseline export.
- Remove the old public minimum_tree definition and testing export from exact.cpp
  when search_session becomes the sole owner. If `verify_height_certificate`
  moves to search_session, remove its definition from certificate.cpp in the
  same integration change. Keep public validate_tree solely in verify.cpp.

Resulting symbol ownership:

| Symbol | Sole defining translation unit/target |
| --- | --- |
| minimum_tree, ExactSearch methods | search_session.cpp / crown_core |
| verify_height_certificate, CertificateReplay methods | search_session.cpp / crown_core |
| validate_tree | verify.cpp / crown_core |
| internal ProducerMachine | exact.cpp / crown_core |
| internal ReplayMachine | certificate.cpp / crown_core |
| internal ValidationMachine | verify.cpp / crown_core |
| testing::minimum_tree_baseline | planner_exact_baseline.cpp / crown_planner_testing |

The P03 literal oracle remains unchanged. This retains three distinct roles:
frozen literal P03, frozen unoptimized v1 producer, new resumable v2 producer.
V1/v2 wire proof meaning is independent of continuation accounting revision.

## 2. Minimal internal machine seam

Have the integrator own one private declaration header, for example
`src/planner/continuation_machine.hpp`, agreed before implementers start. The
following is a declaration sketch, not another public API:

```cpp
namespace crown::planner::continuation_detail {
struct BoundInput;       // immutable owned Catalog, Query, fixed options
struct FrozenCandidate;  // complete immutable producer choice DAG, not a tree proof
struct FrozenTree;       // complete immutable concrete tree
struct FrozenProof;      // immutable HeightCertificate payload
struct CheckedUpper;    // private P02 authority, never caller-constructible
struct CheckedProof;    // private complete replay authority

enum class UnitEvent {
  advanced, need_child, child_complete, candidate_ready,
  producer_complete, upper_valid, upper_invalid,
  proof_valid, proof_invalid, depth_blocked
};
struct UnitResult { UnitEvent event; std::size_t requested_depth = 0; };
struct UnitContext {
  std::size_t depth_ceiling; // optional/unbounded represented explicitly in real API
  // No arbitrary user callback, no recursively usable budget reference.
};

class ProducerMachine {
 public:
  explicit ProducerMachine(std::shared_ptr<const BoundInput>);
  UnitResult step(const UnitContext&); // one safe transition; bad_alloc may escape
  std::shared_ptr<const FrozenCandidate> candidate() const noexcept;
  std::shared_ptr<const FrozenProof> completed_proof() const noexcept;
  void acknowledge_candidate() noexcept; // only scheduler after saving ownership
  void accept_upper(std::shared_ptr<const CheckedUpper>) noexcept;
  // Save a handle only. Matching to the final choice and tree/proof copying are
  // explicit export steps; an old/wrong-height incumbent cannot finalize proof.
  // pimpl, movable/noexcept destruction; own all frames and drafts
};
class ValidationMachine {
 public:
  ValidationMachine(std::shared_ptr<const BoundInput>,
                    std::shared_ptr<const FrozenTree>);
  UnitResult step(const UnitContext&);
  std::shared_ptr<const CheckedUpper> checked() const noexcept;
  // Internal diagnostic view uses fixed enums/IDs until allocating legacy export.
};
class ReplayMachine {
 public:
  ReplayMachine(std::shared_ptr<const BoundInput>,
                std::shared_ptr<const FrozenProof>);
  UnitResult step(const UnitContext&);
  std::shared_ptr<const CheckedProof> checked() const noexcept;
  // Owns independent ValidationMachine, scopes, ports, partitions and proof tables.
};
}
```

Also give the producer owner a private `WitnessMachine` to turn FrozenCandidate
into FrozenTree incrementally. This can be declared beside ProducerMachine;
the scheduler then supplies that tree to ValidationMachine. ProducerMachine's
completed_proof becomes available only after incremental proof export finishes;
the public result remains unverified until ReplayMachine finishes.

After validation, the scheduler supplies CheckedUpper back through accept_upper;
the checked handle retains FrozenTree plus its exact binding. Feasible final proof
export requires that its checked height/tree match the final selected choice.
Infeasible final proof has no upper artifact. This closes the witness/export seam
without making replay trust producer validation: replay checks the upper again.

Each constructor creates only a small inert shell; large initialization is
represented by step stages. Allocating a new shell itself is a scheduler
transition prepared before its phase pointer changes. Shared payload handle
copies allocate nothing. Factories may allocate/validate owned input on admission
as already decided, but cannot hide full search or proof replay in construction.

Scheduler protocol per unit:

1. Check per-call allowance, cumulative phase ceiling, clock and prospective depth.
2. Charge attempted work once, then call exactly one active machine step.
3. On success account one committed transition and process its fixed-size event.
4. On bad_alloc return an allocation_failure stop with the same logical next
   action retained; on unexpected failure poison the session. No formatted string.
5. Scheduling/child-shell creation/publication is itself a separate unit when it
   needs allocation or meaningful work. No event handler drains another machine.

Machine `step` never consumes an entire nested child: it selects a pending child
or advances that child by one safe transition. In replay's upper-validation stage,
one replay step forwards exactly one ValidationMachine step. Only the top-level
scheduler charges it; avoid double charging nested delegation. Logical depth is
reported/checked before pushes, including nested machines' outstanding frames.

One safe transition means one cursor action with prepared allocation followed by
nonthrowing publication, not an arbitrary large loop. It is an abstract work unit,
not a fixed CPU bound: ordinary nonyielding map comparisons/allocation remain
documented costs. Long traversal/copy/sort loops must have explicit saved indices.
No yielding comparator, borrowed vector element across growth, or budget unwind.

Keep producer and replay partition/metadata types private to their own .cpp or
separate private headers. They share immutable input, scalar scheduling vocabulary,
and the P02 validator, **not** incidence/ports/orbit or enumeration algorithms.
Replay must independently reconstruct those facts exactly as current v1/v2 require.

## 3. Dependency and build ownership for parallel implementation

Integrator first freezes the shared private seam and performs baseline extraction
plus sole-public-symbol ownership changes. Then assignments do not share files:

| Owner | Exclusive files | Dependency |
| --- | --- | --- |
| Integrator/API | search.hpp, search_session.cpp, continuation_machine.hpp, new ledger source/header, CMakeLists.txt, IO progress integration | All machine interfaces |
| Producer | exact.cpp, fast_paths.hpp/.cpp, producer-private cursor files, witness-private cursor files | Frozen seam only |
| Independent checker | certificate.cpp, replay-private cursor files | Frozen seam and ValidationMachine declaration |
| Independent P02 | verify.cpp, validation-private cursor files | Frozen seam and current verify.hpp |
| Baseline/test integration | tests/support/planner_exact_baseline.cpp, planner_baseline_budget.hpp, tests/support/planner_probe.hpp, new test files | Existing strict oracle API |

If slot count combines roles, preserve these file ownership boundaries. Only
integrator edits CMake/shared declarations/IO. Other owners request a seam change
instead of independently editing the header. Add implementation source filenames
to crown_core once; private headers are not separately compiled. Do not compile a
second instrumented producer object into crown_planner_testing.

No linker stubs should return fake completion or verified status. Owners may
compile their translation units against declarations before integration, but end
to end link acceptance waits until all actual machine definitions exist. Final
integration must check ordinary CLI linkage and tests that reference both baseline
and ExactSearch in the same executable (the case that reveals this symbol hazard).
That future check is not executed by this design task.
