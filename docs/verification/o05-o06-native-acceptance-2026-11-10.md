# O04–O06 integrated native acceptance — 10 November 2026

O05 WAL/recovery and O06 sinks/backpressure are verified for the documented native
library and local-file guarantees. O04 checkpoints are revalidated in the same
cohort. All 264 current tests pass five complete configurations, including clean
source-only Release. The full Refactor.md goal remains active:45 verified,
1 in progress (A02),32 not started;78 cards. O08 CLI, licensing, experiments and
release reviews remain open. Work is uncommitted at baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`.

## Scope and reviewed implementation

The tested1101-path snapshot preserves all 1100 predecessor paths. This round adds
`tests/unit/durable_pipeline_test.cpp`, registers two integration tests and
corrects three header comments. All production implementation bytes are unchanged;
the header changes are token-identical after comment/whitespace removal.
Every previous test source/fixture,262 registered commands/properties, assertion,
cap and timeout is preserved. Earlier240 O04 and227 S05 names are retained.

The 20-requirement audit maps actual Refactor.md O04/O05/O06 acceptance to reviewed
source hashes and registered tests. Root owns implementation/acceptance. Luna Max
provided the earlier bounded coverage inventory; no Astra was used. Three gaps in
composed coverage were closed: native recovery at each writer boundary, whole
self-join fanout rollback with an attached journal/sink, and poisoned same-owner
sink reopen retaining a queued next input and spent delivery work.

Input sync precedes physical pending work. The bound decision sync precedes
native/source publication. Unknown persistence outcomes block further publication.
Recovery validates selected checkpoint, native state, ordered input/decisions,
reader/queue/window progress and actual persisted sink before tail repair or owner
exposure. Root-selected generation rotation syncs the new checkpoint and log
before root selection. Verified local delivery and native checkpoint validation
gate a durable retirement intent, then root floor, each recorded old unlink/sync,
and intent removal/sync. The selected pair survives; sink-aware recovery resumes
recorded cleanup. Root v2 binds the pre-checkpoint sink prefix; old unproved v1
prefixes do not authorize retirement or sink rotation.

In-process callback delivery has its documented pause/error/retry semantics. Local
file delivery atomically accepts whole canonical physical epochs (including empty
closures), compares exact typed bytes on retry and acknowledges only after sync.
Private spools cannot be transferred or delivered. Pending/failed delivery holds
source admission before another peek. Buffers, sorting, source/native storage and
prefix index share the original query memory account and copied finite cumulative
work/I/O/row/byte limits. Bounded rejection/backpressure costs are reported; there
is no spill fallback or sink-file compaction.

## Complete matrix

| Configuration | Passed / registered | Wall seconds |
| --- | --- | --- |
| debug | 264 / 264 | 939.98 |
| release | 264 / 264 | 749.63 |
| clang | 264 / 264 | 852.09 |
| sanitize | 264 / 264 | 3720.94 |
| fresh_release | 264 / 264 | 484.54 |

These are full unfiltered CTest runs, with 218 actual native executables per mode.
Each default build completes before testing; its build outputs stay unchanged
during CTest. Supplemental controls write to a separate verification directory
and only read those completed libraries. Fresh Release uses exactly the frozen1101 source
paths, with no previous cache/objects, and every compiled source/include is tied
to that copied tree. Exact commands, compiler versions and terminal stdout are
retained in the evidence packet.

Strict C++23 warning errors, Release assertions (`-UNDEBUG` for recovery and
fault/integration tests), ASan+UBSan and leak checks remain enabled. The unchanged
planner residual timeout is3600s normally/7200s sanitized. Project C++ diagnostics
are empty. The clean build has exactly the same three accepted pinned upstream C
build diagnostics as the prior O04 fresh build: one jobserver warning and two
`upb` maybe-uninitialized warnings. No flags are relaxed.

## Native state, output and failure evidence

Both reference and indexed backends exercise a loop-edge self-join with three
exact oracle delta rows, generation2 checkpoint/log, committed source offsets
feed20/30/40, subsequent deletion, verified history retirement and another native
restart. Every mode covers18 private preparation prefixes,460 persistent
allocation faults (458 with logged pending input),32 actual input/decision writer
errors,16 same-owner sink errors and68 process exits. A poisoned sink retains the
next queued input without peeking/advancing source30, preserves spent work on
reopen, and publishes/deduplicates epoch3 before processing epoch4.

All predecessor cases also execute in each full run: typed/query/control-state
checkpoint round trips; eight stream formats and both window FIFO policies;
independent531/1067-byte runtime/session fixtures; every-cut/bit-flip and
checksum-valid malformed checkpoint/log/sink/root/intent cases; exact/under heap,
work, row and I/O ceilings; actual before/after file errors and process exits;
full state/source/output/next-update comparisons. Retirement alone retains12
native typed,32 stream,16 partial-window cases,861 allocation faults,312 actual
I/O errors and312 process exits. The 724-byte intent and324-byte root goldens
remain independent fixtures.

Two unchanged public production-only controls pass all five modes. One changes
source SHA/catalog version while repairing both checkpoint checksums and verifies
public restore rejection; the other changes old checkpoint-prefix sink output
with a valid frame checksum and verifies rejection before history deletion.
They link actual production libraries without the reference/testing libraries.
The historical negative/fixed evidence remains in its predecessor packets.

## Evidence and handoff

The local packet prefix is `build/verification/o05-o06-final-native-acceptance-`. It contains tested
`inputs-v1`,1100 preserved preimages, the source-only fresh manifest, per-mode
configure/build/inventory/CTest receipts and archived stdout, actual binary
inventories, both production controls, root review,20-requirement audit and final
matrix audit. All 40 final receipt jobs are closed successfully. Preparation and
historical receipts remain separately identified.

The native audit pins1090 registered ELF files,65 relevant actual objects,130
Crown archives plus five pinned parser archives,1240 strict flag records,1220
link records and15 build metadata files. Ten supplemental control executables
and their objects are pinned independently. A documentation-only final snapshot
adds this record (1102 paths); final seal/readback checks source, preserved
preimages, fresh copy, native bytes, receipts and document links before handoff.

Verify `o05-o06-final-native-acceptance-post-seal-audit-v1.json` and its seal before new edits. The
[handoff](../handoff.md) and [task ledger](../task_ledger.md) record next work.
See [checkpoints](../checkpoints.md), [native replay](../native-replay.md),
[generations](../generations.md), [local sinks](../local-sink.md) and
[retirement](../history-retirement.md) for APIs and wire/compatibility rules.

## Limits

These guarantees assume a trusted stable Linux namespace, cooperating locks and
local filesystem successful fsync semantics. Process exits are tested; hardware
or power-loss simulation is not performed. Checksums are corruption detection,
not signatures. Arbitrary external callback side effects need their own durable
idempotency protocol. Legacy roots without old-prefix proof remain recoverable
but cannot retire or rotate with that unproved sink. Sink file/index limits still
bound retained output. This card acceptance supplies G7 evidence; complete
release gate disposition and the remaining Refactor work stay open.
