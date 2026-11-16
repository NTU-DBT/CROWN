# `tests/unit/arena_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/arena_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9b6299739885febe4070936ee55f4f4c938fcd48d54b11441cc24446ac374446`. 324 lines partitioned into 34 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/unit/arena_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This test binary fails one intercepted scalar/array global-new attempt. · [reviewed contract](#b0001) |
| [B0002 · 21–25](../../../../../tests/unit/arena_exception_test.cpp#L21) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 26–26](../../../../../tests/unit/arena_exception_test.cpp#L26) | Explanatory comments or spacing. |  |
| [B0004 · 27–33](../../../../../tests/unit/arena_exception_test.cpp#L27) | Type/record definition: class AllocationFailureScope |  · [reviewed contract](#b0004) |
| [B0005 · 34–35](../../../../../tests/unit/arena_exception_test.cpp#L34) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 36–36](../../../../../tests/unit/arena_exception_test.cpp#L36) | Callable definition: void* operator new(std::size_t bytes) | calls allocate; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 37–37](../../../../../tests/unit/arena_exception_test.cpp#L37) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0007) |
| [B0008 · 38–38](../../../../../tests/unit/arena_exception_test.cpp#L38) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 39–39](../../../../../tests/unit/arena_exception_test.cpp#L39) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 40–40](../../../../../tests/unit/arena_exception_test.cpp#L40) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 41–41](../../../../../tests/unit/arena_exception_test.cpp#L41) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 42–46](../../../../../tests/unit/arena_exception_test.cpp#L42) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0012) |
| [B0013 · 47–49](../../../../../tests/unit/arena_exception_test.cpp#L47) | Callable definition: void check(bool value, const char* message) | calls std::runtime_error; guard void check(bool value, const char* message) { · [reviewed contract](#b0013) |
| [B0014 · 50–50](../../../../../tests/unit/arena_exception_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0015 · 51–51](../../../../../tests/unit/arena_exception_test.cpp#L51) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0015) |
| [B0016 · 52–52](../../../../../tests/unit/arena_exception_test.cpp#L52) | Callable definition: Value text(std::string value) | calls ; returns value · [reviewed contract](#b0016) |
| [B0017 · 53–53](../../../../../tests/unit/arena_exception_test.cpp#L53) | Explanatory comments or spacing. |  |
| [B0018 · 54–56](../../../../../tests/unit/arena_exception_test.cpp#L54) | Callable definition: TupleLayout source() | calls ; returns {LayoutId{1}, {{ScalarType::int64}, {ScalarType::string}, {ScalarType::int64}}} · [reviewed contract](#b0018) |
| [B0019 · 57–57](../../../../../tests/unit/arena_exception_test.cpp#L57) | Explanatory comments or spacing. |  |
| [B0020 · 58–60](../../../../../tests/unit/arena_exception_test.cpp#L58) | Callable definition: Tuple row(const TupleLayout& layout, std::int64_t id, char fill = 'a') | calls tuple, n, text, std::string; returns layout.tuple({n(id), text(std::string(320, fill) + std::to_string(id)), n(id * 3)}) · [reviewed contract](#b0020) |
| [B0021 · 61–63](../../../../../tests/unit/arena_exception_test.cpp#L61) | Explanatory comments or spacing. | source comment (unverified): // Arm one failure at the next intercepted new call, then reset on either exit. · [reviewed contract](#b0021) |
| [B0022 · 64–82](../../../../../tests/unit/arena_exception_test.cpp#L64) | Callable definition: template &lt;class Function&gt; auto without_allocations(Function&& function) | calls constexpr; returns result; source comment (unverified): // Arm one failure at the next intercepted new call, then reset on either exit. · [reviewed contract](#b0022) |
| [B0023 · 83–83](../../../../../tests/unit/arena_exception_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0024 · 84–105](../../../../../tests/unit/arena_exception_test.cpp#L84) | Callable definition: void check_arena_preserved(const TupleArena& arena, const ArenaStatistics& statistics, const std::vector&lt;ArenaHandle&gt;& handles, c… | calls check, statistics, size, contains; guard check(arena.statistics() == statistics, "failed arena insertion changed statistics");; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 106–106](../../../../../tests/unit/arena_exception_test.cpp#L106) | Explanatory comments or spacing. |  |
| [B0026 · 107–181](../../../../../tests/unit/arena_exception_test.cpp#L107) | Callable definition: std::size_t arena_insert_failures(std::size_t initial_rows, bool reuse_slot) | calls source, reserve, row, push_back; guard check(initial_rows &gt; 1, "reuse sweep needs a live row to retain");; returns failures; growth insert, push_back, reserve; 4 loop sites · [reviewed contract](#b0026) |
| [B0027 · 182–182](../../../../../tests/unit/arena_exception_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0028 · 183–207](../../../../../tests/unit/arena_exception_test.cpp#L183) | Callable definition: void arena_pin_paths_do_not_allocate() | calls source, insert, row, without_allocations; guard check(arena.statistics().pins == 2, "pin creation did not update pin statistics");; returns arena.pin(first); arena.pin(second); growth insert · [reviewed contract](#b0028) |
| [B0029 · 208–208](../../../../../tests/unit/arena_exception_test.cpp#L208) | Explanatory comments or spacing. |  |
| [B0030 · 209–277](../../../../../tests/unit/arena_exception_test.cpp#L209) | Callable definition: std::size_t reference_insert_failures() | calls source, size, projected_layout, add_index; guard check(table.size() == rows.size(), "failed table insert changed row count");; returns failures; growth insert; 2 loop sites · [reviewed contract](#b0030) |
| [B0031 · 278–278](../../../../../tests/unit/arena_exception_test.cpp#L278) | Explanatory comments or spacing. |  |
| [B0032 · 279–304](../../../../../tests/unit/arena_exception_test.cpp#L279) | Callable definition: void reference_pins_survive_retirement_and_destruction() | calls source, row, insert, without_allocations; guard check(table.erase(erased), "could not erase a pinned reference row");; returns table.pin(erased); table.pin(cleared); growth insert · [reviewed contract](#b0032) |
| [B0033 · 305–306](../../../../../tests/unit/arena_exception_test.cpp#L305) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0033) |
| [B0034 · 307–324](../../../../../tests/unit/arena_exception_test.cpp#L307) | Callable definition: int main() | calls arena_insert_failures, arena_pin_paths_do_not_allocate, reference_insert_failures, reference_pins_survive_retirement_and_destruction; guard check(fresh &gt; 0 && reused &gt; 0 && vector_growth &gt; 0 && reference &gt; 0,; returns 1 · [reviewed contract](#b0034) |

## B0001

[Lines 1–20](../../../../../tests/unit/arena_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:2bfbb4d0d1c4daed89153e591b54d79663ee1e3da3d0ba62e86ba0864e5a1a81
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare arena_exception_test.cpp: include "crown/storage/arena.hpp", "crown/storage/reference.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/arena_exception_test.cpp](../../../../../tests/unit/arena_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 21–25](../../../../../tests/unit/arena_exception_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back the test binary replacement allocator with malloc after a fail countdown. |
| inputs / outputs | Size in; malloc storage or std::bad_alloc out. |
| invariants | Thread-local fail_after is one-shot; only replaced new entries reach it. |
| ownership | Test binary owns hook; matching deletes release blocks. |
| failure | Injected and malloc failures carry bad_alloc. |
| cost | One countdown check and, unless injection fires, one malloc attempt per call. |
| Design | tests/unit/arena_exception_test.cpp:21-25, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0004

[Lines 27–33](../../../../../tests/unit/arena_exception_test.cpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AllocationFailureScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope one insertion-failure position. |
| inputs / outputs | Position in; sets fail_after and resets it to -1 at destruction. |
| invariants | Noncopyable scope prevents duplicated cleanup ownership. |
| ownership | Owns no storage; mutates only test-local hook. |
| failure | Construction/destruction are noexcept. |
| cost | Two thread-local assignments. |
| Design | tests/unit/arena_exception_test.cpp:27-33, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0005

[Lines 34–35](../../../../../tests/unit/arena_exception_test.cpp#L34); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L34-L35:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in arena_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/arena_exception_test.cpp](../../../../../tests/unit/arena_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 36–36](../../../../../tests/unit/arena_exception_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace scalar global new through the local countdown. |
| inputs / outputs | Byte request in; malloc block or bad_alloc out. |
| invariants | Only scalar throwing new is defined here. |
| ownership | Caller owns returned block until matching delete. |
| failure | Injected or malloc failure propagates. |
| cost | One countdown check and, unless injection fires, one malloc attempt. |
| Design | tests/unit/arena_exception_test.cpp:36-36, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0007

[Lines 37–37](../../../../../tests/unit/arena_exception_test.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace array global new through the local countdown. |
| inputs / outputs | Byte request in; malloc block or bad_alloc out. |
| invariants | Only array throwing new is defined here. |
| ownership | Caller owns block until matching delete\[\]. |
| failure | Injected or malloc failure propagates. |
| cost | One countdown check and, unless injection fires, one malloc attempt. |
| Design | tests/unit/arena_exception_test.cpp:37-37, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0008

[Lines 38–38](../../../../../tests/unit/arena_exception_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar replacement-new storage. |
| inputs / outputs | Pointer in; no output. |
| invariants | Uses free on the replacement allocator result. |
| ownership | Consumes the allocation once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/arena_exception_test.cpp:38-38, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0009

[Lines 39–39](../../../../../tests/unit/arena_exception_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array replacement-new storage. |
| inputs / outputs | Pointer in; no output. |
| invariants | Uses free on replacement new\[\] storage. |
| ownership | Consumes the allocation once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/arena_exception_test.cpp:39-39, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0010

[Lines 40–40](../../../../../tests/unit/arena_exception_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized scalar delete. |
| inputs / outputs | Pointer and ignored size in. |
| invariants | Matches scalar replacement new. |
| ownership | Consumes scalar block once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/arena_exception_test.cpp:40-40, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0011

[Lines 41–41](../../../../../tests/unit/arena_exception_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized array delete. |
| inputs / outputs | Pointer and ignored size in. |
| invariants | Matches array replacement new\[\]. |
| ownership | Consumes array block once. |
| failure | No throw. |
| cost | One free. |
| Design | tests/unit/arena_exception_test.cpp:41-41, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0012

[Lines 42–46](../../../../../tests/unit/arena_exception_test.cpp#L42); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L46:sha256:f23c5a94ebfd83ca0850025ccb8c05140fdd3ce1eb2d5b84b654436fde82c70d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare arena_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/arena_exception_test.cpp](../../../../../tests/unit/arena_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 47–49](../../../../../tests/unit/arena_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value, const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a test assertion with a C-string message. |
| inputs / outputs | Bool/message in; returns on true or throws runtime_error. |
| invariants | A false fixture condition cannot pass. |
| ownership | Message borrowed except exception construction. |
| failure | runtime_error is the assertion carrier. |
| cost | One branch; diagnostic only on failure. |
| Design | tests/unit/arena_exception_test.cpp:47-49, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0015

[Lines 51–51](../../../../../tests/unit/arena_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap int64 fixture data in Value. |
| inputs / outputs | int64 in; same integer Value out. |
| invariants | No narrowing or coercion. |
| ownership | Returns Value by value. |
| failure | No custom catch. |
| cost | Fixed scalar construction. |
| Design | tests/unit/arena_exception_test.cpp:51-51, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0016

[Lines 52–52](../../../../../tests/unit/arena_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value text(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap string fixture data in Value. |
| inputs / outputs | Owning string in; string Value out. |
| invariants | Preserves the supplied bytes. |
| ownership | Value owns string content. |
| failure | Allocation failure propagates. |
| cost | String value construction. |
| Design | tests/unit/arena_exception_test.cpp:52-52, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0018

[Lines 54–56](../../../../../tests/unit/arena_exception_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleLayout source() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create three-column arena-fault layout. |
| inputs / outputs | No input; ID 1, fields int64/string/int64. |
| invariants | Fixture rows share this token. |
| ownership | Returned layout owns descriptor. |
| failure | Normal construction errors propagate. |
| cost | Fixed descriptor. |
| Design | tests/unit/arena_exception_test.cpp:54-56, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0020

[Lines 58–60](../../../../../tests/unit/arena_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Tuple row(const TupleLayout& layout, std::int64_t id, char fill = 'a') {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a long-string arena row. |
| inputs / outputs | Layout/id/fill in; tuple with 320 repeated chars, id and id*3 out. |
| invariants | Deterministic row content from arguments. |
| ownership | Tuple owns its generated string. |
| failure | String/tuple failures propagate. |
| cost | Constructs the retained long string and tuple; concatenation temporaries may also allocate. |
| Design | tests/unit/arena_exception_test.cpp:58-60, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0021

[Lines 61–63](../../../../../tests/unit/arena_exception_test.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L63:sha256:96a65fbdcb15641fc717148b70bc0a31a39400b04a8926c1d056a3894c78b55d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Arm one failure at the next intercepted new call, then reset on either exit. No attempts are counted; a callback catching bad_alloc can hide the probe. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/arena_exception_test.cpp](../../../../../tests/unit/arena_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 64–82](../../../../../tests/unit/arena_exception_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Function>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm a one-shot failure at the next intercepted new call. |
| inputs / outputs | Callable in; forwards result if it returns. |
| invariants | Resets hook on return and rethrow; no attempt counter, callback may catch bad_alloc. |
| ownership | Callable/result use forwarding/value semantics; helper retains no state. |
| failure | Uncaught exception rethrows after reset. |
| cost | Not a persistent denial or zero-attempt measurement. |
| Design | tests/unit/arena_exception_test.cpp:64-82, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0024

[Lines 84–105](../../../../../tests/unit/arena_exception_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_arena_preserved(const TupleArena& arena,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare saved arena counts, addresses, handles, pins and stale generation. |
| inputs / outputs | Arena/statistics/handle-address-pin snapshots in; checks invariants or throws. |
| invariants | Prior live identities stay stable; erased handle stays absent. |
| ownership | Vectors/pins are observer-owned; arena remains record owner. |
| failure | Assertion/runtime errors surface; arena diagnostic errors propagate. |
| cost | Scans saved handles and pins, then full invariant check. |
| Design | tests/unit/arena_exception_test.cpp:84-105, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0026

[Lines 107–181](../../../../../tests/unit/arena_exception_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t arena_insert_failures(std::size_t initial_rows, bool reuse_slot) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep fresh and reused arena-slot insertion failures. |
| inputs / outputs | Initial rows/reuse flag in; number of failures before successful insert out. |
| invariants | Failure preserves old identities/stats; retry uses fresh slot or advances reused generation once. |
| ownership | Each attempt owns arena/fixture vectors/pins; hook only wraps insertion. |
| failure | Catches bad_alloc; 1024 attempts without success throws runtime_error. |
| cost | At most 1024 rebuilt fixtures and full checks per failure. |
| Design | tests/unit/arena_exception_test.cpp:107-181, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0028

[Lines 183–207](../../../../../tests/unit/arena_exception_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arena_pin_paths_do_not_allocate() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe pin/erase/reset/clear with a one-shot replacement-new failure. |
| inputs / outputs | No input; exercises two pins, retirement, clear and final releases; checks counts/values. |
| invariants | Pins retain payload but not membership; last release frees retired slot. |
| ownership | Arena owns rows; Pin retains state/value; helper does not count attempts. |
| failure | Injected failure escapes if not caught internally; hook resets. |
| cost | Small fixed fixture; probe cannot prove no caught attempt. |
| Design | tests/unit/arena_exception_test.cpp:183-207, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0030

[Lines 209–277](../../../../../tests/unit/arena_exception_test.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t reference_insert_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ReferenceTable insertion failures with indexes and a retained pin. |
| inputs / outputs | No input; returns bad_alloc positions before insert success. |
| invariants | Failure preserves logical rows, revision, old IDs/address/pin; retry uses tuple ID 3. |
| ownership | Table owns rows/indexes; Pin retains one; snapshots are observer copies. |
| failure | Catches bad_alloc; bounded sweep without success throws runtime_error. |
| cost | Rebuilds three indexes/two rows per position; snapshots and invariant scans. |
| Design | tests/unit/arena_exception_test.cpp:209-277, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0032

[Lines 279–304](../../../../../tests/unit/arena_exception_test.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reference_pins_survive_retirement_and_destruction() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep pins readable across table erase, clear and destruction. |
| inputs / outputs | No input; returns first pin from a destroyed table after releasing second. |
| invariants | Pinned values/addresses remain; membership is retired, then reset releases retention. |
| ownership | Pin retains arena state and its payload after ReferenceTable lifetime; it does not retain the table or indexes. |
| failure | Assertion failures use runtime_error; no fault hook here. |
| cost | Two fixed long-string rows and pin lifecycle checks. |
| Design | tests/unit/arena_exception_test.cpp:279-304, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |

## B0033

[Lines 305–306](../../../../../tests/unit/arena_exception_test.cpp#L305); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L305-L306:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in arena_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/arena_exception_test.cpp](../../../../../tests/unit/arena_exception_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0034

[Lines 307–324](../../../../../tests/unit/arena_exception_test.cpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite arena/reference exception cases. |
| inputs / outputs | No input; calls fresh/reuse/growth/reference sweeps and prints counts. |
| invariants | Every sweep must observe at least one bad_alloc position. |
| ownership | main owns sequencing only. |
| failure | std::exception prints and returns 1; success returns 0. |
| cost | Finite source-defined sweeps; no claim the binary was run. |
| Design | tests/unit/arena_exception_test.cpp:307-324, docs/tuple_arenas.md:39-118, docs/tuple_arenas.md:77-117, docs/storage.md:72-116, [Refactor.md §6.2](../../../../../Refactor.md), [Refactor.md §11.4 S02](../../../../../Refactor.md), [Refactor.md §11.4 S03](../../../../../Refactor.md) |
