# `tests/unit/result_cursor_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/result_cursor_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `340cf956a7ec7638eeb3c7357b8a5ee585afd3d2c0e7680e7890a9595f30c05e`. 817 lines partitioned into 87 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–32](../../../../../tests/unit/result_cursor_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Keep the injector local to this executable. The noinline wrapper prevents · [reviewed contract](#b0001) |
| [B0002 · 33–40](../../../../../tests/unit/result_cursor_exception_test.cpp#L33) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 41–47](../../../../../tests/unit/result_cursor_exception_test.cpp#L41) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 48–49](../../../../../tests/unit/result_cursor_exception_test.cpp#L48) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 50–50](../../../../../tests/unit/result_cursor_exception_test.cpp#L50) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 51–51](../../../../../tests/unit/result_cursor_exception_test.cpp#L51) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 52–52](../../../../../tests/unit/result_cursor_exception_test.cpp#L52) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 53–53](../../../../../tests/unit/result_cursor_exception_test.cpp#L53) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 54–54](../../../../../tests/unit/result_cursor_exception_test.cpp#L54) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 55–55](../../../../../tests/unit/result_cursor_exception_test.cpp#L55) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 56–64](../../../../../tests/unit/result_cursor_exception_test.cpp#L56) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;ResultCursor&gt;); · [reviewed contract](#b0011) |
| [B0012 · 65–67](../../../../../tests/unit/result_cursor_exception_test.cpp#L65) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0012) |
| [B0013 · 68–68](../../../../../tests/unit/result_cursor_exception_test.cpp#L68) | Explanatory comments or spacing. |  |
| [B0014 · 69–78](../../../../../tests/unit/result_cursor_exception_test.cpp#L69) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::runtime_error, std::string; guard check(failure.code() == code, "unexpected cursor error code"); · [reviewed contract](#b0014) |
| [B0015 · 79–79](../../../../../tests/unit/result_cursor_exception_test.cpp#L79) | Explanatory comments or spacing. |  |
| [B0016 · 80–80](../../../../../tests/unit/result_cursor_exception_test.cpp#L80) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0016) |
| [B0017 · 81–81](../../../../../tests/unit/result_cursor_exception_test.cpp#L81) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0017) |
| [B0018 · 82–82](../../../../../tests/unit/result_cursor_exception_test.cpp#L82) | Explanatory comments or spacing. |  |
| [B0019 · 83–86](../../../../../tests/unit/result_cursor_exception_test.cpp#L83) | Callable definition: const std::string& long_key() | calls value; returns value · [reviewed contract](#b0019) |
| [B0020 · 87–87](../../../../../tests/unit/result_cursor_exception_test.cpp#L87) | Explanatory comments or spacing. |  |
| [B0021 · 88–91](../../../../../tests/unit/result_cursor_exception_test.cpp#L88) | Callable definition: const std::string& long_sql_constant() | calls value; returns value · [reviewed contract](#b0021) |
| [B0022 · 92–92](../../../../../tests/unit/result_cursor_exception_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0023 · 93–107](../../../../../tests/unit/result_cursor_exception_test.cpp#L93) | Callable definition: PhysicalPlan join_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0023) |
| [B0024 · 108–108](../../../../../tests/unit/result_cursor_exception_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0025 · 109–112](../../../../../tests/unit/result_cursor_exception_test.cpp#L109) | Callable definition: std::optional&lt;VariableId&gt; variable_term(const Term& term) | calls ; returns *variable; {} · [reviewed contract](#b0025) |
| [B0026 · 113–113](../../../../../tests/unit/result_cursor_exception_test.cpp#L113) | Explanatory comments or spacing. |  |
| [B0027 · 114–143](../../../../../tests/unit/result_cursor_exception_test.cpp#L114) | Callable definition: FreeConnexTree sql_tree(const Query& query) | calls empty, scopes, size, variable_term; returns {}; tree; growth insert, push_back; 5 loop sites · [reviewed contract](#b0027) |
| [B0028 · 144–144](../../../../../tests/unit/result_cursor_exception_test.cpp#L144) | Explanatory comments or spacing. |  |
| [B0029 · 145–160](../../../../../tests/unit/result_cursor_exception_test.cpp#L145) | Callable definition: PhysicalPlan sql_output_plan() | calls long_sql_constant, frontend::bind_sql, check, frontend::normalize_sql; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(binding), "SQL output mapping fixture did not bind…; returns plan · [reviewed contract](#b0029) |
| [B0030 · 161–161](../../../../../tests/unit/result_cursor_exception_test.cpp#L161) | Explanatory comments or spacing. |  |
| [B0031 · 162–171](../../../../../tests/unit/result_cursor_exception_test.cpp#L162) | Callable definition: PhysicalPlan exists_plan() | calls frontend::bind_sql, check, frontend::normalize_sql, std::move; guard check(std::holds_alternative&lt;frontend::BoundSql&gt;(binding), "EXISTS cursor fixture did not bind");; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0031) |
| [B0032 · 172–172](../../../../../tests/unit/result_cursor_exception_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0033 · 173–177](../../../../../tests/unit/result_cursor_exception_test.cpp#L173) | Callable definition: PhysicalRuntimeOptions runtime_options() | calls ; returns result · [reviewed contract](#b0033) |
| [B0034 · 178–178](../../../../../tests/unit/result_cursor_exception_test.cpp#L178) | Explanatory comments or spacing. |  |
| [B0035 · 179–179](../../../../../tests/unit/result_cursor_exception_test.cpp#L179) | Callable definition: Row left_row(std::int64_t x) | calls s, long_key, n; returns {s(long_key()), n(x)} · [reviewed contract](#b0035) |
| [B0036 · 180–180](../../../../../tests/unit/result_cursor_exception_test.cpp#L180) | Callable definition: Row right_row(std::int64_t y) | calls s, long_key, n; returns {s(long_key()), n(y)} · [reviewed contract](#b0036) |
| [B0037 · 181–181](../../../../../tests/unit/result_cursor_exception_test.cpp#L181) | Explanatory comments or spacing. |  |
| [B0038 · 182–185](../../../../../tests/unit/result_cursor_exception_test.cpp#L182) | Callable definition: std::vector&lt;Row&gt; expected_join_rows() | calls s, long_key, n; returns {{s(long_key()), n(1), n(10)}, {s(long_key()), n(1), n(20)}, · [reviewed contract](#b0038) |
| [B0039 · 186–186](../../../../../tests/unit/result_cursor_exception_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0040 · 187–196](../../../../../tests/unit/result_cursor_exception_test.cpp#L187) | Callable definition: PhysicalRuntime make_physical_join(const PhysicalPlan& plan) | calls runtime_options, apply, left_row, right_row; guard check(runtime.has_answer() && runtime.sequence() == 4, "physical cursor fixture did not reach its f…; returns runtime; growth insert · [reviewed contract](#b0040) |
| [B0041 · 197–197](../../../../../tests/unit/result_cursor_exception_test.cpp#L197) | Explanatory comments or spacing. |  |
| [B0042 · 198–207](../../../../../tests/unit/result_cursor_exception_test.cpp#L198) | Callable definition: SupportRuntime make_support_join(const PhysicalPlan& plan) | calls runtime_options, apply, left_row, right_row; guard check(runtime.has_answer() && runtime.sequence() == 4, "support cursor fixture did not reach its fu…; returns runtime; growth insert · [reviewed contract](#b0042) |
| [B0043 · 208–208](../../../../../tests/unit/result_cursor_exception_test.cpp#L208) | Explanatory comments or spacing. |  |
| [B0044 · 209–213](../../../../../tests/unit/result_cursor_exception_test.cpp#L209) | Callable definition: io::Json row_image(const Row& row) | calls io::Json::array, push_back, io::write_scalar; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 214–214](../../../../../tests/unit/result_cursor_exception_test.cpp#L214) | Explanatory comments or spacing. |  |
| [B0046 · 215–218](../../../../../tests/unit/result_cursor_exception_test.cpp#L215) | Callable definition: std::optional&lt;SupportHandle&gt; lookup_support(const SupportRuntime& runtime, NodeId node, SupportRole role, const Row& values) | calls find; returns runtime.find(node, role, values) · [reviewed contract](#b0046) |
| [B0047 · 219–222](../../../../../tests/unit/result_cursor_exception_test.cpp#L219) | Callable definition: std::optional&lt;SupportHandle&gt; lookup_support(const PhysicalRuntime& runtime, NodeId node, SupportRole role, const Row& values) | calls find_support; returns runtime.find_support(node, role, values) · [reviewed contract](#b0047) |
| [B0048 · 223–225](../../../../../tests/unit/result_cursor_exception_test.cpp#L223) | Callable definition: std::optional&lt;storage::Tuple&gt; read_support(const SupportRuntime& runtime, SupportHandle handle) | calls get; returns runtime.get(handle) · [reviewed contract](#b0048) |
| [B0049 · 226–228](../../../../../tests/unit/result_cursor_exception_test.cpp#L226) | Callable definition: std::optional&lt;storage::Tuple&gt; read_support(const PhysicalRuntime& runtime, SupportHandle handle) | calls get_support; returns runtime.get_support(handle) · [reviewed contract](#b0049) |
| [B0050 · 229–229](../../../../../tests/unit/result_cursor_exception_test.cpp#L229) | Explanatory comments or spacing. |  |
| [B0051 · 230–253](../../../../../tests/unit/result_cursor_exception_test.cpp#L230) | Callable definition: template &lt;class Runtime&gt; io::Json support_handle_image(const Runtime& runtime, const SupportSnapshot& snapshot) | calls io::Json::array, read_support, check, layout; guard check(stored && stored-&gt;layout().same_token(tuple.layout()) && stored-&gt;values() == tuple.values(),; returns result; growth push_back; 5 loop sites · [reviewed contract](#b0051) |
| [B0052 · 254–254](../../../../../tests/unit/result_cursor_exception_test.cpp#L254) | Explanatory comments or spacing. |  |
| [B0053 · 255–260](../../../../../tests/unit/result_cursor_exception_test.cpp#L255) | Callable definition: io::Json state_image(const SupportRuntime& runtime) | calls snapshot, sequence, has_answer, io::write_support_snapshot; returns {{@ , runtime.sequence()}, {@ , runtime.has_answer()}, · [reviewed contract](#b0053) |
| [B0054 · 261–261](../../../../../tests/unit/result_cursor_exception_test.cpp#L261) | Explanatory comments or spacing. |  |
| [B0055 · 262–291](../../../../../tests/unit/result_cursor_exception_test.cpp#L262) | Callable definition: io::Json state_image(const PhysicalRuntime& runtime) | calls snapshot, io::Json::array, size, push_back; guard check(handle.has_value(), "physical snapshot row lost its public source handle");; returns {{@ , runtime.sequence()}, {@ , runtime.has_answer()},; growth push_back; 4 loop sites · [reviewed contract](#b0055) |
| [B0056 · 292–292](../../../../../tests/unit/result_cursor_exception_test.cpp#L292) | Explanatory comments or spacing. |  |
| [B0057 · 293–303](../../../../../tests/unit/result_cursor_exception_test.cpp#L293) | Callable definition: void check_startup(const ResultCursor& cursor, const auto& plan, bool scalar = false) | calls metrics, enumeration, size, check; guard check(startup.route_checks == 1 && startup.frame_initializations == expected_frames, · [reviewed contract](#b0057) |
| [B0058 · 304–304](../../../../../tests/unit/result_cursor_exception_test.cpp#L304) | Explanatory comments or spacing. |  |
| [B0059 · 305–309](../../../../../tests/unit/result_cursor_exception_test.cpp#L305) | Callable definition: void check_phase_sum(const ResultCursorMetrics& metrics) | calls check; guard check(metrics.total_work == metrics.startup.work + metrics.results.work + · [reviewed contract](#b0059) |
| [B0060 · 310–310](../../../../../tests/unit/result_cursor_exception_test.cpp#L310) | Explanatory comments or spacing. |  |
| [B0061 · 311–331](../../../../../tests/unit/result_cursor_exception_test.cpp#L311) | Callable definition: std::vector&lt;Row&gt; drain(ResultCursor& cursor) | calls next, push_back, crown::storage::export_row, values; guard check(cursor.metrics().last.rows_emitted == 1 &&; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0061) |
| [B0062 · 332–332](../../../../../tests/unit/result_cursor_exception_test.cpp#L332) | Explanatory comments or spacing. |  |
| [B0063 · 333–361](../../../../../tests/unit/result_cursor_exception_test.cpp#L333) | Callable definition: template &lt;class Runtime, class MakeRuntime, class MakeCursor, class Image&gt; std::size_t sweep_factory_faults(MakeRuntime make_runt… | calls make_runtime, image, fault, make_cursor; guard check(runtime.ready(), std::string(label) + ": successful factory left a reader lease");; returns failures; 1 loop sites · [reviewed contract](#b0063) |
| [B0064 · 362–362](../../../../../tests/unit/result_cursor_exception_test.cpp#L362) | Explanatory comments or spacing. |  |
| [B0065 · 363–369](../../../../../tests/unit/result_cursor_exception_test.cpp#L363) | Type/record definition: struct NextFailureKinds |  · [reviewed contract](#b0065) |
| [B0066 · 370–370](../../../../../tests/unit/result_cursor_exception_test.cpp#L370) | Explanatory comments or spacing. |  |
| [B0067 · 371–424](../../../../../tests/unit/result_cursor_exception_test.cpp#L371) | Callable definition: template &lt;class Runtime, class MakeRuntime, class MakeCursor, class Image&gt; std::size_t sweep_next_faults(MakeRuntime make_runtime… | calls make_runtime, image, make_cursor, check_startup; guard check(yielded && yielded-&gt;values() == expected.front(),; returns failures; 1 loop sites · [reviewed contract](#b0067) |
| [B0068 · 425–425](../../../../../tests/unit/result_cursor_exception_test.cpp#L425) | Explanatory comments or spacing. |  |
| [B0069 · 426–497](../../../../../tests/unit/result_cursor_exception_test.cpp#L426) | Callable definition: template &lt;class Runtime, class MakeRuntime, class MakeCursor, class Image&gt; std::size_t sweep_later_next_faults(MakeRuntime make_r… | calls make_runtime, image, make_cursor, check_startup; guard check(row && row-&gt;values() == expected\[i\],; returns failures; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0069) |
| [B0070 · 498–498](../../../../../tests/unit/result_cursor_exception_test.cpp#L498) | Explanatory comments or spacing. |  |
| [B0071 · 499–513](../../../../../tests/unit/result_cursor_exception_test.cpp#L499) | Callable definition: template &lt;class Runtime, class MakeCursor, class Image&gt; void check_factory_work_limit(Runtime& runtime, MakeCursor make_cursor, I… | calls image, expect_error, make_cursor, check; guard check(runtime.ready() && image(runtime) == before, · [reviewed contract](#b0071) |
| [B0072 · 514–514](../../../../../tests/unit/result_cursor_exception_test.cpp#L514) | Explanatory comments or spacing. |  |
| [B0073 · 515–541](../../../../../tests/unit/result_cursor_exception_test.cpp#L515) | Callable definition: template &lt;class Runtime, class MakeCursor, class Image&gt; void check_next_work_limit(Runtime& runtime, MakeCursor make_cursor, Imag… | calls make_cursor, metrics, next, check; guard check(first && first-&gt;values() == expected.front(), std::string(label) + ": work probe missed first… · [reviewed contract](#b0073) |
| [B0074 · 542–542](../../../../../tests/unit/result_cursor_exception_test.cpp#L542) | Explanatory comments or spacing. |  |
| [B0075 · 543–561](../../../../../tests/unit/result_cursor_exception_test.cpp#L543) | Callable definition: template &lt;class Runtime, class MakeCursor, class Image, class Mutate&gt; void check_read_only_lease(Runtime& runtime, MakeCursor mak… | calls image, make_cursor, check, ready; guard check(!runtime.ready() && cursor.active(), std::string(label) + ": active result cursor did not hol… · [reviewed contract](#b0075) |
| [B0076 · 562–562](../../../../../tests/unit/result_cursor_exception_test.cpp#L562) | Explanatory comments or spacing. |  |
| [B0077 · 563–580](../../../../../tests/unit/result_cursor_exception_test.cpp#L563) | Callable definition: template &lt;class Runtime, class MakeCursor, class Image&gt; void check_one_failed_lease_keeps_another(Runtime& runtime, MakeCursor ma… | calls make_cursor, metrics, cancel, image; guard check(!runtime.ready(), std::string(label) + ": multiple cursors did not hold the runtime read-only… · [reviewed contract](#b0077) |
| [B0078 · 581–581](../../../../../tests/unit/result_cursor_exception_test.cpp#L581) | Explanatory comments or spacing. |  |
| [B0079 · 582–615](../../../../../tests/unit/result_cursor_exception_test.cpp#L582) | Callable definition: template &lt;class MakeRuntime, class Image&gt; void check_cursor_allocation_failure_preserves_yielded_row(const PhysicalPlan& plan, Ma… | calls make_runtime, image, results, next; guard check(saved && saved-&gt;values() == expected_join_rows().front(), "yielded row fixture missed its fir…; source comment (unverified): // Scalar-view scratch is allocated first. The complete compact row is · [reviewed contract](#b0079) |
| [B0080 · 616–616](../../../../../tests/unit/result_cursor_exception_test.cpp#L616) | Explanatory comments or spacing. |  |
| [B0081 · 617–656](../../../../../tests/unit/result_cursor_exception_test.cpp#L617) | Callable definition: void check_no_allocation_cleanup(const PhysicalPlan& plan) | calls make_support_join, results, forbid_allocations, cancel; guard check(cursor.state() == ResultCursorState::cancelled && support.ready(),; growth emplace · [reviewed contract](#b0081) |
| [B0082 · 657–657](../../../../../tests/unit/result_cursor_exception_test.cpp#L657) | Explanatory comments or spacing. |  |
| [B0083 · 658–673](../../../../../tests/unit/result_cursor_exception_test.cpp#L658) | Callable definition: void check_active_facade_moves_and_destruction(const PhysicalPlan& plan) | calls expected_join_rows, runtime_options, apply, left_row; guard check(!moved.ready() && cursor-&gt;active(), "moving an active facade detached its result cursor lease…; growth emplace, insert · [reviewed contract](#b0083) |
| [B0084 · 674–674](../../../../../tests/unit/result_cursor_exception_test.cpp#L674) | Explanatory comments or spacing. |  |
| [B0085 · 675–704](../../../../../tests/unit/result_cursor_exception_test.cpp#L675) | Callable definition: void check_sql_outputs_and_exists(const PhysicalPlan& output_plan, const PhysicalPlan& boolean_plan) | calls runtime_options, apply, n, results; guard check(first.layout().same_token(second.layout()), "SQL cursors did not share their runtime output l…; growth insert · [reviewed contract](#b0085) |
| [B0086 · 705–707](../../../../../tests/unit/result_cursor_exception_test.cpp#L705) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0086) |
| [B0087 · 708–817](../../../../../tests/unit/result_cursor_exception_test.cpp#L708) | Callable definition: int main() | calls join_plan, sql_output_plan, exists_plan, expected_join_rows; guard check(support_factory_points &gt; 0 && physical_factory_points &gt; 0,; returns make_support_join(plan); make_physical_join(plan); growth insert · [reviewed contract](#b0087) |

## B0001

[Lines 1–32](../../../../../tests/unit/result_cursor_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L32:sha256:2d707b01340d4bf6a18ac1c7d347136fc99648171da23e7cf08764a447845d8c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare result_cursor_exception_test.cpp: include "crown/api/error.hpp", "crown/frontend/normalize.hpp", "crown/io/document.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;iterator&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 33–40](../../../../../tests/unit/result_cursor_exception_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count an injected ordinary-new request and back admitted storage with malloc. |
| inputs / outputs | Takes size; increments the thread-local fail-after transition when armed, maps zero bytes to one malloc byte, then returns storage or throws bad_alloc. |
| invariants | The zero point throws before malloc; a real malloc null also throws bad_alloc. This helper backs only the directly replaced ordinary throwing scalar/array forms. |
| ownership | Returned storage is raw and is released by this executable’s matching delete forms; fail_after is thread-local state. |
| failure | Direct malloc/realloc/system calls and account-admission denial are not injected. No dedicated aligned/nothrow replacement is defined; indirect delegation is not asserted coverage. |
| cost | One threshold branch and, when allowed, one malloc. This is request injection, not bytes, RSS or CPU accounting. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0003

[Lines 41–47](../../../../../tests/unit/result_cursor_exception_test.cpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope the thread-local fail-after threshold used by the cursor fault sweeps. |
| inputs / outputs | Optional step initializes fail_after; forbid_allocations changes it to zero; destructor resets it to -1. |
| invariants | The seam fails an ordinary-new request once the remaining count reaches zero; it is not a stack for nested scopes. |
| ownership | Mutates only current-thread scalar state and retains no allocation. |
| failure | The noexcept guard methods do not translate errors; a replacement-new request throws bad_alloc. |
| cost | Constant scalar updates; no allocator-wide observation. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0004

[Lines 48–49](../../../../../tests/unit/result_cursor_exception_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L49:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in result_cursor_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 50–50](../../../../../tests/unit/result_cursor_exception_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar throwing global new through the test malloc seam. |
| inputs / outputs | Accepts requested bytes and returns malloc_new storage or propagates bad_alloc. |
| invariants | Defines the ordinary scalar overload only; no dedicated aligned/nothrow replacement is present. |
| ownership | Returned storage is paired with scalar delete in this executable. |
| failure | Direct allocator and system calls are outside the injected path; indirect library delegation is not asserted. |
| cost | One seam call and possible malloc. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0006

[Lines 51–51](../../../../../tests/unit/result_cursor_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array throwing global new through the test malloc seam. |
| inputs / outputs | Accepts bytes and returns storage or propagates bad_alloc. |
| invariants | Defines the ordinary array overload only; it makes no claim about aligned/nothrow delegation. |
| ownership | Returned storage is paired with array delete. |
| failure | Direct malloc/realloc/system failures are not injected. |
| cost | One seam call and possible malloc. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0007

[Lines 52–52](../../../../../tests/unit/result_cursor_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar replacement-new storage with std::free. |
| inputs / outputs | Accepts a pointer and returns void. |
| invariants | Noexcept; release does not use fail_after. |
| ownership | Ownership of the returned allocation transfers to delete. |
| failure | No error reporting; valid allocation pairing is assumed. |
| cost | One free call. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0008

[Lines 53–53](../../../../../tests/unit/result_cursor_exception_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array replacement-new storage with std::free. |
| inputs / outputs | Accepts pointer and returns void. |
| invariants | Noexcept; release does not use fail_after. |
| ownership | Ownership transfers to delete\[\]. |
| failure | No error reporting. |
| cost | One free call. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0009

[Lines 54–54](../../../../../tests/unit/result_cursor_exception_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized scalar delete for the malloc-backed scalar replacement. |
| inputs / outputs | Accepts pointer and ignored size; returns void. |
| invariants | Calls std::free and is noexcept. |
| ownership | Releases storage; retains no state. |
| failure | No error reporting. |
| cost | One free call. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0010

[Lines 55–55](../../../../../tests/unit/result_cursor_exception_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized array delete for the malloc-backed array replacement. |
| inputs / outputs | Accepts pointer and ignored size; returns void. |
| invariants | Calls std::free and is noexcept. |
| ownership | Releases storage; retains no state. |
| failure | No error reporting. |
| cost | One free call. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0011

[Lines 56–64](../../../../../tests/unit/result_cursor_exception_test.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L64:sha256:b53e34d1f81bfb10bd5736c5a681d6dbe62f49f899c2416f8ae515046c30790b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare result_cursor_exception_test.cpp: bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 65–67](../../../../../tests/unit/result_cursor_exception_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one cursor test assertion with a borrowed message. |
| inputs / outputs | Accepts Boolean condition and message view; returns for true or throws runtime_error. |
| invariants | Does not catch/translate CROWN Error. |
| ownership | Borrows the message for the call and retains no runtime. |
| failure | False condition is a test failure; diagnostic string construction can allocate. |
| cost | One branch. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0014

[Lines 69–78](../../../../../tests/unit/result_cursor_exception_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw crown::api::Error with the exact requested code. |
| inputs / outputs | Forwards action, compares failure.code(), and returns only on a match. |
| invariants | Catches Error only; bad_alloc and other exceptions propagate. |
| ownership | Action and code view are borrowed. |
| failure | Missing or mismatched Error throws runtime_error through check. |
| cost | One action call and code comparison. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0016

[Lines 80–80](../../../../../tests/unit/result_cursor_exception_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an int64 fixture Value. |
| inputs / outputs | Accepts integer and returns Value by value. |
| invariants | Preserves scalar value. |
| ownership | Owns only the returned scalar. |
| failure | No test-specific error translation. |
| cost | Constant fixture construction. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0017

[Lines 81–81](../../../../../tests/unit/result_cursor_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a string fixture Value by moving the supplied string. |
| inputs / outputs | Accepts string by value; returns Value. |
| invariants | Move preserves the supplied string contents. |
| ownership | Returned Value owns its string payload. |
| failure | Allocation/move failures propagate. |
| cost | Fixture value construction. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0019

[Lines 83–86](../../../../../tests/unit/result_cursor_exception_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::string& long_key() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the static 512-byte join key used by both factors. |
| inputs / outputs | No arguments; returns const string reference. |
| invariants | Every call observes the same 512-k value. |
| ownership | Static string outlives all fixture rows that copy or view it. |
| failure | Static initialization allocation failure propagates on first call. |
| cost | One-time 512-byte fixture construction, then reference access. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0021

[Lines 88–91](../../../../../tests/unit/result_cursor_exception_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::string& long_sql_constant() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the static 512-byte SQL constant-output marker. |
| inputs / outputs | No arguments; returns const string reference. |
| invariants | Every call observes the same 512-q constant. |
| ownership | Static string outlives normalized output plan and results. |
| failure | Static initialization allocation failure propagates on first call. |
| cost | One-time 512-byte fixture construction, then reference access. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0023

[Lines 93–107](../../../../../tests/unit/result_cursor_exception_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan join_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the two-input natural join fixture over long string key k. |
| inputs / outputs | No arguments; returns PhysicalPlan for a(k,x) join b(k,y), projecting k,x,y. |
| invariants | Both native atoms share string variable k; node tree uses one generalized join-key root. |
| ownership | Returned plan owns compiled fixture metadata. |
| failure | Planner lowering failures propagate. |
| cost | Constructs a small fixed tree and catalog. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0025

[Lines 109–112](../../../../../tests/unit/result_cursor_exception_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VariableId> variable_term(const Term& term) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract a VariableId only when a Query Term holds one. |
| inputs / outputs | Takes Term reference; returns optional VariableId. |
| invariants | Constant terms return empty optional; variable terms return their ID. |
| ownership | Term is borrowed; result is scalar value. |
| failure | No error translation. |
| cost | One variant check. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0027

[Lines 114–143](../../../../../tests/unit/result_cursor_exception_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree sql_tree(const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an enumeration tree from query atom scopes for SQL fixtures. |
| inputs / outputs | Takes Query reference; returns FreeConnexTree. |
| invariants | No atoms yields empty tree; one atom yields one native root; multiple atoms use intersection of all variable scopes as generalized root and one native child per atom. |
| ownership | Query is borrowed; returned tree owns node/scope vectors. |
| failure | Container allocation and malformed query errors propagate. |
| cost | Scans all atom terms and computes common-variable intersections; bounded by fixture query size. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0029

[Lines 145–160](../../../../../tests/unit/result_cursor_exception_test.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan sql_output_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and lower SQL with repeated core output and one long constant marker. |
| inputs / outputs | No arguments; returns normalized PhysicalPlan for DISTINCT r.x, constant marker, repeated r.x. |
| invariants | Assertions require 3 normalized outputs and a ConstantOutput at index 1. |
| ownership | Plan owns normalized SQL mapping and output layout; local binding/program die after lowering. |
| failure | Binding/normalization/lowering or failed fixture checks propagate. |
| cost | Binds/normalizes one SQL statement with a 512-byte constant, then lowers it. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0031

[Lines 162–171](../../../../../tests/unit/result_cursor_exception_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan exists_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and lower scalar SQL EXISTS over r. |
| inputs / outputs | No arguments; returns normalized PhysicalPlan for SELECT EXISTS(SELECT NULL FROM r). |
| invariants | Binding and normalization diagnostics fail the fixture; resulting output is the SQL EXISTS wrapper. |
| ownership | Plan owns normalized program; intermediate objects are local. |
| failure | Binding/normalization/lowering failures propagate. |
| cost | One small frontend bind/normalize/lower sequence. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0033

[Lines 173–177](../../../../../tests/unit/result_cursor_exception_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions runtime_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable support transition capture for physical cursor state images. |
| inputs / outputs | No arguments; returns PhysicalRuntimeOptions with support.capture_transitions true. |
| invariants | Other options retain defaults. |
| ownership | Returned options value owns no runtime. |
| failure | No custom failure path. |
| cost | Plain option construction. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0035

[Lines 179–179](../../../../../tests/unit/result_cursor_exception_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row left_row(std::int64_t x) { return {s(long_key()), n(x)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a left input row using long_key and x. |
| inputs / outputs | Takes int64 x; returns {string key, integer x}. |
| invariants | Uses the shared 512-byte key. |
| ownership | Returned Row owns scalar values. |
| failure | Value/container allocation failure propagates. |
| cost | One two-field fixture row. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0036

[Lines 180–180](../../../../../tests/unit/result_cursor_exception_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row right_row(std::int64_t y) { return {s(long_key()), n(y)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a right input row using long_key and y. |
| inputs / outputs | Takes int64 y; returns {string key, integer y}. |
| invariants | Key equals left_row’s shared join key. |
| ownership | Returned Row owns values. |
| failure | Allocation failure propagates. |
| cost | One two-field fixture row. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0038

[Lines 182–185](../../../../../tests/unit/result_cursor_exception_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> expected_join_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the four exact rows of the 2x2 equality join fixture. |
| inputs / outputs | No arguments; returns vector of k,x,y rows. |
| invariants | Expected Cartesian combinations are x∈{1,2}, y∈{10,20} under one key. |
| ownership | Vector and each Row own values; callers compare exported tuples to it. |
| failure | Fixture allocation failure propagates. |
| cost | Constructs exactly four expected rows. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0040

[Lines 187–196](../../../../../tests/unit/result_cursor_exception_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime make_physical_join(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and seed a PhysicalRuntime join with four committed inserts. |
| inputs / outputs | Takes plan; returns runtime after inserting two left and two right rows. |
| invariants | Requires has_answer, sequence 4, then check_invariants. |
| ownership | Returned facade owns physical source/runtime state. |
| failure | Apply or invariant errors fail fixture construction. |
| cost | Four physical updates over a small join fixture. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp) |

## B0042

[Lines 198–207](../../../../../tests/unit/result_cursor_exception_test.cpp#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime make_support_join(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct and seed a SupportRuntime join equivalent to the physical fixture. |
| inputs / outputs | Takes plan; inserts left records at node1 and right at node2; returns runtime. |
| invariants | Requires answer and sequence 4 and checks invariants. |
| ownership | Returned runtime owns support state. |
| failure | Apply/invariant errors propagate. |
| cost | Four support updates over a small fixture. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0044

[Lines 209–213](../../../../../tests/unit/result_cursor_exception_test.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json row_image(const Row& row) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize each scalar in a Row into an io::Json array. |
| inputs / outputs | Takes borrowed Row; returns JSON array of write_scalar outputs. |
| invariants | Preserves row field order and scalar representation. |
| ownership | Input row is borrowed; JSON owns serialized values. |
| failure | Serialization/allocation errors propagate. |
| cost | Linear in row width. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp) |

## B0046

[Lines 215–218](../../../../../tests/unit/result_cursor_exception_test.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SupportHandle> lookup_support(const SupportRuntime& runtime, NodeId node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a support handle for one node/role/key in SupportRuntime. |
| inputs / outputs | Takes runtime, node, role and row by reference; returns optional handle. |
| invariants | Delegates to runtime.find with the same key. |
| ownership | Runtime and values are borrowed; handle is an owner-tagged scalar value. |
| failure | Lookup errors propagate. |
| cost | One support lookup. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0047

[Lines 219–222](../../../../../tests/unit/result_cursor_exception_test.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SupportHandle> lookup_support(const PhysicalRuntime& runtime, NodeId node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a physical runtime’s support handle for one key. |
| inputs / outputs | Takes runtime/node/role/row; returns optional handle. |
| invariants | Delegates to find_support; preserves owner/node/role/key identity. |
| ownership | Runtime and row are borrowed. |
| failure | Lookup errors propagate. |
| cost | One physical support lookup. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0048

[Lines 223–225](../../../../../tests/unit/result_cursor_exception_test.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::Tuple> read_support(const SupportRuntime& runtime, SupportHandle handle) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an owning tuple for a SupportRuntime handle. |
| inputs / outputs | Takes runtime and handle; returns optional storage::Tuple. |
| invariants | A stale/absent handle returns empty according to get. |
| ownership | Tuple returned by value owns its row; runtime is borrowed. |
| failure | Lookup errors propagate. |
| cost | One handle read. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0049

[Lines 226–228](../../../../../tests/unit/result_cursor_exception_test.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::Tuple> read_support(const PhysicalRuntime& runtime, SupportHandle handle) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an owning tuple for a PhysicalRuntime support handle. |
| inputs / outputs | Takes runtime and handle; returns optional Tuple from get_support. |
| invariants | Does not export or change physical source rows. |
| ownership | Returned Tuple is an owning value. |
| failure | Lookup errors propagate. |
| cost | One support-handle read. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0051

[Lines 230–253](../../../../../tests/unit/result_cursor_exception_test.cpp#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate every support handle embedded in a SupportSnapshot and serialize its row/identity. |
| inputs / outputs | Takes generic runtime and snapshot; returns JSON array over records, survivors, parent keys and visible keys. |
| invariants | Each public handle must resolve; tuple layout token and values must match; survivor/visible keys are looked up by projected values. |
| ownership | Snapshot and runtime are borrowed; JSON output owns serialized fields. |
| failure | Missing/stale handle or tuple mismatch throws runtime_error; lookups/serialization errors propagate. |
| cost | Traverses all captured support rows/keys and performs one public handle read per item. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0053

[Lines 255–260](../../../../../tests/unit/result_cursor_exception_test.cpp#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json state_image(const SupportRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a JSON diagnostic image of SupportRuntime sequence, answer, support snapshot and handles. |
| inputs / outputs | Takes runtime reference; returns Json. |
| invariants | Snapshot state and handle image are both derived from same committed runtime call sequence. |
| ownership | Runtime borrowed; returned Json owns copied report representation. |
| failure | Snapshot/write/handle errors propagate. |
| cost | Materializes support snapshot and serializes all fixture support handles. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0055

[Lines 262–291](../../../../../tests/unit/result_cursor_exception_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json state_image(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a JSON diagnostic image of PhysicalRuntime tables, source handles, derivations and support. |
| inputs / outputs | Takes PhysicalRuntime reference; returns Json. |
| invariants | For each snapshot physical row, source handle must exist and round-trip to same row; derivation rows/counts and support handles are serialized. |
| ownership | Runtime borrowed; snapshot and report Json own values; no mutation occurs. |
| failure | Missing public source/support handle throws runtime_error; snapshot/serializer failures propagate. |
| cost | Traverses physical/support snapshots and performs row/handle export proportional to fixture state. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0057

[Lines 293–303](../../../../../tests/unit/result_cursor_exception_test.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_startup(const ResultCursor& cursor, const auto& plan, bool scalar = false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cursor startup work counters against route and frame initialization expectations. |
| inputs / outputs | Takes cursor, plan and optional scalar flag; returns after assertions. |
| invariants | One route check; frame initializations equal enumeration step count except SQL EXISTS scalar; calls/opens/advances and result/termination/failed work start at zero. |
| ownership | Cursor and plan borrowed. |
| failure | Counter mismatch throws runtime_error. |
| cost | Reads fixed metrics and plan step count. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0059

[Lines 305–309](../../../../../tests/unit/result_cursor_exception_test.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_phase_sum(const ResultCursorMetrics& metrics) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require total cursor abstract work to equal the four phase sums. |
| inputs / outputs | Takes metrics by reference; no return. |
| invariants | startup+results+termination+failed equals total_work. |
| ownership | Metrics borrowed. |
| failure | Mismatch throws runtime_error. |
| cost | Constant number of integer comparisons/additions. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0061

[Lines 311–331](../../../../../tests/unit/result_cursor_exception_test.cpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> drain(ResultCursor& cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a ResultCursor into owning Rows and validate result/termination metric phases. |
| inputs / outputs | Takes mutable cursor; returns vector of exported Row values. |
| invariants | Each row-producing next increments rows_emitted by one; terminal null marks exhausted/releases lease; repeated null calls add no work. |
| ownership | Cursor owns traversal; returned vector rows are exported owning values. |
| failure | Cursor next failures propagate; phase mismatch throws runtime_error. |
| cost | Reads all result rows and one terminal null; no timing assertion. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md) |

## B0063

[Lines 333–361](../../../../../tests/unit/result_cursor_exception_test.cpp#L333); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime, class MakeRuntime, class MakeCursor, class Image>
std::size_t sweep_factory_faults(MakeRuntime make_runtime, MakeCursor make_cursor, Image image,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep cursor-factory ordinary-new fault points for fresh Support/Physical runtimes. |
| inputs / outputs | Takes factories/image; loops threshold 0..63 and returns failures before first successful create/cancel. |
| invariants | Successful factory cancellation leaves runtime ready; failed construction leaves image and readiness unchanged; a new factory on same runtime captures same sequence and releases its lease. |
| ownership | Each iteration owns a fresh runtime; failed cursor construction yields no cursor; successful retry cursor owns/releases lease. |
| failure | Catches bad_alloc from armed factory; failure does not poison runtime. The seam is only ordinary scalar/array throwing new, not all allocation APIs. |
| cost | At most 64 fresh runtime setups per helper; no CPU-time or byte bound. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0065

[Lines 363–369](../../../../../tests/unit/result_cursor_exception_test.cpp#L363); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NextFailureKinds {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record which observed failure locations were reached by the first-next sweep. |
| inputs / outputs | Fields are Boolean flags for live cursor open, key projection, bucket cursor open, result assembly and SQL mapping. |
| invariants | Flags aggregate observed metric predicates; they do not claim exhaustive allocation sites. |
| ownership | Plain value state local to the test. |
| failure | No custom failure path. |
| cost | Five Boolean values. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp) |

## B0067

[Lines 371–424](../../../../../tests/unit/result_cursor_exception_test.cpp#L371); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime, class MakeRuntime, class MakeCursor, class Image>
std::size_t sweep_next_faults(MakeRuntime make_runtime, MakeCursor make_cursor, Image image,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep first-next ordinary-new failure points and require failed cursor closure plus fresh-cursor recovery. |
| inputs / outputs | Takes fresh runtime/cursor/image factories, expected rows and mutable failure-kind flags; returns failure count at first successful threshold. |
| invariants | On bad_alloc cursor is failed/inactive and runtime ready; failure metrics stay in failed phase; image/sequence/handles unchanged; same cursor then rejects invalid_cursor; reopening a new cursor on the same runtime epoch drains exact expected rows. |
| ownership | Runtime survives cursor failure; the cursor is permanently failed; each retry cursor owns a new lease. Expected rows and image are local values. |
| failure | Catches bad_alloc only in armed next; checks invalid_cursor afterward. Direct malloc/system/account denial are not faulted; no aligned/nothrow direct replacement. |
| cost | At most 96 thresholds per runtime family, with one complete retry after each failure; no time guarantee. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md) |

## B0069

[Lines 426–497](../../../../../tests/unit/result_cursor_exception_test.cpp#L426); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime, class MakeRuntime, class MakeCursor, class Image>
std::size_t sweep_later_next_faults(MakeRuntime make_runtime, MakeCursor make_cursor, Image image,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep a later next call after two yielded rows, including deepest backtracking and bucket reopen. |
| inputs / outputs | Takes factories/image/expected rows; for each threshold yields two owned rows, faults the third next, then reopens a cursor. |
| invariants | Prior rows and committed image remain unchanged; failed cursor closes, later next invalid_cursor; metrics preserve two successful rows; at least one failure has frame closes plus bucket lookups; fresh cursor returns full result. This is a fresh cursor retry, not resumption of failed cursor. |
| ownership | Held output tuples own row values across failure/retry; runtime stays same and remains writable once leases close. |
| failure | Catches bad_alloc at third next; other errors/assertion failures propagate. Faults are ordinary-new seam only. |
| cost | At most 96 thresholds, each doing two yields and then full retry; no CPU/delay claim. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md) |

## B0071

[Lines 499–513](../../../../../tests/unit/result_cursor_exception_test.cpp#L499); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime, class MakeCursor, class Image>
void check_factory_work_limit(Runtime& runtime, MakeCursor make_cursor, Image image,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Force zero startup work allowance, then verify a normal new cursor still drains the original result. |
| inputs / outputs | Takes runtime, cursor/image factories, expected rows and label; no return. |
| invariants | resource_limit occurs during cursor construction before a lease is retained; state image and readiness remain unchanged; default-limit retry returns full expected rows. |
| ownership | Runtime remains borrowed and committed; temporary failed/retry cursor ownership is local. |
| failure | Requires exact resource_limit; other errors propagate. This is abstract work-limit rejection, not allocation injection. |
| cost | One failed factory, one full cursor drain and image checks. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0073

[Lines 515–541](../../../../../tests/unit/result_cursor_exception_test.cpp#L515); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime, class MakeCursor, class Image>
void check_next_work_limit(Runtime& runtime, MakeCursor make_cursor, Image image,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate cursor startup/first-row abstract work, then fail a next call one unit short. |
| inputs / outputs | Takes runtime/factory/image/expected/label; measures one probe row then constructs limited cursor. |
| invariants | Budget=startup+first-result-1; next fails at exact total_work and failed.work=result_work-1, releases lease, subsequent next is invalid_cursor, and default cursor retry is complete with unchanged state. |
| ownership | Probe and limited cursors own separate leases; expected relation is local. |
| failure | Exact resource_limit and invalid_cursor codes required; this is abstract work accounting, not CPU time or allocator failure. |
| cost | Two cursor constructions plus one probe and one retry drain. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0075

[Lines 543–561](../../../../../tests/unit/result_cursor_exception_test.cpp#L543); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime, class MakeCursor, class Image, class Mutate>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an active result cursor makes the runtime read-only while ordinary committed reads remain available. |
| inputs / outputs | Takes runtime, cursor/image/mutate functions, expected rows and label. |
| invariants | Active cursor makes ready false; snapshot image is unchanged; mutation is runtime_busy without releasing lease; cancel marks cancelled and restores ready; fresh cursor drains; then mutation succeeds. |
| ownership | Cursor holds a runtime read lease; runtime remains same owner; returned rows own values. |
| failure | Exact runtime_busy and cursor states required. No concurrency/thread lock is tested. |
| cost | One read-only interval, cancellation, full retry drain and one successful mutation. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0077

[Lines 563–580](../../../../../tests/unit/result_cursor_exception_test.cpp#L563); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Runtime, class MakeCursor, class Image>
void check_one_failed_lease_keeps_another(Runtime& runtime, MakeCursor make_cursor, Image image,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify failure of one cursor does not release another cursor’s lease. |
| inputs / outputs | Takes runtime, cursor/image factories, expected rows and label; creates probe, failing cursor and peer. |
| invariants | Failing cursor uses startup_work-only budget and next throws resource_limit; it closes while peer stays active and runtime stays not ready; peer drains exact rows and only then runtime becomes ready. |
| ownership | Both cursors independently hold read leases on the same runtime; runtime snapshot remains committed. |
| failure | Exact resource_limit and state assertions; no allocation injection in this helper. |
| cost | Three cursor opens, one failure, and a full peer drain. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0079

[Lines 582–615](../../../../../tests/unit/result_cursor_exception_test.cpp#L582); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class MakeRuntime, class Image>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject failure on the second result call after preserving the first owning row. |
| inputs / outputs | Takes plan, physical-runtime factory and image helper; saves first cursor tuple then arms fail_after=1 for second next. |
| invariants | Second next fails after all output fields are read; failed cursor closes/releases read lease, image is unchanged, failed cursor cannot continue; same runtime accepts an erase update, and saved first row remains valid after runtime/facade destruction. |
| ownership | Saved storage::Tuple owns its values; cursor failure does not own or invalidate previously returned tuple. |
| failure | Catches bad_alloc from ordinary-new shim; direct allocator/system/account denial are outside. No failed-cursor retry is attempted; only a later runtime update is. |
| cost | One prior row, one injected later failure, one update and post-runtime value check; not all-allocator proof. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md) |

## B0081

[Lines 617–656](../../../../../tests/unit/result_cursor_exception_test.cpp#L617); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_no_allocation_cleanup(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard cancel, cursor destruction and move assignment with fail-all ordinary-new threshold. |
| inputs / outputs | Takes plan; exercises SupportRuntime cancel, PhysicalRuntime cursor destruction, then cursor move assignment between two runtimes. |
| invariants | Cancellation/destruction release leases; move assignment cancels destination’s lease and transfers source cursor lease; source cursor is moved-from and rejects next. Guard observes only requests routed through the directly replaced ordinary new symbols. |
| ownership | Cursor is move-only; runtime facades own support state; moved destination cursor owns the source runtime lease. |
| failure | An intercepted ordinary-new request throws bad_alloc. No direct malloc, system, MemoryAccount denial or dedicated aligned/nothrow path is injected. |
| cost | Several cleanup/move paths under a narrow fail-after guard; not a process-wide no-allocation proof. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0083

[Lines 658–673](../../../../../tests/unit/result_cursor_exception_test.cpp#L658); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_active_facade_moves_and_destruction(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a cursor remains usable after its PhysicalRuntime facade is moved and destroyed. |
| inputs / outputs | Takes plan; seeds runtime, opens cursor, moves facade, exits scope, then drains cursor. |
| invariants | Move does not detach the cursor lease; moved facade is busy while cursor active; cursor remains active and returns expected four rows after original/moved local facade scope ends. |
| ownership | ResultCursor holds shared logical SupportRuntime backing; emitted tuples own rows. Physical facade ownership is distinct from retained logical cursor backing. |
| failure | Fixture state/cursor assertion failures throw runtime_error; traversal errors propagate. |
| cost | One runtime seed, facade move/destruction and complete cursor drain. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/result_cursors.md § Read lease and runtime lifetime](../../../../result_cursors.md) |

## B0085

[Lines 675–704](../../../../../tests/unit/result_cursor_exception_test.cpp#L675); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_sql_outputs_and_exists(const PhysicalPlan& output_plan, const PhysicalPlan& boolean_plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check SQL repeated/constant output mapping, core-view bypass and scalar SQL EXISTS output. |
| inputs / outputs | Takes output plan and Boolean EXISTS plan; constructs/seeds physical runtimes and opens one or more cursors. |
| invariants | SQL cursors share layout token and emit (7,long constant,7); core_results emits core row; EXISTS emits one true Boolean then terminal null with phase metrics and releases lease. |
| ownership | Each cursor owns a read lease; returned Tuples own values; plan/runtime outlive active local cursors. |
| failure | Cursor/runtime errors propagate; mismatched output/layout throws runtime_error. |
| cost | Three small committed query fixtures and full cursor traversals. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md) |

## B0086

[Lines 705–707](../../../../../tests/unit/result_cursor_exception_test.cpp#L705); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L705-L707:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in result_cursor_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0087

[Lines 708–817](../../../../../tests/unit/result_cursor_exception_test.cpp#L708); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all cursor allocation, work-limit, lease, movement, SQL mapping and EXISTS fixtures. |
| inputs / outputs | Receives no args; creates base/SQL plans and runtime/cursor/image/mutation lambdas, runs all sweeps and prints observed counts. |
| invariants | Expected output is fixed four-row join or fixed SQL row; failure sweeps exercise Support, Physical, core and SQL cursor paths; no A04 evaluator or durable sink is used. |
| ownership | Main owns plans/runtimes and lambdas; helpers create independent runtimes/cursors. |
| failure | Catches std::exception, resets fail_after, prints error and returns1; otherwise returns0. |
| cost | Runs selected finite threshold loops (64/96 caps) and small fixed matrices; no build/test execution is asserted here. |
| Design | [tests/unit/result_cursor_exception_test.cpp](../../../../../tests/unit/result_cursor_exception_test.cpp), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |
