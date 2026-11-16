# `tests/unit/indexed_copy_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_copy_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `45c0b4813ecfc86bd67edb0f1a28b5dddafb2486bebd810d3f207e6caa3c2f10`. 151 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/indexed_copy_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares callable signatures. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/indexed_copy_test.cpp#L23) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 26–32](../../../../../tests/unit/indexed_copy_test.cpp#L26) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0003) |
| [B0004 · 33–35](../../../../../tests/unit/indexed_copy_test.cpp#L33) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000}) · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/unit/indexed_copy_test.cpp#L36) | Callable definition: IndexedLimits limits() | calls ; returns {16, 8, 64, 128, 256, 2048, 32, 8} · [reviewed contract](#b0005) |
| [B0006 · 37–37](../../../../../tests/unit/indexed_copy_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0007 · 38–145](../../../../../tests/unit/indexed_copy_test.cpp#L38) | Callable definition: void checked_sparse_copy_and_faults() | calls layout, key_layout, group, dummy; returns result; growth insert; 1 loop sites; source comment (unverified): // Current rows are B,C, but key9 stayed live through C after A disappeared. · [reviewed contract](#b0007) |
| [B0008 · 146–147](../../../../../tests/unit/indexed_copy_test.cpp#L146) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 148–151](../../../../../tests/unit/indexed_copy_test.cpp#L148) | Callable definition: int main() | calls checked_sparse_copy_and_faults · [reviewed contract](#b0009) |

## B0001

[Lines 1–22](../../../../../tests/unit/indexed_copy_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:8eab2da8f704a4957d76c676a1bf24c13f10d2a49d5fe44908d28eb1d5f0b038
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_copy_test.cpp: include "crown/storage/indexed.hpp", "index_allocation.hpp", "indexed_testing.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_copy_test.cpp](../../../../../tests/unit/indexed_copy_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–25](../../../../../tests/unit/indexed_copy_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an indexed-copy assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | Copy/source discrepancy fails. |
| ownership | Message borrowed except diagnostic. |
| failure | runtime_error carrier. |
| cost | One branch. |
| Design | tests/unit/indexed_copy_test.cpp:23-25, docs/tuple_arenas.md:120-139, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 26–32](../../../../../tests/unit/indexed_copy_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one storage Error code. |
| inputs / outputs | Code/action in; returns on exact match. |
| invariants | Wrong/missing Error cannot pass. |
| ownership | Action forwarded; Error borrowed. |
| failure | Mismatch becomes runtime_error. |
| cost | One operation/check. |
| Design | tests/unit/indexed_copy_test.cpp:26-32, docs/tuple_arenas.md:120-139, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 33–35](../../../../../tests/unit/indexed_copy_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a large standalone IndexWorkAllowance. |
| inputs / outputs | No input; fixed five-domain allowance out. |
| invariants | Work is not byte funding. |
| ownership | Caller owns allowance. |
| failure | No custom catch. |
| cost | Fixed struct. |
| Design | tests/unit/indexed_copy_test.cpp:33-35, docs/tuple_arenas.md:120-139, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 36–36](../../../../../tests/unit/indexed_copy_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedLimits limits() { return {16, 8, 64, 128, 256, 2048, 32, 8}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return finite IndexedLimits for sparse-copy fixtures. |
| inputs / outputs | No input; fixed rows/indexes/keys/directories/arena bounds out. |
| invariants | Limits bound the fixture components, not bytes. |
| ownership | Returned value copied into table. |
| failure | No custom catch. |
| cost | Fixed struct. |
| Design | tests/unit/indexed_copy_test.cpp:36-36, docs/tuple_arenas.md:120-139, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 38–145](../../../../../tests/unit/indexed_copy_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void checked_sparse_copy_and_faults() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check sparse owning copy, historical key order and every covered allocation failure. |
| inputs / outputs | No input; creates dropped index gaps, deletes rows with Pins, copies, faults every s04_alloc new position, retries and recopies. |
| invariants | Copy retains only live rows/indexes and old logical highwater but new owner/payloads; source cursor/pins/state survive failure. |
| ownership | Source and copies own separate arenas; Pin retains deleted source value. |
| failure | Injected bad_alloc must leave source intact; work denial uses storage_work_limit. |
| cost | Measures all covered scalar/aligned/nothrow global-new attempts via S04 helper; observer snapshots and repeated full state checks are test costs. |
| Design | tests/unit/indexed_copy_test.cpp:38-145, docs/tuple_arenas.md:120-139, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 146–147](../../../../../tests/unit/indexed_copy_test.cpp#L146); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L146-L147:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_copy_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_copy_test.cpp](../../../../../tests/unit/indexed_copy_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 148–151](../../../../../tests/unit/indexed_copy_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run sparse indexed copy and fault coverage. |
| inputs / outputs | No input; calls one copy suite and returns success text. |
| invariants | Suite checks both native and compile-selected collision profile. |
| ownership | main owns call order. |
| failure | Unexpected exception fails process. |
| cost | Finite four-row fixture with one fault per measured new attempt; no execution claim. |
| Design | tests/unit/indexed_copy_test.cpp:148-151, docs/tuple_arenas.md:120-139, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
