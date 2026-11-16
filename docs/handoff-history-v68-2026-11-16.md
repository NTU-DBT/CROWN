# CROWN continuation handoff — V68 current-code correctness review

The Refactor implementation goal remains **ACTIVE**. Ledger:
**71 verified / 1 in progress (A02) / 6 not started / 78 total**.
This review adds no feature or production edit. The
[exact V67 handoff](handoff-history-v67-2026-11-16.md) preserves guarded key
specialization, its targeted native checks, current contracts and relocated SDK.

## Current implementation

Read the [V68 full-scope review](verification/full-scope-review-v68-2026-11-16.md)
for findings, actual source-reading depth and current regression evidence.
All 868 maintained code/configuration paths remain exact V67, including all
393 production files: 389 retain the V65 reviewed bytes, two add V66 exact
snapshot top-k, and two add V67 cold FK/UNIQUE specialization. The source reviews
found no new actionable correctness defect. Fresh targeted reading, inherited
semantic review and actual executions are explicitly distinguished.

The key selector remains opt-in `CROWN::keys`, with enforced constraints,
distinct live witnesses and private-field guards. It retains the general plan
and full source catalog; reduced proof identity belongs to the reduced query.
Existing runtime ownership validates all source after-states, including tables
whose query occurrence was eliminated. Top-k remains exact snapshot sorting.
Each query has independent serial state and budgets.

## Validation and human inspection

Both complete current builds pass. Release and ASan/UBSan each pass **387/387
registered tests: 774 executions, zero failures/skips**. All 868 source/config
hashes, registrations and producer metadata remain unchanged through the runs.
Actual commands, raw output, JUnit and completed receipts are under
`build/verification/v68-full-regression-v1/*-suite-v2`.
The initial suite-v1 producer-path lookup stopped before CTest; the correction
and actual completed runs retain separate records. Historical V66 full385 and
V67 targeted results keep their own vintages.

The source maps still cover 866 files / 195,388 lines / 21,685 regions. All
18,439 nonblank regions have usage contracts; 3,246 blank regions have structural
descriptions. Checking passes with 152,798 generated local links and zero errors.
The 20,926-record registry is unchanged, SHA-256
`ac7f826cc39c9db15396e4451dca91b25f1df98e7c7781f02641c15fe28f3488`.
The successor guide audit includes this handoff and the new review record.

No new exception framework, query-update work or release image is introduced.
Required rollback, borrowed-token lifetime, reader cleanup and uncertain-I/O
boundaries remain. Complete source scans, materialization, scalar comparisons,
allocation and cleanup retain their actual costs; no new paper-bound claim is
made. Original R1/R2 archives and frozen SDK/source evidence remain immutable.

## Preservation and next work

Current code uses the exact V67 frozen source basis at
`build/verification/human-inspection-v67-source-v1`. V68 changes only two guides
and adds the review plus V67 handoff history. Their explicit successor overlay
is `build/verification/human-inspection-v68-documentation-overlay-v1`.
The root joins exact code, reviewer packets, native profiles and final documents
under `build/verification/v68-full-review-root-v1`. Successor progress/postseal:
`build/verification/human-inspection-v68-progress-v1.json` and
`build/verification/human-inspection-v68-postseal-v1.json`.

Continue the literal X03/X04/X06/X08 requirements. X03 star preparation is
unimplemented: `build/verification/v68-star-proof-v1` pins P2 and separates its
stated bounds from the rebuild/projection/histogram gaps and proposed local
repairs. `build/verification/v68-star-oracle-v1` contains unexecuted acceptance
fixtures. These packets grant no feature acceptance. A real implementation
still needs admission, exact degree/H state, rebalancing, resource-safe atomic
updates, output agreement and an honestly qualified delay profile.

Comparisons and difference may use ordinary propagation or exact recomputation.
Approximation, shared-query optimization and parallel/distributed execution stay
deferred. Keep code direct and performant, with source-bound usage specs and
exact paper/local-engineering attribution. Prefer disjoint own-model reviewers;
reserve Astra Max for occasional hard audits and Luna Max for mechanical work.
Git metadata and closed evidence are read-only. Use PYTHONDONTWRITEBYTECODE=1
and the escalated shell path because default bwrap fails. Reusable producer
build directories remain mutable.
