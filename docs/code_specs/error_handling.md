# Error handling: disposition and one simplification

Session [update-pattern enforcement](../update_patterns.md) adds no catch or
rollback layer. Borrowed rule checks and whole-watermark scratch reject before
journal/native preparation. The existing begin boundary latches a completed
semantic Error and releases private preparation. If allocation fails while
constructing that error, the same boundary leaves the command retryable without
a semantic latch. The fixed violation stores no row or formatted message.
Declaration limits reuse existing failures; versioned image checks reuse
ImageFailure. The [V52 controls](../verification/update-pattern-runtime-v52-2026-11-14.md)
cover five persistent C++ new denial points on this rejection path.

`EventReader::peek` keeps one consuming-preparation catch: framing/decoding,
record limits, source ordering and cached publication can fail after stream bytes
have been consumed. The handler latches failure and rethrows the original error.
Engine application happens after `peek` returns, so a complete cached event can
still be retried after engine rejection. The source comment now names this full
scope; the correction changes no executable token or handler. See
[reader acceptance](../ingestion.md).

Checked aggregate integer casts add no production handler. The compiler retains
one immutable guard per original column; shared projection spends its existing
budget and raises aggregate_overflow before group mutation. Standalone private
proposals or the composed source/native token already own cleanup. The durable
Session's existing semantic classification records a Reject and verifies the
same failure on replay. Raw bigint types, mutable operator state and the single
native rollback path remain the relevant ownership boundaries. See the
[aggregate usage contract](../sql_aggregate_runtime.md).

The [complete physical checkpoint](../sql_aggregate_checkpoint.md) adds no
production catch. Inspection rejects malformed/budgeted bytes before receiving
allocation; restore matches expected metadata, then uses normal owning cleanup
and the genuine cold factory. Source constraints/arithmetic keep their original
errors. A delivery-anchor DTO cannot replace a sink receipt or an uncertain-I/O
recovery latch. There is no new handler or checkpoint field on ordinary updates.

The [genuine R2 descriptor](../sql_aggregate_descriptor.md) and selected opaque
checkpoint port add no production handler. Bounded wire checks use ImageFailure;
existing compiler/schema/account failures propagate through owning cleanup.
Descriptor admission exposes a fresh C0 owner only after exact original binding
and actual native recipe comparison. The shared selected-file reader retains
the existing plan reader's root/stamp/EOF/hash discipline for both file types.

The [R2 record foundation](../sql_aggregate_records.md) adds no production
handler. Fixed malformed/version/type/budget checks use the existing ImageFailure
carrier; owned account buffers clean up through normal value destruction. A WAL
feed validates one fixed-size candidate before publishing it. It does not infer
fsync success, repair a tail or translate resource denial into a semantic Reject.
The upper [durable Session](../sql_aggregate_session.md) supplies the explicit
native publication and recovery boundaries; the codec remains transport only.

Physical [source capture and cold reconstruction](../sql_source_images.md) add
no production catch or retry/undo framework. A fresh unpublished owner reuses
the existing source/native prepared token and group arithmetic. Owning values
release incomplete work on failure; lowerer, domain, work and allocation errors
keep their existing carriers. In particular, a foreign genuine tree can fail
the real lowerer before the later snapshot-binding comparison. Tests describe
that actual boundary rather than requiring a new translation catch.

The handler counts below describe the frozen W02 human-review packet, not later
source additions. W03 adds one weighted cursor `next` boundary: on a throwing
read/output operation it releases borrowed state/readers, records spent work and
rethrows the original error. It neither rolls back nor changes committed query
state. Cursor creation publishes a reader only after its complete preparation.

W03 also removes a redundant overflow guard in each weighted metric helper.
Each managed category counter starts at zero and is a subset of cumulative
work, so successful cumulative charging proves both additions fit. The scoped
helper contracts state that invariant; no rollback or reader-cleanup boundary
was removed.

The v6 candidate/session inspection keeps the existing resumable exception
boundaries. Candidate capacity and immutable payload still precede committed
dedup membership; publication then uses a nonthrowing handle move. Geometric
capacity growth removes repeated prefix relocation without adding a catch,
wrapper or state field. The compatibility replay report now distinguishes a
checked finite witness from a checked empty family. The source audit records
the exact behavior substitutions separately from comment-only changes.

The next inspection pass also removes the Boolean and physical metric guards
under that same invariant, and a cursor null check on the address of an existing
`next_entry()` tuple. Real nullable lookup checks remain. Physical source
preparation now relies on the unique `Data` owner already held by `begin_staged`:
unwinding runs its rollback destructor before public error presentation. The
local rollback/rethrow catch duplicated that RAII obligation. Resumed routing
still needs its explicit abort catch because the caller retains the token.
The allocation-factory cleanup and native-to-public diagnostic catches remain
necessary; their scoped cards state the ownership or presentation obligation.

The frozen source inventory contains **1240 C++/Python handlers**: 343 in maintained components/tools/examples and 897 in tests. Production/tools include 67 broad handlers. `catch_inventory.json` in the verification packet records each path, line, handler and body. These are syntax counts, not a defect count. Shell traps, CMake fatal errors and implicit RAII unwinding are outside that count.

| Suggested production category | Handlers |
| --- | ---: |
| cleanup_or_inverse_before_propagation | 23 |
| durable_authority_or_poison | 7 |
| explicit_result_or_stop_boundary | 125 |
| other_needs_context | 81 |
| process_or_tool_boundary | 33 |
| public_error_translation | 74 |

The categories above are triage hints. The focused semantic dispositions below explain actual contracts; unlisted handlers have not been individually certified.

| Boundary / source | Disposition | Reason |
| --- | --- | --- |
| [Account factories](../../include/crown/resource/ownership.hpp), [controller construction](../../src/resource/memory.cpp) | Keep cleanup catch | Construction can fail after raw allocation; deallocate that exact storage before propagating. |
| [Indexed journal](../../src/storage/accounted_indexed_journal.inc), [support stage](../../src/runtime/support.cpp) | Keep paired storage and metadata undo | One restores memberships/nodes, the other flags/counts. Inverse work and pins must be funded before mutation. |
| [Delta callback/delivery](../../src/runtime/delta.cpp) | Keep retry/deferred-discard boundary | A callback can fail or move/close a facade while a retained row and lease still have to survive until callback return. |
| [Session finish/journal_append](../../src/runtime/session.cpp) | Keep recovery-required latches | WAL decision/append may be durable or uncertain; ordinary rollback cannot revoke that authority. |
| [SelectionGuard/generation restore](../../src/runtime/session.cpp) | Keep lock ownership and preallocation order | An uncertain selected root retains authority; a final holder allocation must precede durable tail repair. |
| [Native statistics](../../src/runtime/native_statistics.cpp), [support P/E capture](../../src/runtime/support.cpp) | Keep narrow exhaustion catches | Budget exhaustion produces an explicitly incomplete distribution while prior exact components survive. Corruption/foreign-owner faults must propagate. Empty Exhausted catches are intentional local completion boundaries. |
| [Planner continuations](../../src/planner/search_session.cpp), [candidate sessions](../../src/planner/candidates.cpp) | Keep explicit stop translation | Resumable work needs distinct resource, allocation, counter and internal-failure outcomes; catch count alone cannot justify removal. |
| [Operation::note](../../src/planner/selection.cpp), [component_diagnostic](../../src/planner/selection_budget.cpp) | Remove local exception-only conversion; applied by root | The former path threw a fixed Failure just to catch it and copy fields. Both paths now share a noexcept enum-to-value mapper; throwing callers still call component_failure. |

The mapper change preserves every enum mapping, optional component and reason bit. It changes no allocator, transaction, durable lock or error category. The proposed three-file diff remains in `component-diagnostic.patch`; root applied it and owns linked regression testing. No runtime speedup is claimed without measurement.

The current resource/reference/indexed inspection adds individual block contracts
without introducing a runtime handler. The two resource catches free partially
constructed raw storage. Reference insertion removes partially installed
memberships, and journal insertion separately reverses a completed insertion if
acquiring its pin fails. Indexed publication/undo already has no catch clauses:
it prepares allocations, inverse ownership and work admission before mutation.
Final table-State release can still destroy all resident rows/index metadata;
allocation-free commit/rollback is not necessarily constant-time cleanup.

The W05 weighted composition port reuses the existing pending epoch's single
abort/rethrow boundary in `stage_native`; it adds no count mirror or recovery
layer. Successful contribution capture records actual logical totals. Aborted
capture is a partial attempted trace and can retain caller shares before
normalization; an execution ordinal alone does not certify completion. See the
[weighted usage contract](../weighted_messages.md) and the source-pinned cards.

The SQL-row continuation removes the inner catch in private support
`PendingEpoch::Data::stage_tuple`. Both caller-held staging ports already abort
their token on failure; the two local-owner paths unwind their rollback owner.
The four-caller source proof and affected native fault gates are recorded in the
[W05 verification](../verification/w05-sql-rows-human-inspection-2026-11-12.md).
The outer abort boundaries remain. SQL-row source replacement prepares private
nodes and uses the native epoch owner without a new catch or source undo layer.
The compiler's diagnostic boundary and the cursor's terminal-failure/reader
release boundary remain necessary. Session catch removal is still a separate,
unapplied review proposal at this checkpoint.

The [v8 continuation](../verification/human-inspection-v8-2026-11-12.md) then
applies that one session simplification. `local_sink_impl` sets failed=true before
replacement file acquisition and clears it only after nonthrowing final moves;
the removed catch added no cleanup or durable authority. All selected sink
normal/fault/crash/replay and session tests pass in Debug and with sanitizers.
The cost/statistics handlers remain their public noexcept status boundaries;
EXPLAIN and accounted-arena scopes need no new catch. Comments and usage cards
add no executable checks. Separate input/recovery drafts remain unintegrated.

The [v9 continuation](../verification/human-inspection-v9-2026-11-12.md) integrates
input/recovery/window/report drafts while retaining all reader and durable-file
cleanup/publication handlers. It removes only the integer parser's dominated
final empty-span guard and unused capture. Successful branches already consume a
digit; syntax/range still rejects earlier. Selected ingestion/failure/memory and
recovery/window/report gates pass in both profiles. No handler, runtime state,
allocation layer or fallback is added.

The [v10 continuation](../verification/human-inspection-v10-2026-11-12.md) adds two
necessary post-clock activity checks. The timing helper can cancel and release
the candidate after the entry check, so staging must stop before allocation and
verification before target access. All existing handlers remain. Histogram lookup
uses existing sorted adjacency, preserving bounded-exhaustion publication rules;
it spends actual probes without refilling or replacing the allowance. No new
runtime wrapper, catch or allocation layer is introduced.

The [v11 continuation](../verification/human-inspection-v11-2026-11-12.md) retains
all 21 existing CLI component handlers after reviewing their distinct roles.
Two short final-main catches contain failures from those handlers' diagnostic
bodies: fixed JSON literals handle C++ bad_alloc and other standard exceptions.
The same final boundary flushes/checks stdout once per invocation. The pre-fix
process failures are reproduced, including persistent C++ allocation denial;
no native loop, retry, rollback or allocation framework is added. Error exit or
missing stdout never establishes the outcome of earlier durable operations.
Recovery codec/retirement keeps its one narrow ImageFailure translation and
existing file protocol; typed query/context/document keeps its scalar-context
translation. Comment/spec updates add no executable checks.

The [v12 header continuation](../verification/human-inspection-v12-2026-11-12.md)
adds usage/ownership/cost comments and contracts without executable changes.
These 23 headers contain no catches. Fixed versus legacy diagnostic policies,
five-domain admission, optional versus required owner access and native versus
public validation serve distinct boundaries; none is removed merely to reduce
the number of guards. No runtime instrumentation or new recovery layer is added.

The [v13 continuation](../verification/human-inspection-v13-2026-11-12.md) documents
recovery/session headers, storage internals and IR primitives without executable
changes. Fixed diagnostics avoid owning message strings; C++ throwing/unwinding
still costs runtime work. Native versus legacy policies and required owner/
kind/bounds checks stay distinct. The direct-CQ catalog error translation stays
narrow, and valueless-Value rejection remains meaningful. No new catch, retry,
allocation framework or per-update check is introduced.

The [v14 cleanup](../verification/human-inspection-v14-2026-11-12.md) removes the
unused delimited/text-cell parser helpers after complete maintained caller and
package-export searches. Six direct throw sites disappear with that unused
code; the active UTF-8 validator and its rejection helper preserve complete
C++/literal token streams. No catches are removed or added. Reader
poisoning, engine retry, source acknowledgement, native rollback and durable
outcome boundaries retain their documented distinct roles. Existing native and
installed-consumer checks pass in Debug and sanitizer profiles.

The [v15 capture/tool cleanup](../verification/human-inspection-v15-2026-11-12.md)
replaces an unnecessary histogram lookup scan after multiplicity sorting,
preserving allocation, resource admission and incomplete-result publication
boundaries. It adds no catches or runtime state. Offline mapping fixes preserve
source bytes and reuse a per-file digest; malformed encoding and stale review
remain visible failures. Test-support contracts distinguish C++ new denial from
malloc, account and byte-limit coverage. Existing native allocation/failure and
one-under work-budget controls pass in both profiles.

The [v16 nonproduction review](../verification/human-inspection-v16-2026-11-12.md)
adds no production handlers, state or update work. Offline oracle assertions
now distinguish equal-valued scalar kinds; its valid native corpora and focused
counterexamples pass. Existing test-only subprocess/schema/diagnostic boundaries
retain their explicit roles and limits. The CLI test-summary correction changes
one count and its closed package identity, with all other payloads preserved.
Comments in self-hashing generators remain byte-identical; their contracts live
in the sidecar maps. The separate dependency docstring correction is an intended
literal change, not token-equivalent comment evidence.

The [prepared source batch](../sql_rows_batches.md) adds no production catch or
source undo framework. Source/key proposals remain private until the existing
native epoch can commit; earlier native changes use that epoch's original abort
boundary. Closing the token destroys its backing workspace immediately through
existing ownership. Final constraint, arithmetic, work and allocation failures
remain visible, with retry at the unchanged sequence. This does not supply a
durable rejection or recovery decision; those belong to the upper
[Session](../sql_aggregate_session.md).

The [prepared aggregate batch](../aggregate_batches.md) also adds no production
catch or inverse journal. It leaves committed row/group maps untouched until all
final arithmetic, output and detached nodes are ready. The busy flag is set only
after construction succeeds; rollback discards private proposals. Token ownership
keeps its owner alive through cleanup.

The [original SQL compiler](../sql_aggregate_binding.md) replaces the rejected
upstream clone path with checked wire decodes. Existing arena/result owners clean
up partial construction. One public factory boundary converts ordinary CROWN
admission errors to diagnostics, while parser-contract and allocation failures
propagate. Its shared native parser gate and temporary ASTs are cold compilation
costs; they add no update-path handler or retry mechanism. Targeted first-arena
denial/retry checks do not certify every upstream allocator path.

The [composed aggregate runtime](../sql_aggregate_runtime.md) keeps source/native
rollback in the genuine child token. Touched group proposals and owned output
finish before publication, and failed preparation destroys them through member
ownership. Commit uses funded nodes and same-allocator state swaps. There is no
new production catch, joined-row ledger or duplicate undo system. Required native
fact capture is still real work and memory, released before returning the group
result; group-only state does not imply a whole-operation bound by changed groups.

## Per-primitive overhead worth keeping visible

| Primitive | Source evidence | Cost / minimal next step |
| --- | --- | --- |
| Boolean child-presence edit | [presence](../../src/runtime/support.cpp): `auto next=value` copies RecordState.present. | O(fan-out) array copy and possible allocation per touched row. If profiling justifies it, use scalar/slot undo at this one metadata boundary and preserve rollback; do not delete storage undo. The new W02 path independently uses compact scalar/slot undo. |
| Physical derivation erase/revive | [route/rollback](../../src/runtime/physical.cpp): `set_lifetime_containing` on ordered map nodes. | O(outstanding allocations) owner-ledger search. A future narrow owned-node map conversion can classify exact storage in O(1); preserve iterator/extracted-node stability and failure tests. This packet does not perform that refactor. |
| Indexed operation entry | [StorageOperation](../../src/runtime/storage_work.hpp): fresh StorageWorkState plus AccountedIndexWork. | Fresh-operation control allocations are explicit. Nested/resumed calls already reuse the original lease/grant; never pool/refill in a way that changes budget identity. |
| Hash-directory invariant check | [check_invariants_noalloc](../../src/storage/hash_directory.hpp): resident-by-resident chain search. | Allocation-free can still be O(capacity+n²) under collisions; it is a diagnostic, not a hot probe. |
| Weighted numeric edit | [weighted](../../src/runtime/weighted.cpp): inline scalars, cached child array, vector undo. | Default edits avoid full record/child-array image allocation; product recomputation still visits factors, and explicit capture/snapshot requests copy them. |
| Boolean child propagation | [support](../../src/runtime/support.cpp): `table.bucket()` materializes accounted matching handles before visiting parents. | O(matches) scratch/copy, separate from lazy result-cursor traversal. |
| Public/native tuple construction | [layout](../../src/storage/layout.cpp), [native factory](../../src/storage/accounted_layout.cpp): both validate the row. | An optimization candidate with different presentation details; preserving public field-index diagnostics and invalid-layout order is required before removing a pass. |

These are source-derived cost mechanisms, not measured regressions. Source comments and specs add no executable checks or instrumentation. The simplest safe design change removes work with no semantic role; it does not remove required admission, ownership or inverse state merely because another layer also has error handling.

## R2 file boundaries and the unlink quota correction

The [concrete R2 owners](../sql_aggregate_files.md) keep uncertainty at the POSIX
boundary. Main append/publication code has no catch layer: validation and funding
precede I/O; successful sync/stat precede fixed-state publication. Pre-I/O wire or
resource refusal can leave the owner usable. An admitted I/O failure poisons it,
including a stat failure after successful fsync; close/reopen validates survivors.

Keep the create cleanup boundary and its fixed eight-attempt emergency helper.
Only that helper sets the private emergency flag. Ordinary post-link temporary
unlink and EINTR retries spend the normal operation quota. The same correction
applies to the existing journal, local sink and generation owner; the
[regression](../../tests/unit/file_cleanup_quota_test.cpp) checks cap+8, actual
linked bytes, locks and FD/account release. No additional native undo state,
retry framework or ordinary update field is introduced. Codec/prefix/index work
checkpoints and raw best-effort close are specified separately in the guide.

## R2 Session boundaries

The separate [Session](../sql_aggregate_session.md) reuses the genuine native
prepared token as its only rollback owner. Its preparation catch recognizes only
the six explicit semantic Error codes; resource and contract failures keep the
same logged head pending and propagate. A typed checkpoint-preparation catch
poisons the owner when selected-root continuity fails while allowing safe
unselected-candidate cleanup failures to retry. The root-selection catch retains
uncertain authority and rethrows the original failure. These three boundaries
serve distinct obligations; log and delivery add no catch wrapper or undo layer.

Native publication and confirmed-delivery postconditions use the same upper
poison flag. Funding precedes durable Input/decision/sink publication. Publication
allocates no new C++ storage, but native commit/journal/capture teardown can scale
with prepared work, and a new source-position node still needs ordered-map key
comparisons. Nonallocating does not mean constant time.

Recovery scans the actual sink and WAL on open, replays genuine decisions and
checks delivered whole bytes. Its final continuity barriers use stamp/EOF/stamp
for each held file plus a bounded root reread; they do not rescan those histories.
All semantic/output/coverage checks precede either tail repair. This adds no
ordinary source/group runtime field, output queue or generic recovery engine.

## R2 JSONL and CLI boundaries

The [JSONL reader](../sql_aggregate_input.md) sets its reopen latch before
consuming input and clears it after complete validation/funding or clean EOF.
Its decoder adds no catch, retry or native rollback layer. A returned owning
command survives the stream/reader and can be retried after pre-I/O log funding
failure; an uncertain file outcome still requires Session recovery. Logged W and
the pending head's reader continuation determine restart, including after Reject.

The CLI's six fixed-failure translations are presentation work after RAII owners
unwind: Session, file, generation, image, memory and indexed-storage failures keep
their family/resource diagnostics. They do not retry, repair around corruption,
or convert a resource failure into a semantic Reject. A failed report does not
undo a durable decision; the next invocation resumes its actual W/I/C/D.

The existing JSON library may refuse a covered C++ allocation while destroying a
DOM and finish cleanup by its own fallback. Tests require either correct decoded
ownership or a propagated allocation failure, plus exact receiving-account
restoration. This behavior introduces no new reader exception wrapper and does
not establish malloc or whole-process memory accounting.
