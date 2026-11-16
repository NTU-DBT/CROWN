# O04 durable session file scope — 10 November 2026

O04 remains in progress. Atomic durable publication and bounded file loading are
implemented; full registered-suite and fresh-source acceptance remain open.
This record extends the [complete binary session scope](o04-session-image-native-2026-11-10.md)
and [contract](../checkpoints.md). Work is uncommitted at baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`.

## Behavior and limits

The production `QuerySession::checkpoint_file` API captures one complete CROWNSI1
artifact while holding the session guard. It anchors the parent, creates an
exclusive random 0600 sibling, writes all bytes, fsyncs/checks close, renames,
then fsyncs/checks the directory. It does not acknowledge input or advance state.
Temporary and destination basenames must differ. The final leaf is replaced
without following a symlink. The supported Linux local-filesystem contract
requires an existing parent trusted against external temporary-name edits.

Failures distinguish not_published, unknown, published_unsynced and durable.
Rename errors are unknown; directory-close errors after successful fsync retain
durable status. Cleanup is bounded to eight attempts and reports failure without
hiding the original stage/errno. A failed save never claims rollback after rename.
Process termination may leave private temporary names; named restore ignores them.

`restore_file` requires a no-follow regular file and checks its size before
allocation. A 316-byte stack preamble determines the captured or overridden
memory cap. One receiving account owns the complete buffer, decoded source/window
state and rebuilt runtime. The buffer is freed before return; runtime admission
uses one indexed grant. Full checksums, bindings and native validation still run.
Read loops require expected length and EOF, compare inode/size/mtime/ctime, and
close descriptors on failed allocation/parse/I/O. Image/native/account ceilings
and finite I/O path/chunk/operation limits remain independent.

## Final selected acceptance

| Configuration | Selected tests | Seconds |
| --- | --- | ---: |
| GCC Debug | 53/53 | 23.43 |
| GCC Release | 53/53 | 6.11 |
| Clang18 Debug | 53/53 | 19.23 |
| ASan+UBSan with leaks | 53/53 | 92.81 |

The previous 50 selected names are retained. All 42 actual targets per mode were
built; accepted builds have zero compiler diagnostics. Actual flags retain C++23,
strict warning errors, enabled test assertions and sanitizer/leak settings.
The audit hashes 168 executable files/four caches, 24 changed translation-unit
objects, 16 archives and 368 compiler/link records. The production file test
links `libcrown_runtime.a`; private syscall/crash injection links the separate
testing library. No predecessor assertion, fixture, limit or timeout was weakened.

Production cases cover both backends, six typed queries and four control states
(48 cases). Persistent allocation faults cover all 18/608 reference and 20/617
indexed self-join capture/restore requests. This file fixture uses workload-off
defaults; the predecessor binary fixture's workload capture remains independently
covered by the retained tests. Exact receiving peak succeeds and one byte under
fails. Repeated publication retains no account growth or normal temporary names.
Source destruction, CSV permutation/origin continuation, two window FIFOs across
both backends, corruption/truncation, symlink/special-file refusal, descriptor
cleanup and next-update behavior pass.

For each backend, hooks exercise failures before/after all 26 publication and 25
read syscalls, three-byte short transfers, zero progress, EINTR and operation caps.
Cleanup EACCES and persistent EINTR verify the eight-attempt bound, cleanup flag,
retained old artifact and no descriptor leaks. Successful truncate/grow/overwrite
after initial stat are verified and rejected. The new mutation callback originally
discarded syscall results; Release fortified warnings caught that. Final source7
checks the results and requires actual mutation; source6 production code is unchanged.

Each backend has 52 before/after process-exit publication boundaries (104 total).
The parent loads the named artifact and verifies the exact old/new epoch, state
and subsequent self-join deltas. This tests process termination, not power-loss
or hardware simulation. Durability relies on successful local filesystem fsync.

## Preserved controls and handoff

Deterministic zero entropy made the temporary basename equal a missing destination.
Before the guard, the actual executable failed with
`temporary basename collision exposed destination before publication`.
All ten source preimages and the negative ELF are preserved. The unchanged
control passes after skipping that basename before creation. Leaf symlink entry
replacement also leaves the symlink's target unchanged. The independent 1067-byte
Python session fixture and all prior codec fault checks remain intact.

Receipt prefix: `build/verification/o04-session-files-native-`. The matrix audit,
job records, archived terminal stdout, negative/positive logs and source preimages
are retained. All 31 jobs are closed. Tested source7 pins 1018 paths; final8
adds this record and changes documentation only (1019 paths). Seal and independent
readback bind sources, compiler records, actual binaries and documentation links.

Root implemented the work; Luna Max supplied bounded primary-manpage inventory
and read-only review. No Astra was used. The [handoff](../handoff.md) records next
steps. Ledger stays 42 verified/3 in progress/33 not started, 78 total. Full O04
acceptance is next; O05 WAL and O06 durable delivery/replay remain separate.
