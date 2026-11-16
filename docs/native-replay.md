# Native journal reconstruction

`QuerySession::restore_journal` reconstructs a native session from its exact
durable checkpoint and complete journal prefix, then returns it paused with the
exclusive journal writer attached. [Generation selection/rotation](generations.md)
adds a durable root and root-selected recovery over this factory. O05 and the
integrated O04–O06 acceptance are verified within their frozen native/set-session
scope; explicit verified history retirement is available.
The [local epoch sink](local-sink.md) now supplies durable local delivery,
canonical retry, prefix receipts and bounded backpressure. The sink-aware
`restore_journal_with_local_sink` and `restore_generation_with_local_sink`
factories compare the actual durable prefix before retaining only missing output.
Explicit [verified history retirement](history-retirement.md) is implemented.
R2 aggregate retirement, independent catalogue closure and release gates have
separate scopes; see the [ledger](task_ledger.md).

Include `crown/runtime/session_journal.hpp`. Supply the compiled program,
checkpoint path, journal path, `SessionJournalRecoveryOptions` and an owned input
stream for stream sessions. `options.journal.query_id` and `generation` must
identify the expected checkpoint/log pair. Header checks bind the exact checkpoint
image SHA256, program/source/catalog/arithmetic policy and physical/command bases.
The factory rejects stopped, failed or ended baselines, which cannot enable this
writer. File ownership and filesystem assumptions follow
[journal files](journal-files.md); publication ordering follows the
[session writer](session-journal.md).

The receiving runtime, decoded records, native reader/queue state, window state,
file buffers and replay output all use one newly admitted query account. The
saved memory cap applies unless `memory_limit_bytes` explicitly overrides it.
There is no fresh allowance for each input. Source rows are copied directly from
native decoded views into native accounted storage; replay does not convert them
through ordinary owning Row objects. Complete frame validation precedes private
native admission. Every decision must match the actual prepared transition's
physical/metadata kind, physical sequence, accepted command and completion.
Ordered prefix validation additionally binds its input/hash/substep.

Reconstruction publishes each committed native transition only inside the
unexposed receiving session. No owner or output escapes until the complete
prefix, stable file metadata, exact EOF and file/directory synchronization pass.
Complete checksum or semantic corruption rejects without truncating the log.
With the default `repair_torn_tail=true`, only an incomplete later frame is
removed, after native validation and any requested input seek. Set it false to
reject a torn tail without repair. A repair I/O failure can be indeterminate;
release the failed construction and reopen using the same pair.

An uncommitted complete input remains cached in its reader or typed queue. A
partially committed watermark retains every completed expiration step and the
active native command. Subsequent admission finishes that command before consuming
another input. An unfinished window command receives a tentative semantic check
that rolls back without publishing another step. Do not reoffer retained input.
Post-checkpoint EOF, stream failures and later queue closure are not journal
decisions: upstream must reobserve/reoffer those controls. A queue already closed
in the baseline retains that closure.

For stream input the journal carries consumed bytes, decoded records, header state
and CSV permutation, including a cached pending row. The factory validates native
row/domain/profile/source ordering, checkpoint-known CSV mappings and native text
record starts. For a first CSV header it checks possible byte-length bounds from
schema names, optional/required quoting and LF/CRLF. It does not authenticate the
raw header spelling against the external source; the bound journal is trusted
input subject to its checksums and semantic checks.

By default supply the continuation stream at the first unread byte after the
last complete logged input, including a retained uncommitted row. With
`seek_source_from_origin=true`, supply the original seekable stream; recovery
seeks to the reconstructed consumed-byte counter before returning. A bad or
unseekable stream rejects. Seeking is invalid for typed input. Do not seek only
to the last committed row when a later complete input is retained.

`decode_work` bounds cumulative extra record inspection/materialization during
reconstruction; the file cursor retains its independent scan limit.
`source_work` bounds cumulative replay source/value validation, also limited by
`journal.native.source.work` for each input. Work is reserved before variable
UTF8/value/name/CSV visits and copies. Initial checkpoint validation retains its
own native limits. Existing engine/window/source/file/record limits and the shared
heap cap still apply. These are resource contracts, not wall-time or RSS bounds.
Recovery options are copied at entry, so external mutation cannot refill quotas.

With the bare factories, committed replay output is held in an accounted buffer, bounded by
`output_rows` (default65536) and `output_bytes` (default64MiB). The byte limit
includes control storage, actual vector capacity and retained native tuple
allocations; transient allocation peaks also obey the query account. Limit
failure rejects the entire construction. No tentative output is delivered.
By default output covers physical decisions after the checkpoint. The optional
`outputs_after_physical_sequence` suppresses earlier epochs. This caller-supplied
frontier is not a persisted acknowledgment or retirement authority. Sink-aware
recovery rejects it and validates actual stored canonical epochs instead.
Acknowledged output does not consume the replay backlog allowance, so zero
row/byte caps are valid when the sink covers all replayed physical epochs. Only
missing output remains buffered; use whole-epoch local delivery after restore,
with ordinary transfer/discard guarded by the attached sink. Original shared
heap, source/decode/file and cumulative delivery-work limits still apply.
See the [local sink contract](local-sink.md).

For bare recovery, consume with `next_recovered_output()`, which transfers owning native tuples
without allocation, or explicitly `discard_recovered_output()`. Regular output
iteration and new admission reject while the recovery buffer is pending.
Drain/stop/drop discard it according to their existing lifecycle semantics.
After consumption/discard, `start()` resumes normal journaled admission. A
returned tuple remains valid after session destruction under its original
account. Recovery output counts appear in ordinary status/statistics too.

`RecoveredResult::same_identity` compares query_id, generation, physical epoch,
operation and exact native typed tuple values. Ordinal, container iteration order
and layout addresses are excluded; identity does not rely on a hash collision
assumption. Scope it to the bound query/generation and the native set-output
contract. Metadata-only steps emit no rows. This API supplies replay identity,
not a durable external delivery protocol.

`recovery_status()` reports construction records/work/reader counters/pending
sequence as a fixed handoff snapshot. Its output fields track the current buffer;
use live `progress()` and `journal_state()` for subsequent input/log changes.
Native memory, image, file and fixed session-journal failures retain their
categories. On an uncertain live writer failure, drop/destroy that owner before
calling the factory. Checkpoint-file replacement remains blocked while attached.
Direct pairs have no rotation; use the generation APIs for managed rotation.
The local sink's verified durable prefix is available for explicit retirement;
explicit retirement now uses actual verified local delivery, a checkpoint-bound
root fingerprint and durable cleanup intent. A pending intent requires the
sink-aware generation factory; it validates before tail repair and completes
cleanup before exposing an owner. Bare generation recovery rejects it. See
[retirement](history-retirement.md).

See the [verification record](verification/o05-native-replay-2026-11-10.md) for
the accepted source and scoped matrix. Whole-suite/fresh recovery acceptance and
the remaining [Refactor tasks](task_ledger.md) are still open.
