# `tests/unit/indexed_journal_fault_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_journal_fault_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a4384b610d29d995151acff6a30961e2cb9d6aa57d8b087164d7e709f6e521f7`. 214 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../tests/unit/indexed_journal_fault_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 20–22](../../../../../tests/unit/indexed_journal_fault_test.cpp#L20) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../tests/unit/indexed_journal_fault_test.cpp#L23) | Callable definition: IndexWork budget() | calls ; returns {100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000} · [reviewed contract](#b0003) |
| [B0004 · 24–24](../../../../../tests/unit/indexed_journal_fault_test.cpp#L24) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance, budget; returns IndexWorkAllowance(budget()) · [reviewed contract](#b0004) |
| [B0005 · 25–25](../../../../../tests/unit/indexed_journal_fault_test.cpp#L25) | Callable definition: std::shared_ptr&lt;IndexWorkAllowance&gt; grant() | calls budget; returns std::make_shared&lt;IndexWorkAllowance&gt;(budget()); growth make_shared · [reviewed contract](#b0005) |
| [B0006 · 26–42](../../../../../tests/unit/indexed_journal_fault_test.cpp#L26) | Type/record definition: struct Definition | returns layout.tuple({id, key, std::string(512, static_cast&lt;char&gt;(@ + id)),; growth emplace_back, push_back; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 43–63](../../../../../tests/unit/indexed_journal_fault_test.cpp#L43) | Type/record definition: struct Fixture | returns table.pin(handles.front(), work); growth insert, push_back; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 64–68](../../../../../tests/unit/indexed_journal_fault_test.cpp#L64) | Type/record definition: struct KeyImage |  · [reviewed contract](#b0008) |
| [B0009 · 69–76](../../../../../tests/unit/indexed_journal_fault_test.cpp#L69) | Type/record definition: struct Image |  · [reviewed contract](#b0009) |
| [B0010 · 77–78](../../../../../tests/unit/indexed_journal_fault_test.cpp#L77) | Explanatory comments or spacing. | source comment (unverified): // A separate observer owns these copies. They neither replenish the journal's · [reviewed contract](#b0010) |
| [B0011 · 79–91](../../../../../tests/unit/indexed_journal_fault_test.cpp#L79) | Callable definition: Image image(Fixture& f) | calls ample, statistics, revision, snapshot; returns result; growth push_back; 3 loop sites; source comment (unverified): // A separate observer owns these copies. They neither replenish the journal's · [reviewed contract](#b0011) |
| [B0012 · 92–95](../../../../../tests/unit/indexed_journal_fault_test.cpp#L92) | declares types or opens a type body. |  · [reviewed contract](#b0012) |
| [B0013 · 96–101](../../../../../tests/unit/indexed_journal_fault_test.cpp#L96) | Callable definition: Streams(Fixture& f, IndexedTable::Journal& journal, const Image& before) : live(journal.live()) | calls live, size, push_back, index_keys; growth push_back; 2 loop sites · [reviewed contract](#b0013) |
| [B0014 · 102–103](../../../../../tests/unit/indexed_journal_fault_test.cpp#L102) | Explanatory comments or spacing. | source comment (unverified): // All metadata/copies were prepared before failure. Comparison follows only · [reviewed contract](#b0014) |
| [B0015 · 104–127](../../../../../tests/unit/indexed_journal_fault_test.cpp#L104) | Callable definition: bool same(Fixture& f, const Image& before, IndexWorkAllowance& work) | calls statistics, revision, is_live, get; returns false; false; 4 loop sites; source comment (unverified): // All metadata/copies were prepared before failure. Comparison follows only · [reviewed contract](#b0015) |
| [B0016 · 128–128](../../../../../tests/unit/indexed_journal_fault_test.cpp#L128) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 129–129](../../../../../tests/unit/indexed_journal_fault_test.cpp#L129) | Type/record definition: enum class Operation | growth insert · [reviewed contract](#b0017) |
| [B0018 · 130–141](../../../../../tests/unit/indexed_journal_fault_test.cpp#L130) | Callable definition: std::uint64_t apply(Fixture& f, const Definition& d, IndexedTable::Journal& journal, Operation operation) | calls insert, erase, owner, live; returns journal.insert(d.addition).handle.tuple.value; journal.erase(f.handles\[1\]) ? 1 : 0; growth insert · [reviewed contract](#b0018) |
| [B0019 · 142–187](../../../../../tests/unit/indexed_journal_fault_test.cpp#L142) | Callable definition: void sweep(const Definition& d, Operation operation, const char* label, bool must_allocate) | calls baseline, grant, journal, verify; 1 loop sites · [reviewed contract](#b0019) |
| [B0020 · 188–203](../../../../../tests/unit/indexed_journal_fault_test.cpp#L188) | Callable definition: void opening(const Definition& d) | calls baseline, grant, emplace, journal; growth emplace; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 204–204](../../../../../tests/unit/indexed_journal_fault_test.cpp#L204) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 205–214](../../../../../tests/unit/indexed_journal_fault_test.cpp#L205) | Callable definition: int main() | calls opening, sweep; growth insert · [reviewed contract](#b0022) |

## B0001

[Lines 1–19](../../../../../tests/unit/indexed_journal_fault_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:31de289e4e2814550fde990e75b2c87e9954b484f6801e884e1d9e8d5b6b6b35
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_journal_fault_test.cpp: include "crown/storage/indexed.hpp", "index_allocation.hpp", "indexed_testing.hpp", &lt;cstdint&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 20–22](../../../../../tests/unit/indexed_journal_fault_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one journal fault assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | A false state/fault result fails. |
| ownership | Message borrowed except failure formatting. |
| failure | runtime_error is harness carrier. |
| cost | One branch. |
| Design | tests/unit/indexed_journal_fault_test.cpp:20-22, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 23–23](../../../../../tests/unit/indexed_journal_fault_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWork budget() { return {100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the fixed five-domain journal budget. |
| inputs / outputs | No input; five large logical-work limits out. |
| invariants | IndexWork is independent of bytes/accounting. |
| ownership | Value owned by caller. |
| failure | No custom catch. |
| cost | Fixed struct. |
| Design | tests/unit/indexed_journal_fault_test.cpp:23-23, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 24–24](../../../../../tests/unit/indexed_journal_fault_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() { return IndexWorkAllowance(budget()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap the fixed journal budget in an allowance. |
| inputs / outputs | No input; IndexWorkAllowance out. |
| invariants | Remaining grant is explicit and later shared with the journal. |
| ownership | Caller owns allowance. |
| failure | Constructor errors propagate. |
| cost | Fixed allowance construction. |
| Design | tests/unit/indexed_journal_fault_test.cpp:24-24, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 25–25](../../../../../tests/unit/indexed_journal_fault_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<IndexWorkAllowance> grant() { return std::make_shared<IndexWorkAllowance>(budget()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share one journal work allowance across fixture operations. |
| inputs / outputs | No input; shared_ptr to a fresh allowance out. |
| invariants | Ownership of the grant may be retained by journal cursors. |
| ownership | Returned shared_ptr owns grant control and state. |
| failure | Allocation failure propagates. |
| cost | One shared ownership construction. |
| Design | tests/unit/indexed_journal_fault_test.cpp:25-25, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 26–42](../../../../../tests/unit/indexed_journal_fault_test.cpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Definition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build four-row, three-index journal-fault inputs. |
| inputs / outputs | No input; Definition owns layout/projections/four rows and addition tuple. |
| invariants | Two rows share index key 9; text is long and decimal literal fixed for fault paths. |
| ownership | Definition owns tuple values/programs. |
| failure | Tuple and projection setup failures propagate. |
| cost | Three projections and four rows. |
| Design | tests/unit/indexed_journal_fault_test.cpp:26-42, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 43–63](../../../../../tests/unit/indexed_journal_fault_test.cpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an indexed fixture and pin its first row. |
| inputs / outputs | Definition and optional limits in; Fixture owns table, index IDs, handles, Pin and saved tuple address. |
| invariants | Collision profile is configured before adding indexes/rows; first tuple address is recorded. |
| ownership | Fixture owns table, rows and pin; index handles are metadata. |
| failure | Native storage failures propagate. |
| cost | Three index builds, four inserts and one pin. |
| Design | tests/unit/indexed_journal_fault_test.cpp:43-63, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 64–68](../../../../../tests/unit/indexed_journal_fault_test.cpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one copied key and its logical member IDs. |
| inputs / outputs | Tuple key and member TupleIds in; equality-comparable KeyImage out. |
| invariants | Only IDs are copied from handles for semantic comparisons. |
| ownership | Observer owns key/member vector copies. |
| failure | Copy allocation errors propagate. |
| cost | Copies one bucket's contents. |
| Design | tests/unit/indexed_journal_fault_test.cpp:64-68, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 69–76](../../../../../tests/unit/indexed_journal_fault_test.cpp#L69); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Image {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store rows and all index contents for a journal observer. |
| inputs / outputs | Copied rows and per-index KeyImages in; equality-comparable Image out. |
| invariants | Captures row order and each key/member sequence, not private journal internals. |
| ownership | Observer owns copies; Fixture owns table state. |
| failure | Copy errors propagate. |
| cost | Space proportional to rows, keys and memberships. |
| Design | tests/unit/indexed_journal_fault_test.cpp:69-76, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0010

[Lines 77–78](../../../../../tests/unit/indexed_journal_fault_test.cpp#L77); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L77-L78:sha256:88723fa8a9bb0c7ced331a655a2b46f09cb567b3505eb4b07d102fd72a33e93a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A separate observer owns these copies. They neither replenish the journal's grant nor run inside its failure window. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 79–91](../../../../../tests/unit/indexed_journal_fault_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Image image(Fixture& f) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an observer snapshot outside journal fault/denial windows. |
| inputs / outputs | Fixture in; copies snapshot rows and every index key/bucket, then checks invariants. |
| invariants | Observer allocations/work never replenish the journal grant or run inside the operation fault scope. |
| ownership | Copied image is observer-owned; table remains fixture-owned. |
| failure | Native snapshot errors and copy allocation failures propagate. |
| cost | Full row/key/bucket traversal and allocations. |
| Design | tests/unit/indexed_journal_fault_test.cpp:79-91, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0012

[Lines 92–95](../../../../../tests/unit/indexed_journal_fault_test.cpp#L92); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L92-L95:sha256:26a33f534f5e8eade912837444de6ece673cc73617ecc9b071805df701404240
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_journal_fault_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 96–101](../../../../../tests/unit/indexed_journal_fault_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Streams(Fixture& f, IndexedTable::Journal& journal, const Image& before) : live(journal.live()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare live, key and bucket cursors before fault injection. |
| inputs / outputs | Fixture, active Journal and before-image in; Streams owns journal cursor values for live, each index key and each known bucket. |
| invariants | Metadata/copies are prepared before failure; cursor factories consume the journal grant but test vectors are independent. |
| ownership | Journal cursors retain the journal's shared work grant and borrow table/journal state. |
| failure | Cursor construction errors propagate. |
| cost | One cursor for live, per-index key cursor and one bucket cursor per observed key. |
| Design | tests/unit/indexed_journal_fault_test.cpp:96-101, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0014

[Lines 102–103](../../../../../tests/unit/indexed_journal_fault_test.cpp#L102); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L102-L103:sha256:99726ebe82babfac2804eeeb1e751650a6605f806fead39aff45157a0f3ece3d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: All metadata/copies were prepared before failure. Comparison follows only already-owned cursors and exact borrowed values, including every end check. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 104–127](../../../../../tests/unit/indexed_journal_fault_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same(Fixture& f, const Image& before, IndexWorkAllowance& work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare precreated journal cursors and table counters after injected failure. |
| inputs / outputs | Fixture, before-image and allowance in; advances live/key/bucket cursors through every expected item/end and compares stats/revision/pin/address/handle ownership. |
| invariants | No new observer containers are constructed in this comparison; every stream and end condition must match the earlier image. |
| ownership | Streams owns cursor objects; rows/keys in before-image are copied; cursor entries borrow table tuples. |
| failure | Returns false on discrepancy; work denial or other exception is caught by caller as failed comparison. |
| cost | Traverses all copied rows, keys and memberships using existing cursors. |
| Design | tests/unit/indexed_journal_fault_test.cpp:104-127, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0016

[Lines 128–128](../../../../../tests/unit/indexed_journal_fault_test.cpp#L128); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L128:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_journal_fault_test.cpp: struct Streams. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 129–129](../../../../../tests/unit/indexed_journal_fault_test.cpp#L129); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Operation { insert, erase, duplicate, absent, live, bucket, keys };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select journal mutator/no-op/cursor-construction operation. |
| inputs / outputs | No input; enum distinguishes insert, erase, duplicate, absent erase and live/bucket/key cursor setup. |
| invariants | No-op and cursor operations have separately measured allocation expectations. |
| ownership | Enum carries no owned state. |
| failure | No custom failure path. |
| cost | Fixed enum. |
| Design | tests/unit/indexed_journal_fault_test.cpp:129-129, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0018

[Lines 130–141](../../../../../tests/unit/indexed_journal_fault_test.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t apply(Fixture& f, const Definition& d, IndexedTable::Journal& journal, Operation operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one operation through an active journal. |
| inputs / outputs | Fixture, Definition, Journal and Operation in; uint64 status/ID out. |
| invariants | Expected operation results are returned for baseline/retry comparison. |
| ownership | Journal and table are caller-owned; temporary cursors do not escape. |
| failure | Storage/contract/work and allocation exceptions propagate. |
| cost | One operation or cursor construction. |
| Design | tests/unit/indexed_journal_fault_test.cpp:130-141, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0019

[Lines 142–187](../../../../../tests/unit/indexed_journal_fault_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep(const Definition& d, Operation operation, const char* label, bool must_allocate) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep journal operation allocation positions and test rollback/retry. |
| inputs / outputs | Definition/operation/allocation class in; starts with journal prefix erase, measures successful covered-new calls, injects each position, compares prepared cursor streams, exhausts remaining work, rolls back, checks committed state, retries and commits. |
| invariants | During the injected failure, prepared Streams compare the saved prefix revision exactly as well as its rows/keys/members. After explicit rollback, assertions check selected committed/retained/tentative/node fields. Final retry Image equality first normalizes actual.revision to the successful baseline, so it does not require equal raw revision across aborted trials. Observation/rollback make no additional covered-new attempt; commit is separately checked at zero covered-new calls. |
| ownership | S04 helper covers ordinary, aligned and nothrow scalar/array global-new replacement overloads, not direct libc or exception-ABI allocation; observer snapshots and cursors are prepared outside operation fault windows. |
| failure | Expected bad_alloc is caught per measured position; journal rollback/commit errors, state mismatches and unexpected carriers fail assertions. |
| cost | Per allocation position performs a full precreated-stream comparison and after-rollback image; commit/rollback cleanup may traverse history. |
| Design | tests/unit/indexed_journal_fault_test.cpp:142-187, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0020

[Lines 188–203](../../../../../tests/unit/indexed_journal_fault_test.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void opening(const Definition& d) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep journal-open allocation failures before publication. |
| inputs / outputs | Definition in; measures journal construction, then faults each reached position and verifies no candidate journal/exclusivity or state change is published. |
| invariants | Only a fully constructed optional Journal is accepted; image calls run outside fault scopes. |
| ownership | Candidate optional owns a journal only on success; subject owns table. |
| failure | Each measured position must throw bad_alloc and leave no candidate. |
| cost | One state image per failure position and one opening sequence baseline. |
| Design | tests/unit/indexed_journal_fault_test.cpp:188-203, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0021

[Lines 204–204](../../../../../tests/unit/indexed_journal_fault_test.cpp#L204); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L204-L204:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_journal_fault_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_journal_fault_test.cpp](../../../../../tests/unit/indexed_journal_fault_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 205–214](../../../../../tests/unit/indexed_journal_fault_test.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run journal opening, partial mutation, no-op and cursor fault suites. |
| inputs / outputs | No input; sweeps insertion/erase/duplicate/absent and three cursor constructors after an erase prefix. |
| invariants | All assertions cover failure atomicity, rollback, cursors and retry against a successful baseline. |
| ownership | main owns sequencing. |
| failure | Unexpected exception fails process. |
| cost | Seven finite operation sweeps plus opening; no native test execution claimed. |
| Design | tests/unit/indexed_journal_fault_test.cpp:205-214, docs/storage_journal.md:87-182, docs/memory_accounts.md:342-409, tests/support/index_allocation.hpp:1-70, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
