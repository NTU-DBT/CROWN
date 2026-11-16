# `tests/unit/json_cleanup_test.cpp` — block usage map

[Source](../../../../../tests/unit/json_cleanup_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `240a7bcb3941fc61b26aa052b0ece31156b7ee90a4cb61f0ef949863818ee177`. 586 lines partitioned into 81 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–34](../../../../../tests/unit/json_cleanup_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 35–38](../../../../../tests/unit/json_cleanup_test.cpp#L35) | Member/declaration region. |  · [reviewed contract](#b0002) |
| [B0003 · 39–63](../../../../../tests/unit/json_cleanup_test.cpp#L39) | Callable definition: bool before_new() noexcept | calls fetch_add, load, compare_exchange_weak; returns false; true; 1 loop sites · [reviewed contract](#b0003) |
| [B0004 · 64–64](../../../../../tests/unit/json_cleanup_test.cpp#L64) | Explanatory comments or spacing. |  |
| [B0005 · 65–71](../../../../../tests/unit/json_cleanup_test.cpp#L65) | Callable definition: void allocation_succeeded() noexcept | calls fetch_add, load · [reviewed contract](#b0005) |
| [B0006 · 72–72](../../../../../tests/unit/json_cleanup_test.cpp#L72) | Explanatory comments or spacing. |  |
| [B0007 · 73–79](../../../../../tests/unit/json_cleanup_test.cpp#L73) | Callable definition: void deallocated() noexcept | calls fetch_add, fetch_sub, load · [reviewed contract](#b0007) |
| [B0008 · 80–80](../../../../../tests/unit/json_cleanup_test.cpp#L80) | Explanatory comments or spacing. |  |
| [B0009 · 81–86](../../../../../tests/unit/json_cleanup_test.cpp#L81) | Type/record definition: struct Counts |  · [reviewed contract](#b0009) |
| [B0010 · 87–87](../../../../../tests/unit/json_cleanup_test.cpp#L87) | Explanatory comments or spacing. |  |
| [B0011 · 88–93](../../../../../tests/unit/json_cleanup_test.cpp#L88) | Type/record definition: struct Window |  · [reviewed contract](#b0011) |
| [B0012 · 94–94](../../../../../tests/unit/json_cleanup_test.cpp#L94) | Explanatory comments or spacing. |  |
| [B0013 · 95–100](../../../../../tests/unit/json_cleanup_test.cpp#L95) | Callable definition: Counts counts() noexcept | calls load; returns {total_successful_allocations.load(std::memory_order_relaxed), · [reviewed contract](#b0013) |
| [B0014 · 101–101](../../../../../tests/unit/json_cleanup_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0015 · 102–107](../../../../../tests/unit/json_cleanup_test.cpp#L102) | Callable definition: Window window() noexcept | calls load; returns {cleanup_new_attempts.load(std::memory_order_relaxed), · [reviewed contract](#b0015) |
| [B0016 · 108–108](../../../../../tests/unit/json_cleanup_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0017 · 109–115](../../../../../tests/unit/json_cleanup_test.cpp#L109) | Callable definition: void begin_cleanup_window() noexcept | calls store · [reviewed contract](#b0017) |
| [B0018 · 116–116](../../../../../tests/unit/json_cleanup_test.cpp#L116) | Explanatory comments or spacing. |  |
| [B0019 · 117–119](../../../../../tests/unit/json_cleanup_test.cpp#L117) | Callable definition: void end_cleanup_window() noexcept | calls store · [reviewed contract](#b0019) |
| [B0020 · 120–120](../../../../../tests/unit/json_cleanup_test.cpp#L120) | Explanatory comments or spacing. |  |
| [B0021 · 121–124](../../../../../tests/unit/json_cleanup_test.cpp#L121) | Callable definition: void fail_after(Counter allowed) noexcept | calls store · [reviewed contract](#b0021) |
| [B0022 · 125–125](../../../../../tests/unit/json_cleanup_test.cpp#L125) | Explanatory comments or spacing. |  |
| [B0023 · 126–128](../../../../../tests/unit/json_cleanup_test.cpp#L126) | Callable definition: void stop_failure() noexcept | calls store · [reviewed contract](#b0023) |
| [B0024 · 129–133](../../../../../tests/unit/json_cleanup_test.cpp#L129) | Closes surrounding scope/type. | source comment (unverified): // namespace cleanup_probe · [reviewed contract](#b0024) |
| [B0025 · 134–144](../../../../../tests/unit/json_cleanup_test.cpp#L134) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t size) | calls cleanup_probe::before_new, std::malloc, cleanup_probe::allocation_succeeded; returns result; growth malloc, new; source comment (unverified): // Keep the replacement allocation pair opaque to optimized caller analysis, · [reviewed contract](#b0025) |
| [B0026 · 145–145](../../../../../tests/unit/json_cleanup_test.cpp#L145) | Explanatory comments or spacing. |  |
| [B0027 · 146–148](../../../../../tests/unit/json_cleanup_test.cpp#L146) | Callable definition: void* operator new\[\](std::size_t size) | calls ; returns ::operator new(size); growth new · [reviewed contract](#b0027) |
| [B0028 · 149–149](../../../../../tests/unit/json_cleanup_test.cpp#L149) | Explanatory comments or spacing. |  |
| [B0029 · 150–170](../../../../../tests/unit/json_cleanup_test.cpp#L150) | Callable definition: \[\[gnu::noinline\]\] void* operator new(std::size_t size, std::align_val_t alignment) | calls cleanup_probe::before_new, max, std::aligned_alloc, cleanup_probe::allocation_succeeded; returns result; growth new · [reviewed contract](#b0029) |
| [B0030 · 171–171](../../../../../tests/unit/json_cleanup_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0031 · 172–174](../../../../../tests/unit/json_cleanup_test.cpp#L172) | Callable definition: void* operator new\[\](std::size_t size, std::align_val_t alignment) | calls ; returns ::operator new(size, alignment); growth new · [reviewed contract](#b0031) |
| [B0032 · 175–175](../../../../../tests/unit/json_cleanup_test.cpp#L175) | Explanatory comments or spacing. |  |
| [B0033 · 176–181](../../../../../tests/unit/json_cleanup_test.cpp#L176) | Callable definition: \[\[gnu::noinline\]\] void operator delete(void* pointer) noexcept | calls cleanup_probe::deallocated, std::free · [reviewed contract](#b0033) |
| [B0034 · 182–182](../../../../../tests/unit/json_cleanup_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0035 · 183–185](../../../../../tests/unit/json_cleanup_test.cpp#L183) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0035) |
| [B0036 · 186–186](../../../../../tests/unit/json_cleanup_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0037 · 187–189](../../../../../tests/unit/json_cleanup_test.cpp#L187) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0037) |
| [B0038 · 190–190](../../../../../tests/unit/json_cleanup_test.cpp#L190) | Explanatory comments or spacing. |  |
| [B0039 · 191–193](../../../../../tests/unit/json_cleanup_test.cpp#L191) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0039) |
| [B0040 · 194–194](../../../../../tests/unit/json_cleanup_test.cpp#L194) | Explanatory comments or spacing. |  |
| [B0041 · 195–197](../../../../../tests/unit/json_cleanup_test.cpp#L195) | Callable definition: void operator delete(void* pointer, std::align_val_t) noexcept | calls  · [reviewed contract](#b0041) |
| [B0042 · 198–198](../../../../../tests/unit/json_cleanup_test.cpp#L198) | Explanatory comments or spacing. |  |
| [B0043 · 199–201](../../../../../tests/unit/json_cleanup_test.cpp#L199) | Callable definition: void operator delete\[\](void* pointer, std::align_val_t) noexcept | calls  · [reviewed contract](#b0043) |
| [B0044 · 202–202](../../../../../tests/unit/json_cleanup_test.cpp#L202) | Explanatory comments or spacing. |  |
| [B0045 · 203–205](../../../../../tests/unit/json_cleanup_test.cpp#L203) | Callable definition: void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0045) |
| [B0046 · 206–206](../../../../../tests/unit/json_cleanup_test.cpp#L206) | Explanatory comments or spacing. |  |
| [B0047 · 207–209](../../../../../tests/unit/json_cleanup_test.cpp#L207) | Callable definition: void operator delete\[\](void* pointer, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0047) |
| [B0048 · 210–212](../../../../../tests/unit/json_cleanup_test.cpp#L210) | declares namespace scope. |  · [reviewed contract](#b0048) |
| [B0049 · 213–230](../../../../../tests/unit/json_cleanup_test.cpp#L213) | Type/record definition: template &lt;class T&gt; class ProbeAllocator | returns std::allocator&lt;T&gt;{}.allocate(count); growth allocate · [reviewed contract](#b0049) |
| [B0050 · 231–231](../../../../../tests/unit/json_cleanup_test.cpp#L231) | Explanatory comments or spacing. |  |
| [B0051 · 232–235](../../../../../tests/unit/json_cleanup_test.cpp#L232) | Callable definition: template &lt;class T, class U&gt; bool operator==(const ProbeAllocator&lt;T&gt;&, const ProbeAllocator&lt;U&gt;&) noexcept | returns true · [reviewed contract](#b0051) |
| [B0052 · 236–236](../../../../../tests/unit/json_cleanup_test.cpp#L236) | Explanatory comments or spacing. |  |
| [B0053 · 237–240](../../../../../tests/unit/json_cleanup_test.cpp#L237) | Callable definition: template &lt;class T, class U&gt; bool operator!=(const ProbeAllocator&lt;T&gt;&, const ProbeAllocator&lt;U&gt;&) noexcept | returns false · [reviewed contract](#b0053) |
| [B0054 · 241–258](../../../../../tests/unit/json_cleanup_test.cpp#L241) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0054) |
| [B0055 · 259–270](../../../../../tests/unit/json_cleanup_test.cpp#L259) | Type/record definition: enum class Shape : std::uint8_t |  · [reviewed contract](#b0055) |
| [B0056 · 271–282](../../../../../tests/unit/json_cleanup_test.cpp#L271) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0056) |
| [B0057 · 283–307](../../../../../tests/unit/json_cleanup_test.cpp#L283) | Callable definition: constexpr std::string_view shape_name(Shape shape) noexcept | calls ; returns @; @ · [reviewed contract](#b0057) |
| [B0058 · 308–308](../../../../../tests/unit/json_cleanup_test.cpp#L308) | Explanatory comments or spacing. |  |
| [B0059 · 309–317](../../../../../tests/unit/json_cleanup_test.cpp#L309) | Callable definition: template &lt;class Json&gt; Json make_binary() | calls reserve, push_back, Json, Json::binary; returns Json(Json::binary(std::move(bytes))); growth push_back, reserve; 1 loop sites · [reviewed contract](#b0059) |
| [B0060 · 318–318](../../../../../tests/unit/json_cleanup_test.cpp#L318) | Explanatory comments or spacing. |  |
| [B0061 · 319–408](../../../../../tests/unit/json_cleanup_test.cpp#L319) | Callable definition: template &lt;class Json&gt; Json make_case(Shape shape) | calls Json, std::string, Json::array, push_back; returns Json{}; Json(std::uint64_t{42}); growth push_back; 8 loop sites · [reviewed contract](#b0061) |
| [B0062 · 409–409](../../../../../tests/unit/json_cleanup_test.cpp#L409) | Explanatory comments or spacing. |  |
| [B0063 · 410–415](../../../../../tests/unit/json_cleanup_test.cpp#L410) | Callable definition: void prime_output(const DefaultJson& value, Shape shape) | calls dump, size · [reviewed contract](#b0063) |
| [B0064 · 416–416](../../../../../tests/unit/json_cleanup_test.cpp#L416) | Explanatory comments or spacing. |  |
| [B0065 · 417–423](../../../../../tests/unit/json_cleanup_test.cpp#L417) | Callable definition: template &lt;class Json&gt; void prime_output(const Json& value, Shape shape) | calls dump, size · [reviewed contract](#b0065) |
| [B0066 · 424–424](../../../../../tests/unit/json_cleanup_test.cpp#L424) | Explanatory comments or spacing. |  |
| [B0067 · 425–436](../../../../../tests/unit/json_cleanup_test.cpp#L425) | Type/record definition: struct CaseOutcome |  · [reviewed contract](#b0067) |
| [B0068 · 437–437](../../../../../tests/unit/json_cleanup_test.cpp#L437) | Explanatory comments or spacing. |  |
| [B0069 · 438–446](../../../../../tests/unit/json_cleanup_test.cpp#L438) | Callable definition: bool balanced(const Counts& before, const Counts& after) noexcept | calls ; returns false; after.live == before.live && · [reviewed contract](#b0069) |
| [B0070 · 447–447](../../../../../tests/unit/json_cleanup_test.cpp#L447) | Explanatory comments or spacing. |  |
| [B0071 · 448–517](../../../../../tests/unit/json_cleanup_test.cpp#L448) | Callable definition: template &lt;class Json&gt; CaseOutcome run_case(Shape shape) | calls counts, emplace, prime_output, begin_cleanup_window; returns outcome; outcome; growth emplace; 1 loop sites · [reviewed contract](#b0071) |
| [B0072 · 518–518](../../../../../tests/unit/json_cleanup_test.cpp#L518) | Explanatory comments or spacing. |  |
| [B0073 · 519–540](../../../../../tests/unit/json_cleanup_test.cpp#L519) | Callable definition: template &lt;class Json&gt; bool cleanup_type(std::string_view label, Counter& cases, Counter& points) | calls shape_name; returns valid; 1 loop sites · [reviewed contract](#b0073) |
| [B0074 · 541–541](../../../../../tests/unit/json_cleanup_test.cpp#L541) | Explanatory comments or spacing. |  |
| [B0075 · 542–554](../../../../../tests/unit/json_cleanup_test.cpp#L542) | Callable definition: template &lt;class Json&gt; void serialize_type(std::string_view label) | calls dump, shape_name, size, write; 1 loop sites · [reviewed contract](#b0075) |
| [B0076 · 555–555](../../../../../tests/unit/json_cleanup_test.cpp#L555) | Explanatory comments or spacing. |  |
| [B0077 · 556–561](../../../../../tests/unit/json_cleanup_test.cpp#L556) | Callable definition: int serialize_all() | calls ; returns std::cout ? 0 : 2 · [reviewed contract](#b0077) |
| [B0078 · 562–562](../../../../../tests/unit/json_cleanup_test.cpp#L562) | Explanatory comments or spacing. |  |
| [B0079 · 563–573](../../../../../tests/unit/json_cleanup_test.cpp#L563) | Callable definition: int cleanup_all() | calls ; returns valid ? 0 : 1 · [reviewed contract](#b0079) |
| [B0080 · 574–576](../../../../../tests/unit/json_cleanup_test.cpp#L574) | Closes surrounding scope/type. | source comment (unverified): // namespace cleanup_probe · [reviewed contract](#b0080) |
| [B0081 · 577–586](../../../../../tests/unit/json_cleanup_test.cpp#L577) | Callable definition: int main(int argc, char** argv) | calls std::strcmp, cleanup_probe::serialize_all, cleanup_probe::cleanup_all; returns cleanup_probe::serialize_all(); cleanup_probe::cleanup_all() · [reviewed contract](#b0081) |

## B0001

[Lines 1–34](../../../../../tests/unit/json_cleanup_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L34:sha256:762fa2c16da99b2d0571b5d15659d72ca1e491b8274483db59fc942f446501a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare json_cleanup_test.cpp: include &lt;array&gt;, &lt;atomic&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;cstring&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;map&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;, &lt;vector&gt;, &lt;nlohmann/json.hpp&gt;; bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. Atomic counter storage and later atomic accesses belong to the test probe, not an engine timing or allocation measure. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 35–38](../../../../../tests/unit/json_cleanup_test.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L38:sha256:bdd33329a5239264934b7fcee47994cdf84b7da694e6d140c36d675c54521acd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare json_cleanup_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. Atomic counter storage and later atomic accesses belong to the test probe, not an engine timing or allocation measure. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 39–63](../../../../../tests/unit/json_cleanup_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool before_new() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Increment global allocation-attempt counters, optionally cleanup-window counters, and fail persistently once allowed new requests are exhausted. |
| inputs / outputs | Declaration: \`bool before_new() noexcept\`. Inputs/outputs in this selected body: Increment global allocation-attempt counters, optionally cleanup-window counters, and fail persistently once allowed new requests are exhausted. |
| invariants | When injection is enabled, the failure condition applies at and after the configured attempt; atomics are local probe counters, not a general allocator census. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0005

[Lines 65–71](../../../../../tests/unit/json_cleanup_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void allocation_succeeded() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count successful replacement allocations and live-allocation delta, including cleanup-window successes when enabled. |
| inputs / outputs | Declaration: \`void allocation_succeeded() noexcept\`. Inputs/outputs in this selected body: Count successful replacement allocations and live-allocation delta, including cleanup-window successes when enabled. |
| invariants | Counts only successful calls through directly replaced global-new forms and deletes that route to this replacement. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0007

[Lines 73–79](../../../../../tests/unit/json_cleanup_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void deallocated() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count a non-null replacement delete as deallocation and decrement live count. |
| inputs / outputs | Declaration: \`void deallocated() noexcept\`. Inputs/outputs in this selected body: Count a non-null replacement delete as deallocation and decrement live count. |
| invariants | Non-null pointers only affect deallocation/live counters; direct free outside replacement is not observed. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0009

[Lines 81–86](../../../../../tests/unit/json_cleanup_test.cpp#L81); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Counts {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold successful-allocation, deallocation, live and injected-failure counts. |
| inputs / outputs | Declaration: \`struct Counts\`. Inputs/outputs in this selected body: Hold successful-allocation, deallocation, live and injected-failure counts. |
| invariants | Counts are snapshots of global probe state; live is total live replacement allocations at that instant. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0011

[Lines 88–93](../../../../../tests/unit/json_cleanup_test.cpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Window {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold cleanup-window request, success, deallocation and injected-failure counts. |
| inputs / outputs | Declaration: \`struct Window\`. Inputs/outputs in this selected body: Hold cleanup-window request, success, deallocation and injected-failure counts. |
| invariants | Window counters are reset before each destruction window and observe only while flag is true. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0013

[Lines 95–100](../../../../../tests/unit/json_cleanup_test.cpp#L95); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Counts counts() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read global atomic allocation counters into Counts. |
| inputs / outputs | Declaration: \`Counts counts() noexcept\`. Inputs/outputs in this selected body: Read global atomic allocation counters into Counts. |
| invariants | No allocation and relaxed atomic reads only. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0015

[Lines 102–107](../../../../../tests/unit/json_cleanup_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Window window() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read cleanup-window atomic counters into Window. |
| inputs / outputs | Declaration: \`Window window() noexcept\`. Inputs/outputs in this selected body: Read cleanup-window atomic counters into Window. |
| invariants | No allocation and relaxed atomic reads only. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0017

[Lines 109–115](../../../../../tests/unit/json_cleanup_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void begin_cleanup_window() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset cleanup counters and enable cleanup-only observation. |
| inputs / outputs | Declaration: \`void begin_cleanup_window() noexcept\`. Inputs/outputs in this selected body: Reset cleanup counters and enable cleanup-only observation. |
| invariants | No allocation; scope begins before destructor only in run_case. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0019

[Lines 117–119](../../../../../tests/unit/json_cleanup_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void end_cleanup_window() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable cleanup-window observation. |
| inputs / outputs | Declaration: \`void end_cleanup_window() noexcept\`. Inputs/outputs in this selected body: Disable cleanup-window observation. |
| invariants | No allocation; called after destructor and failure scope finishes. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0021

[Lines 121–124](../../../../../tests/unit/json_cleanup_test.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fail_after(Counter allowed) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set persistent failure after the requested number of new attempts. |
| inputs / outputs | Declaration: \`void fail_after(Counter allowed) noexcept\`. Inputs/outputs in this selected body: Set persistent failure after the requested number of new attempts. |
| invariants | Failure remains active until explicit stop_failure; subsequent global-new calls fail as well. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0023

[Lines 126–128](../../../../../tests/unit/json_cleanup_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stop_failure() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable allocation failure injection. |
| inputs / outputs | Declaration: \`void stop_failure() noexcept\`. Inputs/outputs in this selected body: Disable allocation failure injection. |
| invariants | Does not reset counters or fail index; it only disarms new injection. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0024

[Lines 129–133](../../../../../tests/unit/json_cleanup_test.cpp#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L129-L133:sha256:648661bff751dbe76734d157f157ed81619b81744c7540c6b80a83db8f5bbd89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in json_cleanup_test.cpp: namespace cleanup_probe. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 134–144](../../../../../tests/unit/json_cleanup_test.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t size) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept ordinary scalar global throwing new, use malloc/free accounting, and throw bad_alloc at the configured point or on malloc failure. |
| inputs / outputs | Declaration: \`\[\[gnu::noinline\]\] void* operator new(std::size_t size)\`. Inputs/outputs in this selected body: Intercept ordinary scalar global throwing new, use malloc/free accounting, and throw bad_alloc at the configured point or on malloc failure. |
| invariants | Failpoint runs before backing malloc; ordinary scalar global new is directly replaced; backing malloc failure becomes bad_alloc. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Throws bad_alloc before malloc at the selected global-new point or if malloc fails. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0027

[Lines 146–148](../../../../../tests/unit/json_cleanup_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t size) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array replacement new through scalar replacement new. |
| inputs / outputs | Declaration: \`void* operator new\[\](std::size_t size)\`. Inputs/outputs in this selected body: Route ordinary array replacement new through scalar replacement new. |
| invariants | Array requests that delegate to this symbol share same probe; unknown library delegation is not asserted as coverage. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0029

[Lines 150–170](../../../../../tests/unit/json_cleanup_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* operator new(std::size_t size, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept aligned scalar global throwing new, round allocation size to alignment and use aligned_alloc. |
| inputs / outputs | Declaration: \`\[\[gnu::noinline\]\] void* operator new(std::size_t size, std::align_val_t alignment)\`. Inputs/outputs in this selected body: Intercept aligned scalar global throwing new, round allocation size to alignment and use aligned_alloc. |
| invariants | Aligned replacement is directly defined and failpoint runs before aligned_alloc; overflow rounding also throws bad_alloc. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Throws bad_alloc before aligned_alloc, on size-rounding overflow, or if aligned_alloc fails. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0031

[Lines 172–174](../../../../../tests/unit/json_cleanup_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t size, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned array replacement new through scalar aligned replacement new. |
| inputs / outputs | Declaration: \`void* operator new\[\](std::size_t size, std::align_val_t alignment)\`. Inputs/outputs in this selected body: Route aligned array replacement new through scalar aligned replacement new. |
| invariants | Aligned array routes through aligned scalar replacement. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0033

[Lines 176–181](../../../../../tests/unit/json_cleanup_test.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void operator delete(void* pointer) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free non-null global-new storage and update counters. |
| inputs / outputs | Declaration: \`\[\[gnu::noinline\]\] void operator delete(void* pointer) noexcept\`. Inputs/outputs in this selected body: Free non-null global-new storage and update counters. |
| invariants | This is ordinary scalar delete and ignores null; aligned overloads are separate, and custom deallocation not reaching replacement is outside counters. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0035

[Lines 183–185](../../../../../tests/unit/json_cleanup_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array delete through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer) noexcept\`. Inputs/outputs in this selected body: Route array delete through scalar delete. |
| invariants | Array delete delegates through this TU’s scalar replacement delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0037

[Lines 187–189](../../../../../tests/unit/json_cleanup_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route sized scalar delete through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete(void* pointer, std::size_t) noexcept\`. Inputs/outputs in this selected body: Route sized scalar delete through scalar delete. |
| invariants | Sized delete delegates through this TU’s scalar replacement delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0039

[Lines 191–193](../../../../../tests/unit/json_cleanup_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route sized array delete through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer, std::size_t) noexcept\`. Inputs/outputs in this selected body: Route sized array delete through scalar delete. |
| invariants | Sized array delete delegates through this TU’s scalar replacement delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0041

[Lines 195–197](../../../../../tests/unit/json_cleanup_test.cpp#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned scalar delete through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete(void* pointer, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Route aligned scalar delete through scalar delete. |
| invariants | Aligned delete delegates to scalar delete; total allocator behavior beyond replacement forms is not inferred. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0043

[Lines 199–201](../../../../../tests/unit/json_cleanup_test.cpp#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned array delete through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Route aligned array delete through scalar delete. |
| invariants | Aligned array delete delegates to scalar delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0045

[Lines 203–205](../../../../../tests/unit/json_cleanup_test.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route sized aligned scalar delete through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Route sized aligned scalar delete through scalar delete. |
| invariants | Sized aligned delete delegates to scalar delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0047

[Lines 207–209](../../../../../tests/unit/json_cleanup_test.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route sized aligned array delete through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer, std::size_t, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Route sized aligned array delete through scalar delete. |
| invariants | Sized aligned array delete delegates to scalar delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0048

[Lines 210–212](../../../../../tests/unit/json_cleanup_test.cpp#L210); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L210-L212:sha256:b5c35069fa355a7a08f831b5b75a88d3e55bb6034cc545cd8c5b707bd702193e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare json_cleanup_test.cpp: declare the recorded helper API/type boundary. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0049

[Lines 213–230](../../../../../tests/unit/json_cleanup_test.cpp#L213); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class T>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a stateless standard allocator adapter for the custom JSON vector type. |
| inputs / outputs | Declaration: \`template &lt;class T&gt; class ProbeAllocator\`. Inputs/outputs in this selected body: Define a stateless standard allocator adapter for the custom JSON vector type. |
| invariants | Custom vector allocator delegates allocation/deallocation to std::allocator; there is no independent accounting layer in ProbeAllocator. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0051

[Lines 232–235](../../../../../tests/unit/json_cleanup_test.cpp#L232); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class T, class U>
bool operator==(const ProbeAllocator<T>&, const ProbeAllocator<U>&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare allocator instances as always equal. |
| inputs / outputs | Declaration: \`template &lt;class T, class U&gt; bool operator==(const ProbeAllocator&lt;T&gt;&, const ProbeAllocator&lt;U&gt;&) noexcept\`. Inputs/outputs in this selected body: Compare allocator instances as always equal. |
| invariants | Allocator equality has no state and always returns true. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0053

[Lines 237–240](../../../../../tests/unit/json_cleanup_test.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class T, class U>
bool operator!=(const ProbeAllocator<T>&, const ProbeAllocator<U>&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare allocator instances as never unequal. |
| inputs / outputs | Declaration: \`template &lt;class T, class U&gt; bool operator!=(const ProbeAllocator&lt;T&gt;&, const ProbeAllocator&lt;U&gt;&) noexcept\`. Inputs/outputs in this selected body: Compare allocator instances as never unequal. |
| invariants | Allocator inequality has no state and always returns false. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0054

[Lines 241–258](../../../../../tests/unit/json_cleanup_test.cpp#L241); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L241-L258:sha256:d745b909a8ddb1b07f475c1d5f24c33f47924d3931a61c99e3566d3bb8f88236
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the vector-derived ProbeArray JSON-test container, its inherited constructors/assignment and default constructor; object operations follow its selected allocator. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. The wrapper declaration creates no instance; instantiated vector/allocator operations define storage and failure behavior. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0055

[Lines 259–270](../../../../../tests/unit/json_cleanup_test.cpp#L259); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Shape : std::uint8_t {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the ten JSON fixture shapes used by cleanup and serialization fixtures, including deep_chain. |
| inputs / outputs | Declaration: \`enum class Shape : std::uint8_t\`. Inputs/outputs in this selected body: Name the ten JSON fixture shapes used by cleanup and serialization fixtures, including deep_chain. |
| invariants | The enum includes deep_chain; the adjacent serializable_shapes list separately omits it so dump does not become a second recursion-depth test. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0056

[Lines 271–282](../../../../../tests/unit/json_cleanup_test.cpp#L271); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L271-L282:sha256:0cc8613568be57765bda1c63232d8043d7b4543c04f672464087e1fdfdf27d25
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare json_cleanup_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0057

[Lines 283–307](../../../../../tests/unit/json_cleanup_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::string_view shape_name(Shape shape) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a fixed display label for each shape. |
| inputs / outputs | Declaration: \`constexpr std::string_view shape_name(Shape shape) noexcept\`. Inputs/outputs in this selected body: Return a fixed display label for each shape. |
| invariants | All ten enum values have one label; unknown fallthrough returns the literal fallback. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0059

[Lines 309–317](../../../../../tests/unit/json_cleanup_test.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Json>
Json make_binary() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a 2048-byte binary JSON value. |
| inputs / outputs | Declaration: \`template &lt;class Json&gt; Json make_binary()\`. Inputs/outputs in this selected body: Build a 2048-byte binary JSON value. |
| invariants | Bytes cycle through uint8 values modulo 256 and are moved into nlohmann binary. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0061

[Lines 319–408](../../../../../tests/unit/json_cleanup_test.cpp#L319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Json>
Json make_case(Shape shape) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one of ten scalar, binary, wide, growth, nested or 4096-deep JSON trees. |
| inputs / outputs | Declaration: \`template &lt;class Json&gt; Json make_case(Shape shape)\`. Inputs/outputs in this selected body: Construct one of ten scalar, binary, wide, growth, nested or 4096-deep JSON trees. |
| invariants | Finite fixed shape sizes: 512 wide entries, 96 long-key members, 4096 growth entries/depth, and 64 nested rows. Deep-chain destructor is exercised but dump is omitted. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Fixed JSON fixtures up to 4096 elements/depth; no production complexity evidence. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0063

[Lines 410–415](../../../../../tests/unit/json_cleanup_test.cpp#L410); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prime_output(const DefaultJson& value, Shape shape) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prime ordinary JSON output by dumping all but the deep recursive shape. |
| inputs / outputs | Declaration: \`void prime_output(const DefaultJson& value, Shape shape)\`. Inputs/outputs in this selected body: Prime ordinary JSON output by dumping all but the deep recursive shape. |
| invariants | No dump call for deep_chain; returned temporary string is discarded for other cases. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0065

[Lines 417–423](../../../../../tests/unit/json_cleanup_test.cpp#L417); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Json>
void prime_output(const Json& value, Shape shape) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prime custom-allocator JSON output by dumping all but the deep recursive shape. |
| inputs / outputs | Declaration: \`template &lt;class Json&gt; void prime_output(const Json& value, Shape shape)\`. Inputs/outputs in this selected body: Prime custom-allocator JSON output by dumping all but the deep recursive shape. |
| invariants | Same non-deep-chain output priming rule for custom allocator JSON. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0067

[Lines 425–436](../../../../../tests/unit/json_cleanup_test.cpp#L425); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CaseOutcome {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold pass/fault point and allocation/free/live restoration observations for one shape. |
| inputs / outputs | Declaration: \`struct CaseOutcome\`. Inputs/outputs in this selected body: Hold pass/fault point and allocation/free/live restoration observations for one shape. |
| invariants | Outcome stores counters/booleans only; no Json tree escapes this case. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0069

[Lines 438–446](../../../../../tests/unit/json_cleanup_test.cpp#L438); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool balanced(const Counts& before, const Counts& after) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare allocation/free balance and require the live allocation count to return to its pre-case value. |
| inputs / outputs | Declaration: \`bool balanced(const Counts& before, const Counts& after) noexcept\`. Inputs/outputs in this selected body: Compare allocation/free balance and require the live allocation count to return to its pre-case value. |
| invariants | Requires monotone success/free totals, equal live count, and equal deltas; does not detect allocations outside counted replacements. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0071

[Lines 448–517](../../../../../tests/unit/json_cleanup_test.cpp#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Json>
CaseOutcome run_case(Shape shape) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build and prime one JSON value, observe normal destructor cleanup, then sweep persistent global-new failures at every observed cleanup allocation point. |
| inputs / outputs | Declaration: \`template &lt;class Json&gt; CaseOutcome run_case(Shape shape)\`. Inputs/outputs in this selected body: Build and prime one JSON value, observe normal destructor cleanup, then sweep persistent global-new failures at every observed cleanup allocation point. |
| invariants | Normal destruction window counts global replacement-new calls/frees. Each fault point reconstructs before arming, then fails during destruction; failure remains armed until \`reset()\` returns. Checks one selected injected failure, no retry allocation, balance, live restoration; cap 64 and growth shapes require &gt;2 points. |
| ownership | Json tree exists only inside this call and is destroyed before return; returned outcome contains scalar counters/flags only. |
| failure | A throw escaping a noexcept JSON destructor would terminate; the expected probe behavior is one caught cleanup failure and no retry allocation. |
| cost | One normal cleanup plus at most 64 observed cleanup allocation positions per shape. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0073

[Lines 519–540](../../../../../tests/unit/json_cleanup_test.cpp#L519); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Json>
bool cleanup_type(std::string_view label, Counter& cases, Counter& points) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all ten cleanup shapes for one JSON implementation and print allocation/free/fault/live counters. |
| inputs / outputs | Declaration: \`template &lt;class Json&gt; bool cleanup_type(std::string_view label, Counter& cases, Counter& points)\`. Inputs/outputs in this selected body: Run all ten cleanup shapes for one JSON implementation and print allocation/free/fault/live counters. |
| invariants | Loops all ten shapes for each type; outputs diagnostic counts but does not itself compare serialized bytes. |
| ownership | Each Json value is local to one shape iteration; only aggregate counters are returned. |
| failure | Per-case invariant failure returns false and is aggregated; any unexpected exception propagates to the process. |
| cost | Ten shapes for one JSON implementation. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0075

[Lines 542–554](../../../../../tests/unit/json_cleanup_test.cpp#L542); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Json>
void serialize_type(std::string_view label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize all nine serializable shapes for one JSON implementation and omit the deep recursive shape. |
| inputs / outputs | Declaration: \`template &lt;class Json&gt; void serialize_type(std::string_view label)\`. Inputs/outputs in this selected body: Serialize all nine serializable shapes for one JSON implementation and omit the deep recursive shape. |
| invariants | Nine shapes only; output bytes/size are emitted, not compared inside this function. |
| ownership | Json tree and serialized string are local to each iteration. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Nine serializable shapes; deep-chain dump omitted. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0077

[Lines 556–561](../../../../../tests/unit/json_cleanup_test.cpp#L556); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int serialize_all() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize DefaultJson, ordered_json and custom-vector JSON fixtures. |
| inputs / outputs | Declaration: \`int serialize_all()\`. Inputs/outputs in this selected body: Serialize DefaultJson, ordered_json and custom-vector JSON fixtures. |
| invariants | Runs all nine serializable shapes for each of three JSON implementations and writes output; no byte equality check is inside this function. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | No custom runtime error translation; standard container/string/stream operations may throw, and the cleanup harness reports aggregate false on its named balance checks. |
| cost | Nine shapes for each of three implementations. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0079

[Lines 563–573](../../../../../tests/unit/json_cleanup_test.cpp#L563); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int cleanup_all() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run cleanup sweeps for all three JSON implementations and return failure if any case is unbalanced. |
| inputs / outputs | Declaration: \`int cleanup_all()\`. Inputs/outputs in this selected body: Run cleanup sweeps for all three JSON implementations and return failure if any case is unbalanced. |
| invariants | Runs 30 cleanup cases (10 shapes across 3 JSON implementations), combines their boolean results, and has no CROWN runtime calls. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Per-case invariant failure returns false and is aggregated; any unexpected exception propagates to the process. |
| cost | Thirty cleanup cases: ten shapes per implementation. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0080

[Lines 574–576](../../../../../tests/unit/json_cleanup_test.cpp#L574); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L574-L576:sha256:9c5f35e174d9cb5c7712bc0056efc59a8c2142822125aaa1fb02fc5e9cedb02d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in json_cleanup_test.cpp: namespace cleanup_probe. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0081

[Lines 577–586](../../../../../tests/unit/json_cleanup_test.cpp#L577); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc, char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch only the explicit --serialize or --cleanup command-line modes. |
| inputs / outputs | Declaration: \`int main(int argc, char** argv)\`. Inputs/outputs in this selected body: Dispatch only the explicit --serialize or --cleanup command-line modes. |
| invariants | CLI requires exactly one recognized flag; unknown usage returns 2. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | The driver catches documented exceptions, prints a diagnostic and returns a nonzero status. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/json_cleanup_test.cpp](../../../../../tests/unit/json_cleanup_test.cpp), [tools/verify_json_cleanup.py](../../../../../tools/verify_json_cleanup.py), [docs/verification/c02-json-cleanup-tests-proposal/README.md](../../../../verification/c02-json-cleanup-tests-proposal/README.md), [CMakeLists.txt](../../../../../CMakeLists.txt) |
