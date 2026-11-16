# `tests/unit/statistics_explain_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/statistics_explain_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `9b0e9f15cd5950c43bf09078514255631b78e368b72ca94ed1107b615847f638`. 48 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/statistics_explain_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../tests/unit/statistics_explain_exception_test.cpp#L8) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t n) | calls std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../tests/unit/statistics_explain_exception_test.cpp#L9) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 10–10](../../../../../tests/unit/statistics_explain_exception_test.cpp#L10) | Callable definition: void* operator new(std::size_t n) | calls fault::allocate; returns fault::allocate(n); growth allocate, new · [reviewed contract](#b0004) |
| [B0005 · 11–11](../../../../../tests/unit/statistics_explain_exception_test.cpp#L11) | Callable definition: void* operator new\[\](std::size_t n) | calls ; returns fault::allocate(n); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 12–12](../../../../../tests/unit/statistics_explain_exception_test.cpp#L12) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0006) |
| [B0007 · 13–13](../../../../../tests/unit/statistics_explain_exception_test.cpp#L13) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0007) |
| [B0008 · 14–14](../../../../../tests/unit/statistics_explain_exception_test.cpp#L14) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 15–15](../../../../../tests/unit/statistics_explain_exception_test.cpp#L15) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 16–16](../../../../../tests/unit/statistics_explain_exception_test.cpp#L16) | declares namespace scope; declares aliases. |  · [reviewed contract](#b0010) |
| [B0011 · 17–27](../../../../../tests/unit/statistics_explain_exception_test.cpp#L17) | Callable definition: template&lt;class Operation,class Verify&gt;void sweep(const char* label,Operation operation,Verify verify) | calls operation, verify, check; guard check(completed && failures&gt;0);std::cout&lt;&lt;label&lt;&lt;" injected failures="&lt;&lt;failures&lt;&lt;'\n';; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 28–48](../../../../../tests/unit/statistics_explain_exception_test.cpp#L28) | Callable definition: int main() | calls plan, database, requested, wf::delta_options; guard const auto verify=\[&\]{check(runtime.owner()==owner && runtime.sequence()==1 && runtime.canonical_st…; growth insert · [reviewed contract](#b0012) |

## B0001

[Lines 1–7](../../../../../tests/unit/statistics_explain_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:bf441df78eab20c4fa4330c8d32b2fee96969b3a1856e155ba9484f416833b81
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_explain_exception_test.cpp: include "statistics_report_fixture.hpp", &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;new&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/statistics_explain_exception_test.cpp](../../../../../tests/unit/statistics_explain_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–8](../../../../../tests/unit/statistics_explain_exception_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t n){if(active){if(remaining==0)throw std::bad_alloc{};--remaining;}if(auto* p=std::malloc(n?n:1))return p;throw std::bad_alloc{};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back report capture/export replacement new with thread-local fail-after state. |
| inputs / outputs | C++ allocation size and thread-local active/remaining enter; malloc-backed pointer or std::bad_alloc exits. |
| invariants | Fault state is per thread and only affects global new/new\[\] requests while active; direct malloc and syscalls are not observed. |
| ownership | The seam owns no report/runtime objects; allocated pointer is paired with the matching delete. |
| failure | Zero remaining throws before malloc; malloc failure also throws. |
| cost | Counter branch and one malloc for an admitted request; not a universal heap tracer. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 9–9](../../../../../tests/unit/statistics_explain_exception_test.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L9:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in statistics_explain_exception_test.cpp: namespace fault. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/statistics_explain_exception_test.cpp](../../../../../tests/unit/statistics_explain_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 10–10](../../../../../tests/unit/statistics_explain_exception_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return fault::allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar new through the report allocation fault seam. |
| inputs / outputs | C++ byte size enters; pointer or std::bad_alloc exits. |
| invariants | Both overloads share the thread-local position and caller operation. |
| ownership | No ownership escapes beyond returned malloc storage. |
| failure | Injected new failure throws std::bad_alloc; direct malloc paths are outside the counter. |
| cost | One seam call and at most one malloc. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 11–11](../../../../../tests/unit/statistics_explain_exception_test.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n){return fault::allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array new through the report allocation fault seam. |
| inputs / outputs | C++ byte size enters; pointer or std::bad_alloc exits. |
| invariants | Both overloads share the thread-local position and caller operation. |
| ownership | No ownership escapes beyond returned malloc storage. |
| failure | Injected new failure throws std::bad_alloc; direct malloc paths are outside the counter. |
| cost | One seam call and at most one malloc. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 12–12](../../../../../tests/unit/statistics_explain_exception_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no result exits. |
| invariants | Delete overloads are noexcept and do not consult active fault state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injected failure occurs during delete. |
| cost | One free call; does not prove cleanup has no other system effects. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 13–13](../../../../../tests/unit/statistics_explain_exception_test.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage. |
| inputs / outputs | Pointer enters; no result exits. |
| invariants | Delete overloads are noexcept and do not consult active fault state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injected failure occurs during delete. |
| cost | One free call; does not prove cleanup has no other system effects. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 14–14](../../../../../tests/unit/statistics_explain_exception_test.cpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no result exits. |
| invariants | Delete overloads are noexcept and do not consult active fault state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injected failure occurs during delete. |
| cost | One free call; does not prove cleanup has no other system effects. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 15–15](../../../../../tests/unit/statistics_explain_exception_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized array replacement-new storage. |
| inputs / outputs | Pointer enters; no result exits. |
| invariants | Delete overloads are noexcept and do not consult active fault state. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injected failure occurs during delete. |
| cost | One free call; does not prove cleanup has no other system effects. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 16–16](../../../../../tests/unit/statistics_explain_exception_test.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L16:sha256:19d8b6cee0a1ae0e1c8fc431db05eecb68ee9032113f595b54ebf618ea50eec3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_explain_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/statistics_explain_exception_test.cpp](../../../../../tests/unit/statistics_explain_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 17–27](../../../../../tests/unit/statistics_explain_exception_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Operation,class Verify>void sweep(const char* label,Operation operation,Verify verify){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Repeat an operation with a global-new failpoint at every position, then verify retained state and rerun recovery. |
| inputs / outputs | Label, operation callable, and verifier enter; sweeps positions 0..2047; prints failure count on success. |
| invariants | Each bad_alloc disables fault before verification; verifier runs and operation is rerun after every attempted position; requires at least one failure and eventual completion. |
| ownership | Callable/verify closures borrow runtime/report/session state; any produced report must own its own data and is discarded by caller. |
| failure | Only replacement C++ new/new\[\] allocation failures are injected. Failpoint is disabled for verification/recovery; malloc/syscall faults are outside scope. |
| cost | Repeats operation and verifier for each failpoint up to the first success; exact work depends on serializer/capture object size. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 28–48](../../../../../tests/unit/statistics_explain_exception_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep actual-owner report capture, bounded JSON/text export, and guarded private-session report capture. |
| inputs / outputs | Builds DeltaRuntime and committed prior report, rotates mode segment, serializes retained report, snapshots canonical state; then builds pending QuerySession report and executes four sweeps. |
| invariants | Every injected failure leaves owner/sequence/canonical runtime and retained encoding stable; recovery report matches literal facts/workload snapshot; pending session report stays identical until stop/drop; dropped owner cannot create combined report while retained pending report still exports. |
| ownership | Retained reports own all serialized facts; closures borrow runtime/session/report only during operation and verification; dropped session is separate from report lifetime. |
| failure | Each sweep accepts only global new/new\[\] bad_alloc; the private pending operation is session-guarded; stop/drop transitions are outside injection. No direct malloc/syscall coverage. |
| cost | Four failpoint sweeps repeatedly capture or encode reports and verify full encodings; report-sized cost, not benchmark. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [Refactor.md](../../../../../Refactor.md) |
