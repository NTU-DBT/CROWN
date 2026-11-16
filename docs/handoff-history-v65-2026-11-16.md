# CROWN continuation handoff — V65 full-scope correctness review

The Refactor implementation goal remains **ACTIVE**. Ledger state is unchanged:
**69 verified / 1 in progress (A02) / 8 not started / 78 total**. V03/V04 retain
their separately documented internal R1/R2 qualification. The
[exact V64 handoff](handoff-history-v64-2026-11-16.md) preserves the accepted
archive/SDK/report/source details and all prior source/test vintages.

## Current source and review

Read the [V65 review](verification/full-scope-review-v65-2026-11-16.md) and
[human inspection guide](code_review.md). All 858 maintained code/configuration
paths have explicit assignment: 472 primary paths, including all 389 production
files, and 386 tests/helpers. Every primary path has full or targeted semantic
body/interface inspection. Most test bodies retain their previous source-bound
review and full-suite authority; no fresh every-line test review is claimed.
Combined per-file coverage, source hashes, arguments and exact depth are under
`build/verification/v65-full-scope-review-v1`.

The current code maps cover 856 files / 193,314 lines / 21,402 regions. All 18,207
nonblank regions have source-bound usage contracts; 3,195 blank regions retain
structural descriptions. The registry has 20,681 records, SHA-256
`cf2104422acfe2e441c781229cd57bcbe53fe4aa298c06dd7776abe6daf886d2`.
Three semantic amendments and 112 hash/anchor changes preserve 20,566 unrelated
records. Root and an independent reader validate all 115 affected anchors.

## Corrections

REC-01: `src/recovery/sql_aggregate_descriptor.cpp` previously mapped the real
binder's resource_limit diagnostic to ImageFault::binding. A valid descriptor
with binding.work_limit=0 reproduced this, while rows reported work. The direct
branch now maps resource refusal to ImageFault::work and other diagnostics to
binding. The unit regression checks all four binder-work domains, account cleanup,
both backends and ordinary/opaque metadata. Independent rebuilt-archive receiving
confirms successful default rebind and identical descriptor bytes. This is a
cold failure-category fix; update algorithms and wire formats stay the same.

RUNTIME-DOC-01: `include/crown/runtime/window.hpp` and its class card now describe
label FIFO, full-row lifetime FIFO and unrestricted order. The two source comment
lines preserve all 1,666 tokens, 11 literals and 211 line positions.

The only code-path successors to V64 are the descriptor implementation, its unit
test and that comment-only header. The descriptor guide, review guide, README,
handoff and generated maps describe the current behavior. The accepted V64
archive is a preserved historical source point and retains the old cold failure
category; these corrections have separate current-source validation.

## Validation and preservation

V65 baseline checks pass: 619 SQLite queries across both backends (1,238 cases /
21,046 snapshots), 1,000 integer/Fraction aggregate cases (23,523 observations),
and 25 window cases (4,000 commands / all five policies). Selected direct
registered-command cohorts pass: runtime/storage 20, recovery 20, compiler/planner
18 Release plus 18 sanitizer, and CLI/tools nine. Initial limited-reading and
runner-selection attempts remain preserved with their dispositions.

After the fix, selected Release and sanitizer targets rebuild and the descriptor,
checkpoint, Session, Session-fault, transaction-crash and aggregate-CLI checks
receive their own receipts under `corrections-v1`. CTest supplies discovery;
these are direct registered script/binary executions. The actual V63 full
383-test Release and 383-test ASan/UBSan runs retain their original source point.
No current full-383 rerun or new timing result is claimed. The later window
comment correction joins the tested header by exact token/literal equality.

V64 progress seal: `build/verification/human-inspection-v64-progress-v1.json`,
SHA `be2201971a2ba29502883b9a9a39b1fdec468a4ba6b15bc1c77d09f0c3695db9`.
Its postseal passed 4,882 source pairs / 39,908 hashed files / zero mismatches.
The V65 receiver, final source inventory, code/link checks and review packet
preserve the successor authority. Closed packets and frozen images remain
immutable; producer builds and private consumer/build staging remain reusable.

## Next work

Follow the literal X02–X06/X08 criteria and user priorities for a separately
reviewed exact extension. Comparisons, snapshot top-k and difference may use
ordinary propagation or exact recomputation. Keep the interface and each query's
state/budget independent. Approximation, shared-query optimization and parallel/
distributed execution remain deferred. The implementation goal stays active.

Keep code direct and costs explicit. Preserve source-bound specs with each
behavioral change; do not replace semantic review with hash rebinding. Use disjoint
parallel readers and own-model reasoning; reserve Astra Max for occasional hard
audits and use Luna Max for mechanical work. Git metadata is read-only here;
use PYTHONDONTWRITEBYTECODE=1 and the escalated shell path because default bwrap
fails. Preserve completed receipts and use new versioned attempts.
