# AntiGravity / coding-agent handoff

Updated 12 November 2026. The full [Refactor.md](../Refactor.md) implementation
remains active and uncommitted at `e369a623517723b3be3ea3e9806779f3c591e7f9`.
The [ledger](task_ledger.md) is **55 verified, two in progress (A02, W05), 21 not
started; 78 total**. W04 is verified within its explicit admitted scope.
Individual human review across the repository and all release reviews remain open.

## Current checkpoint

Read [W04 verification](verification/w04-aggregates-human-inspection-2026-11-12.md),
[aggregate semantics/usage/costs](aggregates.md), the
[source index](code_specs/README.md) and [primitive cards](code_specs/primitives.md).
Acceptance: `build/verification/w04-acceptance-v1.json` (16 requirements).
Final source/evidence seal: `build/verification/w04-progress-v1.json`.
Frozen source: `build/w04-source-v1`. Never mutate sealed source/build/evidence
or rerun native jobs there. New work needs new build/evidence versions.

The opt-in `crown_aggregate` / installed `CROWN::aggregate` component admits one
flat logical bag input or no-FROM singleton, GROUP BY input columns, nullable
arguments/keys and integer COUNT/SUM/AVG. COUNT forms are separate; every DISTINCT
aggregate form rejects explicitly. SUM(integer) checks bigint range even with
capture off; SUM(bigint) is NUMERIC(38,0); AVG keeps exact sum/non-NULL count and
NUMERIC(38,s), s=0..18, ties away. The fixed output type is a local contract.
General SQL bag/NULL admission remains W05; cross-runtime batches/recovery are W06.
Existing set SQL wire meanings/backend admission remain separate.

Compiler metadata and runtime allocations have explicit finite accounts; callers
can supply one shared account. New keys/nodes/output are funded before state
publication, with no production catch/undo framework or whole-state copy. Default
off capture avoids output rendering/cleanup; repeated output arguments share
statistics. Explicit invariant recomputation is full diagnostic work. Serialize
all runtime calls, including const diagnostics. Physical/ordered-row comment
changes preserve executable tokens and explain actual map/ledger/teardown costs.

## Verification and review

There are 3,049 source-pinned usage contracts in 2,524 mapped blocks. All 677
maintained code/build/test files, 156,013 lines and 17,383 blocks are structurally
mapped. New contracts cover all substantive assigned aggregate scopes, alongside
the integrated physical and private arithmetic scopes. Structural-only regions
elsewhere remain individual semantic-review work (3,171 selected production
blocks: 687 include, 2,427 src, 57 apps); do not refresh a review hash
without checking its code and contract. The standalone generator/checker adds no
runtime instrumentation.

Strict GCC Debug and ASan/UBSan/leak gates use identical 1,114 current native
inputs. Four aggregate tests plus 18 foundation controls pass in one final cohort per
profile (22/22: 24.48 s Debug / 88.76 s sanitizer). Raw LastTest logs are archived. SQL oracle:
172 expanded SQLite GROUP BY/COUNT/SUM cases / 4,393 snapshots; AVG uses exact
Fraction from SQL sufficient statistics. Forty-six compressed large-weight cases / 150 snapshots compare native COUNT
outputs with SQL integer weighted-sum identities (298 scalar checks); their wide
SUM/AVG stay Python exact evidence. Both oracles cover all nineteen AVG scales. Private
arithmetic: 2,542 cases / 31,275 observations. Per fixture, 34 constructor/update
and three snapshot fault positions pass retries/sentinels; do not call them a
global unique count. Receiver exact/one-under peak: 4,594 requested bytes. The
512-alias control has zero heap requests/equal logical work 168 with capture off;
no timing speedup follows. Retained results, final program ownership and actual
W03 compressed ingestion with both backends pass; the test explicitly retracts
the tuple in the aggregate, without a producer deletion or automatic delta adapter. Installed public consumer passes.

All 315 predecessor test definitions/properties remain; four append for 319 total.
Final receipts: `w04-module-build-*-v3`, `w04-final-ctest-*-v1`, `w04-cli-build-debug-v2`
and `w04-{install-debug,installed-consumer-configure,installed-consumer-build,installed-consumer-run}-v2`.
Five historical syntax/build-command corrections are retained separately; final
native gates pass with no source drift. The final audit closed the original
large-count SQL and sampled-scale evidence gaps; keep the v1 oracle/gate packets
unchanged and use the corrected coverage-v2/final-profile records. No full 319-test, Release/Clang, PostgreSQL
server, W06 crash/recovery or latency experiment is claimed.

All 160 constant-route artifacts and 2,457 frozen predecessor source paths remain
unchanged. That repair, its negative probe, old failed test and older inspection
packets stay sealed. Its original-query proof/key provenance versus empty operator
geometry remains authoritative. The [prior handoff](handoff-history-w04-start-2026-11-12.md)
is a byte-identical archive of the W04-start handoff and earlier evidence chain.

## Active W05 work

The next continuation now implements the opt-in nullable SQL compiler and
physical bag source runtime. Read [the active runtime guide](sql_rows_runtime.md)
and `build/verification/w05-rows-implementation-v1/`. Initial strict Debug
compiler/runtime gates pass, including 248 allocation cuts across four
backend/capture fixtures, five output-copy cuts per backend, source-work
exact/one-under checks, and receiver peaks 56,919 / 60,001 requested bytes.
These observed peaks precede the result-schema lifetime extension; its final
gate is still pending. A sanitizer build passed; sanitizer tests and complete
mature-engine/final regression gates remain outstanding. Do not infer W05
acceptance or current regenerated source-map counts from these partial results.

The accounted-plan reviewer supplied 58 more contracts and nine comment-only
clarifications, integrated with complete executable-token equality. Canonical
cards now total 3,702 before the new SQL cards and pending support review;
maps have not yet been regenerated for the new files. The independent compiler
review found unnecessary hidden fields for local equality (corrected) and an
allocation-boundary comment mismatch (corrected). Its runtime appendix identified
schema ownership for returned SQL rows; the implementation now shares its
immutable program in each result, with verification in progress.

The foundation checkpoint below remains sealed. Active W05 build directories
have since been reused only after preserving their terminal logs and preimages.

The W04 checkpoint above stays sealed. W05 starts from
`build/verification/w05-start-v1/preimages.json`; its 2,484 source before-images
are in `build/verification/w05-preimages-v1`, and all 310 W04 evidence artifacts
matched before work began. The bounded Luna Max inventory is staged at
`build/verification/w05-sql-bag-inventory-v1/README.md`. Design and implementation
progress is in `build/verification/w05-start-v1/design-notes-v1.md` and
`progress.json`. The [current SQL rows guide](sql_rows.md) and
[foundation verification](verification/w05-foundations-human-inspection-2026-11-12.md)
describe the implemented primitives. The earlier scalar gate passes 14 selected
names and 3,439 matching-type DuckDB cases; `scalar-progress-v1.json` preserves its
seven-file source overlay, raw logs and dependency limits.

WeightedRuntime now has `create_into` for a supplied account and
`PendingEpoch::stage_contribution(NodeId, TupleValuesView, old, next)` for one
adapter-owned share. The latter computes total-old+next at the existing lookup,
reusing one epoch/grant/abort boundary with no duplicate native count map or larger
queue payload. The adapter still authenticates physical source identity/old
weight. Successful committed captures contain totals; aborted traces can retain
attempted shares before normalization. The original absolute path/order remains.
Both create_into overloads reject empty accounts and report the receiver's actual
cap. Distinct compiler accounts remain unchanged; shared-account costs are visible.

The current 23-name cohort passes strict Debug (59.46 s) and ASan/UBSan/leaks
(213.39 s) on identical 1,117 inputs, with no drift. Raw logs are archived. Each
input kind observes 1,108 allocation-cut positions across eight fixtures; all
eight matched absolute/contribution request counts agree. Receiver construction
has 153/156 positions and exact/one-under peaks 115,989/118,072 requested bytes.
Read `build/verification/w05-weighted-composition-v1/native-evidence-v1.json`
and `source-overlay-v1.json`: sixteen native deltas relative to W04, 82 linked
artifacts / 352 C++ objects. The three initial standalone syntax commands missed
the vendor include path; corrected commands pass. All 319 predecessor registrations
are preserved, with only sql_scalar_oracle appended for 320 total.

Current maps have 3,644 contracts in 3,098 reviewed blocks; 680 maintained files /
156,600 lines / 17,451 blocks are structurally mapped. Individual inspection still
needs 2,750 selected production blocks (614 include, 2,079 src, 57 apps). The
reference/resource/weighted/indexed/annotation packets are integrated by exact
source/contract keys. This continuation's nine source comment edits preserve
executable tokens; indexed optional comments remain unapplied. The current indexed
guide names AccountedStorageTable/AccountedPlanStorage separately from standalone
tables.

PostgreSQL 16.15's capability probe preserves exact mixed-scale NUMERIC/NULL and
selected C-collation results; both temporary server starts are stopped. It is not
native CROWN agreement. The current partial checkpoint is
`build/verification/w05-composition-progress-v1.json`. W05 acceptance is incomplete:
actual nullable/bag compiler/source/runtime work remains. build/w05-debug and
build/w05-sanitizer stay ACTIVE and unsealed; archive logs and preserve this
source/evidence before reuse. Classical core nullability and frozen normalization
v1/v2 meanings remain unchanged unless a new supported boundary is implemented
and verified. Proposed next steps are in `rows-implementation-notes-v3.md` under
the active W05 start packet; they are not completed behavior.

## Continue the full goal

Start W05 from its unchanged Refactor acceptance: general SQL NULL/type behavior,
plain SELECT bags and explicit source admission. Keep general SQL equality NULL
rules separate from aggregate grouping NULL behavior; preserve set-mode fixtures.
W06 coordinates aggregate transactions/batches/checkpoint/recovery after W05.
Continue the user-requested primitive review in parallel, prioritizing uncovered
production blocks and direct implementation/performance costs. Use the current
model substantially, bounded Luna Max work for simple inventories and Astra Max
sparingly. Root owns implementation, integration and final native gates.

A02's intended distribution-license disposition remains pending; do not repeat the
question while independent work remains. C04/B01 and later experiments/extensions
still have their declared dependencies. Keep the complete 78-card goal active;
a verified W04 checkpoint is not full implementation or release completion.
