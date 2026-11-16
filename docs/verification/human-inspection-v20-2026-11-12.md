# Inspectable prepared aggregate groups and failure controls

The maps contain **11,502 source-pinned contracts in 9,146 blocks**, across
696 maintained code files / 161,845 lines / 18,141 mapped blocks. All 5,554
selected production scopes and all selected root CMake/module/example/tool
scopes have authored contracts. Every inventoried line is structurally mapped.
Remaining selected manual gaps are 4,048 test scopes. A map supports examination;
it is not universal semantic or execution proof. Start with the
[source index](../code_specs/README.md) and [primitive cards](../code_specs/primitives.md).

This adds 195 contracts after [v19](human-inspection-v19-2026-11-12.md): 42 for
the prepared aggregate variant and 153 for unchanged candidate/initialization
failure tests. All 106 existing aggregate cards are reconciled: 85 hash-only,
21 semantic or anchor updates. Root refines three cost descriptions to distinguish
zero-width State buffers and token-retained owners from facade destruction.
Original review packets stay unchanged.

The [aggregate batch contract](../aggregate_batches.md) explains unique signed
logical deltas, the actual row ledger, touched groups, one Budget, exact wide
sufficient statistics, final SUM checks, output identity and nonallocating
publication. It adds no production catch or second undo layer. A compile-time
policy preserves single-row SUM behavior; four batch-only counters move into
BatchMetrics, preserving legacy Metrics/Epoch sizes at 72/160 bytes.

[Executed checks](w06-aggregate-batches-2026-11-12.md) pass all four aggregate
tests in strict Debug and ASan/UBSan/leak profiles, 3.60 / 12.39 seconds. The
existing runtime test executes four new batch fixtures before its preserved
W04 controls. Complete test-disabled Release and a moved installed strict C++23
consumer pass. The consumer replaces two groups, destroys caller text and the
facade before commit, and retains owning output/program handles. All 327 CTest
definitions remain byte-identical; execution of all 327 tests and a Clang gate remain open.

Actual v19/new Release probes preserve constructor/per-operation allocation
counts, selected work and explicit outputs across five ordinary single-row cases.
Shared ownership/busy state adds 56 fixed accounted bytes; facade size is 40→16.
The legacy value layouts remain unchanged. These are storage/work observations,
not CPU speedups, global-heap coverage or portable ABI promises. Detached nodes
still require logarithmic destination-map comparisons.

The 153 failure-test cards add no source edits or execution claims. They specify
actual C++ new fault interception, ContentBudget limits, borrowed/detached
oracles and owner lifetimes. Candidate same-owner retries differ from fresh
factory/admission trials; initialization/rebuild teardown is not a retry of a
partially published owner. Two recorded context drifts are preserved rather than
silently rebasing old review hashes.

One focused Astra Max review examines the next, unadopted compiler proposal and
requires revision: normalized output equality can merge originally ungrouped
columns; pinned upb DeepClone has unsafe allocation-failure paths; CMake lacks
one UTF-8 support include directory. Root reproduces all three grouping cases in
a private strict executable after correcting only its harness include path.
The proposed positive controls pass but miss those cases. No unsafe-clone crash
injection or production compiler adoption is claimed. A separate repair uses
genuine original column origins and checked wire decoding; it remains next work.

Root evidence: build/verification/w06-aggregate-batch-implementation-v1. All 12
aggregate recorder jobs pass without in-command drift, binding 1,132 maintained
inputs in their recorded cohorts. Only the existing aggregate header/runtime
production files change from v19; the other 325 production files stay identical.
Frozen source/evidence and moved SDKs remain immutable; main builds stay active.

Seal: build/verification/human-inspection-v20-progress-v1.json; frozen source:
build/verification/human-inspection-v20-source-v1. W06 remains in progress:
standalone prepared groups do not supply a closed genuine-source contribution
port or coordinated publication, durable outcomes, session/checkpoint/recovery,
or operational CLI. Varying-int32 SUM admission also remains explicit. The full
ledger stays 56 verified / two in progress / 20 not started. Continue from the
[handoff](../handoff.md); remaining test reviews are separate bounded tasks.
