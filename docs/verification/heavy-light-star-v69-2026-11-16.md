# V69 heavy/light star prototype acceptance

X03 is verified for the opt-in, initially empty, serial exact-set family in
[the public guide](../star.md). The implementation has real heavy/light update
routes, exact generalized H, sparse rebalancing, counted projected groups and an
owning distinct cursor. It preserves the general backend as a separate comparison
route. This accepts a prototype under the literal X03 requirements, with explicit
implementation costs; it does not accept the full P2 theorem or a new release.

## Current source and review scope

Current scope is 878 maintained code/configuration paths: 483 primary paths and
395 test/helper paths, including 400 production files. All 393 earlier production
files retain their exact V68 bytes. Seven new production files implement cold
admission and the owner; three new test files exercise the real native owner.
The only changed old code/configuration files are an appended CMake target/test
section and offline documentation context. The former has an exact V68 prefix;
stripping the named star dictionary/role/routing additions from the latter gives
the exact old AST. [Entry receiving](../../build/verification/continuation-v69-entry-v1/closure.json)
pins the starting source point.

The [V68 full-scope review](full-scope-review-v68-2026-11-16.md) retains its full
and targeted readings of the earlier implementation. This successor reads all
seven new production files and their tests, including admission, ownership,
mutation/inverses, H tracking, reset candidate selection and cursor scheduling.
The [bounded Astra audit](../../build/verification/v69-star-independent-audit-v1/review.txt)
binds the actual pre-repair source and reports its iterator defect; it is not
relabeled as a review of later repaired bytes. The
[repair receiving](../../build/verification/v69-star-repair-receiving-v1/README.md)
checks the concrete successor deltas and evidence, with its prior-author role
explicit. Fresh source reading, inherited review and actual execution remain
separate. There is no universal correctness proof.

## Admission and algorithm

Admission takes a genuine direct-CQ physical plan and an explicit center. The
center contains every query variable exactly once; distinct-table unary satellites
occupy distinct coordinates and filter every hidden variable. Head order and
repetition survive; the exponent uses the number of distinct head variables.
Unsupported near-miss families fail cold admission. There is no 64-coordinate cap,
automatic optimizer registration, SQL star syntax, signed delta or durable owner.

Degrees count center rows independently of satellite membership. The exact
generalized H uses integer thresholds, occupied degree frequencies and two suffix
counts. Label hysteresis bounds light buckets and heavy-key counts. A reset scans
old heavy keys and the relevant occupied degree band, then migrates only changed
labels. It never rebuilds the full star state just because the scale changes.

A light satellite update touches its incident center facts. A heavy satellite
update touches its reverse groups and changes liveness without visiting center
facts or projections. Light-eligible facts contribute counted full-head projections
to one mask/heavy-values group. Enumeration visits live group projections, paces
candidates and deduplicates with a seen set and queue. No eager global output union
or hidden generic join-maintenance owner is retained.

One original finite account owns source state, imported comparison metadata,
indices, inverse records, cursor scratch and owning output. Original constraints
remain enforced on every table. A compact inverse journal and prepared source/H
tokens retain atomic publication and rollback; valid final publication allocates
nothing. The separate cold metadata import grant is capped by all five original
indexed work domains and is never recreated during updates. A writing guard spans
source/H commitment and journal retirement.

## Actual validation

Final strict Release and ASan/UBSan builds both pass for the two added targets.
Each profile then executes the actual registered `star` command and the registered
`star_oracle` command with its capture-only artifact option. Both pass with all
878 code/configuration hashes unchanged. Each unit reports 378,046 checks. Each
oracle reports 32 native cases, 1,824 source events, two backends and agreement with
original full-state CQ/constraint evaluation, independently translated SQLite and
exact integer H. Raw requests, native output and model summaries are retained in
the [Release capture](../../build/verification/v69-star-root-v1/release-acceptance-v1/receiving.json)
and [sanitizer capture](../../build/verification/v69-star-root-v1/sanitizer-acceptance-v1/receiving.json).

Coverage includes every source relation, no-op epochs, Boolean/full/projected and
ordered repeated heads, projection collisions and last witnesses, degree/H
boundaries, promotion/demotion/reset, sparse high degree, 70 coordinates, typed
scalars, source constraints, finite work and indexed row limits, independent owners,
reader leases and returned tuple survival. Each profile tests 198 persistent
allocation-failure prefixes across one/two-promotion cases and both backends,
checking unchanged original sources/results/state and retry on the same owner.
Later cursor failure also preserves an already returned owning tuple.

CTest discovery now lists 389 registrations. The original 387 commands/properties
are unchanged, apart from CTest's scheduling COST observation. V68 actually ran
all 387 in both profiles: 774 successful executions. V69 runs the two added
commands in each profile; it does not claim a new complete 389-test suite.

The [relocated SDK verification](../../build/verification/v69-star-sdk-v1/README.md)
physically moves a 275-file installation and compiles two public consumers with
`find_package(Crown)` and `CROWN::star`. Compiler/link dependencies resolve only
through the moved headers and byte-identical producer archives. All 155 installed
Crown headers match source. Four held-out comparisons use separate genuine general
and star owners across reference/indexed sources and M=32/512; 48 full-source and
full-output checkpoints agree. Every sparse-reset trigger records exactly one
reset, five migrated rows, 11 center visits and 102 selected work units, at both
sizes. Heavy satellite erase/reinsert records zero center visits, one group visit
and six selected units; light erase records one center visit, no group visit and
nine units. These discriminate actual work paths, not wall-clock speedup.

## Findings, corrections and limits

The initial failed native runs remain under `*-checks-v1`; passing later runs do
not erase them. The unit's degree-zero key expectation was corrected because a
still-present satellite must retain its key. The oracle exposed missing funded
original-program metadata import for indexed plans; the cold grant fixes it.

The independent audit found that insertion undo retained an iterator invalidated
by extraction/reinsertion. Undo now retains a stable value pointer and performs a
fresh reverse lookup, under the journal's parent-before-child restoration order.
A further H-token review found retired histogram iterators surviving commitment;
commit and moves now clear inactive dependencies. Focused libstdc++ debug controls
reproduce each old-source iterator failure and pass on the correction:
[journal](../../build/verification/v69-star-root-v1/journal-debug-control-v1/receiving.json),
[H token](../../build/verification/v69-star-root-v1/hindex-debug-control-v1/receiving.json).
These controls exercise private header primitives, with opaque native core linkage;
they are not an entire debug-library rebuild. Old native executables were not
copied before relinking; exact old sources, command logs and failure receipts are
retained instead.

P2 is pinned arXiv:2603.14754v1. Definition 4.5 p14 supplies the literal family;
Theorem 1.4 p3 states update O(h^(d-1)) and delay O(h^(d-j)) under its premises.
The [primary audit](../../build/verification/v68-star-proof-v1/audit.txt) separates
the paper's rebuild/projection/histogram gaps from local repairs. The actual cursor
uses at most O_d((h+1)^(d-j)) selected candidates per production step, with j distinct
head variables. Ordered-container logarithms, scalar widths, allocation/account
work, H threshold spans, source constraints, startup, cleanup and last-owner
destruction remain explicit additional costs. Full heads have candidate quantum
one; this does not imply end-to-end constant delay. No blanket P2 theorem, matching
lower bound or measured speedup is claimed.

Static source arguments cover the complete writing-guard lifetime and all five
cold metadata caps. Native tests do not independently inject every allocator
callback or isolate every metadata cap. Finite oracle/fault traces complement
these arguments and cannot cover every supported update sequence.

## Human inspection and continuation

The [source maps](../code_specs/README.md) cover 876 files, 197,708 lines and 21,941
regions. All 18,669 nonblank regions have scoped usage contracts; 3,272 blank
regions retain structural descriptions. The registry has 21,166 contracts:
240 newly authored cards, 1,789 old source/anchor rebindings including seven
semantic context/routing amendments, and 19,137 unrelated records preserved
exactly. Generator/checker results, exact candidate lineage and independent
[spec receiving](../../build/verification/v69-star-spec-receiving-v1/README.md)
remain separate from native execution. Each card states purpose, input/output,
invariants, ownership, failure, cost and references. Paper authority is distinguished
from local engineering. These offline maps add no runtime work.

The implementation goal remains active. X03 is verified; X04, X06 and X08 remain
open. Approximation and parallel/distributed execution stay deferred. The multi-query
interface keeps independent serial owners. R1/R2 frozen sources, SDKs and decisions
retain their original vintages; V69 accepts no new release. The
[handoff](../handoff.md) points to the current source/evidence join.
