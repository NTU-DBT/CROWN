# R2 WAL and group sink files

The [public file API](../include/crown/recovery/sql_aggregate_files.hpp) owns actual
Linux regular files for the [CROWNAG2 records](sql_aggregate_records.md). Each
owner holds one exclusive advisory lock until checked close or destruction.
Factories require an actual [admitted descriptor](sql_aggregate_descriptor.md),
compare its hash with the expected header, and freeze its genuine schema into
the receiving memory account. Another writer must respect the lock; the
containing namespace must be trusted.

These primitives establish durable transport prefixes. The upper
[Session](sql_aggregate_session.md) connects them to native preparation/publication,
selected roots, checkpoint recovery and source positions. The separate [R2 JSONL/CLI path](sql_aggregate_input.md) now connects these primitives through Session. The complete physical [checkpoint](sql_aggregate_checkpoint.md) remains a
separate component.

The source is divided by responsibility:

| Primitive | Usage and implementation |
| --- | --- |
| `WalFile` | [Stage one fixed cursor candidate, sync the supplied frame, then publish its confirmed transport state](../src/recovery/sql_aggregate_wal_file.cpp). The file retains no second pending command. |
| `SinkFile` | [Validate a group epoch, prepay index growth, then sync and publish one offset entry](../src/recovery/sql_aggregate_sink_file.cpp). Duplicates compare the complete actual bytes. |
| Private `Io` | [Bounded POSIX calls, FD lifetime, stamps, prefix reads and explicit tail truncation](../src/recovery/sql_aggregate_file_detail.cpp). It contains no native state, undo records or execution policy. |
| `SinkReceipt` | A fixed observation minted by a healthy, untorn actual sink owner. Copies preserve that observation and retain no file lock. |

## Opening and writing

`create(account, path, descriptor, header, limits)` funds all metadata and the
encoded header before creating a random temporary inode in the same directory.
It locks and syncs that inode, links it to the destination without replacement,
removes the temporary name, syncs the directory and checks the final size.
An existing file or symlink is preserved. Temporary cleanup is bounded; failure
is reported by `temporary_cleanup_failed()`. A process crash may leave a
temporary name for later namespace maintenance.

`open` uses `O_NOFOLLOW`, requires a regular file, acquires the lock, and scans
the whole admitted prefix. It authenticates the length-bearing 148-byte frame
header before allocating the body. After scanning it checks EOF and file stamps,
syncs the file and directory, and rechecks the stamp. Visible complete valid
records left by an uncertain writer can become the newly confirmed prefix.
Open never truncates. The WAL replay callback is private to the receiving session
factory; its effects must stay unpublished until that whole open succeeds.

`append(frame)` borrows one immutable, already funded frame through the call.
It re-inspects the actual bytes under the owner's frozen schema, including
frames encoded elsewhere. Cached `Frame::info()` does not authorize a write.
The caller keeps the owned pending input or output spool alive; neither owner
retains an output queue or another command-byte copy.

All validation, fingerprinting, scratch growth and sink index growth precede
the append I/O. The uncertainty latch is set before the first stamp check.
Only successful write, fsync and final size/stat checking allow publication.
WAL publication moves fixed cursor state; sink publication inserts one reserved
fixed index entry. Neither publication allocates. The latch remains set after
any I/O failure, including a final stat failure after a successful fsync.

After such failure, `requires_reopen()` is true. State, prefix and receipt getters
reject that owner. Checked `close()` is still available and consumes the FD once,
including EINTR; destruction closes best effort. Reopen and validate surviving
bytes before retrying. `FileFailure::outcome()` describes the attempted file
operation; it does not grant native commit or retry authority.

## Frontiers, ordering and duplicate delivery

WAL records have consecutive transport ordinals starting with header zero. Its
fixed cursor tracks W (last logged Input), I (last disposition), C (last Commit),
the one pending input identity and `sink_floor`. A Reject advances I while C
stays unchanged. Logging a later Input records the prior C as the required sink
floor. These are transport facts; the upper Session compares the actual runtime
and sink and enforces W=I and D=C before the next command.

Sink header ordinal is zero. Every group epoch uses its **absolute physical
sequence C as ordinal**, also when `base_sequence>0`. C is contiguous from that
base; input I strictly increases across epochs and can skip rejected commands;
generation never decreases. Successful empty epochs remain whole 255-byte
records. A header-only prefix reports its declared base C and generation/I zero,
meaning no output epoch was observed in that file. It describes a selected
baseline; it does not contain proof of earlier epochs.

`append` returns false only if the existing epoch's complete encoded bytes match
the supplied frame. The implementation reads and compares every byte in bounded
chunks, with stamp checks before and after. A matching digest or sequence alone
cannot accept a retry. `verify` performs this existing-prefix comparison and can
operate through a validated incomplete suffix; it never appends.

`SinkPrefix::content_sha256` is a chained fingerprint, not a raw file hash. The
header fingerprint is its protected prefix checksum at bytes 84–147. For each
epoch, the next fingerprint is SHA256 of the previous 64 ASCII checksum bytes
followed by that epoch's 64 ASCII protected-prefix checksum bytes. Each protected
prefix binds its whole body hash and byte length. A `SinkReceipt` is privately
minted from the actual healthy, untorn owner; editable root/checkpoint DTOs cannot
construct one. A later coordinator must still check its current owner and the
selected root's exact sink identity, sequence, byte count and fingerprint.

## Tail repair boundary

A short first frame is fatal. A complete bad record is fatal even if it follows
a valid prefix. Only a suffix whose available envelope bytes, kind, ordinal and
fixed minimum/exact length are consistent with a possible next record is marked
torn. No suffix is admitted beyond a record or terminal sequence limit. The
incomplete body's unauthenticated remainder is not decoded or retained: at most
the 148-byte envelope plus nine kind/ordinal bytes are needed. EOF/stamp checks
still cover the actual full file size.

`repair_tail()` is explicitly a **low-level caller obligation**: before calling
it, the receiving session must validate all selected root/checkpoint/descriptor
identities, every complete WAL/sink frame, genuine native semantic replay and
output equality, sink coverage, EOF and stamps. The file primitive cannot prove
that semantic barrier. Once authorized by that validation, repair truncates only
the known incomplete suffix, syncs and checks size/stat. It preserves complete
pending Inputs and every complete decision/epoch. Repair I/O failures poison the
owner by the same rule as append. No complete corruption is repairable here.

## Cost, accounting and failure carriers

Factories use the receiving account for owner storage, immutable schema metadata,
frame scratch and sink indexes. A same-account genuine program shares its
immutable metadata; another account gets a funded freeze. Metadata copying is
cold work. WAL append owns no additional frame buffer and uses fixed state.
Sink storage is O(number of admitted epochs); capacity grows geometrically before
I/O. Duplicate comparison uses at most `min(epoch bytes, chunk_bytes)` scratch.
New output encoding and its one spool remain the caller's separate cost.

File limits bound full file bytes, record count, per-record codec grants, path
and chunk sizes, syscall attempts and charged logical work. Work includes
defined codec, prefix-validation, chaining and duplicate-comparison checkpoints.
A failed codec inspection or WAL feed returns no codec work, but earlier charges
remain: prefix checking is prepaid, and a successful sink inspection is charged
before later admission can reject. Cold metadata copying, native replay and CPU
time are outside that counter. Each individual codec call is still bounded by its supplied
grant. Caller retries are not a new end-to-end CPU allowance proof. Every attempt routed through the
bounded dispatcher, including EINTR, spends the operation counter. Best-effort
RAII close and the raw close on a checked-close quota rejection are outside it. Mandatory temporary-name
cleanup has at most eight attempts outside the ordinary operation cap.

`ImageFailure` reports wire/schema/order/codec-grant failures. `FileFailure`
reports fixed stage/fault/outcome/native-error data. Receiving allocation failures
propagate directly. The main append/replay paths have no catch/retry/undo layer;
only bounded EINTR handling and the create cleanup boundary are present. These
files add no field or check to ordinary update/runtime targets.

All durability, ownership, wire and failure rules here are local engineering
contracts. The weighted aggregate context is P1 §7.3, equations (10)–(14), in the
[corrected paper/source map](code_review.md); it does not prove POSIX durability.
The [block usage map](code_specs/README.md), [primitive guide](code_specs/primitives.md)
and [test sources](../tests/unit/sql_aggregate_files_test.cpp) provide the human
inspection route. Actual syscall/crash coverage is in the separate
[fault tests](../tests/unit/sql_aggregate_files_fault_test.cpp).
