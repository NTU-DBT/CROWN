# `tests/unit/owner_statistics_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/owner_statistics_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8026b8407d8ccf5e9312ffe0ee4c91f6c9a2dab1017bfe3939e9a4d6e21bc209`. 61 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/unit/owner_statistics_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 7–11](../../../../../tests/unit/owner_statistics_exception_test.cpp#L7) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t n) | calls std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 12–12](../../../../../tests/unit/owner_statistics_exception_test.cpp#L12) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 13–13](../../../../../tests/unit/owner_statistics_exception_test.cpp#L13) | Callable definition: void* operator new(std::size_t n) | calls allocate; returns allocate(n); growth allocate, new · [reviewed contract](#b0004) |
| [B0005 · 14–14](../../../../../tests/unit/owner_statistics_exception_test.cpp#L14) | Callable definition: void* operator new\[\](std::size_t n) | calls ; returns allocate(n); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 15–15](../../../../../tests/unit/owner_statistics_exception_test.cpp#L15) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0006) |
| [B0007 · 16–16](../../../../../tests/unit/owner_statistics_exception_test.cpp#L16) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 17–17](../../../../../tests/unit/owner_statistics_exception_test.cpp#L17) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 18–18](../../../../../tests/unit/owner_statistics_exception_test.cpp#L18) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 19–19](../../../../../tests/unit/owner_statistics_exception_test.cpp#L19) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0010) |
| [B0011 · 20–35](../../../../../tests/unit/owner_statistics_exception_test.cpp#L20) | Callable definition: template&lt;class Runtime&gt; std::size_t sweep(Runtime& runtime,const stats::OwnerRequest& request) | calls canonical_state, owner, sequence, capture_statistics; guard check(runtime.owner()==owner && runtime.sequence()==seq && runtime.canonical_state()==before);; returns failures; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 36–48](../../../../../tests/unit/owner_statistics_exception_test.cpp#L36) | Callable definition: std::size_t copy_sweep(const stats::OwnerCapture& before,const stats::OwnerCapture& after) | calls same_facts, check, stamp; guard if(succeeded){same_facts(target,after);check(target.stamp().sequence==after.stamp().sequence);break…; returns failures; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 49–61](../../../../../tests/unit/owner_statistics_exception_test.cpp#L49) | Callable definition: int main() | calls plan, request, PhysicalRuntime::initialize, database; growth insert · [reviewed contract](#b0013) |

## B0001

[Lines 1–6](../../../../../tests/unit/owner_statistics_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:db5cd8d4fa52e5d53ec61068462799308d8a37d50e6dd3e479e90377f8eaffe2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owner_statistics_exception_test.cpp: include "owner_statistics_fixture.hpp", &lt;cstdlib&gt;, &lt;new&gt;, &lt;iostream&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–11](../../../../../tests/unit/owner_statistics_exception_test.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t n){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back the executable's replacement global C++ new/new\[\] with malloc and a fail-after counter. |
| inputs / outputs | Byte size and thread-local injection state enter; malloc-backed pointer or std::bad_alloc exits. |
| invariants | Only active injected requests advance allocations/remaining; zero remaining throws before the malloc attempt; zero bytes are normalized to one. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One counter path plus one malloc for an admitted request; direct malloc/syscalls from other code are not counted. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 12–12](../../../../../tests/unit/owner_statistics_exception_test.cpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L12:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in owner_statistics_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 13–13](../../../../../tests/unit/owner_statistics_exception_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar new calls through the owner-capture exception seam. |
| inputs / outputs | Scalar C++ allocation size enters; pointer or std::bad_alloc exits. |
| invariants | Uses the shared failpoint counter so capture and copy allocation frontiers are ordered in one sweep. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One seam and at most one malloc; no native request-byte total is measured here. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 14–14](../../../../../tests/unit/owner_statistics_exception_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array new\[\] calls through the owner-capture exception seam. |
| inputs / outputs | Array C++ allocation size enters; pointer or std::bad_alloc exits. |
| invariants | Array and scalar requests share the same injection position. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One seam and at most one malloc; direct allocation APIs remain invisible. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 15–15](../../../../../tests/unit/owner_statistics_exception_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar replacement-new storage through its matching delete overload. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The overload is noexcept and does not consult failpoint state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept; no injection occurs during cleanup. |
| cost | One free call; release cost is not evidence that all heap or syscall activity is absent. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 16–16](../../../../../tests/unit/owner_statistics_exception_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array replacement-new storage through its matching delete overload. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The overload is noexcept and does not consult failpoint state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept; no injection occurs during cleanup. |
| cost | One free call; release cost is not evidence that all heap or syscall activity is absent. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 17–17](../../../../../tests/unit/owner_statistics_exception_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized scalar replacement-new storage through its matching delete overload. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The overload is noexcept and does not consult failpoint state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept; no injection occurs during cleanup. |
| cost | One free call; release cost is not evidence that all heap or syscall activity is absent. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 18–18](../../../../../tests/unit/owner_statistics_exception_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized array replacement-new storage through its matching delete overload. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The overload is noexcept and does not consult failpoint state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | Deallocation is noexcept; no injection occurs during cleanup. |
| cost | One free call; release cost is not evidence that all heap or syscall activity is absent. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 19–19](../../../../../tests/unit/owner_statistics_exception_test.cpp#L19); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L19-L19:sha256:94d285ae3d5d306a1596dbd4c4ac0c43f2c151b16c17b61492fd0a209643c830
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owner_statistics_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/owner_statistics_exception_test.cpp](../../../../../tests/unit/owner_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 20–35](../../../../../tests/unit/owner_statistics_exception_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Runtime> std::size_t sweep(Runtime& runtime,const stats::OwnerRequest& request){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep owner-capture failures for PhysicalRuntime and SupportRuntime, then owning assignment across a committed update. |
| inputs / outputs | Creates a shared eight-selection request; sweeps each C++ new failpoint on a physical owner and a populated support owner; captures before and after a physical S insert for copy assignment. |
| invariants | Every failed capture preserves canonical state, owner, sequence, report freshness and invariants; recovery capture equals the baseline. Failed assignment leaves target facts/stamp/owner intact; successful assignment equals after report. |
| ownership | Reports own keys/layout/plan; copy target owns prior value until assignment succeeds. Runtime state remains owned separately by each local runtime. |
| failure | Only global C++ new/new\[\] failure is injected and caught as bad_alloc. It does not fault malloc, native MemoryAccount admission, or syscalls. |
| cost | Repeats full state scans and literal map comparisons at every failpoint for two layers, plus a deep report copy sweep; it is recovery/strong-guarantee evidence rather than a timing run. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 36–48](../../../../../tests/unit/owner_statistics_exception_test.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t copy_sweep(const stats::OwnerCapture& before,const stats::OwnerCapture& after){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep copy assignment from a prior OwnerCapture into a report with a later committed sequence. |
| inputs / outputs | Borrowed before/after captures enter; failpoints replace target assignment until success; returns number of injected bad_alloc failures. |
| invariants | On each failure, the target still matches before facts, stamp owner, and sequence; on success it matches after facts and sequence. Requires at least one failure and a later successful assignment. |
| ownership | Before and after inputs are borrowed; target owns a copy independent of both arguments. |
| failure | Uses global new/new\[\] fail injection only; catches bad_alloc. On an unexpected exception the seam is disabled and the exception propagates. |
| cost | Per attempt first copies before, then assignment allocates the target value; one allocation position per iteration, up to 1024, no report scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 49–61](../../../../../tests/unit/owner_statistics_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise owner capture OOM recovery for both physical and support owners and strong report assignment. |
| inputs / outputs | Creates one physical runtime at epoch 0, captures after support-only updates, then advances physical runtime and runs copy_sweep. |
| invariants | Main's checks are delegated to sweep/copy_sweep; the cross-owner layer output keeps the actual SupportOwnerId/sequence and copied report identity. |
| ownership | All runtimes and three reports are local owning values; no report borrows runtime storage after capture. |
| failure | Unexpected bad_alloc outside an active sweep or any invariant mismatch escapes and fails the process. |
| cost | Performs three bounded allocation-position sweeps with repeated canonical-state checks; no timing or all-allocator failure guarantee. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |
