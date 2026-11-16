# `tests/unit/delta_lifecycle_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/delta_lifecycle_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `21eb44fe6e5619ac9138ee4ff3d5f6807c13cdb5c0af57150436c55f471cfd34`. 1065 lines partitioned into 76 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–28](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Keep failure armed while a pending epoch closes cursors and undoes private · [reviewed contract](#b0001) |
| [B0002 · 29–36](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L29) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 37–43](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L37) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 44–45](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L44) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 46–46](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L46) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 47–47](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L47) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 48–48](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L48) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 49–49](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L49) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 50–50](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L50) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 51–51](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L51) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 52–63](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L52) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;DeltaRuntime&gt;); · [reviewed contract](#b0011) |
| [B0012 · 64–66](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L64) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0012) |
| [B0013 · 67–67](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L67) | Explanatory comments or spacing. |  |
| [B0014 · 68–78](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L68) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, "unexpected error code: expected " + std::string(code) + · [reviewed contract](#b0014) |
| [B0015 · 79–79](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L79) | Explanatory comments or spacing. |  |
| [B0016 · 80–80](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L80) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0016) |
| [B0017 · 81–81](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L81) | Callable definition: Row edge(std::int64_t left, std::int64_t right) | calls n; returns {n(left), n(right)} · [reviewed contract](#b0017) |
| [B0018 · 82–82](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L82) | Explanatory comments or spacing. |  |
| [B0019 · 83–98](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L83) | Callable definition: PhysicalPlan make_alias_separator_plan() | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0019) |
| [B0020 · 99–99](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L99) | Explanatory comments or spacing. |  |
| [B0021 · 100–113](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L100) | Callable definition: PhysicalPlan make_shared_separator_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0021) |
| [B0022 · 114–114](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L114) | Explanatory comments or spacing. |  |
| [B0023 · 115–124](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L115) | Callable definition: DeltaOptions options(std::size_t spool_rows = 65536, std::size_t spool_bytes = 64 * 1024 * 1024) | calls ; returns result · [reviewed contract](#b0023) |
| [B0024 · 125–125](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L125) | Explanatory comments or spacing. |  |
| [B0025 · 126–131](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L126) | Callable definition: void apply_and_discard(DeltaRuntime& runtime, TableId table, SetOperation operation, Row values) | calls apply, sequence, std::move, discard; guard check(runtime.ready(), "discarding a seed output did not release its output lease"); · [reviewed contract](#b0025) |
| [B0026 · 132–132](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L132) | Explanatory comments or spacing. |  |
| [B0027 · 133–136](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L133) | Callable definition: void seed_alias_plan(DeltaRuntime& runtime) | calls apply_and_discard, edge; growth insert · [reviewed contract](#b0027) |
| [B0028 · 137–137](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L137) | Explanatory comments or spacing. |  |
| [B0029 · 138–142](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L138) | Callable definition: void seed_shared_separator(DeltaRuntime& runtime) | calls apply_and_discard, n; growth insert · [reviewed contract](#b0029) |
| [B0030 · 143–143](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L143) | Explanatory comments or spacing. |  |
| [B0031 · 144–148](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L144) | Type/record definition: struct DerivationImage |  · [reviewed contract](#b0031) |
| [B0032 · 149–156](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L149) | Type/record definition: struct SnapshotImage |  · [reviewed contract](#b0032) |
| [B0033 · 157–157](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L157) | Explanatory comments or spacing. |  |
| [B0034 · 158–170](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L158) | Callable definition: SnapshotImage snapshot_image(const DeltaRuntime& runtime) | calls snapshot, owner, io::write_support_snapshot, plan; returns result; growth push_back, resize; 2 loop sites · [reviewed contract](#b0034) |
| [B0035 · 171–171](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0036 · 172–183](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L172) | Callable definition: io::Json normalized_owners(io::Json value) | calls is_object, contains, items, self; returns value; 2 loop sites · [reviewed contract](#b0036) |
| [B0037 · 184–184](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L184) | Explanatory comments or spacing. |  |
| [B0038 · 185–189](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L185) | Callable definition: bool same_logical_snapshot(const SnapshotImage& left, const SnapshotImage& right) | calls normalized_owners; returns left.sequence == right.sequence && left.physical == right.physical && · [reviewed contract](#b0038) |
| [B0039 · 190–190](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L190) | Explanatory comments or spacing. |  |
| [B0040 · 191–195](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L191) | Callable definition: bool same_live(const std::optional&lt;LiveSnapshot&gt;& left, const std::optional&lt;LiveSnapshot&gt;& right) | calls has_value; returns false; !left \|\| (left-&gt;sequence == right-&gt;sequence && left-&gt;factors == right-&gt;factors) · [reviewed contract](#b0040) |
| [B0041 · 196–196](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L196) | Explanatory comments or spacing. |  |
| [B0042 · 197–213](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L197) | Callable definition: void check_stats(const PhysicalStorageStatistics& before, const PhysicalStorageStatistics& after, std::string_view context) | calls check, std::string, check_arena; guard check(old_stats.live_records == new_stats.live_records && · [reviewed contract](#b0042) |
| [B0043 · 214–214](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L214) | Explanatory comments or spacing. |  |
| [B0044 · 215–230](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L215) | Callable definition: void check_unchanged(DeltaRuntime& runtime, const SnapshotImage& before, const std::optional&lt;LiveSnapshot&gt;& live_before, const Ph… | calls check, ready, state, sequence; guard check(runtime.ready() && runtime.state() == DeltaState::ready && · [reviewed contract](#b0044) |
| [B0045 · 231–231](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L231) | Explanatory comments or spacing. |  |
| [B0046 · 232–237](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L232) | Type/record definition: struct RecordImage |  · [reviewed contract](#b0046) |
| [B0047 · 238–238](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L238) | Explanatory comments or spacing. |  |
| [B0048 · 239–244](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L239) | Callable definition: std::vector&lt;RecordImage&gt; records(DeltaRuntime::Epoch& epoch) | calls next, push_back, crown::storage::export_row, values; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 245–245](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L245) | Explanatory comments or spacing. |  |
| [B0050 · 246–264](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L246) | Callable definition: void check_retry_matches_clean(DeltaRuntime& retried_runtime, DeltaRuntime::Epoch& retried_output, DeltaRuntime& clean_runtime, D… | calls check, sequence, std::string, records; guard check(retried_output.sequence() == expected_sequence && · [reviewed contract](#b0050) |
| [B0051 · 265–265](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0052 · 266–318](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L266) | Callable definition: template &lt;class RuntimeFactory, class Seeder&gt; void sweep_begin_failures(RuntimeFactory make_runtime, Seeder seed, std::string_vie… | calls make_runtime, seed, snapshot_image, live_snapshot; guard check(retry.active() && retry.sequence() == sequence + 1,; growth emplace, insert; 1 loop sites · [reviewed contract](#b0052) |
| [B0053 · 319–319](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L319) | Explanatory comments or spacing. |  |
| [B0054 · 320–374](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L320) | Callable definition: template &lt;class Seeder&gt; void sweep_first_step_failures(Seeder seed, std::string_view label) | calls make_alias_separator_plan, options, seed, snapshot_image; guard check(pending.active(), std::string(label) + ": fixture begin did not retain its transaction");; growth insert; 1 loop sites · [reviewed contract](#b0054) |
| [B0055 · 375–375](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L375) | Explanatory comments or spacing. |  |
| [B0056 · 376–440](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L376) | Callable definition: void sweep_resumed_cursor_failures() | calls make_shared_separator_plan, options, seed_shared_separator, snapshot_image; guard check(result != DeltaStep::prepared,; growth insert; 2 loop sites · [reviewed contract](#b0056) |
| [B0057 · 441–441](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L441) | Explanatory comments or spacing. |  |
| [B0058 · 442–509](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L442) | Callable definition: void sweep_paused_drain_failures() | calls make_alias_separator_plan, options, seed_alias_plan, snapshot_image; guard check(pending.active() && pending.state() == DeltaState::paused &&; growth insert; 1 loop sites; source comment (unverified): // The chosen fixture has work, but this guard keeps quota and lifecycle · [reviewed contract](#b0058) |
| [B0059 · 510–510](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L510) | Explanatory comments or spacing. |  |
| [B0060 · 511–568](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L511) | Callable definition: void test_stage_prefix_rollback_and_aliases() | calls make_alias_separator_plan, options, make_shared_separator_plan, seed_alias_plan; guard check(result != DeltaStep::prepared,; returns kind == 0 ? DeltaRuntime{make_alias_separator_plan(), options()}; growth insert; 2 loop sites · [reviewed contract](#b0060) |
| [B0061 · 569–569](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L569) | Explanatory comments or spacing. |  |
| [B0062 · 570–674](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L570) | Callable definition: void test_noalloc_pending_lifecycle() | calls make_alias_separator_plan, options, seed_alias_plan, snapshot_image; guard check(!pending.active() && pending.state() == DeltaState::aborted,; returns pending.commit(); growth emplace, insert · [reviewed contract](#b0062) |
| [B0063 · 675–675](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L675) | Explanatory comments or spacing. |  |
| [B0064 · 676–787](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L676) | Callable definition: void test_quota_failures_after_partial_progress() | calls options, make_alias_separator_plan, seed_alias_plan, set_mode; guard check(result != DeltaStep::prepared,; growth insert; 3 loop sites; source comment (unverified): // Calibrate an exact private prefix, then place the work ceiling at that · [reviewed contract](#b0064) |
| [B0065 · 788–788](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L788) | Explanatory comments or spacing. |  |
| [B0066 · 789–792](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L789) | Callable definition: void burn_for(std::chrono::milliseconds duration) | calls std::chrono::steady_clock::now; 1 loop sites · [reviewed contract](#b0066) |
| [B0067 · 793–793](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L793) | Explanatory comments or spacing. |  |
| [B0068 · 794–837](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L794) | Callable definition: void test_serializer_callback_lifecycle_and_timing() | calls make_alias_separator_plan, options, seed_alias_plan, apply; guard check(threw && serializers == 1 && sinks == 0 && output.active() && output.remaining() == 3 &&; growth insert · [reviewed contract](#b0068) |
| [B0069 · 838–838](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L838) | Explanatory comments or spacing. |  |
| [B0070 · 839–959](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L839) | Callable definition: void test_delivery_callback_lifecycle() | calls make_alias_separator_plan, options, seed_alias_plan, sequence; guard check(threw && output.active() && output.remaining() == remaining &&; growth emplace, insert, push_back, reserve; 1 loop sites; source comment (unverified): // The request is deferred until this borrowed row is released. · [reviewed contract](#b0070) |
| [B0071 · 960–960](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L960) | Explanatory comments or spacing. |  |
| [B0072 · 961–1017](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L961) | Callable definition: void test_discard_faults_and_drain_quotas() | calls make_alias_separator_plan, options, seed_alias_plan, snapshot_image; guard check(!pending.active() && pending.state() == DeltaState::aborted,; growth emplace, insert; 1 loop sites · [reviewed contract](#b0072) |
| [B0073 · 1018–1018](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1018) | Explanatory comments or spacing. |  |
| [B0074 · 1019–1040](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1019) | Callable definition: void test_prepare_commit_and_state_errors() | calls make_alias_separator_plan, options, seed_alias_plan, sequence; guard check(pending.active() && runtime.state() == DeltaState::pending_delta,; returns pending.commit(); growth insert · [reviewed contract](#b0074) |
| [B0075 · 1041–1043](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1041) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0075) |
| [B0076 · 1044–1065](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1044) | Callable definition: int main() | calls sweep_begin_failures, make_alias_separator_plan, options, sweep_first_step_failures; returns DeltaRuntime{make_alias_separator_plan(), options()}; 1 · [reviewed contract](#b0076) |

## B0001

[Lines 1–28](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L28:sha256:2d72838bf1e233fc8b77a5386322fe9c756964ce6146071ae3004f5184f76d37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_lifecycle_exception_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", &lt;algorithm&gt;, &lt;chrono&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 29–36](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement one fail-after position for the test replacement allocation seam. |
| inputs / outputs | Requested byte size enters; successful calls return malloc storage with zero requests promoted to one byte; a chosen fail_after position or malloc failure throws std::bad_alloc. |
| invariants | At fail_after zero it throws before malloc; positive values decrement once; the counter counts only calls that reach this helper through the ordinary throwing scalar or array operator new replacements. |
| ownership | Thread-local fail_after belongs to this test executable. Replacement-new storage is malloc-backed; deletes free compatible pointers. |
| failure | This file defines replacements for ordinary throwing scalar and array global new. Index i allows i successful intercepted requests, then bad_alloc persists until FaultScope resets it; backing malloc failure also throws. Direct malloc/realloc, system calls and separate account-limit denials are not intercepted. No dedicated aligned/nothrow replacements are defined; implementation-dependent library delegation is not asserted coverage. |
| cost | One counter branch and at most one malloc call; the index is calls, not bytes or total allocations. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0003

[Lines 37–43](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Scope the thread-local ordinary-new failure position. |
| inputs / outputs | Constructor sets fail_after to its argument (default -1); forbid_allocations sets it to zero; destructor unconditionally resets it to -1; copying is deleted. |
| invariants | The guard is deliberately local and not a nested save/restore stack; while zero, the replaced ordinary throwing scalar and array operator new calls fail. Other allocation APIs are not intercepted. |
| ownership | The guard does not own runtime state; it changes the test executable thread-local fail_after value and resets it on destruction. |
| failure | No exception is thrown by guard operations; intercepted ordinary new may throw std::bad_alloc when used while the counter is zero. |
| cost | One thread-local write on entry/reset and one on explicit forbid_allocations. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0004

[Lines 44–45](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L45:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_lifecycle_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 46–46](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary throwing scalar global new through the failure seam. |
| inputs / outputs | Byte count enters; pointer from malloc_new exits or std::bad_alloc is thrown. |
| invariants | Only the ordinary scalar throwing form is replaced here; it shares the same per-thread counter with the ordinary array form. |
| ownership | Thread-local fail_after belongs to this test executable. Replacement-new storage is malloc-backed; deletes free compatible pointers. |
| failure | This file defines replacements for ordinary throwing scalar and array global new. Index i allows i successful intercepted requests, then bad_alloc persists until FaultScope resets it; backing malloc failure also throws. Direct malloc/realloc, system calls and separate account-limit denials are not intercepted. No dedicated aligned/nothrow replacements are defined; implementation-dependent library delegation is not asserted coverage. |
| cost | One call to the wrapper and malloc_new; no direct account-byte measurement. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0006

[Lines 47–47](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary throwing array global new through the failure seam. |
| inputs / outputs | Byte count enters; pointer from malloc_new exits or std::bad_alloc is thrown. |
| invariants | Only the ordinary array throwing form is replaced here; it shares the scalar form counter. |
| ownership | Thread-local fail_after belongs to this test executable. Replacement-new storage is malloc-backed; deletes free compatible pointers. |
| failure | This file defines replacements for ordinary throwing scalar and array global new. Index i allows i successful intercepted requests, then bad_alloc persists until FaultScope resets it; backing malloc failure also throws. Direct malloc/realloc, system calls and separate account-limit denials are not intercepted. No dedicated aligned/nothrow replacements are defined; implementation-dependent library delegation is not asserted coverage. |
| cost | One call to the wrapper and malloc_new. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0007

[Lines 48–48](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the ordinary scalar replacement new. |
| inputs / outputs | Pointer enters; calls std::free; no output. |
| invariants | Null is accepted by free; this is the unsized scalar delete paired with malloc-backed storage. |
| ownership | Thread-local fail_after belongs to this test executable. Replacement-new storage is malloc-backed; deletes free compatible pointers. |
| failure | This file defines replacements for ordinary throwing scalar and array global new. Index i allows i successful intercepted requests, then bad_alloc persists until FaultScope resets it; backing malloc failure also throws. Direct malloc/realloc, system calls and separate account-limit denials are not intercepted. No dedicated aligned/nothrow replacements are defined; implementation-dependent library delegation is not asserted coverage. |
| cost | One free call. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0008

[Lines 49–49](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage returned by the ordinary array replacement new. |
| inputs / outputs | Pointer enters; calls std::free; no output. |
| invariants | This is the unsized array delete paired with malloc-backed replacement storage. |
| ownership | Thread-local fail_after belongs to this test executable. Replacement-new storage is malloc-backed; deletes free compatible pointers. |
| failure | This file defines replacements for ordinary throwing scalar and array global new. Index i allows i successful intercepted requests, then bad_alloc persists until FaultScope resets it; backing malloc failure also throws. Direct malloc/realloc, system calls and separate account-limit denials are not intercepted. No dedicated aligned/nothrow replacements are defined; implementation-dependent library delegation is not asserted coverage. |
| cost | One free call. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0009

[Lines 50–50](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage through sized delete. |
| inputs / outputs | Pointer and compiler-supplied size enter; size is ignored and pointer is passed to std::free. |
| invariants | The deallocation family remains compatible with malloc-backed replacement new. |
| ownership | Thread-local fail_after belongs to this test executable. Replacement-new storage is malloc-backed; deletes free compatible pointers. |
| failure | This file defines replacements for ordinary throwing scalar and array global new. Index i allows i successful intercepted requests, then bad_alloc persists until FaultScope resets it; backing malloc failure also throws. Direct malloc/realloc, system calls and separate account-limit denials are not intercepted. No dedicated aligned/nothrow replacements are defined; implementation-dependent library delegation is not asserted coverage. |
| cost | One free call; no size-dependent work. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0010

[Lines 51–51](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage through sized delete. |
| inputs / outputs | Pointer and compiler-supplied size enter; size is ignored and pointer is passed to std::free. |
| invariants | The deallocation family remains compatible with malloc-backed replacement new\[\]. |
| ownership | Thread-local fail_after belongs to this test executable. Replacement-new storage is malloc-backed; deletes free compatible pointers. |
| failure | This file defines replacements for ordinary throwing scalar and array global new. Index i allows i successful intercepted requests, then bad_alloc persists until FaultScope resets it; backing malloc failure also throws. Direct malloc/realloc, system calls and separate account-limit denials are not intercepted. No dedicated aligned/nothrow replacements are defined; implementation-dependent library delegation is not asserted coverage. |
| cost | One free call; no size-dependent work. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0011

[Lines 52–63](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L63:sha256:0b78ed59139c07cbf912fc6032e5a975ca97461b81be73225f30e57bf633e01c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta_lifecycle_exception_test.cpp: bind local aliases/name imports; require 6 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 64–66](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one test assertion with std::runtime_error. |
| inputs / outputs | Boolean condition and message enter; true returns, false throws. |
| invariants | Does not translate product Error or std::bad_alloc. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Fixed small-fixture or field conversion; not runtime cost. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp) |

## B0014

[Lines 68–78](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an action and require a crown::api::Error with an exact code. |
| inputs / outputs | Action and string_view code enter; returns after a matching Error or throws std::runtime_error. |
| invariants | Only crown::api::Error is caught; a wrong code is diagnosed and other exception types propagate. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Fixed small-fixture or field conversion; not runtime cost. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp) |

## B0016

[Lines 80–80](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one integer Value. |
| inputs / outputs | int64 enters; Value returns by value. |
| invariants | No runtime state changes. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Fixed small-fixture or field conversion; not runtime cost. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp) |

## B0017

[Lines 81–81](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t left, std::int64_t right) { return {n(left), n(right)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an owning two-field edge Row. |
| inputs / outputs | Two int64 scalars enter; Row containing integer Values exits. |
| invariants | The result has exactly two columns in caller-provided order. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Fixed small-fixture or field conversion; not runtime cost. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp) |

## B0019

[Lines 83–98](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_alias_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and lower the literal self-join alias fixture. |
| inputs / outputs | Binds SELECT DISTINCT l.x, l.z, r.z FROM E AS l JOIN E AS r ON l.z = r.x; normalizes the bound query; lowers it with a generalized join root and two native leaf occurrences over table 0. |
| invariants | Binding/normalization diagnostic alternatives become std::runtime_error; left and right aliases remain separate occurrences even though they share one physical table. |
| ownership | Catalog, tree, binding alternatives and normalized program are local values; returned PhysicalPlan owns its compiled representation. |
| failure | A BindingDiagnostic is converted to std::runtime_error with code/message; planner errors propagate. |
| cost | Binds, normalizes and lowers one fixed small query; no execution or cost theorem. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0021

[Lines 100–113](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_shared_separator_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the two-table shared-separator fixture plan. |
| inputs / outputs | Creates R(a,x) and S(x,y), a query over both occurrences, and a native tree sharing x; returns PhysicalPlan. |
| invariants | The native leaves are distinct table occurrences joined on shared separator x. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Compiles one fixed two-relation fixture. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0023

[Lines 115–124](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions options(std::size_t spool_rows = 65536,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build DeltaOptions for the exception/lifecycle fixtures. |
| inputs / outputs | Optional spool row/byte limits enter with defaults 65536 rows and 64 MiB; returns delta mode, on_output live maintenance, transition capture, and requested limits. |
| invariants | These are configured row and spool-byte limits; no account memory-limit fault is configured by this helper. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Copies scalar configuration only. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md) |

## B0025

[Lines 126–131](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply_and_discard(DeltaRuntime& runtime, TableId table,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a contiguous seed update and immediately release its public output lease. |
| inputs / outputs | Borrowed runtime, table, operation and owning Row by value enter; runtime applies sequence()+1, returned Epoch is discarded, then runtime.ready() is checked. |
| invariants | Each seed is physically committed but its public output is intentionally discarded; discard must release the output lease before another seed. |
| ownership | Caller owns DeltaRuntime; this helper owns the moved Row and temporary committed Epoch only until discard. |
| failure | Product API errors propagate; failure to return to ready throws std::runtime_error. |
| cost | One runtime apply and output discard per seed row. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md) |

## B0027

[Lines 133–136](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seed_alias_plan(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed the self-join alias fixture with two reciprocal edges. |
| inputs / outputs | Runtime is borrowed; inserts edge(1,2) and edge(2,1) through apply_and_discard. |
| invariants | Both aliases read the same seeded table and the seed outputs are discarded before the next update. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Two contiguous inserts and immediate lease release. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0029

[Lines 138–142](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void seed_shared_separator(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed the shared-separator fixture with two R rows and one S row. |
| inputs / outputs | Runtime is borrowed; inserts R(1,7), R(2,7), and S(7,9), discarding each output. |
| invariants | Both R rows share x=7 with the S fixture row; this seeds a nonempty answer for later S insertion and R erasure scenarios. |
| ownership | Arguments are borrowed/copy-by-value as stated; returned Rows, strings, and image structs own their contents. |
| failure | Fixture and comparison errors propagate; check() turns a false predicate into std::runtime_error. |
| cost | Three contiguous inserts and immediate output discard. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0031

[Lines 144–148](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L144); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DerivationImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one exported derivation row and its multiplicity for snapshot comparison. |
| inputs / outputs | Owns Row values and uint64 count; defaulted equality compares both. |
| invariants | This is an owning snapshot image, detached from any borrowed runtime tuple. |
| ownership | Snapshot/image results own copied Relations, rows, and JSON. Runtime, live snapshot, and storage-statistics inputs are borrowed for comparison. |
| failure | Serialization, cursor/API, and invariant failures propagate. Mismatch checks throw std::runtime_error. |
| cost | One row copy and one integer field. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md) |

## B0032

[Lines 149–156](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L149); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the logical physical/support/derivation state and public owner of a runtime snapshot. |
| inputs / outputs | Owns sequence, SupportOwnerId, physical Relation vector, serialized support Json, and per-occurrence DerivationImage vectors; defaulted equality compares every field. |
| invariants | The owner is retained for exact same-runtime unchanged checks; cross-runtime logical comparison later normalizes owner identity only in support JSON and omits this owner field. |
| ownership | Snapshot/image results own copied Relations, rows, and JSON. Runtime, live snapshot, and storage-statistics inputs are borrowed for comparison. |
| failure | Serialization, cursor/API, and invariant failures propagate. Mismatch checks throw std::runtime_error. |
| cost | Copies fixture physical rows, support snapshot JSON and derivation rows; not a byte-account or RSS measure. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0034

[Lines 158–170](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage snapshot_image(const DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize an owning SnapshotImage from the current committed runtime. |
| inputs / outputs | Runtime is borrowed; snapshot/sequence/owner, exported physical tables, support JSON, and exported derivation rows are copied into result. |
| invariants | Every tuple becomes an owning Row plus count; snapshot image remains valid after later runtime changes. This is used after a ready barrier. |
| ownership | Only the DeltaRuntime input is borrowed; SnapshotImage and all nested Relations/Json/Rows own their data. |
| failure | Snapshot, JSON serialization, row export and allocation errors propagate. |
| cost | Copies and serializes selected physical/support/derivation state for the small fixture. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [docs/delta_lifecycle.md § States and operations](../../../../delta_lifecycle.md) |

## B0036

[Lines 172–183](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_owners(io::Json value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize support-owner IDs recursively in an owned Json value. |
| inputs / outputs | Json enters by value; recursively replaces each object member named owner with integer zero; normalized Json exits. |
| invariants | Arrays/objects are traversed recursively; non-object/non-array scalars are unchanged. This is only for cross-runtime logical comparison. |
| ownership | Snapshot/image results own copied Relations, rows, and JSON. Runtime, live snapshot, and storage-statistics inputs are borrowed for comparison. |
| failure | Serialization, cursor/API, and invariant failures propagate. Mismatch checks throw std::runtime_error. |
| cost | Walks and mutates the copied JSON tree once. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md) |

## B0038

[Lines 185–189](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_logical_snapshot(const SnapshotImage& left, const SnapshotImage& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare logical snapshots while ignoring public owner identity. |
| inputs / outputs | Two SnapshotImage values are borrowed; returns equality over sequence, physical Relations, support JSON after recursive owner normalization, and derivation vectors. |
| invariants | It deliberately does not compare SnapshotImage.owner; it does compare sequence and all listed logical rows/counts. |
| ownership | Snapshot/image results own copied Relations, rows, and JSON. Runtime, live snapshot, and storage-statistics inputs are borrowed for comparison. |
| failure | Serialization, cursor/API, and invariant failures propagate. Mismatch checks throw std::runtime_error. |
| cost | Traverses copied supports for normalization and compares small fixture images. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md) |

## B0040

[Lines 191–195](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_live(const std::optional<LiveSnapshot>& left,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare whether two optional live snapshots have the same presence and logical image. |
| inputs / outputs | Two optional LiveSnapshot references enter; returns false on presence mismatch, otherwise compares sequence and factor relations. |
| invariants | No owner or allocation statistics are part of this live-image comparator. |
| ownership | Snapshot/image results own copied Relations, rows, and JSON. Runtime, live snapshot, and storage-statistics inputs are borrowed for comparison. |
| failure | Serialization, cursor/API, and invariant failures propagate. Mismatch checks throw std::runtime_error. |
| cost | Compares presence and, when present, sequence and fixture factor rows. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0042

[Lines 197–213](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_stats(const PhysicalStorageStatistics& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected committed arena and derivation-key accounting after rollback. |
| inputs / outputs | Before/after PhysicalStorageStatistics and diagnostic context enter by reference/view; throws on mismatch. |
| invariants | For source and support arenas, live_records, retained_records, and pins must match while slots may stay equal or increase; derivation_keys must match. It does not require high-water slot reclamation. |
| ownership | Statistics are borrowed read values; no account/controller ownership is changed. |
| failure | Mismatch throws std::runtime_error with context; product statistics calls happen at the caller and may propagate. |
| cost | Compares selected counters only; does not measure total charged bytes, global heap, RSS, or CPU. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0044

[Lines 215–230](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L215); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_unchanged(DeltaRuntime& runtime, const SnapshotImage& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an aborted pending operation left all checked committed state unchanged. |
| inputs / outputs | Runtime, saved SnapshotImage, optional live snapshot, stats, sequence, answer and context enter; no output. |
| invariants | Requires ready state and DeltaState::ready, same sequence/answer/public owner, exact SnapshotImage, same live factors, selected stats via check_stats, and passing runtime invariants. |
| ownership | Snapshot/image results own copied Relations, rows, and JSON. Runtime, live snapshot, and storage-statistics inputs are borrowed for comparison. |
| failure | A mismatch throws std::runtime_error; snapshot and invariant/API errors propagate. |
| cost | Re-snapshots and serializes selected small physical/support/derivation state and reads statistics. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0046

[Lines 232–237](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L232); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RecordImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the identifying fields for one signed output record image. |
| inputs / outputs | Owns ordinal, SetOperation and Row; defaulted equality checks all fields. |
| invariants | The Row is exported/copied, so equality does not depend on an Epoch borrowed tuple lifetime. |
| ownership | Snapshot/image results own copied Relations, rows, and JSON. Runtime, live snapshot, and storage-statistics inputs are borrowed for comparison. |
| failure | Serialization, cursor/API, and invariant failures propagate. Mismatch checks throw std::runtime_error. |
| cost | One ordinal/op plus owning row comparison. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0048

[Lines 239–244](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<RecordImage> records(DeltaRuntime::Epoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a committed Epoch into owning signed-record images. |
| inputs / outputs | Epoch is borrowed; repeatedly calls next(), exports each tuple into a Row and returns vector&lt;RecordImage&gt;. |
| invariants | Exhausts the epoch cursor; each image owns ordinal/op/values independently of the Epoch. |
| ownership | Epoch remains caller-owned; vector and each exported Row are owning values. |
| failure | Epoch next and row-export errors propagate. |
| cost | One pass over the output rows plus one value export per row. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0050

[Lines 246–264](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_retry_matches_clean(DeltaRuntime& retried_runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a same-sequence retry with a separately initialized clean owner. |
| inputs / outputs | Two runtimes and their output Epochs are borrowed; expected sequence/context enter; no output. |
| invariants | Output sequences and exact ordered RecordImages match; snapshots compare logically with support owner IDs normalized; live snapshots and selected arena/derivation stats match; invariants pass on both owners. Owner IDs themselves may differ. |
| ownership | Retry and clean runtime/output ownership stays with caller; record and snapshot comparators only borrow them during checking. |
| failure | Any mismatch throws std::runtime_error; output cursors are drained by records(). |
| cost | Drains both outputs, copies both snapshots and statistics, and checks both invariant sets. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0052

[Lines 266–318](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class RuntimeFactory, class Seeder>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep intercepted ordinary-new fail positions while constructing a pending epoch. |
| inputs / outputs | Runtime factory and seeder enter; for each point through 4095 create fresh runtime/seed, save state, then arm FaultScope around runtime.begin(update) plus optional emplacement; on bad_alloc check old state, retry same sequence on same runtime, and compare with separate clean runtime. |
| invariants | Seed/snapshot precede the armed operation; when an ordinary-new call throws at fail_after zero, the counter remains zero during stack unwinding, and the catch keeps it at zero until FaultScope exits. Failed begin must leave ready committed state, and same-sequence retry output/logical snapshot/live state/stats match clean execution. First non-failing begin must follow at least one injected ordinary-new failure, then is rolled back and checked unchanged. |
| ownership | Each fault-point iteration owns a fresh DeltaRuntime. On a failed selected operation, its retry uses that same runtime/sequence; a separately constructed clean runtime is only an oracle. PendingEpoch/committed Epoch tokens own their private or retained state until rollback/discard. |
| failure | Catches std::bad_alloc only around begin and optional token emplacement; other exceptions propagate. The file replaces ordinary throwing scalar/array global new. Direct malloc/realloc, system calls and independent account-limit denials are not intercepted. It defines no dedicated aligned/nothrow replacements and makes no coverage promise about indirect library delegation. |
| cost | Fresh fixture owner per fail index, at most 4096 points; retries, snapshots and clean-owner oracle run after the fault scope. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md) |

## B0054

[Lines 320–374](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Seeder>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep intercepted ordinary-new fail positions on the first pending step. |
| inputs / outputs | Seeder and label enter; each point constructs/seeds a fresh alias runtime, begins outside the fault scope, then arms the seam only around pending.step(). |
| invariants | On bad_alloc the token must be aborted and runtime ready with exact saved state; retry of same input/sequence on that same runtime must match an independently seeded clean runtime. First successful step transition must follow at least one failure and is explicitly rolled back before unchanged-state check. |
| ownership | Each fault-point iteration owns a fresh DeltaRuntime. On a failed selected operation, its retry uses that same runtime/sequence; a separately constructed clean runtime is only an oracle. PendingEpoch/committed Epoch tokens own their private or retained state until rollback/discard. |
| failure | Catches std::bad_alloc only around step(); PendingEpoch::step internally rolls back and rethrows. It is not an account-limit injector or all-allocation hook. |
| cost | Fresh runtime per point, at most 4096; seed and baseline snapshots are outside the armed step; same-owner retry and clean comparison are outside it. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md) |

## B0056

[Lines 376–440](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_resumed_cursor_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fail positions while stepping a resumed shared-separator cursor. |
| inputs / outputs | Each point seeds shared-separator runtime; advances pending until one core_result, pauses/resumes, then arms the ordinary-new seam around exactly the next pending.step(). |
| invariants | A failure leaves an aborted token and unchanged committed state; same update/sequence retry on the same owner matches separate clean execution. The first successful transition is rolled back. Fixture drives the cursor lifecycle but does not force a particular lower-level malloc call. |
| ownership | Each fault-point iteration owns a fresh DeltaRuntime. On a failed selected operation, its retry uses that same runtime/sequence; a separately constructed clean runtime is only an oracle. PendingEpoch/committed Epoch tokens own their private or retained state until rollback/discard. |
| failure | Catches std::bad_alloc around one resumed step; rollback/rethrow is product behavior. Other failures propagate. Direct malloc and APIs outside ordinary scalar/array global new are unobserved. |
| cost | At most 4096 fresh shared-separator owners; setup, cursor prefix and pause/resume are outside the fault scope. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md) |

## B0058

[Lines 442–509](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_paused_drain_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fail positions while draining a paused partial alias update. |
| inputs / outputs | For each point seeds runtime, begins update, verifies step while paused raises delta_paused without closing it, accepts one prefix, pauses, then arms seam around drain(). |
| invariants | On bad_alloc the whole token is aborted and saved committed state is unchanged; retry on same runtime and sequence matches clean output/state. On first successful drain the token is prepared, commits the next sequence and releases output. |
| ownership | Each fault-point iteration owns a fresh DeltaRuntime. On a failed selected operation, its retry uses that same runtime/sequence; a separately constructed clean runtime is only an oracle. PendingEpoch/committed Epoch tokens own their private or retained state until rollback/discard. |
| failure | Catches std::bad_alloc only around PendingEpoch::drain(); its internal step failure path rolls back/rethrows. Exact delta_paused is separately expected before the fault scope. |
| cost | At most 8192 fixture owners; prefix setup and ready-state checks are outside the armed drain. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md) |

## B0060

[Lines 511–568](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L511); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_stage_prefix_rollback_and_aliases() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rollback an accepted route prefix for alias and shared-separator fixtures, then retry on the same owner. |
| inputs / outputs | Runs two fixtures: self-join insert and shared-separator erase. Steps until core_result, pauses, explicitly rolls back, checks exact saved state, then retries same update/sequence and compares output/stages or separator counters with a new clean owner. |
| invariants | No unpublished prefix becomes committed; sequence/input remain reusable; completed stage summaries are present, with at least two summaries for aliases, while separator maintenance counters are nonzero for shared-separator case. The test does not assert exact stage-summary ordering. No allocation failure is injected here. |
| ownership | PendingEpoch is explicitly rolled back while its DeltaRuntime facade remains alive; retry uses that same runtime, while clean runtime is only an oracle. |
| failure | Only fixture/API mismatch is raised; no expected product failure beyond normal rollback lifecycle. |
| cost | One partial rollback and one same-owner retry for each of two small plans, plus an independent clean comparison. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [include/crown/frontend/bind.hpp](../../../../../include/crown/frontend/bind.hpp), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/delta_transition_spec.md § Route algorithm](../../../../delta_transition_spec.md) |

## B0062

[Lines 570–674](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L570); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_noalloc_pending_lifecycle() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pending rollback, destruction, moves, pause/resume/drain and prepared commit under the ordinary-new failure seam. |
| inputs / outputs | Runs five cases: rollback; PendingEpoch destruction; token moves then rollback; rollback/reset after DeltaRuntime facade scope; pause/resume/start_drain, then drain outside guard and commit inside guard. |
| invariants | Each guarded operation must succeed while replaced ordinary scalar/array global new calls would fail. Cases check abort/readiness/sequence or prepared commit sequence; the post-start_drain drain is not under the guard, committed output is discarded outside it. No direct malloc/realloc or aligned/system-call coverage. |
| ownership | The pending token holds shared backing implementation state; the fourth case rolls it back after facade lifetime. Other cases keep the facade alive. Committed Epoch lease remains owned until discard. |
| failure | No bad_alloc is expected from intercepted ordinary throwing scalar/array new during the specifically guarded calls. This is a narrow seam assertion, not a proof of zero allocation through every API. |
| cost | A handful of one-row lifecycle cases; only listed calls run with fail_after zero. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/epoch_views.md § Prefix and handle lifetime](../../../../epoch_views.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0064

[Lines 676–787](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L676); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_quota_failures_after_partial_progress() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise spool-row and abstract-work limits after private progress, plus explicit zero-output retention drain. |
| inputs / outputs | Three cases: row limit one then one staged spool record and failing drain; calibrated work ceiling after a core prefix and failing drain; zero row/byte spool limits with start_drain/drain and commit. |
| invariants | The row/work failures must raise resource_limit, abort the whole unpublished epoch and preserve saved committed state. Explicit zero-output drain still accepts/discards internal records, stores zero spool rows and commits an empty output token. The zero-quota branch checks counters/readiness/invariants, not a separate A04 output oracle. |
| ownership | Each calibrated/runtime scenario owns its DeltaRuntime, pending token, and snapshot oracle values. |
| failure | Catches exact crown::api::Error code resource_limit only in quota cases; other failures propagate. No allocation-failure injector is armed. |
| cost | Calibrates a small route work prefix, compares abstract work counters and row/byte spool limits; neither is elapsed CPU time or total-memory/RSS coverage. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0066

[Lines 789–792](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L789); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void burn_for(std::chrono::milliseconds duration) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Busy-wait for a requested steady-clock duration in a callback fixture. |
| inputs / outputs | chrono::milliseconds enters; spins until steady_clock reaches computed end; returns void. |
| invariants | No correctness guarantee is made about exact elapsed duration or scheduler delay. |
| ownership | Runtime and Epoch own the values under measurement; serializer/sink callables are borrowed for each deliver_one invocation. |
| failure | No exception handling or runtime-state change. |
| cost | Consumes at least the intended clock interval when scheduling permits and burns CPU while spinning; this is a test timing stimulus, not a benchmark. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md), [docs/delta_lifecycle.md § Cost and mode boundaries](../../../../delta_lifecycle.md) |

## B0068

[Lines 794–837](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L794); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_serializer_callback_lifecycle_and_timing() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check serializer failure retention and separate serializer/sink timing accumulation. |
| inputs / outputs | Three-row output; throwing serializer, counting sink, then successful callbacks each busy-wait 2ms; first delivery is attempted while ordinary-new seam is set to fail any intercepted call. |
| invariants | CodecFailure means sink was not called, row/lease remains and serialization time is positive while sink time stays zero. Later successful callback consumes one row and increments both accumulated phases; test checks monotonic increase, not exact time. |
| ownership | Runtime and Epoch own the values under measurement; serializer/sink callables are borrowed for each deliver_one invocation. |
| failure | Catches only its local CodecFailure; this branch does not inject bad_alloc as an expected outcome. Ordinary-new guard surrounds the failed delivery call only. |
| cost | One throwing callback plus two deliberate busy-waits; no performance or latency threshold. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0070

[Lines 839–959](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L839); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_delivery_callback_lifecycle() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check callback failure, borrowed-front lifetime, deferred discard, and reentrant-read behavior. |
| inputs / outputs | Four cases: throwing sink and same-epoch retry versus clean owner plus next update; move Epoch facade inside callback; callback-requested discard; callback reentrant next(). Selected callback calls run under ordinary-new-disabled seam except the reentrant case. |
| invariants | A thrown sink keeps ordinal/front/remaining and output lease for retry; successful retry reproduces exact rows and next input result versus clean owner. Moving facade keeps borrowed front valid and lease shared; discard takes effect after callback returns; reentrant next raises runtime_busy without consuming front. No external durability is tested. |
| ownership | Callback SignedResult front is borrowed only until callback return. Saved RecordImage rows are exported copies. Epoch may move during callback; shared output state/lease survives in its new owner. |
| failure | Catches local SinkFailure and exact runtime_busy. No durable sink, network, exactly-once or external acknowledgment is exercised; ordinary-new seam covers only selected callback calls. |
| cost | A few callbacks over a three-row fixture plus clean-owner comparison; no throughput claim. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0072

[Lines 961–1017](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L961); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_discard_faults_and_drain_quotas() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fail positions through discard of a paused prefix, then retry same input. |
| inputs / outputs | Each point creates/seeds fresh runtime, saves snapshots/stats, begins and steps once, pauses, then arms the seam around pending.discard(). |
| invariants | On bad_alloc, discard failure must abort and preserve committed state; retry on same runtime and sequence matches a clean owner. First successful discard commits the sequence with empty inactive output and positive accepted/discarded counters. |
| ownership | Each fault-point iteration owns a fresh DeltaRuntime. On a failed selected operation, its retry uses that same runtime/sequence; a separately constructed clean runtime is only an oracle. PendingEpoch/committed Epoch tokens own their private or retained state until rollback/discard. |
| failure | Catches std::bad_alloc only around pending.discard(). Direct malloc/realloc, system calls and account denials are not intercepted. There are no dedicated aligned/nothrow replacements or assertions about indirect library delegation. |
| cost | At most 8192 fresh runtimes; seed/snapshot/step/pause are outside fault scope; same-owner retry and clean comparison are outside it. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0074

[Lines 1019–1040](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1019); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_prepare_commit_and_state_errors() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check early commit state error and prepared commit under the ordinary-new seam. |
| inputs / outputs | Begins one update; early commit must raise runtime_busy while preserving active pending state; drains to prepared, calls commit with fail_after zero, then discards committed result. |
| invariants | Prepared commit publishes the next input sequence and committed_output lease; discard returns runtime to ready and invariants pass. The commit guard observes only ordinary scalar/array global new calls. |
| ownership | Each case owns its runtime, pending token, committed output, snapshot images, and local callback fixtures. A PendingEpoch holds shared runtime implementation state; a committed Epoch can retain output and an output lease independently of the DeltaRuntime facade. |
| failure | Catches exact runtime_busy for early commit; no allocation exception expected from the narrow ordinary-new guard around prepared commit. |
| cost | One alias-fixture update and result lease transition; no A04 or memory bound claim. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [include/crown/storage/accounted_indexed.hpp](../../../../../include/crown/storage/accounted_indexed.hpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [src/storage/accounted_indexed_journal.inc](../../../../../src/storage/accounted_indexed_journal.inc), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Native table and journal behavior](../../../../memory_accounts.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_lifecycle.md § Drain, disconnect and rollback](../../../../delta_lifecycle.md), [docs/prepared_epochs.md § API and ownership](../../../../prepared_epochs.md), [docs/prepared_epochs.md § Staging, rollback, and publication](../../../../prepared_epochs.md), [docs/delta_lifecycle.md § Publication and committed delivery](../../../../delta_lifecycle.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0075

[Lines 1041–1043](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1041); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1041-L1043:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in delta_lifecycle_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/code_review.md](../../../../code_review.md) |

## B0076

[Lines 1044–1065](../../../../../tests/unit/delta_lifecycle_exception_test.cpp#L1044); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixed exception/lifecycle scenario matrix and report uncaught exceptions as failure status. |
| inputs / outputs | No arguments; runs begin/step/resume/drain sweeps, rollback, no-new cases, quota, callback, discard and prepared-commit scenarios; catches std::exception, resets fail_after, prints message, returns 1, otherwise prints success and returns 0. |
| invariants | Describes source behavior only; packet records no execution result. |
| ownership | main() owns each selected fixture scope only; no runtime is retained after return. |
| failure | The top-level handler catches std::exception, resets the thread-local counter even if a local guard was bypassed, and returns failure. It does not catch non-std exceptions. |
| cost | Dispatches finite fixture loops (bounds 4096/8192 per sweep) if invoked; no runtime duration claim. |
| Design | [tests/unit/delta_lifecycle_exception_test.cpp](../../../../../tests/unit/delta_lifecycle_exception_test.cpp) |
