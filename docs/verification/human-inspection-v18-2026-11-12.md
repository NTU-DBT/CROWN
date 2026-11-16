# Inspectable weighted deltas and test contracts

The maps contain **11,229 scoped contracts in 8,877 blocks**, across 695 maintained
files / 160,325 lines / 17,985 mapped blocks. Every inventoried line has a structural
map. All 5,496 selected production scopes have contracts, as do all selected root
CMake, module, example and tool scopes. Remaining selected manual gaps are 4,201
test scopes. Structural mapping is not universal semantic or execution proof.
Start with the [source index](../code_specs/README.md),
[primitive cards](../code_specs/primitives.md) and [review guide](../code_review.md).

This checkpoint adds 413 contracts after [v17](human-inspection-v17-2026-11-12.md):
65 for the new weighted primitive, focused controls and CMake commands; 186 for
statistics tests/fixtures; 162 for memory-account and maintenance-cost tests.
The latter 348 contracts inspect unchanged sources. Their packet postimages and
whole-file hashes preserve exact tokens/literals; no native behavior or test
execution is inferred from a documentation-only review.

## Direct primitive and measured cost

The [weighted-delta contract](../weighted_deltas.md) explains the actual calling
sequence, unsigned signed-magnitude facts, causal telescope, owning/borrowed
lifetimes, failure phases and real costs. The implementation reuses one native
PendingEpoch, its retained grant/compact undo and the existing iterative traversal
kernel. An ordered lookup borrows owned payloads and freezes only new net keys.
Commit drops the lookup and publishes an immutable shared fact owner. No new
production catch or general transaction framework is added.

Root implemented the private proposal, reviewed/tested it, and adopted one
small Astra review suggestion: stop anchor lookup at its unique match. Actual
32-step ordered/indexed probes reduce capture work 382→351 and epoch work 396→365,
with identical results, allocation/free/payload facts, remaining capture counters
and native grants. This is logical-work evidence, not a CPU speedup claim.
Disabled-capture probes preserve work/grants/allocation counts with a measured
fixed 72 pending payload bytes and 16 Epoch bytes; facade size stays 40 bytes.
Enabled traversal can still scan earlier unrelated prefixes. No output-only
complexity or new paper theorem is claimed.

[Final native evidence](w06-weighted-deltas-2026-11-12.md) passes ten selected
weighted/SQL tests per strict Debug and ASan/UBSan/leak profile: 51.73 / 111.04
seconds. The focused new test takes 2.82 / 10.14 seconds, exercises 337 covered C++
new failure positions with retries/teardown, and checks 768 generated private
previews against full independent joins. Enabled contribution updates, arithmetic
abort, committed ownership, nullary UINT64_MAX and exact shared work limits pass.
Native indexed work 1218 without capture / 1474 with capture is admitted at 1474
and rejected atomically at 1473 over 64 resumed stages.

The complete test-disabled production Release build and both runtime-testing
variants pass. A moved installed strict C++23 public consumer passes with 216
installed files and retains shared output after runtime destruction. All 325
predecessor test commands and execution properties remain except source-line
backtraces; weighted_delta is the only addition, for 326 registrations.

## Review source, boundaries and remaining implementation

The statistics/memory test cards distinguish original-account requested/payload
bytes, C++ new interception, direct malloc/syscall limits, borrowed images,
detached owners, exact budget cuts and retry behavior. The canonical map merges
only individually anchored scoped records. All 22 assigned test source files
remain byte-identical. Parent recipe/evidence records bind complete packet file
sets, including auxiliary caller/postimage context rather than only card JSON.

One focused Astra Max reviewer accepts its exact earlier logical-CQ variant
without a required correctness fix. Its snapshot and manifest remain immutable.
Root's early-exit change, three later test controls, final code maps and native
execution are recorded as explicit receiving follow-ups. Other reviews use Luna
Max; root owns design, implementation, proof checks, integration and execution.

Root evidence: `build/verification/w06-weighted-delta-implementation-v1`.
Seal: `build/verification/human-inspection-v18-progress-v1.json`; frozen source:
`build/verification/human-inspection-v18-source-v1`. Active build directories
remain reusable. Earlier source cohorts and two corrected setup attempts remain
preserved; final gates have no in-command source drift. No full326-test run,
Clang gate, broad release or runtime latency claim is made.

W06 is now in_progress. The primitive alone supplies no physical SQL batch,
aggregate coordinator, durable terminal outcome, checkpoint or recovery protocol.
The separate sealed two-file source-batch proposal is ready for root adoption and
native tests; it remains unmerged here. The ledger is 56 verified, two in progress
(A02/W06), 20 not started, 78 total. Full Refactor and per-block review stay active;
see the [handoff](../handoff.md) for the concrete next step.
