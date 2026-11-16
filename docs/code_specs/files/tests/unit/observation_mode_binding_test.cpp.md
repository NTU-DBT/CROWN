# `tests/unit/observation_mode_binding_test.cpp` — block usage map

[Source](../../../../../tests/unit/observation_mode_binding_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `22cf1db7193a455faf741735494502479d9b96d952feff4c5cb504a3b22c559f`. 897 lines partitioned into 75 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–34](../../../../../tests/unit/observation_mode_binding_test.cpp#L1) | Imports dependencies; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 35–43](../../../../../tests/unit/observation_mode_binding_test.cpp#L35) | Callable definition: void note() | calls load, fetch_add, store · [reviewed contract](#b0002) |
| [B0003 · 44–44](../../../../../tests/unit/observation_mode_binding_test.cpp#L44) | Explanatory comments or spacing. |  |
| [B0004 · 45–49](../../../../../tests/unit/observation_mode_binding_test.cpp#L45) | Callable definition: void* allocate(std::size_t bytes) | calls note, std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0004) |
| [B0005 · 50–50](../../../../../tests/unit/observation_mode_binding_test.cpp#L50) | Explanatory comments or spacing. |  |
| [B0006 · 51–57](../../../../../tests/unit/observation_mode_binding_test.cpp#L51) | Callable definition: void* allocate_aligned(std::size_t bytes, std::size_t alignment) | calls note, posix_memalign; returns result · [reviewed contract](#b0006) |
| [B0007 · 58–58](../../../../../tests/unit/observation_mode_binding_test.cpp#L58) | Explanatory comments or spacing. |  |
| [B0008 · 59–81](../../../../../tests/unit/observation_mode_binding_test.cpp#L59) | Callable definition: template &lt;class Action&gt; void measure(Action&& action, std::size_t fail_index, std::size_t& allocations, bool& failure_injected, s… | calls store, load · [reviewed contract](#b0008) |
| [B0009 · 82–82](../../../../../tests/unit/observation_mode_binding_test.cpp#L82) | Explanatory comments or spacing. |  |
| [B0010 · 83–88](../../../../../tests/unit/observation_mode_binding_test.cpp#L83) | Callable definition: void disarm() noexcept | calls store · [reviewed contract](#b0010) |
| [B0011 · 89–90](../../../../../tests/unit/observation_mode_binding_test.cpp#L89) | Closes surrounding scope/type. | source comment (unverified): // namespace allocation_probe · [reviewed contract](#b0011) |
| [B0012 · 91–91](../../../../../tests/unit/observation_mode_binding_test.cpp#L91) | Callable definition: void* operator new(std::size_t bytes) | calls allocation_probe::allocate; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0012) |
| [B0013 · 92–92](../../../../../tests/unit/observation_mode_binding_test.cpp#L92) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0013) |
| [B0014 · 93–95](../../../../../tests/unit/observation_mode_binding_test.cpp#L93) | Callable definition: void* operator new(std::size_t bytes, std::align_val_t alignment) | calls allocation_probe::allocate_aligned; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0014) |
| [B0015 · 96–98](../../../../../tests/unit/observation_mode_binding_test.cpp#L96) | Callable definition: void* operator new\[\](std::size_t bytes, std::align_val_t alignment) | calls ; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0015) |
| [B0016 · 99–99](../../../../../tests/unit/observation_mode_binding_test.cpp#L99) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0016) |
| [B0017 · 100–100](../../../../../tests/unit/observation_mode_binding_test.cpp#L100) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0017) |
| [B0018 · 101–101](../../../../../tests/unit/observation_mode_binding_test.cpp#L101) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0018) |
| [B0019 · 102–102](../../../../../tests/unit/observation_mode_binding_test.cpp#L102) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0019) |
| [B0020 · 103–103](../../../../../tests/unit/observation_mode_binding_test.cpp#L103) | Callable definition: void operator delete(void* pointer, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0020) |
| [B0021 · 104–104](../../../../../tests/unit/observation_mode_binding_test.cpp#L104) | Callable definition: void operator delete\[\](void* pointer, std::align_val_t) noexcept | calls  · [reviewed contract](#b0021) |
| [B0022 · 105–107](../../../../../tests/unit/observation_mode_binding_test.cpp#L105) | Callable definition: void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0022) |
| [B0023 · 108–110](../../../../../tests/unit/observation_mode_binding_test.cpp#L108) | Callable definition: void operator delete\[\](void* pointer, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0023) |
| [B0024 · 111–122](../../../../../tests/unit/observation_mode_binding_test.cpp#L111) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_copyable_v&lt;ObservationConfiguration&gt;); · [reviewed contract](#b0024) |
| [B0025 · 123–123](../../../../../tests/unit/observation_mode_binding_test.cpp#L123) | Callable definition: std::uint64_t fake_clock() noexcept | calls ; returns ++clock_reads · [reviewed contract](#b0025) |
| [B0026 · 124–124](../../../../../tests/unit/observation_mode_binding_test.cpp#L124) | Explanatory comments or spacing. |  |
| [B0027 · 125–127](../../../../../tests/unit/observation_mode_binding_test.cpp#L125) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0027) |
| [B0028 · 128–128](../../../../../tests/unit/observation_mode_binding_test.cpp#L128) | Explanatory comments or spacing. |  |
| [B0029 · 129–139](../../../../../tests/unit/observation_mode_binding_test.cpp#L129) | Callable definition: template &lt;class Action&gt; void expect_error(std::string_view code, Action&& action, std::string_view label) | calls check, code; guard check(error.code() == code, label); · [reviewed contract](#b0029) |
| [B0030 · 140–140](../../../../../tests/unit/observation_mode_binding_test.cpp#L140) | Explanatory comments or spacing. |  |
| [B0031 · 141–141](../../../../../tests/unit/observation_mode_binding_test.cpp#L141) | Callable definition: Value integer(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0031) |
| [B0032 · 142–142](../../../../../tests/unit/observation_mode_binding_test.cpp#L142) | Callable definition: Row row(std::int64_t value) | calls integer; returns Row{integer(value)} · [reviewed contract](#b0032) |
| [B0033 · 143–143](../../../../../tests/unit/observation_mode_binding_test.cpp#L143) | Callable definition: Row edge(std::int64_t x, std::int64_t y) | calls integer; returns Row{integer(x), integer(y)} · [reviewed contract](#b0033) |
| [B0034 · 144–158](../../../../../tests/unit/observation_mode_binding_test.cpp#L144) | declares types or opens a type body. |  · [reviewed contract](#b0034) |
| [B0035 · 159–168](../../../../../tests/unit/observation_mode_binding_test.cpp#L159) | Callable definition: QFixture() : plan(planner::lower_tree(catalog, query, FreeConnexTree{ NodeId{0}, {{"R", NodeKind::native, {VariableId{0}, Variabl… | calls plan, planner::lower_tree, resize, insert; growth insert, resize · [reviewed contract](#b0035) |
| [B0036 · 169–169](../../../../../tests/unit/observation_mode_binding_test.cpp#L169) | Explanatory comments or spacing. |  |
| [B0037 · 170–174](../../../../../tests/unit/observation_mode_binding_test.cpp#L170) | Callable definition: \[\[nodiscard\]\] Database with_match() const | calls insert, row; returns result; growth insert · [reviewed contract](#b0037) |
| [B0038 · 175–176](../../../../../tests/unit/observation_mode_binding_test.cpp#L175) | Closes surrounding scope/type. |  · [reviewed contract](#b0038) |
| [B0039 · 177–185](../../../../../tests/unit/observation_mode_binding_test.cpp#L177) | Callable definition: ObservationOptions observation_options(ObservationMode mode) | calls ; returns result · [reviewed contract](#b0039) |
| [B0040 · 186–186](../../../../../tests/unit/observation_mode_binding_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0041 · 187–206](../../../../../tests/unit/observation_mode_binding_test.cpp#L187) | Callable definition: DeltaOptions exact_options(ObservationMode mode = ObservationMode::trace) | calls observation_options; returns result · [reviewed contract](#b0041) |
| [B0042 · 207–207](../../../../../tests/unit/observation_mode_binding_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0043 · 208–222](../../../../../tests/unit/observation_mode_binding_test.cpp#L208) | Callable definition: bool same_options(const DeltaOptions& a, const DeltaOptions& b) | calls ; returns a.physical.support.work_limit == b.physical.support.work_limit && · [reviewed contract](#b0043) |
| [B0044 · 223–223](../../../../../tests/unit/observation_mode_binding_test.cpp#L223) | Explanatory comments or spacing. |  |
| [B0045 · 224–247](../../../../../tests/unit/observation_mode_binding_test.cpp#L224) | Callable definition: void check_configuration(const ObservationConfiguration& actual, const DeltaOptions& requested, DeltaMode resolved_mode, DeltaCom… | calls check, ObservationConfiguration::format_version, same_options, requested_options; guard check(ObservationConfiguration::format_version() == 1, · [reviewed contract](#b0045) |
| [B0046 · 248–248](../../../../../tests/unit/observation_mode_binding_test.cpp#L248) | Explanatory comments or spacing. |  |
| [B0047 · 249–254](../../../../../tests/unit/observation_mode_binding_test.cpp#L249) | Callable definition: Relation drain(SupportRuntime::ResultCursor cursor) | calls next, check, insert, crown::storage::export_row; guard check(result.insert(crown::storage::export_row(tuple-&gt;values())).second, "runtime emitted a duplica…; returns result; growth insert; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 255–255](../../../../../tests/unit/observation_mode_binding_test.cpp#L255) | Explanatory comments or spacing. |  |
| [B0049 · 256–258](../../../../../tests/unit/observation_mode_binding_test.cpp#L256) | Callable definition: Relation reference_result(const QFixture& fixture, const Database& database) | calls reference::evaluate; returns reference::evaluate(fixture.catalog, fixture.query, database) · [reviewed contract](#b0049) |
| [B0050 · 259–259](../../../../../tests/unit/observation_mode_binding_test.cpp#L259) | Explanatory comments or spacing. |  |
| [B0051 · 260–265](../../../../../tests/unit/observation_mode_binding_test.cpp#L260) | Callable definition: void check_runtime_result(DeltaRuntime& runtime, const QFixture& fixture, const Database& database, std::string_view message) | calls check, drain, results, reference_result; guard check(drain(runtime.results()) == reference_result(fixture, database), message); · [reviewed contract](#b0051) |
| [B0052 · 266–266](../../../../../tests/unit/observation_mode_binding_test.cpp#L266) | Explanatory comments or spacing. |  |
| [B0053 · 267–276](../../../../../tests/unit/observation_mode_binding_test.cpp#L267) | Callable definition: void check_attempt_config(const ObservationSummary& summary, const DeltaOptions& requested, DeltaMode resolved, std::uint64_t own… | calls check, has_value, check_configuration; guard check(summary.configuration.has_value(), · [reviewed contract](#b0053) |
| [B0054 · 277–277](../../../../../tests/unit/observation_mode_binding_test.cpp#L277) | Explanatory comments or spacing. |  |
| [B0055 · 278–474](../../../../../tests/unit/observation_mode_binding_test.cpp#L278) | Callable definition: void scenario_timeline_and_retained_configuration() | calls exact_options, DeltaRuntime::initialize, owner, check; guard check(runtime.plan().nodes().size() == 2,; growth insert; source comment (unverified): // Q's physical tree has two nodes, but C* contains only R: S's separator · [reviewed contract](#b0055) |
| [B0056 · 475–475](../../../../../tests/unit/observation_mode_binding_test.cpp#L475) | Explanatory comments or spacing. |  |
| [B0057 · 476–503](../../../../../tests/unit/observation_mode_binding_test.cpp#L476) | Callable definition: void scenario_failed_bootstrap_is_atomic() | calls exact_options, with_match, DeltaRuntime::initialize, owner; guard check(before.current_configuration.has_value(), · [reviewed contract](#b0057) |
| [B0058 · 504–504](../../../../../tests/unit/observation_mode_binding_test.cpp#L504) | Explanatory comments or spacing. |  |
| [B0059 · 505–608](../../../../../tests/unit/observation_mode_binding_test.cpp#L505) | Callable definition: void scenario_allocation_failure_sweep_and_recovery() | calls exact_options, with_match, DeltaRuntime::initialize, allocation_probe::measure; guard check(calibration.mode() == DeltaMode::delta,; 2 loop sites; source comment (unverified): // Keep this allocation position armed across two failed calls on the same · [reviewed contract](#b0059) |
| [B0060 · 609–609](../../../../../tests/unit/observation_mode_binding_test.cpp#L609) | Explanatory comments or spacing. |  |
| [B0061 · 610–684](../../../../../tests/unit/observation_mode_binding_test.cpp#L610) | Callable definition: void scenario_generation_saturation_and_off_suppression() | calls exact_options, max, detail::set_observation_initial_generation_for_testing, DeltaRuntime::initialize; guard check(initial.current_configuration &&; growth insert; source comment (unverified): // Off removes the observation collector and cannot coexist with the legacy · [reviewed contract](#b0061) |
| [B0062 · 685–685](../../../../../tests/unit/observation_mode_binding_test.cpp#L685) | Explanatory comments or spacing. |  |
| [B0063 · 686–692](../../../../../tests/unit/observation_mode_binding_test.cpp#L686) | Type/record definition: struct ModeRun |  · [reviewed contract](#b0063) |
| [B0064 · 693–693](../../../../../tests/unit/observation_mode_binding_test.cpp#L693) | Explanatory comments or spacing. |  |
| [B0065 · 694–740](../../../../../tests/unit/observation_mode_binding_test.cpp#L694) | Callable definition: ModeRun run_observation_mode(const QFixture& fixture, ObservationMode mode) | calls exact_options, DeltaRuntime::initialize, detail::set_observation_clock_for_testing, row; guard check(output && output-&gt;operation == SetOperation::insert &&; returns {physical, support, delta, allocations, reads}; growth insert; source comment (unverified): // Match the legacy allocating transition-capture policy across off, · [reviewed contract](#b0065) |
| [B0066 · 741–741](../../../../../tests/unit/observation_mode_binding_test.cpp#L741) | Explanatory comments or spacing. |  |
| [B0067 · 742–764](../../../../../tests/unit/observation_mode_binding_test.cpp#L742) | Callable definition: void scenario_off_equivalence_and_optional_clock() | calls run_observation_mode, check; guard check(off.physical.work == counters.physical.work && · [reviewed contract](#b0067) |
| [B0068 · 765–765](../../../../../tests/unit/observation_mode_binding_test.cpp#L765) | Explanatory comments or spacing. |  |
| [B0069 · 766–790](../../../../../tests/unit/observation_mode_binding_test.cpp#L766) | Callable definition: void scenario_direct_lower_layers_unbound() | calls exact_options, support, apply, edge; guard check(support_snapshot.last && !support_snapshot.last-&gt;configuration &&; growth insert · [reviewed contract](#b0069) |
| [B0070 · 791–791](../../../../../tests/unit/observation_mode_binding_test.cpp#L791) | Explanatory comments or spacing. |  |
| [B0071 · 792–858](../../../../../tests/unit/observation_mode_binding_test.cpp#L792) | Callable definition: void scenario_session_drain_drop_retains_captured_configuration() | calls exact_options, row, io::write_input_json, push_back; guard check(current.current_configuration.has_value(),; growth insert, make_unique, push_back; 2 loop sites · [reviewed contract](#b0071) |
| [B0072 · 859–859](../../../../../tests/unit/observation_mode_binding_test.cpp#L859) | Explanatory comments or spacing. |  |
| [B0073 · 860–868](../../../../../tests/unit/observation_mode_binding_test.cpp#L860) | Callable definition: template &lt;class Action&gt; void run_scenario(std::string_view name, Action&& action) | calls std::runtime_error, std::string, what · [reviewed contract](#b0073) |
| [B0074 · 869–870](../../../../../tests/unit/observation_mode_binding_test.cpp#L869) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0074) |
| [B0075 · 871–897](../../../../../tests/unit/observation_mode_binding_test.cpp#L871) | Callable definition: int main() | calls run_scenario, detail::set_observation_clock_for_testing, detail::set_observation_initial_generation_for_testing, what; returns 0; 1 · [reviewed contract](#b0075) |

## B0001

[Lines 1–34](../../../../../tests/unit/observation_mode_binding_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L34:sha256:455024d7ea1a74d7a33e11b9a6127041230b0773161693dedbde7ddf31d32c4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare observation_mode_binding_test.cpp: include "crown/api/error.hpp", "crown/io/ingest.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "crown/runtime/observation.hpp", "crown/runtime/physical.hpp", "crown/runtime/session.hpp", "crown/runtime/support.hpp", "evaluator.hpp", &lt;atomic&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. Atomic counter storage and later atomic accesses belong to the test probe, not an engine timing or allocation measure. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 35–43](../../../../../tests/unit/observation_mode_binding_test.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void note() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count and possibly inject a bad_alloc at a selected C++ allocation probe position while observation is armed. |
| inputs / outputs | Declaration: \`void note()\`. Inputs/outputs in this selected body: Count and possibly inject a bad_alloc at a selected C++ allocation probe position while observation is armed. |
| invariants | Counts calls into this executable’s replacement-new probe only; active requests increment atomic attempt/failure counters. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | When active, the probe can throw std::bad_alloc at or after fail_at; otherwise it returns without error. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0004

[Lines 45–49](../../../../../tests/unit/observation_mode_binding_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Call the allocation probe then allocate at least one byte with malloc; translate null to bad_alloc. |
| inputs / outputs | Declaration: \`void* allocate(std::size_t bytes)\`. Inputs/outputs in this selected body: Call the allocation probe then allocate at least one byte with malloc; translate null to bad_alloc. |
| invariants | Calls note() before malloc; injection happens before backing allocation, while real malloc failure also becomes bad_alloc. |
| ownership | Returns malloc-backed raw storage; ownership transfers to the caller, which releases it through the matching replacement delete path. |
| failure | Throws std::bad_alloc at the armed probe point or if malloc fails. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0006

[Lines 51–57](../../../../../tests/unit/observation_mode_binding_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate_aligned(std::size_t bytes, std::size_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Call the allocation probe then allocate storage at requested alignment with posix_memalign. |
| inputs / outputs | Declaration: \`void* allocate_aligned(std::size_t bytes, std::size_t alignment)\`. Inputs/outputs in this selected body: Call the allocation probe then allocate storage at requested alignment with posix_memalign. |
| invariants | Calls note() before posix_memalign; aligned allocation failure becomes bad_alloc. |
| ownership | Returns posix_memalign-backed raw storage; ownership transfers to the caller, which releases it through the matching replacement delete path. |
| failure | Throws std::bad_alloc at the armed probe point or if posix_memalign fails. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0008

[Lines 59–81](../../../../../tests/unit/observation_mode_binding_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void measure(Action&& action, std::size_t fail_index,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run an action while resetting probe counters, setting the fail index and collecting attempt/fault outputs, disabling active state on both return and exception. |
| inputs / outputs | Declaration: \`template &lt;class Action&gt; void measure(Action&& action, std::size_t fail_index, std::size_t& allocations, bool& failure_injected, std::size_t& failures)\`. Inputs/outputs in this selected body: Run an action while resetting probe counters, setting the fail index and collecting attempt/fault outputs, disabling active state on both return and exception. |
| invariants | Fail index is zero-based and persistent for requests at/after the threshold in this guarded action; catch path records then rethrows. |
| ownership | The action is invoked but not retained; output references are borrowed result slots filled before return. |
| failure | Deactivates/records state then rethrows any action exception. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0010

[Lines 83–88](../../../../../tests/unit/observation_mode_binding_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void disarm() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable probe activity, restore no-failure marker, and clear only the injected flag and injected-fault count. |
| inputs / outputs | Declaration: \`void disarm() noexcept\`. Inputs/outputs in this selected body: Disable probe activity, restore no-failure marker, and clear only the injected flag and injected-fault count. |
| invariants | Disarm is nonthrowing and resets the active flag, failure marker and injected diagnostics. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Noexcept probe reset. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0011

[Lines 89–90](../../../../../tests/unit/observation_mode_binding_test.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L90:sha256:0b226b9db70fd75a395d7251fe9828ab661cf302ee86deb2878e9c14f4055be8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in observation_mode_binding_test.cpp: namespace allocation_probe. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 91–91](../../../../../tests/unit/observation_mode_binding_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar global throwing new through the probe and malloc. |
| inputs / outputs | Declaration: \`void* operator new(std::size_t bytes)\`. Inputs/outputs in this selected body: Route ordinary scalar global throwing new through the probe and malloc. |
| invariants | Direct ordinary scalar throwing replacement; no dedicated nothrow form exists and indirect delegation is not asserted. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0013

[Lines 92–92](../../../../../tests/unit/observation_mode_binding_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array global throwing new through the same scalar backing path. |
| inputs / outputs | Declaration: \`void* operator new\[\](std::size_t bytes)\`. Inputs/outputs in this selected body: Route ordinary array global throwing new through the same scalar backing path. |
| invariants | Array replacement delegates to direct ordinary scalar replacement and shares its probe. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0014

[Lines 93–95](../../../../../tests/unit/observation_mode_binding_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned scalar global throwing new through the probe and aligned allocation. |
| inputs / outputs | Declaration: \`void* operator new(std::size_t bytes, std::align_val_t alignment)\`. Inputs/outputs in this selected body: Route aligned scalar global throwing new through the probe and aligned allocation. |
| invariants | Direct aligned scalar throwing replacement; no nothrow form or account-denial seam. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0015

[Lines 96–98](../../../../../tests/unit/observation_mode_binding_test.cpp#L96); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned array global throwing new through the scalar aligned replacement. |
| inputs / outputs | Declaration: \`void* operator new\[\](std::size_t bytes, std::align_val_t alignment)\`. Inputs/outputs in this selected body: Route aligned array global throwing new through the scalar aligned replacement. |
| invariants | Aligned array replacement delegates to direct aligned scalar replacement. |
| ownership | Returns raw storage to the allocation caller; storage ownership transfers to the corresponding C++ object. |
| failure | Direct ordinary/aligned throwing replacement can throw std::bad_alloc at the armed probe point or on backing allocation failure. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0016

[Lines 99–99](../../../../../tests/unit/observation_mode_binding_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free a scalar replacement pointer and decrement tracked live allocations for non-null storage. |
| inputs / outputs | Declaration: \`void operator delete(void* pointer) noexcept\`. Inputs/outputs in this selected body: Free a scalar replacement pointer and decrement tracked live allocations for non-null storage. |
| invariants | Counts frees only when callers reach this executable’s replacement delete forms. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0017

[Lines 100–100](../../../../../tests/unit/observation_mode_binding_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free an array replacement pointer through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer) noexcept\`. Inputs/outputs in this selected body: Free an array replacement pointer through scalar delete. |
| invariants | Array delete delegates to scalar delete and shares deallocation accounting. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0018

[Lines 101–101](../../../../../tests/unit/observation_mode_binding_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free a sized scalar replacement pointer through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete(void* pointer, std::size_t) noexcept\`. Inputs/outputs in this selected body: Free a sized scalar replacement pointer through scalar delete. |
| invariants | Sized scalar delete delegates; no size-specific allocator accounting. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0019

[Lines 102–102](../../../../../tests/unit/observation_mode_binding_test.cpp#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free a sized array replacement pointer through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer, std::size_t) noexcept\`. Inputs/outputs in this selected body: Free a sized array replacement pointer through scalar delete. |
| invariants | Sized array delete delegates; no size-specific allocator accounting. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0020

[Lines 103–103](../../../../../tests/unit/observation_mode_binding_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free aligned scalar replacement storage through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete(void* pointer, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free aligned scalar replacement storage through scalar delete. |
| invariants | Aligned scalar delete delegates to scalar delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0021

[Lines 104–104](../../../../../tests/unit/observation_mode_binding_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free aligned array replacement storage through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free aligned array replacement storage through scalar delete. |
| invariants | Aligned array delete delegates to aligned scalar delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0022

[Lines 105–107](../../../../../tests/unit/observation_mode_binding_test.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized aligned scalar replacement storage through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free sized aligned scalar replacement storage through scalar delete. |
| invariants | Sized aligned scalar delete delegates to aligned scalar delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0023

[Lines 108–110](../../../../../tests/unit/observation_mode_binding_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized aligned array replacement storage through scalar delete. |
| inputs / outputs | Declaration: \`void operator delete\[\](void* pointer, std::size_t, std::align_val_t) noexcept\`. Inputs/outputs in this selected body: Free sized aligned array replacement storage through scalar delete. |
| invariants | Sized aligned array delete delegates to aligned scalar delete. |
| ownership | Consumes and releases the supplied pointer; it retains no object. |
| failure | Noexcept deallocation; this entry does not add allocation-failure coverage. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0024

[Lines 111–122](../../../../../tests/unit/observation_mode_binding_test.cpp#L111); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L122:sha256:2f50fb58b537234a73d41bcf39f0a38615305c51ed8c173bd1e95fc0c54a6775
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare observation_mode_binding_test.cpp: bind local aliases/name imports; require 5 compile-time type/ABI conditions; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 123–123](../../../../../tests/unit/observation_mode_binding_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t fake_clock() noexcept { return ++clock_reads; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the injected observation clock and return a monotonically increasing test tick. |
| inputs / outputs | Declaration: \`std::uint64_t fake_clock() noexcept\`. Inputs/outputs in this selected body: Read the injected observation clock and return a monotonically increasing test tick. |
| invariants | Clock counter is reset by runner and fake clock returns one incremented scalar read. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Function is declared noexcept and only increments the injected clock counter; it has no exception path. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0027

[Lines 125–127](../../../../../tests/unit/observation_mode_binding_test.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one local O07 fixture assertion with a runtime_error diagnostic. |
| inputs / outputs | Declaration: \`void check(bool condition, std::string_view message)\`. Inputs/outputs in this selected body: Fail one local O07 fixture assertion with a runtime_error diagnostic. |
| invariants | False predicate throws std::runtime_error; no API Error translation. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | A failed fixture assertion raises std::runtime_error; no production error translation. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0029

[Lines 129–139](../../../../../tests/unit/observation_mode_binding_test.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void expect_error(std::string_view code, Action&& action, std::string_view label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to raise crown::api::Error with an exact code and a labeled failure. |
| inputs / outputs | Declaration: \`template &lt;class Action&gt; void expect_error(std::string_view code, Action&& action, std::string_view label)\`. Inputs/outputs in this selected body: Require an action to raise crown::api::Error with an exact code and a labeled failure. |
| invariants | Catches only crown::api::Error; another exception propagates and missing/wrong code fails through check. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0031

[Lines 141–141](../../../../../tests/unit/observation_mode_binding_test.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value integer(std::int64_t value) { return Value{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one int64 Value for the finite query fixture. |
| inputs / outputs | Declaration: \`Value integer(std::int64_t value)\`. Inputs/outputs in this selected body: Construct one int64 Value for the finite query fixture. |
| invariants | Scalar Value is returned by value. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0032

[Lines 142–142](../../../../../tests/unit/observation_mode_binding_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t value) { return Row{integer(value)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a unary Row around one integer Value. |
| inputs / outputs | Declaration: \`Row row(std::int64_t value)\`. Inputs/outputs in this selected body: Construct a unary Row around one integer Value. |
| invariants | Row owns one int64 value. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0033

[Lines 143–143](../../../../../tests/unit/observation_mode_binding_test.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t x, std::int64_t y) { return Row{integer(x), integer(y)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an edge Row for R(x,y). |
| inputs / outputs | Declaration: \`Row edge(std::int64_t x, std::int64_t y)\`. Inputs/outputs in this selected body: Construct an edge Row for R(x,y). |
| invariants | Row owns two int64 values. |
| ownership | Value parameters are local copies and returned values own their contents; no borrowed fixture is retained unless declared as a reference return. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0034

[Lines 144–158](../../../../../tests/unit/observation_mode_binding_test.cpp#L144); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L144-L158:sha256:b6f4a567673445990f58f80c51fac9dc00e027eb5b9115e195ebe364bcbbf8b5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare observation_mode_binding_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0035

[Lines 159–168](../../../../../tests/unit/observation_mode_binding_test.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  QFixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the fixed R(x,y), S(y), head-x fixture and its initial source database. |
| inputs / outputs | Declaration: \`QFixture() : plan(planner::lower_tree(catalog, query, FreeConnexTree{ NodeId{0}, {{"R", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}}, {"S", NodeKind::nati…\`. Inputs/outputs in this selected body: Build the fixed R(x,y), S(y), head-x fixture and its initial source database. |
| invariants | Fixture catalog/query/plan/database are owned values. R is root, S is child and head is x; S separator y is outside head, so C* contains only R. |
| ownership | Owns Catalog, Query, PhysicalPlan and initial Database fixture values. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0037

[Lines 170–174](../../../../../tests/unit/observation_mode_binding_test.cpp#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] Database with_match() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the initial database and insert S(9), making the query result contain x=7. |
| inputs / outputs | Declaration: \`\[\[nodiscard\]\] Database with_match() const\`. Inputs/outputs in this selected body: Copy the initial database and insert S(9), making the query result contain x=7. |
| invariants | Returns a database copy with S(9) added, making output x=7. |
| ownership | Borrows fixture and returns a copied Database. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0038

[Lines 175–176](../../../../../tests/unit/observation_mode_binding_test.cpp#L175); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L176:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in observation_mode_binding_test.cpp: struct QFixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0039

[Lines 177–185](../../../../../tests/unit/observation_mode_binding_test.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationOptions observation_options(ObservationMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build observation option values for a requested mode with fixed trace/sample settings. |
| inputs / outputs | Declaration: \`ObservationOptions observation_options(ObservationMode mode)\`. Inputs/outputs in this selected body: Build observation option values for a requested mode with fixed trace/sample settings. |
| invariants | Returns ObservationOptions with fixed mode/capacity/period/offset/timing values. |
| ownership | Option values are returned/copied by value; fields contain fixed scalar or optional settings. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0041

[Lines 187–206](../../../../../tests/unit/observation_mode_binding_test.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions exact_options(ObservationMode mode = ObservationMode::trace) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build nested delta options with explicit support, work, view, spool and observation limits. |
| inputs / outputs | Declaration: \`DeltaOptions exact_options(ObservationMode mode = ObservationMode::trace)\`. Inputs/outputs in this selected body: Build nested delta options with explicit support, work, view, spool and observation limits. |
| invariants | Returns nested DeltaOptions with explicit support, work, view, spool and observation settings. |
| ownership | Option values are returned/copied by value; fields contain fixed scalar or optional settings. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0043

[Lines 208–222](../../../../../tests/unit/observation_mode_binding_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_options(const DeltaOptions& a, const DeltaOptions& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every configuration-sensitive DeltaOptions field used by this fixture. |
| inputs / outputs | Declaration: \`bool same_options(const DeltaOptions& a, const DeltaOptions& b)\`. Inputs/outputs in this selected body: Compare every configuration-sensitive DeltaOptions field used by this fixture. |
| invariants | Equality is fieldwise across the nested fields listed in the body, not object representation. |
| ownership | Option values are returned/copied by value; fields contain fixed scalar or optional settings. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0045

[Lines 224–247](../../../../../tests/unit/observation_mode_binding_test.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_configuration(const ObservationConfiguration& actual,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the complete exposed ObservationConfiguration against requested options and expected resolved owner/generation/factor fields. |
| inputs / outputs | Declaration: \`void check_configuration(const ObservationConfiguration& actual, const DeltaOptions& requested, DeltaMode resolved_mode, DeltaCompletion resolved_completion, std::uint64_t owner, …\`. Inputs/outputs in this selected body: Check the complete exposed ObservationConfiguration against requested options and expected resolved owner/generation/factor fields. |
| invariants | Configuration captures requested/resolved mode/completion, owner, generation/saturation, factor count and every specified nested option. |
| ownership | Option values are returned/copied by value; fields contain fixed scalar or optional settings. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0047

[Lines 249–254](../../../../../tests/unit/observation_mode_binding_test.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a by-value SupportRuntime result cursor into an owning set Relation and reject duplicate set rows. |
| inputs / outputs | Declaration: \`Relation drain(SupportRuntime::ResultCursor cursor)\`. Inputs/outputs in this selected body: Drain a by-value SupportRuntime result cursor into an owning set Relation and reject duplicate set rows. |
| invariants | Consumes a cursor by value and returns a set of exported Row copies. |
| ownership | Consumes cursor by value and returns a Relation of copied Row values. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0049

[Lines 256–258](../../../../../tests/unit/observation_mode_binding_test.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation reference_result(const QFixture& fixture, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the fixed query through the independent A04 reference evaluator. |
| inputs / outputs | Declaration: \`Relation reference_result(const QFixture& fixture, const Database& database)\`. Inputs/outputs in this selected body: Evaluate the fixed query through the independent A04 reference evaluator. |
| invariants | Uses the independent A04 reference evaluator on this fixture database. |
| ownership | Borrows fixture/database; returns an owning Relation. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0051

[Lines 260–265](../../../../../tests/unit/observation_mode_binding_test.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_runtime_result(DeltaRuntime& runtime, const QFixture& fixture,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare DeltaRuntime result rows and physical snapshot to the independent database/evaluator state. |
| inputs / outputs | Declaration: \`void check_runtime_result(DeltaRuntime& runtime, const QFixture& fixture, const Database& database, std::string_view message)\`. Inputs/outputs in this selected body: Compare DeltaRuntime result rows and physical snapshot to the independent database/evaluator state. |
| invariants | Checks full result set and exact source tables; finite oracle only, not performance evidence. |
| ownership | Borrows runtime/fixture/database; output rows are copied into local Relation. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0053

[Lines 267–276](../../../../../tests/unit/observation_mode_binding_test.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_attempt_config(const ObservationSummary& summary,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one retained attempt summary against its captured request, mode, owner, generation and outcome. |
| inputs / outputs | Declaration: \`void check_attempt_config(const ObservationSummary& summary, const DeltaOptions& requested, DeltaMode resolved, std::uint64_t owner, std::uint64_t generation, ObservationOutcome o…\`. Inputs/outputs in this selected body: Check one retained attempt summary against its captured request, mode, owner, generation and outcome. |
| invariants | Historical attempt configuration is the value captured at begin; later set_mode calls do not relabel it. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0055

[Lines 278–474](../../../../../tests/unit/observation_mode_binding_test.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_timeline_and_retained_configuration() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise initialization, mode changes, pending rollback, committed output, moves, rebuilt owner and detached configuration lifetimes. |
| inputs / outputs | Declaration: \`void scenario_timeline_and_retained_configuration()\`. Inputs/outputs in this selected body: Exercise initialization, mode changes, pending rollback, committed output, moves, rebuilt owner and detached configuration lifetimes. |
| invariants | Checks initial generation, same-mode no-op, pending rollback, committed delta output, busy switch rejection, move, rebuild with fresh owner and detached value lifetime. |
| ownership | Runtime owners are local; copied ObservationConfiguration/ObservationSnapshot values survive later mode changes or runtime destruction. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Finite one-row fixture transitions and configuration checks; no wall-clock benchmark. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0057

[Lines 476–503](../../../../../tests/unit/observation_mode_binding_test.cpp#L476); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_failed_bootstrap_is_atomic() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise failed delta bootstrap and prove the maintenance runtime/configuration/cache remain unchanged. |
| inputs / outputs | Declaration: \`void scenario_failed_bootstrap_is_atomic()\`. Inputs/outputs in this selected body: Exercise failed delta bootstrap and prove the maintenance runtime/configuration/cache remain unchanged. |
| invariants | Zero view/cursor budgets reject mode bootstrap with resource_limit before mode/cache/configuration publication; same-mode maintenance remains inert. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0059

[Lines 505–608](../../../../../tests/unit/observation_mode_binding_test.cpp#L505); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_allocation_failure_sweep_and_recovery() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep tracked allocation failures during maintenance-to-delta bootstrap; repeat each failure on the same owner, then disarm and recover that owner. |
| inputs / outputs | Declaration: \`void scenario_allocation_failure_sweep_and_recovery()\`. Inputs/outputs in this selected body: Sweep tracked allocation failures during maintenance-to-delta bootstrap; repeat each failure on the same owner, then disarm and recover that owner. |
| invariants | Failure positions count directly replaced ordinary/aligned global-new requests. Two failures and unarmed recovery use each same owner; direct malloc, MemoryAccount, syscall and nothrow paths are not injected. |
| ownership | Each fault position creates one fresh runtime; two failures and the subsequent recovery use that same owner. |
| failure | Only calls reaching direct ordinary/aligned global new are injected. Repeated bad_alloc must preserve mode/cache/configuration and the same owner retries after disarming. Direct malloc, MemoryAccount denial and systemcall failure are not injected. |
| cost | One successful calibration plus one fresh owner per observed global-new request; two failures and one recovery on each owner. This is not byte accounting or CPU time. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0061

[Lines 610–684](../../../../../tests/unit/observation_mode_binding_test.cpp#L610); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_generation_saturation_and_off_suppression() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise generation saturation at UINT64_MAX and disabled-observation suppression, including mandatory output/accounting. |
| inputs / outputs | Declaration: \`void scenario_generation_saturation_and_off_suppression()\`. Inputs/outputs in this selected body: Exercise generation saturation at UINT64_MAX and disabled-observation suppression, including mandatory output/accounting. |
| invariants | Generation reaches exact UINT64_MAX unsaturated, then a later successful semantic switch marks saturation. Off mode omits optional configuration but still performs mandatory output/accounting; off plus transition capture is invalid. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Finite generation boundary and disabled-mode fixture with one named update. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0063

[Lines 686–692](../../../../../tests/unit/observation_mode_binding_test.cpp#L686); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModeRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the result of one observation-mode run: physical/support/delta metrics, counted allocations and fake-clock reads. |
| inputs / outputs | Declaration: \`struct ModeRun\`. Inputs/outputs in this selected body: Hold the result of one observation-mode run: physical/support/delta metrics, counted allocations and fake-clock reads. |
| invariants | Returns copied physical/support/delta metric structs plus global-new request and fake-clock counts for one update. |
| ownership | Plain local fixture value type; declared containers and scalar values are owned by the record. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Plain fixture data declaration; no runtime work. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0065

[Lines 694–740](../../../../../tests/unit/observation_mode_binding_test.cpp#L694); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ModeRun run_observation_mode(const QFixture& fixture, ObservationMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the same update under off, counters and timed modes, collect metrics/clock/allocation observations and compare final A04 result. |
| inputs / outputs | Declaration: \`ModeRun run_observation_mode(const QFixture& fixture, ObservationMode mode)\`. Inputs/outputs in this selected body: Run the same update under off, counters and timed modes, collect metrics/clock/allocation observations and compare final A04 result. |
| invariants | Runs same one-row Q update in off/counters/timed modes; timed reads fake clock, off/counters suppress it, and result is checked against A04. |
| ownership | Fixture is borrowed; runtime/epoch are local; returned ModeRun contains copied metric/count values. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Finite one-row fixture transitions and configuration checks; no wall-clock benchmark. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0067

[Lines 742–764](../../../../../tests/unit/observation_mode_binding_test.cpp#L742); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_off_equivalence_and_optional_clock() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare off, counters and timed modes for mandatory metric and output equivalence, allocation counts and clock suppression. |
| inputs / outputs | Declaration: \`void scenario_off_equivalence_and_optional_clock()\`. Inputs/outputs in this selected body: Compare off, counters and timed modes for mandatory metric and output equivalence, allocation counts and clock suppression. |
| invariants | Compares selected mandatory work/output fields and replacement-new counts; it does not require all optional metrics or clock duration equal. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Three one-row mode runs, not a benchmark. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0069

[Lines 766–790](../../../../../tests/unit/observation_mode_binding_test.cpp#L766); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_direct_lower_layers_unbound() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Call support-only and physical-only APIs and prove their summaries are unbound to a DeltaRuntime configuration. |
| inputs / outputs | Declaration: \`void scenario_direct_lower_layers_unbound()\`. Inputs/outputs in this selected body: Call support-only and physical-only APIs and prove their summaries are unbound to a DeltaRuntime configuration. |
| invariants | Direct support/physical summaries remain unbound to a DeltaRuntime configuration. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Finite one-row fixture transitions and configuration checks; no wall-clock benchmark. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0071

[Lines 792–858](../../../../../tests/unit/observation_mode_binding_test.cpp#L792); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_session_drain_drop_retains_captured_configuration() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one QuerySession event through commit/drain/stop/drop, checking captured configuration and trace release/retention. |
| inputs / outputs | Declaration: \`void scenario_session_drain_drop_retains_captured_configuration()\`. Inputs/outputs in this selected body: Run one QuerySession event through commit/drain/stop/drop, checking captured configuration and trace release/retention. |
| invariants | Session commit/drain/drop retains copied configuration summary while releasing trace records on drop; snapshot rows are owning values. |
| ownership | Session owns stream/runtime; observation snapshot/configuration are value copies and trace rows are separately retained/released. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Finite one-row fixture transitions and configuration checks; no wall-clock benchmark. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0073

[Lines 860–868](../../../../../tests/unit/observation_mode_binding_test.cpp#L860); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void run_scenario(std::string_view name, Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add a scenario label to output and rethrow an exception with that label. |
| inputs / outputs | Declaration: \`template &lt;class Action&gt; void run_scenario(std::string_view name, Action&& action)\`. Inputs/outputs in this selected body: Add a scenario label to output and rethrow an exception with that label. |
| invariants | Label/action are borrowed for invocation; caught exception is wrapped in a newly allocated labeled runtime_error. |
| ownership | Reference/view inputs are borrowed for the call; no fixture argument is retained unless purpose says an output value is returned. |
| failure | Fixture mismatch is reported by its local assertion helper; otherwise API, allocation and filesystem exceptions propagate unless this function explicitly catches them. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |

## B0074

[Lines 869–870](../../../../../tests/unit/observation_mode_binding_test.cpp#L869); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L869-L870:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in observation_mode_binding_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0075

[Lines 871–897](../../../../../tests/unit/observation_mode_binding_test.cpp#L871); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the O07 mode-binding proposal scenarios, reset test seams and return process success/failure. |
| inputs / outputs | Declaration: \`int main()\`. Inputs/outputs in this selected body: Run the O07 mode-binding proposal scenarios, reset test seams and return process success/failure. |
| invariants | Main resets test clock/generation seams on both success/failure and returns 0 or 1; no execution result is claimed by this review. |
| ownership | Fixture/runtime/report objects are local to the test call; no runtime owner escapes the scenario. |
| failure | The driver catches documented exceptions, prints a diagnostic and returns a nonzero status. |
| cost | Work is limited to the explicitly named fixture fields or finite scenario; no production complexity or wall-clock bound. |
| Design | [tests/unit/observation_mode_binding_test.cpp](../../../../../tests/unit/observation_mode_binding_test.cpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md) |
