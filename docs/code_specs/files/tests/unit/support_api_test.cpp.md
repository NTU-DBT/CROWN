# `tests/unit/support_api_test.cpp` — block usage map

[Source](../../../../../tests/unit/support_api_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `26e921bb5eac216ba4397cbe5a87be99b6d9d135065853775634c7f7d417cb5d`. 615 lines partitioned into 55 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/support_api_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../../tests/unit/support_api_test.cpp#L22) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 25–25](../../../../../tests/unit/support_api_test.cpp#L25) | Explanatory comments or spacing. |  |
| [B0004 · 26–36](../../../../../tests/unit/support_api_test.cpp#L26) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::string; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 37–37](../../../../../tests/unit/support_api_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0006 · 38–38](../../../../../tests/unit/support_api_test.cpp#L38) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 39–39](../../../../../tests/unit/support_api_test.cpp#L39) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0007) |
| [B0008 · 40–40](../../../../../tests/unit/support_api_test.cpp#L40) | Callable definition: Value date(std::string_view value) | calls Date::parse; returns Date::parse(value) · [reviewed contract](#b0008) |
| [B0009 · 41–41](../../../../../tests/unit/support_api_test.cpp#L41) | Callable definition: Value decimal(std::string_view value) | calls Decimal::parse; returns Decimal::parse(value) · [reviewed contract](#b0009) |
| [B0010 · 42–42](../../../../../tests/unit/support_api_test.cpp#L42) | Explanatory comments or spacing. |  |
| [B0011 · 43–51](../../../../../tests/unit/support_api_test.cpp#L43) | Callable definition: PhysicalPlan unary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0011) |
| [B0012 · 52–52](../../../../../tests/unit/support_api_test.cpp#L52) | Explanatory comments or spacing. |  |
| [B0013 · 53–64](../../../../../tests/unit/support_api_test.cpp#L53) | Callable definition: PhysicalPlan typed_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0013) |
| [B0014 · 65–65](../../../../../tests/unit/support_api_test.cpp#L65) | Explanatory comments or spacing. |  |
| [B0015 · 66–79](../../../../../tests/unit/support_api_test.cpp#L66) | Callable definition: PhysicalPlan generalized_pair_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0015) |
| [B0016 · 80–80](../../../../../tests/unit/support_api_test.cpp#L80) | Explanatory comments or spacing. |  |
| [B0017 · 81–97](../../../../../tests/unit/support_api_test.cpp#L81) | Callable definition: PhysicalPlan nested_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0017) |
| [B0018 · 98–98](../../../../../tests/unit/support_api_test.cpp#L98) | Explanatory comments or spacing. |  |
| [B0019 · 99–111](../../../../../tests/unit/support_api_test.cpp#L99) | Callable definition: PhysicalPlan native_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0019) |
| [B0020 · 112–112](../../../../../tests/unit/support_api_test.cpp#L112) | Explanatory comments or spacing. |  |
| [B0021 · 113–115](../../../../../tests/unit/support_api_test.cpp#L113) | Callable definition: const NodeSupportSnapshot& node(const SupportSnapshot& snapshot, NodeId id) | calls at; returns snapshot.nodes.at(id.value) · [reviewed contract](#b0021) |
| [B0022 · 116–116](../../../../../tests/unit/support_api_test.cpp#L116) | Explanatory comments or spacing. |  |
| [B0023 · 117–123](../../../../../tests/unit/support_api_test.cpp#L117) | Callable definition: const ProjectionKeySnapshot* key_with_values( const std::vector&lt;ProjectionKeySnapshot&gt;& keys, const Row& values) | calls std::find_if, begin, end, values; returns key.key.values() == values; found == keys.end() ? nullptr : &*found · [reviewed contract](#b0023) |
| [B0024 · 124–124](../../../../../tests/unit/support_api_test.cpp#L124) | Explanatory comments or spacing. |  |
| [B0025 · 125–133](../../../../../tests/unit/support_api_test.cpp#L125) | Callable definition: bool zero(const SupportMetrics& m) | calls ; returns m.work == 0 && m.copied_rows == 0 && m.copied_index_memberships == 0 && · [reviewed contract](#b0025) |
| [B0026 · 134–134](../../../../../tests/unit/support_api_test.cpp#L134) | Explanatory comments or spacing. |  |
| [B0027 · 135–141](../../../../../tests/unit/support_api_test.cpp#L135) | Callable definition: bool has_transition(const SupportEpoch& epoch, NodeId node_id, SupportRole role, SetOperation operation, const Row& tuple) | calls std::any_of, begin, end, values; returns std::any_of(epoch.transitions.begin(), epoch.transitions.end(), \[&\](const auto& event) {; event.han… · [reviewed contract](#b0027) |
| [B0028 · 142–142](../../../../../tests/unit/support_api_test.cpp#L142) | Explanatory comments or spacing. |  |
| [B0029 · 143–153](../../../../../tests/unit/support_api_test.cpp#L143) | Callable definition: void check_journaled_mutation(const SupportEpoch& epoch) | calls check, size; guard check(m.copied_rows == 0 && m.copied_index_memberships == 0 && · [reviewed contract](#b0029) |
| [B0030 · 154–157](../../../../../tests/unit/support_api_test.cpp#L154) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0030) |
| [B0031 · 158–163](../../../../../tests/unit/support_api_test.cpp#L158) | Callable definition: std::vector&lt;RecordView&gt; record_views(const NodeSupportSnapshot& state) | calls emplace_back, crown::storage::export_row, values; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 164–164](../../../../../tests/unit/support_api_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0033 · 165–169](../../../../../tests/unit/support_api_test.cpp#L165) | Callable definition: std::vector&lt;KeyView&gt; key_views(const std::vector&lt;ProjectionKeySnapshot&gt;& keys) | calls emplace_back, crown::storage::export_row, values; returns result; growth emplace_back; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 170–170](../../../../../tests/unit/support_api_test.cpp#L170) | Explanatory comments or spacing. |  |
| [B0035 · 171–175](../../../../../tests/unit/support_api_test.cpp#L171) | Callable definition: std::vector&lt;Row&gt; row_views(const std::vector&lt;storage::Tuple&gt;& tuples) | calls push_back, crown::storage::export_row, values; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 176–176](../../../../../tests/unit/support_api_test.cpp#L176) | Explanatory comments or spacing. |  |
| [B0037 · 177–192](../../../../../tests/unit/support_api_test.cpp#L177) | Callable definition: void compare_canonical_state(const SupportSnapshot& left, const SupportSnapshot& right) | calls check, size, record_views, row_views; guard check(left.sequence == right.sequence && left.has_answer == right.has_answer,; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 193–193](../../../../../tests/unit/support_api_test.cpp#L193) | Explanatory comments or spacing. |  |
| [B0039 · 194–205](../../../../../tests/unit/support_api_test.cpp#L194) | Callable definition: void checked_projection_counters() | calls max, check, increment_support, expect_error; guard check(increment_support({above_double_exact}).value == above_double_exact + 1U, · [reviewed contract](#b0039) |
| [B0040 · 206–206](../../../../../tests/unit/support_api_test.cpp#L206) | Explanatory comments or spacing. |  |
| [B0041 · 207–256](../../../../../tests/unit/support_api_test.cpp#L207) | Callable definition: void options_and_validation_are_checked_before_commit() | calls unary_plan, expect_error, runtime, owner; guard check(runtime.sequence() == 0 && runtime.owner() == owner && !runtime.has_answer() &&; growth insert · [reviewed contract](#b0041) |
| [B0042 · 257–257](../../../../../tests/unit/support_api_test.cpp#L257) | Explanatory comments or spacing. |  |
| [B0043 · 258–360](../../../../../tests/unit/support_api_test.cpp#L258) | Callable definition: void noops_sequences_metrics_and_owned_handles() | calls generalized_pair_plan, runtime, n, apply; guard check(first.native_changed && first.sequence == 1 && !first.has_answer,; returns event.handle.node == NodeId{1} && event.handle.role == SupportRole::parent_support &&; growth insert; source comment (unverified): // The right native scope is sorted by VariableId as {y, z}. · [reviewed contract](#b0043) |
| [B0044 · 361–361](../../../../../tests/unit/support_api_test.cpp#L361) | Explanatory comments or spacing. |  |
| [B0045 · 362–401](../../../../../tests/unit/support_api_test.cpp#L362) | Callable definition: void support_limit_failure_is_atomic_and_retryable() | calls runtime, unary_plan, apply, n; guard check(first.native_changed && key, "support counter reaches configured limit exactly");; growth insert · [reviewed contract](#b0045) |
| [B0046 · 402–402](../../../../../tests/unit/support_api_test.cpp#L402) | Explanatory comments or spacing. |  |
| [B0047 · 403–440](../../../../../tests/unit/support_api_test.cpp#L403) | Callable definition: void work_limit_boundaries_and_atomic_retry() | calls probe, unary_plan, apply, n; guard check(measured &gt; 0, "a real reference mutation reports nonzero charged work");; growth insert · [reviewed contract](#b0047) |
| [B0048 · 441–441](../../../../../tests/unit/support_api_test.cpp#L441) | Explanatory comments or spacing. |  |
| [B0049 · 442–489](../../../../../tests/unit/support_api_test.cpp#L442) | Callable definition: void fifo_and_lifo_produce_same_canonical_state() | calls nested_plan, fifo, lifo, n; guard check(a.has_answer == b.has_answer, "FIFO/LIFO differ before multi-key propagation");; growth insert; 1 loop sites · [reviewed contract](#b0049) |
| [B0050 · 490–490](../../../../../tests/unit/support_api_test.cpp#L490) | Explanatory comments or spacing. |  |
| [B0051 · 491–547](../../../../../tests/unit/support_api_test.cpp#L491) | Callable definition: void reference_storage_snapshot_copy_owns_and_preserves_ids() | calls native_join_plan, original, nodes, table; guard check(inserted.inserted && original_table.indices().size() &gt; 0,; returns a.value &lt; b.value; growth insert · [reviewed contract](#b0051) |
| [B0052 · 548–548](../../../../../tests/unit/support_api_test.cpp#L548) | Explanatory comments or spacing. |  |
| [B0053 · 549–596](../../../../../tests/unit/support_api_test.cpp#L549) | Callable definition: void constant_routes_and_runtime_moves() | calls planner::lower_tree, true_runtime, check, route; guard check(true_plan.route() == PhysicalRoute::constant_true && true_plan.inputs().empty() &&; growth insert · [reviewed contract](#b0053) |
| [B0054 · 597–599](../../../../../tests/unit/support_api_test.cpp#L597) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0054) |
| [B0055 · 600–615](../../../../../tests/unit/support_api_test.cpp#L600) | Callable definition: int main() | calls checked_projection_counters, options_and_validation_are_checked_before_commit, noops_sequences_metrics_and_owned_handles, support_limit_failure_is_atomic_and_retryable; returns 1; 0 · [reviewed contract](#b0055) |

## B0001

[Lines 1–21](../../../../../tests/unit/support_api_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:d233c85701ddc42aded84c4f5dca3ca50d5513180f6d099b3dd253c815f9ce53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_api_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/support.hpp", "crown/storage/physical.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;tuple&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_api_test.cpp](../../../../../tests/unit/support_api_test.cpp), [docs/runtime_support.md](../../../../runtime_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 22–24](../../../../../tests/unit/support_api_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a support API fixture assertion when its condition is false. |
| inputs / outputs | Takes Boolean and borrowed diagnostic; returns void. |
| invariants | Does not catch failures from the expression being checked. |
| ownership | Borrows message for the call and retains no state. |
| failure | False throws std::runtime_error. |
| cost | One branch; exception construction on failure. |
| Design | tests/unit/support_api_test.cpp:22-24 |

## B0004

[Lines 26–36](../../../../../tests/unit/support_api_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one support API action to throw crown::Error with an exact code. |
| inputs / outputs | Takes an Action&& parameter and borrowed expected code; invokes the named action once as an lvalue. |
| invariants | Catches only crown::Error; wrong code fails through check, no error throws runtime_error, other exceptions propagate. |
| ownership | The callable and code view are used only during this call; invocation does not use std::forward. |
| failure | Wrong code or no crown::Error becomes std::runtime_error. |
| cost | One action invocation and expected-code comparison. |
| Design | tests/unit/support_api_test.cpp:26-36 |

## B0006

[Lines 38–38](../../../../../tests/unit/support_api_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct integer scalar Values for support fixtures. |
| inputs / outputs | Takes one int64 and returns Value. |
| invariants | Preserves the supplied integer value/tag. |
| ownership | Returns scalar by value. |
| failure | No conversion failure is exercised. |
| cost | One scalar Value construction. |
| Design | tests/unit/support_api_test.cpp:38-38 |

## B0007

[Lines 39–39](../../../../../tests/unit/support_api_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct string scalar Values for support fixtures. |
| inputs / outputs | Takes a string by value and returns Value. |
| invariants | Preserves supplied string value/tag. |
| ownership | Returned Value owns its string payload. |
| failure | No conversion failure is exercised. |
| cost | One scalar Value construction. |
| Design | tests/unit/support_api_test.cpp:39-39 |

## B0008

[Lines 40–40](../../../../../tests/unit/support_api_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value date(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse date literals used in the typed support fixture. |
| inputs / outputs | Takes a borrowed string view and returns Date::parse(value) wrapped as Value. |
| invariants | Format/calendar acceptance is delegated to Date::parse. |
| ownership | Returned scalar is by value; view is used during parse. |
| failure | Invalid date parse may throw; this helper does not translate it. |
| cost | One date parse and Value construction. |
| Design | tests/unit/support_api_test.cpp:40-40 |

## B0009

[Lines 41–41](../../../../../tests/unit/support_api_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value decimal(std::string_view value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse decimal literals used in the typed support fixture. |
| inputs / outputs | Takes a borrowed view and returns Decimal::parse(value) wrapped as Value. |
| invariants | Syntax/scale acceptance is delegated to Decimal::parse. |
| ownership | Returned scalar is by value; view is used during parse. |
| failure | Invalid decimal parse may throw; this helper does not translate it. |
| cost | One decimal parse and Value construction. |
| Design | tests/unit/support_api_test.cpp:41-41 |

## B0011

[Lines 43–51](../../../../../tests/unit/support_api_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the one-column unary native plan for counter, option, retry and move cases. |
| inputs / outputs | Returns plan for catalog v1, unary(x int64), one atom/head variable 0, one native node. |
| invariants | Fixture has one input and no child edge. |
| ownership | Returned PhysicalPlan owns its compiled fixture. |
| failure | lower_tree failure propagates; fixed fixture is intended to succeed. |
| cost | One lower_tree call over one table/node. |
| Design | tests/unit/support_api_test.cpp:43-51, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0013

[Lines 53–64](../../../../../tests/unit/support_api_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan typed_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a native plan for string/date/decimal scalar-tag checks. |
| inputs / outputs | Returns version-2 typed(word string, day date, amount decimal(8,2)) table, matching three variables/head outputs and one native node. |
| invariants | Physical columns map in order to variables 0,1,2. |
| ownership | Returned PhysicalPlan owns its compiled fixture. |
| failure | lower_tree failure propagates; this factory contains no invalid schema. |
| cost | One lower_tree call for one three-field table/node. |
| Design | tests/unit/support_api_test.cpp:53-64, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0015

[Lines 66–79](../../../../../tests/unit/support_api_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan generalized_pair_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the generalized-y two-leaf fixture for propagation and handle checks. |
| inputs / outputs | Returns version-4 left(x,y)/right(y,z), matching atoms with output y only, generalized y root over native left/right leaves. |
| invariants | Root children are nodes 1 and 2; separator y occupies fixture-declared positions. |
| ownership | Returned plan owns compiled catalog/query/tree. |
| failure | lower_tree failure propagates; no negative fixture is present. |
| cost | One fixed three-node lowering. |
| Design | tests/unit/support_api_test.cpp:66-79, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0017

[Lines 81–97](../../../../../tests/unit/support_api_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nested_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the nested generalized-x fixture for FIFO/LIFO comparison. |
| inputs / outputs | Returns version-6 b(x,y), c(y), g(x), output x; generalized x root, native b child with nested native c, and native g child. |
| invariants | Node IDs and child links are the exact four-node topology in the fixture. |
| ownership | Returned plan owns compiled fixture. |
| failure | lower_tree failure propagates; topology validity is not tested inside this factory. |
| cost | One fixed four-node lowering. |
| Design | tests/unit/support_api_test.cpp:81-97, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0019

[Lines 99–111](../../../../../tests/unit/support_api_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan native_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build two-native-node x,y-to-y,z join plan for storage snapshot-copy checks. |
| inputs / outputs | Returns version-4 left(x,y)/right(y,z), ordered output x,y,z, left-parent/right-child native tree. |
| invariants | Parent and child share separator y; no rows are inserted here. |
| ownership | Returned plan owns compiled fixture. |
| failure | lower_tree failure propagates; fixed tree is expected to be valid. |
| cost | One fixed two-node lowering. |
| Design | tests/unit/support_api_test.cpp:99-111, [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp) |

## B0021

[Lines 113–115](../../../../../tests/unit/support_api_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const NodeSupportSnapshot& node(const SupportSnapshot& snapshot, NodeId id) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one node snapshot by public NodeId value. |
| inputs / outputs | Takes borrowed snapshot and id; returns const reference to nodes.at(id.value). |
| invariants | Uses bounds-checked vector access rather than searching the node field. |
| ownership | Returned reference is tied to snapshot lifetime. |
| failure | Out-of-range id throws std::out_of_range without local translation. |
| cost | One bounds-checked access. |
| Design | tests/unit/support_api_test.cpp:113-115, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0023

[Lines 117–123](../../../../../tests/unit/support_api_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ProjectionKeySnapshot* key_with_values(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the first projection-key snapshot whose tuple values equal a requested Row. |
| inputs / outputs | Takes borrowed key vector and Row; returns pointer to match or null. |
| invariants | Equality is on key.key.values(); support count and handle are not compared. |
| ownership | Returned pointer borrows vector element and depends on vector lifetime/stability. |
| failure | Missing key returns null. |
| cost | One linear find_if scan. |
| Design | tests/unit/support_api_test.cpp:117-123, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0025

[Lines 125–133](../../../../../tests/unit/support_api_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool zero(const SupportMetrics& m) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that all 20 explicitly listed work/copy/transition/storage/journal/queue metrics are zero. |
| inputs / outputs | Takes borrowed SupportMetrics and returns Boolean over fields shown in source. |
| invariants | Only the fields in this expression are covered; later/unlisted metrics are not implicitly included. |
| ownership | Metrics record is borrowed. |
| failure | No exception path is introduced. |
| cost | At most 20 scalar comparisons with short-circuit evaluation. |
| Design | tests/unit/support_api_test.cpp:125-133, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0027

[Lines 135–141](../../../../../tests/unit/support_api_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool has_transition(const SupportEpoch& epoch, NodeId node_id, SupportRole role, SetOperation operation, const Row& tuple) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check for a captured transition matching node, role, operation and row values. |
| inputs / outputs | Takes borrowed epoch/row and scalar selectors; returns whether any event matches all four conditions. |
| invariants | Tuple comparison uses event.tuple.values(); handle owner and tuple ID are not compared. |
| ownership | All input objects are borrowed. |
| failure | No match returns false. |
| cost | Linear any_of scan with short-circuit on first match. |
| Design | tests/unit/support_api_test.cpp:135-141, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0029

[Lines 143–153](../../../../../tests/unit/support_api_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_journaled_mutation(const SupportEpoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert selected accounting conditions for a real journaled support mutation. |
| inputs / outputs | Checks zero copied-state metrics, journal sequence equal epoch sequence, positive journal-record count equal record vector size, and positive storage/metadata changes. |
| invariants | Applies only to epochs passed by this test; not a proof of all runtime updates. |
| ownership | Borrows epoch and optional journal. |
| failure | Any unmet condition throws std::runtime_error; missing journal fails the combined check. |
| cost | Three grouped check() calls inspect the listed scalar metrics and journal properties; the helper creates no journal. |
| Design | tests/unit/support_api_test.cpp:143-153, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0030

[Lines 154–157](../../../../../tests/unit/support_api_test.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L157:sha256:b9edeb7e2213e5ec25b8e1a155a1bcc20343db032fc3bd67e8ae943c2e894a27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare support_api_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/support_api_test.cpp](../../../../../tests/unit/support_api_test.cpp), [docs/runtime_support.md](../../../../runtime_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0031

[Lines 158–163](../../../../../tests/unit/support_api_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<RecordView> record_views(const NodeSupportSnapshot& state) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project snapshot records into owning row/satisfied/child-flag/survival tuples. |
| inputs / outputs | Takes borrowed node snapshot; returns one RecordView per record. |
| invariants | Rows are exported from tuple values; listed metadata is copied. |
| ownership | Output vector and Rows own data; input is borrowed. |
| failure | Allocation or row-export errors propagate. |
| cost | One pass and one projected tuple per record. |
| Design | tests/unit/support_api_test.cpp:158-163, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0033

[Lines 165–169](../../../../../tests/unit/support_api_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<KeyView> key_views(const std::vector<ProjectionKeySnapshot>& keys) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project key snapshots into owning row/support-count pairs. |
| inputs / outputs | Takes borrowed key vector and returns one pair per key. |
| invariants | Row comes from exported key values and count from exact support.value. |
| ownership | Output owns rows/pairs; input is borrowed. |
| failure | Allocation or export errors propagate. |
| cost | One pass and one output pair per key. |
| Design | tests/unit/support_api_test.cpp:165-169, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0035

[Lines 171–175](../../../../../tests/unit/support_api_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> row_views(const std::vector<storage::Tuple>& tuples) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export storage tuple values into owning Rows for equality checks. |
| inputs / outputs | Takes borrowed tuple vector and returns one Row per tuple. |
| invariants | Exports tuple.values(); tuple handles/storage ownership are not returned. |
| ownership | Output rows own scalar values; tuple vector is borrowed. |
| failure | Allocation or export failures propagate. |
| cost | One pass and one row export per tuple. |
| Design | tests/unit/support_api_test.cpp:171-175, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp) |

## B0037

[Lines 177–192](../../../../../tests/unit/support_api_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_canonical_state(const SupportSnapshot& left, const SupportSnapshot& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require two support snapshots to agree on fields compared by the FIFO/LIFO test. |
| inputs / outputs | Checks sequence, answer, node count/identity/kind, projected records, survivors, parent keys, visible-key presence and visible keys when present. |
| invariants | Compares returned vector order; does not compare metrics, transitions, owner IDs or journals. |
| ownership | Snapshots are borrowed; projected row/key vectors are local owning temporaries. |
| failure | A mismatch throws std::runtime_error through check. |
| cost | Passes over nodes and records/keys via projection helpers; this is fixture work, not a production bound. |
| Design | tests/unit/support_api_test.cpp:177-192, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0039

[Lines 194–205](../../../../../tests/unit/support_api_test.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void checked_projection_counters() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected exact support-counter increment/decrement boundaries and underflow errors. |
| inputs / outputs | Uses 2^53+117, uint64 max-1/max, increment of zero with limit zero, and decrement of one/zero. |
| invariants | Expects exact increment above 2^53 and to max; support_overflow at max/zero limit; decrement one to zero; runtime_contract when decrementing zero. |
| ownership | Only scalar counter values are retained. |
| failure | Two cases expect support_overflow; underflow expects runtime_contract. |
| cost | Six counter calls on fixed values. |
| Design | tests/unit/support_api_test.cpp:194-205, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0041

[Lines 207–256](../../../../../tests/unit/support_api_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void options_and_validation_are_checked_before_commit() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check option rejection, invalid update envelopes, generalized-write admission, typed scalar tags, and state preservation on selected failures. |
| inputs / outputs | Uses unary, generalized-pair and typed plans. Rejects support limit 0, order 255, sequence 2, node 7, wrong unary arity, operation 255, generalized root write, and a typed row with day supplied as string; then accepts (é, 2024-02-29, 123.40) and checks changed-value lookups. |
| invariants | Unary runtime remains sequence 0/same owner/no answer/no row after invalid envelopes; generalized runtime stays sequence 0/no answer; typed exact decimal/date/binary string lookups miss only the shown alternatives. |
| ownership | Runtimes own live state; rows/plans/snapshot owner values are local. |
| failure | Expected invalid_options (2), invalid_sequence, invalid_native_update (node/op/generalized root), and invalid_tuple (arity/wrong tag). |
| cost | Three plan lowerings; two rejected constructors; four unary invalid updates, one generalized rejection, one invalid and one accepted typed update, three negative lookups. |
| Design | tests/unit/support_api_test.cpp:207-256, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0043

[Lines 258–360](../../../../../tests/unit/support_api_test.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void noops_sequences_metrics_and_owned_handles() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check generalized support propagation, support-count transitions, no-op sequencing, deleted-key ownership and fresh handle identity. |
| inputs / outputs | On generalized-y plan uses left rows (1,10)/(2,10), right (10,7); updates sequences 1-8 insert/erase/duplicate/absent, then right erase at 9 and last left erase at 10. |
| invariants | Checks incomplete then true root, y count 1-&gt;2-&gt;1 without membership event, root record/survivor/visible (10), zero-work no-ops consuming sequences, captured deleted row surviving live deletion, and one reclaimed candidate. |
| ownership | Runtime owns live state; snapshots and transition tuple retain captured rows/metadata; saved key copy outlives deletion. |
| failure | No error injection; duplicate insert and absent delete are checked as no-ops. |
| cost | Ten updates, selected snapshots and invariant check on fixed three-node plan. |
| Design | tests/unit/support_api_test.cpp:258-360, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0045

[Lines 362–401](../../../../../tests/unit/support_api_test.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void support_limit_failure_is_atomic_and_retryable() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check same-runtime rollback/retry when a unary projection counter is at configured capacity. |
| inputs / outputs | Support limit 1 with capture: insert (20), fail insert (21) at sequence 2, erase (20) at sequence 2, insert (21) at sequence 3. |
| invariants | Overflow must preserve sequence/owner/answer, prior row/key handle, support count, live/retained/pin stats and first journal; freed capacity allows retry with fresh tuple ID. |
| ownership | Runtime owns rows and handles; snapshot and first journal are retained across failure/retry. |
| failure | Only full-cap insert expects support_overflow; invariants checked before and after retry. |
| cost | Four update attempts (three successful, one failed) and before/after snapshot/stat reads on one-node plan. |
| Design | tests/unit/support_api_test.cpp:362-401, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0047

[Lines 403–440](../../../../../tests/unit/support_api_test.cpp#L403); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void work_limit_boundaries_and_atomic_retry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check work-cap exact admission, one-below atomic failure and zero-cap no-op. |
| inputs / outputs | Measure one unary insert (3); test cap equal to measured, measured-1, and zero with erase then insert. |
| invariants | Exact cap accepts sequence 1; one-below expects resource_limit and preserves owner/sequence/answer/rows; zero-cap absent erase consumes sequence with zero metrics, then insert fails and leaves row absent. |
| ownership | Probe, accepted, rejected and zero-cap runtimes are independent. |
| failure | Only the two bounded insertions expect resource_limit. |
| cost | One probe, one exact-cap insert, one rejected insert and two zero-cap operations; measured value is fixture-derived, not benchmarked. |
| Design | tests/unit/support_api_test.cpp:403-440, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0049

[Lines 442–489](../../../../../tests/unit/support_api_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fifo_and_lifo_produce_same_canonical_state() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare FIFO/LIFO propagation on one nested four-node plan after matched updates. |
| inputs / outputs | Both runtimes receive rows (1,10),(2,10), nested row (10), root rows 1 and 2, then erase nested row (10), sequences 1-6. |
| invariants | At selected stages compare sequence/answer/nodes/records/survivors/parent/visible keys; nested insert reports 3 native visits and 3 child-key events; final erase clears answer and has survivor transitions. |
| ownership | Each runtime owns separate state; snapshots and transitions are read for comparison. |
| failure | No expected exception or fault injection occurs. |
| cost | Six updates per order, stage snapshots and final invariant checks. |
| Design | tests/unit/support_api_test.cpp:442-489, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0051

[Lines 491–547](../../../../../tests/unit/support_api_test.cpp#L491); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reference_storage_snapshot_copy_owns_and_preserves_ids() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that ReferencePlanStorage snapshot_copy clones indexed rows under a fresh owner with independent local ID counters. |
| inputs / outputs | Uses native join root row (1,10); adds field-0 index target 701; copies; then adds field-1 index targets 702/703 and inserts (2,11) in both tables. |
| invariants | Copy preserves registered index IDs, cloned tuple ID, added index definition/memberships, and next counters; later mutations are independent. |
| ownership | Copy owns cloned rows/tables/indexes under a different owner; original handle is foreign to copy; handles remain owner-specific. |
| failure | Copied lookup with original handle expects foreign_handle. No allocation-failure injection occurs. |
| cost | One original insert, one copy, one expected foreign lookup, index additions and two independent later inserts. |
| Design | tests/unit/support_api_test.cpp:491-547, [include/crown/storage/physical.hpp](../../../../../include/crown/storage/physical.hpp), [src/storage/physical.cpp](../../../../../src/storage/physical.cpp), [include/crown/storage/reference.hpp](../../../../../include/crown/storage/reference.hpp), [include/crown/storage/backend.hpp](../../../../../include/crown/storage/backend.hpp) |

## B0053

[Lines 549–596](../../../../../tests/unit/support_api_test.cpp#L549); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constant_routes_and_runtime_moves() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check true/false constant routes, external-write rejection, and SupportRuntime move/handle behavior. |
| inputs / outputs | Builds empty true/false queries; attempts write to true; inserts (42) in unary source; move constructs, self-moves, then move assigns into destination previously containing (9). |
| invariants | True starts answered and false unanswered, both no ports/nodes. Moves preserve source owner/sequence/handle; old destination handle becomes foreign. |
| ownership | Move transfers live plan/state and source handle; destination's previous runtime is replaced. |
| failure | Expected invalid_native_update for constant write, invalid_runtime for moved-from access, foreign_support_handle for old destination handle. |
| cost | Two constant lowerings/runtimes, one source update, move construction, self-move, destination setup/update, move assignment, invariant check. |
| Design | tests/unit/support_api_test.cpp:549-596, [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0054

[Lines 597–599](../../../../../tests/unit/support_api_test.cpp#L597); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L597-L599:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in support_api_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/support_api_test.cpp](../../../../../tests/unit/support_api_test.cpp), [docs/runtime_support.md](../../../../runtime_support.md), [docs/code_review.md](../../../../code_review.md) |

## B0055

[Lines 600–615](../../../../../tests/unit/support_api_test.cpp#L600); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the support API test executable's finite entry sequence. |
| inputs / outputs | Calls eight named support test bodies in source order, catches std::exception, returns 0 on success or 1 after printing failure. |
| invariants | No command-line input; claims only the listed fixture calls. |
| ownership | Fixture state is local to each called test. |
| failure | Escaping std::exception is printed and maps to 1. |
| cost | Eight test-function calls; no benchmark. |
| Design | tests/unit/support_api_test.cpp:600-615 |
