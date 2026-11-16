# CROWN continuation handoff — V62 R1 technical freeze

The full Refactor implementation goal remains **ACTIVE**. V03 is verified for
the documented internal R1 equality-set scope. The ledger is **68 verified /
1 in progress (A02) / 9 not started / 78 total**. Licensing disposition remains
deferred by the user; preserve existing rights/notices and do not promote A02.

## Current authority

Read the [V62 full-scope review](verification/r1-release-v62-2026-11-15.md),
[R1 method](releases/r1.md), [local technical decision](../build/r1-release-v62-v1/candidate-v1/release-decision.json)
and [task ledger](task_ledger.md). The exact archive SHA-256 is
`e37b89a18b0d79849d2580cb5ff0f74846493d31de801410a92cf77b23293a6a`.
The assembler's metadata remains unqualified; the separate root decision binds
this image. Archived status documents retain their pre-decision vintage.

All 832 maintained code files have current source maps and 20,199 adopted usage
contracts. All 373 production files retain the reviewed V61 bytes. Both complete
376-test suites pass in strict Release and ASan/UBSan, without failures/skips or
source drift. Fresh-source compiler/dependency/target joins, all archive hashes,
all 258 tested SDK files, 74 additional signed/current SQLite prefixes and the
complete qualified report receive exact byte checks. No new timing is claimed.

The exact [pre-release handoff](handoff-history-v62-pre-release-2026-11-15.md)
preserves helper failures, repairs, source vintages and prior session details.
The [V61 handoff](handoff-history-v61-2026-11-15.md) and every completed predecessor
snapshot/packet/private prefix remain immutable. Final V62 progress/source seal
and postseal check are under `build/verification/human-inspection-v62-*`.

## Next work: V04

R2 still lacks a genuine public plain-SELECT-bag durable input/output/checkpoint/
replay workflow. Existing in-memory W05 rows and durable aggregate W06 contracts
remain valid; neither a narrowed in-memory claim nor COUNT(*) substitutes for
the required bag workflow. Exact signed multiplicities need uint64 magnitudes,
including retractions larger than int64. Reuse format-independent generation
ownership; existing aggregate-specific frame/WAL/sink types require a deliberate
typed row counterpart. Keep per-update state/capture bounded and avoid snapshots
or persistent result graphs on the update path.

The sealed future-R2 scope/trial audits are `v62-r2-scope-audit-v1`,
`v62-r2-sdk-trial-design-v1` and `v62-r2-output-capture-audit-v1` under
`build/verification`. An isolated support-capture prototype is complete in
`build/r2-bag-recovery-prototype-v1/source`; its sealed evidence is
`build/verification/v62-r2-support-capture-prototype-v1` (manifest SHA-256
`0f21f800b747334ca7d860e88ca2d251ec61bf9c803face0fb46067e2769da08`).
Both strict Release and ASan/UBSan pass five targeted tests each, including 258
transactions/484 stages in the new test. The patch and 189 contract proposals
are preserved; **no prototype code is adopted** and no R2 release is accepted.
It adds distinct support capture through the existing traversal while numeric
bag capture remains unchanged. All prototype native jobs are terminal.

## Continuation rules

Keep code direct, comments/specs source-bound and performance costs explicit.
Comparisons, top-k and difference may use ordinary change propagation or exact
recomputation. Preserve the multi-query interface with independent serial query
owners. Approximation and parallel/distributed execution remain deferred.
Use parallel agents for disjoint review/implementation; use Astra Max sparingly.

Preserve all completed evidence and use new versioned packet/attempt names.
Only explicitly frozen images are immutable: main producer builds,
`build/r1-release-v62-v1/fresh-source-v1` and the R2 prototype source/build remain
reusable. The accepted `candidate-v1`, its external decision, closed V62 packets
and final source snapshot are protected. Do not glob-protect all of `build`.
Use `PYTHONDONTWRITEBYTECODE=1`; this environment's shell calls require the
escalated execution path because default bwrap fails. Git metadata is read-only.
