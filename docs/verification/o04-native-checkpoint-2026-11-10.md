# O04 native runtime image progress

10 November 2026. O04 is in progress. This checkpoint implements a native
runtime image and actual `DeltaRuntime` restore. Complete session/source/window
state and durable file publication remain required by Refactor.md.

## Implemented component

The [component contract](../checkpoints.md) documents CROWNRI1/version1,
physical/source/catalog/arithmetic/policy binding, exact binary scalar encoding,
bounded validation and the writer-ready barrier. Native source snapshots and
the encoded image use the original query account. Decode, executable admission,
constraint validation and support/index/live rebuild use one receiving account.
Restore preserves the committed sequence and semantic state; diagnostic history
starts fresh. The receiving memory ceiling is independently configurable.

Encode preflights serialized size/work before allocating its one final buffer.
Decode verifies the complete checksummed structure before output allocation.
All encoded values are owned after capture and all decoded values after import.
No public ordinary snapshot graph is used internally.

## Evidence

Source6 freezes990 paths. All984 predecessor S05 source paths were verified
without drift and copied to `o04-native-checkpoint-preimages-v1`. The independent
531-byte Python struct/hashlib fixture has SHA256
`5c5c2b043e1ed6ce0e3f22aa5ffc9ba78557f33dd9b4a182b7586ce14e045da1`.
The C++ encoder matches every byte. Codec checks include every truncated prefix
and every single-byte bit flip; resealed bad versions/bindings/counts/tags/bools/
dates/decimals; trailing bytes; integer/date/38-digit decimal extremes; wide
NUL/raw-byte strings; empty rows/tables; and exact/one-under byte/work/query caps.
Every1 encode and5 decode allocation position is swept with persistent denial.

Runtime checks cover20 backend/policy/build combinations: reference/indexed,
four Delta policy pairs plus maintenance mode, and direct/insertion-replay builds.
They compare exact source/support/derivation/live state and subsequent projected
delta sets. Direct on-output cases sweep all11/13 capture and377/391 restore
allocation positions. The same counts hold in all four compilers/configurations.
Exact/one-under receiving byte caps and zero rebuild-work rejection retain the
original state. Private epochs, readers and unread output reject capture.
Twenty repeated captures keep resident bytes stable. Held images survive source
closure, release without allocation and reconcile as actual recovery-owner bytes
in operator memory reports.

| Configuration | Selected tests | Result | Seconds |
| --- | ---: | --- | ---: |
| GCC Debug |37 |PASS37/37 |121.89 |
| GCC Release |37 |PASS37/37 |16.72 |
| Clang18 Debug |37 |PASS37/37 |98.17 |
| ASan+UBSan/leaks |37 |PASS37/37 |529.80 |

The scope is two new tests plus35 existing physical/delta/session/window/
initialization/memory regressions, using27 rebuilt actual executables per mode.
The independent audit reads108 binaries/four caches,28 changed-unit objects,
12 core/runtime archives and240 generated compiler/link records. Strict C++23
and warnings-as-errors remain enabled; new tests use `-UNDEBUG`. Instrumented
tests retain leak detection and halt-on-error. Accepted builds have zero compiler
diagnostics. The full229-test registration and fresh source build remain future
O04 acceptance work.

A separate public-only caller compiles against the actual production runtime
archive in all four modes, without the runtime testing ABI. Both backends pass
source-closed image lifetime, exact state/sequence and the next deletion. Its
four native binaries, sources, commands and logs are pinned separately under
`o04-native-checkpoint-production-control-v1`. Candidate1 incorrectly expected
ordinal0; the unchanged public contract starts at1. Candidate2 corrects that
expected constant and passes; both candidates and all raw results remain.

Earlier Debug attempts preserve an invalid test-policy combination and a cap
calibration that included later invariant scratch. The corrected test uses a
supported policy and measures the immediate restore peak. Exact/one-under and
all persistent-failure assertions remain. No existing test, fixture, assertion,
limit or timeout was weakened. The existing sanitizer initialization sweep
finished within its unchanged900s timeout.

## Remaining O04 work

The source-pinned `o04-native-checkpoint-session-integration-review-v1.json`
records10 actual session/queue/reader/window files. A session barrier must include
an active multi-step watermark, which can survive between committed physical
steps. Queue accepted positions, reader cache/framing/CSV state and independent
window command/physical/watermark/label counters require native serialization and
restore. Label/count/FIFO/expiration indices must agree with managed base rows.
Construct the session around the restored query account without admitting an
extra runtime allowance or exporting ordinary internal DTOs.

Add the complete session manifest, bounded native metadata, atomic durable file
publication and complete corruption/compatibility/repeated-checkpoint acceptance.
The current checks compare delta sets; stable replay ordering/identity remains
part of O05/O06. O04 is not verified. The full78-card goal remains active.

All20 current jobs are closed, all terminal CTest stdout is archived and every
production-control handle is closed. Final source/progress/seal receipts use
`build/verification/o04-native-checkpoint-`. Continue from [the handoff](../handoff.md).
