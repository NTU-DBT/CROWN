# Barrier-based reoptimization (C06, verified component)

C06 component acceptance is verified. Native candidate rebuild, ordered catch-up, exact equivalence,
managed-root installation, same-lock selected-plan recovery, immutable sink
lineage, rotation, retirement and journal promotion are implemented. Development
checks exercise actual switches against a non-switching reference. The optional
C05 bridge, nonzero-prefix switch/promotion cuts, recovery allocation admission
and bounded churn are implemented. The moved SDK example passes on both backends.
All28 selected GCC Debug tests pass190.37s. All20 C06 tests pass in fresh source-only
GCC13 Release78.70s and linked Clang18 Release84.45s. Eleven fresh ASan/UBSan/leak
checks pass115.22s. The moved SDK passes in each ordinary compiler profile.
The13-requirement audit binds1739 frozen paths,1073 current code/test inputs,
142 actual archives/executables/example objects and11 final receipts in
`build/verification/c06-transition-acceptance-v1.json`. All295 predecessor test
definitions/properties are preserved;302 tests register. This component packet
does not claim a full302 execution or R0/R1 release. The full Refactor.md goal
remains active.

## Native foundation

`DeltaRuntime::rebuilt_for(candidate, build, replan)` lowers a typed P07
minimum-height candidate from the current owner's complete admitted SQL/CQ source.
It snapshots/rebuilds at the exact committed physical epoch while the original
owner remains intact. Both owners, new executable metadata, intermediate source
rows, target state and live bootstrap use the original query account. Caller
row/program exports and a new independent memory grant are not used.

The source must be writer-ready: private epochs, pinned result cursors and
unread delta output block bootstrap. Source/schema/backend producer options and
actual output mode remain bound; the target gets a fresh runtime owner identity.
ReplanLimits bound metadata compilation separately from BuildOptions' snapshot,
bulk state construction and live bootstrap. Their costs must be combined in the
eventual C06 report, not described as free work. An exception destroys unpublished
target storage and leaves original committed state available for retry.

The new fixture covers direct CQ and SQL EXISTS, reference/indexed backends,
maintenance/delta modes and direct/insertion-replay builds. It checks actual
alternative trees, exact epoch/source/result/delta preservation, shared memory,
busy barriers, exhausted compiler/build/memory grants and retry. Its current
build/test outcome is recorded in the handoff rather than assumed here.

## Policy units and boundaries

`runtime::reoptimization::evaluate` is allocation-free pure arithmetic. Forecasts
are explicitly caller predictions of old/target nanoseconds per input and a
future input horizon. C02 height/depth/slot scores are not converted implicitly
to time or bytes, and no C03 policy is enabled by labeling a caller prediction.

The policy enforces a minimum physical-epoch gap, relative basis-point and
absolute savings floors, and payback of measured snapshot/rebuild, catch-up and
equivalence time plus a declared publication/cleanup reserve. Division and exact
rounding avoid overflowing products; unavailable forecasts, bad epochs, insufficient
benefit, short horizons and unrepresentable cost sums remain explicit rejections.
Actual publication/cleanup time must be reported afterward; the reserve is not
a latency guarantee or permission to roll back an already selected durable root.
Arithmetic eligibility alone grants no structural, memory, equivalence, output
or recovery authority.

## Required session protocol

The current preparation API is `begin_reoptimization(candidate, options)`,
`request_reoptimization_barrier()`, `advance_reoptimization(quantum)`,
`reoptimization_status()` and `cancel_reoptimization()`. Preparation requires a
started, committed, delivered, writer-ready session; it can preserve an existing
pause and queued input. An optional expected actual owner/epoch rejects stale
caller choices before rebuilding. Core runtime consumes typed candidates without
depending on the optional selection runtime library.

While the old plan runs, one original-account row and linked record are funded
before each physical begin. Their complete real requests, including allocation
framing, are checked against backlog limits. Publication links the staged record
without allocating. Aborted native attempts release the staged record; committed
no-ops stay in order. A staging, memory or replay failure releases only candidate
state and unfreezes admission; the ordinary writer keeps its normal transactional
failure/retry rules. Window metadata does not create a ledger record or epoch.

Barrier requests freeze new typed admission and unread stream decoding. Already
admitted queue entries, cached stream rows and every remaining watermark substep
drain on the old owner. The normal output API must consume old output; attached
local sinks must accept even empty epochs. Internal draining can finish a paused
epoch while preserving the public paused state. It never discards output to
advance a switch. The existing empty-queue checkpoint guard stays in place.

Private catch-up discards its own output and keeps an unfinished target epoch
across calls. Quantum and `catch_up_steps` count native begin/step calls, whose
ordinary per-epoch grants remain in force; they are not bounds on CPU time.
`catch_up_native_work` reports physical plus delta coordinator work for completed
replays. Staging work charges descriptors/string bytes before copy. Exact source
and result comparisons use funded ordered native rows, erase each matched target
row, and charge field/string comparisons. `equivalence_work` covers this explicit
comparison/materialization work; `equivalence_rows` bounds visits on both sides
across source and result rows. Two result cursors each have the separate finite
`equivalence_cursor_work` limit. `equivalence_native_work` reports their observed
mandatory work; a failed construction increments `equivalence_unobserved_startups`
because no cursor metrics survived. Indexed storage retains its ordinary finite
operation grants throughout; these counters are different work domains.

`verified` means exact source/SQL-result equality at the same physical epoch and
eligible measured payback. It retains both owners and freezes admission; it does
not publish a plan. Missing forecasts reject honestly. Explicit cancellation
releases candidate/ledger resources and permits old-plan admission again. Status
reports cumulative original-account current/peak memory, never a fabricated
phase-local peak. Catch-up time includes ledger staging and private replay;
old-plan barrier drain time is reported separately to avoid charging baseline
maintenance twice. Preparation clocks are enabled only for an explicit candidate,
with their own read counter independent of optional ordinary observation mode.
Snapshot/rebuild timing starts before the funded candidate control allocation.
Dropping the session releases that control as well as target and ledger storage.
Original journal/generation uncertainty releases candidate resources, reports
`recovery_required`, and keeps all existing journal admission/output gates and
locks. Cancelling a candidate cannot bypass authoritative old-plan recovery.

The remaining publication protocol follows.

Keep the QuerySession owner, input reader/queue, window controller, source positions,
accepted/physical progress and delivery owner stable. Rebuild a target at snapshot
epoch S. Stage funded catch-up entries before old commits; commit markers must
publish without throwing. Record each committed physical update, including no-ops,
in exact sequence. Window metadata steps keep the original command controller;
they do not invent physical epochs. Replay only committed entries into the target
and discard its output privately. Bounded ledger exhaustion cancels migration or
applies explicit backpressure while preserving old-plan progress.

At the final barrier, freeze admission and drain already admitted queued/window
commands through the old plan with all normal output obligations. Require no
private state, pending WAL input, unread/recovered output, partial watermark or
delivery backlog. An attached sink must durably accept every old epoch through B,
including empty epochs. Match target/source sequence B, exact source state and
the complete configured result view under finite work/memory limits: SQL rows
by default, or the explicitly requested core view. Existing checkpoint queues
must be empty: removing that check without a versioned pending-input envelope
would lose admitted input on recovery.

Before publication, prepare all target metadata/encoded files, new WAL ownership,
run/report context and switch bookkeeping. After a successful durable selection,
in-memory runtime/context/WAL replacement must not allocate or throw. Retain the
old runtime until switch completion; charge its temporary overlap and subsequent
release. Existing source-catalog aliases in reader/queue may retain old executable
metadata: rebind exact compatible source ownership or include that retained
memory honestly, including through repeated switches.

## Durable selection and sink lineage

`CROWNGR1` v3 has a required selected `.plan` hash and an optional delivery anchor:
276 bytes without delivery,388 with it. v1/v2 retain their exact212/324-byte forms.
The root selects its own generation's `.plan`, so rotations retain a complete
descriptor without depending on a historical file. Descriptor link/file/directory
sync must finish before root selection. Candidate cleanup removes only the next
unselected checkpoint/WAL/descriptor; retirement removes that exact historical
range and preserves the selected descriptor. The v2 retirement intent adds the
selected plan hash while keeping v1's724 bytes unchanged. Before deleting history,
the generation owner rereads/checks the current descriptor under the receiving
query account. An uncertain root rename latches the owner against reuse.

`CROWNPL1` descriptor v1 records predecessor selection, source/target bindings,
switch generation and physical/command frontiers, optional exact immutable sink
origin, and opaque compiler artifact bytes. Descriptor v2 adds the last actual
switch epoch, separately from subsequent checkpoint/metadata selections. Rotation
refreshes predecessor/frontier metadata, preserves that hysteresis epoch, and
records a sink attached after the switch. Legacy v1 bytes remain unchanged.
The codec checks full framing/checksum,
monotone frontiers, logical source/catalog/policy continuity, and bounded original-
account byte ownership. Its work grant charges four byte visits per frame byte;
compiler replay and native build grants stay separate. The codec deliberately
grants no semantic/native switching authority. Ordinary caller-plan recovery
rejects v3 roots; use the locked descriptor admission API below.

`io::CompilerPlanArtifact` is an explicit compiler input boundary: prepare from a
checked `PhysicalPlan`, or replay the entire artifact through `read_physical`.
Retained bytes and native executable metadata use a caller-supplied compiler
account. Factory wall time includes temporary JSON/string/PhysicalPlan teardown.
Standard compiler DTO temporaries remain outside native execution accounting;
the reported compiler-account current/cumulative peak does not claim those bytes
or a phase-local/global peak. Native execution must freeze metadata into its
original receiving account and reuse its existing finite indexed admission grant.
No compiler-artifact factory runs inside a native session mutation. Publication
includes measured artifact preparation and native publication preparation in
payback, alongside rebuild/catch-up/equivalence and the declared irreversible-work
reserve. Publication and cleanup times are measured after selection. Cleanup
includes the old runtime and checkpoint/image scratch release; returned current
memory is sampled after that release. The compiler account is reported separately.

After `advance_reoptimization` returns `verified`, explicitly prepare the checked
target's `io::CompilerPlanArtifact` outside native mutation, then call
`publish_reoptimization(artifact)`. The artifact must match the verified target's
complete physical/source identity. Publication requires a managed root, healthy
unfinished input, empty private/admitted input and window work, and complete normal
delivery. It preserves paused state, input/controller progress, current workload
configuration and the original query account while installing a fresh owner.
Rebuild-era counters are reset at B. Preparation failure retains the old owner
and permits retry with the same immutable compiler input. A final payback rejection
releases the candidate without selecting its prepared files.

Native publication prepares all metadata and target-bound files before selection.
The small selection guard retains the root lock and marks recovery-required after
an ambiguous selection. After durable root publication, installation uses only
nonthrowing moves and cleanup; no rollback root rewrite or allocation is attempted.
The old runtime remains owned until that selection completes. Clock diagnostic
failure after selection cannot cancel an installed runtime.

For recovery, `lock_generation_recovery(expected_source, root, options)` acquires
the actual root lock and funds descriptor loading in the receiving query account.
Its move-only `LockedGenerationRecovery` exposes borrowed immutable compiler bytes.
The caller explicitly runs `CompilerPlanArtifact::replay` while retaining this lock,
then consumes the package with `restore_selected_generation`, or its local-sink
variant. Native admission imports into the same receiving account and checks exact
descriptor/artifact/checkpoint/WAL binding before any tail repair. The expected
source cannot choose a different physical plan. Legacy roots can use the same
handoff with the expected original compiler artifact. Pending retirement requires
sink-aware admission before any replay or repair.

`promote_journal(root, options)` checkpoints a healthy quiescent journaled session
under a new managed root at the following generation. Its first retained generation
is the new one. Existing unmanaged checkpoint/WAL bytes and sink header remain
unchanged; subsequent native switches use the ordinary managed-root protocol.

Selected-plan recovery allocates its persistent generation holder before native
admission and tail repair. Exact runtime binding is checked before opening/replaying
the WAL. Sink schema/origin/prefix checks also precede repair. A rejected receiving
allocation or exact-heap admission releases the original root lock without changing
either incomplete tail; only a completely admitted native session repairs them.

Keep exact physical-image/WAL and sink-header binding checks. Publish a bounded,
reconstructible plan descriptor per selected generation. It must bind the checked
target program, predecessor selection/final barrier and, when attached, the exact
immutable sink-origin header. A backward-compatible root version must bind the
descriptor's hash alongside the target checkpoint/WAL selection. Sync descriptor,
checkpoint and fresh target-bound WAL before the one root publication. Candidate
cleanup and later rotations/retirement must preserve all descriptor dependencies.

Do not rewrite or weaken the existing sink header. Open its exact immutable
origin identity, then independently validate selected-plan/source/catalog/policy/
result-schema compatibility and the existing delivery-prefix anchor. Append only
new physical B+1 output under the new generation, never private catch-up output.
Retirement must use validated lineage, rather than direct equality between an
old sink physical binding and the new WAL. Version retirement intents to retain
the new selection metadata while preserving historical root/intent codecs.

Generation-root rename plus directory sync is the durable commitment. An ambiguous
post-selection failure marks recovery-required, blocks future admission/output/
publication, and retains locks until drop/destruction. Do not overwrite the root
to "undo" an uncertain selection. Recovery must load the authoritative selected
descriptor under the same root lock and restore whichever complete selection
survived. Journal-only sessions need a managed-root promotion/recovery entrypoint
before their physical binding can switch.

## Optional C05 integration

Link `crown_selection_runtime` and call
`selection::select_for_reoptimization(snapshot, source, session, request)` to get
a measured `CurrentSelection`. Unlike ordinary `select_current`, this explicit
entry measures complete wall preparation, including capture, ranking, lowering,
cache work and temporary teardown. C05's optional active-time diagnostics remain
distinct. An unmeasured zero is not interpreted as a free selection.

`selection::begin_reoptimization(session, choice, options)` rechecks owner, epoch,
physical source/options, pending state, statistics reset/configuration/mode and
facts needed by the effective policy. It rejects stale and foreign choices and
sets the native owner/epoch fence. The native layer independently rebuilds from
the checked candidate and actual session. Measured selection plus validation time
enters `costs.selection_prepare_ns` and checked payback addition. C02 model scores
are never converted into time estimates. Native `QuerySession` candidate APIs
retain no dependency on the optional bridge.

Prepare its durable input explicitly outside native mutation with
`CompilerPlanArtifact::prepare(compiler_account, choice.selection().plan())`.
This overload exports the native compiler metadata, performs independent canonical
lowering, checks full source/physical identity and serializes that canonical input.
Its measured time includes the DTO export/reconstruction and teardown. Transient
standard compiler DTO memory remains explicitly outside native query accounting.
Complete `read_physical` replay of these bytes is covered for CQ, SQL and both
backends, including native C05 selections.

The installed `examples/reoptimization` client links only
`CROWN::selection_runtime`. Run `crown_reoptimization run DIRECTORY reference`
then `crown_reoptimization resume DIRECTORY reference` (or use `indexed`) in
separate processes. It demonstrates a real physical-tree change, explicit predicted
time inputs, normal no-op delivery, paused installation, rotation/retirement and
same-lock selected compiler replay. Its source grant and forecast values are
example inputs, not measured speedups.

## Resource and failure verification

Development switch cuts now prepare at epoch1, replay two committed records and
select at B=3 with all three normal output epochs already delivered. Journal
promotion cuts likewise start at delivered B=3 and preserve original unmanaged
files. Before/after syscall and process-crash cuts recover the original or complete
new selection and validate the next output; allocation denial begins at root
publication to cover installation and scratch cleanup.

Recovery tests sweep all1105 actual receiving allocations across both backends,
with two incomplete tails. They prove exact/one-under heap behavior, unchanged
durable bytes on failed admission, released locks, retry and eventual repair.
The sweep exposed a generation-holder allocation after repair; that allocation is
now before admission. No additional catch scaffolding is used.

The bounded churn test switches64 times across backend/mode combinations and128
physical inputs. It varies data, forecasts, statistics configuration and pause,
compares exact normal delivery with a non-switching reference, retires each old
generation and restarts after deletion. The heap stays at32MiB, history at two
generations and the sink at32 epochs. Steady native-state requests/allocations do
not grow with switch count. The sink's actual reported index/scratch vector bytes
are tracked separately under the declared retained-log exception in Refactor.md;
they still count toward the original account's current bytes and peak. Complete
owner destruction leaves only the held account controller.

## Dependency structure and acceptance scope

The native runtime consumes typed candidates from crown_plan. The optional C05
bridge lives in `crown_selection_runtime`; actual runtime archive symbol audits
show no dependency back to it. C05 owner/epoch/source and configuration are checked
again at native preparation. Descriptor encoding/admission preserves S05's
original-account and explicit compiler-input boundary; no PhysicalPlan/JSON export
runs inside native mutation.

Accepted checks include genuinely different trees, repeated switches, nonempty
queues, paused sessions, duplicate window labels, metadata-only expiration/partial
watermarks, empty-output epochs, sink backpressure, rates/data changes and exact
non-switching references. Persistent allocation faults must cover rebuild, ledger,
equivalence and file preparation. Fault/crash cuts cover descriptor/checkpoint/
WAL publication, root rename before/after effect, directory sync and allocation-free
installation. They recover either surviving root with a sink already through B. Reject
foreign/missing plans, altered origin headers, bad schemas/prefix anchors and
conflicting retirement inputs before repair/deletion. Retirement/restart after
historical generations disappear is covered. Receiving-admission allocation sweeps
exclude pending retirement cleanup, which retains its separate recorded recovery
protocol and inherited fault controls. Forecasts remain declared predictions;
neither automatic arrival-rate inference nor measured speedups are claimed.
Full release reviews, licensing disposition and the other Refactor.md cards remain
outside this C06 component acceptance.
