# `tests/unit/fragment_cursor_test.cpp` — block usage map

[Source](../../../../../tests/unit/fragment_cursor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6d895cc11a32215c8ac0f238cb3d89e4b23d182df202f9a740cff6c14a18da1c`. 827 lines partitioned into 57 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/fragment_cursor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../tests/unit/fragment_cursor_test.cpp#L21) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../tests/unit/fragment_cursor_test.cpp#L24) | Explanatory comments or spacing. |  |
| [B0004 · 25–35](../../../../../tests/unit/fragment_cursor_test.cpp#L25) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::string; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/fragment_cursor_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0006 · 37–37](../../../../../tests/unit/fragment_cursor_test.cpp#L37) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 38–38](../../../../../tests/unit/fragment_cursor_test.cpp#L38) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0007) |
| [B0008 · 39–39](../../../../../tests/unit/fragment_cursor_test.cpp#L39) | Callable definition: Value day(std::string_view value) | calls Date::parse; returns Date::parse(value) · [reviewed contract](#b0008) |
| [B0009 · 40–40](../../../../../tests/unit/fragment_cursor_test.cpp#L40) | Callable definition: Value decimal(std::string_view value) | calls Decimal::parse; returns Decimal::parse(value) · [reviewed contract](#b0009) |
| [B0010 · 41–41](../../../../../tests/unit/fragment_cursor_test.cpp#L41) | Explanatory comments or spacing. |  |
| [B0011 · 42–54](../../../../../tests/unit/fragment_cursor_test.cpp#L42) | Callable definition: Relation drain(SupportRuntime::ResultCursor& cursor) | calls next, check, layout, same_token; guard check(row-&gt;layout().same_token(cursor.layout()),; returns rows; growth insert; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 55–55](../../../../../tests/unit/fragment_cursor_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0013 · 56–63](../../../../../tests/unit/fragment_cursor_test.cpp#L56) | Callable definition: void check_schema(const storage::TupleLayout& layout, const std::vector&lt;VariableId&gt;& variables, const std::string& context) | calls check, fields, size; guard check(layout.fields().size() == variables.size(), context + ": wrong output arity");; 1 loop sites · [reviewed contract](#b0013) |
| [B0014 · 64–64](../../../../../tests/unit/fragment_cursor_test.cpp#L64) | Explanatory comments or spacing. |  |
| [B0015 · 65–72](../../../../../tests/unit/fragment_cursor_test.cpp#L65) | Callable definition: Relation a04_assignments(const Catalog& catalog, const Query& query, const Database& database) | calls clear, size, push_back, reference::evaluate; returns reference::evaluate(catalog, full, database); growth push_back; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 73–73](../../../../../tests/unit/fragment_cursor_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0017 · 74–92](../../../../../tests/unit/fragment_cursor_test.cpp#L74) | Callable definition: Relation a04_project(const Relation& assignments, const Query& query, const FixedAssignment& fixed = {}) | calls at, push_back, insert, std::move; returns projected; growth insert, push_back; 3 loop sites · [reviewed contract](#b0017) |
| [B0018 · 93–93](../../../../../tests/unit/fragment_cursor_test.cpp#L93) | Explanatory comments or spacing. |  |
| [B0019 · 94–98](../../../../../tests/unit/fragment_cursor_test.cpp#L94) | Callable definition: void insert(PhysicalRuntime& runtime, std::uint64_t& sequence, TableId table, Row row) | calls apply, check; guard check(result.input.physical_changed, "fixture source row was not inserted");; growth insert · [reviewed contract](#b0019) |
| [B0020 · 99–99](../../../../../tests/unit/fragment_cursor_test.cpp#L99) | Explanatory comments or spacing. |  |
| [B0021 · 100–109](../../../../../tests/unit/fragment_cursor_test.cpp#L100) | Callable definition: PhysicalPlan one_hidden_variable_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0021) |
| [B0022 · 110–113](../../../../../tests/unit/fragment_cursor_test.cpp#L110) | Explanatory comments or spacing. | source comment (unverified): // The selected local fragment is S(x,z,y). R(a,x) is its outside parent and · [reviewed contract](#b0022) |
| [B0023 · 114–128](../../../../../tests/unit/fragment_cursor_test.cpp#L114) | Callable definition: PhysicalPlan local_child_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree); source comment (unverified): // The selected local fragment is S(x,z,y). R(a,x) is its outside parent and · [reviewed contract](#b0023) |
| [B0024 · 129–129](../../../../../tests/unit/fragment_cursor_test.cpp#L129) | Explanatory comments or spacing. |  |
| [B0025 · 130–143](../../../../../tests/unit/fragment_cursor_test.cpp#L130) | Callable definition: PhysicalPlan outside_c_star_child_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0025) |
| [B0026 · 144–144](../../../../../tests/unit/fragment_cursor_test.cpp#L144) | Explanatory comments or spacing. |  |
| [B0027 · 145–163](../../../../../tests/unit/fragment_cursor_test.cpp#L145) | Callable definition: PhysicalPlan depth_three_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0027) |
| [B0028 · 164–164](../../../../../tests/unit/fragment_cursor_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0029 · 165–180](../../../../../tests/unit/fragment_cursor_test.cpp#L165) | Callable definition: PhysicalPlan shared_siblings_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0029) |
| [B0030 · 181–181](../../../../../tests/unit/fragment_cursor_test.cpp#L181) | Explanatory comments or spacing. |  |
| [B0031 · 182–200](../../../../../tests/unit/fragment_cursor_test.cpp#L182) | Callable definition: PhysicalPlan product_plan(std::size_t arity) | calls push_back, std::to_string, planner::lower_tree; returns planner::lower_tree(catalog, query, tree); growth push_back; 2 loop sites · [reviewed contract](#b0031) |
| [B0032 · 201–201](../../../../../tests/unit/fragment_cursor_test.cpp#L201) | Explanatory comments or spacing. |  |
| [B0033 · 202–220](../../../../../tests/unit/fragment_cursor_test.cpp#L202) | Callable definition: PhysicalPlan typed_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0033) |
| [B0034 · 221–221](../../../../../tests/unit/fragment_cursor_test.cpp#L221) | Explanatory comments or spacing. |  |
| [B0035 · 222–236](../../../../../tests/unit/fragment_cursor_test.cpp#L222) | Callable definition: PhysicalPlan self_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0035) |
| [B0036 · 237–237](../../../../../tests/unit/fragment_cursor_test.cpp#L237) | Explanatory comments or spacing. |  |
| [B0037 · 238–244](../../../../../tests/unit/fragment_cursor_test.cpp#L238) | Callable definition: PhysicalPlan nullary_atom_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0037) |
| [B0038 · 245–245](../../../../../tests/unit/fragment_cursor_test.cpp#L245) | Explanatory comments or spacing. |  |
| [B0039 · 246–250](../../../../../tests/unit/fragment_cursor_test.cpp#L246) | Callable definition: PhysicalPlan constant_plan(bool truth) | calls planner::lower_tree; returns planner::lower_tree(catalog, query, FreeConnexTree{}) · [reviewed contract](#b0039) |
| [B0040 · 251–251](../../../../../tests/unit/fragment_cursor_test.cpp#L251) | Explanatory comments or spacing. |  |
| [B0041 · 252–305](../../../../../tests/unit/fragment_cursor_test.cpp#L252) | Callable definition: void hidden_bindings_project_without_multiplying_rows() | calls one_hidden_variable_plan, runtime, resize, n; guard check(drain(all) == expected_assignments &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 306–306](../../../../../tests/unit/fragment_cursor_test.cpp#L306) | Explanatory comments or spacing. |  |
| [B0043 · 307–398](../../../../../tests/unit/fragment_cursor_test.cpp#L307) | Callable definition: void local_fragments_and_full_physical_subtrees() | calls local_child_plan, runtime, resize, n; guard check(drain(local) == expected_local_output &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 399–399](../../../../../tests/unit/fragment_cursor_test.cpp#L399) | Explanatory comments or spacing. |  |
| [B0045 · 400–437](../../../../../tests/unit/fragment_cursor_test.cpp#L400) | Callable definition: void physical_subtree_can_include_nodes_outside_c_star() | calls outside_c_star_child_plan, check, enumeration, size; guard check(plan.enumeration().steps.size() == 1 &&; growth insert, resize; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 438–438](../../../../../tests/unit/fragment_cursor_test.cpp#L438) | Explanatory comments or spacing. |  |
| [B0047 · 439–538](../../../../../tests/unit/fragment_cursor_test.cpp#L439) | Callable definition: void depth_three_shared_hidden_variable_and_factor_subsets() | calls depth_three_plan, runtime, resize, n; guard check(drain(all) == expected_full && reference_full == expected_full,; growth insert, resize; 3 loop sites; source comment (unverified): // The root factor survives for z=10 because y=100 or y=101 has a complete · [reviewed contract](#b0047) |
| [B0048 · 539–539](../../../../../tests/unit/fragment_cursor_test.cpp#L539) | Explanatory comments or spacing. |  |
| [B0049 · 540–613](../../../../../tests/unit/fragment_cursor_test.cpp#L540) | Callable definition: void shared_factor_values_and_generalized_products() | calls shared, shared_siblings_plan, insert, n; guard check(drain(siblings) == Relation{{n(1), n(10), n(100)},; growth insert, push_back; 9 loop sites · [reviewed contract](#b0049) |
| [B0050 · 614–614](../../../../../tests/unit/fragment_cursor_test.cpp#L614) | Explanatory comments or spacing. |  |
| [B0051 · 615–670](../../../../../tests/unit/fragment_cursor_test.cpp#L615) | Callable definition: void self_join_aliases_keep_positive_support_during_delete() | calls self_join_plan, runtime, resize, n; guard check(after_database.tables\[0\].erase(first) == 1,; growth insert, resize · [reviewed contract](#b0051) |
| [B0052 · 671–671](../../../../../tests/unit/fragment_cursor_test.cpp#L671) | Explanatory comments or spacing. |  |
| [B0053 · 672–727](../../../../../tests/unit/fragment_cursor_test.cpp#L672) | Callable definition: void typed_bindings_nullary_values_and_constant_routes() | calls typed, typed_plan, n, s; guard check(drain(typed_witness) == Relation{first},; growth insert · [reviewed contract](#b0053) |
| [B0054 · 728–728](../../../../../tests/unit/fragment_cursor_test.cpp#L728) | Explanatory comments or spacing. |  |
| [B0055 · 729–808](../../../../../tests/unit/fragment_cursor_test.cpp#L729) | Callable definition: void journal_commit_rollback_and_facade_lifetimes() | calls runtime, one_hidden_variable_plan, insert, n; guard check(pending.preview().physical_changed && pending.support().native_changed &&; returns transition.handle.role == SupportRole::visible &&; growth emplace, insert; 1 loop sites · [reviewed contract](#b0055) |
| [B0056 · 809–811](../../../../../tests/unit/fragment_cursor_test.cpp#L809) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0056) |
| [B0057 · 812–827](../../../../../tests/unit/fragment_cursor_test.cpp#L812) | Callable definition: int main() | calls hidden_bindings_project_without_multiplying_rows, local_fragments_and_full_physical_subtrees, physical_subtree_can_include_nodes_outside_c_star, depth_three_shared_hidden_variable_and_factor_subsets; returns 1 · [reviewed contract](#b0057) |

## B0001

[Lines 1–20](../../../../../tests/unit/fragment_cursor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:2999343de4a1f0542bda9c2c111856a2621e77b900d06b8b9ed1ee642fdcd25b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare fragment_cursor_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", "evaluator.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/fragment_cursor_test.cpp](../../../../../tests/unit/fragment_cursor_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–23](../../../../../tests/unit/fragment_cursor_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a test-local assertion gate for the fragment cursor fixture. |
| inputs / outputs | A boolean condition and diagnostic string are supplied; the function returns normally for true and has no result value. |
| invariants | Only false selects the failure path; it makes no product-runtime assertion by itself. |
| ownership | The helper borrows the message for the call and retains no fixture state. |
| failure | False throws std::runtime_error with the supplied message. |
| cost | One condition branch; exception construction occurs only on failure, while callers may construct the message before the call. |
| Design | [tests/unit/fragment_cursor_test.cpp § L21-L23](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0004

[Lines 25–35](../../../../../tests/unit/fragment_cursor_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
expect_error(Action&& action
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that one supplied operation throws crown::Error with the requested code. |
| inputs / outputs | A callable and expected code view are inputs; a matching caught Error produces normal return. |
| invariants | Only crown::Error is caught; its code() must equal the caller-supplied code. The helper does not classify errors beyond that comparison. |
| ownership | The callable and code view are borrowed for the call; no cursor or runtime is retained. |
| failure | A mismatched code fails through check(); no caught Error throws std::runtime_error. Other exception types propagate. |
| cost | Invokes the callable once and compares one code on the exceptional path; no cost bound is claimed for the callable. |
| Design | [tests/unit/fragment_cursor_test.cpp § L25-L35](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L294-L303](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0006

[Lines 37–37](../../../../../tests/unit/fragment_cursor_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one signed 64-bit fixture value to the public Value alternative. |
| inputs / outputs | One std::int64_t enters and one Value is returned. |
| invariants | No numeric conversion, range policy, or validation beyond the return conversion is tested here. |
| ownership | The scalar is stored by value. |
| failure | No test-local failure branch is present. |
| cost | One scalar conversion. |
| Design | [tests/unit/fragment_cursor_test.cpp § L37-L37](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0007

[Lines 38–38](../../../../../tests/unit/fragment_cursor_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one string fixture value to Value. |
| inputs / outputs | An owning std::string parameter enters and a Value is returned. |
| invariants | The helper does not normalize text or validate a schema. |
| ownership | The string parameter is by value and is returned into the Value object; no separate fixture owner is retained. |
| failure | No test-local failure branch is present. |
| cost | One value construction; allocation behavior for string storage is not asserted. |
| Design | [tests/unit/fragment_cursor_test.cpp § L38-L38](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0008

[Lines 39–39](../../../../../tests/unit/fragment_cursor_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value day(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a date literal for typed fragment fixtures. |
| inputs / outputs | A string view enters; Date::parse result is converted to Value. |
| invariants | The helper delegates date validity and representation to Date::parse. |
| ownership | The view is borrowed only during parsing; the returned Value owns its scalar value. |
| failure | Any Date::parse failure propagates; no code is asserted here. |
| cost | One parser call for one scalar; no parser complexity claim. |
| Design | [tests/unit/fragment_cursor_test.cpp § L39-L39](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0009

[Lines 40–40](../../../../../tests/unit/fragment_cursor_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value decimal(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a decimal literal for typed fragment fixtures. |
| inputs / outputs | A string view enters; Decimal::parse result is converted to Value. |
| invariants | The helper delegates decimal syntax and scale behavior to Decimal::parse. |
| ownership | The view is borrowed only during parsing; the returned Value owns its scalar value. |
| failure | Any Decimal::parse failure propagates; no code is asserted here. |
| cost | One parser call for one scalar; no parser complexity claim. |
| Design | [tests/unit/fragment_cursor_test.cpp § L40-L40](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0011

[Lines 42–54](../../../../../tests/unit/fragment_cursor_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor& cursor)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a fragment result cursor into the test’s set-valued Relation while checking cursor output basics. |
| inputs / outputs | A borrowed SupportRuntime::ResultCursor enters; a Relation of exported rows is returned. |
| invariants | Every yielded row must have the cursor layout token and insert as a new Relation member; exhaustion must leave state exhausted and inactive, and another next() must remain empty. |
| ownership | The cursor is borrowed and not closed here; returned exported rows are retained by the Relation. |
| failure | Any failed check throws std::runtime_error; exceptions from next() or export_row propagate. |
| cost | Calls next() once per emitted row plus the terminal and repeat-empty calls, and stores all emitted rows; output size is fixture-dependent, with no public delay or memory guarantee. |
| Design | [tests/unit/fragment_cursor_test.cpp § L42-L53](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0013

[Lines 56–63](../../../../../tests/unit/fragment_cursor_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_schema(const storage::TupleLayout& layout
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check output arity and positional variable IDs in a cursor descriptor. |
| inputs / outputs | A borrowed TupleLayout, expected VariableId vector, and context string enter; no value is returned. |
| invariants | It checks field count and that field i has the expected variable at i; it does not check scalar types. |
| ownership | All three inputs are borrowed for the call. |
| failure | Wrong arity or position fails through check() with std::runtime_error. |
| cost | One size comparison and one field comparison per expected variable. |
| Design | [tests/unit/fragment_cursor_test.cpp § L56-L63](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0015

[Lines 65–72](../../../../../tests/unit/fragment_cursor_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04_assignments(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the full-variable reference assignment relation used as the fragment cursor oracle. |
| inputs / outputs | Catalog, Query, and Database are borrowed; a copied Query with every variable placed in its head is evaluated and returned as Relation. |
| invariants | The copied head is ordered by the query.variables index; this helper does not preserve the query’s original projection head. |
| ownership | Catalog and Database are borrowed; the returned Relation owns its rows. |
| failure | Any failure from copying/query construction/reference::evaluate propagates; no error category is asserted. |
| cost | Visits each query variable once to build the head, then pays reference evaluation and relation materialization for this finite fixture. |
| Design | [tests/unit/fragment_cursor_test.cpp § L65-L72](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0017

[Lines 74–92](../../../../../tests/unit/fragment_cursor_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04_project(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Filter full assignments by fixed bindings and project fields in the query head order for the reference oracle. |
| inputs / outputs | A set of assignments, Query, and optional FixedAssignment are borrowed; a projected Relation is returned. |
| invariants | Every fixed binding must equal assignment.at(variable.value); output columns follow query.head and Relation insertion collapses equal output rows. |
| ownership | Inputs are borrowed; the helper creates and owns projected rows in its Relation. |
| failure | An out-of-range variable index or row access failure propagates; the test does not assert an error code for it. |
| cost | Scans each input assignment and its fixed/head entries, materializing projected rows; cost follows these finite fixture sizes. |
| Design | [tests/unit/fragment_cursor_test.cpp § L74-L92](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0019

[Lines 94–98](../../../../../tests/unit/fragment_cursor_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void insert(PhysicalRuntime& runtime
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one fixture insert and reject an event that did not change physical input membership. |
| inputs / outputs | Runtime, mutable sequence, table ID, and owning Row enter; the sequence increments before apply and no value is returned. |
| invariants | The helper always submits SetOperation::insert and requires result.input.physical_changed. |
| ownership | Runtime and sequence are borrowed; the submitted Row is passed to apply by the initializer expression. |
| failure | A nonchanging insert fails through check() with std::runtime_error; apply failures propagate. |
| cost | One sequence increment, one apply call, and one boolean check. |
| Design | [tests/unit/fragment_cursor_test.cpp § L94-L98](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0021

[Lines 100–109](../../../../../tests/unit/fragment_cursor_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan one_hidden_variable_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a one-table plan whose query exposes x and hides z. |
| inputs / outputs | No parameters enter; the helper returns planner::lower_tree for a two-int64-column r table and one native node. |
| invariants | The query head contains only VariableId{0}; the tree scope contains both variables. |
| ownership | Catalog, Query, and tree are local values; the returned plan owns its plan data. |
| failure | No test-local error is asserted; planner::lower_tree failure propagates. |
| cost | Builds a fixed two-field fixture and invokes lowering once. |
| Design | [tests/unit/fragment_cursor_test.cpp § L100-L109](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L252-L303](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0022

[Lines 110–113](../../../../../tests/unit/fragment_cursor_test.cpp#L110); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L110-L113:sha256:d054bc9ce5e7330984be7e672cc856d4b464b9d6e9fd7e55381612df3628856d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: The selected local fragment is S(x,z,y). R(a,x) is its outside parent and deliberately has no row for x=20. Its separator x is visible, while z is hidden inside the selected child subtree. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/fragment_cursor_test.cpp](../../../../../tests/unit/fragment_cursor_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 114–128](../../../../../tests/unit/fragment_cursor_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan local_child_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct parent r(a,x) and selected child s(x,z,y) for local-fragment versus whole-query checks. |
| inputs / outputs | No parameters enter; returns a plan lowered from two native relations and the declared two-node tree. |
| invariants | The query head is x,y; the child subtree also carries z, and the fixture comment identifies x as its separator. |
| ownership | The catalog, query, and tree are local; the returned plan is the fixture owner. |
| failure | No failure category is asserted; lowering failure propagates. |
| cost | Creates two small schema descriptors and lowers once; no data-dependent runtime cost is measured. |
| Design | [tests/unit/fragment_cursor_test.cpp § L114-L128](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L307-L398](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0025

[Lines 130–143](../../../../../tests/unit/fragment_cursor_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan outside_c_star_child_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a two-relation plan where s(z,y) is a physical child while enumeration names only the root. |
| inputs / outputs | No parameters enter; returns the plan produced by lowering the two-node query/tree. |
| invariants | The query head is x, while the native child also has y; its relation is outside the selected enumeration node as tested by the caller. |
| ownership | Inputs are local fixture values; returned PhysicalPlan owns the lowered plan. |
| failure | No fixture-specific failure is asserted; lowering failure propagates. |
| cost | Fixed two-node setup and one lowering call. |
| Design | [tests/unit/fragment_cursor_test.cpp § L130-L143](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L400-L437](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0027

[Lines 145–163](../../../../../tests/unit/fragment_cursor_test.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan depth_three_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a three-node native chain r→s→t with shared z and y variables. |
| inputs / outputs | No parameters enter; returns the lowered four-variable plan. |
| invariants | The query head contains x only, so z, y and w are hidden. The t atom uses physical term order y,z,w (VariableIds 2,1,3); the tree node scope is the ordered set z,y,w (VariableIds 1,2,3). |
| ownership | The fixture’s local Catalog, Query, and FreeConnexTree are passed to lowering; the returned plan is owned by its caller. |
| failure | No failure category is asserted; lowering failure propagates. |
| cost | Fixed three-node descriptor construction and one lowering call. |
| Design | [tests/unit/fragment_cursor_test.cpp § L145-L163](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L439-L538](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0029

[Lines 165–180](../../../../../tests/unit/fragment_cursor_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan shared_siblings_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct two native sibling factors joined below a generalized parent on shared x. |
| inputs / outputs | No parameters enter; returns a lowered three-variable plan. |
| invariants | Both child scopes contain VariableId{0}; the generalized root lists both child nodes. |
| ownership | Schema/tree values are local; the returned plan is owned by the caller. |
| failure | No fixture-specific failure is asserted; lowering failure propagates. |
| cost | Fixed two-child descriptor setup and one lowering call. |
| Design | [tests/unit/fragment_cursor_test.cpp § L165-L180](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L540-L561](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0031

[Lines 182–200](../../../../../tests/unit/fragment_cursor_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan product_plan(std::size_t arity)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a generalized root over one independent one-column native table per requested fixture position. |
| inputs / outputs | Arity enters; the helper creates matching query variables, atoms, catalog tables, child IDs and native nodes, then returns a lowered plan. |
| invariants | Each generated child has its own VariableId and TableId indexed from zero; no arity validation is performed locally. |
| ownership | Generated vectors and descriptors are local; the returned PhysicalPlan owns its lowered representation. |
| failure | No test-local failure path is asserted; allocation or lowering failures propagate. |
| cost | Fixture construction loops proportional to arity and performs one lowering call; this is not a runtime complexity result. |
| Design | [tests/unit/fragment_cursor_test.cpp § L182-L200](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L563-L612](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0033

[Lines 202–220](../../../../../tests/unit/fragment_cursor_test.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan typed_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the typed one-relation plan used to check witness bindings. |
| inputs / outputs | No parameters enter; returns the lowered plan for int64, string, date, decimal(8,2), and boolean fields. |
| invariants | Only n is in the query head; the native node scope names all five variables. |
| ownership | Schema/query/tree descriptors are local and the plan is returned by value. |
| failure | No failure category is asserted; lowering failure propagates. |
| cost | Creates five fixed field descriptors and lowers once. |
| Design | [tests/unit/fragment_cursor_test.cpp § L202-L220](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L672-L727](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0035

[Lines 222–236](../../../../../tests/unit/fragment_cursor_test.cpp#L222); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan self_join_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build two occurrence aliases of the same r table, sharing x and projecting x only. |
| inputs / outputs | No parameters enter; returns the lowered plan with r_z and r_w aliases over TableId{0}. |
| invariants | The two aliases bind the same source columns to distinct variables z and w; the generalized root joins on x. |
| ownership | Catalog/query/tree are local; returned plan owns its lowering. |
| failure | No failure category is asserted; lowering failure propagates. |
| cost | Fixed two-occurrence descriptor construction and one lowering call. |
| Design | [tests/unit/fragment_cursor_test.cpp § L222-L236](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L615-L670](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0037

[Lines 238–244](../../../../../tests/unit/fragment_cursor_test.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_atom_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a query with a zero-column output and a native atom whose table column is ignored. |
| inputs / outputs | No parameters enter; returns a plan lowered from one string-tag table and an empty query head. |
| invariants | The atom term is IgnoredColumn and no query variable is declared. |
| ownership | Fixture descriptors are local; returned plan is owned by caller. |
| failure | No failure category is asserted; lowering failure propagates. |
| cost | One fixed table/node setup and one lowering call. |
| Design | [tests/unit/fragment_cursor_test.cpp § L238-L244](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L696-L713](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0039

[Lines 246–250](../../../../../tests/unit/fragment_cursor_test.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan constant_plan(bool truth)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an empty-catalog, no-atom constant query from the requested truth value. |
| inputs / outputs | A bool enters; the helper initializes Query.contradiction to !truth and returns the lowered empty-tree plan. The flag selects the constant-false route. |
| invariants | This is a query-constant fixture; no data table is present. |
| ownership | The temporary Catalog and Query are passed by reference during lowering; caller owns the returned plan. |
| failure | No test-local failure category is asserted. |
| cost | One boolean inversion and one lowering call. |
| Design | [tests/unit/fragment_cursor_test.cpp § L246-L250](../../../../../tests/unit/fragment_cursor_test.cpp), [tests/unit/fragment_cursor_test.cpp § L715-L726](../../../../../tests/unit/fragment_cursor_test.cpp), [include/crown/ir/model.hpp § L74-L79](../../../../../include/crown/ir/model.hpp) |

## B0041

[Lines 252–305](../../../../../tests/unit/fragment_cursor_test.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hidden_bindings_project_without_multiplying_rows()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare whole-witness and projected completion cursors for a hidden-variable query, including binding validation. |
| inputs / outputs | A one-table plan and three rows are inserted; witnesses return full (x,z) assignments, completions project x, and fixed z values filter those assignments. |
| invariants | The asserted results are three full assignments; projected x deduplicates duplicate witnesses; z=20 yields two x values, z=10 one, and z=99 none. Repeated binding IDs, wrong-type z, and unknown variable 99 each expect invalid_binding. |
| ownership | PhysicalRuntime owns maintained state; view/cursors are local and explicitly drained; the reference Database and Relation results are test-owned. |
| failure | The three binding-shape failures are checked only for Error code invalid_binding; all other failed checks use the local runtime_error harness. |
| cost | Inserts three rows, enumerates the finite reference/cursor results several times, and materializes each drained Relation; no general delay or storage bound is asserted. |
| Design | [tests/unit/fragment_cursor_test.cpp § L252-L305](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0043

[Lines 307–398](../../../../../tests/unit/fragment_cursor_test.cpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void local_fragments_and_full_physical_subtrees()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare completions for a visible child fragment with whole-query completions and explicit physical-subtree witness cursors. |
| inputs / outputs | The fixture inserts one parent row and two child rows; cursors select VisibleFragment{1}, WitnessFragment root 0 or 1, or an empty node set. |
| invariants | The child C* completion exposes x,y despite the absent outside parent at x=20; its hidden z=20 binding filters to one row, while a binding on outside variable a is ignored locally. Whole-query hidden-z=20 yields empty. Root witnesses join the native root factor r with its one physical child factor s; empty factors yield {{}}. Invalid root/node 99, repeated node 1, and simultaneous root/nodes expect invalid_fragment. |
| ownership | Runtime and view own/retain their respective state; cursor results are drained into owning test Relations, and the view is closed. |
| failure | Only malformed fragment selections are asserted to throw Error with code invalid_fragment; other failures are local runtime_error checks or propagated. |
| cost | Uses three inserted rows, reference evaluation, and finite cursor drains; output materialization is proportional to these fixture results, with no general cursor bound asserted. |
| Design | [tests/unit/fragment_cursor_test.cpp § L307-L398](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0045

[Lines 400–437](../../../../../tests/unit/fragment_cursor_test.cpp#L400); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void physical_subtree_can_include_nodes_outside_c_star()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that witness root traversal follows the physical child even when that node is absent from enumeration C*. |
| inputs / outputs | Two r rows and one s row feed whole-query, root-0, and root-1 witness cursors plus a visible-fragment completion request. |
| invariants | The fixture asserts that enumeration has one step at node 0; whole/root witnesses return only (1,10,100), root 1 exposes (z,y), VisibleFragment{1} expects invalid_fragment, and whole-query fixed z=20 returns empty. |
| ownership | PhysicalRuntime and its view own the fixture state; drained output Relations own exported rows. |
| failure | The invalid visible-fragment request is checked for Error code invalid_fragment; the other assertions use check(). |
| cost | Two source inserts and one child insert, followed by finite scans of the one-result fixture; no general traversal cost claim. |
| Design | [tests/unit/fragment_cursor_test.cpp § L400-L437](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0047

[Lines 439–538](../../../../../tests/unit/fragment_cursor_test.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void depth_three_shared_hidden_variable_and_factor_subsets()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise three-level witness joins, hidden shared bindings, physical subtrees, and exact selected-factor subsets. |
| inputs / outputs | The fixture inserts 4 r, 5 s, and 8 t rows; cursors cover the whole tree, fixed hidden z/y values, middle subtree root 1, factors {0,2}, and leaf factor {2}. |
| invariants | The whole assignment oracle is the six listed rows; z=10,y=100 projects x=1 and z=10,y=300 is empty. The middle subtree emits the six S⋈T rows. Selecting only factors 0 and 2 keeps y=999 because the middle factor is omitted; a binding on omitted variable x is ignored by factor {2}. |
| ownership | Runtime/view own the query state; expected Relations and cursor outputs are test-owned. The test closes the view. |
| failure | No product error code is asserted in this region; mismatches fail through check(). |
| cost | Loads 17 rows, builds explicit reference relations, and drains each finite factor selection into sets; there is no asymptotic join or delay claim. |
| Design | [tests/unit/fragment_cursor_test.cpp § L439-L538](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0049

[Lines 540–613](../../../../../tests/unit/fragment_cursor_test.cpp#L540); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void shared_factor_values_and_generalized_products()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check shared-variable agreement across selected siblings, generalized parent support, and disconnected generalized products. |
| inputs / outputs | The sibling fixture inserts five rows; separate product fixtures use arities 3 and 8 with two values per child, then enumerate full/root and two selected child factors. |
| invariants | The siblings agree only at x=1 and produce two rows; the generalized parent factor contains only x=1. Product expected Relations are constructed by repeated cross products; full and root cursors equal them, and the selected left/right factors expose their two-variable product in left/right order. |
| ownership | Each PhysicalRuntime/view owns one fixture; expected choice vectors and Relations remain test-owned until comparison. |
| failure | No domain error is asserted here; all comparison failures use check(). |
| cost | The test explicitly builds arities 3 and 8, each with two values per child, and materializes full and selected output sets; no general exponential-runtime claim is made. |
| Design | [tests/unit/fragment_cursor_test.cpp § L540-L613](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0051

[Lines 615–670](../../../../../tests/unit/fragment_cursor_test.cpp#L615); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void self_join_aliases_keep_positive_support_during_delete()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare before/after witness and completion cursors when deleting one source row routed through two self-join aliases. |
| inputs / outputs | Two rows for one table are inserted, then a prepared erase of the first row supplies before and after views/cursors. |
| invariants | A04 has four assignments before and one after; the prepared preview has two derivation changes; projected x=1 remains in both snapshots, while fixed z=10,w=20 exists only before. Commit followed by closing both views must leave the runtime ready. |
| ownership | The pending epoch retains before/after snapshot state; views and cursors are local and closed after commit; the reference databases/Relations are test-owned. |
| failure | This function asserts values and readiness only; it names no product error code. |
| cost | Two input rows and one prepared erase; finite before/after cursor results are compared against materialized A04 relations. |
| Design | [tests/unit/fragment_cursor_test.cpp § L615-L670](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0053

[Lines 672–727](../../../../../tests/unit/fragment_cursor_test.cpp#L672); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_bindings_nullary_values_and_constant_routes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise typed witness bindings, nullary native-factor output, empty factor identity, and constant true/false routes. |
| inputs / outputs | Two typed rows cover int64/string/date/decimal/boolean; a tag row populates a nullary atom; separate empty plans represent constants. |
| invariants | The typed binding selects the first row; wrong-type date and decimal bindings expect invalid_binding. Empty nullary input has no whole witness, the empty selected factor set is {{}}; a supported nullary factor and constant true each yield {{}} while constant false is empty. |
| ownership | Each PhysicalRuntime/view/cursor owns or retains only its local fixture state; the source Rows and expected Relations are test values. |
| failure | Only the two wrong-type binding checks assert Error code invalid_binding; the remaining conditions fail through check(). |
| cost | Two typed rows and one nullary row are loaded; each listed cursor is finite and drained, with no broader cardinality guarantee. |
| Design | [tests/unit/fragment_cursor_test.cpp § L672-L727](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0055

[Lines 729–808](../../../../../tests/unit/fragment_cursor_test.cpp#L729); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_commit_rollback_and_facade_lifetimes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check snapshot cursor behavior across commit/rollback and the lifetime of detached views and tuples. |
| inputs / outputs | A prepared physical erase creates before/after views; a SupportRuntime epoch stages two inserts then rolls back; a scoped PhysicalRuntime supplies a detached view and tuple. |
| invariants | Before completion retains x=1 and after witness contains only z=20; the before witness cursor continues after commit with both old assignments. Rollback invalidates staged views, makes its active cursor failed, and later next() expects invalid_cursor; rolled-back runtime output is empty. A saved (7,70) tuple and detached view remain usable after facade destruction. |
| ownership | Pending epoch/views retain snapshot state while active; exported Tuple/View handles are stored in optionals beyond the local facade block and explicitly closed afterward. |
| failure | The post-rollback cursor check expects Error code invalid_cursor; other conditions use check() and no other code is asserted. |
| cost | The fixture uses two-row states, two staged events, and a single detached tuple; cursor drains/materialized sets are finite and do not establish a general history bound. |
| Design | [tests/unit/fragment_cursor_test.cpp § L729-L808](../../../../../tests/unit/fragment_cursor_test.cpp) |

## B0056

[Lines 809–811](../../../../../tests/unit/fragment_cursor_test.cpp#L809); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L809-L811:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in fragment_cursor_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/fragment_cursor_test.cpp](../../../../../tests/unit/fragment_cursor_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0057

[Lines 812–827](../../../../../tests/unit/fragment_cursor_test.cpp#L812); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the eight named fragment cursor fixture functions in sequence and report harness failure status. |
| inputs / outputs | No inputs enter; successful completion prints a label and returns 0, while a caught std::exception prints what() and returns 1. |
| invariants | The source establishes call order only; this contract records no execution result. |
| ownership | All fixture values live inside the called functions; the caught exception is borrowed by const reference while printing. |
| failure | The harness catches std::exception, not every possible termination mode; there is no product error code assertion at this boundary. |
| cost | Calls eight test functions sequentially; their own finite fixture costs are not summarized as a runtime bound. |
| Design | [tests/unit/fragment_cursor_test.cpp § L812-L827](../../../../../tests/unit/fragment_cursor_test.cpp) |
