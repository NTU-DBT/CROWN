# `tests/unit/index_scalar_work_test.cpp` — block usage map

[Source](../../../../../tests/unit/index_scalar_work_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `1ef3d37ae57d5547ec8648ad29c7db17643b1ab3a06a4d7ad82f1818dec80a0e`. 97 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/index_scalar_work_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 16–18](../../../../../tests/unit/index_scalar_work_test.cpp#L16) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 19–25](../../../../../tests/unit/index_scalar_work_test.cpp#L19) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0003) |
| [B0004 · 26–26](../../../../../tests/unit/index_scalar_work_test.cpp#L26) | Explanatory comments or spacing. |  |
| [B0005 · 27–72](../../../../../tests/unit/index_scalar_work_test.cpp#L27) | Callable definition: void scalar_boundaries() | calls layout, Decimal::parse, std::string, verify; source comment (unverified): // Eight row-framing bytes, then tagged payloads: 9 +12 +2 +9 +50. · [reviewed contract](#b0005) |
| [B0006 · 73–73](../../../../../tests/unit/index_scalar_work_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0007 · 74–91](../../../../../tests/unit/index_scalar_work_test.cpp#L74) | Callable definition: void canonical_and_large_counters() | calls layout, tuple, Decimal::parse, equal; source comment (unverified): // These are work-count checks. Actual support payload/membership differential · [reviewed contract](#b0007) |
| [B0008 · 92–93](../../../../../tests/unit/index_scalar_work_test.cpp#L92) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 94–97](../../../../../tests/unit/index_scalar_work_test.cpp#L94) | Callable definition: int main() | calls scalar_boundaries, canonical_and_large_counters · [reviewed contract](#b0009) |

## B0001

[Lines 1–15](../../../../../tests/unit/index_scalar_work_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:4b7910193c0da1ea23cc455e856c942925d96c2a652c4a035da071d77a2c5e49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare index_scalar_work_test.cpp: include "index_scalar_work.hpp", &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–18](../../../../../tests/unit/index_scalar_work_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an IndexWork scalar test assertion. |
| inputs / outputs | Bool/message in; runtime_error on false. |
| invariants | False scalar/work condition fails. |
| ownership | Message borrowed unless reported. |
| failure | runtime_error carrier. |
| cost | One branch. |
| Design | tests/unit/index_scalar_work_test.cpp:16-18, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 19–25](../../../../../tests/unit/index_scalar_work_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one storage Error code. |
| inputs / outputs | Code/action in; returns on exact match. |
| invariants | Wrong/missing storage error fails. |
| ownership | Action forwarded; caught Error borrowed. |
| failure | Mismatch becomes runtime_error. |
| cost | One action/check. |
| Design | tests/unit/index_scalar_work_test.cpp:19-25, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 27–72](../../../../../tests/unit/index_scalar_work_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scalar_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact typed scalar framing and admission limits. |
| inputs / outputs | No input; hashes/copies/compares int64,string,bool,date,decimal and repeated/nullary projections. |
| invariants | Literal 90-scalar-byte hash-admission budget and other field/byte budgets are tested; layout-token mismatch is distinct. |
| ownership | Tuples/projections own values; IndexWorkAllowance is only logical work debit. |
| failure | One-under budgets require storage_work_limit; wrong token requires layout_mismatch. |
| cost | Exact literal work checks, not allocator-byte or CPU measurement. |
| Design | tests/unit/index_scalar_work_test.cpp:27-72, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 74–91](../../../../../tests/unit/index_scalar_work_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void canonical_and_large_counters() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check decimal aliases and large/max work counters. |
| inputs / outputs | No input; compares 1 and 1.000 and admits counters above 2^53 through uint64 max. |
| invariants | Decimal canonical equality and exact integer debit arithmetic hold without overflow. |
| ownership | Allowance is standalone caller-owned state. |
| failure | Over-limit extra step raises storage_work_limit. |
| cost | Fixed scalar values and counter updates. |
| Design | tests/unit/index_scalar_work_test.cpp:74-91, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 92–93](../../../../../tests/unit/index_scalar_work_test.cpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L93:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in index_scalar_work_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/index_scalar_work_test.cpp](../../../../../tests/unit/index_scalar_work_test.cpp), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 94–97](../../../../../tests/unit/index_scalar_work_test.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run scalar framing and large counter tests. |
| inputs / outputs | No input; invokes two boundary cases and emits result. |
| invariants | Finite literal assertions must pass. |
| ownership | main owns only call order. |
| failure | Unexpected Error/assertion fails process. |
| cost | Small source-defined cases; not executed here. |
| Design | tests/unit/index_scalar_work_test.cpp:94-97, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
