# Durable SQL aggregate session

The [Session API](../include/crown/recovery/sql_aggregate_session.hpp) connects one
genuine original-SQL aggregate runtime to its selected checkpoint, WAL and group
sink. It owns the actual locks and state; editable metadata and decoded records
cannot authorize native publication. Calls and borrowed views require external
serialization on one writer thread.

The implementation has three responsibilities:

| Source | Usage |
| --- | --- |
| [Public API](../include/crown/recovery/sql_aggregate_session.hpp) | Factories, limits, observations and the four explicit commands. |
| [Private owner](../src/recovery/sql_aggregate_session_detail.hpp) | Receiving account, genuine runtime/descriptor, source positions, file owners, one pending head and one output frame. Destruction releases their storage and locks. |
| [Live operations](../src/recovery/sql_aggregate_session.cpp) | Own/fund Input, prepare the existing native token, durably decide, publish, deliver and rotate checkpoints. |
| [Cold recovery](../src/recovery/sql_aggregate_session_replay.cpp) | Restore the selected genuine physical image, replay actual decisions, compare actual sink bytes, validate the complete barrier, then repair admissible tails. |

The aggregate semantics come from the [composed runtime](sql_aggregate_runtime.md),
[physical source image](sql_source_images.md),
[checkpoint](sql_aggregate_checkpoint.md) and [record format](sql_aggregate_records.md).
The [file primitives](sql_aggregate_files.md) specify their own POSIX assumptions.
The transaction/recovery requirements are local engineering contracts in
[Refactor.md §8.3 and W06](../Refactor.md), with weighted context mapped in
[the paper/source review](code_review.md). No paper theorem establishes fsync,
rollback allocation, SQL semantics or these recovery bounds.

## State and command usage

`SessionState` reports these separate frontiers. W is an Input's command
sequence; its WAL frame ordinal is a different transport position.

| Frontier | Meaning | Advances at |
| --- | --- | --- |
| W, `logged` | Last fully confirmed logged Input | Input write/fsync/final stat |
| I, `disposed` | Last confirmed Commit or semantic Reject | Decision sync followed by prepaid progress publication |
| C, `committed` | Native atomic-batch sequence | Commit sync followed by publication of that same prepared token |
| D, `delivered` | Actual confirmed sink epoch | Whole canonical frame write/fsync/final stat |

`create_into` accepts a genuine bound `SqlAggregateProgram`, checked source tree,
physical options and normal runtime options with `capture_changes=true`. Supply
hexadecimal query/sink identities and distinct trusted root/sink paths. The factory
creates a genuine descriptor, actual sink, complete initial physical checkpoint,
matching WAL and v3 selected root. Existing destinations are preserved. Failure
can leave unselected candidates or a newly created sink; creation does not erase
those files or turn them into a successful session. Use `recover_into` for an
already selected root.

Factories borrow `SessionLimits` through a const reference only for the call.
That caller-owned DTO can contain ordinary compiler parameter vectors/strings;
the session keeps only the fixed checkpoint, capture, WAL/sink, history and replay
bounds needed by its operations. Cold admission/rebuild options are not retained,
and GenerationOwner already owns its fixed generation limits. The caller may
change or destroy its configuration after a successful factory return.

`log(InputView)` requires W=I, D=C and no pending head/output. Its command sequence
must be I+1. Replacements borrow complete original physical rows only through
the call. They carry exact before/after weights and can form the existing native
net batch; this is not an ordered intermediate event stream. Input encoding and
source-position node funding finish before Input I/O. Successful log owns all
rows, TEXT and source names, so the caller may release its buffers immediately.

An optional existing source name must advance to a strictly larger offset; a
new name spends the declared source-count/name-byte limits. An optional reader
position must advance bytes and increase its prior record count by exactly one,
with records no greater than the new I. Omitting reader metadata retains its
previous position. `logged_reader_position()` includes a pending Input's reader
position; `reader_position()` and `progress()` expose only disposed progress.

`decide()` attempts exactly the owned logged head through the existing genuine
`prepare_batch` token. It constructs the whole canonical group frame and Commit
identity before decision I/O. After confirmed Commit sync, it commits that same
token, publishes prepaid source/reader progress, advances I/C and retains one
output frame. Publication needs no new C++ allocation. A successful empty/no-op
batch still advances C and retains a complete empty group epoch.

Only the explicit native weight-mismatch, source-overflow, enforced UNIQUE/FK,
aggregate-overflow and annotation-overflow diagnostics become a durable Reject.
Reject advances I/source/reader progress while C/D remain unchanged. Memory, work,
binding, unsupported-operation and other contract failures propagate; they have
no Reject tag. A healthy session retains the same pending head for `decide()`
retry, with native rollback owned solely by the original prepared token. Do not
log a second Input for that command.

`deliver()` appends the retained canonical frame to the actual sink, obtains its
genuine receipt and releases the frame only after confirmed D=C. It returns false
when no output exists. The sink's duplicate path compares every actual byte.
No later Input can bypass a retained output. `output()` is a borrow valid only
while that unmoved owner retains the frame. A pending-input borrow ends when
`decide()` consumes the head; progress/descriptor borrows require their live
owner and serialized access across mutations.

`checkpoint()` requires W=I and D=C with no head/spool. It captures the complete
physical source and disposed source/reader progress with the actual sink anchor,
then syncs the next descriptor, checkpoint and matching empty WAL. Only afterward
does it select the next root. It keeps all selected history from generation one;
`history_generations` is checked against the durable root and cannot be refilled
by reopening. R2 retirement is a separate unfinished operation.

## Recovery and failure boundaries

`recover_into` reads the actual v3 root under its stable lock. It requires a
descriptor hash, delivery anchor, C<=I, first generation one, an admitted history
count and no R1 retirement intent. It rebinds the genuine descriptor, releases
that admission's temporary C0 runtime, and builds the actual native state from
the complete selected physical checkpoint in the receiving account. It opens
the actual sink before WAL replay and compares the checkpoint's exact prefix
anchor.

Each complete Input is decoded, owned and has its progress publication prepaid.
A persisted decision runs that Input through the genuine native factory; a final
undecided Input stays unprepared until `decide()`. A Reject must reproduce the
exact semantic reason. A Commit must
reproduce the whole canonical output size/hash. Already delivered output is
verified against the actual sink's full bytes. A later Input proves the prior C
was delivered; recovery refuses a missing earlier epoch, a sink ahead of genuine
replay or a pending Input whose prior output was not delivered. At most the final
committed epoch can remain as one missing output spool.

Only after complete frame validation, native replay, decision/output agreement,
sink coverage, EOF/stamp checks and selected-root continuity does recovery repair
an admissible incomplete suffix. It validates files/root again afterward before
returning the owner. Complete corruption or semantic disagreement aborts before
either truncate; complete pending Inputs remain pending. Set `repair_torn_tail`
false to refuse torn suffixes without truncating them.

`requires_reopen()` is the one observation allowed on an uncertain/moved owner.
After an admitted WAL/sink I/O failure or uncertain root selection, release the
owner and reopen actual surviving files. Authority getters reject the poisoned
owner. A failure validating the selected root also poisons it. Failure deleting
or syncing only an unselected next candidate can leave the old selection usable
for checkpoint retry. Before-I/O validation/resource refusal can leave a healthy
pending head or spool; inspect `requires_reopen()` before retrying.

## Resource and performance scope

The session retains one genuine mutable database, one pending decoded Input and
one committed output frame. It adds no shadow database, output queue, second undo
journal, generic callback engine or per-row exception wrapper. Native preparation
and rollback reuse the existing runtime. Progress nodes, output storage and file
index growth are funded before their corresponding durable publication.

Normal source/native/group/index options, including disabled normal caps, remain
exactly those admitted in the descriptor. Cold rebuild, descriptor/checkpoint
admission, capture, WAL/sink scans and generation I/O have separate host limits.
`replay_commands` bounds Inputs in the selected WAL; `replay_codec_work` is one
cumulative allowance for Input decoding, canonical output encoding and full-output
hash byte visits across that replay. File scan/duplicate work is charged by the
separate file owners. These counters are not one total-recovery CPU budget.

`ReplayStatistics` exposes replayed Input count and that codec allowance usage.
Native/group/source totals observe successful replayed Commit preparations;
semantic-error attempts have no successful native epoch metrics to return. They
do not impose a new preemptive native replay grant. Reopen does not change normal
operational policy or provide a wall-clock bound. Checkpoints explicitly capture
and rebuild complete physical source bags; sink open retains a bounded offset
index proportional to its admitted epochs. These operations have whole-image or
history costs, separate from ordinary update work.

The separate [JSONL reader and CLI](sql_aggregate_input.md) now provide source
resumption through this API, including pending Input reader continuation and
committed-spool delivery. Checked varying-integer arguments now have
[native/recovery evidence](verification/human-inspection-v32-2026-11-13.md).
The [V33 requirement audit](verification/human-inspection-v33-2026-11-13.md)
verifies W06 within this bounded SQL/native/local-sink contract. The actual
interrupted mixed self-join matrix checks both backends, semantic Rejects,
checkpoint selection, missing output and torn suffix recovery. Healthy live
owners and every injected survivor are checked with a valid next update.
Actual process exits occur around observed persistence syscalls; equivalence
during private RAM preparation/publication follows from the inspected source
ordering, rather than an exit after every alias instruction. R2 history
retirement, broader packaging and release acceptance remain open.
