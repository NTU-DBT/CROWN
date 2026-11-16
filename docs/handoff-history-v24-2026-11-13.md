# CROWN continuation handoff

The full Refactor.md implementation goal remains active. The [ledger](task_ledger.md)
is **56 verified / 2 in progress (A02/W06) / 20 not started**, 78 total. No full
release is claimed. A02 license disposition blocks C04/B01; it does not block W06.

The latest [V24 checkpoint](verification/human-inspection-v24-2026-11-13.md) is
`build/verification/human-inspection-v24-progress-v1.json`, with frozen source
`build/verification/human-inspection-v24-source-v1`. Its root packet is
`build/verification/w06-cold-rebuild-implementation-v1`. Prior detailed live notes
are preserved in [the V23 handoff history](handoff-history-v23-2026-11-13.md).

## Current verified behavior

The [composed runtime](sql_aggregate_runtime.md) has genuine original SQL/catalog
binding, one physical-source/native transaction and touched group-only state.
The [source image and closed cold factories](sql_source_images.md) capture all
physical rows, including filtered/unused tables and NULLs, and reconstruct them
through genuine lowering/binding and final row/UNIQUE/FK validation. At C>0 only
unpublished owners start at C−1 and commit one complete seed at C. C0 initializes
authentic static/global-empty state once; UINT64_MAX is terminal.

Separate finite source/native/indexed/group build grants do not replace original
operational domains or plan caps. Cold journals/cursors/outputs/grants close
before normal-context installation. There is no added hot field, joined-row
mirror, live sequence setter, production catch or second undo system.

The [receiving checks](verification/w06-cold-rebuild-2026-11-13.md) pass all 19
selected tests per strict Debug/full ASan+UBSan+leak profile: 119.15s/312.03s.
Complete OFF production Release and relocated 220-file strict public SDK pass on
both backends. The SDK releases the original account while the rebuilt owner is
live, then commits the next exact output diff. Private weak observations prove
actual lease and allowance strong owners expire before normal-context allocation;
those observers are excluded from adoption.

Each maintained reconstruction oracle checks 99 cases / 198 backend requests /
3,436 atomic epochs / 3,634 snapshots and actual reconstructions, AVG scales
0..18. Separate private DuckDB 1.5.4 Debug and PostgreSQL 16.15 sanitizer runs pass;
the private PG cluster stops. Six CPPs/test/driver are instrumented privately,
while underlying dependencies are Release; the maintained full SAN is separate.
All 331 predecessor test commands/properties remain except line backtraces;
333 are registered. Execution of all 333 and a Clang gate remain unclaimed.

Actual old/private/new installed Release observations match exactly in 20 normal
SQL scenarios: C++ new requests, account current/peak/purpose/lifetime totals,
source/native/group work, outputs and layouts. No CPU timing or portable ABI
claim follows. Strict build namespace/format repairs and the foreign-tree fixture's
actual invalid_plan carrier are preserved with five original failed receipts.
All 39 recorder jobs are terminal, 34 successful, with no in-command input drift.

## Human inspection

The [source map](code_specs/README.md) contains 13,275 contracts in 10,900 of
18,549 blocks across 709 files / 165,172 lines. All 5,687 selected production
scopes have contracts; 2,641 selected test scopes remain. Structural mapping is
not full semantic certification. The [primitive guide](code_specs/primitives.md)
uses 464 source links instead of thousands of duplicate card rows; all detailed
seven-field block contracts remain in their source pages.

V24 adds 552 existing-test cards and 88 cold-source/API/test/CMake/oracle cards,
with 2,086 exact keyed updates plus 45 reviewed offline generator records.
Test corrections change only comments/diagnostic strings. The final offline
formatter and two residual-test literals occur after native gates and have exact
separate phase proofs; no wording-only native rerun is claimed. Original keyed
records and master order are preserved. The source review is Luna-authored and
root-finalized after root independently verifies preservation and all scopes.
Its sealed packet must not be rewritten or rerun as an authoring task.

## Continue here

All current review packets are integrated. Continue individual test reviews in
bounded read-only batches using Luna Max; use root for substantive implementation
and verification, and Astra Max sparingly for demanding independent reviews.
The current turn used one bounded Astra review, with both validation gaps closed.

Next implement the smallest synchronous R2 coordinator with one logged pending
command and one committed output spool. Add explicit versioned nullable physical
batch, Commit/Reject, descriptor, group sink and checkpoint factories. Authenticate
original SQL/catalog/parameters/scales/options, native binding and source/frontier
authority before feeding decoded rows to the genuine cold factory. Editable
SourceSnapshot fields are data, not durable provenance or search-optimality proof.

Reuse actual GenerationOwner opaque bounded checkpoint publication; do not
reinterpret R1 row/set codecs or retirement receipts. Separate W logged input,
I disposition/source progress, C runtime epoch and D actual sink acknowledgement.
Input fsync precedes mutation; Commit fsync precedes nonallocating publication.
Reject consumes I without C; resource denial retains pending input; uncertain
append requires reopen/recovery. Empty-output epochs require durable closure.
No R2 CLI or durable acceptance exists. Varying-int32 column admission stays open.

The sealed reuse assessment is
`build/verification/w06-sql-aggregate-durable-assessment-v1/SHA256SUMS`, SHA256
`4db5dbb0d6bf397f1cd7334dbfd9ca6063de16f8fa2cddb6d0787bbc0e24066e`.
Read its assessment/validation/references and the previous runtime packet's
r2-rebuild-port-notes-v1.md. P1 aggregation is §7.3; ownership, work and durability
contracts are local engineering, not additional paper theorems.

## Working rules

Never edit maintained native inputs while recorder jobs are live, or overlap
build/CTest/enumeration in one build directory. Archive terminal LastTest before
the next native action. Main Debug/SAN/OFF builds remain reusable; every sealed
private build, SDK, source and evidence path is immutable. Do not rerun an old
live-source postcheck after authorized edits; verify its frozen/protected files.
Adopt through fresh writes, not preserved author mtimes. Native commands require
sandbox escalation in this environment. Do not stage, reset or commit Git.
Generate maps before running the checker; do not race them. Record failures and
run only checks justified by actual changes. The active goal remains incomplete.
