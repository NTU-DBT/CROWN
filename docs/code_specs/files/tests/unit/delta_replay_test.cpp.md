# `tests/unit/delta_replay_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_replay_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `51770e06877ee066c6f7206b85ed51eddbdf11eeb178ac77e0696305bc145001`. 771 lines partitioned into 77 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/delta_replay_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 27–29](../../../../../tests/unit/delta_replay_test.cpp#L27) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 30–30](../../../../../tests/unit/delta_replay_test.cpp#L30) | Explanatory comments or spacing. |  |
| [B0004 · 31–42](../../../../../tests/unit/delta_replay_test.cpp#L31) | Callable definition: template &lt;class Action&gt; void expect_error_code(Action&& action, const std::string& expected, const std::string& label) | calls action, check, code; guard check(failure.code() == expected, · [reviewed contract](#b0004) |
| [B0005 · 43–43](../../../../../tests/unit/delta_replay_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0006 · 44–57](../../../../../tests/unit/delta_replay_test.cpp#L44) | Callable definition: void check_profile_text(const DeltaRuntimeProfile& profile, const std::string& label) | calls check, empty, find; guard check(!text.empty() && text.find('\0') == std::string_view::npos,; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 58–58](../../../../../tests/unit/delta_replay_test.cpp#L58) | Explanatory comments or spacing. |  |
| [B0008 · 59–59](../../../../../tests/unit/delta_replay_test.cpp#L59) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 60–60](../../../../../tests/unit/delta_replay_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0010 · 61–65](../../../../../tests/unit/delta_replay_test.cpp#L61) | Callable definition: VariableSet variables(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 66–66](../../../../../tests/unit/delta_replay_test.cpp#L66) | Explanatory comments or spacing. |  |
| [B0012 · 67–76](../../../../../tests/unit/delta_replay_test.cpp#L67) | Callable definition: DeltaOptions replay_options() | calls ; returns result · [reviewed contract](#b0012) |
| [B0013 · 77–77](../../../../../tests/unit/delta_replay_test.cpp#L77) | Explanatory comments or spacing. |  |
| [B0014 · 78–80](../../../../../tests/unit/delta_replay_test.cpp#L78) | Callable definition: Relation a04(const auto& plan, const Database& database) | calls reference::evaluate, reference::input::catalog, catalog, reference::input::query; returns reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()… · [reviewed contract](#b0014) |
| [B0015 · 81–81](../../../../../tests/unit/delta_replay_test.cpp#L81) | Explanatory comments or spacing. |  |
| [B0016 · 82–90](../../../../../tests/unit/delta_replay_test.cpp#L82) | Callable definition: std::set&lt;SignedKey&gt; difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 91–91](../../../../../tests/unit/delta_replay_test.cpp#L91) | Explanatory comments or spacing. |  |
| [B0018 · 92–107](../../../../../tests/unit/delta_replay_test.cpp#L92) | Callable definition: Relation drain_current(SupportRuntime::ResultCursor cursor, const storage::TupleLayout& expected_layout, const std::string& label) | calls check, layout, same_token, next; guard check(cursor.layout().same_token(expected_layout),; returns result; growth insert; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 108–108](../../../../../tests/unit/delta_replay_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0020 · 109–134](../../../../../tests/unit/delta_replay_test.cpp#L109) | Callable definition: std::vector&lt;Relation&gt; a04_live(const auto& plan, const Relation& answer) | calls query, size, try_emplace, reserve; guard check(position != head_positions.end(),; returns result; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0020) |
| [B0021 · 135–135](../../../../../tests/unit/delta_replay_test.cpp#L135) | Explanatory comments or spacing. |  |
| [B0022 · 136–140](../../../../../tests/unit/delta_replay_test.cpp#L136) | Type/record definition: struct Event |  · [reviewed contract](#b0022) |
| [B0023 · 141–142](../../../../../tests/unit/delta_replay_test.cpp#L141) | declares types or opens a type body. |  · [reviewed contract](#b0023) |
| [B0024 · 143–152](../../../../../tests/unit/delta_replay_test.cpp#L143) | Callable definition: public: ReplayRun(PhysicalPlan plan, std::size_t table_count) : runtime_(std::move(plan), replay_options()) | calls runtime_, std::move, replay_options, resize; guard check(runtime_.completion() == DeltaCompletion::ordered_replay,; growth resize · [reviewed contract](#b0024) |
| [B0025 · 153–153](../../../../../tests/unit/delta_replay_test.cpp#L153) | Explanatory comments or spacing. |  |
| [B0026 · 154–165](../../../../../tests/unit/delta_replay_test.cpp#L154) | Callable definition: void seed(TableId table, Row row, const std::string& label) | calls apply, check, sequence, remaining; guard check(epoch.sequence() == sequence && epoch.remaining() == 0 &&; growth insert · [reviewed contract](#b0026) |
| [B0027 · 166–166](../../../../../tests/unit/delta_replay_test.cpp#L166) | Explanatory comments or spacing. |  |
| [B0028 · 167–174](../../../../../tests/unit/delta_replay_test.cpp#L167) | Callable definition: void bootstrap(const std::string& label) | calls check, mode, set_mode, live_snapshot; guard check(runtime_.mode() == DeltaMode::maintenance, · [reviewed contract](#b0028) |
| [B0029 · 175–175](../../../../../tests/unit/delta_replay_test.cpp#L175) | Explanatory comments or spacing. |  |
| [B0030 · 176–181](../../../../../tests/unit/delta_replay_test.cpp#L176) | Callable definition: void maintenance(const std::string& label) | calls set_mode, check, live_snapshot, check_current; guard check(!runtime_.live_snapshot(), · [reviewed contract](#b0030) |
| [B0031 · 182–182](../../../../../tests/unit/delta_replay_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0032 · 183–272](../../../../../tests/unit/delta_replay_test.cpp#L183) | Callable definition: Event apply(TableId table, SetOperation operation, Row row, const std::string& label) | calls a04, plan, at, insert; guard check(changed, label + ": source update did not cross set membership");; returns result; growth insert, push_back; 2 loop sites · [reviewed contract](#b0032) |
| [B0033 · 273–273](../../../../../tests/unit/delta_replay_test.cpp#L273) | Explanatory comments or spacing. |  |
| [B0034 · 274–274](../../../../../tests/unit/delta_replay_test.cpp#L274) | Callable definition: \[\[nodiscard\]\] const DeltaRuntime& runtime() const | calls ; returns runtime_ · [reviewed contract](#b0034) |
| [B0035 · 275–275](../../../../../tests/unit/delta_replay_test.cpp#L275) | Callable definition: \[\[nodiscard\]\] const Database& database() const | calls ; returns database_ · [reviewed contract](#b0035) |
| [B0036 · 276–276](../../../../../tests/unit/delta_replay_test.cpp#L276) | Explanatory comments or spacing. |  |
| [B0037 · 277–299](../../../../../tests/unit/delta_replay_test.cpp#L277) | Callable definition: private: void check_current(const std::string& label) | calls a04, plan, check, has_answer; guard check(runtime_.has_answer() == !expected.empty(), · [reviewed contract](#b0037) |
| [B0038 · 300–305](../../../../../tests/unit/delta_replay_test.cpp#L300) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0038) |
| [B0039 · 306–318](../../../../../tests/unit/delta_replay_test.cpp#L306) | Callable definition: PhysicalPlan root_child_plan(PhysicalOptions physical = {}) | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree, physical) · [reviewed contract](#b0039) |
| [B0040 · 319–319](../../../../../tests/unit/delta_replay_test.cpp#L319) | Explanatory comments or spacing. |  |
| [B0041 · 320–343](../../../../../tests/unit/delta_replay_test.cpp#L320) | Callable definition: void runtime_profile_names_actual_backend() | calls runtime, root_child_plan, check, plan; guard check(runtime.plan().guarantee().storage_backend == expected,; 2 loop sites; source comment (unverified): // Profile text has static lifetime, including the selected backend label. · [reviewed contract](#b0041) |
| [B0042 · 344–344](../../../../../tests/unit/delta_replay_test.cpp#L344) | Explanatory comments or spacing. |  |
| [B0043 · 345–403](../../../../../tests/unit/delta_replay_test.cpp#L345) | Callable definition: void runtime_profile_reports_effective_strategy_and_limits() | calls default_runtime, root_child_plan, profile, check; guard check(automatic.mode == DeltaMode::delta &&; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 404–404](../../../../../tests/unit/delta_replay_test.cpp#L404) | Explanatory comments or spacing. |  |
| [B0045 · 405–442](../../../../../tests/unit/delta_replay_test.cpp#L405) | Callable definition: void runtime_profile_tracks_active_mode_changes() | calls runtime, root_child_plan, profile, check; guard check(maintenance.mode == DeltaMode::maintenance && · [reviewed contract](#b0045) |
| [B0046 · 443–443](../../../../../tests/unit/delta_replay_test.cpp#L443) | Explanatory comments or spacing. |  |
| [B0047 · 444–454](../../../../../tests/unit/delta_replay_test.cpp#L444) | Callable definition: void runtime_profile_rejects_incompatible_replay_options() | calls expect_error_code, DeltaRuntime, root_child_plan; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 455–455](../../../../../tests/unit/delta_replay_test.cpp#L455) | Explanatory comments or spacing. |  |
| [B0049 · 456–462](../../../../../tests/unit/delta_replay_test.cpp#L456) | Callable definition: DeltaRuntimeProfile detached_delta_profile() | calls runtime, root_child_plan, profile; returns runtime.profile() · [reviewed contract](#b0049) |
| [B0050 · 463–463](../../../../../tests/unit/delta_replay_test.cpp#L463) | Explanatory comments or spacing. |  |
| [B0051 · 464–472](../../../../../tests/unit/delta_replay_test.cpp#L464) | Callable definition: void runtime_profile_text_outlives_its_facade() | calls detached_delta_profile, check, check_profile_text; guard check(detached.mode == DeltaMode::delta && · [reviewed contract](#b0051) |
| [B0052 · 473–473](../../../../../tests/unit/delta_replay_test.cpp#L473) | Explanatory comments or spacing. |  |
| [B0053 · 474–505](../../../../../tests/unit/delta_replay_test.cpp#L474) | Callable definition: void ancestor_child_crossings_have_no_replay_tail() | calls run, root_child_plan, seed, n; guard check(a04(run.runtime().plan(), run.database()).empty(),; growth insert · [reviewed contract](#b0053) |
| [B0054 · 506–506](../../../../../tests/unit/delta_replay_test.cpp#L506) | Explanatory comments or spacing. |  |
| [B0055 · 507–507](../../../../../tests/unit/delta_replay_test.cpp#L507) | Callable definition: PhysicalPlan dead_child_plan() | calls root_child_plan; returns root_child_plan() · [reviewed contract](#b0055) |
| [B0056 · 508–508](../../../../../tests/unit/delta_replay_test.cpp#L508) | Explanatory comments or spacing. |  |
| [B0057 · 509–537](../../../../../tests/unit/delta_replay_test.cpp#L509) | Callable definition: void dead_changed_keys_are_filtered_before_root_activation() | calls run, dead_child_plan, bootstrap, n; guard check(event.raw.empty() && event.metrics.changed_keys == 1 &&; growth insert; 1 loop sites · [reviewed contract](#b0057) |
| [B0058 · 538–538](../../../../../tests/unit/delta_replay_test.cpp#L538) | Explanatory comments or spacing. |  |
| [B0059 · 539–554](../../../../../tests/unit/delta_replay_test.cpp#L539) | Callable definition: PhysicalPlan sibling_alias_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0059) |
| [B0060 · 555–555](../../../../../tests/unit/delta_replay_test.cpp#L555) | Explanatory comments or spacing. |  |
| [B0061 · 556–561](../../../../../tests/unit/delta_replay_test.cpp#L556) | Callable definition: std::set&lt;SignedKey&gt; stage_records(const Event& event, const DeltaStage& stage) | calls insert, at; returns result; growth insert; 1 loop sites · [reviewed contract](#b0061) |
| [B0062 · 562–562](../../../../../tests/unit/delta_replay_test.cpp#L562) | Explanatory comments or spacing. |  |
| [B0063 · 563–599](../../../../../tests/unit/delta_replay_test.cpp#L563) | Callable definition: void sibling_alias_prefixes_wait_for_their_route() | calls run, sibling_alias_plan, seed, n; guard check(inserted.stages.size() == 2 &&; growth insert · [reviewed contract](#b0063) |
| [B0064 · 600–600](../../../../../tests/unit/delta_replay_test.cpp#L600) | Explanatory comments or spacing. |  |
| [B0065 · 601–619](../../../../../tests/unit/delta_replay_test.cpp#L601) | Callable definition: PhysicalPlan sibling_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0065) |
| [B0066 · 620–620](../../../../../tests/unit/delta_replay_test.cpp#L620) | Explanatory comments or spacing. |  |
| [B0067 · 621–641](../../../../../tests/unit/delta_replay_test.cpp#L621) | Callable definition: void deleting_parent_prunes_queued_child_before_its_turn() | calls run, sibling_plan, seed, n; guard check(a04(run.runtime().plan(), run.database()).size() == 1, · [reviewed contract](#b0067) |
| [B0068 · 642–642](../../../../../tests/unit/delta_replay_test.cpp#L642) | Explanatory comments or spacing. |  |
| [B0069 · 643–657](../../../../../tests/unit/delta_replay_test.cpp#L643) | Callable definition: PhysicalPlan shared_separator_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0069) |
| [B0070 · 658–658](../../../../../tests/unit/delta_replay_test.cpp#L658) | Explanatory comments or spacing. |  |
| [B0071 · 659–691](../../../../../tests/unit/delta_replay_test.cpp#L659) | Callable definition: void shared_parent_separator_keeps_child_until_last_parent() | calls run, shared_separator_plan, seed, n; guard check(first.raw == std::vector&lt;SignedKey&gt;{{SetOperation::erase, · [reviewed contract](#b0071) |
| [B0072 · 692–692](../../../../../tests/unit/delta_replay_test.cpp#L692) | Explanatory comments or spacing. |  |
| [B0073 · 693–706](../../../../../tests/unit/delta_replay_test.cpp#L693) | Callable definition: PhysicalPlan nullary_product_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0073) |
| [B0074 · 707–707](../../../../../tests/unit/delta_replay_test.cpp#L707) | Explanatory comments or spacing. |  |
| [B0075 · 708–746](../../../../../tests/unit/delta_replay_test.cpp#L708) | Callable definition: void nullary_anchor_product_and_rebootstrap() | calls run, nullary_product_plan, seed, n; guard check(a04(run.runtime().plan(), run.database()).empty(),; returns step.node == NodeId{0}; growth insert · [reviewed contract](#b0075) |
| [B0076 · 747–749](../../../../../tests/unit/delta_replay_test.cpp#L747) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0076) |
| [B0077 · 750–771](../../../../../tests/unit/delta_replay_test.cpp#L750) | Callable definition: int main() | calls runtime_profile_names_actual_backend, runtime_profile_reports_effective_strategy_and_limits, runtime_profile_tracks_active_mode_changes, runtime_profile_rejects_incompatible_replay_options; returns 1 · [reviewed contract](#b0077) |

## B0001

[Lines 1–26](../../../../../tests/unit/delta_replay_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L26:sha256:c3d4e1c1e73bb03980ca314379110e28a419cce296c12d92238c3ff65035d26c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_replay_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "evaluator.hpp", "native_input.hpp", "statistics_acceptance.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;initializer_list&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 27–29](../../../../../tests/unit/delta_replay_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a replay fixture predicate. |
| inputs / outputs | Takes condition/message by const reference; returns on true. |
| invariants | Does not catch runtime exceptions. |
| ownership | Message borrowed during call. |
| failure | False throws std::runtime_error. |
| cost | One condition. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0004

[Lines 31–42](../../../../../tests/unit/delta_replay_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw crown::Error with one exact code. |
| inputs / outputs | Takes callable, expected code and label; returns after matching. |
| invariants | Catches only crown::Error; wrong code or no error fails; other exception types propagate. |
| ownership | Callable and string references borrowed during invocation. |
| failure | Expected error mismatch fails. |
| cost | Invokes action once. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0006

[Lines 44–57](../../../../../tests/unit/delta_replay_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_profile_text(const DeltaRuntimeProfile& profile,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require every textual runtime-profile field to be nonempty and readable. |
| inputs / outputs | Takes DeltaRuntimeProfile by const reference and label; returns void. |
| invariants | Checks selected string_views are nonempty and contain no embedded NUL; does not validate truth of every claim. |
| ownership | Profile borrowed; field views have their own profile-defined lifetime. |
| failure | Empty/unreadable field fails. |
| cost | Checks each enumerated profile view. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0008

[Lines 59–59](../../../../../tests/unit/delta_replay_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 fixture Value. |
| inputs / outputs | Takes signed integer; returns Value by value. |
| invariants | Preserves integer. |
| ownership | No external state retained. |
| failure | Variant errors propagate. |
| cost | Scalar conversion. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0010

[Lines 61–65](../../../../../tests/unit/delta_replay_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variables(std::initializer_list<std::size_t> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build VariableSet from zero-based indices. |
| inputs / outputs | Takes initializer list; returns set of VariableId. |
| invariants | Repeated indices collapse. |
| ownership | Returned set owns IDs. |
| failure | Allocation errors propagate. |
| cost | One set insertion per input. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0012

[Lines 67–76](../../../../../tests/unit/delta_replay_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions replay_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure a maintenance-first ordered replay runtime. |
| inputs / outputs | No args; returns DeltaOptions. |
| invariants | Sets mode=maintenance, live maintenance=on_output and completion=ordered_replay; under acceptance macro also sets requested support order. |
| ownership | Options own scalar/configuration values. |
| failure | Invalid combination is checked by runtime construction, not here. |
| cost | Constant-size setup. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0014

[Lines 78–80](../../../../../tests/unit/delta_replay_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04(const auto& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the independent A04 query answer. |
| inputs / outputs | Takes plan/database by const reference; returns Relation. |
| invariants | Uses reference evaluator, independently of runtime-maintained answers. |
| ownership | Inputs borrowed; result owns rows. |
| failure | Evaluation/allocation errors propagate. |
| cost | One finite reference evaluation. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0016

[Lines 82–90](../../../../../tests/unit/delta_replay_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> difference(const Relation& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact set-valued signed difference between A04 answers. |
| inputs / outputs | Takes before/after by const reference; returns set of operation/row keys. |
| invariants | Only after-only inserts and before-only erases appear. |
| ownership | Inputs borrowed; result owns copied rows. |
| failure | Allocation errors propagate. |
| cost | Scans both finite answers. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0018

[Lines 92–107](../../../../../tests/unit/delta_replay_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain_current(SupportRuntime::ResultCursor cursor,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a current result cursor and validate tuple layout and lease release. |
| inputs / outputs | Takes ResultCursor by value, expected layout and label by const reference; returns Relation. |
| invariants | Requires same layout token for cursor and each tuple, unique exported rows, exhausted cursor state and inactive lease. |
| ownership | Cursor value owns its reader/lease handle during drain; exported rows copied to result. |
| failure | Layout/duplicate/lease mismatch fails; cursor errors propagate. |
| cost | Visits every current row. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0020

[Lines 109–134](../../../../../tests/unit/delta_replay_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> a04_live(const auto& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an A04 answer into visible-scope live factors. |
| inputs / outputs | Takes plan/answer by const reference; returns factor vector. |
| invariants | Uses first position for each head variable and projects each enumeration-step scope. |
| ownership | Inputs borrowed; factors own keys. |
| failure | Missing head field/index or allocation error propagates. |
| cost | Visits each answer row per factor. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/incremental_live.md § Maintained state](../../../../incremental_live.md) |

## B0022

[Lines 136–140](../../../../../tests/unit/delta_replay_test.cpp#L136); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Event {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one replay event’s signed records, stages and metrics. |
| inputs / outputs | Aggregate owns vectors and DeltaMetrics by value. |
| invariants | Event data are copied before the epoch leaves apply(). |
| ownership | Owns copied rows/stages/scalars. |
| failure | Plain aggregate. |
| cost | Storage proportional to emitted output and route stages. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0023

[Lines 141–142](../../../../../tests/unit/delta_replay_test.cpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L142:sha256:48c382e99c3751b362f3c0ec347230c8254208d06e990e41bc2ab8c11b9d003f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_replay_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 143–152](../../../../../tests/unit/delta_replay_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one DeltaRuntime configured for ordered replay and its fixture database. |
| inputs / outputs | Takes plan/table count; constructs runtime from replay_options and resizes database tables. |
| invariants | Checks selected completion is ordered_replay; optional acceptance instrumentation is macro-gated. |
| ownership | Owns runtime, mirror database and sequence. |
| failure | Runtime construction/plan errors propagate. |
| cost | Constructs one runtime and table slots. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0026

[Lines 154–165](../../../../../tests/unit/delta_replay_test.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void seed(TableId table, Row row, const std::string& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed one row into runtime and mirror while in maintenance mode. |
| inputs / outputs | Takes table, Row and label; returns void. |
| invariants | Requires matching sequence, empty/inactive epoch and no returned row before inserting unique row in mirror; checks invariants. |
| ownership | Runtime and database own stored values. |
| failure | Unexpected output, duplicate seed or invariant failure fails. |
| cost | One runtime application plus epoch/invariant checks. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0028

[Lines 167–174](../../../../../tests/unit/delta_replay_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void bootstrap(const std::string& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bootstrap live delta state from seeded physical rows. |
| inputs / outputs | Takes label; returns void. |
| invariants | Requires initial maintenance mode, transitions to delta, requires L published and validates current state. |
| ownership | ReplayRun owns runtime/database. |
| failure | Mode/snapshot/A04 mismatch fails. |
| cost | One full mode bootstrap and A04/current checks. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0030

[Lines 176–181](../../../../../tests/unit/delta_replay_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void maintenance(const std::string& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Switch runtime to maintenance and validate current answer without a live snapshot. |
| inputs / outputs | Takes label; returns void. |
| invariants | Drops L snapshot and calls current-state A04 validation; does not rewind sequence. |
| ownership | ReplayRun owns state. |
| failure | Unexpected retained snapshot/current mismatch fails. |
| cost | One mode transition plus current A04 checks. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0032

[Lines 183–272](../../../../../tests/unit/delta_replay_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Event apply(TableId table, SetOperation operation, Row row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a physical set crossing, drain atomic replay output and reconcile route/work metrics. |
| inputs / outputs | Takes table, operation, Row and label; returns owning Event. |
| invariants | Computes A04 before/after difference; requires a real set change; verifies committed sequence, output count/lease, exact unique signed rows, ordinals/layout, drained-ready state, ordered-replay counters and contiguous stage/output intervals; commits mirror DB only after drain and then rechecks current core/output/L/invariants. |
| ownership | Runtime owns engine state; after_database copy is moved into mirror after output drain; returned Event owns copies of rows/stages/metrics. |
| failure | No allocation injection; physical no-op fixture, output, stage, accounting or state mismatch fails. |
| cost | Two A04 answer evaluations plus event preparation, output drain, stage reconciliation and after-state current checks. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/ordered_delta.md § Bounded production and explicit finalization](../../../../ordered_delta.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0034

[Lines 274–274](../../../../../tests/unit/delta_replay_test.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const DeltaRuntime& runtime() const { return runtime_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the DeltaRuntime as const reference. |
| inputs / outputs | No args; returns const DeltaRuntime&. |
| invariants | Read-only facade access. |
| ownership | Borrowed until ReplayRun destruction. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0035

[Lines 275–275](../../../../../tests/unit/delta_replay_test.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const Database& database() const { return database_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose mirrored physical Database as const reference. |
| inputs / outputs | No args; returns const Database&. |
| invariants | Read-only access to committed fixture image. |
| ownership | Borrowed until ReplayRun destruction. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0037

[Lines 277–299](../../../../../tests/unit/delta_replay_test.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 private:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare current answer views and live projections against A04. |
| inputs / outputs | Private method takes label; returns void. |
| invariants | Checks answer truth, drains core and SQL result cursors against A04, validates L sequence/factors in delta mode and calls invariants; optional source counters are macro-gated. |
| ownership | ReplayRun owns runtime/database; cursors local; A04 values local. |
| failure | Any answer/layout/lease/live/invariant mismatch fails. |
| cost | Two cursor drains, A04 materialization and optional acceptance instrumentation. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0038

[Lines 300–305](../../../../../tests/unit/delta_replay_test.cpp#L300); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L300-L305:sha256:98184d37ef4b5b2fcce99b3ac82af8b3eaf588dd12a11bfc78fc4399192f6a84
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_replay_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0039

[Lines 306–318](../../../../../tests/unit/delta_replay_test.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan root_child_plan(PhysicalOptions physical = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the two-factor replay fixture under an explicit admitted backend. |
| inputs / outputs | Optional PhysicalOptions in; checked lowered r(x),s(x,y) plan out. |
| invariants | Query/tree/head remain identical when only backend options change. |
| ownership | Returned immutable plan owns its descriptors; local Catalog/Query/Tree do not escape by reference. |
| failure | Normal compiler/tree/backend admission failures propagate to the test boundary. |
| cost | Cold fixture compilation/allocation, outside measured native transitions. |
| Design | [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0041

[Lines 320–343](../../../../../tests/unit/delta_replay_test.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void runtime_profile_names_actual_backend() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reproduce stale indexed backend provenance and verify the corrected descriptor. |
| inputs / outputs | Reference/indexed plans run maintenance and delta modes; checks compare actual plan backend with profile text. |
| invariants | Both early maintenance and normal delta profile returns must agree with the admitted plan. Detached static text remains readable after facade destruction. |
| ownership | Each runtime is locally scoped; a detached value profile retains only static string_views and scalar metadata. |
| failure | Checks throw at the existing test boundary. The pinned pre-fix executable rejects the indexed profile as expected. |
| cost | Two cold runtime constructions/mode bootstraps with finite indexed limits; no production instrumentation or benchmark claim. |
| Design | [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0043

[Lines 345–403](../../../../../tests/unit/delta_replay_test.cpp#L345); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void runtime_profile_reports_effective_strategy_and_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check effective replay strategy, bounds, publication, view and spool caps across option combinations. |
| inputs / outputs | No args; constructs runtimes/profiles and returns void. |
| invariants | Asserts automatic on_output chooses ordered replay bounded candidate/accepted actions with eager atomic spool and nonconstant public startup; incremental/eager automatic choose anchored with accepted bound unclaimed; root-first bounds unclaimed; customized core view/caps reflected. Internal work-action claims are not CPU/time claims. |
| ownership | Each runtime owns plan/state; profile is copied value. |
| failure | Profile mismatch or runtime construction error fails. |
| cost | Constructs a fixed handful of runtimes and reads profiles. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/ordered_delta.md § Profile, memory and publication](../../../../ordered_delta.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0045

[Lines 405–442](../../../../../tests/unit/delta_replay_test.cpp#L405); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void runtime_profile_tracks_active_mode_changes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check profile fields track maintenance, delta bootstrap, mode exit and rebootstrap. |
| inputs / outputs | No args; constructs one runtime and transitions modes. |
| invariants | Maintenance says no delta output/unclaimed bounds; delta says atomic spool/bounded replay; maintenance removes claims; reentry restores replay strategy. |
| ownership | Local runtime owns state; profiles copied. |
| failure | Transition/profile mismatch fails. |
| cost | One runtime and three mode changes. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/ordered_delta.md § Profile, memory and publication](../../../../ordered_delta.md) |

## B0047

[Lines 444–454](../../../../../tests/unit/delta_replay_test.cpp#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void runtime_profile_rejects_incompatible_replay_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require ordered replay to reject incompatible incremental/eager live-maintenance options. |
| inputs / outputs | No args; runs two invalid constructors. |
| invariants | Expects exact invalid_options Error for each incompatible policy/completion combination. |
| ownership | Each lambda creates temporary runtime. |
| failure | Wrong code or accepted invalid combination fails. |
| cost | Two constructor attempts. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0049

[Lines 456–462](../../../../../tests/unit/delta_replay_test.cpp#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntimeProfile detached_delta_profile() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a profile value from a temporary DeltaRuntime configured with custom spool limits. |
| inputs / outputs | No args; returns DeltaRuntimeProfile by value. |
| invariants | Custom row/byte limits are 23/8192; profile is copied before facade destruction. |
| ownership | Temporary runtime owns plan/state; returned profile owns scalar values and static-lifetime text views. |
| failure | Construction/profile errors propagate. |
| cost | One runtime construction/profile copy. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp) |

## B0051

[Lines 464–472](../../../../../tests/unit/delta_replay_test.cpp#L464); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void runtime_profile_text_outlives_its_facade() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify profile values and textual views remain usable after runtime facade destruction. |
| inputs / outputs | No args; obtains detached profile and returns void. |
| invariants | Checks effective ordered replay, custom limits and all selected text fields. |
| ownership | Detached profile survives temporary facade; text lifetime is asserted by profile API/test, not by storing runtime-owned buffers. |
| failure | Profile field mismatch fails. |
| cost | One detached profile check. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0053

[Lines 474–505](../../../../../tests/unit/delta_replay_test.cpp#L474); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ancestor_child_crossings_have_no_replay_tail() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise ancestor/child input crossings with one ordered replay owner and separate finalization accounting. |
| inputs / outputs | No args; returns void. |
| invariants | A04 confirms initial no answer; child insertion/deletion each emits one signed result despite two changed keys; requires one candidate/accepted and separately nonzero finalization/retained-state counters. |
| ownership | ReplayRun owns runtime/database; Event owns copied output/stages/metrics. |
| failure | Output or named metric mismatch fails; no fault injection. |
| cost | Two seed/bootstrap actions and two checked events. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/ordered_delta.md § Productive queues](../../../../ordered_delta.md), [docs/ordered_delta.md § Bounded production and explicit finalization](../../../../ordered_delta.md) |

## B0055

[Lines 507–507](../../../../../tests/unit/delta_replay_test.cpp#L507); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan dead_child_plan() { return root_child_plan(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the root/child dead-key plan used for queue filtering. |
| inputs / outputs | No args; returns root_child_plan(). |
| invariants | Alias preserves that fixed plan shape. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One plan construction/lowering. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0057

[Lines 509–537](../../../../../tests/unit/delta_replay_test.cpp#L509); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void dead_changed_keys_are_filtered_before_root_activation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check dead changed child keys are filtered before productive root activation. |
| inputs / outputs | No args; applies 48 child inserts under absent root, then inserts root. |
| invariants | Each dead E key changes one key but has no candidate/output and enters no productive queue; later root insertion emits 48 rows with candidate=accepted=48 and queue activity. Counts are fixture-specific. |
| ownership | ReplayRun owns state; event copies own output. |
| failure | A04/output/counter mismatch fails. |
| cost | 48 dead-key events plus one activation and A04 checks. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/ordered_delta.md § Productive queues](../../../../ordered_delta.md) |

## B0059

[Lines 539–554](../../../../../tests/unit/delta_replay_test.cpp#L539); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan sibling_alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a sibling alias join plan over one physical edge table. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Two native occurrences share table 0 and separator y; output head order is x,z,y. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0061

[Lines 556–561](../../../../../tests/unit/delta_replay_test.cpp#L556); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> stage_records(const Event& event, const DeltaStage& stage) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect the signed records assigned to one stage output interval. |
| inputs / outputs | Takes Event and DeltaStage by const reference; returns owning SignedKey set. |
| invariants | Copies records in \[output_begin, output_begin+output_count); \`.at\` detects invalid bounds; duplicate set keys collapse, with separate outer checks verifying expected cardinality. |
| ownership | Event borrowed; result owns copied rows. |
| failure | Out-of-range interval throws; mismatches are caught by caller. |
| cost | Copies each stage-assigned row. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md) |

## B0063

[Lines 563–599](../../../../../tests/unit/delta_replay_test.cpp#L563); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sibling_alias_prefixes_wait_for_their_route() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check sibling alias answers wait for the route that owns their prefix, for insertion and deletion. |
| inputs / outputs | No args; returns void. |
| invariants | Uses exact route stage counts and per-stage signed-row sets for loop insert/delete; confirms current child-L index was read. |
| ownership | ReplayRun owns runtime/database; Events own copied outputs. |
| failure | Prefix/answer/metric mismatch fails. |
| cost | Two seeds, bootstrap and two alias events. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/ordered_delta.md § Fragment cursor and exact ownership](../../../../ordered_delta.md) |

## B0065

[Lines 601–619](../../../../../tests/unit/delta_replay_test.cpp#L601); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan sibling_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a root with two sibling child tables s(x,y), t(x,z). |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Root shares x with both children; fixture tests queued future child pruning. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0067

[Lines 621–641](../../../../../tests/unit/delta_replay_test.cpp#L621); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deleting_parent_prunes_queued_child_before_its_turn() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check ancestor deletion removes a queued future child before duplicate processing. |
| inputs / outputs | No args; seeds one answer then deletes S row. |
| invariants | Exact one answer retraction; two changed keys but one candidate/accepted; queue has one pop and one erase. |
| ownership | ReplayRun owns state; event values copied. |
| failure | Output/queue metric mismatch fails. |
| cost | Three seeds, bootstrap and one event. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/ordered_delta.md § Productive queues](../../../../ordered_delta.md) |

## B0069

[Lines 643–657](../../../../../tests/unit/delta_replay_test.cpp#L643); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shared_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a parent/child plan sharing separator x. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Two parent rows share x and child row is retained until last parent disappears. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0071

[Lines 659–691](../../../../../tests/unit/delta_replay_test.cpp#L659); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void shared_parent_separator_keeps_child_until_last_parent() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check shared child L and index survive first parent deletion and disappear after last-parent crossing. |
| inputs / outputs | No args; seeds two parents and one child, bootstraps and applies two deletions. |
| invariants | First event emits one row erase but no separator crossing/index update; second emits one erase and crosses support to zero with one child index update. |
| ownership | ReplayRun owns runtime/database; snapshots borrowed transiently. |
| failure | Output/L/support metric mismatch fails. |
| cost | Three seeds/bootstrap and two checked events. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/ordered_delta.md § Coupling and deletion completeness](../../../../ordered_delta.md) |

## B0073

[Lines 693–706](../../../../../tests/unit/delta_replay_test.cpp#L693); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_product_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a nullary generalized root over two unary native children. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Root scope is empty and head field order is y,x; root activation/deactivation gates disconnected product. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0075

[Lines 708–746](../../../../../tests/unit/delta_replay_test.cpp#L708); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_anchor_product_and_rebootstrap() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nullary product activation/deactivation and ordered-replay rebootstrap. |
| inputs / outputs | No args; seeds two rows, bootstraps, inserts/deletes second child row, then cycles maintenance/delta. |
| invariants | Exact two insertions and two erasures; verifies Row{} root L key; maintenance drops live snapshot, later bootstrap preserves ordered replay completion. |
| ownership | ReplayRun owns runtime/database; returned Event copies output. |
| failure | A04, output, root L or strategy mismatch fails. |
| cost | Two seeds, two events and one maintenance/rebootstrap cycle. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/ordered_delta.md § Strategies and state](../../../../ordered_delta.md) |

## B0076

[Lines 747–749](../../../../../tests/unit/delta_replay_test.cpp#L747); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L747-L749:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_replay_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_replay_test.cpp](../../../../../tests/unit/delta_replay_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0077

[Lines 750–771](../../../../../tests/unit/delta_replay_test.cpp#L750); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run replay/profile regressions and present one process exit status. |
| inputs / outputs | No CLI input; executes fixture functions, prints success, returns zero or one. |
| invariants | Backend provenance executes before the existing independent replay corpus; original fixtures are retained. |
| ownership | All fixture owners are local; main retains no rows across tests. |
| failure | One existing std::exception presentation catch reports the failing assertion and returns one. |
| cost | Sum of explicit test fixtures and optional acceptance output; no production cost. |
| Design | [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_runtime.md](../../../../delta_runtime.md) |
