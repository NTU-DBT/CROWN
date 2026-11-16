# `tests/unit/selection_publication_fault_independent_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_publication_fault_independent_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `60df4216f918971dec859c27160afd71cf65076e9e217f31bcb56c6c3918f1b1`. 173 lines partitioned into 36 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 13–18](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L13) | Callable definition: \[\[gnu::noinline\]\] void before_allocation() | calls max · [reviewed contract](#b0002) |
| [B0003 · 19–23](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L19) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t size) | calls before_allocation, std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0003) |
| [B0004 · 24–28](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L24) | Callable definition: \[\[gnu::noinline\]\] void* allocate_aligned(std::size_t size,std::size_t alignment) | calls before_allocation, posix_memalign; returns result · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L29) | Explanatory comments or spacing. | source comment (unverified): // Keep each replacement allocation/deallocation boundary explicit at -O3. · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L31) | Callable definition: \[\[gnu::noinline\]\] void release(void* pointer) noexcept | calls std::free; source comment (unverified): // Keep each replacement allocation/deallocation boundary explicit at -O3. · [reviewed contract](#b0006) |
| [B0007 · 32–37](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L32) | Type/record definition: struct Measure |  · [reviewed contract](#b0007) |
| [B0008 · 38–38](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L38) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 39–39](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L39) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n) | calls allocate; returns allocate(n); growth allocate, new · [reviewed contract](#b0009) |
| [B0010 · 40–40](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L40) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n) | calls ; returns allocate(n); growth allocate, new · [reviewed contract](#b0010) |
| [B0011 · 41–41](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L41) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n,std::align_val_t a) | calls allocate_aligned; returns allocate_aligned(n,static_cast&lt;std::size_t&gt;(a)); growth new · [reviewed contract](#b0011) |
| [B0012 · 42–42](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L42) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n,std::align_val_t a) | calls ; returns allocate_aligned(n,static_cast&lt;std::size_t&gt;(a)); growth new · [reviewed contract](#b0012) |
| [B0013 · 43–43](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L43) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n,const std::nothrow_t&) noexcept | calls allocate; returns allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0013) |
| [B0014 · 44–44](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L44) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n,const std::nothrow_t&) noexcept | calls ; returns allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0014) |
| [B0015 · 45–45](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L45) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n,std::align_val_t a,const std::nothrow_t&) noexcept | calls allocate_aligned; returns allocate_aligned(n,static_cast&lt;std::size_t&gt;(a)); nullptr; growth new · [reviewed contract](#b0015) |
| [B0016 · 46–46](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L46) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n,std::align_val_t a,const std::nothrow_t&) noexcept | calls ; returns allocate_aligned(n,static_cast&lt;std::size_t&gt;(a)); nullptr; growth new · [reviewed contract](#b0016) |
| [B0017 · 47–47](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L47) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p) noexcept | calls release · [reviewed contract](#b0017) |
| [B0018 · 48–48](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L48) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0018) |
| [B0019 · 49–49](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L49) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p,std::size_t) noexcept | calls release · [reviewed contract](#b0019) |
| [B0020 · 50–50](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L50) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0020) |
| [B0021 · 51–51](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L51) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p,std::align_val_t) noexcept | calls release · [reviewed contract](#b0021) |
| [B0022 · 52–52](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L52) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p,std::align_val_t) noexcept | calls  · [reviewed contract](#b0022) |
| [B0023 · 53–53](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L53) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p,std::size_t,std::align_val_t) noexcept | calls release · [reviewed contract](#b0023) |
| [B0024 · 54–54](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L54) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p,std::size_t,std::align_val_t) noexcept | calls  · [reviewed contract](#b0024) |
| [B0025 · 55–55](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L55) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p,const std::nothrow_t&) noexcept | calls release · [reviewed contract](#b0025) |
| [B0026 · 56–56](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L56) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p,const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0026) |
| [B0027 · 57–57](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L57) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p,std::align_val_t,const std::nothrow_t&) noexcept | calls release · [reviewed contract](#b0027) |
| [B0028 · 58–58](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L58) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p,std::align_val_t,const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0028) |
| [B0029 · 59–61](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L59) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0029) |
| [B0030 · 62–64](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L62) | Callable definition: s::Request request(unsigned id) | calls depth; returns value · [reviewed contract](#b0030) |
| [B0031 · 65–69](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L65) | Callable definition: current::CurrentSelection select(const BooleanFixture& f,r::PhysicalRuntime& owner,s::PlanCache& cache, unsigned id,s::CacheUse u… | calls current::select_current, request, complete; returns complete(attempt) · [reviewed contract](#b0031) |
| [B0032 · 70–76](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L70) | Type/record definition: struct Scenario |  · [reviewed contract](#b0032) |
| [B0033 · 77–77](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L77) | Type/record definition: struct FaultSummary |  · [reviewed contract](#b0033) |
| [B0034 · 78–159](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L78) | Callable definition: FaultSummary focused(const BooleanFixture& f,r::PhysicalRuntime& owner,bool warm) | calls canonical_state, workload_statistics, owner, request; guard check(successful.selection && measured_calls&gt;8 && measured_calls&lt;100'000,"focused publication basel…; returns summary; growth insert; 2 loop sites; source comment (unverified): // A recovered allocation after publication is not falsely classified as · [reviewed contract](#b0034) |
| [B0035 · 160–160](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L160) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0035) |
| [B0036 · 161–173](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L161) | Callable definition: int main(int argc,char** argv) | calls check, boolean_fixture, r::PhysicalRuntime::initialize, lower; guard check(argc==2,"usage: selection_publication_fault_independent_test REPOSITORY_ROOT");; returns 1 · [reviewed contract](#b0036) |

## B0001

[Lines 1–12](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:487283bda3fb7fd6c2ac0deecf3d3c37e4a52ec93517f02060f0008d16280f0b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_publication_fault_independent_test.cpp: include "selection_independent_fixture.hpp", &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;new&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–18](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void before_allocation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm and advance the test executable's selected replacement-new fault position. |
| inputs / outputs | An active measurement increments calls; remaining zero sets triggered and throws bad_alloc, finite positive remaining decrements, and the unlimited sentinel stays unchanged. |
| invariants | The hook observes only calls routed through this test translation unit's replacement operators; the campaign bounds the measured baseline below 100,000 calls. |
| ownership | Four thread-local scalar controls; it owns no query account block or caller allocation. |
| failure | The chosen position raises bad_alloc before the wrapped allocator runs; counter wrap is not separately saturated. |
| cost | One enabled check and counter update per wrapped allocation attempt; inactive mode returns after one thread-local read. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 19–23](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t size)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back ordinary scalar and array replacement-new requests with the fault hook and malloc. |
| inputs / outputs | Requested size becomes malloc(size), with zero normalized to one byte; a successful pointer returns to the matching replacement delete. |
| invariants | Every request passes through before_allocation before malloc; zero-size requests still receive a non-null one-byte request when malloc succeeds. |
| ownership | The malloc block is released by release; this shim is executable-local test instrumentation. |
| failure | The hook or a null malloc result throws std::bad_alloc. |
| cost | One hook plus one C allocator request on the non-injected path; allocator work and byte accounting are separate from the call counter. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 24–28](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate_aligned(std::size_t size,std::size_t alignment)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back aligned replacement-new requests through the fault hook and POSIX aligned allocation. |
| inputs / outputs | Size and alignment go to posix_memalign, with zero size normalized to one; success returns its pointer. |
| invariants | The same fault position is consumed before posix_memalign and all results use the common free-based release path. |
| ownership | The returned aligned block is owned by the caller until a matching replacement delete. |
| failure | The hook or a nonzero posix_memalign result becomes std::bad_alloc. |
| cost | One hook and one POSIX allocator request unless the hook fails; system allocator work is not a fixed-cost bound. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 29–30](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L30:sha256:2f21552e2dc77de3028671f6b64d4fb86427917859aee17aa683b8c05c2dcf54
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Keep each replacement allocation/deallocation boundary explicit at -O3. Every delete form reaches the same nonallocating release operation. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 31–31](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void release(void* pointer) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the test executable's replacement allocation helpers. |
| inputs / outputs | A pointer is passed directly to std::free; the helper returns no value. |
| invariants | All sized, array, aligned and nothrow delete overloads converge on this deallocation boundary. |
| ownership | It relinquishes the malloc-compatible block; it does not touch a MemoryAccount ledger. |
| failure | Declared noexcept; no error translation is provided for an invalid pointer. |
| cost | One free call; deallocation time depends on the C allocator and is not measured by calls. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 32–37](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L32); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Measure {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope the replacement-new counter or one persistent fault position around a focused call. |
| inputs / outputs | An optional fail index resets calls and triggered, sets remaining, and turns measurement on; destruction disables it and restores the unlimited sentinel. |
| invariants | The test uses nonnested scopes by convention. This type has no nesting or copy guard; destruction disables measurement and restores remaining to the unlimited sentinel. |
| ownership | No dynamic resource is owned; the object controls thread-local test state for its lexical lifetime. |
| failure | The source has no explicit failure branch; the constructor is not declared noexcept and its caller still runs fallible work inside the scope. |
| cost | A few thread-local scalar writes at scope entry and exit; not an allocator census. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 38–38](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_publication_fault_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 39–39](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the scalar throwing replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size are forwarded to allocate(n); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | The fault hook or underlying allocator failure propagates as std::bad_alloc. |
| cost | One hook and one malloc request on a successful attempt. Allocator work is size/runtime dependent and is not represented by a fixed count. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 40–40](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the array throwing replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size are forwarded to allocate(n); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | The fault hook or underlying allocator failure propagates as std::bad_alloc. |
| cost | One hook and one malloc request on a successful attempt. Allocator work is size/runtime dependent and is not represented by a fixed count. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 41–41](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n,std::align_val_t a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the scalar aligned throwing replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size and alignment are forwarded to allocate_aligned(n,a); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | The fault hook or underlying allocator failure propagates as std::bad_alloc. |
| cost | One hook and one posix_memalign request on a successful attempt. Allocator work is size/runtime dependent and is not represented by a fixed count. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 42–42](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n,std::align_val_t a)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the array aligned throwing replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size and alignment are forwarded to allocate_aligned(n,a); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | The fault hook or underlying allocator failure propagates as std::bad_alloc. |
| cost | One hook and one posix_memalign request on a successful attempt. Allocator work is size/runtime dependent and is not represented by a fixed count. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 43–43](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n,const std::nothrow_t&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the scalar nothrow replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size are forwarded to allocate(n); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | Catches any exception from the helper and returns nullptr, as the nothrow form requires. |
| cost | One hook and one malloc request on a successful attempt. The wrapper also enters a try/catch boundary; it does not add account or RSS measurement. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 44–44](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n,const std::nothrow_t&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the array nothrow replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size are forwarded to allocate(n); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | Catches any exception from the helper and returns nullptr, as the nothrow form requires. |
| cost | One hook and one malloc request on a successful attempt. The wrapper also enters a try/catch boundary; it does not add account or RSS measurement. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 45–45](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n,std::align_val_t a,const std::nothrow_t&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the scalar aligned nothrow replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size and alignment are forwarded to allocate_aligned(n,a); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | Catches any exception from the helper and returns nullptr, as the nothrow form requires. |
| cost | One hook and one posix_memalign request on a successful attempt. The wrapper also enters a try/catch boundary; it does not add account or RSS measurement. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 46–46](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n,std::align_val_t a,const std::nothrow_t&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the array aligned nothrow replacement allocation form for this test executable. |
| inputs / outputs | The C++ allocation size and alignment are forwarded to allocate_aligned(n,a); success returns the helper's pointer. |
| invariants | This signature routes one allocation family through the same thread-local fault position; it adds no retained test state. |
| ownership | A successful malloc-compatible block is later freed by the matching local delete overload; this is not product telemetry. |
| failure | Catches any exception from the helper and returns nullptr, as the nothrow form requires. |
| cost | One hook and one posix_memalign request on a successful attempt. The wrapper also enters a try/catch boundary; it does not add account or RSS measurement. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 47–47](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the scalar unsized replacement delete form to the shared release helper. |
| inputs / outputs | pointer only -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 48–48](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the array unsized replacement delete form to the shared release helper. |
| inputs / outputs | pointer only -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 49–49](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p,std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the scalar sized replacement delete form to the shared release helper. |
| inputs / outputs | pointer; size is ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 50–50](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p,std::size_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the array sized replacement delete form to the shared release helper. |
| inputs / outputs | pointer; size is ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 51–51](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p,std::align_val_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the scalar aligned replacement delete form to the shared release helper. |
| inputs / outputs | pointer; alignment is ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 52–52](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p,std::align_val_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the array aligned replacement delete form to the shared release helper. |
| inputs / outputs | pointer; alignment is ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 53–53](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p,std::size_t,std::align_val_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the scalar sized aligned replacement delete form to the shared release helper. |
| inputs / outputs | pointer; size and alignment are ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 54–54](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p,std::size_t,std::align_val_t) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the array sized aligned replacement delete form to the shared release helper. |
| inputs / outputs | pointer; size and alignment are ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 55–55](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p,const std::nothrow_t&) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the scalar nothrow cleanup replacement delete form to the shared release helper. |
| inputs / outputs | pointer; tag is ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 56–56](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p,const std::nothrow_t&) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the array nothrow cleanup replacement delete form to the shared release helper. |
| inputs / outputs | pointer; tag is ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 57–57](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p,std::align_val_t,const std::nothrow_t&) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the scalar aligned nothrow cleanup replacement delete form to the shared release helper. |
| inputs / outputs | pointer; alignment and tag are ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 58–58](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p,std::align_val_t,const std::nothrow_t&) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the array aligned nothrow cleanup replacement delete form to the shared release helper. |
| inputs / outputs | pointer; alignment and tag are ignored -&gt; release(p); no deallocation metadata is inspected. |
| invariants | This overload is only the executable-local replacement boundary; all forms free through release. |
| ownership | The pointer's allocation lifetime ends here; no query owner or prior selection is modified by the wrapper itself. |
| failure | The overload is noexcept and does not translate an invalid free into a test diagnostic. |
| cost | One release call followed by the C allocator's free work; the instrumentation does not time that work. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0029

[Lines 59–61](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L61:sha256:6e53fa0a4be56e16cc5598b94b2c7ac916d155108741a314267711d14f1c5279
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_publication_fault_independent_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0030

[Lines 62–64](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
s::Request request(unsigned id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Vary the aggregate score-bit limit for a direct-CQ independent selection request. |
| inputs / outputs | An id is added to the fixture's depth request as score_bits = 500 + id; the returned request selects the same scoring mode with a distinct bound. |
| invariants | The focused campaign prepares the wanted request before arming fault measurement, so request construction is not one of the injected selection positions. |
| ownership | Returns a caller-owned request value; it borrows no owner or cache storage. |
| failure | The helper itself has no explicit error translation; a later select/complete call can return or raise the test failure. |
| cost | Copies a request and writes one scalar bound; delegated selection cost is accounted separately. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 65–69](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
current::CurrentSelection select(const BooleanFixture& f,r::PhysicalRuntime& owner,s::PlanCache& cache,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one independent current-selection request and retain its typed result handle. |
| inputs / outputs | Fixture snapshot, PhysicalRuntime, cache, id and cache-use policy are passed to select_current with DirectCQ{}; complete requires a complete Attempt and returns a copied CurrentSelection. |
| invariants | The helper returns a handle copy before its local Attempt dies; the independent fixture's complete() reference itself only borrows that Attempt. |
| ownership | The caller owns the returned shared result handle; the BooleanFixture and runtime remain caller-owned. |
| failure | An unsuccessful Attempt is converted by complete into a test exception; the native noexcept API retains its stop/stage diagnostics. |
| cost | One full current selection may capture, assess candidates, lower/bind a plan and touch the cache; work and allocations depend on the request and cache path. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 70–76](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L70); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Scenario {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a two-entry FIFO cache and retain two prior current selections for the fault campaign. |
| inputs / outputs | A BooleanFixture and physical owner construct a cache capped at 2 entries, 8 MiB of key bytes and 32 MiB of plan payload, then store selections for ids 0 and 1. |
| invariants | The two retained artifacts occupy the expected prior cache state; the cache is exclusive to this scenario and no global cache is used. |
| ownership | Owns the PlanCache control and two CurrentSelection shared handles; borrows the fixture/runtime during construction. Result data and staged cache entries retain their allocating query account. |
| failure | Cache creation or either complete selection can fail/throw; construction is not treated as infallible setup. |
| cost | PlanCache::create allocates its CacheData control separately via unique_ptr; two full selections follow, and retained result/cache-entry graphs consume query-account and logical cache caps. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0033

[Lines 77–77](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultSummary {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect the focused campaign's tested positions and publication outcomes. |
| inputs / outputs | Three size counters report total positions, allocation failures observed during publication, and positions that completed after a fault was triggered. |
| invariants | The counters distinguish an error result from a fully completed result after the injected position; they do not claim every fault must abort. |
| ownership | Plain value fields returned to the caller; no query handle is retained. |
| failure | No custom failure behavior is defined; checks in focused throw on an unexpected campaign result. |
| cost | One unconditional position increment and at most one branch-dependent outcome increment per selected position; the number of positions is data-dependent. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0034

[Lines 78–159](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FaultSummary focused(const BooleanFixture& f,r::PhysicalRuntime& owner,bool warm)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise selected allocation-failure positions in cold insertion and warm cache-hit publication. |
| inputs / outputs | Captures canonical owner/workload facts, measures one successful selection’s replacement-new count N, then faults sampled positions {0, 1, N/2, N-1, …, N-8} after deduplication on fresh two-entry scenarios; it returns attempted-position, publication-failure and completed-after-injection totals. The positions are a sample, not an exhaustive sweep. |
| invariants | After each injected position it checks unchanged owner/proof and old handles; failure must preserve cache counters/FIFO and same-owner retry must return the exact artifact, while a recovered attempt must publish the complete expected result. It does not snapshot or assert query-account current bytes. |
| ownership | The caller-owned owner and fixture outlive the campaign; each loop owns a fresh Scenario whose prior selections remain alive through failure, retry and eviction checks. |
| failure | An injected position can yield allocation_failure or a complete result after recovery; either branch is checked. The function requires at least one late publication failure and throws if not reached. |
| cost | Baseline N is dynamic and guarded to 9..99,999. At most eleven distinct sampled positions are tried, not every fault position. Each position constructs a fresh Scenario (including its two cache-fill selections), then runs one injected selection; only a returned failure triggers two read-only diagnostic hits and a retry. Cold cases also check three FIFO observations; both cold and warm cases reinitialize the retained plan once per position. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [src/planner/selection_cache.cpp](../../../../../src/planner/selection_cache.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0035

[Lines 160–160](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L160); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L160-L160:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_publication_fault_independent_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 161–173](../../../../../tests/unit/selection_publication_fault_independent_test.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both cold and warm independent allocation-publication fault campaigns for C05 selection. |
| inputs / outputs | Requires one repository-root argument, builds the literal Boolean fixture/runtime, commits hot()’s 100 duplicate inserts (90 table-0 R, 5 table-1 S, 5 table-2 T), then calls focused with cold request id 2 (score_bits=502) and warm id 0 (score_bits=500), and prints aggregate counters. Duplicate inserts leave source tuples unchanged while each event advances the owner sequence and workload inputs. |
| invariants | The executable is a source-level acceptance harness; this card records its main path but does not certify that the test was executed. |
| ownership | Fixture and owner are local to main; each returned Scenario/result handle is scoped by focused. |
| failure | A bad argument or failed assertion is caught as std::exception, printed and returned as status 1. |
| cost | Runs fixture construction and two data-dependent fault campaigns; each campaign's selected position set and native selection costs are runtime-calibrated, not fixed by this main. |
| Design | [tests/unit/selection_publication_fault_independent_test.cpp](../../../../../tests/unit/selection_publication_fault_independent_test.cpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp), [src/runtime/selection.cpp](../../../../../src/runtime/selection.cpp), [docs/selection.md](../../../../selection.md) |
