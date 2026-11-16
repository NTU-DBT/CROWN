# O04 native complete-session checkpoint composition

This record covers complete native in-memory QuerySession checkpoint capture and
restore. O04 remains in progress: the pointer-free complete session envelope,
format compatibility rules, atomic durable publication and full/fresh-source
acceptance are still required. Root performed this work directly, with no Astra
or other agent. The full Refactor.md goal remains active; ledger42 verified,
3 in progress (A02/O04/O06),33 not started,78 total is unchanged.

## Implementation and ownership

[SessionCheckpoint](../../include/crown/runtime/session_checkpoint.hpp) owns the
runtime binary image, native input/source/window metadata and flat session
control/policy state. [QuerySession](../../src/runtime/session.cpp) captures under
the creator-thread/reentry guard and rebuilds an unpublished new session in one
receiving account. The runtime admission grant spans managed-row validation,
physical/source/support/live rebuild and workload configuration. Active reader
options share one newly funded native control with SessionRunContext.

Accepted/runtime/window sequences and source kinds/policies must agree. Every
managed base row must equal a distinct window count row; a window which is valid
on its own but mismatches base rows rejects. Unmanaged initialized tables remain
intact. Created/running/paused/stopped typed and window sessions round trip;
streams retain all eight profiles, paused accepted prefixes, original byte/record
origin, CSV mapping, EOF and stopped accepted/failure state. Active streams need
a supplied continuation at the next unread byte. Diagnostic histories, owner IDs,
allocation history and declared benchmark labels reset; configuration is retained.

Capture rejects queued/cached/failed active input, private/prepared/draining
work, unread/partially consumed output and active watermarks. An active command
still blocks capture between physical commits. A stopped partial watermark keeps
its existing active-command tombstone; rejection is allocation-free and preserves
physical sequence3/source sequence5 in the explicit fixture. Existing stop
semantics were retained.

## Acceptance executed

| Configuration | Selected tests | Wall time |
| --- | --- | --- |
| GCC Debug | 48/48 | 22.90s |
| GCC Release | 48/48 | 3.09s |
| Clang18 Debug | 48/48 | 19.93s |
| ASan + UBSan + leak checking | 48/48 | 94.06s |

All four modes test the same executable code from source8 (999 paths); final9
adds this record and changes documentation only (1000 paths). These48 selected
regressions are scoped evidence, not a full or fresh-source O04 acceptance claim.
The matrix retains the predecessor's44 runtime/source/window, ingest/CLI,
transport, lifecycle, storage and memory regressions and adds four actual native
session targets (production and actual indexed-grant variants).

Each production/grant session target covers48 typed cases across two backends,
six query kinds and four lifecycle states. Cases include unary projection,
self-join, disconnected maintenance, nullary set, bound SQL predicate and SQL
EXISTS. Typed snapshots and signed delta sets use the independent A04 definition
or explicit SQL definitions; subsequent output ordinals remain contiguous.
Each also covers16 stream profile/backend continuations. Each window target
covers16 backend/FIFO/lifecycle cases, metadata-only commands, duplicate labels,
orphaned original count IDs, multiple expiration steps and next updates. Explicit
unmanaged initial rows and complete window/base matching are checked separately.

Whole-session self-join capture/restore sweeps every17/609 reference and19/618
indexed allocation position. Windows sweep26/306 reference and28/315 indexed
positions for each FIFO policy. Global replacement allocation counts match actual
original/receiving account requests. Exact receiving restore peaks succeed and
one byte less rejects. Images survive original-session destruction; after image
release only its account controller remains, and destruction allocates nothing.

Malformed versions/kinds/sequences/policies, valid-but-mismatched window rows,
zero and exact matching-work thresholds, wrong-thread/busy capture, cached healthy
reader rejection after engine overflow, failed reader terminal state and stopped
metadata limits are exercised. Matching work counts abstract set/directory/field
visits; scalar byte comparisons are additional. It is not a CPU-time claim.

## Counter-reset control and preserved failures

The unchanged public-only control in `reader-counter-control-v3.cpp`/`v4.cpp`
links actual production archives. Before the fix, resetting saved reader records
to0 at accepted sequence1 allowed sequence2 past configured records1. Its ELF,
source/log and17 pre-fix source paths are preserved under the receipt prefix.
The same source now rejects before publication. Session-owned readers start at
zero, so their quiescent record count must equal accepted sequence. Distinct
accepted positions cannot outnumber accepted records. All eight profiles and both
backends reject these corruptions before any receiving allocation.

Initial new-fixture compilation errors and raw test failures remain preserved.
The nullary fixture accidentally set constant_false and was corrected. A GDB
trace proves an initial exact-cap failure was a3440-byte result-cursor allocation
after successful restore; the cap test now checks nonallocating status and the
actual restore peak, while independent result and one-under assertions remain.
The new stopped-partial-watermark fixture initially expected a round trip despite
an active tombstone; it now tests the existing no-active-command barrier and
unchanged terminal prefixes. No predecessor assertion, fixture, cap or timeout
was weakened.

## Reproducibility and continuation

Receipt prefix: `build/verification/o04-session-checkpoint-native-`. The native
matrix audit pins152 actual executables/four caches,52 changed-unit objects,
16 core/plan/runtime archives and336 compiler/link records. All accepted build
logs have zero compiler diagnostics; strict warnings, assertions and sanitizer/
leak settings are checked against actual generated flags. Every terminal CTest
stdout is archived. All43 jobs and tool handles are closed. Final seal and
independent readback pin source inputs, preimages, native bytes, compiler records,
artifacts and document links.

Continue with binary serialization of this native session state, checksum and
compatibility validation, then atomic durable publication and full/fresh O04
acceptance. O05 WAL and O06 durable replay/delivery remain separate. See the
[checkpoint contract](../checkpoints.md), [handoff](../handoff.md) and
[ledger](../task_ledger.md).
