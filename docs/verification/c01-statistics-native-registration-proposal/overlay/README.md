# CROWN
This project provides the source code of our paper: [Change Propagation Without Joins](https://www.vldb.org/pvldb/vol16/p1046-hu.pdf). It also contains the scripts for reproducing the experiment results in the paper.

The CROWN Next refactor has a separate C++23 library and CLI.

The frozen O07 EXPLAIN/metrics/trace checkpoint passed all 99 tests in each of
five build configurations, with its 691-entry source seal independently verified.
That historical checkpoint does not verify the later C01 integration candidate.
See the [observability guide](docs/observability.md) and
[verified record](docs/verification/observability-2026-11-07.md).

C01 adds explicit bounded state capture, optional update statistics, and a
separate versioned report API; see [runtime statistics](docs/statistics.md).
The native C01 matrix remains pending. The guide records scoped actual-engine
collection timings; accepted isolated checks do not establish native verification
or cost ranking.

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
full-query output through the library API. Durable delivery remains in progress.
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
implemented and verified; operational sinks and recovery remain later
work.

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
O02 adds no CLI command. O03 typed queues and operational windows are now
acceptance-verified: all 79 tests pass in GCC Debug/Release, ASan/UBSan,
Clang Debug and a fresh source-only Release build. The 435-input native
fingerprint is
`e035d699fe49312aea9307c43e597eb70af6989db295b84205baf85c806a64b0`.
The typed queue and window APIs are library-only. See the
[O03 verification packet](docs/verification/batches-windows-2026-11-06.md) and
[batch and window guide](docs/batches_windows.md). That 79-test matrix and
fingerprint describe the O03 snapshot and are historical after the later P04
planner edits. O04 checkpoint/restore,
O05 WAL, O06 durable delivery, and the O08 session/streaming CLI remain
separate work. R06 adds library APIs for
initializing physical and delta owners from a validated database snapshot,
including a `QuerySession` factory overload, quiescent rebuild into a new
owner, and canonical/invariant diagnostics; see the
[runtime initialization contract](docs/runtime_initialization.md). R06 was
acceptance-verified in its historical snapshot: all 75 tests passed in the
five-configuration matrix. That R06 matrix and source seal predate O03 and are
historical after these O03 edits. The earlier 71-test O02 result above
is also historical; see the
[R06 verification packet](docs/verification/runtime-initialization-2026-11-06.md)
for its matrix configurations and timings. The optional R2 atomic net-batch
mode remains explicitly disabled; ordinary transport batches preserve one
physical epoch per event.

P04's optimized exact planner is acceptance-verified: all 82 tests pass GCC
Debug/Release, ASan/UBSan, Clang Debug and a fresh source-only Release build.
Independent source/proof, differential and failure reviews pass. See the
[P04 verification record](docs/verification/planner-fast-paths-2026-11-06.md)
and [planner preservation proofs](docs/planner_proofs.md). This is the historical
P04 snapshot before the P06 continuation edits.

# Project Structure
- `crown` source code for implementation of CROWN, check `crown/README.md` for more.
- `experiments` scripts and source code for data experiments, check `experiments/README.md` for more.
- `dbtoaster_modified` modified dbtoaster-backend source code
- `dbtoaster_frontend_modified` modified dbtoaster-a5 source code

# How to implement a customized query
Please check the `How to implement a customized query` section in `crown/README.md`

# Reproduction
Please check the [instructions](experiments/README.md).

P06 is acceptance-verified: all 86 tests pass the five-configuration matrix.
The library now owns actual resumable search, independent validation and proof
replay, with distinct validated-incumbent/verified-optimum types and explicit
resource grants. See the [continuation contract](docs/planner_continuations.md)
and [P06 verification record](docs/verification/planner-continuations-2026-11-06.md).
The full 78-card implementation goal remains active.

## Native EXPLAIN

The native CLI can report validated physical plans, runtime and session state,
and exact-search or certificate-replay progress with `crown explain`. These are
read-only diagnostic reports: capture does not advance a runtime or search,
and it does not add cost-ranking authority. See the
[observability guide](docs/observability.md) for modes, report scope, and
examples.
