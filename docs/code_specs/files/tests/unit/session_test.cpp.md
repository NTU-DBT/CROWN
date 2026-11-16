# `tests/unit/session_test.cpp` — block usage map

[Source](../../../../../tests/unit/session_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f1a02b70bd84a91691e6bf3401495ef271e83bc09a43e2ca9574bedf1b255ede`. 1196 lines partitioned into 94 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–29](../../../../../tests/unit/session_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 30–32](../../../../../tests/unit/session_test.cpp#L30) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 33–33](../../../../../tests/unit/session_test.cpp#L33) | Explanatory comments or spacing. |  |
| [B0004 · 34–45](../../../../../tests/unit/session_test.cpp#L34) | Callable definition: template &lt;class Action&gt; void expect_code(Action&& action, std::string_view code, const std::string& label) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 46–46](../../../../../tests/unit/session_test.cpp#L46) | Explanatory comments or spacing. |  |
| [B0006 · 47–54](../../../../../tests/unit/session_test.cpp#L47) | Callable definition: template &lt;class Action&gt; void run_case(const std::string& label, Action&& action) | calls std::runtime_error, what · [reviewed contract](#b0006) |
| [B0007 · 55–60](../../../../../tests/unit/session_test.cpp#L55) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_copy_constructible_v&lt;QuerySession&gt;); · [reviewed contract](#b0007) |
| [B0008 · 61–61](../../../../../tests/unit/session_test.cpp#L61) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 62–62](../../../../../tests/unit/session_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0010 · 63–71](../../../../../tests/unit/session_test.cpp#L63) | Callable definition: PhysicalPlan unary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0010) |
| [B0011 · 72–72](../../../../../tests/unit/session_test.cpp#L72) | Explanatory comments or spacing. |  |
| [B0012 · 73–90](../../../../../tests/unit/session_test.cpp#L73) | Callable definition: PhysicalPlan self_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0012) |
| [B0013 · 91–91](../../../../../tests/unit/session_test.cpp#L91) | Explanatory comments or spacing. |  |
| [B0014 · 92–107](../../../../../tests/unit/session_test.cpp#L92) | Callable definition: PhysicalPlan projected_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0014) |
| [B0015 · 108–108](../../../../../tests/unit/session_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0016 · 109–135](../../../../../tests/unit/session_test.cpp#L109) | Callable definition: PhysicalPlan deep_chain_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0016) |
| [B0017 · 136–136](../../../../../tests/unit/session_test.cpp#L136) | Explanatory comments or spacing. |  |
| [B0018 · 137–148](../../../../../tests/unit/session_test.cpp#L137) | Callable definition: PhysicalPlan projected_source_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0018) |
| [B0019 · 149–149](../../../../../tests/unit/session_test.cpp#L149) | Explanatory comments or spacing. |  |
| [B0020 · 150–160](../../../../../tests/unit/session_test.cpp#L150) | Callable definition: PhysicalPlan repeated_column_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0020) |
| [B0021 · 161–161](../../../../../tests/unit/session_test.cpp#L161) | Explanatory comments or spacing. |  |
| [B0022 · 162–171](../../../../../tests/unit/session_test.cpp#L162) | Callable definition: PhysicalPlan boolean_column_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0022) |
| [B0023 · 172–172](../../../../../tests/unit/session_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0024 · 173–181](../../../../../tests/unit/session_test.cpp#L173) | Callable definition: PhysicalPlan nullary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0024) |
| [B0025 · 182–182](../../../../../tests/unit/session_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0026 · 183–187](../../../../../tests/unit/session_test.cpp#L183) | Callable definition: PhysicalPlan constant_nullary_plan(bool truth) | calls planner::lower_tree; returns planner::lower_tree(catalog, query, FreeConnexTree{}) · [reviewed contract](#b0026) |
| [B0027 · 188–188](../../../../../tests/unit/session_test.cpp#L188) | Explanatory comments or spacing. |  |
| [B0028 · 189–205](../../../../../tests/unit/session_test.cpp#L189) | Callable definition: PhysicalPlan exists_plan() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0028) |
| [B0029 · 206–206](../../../../../tests/unit/session_test.cpp#L206) | Explanatory comments or spacing. |  |
| [B0030 · 207–211](../../../../../tests/unit/session_test.cpp#L207) | Callable definition: QuerySession::Owner create_session( PhysicalPlan plan, std::string input, SessionOptions options = {}) | calls QuerySession::create, std::move; returns QuerySession::create(std::move(plan),; growth make_unique · [reviewed contract](#b0030) |
| [B0031 · 212–212](../../../../../tests/unit/session_test.cpp#L212) | Explanatory comments or spacing. |  |
| [B0032 · 213–221](../../../../../tests/unit/session_test.cpp#L213) | Callable definition: std::string json_record(const PhysicalPlan& plan, std::uint64_t sequence, TableId table, Row values, SetOperation operation = Set… | calls std::move, io::write_input_json, source_catalog; returns io::write_input_json(event, plan.source_catalog()) + @; growth insert · [reviewed contract](#b0032) |
| [B0033 · 222–222](../../../../../tests/unit/session_test.cpp#L222) | Explanatory comments or spacing. |  |
| [B0034 · 223–227](../../../../../tests/unit/session_test.cpp#L223) | Type/record definition: struct Event | growth insert · [reviewed contract](#b0034) |
| [B0035 · 228–228](../../../../../tests/unit/session_test.cpp#L228) | Explanatory comments or spacing. |  |
| [B0036 · 229–238](../../../../../tests/unit/session_test.cpp#L229) | Callable definition: std::string json_trace(const PhysicalPlan& plan, const std::vector&lt;Event&gt;& events, std::uint64_t first_offset = 100) | calls size, json_record; returns text; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 239–239](../../../../../tests/unit/session_test.cpp#L239) | Explanatory comments or spacing. |  |
| [B0038 · 240–242](../../../../../tests/unit/session_test.cpp#L240) | Callable definition: Relation a04(const PhysicalPlan& plan, const Database& database) | calls reference::evaluate, source_catalog, query; returns reference::evaluate(plan.source_catalog(), plan.query(), database) · [reviewed contract](#b0038) |
| [B0039 · 243–243](../../../../../tests/unit/session_test.cpp#L243) | Explanatory comments or spacing. |  |
| [B0040 · 244–252](../../../../../tests/unit/session_test.cpp#L244) | Callable definition: std::set&lt;SignedKey&gt; signed_difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0040) |
| [B0041 · 253–253](../../../../../tests/unit/session_test.cpp#L253) | Explanatory comments or spacing. |  |
| [B0042 · 254–262](../../../../../tests/unit/session_test.cpp#L254) | Callable definition: Database after_update(const Database& before, const PhysicalSetUpdate& update) | calls at, insert, erase; returns result; growth insert · [reviewed contract](#b0042) |
| [B0043 · 263–263](../../../../../tests/unit/session_test.cpp#L263) | Explanatory comments or spacing. |  |
| [B0044 · 264–275](../../../../../tests/unit/session_test.cpp#L264) | Callable definition: std::set&lt;SignedKey&gt; collect_output(QuerySession& session, const std::string& label) | calls next_output, check, emplace, crown::storage::export_row; guard check(record-&gt;ordinal == ++ordinal,; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 276–276](../../../../../tests/unit/session_test.cpp#L276) | Explanatory comments or spacing. |  |
| [B0046 · 277–284](../../../../../tests/unit/session_test.cpp#L277) | Callable definition: void step_to_prepared(QuerySession& session, const std::string& label) | calls status, step, check; guard check(++calls &lt; 100000,; 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 285–285](../../../../../tests/unit/session_test.cpp#L285) | Explanatory comments or spacing. |  |
| [B0048 · 286–303](../../../../../tests/unit/session_test.cpp#L286) | Callable definition: void check_snapshot_against_a04(QuerySession& session, const PhysicalPlan& plan, const Database& database, std::uint64_t sequence… | calls snapshot, check, layout, same_token; guard check(tuple.layout().same_token(snapshot.layout),; growth insert; 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 304–304](../../../../../tests/unit/session_test.cpp#L304) | Explanatory comments or spacing. |  |
| [B0050 · 305–323](../../../../../tests/unit/session_test.cpp#L305) | Callable definition: void apply_epoch_and_check(QuerySession& session, const PhysicalPlan& plan, Database& database, const PhysicalSetUpdate& update, … | calls a04, after_update, signed_difference, check; guard check(session.begin_next(), label + ": expected another input event"); · [reviewed contract](#b0050) |
| [B0051 · 324–324](../../../../../tests/unit/session_test.cpp#L324) | Explanatory comments or spacing. |  |
| [B0052 · 325–329](../../../../../tests/unit/session_test.cpp#L325) | Type/record definition: struct LifecycleScenario |  · [reviewed contract](#b0052) |
| [B0053 · 330–330](../../../../../tests/unit/session_test.cpp#L330) | Explanatory comments or spacing. |  |
| [B0054 · 331–337](../../../../../tests/unit/session_test.cpp#L331) | Callable definition: LifecycleScenario self_join_scenario() | calls self_join_plan, n; returns {@ , self_join_plan(), · [reviewed contract](#b0054) |
| [B0055 · 338–338](../../../../../tests/unit/session_test.cpp#L338) | Explanatory comments or spacing. |  |
| [B0056 · 339–345](../../../../../tests/unit/session_test.cpp#L339) | Callable definition: LifecycleScenario projected_scenario() | calls projected_join_plan, n; returns {@ , projected_join_plan(), · [reviewed contract](#b0056) |
| [B0057 · 346–346](../../../../../tests/unit/session_test.cpp#L346) | Explanatory comments or spacing. |  |
| [B0058 · 347–355](../../../../../tests/unit/session_test.cpp#L347) | Callable definition: LifecycleScenario deep_chain_scenario() | calls deep_chain_plan, n; returns {@ , deep_chain_plan(), · [reviewed contract](#b0058) |
| [B0059 · 356–356](../../../../../tests/unit/session_test.cpp#L356) | Explanatory comments or spacing. |  |
| [B0060 · 357–434](../../../../../tests/unit/session_test.cpp#L357) | Callable definition: void pause_after_each_core_result(const LifecycleScenario& scenario) | calls json_trace, create_session, std::move, resize; guard check(expected.size() &gt;= 2,; growth resize; 2 loop sites · [reviewed contract](#b0060) |
| [B0061 · 435–435](../../../../../tests/unit/session_test.cpp#L435) | Explanatory comments or spacing. |  |
| [B0062 · 436–546](../../../../../tests/unit/session_test.cpp#L436) | Callable definition: void control_state_and_phase_matrix() | calls unary_plan, resize, source_catalog, size; guard check(initial.state == SessionState::created &&; growth resize; source comment (unverified): // Ready draining is explicitly idempotent, including an empty input. · [reviewed contract](#b0062) |
| [B0063 · 547–547](../../../../../tests/unit/session_test.cpp#L547) | Explanatory comments or spacing. |  |
| [B0064 · 548–650](../../../../../tests/unit/session_test.cpp#L548) | Callable definition: void private_phase_guards_and_draining() | calls unary_plan, n, create_session, json_trace; guard check(session-&gt;begin_next(), "first private-phase input is missing");; growth insert, resize · [reviewed contract](#b0064) |
| [B0065 · 651–651](../../../../../tests/unit/session_test.cpp#L651) | Explanatory comments or spacing. |  |
| [B0066 · 652–725](../../../../../tests/unit/session_test.cpp#L652) | Callable definition: void output_snapshot_and_limits() | calls unary_plan, json_record, n, create_session; guard check(empty.rows.empty() && empty.sequence == 0 && empty.accounted_bytes == 0,; growth insert, resize · [reviewed contract](#b0066) |
| [B0067 · 726–726](../../../../../tests/unit/session_test.cpp#L726) | Explanatory comments or spacing. |  |
| [B0068 · 727–767](../../../../../tests/unit/session_test.cpp#L727) | Callable definition: void drain_committed_output_without_reading_next_input() | calls unary_plan, n, create_session, json_trace; guard check(expected == std::set&lt;SignedKey&gt;{{SetOperation::insert, {n(1)}}},; growth insert, resize · [reviewed contract](#b0068) |
| [B0069 · 768–768](../../../../../tests/unit/session_test.cpp#L768) | Explanatory comments or spacing. |  |
| [B0070 · 769–810](../../../../../tests/unit/session_test.cpp#L769) | Callable definition: void projection_noop_filter_and_source_progress() | calls projected_source_plan, n, create_session, json_trace; guard check(progress.sequence == i + 1 &&; growth insert, resize; 1 loop sites; source comment (unverified): // New physical row, same projected answer. · [reviewed contract](#b0070) |
| [B0071 · 811–811](../../../../../tests/unit/session_test.cpp#L811) | Explanatory comments or spacing. |  |
| [B0072 · 812–835](../../../../../tests/unit/session_test.cpp#L812) | Callable definition: void maintenance_mode_keeps_results_without_delta_output() | calls unary_plan, n, create_session, json_trace; guard check(session-&gt;begin_next(), "maintenance-mode input event is missing");; growth resize; 1 loop sites · [reviewed contract](#b0072) |
| [B0073 · 836–836](../../../../../tests/unit/session_test.cpp#L836) | Explanatory comments or spacing. |  |
| [B0074 · 837–936](../../../../../tests/unit/session_test.cpp#L837) | Callable definition: void scalar_exists_boolean_and_nullary_snapshots() | calls exists_plan, n, create_session, json_trace; guard check(empty.sequence == 0 && empty.rows.size() == 1 &&; growth emplace, insert, resize; 1 loop sites · [reviewed contract](#b0074) |
| [B0075 · 937–937](../../../../../tests/unit/session_test.cpp#L937) | Explanatory comments or spacing. |  |
| [B0076 · 938–945](../../../../../tests/unit/session_test.cpp#L938) | Type/record definition: class TrackingStream final : public std::istringstream |  · [reviewed contract](#b0076) |
| [B0077 · 946–947](../../../../../tests/unit/session_test.cpp#L946) | declares types or opens a type body. |  · [reviewed contract](#b0077) |
| [B0078 · 948–950](../../../../../tests/unit/session_test.cpp#L948) | Callable definition: public: ReentrantBuffer(std::string text, std::function&lt;void()&gt; callback) : text_(std::move(text)), callback_(std::move(callback)) | calls void, text_, std::move, callback_ · [reviewed contract](#b0078) |
| [B0079 · 951–956](../../../../../tests/unit/session_test.cpp#L951) | Callable definition: protected: int_type underflow() override | calls notify, size, traits_type::eof, traits_type::to_int_type; returns traits_type::eof(); traits_type::to_int_type(text_\[position_\]) · [reviewed contract](#b0079) |
| [B0080 · 957–961](../../../../../tests/unit/session_test.cpp#L957) | Callable definition: int_type uflow() override | calls underflow, traits_type::eq_int_type, traits_type::eof; returns next · [reviewed contract](#b0080) |
| [B0081 · 962–970](../../../../../tests/unit/session_test.cpp#L962) | Callable definition: std::streamsize xsgetn(char* destination, std::streamsize count) override | calls notify, size, std::min, std::copy_n; returns 0; static_cast&lt;std::streamsize&gt;(copied) · [reviewed contract](#b0081) |
| [B0082 · 971–977](../../../../../tests/unit/session_test.cpp#L971) | Callable definition: private: void notify() | calls callback_ · [reviewed contract](#b0082) |
| [B0083 · 978–983](../../../../../tests/unit/session_test.cpp#L978) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0083) |
| [B0084 · 984–992](../../../../../tests/unit/session_test.cpp#L984) | Type/record definition: class ReentrantStream final : public std::istream |  · [reviewed contract](#b0084) |
| [B0085 · 993–993](../../../../../tests/unit/session_test.cpp#L993) | Explanatory comments or spacing. |  |
| [B0086 · 994–1084](../../../../../tests/unit/session_test.cpp#L994) | Callable definition: void parser_stickiness_cleanup_and_retry() | calls unary_plan, json_record, n, QuerySession::create; guard check(parser_error && session-&gt;status().input_failed &&; growth insert, make_unique, resize; 1 loop sites · [reviewed contract](#b0086) |
| [B0087 · 1085–1085](../../../../../tests/unit/session_test.cpp#L1085) | Explanatory comments or spacing. |  |
| [B0088 · 1086–1123](../../../../../tests/unit/session_test.cpp#L1086) | Callable definition: void output_stop_and_drop_tombstone() | calls unary_plan, QuerySession::create, json_record, n; guard check(session-&gt;begin_next(), "output-stop fixture has no input");; growth insert, make_unique, resize · [reviewed contract](#b0088) |
| [B0089 · 1124–1124](../../../../../tests/unit/session_test.cpp#L1124) | Explanatory comments or spacing. |  |
| [B0090 · 1125–1161](../../../../../tests/unit/session_test.cpp#L1125) | Callable definition: void creator_thread_and_stream_reentry() | calls unary_plan, create_session, json_record, n; guard check(wrong_thread_code == "session_wrong_thread",; growth make_unique · [reviewed contract](#b0090) |
| [B0091 · 1162–1162](../../../../../tests/unit/session_test.cpp#L1162) | Explanatory comments or spacing. |  |
| [B0092 · 1163–1184](../../../../../tests/unit/session_test.cpp#L1163) | Callable definition: void run() | calls run_case, self_join_scenario, projected_scenario, deep_chain_scenario; 1 loop sites · [reviewed contract](#b0092) |
| [B0093 · 1185–1186](../../../../../tests/unit/session_test.cpp#L1185) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0093) |
| [B0094 · 1187–1196](../../../../../tests/unit/session_test.cpp#L1187) | Callable definition: int main() | calls run, what; returns 1; 0 · [reviewed contract](#b0094) |

## B0001

[Lines 1–29](../../../../../tests/unit/session_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L29:sha256:a36a62ac5fb6fb76203ddbed0674e531e282ab0563aa4058864e6890c48f2e33
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/ingest.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", "evaluator.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;thread&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 30–32](../../../../../tests/unit/session_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one local test assertion with the supplied diagnostic. |
| inputs / outputs | Accepts a predicate and a borrowed message; returns for true and throws std::runtime_error for false. |
| invariants | It translates no CROWN Error and catches no exception. |
| ownership | The arguments are borrowed for the call; it stores no fixture or runtime state. |
| failure | Only a false predicate raises std::runtime_error with the supplied message. |
| cost | One branch; constructing a caller diagnostic may allocate before entry. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0004

[Lines 34–45](../../../../../tests/unit/session_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void expect_code(Action&& action, std::string_view code,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw crown::api::Error with one exact code. |
| inputs / outputs | Forwards the action; returns after matching code, otherwise throws a test std::runtime_error. |
| invariants | Catches only crown::api::Error; other exceptions propagate, and a mismatched code fails through check. |
| ownership | The callable and expected-code view are borrowed; no result is retained. |
| failure | No expected Error or a different error code is reported as test failure. |
| cost | One action invocation and exact error-code comparison. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0006

[Lines 47–54](../../../../../tests/unit/session_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void run_case(const std::string& label, Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one labeled fixture and add its label to any std::exception diagnostic. |
| inputs / outputs | Takes a borrowed label and forwarded action; returns the action result or rethrows a runtime_error. |
| invariants | It catches std::exception only; non-standard exceptions propagate. |
| ownership | The action and label are used during this call; any returned value follows the action return type. |
| failure | An action exception is replaced by runtime_error carrying label and what(); message construction can itself fail. |
| cost | One action call; formatting occurs only on exception. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0007

[Lines 55–60](../../../../../tests/unit/session_test.cpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L60:sha256:2eb4f51096db69b50e1a860f92379c259a8fb929a8afbdd9386f0ca52cc1be4b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_test.cpp: require 4 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 61–61](../../../../../tests/unit/session_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 scalar Value for fixture rows. |
| inputs / outputs | Takes one signed 64-bit integer and returns a Value by value. |
| invariants | The conversion preserves the integer value. |
| ownership | The scalar Value owns no external row or session state. |
| failure | No test-specific error translation is present. |
| cost | Constant scalar construction; no query runtime is invoked. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0010

[Lines 63–71](../../../../../tests/unit/session_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-table unary query plan used for exact input/result lifecycle fixtures. |
| inputs / outputs | No arguments; returns a PhysicalPlan for catalog table unary(x), projecting x. |
| invariants | The lowered source catalog and one native node describe the same unary query. |
| ownership | The returned plan owns its value state; no QuerySession is created here. |
| failure | Planner lowering errors propagate to the test caller. |
| cost | Builds a small in-memory catalog/query/tree and invokes lower_tree once. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0012

[Lines 73–90](../../../../../tests/unit/session_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan self_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a self-join plan whose two aliases share one edge table and join on the middle variable. |
| inputs / outputs | No arguments; returns a PhysicalPlan projecting x,z,y from left and right edge aliases. |
| invariants | Both aliases bind to table 0 with opposite variable positions; the generalized join uses the shared variable. |
| ownership | The returned PhysicalPlan owns its lowered metadata. |
| failure | Planner lowering errors propagate. |
| cost | Creates fixed fixture metadata and performs one lowering; no event is executed. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0014

[Lines 92–107](../../../../../tests/unit/session_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-table join that exposes only column a from r. |
| inputs / outputs | No arguments; returns a plan joining r(a,x) with s(x,z) and projecting a. |
| invariants | The common x variable joins the rows while z is omitted from output. |
| ownership | Returns an owned PhysicalPlan; it creates no live runtime. |
| failure | Planner lowering errors propagate. |
| cost | Fixed small plan-construction cost. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0016

[Lines 109–135](../../../../../tests/unit/session_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan deep_chain_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the four-factor r-s-t-u chain used to exercise deeper private preparation. |
| inputs / outputs | No arguments; returns a plan whose adjacent tables share y, z, and w and whose output is x,y,z,w,q. |
| invariants | Each source occurrence is connected through the declared shared variable; all four relations participate. |
| ownership | Returns an owned PhysicalPlan. |
| failure | Planner lowering errors propagate. |
| cost | Constructs fixed metadata and lowers one finite tree. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0018

[Lines 137–148](../../../../../tests/unit/session_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_source_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a source plan whose physical row includes payload but result projection retains only x. |
| inputs / outputs | No arguments; returns a one-table plan over source(x,payload), projecting x. |
| invariants | The source layout and result layout differ; payload remains an input column but not an output column. |
| ownership | Returns an owned plan and retains no input event. |
| failure | Planner lowering errors propagate. |
| cost | One fixture-plan lowering. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0020

[Lines 150–160](../../../../../tests/unit/session_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan repeated_column_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a plan that maps both physical pair columns to the same logical variable. |
| inputs / outputs | No arguments; returns a one-table plan for pair(first,second) with repeated variable x. |
| invariants | A matching tuple must satisfy the repeated-variable equality induced by the atom. |
| ownership | Returns an owned plan. |
| failure | Planner lowering errors propagate. |
| cost | One fixed lowering operation. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0022

[Lines 162–171](../../../../../tests/unit/session_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan boolean_column_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-column Boolean query fixture. |
| inputs / outputs | No arguments; returns a plan over flags(enabled) projecting the Boolean value. |
| invariants | The output scalar type is Boolean and the fixture has one native occurrence. |
| ownership | Returns an owned plan. |
| failure | Planner lowering errors propagate. |
| cost | One fixed lowering operation. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0024

[Lines 173–181](../../../../../tests/unit/session_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a nullary projection over a nonempty-capable unary relation. |
| inputs / outputs | No arguments; returns a plan with no free variables. |
| invariants | The query result is an empty tuple when the unary atom is satisfied; source updates still form physical epochs. |
| ownership | Returns an owned plan. |
| failure | Planner lowering errors propagate. |
| cost | One fixed lowering operation. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0026

[Lines 183–187](../../../../../tests/unit/session_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan constant_nullary_plan(bool truth) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a constant nullary truth or falsehood fixture. |
| inputs / outputs | Accepts truth and returns an empty-catalog PhysicalPlan whose query negation is the inverse flag. |
| invariants | The resulting epoch-zero relation distinguishes one empty tuple from no rows. |
| ownership | Returns an owned plan; input is a borrowed Boolean. |
| failure | Planner lowering errors propagate. |
| cost | Builds and lowers an empty catalog/tree. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0028

[Lines 189–205](../../../../../tests/unit/session_test.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan exists_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind, normalize, and lower a scalar SQL EXISTS query into a physical plan. |
| inputs / outputs | No arguments; returns a PhysicalPlan for SELECT EXISTS(SELECT NULL FROM r). |
| invariants | Binding or normalization diagnostics are converted to test runtime_error; the plan uses the normalized core atom. |
| ownership | The returned plan owns lowered metadata; intermediate binding/normalized objects are local. |
| failure | A binding/normalization diagnostic becomes runtime_error with its code/message; lowering errors propagate. |
| cost | Runs frontend bind and normalize once, then lowers the finite normalized plan. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0030

[Lines 207–211](../../../../../tests/unit/session_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner create_session(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an in-memory QuerySession with a moved plan, owned string stream, and options. |
| inputs / outputs | Takes plan, input bytes, and optional options by value; returns QuerySession::Owner. |
| invariants | The stream is transferred into QuerySession::create; the factory begins with the API-defined initial state. |
| ownership | Owner retains the session; the session owns its istringstream and runtime after transfer. |
| failure | Factory allocation/validation errors propagate; no retry is performed here. |
| cost | Creates an in-memory stream and initializes the finite session fixture. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0032

[Lines 213–221](../../../../../tests/unit/session_test.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string json_record(const PhysicalPlan& plan, std::uint64_t sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one physical input event as JSONL using the plan source catalog. |
| inputs / outputs | Takes sequence, table, row by value plus operation and optional source position; returns encoded text with a newline. |
| invariants | Uses io::write_input_json and preserves the supplied event fields. |
| ownership | The returned string owns bytes; row/position are moved into the local event. |
| failure | Encoder or allocation errors propagate to the caller. |
| cost | One record serialization; no stream read or session transition. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0034

[Lines 223–227](../../../../../tests/unit/session_test.cpp#L223); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Event {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one fixture update with table, row values, and set operation. |
| inputs / outputs | Aggregate fields are initialized by the fixture; no callable input/output. |
| invariants | The default operation is insert; each instance owns its Row value. |
| ownership | Row storage is value-owned by Event. |
| failure | No custom failure path. |
| cost | Plain test data. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0036

[Lines 229–238](../../../../../tests/unit/session_test.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string json_trace(const PhysicalPlan& plan, const std::vector<Event>& events,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode an ordered vector of fixture events into consecutive JSONL input. |
| inputs / outputs | Takes plan, borrowed event vector, and first source offset; returns owned concatenated bytes. |
| invariants | Sequences are one-based vector order; source is feed and offsets advance by ten from first_offset. |
| ownership | Input events are borrowed; output string owns serialization. |
| failure | Encoder/allocation failures propagate. |
| cost | Linear in event count and encoded byte volume. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0038

[Lines 240–242](../../../../../tests/unit/session_test.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04(const PhysicalPlan& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the query with the independent A04 reference evaluator for a source database. |
| inputs / outputs | Takes borrowed plan and Database; returns Relation by value. |
| invariants | Uses plan source catalog and query, not QuerySession state. |
| ownership | Returned reference relation owns its row set; plan/database remain borrowed. |
| failure | Reference evaluator failures propagate. |
| cost | Work depends on the small fixture database/query; this is an exact answer oracle, not a runtime cost bound. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0040

[Lines 244–252](../../../../../tests/unit/session_test.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> signed_difference(const Relation& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact signed set delta between two relation snapshots. |
| inputs / outputs | Takes before and after Relations by reference; returns a set of (insert/erase, Row). |
| invariants | Only rows newly present become insertions and rows removed become erasures; unchanged rows are omitted. |
| ownership | Input relations are borrowed; result set owns copied row keys. |
| failure | Set/row allocation failures propagate. |
| cost | Scans both finite fixture relations and inserts changed rows into an ordered set. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0042

[Lines 254–262](../../../../../tests/unit/session_test.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database after_update(const Database& before, const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one insert or erase to a copied database for the next A04 oracle state. |
| inputs / outputs | Takes database and update by const reference; returns a modified Database by value. |
| invariants | Set semantics make duplicate insert and absent erase no-ops. |
| ownership | Copies the database; returned tables/rows own their values. |
| failure | Invalid table index or allocation errors propagate through at(). |
| cost | Copies and updates the finite fixture database; cost scales with its table/row contents. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0044

[Lines 264–275](../../../../../tests/unit/session_test.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> collect_output(QuerySession& session,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume all currently retained session output and export it to a unique signed-row set. |
| inputs / outputs | Takes mutable session and borrowed label; returns set of operation/Row keys. |
| invariants | Ordinals must be contiguous from one for this drain, and duplicate signed rows fail the assertion. |
| ownership | Session output is returned as owning SignedResult values; exported Rows in result set are owned copies. |
| failure | Ordinal/duplicate mismatch throws runtime_error; API/output errors propagate. |
| cost | Reads until next_output returns empty and exports each finite fixture row. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0046

[Lines 277–284](../../../../../tests/unit/session_test.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void step_to_prepared(QuerySession& session, const std::string& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Step a pending event until the session reports prepared. |
| inputs / outputs | Takes mutable session and label; returns after phase becomes prepared. |
| invariants | A 100000-call guard bounds the loop count; it does not impose wall-clock time. |
| ownership | Session owns private pending work; helper retains no result. |
| failure | Session errors propagate; guard exhaustion throws runtime_error. |
| cost | At most 100000 calls, usually one per core result; this is not a CPU-time bound. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0048

[Lines 286–303](../../../../../tests/unit/session_test.cpp#L286); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_snapshot_against_a04(QuerySession& session, const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a committed session snapshot and accepted progress with the independent A04 result. |
| inputs / outputs | Takes mutable session, plan/database references, expected sequence and label; returns after assertions. |
| invariants | Every row uses snapshot layout token; snapshot sequence/progress equal expected and session progress; rows are unique and equal A04. |
| ownership | Snapshot owns copied/shareable rows and progress; A04 result and observed set are local owned values. |
| failure | Any mismatch throws runtime_error; snapshot/reference failures propagate. |
| cost | Materializes a bounded test snapshot and scans its rows; no timing assertion. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md) |

## B0050

[Lines 305–323](../../../../../tests/unit/session_test.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_epoch_and_check(QuerySession& session, const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive one physical update through begin, prepared, commit, signed-output comparison, and snapshot oracle. |
| inputs / outputs | Takes mutable session, plan, mutable database, update, and label; returns after state checks. |
| invariants | Pending sequence matches update; output is exact before/after A04 set difference; snapshot after commit equals updated database. |
| ownership | Session owns runtime state; helper owns the copied next database and output set before moving database into caller. |
| failure | API/reference errors propagate; failed assertions throw runtime_error. |
| cost | One full physical fixture epoch plus reference evaluations before and after; no timing bound. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0052

[Lines 325–329](../../../../../tests/unit/session_test.cpp#L325); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LifecycleScenario {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle a label, lowered plan, and physical-event list for lifecycle scenarios. |
| inputs / outputs | Aggregate fields are owned values populated by scenario factories. |
| invariants | Plan and events describe one finite scenario. |
| ownership | Owns the copied label, plan, and event vector. |
| failure | No custom failure behavior. |
| cost | Plain test data; scenario construction is separate. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0054

[Lines 331–337](../../../../../tests/unit/session_test.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LifecycleScenario self_join_scenario() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the self-join lifecycle fixture with its edge events. |
| inputs / outputs | No arguments; returns a LifecycleScenario. |
| invariants | Uses self_join_plan and ordered edge changes. |
| ownership | Returned scenario owns plan and event rows. |
| failure | Plan/vector allocation failures propagate. |
| cost | Finite fixture construction. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0056

[Lines 339–345](../../../../../tests/unit/session_test.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LifecycleScenario projected_scenario() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the projected two-table join lifecycle fixture. |
| inputs / outputs | No arguments; returns a LifecycleScenario. |
| invariants | Uses projected_join_plan and events that exercise projected results. |
| ownership | Returned scenario owns plan and event rows. |
| failure | Plan/vector allocation failures propagate. |
| cost | Finite fixture construction. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0058

[Lines 347–355](../../../../../tests/unit/session_test.cpp#L347); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LifecycleScenario deep_chain_scenario() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the four-factor chain lifecycle fixture. |
| inputs / outputs | No arguments; returns a LifecycleScenario. |
| invariants | Uses deep_chain_plan and events that exercise multiple core results. |
| ownership | Returned scenario owns plan and event rows. |
| failure | Plan/vector allocation failures propagate. |
| cost | Finite fixture construction. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0060

[Lines 357–434](../../../../../tests/unit/session_test.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pause_after_each_core_result(const LifecycleScenario& scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pause each selected scenario after every core result and verify publication stays private until commit. |
| inputs / outputs | Takes one borrowed LifecycleScenario; creates a session for its encoded event stream. |
| invariants | While paused, accepted progress/snapshot/output remain at previous commit; snapshot and begin are rejected in private phases; start resumes; committed signed rows and snapshot match A04; next event is not implicitly admitted. |
| ownership | Local session owns the stream/runtime; scenario is borrowed; oracle database and output values are local. |
| failure | Expected phase errors are matched exactly; unexpected API/reference errors propagate; assertion failures throw runtime_error. |
| cost | Runs every selected event and pauses at each core_result; this is work-step coverage, not a timing bound. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0062

[Lines 436–546](../../../../../tests/unit/session_test.cpp#L436); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void control_state_and_phase_matrix() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the public control-state and private phase transition matrix. |
| inputs / outputs | No arguments; creates several sessions, invokes lifecycle APIs, and returns after exact status/error assertions. |
| invariants | Tests created/running/paused/stopped/dropped states, pending/prepared/output phases, idempotence, and EOF; source progress changes only on commit. |
| ownership | Each local QuerySession::Owner owns its stream/runtime; snapshots/output are local owning values. |
| failure | Expected API error codes are asserted; a mismatch throws runtime_error. |
| cost | Finite transition matrix over a small number of sessions; no background task or time measurement. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0064

[Lines 548–650](../../../../../tests/unit/session_test.cpp#L548); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void private_phase_guards_and_draining() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise phase guards and the boundary between draining the current event and admitting another. |
| inputs / outputs | No arguments; drives events through pending/prepared/output phases with pause and drain calls. |
| invariants | Drain finishes or discards only current event/output; it does not read the next record; accepted progress changes after commit; pause gates admission/steps. |
| ownership | Session owns the input and private token; returned output/snapshot handles are local values. |
| failure | Expected session_pending_epoch/session_paused/output_pending codes are checked; unexpected failures propagate. |
| cost | Finite session transitions and current-event work; no whole-file drain or timing claim. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0066

[Lines 652–725](../../../../../tests/unit/session_test.cpp#L652); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void output_snapshot_and_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check snapshots with committed unread output, configured/per-call row and byte limits, and retained caller values. |
| inputs / outputs | No arguments; creates sessions, commits rows, requests snapshots and output, then returns after assertions. |
| invariants | Snapshot reads committed rows without consuming output; unpublished phases reject; zero and small limits return resource_limit; per-call limits override; prior snapshot/output values survive stop/drop. |
| ownership | SessionSnapshot owns/shared-owns immutable rows/layout/progress; returned SignedResult owns its tuple; references/iterators remain tied to live collection handles. |
| failure | Expected resource_limit/session errors are checked; other failures propagate. |
| cost | Builds bounded fixture snapshots and exports rows; does not measure retained memory or CPU. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md) |

## B0068

[Lines 727–767](../../../../../tests/unit/session_test.cpp#L727); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drain_committed_output_without_reading_next_input() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify drain discards committed output without reading or acknowledging the next input. |
| inputs / outputs | No arguments; commits one event, leaves output unread, drains it, then checks next sequence admission. |
| invariants | Drain releases current output artifact only; the second event remains unread until an explicit begin_next; snapshot retains committed rows. |
| ownership | Session owns stream/runtime; snapshot rows remain caller-owned after output discard. |
| failure | API errors and assertion mismatches propagate as test failure. |
| cost | Processes the current committed output and checks one later event boundary; no file-wide drain. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0070

[Lines 769–810](../../../../../tests/unit/session_test.cpp#L769); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void projection_noop_filter_and_source_progress() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check source progress for projected updates, duplicate inserts, absent erases, filters, and no-op projected changes. |
| inputs / outputs | No arguments; drives a sequence with explicit feed offsets and compares snapshots/output. |
| invariants | Every successful physical event sequence advances on commit even if output is unchanged or filtered; source offsets advance exactly as specified; row answers match A04. |
| ownership | Session owns decoded input/runtime; database oracle and signed sets are local values. |
| failure | Expected outputs and progress mismatch throw runtime_error; API/reference failures propagate. |
| cost | Finite event sequence with before/after A04 evaluation; no timing/resource bound. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0072

[Lines 812–835](../../../../../tests/unit/session_test.cpp#L812); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void maintenance_mode_keeps_results_without_delta_output() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify maintenance mode commits query-result state while suppressing retained delta output. |
| inputs / outputs | No arguments; creates a maintenance-configured session and applies fixture events. |
| invariants | Snapshots still match A04 and accepted progress commits, while next_output returns no retained delta rows. |
| ownership | Session owns runtime; snapshot rows are owned by the returned snapshot. |
| failure | API/reference failures propagate; assertion mismatch throws runtime_error. |
| cost | Finite maintenance fixture; does not imply durable sink delivery. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0074

[Lines 837–936](../../../../../tests/unit/session_test.cpp#L837); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_exists_boolean_and_nullary_snapshots() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check scalar SQL EXISTS, Boolean rows, native nullary truth, constants, and core-view nullary output. |
| inputs / outputs | No arguments; builds separate plans/sessions and verifies epoch-zero and post-update snapshots/output. |
| invariants | SQL EXISTS begins false then signed transition reflects existence; Boolean type is preserved; native nullary result is the empty tuple; constant true/false epoch-zero result differs; core-view EXISTS emits one empty tuple. |
| ownership | Each session owns its runtime; snapshots and signed rows are local values. |
| failure | Binding/normalization/session errors propagate; mismatched scalar/nullary rows throw runtime_error. |
| cost | Finite set of small query/session fixtures and row checks; no aggregate/recovery coverage. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0076

[Lines 938–945](../../../../../tests/unit/session_test.cpp#L938); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TrackingStream final : public std::istringstream {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track destruction of an owned istringstream for cleanup assertions. |
| inputs / outputs | Constructs from moved text and a borrowed bool reference; no return value. |
| invariants | Destructor sets the referenced marker true. |
| ownership | The stream owns its text; the marker reference must outlive the stream. |
| failure | No exception translation; stream destruction follows the standard noexcept contract. |
| cost | Stream fixture construction/destruction only. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0077

[Lines 946–947](../../../../../tests/unit/session_test.cpp#L946); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L946-L947:sha256:f783ece3512221d0d8edf367881cd06dac4c423f8ee97999b9d90a240b750a67
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0078

[Lines 948–950](../../../../../tests/unit/session_test.cpp#L948); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
  ReentrantBuffer(std::string text, std::function<void()> callback)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the custom reentrant stream buffer with owned input text and a callback. |
| inputs / outputs | Takes text and callback by value/move; initializes streambuf fixture state. |
| invariants | Callback is invoked at most once by notify; position begins at zero. |
| ownership | Buffer owns text/callback and keeps only local cursor/flag state. |
| failure | Allocation or callback exceptions propagate through stream operations. |
| cost | Fixture construction; no product stream cost claim. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0079

[Lines 951–956](../../../../../tests/unit/session_test.cpp#L951); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 protected:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the current input character and trigger the one-shot reentry callback. |
| inputs / outputs | No arguments; returns current character or EOF. |
| invariants | Does not advance position; calls notify first. |
| ownership | Reads buffer-owned text; no returned view escapes. |
| failure | Callback exceptions can propagate to istream caller. |
| cost | Constant-time fixture buffer lookup plus callback check. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0080

[Lines 957–961](../../../../../tests/unit/session_test.cpp#L957); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  int_type uflow() override {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and consume one character through underflow. |
| inputs / outputs | No arguments; returns next int_type or EOF. |
| invariants | Advances position only for non-EOF character. |
| ownership | Uses owned text; result is a character value. |
| failure | Callback/stream exceptions propagate. |
| cost | One buffer read and possible cursor increment. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0081

[Lines 962–970](../../../../../tests/unit/session_test.cpp#L962); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::streamsize xsgetn(char* destination, std::streamsize count) override {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy up to count bytes from current buffer position into the caller destination. |
| inputs / outputs | Takes borrowed destination and requested streamsize; returns bytes copied. |
| invariants | Nonpositive count returns zero; position advances by copied bytes only. |
| ownership | Destination is borrowed for the call; backing text remains buffer-owned. |
| failure | Invalid destination behavior follows the streambuf caller contract; callback exceptions propagate. |
| cost | Copies at most available bytes in one bounded fixture operation. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0082

[Lines 971–977](../../../../../tests/unit/session_test.cpp#L971); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 private:
  void notify() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the stored callback once, before the custom stream exposes input. |
| inputs / outputs | No arguments; mutates one-shot flag and returns void. |
| invariants | If already called or callback is empty it does nothing; sets called before invoking callback. |
| ownership | Callback remains owned by the buffer; callback may reenter the owning QuerySession. |
| failure | A callback exception propagates; it is not swallowed here. |
| cost | One Boolean check and optional callback invocation. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0083

[Lines 978–983](../../../../../tests/unit/session_test.cpp#L978); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L978-L983:sha256:3070bb2630d278630bf3abc3536d794a2a1c38082761d83ed5563907e7e12914
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare session_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0084

[Lines 984–992](../../../../../tests/unit/session_test.cpp#L984); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ReentrantStream final : public std::istream {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide an istream backed by ReentrantBuffer for the session reentry guard fixture. |
| inputs / outputs | Constructs from text and callback; no explicit result. |
| invariants | Installs its member buffer with rdbuf after base stream initialization. |
| ownership | The stream object owns buffer, which owns text/callback; session takes stream ownership when passed to factory. |
| failure | Construction allocation errors propagate. |
| cost | Creates one custom input stream; callback is invoked only when buffer read occurs. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0086

[Lines 994–1084](../../../../../tests/unit/session_test.cpp#L994); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void parser_stickiness_cleanup_and_retry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish sticky parser failure, stop-aborted private input, and retryable spool quota failure. |
| inputs / outputs | No arguments; creates three session cases with TrackingStream or quota options. |
| invariants | Malformed second JSON makes input_failed sticky and preserves committed seq1; stop destroys input and aborts private work without acknowledging it; spool resource_limit is not parser failure and cached decoded event can be retried on the same session owner. |
| ownership | Each session owns its TrackingStream/runtime; A04 database and progress checks are local. |
| failure | Parser and quota errors are checked by code/state; assertion mismatch throws runtime_error. |
| cost | Runs finite two-event fixtures and one bounded step loop; no durable journal or sink is enabled. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0088

[Lines 1086–1123](../../../../../tests/unit/session_test.cpp#L1086); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void output_stop_and_drop_tombstone() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check stop discards unread output but retains committed snapshot/progress, while drop leaves only a tombstone. |
| inputs / outputs | No arguments; creates one committed-output session and exercises stop/drop. |
| invariants | Stop releases unread output/input yet preserves committed seq/progress/snapshot; drop preserves status scalars but progress/snapshot reject. |
| ownership | Session owner retains facade; held snapshot/output values own their data according to their API contracts. |
| failure | Exact stopped/dropped error codes are required; assertion mismatch throws runtime_error. |
| cost | Finite control/cleanup transitions; no allocation injection. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0090

[Lines 1125–1161](../../../../../tests/unit/session_test.cpp#L1125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void creator_thread_and_stream_reentry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify creator-thread rejection precedes state access and stream read reentry reports busy. |
| inputs / outputs | No arguments; calls session status from a worker thread and from a custom stream callback. |
| invariants | Wrong thread yields session_wrong_thread; creator-thread nested query during read yields session_busy; outer read can continue. |
| ownership | Worker borrows session only while main retains exclusive fixture lifetime; custom stream callback is owned by stream. |
| failure | Expected errors are captured and asserted; thread creation/join errors propagate. |
| cost | Creates/joins one thread and triggers one input read callback; no timing guarantee. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0092

[Lines 1163–1184](../../../../../tests/unit/session_test.cpp#L1163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the named session lifecycle, snapshot, projection, SQL/nullary, cleanup, and reentry fixtures. |
| inputs / outputs | No arguments; invokes the selected test routines and returns void. |
| invariants | Failure in any subtest propagates to main; this entry point itself does not catch product errors. |
| ownership | Fixture/session ownership is scoped to each called routine. |
| failure | First thrown error terminates the test flow to main’s failure handler. |
| cost | Runs the finite list of fixtures; does not itself impose a runtime benchmark. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |

## B0093

[Lines 1185–1186](../../../../../tests/unit/session_test.cpp#L1185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1185-L1186:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in session_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0094

[Lines 1187–1196](../../../../../tests/unit/session_test.cpp#L1187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute session_test fixtures and emit pass/failure status. |
| inputs / outputs | Receives process arguments implicitly; returns 0 on all checks or 1 on caught std::exception. |
| invariants | Calls run(); prints final success only after it returns; on exception writes what() to stderr. |
| ownership | Process owns streams and all local test state until exit. |
| failure | Catches std::exception, prints diagnostic, and returns failure; non-standard exceptions are not caught. |
| cost | Runs all fixtures once; no execution is claimed by this source review. |
| Design | [tests/unit/session_test.cpp](../../../../../tests/unit/session_test.cpp) |
