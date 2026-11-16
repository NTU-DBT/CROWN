# CROWN continuation handoff — V69 heavy/light star prototype

The Refactor implementation goal remains **ACTIVE**. Ledger:
**72 verified / 1 in progress (A02) / 5 not started / 78 total**.
X03 is verified within the exact scope and costs of the
[V69 acceptance](verification/heavy-light-star-v69-2026-11-16.md).
The [V68 handoff](handoff-history-v68-2026-11-16.md) preserves the prior complete
current-code review and 387-test profiles.

## Current implementation

`CROWN::star` is opt-in cold admission plus an initially empty serial exact-set
owner for literal center-plus-unary CQs. Read [the guide](star.md) before using
`planner::star::admit` and `runtime::star::Runtime`. It retains all original source
tables/constraints and original comparison metadata, with one private source-only
coordinator. General execution remains a separate comparison route.

Light updates visit incident center rows; heavy updates visit reverse groups.
Exact generalized H uses occupied degree buckets/two suffixes. Hysteresis and sparse
scale resets migrate changed labels only. Counted per-group head projections and
a paced seen/queue cursor preserve DISTINCT projection and repeated head positions.
All retained native work uses the original query account. There is one inverse
journal, no whole-star state clone or catch/retry framework. Publication is prepaid;
a writing guard spans source/H commit and journal retirement.

All 393 old production files remain exact V68. Seven new production files and
three tests are added; old CMake only appends target/install/test metadata and the
offline context helper gains explicit star entries/routes. Current inventory:
878 code/configuration paths, 483 primary, 395 test/helper, 400 production.

## Actual verification and inspection

Final Release and ASan/UBSan star builds pass. Each profile passes both added
registered commands: 378,046 unit checks and 32 original-query oracle cases with
1,824 source events across two backends. Native output, source snapshots, SQLite
and exact H models agree. Each unit covers 198 persistent allocation prefixes,
same-owner retry, cursor failure after a retained output, source constraints,
wide/typed/repeated projection, labels and real branch counters.

The original 387 registrations are unchanged; CTest now lists 389. V68 ran the
complete 387 in both profiles (774 passes). V69 executes only the two added commands
per profile and does not claim a new full 389 suite. Current code/configuration
hashes remain stable across the final builds/executions.

A 275-file installed SDK is physically relocated. Two public consumers pass;
all 155 installed Crown headers match source and linked archives match producer
bytes. Four held-out genuine general/star comparisons produce 48 matching full
source/output checkpoints. M=32/512 reset triggers each show 1 reset, 5 migrated rows,
11 center visits, 102 selected work; heavy satellite changes use 0 center visits / 1 group visit / 6 selected work units.
These discriminate paths rather than prove a timing speedup.

The saved initial failures remain: an incorrect degree-zero unit expectation,
missing funded indexed metadata import, invalid journal insertion-undo iterator,
and retired H-token iterator dependencies. Corrections pass final native checks;
two focused libstdc++ debug old/fixed controls reproduce then eliminate the iterator
failures. Exact old sources/logs are retained; old native executables were not copied
before relinking. The pre-repair Astra audit and scoped successor receiving have
separate source pins and reviewer-role limits.

Source maps cover876 files /197,708 lines /21,941 regions. All 18,669 nonblank regions
have usage contracts; 3,272 blank regions retain structural descriptions. There are
21,166 authored contracts: 240 new, 1,789 old rebindings with seven semantic wrapper
amendments, 19,137 unrelated records exact. Canonical registry SHA-256:
`0af0aae073b51c5d4930862f0021e2674571ecb65733ace2cc1b2398fdf44bc5`.
Offline generator/checker and independent source/card receiving pass; they add no
runtime checks or overhead.

## Source, evidence and next work

The new root packet is `build/verification/v69-star-root-v1`. It retains actual
build/check revisions, final registered-command captures, old-source controls,
contract lineage, source-point providers and final document checks. Independent
SDK/spec/repair packets are siblings. Final progress/postseal paths are
`build/verification/human-inspection-v69-progress-v1.json` and
`build/verification/human-inspection-v69-postseal-v1.json`.
The V69 source point reuses immutable V68 per-file providers for exact files and
an explicit new overlay for changed/added bytes. Preserve all earlier closed
packets, source/SDK images and R1/R2 decisions. No new release is accepted here.

P2 Definition 4.5 p14 supplies the literal family; Theorem 1.4 p3 states its own bounds.
Local group/sparse-reset/H/cursor repairs are separate. Candidate pacing has actual
exponent d-j with j distinct head variables; ordered maps, scalar width, allocation,
source constraints, H threshold spans, startup and cleanup remain additional costs.
No full P2, new optimum, universal correctness or end-to-end constant-delay claim.

Continue X04 comparison predicates, X06 explicit fallback and X08 difference under
their literal requirements. Ordinary propagation/exact recomputation is permitted.
Approximation and parallel/distributed execution stay deferred; multi-query keeps
independent serial owners. Keep code direct and performant, and update source-bound
usage specs with actual paper/local-engineering attribution. Use own-model disjoint
agents; Astra Max only for occasional hard audits, Luna Max for mechanical work.
Git metadata/closed evidence are read-only. Set PYTHONDONTWRITEBYTECODE=1 and use
the escalated shell path because default bwrap fails. Producer builds stay mutable.
