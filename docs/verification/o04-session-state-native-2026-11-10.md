# O04 native source/window state progress and restore-grant repair

10 November 2026. O04 remains in progress. This checkpoint adds actual native
source/window state capture and receiving-account restoration. The complete
QuerySession envelope, cross-owner checks, binary session manifest and durable
file publication are still required.

## Native state and ownership

`io::QueueCheckpoint` retains accepted positions, mode, limits, closed state and
catalog identity. Capture requires an empty, healthy queue. Restored queues
continue sequence/source-offset validation under their original limits.

`io::ReaderCheckpoint` retains native options, accepted positions, original
byte/record counters, CSV header/permutation and EOF. Capture rejects a cached
unacknowledged record or failed reader. Restore takes a continuation at the next
unread byte; subsequent source offsets and total byte/record quotas continue
from the saved origin. Receiving imports deep-copy native positions/options
instead of exporting ordinary maps or strings. Custom source-state limits are
available on capture and restore.

`WindowCheckpoint` owns native label/count rows and retains options capacity,
catalog identity, command/physical/watermark/last-label progress, last command
work and terminal state. A count ID can survive withdrawal of its original label.
Restore checks row/domain shape, unique physical counts, exact label references,
deadline arithmetic, multiplicity and catalog binding, then rebuilds FIFO and
expiration directories. Prepared steps and active multi-step watermarks reject
capture, including between their committed physical steps.

All native snapshot and import allocations use the original or receiving query
account. Immutable options can be retained; imports clone them under the receiver.
Work/label/count/source/CSV limits and the actual account-byte limit remain finite.
These native C++ objects are components for serialization, not a session file format.

## Indexed-work repair

The predecessor runtime-image restore ended its physical admission grant before
live bootstrap, creating a second allowance. A new direct
`fresh_operations==1` assertion fails on the preserved source3 implementation.
Source4 moves one outer operation around program/source/support/live restore;
the same assertion then passes. Source5 also checks the public error when initial
indexed work is zero and calibrates the exact byte cap immediately after restore.
The indexed persistent-failure sweep now covers389 allocation positions, compared
with391 in the predecessor; reference restore remains377. No existing assertion,
fixture, configured limit or timeout was weakened.

## Evidence

All991 predecessor paths were checked without drift and copied to
`o04-session-state-native-preimages-v1`. Source6 freezes995 paths. Actual raw
source3 failure, four focus-source preimages and successful post-repair runs
remain under the same receipt prefix.

Source tests cover eight reader profiles, physical/window queues in open/closed
states, all3–4 reader capture and12–15 reader restore allocation positions,
all10/12 queue positions, and1025 accepted sources with explicit larger limits.
They compare subsequent rows, source offsets, CSV mapping, quota counters and EOF.
Window tests cover both backends and both FIFO policies, all6/30 capture/restore
positions, count IDs whose original label is gone, exact/one-under receiving byte
caps, work/count limits, malformed metadata, repeated snapshots, active watermark
barriers and subsequent insert/expiration state and deltas. Both new tests link
the production runtime archive. The existing runtime image test now directly
checks one grant across all indexed restore cases.

| Configuration | Selected tests | Result | Seconds |
| --- | ---: | --- | ---: |
| GCC Debug |44 |PASS44/44 |22.44 |
| GCC Release |44 |PASS44/44 |3.17 |
| Clang18 Debug |44 |PASS44/44 |18.31 |
| ASan+UBSan/leaks |44 |PASS44/44 |93.20 |

The scope includes ingest/CLI fixtures, transport, session/window, runtime and
actual byte/storage regressions. The existing ordinary initialization case stays
selected; its implementation is unchanged. The predecessor separately records
the complete initialization exception sweep. Current scoped checks do not replace
full231-case/fresh-source O04 acceptance.

The independent audit reads136 actual executables/four caches,64 directly changed
translation-unit objects,16 core/plan/runtime archives and304 generated compiler/
link records. Strict C++23/warnings-as-errors and new-test `-UNDEBUG` remain; the
new tests have no runtime testing ABI. Sanitizers retain leak detection and
halt-on-error. Accepted builds have zero compiler diagnostics. All20 jobs are
closed and every terminal CTest stdout is archived.

## Next complete-session work

Compose these components under QuerySession's thread/reentrancy guard and the
receiving runtime account. Preserve session control/EOF/failure state, snapshot
and input policies, source-kind metadata and all independent sequences. Require
the actual quiescent source/window boundary. Validate managed base rows against
window counts while using the runtime restore's admission grant. An internal
source/window import must not create another runtime allowance or ordinary DTO.

Encode the full versioned session manifest with source/output positions and
checksums; add atomic durable file publication and complete SQL/alias/Boolean/
window/corruption/compatibility/repeated-checkpoint acceptance. O05 WAL and O06
replay/delivery identity remain separate. The full78-card goal stays active.
See [the handoff](../handoff.md) and [component contract](../checkpoints.md).
