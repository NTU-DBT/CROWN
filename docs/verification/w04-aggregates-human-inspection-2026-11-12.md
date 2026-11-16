# W04 aggregates and human inspection — 12 November 2026

W04 is verified for the explicit flat typed logical bag input described in
[the aggregate contract](../aggregates.md): COUNT, integer SUM/AVG, input-column
GROUP BY, nullable arguments/keys and owning group value events. A no-FROM
aggregate uses an implicit singleton. Every DISTINCT aggregate form is rejected
explicitly. General SQL bag/NULL admission remains W05; coordinated aggregate
transactions, batches and recovery remain W06. The full Refactor.md objective and
repository-wide individual semantic review remain active.

[Acceptance](../../build/verification/w04-acceptance-v1.json) records 16 requirements.
[Progress and source seal](../../build/verification/w04-progress-v1.json) identify
this checkpoint's exact sources and artifacts. The ledger becomes 55 verified,
one in progress (A02) and 22 not started, 78 total. This is scoped execution and
inspection evidence, with no full release or performance claim.

## Direct implementation

The explicit `crown_aggregate` / installed `CROWN::aggregate` library adds an
immutable aggregate compiler, nullable owned tuple boundary, bounded integer
primitive and one-group replacement runtime. Existing set SQL wire formats and
physical backend admission retain their prior meanings. The compiler resolves
numeric column/group/argument positions, shares repeated argument statistics and
retains stable output names and literal backing. Retained compiler metadata has
an explicit finite account; runtime keys, scratch, nodes and output use their
receiving account. The two forms can use one caller-supplied account.

Group existence uses total multiplicity, separately from non-NULL argument count
and signed sum. COUNT returns checked bigint; SUM(integer) checks bigint range
before publication even when capture is off. SUM(bigint) returns NUMERIC(38,0),
and AVG uses exact sum/count with declared NUMERIC(38,s), s=0..18 and half ties
away. The fixed precision/scale is a local contract. PostgreSQL references in
[the numeric explanation](../aggregates.md#sql-and-numeric-contract) supply the
SQL context; no paper theorem is attributed to these frontend/resource choices.

Updates prepare arithmetic, new keys, requested output and destination-allocator
map nodes before publication. The commit section inserts prepared nodes, copies
inline statistics or erases old state, then advances the epoch. There is no
production catch/undo journal in this runtime and no whole-state copy or full
result scan on each update. Explicit invariant checks recompute complete input
state and may allocate. Const diagnostics reuse scratch; callers serialize
operations on one runtime/account.

Review removed two avoidable costs. Compiler column lookup now borrows its single
relation binding instead of copying the qualifier string. Runtime cleanup clears
output scratch only inside actual rendering; uncaptured updates and early no-ops
do not scan SELECT outputs. New keys/groups and requested output still have their
real allocation/copy costs. Ordered map field/string comparisons, teardown and
full diagnostics are not hidden by selected logical work counters.

## Human contracts and comments

The [inspection index](../code_specs/README.md) maps all 156,013 lines in 677
maintained files to 17,383 contiguous blocks. There are 3,049 manually authored,
source-pinned contracts, including 330 integrated physical/ordered-row contracts,
42 private arithmetic/test contracts and 246 compiler/runtime/test/build
contracts added after the 2,431-card constant-route checkpoint. The last addition
is the compressed SQL COUNT helper. A redundant root packaging-list proposal was
withdrawn; the existing fuller contract remains. Eleven existing CMake cards were source-aware updates; two closures
were precisely reanchored so their cards still describe the original test block.

The four new review packets are
[binding/tuple/public/build](../../build/verification/w04-binding-human-review-v1/review.md),
[runtime](../../build/verification/w04-runtime-human-review-v1/review.md),
[independent oracle](../../build/verification/w04-sql-oracle-author-v1/README.md) and
[native assertions](../../build/verification/w04-runtime-test-review-v1/review.md).
The earlier raw physical packet is preserved; its current-source integration is
recorded separately in `w04-physical-integration-v1`. Contracts explain purpose,
inputs/outputs, invariants, ownership, failures, costs and references. Comments
explain non-obvious boundaries and proofs. Documentation adds no runtime machinery.
Structural-only mapped regions elsewhere are not completed individual reviews.
There are 3,171 selected production blocks still without individual cards
(687 include, 2,427 src and 57 apps); the full human review remains active.

## Native checks

All gates use the same 1,114 current code/build/test inputs, strict GCC C++23
warnings and the profile's declared options. ASan/UBSan enable leak detection and
halt on findings. Test times below are gate elapsed times, not benchmark results.

| Final cohort | Debug | ASan/UBSan/leaks |
| --- | --- | --- |
| Four aggregate tests plus eighteen foundation controls | 22/22, 24.48 s | 22/22, 88.76 s |

Aggregate gates are `aggregate_integer_oracle`, `aggregate_binding`,
`aggregate_runtime` and `aggregate_sql_oracle`. Foundation controls cover W01
annotations, W02 messages/limits, W03 compressed bags/cursor limits, binding,
normalization, admission, physical/runtime exception behavior, lowering, public
API, native programs and the nonempty constant-route regression. Each raw
`w04-final-ctest-{debug,sanitizer}-v1.LastTest.log` was archived
before later CTest/build operations. The exact receipts and log hashes are in
the acceptance/progress records.

The private arithmetic oracle checks 2,542 cases and 31,275 observations per
profile with Python unbounded integers and exact rational rounding. Native
arithmetic/output conversion uses zero heap allocations in its observed scopes.
The aggregate oracle checks 172 expanded SQL-statistic cases / 4,393 snapshots using
actual SQLite 3.45.1 GROUP BY, COUNT and integer SUM. AVG is derived from those
SQL sufficient statistics with exact Fraction rounding; SQLite floating AVG is
unused. Forty-six large-weight cases / 150 snapshots compare native COUNT outputs to
actual compressed-weight SQLite integer SUM(weight) and conditional SUM(weight)
identities: 298 scalar checks, including 58 values above 2^53 and 21 at INT64_MAX.
Their wide SUM/AVG values still use separately labelled Python exact-model
checks. Both oracles cover all nineteen AVG scales, with 38 signed true-last-place
tie histories in the aggregate corpus. There are 329 changed-input epochs with
correctly unchanged visible output.

Native assertions sweep 34 observed constructor/update allocation-failure
positions across grouped/global/no-FROM constructors and new/existing/vanished
groups, plus three snapshot failure positions. Each cohort has a success sentinel
and same-account/runtime retry. These fixture-specific positions are not a global
unique allocation count. State, epoch, current charge, retained outputs and final
controller-only ownership hold. When compiler and runtime accounts are distinct, compiler account statistics
remain unchanged by runtime work. A snapshot remains the final program metadata owner after external
program/runtime release. Exact/one-under receiver peak is 4,594 requested bytes
for its declared cohort. The 512-alias existing-row control observes zero heap
requests and equal selected logical work (168) with capture off; no elapsed CPU
claim follows.

Both W03 backends supply real compressed tuple views; the test explicitly
ingests and retracts them in the aggregate. It does not delete the producer row
or consume an automatic producer delta. An installed consumer links only `CROWN::aggregate`, then
binds, replaces, snapshots, checks invariants and releases a shared finite account.
The install/configure/build/run receipts are separate from the native CTest gates.
All 315 predecessor emitted test definitions and properties, including backtrace
triples, remain after same-profile build-path substitution; four tests append for
319 registered. The [registration audit](../../build/verification/w04-registration-v1/result.json)
reads generated records without rerunning CTest in sealed predecessor builds.

## Evidence limits and preserved corrections

All 160 prior constant-route artifacts and its 2,457 frozen source paths still
match. Older negative probes and failed tests remain negative historical evidence.
Current documentation does not overwrite their conclusions with a positive result.

Five historical W04 syntax/build-command failures are retained with their corrections: a
binding test tried to borrow from a temporary rejected by the public rvalue
restriction; one manual syntax command omitted the vendored JSON include path;
a test helper name collided with `std::bind` through ADL; and the first two
module build commands misspelled the existing constant-route target after the
other targets built. Corrected commands pass, with no input drift. These were
test/command corrections; no failing aggregate behavior was found by the final
native gates. No tests ran after a failed build before a corrected build passed.

The final audit also caught two evidence gaps: large counts originally used
only the Python model, and every-scale wording exceeded six sampled scales.
The preserved v1 gates retain that historical scope. The
[coverage revision](../../build/verification/w04-sql-oracle-coverage-v2/README.md)
adds compressed SQL COUNT checks and all nineteen scales; both complete final
profiles pass on those current scripts. No production change was needed.

This checkpoint does not run all 319 tests, a Release/Clang matrix, a PostgreSQL
server, a latency experiment or W06 crash/recovery integration. Those limits do
not replace their later release/feature gates. The index continues to identify
unreviewed semantic regions rather than assigning them a completion label.
