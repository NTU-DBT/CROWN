# Human inspection v6: candidates, sessions and public IR

The full [Refactor.md](../../Refactor.md) objective remains active. This packet
extends the [v5 checkpoint](human-inspection-v5-2026-11-11.md); it is a scoped
inspection and implementation change, not release acceptance or complete
semantic coverage of the repository. The ledger remains 54 verified, A02 in
progress and 23 not started. Both fresh native verification profiles pass.

## Reviewable source and specs

The [source index](../code_specs/README.md) and [primitive cards](../code_specs/primitives.md)
now include 389 new contracts, for 1,678 total. Each card states purpose,
inputs/outputs, invariants, ownership, failure, cost and narrow design references,
with a reviewed source hash and a unique source anchor. Structural line maps
remain distinct from individually reviewed semantics. The new scope covers
search_session.cpp/search.hpp; candidate provider/generator/key/binding and
their public APIs; and IDs/tree/physical public types. One new test function
documents the observable replay-diagnostic regression.

There are 1,499 mapped blocks with contracts across 664 files, 152,939 lines
and 16,947 structural blocks. All 297 selected production blocks in the 12
assigned files have cards. Another 3,842 selected production blocks lack
individual contracts, and the broader tests/tools review remains open.

Root applied 116 focused comment edits. The 82 selected session comments explain
protocol, authority, resource order and lifetime; trivial getters/equality/copy
declarations retain their individual external cards without repetitive inline
text. No runtime helper, state field, instrumentation or exception handler was
added. The complete three source substitutions and comment-only files are
recorded separately in the source-edit audit.

The full 2,448-path v5 source is preserved under
`build/verification/inspection-v6-preimages-v1`. Before integration all source
hashes and all 86 predecessor artifacts matched the sealed v5 manifest.
Previously sealed builds/source/evidence remain unchanged. Review packets are
`inspection-v6-{session,candidates,ir-types,root}-v1`; root integration is
`inspection-v6-integration-v1`. These are local build/verification paths.

## Direct implementation changes

Candidate publication previously called `reserve(size + 1)` for every distinct
candidate, which can repeatedly relocate the whole prefix. It now reserves
checked geometric capacity only when needed. The existing count/overflow checks
run first; clipping the increment by `max_size - capacity` prevents overflow.
Capacity and immutable payload still succeed before seen-key insertion. The
same saved stage and logical work/content charges remain. Public access returns
owning handles and snapshots copy vectors, so relocation invalidates no exported
element borrow. See [candidate transactions](../candidate_alternatives.md#identity-cache-and-transactions).

The independent growth review checks arithmetic, owners, retry/publication
ordering and all 123 candidate card cost fields. Its static arithmetic control
covers 47,840 small states and 28 large boundary states; this is not native
execution or a benchmark. Geometric growth gives amortized constant handle
relocation per publication, while a single reserve remains linear and may
allocate spare capacity. Allocation positions/sizes intentionally change;
logical caps do not bound allocator bytes or hard elapsed time.

`verify_height_certificate` retains its checked handle and chooses successful
wording from that immutable admitted certificate after independent replay.
Finite proofs retain the upper/lower wording. A valid infinite-root proof now
reports an independently verified empty admissible family. Invalid and resource
messages retain their previous paths. No proof rule, search/checker unit or
authority outcome changes. A focused regression checks all four outcomes.

## Independent documentation corrections

The root/IR reviewer checks all 105 requested cards against their actual bodies
and dependencies, unique anchors, hashes and intended mapped blocks. Corrections
make the following limits explicit:

- Plan assignments can synchronously destroy the destination's previous payload;
  fixed handle work applies to construction.
- Exported layout/projection handles share account-backed metadata. Result
  construction may allocate through the retained account, and equality checks
  can scan string bytes; instruction counts alone are not total cost bounds.
- Lowering checks tree routes. `from_compiled` copies an existing native
  validation/profile without rerunning P02. Constant operators and tree evidence
  retain distinct meanings.
- A null lower also occurs in default/moved-from snapshots; it alone does not
  establish infeasibility. Failed terminal owners retain scratch until teardown.

The raw review material and exact field corrections remain preserved beside
the applied corrections. Paper definitions describe only their cited structural
claims; allocator, retry, native export, normal-form and independent recurrence
arguments retain their local design references.

## Verification and remaining work

Strict Debug and ASan/UBSan/leak builds pass on the same 1,101 stable maintained
inputs. Each profile passes all nine selected tests; Debug takes 73.00 seconds
and sanitizer 253.58 seconds. Both complete raw `LastTest.log` files are archived
before any further CTest enumeration. The selected tests are:

| Check | Main purpose |
| --- | --- |
| planner_candidates | Independent candidate enumeration, keys, binding and retained snapshots |
| planner_candidate_exceptions | Persistent allocation failure and same-owner publication recovery |
| planner_candidate_reports | Progress/prefix/exhaustion and report/schema controls |
| planner_search_exceptions | Independent legacy replay and allocation/resource boundaries |
| planner_certificate_codec | Versioned proof roundtrips and invalid algorithms |
| tree_oracle_fixtures | 21 finite/infeasible CLI cases, replay and corruption controls |
| planner_continuations | Slicing, typed authority, ownership and resource semantics |
| planner_continuation_exceptions | Retained owned search/replay allocation-failure recovery |
| planner_continuation_edges | New four-outcome report regression and existing lifetime/depth edges |

Each profile reports the following separate fault cohorts: P07 generator 613,
key 17 and provider 2,369; owned P06 3,194; legacy search/construction 3,638; and
independent v1/v2 legacy replay 1,236. Allocation sweeps discover their current
positions dynamically; no cross-cohort uniqueness or count reduction is claimed.

The native inventory hashes 44 actual maintained linked artifacts and 252 C++
objects, with strict C++23 flags for every actual compilation. Vendored C
dependencies are outside that C++ inventory. The spec checker passes 33,349
local links, current source hashes and complete structural partitions. Exact
same-profile comparison preserves all 314 registrations/commands/properties,
CMake/install declarations and documentation tools; the unchanged eight anchor
fixtures and ten checker-negative controls retain their earlier applicability.
No full 314-test execution, optimized Release run or measured speedup is claimed.

Final receipts are `inspection-v6-build-final-*-v1`,
`inspection-v6-ctest-final-*-v1`, `inspection-v6-source-edit-audit-v1`,
`inspection-v6-specs-check-v1` and `inspection-v6-metadata-final-v1`, under
`build/verification`. Acceptance/source closure are
`inspection-v6-acceptance-v1.json` and `inspection-v6-progress-v1.json`; frozen
source is `build/inspection-v6-source-v1`. The v5 handoff is archived with
identical bytes in [handoff-history-v5-2026-11-11.md](../handoff-history-v5-2026-11-11.md).

Other source blocks, tests/tools, W04 and later implementation/experiment/release
gates remain open. Read-only v7 work may be staged during these tests; it is not
part of the current native acceptance.
