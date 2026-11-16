# CROWN continuation handoff — V67 guarded key-specialization acceptance

The Refactor implementation goal remains **ACTIVE**. Ledger:
**71 verified / 1 in progress (A02) / 6 not started / 78 total**.
X02 now has separately verified key-specialization scope. The
[exact V66 handoff](handoff-history-v66-2026-11-16.md) preserves top-k, the full
current-at-V66 review and both actual complete 385-test profiles. Earlier accepted
R1/R2 images retain their separate qualification and source/test vintages.

## Current implementation

Read [key-aware plans](key_specialization.md) and
[V67 acceptance](verification/key-specialization-v67-2026-11-16.md).
`CROWN::keys` is a cold opt-in compiler over genuine non-null direct-CQ set plans.
It removes a parent occurrence only with enforced FK/UNIQUE authority, exact
matching typed key terms and ignored or fresh once-used private non-key fields.
Sequential distinct live witnesses prevent erasing the final atom of an FK cycle.
Composite/reordered/empty keys and same-table self-FKs have explicit tests.

The returned immutable handle retains the general comparison plan, reduced plan,
original-ID elimination steps and compact new-to-original occurrence/variable
maps. Head order, aliases, repetitions and types survive. Reduced proof/source
identity belongs to the reduced query; it is not an original-query minimum.
Use PhysicalPlan::from_compiled(selection.plan()) for the existing C05 bridge.
Normalized SQL and constant operators remain general, while nullable/weighted/
aggregate interfaces keep their own contracts. No default planning policy or
wire format changes.

The complete original source catalog/constraints survive lowering. Existing
PhysicalRuntime owns all source rows and validates every after-state, including
updates to eliminated referenced tables. Their native alias routes can be empty;
a live alias of the same physical table remains routed. No additional runtime
owner, comparison state, catch/retry framework or per-event optimization hook is
added. Actual cold guard/search/lowering, full source storage and constraint-scan
costs remain explicit; no P5 dynamic update bound or speedup is claimed.

## Validation and human inspection

Both targeted Release and ASan/UBSan builds/checks pass. Each profile reports
1,009 unit checks and 44 native oracle cases (22 queries on both backends),
1,884 events, 1,928 snapshots per native route and 316 expected constraint
rejections. Independent original-CQ Python/SQLite results and full source/sequence
checks agree; raw native outputs are byte-identical across profiles. Registered
commands, actual raw requests/expectations/outputs and source hashes are under
`build/verification/v67-key-root-v1/*-checks-v1`.

An actual relocated Release SDK passes twelve held-out frames, including three
rejections. Independent receiving verifies 423 compiler dependencies (one consumer,
55 SDK headers, 367 system paths), all eleven linked SDK archives and all 271
unchanged SDK files. Only the actual `build/v67-key-sdk-work-v1/relocated SDK`
image is frozen; producer and consumer/build staging remain reusable.

The current maintained code/configuration inventory is 868 paths: 476 primary,
including 393 production files, and 392 tests/helpers. All 391 old production
files retain exact V66 bytes. Two new production files are
`include/crown/planner/keys.hpp` and `src/planner/keys.cpp`; the three new test files
are unit, genuine-native driver and independent oracle. CMake appends only the
optional target/export/tests; the helper adds offline context/roles/routing.

Maps cover **866 files / 195,388 lines / 21,685 regions**. All **18,439 nonblank
regions** have usage contracts; 3,246 blank regions are structurally described.
The 20,926-record registry SHA-256 is
`ac7f826cc39c9db15396e4451dca91b25f1df98e7c7781f02641c15fe28f3488`.
There are 128 new cards, 1,760 old metadata rebindings (two routing amendments)
and twelve citation-only corrections for five stale inherited reference strings.
All 19,026 unrelated records remain exact. Independent receiving validates every
current source binding, local reference range and nonblank region. Generation
and checking pass with 152,798 generated local links.

The design, actual-source/cards, oracle author, final registry and SDK independent
packets are closed. Initial strict-indentation and zero-guard fixture failures,
the exact failed preimage, the temporary-borrow API correction, shifted helper
coverage and inherited citation findings remain honestly dispositioned. No
universal correctness or fresh every-line reread of all old tests is claimed.

All 385 prior test commands/properties remain exact; the new registration count
is 387. V67 executes the two new registered commands per profile. The V66 full
385 Release + 385 sanitizer passes retain their original source point; they are
not renamed full current-387 runs. Original accepted R1/R2 images/decisions remain
immutable. The old R2 archive predates top-k/keys and retains the cold failure
category documented in V65; current source/SDK validation is a separate successor.
No new release image is accepted or externally published.

## Preservation and next work

V67 source snapshot: `build/verification/human-inspection-v67-source-v1`
(4,911 source paths). Final source/guide receiving and root closure:
`build/verification/v67-key-root-v1`. Successor progress and postseal:
`build/verification/human-inspection-v67-progress-v1.json` and
`build/verification/human-inspection-v67-postseal-v1.json`.
Preserve those records, exact frozen source and relocated SDK. Historical pending
receipts keep their original states; final receiving/postseal is authoritative.

Next follow the literal X03/X04/X06/X08 criteria and user priorities. Comparisons
and difference may use ordinary propagation or exact recomputation, with honest
materialization/work costs. Approximation, shared-query optimization and parallel/
distributed execution remain deferred. Each query has independent serial state,
budgets and publication/recovery boundaries.

Keep code direct; add source-bound specs with behavior changes and do not replace
semantic review with hash rebinding. Use disjoint parallel readers and own-model
reasoning; reserve Astra Max for occasional hard audits and Luna Max for mechanical
work. Git metadata is read-only. Use PYTHONDONTWRITEBYTECODE=1 and the escalated
shell path because default bwrap fails. Closed packets/frozen images are immutable;
reusable producer/consumer staging is not protected by broad build globs.
