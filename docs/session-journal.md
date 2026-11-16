# Session journal writer

This component connects the maintained journal file to
QuerySession's native input/prepared commit barriers. The [native recovery
factory](native-replay.md) reconstructs this checkpoint/log pair and retains
pending input, partial windows, source continuation and bounded committed output.
[Generation selection/rotation](generations.md) publishes complete pairs before
switching a locked durable root. [Local epoch delivery](local-sink.md) adds
durable canonical output and backpressure over this writer. Sink-aware restore
and explicit [history retirement](history-retirement.md) are implemented. The
[O04–O06 integrated acceptance](verification/o05-o06-native-acceptance-2026-11-10.md)
records their frozen native/source scope; later changes have their own verification.
Whole-current-suite and release acceptance remain separate gates.

Include `crown/runtime/session_journal.hpp`. Configure SessionJournalOptions with
a 32-byte lowercase hexadecimal query_id and a positive generation. First publish
a quiescent checkpoint through the existing checkpoint_file API, then call
`enable_journal(checkpoint_path,journal_path,options)` while the session still has
that exact state. The existing checkpoint must pass checked regular-file loading
and match the complete current encoded session envelope. The journal header binds
its SHA256, runtime/program/source/catalog/policy binding, physical/accepted input
bases and query/generation identity. The new journal is created exclusively; no
existing entry is replaced. Captured/loaded/encoded bytes use the original query
account. Created or paused sessions may enable the writer; stopped/dropped,
failed/ended, busy or already-enabled sessions reject it.

Input ordering is native validation, durable logical input frame, then physical
engine begin. For windows, semantic preparation validates and allocates private
nodes before log admission; its unpublished Prepared token rolls back on failure.
The complete window command is logged once, including label/timestamp/row or
watermark, and the reader/queue retains its immutable head until completion.
Retries and later watermark substeps reuse that input record. Stream input also
records the decoder's consumed bytes/decoded records/header bit/CSV permutation
from a nonallocating borrowed decoder_position() view. That includes a cached,
unacknowledged row, which the quiescent reader checkpoint cannot capture.

A physical commit first requires the existing prepared barrier. It writes/syncs
a decision bound to input ordinal/body hash and the next substep, then executes
the native nonallocating commit, publishes the prepared window state and
nonthrowingly acknowledges the source. Public output remains inaccessible during
private work and appears only after publication. Metadata-only steps follow the
same durable decision ordering while leaving physical sequence unchanged.

A watermark can expire one of several labels for the same row without producing
a physical update. Such non-final metadata steps are valid commits: physical and
completed-command counters remain unchanged, substep advances and the same input
remains pending. Only the last step acknowledges the command. Incomplete steps
are restricted to window watermarks; physical/stream metadata and incomplete
insertion/withdrawal commands reject in prefix validation. The version1 wire
layout and all seven existing golden records are unchanged; this corrects the
pre-release semantic rule that incorrectly required every metadata step to
complete. Older prefix implementations reject this newly supported case.

`drain()` splits internal preparation from publication when journaling is enabled,
syncs the decision and then commits/discards the current output. It cannot bypass
the writer, and paused admission remains paused. Unattached sessions retain their
previous behavior.

Allocation/codec failures before a decision roll back private engine/window work
and retain cached input and any durable input frame for retry. A journal file
failure marks recovery_required, rolls back private work and blocks further
admission/step/commit/drain/output/snapshot/checkpoint publication. An unknown
append may already contain the complete decision: destroy/drop the old owner,
reopen/validate the surviving prefix and reconstruct native state before resuming.
Do not retry the poisoned writer. After releasing it, use the native
restore_journal factory with the exact baseline and expected generation.

`journal_state()` is fixed metadata about the last confirmed durable prefix. With
recovery_required it is a lower bound, not authority to resume. New session
journal failures carry a fixed fault/diagnostic; native memory/file/codec errors
retain their categories. Explicit drop releases the journal descriptor, lock and
funded file buffers; repeated drop/destruction does not close it twice. A stopped
session retains its writer until drop/destruction. Destruction/terminal cleanup
close best effort under the existing File contract; append success requires fsync.

The session checkpoint_file API rejects while the writer is attached, protecting
the active baseline/journal pair from library replacement. Keep their containing
namespace and names stable. Direct pairs have no detach/rotation API; the
generation APIs provide managed rotation while retaining historical pairs.
Exported checkpoint objects/images and diagnostics do not authorize retirement.
Verified local sink receipts describe durable output coverage. Explicit
[retirement](history-retirement.md) additionally requires private native verification,
a checkpoint-bound root anchor and durable cleanup intent before deletion.

Limits retain the file/record/validation/source/window/native resource contracts
and actual shared query heap budget; this is not a wall-time/RSS claim. Durability
inherits the local Linux64 filesystem/fsync/trusted-directory assumptions from
[journal files](journal-files.md). Process exits in tests are syscall-boundary
crashes, not power-loss simulation. The [record contract](journal.md) describes
the framed prefix; O06 will supply audited durable output delivery.
