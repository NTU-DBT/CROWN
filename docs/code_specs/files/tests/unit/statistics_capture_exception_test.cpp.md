# `tests/unit/statistics_capture_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/statistics_capture_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8a17810deec37a5d509724302864a04b4e93334261c842a740fdcfa1634106cc`. 59 lines partitioned into 11 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/statistics_capture_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../tests/unit/statistics_capture_exception_test.cpp#L9) | Callable definition: void* allocate(std::size_t n) | calls std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 14–14](../../../../../tests/unit/statistics_capture_exception_test.cpp#L14) | Callable definition: void check(bool b) | calls std::runtime_error; guard void check(bool b){if(!b)throw std::runtime_error("capture allocation exception assertion");} · [reviewed contract](#b0003) |
| [B0004 · 15–15](../../../../../tests/unit/statistics_capture_exception_test.cpp#L15) | Closes surrounding scope/type. |  · [reviewed contract](#b0004) |
| [B0005 · 16–16](../../../../../tests/unit/statistics_capture_exception_test.cpp#L16) | Callable definition: void* operator new(std::size_t n) | calls allocate; returns allocate(n); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 17–17](../../../../../tests/unit/statistics_capture_exception_test.cpp#L17) | Callable definition: void* operator new\[\](std::size_t n) | calls ; returns allocate(n); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 18–18](../../../../../tests/unit/statistics_capture_exception_test.cpp#L18) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 19–19](../../../../../tests/unit/statistics_capture_exception_test.cpp#L19) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 20–20](../../../../../tests/unit/statistics_capture_exception_test.cpp#L20) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 21–21](../../../../../tests/unit/statistics_capture_exception_test.cpp#L21) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 22–59](../../../../../tests/unit/statistics_capture_exception_test.cpp#L22) | Callable definition: int main() | calls insert, tuple, std::string, add_index; guard check(captured.distribution.completion==stats::Completion::exact && captured.distribution.ndv==3);; growth insert; 3 loop sites; source comment (unverified): // Each k fails the kth allocation in the SAME unchanged owner. The first · [reviewed contract](#b0011) |

## B0001

[Lines 1–8](../../../../../tests/unit/statistics_capture_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:56f5b8cd4e5e746cc213efc971e09b777c51dbd6097ffc0385e54571e8118c29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_capture_exception_test.cpp: include "crown/runtime/statistics.hpp", &lt;cstdlib&gt;, &lt;new&gt;, &lt;stdexcept&gt;, &lt;iostream&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/statistics_capture_exception_test.cpp](../../../../../tests/unit/statistics_capture_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–13](../../../../../tests/unit/statistics_capture_exception_test.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t n) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back global C++ allocation operators with malloc and fail the configured new request. |
| inputs / outputs | Allocation size and active fail-after counter enter; allocated pointer or std::bad_alloc exits. |
| invariants | The seam counts only calls routed through replacement global new/new\[\] while injecting; direct malloc remains unobserved. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One counter update plus one malloc when admitted; not a general heap/syscall tracer. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 14–14](../../../../../tests/unit/statistics_capture_exception_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool b){if(!b)throw std::runtime_error("capture allocation exception assertion");}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a storage-capture test assertion failure. |
| inputs / outputs | Boolean enters; normal return or std::runtime_error exits. |
| invariants | The check does not catch production Error or allocator failure. |
| ownership | No stored references; exception owns its message. |
| failure | False throws std::runtime_error; expected crown::Error is handled separately by error(). |
| cost | One branch; only failure constructs exception storage. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 15–15](../../../../../tests/unit/statistics_capture_exception_test.cpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in statistics_capture_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/statistics_capture_exception_test.cpp](../../../../../tests/unit/statistics_capture_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 16–16](../../../../../tests/unit/statistics_capture_exception_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar new through the storage-capture failpoint. |
| inputs / outputs | C++ allocation size enters; pointer or bad_alloc exits. |
| invariants | Scalar and array requests use the same position counter. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One seam call and at most one malloc. Direct malloc/syscall activity is outside the seam. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 17–17](../../../../../tests/unit/statistics_capture_exception_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array new through the storage-capture failpoint. |
| inputs / outputs | C++ allocation size enters; pointer or bad_alloc exits. |
| invariants | Scalar and array requests use the same position counter. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One seam call and at most one malloc. Direct malloc/syscall activity is outside the seam. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 18–18](../../../../../tests/unit/statistics_capture_exception_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Free is noexcept and independent of injection state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases storage from this executable's replacement new. |
| cost | One free call; does not certify allocator or OS behavior. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 19–19](../../../../../tests/unit/statistics_capture_exception_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Free is noexcept and independent of injection state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases storage from this executable's replacement new. |
| cost | One free call; does not certify allocator or OS behavior. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 20–20](../../../../../tests/unit/statistics_capture_exception_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Free is noexcept and independent of injection state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases storage from this executable's replacement new. |
| cost | One free call; does not certify allocator or OS behavior. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 21–21](../../../../../tests/unit/statistics_capture_exception_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized array replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Free is noexcept and independent of injection state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases storage from this executable's replacement new. |
| cost | One free call; does not certify allocator or OS behavior. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 22–59](../../../../../tests/unit/statistics_capture_exception_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep storage projection and index capture through every global C++ new failure position on the same unchanged ReferenceTable. |
| inputs / outputs | Builds a 7-row table with three unique binary string keys, adds a projected index, and repeats projection/index capture with a fresh Budget at each failpoint. |
| invariants | Each injected failure leaves table owner, revision, snapshot and invariants unchanged; baseline exact index distribution remains valid; uninstrumented recovery reproduces NDV/histogram; first successful failpoint proves all earlier positions were visited. |
| ownership | ReferenceTable owns source rows/index; baseline/captured distribution owns copied keys, while each trial's temporary capture dies before the next iteration. |
| failure | Only global new/new\[\] bad_alloc is injected. It is not a native MemoryAccount or arbitrary malloc/syscall fault sweep. |
| cost | Per failpoint traverses fixed seven rows or indexed keys, then recaptures for recovery; no timing claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md), [Refactor.md](../../../../../Refactor.md) |
