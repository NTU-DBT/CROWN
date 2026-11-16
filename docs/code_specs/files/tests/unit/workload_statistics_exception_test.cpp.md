# `tests/unit/workload_statistics_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/workload_statistics_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2a3e4734a77282a1902b6a8fc36efaa53fcb49a0229cc5ab8f88d6d829352c84`. 132 lines partitioned into 17 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/workload_statistics_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 9–15](../../../../../tests/unit/workload_statistics_exception_test.cpp#L9) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 16–22](../../../../../tests/unit/workload_statistics_exception_test.cpp#L16) | Type/record definition: struct Fault |  · [reviewed contract](#b0003) |
| [B0004 · 23–23](../../../../../tests/unit/workload_statistics_exception_test.cpp#L23) | Closes surrounding scope/type. |  · [reviewed contract](#b0004) |
| [B0005 · 24–24](../../../../../tests/unit/workload_statistics_exception_test.cpp#L24) | Callable definition: void* operator new(std::size_t bytes) | calls allocate; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0005) |
| [B0006 · 25–25](../../../../../tests/unit/workload_statistics_exception_test.cpp#L25) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocate(bytes); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 26–26](../../../../../tests/unit/workload_statistics_exception_test.cpp#L26) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 27–27](../../../../../tests/unit/workload_statistics_exception_test.cpp#L27) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 28–28](../../../../../tests/unit/workload_statistics_exception_test.cpp#L28) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 29–29](../../../../../tests/unit/workload_statistics_exception_test.cpp#L29) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 30–33](../../../../../tests/unit/workload_statistics_exception_test.cpp#L30) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 34–61](../../../../../tests/unit/workload_statistics_exception_test.cpp#L34) | Callable definition: void strong_configure() | calls runtime, plan, delta_options, configure_workload_statistics; guard check(current.options()==previous.options() && current.stamp().reset_generation==previous.stamp().r…; growth insert; 1 loop sites; source comment (unverified): // Disabling releases every slab/route without requesting new allocation. · [reviewed contract](#b0012) |
| [B0013 · 62–90](../../../../../tests/unit/workload_statistics_exception_test.cpp#L62) | Callable definition: void same_owner_update_recovery() | calls runtime, alias_plan, delta_options, configure_workload_statistics; guard check(runtime.owner()==owner && runtime.ready());; growth insert; 1 loop sites; source comment (unverified): // Recovery is an actual subsequent update on the same owner and same · [reviewed contract](#b0013) |
| [B0014 · 91–108](../../../../../tests/unit/workload_statistics_exception_test.cpp#L91) | Callable definition: void nonallocating_commit_abort_and_snapshot_failure() | calls runtime, alias_plan, delta_options, configure_workload_statistics; guard const auto before=runtime.workload_statistics(); check(before.pending() && before.metadata().commit…; growth insert · [reviewed contract](#b0014) |
| [B0015 · 109–126](../../../../../tests/unit/workload_statistics_exception_test.cpp#L109) | Callable definition: void failed_mode_oom() | calls runtime, plan, delta_options, apply; guard check(runtime.ready() && runtime.mode()==DeltaMode::maintenance && runtime.owner()==before.stamp().…; growth insert; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 127–127](../../../../../tests/unit/workload_statistics_exception_test.cpp#L127) | Closes surrounding scope/type. |  · [reviewed contract](#b0016) |
| [B0017 · 128–132](../../../../../tests/unit/workload_statistics_exception_test.cpp#L128) | Callable definition: int main() | calls strong_configure, same_owner_update_recovery, nonallocating_commit_abort_and_snapshot_failure, failed_mode_oom · [reviewed contract](#b0017) |

## B0001

[Lines 1–8](../../../../../tests/unit/workload_statistics_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:4af7cb07e65d6127efd6741675e8908309ea64b4372f7b9812c6f8db23db5b6c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare workload_statistics_exception_test.cpp: include "workload_statistics_fixture.hpp", &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;new&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–15](../../../../../tests/unit/workload_statistics_exception_test.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back the executable's global C++ new/new\[\] with a thread-local fail-after counter and malloc. |
| inputs / outputs | Byte size and fail_after/allocations enter; malloc-backed pointer or std::bad_alloc exits. |
| invariants | At zero it throws before incrementing allocations; positive positions decrement then count the admitted C++ request; direct malloc and syscalls are outside the seam. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One TLS branch/counter plus one malloc on admitted new; no native byte/account total. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 16–22](../../../../../tests/unit/workload_statistics_exception_test.cpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fault {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope one thread-local allocation failure position and restore its previous threshold. |
| inputs / outputs | Position enters; Fault sets fail_after for lifetime and restores previous value at destruction. |
| invariants | Fault is noncopyable so nested/duplicate restoration cannot silently alter the failpoint order. |
| ownership | RAII object borrows only scalar TLS state; it owns no allocation. |
| failure | Constructor/destructor do not allocate or throw; the guard restores injection state during exception unwinding. |
| cost | Two TLS scalar writes; no C++ new request. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0004

[Lines 23–23](../../../../../tests/unit/workload_statistics_exception_test.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L23:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in workload_statistics_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 24–24](../../../../../tests/unit/workload_statistics_exception_test.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar new through the workload OOM seam. |
| inputs / outputs | C++ request size enters; pointer or std::bad_alloc exits. |
| invariants | Scalar and array calls share the thread-local threshold and attempt count. |
| ownership | Returned malloc block is paired with matching delete. |
| failure | Threshold zero throws before malloc; malloc exhaustion also throws. |
| cost | One counter path and at most one malloc; cannot see direct malloc/syscalls. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0006

[Lines 25–25](../../../../../tests/unit/workload_statistics_exception_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array new through the workload OOM seam. |
| inputs / outputs | C++ request size enters; pointer or std::bad_alloc exits. |
| invariants | Scalar and array calls share the thread-local threshold and attempt count. |
| ownership | Returned malloc block is paired with matching delete. |
| failure | Threshold zero throws before malloc; malloc exhaustion also throws. |
| cost | One counter path and at most one malloc; cannot see direct malloc/syscalls. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 26–26](../../../../../tests/unit/workload_statistics_exception_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Delete is noexcept and independent of fail_after. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injection during delete. |
| cost | One free; no allocator/syscall absence claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 27–27](../../../../../tests/unit/workload_statistics_exception_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Delete is noexcept and independent of fail_after. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injection during delete. |
| cost | One free; no allocator/syscall absence claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 28–28](../../../../../tests/unit/workload_statistics_exception_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Delete is noexcept and independent of fail_after. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injection during delete. |
| cost | One free; no allocator/syscall absence claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 29–29](../../../../../tests/unit/workload_statistics_exception_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized array replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | Delete is noexcept and independent of fail_after. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No injection during delete. |
| cost | One free; no allocator/syscall absence claim. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 30–33](../../../../../tests/unit/workload_statistics_exception_test.cpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L33:sha256:798e383017df7c674d3d6c861ea2179491ce8e3798de9fcef34e4a9ef780afaf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare workload_statistics_exception_test.cpp: bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 34–61](../../../../../tests/unit/workload_statistics_exception_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void strong_configure() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep workload collector configuration and verify strong replacement, reset, and disable under global-new failure. |
| inputs / outputs | Starts with committed counters; tries new sampling/detail options across allocation positions, then resets and disables under fail_after=0. |
| invariants | Every configuration bad_alloc preserves old options, generations, cells, owner, sequence and retained payload; success increments configuration generation and clears cells; reset/disable make no covered new calls; disable releases all slabs/routes. |
| ownership | Old Snapshot owns its interval values; runtime owns active collector; candidate configure state remains private until committed. |
| failure | Only global C++ new/new\[\] requests are injected/counted; direct malloc/syscalls are not observed. reset/configure are expected to finish when fail_after=0. |
| cost | Sweeps the collector's finite replacement allocation positions, then fixed reset/disable; memory bytes come from collector account, not new-call count. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 62–90](../../../../../tests/unit/workload_statistics_exception_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void same_owner_update_recovery() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep C++ allocation failure through a real alias update, recover same sequence on the same owner, and erase it. |
| inputs / outputs | Creates generalized alias plan; tries one tagged insert at every global-new position; on failure retries the same physical update and then cleans up with erase. |
| invariants | Failed attempt leaves owner/ready/sequence/cells/source rows unchanged; staged detail may increase only attempt metadata; a fresh call on the same owner/sequence succeeds; final erase returns source set empty. |
| ownership | Runtime owns source/collector state; before/after workload Snapshots own copied cells; update Row is local. |
| failure | Only global new/new\[\] bad_alloc is injected; direct malloc, MemoryAccount, and syscalls are not faulted. Failure recovery is required at every encountered failpoint. |
| cost | Per failpoint performs one physical update and full snapshot/invariant checks; up to 2048 positions, followed by recovery/erase. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 91–108](../../../../../tests/unit/workload_statistics_exception_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void nonallocating_commit_abort_and_snapshot_failure() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove selected transaction finish/rollback paths make no covered C++ new calls and snapshot copying can fail without mutation. |
| inputs / outputs | Prepares/drains pending insert; counts global-new calls through commit and rollback at fail_after=0; injects snapshot failure then retries. |
| invariants | Commit publishes exactly once with no new request; rollback preserves sequence and committed cells with no new request; snapshot bad_alloc leaves collector cells unchanged and a later snapshot succeeds. |
| ownership | Pending ticket and output are local; committed snapshots own cell copies; runtime owns collector. |
| failure | Global-new seam throws if guarded commit/rollback tries allocation; snapshot is expected to throw bad_alloc at its first request; direct malloc/syscalls remain outside the claim. |
| cost | Two guarded finish operations and two snapshots; this only proves no replacement global-new request on those covered paths, not zero heap or syscalls. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0015

[Lines 109–126](../../../../../tests/unit/workload_statistics_exception_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failed_mode_oom() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep a maintenance-to-delta mode transition and verify failed bootstrap preserves the old interval. |
| inputs / outputs | Builds a maintenance runtime, commits base rows, configures counters, commits one more row, then injects global-new failures into set_mode(delta). |
| invariants | Every failure leaves runtime ready/in maintenance with same owner, segment, modes, cells and no previous interval; success creates next segment, rotates old committed counters into previous and clears current. |
| ownership | Before Snapshot owns old interval; runtime owns current and previous collector slabs. |
| failure | Only global new/new\[\] bad_alloc is injected; other transition errors propagate; does not sweep direct malloc/syscalls. |
| cost | Mode transition rebuilds bounded state at each failure position; loop capped 2048, not a timing benchmark. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0016

[Lines 127–127](../../../../../tests/unit/workload_statistics_exception_test.cpp#L127); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L127:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in workload_statistics_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/workload_statistics_exception_test.cpp](../../../../../tests/unit/workload_statistics_exception_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 128–132](../../../../../tests/unit/workload_statistics_exception_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run configuration, same-owner update, nonallocating transaction finish, and mode-transition failure groups. |
| inputs / outputs | No input; invokes four named groups and reports their failure counts. |
| invariants | The main aggregates assertions only; all OOM handling and post-failure recovery is in called groups. |
| ownership | Each runtime and saved Snapshot is local; no report data is retained globally. |
| failure | Unexpected failures propagate and fail the test. |
| cost | Runs finite failure-frontier sweeps up to 2048 positions; these are exception-safety checks, not process-wide allocation or syscall evidence. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
