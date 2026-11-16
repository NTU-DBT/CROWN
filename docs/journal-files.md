# Durable journal files

Include `crown/recovery/journal_file.hpp` and use `crown::recovery::journal::File`.
This is the Linux file-storage component of O05. The [session writer](session-journal.md)
connects it to native prepared commit. The [native recovery factory](native-replay.md)
reconstructs the bound query, pending input, source continuation and committed
output with semantic identity. [Generation selection/rotation](generations.md)
durably selects a complete pair under a separate root lock, retaining old pairs.
[Local epoch delivery](local-sink.md) supplies its own transactional result file,
canonical retry and local prefix receipts. Sink-aware restore and explicit
[history retirement](history-retirement.md) are implemented and verified within
the [dated O04–O06 integrated acceptance](verification/o05-o06-native-acceptance-2026-11-10.md).
That 264-test source/configuration matrix is historical evidence; full release
review remains open.

`File::create(account,path,header,limits)` exclusively creates a new journal. It
encodes/validates a complete header, creates a random private sibling with0600
permissions, takes an exclusive advisory flock, writes/syncs the inode, publishes
it using linkat without replacement, unlinks the temporary name and syncs the
parent directory. Existing files and symlinks are never replaced. Success means
the header and final name are durable. Publication errors can leave the complete
final journal present; inspect the outcome and reopen rather than recreate over it.
The caller supplies a trusted containing namespace and keeps the final name stable
while a writer is active. Crashes may leave private orphan temporaries; they are
never selected as the journal automatically.

`File::open(account,path,expected,limits)` opens an existing no-follow regular
file, takes the same nonblocking exclusive flock and validates the full prefix
against the exact expected header. It reads one bounded record at a time and
retains a pending input in its original encoded form. Every variable buffer is
charged to the receiving memory account. It checks stable inode/size/timestamps
and exact EOF, then syncs the inode and parent directory before returning. This
adopts the complete visible prefix as durable, including a complete commit that
an earlier writer might have reported as unknown. A second cooperating writer
fails with `busy`, including through another hard link to that inode.

`append(full_record)` first copies the frame into account-funded storage and
validates the next ordinal, binding, command/physical/substep sequence and total
limits through the private cursor. It checks the file has not changed, loops
short/EINTR pwrite calls at the validated end and fsyncs before success. It never
rescans old records for an append. An allocation/validation failure leaves disk
and cursor unchanged, so the same owner can retry. Once cursor validation has
advanced, any subsequent failure poisons the owner; close and reopen before more
appends. The failure may occur after a complete commit was physically written.

`state()` reports the admitted complete prefix and pending input frame. Reports
cannot import/reset private allowances. Frame views borrow the file owner until
another operation, move or destruction. Rvalue owners cannot return a state view;
the owner is noncopyable and moves invalidate the source. On reopen, an incomplete
later tail is reported, but no append is allowed until explicit `repair_tail()`.
Repair truncates only bytes after the last complete record and fsyncs. Every
complete pending input and physical window substep is retained. An incomplete
mandatory header, complete corruption or incompatible binding rejects without
modifying the file. Repair does not retire any committed history. A checkpoint
marker alone never authorizes truncation of committed records.

`FileFailure` has fixed fault/stage/outcome/native errno/temporary-cleanup metadata
and a fixed diagnostic. Outcomes describe the attempted operation: unchanged,
unknown or durable. Unknown requires recovery and never authorizes blind retry.
Checked `close()` reports errors; destruction closes best effort. Linux close is
called once even after EINTR. Ordinary attempts, including interrupted calls,
consume the operation budget; mandatory temporary cleanup has at most8 attempts
outside it. Limits also cover whole-file and per-record bytes, codec validation
work/records, path/chunk sizes and actual receiving-account heap bytes. Codec
work counts validator visits; bounded framing copies and kernel I/O have their
own byte/attempt bounds. No wall-time or resident-memory claim is made.

Durability assumes a local Linux filesystem honoring fsync and linkat, an
existing trusted parent, cooperating single-writer ownership and a stable journal
name. The crash tests exit processes before/after actual syscalls; they do not
simulate power loss. This file component does not certify externally managed
sinks. The separate [local epoch delivery](local-sink.md) protocol records its
own verified persistence and acknowledgement scope.
