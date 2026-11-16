# S05 native window ownership — 9 November 2026

Status: **in progress**. The full 78-card Refactor.md goal remains active at
41 verified / 3 in progress / 34 not started. Root implemented this checkpoint;
one existing Luna Max agent performed a read-only caller/test census. No Astra
was used. Continue using root for most work, reserving Astra Max sparingly.
Artifacts live in `build/verification/s05-window-native-*`.

## Actual storage and ownership

WindowController uses the original query account for compact label/count rows,
expiration/global/relation FIFO nodes, active watermark capacity, transient
preflight cursors, Prepared control and its compact physical-update payload.
Session:0 keeps the existing outer controls; nested window ownership is session:1.
Actual allocations and framing are charged, with no ordinary operational Row,
string/container mirror, accounting-only ticket or replacement allowance.

Immutable WindowTables owns funded control/capacity storage. AccountedWindowOptions
copies share that owner without allocation, including retained run contexts after
controller/session destruction. Caller WindowOptions and canonical labels/counts/
active commands remain explicit external DTOs. Prepared::update() exposes
PhysicalUpdateView over its own native payload until Prepared destruction,
including after publish. DeltaRuntime::begin_view imports native rows/pins before
returning and retains no borrowed caller row. External update APIs use the same
admission path without manufacturing an ordinary Row export.

Full-row duplicate reference counts, global/per-relation FIFO, complete watermark
preflight and command/physical sequence separation retain their behavior. Only the
last watermark step acknowledges the command/watermark. Failure preserves the
prior committed prefix and permits retry. Publish/stop/teardown allocate nothing;
stop frees actual expansion capacity while retaining active prefix scalars.

WindowMetrics.accounted_bytes and max_accounted_bytes now describe native retained
payload/index descriptors and active expansion capacity. Numerical values change
from the former ordinary Row-capacity estimate. This component sublimit remains
separate from actual query requests, including tree links/framing/controls and
preparation overlap. All of those requests use the same original query limit.

## Source and verification scopes

Production source1 freezes 928 paths. Source4 adds the new test and its harness
corrections, for 929 paths. Existing tests and production remain unchanged in the
later test versions. Source5 changes only the new test's optional reset/emplace
sequence to direct owner copy/move/assignment; all assertion calls remain. Final
source6 changes current documentation only, for 930 paths. Full Debug build5
covers every target on source4; the final source5 new test is rebuilt separately.

| Configuration | Completed scope |
| --- | --- |
| GCC Debug |212/212 source4, 880.95s; final test source5 1/1, 1.59s |
| GCC Release |25/25 source5, 15.09s |
| Clang18 Debug |25/25 source4, 99.58s; final test source5 1/1, 1.41s |
| ASan+UBSan/leaks |25/25 source4, 523.04s; final test source5 1/1, 5.97s |

Strict final builds retain all warning flags and have zero compiler diagnostics.
Detailed stdout is preserved before subsequent CTest/registration calls; no
registration enumeration overlaps CTest. All 28 recorded jobs are
closed. Progress-v2 binds exact source scopes, binary hashes, raw attempts and
handoff. Complete compiler/sanitizer/fresh-source/native acceptance remains open.

The actual window_memory test reconciles upstream allocation calls against native
account allocations, covering both backends/FIFO policies, five scalar types,
38-digit decimals, long binary keys, retained options/update payloads after
facade destruction, original-account caps, 512-label expansion, prefix recovery,
same-input retry, final controller-only release and no-allocation barriers.
Debug source4 fixture insertion peaks are 129086 reference / 130446 indexed;
global watermark peaks are 550946 / 551821 and per-relation peaks 551232 / 552107.
Persistent scenarios cover reference 26/6/15/14 global and 26/6/17/14 per-relation
faults; indexed counts are 30/6/18/17 and 30/6/20/17. These are fixture measurements
rather than universal production peaks. Final source5 stdout is preserved too.

Keep raw attempts: the new test first used a private accessor; source3 switches
to the existing public plan accessor. A GDB trace proves its next abort was the
allocation helper rejecting nested guards; source4 leaves the persistent failure
scope active and independently forbids publication allocation on ordinary calls.
GCC Release later flags the optional reset/emplace test idiom; source5 directly
copies/moves/assigns the native owner. No production code, warning flag, assertion,
existing reference/model test or frozen schema/CLI verifier was weakened.

## Remaining work

Transport/TypedQueue controls and nested input/window-command/source-position
payloads, EventReader options/decoder/cached records/progress, nested session
input/options/progress/observation/cursor/workload settings, capture/report/
diagnostic/asynchronous graphs and authentic operator record/byte reconciliation
remain incomplete. The 7-file 211-candidate next-owner
inventory includes funded aliases/borrowed inputs/explicit external exports and
is not exhaustive proof. Complete overflow/no-op/churn and full native matrices
remain open. S05 and whole-query memory-budget acceptance remain **false**. See
[handoff](../handoff.md), [memory contract](../memory_accounts.md),
[window guide](../batches_windows.md) and [ledger](../task_ledger.md).
