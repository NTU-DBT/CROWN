# Checkpoint and restore implementation

O04 is acceptance-verified. `QuerySession::checkpoint_image` captures a complete
pointer-free CROWNSI1 session envelope; `restore_image` validates both envelope
and runtime checksums and restores native source/options/window/control state
in one receiving account. The separate `SessionCheckpoint` remains an in-memory
C++ state API. Atomic durable file publication and bounded loading are implemented
below. On the frozen O04 acceptance snapshot, all 240 then-registered tests passed
the four native configurations and a fresh source-only Release build; see the [full acceptance record](verification/o04-native-acceptance-2026-11-10.md).

## Native runtime component

`DeltaRuntime::checkpoint_image(ImageLimits)` returns an owning `EncodedImage`.
Capture requires no private epoch, active result cursor or unread committed
output. The image stores complete physical base rows, sufficient to rebuild
occurrence adapters, support/derivation counters, indices and Delta live state.
It contains no pointer, table handle or allocator address.

`DeltaRuntime::restore_image(program, bytes, options, build, limits)` constructs
an unpublished new runtime. The physical/source hashes, catalog version,
arithmetic identity and semantic runtime policy must match. The requested mode
must equal the captured actual mode, including a mode changed after creation.
The receiving query's byte ceiling can differ. Every decoded row, executable
metadata, temporary and rebuilt runtime allocation uses that receiving account.
Any failure releases the unpublished result; an existing source runtime remains
valid. Releasing or retaining an image does not retain the original runtime graph.

Restore reruns native row/domain, enforced constraint and duplicate membership
validation before publication. Both direct and insertion-replay initialization
use the existing cumulative build grant, including live bootstrap. Diagnostic
observation/workload histories, allocation history and owner IDs start fresh;
these are separate from restored logical state and sequence.

## Runtime image format 1

The eight-byte magic is `CROWNRI1`. The header has little-endian format/version
`u16(1)`, flags `u16(0)`, payload length `u64` and64 lowercase ASCII SHA256 bytes,
for84 bytes total. The checksum covers the complete payload. It provides
corruption detection; callers remain responsible for trusted artifact selection.

The payload contains64-byte physical and source hashes, catalog version and
committed epoch (`u64`), arithmetic `u16(1)` for exact-nonnull-v1,26 little-endian
policy words and a `u64` table count. Tables appear in contiguous catalog-ID
order, each with ID/row count, then rows with a field count. Scalar tags are
0:int64 bits,1:raw byte string with `u64` length,2:Boolean byte0/1,3:signed32-bit
epoch day and4:canonical exact decimal with a one-byte text length. Empty rows
and empty tables are retained. Source capture uses the native canonical row order.

The policy words record support work presence/value, support count limit,
propagation order, transition capture, observation mode/capacity/sampling/timing,
a reserved zero word for the configurable receiving memory cap, physical work
presence/value and derivation limit, actual Delta mode, result view, live policy,
requested completion, Delta/cursor/epoch-view work presence/value and spool
row/byte limits. Source/plan identity binds the immutable catalog and backend.
The codec treats these words as bound metadata; runtime restore derives and
matches their values from the supplied runtime options before native admission.
Unknown versions/flags/arithmetic and mismatched policy/bindings are rejected.
The complete session envelope has its own version and compatibility rules below.

## Resource and validation contract

`ImageLimits` bounds encoded bytes, serialized byte work, tables, total rows,
fields per row and string/decimal bytes. Encode preflights the complete image
and its remaining byte work before allocating one final buffer. Decode checks
header, checksum, binding, all counts and exact scalar encodings before output
allocation, then deep-copies validated rows. Trailing bytes and noncanonical
scalars are rejected. Neither validation nor failure carries an owning error string.

Byte work counts serialized visits during preflight, materialization and
checksum. Native source snapshot/sort and runtime admission/rebuild retain their
own storage/build grants and comparison costs. These finite units do not claim
a CPU-time or RSS bound. All retained and temporary requests also consume the
query account. Held images appear under recovery owner0 in memory reports.

## Evidence and remaining acceptance

The independent Python `struct`/`hashlib` fixture is
`tests/recovery/runtime-image-v1.hex`. The codec test checks every truncation and
single-byte bit flip, checksum-valid malformed values/counts, exact and one-under
byte/work/query caps, allocation faults and retained output lifetime. Runtime
tests compare source/support/live state and subsequent projected deltas across
both storage backends, maintenance/delta policies and both initialization methods.
They also exercise quiescence, repeated capture, original-account allocation,
restore OOM and semantic rejection. Current receipts use
`build/verification/o04-native-checkpoint-`; see [the handoff](handoff.md) for the
actual completed matrix scope.
The [native component record](verification/o04-native-checkpoint-2026-11-10.md)
records37/37 selected tests in each of four configurations and the public-only
production-library controls. Delta-set checks leave replay ordering/identity
to the later recovery/delivery protocol.

O04 full/fresh-source acceptance is complete. Binary session/native owner
composition, quiescence, corruption checks, version1 compatibility rules and atomic
durable files are implemented below. O05 adds WAL and crash replay;
O06 adds durable delivery. The full Refactor.md goal remains active.


## Native source and window state components

Session composition uses `io::QueueCheckpoint`, `io::ReaderCheckpoint`
and `runtime::WindowCheckpoint`. Queue/reader snapshots own accepted source
positions; reader state includes its original byte/record counters, CSV header
permutation, options and EOF. A queue must be empty and a reader must have no
unacknowledged cached record. Reader restore accepts a continuation at the next
unread byte; its counters retain the original source origin. Custom metadata
limits are explicit on both capture and restore. Immutable option snapshots
retain native storage and receiving imports clone it under the new query account.

Window state retains count identity after its original label expires, all label
payloads/timestamps, independent command/physical/watermark/last-label progress,
options capacity and terminal state. Restore validates catalog, shape/domain,
unique row counts, label references, deadlines and exact multiplicity, then
rebuilds native FIFO/expiration directories. A prepared step or an active
multi-step watermark rejects capture, including between physical commits.

The runtime image restore now retains one indexed admission grant through
program/source/support/live rebuild. A direct counter regression distinguishes
the repaired path from the preserved predecessor. Source6 passes44 selected
tests in each of GCC Debug/Release, Clang18 and ASan+UBSan/leaks. The
[native state record](verification/o04-session-state-native-2026-11-10.md) retains
the exact scope, negative regression and allocation-failure evidence.
These native components are covered by the full verified O04 session acceptance.


## Complete native QuerySession checkpoint state

`QuerySession::checkpoint_state(SessionCheckpointLimits)` captures a move-only
`SessionCheckpoint` under the creator-thread/reentry guard. Created, running,
paused and stopped sessions are supported. Capture requires no pending epoch,
unread output, queued event, cached reader record, failed active reader or active
window command. A multi-step watermark remains busy between physical commits.
Stopping closes the source and permits capture of its accepted prefix and failure
flag when window state is quiescent. A stopped unfinished watermark retains an
active command tombstone and still rejects capture without changing that state.
Dropped sessions reject capture.

The native state includes runtime image bytes, actual Delta policy, source kind,
control state, independent committed/source/window sequences, EOF/failure flags,
native input policies and positions, queue closure/limits, reader byte/record
origin and CSV mapping, window labels/count identities/watermark, snapshot limits
and workload configuration. Diagnostic counters/history, ownership identities,
declared benchmark labels and allocation history restart on restore.

`QuerySession::restore_state(program, state, options, continuation)` builds an
unpublished new session in one receiving account. The default byte ceiling is the
captured Delta ceiling; `options.memory_limit_bytes` explicitly overrides it.
All native source/window options, progress, rows, executable metadata and rebuilt
state use that account. One indexed admission grant covers physical/support/live
rebuild and workload configuration. Existing sources remain unchanged on failure.

An active stream needs a caller-owned continuation positioned at the next unread
byte, including an EOF continuation (which is not read). Original byte/record
counters and CSV header mapping are retained. Stopped streams need no continuation;
typed/stopped states reject an unused continuation. Whole-session streams always
start at sequence zero: saved read records must equal accepted source sequence at
a quiescent checkpoint, preventing a malformed counter from resetting a record
limit. Accepted distinct source positions cannot outnumber accepted records.

Restore checks source/runtime sequence agreement, source kind/policies and window
command/physical progress. Managed runtime base rows must exactly match distinct
window count rows, using native receiving-account scratch before admission. An
internally valid window state with different managed rows rejects; unmanaged
initialized tables remain intact. Window validation independently reconstructs
FIFO/expiration indices and validates labels, counts, references and deadlines.

Image/source/window metadata limits and query memory caps remain independent.
Matching work counts native directory/set/field visits; scalar byte comparisons
are additional costs. These abstract work units do not claim a CPU-time bound.
Capture preflights stopped input options and progress before cloning state.

`SessionCheckpoint` is native in-memory state. `recovery::SessionImage` is the
complete serialized session artifact described below. Atomic durable publication
uses that artifact. Complete O04 acceptance covers these components and the file
API. WAL/replay and durable delivery follow in O05/O06.

The [native session verification record](verification/o04-session-checkpoint-native-2026-11-10.md)
records48 selected tests in four configurations, the unchanged production-library
counter-reset control, native allocation/fault coverage and remaining scope.


## Complete binary session API

Include `crown/recovery/session_image.hpp`. `QuerySession::checkpoint_image()`
returns owning account-funded bytes, a fixed manifest and admission statistics.
The limits overload accepts `SessionCheckpointLimits` and `SessionImageLimits`.
The writer guard spans both native capture and encoding. The low-level encoder
also rejects caller-mutated native metadata that contradicts its structural
inspector; it does not replace schema/program admission.

`QuerySession::restore_image(program, bytes, continuation)` uses the captured
query ceiling; the options overload accepts `SessionRestoreOptions`, optional
`SessionImageLimits` and a continuation. The byte view must remain immutable for
the synchronous call. Complete structure, checksums, fixed policies, accepted
positions and metadata limits are validated before receiving materialization.
All temporary native maps, texts, window rows and rebuilt executable state use
one receiving account. Runtime bytes borrow input only until native restore ends;
all retained values own their bytes. Native runtime admission retains its one
indexed grant and its own storage/build/domain/constraint validation.

`inspect_session_image` allocates nothing and returns fixed metadata. Its manifest
is descriptive, not authority to install an incompatible program. Captured queue/
reader/window `work` words are descriptive measurements, never budget authority;
actual byte, metadata, storage/build and memory accounting is recomputed. Receiving
memory overrides affect the new query's actual options. Diagnostic histories,
allocation history and ownership IDs restart.

The [binary session evidence](verification/o04-session-image-native-2026-11-10.md)
records50 selected tests in four modes, the independent1067-byte fixture and the
public-only encoder consistency control. No file is published by these methods.

## CROWNSI1 session envelope format 1

All numbers are little endian. Booleans and optional presence tags are one byte,
0 or1 only. A present optional u64 adds its eight-byte value; an absent one adds
no payload. Host sizes/IDs are u64 and reject host overflow. Metadata text is a
u64 length plus exact UTF-8 bytes; source names are nonempty and exclude NUL.
Row strings use the native raw-byte scalar codec and do not normalize text.

The84-byte header contains magic CROWNSI1, u16 version1, u16 flags0, u64 payload
length and64 lowercase ASCII SHA256 bytes over the complete payload. Nested
CROWNRI1/version1 must also validate its own checksum/arithmetic/bindings.
Unknown versions, flags, scalar tags and enum values reject. There is no implicit
migration or forward skipping. Checksums detect corruption; artifact selection
and a matching immutable CompiledProgram remain caller responsibilities.

Payload order:

1. Native-state version u32; session state, input kind, input_failed and EOF u8;
   committed physical sequence u64.
2. The26 bound runtime policy words, then the captured query memory ceiling u64.
   Policy word10 remains canonical zero; receiving memory can be overridden.
3. Snapshot rows/bytes u64 and optional cursor work; workload mode u8, then
   max_cells/period/offset/detail_budget u64.
4. Input format u8; five input size limits u64; optional total bytes/records;
   optional table; delimiter/header/CSV operation u8; sorted token map count and
   text/table pairs; optional null spelling/source text; byte-offset origin u64.
5. Optional queue limits (batches/events/bytes u64).
6. Source discriminant u8 (reader0, queue1, stopped progress2); accepted sequence
   and sorted unique position count u64; each position is name text plus offset.
   Reader adds bytes/records u64, header-read/ended u8, CSV field count/list u64,
   catalog SHA64 and capture work u64. Queue adds mode/closed u8, catalog SHA64
   and capture work u64. Its limits and reader options equal the outer policies
   and are implicit; stopped progress has no extra payload.
7. Optional window: managed ID count/capacity/list u64; width u64/FIFO u8;
   max-labels/max-accounted-bytes/command-work u64; completed command/physical/
   watermark/last-label u64; catalog SHA64; last-command/capture work u64;
   stopped u8. Count rows follow (count u64, then id/table/row/refcount); labels
   follow (count u64, then label/table/row/timestamp/deadline/count-id). Row field
   counts are u64; scalar tags/payloads match CROWNRI1 exactly. Active commands
   and their step counters are forbidden by quiescence, so are implicit absent/0.
   FIFO values 0/1 retain global/per-table label order; 2/3 select global/per-table
   physical-row lifetime order; 4 is unrestricted baseline order. The byte position/layout is unchanged; older
   readers reject 2/3. Restore preserves count birth IDs rather than deriving
   lifetime order from surviving labels. See [update patterns](update_patterns.md).
8. State version 2 only: source hash SHA64, source table/rule counts u64,
   sorted rules (table u64, insertion-only u8, raw FIFO scope u64), physical and
   command origins u64, violation-present u8; if present, kind u8 and
   table/command/label u64. Size is 97+17R+(violation?25:0) bytes. Version 1
   omits the entire section. Undeclared captures default to version 1; declared
   captures require version 2. Parse/import/copy grants and the receiving account
   cap are distinct. Restored prefix metadata assumes the existing trusted local
   checkpoint boundary and is reported explicitly, not authenticated as history.
   See [declared recovery](update_patterns.md#restore-the-declared-contract).
9. Runtime-component byte length u64, then the exact CROWNRI1 blob. No trailing
   bytes are permitted. Runtime manifest/statistics are derived, not pointer data.

Envelope byte/work/row/scalar limits are independent of native runtime/source/
window/matching and receiving account caps. Envelope row limits count window
row payloads; runtime rows retain their embedded component limits. Work admission
conservatively reserves validation/materialization and nested image inspection;
native metadata/storage/build work has separate documented units. Window managed
capacity is explicit and bounded before allocation, preserving reserved capacity.

Created/running/paused/stopped states are supported only at the quiescent barrier.
Queued/cached/failed active input, private work, unread output and active windows
reject. Stopping a partial watermark retains an active tombstone and still
rejects. Active streams require a next-unread-byte continuation (even EOF); typed
and stopped states reject unused continuations. Reader records equal accepted
sequence; distinct accepted sources cannot outnumber it. Window and base rows,
command/physical sequences, references, catalog/schema and program policies are
validated again during native admission. Histories/owner IDs reset; logical
state/configuration remain. The file API below publishes this complete envelope.


## Atomic durable checkpoint files

Include `crown/recovery/session_file.hpp`. On the supported Linux local-file
platform, `QuerySession::checkpoint_file(path)` captures and publishes a complete
CROWNSI1 artifact. Its overload accepts native checkpoint limits and
`CheckpointFileLimits`. The session guard spans capture, validation and I/O;
queued/private/output/active-window barriers retain their existing behavior.
No event is acknowledged or runtime state advanced by saving a checkpoint.

Publication opens and anchors the existing parent directory, creates an exclusive
random sibling file with permissions of at most `0600` (subject to umask), writes every
byte, fsyncs and checks its close, renames it over the final entry atomically,
then fsyncs and checks the directory close. The temporary basename must differ
from the destination. Private names are created with O_EXCL/O_NOFOLLOW; a
preexisting private name is never overwritten. The final entry is replaced,
not followed, including a leaf symlink. Parent resolution may traverse symlinks
before the directory is anchored. The parent must be trusted against external
edits to the writer's temporary entries; arbitrary competing namespace mutation
is outside this single-writer publication contract.

`PublishedCheckpoint` reports the actual fixed manifest, byte count, admitted I/O
operations and durable outcome. `FileFailure` carries fixed fault/stage/errno,
publication state and `temporary_cleanup_failed`, without owning error strings:

| State | Meaning |
| --- | --- |
| not_published | Publication was not attempted; the prior target is unchanged. |
| unknown | Rename was attempted and returned an error; inspect/reconcile the target before assuming old or new. |
| published_unsynced | Rename succeeded; the complete new target is visible, but directory durability is unconfirmed. |
| durable | File and parent synchronization succeeded; even a subsequent checked directory-close error does not undo publication. |

Failures never claim rollback after rename. Before publication, owned temporary
fds are closed and private names are removed best-effort. Cleanup has at most
eight attempts outside ordinary I/O quota; inability to confirm
removal sets the cleanup flag. Process termination may leave private temporaries;
loading the named checkpoint never selects those names automatically. A caller
may reconcile/delete them in its trusted directory. The implementation does not
truncate WAL or make output delivery/deduplication claims.

`QuerySession::restore_file(program, path, ...)` opens the final entry with
O_NOFOLLOW/O_NONBLOCK, requires a regular file and caps its size before allocation.
A fixed 316-byte versioned preamble is read on the stack to obtain the captured
memory ceiling (or receiving override); it is not trusted until full checksum
validation. One receiving account owns the complete file buffer and all decoded/
rebuilt native state. The buffer is released before the query returns. There is
no intermediate unaccounted byte copy or second receiving account. A matching
immutable CompiledProgram remains required, and active streams require their
next-unread-byte continuation. File loading retains one indexed runtime grant.

Read loops handle short transfers/EINTR, require the expected byte count and EOF,
and compare size/inode/device/modification metadata before/after. Complete nested
checksums and native program/schema/window validation then run as for in-memory
restore. Fds are closed on every failed allocation/parse/I/O path. Linux close
errors do not retry the released descriptor. Changing/truncated/corrupt files,
leaf symlinks and special files reject. Atomic replacement while an old fd is
open permits reading the old complete inode; external in-place mutation is not
accepted as a consistent checkpoint.

`CheckpointFileLimits` bounds path bytes (default 4095, stack capacity 4096),
nonzero transfer chunks (default 1 MiB, at most SSIZE_MAX), I/O operations and image
limits. Decode/native metadata/build/matching and the query ceiling remain
independent. The fixed preamble, syscall retries and copying are additional to
codec byte-work units. No CPU-time, wall-clock or RSS bound is claimed.

Durability follows the local filesystem's successful fsync guarantees and normal
storage assumptions. The tests inject actual syscall boundaries and process
termination; they do not simulate power loss or hardware faults.

The [durable-file verification record](verification/o04-session-files-native-2026-11-10.md)
records the 53-test scope in four configurations, production allocation sweeps,
syscall faults, process exits and the preserved namespace regression control.
The frozen O04 acceptance passed all 240 then-registered tests in GCC Debug/Release,
Clang18 Debug, ASan+UBSan/leaks and clean source-only Release. Supplemental public
controls independently alter source SHA and catalog version, reseal both checksums
and verify binding rejection in every configuration. The
[full verification record](verification/o04-native-acceptance-2026-11-10.md) binds the
actual binaries, flags, source inputs and archived terminal stdout.

Integrated O04–O06 acceptance is verified: all 264 registered tests pass Debug,
Release, Clang18, ASan+UBSan/leaks and clean source-only Release with unchanged
predecessor definitions. See the [complete record](verification/o05-o06-native-acceptance-2026-11-10.md)
for requirement mapping, whole native pipeline/crash/resource evidence and limits.
