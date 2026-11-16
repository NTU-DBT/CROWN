# `tests/unit/physical_runtime_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/physical_runtime_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `571284d89dda7e6ac1f020b271d9346780c2509e383d64fae57787fcf31e779f`. 691 lines partitioned into 90 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–24](../../../../../tests/unit/physical_runtime_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Keep this injector local to the executable. The noinline wrapper prevents · [reviewed contract](#b0001) |
| [B0002 · 25–32](../../../../../tests/unit/physical_runtime_exception_test.cpp#L25) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 33–39](../../../../../tests/unit/physical_runtime_exception_test.cpp#L33) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0003) |
| [B0004 · 40–41](../../../../../tests/unit/physical_runtime_exception_test.cpp#L40) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 42–42](../../../../../tests/unit/physical_runtime_exception_test.cpp#L42) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0005) |
| [B0006 · 43–43](../../../../../tests/unit/physical_runtime_exception_test.cpp#L43) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 44–44](../../../../../tests/unit/physical_runtime_exception_test.cpp#L44) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0007) |
| [B0008 · 45–45](../../../../../tests/unit/physical_runtime_exception_test.cpp#L45) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0008) |
| [B0009 · 46–46](../../../../../tests/unit/physical_runtime_exception_test.cpp#L46) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0009) |
| [B0010 · 47–47](../../../../../tests/unit/physical_runtime_exception_test.cpp#L47) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0010) |
| [B0011 · 48–57](../../../../../tests/unit/physical_runtime_exception_test.cpp#L48) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;PhysicalRuntime::PendingUpdate&gt;); · [reviewed contract](#b0011) |
| [B0012 · 58–60](../../../../../tests/unit/physical_runtime_exception_test.cpp#L58) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0012) |
| [B0013 · 61–61](../../../../../tests/unit/physical_runtime_exception_test.cpp#L61) | Explanatory comments or spacing. |  |
| [B0014 · 62–62](../../../../../tests/unit/physical_runtime_exception_test.cpp#L62) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0014) |
| [B0015 · 63–63](../../../../../tests/unit/physical_runtime_exception_test.cpp#L63) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0015) |
| [B0016 · 64–64](../../../../../tests/unit/physical_runtime_exception_test.cpp#L64) | Explanatory comments or spacing. |  |
| [B0017 · 65–68](../../../../../tests/unit/physical_runtime_exception_test.cpp#L65) | Callable definition: const Row& row_a() | calls n, s; returns value · [reviewed contract](#b0017) |
| [B0018 · 69–72](../../../../../tests/unit/physical_runtime_exception_test.cpp#L69) | Callable definition: const Row& row_b() | calls n, s; returns value · [reviewed contract](#b0018) |
| [B0019 · 73–76](../../../../../tests/unit/physical_runtime_exception_test.cpp#L73) | Callable definition: const Row& row_c() | calls n, s; returns value · [reviewed contract](#b0019) |
| [B0020 · 77–77](../../../../../tests/unit/physical_runtime_exception_test.cpp#L77) | Explanatory comments or spacing. |  |
| [B0021 · 78–91](../../../../../tests/unit/physical_runtime_exception_test.cpp#L78) | Callable definition: PhysicalPlan make_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0021) |
| [B0022 · 92–92](../../../../../tests/unit/physical_runtime_exception_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0023 · 93–97](../../../../../tests/unit/physical_runtime_exception_test.cpp#L93) | Callable definition: PhysicalRuntimeOptions options() | calls ; returns result · [reviewed contract](#b0023) |
| [B0024 · 98–98](../../../../../tests/unit/physical_runtime_exception_test.cpp#L98) | Explanatory comments or spacing. |  |
| [B0025 · 99–100](../../../../../tests/unit/physical_runtime_exception_test.cpp#L99) | Type/record definition: enum class Scenario |  · [reviewed contract](#b0025) |
| [B0026 · 101–101](../../../../../tests/unit/physical_runtime_exception_test.cpp#L101) | Explanatory comments or spacing. |  |
| [B0027 · 102–106](../../../../../tests/unit/physical_runtime_exception_test.cpp#L102) | Callable definition: SetOperation operation(Scenario scenario) | calls ; returns scenario == Scenario::insert_new_projection \|\| scenario == Scenario::insert_existing_projection; growth insert · [reviewed contract](#b0027) |
| [B0028 · 107–107](../../../../../tests/unit/physical_runtime_exception_test.cpp#L107) | Explanatory comments or spacing. |  |
| [B0029 · 108–112](../../../../../tests/unit/physical_runtime_exception_test.cpp#L108) | Callable definition: PhysicalSetUpdate target_update(const PhysicalRuntime& runtime, Scenario scenario) | calls row_c, row_a, row_b, sequence; returns {runtime.sequence() + 1, TableId{0}, operation(scenario), values} · [reviewed contract](#b0029) |
| [B0030 · 113–113](../../../../../tests/unit/physical_runtime_exception_test.cpp#L113) | Explanatory comments or spacing. |  |
| [B0031 · 114–125](../../../../../tests/unit/physical_runtime_exception_test.cpp#L114) | Callable definition: io::Json normalized_owners(io::Json value) | calls is_object, contains, items, self; returns value; 2 loop sites · [reviewed contract](#b0031) |
| [B0032 · 126–126](../../../../../tests/unit/physical_runtime_exception_test.cpp#L126) | Explanatory comments or spacing. |  |
| [B0033 · 127–131](../../../../../tests/unit/physical_runtime_exception_test.cpp#L127) | Callable definition: io::Json row_json(const Row& values) | calls io::Json::array, push_back, io::write_scalar; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0033) |
| [B0034 · 132–132](../../../../../tests/unit/physical_runtime_exception_test.cpp#L132) | Explanatory comments or spacing. |  |
| [B0035 · 133–135](../../../../../tests/unit/physical_runtime_exception_test.cpp#L133) | Callable definition: std::string operation_name(SetOperation operation_value) | calls ; returns operation_value == SetOperation::insert ? @ : @; growth insert · [reviewed contract](#b0035) |
| [B0036 · 136–136](../../../../../tests/unit/physical_runtime_exception_test.cpp#L136) | Explanatory comments or spacing. |  |
| [B0037 · 137–159](../../../../../tests/unit/physical_runtime_exception_test.cpp#L137) | Callable definition: io::Json preview_image(const PhysicalPreview& preview) | calls io::Json::array, push_back, row_json, crown::storage::export_row; returns {{@ , preview.sequence}, {@ , preview.table.value},; growth push_back; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 160–160](../../../../../tests/unit/physical_runtime_exception_test.cpp#L160) | Explanatory comments or spacing. |  |
| [B0039 · 161–164](../../../../../tests/unit/physical_runtime_exception_test.cpp#L161) | Callable definition: io::Json epoch_image(const PhysicalEpoch& epoch) | calls preview_image, normalized_owners, io::write_support_epoch; returns {{@ , preview_image(epoch.input)}, · [reviewed contract](#b0039) |
| [B0040 · 165–165](../../../../../tests/unit/physical_runtime_exception_test.cpp#L165) | Explanatory comments or spacing. |  |
| [B0041 · 166–170](../../../../../tests/unit/physical_runtime_exception_test.cpp#L166) | Type/record definition: struct DerivationImage |  · [reviewed contract](#b0041) |
| [B0042 · 171–180](../../../../../tests/unit/physical_runtime_exception_test.cpp#L171) | Type/record definition: struct SnapshotImage | returns sequence == other.sequence && physical == other.physical && support == other.support && · [reviewed contract](#b0042) |
| [B0043 · 181–181](../../../../../tests/unit/physical_runtime_exception_test.cpp#L181) | Explanatory comments or spacing. |  |
| [B0044 · 182–192](../../../../../tests/unit/physical_runtime_exception_test.cpp#L182) | Callable definition: SnapshotImage snapshot_image(const PhysicalRuntime& runtime) | calls snapshot, normalized_owners, io::write_support_snapshot, plan; returns result; growth push_back, resize; 2 loop sites · [reviewed contract](#b0044) |
| [B0045 · 193–193](../../../../../tests/unit/physical_runtime_exception_test.cpp#L193) | Explanatory comments or spacing. |  |
| [B0046 · 194–199](../../../../../tests/unit/physical_runtime_exception_test.cpp#L194) | Type/record definition: struct SourceHandleImage |  · [reviewed contract](#b0046) |
| [B0047 · 200–204](../../../../../tests/unit/physical_runtime_exception_test.cpp#L200) | Type/record definition: struct SupportHandleImage |  · [reviewed contract](#b0047) |
| [B0048 · 205–209](../../../../../tests/unit/physical_runtime_exception_test.cpp#L205) | Type/record definition: struct PublicHandles |  · [reviewed contract](#b0048) |
| [B0049 · 210–210](../../../../../tests/unit/physical_runtime_exception_test.cpp#L210) | Explanatory comments or spacing. |  |
| [B0050 · 211–242](../../../../../tests/unit/physical_runtime_exception_test.cpp#L211) | Callable definition: PublicHandles public_handles(const PhysicalRuntime& runtime) | calls snapshot, size, find_source, check; guard check(handle.has_value(), "source snapshot row has no public source handle");; returns result; growth push_back; 7 loop sites · [reviewed contract](#b0050) |
| [B0051 · 243–243](../../../../../tests/unit/physical_runtime_exception_test.cpp#L243) | Explanatory comments or spacing. |  |
| [B0052 · 244–261](../../../../../tests/unit/physical_runtime_exception_test.cpp#L244) | Type/record definition: struct HeldEpoch | guard check(epoch.input.source.has_value(), "fixture commit did not retain its full source row");; growth push_back; 1 loop sites · [reviewed contract](#b0052) |
| [B0053 · 262–263](../../../../../tests/unit/physical_runtime_exception_test.cpp#L262) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0053) |
| [B0054 · 264–277](../../../../../tests/unit/physical_runtime_exception_test.cpp#L264) | Callable definition: void check_held(const HeldEpochs& held, const std::string& context) | calls check, handle, tuple, values; guard check(image.epoch.input.source && image.epoch.input.source-&gt;handle == image.source_handle &&; growth push_back; 2 loop sites · [reviewed contract](#b0054) |
| [B0055 · 278–278](../../../../../tests/unit/physical_runtime_exception_test.cpp#L278) | Explanatory comments or spacing. |  |
| [B0056 · 279–279](../../../../../tests/unit/physical_runtime_exception_test.cpp#L279) | Callable definition: void hold(HeldEpochs& held, PhysicalEpoch epoch) | calls emplace_back, std::move; growth emplace_back · [reviewed contract](#b0056) |
| [B0057 · 280–280](../../../../../tests/unit/physical_runtime_exception_test.cpp#L280) | Explanatory comments or spacing. |  |
| [B0058 · 281–295](../../../../../tests/unit/physical_runtime_exception_test.cpp#L281) | Callable definition: std::uint64_t initialize(PhysicalRuntime& runtime, Scenario scenario, HeldEpochs& held) | calls hold, apply, row_a, row_b; guard check(runtime.derivation_count(OccurrenceId{0}, Row{n(10), n(1)}) == expected_count &&; returns runtime.sequence(); growth insert · [reviewed contract](#b0058) |
| [B0059 · 296–296](../../../../../tests/unit/physical_runtime_exception_test.cpp#L296) | Explanatory comments or spacing. |  |
| [B0060 · 297–307](../../../../../tests/unit/physical_runtime_exception_test.cpp#L297) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, "unexpected error code: expected " + std::string(code) + · [reviewed contract](#b0060) |
| [B0061 · 308–308](../../../../../tests/unit/physical_runtime_exception_test.cpp#L308) | Explanatory comments or spacing. |  |
| [B0062 · 309–324](../../../../../tests/unit/physical_runtime_exception_test.cpp#L309) | Callable definition: void check_rollback_statistics(const PhysicalStorageStatistics& before, const PhysicalStorageStatistics& after, const std::string… | calls check, std::string, check_arena; guard check(old_stats.live_records == new_stats.live_records && · [reviewed contract](#b0062) |
| [B0063 · 325–325](../../../../../tests/unit/physical_runtime_exception_test.cpp#L325) | Explanatory comments or spacing. |  |
| [B0064 · 326–337](../../../../../tests/unit/physical_runtime_exception_test.cpp#L326) | Callable definition: void check_unchanged(PhysicalRuntime& runtime, const SnapshotImage& before, const PublicHandles& handles, const PhysicalStorageSt… | calls check, ready, sequence, has_answer; guard check(runtime.ready() && runtime.sequence() == sequence && runtime.has_answer() == answer && runtim… · [reviewed contract](#b0064) |
| [B0065 · 338–338](../../../../../tests/unit/physical_runtime_exception_test.cpp#L338) | Explanatory comments or spacing. |  |
| [B0066 · 339–360](../../../../../tests/unit/physical_runtime_exception_test.cpp#L339) | Callable definition: void check_busy_readers(PhysicalRuntime& runtime, const PhysicalRuntime::PendingUpdate& pending, std::uint64_t sequence, const Pu… | calls check, ready, sequence, preview; guard check(!runtime.ready() && runtime.sequence() == sequence, · [reviewed contract](#b0066) |
| [B0067 · 361–361](../../../../../tests/unit/physical_runtime_exception_test.cpp#L361) | Explanatory comments or spacing. |  |
| [B0068 · 362–365](../../../../../tests/unit/physical_runtime_exception_test.cpp#L362) | Type/record definition: struct ExpectedResult |  · [reviewed contract](#b0068) |
| [B0069 · 366–366](../../../../../tests/unit/physical_runtime_exception_test.cpp#L366) | Explanatory comments or spacing. |  |
| [B0070 · 367–393](../../../../../tests/unit/physical_runtime_exception_test.cpp#L367) | Callable definition: ExpectedResult clean_result(const PhysicalPlan& plan, Scenario scenario) | calls options, initialize, apply, target_update; guard check(epoch.input.physical_changed && epoch.input.source && epoch.input.derivations.size() == 2,; returns {snapshot_image(runtime), epoch_image(epoch)}; 1 loop sites · [reviewed contract](#b0070) |
| [B0071 · 394–394](../../../../../tests/unit/physical_runtime_exception_test.cpp#L394) | Explanatory comments or spacing. |  |
| [B0072 · 395–399](../../../../../tests/unit/physical_runtime_exception_test.cpp#L395) | Type/record definition: struct SweepResult |  · [reviewed contract](#b0072) |
| [B0073 · 400–400](../../../../../tests/unit/physical_runtime_exception_test.cpp#L400) | Explanatory comments or spacing. |  |
| [B0074 · 401–464](../../../../../tests/unit/physical_runtime_exception_test.cpp#L401) | Callable definition: SweepResult sweep(const PhysicalPlan& plan, Scenario scenario) | calls clean_result, options, initialize, snapshot_image; guard check(failed_during_prepare && !failed_during_commit,; returns counts; growth emplace; 1 loop sites; source comment (unverified): // Keep failure armed while any returned token unwinds. · [reviewed contract](#b0074) |
| [B0075 · 465–465](../../../../../tests/unit/physical_runtime_exception_test.cpp#L465) | Explanatory comments or spacing. |  |
| [B0076 · 466–485](../../../../../tests/unit/physical_runtime_exception_test.cpp#L466) | Callable definition: void check_explicit_rollback_is_noalloc(const PhysicalPlan& plan) | calls options, initialize, snapshot_image, public_handles; guard check(!pending.active(), "explicit physical rollback left its token active"); · [reviewed contract](#b0076) |
| [B0077 · 486–486](../../../../../tests/unit/physical_runtime_exception_test.cpp#L486) | Explanatory comments or spacing. |  |
| [B0078 · 487–508](../../../../../tests/unit/physical_runtime_exception_test.cpp#L487) | Callable definition: void check_destructor_cancellation_is_noalloc(const PhysicalPlan& plan) | calls options, initialize, snapshot_image, public_handles; guard check(remained_active, "destructor fixture did not prepare an active physical update"); · [reviewed contract](#b0078) |
| [B0079 · 509–509](../../../../../tests/unit/physical_runtime_exception_test.cpp#L509) | Explanatory comments or spacing. |  |
| [B0080 · 510–546](../../../../../tests/unit/physical_runtime_exception_test.cpp#L510) | Callable definition: void check_move_assignment_is_noalloc(const PhysicalPlan& plan) | calls options, initialize, snapshot_image, public_handles; guard check(transferred, "physical pending move assignment did not transfer its active token"); · [reviewed contract](#b0080) |
| [B0081 · 547–547](../../../../../tests/unit/physical_runtime_exception_test.cpp#L547) | Explanatory comments or spacing. |  |
| [B0082 · 548–565](../../../../../tests/unit/physical_runtime_exception_test.cpp#L548) | Callable definition: void check_facade_destruction_with_active_update(const PhysicalPlan& plan) | calls options, initialize, emplace, prepare; guard check(pending-&gt;active(), "facade-destruction fixture did not retain an active physical update");; growth emplace · [reviewed contract](#b0082) |
| [B0083 · 566–566](../../../../../tests/unit/physical_runtime_exception_test.cpp#L566) | Explanatory comments or spacing. |  |
| [B0084 · 567–590](../../../../../tests/unit/physical_runtime_exception_test.cpp#L567) | Callable definition: void check_commit_after_facade_destruction_is_noalloc(const PhysicalPlan& plan) | calls options, initialize, emplace, prepare; guard check(output.has_value() && closed,; growth emplace, emplace_back · [reviewed contract](#b0084) |
| [B0085 · 591–591](../../../../../tests/unit/physical_runtime_exception_test.cpp#L591) | Explanatory comments or spacing. |  |
| [B0086 · 592–610](../../../../../tests/unit/physical_runtime_exception_test.cpp#L592) | Callable definition: void check_commit_is_noalloc(const PhysicalPlan& plan) | calls options, initialize, clean_result, prepare; guard check(output && !pending.active() && runtime.ready(), "no-allocation physical commit did not close …; growth emplace · [reviewed contract](#b0086) |
| [B0087 · 611–611](../../../../../tests/unit/physical_runtime_exception_test.cpp#L611) | Explanatory comments or spacing. |  |
| [B0088 · 612–656](../../../../../tests/unit/physical_runtime_exception_test.cpp#L612) | Callable definition: void check_staged_output_exception_cancels(const PhysicalPlan& plan, Scenario scenario) | calls options, initialize, snapshot_image, public_handles; guard check(output_failed && pending.active() && !runtime.ready() && runtime.sequence() == sequence,; source comment (unverified): // This models a caller building its private output before commit. The · [reviewed contract](#b0088) |
| [B0089 · 657–659](../../../../../tests/unit/physical_runtime_exception_test.cpp#L657) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0089) |
| [B0090 · 660–691](../../../../../tests/unit/physical_runtime_exception_test.cpp#L660) | Callable definition: int main() | calls make_plan, check_explicit_rollback_is_noalloc, check_destructor_cancellation_is_noalloc, check_move_assignment_is_noalloc; guard check(insert_new.prepare_failures &gt; 0 && erase_last.prepare_failures &gt; 0 &&; returns 1 · [reviewed contract](#b0090) |

## B0001

[Lines 1–24](../../../../../tests/unit/physical_runtime_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L24:sha256:7dfbb9ef12d2e6b217af0704614d0869b7fae1078d7bf3c064049a324afa49bf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_runtime_exception_test.cpp: include "crown/api/error.hpp", "crown/io/document.hpp", "crown/io/support.hpp", "crown/planner/lower.hpp", "crown/runtime/physical.hpp", &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 25–32](../../../../../tests/unit/physical_runtime_exception_test.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the physical-test malloc-backed ordinary-new failure position. |
| inputs / outputs | A byte count enters; selected zero throws bad_alloc, positive positions decrement, and admitted requests return malloc(bytes or 1). |
| invariants | Only fail_after exists; unlike the batch/window executable this seam has no allocation counter. |
| ownership | The seam mutates one thread-local fail_after value; successful malloc storage is returned to the C++ caller and freed by replacement delete. |
| failure | Only ordinary global scalar/array new is replaced. Raw malloc/realloc, aligned/nothrow allocation, account-admission denial, and system calls are not intercepted. |
| cost | One thread-local index branch/decrement and at most one malloc attempt. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0003

[Lines 33–39](../../../../../tests/unit/physical_runtime_exception_test.cpp#L33); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set and reset the physical-test ordinary-new failure scope. |
| inputs / outputs | Optional step enters; constructor writes fail_after, destructor restores -1, and forbid_allocations() writes zero. |
| invariants | Copy/assignment are deleted; nested prior fail state is not restored. |
| ownership | Borrows and changes only the executable-local thread-local fail_after scalar; owns no runtime, pending token, or storage result. |
| failure | Construction selects a step, destruction disables injection by setting -1, and forbid_allocations() sets zero. It is not nesting-aware and catches no exception. |
| cost | Constant scalar bookkeeping with no allocation counter. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0004

[Lines 40–41](../../../../../tests/unit/physical_runtime_exception_test.cpp#L40); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L41:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in physical_runtime_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 42–42](../../../../../tests/unit/physical_runtime_exception_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch scalar ordinary operator new through malloc_new. |
| inputs / outputs | A size enters; malloc_new returns malloc-backed storage or throws std::bad_alloc. |
| invariants | Both ordinary overloads consume the same thread-local fail_after position. |
| ownership | The test executable owns only thread-local fail_after. A successful replacement request returns malloc-backed storage to its caller; the matching replacement delete releases it. |
| failure | A selected fail_after position throws std::bad_alloc at ordinary global operator new or operator new\[\]; a null std::malloc result also throws. The harness does not replace aligned or nothrow overloads and does not inject raw malloc/realloc, system-call, or MemoryAccount admission failures. Accounted allocations are intercepted only if admission succeeds and execution reaches one of these replaced ordinary new overloads. |
| cost | One thread-local index check and, when admitted, one std::malloc attempt. Fault positions count intercepted C++ allocation calls, not requested bytes, account charges, RSS, abstract work, or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0006

[Lines 43–43](../../../../../tests/unit/physical_runtime_exception_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch array ordinary operator new\[\] through malloc_new. |
| inputs / outputs | A size enters; malloc_new returns malloc-backed storage or throws std::bad_alloc. |
| invariants | Both ordinary overloads consume the same thread-local fail_after position. |
| ownership | The test executable owns only thread-local fail_after. A successful replacement request returns malloc-backed storage to its caller; the matching replacement delete releases it. |
| failure | A selected fail_after position throws std::bad_alloc at ordinary global operator new or operator new\[\]; a null std::malloc result also throws. The harness does not replace aligned or nothrow overloads and does not inject raw malloc/realloc, system-call, or MemoryAccount admission failures. Accounted allocations are intercepted only if admission succeeds and execution reaches one of these replaced ordinary new overloads. |
| cost | One thread-local index check and, when admitted, one std::malloc attempt. Fault positions count intercepted C++ allocation calls, not requested bytes, account charges, RSS, abstract work, or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0007

[Lines 44–44](../../../../../tests/unit/physical_runtime_exception_test.cpp#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage through scalar unsized delete. |
| inputs / outputs | A compatible replacement-new pointer enters; no value exits. |
| invariants | The overload calls std::free and does not alter fail_after. |
| ownership | The pointer is borrowed during the call and released here; it must be compatible malloc-backed replacement storage. |
| failure | Delete itself is not injected; only ordinary scalar/array sized and unsized forms are supplied. |
| cost | One std::free call. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0008

[Lines 45–45](../../../../../tests/unit/physical_runtime_exception_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage through array unsized delete. |
| inputs / outputs | A compatible replacement-new pointer enters; no value exits. |
| invariants | The overload calls std::free and does not alter fail_after. |
| ownership | The pointer is borrowed during the call and released here; it must be compatible malloc-backed replacement storage. |
| failure | Delete itself is not injected; only ordinary scalar/array sized and unsized forms are supplied. |
| cost | One std::free call. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0009

[Lines 46–46](../../../../../tests/unit/physical_runtime_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage through scalar sized delete. |
| inputs / outputs | A compatible replacement-new pointer enters; no value exits. |
| invariants | The overload calls std::free and does not alter fail_after. |
| ownership | The pointer is borrowed during the call and released here; it must be compatible malloc-backed replacement storage. |
| failure | Delete itself is not injected; only ordinary scalar/array sized and unsized forms are supplied. |
| cost | One std::free call. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0010

[Lines 47–47](../../../../../tests/unit/physical_runtime_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release storage through array sized delete. |
| inputs / outputs | A compatible replacement-new pointer enters; no value exits. |
| invariants | The overload calls std::free and does not alter fail_after. |
| ownership | The pointer is borrowed during the call and released here; it must be compatible malloc-backed replacement storage. |
| failure | Delete itself is not injected; only ordinary scalar/array sized and unsized forms are supplied. |
| cost | One std::free call. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0011

[Lines 48–57](../../../../../tests/unit/physical_runtime_exception_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L57:sha256:fa31a9a6de131e8fb922dd8ac6dff6d43b0d5f639bd955ad2a84e77e801c7462
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_runtime_exception_test.cpp: bind local aliases/name imports; require 4 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 58–60](../../../../../tests/unit/physical_runtime_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a false assertion into a test runtime_error. |
| inputs / outputs | Bool and diagnostic string enter; true returns and false throws. |
| invariants | No crown error is caught or translated. |
| ownership | Arguments are borrowed; a constructed message becomes owned by a thrown std::runtime_error. |
| failure | False conditions throw std::runtime_error. No engine/API error is caught or translated. |
| cost | One predicate branch and failure-only message construction. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp) |

## B0014

[Lines 62–62](../../../../../tests/unit/physical_runtime_exception_test.cpp#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an integer fixture in Value. |
| inputs / outputs | An int64 enters by value; integer Value exits. |
| invariants | No view into the argument escapes. |
| ownership | Returned Value/PhysicalPlan/options own their copied fixture data; the source catalog/query/tree are locals consumed by lower_tree. |
| failure | Plan lowering, variant/string copying, and allocation errors propagate; fixture helpers install no fault scope. |
| cost | Builds one fixed three-column/two-occurrence plan or option object. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0015

[Lines 63–63](../../../../../tests/unit/physical_runtime_exception_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a string fixture in an owning Value. |
| inputs / outputs | An owning std::string enters by value; string Value exits. |
| invariants | Returned variant owns/moves the string contents. |
| ownership | Returned Value/PhysicalPlan/options own their copied fixture data; the source catalog/query/tree are locals consumed by lower_tree. |
| failure | Plan lowering, variant/string copying, and allocation errors propagate; fixture helpers install no fault scope. |
| cost | Builds one fixed three-column/two-occurrence plan or option object. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0017

[Lines 65–68](../../../../../tests/unit/physical_runtime_exception_test.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& row_a() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the process-static physical source row A (10,1,"source-row-a"). |
| inputs / outputs | No input; const Row& to the static fixture value exits. |
| invariants | The function-static row owns its values for process lifetime; witness differs for A/B and C uses y=2. |
| ownership | Each function-static const Row owns its Value members for process lifetime. Callers borrow a const reference; the reference is never to a temporary. |
| failure | First static initialization can propagate allocation failure; the accessor catches nothing and installs no injector. |
| cost | One fixed three-field row at first initialization, then a static reference return. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0018

[Lines 69–72](../../../../../tests/unit/physical_runtime_exception_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& row_b() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the process-static physical source row B (10,1,"source-row-b"). |
| inputs / outputs | No input; const Row& to the static fixture value exits. |
| invariants | The function-static row owns its values for process lifetime; witness differs for A/B and C uses y=2. |
| ownership | Each function-static const Row owns its Value members for process lifetime. Callers borrow a const reference; the reference is never to a temporary. |
| failure | First static initialization can propagate allocation failure; the accessor catches nothing and installs no injector. |
| cost | One fixed three-field row at first initialization, then a static reference return. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0019

[Lines 73–76](../../../../../tests/unit/physical_runtime_exception_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Row& row_c() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the process-static physical source row C (10,2,"source-row-c"). |
| inputs / outputs | No input; const Row& to the static fixture value exits. |
| invariants | The function-static row owns its values for process lifetime; witness differs for A/B and C uses y=2. |
| ownership | Each function-static const Row owns its Value members for process lifetime. Callers borrow a const reference; the reference is never to a temporary. |
| failure | First static initialization can propagate allocation failure; the accessor catches nothing and installs no injector. |
| cost | One fixed three-field row at first initialization, then a static reference return. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0021

[Lines 78–91](../../../../../tests/unit/physical_runtime_exception_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the fixed same-table two-alias physical plan. |
| inputs / outputs | No input; catalog R(x,y,witness), query aliases left/right with ignored witness columns, x/y output, and generalized/native tree enter lower_tree; PhysicalPlan exits. |
| invariants | Both native occurrences read table 0 and project x,y; witness is full source identity but not projected. |
| ownership | Returned Value/PhysicalPlan/options own their copied fixture data; the source catalog/query/tree are locals consumed by lower_tree. |
| failure | Plan lowering, variant/string copying, and allocation errors propagate; fixture helpers install no fault scope. |
| cost | Builds one fixed three-column/two-occurrence plan or option object. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0023

[Lines 93–97](../../../../../tests/unit/physical_runtime_exception_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable support transition capture for physical runtime fixtures. |
| inputs / outputs | No input; PhysicalRuntimeOptions exits with support.capture_transitions=true. |
| invariants | Other support/physical options remain defaults. |
| ownership | Returned Value/PhysicalPlan/options own their copied fixture data; the source catalog/query/tree are locals consumed by lower_tree. |
| failure | Plan lowering, variant/string copying, and allocation errors propagate; fixture helpers install no fault scope. |
| cost | Builds one fixed three-column/two-occurrence plan or option object. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp) |

## B0025

[Lines 99–100](../../../../../tests/unit/physical_runtime_exception_test.cpp#L99); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Scenario { insert_new_projection, erase_last_projection, insert_existing_projection,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the four full-row insertion/erasure scenarios. |
| inputs / outputs | No input; Scenario value names new projection insert, last projection erase, existing projection insert, or shared projection erase. |
| invariants | The scenarios distinguish projection zero-crossings from changes in full source-row identity. |
| ownership | Returned Value/PhysicalPlan/options own their copied fixture data; the source catalog/query/tree are locals consumed by lower_tree. |
| failure | Plan lowering, variant/string copying, and allocation errors propagate; fixture helpers install no fault scope. |
| cost | Builds one fixed three-column/two-occurrence plan or option object. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0027

[Lines 102–106](../../../../../tests/unit/physical_runtime_exception_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SetOperation operation(Scenario scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map projection scenarios to source set operation. |
| inputs / outputs | Scenario enters; insert for insert_new/insert_existing, erase for erase_last/erase_shared. |
| invariants | The enum’s two insert and two erase cases are exhaustive in this expression. |
| ownership | Returned Value/PhysicalPlan/options own their copied fixture data; the source catalog/query/tree are locals consumed by lower_tree. |
| failure | Plan lowering, variant/string copying, and allocation errors propagate; fixture helpers install no fault scope. |
| cost | Builds one fixed three-column/two-occurrence plan or option object. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0029

[Lines 108–112](../../../../../tests/unit/physical_runtime_exception_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate target_update(const PhysicalRuntime& runtime, Scenario scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the next full-source-row update for one physical scenario. |
| inputs / outputs | Runtime and scenario are borrowed; returns sequence runtime.sequence()+1, table 0, mapped operation, and row C/A/B according to case. |
| invariants | Insert-existing and erase-shared both use B (same projected x/y as A but distinct witness); erase-last uses A. Returned PhysicalSetUpdate owns its Row copy. |
| ownership | Borrows runtime only for sequence(); returned PhysicalSetUpdate owns its Row values, copied from process-static fixture rows. |
| failure | Plan lowering, variant/string copying, and allocation errors propagate; fixture helpers install no fault scope. |
| cost | Builds one fixed three-column/two-occurrence plan or option object. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0031

[Lines 114–125](../../../../../tests/unit/physical_runtime_exception_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json normalized_owners(io::Json value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize owner fields recursively in a JSON diagnostic value. |
| inputs / outputs | JSON enters by value; every object member named owner at any nesting is replaced with integer zero; owning JSON exits. |
| invariants | Other fields, including relation/tuple IDs and array order, are preserved. |
| ownership | Inputs are borrowed or passed as owned JSON by value as specified; returned JSON/string owns its serialized contents and does not retain runtime references. |
| failure | JSON/string/vector allocations and scalar serialization errors propagate; these formatters catch no product error. |
| cost | Walks or serializes only the supplied small preview/result image; output construction cost is not PhysicalMetrics.work or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0033

[Lines 127–131](../../../../../tests/unit/physical_runtime_exception_test.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json row_json(const Row& values) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one Row as a JSON array of scalar images. |
| inputs / outputs | Row is borrowed; array with one write_scalar result per field exits. |
| invariants | Field ordering and values follow the source row. |
| ownership | Inputs are borrowed or passed as owned JSON by value as specified; returned JSON/string owns its serialized contents and does not retain runtime references. |
| failure | JSON/string/vector allocations and scalar serialization errors propagate; these formatters catch no product error. |
| cost | Walks or serializes only the supplied small preview/result image; output construction cost is not PhysicalMetrics.work or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/io/document.hpp](../../../../../include/crown/io/document.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0035

[Lines 133–135](../../../../../tests/unit/physical_runtime_exception_test.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string operation_name(SetOperation operation_value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map SetOperation to its diagnostic string. |
| inputs / outputs | A SetOperation enters; insert maps to "insert", all other valid enum value maps to "erase". |
| invariants | No runtime state is accessed. |
| ownership | Inputs are borrowed or passed as owned JSON by value as specified; returned JSON/string owns its serialized contents and does not retain runtime references. |
| failure | JSON/string/vector allocations and scalar serialization errors propagate; these formatters catch no product error. |
| cost | Walks or serializes only the supplied small preview/result image; output construction cost is not PhysicalMetrics.work or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0037

[Lines 137–159](../../../../../tests/unit/physical_runtime_exception_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json preview_image(const PhysicalPreview& preview) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the physical preview fields used by equality oracles. |
| inputs / outputs | PhysicalPreview is borrowed; JSON includes sequence/table/operation/physical_changed, selected metrics, optional pinned source handle/tuple, and derivation occurrence/node/tuple/count-transition/native_changed images. |
| invariants | Owner in source handle is normalized to zero; metrics serialize named counters but do not measure elapsed time. |
| ownership | Inputs are borrowed or passed as owned JSON by value as specified; returned JSON/string owns its serialized contents and does not retain runtime references. |
| failure | JSON/string/vector allocations and scalar serialization errors propagate; these formatters catch no product error. |
| cost | Walks or serializes only the supplied small preview/result image; output construction cost is not PhysicalMetrics.work or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0039

[Lines 161–164](../../../../../tests/unit/physical_runtime_exception_test.cpp#L161); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Json epoch_image(const PhysicalEpoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize one returned PhysicalEpoch into normalized input/support JSON. |
| inputs / outputs | PhysicalEpoch is borrowed; preview_image(input) and write_support_epoch(support) form an owning JSON value with owner IDs normalized. |
| invariants | Only returned epoch data is encoded; this does not publish another update. |
| ownership | Inputs are borrowed or passed as owned JSON by value as specified; returned JSON/string owns its serialized contents and does not retain runtime references. |
| failure | JSON/string/vector allocations and scalar serialization errors propagate; these formatters catch no product error. |
| cost | Walks or serializes only the supplied small preview/result image; output construction cost is not PhysicalMetrics.work or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0041

[Lines 166–170](../../../../../tests/unit/physical_runtime_exception_test.cpp#L166); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DerivationImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one copied derivation row and its multiplicity. |
| inputs / outputs | Row values and uint64 count are owned by DerivationImage; default equality compares both. |
| invariants | The row is an exported diagnostic copy, not an accounted runtime tuple. |
| ownership | Value members own the image fields; equality compares stored values. Handles/IDs are scalar identity values, not owners of the referenced runtime rows. |
| failure | Member construction/copy can propagate ordinary allocation failures where fields own vectors/JSON/rows; no custom failure translation exists. |
| cost | Copies or compares only the explicit fixture image fields. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0042

[Lines 171–180](../../../../../tests/unit/physical_runtime_exception_test.cpp#L171); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SnapshotImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store sequence, physical relation rows, normalized support JSON, and derivation images. |
| inputs / outputs | SnapshotImage owns the four fields and defines equality on all of them. |
| invariants | Owner-normalized support equality ignores owner IDs only; physical rows/counts and sequence remain compared. |
| ownership | Owns physical Relation values, support JSON and copied derivation images; no runtime or accounted tuple pin is stored. |
| failure | Member construction/copy can propagate ordinary allocation failures where fields own vectors/JSON/rows; no custom failure translation exists. |
| cost | Copies or compares only the explicit fixture image fields. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0044

[Lines 182–192](../../../../../tests/unit/physical_runtime_exception_test.cpp#L182); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotImage snapshot_image(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a detached physical/logical runtime snapshot image. |
| inputs / outputs | Runtime is borrowed; snapshot() supplies sequence/physical tables/support/derivations; support JSON is normalized and each derivation tuple is exported to Row. |
| invariants | Returned image compares physical rows, support snapshot, derivation rows/counts, and sequence; it does not include public handles. |
| ownership | Borrows the runtime; PhysicalSnapshot is a detached diagnostic value during the call, and returned Row/JSON/vector fields own their copied contents. |
| failure | Snapshot/export/JSON/vector allocation errors propagate; no runtime error is caught by the oracle. |
| cost | Scans the small snapshot’s physical rows and derivation counts and serializes the logical support snapshot. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0046

[Lines 194–199](../../../../../tests/unit/physical_runtime_exception_test.cpp#L194); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceHandleImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one source table/tuple handle and copied row image. |
| inputs / outputs | TableId, TupleHandle, and Row values are fields in SourceHandleImage. |
| invariants | The scalar handle identifies runtime-owned storage but does not pin it. |
| ownership | The image owns the copied Row and scalar handle metadata. The handle identifies storage owned by a runtime but does not keep that storage alive. |
| failure | Ordinary value copy failures propagate; no stale-handle recovery is performed by this record type. |
| cost | Stores one handle identity and one copied row image. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0047

[Lines 200–204](../../../../../tests/unit/physical_runtime_exception_test.cpp#L200); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportHandleImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one support handle and copied row image. |
| inputs / outputs | SupportHandle and Row values enter by value; struct owns them. |
| invariants | The handle is an identifier only; row image is a detached exported copy. |
| ownership | The image owns the copied Row and scalar handle metadata. The handle identifies storage owned by a runtime but does not keep that storage alive. |
| failure | Ordinary value copy failures propagate; no stale-handle recovery is performed by this record type. |
| cost | Stores one handle identity and one copied row image. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0048

[Lines 205–209](../../../../../tests/unit/physical_runtime_exception_test.cpp#L205); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PublicHandles {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store exported source and support public-handle images. |
| inputs / outputs | Two vectors of handle/row image structs are fields in PublicHandles. |
| invariants | Equality compares ordered copied handle/value entries; this struct does not own referenced runtime records. |
| ownership | Owns vectors of copied public handle/row images; does not own or pin the source runtime tuples. |
| failure | Vector copies/growth may propagate ordinary allocation failure; no handle resolution is performed by the struct itself. |
| cost | Storage proportional to the explicit small source/support handle list. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0050

[Lines 211–242](../../../../../tests/unit/physical_runtime_exception_test.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PublicHandles public_handles(const PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate snapshot source/support rows and verify each public handle resolves. |
| inputs / outputs | Borrows PhysicalRuntime; source snapshot rows use find_source/get_source; support records, survivors, parent keys, and optional visible keys use find/get APIs; copied public images exit. |
| invariants | Every looked-up tuple must match complete values and support layout token; result includes all listed categories in traversal order. |
| ownership | Borrows PhysicalRuntime. The returned PublicHandles owns exported Row copies and scalar handles; AccountedTuple/ Tuple lookup results are local temporaries. |
| failure | Every snapshot row must resolve via find_source/get_source and every support record/survivor/key via public lookup; a missing/mismatched handle throws runtime_error. Runtime busy/API and allocation errors propagate. |
| cost | Visits all source rows and support record/survivor/parent/visible keys in a diagnostic snapshot and performs corresponding public handle lookups. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0052

[Lines 244–261](../../../../../tests/unit/physical_runtime_exception_test.cpp#L244); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct HeldEpoch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one committed PhysicalEpoch and snapshot its source pin and logical journal. |
| inputs / outputs | Moves a PhysicalEpoch in; stores source handle/ArenaHandle, exported source Row, normalized support JSON, and copied journal record Rows. |
| invariants | Fixture epoch must include source change; retained source pin and support journal stay alive as part of epoch. |
| ownership | HeldEpoch owns a moved PhysicalEpoch, which retains its source pin and support journal. It also owns detached source-value, JSON, and journal-row images for later comparison. |
| failure | Construction copies/serializes source and journal values and can propagate allocation/API errors; no recovery path is provided. |
| cost | Copies the source row, support JSON, and each journal record row once per retained epoch. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0053

[Lines 262–263](../../../../../tests/unit/physical_runtime_exception_test.cpp#L262); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L262-L263:sha256:6ce64e9303ae42877f61a2d828acc40f68d10d385883630006e85916763ca6a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical_runtime_exception_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0054

[Lines 264–277](../../../../../tests/unit/physical_runtime_exception_test.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_held(const HeldEpochs& held, const std::string& context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify held committed source pins and logical journal contents are unchanged. |
| inputs / outputs | Borrows HeldEpochs and context string; re-reads each retained source tuple, serialized logical epoch, and journal rows. |
| invariants | Handle/pin/value, normalized logical JSON, and journal row sequence must exactly match saved images. |
| ownership | Borrows the held epoch vector and its retained PhysicalEpoch pins/journals; comparison rows/JSON are temporary detached values. |
| failure | Any lost source pin, changed source row, changed normalized support journal, or changed journal record values throws runtime_error. |
| cost | Serializes and walks every held epoch and journal record; fixture size only, not a runtime work/CPU bound. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0056

[Lines 279–279](../../../../../tests/unit/physical_runtime_exception_test.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void hold(HeldEpochs& held, PhysicalEpoch epoch) { held.emplace_back(std::move(epoch)); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move a committed epoch into the held-owner vector. |
| inputs / outputs | HeldEpochs is borrowed mutably; PhysicalEpoch is consumed by value and moved into vector. |
| invariants | The vector now retains the epoch’s source pin and support journal. |
| ownership | Moves the supplied epoch into the caller-owned HeldEpochs vector; vector growth and HeldEpoch construction retain the epoch/source/journal owners. |
| failure | Allocation or HeldEpoch copy/serialization errors propagate; no catch occurs here. |
| cost | One epoch append plus retained diagnostic images for its source and journal. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0058

[Lines 281–295](../../../../../tests/unit/physical_runtime_exception_test.cpp#L281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t initialize(PhysicalRuntime& runtime, Scenario scenario, HeldEpochs& held) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed one PhysicalRuntime according to a selected projection scenario. |
| inputs / outputs | Borrows runtime and HeldEpochs; applies A, optionally B, and optionally an erase of B, retaining each returned epoch. |
| invariants | Checks expected two-alias projection count for (10,1), runtime invariants, held epochs, and returns current sequence. |
| ownership | Borrows a PhysicalRuntime and appends returned PhysicalEpoch owners into the caller-owned HeldEpochs. Static rows are borrowed; \`apply\` imports runtime ownership before returning. |
| failure | Setup apply/oracle errors propagate before a fault scope; mismatched projected counts or invariants throw runtime_error. |
| cost | Applies two or three fixed seed source updates according to the scenario, then checks the resulting small runtime. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0060

[Lines 297–307](../../../../../tests/unit/physical_runtime_exception_test.cpp#L297); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a crown::api::Error with an exact error code. |
| inputs / outputs | Forwarded action and expected string_view enter; a matching Error returns normally. |
| invariants | Wrong code/no Error fail via runtime_error; non-crown exceptions propagate. |
| ownership | Borrows an action for its duration; no error or result is retained. |
| failure | Returns only when the action throws crown::api::Error with the exact requested code; wrong code or no Error throws runtime_error. std::bad_alloc is not accepted as the expected product error. |
| cost | One action invocation and error-code comparison. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0062

[Lines 309–324](../../../../../tests/unit/physical_runtime_exception_test.cpp#L309); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_rollback_statistics(const PhysicalStorageStatistics& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare physical arena rollback counters without requiring slot shrinkage. |
| inputs / outputs | Before/after PhysicalStorageStatistics and context enter by const reference. |
| invariants | Source/support live_records, retained_records and pins must match; new slots may stay at or above old high-water slots; derivation_keys must match. |
| ownership | Statistics arguments are borrowed snapshots by const reference; no runtime or arena state is owned. |
| failure | Throws runtime_error unless live/retained/pin counts match, high-water slots have not decreased, and derivation-key count is unchanged. It intentionally does not require high-water slots to roll back. |
| cost | Compares fixed arena counters and one key count; does not measure bytes or CPU time. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0064

[Lines 326–337](../../../../../tests/unit/physical_runtime_exception_test.cpp#L326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_unchanged(PhysicalRuntime& runtime, const SnapshotImage& before,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a failed physical update left runtime and public state unchanged. |
| inputs / outputs | Borrows runtime plus saved SnapshotImage, PublicHandles, stats, sequence, answer, owner, held epochs, and context. |
| invariants | Checks ready/sequence/answer/owner, image, handles, rollback counters, old held epochs, and check_invariants. |
| ownership | Borrows the runtime, detached before-image/handles/stats, and HeldEpoch pin set; snapshots created for comparison are temporary owned values. |
| failure | Throws runtime_error if readiness/sequence/answer/owner, snapshot, public handles, arena counters, held journals, or invariants differ from the committed baseline. |
| cost | Performs a full small test snapshot/handle/invariant comparison and walks held epochs; no timing/work bound. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0066

[Lines 339–360](../../../../../tests/unit/physical_runtime_exception_test.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_busy_readers(PhysicalRuntime& runtime, const PhysicalRuntime::PendingUpdate& pending,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pending physical preview and reject the named public readers while busy. |
| inputs / outputs | Borrows runtime, active PendingUpdate, pre-update sequence and PublicHandles. Reads preview/pending snapshot and invokes named getters. |
| invariants | Preview must describe changed source plus two aliases; tentative snapshot sequence is +1, facade sequence remains old/not ready; listed answer/snapshot/derivation/handle/stats/invariant readers throw runtime_busy. |
| ownership | Borrows runtime, active pending token, and saved public handles. Preview reference and pending snapshot are used only while that token remains active. |
| failure | Requires unpublished sequence/readiness, physical preview/source/two alias changes, and tentative snapshot sequence; verifies the named read APIs each throw runtime_busy while pending. This list does not imply every public API was tested. |
| cost | Reads one preview/snapshot and invokes a fixed list of guarded getters; no resource or CPU limit is asserted. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0068

[Lines 362–365](../../../../../tests/unit/physical_runtime_exception_test.cpp#L362); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExpectedResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store detached clean-result snapshot and epoch images. |
| inputs / outputs | SnapshotImage and JSON epoch are owned fields of ExpectedResult. |
| invariants | No runtime/token reference is retained. |
| ownership | Owns a detached SnapshotImage and JSON epoch image. |
| failure | Member construction/copy errors propagate; this aggregate performs no validation by itself. |
| cost | Stores one small physical snapshot image and one serialized epoch image. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0070

[Lines 367–393](../../../../../tests/unit/physical_runtime_exception_test.cpp#L367); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExpectedResult clean_result(const PhysicalPlan& plan, Scenario scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one unfaulted expected physical transition for a scenario. |
| inputs / outputs | Borrows plan; initializes a fresh runtime, applies target update, checks two alias derivations and expected before/after counts/native crossing, then returns detached snapshot/epoch images. |
| invariants | Checks sequence/ready, old held epochs, and invariants; returns the oracle for faulted retry comparison. |
| ownership | Borrows the plan; local PhysicalRuntime/HeldEpochs own runtime state and returned epochs until image capture. ExpectedResult owns detached images. |
| failure | Runs an unfaulted setup/apply and verifies both alias changes, native count transitions, support crossing, sequence/readiness, held epochs, and invariants. Errors propagate; this is the comparison oracle, not an injected-failure trial. |
| cost | Builds one fixed scenario, applies one target update and serializes its small before/after result. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0072

[Lines 395–399](../../../../../tests/unit/physical_runtime_exception_test.cpp#L395); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SweepResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count total, prepare, and commit bad_alloc positions. |
| inputs / outputs | Three size_t counters enter default zero; no runtime value exits. |
| invariants | Counters distinguish caught failure phase; sweep later requires prepare failures and zero commit failures. |
| ownership | Plain scalar counters owned by the caller; no runtime or token is retained. |
| failure | No throwing behavior or invariants are defined by the aggregate itself. |
| cost | Three size_t counters. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp) |

## B0074

[Lines 401–464](../../../../../tests/unit/physical_runtime_exception_test.cpp#L401); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SweepResult sweep(const PhysicalPlan& plan, Scenario scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary-new fault points through PhysicalRuntime prepare/commit and same-owner retry. |
| inputs / outputs | Borrows plan/scenario; each up-to-8192 iteration owns a fresh initialized runtime, before images/handles/stats, same target update, optional PendingUpdate/result, and held epochs. |
| invariants | bad_alloc is expected only during prepare; after failure committed state is unchanged and the same update retries on the same runtime to match clean_result. Commit failures are rejected; first success matches oracle and invariants. Setup is outside the fault scope. |
| ownership | Borrows the plan; each iteration owns a fresh PhysicalRuntime, HeldEpochs, update, pending optional, and result optional. On failure, the same runtime and same complete update are used for the explicit retry. |
| failure | Faults only ordinary global new/new\[\] while prepare plus commit run; catches bad_alloc, keeps injection armed while a possibly returned token unwinds, and classifies prepare versus commit failure. Requires prepare failures and zero commit failures, verifies the committed state/handles/journals, then retries the same update on the same owner and compares with clean_result. Setup/oracle and account-limit failures are outside the fault scope. Stops on first successful position; hard loop cap is 8192 positions. |
| cost | Rebuilds and initializes a fixed two-alias physical runtime per position, snapshots/serializes it, and sweeps ordinary C++ allocation-call indices. The 8192 cap is an iteration guard, not a byte/work/CPU guarantee. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0076

[Lines 466–485](../../../../../tests/unit/physical_runtime_exception_test.cpp#L466); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_explicit_rollback_is_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check explicit pending-update rollback is available without ordinary-new calls. |
| inputs / outputs | Builds baseline, prepares one insert_new update before arming; calls rollback with fail_after=0 and validates state. |
| invariants | Token becomes inactive, runtime unchanged, and later commit throws invalid_epoch. |
| ownership | Borrows the plan; runtime and pending update are local owners; before images/handles/stats are detached copies. |
| failure | Prepares before arming fail_after=0, explicitly rolls the token back under the ordinary-new seam, verifies the token is inactive and runtime unchanged, then requires a second commit to throw invalid_epoch. This is rollback behavior, not failure injection during prepare. |
| cost | One fixed initialized runtime, one prepare, and one rollback/oracle comparison; no allocation-count bytes or CPU bound. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0078

[Lines 487–508](../../../../../tests/unit/physical_runtime_exception_test.cpp#L487); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_destructor_cancellation_is_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check active PendingUpdate destructor cancels without ordinary-new calls. |
| inputs / outputs | Prepares while the guard is disabled; sets fail_after=0 before leaving token scope, then checks runtime against baseline. |
| invariants | Token was active before destruction; afterward runtime must be ready and unchanged. This tests destructor cancellation rather than a failed prepare. |
| ownership | Runtime owns the active update state; a local pending token borrows/retains that state until scope exit and cancels it on destruction. |
| failure | Prepare occurs while the FaultScope is disabled. The test then sets fail_after=0 before token destruction and compares committed runtime state afterward; this checks token-destructor cancellation only through ordinary new/new\[\]. |
| cost | One initialized runtime, one prepared update and one token destructor; no account-byte or CPU measurement. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0080

[Lines 510–546](../../../../../tests/unit/physical_runtime_exception_test.cpp#L510); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_move_assignment_is_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check pending-token move assignment and rollback under ordinary-new prohibition. |
| inputs / outputs | Two runtimes each prepare insert_new; destination token move-assigns source token, then rolls it back under fail_after=0. |
| invariants | Source token becomes inactive, destination token owns active source-runtime update, explicit rollback closes it, both runtimes restore saved state, later commit is invalid_epoch. |
| ownership | Two runtimes own independent state; each active token initially belongs to its corresponding runtime. Move assignment transfers the source token into destination and cancellation rolls back the source runtime update; both runtimes outlive the tokens. |
| failure | With fail_after=0, verifies move assignment and explicit rollback do not call replaced ordinary new/new\[\]. Both runtime states must match their before images; a later commit on the rolled-back token must throw invalid_epoch. |
| cost | Two fixed runtimes, two prepared updates, one token move and two state comparisons. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0082

[Lines 548–565](../../../../../tests/unit/physical_runtime_exception_test.cpp#L548); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_facade_destruction_with_active_update(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rollback an active physical token after its facade is destroyed. |
| inputs / outputs | Optional PendingUpdate outlives a local initialized runtime; after facade destruction token rollback runs under fail_after=0. |
| invariants | Token closes, older held source/journal pins remain unchanged, and later commit is invalid_epoch; test does not access destroyed facade. |
| ownership | The optional PendingUpdate outlives the local PhysicalRuntime facade; the pending token retains enough internal/account ownership to perform rollback after facade destruction. HeldEpochs separately retains older committed epochs. |
| failure | After facade destruction, rollback runs with fail_after=0, must close the token, preserve held source/journal pins, and make a later commit fail invalid_epoch. It does not assert access to the destroyed facade. |
| cost | One initialized runtime, one prepare, facade destruction, and one token rollback. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md) |

## B0084

[Lines 567–590](../../../../../tests/unit/physical_runtime_exception_test.cpp#L567); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_commit_after_facade_destruction_is_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit an active physical update after destroying its facade. |
| inputs / outputs | Optional token and output outlive a scoped runtime; commit runs with fail_after=0, output is moved into HeldEpochs. |
| invariants | Token closes, returned epoch retains source row C and logical journal, held images remain valid, and second commit is invalid_epoch. |
| ownership | The pending token survives its facade; commit returns a PhysicalEpoch that is moved into HeldEpochs and retains the new source pin and journal after the facade is gone. |
| failure | Commit runs with fail_after=0 and must return/close without replaced ordinary new/new\[\]. The returned source row and logical journal are checked; a second commit must throw invalid_epoch. |
| cost | One prepare/commit plus source/journal retention checks, with no account/raw-malloc/system-call interception. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0086

[Lines 592–610](../../../../../tests/unit/physical_runtime_exception_test.cpp#L592); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_commit_is_noalloc(const PhysicalPlan& plan) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check ordinary-new-free commit while the runtime facade is alive. |
| inputs / outputs | Initializes runtime/held epochs, prepares insert_new, and commits under fail_after=0 into optional PhysicalEpoch. |
| invariants | Output and published snapshot equal clean_result, token is inactive/runtime ready, prior epochs persist, second commit is invalid_epoch, invariants pass. |
| ownership | Runtime owns published state; pending token owns private update until commit; returned PhysicalEpoch owns its input/source pin and support epoch/journal. Earlier HeldEpochs keep prior pins alive. |
| failure | Commit runs under fail_after=0; output must equal clean_result and published snapshot, close the token, preserve old epochs, and reject a second commit as invalid_epoch. Only replacement ordinary new/new\[\] is forbidden. |
| cost | One prepared update and publication plus small image/invariant checks; no wall-clock, CPU, or byte bound. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md) |

## B0088

[Lines 612–656](../../../../../tests/unit/physical_runtime_exception_test.cpp#L612); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_staged_output_exception_cancels(const PhysicalPlan& plan, Scenario scenario) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model caller-side output-staging bad_alloc and cancel the still-active physical token. |
| inputs / outputs | For insert_new and erase_last, prepares update, checks pending busy readers, then attempts a std::vector copy of preview.derivations under fail_after=0. |
| invariants | Staging bad_alloc leaves token active/unpublished and facade busy; explicit rollback under same seam restores full baseline; same-owner retry matches clean output. This is a model vector, not a production adapter output call. |
| ownership | Runtime owns the prepared private update; pending token remains active while the caller-local std::vector stages a copy of preview derivations. The copied vector owns its elements; rollback releases the pending state, and retry reuses the same update value. |
| failure | After prepare, busy-read guards must reject the listed public readers. A fail_after=0 allocation in caller-side output staging must throw bad_alloc without closing/publishing the token; explicit rollback under the same ordinary-new seam restores baseline, then same-owner apply(update) must match the clean oracle. It models a caller staging vector, not a production output adapter. |
| cost | One fixed scenario, preview/snapshot/handle checks, one intentionally failing standard-vector allocation, rollback, and same-owner retry. No byte/resource/CPU budget is measured. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md), [include/crown/runtime/support.hpp](../../../../../include/crown/runtime/support.hpp), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp), [docs/physical_runtime.md § Retained source rows and logical journals](../../../../physical_runtime.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp), [src/storage/accounted_table.cpp](../../../../../src/storage/accounted_table.cpp), [docs/memory_accounts.md § Live, retained and reserved state](../../../../memory_accounts.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0089

[Lines 657–659](../../../../../tests/unit/physical_runtime_exception_test.cpp#L657); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L657-L659:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in physical_runtime_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/code_review.md](../../../../code_review.md) |

## B0090

[Lines 660–691](../../../../../tests/unit/physical_runtime_exception_test.cpp#L660); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run physical token lifecycle/output checks and four scenario allocation sweeps. |
| inputs / outputs | Calls rollback/destructor/move/facade/commit/staging tests, then sweeps insert-new, erase-last, insert-existing-projection, and erase-shared-projection. |
| invariants | Source requires prepare failures in all four and zero commit failures; catches std::exception, resets fail_after, and returns 1 on failure. This packet does not claim execution. |
| ownership | The plan and each runtime/sweep fixture are local to main or its test helper; all are destroyed before process exit. |
| failure | Catches std::exception, resets fail_after, prints the failure text and returns 1. The success path checks the source-level sweep counts and prints them. No test execution is claimed by this contract packet. |
| cost | Calls the fixed lifecycle/output tests and four scenario sweeps; no runtime performance threshold is present. |
| Design | [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp) |
