# `tests/unit/indexed_delta_runtime_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_delta_runtime_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `02c9fcce2fe198dad781c781edc329faaf84350b244cc1bb12b66429d936ad30`. 1446 lines partitioned into 95 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–35](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 36–47](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L36) | Callable definition: DeltaRuntime make_runtime(PhysicalPlan plan,DeltaOptions options={}) | calls runtime, std::move, statistics_acceptance::enable, DeltaRuntime; returns runtime; DeltaRuntime(std::move(plan),options) · [reviewed contract](#b0002) |
| [B0003 · 48–49](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L48) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 50–52](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L50) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0004) |
| [B0005 · 53–53](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L53) | Explanatory comments or spacing. |  |
| [B0006 · 54–64](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L54) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::string; guard check(failure.code() == code, · [reviewed contract](#b0006) |
| [B0007 · 65–65](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L65) | Explanatory comments or spacing. |  |
| [B0008 · 66–66](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L66) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 67–67](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L67) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0009) |
| [B0010 · 68–68](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L68) | Explanatory comments or spacing. |  |
| [B0011 · 69–83](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L69) | Callable definition: std::string row_string(const Row& row) | calls size, std::visit, constexpr, to_string; returns @ + value + @; value ? @ : @; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 84–84](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L84) | Explanatory comments or spacing. |  |
| [B0013 · 85–93](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L85) | Callable definition: std::set&lt;SignedKey&gt; exact_difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 94–94](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L94) | Explanatory comments or spacing. |  |
| [B0015 · 95–102](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L95) | Callable definition: std::set&lt;SignedKey&gt; record_set(const std::vector&lt;SignedResult&gt;& records) | calls check, emplace, crown::storage::export_row, values; guard check(result.emplace(record.operation, crown::storage::export_row(record.tuple.values())).second,; returns result; growth emplace; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 103–103](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L103) | Explanatory comments or spacing. |  |
| [B0017 · 104–108](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L104) | Callable definition: VariableSet variable_set(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 109–109](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0019 · 110–142](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L110) | Callable definition: FreeConnexTree sql_tree(const Query& query) | calls empty, scopes, size, insert; returns {}; {NodeId{0},; growth insert, push_back; 5 loop sites · [reviewed contract](#b0019) |
| [B0020 · 143–143](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L143) | Explanatory comments or spacing. |  |
| [B0021 · 144–155](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L144) | Callable definition: PhysicalPlan sql_plan(std::string_view sql, const Catalog& catalog) | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns s04_runtime::lower_normalized(program, sql_tree(program.core)) · [reviewed contract](#b0021) |
| [B0022 · 156–156](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L156) | Explanatory comments or spacing. |  |
| [B0023 · 157–172](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L157) | Callable definition: Relation a04_core(const auto& plan, const Database& physical) | calls normalized, reference::evaluate, reference::input::catalog, catalog; returns reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()…; growth insert, resize; 2 loop sites · [reviewed contract](#b0023) |
| [B0024 · 173–173](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L173) | Explanatory comments or spacing. |  |
| [B0025 · 174–179](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L174) | Callable definition: Relation a04_output(const auto& plan, const Database& physical) | calls a04_core, normalized, frontend::map_sql_result, reference::input::normalized; returns frontend::map_sql_result(reference::input::normalized(*plan.normalized()), core); core · [reviewed contract](#b0025) |
| [B0026 · 180–180](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L180) | Explanatory comments or spacing. |  |
| [B0027 · 181–206](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L181) | Callable definition: std::vector&lt;Relation&gt; project_core_to_live_scopes(const auto& plan, const Relation& core) | calls query, size, try_emplace, reserve; guard check(position != head_positions.end(),; returns result; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0027) |
| [B0028 · 207–207](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0029 · 208–221](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L208) | Callable definition: void check_live(const DeltaRuntime& runtime, const Database& physical, const std::string& where) | calls mode, check, live_snapshot, has_value; guard check(!runtime.live_snapshot(), where + ": maintenance mode retained L"); · [reviewed contract](#b0029) |
| [B0030 · 222–222](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L222) | Explanatory comments or spacing. |  |
| [B0031 · 223–227](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L223) | Type/record definition: struct OracleRoute |  · [reviewed contract](#b0031) |
| [B0032 · 228–232](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L228) | declares types or opens a type body. | source comment (unverified): // Independent occurrence-prefix evaluator. It expands each physical input · [reviewed contract](#b0032) |
| [B0033 · 233–267](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L233) | Callable definition: public: PrefixOracle(const Plan& plan, const Database& physical) : plan_(plan), normalized_(plan.normalized().has_value()) | calls plan_, normalized_, normalized, has_value; growth push_back, resize; 2 loop sites · [reviewed contract](#b0033) |
| [B0034 · 268–268](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L268) | Explanatory comments or spacing. |  |
| [B0035 · 269–271](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L269) | Callable definition: \[\[nodiscard\]\] Relation core() const | calls reference::evaluate; returns reference::evaluate(catalog_, query_, database_) · [reviewed contract](#b0035) |
| [B0036 · 272–272](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L272) | Explanatory comments or spacing. |  |
| [B0037 · 273–278](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L273) | Callable definition: \[\[nodiscard\]\] Relation output() const | calls core, frontend::map_sql_result, reference::input::normalized, normalized; returns frontend::map_sql_result(reference::input::normalized(*plan_.normalized()), result); result · [reviewed contract](#b0037) |
| [B0038 · 279–279](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L279) | Explanatory comments or spacing. |  |
| [B0039 · 280–293](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L280) | Callable definition: void apply(OccurrenceId occurrence, const PhysicalSetUpdate& update) | calls at, check, insert, erase; guard check(route.base == update.table,; growth insert · [reviewed contract](#b0039) |
| [B0040 · 294–294](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L294) | Explanatory comments or spacing. |  |
| [B0041 · 295–304](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L295) | Callable definition: private: void rebuild_normalized(OccurrenceId occurrence) | calls reference::input::normalized, normalized, at, frontend::adapt_row; growth insert; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 305–313](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L305) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0042) |
| [B0043 · 314–321](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L314) | Type/record definition: struct ActualEpoch |  · [reviewed contract](#b0043) |
| [B0044 · 322–322](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L322) | Explanatory comments or spacing. |  |
| [B0045 · 323–340](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L323) | Callable definition: Relation drain_current(SupportRuntime::ResultCursor& cursor, const std::string& where) | calls next, check, layout, same_token; guard check(tuple-&gt;layout().same_token(cursor.layout()),; returns rows; growth insert; 2 loop sites · [reviewed contract](#b0045) |
| [B0046 · 341–341](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L341) | Explanatory comments or spacing. |  |
| [B0047 · 342–352](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L342) | Callable definition: void check_current(const DeltaRuntime& runtime, const Database& physical, const std::string& where) | calls core_results, check, drain_current, a04_core; guard check(drain_current(core_cursor, where + " core") == · [reviewed contract](#b0047) |
| [B0048 · 353–353](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L353) | Explanatory comments or spacing. |  |
| [B0049 · 354–389](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L354) | Callable definition: ActualEpoch drain_epoch(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch, const std::set&lt;SignedKey&gt;& expected, const std::string… | calls check, layout, same_token, result_layout; guard check(epoch.layout().same_token(runtime.result_layout()),; returns actual; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0049) |
| [B0050 · 390–390](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L390) | Explanatory comments or spacing. |  |
| [B0051 · 391–650](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L391) | Callable definition: ActualEpoch apply_checked(DeltaRuntime& runtime, Database& database, const PhysicalSetUpdate& update, const std::string& label, b… | calls check, sequence, a04_output, plan; guard check(update.sequence == runtime.sequence() + 1,; returns actual; growth emplace, insert, push_back, reserve; 11 loop sites · [reviewed contract](#b0051) |
| [B0052 · 651–651](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L651) | Explanatory comments or spacing. |  |
| [B0053 · 652–669](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L652) | Callable definition: void seed_maintenance(DeltaRuntime& runtime, const Database& database, const std::string& label) | calls check, mode, live_snapshot, size; guard check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot(),; growth insert; 2 loop sites · [reviewed contract](#b0053) |
| [B0054 · 670–670](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L670) | Explanatory comments or spacing. |  |
| [B0055 · 671–682](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L671) | Callable definition: PhysicalPlan hidden_projection_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0055) |
| [B0056 · 683–683](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L683) | Explanatory comments or spacing. |  |
| [B0057 · 684–693](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L684) | Callable definition: PhysicalPlan hidden_binary_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0057) |
| [B0058 · 694–694](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L694) | Explanatory comments or spacing. |  |
| [B0059 · 695–704](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L695) | Callable definition: PhysicalPlan root_pair_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0059) |
| [B0060 · 705–705](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L705) | Explanatory comments or spacing. |  |
| [B0061 · 706–718](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L706) | Callable definition: PhysicalPlan ancestor_child_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0061) |
| [B0062 · 719–719](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L719) | Explanatory comments or spacing. |  |
| [B0063 · 720–736](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L720) | Callable definition: PhysicalPlan deep_chain_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0063) |
| [B0064 · 737–737](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L737) | Explanatory comments or spacing. |  |
| [B0065 · 738–750](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L738) | Callable definition: PhysicalPlan root_child_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0065) |
| [B0066 · 751–751](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L751) | Explanatory comments or spacing. |  |
| [B0067 · 752–764](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L752) | Callable definition: PhysicalPlan projected_path_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0067) |
| [B0068 · 765–765](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L765) | Explanatory comments or spacing. |  |
| [B0069 · 766–779](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L766) | Callable definition: PhysicalPlan hidden_separator_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0069) |
| [B0070 · 780–780](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L780) | Explanatory comments or spacing. |  |
| [B0071 · 781–788](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L781) | Callable definition: PhysicalPlan boolean_unary_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0071) |
| [B0072 · 789–789](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L789) | Explanatory comments or spacing. |  |
| [B0073 · 790–803](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L790) | Callable definition: PhysicalPlan shared_separator_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0073) |
| [B0074 · 804–804](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L804) | Explanatory comments or spacing. |  |
| [B0075 · 805–819](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L805) | Callable definition: PhysicalPlan self_join_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0075) |
| [B0076 · 820–820](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L820) | Explanatory comments or spacing. |  |
| [B0077 · 821–833](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L821) | Callable definition: PhysicalPlan same_scope_alias_plan() | calls variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree) · [reviewed contract](#b0077) |
| [B0078 · 834–834](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L834) | Explanatory comments or spacing. |  |
| [B0079 · 835–855](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L835) | Callable definition: PhysicalPlan product_plan(std::size_t arity) | calls push_back, std::to_string, variable_set, s04_runtime::lower_tree; returns s04_runtime::lower_tree(catalog, query, tree); growth push_back; 2 loop sites · [reviewed contract](#b0079) |
| [B0080 · 856–856](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L856) | Explanatory comments or spacing. |  |
| [B0081 · 857–919](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L857) | Callable definition: void exhaustive_family(const std::string& label, const PhysicalPlan& plan, const std::vector&lt;std::vector&lt;Row&gt;&gt;& domains) | calls check, size, resize, insert; guard check(domain.size() &lt; sizeof(std::size_t) * 8,; growth insert, resize; 8 loop sites; source comment (unverified): // For each binary relation state, toggle each domain row in fixed order. · [reviewed contract](#b0081) |
| [B0082 · 920–920](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L920) | Explanatory comments or spacing. |  |
| [B0083 · 921–941](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L921) | Callable definition: void exhaustive_binary_domain_toggles() | calls n, exhaustive_family, hidden_binary_plan, projected_path_plan; guard check(checked_exhaustive_transitions == 2504, · [reviewed contract](#b0083) |
| [B0084 · 942–942](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L942) | Explanatory comments or spacing. |  |
| [B0085 · 943–998](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L943) | Callable definition: void projection_collisions_noops_and_count_only() | calls make_runtime, hidden_projection_plan, resize, check_live; guard check(collision.records.empty(), "hidden z collision emitted projected x");; growth insert, resize · [reviewed contract](#b0085) |
| [B0086 · 999–999](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L999) | Explanatory comments or spacing. |  |
| [B0087 · 1000–1086](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1000) | Callable definition: void root_ancestor_deep_and_global_liveness() | calls make_runtime, root_pair_plan, n, seed_maintenance; guard check(deletion.records.size() == 1,; returns factor.empty(); growth insert · [reviewed contract](#b0087) |
| [B0088 · 1087–1087](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1087) | Explanatory comments or spacing. |  |
| [B0089 · 1088–1171](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1088) | Callable definition: void products_alias_prefixes_and_self_join() | calls make_runtime, product_plan, resize, apply_checked; guard check(last.records.size() == expected,; growth insert, resize; 3 loop sites · [reviewed contract](#b0089) |
| [B0090 · 1172–1172](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1172) | Explanatory comments or spacing. |  |
| [B0091 · 1173–1294](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1173) | Callable definition: void sql_mapping_predicates_and_exists() | calls make_runtime, sql_plan, resize, apply_checked; guard check(output.contains({n(10), n(1), n(10), n(7)}),; growth insert, resize; 2 loop sites · [reviewed contract](#b0091) |
| [B0092 · 1295–1295](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1295) | Explanatory comments or spacing. |  |
| [B0093 · 1296–1414](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1296) | Callable definition: void seeded_updates_and_modes_discard_readiness() | calls make_runtime, self_join_plan, apply_checked, n; guard check(empty_epoch.remaining() == 0 && !empty_epoch.active() && runtime.ready(),; growth insert; 2 loop sites · [reviewed contract](#b0093) |
| [B0094 · 1415–1417](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1415) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0094) |
| [B0095 · 1418–1446](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1418) | Callable definition: int main(int argc,char** argv) | calls std::string_view, check, projection_collisions_noops_and_count_only, root_ancestor_deep_and_global_liveness; guard else check(argc==1,"expected no argument, eager, incremental, anchored or root_first policy");; returns 1 · [reviewed contract](#b0095) |

## B0001

[Lines 1–35](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L35:sha256:d7dcfa60543e97a5f9cdd88b537bae1d92ab2aa258d906123c28abebbd77904c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_delta_runtime_test.cpp: include "indexed_runtime_fixture.hpp", "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "evaluator.hpp", "native_input.hpp", "statistics_acceptance.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;map&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 36–47](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime make_runtime(PhysicalPlan plan,DeltaOptions options={}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a DeltaRuntime with the suite-selected live/completion policy. |
| inputs / outputs | Takes PhysicalPlan and optional DeltaOptions by value; returns move-only runtime. |
| invariants | Overwrites the two policy fields from globals; under CROWN_STATISTICS_ACCEPTANCE also sets support order and enables acceptance hooks. It does not initialize a Database snapshot. |
| ownership | Plan and runtime own their metadata/state; option argument is local. |
| failure | Constructor validation/allocation errors propagate. |
| cost | Builds one runtime facade and optional acceptance instrumentation. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0003

[Lines 48–49](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L49:sha256:f69278d87eb40739c3945817a698db198d11c4e48d35c0a7a9e7226960b39157
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_delta_runtime_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 50–52](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one test predicate with its diagnostic. |
| inputs / outputs | Takes condition and borrowed string; returns on true. |
| invariants | Does not translate runtime errors. |
| ownership | Message borrowed for the call. |
| failure | False throws std::runtime_error. |
| cost | One branch. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0006

[Lines 54–64](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw one exact crown::Error code. |
| inputs / outputs | Forwards action and borrows expected code view; returns after matching Error. |
| invariants | Catches only crown::Error; other exception types propagate; wrong code fails through check. |
| ownership | Callable/code borrowed during invocation. |
| failure | No expected Error or code mismatch becomes test failure. |
| cost | One action invocation. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0008

[Lines 66–66](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an int64 fixture Value. |
| inputs / outputs | Takes signed integer; returns Value by value. |
| invariants | Preserves numeric value. |
| ownership | No external state retained. |
| failure | No custom failure handling. |
| cost | Scalar conversion. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0009

[Lines 67–67](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a string fixture Value. |
| inputs / outputs | Takes string by value; returns Value by value. |
| invariants | Preserves contents. |
| ownership | Returned scalar owns its string. |
| failure | Copy/allocation errors propagate. |
| cost | One scalar construction. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0011

[Lines 69–83](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string row_string(const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render fixture Row fields as a diagnostic string. |
| inputs / outputs | Takes borrowed Row; returns std::string. |
| invariants | Uses variant-specific formatting for string, bool, date, decimal and numeric values; adds parentheses and comma separators. |
| ownership | Input borrowed; output string owns bytes. |
| failure | Formatting/allocation failures propagate. |
| cost | Visits every field and formats each scalar. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0013

[Lines 85–93](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> exact_difference(const Relation& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute exact set-valued signed delta between before/after answers. |
| inputs / outputs | Takes two Relations by reference; returns set of operation/Row keys. |
| invariants | Rows present only after become insert; rows present only before become erase; common rows omitted. |
| ownership | Inputs borrowed; output set owns copied row values. |
| failure | Set allocation failures propagate. |
| cost | Scans both finite fixture relations. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0015

[Lines 95–102](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> record_set(const std::vector<SignedResult>& records) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export signed output records to a unique operation/row set. |
| inputs / outputs | Takes borrowed vector&lt;SignedResult&gt;; returns set&lt;SignedKey&gt;. |
| invariants | Fails on duplicate pairs and requires result cardinality equal input length. |
| ownership | Record tuples borrowed during copy; result owns exported rows. |
| failure | Duplicate is test failure; export/allocation errors propagate. |
| cost | Copies all vector records into an ordered set. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0017

[Lines 104–108](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variable_set(std::initializer_list<std::size_t> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a VariableSet from zero-based variable indices. |
| inputs / outputs | Takes initializer list; returns set of VariableId. |
| invariants | Uses set semantics, so repeated indices collapse. |
| ownership | Returned set owns IDs. |
| failure | Allocation failures propagate. |
| cost | Inserts each supplied index. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0019

[Lines 110–142](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree sql_tree(const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the indexed-fixture supplied tree for a normalized SQL core query. |
| inputs / outputs | Takes Query by const reference; returns FreeConnexTree. |
| invariants | Contradiction/no atoms returns empty tree; one atom gets one native node; multiple atoms use a generalized root on the intersection of all atom scopes with one native child per occurrence. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Query borrowed; tree owns copied node/scoping metadata. |
| failure | Allocation/tree construction failures propagate. |
| cost | Scans atom terms, computes scope intersections and constructs finite tree metadata. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0021

[Lines 144–155](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan sql_plan(std::string_view sql, const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize fixture SQL, then lower using the indexed fixture backend, then lower the helper tree. |
| inputs / outputs | Borrows SQL view and Catalog; returns PhysicalPlan. |
| invariants | Binding/normalization diagnostics become runtime_error with code/message; lower_normalized uses sql_tree over normalized core. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | SQL/catalog borrowed during helper; plan owns lowered metadata. |
| failure | Diagnostics or lowering failures propagate. |
| cost | Runs bind, normalize, tree construction and one lowering call. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0023

[Lines 157–172](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04_core(const auto& plan, const Database& physical) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute expected normalized core answer using the independent A04 evaluator. |
| inputs / outputs | Takes plan/database by const reference; returns Relation. |
| invariants | Classic plans evaluate directly; normalized plans adapt physical rows into logical core tables before A04 evaluation. |
| ownership | Inputs borrowed; logical snapshot and returned relation own rows. |
| failure | Frontend/reference/allocation errors propagate. |
| cost | Adapts finite source rows and materializes one independent answer. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0025

[Lines 174–179](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04_output(const auto& plan, const Database& physical) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map independent core answer through normalized SQL output fields when applicable. |
| inputs / outputs | Takes plan/database by const reference; returns Relation. |
| invariants | Classic plan returns core answer; normalized plan maps through SQL result projection, repeated/reordered fields and constants. |
| ownership | Inputs borrowed; returned set owns output rows. |
| failure | Reference/SQL mapping errors propagate. |
| cost | Calls a04_core then optionally maps the finite answer. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0027

[Lines 181–206](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> project_core_to_live_scopes(const auto& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project A04 core answers into every maintained visible factor scope. |
| inputs / outputs | Takes plan/core Relation by const reference; returns Relation vector. |
| invariants | Uses first head position for a variable and emits one set factor per enumeration step. |
| ownership | Inputs borrowed; output factor relations own projected keys. |
| failure | Missing head field or index error throws; allocation failures propagate. |
| cost | Visits every answer for every factor scope. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0029

[Lines 208–221](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_live(const DeltaRuntime& runtime, const Database& physical,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the runtime L snapshot to independent A04 projections. |
| inputs / outputs | Takes DeltaRuntime/database by reference and label; returns void. |
| invariants | Maintenance requires no live snapshot; delta requires matching sequence and factors projected by project_core_to_live_scopes. This helper itself does not call check_invariants. |
| ownership | Runtime/database borrowed; snapshot and expected projections local. |
| failure | Missing/stale/different L fails through check. |
| cost | Materializes one live snapshot and scans the finite A04 result. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0031

[Lines 223–227](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L223); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OracleRoute {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold one physical-base to occurrence-target route and occurrence-specific shadow relation. |
| inputs / outputs | Aggregate stores base/target TableIds and Relation. |
| invariants | Used by PrefixOracle to split one physical table into occurrence-specific independent input tables. |
| ownership | Owns copied relation rows. |
| failure | No custom behavior. |
| cost | Plain oracle route data. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0032

[Lines 228–232](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L228); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L228-L232:sha256:b5a2316c00c668ec8b5d98230204015fac3b995307199745b19acddcbb5cc3ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_delta_runtime_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0033

[Lines 233–267](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an occurrence-expanded independent evaluator around a plan and physical snapshot. |
| inputs / outputs | Constructor takes plan/database by const reference; initializes owned Catalog, Query, Database and route vector. |
| invariants | For classic tree plans it copies each occurrence base into a separate table and rewrites that query atom; normalized plans route each adapter to a logical core table and adapt rows; non-tree normalized route returns without occurrence routes. This is a test oracle, not D03 runtime logic. |
| ownership | Plan borrowed by reference; catalog/query/database/routes owned by PrefixOracle. |
| failure | Adapter/index/allocation failures propagate. |
| cost | Copies finite input tables per occurrence and builds logical route shadows. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0035

[Lines 269–271](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] Relation core() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the occurrence-expanded prefix query with A04. |
| inputs / outputs | No args; returns Relation. |
| invariants | Uses copied catalog/query/database and no DeltaRuntime state. |
| ownership | Returned relation owns rows. |
| failure | A04 errors propagate. |
| cost | One complete finite materialization. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0037

[Lines 273–278](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] Relation output() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate a prefix core relation and map it to SQL output when normalized. |
| inputs / outputs | No args; returns Relation. |
| invariants | Classic prefix returns core; normalized prefix applies the plan’s SQL result mapping. |
| ownership | Returned Relation owns rows; PrefixOracle retains its snapshot. |
| failure | Mapping/A04 errors propagate. |
| cost | Runs core() then optional map. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0039

[Lines 280–293](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void apply(OccurrenceId occurrence, const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical update to a selected occurrence’s independent source shadow. |
| inputs / outputs | Takes occurrence and update by reference; returns void. |
| invariants | Requires route base equal update.table; insert must add and erase must remove exactly one row; normalized route rebuilds adapted table, classic route copies shadow to target table. |
| ownership | Update borrowed; route shadow and copied database owned by oracle. |
| failure | Wrong route/duplicate insert/absent erase fails through check; access/allocation failures propagate. |
| cost | One set mutation and, for normalized input, one full route shadow remap. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0041

[Lines 295–304](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 private:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild one normalized occurrence’s logical target relation from its physical shadow. |
| inputs / outputs | Takes occurrence; returns void. |
| invariants | Adapts each route shadow row and replaces the target table relation with mapped rows. |
| ownership | Program borrowed via retained plan; replacement Relation owns rows. |
| failure | Adapter/allocation errors propagate. |
| cost | Scans one occurrence’s finite shadow rows. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0042

[Lines 305–313](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L305); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L305-L313:sha256:4e937e5940719c56896b4274836774d424ae67ee6d1837b1c613ee967ebe10a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_delta_runtime_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0043

[Lines 314–321](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L314); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ActualEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle actual output records, stage summaries, work metrics, input audit and changed flag. |
| inputs / outputs | Aggregate owns its vectors/metrics/boolean. |
| invariants | Filled by drain_epoch/apply_checked after successful commit. |
| ownership | Records and derivation values own copies/moved tuples. |
| failure | No custom failure path. |
| cost | Plain result bundle; vectors scale with one fixture epoch. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0045

[Lines 323–340](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain_current(SupportRuntime::ResultCursor& cursor,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a current SupportRuntime cursor and verify row layout/type/uniqueness. |
| inputs / outputs | Takes lvalue cursor and label by reference; returns Relation. |
| invariants | Checks token, arity, scalar type, no duplicate set rows, exhausted state and released lease. |
| ownership | Cursor borrowed and consumed; Relation owns exported rows. |
| failure | Mismatch throws runtime_error; cursor errors propagate. |
| cost | Reads and copies all current result tuples. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0047

[Lines 342–352](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_current(const DeltaRuntime& runtime, const Database& physical,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare current core and public answer cursors with A04. |
| inputs / outputs | Takes runtime/database by reference; returns void. |
| invariants | Drains core cursor against a04_core and output cursor against a04_output. |
| ownership | Runtime/database borrowed; cursors and expected relations local. |
| failure | Mismatch throws runtime_error. |
| cost | Materializes and drains both finite current views. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0049

[Lines 354–389](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L354); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ActualEpoch drain_epoch(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a committed DeltaRuntime epoch and check its signed spool against A04. |
| inputs / outputs | Takes runtime/epoch by reference, expected signed set and label; returns ActualEpoch. |
| invariants | Validates output layout, count, active/readiness lease state, contiguous one-based ordinals, typed tuples, exact unique signed rows; exhausting output must restore runtime.ready and no further record exists. |
| ownership | Epoch/runtime borrowed; returned records are moved into owned vector. |
| failure | Any mismatch fails via check; API errors propagate. |
| cost | Drains all expected records and copies stage/metric data later through caller. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0051

[Lines 391–650](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L391); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ActualEpoch apply_checked(DeltaRuntime& runtime, Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical event and reconcile its stage/output/live metrics with independent A04 prefix oracles. |
| inputs / outputs | Takes runtime/database/update by reference plus label/trace flag; returns ActualEpoch. |
| invariants | Checks contiguous sequence, physical change audit/derivation count, occurrence-expanded prefix answers and each native crossing; count-only routes have no stage; EXISTS output is emitted outside route intervals; raw spool equals exact A04 before/after difference; final physical/core/output/live/invariants match; anchored/replay/non-eager metric identities are checked. This is a successful-update acceptance helper, not a fault-injection test. |
| ownership | Runtime/database caller-owned; copy of after DB, PrefixOracle, cursors, stages and return object local; database advances only after committed epoch output is drained. |
| failure | Runtime/check failures propagate; no bad_alloc or malloc/system/account failure is deliberately injected. |
| cost | Per event builds multiple finite A04 prefix answers, drains complete output and checks all instrumentation; no CPU-time claim. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § One physical input](../../../../delta_runtime.md), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0053

[Lines 652–669](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L652); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seed_maintenance(DeltaRuntime& runtime, const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed an empty maintenance runtime through accepted physical inserts, then bootstrap delta mode. |
| inputs / outputs | Takes runtime/database and label by const reference; returns void. |
| invariants | Each seed consumes contiguous sequence and must produce no output; after all rows, runtime physical snapshot equals database, mode switch builds L, and check_live matches A04. |
| ownership | Runtime is caller-owned; database borrowed; seed epochs are local. |
| failure | Unexpected output or runtime error fails. |
| cost | Applies one maintenance epoch per source row plus one full L bootstrap. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0055

[Lines 671–682](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L671); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan hidden_projection_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture a native plan whose input scope (x,z) projects only x. |
| inputs / outputs | No args; returns PhysicalPlan. |
| invariants | Table also contains ignored payload; hidden z remains in E but not answer head. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns lowered metadata. |
| failure | Lowering/allocation failures propagate. |
| cost | Constructs and lowers one fixed tree. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0057

[Lines 684–693](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L684); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan hidden_binary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture a one-table binary plan with hidden z and projected x. |
| inputs / outputs | No args; returns plan. |
| invariants | Native key is (x,z); query result exposes x, enabling projection-collision/no-op cases. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Returned plan owns metadata. |
| failure | Lowering failures propagate. |
| cost | One fixed lowering operation. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0059

[Lines 695–704](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L695); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan root_pair_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture a one-table plan exposing root pair (x,y). |
| inputs / outputs | No args; returns PhysicalPlan. |
| invariants | Native scope and output head are both {x,y}. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed tree lowering. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0061

[Lines 706–718](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L706); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan ancestor_child_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture parent r(x) -&gt; child s(x,y) and expose both variables. |
| inputs / outputs | No args; returns plan. |
| invariants | Tree has one ancestor/child edge with separator x. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns lowered values. |
| failure | Lowering errors propagate. |
| cost | Constructs two tables and one tree then lowers. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0063

[Lines 720–736](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L720); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan deep_chain_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture a three-factor path with hidden final variable w. |
| inputs / outputs | No args; returns plan. |
| invariants | r(x,y)-&gt;s(y,z)-&gt;t(z,w); output head is x,y,z, omitting w. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed tree build/lower. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0065

[Lines 738–750](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L738); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan root_child_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture the two-factor root/child plan used for liveness activation. |
| inputs / outputs | No args; returns plan. |
| invariants | Root is r(x); child is s(x,y); head exposes x,y. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed lowering operation. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0067

[Lines 752–764](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L752); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_path_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture a root/child plan that projects only root variable x. |
| inputs / outputs | No args; returns plan. |
| invariants | Child E key y is hidden in query output, so child membership can change without answer change. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed lowering operation. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0069

[Lines 766–779](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L766); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan hidden_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture path R(x,z)-&gt;S(z,y) exposing only x. |
| inputs / outputs | No args; returns plan. |
| invariants | Separator z and child y are hidden from head. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed lowering. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0071

[Lines 781–788](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L781); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan boolean_unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture a Boolean query over unary relation r(x). |
| inputs / outputs | No args; returns plan with empty head. |
| invariants | Answer is nullary truth iff source has a row. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed lowering. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0073

[Lines 790–803](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L790); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shared_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture R(a,x)-&gt;S(x,z) with all variables projected. |
| inputs / outputs | No args; returns plan. |
| invariants | Child separator x can have multiple live parents; head is a,x,z. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed lowering. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0075

[Lines 805–819](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L805); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan self_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture a two-occurrence self-join of edge(src,dst,payload). |
| inputs / outputs | No args; returns plan. |
| invariants | Left maps x,y; right maps y,z; ignored payload; generalized join scope y; output order x,z,y. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed tree lowering. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0077

[Lines 821–833](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L821); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan same_scope_alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture two aliases over the same full edge scope and table. |
| inputs / outputs | No args; returns plan. |
| invariants | Generalized root joins two native occurrences on both x,y; duplicate route ownership is tested separately. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed tree lowering. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0079

[Lines 835–855](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L835); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan product_plan(std::size_t arity) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the indexed-fixture an arity-factor disconnected product plan. |
| inputs / outputs | Takes arity; returns plan. |
| invariants | One unary table/atom per variable and a generalized nullary root over every native child. In this twin the fixture selector supplies the indexed storage backend; this card does not claim native backend execution. |
| ownership | Returned catalog/query/tree are moved into owned plan. |
| failure | Allocation/lowering errors propagate. |
| cost | Builds metadata proportional to requested arity and lowers once. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0081

[Lines 857–919](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L857); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaustive_family(const std::string& label, const PhysicalPlan& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate every fixture relation state and each directed one-row toggle for a plan family. |
| inputs / outputs | Takes label, plan and finite per-table row domains by reference; returns void. |
| invariants | For each bitmask state it seeds a maintenance runtime, switches to delta, and toggles every domain row once; state masks plus fixed-prefix XOR cover every state/toggle pair for these domains. Counts are test-local. Plans in this twin pass through the indexed fixture selector; no execution is claimed here. |
| ownership | Plan/domains borrowed; each runtime/database/seed epoch local. |
| failure | Oversized domain-mask check or any state/update mismatch throws runtime_error. |
| cost | Runs product of per-table 2^domain sizes states, with one fresh runtime per state and all domain toggles; no broad complexity claim. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0083

[Lines 921–941](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L921); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaustive_binary_domain_toggles() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run exhaustive finite-state toggle families for hidden, projected path, hidden separator and Boolean fixtures. |
| inputs / outputs | No args; returns after four exhaustive_family calls. |
| invariants | Checks cumulative directed-toggle count exactly 2,504. This is a finite fixture inventory, not every possible query or database. Plans in this twin pass through the indexed fixture selector; no execution is claimed here. |
| ownership | Domain rows and plans local. |
| failure | Count or per-toggle mismatch fails. |
| cost | Runs 2,504 checked transitions plus repeated bootstrap per finite state. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0085

[Lines 943–998](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L943); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void projection_collisions_noops_and_count_only() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise hidden-key collisions, count-only derivations, final projected witness crossings and physical no-ops. |
| inputs / outputs | No args; creates runtime and source database, returns after nine updates. |
| invariants | Checks hidden z/payload changes do not alter x output until final witness removed; count-only changes have no DeltaStage; insert/delete of final witness emits exactly one signed x; duplicate insert and absent erase emit none but advance sequence. Plans in this twin pass through the indexed fixture selector; no execution is claimed here. |
| ownership | Runtime owns state; local database follows each committed input. |
| failure | Any state/output/sequence mismatch fails. |
| cost | Nine event preparations plus A04 before/after/live comparisons. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § One physical input](../../../../delta_runtime.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0087

[Lines 1000–1086](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1000); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void root_ancestor_deep_and_global_liveness() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise empty-separator root changes, ancestor/deep liveness, dead keys and shared-parent support. |
| inputs / outputs | No args; executes five independent fixture scopes. |
| invariants | Asserts exact A04 signed rows and L snapshots for root key changes, parent-child deletion, descendant activation under unchanged root, dead child E excluded until root activation, and child L retained until last parent disappears. Plans in this twin pass through the indexed fixture selector; no execution is claimed here. |
| ownership | Each nested runtime/database local; live snapshots are copies. |
| failure | Mismatch throws runtime_error. |
| cost | Five small finite runtimes and their event/A04 checks. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/incremental_live.md § Maintained state](../../../../incremental_live.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0089

[Lines 1088–1171](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1088); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void products_alias_prefixes_and_self_join() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise disconnected products, same-scope aliases and self-join prefix ownership. |
| inputs / outputs | No args; runs arity 3/8 product plus two alias/join fixtures. |
| invariants | Last product child emits 2^(arity-1) combinations; aliases emit once at completing route prefix; self-join loop insertion/deletion matches explicit three-row signed set and 1+2/2+1 stage counts. Plans in this twin pass through the indexed fixture selector; no execution is claimed here. |
| ownership | Runtimes/database/stage records local owning values. |
| failure | Output/stage mismatch fails. |
| cost | Finite product inserts plus full event checks; output grows with fixture product. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0091

[Lines 1173–1294](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sql_mapping_predicates_and_exists() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise normalized SQL result mapping, predicate aliases, scalar EXISTS and constant/source-free routes. |
| inputs / outputs | No args; binds/lower several SQL plans and applies events. |
| invariants | A04 oracle checks reordered/repeated/constants; filtered alias keeps physical route ordinal; EXISTS flips Boolean row pair and suppresses per-route spool counts; second witness count-only; constants and contradiction cases emit no source-event delta. Plans in this twin pass through the indexed fixture selector; no execution is claimed here. |
| ownership | SQL programs/plans/runtimes local owning values. |
| failure | Bind/normalize/runtime errors propagate; mismatch fails. |
| cost | Several fixed small plans and events with independent A04 materializations. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0093

[Lines 1296–1414](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seeded_updates_and_modes_discard_readiness() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise seeded self-join updates, empty epochs, mode bootstrap, discard commit semantics and read leases. |
| inputs / outputs | No args; two deterministic LCG seeds each drive 72 updates, then four explicit scopes. |
| invariants | Duplicate/absent physical updates still consume sequence; maintenance produces no L/output then delta rebootstrap scans current E; discarding committed output leaves source committed; result cursor lease blocks new writer until canceled; empty epoch has no lease. Plans in this twin pass through the indexed fixture selector; no execution is claimed here. |
| ownership | Runtime owns physical/support/L state; local db mirrors committed rows; epoch/cursor own delivery/read leases. |
| failure | Expected runtime_busy is matched exactly; other mismatches fail. No allocation fault is injected. |
| cost | 144 seeded events plus fixed mode/lease scenarios; deterministic work counters are not wall-clock limits. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |

## B0094

[Lines 1415–1417](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1415); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1415-L1417:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_delta_runtime_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0095

[Lines 1418–1446](../../../../../tests/unit/indexed_delta_runtime_test.cpp#L1418); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select optional live/completion policy and run the D04 acceptance fixtures. |
| inputs / outputs | Reads argc/argv and returns 0/1. |
| invariants | Accepts no argument or one of eager, incremental, anchored, root_first; selected values affect later make_runtime calls. Runs fixed scenarios and optionally emits statistics acceptance. Printing PASS occurs only if run returns; this contract does not claim execution. |
| ownership | All scenario data/runtime local to called functions. |
| failure | Invalid args fail through check; caught std::exception reports and returns 1. |
| cost | Calls five fixture groups once, including 2,504 exhaustive toggles. |
| Design | [tests/unit/indexed_delta_runtime_test.cpp](../../../../../tests/unit/indexed_delta_runtime_test.cpp), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [tests/support/indexed_runtime_fixture.hpp](../../../../../tests/support/indexed_runtime_fixture.hpp) |
