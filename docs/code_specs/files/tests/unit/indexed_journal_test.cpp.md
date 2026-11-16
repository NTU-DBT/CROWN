# `tests/unit/indexed_journal_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_journal_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `89954d1f8633c376c4688bd022f6169fdbe5dc6cef09908d31574158e7cd782a`. 236 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/indexed_journal_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 21–23](../../../../../tests/unit/indexed_journal_test.cpp#L21) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 24–28](../../../../../tests/unit/indexed_journal_test.cpp#L24) | Callable definition: template&lt;class Function&gt; void error(std::string_view code, Function&& operation) | calls operation, verify, code, std::runtime_error · [reviewed contract](#b0003) |
| [B0004 · 29–29](../../../../../tests/unit/indexed_journal_test.cpp#L29) | Callable definition: IndexWork budget() | calls ; returns {1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000} · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../tests/unit/indexed_journal_test.cpp#L30) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance, budget; returns IndexWorkAllowance(budget()) · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../tests/unit/indexed_journal_test.cpp#L31) | Callable definition: std::shared_ptr&lt;IndexWorkAllowance&gt; grant() | calls budget; returns std::make_shared&lt;IndexWorkAllowance&gt;(budget()); growth make_shared · [reviewed contract](#b0006) |
| [B0007 · 32–32](../../../../../tests/unit/indexed_journal_test.cpp#L32) | Callable definition: IndexedLimits limits() | calls ; returns {64, 8, 1024, 2048, 4096, 16384, 256, 256, 128} · [reviewed contract](#b0007) |
| [B0008 · 33–47](../../../../../tests/unit/indexed_journal_test.cpp#L33) | Type/record definition: struct Definition | returns layout.tuple({id, key, std::string(512, static_cast&lt;char&gt;(@ + id % 20)),; programs\[1\].target().tupl…; growth emplace_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 48–56](../../../../../tests/unit/indexed_journal_test.cpp#L48) | Callable definition: void profile(IndexedTable& table) | calls defined, detail::IndexedTesting::collisions · [reviewed contract](#b0009) |
| [B0010 · 57–72](../../../../../tests/unit/indexed_journal_test.cpp#L57) | Type/record definition: struct Fixture | returns table.pin(handles.front(), work); growth insert, push_back; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 73–77](../../../../../tests/unit/indexed_journal_test.cpp#L73) | Type/record definition: struct KeyImage |  · [reviewed contract](#b0011) |
| [B0012 · 78–82](../../../../../tests/unit/indexed_journal_test.cpp#L78) | Type/record definition: struct Image |  · [reviewed contract](#b0012) |
| [B0013 · 83–84](../../../../../tests/unit/indexed_journal_test.cpp#L83) | Explanatory comments or spacing. | source comment (unverified): // Observer snapshots are separate from the operation being tested. Their · [reviewed contract](#b0013) |
| [B0014 · 85–97](../../../../../tests/unit/indexed_journal_test.cpp#L85) | Callable definition: Image image(Fixture& f) | calls ample, snapshot, keys, bucket; returns result; growth push_back; 3 loop sites; source comment (unverified): // Observer snapshots are separate from the operation being tested. Their · [reviewed contract](#b0014) |
| [B0015 · 98–137](../../../../../tests/unit/indexed_journal_test.cpp#L98) | Callable definition: void rollback_order_growth(const Definition& d) | calls f, image, statistics, get; growth insert, push_back; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 138–154](../../../../../tests/unit/indexed_journal_test.cpp#L138) | Callable definition: void commit_retention(const Definition& d) | calls f, grant, journal, verify; growth insert · [reviewed contract](#b0016) |
| [B0017 · 155–180](../../../../../tests/unit/indexed_journal_test.cpp#L155) | Callable definition: void limits_and_ownership(const Definition& d) | calls f, ample, live, error; guard auto cap = limits();cap.rows = 4;cap.journal_entries = 2;Fixture bounded(d, cap);auto shared = gran…; growth insert · [reviewed contract](#b0017) |
| [B0018 · 181–230](../../../../../tests/unit/indexed_journal_test.cpp#L181) | Callable definition: void differential_tape(const Definition& d) | calls indexed, limits, profile, reference; growth insert, push_back; 8 loop sites · [reviewed contract](#b0018) |
| [B0019 · 231–231](../../../../../tests/unit/indexed_journal_test.cpp#L231) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0019) |
| [B0020 · 232–236](../../../../../tests/unit/indexed_journal_test.cpp#L232) | Callable definition: int main() | calls rollback_order_growth, commit_retention, limits_and_ownership, differential_tape · [reviewed contract](#b0020) |

## B0001

[Lines 1–20](../../../../../tests/unit/indexed_journal_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:d531eb6c7ba1e5c44a01e1c3828018262766cbb0149bfe0d8004e5efbf95a46d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_journal_test.cpp: include "crown/storage/indexed.hpp", "crown/storage/reference.hpp", "index_allocation.hpp", "indexed_testing.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;memory&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_journal_test.cpp](../../../../../tests/unit/indexed_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–23](../../../../../tests/unit/indexed_journal_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a journal assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | False journal behavior fails the test process. |
| ownership | Message borrowed except failure formatting. |
| failure | runtime_error is the assertion carrier. |
| cost | One branch. |
| Design | tests/unit/indexed_journal_test.cpp:21-23, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 24–28](../../../../../tests/unit/indexed_journal_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void error(std::string_view code, Function&& operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one storage Error code from a journal action. |
| inputs / outputs | Expected code/action in; returns after exact Error match. |
| invariants | Wrong/missing code cannot pass; unrelated exceptions propagate. |
| ownership | Action forwarded; caught Error borrowed. |
| failure | Mismatch or absent expected error becomes runtime_error. |
| cost | One action and code comparison. |
| Design | tests/unit/indexed_journal_test.cpp:24-28, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 29–29](../../../../../tests/unit/indexed_journal_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWork budget() { return {1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a large fixed five-domain journal budget. |
| inputs / outputs | No input; five literal work limits out. |
| invariants | Logical work budget is not memory/account allocation authority. |
| ownership | Returned struct caller-owned. |
| failure | No custom catch. |
| cost | Fixed value. |
| Design | tests/unit/indexed_journal_test.cpp:29-29, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 30–30](../../../../../tests/unit/indexed_journal_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() { return IndexWorkAllowance(budget()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an allowance from the fixed journal budget. |
| inputs / outputs | No input; standalone IndexWorkAllowance out. |
| invariants | Allowance is independent state for ordinary operations. |
| ownership | Caller owns grant. |
| failure | Constructor errors propagate. |
| cost | Fixed allowance value construction. |
| Design | tests/unit/indexed_journal_test.cpp:30-30, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 31–31](../../../../../tests/unit/indexed_journal_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<IndexWorkAllowance> grant() { return std::make_shared<IndexWorkAllowance>(budget()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share a journal allowance through shared ownership. |
| inputs / outputs | No input; shared_ptr&lt;IndexWorkAllowance&gt; out. |
| invariants | Journal/cursors may retain the grant owner. |
| ownership | shared_ptr owns its control/state. |
| failure | Allocation failure propagates. |
| cost | Constructs shared grant ownership; exact allocator requests are not measured here. |
| Design | tests/unit/indexed_journal_test.cpp:31-31, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 32–32](../../../../../tests/unit/indexed_journal_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedLimits limits() { return {64, 8, 1024, 2048, 4096, 16384, 256, 256, 128}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return limits for the four-row indexed journal fixture. |
| inputs / outputs | No input; fixed indexed component caps out. |
| invariants | Bounds are finite component limits, not byte estimates. |
| ownership | Fixture copies limits into table. |
| failure | No custom failure path. |
| cost | Fixed value. |
| Design | tests/unit/indexed_journal_test.cpp:32-32, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 33–47](../../../../../tests/unit/indexed_journal_test.cpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Definition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define scalar projections and deterministic journal rows/keys. |
| inputs / outputs | No input; Definition owns four-field layout and three projections; row/key helpers build typed tuples. |
| invariants | Projection programs include nullary, field and repeated-field shapes; rows carry long text and a small negative decimal. |
| ownership | Layout/program/tuple values are fixture-owned. |
| failure | Tuple and projection setup errors propagate. |
| cost | Three projections and fixed-size row/key construction. |
| Design | tests/unit/indexed_journal_test.cpp:33-47, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 48–56](../../../../../tests/unit/indexed_journal_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void profile(IndexedTable& table) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply collision profile only when the testing library enables it. |
| inputs / outputs | IndexedTable reference in; mutates test hashes for profile 1 or 2, otherwise no-op. |
| invariants | No profile and unrecognized profile values use native hashes; selected profile is applied before fixture indexes/rows. |
| ownership | Borrows table; no replacement ownership. |
| failure | The source has no error branch for an unrecognized profile value. |
| cost | One testing hook or no runtime work. |
| Design | tests/unit/indexed_journal_test.cpp:48-56, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0010

[Lines 57–72](../../../../../tests/unit/indexed_journal_test.cpp#L57); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct table, indexes, rows and a pin for journal cases. |
| inputs / outputs | Definition and optional IndexedLimits in; Fixture owns IndexedTable, index IDs, handles and first-row Pin. |
| invariants | Three projections are registered; four rows use keys 9,10,9,11; first row remains pinned. |
| ownership | Fixture owns table and pin; table owns rows/indexes. |
| failure | Native table errors propagate. |
| cost | Three index builds, four inserts and one pin. |
| Design | tests/unit/indexed_journal_test.cpp:57-72, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 73–77](../../../../../tests/unit/indexed_journal_test.cpp#L73); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store copied key and member IDs in an observer record. |
| inputs / outputs | Key tuple and member TupleIds in; equality-comparable KeyImage out. |
| invariants | Member order is part of image equality. |
| ownership | Observer owns key/member copies. |
| failure | Copy failure propagates. |
| cost | Copies one bucket. |
| Design | tests/unit/indexed_journal_test.cpp:73-77, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0012

[Lines 78–82](../../../../../tests/unit/indexed_journal_test.cpp#L78); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Image {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store row and per-index key images for comparisons. |
| inputs / outputs | Rows and index key vectors in; equality-comparable Image out. |
| invariants | Captures logical values/order only; does not expose internal node addresses. |
| ownership | Image owns copies. |
| failure | Copy failures propagate. |
| cost | Space proportional to observed rows/keys/memberships. |
| Design | tests/unit/indexed_journal_test.cpp:78-82, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0013

[Lines 83–84](../../../../../tests/unit/indexed_journal_test.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L84:sha256:f1728e78b8816128d449666a8980f9b5d2e4f48408a271dfda47b91c351f22cf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Observer snapshots are separate from the operation being tested. Their allocations/work never run inside a fault/denial scope or replenish a journal. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/indexed_journal_test.cpp](../../../../../tests/unit/indexed_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 85–97](../../../../../tests/unit/indexed_journal_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Image image(Fixture& f) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create independent state observer outside journal operation scopes. |
| inputs / outputs | Fixture in; copies rows, keys and buckets, checks invariants, returns Image. |
| invariants | Snapshots are separate from the operation; their allocations/work do not replenish a journal or run in a failure/denial window. |
| ownership | Observer owns copies; fixture/table owns authoritative state. |
| failure | Native work/storage errors and copy failures propagate. |
| cost | Full table/index traversal and copied data. |
| Design | tests/unit/indexed_journal_test.cpp:85-97, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0015

[Lines 98–137](../../../../../tests/unit/indexed_journal_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback_order_growth(const Definition& d) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rollback tentative row erases, growth inserts and key-order reactivation. |
| inputs / outputs | Definition in; creates journal, attempts prohibited ordinary operations, erases rows, inserts five, checks no-ops/counters/key order/cursors, then rolls back. |
| invariants | Tentative IDs/order/membership/pin identity and committed counters restore; rollback restores next tuple ID (retry yields ID 5); cursor and outside-journal work ownership errors are checked. |
| ownership | Journal retains undo records; fixture/table owns rows/pin; observer image is a separate full copy. |
| failure | Expected storage_busy/storage_contract/invalid_cursor; failed invariant or cursor result becomes runtime_error. |
| cost | Two erases/five inserts, full observer scans and cursor traversals; rollback can process undo records linearly despite zero covered new calls. |
| Design | tests/unit/indexed_journal_test.cpp:98-137, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0016

[Lines 138–154](../../../../../tests/unit/indexed_journal_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit_retention(const Definition& d) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit retained row changes while preserving journal change views. |
| inputs / outputs | Definition in; erases two rows, inserts one, saves change-view address/cursor, commits under covered-new denial and checks statistics/invariants. |
| invariants | Commit releases retained-row/membership counters and journal entries, updates committed action counts, keeps change payload and journal cursor valid after close. |
| ownership | Journal owns history/change view; table owns committed rows; cursor retains authority/grant. |
| failure | Covered new allocation would trigger bad_alloc; assertions detect state/address/counter mismatch. |
| cost | Three changes and full invariant check; commit cleanup may be linear in history. |
| Design | tests/unit/indexed_journal_test.cpp:138-154, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0017

[Lines 155–180](../../../../../tests/unit/indexed_journal_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limits_and_ownership(const Definition& d) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check journal grant ownership, caps and composed allowances. |
| inputs / outputs | Definition in; tests null grant, empty commit, rollback cursor invalidation, weak grant retention, retained-row/history caps and a shared exhausted allowance across tables. |
| invariants | No-op erase does not consume journal history; failed row/history/work admission preserves state; Journal/cursor keeps allowance alive. |
| ownership | Two fixtures own tables; journals/cursors share grant; images are observers. |
| failure | Requires storage_contract, invalid_cursor, storage_capacity and storage_work_limit at designated operations. |
| cost | Several small fixtures and full state copies; closes under covered-new denial after grant exhaustion. |
| Design | tests/unit/indexed_journal_test.cpp:155-180, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0018

[Lines 181–230](../../../../../tests/unit/indexed_journal_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void differential_tape(const Definition& d) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare 40 journal epochs of 12 operations against ReferenceTable and an independent model. |
| inputs / outputs | Definition in; deterministic 480-event tape inserts/finds/erases, compares indexed live order, reference membership and four index buckets per step, then commits or rolls back. |
| invariants | Model restores rows/IDs/next ID on every third epoch; all projections, tuple IDs, bucket order and invariants agree; observer work is distinct from journal grant. |
| ownership | IndexedTable and ReferenceTable own separate rows/indexes; vectors/maps are model state; observer snapshots are copies. |
| failure | Any differential/invariant assertion fails; rollback/commit runs under S04 covered-new denial. |
| cost | 480 operation events plus per-step full snapshots and four-bucket scans; commit/rollback may do linear journal cleanup. |
| Design | tests/unit/indexed_journal_test.cpp:181-230, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0019

[Lines 231–231](../../../../../tests/unit/indexed_journal_test.cpp#L231); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L231-L231:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in indexed_journal_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/indexed_journal_test.cpp](../../../../../tests/unit/indexed_journal_test.cpp), [docs/session-journal.md](../../../../session-journal.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 232–236](../../../../../tests/unit/indexed_journal_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run journal rollback, retention, ownership/cap and differential tape cases. |
| inputs / outputs | No input; invokes four journal suites and prints success. |
| invariants | Pass text is reachable only after finite source assertions. |
| ownership | main owns sequencing. |
| failure | Unexpected exception fails process. |
| cost | Includes 480-model-event tape; no test execution claimed. |
| Design | tests/unit/indexed_journal_test.cpp:232-236, docs/storage_journal.md:57-182, docs/memory_accounts.md:342-409, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
