# `tests/support/selection_exception_support.hpp` — block usage map

[Source](../../../../../tests/support/selection_exception_support.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2ce43258b81c9119b8a68d70ce5c4815d964f28ef162143783d023b584253533`. 195 lines partitioned into 45 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../tests/support/selection_exception_support.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 13–15](../../../../../tests/support/selection_exception_support.hpp#L13) | Callable definition: template&lt;class Text&gt; inline std::string caller_text(const Text& text) | calls data, size; returns std::string{text.data(), text.size()} · [reviewed contract](#b0002) |
| [B0003 · 16–20](../../../../../tests/support/selection_exception_support.hpp#L16) | declares values/defaults or compile-time conditions. | source comment (unverified): // Counts covered new calls even outside Fault. Zero denial persists through · [reviewed contract](#b0003) |
| [B0004 · 21–25](../../../../../tests/support/selection_exception_support.hpp#L21) | Callable definition: inline void position() | calls  · [reviewed contract](#b0004) |
| [B0005 · 26–28](../../../../../tests/support/selection_exception_support.hpp#L26) | Callable definition: \[\[gnu::noinline\]\] inline void* allocate(std::size_t n) | calls position, std::malloc; returns p; growth allocate, malloc · [reviewed contract](#b0005) |
| [B0006 · 29–35](../../../../../tests/support/selection_exception_support.hpp#L29) | Callable definition: \[\[gnu::noinline\]\] inline void* aligned(std::size_t n, std::size_t alignment) | calls position, max, std::aligned_alloc; returns p · [reviewed contract](#b0006) |
| [B0007 · 36–36](../../../../../tests/support/selection_exception_support.hpp#L36) | Callable definition: \[\[gnu::noinline\]\] inline void release(void* p) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 37–37](../../../../../tests/support/selection_exception_support.hpp#L37) | Explanatory comments or spacing. | source comment (unverified): // One lexical, nonnested guard: implicit copying does not create private fault state. · [reviewed contract](#b0008) |
| [B0009 · 38–45](../../../../../tests/support/selection_exception_support.hpp#L38) | Type/record definition: struct Fault | source comment (unverified): // One lexical, nonnested guard: implicit copying does not create private fault state. · [reviewed contract](#b0009) |
| [B0010 · 46–47](../../../../../tests/support/selection_exception_support.hpp#L46) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 48–52](../../../../../tests/support/selection_exception_support.hpp#L48) | Callable definition: inline auto metadata(const ws::Metadata& m) | calls ; returns std::tuple{m.attempts, m.committed, m.aborted, m.selected, m.complete, m.aborted_selected, · [reviewed contract](#b0011) |
| [B0012 · 53–57](../../../../../tests/support/selection_exception_support.hpp#L53) | Callable definition: inline auto stamp(const ws::Stamp& s) | calls ; returns std::tuple{s.owner, s.committed_epoch, s.interval_start_epoch, s.reset_generation, · [reviewed contract](#b0012) |
| [B0013 · 58–61](../../../../../tests/support/selection_exception_support.hpp#L58) | Callable definition: inline auto memory(const ws::Memory& m) | calls ; returns std::tuple{m.object_bytes, m.descriptors_bytes, m.committed_bytes, m.attempt_bytes, · [reviewed contract](#b0013) |
| [B0014 · 62–64](../../../../../tests/support/selection_exception_support.hpp#L62) | Callable definition: template&lt;class T&gt; bool equal(std::span&lt;const T&gt; a, std::span&lt;const T&gt; b) | calls size, std::equal, begin, end; returns a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin()) · [reviewed contract](#b0014) |
| [B0015 · 65–74](../../../../../tests/support/selection_exception_support.hpp#L65) | Callable definition: inline void workload(const ws::Snapshot& a, const ws::Snapshot& b) | calls check, plan, physical_sha256, stamp; guard check(a.plan().physical_sha256() == b.plan().physical_sha256() && stamp(a.stamp()) == stamp(b.stamp… · [reviewed contract](#b0015) |
| [B0016 · 75–88](../../../../../tests/support/selection_exception_support.hpp#L75) | Callable definition: inline std::vector&lt;std::string&gt; rank_image(const pr::Result& result) | calls selected, structural_key, scores, insert; returns out; growth insert, push_back; 5 loop sites · [reviewed contract](#b0016) |
| [B0017 · 89–89](../../../../../tests/support/selection_exception_support.hpp#L89) | Explanatory comments or spacing. | source comment (unverified): // Ordinary text/JSON export copies key/plan payload; this is not a cheap handle copy. · [reviewed contract](#b0017) |
| [B0018 · 90–101](../../../../../tests/support/selection_exception_support.hpp#L90) | Callable definition: inline std::vector&lt;std::string&gt; selection_image(const ps::Selection& result) | calls selected, structural_key, std::to_string, selected_index; returns out; growth insert, push_back; 2 loop sites; source comment (unverified): // Ordinary text/JSON export copies key/plan payload; this is not a cheap handle copy. · [reviewed contract](#b0018) |
| [B0019 · 102–102](../../../../../tests/support/selection_exception_support.hpp#L102) | Callable definition: inline const ps::Selection& pure(const ps::Selection& value) | calls ; returns value · [reviewed contract](#b0019) |
| [B0020 · 103–103](../../../../../tests/support/selection_exception_support.hpp#L103) | Callable definition: inline const ps::Selection& pure(const rs::CurrentSelection& value) | calls selection; returns value.selection() · [reviewed contract](#b0020) |
| [B0021 · 104–109](../../../../../tests/support/selection_exception_support.hpp#L104) | Callable definition: inline auto cache_image(ps::PlanCache& cache) | calls ps::detail::Factory::cache, emplace_back, io::write_physical, dump; returns out; growth emplace_back; 1 loop sites · [reviewed contract](#b0021) |
| [B0022 · 110–110](../../../../../tests/support/selection_exception_support.hpp#L110) | Type/record definition: struct Totals |  · [reviewed contract](#b0022) |
| [B0023 · 111–112](../../../../../tests/support/selection_exception_support.hpp#L111) | Explanatory comments or spacing. | source comment (unverified): // Only invoke runs under Fault; image/proof/owner/cache verification follows disarming. · [reviewed contract](#b0023) |
| [B0024 · 113–171](../../../../../tests/support/selection_exception_support.hpp#L113) | Callable definition: template&lt;class Invoke&gt; void sweep(const char* label, const planner::CandidateSnapshot& snapshot, runtime::PhysicalRuntime& owner,… | calls request, ps::PlanCache::create, complete, invoke; guard check(count != 0 && count &lt; 200'000, "C05 fault position guard exceeded");; returns cache; growth push_back; 3 loop sites; source comment (unverified): // Only invoke runs under Fault; image/proof/owner/cache verification follows disarming. · [reviewed contract](#b0024) |
| [B0025 · 172–175](../../../../../tests/support/selection_exception_support.hpp#L172) | Closes surrounding scope/type. | source comment (unverified): // namespace c05_fault · [reviewed contract](#b0025) |
| [B0026 · 176–176](../../../../../tests/support/selection_exception_support.hpp#L176) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n) | calls c05_fault::allocate; returns c05_fault::allocate(n); growth allocate, new; source comment (unverified): // No-inline allocation/deallocation seams keep optimized compilers from · [reviewed contract](#b0026) |
| [B0027 · 177–177](../../../../../tests/support/selection_exception_support.hpp#L177) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n) | calls ; returns c05_fault::allocate(n); growth allocate, new · [reviewed contract](#b0027) |
| [B0028 · 178–178](../../../../../tests/support/selection_exception_support.hpp#L178) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, const std::nothrow_t&) noexcept | calls c05_fault::allocate; returns c05_fault::allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0028) |
| [B0029 · 179–179](../../../../../tests/support/selection_exception_support.hpp#L179) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, const std::nothrow_t&) noexcept | calls ; returns c05_fault::allocate(n); nullptr; growth allocate, new · [reviewed contract](#b0029) |
| [B0030 · 180–180](../../../../../tests/support/selection_exception_support.hpp#L180) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, std::align_val_t alignment) | calls c05_fault::aligned; returns c05_fault::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0030) |
| [B0031 · 181–181](../../../../../tests/support/selection_exception_support.hpp#L181) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, std::align_val_t alignment) | calls ; returns c05_fault::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0031) |
| [B0032 · 182–182](../../../../../tests/support/selection_exception_support.hpp#L182) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept | calls c05_fault::aligned; returns c05_fault::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); nullptr; growth new · [reviewed contract](#b0032) |
| [B0033 · 183–183](../../../../../tests/support/selection_exception_support.hpp#L183) | Callable definition: \[\[gnu::noinline\]\] void* operator new\[\](std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept | calls ; returns c05_fault::aligned(n, static_cast&lt;std::size_t&gt;(alignment)); nullptr; growth new · [reviewed contract](#b0033) |
| [B0034 · 184–184](../../../../../tests/support/selection_exception_support.hpp#L184) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p) noexcept | calls c05_fault::release · [reviewed contract](#b0034) |
| [B0035 · 185–185](../../../../../tests/support/selection_exception_support.hpp#L185) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p) noexcept | calls  · [reviewed contract](#b0035) |
| [B0036 · 186–186](../../../../../tests/support/selection_exception_support.hpp#L186) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::size_t) noexcept | calls c05_fault::release · [reviewed contract](#b0036) |
| [B0037 · 187–187](../../../../../tests/support/selection_exception_support.hpp#L187) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::size_t) noexcept | calls  · [reviewed contract](#b0037) |
| [B0038 · 188–188](../../../../../tests/support/selection_exception_support.hpp#L188) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, const std::nothrow_t&) noexcept | calls c05_fault::release · [reviewed contract](#b0038) |
| [B0039 · 189–189](../../../../../tests/support/selection_exception_support.hpp#L189) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0039) |
| [B0040 · 190–190](../../../../../tests/support/selection_exception_support.hpp#L190) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::align_val_t) noexcept | calls c05_fault::release · [reviewed contract](#b0040) |
| [B0041 · 191–191](../../../../../tests/support/selection_exception_support.hpp#L191) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::align_val_t) noexcept | calls  · [reviewed contract](#b0041) |
| [B0042 · 192–192](../../../../../tests/support/selection_exception_support.hpp#L192) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::size_t, std::align_val_t) noexcept | calls c05_fault::release · [reviewed contract](#b0042) |
| [B0043 · 193–193](../../../../../tests/support/selection_exception_support.hpp#L193) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0043) |
| [B0044 · 194–194](../../../../../tests/support/selection_exception_support.hpp#L194) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept | calls c05_fault::release · [reviewed contract](#b0044) |
| [B0045 · 195–195](../../../../../tests/support/selection_exception_support.hpp#L195) | Callable definition: \[\[gnu::noinline\]\] void operator delete\[\](void* p, std::align_val_t, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0045) |

## B0001

[Lines 1–12](../../../../../tests/support/selection_exception_support.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L12:sha256:a6f5dea50be9ae075bc75df7c24cd5f83792901759a944eaba4bab6f0fd1e25b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_exception_support.hpp: include "selection_fixture.hpp", "selection_detail.hpp", &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;tuple&gt;, &lt;type_traits&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 13–15](../../../../../tests/support/selection_exception_support.hpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Text> inline std::string caller_text(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a caller-owned exact byte copy from native/ordinary text views for test comparison. |
| inputs / outputs | Constructs std::string(text.data(),text.size()), preserving embedded NUL bytes. |
| invariants | Text must expose a stable valid byte span through construction. This is an explicit ordinary export, not a shared SelectionText/key handle. |
| ownership | Returned string owns independent bytes outside query account unless caller separately funds it; source can expire afterward. |
| failure | Ordinary allocation failures propagate and can be caught by an active executable new seam. |
| cost | O(text length) copy with possible string allocation; small-string optimization is not assumed. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 16–20](../../../../../tests/support/selection_exception_support.hpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline thread_local std::ptrdiff_t fail_after
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep C05 allocation calibration and persistent per-thread fail position. |
| inputs / outputs | allocations counts every covered replacement-new call, including while fail_after is negative/outside a Fault; triggered reports reaching configured zero. |
| invariants | Counter is unsigned and not saturating/overflow-guarded here; actual sweep bounds count below 200,000. Not an account, byte, free, live-allocation or system malloc meter. |
| ownership | Only thread-local scalar state; no heap or owner. |
| failure | Failure injection is controlled by Fault and position; unrelated allocator null remains separate. |
| cost | One increment/check per covered new even outside fault windows; executable test-only replacement. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 21–25](../../../../../tests/support/selection_exception_support.hpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void position()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count a C05 replacement-new attempt and enforce persistent zero denial. |
| inputs / outputs | Increments allocations unconditionally; zero sets triggered then throws, positive fail_after decrements, negative allows underlying request. |
| invariants | Unlike S04 enabled Scope, ordinary calls outside Fault still count. Zero never auto-disarms; instrumentation remains active until Fault destruction. Finite test calibration prevents counter overflow. |
| ownership | Thread-local counters only. |
| failure | Throws bad_alloc at the injected position and all subsequent covered positions in that fault window; actual malloc failure is separate. |
| cost | Fixed counter/branch operations; no helper buffer, account or timing probe. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 26–28](../../../../../tests/support/selection_exception_support.hpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void* allocate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate ordinary C++ raw storage through the C05 fault seam. |
| inputs / outputs | Calls position before malloc(n?n:1). |
| invariants | Only covered new forms are intercepted; no raw malloc/realloc/system failure hook or new_handler retry. Zero-size allocation requests one real byte. |
| ownership | Returned raw storage belongs to caller and is freed by compatible global delete; no MemoryAccount is synthesized. |
| failure | Persistent injected denial or actual allocator null throws bad_alloc; aligned rounding overflow also throws. triggered distinguishes configured denial only. |
| cost | Fixed seam work plus one real allocator request; counter does not include requested/padded bytes, allocator metadata, frees or timings. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 29–35](../../../../../tests/support/selection_exception_support.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void* aligned(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate aligned C++ raw storage through the C05 fault seam. |
| inputs / outputs | Calls position before rounding/checking size for valid C++ alignment and aligned_alloc. |
| invariants | Only covered new forms are intercepted; no raw malloc/realloc/system failure hook or new_handler retry. Rounding checks n+(alignment-1) overflow; alignment is valid nonzero align_val_t input. |
| ownership | Returned raw storage belongs to caller and is freed by compatible global delete; no MemoryAccount is synthesized. |
| failure | Persistent injected denial or actual allocator null throws bad_alloc; aligned rounding overflow also throws. triggered distinguishes configured denial only. |
| cost | Fixed seam work plus one real allocator request; counter does not include requested/padded bytes, allocator metadata, frees or timings. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 36–36](../../../../../tests/support/selection_exception_support.hpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] inline void release(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release C05 replacement-new raw storage consistently across delete forms. |
| inputs / outputs | Calls std::free(p). |
| invariants | No allocation position is consumed or counter decremented; cleanup observations concern successful completion under covered new denial, not system allocator teardown guarantees. |
| ownership | Caller passes compatible raw storage; object destruction occurs before normal delete dispatch. |
| failure | Noexcept direct free, no handler or injected release failure. |
| cost | One free, no replacement allocation; actual allocator release work is unmetered. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 37–37](../../../../../tests/support/selection_exception_support.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:47e61db3b92d448f2ebe09ae90822c6903b74fbc5f74c4908012e7b30dd8025c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: One lexical, nonnested guard: implicit copying does not create private fault state. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 38–45](../../../../../tests/support/selection_exception_support.hpp#L38); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fault {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm one lexical C05 persistent new-failure interval without resetting allocation calibration. |
| inputs / outputs | Constructor clears triggered, checks position&lt;=PTRDIFF_MAX and installs fail_after; destructor resets fail_after=-1. allocations is deliberately not reset. |
| invariants | Actual callers use nonnested automatic guards around exactly invoke(cache). Type has a user destructor but no deleted copy: implicit copying is possible and does not create independent fault state; do not copy/nest it. No move is declared (rvalue copying can use the copy constructor). |
| ownership | Guard controls shared per-thread state only; external owner/cache/snapshot are retained outside it. |
| failure | Out-of-range position throws bad_alloc before arming a new count; destructor nonthrowingly disarms. Persistent zero denial covers further new calls during unwinding until scope exit. |
| cost | Fixed checks/stores, no allocation by guard itself; unsigned calibration bounds are enforced by sweep. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 46–47](../../../../../tests/support/selection_exception_support.hpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L47:sha256:168c5d417eb5a9fe408d204c2200963ec89825f6105b4ce97a8e0881d7bcc6ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_exception_support.hpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0011

[Lines 48–52](../../../../../tests/support/selection_exception_support.hpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline auto metadata(const ws::Metadata& m)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project all current workload lifecycle/protocol metadata into an owning numeric tuple. |
| inputs / outputs | Copies attempts/committed/aborted/selected/complete, aborted-selected/truncated/committed-truncated, guards/detail actions/cleared/merged cells and all saturation/descriptor/protocol/ordinal flags. |
| invariants | Tuple values do not retain a Metadata reference or row payload; this projection is a test comparator, not source/commit authority. |
| ownership | Tuple owns inline IDs/integers/booleans only; input snapshot struct is borrowed during construction. |
| failure | No explicit handler or allocation on valid numeric tuple construction. |
| cost | Fixed field copies; no descriptor/row/account-ledger scan. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 53–57](../../../../../tests/support/selection_exception_support.hpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline auto stamp(const ws::Stamp& s)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project all workload owner/interval identity metadata into an owning numeric tuple. |
| inputs / outputs | Copies owner, committed epoch, interval start, reset/configuration generation, segment, format and saturation flags. |
| invariants | Same stamp alone does not imply equal counters/modes/pending/history; workload comparison checks those separately. |
| ownership | Tuple owns inline IDs/integers/booleans only; input snapshot struct is borrowed during construction. |
| failure | No explicit handler or allocation on valid numeric tuple construction. |
| cost | Fixed field copies; no descriptor/row/account-ledger scan. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 58–61](../../../../../tests/support/selection_exception_support.hpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline auto memory(const ws::Memory& m)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project workload component-capacity accounting for exact regression comparison. |
| inputs / outputs | Copies object/descriptor/committed/attempt/previous/routes capacity bytes and retained_payload_bytes. |
| invariants | These are component logical payload capacities, not whole-query requested bytes, allocator framing, detached snapshots, process memory or allocation timings. |
| ownership | Tuple owns inline IDs/integers/booleans only; input snapshot struct is borrowed during construction. |
| failure | No explicit handler or allocation on valid numeric tuple construction. |
| cost | Fixed field copies; no descriptor/row/account-ledger scan. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 62–64](../../../../../tests/support/selection_exception_support.hpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> bool equal(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare numeric spans without exporting or copying their arrays. |
| inputs / outputs | Checks equal sizes then std::equal over all elements until first mismatch. |
| invariants | Span owners must remain stable; equality of a partial field alone is not complete snapshot/proof equivalence. |
| ownership | Borrows both arrays; bool result owns nothing. |
| failure | Element equality requirements are supplied by current numeric Descriptor/Cell types; no local catch or failure injection. |
| cost | O(compared elements), with Cell equality including fixed histogram members; no array/key allocation. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 65–74](../../../../../tests/support/selection_exception_support.hpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void workload(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require unchanged complete public workload snapshot fields after an attempted operation. |
| inputs / outputs | Compares plan hash, full stamps/options/modes/current+previous descriptors/cells/metadata/capacity accounting, pending/history flags, prior interval bounds and detail availability; fails through fixture check. |
| invariants | Reads detached snapshot facts; it does not compare live row/account-ledger state, which test callers verify separately. Equality is on exposed content, not shared-pointer identity or an actual-owner freshness grant. |
| ownership | Inputs are borrowed owning snapshots; no snapshot graph clone. Numeric tuple projections copy values only. |
| failure | Mismatch throws runtime_error outside the intended measured/fault invocation in actual callers. Existing allocation counters may observe unrelated diagnostic construction when enabled. |
| cost | Linear descriptor/current/previous Cell comparisons and fixed metadata/hash fields; no owning row export or new query capture within this helper itself. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 75–88](../../../../../tests/support/selection_exception_support.hpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<std::string> rank_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export tested ranking score/reproduction facts with full modeled physical artifacts for C05 recovery comparison. |
| inputs / outputs | Copies selected/key/height/score text, depth/population/slot reproduction records and, if present, io::write_physical(modeled_plan).dump(). |
| invariants | Only chosen public fields are in this comparison image; it is descriptive data rather than proof, actual owner identity or complete usage equality. Caller verifies owner/workload/proof and retained usage separately. |
| ownership | Owns ordinary strings/vector/JSON exports; caller_text explicitly copies bytes from native SelectionText/ScoreText. Modeled CompiledProgram export creates ordinary PhysicalPlan payload while sharing existing layout/projection owners. |
| failure | Actual string/DOM/plan export/allocation failures propagate; image construction is outside Fault in the sweep. |
| cost | Visits all score/term records and copied text bytes, plus full physical program/catalog/tree/options export and serialization for every modeled plan. Not a shared-key/no-allocation image. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 89–89](../../../../../tests/support/selection_exception_support.hpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L89:sha256:c603a44ecacf3549a7ed34f36954c3e9c444639c249f981e543e54b9f9a1fe37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Ordinary text/JSON export copies key/plan payload; this is not a cheap handle copy. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 90–101](../../../../../tests/support/selection_exception_support.hpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<std::string> selection_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an independent ordinary comparison image of a prepared pure selection bundle. |
| inputs / outputs | Copies chosen key/index, full compiled physical-plan export, effective policy/fallback, optional cache-binding bytes, purpose-tagged rank images and candidate eligibility decisions. |
| invariants | Diagnostic usage/timing/all source/evidence fields are not exhaustively serialized; tests supplement this image with retained usage and full actual owner/workload/proof checks. An image is not an admitted executable or selection capability. |
| ownership | Owns ordinary vector/strings/DOM export copies. Native immutable Selection/Result/plan handles stay borrowed; copying their handles differs from these byte exports. |
| failure | Formatting/export/allocation failures propagate and are not swallowed. Actual sweep captures images after persistent-denial guard is disarmed. |
| cost | Full selected plan export plus every assessment rank_image and decision, with real ordinary allocation and potentially repeated modeled-plan serialization. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0019

[Lines 102–102](../../../../../tests/support/selection_exception_support.hpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const ps::Selection& pure(const ps::Selection& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize test access to the pure choice without cloning a selection graph. |
| inputs / outputs | Returns the supplied pure Selection reference. |
| invariants | This accessor performs no capture, owner revalidation or typed proof construction. Temporary callers must not retain the returned reference beyond owner lifetime. |
| ownership | Reference borrows argument; copying it into a separate Selection explicitly shares its real immutable control. |
| failure | No explicit allocation/throw path for factory-produced valid handles; no added handler. |
| cost | Fixed const reference forwarding, no key/array/JSON copy. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 103–103](../../../../../tests/support/selection_exception_support.hpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline const ps::Selection& pure(const rs::CurrentSelection& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize test access to the pure choice without cloning a selection graph. |
| inputs / outputs | Returns value.selection() from retained CurrentSelection. |
| invariants | This accessor performs no capture, owner revalidation or typed proof construction. Temporary callers must not retain the returned reference beyond owner lifetime. |
| ownership | Reference borrows CurrentSelection's retained native Data/Selection graph; wrapper must outlive the reference. |
| failure | No explicit allocation/throw path for factory-produced valid handles; no added handler. |
| cost | Fixed const reference forwarding, no key/array/JSON copy. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 104–109](../../../../../tests/support/selection_exception_support.hpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline auto cache_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect exact FIFO cache artifact content through the test-only private seam. |
| inputs / outputs | Reads Factory::cache(&cache)-&gt;entries in order and copies each key, full physical JSON dump and stored payload into an ordinary tuple vector. |
| invariants | This is private test visibility, not public cache mutation/proof authority. cache.statistics is compared separately; image does not itself assert account bytes or whole-cache timing. |
| ownership | Returned keys/JSON strings own independent copies; cache and plan entries are borrowed only while exporting. PlanCache owner must be valid. |
| failure | Serialization/string/vector allocation errors propagate; actual sweep obtains/compares this image outside Fault. |
| cost | Linear cache entries plus every full plan export/serialization and key byte copy, with real ordinary allocations; no blanket shared-key claim. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 110–110](../../../../../tests/support/selection_exception_support.hpp#L110); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Totals {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate fault-sweep coverage observations across caller scenarios. |
| inputs / outputs | positions counts attempted injected positions; recovered counts a complete exact result despite reaching denial; publication/assessment/lowering fields classify failed Attempt stages. |
| invariants | Counters describe covered executable C++ new positions and observed diagnostics, not all malloc failures, every possible execution path, bytes or runtime performance. No overflow/saturation check; bounded caller loops apply. |
| ownership | Inline numeric aggregate; copies/moves copy scalar values and own no query graph. |
| failure | No own handler or authority; test assertions require named phase counts nonzero. |
| cost | Fixed increments per observed sweep position, no extra runtime hook. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 111–112](../../../../../tests/support/selection_exception_support.hpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L112:sha256:b53b00a0c48af422658e4063502090a3558f60114624e5d5df045d7fe2341c26
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Only invoke runs under Fault; image/proof/owner/cache verification follows disarming. The calibrated positions are C++ new attempts, not a system malloc-failure sweep. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 113–171](../../../../../tests/support/selection_exception_support.hpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Invoke>
void sweep(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run caller-supplied pure/current selection under every calibrated persistent C++ new-denial position and verify preserved state. |
| inputs / outputs | Builds a one-entry cache (warm target or height seed), measures covered new count for invoke, retains exact comparison images/proof/owner/workload/prior results, then for each position invokes with a lexical Fault, checks triggered and either exact completion or accepted allocation/lowering-limit failure. |
| invariants | Count must be nonzero and &lt;200,000. Failure must leave cache stats/FIFO/artifacts unchanged; completed recovery resets cache to the baseline setup. Every position verifies actual owner/sequence/canonical/workload, snapshot/proof/keys and older selection contents; final disarmed retry must match baseline. Persistent denial is not one-shot, and this is not raw system malloc/account-byte failure coverage. |
| ownership | snapshot/owner/source/evidence/totals are borrowed; Invoke is copied by value (actual callers use borrowed-capture lambdas). Ordinary keys/images/canonical DTOs and typed immutable result handles are retained outside fault windows. Only invoke and Attempt transfer run with Fault active. |
| failure | The selection APIs are noexcept Attempt boundaries. After guard exit, unexpected result/phase/cache/state changes throw through check; helper adds no catch or automatic engine recovery. A later image/assert allocation can fail separately, and no global malloc denial is simulated. |
| cost | One baseline plus count full selection calls and a full proof/owner/workload/image verification per position, including repeated captures/ordinary serializations; many allocations occur outside measured invocation. Counts are test calibration, not byte/CPU/complete system-allocation evidence. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const auto make_cache = [&] {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a reproducible cache state before measuring/injecting selection. |
| inputs / outputs | Creates PlanCache limits {1 entry,8MiB key,32MiB plan payload}, warms with target invoke or height seed, then returns owning cache. |
| invariants | Each reset uses the same warm flag/caller source/evidence. It runs outside the Fault guard and can allocate; creating a baseline cache is not measured selection publication. |
| ownership | Returns actual move-only PlanCache owner; lambda borrows synchronous sweep inputs and does not escape. |
| failure | Any failed setup selection is rejected by complete and aborts fixture; no hidden retry or fallback cache. |
| cost | Real cache/control/plan-key setup and optional full selection/lowering; not just a fixed object construction. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

```text
  const auto verify = [&] {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each injected call left actual owner/proofs and all older successful results intact. |
| inputs / outputs | Compares owner ID/sequence/canonical rows, new workload snapshot with retained snapshot, typed original proof/candidates/keys, prior selection bytes+usage and earlier baseline result; current selections additionally require retained actual owner/epoch capture and workload agreement. |
| invariants | Verification is after Fault destruction. It checks explicit observed fields, with independent actual owner state/proof authority; comparison exports alone do not create evidence. |
| ownership | Lambda borrows sweep locals; canonical/images/keys are independent ordinary copies, typed Selection/CurrentSelection copies share their existing immutable Data controls. |
| failure | Mismatch throws runtime_error. Actual verification capture/export allocation errors are separate from the injected invoke result. |
| cost | Full canonical/workload capture plus candidate/score/plan/text comparisons at every position, potentially allocating under both original query accounts and ordinary caller memory. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 172–175](../../../../../tests/support/selection_exception_support.hpp#L172); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L172-L175:sha256:73a13d0acfb7b391f9d748b513d94e3cd982db3c0d6f153f45627447df822aab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_exception_support.hpp: namespace c05_fault. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 176–176](../../../../../tests/support/selection_exception_support.hpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n) { return c05_fault::allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary throwing global new overload. |
| inputs / outputs | Forwards raw size to c05_fault::allocate; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0027

[Lines 177–177](../../../../../tests/support/selection_exception_support.hpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n) { return c05_fault::allocate(n); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary throwing global new overload. |
| inputs / outputs | Forwards raw size to c05_fault::allocate; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 178–178](../../../../../tests/support/selection_exception_support.hpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, const std::nothrow_t&) noexcept { try { return c05_fault::allocate(n); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary nothrow global new overload. |
| inputs / outputs | Forwards raw size to c05_fault::allocate; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0029

[Lines 179–179](../../../../../tests/support/selection_exception_support.hpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, const std::nothrow_t&) noexcept { try { return c05_fault::allocate(n); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's ordinary nothrow global new overload. |
| inputs / outputs | Forwards raw size to c05_fault::allocate; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0030

[Lines 180–180](../../../../../tests/support/selection_exception_support.hpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment) { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned throwing global new overload. |
| inputs / outputs | Forwards raw size and alignment to c05_fault::aligned; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0031

[Lines 181–181](../../../../../tests/support/selection_exception_support.hpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment) { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned throwing global new overload. |
| inputs / outputs | Forwards raw size and alignment to c05_fault::aligned; returns raw storage or propagates bad_alloc. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Configured denial, arithmetic overflow where applicable and actual allocator failure propagate; no new_handler retry is added. |
| cost | Fixed forwarding plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0032

[Lines 182–182](../../../../../tests/support/selection_exception_support.hpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned nothrow global new overload. |
| inputs / outputs | Forwards raw size and alignment to c05_fault::aligned; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0033

[Lines 183–183](../../../../../tests/support/selection_exception_support.hpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new[](std::size_t n, std::align_val_t alignment, const std::nothrow_t&) noexcept { try { return c05_fault::aligned(n, static_cast<std::size_t>(alignment)); } catch (...) { return nullptr; } }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the executable's aligned nothrow global new overload. |
| inputs / outputs | Forwards raw size and alignment to c05_fault::aligned; catches every exception and returns nullptr. |
| invariants | One replacement family per single linked test translation unit. Injection is persistent at zero; covered aligned and ordinary forms are present. |
| ownership | Raw storage ownership follows matching delete family; no query-account object is created by overload dispatch. |
| failure | Nothrow catch is required by its noexcept/null contract; it does not report engine recovery or retry. |
| cost | Fixed forwarding and exception-to-null mapping on failure plus the exact allocator seam cost; count is attempts, not bytes/live/peak/process malloc failures. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0034

[Lines 184–184](../../../../../tests/support/selection_exception_support.hpp#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0035

[Lines 185–185](../../../../../tests/support/selection_exception_support.hpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0036

[Lines 186–186](../../../../../tests/support/selection_exception_support.hpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::size_t) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0037

[Lines 187–187](../../../../../tests/support/selection_exception_support.hpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::size_t) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0038

[Lines 188–188](../../../../../tests/support/selection_exception_support.hpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, const std::nothrow_t&) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0039

[Lines 189–189](../../../../../tests/support/selection_exception_support.hpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, const std::nothrow_t&) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0040

[Lines 190–190](../../../../../tests/support/selection_exception_support.hpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::align_val_t) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0041

[Lines 191–191](../../../../../tests/support/selection_exception_support.hpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0042

[Lines 192–192](../../../../../tests/support/selection_exception_support.hpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::size_t, std::align_val_t) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0043

[Lines 193–193](../../../../../tests/support/selection_exception_support.hpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::size_t, std::align_val_t) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0044

[Lines 194–194](../../../../../tests/support/selection_exception_support.hpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* p, std::align_val_t, const std::nothrow_t&) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0045

[Lines 195–195](../../../../../tests/support/selection_exception_support.hpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete[](void* p, std::align_val_t, const std::nothrow_t&) noexcept { c05_fault::release(p); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide compatible global delete overload for the executable allocation seam. |
| inputs / outputs | Forwards pointer to c05_fault::release; sized/aligned/nothrow tags are intentionally ignored after allocation dispatch. |
| invariants | Pointer must belong to compatible malloc/aligned_alloc-backed replacement storage. This does not override placement delete or change object lifetime rules. |
| ownership | Releases raw allocation after any required object destructor; no query/account owner is retained. |
| failure | Declared noexcept; no failure injection on release, retry or handler. |
| cost | One nonallocating release dispatch plus actual free cost; calls counters do not decrement and do not become live allocation counts. |
| Design | [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp), [tests/support/selection_fixture.hpp](../../../../../tests/support/selection_fixture.hpp), [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [tests/unit/selection_normalized_exception_test.cpp](../../../../../tests/unit/selection_normalized_exception_test.cpp), [src/planner/selection_detail.hpp](../../../../../src/planner/selection_detail.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |
