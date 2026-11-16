# `tests/unit/ranking_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `98603ab2ccffc4ff854e6a77021eceeb102c95ad1e0136ed830606d3b5d06f36`. 94 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/ranking_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/ranking_exception_test.cpp#L15) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t n) | calls std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0002) |
| [B0003 · 16–16](../../../../../tests/unit/ranking_exception_test.cpp#L16) | Type/record definition: struct Fault |  · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../tests/unit/ranking_exception_test.cpp#L17) | declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 18–18](../../../../../tests/unit/ranking_exception_test.cpp#L18) | Callable definition: auto metadata(const ws::Metadata& m) | calls ; returns std::tuple{m.attempts,m.committed,m.aborted,m.selected,m.complete,m.aborted_selected,m.truncated,m.… · [reviewed contract](#b0005) |
| [B0006 · 19–19](../../../../../tests/unit/ranking_exception_test.cpp#L19) | Callable definition: auto stamp(const ws::Stamp& s) | calls ; returns std::tuple{s.owner,s.committed_epoch,s.interval_start_epoch,s.reset_generation,s.configuration_gene… · [reviewed contract](#b0006) |
| [B0007 · 20–20](../../../../../tests/unit/ranking_exception_test.cpp#L20) | Callable definition: auto memory(const ws::Memory& m) | calls ; returns std::tuple{m.object_bytes,m.descriptors_bytes,m.committed_bytes,m.attempt_bytes,m.previous_bytes,m.… · [reviewed contract](#b0007) |
| [B0008 · 21–21](../../../../../tests/unit/ranking_exception_test.cpp#L21) | Callable definition: template&lt;class T&gt; bool same(std::span&lt;const T&gt; a,std::span&lt;const T&gt; b) | calls size, std::equal, begin, end; returns a.size()==b.size() && std::equal(a.begin(),a.end(),b.begin()) · [reviewed contract](#b0008) |
| [B0009 · 22–31](../../../../../tests/unit/ranking_exception_test.cpp#L22) | Callable definition: void same_workload_complete(const ws::Snapshot& a,const ws::Snapshot& b) | calls c02_test::check, plan, physical_sha256, stamp; guard c02_test::check(a.plan().physical_sha256()==b.plan().physical_sha256() && stamp(a.stamp())==stamp(b… · [reviewed contract](#b0009) |
| [B0010 · 32–43](../../../../../tests/unit/ranking_exception_test.cpp#L32) | Callable definition: std::vector&lt;std::string&gt; result_image(const crown::planner::ranking::Result& result) | calls selected, structural_key, scores, push_back; returns out; growth push_back; 5 loop sites · [reviewed contract](#b0010) |
| [B0011 · 44–44](../../../../../tests/unit/ranking_exception_test.cpp#L44) | Closes surrounding scope/type. |  · [reviewed contract](#b0011) |
| [B0012 · 45–45](../../../../../tests/unit/ranking_exception_test.cpp#L45) | Definitions sharing source lines: void* operator new(std::size_t n) / void* operator new\[\](std::size_t n) | calls allocate; returns allocate(n); allocate(n); growth allocate, new · [reviewed contract](#b0012) |
| [B0013 · 46–46](../../../../../tests/unit/ranking_exception_test.cpp#L46) | Callable definition: void* operator new(std::size_t n,const std::nothrow_t&) noexcept | calls allocate; returns allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0013) |
| [B0014 · 47–47](../../../../../tests/unit/ranking_exception_test.cpp#L47) | Callable definition: void* operator new\[\](std::size_t n,const std::nothrow_t&) noexcept | calls ; returns allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0014) |
| [B0015 · 48–48](../../../../../tests/unit/ranking_exception_test.cpp#L48) | Definitions sharing source lines: void operator delete(void* p) noexcept / void operator delete\[\](void* p) noexcept | calls std::free · [reviewed contract](#b0015) |
| [B0016 · 49–49](../../../../../tests/unit/ranking_exception_test.cpp#L49) | Definitions sharing source lines: void operator delete(void* p,std::size_t) noexcept / void operator delete\[\](void* p,std::size_t) noexcept | calls std::free · [reviewed contract](#b0016) |
| [B0017 · 50–50](../../../../../tests/unit/ranking_exception_test.cpp#L50) | Definitions sharing source lines: void operator delete(void* p,const std::nothrow_t&) noexcept / void operator delete\[\](void* p,const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0017) |
| [B0018 · 51–94](../../../../../tests/unit/ranking_exception_test.cpp#L51) | Callable definition: int main() | calls fixture, candidates, planner::lower_tree, candidate; guard check(canonical.sources==f.database.tables && workload.metadata().committed==7 && workload.metadata…; returns 1; growth insert, push_back; 5 loop sites · [reviewed contract](#b0018) |

## B0001

[Lines 1–14](../../../../../tests/unit/ranking_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:dd2fc01e3777e218c31b2c871b7abe6b5c013da9dfb9c8852d0f86553d4c4427
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_exception_test.cpp: include "ranking_fixture.hpp", "crown/runtime/ranking_evidence.hpp", "candidate_binding.hpp", "frozen_binding_v2.hpp", &lt;algorithm&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;new&gt;, &lt;tuple&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–15](../../../../../tests/unit/ranking_exception_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t n){++allocations;if(fail_after==0){triggered=true;throw std::bad_alloc{};}if(fail_after>0){--fail_after;}if(auto* p=std::malloc(n?n:1)){return p;}throw std::bad_alloc{};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count and optionally fail one call through the test executable’s selected allocation seam. |
| inputs / outputs | Input is requested size; increments thread-local allocations, throws bad_alloc at fail_after zero, decrements positive countdown, otherwise allocates at least one byte with malloc. |
| invariants | The counter increments for successful and injected-failing attempts, and that increment is unchecked; test counts are far below size_t wrap. Only allocation entry points wired below reach it. |
| ownership | The returned malloc block belongs to the matching test replacement delete; counter and fault state are thread-local. |
| failure | Injected point or malloc failure throws std::bad_alloc. |
| cost | One counter update, countdown branch and malloc per call; no product allocator/byte accounting is performed. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0003

[Lines 16–16](../../../../../tests/unit/ranking_exception_test.cpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fault {explicit Fault(std::size_t i){triggered=false;fail_after=static_cast<std::ptrdiff_t>(i);}~Fault(){fail_after=-1;}};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set and clear the test allocation-failure countdown for one scope. |
| inputs / outputs | Input is a size_t failure position; constructor clears triggered and casts the position to ptrdiff_t; destructor resets fail_after to -1. |
| invariants | Intended nonnested, uncopied bounded use is a caller convention: the type does not enforce nesting or delete its implicit copy operations, and it does not guard size_t-to-ptrdiff_t conversion. triggered remains observable after scope exit. |
| ownership | Fault owns only thread-local test configuration and has no heap payload. |
| failure | No explicit failure translation; unusual out-of-range casts are not checked. |
| cost | Fixed thread-local assignments on construction/destruction. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0004

[Lines 17–17](../../../../../tests/unit/ranking_exception_test.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:fae15d1bcb60d6f8d0aeaa16ae88fe8b59c277b3cd88188819be7a5f4ad1b93c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 18–18](../../../../../tests/unit/ranking_exception_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto metadata(const ws::Metadata& m){return std::tuple{m.attempts,m.committed,m.aborted,m.selected,m.complete,m.aborted_selected,m.truncated,m.committed_truncated,m.guards,m.detail_actions,m.cleared_cells,m.merged_cells,m.saturated,m.invalid_descriptor,m.protocol_error,m.ordinal_exhausted};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot every public workload metadata counter into a comparable tuple. |
| inputs / outputs | Input is a borrowed workload::Metadata; output contains the named attempt/commit/abort/selection/truncation/guard/detail/cell/saturation/protocol counters. |
| invariants | Tuple order is fixed by this test; later comparisons cover only fields present in the tuple. |
| ownership | Metadata is borrowed; tuple owns scalar copies. |
| failure | No explicit failure path beyond scalar tuple construction. |
| cost | Fixed number of scalar reads and tuple construction. |
| Design | [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp) |

## B0006

[Lines 19–19](../../../../../tests/unit/ranking_exception_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto stamp(const ws::Stamp& s){return std::tuple{s.owner,s.committed_epoch,s.interval_start_epoch,s.reset_generation,s.configuration_generation,s.segment,s.format_version,s.reset_saturated,s.configuration_saturated,s.segment_saturated};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot workload ownership, epoch and generation fields into a tuple. |
| inputs / outputs | Input is a borrowed workload::Stamp; output contains owner, epoch interval, reset/configuration/segment/version and saturation fields. |
| invariants | The tuple compares the enumerated stamp fields only. |
| ownership | Stamp is borrowed; returned tuple owns scalar copies. |
| failure | No explicit failure path. |
| cost | Fixed scalar tuple construction. |
| Design | [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp) |

## B0007

[Lines 20–20](../../../../../tests/unit/ranking_exception_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto memory(const ws::Memory& m){return std::tuple{m.object_bytes,m.descriptors_bytes,m.committed_bytes,m.attempt_bytes,m.previous_bytes,m.retained_payload_bytes,m.routes_bytes};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot the named workload memory counters for equality checks. |
| inputs / outputs | Input is a borrowed workload::Memory; output tuple contains object, descriptor, committed, attempt, previous, retained-payload and route bytes. |
| invariants | These are the public workload counters listed; they do not equal total process or MemoryAccount bytes. |
| ownership | Memory value is borrowed; tuple owns scalar copies. |
| failure | No explicit failure path. |
| cost | Fixed scalar tuple construction. |
| Design | [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp) |

## B0008

[Lines 21–21](../../../../../tests/unit/ranking_exception_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> bool same(std::span<const T> a,std::span<const T> b){return a.size()==b.size() && std::equal(a.begin(),a.end(),b.begin());}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two spans element by element after checking their lengths. |
| inputs / outputs | Inputs are borrowed const spans; returns false if sizes differ or std::equal finds a mismatch. |
| invariants | No copy or normalization is applied; comparison is only as complete as the supplied element equality. |
| ownership | Spans and elements are borrowed for the duration of comparison. |
| failure | No explicit failure handling; element comparison follows T semantics. |
| cost | Length comparison plus at most one linear traversal of the span. |
| Design | [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp) |

## B0009

[Lines 22–31](../../../../../tests/unit/ranking_exception_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void same_workload_complete(const ws::Snapshot& a,const ws::Snapshot& b){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the selected public fields of two workload snapshots after ranking/capture failures. |
| inputs / outputs | Inputs are borrowed Snapshots; compares plan hash, stamp, options/modes, descriptors/cells, current and previous metadata/memory and interval/detail state. |
| invariants | It covers the listed snapshot accessors; owner canonical state and candidate handles are checked separately by main’s verify lambda. |
| ownership | Snapshots are borrowed and not retained. |
| failure | A mismatch throws through c02_test::check; range comparisons run synchronously. |
| cost | Compares fixed-size tuples/flags plus linear descriptor, cell and previous-cell spans. |
| Design | [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp) |

## B0010

[Lines 32–43](../../../../../tests/unit/ranking_exception_test.cpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<std::string> result_image(const crown::planner::ranking::Result& result){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Flatten the selected candidate and score fields into stable strings for before/after checks. |
| inputs / outputs | Input is a borrowed ranking Result; output vector begins with selected structural key and appends each score’s key, height, numeric terms, depths, table depths, populations, slot terms and optional modeled-plan digest. |
| invariants | result_image deliberately omits Result::usage, which main compares separately for the baseline expected result. The recovered cleanup-allocation Result is compared by image only; its usage is not compared. Image equality is not full Result equality. |
| ownership | Result is borrowed; vector and every appended string own their copies. |
| failure | String/vector allocation errors propagate. |
| cost | Visits every score and its nested vectors, formatting scalar numbers and copying text; output allocation scales with scores and evidence detail. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0011

[Lines 44–44](../../../../../tests/unit/ranking_exception_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L44:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 45–45](../../../../../tests/unit/ranking_exception_test.cpp#L45); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n){return allocate(n);}void* operator new[](std::size_t n){return allocate(n);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar/array global new calls through the faultable allocator. |
| inputs / outputs | Two same-line definitions accept byte size and return allocate(size) for scalar and array allocation. |
| invariants | These are the throwing overloads wired to the local counter; no aligned overload is replaced in this file. |
| ownership | Returned storage is a malloc block freed by the corresponding delete overloads. |
| failure | Injected or underlying allocation failure propagates as std::bad_alloc. |
| cost | One allocate call per requested object/array; counter counts calls, not bytes or CPU. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0013

[Lines 46–46](../../../../../tests/unit/ranking_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route nothrow scalar new through the faultable allocator. |
| inputs / outputs | Input is size; calls allocate inside try and returns nullptr if any exception is raised. |
| invariants | The nothrow boundary suppresses all exceptions from allocate; triggered still records the injected point. |
| ownership | A returned malloc block is later released by the ordinary scalar/array delete expression. The matching nothrow placement-delete overload is used if construction fails after allocation; it is not the normal destruction path for a successfully constructed object. |
| failure | Returns null instead of propagating allocation exceptions. |
| cost | One allocate attempt and catch-all branch. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0014

[Lines 47–47](../../../../../tests/unit/ranking_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route nothrow array new through the faultable allocator. |
| inputs / outputs | Input is array size; calls allocate inside try and returns nullptr on any exception. |
| invariants | This array overload is distinct from the throwing array overload; only its failure return is nothrow. |
| ownership | A returned malloc block is later released by the ordinary scalar/array delete expression. The matching nothrow placement-delete overload is used if construction fails after allocation; it is not the normal destruction path for a successfully constructed object. |
| failure | Returns null for injected or underlying allocation exceptions. |
| cost | One allocate attempt and catch-all branch. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0015

[Lines 48–48](../../../../../tests/unit/ranking_exception_test.cpp#L48); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p) noexcept{std::free(p);}void operator delete[](void* p) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release ordinary scalar and array allocation blocks through free. |
| inputs / outputs | Inputs are scalar or array pointer; both same-line overloads call std::free. |
| invariants | No allocation counters are adjusted here; allocation attempts were counted at new entry. |
| ownership | Pointer storage is released; null is accepted by free. |
| failure | No exception path because overloads are noexcept. |
| cost | One free per delete call. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0016

[Lines 49–49](../../../../../tests/unit/ranking_exception_test.cpp#L49); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,std::size_t) noexcept{std::free(p);}void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized scalar and array allocation blocks through free. |
| inputs / outputs | Inputs are pointer and size; size is ignored and both overloads call std::free. |
| invariants | Sized delete behavior matches the unsized test deallocator; size is not validated. |
| ownership | Pointer storage is released. |
| failure | No exception path because overloads are noexcept. |
| cost | One free per delete call. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0017

[Lines 50–50](../../../../../tests/unit/ranking_exception_test.cpp#L50); `inline-cluster`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* p,const std::nothrow_t&) noexcept{std::free(p);}void operator delete[](void* p,const std::nothrow_t&) noexcept{std::free(p);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release blocks passed to the nothrow scalar/array delete overloads. |
| inputs / outputs | Inputs are pointer and nothrow tag; both overloads call std::free. |
| invariants | Tag and pointer size do not affect the release operation. |
| ownership | Pointer storage is released. |
| failure | No exception path because overloads are noexcept. |
| cost | One free per delete call. |
| Design | [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0018

[Lines 51–94](../../../../../tests/unit/ranking_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise allocation-failure recovery for runtime evidence capture and ranking. |
| inputs / outputs | No inputs; creates proof/candidates/runtime, applies seven updates to its initial rows (four physical changes and three no-op outcomes), captures evidence, and runs three rank policies. For each policy it measures N intercepted new calls, injects positions 0..N-1, then retries once after the full sweep. It separately measures capture count M, injects 0..M-1 and retries once. |
| invariants | The fixture asserts workload committed=7, attempts=7, aborted=0; capture has denominator 7 and three source rows. Each rank sweep injects exactly 0..N-1 (there is no injected terminal N point) and performs one retry after that policy’s sweep. Capture likewise sweeps all M measured positions, then retries. verify compares selected runtime/workload/proof state, but this test takes no direct query-account current-byte snapshot. Recovered rank results are image-checked; their usage is not compared. Interception covers the unaligned scalar/array throwing and nothrow new overloads defined in this translation unit; aligned new and independent direct malloc calls are outside that hook. The frozen/current P07 binding comparison checks bytes, string capacity and covered-new count for this one fixture. |
| ownership | Runtime owner, candidate snapshot, baseline evidence/results and each retry own independent handles; the verify lambda observes retained owner/snapshot state after each fault. |
| failure | Rank failures must return allocation_failure unless a cleanup allocation completes the same result; capture failures return no evidence with allocation_failure. Retry and state mismatches fail by exception. |
| cost | Source-call schedule: each of three policies has one measured healthy rank, N injected rank attempts and one post-sweep retry (N+2 rank calls per policy, excluding fixture setup and comparisons). Capture has the earlier evidence capture, one calibration capture, M injected attempts and one retry (M+3 capture calls total). Snapshot/result comparisons traverse selected fields. The hook counts selected C++ new attempts, not bytes, total heap, RSS or CPU. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [include/crown/runtime/workload_statistics.hpp](../../../../../include/crown/runtime/workload_statistics.hpp), [src/planner/candidate_binding.hpp](../../../../../src/planner/candidate_binding.hpp), [src/planner/ranking.cpp](../../../../../src/planner/ranking.cpp), [src/planner/ranking_detail.hpp](../../../../../src/planner/ranking_detail.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp), [tests/support/frozen_binding_v2.hpp](../../../../../tests/support/frozen_binding_v2.hpp), [tests/support/ranking_fixture.hpp](../../../../../tests/support/ranking_fixture.hpp), [tests/unit/ranking_exception_test.cpp](../../../../../tests/unit/ranking_exception_test.cpp) |
