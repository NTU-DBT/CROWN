# `tests/unit/delta_replay_scale_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_replay_scale_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `417c01e0aa96467f65b60341c7266d8fe467da5b3eaa19d33bebcbf24d136d4e`. 395 lines partitioned into 48 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/delta_replay_scale_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/delta_replay_scale_test.cpp#L23) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../tests/unit/delta_replay_scale_test.cpp#L26) | Explanatory comments or spacing. |  |
| [B0004 · 27–27](../../../../../tests/unit/delta_replay_scale_test.cpp#L27) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0004) |
| [B0005 · 28–28](../../../../../tests/unit/delta_replay_scale_test.cpp#L28) | Explanatory comments or spacing. |  |
| [B0006 · 29–33](../../../../../tests/unit/delta_replay_scale_test.cpp#L29) | Callable definition: VariableSet variables(std::initializer_list&lt;std::size_t&gt; values) | calls insert; returns result; growth insert; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 34–34](../../../../../tests/unit/delta_replay_scale_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0008 · 35–42](../../../../../tests/unit/delta_replay_scale_test.cpp#L35) | Callable definition: DeltaOptions options(DeltaCompletion completion) | calls ; returns result · [reviewed contract](#b0008) |
| [B0009 · 43–43](../../../../../tests/unit/delta_replay_scale_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0010 · 44–58](../../../../../tests/unit/delta_replay_scale_test.cpp#L44) | Callable definition: PhysicalPlan chain_plan() | calls variables, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0010) |
| [B0011 · 59–59](../../../../../tests/unit/delta_replay_scale_test.cpp#L59) | Explanatory comments or spacing. |  |
| [B0012 · 60–62](../../../../../tests/unit/delta_replay_scale_test.cpp#L60) | Callable definition: Relation a04(const auto& plan, const Database& database) | calls reference::evaluate, reference::input::catalog, catalog, reference::input::query; returns reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()… · [reviewed contract](#b0012) |
| [B0013 · 63–63](../../../../../tests/unit/delta_replay_scale_test.cpp#L63) | Explanatory comments or spacing. |  |
| [B0014 · 64–72](../../../../../tests/unit/delta_replay_scale_test.cpp#L64) | Callable definition: std::set&lt;SignedKey&gt; difference(const Relation& before, const Relation& after) | calls contains, emplace; returns result; growth emplace, insert; 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 73–73](../../../../../tests/unit/delta_replay_scale_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0016 · 74–98](../../../../../tests/unit/delta_replay_scale_test.cpp#L74) | Callable definition: std::vector&lt;Relation&gt; a04_live(const auto& plan, const Relation& answer) | calls query, size, try_emplace, reserve; guard check(position != head_positions.end(),; returns result; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0016) |
| [B0017 · 99–99](../../../../../tests/unit/delta_replay_scale_test.cpp#L99) | Explanatory comments or spacing. |  |
| [B0018 · 100–115](../../../../../tests/unit/delta_replay_scale_test.cpp#L100) | Callable definition: Relation drain_current(SupportRuntime::ResultCursor cursor, const storage::TupleLayout& layout, const std::string& label) | calls check, layout, same_token, next; guard check(cursor.layout().same_token(layout),; returns result; growth insert; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 116–116](../../../../../tests/unit/delta_replay_scale_test.cpp#L116) | Explanatory comments or spacing. |  |
| [B0020 · 117–121](../../../../../tests/unit/delta_replay_scale_test.cpp#L117) | Type/record definition: struct Event |  · [reviewed contract](#b0020) |
| [B0021 · 122–122](../../../../../tests/unit/delta_replay_scale_test.cpp#L122) | Explanatory comments or spacing. |  |
| [B0022 · 123–153](../../../../../tests/unit/delta_replay_scale_test.cpp#L123) | Callable definition: Event collect(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch, const std::set&lt;SignedKey&gt;& expected, const std::string& label) | calls check, remaining, size, active; guard check(epoch.remaining() == expected.size() &&; returns result; growth insert, push_back; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 154–155](../../../../../tests/unit/delta_replay_scale_test.cpp#L154) | declares types or opens a type body. |  · [reviewed contract](#b0023) |
| [B0024 · 156–168](../../../../../tests/unit/delta_replay_scale_test.cpp#L156) | Callable definition: public: ScaleRun(PhysicalPlan plan, std::size_t count) : replay_(plan, options(DeltaCompletion::ordered_replay)), anchored_(std::… | calls replay_, options, anchored_, std::move; guard check(replay_.completion() == DeltaCompletion::ordered_replay &&; growth resize; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 169–169](../../../../../tests/unit/delta_replay_scale_test.cpp#L169) | Explanatory comments or spacing. |  |
| [B0026 · 170–178](../../../../../tests/unit/delta_replay_scale_test.cpp#L170) | Callable definition: void bootstrap(std::size_t count) | calls set_mode, check_current, check, a04; guard check(a04(replay_.plan(), database_).empty(), · [reviewed contract](#b0026) |
| [B0027 · 179–179](../../../../../tests/unit/delta_replay_scale_test.cpp#L179) | Explanatory comments or spacing. |  |
| [B0028 · 180–208](../../../../../tests/unit/delta_replay_scale_test.cpp#L180) | Callable definition: std::pair&lt;Event, Event&gt; update(SetOperation operation, const std::string& label) | calls a04, plan, n, at; guard check(changed, label + ": S event did not cross source set membership");; returns {std::move(replay_result), std::move(anchored_result)}; growth insert · [reviewed contract](#b0028) |
| [B0029 · 209–209](../../../../../tests/unit/delta_replay_scale_test.cpp#L209) | Explanatory comments or spacing. |  |
| [B0030 · 210–224](../../../../../tests/unit/delta_replay_scale_test.cpp#L210) | Callable definition: private: void seed(Row row) | calls apply, check, remaining, next; guard check(replay_epoch.remaining() == 0 && anchored_epoch.remaining() == 0,; growth insert · [reviewed contract](#b0030) |
| [B0031 · 225–225](../../../../../tests/unit/delta_replay_scale_test.cpp#L225) | Explanatory comments or spacing. |  |
| [B0032 · 226–247](../../../../../tests/unit/delta_replay_scale_test.cpp#L226) | Callable definition: void check_current(const DeltaRuntime& runtime, const std::string& label) | calls a04, plan, check, has_answer; guard check(runtime.has_answer() == !expected.empty(), · [reviewed contract](#b0032) |
| [B0033 · 248–254](../../../../../tests/unit/delta_replay_scale_test.cpp#L248) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0033) |
| [B0034 · 255–260](../../../../../tests/unit/delta_replay_scale_test.cpp#L255) | Type/record definition: struct ScaleMetrics |  · [reviewed contract](#b0034) |
| [B0035 · 261–261](../../../../../tests/unit/delta_replay_scale_test.cpp#L261) | Explanatory comments or spacing. |  |
| [B0036 · 262–283](../../../../../tests/unit/delta_replay_scale_test.cpp#L262) | Callable definition: void check_insert_contract(const Event& replay, const Event& anchored, std::size_t count, const std::string& label) | calls check, front; guard check(r.changed_keys == count + 1 && r.candidates == count && · [reviewed contract](#b0036) |
| [B0037 · 284–284](../../../../../tests/unit/delta_replay_scale_test.cpp#L284) | Explanatory comments or spacing. |  |
| [B0038 · 285–307](../../../../../tests/unit/delta_replay_scale_test.cpp#L285) | Callable definition: void check_delete_contract(const Event& replay, const Event& anchored, std::size_t count, const std::string& label) | calls check, front; guard check(r.changed_keys == count + 1 && r.candidates == count && · [reviewed contract](#b0038) |
| [B0039 · 308–308](../../../../../tests/unit/delta_replay_scale_test.cpp#L308) | Explanatory comments or spacing. |  |
| [B0040 · 309–328](../../../../../tests/unit/delta_replay_scale_test.cpp#L309) | Callable definition: ScaleMetrics run_scale(std::size_t count) | calls run, chain_plan, bootstrap, update; guard check(inserted.first.raw.size() == count &&; returns {inserted.first.metrics, inserted.second.metrics,; growth insert · [reviewed contract](#b0040) |
| [B0041 · 329–331](../../../../../tests/unit/delta_replay_scale_test.cpp#L329) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0041) |
| [B0042 · 332–335](../../../../../tests/unit/delta_replay_scale_test.cpp#L332) | Callable definition: PhaseMaxima phase_maxima(const DeltaMetrics& metrics) | calls ; returns {metrics.replay_max_first_work, metrics.replay_max_next_work, · [reviewed contract](#b0042) |
| [B0043 · 336–336](../../../../../tests/unit/delta_replay_scale_test.cpp#L336) | Explanatory comments or spacing. |  |
| [B0044 · 337–342](../../../../../tests/unit/delta_replay_scale_test.cpp#L337) | Callable definition: void check_phase_metrics(const DeltaMetrics& metrics, const std::string& label) | calls check; guard check(metrics.replay_max_first_work != 0 && · [reviewed contract](#b0044) |
| [B0045 · 343–343](../../../../../tests/unit/delta_replay_scale_test.cpp#L343) | Explanatory comments or spacing. |  |
| [B0046 · 344–383](../../../../../tests/unit/delta_replay_scale_test.cpp#L344) | Callable definition: void accepted_transition_work_does_not_grow_with_output_count() | calls run_scale, check_phase_metrics, check, phase_maxima; guard check(phase_maxima(small.insertion_replay) == · [reviewed contract](#b0046) |
| [B0047 · 384–386](../../../../../tests/unit/delta_replay_scale_test.cpp#L384) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0047) |
| [B0048 · 387–395](../../../../../tests/unit/delta_replay_scale_test.cpp#L387) | Callable definition: int main() | calls accepted_transition_work_does_not_grow_with_output_count, what; returns 1 · [reviewed contract](#b0048) |

## B0001

[Lines 1–22](../../../../../tests/unit/delta_replay_scale_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:7e3348fac241daa9e98a1ac5b5c73051caaf78d3cccf4abd30edb6b9eec771ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_replay_scale_test.cpp: include "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "evaluator.hpp", "native_input.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;initializer_list&gt;, &lt;map&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–25](../../../../../tests/unit/delta_replay_scale_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed runtime-scale assertion into a test exception. |
| inputs / outputs | Accepts a Boolean and const std::string diagnostic; returns when true and throws std::runtime_error carrying the message when false. |
| invariants | The helper body only branches on the Boolean. Call-site diagnostic expressions and temporary strings are constructed before entry, including on passing assertions. |
| ownership | Borrows the already materialized message during the call; a thrown exception owns its error text. |
| failure | False throws; allocation failures propagate; no condition is caught here. |
| cost | One condition branch in the helper. Caller-side concatenation or literal-to-string conversion may allocate for every check, whether it succeeds or fails. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp) |

## B0004

[Lines 27–27](../../../../../tests/unit/delta_replay_scale_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one signed 64-bit fixture value for the plan database. |
| inputs / outputs | Converts an int64_t to the runtime Value variant and returns it. |
| invariants | The fixture passes only signed 64-bit values through this wrapper. |
| ownership | Returns an owning Value. |
| failure | Variant construction failures propagate. |
| cost | Fixed-size variant construction; does not scan rows or execute runtime work. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp) |

## B0006

[Lines 29–33](../../../../../tests/unit/delta_replay_scale_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VariableSet variables(std::initializer_list<std::size_t> values)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a VariableSet from positional variable indices. |
| inputs / outputs | Takes an initializer_list&lt;size_t&gt;, wraps each index as VariableId, inserts it into a set, and returns the set. |
| invariants | Set semantics remove duplicate indices and order identifiers by the set comparator. |
| ownership | Returns an owning set; initializer-list values are read during the call. |
| failure | Allocation failures propagate. |
| cost | Loops over input count and performs set insertions; fixture setup cost only. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp) |

## B0008

[Lines 35–42](../../../../../tests/unit/delta_replay_scale_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(DeltaCompletion completion)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select maintenance setup and a requested delta completion mode. |
| inputs / outputs | Takes a DeltaCompletion and returns DeltaOptions with mode maintenance, the requested completion, and live maintenance on_output for ordered replay or incremental otherwise. |
| invariants | The fixture always starts in maintenance mode; the two completion variants deliberately select different live-maintenance policies. |
| ownership | Returns options by value. |
| failure | No helper-level validation or recovery; invalid runtime configuration errors propagate from construction/use. |
| cost | Fixed option assignments and one completion comparison; no relation work. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0010

[Lines 44–58](../../../../../tests/unit/delta_replay_scale_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan chain_plan()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the fixed two-table chain fixture to a physical plan. |
| inputs / outputs | Creates catalog R(a,x), S(x,y), query head (a,x,y), and a native free-connex tree with R root and S child; returns planner::lower_tree result. |
| invariants | The tree and query share x; R and S are distinct native occurrences, with S joined below R. This helper describes only this fixed fixture. |
| ownership | Owns local catalog/query/tree values and returns the lowered plan by value. |
| failure | Planner lowering errors propagate. |
| cost | Constructs small metadata containers and invokes planner validation/lowering; no data rows are scanned. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0012

[Lines 60–62](../../../../../tests/unit/delta_replay_scale_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation a04(const auto& plan, const Database& database)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the plan’s query with the independent A04 reference evaluator. |
| inputs / outputs | Accepts any plan-like value exposing catalog() and query(), plus a Database; adapts catalog/query into reference input and returns reference::evaluate result. |
| invariants | A04 evaluation supplies the expected whole-query answer independently of the DeltaRuntime enumeration result; the plan provides query metadata only. |
| ownership | Borrows plan and database during evaluation; returned Relation owns rows. |
| failure | Adapter/evaluator validation or allocation errors propagate. |
| cost | Converts catalog/query representations and runs the reference whole-query nested-loop evaluation; work depends on query, database rows, and intermediate joins. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp) |

## B0014

[Lines 64–72](../../../../../tests/unit/delta_replay_scale_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<SignedKey> difference(const Relation& before, const Relation& after)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the exact signed set difference between two answer relations. |
| inputs / outputs | Returns inserts for rows in after but not before and erases for rows in before but not after, keyed by (operation,row). |
| invariants | Uses set membership and deduplicates equal signed keys; unchanged rows are omitted. |
| ownership | Borrows both relations; owns a new set of signed keys and copied rows. |
| failure | Allocation failures propagate. |
| cost | Scans both relations, performs ordered-set contains/insert operations, and copies changed rows; not a runtime metric. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp) |

## B0016

[Lines 74–98](../../../../../tests/unit/delta_replay_scale_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Relation> a04_live(const auto& plan, const Relation& answer)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project a whole A04 answer onto each plan enumeration node’s visible scope. |
| inputs / outputs | Builds first head position per variable, then for each enumeration step projects every full answer tuple to the node visible scope and returns one Relation per step. |
| invariants | It derives live-factor expectations from whole-query answers; it does not calculate live sets by replaying production update history. A missing visible variable in the head fails the check. |
| ownership | Borrows plan/answer; returned vector and relations own projected keys; duplicate projections collapse in each set. |
| failure | Missing scope variable triggers check failure; out-of-range answer indexing and allocation failures propagate. |
| cost | Builds a head map and scans every answer for every enumeration step, copying scope keys and inserting into sets; cost scales with answer count, step count, and scope widths. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0018

[Lines 100–115](../../../../../tests/unit/delta_replay_scale_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain_current(SupportRuntime::ResultCursor cursor, const storage::TupleLayout& layout, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain and validate a current-result cursor into a set-valued relation. |
| inputs / outputs | Takes ResultCursor by value, expected TupleLayout, and label; checks layout tokens, exports every tuple row, rejects duplicates, and returns a Relation after requiring exhausted/inactive state. |
| invariants | Each tuple layout must match the runtime layout; full exhaustion releases the cursor lease. |
| ownership | Takes ownership of cursor handle by value; exported rows are copied into an owning Relation; label is borrowed. |
| failure | Layout mismatch, duplicate result, retained lease, and allocation failures fail/propagate. |
| cost | Consumes every returned tuple, exports/copies rows, and performs ordered-set insertions; diagnostic strings can be formed at checks. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0020

[Lines 117–121](../../../../../tests/unit/delta_replay_scale_test.cpp#L117); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Event
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle raw signed output, route stages, and metrics captured for one epoch. |
| inputs / outputs | Event stores a vector of signed keys, a vector of DeltaStage values, and one DeltaMetrics snapshot. |
| invariants | It is a test result container; it makes no runtime correctness guarantee by itself. |
| ownership | Owns copied raw keys, stages, and metrics. |
| failure | No behavior or recovery. |
| cost | Default member construction; later vector assignment/appends allocate according to captured output size. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0022

[Lines 123–153](../../../../../tests/unit/delta_replay_scale_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Event collect(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch, const std::set<SignedKey>& expected, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain one delta epoch and compare its exact signed output with the A04 delta. |
| inputs / outputs | Checks remaining cardinality and lease state, drains records, requires contiguous ordinals and matching layout, rejects duplicate keys, compares unique signed rows to expected, requires exhausted/inactive epoch and ready runtime, checks no extra next record, then snapshots stages/metrics into Event. |
| invariants | The epoch must correspond to exactly one native input and expose one route stage whose output_count equals raw rows. A04 expected set is independently computed by caller. |
| ownership | Borrows runtime, epoch, expected set, and label; Event owns copies of raw keys, stages, and metrics. |
| failure | Any failed condition throws; record/export/allocation exceptions propagate. |
| cost | Visits each output, exports and copies rows, inserts into a set, copies stage and metric snapshots; per-check diagnostic string arguments may be formed eagerly. Work is output-proportional here and does not bound producer CPU. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/decisions/0011-reference-support.md](../../../../decisions/0011-reference-support.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0023

[Lines 154–155](../../../../../tests/unit/delta_replay_scale_test.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L155:sha256:798f5736617b08deb16d515f2593c5e014f519f3969f2014dda3a861a5cdd122
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_replay_scale_test.cpp: open the test/reference type declaration. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 156–168](../../../../../tests/unit/delta_replay_scale_test.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
public: ScaleRun(PhysicalPlan plan, std::size_t count) : replay_(plan, options(DeltaCompletion::ordered_replay)), anchored_(std::move(plan), options(DeltaCompletion::anchored))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct paired ordered-replay and anchored DeltaRuntime fixtures and seed R. |
| inputs / outputs | Accepts a lowered plan and root-row count; constructs replay_ with ordered_replay options and anchored_ with anchored options, resizes the oracle database for two tables, checks configured modes, then seeds rows (i,7) for i in \[0,count). |
| invariants | Both runtimes receive the same ordered physical inputs and begin in maintenance mode; the independent Database mirrors R memberships. |
| ownership | The ScaleRun object owns both runtimes, database, and sequence. The plan is copied to replay_ and moved to anchored_. |
| failure | Runtime construction, seed checks, and allocations may throw; partial construction does not establish a completed fixture. |
| cost | Builds two runtimes, loops count times calling seed; seed performs two runtime applies and current-state checks per root row, including repeated reference evaluation and cursor drains. This setup is not benchmarked. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md) |

## B0026

[Lines 170–178](../../../../../tests/unit/delta_replay_scale_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bootstrap(std::size_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Switch both paired runtimes from maintenance setup to delta mode and validate the empty-answer baseline. |
| inputs / outputs | Accepts count; changes both runtimes to DeltaMode::delta, checks their current state against A04, verifies the fixture answer is empty before S insertion, and requires nonzero count. |
| invariants | The nonzero root side is present while S is absent, so the chain query has no answers at bootstrap. |
| ownership | Borrows the owned runtime/database members; set_mode results are explicitly discarded. |
| failure | Failed condition or runtime/evaluator error propagates; no rollback to maintenance is attempted. |
| cost | Performs two mode changes and two full check_current passes, plus another A04 query evaluation and a count check. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0028

[Lines 180–208](../../../../../tests/unit/delta_replay_scale_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::pair<Event, Event> update(SetOperation operation, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one S-row insert or erase to the paired runtimes and check its signed result. |
| inputs / outputs | Takes SetOperation and label; computes A04 before and after on an independent copied Database with S(7,9) membership toggled, increments sequence, applies identical PhysicalSetUpdate to both runtimes, collects both epochs, compares signed sets, then commits the oracle database copy and checks both after-states. |
| invariants | The source set must actually change membership; both epochs must use the same sequence and exactly match the independent before/after answer difference. Oracle state is committed only after both event collections and strategy comparison pass. |
| ownership | Borrows label; local after_database owns a copy until moved into database_; runtime epochs are local RAII handles; ScaleRun owns persistent state. |
| failure | Checks and runtime/evaluator/allocation errors propagate. A failure after apply can leave one or both runtimes advanced while oracle database remains old; this test helper is not a transaction/rollback wrapper. |
| cost | Copies the oracle database, evaluates A04 before/after, applies to two runtimes, drains outputs, compares sets, moves database copy, and performs two full post-state checks; not a CPU/RSS measurement. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/decisions/0011-reference-support.md](../../../../decisions/0011-reference-support.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0030

[Lines 210–224](../../../../../tests/unit/delta_replay_scale_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
private: void seed(Row row)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed one R row into both runtimes while requiring maintenance mode to emit no delta. |
| inputs / outputs | Takes a Row by value, increments sequence, applies an R insert to both runtimes, checks both epochs have no output, inserts row into oracle table R, and validates both current states. |
| invariants | Seed rows are unique in the oracle set; a maintenance-mode seed must return neither remaining output nor a record. |
| ownership | Consumes/moves the row into oracle database after runtime inputs are constructed; local epoch handles own their leases until destruction. |
| failure | Duplicate fixture row or unexpected output fails; apply/oracle-check errors propagate. |
| cost | Two runtime apply calls, epoch checks, one set insertion, and two check_current passes; repeated seed setup includes whole-query reference and cursor work. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0032

[Lines 226–247](../../../../../tests/unit/delta_replay_scale_test.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_current(const DeltaRuntime& runtime, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a runtime’s current answer and live image with the independent A04 oracle. |
| inputs / outputs | Evaluates A04 over runtime.plan() and fixture database; checks has_answer, drains core_results and results against expected, then compares delta-mode live_snapshot sequence/factors against A04 projections, or requires no live snapshot in maintenance, and checks invariants. |
| invariants | Core and public result relations must both equal A04; delta live sequence must equal runtime sequence; maintenance mode has no live image. The live factor oracle is projection of full answers, not event-history replay. |
| ownership | Borrows runtime and label; cursor handles are taken by value in drain_current and drained; oracle Relations/projections are local owning copies. |
| failure | Any mismatch throws; evaluator, cursor, export, invariant, and allocation failures propagate. |
| cost | Per call runs full A04 evaluation, drains two current-result cursors, and in delta mode reads/copies live snapshot and recomputes projections; also invokes invariant checks. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0033

[Lines 248–254](../../../../../tests/unit/delta_replay_scale_test.cpp#L248); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L248-L254:sha256:5e9f8bac320eb8031801796adef0bb8e64062579e9af3e20ab2a0e6dd6bd1331
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_replay_scale_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0034

[Lines 255–260](../../../../../tests/unit/delta_replay_scale_test.cpp#L255); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ScaleMetrics
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group the four runtime metric snapshots returned by one scale scenario. |
| inputs / outputs | Stores insertion/deletion metrics for replay and anchored completion by value. |
| invariants | The structure records four operations; it does not compare or normalize their counters. |
| ownership | Owns metric values. |
| failure | No behavior. |
| cost | Fixed-size metric copies. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0036

[Lines 262–283](../../../../../tests/unit/delta_replay_scale_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_insert_contract(const Event& replay, const Event& anchored, std::size_t count, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert source-derived insertion counters for ordered replay and anchored enumeration. |
| inputs / outputs | Accepts replay and anchored Event references, root count N, and label; checks changed_keys=N+1 for each; replay candidates/accepted/rejected/earlier_probes=N/N/0/0; anchored candidates/accepted/rejected/earlier_probes=2N/N/N/N; replay queue inserts/pops/erases/peak=N/N/0/N; replay spool rows/capacity=N/N; and replay route-stage counters equal epoch counters. |
| invariants | These are exact assertions for this chain fixture’s insertion at N=2 or N=64. They cover instrumented key/candidate/queue/spool counters and one stage, not all copying, allocations, CPU, or bytes. |
| ownership | Borrows events and label; no mutation of counters. |
| failure | Any mismatch throws; no native metrics are recomputed here. |
| cost | Fixed number of integer comparisons; callers form diagnostic strings and may allocate. Values are observations from the test runtime, not timing data. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/decisions/0011-reference-support.md](../../../../decisions/0011-reference-support.md) |

## B0038

[Lines 285–307](../../../../../tests/unit/delta_replay_scale_test.cpp#L285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_delete_contract(const Event& replay, const Event& anchored, std::size_t count, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert source-derived deletion counters and queued-child pruning for the chain fixture. |
| inputs / outputs | Checks changed_keys=N+1; replay candidates/accepted/rejected/earlier_probes=N/N/0/0; anchored candidates/accepted/rejected/earlier_probes=2N/N/N/N; replay queue inserts/pops/erases/peak=N+1/N/1/N+1; replay spool rows/capacity=N/N; and replay route-stage counters equal epoch counters. |
| invariants | Deletes the sole S child support from the R-root/S-child tree after N joined outputs exist. The changed queue initially includes N root keys and the S key; removing the last live parent key prunes the queued child key. Assertions characterize this fixture, not a general delay bound. |
| ownership | Borrows Events and label without retaining them. |
| failure | A mismatch throws; operation/evaluator errors occur in caller. |
| cost | Fixed number of comparisons; diagnostic arguments may allocate at call sites. The counters do not bound total copying, allocator work, or CPU. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/decisions/0011-reference-support.md](../../../../decisions/0011-reference-support.md) |

## B0040

[Lines 309–328](../../../../../tests/unit/delta_replay_scale_test.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScaleMetrics run_scale(std::size_t count)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one N-sized paired scale scenario and return its four metric snapshots. |
| inputs / outputs | Constructs ScaleRun, bootstraps, inserts S(7,9), checks insertion contract and raw cardinality N for both strategies, erases S, checks deletion contract and cardinality, then returns replay/anchored metrics for insert/delete. |
| invariants | Only this two-event chain workload is covered; answer count is N for both insert and delete. |
| ownership | Owns ScaleRun for the call; returns metric values by copy. |
| failure | Assertion, runtime, A04, and allocation failures propagate. |
| cost | Runs paired runtime construction/seeding, two paired applies and output drains, exact A04 evaluation, current-state checks and counter checks. N controls fixture/work size; no elapsed-time measure. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/decisions/0011-reference-support.md](../../../../decisions/0011-reference-support.md) |

## B0041

[Lines 329–331](../../../../../tests/unit/delta_replay_scale_test.cpp#L329); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L329-L331:sha256:256a056aa47c0bb3efa1c4585056d60f26fe0eb03d3b6f3c943442a9e15cc057
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_replay_scale_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0042

[Lines 332–335](../../../../../tests/unit/delta_replay_scale_test.cpp#L332); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhaseMaxima phase_maxima(const DeltaMetrics& metrics)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract first, next, and last replay producer work maxima as a tuple. |
| inputs / outputs | Returns replay_max_first_work, replay_max_next_work, and replay_max_last_work from a DeltaMetrics value. |
| invariants | Tuple order is fixed to first/next/last successful-transition producer work fields. |
| ownership | Borrows metrics and returns scalar copies. |
| failure | No helper-level failure. |
| cost | Fixed three scalar reads and tuple construction. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0044

[Lines 337–342](../../../../../tests/unit/delta_replay_scale_test.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_phase_metrics(const DeltaMetrics& metrics, const std::string& label)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require nonzero producer-work counters for each successful replay transition phase. |
| inputs / outputs | Checks first, next, and last maxima are all nonzero for the supplied metric snapshot. |
| invariants | This confirms the source instrumentation charged each phase; it does not measure delay, prove a bound, or refer to consumer-side epoch.next cost. |
| ownership | Borrows metrics and label. |
| failure | A zero field throws; no recovery. |
| cost | Three scalar comparisons; diagnostic argument may allocate at caller. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0046

[Lines 344–383](../../../../../tests/unit/delta_replay_scale_test.cpp#L344); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accepted_transition_work_does_not_grow_with_output_count()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare ordered-replay phase counters at N=2 and N=64 while observing setup/finalization growth. |
| inputs / outputs | Runs complete insert/delete scenarios for counts 2 and 64; checks nonzero phase maxima on each replay insert/delete snapshot; requires first/next/last producer maxima equal across sizes for insert and erase; requires replay_preparation_work and finalization_work grow for larger N; prints four metric summaries. |
| invariants | The asserted equality concerns instrumented producer work maxima for these two fixed sizes; preparation and explicit finalization grow with changed keys. DeltaRuntime::apply drains producer and commits before the returned epoch is consumed, so these maxima are producer-phase counters, not a bound on consumer delay or CPU. |
| ownership | Each ScaleMetrics local owns copied counters; print lambda borrows them. |
| failure | Failed equality/growth assertion throws; output stream errors are not explicitly checked. |
| cost | Runs two N-sized fixtures, at N=2 and N=64. Each fixture performs an insertion and an erasure in both runtimes: four paired S updates in total, plus two setup/seeding campaigns and repeated A04/cursor checks. It compares counters and prints, without measuring wall-clock time or total bytes. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/decisions/0011-reference-support.md](../../../../decisions/0011-reference-support.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0047

[Lines 384–386](../../../../../tests/unit/delta_replay_scale_test.cpp#L384); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L384-L386:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_replay_scale_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [docs/incremental_live.md](../../../../incremental_live.md), [docs/code_review.md](../../../../code_review.md) |

## B0048

[Lines 387–395](../../../../../tests/unit/delta_replay_scale_test.cpp#L387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite ordered-replay scale comparison as a standalone test executable. |
| inputs / outputs | Calls accepted_transition_work_does_not_grow_with_output_count, prints success and returns 0; catches std::exception, prints what(), and returns 1 on failure. |
| invariants | Only std::exception is caught. The executable reports checks from the two fixed fixture sizes; it does not execute a proof or a benchmark. |
| ownership | Automatic local test objects own their runtime and fixture resources for each run. |
| failure | Caught std::exception becomes exit status 1; other exception types are not caught here. |
| cost | Runs two fixture sizes, each with a paired insertion and erasure, including their setup, A04 evaluation, current-state/cursor checks, counter comparisons and output. |
| Design | [tests/unit/delta_replay_scale_test.cpp](../../../../../tests/unit/delta_replay_scale_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [tests/reference/native_input.hpp](../../../../../tests/reference/native_input.hpp), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/decisions/0011-reference-support.md](../../../../decisions/0011-reference-support.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |
