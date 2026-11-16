# `tests/unit/epoch_view_test.cpp` — block usage map

[Source](../../../../../tests/unit/epoch_view_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `44c0bb451d9da2d5133f5d28bb651b17a5c0bb6d4fb5a9054a979cb56a2b7206`. 812 lines partitioned into 49 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/epoch_view_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../tests/unit/epoch_view_test.cpp#L21) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../tests/unit/epoch_view_test.cpp#L24) | Explanatory comments or spacing. |  |
| [B0004 · 25–35](../../../../../tests/unit/epoch_view_test.cpp#L25) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::string; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/epoch_view_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0006 · 37–37](../../../../../tests/unit/epoch_view_test.cpp#L37) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 38–38](../../../../../tests/unit/epoch_view_test.cpp#L38) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0007) |
| [B0008 · 39–39](../../../../../tests/unit/epoch_view_test.cpp#L39) | Explanatory comments or spacing. |  |
| [B0009 · 40–52](../../../../../tests/unit/epoch_view_test.cpp#L40) | Callable definition: Relation drain(SupportRuntime::ResultCursor& cursor) | calls next, check, layout, same_token; guard check(row-&gt;layout().same_token(cursor.layout()),; returns rows; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 53–53](../../../../../tests/unit/epoch_view_test.cpp#L53) | Explanatory comments or spacing. |  |
| [B0011 · 54–61](../../../../../tests/unit/epoch_view_test.cpp#L54) | Callable definition: void check_schema(const storage::TupleLayout& layout, const std::vector&lt;VariableId&gt;& variables, const std::string& context) | calls check, fields, size; guard check(layout.fields().size() == variables.size(), context + ": wrong output arity");; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 62–62](../../../../../tests/unit/epoch_view_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0013 · 63–74](../../../../../tests/unit/epoch_view_test.cpp#L63) | Callable definition: PhysicalPlan xy_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree); source comment (unverified): // Keep a deliberately non-sorted head so whole-query output order can be · [reviewed contract](#b0013) |
| [B0014 · 75–75](../../../../../tests/unit/epoch_view_test.cpp#L75) | Explanatory comments or spacing. |  |
| [B0015 · 76–85](../../../../../tests/unit/epoch_view_test.cpp#L76) | Callable definition: PhysicalPlan hidden_witness_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0015) |
| [B0016 · 86–86](../../../../../tests/unit/epoch_view_test.cpp#L86) | Explanatory comments or spacing. |  |
| [B0017 · 87–101](../../../../../tests/unit/epoch_view_test.cpp#L87) | Callable definition: PhysicalPlan hidden_branch_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0017) |
| [B0018 · 102–102](../../../../../tests/unit/epoch_view_test.cpp#L102) | Explanatory comments or spacing. |  |
| [B0019 · 103–120](../../../../../tests/unit/epoch_view_test.cpp#L103) | Callable definition: PhysicalPlan chain_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0019) |
| [B0020 · 121–121](../../../../../tests/unit/epoch_view_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0021 · 122–128](../../../../../tests/unit/epoch_view_test.cpp#L122) | Callable definition: PhysicalPlan nullary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0021) |
| [B0022 · 129–129](../../../../../tests/unit/epoch_view_test.cpp#L129) | Explanatory comments or spacing. |  |
| [B0023 · 130–134](../../../../../tests/unit/epoch_view_test.cpp#L130) | Callable definition: PhysicalPlan constant_plan(bool truth) | calls planner::lower_tree; returns planner::lower_tree(catalog, query, FreeConnexTree{}) · [reviewed contract](#b0023) |
| [B0024 · 135–135](../../../../../tests/unit/epoch_view_test.cpp#L135) | Explanatory comments or spacing. |  |
| [B0025 · 136–140](../../../../../tests/unit/epoch_view_test.cpp#L136) | Callable definition: void apply_insert(PhysicalRuntime& runtime, std::uint64_t& sequence, TableId table, Row row) | calls apply, check; guard check(result.input.physical_changed, "physical view fixture row was not inserted");; growth insert · [reviewed contract](#b0025) |
| [B0026 · 141–141](../../../../../tests/unit/epoch_view_test.cpp#L141) | Explanatory comments or spacing. |  |
| [B0027 · 142–208](../../../../../tests/unit/epoch_view_test.cpp#L142) | Callable definition: void full_head_witness_restriction_and_bindings() | calls xy_plan, runtime, resize, n; guard check(view.valid() && !view.tentative() && view.sequence() == sequence &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 209–209](../../../../../tests/unit/epoch_view_test.cpp#L209) | Explanatory comments or spacing. |  |
| [B0029 · 210–240](../../../../../tests/unit/epoch_view_test.cpp#L210) | Callable definition: void hidden_bindings_and_c_star_fragments() | calls runtime, hidden_witness_plan, apply_insert, n; guard check(drain(visible) == Relation{{n(1)}},; returns step.node == NodeId{1} · [reviewed contract](#b0029) |
| [B0030 · 241–241](../../../../../tests/unit/epoch_view_test.cpp#L241) | Explanatory comments or spacing. |  |
| [B0031 · 242–308](../../../../../tests/unit/epoch_view_test.cpp#L242) | Callable definition: void ancestor_child_chain_and_independent_ejoin() | calls chain_plan, runtime, resize, n; guard check(plan.enumeration().steps.size() == 3 &&; growth insert, resize; 6 loop sites · [reviewed contract](#b0031) |
| [B0032 · 309–309](../../../../../tests/unit/epoch_view_test.cpp#L309) | Explanatory comments or spacing. |  |
| [B0033 · 310–333](../../../../../tests/unit/epoch_view_test.cpp#L310) | Callable definition: void projection_count_changes_keep_visible_rows() | calls runtime, hidden_witness_plan, check, apply; guard check(runtime.apply({1, NodeId{0}, SetOperation::insert, {n(1), n(10)}}).native_changed,; growth insert · [reviewed contract](#b0033) |
| [B0034 · 334–334](../../../../../tests/unit/epoch_view_test.cpp#L334) | Explanatory comments or spacing. |  |
| [B0035 · 335–423](../../../../../tests/unit/epoch_view_test.cpp#L335) | Callable definition: void pending_view_freezes_prefix_and_commit_preserves_old_cursor() | calls runtime, xy_plan, apply_insert, n; guard check(deleted_handle.has_value(), "pending-view fixture could not find the row to erase");; growth emplace, insert · [reviewed contract](#b0035) |
| [B0036 · 424–424](../../../../../tests/unit/epoch_view_test.cpp#L424) | Explanatory comments or spacing. |  |
| [B0037 · 425–555](../../../../../tests/unit/epoch_view_test.cpp#L425) | Callable definition: void pending_chain_leaf_delete_restores_ghost_rows_through_parent_keys() | calls chain_plan, runtime, resize, n; guard check(after_database.tables\[2\].erase(leaf) == 1,; returns selected; growth insert, resize; 6 loop sites · [reviewed contract](#b0037) |
| [B0038 · 556–556](../../../../../tests/unit/epoch_view_test.cpp#L556) | Explanatory comments or spacing. |  |
| [B0039 · 557–598](../../../../../tests/unit/epoch_view_test.cpp#L557) | Callable definition: void current_view_copies_and_multiple_cursors_guard_mutations() | calls runtime, xy_plan, apply, n; guard check(view.valid() && !view.tentative() && view.sequence() == 1 &&; growth emplace, insert · [reviewed contract](#b0039) |
| [B0040 · 599–599](../../../../../tests/unit/epoch_view_test.cpp#L599) | Explanatory comments or spacing. |  |
| [B0041 · 600–637](../../../../../tests/unit/epoch_view_test.cpp#L600) | Callable definition: void pending_logical_stage_resumes_only_after_all_view_copies_close() | calls runtime, xy_plan, begin_epoch, check; guard check(pending.stage(NodeId{0}, {n(1), n(10)}),; growth emplace, insert · [reviewed contract](#b0041) |
| [B0042 · 638–638](../../../../../tests/unit/epoch_view_test.cpp#L638) | Explanatory comments or spacing. |  |
| [B0043 · 639–670](../../../../../tests/unit/epoch_view_test.cpp#L639) | Callable definition: void rollback_invalidates_views_and_closes_cursors() | calls runtime, xy_plan, begin_epoch, check; guard check(pending.stage(NodeId{0}, {n(1), n(10)}),; growth emplace, insert · [reviewed contract](#b0043) |
| [B0044 · 671–671](../../../../../tests/unit/epoch_view_test.cpp#L671) | Explanatory comments or spacing. |  |
| [B0045 · 672–751](../../../../../tests/unit/epoch_view_test.cpp#L672) | Callable definition: void nullary_truth_constant_routes_and_noop_views() | calls truth, nullary_plan, current_view, results; guard check(drain(empty_rows).empty(), "empty nullary view returned a truth row");; growth insert · [reviewed contract](#b0045) |
| [B0046 · 752–752](../../../../../tests/unit/epoch_view_test.cpp#L752) | Explanatory comments or spacing. |  |
| [B0047 · 753–790](../../../../../tests/unit/epoch_view_test.cpp#L753) | Callable definition: void view_and_value_owning_lifetimes_survive_facade_move_and_destruction() | calls original, xy_plan, apply_insert, n; guard check(saved && saved-&gt;values() == Row{n(70), n(7)},; growth emplace · [reviewed contract](#b0047) |
| [B0048 · 791–793](../../../../../tests/unit/epoch_view_test.cpp#L791) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0048) |
| [B0049 · 794–812](../../../../../tests/unit/epoch_view_test.cpp#L794) | Callable definition: int main() | calls full_head_witness_restriction_and_bindings, hidden_bindings_and_c_star_fragments, ancestor_child_chain_and_independent_ejoin, projection_count_changes_keep_visible_rows; returns 1 · [reviewed contract](#b0049) |

## B0001

[Lines 1–20](../../../../../tests/unit/epoch_view_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:2999343de4a1f0542bda9c2c111856a2621e77b900d06b8b9ed1ee642fdcd25b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare epoch_view_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", "evaluator.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/epoch_view_test.cpp](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–23](../../../../../tests/unit/epoch_view_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an epoch-view test when a boolean assertion is false. |
| inputs / outputs | Accepts a condition and diagnostic string; returns normally if true and throws std::runtime_error(message) otherwise. |
| invariants | The helper checks the supplied condition only; it does not establish view correctness by itself. |
| ownership | The diagnostic string is borrowed for the call. |
| failure | False conditions throw and propagate to main's failure handler. |
| cost | Constant-time condition check; error-message use occurs only on failure. |
| Design | [tests/unit/epoch_view_test.cpp §B0002 L21-L23](../../../../../tests/unit/epoch_view_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0004

[Lines 25–35](../../../../../tests/unit/epoch_view_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an action throws crown::Error with one exact code. |
| inputs / outputs | Invokes the action and catches Error; compares failure.code() to the requested string_view. |
| invariants | No exception or a different code fails; unrelated exception types propagate. |
| ownership | Action and expected code are borrowed; caught failure is local. |
| failure | Mismatch or missing Error throws std::runtime_error. |
| cost | One action call and code comparison. |
| Design | [tests/unit/epoch_view_test.cpp §B0004 L25-L35](../../../../../tests/unit/epoch_view_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0006

[Lines 37–37](../../../../../tests/unit/epoch_view_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an int64 Value for view fixtures. |
| inputs / outputs | Converts one signed integer to Value and returns it by value. |
| invariants | Preserves the exact fixture scalar; it does not validate plan schema. |
| ownership | Returned scalar is value-owned. |
| failure | Conversion errors propagate. |
| cost | Scalar construction only. |
| Design | [tests/unit/epoch_view_test.cpp §B0006 L37-L37](../../../../../tests/unit/epoch_view_test.cpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md) |

## B0007

[Lines 38–38](../../../../../tests/unit/epoch_view_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a string Value for view fixtures. |
| inputs / outputs | Moves one std::string into Value and returns it. |
| invariants | Preserves the selected string exactly; this helper does not perform runtime type admission. |
| ownership | Returned variant owns the string payload. |
| failure | Construction failures propagate. |
| cost | Moves one string payload into the variant; payload-byte cost follows string length. |
| Design | [tests/unit/epoch_view_test.cpp §B0007 L38-L38](../../../../../tests/unit/epoch_view_test.cpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md) |

## B0009

[Lines 40–52](../../../../../tests/unit/epoch_view_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor& cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a ResultCursor into a set while checking row layout and cursor exhaustion. |
| inputs / outputs | Repeatedly calls next(), verifies each tuple layout token matches cursor.layout(), exports rows into a Relation without duplicates, and checks exhausted/inactive state plus stable nullopt on another next(). |
| invariants | The helper checks emitted set uniqueness and cursor lease release on natural exhaustion for the supplied cursor; it does not test cancellation or rollback. |
| ownership | Cursor is borrowed; exported Relation rows own their values. Cursor remains caller-owned but is exhausted. |
| failure | Unexpected layout token, duplicate, state or next result fails through check. |
| cost | Consumes all emitted rows and copies their values; work scales with result count and projected row width. |
| Design | [tests/unit/epoch_view_test.cpp §B0009 L40-L52](../../../../../tests/unit/epoch_view_test.cpp), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0011

[Lines 54–61](../../../../../tests/unit/epoch_view_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_schema(const storage::TupleLayout& layout,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a tuple layout's ordered variable schema. |
| inputs / outputs | Accepts a TupleLayout, expected VariableId sequence and context; checks equal field count and variable ID at every position. |
| invariants | The predicate is ordered-schema equality for IDs and arity; scalar types and layout token are not compared here. |
| ownership | Layout and expected vector are borrowed. |
| failure | First mismatch fails through check. |
| cost | Linear scan of the requested field list. |
| Design | [tests/unit/epoch_view_test.cpp §B0011 L54-L61](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md) |

## B0013

[Lines 63–74](../../../../../tests/unit/epoch_view_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan xy_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an xy plan whose SQL output order differs from root-fragment variable order. |
| inputs / outputs | Creates one r(x:int64,y:int64) occurrence and an output mapping y then x, with one native node whose scope is x,y; lowers the physical plan. |
| invariants | The fixture distinguishes whole-query mapped order from fragment sorted-variable order; it is a single-table plan. |
| ownership | Local DTOs are consumed by lowering; returned plan owns metadata. |
| failure | Planner errors propagate. |
| cost | Fixed one-node lowering and two-variable metadata. |
| Design | [tests/unit/epoch_view_test.cpp §B0013 L63-L74](../../../../../tests/unit/epoch_view_test.cpp), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md) |

## B0015

[Lines 76–85](../../../../../tests/unit/epoch_view_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan hidden_witness_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-node plan with a projected x and hidden witness variable. |
| inputs / outputs | Creates r(x,witness) with query head x and one native node over both variables, then lowers. |
| invariants | The witness remains a query variable outside the public head and is used by hidden-binding tests. |
| ownership | Returned plan owns lowered metadata. |
| failure | Planner errors propagate. |
| cost | Fixed two-field one-node lowering. |
| Design | [tests/unit/epoch_view_test.cpp §B0015 L76-L85](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0017

[Lines 87–101](../../../../../tests/unit/epoch_view_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan hidden_branch_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-node branch with hidden variables outside the C* enumeration. |
| inputs / outputs | Creates r(x,z) as root and s(z,w) as child, while query output contains only x; lowers the tree. |
| invariants | The child factor supplies a hidden branch used to test fragment selection and existential binding; the fixture itself does not assert enumeration behavior. |
| ownership | Plan is returned by value with owned lowered metadata. |
| failure | Planner errors propagate. |
| cost | Fixed two-relation plan construction and lowering. |
| Design | [tests/unit/epoch_view_test.cpp §B0017 L87-L101](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md) |

## B0019

[Lines 103–120](../../../../../tests/unit/epoch_view_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan chain_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a three-node r-to-s-to-t C* chain with a reordered, repeated output mapping. |
| inputs / outputs | Creates r(x,y), s(y,z), t(z,w) and output variables w,x,z,y,w; lowers a three-level native tree. |
| invariants | Repeated output variable w is intentional; root-fragment schema remains the sorted visible scope and differs from whole-query output mapping. |
| ownership | Plan owns lowered metadata; fixture vectors are temporary. |
| failure | Planner errors propagate. |
| cost | Fixed three-relation/four-variable plan lowering. |
| Design | [tests/unit/epoch_view_test.cpp §B0019 L103-L120](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md) |

## B0021

[Lines 122–128](../../../../../tests/unit/epoch_view_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a nullary query over a native relation with an ignored input column. |
| inputs / outputs | Creates flags(tag:string), maps the atom column to IgnoredColumn, and uses an empty query head and native-node scope. |
| invariants | The physical witness is non-nullary while projected query truth is one empty row when supported. |
| ownership | Lowered plan owns query metadata; catalog inputs are temporary. |
| failure | Planner errors propagate. |
| cost | Fixed one-column one-node lowering. |
| Design | [tests/unit/epoch_view_test.cpp §B0021 L122-L128](../../../../../tests/unit/epoch_view_test.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0023

[Lines 130–134](../../../../../tests/unit/epoch_view_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan constant_plan(bool truth) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the plan for a selected constant Boolean truth value. |
| inputs / outputs | Accepts truth; constructs an empty catalog/query/tree, setting query false flag to !truth, then lowers. |
| invariants | The returned zero-relation plan encodes exactly the requested constant truth fixture. |
| ownership | Plan owns its lowered constant route. |
| failure | Planner errors propagate. |
| cost | Constant-size descriptor construction and lowering. |
| Design | [tests/unit/epoch_view_test.cpp §B0023 L130-L134](../../../../../tests/unit/epoch_view_test.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0025

[Lines 136–140](../../../../../tests/unit/epoch_view_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_insert(PhysicalRuntime& runtime, std::uint64_t& sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical insert with the next sequence and require a real source membership change. |
| inputs / outputs | Preincrements the referenced sequence, submits table/row insert to PhysicalRuntime, and checks result.input.physical_changed. |
| invariants | The helper is for fixture insertion; duplicates fail its assertion instead of being treated as accepted no-ops. |
| ownership | Runtime is borrowed; the by-reference sequence is updated before apply returns. |
| failure | Engine failures propagate; a no-op result fails through check. |
| cost | One physical runtime update and row comparison. |
| Design | [tests/unit/epoch_view_test.cpp §B0025 L136-L140](../../../../../tests/unit/epoch_view_test.cpp), [docs/physical_runtime.md §Input and source-row identity](../../../../physical_runtime.md) |

## B0027

[Lines 142–208](../../../../../tests/unit/epoch_view_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void full_head_witness_restriction_and_bindings() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise current-view whole-query results, bindings, fragments and writer exclusion. |
| inputs / outputs | Loads three xy rows; compares mapped whole results to reference::evaluate; checks exact/partial/repeated bindings, invalid conflicts/type/ID, root fragment sorted schema, invalid fragment, second view construction and runtime_busy on write. |
| invariants | Assertions cover this finite single-table fixture, output ordering and listed errors. The differential oracle is independent code for this input, not a universal proof or current run result. |
| ownership | PhysicalRuntime owns rows; view and cursors are local leases; expected/output Relations are test copies. |
| failure | Invalid bindings/fragments must carry exact codes; active view writer attempt must be runtime_busy. |
| cost | Three updates, several small cursors, row exports and one full reference evaluation. |
| Design | [tests/unit/epoch_view_test.cpp §B0027 L142-L208](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0029

[Lines 210–240](../../../../../tests/unit/epoch_view_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hidden_bindings_and_c_star_fragments() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test hidden-variable bindings and reject a hidden non-C* node as a visible fragment. |
| inputs / outputs | Loads two witnesses for x=1; checks visible binding collapses witnesses, hidden witness binding filters completions and a miss is empty; then checks hidden branch node is absent from C* steps and invalid as a VisibleFragment root. |
| invariants | The fixture distinguishes projection from existential witness restriction; it asserts one enumerator shape only. |
| ownership | Two runtimes own rows; views/cursors close within the case. |
| failure | Invalid fragment must report invalid_fragment; assertion mismatches fail the test. |
| cost | Four fixture updates, a few completion cursors and one enumeration-step scan. |
| Design | [tests/unit/epoch_view_test.cpp §B0029 L210-L240](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md) |

## B0031

[Lines 242–308](../../../../../tests/unit/epoch_view_test.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ancestor_child_chain_and_independent_ejoin() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whole-query and fragment traversal over a three-level visible chain. |
| inputs / outputs | Loads r/s/t row sets; verifies three-step parent chain; compares a hand-built E-join to the reference evaluator; checks whole results, root fragment schema/rows and child fragment rows under y=10. |
| invariants | The hand join and reference evaluator are two finite expected-result constructions; the test is not a proof of arbitrary E-join traversal. |
| ownership | Runtime owns maintained state; fixture rows, hand relations and evaluator result are local values; cursors are drained and released. |
| failure | Any plan-shape, schema, row or differential mismatch fails through check. |
| cost | Nested fixture joins, reference evaluation, and three cursor drains; work scales with the small relation cross-products and outputs. |
| Design | [tests/unit/epoch_view_test.cpp §B0031 L242-L308](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0033

[Lines 310–333](../../../../../tests/unit/epoch_view_test.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void projection_count_changes_keep_visible_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a positive hidden-witness count decrease leaves the projected answer visible. |
| inputs / outputs | Starts with two (x=1,witness) rows; deletes one in a pending epoch; opens before/after views; checks journal/membership metrics and one visible x=1 result on both sides before commit. |
| invariants | The assertion covers a positive support-count change in this one-witness-hidden fixture; it does not test the zero-crossing deletion here. |
| ownership | Pending epoch owns mutation; before/after views and cursors borrow its journal-backed prefix. |
| failure | Failed view or result assertion propagates; no expected engine error is injected. |
| cost | Two committed inserts, one stage, one view patch, two short cursor drains and a commit. |
| Design | [tests/unit/epoch_view_test.cpp §B0033 L310-L333](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md) |

## B0035

[Lines 335–423](../../../../../tests/unit/epoch_view_test.cpp#L335); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pending_view_freezes_prefix_and_commit_preserves_old_cursor() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test physical erase before/after views, commit preservation and lease release. |
| inputs / outputs | Prepares deletion of xy row (2,20); verifies zero-work view construction fails without aborting; checks before restores and after excludes the row, shared patch metrics, public read/write blocking, a partially consumed before cursor across commit, retained pins, and writer resumption after all copies/cursors close. |
| invariants | The case asserts one prepared prefix and these lease/pin boundaries. Before-side behavior is checked only on the fixture rows and output mapping. |
| ownership | Pending physical update owns undo and source state; views/cursors retain the journal/read lease; saved row and handle are local value/identity snapshots. |
| failure | Expected resource_limit and runtime_busy codes are checked; closing each holder releases only its own lease. |
| cost | Two initial inserts, one delete preparation, repeated view/cursor construction, several failed writes, stats and one later insert. |
| Design | [tests/unit/epoch_view_test.cpp §B0035 L335-L423](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md §Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md), [docs/physical_runtime.md §Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0037

[Lines 425–555](../../../../../tests/unit/epoch_view_test.cpp#L425); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pending_chain_leaf_delete_restores_ghost_rows_through_parent_keys() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare before/after chain views across leaf deletion and insertion, including restored parent-key buckets. |
| inputs / outputs | Builds a three-level chain; computes reference whole/subtree relations before and after leaf deletion; checks patch/transition counts, whole results, bound completions, child fragment, partially consumed before cursor through commit, then prepares inverse insertion and checks before exclusion/after inclusion. |
| invariants | The reference comparisons and parent-key bucket checks cover the selected finite chain; transition set is asserted to contain E changes at nodes 0,1,2 for the deletion. |
| ownership | Physical runtime and pending tokens own state; before/after databases and evaluator relations are copied test fixtures; cursor rows are exported while owned. |
| failure | Failed assertion or evaluator mismatch fails the test; no fault allocator is used. |
| cost | Initial chain inserts, multiple full reference evaluations, patch construction, whole/fragment cursors and one extra insert/delete preparation. |
| Design | [tests/unit/epoch_view_test.cpp §B0037 L425-L555](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/epoch_views.md §Prefix and handle lifetime](../../../../epoch_views.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0039

[Lines 557–598](../../../../../tests/unit/epoch_view_test.cpp#L557); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void current_view_copies_and_multiple_cursors_guard_mutations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify copied committed views and multiple cursors share a mutation-blocking lease. |
| inputs / outputs | Creates a committed current view and copy, opens independent cursors, reads the same row, then checks writes stay runtime_busy until both view facades and both cursor objects are released. |
| invariants | The test checks the last-holder release boundary for this committed view; closing one copied facade does not prove release while another holder remains. |
| ownership | Copies and cursors retain the committed group; each optional owns one cursor until reset. |
| failure | Writer attempts must report runtime_busy while a holder exists; final insert must change membership. |
| cost | One row fixture, two view handles, two cursors and four write attempts. |
| Design | [tests/unit/epoch_view_test.cpp §B0039 L557-L598](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §What an epoch view represents](../../../../epoch_views.md), [docs/epoch_views.md §Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0041

[Lines 600–637](../../../../../tests/unit/epoch_view_test.cpp#L600); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pending_logical_stage_resumes_only_after_all_view_copies_close() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a pending logical stage resumes only after all external copies and cursors close. |
| inputs / outputs | Stages one row, checks zero-work view construction fails without abort, opens/copies a tentative view and cursor, checks reads and later stages are blocked, closes holders one by one, then stages another row and commits once. |
| invariants | The assertions distinguish runtime_busy from auto-abort and verify all external holders seal the prefix until the last is released. |
| ownership | PendingEpoch owns private state; copied EpochViews and cursor independently retain the shared view group. |
| failure | Construction must report resource_limit; read/stage calls must report runtime_busy until the cursor and copies are released. |
| cost | Two staged unary rows, one failed view build, one cursor, several lease checks and one commit. |
| Design | [tests/unit/epoch_view_test.cpp §B0041 L600-L637](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Prefix and handle lifetime](../../../../epoch_views.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0043

[Lines 639–670](../../../../../tests/unit/epoch_view_test.cpp#L639); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback_invalidates_views_and_closes_cursors() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check rollback invalidates a tentative view and proactively closes its active cursors. |
| inputs / outputs | Stages a row, opens one view and two cursors, reads one tentative tuple, rolls back, checks failed cursor states and invalid_cursor next calls, invalid_epoch on another view request, readiness restoration and same-sequence write. |
| invariants | Assertions check this rollback path closes every active cursor and restores the writer boundary; the returned tuple is not used after abort. |
| ownership | Pending token performs rollback; view/cursor facades remain local invalid handles until closed or destroyed. |
| failure | Cursor reuse must report invalid_cursor; post-rollback view creation must report invalid_epoch. |
| cost | One staged row, two cursor startups, rollback and one retry insert. |
| Design | [tests/unit/epoch_view_test.cpp §B0043 L639-L670](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md §Cursor states and close behavior](../../../../result_cursors.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0045

[Lines 672–751](../../../../../tests/unit/epoch_view_test.cpp#L672); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nullary_truth_constant_routes_and_noop_views() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nullary answer rows for physical truth transitions, no-op aliases and constant routes. |
| inputs / outputs | Starts with empty relation, inserts first witness, adds a second physical row that leaves logical support unchanged, erases one witness then the last; compares before/after empty-tuple relations and checks constant true/false plans. |
| invariants | The fixture asserts set/existential semantics: exactly one empty output row iff the Boolean query is true; second physical witness is a support no-op. |
| ownership | Each PhysicalRuntime owns its data; pending views/cursors are closed after each phase. |
| failure | Assertion failures propagate; physical updates are expected to be valid. |
| cost | Four physical preparations, short nullary cursor drains, two constant runtimes and repeated commits. |
| Design | [tests/unit/epoch_view_test.cpp §B0045 L672-L751](../../../../../tests/unit/epoch_view_test.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md), [docs/epoch_views.md §Projected completions](../../../../epoch_views.md), [docs/physical_runtime.md §Input and source-row identity](../../../../physical_runtime.md) |

## B0047

[Lines 753–790](../../../../../tests/unit/epoch_view_test.cpp#L753); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void view_and_value_owning_lifetimes_survive_facade_move_and_destruction() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that an epoch view and copied result tuple survive facade move and destruction. |
| inputs / outputs | Loads (7,70), retains a current view and a bound result tuple, cancels its cursor, moves the PhysicalRuntime, copies/traverses the view, destroys the facade, moves the view handle and traverses again; checks saved tuple/layout after close. |
| invariants | The fixture asserts retained owner lifetime and owning result values on this path; it does not test cross-thread use. |
| ownership | View/cursor retain the runtime implementation; saved Tuple owns projected values and layout identity independently. |
| failure | Moved-from view must be invalid; any lost owner or row fails through check. |
| cost | One row update, two short cursor traversals, facade/view moves and one value/layout check. |
| Design | [tests/unit/epoch_view_test.cpp §B0047 L753-L790](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md §What an epoch view represents](../../../../epoch_views.md), [docs/result_cursors.md §Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0048

[Lines 791–793](../../../../../tests/unit/epoch_view_test.cpp#L791); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L791-L793:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in epoch_view_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/epoch_view_test.cpp](../../../../../tests/unit/epoch_view_test.cpp), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md) |

## B0049

[Lines 794–812](../../../../../tests/unit/epoch_view_test.cpp#L794); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all epoch-view cases and report test process status. |
| inputs / outputs | Invokes eleven named cases; prints success on completion and returns 1 after reporting any std::exception. |
| invariants | The main function records only the invoked executable outcome; source review does not assert that the binary was built or run. |
| ownership | Cases own local runtimes, views and cursors; main owns the exception boundary. |
| failure | Any propagated standard exception returns 1. |
| cost | Sequential finite fixtures, reference evaluations and cursor traversals defined by the called cases. |
| Design | [tests/unit/epoch_view_test.cpp §B0049 L794-L812](../../../../../tests/unit/epoch_view_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |
