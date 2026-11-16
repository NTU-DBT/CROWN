# `tests/unit/prepared_epoch_test.cpp` — block usage map

[Source](../../../../../tests/unit/prepared_epoch_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4efb36790f8646cc632664dc7e88de1f8a7727d9f42c92ee846cfb4811b8174c`. 659 lines partitioned into 44 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/prepared_epoch_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../../tests/unit/prepared_epoch_test.cpp#L22) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0002) |
| [B0003 · 25–25](../../../../../tests/unit/prepared_epoch_test.cpp#L25) | Explanatory comments or spacing. |  |
| [B0004 · 26–35](../../../../../tests/unit/prepared_epoch_test.cpp#L26) | Callable definition: void check_rollback_statistics(const storage::ArenaStatistics& before, const storage::ArenaStatistics& after, const std::string& … | calls check; guard check(before.live_records == after.live_records &&; source comment (unverified): // Failed writes may grow the arena's high-water mark and free-slot count. · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/prepared_epoch_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0006 · 37–47](../../../../../tests/unit/prepared_epoch_test.cpp#L37) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls action, check, code, std::string; guard check(failure.code() == code, · [reviewed contract](#b0006) |
| [B0007 · 48–48](../../../../../tests/unit/prepared_epoch_test.cpp#L48) | Explanatory comments or spacing. |  |
| [B0008 · 49–49](../../../../../tests/unit/prepared_epoch_test.cpp#L49) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0008) |
| [B0009 · 50–50](../../../../../tests/unit/prepared_epoch_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0010 · 51–59](../../../../../tests/unit/prepared_epoch_test.cpp#L51) | Callable definition: PhysicalPlan unary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0010) |
| [B0011 · 60–60](../../../../../tests/unit/prepared_epoch_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0012 · 61–74](../../../../../tests/unit/prepared_epoch_test.cpp#L61) | Callable definition: PhysicalPlan loop_alias_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0012) |
| [B0013 · 75–75](../../../../../tests/unit/prepared_epoch_test.cpp#L75) | Explanatory comments or spacing. |  |
| [B0014 · 76–87](../../../../../tests/unit/prepared_epoch_test.cpp#L76) | Callable definition: PhysicalPlan boolean_alias_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0014) |
| [B0015 · 88–88](../../../../../tests/unit/prepared_epoch_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0016 · 89–91](../../../../../tests/unit/prepared_epoch_test.cpp#L89) | Callable definition: bool same_tuple(const storage::Tuple& left, const storage::Tuple& right) | calls values; returns left.values() == right.values() · [reviewed contract](#b0016) |
| [B0017 · 92–92](../../../../../tests/unit/prepared_epoch_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0018 · 93–125](../../../../../tests/unit/prepared_epoch_test.cpp#L93) | Callable definition: bool same_snapshot(const SupportSnapshot& left, const SupportSnapshot& right) | calls size, has_value, same_tuple; returns false; false; 5 loop sites · [reviewed contract](#b0018) |
| [B0019 · 126–126](../../../../../tests/unit/prepared_epoch_test.cpp#L126) | Explanatory comments or spacing. |  |
| [B0020 · 127–134](../../../../../tests/unit/prepared_epoch_test.cpp#L127) | Callable definition: void expect_closed(SupportRuntime::PendingEpoch& pending) | calls check, active, expect_error, stage; guard check(!pending.active(), "closed prepared epoch still reports active"); · [reviewed contract](#b0020) |
| [B0021 · 135–135](../../../../../tests/unit/prepared_epoch_test.cpp#L135) | Explanatory comments or spacing. |  |
| [B0022 · 136–150](../../../../../tests/unit/prepared_epoch_test.cpp#L136) | Callable definition: void check_busy_readers(SupportRuntime& runtime, SupportHandle existing) | calls expect_error, has_answer, snapshot, find; growth insert · [reviewed contract](#b0022) |
| [B0023 · 151–151](../../../../../tests/unit/prepared_epoch_test.cpp#L151) | Explanatory comments or spacing. |  |
| [B0024 · 152–158](../../../../../tests/unit/prepared_epoch_test.cpp#L152) | Callable definition: Relation visible_answers(const SupportSnapshot& snapshot, NodeId root) | calls at, check, has_value, insert; guard check(visible.has_value(), "query root has no visible projection");; returns result; growth insert; 1 loop sites · [reviewed contract](#b0024) |
| [B0025 · 159–159](../../../../../tests/unit/prepared_epoch_test.cpp#L159) | Explanatory comments or spacing. |  |
| [B0026 · 160–167](../../../../../tests/unit/prepared_epoch_test.cpp#L160) | Callable definition: void check_reference_answers(const SupportRuntime& runtime, const SupportSnapshot& snapshot, const Database& database) | calls reference::evaluate, reference::input::catalog, plan, catalog; guard check(snapshot.has_answer == !expected.empty(), · [reviewed contract](#b0026) |
| [B0027 · 168–168](../../../../../tests/unit/prepared_epoch_test.cpp#L168) | Explanatory comments or spacing. |  |
| [B0028 · 169–217](../../../../../tests/unit/prepared_epoch_test.cpp#L169) | Callable definition: void check_epoch_trace(const SupportEpoch& epoch, std::size_t changed_native_stages) | calls check, size, by_application, seen_id; guard check(epoch.journal != nullptr && epoch.journal-&gt;sequence == epoch.sequence,; returns value; event != nullptr; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 218–218](../../../../../tests/unit/prepared_epoch_test.cpp#L218) | Explanatory comments or spacing. |  |
| [B0030 · 219–300](../../../../../tests/unit/prepared_epoch_test.cpp#L219) | Callable definition: void busy_preview_commit_and_rollback() | calls runtime, unary_plan, apply, n; guard check(first.native_changed && existing.has_value(), "busy-reader fixture did not commit its first r…; growth insert · [reviewed contract](#b0030) |
| [B0031 · 301–301](../../../../../tests/unit/prepared_epoch_test.cpp#L301) | Explanatory comments or spacing. |  |
| [B0032 · 302–399](../../../../../tests/unit/prepared_epoch_test.cpp#L302) | Callable definition: void loop_edge_aliases_accumulate_new_new_cross_terms() | calls loop_alias_plan, runtime, begin_epoch, check; guard check(pending.stage(NodeId{1}, Row{n(1), n(2)}), "forward alias insertion was a no-op");; growth insert, resize; 4 loop sites; source comment (unverified): // Both occurrences are aliases of the same physical edge relation. Rows · [reviewed contract](#b0032) |
| [B0033 · 400–400](../../../../../tests/unit/prepared_epoch_test.cpp#L400) | Explanatory comments or spacing. |  |
| [B0034 · 401–449](../../../../../tests/unit/prepared_epoch_test.cpp#L401) | Callable definition: void same_scope_aliases_and_boolean_nullary_projection_counts() | calls boolean_alias_plan, runtime, begin_epoch, check; guard check(pending.stage(NodeId{2}, Row{n(6)}) && pending.stage(NodeId{1}, Row{n(6)}),; growth insert, resize; 2 loop sites · [reviewed contract](#b0034) |
| [B0035 · 450–450](../../../../../tests/unit/prepared_epoch_test.cpp#L450) | Explanatory comments or spacing. |  |
| [B0036 · 451–520](../../../../../tests/unit/prepared_epoch_test.cpp#L451) | Callable definition: void invalid_stages_abort_whole_epoch_and_allow_retry() | calls runtime, boolean_alias_plan, apply, n; guard check(old_handle.has_value() && before.has_answer, "invalid-stage fixture lacks a live old answer");; growth insert, resize · [reviewed contract](#b0036) |
| [B0037 · 521–521](../../../../../tests/unit/prepared_epoch_test.cpp#L521) | Explanatory comments or spacing. |  |
| [B0038 · 522–564](../../../../../tests/unit/prepared_epoch_test.cpp#L522) | Callable definition: void work_and_support_failures_abort_partial_epochs() | calls probe, unary_plan, apply, n; guard check(measured &gt; 0, "work-limit fixture measured no native work");; growth insert · [reviewed contract](#b0038) |
| [B0039 · 565–565](../../../../../tests/unit/prepared_epoch_test.cpp#L565) | Explanatory comments or spacing. |  |
| [B0040 · 566–590](../../../../../tests/unit/prepared_epoch_test.cpp#L566) | Callable definition: void pending_owns_runtime_impl_across_facade_move_and_destruction() | calls source, unary_plan, begin_epoch, destination; guard check(pending.stage(NodeId{0}, Row{n(8)}), "moved-facade stage was a no-op");; growth emplace, insert · [reviewed contract](#b0040) |
| [B0041 · 591–591](../../../../../tests/unit/prepared_epoch_test.cpp#L591) | Explanatory comments or spacing. |  |
| [B0042 · 592–640](../../../../../tests/unit/prepared_epoch_test.cpp#L592) | Callable definition: void moved_from_tokens_and_changed_value_journals() | calls runtime, unary_plan, begin_epoch, std::move; guard check(!source.active() && destination.active(), "move did not transfer pending epoch ownership");; returns record.handle.role == SupportRole::records && record.tuple().values() == Row{n(1000)}; growth insert; 3 loop sites · [reviewed contract](#b0042) |
| [B0043 · 641–643](../../../../../tests/unit/prepared_epoch_test.cpp#L641) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0043) |
| [B0044 · 644–659](../../../../../tests/unit/prepared_epoch_test.cpp#L644) | Callable definition: int main() | calls busy_preview_commit_and_rollback, loop_edge_aliases_accumulate_new_new_cross_terms, same_scope_aliases_and_boolean_nullary_projection_counts, invalid_stages_abort_whole_epoch_and_allow_retry; returns 1; 0 · [reviewed contract](#b0044) |

## B0001

[Lines 1–21](../../../../../tests/unit/prepared_epoch_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:b803f1e248de445c4a5fb8831a25d23bce65dc95d0623d1b8f76d4214715b79f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare prepared_epoch_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/support.hpp", "evaluator.hpp", "native_input.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/prepared_epoch_test.cpp](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 22–24](../../../../../tests/unit/prepared_epoch_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a test immediately when a boolean assertion is false. |
| inputs / outputs | Accepts a condition and diagnostic string; returns normally when true and throws std::runtime_error(message) when false. |
| invariants | The helper checks only the supplied condition; it does not interpret engine state or prove a runtime property. |
| ownership | The diagnostic string is borrowed for the call; no fixture or runtime owner is retained. |
| failure | False conditions throw; message construction may itself allocate before the test runner handles the failure. |
| cost | Constant-time check on the supplied bool. Constructing the caller-owned diagnostic precedes the call; std::runtime_error may copy/allocate its message on the false branch. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0002 L22-L24](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0004

[Lines 26–35](../../../../../tests/unit/prepared_epoch_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_rollback_statistics(const storage::ArenaStatistics& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare arena rollback statistics around one failed prepared epoch. |
| inputs / outputs | Accepts before/after ArenaStatistics and a context label; checks equal live_records, retained_records and pins, and nondecreasing aggregate slots. |
| invariants | The assertion permits the arena high-water slot count and free-slot count to grow after failed writes; it does not require allocator or capacity rollback. |
| ownership | Statistics and context are borrowed test values; the helper retains no arena state. |
| failure | A mismatch throws through check with the supplied context. |
| cost | Three scalar comparisons; message concatenation is on assertion failure. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0004 L26-L35](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/runtime_support.md §Atomicity and accounting](../../../../runtime_support.md) |

## B0006

[Lines 37–47](../../../../../tests/unit/prepared_epoch_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an action throws the requested public Error code. |
| inputs / outputs | Invokes a forwarded action, catches crown::Error, and compares failure.code() with the expected string_view. |
| invariants | Only the Error type and exact code are accepted; no exception or a different code fails the assertion. |
| ownership | Action and expected code are borrowed for the call; the caught exception remains owned by the catch scope. |
| failure | A mismatched Error or missing Error throws std::runtime_error; unrelated exception types propagate. |
| cost | One action invocation and one code comparison; failure diagnostics may allocate. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0006 L37-L47](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |

## B0008

[Lines 49–49](../../../../../tests/unit/prepared_epoch_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an int64 Value fixture. |
| inputs / outputs | Converts one std::int64_t value to crown::Value and returns it by value. |
| invariants | Preserves the exact signed integer selected by the fixture; this helper makes no runtime admission claim. |
| ownership | The returned variant owns its scalar value. |
| failure | Any variant conversion failure propagates to the caller. |
| cost | Scalar construction and return; no row scan. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0008 L49-L49](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md) |

## B0010

[Lines 51–59](../../../../../tests/unit/prepared_epoch_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-table, one-native-node unary support plan. |
| inputs / outputs | Constructs catalog unary(x:int64), query unary(x) with x as output, and a one-node native tree; returns planner::lower_tree output. |
| invariants | The fixture has one logical occurrence, one visible variable and root NodeId{0}; assertions using it address that exact shape. |
| ownership | Catalog, query and tree are local values copied or consumed by lowering; the returned PhysicalPlan owns its plan data. |
| failure | Planner rejection propagates from lower_tree; the helper does not catch it. |
| cost | Small fixed catalog/query/tree construction and lowering over one variable and one node. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0010 L51-L59](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0012

[Lines 61–74](../../../../../tests/unit/prepared_epoch_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan loop_alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-occurrence loop-alias plan over one physical edge table. |
| inputs / outputs | Creates forward(x,y) and reverse(y,x) occurrences over edge(from,to), under a generalized root with two native children; lowers and returns the plan. |
| invariants | The two child ports expose opposite logical tuple orders while referring to the same physical relation; the fixture distinguishes alias presence and cross terms. |
| ownership | Local catalog/query/tree are inputs to lowering; the returned plan owns compiled metadata. |
| failure | Planner validation errors propagate. |
| cost | Fixed two-atom plan construction and lowering; test data size is supplied by the caller. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0012 L61-L74](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/physical_runtime.md §Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0014

[Lines 76–87](../../../../../tests/unit/prepared_epoch_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan boolean_alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-alias unary plan with a nullary Boolean output. |
| inputs / outputs | Creates two occurrences of unary(x) over one table, a generalized intersection root, and an empty query head; lowers and returns the plan. |
| invariants | The root requires both same-scope aliases, while the public answer is Boolean/nullary; the fixture is used to check existential and projection support counts. |
| ownership | The returned PhysicalPlan owns lowered metadata; temporary descriptors remain local. |
| failure | Planner rejection propagates. |
| cost | Fixed three-node plan construction and lowering. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0014 L76-L87](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md) |

## B0016

[Lines 89–91](../../../../../tests/unit/prepared_epoch_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_tuple(const storage::Tuple& left, const storage::Tuple& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two storage tuples by their public value sequences. |
| inputs / outputs | Accepts two Tuple references and returns whether left.values() equals right.values(). |
| invariants | Only scalar sequences are compared; owner handles, tuple identity and layout-token identity are not compared by this helper. |
| ownership | Both tuples are borrowed for the comparison; no tuple is retained. |
| failure | Value comparison exceptions propagate. |
| cost | Compares the tuple fields, proportional to tuple arity and value comparison cost. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0016 L89-L91](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/runtime_support.md §Maintained state](../../../../runtime_support.md) |

## B0018

[Lines 93–125](../../../../../tests/unit/prepared_epoch_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_snapshot(const SupportSnapshot& left, const SupportSnapshot& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the snapshot fields used as rollback equality evidence. |
| inputs / outputs | Checks sequence, answer flag, node count and node identity/kind; then compares record tuples/handles/flags, survivor tuple values, P-key tuples/handles/counts and optional E-key tuples/handles/counts. |
| invariants | Returns true only when these enumerated fields and vector lengths match. Fields not named in the body are outside this helper's equality predicate. |
| ownership | Snapshots are borrowed owning test values; all nested tuple comparisons occur while they remain alive. |
| failure | Returns false on the first mismatch; equality failures from value comparison propagate. |
| cost | Linear over nodes, records, survivors, parent keys and visible keys; no copies of the complete snapshots. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0018 L93-L125](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/runtime_support.md §Maintained state](../../../../runtime_support.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0020

[Lines 127–134](../../../../../tests/unit/prepared_epoch_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_closed(SupportRuntime::PendingEpoch& pending) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the observable closed-token behavior after commit or rollback. |
| inputs / outputs | Accepts a PendingEpoch reference; asserts inactive state, expects invalid_epoch from stage/preview/snapshot/commit, then calls rollback again. |
| invariants | The helper checks those four closed-token operations and idempotent repeat rollback only. |
| ownership | The caller retains the token; the helper does not take ownership. |
| failure | Any wrong activity state or error code fails via the local assertion helpers. |
| cost | Four expected-error invocations and one rollback call. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0020 L127-L134](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §API and ownership](../../../../prepared_epochs.md) |

## B0022

[Lines 136–150](../../../../../tests/unit/prepared_epoch_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_busy_readers(SupportRuntime& runtime, SupportHandle existing) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that public runtime reads and mutations are blocked during a pending writer. |
| inputs / outputs | Uses a runtime and an existing SupportHandle; expects runtime_busy from has_answer, snapshot, find, get, storage_statistics, check_invariants, apply and begin_epoch. |
| invariants | The checks cover the listed APIs on this fixture; plan/options/owner and sequence access are not tested here. |
| ownership | Runtime and handle are borrowed; the helper neither closes the pending token nor retains the handle. |
| failure | Any call returning normally or throwing a different Error code fails. |
| cost | Eight API attempts with small fixed lookup/update arguments. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0022 L136-L150](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §API and ownership](../../../../prepared_epochs.md), [docs/physical_runtime.md §Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0024

[Lines 152–158](../../../../../tests/unit/prepared_epoch_test.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation visible_answers(const SupportSnapshot& snapshot, NodeId root) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the selected root's visible keys as an owning test Relation. |
| inputs / outputs | Reads snapshot.nodes\[root.value\].visible_keys, requires that projection to exist, exports each key tuple's values to a Relation, and returns the set. |
| invariants | The result is a set of projected root keys; absent visible_keys fails. This conversion does not inspect nonroot factors. |
| ownership | The snapshot is borrowed while rows are exported; the returned Relation owns exported row values. |
| failure | Missing root projection fails via check; out-of-range node access propagates std::out_of_range. |
| cost | Visits and exports each visible key; work follows the selected root result size and value arity. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0024 L152-L158](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/runtime_support.md §Maintained state](../../../../runtime_support.md) |

## B0026

[Lines 160–167](../../../../../tests/unit/prepared_epoch_test.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_reference_answers(const SupportRuntime& runtime, const SupportSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare tentative visible answers and truth with the full reference CQ evaluator. |
| inputs / outputs | Evaluates the runtime plan's catalog/query against a Database via reference::evaluate; checks snapshot.has_answer and exported root visible answers against that result. |
| invariants | The comparison covers the finite supplied database and query. The reference evaluator is a differential oracle, not a universal proof or a current execution claim. |
| ownership | Runtime, snapshot and database are borrowed; expected and exported relations are local owning values. |
| failure | Any disagreement fails by check; evaluator or export errors propagate. |
| cost | Runs full reference evaluation and copies projected root keys; cost scales with this fixture's database/query and result sizes. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0026 L160-L167](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md) |

## B0028

[Lines 169–217](../../../../../tests/unit/prepared_epoch_test.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_epoch_trace(const SupportEpoch& epoch, std::size_t changed_native_stages) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check aggregate event, application-order and journal-record accounting in a committed or preview epoch. |
| inputs / outputs | Accepts SupportEpoch and changed native stage count; validates journal sequence, event totals, contiguous event IDs/ordinals, earlier child causes, native/child counts and journal record ordinals/causes. |
| invariants | The assertions match the documented prepared-epoch trace shape for the supplied epoch; they do not prove causality for executions not represented by this trace. |
| ownership | Epoch and journal are borrowed; temporary pointer/seen vectors own only their diagnostics. |
| failure | Missing journal or any counter/order/cause mismatch throws through check. |
| cost | Allocates two vectors proportional to event count and scans events and journal records once. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0028 L169-L217](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md), [docs/runtime_support.md §Logical trace diagnostic](../../../../runtime_support.md) |

## B0030

[Lines 219–300](../../../../../tests/unit/prepared_epoch_test.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void busy_preview_commit_and_rollback() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise prepared-token busy reads, preview isolation, commit, no-op sequencing and rollback. |
| inputs / outputs | Starts from unary row 1; rejects invalid begin requests; stages a duplicate then row 2; inspects preview/snapshot, commits sequence 2, checks closed-token behavior and a no-op sequence 3, then explicitly and destructively rolls back sequence-4 attempts. |
| invariants | Assertions check one committed publication boundary, no work/journal for duplicate membership, owner-only tentative inspection, retained old handle, and no sequence/state change on rollback. |
| ownership | Local runtime owns plan state; pending tokens, snapshots and handles live within the case. The explicit snapshot is a test copy, not production rollback storage. |
| failure | Exact Error codes and state equality are asserted; any failure aborts the test through std::runtime_error. |
| cost | Small unary rows, snapshots at selected boundaries and a few public API calls; snapshot copies are separate from support work metrics. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0030 L219-L300](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0032

[Lines 302–399](../../../../../tests/unit/prepared_epoch_test.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void loop_edge_aliases_accumulate_new_new_cross_terms() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise same-epoch alias staging, loop cross terms, trace aggregation and erase/no-op behavior. |
| inputs / outputs | Stages both orientations of two edge rows across forward/reverse aliases; checks incomplete and completed tentative support, commits against a full CQ evaluator, then commits an absent erase and removes an edge from both aliases. |
| invariants | The finite assertions require newly staged aliases to see earlier tentative prefixes, preserve exact P/E/root counts and publish one sequence; the case is not a general proof of recurrence correctness. |
| ownership | Pending token/runtime own mutable support state; snapshots, database and returned epoch are case-local owning values. |
| failure | Failures in an assertion or evaluator comparison fail the case; engine errors are not injected here. |
| cost | Four changed insertion stages, selected snapshots, trace scans and full reference evaluations on a two-row database. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0032 L302-L399](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md), [docs/physical_runtime.md §Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0034

[Lines 401–449](../../../../../tests/unit/prepared_epoch_test.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void same_scope_aliases_and_boolean_nullary_projection_counts() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise same-scope aliases and multiplicity of a Boolean nullary projection. |
| inputs / outputs | Stages values 6 and 5 through both native aliases under a generalized root; checks two distinct survivors but one empty visible key with support count two, then compares the committed answer with the reference evaluator. |
| invariants | The fixture asserts existential answer presence and exact local support counters for two finite values; it does not equate support count with duplicate public rows. |
| ownership | Runtime and pending token own native state; snapshots and reference Database/Relation are local values. |
| failure | Assertion/evaluator mismatch fails the test; no production error path is added. |
| cost | Four changed stages, snapshots, invariant scan and one small reference evaluation. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0034 L401-L449](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/semantics.md §Answers and Boolean queries](../../../../semantics.md), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md), [docs/reference_fuzz.md §Scope](../../../../reference_fuzz.md) |

## B0036

[Lines 451–520](../../../../../tests/unit/prepared_epoch_test.cpp#L451); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void invalid_stages_abort_whole_epoch_and_allow_retry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whole-token rollback for invalid stages and successful retry at the same sequence. |
| inputs / outputs | Begins with two committed aliases; tests a wrong-typed row, out-of-range node and generalized-node stage after earlier private changes; after each failure compares prior snapshots/statistics/handles and retries valid stages. |
| invariants | The test asserts exact error codes, restored public state and nondecreasing arena slots while live/retained/pin counts match; rollback may preserve higher storage high-water state. |
| ownership | Runtime owns committed state; token and snapshots are local. Old SupportHandle is checked while runtime owner remains alive. |
| failure | Expected invalid_tuple and invalid_native_update failures abort earlier stages; each failure must leave sequence retryable. |
| cost | Several small alias stages, snapshot/statistics scans, retry commits and full reference evaluations. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0036 L451-L520](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/prepared_epochs.md §API and ownership](../../../../prepared_epochs.md), [docs/runtime_support.md §Atomicity and accounting](../../../../runtime_support.md) |

## B0038

[Lines 522–564](../../../../../tests/unit/prepared_epoch_test.cpp#L522); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void work_and_support_failures_abort_partial_epochs() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise epoch-wide work and support limits after a partial stage, then retry. |
| inputs / outputs | Measures one unlimited unary insert's work; uses that amount as a fresh runtime's epoch work cap, stages one row and expects resource_limit on a second; separately caps support at one and expects support_overflow on the second row. |
| invariants | The assertions test these selected budget boundaries and restoration/retry on a unary fixture; this is not an allocation-failure sweep or a general resource-bound proof. |
| ownership | Each runtime/token owns its own state and account; the measured probe is a separate runtime from limited_work. |
| failure | Limit errors must close and roll back the token without consuming sequence; same-sequence retries are asserted. |
| cost | One calibration update plus bounded two-stage attempts, snapshots and arena statistics; work cap is the observed fixture count. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0038 L522-L564](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §Batch event and resource accounting](../../../../prepared_epochs.md), [docs/prepared_epochs.md §Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0040

[Lines 566–590](../../../../../tests/unit/prepared_epoch_test.cpp#L566); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pending_owns_runtime_impl_across_facade_move_and_destruction() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a pending token retains runtime implementation across facade move or destruction. |
| inputs / outputs | Stages/commits one row after moving a SupportRuntime facade; then detaches a pending token from a temporary facade, stages it, snapshots and commits. |
| invariants | The case asserts owner implementation survives these two lifetimes and sequence boundaries; it checks no concurrent/thread behavior. |
| ownership | PendingEpoch retains shared runtime implementation; local facade and optional token scopes determine destruction order. |
| failure | Any invalid moved-token behavior or lost tentative answer fails through assertions. |
| cost | Two unary token lifecycles and one tentative snapshot. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0040 L566-L590](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §API and ownership](../../../../prepared_epochs.md) |

## B0042

[Lines 592–640](../../../../../tests/unit/prepared_epoch_test.cpp#L592); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void moved_from_tokens_and_changed_value_journals() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check move-only token transfer and changed-value journal retention after unrelated rows are removed. |
| inputs / outputs | Moves an active token and expects moved-from methods to report invalid_epoch; commits the destination. In a second runtime, inserts 32 unrelated rows plus row 1000, retains a one-change journal, erases all rows and destroys the runtime facade. |
| invariants | The finite case checks journal record count is below 32, retained journal tuples with tracked roles equal row 1000, and one changed native tuple survives facade destruction. It does not establish a universal asymptotic memory bound. |
| ownership | Token move transfers implementation ownership; a shared_ptr&lt;const SupportJournal&gt; deliberately outlives journal_runtime and pins only observed journal payload. |
| failure | Wrong token codes, unrelated-row capture or expired tuple access fail the test. |
| cost | 32 insert/erase update pairs, journal scans and storage-statistics reads; this is a bounded retention comparison, not a performance benchmark. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0042 L592-L640](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md §API and ownership](../../../../prepared_epochs.md), [docs/runtime_support.md §Atomicity and accounting](../../../../runtime_support.md) |

## B0043

[Lines 641–643](../../../../../tests/unit/prepared_epoch_test.cpp#L641); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L641-L643:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in prepared_epoch_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/prepared_epoch_test.cpp](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/code_review.md](../../../../code_review.md) |

## B0044

[Lines 644–659](../../../../../tests/unit/prepared_epoch_test.cpp#L644); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the prepared logical-epoch cases and report process status. |
| inputs / outputs | Calls seven named test cases; prints a success line only after all return, catches std::exception, prints its message and returns 1 on failure. |
| invariants | The process status reflects these assertion cases when this executable is invoked; this source review does not claim it was built or run. |
| ownership | Each case owns and releases its fixtures; main owns only the process-level exception boundary. |
| failure | Any propagated standard exception returns failure status 1. |
| cost | Sequentially runs the seven finite cases and their documented fixture work. |
| Design | [tests/unit/prepared_epoch_test.cpp §B0044 L644-L659](../../../../../tests/unit/prepared_epoch_test.cpp), [docs/code_review.md §Coverage and retained evidence](../../../../code_review.md) |
