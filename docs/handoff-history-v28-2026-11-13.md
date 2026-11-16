# CROWN continuation handoff

The full Refactor.md goal remains active. The [ledger](task_ledger.md) is
**56 verified / 2 in progress (A02/W06) / 20 not started**, 78 total. A02 license
work blocks C04/B01; W06 can continue. No full release is claimed.

Latest [V28 checkpoint](verification/human-inspection-v28-2026-11-13.md):
`build/verification/human-inspection-v28-progress-v1.json`, frozen source
`build/verification/human-inspection-v28-source-v1`, root packet
`build/verification/existing-tests-inspection-v28-implementation-v1`.
Previous detailed implementation state is preserved in
[V27 history](handoff-history-v27-2026-11-13.md).

## Current actual implementation

The [composed SQL runtime](sql_aggregate_runtime.md), complete physical capture
and [genuine cold rebuild](sql_source_images.md), [R2 records](sql_aggregate_records.md),
[genuine descriptor](sql_aggregate_descriptor.md) and
[complete physical checkpoint](sql_aggregate_checkpoint.md) remain implemented.
They retain original nullable physical bags, filtered/unused sources, original
normal policies and separate runtime C/command I/source/reader progress.
Checkpoint restore inspects/matches complete expected data before receiving
allocation, then rebuilds through actual source/native/group factories once at C.
Metadata/snapshot/anchor DTOs remain data rather than durable ownership.

V27's [receiving gates](verification/w06-r2-checkpoint-2026-11-13.md) remain the
latest native checkpoint acceptance: strict Debug 8/8 (120.65s), full
ASan/UBSan/leak 8/8 (243.39s), complete OFF Release and relocated 224-file SDK,
including producer/descriptor/frame lifetime and the exact next removal.
Independent checkpoint SQL modes each perform 3,634 serialized restorations;
the full wire golden is 611 bytes. All 336 prior registrations are retained,
339 registered. The historical packet preserves all 23 jobs (21 successful,
both original failures and fixes). Full 339/Clang/CPU timing/R2 durability
acceptance is unclaimed. Protected SDKs/private builds remain unchanged.

## Current human inspection

The [map](code_specs/README.md) has **14,497 scoped contracts** across **723
files, 167,259 lines and 18,865 blocks**. All selected production,
example and tool regions have cards; **1,666 selected existing-test regions
remain**. Structural partitioning and card presence are not complete semantic
proof. This pass adds 557 cards across 63 files: 261 storage, 213 Python/example,
52 legacy file-test and 31 reference-core contracts. Existing 13,940 records/order remain.

Root authors/implements and verifies; Luna handles bounded reviews and a normal
model supplies deeper review. No Astra call is used. The original generic
batch of 213 Python contracts was rejected without adoption; a fresh normal-model amendment
individually replaces every card. Six findings in the 52 root-authored contracts are resolved.
A fresh root storage amendment clarifies revision-normalized retry assertions
without mutating the completed author packet. Exact sources, objects, fields,
anchors, local references, complete payloads and global key uniqueness pass.

Seven test/helper files change only comments and eight diagnostic strings:
15 exact substitutions. Native input scope has 1,167 paths; production source
and all statement/control/ownership logic remain unchanged by token/AST proof.
No native/test/build/configure/install or fixture execution occurs in V28.
The generated-map and fixed current-guide link audits pass; no runtime state,
handler, instrumentation, grant or update overhead is introduced.

## Next work

Continue individual test inspection while implementing actual W06 durability.
Read the V27 root packet's `next-implementation.md` and immutable
`w06-r2-protocol-review-v1/{protocol,actual-apis,decisive-tests}.md`.
Current descriptors/checkpoints/transport do not own actual R2 durability.

Add concrete R2 WAL/sink file owners and synchronous coordination with one
owned logged Input and one committed canonical output spool. Separate W logged,
I disposition/progress, C actual epoch and D actual sink receipt. Log only at
W=I,D=C. Fund Input/progress publication before Input fsync; prepare the actual
token/output/Commit bytes before Commit fsync, then publish that same funded
token/frontiers without allocation. Stable semantic Reject consumes I alone;
resource denial retains the identical head. Uncertain I/O requires actual reopen.

The sink must privately create its genuine Receipt. Require v3 descriptor hash,
C≤I, actual D=C checkpoint coverage and no R1 retirement intent. Each Input
implies prior sink_floor=C. Validate complete frames, genuine decisions/output,
EOF/stamps/root and actual sink coverage before tail repair. Complete corruption
and complete pending Input are never repairable suffixes. Publish synced
descriptor/checkpoint/new WAL before root selection. GenerationOwner authenticates
selected opaque bytes; it neither creates/validates WAL nor enforces R2 semantics.
Use finite history caps until R2 retirement exists. Add nullable JSONL/CLI resuming
after logged W, including pending reader position. Varying-int32 admission and
full release reviews remain open.

## Working rules

No maintained native edits during recorder jobs; no overlapping build/CTest/
enumeration in one build directory. Archive terminal LastTest before the next
native action. Main Debug/SAN/OFF builds are reusable; sealed evidence, frozen
source, private builds and SDKs are immutable. After a completion report use a
fresh amendment for corrections. Never rerun old live-source postchecks after
authorized edits. Adopt fresh writes. Do not stage/reset/commit Git. Native
commands need sandbox escalation here. Generate maps before checking; retain
failures and run checks appropriate to actual changes. Goal remains active.
