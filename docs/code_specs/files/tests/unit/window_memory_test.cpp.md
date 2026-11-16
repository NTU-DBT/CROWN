# `tests/unit/window_memory_test.cpp` — block usage map

[Source](../../../../../tests/unit/window_memory_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d47421d340ee174ad1cefec9e43f2b1a65d2ceab86f17e1c2e6b12803fa36714`. 212 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/window_memory_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 13–15](../../../../../tests/unit/window_memory_test.cpp#L13) | Callable definition: void check(bool condition,std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 16–22](../../../../../tests/unit/window_memory_test.cpp#L16) | Callable definition: PhysicalPlan plan(bool indexed) | calls push_back, planner::lower_tree, s04_runtime::options; returns planner::lower_tree(catalog,Query{{},{},{},false},FreeConnexTree{},indexed?s04_runtime::options():P…; growth push_back; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 23–25](../../../../../tests/unit/window_memory_test.cpp#L23) | Callable definition: DeltaOptions options(std::uint64_t cap=64*1024*1024) | calls ; returns result · [reviewed contract](#b0004) |
| [B0005 · 26–28](../../../../../tests/unit/window_memory_test.cpp#L26) | Callable definition: WindowOptions windows(WindowFifoPolicy fifo=WindowFifoPolicy::global) | calls ; returns result · [reviewed contract](#b0005) |
| [B0006 · 29–32](../../../../../tests/unit/window_memory_test.cpp#L29) | Callable definition: Row row(std::int64_t id,std::size_t bytes=8192) | calls std::string, Date::parse, Decimal::parse; returns {id,std::string(@ ,7)+std::string(bytes,@ ),true,Date::parse(@ ), · [reviewed contract](#b0006) |
| [B0007 · 33–35](../../../../../tests/unit/window_memory_test.cpp#L33) | Callable definition: io::WindowCommand insertion(std::uint64_t sequence,std::uint64_t label,TableId table,const Row& values) | calls ; returns {sequence,io::WindowInsert{label,table,values,0},{}} · [reviewed contract](#b0007) |
| [B0008 · 36–40](../../../../../tests/unit/window_memory_test.cpp#L36) | Callable definition: void controller_only(const resource::MemoryAccount& account) | calls check_invariants, statistics, check, resource::MemoryAccount::control_bytes; guard check(usage.allocations==1 && usage.requested_bytes==resource::MemoryAccount::control_bytes(), · [reviewed contract](#b0008) |
| [B0009 · 41–43](../../../../../tests/unit/window_memory_test.cpp#L41) | declares types or opens a type body. |  · [reviewed contract](#b0009) |
| [B0010 · 44–45](../../../../../tests/unit/window_memory_test.cpp#L44) | Callable definition: Fixture(bool indexed,std::uint64_t cap=64*1024*1024,WindowFifoPolicy fifo=WindowFifoPolicy::global) :runtime(plan(indexed),option… | calls runtime, plan, options, window · [reviewed contract](#b0010) |
| [B0011 · 46–46](../../../../../tests/unit/window_memory_test.cpp#L46) | Callable definition: resource::MemoryAccount account() const | calls plan; returns runtime.plan().account() · [reviewed contract](#b0011) |
| [B0012 · 47–69](../../../../../tests/unit/window_memory_test.cpp#L47) | Callable definition: void accept(const io::WindowCommand& command,bool count_requests=false) | calls account, statistics, emplace, prepare; guard if(count_requests)check(calls==account().statistics().successful_allocations-before && calls&gt;0,; growth emplace; source comment (unverified): // A persistent upstream failure scope remains active through publication; · [reviewed contract](#b0012) |
| [B0013 · 70–70](../../../../../tests/unit/window_memory_test.cpp#L70) | Closes surrounding scope/type. |  · [reviewed contract](#b0013) |
| [B0014 · 71–97](../../../../../tests/unit/window_memory_test.cpp#L71) | Callable definition: void controls_and_retained_values(bool indexed) | calls row, insertion, runtime, plan; guard check(calls==account.statistics().successful_allocations-before,; growth emplace · [reviewed contract](#b0014) |
| [B0015 · 98–110](../../../../../tests/unit/window_memory_test.cpp#L98) | Callable definition: void allocation_and_prefixes(bool indexed,WindowFifoPolicy fifo) | calls f, row, insertion, accept; guard const auto before=f.window.canonical_state();check(before.labels.size()==3 && before.counts.size()=… · [reviewed contract](#b0015) |
| [B0016 · 111–116](../../../../../tests/unit/window_memory_test.cpp#L111) | Callable definition: template&lt;class Action&gt; void denied(Action&& action) | calls action, check, fault, std::runtime_error; guard check(failure.fault()==resource::MemoryFault::limit,"unexpected window account failure kind");retur… · [reviewed contract](#b0016) |
| [B0017 · 117–137](../../../../../tests/unit/window_memory_test.cpp#L117) | Callable definition: void insertion_limits(bool indexed) | calls row, insertion, f, account; guard peak=f.account().statistics().peak_requested_bytes;check(peak&gt;initial,"window insertion did not exc… · [reviewed contract](#b0017) |
| [B0018 · 138–174](../../../../../tests/unit/window_memory_test.cpp#L138) | Callable definition: void expansion_limits_and_stop(bool indexed,WindowFifoPolicy fifo) | calls row, insertion, accept, f; guard check(peak&gt;before,"watermark native expansion did not exceed prior peak");; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 175–200](../../../../../tests/unit/window_memory_test.cpp#L175) | Callable definition: void persistent_failures(bool indexed,WindowFifoPolicy fifo) | calls insertion, row, f, accept; guard ++failures;check(f.window.canonical_state()==before && f.runtime.canonical_state()==physical && f.r…; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 201–201](../../../../../tests/unit/window_memory_test.cpp#L201) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0020) |
| [B0021 · 202–212](../../../../../tests/unit/window_memory_test.cpp#L202) | Callable definition: int main() | calls controls_and_retained_values, insertion_limits, allocation_and_prefixes, expansion_limits_and_stop; returns 1; 2 loop sites · [reviewed contract](#b0021) |

## B0001

[Lines 1–12](../../../../../tests/unit/window_memory_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:807f2babdb717fbe63e88938a764a50f3bf74bc6a525c86aa5e0202af61ab027
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare window_memory_test.cpp: include "crown/runtime/session.hpp", "indexed_runtime_fixture.hpp", "index_allocation.hpp", &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;; bind local aliases/name imports; declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/window_memory_test.cpp](../../../../../tests/unit/window_memory_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–15](../../../../../tests/unit/window_memory_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a window memory test assertion with its message. |
| inputs / outputs | Predicate and borrowed message in; no result. |
| invariants | True returns; false throws. |
| ownership | Message borrowed except when copied into exception. |
| failure | False throws std::runtime_error; allocation errors propagate. |
| cost | One predicate check. |
| Design | [tests/unit/window_memory_test.cpp § lines 13-15](../../../../../tests/unit/window_memory_test.cpp) |

## B0003

[Lines 16–22](../../../../../tests/unit/window_memory_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan plan(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build two physical tables and lower an empty-query plan for the chosen backend profile. |
| inputs / outputs | Selector in; plan over left/right tables with id, key, flag, day, amount out. |
| invariants | Both tables have identical five-column shape; amount is decimal(38,2); indexed true chooses test fixture selector options. |
| ownership | Plan owns lowered schema/query/tree metadata. |
| failure | Catalog/planner allocation errors propagate. |
| cost | Builds two tables/ten columns and performs one lowering; no runtime timing claim. |
| Design | [tests/unit/window_memory_test.cpp § lines 16-22](../../../../../tests/unit/window_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp § lines 4-20](../../../../../tests/support/indexed_runtime_fixture.hpp), [include/crown/planner/lower.hpp § lines 1-16](../../../../../include/crown/planner/lower.hpp) |

## B0004

[Lines 23–25](../../../../../tests/unit/window_memory_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(std::uint64_t cap=64*1024*1024) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the original Delta query-account cap for the fixture runtime. |
| inputs / outputs | Cap bytes in; DeltaOptions out. |
| invariants | Only physical.support.memory_limit_bytes is set. |
| ownership | Returns a local value passed to DeltaRuntime. |
| failure | No custom failure handling. |
| cost | Scalar option assignment. |
| Design | [tests/unit/window_memory_test.cpp § lines 23-25](../../../../../tests/unit/window_memory_test.cpp), [include/crown/runtime/delta.hpp § lines 1-80](../../../../../include/crown/runtime/delta.hpp) |

## B0005

[Lines 26–28](../../../../../tests/unit/window_memory_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowOptions windows(WindowFifoPolicy fifo=WindowFifoPolicy::global) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure the two managed tables, width and FIFO mode. |
| inputs / outputs | WindowFifoPolicy in; WindowOptions out. |
| invariants | Managed tables are TableId 0 and 1 in that order; width=10; FIFO copied unchanged. |
| ownership | Returned ordinary options are caller input; WindowController imports native options under its account. |
| failure | Vector allocation failure propagates. |
| cost | Two-element table list and scalar assignments. |
| Design | [tests/unit/window_memory_test.cpp § lines 26-28](../../../../../tests/unit/window_memory_test.cpp), [include/crown/runtime/window.hpp § lines 15-28](../../../../../include/crown/runtime/window.hpp) |

## B0006

[Lines 29–32](../../../../../tests/unit/window_memory_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t id,std::size_t bytes=8192) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a full window-row fixture with binary text and typed scalars. |
| inputs / outputs | ID and payload length in; owning Row out. |
| invariants | String contains NUL prefix followed by w bytes, plus bool/date/38-digit decimal. |
| ownership | Ordinary test Row owns its values before the WindowCommand import. |
| failure | String/Date/Decimal construction errors propagate. |
| cost | Five scalar fields, with text proportional to bytes. |
| Design | [tests/unit/window_memory_test.cpp § lines 29-32](../../../../../tests/unit/window_memory_test.cpp) |

## B0007

[Lines 33–35](../../../../../tests/unit/window_memory_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::WindowCommand insertion(std::uint64_t sequence,std::uint64_t label,TableId table,const Row& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Package one window insertion command from independent command sequence, label and table. |
| inputs / outputs | Sequence, label, table and borrowed row in; owning WindowCommand out. |
| invariants | Timestamp is fixed at zero; source position is absent. Command sequence and label remain distinct fields. |
| ownership | WindowCommand copies row values; caller retains input row. |
| failure | Copy/allocation failure propagates. |
| cost | Copies one row and constructs one variant command. |
| Design | [tests/unit/window_memory_test.cpp § lines 33-35](../../../../../tests/unit/window_memory_test.cpp), [include/crown/io/batch.hpp § lines 13-25](../../../../../include/crown/io/batch.hpp) |

## B0008

[Lines 36–40](../../../../../tests/unit/window_memory_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controller_only(const resource::MemoryAccount& account) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require all window/test-held native owners to be gone except the shared account controller. |
| inputs / outputs | Account in; no output. |
| invariants | Runs invariant check then requires one allocation/control_bytes exactly. |
| ownership | Account handle borrowed; no new grant. |
| failure | Mismatch throws test runtime_error; account error propagates. |
| cost | One account diagnostic scan. |
| Design | [tests/unit/window_memory_test.cpp § lines 36-40](../../../../../tests/unit/window_memory_test.cpp), [include/crown/resource/memory.hpp § lines 80-142](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp § lines 82-104](../../../../../src/resource/memory.cpp) |

## B0009

[Lines 41–43](../../../../../tests/unit/window_memory_test.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L43:sha256:3ba22f66249a2f9d363f789fcc55d6ddc9e37d30099387f8ee2d7122a8f6a386
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare window_memory_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/window_memory_test.cpp](../../../../../tests/unit/window_memory_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 44–45](../../../../../tests/unit/window_memory_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture(bool indexed,std::uint64_t cap=64*1024*1024,WindowFifoPolicy fifo=WindowFifoPolicy::global)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a DeltaRuntime and WindowController sharing the runtime plan account. |
| inputs / outputs | Selector, cap and FIFO in; Fixture with runtime/window out. |
| invariants | Controller receives runtime.plan().account() and source_catalog(); no separate query account is created. |
| ownership | Fixture owns both facades; WindowController and DeltaRuntime share the same account/control. |
| failure | Runtime/window construction validation and allocation errors propagate. |
| cost | One runtime-plan construction and one window controller construction. |
| Design | [tests/unit/window_memory_test.cpp § lines 41-45](../../../../../tests/unit/window_memory_test.cpp), [src/runtime/window.cpp § lines 163-173](../../../../../src/runtime/window.cpp), [include/crown/runtime/window.hpp § lines 171-181](../../../../../include/crown/runtime/window.hpp), [docs/batches_windows.md § Native window memory ownership, lines 93-115](../../../../batches_windows.md) |

## B0011

[Lines 46–46](../../../../../tests/unit/window_memory_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account() const {return runtime.plan().account();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a handle to the Fixture runtime’s existing account. |
| inputs / outputs | Fixture in; shared MemoryAccount handle out. |
| invariants | Returns the plan account; copying the handle does not mint another allowance. |
| ownership | Returned handle retains shared controller while fixture account remains live. |
| failure | No custom failure path; shared handle copy is noexcept. |
| cost | One handle copy. |
| Design | [tests/unit/window_memory_test.cpp § lines 46-46](../../../../../tests/unit/window_memory_test.cpp), [include/crown/resource/memory.hpp § lines 106-120](../../../../../include/crown/resource/memory.hpp) |

## B0012

[Lines 47–69](../../../../../tests/unit/window_memory_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accept(const io::WindowCommand& command,bool count_requests=false)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and publish one window command, applying any genuine physical update first. |
| inputs / outputs | Borrowed WindowCommand and optional request-count flag in; one metadata/window step, with Delta Epoch if update exists. |
| invariants | Window prepare and pending drain happen before publication. When requested, replacement-new calls during prepare/drain equal account successful-allocation delta and must be positive. Publication is under a zero-new barrier unless an upstream persistent fault scope is already active; account invariants checked afterward. |
| ownership | Fixture runtime/window own state under one account; Prepared owns tentative nodes/rows and borrows controller; PendingEpoch imports update under same account. |
| failure | Preparation/drain failures escape; RAII leaves unpublished state; failed test predicates throw. |
| cost | One prepare plus optional full delta drain; not a CPU timing measurement. Request hook counts replacement new only. |
| Design | [tests/unit/window_memory_test.cpp § lines 47-69](../../../../../tests/unit/window_memory_test.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [src/runtime/window.cpp § lines 298-413](../../../../../src/runtime/window.cpp), [src/runtime/delta.cpp § lines 1582-1589](../../../../../src/runtime/delta.cpp), [include/crown/runtime/window.hpp § lines 152-166](../../../../../include/crown/runtime/window.hpp), [docs/batches_windows.md § Steps, source progress and failure, lines 154-193](../../../../batches_windows.md), [docs/query_memory.md § Query memory contract, lines 19-33](../../../../query_memory.md) |

## B0013

[Lines 70–70](../../../../../tests/unit/window_memory_test.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L70:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in window_memory_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/window_memory_test.cpp](../../../../../tests/unit/window_memory_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 71–97](../../../../../tests/unit/window_memory_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void controls_and_retained_values(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check window option/update ownership after controller facade destruction and account release after final handles clear. |
| inputs / outputs | Selector in; asserts constructor request reconciliation, copied options, published update equality, window attribution, native retention and final controller-only state. |
| invariants | Window constructor replacement-new attempts equal successful allocation increase; copying AccountedWindowOptions and final release/Prepared destruction occur with replacement new forbidden. Prepared update retains row after publication and after controller scope ends; options retain managed-table order; window attribution is exercised. |
| ownership | Runtime owns account; retained options and published Prepared keep funded data alive independently of controller facade. Account handle remains for final checks. |
| failure | Any ownership/accounting/value mismatch fails; prepare/commit/allocation errors propagate. |
| cost | One runtime/window, one insert preparation+physical commit and fixed copy/move/release checks. |
| Design | [tests/unit/window_memory_test.cpp § lines 71-97](../../../../../tests/unit/window_memory_test.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [src/runtime/window.cpp § lines 130-161,171-173](../../../../../src/runtime/window.cpp), [include/crown/runtime/window.hpp § lines 29-67,152-166](../../../../../include/crown/runtime/window.hpp), [docs/batches_windows.md § Native window memory ownership, lines 93-115](../../../../batches_windows.md) |

## B0015

[Lines 98–110](../../../../../tests/unit/window_memory_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_and_prefixes(bool indexed,WindowFifoPolicy fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise duplicate-row reference counts and a multi-step watermark prefix for one FIFO policy. |
| inputs / outputs | Selector/FIFO in; checks three labels over two distinct rows, first unfinished watermark step, and final progress after completing it. |
| invariants | Two labels for the same row count as one physical row. Three insert commands advance physical runtime only on two unique inserts; watermark sequence 4 expires labels over three steps, leaves completed command/watermark at (3,0) after first step, then finishes at command 4/watermark 10 with no labels and runtime sequence 4. Each prepare is checked against replacement-new/account successful-allocation delta. |
| ownership | Fixture owns original runtime account/window; each Prepared/optional PendingEpoch is local and published before next command. |
| failure | Any count, prefix, progress, byte request or physical-sequence mismatch fails. |
| cost | Three insert commands plus three invocations of the same watermark command; compare/export canonical window state twice. No elapsed-time limit. |
| Design | [tests/unit/window_memory_test.cpp § lines 98-110](../../../../../tests/unit/window_memory_test.cpp), [src/runtime/window.cpp § lines 339-409,132-161](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Window policy and full-row identity, lines 117-152](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure, lines 154-175](../../../../batches_windows.md) |

## B0016

[Lines 111–116](../../../../../tests/unit/window_memory_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Action> void denied(Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to fail specifically at the native MemoryAccount limit. |
| inputs / outputs | Callable in; no output. |
| invariants | Returns only after catching MemoryFailure with fault()==limit; all other outcomes are rejected. |
| ownership | Callable forwarded for one invocation. |
| failure | Wrong MemoryFault rethrows as test runtime_error; no failure throws expected-denial runtime_error; other exceptions escape. |
| cost | One call and one exception classification. |
| Design | [tests/unit/window_memory_test.cpp § lines 111-116](../../../../../tests/unit/window_memory_test.cpp), [include/crown/resource/memory.hpp § lines 39-73](../../../../../include/crown/resource/memory.hpp) |

## B0017

[Lines 117–137](../../../../../tests/unit/window_memory_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void insertion_limits(bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate a one-row insertion peak and check exact/one-under original-account boundaries. |
| inputs / outputs | Selector in; checks exact requested peak, atomic refusal under peak-1, metadata-only same-command retry and final release. |
| invariants | Large row has 16000 w bytes. Exact peak cap accepts insertion and reaches measured peak. One-byte-under throws limit without changing window or physical canonical state and leaves runtime ready. A watermark-zero command at the same command sequence retries under unchanged cap with physical sequence still zero. |
| ownership | Each Fixture has one original plan account; failed Prepared import is released before retry; copied account handle survives fixture. |
| failure | Only limit denial is accepted; any state/progress/cap mutation fails. |
| cost | Three one-insertion fixtures and one small metadata retry; byte peaks are measured from current account requests, not payload length or RSS. |
| Design | [tests/unit/window_memory_test.cpp § lines 117-137](../../../../../tests/unit/window_memory_test.cpp), [src/runtime/window.cpp § lines 301-322,339-367](../../../../../src/runtime/window.cpp), [src/resource/memory.cpp § lines 82-104,192-231](../../../../../src/resource/memory.cpp), [docs/query_memory.md § Query memory contract, lines 19-33](../../../../query_memory.md), [docs/batches_windows.md § Native window memory ownership, lines 93-115](../../../../batches_windows.md) |

## B0018

[Lines 138–174](../../../../../tests/unit/window_memory_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expansion_limits_and_stop(bool indexed,WindowFifoPolicy fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure and bound the native active-watermark expansion for 512 labels under each FIFO policy. |
| inputs / outputs | Selector/FIFO in; calibrates request peak, exact-cap acceptance, one-under atomic rejection, same-command no-op retry and stop release. |
| invariants | Seeds labels 1..512 over one identical zero-payload row; watermark sequence 513 to 10 is the first active step. Stop under replacement-new prohibition releases actual expiration-label vector capacity while preserving active scalar progress; measured exact cap accepts and reaches peak; peak-1 failure preserves canonical window/runtime state and current bytes, then watermark 0 retries at the same command sequence with original limit. |
| ownership | Fixture owns account, runtime and controller; expiration capacity is native account-funded and is discarded by stop, retained scalar progress belongs to window state. |
| failure | Only MemoryFailure(limit) qualifies as byte denial; state/cap/current usage drift or failed retry fails. |
| cost | Exactly 512 seed commands per fixture plus one watermark step; two FIFO policies are supplied by caller. Account peaks/current bytes are not CPU measurements. |
| Design | [tests/unit/window_memory_test.cpp § lines 138-174](../../../../../tests/unit/window_memory_test.cpp), [src/runtime/window.cpp § lines 275-280,369-409](../../../../../src/runtime/window.cpp), [include/crown/runtime/window.hpp § lines 17-27,97-101,183-186](../../../../../include/crown/runtime/window.hpp), [docs/batches_windows.md § Steps, source progress and failure, lines 154-193](../../../../batches_windows.md), [docs/query_memory.md § Query memory contract, lines 19-33](../../../../query_memory.md) |

## B0019

[Lines 175–200](../../../../../tests/unit/window_memory_test.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_failures(bool indexed,WindowFifoPolicy fifo) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep replacement-new failure points through window insertion, duplicate insertion and both first/continuing watermark steps. |
| inputs / outputs | Selector/FIFO in; four prepared-state scenarios each require bad_alloc positions and one successful endpoint before 2048 positions. |
| invariants | Fault scope remains active through prepare, optional Delta drain and publication. On bad_alloc, window canonical state and physical canonical state equal pre-step state and runtime is ready; retry is the same command on the same fixture. Scenarios seed zero, one duplicate, two labels before watermark, or an already active watermark prefix. |
| ownership | Each trial builds a fresh Fixture and seed prefix before fault scope; the original account/controller remain the retry owner. Prepared and pending objects clean up before state comparison. |
| failure | Only bad_alloc is counted; any partial committed state, missing failure, or no success within 2048 fails. |
| cost | At most 2048 fresh setup+one attempted command positions for each of four cases, repeated for two FIFO policies. Hook is replacement new only; no duration guarantee. |
| Design | [tests/unit/window_memory_test.cpp § lines 175-200](../../../../../tests/unit/window_memory_test.cpp), [tests/support/index_allocation.hpp § lines 11-45](../../../../../tests/support/index_allocation.hpp), [src/runtime/window.cpp § lines 298-413,132-161](../../../../../src/runtime/window.cpp), [src/runtime/delta.cpp § lines 1582-1589](../../../../../src/runtime/delta.cpp), [docs/batches_windows.md § Steps, source progress and failure, lines 154-193](../../../../batches_windows.md) |

## B0020

[Lines 201–201](../../../../../tests/unit/window_memory_test.cpp#L201); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L201-L201:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in window_memory_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/window_memory_test.cpp](../../../../../tests/unit/window_memory_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 202–212](../../../../../tests/unit/window_memory_test.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run window retention, cap, prefix, expansion and persistent-failure checks across both backend selectors and FIFO modes. |
| inputs / outputs | No arguments; 0 on success, 1 after caught std::exception. |
| invariants | Both selectors run option/insert checks; each selector runs allocation-prefix, 512-label expansion and fault suites for global and per-relation FIFO. Source review only; no execution claim. |
| ownership | Fixture-local runtimes, controllers, commands and account handles are released before return. |
| failure | Catches std::exception, prints message and returns 1; success prints summary. |
| cost | Two selector profiles, two FIFO policies, four scenarios per fault sweep capped at 2048 each; no CPU-time threshold. |
| Design | [tests/unit/window_memory_test.cpp § lines 202-212](../../../../../tests/unit/window_memory_test.cpp), [tests/support/indexed_runtime_fixture.hpp § lines 4-20](../../../../../tests/support/indexed_runtime_fixture.hpp) |
