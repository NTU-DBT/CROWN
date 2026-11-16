# `tests/unit/fragment_cursor_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/fragment_cursor_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0fa3f3f340b5cd2c938820a22e4d488c1c1f2a547a9cb7d05dbfcc98009c4564`. 673 lines partitioned into 64 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–25](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Keep the injector persistent so cursor and intrusive-list cleanup runs with · [reviewed contract](#b0001) |
| [B0002 · 26–33](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L26) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 34–40](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L34) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 41–42](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L41) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 43–43](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L43) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 44–44](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L44) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 45–45](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L45) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 46–46](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L46) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 47–47](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L47) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 48–48](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L48) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 49–58](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L49) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;SupportRuntime::PendingEpoch&gt;); · [reviewed contract](#b0011) |
| [B0012 · 59–61](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L59) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0012) |
| [B0013 · 62–62](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0014 · 63–72](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L63) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::runtime_error, std::string; guard check(failure.code() == code, "unexpected fragment cursor error code"); · [reviewed contract](#b0014) |
| [B0015 · 73–73](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0016 · 74–74](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L74) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0016) |
| [B0017 · 75–75](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L75) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0017) |
| [B0018 · 76–78](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L76) | Callable definition: Row a_row(std::int64_t x, std::int64_t y, std::string witness) | calls n, s, std::move; returns {n(x), n(y), s(std::move(witness))} · [reviewed contract](#b0018) |
| [B0019 · 79–81](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L79) | Callable definition: Row b_row(std::int64_t x, std::int64_t y, std::string witness) | calls n, s, std::move; returns {n(x), n(y), s(std::move(witness))} · [reviewed contract](#b0019) |
| [B0020 · 82–84](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L82) | Callable definition: Row c_row(std::int64_t x, std::int64_t z, std::string witness) | calls n, s, std::move; returns {n(x), n(z), s(std::move(witness))} · [reviewed contract](#b0020) |
| [B0021 · 85–91](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L85) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0021) |
| [B0022 · 92–111](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L92) | Callable definition: PhysicalPlan make_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree); source comment (unverified): // C is below A but outside the root-connected C* subtree for head {x,y}. · [reviewed contract](#b0022) |
| [B0023 · 112–112](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L112) | Explanatory comments or spacing. |  |
| [B0024 · 113–118](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L113) | Callable definition: const std::vector&lt;Row&gt;& a_rows() | calls a_row; returns rows · [reviewed contract](#b0024) |
| [B0025 · 119–124](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L119) | Callable definition: const std::vector&lt;Row&gt;& b_rows() | calls b_row; returns rows · [reviewed contract](#b0025) |
| [B0026 · 125–130](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L125) | Callable definition: const std::vector&lt;Row&gt;& c_rows() | calls c_row; returns rows · [reviewed contract](#b0026) |
| [B0027 · 131–131](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0028 · 132–144](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L132) | Callable definition: SupportRuntime make_support(const PhysicalPlan& plan) | calls a_rows, apply, b_rows, c_rows; guard check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "support witness fixture did not …; returns runtime; growth insert; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 145–145](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L145) | Explanatory comments or spacing. |  |
| [B0030 · 146–158](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L146) | Callable definition: PhysicalRuntime make_physical(const PhysicalPlan& plan) | calls a_rows, apply, b_rows, c_rows; guard check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "physical witness fixture did not…; returns runtime; growth insert; 3 loop sites · [reviewed contract](#b0030) |
| [B0031 · 159–159](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L159) | Explanatory comments or spacing. |  |
| [B0032 · 160–160](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L160) | Callable definition: void sort_rows(std::vector&lt;Row&gt;& rows) | calls std::sort, begin, end · [reviewed contract](#b0032) |
| [B0033 · 161–161](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L161) | Explanatory comments or spacing. |  |
| [B0034 · 162–169](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L162) | Callable definition: std::vector&lt;Row&gt; drain(Cursor& cursor) | calls next, push_back, crown::storage::export_row, values; guard check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),; returns rows; growth push_back; 1 loop sites · [reviewed contract](#b0034) |
| [B0035 · 170–170](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L170) | Explanatory comments or spacing. |  |
| [B0036 · 171–185](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L171) | Callable definition: std::vector&lt;Row&gt; expected_all_witnesses(bool omit_b10 = false) | calls a_rows, c_rows, b_rows, b_row; returns rows; growth push_back; 3 loop sites · [reviewed contract](#b0036) |
| [B0037 · 186–186](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0038 · 187–198](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L187) | Callable definition: std::vector&lt;Row&gt; expected_a_b() | calls a_rows, b_rows, std::any_of, c_rows; returns a\[0\] == c\[0\] && a\[2\] == c\[2\]; rows; growth push_back; 2 loop sites · [reviewed contract](#b0038) |
| [B0039 · 199–199](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L199) | Explanatory comments or spacing. |  |
| [B0040 · 200–206](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L200) | Callable definition: std::vector&lt;Row&gt; expected_b_c() | calls b_rows, c_rows, push_back, sort_rows; returns rows; growth push_back; 2 loop sites · [reviewed contract](#b0040) |
| [B0041 · 207–207](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0042 · 208–214](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L208) | Callable definition: std::vector&lt;Row&gt; expected_a_c() | calls a_rows, c_rows, push_back, sort_rows; returns rows; growth push_back; 2 loop sites · [reviewed contract](#b0042) |
| [B0043 · 215–215](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L215) | Explanatory comments or spacing. |  |
| [B0044 · 216–222](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L216) | Callable definition: void check_schema(const storage::TupleLayout& layout, std::initializer_list&lt;VariableId&gt; variables, std::string_view message) | calls check, fields, size; guard check(layout.fields().size() == variables.size(), message);; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 223–223](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L223) | Explanatory comments or spacing. |  |
| [B0046 · 224–329](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L224) | Callable definition: void check_fragment_semantics(const PhysicalPlan& plan) | calls make_support, current_view, witnesses, check_schema; guard check(drain(whole) == expected_all_witnesses(), "whole-tree witness traversal lost a factor or hidd…; source comment (unverified): // B and C are not adjacent. Their exact factor set joins only on x, so · [reviewed contract](#b0046) |
| [B0047 · 330–330](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L330) | Explanatory comments or spacing. |  |
| [B0048 · 331–364](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L331) | Callable definition: template &lt;class MakeRuntime&gt; void check_current_witness_factory_sweep(const PhysicalPlan& plan, std::string_view name, MakeRuntim… | calls make_runtime, sequence, current_view, fault; guard check(failures &gt; 0, "current witness factory sweep missed allocation failures");; 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 365–365](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L365) | Explanatory comments or spacing. |  |
| [B0050 · 366–405](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L366) | Callable definition: void check_pending_witness_factory_sweep(const PhysicalPlan& plan, SnapshotSide side) | calls expected_all_witnesses, make_support, sequence, begin_epoch; guard check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "pending witness factory delete was a no-op");; 1 loop sites · [reviewed contract](#b0050) |
| [B0051 · 406–406](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L406) | Explanatory comments or spacing. |  |
| [B0052 · 407–440](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L407) | Callable definition: void check_hidden_completion_factory_sweep(const PhysicalPlan& plan) | calls make_support, sequence, current_view, fault; guard check(failures &gt; 0, "hidden completion factory sweep missed allocation failures");; 1 loop sites · [reviewed contract](#b0052) |
| [B0053 · 441–441](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L441) | Explanatory comments or spacing. |  |
| [B0054 · 442–500](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L442) | Callable definition: void check_witness_next_fault_sweep(const PhysicalPlan& plan, SnapshotSide side, bool later) | calls expected_all_witnesses, make_support, begin_epoch, sequence; guard check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "witness next fixture delete was a no-op");; 1 loop sites · [reviewed contract](#b0054) |
| [B0055 · 501–501](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L501) | Explanatory comments or spacing. |  |
| [B0056 · 502–535](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L502) | Callable definition: void check_pending_commit_noalloc(const PhysicalPlan& plan) | calls make_support, sequence, begin_epoch, check; guard check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "commit witness fixture delete was a no-op");; growth emplace, push_back · [reviewed contract](#b0056) |
| [B0057 · 536–536](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L536) | Explanatory comments or spacing. |  |
| [B0058 · 537–560](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L537) | Callable definition: void check_pending_rollback_noalloc(const PhysicalPlan& plan) | calls make_support, begin_epoch, sequence, check; guard check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "rollback witness fixture delete was a no-op"); · [reviewed contract](#b0058) |
| [B0059 · 561–561](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L561) | Explanatory comments or spacing. |  |
| [B0060 · 562–622](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L562) | Callable definition: void check_pending_move_and_destruction_noalloc(const PhysicalPlan& plan) | calls make_support, emplace, begin_epoch, sequence; guard check(destination-&gt;stage(NodeId{2}, b_row(1, 10, "b10")), "move destination witness update was a no…; growth emplace, insert · [reviewed contract](#b0060) |
| [B0061 · 623–623](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L623) | Explanatory comments or spacing. |  |
| [B0062 · 624–646](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L624) | Callable definition: void check_phase_limits(const PhysicalPlan& plan) | calls make_support, current_view, expect_error, witnesses; guard check(view.valid(), "startup work-limit failure invalidated its epoch view"); · [reviewed contract](#b0062) |
| [B0063 · 647–649](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L647) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0063) |
| [B0064 · 650–673](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L650) | Callable definition: int main() | calls make_plan, check_fragment_semantics, check_current_witness_factory_sweep, check_pending_witness_factory_sweep; returns 1 · [reviewed contract](#b0064) |

## B0001

[Lines 1–25](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L25:sha256:8e3482e4617279bb818ca66c2af27b17af583d4fad863e74a28caebc8b9a00ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare fragment_cursor_exception_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", "crown/storage/reference.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 26–33](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary throwing scalar/array replacement new to malloc with a persistent fail-after seam; fail before malloc at zero. |
| inputs / outputs | Inputs and return are those in \`\[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes)\`; body-specific behavior: Route ordinary throwing scalar/array replacement new to malloc with a persistent fail-after seam; fail before malloc at zero. |
| invariants | fail_after rejects before malloc; ordinary scalar/array replacement symbols are direct coverage only; no aligned/nothrow replacement, direct malloc/account/systemcall injection, or claim about unknown delegation. |
| ownership | No pointer is retained; fail_after is thread-local. |
| failure | Fails with std::bad_alloc before std::malloc at zero; this shim controls only calls reaching directly defined ordinary throwing scalar/array replacements. Direct malloc, account denial and system calls are not injected; unknown indirect delegation is not asserted. |
| cost | One failpoint check plus one malloc request for nonzero bytes; no byte counter or total heap accounting. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0003

[Lines 34–40](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm/reset the thread-local failure index and expose a no-allocation guard; copying the scope is forbidden. |
| inputs / outputs | Inputs and return are those in \`struct FaultScope\`; body-specific behavior: Arm/reset the thread-local failure index and expose a no-allocation guard; copying the scope is forbidden. |
| invariants | FaultScope teardown disarms the thread-local point; forbid_allocations sets zero for covered calls only. |
| ownership | No resource is owned; destructor disarms the thread-local injector. |
| failure | Constructor simply arms the thread-local point; destructor resets it. It is not a process-wide allocator monitor. |
| cost | Constant thread-local assignment on construction/destruction. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0004

[Lines 41–42](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in fragment_cursor_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 43–43](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept ordinary scalar throwing new only. |
| inputs / outputs | Inputs and return are those in \`void* operator new(std::size_t bytes)\`; body-specific behavior: Intercept ordinary scalar throwing new only. |
| invariants | The shim covers calls reaching these ordinary throwing replacement forms; unknown library delegation is not claimed. |
| ownership | Pointer ownership transfers to the allocator caller. |
| failure | Throws std::bad_alloc on armed request or backing malloc failure. |
| cost | One checked malloc request. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0006

[Lines 44–44](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept ordinary array throwing new only. |
| inputs / outputs | Inputs and return are those in \`void* operator new\[\](std::size_t bytes)\`; body-specific behavior: Intercept ordinary array throwing new only. |
| invariants | The shim covers calls reaching these ordinary throwing replacement forms; unknown library delegation is not claimed. |
| ownership | Pointer ownership transfers to the allocator caller. |
| failure | Throws std::bad_alloc on armed request or backing malloc failure. |
| cost | One checked malloc request. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0007

[Lines 45–45](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar replacement allocation storage. |
| inputs / outputs | Inputs and return are those in \`void operator delete(void* pointer) noexcept\`; body-specific behavior: Free scalar replacement allocation storage. |
| invariants | Deallocation form is not an allocation fault or total heap observation. |
| ownership | Consumes/frees the given pointer. |
| failure | Declared noexcept and calls std::free. |
| cost | One free call. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0008

[Lines 46–46](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array replacement allocation storage. |
| inputs / outputs | Inputs and return are those in \`void operator delete\[\](void* pointer) noexcept\`; body-specific behavior: Free array replacement allocation storage. |
| invariants | Deallocation form is not an allocation fault or total heap observation. |
| ownership | Consumes/frees the given pointer. |
| failure | Declared noexcept and calls std::free. |
| cost | One free call. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0009

[Lines 47–47](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized scalar replacement allocation storage. |
| inputs / outputs | Inputs and return are those in \`void operator delete(void* pointer, std::size_t) noexcept\`; body-specific behavior: Free sized scalar replacement allocation storage. |
| invariants | Deallocation form is not an allocation fault or total heap observation. |
| ownership | Consumes/frees the given pointer. |
| failure | Declared noexcept and calls std::free. |
| cost | One free call. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0010

[Lines 48–48](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized array replacement allocation storage. |
| inputs / outputs | Inputs and return are those in \`void operator delete\[\](void* pointer, std::size_t) noexcept\`; body-specific behavior: Free sized array replacement allocation storage. |
| invariants | Deallocation form is not an allocation fault or total heap observation. |
| ownership | Consumes/frees the given pointer. |
| failure | Declared noexcept and calls std::free. |
| cost | One free call. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0011

[Lines 49–58](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L49); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L58:sha256:775f0ade165c57991fc606bc1353d7422794d23a80072af57ff1c6edbf1cadd9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare fragment_cursor_exception_test.cpp: bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 59–61](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one fragment-cursor test assertion. |
| inputs / outputs | Inputs and return are those in \`void check(bool condition, std::string_view message)\`; body-specific behavior: Fail one fragment-cursor test assertion. |
| invariants | False assertion throws runtime_error. |
| ownership | Message view/action borrow their values only during the check call. |
| failure | False assertion throws std::runtime_error. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0014

[Lines 63–72](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an action and require an exact CROWN Error code. |
| inputs / outputs | Inputs and return are those in \`template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code)\`; body-specific behavior: Run an action and require an exact CROWN Error code. |
| invariants | Only crown::api::Error is caught; exact code mismatch fails; other exceptions propagate. |
| ownership | Action and code view are borrowed for one call; no callback is retained. |
| failure | Throws runtime_error if no exact crown::api::Error is seen or the code differs; other exceptions propagate. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0016

[Lines 74–74](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an int64 witness Value. |
| inputs / outputs | Inputs and return are those in \`Value n(std::int64_t value)\`; body-specific behavior: Build an int64 witness Value. |
| invariants | Integer payload is owned by Value. |
| ownership | Scalar Value owns no external storage. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0017

[Lines 75–75](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a string witness Value by moving a string into the scalar. |
| inputs / outputs | Inputs and return are those in \`Value s(std::string value)\`; body-specific behavior: Build a string witness Value by moving a string into the scalar. |
| invariants | String payload is moved into Value and owned. |
| ownership | Value owns moved string bytes. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0018

[Lines 76–78](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row a_row(std::int64_t x, std::int64_t y, std::string witness) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one A table row (x,y,a_witness). |
| inputs / outputs | Inputs and return are those in \`Row a_row(std::int64_t x, std::int64_t y, std::string witness)\`; body-specific behavior: Build one A table row (x,y,a_witness). |
| invariants | Each row owns its scalar/string values. |
| ownership | Returned Row owns its scalar and string values. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0019

[Lines 79–81](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row b_row(std::int64_t x, std::int64_t y, std::string witness) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one B table row (x,y,b_witness). |
| inputs / outputs | Inputs and return are those in \`Row b_row(std::int64_t x, std::int64_t y, std::string witness)\`; body-specific behavior: Build one B table row (x,y,b_witness). |
| invariants | Each row owns its scalar/string values. |
| ownership | Returned Row owns its scalar and string values. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0020

[Lines 82–84](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row c_row(std::int64_t x, std::int64_t z, std::string witness) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one C table row (x,z,a_witness). |
| inputs / outputs | Inputs and return are those in \`Row c_row(std::int64_t x, std::int64_t z, std::string witness)\`; body-specific behavior: Build one C table row (x,z,a_witness). |
| invariants | Each row owns its scalar/string values. |
| ownership | Returned Row owns its scalar and string values. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0021

[Lines 85–91](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L85-L91:sha256:75c210e48e03f5f6b648a0a86f94a88a11c6a39674e70de9b266fd58dc224713
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare fragment_cursor_exception_test.cpp: declare constant fixture data. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. These constexpr data are fixed fixture constants; quota literals are grants, not reserved bytes or measured peaks. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 92–111](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the A-B-C physical tree/query where C is below A but outside root-connected C* for head {x,y}. |
| inputs / outputs | Inputs and return are those in \`PhysicalPlan make_plan()\`; body-specific behavior: Lower the A-B-C physical tree/query where C is below A but outside root-connected C* for head {x,y}. |
| invariants | PhysicalPlan owns copied lowered metadata; join variables and tree node identifiers are the fixed fixture contract. |
| ownership | Returned PhysicalPlan owns lowered metadata. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Builds one fixed 3-table plan/tree and lowers it once. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0024

[Lines 113–118](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& a_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the static A rows including duplicate projected pairs, an orphan, and another key. |
| inputs / outputs | Inputs and return are those in \`const std::vector&lt;Row&gt;& a_rows()\`; body-specific behavior: Return the static A rows including duplicate projected pairs, an orphan, and another key. |
| invariants | Reference to function-local static vector is borrowed but remains valid for program lifetime; caller must not mutate. |
| ownership | Returns a borrowed reference to immutable function-static rows; storage lasts to program exit. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Initializes fixed static rows once; later returns a const reference. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0025

[Lines 119–124](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& b_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the static B rows including duplicate projected pairs. |
| inputs / outputs | Inputs and return are those in \`const std::vector&lt;Row&gt;& b_rows()\`; body-specific behavior: Return the static B rows including duplicate projected pairs. |
| invariants | Reference to function-local static vector is borrowed but remains valid for program lifetime; caller must not mutate. |
| ownership | Returns a borrowed reference to immutable function-static rows; storage lasts to program exit. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Initializes fixed static rows once; later returns a const reference. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0026

[Lines 125–130](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& c_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the static C rows that witness selected A values and include finite unrelated values. |
| inputs / outputs | Inputs and return are those in \`const std::vector&lt;Row&gt;& c_rows()\`; body-specific behavior: Return the static C rows that witness selected A values and include finite unrelated values. |
| invariants | Reference to function-local static vector is borrowed but remains valid for program lifetime; caller must not mutate. |
| ownership | Returns a borrowed reference to immutable function-static rows; storage lasts to program exit. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Initializes fixed static rows once; later returns a const reference. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0028

[Lines 132–144](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime make_support(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create SupportRuntime and seed A/B/C through support-node updates. |
| inputs / outputs | Inputs and return are those in \`SupportRuntime make_support(const PhysicalPlan& plan)\`; body-specific behavior: Create SupportRuntime and seed A/B/C through support-node updates. |
| invariants | Returned runtime owns its plan-backed runtime state; fixture seed updates are finite and sequence ordered. |
| ownership | Returned SupportRuntime owns runtime state initialized from borrowed plan. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Applies the fixed A/B/C seed rows to a small support runtime. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0030

[Lines 146–158](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime make_physical(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create PhysicalRuntime and seed A/B/C through table updates. |
| inputs / outputs | Inputs and return are those in \`PhysicalRuntime make_physical(const PhysicalPlan& plan)\`; body-specific behavior: Create PhysicalRuntime and seed A/B/C through table updates. |
| invariants | Returned runtime owns its plan-backed runtime state; physical table seeds are finite and sequence ordered. |
| ownership | Returned PhysicalRuntime owns runtime state initialized from borrowed plan. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Applies the fixed A/B/C seed rows to a small physical runtime. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0032

[Lines 160–160](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sort_rows(std::vector<Row>& rows) { std::sort(rows.begin(), rows.end()); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sort materialized rows for deterministic expected comparison. |
| inputs / outputs | Inputs and return are those in \`void sort_rows(std::vector&lt;Row&gt;& rows)\`; body-specific behavior: Sort materialized rows for deterministic expected comparison. |
| invariants | Determinism only orders expected result values. |
| ownership | Inputs are borrowed or values for the call as declared; the helper retains no result after return, except explicitly mutated output-reference arguments. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0034

[Lines 162–169](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> drain(Cursor& cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a cursor, export tuple values to owning Rows, then verify exhausted/inactive state. |
| inputs / outputs | Inputs and return are those in \`std::vector&lt;Row&gt; drain(Cursor& cursor)\`; body-specific behavior: Drain a cursor, export tuple values to owning Rows, then verify exhausted/inactive state. |
| invariants | Exported Rows copy tuple scalar values and outlive the cursor; exhaustion transitions state to exhausted and inactive. |
| ownership | Cursor owns traversal/read lease while live; returned Rows own exported values after cursor closure. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Consumes all finite cursor rows and sorts the copied result. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0036

[Lines 171–185](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> expected_all_witnesses(bool omit_b10 = false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate full witness assignments with nested A-C-B loops and optional removal of b10. |
| inputs / outputs | Inputs and return are those in \`std::vector&lt;Row&gt; expected_all_witnesses(bool omit_b10 = false)\`; body-specific behavior: Enumerate full witness assignments with nested A-C-B loops and optional removal of b10. |
| invariants | Nested loops are an independent finite test oracle, not implementation traversal. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | Returns false on mismatch; allocation or value-comparison exceptions propagate. |
| cost | Compares only the finite fields/vectors named by the helper; not an execution-time bound. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0038

[Lines 187–198](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> expected_a_b() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build expected A-subtree rows requiring both B join and hidden C child witness. |
| inputs / outputs | Inputs and return are those in \`std::vector&lt;Row&gt; expected_a_b()\`; body-specific behavior: Build expected A-subtree rows requiring both B join and hidden C child witness. |
| invariants | Expected A-B answer requires a C witness; A and B join on x,y and output hidden witnesses. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0040

[Lines 200–206](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> expected_b_c() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build expected disconnected B-C factor rows by their shared x. |
| inputs / outputs | Inputs and return are those in \`std::vector&lt;Row&gt; expected_b_c()\`; body-specific behavior: Build expected disconnected B-C factor rows by their shared x. |
| invariants | B-C factors are selected by shared x; this is not a full query output oracle. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0042

[Lines 208–214](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<Row> expected_a_c() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build expected A-C child rows by x and a_witness. |
| inputs / outputs | Inputs and return are those in \`std::vector&lt;Row&gt; expected_a_c()\`; body-specific behavior: Build expected A-C child rows by x and a_witness. |
| invariants | A-C requires x and shared witness equality. |
| ownership | Reference parameters are borrowed for the call; returned values own their result storage, and no borrowed fixture is retained unless the signature explicitly returns a reference. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Constructs or compares bounded test values; cost is not a production complexity claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0044

[Lines 216–222](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_schema(const storage::TupleLayout& layout, std::initializer_list<VariableId> variables,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exported tuple layout field count and variable order. |
| inputs / outputs | Inputs and return are those in \`void check_schema(const storage::TupleLayout& layout, std::initializer_list&lt;VariableId&gt; variables, std::string_view message)\`; body-specific behavior: Check exported tuple layout field count and variable order. |
| invariants | Layout is checked for exposed field order, not every schema metadata property. |
| ownership | Inputs are borrowed or values for the call as declared; the helper retains no result after return, except explicitly mutated output-reference arguments. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Finite fixture work described by purpose; no wall-clock or global-resource claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0046

[Lines 224–329](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_fragment_semantics(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whole, root, subtree, arbitrary node and selected-factor fragment semantics against independent nested-loop expected rows. |
| inputs / outputs | Inputs and return are those in \`void check_fragment_semantics(const PhysicalPlan& plan)\`; body-specific behavior: Check whole, root, subtree, arbitrary node and selected-factor fragment semantics against independent nested-loop expected rows. |
| invariants | Expected rows are explicit finite relational loops; view and cursor factories are exercised as APIs, not whole-runtime memory scans. |
| ownership | Plan is borrowed; runtime/view/cursor and copied expected Rows are local. |
| failure | The named \`check\` assertion reports mismatches as std::runtime_error; planner/runtime errors and allocation failures otherwise propagate unless this body explicitly catches them. |
| cost | Exercises a finite set of whole/root/subtree/node/factor fragments against explicit nested-loop expectations. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0048

[Lines 331–364](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class MakeRuntime>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep factory ordinary-new failure points for current-view witness cursor creation and retry via a fresh cursor. |
| inputs / outputs | Inputs and return are those in \`template &lt;class MakeRuntime&gt; void check_current_witness_factory_sweep(const PhysicalPlan& plan, std::string_view name, MakeRuntime make_runtime)\`; body-specific behavior: Sweep factory ordinary-new failure points for current-view witness cursor creation and retry via a fresh cursor. |
| invariants | Every failure point is armed around factory creation only; failed factory leaves view valid; retry creates a new cursor on the same view. |
| ownership | Plan borrowed; runtime/view/cursor are local. Each cursor is independent; retries use a new cursor on the same view. |
| failure | Injected bad_alloc during factory creation is caught by the sweep; failed attempt gets a fresh factory call. Unexpected errors/assertions fail the test. |
| cost | Fail-after loop bounded by observed successful factory requests plus success; retries the fixture with a fresh cursor. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0050

[Lines 366–405](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L366); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_pending_witness_factory_sweep(const PhysicalPlan& plan, SnapshotSide side) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep before/after pending-view witness factory failures while preserving the pending transition and side-specific results. |
| inputs / outputs | Inputs and return are those in \`void check_pending_witness_factory_sweep(const PhysicalPlan& plan, SnapshotSide side)\`; body-specific behavior: Sweep before/after pending-view witness factory failures while preserving the pending transition and side-specific results. |
| invariants | Pending object owns its private transition; the pending view/cursor retains a read lease until its documented invalidation/release boundary. |
| ownership | Plan borrowed; each pending epoch and view/cursor is local; saved before/after Rows own their scalar values. |
| failure | Injected factory bad_alloc is checked at each point; transition remains under same pending owner and is explicitly retried using a new view/cursor handle. |
| cost | Fail-after sweeps run for before and after sides over finite fixture rows. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0052

[Lines 407–440](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L407); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_hidden_completion_factory_sweep(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep hidden projected-completion creation failures and retry through a new handle. |
| inputs / outputs | Inputs and return are those in \`void check_hidden_completion_factory_sweep(const PhysicalPlan& plan)\`; body-specific behavior: Sweep hidden projected-completion creation failures and retry through a new handle. |
| invariants | Factory failures do not retry the same partial cursor; new cursor gets an independent traversal. |
| ownership | Plan borrowed; each view/completion handle is local and retry creates a fresh handle. |
| failure | Factory failure is caught; each retry uses a new completion handle. No direct malloc fault is injected. |
| cost | Fail-after loop bounded by hidden-completion factory request count observed in clean attempt. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0054

[Lines 442–500](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_witness_next_fault_sweep(const PhysicalPlan& plan, SnapshotSide side, bool later) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ResultCursor::next failures after optional prefix; failed cursor closes while peer handles/view stay usable and retry uses a new cursor. |
| inputs / outputs | Inputs and return are those in \`void check_witness_next_fault_sweep(const PhysicalPlan& plan, SnapshotSide side, bool later)\`; body-specific behavior: Sweep ResultCursor::next failures after optional prefix; failed cursor closes while peer handles/view stay usable and retry uses a new cursor. |
| invariants | next() failure closes that cursor; it is not resumable. Previously returned tuples are owned; retry is a fresh cursor on the same still-valid view. |
| ownership | Plan borrowed; cursor is local; exported prefix tuples own copied values. A next-failure retry is a new cursor, not resumption of the failed cursor. |
| failure | Injected \`next()\` bad_alloc is expected to close/fail that cursor; calling it again returns invalid_cursor. Recovery opens a new cursor on same view; not same-cursor retry. |
| cost | Fail-after sweep per selected side/prefix; fixture rows and peer cursors are finite. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0056

[Lines 502–535](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L502); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_pending_commit_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard pending commit while before-side cursors/tuples are live; require the commit path to avoid the replaced ordinary-new forms. |
| inputs / outputs | Inputs and return are those in \`void check_pending_commit_noalloc(const PhysicalPlan& plan)\`; body-specific behavior: Guard pending commit while before-side cursors/tuples are live; require the commit path to avoid the replaced ordinary-new forms. |
| invariants | Commit guard proves only no request reached directly defined ordinary replacements during commit; active before-view cursor/tuple value semantics are checked separately. |
| ownership | Pending epoch owns its transition; cursor/view lease and already exported tuples are local owning handles/values. |
| failure | Guarded commit must avoid requests reaching the ordinary replacement; commit/API/assertion errors fail. Does not establish no malloc, account or system allocation. |
| cost | One guarded commit and finite cursor/value checks. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0058

[Lines 537–560](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L537); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_pending_rollback_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard pending rollback; invalidate view/cursors before undo while copied tuples remain owned. |
| inputs / outputs | Inputs and return are those in \`void check_pending_rollback_noalloc(const PhysicalPlan& plan)\`; body-specific behavior: Guard pending rollback; invalidate view/cursors before undo while copied tuples remain owned. |
| invariants | Rollback invalidates view/cursor before undo; already exported tuple values remain owned. This does not prove allocator-system or account-denial behavior. |
| ownership | Pending epoch/view/cursor are local; exported tuple values own their rows after rollback invalidates cursors. |
| failure | Guarded rollback must invalidate leased handles and preserve copied tuples; replacement-new request throws. Other allocator channels are outside seam. |
| cost | One guarded rollback and finite cursor/value checks. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0060

[Lines 562–622](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L562); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_pending_move_and_destruction_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard move replacement and destruction of pending epochs, checking destination/source cursor invalidation and runtime busy state. |
| inputs / outputs | Inputs and return are those in \`void check_pending_move_and_destruction_noalloc(const PhysicalPlan& plan)\`; body-specific behavior: Guard move replacement and destruction of pending epochs, checking destination/source cursor invalidation and runtime busy state. |
| invariants | Moved/destroyed pending owner invalidates its leased views/cursors; the source runtime remains busy until rollback/cleanup as asserted. |
| ownership | Source and destination pending owners, cursors and views are local; runtime lifetime remains controlled by owning runtime. |
| failure | Guarded move/destruction checks only directly replaced ordinary new forms; lifecycle/API mismatches throw via check. |
| cost | Finite move-assignment/destruction cases with a few live cursors/views. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0062

[Lines 624–646](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L624); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_phase_limits(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise cursor/view startup work limits and retry through a fresh cursor after the limited path. |
| inputs / outputs | Inputs and return are those in \`void check_phase_limits(const PhysicalPlan& plan)\`; body-specific behavior: Exercise cursor/view startup work limits and retry through a fresh cursor after the limited path. |
| invariants | Limits bound the selected runtime work dimension; no elapsed-time or global CPU claim. |
| ownership | Each runtime, view and cursor is local; a fresh cursor retries the same still-valid view after a limited/failure path. |
| failure | Checks named work limit errors and public state; this is not elapsed CPU or total resource measurement. |
| cost | Finite work-limit values and cursor starts; no timing claim. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |

## B0063

[Lines 647–649](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L647); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L647-L649:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in fragment_cursor_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [docs/result_cursors.md](../../../../result_cursors.md), [docs/code_review.md](../../../../code_review.md) |

## B0064

[Lines 650–673](../../../../../tests/unit/fragment_cursor_exception_test.cpp#L650); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run fragment-cursor witness, lease, fault, pending-epoch and limit fixtures; report caught errors. |
| inputs / outputs | Inputs and return are those in \`int main()\`; body-specific behavior: Run fragment-cursor witness, lease, fault, pending-epoch and limit fixtures; report caught errors. |
| invariants | The driver catches std::exception and returns 1 on fixture failure; no native run is asserted here. |
| ownership | All fixture and runtime objects are local to main. |
| failure | Catches std::exception, prints error and returns 1; no test run is claimed. |
| cost | Runs finite fragment cursor cases; no native execution is claimed. |
| Design | [tests/unit/fragment_cursor_exception_test.cpp](../../../../../tests/unit/fragment_cursor_exception_test.cpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/result_cursors.md § Cursor states and close behavior](../../../../result_cursors.md), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md) |
