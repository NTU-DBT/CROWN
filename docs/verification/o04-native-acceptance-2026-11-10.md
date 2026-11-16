# O04 full native acceptance — 10 November 2026

O04 versioned checkpoints are acceptance-verified. The full Refactor.md goal
remains active. Work is uncommitted at baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`. The [contract](../checkpoints.md) defines
the supported APIs, binary format, resource accounting and failure outcomes;
the [handoff](../handoff.md) identifies the next work.

## Full current matrix

| Configuration | Tests | Seconds |
| --- | --- | ---: |
| GCC13 Debug | 240/240 | 924.94 |
| GCC13 Release | 240/240 | 168.54 |
| Clang18 Debug | 240/240 | 758.85 |
| ASan+UBSan with leaks | 240/240 | 3649.70 |
| Fresh source-only GCC13 Release | 240/240 | 167.70 |

All 227 S05 registered names are retained; 13 O04 names extend them. Each mode
builds 202 actual native executables. Complete terminal stdout is archived for
every run. No predecessor fixture, assertion, memory/work cap or timeout changed.
The sanitizer planner timeout remains 7200s, 3600s elsewhere. All sanitizer tests
retain leak detection and halt-on-error settings. The clean source tree copies
and hashes all 1019 accepted source paths without any cache/object/library/
executable; its configure, full build and full tests run in a new directory.

The audit pins 1010 full-build executables,130 project archives,1160 strict C++
flag records,1140 links and15 cache/CTest/compiler-command records. Production
session tests link the actual production library; grant/syscall hooks use the
separate testing library. C++23, all strict warning errors and active test checks
are verified against generated flags/commands. CROWN code has no compiler
diagnostics. The fresh upstream build emits the same two upb C warnings and one
recursive Make notice as the accepted S05 clean build. The exact lines, raw logs
and unchanged pinned dependency archive are preserved; no suppression or flag
change hides them.

## Requirement evidence

The eight clauses below have concrete source hashes/test mappings in
requirement-audit-v2.json and are checked against the complete current matrix.

| Requirement | Evidence |
| --- | --- |
| Manifest and bindings | Runtime and complete-session manifests bind physical/source hashes, catalog version, arithmetic, runtime policies, committed epoch and accepted source positions. |
| Pointer-free state | CROWNSI1/version1 serializes owning values, controls/options, reader/queue metadata and window labels/count identities/deadlines; embedded CROWNRI1 base rows rebuild native support/index/live state. |
| Checksums/compatibility | Both SHA256 layers, exact versions/flags, canonical scalar/enum/optional/count formats and native program/schema/window admission are enforced. |
| Quiescence | Session guard spans capture/encode/I/O; private epochs, queued/cached input, unread output, active windows and stopped partial-watermark tombstones reject. |
| State/results/next updates | Reference/indexed backends, six typed query shapes/four controls, eight stream formats and both window FIFO policies preserve independent exact state/deltas and next updates, including after source destruction. |
| Malformed and incompatible input | Independent 531/1067-byte fixtures, every truncation/bit flip, resealed invalid structures/bindings and actual corrupt/truncated/changing files reject safely. |
| Repeated resource budgets | Repeated capture/save has stable resident storage; persistent allocation faults, exact/one-under byte/work caps, one receiving account and one indexed runtime grant are exercised. |
| Durable files | Exclusive sibling/full write/fsync/checked close/rename/parent fsync, every syscall before/after fault, bounded cleanup and52 process-exit boundaries per backend preserve the specified old/new epoch and next update. |

The predecessor [runtime](o04-native-checkpoint-2026-11-10.md),
[source/window](o04-session-state-native-2026-11-10.md),
[native session](o04-session-checkpoint-native-2026-11-10.md),
[binary envelope](o04-session-image-native-2026-11-10.md) and
[durable-file](o04-session-files-native-2026-11-10.md) records retain detailed
case, allocation-fault and deterministic before/after control evidence. The
complete current matrix covers their registered tests together with all previous
subsystems. Diagnostic histories/allocation identities restart on a new owner;
logical state/configuration and accepted progress are preserved.

## Isolated public binding controls

Read-only inventory identified two binding dimensions lacking isolated complete-
session negative coverage. The supplementary public C++ control changes source
SHA or catalog version independently, leaves physical SHA unchanged, recomputes
both checksums and confirms structural inspection succeeds. Four restore attempts
per field must reject with ImageFault::binding. The valid baseline restores.
All five production-library controls pass: five valid restores and40 incompatible
admission rejections. The controls also check original session/account stability.
They use public APIs without private runtime hooks. Their retained source, exact
compile/link commands, five objects/executables and raw logs are part of the seal.

## Handoff and scope

Receipt prefix is `build/verification/o04-final-native-acceptance-`. All
25 configure/build/test/control jobs are closed. Tested inputs-v1 and all
preimages pin 1019 paths; final inputs-v2 adds this guide and changes documentation
only (1020 paths). Matrix and requirement audits, warning review, binary
inventories, final progress, seal and independent readback bind source, actual
executables, compiler/link records and archived test stdout.

The durable file contract is Linux local filesystem successful-fsync behavior
with an existing parent trusted against edits to private temporary names.
Process termination is tested; power-loss/hardware simulation is not claimed.
Publication uncertainty and failed cleanup remain explicit caller-visible states.
O05 WAL/replay and O06 durable delivery/output deduplication remain separate;
O08 CLI integration and release gates are still open.

Root completed implementation/acceptance. Luna Max supplied bounded read-only
inventory; no Astra was used. The ledger is43 verified/2 in progress(A02/O06)/
33 not started,78 total. O05 deterministic journal recovery is next.
