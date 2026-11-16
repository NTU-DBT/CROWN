# CROWN
This project provides the source code of our paper: [Change Propagation Without Joins](https://www.vldb.org/pvldb/vol16/p1046-hu.pdf). It also contains the scripts for reproducing the experiment results in the paper.

The CROWN Next refactor has a separate C++23 library and CLI.

Start with the [SQL quickstart](docs/quickstart.md), then read the
[current interfaces and guarantees](docs/guarantees.md). Add another supported
query through the [SQL and fixture workflow](docs/development.md); use the
[troubleshooting guide](docs/troubleshooting.md) for input, resource and recovery
failures. A [complete cursor example](docs/cursor_example.md) uses the installed API.

The [V01 documentation acceptance](docs/verification/v01-documentation-2026-11-14.md)
passes a fresh Release installation, an unseen 18-event SQLite comparison,
checkpoint/restore and all five then-shipped public examples. Scoped guarantee
review and component experiments have separate receiving records. Broader
implementation and release qualification remain open.

For human examination, start with the [code review guide](docs/code_review.md).
It maps algorithms to code, exact paper versions, local proofs and tests, and
distinguishes current behavior from historical evidence.
The [block inspection index](docs/code_specs/README.md) links every maintained
source range to its declaration, local evidence and module context. Start with
the [reviewed primitive contracts](docs/code_specs/primitives.md) for usage,
ownership, failure phases and costs; the index distinguishes these contracts
from generated structural coverage.

The [V61 full-scope review](docs/verification/full-scope-review-v61-2026-11-15.md)
covers its 830 maintained code files with 20,158 usage contracts. Of 373 production
paths, 365 retain the previous reviewed bytes; five changed and three new paths
receive separate source and correctness checks. Independent query ownership,
prepared input dispatch, cache policy and resource boundaries pass Release and
ASan/UBSan checks. The complete [six-study report](build/verification/v61-full-experimental-report-v1/report/report.md)
retains raw records, build/source qualification and portable replay, with
independent checks of every metric. Finite results include slower outcomes;
the ordinary input interpreter remains the default.
The full Refactor and release goal remains active.

The [V62 full-scope review and R1 technical freeze](docs/verification/r1-release-v62-2026-11-15.md)
receives its 832 maintained code files and 20,199 usage contracts. All 376 then-current
tests pass in both strict Release and ASan/UBSan, without failures or skips.
The versioned archive matches every source/checksum and all 258 files of the
independently tested SDK. The [local R1 decision](build/r1-release-v62-v1/candidate-v1/release-decision.json)
accepts the documented equality-set scope. R2 release qualification and separately
gated exact extensions remain separate work; the full implementation goal stays active.

The [V63 durable-row review](docs/verification/sql-rows-recovery-v63-2026-11-16.md)
receives its then-current inventory of 856 code files and 20,671 source-bound usage
contracts. Complete strict Release and ASan/UBSan builds and all 383 current
tests pass in each profile, without failures, skips or code/configuration drift.
Two independently received public SDK images each pass the same seven SQLite
query trials with signed output and recovery. Ordinary
binding preserves the original large-parameter memory bound; recovery metadata
is explicitly requested. Read the [durable-row API](docs/sql_rows_session.md),
[R2 compatibility](docs/r2_compatibility.md) and [migration](docs/r2_migration.md).
V64 separately qualifies the admitted R2 image; its archived documents retain their pre-decision vintage.

V64 adds explicit R2 candidate packaging while retaining the R1 default. All
389 production files and 25 Release SDK native payloads retain their tested V63
bytes. At that source point, inspection maps 856 files / 193,299 lines with 20,681 contracts; the
new [R2 method](docs/releases/r2.md) and extended report retain original measured
vintages. Both targeted release-tool regressions and the exact R2 image/SDK receiving
pass. A [separate internal R2 decision](build/r2-release-v64-v1/candidate-v1/release-decision.json)
accepts the documented scope; [the review](docs/verification/r2-package-v64-2026-11-16.md)
retains the source/test vintages and explicit limits. The broader goal remains active.

The [V65 full-scope review](docs/verification/full-scope-review-v65-2026-11-16.md)
inspects all 472 primary code/configuration paths, including every production file.
It corrects aggregate recovery's work-exhaustion category and stale window-policy
wording. Current usage maps cover 856 files / 193,314 lines with 20,681 contracts.
Per-file review depth, independent SQL/arithmetic/window checks, targeted native
regressions and preserved full-suite vintages are explicit in that record.

V66 adds the opt-in [exact snapshot top-k API](docs/topk.md) for genuine SQL
row/bag and aggregate owners. It uses full snapshot collection and sorting,
compressed multiplicities, explicit NULL placement and query-scoped identity
ties. The [feature review](docs/verification/snapshot-topk-v66-2026-11-16.md)
records independent ranking, resource/ownership and relocated-SDK checks. The
[current full-scope review](docs/verification/full-scope-review-v66-2026-11-16.md)
joins all 391 production files to their source inspections and actual validation.
Current inspection maps cover 861 files / 194,204 lines with 20,798 contracts.

V67 adds [guarded key-aware plans](docs/key_specialization.md): an opt-in cold
FK/UNIQUE rewrite for non-null CQ sets. It retains every original source table
and constraint while removing redundant native join routes. The
[acceptance record](docs/verification/key-specialization-v67-2026-11-16.md)
receives exact original-query/SQLite comparisons, both backends/profiles and a
relocated public SDK. Current maps cover 866 files / 195,388 lines with 20,926
contracts; source/proof scope and actual cold/source-validation costs are explicit.

V69 adds the opt-in [heavy/light star prototype](docs/star.md) for exact
center-plus-unary CQs. Real light-row/heavy-group routes, exact generalized H,
sparse resets and projected cursors pass original-query/SQLite comparisons,
Release and ASan/UBSan, and a relocated public SDK. The
[acceptance record](docs/verification/heavy-light-star-v69-2026-11-16.md) preserves
the audit findings and fixes, source-linked usage contracts and actual cost limits.
All 393 earlier production files remain unchanged; prior full-suite and new
targeted checks retain their separate source vintages.

V70 adds [explicit comparison-aware query owners](docs/comparisons.md): typed
public IR, ordinary propagation, complete hidden-variable filtering before
projection, owning snapshots and atomic exact endpoint set deltas. Both new
registered commands pass Release and ASan/UBSan, alongside original/SQLite models
and a relocated public SDK. The [acceptance](docs/verification/comparison-support-v70-2026-11-16.md)
keeps exact work/materialization costs, source-bound specs and proof limits clear.

V71 adds the explicit [general-query fallback](docs/fallback.md) for cyclic and
acyclic non-free-connex exact-set public IR. Iterative full-source recomputation,
accounted source images and exact endpoint deltas pass both native profiles,
independent Python/SQLite joins and a relocated public SDK. The
[current-inventory review](docs/verification/general-query-fallback-v71-2026-11-16.md)
records all source/review vintages and real costs, without a CROWN/GHD bound.

V72 adds explicit [set and bag difference](docs/difference.md) between two positive
public-IR CQs. One physical owner/image feeds shared iterative recomputation;
compressed counts and exact endpoint replacements distinguish EXCEPT from EXCEPT
ALL. Both native profiles, independent Counter/SQLite oracles and a relocated SDK
pass. The [acceptance](docs/verification/difference-v72-2026-11-16.md) records
source-linked contracts, actual costs and the shared fallback migration.

The opt-in [nullable SQL rows library](docs/sql_rows_runtime.md) supports physical
bag replacements, NULL-sensitive equality joins, DISTINCT and owning results.
Its [verified scope and evidence](docs/verification/w05-sql-rows-human-inspection-2026-11-12.md)
are separate from [grouped COUNT/SUM/AVG](docs/aggregates.md); coordinated
aggregate batches and local recovery now have
[bounded W06 acceptance](docs/verification/human-inspection-v33-2026-11-13.md).
Debug and sanitizer checks cover interrupted mixed self-joins on both backends,
including exact COUNT/SUM/AVG, source weights and sink bytes. The [V44 inspection](docs/verification/human-inspection-v44-2026-11-14.md) adds
23 test instrumentation and fixture usage specs. The current block index has
21,731 contracts across 900 files, covering every nonblank mapped block.
The [V54 full review](docs/verification/full-scope-review-v54-2026-11-15.md)
inspects all 364 production files plus 53 build/tool/example files and records the
correctness/tooling fixes with full Debug and sanitizer verification plus
corrective reruns. X01's [qualified support-action profile](docs/verification/update-pattern-profile-v54-2026-11-15.md)
is verified for the proved source/tree cases and actual captured Session
premises. Its cost model, historical capture, initialization and output/storage
boundaries are explicit. Broader mixed characterization, R2 history retirement
and release gates remain open.

O08 is verified: generic SQL compilation, native stream execution, local
results, checkpoint/restore and relocatable public-library installation pass
all 19 affected CLI/package tests in five configurations. The separate full
264-test acceptance covers the frozen O04–O06 predecessor; full release gates
remain open. See the [O08 evidence](docs/verification/o08-workflow-acceptance-2026-11-10.md),
[CLI/install guide](docs/cli.md), [handoff](docs/handoff.md) and [ledger](docs/task_ledger.md).

The [controlled measurement runner](docs/measurement.md) checks independent
results before repeated native runs, retaining compile/load/maintenance/output/
encoding/sink timings, raw counters and memory/latency distributions. B03
[acceptance passed](docs/verification/b03-measurement-acceptance-2026-11-11.md);
these tools alone make no performance claim.

C07's [held-out ranking evaluation](docs/ranking_evaluation.md) is verified on
disjoint synthetic traces, with actual feasible-candidate regret and proxy errors
reported separately from minimum-height search. Its
[finite observations](docs/verification/c07-heldout-observations-2026-11-11.md)
include unfavorable weighted-depth results under workload shifts; no global
cost-optimality or fixed-speedup claim follows.

S04's explicitly selected [indexed storage backend](docs/indexed_storage.md)
is verified on its frozen source: all 199 tests pass the five native
configurations, with 281 actual C++ commands per build and exact source/evidence controls. The default backend
remains reference storage. The finite comparison shows faster secondary-bucket
walks and slower primary/eight-live walks; see the qualified
[S04 record](docs/verification/indexed-runtime-2026-11-08.md).
S05's [query memory contract](docs/query_memory.md) is verified. Native runtime,
session, input, output, planner-selection and diagnostic state share one finite
query account. All227 tests pass GCC Debug/Release, Clang18, ASan+UBSan/leaks and
a fresh source-only Release build on the same executable code. The
[acceptance record](docs/verification/s05-native-acceptance-2026-11-09.md) maps
checked limits, rollback, churn and operator-memory reconciliation to evidence.
O05/O06 recovery and local delivery are verified in the later integrated cohort;
A02 licensing and release reviews remain open.

The frozen O07 EXPLAIN/metrics/trace checkpoint passed all 99 tests in each of
five build configurations, with its 691-entry source seal independently verified.
That historical checkpoint does not verify later integrations.
See the [observability guide](docs/observability.md) and
[verified record](docs/verification/observability-2026-11-07.md).

C01 adds explicit bounded state capture, optional update statistics, and a
separate versioned report API; see [runtime statistics](docs/statistics.md).
C01 is verified: all 131 tests passed each of the five native configurations;
see its [verified record](docs/verification/statistics-2026-11-07.md). The guide
records scoped actual-engine collection timings separately from that matrix.

C02's library-only [baseline ranking API](docs/ranking.md) is verified. It ranks
typed minimum-height candidates by height, committed-input native depth, or a
source-cardinality tuple/index-slot proxy. All 143 tests pass the five native
configurations with independent matrix and final source audits; see the
[verified record](docs/verification/ranking-2026-11-07.md). It adds no CLI command,
deployment action, calibrated runtime-cost model or allocator-byte claim.

C05's [selection API](docs/selection.md) returns an immutable physical plan from
a typed, certified minimum-height candidate snapshot. It supports C02 baseline
policies, an optional unitless tuple/index-slot constraint, and a bounded FIFO
cache of whole plan artifacts. Every call performs fresh admission and complete
retained-set assessments. Its historical C05 checkpoint passed all 158 tests in five native configurations;
independent matrix and final source audits verify the native registration.
See the [C05 record](docs/verification/selection-2026-11-07.md). Selection does not
install or migrate a plan,
advance a provider, enable C03 calibration, or predict allocator bytes.

C04's optional [meta-decomposition candidate adapter](docs/meta_candidate_adapter.md)
is verified: bounded ordinary enumeration and generalized/head-aware mapping feed
the checked finite-proposal provider under an independent original height proof.
See the [coverage, limits and native evidence](docs/verification/meta-candidates-v56-2026-11-15.md).
It makes no global maintenance-cost optimality claim.

B01's [pinned legacy comparison environments](docs/legacy_baselines.md) are
verified for their named tiny replays. Both original sources build unchanged;
independent output checks retain the published Scala parser-test failure and
explicit query/mode limits. The current [matched experiments](docs/component_evaluation.md)
add finite whole-implementation comparisons with those qualified observers.

P07 alternative-plan enumeration and caching is implemented and verified.
In the historical P07 snapshot, all 92 tests pass the GCC Debug, GCC Release, ASan+UBSan+leak-checking,
Clang Debug and fresh source-only Release matrix on one frozen revision. Its
[verified record](docs/verification/candidate-alternatives-2026-11-07.md)
records the matching frozen fingerprints and independent matrix evidence.
P05 residual candidate construction is implemented and verified. All 89 tests
pass its five-configuration matrix with the documented sanitizer-watchdog bridge;
see the [verification record](docs/verification/residual-candidates-2026-11-07.md).
See [native build instructions](docs/native_build.md), the
[task ledger](docs/task_ledger.md), and the [AntiGravity handoff](docs/handoff.md).
The existing implementation and experiment instructions below remain the
legacy artifact. The new CLI provides exact reference evaluation, certified
structural planning, and SQL syntax/binding/normalization inspection. SQL local
adapters preserve occurrence identity and projection supports; integrated SQL
admission is available through `admit-sql`. Supplied-tree
[physical lowering](docs/physical_plans.md) is available through `lower-plan`
and `lower-normalized`. A [reference support kernel](docs/runtime_support.md)
now maintains logical native/generalized support and exact projections;
the [delta owner](docs/delta_runtime.md) adds bounded atomic
full-query output through the library API. Durable local delivery is now verified under O06.
Normalized artifacts now have strict replay readers, explicit CQ version
upgrades and [canonical query/cache identities](docs/query_identity.md).
The core library also provides [typed tuple/key layouts and reference storage](docs/storage.md)
with live separator indexes, [generational tuple arenas and explicit payload
pins](docs/tuple_arenas.md), and allocation-failure rollback.
Reversible [storage journals](docs/storage_journal.md) and metadata undo provide
atomic logical updates with pinned before/after values and causal event traces.
An owner-only [prepared epoch](docs/prepared_epochs.md) can stage several
same-sign logical updates behind one commit boundary. The library's
[physical coordinator](docs/physical_runtime.md) now maintains full source rows,
per-occurrence derivation counts and atomic alias fan-out. Lazy
[current-result cursors](docs/result_cursors.md) traverse live indexes and pin
one committed epoch. [Epoch views and fragment cursors](docs/epoch_views.md)
add journal-backed before/after context, typed visible/hidden bindings,
projected completions and full survivor-factor assignments. The
[projected delta specification](docs/delta_transition_spec.md) defines E-key
ownership, per-alias contexts and live-state publication. Its D04 implementation
uses stage-local journal views, live E-key witnesses and lazy completions.
D05 adds verified [ordered E replay](docs/ordered_delta.md), row-coupled live
maintenance, parent/child live indexes and a runtime guarantee profile.
After route preparation, internal first/next/last production uses bounded
fixed-query indexed actions. Public atomic startup includes the whole epoch;
ordered dictionary, cleanup and full-scan costs remain explicit.
Verified [pending-epoch lifecycle](docs/delta_lifecycle.md) adds resumable
private replay, required internal draining and recoverable committed callback
delivery. The O02 library [Session API](docs/session_lifecycle.md) is
implemented and verified; O05/O06 now verify native recovery and operational
local sinks separately.

Verified O01 adds strict physical-row input and ordered
library replay; see the [input guide](docs/ingestion.md) and the
[native build and CLI guide](docs/native_build.md). Events retain the complete
declared source row, including columns unused by the query. `EventReader`
supports JSONL, binary, CSV, and explicitly selected legacy profiles;
`OrderedReplay` advances accepted input progress only after the runtime commits
the event. For example:

```sh
build/debug/crown validate-input CATALOG.json jsonl EVENTS.jsonl
build/debug/crown validate-input CATALOG.json csv TABLE.csv PHYSICAL_TABLE
```

`validate-input` is a diagnostic, full-stream validator. All 69 tests pass the
[compiler/sanitizer/clean matrix](docs/verification/physical-input-2026-11-06.md).
That matrix is the verified historical O01 snapshot and does not verify O02.
O02 adds a library-only `QuerySession` API for one-event-at-a-time begin, step,
commit, drain and committed output/snapshots. Its verified historical snapshot
passed all 71 tests in the
[five-configuration matrix](docs/verification/session-lifecycle-2026-11-06.md).
The optional [independent query directory](docs/independent_queries.md) owns
separate serial sessions through `CROWN::queries`; each keeps its own input,
progress, results, memory account and recovery boundary.
An opt-in [prepared SQL input program](docs/input_specialization.md) prebinds
expression dispatch while preserving the physical plan and ordinary execution
pipeline. The interpreter remains the default.
O02 adds no CLI command. O03 typed queues and operational windows are now
acceptance-verified: all 79 tests pass in GCC Debug/Release, ASan/UBSan,
Clang Debug and a fresh source-only Release build. The 435-input native
fingerprint is
`e035d699fe49312aea9307c43e597eb70af6989db295b84205baf85c806a64b0`.
The typed queue and window APIs are library-only. See the
[O03 verification packet](docs/verification/batches-windows-2026-11-06.md) and
[batch and window guide](docs/batches_windows.md). That 79-test matrix and
fingerprint describe the O03 snapshot and are historical after the later P04
planner edits. O04 [versioned session checkpoints and durable file restore](docs/checkpoints.md)
are acceptance-verified on the frozen O04 snapshot: all 240 then-registered tests
passed GCC Debug/Release, Clang18, ASan+UBSan/leaks and a clean source-only Release build. See the
[O04 acceptance record](docs/verification/o04-native-acceptance-2026-11-10.md). O05 WAL and O06 local durable delivery are now verified; the
O08 session/streaming CLI is also verified on its selected workflow matrix. O05 includes a maintained
[journal record codec and prefix validator](docs/journal.md) and
[durable single-writer journal files](docs/journal-files.md), connected to
[prepared session input/commit publication](docs/session-journal.md) and
[native reconstruction/replay](docs/native-replay.md). Recovery preserves pending
input/window/source continuation and bounded committed output with semantic
identity. [Durable generation selection/rotation](docs/generations.md) now
publishes complete pairs before switching a locked root and preserves historical
pairs. [Durable local epoch delivery](docs/local-sink.md) now provides canonical
idempotent output, bounded backpressure and local prefix receipts. Sink-aware native factories now validate actual accepted epochs without
retaining acknowledged replay output; only missing output uses the backlog grant.
See the [scoped restart evidence](docs/verification/o06-sink-restore-native-2026-11-10.md). [Crash-safe history retirement](docs/history-retirement.md) now records durable
cleanup intent and binds checkpoint delivery before deleting older pairs.
Integrated O04–O06 acceptance passes all264 tests in GCC Debug/Release, Clang18,
ASan+UBSan/leaks and a fresh source-only Release build. All262 previous test
definitions are preserved; both native backends compose private fanout, writer/
sink errors, queued backpressure, replay, next updates and verified retirement.
See the [integrated record](docs/verification/o05-o06-native-acceptance-2026-11-10.md).
These are native library/local-file guarantees; arbitrary external callback
side effects require their own protocol. R06 adds library APIs for
initializing physical and delta owners from a validated database snapshot,
including a `QuerySession` factory overload, quiescent rebuild into a new
owner, and canonical/invariant diagnostics; see the
[runtime initialization contract](docs/runtime_initialization.md). R06 was
acceptance-verified in its historical snapshot: all 75 tests passed in the
five-configuration matrix. That R06 matrix and source seal predate O03 and are
historical after these O03 edits. The earlier 71-test O02 result above
is also historical; see the
[R06 verification packet](docs/verification/runtime-initialization-2026-11-06.md)
for its matrix configurations and timings. The O03/R1 transport API has no
atomic net-batch mode; it preserves one physical epoch per event. The separate
[SQL-row NetBatch](docs/sql_rows_batches.md) and aggregate coordinator provide
explicit atomic R2 replacements under their own contracts.

P04's optimized exact planner is acceptance-verified: all 82 tests pass GCC
Debug/Release, ASan/UBSan, Clang Debug and a fresh source-only Release build.
Independent source/proof, differential and failure reviews pass. See the
[P04 verification record](docs/verification/planner-fast-paths-2026-11-06.md)
and [planner preservation proofs](docs/planner_proofs.md). This is the historical
P04 snapshot before the P06 continuation edits.

# Project Structure
- `include`, `src` and `apps/crown` contain the native public API, implementation and CLI.
- `docs`, `tests` and `examples` contain the native contracts, independent checks and public API examples.
- `crown` source code for implementation of CROWN, check `crown/README.md` for more.
- `experiments` scripts and source code for data experiments, check `experiments/README.md` for more.
- `dbtoaster_modified` modified dbtoaster-backend source code
- `dbtoaster_frontend_modified` modified dbtoaster-a5 source code

# How to implement a customized query
For CROWN Next, follow the [query contribution guide](docs/development.md):
supported queries need SQL, catalog/update fixtures and independent expected
results, with no query-specific C++ class. The customization section in the
[legacy CROWN guide](crown/README.md) describes the original Scala/Flink code used
for paper reproduction.

# Reproduction
Please check the [instructions](experiments/README.md).

P06 is acceptance-verified: all 86 tests pass the five-configuration matrix.
The library now owns actual resumable search, independent validation and proof
replay, with distinct validated-incumbent/verified-optimum types and explicit
resource grants. See the [continuation contract](docs/planner_continuations.md)
and [P06 verification record](docs/verification/planner-continuations-2026-11-06.md).
Implementation remains active under the user's current scope. The stable
78-card ledger retains deferred research: approximation and parallel/distributed
execution wait; multi-query maintenance keeps independent query state. Comparisons,
top-k and difference may use ordinary change propagation or exact recomputation.

## Native EXPLAIN

The native CLI can report validated physical plans, runtime and session state,
and exact-search or certificate-replay progress with `crown explain`. These are
read-only diagnostic reports: capture does not advance a runtime or search,
and it does not add cost-ranking authority. See the
[observability guide](docs/observability.md) for modes, report scope, and
examples.

Runtime/session commands also accept `--format memory-json` for actual operator
record counts joined to query allocation totals, table/index storage and tuple
arena lifetimes. See the [memory report contract](docs/memory_reports.md) for
scope, limits and the explicit JSON export boundary. The query account and explicit export boundaries follow the [S05 contract](docs/query_memory.md).

Native invariant diagnostics also fund their issue keys and expected-state
collections from the original query account, preserving version1 diagnostic
bytes. See [invariant memory ownership](docs/invariant_memory.md).
