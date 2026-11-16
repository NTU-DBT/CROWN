# `tests/unit/storage_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/storage_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `44d6b22d55477fe17b91902781fa4d5fa402bc55a43c178aeb09d513a899ebe9`. 129 lines partitioned into 22 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/unit/storage_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This test binary fails one intercepted scalar/array global-new attempt. · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../tests/unit/storage_exception_test.cpp#L14) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../tests/unit/storage_exception_test.cpp#L19) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 20–20](../../../../../tests/unit/storage_exception_test.cpp#L20) | Callable definition: void* operator new(std::size_t bytes) | calls allocate; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0004) |
| [B0005 · 21–21](../../../../../tests/unit/storage_exception_test.cpp#L21) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../tests/unit/storage_exception_test.cpp#L22) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0006) |
| [B0007 · 23–23](../../../../../tests/unit/storage_exception_test.cpp#L23) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 24–24](../../../../../tests/unit/storage_exception_test.cpp#L24) | Callable definition: void operator delete(void* pointer,std::size_t) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 25–25](../../../../../tests/unit/storage_exception_test.cpp#L25) | Callable definition: void operator delete\[\](void* pointer,std::size_t) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 26–29](../../../../../tests/unit/storage_exception_test.cpp#L26) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0010) |
| [B0011 · 30–30](../../../../../tests/unit/storage_exception_test.cpp#L30) | Callable definition: void check(bool value,const std::string& message) | calls std::runtime_error; guard void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); } · [reviewed contract](#b0011) |
| [B0012 · 31–31](../../../../../tests/unit/storage_exception_test.cpp#L31) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0012) |
| [B0013 · 32–32](../../../../../tests/unit/storage_exception_test.cpp#L32) | Callable definition: Value text(std::string value) | calls ; returns value · [reviewed contract](#b0013) |
| [B0014 · 33–33](../../../../../tests/unit/storage_exception_test.cpp#L33) | Callable definition: TupleLayout source() | calls ; returns {LayoutId{1},{{ScalarType::int64},{ScalarType::string},{ScalarType::int64}}} · [reviewed contract](#b0014) |
| [B0015 · 34–38](../../../../../tests/unit/storage_exception_test.cpp#L34) | Callable definition: void initialize(ReferenceTable& table,const TupleLayout& layout) | calls add_index, projected_layout, indices, size; growth insert; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 39–43](../../../../../tests/unit/storage_exception_test.cpp#L39) | Callable definition: void expect_rows(const ReferenceTable& table,const std::vector&lt;Tuple&gt;& before) | calls snapshot, check, size, check_invariants; guard const auto after=table.snapshot(); check(after.size()==before.size(),"allocation failure changed pr…; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 44–65](../../../../../tests/unit/storage_exception_test.cpp#L44) | Callable definition: std::size_t insertion_failures() | calls source, initialize, snapshot, revision; guard check(table.revision()==revision && !table.find(candidate) && cursor.next().has_value(),"failed ins…; returns failures; growth insert; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 66–86](../../../../../tests/unit/storage_exception_test.cpp#L66) | Callable definition: std::size_t index_failures() | calls source, initialize, projected_layout, snapshot; guard check(table.indices()==indices && table.revision()==revision && cursor.next().has_value(),"failed i…; returns failures; 1 loop sites · [reviewed contract](#b0018) |
| [B0019 · 87–107](../../../../../tests/unit/storage_exception_test.cpp#L87) | Callable definition: std::size_t deletion_failures() | calls source, initialize, indices, back; guard check(table.revision()==revision && cursor.next().has_value(),"failed key deletion partially remove…; returns failures; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 108–121](../../../../../tests/unit/storage_exception_test.cpp#L108) | Callable definition: std::size_t tuple_assignment_failures() | calls tuple, n, text, std::string; guard if (failed) { ++failures; check(target==old,"failed tuple copy assignment broke validated layout/va…; returns failures; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 122–122](../../../../../tests/unit/storage_exception_test.cpp#L122) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0021) |
| [B0022 · 123–129](../../../../../tests/unit/storage_exception_test.cpp#L123) | Callable definition: int main() | calls insertion_failures, index_failures, deletion_failures, tuple_assignment_failures; guard check(insert&gt;0 && index&gt;0 && erase&gt;0 && assign&gt;0,"allocation fault sweep did not exercise failure p…; returns 1; growth insert · [reviewed contract](#b0022) |

## B0001

[Lines 1–13](../../../../../tests/unit/storage_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:4601e80336e5b5b5b3e75abc3414842087f44fb101946567333db8e9dc336b79
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_exception_test.cpp: include "crown/storage/reference.hpp", "crown/api/error.hpp", &lt;cstdlib&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;new&gt;, &lt;stdexcept&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/storage_exception_test.cpp](../../../../../tests/unit/storage_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–18](../../../../../tests/unit/storage_exception_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back scalar/array replacement new with a one-shot failure countdown and malloc. |
| inputs / outputs | Size in; malloc block or bad_alloc out. |
| invariants | The test binary replaces throwing scalar/array new only; direct libc calls are outside this path. |
| ownership | Hook is translation-unit-local; matching delete frees blocks. |
| failure | Injected or malloc failure is bad_alloc. |
| cost | One countdown check and, unless injection fires, one malloc attempt per call. |
| Design | tests/unit/storage_exception_test.cpp:14-18, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0003

[Lines 19–19](../../../../../tests/unit/storage_exception_test.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_exception_test.cpp](../../../../../tests/unit/storage_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 20–20](../../../../../tests/unit/storage_exception_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace scalar global new for the reference-storage fault sweeps. |
| inputs / outputs | Size in; malloc storage or bad_alloc. |
| invariants | No aligned/nothrow overload is independently defined in this TU. |
| ownership | Caller owns block through matching scalar delete. |
| failure | bad_alloc propagates. |
| cost | One countdown check and, unless injection fires, one malloc attempt. |
| Design | tests/unit/storage_exception_test.cpp:20-20, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0005

[Lines 21–21](../../../../../tests/unit/storage_exception_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace array global new for the reference-storage fault sweeps. |
| inputs / outputs | Size in; malloc storage or bad_alloc. |
| invariants | Array requests use the same thread-local countdown. |
| ownership | Caller owns block through matching array delete. |
| failure | bad_alloc propagates. |
| cost | One countdown check and, unless injection fires, one malloc attempt. |
| Design | tests/unit/storage_exception_test.cpp:21-21, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0006

[Lines 22–22](../../../../../tests/unit/storage_exception_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free replacement scalar-new storage. |
| inputs / outputs | Pointer in; no output. |
| invariants | Uses free. |
| ownership | Consumes block once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/storage_exception_test.cpp:22-22, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0007

[Lines 23–23](../../../../../tests/unit/storage_exception_test.cpp#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free replacement array-new storage. |
| inputs / outputs | Pointer in; no output. |
| invariants | Uses free. |
| ownership | Consumes block once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/storage_exception_test.cpp:23-23, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0008

[Lines 24–24](../../../../../tests/unit/storage_exception_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer,std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized scalar delete for local replacement new. |
| inputs / outputs | Pointer/ignored size in. |
| invariants | Matches scalar storage. |
| ownership | Consumes block once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/storage_exception_test.cpp:24-24, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0009

[Lines 25–25](../../../../../tests/unit/storage_exception_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer,std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized array delete for local replacement new\[\]. |
| inputs / outputs | Pointer/ignored size in. |
| invariants | Matches array storage. |
| ownership | Consumes block once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/storage_exception_test.cpp:25-25, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0010

[Lines 26–29](../../../../../tests/unit/storage_exception_test.cpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L29:sha256:c0cf7723e3a9f92d228f14c2f2c2df778956141c8ac13c38251d1326c3336fb0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare storage_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/storage_exception_test.cpp](../../../../../tests/unit/storage_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 30–30](../../../../../tests/unit/storage_exception_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const std::string& message) { if (!value) throw std::runtime_error(message); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one reference-storage assertion. |
| inputs / outputs | Bool/message in; runtime_error when false. |
| invariants | False assertion fails the executable. |
| ownership | Message is borrowed until failure text is built. |
| failure | runtime_error is harness carrier. |
| cost | One branch; formatting only on failure. |
| Design | tests/unit/storage_exception_test.cpp:30-30, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0012

[Lines 31–31](../../../../../tests/unit/storage_exception_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap integer fixture value. |
| inputs / outputs | int64 in; integer Value out. |
| invariants | No conversion. |
| ownership | Value returned by value. |
| failure | No custom catch. |
| cost | Fixed scalar construction. |
| Design | tests/unit/storage_exception_test.cpp:31-31, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0013

[Lines 32–32](../../../../../tests/unit/storage_exception_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value text(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap string fixture value. |
| inputs / outputs | string in; string Value out. |
| invariants | Bytes preserved. |
| ownership | Value owns moved string. |
| failure | Allocation failure propagates. |
| cost | String construction. |
| Design | tests/unit/storage_exception_test.cpp:32-32, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0014

[Lines 33–33](../../../../../tests/unit/storage_exception_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout source() { return {LayoutId{1},{{ScalarType::int64},{ScalarType::string},{ScalarType::int64}}}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the three-column ReferenceTable fixture layout. |
| inputs / outputs | No input; ID 1 int64/string/int64 descriptor. |
| invariants | All sweep fixtures use same schema. |
| ownership | Returned descriptor owns fields. |
| failure | Construction errors propagate. |
| cost | Fixed descriptor. |
| Design | tests/unit/storage_exception_test.cpp:33-33, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0015

[Lines 34–38](../../../../../tests/unit/storage_exception_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialize(ReferenceTable& table,const TupleLayout& layout) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare three projections and twelve rows for each storage sweep. |
| inputs / outputs | ReferenceTable/layout in; installs integer, composite and nullary indexes, then twelve duplicate-pattern rows. |
| invariants | Stable index/tuple IDs make no-consumption checks reproducible. |
| ownership | Table owns records/indexes. |
| failure | Setup errors propagate before fault countdown is armed. |
| cost | Three index builds plus twelve long-string inserts per attempt. |
| Design | tests/unit/storage_exception_test.cpp:34-38, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0016

[Lines 39–43](../../../../../tests/unit/storage_exception_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_rows(const ReferenceTable& table,const std::vector<Tuple>& before) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a table snapshot with the saved tuple sequence. |
| inputs / outputs | Table/preimage vector in; checks size, every tuple and invariants. |
| invariants | Row order, value and layout all match preimage. |
| ownership | Snapshot is an owning observer copy. |
| failure | Mismatch throws runtime_error; diagnostic errors propagate. |
| cost | Full snapshot and O(state) invariant scan. |
| Design | tests/unit/storage_exception_test.cpp:39-43, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0017

[Lines 44–65](../../../../../tests/unit/storage_exception_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t insertion_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep strong exception behavior of row insertion. |
| inputs / outputs | No input; returns number of bad_alloc positions before success. |
| invariants | On failure, snapshot/revision/find/cursor and next tuple ID are unchanged; retry receives ID 13. |
| ownership | Each attempt owns a fresh table, snapshot and cursor. |
| failure | Catches bad_alloc only; 512 positions without success is runtime_error. |
| cost | Rebuilds seeded table for each position and compares full state on failure. |
| Design | tests/unit/storage_exception_test.cpp:44-65, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0018

[Lines 66–86](../../../../../tests/unit/storage_exception_test.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t index_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep atomic index construction. |
| inputs / outputs | No input; returns failures before index ID 4 is installed. |
| invariants | Rows/index list/revision/cursor remain unchanged and failed build consumes no ID. |
| ownership | Fresh table/projection/snapshots per position. |
| failure | bad_alloc is expected; bounded sweep exhaustion fails. |
| cost | Rebuilds 12-row table and checks snapshot/invariants per failure. |
| Design | tests/unit/storage_exception_test.cpp:66-86, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0019

[Lines 87–107](../../../../../tests/unit/storage_exception_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t deletion_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep nullary erase_key allocation failures. |
| inputs / outputs | No input; returns failures before all rows are erased. |
| invariants | Failure leaves rows/revision/cursor intact; success removes every secondary bucket. |
| ownership | ReferenceTable owns memberships; snapshot is observer state. |
| failure | bad_alloc is expected until success; 512 misses fail. |
| cost | Repeated whole-table snapshot and invariant work per cut. |
| Design | tests/unit/storage_exception_test.cpp:87-107, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0020

[Lines 108–121](../../../../../tests/unit/storage_exception_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t tuple_assignment_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep Tuple copy-assignment allocation failures across different layouts. |
| inputs / outputs | No input; target/input Tuples in; counts failures before target equals input. |
| invariants | A failed assignment preserves old target; successful retry replaces it exactly. |
| ownership | Target/input own their tuple values. |
| failure | bad_alloc caught per cut; 64 cuts without success throws runtime_error. |
| cost | At most 64 value-copy attempts. |
| Design | tests/unit/storage_exception_test.cpp:108-121, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0021

[Lines 122–122](../../../../../tests/unit/storage_exception_test.cpp#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L122-L122:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in storage_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/storage_exception_test.cpp](../../../../../tests/unit/storage_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 123–129](../../../../../tests/unit/storage_exception_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run insertion/index/deletion/tuple-assignment failure sweeps. |
| inputs / outputs | No input; prints observed failure counts and process status. |
| invariants | Each sweep must hit at least one failure. |
| ownership | main owns sequence only. |
| failure | std::exception prints/returns 1; success returns 0. |
| cost | Finite source-declared bounds; not run in this review. |
| Design | tests/unit/storage_exception_test.cpp:123-129, docs/storage.md:72-116, docs/tuple_arenas.md:77-139, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |
