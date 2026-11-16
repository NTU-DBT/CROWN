# `tests/unit/statistics_collection_test.cpp` — block usage map

[Source](../../../../../tests/unit/statistics_collection_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a3d5c8c15f02fb1ac2586f6626bddd85a7c86310ec6f5cb1c34576a0a81e3367`. 171 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/statistics_collection_test.cpp#L1) | Imports dependencies; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 8–12](../../../../../tests/unit/statistics_collection_test.cpp#L8) | Type/record definition: struct CollectorTestAccess |  · [reviewed contract](#b0002) |
| [B0003 · 13–17](../../../../../tests/unit/statistics_collection_test.cpp#L13) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 18–24](../../../../../tests/unit/statistics_collection_test.cpp#L18) | Callable definition: void* allocate(std::size_t n) | calls std::bad_alloc, std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0004) |
| [B0005 · 25–32](../../../../../tests/unit/statistics_collection_test.cpp#L25) | declares values/defaults or compile-time conditions. | growth insert · [reviewed contract](#b0005) |
| [B0006 · 33–33](../../../../../tests/unit/statistics_collection_test.cpp#L33) | Callable definition: Options enabled() | calls ; returns o · [reviewed contract](#b0006) |
| [B0007 · 34–50](../../../../../tests/unit/statistics_collection_test.cpp#L34) | Callable definition: void transactions() | calls configure, enabled, begin, nest; guard c.degree(2,5); assert(c.finish(n,true));; source comment (unverified): // stale same-depth ticket · [reviewed contract](#b0007) |
| [B0008 · 51–64](../../../../../tests/unit/statistics_collection_test.cpp#L51) | Callable definition: void sampling_and_noops() | calls enabled, configure, begin, degree; guard assert(c.metadata().attempts==10 && c.metadata().selected==3);; 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 65–81](../../../../../tests/unit/statistics_collection_test.cpp#L65) | Callable definition: void truncation_and_invalid() | calls enabled, configure, begin, degree; guard assert(c.finish(r,true));; source comment (unverified): // wrong initiating op · [reviewed contract](#b0009) |
| [B0010 · 82–105](../../../../../tests/unit/statistics_collection_test.cpp#L82) | Callable definition: void histogram_and_support() | calls configure, enabled, begin, degree; guard c.occurrence(4,true); c.occurrence(4,false); assert(c.finish(r,true));; 1 loop sites; source comment (unverified): // Independent expected bin boundaries: every representable power of two · [reviewed contract](#b0010) |
| [B0011 · 106–126](../../../../../tests/unit/statistics_collection_test.cpp#L106) | Callable definition: void lifecycle_memory_and_allocations() | calls assert, memory, begin, degree; guard Collector c; assert(c.memory().retained_payload_bytes==0); · [reviewed contract](#b0011) |
| [B0012 · 127–138](../../../../../tests/unit/statistics_collection_test.cpp#L127) | Callable definition: void saturation_boundaries() | calls enabled, configure, begin, degree; guard auto r=c.begin(0,true); c.degree(2,2); c.degree(2,3); assert(c.finish(r,true)); · [reviewed contract](#b0012) |
| [B0013 · 139–160](../../../../../tests/unit/statistics_collection_test.cpp#L139) | Callable definition: void configuration_faults() | calls configure, enabled, begin, assert; guard auto r=c.begin(0,true); assert(c.finish(r,true));; 1 loop sites; source comment (unverified): // Four independent allocation positions: descriptor vector and three slabs. · [reviewed contract](#b0013) |
| [B0014 · 161–161](../../../../../tests/unit/statistics_collection_test.cpp#L161) | Closes surrounding scope/type. |  · [reviewed contract](#b0014) |
| [B0015 · 162–162](../../../../../tests/unit/statistics_collection_test.cpp#L162) | Callable definition: void* operator new(std::size_t n) | calls allocate; returns allocate(n); growth allocate, new · [reviewed contract](#b0015) |
| [B0016 · 163–163](../../../../../tests/unit/statistics_collection_test.cpp#L163) | Callable definition: void* operator new\[\](std::size_t n) | calls ; returns allocate(n); growth allocate, new · [reviewed contract](#b0016) |
| [B0017 · 164–164](../../../../../tests/unit/statistics_collection_test.cpp#L164) | Callable definition: void operator delete(void* p) noexcept | calls std::free · [reviewed contract](#b0017) |
| [B0018 · 165–165](../../../../../tests/unit/statistics_collection_test.cpp#L165) | Callable definition: void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0018) |
| [B0019 · 166–166](../../../../../tests/unit/statistics_collection_test.cpp#L166) | Callable definition: void operator delete(void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0019) |
| [B0020 · 167–167](../../../../../tests/unit/statistics_collection_test.cpp#L167) | Callable definition: void operator delete\[\](void* p,std::size_t) noexcept | calls  · [reviewed contract](#b0020) |
| [B0021 · 168–171](../../../../../tests/unit/statistics_collection_test.cpp#L168) | Callable definition: int main() | calls transactions, sampling_and_noops, truncation_and_invalid, histogram_and_support · [reviewed contract](#b0021) |

## B0001

[Lines 1–7](../../../../../tests/unit/statistics_collection_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:dfd48e7b881a972799a7f379cf94c82f5d1c4d80d6d89f350640efea9fd244ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_collection_test.cpp: include "statistics_collection.hpp", &lt;cassert&gt;, &lt;cstdlib&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;stdexcept&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–12](../../../../../tests/unit/statistics_collection_test.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CollectorTestAccess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow tests to seed Collector's private generation, ordinal, and attempt counters at uint64 maxima. |
| inputs / outputs | CollectorTestAccess methods take a mutable Collector; no value exits. |
| invariants | Only test friend access changes generation/ordinal/attempt count; no production accessor or runtime path is invoked. |
| ownership | Mutates only the supplied local Collector by reference; no collector pointer or ticket escapes. |
| failure | No expected failure; test preconditions require an enabled/configured local Collector. |
| cost | Three scalar assignments. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 13–17](../../../../../tests/unit/statistics_collection_test.cpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L17:sha256:c7f22a1c6ef1c3fc8ce9fe0f1d55b6acad6f053d05686e4ca8952928ba7fb90e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_collection_test.cpp: bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 18–24](../../../../../tests/unit/statistics_collection_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t n) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back the collector configuration and no-allocation-path test with a fail-after global new shim. |
| inputs / outputs | Requested size and fail_after enter; malloc-backed pointer or std::bad_alloc exits; successful attempt count increments. |
| invariants | Only replacement C++ new requests are counted; fail_after zero remains active until reset by the harness. |
| ownership | No collector state is referenced by allocator seam. |
| failure | At zero, throws std::bad_alloc before malloc; backing malloc failure also throws. Used only to inject failure in C++ allocation requests; no claim about syscalls or all heap activity. |
| cost | One counter check plus one malloc for admitted C++ new; direct malloc/syscall not instrumented. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0005

[Lines 25–32](../../../../../tests/unit/statistics_collection_test.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L32:sha256:a7b7cb5edf7e6073289ba349ef3662d5a5d3742d93a784d2d9c919d50930dc42
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_collection_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 33–33](../../../../../tests/unit/statistics_collection_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Options enabled() { Options o; o.mode=Mode::counters; return o; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an enabled counters-mode Collector Options value. |
| inputs / outputs | No input; Options exits with mode=counters. |
| invariants | Other Options fields keep their default values; descriptor capacity is checked by configure. |
| ownership | Returned value owns only scalar options. |
| failure | No expected exception. |
| cost | Fixed-size options construction. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0007

[Lines 34–50](../../../../../tests/unit/statistics_collection_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void transactions() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify nested collector ticket commit/abort protocol and stale-ticket rejection. |
| inputs / outputs | Configures six descriptors; admits outer and nested update tickets; records degree values; completes and aborts nested/root transactions, retries same-depth stale tickets. |
| invariants | Nested success remains private until outer finish; abort discards staged cells; invalid/stale ticket sequences report false and leave no pending transaction; committed degree sum stays 5. |
| ownership | Collector owns descriptor/slab state; tickets are local scalar tokens; no runtime rows are involved. |
| failure | No expected thrown error; each protocol failure is reported by false return and asserted. |
| cost | Fixed descriptor/cell vectors plus a bounded set of ticket/action calls. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0008

[Lines 51–64](../../../../../tests/unit/statistics_collection_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sampling_and_noops() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check deterministic systematic sampling, no-op input denominators, and reset. |
| inputs / outputs | Period=3, offset=1; ten logical attempts include a nonselected/no-change event and one abort; then reset and one no-op. |
| invariants | Attempts=10, selected=3, complete=2, aborted_selected=1; all physical inputs/noops/changes publish independently; detail from aborted work is absent; reset clears prior cells. |
| ownership | Collector owns current cells and options; local tickets/counters live for this test only. |
| failure | Invalid operations are captured through protocol return values; no allocator fault is injected here. |
| cost | Ten fixed attempts and one reset over six cells; no clock or wall-time dependency. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0009

[Lines 65–81](../../../../../tests/unit/statistics_collection_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void truncation_and_invalid() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check per-attempt detail truncation, invalid descriptor/protocol flags, wrong-operation routing, and zero detail budget. |
| inputs / outputs | Configures detail_budget=2 and submits support/degree actions, invalid indices/operation pairings, noop detail, then reconfigures with zero budget. |
| invariants | A truncated selected attempt publishes no partial detail but keeps exact physical changed/noop counters; invalid/protocol metadata is explicit; wrong initiating operation leaves unrelated cell untouched. |
| ownership | Collector retains descriptor and slabs; all ticket/action inputs are scalar test values. |
| failure | Invalid descriptor and protocol conditions set metadata/false return rather than throwing; invalid Options are checked by configure elsewhere. |
| cost | Bounded number of detail actions with fixed descriptor cells. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0010

[Lines 82–105](../../../../../tests/unit/statistics_collection_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void histogram_and_support() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check logarithmic degree/support histograms, repeated event multiplicity, and saturating counter merge. |
| inputs / outputs | Records degree values 0..4 including repeat 4; support transitions 0-&gt;2, 2-&gt;3, 3-&gt;1, 1-&gt;0 and unchanged zero; occurrence accepted/rejected. |
| invariants | Every input event contributes separately; changed support observes after-value including zero; power-of-two boundaries start new bins; sums/counts clamp and mark saturated at UINT64_MAX. |
| ownership | Mutates collector-owned cells only; test Cell locals own no dynamic data. |
| failure | Saturation is represented in Cell flags/capped counters; no exception is expected. |
| cost | Six degree, five support, two occurrence observations and fixed boundary loop through bin 64. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0011

[Lines 106–126](../../../../../tests/unit/statistics_collection_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifecycle_memory_and_allocations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check collector slab memory accounting, history rotation, reset, disable, and selected no-new operations. |
| inputs / outputs | Starts disabled, configures descriptors, runs nested transaction/rotate/reset under fail_after=0, then disables. |
| invariants | Disabled collector retains zero payload; enabled memory equals descriptor/current/attempt/previous capacity totals; rotate preserves prior snapshot then replaces history; reset increments generation and clears cells; covered new count does not increase during commit/abort/rotate/reset. |
| ownership | Collector owns descriptor/cell vectors; previous/current views are read while collector is alive. |
| failure | Global new injector fails if a covered allocation is attempted; this only proves no covered C++ new call in the guarded paths, not no malloc/syscall/heap activity. |
| cost | Reads capacity accounting and executes fixed slab swaps/counter operations; cleanup deallocates retained slabs outside guarded no-new assertion. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0012

[Lines 127–138](../../../../../tests/unit/statistics_collection_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void saturation_boundaries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed counter/generation maxima and verify saturation and ordinal exhaustion recovery. |
| inputs / outputs | Uses detail_actions=2, then sets generation/attempt/ordinal to UINT64_MAX and performs reset/begin/finish calls. |
| invariants | Generation/metadata saturates instead of wrapping; exhausted ordinal returns serial 0 and no pending ticket; reset restores ability to admit a new root ticket. |
| ownership | Test access mutates private counters in a local Collector; tickets and cells are owned by that collector. |
| failure | Exhaustion is observable flags/false ticket completion; no exception expected. |
| cost | Fixed max-boundary assignments and a few collector calls. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0013

[Lines 139–160](../../../../../tests/unit/statistics_collection_test.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void configuration_faults() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep the four expected Collector::configure allocations and verify strong replacement semantics. |
| inputs / outputs | Starts with a committed cell; injects at descriptor vector and three slab positions, then tries invalid period, max_cells, duplicate descriptor and orphan descriptor. |
| invariants | Every allocation failure preserves previous generation, committed input, and retained-byte total; validation errors preserve the same old configuration; a final valid configure increments generation once. |
| ownership | Collector owns old vectors throughout failed configure; candidate configuration allocations roll back before return. |
| failure | Catches std::bad_alloc for injected global new requests, invalid_argument/length_error for invalid configs; this harness does not fault direct malloc or syscalls. |
| cost | Four targeted allocation-frontier runs plus validation/reconfigure checks over six descriptors/cells. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md) |

## B0014

[Lines 161–161](../../../../../tests/unit/statistics_collection_test.cpp#L161); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L161-L161:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in statistics_collection_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/statistics_collection_test.cpp](../../../../../tests/unit/statistics_collection_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 162–162](../../../../../tests/unit/statistics_collection_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n) { return allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar C++ allocations through the collector fail-after seam. |
| inputs / outputs | Requested byte count enters; allocated pointer or std::bad_alloc exits. |
| invariants | Scalar and array requests share fail_after; direct malloc calls do not pass through this counter. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One counter path plus at most one malloc; not a syscall or universal heap tracer. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0016

[Lines 163–163](../../../../../tests/unit/statistics_collection_test.cpp#L163); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n) { return allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array C++ allocations through the collector fail-after seam. |
| inputs / outputs | Requested byte count enters; allocated pointer or std::bad_alloc exits. |
| invariants | Scalar and array requests share fail_after; direct malloc calls do not pass through this counter. |
| ownership | The seam borrows only scalar counters; allocated backing storage is returned to the matching replacement delete. The harness owns no runtime state. |
| failure | The selected global C++ new/new\[\] request throws std::bad_alloc at the configured position; malloc failure also throws. Direct malloc/syscall activity is outside this seam. |
| cost | One counter path plus at most one malloc; not a syscall or universal heap tracer. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0017

[Lines 164–164](../../../../../tests/unit/statistics_collection_test.cpp#L164); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The wrapper is the test's global C++ allocation interposer; delete does not inject failures. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases replacement-new storage. |
| cost | One free call. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0018

[Lines 165–165](../../../../../tests/unit/statistics_collection_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The wrapper is the test's global C++ allocation interposer; delete does not inject failures. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases replacement-new storage. |
| cost | One free call. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0019

[Lines 166–166](../../../../../tests/unit/statistics_collection_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized scalar replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The wrapper is the test's global C++ allocation interposer; delete does not inject failures. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases replacement-new storage. |
| cost | One free call. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0020

[Lines 167–167](../../../../../tests/unit/statistics_collection_test.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* p,std::size_t) noexcept { std::free(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized array replacement-new storage. |
| inputs / outputs | Pointer enters; no value exits. |
| invariants | The wrapper is the test's global C++ allocation interposer; delete does not inject failures. |
| ownership | The pointer refers to storage returned by this executable's replacement new and is released with free; no runtime object is retained. |
| failure | No failure is injected during delete; it releases replacement-new storage. |
| cost | One free call. |
| Design | [docs/statistics.md](../../../../statistics.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [Refactor.md](../../../../../Refactor.md) |

## B0021

[Lines 168–171](../../../../../tests/unit/statistics_collection_test.cpp#L168); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all seven collector protocol, sampling, truncation, histogram, memory, saturation, and configuration groups. |
| inputs / outputs | No input; calls transactions, sampling/noops, truncation/invalid, histogram/support, lifecycle/memory, saturation, and configuration-fault tests. |
| invariants | Aggregate assertions are those of the named groups; they cover private nested staging, outer publication, bounded counters, and explicit degradation. |
| ownership | All collectors and ticket tokens are local; only snapshots or scalar checks outlive helper calls. |
| failure | Exceptions from bad_alloc/configuration paths are handled by their designated groups; unexpected failure terminates the test. |
| cost | Executes fixed-size numeric traces and four allocation-fault positions; no throughput or no-heap generalization is made. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp) |
