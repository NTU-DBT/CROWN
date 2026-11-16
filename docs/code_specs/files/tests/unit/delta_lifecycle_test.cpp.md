# `tests/unit/delta_lifecycle_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_lifecycle_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fb0b2974bc14e3881c232a3422c7dd34b6aad204bb6c2e901a77a822bf84fc64`. 1080 lines partitioned into 106 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/delta_lifecycle_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 27–29](../../../../../tests/unit/delta_lifecycle_test.cpp#L27) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 30–30](../../../../../tests/unit/delta_lifecycle_test.cpp#L30) | Explanatory comments or spacing. |  |
| [B0004 · 31–42](../../../../../tests/unit/delta_lifecycle_test.cpp#L31) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, const std::string& code, const std::string& label) | calls action, check, code; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 43–43](../../../../../tests/unit/delta_lifecycle_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0006 · 44–44](../../../../../tests/unit/delta_lifecycle_test.cpp#L44) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 45–45](../../../../../tests/unit/delta_lifecycle_test.cpp#L45) | Explanatory comments or spacing. |  |
| [B0008 · 46–50](../../../../../tests/unit/delta_lifecycle_test.cpp#L46) | Callable definition: VariableSet variables(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 51–51](../../../../../tests/unit/delta_lifecycle_test.cpp#L51) | Explanatory comments or spacing. |  |
| [B0010 · 52–54](../../../../../tests/unit/delta_lifecycle_test.cpp#L52) | Callable definition: Relation a04(const auto& plan, const Database& database) | calls reference::evaluate, reference::input::catalog, catalog, reference::input::query; returns reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()… · [reviewed contract](#b0010) |
| [B0011 · 55–55](../../../../../tests/unit/delta_lifecycle_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0012 · 56–64](../../../../../tests/unit/delta_lifecycle_test.cpp#L56) | Callable definition: std::set&lt;SignedKey&gt; signed_difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 65–65](../../../../../tests/unit/delta_lifecycle_test.cpp#L65) | Explanatory comments or spacing. |  |
| [B0014 · 66–91](../../../../../tests/unit/delta_lifecycle_test.cpp#L66) | Callable definition: std::vector&lt;Relation&gt; a04_live(const auto& plan, const Relation& answer) | calls query, size, try_emplace, reserve; guard check(position != head_positions.end(),; returns result; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0014) |
| [B0015 · 92–92](../../../../../tests/unit/delta_lifecycle_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0016 · 93–108](../../../../../tests/unit/delta_lifecycle_test.cpp#L93) | Callable definition: std::set&lt;SignedKey&gt; collect(DeltaRuntime::Epoch& epoch, const std::string& label) | calls next, check, layout, same_token; guard check(record-&gt;ordinal == ++ordinal, label + ": non-contiguous ordinal");; returns rows; growth emplace; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 109–109](../../../../../tests/unit/delta_lifecycle_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0018 · 110–117](../../../../../tests/unit/delta_lifecycle_test.cpp#L110) | Callable definition: Relation collect_results(DeltaRuntime& runtime) | calls results, next, check, insert; guard check(result.insert(crown::storage::export_row(tuple-&gt;values())).second,; returns result; growth insert; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 118–118](../../../../../tests/unit/delta_lifecycle_test.cpp#L118) | Explanatory comments or spacing. |  |
| [B0020 · 119–141](../../../../../tests/unit/delta_lifecycle_test.cpp#L119) | Callable definition: void check_committed(DeltaRuntime& runtime, const Database& database, const std::string& label) | calls a04, plan, check, has_answer; guard check(runtime.has_answer() == !expected.empty(), · [reviewed contract](#b0020) |
| [B0021 · 142–142](../../../../../tests/unit/delta_lifecycle_test.cpp#L142) | Explanatory comments or spacing. |  |
| [B0022 · 143–151](../../../../../tests/unit/delta_lifecycle_test.cpp#L143) | Type/record definition: struct Scenario |  · [reviewed contract](#b0022) |
| [B0023 · 152–152](../../../../../tests/unit/delta_lifecycle_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0024 · 153–169](../../../../../tests/unit/delta_lifecycle_test.cpp#L153) | Callable definition: PhysicalPlan self_join_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0024) |
| [B0025 · 170–170](../../../../../tests/unit/delta_lifecycle_test.cpp#L170) | Explanatory comments or spacing. |  |
| [B0026 · 171–185](../../../../../tests/unit/delta_lifecycle_test.cpp#L171) | Callable definition: PhysicalPlan shared_separator_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0026) |
| [B0027 · 186–186](../../../../../tests/unit/delta_lifecycle_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0028 · 187–209](../../../../../tests/unit/delta_lifecycle_test.cpp#L187) | Callable definition: PhysicalPlan deep_chain_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0028) |
| [B0029 · 210–210](../../../../../tests/unit/delta_lifecycle_test.cpp#L210) | Explanatory comments or spacing. |  |
| [B0030 · 211–215](../../../../../tests/unit/delta_lifecycle_test.cpp#L211) | Callable definition: Scenario self_join_scenario() | calls self_join_plan, n; returns {@ , self_join_plan(), 1,; growth insert · [reviewed contract](#b0030) |
| [B0031 · 216–216](../../../../../tests/unit/delta_lifecycle_test.cpp#L216) | Explanatory comments or spacing. |  |
| [B0032 · 217–223](../../../../../tests/unit/delta_lifecycle_test.cpp#L217) | Callable definition: Scenario shared_separator_scenario() | calls shared_separator_plan, n; returns {@ , shared_separator_plan(), 2, · [reviewed contract](#b0032) |
| [B0033 · 224–224](../../../../../tests/unit/delta_lifecycle_test.cpp#L224) | Explanatory comments or spacing. |  |
| [B0034 · 225–232](../../../../../tests/unit/delta_lifecycle_test.cpp#L225) | Callable definition: Scenario deep_chain_scenario() | calls deep_chain_plan, n; returns {@ , deep_chain_plan(), 4,; growth insert · [reviewed contract](#b0034) |
| [B0035 · 233–237](../../../../../tests/unit/delta_lifecycle_test.cpp#L233) | declares types or opens a type body. |  · [reviewed contract](#b0035) |
| [B0036 · 238–257](../../../../../tests/unit/delta_lifecycle_test.cpp#L238) | Callable definition: Harness(const Scenario& scenario, DeltaOptions options) : runtime(scenario.plan, options) | calls runtime, resize, check, at; guard check(after.tables.at(table.value).insert(row).second,; growth insert, resize; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 258–258](../../../../../tests/unit/delta_lifecycle_test.cpp#L258) | Explanatory comments or spacing. |  |
| [B0038 · 259–262](../../../../../tests/unit/delta_lifecycle_test.cpp#L259) | Callable definition: PhysicalSetUpdate target(const Scenario& scenario) const | calls sequence; returns {runtime.sequence() + 1, scenario.update_table, · [reviewed contract](#b0038) |
| [B0039 · 263–263](../../../../../tests/unit/delta_lifecycle_test.cpp#L263) | Explanatory comments or spacing. |  |
| [B0040 · 264–269](../../../../../tests/unit/delta_lifecycle_test.cpp#L264) | Callable definition: PhysicalSetUpdate inverse(const Scenario& scenario) const | calls sequence; returns {runtime.sequence() + 1, scenario.update_table,; growth insert · [reviewed contract](#b0040) |
| [B0041 · 270–270](../../../../../tests/unit/delta_lifecycle_test.cpp#L270) | Explanatory comments or spacing. |  |
| [B0042 · 271–279](../../../../../tests/unit/delta_lifecycle_test.cpp#L271) | Callable definition: Database after(const PhysicalSetUpdate& update) const | calls at, insert, erase; returns next; growth insert · [reviewed contract](#b0042) |
| [B0043 · 280–280](../../../../../tests/unit/delta_lifecycle_test.cpp#L280) | Explanatory comments or spacing. |  |
| [B0044 · 281–284](../../../../../tests/unit/delta_lifecycle_test.cpp#L281) | Callable definition: std::set&lt;SignedKey&gt; expected(const PhysicalSetUpdate& update) const | calls signed_difference, a04, plan, after; returns signed_difference(a04(runtime.plan(), database), · [reviewed contract](#b0044) |
| [B0045 · 285–285](../../../../../tests/unit/delta_lifecycle_test.cpp#L285) | Explanatory comments or spacing. |  |
| [B0046 · 286–298](../../../../../tests/unit/delta_lifecycle_test.cpp#L286) | Callable definition: std::set&lt;SignedKey&gt; apply_and_check(const PhysicalSetUpdate& update, const std::string& label) | calls expected, apply, check, sequence; guard check(output.sequence() == update.sequence,; returns observed · [reviewed contract](#b0046) |
| [B0047 · 299–299](../../../../../tests/unit/delta_lifecycle_test.cpp#L299) | Explanatory comments or spacing. |  |
| [B0048 · 300–302](../../../../../tests/unit/delta_lifecycle_test.cpp#L300) | Callable definition: void publish_database(const PhysicalSetUpdate& update) | calls after · [reviewed contract](#b0048) |
| [B0049 · 303–304](../../../../../tests/unit/delta_lifecycle_test.cpp#L303) | Closes surrounding scope/type. |  · [reviewed contract](#b0049) |
| [B0050 · 305–311](../../../../../tests/unit/delta_lifecycle_test.cpp#L305) | Callable definition: DeltaOptions lifecycle_options() | calls ; returns result · [reviewed contract](#b0050) |
| [B0051 · 312–312](../../../../../tests/unit/delta_lifecycle_test.cpp#L312) | Explanatory comments or spacing. |  |
| [B0052 · 313–320](../../../../../tests/unit/delta_lifecycle_test.cpp#L313) | Callable definition: void check_replay_work_partition(const DeltaMetrics& metrics, const std::string& label) | calls check; guard check(partition == metrics.work, · [reviewed contract](#b0052) |
| [B0053 · 321–321](../../../../../tests/unit/delta_lifecycle_test.cpp#L321) | Explanatory comments or spacing. |  |
| [B0054 · 322–339](../../../../../tests/unit/delta_lifecycle_test.cpp#L322) | Callable definition: void step_once(DeltaRuntime::PendingEpoch& pending, std::size_t expected, const std::string& label) | calls metrics, step, check, state; guard check(accepted_after &gt;= accepted_before && · [reviewed contract](#b0054) |
| [B0055 · 340–340](../../../../../tests/unit/delta_lifecycle_test.cpp#L340) | Explanatory comments or spacing. |  |
| [B0056 · 341–352](../../../../../tests/unit/delta_lifecycle_test.cpp#L341) | Callable definition: void drive_to_prefix(DeltaRuntime::PendingEpoch& pending, std::size_t prefix, std::size_t expected, const std::string& label) | calls metrics, check, state, step_once; guard check(pending.state() != DeltaState::epoch_prepared,; 1 loop sites · [reviewed contract](#b0056) |
| [B0057 · 353–353](../../../../../tests/unit/delta_lifecycle_test.cpp#L353) | Explanatory comments or spacing. |  |
| [B0058 · 354–363](../../../../../tests/unit/delta_lifecycle_test.cpp#L354) | Callable definition: void drive_prepared(DeltaRuntime::PendingEpoch& pending, std::size_t expected, const std::string& label) | calls state, step_once, check, metrics; guard check(++calls &lt; 100000, label + ": preparation did not terminate");; 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 364–364](../../../../../tests/unit/delta_lifecycle_test.cpp#L364) | Explanatory comments or spacing. |  |
| [B0060 · 365–391](../../../../../tests/unit/delta_lifecycle_test.cpp#L365) | Callable definition: void check_barrier(Harness& harness, const PhysicalSetUpdate& update, const std::string& label) | calls sequence, expect_error, results, core_results; guard check(harness.runtime.sequence() == sequence, · [reviewed contract](#b0060) |
| [B0061 · 392–392](../../../../../tests/unit/delta_lifecycle_test.cpp#L392) | Explanatory comments or spacing. |  |
| [B0062 · 393–399](../../../../../tests/unit/delta_lifecycle_test.cpp#L393) | Callable definition: bool same_timings(const DeltaTimings& left, const DeltaTimings& right) | calls ; returns left.propagation_ns == right.propagation_ns && · [reviewed contract](#b0062) |
| [B0063 · 400–400](../../../../../tests/unit/delta_lifecycle_test.cpp#L400) | Explanatory comments or spacing. |  |
| [B0064 · 401–408](../../../../../tests/unit/delta_lifecycle_test.cpp#L401) | Callable definition: bool monotone_timings(const DeltaTimings& earlier, const DeltaTimings& later) | calls ; returns later.propagation_ns &gt;= earlier.propagation_ns && · [reviewed contract](#b0064) |
| [B0065 · 409–409](../../../../../tests/unit/delta_lifecycle_test.cpp#L409) | Explanatory comments or spacing. |  |
| [B0066 · 410–482](../../../../../tests/unit/delta_lifecycle_test.cpp#L410) | Callable definition: void pause_resume_each_output_prefix(const Scenario& scenario) | calls count_harness, lifecycle_options, target, expected; guard check(output_count &gt; 1,; 1 loop sites · [reviewed contract](#b0066) |
| [B0067 · 483–483](../../../../../tests/unit/delta_lifecycle_test.cpp#L483) | Explanatory comments or spacing. |  |
| [B0068 · 484–517](../../../../../tests/unit/delta_lifecycle_test.cpp#L484) | Callable definition: void discard_each_output_prefix(const Scenario& scenario) | calls lifecycle_options, count_harness, expected, target; guard check(discarded.sequence() == event.sequence && discarded.remaining() == 0 &&; 1 loop sites · [reviewed contract](#b0068) |
| [B0069 · 518–518](../../../../../tests/unit/delta_lifecycle_test.cpp#L518) | Explanatory comments or spacing. |  |
| [B0070 · 519–548](../../../../../tests/unit/delta_lifecycle_test.cpp#L519) | Callable definition: void start_drain_drops_staged_output(const Scenario& scenario) | calls harness, lifecycle_options, target, expected; guard check(pending.state() == DeltaState::draining &&; 1 loop sites · [reviewed contract](#b0070) |
| [B0071 · 549–549](../../../../../tests/unit/delta_lifecycle_test.cpp#L549) | Explanatory comments or spacing. |  |
| [B0072 · 550–585](../../../../../tests/unit/delta_lifecycle_test.cpp#L550) | Callable definition: void abort_each_output_prefix(const Scenario& scenario, bool destroy_token) | calls count_harness, lifecycle_options, expected, target; guard check(!pending.active(), scenario.label + ": rollback left its token active");; 1 loop sites · [reviewed contract](#b0072) |
| [B0073 · 586–586](../../../../../tests/unit/delta_lifecycle_test.cpp#L586) | Explanatory comments or spacing. |  |
| [B0074 · 587–634](../../../../../tests/unit/delta_lifecycle_test.cpp#L587) | Callable definition: void owning_input_and_move_lifecycle(const Scenario& scenario) | calls harness, lifecycle_options, target, expected; guard check(!original_pending.active() && pending.active(),; returns token; growth insert · [reviewed contract](#b0074) |
| [B0075 · 635–635](../../../../../tests/unit/delta_lifecycle_test.cpp#L635) | Explanatory comments or spacing. |  |
| [B0076 · 636–660](../../../../../tests/unit/delta_lifecycle_test.cpp#L636) | Callable definition: void canonical_policy_pause_resume(const Scenario& scenario, LiveMaintenance maintenance, DeltaCompletion completion, const std::… | calls lifecycle_options, harness, check, completion; guard check(harness.runtime.completion() == completion, · [reviewed contract](#b0076) |
| [B0077 · 661–661](../../../../../tests/unit/delta_lifecycle_test.cpp#L661) | Explanatory comments or spacing. |  |
| [B0078 · 662–680](../../../../../tests/unit/delta_lifecycle_test.cpp#L662) | Callable definition: void drain_resumes_paused_token(const Scenario& scenario) | calls harness, lifecycle_options, target, expected; guard check(pending.state() == DeltaState::epoch_prepared, · [reviewed contract](#b0078) |
| [B0079 · 681–681](../../../../../tests/unit/delta_lifecycle_test.cpp#L681) | Explanatory comments or spacing. |  |
| [B0080 · 682–691](../../../../../tests/unit/delta_lifecycle_test.cpp#L682) | Callable definition: PhysicalPlan projection_count_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0080) |
| [B0081 · 692–692](../../../../../tests/unit/delta_lifecycle_test.cpp#L692) | Explanatory comments or spacing. |  |
| [B0082 · 693–702](../../../../../tests/unit/delta_lifecycle_test.cpp#L693) | Callable definition: PhysicalPlan filtered_plan() | calls n, variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0082) |
| [B0083 · 703–703](../../../../../tests/unit/delta_lifecycle_test.cpp#L703) | Explanatory comments or spacing. |  |
| [B0084 · 704–725](../../../../../tests/unit/delta_lifecycle_test.cpp#L704) | Callable definition: void finish_empty_delta(DeltaRuntime& runtime, Database& database, const PhysicalSetUpdate& update, const std::string& label) | calls at, insert, erase, check; guard check(signed_difference(a04(runtime.plan(), database),; growth insert · [reviewed contract](#b0084) |
| [B0085 · 726–726](../../../../../tests/unit/delta_lifecycle_test.cpp#L726) | Explanatory comments or spacing. |  |
| [B0086 · 727–804](../../../../../tests/unit/delta_lifecycle_test.cpp#L727) | Callable definition: void no_op_count_only_filtered_and_maintenance() | calls self_join_plan, n, harness, lifecycle_options; guard check(harness.expected(event).empty(), "duplicate insert changed A04 answer");; growth insert, resize; 1 loop sites · [reviewed contract](#b0086) |
| [B0087 · 805–805](../../../../../tests/unit/delta_lifecycle_test.cpp#L805) | Explanatory comments or spacing. |  |
| [B0088 · 806–825](../../../../../tests/unit/delta_lifecycle_test.cpp#L806) | Callable definition: PhysicalPlan exists_plan() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; guard check(program.binding.wrapper == frontend::SqlWrapper::exists &&; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0088) |
| [B0089 · 826–826](../../../../../tests/unit/delta_lifecycle_test.cpp#L826) | Explanatory comments or spacing. |  |
| [B0090 · 827–827](../../../../../tests/unit/delta_lifecycle_test.cpp#L827) | Callable definition: Relation exists_sql_answer(bool value) | calls ; returns Relation{{Value{value}}} · [reviewed contract](#b0090) |
| [B0091 · 828–828](../../../../../tests/unit/delta_lifecycle_test.cpp#L828) | Explanatory comments or spacing. |  |
| [B0092 · 829–841](../../../../../tests/unit/delta_lifecycle_test.cpp#L829) | Callable definition: Relation a04_exists_core(const auto& plan, const Database& database) | calls source_catalog, check, size, empty; guard check(catalog.tables.size() == 1 && !catalog.tables\[0\].columns.empty(),; returns reference::evaluate(reference::input::catalog(catalog), source_query, database); growth push_back; source comment (unverified): // This source-level nullary query is an independent A04 definition of the · [reviewed contract](#b0092) |
| [B0093 · 842–842](../../../../../tests/unit/delta_lifecycle_test.cpp#L842) | Explanatory comments or spacing. |  |
| [B0094 · 843–854](../../../../../tests/unit/delta_lifecycle_test.cpp#L843) | Callable definition: void check_exists_results(DeltaRuntime& runtime, bool expected, const std::string& label) | calls check, collect_results, exists_sql_answer, has_answer; guard check(collect_results(runtime) == exists_sql_answer(expected), · [reviewed contract](#b0094) |
| [B0095 · 855–855](../../../../../tests/unit/delta_lifecycle_test.cpp#L855) | Explanatory comments or spacing. |  |
| [B0096 · 856–862](../../../../../tests/unit/delta_lifecycle_test.cpp#L856) | Callable definition: std::set&lt;SignedKey&gt; exists_flip(bool before, bool after) | calls emplace; returns expected; expected; growth emplace, insert · [reviewed contract](#b0096) |
| [B0097 · 863–863](../../../../../tests/unit/delta_lifecycle_test.cpp#L863) | Explanatory comments or spacing. |  |
| [B0098 · 864–913](../../../../../tests/unit/delta_lifecycle_test.cpp#L864) | Callable definition: void scalar_exists_pending_mapping() | calls exists_plan, check_exists_results, resize, sequence; guard check(a04_exists_core(runtime.plan(), database).empty() &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0098) |
| [B0099 · 914–914](../../../../../tests/unit/delta_lifecycle_test.cpp#L914) | Explanatory comments or spacing. |  |
| [B0100 · 915–1016](../../../../../tests/unit/delta_lifecycle_test.cpp#L915) | Callable definition: void deliver_one_acknowledges_after_callback_success() | calls self_join_scenario, harness, lifecycle_options, target; guard check(epoch.remaining() == wanted.size(),; growth push_back · [reviewed contract](#b0100) |
| [B0101 · 1017–1017](../../../../../tests/unit/delta_lifecycle_test.cpp#L1017) | Explanatory comments or spacing. |  |
| [B0102 · 1018–1042](../../../../../tests/unit/delta_lifecycle_test.cpp#L1018) | Callable definition: void facade_destruction_keeps_token_rollback_safe() | calls self_join_scenario, lifecycle_options, resize, at; guard check(output.remaining() == 0,; growth emplace, insert, resize; 1 loop sites · [reviewed contract](#b0102) |
| [B0103 · 1043–1043](../../../../../tests/unit/delta_lifecycle_test.cpp#L1043) | Explanatory comments or spacing. |  |
| [B0104 · 1044–1068](../../../../../tests/unit/delta_lifecycle_test.cpp#L1044) | Callable definition: void run() | calls self_join_scenario, shared_separator_scenario, deep_chain_scenario, pause_resume_each_output_prefix; 1 loop sites · [reviewed contract](#b0104) |
| [B0105 · 1069–1070](../../../../../tests/unit/delta_lifecycle_test.cpp#L1069) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0105) |
| [B0106 · 1071–1080](../../../../../tests/unit/delta_lifecycle_test.cpp#L1071) | Callable definition: int main() | calls run, what; returns 1; 0 · [reviewed contract](#b0106) |

## B0001

[Lines 1–26](../../../../../tests/unit/delta_lifecycle_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L26:sha256:30b78a0b2d36f53ef3c872976a9c9708f3e34c0ac65425ccbaf70fd383779069
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_lifecycle_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "evaluator.hpp", "native_input.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;initializer_list&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 27–29](../../../../../tests/unit/delta_lifecycle_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one test assertion with a diagnostic. |
| inputs / outputs | Boolean predicate and borrowed message enter; true returns, false throws std::runtime_error. |
| invariants | It catches no API or allocation error. |
| ownership | Inputs are borrowed; no data is retained. |
| failure | A false predicate throws std::runtime_error; it does not translate a product Error. |
| cost | One branch; false-path message construction is test diagnostic work. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0004

[Lines 31–42](../../../../../tests/unit/delta_lifecycle_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one action and require a crown::api::Error with the requested exact code. |
| inputs / outputs | Action, expected code, and label enter; returns after matching Error or throws test runtime_error. |
| invariants | Catches only crown::api::Error; bad_alloc and other exceptions propagate; wrong code fails. |
| ownership | Inputs are borrowed; no data is retained. |
| failure | A false predicate throws std::runtime_error; it does not translate a product Error. |
| cost | One branch; false-path message construction is test diagnostic work. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0006

[Lines 44–44](../../../../../tests/unit/delta_lifecycle_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one integer Value. |
| inputs / outputs | int64 enters; Value exits by value. |
| invariants | No runtime state or fixture changes. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | Small fixed scalar or fixture conversion. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0008

[Lines 46–50](../../../../../tests/unit/delta_lifecycle_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variables(std::initializer_list<std::size_t> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a sorted VariableSet from literal variable indices. |
| inputs / outputs | initializer_list of size_t enters; owning VariableSet exits. |
| invariants | Each index becomes VariableId; duplicates collapse under set insertion. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | Small fixed scalar or fixture conversion. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0010

[Lines 52–54](../../../../../tests/unit/delta_lifecycle_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04(const auto& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute a full-recomputation answer with the independent A04 reference evaluator. |
| inputs / outputs | Compiled plan catalog/query are converted to reference inputs; Database is borrowed; owning Relation exits. |
| invariants | This is the expected full answer for lifecycle comparisons, independent of DeltaRuntime result enumeration. |
| ownership | Plan and database inputs are borrowed for the oracle call; returned Relation/Row values own their scalar results. |
| failure | Reference evaluator exceptions propagate; test assertions report oracle mismatches separately. |
| cost | Full recomputation of the small literal fixture; no runtime performance bound. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0012

[Lines 56–64](../../../../../tests/unit/delta_lifecycle_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> signed_difference(const Relation& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the signed set difference between two full A04 Relations. |
| inputs / outputs | Before/after Relations are borrowed; owning set of (insert/erase, Row) exits. |
| invariants | Only rows present in after but absent before become insertions; reverse membership changes become erasures; no row appears twice. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | Small fixed scalar or fixture conversion. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0014

[Lines 66–91](../../../../../tests/unit/delta_lifecycle_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> a04_live(const auto& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project the SQL A04 answer into each compiled visible-factor scope. |
| inputs / outputs | Plan and full answer Relation are borrowed; vector of owning factor Relations exits. |
| invariants | Head-variable positions are mapped once; every visible scope variable must occur in the answer head or the test fails. |
| ownership | Plan and database inputs are borrowed for the oracle call; returned Relation/Row values own their scalar results. |
| failure | Reference evaluator exceptions propagate; test assertions report oracle mismatches separately. |
| cost | Walks the small A04 answer once per enumeration step and copies the factor keys; no runtime timing claim. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0016

[Lines 93–108](../../../../../tests/unit/delta_lifecycle_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> collect(DeltaRuntime::Epoch& epoch,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a committed DeltaRuntime::Epoch into unique signed row images. |
| inputs / outputs | Epoch is borrowed and repeatedly next()ed; owning set of operation/Row exits. |
| invariants | Ordinals must be contiguous, tuple layout token must match epoch.layout(), rows must be unique, and exhaustion releases the lease. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | Small fixed scalar or fixture conversion. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0018

[Lines 110–117](../../../../../tests/unit/delta_lifecycle_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation collect_results(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain the runtime’s committed SQL result cursor into an owning set Relation. |
| inputs / outputs | DeltaRuntime is borrowed; cursor tuples are exported into owned Rows and a Relation exits. |
| invariants | Duplicate results fail the fixture; the cursor is local and not retained. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | Small fixed scalar or fixture conversion. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0020

[Lines 119–141](../../../../../tests/unit/delta_lifecycle_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_committed(DeltaRuntime& runtime, const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a ready DeltaRuntime’s answer, result cursor, physical snapshot, live factors, and invariants with one expected database. |
| inputs / outputs | Runtime and expected Database are borrowed; computes A04 answer, drains public results, reads snapshot/live snapshot, and returns void or throws. |
| invariants | has_answer and rows match independent A04; physical tables/sequence match; Delta mode has exact projected live factors, maintenance mode has no live snapshot; check_invariants runs only at this ready barrier. |
| ownership | Plan and database inputs are borrowed for the oracle call; returned Relation/Row values own their scalar results. |
| failure | Reference evaluator exceptions propagate; test assertions report oracle mismatches separately. |
| cost | Full recomputation of the small literal fixture; no runtime performance bound. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0022

[Lines 143–151](../../../../../tests/unit/delta_lifecycle_test.cpp#L143); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Scenario {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold one literal query/update fixture description. |
| inputs / outputs | Owns label, lowered plan, table count, seed (table,row) pairs, update table/op/row. |
| invariants | Scenario is data only; it does not mutate a runtime. |
| ownership | Harness owns one DeltaRuntime and its oracle Database. Fixture rows and returned update/snapshot values are owning copies; expected A04 output is detached. |
| failure | Seed/update/oracle/API errors propagate; helper check() raises std::runtime_error on mismatches. |
| cost | Owns one small scenario description and its rows. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0024

[Lines 153–169](../../../../../tests/unit/delta_lifecycle_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan self_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-alias self-join over one edge table. |
| inputs / outputs | Creates E(src,dst), query outputs x,z,y for aliases left/right joined on the shared variable, and a three-node tree; returns PhysicalPlan. |
| invariants | The root separator is the join variable; the two aliases remain distinct occurrences over the same base table. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0026

[Lines 171–185](../../../../../tests/unit/delta_lifecycle_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shared_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-table query whose R/S leaves share separator x. |
| inputs / outputs | Catalog R(a,x), S(x,z), query/tree enter by local construction; PhysicalPlan exits. |
| invariants | Fixture plan has native leaves connected on x and projects a,x,z. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0028

[Lines 187–209](../../../../../tests/unit/delta_lifecycle_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan deep_chain_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a four-table chain query. |
| inputs / outputs | R(x,y), S(y,z), T(z,w), U(w,q), query and parent-before-child tree construct one PhysicalPlan. |
| invariants | The chain fixture has four native occurrences and shared adjacent separators; no input data are embedded in the plan. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0030

[Lines 211–215](../../../../../tests/unit/delta_lifecycle_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scenario self_join_scenario() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the self-join fixture to literal seed and target rows. |
| inputs / outputs | Returns Scenario with two reciprocal edges seeded and insert edge(1,1) target. |
| invariants | A04 answer changes by multiple output rows, as asserted by the prefix scenarios. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0032

[Lines 217–223](../../../../../tests/unit/delta_lifecycle_test.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scenario shared_separator_scenario() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the shared-separator fixture to its seed and erase target. |
| inputs / outputs | Seeds R rows (1,7),(2,7) and S rows (7,10),(7,11),(7,12); target erases R(1,7). |
| invariants | Several outputs depend on shared separator x=7; fixture is owned by returned Scenario. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0034

[Lines 225–232](../../../../../tests/unit/delta_lifecycle_test.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Scenario deep_chain_scenario() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the deep-chain fixture to seed paths and insert target. |
| inputs / outputs | Seeds S/T/U paths around y=7,z=8/9,w=10/11,q=100/101/110/111; target inserts R(1,7). |
| invariants | The answer expands through multiple later factors; returned Scenario owns the rows. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0035

[Lines 233–237](../../../../../tests/unit/delta_lifecycle_test.cpp#L233); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L233-L237:sha256:965a3677d162a52ad047eb97ca43df570e641709ab90cf2991d65e8ce54fcc30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_lifecycle_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 238–257](../../../../../tests/unit/delta_lifecycle_test.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Harness(const Scenario& scenario, DeltaOptions options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed a DeltaRuntime in maintenance mode, bootstrap delta mode, and validate its initial committed answer. |
| inputs / outputs | Scenario and requested DeltaOptions enter; Harness owns runtime/database; seed rows are applied contiguously and each output is required empty. |
| invariants | Runtime begins maintenance, then set_mode(delta) creates the live image; the final database and result/live projections match A04. |
| ownership | Harness owns one DeltaRuntime and its oracle Database. Fixture rows and returned update/snapshot values are owning copies; expected A04 output is detached. |
| failure | Seed insertion errors or product API failures propagate; duplicate seed/mismatch throws runtime_error. |
| cost | One runtime plus the scenario’s fixed seed count and a single live-image bootstrap. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0038

[Lines 259–262](../../../../../tests/unit/delta_lifecycle_test.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate target(const Scenario& scenario) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the next contiguous update using Scenario target fields. |
| inputs / outputs | Scenario is borrowed; update sequence is runtime.sequence()+1 with configured table/op/values. |
| invariants | No runtime mutation; returned PhysicalSetUpdate owns its Row. |
| ownership | Harness owns one DeltaRuntime and its oracle Database. Fixture rows and returned update/snapshot values are owning copies; expected A04 output is detached. |
| failure | Seed/update/oracle/API errors propagate; helper check() raises std::runtime_error on mismatches. |
| cost | Small literal fixtures only; no elapsed-time or memory claim. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0040

[Lines 264–269](../../../../../tests/unit/delta_lifecycle_test.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate inverse(const Scenario& scenario) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the inverse operation at the next sequence. |
| inputs / outputs | Scenario is borrowed; flips insert/erase and copies the target row/table. |
| invariants | Does not apply or commit the inverse. |
| ownership | Harness owns one DeltaRuntime and its oracle Database. Fixture rows and returned update/snapshot values are owning copies; expected A04 output is detached. |
| failure | Seed/update/oracle/API errors propagate; helper check() raises std::runtime_error on mismatches. |
| cost | Small literal fixtures only; no elapsed-time or memory claim. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0042

[Lines 271–279](../../../../../tests/unit/delta_lifecycle_test.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database after(const PhysicalSetUpdate& update) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the Harness database and apply set membership semantics for one update. |
| inputs / outputs | Update and Harness database are borrowed; owning Database copy exits. |
| invariants | Duplicate insert and absent erase leave membership unchanged; helper does not advance runtime. |
| ownership | Harness owns one DeltaRuntime and its oracle Database. Fixture rows and returned update/snapshot values are owning copies; expected A04 output is detached. |
| failure | Seed/update/oracle/API errors propagate; helper check() raises std::runtime_error on mismatches. |
| cost | Small literal fixtures only; no elapsed-time or memory claim. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0044

[Lines 281–284](../../../../../tests/unit/delta_lifecycle_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> expected(const PhysicalSetUpdate& update) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute expected signed output for one update by A04 before/after recomputation. |
| inputs / outputs | Update enters by const reference; uses current database and after() copy; owning signed-row set exits. |
| invariants | This oracle is derived from full answer set differences, not internal DeltaMetrics. |
| ownership | Harness owns one DeltaRuntime and its oracle Database. Fixture rows and returned update/snapshot values are owning copies; expected A04 output is detached. |
| failure | Seed/update/oracle/API errors propagate; helper check() raises std::runtime_error on mismatches. |
| cost | Small literal fixtures only; no elapsed-time or memory claim. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0046

[Lines 286–298](../../../../../tests/unit/delta_lifecycle_test.cpp#L286); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> apply_and_check(const PhysicalSetUpdate& update,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one update and compare committed signed output and resulting runtime state with A04. |
| inputs / outputs | Update and label enter; computes wanted rows, calls runtime.apply, checks sequence, drains Epoch, updates oracle Database, validates after state, and returns observed signed-row set. |
| invariants | Output equals the independent A04 set difference; public results, physical snapshot, live factors (if delta mode), and invariants are checked after output lease closes. |
| ownership | The Epoch returned by apply owns committed output until collect() drains it; exported expected/observed Rows and next Database are values. |
| failure | Product exceptions propagate; mismatches throw runtime_error. The test has no allocation injector. |
| cost | One small full before/after reference evaluation plus one runtime apply and result drain. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0048

[Lines 300–302](../../../../../tests/unit/delta_lifecycle_test.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publish_database(const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance only the caller-side oracle Database after a runtime commit or intentional discard. |
| inputs / outputs | Update is borrowed; Harness database replaced by after(update). |
| invariants | No runtime input is submitted and no output row is published by this helper. |
| ownership | Harness owns one DeltaRuntime and its oracle Database. Fixture rows and returned update/snapshot values are owning copies; expected A04 output is detached. |
| failure | Database copy/allocation failures propagate; no runtime error is caught. |
| cost | Copies and edits one small literal database. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0049

[Lines 303–304](../../../../../tests/unit/delta_lifecycle_test.cpp#L303); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L303-L304:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_lifecycle_test.cpp: struct Harness. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 305–311](../../../../../tests/unit/delta_lifecycle_test.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions lifecycle_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Request deterministic options for the lifecycle harness. |
| inputs / outputs | No inputs; returns DeltaOptions with maintenance initial mode, on_output live policy, and automatic completion. |
| invariants | The options are requested settings; automatic completion resolves according to the runtime policy and is not itself measured work. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | Small fixed scalar or fixture conversion. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0052

[Lines 313–320](../../../../../tests/unit/delta_lifecycle_test.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_replay_work_partition(const DeltaMetrics& metrics,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require replay phase work counters to sum to aggregate delta work. |
| inputs / outputs | DeltaMetrics is borrowed; no output. |
| invariants | Preparation + first + results + termination + finalization must equal total work for the exercised replay path. |
| ownership | PendingEpoch is borrowed and remains owned by its caller. Returned metrics/stage spans are borrowed only while the token remains open. |
| failure | Contract mismatch throws std::runtime_error; expected product errors are handled by expect_error at scenario sites. |
| cost | Reads five counters and one total; this is an accounting invariant, not elapsed time. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0054

[Lines 322–339](../../../../../tests/unit/delta_lifecycle_test.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void step_once(DeltaRuntime::PendingEpoch& pending, std::size_t expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one pending epoch step and validate accepted-row accounting. |
| inputs / outputs | PendingEpoch borrowed, expected output count and label enter; calls step() once, returns void. |
| invariants | Accepted rises by at most one; core_result raises by exactly one; progress/prepared do not raise it; a fixture with more rows cannot prepare after its first accepted row. |
| ownership | PendingEpoch is borrowed and remains owned by its caller. Returned metrics/stage spans are borrowed only while the token remains open. |
| failure | Test runtime_error on counter/transition mismatch; expected product errors are asserted by calling scenarios. |
| cost | At most one pending step and a fixed number of metric reads. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0056

[Lines 341–352](../../../../../tests/unit/delta_lifecycle_test.cpp#L341); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drive_to_prefix(DeltaRuntime::PendingEpoch& pending, std::size_t prefix,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a token until its accepted core-row counter reaches a requested prefix. |
| inputs / outputs | PendingEpoch borrowed; prefix, full output count, label enter; no output. |
| invariants | Never steps after prepared; exits only at the exact prefix; a 100000-call safety guard fails a nonprogressing fixture. |
| ownership | PendingEpoch is borrowed and remains owned by its caller. Returned metrics/stage spans are borrowed only while the token remains open. |
| failure | Contract mismatch throws std::runtime_error; expected product errors are handled by expect_error at scenario sites. |
| cost | Data-dependent repeated step calls until the small target prefix; guard is an iteration limit, not a time bound. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0058

[Lines 354–363](../../../../../tests/unit/delta_lifecycle_test.cpp#L354); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drive_prepared(DeltaRuntime::PendingEpoch& pending, std::size_t expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a pending token to epoch_prepared and verify complete A04 row count. |
| inputs / outputs | PendingEpoch borrowed; expected count/label enter; loops step() until prepared. |
| invariants | Accepted count at prepare equals expected full A04 signed output size. |
| ownership | PendingEpoch is borrowed and remains owned by its caller. Returned metrics/stage spans are borrowed only while the token remains open. |
| failure | Contract mismatch throws std::runtime_error; expected product errors are handled by expect_error at scenario sites. |
| cost | Runs remaining route/preparation work for the tiny fixture; no delay guarantee. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0060

[Lines 365–391](../../../../../tests/unit/delta_lifecycle_test.cpp#L365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_barrier(Harness& harness, const PhysicalSetUpdate& update,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check named runtime readers and writers are blocked while a token is pending. |
| inputs / outputs | Harness, update, label enter; calls results/core_results/current_view/snapshot/live_snapshot/storage_statistics/has_answer/set_mode/apply. |
| invariants | Each named access must throw runtime_busy; committed sequence is unchanged. Coverage is limited to these listed calls. |
| ownership | PendingEpoch is borrowed and remains owned by its caller. Returned metrics/stage spans are borrowed only while the token remains open. |
| failure | Contract mismatch throws std::runtime_error; expected product errors are handled by expect_error at scenario sites. |
| cost | Reads fixed counters/timings and advances at most one pending step per call unless the named loop repeats it. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0062

[Lines 393–399](../../../../../tests/unit/delta_lifecycle_test.cpp#L393); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_timings(const DeltaTimings& left, const DeltaTimings& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the five recorded DeltaTimings phase fields exactly. |
| inputs / outputs | Two DeltaTimings values are borrowed; returns bool over propagation, internal_delta, output_mapping, serialization, sink_wait. |
| invariants | No clock is read and no timing value is normalized. |
| ownership | PendingEpoch is borrowed and remains owned by its caller. Returned metrics/stage spans are borrowed only while the token remains open. |
| failure | Contract mismatch throws std::runtime_error; expected product errors are handled by expect_error at scenario sites. |
| cost | Five scalar comparisons; no timing claim. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0064

[Lines 401–408](../../../../../tests/unit/delta_lifecycle_test.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool monotone_timings(const DeltaTimings& earlier,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each of five DeltaTimings fields is monotone across two snapshots. |
| inputs / outputs | Earlier/later timings borrowed; returns bool. |
| invariants | Compares only the five phase totals; it does not assert elapsed wall-time accuracy or a lower bound. |
| ownership | PendingEpoch is borrowed and remains owned by its caller. Returned metrics/stage spans are borrowed only while the token remains open. |
| failure | Contract mismatch throws std::runtime_error; expected product errors are handled by expect_error at scenario sites. |
| cost | Five scalar comparisons. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0066

[Lines 410–482](../../../../../tests/unit/delta_lifecycle_test.cpp#L410); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pause_resume_each_output_prefix(const Scenario& scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise pause/resume at every accepted output prefix for each self-join, shared-separator, and deep-chain fixture. |
| inputs / outputs | For every prefix below full A04 delta size, creates fresh Harness, begins update, drives to prefix, asserts runtime_busy barrier, tests invalid early resume/commit or paused step at prefix 0, pauses/resumes, drives prepared, commits, drains signed rows, checks A04 and then applies inverse update. |
| invariants | Pending and runtime states move together; pause/rejected calls preserve token, accepted count, and timings; committed rows equal the same before/after A04 difference; inverse produces the full reverse difference. |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | Named expected errors: invalid_delta_state, runtime_busy, delta_paused. Other runtime failures propagate; assertion mismatch is runtime_error. |
| cost | Repeats a small transaction for every prefix in all three fixtures, then performs an inverse transaction; monotonic phase counters are not timing benchmarks. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0068

[Lines 484–517](../../../../../tests/unit/delta_lifecycle_test.cpp#L484); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void discard_each_output_prefix(const Scenario& scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise explicit discard after every output prefix and verify all required internal rows still run. |
| inputs / outputs | For each prefix, begins update, advances to prefix, calls PendingEpoch::discard(), checks committed empty/inactive Epoch, accepted/discarded counters and replay-work partition, updates caller DB and checks A04/live state, then applies inverse. |
| invariants | discard() drains and commits the input while suppressing all public records; accepted/discarded count equals full A04 delta size, and the subsequent inverse proves live state was updated. |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | No injected failure; mismatched disposition/counters/oracle throws runtime_error. |
| cost | One discard for each prefix, full internal completion, and one inverse update per scenario. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0070

[Lines 519–548](../../../../../tests/unit/delta_lifecycle_test.cpp#L519); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void start_drain_drops_staged_output(const Scenario& scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start output drain after a staged prefix, continue through all work, and commit no public output. |
| inputs / outputs | Begins with on_output policy, advances to at most one prefix, pauses, calls start_drain(), drains to prepared, checks every stage output interval is zero, commits and checks empty output/discard count/work partition, then checks state and inverse update. |
| invariants | start_drain clears staged public spool intervals but does not skip core projection/live maintenance; input is committed and A04 state remains correct. |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | No injected failure; expected output is empty by explicit retention disable, not by a resource quota. |
| cost | One small full fixture update after at most one staged output prefix. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0072

[Lines 550–585](../../../../../tests/unit/delta_lifecycle_test.cpp#L550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void abort_each_output_prefix(const Scenario& scenario, bool destroy_token) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare explicit rollback with PendingEpoch destruction at every output prefix, then retry the exact same input. |
| inputs / outputs | For each prefix, saves committed sequence/A04 answer; either destroys scoped pending token or calls rollback(); checks old state/ready, then begins same update at same sequence, commits exact A04 output and applies inverse. |
| invariants | Rollback/destruction aborts unpublished physical/support/live changes; neither consumes sequence nor changes committed answer. The retry reuses same runtime and input sequence. This scenario does not destroy the DeltaRuntime facade. |
| ownership | Harness retains DeltaRuntime; the token is separately owned and either explicitly rolled back or destroyed before retry. No output artifact was committed by the aborted token. |
| failure | Only mismatches throw runtime_error; no product error or allocation fault is selected. |
| cost | For every fixture output prefix, constructs one abort and one retry, plus inverse update. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0074

[Lines 587–634](../../../../../tests/unit/delta_lifecycle_test.cpp#L587); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void owning_input_and_move_lifecycle(const Scenario& scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify begin owns update row values and a moved DeltaRuntime facade remains paired with its PendingEpoch. |
| inputs / outputs | Copies source update into begin(), mutates/clears/shrinks caller copy, moves PendingEpoch and runtime facade, drains/commits and compares exact A04 output; checks moved runtime, snapshot, next inverse input. |
| invariants | Input bytes used by pending update are independent of mutated caller Row; token move transfers token ownership; runtime facade move preserves its shared Impl; committed and next-update answers match A04. This is not facade destruction. |
| ownership | PendingEpoch owns imported source values/pins; DeltaRuntime move transfers its shared implementation handle. Epoch output and returned Rows remain owning values. |
| failure | No expected product exception; mismatch throws runtime_error. |
| cost | One small update and inverse per self-join/shared-separator scenario. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0076

[Lines 636–660](../../../../../tests/unit/delta_lifecycle_test.cpp#L636); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical_policy_pause_resume(const Scenario& scenario,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pause/resume under explicit incremental+anchored and eager+root-first option pairs. |
| inputs / outputs | Builds Harness with requested LiveMaintenance/DeltaCompletion, asserts selected completion, begins update, accepts one prefix, pauses/resumes, drains/prepares, commits A04 rows, validates state, applies inverse. |
| invariants | Options chosen are explicit; both modes preserve same public signed answer delta and subsequent state. The test does not establish a cost/delay theorem for these policies. |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | Named invalid-state/runtime_busy/resource errors are checked where specified; oracle mismatches throw std::runtime_error. No allocation seam is installed in this executable. |
| cost | Repeats tiny fixture transactions over output prefixes and checks exact row/counter/state oracles; timing checks are monotonicity/equality assertions, not a benchmark. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0078

[Lines 662–680](../../../../../tests/unit/delta_lifecycle_test.cpp#L662); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drain_resumes_paused_token(const Scenario& scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify retaining drain resumes a paused token and preserves prepared output. |
| inputs / outputs | Begins update, advances one row, pauses, calls drain(), expects epoch_prepared, commits retained Epoch, compares its rows to A04, checks after state and inverse. |
| invariants | drain() implicitly resumes pause and retains output under current policy; it is distinct from start_drain(). |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | No fault injection; assertion mismatch throws runtime_error. |
| cost | One partial-prefix then full drain and inverse update. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0080

[Lines 682–691](../../../../../tests/unit/delta_lifecycle_test.cpp#L682); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projection_count_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-table projection where a source-only change leaves the distinct projected answer unchanged. |
| inputs / outputs | R(x,y) query projects x; returned PhysicalPlan supports seeded row (1,10) and later row (1,11). |
| invariants | Both source rows contribute the same projected x=1, so inserting the second source row has empty result-set delta. No runtime is created here. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0082

[Lines 693–702](../../../../../tests/unit/delta_lifecycle_test.cpp#L693); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan filtered_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-table query filtered by a constant predicate. |
| inputs / outputs | R(x,flag) query atom binds flag=1; returns PhysicalPlan. |
| invariants | The later row with flag=0 is excluded from the query answer; fixture is used for empty-delta route behavior. |
| ownership | Catalog, query/tree temporaries, and returned lowered plan are owning values; no DeltaRuntime is created here. |
| failure | Planner/frontend diagnostics propagate or are converted to test std::runtime_error at the fixture boundary. |
| cost | Compiles one fixed tiny query/tree fixture; not runtime update cost. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0084

[Lines 704–725](../../../../../tests/unit/delta_lifecycle_test.cpp#L704); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish_empty_delta(DeltaRuntime& runtime, Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish and commit an update known to have empty full-recomputation delta. |
| inputs / outputs | Copies database, applies set membership change, confirms signed A04 before/after difference is empty, begins update, drives to prepared with expected accepted count 0, commits empty output, updates oracle DB and checks committed state. |
| invariants | No public rows are emitted; valid no-op/count-only/filtered input still commits its sequence and exact physical state. |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | No expected Error; false empty-delta premise fails runtime_error. |
| cost | Two small A04 evaluations, one pending update, and one committed state check. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0086

[Lines 727–804](../../../../../tests/unit/delta_lifecycle_test.cpp#L727); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void no_op_count_only_filtered_and_maintenance() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise duplicate no-op, count-only projection, filtered update, maintenance drain, and maintenance-to-delta bootstrap. |
| inputs / outputs | Contains four cases: duplicate edge insert; duplicate projected x; filtered row; shared-separator maintenance-mode erase followed by set_mode(delta) and restore insert. |
| invariants | Empty answer deltas are checked with A04; maintenance path produces no delta spool/live image; after explicit delta bootstrap, a restoring update emits the A04 difference and live snapshot is current. |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | Only fixture mismatches throw runtime_error; no allocation/work fault injected. |
| cost | Three empty-output fixtures and one maintenance/bootstrapped delta update. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0088

[Lines 806–825](../../../../../tests/unit/delta_lifecycle_test.cpp#L806); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan exists_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a normalized SQL scalar EXISTS plan over one source relation. |
| inputs / outputs | Binds \`SELECT EXISTS(SELECT NULL FROM r)\`, normalizes it, verifies SQL wrapper and one core atom, constructs nullary tree, returns lowered normalized PhysicalPlan. |
| invariants | Binding result uses source catalog; core query is one nullary atom whose truth tracks nonempty source relation. |
| ownership | The bound/normalized query and returned plan/relation rows are owning values. Runtime/result-cursor references are borrowed only during checks. |
| failure | Binding/normalization diagnostics become std::runtime_error; planner errors propagate. |
| cost | Binds and lowers one fixed scalar query, not a measured workload. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/delta_transition_spec.md § SQL output and event order](../../../../delta_transition_spec.md) |

## B0090

[Lines 827–827](../../../../../tests/unit/delta_lifecycle_test.cpp#L827); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation exists_sql_answer(bool value) { return Relation{{Value{value}}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the SQL wrapper’s one-row Boolean result Relation. |
| inputs / outputs | Bool enters; owning Relation with one \`Value{bool}\` row exits. |
| invariants | This wrapper relation is separate from nullary core answer truth. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | One Boolean Value and one-row Relation. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0092

[Lines 829–841](../../../../../tests/unit/delta_lifecycle_test.cpp#L829); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04_exists_core(const auto& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute core truth for the EXISTS source using an independent A04 source-level query. |
| inputs / outputs | Plan source catalog and Database are borrowed; constructs one source atom query and returns reference evaluator Relation. |
| invariants | The A04 source query is intentionally nonnullary and independent of the normalized nullary core catalog; nonempty relation maps to one empty core tuple. |
| ownership | The bound/normalized query and returned plan/relation rows are owning values. Runtime/result-cursor references are borrowed only during checks. |
| failure | Frontend binding diagnostics become std::runtime_error; API errors propagate except exact expected lifecycle errors. |
| cost | One fixed scalar EXISTS query and one-row source fixture; no complexity or latency claim. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/delta_transition_spec.md § SQL output and event order](../../../../delta_transition_spec.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0094

[Lines 843–854](../../../../../tests/unit/delta_lifecycle_test.cpp#L843); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_exists_results(DeltaRuntime& runtime, bool expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check current SQL Boolean row, core truth, nullary live factor, and invariants for EXISTS. |
| inputs / outputs | Runtime, expected bool, label enter; drains SQL results, checks has_answer, reads live snapshot, runs invariants. |
| invariants | Expected SQL result is one Boolean row while the core live factor is \`{empty tuple}\` for true and empty for false. |
| ownership | The bound/normalized query and returned plan/relation rows are owning values. Runtime/result-cursor references are borrowed only during checks. |
| failure | Mismatch throws runtime_error; runtime read failures propagate. |
| cost | One current SQL-result traversal plus one small live snapshot read. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/delta_transition_spec.md § SQL output and event order](../../../../delta_transition_spec.md) |

## B0096

[Lines 856–862](../../../../../tests/unit/delta_lifecycle_test.cpp#L856); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> exists_flip(bool before, bool after) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the signed row replacement for a Boolean truth flip. |
| inputs / outputs | Before/after bool enter; owning SignedKey set exits. |
| invariants | Equal truth yields empty set; changed truth yields erase old bool and insert new bool. |
| ownership | Input scalar values are copied into the returned owning Value/Row/container. |
| failure | Construction/allocation errors propagate; no product error is caught. |
| cost | At most two one-field rows. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0098

[Lines 864–913](../../../../../tests/unit/delta_lifecycle_test.cpp#L864); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_exists_pending_mapping() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify pending scalar EXISTS mapping from false→true and committed update from true→false. |
| inputs / outputs | Starts empty runtime; computes source A04 before/after; begins insert, steps to prepared, commits and checks exact erase(false),insert(true) ordinals/values; applies erase and checks reverse. |
| invariants | Core nullary result changes once, but SQL output is exactly two replacement rows in order; runtime SQL/core/live result and invariants match each state. |
| ownership | PendingEpoch owns private update; committed Epoch owns two SignedResult rows until next() transfers them. |
| failure | Mismatched SQL mapping fails runtime_error; no expected product Error or allocation injection. |
| cost | One insert and one erase, each checked against tiny independent A04 source truth. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [docs/delta_transition_spec.md § SQL output and event order](../../../../delta_transition_spec.md) |

## B0100

[Lines 915–1016](../../../../../tests/unit/delta_lifecycle_test.cpp#L915); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deliver_one_acknowledges_after_callback_success() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check callback success is the acknowledgement boundary for a committed output row. |
| inputs / outputs | Creates a three-row self-join Epoch; sink throws on first callback, retries same front, tests reentrant next runtime_busy, then serializer throws, then serializer and sink both succeed in order, then callback requests discard. |
| invariants | Thrown callback leaves same ordinal/operation/tuple and remaining count; serializer failure skips sink; success removes exactly one front; callback discard is deferred until borrowed row returns and then releases unread remainder. Exact row identity/order is checked. |
| ownership | Epoch owns committed FIFO nodes; callback receives a borrowed const SignedResult until it returns. Copies saved by the fixture own their Row/tuple values. |
| failure | Catches only the two deliberately thrown std::runtime_error callbacks and expected Error runtime_busy. No external durability or exactly-once guarantee. |
| cost | Five callback attempts over three rows with phase timing monotonicity; not throughput or wall-time budget. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0102

[Lines 1018–1042](../../../../../tests/unit/delta_lifecycle_test.cpp#L1018); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void facade_destruction_keeps_token_rollback_safe() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a PendingEpoch remains active and can roll back after its DeltaRuntime facade scope ends. |
| inputs / outputs | Builds/seeds a local runtime, switches to delta, stores \`runtime.begin()\` token outside scope, steps once, exits runtime scope, then checks token active and calls rollback. |
| invariants | The token’s shared implementation owner keeps pending state available after facade destruction; rollback closes token. This does not assert that backing state was destroyed at facade scope exit. |
| ownership | Each scenario owns its Harness, pending token, committed Epoch and expected A04 rows. Callback SignedResult arguments are borrowed for the callback; next() returns owning SignedResult values. |
| failure | Named invalid-state/runtime_busy/resource errors are checked where specified; oracle mismatches throw std::runtime_error. No allocation seam is installed in this executable. |
| cost | Repeats tiny fixture transactions over output prefixes and checks exact row/counter/state oracles; timing checks are monotonicity/equality assertions, not a benchmark. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md) |

## B0104

[Lines 1044–1068](../../../../../tests/unit/delta_lifecycle_test.cpp#L1044); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixed lifecycle fixture matrix. |
| inputs / outputs | No inputs; runs pause/resume, discard, drain, abort/destruction, policy, no-op, EXISTS, callback, and facade-lifetime scenarios. |
| invariants | Any mismatch propagates to main; no runtime behavior is added by orchestration. |
| ownership | run() scopes all fixtures; main retains no runtime after return. |
| failure | Catches std::exception, prints the diagnostic, returns 1; success prints a source-defined message. This packet does not claim the executable was run. |
| cost | Dispatches the fixed lifecycle matrix if invoked; no duration threshold. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |

## B0105

[Lines 1069–1070](../../../../../tests/unit/delta_lifecycle_test.cpp#L1069); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1069-L1070:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_lifecycle_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0106

[Lines 1071–1080](../../../../../tests/unit/delta_lifecycle_test.cpp#L1071); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute run() and convert an uncaught std::exception to process status. |
| inputs / outputs | No arguments; on success prints fixed message/returns 0, on exception prints what()/returns 1. |
| invariants | Source behavior only; packet does not claim this executable ran. |
| ownership | run() scopes all fixtures; main retains no runtime after return. |
| failure | Catches std::exception, prints the diagnostic, returns 1; success prints a source-defined message. This packet does not claim the executable was run. |
| cost | Dispatches the fixed lifecycle matrix if invoked; no duration threshold. |
| Design | [tests/unit/delta_lifecycle_test.cpp](../../../../../tests/unit/delta_lifecycle_test.cpp) |
