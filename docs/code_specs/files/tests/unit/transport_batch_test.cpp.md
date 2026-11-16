# `tests/unit/transport_batch_test.cpp` — block usage map

[Source](../../../../../tests/unit/transport_batch_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6b77423388e1f74c13281f07500e00c35a6244a74c40131229c1e60f9f93d2c6`. 531 lines partitioned into 50 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../tests/unit/transport_batch_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 25–27](../../../../../tests/unit/transport_batch_test.cpp#L25) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 28–28](../../../../../tests/unit/transport_batch_test.cpp#L28) | Explanatory comments or spacing. |  |
| [B0004 · 29–40](../../../../../tests/unit/transport_batch_test.cpp#L29) | Callable definition: template &lt;class Action&gt; void expect_code(Action&& action, std::string_view code, const std::string& label) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0004) |
| [B0005 · 41–47](../../../../../tests/unit/transport_batch_test.cpp#L41) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_copy_constructible_v&lt;TransportBatch&gt;); · [reviewed contract](#b0005) |
| [B0006 · 48–48](../../../../../tests/unit/transport_batch_test.cpp#L48) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0006) |
| [B0007 · 49–49](../../../../../tests/unit/transport_batch_test.cpp#L49) | Explanatory comments or spacing. |  |
| [B0008 · 50–52](../../../../../tests/unit/transport_batch_test.cpp#L50) | Callable definition: Catalog unary_catalog() | calls ; returns {1, {{@ , {{@ , ScalarType::int64}}}}} · [reviewed contract](#b0008) |
| [B0009 · 53–53](../../../../../tests/unit/transport_batch_test.cpp#L53) | Explanatory comments or spacing. |  |
| [B0010 · 54–62](../../../../../tests/unit/transport_batch_test.cpp#L54) | Callable definition: PhysicalPlan unary_plan() | calls unary_catalog, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0010) |
| [B0011 · 63–63](../../../../../tests/unit/transport_batch_test.cpp#L63) | Explanatory comments or spacing. |  |
| [B0012 · 64–73](../../../../../tests/unit/transport_batch_test.cpp#L64) | Callable definition: PhysicalPlan ignored_projection_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0012) |
| [B0013 · 74–74](../../../../../tests/unit/transport_batch_test.cpp#L74) | Explanatory comments or spacing. |  |
| [B0014 · 75–90](../../../../../tests/unit/transport_batch_test.cpp#L75) | Callable definition: PhysicalPlan self_join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0014) |
| [B0015 · 91–91](../../../../../tests/unit/transport_batch_test.cpp#L91) | Explanatory comments or spacing. |  |
| [B0016 · 92–101](../../../../../tests/unit/transport_batch_test.cpp#L92) | Callable definition: PhysicalPlan boolean_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0016) |
| [B0017 · 102–102](../../../../../tests/unit/transport_batch_test.cpp#L102) | Explanatory comments or spacing. |  |
| [B0018 · 103–108](../../../../../tests/unit/transport_batch_test.cpp#L103) | Callable definition: InputEvent event(std::uint64_t sequence, Row values, SetOperation operation = SetOperation::insert, std::optional&lt;SourcePosition&gt;… | calls std::move; returns {{sequence, table, operation, std::move(values)}, std::move(position)}; growth insert · [reviewed contract](#b0018) |
| [B0019 · 109–109](../../../../../tests/unit/transport_batch_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0020 · 110–115](../../../../../tests/unit/transport_batch_test.cpp#L110) | Callable definition: TransportBatch batch(std::vector&lt;InputEvent&gt; events, BatchLimits limits = {}) | calls reserve, size, emplace_back, std::move; returns TransportBatch(std::move(items), limits); growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 116–116](../../../../../tests/unit/transport_batch_test.cpp#L116) | Explanatory comments or spacing. |  |
| [B0022 · 117–122](../../../../../tests/unit/transport_batch_test.cpp#L117) | Callable definition: QueueLimits generous_queue_limits() | calls ; returns limits · [reviewed contract](#b0022) |
| [B0023 · 123–123](../../../../../tests/unit/transport_batch_test.cpp#L123) | Explanatory comments or spacing. |  |
| [B0024 · 124–193](../../../../../tests/unit/transport_batch_test.cpp#L124) | Callable definition: void transport_batch_and_admission_limits() | calls batch, check, empty, size; guard check(empty.empty() && empty.size() == 0, · [reviewed contract](#b0024) |
| [B0025 · 194–194](../../../../../tests/unit/transport_batch_test.cpp#L194) | Explanatory comments or spacing. |  |
| [B0026 · 195–200](../../../../../tests/unit/transport_batch_test.cpp#L195) | Callable definition: std::vector&lt;InputEvent&gt; alternating_trace() | calls event, n; returns {event(1, {n(8)}, SetOperation::insert, SourcePosition{@ , 10}),; growth insert · [reviewed contract](#b0026) |
| [B0027 · 201–201](../../../../../tests/unit/transport_batch_test.cpp#L201) | Explanatory comments or spacing. |  |
| [B0028 · 202–251](../../../../../tests/unit/transport_batch_test.cpp#L202) | Callable definition: void fifo_barriers_for_every_batch_partition() | calls unary_catalog, alternating_trace, queue, generous_queue_limits; guard check(queue.enqueue(offered) == Admission::accepted && offered.empty(),; growth push_back; 4 loop sites; source comment (unverified): // There are three possible cut points. Exercise every contiguous partition, · [reviewed contract](#b0028) |
| [B0029 · 252–252](../../../../../tests/unit/transport_batch_test.cpp#L252) | Explanatory comments or spacing. |  |
| [B0030 · 253–319](../../../../../tests/unit/transport_batch_test.cpp#L253) | Callable definition: void queue_sticky_validation_and_owned_rows() | calls unary_catalog, generous_queue_limits, sequence_queue, batch; guard check(sequence_queue.enqueue(invalid_sequence) == Admission::accepted,; growth emplace_back, insert · [reviewed contract](#b0030) |
| [B0031 · 320–320](../../../../../tests/unit/transport_batch_test.cpp#L320) | Explanatory comments or spacing. |  |
| [B0032 · 321–332](../../../../../tests/unit/transport_batch_test.cpp#L321) | Callable definition: std::set&lt;SignedKey&gt; collect_epoch_output(QuerySession& session, const std::string& label) | calls next_output, check, emplace, crown::storage::export_row; guard check(record-&gt;ordinal == ++ordinal,; returns rows; growth emplace; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 333–333](../../../../../tests/unit/transport_batch_test.cpp#L333) | Explanatory comments or spacing. |  |
| [B0034 · 334–340](../../../../../tests/unit/transport_batch_test.cpp#L334) | Callable definition: void step_to_prepared(QuerySession& session, const std::string& label) | calls status, step, check; guard check(++calls &lt; 100000, label + ": epoch failed to reach preparation");; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 341–341](../../../../../tests/unit/transport_batch_test.cpp#L341) | Explanatory comments or spacing. |  |
| [B0036 · 342–355](../../../../../tests/unit/transport_batch_test.cpp#L342) | Callable definition: void check_snapshot(QuerySession& session, const reference::Session& oracle, std::uint64_t sequence, const std::string& label) | calls snapshot, check, layout, same_token; guard check(tuple.layout().same_token(snapshot.layout),; growth insert; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 356–356](../../../../../tests/unit/transport_batch_test.cpp#L356) | Explanatory comments or spacing. |  |
| [B0038 · 357–383](../../../../../tests/unit/transport_batch_test.cpp#L357) | Callable definition: void apply_and_compare(QuerySession& session, reference::Session& oracle, const InputEvent& input, const std::string& label) | calls apply, emplace, check, begin_next_result; guard check(session.begin_next_result() == SessionBegin::pending,; growth emplace, insert; 2 loop sites · [reviewed contract](#b0038) |
| [B0039 · 384–384](../../../../../tests/unit/transport_batch_test.cpp#L384) | Explanatory comments or spacing. |  |
| [B0040 · 385–411](../../../../../tests/unit/transport_batch_test.cpp#L385) | Callable definition: void run_typed_oracle_case(const std::string& label, PhysicalPlan plan, Database initial, std::vector&lt;std::vector&lt;InputEvent&gt;&gt; pa… | calls QuerySession::create_typed, generous_queue_limits, oracle, source_catalog; guard check(session-&gt;enqueue(offered) == Admission::accepted && offered.empty(),; growth push_back; 3 loop sites · [reviewed contract](#b0040) |
| [B0041 · 412–412](../../../../../tests/unit/transport_batch_test.cpp#L412) | Explanatory comments or spacing. |  |
| [B0042 · 413–467](../../../../../tests/unit/transport_batch_test.cpp#L413) | Callable definition: void typed_session_nonblocking_finish_and_pause() | calls unary_plan, QuerySession::create_typed, start, check; guard check(session-&gt;begin_next_result() == SessionBegin::would_block && · [reviewed contract](#b0042) |
| [B0043 · 468–468](../../../../../tests/unit/transport_batch_test.cpp#L468) | Explanatory comments or spacing. |  |
| [B0044 · 469–499](../../../../../tests/unit/transport_batch_test.cpp#L469) | Callable definition: void typed_epochs_match_reference_with_projection_aliases_and_types() | calls ignored_projection_plan, resize, insert, n; growth insert, resize · [reviewed contract](#b0044) |
| [B0045 · 500–500](../../../../../tests/unit/transport_batch_test.cpp#L500) | Explanatory comments or spacing. |  |
| [B0046 · 501–510](../../../../../tests/unit/transport_batch_test.cpp#L501) | Callable definition: void bad_initial_database_is_rejected() | calls unary_plan, resize, insert, std::string; growth insert, resize · [reviewed contract](#b0046) |
| [B0047 · 511–511](../../../../../tests/unit/transport_batch_test.cpp#L511) | Explanatory comments or spacing. |  |
| [B0048 · 512–519](../../../../../tests/unit/transport_batch_test.cpp#L512) | Callable definition: void run() | calls transport_batch_and_admission_limits, fifo_barriers_for_every_batch_partition, queue_sticky_validation_and_owned_rows, typed_session_nonblocking_finish_and_pause · [reviewed contract](#b0048) |
| [B0049 · 520–521](../../../../../tests/unit/transport_batch_test.cpp#L520) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0049) |
| [B0050 · 522–531](../../../../../tests/unit/transport_batch_test.cpp#L522) | Callable definition: int main() | calls run, what; returns 1; 0 · [reviewed contract](#b0050) |

## B0001

[Lines 1–24](../../../../../tests/unit/transport_batch_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:1e44dcae38c7546ed2d6c7c62bea3adf980735f8f36cdd46915aa39804c4767f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare transport_batch_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", "evaluator.hpp", &lt;cstdint&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/transport_batch_test.cpp](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 25–27](../../../../../tests/unit/transport_batch_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a transport test when a boolean assertion is false. |
| inputs / outputs | Accepts a condition and message; throws std::runtime_error(message) if false. |
| invariants | The helper evaluates only the supplied condition. |
| ownership | Message is borrowed for the call. |
| failure | False condition fails the enclosing test. |
| cost | Constant-time condition check; failure path uses the message. |
| Design | [tests/unit/transport_batch_test.cpp §B0002 L25-L27](../../../../../tests/unit/transport_batch_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0004

[Lines 29–40](../../../../../tests/unit/transport_batch_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert an action fails with one exact crown::Error code. |
| inputs / outputs | Perfect-forwards and invokes the action, catches Error, and compares failure.code() with the requested code and label. |
| invariants | No exception or a different code fails; non-Error exceptions propagate. |
| ownership | Forwarded action is invoked within this call; label/code references are borrowed. |
| failure | Mismatch or missing Error throws std::runtime_error. |
| cost | One action attempt and one code comparison. |
| Design | [tests/unit/transport_batch_test.cpp §B0004 L29-L40](../../../../../tests/unit/transport_batch_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0005

[Lines 41–47](../../../../../tests/unit/transport_batch_test.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L47:sha256:49cd23a60ffef9bd3cbba7a758c4d8214107dc7c1fc1240b0daf86667a03eb8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare transport_batch_test.cpp: require 5 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/transport_batch_test.cpp](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 48–48](../../../../../tests/unit/transport_batch_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an int64 Value for typed input fixtures. |
| inputs / outputs | Converts one signed integer to Value and returns it. |
| invariants | Preserves the fixture scalar; typed queue schema validation is separate. |
| ownership | Returned scalar is value-owned. |
| failure | Conversion errors propagate. |
| cost | Scalar construction only. |
| Design | [tests/unit/transport_batch_test.cpp §B0006 L48-L48](../../../../../tests/unit/transport_batch_test.cpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md) |

## B0008

[Lines 50–52](../../../../../tests/unit/transport_batch_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog unary_catalog() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the unary int64 catalog used by physical queue tests. |
| inputs / outputs | Returns a one-table catalog with table unary and column x:int64. |
| invariants | This test schema has exactly one positional field. |
| ownership | Returned Catalog owns its metadata. |
| failure | Value construction errors propagate. |
| cost | Fixed one-table, one-column value construction. |
| Design | [tests/unit/transport_batch_test.cpp §B0008 L50-L52](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0010

[Lines 54–62](../../../../../tests/unit/transport_batch_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-relation unary PhysicalPlan for typed session fixtures. |
| inputs / outputs | Uses unary_catalog, query unary(x), one native tree node and planner::lower_tree. |
| invariants | The fixture has one physical source table and one visible answer column. |
| ownership | Returned plan owns lowered metadata. |
| failure | Planner errors propagate. |
| cost | Fixed one-node plan construction/lowering. |
| Design | [tests/unit/transport_batch_test.cpp §B0010 L54-L62](../../../../../tests/unit/transport_batch_test.cpp), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0012

[Lines 64–73](../../../../../tests/unit/transport_batch_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan ignored_projection_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a projection fixture with an ignored physical payload column. |
| inputs / outputs | Creates pair(x:int64,payload:int64), maps only x into the query and lowers a one-node plan. |
| invariants | Physical row identity remains two fields while query membership projects x; separate source rows may share the projected answer. |
| ownership | Plan owns lowered metadata. |
| failure | Planner errors propagate. |
| cost | Fixed one-node two-field plan construction/lowering. |
| Design | [tests/unit/transport_batch_test.cpp §B0012 L64-L73](../../../../../tests/unit/transport_batch_test.cpp), [docs/physical_runtime.md §Input and source-row identity](../../../../physical_runtime.md), [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md) |

## B0014

[Lines 75–90](../../../../../tests/unit/transport_batch_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan self_join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-occurrence self-join plan over one edge table. |
| inputs / outputs | Creates left(x,z) and right(z,y) aliases over edge(src,dst), a generalized separator z root and two native children; lowers. |
| invariants | The two atom occurrences route one physical relation into distinct aliases; output order is x,z,y. |
| ownership | Returned plan owns lowered metadata. |
| failure | Planner errors propagate. |
| cost | Fixed three-node, three-variable lowering. |
| Design | [tests/unit/transport_batch_test.cpp §B0014 L75-L90](../../../../../tests/unit/transport_batch_test.cpp), [docs/physical_runtime.md §Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0016

[Lines 92–101](../../../../../tests/unit/transport_batch_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan boolean_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-column Boolean typed plan. |
| inputs / outputs | Creates flags(enabled:boolean), one native node and query output enabled; lowers and returns the plan. |
| invariants | The fixture admits boolean values and exposes that variable directly. |
| ownership | Returned plan owns its lowered metadata. |
| failure | Planner errors propagate. |
| cost | Fixed one-column plan lowering. |
| Design | [tests/unit/transport_batch_test.cpp §B0016 L92-L101](../../../../../tests/unit/transport_batch_test.cpp), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0018

[Lines 103–108](../../../../../tests/unit/transport_batch_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InputEvent event(std::uint64_t sequence, Row values,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owned typed InputEvent fixture. |
| inputs / outputs | Accepts sequence, Row, optional insert/erase operation, optional SourcePosition and table; moves row and position into the returned event. |
| invariants | Defaults are insert, no source position and TableId{0}; no queue validation occurs here. |
| ownership | Returned InputEvent owns moved values and source text. |
| failure | Moves/construction errors propagate. |
| cost | Moves one row and optional position; source-text cost follows payload size. |
| Design | [tests/unit/transport_batch_test.cpp §B0018 L103-L108](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0020

[Lines 110–115](../../../../../tests/unit/transport_batch_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TransportBatch batch(std::vector<InputEvent> events, BatchLimits limits = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Package InputEvents into a move-only TransportBatch with supplied limits. |
| inputs / outputs | Reserves a vector of InputItem, moves each event into it, then constructs and returns TransportBatch using BatchLimits. |
| invariants | Batch construction applies its own event/byte limits; queue admission is a separate operation. |
| ownership | TransportBatch receives moved item ownership; caller vector elements are moved-from. |
| failure | Construction/limit errors propagate. |
| cost | Reserves and moves each input event once; payload accounting follows the batch implementation and provided limits. |
| Design | [tests/unit/transport_batch_test.cpp §B0020 L110-L115](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0022

[Lines 117–122](../../../../../tests/unit/transport_batch_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueueLimits generous_queue_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return generous batch and event caps for queue fixtures. |
| inputs / outputs | Returns QueueLimits with batches=32 and events=64; byte cap remains its declared default. |
| invariants | The named limits are fixture capacities, not an application recommendation. |
| ownership | Returned limit struct is a value. |
| failure | No error path in this helper. |
| cost | Constant-size scalar setup. |
| Design | [tests/unit/transport_batch_test.cpp §B0022 L117-L122](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md) |

## B0024

[Lines 124–193](../../../../../tests/unit/transport_batch_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void transport_batch_and_admission_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check empty batches, batch event/byte caps and queue admission ownership. |
| inputs / outputs | Constructs zero-capacity empty batches; expects resource_limit for nonempty zero-event/zero-byte limits; checks empty admission at zero queue caps and full rejection at event, byte and descriptor limits. |
| invariants | The test checks rejected offered batches and queue statistics remain unchanged, while accepted empty input is consumed without closing the queue. |
| ownership | Queue owns accepted items; on Admission::full the caller retains each offered batch. |
| failure | Exact resource_limit codes are asserted at TransportBatch construction; queue refusal returns Admission::full. |
| cost | Several tiny batches/queues and scalar statistics comparisons; byte accounting is observed from these fixtures. |
| Design | [tests/unit/transport_batch_test.cpp §B0024 L124-L193](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md), [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md) |

## B0026

[Lines 195–200](../../../../../tests/unit/transport_batch_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<InputEvent> alternating_trace() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce a four-event alternating signed-update trace with source positions. |
| inputs / outputs | Returns insert, erase, insert, erase of unary row 8 at sequences 1–4 and feed offsets 10,20,30,40. |
| invariants | Events form barriers whose order and operation polarity must survive every batch partition. |
| ownership | Returned vector owns its event payloads and source strings. |
| failure | Event construction errors propagate. |
| cost | Constructs four small events. |
| Design | [tests/unit/transport_batch_test.cpp §B0026 L195-L200](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md) |

## B0028

[Lines 202–251](../../../../../tests/unit/transport_batch_test.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fifo_barriers_for_every_batch_partition() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check FIFO barriers for all contiguous partitions of a four-event batch. |
| inputs / outputs | Iterates all eight cut masks; admits each contiguous partition, verifies queue counts and finish state, then peeks and acknowledges each exact event while checking progress/source offsets and stable EOF. |
| invariants | The finite trace asserts batching does not coalesce or reorder signed updates and acknowledgement advances one sequence at a time; it does not test arbitrary queue lengths. |
| ownership | Each TypedQueue owns accepted batches; accepted offered objects are emptied; the expected trace remains local. |
| failure | Any admission/status/order/progress mismatch fails through check. |
| cost | Eight partitions × four events with queue bookkeeping and exact row/position comparisons. |
| Design | [tests/unit/transport_batch_test.cpp §B0028 L202-L251](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md), [docs/batches_windows.md §Steps, source progress and failure](../../../../batches_windows.md) |

## B0030

[Lines 253–319](../../../../../tests/unit/transport_batch_test.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void queue_sticky_validation_and_owned_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check deferred head validation, sticky errors and native ownership of queued row strings. |
| inputs / outputs | Queues batches with a late sequence error, repeated source offset, wrong row type and wrong InputItem kind; then destroys caller batch containing a 300-byte string and reads the owned queue head. |
| invariants | Assertions require admission before semantic head checks, acknowledged prefix preservation, no progress/head consumption on error, sticky failure and owned string lifetime. |
| ownership | TypedQueue owns accepted native item storage; caller retains a batch only when admission did not transfer it. |
| failure | Expected error codes are invalid_sequence, input_failed, invalid_source_position, invalid_update and invalid_input_kind. |
| cost | Creates four tiny validation queues and one 300-byte string row; repeated peeks and progress/stat reads. |
| Design | [tests/unit/transport_batch_test.cpp §B0030 L253-L319](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Native typed queue admission](../../../../batches_windows.md), [docs/batches_windows.md §Steps, source progress and failure](../../../../batches_windows.md) |

## B0032

[Lines 321–332](../../../../../tests/unit/transport_batch_test.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> collect_epoch_output(QuerySession& session,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect one committed session epoch's signed output rows. |
| inputs / outputs | Repeatedly calls next_output, checks ordinals start at one and inserts (operation, exported tuple row) into a set. |
| invariants | Returns a set of distinct signed rows; ordinal validation is local to the drained epoch output. |
| ownership | Session is borrowed; exported rows own test values. |
| failure | Duplicate signed rows or ordinal mismatch fails. |
| cost | Consumes and copies the complete output prefix; cost follows record count and row width. |
| Design | [tests/unit/transport_batch_test.cpp §B0032 L321-L332](../../../../../tests/unit/transport_batch_test.cpp), [docs/session_lifecycle.md §Control states and work phases](../../../../session_lifecycle.md) |

## B0034

[Lines 334–340](../../../../../tests/unit/transport_batch_test.cpp#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void step_to_prepared(QuerySession& session, const std::string& label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Step a session until its epoch reaches prepared phase, with a test guard. |
| inputs / outputs | Repeatedly calls session.step() until status.phase is prepared; increments a call counter and requires it remain below 100000. |
| invariants | The bound is a fixture watchdog against nonprogress, not a production work or latency guarantee. |
| ownership | Session remains caller-owned and may hold pending state when this helper returns. |
| failure | check throws if the phase does not reach prepared before the guard. |
| cost | Up to 99999 step calls; actual work depends on session phase and plan. |
| Design | [tests/unit/transport_batch_test.cpp §B0034 L334-L340](../../../../../tests/unit/transport_batch_test.cpp), [docs/session_lifecycle.md §Control states and work phases](../../../../session_lifecycle.md) |

## B0036

[Lines 342–355](../../../../../tests/unit/transport_batch_test.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_snapshot(QuerySession& session, const reference::Session& oracle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a committed QuerySession snapshot with the reference session. |
| inputs / outputs | Copies session.snapshot(), exports rows into a Relation, checks tuple layout-token identity, uniqueness, committed/progress sequence equality and relation equality to oracle.snapshot(). |
| invariants | Checks one committed boundary for a finite oracle state; snapshot equality is not an independent proof outside the compared fixture. |
| ownership | Session and oracle are borrowed; snapshot and exported Relation are local owning values. |
| failure | Layout, duplicate, sequence or answer mismatch fails by check. |
| cost | Copies the snapshot and scans every projected row; cost scales with snapshot size and row width. |
| Design | [tests/unit/transport_batch_test.cpp §B0036 L342-L355](../../../../../tests/unit/transport_batch_test.cpp), [docs/session_lifecycle.md §Bounded owning snapshots](../../../../session_lifecycle.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0038

[Lines 357–383](../../../../../tests/unit/transport_batch_test.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_and_compare(QuerySession& session, reference::Session& oracle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one accepted typed event through a session and compare its signed delta with reference semantics. |
| inputs / outputs | Advances reference::Session first; derives expected added/removed signed rows; begins pending result, checks sequence/progress, steps, commits, compares output, source offset and post-commit snapshot. |
| invariants | The reference session is a differential oracle for this event/fixture. Source progress is asserted only when the event carries a position. |
| ownership | Session and oracle own separate states; InputEvent is borrowed; output and snapshot rows are copied for comparison. |
| failure | Any mismatch in pending status, delta, progress or snapshot fails the test. |
| cost | One reference update, one native session epoch, full output drain and full snapshot scan. |
| Design | [tests/unit/transport_batch_test.cpp §B0038 L357-L383](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Steps, source progress and failure](../../../../batches_windows.md), [docs/session_lifecycle.md §Control states and work phases](../../../../session_lifecycle.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0040

[Lines 385–411](../../../../../tests/unit/transport_batch_test.cpp#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run_typed_oracle_case(const std::string& label, PhysicalPlan plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a typed-session differential case over preloaded rows and partitioned input batches. |
| inputs / outputs | Creates DeltaMode::delta typed session with initial Database and generous limits; initializes reference::Session, checks seq-0 snapshot, admits supplied partitions, then applies each flattened event via apply_and_compare, finishes input and checks EOF/final snapshot. |
| invariants | Partitioning affects queue packaging only in this fixture; each event is committed and compared separately. The finite comparison is not an all-input proof. |
| ownership | Session and oracle own separate mutable states; initial/partition vectors are moved or copied according to calls; flattened trace is local. |
| failure | Admission must transfer each batch; any event/eof/oracle mismatch fails. |
| cost | Reference and runtime process every fixture event, with an output and whole snapshot comparison per event. |
| Design | [tests/unit/transport_batch_test.cpp §B0040 L385-L411](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md), [docs/batches_windows.md §Steps, source progress and failure](../../../../batches_windows.md), [docs/session_lifecycle.md §Bounded owning snapshots](../../../../session_lifecycle.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0042

[Lines 413–467](../../../../../tests/unit/transport_batch_test.cpp#L413); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_session_nonblocking_finish_and_pause() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed-session would-block, explicit finish, pause/resume and closed-input behavior. |
| inputs / outputs | Starts an open empty session and checks would_block; contrasts explicit finish to EOF; confirms empty batch is not EOF; admits one event; pauses and expects admission/step session_paused without consumption; resumes, commits/drains, finishes and rejects a later batch as input_closed. |
| invariants | The test distinguishes queue emptiness from EOF and pause from completion for one-event prefixes; no asynchronous worker is involved. |
| ownership | Session owns accepted input; rejected offered batches remain caller-owned; session objects are local. |
| failure | Expected input_would_block, session_paused and input_closed codes are asserted at their named boundaries. |
| cost | Two sessions, two small batches, one prepared epoch and one drained output prefix. |
| Design | [tests/unit/transport_batch_test.cpp §B0042 L413-L467](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md), [docs/session_lifecycle.md §Control states and work phases](../../../../session_lifecycle.md), [docs/session_lifecycle.md §Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0044

[Lines 469–499](../../../../../tests/unit/transport_batch_test.cpp#L469); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_epochs_match_reference_with_projection_aliases_and_types() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare typed-session deltas with reference semantics for projection aliases and Boolean types. |
| inputs / outputs | Runs three oracle cases: ignored payload projection with repeated x rows and source offsets; two aliases of an edge self-join; and Boolean rows true/false with an erase. |
| invariants | Each event is applied as its own barrier and compared by run_typed_oracle_case; finite fixtures cover these input shapes only. |
| ownership | Each case builds independent session/reference state and owns its input partitions/database. |
| failure | Any per-event output, progress or snapshot mismatch fails through the shared oracle helper. |
| cost | Processes 13 small events across three cases, with reference evaluation, output draining and snapshot scans after each. |
| Design | [tests/unit/transport_batch_test.cpp §B0044 L469-L499](../../../../../tests/unit/transport_batch_test.cpp), [docs/physical_runtime.md §Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md §Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0046

[Lines 501–510](../../../../../tests/unit/transport_batch_test.cpp#L501); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bad_initial_database_is_rejected() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check typed session construction rejects a malformed initial database row. |
| inputs / outputs | Builds unary plan and a one-table Database containing a string where x:int64 is required; expects invalid_update from create_typed. |
| invariants | The assertion covers initial snapshot schema validation for this one malformed row. |
| ownership | Plan and malformed database are local; factory must reject before a session is returned. |
| failure | Expected public Error code is invalid_update; unexpected success or code fails. |
| cost | Attempts one typed-session construction and validates one row. |
| Design | [tests/unit/transport_batch_test.cpp §B0046 L501-L510](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md §Typed ordered input](../../../../batches_windows.md), [docs/session_lifecycle.md §Bounded owning snapshots](../../../../session_lifecycle.md) |

## B0048

[Lines 512–519](../../../../../tests/unit/transport_batch_test.cpp#L512); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the six transport-batch and typed-session test cases. |
| inputs / outputs | Calls admission limits, all FIFO partitions, sticky validation/ownership, nonblocking lifecycle, typed oracle cases and malformed initial-database rejection. |
| invariants | Execution outcome covers only these named cases; the helper itself makes no engine guarantee. |
| ownership | Each case manages its local queue/session state. |
| failure | Any propagated assertion or engine exception fails the caller. |
| cost | Sequentially runs the finite fixtures described by the six cases. |
| Design | [tests/unit/transport_batch_test.cpp §B0048 L512-L519](../../../../../tests/unit/transport_batch_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0049

[Lines 520–521](../../../../../tests/unit/transport_batch_test.cpp#L520); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L520-L521:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in transport_batch_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/transport_batch_test.cpp](../../../../../tests/unit/transport_batch_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 522–531](../../../../../tests/unit/transport_batch_test.cpp#L522); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run transport tests and translate exceptions to process exit status. |
| inputs / outputs | Calls run(), prints a success line on completion, or catches std::exception, prints its message and returns 1; otherwise returns 0. |
| invariants | Describes the executable boundary only when invoked; this packet makes no current build or CTest claim. |
| ownership | main owns the process-level try/catch; test cases own their fixtures. |
| failure | Any propagated standard exception yields status 1. |
| cost | Calls the finite test suite sequentially. |
| Design | [tests/unit/transport_batch_test.cpp §B0050 L522-L531](../../../../../tests/unit/transport_batch_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |
