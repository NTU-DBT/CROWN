# P06 owned exact-search continuations, 2026-11-06

P06 is implemented and acceptance-verified. The full 78-card goal remains
active: 34 verified, two in progress (A02/O06), 42 not started. This internal
acceptance is not external V02 review, a release or durable recovery signoff.

Work remains uncommitted on master at baseline
`e369a623517723b3be3ea3e9806779f3c591e7f9`. Original Refactor.md and legacy
trees are preserved. Requirements: [Refactor.md](../../Refactor.md), P06.
The [P04 packet](planner-fast-paths-2026-11-06.md) and its 529-input seal are
historical, unchanged. The saved [preflight](p06-design-preflight-2026-11-06.md),
[transition plan](p06-transition-plan-2026-11-06.md) and
[implementation seams](p06-implementation-seams-2026-11-06.md) document the design
and resolved routine choices; actual source and evidence take precedence.

## Implementation and independent arguments

Root implemented the [public API](../../include/crown/planner/search.hpp),
[facades/strict adapters](../../src/planner/search_session.cpp),
[resource ledger](../../src/planner/continuation_budget.hpp) and
[typed IO](../../src/io/search.cpp). Separate Astra owners implemented the
[producer/witness](../../src/planner/exact.cpp),
[independent replay](../../src/planner/certificate.cpp) and
[independent P02 cursor](../../src/planner/verify.cpp). Luna Max extracted the
actual private v1 baseline and authored independent semantic/OOM/edge/IO cases.
A fresh Astra reviewer checked actual source, preserved mathematics, authority,
lifecycle, retries, IO and written arguments. Findings below are resolved and
conditional source clearance is satisfied by the final matrix.

ExactSearch owns real preprocessing, hierarchy, partition/root/child enumeration,
memo, witness and proof-export positions. Producer coroutine frames execute
allocating operations outside resume as retryable saved operations; the code
between yields is nonallocating. Independent replay owns manual jobs and its
separate smallest-remaining block/complement enumeration. P02 owns explicit scan,
reachability/property/connectivity/connex/report-export positions. No grant
restarts a completed prefix. No checker uses producer metadata or enumeration.
The immutable ports cache publishes only independently completed records.

P04 singleton/constant/hierarchy/component/symmetry/incumbent preservation rules
and v1/v2 certificate meaning remain unchanged. A separate v1 testing translation
unit retains the old labelled-state baseline and budget, while literal P03 stays
unchanged. Production compiles its machines/adapters once and exposes no baseline
control. See [proofs](../planner_proofs.md) and the
[continuation contract](../planner_continuations.md).

ValidatedIncumbent owns only a complete P02-checked upper witness. VerifiedOptimum
adds matching completed independent lower proof; VerifiedInfeasible proves the
empty admissible family without an upper tree. Constructors are private and
payloads immutable/owning. Strict policy withholds incumbent handles; best-found
may expose the last validated upper while search/replay is incomplete. The lower
bound stays universal zero/one until complete independent replay. A partial memo,
visited alternatives or an incumbent cannot become optimum authority.

Admission owns exact catalog/query/options/proof binding; resume accepts no
replacement. Per-call grants and cumulative producer/replay work/active time and
logical depth are distinct. Extensions are monotone, consumed counters never
reset and zero grants perform no allocation, clock sample or transition.
Persistent OOM returns a fixed enum, retains the same pending transition and old
upper handle, then resumes the same owner after recovery. Cancellation frees live
frames leaf-first; a flat ChoiceArena with nonowning child links avoids recursive
payload teardown. Published handles survive facade destruction. Cancellation
retains checked-claim/structural/peak/work history and resets current depth.

The default continuation_v1 allowance is ten million controlled transitions per
phase. Explicit ceilings remain exact. This finer accounting includes controlled
validation/copy/traversal and scheduling, and is not numerically comparable with
old P03/P04 charges. Before final freeze the mandatory nine-atom height-three
case measured producer6076513/replay4430380 after independent ports caching;
uncached replay was14224887. The historical P04 reference was1295117/3414349.
These are diagnostic observations, not complexity or stable-counter promises.

Input admission, serialization, cancellation/destruction and ordinary allocator/
container/scalar-width costs remain explicit separate costs. Active clocks exclude
caller pauses; checkpoints are cooperative, not hard CPU deadlines. Complete
memory/capacity limits remain S05. Legacy aggregate/error conversion can itself
throw bad_alloc and never returns a partially certified result.

Typed progress/upper documents use a separate strict schema and always have
certificate:null. Strict progress has no incumbent. Typed optimum/infeasibility
writers alone export ordinary height certificates. Exact CQ/catalog bindings
retain primitive v1, date/decimal v2 and metadata v3 content. Mutable progress or
JSON cannot construct a verified authority. No new user CLI command is required.

## Independent acceptance cases

Four representative P03/private-v1/v2 families run whole, unit and varied grants;
completed transition counts and results agree. The existing371+7 literal cases,
residual-seven/nine minima3, true hierarchy/component/symmetry/prune cases,
wide/deep/corruption/resource and legacy codec/CLI cases remain covered.
Pauses occur inside producer, witness, P02, export and independent replay. A
separate zero-replay ceiling deliberately stops after producer completion:
strict exposes no authority, then the same owner completes after extension.
No test assumes replay must cost more work than producer.

Owned caller-input/proof mutations, immutable handle types/lifetimes, moved-from
owners, repeated zero grants, monotone/invalid extensions and honest bounds pass.
Standalone v1/v2 replay succeeds and rejects corrupt algorithms, root/members,
flags/orbits/bounds and upper claims. Empty body completes at logical depth0;
nonempty depth0 retains/resumes. Both facade clocks exclude2.5-second caller-idle
intervals. A150-scope hierarchy with unbounded logical depth retains a valid
height-one upper after owner teardown. Cancellation after nonzero depth/checked
claims preserves history and releases current depth.

All observed advance-allocation positions are swept without a cap:

| Actual owned path | Fault positions / successful advance allocations |
| --- | --- |
| Hierarchical search | 264 |
| Connected duplicate/nonhierarchical search | 1283 |
| Infeasible search | 424 |
| Independent v2 replay | 509 |
| Independent v1 replay | 534 |
| Infeasibility replay | 180 |

Failure remains armed through two retries/unwind. The same owner then resumes to
the identical complete certificate, preserving committed transitions and charging
attempt/failure counts. Incumbent replacement retains the previous validated
upper. Replay failures cover indexing, dependency publication and final owning
authority preparation. Progress/zero grants/moves/owning handle copies/cancel/
destruction remain allocation-free under persistent failure. These are observed
positions, not API allocation guarantees.

Typed IO validates14 actual progress/upper/certificate documents, including exact
v1/v2/v3 binding, and rejects six authority/limit mutations. Actual strict native
read/replay checks complement structural schema validation.

## Resolved integration findings and retained failed attempt

Initial compatibility found the missing legacy replay-reason prefix and repeated
independent ports costs. The prefix is preserved; caching retains independent
ports semantics. Work default/accounting is explicitly revised as above, not
silently extended on a resource stop. Every mandatory residual case still proves
height3 under the default. Old tests based on relative work totals now force the
actual replay interruption with its separate allowance.

Fresh source review found an empty-body depth-one dispatch and recursive shared
child ownership. Empty replay now needs/reports depth0; flat arena records plus
leaf-first coroutine cancellation remove that teardown path. IO review found
cancelled replay's checked-claim reset and retained live depth; history is now
saved and current depth cleared. Corresponding edge regressions pass.

The first new OOM fixture incorrectly included legacy attempted-work aliases in
its unchanged-cursor comparison. It now excludes only those aliases while keeping
explicit attempt/failure/commit assertions and full zero-grant snapshots. The
final matrix's first attempt exposed GCC's maybe-uninitialized diagnostic for
optional<ValidatedIncumbent> copy in that fixture. Explicit value-initialization
plus conditional emplace preserves the owning copy; warnings remain enabled.
Actual optimized target and all six sweeps pass unchanged (0.67s targeted).

Attempt-one Release/clean builds failed; the other three exact process groups
were explicitly stopped before source edits. All five handles ended, and the
clean temporary tree was removed. Logs/freeze/partial raw output/disposition are
retained under ignored planner-continuations-attempt-1/. That attempt is not
acceptance evidence. Final attempt two below uses the repaired source.

## Final five-configuration matrix

All jobs are terminal/closed. Every before/after native/test fingerprint matches
455 frozen inputs:
`08d2908231152172c9605e57fb27d8a14915c46dde7adf0dc4c86d207a53220c`.
The digest is sorted path/NUL/content/NUL over CMakeLists/CMakePresets and
include/src/apps/tests/cmake, excluding Python caches. No native source changed
while any final job ran.

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC13.3.0 Debug | 86/86 pass | 230.95s |
| GCC13.3.0 Release | 86/86 pass | 32.98s |
| ASan/UBSan, including external parser C | 86/86 pass | 1000.27s |
| Clang18.1.3 C/C++ Debug | 86/86 pass | 176.72s |
| Fresh source-only Release | 86/86 pass | 32.62s |

Clean verification took418.56s (418.63s wrapper), stages1.01/384.76/32.64, and
removed /tmp/crown-clean-source-94d1xqx2. Four in-place runs retain full passing
stdout/counters; source-only output retains its complete aggregate rather than
all passing-test stdout. Stage/raw/per-configuration/aggregate evidence and
independent matrix audit are under ignored build/verification/planner-continuations-*.
Production has zero private-baseline exports versus one testing export; public
minimum_tree/verify_height_certificate each have one defining production object.
Runtime probes remain zero production versus eleven testing definitions.
Actual compiler versions and sanitizer coverage, including new sources/tests and
external parser C recipe, are independently inspected.

Final Release schema audit passes22meta,26normalized,19identity,17height,
59admission,2layout/projection,31physical,3support,2rejected,2input and3diagnostic
artifacts. Real legacy v1 schema/native read/replay remains exercised. D04 raw
2712/1408/2504 rows and qualified D05 N2/64 profiles remain; allocation counts
from old paths are re-observed, not assumed numerically stable after P02 changes.

## Source seal, full-goal status and next work

The [546-input manifest](planner-continuations-sources.sha256) covers final
code/tests, schema/tool/dependency inputs and ordinary documentation. It adds17
paths to the historical P04 inventory. Verification/handoff/ledger/caches are
excluded to avoid circular evidence hashes. Manifest SHA-256:
`93f07d7ce236804aff148d19eebd9c8f7fdf1bd85056113c8c5933e156314536`.
Original Refactor.md SHA remains
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.
All historical manifest files are preserved and never resealed against new code.
Final independent Luna Max audit passes all546 checksums, exact independently
rediscovered inventory,455-input native fingerprint, original requirements,
six historical manifest-file hashes and78 unique ledger rows at34/2/42. Across
63 Markdown documents all494 local destination occurrences resolve to153 unique
local target paths;17 external destinations were excluded. The initial default-
allowance check was a line-wrap matcher issue and was corrected in audit code
only; documentation/source/seal bytes did not change. Full checksum output and
audit JSON remain in ignored build evidence. Independent matrix review confirms
all86 pass markers/zero failures per in-place run and77 identical counter rows;
clean-source evidence is aggregate-only with verified temporary removal.

The full goal remains active at34verified/2in_progress/42not_started/78total.
Continue with P05 using its [design preflight](p05-design-preflight-2026-11-06.md).
Implement faithful frozen-ear traces, induced heads/identity and sound checked
reconstruction plus full-original-query exact fallback; round counts never
establish minimum authority. P05 is not implemented by its preflight. S04's A02
dependency and release/external-review obligations remain distinct work.
