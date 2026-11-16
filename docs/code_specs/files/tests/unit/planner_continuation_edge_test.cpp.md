# `tests/unit/planner_continuation_edge_test.cpp` — block usage map

[Source](../../../../../tests/unit/planner_continuation_edge_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `70e754b0539f48e8dc2bf6ffd7c56d6310f23d14e6377dffbbfe53f8f318c065`. 531 lines partitioned into 46 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/planner_continuation_edge_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/planner_continuation_edge_test.cpp#L23) | Callable definition: void check(bool condition, const char* message) | calls std::runtime_error; guard void check(bool condition, const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../tests/unit/planner_continuation_edge_test.cpp#L26) | Explanatory comments or spacing. |  |
| [B0004 · 27–30](../../../../../tests/unit/planner_continuation_edge_test.cpp#L27) | Type/record definition: struct Fixture |  · [reviewed contract](#b0004) |
| [B0005 · 31–31](../../../../../tests/unit/planner_continuation_edge_test.cpp#L31) | Explanatory comments or spacing. |  |
| [B0006 · 32–57](../../../../../tests/unit/planner_continuation_edge_test.cpp#L32) | Callable definition: Fixture fixture_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls insert, begin, end, reserve; returns fixture; growth emplace_back, insert, push_back, reserve; 5 loop sites · [reviewed contract](#b0006) |
| [B0007 · 58–58](../../../../../tests/unit/planner_continuation_edge_test.cpp#L58) | Explanatory comments or spacing. |  |
| [B0008 · 59–61](../../../../../tests/unit/planner_continuation_edge_test.cpp#L59) | Callable definition: HeightCertificate certificate_for(const OracleResult& result) | calls ; returns {result.algorithm, result.minimum_height, result.tree, result.lower_bounds} · [reviewed contract](#b0008) |
| [B0009 · 62–62](../../../../../tests/unit/planner_continuation_edge_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0010 · 63–68](../../../../../tests/unit/planner_continuation_edge_test.cpp#L63) | Callable definition: bool is_full_root(const LowerBoundEntry& entry, std::size_t occurrence_count) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 69–69](../../../../../tests/unit/planner_continuation_edge_test.cpp#L69) | Explanatory comments or spacing. |  |
| [B0012 · 70–73](../../../../../tests/unit/planner_continuation_edge_test.cpp#L70) | Callable definition: bool zero_depth_counters(const SearchProgress& progress) | calls ; returns progress.producer.current_depth == 0 && progress.producer.peak_depth == 0 && · [reviewed contract](#b0012) |
| [B0013 · 74–74](../../../../../tests/unit/planner_continuation_edge_test.cpp#L74) | Explanatory comments or spacing. |  |
| [B0014 · 75–77](../../../../../tests/unit/planner_continuation_edge_test.cpp#L75) | Callable definition: bool zero_depth_counters(const ReplayProgress& progress) | calls ; returns progress.work.current_depth == 0 && progress.work.peak_depth == 0 · [reviewed contract](#b0014) |
| [B0015 · 78–78](../../../../../tests/unit/planner_continuation_edge_test.cpp#L78) | Explanatory comments or spacing. |  |
| [B0016 · 79–85](../../../../../tests/unit/planner_continuation_edge_test.cpp#L79) | Callable definition: bool same_work_history(const WorkCounters& before, const WorkCounters& after) | calls ; returns before.attempted == after.attempted && · [reviewed contract](#b0016) |
| [B0017 · 86–86](../../../../../tests/unit/planner_continuation_edge_test.cpp#L86) | Explanatory comments or spacing. |  |
| [B0018 · 87–94](../../../../../tests/unit/planner_continuation_edge_test.cpp#L87) | Callable definition: bool same_statistics(const SearchStatistics& a, const SearchStatistics& b) | calls ; returns a.work == b.work && a.states == b.states && a.partitions == b.partitions && · [reviewed contract](#b0018) |
| [B0019 · 95–95](../../../../../tests/unit/planner_continuation_edge_test.cpp#L95) | Explanatory comments or spacing. |  |
| [B0020 · 96–104](../../../../../tests/unit/planner_continuation_edge_test.cpp#L96) | Callable definition: SearchProgress finish_unit_search(ExactSearch& owner) | calls advance, check; guard check(advanced.stopped_for == StopReason::quantum_work &&; returns advanced.progress; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 105–105](../../../../../tests/unit/planner_continuation_edge_test.cpp#L105) | Explanatory comments or spacing. |  |
| [B0022 · 106–114](../../../../../tests/unit/planner_continuation_edge_test.cpp#L106) | Callable definition: ReplayProgress finish_unit_replay(CertificateReplay& owner) | calls advance, check; guard check(advanced.stopped_for == StopReason::quantum_work &&; returns advanced.progress; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 115–116](../../../../../tests/unit/planner_continuation_edge_test.cpp#L115) | Explanatory comments or spacing. | source comment (unverified): // Compatibility diagnostics describe only the evidence that replay published. · [reviewed contract](#b0023) |
| [B0024 · 117–148](../../../../../tests/unit/planner_continuation_edge_test.cpp#L117) | Callable definition: void compatibility_report_describes_checked_evidence(const Fixture& finite, const HeightCertificate& certificate) | calls verify_height_certificate, check, fixture_for, minimum_tree; guard check(upper.valid && !upper.resource_limit &&; source comment (unverified): // Compatibility diagnostics describe only the evidence that replay published. · [reviewed contract](#b0024) |
| [B0025 · 149–149](../../../../../tests/unit/planner_continuation_edge_test.cpp#L149) | Explanatory comments or spacing. |  |
| [B0026 · 150–185](../../../../../tests/unit/planner_continuation_edge_test.cpp#L150) | Callable definition: void empty_body_depth_zero() | calls minimum_tree, check, certificate_for, ExactSearch::create; guard check(legacy.status == OracleStatus::proven_minimum && legacy.minimum_height == 0 && · [reviewed contract](#b0026) |
| [B0027 · 186–186](../../../../../tests/unit/planner_continuation_edge_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0028 · 187–243](../../../../../tests/unit/planner_continuation_edge_test.cpp#L187) | Callable definition: void zero_depth_nonempty_retains_and_resumes(const Fixture& fixture, const HeightCertificate& certificate) | calls ExactSearch::create, advance, check, optimum; guard check(stopped.stopped_for == StopReason::quantum_work, · [reviewed contract](#b0028) |
| [B0029 · 244–244](../../../../../tests/unit/planner_continuation_edge_test.cpp#L244) | Explanatory comments or spacing. |  |
| [B0030 · 245–285](../../../../../tests/unit/planner_continuation_edge_test.cpp#L245) | Callable definition: void cancellation_preserves_work_history_and_claims( const Fixture& fixture, const HeightCertificate& certificate) | calls ExactSearch::create, advance, check, cancel; guard check(advanced.stopped_for == StopReason::quantum_work &&; 2 loop sites · [reviewed contract](#b0030) |
| [B0031 · 286–286](../../../../../tests/unit/planner_continuation_edge_test.cpp#L286) | Explanatory comments or spacing. |  |
| [B0032 · 287–360](../../../../../tests/unit/planner_continuation_edge_test.cpp#L287) | Callable definition: void replay_rejects_corrupt_v1(const Fixture& fixture) | calls testing::minimum_tree_baseline, check, certificate_for, CertificateReplay::create; guard check(baseline.status == OracleStatus::proven_minimum && baseline.minimum_height == 2 &&; returns is_full_root(entry, fixture.query.atoms.size()); is_full_root(entry, fixture.query.atoms.size()); 1 loop sites; source comment (unverified): // Creation only admits and owns the typed value. Rejection must come from · [reviewed contract](#b0032) |
| [B0033 · 361–361](../../../../../tests/unit/planner_continuation_edge_test.cpp#L361) | Explanatory comments or spacing. |  |
| [B0034 · 362–364](../../../../../tests/unit/planner_continuation_edge_test.cpp#L362) | Callable definition: std::uint64_t total_active_time(const SearchProgress& progress) | calls ; returns progress.producer.active_nanoseconds + progress.replay.active_nanoseconds · [reviewed contract](#b0034) |
| [B0035 · 365–365](../../../../../tests/unit/planner_continuation_edge_test.cpp#L365) | Explanatory comments or spacing. |  |
| [B0036 · 366–436](../../../../../tests/unit/planner_continuation_edge_test.cpp#L366) | Callable definition: void active_time_excludes_admission_and_idle(const Fixture& fixture, const HeightCertificate& certificate) | calls ExactSearch::create, progress, check, total_active_time; guard check(total_active_time(admitted_search) == 0, · [reviewed contract](#b0036) |
| [B0037 · 437–437](../../../../../tests/unit/planner_continuation_edge_test.cpp#L437) | Explanatory comments or spacing. |  |
| [B0038 · 438–449](../../../../../tests/unit/planner_continuation_edge_test.cpp#L438) | Callable definition: Fixture nested_chain(std::size_t count) | calls reserve, push_back, std::move, fixture_for; returns fixture_for(scopes, {0}); growth push_back, reserve; 2 loop sites · [reviewed contract](#b0038) |
| [B0039 · 450–450](../../../../../tests/unit/planner_continuation_edge_test.cpp#L450) | Explanatory comments or spacing. |  |
| [B0040 · 451–462](../../../../../tests/unit/planner_continuation_edge_test.cpp#L451) | Callable definition: SearchProgress finish_varied_search(ExactSearch& owner) | calls advance, size, check; guard check(advanced.stopped_for == StopReason::quantum_work &&; returns advanced.progress; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 463–463](../../../../../tests/unit/planner_continuation_edge_test.cpp#L463) | Explanatory comments or spacing. |  |
| [B0042 · 464–503](../../../../../tests/unit/planner_continuation_edge_test.cpp#L464) | Callable definition: void deep_hierarchy_handle_survives_owner_teardown() | calls nested_chain, ExactSearch::create, finish_varied_search, check; guard check(completed.result == ResultKind::verified_optimum && completed.proof_complete &&; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 504–504](../../../../../tests/unit/planner_continuation_edge_test.cpp#L504) | Explanatory comments or spacing. |  |
| [B0044 · 505–519](../../../../../tests/unit/planner_continuation_edge_test.cpp#L505) | Callable definition: void run() | calls fixture_for, minimum_tree, check, certificate_for; guard check(exact_baseline.status == OracleStatus::proven_minimum && exact_baseline.minimum_height == 2, · [reviewed contract](#b0044) |
| [B0045 · 520–521](../../../../../tests/unit/planner_continuation_edge_test.cpp#L520) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0045) |
| [B0046 · 522–531](../../../../../tests/unit/planner_continuation_edge_test.cpp#L522) | Callable definition: int main() | calls run, what; returns 0; 1 · [reviewed contract](#b0046) |

## B0001

[Lines 1–22](../../../../../tests/unit/planner_continuation_edge_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:8267c5eb13df7fc104b9ca8182e59d941bd8d02649610a53143011344586cfe8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_continuation_edge_test.cpp: include "crown/planner/search.hpp", "crown/planner/verify.hpp", "planner_probe.hpp", &lt;array&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;thread&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–25](../../../../../tests/unit/planner_continuation_edge_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an edge-case assertion with a diagnostic. |
| inputs / outputs | Takes a boolean and borrowed message; normal return means true. |
| invariants | A false condition throws std::runtime_error. |
| ownership | No retained state. |
| failure | Exception/message allocation failure may propagate. |
| cost | One branch on success. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0004

[Lines 27–30](../../../../../tests/unit/planner_continuation_edge_test.cpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the catalog and query used by edge fixtures. |
| inputs / outputs | Stores one Catalog and one Query and returns them by value. |
| invariants | This wrapper adds no validation. |
| ownership | Both are owned values. |
| failure | Fixture allocations can throw. |
| cost | Variable-sized fixture storage. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0006

[Lines 32–57](../../../../../tests/unit/planner_continuation_edge_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture fixture_for(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the edge-test catalog/query from numbered scope and head labels. |
| inputs / outputs | Creates generated variables/tables/atoms and ordered head terms from fixture vectors. |
| invariants | Sorted distinct labels are later used as direct vector indices, so test labels must be dense zero-based values; this builder does not remap arbitrary sparse names safely. |
| ownership | Returns an owning Fixture; temporary mapping data is local. |
| failure | Sparse/out-of-range labels fail via bounds-checked access; allocation errors propagate. |
| cost | Visits every variable, scope and head entry. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0008

[Lines 59–61](../../../../../tests/unit/planner_continuation_edge_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
HeightCertificate certificate_for(const OracleResult& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy an OracleResult into a HeightCertificate for the compatibility/replay fixture. |
| inputs / outputs | Returns algorithm, minimum, tree and lower-bound evidence. |
| invariants | Projection alone does not prove the certificate; replay supplies independent checking. |
| ownership | Returned certificate owns copied payload. |
| failure | Copies may allocate and throw. |
| cost | Linear in copied evidence size. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0010

[Lines 63–68](../../../../../tests/unit/planner_continuation_edge_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool is_full_root(const LowerBoundEntry& entry, std::size_t occurrence_count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a lower-bound entry names every occurrence ID in a full root scope. |
| inputs / outputs | Reads one entry and expected occurrence count; returns true only for exactly ordered IDs 0 through n-1. |
| invariants | The predicate checks the occurrence vector shape only, not all root flags or bound correctness. |
| ownership | Entry is borrowed. |
| failure | No explicit failure path except ordinary comparison. |
| cost | Scans the occurrence list once. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0012

[Lines 70–73](../../../../../tests/unit/planner_continuation_edge_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool zero_depth_counters(const SearchProgress& progress) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether producer and replay current and peak logical depths are all zero. |
| inputs / outputs | Reads SearchProgress and returns true only when producer.current_depth, producer.peak_depth, replay.current_depth, and replay.peak_depth are all zero. |
| invariants | The predicate requires historical peak_depth to be zero as well as current_depth; it describes this zero-frame fixture boundary, not a current-depth-only or monotonic-history check. |
| ownership | Progress snapshot is borrowed. |
| failure | Returns false when any compared depth is nonzero; this Boolean predicate does not throw or invoke check. |
| cost | At most 4 scalar comparisons with short-circuit evaluation; no allocation. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0014

[Lines 75–77](../../../../../tests/unit/planner_continuation_edge_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool zero_depth_counters(const ReplayProgress& progress) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether replay current and peak logical depth are both zero. |
| inputs / outputs | Reads ReplayProgress and returns true only when work.current_depth and work.peak_depth are both zero. |
| invariants | Peak depth is explicitly required to be zero here; historical work/claim totals are not checked by this helper. |
| ownership | Snapshot is borrowed. |
| failure | Returns false when any compared depth is nonzero; this Boolean predicate does not throw or invoke check. |
| cost | At most 2 scalar comparisons with short-circuit evaluation; no allocation. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0016

[Lines 79–85](../../../../../tests/unit/planner_continuation_edge_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_work_history(const WorkCounters& before, const WorkCounters& after) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the historical work fields around cancellation and also require the resulting current depth to be zero. |
| inputs / outputs | Compares attempts, committed transitions, allocation failures, active nanoseconds and peak depth, then checks after.current_depth == 0. |
| invariants | Historical counters must be preserved while active depth is released; this differs from a general progress equality helper. |
| ownership | Snapshots are borrowed. |
| failure | Returns false on a history mismatch or nonzero final current depth; this predicate performs no assertion or throwing operation. |
| cost | Fixed scalar comparisons. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0018

[Lines 87–94](../../../../../tests/unit/planner_continuation_edge_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_statistics(const SearchStatistics& a, const SearchStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the structural work fields used by edge fixtures. |
| inputs / outputs | Returns equality over work/states/partitions/candidates/cache/certificate/hierarchy/singleton/empty-body/component/symmetry/bound-prune counters. |
| invariants | Only these enumerated statistics are compared. |
| ownership | Both values are borrowed. |
| failure | No explicit failure path. |
| cost | Fixed scalar comparisons. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0020

[Lines 96–104](../../../../../tests/unit/planner_continuation_edge_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchProgress finish_unit_search(ExactSearch& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish an exact search by repeatedly granting one transition. |
| inputs / outputs | Advances forever with work quantum one and returns only on complete; intermediate stops must be quantum_work and result must not be failed. |
| invariants | The loop has no call-count or CPU guard; it relies on eventual completion of the selected fixture. |
| ownership | Owner remains borrowed and owns the continuation. |
| failure | Unexpected stop or failed phase throws; an actually nonterminating implementation would keep looping. |
| cost | One transition grant and progress inspection per iteration. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0022

[Lines 106–114](../../../../../tests/unit/planner_continuation_edge_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayProgress finish_unit_replay(CertificateReplay& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish replay by granting one transition until complete. |
| inputs / outputs | Advances a borrowed replay owner with one-work grants and returns the progress when stopped_for is complete. Other iterations must stop for quantum_work and remain outside failed phase. |
| invariants | No call-count or CPU guard is present. Completion/validity is checked by callers; this helper alone does not return the checked certificate. |
| ownership | Replay state remains owned by caller. |
| failure | Unexpected stop or failed phase throws; a nonterminating replay would keep looping. |
| cost | One transition grant per iteration. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0023

[Lines 115–116](../../../../../tests/unit/planner_continuation_edge_test.cpp#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L116:sha256:d4508a0bb0cf7a2e97b21c90d6a1496b5ef2ba6c698263c9126e37488614e456
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Compatibility diagnostics describe only the evidence that replay published. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 117–148](../../../../../tests/unit/planner_continuation_edge_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compatibility_report_describes_checked_evidence(const Fixture& finite,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that compatibility diagnostics describe independently published finite or empty-family evidence. |
| inputs / outputs | Replays a known finite certificate and a freshly proved cyclic empty-family certificate, then retries corrupted and zero-work versions. |
| invariants | Success text must match finite versus infinite replay authority; invalid algorithms and resource stops cannot acquire a successful empty-family message. |
| ownership | Fixtures and certificates are local owning values; each compatibility call admits its own replay snapshot. |
| failure | check throws on a mismatch and the existing test main reports failure; no production error path is added. |
| cost | Two small exact query cases and four independent replay calls; no performance claim or benchmark. The zero-work call stops before replay work. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0026

[Lines 150–185](../../../../../tests/unit/planner_continuation_edge_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void empty_body_depth_zero() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify empty-body exact search and replay complete at logical depth zero. |
| inputs / outputs | Calls the legacy minimum_tree compatibility entrypoint with recursion_limit zero, then owned ExactSearch and CertificateReplay at logical depth zero; checks height-zero typed authority and current/peak counters. |
| invariants | This establishes the empty-body boundary case only; it does not say nonempty recursion ignores depth limits. |
| ownership | Owners and fixture are local; optimum handle is checked before teardown. |
| failure | Unexpected stop, nonzero depth, wrong height or missing authority throws. |
| cost | Checks the empty-body fixture with exact search and certificate replay, using finish_unit_search and finish_unit_replay. Both helpers grant one work unit in for(;;) loops with no local call-count guard; the test relies on empty-body completion. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0028

[Lines 187–243](../../../../../tests/unit/planner_continuation_edge_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void zero_depth_nonempty_retains_and_resumes(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a nonempty search and replay pause at zero logical depth without losing work, then resume after raising depth. |
| inputs / outputs | Uses zero depth, repeats the stop, checks attempt/commit/claim history, raises depth to unlimited and completes. |
| invariants | Depth-limit stop is distinct from a work quantum; repeated blocked attempts may increment attempts while commits/checked claims stay fixed. |
| ownership | The same owner resumes; input is not re-admitted. |
| failure | Unexpected stop, counter change or failure throws. |
| cost | Performs initial blocked advances, then resumes the same search and replay using one-unit grants. The completion helpers have no local iteration cap; these finite fixtures are expected to terminate, but the helper does not impose a call or CPU bound. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0030

[Lines 245–285](../../../../../tests/unit/planner_continuation_edge_test.cpp#L245); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cancellation_preserves_work_history_and_claims(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify cancellation preserves historical producer/replay work but releases active frames. |
| inputs / outputs | Cancels a partially advanced search and replay, then compares counter history, depth, progress and partial checked-claim count. |
| invariants | Cancellation leaves partial replay incomplete/invalid and never promotes it to checked authority; current depth returns to zero. |
| ownership | Saved owner state is inspected after cancel; no claim is made that unfinished frames survive. |
| failure | Assertion mismatch throws. |
| cost | Advances search until a nonzero current depth and replay until a checked-claim prefix, cancels both, and compares retained histories. Both prefix-seeking for(;;) loops lack a local iteration guard; the assertions do not bound their number of calls or CPU time. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0032

[Lines 287–360](../../../../../tests/unit/planner_continuation_edge_test.cpp#L287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay_rejects_corrupt_v1(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and reject five altered v1 proof examples after replay has made work. |
| inputs / outputs | Starts from private v1 baseline proof and changes algorithm, full-root claim, occurrence ID, root lower bound or claimed upper height. |
| invariants | The test requires replay to perform at least two calls and commit work before failure for these mutations; this finite set is not all possible corruptions. |
| ownership | Replay owns each mutated proof copy. |
| failure | A mutation that is accepted, rejected too early, or yields checked authority fails the test. |
| cost | First completes an unmodified v1 replay through the unguarded finish_unit_replay helper. For each of five corruptions, advances once and then loops while the stop remains quantum_work; there is no local call-count cap on that rejection loop. Each case requires at least two calls and a committed transition before invalid_certificate; only these five mutations are covered. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2) |

## B0034

[Lines 362–364](../../../../../tests/unit/planner_continuation_edge_test.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t total_active_time(const SearchProgress& progress) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sum producer and replay active-nanosecond counters from one SearchProgress. |
| inputs / outputs | Returns the arithmetic sum of two unsigned active-time fields. |
| invariants | This helper uses the fixture’s small counters and does not check arithmetic overflow. |
| ownership | Progress is borrowed. |
| failure | No explicit exception handling. |
| cost | Two reads and one addition. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0036

[Lines 366–436](../../../../../tests/unit/planner_continuation_edge_test.cpp#L366); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void active_time_excludes_admission_and_idle(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show active-time accounting excludes admission, zero-work grants and caller idle sleep. |
| inputs / outputs | Uses 2-second active-time limits, does zero-grant calls, advances work, sleeps 2.5 seconds, then resumes producer and replay. |
| invariants | Only time measured inside advancement is charged by this API; wall-clock sleep is not. This does not claim CPU-time accounting or a hard scheduling deadline. |
| ownership | Owners persist across the caller’s sleep and resume on the same inputs. |
| failure | Unexpected total-time stop or zero/changed counter behavior fails; thread/sleep scheduling can affect elapsed wall time. |
| cost | Includes two deliberate 2.5-second sleeps and several small advances. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0038

[Lines 438–449](../../../../../tests/unit/planner_continuation_edge_test.cpp#L438); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture nested_chain(std::size_t count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a nested chain of scopes of lengths count down to one. |
| inputs / outputs | Builds local prefix scopes of lengths count down to one, calls fixture_for(scopes, {0}), and returns the resulting Catalog/Query Fixture. |
| invariants | The generated variables are dense zero-based labels expected by fixture_for. |
| ownership | The returned Fixture owns generated catalog/query metadata. The local scope vectors are temporary inputs to fixture_for and are destroyed before return. |
| failure | Allocation can throw. |
| cost | Produces the triangular number of scope entries relative to count. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0040

[Lines 451–462](../../../../../tests/unit/planner_continuation_edge_test.cpp#L451); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchProgress finish_varied_search(ExactSearch& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete a search under a repeated varied work-grant schedule. |
| inputs / outputs | Cycles grants 7, 31, 127, 509 and 1,021 until the selected search returns complete. |
| invariants | Every intermediate stop must be quantum_work and phase nonfailed; there is no loop guard, so it is not a CPU bound. |
| ownership | Search owner is borrowed. |
| failure | Unexpected stop/failure throws; nontermination would keep looping. |
| cost | One progress advance per iteration with cyclic grant sizes. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0042

[Lines 464–503](../../../../../tests/unit/planner_continuation_edge_test.cpp#L464); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deep_hierarchy_handle_survives_owner_teardown() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain and validate a best-found incumbent after a deep-search owner is destroyed. |
| inputs / outputs | Builds 150 nested scopes, searches with best_found and unbounded configured producer/replay work and depth, checks a completed height-one VerifiedOptimum, separately retains the ValidatedIncumbent, then validates that upper tree after the facade scope ends. |
| invariants | The owner also publishes a distinct VerifiedOptimum at completion. The retained ValidatedIncumbent handle is a checked upper-witness object and does not itself carry the minimum-height proof; its immutable payload remains valid after facade teardown. |
| ownership | The retained ValidatedIncumbent shares an immutable CheckedUpper containing the checked tree/report and admitted BindingData. It therefore retains the catalog/query binding after the facade is destroyed; the facade and its unfinished workers are separate owners. |
| failure | Unexpected stop, missing/invalid handle or wrong tree validation throws. |
| cost | Builds 150 nested scopes (11,325 scope entries) and searches with producer-work, replay-work, and depth ceilings unset. finish_varied_search uses grants 7/31/127/509/1,021 in an unguarded for(;;) loop, then the test retains and validates the incumbent tree after owner teardown. No CPU or heap bound is measured. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [exact paper reference](https://arxiv.org/html/2301.04003v2#S3.SS2), [src/planner/continuation_machine.hpp](../../../../../src/planner/continuation_machine.hpp) |

## B0044

[Lines 505–519](../../../../../tests/unit/planner_continuation_edge_test.cpp#L505); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the compatibility, empty-body, depth-resume, cancellation, corrupted-v1, active-time and deep-owner edge cases. |
| inputs / outputs | Calls each grouped edge-case routine in sequence using its local fixture; returns no value. |
| invariants | The aggregate checks only those named cases, including zero-depth completion, resumable depth stops, cancellation history, selected v1 corruption, active-time accounting and a retained deep-search incumbent. |
| ownership | Each routine owns its local fixtures and owners. |
| failure | The first uncaught assertion/runtime error aborts this aggregate. |
| cost | Cost is the sum of its cases, including the active-time sleeps and deep search. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/continuation_budget.hpp](../../../../../src/planner/continuation_budget.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0045

[Lines 520–521](../../../../../tests/unit/planner_continuation_edge_test.cpp#L520); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L520-L521:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in planner_continuation_edge_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0046

[Lines 522–531](../../../../../tests/unit/planner_continuation_edge_test.cpp#L522); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the edge suite and return a process status from caught standard exceptions. |
| inputs / outputs | No arguments are consumed; success returns zero and std::exception prints to stderr and returns one. |
| invariants | The CMake test invokes the no-argument path; no runtime configuration is parsed. |
| ownership | Process arguments and caught exception reference are borrowed. |
| failure | Only std::exception is caught. |
| cost | Runs the sequence of edge cases. |
| Design | [tests/unit/planner_continuation_edge_test.cpp](../../../../../tests/unit/planner_continuation_edge_test.cpp), [include/crown/planner/search.hpp](../../../../../include/crown/planner/search.hpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp), [src/planner/certificate.cpp](../../../../../src/planner/certificate.cpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md) |
