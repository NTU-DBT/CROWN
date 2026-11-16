# CROWN continuation handoff

The full Refactor.md implementation goal remains active. The [ledger](task_ledger.md)
is **56 verified / 2 in progress (A02/W06) / 20 not started**, 78 total. No full
release is claimed. A02 license disposition blocks C04/B01; it does not block W06.

The [physical-source capture and inspection checkpoint](verification/human-inspection-v23-2026-11-13.md)
is sealed by `build/verification/human-inspection-v23-progress-v1.json`, with
frozen source `build/verification/human-inspection-v23-source-v1`. Its root packet
is `build/verification/w06-source-image-implementation-v1`. The prior
[V22 checkpoint](verification/human-inspection-v22-2026-11-13.md) remains immutable:
seal `build/verification/human-inspection-v22-progress-v1.json`, SHA256
`8c4b1e91afeb889a975dba564f2063d9a743f1757e74cc6083148c7b4582b0b4`.
The entry audit verifies its 4,432 frozen source paths and 8,460 protected evidence
files. Previous detailed notes are preserved in [the V22 handoff history](handoff-history-v22-2026-11-13.md).

## Live continuation after V23

V23 postcheck passes for all 4,438 live/frozen source paths and 9,043 protected
evidence files. Its seal SHA256 is
`dacaaf88911063ed3618aa678a28c2110094d79c5ee42df9bb2393a97e441f8a`.
Later authorized changes mean its live postcheck must not be rerun.

Root adopts 20 cold-rebuild candidate paths in
`build/verification/w06-cold-rebuild-implementation-v1/receiving-adoption-v1.json`.
Two are new source/test files; two offline role strings add no runtime work.
The private Debug and six-CPP sanitizer units pass. DuckDB1.5.4 Debug and
PostgreSQL16.15 private-sanitizer runs each pass 99 cases / 198 backend requests /
3,436 atomic epochs / 3,634 snapshots and 3,634 actual reconstructions at C0 and
every committed epoch; AVG scales0..18. The private PG cluster is stopped.
Non-owning private weak observations prove both cold lease and allowance control
have no strong owners while the returned owner is live, before normal-context
allocation. These observers are excluded from adoption. Remaining dependencies
in these private sanitizer runs are Release; full maintained SAN remains required.

The 20 ordinary old/new Release cases match exactly for covered C++ new requests,
account current/peak/purpose/lifetime totals, source/native/group work, output and
layouts. This is no CPU timing or portable ABI claim. Strict builds first caught
ambiguous runtime detail names and misleading conditional formatting; root fixes
those directly. A foreign genuine tree rejects with the existing lowerer's
`invalid_plan`, so that one fixture expectation is corrected without translation.
Original failures and author seals remain intact. Main/installed gates are pending.

Planner/initialization169 and delta-maintenance210 test cards are adopted:
canonical13,014 before cold-source cards. Three source candidates change only
comments and 3/3/1 diagnostic literals; non-literal tokens and assertion flow are
unchanged. The continuation injection faults the first intercepted request in a
transition whose clean run improves the incumbent, not a proven publication
allocation. The delta-live label now says anchored completion on the on-output
runtime. Original keyed records/order are preserved. Current maps still describe
V23 until the cold-source review and fresh generation/check complete.

## Current verified behavior

The [composed runtime](sql_aggregate_runtime.md) has genuine original SQL/catalog
binding, one physical-source/native transaction and touched group-only state.
V22 verified 24 selected Debug and full sanitizer tests, independent SQL controls,
a complete test-disabled Release, relocated SDK and exact legacy allocation/work
observations. Its protected private builds and SDK must not be rebuilt.

The [physical source image](sql_source_images.md) is now adopted. It captures all
original nullable physical rows, including filtered/unused tables, actual source
and native recipes/binding, and coherent sequence. It uses shared immutable owners,
one receiving-account entry vector and one finite cumulative capture allowance.
There is no update-path cache, extra hot state or new catch. Main Debug and full
ASan/UBSan each pass all seven focused tests; test-disabled Release and relocated
220-file public SDK consumer pass. Both profiles register 331 tests; all previous
330 commands/execution properties remain, excluding line backtraces. These gates
do not mean that all 331 tests were executed.

The map contains 12,635 source-pinned contracts in 10,274 of 18,466 blocks across
707 files / 164,404 lines. All 5,662 selected production scopes have contracts;
3,193 selected test scopes remain. Structural mapping is not full semantic review.
The 96 result/delta, 97 indexed-session/ingest and 30 source-image cards are integrated. Their
comment/diagnostic corrections narrow claims to directly intercepted ordinary
throwing new forms; indirect delegation is not asserted. Non-literal C++ tokens,
assertions, calls and control flow are unchanged. The ingest candidate changes
18 literal tokens, after the main gates; the offline map generator separately
changes one README prose literal. Exact preimages/proofs and input phases are
preserved in the active packet. No wording-only native rerun is claimed.

## Next implementation

Complete a closed whole-image cold factory before durable W06 integration. The private proposal is sealed at
`build/verification/w06-sql-aggregate-cold-rebuild-design-v1`; its SHA256SUMS is
`bc26e9d4240a7f2eb0bccedc706224f12febd4e17f410a033628f75606e5918a`.
Root verifies all 79 payloads and all 15 maintained preimages. Its 17 postimages
and 105 cards have static checks only; they are not adopted or natively verified.
Review and compile them in a separate receiving packet after this checkpoint. Restore through genuine SQL
lowering and native binding, not a fabricated normalized DTO. Revalidate editable
images; do not treat their fields as authenticated checkpoint authority.

Cold reconstruction needs separate finite cumulative grants for source admission,
native materialization/update and groups. Native StorageWorkContext and
AccountedPlanStorage both enforce the original operational plan grant; the cold
route must preserve immutable original plan/binding identity and close every cold
lease before installing the normal context while unpublished. Do not mutate plan
limits, refill per row/chunk, expose live sequence setters, or replay C dummy
epochs. Final whole-image FK/SUM constraints and coherent source/native/group C
must hold. Varying-int32 column admission remains a separate open requirement.

Then implement the smallest synchronous R2 coordinator: one logged pending
command, one committed output spool, explicit versioned nullable physical batch,
Commit/Reject, descriptor, group sink and checkpoint factories. Reuse genuine
GenerationOwner opaque bounded checkpoint publication, not R1 row/set codecs or
retirement receipts. Separate W logged input, I disposition/source progress,
C runtime epoch and D actual sink acknowledgement. Input fsync precedes mutation;
Commit fsync precedes nonallocating publication. Reject consumes I without C;
resource denial retains pending input; uncertain append requires reopen/recovery.
Empty-output epochs require durable closure. No R2 CLI or durable acceptance exists.

The sealed reuse assessment is
`build/verification/w06-sql-aggregate-durable-assessment-v1/SHA256SUMS`, SHA256
`4db5dbb0d6bf397f1cd7334dbfd9ca6063de16f8fa2cddb6d0787bbc0e24066e`.
Read its assessment/validation/references and the prior runtime packet's
`r2-rebuild-port-notes-v1.md`. P1 aggregation is §7.3; ownership, work and durability
contracts are local engineering, not additional paper theorems.

## Working rules

Start with [primitive contracts](code_specs/primitives.md) and the
[source index](code_specs/README.md). Remaining individual test scopes stay explicit.
A Luna Max agent reviews a separate planner/initialization test batch read-only;
its private proposal is not current coverage. Use own-model review substantially
and Astra Max sparingly, as requested.

Never edit maintained native inputs while recorder jobs are live, or overlap
build/CTest/enumeration in one build directory. Archive terminal LastTest before
the next native action. Main Debug/SAN/OFF builds remain reusable; every sealed
private build, SDK, source and evidence path is immutable. Adopt via fresh writes,
not preserved author mtimes. Native commands require sandbox escalation in this
environment. Do not stage, reset or commit Git. Record failures honestly and run
only checks justified by the implementation change.
