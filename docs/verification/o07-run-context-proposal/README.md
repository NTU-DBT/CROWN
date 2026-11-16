# O07 run-context proposal — design and compiler evidence only

O07 remains **not_started (NS)**. This is an excluded, unapplied layer above
`o07-mode-binding-proposal` and `o07-runtime-proposal`. It preserves those ready
packages, the separate EXPLAIN package, native inputs, tests, CMake, ordinary
documentation and historical seals. No generated binary is executed here.
Root owns independent execution and integration approval.

## Recorded facts and declarations

`PhysicalRuntime::initialization_context()` and
`DeltaRuntime::initialization_context()` return a fixed-size value recording
successful construction as `empty_constructor`, `initialized_database`, or
`rebuilt_snapshot`. The latter two retain exact applied `BuildOptions`, including
method and optional cumulative build cap. Empty construction records **no**
applied BuildOptions: its mode bootstrap uses the existing ordinary options.
The route is set after successful build and is unrelated to replay counters;
empty direct and empty insertion-replay databases remain distinguishable.
A rebuilt runtime gets the new rebuild route/options and owner. Failed builds
produce no successful artifact or history. BuildMetrics remain separate work
measurements; no timing or total-memory assertion is added.

`QuerySession::run_context()` returns an owned immutable shared context created
at admission. It records stream / typed physical / typed window input, exact
`io::InputOptions` and limits, optional queue/window options, default snapshot limits (individual snapshot calls may override them),
initialization, exact requested `DeltaOptions`, and resolved initial delta mode
and completion. Typed input preserves the validated default wire-option fields
but marks wire format **not applicable**, rather than claiming JSONL decoding.
The context survives stop, drop and destruction of the session through a copied
handle. The runtime has no session mode-switch API; its recorded initial options
are therefore the session's fixed run policy. External `TransportBatch` builder
limits vary by caller/batch and are not session queue configuration or inferred.

`DeclaredBenchmarkContext` owns optional run, input-adapter, output-codec and
sink labels. It has no mutator; callers allocate it explicitly before mutation.
`DeltaRuntime::declare_benchmark_context()` replaces only the current diagnostic
declaration; outer delta begin copies its owning handle into that attempt.
Rebuilt runtimes inherit the caller declaration but record a new construction
route. SessionOptions accepts the same immutable handle. Missing labels are
null; empty labels remain explicit empty labels. Arbitrary native byte strings
are retained without JSON, hashing, UTF-8 validation or scalar coercion.

These labels are **caller-declared and unmeasured**. A label cannot identify,
validate or characterize a `std::function` target, grant proof authority, imply
sink acknowledgment, assert durability, establish recovery, or establish a cost
bound. Changing declarations midway through an attempt does not relabel it.
A caller which changes callback implementations must supply an honest benchmark
identity; reporting cannot infer this. Diagnostic declaration changes do not
advance the semantic mode-generation counter. Current declarations and begin
bindings are deliberately separate even when the labels happen to match.

## Actual attempt disposition

Enabled outer delta attempts gain `ObservationSummary::output`. Its flags are
set at actual existing execution seams; the immutable begin configuration is
never rewritten:

| Field | Recorded fact |
| --- | --- |
| `discard_drain_requested` | `start_drain()` reached output suppression, even if a subsequent mandatory charge fails. |
| `completion_drain_invoked` | The completion helper `drain()` was invoked; it can preserve retention and does not mean suppression. |
| `retention_disabled` | Mandatory suppression charges succeeded and output retention was disabled. |
| `prepared` | Required delta preparation completed. |
| `published` | Existing physical/live commit barrier completed. |
| `released` | Output ownership closed, including empty publication, rollback, explicit discard and final consumption. |
| `transferred` | At least one native row was transferred by `next()`. |
| `serialization_invoked` / `sink_invoked` | A real corresponding callback was invoked; success/failure remain the existing separate counters. |
| `unread_discarded` | At least one previously retained row was released without transfer/acknowledgment. |

Initial retention is always `retain`. `retention_disabled` also covers future
mapped records suppressed before spool insertion; `unread_discarded` alone does
not count these. Flags can describe mixed outcomes, such as one transfer followed
by discard; they are neither row totals nor mutually exclusive modes. Empty
retained output and empty suppressed output stay distinct. Pending/committed/
aborted outcome remains in the enclosing summary. Completion drain does not
claim timing of every required phase; earlier mandatory metrics retain their
meaning and partition. Callback invocation does not claim serialized bytes,
external delivery, durable acceptance, or exactly-once behavior.

Output owns a local lifecycle value and a begin ticket. Its summary remains
mutable only during that attempt's output lease. Closing it seals further
updates, including empty epochs which can outlive later attempts. Deferred
callback discard retains the existing borrowed-row and acknowledgment semantics.
Rollback records release before final aborted summary; state/journal rollback
and all mandatory budget checks are unchanged. Failure to suppress retention
keeps `retention_disabled=false`; no silent successful-drain claim is made.

## Ownership, optional-off behavior, and export

Construction metadata is fixed-size. Session metadata and declared strings are
owned once at admission, with shared const handles copied in observation hooks.
`ObservationSnapshot` and `ObservationSummary` are now nontrivial, explicitly
noexcept-copy/move values: no vectors/maps/strings are copied during mutation,
cancel, output close or session drop. Shared-handle copy does not allocate;
releasing a last owner may deallocate. Existing explicit trace export may allocate.
Session admission gains the documented owned metadata allocation/copies; failure
there is ordinary construction allocation failure, not a new semantic check.

Off still has no observer, trace, attempt summaries, optional clocks or output
hook updates. Mandatory metrics, caps, event IDs, output and cleanup remain
active. Successful construction/session metadata and caller declarations remain
readable independently of telemetry; they do not fabricate disabled history.
Counters/timed/trace use the same new flags without adding clocks. Nothing here
validates native byte values via JSON on admission or failure unwind.

`io::write_run_context_json(snapshot, max_bytes)` is a separately allocating,
strict UTF-8 version-1 companion export. It serializes actual recorded facts and
caller-declared context in separate provenance-bearing objects, current and last
attempt bindings separately, all native session option fields, and null for
missing metadata. It copies neither current mode nor current declarations onto
history. Mode owner/generation references point to the existing full EXPLAIN
configuration; saturated generations remain explicitly marked. This companion
has no metric totals, avoiding reinterpretation of disabled/unavailable payloads.
Its byte cap is the encoded artifact cap. Invalid UTF-8/native-byte labels fail
**this export only**. No partial artifact is returned and no sink is called.

The existing EXPLAIN CLI is rebuilt as a linkage consumer only. Its accepted
report schema/CLI behavior is preserved: it does not silently emit this new
companion or claim the old unknown fields are now implemented. Native report
integration must include this companion shape or a versioned schema extension,
with independent JSON shape and UTF-8 tests. Human report extension and schema
integration remain pending. The new exporter itself is a callable library seam.

S05 total bytes remain open. Queue, spool, window and snapshot accounted-byte
ceilings retain their concrete existing payload rules and exclusions: allocator
headers, tree links, transient old/new allocations, cursor-produced rows and
other component-specific metadata are additional. The admission metadata added
here is also additional and not charged into unrelated payload caps. S04/A02,
durable sinks/checkpoints and recovery are not discharged by any label or flag.

## Compiler-only build and ABI closure

Use include precedence: **run-context → mode-binding → runtime → EXPLAIN → native**.
The patch targets the already-layered mode/runtime proposal, not the native tree.
`patch-baselines.json` names each exact predecessor; `baseline-sha256.json` pins
native, predecessor, report and reused non-runtime archive inputs.
`overlay-sha256.json` identifies the proposed files. None of these patches is
applied by the helper scripts.

All nine runtime TUs must be rebuilt against these public layouts: support,
physical, delta, observation, session, replay, window, IO support and inspection.
In particular, every object returning/copying the now nontrivial observation
snapshot must use the same header; old mode/runtime archives are ABI-incompatible.
SessionOptions also gains a shared handle. Recompile every independent test,
consumer, app and report object. Reusing just changed objects is invalid.

The fresh layered transitive source audit here rechecks 49 non-runtime TUs. Core
`src/io/batch.cpp → include/crown/io/batch.hpp → include/crown/io/ingest.hpp → IR`
does not include session/delta/observation options. Native core/plan/sql/PG
archives may be reused only at the pinned hashes; no changed runtime layout is
passed through them. Replay/window runtime TUs are rebuilt regardless. Actual
compiler dependency closures and hashes are retained in compile evidence for
both runtime and all report/CLI consumers; a future include-graph change requires
redoing this audit, not trusting the old count.

```sh
python3 docs/verification/o07-run-context-proposal/build_proposal.py /tmp/crown-o07-run-context-testing --testing --opt 0
python3 docs/verification/o07-run-context-proposal/build_report.py /tmp/crown-o07-run-context-report-testing --runtime-evidence /tmp/crown-o07-run-context-testing/compile-evidence.json
python3 docs/verification/o07-run-context-proposal/build_proposal.py /tmp/crown-o07-run-context-production --opt 3
python3 docs/verification/o07-run-context-proposal/build_report.py /tmp/crown-o07-run-context-report-production --runtime-evidence /tmp/crown-o07-run-context-production/compile-evidence.json
```

The runtime recipes compile all nine TUs with strict conversion warnings and
`-Werror`; report recipes compile all three existing report/CLI consumers plus
the new exporter and link the complete matching runtime archive. `CROWN_RUNTIME_TESTING`
is consistently on for testing builds and absent for production. These are
compiler/linker checks, **not test passes**. No native build directory is changed.

## Required independent execution before integration

1. Empty constructor, empty direct build, empty replay build, populated builds,
   failed builds and rebuilt owners: exact method/cap, source identity and no
   historical generation contamination; option copies independent of caller.
2. All stream formats and options, typed physical and typed window inputs with
   non-default queue/window/snapshot/run limits; context remains exact after
   stop/drop/destruction; typed wire applicability is honest.
3. Retained preparation versus suppression before/after rows and after prepared;
   empty result, paused drain, abort/cap failure, partial transfer then discard,
   unread destruction, session drain/stop/drop, moved epoch and old empty epoch
   surviving a later attempt; all literal flags and existing metrics reconciled.
4. Failed/retried serializer and sink, deferred callback discard and reentrancy;
   callback invocation is distinct from acknowledgment; changed caller labels
   and successful/failed/no-op mode switches preserve old begin identity.
5. Off/counters/timed/trace produce identical accepted results and rollback
   state; optional off clock probe stays zero, existing caps/event IDs unchanged;
   nonallocating mutation/cancel/release hooks and disabled history stay absent.
6. Companion strict JSON parses, fields match the typed metadata independently,
   invalid UTF-8 stays accepted as native declaration and fails export only,
   controls/NUL escape, exact encoded-size boundary, missing versus empty labels,
   unavailable history, and no old-current relabeling.

## Full O07 work still outstanding

The accepted EXPLAIN proposal handles an owned validated physical plan and
optional typed proof/candidate evidence. It still needs independent owning
report shapes for **live `SearchProgress`**, interrupted/budgeted search,
certificate replay progress, and **`VerifiedInfeasible`** when no physical plan
exists. A progress status or edited flag cannot create infeasibility/optimum
proof. Preserve exact original bindings and typed authority; structural height,
finite candidate-family exhaustion, and future statistics/cost ranking remain
separate claims. These report additions should not be forced through a fake
physical-plan constructor.

Current-result cursor observation also remains: optional startup, successful
advance, exhausted advance, failed call and cleanup timing; explicit empty,
nullary/Boolean, cancelled and failed terminal status; per-cursor lifetime and
maximum-result-work scopes; mandatory lease release with telemetry off. Existing
view/cursor `last` work is not an additive extra phase. No cursor timing claim is
made by the delta output flags in this proposal.

Other full gates include native integration and schema/human-report wiring,
independent workload/trace/metric reconciliation, input/window/build/inspection
observation coverage, requested report failure cases, and the full native
configuration matrix. B03's benchmark runner, O08's general CLI/install scope,
S05 whole-memory and durable/recovery gates remain distinct. No performance,
resource-completeness, progress or verification claim follows from compilation.
