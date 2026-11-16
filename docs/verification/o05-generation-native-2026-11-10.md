# O05 native generation selection — 10 November 2026

This turn advances O05; full Refactor.md remains active. Root implemented and
reviewed production changes. Luna Max supplied a bounded read-only helper
inventory/review and independent root bytes; no Astra was used. Ledger43 verified,
3 in progress(A02/O05/O06),32 not started;78 total. Work remains uncommitted on
baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`.

## Accepted boundary

The [generation API](../generations.md) selects an exact checkpoint/journal pair
through a separately locked durable root. Initial enable publishes both complete
files before the root. Quiescent rotation publishes a new native checkpoint,
fresh journal/header and durable root before activating the new writer. Recovery
checks root query identity/checksum/stable metadata, checkpoint hash/bases and
native journal binding before any replay or tail repair. No owner/output escapes
before native reconstruction succeeds. Initial/rotation completion after the
root-selection syscall is verified allocation-free.

The old selected pair is retained. Cleanup can remove only the next unselected
candidate after rereading current root under its stable sentinel lock. Neither
output consumption nor the replay frontier authorizes deleting history. The
default retained-generation cap32 bounds selected pairs; durable O06 output
acknowledgment, history retirement and complete integrated acceptance remain open.
Relative paths require stable CWD; trusted Linux parent/name/fsync assumptions
are explicit. Checksums are not authentication signatures.

## Verification

Frozen native source1 retains all1057 predecessor paths and adds11 implementation,
header/test/support and independent-fixture paths (1068 total). Only CMakeLists.txt,
session.hpp and session.cpp among prior paths changed. No old test, assertion,
fixture, resource cap or timeout changed. Every final selected66/66 test passes
in four configurations: Debug 60.69s, Release 37.03s, Clang18 64.7s, ASan+UBSan/leaks 145.63s. All250 predecessor names remain among253
registered names. These are scoped component regressions, not full253/fresh
acceptance. Historical predecessor acceptance applies to its frozen snapshots.

Each mode covers24 typed query/backend/pending cases,32 eight-format stream/
backend/pending cases and16 partial watermark/backend/FIFO prefixes. Exact native
state, source/decoder/CSV continuation, selected-generation output identity and
the next update match uninterrupted/reference execution. Old pair bytes remain
intact across rotation/recovery. Root truncation at every byte and a one-bit flip
at each byte reject; checksum-valid malformed/query/checkpoint/bases mutations
and a root mismatch with a torn log reject before repair. Missing root never
selects orphan files. Symlink admission, exclusive creation, lock/drop, maximum
generation, copied retention policy and exact/one-under cumulative work/I/O limits
pass.

An independent Python struct/hashlib generator supplies a212-byte CROWNGR1 golden
without the production codec. Full record SHA256 is
`bc82d64bb74bdf4ca99958b41d9bf83d33025e15c08407b3cfceef0168543d9c`.
Production inspection matches all fields; maintained fixture/generator/manifest
are byte-identical to the independent artifacts.

All910 receiving allocation failures release account/descriptor/lock ownership
without changing the selected root/log; measured exact/one-under query peaks pass.
Actual enable/rotate/reopen traces contain34/35/43 syscall boundaries across root,
checkpoint-reader and journal backends. All222 applicable before/after injected
I/O errors and224 process exits pass native old/new state/source/output/next-update
checks. Two after-boundaries concern unlink already returning ENOENT; an
after-success injection cannot change those failed syscalls, and they are checked
separately as already-absent candidates. Short3-byte transfers, repeated EINTR
and cumulative I/O limits pass. Both crash sides remain covered for all112 actual
boundaries. Process exits are not power-loss simulation.

The initial3 focused tests passed, but unchanged production-only public controls
then reproduced an uncovered configuration gap: too-small checkpoint path or
zero chunk/operation load policies could publish a root. Each saved negative
ELF mode exits1. The final unchanged control source exits0 for all three modes
after preflight validation. Full1068-path interim source and two relevant Debug
objects/negative ELF are preserved. The separate initial fault-test assumption
about after-success injection on ENOENT was corrected without weakening actual
error/crash coverage; its failing stdout remains. Initial declaration/test compile
corrections and the unconfigured-new-target build failure are also retained.

Audit pins204 actual executables,24 changed-unit objects,16 archives/four caches
and440 compiler/link records, plus production-only negative/positive public
controls. Strict C++23 warnings-as-errors, unchanged predecessor flag records,
new-test assertions and sanitizer/leak settings pass. All22 final matrix/control
receipt jobs are CLOSED; every terminal stdout was archived before enumeration.
Accepted builds have no compiler diagnostics. No build overlaps CTest in its own
directory.

## Evidence and next work

Receipt prefix: `build/verification/o05-generation-native-`. It includes
preimages-v1,interim-v1,negative-objects-v1,independent-v1,public controls/commands,
inputs-v1,scope/runners,all four-mode final-v1 jobs,matrix-audit-v1,
root-review-v1,progress-v1,jobs-v1,checkpoint-seal-v1 and post-seal-audit-v1.
Final docs-only source2 adds this record and the API guide (1070 paths). Verify
the seal and independent readback before new edits. Earlier focused/failing logs
are historical evidence; final acceptance belongs to the frozen native source1.

Next implement O06 durable local output/outbox acknowledgment/deduplication and
bounded backpressure/cancellation. Use durable sink authority to permit old-pair
retirement only after the selected checkpoint and required delivery are covered,
then verify every retirement/persistence boundary and full/fresh O04–O06
acceptance. Remaining A02/other Refactor tasks and release gates stay open. See
[handoff](../handoff.md).
