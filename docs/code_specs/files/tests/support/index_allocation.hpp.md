# `tests/support/index_allocation.hpp` — block usage map

[Source](../../../../../tests/support/index_allocation.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `95bdd7c8355223c6431099fbb63b979558d590d91c1f14059cad389f6297ca6a`. 70 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/support/index_allocation.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Single-TU test-executable replacement new/delete, following the native C05 · [reviewed contract](#b0001) |
| [B0002 · 18–24](../../../../../tests/support/index_allocation.hpp#L18) | Callable definition: inline void position() | calls max · [reviewed contract](#b0002) |
| [B0003 · 25–28](../../../../../tests/support/index_allocation.hpp#L25) | Callable definition: \[\[gnu::noinline\]\] inline void* allocate(std::size_t size) | calls position, std::malloc; returns value; growth allocate, malloc · [reviewed contract](#b0003) |
| [B0004 · 29–35](../../../../../tests/support/index_allocation.hpp#L29) | Callable definition: \[\[gnu::noinline\]\] inline void* aligned(std::size_t size, std::size_t alignment) | calls position, max, std::aligned_alloc; returns value · [reviewed contract](#b0004) |
| [B0005 · 36–36](../../../../../tests/support/index_allocation.hpp#L36) | Callable definition: \[\[gnu::noinline\]\] inline void release(void* value) noexcept | calls std::free · [reviewed contract](#b0005) |
| [B0006 · 37–46](../../../../../tests/support/index_allocation.hpp#L37) | Type/record definition: class Scope |  · [reviewed contract](#b0006) |
| [B0007 · 47–50](../../../../../tests/support/index_allocation.hpp#L47) | Closes surrounding scope/type. | source comment (unverified): // namespace s04_alloc · [reviewed contract](#b0007) |
| [B0008 · 51–51](../../../../../tests/support/index_allocation.hpp#L51) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n) | calls s04_alloc::allocate; returns s04_alloc::allocate(n); growth allocate, new; source comment (unverified): // No-inline allocation/deallocation seams keep optimized compilers from · [reviewed contract](#b0008) |
| [B0009 · 52–52](../../../../../tests/support/index_allocation.hpp#L52) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n) | calls ; returns s04_alloc::allocate(n); growth allocate, new · [reviewed contract](#b0009) |
| [B0010 · 53–53](../../../../../tests/support/index_allocation.hpp#L53) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, const std::nothrow_t&) noexcept | calls s04_alloc::allocate; returns s04_alloc::allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0010) |
| [B0011 · 54–54](../../../../../tests/support/index_allocation.hpp#L54) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, const std::nothrow_t&) noexcept | calls ; returns s04_alloc::allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0011) |
| [B0012 · 55–55](../../../../../tests/support/index_allocation.hpp#L55) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, std::align_val_t alignment) | calls s04_alloc::aligned; returns s04_alloc::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0012) |
| [B0013 · 56–56](../../../../../tests/support/index_allocation.hpp#L56) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, std::align_val_t alignment) | calls ; returns s04_alloc::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0013) |
| [B0014 · 57–57](../../../../../tests/support/index_allocation.hpp#L57) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept | calls s04_alloc::aligned; returns s04_alloc::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); nullptr; growth new · [reviewed contract](#b0014) |
| [B0015 · 58–58](../../../../../tests/support/index_allocation.hpp#L58) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept | calls ; returns s04_alloc::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); nullptr; growth new · [reviewed contract](#b0015) |
| [B0016 · 59–59](../../../../../tests/support/index_allocation.hpp#L59) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p) noexcept | calls s04_alloc::release · [reviewed contract](#b0016) |
| [B0017 · 60–60](../../../../../tests/support/index_allocation.hpp#L60) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0017) |
| [B0018 · 61–61](../../../../../tests/support/index_allocation.hpp#L61) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::size_t) noexcept | calls s04_alloc::release · [reviewed contract](#b0018) |
| [B0019 · 62–62](../../../../../tests/support/index_allocation.hpp#L62) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::size_t) noexcept | calls  · [reviewed contract](#b0019) |
| [B0020 · 63–63](../../../../../tests/support/index_allocation.hpp#L63) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, const std::nothrow_t&) noexcept | calls s04_alloc::release · [reviewed contract](#b0020) |
| [B0021 · 64–64](../../../../../tests/support/index_allocation.hpp#L64) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0021) |
| [B0022 · 65–65](../../../../../tests/support/index_allocation.hpp#L65) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::align_val_t) noexcept | calls s04_alloc::release · [reviewed contract](#b0022) |
| [B0023 · 66–66](../../../../../tests/support/index_allocation.hpp#L66) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::align_val_t) noexcept | calls  · [reviewed contract](#b0023) |
| [B0024 · 67–67](../../../../../tests/support/index_allocation.hpp#L67) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::size_t, std::align_val_t) noexcept | calls s04_alloc::release · [reviewed contract](#b0024) |
| [B0025 · 68–68](../../../../../tests/support/index_allocation.hpp#L68) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0025) |
| [B0026 · 69–69](../../../../../tests/support/index_allocation.hpp#L69) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept | calls s04_alloc::release · [reviewed contract](#b0026) |
| [B0027 · 70–70](../../../../../tests/support/index_allocation.hpp#L70) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::align_val_t, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0027) |

## B0001

[Lines 1–17](../../../../../tests/support/index_allocation.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline thread_local bool enabled
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep per-thread replacement-new measurement and persistent denial state for one test executable. |
| inputs / outputs | enabled gates position counting; remaining&lt;0 means count without injection; remaining&gt;0 permits that many positions; zero rejects every subsequent covered attempt; calls/triggered record attempt count/injected denial. |
| invariants | Only the thread-local helper state is controlled. Counts include failed covered new calls, not bytes, frees, resident/peak allocations, query-account requests or raw malloc/realloc calls. Other threads have separate counters but share the executable replacement functions. |
| ownership | Inline thread-local scalar storage; no query/account or heap payload is owned. |
| failure | Counter exhaustion and configured zero throw bad_alloc through position; triggered marks injected zero, not every possible allocator failure. |
| cost | Fixed checks/stores per covered new while enabled; no added production library code. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–24](../../../../../tests/support/index_allocation.hpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void position()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count and possibly deny the next covered C++ allocation attempt. |
| inputs / outputs | When disabled returns; otherwise checks calls overflow, increments calls, throws at remaining==0 (leaving zero persistent), or decrements positive remaining. |
| invariants | The rejected position is counted. Negative remaining counts without denial. Overflow rejection occurs before increment and does not set triggered. No one-shot auto-disarm or system malloc interposition. |
| ownership | Mutates only per-thread scalar test state. |
| failure | Throws bad_alloc for counter exhaustion/configured denial; underlying malloc can fail later independently. |
| cost | Fixed arithmetic/branches with no helper allocation; exception propagation itself is a runtime failure path, not measured bytes. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 25–28](../../../../../tests/support/index_allocation.hpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void* allocate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Interpose ordinary global C++ allocation with an explicit malloc/free-compatible test seam. |
| inputs / outputs | Calls position then malloc(size?size:1), returning raw storage or throwing bad_alloc. |
| invariants | Only covered new/new\[\] calls reach position; no new_handler retry loop or malloc-failure injection is implemented. Zero-size request is normalized to one byte. |
| ownership | Successful caller owns raw storage and must release through matching replacement delete/free; this helper carries no MemoryAccount. |
| failure | Persistent injected denial precedes malloc; actual malloc-null also throws but need not set triggered. |
| cost | One counter gate plus one real malloc request. calls measures attempts, not successful allocations, size, allocator overhead or latency. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 29–35](../../../../../tests/support/index_allocation.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void* aligned(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Interpose aligned global C++ allocation while preserving aligned_alloc size constraints. |
| inputs / outputs | Counts/denies position, checks size+(alignment-1) overflow, rounds normalized nonzero size to an alignment multiple, then calls aligned_alloc. |
| invariants | Alignment comes from valid C++ align_val_t new calls and is nonzero/supported; direct arbitrary alignment is not validated. This seam extends coverage to aligned C++ forms, not every libc allocation. |
| ownership | Returns raw aligned malloc-family storage released by the replacement free seam; owns no account. |
| failure | Injected denial, rounding overflow or actual aligned_alloc-null throws bad_alloc. triggered identifies injection only. |
| cost | Fixed rounding/checks plus one actual aligned allocation with possible padded size; padded bytes are not recorded by calls. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 36–36](../../../../../tests/support/index_allocation.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void release(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release replacement-new storage without creating another measured allocation. |
| inputs / outputs | Calls std::free(value), including harmless null. |
| invariants | All delete variants route here; no destructor invocation, size validation or account-ledger reconciliation occurs in release itself. |
| ownership | Caller transfers only a pointer allocated by this compatible replacement family. Object destructor execution precedes ordinary delete dispatch. |
| failure | Declared noexcept; no injected deallocation failure or recovery. |
| cost | One free operation with actual allocator teardown cost; no counting of frees/live bytes and no replacement allocation. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 37–46](../../../../../tests/support/index_allocation.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Scope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound one nonnested allocation measurement/injection window with automatic disarming. |
| inputs / outputs | Constructor terminates if enabled, sets fail_after/calls=0/triggered=false/enabled=true; destructor sets enabled=false and remaining=-1, preserving calls/triggered for later assertions. |
| invariants | Scope default -1 counts covered calls without denial; zero is persistent C++ new denial until scope exit. Copy/assignment are deleted and user destructor suppresses implicit move, so guard is neither copied nor moved. |
| ownership | Guard owns only responsibility to toggle thread-local test state; no independent query grant/account/payload. |
| failure | Nested active Scope terminates deliberately; destructor disarms during unwinding without allocating. Caller code inspects counters after the scope. |
| cost | Fixed flag/counter setup and teardown; measured operation may allocate and fail arbitrarily. This is single-TU test support, never a storage-library dependency. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 47–50](../../../../../tests/support/index_allocation.hpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L50:sha256:96da8c5f809456c448b1ba46810962dc9834dad1fb21306134c0372f04b63ff9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in index_allocation.hpp: namespace s04_alloc. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 51–51](../../../../../tests/support/index_allocation.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n) { return s04_alloc::allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary throwing global new overload. |
| inputs / outputs | Forwards raw size to s04_alloc::allocate; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 52–52](../../../../../tests/support/index_allocation.hpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n) { return s04_alloc::allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary throwing global new overload. |
| inputs / outputs | Forwards raw size to s04_alloc::allocate; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 53–53](../../../../../tests/support/index_allocation.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, const std::nothrow_t&) noexcept { try { return s04_alloc::allocate(n); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary nothrow global new overload. |
| inputs / outputs | Forwards raw size to s04_alloc::allocate; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 54–54](../../../../../tests/support/index_allocation.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, const std::nothrow_t&) noexcept { try { return s04_alloc::allocate(n); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary nothrow global new overload. |
| inputs / outputs | Forwards raw size to s04_alloc::allocate; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 55–55](../../../../../tests/support/index_allocation.hpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment) { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned throwing global new overload. |
| inputs / outputs | Forwards raw size and alignment to s04_alloc::aligned; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 56–56](../../../../../tests/support/index_allocation.hpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment) { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned throwing global new overload. |
| inputs / outputs | Forwards raw size and alignment to s04_alloc::aligned; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 57–57](../../../../../tests/support/index_allocation.hpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned nothrow global new overload. |
| inputs / outputs | Forwards raw size and alignment to s04_alloc::aligned; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 58–58](../../../../../tests/support/index_allocation.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return s04_alloc::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned nothrow global new overload. |
| inputs / outputs | Forwards raw size and alignment to s04_alloc::aligned; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 59–59](../../../../../tests/support/index_allocation.hpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 60–60](../../../../../tests/support/index_allocation.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 61–61](../../../../../tests/support/index_allocation.hpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::size_t) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 62–62](../../../../../tests/support/index_allocation.hpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::size_t) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 63–63](../../../../../tests/support/index_allocation.hpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 64–64](../../../../../tests/support/index_allocation.hpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 65–65](../../../../../tests/support/index_allocation.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::align_val_t) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 66–66](../../../../../tests/support/index_allocation.hpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 67–67](../../../../../tests/support/index_allocation.hpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::size_t, std::align_val_t) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 68–68](../../../../../tests/support/index_allocation.hpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::size_t, std::align_val_t) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 69–69](../../../../../tests/support/index_allocation.hpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 70–70](../../../../../tests/support/index_allocation.hpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t, const std::nothrow_t&) noexcept { s04_alloc::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to s04_alloc::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [tests/unit/indexed_fault_test.cpp](../../../../../tests/unit/indexed_fault_test.cpp), [tests/unit/indexed_runtime_budget_test.cpp](../../../../../tests/unit/indexed_runtime_budget_test.cpp), [tests/unit/invariant_memory_test.cpp](../../../../../tests/unit/invariant_memory_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |
