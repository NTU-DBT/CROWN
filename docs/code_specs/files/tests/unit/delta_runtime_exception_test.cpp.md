# `tests/unit/delta_runtime_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_runtime_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `120126329f78a808fba1cdefca2ab4b91754992e0fac5ad3b7a7d5f6808efd37`. 763 lines partitioned into 86 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../tests/unit/delta_runtime_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Keep failures armed while DeltaRuntime unwinds its private live image and · [reviewed contract](#b0001) |
| [B0002 · 31–38](../../../../../tests/unit/delta_runtime_exception_test.cpp#L31) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 39–45](../../../../../tests/unit/delta_runtime_exception_test.cpp#L39) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 46–47](../../../../../tests/unit/delta_runtime_exception_test.cpp#L46) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 48–48](../../../../../tests/unit/delta_runtime_exception_test.cpp#L48) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 49–49](../../../../../tests/unit/delta_runtime_exception_test.cpp#L49) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 50–50](../../../../../tests/unit/delta_runtime_exception_test.cpp#L50) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 51–51](../../../../../tests/unit/delta_runtime_exception_test.cpp#L51) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 52–52](../../../../../tests/unit/delta_runtime_exception_test.cpp#L52) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 53–53](../../../../../tests/unit/delta_runtime_exception_test.cpp#L53) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 54–64](../../../../../tests/unit/delta_runtime_exception_test.cpp#L54) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;DeltaRuntime&gt;); · [reviewed contract](#b0011) |
| [B0012 · 65–67](../../../../../tests/unit/delta_runtime_exception_test.cpp#L65) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0012) |
| [B0013 · 68–68](../../../../../tests/unit/delta_runtime_exception_test.cpp#L68) | Explanatory comments or spacing. |  |
| [B0014 · 69–79](../../../../../tests/unit/delta_runtime_exception_test.cpp#L69) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, "unexpected error code: expected " + std::string(code) + · [reviewed contract](#b0014) |
| [B0015 · 80–80](../../../../../tests/unit/delta_runtime_exception_test.cpp#L80) | Explanatory comments or spacing. |  |
| [B0016 · 81–81](../../../../../tests/unit/delta_runtime_exception_test.cpp#L81) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0016) |
| [B0017 · 82–82](../../../../../tests/unit/delta_runtime_exception_test.cpp#L82) | Callable definition: Row edge(std::int64_t left, std::int64_t right) | calls n; returns {n(left), n(right)} · [reviewed contract](#b0017) |
| [B0018 · 83–83](../../../../../tests/unit/delta_runtime_exception_test.cpp#L83) | Explanatory comments or spacing. |  |
| [B0019 · 84–95](../../../../../tests/unit/delta_runtime_exception_test.cpp#L84) | Callable definition: PhysicalPlan make_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0019) |
| [B0020 · 96–96](../../../../../tests/unit/delta_runtime_exception_test.cpp#L96) | Explanatory comments or spacing. |  |
| [B0021 · 97–110](../../../../../tests/unit/delta_runtime_exception_test.cpp#L97) | Callable definition: PhysicalPlan make_shared_separator_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0021) |
| [B0022 · 111–111](../../../../../tests/unit/delta_runtime_exception_test.cpp#L111) | Explanatory comments or spacing. |  |
| [B0023 · 112–127](../../../../../tests/unit/delta_runtime_exception_test.cpp#L112) | Callable definition: PhysicalPlan make_normalized_plan() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0023) |
| [B0024 · 128–128](../../../../../tests/unit/delta_runtime_exception_test.cpp#L128) | Explanatory comments or spacing. |  |
| [B0025 · 129–143](../../../../../tests/unit/delta_runtime_exception_test.cpp#L129) | Callable definition: PhysicalPlan make_exists_plan() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; guard check(program.binding.wrapper == frontend::SqlWrapper::exists && program.core.atoms.size() == 1,; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0025) |
| [B0026 · 144–144](../../../../../tests/unit/delta_runtime_exception_test.cpp#L144) | Explanatory comments or spacing. |  |
| [B0027 · 145–151](../../../../../tests/unit/delta_runtime_exception_test.cpp#L145) | Callable definition: DeltaOptions options(DeltaMode mode = DeltaMode::delta) | calls ; returns result · [reviewed contract](#b0027) |
| [B0028 · 152–152](../../../../../tests/unit/delta_runtime_exception_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0029 · 153–157](../../../../../tests/unit/delta_runtime_exception_test.cpp#L153) | Callable definition: void apply_and_discard(DeltaRuntime& runtime, SetOperation operation, const Row& values) | calls apply, sequence, discard, check; guard check(runtime.ready(), "discarding a fixture epoch did not release its output lease"); · [reviewed contract](#b0029) |
| [B0030 · 158–158](../../../../../tests/unit/delta_runtime_exception_test.cpp#L158) | Explanatory comments or spacing. |  |
| [B0031 · 159–164](../../../../../tests/unit/delta_runtime_exception_test.cpp#L159) | Callable definition: void apply_and_discard_at(DeltaRuntime& runtime, TableId table, SetOperation operation, const Row& values) | calls apply, sequence, discard, check; guard check(runtime.ready(), "discarding a fixture epoch did not release its output lease"); · [reviewed contract](#b0031) |
| [B0032 · 165–165](../../../../../tests/unit/delta_runtime_exception_test.cpp#L165) | Explanatory comments or spacing. |  |
| [B0033 · 166–170](../../../../../tests/unit/delta_runtime_exception_test.cpp#L166) | Callable definition: void seed_base(DeltaRuntime& runtime, bool include_loop = false) | calls apply_and_discard, edge; growth insert · [reviewed contract](#b0033) |
| [B0034 · 171–171](../../../../../tests/unit/delta_runtime_exception_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0035 · 172–176](../../../../../tests/unit/delta_runtime_exception_test.cpp#L172) | Callable definition: const std::vector&lt;Row&gt;& loop_delta_rows() | calls n; returns rows · [reviewed contract](#b0035) |
| [B0036 · 177–177](../../../../../tests/unit/delta_runtime_exception_test.cpp#L177) | Explanatory comments or spacing. |  |
| [B0037 · 178–198](../../../../../tests/unit/delta_runtime_exception_test.cpp#L178) | Callable definition: void check_output(DeltaRuntime::Epoch& epoch, DeltaRuntime& runtime, SetOperation operation, const std::vector&lt;Row&gt;& expected) | calls check, sequence, active, empty; guard check(epoch.sequence() == runtime.sequence(), "delta artifact sequence differs from its committed i…; growth push_back; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 199–199](../../../../../tests/unit/delta_runtime_exception_test.cpp#L199) | Explanatory comments or spacing. |  |
| [B0039 · 200–204](../../../../../tests/unit/delta_runtime_exception_test.cpp#L200) | Type/record definition: struct DerivationImage |  · [reviewed contract](#b0039) |
| [B0040 · 205–211](../../../../../tests/unit/delta_runtime_exception_test.cpp#L205) | Type/record definition: struct SnapshotImage |  · [reviewed contract](#b0040) |
| [B0041 · 212–212](../../../../../tests/unit/delta_runtime_exception_test.cpp#L212) | Explanatory comments or spacing. |  |
| [B0042 · 213–225](../../../../../tests/unit/delta_runtime_exception_test.cpp#L213) | Callable definition: SnapshotImage snapshot_image(const DeltaRuntime& runtime) | calls snapshot, io::write_support_snapshot, plan, resize; returns result; growth push_back, resize; 2 loop sites · [reviewed contract](#b0042) |
| [B0043 · 226–226](../../../../../tests/unit/delta_runtime_exception_test.cpp#L226) | Explanatory comments or spacing. |  |
| [B0044 · 227–231](../../../../../tests/unit/delta_runtime_exception_test.cpp#L227) | Callable definition: bool same_live(const std::optional&lt;LiveSnapshot&gt;& left, const std::optional&lt;LiveSnapshot&gt;& right) | calls has_value; returns false; !left \|\| (left-&gt;sequence == right-&gt;sequence && left-&gt;factors == right-&gt;factors) · [reviewed contract](#b0044) |
| [B0045 · 232–232](../../../../../tests/unit/delta_runtime_exception_test.cpp#L232) | Explanatory comments or spacing. |  |
| [B0046 · 233–249](../../../../../tests/unit/delta_runtime_exception_test.cpp#L233) | Callable definition: void check_stats(const PhysicalStorageStatistics& before, const PhysicalStorageStatistics& after, std::string_view context) | calls check, std::string, check_arena; guard check(old_stats.live_records == new_stats.live_records && · [reviewed contract](#b0046) |
| [B0047 · 250–250](../../../../../tests/unit/delta_runtime_exception_test.cpp#L250) | Explanatory comments or spacing. |  |
| [B0048 · 251–265](../../../../../tests/unit/delta_runtime_exception_test.cpp#L251) | Callable definition: void check_unchanged(DeltaRuntime& runtime, const SnapshotImage& before, const std::optional&lt;LiveSnapshot&gt;& live_before, const Ph… | calls check, ready, sequence, has_answer; guard check(runtime.ready() && runtime.sequence() == sequence && runtime.has_answer() == answer && · [reviewed contract](#b0048) |
| [B0049 · 266–266](../../../../../tests/unit/delta_runtime_exception_test.cpp#L266) | Explanatory comments or spacing. |  |
| [B0050 · 267–267](../../../../../tests/unit/delta_runtime_exception_test.cpp#L267) | Type/record definition: enum class LoopChange | growth insert · [reviewed contract](#b0050) |
| [B0051 · 268–268](../../../../../tests/unit/delta_runtime_exception_test.cpp#L268) | Explanatory comments or spacing. |  |
| [B0052 · 269–271](../../../../../tests/unit/delta_runtime_exception_test.cpp#L269) | Callable definition: SetOperation sign(LoopChange change) | calls ; returns change == LoopChange::insert ? SetOperation::insert : SetOperation::erase; growth insert · [reviewed contract](#b0052) |
| [B0053 · 272–272](../../../../../tests/unit/delta_runtime_exception_test.cpp#L272) | Explanatory comments or spacing. |  |
| [B0054 · 273–275](../../../../../tests/unit/delta_runtime_exception_test.cpp#L273) | Callable definition: void prepare_change(DeltaRuntime& runtime, LoopChange change) | calls seed_base · [reviewed contract](#b0054) |
| [B0055 · 276–276](../../../../../tests/unit/delta_runtime_exception_test.cpp#L276) | Explanatory comments or spacing. |  |
| [B0056 · 277–320](../../../../../tests/unit/delta_runtime_exception_test.cpp#L277) | Callable definition: std::size_t sweep_change_failures(LoopChange change) | calls sign, make_plan, options, prepare_change; guard check(failures &gt; 0, "self-join ordinary-new failure sweep did not inject bad_alloc");; returns failures; growth emplace, insert; 1 loop sites; source comment (unverified): // Keep all private rollback cleanup under persistent failure. · [reviewed contract](#b0056) |
| [B0057 · 321–321](../../../../../tests/unit/delta_runtime_exception_test.cpp#L321) | Explanatory comments or spacing. |  |
| [B0058 · 322–332](../../../../../tests/unit/delta_runtime_exception_test.cpp#L322) | Callable definition: void seed_shared_separator(DeltaRuntime& runtime) | calls apply_and_discard_at, n, live_snapshot, check; guard check(live && live-&gt;factors.size() == 2 &&; growth insert · [reviewed contract](#b0058) |
| [B0059 · 333–333](../../../../../tests/unit/delta_runtime_exception_test.cpp#L333) | Explanatory comments or spacing. |  |
| [B0060 · 334–381](../../../../../tests/unit/delta_runtime_exception_test.cpp#L334) | Callable definition: void sweep_shared_separator_delete_failures() | calls n, make_shared_separator_plan, options, seed_shared_separator; guard check(failures &gt; 0,; growth emplace; 1 loop sites; source comment (unverified): // Keep rollback cleanup under persistent failure. · [reviewed contract](#b0060) |
| [B0061 · 382–382](../../../../../tests/unit/delta_runtime_exception_test.cpp#L382) | Explanatory comments or spacing. |  |
| [B0062 · 383–433](../../../../../tests/unit/delta_runtime_exception_test.cpp#L383) | Callable definition: void check_mode_bootstrap_failure_sweep() | calls make_plan, options, seed_base, snapshot_image; guard check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot(),; growth insert; 1 loop sites · [reviewed contract](#b0062) |
| [B0063 · 434–434](../../../../../tests/unit/delta_runtime_exception_test.cpp#L434) | Explanatory comments or spacing. |  |
| [B0064 · 435–454](../../../../../tests/unit/delta_runtime_exception_test.cpp#L435) | Callable definition: void check_spool_limit_atomicity(std::size_t row_limit, std::size_t byte_limit, std::string_view label) | calls options, make_plan, seed_base, set_mode; growth insert; source comment (unverified): // No spool is used while maintenance mode is active. · [reviewed contract](#b0064) |
| [B0065 · 455–455](../../../../../tests/unit/delta_runtime_exception_test.cpp#L455) | Explanatory comments or spacing. |  |
| [B0066 · 456–462](../../../../../tests/unit/delta_runtime_exception_test.cpp#L456) | Callable definition: void check_exists_sql_row(const DeltaRuntime& runtime, bool expected) | calls results, next, check, values; guard check(row && row-&gt;values().size() == 1 && std::get&lt;bool&gt;(row-&gt;values()\[0\]) == expected, · [reviewed contract](#b0066) |
| [B0067 · 463–463](../../../../../tests/unit/delta_runtime_exception_test.cpp#L463) | Explanatory comments or spacing. |  |
| [B0068 · 464–477](../../../../../tests/unit/delta_runtime_exception_test.cpp#L464) | Callable definition: void check_exists_flip_output(DeltaRuntime::Epoch& output, DeltaRuntime& runtime) | calls check, remaining, active, next; guard check(output.remaining() == 2 && output.active(),; growth insert · [reviewed contract](#b0068) |
| [B0069 · 478–478](../../../../../tests/unit/delta_runtime_exception_test.cpp#L478) | Explanatory comments or spacing. |  |
| [B0070 · 479–505](../../../../../tests/unit/delta_runtime_exception_test.cpp#L479) | Callable definition: void check_exists_mapping_spool_failure_is_atomic() | calls options, make_exists_plan, snapshot_image, live_snapshot; guard check(!answer && runtime.mode() == DeltaMode::delta,; growth emplace, insert; source comment (unverified): // The same input with room for both replacement records proves the rejected · [reviewed contract](#b0070) |
| [B0071 · 506–506](../../../../../tests/unit/delta_runtime_exception_test.cpp#L506) | Explanatory comments or spacing. |  |
| [B0072 · 507–533](../../../../../tests/unit/delta_runtime_exception_test.cpp#L507) | Callable definition: void check_zero_spool_limits_allow_empty_output() | calls options, make_plan, seed_base, set_mode; guard check(live_before.has_value(), "zero-spool no-op fixture has no committed live image");; growth insert · [reviewed contract](#b0072) |
| [B0073 · 534–534](../../../../../tests/unit/delta_runtime_exception_test.cpp#L534) | Explanatory comments or spacing. |  |
| [B0074 · 535–549](../../../../../tests/unit/delta_runtime_exception_test.cpp#L535) | Callable definition: void check_bootstrap_cursor_limit_preserves_maintenance() | calls options, make_plan, seed_base, snapshot_image; guard check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot(), · [reviewed contract](#b0074) |
| [B0075 · 550–550](../../../../../tests/unit/delta_runtime_exception_test.cpp#L550) | Explanatory comments or spacing. |  |
| [B0076 · 551–567](../../../../../tests/unit/delta_runtime_exception_test.cpp#L551) | Callable definition: void check_active_output_blocks_input_and_mode_switch() | calls make_plan, options, seed_base, apply; guard check(output.active() && output.remaining() == 3 && !runtime.ready(),; growth insert · [reviewed contract](#b0076) |
| [B0077 · 568–568](../../../../../tests/unit/delta_runtime_exception_test.cpp#L568) | Explanatory comments or spacing. |  |
| [B0078 · 569–610](../../../../../tests/unit/delta_runtime_exception_test.cpp#L569) | Callable definition: void check_delivery_and_discard_are_allocation_free() | calls make_plan, options, seed_base, apply; guard check(values_ok && count == 3 && !output.active() && output.remaining() == 0 && runtime.ready(),; growth insert; 1 loop sites · [reviewed contract](#b0078) |
| [B0079 · 611–611](../../../../../tests/unit/delta_runtime_exception_test.cpp#L611) | Explanatory comments or spacing. |  |
| [B0080 · 612–660](../../../../../tests/unit/delta_runtime_exception_test.cpp#L612) | Callable definition: void check_facade_move_and_destruction_with_active_output() | calls make_plan, options, seed_base, apply; guard check(!moved.ready() && output.active(), "moving the facade detached its committed output lease");; growth emplace, insert; 1 loop sites · [reviewed contract](#b0080) |
| [B0081 · 661–661](../../../../../tests/unit/delta_runtime_exception_test.cpp#L661) | Explanatory comments or spacing. |  |
| [B0082 · 662–701](../../../../../tests/unit/delta_runtime_exception_test.cpp#L662) | Callable definition: void check_final_epoch_and_plan_destruction_are_allocation_free() | calls make_plan, options, seed_base, emplace; guard check(output-&gt;active(), "final-epoch destruction fixture has no committed delta output");; growth emplace, insert · [reviewed contract](#b0082) |
| [B0083 · 702–702](../../../../../tests/unit/delta_runtime_exception_test.cpp#L702) | Explanatory comments or spacing. |  |
| [B0084 · 703–730](../../../../../tests/unit/delta_runtime_exception_test.cpp#L703) | Callable definition: void check_finite_work_limit_preserves_input() | calls options, make_plan, seed_base, set_mode; guard check(clean_work &gt; bootstrap_work,; growth insert · [reviewed contract](#b0084) |
| [B0085 · 731–733](../../../../../tests/unit/delta_runtime_exception_test.cpp#L731) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0085) |
| [B0086 · 734–763](../../../../../tests/unit/delta_runtime_exception_test.cpp#L734) | Callable definition: int main(int argc,char** argv) | calls std::string_view, check, sweep_change_failures, sweep_shared_separator_delete_failures; guard else check(argc==1,"expected no argument, eager or incremental live policy");; returns 1; growth insert · [reviewed contract](#b0086) |

## B0001

[Lines 1–30](../../../../../tests/unit/delta_runtime_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L30:sha256:314be9e3944d9772d6d4c713117341634a92d15db95cfa1e63c8d9bbe1408640
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_runtime_exception_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/document.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 31–38](../../../../../tests/unit/delta_runtime_exception_test.cpp#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a thread-local fail-after point to the direct ordinary-new replacement and back admitted storage with malloc. |
| inputs / outputs | Takes byte count; throws before malloc when fail_after==0, decrements positive threshold, returns malloc(bytes or 1), or throws bad_alloc. |
| invariants | No per-request allocation counter exists; fault index counts ordinary-new calls reaching this symbol. |
| ownership | Returns raw storage freed by matching scalar/array sized or unsized deletes. |
| failure | Direct malloc/realloc/syscalls and separate MemoryAccount denial are not injected; no dedicated aligned/nothrow form is defined, and indirect delegation is not asserted. |
| cost | One threshold branch plus possible malloc; not bytes/RSS/CPU accounting. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0003

[Lines 39–45](../../../../../tests/unit/delta_runtime_exception_test.cpp#L39); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope one DeltaRuntime fail-after setting. |
| inputs / outputs | Optional step initializes thread-local threshold; forbid_allocations sets zero; destructor resets -1. |
| invariants | A positive threshold allows that many direct ordinary-new requests before rejection; no nesting stack. |
| ownership | Mutates only thread-local scalar state. |
| failure | No custom error handling; replacement request throws bad_alloc. |
| cost | Constant scalar writes; no allocator-wide observation. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0004

[Lines 46–47](../../../../../tests/unit/delta_runtime_exception_test.cpp#L46); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L47:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_runtime_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 48–48](../../../../../tests/unit/delta_runtime_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar throwing global new through malloc_new. |
| inputs / outputs | Accepts size and returns storage or propagates bad_alloc. |
| invariants | Directly defines ordinary scalar overload only. |
| ownership | Returned storage is paired with scalar delete in this executable. |
| failure | No dedicated aligned/nothrow replacement; delegation is not asserted; direct malloc/system failures are not injected. |
| cost | One seam call and possible malloc. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0006

[Lines 49–49](../../../../../tests/unit/delta_runtime_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array throwing global new through malloc_new. |
| inputs / outputs | Accepts size and returns storage or propagates bad_alloc. |
| invariants | Directly defines ordinary array overload only. |
| ownership | Returned storage is paired with array delete. |
| failure | No dedicated aligned/nothrow replacement; direct allocator/system failures are outside. |
| cost | One seam call and possible malloc. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0007

[Lines 50–50](../../../../../tests/unit/delta_runtime_exception_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar storage through std::free. |
| inputs / outputs | Accepts pointer; returns void. |
| invariants | Noexcept. |
| ownership | Delete consumes the matching replacement allocation. |
| failure | No error reporting. |
| cost | One free. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0008

[Lines 51–51](../../../../../tests/unit/delta_runtime_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array storage through std::free. |
| inputs / outputs | Accepts pointer; returns void. |
| invariants | Noexcept. |
| ownership | Delete\[\] consumes matching array allocation. |
| failure | No error reporting. |
| cost | One free. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0009

[Lines 52–52](../../../../../tests/unit/delta_runtime_exception_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized scalar delete for the replacement allocation. |
| inputs / outputs | Accepts pointer and ignored size. |
| invariants | Calls std::free; noexcept. |
| ownership | Releases the pointer, retains no state. |
| failure | No error reporting. |
| cost | One free. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0010

[Lines 53–53](../../../../../tests/unit/delta_runtime_exception_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized array delete for the replacement allocation. |
| inputs / outputs | Accepts pointer and ignored size. |
| invariants | Calls std::free; noexcept. |
| ownership | Releases the pointer, retains no state. |
| failure | No error reporting. |
| cost | One free. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0011

[Lines 54–64](../../../../../tests/unit/delta_runtime_exception_test.cpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L64:sha256:031ec300197f3a49848be51ded6d1ed699bd2337060968307fd4c79b77ee07de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_runtime_exception_test.cpp: bind local aliases/name imports; require 4 compile-time type/ABI conditions; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 65–67](../../../../../tests/unit/delta_runtime_exception_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one DeltaRuntime test assertion. |
| inputs / outputs | Accepts predicate and owned/borrowed diagnostic string reference; throws runtime_error only when false. |
| invariants | Does not translate product Error. |
| ownership | Message reference is used during call; no fixture retained. |
| failure | False assertion throws runtime_error; formatting/allocation errors propagate. |
| cost | One predicate branch. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0014

[Lines 69–79](../../../../../tests/unit/delta_runtime_exception_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one callable to throw Error with an exact error code. |
| inputs / outputs | Forwards action and code view; returns only for matching Error. |
| invariants | Catches Error only; bad_alloc and other exceptions escape. |
| ownership | Callable/code are borrowed. |
| failure | Missing or wrong Error becomes test runtime_error. |
| cost | One call and code comparison. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0016

[Lines 81–81](../../../../../tests/unit/delta_runtime_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct int64 fixture Value. |
| inputs / outputs | Takes integer and returns Value. |
| invariants | Value preserves input scalar. |
| ownership | Owns returned scalar only. |
| failure | No custom failure. |
| cost | Constant fixture operation. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0017

[Lines 82–82](../../../../../tests/unit/delta_runtime_exception_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t left, std::int64_t right) { return {n(left), n(right)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a two-column edge Row. |
| inputs / outputs | Takes two int64 values and returns Row{x,z}. |
| invariants | Field order is the source relation order. |
| ownership | Returned vector owns values. |
| failure | Container allocation errors propagate. |
| cost | Two scalar conversions and row construction. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0019

[Lines 84–95](../../../../../tests/unit/delta_runtime_exception_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the E(x,z), E(z,y) self-join DeltaRuntime plan. |
| inputs / outputs | No args; returns PhysicalPlan with two occurrences over table E and output x,z,y. |
| invariants | Second atom joins on z; fixed tree preserves parent/child separator. |
| ownership | Returned plan owns metadata. |
| failure | Planner errors propagate. |
| cost | One small fixed lowering. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0021

[Lines 97–110](../../../../../tests/unit/delta_runtime_exception_test.cpp#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_shared_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the two-table shared-separator plan R(a,x) join S(x,y). |
| inputs / outputs | No args; returns PhysicalPlan with one parent factor and child factor at x. |
| invariants | Both parent rows may share one child key; fixture exercises delayed deletion crossing. |
| ownership | Returned plan owns metadata. |
| failure | Planner errors propagate. |
| cost | One fixed lowering. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp) |

## B0023

[Lines 112–127](../../../../../tests/unit/delta_runtime_exception_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_normalized_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind, normalize and lower a DISTINCT SQL self-join plan. |
| inputs / outputs | No args; returns normalized plan for E AS l JOIN E AS r ON l.z=r.x, outputs l.x,l.z,r.z. |
| invariants | Binding/normalization diagnostics become runtime_error; tree joins shared variable z. |
| ownership | Returned plan owns compiled normalized mapping. |
| failure | Binding/normalization/lowering errors propagate. |
| cost | One frontend bind/normalize/lower pass. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0025

[Lines 129–143](../../../../../tests/unit/delta_runtime_exception_test.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_exists_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and lower SQL EXISTS over r. |
| inputs / outputs | No args; returns normalized plan for SELECT EXISTS(SELECT NULL FROM r). |
| invariants | Checks bound wrapper is EXISTS with one core atom; result is Boolean SQL wrapper. |
| ownership | Returned plan owns normalized metadata; intermediates are local. |
| failure | Binding/normalization/plan assertion errors propagate. |
| cost | One small frontend pipeline. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp) |

## B0027

[Lines 145–151](../../../../../tests/unit/delta_runtime_exception_test.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(DeltaMode mode = DeltaMode::delta) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build DeltaOptions for selected mode and live-maintenance policy. |
| inputs / outputs | Takes DeltaMode (default delta); returns options with global test selected_policy and transition capture. |
| invariants | Other values remain documented defaults; selected_policy comes from process arg/default. |
| ownership | Plain copied options value. |
| failure | Invalid policy is rejected by DeltaRuntime construction, not here. |
| cost | Option assignments only. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0029

[Lines 153–157](../../../../../tests/unit/delta_runtime_exception_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_and_discard(DeltaRuntime& runtime, SetOperation operation, const Row& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the next update on table zero and immediately discard its output artifact. |
| inputs / outputs | Takes runtime, operation and borrowed row; sequence is runtime.sequence()+1. |
| invariants | Requires runtime.ready after discard; accepted physical update remains committed even though output rows are discarded. |
| ownership | Runtime owns state; returned Epoch is local and discard releases output owner. |
| failure | Apply errors propagate; readiness mismatch throws runtime_error. |
| cost | One full apply plus output discard. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0031

[Lines 159–164](../../../../../tests/unit/delta_runtime_exception_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_and_discard_at(DeltaRuntime& runtime, TableId table,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply and discard an update addressed to a selected physical table. |
| inputs / outputs | Takes runtime/table/op/row; returns void. |
| invariants | Uses next contiguous sequence and checks ready after discard. |
| ownership | Runtime owns state; temporary Epoch owns artifact until discard. |
| failure | Apply errors propagate. |
| cost | One physical epoch and artifact release. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0033

[Lines 166–170](../../../../../tests/unit/delta_runtime_exception_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seed_base(DeltaRuntime& runtime, bool include_loop = false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed the two-edge self-join base, optionally including a loop. |
| inputs / outputs | Takes runtime and include_loop; inserts (1,2),(2,1), optionally (1,1), each through apply_and_discard. |
| invariants | Every event commits; each output artifact is discarded and writer readiness restored. |
| ownership | Runtime owns relation/live state; local edge rows copied into updates. |
| failure | Apply/invariant errors propagate. |
| cost | Two or three physical epochs. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0035

[Lines 172–176](../../../../../tests/unit/delta_runtime_exception_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<Row>& loop_delta_rows() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return exact three loop-join rows produced by inserting or removing edge (1,1). |
| inputs / outputs | No args; returns vector of ordered triples. |
| invariants | Rows are (1,1,1),(1,1,2),(2,1,1). |
| ownership | Static vector owns its fixture values and outlives caller. |
| failure | Static initialization errors propagate. |
| cost | Three fixed rows. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0037

[Lines 178–198](../../../../../tests/unit/delta_runtime_exception_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_output(DeltaRuntime::Epoch& epoch, DeltaRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a committed Epoch and compare its output with exact expected signed rows. |
| inputs / outputs | Takes mutable Epoch, runtime, operation and expected rows. |
| invariants | Sequence equals committed runtime; active/remaining equal expected cardinality; ordinals contiguous from one; row set equals expected; last record closes output lease; spool row metric and audit journal retained; runtime invariants hold. |
| ownership | Epoch owns spool records and committed PhysicalEpoch; each next returns owning SignedResult; runtime is borrowed. |
| failure | Mismatch throws runtime_error; next/invariant errors propagate. |
| cost | Drains every fixture row, sorts output, then checks retained input pins. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0039

[Lines 200–204](../../../../../tests/unit/delta_runtime_exception_test.cpp#L200); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DerivationImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Image one derivation as row values plus derivation count. |
| inputs / outputs | Fields store Row and uint64 count. |
| invariants | Equality compares both. |
| ownership | Owns copied row values. |
| failure | No custom error path. |
| cost | Plain test value. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0040

[Lines 205–211](../../../../../tests/unit/delta_runtime_exception_test.cpp#L205); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a comparable committed DeltaRuntime snapshot. |
| inputs / outputs | Fields store sequence, physical relations, support Json and per-occurrence derivation images. |
| invariants | Image omits transient pending/output owner state. |
| ownership | Owns copies of rows, Json and count values. |
| failure | Snapshot/export allocation errors propagate. |
| cost | Copies committed snapshot content proportional to fixture state. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0042

[Lines 213–225](../../../../../tests/unit/delta_runtime_exception_test.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage snapshot_image(const DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export DeltaRuntime snapshot into an owned comparison image. |
| inputs / outputs | Takes const runtime; copies physical tables and support serialization, exports each derivation tuple/count. |
| invariants | Sequence comes from the same snapshot; no mutation. |
| ownership | Runtime borrowed; returned Image owns exported state. |
| failure | Snapshot/write/export failures propagate. |
| cost | Traverses all fixture physical/support/derivation rows. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0044

[Lines 227–231](../../../../../tests/unit/delta_runtime_exception_test.cpp#L227); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_live(const std::optional<LiveSnapshot>& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optional committed live snapshots by sequence and factor contents. |
| inputs / outputs | Takes two optional values; returns bool. |
| invariants | Both absent match; presence mismatch fails; present values compare only sequence and factors. |
| ownership | Arguments borrowed; factors are compared by value. |
| failure | No error translation. |
| cost | Linear in factor/row contents. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0046

[Lines 233–249](../../../../../tests/unit/delta_runtime_exception_test.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_stats(const PhysicalStorageStatistics& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check failed epoch did not alter committed storage high-water/accounting counters. |
| inputs / outputs | Takes before/after PhysicalStorageStatistics and context; checks source/support live, retained, pin counts, nondecreasing slots, and derivation-key count. |
| invariants | Slots may stay high or grow due attempted work; committed live/retained/pin counts and key count must be unchanged. |
| ownership | Statistics are value snapshots; no runtime retained. |
| failure | Mismatch throws context-rich runtime_error. |
| cost | Compares two arenas and one key count. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0048

[Lines 251–265](../../../../../tests/unit/delta_runtime_exception_test.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_unchanged(DeltaRuntime& runtime, const SnapshotImage& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every public committed-state oracle after an aborted DeltaRuntime attempt. |
| inputs / outputs | Takes runtime, prior SnapshotImage, optional LiveSnapshot, prior stats, sequence/answer/mode/context. |
| invariants | Requires ready, same sequence/answer/mode/snapshot/live factors/storage counts, then checks invariants. |
| ownership | Runtime is borrowed; images/stats are owning snapshots. |
| failure | Any state difference throws runtime_error; snapshot/invariant failures propagate. |
| cost | Builds and compares another full fixture image after failure. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0050

[Lines 267–267](../../../../../tests/unit/delta_runtime_exception_test.cpp#L267); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class LoopChange { insert, erase };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name whether the injected loop update inserts or erases edge (1,1). |
| inputs / outputs | Enum values insert/erase. |
| invariants | Used to choose update sign and whether base is preseeded with loop. |
| ownership | Plain local enum. |
| failure | No custom failure. |
| cost | No runtime cost. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0052

[Lines 269–271](../../../../../tests/unit/delta_runtime_exception_test.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SetOperation sign(LoopChange change) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map fixture loop change to set operation. |
| inputs / outputs | Takes LoopChange; returns insert or erase. |
| invariants | Exhaustively maps the two enum values. |
| ownership | Scalar value only. |
| failure | No custom failure. |
| cost | One conditional. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0054

[Lines 273–275](../../../../../tests/unit/delta_runtime_exception_test.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_change(DeltaRuntime& runtime, LoopChange change) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare base state appropriate to insert or erase fault sweep. |
| inputs / outputs | Takes runtime and change; seeds existing edges and includes loop only for erase case. |
| invariants | Erase test starts with row present; insert starts absent. |
| ownership | Runtime owns committed seeded state. |
| failure | Seed/update errors propagate. |
| cost | Two or three committed fixture epochs. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0056

[Lines 277–320](../../../../../tests/unit/delta_runtime_exception_test.cpp#L277); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t sweep_change_failures(LoopChange change) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fail points through self-join insert and erase apply paths. |
| inputs / outputs | Takes LoopChange; each attempt creates fresh DeltaRuntime/base, captures image/live/stats, and arms only around apply; returns failure count at first success. |
| invariants | Each bad_alloc leaves same runtime’s committed image/sequence/mode/readiness/invariants unchanged; it retries the update on that same runtime owner and checks exact three signed rows. Success artifact produces the same expected output. Max 8192. |
| ownership | Each loop iteration owns its runtime; failed apply produces no returned Epoch; successful/retry Epoch owns committed input and spool. |
| failure | Catches bad_alloc only in armed apply; post-failure retry occurs with injection disabled. Direct malloc/system/account denial are outside seam; indirect nothrow delegation is not asserted. |
| cost | Up to 8192 fresh runtime setups and seeded rows per operation, plus one same-owner retry after each failure. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § One physical input](../../../../delta_runtime.md) |

## B0058

[Lines 322–332](../../../../../tests/unit/delta_runtime_exception_test.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seed_shared_separator(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed two R(a,x) parent rows sharing x=7 and one S(x,y) child row. |
| inputs / outputs | Takes mutable runtime; applies three table-specific inserts and returns void. |
| invariants | Checks live factors equal the two parent rows and shared child key, then checks invariants. |
| ownership | Runtime owns physical/live state; fixture rows copied into updates. |
| failure | Apply/live snapshot/invariant mismatch propagates or throws runtime_error. |
| cost | Three committed fixture epochs and one live snapshot. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp) |

## B0060

[Lines 334–381](../../../../../tests/unit/delta_runtime_exception_test.cpp#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_shared_separator_delete_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep erase failures when one shared separator child key supports two parent rows. |
| inputs / outputs | No args; each point creates/seed fresh runtime, captures committed images, arms around deleting S(7,9), and returns at first success. |
| invariants | On bad_alloc same runtime remains unchanged; same-owner retry emits two exact erase rows; success emits same expected result; max8192. |
| ownership | Each attempt owns DeltaRuntime; failed attempt has no Epoch; retry artifact owns source/support journal pins until artifact destruction. |
| failure | Catches bad_alloc in apply; retry is outside scope. Seam does not inject direct malloc/syscall/account denial. |
| cost | Fresh runtime setup plus three seed epochs and up to one retry per failure. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § One physical input](../../../../delta_runtime.md) |

## B0062

[Lines 383–433](../../../../../tests/unit/delta_runtime_exception_test.cpp#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_mode_bootstrap_failure_sweep() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep delta-mode live-image bootstrap failures from a seeded maintenance runtime. |
| inputs / outputs | No args; each point creates maintenance runtime, seeds base, captures image/stats and arms around set_mode(delta). |
| invariants | On bad_alloc mode stays maintenance, no partial live image is installed and committed image/stats unchanged; same owner retries set_mode(delta), then applies loop insertion and checks complete output. First success has complete live image tagged to current sequence. Max8192. |
| ownership | Runtime owner is reused for bootstrap retry; mode change and later update are separate operations on that owner. |
| failure | Catches bad_alloc only during mode switch; direct allocator/syscall/MemoryAccount denial not injected. |
| cost | Up to 8192 fresh seed+bootstrap attempts, including same-owner bootstrap retry for failures. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0064

[Lines 435–454](../../../../../tests/unit/delta_runtime_exception_test.cpp#L435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_spool_limit_atomicity(std::size_t row_limit, std::size_t byte_limit,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check row-count and payload-byte spool quotas reject a loop insertion atomically. |
| inputs / outputs | Takes row and byte limits plus label; creates maintenance runtime, seeds, switches to delta then applies update expecting resource_limit. |
| invariants | No spool during maintenance seeding; after failed apply, snapshot/live/sequence/mode/storage/invariants match committed preimage. The call is logical quota rejection, not malloc injection. |
| ownership | Runtime owns current physical/live state; before images are caller-owned copies. |
| failure | Requires exact resource_limit; unexpected error propagates. |
| cost | One failed epoch after a small seeded fixture for each configured limit. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0066

[Lines 456–462](../../../../../tests/unit/delta_runtime_exception_test.cpp#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_exists_sql_row(const DeltaRuntime& runtime, bool expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read and verify one Boolean SQL EXISTS result from a committed runtime. |
| inputs / outputs | Takes runtime and expected bool; creates \`results()\` cursor, reads one row and terminal null. |
| invariants | Row has exactly one Boolean field equal to expected; no second row. |
| ownership | Cursor read lease and returned Tuple are local owning values. |
| failure | Mismatch throws runtime_error; cursor errors propagate. |
| cost | Two cursor next calls. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/result_cursors.md § Traversal and output rows](../../../../result_cursors.md) |

## B0068

[Lines 464–477](../../../../../tests/unit/delta_runtime_exception_test.cpp#L464); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_exists_flip_output(DeltaRuntime::Epoch& output, DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check false-to-true SQL EXISTS output emits erase(false) then insert(true). |
| inputs / outputs | Takes mutable Epoch and runtime; reads two SignedResult rows. |
| invariants | Ordinal 1 erases false; ordinal 2 inserts true; after second row remaining zero and runtime ready. |
| ownership | Epoch owns unread spool and committed input; returned records own tuples. |
| failure | Unexpected order/value/lease state throws runtime_error. |
| cost | Consumes exactly two committed output records. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0070

[Lines 479–505](../../../../../tests/unit/delta_runtime_exception_test.cpp#L479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_exists_mapping_spool_failure_is_atomic() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cause SQL EXISTS mapping to exceed a one-row spool, then compare prior false state and a separate clean transition. |
| inputs / outputs | No args; starts false delta runtime with row limit1, checks SQL false, attempts insert and expects resource_limit; captures state, then uses a distinct clean runtime to inspect both expected signs. |
| invariants | Failed apply returns no partial Epoch; original runtime’s physical/support/live/sequence/mode unchanged and still queries false. This function does not retry the failed update on the original owner; clean is a separate comparator. |
| ownership | Failed runtime remains owner of committed false state; clean runtime and output artifact are separate. |
| failure | Exact resource_limit required. This is spool quota rejection, not an allocator fault point. |
| cost | One rejected input plus one independent clean input and two small SQL result reads. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0072

[Lines 507–533](../../../../../tests/unit/delta_runtime_exception_test.cpp#L507); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_zero_spool_limits_allow_empty_output() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify zero spool limits allow a duplicate insert whose signed output is empty. |
| inputs / outputs | No args; seeds in maintenance mode, bootstraps delta, then repeats an existing edge. |
| invariants | Epoch has no physical change/output rows and no lease, but accepted sequence advances; physical rows and derivations remain same, support sequence tag and live sequence advance. |
| ownership | Runtime owns live state; empty Epoch retains committed input image until dropped but no delivery lease. |
| failure | Assertion/update failures propagate; not a fault-injection path. |
| cost | One duplicate physical update and committed snapshot checks. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0074

[Lines 535–549](../../../../../tests/unit/delta_runtime_exception_test.cpp#L535); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_bootstrap_cursor_limit_preserves_maintenance() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set cursor work limit to zero and verify delta bootstrap does not partially switch maintenance mode. |
| inputs / outputs | No args; seeds a maintenance runtime, snapshots state/stats, then expects set_mode(delta) resource_limit. |
| invariants | Mode remains maintenance; no live image; committed snapshot/storage unchanged and invariants pass. Work-limit failure is distinct from ordinary-new failure. |
| ownership | Runtime remains same owner; images/stats are owning local copies. |
| failure | Requires exact resource_limit. |
| cost | One bootstrap cursor attempt and state comparisons. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/result_cursors.md § Work accounting](../../../../result_cursors.md), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0076

[Lines 551–567](../../../../../tests/unit/delta_runtime_exception_test.cpp#L551); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_active_output_blocks_input_and_mode_switch() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify unread nonempty Epoch output blocks new input and mode changes until discard. |
| inputs / outputs | No args; seed runtime, apply loop insertion producing three rows, attempt second apply and mode switch. |
| invariants | Both operations report runtime_busy; sequence/mode/output lease remain unchanged; discard releases output owner without rewinding committed input. |
| ownership | Epoch owns output spool; runtime facade owns shared DeltaRuntime::Impl while active. |
| failure | Exact runtime_busy required; state mismatch throws runtime_error. |
| cost | One held three-row output and two rejected writer operations. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0078

[Lines 569–610](../../../../../tests/unit/delta_runtime_exception_test.cpp#L569); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_delivery_and_discard_are_allocation_free() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard Epoch::next and discard with the directly replaced ordinary-new fault scope. |
| inputs / outputs | No args; drains three committed SignedResults under fail-after zero, then separately discards an output artifact under same guard. |
| invariants | Moves rows and releases output lease; committed input remains accepted; input source tuple and support journal audit pin remain accessible afterward. Does not call sink delivery/ack API. |
| ownership | Epoch owns the spool and committed PhysicalEpoch; each returned SignedResult owns tuple values; input journal/source pins persist in artifact data after output owner release. |
| failure | An ordinary-new request reaching the replacement throws bad_alloc. Direct malloc/realloc/system/account denial and dedicated aligned/nothrow paths are not injected. |
| cost | Three output moves plus one discard under narrow replacement-new guard; not process-wide no-allocation proof. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0080

[Lines 612–660](../../../../../tests/unit/delta_runtime_exception_test.cpp#L612); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_facade_move_and_destruction_with_active_output() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check active output follows a moved facade and remains consumable after facade destruction. |
| inputs / outputs | No args; tests facade move while Epoch active, destroys a facade while separate Epoch persists then consumes, and discards a third Epoch after facade destruction. |
| invariants | Move preserves shared output lease; facade destruction does not invalidate output; next/discard release output owner, while committed input source/support audit pins still resolve. |
| ownership | Active Epoch::Data retains shared DeltaRuntime::Impl until finish; after finish the artifact still retains input/journal fields and returned rows own values. |
| failure | Assertions or valid Epoch API errors fail; ordinary-new guards are limited to next/discard. |
| cost | Three small runtime/output lifecycles; no sink invocation or durable acknowledgement. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0082

[Lines 662–701](../../../../../tests/unit/delta_runtime_exception_test.cpp#L662); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_final_epoch_and_plan_destruction_are_allocation_free() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard destruction of a final active Epoch and two PhysicalPlan variants. |
| inputs / outputs | No args; resets Epoch with active output, ordinary PhysicalPlan, then normalized SQL PhysicalPlan while fail-after is zero. |
| invariants | Each optional resets; SQL plan includes normalized metadata/identity; only requests through ordinary replacement symbols are forbidden. |
| ownership | Optional owns Epoch or PhysicalPlan; Epoch retains committed artifact until reset. |
| failure | Check fails if a guarded ordinary-new request throws or object remains; direct malloc/system paths are not guarded. |
| cost | Three destruction cases; not a global heap or account-denial test. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0084

[Lines 703–730](../../../../../tests/unit/delta_runtime_exception_test.cpp#L703); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_finite_work_limit_preserves_input() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate a DeltaRuntime abstract work limit between delta bootstrap and update costs, then verify failed update preserves input. |
| inputs / outputs | No args; a calibration runtime measures bootstrap and clean update work; second runtime uses bootstrap work as cap and attempts loop insertion. |
| invariants | Requires clean update work&gt;bootstrap; update returns resource_limit while image/live/sequence/mode/stats remain same. This is a work-limit oracle, not allocator injection or CPU timing. |
| ownership | Each calibration/limited runtime is independent; failed update leaves limited owner reusable though function does not retry it. |
| failure | Requires resource_limit; exact committed-state checks through check_unchanged. |
| cost | Two seeded runtimes, one successful calibration update and one bounded failure. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0085

[Lines 731–733](../../../../../tests/unit/delta_runtime_exception_test.cpp#L731); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L731-L733:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_runtime_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/code_review.md](../../../../code_review.md) |

## B0086

[Lines 734–763](../../../../../tests/unit/delta_runtime_exception_test.cpp#L734); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(int argc,char** argv) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select one live-maintenance policy from process arguments and run all DeltaRuntime exception fixtures. |
| inputs / outputs | Accepts argc/argv; no arg uses default policy; \`eager\` or \`incremental\` selects that policy; runs insert/delete/shared-separator/mode/quota/output/teardown/work checks. |
| invariants | Any other args fail; selected policy is passed through options; output success means source check completion only, not evidence from this review. |
| ownership | Main owns all fixtures and temporary runtimes in called routines. |
| failure | Catches std::exception, resets fail_after, writes diagnostic and returns1; otherwise returns0. |
| cost | Finite fault sweeps up to 8192 thresholds under each selected process policy; no wall time or native execution claim. |
| Design | [tests/unit/delta_runtime_exception_test.cpp](../../../../../tests/unit/delta_runtime_exception_test.cpp), [docs/delta_runtime.md § One physical input](../../../../delta_runtime.md) |
