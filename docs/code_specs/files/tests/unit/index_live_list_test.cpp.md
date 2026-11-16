# `tests/unit/index_live_list_test.cpp` — block usage map

[Source](../../../../../tests/unit/index_live_list_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `b60dcf4da8c0fd45663762b9571ccb5dff9deab9c23d81426ba5923ada7d2dbc`. 146 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/index_live_list_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/index_live_list_test.cpp#L23) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 26–32](../../../../../tests/unit/index_live_list_test.cpp#L26) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0003) |
| [B0004 · 33–39](../../../../../tests/unit/index_live_list_test.cpp#L33) | Type/record definition: struct Node |  · [reviewed contract](#b0004) |
| [B0005 · 40–44](../../../../../tests/unit/index_live_list_test.cpp#L40) | declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_copy_constructible_v&lt;Node&gt; && !std::is_move_constructible_v&lt;Node&gt;); · [reviewed contract](#b0005) |
| [B0006 · 45–47](../../../../../tests/unit/index_live_list_test.cpp#L45) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{1'000'000, 0, 0, 0, 1'000'000}) · [reviewed contract](#b0006) |
| [B0007 · 48–60](../../../../../tests/unit/index_live_list_test.cpp#L48) | Callable definition: template &lt;class List&gt; std::vector&lt;std::uint64_t&gt; order(const List& list) | calls first, List::next, verify, size; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 61–61](../../../../../tests/unit/index_live_list_test.cpp#L61) | Explanatory comments or spacing. |  |
| [B0009 · 62–94](../../../../../tests/unit/index_live_list_test.cpp#L62) | Callable definition: void boundaries_and_membership() | calls empty, ample, rejects, prepare_insert; 3 loop sites; source comment (unverified): // Three actual nodes carry exact annotations here. This is not a claim of · [reviewed contract](#b0009) |
| [B0010 · 95–95](../../../../../tests/unit/index_live_list_test.cpp#L95) | Explanatory comments or spacing. |  |
| [B0011 · 96–117](../../../../../tests/unit/index_live_list_test.cpp#L96) | Callable definition: void inverse_neighbors() | calls bucket, a, b, c; 2 loop sites; source comment (unverified): // Both inverses were reserved before their corresponding forward removals, · [reviewed contract](#b0011) |
| [B0012 · 118–118](../../../../../tests/unit/index_live_list_test.cpp#L118) | Explanatory comments or spacing. |  |
| [B0013 · 119–140](../../../../../tests/unit/index_live_list_test.cpp#L119) | Callable definition: void generated_tape() | calls bucket, ample, contains, prepare_insert; growth emplace, make_unique, push_back; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 141–142](../../../../../tests/unit/index_live_list_test.cpp#L141) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 143–146](../../../../../tests/unit/index_live_list_test.cpp#L143) | Callable definition: int main() | calls boundaries_and_membership, inverse_neighbors, generated_tape · [reviewed contract](#b0015) |

## B0001

[Lines 1–22](../../../../../tests/unit/index_live_list_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:ec9197581c5f5cb190d41ed3c3ddee7cf759ae29a1b50ec0287c55c84c7dba66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare index_live_list_test.cpp: include "live_list.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;memory&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/index_live_list_test.cpp](../../../../../tests/unit/index_live_list_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–25](../../../../../tests/unit/index_live_list_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a live-list assertion. |
| inputs / outputs | Bool/message in; runtime_error on false. |
| invariants | False list state fails. |
| ownership | Message borrowed except failure format. |
| failure | runtime_error carrier. |
| cost | One branch. |
| Design | tests/unit/index_live_list_test.cpp:23-25, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 26–32](../../../../../tests/unit/index_live_list_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one storage Error code. |
| inputs / outputs | Expected code/action in; returns after exact Error match. |
| invariants | Missing/wrong code cannot pass. |
| ownership | Action forwarded; Error borrowed. |
| failure | Mismatch becomes runtime_error. |
| cost | One check. |
| Design | tests/unit/index_live_list_test.cpp:26-32, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 33–39](../../../../../tests/unit/index_live_list_test.cpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Node {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a nonmovable Node with independent row/bucket hooks and uint64 payload. |
| inputs / outputs | Key/annotation in; stores scalar payload plus two hooks. |
| invariants | A node can be in row and bucket lists independently. |
| ownership | Fixture owns nodes; lists borrow hooks. |
| failure | No custom failure carrier. |
| cost | Fixed node construction. |
| Design | tests/unit/index_live_list_test.cpp:33-39, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 40–44](../../../../../tests/unit/index_live_list_test.cpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L44:sha256:cdfd6f3662509ad4df1d577066ad01ca03f8dedf3f306509578ead93c81cb47c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare index_live_list_test.cpp: bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/index_live_list_test.cpp](../../../../../tests/unit/index_live_list_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 45–47](../../../../../tests/unit/index_live_list_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a small structural/link IndexWork grant. |
| inputs / outputs | No input; finite structural and link actions out. |
| invariants | No scalar/pointer work is supplied. |
| ownership | Returned allowance caller-owned. |
| failure | No custom catch. |
| cost | Fixed value. |
| Design | tests/unit/index_live_list_test.cpp:45-47, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 48–60](../../../../../tests/unit/index_live_list_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class List>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture live-list order and verify links/tail. |
| inputs / outputs | List in; key vector out. |
| invariants | Detects cycles/foreign nodes, checks cardinality and empty/nonempty tail. |
| ownership | List borrows Nodes; vector is test-owned. |
| failure | Mismatch throws runtime_error. |
| cost | Traverses all members. |
| Design | tests/unit/index_live_list_test.cpp:48-60, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 62–94](../../../../../tests/unit/index_live_list_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void boundaries_and_membership() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check empty/capacity, exact work and uint64 annotation boundaries. |
| inputs / outputs | No input; probes zero capacity and three nodes with payloads 0, &gt;2^53 and UINT64_MAX. |
| invariants | Payload exactness is tested on three real nodes; row/bucket hooks stay independent. |
| ownership | Lists borrow fixture nodes. |
| failure | Requires storage_capacity/work/contract errors. |
| cost | Three node links and fixed boundary checks. |
| Design | tests/unit/index_live_list_test.cpp:62-94, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 96–117](../../../../../tests/unit/index_live_list_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void inverse_neighbors() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore two removed nodes to their saved list neighbors. |
| inputs / outputs | No input; reserves work then removes/reinserts nodes in a full bucket. |
| invariants | Inverse action budget is reserved before forward removal; final order matches original. |
| ownership | Bucket owns no Nodes; saved neighbor pointers are valid fixture nodes. |
| failure | Insufficient grant must fail before list changes. |
| cost | Four node fixture, two removals and two inverse insertions. |
| Design | tests/unit/index_live_list_test.cpp:96-117, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0013

[Lines 119–140](../../../../../tests/unit/index_live_list_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generated_tape() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run 5000 seeded list membership/order updates. |
| inputs / outputs | No input; deterministic tape mutates list against map/insertion-order model. |
| invariants | Every step checks membership, exact order, size and final empty traversal. |
| ownership | Map owns nodes; list borrows links. |
| failure | Unexpected errors/assertions fail process. |
| cost | 5000 steps with complete traversal each step. |
| Design | tests/unit/index_live_list_test.cpp:119-140, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0014

[Lines 141–142](../../../../../tests/unit/index_live_list_test.cpp#L141); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L141-L142:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in index_live_list_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/index_live_list_test.cpp](../../../../../tests/unit/index_live_list_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 143–146](../../../../../tests/unit/index_live_list_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run live-list capacity, inverse-neighbor and model-tape checks. |
| inputs / outputs | No input; invokes three cases and prints summary. |
| invariants | All finite assertions must hold. |
| ownership | main owns sequence. |
| failure | Unexpected exception fails process. |
| cost | Finite source-defined 5000-step trace; not executed here. |
| Design | tests/unit/index_live_list_test.cpp:143-146, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
