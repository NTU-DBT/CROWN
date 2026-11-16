# S05 native acceptance audit

9 November 2026. Refactor.md requires checked capacity/overflow, a per-query
memory budget and statistics, rollback preserving the prior epoch, no logical
history leak under no-op/churn, and memory reports reconciling with actual
operator records. S05 is verified: all five complete native matrices and the
independent source, compiler and executable readback pass.
The full78-card implementation goal remains active.

## Implementation and ownership review

The [query memory contract](../query_memory.md) states the budget domain and
explicit caller/component boundaries. The review follows account creation and
propagation through runtime admission/rebuilds, session/native input, executable
program/replan storage, current-owner ranking/selection and captures. Runtime
paths use the query account; only explicit standalone entry points create a
component account. Native graph/row/container/JSON-token ownership and allocator
types enforce that relationship for arbitrary admitted sizes.

The source review records exact call sites and hashes in
`build/verification/s05-final-native-acceptance-ownership-review-v1.json`.
The688-match compiler/I/O census and raw-allocation search are navigation aids;
they do not replace the code/dataflow review. Native program replanning includes
the separately included program_replan.inc. New internal unfunded paths were
not found. Caller-provided streams/artifacts, initial compiler work, explicit
exports and public exception presentation remain the documented boundaries.

## Requirement-to-evidence audit

| S05 requirement | Implementation and actual evidence |
| --- | --- |
| Checked capacity and overflow | MemoryAccount checks aligned request arithmetic, ceiling and allocation-history overflow before allocation. Support and derivation counters check exact configured limits before incrementing. Native arena/index/delta dimensions use checked limits. memory_account_contract, support/physical/delta exception and resource tests exercise rejection and rollback. |
| One real query-byte budget | Native factories/admission/rebuilds retain one account. Runtime, delta, session, epoch, input/window, observation/statistics, ranking/selection, program/capture and invariant memory tests compare global upstream requests to original-account requests, genuine exact/one-under peaks and same-cap retry. |
| Distinct live/reserved/history statistics | Account purposes/lifetimes and table/arena stats distinguish active/retained/free slots, values, directories, undo/history, actual requested/payload bytes and peak/allocation/free history. Memory reports sum disjoint owner/purpose/lifetime partitions to the account. |
| Valid previous epoch after overflow/OOM | Persistent allocation sweeps cover native storage and each runtime stage, pending/resumed/cancelled operations, alias fan-out and report/copy failure. Independent canonical before/after state, existing outputs and older snapshots remain valid; rollback/publication/release are tested with allocation denied. |
| No no-op/churn logical history leak | Runtime/model/delta/window tests and20-cycle report churn check stable logical state and warmed capacity. Native ownership has no append-only per-owner allocation history. Retained generations and reusable/exhausted slots are explicitly charged rather than counted as live rows. |
| Reports reconcile actual operator records | Actual Support/Physical/Delta/Session reports join canonical record/survivor/P/E/derivation/live-factor counts to real table/index/arena owners. Both backends, three tree shapes, composite buckets, wide NUL/SQL values and corrupted live counts are checked. Report failure publishes no partial partition. |

These are finite correctness/resource checks. They do not establish a process-RSS
ceiling, universal performance bound or a durable delivery/recovery guarantee.
O04–O06 and the remaining task cards keep their independent acceptance criteria.

## Matrix status

All current C++/tool/schema/test inputs match the sealed native invariant
checkpoint. New input1 freezes982 paths, with982 verified preimages. No
production/test/limit/timeout changes have been made for this acceptance run.

| Configuration | Complete registration | Result | Seconds |
| --- | --- | --- | ---: |
| GCC Debug (predecessor source5) |227 |PASS227/227 |911.41 |
| GCC Release |227 |PASS227/227 |155.78 |
| Clang18 Debug |227 |PASS227/227 |749.69 |
| ASan+UBSan/leaks |227 |PASS227/227 |3703.93 |
| Fresh source-only Release (predecessor source5) |227 |PASS227/227 |155.29 |

The sanitizer sweep retained its original7200s timeout and all assertions and
fixtures. Every test job is closed and every terminal CTest stdout is saved.

The reused runs cover the same executable code: predecessor final7 differs
from tested5 only in documentation, and current input1 is unchanged from final7.
The fresh build starts with982 source files and no cache/objects, verifying334
strict project C++ objects,96 parser C objects,27 local libraries and436 native
flag/link records. Its three dependency/build-tool diagnostics match the exact
[pre-existing warning policy](observability-matrix-review-2026-11-07.md), including
counts, archive pin and unchanged extracted sources; no safety/fix claim is made.

Root performs this review directly, with no Astra. Small-agent work remains
unavailable at the existing thread limit. All predecessors, raw results and
source/binary/object evidence remain preserved. Continue from
[the handoff](../handoff.md). S05 is verified; the full goal remains active.

## Independent readback and handoff

`s05-final-native-acceptance-readback-v1.json` verifies984 source paths and982
preserved preimages, all950 actual executables and five caches,20 primary
compiler/link records,982 fresh source files,334 strict C++ objects,96 parser
objects,27 local libraries and436 fresh compiler/link records. It rereads the
predecessor's2470 pinned artifacts and all five raw full-suite results. There is
no executable-source drift from predecessor tested5; final edits are documentation.

All three current acceptance jobs are closed with exit0. Detailed terminal test
stdout is archived. Final source, progress and seal receipts use the
`build/verification/s05-final-native-acceptance-` prefix; earlier checkpoints and
raw failed attempts remain preserved. The ledger is42 verified,2 in progress
(A02/O06),34 not started,78 total. O04 checkpoint/restore is the next dependency;
the isolated row-codec prototype has not completed that card.
