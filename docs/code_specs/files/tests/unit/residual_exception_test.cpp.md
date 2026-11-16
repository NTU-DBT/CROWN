# `tests/unit/residual_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/residual_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `95207ebdfabcc6ba0dc1a39ce6efaa9bec630812ef297db039599752fc667e63`. 786 lines partitioned into 81 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../tests/unit/residual_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 25–33](../../../../../tests/unit/residual_exception_test.cpp#L25) | Callable definition: \[\[gnu::noinline\]\] void* tracked_malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 34–34](../../../../../tests/unit/residual_exception_test.cpp#L34) | Explanatory comments or spacing. |  |
| [B0004 · 35–40](../../../../../tests/unit/residual_exception_test.cpp#L35) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0004) |
| [B0005 · 41–42](../../../../../tests/unit/residual_exception_test.cpp#L41) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 43–43](../../../../../tests/unit/residual_exception_test.cpp#L43) | Callable definition: void* operator new(std::size_t bytes) | calls tracked_malloc_new; returns tracked_malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 44–44](../../../../../tests/unit/residual_exception_test.cpp#L44) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns tracked_malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 45–48](../../../../../tests/unit/residual_exception_test.cpp#L45) | Callable definition: void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept | calls tracked_malloc_new; returns tracked_malloc_new(bytes); nullptr; growth new · [reviewed contract](#b0008) |
| [B0009 · 49–52](../../../../../tests/unit/residual_exception_test.cpp#L49) | Callable definition: void* operator new\[\](std::size_t bytes, const std::nothrow_t&) noexcept | calls ; returns tracked_malloc_new(bytes); nullptr; growth new · [reviewed contract](#b0009) |
| [B0010 · 53–53](../../../../../tests/unit/residual_exception_test.cpp#L53) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 54–54](../../../../../tests/unit/residual_exception_test.cpp#L54) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 55–55](../../../../../tests/unit/residual_exception_test.cpp#L55) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0012) |
| [B0013 · 56–56](../../../../../tests/unit/residual_exception_test.cpp#L56) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0013) |
| [B0014 · 57–57](../../../../../tests/unit/residual_exception_test.cpp#L57) | Callable definition: void operator delete(void* pointer, const std::nothrow_t&) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 58–58](../../../../../tests/unit/residual_exception_test.cpp#L58) | Callable definition: void operator delete\[\](void* pointer, const std::nothrow_t&) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 59–67](../../../../../tests/unit/residual_exception_test.cpp#L59) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_destructible_v&lt;ResidualSearch&gt;); · [reviewed contract](#b0016) |
| [B0017 · 68–70](../../../../../tests/unit/residual_exception_test.cpp#L68) | Callable definition: void check(bool condition, const char* message) | calls std::runtime_error; guard void check(bool condition, const char* message) { · [reviewed contract](#b0017) |
| [B0018 · 71–71](../../../../../tests/unit/residual_exception_test.cpp#L71) | Explanatory comments or spacing. |  |
| [B0019 · 72–75](../../../../../tests/unit/residual_exception_test.cpp#L72) | Type/record definition: struct Fixture |  · [reviewed contract](#b0019) |
| [B0020 · 76–76](../../../../../tests/unit/residual_exception_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0021 · 77–101](../../../../../tests/unit/residual_exception_test.cpp#L77) | Callable definition: Fixture scoped_fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls names, begin, end, insert; returns fixture; growth emplace_back, insert, push_back, reserve; 5 loop sites · [reviewed contract](#b0021) |
| [B0022 · 102–102](../../../../../tests/unit/residual_exception_test.cpp#L102) | Explanatory comments or spacing. |  |
| [B0023 · 103–108](../../../../../tests/unit/residual_exception_test.cpp#L103) | Callable definition: bool same_term(const Term& left, const Term& right) | calls index; returns false; *id == std::get&lt;VariableId&gt;(right) · [reviewed contract](#b0023) |
| [B0024 · 109–109](../../../../../tests/unit/residual_exception_test.cpp#L109) | Explanatory comments or spacing. |  |
| [B0025 · 110–125](../../../../../tests/unit/residual_exception_test.cpp#L110) | Callable definition: bool same_query(const Query& left, const Query& right) | calls size, same_term; returns false; false; 4 loop sites · [reviewed contract](#b0025) |
| [B0026 · 126–126](../../../../../tests/unit/residual_exception_test.cpp#L126) | Explanatory comments or spacing. |  |
| [B0027 · 127–145](../../../../../tests/unit/residual_exception_test.cpp#L127) | Callable definition: bool same_catalog(const Catalog& left, const Catalog& right) | calls size; returns false; false; 2 loop sites · [reviewed contract](#b0027) |
| [B0028 · 146–146](../../../../../tests/unit/residual_exception_test.cpp#L146) | Explanatory comments or spacing. |  |
| [B0029 · 147–157](../../../../../tests/unit/residual_exception_test.cpp#L147) | Callable definition: bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) | calls size; returns false; false; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 158–158](../../../../../tests/unit/residual_exception_test.cpp#L158) | Explanatory comments or spacing. |  |
| [B0031 · 159–170](../../../../../tests/unit/residual_exception_test.cpp#L159) | Callable definition: bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) | calls has_value, size, same_tree; returns false; false; 1 loop sites · [reviewed contract](#b0031) |
| [B0032 · 171–171](../../../../../tests/unit/residual_exception_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0033 · 172–189](../../../../../tests/unit/residual_exception_test.cpp#L172) | Callable definition: bool same_layer(const ResidualLayer& a, const ResidualLayer& b) | calls size; returns false; false; 3 loop sites · [reviewed contract](#b0033) |
| [B0034 · 190–190](../../../../../tests/unit/residual_exception_test.cpp#L190) | Explanatory comments or spacing. |  |
| [B0035 · 191–195](../../../../../tests/unit/residual_exception_test.cpp#L191) | Callable definition: bool same_view(const ResidualView& a, const ResidualView& b) | calls same_query; returns a.original_occurrences == b.original_occurrences && a.original_variables == b.original_variables && · [reviewed contract](#b0035) |
| [B0036 · 196–196](../../../../../tests/unit/residual_exception_test.cpp#L196) | Explanatory comments or spacing. |  |
| [B0037 · 197–204](../../../../../tests/unit/residual_exception_test.cpp#L197) | Callable definition: bool same_record(const ResidualTraceRecord& a, const ResidualTraceRecord& b) | calls size, same_view, same_layer; returns false; false; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 205–205](../../../../../tests/unit/residual_exception_test.cpp#L205) | Explanatory comments or spacing. |  |
| [B0039 · 206–213](../../../../../tests/unit/residual_exception_test.cpp#L206) | Callable definition: bool same_statistics(const ResidualStatistics& a, const ResidualStatistics& b) | calls ; returns a.hierarchy_tests == b.hierarchy_tests && a.rounds == b.rounds && · [reviewed contract](#b0039) |
| [B0040 · 214–214](../../../../../tests/unit/residual_exception_test.cpp#L214) | Explanatory comments or spacing. |  |
| [B0041 · 215–228](../../../../../tests/unit/residual_exception_test.cpp#L215) | Callable definition: bool same_search_shape(const SearchProgress& a, const SearchProgress& b) | calls ; returns a.phase == b.phase && a.result == b.result && a.heights == b.heights && · [reviewed contract](#b0041) |
| [B0042 · 229–229](../../../../../tests/unit/residual_exception_test.cpp#L229) | Explanatory comments or spacing. |  |
| [B0043 · 230–238](../../../../../tests/unit/residual_exception_test.cpp#L230) | Callable definition: bool same_progress_shape(const ResidualProgress& a, const ResidualProgress& b) | calls same_statistics, same_search_shape; returns a.phase == b.phase && a.result == b.result && a.proof_status == b.proof_status && · [reviewed contract](#b0043) |
| [B0044 · 239–239](../../../../../tests/unit/residual_exception_test.cpp#L239) | Explanatory comments or spacing. |  |
| [B0045 · 240–246](../../../../../tests/unit/residual_exception_test.cpp#L240) | Callable definition: bool same_progress(const ResidualProgress& a, const ResidualProgress& b) | calls same_progress_shape; returns same_progress_shape(a, b) && a.last_stop == b.last_stop && a.exact_stop == b.exact_stop && · [reviewed contract](#b0045) |
| [B0046 · 247–247](../../../../../tests/unit/residual_exception_test.cpp#L247) | Explanatory comments or spacing. |  |
| [B0047 · 248–253](../../../../../tests/unit/residual_exception_test.cpp#L248) | Callable definition: bool counters_monotone(const WorkCounters& before, const WorkCounters& after) | calls ; returns after.attempted &gt;= before.attempted && · [reviewed contract](#b0047) |
| [B0048 · 254–254](../../../../../tests/unit/residual_exception_test.cpp#L254) | Explanatory comments or spacing. |  |
| [B0049 · 255–259](../../../../../tests/unit/residual_exception_test.cpp#L255) | Callable definition: bool progress_counters_monotone(const ResidualProgress& before, const ResidualProgress& after) | calls counters_monotone; returns counters_monotone(before.work, after.work) && · [reviewed contract](#b0049) |
| [B0050 · 260–260](../../../../../tests/unit/residual_exception_test.cpp#L260) | Explanatory comments or spacing. |  |
| [B0051 · 261–264](../../../../../tests/unit/residual_exception_test.cpp#L261) | Callable definition: bool same_trace(const ResidualTrace& a, const ResidualTrace& b) | calls valid, same_catalog, catalog, same_query; returns a.valid() && b.valid() && same_catalog(a.catalog(), b.catalog()) && · [reviewed contract](#b0051) |
| [B0052 · 265–265](../../../../../tests/unit/residual_exception_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0053 · 266–270](../../../../../tests/unit/residual_exception_test.cpp#L266) | Callable definition: bool same_candidate(const ResidualCandidate& a, const ResidualCandidate& b) | calls valid, same_catalog, catalog, same_query; returns a.valid() && b.valid() && same_catalog(a.catalog(), b.catalog()) && · [reviewed contract](#b0053) |
| [B0054 · 271–273](../../../../../tests/unit/residual_exception_test.cpp#L271) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0054) |
| [B0055 · 274–278](../../../../../tests/unit/residual_exception_test.cpp#L274) | Callable definition: ResidualOptions options_for(ResidualMode mode) | calls ; returns options · [reviewed contract](#b0055) |
| [B0056 · 279–279](../../../../../tests/unit/residual_exception_test.cpp#L279) | Explanatory comments or spacing. |  |
| [B0057 · 280–286](../../../../../tests/unit/residual_exception_test.cpp#L280) | Type/record definition: struct Baseline |  · [reviewed contract](#b0057) |
| [B0058 · 287–287](../../../../../tests/unit/residual_exception_test.cpp#L287) | Explanatory comments or spacing. |  |
| [B0059 · 288–331](../../../../../tests/unit/residual_exception_test.cpp#L288) | Callable definition: Baseline calibrate(const Fixture& fixture, ResidualMode mode) | calls ResidualSearch::create, options_for, advance, progress; guard check(advanced.stopped_for == ResidualStopReason::complete,; returns Baseline{progress, *trace, *candidate, std::move(optimum), allocations}; growth emplace · [reviewed contract](#b0059) |
| [B0060 · 332–332](../../../../../tests/unit/residual_exception_test.cpp#L332) | Explanatory comments or spacing. |  |
| [B0061 · 333–337](../../../../../tests/unit/residual_exception_test.cpp#L333) | Callable definition: bool allocation_stop(const ResidualAdvance& value) | calls ; returns value.stopped_for == ResidualStopReason::allocation_failure \|\| · [reviewed contract](#b0061) |
| [B0062 · 338–338](../../../../../tests/unit/residual_exception_test.cpp#L338) | Explanatory comments or spacing. |  |
| [B0063 · 339–342](../../../../../tests/unit/residual_exception_test.cpp#L339) | Callable definition: bool trace_same_optional(const std::optional&lt;ResidualTrace&gt;& a, const std::optional&lt;ResidualTrace&gt;& b) | calls has_value, same_trace; returns a.has_value() == b.has_value() && (!a \|\| same_trace(*a, *b)) · [reviewed contract](#b0063) |
| [B0064 · 343–343](../../../../../tests/unit/residual_exception_test.cpp#L343) | Explanatory comments or spacing. |  |
| [B0065 · 344–347](../../../../../tests/unit/residual_exception_test.cpp#L344) | Callable definition: bool candidate_same_optional(const std::optional&lt;ResidualCandidate&gt;& a, const std::optional&lt;ResidualCandidate&gt;& b) | calls has_value, same_candidate; returns a.has_value() == b.has_value() && (!a \|\| same_candidate(*a, *b)) · [reviewed contract](#b0065) |
| [B0066 · 348–348](../../../../../tests/unit/residual_exception_test.cpp#L348) | Explanatory comments or spacing. |  |
| [B0067 · 349–360](../../../../../tests/unit/residual_exception_test.cpp#L349) | Type/record definition: struct Coverage |  · [reviewed contract](#b0067) |
| [B0068 · 361–361](../../../../../tests/unit/residual_exception_test.cpp#L361) | Explanatory comments or spacing. |  |
| [B0069 · 362–382](../../../../../tests/unit/residual_exception_test.cpp#L362) | Callable definition: void update_coverage(Coverage& coverage, const ResidualProgress& p, const std::optional&lt;ResidualTrace&gt;& trace, const std::optiona… | calls has_value · [reviewed contract](#b0069) |
| [B0070 · 383–383](../../../../../tests/unit/residual_exception_test.cpp#L383) | Explanatory comments or spacing. |  |
| [B0071 · 384–538](../../../../../tests/unit/residual_exception_test.cpp#L384) | Callable definition: void residual_oom_sweep(const Fixture& fixture, ResidualMode mode, const Baseline& baseline, Coverage& coverage, const char* labe… | calls ResidualSearch::create, options_for, fault, advance; guard check(completed.stopped_for == ResidualStopReason::complete,; 1 loop sites · [reviewed contract](#b0071) |
| [B0072 · 539–539](../../../../../tests/unit/residual_exception_test.cpp#L539) | Explanatory comments or spacing. |  |
| [B0073 · 540–556](../../../../../tests/unit/residual_exception_test.cpp#L540) | Callable definition: void trace_verifier_is_independent_and_resource_honest(const Fixture& fixture, const ResidualTrace& trace) | calls verify_residual_trace, record, check; guard check(valid.valid && !valid.resource_limit && valid.work &gt; 0 && valid.rule == ResidualTraceRule::no… · [reviewed contract](#b0073) |
| [B0074 · 557–557](../../../../../tests/unit/residual_exception_test.cpp#L557) | Explanatory comments or spacing. |  |
| [B0075 · 558–626](../../../../../tests/unit/residual_exception_test.cpp#L558) | Callable definition: void limit_extensions_and_zero_quanta(const Fixture& fixture) | calls options_for, std::move, make_limited, ResidualSearch::create; guard check(first.stopped_for == expected && progress.result == ResidualResult::unfinished &&; returns std::pair{std::move(options), kind}; 1 loop sites · [reviewed contract](#b0075) |
| [B0076 · 627–627](../../../../../tests/unit/residual_exception_test.cpp#L627) | Explanatory comments or spacing. |  |
| [B0077 · 628–698](../../../../../tests/unit/residual_exception_test.cpp#L628) | Callable definition: void cancellation_lifecycle_and_outliving_handles(const Fixture& fixture) | calls ResidualSearch::create, options_for, advance, trace; guard check(current.result != ResidualResult::failed,; growth emplace; 1 loop sites · [reviewed contract](#b0077) |
| [B0078 · 699–699](../../../../../tests/unit/residual_exception_test.cpp#L699) | Explanatory comments or spacing. |  |
| [B0079 · 700–773](../../../../../tests/unit/residual_exception_test.cpp#L700) | Callable definition: void run() | calls scoped_fixture, calibrate, check, record; guard check(candidate_baseline.trace.record().layers.size() == 1 &&; source comment (unverified): // Head-induced nonhierarchy removes the second atom while retaining a valid · [reviewed contract](#b0079) |
| [B0080 · 774–775](../../../../../tests/unit/residual_exception_test.cpp#L774) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0080) |
| [B0081 · 776–786](../../../../../tests/unit/residual_exception_test.cpp#L776) | Callable definition: int main() | calls run, what; returns 0; 1 · [reviewed contract](#b0081) |

## B0001

[Lines 1–24](../../../../../tests/unit/residual_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:32204909b8bd0e69287c4b2a8d48ae7c3f25def2c7ca2ae5e98c70cbb7988a2a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_exception_test.cpp: include "crown/planner/residual.hpp", "crown/planner/verify.hpp", &lt;algorithm&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 25–33](../../../../../tests/unit/residual_exception_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* tracked_malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track one directly intercepted replacement-new request, fail before backing malloc at the selected point, and translate real malloc failure to bad_alloc. |
| inputs / outputs | Inputs and return are those in \`\[\[gnu::noinline\]\] void* tracked_malloc_new(std::size_t bytes)\`; body-specific behavior: Track one directly intercepted replacement-new request, fail before backing malloc at the selected point, and translate real malloc failure to bad_alloc. |
| invariants | Counter measures calls into this helper, not bytes, total process allocation, direct malloc outside the replacement, account admission, or OS calls. |
| ownership | No allocation object is retained; thread-local failpoint/count are shared only with the current thread. |
| failure | Throws std::bad_alloc at fail_after==0 before calling malloc; real malloc nullptr is translated to bad_alloc. The sweep intercepts these directly defined replacement-new calls only. |
| cost | One counter update, one branch and at most one malloc request; counter counts intercepted helper invocations, not bytes or all allocation sources. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0004

[Lines 35–40](../../../../../tests/unit/residual_exception_test.cpp#L35); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm thread-local fail_after for one lexical sweep scope and clear it at scope exit; copying is forbidden. |
| inputs / outputs | Inputs and return are those in \`struct FaultScope\`; body-specific behavior: Arm thread-local fail_after for one lexical sweep scope and clear it at scope exit; copying is forbidden. |
| invariants | fail_after=-1 disables failure; zero fails before std::malloc; destructor always resets the thread-local injector. |
| ownership | The scope owns no resources; it changes thread-local state and resets it during destruction. |
| failure | Constructor is noexcept; destructor resets the thread-local failpoint to disabled. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0005

[Lines 41–42](../../../../../tests/unit/residual_exception_test.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in residual_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 43–43](../../../../../tests/unit/residual_exception_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return tracked_malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar throwing new through tracked_malloc_new. |
| inputs / outputs | Inputs and return are those in \`void* operator new(std::size_t bytes)\`; body-specific behavior: Route ordinary scalar throwing new through tracked_malloc_new. |
| invariants | Direct replacement only; a library nothrow request may indirectly delegate, which is not asserted coverage. |
| ownership | Returns the malloc-backed pointer to the caller; no allocation metadata is retained by the helper. |
| failure | Throws std::bad_alloc from the tracked helper when armed or when malloc fails. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0007

[Lines 44–44](../../../../../tests/unit/residual_exception_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return tracked_malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array throwing new through tracked_malloc_new. |
| inputs / outputs | Inputs and return are those in \`void* operator new\[\](std::size_t bytes)\`; body-specific behavior: Route ordinary array throwing new through tracked_malloc_new. |
| invariants | Direct replacement only; aligned forms and direct malloc/account/systemcall failures are outside this injector. |
| ownership | Returns the malloc-backed pointer to the caller; no allocation metadata is retained by the helper. |
| failure | Throws std::bad_alloc from the tracked helper when armed or when malloc fails. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0008

[Lines 45–48](../../../../../tests/unit/residual_exception_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the directly defined scalar nothrow form through the tracker and return null on bad_alloc. |
| inputs / outputs | Inputs and return are those in \`void* operator new(std::size_t bytes, const std::nothrow_t&) noexcept\`; body-specific behavior: Route the directly defined scalar nothrow form through the tracker and return null on bad_alloc. |
| invariants | Dedicated nothrow replacement exists here, but no aligned replacement; indirect library delegation is not claimed. |
| ownership | Returns a pointer or null; storage ownership passes to the C++ caller and matching delete frees it. |
| failure | Catches std::bad_alloc and returns nullptr under its noexcept signature. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0009

[Lines 49–52](../../../../../tests/unit/residual_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, const std::nothrow_t&) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route the directly defined array nothrow form through the tracker and return null on bad_alloc. |
| inputs / outputs | Inputs and return are those in \`void* operator new\[\](std::size_t bytes, const std::nothrow_t&) noexcept\`; body-specific behavior: Route the directly defined array nothrow form through the tracker and return null on bad_alloc. |
| invariants | Dedicated nothrow replacement exists here, but no aligned replacement; indirect library delegation is not claimed. |
| ownership | Returns a pointer or null; storage ownership passes to the C++ caller and matching delete frees it. |
| failure | Catches std::bad_alloc and returns nullptr under its noexcept signature. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0010

[Lines 53–53](../../../../../tests/unit/residual_exception_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free ordinary scalar replacement storage through std::free. |
| inputs / outputs | Inputs and return are those in \`void operator delete(void* pointer) noexcept\`; body-specific behavior: Free ordinary scalar replacement storage through std::free. |
| invariants | Null and replacement delete paths release only pointers returned by these replacement forms. |
| ownership | Consumes a raw pointer and releases it; no value is retained. |
| failure | Declared noexcept; calls std::free. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0011

[Lines 54–54](../../../../../tests/unit/residual_exception_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free ordinary array replacement storage through std::free. |
| inputs / outputs | Inputs and return are those in \`void operator delete\[\](void* pointer) noexcept\`; body-specific behavior: Free ordinary array replacement storage through std::free. |
| invariants | Null and replacement delete paths release only pointers returned by these replacement forms. |
| ownership | Consumes a raw pointer and releases it; no value is retained. |
| failure | Declared noexcept; calls std::free. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0012

[Lines 55–55](../../../../../tests/unit/residual_exception_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized scalar replacement storage through std::free. |
| inputs / outputs | Inputs and return are those in \`void operator delete(void* pointer, std::size_t) noexcept\`; body-specific behavior: Free sized scalar replacement storage through std::free. |
| invariants | Sized delete does not count allocations and does not claim allocator-system coverage. |
| ownership | Consumes a raw pointer and releases it; no value is retained. |
| failure | Declared noexcept; calls std::free. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0013

[Lines 56–56](../../../../../tests/unit/residual_exception_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized array replacement storage through std::free. |
| inputs / outputs | Inputs and return are those in \`void operator delete\[\](void* pointer, std::size_t) noexcept\`; body-specific behavior: Free sized array replacement storage through std::free. |
| invariants | Sized delete does not count allocations and does not claim allocator-system coverage. |
| ownership | Consumes a raw pointer and releases it; no value is retained. |
| failure | Declared noexcept; calls std::free. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0014

[Lines 57–57](../../../../../tests/unit/residual_exception_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar nothrow-placement cleanup storage through std::free. |
| inputs / outputs | Inputs and return are those in \`void operator delete(void* pointer, const std::nothrow_t&) noexcept\`; body-specific behavior: Free scalar nothrow-placement cleanup storage through std::free. |
| invariants | Nothrow delete is a deallocation pairing only; it does not extend the fault seam. |
| ownership | Consumes a raw pointer and releases it; no value is retained. |
| failure | Declared noexcept; calls std::free. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0015

[Lines 58–58](../../../../../tests/unit/residual_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, const std::nothrow_t&) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array nothrow-placement cleanup storage through std::free. |
| inputs / outputs | Inputs and return are those in \`void operator delete\[\](void* pointer, const std::nothrow_t&) noexcept\`; body-specific behavior: Free array nothrow-placement cleanup storage through std::free. |
| invariants | Nothrow delete is a deallocation pairing only; it does not extend the fault seam. |
| ownership | Consumes a raw pointer and releases it; no value is retained. |
| failure | Declared noexcept; calls std::free. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0016

[Lines 59–67](../../../../../tests/unit/residual_exception_test.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L67:sha256:0a1a82638846d3d050157cd717e6448318b813b1ec86a5aec36cdf11bd0814c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_exception_test.cpp: bind local aliases/name imports; require 3 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0017

[Lines 68–70](../../../../../tests/unit/residual_exception_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const char* message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed fixture assertion into std::runtime_error. |
| inputs / outputs | Inputs and return are those in \`void check(bool condition, const char* message)\`; body-specific behavior: Turn a failed fixture assertion into std::runtime_error. |
| invariants | Test-local assertion oracle; it does not translate planner errors. |
| ownership | Inputs are borrowed or values for the call as declared; the helper retains no result after return, except explicitly mutated output-reference arguments. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0019

[Lines 72–75](../../../../../tests/unit/residual_exception_test.cpp#L72); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the synthetic residual fixture catalog and query. |
| inputs / outputs | Inputs and return are those in \`struct Fixture\`; body-specific behavior: Own the synthetic residual fixture catalog and query. |
| invariants | Plain value fixture only; it performs no planner operation. |
| ownership | Owns the catalog and query as fixture values. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0021

[Lines 77–101](../../../../../tests/unit/residual_exception_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an integer-variable, int-column fixture from scopes/head, using distinct occurrence tables. |
| inputs / outputs | Inputs and return are those in \`Fixture scoped_fixture(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head)\`; body-specific behavior: Build an integer-variable, int-column fixture from scopes/head, using distinct occurrence tables. |
| invariants | Each scope is a source occurrence, including repeated variables within one occurrence; head order is preserved. |
| ownership | Scopes/head are borrowed; returned fixture owns its generated Catalog and Query. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0023

[Lines 103–108](../../../../../tests/unit/residual_exception_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_term(const Term& left, const Term& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare Term alternatives and values for failure-stability snapshots. |
| inputs / outputs | Inputs and return are those in \`bool same_term(const Term& left, const Term& right)\`; body-specific behavior: Compare Term alternatives and values for failure-stability snapshots. |
| invariants | Comparison is intentionally variant-aware for terms; not a cryptographic or serialized identity test. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0025

[Lines 110–125](../../../../../tests/unit/residual_exception_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_query(const Query& left, const Query& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare complete query shape, including variable names/types, occurrence/table/terms, ordered head and contradiction. |
| inputs / outputs | Inputs and return are those in \`bool same_query(const Query& left, const Query& right)\`; body-specific behavior: Compare complete query shape, including variable names/types, occurrence/table/terms, ordered head and contradiction. |
| invariants | Exact structural equality for the checked query fields is the stability oracle. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0027

[Lines 127–145](../../../../../tests/unit/residual_exception_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_catalog(const Catalog& left, const Catalog& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare catalog version/table count, table names/column counts/types used by the OOM fixture; it does not compare every metadata field value. |
| inputs / outputs | Inputs and return are those in \`bool same_catalog(const Catalog& left, const Catalog& right)\`; body-specific behavior: Compare catalog version/table count, table names/column counts/types used by the OOM fixture; it does not compare every metadata field value. |
| invariants | Fixture catalog metadata not enumerated in this comparator is not covered by its equality claim. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0029

[Lines 147–157](../../../../../tests/unit/residual_exception_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare tree identity, root and nodes/edges represented in the FreeConnexTree. |
| inputs / outputs | Inputs and return are those in \`bool same_tree(const FreeConnexTree& left, const FreeConnexTree& right)\`; body-specific behavior: Compare tree identity, root and nodes/edges represented in the FreeConnexTree. |
| invariants | This comparator checks the fields listed in its body, not semantic tree optimality. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0031

[Lines 159–170](../../../../../tests/unit/residual_exception_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_certificate(const HeightCertificate& left, const HeightCertificate& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare height-certificate entries and associated owned proof fields. |
| inputs / outputs | Inputs and return are those in \`bool same_certificate(const HeightCertificate& left, const HeightCertificate& right)\`; body-specific behavior: Compare height-certificate entries and associated owned proof fields. |
| invariants | Only compared certificate fields are asserted; no independent theorem follows from equality. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0033

[Lines 172–189](../../../../../tests/unit/residual_exception_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_layer(const ResidualLayer& a, const ResidualLayer& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare residual layer vectors and optional-layer contents used to detect mutation after failure. |
| inputs / outputs | Inputs and return are those in \`bool same_layer(const ResidualLayer& a, const ResidualLayer& b)\`; body-specific behavior: Compare residual layer vectors and optional-layer contents used to detect mutation after failure. |
| invariants | Checks exported layer state, not hidden worker memory. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0035

[Lines 191–195](../../../../../tests/unit/residual_exception_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_view(const ResidualView& a, const ResidualView& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the exported residual view fields used by the fault-sweep stability oracle. |
| inputs / outputs | Inputs and return are those in \`bool same_view(const ResidualView& a, const ResidualView& b)\`; body-specific behavior: Compare the exported residual view fields used by the fault-sweep stability oracle. |
| invariants | Checks exported view values, not the correctness theorem in isolation. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0037

[Lines 197–204](../../../../../tests/unit/residual_exception_test.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_record(const ResidualTraceRecord& a, const ResidualTraceRecord& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare one residual trace record, including scope/anchor/deletion data. |
| inputs / outputs | Inputs and return are those in \`bool same_record(const ResidualTraceRecord& a, const ResidualTraceRecord& b)\`; body-specific behavior: Compare one residual trace record, including scope/anchor/deletion data. |
| invariants | Checks exported trace record values, not the correctness theorem in isolation. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0039

[Lines 206–213](../../../../../tests/unit/residual_exception_test.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_statistics(const ResidualStatistics& a, const ResidualStatistics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exposed residual statistics for retry stability. |
| inputs / outputs | Inputs and return are those in \`bool same_statistics(const ResidualStatistics& a, const ResidualStatistics& b)\`; body-specific behavior: Compare exposed residual statistics for retry stability. |
| invariants | Field equality supports stability checks; it is not an independent work-accounting proof. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0041

[Lines 215–228](../../../../../tests/unit/residual_exception_test.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_search_shape(const SearchProgress& a, const SearchProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact-search public shape retained inside residual progress. |
| inputs / outputs | Inputs and return are those in \`bool same_search_shape(const SearchProgress& a, const SearchProgress& b)\`; body-specific behavior: Compare exact-search public shape retained inside residual progress. |
| invariants | Compares public search progress shape only. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0043

[Lines 230–238](../../../../../tests/unit/residual_exception_test.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_progress_shape(const ResidualProgress& a, const ResidualProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare residual progress shape while normalizing counters checked separately. |
| inputs / outputs | Inputs and return are those in \`bool same_progress_shape(const ResidualProgress& a, const ResidualProgress& b)\`; body-specific behavior: Compare residual progress shape while normalizing counters checked separately. |
| invariants | Compares selected residual progress fields only. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0045

[Lines 240–246](../../../../../tests/unit/residual_exception_test.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_progress(const ResidualProgress& a, const ResidualProgress& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare full residual progress values including counters. |
| inputs / outputs | Inputs and return are those in \`bool same_progress(const ResidualProgress& a, const ResidualProgress& b)\`; body-specific behavior: Compare full residual progress values including counters. |
| invariants | Full covered-field equality is used before/after failure and retry. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0047

[Lines 248–253](../../../../../tests/unit/residual_exception_test.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool counters_monotone(const WorkCounters& before, const WorkCounters& after) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each work counter is monotone componentwise. |
| inputs / outputs | Inputs and return are those in \`bool counters_monotone(const WorkCounters& before, const WorkCounters& after)\`; body-specific behavior: Check each work counter is monotone componentwise. |
| invariants | Counters may advance on failed work; each named component must not decrease. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0049

[Lines 255–259](../../../../../tests/unit/residual_exception_test.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool progress_counters_monotone(const ResidualProgress& before, const ResidualProgress& after) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check residual progress counter monotonicity through the covered fields. |
| inputs / outputs | Inputs and return are those in \`bool progress_counters_monotone(const ResidualProgress& before, const ResidualProgress& after)\`; body-specific behavior: Check residual progress counter monotonicity through the covered fields. |
| invariants | Monotonicity is only over the explicit compared counter fields. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0051

[Lines 261–264](../../../../../tests/unit/residual_exception_test.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_trace(const ResidualTrace& a, const ResidualTrace& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optional immutable trace handles by presence and value. |
| inputs / outputs | Inputs and return are those in \`bool same_trace(const ResidualTrace& a, const ResidualTrace& b)\`; body-specific behavior: Compare optional immutable trace handles by presence and value. |
| invariants | Presence and exported trace equality define this optional-handle comparator. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0053

[Lines 266–270](../../../../../tests/unit/residual_exception_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_candidate(const ResidualCandidate& a, const ResidualCandidate& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optional candidate handles by presence and value. |
| inputs / outputs | Inputs and return are those in \`bool same_candidate(const ResidualCandidate& a, const ResidualCandidate& b)\`; body-specific behavior: Compare optional candidate handles by presence and value. |
| invariants | Presence and exported candidate equality define this optional-handle comparator. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0054

[Lines 271–273](../../../../../tests/unit/residual_exception_test.cpp#L271); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L271-L273:sha256:929c414dff4a792e963b678afea4332ef2578db62d1e885745396df01f703973
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare residual_exception_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0055

[Lines 274–278](../../../../../tests/unit/residual_exception_test.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResidualOptions options_for(ResidualMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build options for a selected residual mode with fixture defaults. |
| inputs / outputs | Inputs and return are those in \`ResidualOptions options_for(ResidualMode mode)\`; body-specific behavior: Build options for a selected residual mode with fixture defaults. |
| invariants | Mode selection does not make a candidate an exact original-query proof. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0057

[Lines 280–286](../../../../../tests/unit/residual_exception_test.cpp#L280); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Baseline {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the measured advance-allocation count and the public trace/candidate/progress result from a clean calibration. |
| inputs / outputs | Inputs and return are those in \`struct Baseline\`; body-specific behavior: Hold the measured advance-allocation count and the public trace/candidate/progress result from a clean calibration. |
| invariants | Calibration count is observed through this executable’s replacement-new tracker and is reset around advance only. |
| ownership | Stores a copied baseline advance request count and optional public outputs/handles as values. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0059

[Lines 288–331](../../../../../tests/unit/residual_exception_test.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Baseline calibrate(const Fixture& fixture, ResidualMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one clean ResidualSearch advance to completion and capture the tracker count plus public baseline result for this mode. |
| inputs / outputs | Inputs and return are those in \`Baseline calibrate(const Fixture& fixture, ResidualMode mode)\`; body-specific behavior: Run one clean ResidualSearch advance to completion and capture the tracker count plus public baseline result for this mode. |
| invariants | Clean calibration measures tracked-new calls during advance only; ResidualSearch::create and fixture construction occur before the count is reset. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0061

[Lines 333–337](../../../../../tests/unit/residual_exception_test.cpp#L333); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool allocation_stop(const ResidualAdvance& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize only public allocation-stop statuses used by the fail sweep. |
| inputs / outputs | Inputs and return are those in \`bool allocation_stop(const ResidualAdvance& value)\`; body-specific behavior: Recognize only public allocation-stop statuses used by the fail sweep. |
| invariants | Only statuses explicitly named in the helper count as allocation stop. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0063

[Lines 339–342](../../../../../tests/unit/residual_exception_test.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool trace_same_optional(const std::optional<ResidualTrace>& a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optional trace values without conflating absent with present. |
| inputs / outputs | Inputs and return are those in \`bool trace_same_optional(const std::optional&lt;ResidualTrace&gt;& a, const std::optional&lt;ResidualTrace&gt;& b)\`; body-specific behavior: Compare optional trace values without conflating absent with present. |
| invariants | An absent handle is not equal to an empty trace. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0065

[Lines 344–347](../../../../../tests/unit/residual_exception_test.cpp#L344); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool candidate_same_optional(const std::optional<ResidualCandidate>& a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optional candidate values without conflating absent with present. |
| inputs / outputs | Inputs and return are those in \`bool candidate_same_optional(const std::optional&lt;ResidualCandidate&gt;& a, const std::optional&lt;ResidualCandidate&gt;& b)\`; body-specific behavior: Compare optional candidate values without conflating absent with present. |
| invariants | An absent handle is not equal to an empty candidate. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0067

[Lines 349–360](../../../../../tests/unit/residual_exception_test.cpp#L349); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Coverage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate observed public phase coverage flags for trace, candidate, exact replay, and repair. |
| inputs / outputs | Inputs and return are those in \`struct Coverage\`; body-specific behavior: Accumulate observed public phase coverage flags for trace, candidate, exact replay, and repair. |
| invariants | Coverage means public status/handle transition observed in the fixture, not a map of internal allocation locations. |
| ownership | Owns booleans/coverage flags by value. |
| failure | Plain test data declaration; no custom error handling. |
| cost | Plain fixture data; no runtime work. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0069

[Lines 362–382](../../../../../tests/unit/residual_exception_test.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void update_coverage(Coverage& coverage, const ResidualProgress& p,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Update phase flags from public progress and optional handles; flags do not identify exact internal allocation sites. |
| inputs / outputs | Inputs and return are those in \`void update_coverage(Coverage& coverage, const ResidualProgress& p, const std::optional&lt;ResidualTrace&gt;& trace, const std::optional&lt;ResidualCandidate&gt;& candidate)\`; body-specific behavior: Update phase flags from public progress and optional handles; flags do not identify exact internal allocation sites. |
| invariants | Flags are inferred from public progress, returned handles, and phase state. |
| ownership | Mutates the caller-owned Coverage; progress/trace/candidate observations are borrowed. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0071

[Lines 384–538](../../../../../tests/unit/residual_exception_test.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void residual_oom_sweep(const Fixture& fixture, ResidualMode mode, const Baseline& baseline,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fail-after points in ResidualSearch::advance, checking repeated failure stability then retrying the same owner to the clean result. |
| inputs / outputs | Inputs and return are those in \`void residual_oom_sweep(const Fixture& fixture, ResidualMode mode, const Baseline& baseline, Coverage& coverage, const char* label)\`; body-specific behavior: Sweep ordinary-new fail-after points in ResidualSearch::advance, checking repeated failure stability then retrying the same owner to the clean result. |
| invariants | Creates ResidualSearch before arming/resetting the counter; sweep targets advance only. Every failed point repeats on the same owner, and retry occurs after disabling the shim. Comparator is same clean fixture/result, not exact allocation-location coverage. |
| ownership | Fixture and clean baseline are borrowed; coverage is mutated by reference; each search owner/handle in an iteration is local, and retry stays on that same owner. |
| failure | Only catches/repeats the expected std::bad_alloc outcomes in its armed ordinary-new sweep; other failure/mismatch paths throw and abort the test. No direct malloc/realloc, systemcall, MemoryAccount, aligned replacement, or allocator-wide guarantee. |
| cost | For each observed advance-time tracker request, builds a fresh fixture/owner, injects one persistent failure, repeats stability checks, then retries the same owner after disarming; bounded by baseline count, not CPU time. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0073

[Lines 540–556](../../../../../tests/unit/residual_exception_test.cpp#L540); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void trace_verifier_is_independent_and_resource_honest(const Fixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check trace verification against the independent residual oracle and bounded verifier resource outcomes. |
| inputs / outputs | Inputs and return are those in \`void trace_verifier_is_independent_and_resource_honest(const Fixture& fixture, const ResidualTrace& trace)\`; body-specific behavior: Check trace verification against the independent residual oracle and bounded verifier resource outcomes. |
| invariants | Valid trace consistency is checked against tests/reference residual oracle; the verifier does not prove original minimum height. |
| ownership | Fixture and trace handle are borrowed for verification; verifier outputs are local. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0075

[Lines 558–626](../../../../../tests/unit/residual_exception_test.cpp#L558); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void limit_extensions_and_zero_quanta(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise selected residual ceilings and test inert zero grants plus same-owner continuation to completion. |
| inputs / outputs | Inputs and return are those in \`void limit_extensions_and_zero_quanta(const Fixture& fixture)\`; body-specific behavior: Raise selected residual ceilings and test inert zero grants plus same-owner continuation to completion. |
| invariants | Limits are logical planner ceilings and quanta; elapsed wall-clock time is not asserted. |
| ownership | Fixture is borrowed; each continuation owner and exported result is local to the scoped attempt. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Runs finite zero-grant and limit-extension continuation cases on small fixtures; no elapsed-time bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0077

[Lines 628–698](../../../../../tests/unit/residual_exception_test.cpp#L628); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cancellation_lifecycle_and_outliving_handles(const Fixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel a retained residual owner, preserve already-returned immutable handles, and create/retry a separate owner where stated. |
| inputs / outputs | Inputs and return are those in \`void cancellation_lifecycle_and_outliving_handles(const Fixture& fixture)\`; body-specific behavior: Cancel a retained residual owner, preserve already-returned immutable handles, and create/retry a separate owner where stated. |
| invariants | Cancellation discards private owner work; previously copied immutable trace/candidate handles can outlive that owner. A new owner is a separate run. |
| ownership | Fixture is borrowed; each search owner and copied public handle is local, with saved handles retained independently across cancel/drop. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Runs finite cancellation/handle-lifetime cases; no allocation-location or total-heap bound. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0079

[Lines 700–773](../../../../../tests/unit/residual_exception_test.cpp#L700); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the selected projected, graft/repair, seven-atom and nine-atom residual exactness and fault cases. |
| inputs / outputs | Inputs and return are those in \`void run()\`; body-specific behavior: Run the selected projected, graft/repair, seven-atom and nine-atom residual exactness and fault cases. |
| invariants | Finite named fixtures use P03 only for their small supported scope and P06/exact search for original-query authority; no unproved round-plus-one claim. |
| ownership | Creates all fixtures, owners, and independent outputs as local values; no global runtime is kept. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Runs the finite projected/grafted/seven- and nine-atom scenarios; P06 proof work is fixture-specific. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |

## B0080

[Lines 774–775](../../../../../tests/unit/residual_exception_test.cpp#L774); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L774-L775:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in residual_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/code_review.md](../../../../code_review.md) |

## B0081

[Lines 776–786](../../../../../tests/unit/residual_exception_test.cpp#L776); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the residual exception fixtures, report diagnostic/counter summaries, and return conventional status. |
| inputs / outputs | Inputs and return are those in \`int main()\`; body-specific behavior: Run the residual exception fixtures, report diagnostic/counter summaries, and return conventional status. |
| invariants | No test execution is asserted by the presence of this main contract. |
| ownership | All test/runtime owners are local to main; no object escapes process scope. |
| failure | Catches std::exception to print failure and return 1; no test result is claimed by this source review. |
| cost | Invokes the finite \`run()\` suite and formats only diagnostics/counters. |
| Design | [tests/unit/residual_exception_test.cpp](../../../../../tests/unit/residual_exception_test.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/planner_continuations.md § Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md § Lifetime and output](../../../../planner_continuations.md) |
