# `tests/unit/maintenance_cost_fit_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fd1e0f79cb77fc15aaac015ae6192e2aadee2800f241545fb756714a023cb1ea`. 291 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Persistent allocation failures for the public calibration factories. · [reviewed contract](#b0001) |
| [B0002 · 22–33](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L22) | Callable definition: \[\[gnu::noinline\]\] void* allocate(std::size_t bytes) | calls std::malloc; returns pointer; growth allocate, malloc; source comment (unverified): // Keep failing every later allocation after the selected position. This · [reviewed contract](#b0002) |
| [B0003 · 34–34](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0004 · 35–44](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L35) | Type/record definition: struct Fault |  · [reviewed contract](#b0004) |
| [B0005 · 45–46](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L45) | Closes surrounding scope/type. | source comment (unverified): // namespace c03_fit_fault · [reviewed contract](#b0005) |
| [B0006 · 47–47](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L47) | Callable definition: void* operator new(std::size_t bytes) | calls c03_fit_fault::allocate; returns c03_fit_fault::allocate(bytes); growth allocate, new · [reviewed contract](#b0006) |
| [B0007 · 48–48](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L48) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns c03_fit_fault::allocate(bytes); growth allocate, new · [reviewed contract](#b0007) |
| [B0008 · 49–51](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L49) | Callable definition: void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept | calls c03_fit_fault::allocate; returns c03_fit_fault::allocate(bytes); nullptr; growth allocate, new · [reviewed contract](#b0008) |
| [B0009 · 52–54](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L52) | Callable definition: void* operator new\[\](std::size_t bytes, const std::nothrow_t&) noexcept | calls ; returns c03_fit_fault::allocate(bytes); nullptr; growth allocate, new · [reviewed contract](#b0009) |
| [B0010 · 55–55](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L55) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 56–56](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L56) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 57–57](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L57) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0012) |
| [B0013 · 58–58](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L58) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0013) |
| [B0014 · 59–59](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L59) | Callable definition: void operator delete(void* pointer, const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 60–60](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L60) | Callable definition: void operator delete\[\](void* pointer, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 61–66](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L61) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0016) |
| [B0017 · 67–69](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L67) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0017) |
| [B0018 · 70–70](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L70) | Explanatory comments or spacing. |  |
| [B0019 · 71–76](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L71) | Callable definition: bool same_fit_options(const model::FitOptions& left, const model::FitOptions& right) | calls ; returns left.max_iterations == right.max_iterations && · [reviewed contract](#b0019) |
| [B0020 · 77–77](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L77) | Explanatory comments or spacing. |  |
| [B0021 · 78–85](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L78) | Type/record definition: struct CalibrationImage |  · [reviewed contract](#b0021) |
| [B0022 · 86–86](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L86) | Explanatory comments or spacing. |  |
| [B0023 · 87–100](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L87) | Callable definition: CalibrationImage image_of(const model::Calibration& value, std::string_view context, std::string_view backend) | calls coefficients, fit_summary, origin, fit_observations; guard check(raw.size() &lt;= result.observations.size(), "fixture raw observations exceed image capacity");; returns result; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 101–101](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0025 · 102–133](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L102) | Callable definition: bool same_calibration(const model::Calibration& value, const CalibrationImage& expected) | calls context, backend, origin, fit_summary; returns false; false; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 134–134](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L134) | Explanatory comments or spacing. |  |
| [B0027 · 135–147](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L135) | Callable definition: template &lt;class Invoke, class Verify&gt; std::size_t count_successful_allocations(const Account& account, const crown::resource::Mem… | calls invoke, verify, check, reset; guard check(count &gt; 0 && count &lt; 4096, "calibration fault sweep allocation count outside guard");; returns count · [reviewed contract](#b0027) |
| [B0028 · 148–148](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L148) | Explanatory comments or spacing. |  |
| [B0029 · 149–184](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L149) | Callable definition: template &lt;class Invoke, class Verify&gt; std::size_t sweep(const Account& account, const model::Calibration& retained, const Calibra… | calls statistics, count_successful_allocations, fault, invoke; guard check(triggered && attempted_allocations &gt;= position + 1,; returns positions; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 185–185](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L185) | Explanatory comments or spacing. |  |
| [B0031 · 186–199](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L186) | Callable definition: std::array&lt;model::FitObservation, 4&gt; fit_observations() | calls ; returns result; source comment (unverified): // 2*5 + 3*2 + 1*7 · [reviewed contract](#b0031) |
| [B0032 · 200–200](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L200) | Explanatory comments or spacing. |  |
| [B0033 · 201–206](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L201) | Callable definition: std::array&lt;model::CalibrationSample, 4&gt; isolated_samples() | calls ; returns {{{model::Component::base_input, 2, 4}, · [reviewed contract](#b0033) |
| [B0034 · 207–207](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0035 · 208–246](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L208) | Callable definition: void fit_faults() | calls Account::create, context, backend, fit_observations; guard check(first.stop == pr::Stop::complete && first.calibration,; returns model::fit(account, context, backend, observations); 1 loop sites; source comment (unverified): // Both names exceed common SBO capacities. · [reviewed contract](#b0035) |
| [B0036 · 247–247](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L247) | Explanatory comments or spacing. |  |
| [B0037 · 248–280](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L248) | Callable definition: void isolated_calibration_faults() | calls Account::create, context, backend, isolated_samples; guard check(first.stop == pr::Stop::complete && first.calibration,; returns model::calibrate(account, context, backend, samples); source comment (unverified): // Force both owned strings to allocate. · [reviewed contract](#b0037) |
| [B0038 · 281–282](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L281) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0038) |
| [B0039 · 283–291](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L283) | Callable definition: int main() | calls fit_faults, isolated_calibration_faults, what; returns 1 · [reviewed contract](#b0039) |

## B0001

[Lines 1–21](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:cba424c4bae8af3bd9712d8e9fb5749b179e01dd0ec9867aaafe3c2e1b2b53b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare maintenance_cost_fit_exception_test.cpp: include "crown/resource/memory.hpp", "crown/runtime/maintenance_cost.hpp", &lt;array&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;utility&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 22–33](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* allocate(std::size_t bytes) {
  ++allocations;
  // Keep failing every later allocation after the selected position. This
  // detects a catch-and-continue path that would otherwise hide partial work.
  if (fail_after == 0) {
    triggered = true;
    throw std::bad_alloc{};
  }
  if (fail_after > 0) --fail_after;
  if (void* pointer = std::malloc(bytes ? bytes : 1)) return pointer;
  throw std::bad_alloc{};
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count replacement allocation attempts and persistently fail from a selected index. |
| inputs / outputs | Increments the thread-local allocation attempt counter, persistently throws once fail_after reaches zero, otherwise decrements positive fail_after and delegates bytes (or 1 for zero) to malloc. |
| invariants | The selected position triggers bad_alloc and leaves fail_after at zero, so every later allocation attempt in that Fault scope also fails. |
| ownership | Returns malloc storage to the corresponding replacement new; no memory-account ownership is implied by this hook. |
| failure | Throws std::bad_alloc on selected fault or malloc failure. This function does not catch its throwing form. |
| cost | One TLS counter update and one fault check per hooked new call, then one malloc on allowed calls. Counter means attempt positions, not byte totals, RSS, or complete allocator interception. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0004

[Lines 35–44](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fault {
  explicit Fault(std::size_t position) {
    allocations = 0;
    triggered = false;
    fail_after = static_cast<std::ptrdiff_t>(position);
  }
  ~Fault() { fail_after = -1; }
  Fault(const Fault&) = delete;
  Fault& operator=(const Fault&) = delete;
};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | RAII guard for one persistent allocation-failure position. |
| inputs / outputs | Fault(position) resets allocations and triggered and sets fail_after; its destructor sets fail_after back to -1. Copy operations are deleted. |
| invariants | Failure remains active at and after the selected position for the scope; nested Fault use is not detected or prohibited by this type. |
| ownership | RAII object mutates thread-local c03_fit_fault state; it owns no allocation result. |
| failure | Construction only casts the selected position to ptrdiff_t; no exception handling is added. A bad cast domain is not tested. |
| cost | Fixed TLS assignments on construction/destruction. It does not perform the factory call itself. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0005

[Lines 45–46](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L45); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L46:sha256:b6a3459adae0aeff469f054560f8a53daea6ae985a103e9554ef9675a5250f15
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in maintenance_cost_fit_exception_test.cpp: namespace c03_fit_fault. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 47–47](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return c03_fit_fault::allocate(bytes); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replacement scalar throwing operator new. |
| inputs / outputs | Implements ordinary scalar throwing operator new by directly returning c03_fit_fault::allocate(bytes). |
| invariants | Every selected call contributes one attempt to the test hook; an allowed call returns malloc-backed storage. |
| ownership | Returned raw storage belongs to the caller until a matching delete replacement frees it. |
| failure | Propagates std::bad_alloc from persistent injection or malloc failure, as required for throwing new. |
| cost | One hook invocation and possible malloc. This translation unit defines no aligned replacements; that fact alone does not establish which unlisted allocation overloads delegate to these hooks. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0007

[Lines 48–48](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return c03_fit_fault::allocate(bytes); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replacement array throwing operator new. |
| inputs / outputs | Implements ordinary array throwing operator new\[\] by passing bytes to the same persistent c03_fit_fault allocator. |
| invariants | Array allocation calls share the scalar hook’s TLS attempt sequence and selected failure point. |
| ownership | Returned raw storage is released through an array delete replacement in this TU. |
| failure | Propagates bad_alloc when injected or when malloc fails. |
| cost | One hook call and possible malloc; no array element construction/destruction cost is part of operator new\[\] itself. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0008

[Lines 49–51](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return c03_fit_fault::allocate(bytes); } catch (...) { return nullptr; }
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replacement scalar nothrow operator new. |
| inputs / outputs | Implements ordinary scalar nothrow operator new by trying c03_fit_fault::allocate(bytes) and catching all exceptions to return nullptr. |
| invariants | The hook still increments attempts and sets triggered before the catch when the chosen fault fires. |
| ownership | A non-null raw region is returned to the caller; nullptr represents any caught allocation exception. |
| failure | No exception escapes this noexcept replacement; every exception is translated to nullptr. |
| cost | One hook call and catch boundary; selected by nothrow scalar allocation. It does not define aligned forms. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0009

[Lines 52–54](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
  try { return c03_fit_fault::allocate(bytes); } catch (...) { return nullptr; }
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replacement array nothrow operator new. |
| inputs / outputs | Implements ordinary array nothrow operator new\[\] with the same allocate call and catch-all-to-null behavior. |
| invariants | Array attempts share the same TLS counter/fail position as other ordinary hooked new calls. |
| ownership | A successful pointer is caller-owned until matching array delete; null indicates caught failure. |
| failure | No exception escapes; all exceptions become nullptr. |
| cost | One hook call and catch boundary, with malloc only when allowed. No array object lifecycle or aligned overload is measured here. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0010

[Lines 55–55](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matching scalar delete through free. |
| inputs / outputs | Implements scalar delete by passing the pointer directly to std::free. |
| invariants | It does not alter allocation counters, triggered state, or fail_after. |
| ownership | Releases storage from the test hook; null is accepted by free. |
| failure | Declared noexcept and catches nothing; free is the only operation. |
| cost | One free call. Deallocation is not an injected allocation position. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0011

[Lines 56–56](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matching array delete through free. |
| inputs / outputs | Implements array delete by calling std::free(pointer). |
| invariants | Uses the same malloc/free pairing as this TU’s replacement new\[\]. |
| ownership | Releases the caller’s array-allocation region; no element destructors are invoked by this function body. |
| failure | Declared noexcept; there is no exception translation or counter mutation. |
| cost | One free call and no fault-counter work. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0012

[Lines 57–57](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sized scalar delete through free. |
| inputs / outputs | Provides the sized scalar delete overload and forwards its pointer to std::free; the size parameter is unused. |
| invariants | Sized deallocation does not compare or record the supplied byte count. |
| ownership | Frees storage through the same C allocator used by c03_fit_fault::allocate. |
| failure | Declared noexcept; no exception path is present. |
| cost | One free call; no allocation attempt or byte-account assertion. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0013

[Lines 58–58](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sized array delete through free. |
| inputs / outputs | Provides the sized array delete overload and forwards the pointer to std::free; the size is unused. |
| invariants | The array size does not affect deallocation or fault state. |
| ownership | Releases raw array storage returned by the replacement hook. |
| failure | Declared noexcept; no exception path is present. |
| cost | One free call with no test-counter change. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0014

[Lines 59–59](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matching scalar nothrow delete through free. |
| inputs / outputs | Provides scalar nothrow delete and frees the supplied pointer. |
| invariants | It is the matching cleanup signature for failed scalar nothrow construction; it does not change fail_after. |
| ownership | Pointer ownership ends at free. |
| failure | Declared noexcept; null or valid malloc pointer is accepted by free. |
| cost | One free call; not an allocation-hook event. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0015

[Lines 60–60](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Matching array nothrow delete through free. |
| inputs / outputs | Provides array nothrow delete and frees the supplied pointer. |
| invariants | It matches array nothrow new cleanup and leaves allocation counters unchanged. |
| ownership | Pointer ownership ends at free. |
| failure | Declared noexcept; no translation or recovery code is present. |
| cost | One free call; no allocation attempt is counted. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0016

[Lines 61–66](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L66:sha256:881fc992fb793d5096a1aefc471556b6d4b0e8aa9b691076216dbf4c79cd29b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare maintenance_cost_fit_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 67–69](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Failure-only diagnostic check using string_view. |
| inputs / outputs | Accepts a Boolean and string_view; on false constructs std::string(message) for std::runtime_error, otherwise returns. |
| invariants | The diagnostic view is read only during the call; the body does not create an owning string on success. |
| ownership | Borrows the view; a thrown runtime_error owns its diagnostic. |
| failure | False throws; no error category is caught here. |
| cost | One branch. Failure may allocate the exception string; successful comparison itself has no loop or factory call. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0019

[Lines 71–76](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_fit_options(const model::FitOptions& left, const model::FitOptions& right) {
  return left.max_iterations == right.max_iterations &&
      left.relative_tolerance == right.relative_tolerance &&
      left.rank_tolerance == right.rank_tolerance && left.ridge == right.ridge &&
      left.quantization_denominator == right.quantization_denominator && left.modes == right.modes;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every FitOptions field in a retry image. |
| inputs / outputs | Compares all six FitOptions members: max_iterations, relative_tolerance, rank_tolerance, ridge, quantization_denominator, and modes. |
| invariants | Returns true only when every compared member matches; this is a field-by-field fixture equality helper. |
| ownership | Both options values are borrowed const references. |
| failure | No exception handling; value comparisons return false on the first mismatch. |
| cost | At most six scalar/array-value comparisons, with early exit; no heap storage or factory execution. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0021

[Lines 78–85](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L78); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CalibrationImage {
  std::array<std::optional<model::Coefficient>, model::component_count> coefficients{};
  std::optional<model::FitSummary> summary;
  std::array<model::FitObservation, 4> observations{};
  std::size_t observation_count{};
  model::CalibrationOrigin origin{};
  std::string_view context, backend;
};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fixed-capacity public-state image for a Calibration. |
| inputs / outputs | Stores component_count optional coefficients, optional FitSummary, four FitObservation slots, observation_count, origin, and two string_views. |
| invariants | Observation storage is fixed capacity four. context/backend are views, not copied strings. |
| ownership | Arrays and summary are owned by CalibrationImage; context/backend remain borrowed from fixture strings. |
| failure | Default member initialization has no explicit failure path; callers check observed count before copying. |
| cost | Fixed-size value storage; no observation vector, account, or dynamic string owner is introduced by this struct. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0023

[Lines 87–100](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CalibrationImage image_of(const model::Calibration& value,
    std::string_view context, std::string_view backend) {
  CalibrationImage result;
  result.coefficients = value.coefficients();
  result.summary = value.fit_summary();
  result.origin = value.origin();
  result.context = context;
  result.backend = backend;
  const auto raw = value.fit_observations();
  check(raw.size() <= result.observations.size(), "fixture raw observations exceed image capacity");
  result.observation_count = raw.size();
  for (std::size_t i = 0; i < raw.size(); ++i) result.observations[i] = raw[i];
  return result;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy public Calibration state into the fixed image. |
| inputs / outputs | Copies coefficients, fit summary and origin from Calibration, stores borrowed context/backend views, then copies each returned fit observation into a fixed four-slot image. |
| invariants | Checks raw observation count does not exceed four before indexing. Returning local result is move-eligible under the repository’s C++23 mode. |
| ownership | The image owns copied coefficient/summary/observation values but borrows label strings; the Calibration accessors refer to its immutable shared data. |
| failure | A raw span larger than four fails through check; accessor/copy exceptions propagate. No copy claim is inferred from absence of std::move. |
| cost | Copies component_count coefficient entries through array assignment and at most four observations. No heap-backed observation vector is created by the image itself. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0025

[Lines 102–133](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_calibration(const model::Calibration& value, const CalibrationImage& expected) {
  if (value.context() != expected.context || value.backend() != expected.backend ||
      value.origin() != expected.origin || value.fit_summary().has_value() != expected.summary.has_value())
    return false;
  const auto& coefficients = value.coefficients();
  for (std::size_t i = 0; i < model::component_count; ++i) {
    if (coefficients[i].has_value() != expected.coefficients[i].has_value()) return false;
    if (coefficients[i]) {
      const auto& a = *coefficients[i];
      const auto& b = *expected.coefficients[i];
      if (a.nanoseconds_per_unit != b.nanoseconds_per_unit || a.samples != b.samples ||
          a.units != b.units || a.elapsed_ns != b.elapsed_ns) return false;
    }
  }
  if (value.fit_summary()) {
    const auto& a = *value.fit_summary();
    const auto& b = *expected.summary;
    if (!same_fit_options(a.options, b.options) || a.observations != b.observations ||
        a.observed_features != b.observed_features || a.numerical_rank != b.numerical_rank ||
        a.iterations != b.iterations || a.total_elapsed_ns != b.total_elapsed_ns ||
        a.underdetermined != b.underdetermined ||
        a.root_mean_square_error_ns != b.root_mean_square_error_ns ||
        a.maximum_absolute_error_ns != b.maximum_absolute_error_ns) return false;
  }
  const auto raw = value.fit_observations();
  if (raw.size() != expected.observation_count) return false;
  for (std::size_t i = 0; i < raw.size(); ++i) {
    if (raw[i].units != expected.observations[i].units ||
        raw[i].elapsed_ns != expected.observations[i].elapsed_ns) return false;
  }
  return true;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare Calibration public state with the retained image. |
| inputs / outputs | Compares context/backend, origin, summary presence and all coefficients; if present, compares fit options/statistics/errors, then every raw observation. |
| invariants | Returns false at the first unequal field and true only after raw observation count and contents match the fixed image. |
| ownership | Reads immutable Calibration accessors and borrowed expected label views; it neither mutates nor extends either owner. |
| failure | Does not throw intentionally; any accessor/runtime exception propagates to its caller. |
| cost | Loops over component_count and up to the raw observation count (fixture cap four), with early exits; no result container is built. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0027

[Lines 135–147](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Invoke, class Verify>
std::size_t count_successful_allocations(const Account& account,
    const crown::resource::MemoryUsage& retained_usage, Invoke invoke, Verify verify) {
  c03_fit_fault::allocations = 0;
  auto counted = invoke();
  const auto count = c03_fit_fault::allocations;
  verify(counted);
  check(count > 0 && count < 4096, "calibration fault sweep allocation count outside guard");
  counted.calibration.reset();
  check(account.statistics().current == retained_usage,
      "allocation-count calibration retained a temporary Calibration");
  return count;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count allocations in one successful factory call and release its temporary result. |
| inputs / outputs | Resets the hook count, invokes one successful factory attempt, records attempt count, verifies the result and requires 1..4095 calls, then resets Calibration and checks account current returns to retained usage. |
| invariants | The count is the number of selected operator-new hook entries on that invocation, not a byte count. Verify runs before the temporary Calibration is reset. |
| ownership | Invoke/Verify closures borrow account and fixtures; counted CalibrationAttempt owns the temporary result until reset. |
| failure | Unexpected stop/result, count range, verification or account delta fails through check; factory stop is not converted into a separate C++ exception by this helper. |
| cost | Exactly one factory call plus result verification and reset. Account current covers requested account bytes; hook observes only replacement-new paths selected by this TU. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0029

[Lines 149–184](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Invoke, class Verify>
std::size_t sweep(const Account& account, const model::Calibration& retained,
    const CalibrationImage& expected, std::string_view label, Invoke invoke, Verify verify) {
  const auto retained_usage = account.statistics().current;
  const auto allocation_count = count_successful_allocations(account, retained_usage, invoke, verify);
  std::size_t positions = 0;
  for (std::size_t position = 0; position < allocation_count; ++position) {
    const auto before = account.statistics().current;
    model::CalibrationAttempt failed;
    std::size_t attempted_allocations = 0;
    bool triggered = false;
    {
      c03_fit_fault::Fault fault(position);
      failed = invoke();
      attempted_allocations = c03_fit_fault::allocations;
      triggered = c03_fit_fault::triggered;
    }
    check(triggered && attempted_allocations >= position + 1,
        "selected allocation position was not reached");
    check(failed.stop == pr::Stop::allocation_failure && !failed.calibration,
        "allocation failure returned a partial Calibration or wrong stop code");
    check(account.statistics().current == before,
        "failed calibration changed receiving-account current usage");
    check(same_calibration(retained, expected),
        "earlier successful coefficients or raw observations changed during fault sweep");
    ++positions;
  }
  auto retry = invoke();
  verify(retry);
  check(same_calibration(*retry.calibration, expected), "unfaulted retry differs from retained calibration image");
  retry.calibration.reset();
  check(account.statistics().current == retained_usage,
      "retry Calibration did not release back to retained baseline");
  std::cout << label << " allocation positions=" << positions << '\n';
  return positions;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail each observed allocation position, check no partial result, then retry. |
| inputs / outputs | Snapshots retained account usage, counts one successful call, injects persistent failure at each zero-based observed allocation position, verifies cleanup and retained calibration, then retries once after the full sweep. |
| invariants | Each fault must trigger and reach at least position+1 attempts, return allocation_failure with no Calibration, and preserve account current and retained public fields; retry must match the image and release its account delta. |
| ownership | Retained Calibration and expected image outlive every attempt; failed/retry attempts are local. Fault only toggles test-thread hook state. |
| failure | Fault scope is persistent from the selected position to the end of that invocation. Missing trigger, wrong stop, partial result, changed baseline or retry mismatch fails check. |
| cost | Helper invokes factory once to count, N times for the full fault sweep, and once for retry. Including the caller’s earlier retained baseline, each scenario makes N+3 factory calls. It measures selected new attempts and account current, not CPU/RSS/all allocation ABIs. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0031

[Lines 186–199](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<model::FitObservation, 4> fit_observations() {
  std::array<model::FitObservation, 4> result{};
  result[0].units[static_cast<std::size_t>(model::Component::base_input)] = 1;
  result[0].elapsed_ns = 5;
  result[1].units[static_cast<std::size_t>(model::Component::edge_lookup)] = 1;
  result[1].elapsed_ns = 2;
  result[2].units[static_cast<std::size_t>(model::Component::snapshot_row)] = 1;
  result[2].elapsed_ns = 7;
  result[3].units[static_cast<std::size_t>(model::Component::base_input)] = 2;
  result[3].units[static_cast<std::size_t>(model::Component::edge_lookup)] = 3;
  result[3].units[static_cast<std::size_t>(model::Component::snapshot_row)] = 1;
  result[3].elapsed_ns = 23;  // 2*5 + 3*2 + 1*7
  return result;
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build four whole-phase fit observations with literal feature vectors and elapsed times. |
| inputs / outputs | Returns four fixed FitObservation values: base_input 1 unit/5 ns, edge_lookup 1/2, snapshot_row 1/7, and combined 2/3/1 units at 23 ns. |
| invariants | The combined elapsed value is literal 2*5+3*2+1*7; each observation has zero in unassigned components. |
| ownership | The returned std::array owns all observations and numeric values. |
| failure | No dynamic failure or calibration call is part of this builder. |
| cost | Writes four fixed records; these are synthetic whole-phase fixture inputs, not measured timings from the runtime. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0033

[Lines 201–206](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<model::CalibrationSample, 4> isolated_samples() {
  return {{{model::Component::base_input, 2, 4},
           {model::Component::base_input, 4, 8},
           {model::Component::edge_lookup, 3, 15},
           {model::Component::snapshot_row, 2, 14}}};
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build four isolated calibration samples. |
| inputs / outputs | Returns four CalibrationSamples: base_input 2/4 and 4/8, edge_lookup 3/15, snapshot_row 2/14. |
| invariants | All sample units/times are positive; base_input aggregates to 6 units/12 ns, yielding 2 ns/unit. |
| ownership | The returned std::array owns all sample records. |
| failure | No dynamic failure or calibration call is part of this builder. |
| cost | Returns four literals; values are synthetic isolated-calibration data, not product measurements. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0035

[Lines 208–246](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fit_faults() {
  const auto account = Account::create(64U * 1024U * 1024U);
  const std::string context(80, 'f');
  const std::string backend(72, 'b');  // Both names exceed common SBO capacities.
  const auto observations = fit_observations();
  const auto invoke = [&] { return model::fit(account, context, backend, observations); };
  auto first = invoke();
  check(first.stop == pr::Stop::complete && first.calibration,
      "fit baseline Calibration was not created");
  const model::Calibration retained = *first.calibration;
  first.calibration.reset();
  const auto expected = image_of(retained, context, backend);
  check(retained.origin() == model::CalibrationOrigin::fitted_linear_assumption &&
      retained.fit_summary() && retained.fit_observations().size() == observations.size(),
      "fit baseline omitted summary or raw observations");
  check(retained.fit_summary()->observed_features == 3 && retained.fit_summary()->numerical_rank == 3 &&
      !retained.fit_summary()->underdetermined, "fit baseline did not retain its identifiable rank");
  const auto& coefficients = retained.coefficients();
  check(coefficients[static_cast<std::size_t>(model::Component::base_input)] &&
      coefficients[static_cast<std::size_t>(model::Component::base_input)]->nanoseconds_per_unit == model::Ratio{5, 1},
      "fit baseline base-input rate differs from its literal data");
  check(coefficients[static_cast<std::size_t>(model::Component::edge_lookup)] &&
      coefficients[static_cast<std::size_t>(model::Component::edge_lookup)]->nanoseconds_per_unit == model::Ratio{2, 1},
      "fit baseline edge-lookup rate differs from its literal data");
  check(coefficients[static_cast<std::size_t>(model::Component::snapshot_row)] &&
      coefficients[static_cast<std::size_t>(model::Component::snapshot_row)]->nanoseconds_per_unit == model::Ratio{7, 1},
      "fit baseline snapshot-row rate differs from its literal data");
  for (std::size_t i = 0; i < observations.size(); ++i)
    check(retained.fit_observations()[i].units == observations[i].units &&
        retained.fit_observations()[i].elapsed_ns == observations[i].elapsed_ns,
        "fit baseline raw observation differs from its input");
  const auto verify = [&](const model::CalibrationAttempt& attempt) {
    check(attempt.stop == pr::Stop::complete && attempt.calibration,
        "fit operation did not succeed outside the fault scope");
    check(same_calibration(*attempt.calibration, expected),
        "fit retry changed coefficients, summary, or raw observations");
  };
  static_cast<void>(sweep(account, retained, expected, "fit", invoke, verify));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep fit with long labels and synthetic observations. |
| inputs / outputs | Builds 80/72-character labels and four synthetic fit observations, retains a baseline fit, checks fitted origin, rank/features, three literal rates and copied observations, then runs the full fault sweep. |
| invariants | This fixture asserts rates 5/1, 2/1, 7/1, observed_features=3, numerical_rank=3 and four retained observations. It does not assert the fitted algorithm’s iteration count or future timing accuracy. |
| ownership | The fit call borrows labels and observation array; returned Calibration owns copied immutable data. Retained handle and expected image outlive all fault positions. |
| failure | Every selected injected failure must return allocation_failure without a partial result; successful retry must match retained public state. |
| cost | Four observations and fixed component loops feed coordinate descent bounded by FitOptions.max_iterations (default 10000), with convergence checked by source. The test does not observe elapsed time or assert how many iterations run; factory schedule is N+3 including retained baseline. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0037

[Lines 248–280](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void isolated_calibration_faults() {
  const auto account = Account::create(64U * 1024U * 1024U);
  const std::string context(88, 'c');
  const std::string backend(76, 'k');  // Force both owned strings to allocate.
  const auto samples = isolated_samples();
  const auto invoke = [&] { return model::calibrate(account, context, backend, samples); };
  auto first = invoke();
  check(first.stop == pr::Stop::complete && first.calibration,
      "isolated-calibration baseline was not created");
  const model::Calibration retained = *first.calibration;
  first.calibration.reset();
  const auto expected = image_of(retained, context, backend);
  check(retained.origin() == model::CalibrationOrigin::isolated_measurement_ratios &&
      !retained.fit_summary() && retained.fit_observations().empty(),
      "isolated calibration retained fitted-only fields");
  const auto& coefficients = retained.coefficients();
  const auto base = coefficients[static_cast<std::size_t>(model::Component::base_input)];
  const auto edge = coefficients[static_cast<std::size_t>(model::Component::edge_lookup)];
  const auto snapshot = coefficients[static_cast<std::size_t>(model::Component::snapshot_row)];
  check(base && base->nanoseconds_per_unit == model::Ratio{2, 1} && base->samples == 2 &&
      base->units == 6 && base->elapsed_ns == 12, "isolated base-input coefficient is not literal");
  check(edge && edge->nanoseconds_per_unit == model::Ratio{5, 1} && edge->samples == 1,
      "isolated edge-lookup coefficient is not literal");
  check(snapshot && snapshot->nanoseconds_per_unit == model::Ratio{7, 1} && snapshot->samples == 1,
      "isolated snapshot-row coefficient is not literal");
  const auto verify = [&](const model::CalibrationAttempt& attempt) {
    check(attempt.stop == pr::Stop::complete && attempt.calibration,
        "isolated calibration did not succeed outside the fault scope");
    check(same_calibration(*attempt.calibration, expected),
        "isolated retry changed coefficients or raw calibration state");
  };
  static_cast<void>(sweep(account, retained, expected, "isolated calibrate", invoke, verify));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep isolated calibrate and check its result shape. |
| inputs / outputs | Builds long labels and four isolated samples, retains a baseline calibrate result, checks isolated origin/no fit-only summary or observations and literal aggregate rates, then fault-sweeps. |
| invariants | Base samples aggregate to 6 units/12 ns (2/1 over two samples); edge is 5/1 and snapshot row 7/1. These are derived from the fixed inputs. |
| ownership | Sample array and labels stay alive during calls; Calibration shares immutable accounted data and the retained handle survives all positions. |
| failure | Injected allocation positions return allocation_failure/no Calibration; successful retry matches the captured public image. |
| cost | Four samples per factory invocation and fixed component iteration. Position count is measured from selected hook calls; no CPU/RSS/all-allocator claim is made. Factory schedule is N+3 including baseline. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |

## B0038

[Lines 281–282](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L281); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L281-L282:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in maintenance_cost_fit_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0039

[Lines 283–291](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
  try {
    fit_faults();
    isolated_calibration_faults();
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fit and isolated-calibration fault schedules. |
| inputs / outputs | Calls fit_faults then isolated_calibration_faults inside a std::exception catch; the catch prints the diagnostic and returns 1. |
| invariants | Success falls through to the implicit zero return. Each scenario owns its account, labels, samples/observations and retained result. |
| ownership | No account or calibration survives either helper return; the main function owns only sequencing and stderr use. |
| failure | Catches std::exception only; non-standard exceptions escape. There is no final success banner in this main. |
| cost | Runs two finite allocation schedules with per-scenario N+3 factory calls including baseline, successful count, N failures and retry. This source review did not execute the native test. |
| Design | [tests/unit/maintenance_cost_fit_exception_test.cpp](../../../../../tests/unit/maintenance_cost_fit_exception_test.cpp), [include/crown/runtime/maintenance_cost.hpp](../../../../../include/crown/runtime/maintenance_cost.hpp), [src/runtime/maintenance_cost.cpp](../../../../../src/runtime/maintenance_cost.cpp), [docs/maintenance_cost.md](../../../../maintenance_cost.md) |
