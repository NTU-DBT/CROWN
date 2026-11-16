# `tests/unit/planner_continuation_test.cpp` — block usage map

[Source](../../../../../tests/unit/planner_continuation_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `5e22e6a5baa6d44043128864aabd45ee49f7bf7a99cf904f93b56461ae9d3d90`. 713 lines partitioned into 42 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/unit/planner_continuation_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 26–28](../../../../../tests/unit/planner_continuation_test.cpp#L26) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 29–29](../../../../../tests/unit/planner_continuation_test.cpp#L29) | Explanatory comments or spacing. |  |
| [B0004 · 30–33](../../../../../tests/unit/planner_continuation_test.cpp#L30) | Type/record definition: struct Fixture |  · [reviewed contract](#b0004) |
| [B0005 · 34–34](../../../../../tests/unit/planner_continuation_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0006 · 35–60](../../../../../tests/unit/planner_continuation_test.cpp#L35) | Callable definition: Fixture scoped_fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls names, begin, end, insert; returns fixture; growth emplace_back, insert, push_back, reserve; 5 loop sites · [reviewed contract](#b0006) |
| [B0007 · 61–61](../../../../../tests/unit/planner_continuation_test.cpp#L61) | Explanatory comments or spacing. |  |
| [B0008 · 62–64](../../../../../tests/unit/planner_continuation_test.cpp#L62) | Callable definition: std::vector&lt;std::vector&lt;std::size_t&gt;&gt; residual_seven() | calls ; returns {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}} · [reviewed contract](#b0008) |
| [B0009 · 65–65](../../../../../tests/unit/planner_continuation_test.cpp#L65) | Explanatory comments or spacing. |  |
| [B0010 · 66–68](../../../../../tests/unit/planner_continuation_test.cpp#L66) | Callable definition: planner::HeightCertificate certificate_of(const planner::OracleResult& result) | calls ; returns {result.algorithm, result.minimum_height, result.tree, result.lower_bounds} · [reviewed contract](#b0010) |
| [B0011 · 69–69](../../../../../tests/unit/planner_continuation_test.cpp#L69) | Explanatory comments or spacing. |  |
| [B0012 · 70–77](../../../../../tests/unit/planner_continuation_test.cpp#L70) | Callable definition: bool same_statistics(const planner::SearchStatistics& a, const planner::SearchStatistics& b) | calls ; returns a.work == b.work && a.states == b.states && a.partitions == b.partitions && · [reviewed contract](#b0012) |
| [B0013 · 78–78](../../../../../tests/unit/planner_continuation_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0014 · 79–85](../../../../../tests/unit/planner_continuation_test.cpp#L79) | Callable definition: bool same_progress(const planner::SearchProgress& a, const planner::SearchProgress& b) | calls same_statistics; returns a.phase == b.phase && a.last_stop == b.last_stop && a.result == b.result && · [reviewed contract](#b0014) |
| [B0015 · 86–86](../../../../../tests/unit/planner_continuation_test.cpp#L86) | Explanatory comments or spacing. |  |
| [B0016 · 87–91](../../../../../tests/unit/planner_continuation_test.cpp#L87) | Callable definition: bool same_progress(const planner::ReplayProgress& a, const planner::ReplayProgress& b) | calls ; returns a.phase == b.phase && a.last_stop == b.last_stop && a.complete == b.complete && · [reviewed contract](#b0016) |
| [B0017 · 92–92](../../../../../tests/unit/planner_continuation_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0018 · 93–109](../../../../../tests/unit/planner_continuation_test.cpp#L93) | Callable definition: void check_monotone(const planner::SearchProgress& before, const planner::SearchProgress& after, const std::string& context) | calls check; guard check(after.producer.attempted &gt;= before.producer.attempted && · [reviewed contract](#b0018) |
| [B0019 · 110–110](../../../../../tests/unit/planner_continuation_test.cpp#L110) | Explanatory comments or spacing. |  |
| [B0020 · 111–122](../../../../../tests/unit/planner_continuation_test.cpp#L111) | Callable definition: void check_monotone(const planner::ReplayProgress& before, const planner::ReplayProgress& after, const std::string& context) | calls check; guard check(after.checked_claims &gt;= before.checked_claims && · [reviewed contract](#b0020) |
| [B0021 · 123–123](../../../../../tests/unit/planner_continuation_test.cpp#L123) | Explanatory comments or spacing. |  |
| [B0022 · 124–124](../../../../../tests/unit/planner_continuation_test.cpp#L124) | Type/record definition: enum class Slicing |  · [reviewed contract](#b0022) |
| [B0023 · 125–125](../../../../../tests/unit/planner_continuation_test.cpp#L125) | Explanatory comments or spacing. |  |
| [B0024 · 126–130](../../../../../tests/unit/planner_continuation_test.cpp#L126) | Type/record definition: struct SearchRun |  · [reviewed contract](#b0024) |
| [B0025 · 131–131](../../../../../tests/unit/planner_continuation_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0026 · 132–138](../../../../../tests/unit/planner_continuation_test.cpp#L132) | Callable definition: planner::ContinuationLimits generous_limits() | calls ; returns limits · [reviewed contract](#b0026) |
| [B0027 · 139–139](../../../../../tests/unit/planner_continuation_test.cpp#L139) | Explanatory comments or spacing. |  |
| [B0028 · 140–180](../../../../../tests/unit/planner_continuation_test.cpp#L140) | Callable definition: SearchRun run_search(const Fixture& fixture, Slicing slicing, planner::SearchPolicy policy = planner::SearchPolicy::strict, plann… | calls generous_limits, std::move, planner::ExactSearch::create, progress; guard check(!owner.incumbent(), "strict policy exposed an incumbent handle");; returns result; growth insert; 1 loop sites · [reviewed contract](#b0028) |
| [B0029 · 181–181](../../../../../tests/unit/planner_continuation_test.cpp#L181) | Explanatory comments or spacing. |  |
| [B0030 · 182–261](../../../../../tests/unit/planner_continuation_test.cpp#L182) | Callable definition: void compare_differential_representatives() | calls scoped_fixture, check, size, planner::minimum_tree; guard check(cases.size() == expected_case_count, "small differential case count changed");; 3 loop sites; source comment (unverified): // Exercise each existing certificate version through the independently · [reviewed contract](#b0030) |
| [B0031 · 262–262](../../../../../tests/unit/planner_continuation_test.cpp#L262) | Explanatory comments or spacing. |  |
| [B0032 · 263–318](../../../../../tests/unit/planner_continuation_test.cpp#L263) | Callable definition: void phase_suspension_and_interval_semantics() | calls scoped_fixture, generous_limits, planner::ExactSearch::create, progress; guard check(upper-&gt;valid() && planner::validate_tree(fixture.catalog, fixture.query, upper-&gt;tree()).valid,; growth insert; 1 loop sites; source comment (unverified): // The seven-atom height-three residual is a compact deeper case that reaches · [reviewed contract](#b0032) |
| [B0033 · 319–319](../../../../../tests/unit/planner_continuation_test.cpp#L319) | Explanatory comments or spacing. |  |
| [B0034 · 320–452](../../../../../tests/unit/planner_continuation_test.cpp#L320) | Callable definition: void replay_phase_coverage_and_corruption() | calls scoped_fixture, planner::minimum_tree, planner::testing::minimum_tree_baseline, certificate_of; guard check(v2_result.minimum_height == 2 && v1_result.minimum_height == 2,; returns entry.occurrences == std::vector&lt;std::size_t&gt;{0, 1, 2} &&; entry.occurrences == std::vector&lt;std::si…; growth insert, push_back; 4 loop sites; source comment (unverified): // Prove that the v1 fixture is actually dispatched as v1, independently of · [reviewed contract](#b0034) |
| [B0035 · 453–453](../../../../../tests/unit/planner_continuation_test.cpp#L453) | Explanatory comments or spacing. |  |
| [B0036 · 454–535](../../../../../tests/unit/planner_continuation_test.cpp#L454) | Callable definition: void ownership_move_and_zero_quantum() | calls scoped_fixture, planner::ExactSearch::create, clear, binding; guard check(bound.valid() && bound.catalog().tables.size() == 2 && bound.query().atoms.size() == 2 &&; 3 loop sites · [reviewed contract](#b0036) |
| [B0037 · 536–536](../../../../../tests/unit/planner_continuation_test.cpp#L536) | Explanatory comments or spacing. |  |
| [B0038 · 537–651](../../../../../tests/unit/planner_continuation_test.cpp#L537) | Callable definition: void resource_stops_and_monotone_extension() | calls scoped_fixture, generous_limits, planner::ExactSearch::create, advance; guard check(stopped.stopped_for == planner::StopReason::total_work &&; 6 loop sites · [reviewed contract](#b0038) |
| [B0039 · 652–652](../../../../../tests/unit/planner_continuation_test.cpp#L652) | Explanatory comments or spacing. |  |
| [B0040 · 653–690](../../../../../tests/unit/planner_continuation_test.cpp#L653) | Callable definition: void wide_dynamic_and_replay_input_ownership() | calls chain, push_back, scoped_fixture, check; guard check(deep.query.variables.size() &gt; 64 && deep.query.atoms.size() &gt; 64 && chain.back().size() &gt; 64,; growth push_back; 3 loop sites · [reviewed contract](#b0040) |
| [B0041 · 691–699](../../../../../tests/unit/planner_continuation_test.cpp#L691) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_convertible_v&lt;planner::ValidatedIncumbent, planner::VerifiedOptimum&gt;);; source comment (unverified): // namespace · [reviewed contract](#b0041) |
| [B0042 · 700–713](../../../../../tests/unit/planner_continuation_test.cpp#L700) | Callable definition: int main() | calls compare_differential_representatives, phase_suspension_and_interval_semantics, replay_phase_coverage_and_corruption, ownership_move_and_zero_quantum; returns 1 · [reviewed contract](#b0042) |

## B0001

[Lines 1–25](../../../../../tests/unit/planner_continuation_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:a3e2d0a04140088ab525b8a86fbf370794a3db5476ee04e59bb2347a7b9c6026
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_continuation_test.cpp: include "crown/api/error.hpp", "crown/planner/search.hpp", "crown/planner/verify.hpp", "planner_probe.hpp", "tree_oracle.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 26–28](../../../../../tests/unit/planner_continuation_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a fixture assertion with its diagnostic when a condition is false. |
| inputs / outputs | Takes a boolean and borrowed message string; returns normally only when the condition is true. |
| invariants | The false branch throws std::runtime_error; it does not convert assertion failures into a status value. |
| ownership | The message is borrowed for the call and no state is retained. |
| failure | Exception construction or message allocation can fail; otherwise the runtime_error escapes to main. |
| cost | One branch on success; the const std::string argument is constructed at the call site before entry even when the assertion passes. Caller-side concatenation/string conversion can allocate on passing checks; runtime_error construction happens only on failure. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0004

[Lines 30–33](../../../../../tests/unit/planner_continuation_test.cpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group the input catalog and query used by these continuation fixtures. |
| inputs / outputs | Owns one Catalog and one Query, returned by value from fixture builders. |
| invariants | The test creates the catalog/query explicitly; this wrapper adds no validation or planner authority. |
| ownership | Both members are owned values; planner admission later snapshots its input. |
| failure | Member allocation during fixture construction can throw. |
| cost | Fixed wrapper plus the variable-sized catalog/query data. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0006

[Lines 35–60](../../../../../tests/unit/planner_continuation_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a catalog/query fixture from numbered scopes and output variables. |
| inputs / outputs | Reads ordered scope and head vectors; returns tables, atoms, variables and head columns using generated names. |
| invariants | Names are collected into a sorted set, then \`ids.at(original_value)\` is used: current inputs must be dense zero-based labels. Scope and head ordering is retained in atom terms and outputs. |
| ownership | All output model data is owned by the returned Fixture; local IDs are temporary. |
| failure | Out-of-range sparse labels throw from \`at\`; vector/string allocations can throw. |
| cost | Visits each scope/head occurrence and creates one variable per distinct label plus table/atom metadata. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0008

[Lines 62–64](../../../../../tests/unit/planner_continuation_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::vector<std::size_t>> residual_seven() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the fixed seven-scope residual case used to reach a deeper exact-search path. |
| inputs / outputs | Returns seven hard-coded ordered scopes as a new vector. |
| invariants | The expected labels are dense and correspond to the later head \`{0,1,6}\`; this is a single deterministic test instance. |
| ownership | The vector owns its rows and labels. |
| failure | Allocation can throw. |
| cost | Copies a fixed seven-row fixture. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0010

[Lines 66–68](../../../../../tests/unit/planner_continuation_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::HeightCertificate certificate_of(const planner::OracleResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an OracleResult into the HeightCertificate value used by replay. |
| inputs / outputs | Copies algorithm, optional minimum height, tree and lower-bound entries from the result. |
| invariants | This is a field projection; it does not itself verify the result or establish checked authority. |
| ownership | The returned certificate owns copied value data. |
| failure | Copy/allocation failures propagate. |
| cost | Linear in the tree and lower-bound payload copied. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0012

[Lines 70–77](../../../../../tests/unit/planner_continuation_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_statistics(const planner::SearchStatistics& a, const planner::SearchStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the structural/certificate work counters selected by this test. |
| inputs / outputs | Reads two SearchStatistics values and returns equality across work, states, partitions, candidates, cache/certificate/hierarchy/singleton/empty-body/component/symmetry/bound-prune fields. |
| invariants | Only the named fields participate; future or omitted fields are not asserted equal. |
| ownership | Both statistic values are borrowed. |
| failure | No exception handling; ordinary comparison is non-throwing for these scalar fields. |
| cost | Fixed number of scalar comparisons. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0014

[Lines 79–85](../../../../../tests/unit/planner_continuation_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_progress(const planner::SearchProgress& a, const planner::SearchProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the selected public search-progress snapshots around inert zero-work/time grants. |
| inputs / outputs | Reads phase, stop, result, interval, producer/proof completion, producer/replay counters, selected structural statistics and limit revision. |
| invariants | Equality is limited to those public progress fields; it does not compare every object byte or elapsed wall time. |
| ownership | Progress snapshots are borrowed values. |
| failure | Nested comparisons are non-throwing scalar/value comparisons. |
| cost | Fixed field comparisons plus same_statistics. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0016

[Lines 87–91](../../../../../tests/unit/planner_continuation_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_progress(const planner::ReplayProgress& a, const planner::ReplayProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare selected replay-progress snapshots around an inert zero-work grant. |
| inputs / outputs | Reads phase, stop, completion, validity, checked-claim count, work counters and limit revision. |
| invariants | It checks this listed semantic summary, not private replay state or proof bytes. |
| ownership | Snapshots are borrowed. |
| failure | No exception handling; ordinary value comparisons apply. |
| cost | Fixed field comparisons. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0018

[Lines 93–109](../../../../../tests/unit/planner_continuation_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_monotone(const planner::SearchProgress& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert monotonic producer and replay histories across one search advance. |
| inputs / outputs | Compares producer/replay attempts, committed transitions, allocation failures, active nanoseconds, peak depth and limit revision before/after. |
| invariants | Current depth, phase, result and other progress fields may change and are not part of this monotonicity check. |
| ownership | Progress snapshots and context text are borrowed. |
| failure | A regression throws through check; message construction can allocate. |
| cost | Fixed counter comparisons. Each context + diagnostic expression passed to check is formed before the check, including when the counters are monotone; string work/allocation is test-harness cost. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0020

[Lines 111–122](../../../../../tests/unit/planner_continuation_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_monotone(const planner::ReplayProgress& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert monotonic replay history and checked-claim count. |
| inputs / outputs | Compares checked claims, replay attempt/commit/allocation/active-time/peak-depth counters and limit revision. |
| invariants | The helper does not require equality of phase or validity; it only checks nondecreasing history. |
| ownership | Snapshots and context text are borrowed. |
| failure | A regression throws through check. |
| cost | Fixed counter comparisons. The context + diagnostic passed to check is formed before the condition branch, including for a passing comparison; this test-harness string work is separate from planner counters. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0022

[Lines 124–124](../../../../../tests/unit/planner_continuation_test.cpp#L124); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Slicing { one_shot, unit, varied };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the three producer slicing patterns exercised by the test. |
| inputs / outputs | Enum values are one-shot, unit quantum and varied quantum. |
| invariants | The varied schedule is separately defined by run_search; enum selection alone does not promise equivalent timing. |
| ownership | No dynamic ownership. |
| failure | No runtime failure path beyond caller logic. |
| cost | Constant-size enum. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0024

[Lines 126–130](../../../../../tests/unit/planner_continuation_test.cpp#L126); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SearchRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect one run’s final progress, optional verified optimum and observed phase set. |
| inputs / outputs | Stores owned progress and phase values plus an optional typed VerifiedOptimum handle. |
| invariants | The struct records public outcomes; it does not turn unfinished progress into optimum authority. |
| ownership | Value members and typed handle are owned by the result. |
| failure | Member copying/moving follows their types. |
| cost | Storage grows with the set of observed phase enum values, which is small. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0026

[Lines 132–138](../../../../../tests/unit/planner_continuation_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::ContinuationLimits generous_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use large finite cumulative work and depth limits for representative exact runs. |
| inputs / outputs | Returns continuation limits with producer and replay work at 50,000,000 and logical depth 1,024; active-time remains unset. |
| invariants | These are test budgets, not proof of CPU-time, total-heap or arbitrary-query bounds. |
| ownership | Returns a value object. |
| failure | No explicit failure handling; default construction is local. |
| cost | Fixed-size initialization. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0028

[Lines 140–180](../../../../../tests/unit/planner_continuation_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchRun run_search(const Fixture& fixture, Slicing slicing,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive ExactSearch under one of three work-grant schedules until it publishes a verified optimum. |
| inputs / outputs | Copies fixture input into ExactSearch admission; advances with 50,000,000, one, or cycling 3/1/5/2 work grants and returns final progress/optimum/phases. |
| invariants | Strict mode must expose no incumbent handle; failed results throw. An unfinished call may stop for quantum work/time or cumulative total work/time. Completion requires complete stop plus typed optimum. The five-million iteration guard counts calls, not CPU seconds. |
| ownership | Owner retains its admitted inputs; SearchRun owns returned progress and optimum handle. |
| failure | Unexpected stop/result and the iteration guard throw; admission or allocation exceptions may propagate. |
| cost | Repeated bounded advancement and progress snapshots; runtime depends on instance and grant schedule. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0030

[Lines 182–261](../../../../../tests/unit/planner_continuation_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_differential_representatives() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Differentially compare four small representative CQs across production v2, private v1 baseline and exhaustive reference, then compare continuation slicing. |
| inputs / outputs | Uses four fixtures and compares status/minimum heights, validates witnesses, independently replays certificates, and checks one-shot/unit/varied exact runs. |
| invariants | Only these four fixtures are covered. Equality concerns committed transition totals and verified outcomes, not attempted calls, CPU time or a proof that implementations agree for all inputs. |
| ownership | Fixture, oracle results, certificates and replay owners are local; returned proof handles live through each check. |
| failure | Any mismatch or bounded replay guard throws; oracle/planner exceptions propagate. |
| cost | Runs four small differential fixtures through production v2, the private v1 baseline, and the exhaustive reference, then through three continuation schedules and independent certificate checks/replays. The one-transition standalone replay and run_search loops have explicit call guards; they are call-count guards, not time limits. Diagnostic strings passed to check are constructed at call sites even on passing assertions. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0032

[Lines 263–318](../../../../../tests/unit/planner_continuation_test.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void phase_suspension_and_interval_semantics() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show a best-found upper can be published before proof completion and a deeper case reaches export/replay phases. |
| inputs / outputs | Advances the known height-two fixture by one work unit, validates and cancels after the incumbent; then completes the residual seven-scope fixture. |
| invariants | The incumbent is a P02-validated upper only; it is not a VerifiedOptimum. The height-three result is accepted only after producer and independent proof replay complete. |
| ownership | Published incumbent handle remains valid after owner cancellation; fixture and owners are local. |
| failure | Unexpected stop, missing phases or wrong height throw. |
| cost | Unit-grant loops have explicit call guards; these count transitions/calls rather than CPU. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0034

[Lines 320–452](../../../../../tests/unit/planner_continuation_test.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_phase_coverage_and_corruption() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Walk all public v2 replay phases and reject a finite set of altered proof claims. |
| inputs / outputs | Replays v2 and private v1 certificates one transition at a time; mutations cover algorithm, minimum, root bound/flags, orbit duplication, missing full root, occurrence IDs and claimed upper tree height. |
| invariants | Checked authority appears only after complete valid replay. The corruptions are selected examples, not exhaustive malformed-input or proof coverage. |
| ownership | Replay owns its admitted proof snapshot; successful checked handles are held only for assertions. |
| failure | Each mutation must reach failed without checked authority; unexpected stop or bounded guard throws. |
| cost | Walks v2 replay, runs nine selected v2 corruption replays, and completes a valid v1 replay with one-work grants; the source places a five-million-call guard on each loop. Work scales with the selected proof data and corruption position. The require_rejected helper forms context + diagnostic strings at check call sites even when assertions pass; this harness cost is separate. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0036

[Lines 454–535](../../../../../tests/unit/planner_continuation_test.cpp#L454); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ownership_move_and_zero_quantum() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise admission snapshots, zero-work/time grants, move state and handle lifetime. |
| inputs / outputs | Clears caller-owned model/proof data after admission; checks zero grants preserve progress, moved-from owners reject access, and saved handles remain usable after facade teardown. |
| invariants | A zero quantum reports its quantum stop without changing progress; only completed replay/producer evidence yields typed checked authority. Saved upper and optimum are distinct typed values. |
| ownership | Planner owners copy input at admission; published immutable payload handles are tested after owner lifetime ends. |
| failure | Invalid moved-from access is expected to throw CROWN Error; unexpected state changes fail assertions. |
| cost | Copies fixture/proof values at admission, advances search and replay with fixed per-call grants, and checks moved-from and saved-handle behavior. Three completion loops are while loops without a local call-count guard; termination relies on these fixtures and the continuation completing. Caller-side diagnostic strings are formed eagerly at check calls. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0038

[Lines 537–651](../../../../../tests/unit/planner_continuation_test.cpp#L537); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resource_stops_and_monotone_extension() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish quantum stops from cumulative work, time and logical-depth stops and verify monotone limit extension. |
| inputs / outputs | Runs producer and replay under exhausted work, zero depth and active-time budgets, snapshots counters/revisions, then raises limits to resume. |
| invariants | Quantum work/time are per-call grants. Producer and replay work/active-time ceilings apply to separate cumulative histories; logical_depth caps the active worker frame depth, not accumulated historical work. Resource stops preserve unfinished state. Monotone raises retain history; these limits do not bound all CPU work or retained bytes. |
| ownership | The same search/replay owner resumes after a limit change; no replacement owner or new query is admitted. |
| failure | Invalid negative time or lowering consumed limits is rejected; unexpected stop/result fails the test. |
| cost | Exercises zero-work, depth, cumulative-work, active-time, and replay-work stops. The producer-completion search after raising work, the depth/time resumes, and the final replay-resume are while loops without local call-count guards; only the producer-before-replay cut has a 1,000,000-call guard. Per-call grants and work/time counters are not CPU or heap bounds. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0040

[Lines 653–690](../../../../../tests/unit/planner_continuation_test.cpp#L653); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void wide_dynamic_and_replay_input_ownership() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise dynamic-width inputs beyond 64 variables and replay after caller mutation. |
| inputs / outputs | Builds a nested scope chain with width 70, completes varied-grant search, then clears/mutates caller catalog/query/certificate after replay admission. |
| invariants | The concrete width exceeds 64 and succeeds; it is not a maximum-width guarantee. Replay authority is obtained only after complete valid checking against the admitted snapshot. |
| ownership | Replay owns copied inputs and certificate after creation; local owners retain only their own state. |
| failure | Unexpected stop, invalid proof or missing authority throws. |
| cost | Builds the finite 70-variable/70-occurrence nested fixture and runs it through run_search, whose advancement loop has a 5,000,000-call guard. The later owned replay uses 13-work grants in a while(!complete) loop without a local call-count guard. Fixture/proof copies and replay work scale with these inputs; 70 is not a maximum-width or CPU guarantee. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0041

[Lines 691–699](../../../../../tests/unit/planner_continuation_test.cpp#L691); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L691-L699:sha256:1990832133f4a45d9cdc68f31ad0e90fc91c95d94660b42f0b15cb6e2e15dc61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_continuation_test.cpp: require 4 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0042

[Lines 700–713](../../../../../tests/unit/planner_continuation_test.cpp#L700); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the six continuation test groups and translate uncaught test exceptions into a failing process exit. |
| inputs / outputs | Takes no command-line options; on success prints a message and returns zero, while std::exception is printed and returns one. |
| invariants | CMake invokes this executable without arguments; the main function does not configure a runtime workload. |
| ownership | Arguments and exception text are borrowed for the process call. |
| failure | Catches std::exception from assertions/fixtures; non-std exceptions are not caught. |
| cost | Runs each listed test group sequentially. |
| Design | [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
