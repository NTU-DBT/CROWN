# AntiGravity / coding-agent handoff

Updated 13 November 2026 (Asia/Shanghai). Full [Refactor.md](../Refactor.md)
implementation remains active and uncommitted at
`e369a623517723b3be3ea3e9806779f3c591e7f9`.
[Ledger](task_ledger.md): 56 verified, two in progress (A02/W06), 20 not started;
78 total. A02 licensing blocks C04/B01, not independent work.

## Current checkpoint

Read [v22 inspection](verification/human-inspection-v22-2026-11-13.md),
[SQL aggregate runtime](sql_aggregate_runtime.md),
[executed checks](verification/w06-sql-aggregate-runtime-2026-11-13.md),
[source index](code_specs/README.md) and [primitive cards](code_specs/primitives.md).
Seal: build/verification/human-inspection-v22-progress-v1.json; frozen source:
build/verification/human-inspection-v22-source-v1. Root evidence:
build/verification/w06-sql-aggregate-runtime-implementation-v1.

Maps: 12,412 contracts / 10,054 authored blocks; 706 files / 164,132 lines /
18,430 mapped blocks. Every inventoried line belongs to an inspection block.
All 5,655 selected production scopes and selected CMake/example/tool scopes have
cards. Remaining selected manual gaps: 3,386 test scopes. Final stable checker:
zero errors / 109,596 generated local links. Structural facts alone are not an
individual usage spec or universal correctness/execution proof.

Since v21: 312 context/explain/lifecycle/session test cards plus 153 composed
runtime/helper/oracle cards. The source-aware review reconciles 1,704 existing
records (1,664 hash-only; 10 semantic; 27 helper reanchors; three CMake context
anchors). Its seal is a2401d86b5a56b7a14ee50f715f9195cc4cd26112057709ea31a563d1b487c80.
The initial selected-block check found two uncovered shared helper callables,
project and argument; root added their actual borrowing/bounds/failure/cost cards.
Do not equate old wrapper cards with coverage of the extracted definitions.

## Accepted in-memory runtime scope

The separate default-built CROWN::sql_aggregate_runtime consumes original SQL/
catalog binding plus genuine physical sql_rows::NetBatch commands. One private
actual source/native token feeds unique native facts into touched group-only
statistics. No joined-row ledger, public prior-weight bypass, production catch,
second undo framework or reparsed/fabricated descriptor is introduced. Shared
W04 arithmetic preserves old single-row behavior. Authentic cold metadata freezes
use the real receiver; same-account imports share. Active tokens retain the owner,
close frees backing workspace, and returned group output drops mandatory D facts.
Touched-group output capacity can remain even when all events are suppressed.

Root adopts 16 source files via adoption-candidate-v1/source-pins.json and
receiving-adoption-v1.json. The runtime author seal is
3e9b336057c473ebd0f356b5c10dad8017d2af2cfa5ffd469428dce3c46bf257;
oracle seal a23797b752787fc343c73078b147834208a5510ac70317fe698c748d809c44e9.
All 79/41 payload entries verify. Runtime production postimages are unchanged.
Receiving changes preserve the compiler SAN block, add runtime/oracle SAN blocks,
add six offline role strings (all function/class ASTs unchanged), and apply two
necessary unit-test repairs plus a planner diagnostic.

Original first fixture has a non-free-connex two-sided source head: a.g/b.y omit
the join separator. Receiving GROUP BY a.id,a.g makes hidden full-key identity
explicit; it is not arbitrary join support or an equivalent rewrite of the
unsupported original. The source-work one-under case catches actual fixed
storage::IndexFailure rather than crown::Error. Original aborts remain evidence.

## Terminal receiving evidence

Strict main Debug 24/24 passes in 129.34s; full ASan/UBSan/leaks 24/24 in 293.94s.
Cohort is 15 prior compiler/parser/W04/W05 checks + 7 weighted + 2 new. Terminal logs:
runtime-debug.LastTest.log SHA 8f275745957eb591767dc2c8b6d95b7337925436a1f0d7d424ea23310604636b;
runtime-sanitizer.LastTest.log SHA 59e05ea8b514116a74b1df10467cc76c7d5eb0fa1a4e161da8afb437f4afd601.
Both profiles preserve all 328 old commands/execution properties except source-line
backtraces; two additions bring 330 registrations. No execution of all 330 or Clang
acceptance is claimed. Complete test-disabled Release includes the runtime archive
and excludes its unit/driver. Relocated 220-file strict C++23 SDK consumer passes
original joined SQL, hidden full keys, foreign-account freeze, caller/facade death
before commit, retained output/program and controller-only teardown.

Actual old/new Release probes preserve all observations across five ordinary W04
cases: constructor/per-operation allocation/account/work, explicit output, layouts.
Metrics/Epoch stay 72/160 bytes on this build. Existing uncaptured updates allocate
zero covered C++ objects; 512 aliases retain work 168. No CPU or portable ABI claim.

Each maintained oracle profile compares 99 cases / 198 backend requests / 3,436 atomic
epochs / 3,634 snapshots: 64 seeded traces × 24 commands plus fixed controls and AVG 0..18.
SQL engines perform joins/predicates/grouping/COUNT/SUM on bounded physical bags;
Fraction rounds exact engine SUM/COUNT for AVG. Full hidden keys, types/names,
before/final changes, flags and all sequences agree. Root private DuckDB 1.5.4
Debug and PostgreSQL 16.15 private SAN runs also pass; PG UTF8/C cluster stops.
Private SAN instruments five proposal CPPs/tests with Release dependency archives;
main full SAN above is separate, not inferred from those private runs.

Resource probes: native D=8/64/256 -> G=1 retains 939 additional accounted result
bytes; returned native bag capture is absent. One touched group among 8/64/256
finalizes one State and reports group_work 16. Exact/one-under receiver grants:
229,866 ordered / 229,777 indexed. Capture/source/native/allocator/map comparison and
cleanup costs remain explicit; these observations do not prove an O(G) whole path.

All 48 recorder jobs are terminal: 43 successes, five preserved failures (three original
fixture aborts, two cost builds before explicit target generation). No in-command
input drift. Final current native input count 1,142. input-cohorts-v1 and receiving-
acceptance-v1 preserve the earlier summary; v2 binds the final current phase.
Two post-gate test wording changes intentionally differ from native cohorts:
delta_lifecycle_exception (one comment + 32 literals) and session_exception (comment
block + 27 literals, +3 lines). Non-literal tokens/assertions/calls/helpers are identical;
full token identity is false. No extra implementation rerun for those edits.

## Comment and contract provenance

The composed_explain comment now says only the lambda-local runtime facade dies;
outer proof/provider/candidate/family still exist during readback. Lifecycle/session
comments and diagnostics scope the ordinary throwing scalar/array replacement-new
seam. Direct malloc/system/account denials have no injected coverage; no dedicated
aligned/nothrow replacements are defined, and indirect library delegation is not
asserted. One unguarded post-start_drain drain no longer claims guarded execution.
Root refines nine receiving lifecycle cards on direct versus indirect coverage;
sealed author packets remain untouched. Integration/refinement/completion receipts
and all full canonical/source preimages are inside the root runtime packet.

The source review's premerge read-only verifier passed against 12,259 cards. Its
unmodified live verifier intentionally expects old scoped records; after merge
use the preserved canonical-preimage.json and root receiving-integration proof,
not a false claim that old projection still equals the live map. The first map
had two helper gaps and its initial link check overlapped a subsequent regeneration;
only stable code-specs-final-v2 and coverage-final-v2 are final evidence.

## Live continuation after v22

V22 seal 8c4b1e91afeb889a975dba564f2063d9a743f1757e74cc6083148c7b4582b0b4
passes postcheck ac2fd91b0e4826456880470b764dddf6b9b6f9cd2fc26e0426194f4adf1242d2.
4,432 frozen source paths / 8,460 protected evidence files. New active packet
build/verification/w06-source-image-implementation-v1/entry-audit.json rechecks
all live/frozen/protected bytes before continuation. Later authorized edits mean
its live postcheck must not be rerun. Prior goal turn is concrete progress.

The formerly pending 96 result/delta failure cards and two comment/diagnostic
candidates are now adopted; canonical 12,508. Corrected cursor has 10 literal edits
plus 4 comment lines; delta has 22 literal edits plus 3 comment lines. Non-literal tokens,
conditions/calls/helpers are unchanged. Integration proof is human-contract-
integration-v1 under the new active packet; no wording-only native rerun. Maps
still describe the V22 phase until new source-image cards/gates are integrated.

Root implements source_snapshot privately in four API/runtime postimages plus
new unit sql_source_snapshot_test.cpp. It captures all physical maps, actual
source/native program and weighted binding, sequence and receiver-owned row
handles, with cumulative row/field/retained-string-extent limits. No per-update
state, joined row mirror, payload clone or new catch. Strict private compile and
both-backend tests pass: one covered-new failure position/backend, exact/one-under
work and row caps, reader/pending exclusion, retained rows after erase and facade
death, no-allocation moves and controller-only teardown. Initial test compile
wrongly used fault.triggered instead of s04_alloc::triggered; fixed test only,
failed receipt preserved. Private SAN build is live; dependencies are Release SDK.
This capture API is not adopted or a durable checkpoint yet. Root will run full
maintained/installed gates after source review. Source and test bytes remain pinned
in the active packet, not in protected V22 directories.

One normal-model agent prepares a separate closed whole-image cold rebuild. It
found that native context and AccountedPlanStorage operation_work both enforce
the original plan grant. A separate cold context/private materialization admission
must preserve immutable original plan identity and replace context only before
unpublished return, after every cold lease closes. Do not use a smaller operational
grant as substitute for genuine cold budgets, mutate plan limits, refill chunks or
expose live sequence setters. This is still private design work. One Luna reviews
source-image cards; another reviews indexed-session/ingest exception tests.

## Continue here

A ready UNMERGED Luna packet supplies 96 baseline / 96 receiving cards for result-
cursor and delta-runtime failure tests:
build/verification/result-delta-failure-tests-human-contracts-v1, seal
acaad1030fc7c6c72dfc828b8bf1fcb478a3951714a6be957637b3e8fee77c16.
Root verified all 25 payload entries. Candidate cursor hash
340cf956a7ec7638eeb3c7357b8a5ee585afd3d2c0e7680e7890a9595f30c05e;
delta hash 120126329f78a808fba1cdefca2ab4b91754992e0fac5ad3b7a7d5f6808efd37.
Inspect exact comment/diagnostic changes, current preimages and non-literal proof
before adopting after v22. Source targets remain unchanged in this checkpoint.
Do not count those 96 toward current coverage or repeat native tests for review-only
work. Reviewer final metadata print used a wrong key after integrity assertions;
actual sealed pins are authoritative. Continue bounded existing test reviews.

W06/R2 durable integration is still unimplemented. The sealed actual-code reuse
assessment is build/verification/w06-sql-aggregate-durable-assessment-v1,
SHA256SUMS 4db5dbb0d6bf397f1cd7334dbfd9ca6063de16f8fa2cddb6d0787bbc0e24066e.
Root verifies all 81 payload entries. Read assessment.md, validation.md, references.md
and root r2-rebuild-port-notes-v1.md before changing code. They are guidance, not
implemented ports or a durable acceptance result. Actual P1 aggregation is §7.3;
no SQL/account/durability theorem follows from its weighted context.

First implement bounded authoritative full physical-source capture (all original
tables, including filtered/unused), actual owner source/weighted binding observation,
and a closed genuine whole-image cold rebuild with coherent source/native/group
sequence and separate cumulative build grants. No public sequence setter, C dummy
epochs, row/chunk grant refills, fabricated normalized DTO or group/join mirror as
truth. Final FK/SUM constraints must hold on the whole valid image. Varying-int32
column admission remains separate and open; literal SUM/wide tests do not close it.

Then add the smallest separate synchronous R2 coordinator: one owned logged pending
command and one committed output spool; explicit new versioned descriptor/WAL/
nullable group sink/checkpoint factories. Reuse actual generation/file publication
where its opaque payload contract permits; do not reinterpret R1 one-row/set tags
or typed retirement receipts. Separate W logged input, I durable disposition/source
progress, C genuine runtime epoch, D actual sink-ack prefix. Input fsync precedes
mutation; Commit fsync precedes nonalloc publication; semantic Reject consumes I
without C; resource denial retains pending input; uncertain append latches recovery-
required. Empty-output epochs need durable closure. Caller status is no sink proof.
No R2 CLI/source/sink/recovery result exists yet. Full Refactor/release stays open.

Never mutate maintained native inputs while recorder jobs run; never overlap
CTest/build/enumeration in one dir. Archive terminal LastTest before the next native
action. Adopt with fresh writes (old copy2 mtimes caused a preserved no-op in v19).
No Git commit/reset/stage, merge, deployment or external message has occurred.
Main native build dirs remain reusable; protected private builds and SDKs do not.
V21 compiler seal d37f17ccf243cefb77c0badc3a0f181d854a6a531ba3330c0f584c85b258a028,
4,417 frozen paths / 7,511 evidence files. V20 seal
5d5c117c9abe996fb31f78b2f5c18e58016eb9afe77d6378e1ab1acba5691835,
4,406 frozen paths / 6,854 evidence files; V19 db9b3011f978bf128a58426bfc095807bd72c3f9e5329d2e3601f3825e2da11f;
v18 0462fc8ea3f14ebcf83bf21fef8b3b4a0708961a31812d67254f3cbc0217321a.
Never rerun predecessor live postchecks after authorized changes; verify frozen
source/protected evidence instead. All existing failed attempts remain intact.

## Immutable predecessors and workspace rules

Corrected v13 seal `build/verification/human-inspection-v13-progress-v2.json`
SHA-256 `47291c0b170ab462a46ca12d648c528578c486278857fc6d407cc3313f97fb9c`;
frozen `build/verification/human-inspection-v13-source-v2`. Original v13 v1 and
its incomplete packet-list recipe remain preserved; v2 explicitly checks all
three review packets. Never use broad string replacement for packet paths.


V12 seal `build/verification/human-inspection-v12-progress-v1.json` SHA-256
`8dc1779dd100077b3a727c47f81b900d6e773a46ba2cfe66d45b0cfc1dc29c26`;
frozen `build/verification/human-inspection-v12-source-v1`. Runtime/storage
header comment-only continuation; 6,671 contracts; no repeated native execution.


V11 seal `build/verification/human-inspection-v11-progress-v1.json` SHA-256
`488e2846f5e527e6ce447ada198216855f93779cabf8df0a3d3c499043ad79e6`;
frozen `build/verification/human-inspection-v11-source-v1`. Its 26/26 profiles
verify the CLI process boundary and prior scoped runtime/recovery/query work.
All 324 original registrations remain; new process test appends for 325.


V10 seal `build/verification/human-inspection-v10-progress-v1.json` SHA-256
`1c4988403b5cf8edeb15fa3075215644016a62d4346ff60f32486c6d4e6b0373`;
frozen `build/verification/human-inspection-v10-source-v1`. Its 30/30 profiles
verify clock-cancellation lifecycle checks and sorted histogram lookup.


V9 seal `build/verification/human-inspection-v9-progress-v1.json` SHA-256
`98af10d2b1684295cda2485c4bb4eba03cb9f161e658f3e9f3c4a66044ae56b1`;
frozen `build/verification/human-inspection-v9-source-v1`. Its18/18 profiles
verify integer-guard cleanup and input/recovery/window/report scopes.


V8 seal `build/verification/human-inspection-v8-progress-v1.json` SHA-256
`45d02d750cea2d1a5094365b8c3f947414eb48cbe1d0c120255a50748e2e17eb`;
frozen `build/verification/human-inspection-v8-source-v1`. Its 24/24 Debug and
sanitizer cohorts verify the Delta backend fix and redundant sink catch removal.
Legacy v2 descriptive quota text stays byte-identical; accurate quota is in docs.
W05 SQL seal `build/verification/w05-rows-progress-v1.json` SHA-256
`7329de62ad308ed40b7f4a4aae38ea3c01e6391b3b118a601f79c2f1287fe8c7`;
frozen `build/verification/w05-rows-source-v1`. W04 and W05 foundation seals remain
immutable too. Never reinstall into preserved `build/w05-rows-sdk-v1`.

Keep code direct; specs state usage, ownership/lifetime, failure phase, actual
cost and precise paper/local references. Use root reasoning substantially,
Luna Max for simple work, Astra Max sparingly. Multiple review agents are
explicitly authorized. No AGENTS.md found. All shell commands need
require_escalated because default sandbox launch fails; no auto-review rejection.
Preserve all staged additions/untracked work and read-only .git. Never reset,
stage or commit. W05 build dirs are active/reusable after evidence/source is
preserved; recorded native hashes are observed bytes. No CTest/build overlap in
one dir; archive terminal LastTest before another build/CTest/enumeration. Use
strict C++23 warnings as errors and preserve every failed receipt/preimage.
