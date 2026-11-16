# CROWN continuation handoff

The full Refactor.md implementation goal remains active. The [ledger](task_ledger.md)
is **56 verified / 2 in progress (A02/W06) / 20 not started**, 78 total. A02 license
disposition blocks C04/B01; W06 can continue. No full release is claimed.

The latest [V25 checkpoint](verification/human-inspection-v25-2026-11-13.md) is
`build/verification/human-inspection-v25-progress-v1.json`, with frozen source
`build/verification/human-inspection-v25-source-v1`. Its root packet is
`build/verification/w06-r2-coordinator-implementation-v1`. The detailed previous
state is preserved in [the V24 handoff](handoff-history-v24-2026-11-13.md).

## Current verified behavior

The [SQL aggregate runtime](sql_aggregate_runtime.md) binds original SQL/catalog
and owns one physical-source/native/group prepared transaction. [Whole-image cold
factories](sql_source_images.md) capture and reconstruct every nullable physical
row, including filtered/unused tables, through genuine lowering and final
constraints. Original operational policies remain distinct from finite build
grants; cold owners close before normal-context installation. V24 evidence is
unchanged and protected.

The new [R2 record foundation](sql_aggregate_records.md) adds explicit physical
net-command, Commit/Reject, sink-header and full-key before/after group epochs.
Frames use CROWNAG2, version1, protected lengths/body checksums, real nullable SQL
types and canonical unique complete keys. Empty output closes a whole epoch.
Direct pending input owns one byte buffer plus flat cell/replacement arrays.
WalCursor validates W/I/C and one pending identity without allocation, deriving
a sink floor at each Input. It does not own files, observe D, fsync or replay.

[Receiving gates](verification/w06-r2-records-2026-11-13.md) pass selected strict
Debug 10/10 (43.90s), full ASan/UBSan/leak 10/10 (86.84s), complete OFF Release and
all codec checks through the relocated 222-file public SDK. Seven independent
Python goldens reproduce exactly. All 333 predecessor commands/properties remain
except backtraces; 334 tests are registered. Full 334/Clang execution is unclaimed.
All 20 existing Release SDK archives are byte-identical to V24; the upper codec
adds no native hot-path field, production catch or ordinary update work. No CPU
timing claim follows. All 23 recorder jobs are terminal, 19 successful, zero drift;
four original setup/test failures are retained. Final native inputs: 1157.

## Human inspection

The [source map](code_specs/README.md) has 13,536 contracts in 11,159 of 18,681 blocks,
714 maintained files / 166,049 lines. All 5,749 selected production scopes, examples
and tools have contracts; 2,478 selected existing-test scopes remain. Structural
maps are not full semantic certification. All 83 selected new-code scopes have
specific seven-field cards, backed by source comments and the small codec guide.

This pass adds 261 cards: 163 old-test, 83 codec/API/test/tool and 15 build. It updates
one public-target-list contract semantically and 1,359 source hashes after exact
unchanged-command review. Root independently checks source/old projections,
payloads, anchors and references before adoption. Final code-map checking passes
105,942 local links; current guides have a separate pinned link audit. The compact
primitive index retains detailed cards in per-file pages. No Astra call is used.

## Next actual work

Implement the smallest synchronous durable R2 owner over these records and the
existing cold factory. Read the root packet's `next-implementation.md`, the sealed
`w06-r2-protocol-review-v1/protocol.md`, `actual-apis.md`, `decisive-tests.md`, and
`w06-r2-records-review-v1/review.md` before choosing ports.

First add opaque GenerationOwner::read_checkpoint(account), mirroring actual
read_plan root/hash/stamp/EOF/cap protections. Then build descriptor admission by
bounded-preflighting actual binding CBOR, re-binding original SQL/catalog/typed
parameters/AVG, and requiring exact binding-image/native recipe/policy equality.
A supplied valid tree establishes an upper height bound, not minimum proof.

R2 still needs its own locked WAL/sink owners, full physical checkpoint format,
synchronous coordinator, genuine replay and typed nullable JSONL/CLI. Keep one
owned logged input and one committed canonical output spool. Separate W logged
input, I disposition/source progress, C actual epoch and D actual sink receipt.
Input fsync precedes prepare; Commit fsync precedes nonallocating publication.
Semantic Reject consumes I alone. Resource denial keeps the head; uncertain
WAL/sink/root outcomes require actual reopen/recovery. Checkpoint only at W=I, D=C.
Use real v3 descriptor/actual delivery anchors, enforce C<=I and reject R1 retirement
intents. Validate the full selected set and replay before repairing incomplete
tails. Complete corruption is never repairable. Do not reinterpret R1 receipts or
signed set rows. Varying-int32 column admission remains open.

## Working rules

Never edit maintained native inputs during recorder jobs or overlap build/CTest/
enumeration in one build directory. Archive terminal LastTest before the next
native action. Main Debug/SAN/OFF builds remain reusable; all protected private
builds, SDKs, source and evidence are immutable. Do not rerun an old live-source
postcheck after authorized edits. Adopt through fresh writes. Native commands
require sandbox escalation here. Do not stage/reset/commit Git. Generate maps
before checking them. Record failures and run checks justified by actual changes.
