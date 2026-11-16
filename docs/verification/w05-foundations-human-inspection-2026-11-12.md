# W05 foundations and continued human inspection

W05 and the full Refactor goal remain in progress. The ledger is 55 verified,
two in progress and 21 not started. This checkpoint verifies shared primitives
and their direct composition; it does not admit complete nullable SQL sources,
joins, DISTINCT or plain SELECT bags. Read the [SQL rows guide](../sql_rows.md)
for implemented boundaries and remaining work. W04 and earlier evidence stay
sealed.

## Implemented composition

`WeightedRuntime::create_into` accepts an existing account and either a physical
plan or compiled program. Its actual cap is authoritative, including existing
resident bytes; empty receivers reject before any replacement-new request.
Frozen metadata and mutable weighted state use that receiver. A separate compiler
account stays unchanged; deliberately shared compiler/execution ownership remains
visible in the shared account.

`PendingEpoch::stage_contribution` replaces one adapter-owned share at the existing
native-row lookup: `total - old + next`. It takes a complete native-scope
`TupleValuesView`, validates/freezes it synchronously, and retains no borrowed
caller cells/string bytes. The adapter must authenticate its physical source row
and old share. All staged aliases use the existing epoch, undo and indexed grant.
The port adds one charged checked arithmetic replacement, with no second native
count map, larger queue payload or additional catch. Absolute replacements keep
their expected-total check and prior work/validation ordering.

Committed native captures contain logical totals. Aborted captures are partial
attempts: a failing contribution can retain its raw shares before normalization.
An execution ordinal marks entry, not successful completion. The public comment,
guide and reviewed cards state this distinction. A native fixture checks committed
totals and rollback; it does not retain/assert the failing raw event. That
diagnostic-branch limit is explicit in the independent review.

## Human contracts and source comments

The index now contains **3,644 source-pinned contracts in 3,098 mapped blocks**.
All **680 maintained files, 156,600 lines and 17,451 blocks** have structural maps.
Other mapped regions remain structural facts rather than individually approved
usage specifications. **2,750 selected production blocks** remain on the semantic
review list: 614 include, 2,079 src and 57 apps. This is not complete repository
inspection.

From the W04 checkpoint, the current W05 work adds 595 net contracts. The shared
scalar/storage phase added 119; this continuation adds 476:

| Scope | New contracts | Review |
| --- | ---: | --- |
| Reference table and backend dispatch | 147 | [Source/ownership/error/cost review](../../build/verification/w05-reference-storage-human-review-v1/report.md) |
| Resource allocators, accounts and text | 72 | [Resource review](../../build/verification/resource-human-review-v1/report.md) |
| Weighted composition, public types and tests | 82 | [Independent composition review](../../build/verification/w05-weighted-composition-human-review-v1/report.md) |
| Standalone indexed table and journal | 117 | [Indexed review](../../build/verification/w05-indexed-storage-human-review-v1/report.md) |
| Annotation arithmetic | 58 | [Root source review](../../build/verification/w05-annotation-human-review-v1/report.md), [independent assessment](../../build/verification/w05-annotation-independent-review-v1/report.md) |

Six reference/dispatch comments and three resource comments preserve all
executable tokens, including literals. They distinguish ordered-handle traversal
from more expensive borrowed-entry lookup, real repeated projection work,
representation-dependent Tuple copies, final-owner teardown and text-copy/report
costs. The indexed source-unchanged card variant is integrated; its five optional
comment postimages remain separate. Its existing comments were accurate.

The resource cards correct two descriptions: nonpropagating container assignment
does not describe assigning an allocator object, and attributed usage accumulation
relies on admitted disjoint subsets rather than throwing checked arithmetic.
Root-authored annotation cards received two independent clarifications: aligned
zero normalization scans, and generic additive-zero/equality obligations plus the
final payload copy. No runtime machinery is added by these documents.

The resource/reference cleanup catches remain necessary. Indexed sources already
have no catch clauses; admission/inverse preparation precedes publication. The
[indexed guide](../indexed_storage.md) now identifies the current account-funded
runtime interfaces separately from standalone tables and historical measurements.
See [error dispositions](../code_specs/error_handling.md) before changing those
ownership boundaries.

P1's corrected v2 §7.3 supplies aggregation context, as explained in the
[source map](../code_review.md). It does not establish these native allocator,
adapter, rollback or latency contracts. Private arithmetic bounds and engineering
costs point to their actual local descriptions.

## Native verification and limits

Strict GCC Debug and ASan/UBSan/leak profiles pass the same **23 selected tests**:
59.46 seconds Debug and 213.39 seconds sanitizer. Both builds and CTest receipts
have identical 1,117 maintained input hashes and zero source drift. Raw LastTest
logs are archived before any later native operation. This is a selected cohort,
not a full 320-test execution, a release or a latency benchmark.

The cohort includes six weighted controls/oracles, source-account/memory tests,
reference/dispatch/journal/arena/layout controls, native program import, physical
execution/exceptions and constant routes. Independent Python oracles compare
1,516 full-message update states and 2,910 projected-bag states across both
backends. They are direct-CQ oracles, not W05 mature SQL agreement.

For each input kind, allocation sweeps observe 1,108 failure positions across
eight backend/capture/creation fixtures. The contribution and absolute paths have
equal request counts in every matched pair. This is 2,216 positions across both
input kinds per profile, not a global unique fault count. Commit and rollback
allocate nothing in their observed scopes. Native-grant exact/one-under controls
reuse one grant across 64 stages and a private snapshot through either port.

Receiving construction sweeps observe 153 ordered and 156 indexed positions,
preserving an existing 128-byte sentinel allocation. The twenty-row scenario's
exact/one-under requested-byte peaks are 115,989 and 118,072 respectively. These
are finite fixture results, not universal sizing recommendations. Typed borrowed
strings including NUL, Boolean, date and 38-digit decimal remain owned after the
caller changes its buffers; this tests the classical native port, not SQL TEXT
domain admission.

The native inventory pins 82 actually linked archives/executables and 352 C++
objects across the two profiles, with their actual link/flag metadata. The sixteen
native source deltas are frozen relative to W04. Read
`build/verification/w05-weighted-composition-v1/native-evidence-v1.json` and
`source-overlay-v1.json`. The W05 build directories remain ACTIVE and unsealed;
preserve receipts/raw logs/source overlays before reuse. Three initial standalone
syntax commands omitted the vendored JSON include path; their failed receipts
are retained and all three corrected commands pass without a code fix.

The earlier [shared scalar gate](../../build/verification/w05-start-v1/scalar-progress-v1.json)
still records 3,439 matching-type DuckDB cases and its separate 14 selected names.
The [registration audit](../../build/verification/w05-registration-v1/README.md)
retains all 319 W04 commands, full properties and backtraces, with only the scalar
oracle appended for 320 registrations. No new test registration was needed for
the weighted fixture extensions.

The isolated PostgreSQL 16.15 [capability probe](../../build/verification/w05-postgres-probe-v1/README.md)
demonstrates selected exact mixed-scale NUMERIC, NULL/grouping, date/Boolean and
C-collation values. Both starts were stopped and verified. Its initial query and
local-validator corrections remain visible. It is engine capability evidence,
not native CROWN/SQL agreement. The W05 installed consumer, Release/Clang,
end-to-end nullable/bag source runtime, W06 recovery and performance experiments
remain separate required work at their appropriate acceptance boundaries.
