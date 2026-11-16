# Human inspection continuation: planner proofs and cursors

Status: this scoped source/documentation and native verification checkpoint
passes after [v4](human-inspection-v4-2026-11-11.md). Both full selected Debug
and ASan/UBSan/leak gates complete. Full implementation and repository-wide
human review remain active, with the unchanged 78-card ledger.

## Scope and human usage contracts

V5 adds 417 individually authored contracts: 111 exact/certificate, 147 residual,
64 helper and 95 root recognition/validation cards. All 63 validator switch cases
have separate usage/failure/cost cards, even though the lexical map groups their
source into one large callable. All 300 selected production blocks in the
22 assigned files have a card. Meaningful ownership, lifetime and grammar
clusters were also reviewed rather than dismissed as scaffolding.

The [inspection index](../code_specs/README.md) now has 1,289 scoped contracts in
1,180 mapped blocks, over 664 files, 152,660 lines and 16,887 structural blocks.
Another 4,139 selected production blocks lack individual contracts, and
repository-wide test/tool semantic review is also unfinished. These inventories
are not semantic coverage percentages or universal correctness claims.

Two current-model reviewers inspected exact/replay and residual machinery.
Luna Max handled the bounded helper slice; root inspected recognition, validation
and the private authority/unit protocol. A separate current-model audit read all
95 root cards. No additional Astra run was used. Reviewers staged artifacts only;
root owns integration, source changes and executed checks.

## Direct code and necessary failure handling

Six `std::move` casts on raw Choice pointers become ordinary pointer assignments.
The source expressions are `Choice*` or `const Choice*`; the casts neither
consume an owner nor clear the source. The replacements preserve the exact
addresses and assignment order. All real owning moves remain intact.

The source audit proves these six substitutions are the only executable changes
in 21 maintained planner files; 20 files change comments/whitespace alone.
Checks, catches, coroutine operation/yield sites, public interfaces and maintained
tests are unchanged. There is no new runtime owner, registry, callback framework,
instrumentation or allocation. Optimized GCC and Clang each produce byte-identical
before/current `exact.cpp` objects under their saved strict Release flags. The
four actual objects are compilation/codegen controls, not linked Release tests
or a comparative speedup measurement.

Root applied 144 reviewer comment changes plus local recognition/validation
cost, topology, C* and formatting clarifications. The
[phase guide](../planner_proofs.md#validation-cursor-and-cost-boundary) follows
numeric safety, structural properties, variable connectivity, maximal/supplied
connex, height and publication. A hidden variable in root scope does not by itself
invalidate connex; C* admission depends on separators and head coverage.

The existing retry scheduler keeps throwing preparation outside coroutine resume
and commits cursor publication afterward. Public residual `advance` retains its
noexcept internal-failure boundary; work/content stops and `bad_alloc` remain
separate outcomes. Prefix infeasibility never promotes into an original-query
no-tree result. The reviewed handlers are necessary for their stated contracts;
none was removed merely to reduce catch count.

## Corrections from source and independent review

- Exported public layout/projection descriptors share native account-backed Data
  and control blocks. Valid conversion takes fixed handle validation/refcount
  work; it does not deep-copy the metadata. The handles can retain those blocks
  after the CompiledProgram object dies without retaining its whole graph or a
  tuple arena. The initial inaccurate helper packet is preserved separately.
- Defaulted move assignment can synchronously release a destination's previous
  implementation and last-owned scratch/input/tree/report data. It is not merely
  the pointer-transfer cost of move construction. The independent root audit's
  exact correction is applied and its before-image is retained.
- Two unique awaiter anchors originally began before their intended methods.
  Trailing context now keeps each anchor's start inside the correct callable.
  The final source map has no uncovered selected block in the assigned scope.

Costs are explicit: repeated GYO scans and ordered container work; insertion
sorting/hierarchy and potentially quadratic claim ordering; exponential exact
search/replay; complete tree/binding copies during restoration admission;
retained completed workers; and payload-dependent final teardown. Selected work,
logical depth, active time, construction cells/records and actual bytes/RSS are
distinct. A successful cursor step is not a fixed wall-time guarantee.

The structural terminology uses corrected
[P1 v2 §3.2](https://arxiv.org/html/2301.04003v2#S3.SS2).
The frozen-ear recipe is attributed narrowly to
[P2 v1 §2.1.4, Definition 2.9 and Algorithm 1](https://arxiv.org/html/2603.14754v1#S2.SS1.SSS4).
Normal-form contraction, branch recurrence, independent lower induction,
maximal-C* validation and compatible restoration/repair are separately identified
local arguments. Residual rounds, partial proofs and merely checked uppers are
not original-query minimum-height authority.

## Executed validation

| Configuration | Current result |
| --- | --- |
| Fresh strict GCC Debug | All 12 selected CTests passed, 860.60 s. |
| Fresh ASan + UBSan + leak checking | All 12 selected CTests passed, 3,500.53 s. |

The selected checks cover recognition, independent tree verification, complete
exact search, fast paths, search/continuation failure recovery, continuation
edge cases, certificate codec, residual models/fault recovery and residual typed
reports. Debug independently checks 4,681 bodies and 4,680 augmentations.
Its five residual sweeps report 24,449 allocation positions; owned P06 sweeps
report 3,194 and independent legacy replays 1,236. These are different fixture
cohorts, not a fabricated global uniqueness count. The sanitizer cohort reports
the same three counts and completes normal leak-checking teardown.

Both native builds/tests bind the same 1,101 stable code inputs. The builds
produce 30 linked native artifacts and 130 actual C++ objects; the four optimized
controls bring the object total to 134. Timings describe this run, not a benchmark.
The specification checker
passes 31,279 local links, current hashes and complete partitions after the
awaiter corrections. All 1,289 anchors resolve uniquely. The unchanged tools
retain the prior eight anchor fixtures and ten negative checker controls; this
does not certify the semantic content of every contract automatically.

Final build receipts are `inspection-v5-build-final-{debug,sanitizer}-v1`;
both raw outputs are archived at
`inspection-v5-ctest-final-{debug,sanitizer}-v1.LastTest.log`.
All 314 test commands/properties match their corresponding v4 profiles;
CMake/install declarations are unchanged. The existing sanitizer-only 7,200 s
residual watchdog is retained. Assertions, every fault position and sanitizer
options are unchanged. No full 314-test run is claimed.

The complete 3,695-line earlier handoff is preserved with identical bytes at
[handoff-history-v4-2026-11-11.md](../handoff-history-v4-2026-11-11.md), while the
active handoff is concise. Before-images of all 2,446 v4 source paths are under
`inspection-v5-preimages-v1`. Acceptance is recorded at
`build/verification/inspection-v5-acceptance-v1.json`; progress/source closure is
`build/verification/inspection-v5-progress-v1.json` with frozen source
`build/inspection-v5-source-v1`. All recorded v5 jobs are terminal at that seal.
Earlier source/build/evidence remains unchanged.

Four isolated read-only v6 packets stage another 383 proposed contracts for
session/public search, IR types, candidate provider/generator, structural keys
and binding encoding. Their diagnostics, comments and checked geometric-reserve
proposal are not applied to maintained inputs. Verify their current hashes and review their changes before v6 integration. W04/W05/W06 and the
full original implementation/release scope remain open.
