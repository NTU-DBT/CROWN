# `tests/unit/indexed_cursor_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_cursor_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `889d4521602a0cfeba21a4b1c07c2b7044e910f3fe8107a9138a17cf978e348c`. 141 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/indexed_cursor_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../../tests/unit/indexed_cursor_test.cpp#L17) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 20–26](../../../../../tests/unit/indexed_cursor_test.cpp#L20) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0003) |
| [B0004 · 27–29](../../../../../tests/unit/indexed_cursor_test.cpp#L27) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000}) · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../tests/unit/indexed_cursor_test.cpp#L30) | Callable definition: IndexedLimits limits() | calls ; returns {256, 8, 1024, 2048, 4096, 16384, 512, 128} · [reviewed contract](#b0005) |
| [B0006 · 31–35](../../../../../tests/unit/indexed_cursor_test.cpp#L31) | Callable definition: template &lt;class Cursor&gt; auto no_allocation_step(Cursor& cursor, IndexWorkAllowance& work) | calls denied, next; returns cursor.next(work) · [reviewed contract](#b0006) |
| [B0007 · 36–38](../../../../../tests/unit/indexed_cursor_test.cpp#L36) | Callable definition: void allocation_free_result() | calls verify · [reviewed contract](#b0007) |
| [B0008 · 39–39](../../../../../tests/unit/indexed_cursor_test.cpp#L39) | Explanatory comments or spacing. |  |
| [B0009 · 40–98](../../../../../tests/unit/indexed_cursor_test.cpp#L40) | Callable definition: void retained_capacity_and_step_boundaries() | calls layout, nullary_layout, integer_layout, decimal_layout; growth insert; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 99–99](../../../../../tests/unit/indexed_cursor_test.cpp#L99) | Explanatory comments or spacing. |  |
| [B0011 · 100–135](../../../../../tests/unit/indexed_cursor_test.cpp#L100) | Callable definition: void noops_mutation_moves_and_owner_loss() | calls layout, key_layout, projection, tuple; returns std::pair{local.live(work), local.pin(saved, work)}; growth insert · [reviewed contract](#b0011) |
| [B0012 · 136–137](../../../../../tests/unit/indexed_cursor_test.cpp#L136) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 138–141](../../../../../tests/unit/indexed_cursor_test.cpp#L138) | Callable definition: int main() | calls retained_capacity_and_step_boundaries, noops_mutation_moves_and_owner_loss · [reviewed contract](#b0013) |

## B0001

[Lines 1–16](../../../../../tests/unit/indexed_cursor_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:bf7b22d2bca38992de94a8d9dcadd814ce2ee9d39edb1ffc984e6bc91473289b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_cursor_test.cpp: include "crown/storage/indexed.hpp", "index_allocation.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_cursor_test.cpp](../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–19](../../../../../tests/unit/indexed_cursor_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an indexed cursor assertion. |
| inputs / outputs | Bool/message in; runtime_error on false. |
| invariants | False cursor/work behavior fails. |
| ownership | Message borrowed except diagnostic. |
| failure | runtime_error carrier. |
| cost | One branch. |
| Design | tests/unit/indexed_cursor_test.cpp:17-19, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 20–26](../../../../../tests/unit/indexed_cursor_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one storage Error code. |
| inputs / outputs | Code/action in; returns after exact crown::Error match. |
| invariants | Wrong/missing code fails. |
| ownership | Action forwarded; Error borrowed. |
| failure | Mismatch becomes runtime_error. |
| cost | One action/check. |
| Design | tests/unit/indexed_cursor_test.cpp:20-26, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 27–29](../../../../../tests/unit/indexed_cursor_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return large indexed-work grant. |
| inputs / outputs | No input; five-domain allowance out. |
| invariants | Work debit is distinct from allocation/bytes. |
| ownership | Caller owns grant. |
| failure | No custom catch. |
| cost | Fixed value. |
| Design | tests/unit/indexed_cursor_test.cpp:27-29, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 30–30](../../../../../tests/unit/indexed_cursor_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedLimits limits() { return {256, 8, 1024, 2048, 4096, 16384, 512, 128}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return finite indexed table component limits. |
| inputs / outputs | No input; eight positional IndexedLimits values out; omitted trailing journal_entries keeps its default. |
| invariants | Includes small arena pin/slot and directory ceilings. |
| ownership | Caller copies into table. |
| failure | No custom catch. |
| cost | Fixed value. |
| Design | tests/unit/indexed_cursor_test.cpp:30-30, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 31–35](../../../../../tests/unit/indexed_cursor_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Cursor>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a cursor while denying all covered global-new calls. |
| inputs / outputs | Cursor/work refs in; one next result out under s04_alloc Scope(0). |
| invariants | S04 helper replaces scalar/array ordinary, aligned and nothrow new forms; direct libc and exception-ABI paths are outside this count. |
| ownership | Cursor borrows table; allowance remains caller-owned. |
| failure | An intercepted allocation throws bad_alloc and escapes. |
| cost | One cursor step plus one scoped global-new attempt counter; not a byte measurement. |
| Design | tests/unit/indexed_cursor_test.cpp:31-35, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 36–38](../../../../../tests/unit/indexed_cursor_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_free_result() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the prior allocation-probe scope observed zero covered new calls. |
| inputs / outputs | No input; checks calls==0 and !triggered. |
| invariants | Only forms covered by s04_alloc are observed. |
| ownership | Reads thread-local test counters. |
| failure | Failure becomes runtime_error through verify. |
| cost | Two scalar counter reads. |
| Design | tests/unit/indexed_cursor_test.cpp:36-38, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 40–98](../../../../../tests/unit/indexed_cursor_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retained_capacity_and_step_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cursor work steps, retained capacity and borrowed entry identity. |
| inputs / outputs | No input; retains large empty directories, creates row, walks live/bucket/key cursors with exact one-step grants. |
| invariants | End detection costs structural step; entries borrow real tuple; clear retains capacity; failed startup/work does not invalidate old cursor. |
| ownership | IndexedTable owns row/key; cursor borrows; copied keys/snapshot are owning outputs. |
| failure | Checks storage_work_limit and bad_alloc; failed cursor allocation preserves table/cursor. |
| cost | 128 setup rows with long text/decimal; cursor probes only one live row after clear. |
| Design | tests/unit/indexed_cursor_test.cpp:40-98, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 100–135](../../../../../tests/unit/indexed_cursor_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void noops_mutation_moves_and_owner_loss() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check no-op stability, mutation invalidation, moves and pin after owner loss. |
| inputs / outputs | No input; runs duplicate/absent/drop/pin, real insert/drop, table/cursor moves and a destroyed owner with Pin. |
| invariants | No-op/pin bookkeeping preserves cursors; real revision/index mutation invalidates; Pin retains value without membership. |
| ownership | Pin retains allocation; cursor does not own table; move transfers owner state. |
| failure | Invalid cursors require invalid_cursor; moved-from facade invalid_storage. |
| cost | Small fixture plus direct cursor checks. |
| Design | tests/unit/indexed_cursor_test.cpp:100-135, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0012

[Lines 136–137](../../../../../tests/unit/indexed_cursor_test.cpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L137:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_cursor_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_cursor_test.cpp](../../../../../tests/unit/indexed_cursor_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 138–141](../../../../../tests/unit/indexed_cursor_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run indexed step-boundary and lifecycle cursor cases. |
| inputs / outputs | No input; invokes both cases and reports. |
| invariants | All tested cursor contracts must hold. |
| ownership | main owns case sequence. |
| failure | Unexpected failure returns nonzero. |
| cost | Finite source tests; not executed here. |
| Design | tests/unit/indexed_cursor_test.cpp:138-141, docs/indexed_storage.md:35-89, docs/memory_accounts.md:378-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
