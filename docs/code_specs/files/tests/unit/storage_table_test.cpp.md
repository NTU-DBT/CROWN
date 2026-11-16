# `tests/unit/storage_table_test.cpp` — block usage map

[Source](../../../../../tests/unit/storage_table_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2e8720b5fd98266d12c7353cef6a968f924e7523a950ac825586d089dbd44786`. 262 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/unit/storage_table_test.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 23–25](../../../../../tests/unit/storage_table_test.cpp#L23) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 26–30](../../../../../tests/unit/storage_table_test.cpp#L26) | Callable definition: template&lt;class Function&gt; void error(std::string_view code, Function&& operation) | calls operation, verify, code, std::runtime_error · [reviewed contract](#b0003) |
| [B0004 · 31–31](../../../../../tests/unit/storage_table_test.cpp#L31) | Callable definition: IndexWork budget() | calls ; returns {1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000} · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../tests/unit/storage_table_test.cpp#L32) | Callable definition: IndexWorkAllowance ample() | calls IndexWorkAllowance, budget; returns IndexWorkAllowance(budget()) · [reviewed contract](#b0005) |
| [B0006 · 33–33](../../../../../tests/unit/storage_table_test.cpp#L33) | Callable definition: std::shared_ptr&lt;IndexWorkAllowance&gt; grant() | calls budget; returns std::make_shared&lt;IndexWorkAllowance&gt;(budget()); growth make_shared · [reviewed contract](#b0006) |
| [B0007 · 34–34](../../../../../tests/unit/storage_table_test.cpp#L34) | Callable definition: IndexedLimits limits() | calls ; returns {128, 8, 4096, 4096, 8192, 32768, 256, 1024, 128} · [reviewed contract](#b0007) |
| [B0008 · 35–54](../../../../../tests/unit/storage_table_test.cpp#L35) | Type/record definition: struct Definition | returns value; layout.tuple({std::int64_t{9'007'199'254'740'992LL + id}, group(id), id % 2 == 0,; growth emplace_back, push_back; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 55–64](../../../../../tests/unit/storage_table_test.cpp#L55) | Callable definition: StorageTable table(const Definition& d, bool indexed) | calls StorageTable, result, limits, defined; returns StorageTable(RelationId{1}, d.layout); result · [reviewed contract](#b0009) |
| [B0010 · 65–69](../../../../../tests/unit/storage_table_test.cpp#L65) | Callable definition: std::vector&lt;std::int64_t&gt; values(StorageTable& stored, IndexWorkAllowance* work) | calls snapshot, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 70–135](../../../../../tests/unit/storage_table_test.cpp#L70) | Callable definition: void facade_model(const Definition& d) | calls table, ample, verify, backend; returns value % 3 == id % 3; value % 3 == id % 3; growth insert, push_back; 7 loop sites · [reviewed contract](#b0011) |
| [B0012 · 136–167](../../../../../tests/unit/storage_table_test.cpp#L136) | Callable definition: void cursors_and_copy(const Definition& d, bool indexed) | calls table, ample, add_index, insert; growth insert; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 168–198](../../../../../tests/unit/storage_table_test.cpp#L168) | Callable definition: void journal_lifetimes(const Definition& d, bool indexed) | calls table, ample, add_index, insert; growth insert, make_unique · [reviewed contract](#b0013) |
| [B0014 · 199–253](../../../../../tests/unit/storage_table_test.cpp#L199) | Callable definition: void literal_journal_boundaries() | calls static_assert, layout, tuple, stored; guard static_assert(sizeof(void*) == 8 && sizeof(TupleArena::Pin) == 40);; growth insert, make_shared; 4 loop sites; source comment (unverified): // Literal admission oracle for the selected 64-bit ABI: open11 metadata · [reviewed contract](#b0014) |
| [B0015 · 254–256](../../../../../tests/unit/storage_table_test.cpp#L254) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;StorageTable&gt;);; source comment (unverified): // namespace · [reviewed contract](#b0015) |
| [B0016 · 257–262](../../../../../tests/unit/storage_table_test.cpp#L257) | Callable definition: int main() | calls facade_model, cursors_and_copy, journal_lifetimes, literal_journal_boundaries; 1 loop sites · [reviewed contract](#b0016) |

## B0001

[Lines 1–22](../../../../../tests/unit/storage_table_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:10240adef4b66a422f22de0f89c3bcd71c7a2e6095cf575531ef6ddf2062637b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_table_test.cpp: include "crown/storage/table.hpp", "index_allocation.hpp", "table_testing.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;memory&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;vector&gt;; bind local aliases/name imports; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/storage_table_test.cpp](../../../../../tests/unit/storage_table_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–25](../../../../../tests/unit/storage_table_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a StorageTable assertion. |
| inputs / outputs | Bool/message in; runtime_error on false. |
| invariants | False dispatch/model condition cannot pass. |
| ownership | Message borrowed except failure construction. |
| failure | runtime_error is harness carrier. |
| cost | One branch. |
| Design | tests/unit/storage_table_test.cpp:23-25, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0003

[Lines 26–30](../../../../../tests/unit/storage_table_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void error(std::string_view code, Function&& operation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one StorageTable Error code. |
| inputs / outputs | Code/action in; returns after exact crown::Error match. |
| invariants | Wrong/missing code fails. |
| ownership | Action forwarded; caught exception borrowed. |
| failure | Mismatch becomes runtime_error. |
| cost | One action/check. |
| Design | tests/unit/storage_table_test.cpp:26-30, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0004

[Lines 31–31](../../../../../tests/unit/storage_table_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWork budget() { return {1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a five-domain standalone IndexWork budget. |
| inputs / outputs | No input; large fixed IndexWork value out. |
| invariants | It is a work allowance, not a MemoryAccount or byte grant. |
| ownership | Returned allowance is caller-owned. |
| failure | Construction does not catch errors. |
| cost | Fixed scalar struct. |
| Design | tests/unit/storage_table_test.cpp:31-31, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0005

[Lines 32–32](../../../../../tests/unit/storage_table_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWorkAllowance ample() { return IndexWorkAllowance(budget()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a fresh standalone work allowance. |
| inputs / outputs | No input; IndexWorkAllowance initialized from budget. |
| invariants | Every helper call gets an independent test allowance. |
| ownership | Caller owns grant. |
| failure | Normal construction failure propagates. |
| cost | One small allowance object. |
| Design | tests/unit/storage_table_test.cpp:32-32, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0006

[Lines 33–33](../../../../../tests/unit/storage_table_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<IndexWorkAllowance> grant() { return std::make_shared<IndexWorkAllowance>(budget()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create shared standalone work allowance. |
| inputs / outputs | No input; shared_ptr of large IndexWorkAllowance out. |
| invariants | Sharing is explicit across journal/facade calls. |
| ownership | Returned shared owner keeps allowance alive. |
| failure | Allocation failure propagates. |
| cost | Constructs shared grant ownership; exact allocator requests are not measured here. |
| Design | tests/unit/storage_table_test.cpp:33-33, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0007

[Lines 34–34](../../../../../tests/unit/storage_table_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexedLimits limits() { return {128, 8, 4096, 4096, 8192, 32768, 256, 1024, 128}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return finite indexed component limits. |
| inputs / outputs | No input; fixed IndexedLimits out. |
| invariants | Limits belong to fixture only; they do not fund bytes. |
| ownership | Returned values copied. |
| failure | No custom failure. |
| cost | Fixed struct. |
| Design | tests/unit/storage_table_test.cpp:34-34, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0008

[Lines 35–54](../../../../../tests/unit/storage_table_test.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Definition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define mixed-scalar rows and three projection programs. |
| inputs / outputs | No input; five-field layout plus row/key helpers and projections. |
| invariants | Uses binary strings, &gt;2^53 integers, dates, decimals and repeated projection slots. |
| ownership | Definition owns programs/layout literals. |
| failure | Tuple/projection construction errors propagate. |
| cost | Fixed fixture descriptors and generated value construction. |
| Design | tests/unit/storage_table_test.cpp:35-54, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0009

[Lines 55–64](../../../../../tests/unit/storage_table_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageTable table(const Definition& d, bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct reference or indexed StorageTable with optional collision profile. |
| inputs / outputs | Definition/backend flag in; standalone facade out. |
| invariants | Reference route has no indexed limits; indexed route receives explicit limits/test hash profile. |
| ownership | Returned table owns backend state. |
| failure | Unknown build profile is a preprocessing error; constructor failures propagate. |
| cost | Creates selected backend; no account is supplied. |
| Design | tests/unit/storage_table_test.cpp:55-64, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0010

[Lines 65–69](../../../../../tests/unit/storage_table_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::int64_t> values(StorageTable& stored, IndexWorkAllowance* work) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect integer fixture IDs from an owning snapshot. |
| inputs / outputs | StorageTable/work pointer in; vector of decoded ID deltas out. |
| invariants | Subtracts the exact 2^53 base used by Definition. |
| ownership | Snapshot owns tuples; returned vector owns numbers. |
| failure | Snapshot/work errors propagate. |
| cost | Copies all live rows; output-sensitive test helper. |
| Design | tests/unit/storage_table_test.cpp:65-69, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0011

[Lines 70–135](../../../../../tests/unit/storage_table_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void facade_model(const Definition& d) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare facade backends over 500 model steps and copy/drop behavior. |
| inputs / outputs | Definition in; drives reference/indexed tables with vector/map expected rows and work grants. |
| invariants | Actual backend/limits, IDs, key order, buckets, copy owner and deleted-ID highwater are checked. |
| ownership | Tables and copies own separate state; work allowance is caller-owned. |
| failure | Checks storage_contract/foreign_handle; mismatches throw runtime_error. |
| cost | 500 mutations with snapshots, bucket/key scans and invariant checks. |
| Design | tests/unit/storage_table_test.cpp:70-135, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0012

[Lines 136–167](../../../../../tests/unit/storage_table_test.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursors_and_copy(const Definition& d, bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check borrowed cursor entries and snapshot-copy failure atomicity for either backend. |
| inputs / outputs | Definition/backend flag in; builds rows, pins, live/bucket/key cursors and repeated copy faults. |
| invariants | Cursor entries alias get() payloads; successful steps use s04_alloc Scope; failed copies preserve source/cursor/pin. |
| ownership | Table owns values; Pin retains one payload; copy is a separate owner. |
| failure | Copy cuts catch bad_alloc; work denial uses storage_work_limit. |
| cost | Copies a tiny table at each covered global-new position; test observer snapshots are separate. |
| Design | tests/unit/storage_table_test.cpp:136-167, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0013

[Lines 168–198](../../../../../tests/unit/storage_table_test.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_lifetimes(const Definition& d, bool indexed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check journal rollback, cross-backend move and retained owner lifetime. |
| inputs / outputs | Definition/backend flag in; stages mutations, exhausts grants, destroys/move-assigns journals and owner. |
| invariants | Rollback restores preimage; moved journal remains active; indexed cursor grant is exact; close is tested under new denial. |
| ownership | Journal owns shared storage/grant; cursor is journal-bound; pin retains payload. |
| failure | Checks storage_contract/invalid_cursor; bad allocation during expected nonallocating close fails test. |
| cost | Per-change rollback/destruction may be linear despite zero covered new calls. |
| Design | tests/unit/storage_table_test.cpp:168-198, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0014

[Lines 199–253](../../../../../tests/unit/storage_table_test.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void literal_journal_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check literal indexed journal work/capacity boundaries and nonallocating close. |
| inputs / outputs | No input; loops commit/rollback and one-under IndexWork/pin/entry caps on selected 64-bit ABI. |
| invariants | Literal work vectors are explicit; failed prep leaves state/cursor; exact exhausted grant closes journal. |
| ownership | StorageTable owns backend; observer snapshots and grant are test-owned. |
| failure | Expected storage_work_limit/storage_capacity; s04_alloc denies covered new attempts at close. |
| cost | Finite literal oracle; no production sizeof-Undo helper; close may traverse/destroy history linearly. |
| Design | tests/unit/storage_table_test.cpp:199-253, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |

## B0015

[Lines 254–256](../../../../../tests/unit/storage_table_test.cpp#L254); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L256:sha256:780d79e629b81f6363c3b01cce6d9e3eb758d88363639190a9e010c7bb3061a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_table_test.cpp: require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/storage_table_test.cpp](../../../../../tests/unit/storage_table_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 257–262](../../../../../tests/unit/storage_table_test.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run facade, cursor/copy, journal and literal boundary cases. |
| inputs / outputs | No input; compares both backends and returns process result. |
| invariants | Success depends on all finite assertions. |
| ownership | main owns orchestration. |
| failure | Unexpected exception fails process. |
| cost | 500-step model plus finite fault sweeps; not run in this review. |
| Design | tests/unit/storage_table_test.cpp:257-262, docs/storage.md:72-116, docs/indexed_storage.md:35-89, docs/storage_journal.md:57-182, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S04](../../../../../Refactor.md) |
