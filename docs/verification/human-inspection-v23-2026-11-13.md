# Inspectable physical source images and existing tests

The [source index](../code_specs/README.md) maps **707 maintained code files,
164,404 lines and 18,466 blocks**. It contains **12,635 source-pinned semantic
contracts in 10,274 blocks**. Every inventoried line belongs to an inspection
block. All 5,662 selected production scopes and selected example/tool scopes have
contracts; **3,193 selected test scopes** still require individual review.
Other structural scaffolding is mapped without blanket semantic certification.
The [primitive guide](../code_specs/primitives.md) explains usage and cost boundaries.

This checkpoint adds 223 contracts after [V22](human-inspection-v22-2026-11-13.md):
96 result/delta failure-test cards, 97 indexed-session/ingest cards and 30
source-image API/runtime/test/CMake cards. The independent source review reconciles
1,548 exact predecessor cards: 1,547 hash-only and one role-map semantic update.
Root separately reviews 45 offline generator cards after correcting one README
prose literal. All predecessor CMake command bodies remain; nine are added.

The [source image contract](../sql_source_images.md) describes complete physical
nullable bags, original unused/filtered rows, actual source/native metadata,
sequence, quiescence, ownership and limits. The image shares immutable tuple and
program owners and allocates one receiving-account entry vector. It adds no hot
state, cache, handler or additional undo system to existing update primitives.
The cumulative work fields admit table/row/field visits and retained string
extents; they do not establish CPU, map-comparison, RSS or paper complexity bounds.

Root independently verifies zero selected function/type gaps in the changed
runtime/test paths. Fresh generation completes before the final checker runs;
that checker validates hashes, complete line ranges, authored fields and local
links. Neither lexical segmentation nor a passing documentation checker proves
all code behavior. Tests listed by the map are not automatically executed.

The [executed receiving checks](w06-source-images-2026-11-13.md) pass seven focused
tests per strict Debug and full ASan/UBSan/leak profile, complete test-disabled
Release and a relocated 220-file public SDK consumer. Both backends exercise
retention, exact/one-under limits, busy-state rejection and measured allocation
failure/retry. Registration is 331, with all 330 predecessor commands/properties
preserved except line backtraces. Execution of all 331 remains unclaimed.

Comment/diagnostic corrections describe the actual ordinary throwing new fault
seams. The older result/delta changes alter 10/22 diagnostic literals; the new
ingest correction alters 18. Their assertions, calls, control flow and non-literal
tokens remain identical. Literal changes are executable-token changes. The offline
README wording now states this distinction explicitly; exact preimages and
receiving proofs are preserved.

Root packet: `build/verification/w06-source-image-implementation-v1`. Its 25 native
recorder jobs are terminal: 24 successes and one preserved private fixture compile
failure, with no in-command input drift. Two later wording-only paths are recorded
as separate input phases. Seal: `build/verification/human-inspection-v23-progress-v1.json`;
frozen source: `build/verification/human-inspection-v23-source-v1`.

A separate 17-postimage cold-rebuild proposal is sealed and statically reviewed,
with 105 block contracts. It remains private, unadopted and uncompiled at this
checkpoint. No durable recovery is established by source capture or static review.
W06 cold rebuild, versioned R2 operational recovery and varying-int32 admission
remain open. The ledger is 56 verified / two in progress / 20 not started. The
full implementation goal stays active; continue from the [handoff](../handoff.md).
