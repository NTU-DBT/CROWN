# `tests/unit/delta_anchor_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_anchor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `13af4a0a5396c8e5f6e77aa6757e2f51ebdf1a8bf0259a878d9d518fad86fc63`. 628 lines partitioned into 70 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/unit/delta_anchor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../tests/unit/delta_anchor_test.cpp#L24) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../tests/unit/delta_anchor_test.cpp#L27) | Explanatory comments or spacing. |  |
| [B0004 · 28–28](../../../../../tests/unit/delta_anchor_test.cpp#L28) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/unit/delta_anchor_test.cpp#L29) | Explanatory comments or spacing. |  |
| [B0006 · 30–34](../../../../../tests/unit/delta_anchor_test.cpp#L30) | Callable definition: VariableSet variables(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 35–35](../../../../../tests/unit/delta_anchor_test.cpp#L35) | Explanatory comments or spacing. |  |
| [B0008 · 36–41](../../../../../tests/unit/delta_anchor_test.cpp#L36) | Callable definition: DeltaOptions options(DeltaCompletion completion) | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 42–42](../../../../../tests/unit/delta_anchor_test.cpp#L42) | Explanatory comments or spacing. |  |
| [B0010 · 43–45](../../../../../tests/unit/delta_anchor_test.cpp#L43) | Callable definition: Relation a04(const auto& plan, const Database& database) | calls reference::evaluate, reference::input::catalog, catalog, reference::input::query; returns reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()… · [reviewed contract](#b0010) |
| [B0011 · 46–46](../../../../../tests/unit/delta_anchor_test.cpp#L46) | Explanatory comments or spacing. |  |
| [B0012 · 47–54](../../../../../tests/unit/delta_anchor_test.cpp#L47) | Callable definition: std::set&lt;SignedKey&gt; difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 55–55](../../../../../tests/unit/delta_anchor_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0014 · 56–81](../../../../../tests/unit/delta_anchor_test.cpp#L56) | Callable definition: std::vector&lt;Relation&gt; a04_live(const auto& plan, const Relation& answer) | calls query, size, try_emplace, reserve; guard check(position != head_positions.end(),; returns result; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0014) |
| [B0015 · 82–82](../../../../../tests/unit/delta_anchor_test.cpp#L82) | Explanatory comments or spacing. |  |
| [B0016 · 83–95](../../../../../tests/unit/delta_anchor_test.cpp#L83) | Callable definition: void check_layout(const storage::TupleLayout& layout, const auto& variables_in_order, const std::string& label) | calls fields, check, size; guard check(fields.size() == variables_in_order.size(),; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 96–96](../../../../../tests/unit/delta_anchor_test.cpp#L96) | Explanatory comments or spacing. |  |
| [B0018 · 97–116](../../../../../tests/unit/delta_anchor_test.cpp#L97) | Callable definition: Relation drain_current(SupportRuntime::ResultCursor& cursor, const std::string& label) | calls layout, next, check, same_token; guard check(tuple-&gt;layout().same_token(layout),; returns result; growth insert; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 117–117](../../../../../tests/unit/delta_anchor_test.cpp#L117) | Explanatory comments or spacing. |  |
| [B0020 · 118–141](../../../../../tests/unit/delta_anchor_test.cpp#L118) | Callable definition: void check_current_and_live(const DeltaRuntime& runtime, const Database& database, const std::vector&lt;VariableId&gt;& head_order, con… | calls a04, plan, core_results, check_layout; guard check(drain_current(core, label + " core") == expected, · [reviewed contract](#b0020) |
| [B0021 · 142–142](../../../../../tests/unit/delta_anchor_test.cpp#L142) | Explanatory comments or spacing. |  |
| [B0022 · 143–147](../../../../../tests/unit/delta_anchor_test.cpp#L143) | Type/record definition: struct EventResult |  · [reviewed contract](#b0022) |
| [B0023 · 148–148](../../../../../tests/unit/delta_anchor_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0024 · 149–192](../../../../../tests/unit/delta_anchor_test.cpp#L149) | Callable definition: EventResult drain_event(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch, const std::set&lt;SignedKey&gt;& expected, const std::vector… | calls check_layout, layout, check, same_token; guard check(epoch.layout().same_token(runtime.result_layout()),; returns result; growth insert, push_back; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 193–193](../../../../../tests/unit/delta_anchor_test.cpp#L193) | Explanatory comments or spacing. |  |
| [B0026 · 194–201](../../../../../tests/unit/delta_anchor_test.cpp#L194) | Callable definition: void drain_empty_maintenance(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch, const std::string& label) | calls check, remaining, active, next; guard check(epoch.remaining() == 0 && !epoch.active(), · [reviewed contract](#b0026) |
| [B0027 · 202–203](../../../../../tests/unit/delta_anchor_test.cpp#L202) | declares types or opens a type body. |  · [reviewed contract](#b0027) |
| [B0028 · 204–209](../../../../../tests/unit/delta_anchor_test.cpp#L204) | Callable definition: public: Pair(PhysicalPlan plan, std::size_t table_count) : anchored_(plan, options(DeltaCompletion::anchored)), root_first_(std::… | calls anchored_, options, root_first_, std::move; growth resize · [reviewed contract](#b0028) |
| [B0029 · 210–210](../../../../../tests/unit/delta_anchor_test.cpp#L210) | Explanatory comments or spacing. |  |
| [B0030 · 211–230](../../../../../tests/unit/delta_anchor_test.cpp#L211) | Callable definition: void seed(TableId table, Row row, const std::string& label) | calls apply, check, sequence, drain_empty_maintenance; guard check(anchored_epoch.sequence() == sequence &&; growth insert · [reviewed contract](#b0030) |
| [B0031 · 231–231](../../../../../tests/unit/delta_anchor_test.cpp#L231) | Explanatory comments or spacing. |  |
| [B0032 · 232–240](../../../../../tests/unit/delta_anchor_test.cpp#L232) | Callable definition: void bootstrap(const std::vector&lt;VariableId&gt;& head_order, const std::string& label) | calls set_mode, check_current_and_live · [reviewed contract](#b0032) |
| [B0033 · 241–241](../../../../../tests/unit/delta_anchor_test.cpp#L241) | Explanatory comments or spacing. |  |
| [B0034 · 242–252](../../../../../tests/unit/delta_anchor_test.cpp#L242) | Callable definition: void maintenance(const std::vector&lt;VariableId&gt;& head_order, const std::string& label) | calls set_mode, check, live_snapshot, check_current_and_maintenance; guard check(!anchored_.live_snapshot() && !root_first_.live_snapshot(), · [reviewed contract](#b0034) |
| [B0035 · 253–253](../../../../../tests/unit/delta_anchor_test.cpp#L253) | Explanatory comments or spacing. |  |
| [B0036 · 254–285](../../../../../tests/unit/delta_anchor_test.cpp#L254) | Callable definition: std::pair&lt;EventResult, EventResult&gt; apply( TableId table, SetOperation operation, Row row, const std::vector&lt;VariableId&gt;& head_or… | calls a04, plan, at, insert; guard check(changed, label + ": fixture update did not change physical membership");; returns {std::move(anchored_result), std::move(root_first_result)}; growth insert · [reviewed contract](#b0036) |
| [B0037 · 286–286](../../../../../tests/unit/delta_anchor_test.cpp#L286) | Explanatory comments or spacing. |  |
| [B0038 · 287–287](../../../../../tests/unit/delta_anchor_test.cpp#L287) | Callable definition: \[\[nodiscard\]\] const Database& database() const | calls ; returns database_ · [reviewed contract](#b0038) |
| [B0039 · 288–288](../../../../../tests/unit/delta_anchor_test.cpp#L288) | Callable definition: \[\[nodiscard\]\] const DeltaRuntime& anchored() const | calls ; returns anchored_ · [reviewed contract](#b0039) |
| [B0040 · 289–289](../../../../../tests/unit/delta_anchor_test.cpp#L289) | Callable definition: \[\[nodiscard\]\] const DeltaRuntime& root_first() const | calls ; returns root_first_ · [reviewed contract](#b0040) |
| [B0041 · 290–290](../../../../../tests/unit/delta_anchor_test.cpp#L290) | Explanatory comments or spacing. |  |
| [B0042 · 291–305](../../../../../tests/unit/delta_anchor_test.cpp#L291) | Callable definition: private: static void check_current_and_maintenance( const DeltaRuntime& runtime, const Database& database, const std::vector&lt;Vari… | calls a04, plan, core_results, check_layout; guard check(drain_current(core, label + " core") == expected, · [reviewed contract](#b0042) |
| [B0043 · 306–312](../../../../../tests/unit/delta_anchor_test.cpp#L306) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0043) |
| [B0044 · 313–328](../../../../../tests/unit/delta_anchor_test.cpp#L313) | Callable definition: PhysicalPlan diagnostic_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0044) |
| [B0045 · 329–329](../../../../../tests/unit/delta_anchor_test.cpp#L329) | Explanatory comments or spacing. |  |
| [B0046 · 330–335](../../../../../tests/unit/delta_anchor_test.cpp#L330) | Type/record definition: struct DiagnosticMetrics |  · [reviewed contract](#b0046) |
| [B0047 · 336–336](../../../../../tests/unit/delta_anchor_test.cpp#L336) | Explanatory comments or spacing. |  |
| [B0048 · 337–378](../../../../../tests/unit/delta_anchor_test.cpp#L337) | Callable definition: DiagnosticMetrics diagnostic_run(std::size_t count) | calls pair, diagnostic_plan, n, seed; guard check(a04(pair.anchored().plan(), pair.database()).size() == count,; returns {inserted_anchor.metrics, inserted_root.metrics,; growth insert; 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 379–382](../../../../../tests/unit/delta_anchor_test.cpp#L379) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0049) |
| [B0050 · 383–387](../../../../../tests/unit/delta_anchor_test.cpp#L383) | Callable definition: CursorWork cursor_work(const DeltaMetrics& metrics) | calls ; returns {metrics.cursor_startup_work, metrics.cursor_results_work, · [reviewed contract](#b0050) |
| [B0051 · 388–388](../../../../../tests/unit/delta_anchor_test.cpp#L388) | Explanatory comments or spacing. |  |
| [B0052 · 389–416](../../../../../tests/unit/delta_anchor_test.cpp#L389) | Callable definition: void anchored_completion_scales_with_changed_witness() | calls diagnostic_run, check, cursor_work; guard check(cursor_work(one.anchored_insert) == cursor_work(many.anchored_insert) &&; 1 loop sites · [reviewed contract](#b0052) |
| [B0053 · 417–417](../../../../../tests/unit/delta_anchor_test.cpp#L417) | Explanatory comments or spacing. |  |
| [B0054 · 418–442](../../../../../tests/unit/delta_anchor_test.cpp#L418) | Callable definition: PhysicalPlan deep_sibling_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0054) |
| [B0055 · 443–443](../../../../../tests/unit/delta_anchor_test.cpp#L443) | Explanatory comments or spacing. |  |
| [B0056 · 444–456](../../../../../tests/unit/delta_anchor_test.cpp#L444) | Callable definition: std::size_t path_depth_to_root(const auto& plan, NodeId node) | calls enumeration, std::find_if, begin, end; guard check(position != steps.end(), "deep fixture omitted its changed witness step");; returns step.node == node; depth; 1 loop sites · [reviewed contract](#b0056) |
| [B0057 · 457–457](../../../../../tests/unit/delta_anchor_test.cpp#L457) | Explanatory comments or spacing. |  |
| [B0058 · 458–505](../../../../../tests/unit/delta_anchor_test.cpp#L458) | Callable definition: void reverse_path_deletion_and_sibling_products() | calls deep_sibling_plan, check, path_depth_to_root, pair; guard check(path_depth_to_root(plan, NodeId{2}) &gt;= 2,; growth emplace, insert; 2 loop sites · [reviewed contract](#b0058) |
| [B0059 · 506–506](../../../../../tests/unit/delta_anchor_test.cpp#L506) | Explanatory comments or spacing. |  |
| [B0060 · 507–521](../../../../../tests/unit/delta_anchor_test.cpp#L507) | Callable definition: PhysicalPlan nullary_separator_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0060) |
| [B0061 · 522–522](../../../../../tests/unit/delta_anchor_test.cpp#L522) | Explanatory comments or spacing. |  |
| [B0062 · 523–562](../../../../../tests/unit/delta_anchor_test.cpp#L523) | Callable definition: void nullary_separator_and_product() | calls pair, nullary_separator_plan, seed, n; guard check(a04(pair.anchored().plan(), pair.database()).empty(),; returns step.node == NodeId{0}; growth insert · [reviewed contract](#b0062) |
| [B0063 · 563–563](../../../../../tests/unit/delta_anchor_test.cpp#L563) | Explanatory comments or spacing. |  |
| [B0064 · 564–578](../../../../../tests/unit/delta_anchor_test.cpp#L564) | Callable definition: PhysicalPlan alias_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0064) |
| [B0065 · 579–579](../../../../../tests/unit/delta_anchor_test.cpp#L579) | Explanatory comments or spacing. |  |
| [B0066 · 580–591](../../../../../tests/unit/delta_anchor_test.cpp#L580) | Callable definition: void check_alias_stage_ownership(const std::pair&lt;EventResult, EventResult&gt;& event, std::size_t first_count, std::size_t second_co… | calls check, size; guard check(result-&gt;stages.size() == 2,; 1 loop sites · [reviewed contract](#b0066) |
| [B0067 · 592–592](../../../../../tests/unit/delta_anchor_test.cpp#L592) | Explanatory comments or spacing. |  |
| [B0068 · 593–613](../../../../../tests/unit/delta_anchor_test.cpp#L593) | Callable definition: void alias_stage_isolation_and_rebootstrap() | calls pair, alias_plan, seed, n; growth insert · [reviewed contract](#b0068) |
| [B0069 · 614–616](../../../../../tests/unit/delta_anchor_test.cpp#L614) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0069) |
| [B0070 · 617–628](../../../../../tests/unit/delta_anchor_test.cpp#L617) | Callable definition: int main() | calls anchored_completion_scales_with_changed_witness, reverse_path_deletion_and_sibling_products, nullary_separator_and_product, alias_stage_isolation_and_rebootstrap; returns 1 · [reviewed contract](#b0070) |

## B0001

[Lines 1–23](../../../../../tests/unit/delta_anchor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:5b2faa600f2d74bf464d561a5de23ac2df865b6b0dd71564d5fe41fda8c3092f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_anchor_test.cpp: include "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "evaluator.hpp", "native_input.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;initializer_list&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–26](../../../../../tests/unit/delta_anchor_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an anchored-completion fixture assertion. |
| inputs / outputs | Takes condition and diagnostic by const reference; returns on true. |
| invariants | Does not catch runtime exceptions. |
| ownership | Message borrowed for the call. |
| failure | False throws std::runtime_error. |
| cost | One conditional branch. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0004

[Lines 28–28](../../../../../tests/unit/delta_anchor_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 fixture Value. |
| inputs / outputs | Takes signed integer; returns Value by value. |
| invariants | Preserves value. |
| ownership | No external state retained. |
| failure | Variant errors propagate. |
| cost | Scalar conversion. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0006

[Lines 30–34](../../../../../tests/unit/delta_anchor_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variables(std::initializer_list<std::size_t> values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a VariableSet from zero-based indices. |
| inputs / outputs | Takes initializer list; returns set of VariableId. |
| invariants | Repeated indices collapse. |
| ownership | Returned set owns IDs. |
| failure | Allocation failures propagate. |
| cost | One insertion per supplied index. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0008

[Lines 36–41](../../../../../tests/unit/delta_anchor_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(DeltaCompletion completion) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure maintenance-first options for anchored or root-first completion. |
| inputs / outputs | Takes completion enum; returns DeltaOptions. |
| invariants | Mode is maintenance, live maintenance is on_output, and only completion strategy varies. |
| ownership | Options own scalar settings. |
| failure | Option/enum errors propagate later through runtime construction or mode transition. |
| cost | Constant-size setup. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0010

[Lines 43–45](../../../../../tests/unit/delta_anchor_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04(const auto& plan, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate a plan with the independent A04 reference evaluator. |
| inputs / outputs | Takes plan/database by const reference; returns Relation. |
| invariants | Does not use the runtime answer as its oracle. |
| ownership | Inputs borrowed; returned set owns rows. |
| failure | Evaluator/allocation exceptions propagate. |
| cost | One finite A04 materialization. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0012

[Lines 47–54](../../../../../tests/unit/delta_anchor_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> difference(const Relation& before, const Relation& after) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute signed set difference between two answer relations. |
| inputs / outputs | Takes before/after by const reference; returns set of operation/row pairs. |
| invariants | Only after-only inserts and before-only erases are retained. |
| ownership | Input relations borrowed; output copies rows. |
| failure | Allocation failures propagate. |
| cost | Scans both finite relations. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0014

[Lines 56–81](../../../../../tests/unit/delta_anchor_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> a04_live(const auto& plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an A04 answer into visible-scope L factors. |
| inputs / outputs | Takes plan/answer by const reference; returns factor vector. |
| invariants | Uses first matching head position; each enumeration-step scope projects answer assignments into set-valued rows. |
| ownership | Inputs borrowed; output factors own keys. |
| failure | Missing head variable/index or allocation failure propagates. |
| cost | Visits each answer for every factor. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/incremental_live.md § Maintained state](../../../../incremental_live.md) |

## B0016

[Lines 83–95](../../../../../tests/unit/delta_anchor_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_layout(const storage::TupleLayout& layout,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check output tuple layout field count and names against expected variable order. |
| inputs / outputs | Takes TupleLayout and expected variable sequence by const reference plus label; returns void. |
| invariants | Asserts exact field count and each ordinal name. |
| ownership | Layout and expected order borrowed. |
| failure | Mismatch fails through check. |
| cost | One comparison per expected field. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0018

[Lines 97–116](../../../../../tests/unit/delta_anchor_test.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain_current(SupportRuntime::ResultCursor& cursor,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a current-result cursor into an owning relation. |
| inputs / outputs | Takes ResultCursor by mutable reference and label; returns Relation. |
| invariants | Exports tuple values, deduplicates as Relation, then requires cursor exhausted and inactive. |
| ownership | Cursor borrowed; returned rows own values; cursor exhaustion releases read lease. |
| failure | Duplicate/state/lease mismatch fails; runtime exceptions propagate. |
| cost | Visits every cursor result. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0020

[Lines 118–141](../../../../../tests/unit/delta_anchor_test.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_current_and_live(const DeltaRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare current query and live projections against A04 after a transition. |
| inputs / outputs | Takes runtime/database/head order by const reference and label; returns void. |
| invariants | Checks A04 current answer, optional live snapshot sequence/factors, supplied head order and runtime invariants. |
| ownership | Inputs borrowed; expected values local. |
| failure | Any answer/snapshot/layout/invariant mismatch fails. |
| cost | One A04 materialization and factor projection. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0022

[Lines 143–147](../../../../../tests/unit/delta_anchor_test.cpp#L143); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct EventResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry signed answer rows, route stages, metrics and bootstrap-mode result from a drained event. |
| inputs / outputs | Aggregate owns Relation/set, vectors and DeltaMetrics by value. |
| invariants | Allows paired strategies to compare both output and work details after epoch drain. |
| ownership | Owns copied rows/stages/metrics; no live runtime reference. |
| failure | Plain data aggregate. |
| cost | Copies the event’s measured finite output and stage records. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0024

[Lines 149–192](../../../../../tests/unit/delta_anchor_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
EventResult drain_event(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain an event epoch and check its signed output, route records, layouts and released lease. |
| inputs / outputs | Takes runtime/epoch by mutable reference, expected signed set and head order by const reference; returns EventResult. |
| invariants | Exports tuple values, checks exact unique output, each stage interval and field order, output counts, remaining()==0 and inactive epoch. |
| ownership | Runtime/epoch/input vectors borrowed; returned event owns copied rows/stages/metrics. |
| failure | Any output/stage/layout/lease mismatch fails; runtime exceptions propagate. |
| cost | Visits emitted records and route stages. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md) |

## B0026

[Lines 194–201](../../../../../tests/unit/delta_anchor_test.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drain_empty_maintenance(DeltaRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain an empty maintenance-mode epoch. |
| inputs / outputs | Takes runtime/epoch by mutable reference and label; returns void. |
| invariants | Requires no records and released/inactive output lease. |
| ownership | Epoch borrowed and exhausted. |
| failure | Unexpected output or retained lease fails. |
| cost | Constant checks for empty epoch. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0027

[Lines 202–203](../../../../../tests/unit/delta_anchor_test.cpp#L202); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L202-L203:sha256:21f6336079dc6170dc30f67f3e8f0eda4f62e579ef1ce8f7b8c4ee362a29235e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_anchor_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 204–209](../../../../../tests/unit/delta_anchor_test.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 public:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct paired on-output runtimes using anchored and root-first completion. |
| inputs / outputs | Takes PhysicalPlan and table count; copies plan into anchored runtime and moves it into root-first runtime, allocates database table slots. |
| invariants | Both options() calls use maintenance mode and on_output live maintenance; strategies differ only in completion. |
| ownership | Pair owns both runtime facades, database and sequence. |
| failure | Runtime construction/allocation errors propagate. |
| cost | Constructs two runtime states over same plan metadata. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0030

[Lines 211–230](../../../../../tests/unit/delta_anchor_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void seed(TableId table, Row row, const std::string& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed the same physical row into both completion runtimes and mirror it locally. |
| inputs / outputs | Takes table, Row and label; applies same next sequence; returns void. |
| invariants | Drains both maintenance epochs as empty and rejects duplicate database seed. |
| ownership | Runtime and mirror each own row copies. |
| failure | Unexpected output or duplicate fails; runtime exceptions propagate. |
| cost | Two event applications and empty drains. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0032

[Lines 232–240](../../../../../tests/unit/delta_anchor_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void bootstrap(const std::vector<VariableId>& head_order,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bootstrap both runtimes into delta mode and compare answers/live state. |
| inputs / outputs | Takes head order and label by const reference; returns void. |
| invariants | Mode transition scans existing E, then check_current_and_live compares both to A04 and checks invariants. |
| ownership | Pair owns runtime/database; expected A04 values local. |
| failure | Transition/evaluator/mismatch errors propagate or fail assertion. |
| cost | Two bootstraps plus two A04 validations. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0034

[Lines 242–252](../../../../../tests/unit/delta_anchor_test.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void maintenance(const std::vector<VariableId>& head_order,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Switch both runtimes back to maintenance and verify maintenance outputs are empty. |
| inputs / outputs | Takes head order/label by const reference; returns void. |
| invariants | Transitions discard live snapshots; applies no physical update in this method. |
| ownership | Pair retains both runtimes/database. |
| failure | Transition or retained snapshot/output fails. |
| cost | Two mode transitions and empty epoch checks. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0036

[Lines 254–285](../../../../../tests/unit/delta_anchor_test.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::pair<EventResult, EventResult> apply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical update to both completion strategies and compare event outputs. |
| inputs / outputs | Takes table, operation, Row, head order and label; returns pair of owning EventResult values. |
| invariants | Requires a real set crossing in local before/after DB; assigns same sequence; applies/drains each; checks A04 output/current/live. Mirror DB advances only after the two engine events succeed. |
| ownership | Pair owns runtimes/database; returned results own copied rows/stages/metrics. |
| failure | No-op fixture update or output/state mismatch fails; no allocation-failure injection. |
| cost | Two runtime events plus A04 before/after/current checks and epoch drains. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § One physical input](../../../../delta_runtime.md) |

## B0038

[Lines 287–287](../../../../../tests/unit/delta_anchor_test.cpp#L287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const Database& database() const { return database_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose fixture Database as const reference. |
| inputs / outputs | No args; returns const Database&. |
| invariants | Read-only access to mirrored state. |
| ownership | Borrowed until Pair destruction. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0039

[Lines 288–288](../../../../../tests/unit/delta_anchor_test.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const DeltaRuntime& anchored() const { return anchored_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the anchored completion runtime as const reference. |
| inputs / outputs | No args; returns const DeltaRuntime&. |
| invariants | Read-only access. |
| ownership | Borrowed until Pair destruction. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0040

[Lines 289–289](../../../../../tests/unit/delta_anchor_test.cpp#L289); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] const DeltaRuntime& root_first() const { return root_first_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the root-first completion runtime as const reference. |
| inputs / outputs | No args; returns const DeltaRuntime&. |
| invariants | Read-only access. |
| ownership | Borrowed until Pair destruction. |
| failure | No custom failure handling. |
| cost | Constant-time accessor. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp) |

## B0042

[Lines 291–305](../../../../../tests/unit/delta_anchor_test.cpp#L291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
 private:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate either runtime’s current query and maintenance snapshot against A04. |
| inputs / outputs | Static helper takes runtime/database/head order/label by const reference; returns void. |
| invariants | In maintenance mode expects no live snapshot; in delta mode validates query answer, head layout, live projection and invariants. |
| ownership | All inputs borrowed; expected answer local. |
| failure | Mode/output/invariant mismatch fails. |
| cost | One A04 evaluation and conditional factor projection. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0043

[Lines 306–312](../../../../../tests/unit/delta_anchor_test.cpp#L306); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L306-L312:sha256:05dab372f77a30b74d79bfd726d17ba16d8af023c6bd1d069d351f4f3bd29027
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_anchor_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0044

[Lines 313–328](../../../../../tests/unit/delta_anchor_test.cpp#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan diagnostic_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a repeated-head tree fixture with a root and two routes. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Preserves explicit variable/head ordering needed to distinguish route prefixes. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed tree lowering. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0046

[Lines 330–335](../../../../../tests/unit/delta_anchor_test.cpp#L330); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DiagnosticMetrics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry selected cursor-work counts for anchored and root-first runs. |
| inputs / outputs | Aggregate stores per-route cursor startup/results/termination fields by value. |
| invariants | Used as deterministic internal work counters, not time or global cost. |
| ownership | Owns scalar copies. |
| failure | Plain aggregate. |
| cost | Constant-size value. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0048

[Lines 337–378](../../../../../tests/unit/delta_anchor_test.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DiagnosticMetrics diagnostic_run(std::size_t count) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the diagnostic repeated-head fixture at one or more row counts and capture per-route completion metrics. |
| inputs / outputs | Takes count; returns DiagnosticMetrics. |
| invariants | Seeds matching route rows, bootstraps, applies the completion event and compares exact A04 output; exports selected cursor-phase metrics for both strategies. |
| ownership | Local Pair/database and returned metrics own values. |
| failure | Answer, stage, layout or metric mismatch fails; no allocation injection. |
| cost | Work grows with finite seeded rows; only named counters are measured, not CPU time. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md § Traversal and assumptions](../../../../anchored_delta.md), [docs/anchored_delta.md § Work and remaining obligations](../../../../anchored_delta.md) |

## B0049

[Lines 379–382](../../../../../tests/unit/delta_anchor_test.cpp#L379); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L379-L382:sha256:3633d8b13bd00ef7392dabf2d28ac019114c40b7df5bd99f7a4521531a587983
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_anchor_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 383–387](../../../../../tests/unit/delta_anchor_test.cpp#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CursorWork cursor_work(const DeltaMetrics& metrics) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project cursor work fields from DeltaMetrics. |
| inputs / outputs | Takes metrics by const reference; returns CursorWork tuple. |
| invariants | Returns startup/result/termination work only; omits unrelated counters and elapsed time. |
| ownership | Metrics borrowed; tuple owns scalar copies. |
| failure | No custom failure handling. |
| cost | Copies three fields. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md § Work and remaining obligations](../../../../anchored_delta.md) |

## B0052

[Lines 389–416](../../../../../tests/unit/delta_anchor_test.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void anchored_completion_scales_with_changed_witness() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare anchored and root-first completion work as changed-witness count grows. |
| inputs / outputs | No args; runs diagnostic fixture for N=1 and N=64. |
| invariants | Requires anchored route cursor phase work remains equal and within fixture threshold while root-first result work rises; exact query answers remain A04-checked. These operation counters do not establish CPU scaling. |
| ownership | Each diagnostic call owns Pair; metrics copied. |
| failure | Any output or counter expectation fails. |
| cost | Two finite runs at two sizes. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md § Work and remaining obligations](../../../../anchored_delta.md) |

## B0054

[Lines 418–442](../../../../../tests/unit/delta_anchor_test.cpp#L418); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan deep_sibling_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a deep sibling plan with a shared root and two branches. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Branches share root scope, with separate descendants used for reverse deletion/product coverage. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0056

[Lines 444–456](../../../../../tests/unit/delta_anchor_test.cpp#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t path_depth_to_root(const auto& plan, NodeId node) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count parent links from a plan node back to the root. |
| inputs / outputs | Takes plan and node by const reference/value; returns depth. |
| invariants | Follows parent links until root; fixture plan is assumed to have a valid finite parent chain. |
| ownership | Plan borrowed. |
| failure | Invalid node/index or malformed chain fails by access or assertion. |
| cost | Visits one node per ancestor. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0058

[Lines 458–505](../../../../../tests/unit/delta_anchor_test.cpp#L458); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reverse_path_deletion_and_sibling_products() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise reverse path deletion and sibling product completion. |
| inputs / outputs | No args; returns void. |
| invariants | A04 signed output and L snapshots are checked while deleting root/path rows and completing sibling branches; verifies support cleanup and route ownership for these fixtures. |
| ownership | Each Pair/runtime and fixture database local; rows are value-owned. |
| failure | Unexpected outputs/live state fail. No injected allocation/runtime fault. |
| cost | Fixed finite seeds and update sequence with paired strategy checks. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/anchored_delta.md § Enumerable parent state and stable deletion](../../../../anchored_delta.md) |

## B0060

[Lines 507–521](../../../../../tests/unit/delta_anchor_test.cpp#L507); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a nullary separator plan with a root gating child product. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Empty-scope root activation controls child L projections. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0062

[Lines 523–562](../../../../../tests/unit/delta_anchor_test.cpp#L523); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_separator_and_product() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise nullary separator crossings and disconnected product activation/deactivation. |
| inputs / outputs | No args; returns void. |
| invariants | Checks Row{} root key, product signed answers and L factors across root insert/erase; oracle is A04 plus exact stage/output records. |
| ownership | Pair owns runtime/database; copied snapshots local. |
| failure | Output or factor mismatch fails. |
| cost | Finite fixture updates and A04 materializations. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md) |

## B0064

[Lines 564–578](../../../../../tests/unit/delta_anchor_test.cpp#L564); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a same-scope alias plan for duplicated native occurrences. |
| inputs / outputs | No args; returns lowered PhysicalPlan. |
| invariants | Two occurrences map the same physical table/scope; prefix ownership is tested separately. |
| ownership | Plan owns metadata. |
| failure | Lowering errors propagate. |
| cost | One fixed plan lowering. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0066

[Lines 580–591](../../../../../tests/unit/delta_anchor_test.cpp#L580); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_alias_stage_ownership(const std::pair<EventResult, EventResult>& event,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that each alias route stage owns its expected event rows. |
| inputs / outputs | Takes paired EventResult and expected route counts by const reference/value; returns void. |
| invariants | Filters route stage slices from output intervals and compares exact signed records per route; does not infer ownership from final relation alone. |
| ownership | EventResult borrowed; temporary sets own row copies. |
| failure | Wrong stage bounds or row ownership fails. |
| cost | Scans stage records and emitted rows. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/delta_runtime.md § Views and prefix identity](../../../../delta_runtime.md) |

## B0068

[Lines 593–613](../../../../../tests/unit/delta_anchor_test.cpp#L593); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void alias_stage_isolation_and_rebootstrap() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise alias stage isolation across maintenance and delta rebootstrap. |
| inputs / outputs | No args; returns void. |
| invariants | Checks each aliased answer appears only in its completing prefix before and after dropping/rebuilding live state. |
| ownership | Pair owns runtimes/database; event results own copies. |
| failure | Stage, bootstrap or A04 mismatch fails. |
| cost | Finite seeds, mode changes and updates with paired runtime checks. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0069

[Lines 614–616](../../../../../tests/unit/delta_anchor_test.cpp#L614); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L614-L616:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_anchor_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0070

[Lines 617–628](../../../../../tests/unit/delta_anchor_test.cpp#L617); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run anchored-completion fixtures and report pass/failure. |
| inputs / outputs | No args; returns 0 on success. |
| invariants | Invokes diagnostic scaling, reverse deletion, nullary/product, and alias/rebootstrap cases; no execution is claimed by the review card. |
| ownership | Fixtures own local runtime state. |
| failure | Caught std::exception prints diagnostic and returns 1. |
| cost | Finite fixtures at specified row counts. |
| Design | [tests/unit/delta_anchor_test.cpp](../../../../../tests/unit/delta_anchor_test.cpp), [docs/anchored_delta.md](../../../../anchored_delta.md) |
