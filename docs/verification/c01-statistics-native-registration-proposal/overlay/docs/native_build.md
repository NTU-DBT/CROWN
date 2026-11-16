# Native executable specification

The frozen O07 native observability checkpoint passed all 99 tests across GCC
Debug/Release, ASan+UBSan, Clang Debug and a fresh source-only Release build.
Its 691-entry source seal is verified historical evidence; it does not establish
acceptance of the later C01 integration candidate or its 131-test registration.
See [observability.md](observability.md) and the
[verified record](verification/observability-2026-11-07.md).

P07 candidate enumeration/cache/report integration is implemented and
verified in its historical snapshot. All 92 tests passed GCC Debug, GCC Release, ASan+UBSan+leak checking,
Clang Debug and fresh source-only Release on one frozen revision. See the
[verified record](verification/candidate-alternatives-2026-11-07.md).

P05 residual candidate construction is implemented and verified. All 89 tests
pass GCC Debug/Release, Clang, ASan+UBSan and fresh source-only Release, with
the qualified sanitizer-watchdog bridge. See the
[verification record](verification/residual-candidates-2026-11-07.md).

The native C++23 build develops CROWN Next independently of the existing
Scala/Flink artifact. It includes a certified exact structural planner; this
does not mean that every planned runtime, recovery or delivery feature is
complete. Read [semantics.md](semantics.md), [sql_support.md](sql_support.md)
and [task_ledger.md](task_ledger.md) for the broader scope and evidence.

Core requirements: Linux, GCC 13 (C and C++), CMake 3.25+, GNU Make and Python 3.10+ with
its standard-library `sqlite3` module and installed `jsonschema` with Draft2020-12
and local RefResolver support (4.10.3 verified).
The vendored JSON header and libpg_query source archive are checksum-checked
during configuration. The parser is built from the archive inside each binary
directory, with no dependency on the earlier spike. Its upstream component
notices are preserved in `third_party/libpg_query/`. Configuration/build/test
does not require network access or parser-source regeneration tools.

```sh
cmake --preset debug
cmake --build --preset debug --parallel 2
ctest --preset debug
python3 tools/verify_clean_build.py --log build/verification/clean-source.log
build/debug/crown --version
build/debug/crown oracle tests/regression/projection_collision.json
```

`release` and `sanitize` are corresponding configure/build/test presets. The
sanitizer preset enables ASan and UBSan for both project C++ and upstream
parser C sources. Actual outcomes and remaining
scope limits are recorded in the task ledger, not inferred
from the existence of a preset.

C01 statistics registration adds five units to both matching runtime libraries
and two units to both matching report libraries. Storage remains in `crown_core`;
`crown_runtime` has no dependency on observability or report IO. The testing
runtime's `CROWN_RUNTIME_TESTING` definition propagates only through its matching
test/report targets. Runtime-only Session consumers link each variant without
any report library. See [statistics.md](statistics.md) for the API and limits.

The draft C01 registration retains all 99 prior tests and adds 32 CTests labeled
`C01`. Run `ctest --test-dir build/debug -L C01 --output-on-failure` for that
selection; the complete native matrix remains the acceptance gate. Added tests
cover state and owner captures, collector and online hooks, joint captures,
allocation failures, typed scalars/constraints, two report/schema variants, and
seven selected policy/replay/window cases for each propagation order. Existing
policy targets keep collection opt-in macros absent. The enabled copies define
`CROWN_STATISTICS_ACCEPTANCE`; only their LIFO copies additionally define
`CROWN_STATISTICS_LIFO`. These selections are not an exhaustive policy product.

`tools/verify_statistics_reports.py` runs the actual matching report producer in
a temporary directory, then the independent copied checker using installed
`jsonschema`. It retains the corpus on failure. Checked-in C01-off v2 baselines
under `tests/statistics/legacy-v2` are verified by checksum and compared byte for
byte in both variants; no historical temporary archive or binary is needed.
The new closed v3 schema does not alter any earlier schema. Native compiler,
sanitizer, clean-source and legacy acceptance remain pending; isolated proposal
passes do not replace them. The statistics guide records the accepted scoped
actual-engine benchmark separately from those native matrix gates.

The CLI commands are:

```sh
crown parse-sql INPUT.sql
crown bind-sql INPUT.sql CATALOG.json [PARAMETER_TYPES.json]
crown normalize-sql INPUT.sql CATALOG.json [PARAMETER_TYPES.json [PARAMETER_VALUES.json]]
crown admit-sql INPUT.sql CATALOG.json [OPTIONS.json]
crown admit-normalized PROGRAM.json [WORK_LIMIT]
crown validate-normalized PROGRAM.json
crown canonicalize-normalized PROGRAM.json
crown upgrade-cq DOCUMENT.json TARGET_VERSION
crown upgrade-normalized PROGRAM.json TARGET_VERSION
crown fingerprint-cq DOCUMENT.json [WORK_LIMIT]
crown fingerprint-normalized PROGRAM.json [WORK_LIMIT]
crown lower-plan QUERY.json TREE.json [OPTIONS.json]
crown lower-normalized PROGRAM.json TREE.json [OPTIONS.json]
crown validate-physical PLAN.json
crown canonicalize-physical PLAN.json
crown validate-input CATALOG.json FORMAT INPUT [TABLE]
crown support-trace PLAN.json LOGICAL_TRACE.json
crown validate-catalog CATALOG.json
crown canonicalize-catalog CATALOG.json
crown validate-cq DOCUMENT.json
crown canonicalize DOCUMENT.json
crown oracle DOCUMENT.json
crown classify DOCUMENT.json
crown validate-plan QUERY.cq.json PLAN.tree.json
crown tree-oracle QUERY.cq.json [WORK_LIMIT]
crown verify-height QUERY.cq.json CERT.json [WORK_LIMIT]
```

`parse-sql` preserves an owned source/AST and locations; syntax success always
leaves semantic admission unchecked. See [sql_parser.md](sql_parser.md).
`bind-sql` resolves the supported SELECT subset to an owned typed IR,
including join scopes, ordered outputs and typed parameters. It leaves native
admission unchecked and does not execute SQL. See [sql_binding.md](sql_binding.md).
`normalize-sql` constructs an equality CQ, executable local adapters and an
ordered SQL output mapping. It rejects row-producing bags, nullable source
columns and cross-occurrence theta predicates. Typed parameter values specialize
the program. Its result still leaves structural admission unchecked; see
[sql_normalization.md](sql_normalization.md). The `AdapterState` library tracks
physical projection supports and commits alias fan-out together, independently
of the maintained join runtime. `PhysicalRuntime` now connects compiled input
adapters to maintained support with source/count/kernel undo; see
[physical runtime](physical_runtime.md).
`admit-sql` connects grounded normalization to bounded body/H+F GYO checks.
It reports seven precise admission categories and preserves complete witnesses
or explicit resource stops. `admit-normalized` first validates a program and
grounds legacy format 1 to format 2. These commands check frontend/structure;
their `execution_status` remains `not_lowered`. See [sql_admission.md](sql_admission.md).
`validate-normalized` and `canonicalize-normalized` replay the complete
source/catalog binding and normalization before accepting any executable
program. `upgrade-cq` explicitly migrates upward among formats 1/2/3;
`upgrade-normalized` supports normalized 1→2 with preserved legacy replay.
The fingerprint commands produce canonical SHA-256 semantic/output/cost/cache
identities, with complete occurrence/variable ID translation maps and honest
resource-stop results. See [schema_evolution.md](schema_evolution.md) and
[query_identity.md](query_identity.md). They leave admission unchecked.
`validate-cq` checks well-formedness/typing and reports that structural admission
has not been checked. `canonicalize` writes deterministic JSON while retaining
the input document format version (1, 2 or 3).
`validate-catalog` checks standalone metadata, without asserting that external
data satisfies its declarations. `canonicalize-catalog` preserves the complete
typed metadata and writes explicit defaults. See [catalog.md](catalog.md).
`oracle` returns epoch-zero answers, then each committed event's full answer,
actual membership additions/removals, and whether the physical table changed.
Its explicit backend is `reference_recompute`. Output is exact sorted JSON;
there is no tolerance-based comparison.

`classify` runs GYO separately on the body and body plus head. It reports
`free_connex`, `acyclic_non_free_connex`, or `cyclic`, with reduction witnesses
and any failed cores. Edge numbers are occurrence positions; the synthetic
head has index `atoms.size()`. This checks no plan or minimum height: its
`height_status` remains `not_checked`. See [planner_proofs.md](planner_proofs.md).

`validate-plan` checks a version-1 structural tree against the supplied CQ,
including optional separator/connex/height claims. Valid trees report their
checked native height as an upper bound. Structurally invalid trees return
exit 1 with concrete violations on stdout; malformed input returns exit 2
with a JSON diagnostic on stderr. See [tree_plans.md](tree_plans.md) for the
plan schema and examples.

`tree-oracle` computes an exact structural minimum and independently replays
its lower-bound certificate before reporting `proven_minimum`. `verify-height`
replays a saved certificate. Resource stops are explicitly incomplete and do
not establish infeasibility. See [tree_oracle.md](tree_oracle.md) for commands,
limits, certificate extraction and the `unsupported`/`resource_limit` statuses.

The optimized planner uses the v2 exact-search algorithm. It handles empty
bodies and single occurrences directly, constructs height-one trees for
q-hierarchical queries, splits disconnected occurrence graphs at the full
query root, and reduces equivalent branches for equal complete native scopes.
Its branch-and-bound cuts only alternatives whose proved lower bounds cannot
improve the checked incumbent. Every completed claim still has an independently
replayed certificate. The verifier retains exact v1 replay and requires a
matching certificate schema and algorithm version. Details and preservation
arguments are in [tree_oracle.md](tree_oracle.md) and
[planner_proofs.md](planner_proofs.md).

P04 is a historical acceptance-verified checkpoint. All 82 tests passed GCC Debug/Release, ASan/UBSan,
Clang Debug and a fresh source-only Release build, with identical before/after
native inputs. Independent source/proof, differential and failure reviews pass.
The previous O03 79-test matrix and source fingerprint are historical. See the
[P04 verification record](verification/planner-fast-paths-2026-11-06.md).
P06 supplies verified owned strict/best-found search and independent replay;
see the [continuation contract](planner_continuations.md).
P05 adds a verified separate residual candidate owner; its
[contract](residual_candidates.md) distinguishes frozen-trace audit, checked
upper trees, exact prefix repair and full-original-query proof authority.
`lower-plan` and `lower-normalized` compile supplied trees into immutable
physical descriptors after independent verification. The `crown_plan` library
also instantiates empty reference storage and runs numeric input/assembly
programs. `validate-physical` rebuilds the complete source/tree/program;
`canonicalize-physical` writes the verified artifact. These operations report
`valid_upper_bound` height and `lowered_not_started` execution. See
[physical_plans.md](physical_plans.md) for options, source bindings and scope.
The `crown_runtime` library now maintains native/generalized support and exact
P/E counts for logical scoped updates. `support-trace` exposes diagnostic
snapshots, affected-record journals and causal event/accounting diagnostics; see
[runtime_support.md](runtime_support.md). The owner-only
[prepared epoch API](prepared_epochs.md) stages several same-sign logical rows
under one undo scope and publication boundary. The embeddable
`PhysicalRuntime` coordinates physical rows and every affected alias atomically;
its prepared token supplies the output-staging boundary. The
[delta owner](delta_runtime.md) prepares bounded atomic core/SQL deltas over
this token. Verified [ordered E replay](ordered_delta.md) adds productive
witness queues and exact parent/child live indexes. Its runtime profile gives
bounded fixed-query indexed actions per internal first/next/last result after
route preparation, with explicit maintenance/finalization costs. Public atomic
startup includes preparing the whole epoch. Canonical
[anchored](anchored_delta.md) and root-first strategies remain comparison paths;
higher-level session control is described in the O02 section below; sinks and
recovery remain later work. R06 now adds library-only snapshot initialization,
quiescent rebuild and invariant inspection; see the
[runtime initialization contract](runtime_initialization.md). No CLI command
was added for these APIs.
Verified [pending delta lifecycle](delta_lifecycle.md) adds one-core-row
stepping, pause/resume, drain/discard/abort and prepared-only commit, with
recoverable codec/sink callbacks and separate phase timings. The historical
D06 snapshot, before O01, recorded 66 passing tests in the
[compiler/sanitizer/clean matrix](verification/delta-lifecycle-2026-11-06.md);
that result does not verify O01. Its [current-result cursor](result_cursors.md)
walks live E indexes with an epoch read lease and owned output tuples; core and
SQL views preserve their declared output order. O01 exposes diagnostic input
validation through the CLI; it does not expose the separate O02 session API or
provide streaming execution.

## O01 physical input and ordered replay

Verified O01 is described in the [input guide](ingestion.md); independent
source review and all 69 tests pass the
[compiler/sanitizer/clean matrix](verification/physical-input-2026-11-06.md).
A physical event names an exact catalog table and
contains its complete declared source row in source-column order, including
columns unused by the query. Input does not substitute logical aliases or
projected witnesses. The version-1 JSONL and binary codecs strictly validate
catalog/source-schema bindings, types, row width, event sequence, and optional
per-source positions. See [physical-update-v1.schema.json](../schemas/physical-update-v1.schema.json)
for JSON shape and [scalars.md](scalars.md) for scalar encodings. CSV and
legacy inputs are available through explicit reader profiles; legacy signs,
table mappings, and timestamp semantics are never inferred.

At the library boundary, `EventReader::peek()` validates and holds one event;
only `acknowledge()` advances its accepted progress. `OrderedReplay` calls the
physical or delta runtime first and acknowledges only after the atomic engine
commit. If the engine rejects an event, that event remains available for retry
and sequence/source progress stays unchanged. Output delivery happens after
input commitment and has its own retry rules. This O01 path is ordered
per-event replay, not file-wide atomicity or batch replay; it has no session
controls, durable checkpoints/recovery, or operational sinks. The separate
O02 library API is described below.

The `validate-input` CLI command reads a catalog and validates a complete input
stream without changing an engine. It prints its summary only after valid EOF.
The CLI supports strict JSONL and binary streams, CSV for one physical table,
and the explicitly chosen `legacy-signed`, `legacy-insert-only`, or
`legacy-flags` profile:

```sh
build/debug/crown validate-input CATALOG.json jsonl EVENTS.jsonl
build/debug/crown validate-input CATALOG.json binary EVENTS.bin
build/debug/crown validate-input CATALOG.json csv TABLE.csv PHYSICAL_TABLE
build/debug/crown validate-input CATALOG.json legacy-signed EVENTS.csv PHYSICAL_TABLE
build/debug/crown validate-input CATALOG.json legacy-insert-only EVENTS.csv PHYSICAL_TABLE
build/debug/crown validate-input CATALOG.json legacy-flags EVENTS.csv PHYSICAL_TABLE
```

The CLI uses default CSV comma/header settings. The library also supports
relation-token and timestamp legacy profiles, custom reader limits, and
caller-supplied initial progress. This O01 diagnostic CLI does not expose the
O02 session API or provide streaming execution.

## O02 library Session API

The library provides synchronous `QuerySession` control for one physical input
event at a time. O02 was independently reviewed and verified: its historical
snapshot passed all 71 tests in the
[five-configuration matrix](verification/session-lifecycle-2026-11-06.md).
The O01 69-test matrix above remains historical. The O02 71-test matrix is
also historical. The R06 75-test matrix below predates O03. O03 is now
acceptance-verified and has no CLI command. See the
[session lifecycle guide](session_lifecycle.md) for state/phase rules and
failure details, the [batch and window guide](batches_windows.md) for O03, and
the [O03 verification packet](verification/batches-windows-2026-11-06.md).

Create the session with a verified `PhysicalPlan` and an owned input stream.
The existing factory starts with an empty database at accepted sequence zero;
R06 also adds a factory overload that accepts an initial `Database`. Both own
the stream, reader and runtime. Public operations belong to the thread that
created the session. A session is noncopyable and nonmovable; keep the returned
`unique_ptr` as its owner. The initialized factory preserves zero accepted
input progress and has no source positions for the supplied snapshot. Details
are in [session_lifecycle.md](session_lifecycle.md).

`begin_next()` begins a genuine private D06 epoch for one validated event; it
does not eagerly apply the event. Each `step()` advances one D06 work step.
When it returns `DeltaStep::prepared`, `commit()` publishes the whole event and
its retained output. `pause()` on pending work pauses that same D06 cursor, and
`start()` resumes it. A minimal retaining loop is:

```cpp
#include "crown/runtime/session.hpp"

auto session = crown::runtime::QuerySession::create(
    std::move(verified_plan), std::move(input));
session->start();
while (session->begin_next()) {
  while (session->step() != crown::runtime::DeltaStep::prepared) {}
  session->commit();
  while (auto row = session->next_output()) {
    // The caller owns this committed row and its delivery policy.
  }
}
auto result = session->snapshot();
session->stop();
```

To finish the current event without retaining its output, call
`start_drain()` and `drain()`. Draining never reads the next event; call
`begin_next()` explicitly for that. `snapshot()` returns an owning
`SessionSnapshot` of one committed result, including its sequence, input
progress, layout and rows. Its default retained-storage limits are 65,536 rows
and 64 MiB, configurable in `SessionOptions.snapshot` or for one call. This is
not a peak-memory cap. Snapshotting does not commit or drain private work.

`stop()` is terminal: it aborts private work, discards unread committed output,
and releases the reader and owned stream while retaining committed runtime
state for snapshots. `drop()` also releases runtime/plan state and accepted
progress. Returned output rows and snapshots own their data and remain valid
after later input or stop/drop. These operations do not add durable recovery.

O04 checkpoint/restore, O05 WAL, O06 durable sinks/backpressure and the O08
session/streaming CLI remain separate future work. A `SessionSnapshot` is a
result snapshot, not a checkpoint.

## R06 runtime initialization and inspection

`PhysicalRuntime::initialize` and `DeltaRuntime::initialize` build a new owner
from a complete source `Database`; their existing constructors still create
empty owners. `rebuilt()` creates a separate owner from a quiescent current
state and preserves the committed sequence, mode and options. Snapshot
initialization validates the complete catalog-bound database, including
constraints in unused tables and valid cyclic foreign keys. Initialization
returns a ready owner at sequence zero without a public event or output; the
first later external event is sequence one. `QuerySession` has a corresponding
initial-database factory overload that leaves accepted input progress empty.

`BuildOptions` selects direct construction or insertion replay and supplies a
cumulative work cap separate from per-update limits. Canonical state, localized
invariant reports and deterministic JSON diagnostics are available through the
runtime library; reports must be complete before callers trust them. The JSON
diagnostics are not checkpoints or restore files, and these work limits do not
provide complete memory-byte accounting, which remains S05 work (see
[tuple and arena scope](tuple_arenas.md)). See the full
[runtime initialization contract](runtime_initialization.md).

R06 acceptance was verified: all 75 tests passed in its five-configuration
matrix. That matrix and source seal predate O03 and remain historical after
the O03 edits. The R06 packet records these per-configuration results:

| Configuration | Result | CTest time |
| --- | --- | ---: |
| GCC 13.3 Debug | 75/75 pass | 195.85 s |
| GCC 13.3 Release | 75/75 pass | 22.22 s |
| ASan/UBSan, including parser C | 75/75 pass | 837.99 s |
| Clang 18.1.3 C/C++ Debug | 75/75 pass | 145.77 s |
| Fresh source-only Release | 75/75 pass | 21.39 s |

See the [R06 verification packet](verification/runtime-initialization-2026-11-06.md)
for detailed acceptance evidence. The O01 and O02 matrices above remain
historical snapshots. No CLI command was added for R06.

## O03 ordered batches and operational windows

O03 is acceptance-verified. All 79 tests passed in the five-configuration
matrix. The 435-input native fingerprint is
`e035d699fe49312aea9307c43e597eb70af6989db295b84205baf85c806a64b0`.
The O02 and R06 matrices above remain historical. See the
[O03 verification packet](verification/batches-windows-2026-11-06.md) for
the acceptance record and the [batch and window guide](batches_windows.md)
for the library API contract.

| Configuration | Result | CTest time |
| --- | --- | ---: |
| GCC 13.3 Debug | 79/79 pass | 191.67 s |
| GCC 13.3 Release | 79/79 pass | 22.73 s |
| ASan/UBSan, including parser C | 79/79 pass | 842.91 s |
| Clang 18.1.3 C/C++ Debug | 79/79 pass | 147.02 s |
| Fresh source-only Release | 79/79 pass | 21.56 s |

Overall clean verification took 395.09 s; the temporary source-only tree was
removed after the run.

`QuerySession::create_typed` accepts move-only `TransportBatch` instances of
ordinary full-row events. Admission is bounded by batch, event and accounted
byte limits. A full response leaves the offered batch with its caller; an
accepted batch preserves every event boundary. Each physical event still
uses the O02 D06 begin/step/commit lifecycle and produces its own committed
delta. Optional R2 atomic net batches are explicitly disabled.

An open empty typed queue is not EOF. `begin_next_result()` returns
`would_block` while it remains open, `end` after it is finished and drained,
and `pending` when a command is available. The Boolean `begin_next()` throws
`input_would_block` for the open-empty case and returns false at EOF.
`finish_input()` closes admission while allowing the accepted prefix to drain.

`QuerySession::create_windowed` enables operational label/FIFO window commands
through the same typed transport boundary. Window timestamps use an adapter
`uint64` domain, and watermark expansion may include multiple physical steps;
see the guide for source progress, retry, pause and failure semantics. These
window behaviors passed the independent reference, persistent-failure and
sequence-boundary suites. No CLI command was added for typed queues or windows.

The `crown_core` library includes immutable typed tuple/key layouts, compiled
numeric projections, generational tuple arenas with explicit retention pins,
and the standard-container `ReferenceTable` backend.
Its [storage journal](storage_journal.md) supports exact reversible insert/erase
scopes and retained values. The logical support kernel now combines these
scopes with metadata undo. Trace input remains version 1; diagnostic output is
version 2. The delta owner supplies integrated full-query output acceptance;
durable delivery remains O work.
Shared target layouts let projections from different input layouts address
the same separator keys. Storage tests cover independent randomized index
operations, live cursor invalidation and allocation-failure rollback. See
[storage.md](storage.md) for ownership, API examples and strict layout/projection
schemas. These library APIs supply physical lowering, maintained support and
committed current-result enumeration.

Input follows [cq-v1.schema.json](../schemas/cq-v1.schema.json),
[cq-v2.schema.json](../schemas/cq-v2.schema.json), or
[cq-v3.schema.json](../schemas/cq-v3.schema.json), with additional
cross-reference and type checks in the native reader. Unknown fields and
duplicate JSON object keys fail. Integer cells are signed 64-bit JSON integer
tokens, strings are exact UTF-8 JSON strings, and bool cells are JSON booleans.
Format 2 adds tagged exact decimal and date cells; see [scalars.md](scalars.md).
Format 3 adds catalog metadata and exact fixed-decimal checks. Enforced unique
and foreign-key constraints are checked against initial data and every
reference after-state before commit. Untrusted declarations, statistics and
hints do not change query semantics.
Nullary true and false results encode as `[[]]` and `[]` respectively.

The handoff file [handoff.md](handoff.md) gives the current checkpoint, exact
verification commands, environment issue and next implementation dependencies.

P06 is acceptance-verified. All 86 tests pass GCC Debug/Release, ASan/UBSan,
Clang Debug and a fresh source-only Release build, with identical native inputs.
New public library APIs own exact producer, P02 validation and independent v1/v2
certificate replay positions, resource grants and immutable upper/optimum types.
The default fine-grained work allowance is ten million per phase. Strict CLI
behavior remains; earlier P04/O03 matrices are historical. See the
[contract](planner_continuations.md) and
[P06 verification record](verification/planner-continuations-2026-11-06.md).

## Native EXPLAIN

Build the native `crown` target, then use the EXPLAIN dispatcher:

```sh
cmake --build --preset debug --target crown --parallel 2
build/debug/crown explain --help
```

The command forms are:

```text
crown explain {physical|runtime|session} PLAN.json [OPTIONS]
crown explain {query|progress} DOCUMENT.json [--work N] [--height-policy strict|best-found]
crown explain replay DOCUMENT.json --certificate FILE [--work N]
```

Reports support `--format text|json|dot|tree-json` and `--max-bytes N`. Runtime
and session reports accept `--observe off|counters|timed|trace`; the default is
`timed`. A work quantum passed to `progress`, `query`, or `replay` is an
explicit producer operation. Capturing or encoding the resulting report does
not advance that producer. See [observability.md](observability.md) for output
and accounting details.
