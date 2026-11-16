# `tests/unit/initialization_test.cpp` — block usage map

[Source](../../../../../tests/unit/initialization_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `47245582c97986ba1e73828100db93b4152b8d7e4f7f3a2d7e045b39652d1f8d`. 822 lines partitioned into 78 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–33](../../../../../tests/unit/initialization_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 34–36](../../../../../tests/unit/initialization_test.cpp#L34) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 37–37](../../../../../tests/unit/initialization_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0004 · 38–48](../../../../../tests/unit/initialization_test.cpp#L38) | Callable definition: template &lt;class Action&gt; void expect_code(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 49–49](../../../../../tests/unit/initialization_test.cpp#L49) | Explanatory comments or spacing. |  |
| [B0006 · 50–50](../../../../../tests/unit/initialization_test.cpp#L50) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 51–51](../../../../../tests/unit/initialization_test.cpp#L51) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0007) |
| [B0008 · 52–52](../../../../../tests/unit/initialization_test.cpp#L52) | Explanatory comments or spacing. |  |
| [B0009 · 53–58](../../../../../tests/unit/initialization_test.cpp#L53) | Callable definition: Row project(const Assignment& assignment, const auto& variables) | calls reserve, size, push_back, at; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 59–59](../../../../../tests/unit/initialization_test.cpp#L59) | Explanatory comments or spacing. |  |
| [B0011 · 60–72](../../../../../tests/unit/initialization_test.cpp#L60) | Callable definition: std::optional&lt;Assignment&gt; assign_terms(const auto& atom, const Row& row) | calls size, emplace, reference::input::scalar; returns {}; {}; growth emplace; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 73–73](../../../../../tests/unit/initialization_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0013 · 74–83](../../../../../tests/unit/initialization_test.cpp#L74) | Callable definition: std::optional&lt;Assignment&gt; source_assignment(const auto& plan, const auto& input, const Row& row, const RowAdapter& adapter = {}) | calls adapter, normalized, assign_terms, query; returns adapter(input.occurrence, row); assign_terms(plan.query().atoms.at(input.occurrence.value), row) · [reviewed contract](#b0013) |
| [B0014 · 84–84](../../../../../tests/unit/initialization_test.cpp#L84) | Explanatory comments or spacing. |  |
| [B0015 · 85–104](../../../../../tests/unit/initialization_test.cpp#L85) | Callable definition: std::vector&lt;std::vector&lt;CanonicalCount&gt;&gt; independent_derivations( const auto& plan, const Database& database, const RowAdapter& a… | calls counts, inputs, size, nodes; returns result; growth push_back, reserve; 4 loop sites · [reviewed contract](#b0015) |
| [B0016 · 105–105](../../../../../tests/unit/initialization_test.cpp#L105) | Explanatory comments or spacing. |  |
| [B0017 · 106–120](../../../../../tests/unit/initialization_test.cpp#L106) | Callable definition: Relation independent_output(const auto& plan, const Database& database) | calls normalized, reference::evaluate, reference::input::catalog, source_catalog; returns reference::evaluate(reference::input::catalog(plan.source_catalog()), reference::input::query(plan.…; growth insert, resize; 2 loop sites · [reviewed contract](#b0017) |
| [B0018 · 121–121](../../../../../tests/unit/initialization_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0019 · 122–135](../../../../../tests/unit/initialization_test.cpp#L122) | Callable definition: Relation independent_core(const auto& plan, const Database& database) | calls normalized, reference::evaluate, reference::input::catalog, source_catalog; returns reference::evaluate(reference::input::catalog(plan.source_catalog()), reference::input::query(plan.…; growth insert, resize; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 136–136](../../../../../tests/unit/initialization_test.cpp#L136) | Explanatory comments or spacing. |  |
| [B0021 · 137–148](../../../../../tests/unit/initialization_test.cpp#L137) | Callable definition: Relation drain(SupportRuntime::ResultCursor& cursor, const std::string& where) | calls next, check, layout, same_token; guard check(tuple-&gt;layout().same_token(cursor.layout()), where + ": tuple layout token changed");; returns rows; growth insert; 2 loop sites · [reviewed contract](#b0021) |
| [B0022 · 149–151](../../../../../tests/unit/initialization_test.cpp#L149) | Callable definition: Relation drain(SupportRuntime::ResultCursor&& cursor,const std::string& where) | calls ; returns drain(cursor,where) · [reviewed contract](#b0022) |
| [B0023 · 152–152](../../../../../tests/unit/initialization_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0024 · 153–170](../../../../../tests/unit/initialization_test.cpp#L153) | Callable definition: void check_physical_state(const PhysicalRuntime& runtime, const Database& database, const RowAdapter& adapter = {}, std::uint64_t… | calls snapshot, canonical_state, check, sequence; guard check(runtime.sequence() == sequence && state.sequence == sequence && · [reviewed contract](#b0024) |
| [B0025 · 171–171](../../../../../tests/unit/initialization_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0026 · 172–193](../../../../../tests/unit/initialization_test.cpp#L172) | Callable definition: std::vector&lt;Relation&gt; independent_live_factors(const auto& plan, const Relation& core) | calls query, size, try_emplace, enumeration; guard check(position != head_positions.end(), "live scope variable missing from core head");; returns result; growth insert, push_back; 4 loop sites · [reviewed contract](#b0026) |
| [B0027 · 194–194](../../../../../tests/unit/initialization_test.cpp#L194) | Explanatory comments or spacing. |  |
| [B0028 · 195–234](../../../../../tests/unit/initialization_test.cpp#L195) | Callable definition: void check_delta_state(const DeltaRuntime& runtime, const Database& database, const RowAdapter& adapter = {}) | calls snapshot, canonical_state, check, sequence; guard check(snapshot.sequence == runtime.sequence() && snapshot.physical.tables == database.tables,; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 235–235](../../../../../tests/unit/initialization_test.cpp#L235) | Explanatory comments or spacing. |  |
| [B0030 · 236–260](../../../../../tests/unit/initialization_test.cpp#L236) | Callable definition: PhysicalPlan intersection_plan(std::size_t children) | calls push_back, std::to_string, insert, begin; returns planner::lower_tree(catalog, query, tree); growth insert, push_back; 2 loop sites · [reviewed contract](#b0030) |
| [B0031 · 261–261](../../../../../tests/unit/initialization_test.cpp#L261) | Explanatory comments or spacing. |  |
| [B0032 · 262–272](../../../../../tests/unit/initialization_test.cpp#L262) | Callable definition: Database intersection_database(std::size_t children) | calls resize, insert, n, s; returns database; growth insert, resize; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 273–273](../../../../../tests/unit/initialization_test.cpp#L273) | Explanatory comments or spacing. |  |
| [B0034 · 274–279](../../../../../tests/unit/initialization_test.cpp#L274) | Callable definition: void check_build_metrics(const BuildMetrics& direct, const BuildMetrics& replay, const std::string& where) | calls check; guard check(direct.replay_inputs == 0 && direct.replay_events == 0 && direct.replay_work == 0, · [reviewed contract](#b0034) |
| [B0035 · 280–280](../../../../../tests/unit/initialization_test.cpp#L280) | Explanatory comments or spacing. |  |
| [B0036 · 281–312](../../../../../tests/unit/initialization_test.cpp#L281) | Callable definition: void generalized_bootstrap_and_live_indexes(std::size_t children) | calls intersection_plan, intersection_database, PhysicalRuntime::initialize, check_build_metrics; guard check(direct.canonical_state() == replay.canonical_state(), · [reviewed contract](#b0036) |
| [B0037 · 313–313](../../../../../tests/unit/initialization_test.cpp#L313) | Explanatory comments or spacing. |  |
| [B0038 · 314–326](../../../../../tests/unit/initialization_test.cpp#L314) | Callable definition: PhysicalPlan internal_native_root_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0038) |
| [B0039 · 327–327](../../../../../tests/unit/initialization_test.cpp#L327) | Explanatory comments or spacing. |  |
| [B0040 · 328–374](../../../../../tests/unit/initialization_test.cpp#L328) | Callable definition: void native_root_and_disconnected_nullary() | calls internal_native_root_plan, n, s, PhysicalRuntime::initialize; guard check(direct.canonical_state() == replay.canonical_state(),; growth resize · [reviewed contract](#b0040) |
| [B0041 · 375–375](../../../../../tests/unit/initialization_test.cpp#L375) | Explanatory comments or spacing. |  |
| [B0042 · 376–416](../../../../../tests/unit/initialization_test.cpp#L376) | Callable definition: PhysicalPlan sql_plan(std::string_view sql, const Catalog& catalog) | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns planner::lower_normalized(program, FreeConnexTree{}); planner::lower_normalized(program, tree); growth insert, push_back; 5 loop sites · [reviewed contract](#b0042) |
| [B0043 · 417–417](../../../../../tests/unit/initialization_test.cpp#L417) | Explanatory comments or spacing. |  |
| [B0044 · 418–421](../../../../../tests/unit/initialization_test.cpp#L418) | Callable definition: PhysicalPlan filtered_self_join_plan(const Catalog& catalog) | calls sql_plan; returns sql_plan(@ · [reviewed contract](#b0044) |
| [B0045 · 422–422](../../../../../tests/unit/initialization_test.cpp#L422) | Explanatory comments or spacing. |  |
| [B0046 · 423–428](../../../../../tests/unit/initialization_test.cpp#L423) | Callable definition: RowAdapter filtered_self_join_adapter() | calls at, n; returns \[\](OccurrenceId occurrence, const Row& row) -&gt; std::optional&lt;Assignment&gt; {; {} · [reviewed contract](#b0046) |
| [B0047 · 429–429](../../../../../tests/unit/initialization_test.cpp#L429) | Explanatory comments or spacing. |  |
| [B0048 · 430–440](../../../../../tests/unit/initialization_test.cpp#L430) | Callable definition: Relation independent_filtered_sql(const Database& database) | calls at, insert, n, contains; returns output; growth insert; 2 loop sites · [reviewed contract](#b0048) |
| [B0049 · 441–441](../../../../../tests/unit/initialization_test.cpp#L441) | Explanatory comments or spacing. |  |
| [B0050 · 442–457](../../../../../tests/unit/initialization_test.cpp#L442) | Callable definition: Relation drain_signed(DeltaRuntime::Epoch& epoch, const Relation& before, const Relation& after, const std::string& where) | calls contains, emplace, next, check; guard check(actual.emplace(record-&gt;operation, crown::storage::export_row(record-&gt;tuple.values())).second,; returns after; growth emplace, insert; 3 loop sites · [reviewed contract](#b0050) |
| [B0051 · 458–458](../../../../../tests/unit/initialization_test.cpp#L458) | Explanatory comments or spacing. |  |
| [B0052 · 459–478](../../../../../tests/unit/initialization_test.cpp#L459) | Callable definition: void apply_checked_sql_delta(DeltaRuntime& runtime, Database& database, std::uint64_t sequence, SetOperation operation, const Row… | calls independent_filtered_sql, insert, erase, apply; guard check(epoch.sequence() == sequence && epoch.input().input.sequence == sequence,; growth insert · [reviewed contract](#b0052) |
| [B0053 · 479–479](../../../../../tests/unit/initialization_test.cpp#L479) | Explanatory comments or spacing. |  |
| [B0054 · 480–512](../../../../../tests/unit/initialization_test.cpp#L480) | Callable definition: void aliases_projection_collisions_and_suffix() | calls filtered_self_join_plan, n, s, filtered_self_join_adapter; guard check(direct.canonical_state() == replay.canonical_state(),; growth insert · [reviewed contract](#b0054) |
| [B0055 · 513–513](../../../../../tests/unit/initialization_test.cpp#L513) | Explanatory comments or spacing. |  |
| [B0056 · 514–528](../../../../../tests/unit/initialization_test.cpp#L514) | Callable definition: PhysicalPlan reciprocal_loop_plan() | calls n, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0056) |
| [B0057 · 529–529](../../../../../tests/unit/initialization_test.cpp#L529) | Explanatory comments or spacing. |  |
| [B0058 · 530–543](../../../../../tests/unit/initialization_test.cpp#L530) | Callable definition: void self_join_loops_and_constants() | calls reciprocal_loop_plan, n, PhysicalRuntime::initialize, check_physical_state; guard check(direct.canonical_state() == replay.canonical_state(), · [reviewed contract](#b0058) |
| [B0059 · 544–544](../../../../../tests/unit/initialization_test.cpp#L544) | Explanatory comments or spacing. |  |
| [B0060 · 545–557](../../../../../tests/unit/initialization_test.cpp#L545) | Callable definition: Catalog cyclic_catalog() | calls ; returns catalog · [reviewed contract](#b0060) |
| [B0061 · 558–558](../../../../../tests/unit/initialization_test.cpp#L558) | Explanatory comments or spacing. |  |
| [B0062 · 559–565](../../../../../tests/unit/initialization_test.cpp#L559) | Callable definition: PhysicalPlan cyclic_plan(const Catalog& catalog) | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0062) |
| [B0063 · 566–566](../../../../../tests/unit/initialization_test.cpp#L566) | Explanatory comments or spacing. |  |
| [B0064 · 567–603](../../../../../tests/unit/initialization_test.cpp#L567) | Callable definition: void cyclic_constraints_and_rejected_images() | calls cyclic_catalog, cyclic_plan, n, s; guard check(initialized.sequence() == 0 && initialized.snapshot().physical.tables == cycle.tables,; growth insert · [reviewed contract](#b0064) |
| [B0065 · 604–604](../../../../../tests/unit/initialization_test.cpp#L604) | Explanatory comments or spacing. |  |
| [B0066 · 605–656](../../../../../tests/unit/initialization_test.cpp#L605) | Callable definition: void physical_rebuild_ownership_and_barriers() | calls intersection_plan, intersection_database, PhysicalRuntime::initialize, find_source; guard check(initial_handle.has_value(), "initialized source handle missing");; returns *tuple; growth insert · [reviewed contract](#b0066) |
| [B0067 · 657–657](../../../../../tests/unit/initialization_test.cpp#L657) | Explanatory comments or spacing. |  |
| [B0068 · 658–690](../../../../../tests/unit/initialization_test.cpp#L658) | Callable definition: void delta_rebuild_preserves_mode_and_barrier() | calls intersection_plan, intersection_database, DeltaRuntime::initialize, apply; guard check(rebuilt.owner() != runtime.owner() && rebuilt.sequence() == 1 &&; growth insert · [reviewed contract](#b0068) |
| [B0069 · 691–691](../../../../../tests/unit/initialization_test.cpp#L691) | Explanatory comments or spacing. |  |
| [B0070 · 692–738](../../../../../tests/unit/initialization_test.cpp#L692) | Callable definition: void scalar_exists_and_constant_routes() | calls sql_plan, resize, DeltaRuntime::initialize, check_delta_state; guard check(drain(false_at_zero.results(), "false scalar exists at sequence zero") ==; growth resize · [reviewed contract](#b0070) |
| [B0071 · 739–739](../../../../../tests/unit/initialization_test.cpp#L739) | Explanatory comments or spacing. |  |
| [B0072 · 740–744](../../../../../tests/unit/initialization_test.cpp#L740) | Callable definition: std::string json_input(const auto& plan, std::uint64_t sequence, TableId table, Row row) | calls io::write_input_json, std::move, source_catalog; returns io::write_input_json({PhysicalSetUpdate{sequence, table, SetOperation::insert, std::move(row)},; growth insert · [reviewed contract](#b0072) |
| [B0073 · 745–745](../../../../../tests/unit/initialization_test.cpp#L745) | Explanatory comments or spacing. |  |
| [B0074 · 746–787](../../../../../tests/unit/initialization_test.cpp#L746) | Callable definition: void session_initial_database_and_first_event() | calls filtered_self_join_plan, n, s, json_input; guard check(session-&gt;status().committed_sequence == 0 && session-&gt;progress() == io::InputProgress{},; growth emplace, insert, make_unique; 4 loop sites · [reviewed contract](#b0074) |
| [B0075 · 788–788](../../../../../tests/unit/initialization_test.cpp#L788) | Explanatory comments or spacing. |  |
| [B0076 · 789–798](../../../../../tests/unit/initialization_test.cpp#L789) | Callable definition: void initialization_budgets() | calls intersection_plan, intersection_database, expect_code, PhysicalRuntime::initialize · [reviewed contract](#b0076) |
| [B0077 · 799–800](../../../../../tests/unit/initialization_test.cpp#L799) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0077) |
| [B0078 · 801–822](../../../../../tests/unit/initialization_test.cpp#L801) | Callable definition: int main() | calls static_assert, generalized_bootstrap_and_live_indexes, native_root_and_disconnected_nullary, aliases_projection_collisions_and_suffix; guard static_assert(!std::is_copy_constructible_v&lt;PhysicalRuntime&gt;);; returns 1 · [reviewed contract](#b0078) |

## B0001

[Lines 1–33](../../../../../tests/unit/initialization_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L33:sha256:dec9e64838ca076623cd109003783d348f28f8192eda28dea452dbf1ae7f67cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare initialization_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", "evaluator.hpp", "native_input.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 34–36](../../../../../tests/unit/initialization_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a test predicate with its owned string diagnostic. |
| inputs / outputs | Takes bool and const std::string&; returns for true. |
| invariants | No CROWN error translation. |
| ownership | Message borrowed during call. |
| failure | False throws std::runtime_error. |
| cost | One branch. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp) |

## B0004

[Lines 38–48](../../../../../tests/unit/initialization_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw exactly the given CROWN Error code. |
| inputs / outputs | Forwards action and borrows code view; returns after matching Error. |
| invariants | Catches only crown::Error; mismatched code fails through check and other exception types propagate. |
| ownership | Action/code are borrowed during invocation. |
| failure | No Error or wrong code throws test runtime_error. |
| cost | One action call and string-code comparison. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0006

[Lines 50–50](../../../../../tests/unit/initialization_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 fixture scalar Value. |
| inputs / outputs | Takes signed integer; returns Value by value. |
| invariants | Preserves input integer. |
| ownership | No external row state. |
| failure | No custom failure translation. |
| cost | Scalar conversion. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0007

[Lines 51–51](../../../../../tests/unit/initialization_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a string fixture scalar Value. |
| inputs / outputs | Takes string by value; returns Value by moving/copying that value. |
| invariants | Preserves string contents. |
| ownership | Returned Value owns scalar string storage. |
| failure | Allocation/copy failures propagate. |
| cost | One scalar value construction. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0009

[Lines 53–58](../../../../../tests/unit/initialization_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row project(const Assignment& assignment, const auto& variables) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an Assignment into the requested variable order. |
| inputs / outputs | Takes borrowed assignment and variable range; returns Row by value. |
| invariants | Each output position uses assignment.at(variable); missing variables throw. |
| ownership | Returned row owns copied Values; assignment borrowed. |
| failure | out_of_range/allocation failures propagate. |
| cost | Visits every requested variable. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp) |

## B0011

[Lines 60–72](../../../../../tests/unit/initialization_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Assignment> assign_terms(const auto& atom, const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Match one atom’s terms against one physical or logical row. |
| inputs / outputs | Takes atom/row by reference; returns optional Assignment. |
| invariants | Rejects arity mismatch, inconsistent repeated variables, and constant inequality; matching variables are copied into map. |
| ownership | Inputs borrowed; returned map owns assigned Values. |
| failure | Value/map allocation or bad row variant access may propagate. |
| cost | Scans row terms once. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0013

[Lines 74–83](../../../../../tests/unit/initialization_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<Assignment> source_assignment(const auto& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map one plan input occurrence and source row to its logical assignment. |
| inputs / outputs | Takes plan, input, row and optional adapter by const reference; returns optional Assignment. |
| invariants | Adapter takes precedence; otherwise classic plan matches query atom directly, while normalized plan adapts physical row then matches normalized core atom. |
| ownership | All inputs borrowed; optional result owns its Values. |
| failure | Bad occurrence/index or adapter/frontend failures propagate. |
| cost | One adapter or one term match plus optional normalized adaptation. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0015

[Lines 85–104](../../../../../tests/unit/initialization_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::vector<CanonicalCount>> independent_derivations(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently count per-occurrence source derivations projected to each node scope. |
| inputs / outputs | Takes plan/database and optional adapter by reference; returns vector of canonical count entries. |
| invariants | Scans plan inputs and complete database table rows; counts each accepted source assignment by projected scope key, independently of runtime indexes. |
| ownership | Inputs borrowed; returned vectors/maps own their row keys and counts. |
| failure | Index/adapter/container errors propagate. |
| cost | Scans every fixture source row and emits sorted map entries. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0017

[Lines 106–120](../../../../../tests/unit/initialization_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation independent_output(const auto& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the expected query result with the A04 reference evaluator. |
| inputs / outputs | Takes plan/database by const reference; returns Relation. |
| invariants | Classic plan evaluates catalog/query directly; normalized SQL adapts physical rows to logical tables, evaluates normalized core, then maps SQL projection. |
| ownership | Plan/database borrowed; logical database and returned relation are local owning values. |
| failure | Adapter/reference/evaluator failures propagate. |
| cost | Builds a finite logical snapshot as needed, then runs independent A04 evaluation. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0019

[Lines 122–135](../../../../../tests/unit/initialization_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation independent_core(const auto& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute only the normalized core relation with the independent A04 evaluator. |
| inputs / outputs | Takes plan/database by const reference; returns core Relation. |
| invariants | Classic plan follows direct A04 path; normalized plan adapts base rows into core tables and evaluates core without SQL result mapping. |
| ownership | Inputs borrowed; logical database and relation own their rows. |
| failure | Adapter/evaluator errors propagate. |
| cost | Finite row adaptation plus one A04 core evaluation. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0021

[Lines 137–148](../../../../../tests/unit/initialization_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor& cursor, const std::string& where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a support result cursor and validate its tuple layout and set uniqueness. |
| inputs / outputs | Consumes a borrowed lvalue cursor and label; returns Relation of exported rows. |
| invariants | Each tuple must retain cursor layout token, expected arity/scalar types, and unique set row. |
| ownership | Cursor borrowed and consumed; exported Relation owns values. |
| failure | Any mismatch throws runtime_error; cursor errors propagate. |
| cost | Reads all emitted tuples and copies them into a set. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0022

[Lines 149–151](../../../../../tests/unit/initialization_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor&& cursor,const std::string& where) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward an rvalue result cursor to the lvalue drain helper. |
| inputs / outputs | Takes cursor by rvalue reference and label; returns Relation. |
| invariants | No separate drain logic; delegates once to lvalue overload. |
| ownership | Consumes supplied cursor; returned relation owns exported rows. |
| failure | Delegated failures propagate. |
| cost | Same work as one full drain. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0024

[Lines 153–170](../../../../../tests/unit/initialization_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_physical_state(const PhysicalRuntime& runtime, const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare initialized PhysicalRuntime snapshot, canonical state, invariants and output with source scan/A04. |
| inputs / outputs | Takes runtime/database and optional adapter by reference plus expected sequence; returns void. |
| invariants | Requires all exposed snapshot/canonical/support sequences, source rows, per-occurrence counts, invariant report and result rows to match. |
| ownership | Runtime/database borrowed; snapshots, cursor and relations local; drain exports row values. |
| failure | Mismatch throws runtime_error; API/reference failures propagate. |
| cost | Materializes snapshots/canonical state, scans all source rows, then drains full result. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0026

[Lines 172–193](../../../../../tests/unit/initialization_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> independent_live_factors(const auto& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project the independent core relation to each plan enumeration factor’s visible scope. |
| inputs / outputs | Takes plan and core relation by reference; returns one Relation per enumeration step. |
| invariants | Maps visible-scope variables through first head position and inserts projected keys into set factors. |
| ownership | Inputs borrowed; returned factor relations own keys. |
| failure | Missing head variable or row index fails through check/at. |
| cost | Scans each core row for every factor scope. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp) |

## B0028

[Lines 195–234](../../../../../tests/unit/initialization_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_delta_state(const DeltaRuntime& runtime, const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check DeltaRuntime physical/canonical/output state and, in delta mode, live factor indexes. |
| inputs / outputs | Takes runtime/database and optional adapter by reference; returns void. |
| invariants | Always checks sequence/source rows, derivation scan, invariants and A04 output. Maintenance mode must have no live image; delta mode must match independent factors and reconciled row/parent/child totals. |
| ownership | Runtime/database borrowed; snapshots, cursor, factors and output local values. |
| failure | Any discrepancy throws runtime_error; runtime calls propagate errors. |
| cost | Reads full state and scans output/factor indexes; does not assert runtime cost or timing. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md) |

## B0030

[Lines 236–260](../../../../../tests/unit/initialization_test.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan intersection_plan(std::size_t children) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a generalized intersection plan with one native child per source table. |
| inputs / outputs | Takes child count; returns owned PhysicalPlan. |
| invariants | Tables include x/local/payload; child scopes are {x,vi}; generalized root scope is {x}; lowering uses the classic planner in this source and s04 indexed options in indexed_initialization_test.cpp. |
| ownership | Returned plan owns metadata. |
| failure | Lowering/allocation errors propagate. |
| cost | Builds child-count-proportional fixture metadata and lowers once. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0032

[Lines 262–272](../../../../../tests/unit/initialization_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database intersection_database(std::size_t children) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create duplicate-projection rows for generalized intersection initialization. |
| inputs / outputs | Takes child count; returns Database by value. |
| invariants | Each table has two full rows with same x/local but different payload; x=2 occurs in all but last child so only x=1 survives all-child intersection. |
| ownership | Returned database owns row sets and scalar strings. |
| failure | Allocation failures propagate. |
| cost | Builds a small fixed number of rows per child. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp) |

## B0034

[Lines 274–279](../../../../../tests/unit/initialization_test.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_build_metrics(const BuildMetrics& direct, const BuildMetrics& replay,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish direct build metrics from insertion-replay metrics. |
| inputs / outputs | Takes direct/replay metrics and a label by reference; returns void. |
| invariants | Direct must report zero replay inputs/events/work; replay must report at least one replay input. |
| ownership | Metrics/label borrowed. |
| failure | Mismatch throws runtime_error. |
| cost | Constant scalar comparisons. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/runtime/initialization.hpp](../../../../../include/crown/runtime/initialization.hpp) |

## B0036

[Lines 281–312](../../../../../tests/unit/initialization_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generalized_bootstrap_and_live_indexes(std::size_t children) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare direct and insertion-replay physical/delta bootstrap and live indexes for a generalized root. |
| inputs / outputs | Takes child count; constructs plan/database and four initialized owners. |
| invariants | Requires independent physical state and canonical equality; root has two records and survivor x=1; delta direct/replay match with zero spool-retained signed rows and independently checked live state. |
| ownership | Plan/database local; each runtime owns its initialized state. |
| failure | Runtime initialization/assertion errors propagate. |
| cost | Builds direct and replay owners for PhysicalRuntime and DeltaRuntime, then materializes full state checks. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Distinct construction methods](../../../../runtime_initialization.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0038

[Lines 314–326](../../../../../tests/unit/initialization_test.cpp#L314); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan internal_native_root_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an internal-native-root join plan over left(x,y) and right(y,z). |
| inputs / outputs | No arguments; returns lowered PhysicalPlan. |
| invariants | Native left root has native right child; tag columns are ignored. Indexed test delegates lowering through fixed s04 options. |
| ownership | Returned plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | Constructs fixed catalog/query/tree and lowers once. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0040

[Lines 328–374](../../../../../tests/unit/initialization_test.cpp#L328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_root_and_disconnected_nullary() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise native-root, disconnected-product and nullary initialization snapshots. |
| inputs / outputs | No arguments; creates several plans/databases and returns after assertions. |
| invariants | Compares direct/replay native-root canonical state; A04 checks 2x2 product through empty separator; empty/nonempty nullary native occurrence retains derivation count and answer presence. |
| ownership | Each runtime owns input state; fixture values/cursors are local. |
| failure | Any initialization/output mismatch throws runtime_error. |
| cost | Initializes a fixed set of small physical runtimes and drains results. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0042

[Lines 376–416](../../../../../tests/unit/initialization_test.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan sql_plan(std::string_view sql, const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize fixture SQL, then build a native or generalized lower tree. |
| inputs / outputs | Borrows SQL view and catalog; returns PhysicalPlan. |
| invariants | Converts binding/normalization diagnostics to runtime_error; no-atom/contradiction uses empty tree; one atom uses native scope; multi-atom uses generalized intersection of scopes; indexed file uses s04 lowering wrappers. |
| ownership | Input SQL/catalog borrowed; normalized program and returned plan own values. |
| failure | Diagnostic or lowering/allocation failure propagates or is converted as described. |
| cost | Runs bind+normalize and constructs one fixture tree. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0044

[Lines 418–421](../../../../../tests/unit/initialization_test.cpp#L418); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan filtered_self_join_plan(const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the filtered repeated-column/constant SQL self-join fixture plan. |
| inputs / outputs | Takes catalog by const reference; returns plan from sql_plan. |
| invariants | Query is fixed to DISTINCT a.x, a.x AS again, 7 AS fixed, self-joining r with a.flag=1. |
| ownership | Catalog borrowed during lowering; returned plan owns metadata. |
| failure | Binding/normalization/lowering failures propagate. |
| cost | One fixed sql_plan invocation. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp) |

## B0046

[Lines 423–428](../../../../../tests/unit/initialization_test.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowAdapter filtered_self_join_adapter() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt the filtered self-join’s physical rows into the logical x assignment. |
| inputs / outputs | Takes no arguments; returns callable RowAdapter. |
| invariants | Occurrence 0 rejects rows unless flag field equals 1; other occurrence accepts; both map first field to variable 0. |
| ownership | Returned stateless lambda owns no referenced database state. |
| failure | Short row can throw via row.at; caller controls occurrence/shape. |
| cost | Constructs one small callable. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp) |

## B0048

[Lines 430–440](../../../../../tests/unit/initialization_test.cpp#L430); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation independent_filtered_sql(const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute expected filtered self-join SQL output without using runtime state. |
| inputs / outputs | Takes database by const reference; returns Relation. |
| invariants | Builds all right-side x values and flag-filtered left x values, intersects them, and emits {x,x,7}. |
| ownership | Input borrowed; returned set owns rows. |
| failure | Row access/allocation failures propagate. |
| cost | Scans the one fixture table and intersects finite sets. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0050

[Lines 442–457](../../../../../tests/unit/initialization_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain_signed(DeltaRuntime::Epoch& epoch, const Relation& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain and validate one DeltaRuntime epoch’s signed output against independent before/after relations. |
| inputs / outputs | Takes epoch and relations by reference plus label; returns after Relation by value. |
| invariants | Expected rows are set difference inserts/deletes; each raw record must be unique and share epoch layout token; returned relation is the supplied after snapshot. |
| ownership | Epoch/inputs borrowed; actual signed set owns copied rows. |
| failure | Duplicate/wrong output or layout mismatch throws runtime_error. |
| cost | Reads all epoch output and compares finite set differences. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0052

[Lines 459–478](../../../../../tests/unit/initialization_test.cpp#L459); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_checked_sql_delta(DeltaRuntime& runtime, Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one SQL self-join suffix update and verify its signed/committed state. |
| inputs / outputs | Takes runtime/database by reference, sequence, operation and row; returns void. |
| invariants | Computes independent before/after output, applies event, checks exact sequence, drains signed epoch, mutates local caller database only after drain, then checks ready/sequence/state/output. |
| ownership | Runtime/database are caller-owned; local after DB and relation snapshots own values. |
| failure | Runtime/A04/assertion failures propagate; no retry path is tested. |
| cost | One delta event plus full state and result checks. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0054

[Lines 480–512](../../../../../tests/unit/initialization_test.cpp#L480); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void aliases_projection_collisions_and_suffix() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise aliases, projected duplicate identities and an eight-event initialized delta suffix. |
| inputs / outputs | No arguments; builds plan/database, physical and delta runtimes. |
| invariants | Payload-distinct rows count as two source derivations per alias while result is set-distinct; direct/replay agree; eight events include duplicate insert, filter, match and absent/present erase with A04 before/after oracle. |
| ownership | All runtimes and databases local owning values. |
| failure | Unexpected state/output raises runtime_error. |
| cost | Initializes three runtimes, applies eight finite events, and repeatedly checks full state. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0056

[Lines 514–528](../../../../../tests/unit/initialization_test.cpp#L514); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan reciprocal_loop_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a reciprocal/repeated-variable loop plan with constant enabled=1 terms. |
| inputs / outputs | No arguments; returns lowered PhysicalPlan. |
| invariants | Three native occurrences represent forward, reverse and loop; head repeats x as again; indexed variant selects indexed lower options. |
| ownership | Returned plan owns metadata. |
| failure | Lowering/allocation errors propagate. |
| cost | Fixed plan construction and lowering. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0058

[Lines 530–543](../../../../../tests/unit/initialization_test.cpp#L530); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void self_join_loops_and_constants() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare direct and replay initialization for reciprocal loops, repeated variables and constants. |
| inputs / outputs | No arguments; creates plan/database and two runtimes. |
| invariants | A04 state checks plus exact expected result ensure disabled row is filtered, loops and reciprocal pairs preserve repeated output x. |
| ownership | Runtimes own database snapshots; local fixture rows/cursors. |
| failure | Unexpected output/state fails. |
| cost | Initializes two small runtimes and drains them. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0060

[Lines 545–557](../../../../../tests/unit/initialization_test.cpp#L545); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog cyclic_catalog() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create catalog with enforced unique and cyclic foreign-key constraints plus unused table. |
| inputs / outputs | No arguments; returns Catalog. |
| invariants | A and B reference each other; unused table has string label and still participates in full-database validation. |
| ownership | Returned catalog owns definitions. |
| failure | Allocation failures propagate. |
| cost | Constructs three table definitions and four constraints. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp) |

## B0062

[Lines 559–565](../../../../../tests/unit/initialization_test.cpp#L559); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan cyclic_plan(const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-column plan over table a while retaining full cyclic catalog metadata. |
| inputs / outputs | Takes catalog by const reference; returns PhysicalPlan. |
| invariants | Query reads only a.id, but runtime initialization validates catalog-wide constraints; indexed test uses indexed lower wrapper. |
| ownership | Catalog borrowed during lowering; plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed query/tree lowering. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0064

[Lines 567–603](../../../../../tests/unit/initialization_test.cpp#L567); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cyclic_constraints_and_rejected_images() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test full-snapshot cyclic constraints and rejected database images. |
| inputs / outputs | No arguments; creates valid and malformed catalogs/databases/runtimes. |
| invariants | Valid cyclic FK snapshot initializes at seq0; writes to empty runtime cannot satisfy required constraint; duplicate unique, dangling FK even in unused table, missing table, short row and wrong type map to asserted error codes. |
| ownership | All fixture values and initialized runtime local; rejected factory results do not escape. |
| failure | Uses exact constraint_violation, invalid_database and invalid_update codes; mismatches fail. |
| cost | Runs several validation attempts over small snapshots; no allocation fault is armed. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0066

[Lines 605–656](../../../../../tests/unit/initialization_test.cpp#L605); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_rebuild_ownership_and_barriers() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check PhysicalRuntime rebuild barriers, failed build preservation, new owner and old-handle lifetime. |
| inputs / outputs | No arguments; constructs initialized runtime and rebuilt copy. |
| invariants | Active cursor and pending update block rebuild; work limit zero fails without changing original; after commit rebuild has new owner but same sequence/canonical state; source/support handles remain tied to old owner; old tuple keeps owned values. |
| ownership | Original and rebuilt owners are distinct move-only runtimes; old tuple owns returned values; handles are owner-scoped. |
| failure | Checks runtime_busy, resource_limit, foreign_handle and foreign_support_handle codes. |
| cost | One initial build, bounded rebuild attempts and one successful rebuild plus state scan. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0068

[Lines 658–690](../../../../../tests/unit/initialization_test.cpp#L658); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_rebuild_preserves_mode_and_barrier() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check DeltaRuntime rebuild preserves mode/options/state and respects live output barrier. |
| inputs / outputs | No arguments; creates runtime, applies three events and rebuilds. |
| invariants | Successful rebuilt owner differs and preserves sequence/canonical state/delta/eager options; active epoch output makes rebuild busy until discard, then rebuilt seq3 matches original committed state. |
| ownership | Original and rebuilt owners own separate runtime facades over same-account indexed state; output epoch locally owns its lease. |
| failure | Busy barrier/assertion failures propagate; no allocator fault injection. |
| cost | Initial build, three updates, two rebuild calls and full-state check. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0070

[Lines 692–738](../../../../../tests/unit/initialization_test.cpp#L692); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_exists_and_constant_routes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize scalar EXISTS and source-free/source-backed constant projections. |
| inputs / outputs | No arguments; binds several SQL plans and initializes DeltaRuntime/PhysicalRuntime values. |
| invariants | False/true EXISTS rows at seq0 with spool limits zero; SELECT DISTINCT 7 without source yields {7}; source-backed nullary route emits {7} iff source exists with derivation count 2; WHERE FALSE retains source snapshot but emits none. |
| ownership | Each runtime owns supplied snapshot; output relations local. |
| failure | Binding/lowering/init errors propagate; assertion mismatch fails. |
| cost | Several small initializations and full independent state checks; no timing claim. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0072

[Lines 740–744](../../../../../tests/unit/initialization_test.cpp#L740); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string json_input(const auto& plan, std::uint64_t sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one insert event as JSONL for the plan source catalog. |
| inputs / outputs | Borrows plan; takes sequence/table and Row by value; returns string ending newline. |
| invariants | Uses io::write_input_json with no source position; operation is insert. |
| ownership | Returned string owns bytes; row is moved into event. |
| failure | Encoder/allocation failures propagate. |
| cost | One record serialization. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp) |

## B0074

[Lines 746–787](../../../../../tests/unit/initialization_test.cpp#L746); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void session_initial_database_and_first_event() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a QuerySession over an initial snapshot and commit its first external input event. |
| inputs / outputs | No arguments; builds plan, owned stream, supplied Database and session. |
| invariants | Initial database is copied/owned but does not increment accepted input progress; seq0 snapshot matches A04; first stream event seq1 prepares/commits, emits exact signed delta, and seq1 snapshot matches updated source. |
| ownership | Session owner retains initialized runtime and moved input stream; original Database can be mutated after create; snapshots/output rows are owning values. |
| failure | Session/API/assertion failures propagate; this case has no WAL or sink. |
| cost | One session creation, one input preparation/commit and two snapshots; no wall-clock bound. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0076

[Lines 789–798](../../../../../tests/unit/initialization_test.cpp#L789); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialization_budgets() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that direct and replay PhysicalRuntime initialization obey cumulative work budget zero. |
| inputs / outputs | No arguments; constructs plan/database and performs two initialize calls. |
| invariants | Both BuildMethod paths must throw resource_limit; no returned runtime is available for partial-state inspection. |
| ownership | Plan/database are local borrowed inputs during call. |
| failure | expect_code requires exact resource_limit code. |
| cost | Two deterministic budget-limited initialization attempts; not allocator-fault or DeltaRuntime coverage. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Work budgets and build metrics](../../../../runtime_initialization.md) |

## B0077

[Lines 799–800](../../../../../tests/unit/initialization_test.cpp#L799); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L799-L800:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in initialization_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0078

[Lines 801–822](../../../../../tests/unit/initialization_test.cpp#L801); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run initialization/bootstrap, rebuild, SQL, constraint, session-first-event and budget scenarios. |
| inputs / outputs | Takes process arguments implicitly; static-asserts PhysicalRuntime/DeltaRuntime/QuerySession are not copyable; returns 0 or 1. |
| invariants | Runs the listed finite fixture helpers and catches std::exception; printing PASS is program behavior only, not evidence this review executed it. |
| ownership | Scenario state is local to calls. |
| failure | Caught exception prints diagnostic and returns 1. |
| cost | Calls each fixture group once; some helpers instantiate fixed child counts and event suffixes. |
| Design | [tests/unit/initialization_test.cpp](../../../../../tests/unit/initialization_test.cpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |
