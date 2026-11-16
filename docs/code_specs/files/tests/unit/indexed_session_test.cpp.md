# `tests/unit/indexed_session_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_session_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `eb678eb01a3ae0bac6bc70a169a856e07e70ab2b5fbcc91f2d6722e3e334be38`. 1197 lines partitioned into 94 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../tests/unit/indexed_session_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 31–33](../../../../../tests/unit/indexed_session_test.cpp#L31) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 34–34](../../../../../tests/unit/indexed_session_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0004 · 35–46](../../../../../tests/unit/indexed_session_test.cpp#L35) | Callable definition: template &lt;class Action&gt; void expect_code(Action&& action, std::string_view code, const std::string& label) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 47–47](../../../../../tests/unit/indexed_session_test.cpp#L47) | Explanatory comments or spacing. |  |
| [B0006 · 48–55](../../../../../tests/unit/indexed_session_test.cpp#L48) | Callable definition: template &lt;class Action&gt; void run_case(const std::string& label, Action&& action) | calls std::runtime_error, what · [reviewed contract](#b0006) |
| [B0007 · 56–61](../../../../../tests/unit/indexed_session_test.cpp#L56) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_copy_constructible_v&lt;QuerySession&gt;); · [reviewed contract](#b0007) |
| [B0008 · 62–62](../../../../../tests/unit/indexed_session_test.cpp#L62) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 63–63](../../../../../tests/unit/indexed_session_test.cpp#L63) | Explanatory comments or spacing. |  |
| [B0010 · 64–72](../../../../../tests/unit/indexed_session_test.cpp#L64) | Callable definition: PhysicalPlan unary_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0010) |
| [B0011 · 73–73](../../../../../tests/unit/indexed_session_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0012 · 74–91](../../../../../tests/unit/indexed_session_test.cpp#L74) | Callable definition: PhysicalPlan self_join_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0012) |
| [B0013 · 92–92](../../../../../tests/unit/indexed_session_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0014 · 93–108](../../../../../tests/unit/indexed_session_test.cpp#L93) | Callable definition: PhysicalPlan projected_join_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0014) |
| [B0015 · 109–109](../../../../../tests/unit/indexed_session_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0016 · 110–136](../../../../../tests/unit/indexed_session_test.cpp#L110) | Callable definition: PhysicalPlan deep_chain_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0016) |
| [B0017 · 137–137](../../../../../tests/unit/indexed_session_test.cpp#L137) | Explanatory comments or spacing. |  |
| [B0018 · 138–149](../../../../../tests/unit/indexed_session_test.cpp#L138) | Callable definition: PhysicalPlan projected_source_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0018) |
| [B0019 · 150–150](../../../../../tests/unit/indexed_session_test.cpp#L150) | Explanatory comments or spacing. |  |
| [B0020 · 151–161](../../../../../tests/unit/indexed_session_test.cpp#L151) | Callable definition: PhysicalPlan repeated_column_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0020) |
| [B0021 · 162–162](../../../../../tests/unit/indexed_session_test.cpp#L162) | Explanatory comments or spacing. |  |
| [B0022 · 163–172](../../../../../tests/unit/indexed_session_test.cpp#L163) | Callable definition: PhysicalPlan boolean_column_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0022) |
| [B0023 · 173–173](../../../../../tests/unit/indexed_session_test.cpp#L173) | Explanatory comments or spacing. |  |
| [B0024 · 174–182](../../../../../tests/unit/indexed_session_test.cpp#L174) | Callable definition: PhysicalPlan nullary_plan() | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0024) |
| [B0025 · 183–183](../../../../../tests/unit/indexed_session_test.cpp#L183) | Explanatory comments or spacing. |  |
| [B0026 · 184–188](../../../../../tests/unit/indexed_session_test.cpp#L184) | Callable definition: PhysicalPlan constant_nullary_plan(bool truth) | calls s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, FreeConnexTree{}) · [reviewed contract](#b0026) |
| [B0027 · 189–189](../../../../../tests/unit/indexed_session_test.cpp#L189) | Explanatory comments or spacing. |  |
| [B0028 · 190–206](../../../../../tests/unit/indexed_session_test.cpp#L190) | Callable definition: PhysicalPlan exists_plan() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns s04_runtime::lower_normalized(program, tree) · [reviewed contract](#b0028) |
| [B0029 · 207–207](../../../../../tests/unit/indexed_session_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0030 · 208–212](../../../../../tests/unit/indexed_session_test.cpp#L208) | Callable definition: QuerySession::Owner create_session( PhysicalPlan plan, std::string input, SessionOptions options = {}) | calls QuerySession::create, std::move; returns QuerySession::create(std::move(plan),; growth make_unique · [reviewed contract](#b0030) |
| [B0031 · 213–213](../../../../../tests/unit/indexed_session_test.cpp#L213) | Explanatory comments or spacing. |  |
| [B0032 · 214–222](../../../../../tests/unit/indexed_session_test.cpp#L214) | Callable definition: std::string json_record(const PhysicalPlan& plan, std::uint64_t sequence, TableId table, Row values, SetOperation operation = Set… | calls std::move, io::write_input_json, source_catalog; returns io::write_input_json(event, plan.source_catalog()) + @; growth insert · [reviewed contract](#b0032) |
| [B0033 · 223–223](../../../../../tests/unit/indexed_session_test.cpp#L223) | Explanatory comments or spacing. |  |
| [B0034 · 224–228](../../../../../tests/unit/indexed_session_test.cpp#L224) | Type/record definition: struct Event | growth insert · [reviewed contract](#b0034) |
| [B0035 · 229–229](../../../../../tests/unit/indexed_session_test.cpp#L229) | Explanatory comments or spacing. |  |
| [B0036 · 230–239](../../../../../tests/unit/indexed_session_test.cpp#L230) | Callable definition: std::string json_trace(const PhysicalPlan& plan, const std::vector&lt;Event&gt;& events, std::uint64_t first_offset = 100) | calls size, json_record; returns text; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 240–240](../../../../../tests/unit/indexed_session_test.cpp#L240) | Explanatory comments or spacing. |  |
| [B0038 · 241–243](../../../../../tests/unit/indexed_session_test.cpp#L241) | Callable definition: Relation a04(const PhysicalPlan& plan, const Database& database) | calls reference::evaluate, source_catalog, query; returns reference::evaluate(plan.source_catalog(), plan.query(), database) · [reviewed contract](#b0038) |
| [B0039 · 244–244](../../../../../tests/unit/indexed_session_test.cpp#L244) | Explanatory comments or spacing. |  |
| [B0040 · 245–253](../../../../../tests/unit/indexed_session_test.cpp#L245) | Callable definition: std::set&lt;SignedKey&gt; signed_difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0040) |
| [B0041 · 254–254](../../../../../tests/unit/indexed_session_test.cpp#L254) | Explanatory comments or spacing. |  |
| [B0042 · 255–263](../../../../../tests/unit/indexed_session_test.cpp#L255) | Callable definition: Database after_update(const Database& before, const PhysicalSetUpdate& update) | calls at, insert, erase; returns result; growth insert · [reviewed contract](#b0042) |
| [B0043 · 264–264](../../../../../tests/unit/indexed_session_test.cpp#L264) | Explanatory comments or spacing. |  |
| [B0044 · 265–276](../../../../../tests/unit/indexed_session_test.cpp#L265) | Callable definition: std::set&lt;SignedKey&gt; collect_output(QuerySession& session, const std::string& label) | calls next_output, check, emplace, crown::storage::export_row; guard check(record-&gt;ordinal == ++ordinal,; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 277–277](../../../../../tests/unit/indexed_session_test.cpp#L277) | Explanatory comments or spacing. |  |
| [B0046 · 278–285](../../../../../tests/unit/indexed_session_test.cpp#L278) | Callable definition: void step_to_prepared(QuerySession& session, const std::string& label) | calls status, step, check; guard check(++calls &lt; 100000,; 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 286–286](../../../../../tests/unit/indexed_session_test.cpp#L286) | Explanatory comments or spacing. |  |
| [B0048 · 287–304](../../../../../tests/unit/indexed_session_test.cpp#L287) | Callable definition: void check_snapshot_against_a04(QuerySession& session, const PhysicalPlan& plan, const Database& database, std::uint64_t sequence… | calls snapshot, check, layout, same_token; guard check(tuple.layout().same_token(snapshot.layout),; growth insert; 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 305–305](../../../../../tests/unit/indexed_session_test.cpp#L305) | Explanatory comments or spacing. |  |
| [B0050 · 306–324](../../../../../tests/unit/indexed_session_test.cpp#L306) | Callable definition: void apply_epoch_and_check(QuerySession& session, const PhysicalPlan& plan, Database& database, const PhysicalSetUpdate& update, … | calls a04, after_update, signed_difference, check; guard check(session.begin_next(), label + ": expected another input event"); · [reviewed contract](#b0050) |
| [B0051 · 325–325](../../../../../tests/unit/indexed_session_test.cpp#L325) | Explanatory comments or spacing. |  |
| [B0052 · 326–330](../../../../../tests/unit/indexed_session_test.cpp#L326) | Type/record definition: struct LifecycleScenario |  · [reviewed contract](#b0052) |
| [B0053 · 331–331](../../../../../tests/unit/indexed_session_test.cpp#L331) | Explanatory comments or spacing. |  |
| [B0054 · 332–338](../../../../../tests/unit/indexed_session_test.cpp#L332) | Callable definition: LifecycleScenario self_join_scenario() | calls self_join_plan, n; returns {@ , self_join_plan(), · [reviewed contract](#b0054) |
| [B0055 · 339–339](../../../../../tests/unit/indexed_session_test.cpp#L339) | Explanatory comments or spacing. |  |
| [B0056 · 340–346](../../../../../tests/unit/indexed_session_test.cpp#L340) | Callable definition: LifecycleScenario projected_scenario() | calls projected_join_plan, n; returns {@ , projected_join_plan(), · [reviewed contract](#b0056) |
| [B0057 · 347–347](../../../../../tests/unit/indexed_session_test.cpp#L347) | Explanatory comments or spacing. |  |
| [B0058 · 348–356](../../../../../tests/unit/indexed_session_test.cpp#L348) | Callable definition: LifecycleScenario deep_chain_scenario() | calls deep_chain_plan, n; returns {@ , deep_chain_plan(), · [reviewed contract](#b0058) |
| [B0059 · 357–357](../../../../../tests/unit/indexed_session_test.cpp#L357) | Explanatory comments or spacing. |  |
| [B0060 · 358–435](../../../../../tests/unit/indexed_session_test.cpp#L358) | Callable definition: void pause_after_each_core_result(const LifecycleScenario& scenario) | calls json_trace, create_session, std::move, resize; guard check(expected.size() &gt;= 2,; growth resize; 2 loop sites · [reviewed contract](#b0060) |
| [B0061 · 436–436](../../../../../tests/unit/indexed_session_test.cpp#L436) | Explanatory comments or spacing. |  |
| [B0062 · 437–547](../../../../../tests/unit/indexed_session_test.cpp#L437) | Callable definition: void control_state_and_phase_matrix() | calls unary_plan, resize, source_catalog, size; guard check(initial.state == SessionState::created &&; growth resize; source comment (unverified): // Ready draining is explicitly idempotent, including an empty input. · [reviewed contract](#b0062) |
| [B0063 · 548–548](../../../../../tests/unit/indexed_session_test.cpp#L548) | Explanatory comments or spacing. |  |
| [B0064 · 549–651](../../../../../tests/unit/indexed_session_test.cpp#L549) | Callable definition: void private_phase_guards_and_draining() | calls unary_plan, n, create_session, json_trace; guard check(session-&gt;begin_next(), "first private-phase input is missing");; growth insert, resize · [reviewed contract](#b0064) |
| [B0065 · 652–652](../../../../../tests/unit/indexed_session_test.cpp#L652) | Explanatory comments or spacing. |  |
| [B0066 · 653–726](../../../../../tests/unit/indexed_session_test.cpp#L653) | Callable definition: void output_snapshot_and_limits() | calls unary_plan, json_record, n, create_session; guard check(empty.rows.empty() && empty.sequence == 0 && empty.accounted_bytes == 0,; growth insert, resize · [reviewed contract](#b0066) |
| [B0067 · 727–727](../../../../../tests/unit/indexed_session_test.cpp#L727) | Explanatory comments or spacing. |  |
| [B0068 · 728–768](../../../../../tests/unit/indexed_session_test.cpp#L728) | Callable definition: void drain_committed_output_without_reading_next_input() | calls unary_plan, n, create_session, json_trace; guard check(expected == std::set&lt;SignedKey&gt;{{SetOperation::insert, {n(1)}}},; growth insert, resize · [reviewed contract](#b0068) |
| [B0069 · 769–769](../../../../../tests/unit/indexed_session_test.cpp#L769) | Explanatory comments or spacing. |  |
| [B0070 · 770–811](../../../../../tests/unit/indexed_session_test.cpp#L770) | Callable definition: void projection_noop_filter_and_source_progress() | calls projected_source_plan, n, create_session, json_trace; guard check(progress.sequence == i + 1 &&; growth insert, resize; 1 loop sites; source comment (unverified): // New physical row, same projected answer. · [reviewed contract](#b0070) |
| [B0071 · 812–812](../../../../../tests/unit/indexed_session_test.cpp#L812) | Explanatory comments or spacing. |  |
| [B0072 · 813–836](../../../../../tests/unit/indexed_session_test.cpp#L813) | Callable definition: void maintenance_mode_keeps_results_without_delta_output() | calls unary_plan, n, create_session, json_trace; guard check(session-&gt;begin_next(), "maintenance-mode input event is missing");; growth resize; 1 loop sites · [reviewed contract](#b0072) |
| [B0073 · 837–837](../../../../../tests/unit/indexed_session_test.cpp#L837) | Explanatory comments or spacing. |  |
| [B0074 · 838–937](../../../../../tests/unit/indexed_session_test.cpp#L838) | Callable definition: void scalar_exists_boolean_and_nullary_snapshots() | calls exists_plan, n, create_session, json_trace; guard check(empty.sequence == 0 && empty.rows.size() == 1 &&; growth emplace, insert, resize; 1 loop sites · [reviewed contract](#b0074) |
| [B0075 · 938–938](../../../../../tests/unit/indexed_session_test.cpp#L938) | Explanatory comments or spacing. |  |
| [B0076 · 939–946](../../../../../tests/unit/indexed_session_test.cpp#L939) | Type/record definition: class TrackingStream final : public std::istringstream |  · [reviewed contract](#b0076) |
| [B0077 · 947–948](../../../../../tests/unit/indexed_session_test.cpp#L947) | declares types or opens a type body. |  · [reviewed contract](#b0077) |
| [B0078 · 949–951](../../../../../tests/unit/indexed_session_test.cpp#L949) | Callable definition: public: ReentrantBuffer(std::string text, std::function&lt;void()&gt; callback) : text_(std::move(text)), callback_(std::move(callback)) | calls void, text_, std::move, callback_ · [reviewed contract](#b0078) |
| [B0079 · 952–957](../../../../../tests/unit/indexed_session_test.cpp#L952) | Callable definition: protected: int_type underflow() override | calls notify, size, traits_type::eof, traits_type::to_int_type; returns traits_type::eof(); traits_type::to_int_type(text_\[position_\]) · [reviewed contract](#b0079) |
| [B0080 · 958–962](../../../../../tests/unit/indexed_session_test.cpp#L958) | Callable definition: int_type uflow() override | calls underflow, traits_type::eq_int_type, traits_type::eof; returns next · [reviewed contract](#b0080) |
| [B0081 · 963–971](../../../../../tests/unit/indexed_session_test.cpp#L963) | Callable definition: std::streamsize xsgetn(char* destination, std::streamsize count) override | calls notify, size, std::min, std::copy_n; returns 0; static_cast&lt;std::streamsize&gt;(copied) · [reviewed contract](#b0081) |
| [B0082 · 972–978](../../../../../tests/unit/indexed_session_test.cpp#L972) | Callable definition: private: void notify() | calls callback_ · [reviewed contract](#b0082) |
| [B0083 · 979–984](../../../../../tests/unit/indexed_session_test.cpp#L979) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0083) |
| [B0084 · 985–993](../../../../../tests/unit/indexed_session_test.cpp#L985) | Type/record definition: class ReentrantStream final : public std::istream |  · [reviewed contract](#b0084) |
| [B0085 · 994–994](../../../../../tests/unit/indexed_session_test.cpp#L994) | Explanatory comments or spacing. |  |
| [B0086 · 995–1085](../../../../../tests/unit/indexed_session_test.cpp#L995) | Callable definition: void parser_stickiness_cleanup_and_retry() | calls unary_plan, json_record, n, QuerySession::create; guard check(parser_error && session-&gt;status().input_failed &&; growth insert, make_unique, resize; 1 loop sites · [reviewed contract](#b0086) |
| [B0087 · 1086–1086](../../../../../tests/unit/indexed_session_test.cpp#L1086) | Explanatory comments or spacing. |  |
| [B0088 · 1087–1124](../../../../../tests/unit/indexed_session_test.cpp#L1087) | Callable definition: void output_stop_and_drop_tombstone() | calls unary_plan, QuerySession::create, json_record, n; guard check(session-&gt;begin_next(), "output-stop fixture has no input");; growth insert, make_unique, resize · [reviewed contract](#b0088) |
| [B0089 · 1125–1125](../../../../../tests/unit/indexed_session_test.cpp#L1125) | Explanatory comments or spacing. |  |
| [B0090 · 1126–1162](../../../../../tests/unit/indexed_session_test.cpp#L1126) | Callable definition: void creator_thread_and_stream_reentry() | calls unary_plan, create_session, json_record, n; guard check(wrong_thread_code == "session_wrong_thread",; growth make_unique · [reviewed contract](#b0090) |
| [B0091 · 1163–1163](../../../../../tests/unit/indexed_session_test.cpp#L1163) | Explanatory comments or spacing. |  |
| [B0092 · 1164–1185](../../../../../tests/unit/indexed_session_test.cpp#L1164) | Callable definition: void run() | calls run_case, self_join_scenario, projected_scenario, deep_chain_scenario; 1 loop sites · [reviewed contract](#b0092) |
| [B0093 · 1186–1187](../../../../../tests/unit/indexed_session_test.cpp#L1186) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0093) |
| [B0094 · 1188–1197](../../../../../tests/unit/indexed_session_test.cpp#L1188) | Callable definition: int main() | calls run, what; returns 1; 0 · [reviewed contract](#b0094) |

## B0001

[Lines 1–30](../../../../../tests/unit/indexed_session_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L30:sha256:6f2a80ece1ac5e21d036badff9074636e44adc6e8e2009201c629df8077f8fbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_session_test.cpp: include "indexed_runtime_fixture.hpp", "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/ingest.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", "evaluator.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;thread&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 31–33](../../../../../tests/unit/indexed_session_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0004

[Lines 35–46](../../../../../tests/unit/indexed_session_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0006

[Lines 48–55](../../../../../tests/unit/indexed_session_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0007

[Lines 56–61](../../../../../tests/unit/indexed_session_test.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L61:sha256:2eb4f51096db69b50e1a860f92379c259a8fb929a8afbdd9386f0ca52cc1be4b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_session_test.cpp: require 4 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 62–62](../../../../../tests/unit/indexed_session_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0010

[Lines 64–72](../../../../../tests/unit/indexed_session_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the one-table unary query used for basic event, phase and result fixtures. |
| inputs / outputs | No arguments; returns a PhysicalPlan for unary(x) with x projected. |
| invariants | The catalog, query atom and native tree all name the same one-column source. |
| ownership | The returned plan owns its lowered metadata; no session or input stream is created. |
| failure | Planner validation/lowering failures propagate to the test caller. |
| cost | Builds fixed metadata and lowers one small tree; no event is processed. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0012

[Lines 74–91](../../../../../tests/unit/indexed_session_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan self_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a self-join over one physical edge table for joined-result lifecycle cases. |
| inputs / outputs | No arguments; returns the x,z,y plan with left edge(x,z) and right edge(z,y). |
| invariants | Both aliases reference source table 0, share z, and project all three variables. |
| ownership | Returns a value-owned PhysicalPlan; runtime rows belong to later QuerySession calls. |
| failure | Planner validation/lowering failures propagate. |
| cost | Fixed small catalog/query/tree construction and one lower_tree call. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0014

[Lines 93–108](../../../../../tests/unit/indexed_session_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-table join whose public answer projects only r.a. |
| inputs / outputs | No arguments; returns a plan for r(a,x) joined with s(x,z), projecting a. |
| invariants | The repeated x variable is the join key and z is intentionally not in the head. |
| ownership | The returned plan owns lowered state; it retains no session or event. |
| failure | Planner validation/lowering failures propagate. |
| cost | One finite in-memory plan lowering. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0016

[Lines 110–136](../../../../../tests/unit/indexed_session_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan deep_chain_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the four-factor chain used to pause after multiple core-result prefixes. |
| inputs / outputs | No arguments; returns r(x,y)-s(y,z)-t(z,w)-u(w,q), projecting x,y,z,w,q. |
| invariants | Each neighboring pair shares exactly its declared chain variable; every factor has one source table. |
| ownership | Returns an owned PhysicalPlan; event and epoch state are created by callers. |
| failure | Lowering failures propagate; no fixture-specific recovery is attempted. |
| cost | Constructs four fixed atoms and one finite tree. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0018

[Lines 138–149](../../../../../tests/unit/indexed_session_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_source_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-table source fixture with a retained physical payload column omitted from the answer. |
| inputs / outputs | No arguments; source has x and payload, while the query projects x only. |
| invariants | Input remains a complete physical row even though result tuples contain only x. |
| ownership | Returns a value-owned plan; it does not own a source row. |
| failure | Planner validation/lowering errors propagate. |
| cost | One small plan construction and lowering. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0020

[Lines 151–161](../../../../../tests/unit/indexed_session_test.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan repeated_column_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a repeated-variable atom used to check answer filtering against both physical columns. |
| inputs / outputs | No arguments; returns pair(first,second) with both positions bound to variable x. |
| invariants | Rows whose two source values disagree cannot satisfy the repeated-variable atom. |
| ownership | Returns a value-owned plan; input row ownership belongs to the session/runtime. |
| failure | Planner validation/lowering errors propagate. |
| cost | One fixed plan construction and lowering. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0022

[Lines 163–172](../../../../../tests/unit/indexed_session_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan boolean_column_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a native Boolean-column query for snapshot type and value checks. |
| inputs / outputs | No arguments; returns a flags(enabled) plan projecting one Boolean field. |
| invariants | The query result type remains Boolean rather than an integer encoding. |
| ownership | Returns an owned PhysicalPlan and retains no result tuple. |
| failure | Planner validation/lowering errors propagate. |
| cost | One fixed plan construction and lowering. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0024

[Lines 174–182](../../../../../tests/unit/indexed_session_test.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a nonconstant nullary projection over a unary source relation. |
| inputs / outputs | No arguments; returns a query with an empty head and one source atom. |
| invariants | The answer, when present, is the empty tuple; physical events still advance sequence. |
| ownership | Returns an owned plan; it does not retain database rows. |
| failure | Planner validation/lowering errors propagate. |
| cost | One fixed plan construction and lowering. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0026

[Lines 184–188](../../../../../tests/unit/indexed_session_test.cpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan constant_nullary_plan(bool truth) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a constant nullary true or false query without source tables. |
| inputs / outputs | Takes truth and returns an empty-catalog plan whose negation flag is its inverse. |
| invariants | The epoch-zero answer distinguishes a singleton empty tuple from an empty relation. |
| ownership | The returned plan owns its metadata; the Boolean argument is copied. |
| failure | Planner validation/lowering failures propagate. |
| cost | Creates and lowers an empty catalog/tree. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0028

[Lines 190–206](../../../../../tests/unit/indexed_session_test.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan exists_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind, normalize and lower a scalar SQL EXISTS fixture over r. |
| inputs / outputs | No arguments; returns a plan derived from SELECT EXISTS(SELECT NULL FROM r). |
| invariants | Binding and normalization diagnostics become test runtime_error; the normalized core atom is lowered. |
| ownership | The result plan owns its lowered state; binding/normalization temporaries are local. |
| failure | Binding or normalization diagnostic is surfaced with its code/message; lowering errors propagate. |
| cost | Runs bind, normalize and one lowering pass for a fixed query. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0030

[Lines 208–212](../../../../../tests/unit/indexed_session_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0032

[Lines 214–222](../../../../../tests/unit/indexed_session_test.cpp#L214); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0034

[Lines 224–228](../../../../../tests/unit/indexed_session_test.cpp#L224); `type`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0036

[Lines 230–239](../../../../../tests/unit/indexed_session_test.cpp#L230); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0038

[Lines 241–243](../../../../../tests/unit/indexed_session_test.cpp#L241); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0040

[Lines 245–253](../../../../../tests/unit/indexed_session_test.cpp#L245); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0042

[Lines 255–263](../../../../../tests/unit/indexed_session_test.cpp#L255); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0044

[Lines 265–276](../../../../../tests/unit/indexed_session_test.cpp#L265); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0046

[Lines 278–285](../../../../../tests/unit/indexed_session_test.cpp#L278); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0048

[Lines 287–304](../../../../../tests/unit/indexed_session_test.cpp#L287); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md) |

## B0050

[Lines 306–324](../../../../../tests/unit/indexed_session_test.cpp#L306); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0052

[Lines 326–330](../../../../../tests/unit/indexed_session_test.cpp#L326); `type`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0054

[Lines 332–338](../../../../../tests/unit/indexed_session_test.cpp#L332); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0056

[Lines 340–346](../../../../../tests/unit/indexed_session_test.cpp#L340); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0058

[Lines 348–356](../../../../../tests/unit/indexed_session_test.cpp#L348); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0060

[Lines 358–435](../../../../../tests/unit/indexed_session_test.cpp#L358); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0062

[Lines 437–547](../../../../../tests/unit/indexed_session_test.cpp#L437); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0064

[Lines 549–651](../../../../../tests/unit/indexed_session_test.cpp#L549); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md) |

## B0066

[Lines 653–726](../../../../../tests/unit/indexed_session_test.cpp#L653); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md) |

## B0068

[Lines 728–768](../../../../../tests/unit/indexed_session_test.cpp#L728); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0070

[Lines 770–811](../../../../../tests/unit/indexed_session_test.cpp#L770); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp) |

## B0072

[Lines 813–836](../../../../../tests/unit/indexed_session_test.cpp#L813); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0074

[Lines 838–937](../../../../../tests/unit/indexed_session_test.cpp#L838); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0076

[Lines 939–946](../../../../../tests/unit/indexed_session_test.cpp#L939); `type`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0077

[Lines 947–948](../../../../../tests/unit/indexed_session_test.cpp#L947); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L947-L948:sha256:f783ece3512221d0d8edf367881cd06dac4c423f8ee97999b9d90a240b750a67
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_session_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0078

[Lines 949–951](../../../../../tests/unit/indexed_session_test.cpp#L949); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0079

[Lines 952–957](../../../../../tests/unit/indexed_session_test.cpp#L952); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0080

[Lines 958–962](../../../../../tests/unit/indexed_session_test.cpp#L958); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0081

[Lines 963–971](../../../../../tests/unit/indexed_session_test.cpp#L963); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0082

[Lines 972–978](../../../../../tests/unit/indexed_session_test.cpp#L972); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0083

[Lines 979–984](../../../../../tests/unit/indexed_session_test.cpp#L979); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L979-L984:sha256:3070bb2630d278630bf3abc3536d794a2a1c38082761d83ed5563907e7e12914
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_session_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0084

[Lines 985–993](../../../../../tests/unit/indexed_session_test.cpp#L985); `type`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0086

[Lines 995–1085](../../../../../tests/unit/indexed_session_test.cpp#L995); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [src/io/event_reader.cpp](../../../../../src/io/event_reader.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0088

[Lines 1087–1124](../../../../../tests/unit/indexed_session_test.cpp#L1087); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0090

[Lines 1126–1162](../../../../../tests/unit/indexed_session_test.cpp#L1126); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0092

[Lines 1164–1185](../../../../../tests/unit/indexed_session_test.cpp#L1164); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |

## B0093

[Lines 1186–1187](../../../../../tests/unit/indexed_session_test.cpp#L1186); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1186-L1187:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_session_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0094

[Lines 1188–1197](../../../../../tests/unit/indexed_session_test.cpp#L1188); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/unit/indexed_session_test.cpp](../../../../../tests/unit/indexed_session_test.cpp) |
