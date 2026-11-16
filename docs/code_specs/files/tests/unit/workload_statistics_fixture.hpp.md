# `tests/unit/workload_statistics_fixture.hpp` — block usage map

[Source](../../../../../tests/unit/workload_statistics_fixture.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `178c355f0ce37667cebffda94fb587219b204321adf351f7f7e65357e1bdd905`. 80 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/workload_statistics_fixture.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/workload_statistics_fixture.hpp#L15) | Callable definition: inline Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0002) |
| [B0003 · 16–18](../../../../../tests/unit/workload_statistics_fixture.hpp#L16) | Callable definition: inline void check(bool condition,std::source_location at=std::source_location::current()) | calls std::source_location::current, std::runtime_error, std::string, file_name; guard inline void check(bool condition,std::source_location at=std::source_location::current()) { · [reviewed contract](#b0003) |
| [B0004 · 19–22](../../../../../tests/unit/workload_statistics_fixture.hpp#L19) | Callable definition: template&lt;class Action&gt; void error(Action&& action,std::string_view code) | calls action, check, code; guard try { action(); } catch (const Error& failure) { check(failure.code()==code); return; } · [reviewed contract](#b0004) |
| [B0005 · 23–25](../../../../../tests/unit/workload_statistics_fixture.hpp#L23) | Callable definition: inline ws::Options enabled(std::uint64_t period=1,std::uint64_t offset=0,std::uint64_t budget=65536) | calls ; returns result · [reviewed contract](#b0005) |
| [B0006 · 26–28](../../../../../tests/unit/workload_statistics_fixture.hpp#L26) | Callable definition: inline DeltaOptions delta_options(DeltaMode mode=DeltaMode::delta) | calls ; returns result · [reviewed contract](#b0006) |
| [B0007 · 29–46](../../../../../tests/unit/workload_statistics_fixture.hpp#L29) | Callable definition: inline PhysicalPlan plan(bool payload=false,bool generalized=false) | calls push_back, emplace_back, planner::lower_tree; returns planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0},; planner::lower_tree(catalog,query,Free…; growth emplace_back, push_back · [reviewed contract](#b0007) |
| [B0008 · 47–57](../../../../../tests/unit/workload_statistics_fixture.hpp#L47) | Callable definition: inline PhysicalPlan alias_plan(bool predicate=false) | calls planner::lower_tree; returns planner::lower_tree(catalog,query,FreeConnexTree{NodeId{0}, · [reviewed contract](#b0008) |
| [B0009 · 58–68](../../../../../tests/unit/workload_statistics_fixture.hpp#L58) | Callable definition: inline std::size_t find(const ws::Snapshot& snapshot,std::size_t table,SetOperation op,ws::Role role, std::optional&lt;NodeId&gt; node=… | calls descriptors, size, check; guard check(false); return 0;; returns i; 0; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 69–73](../../../../../tests/unit/workload_statistics_fixture.hpp#L69) | Callable definition: inline const ws::Cell& cell(const ws::Snapshot& snapshot,std::size_t table,SetOperation op,ws::Role role, std::optional&lt;NodeId&gt; n… | calls cells, find; returns snapshot.cells()\[find(snapshot,table,op,role,node,occurrence,edge,sign)\] · [reviewed contract](#b0010) |
| [B0011 · 74–76](../../../../../tests/unit/workload_statistics_fixture.hpp#L74) | Callable definition: inline void apply(DeltaRuntime& runtime,std::size_t table,SetOperation operation,Row row) | calls sequence, std::move, discard · [reviewed contract](#b0011) |
| [B0012 · 77–79](../../../../../tests/unit/workload_statistics_fixture.hpp#L77) | Callable definition: inline bool same_cells(std::span&lt;const ws::Cell&gt; a,std::span&lt;const ws::Cell&gt; b) | calls size, std::equal, begin, end; returns a.size()==b.size() && std::equal(a.begin(),a.end(),b.begin()) · [reviewed contract](#b0012) |
| [B0013 · 80–80](../../../../../tests/unit/workload_statistics_fixture.hpp#L80) | Closes surrounding scope/type. | source comment (unverified): // namespace workload_fixture · [reviewed contract](#b0013) |

## B0001

[Lines 1–14](../../../../../tests/unit/workload_statistics_fixture.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:175acf2857e13a761bd89f17c19f5fdad41974b0963f23aa83743a512fee582a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare workload_statistics_fixture.hpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;map&gt;, &lt;source_location&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/workload_statistics_fixture.hpp](../../../../../tests/unit/workload_statistics_fixture.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–15](../../../../../tests/unit/workload_statistics_fixture.hpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an integer Value from a signed scalar. |
| inputs / outputs | int64_t enters; owning Value exits. |
| invariants | No display conversion or runtime operation occurs. |
| ownership | Value owns the scalar alternative. |
| failure | No expected failure. |
| cost | Constant-size scalar construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 16–18](../../../../../tests/unit/workload_statistics_fixture.hpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void check(bool condition,std::source_location at=std::source_location::current()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a source-located workload fixture assertion. |
| inputs / outputs | Boolean and source_location enter; normal return or runtime_error exits. |
| invariants | Uses the call-site file/line when false. |
| ownership | No state escapes; exception owns its diagnostic string. |
| failure | False throws std::runtime_error; no workload/native Error is created. |
| cost | Only failure constructs a diagnostic. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 19–22](../../../../../tests/unit/workload_statistics_fixture.hpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void error(Action&& action,std::string_view code) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw a crown::Error with the exact expected code. |
| inputs / outputs | Forwarded callable and expected code enter; normal return only after matching code; otherwise assertion fails. |
| invariants | A different Error code fails; non-crown exceptions propagate. |
| ownership | Callable/captured owner state is borrowed during invocation; no action result is retained. |
| failure | Catches only crown::Error; mismatch or no exception becomes source-located runtime_error. |
| cost | One action call and exception dispatch. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 23–25](../../../../../tests/unit/workload_statistics_fixture.hpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline ws::Options enabled(std::uint64_t period=1,std::uint64_t offset=0,std::uint64_t budget=65536) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build counters-mode workload options with systematic sampling and bounded detail budget. |
| inputs / outputs | Period, offset, and budget enter with defaults 1,0,65536; Options exits. |
| invariants | Mode is counters; sample settings and detail cap are copied exactly and remain separate from owner-state Limits. |
| ownership | Returns scalar option values; no collector owns them until later configure. |
| failure | No expected failure; invalid period is tested at configure. |
| cost | Fixed-size option construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 26–28](../../../../../tests/unit/workload_statistics_fixture.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline DeltaOptions delta_options(DeltaMode mode=DeltaMode::delta) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct DeltaOptions in requested mode with O07 support observations disabled. |
| inputs / outputs | DeltaMode (default delta) enters; owning options value exits. |
| invariants | C01 workload counters can be tested without O07 clock/observation activity. |
| ownership | Options are returned by value; no runtime is retained. |
| failure | No expected failure. |
| cost | Fixed-size option construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 29–46](../../../../../tests/unit/workload_statistics_fixture.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan plan(bool payload=false,bool generalized=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower R(x,y), S(y), and unused(u), optionally with ignored payload or generalized G(y). |
| inputs / outputs | Payload/generalized flags enter; compiled PhysicalPlan exits. |
| invariants | Catalog IDs remain 0/1/2; payload appends an ignored source field; generalized mode changes head and uses G children R/S; default mode uses native R root/S child. |
| ownership | Plan owns catalog/query/tree; source builders are local. |
| failure | Planner validation/resource failure propagates. |
| cost | Builds and lowers a fixed two/three-node plan. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 47–57](../../../../../tests/unit/workload_statistics_fixture.hpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline PhysicalPlan alias_plan(bool predicate=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a generalized self-join with distinct left/right occurrences and optional right-side tag predicate. |
| inputs / outputs | Predicate flag enters; one-source, two-occurrence generalized plan exits. |
| invariants | Both occurrences project same x/y key but remain separate occurrence IDs; optional predicate constrains right tag to 1. |
| ownership | Returned plan owns input catalog/query/tree. |
| failure | Planner failures propagate. |
| cost | Lowers one fixed two-alias query. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 58–68](../../../../../tests/unit/workload_statistics_fixture.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::size_t find(const ws::Snapshot& snapshot,std::size_t table,SetOperation op,ws::Role role,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve one workload descriptor index by its real table, update operation, role, and optional identities. |
| inputs / outputs | Borrowed Snapshot and table/op/role/optional node-occurrence-edge-sign enter; descriptor index exits. |
| invariants | Operation is mapped from SetOperation; supplied identities must all match the same actual descriptor; missing match fails instead of assuming an index. |
| ownership | Snapshot owns descriptors; helper borrows them during linear scan. |
| failure | No match throws source-located runtime_error; no snapshot mutation. |
| cost | Linear scan over descriptor count. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 69–73](../../../../../tests/unit/workload_statistics_fixture.hpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const ws::Cell& cell(const ws::Snapshot& snapshot,std::size_t table,SetOperation op,ws::Role role,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a borrowed workload Cell selected through the descriptor identity helper. |
| inputs / outputs | Snapshot and descriptor selector arguments enter by reference/value; const Cell reference exits. |
| invariants | Returned cell lifetime is bounded by Snapshot lifetime; no copy or descriptor ID is cached. |
| ownership | Cell reference borrows snapshot-owned vector storage. |
| failure | Missing descriptor error propagates from find. |
| cost | One descriptor scan plus indexed span read. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 74–76](../../../../../tests/unit/workload_statistics_fixture.hpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void apply(DeltaRuntime& runtime,std::size_t table,SetOperation operation,Row row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one physical DeltaRuntime update and discard its signed output. |
| inputs / outputs | Borrowed runtime, source table, operation, and owning Row enter; update commits and output is discarded. |
| invariants | Sequence is current runtime sequence plus one; discarding output does not erase committed state or workload counters. |
| ownership | Runtime owns updated engine state; row moves into the update; output exists only for the call. |
| failure | Runtime validation/resource failures propagate. |
| cost | Executes one physical update and drains/discards its emitted output. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 77–79](../../../../../tests/unit/workload_statistics_fixture.hpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline bool same_cells(std::span<const ws::Cell> a,std::span<const ws::Cell> b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two Cell spans element by element. |
| inputs / outputs | Two borrowed const Cell spans enter; equality boolean exits. |
| invariants | Sizes must match and every same-position Cell must compare equal. |
| ownership | Spans borrow caller-owned snapshots; no copy is retained. |
| failure | No expected failure. |
| cost | Linear in cell count. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/workloads.md](../../../../workloads.md), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 80–80](../../../../../tests/unit/workload_statistics_fixture.hpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L80:sha256:8d48a44628cfb317d9fd6929f8bfe470c0a0f66030c1e5e7d35908b56720de97
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in workload_statistics_fixture.hpp: namespace workload_fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/workload_statistics_fixture.hpp](../../../../../tests/unit/workload_statistics_fixture.hpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |
