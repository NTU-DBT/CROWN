# `tests/unit/indexed_collision_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_collision_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f921d2de4dad01224da457a97b40d5201e866866abd4eea75e54661e8d05386f`. 71 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/indexed_collision_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../tests/unit/indexed_collision_test.cpp#L14) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 17–23](../../../../../tests/unit/indexed_collision_test.cpp#L17) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0003) |
| [B0004 · 24–26](../../../../../tests/unit/indexed_collision_test.cpp#L24) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{1'000'000, 1'000'000, 1'000'000, 1'000'000, 1'000'000}) · [reviewed contract](#b0004) |
| [B0005 · 27–27](../../../../../tests/unit/indexed_collision_test.cpp#L27) | Explanatory comments or spacing. |  |
| [B0006 · 28–64](../../../../../tests/unit/indexed_collision_test.cpp#L28) | Callable definition: void exact_collision_paths(detail::CollisionMode mode) | calls layout, target, projection, table; growth insert; 2 loop sites; source comment (unverified): // Six actual nodes share bucket0. A different full hash performs no equality · [reviewed contract](#b0006) |
| [B0007 · 65–66](../../../../../tests/unit/indexed_collision_test.cpp#L65) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 67–71](../../../../../tests/unit/indexed_collision_test.cpp#L67) | Callable definition: int main() | calls exact_collision_paths · [reviewed contract](#b0008) |

## B0001

[Lines 1–13](../../../../../tests/unit/indexed_collision_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:729699c1444471c6c27f7348748f2ed50cb131b437ba5aede533b8283f658738
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_collision_test.cpp: include "indexed_testing.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_collision_test.cpp](../../../../../tests/unit/indexed_collision_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–16](../../../../../tests/unit/indexed_collision_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an indexed collision assertion. |
| inputs / outputs | Bool/message in; runtime_error on false. |
| invariants | False expected chain/path fails. |
| ownership | Message borrowed except diagnostic. |
| failure | runtime_error carrier. |
| cost | One branch. |
| Design | tests/unit/indexed_collision_test.cpp:14-16, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 17–23](../../../../../tests/unit/indexed_collision_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one storage Error code. |
| inputs / outputs | Code/action in; returns after exact Error match. |
| invariants | Wrong or missing code fails. |
| ownership | Action forwarded; Error borrowed. |
| failure | Mismatch becomes runtime_error. |
| cost | One operation/check. |
| Design | tests/unit/indexed_collision_test.cpp:17-23, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 24–26](../../../../../tests/unit/indexed_collision_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a large five-domain IndexWork allowance. |
| inputs / outputs | No input; fixed finite grant out. |
| invariants | Logical work grant is separate from allocator bytes. |
| ownership | Caller owns grant. |
| failure | No custom catch. |
| cost | Fixed struct. |
| Design | tests/unit/indexed_collision_test.cpp:24-26, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 28–64](../../../../../tests/unit/indexed_collision_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exact_collision_paths(detail::CollisionMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise six real nodes under bucket-only and full-hash collision profiles. |
| inputs / outputs | CollisionMode in; inserts six int tuples, probes primary/secondary paths and erases all. |
| invariants | Bucket-only mismatched full hashes skip equality; full collision admits all six exact scalar bodies; failed lookup preserves stats/cursor. |
| ownership | IndexedTable owns rows/index; cursors borrow table state. |
| failure | One-under lookup requires storage_work_limit; test collision injector is guarded after use. |
| cost | Two profile runs, six-node chain and literal IndexWork budgets. |
| Design | tests/unit/indexed_collision_test.cpp:28-64, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 65–66](../../../../../tests/unit/indexed_collision_test.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L66:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_collision_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_collision_test.cpp](../../../../../tests/unit/indexed_collision_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 67–71](../../../../../tests/unit/indexed_collision_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both exact collision profiles. |
| inputs / outputs | No input; calls same-bucket and same-full-hash cases. |
| invariants | Both return same membership while exercising different equality paths. |
| ownership | main owns call sequence. |
| failure | Unexpected errors fail process. |
| cost | Two finite six-node cases; no test run claimed. |
| Design | tests/unit/indexed_collision_test.cpp:67-71, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
