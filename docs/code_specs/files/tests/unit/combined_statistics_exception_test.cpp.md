# `tests/unit/combined_statistics_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/combined_statistics_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c712924650462cfaa50becfab43e631d5f8d7af038013c435ac5dec7611a88d3`. 40 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/unit/combined_statistics_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 7–11](../../../../../tests/unit/combined_statistics_exception_test.cpp#L7) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 12–12](../../../../../tests/unit/combined_statistics_exception_test.cpp#L12) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 13–13](../../../../../tests/unit/combined_statistics_exception_test.cpp#L13) | Callable definition: void* operator new(std::size_t n) | calls allocate; returns allocate(n); growth allocate, new · [reviewed contract](#b0004) |
| [B0005 · 14–14](../../../../../tests/unit/combined_statistics_exception_test.cpp#L14) | Callable definition: void* operator new\[\](std::size_t n) | calls ; returns allocate(n); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 15–15](../../../../../tests/unit/combined_statistics_exception_test.cpp#L15) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0006) |
| [B0007 · 16–16](../../../../../tests/unit/combined_statistics_exception_test.cpp#L16) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 17–17](../../../../../tests/unit/combined_statistics_exception_test.cpp#L17) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 18–18](../../../../../tests/unit/combined_statistics_exception_test.cpp#L18) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 19–19](../../../../../tests/unit/combined_statistics_exception_test.cpp#L19) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0010) |
| [B0011 · 20–40](../../../../../tests/unit/combined_statistics_exception_test.cpp#L20) | Callable definition: int main() | calls plan, request, database, DeltaRuntime::initialize; guard check(baseline.workload().has_previous());const auto owner=runtime.owner();std::size_t failures=0;b…; growth insert; 1 loop sites · [reviewed contract](#b0011) |

## B0001

[Lines 1–6](../../../../../tests/unit/combined_statistics_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:15c46fb257a3db7057aebdd7740d7824f15497378c433a905fa7a76a81b36d17
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare combined_statistics_exception_test.cpp: include "combined_statistics_fixture.hpp", &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;new&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–11](../../../../../tests/unit/combined_statistics_exception_test.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back the executable's replacement C++ allocation operators and fail one configured new request. |
| inputs / outputs | Requested bytes and the thread-local injecting/remaining state enter; malloc storage or std::bad_alloc exits. |
| invariants | The counter advances only while injection is active; zero remaining rejects the current request before malloc; the zero-size request asks malloc for one byte. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One malloc attempt per successful new call plus counter branches; does not count direct malloc callers or operating-system allocations. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 12–12](../../../../../tests/unit/combined_statistics_exception_test.cpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L12:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in combined_statistics_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 13–13](../../../../../tests/unit/combined_statistics_exception_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar operator new through the fail-after allocator for the combined-capture sweep. |
| inputs / outputs | A scalar C++ allocation size enters; allocated pointer or std::bad_alloc exits. |
| invariants | Injection state is scoped by main; the wrapper measures C++ new requests only. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One seam call and, when admitted, one malloc; no native MemoryAccount claim follows from this wrapper. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 14–14](../../../../../tests/unit/combined_statistics_exception_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array operator new\[\] through the same C++ allocation fault seam. |
| inputs / outputs | Array byte size enters; pointer or std::bad_alloc exits. |
| invariants | Array requests share the same position counter as scalar new, so the sweep covers their common request order. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One seam call and at most one malloc; direct malloc and syscalls are invisible. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 15–15](../../../../../tests/unit/combined_statistics_exception_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage. |
| inputs / outputs | The replacement-new pointer enters; no value exits. |
| invariants | Every replacement allocation is paired with free, independent of whether injection is still enabled. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept and does not inject failures; it frees only storage returned by this executable's malloc-backed replacement new. |
| cost | One free call; cleanup itself is not counted as a zero-heap or syscall-free production result. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 16–16](../../../../../tests/unit/combined_statistics_exception_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage. |
| inputs / outputs | The replacement-new pointer enters; no value exits. |
| invariants | Every replacement allocation is paired with free, independent of whether injection is still enabled. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept and does not inject failures; it frees only storage returned by this executable's malloc-backed replacement new. |
| cost | One free call; cleanup itself is not counted as a zero-heap or syscall-free production result. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 17–17](../../../../../tests/unit/combined_statistics_exception_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage through the sized deallocation overload. |
| inputs / outputs | The replacement-new pointer enters; no value exits. |
| invariants | Every replacement allocation is paired with free, independent of whether injection is still enabled. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept and does not inject failures; it frees only storage returned by this executable's malloc-backed replacement new. |
| cost | One free call; cleanup itself is not counted as a zero-heap or syscall-free production result. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 18–18](../../../../../tests/unit/combined_statistics_exception_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage through the sized deallocation overload. |
| inputs / outputs | The replacement-new pointer enters; no value exits. |
| invariants | Every replacement allocation is paired with free, independent of whether injection is still enabled. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept and does not inject failures; it frees only storage returned by this executable's malloc-backed replacement new. |
| cost | One free call; cleanup itself is not counted as a zero-heap or syscall-free production result. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 19–19](../../../../../tests/unit/combined_statistics_exception_test.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:5c78fa04cbdbab70f26c43b2aec4be3f45fca693a14f2e7ecaaa67472437a1ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare combined_statistics_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/combined_statistics_exception_test.cpp](../../../../../tests/unit/combined_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 20–40](../../../../../tests/unit/combined_statistics_exception_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep allocation failure across a paired owner/workload capture after committed data and a mode-segment rotation. |
| inputs / outputs | Creates one DeltaRuntime, selects the fixture request, commits S(8), enters maintenance mode, then retries capture at increasing global-new fail positions. |
| invariants | Each failed capture leaves owner, sequence, canonical state, workload previous/current slabs, and old report facts unchanged; each position is followed by a successful recovery capture. Success terminates the sweep. |
| ownership | The runtime is local; baseline and each returned CombinedCapture own copied state/workload facts. No capture retains a runtime cursor or row pin. |
| failure | Only std::bad_alloc from the replacement global C++ new/new\[\] is accepted as an injected failure. Runtime input has already committed; this does not inject into malloc paths or native syscalls. |
| cost | Repeated paired state/workload captures, fixture grouping, invariant checks, and JSON-independent workload comparisons run once per failpoint; this is exception-safety evidence, not a timed overhead result. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/verification/c01-statistics-combined-root-results-2026-11-07.md](../../../../verification/c01-statistics-combined-root-results-2026-11-07.md), [Refactor.md](../../../../../Refactor.md) |
