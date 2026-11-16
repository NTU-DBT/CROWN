# `tests/unit/indexed_table_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_table_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `93c57c7d36575961471acbbde79263f72fdfef1caf758c94f3a7b92903b7b56b`. 184 lines partitioned into 15 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/indexed_table_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Exercise the common types and shared-owner native interfaces. · [reviewed contract](#b0001) |
| [B0002 · 17–19](../../../../../tests/unit/indexed_table_test.cpp#L17) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 20–26](../../../../../tests/unit/indexed_table_test.cpp#L20) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0003) |
| [B0004 · 27–29](../../../../../tests/unit/indexed_table_test.cpp#L27) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance; returns IndexWorkAllowance(IndexWork{100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000}) · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../tests/unit/indexed_table_test.cpp#L30) | Callable definition: IndexedLimits limits() | calls ; returns {64, 8, 256, 512, 1024, 4096, 96, 32} · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../tests/unit/indexed_table_test.cpp#L31) | Explanatory comments or spacing. |  |
| [B0007 · 32–54](../../../../../tests/unit/indexed_table_test.cpp#L32) | Callable definition: void foreign_owners_and_tokens() | calls layout, indexed, limits, reference; growth insert; source comment (unverified): // Run first in this executable. Two independently initialized owner counters · [reviewed contract](#b0007) |
| [B0008 · 55–55](../../../../../tests/unit/indexed_table_test.cpp#L55) | Explanatory comments or spacing. |  |
| [B0009 · 56–108](../../../../../tests/unit/indexed_table_test.cpp#L56) | Callable definition: void literal_membership_and_lifecycle() | calls layout, integer_key, empty_key, integer; growth insert · [reviewed contract](#b0009) |
| [B0010 · 109–109](../../../../../tests/unit/indexed_table_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0011 · 110–145](../../../../../tests/unit/indexed_table_test.cpp#L110) | Callable definition: void literal_work_and_capacity_boundaries() | calls layout, tuple, table, work; growth insert; 2 loop sites; source comment (unverified): // One empty primary and one ID directory: two eight-slot arrays, four fixed · [reviewed contract](#b0011) |
| [B0012 · 146–146](../../../../../tests/unit/indexed_table_test.cpp#L146) | Explanatory comments or spacing. |  |
| [B0013 · 147–177](../../../../../tests/unit/indexed_table_test.cpp#L147) | Callable definition: void atomic_index_build_and_pin_retention() | calls layout, key_layout, projection, limits; growth insert · [reviewed contract](#b0013) |
| [B0014 · 178–179](../../../../../tests/unit/indexed_table_test.cpp#L178) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0014) |
| [B0015 · 180–184](../../../../../tests/unit/indexed_table_test.cpp#L180) | Callable definition: int main() | calls foreign_owners_and_tokens, literal_membership_and_lifecycle, literal_work_and_capacity_boundaries, atomic_index_build_and_pin_retention · [reviewed contract](#b0015) |

## B0001

[Lines 1–16](../../../../../tests/unit/indexed_table_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:c17ce49dc02bac2e2d33bbcaa881b6e9c2ecbd3b2d2b37531d139ad7ada1454a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_table_test.cpp: include "crown/storage/indexed.hpp", "crown/storage/reference.hpp", &lt;cstdint&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;vector&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_table_test.cpp](../../../../../tests/unit/indexed_table_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–19](../../../../../tests/unit/indexed_table_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one indexed table assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | Any false fixture expectation fails. |
| ownership | Message borrowed except failure formatting. |
| failure | runtime_error is harness assertion carrier. |
| cost | One branch. |
| Design | tests/unit/indexed_table_test.cpp:17-19, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 20–26](../../../../../tests/unit/indexed_table_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a specified storage Error from an operation. |
| inputs / outputs | Expected code/action in; returns after matching crown::Error. |
| invariants | Wrong or absent Error fails; unrelated exceptions propagate. |
| ownership | Action forwarded; caught Error borrowed. |
| failure | Mismatch or unexpected success becomes runtime_error. |
| cost | One operation and code comparison. |
| Design | tests/unit/indexed_table_test.cpp:20-26, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 27–29](../../../../../tests/unit/indexed_table_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an ample five-domain indexed work allowance. |
| inputs / outputs | No input; fixed high grant out. |
| invariants | Logical work debit does not represent bytes/account charges. |
| ownership | Caller owns allowance. |
| failure | Construction errors propagate. |
| cost | Fixed value. |
| Design | tests/unit/indexed_table_test.cpp:27-29, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 30–30](../../../../../tests/unit/indexed_table_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedLimits limits() { return {64, 8, 256, 512, 1024, 4096, 96, 32}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return table component limits for lifecycle fixtures. |
| inputs / outputs | No input; fixed eight-field IndexedLimits out. |
| invariants | Limits select finite test capacities, not runtime measurement. |
| ownership | Caller copies configuration into table. |
| failure | No custom failure carrier. |
| cost | Fixed struct. |
| Design | tests/unit/indexed_table_test.cpp:30-30, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 32–54](../../../../../tests/unit/indexed_table_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void foreign_owners_and_tokens() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check foreign backend owners, handles and equal-looking layout tokens. |
| inputs / outputs | No input; builds indexed/reference tables with matching relation/layout IDs, cross-uses handles and a reconstructed descriptor. |
| invariants | Backend owners remain distinct; logical IDs may match; wrong owner/relation raises foreign_handle; reconstructed equal layout token raises layout_mismatch without changing stats. |
| ownership | Tables own separate rows; copied/reconstructed descriptors have independent identity. |
| failure | rejects checks exact Error codes; mismatches throw runtime_error. |
| cost | Two inserts, fixed foreign-handle/token probes and invariant scans. |
| Design | tests/unit/indexed_table_test.cpp:32-54, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 56–108](../../../../../tests/unit/indexed_table_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void literal_membership_and_lifecycle() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact membership, index identity/order, pin retention, clear and moves. |
| inputs / outputs | No input; registers same and independent projections, inserts zero/binary/&gt;2^53 integer rows, duplicate and nullary bucket probes, snapshots, erases/drops/rebuilds/clears/moves. |
| invariants | Same token is idempotent while field-equal separate program gets a new ID; &gt;2^53 integers stay distinct; insertion order/nullary bucket exact; Pins retain allocation but not membership; committed clear does not reuse logical IDs. |
| ownership | Table owns rows/indexes; Pin retains erased tuple across clear/move; cursor-free fixture state. |
| failure | Exact invalid_storage on moved-from facade; Error and assertion helpers check expected carriers. |
| cost | Three rows, three indexes and fixed lifecycle/state checks. |
| Design | tests/unit/indexed_table_test.cpp:56-108, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 110–145](../../../../../tests/unit/indexed_table_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void literal_work_and_capacity_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check literal work vectors and component capacity boundaries atomically. |
| inputs / outputs | No input; exact insert grant {4,4,25,16,18}; lowers each of five work domains and four component caps separately. |
| invariants | Exact grant succeeds and exhausts; one-under failure leaves stats/revision unchanged; rejected row/node/directory/arena capacity publishes no state. |
| ownership | Table owns fixture; allowance owned per case. |
| failure | Requires storage_work_limit or storage_capacity as appropriate. |
| cost | One exact insertion plus nine one-under fixtures and invariant checks. |
| Design | tests/unit/indexed_table_test.cpp:110-145, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0013

[Lines 147–177](../../../../../tests/unit/indexed_table_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void atomic_index_build_and_pin_retention() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check atomic index-build capacity failure and pinned slot retention. |
| inputs / outputs | No input; forces key-cap index build failure then retries; fills arena/pin cap, clears while externally retained, rejects insert, releases pin and reuses slot. |
| invariants | Failed build leaves rows/counters/ID allocator intact; pin retention remains charged after clear; reuse has fresh generation and higher logical ID. |
| ownership | Table/arena own values; Pin externally retains tuple; counters checked before/after retry. |
| failure | Expected storage_capacity at build, second pin and retained-slot insert; assertion checks exact identity. |
| cost | Two compact fixtures, one failed index build and bounded slot lifecycle. |
| Design | tests/unit/indexed_table_test.cpp:147-177, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0014

[Lines 178–179](../../../../../tests/unit/indexed_table_test.cpp#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L178-L179:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_table_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_table_test.cpp](../../../../../tests/unit/indexed_table_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 180–184](../../../../../tests/unit/indexed_table_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run owner/token, membership/lifecycle, work/capacity and index-build/pin cases. |
| inputs / outputs | No input; invokes four suites and prints source-defined summary. |
| invariants | All finite explicit assertions must hold. |
| ownership | main owns case order. |
| failure | Unexpected exception fails process. |
| cost | Fixed table scenarios; not executed in this review. |
| Design | tests/unit/indexed_table_test.cpp:180-184, docs/storage.md:11-116, docs/tuple_arenas.md:39-117, docs/indexed_storage.md:35-89, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
