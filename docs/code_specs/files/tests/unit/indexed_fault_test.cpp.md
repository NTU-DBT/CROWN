# `tests/unit/indexed_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `166232b5ab2c882f9d543b8a8d601c88f5058ec5872636e31736d6a90f84c899`. 206 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/unit/indexed_fault_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares callable signatures. |  · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../tests/unit/indexed_fault_test.cpp#L24) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 27–29](../../../../../tests/unit/indexed_fault_test.cpp#L27) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000}) · [reviewed contract](#b0003) |
| [B0004 · 30–30](../../../../../tests/unit/indexed_fault_test.cpp#L30) | Callable definition: IndexedLimits limits() | calls ; returns {32, 8, 256, 512, 1024, 4096, 64, 8} · [reviewed contract](#b0004) |
| [B0005 · 31–40](../../../../../tests/unit/indexed_fault_test.cpp#L31) | declares types or opens a type body. |  · [reviewed contract](#b0005) |
| [B0006 · 41–58](../../../../../tests/unit/indexed_fault_test.cpp#L41) | Callable definition: Definition() : new_keys(layout.tuple(Row{std::int64_t{999}, std::string(600, 'n'), true, Date::parse("9999-12-31"), Decimal::pars… | calls new_keys, tuple, std::string, Date::parse; growth emplace_back, push_back; 2 loop sites · [reviewed contract](#b0006) |
| [B0007 · 59–67](../../../../../tests/unit/indexed_fault_test.cpp#L59) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 68–70](../../../../../tests/unit/indexed_fault_test.cpp#L68) | Callable definition: explicit Fixture(const Definition& definition) : table(RelationId{1}, definition.layout, limits()), pin(build(definition)), pinne… | calls table, limits, pin, build · [reviewed contract](#b0008) |
| [B0009 · 71–71](../../../../../tests/unit/indexed_fault_test.cpp#L71) | Explanatory comments or spacing. |  |
| [B0010 · 72–84](../../../../../tests/unit/indexed_fault_test.cpp#L72) | Callable definition: TupleArena::Pin build(const Definition& definition) | calls defined, detail::IndexedTesting::collisions, ample, push_back; returns table.pin(handles.front(), work); growth insert, push_back; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 85–86](../../../../../tests/unit/indexed_fault_test.cpp#L85) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 87–93](../../../../../tests/unit/indexed_fault_test.cpp#L87) | Type/record definition: struct IndexImage |  · [reviewed contract](#b0012) |
| [B0013 · 94–101](../../../../../tests/unit/indexed_fault_test.cpp#L94) | Type/record definition: struct Image |  · [reviewed contract](#b0013) |
| [B0014 · 102–102](../../../../../tests/unit/indexed_fault_test.cpp#L102) | Explanatory comments or spacing. |  |
| [B0015 · 103–126](../../../../../tests/unit/indexed_fault_test.cpp#L103) | Callable definition: Image image(Fixture& fixture, const Definition& definition) | calls ample, statistics, revision, snapshot; returns result; growth push_back; 4 loop sites · [reviewed contract](#b0015) |
| [B0016 · 127–127](../../../../../tests/unit/indexed_fault_test.cpp#L127) | Explanatory comments or spacing. |  |
| [B0017 · 128–130](../../../../../tests/unit/indexed_fault_test.cpp#L128) | Type/record definition: enum class Operation |  · [reviewed contract](#b0017) |
| [B0018 · 131–156](../../../../../tests/unit/indexed_fault_test.cpp#L131) | Callable definition: std::uint64_t apply(Fixture& fixture, const Definition& definition, Operation operation, IndexWorkAllowance& work) | calls insert, verify, add_index, erase; returns result.handle.tuple.value; result.handle.tuple.value; growth insert · [reviewed contract](#b0018) |
| [B0019 · 157–157](../../../../../tests/unit/indexed_fault_test.cpp#L157) | Explanatory comments or spacing. |  |
| [B0020 · 158–189](../../../../../tests/unit/indexed_fault_test.cpp#L158) | Callable definition: void sweep(const Definition& definition, Operation operation, const char* label, bool must_allocate) | calls baseline, ample, apply, verify; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 190–191](../../../../../tests/unit/indexed_fault_test.cpp#L190) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 192–206](../../../../../tests/unit/indexed_fault_test.cpp#L192) | Callable definition: int main() | calls sweep · [reviewed contract](#b0022) |

## B0001

[Lines 1–23](../../../../../tests/unit/indexed_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:02bbb41593a64dc63fb118c99db3aa1024aa98ec681a323cc882783656aed17e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_fault_test.cpp: include "crown/storage/indexed.hpp", "index_allocation.hpp", "indexed_testing.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–26](../../../../../tests/unit/indexed_fault_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one indexed allocation-fault assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | A false state/fault expectation fails the case. |
| ownership | Message borrowed except failure formatting. |
| failure | runtime_error is the fixture assertion carrier. |
| cost | One branch; formatting only on failure. |
| Design | tests/unit/indexed_fault_test.cpp:24-26, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 27–29](../../../../../tests/unit/indexed_fault_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a generous five-domain IndexWorkAllowance. |
| inputs / outputs | No input; fixed large logical-work grant out. |
| invariants | Work units do not describe allocation bytes or intercept counters. |
| ownership | Caller owns the allowance. |
| failure | No custom catch. |
| cost | Fixed struct construction. |
| Design | tests/unit/indexed_fault_test.cpp:27-29, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 30–30](../../../../../tests/unit/indexed_fault_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedLimits limits() { return {32, 8, 256, 512, 1024, 4096, 64, 8}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return fixed limits for the six-row persistent-fault fixture. |
| inputs / outputs | No input; eight component ceilings out. |
| invariants | The finite fixture stays within explicit row/index/key/directory/arena bounds. |
| ownership | Returned limits are copied into each table. |
| failure | No custom failure carrier. |
| cost | Fixed value. |
| Design | tests/unit/indexed_fault_test.cpp:30-30, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 31–40](../../../../../tests/unit/indexed_fault_test.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L40:sha256:edbacf7b7bc4b4ebb5fae2e94ee4041281b155f54605c80cdff019c416425739
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 41–58](../../../../../tests/unit/indexed_fault_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Definition()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build six scalar projection programs and persistent row/key fixtures. |
| inputs / outputs | No input; Definition owns a five-field TupleLayout, seven projections, six initial rows and new/shared/nullary probe tuples. |
| invariants | Projection inputs cover empty, scalar, reordered, and repeated slots; long strings and decimal/date values are fixed fixtures. |
| ownership | Definition owns its vectors and tuples; rows share the layout token. |
| failure | Tuple, scalar parse and vector allocation failures propagate. |
| cost | Constructs seven projections and a small six-row set with large payloads. |
| Design | tests/unit/indexed_fault_test.cpp:41-58, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 59–67](../../../../../tests/unit/indexed_fault_test.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L67:sha256:915e21d40b415ebe72d0d8d171a2d923508e636f4cc8cd72ac95a5bed3193946
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 68–70](../../../../../tests/unit/indexed_fault_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Fixture(const Definition& definition)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a six-row indexed table and pin its first row. |
| inputs / outputs | Definition in; Fixture builds table, six indexes, six row handles and a Pin. |
| invariants | The first tuple allocation address is recorded; optional collision profile is set before fixture population. |
| ownership | Fixture owns table, handles and Pin; table owns row/index state. |
| failure | Table work/capacity and allocation errors propagate. |
| cost | Six index builds/inserts and one pin. |
| Design | tests/unit/indexed_fault_test.cpp:68-70, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0010

[Lines 72–84](../../../../../tests/unit/indexed_fault_test.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleArena::Pin build(const Definition& definition) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the fixture under the selected collision profile. |
| inputs / outputs | Definition in; installs same-bucket or same-full-hash test profile when compiled for one, adds six indexes, inserts six rows and returns a Pin. |
| invariants | No profile leaves native hashes; unknown profile is rejected at preprocessing; shared pin identifies first row. |
| ownership | Table retains rows and indexes; Fixture receives the owning Pin. |
| failure | Native storage errors propagate. |
| cost | Six indexes, six inserts and one pin under ample logical work. |
| Design | tests/unit/indexed_fault_test.cpp:72-84, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 85–86](../../../../../tests/unit/indexed_fault_test.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L86:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_fault_test.cpp: struct Fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 87–93](../../../../../tests/unit/indexed_fault_test.cpp#L87); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one index in the observer snapshot. |
| inputs / outputs | IndexId, program label, copied keys and copied member TupleIds in; equality-comparable IndexImage out. |
| invariants | The image records logical content for later full-state comparisons. |
| ownership | Vectors and tuples are observer-owned copies, not table state. |
| failure | Copy/allocation errors propagate. |
| cost | Copies one index's keys and member lists. |
| Design | tests/unit/indexed_fault_test.cpp:87-93, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0013

[Lines 94–101](../../../../../tests/unit/indexed_fault_test.cpp#L94); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Image {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a complete indexed fault-test observer image. |
| inputs / outputs | Statistics, revision, copied rows/indexes and pin-liveness in; equality-comparable Image out. |
| invariants | Equality includes public counters, row order, index/key/member order and pin liveness. |
| ownership | Observer owns copies; Fixture remains production-state owner. |
| failure | Copy/allocation errors propagate. |
| cost | Size follows all observed rows, keys and memberships. |
| Design | tests/unit/indexed_fault_test.cpp:94-101, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0015

[Lines 103–126](../../../../../tests/unit/indexed_fault_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Image image(Fixture& fixture, const Definition& definition) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy and validate all visible fixture state outside the fault window. |
| inputs / outputs | Fixture/Definition in; snapshots stats, revision, rows, indexes, keys and bucket TupleIds, checks owner/relation, invariants and pinned address/value. |
| invariants | A foreign projection or bucket handle, moved pin, or inconsistent table fails before comparison. |
| ownership | Observer vectors own copies; table, Rows and Pin remain fixture-owned. |
| failure | Mismatch throws runtime_error; native snapshot/work errors propagate. |
| cost | Full-state traversal and copies across every live index and bucket. |
| Design | tests/unit/indexed_fault_test.cpp:103-126, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0017

[Lines 128–130](../../../../../tests/unit/indexed_fault_test.cpp#L128); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Operation { insert_new_keys, insert_existing_keys, add_index, erase_handle,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate mutators, no-ops and owning output operations for the fault sweep. |
| inputs / outputs | No input; Operation distinguishes insert variants, index build, erase, clear/drop, duplicate/absent, snapshot, keys and bucket. |
| invariants | Each enum case selects one operation with explicit allocation class in main. |
| ownership | No ownership or state change itself. |
| failure | No failure carrier. |
| cost | Fixed enum. |
| Design | tests/unit/indexed_fault_test.cpp:128-130, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0018

[Lines 131–156](../../../../../tests/unit/indexed_fault_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t apply(Fixture& fixture, const Definition& definition, Operation operation, IndexWorkAllowance& work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply exactly one selected operation to a fixture. |
| inputs / outputs | Fixture, Definition, Operation and work allowance in; operation-specific uint64 result out. |
| invariants | Validates expected inserted/duplicate cases; unknown enum cannot silently succeed. |
| ownership | Uses fixture-owned table; snapshots/keys/buckets return temporary owning values. |
| failure | Storage errors, allocation failures and fixture runtime_error propagate. |
| cost | One selected table action; output size varies by operation. |
| Design | tests/unit/indexed_fault_test.cpp:131-156, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0020

[Lines 158–189](../../../../../tests/unit/indexed_fault_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep(const Definition& definition, Operation operation, const char* label, bool must_allocate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure and sweep every covered new-failure position, then retry. |
| inputs / outputs | Definition/operation/allocation class in; reconstructs baseline and subject fixtures, measures calls, injects one bad_alloc at each reached position, compares full images/cursors, retries and prints count. |
| invariants | Checks operation failure preserves all public state and old cursors; no-allocation classes retry with a zero-position denial; only successful result/image must match baseline. |
| ownership | S04 helper observes covered ordinary, aligned and nothrow scalar/array global-new overloads; direct libc and exception-ABI allocation paths are outside that seam; observer images are built outside injection windows. |
| failure | Injected bad_alloc must be caught at each reached position; assertion/runtime_error and storage/work errors remain visible. |
| cost | Measures the successful baseline, materializes its completed-state image, and compares full subject state/cursors at every measured failure position. |
| Design | tests/unit/indexed_fault_test.cpp:158-189, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0021

[Lines 190–191](../../../../../tests/unit/indexed_fault_test.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L191:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 192–206](../../../../../tests/unit/indexed_fault_test.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run insertion, index, deletion, no-op and output allocation fault sweeps. |
| inputs / outputs | No input; invokes twelve operation classes, including pinned erase and output-producing snapshots/keys/buckets. |
| invariants | Each class declares whether baseline must reach an intercepted allocation; failure/retry assertions are source checks only. |
| ownership | main owns sequence; each sweep owns fixtures. |
| failure | Unexpected exception fails process. |
| cost | Twelve finite sweeps, each faulting every measured covered position; not executed in this review. |
| Design | tests/unit/indexed_fault_test.cpp:192-206, docs/indexed_storage.md:35-89, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
