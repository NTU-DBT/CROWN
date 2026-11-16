# O05 native journal reconstruction — 10 November 2026

This is progress on O05, not full Refactor.md or O05 acceptance. Root implemented
and reviewed this cohort; Luna Max supplied a bounded read-only source inventory
and replay review. No Astra was used. The ledger remains43 verified /3 in progress
(A02/O05/O06) /32 not started,78 total. Work is uncommitted on baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`.

## Accepted behavior

The [production factory](../native-replay.md) restores the exact checkpoint into
one receiving account, streams validated journal frames through native source
staging, checks each actual prepared physical/metadata transition and returns a
paused owner only after whole-prefix/EOF/stamp/sync validation. Complete pending
input and partial watermark commands survive; native decoder bytes/records/CSV
mapping and source positions resume before the external unread continuation.
Explicit torn repair follows native validation and optional seek. Complete
corruption rejects without truncation.

Committed replay output is retained under row/actual-byte/query-account limits.
Identity compares exact query/generation/physical epoch/operation/native values,
excluding ordinal and iteration order. Buffer consumption or explicit discard
precedes new updates. A caller frontier is not a durable acknowledgment.
Checkpoint/generation retirement and the O06 delivery protocol remain open.

## Native evidence

Final frozen source1 contains1055 paths, retaining all1053 writer predecessor
paths and adding two native tests. Exactly13 non-document paths changed; no old
test/fixture, resource cap or timeout changed. Final selected63/63 pass in all
four configurations: Debug 30.66s, Release 20.78s, Clang18 41.02s, ASan+UBSan/leaks 123.3s. All247 predecessor test names remain among250
registered names. This is scoped component regression acceptance, not a full250
or fresh-source matrix.

Each configuration verifies24 typed query/backend/pending combinations,80 stream
format/backend/baseline/pending combinations, two nullary quoted-CRLF CSV cases
and16 duplicate-label watermark/backend/FIFO/prefix cases. Stream cases resume a
third unread event from either the original seekable source or an unread tail;
pending input precedes it. Native state/source/output identity and the next
journaled update match uninterrupted execution. All470 input/decision byte cuts
test actual reconstruction, repair policy and exact next commit. Complete
checksum corruption and checksum-valid transition/CSV mapping/text-offset
forgeries reject. Valid quoted, CRLF and headerless CSV cases prevent false
rejection of allowed header lengths.

All916 receiving allocation failures preserve ownership/descriptor/log contracts;
exact/one-under query peaks retain real memory categories. Codec work, cumulative
source work, output rows/bytes, generation binding and output identity limits are
checked. Actual file before/after errors cover98 recovery/repair cases;98 process
exits reopen through the native factory and verify state/source/output/pending
input. Short reads and repeated EINTR obey finite I/O limits. These are process
crashes at actual syscall boundaries, not power-loss simulation.

Two unchanged public API controls expose gaps in the initial implementation:
an offset109 was accepted where the checkpoint-known CSV start is108; a new
1024-byte source name escaped a128-work source limit. Saved pre-fix production
ELF exits1 for both. The final production ELF exits0 for the same control source,
without private runtime hooks or reference-runtime linkage. Exact known text
starts, possible schema/quoting header bounds and conservative precharged source
validation fix these cases. Source work is cumulative across replay inputs.

The audit pins196 actual native executables,32 changed-unit objects,16 archives,
four caches and424 compiler/link records, plus the three public-control builds.
Strict C++23 warnings-as-errors, test assertions and ASan+UBSan/leak settings are
unchanged; accepted builds have no compiler diagnostics. Every terminal CTest
stdout is archived before enumeration. No build overlaps CTest in its directory.

## Reproducibility and limits

Receipts live under `build/verification/o05-native-replay-`: predecessor
preimages-v1, full interim-v1, negative-objects-v1, unchanged public-control-v1.cpp,
control-commands-v1/v2/v3 and their ELFs/logs, inputs-v1, matrix-scope-v1,
run-v1.py, matrix-v1.py/v2.py, final four-mode jobs, matrix-audit-v1,
root-review-v1, progress-v1, jobs-v1, checkpoint-seal-v1 and post-seal-audit-v1.
The final Debug jobs use `-final-v1`; Release/Clang/sanitizers use `-v1`.
Earlier focused logs, strict compiler corrections and the initial Debug job-name
collision are preserved. The collision stopped before launching a child; it did
not overwrite existing evidence. Expected public negative exits1 are recorded
separately from successful final tests.

Final docs-only source2 adds this record and the API guide (1057 paths). Verify
its seal/readback before new edits. Historical writer/File/codec/full-O04
acceptance applies to its own frozen source snapshots. The raw first CSV header
is not authenticated against the continuation stream; documented semantic bounds
and trusted, bound journal checks apply. Local Linux filesystem/fsync/stable-name
assumptions remain those of the file component.

Next: design and implement durable compatible generation selection/publication
before any committed-log retirement, then O06 durable output/ack/deduplication
and backpressure, integrated persistence boundaries and whole/fresh acceptance.
Other A02 and remaining Refactor cards/release gates remain open. See
[handoff](../handoff.md) for the current boundary and next dependencies.
