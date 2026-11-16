# `tests/unit/runtime_observation_test.cpp` — block usage map

[Source](../../../../../tests/unit/runtime_observation_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d40bbfe7005c7d0dc2dad8251fcda574710df6c7a576a01f417f9e95906504d0`. 1450 lines partitioned into 106 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–33](../../../../../tests/unit/runtime_observation_test.cpp#L1) | Imports dependencies; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 34–37](../../../../../tests/unit/runtime_observation_test.cpp#L34) | Callable definition: void note() noexcept | calls load, fetch_add · [reviewed contract](#b0002) |
| [B0003 · 38–38](../../../../../tests/unit/runtime_observation_test.cpp#L38) | Explanatory comments or spacing. |  |
| [B0004 · 39–43](../../../../../tests/unit/runtime_observation_test.cpp#L39) | Callable definition: void* allocate(std::size_t bytes) | calls note, std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0004) |
| [B0005 · 44–44](../../../../../tests/unit/runtime_observation_test.cpp#L44) | Explanatory comments or spacing. |  |
| [B0006 · 45–51](../../../../../tests/unit/runtime_observation_test.cpp#L45) | Callable definition: void* allocate_aligned(std::size_t bytes, std::size_t alignment) | calls note, posix_memalign; returns result · [reviewed contract](#b0006) |
| [B0007 · 52–52](../../../../../tests/unit/runtime_observation_test.cpp#L52) | Explanatory comments or spacing. |  |
| [B0008 · 53–65](../../../../../tests/unit/runtime_observation_test.cpp#L53) | Callable definition: template &lt;class Action&gt; std::size_t count_during(Action&& action) | calls store, load; returns count.load(std::memory_order_relaxed) · [reviewed contract](#b0008) |
| [B0009 · 66–67](../../../../../tests/unit/runtime_observation_test.cpp#L66) | Closes surrounding scope/type. | source comment (unverified): // namespace allocation_probe · [reviewed contract](#b0009) |
| [B0010 · 68–68](../../../../../tests/unit/runtime_observation_test.cpp#L68) | Callable definition: void* operator new(std::size_t bytes) | calls allocation_probe::allocate; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0010) |
| [B0011 · 69–69](../../../../../tests/unit/runtime_observation_test.cpp#L69) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0011) |
| [B0012 · 70–72](../../../../../tests/unit/runtime_observation_test.cpp#L70) | Callable definition: void* operator new(std::size_t bytes, std::align_val_t alignment) | calls allocation_probe::allocate_aligned; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0012) |
| [B0013 · 73–75](../../../../../tests/unit/runtime_observation_test.cpp#L73) | Callable definition: void* operator new\[\](std::size_t bytes, std::align_val_t alignment) | calls ; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0013) |
| [B0014 · 76–76](../../../../../tests/unit/runtime_observation_test.cpp#L76) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0014) |
| [B0015 · 77–77](../../../../../tests/unit/runtime_observation_test.cpp#L77) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0015) |
| [B0016 · 78–78](../../../../../tests/unit/runtime_observation_test.cpp#L78) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0016) |
| [B0017 · 79–79](../../../../../tests/unit/runtime_observation_test.cpp#L79) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0017) |
| [B0018 · 80–80](../../../../../tests/unit/runtime_observation_test.cpp#L80) | Callable definition: void operator delete(void* pointer, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0018) |
| [B0019 · 81–81](../../../../../tests/unit/runtime_observation_test.cpp#L81) | Callable definition: void operator delete\[\](void* pointer, std::align_val_t) noexcept | calls  · [reviewed contract](#b0019) |
| [B0020 · 82–84](../../../../../tests/unit/runtime_observation_test.cpp#L82) | Callable definition: void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0020) |
| [B0021 · 85–87](../../../../../tests/unit/runtime_observation_test.cpp#L85) | Callable definition: void operator delete\[\](void* pointer, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0021) |
| [B0022 · 88–98](../../../../../tests/unit/runtime_observation_test.cpp#L88) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_copyable_v&lt;TraceRecord&gt;); · [reviewed contract](#b0022) |
| [B0023 · 99–101](../../../../../tests/unit/runtime_observation_test.cpp#L99) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0023) |
| [B0024 · 102–102](../../../../../tests/unit/runtime_observation_test.cpp#L102) | Explanatory comments or spacing. |  |
| [B0025 · 103–112](../../../../../tests/unit/runtime_observation_test.cpp#L103) | Callable definition: template &lt;class Action&gt; void expect_resource_limit(Action&& action, std::string_view label) | calls code, check; guard check(caught, label); · [reviewed contract](#b0025) |
| [B0026 · 113–113](../../../../../tests/unit/runtime_observation_test.cpp#L113) | Explanatory comments or spacing. |  |
| [B0027 · 114–114](../../../../../tests/unit/runtime_observation_test.cpp#L114) | Callable definition: Value integer(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0027) |
| [B0028 · 115–115](../../../../../tests/unit/runtime_observation_test.cpp#L115) | Callable definition: Value string(std::string value) | calls std::move; returns Value{std::move(value)} · [reviewed contract](#b0028) |
| [B0029 · 116–116](../../../../../tests/unit/runtime_observation_test.cpp#L116) | Callable definition: Row row(std::int64_t value) | calls integer; returns Row{integer(value)} · [reviewed contract](#b0029) |
| [B0030 · 117–117](../../../../../tests/unit/runtime_observation_test.cpp#L117) | Callable definition: Row edge(std::int64_t x, std::int64_t y) | calls integer; returns Row{integer(x), integer(y)} · [reviewed contract](#b0030) |
| [B0031 · 118–133](../../../../../tests/unit/runtime_observation_test.cpp#L118) | declares types or opens a type body. |  · [reviewed contract](#b0031) |
| [B0032 · 134–144](../../../../../tests/unit/runtime_observation_test.cpp#L134) | Callable definition: QFixture() : plan(planner::lower_tree(catalog, query, FreeConnexTree{ NodeId{0}, {{"R", NodeKind::native, {VariableId{0}, Variabl… | calls plan, planner::lower_tree, resize, insert; growth insert, resize · [reviewed contract](#b0032) |
| [B0033 · 145–146](../../../../../tests/unit/runtime_observation_test.cpp#L145) | Closes surrounding scope/type. |  · [reviewed contract](#b0033) |
| [B0034 · 147–156](../../../../../tests/unit/runtime_observation_test.cpp#L147) | Callable definition: Catalog constrained_q_catalog() | calls ; returns catalog · [reviewed contract](#b0034) |
| [B0035 · 157–177](../../../../../tests/unit/runtime_observation_test.cpp#L157) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0035) |
| [B0036 · 178–183](../../../../../tests/unit/runtime_observation_test.cpp#L178) | Callable definition: ConstraintQFixture() | calls resize, insert, edge, row; growth insert, resize; 1 loop sites · [reviewed contract](#b0036) |
| [B0037 · 184–200](../../../../../tests/unit/runtime_observation_test.cpp#L184) | declares types or opens a type body. |  · [reviewed contract](#b0037) |
| [B0038 · 201–210](../../../../../tests/unit/runtime_observation_test.cpp#L201) | Callable definition: AliasFixture() : plan(planner::lower_tree(catalog, query, FreeConnexTree{ NodeId{0}, {{"projected_join", NodeKind::generalized, {… | calls plan, planner::lower_tree · [reviewed contract](#b0038) |
| [B0039 · 211–212](../../../../../tests/unit/runtime_observation_test.cpp#L211) | Closes surrounding scope/type. |  · [reviewed contract](#b0039) |
| [B0040 · 213–225](../../../../../tests/unit/runtime_observation_test.cpp#L213) | Callable definition: ObservationOptions observation_options(ObservationMode mode, std::size_t trace_capacity = 256, std::uint64_t sample_period = 1, s… | calls ; returns result · [reviewed contract](#b0040) |
| [B0041 · 226–230](../../../../../tests/unit/runtime_observation_test.cpp#L226) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0041) |
| [B0042 · 231–236](../../../../../tests/unit/runtime_observation_test.cpp#L231) | Callable definition: Relation drain(SupportRuntime::ResultCursor cursor) | calls next, check, insert, crown::storage::export_row; guard check(result.insert(crown::storage::export_row(tuple-&gt;values())).second, "support cursor emitted du…; returns result; growth insert; 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 237–237](../../../../../tests/unit/runtime_observation_test.cpp#L237) | Explanatory comments or spacing. |  |
| [B0044 · 238–240](../../../../../tests/unit/runtime_observation_test.cpp#L238) | Callable definition: Relation drain_physical(SupportRuntime::ResultCursor cursor) | calls drain, std::move; returns drain(std::move(cursor)) · [reviewed contract](#b0044) |
| [B0045 · 241–241](../../../../../tests/unit/runtime_observation_test.cpp#L241) | Explanatory comments or spacing. |  |
| [B0046 · 242–246](../../../../../tests/unit/runtime_observation_test.cpp#L242) | Callable definition: Relation expected_q(const QFixture& fixture) | calls insert, row, reference::evaluate; returns reference::evaluate(fixture.catalog, fixture.query, after); growth insert · [reviewed contract](#b0046) |
| [B0047 · 247–247](../../../../../tests/unit/runtime_observation_test.cpp#L247) | Explanatory comments or spacing. |  |
| [B0048 · 248–264](../../../../../tests/unit/runtime_observation_test.cpp#L248) | Callable definition: void check_q_metrics(const SupportMetrics& m) | calls check; guard check(m.work == 40, "Q support work must equal the literal 40 boundary"); · [reviewed contract](#b0048) |
| [B0049 · 265–265](../../../../../tests/unit/runtime_observation_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0050 · 266–273](../../../../../tests/unit/runtime_observation_test.cpp#L266) | Callable definition: void check_q_physical_metrics(const PhysicalMetrics& m) | calls check; guard check(m.work == 44, "Q physical work must equal the literal 44 boundary"); · [reviewed contract](#b0050) |
| [B0051 · 274–274](../../../../../tests/unit/runtime_observation_test.cpp#L274) | Explanatory comments or spacing. |  |
| [B0052 · 275–294](../../../../../tests/unit/runtime_observation_test.cpp#L275) | Callable definition: bool same_support_metrics(const SupportMetrics& left, const SupportMetrics& right) | calls std::tie; returns std::tie(left.work, left.copied_rows, left.copied_index_memberships, · [reviewed contract](#b0052) |
| [B0053 · 295–295](../../../../../tests/unit/runtime_observation_test.cpp#L295) | Explanatory comments or spacing. |  |
| [B0054 · 296–319](../../../../../tests/unit/runtime_observation_test.cpp#L296) | Callable definition: std::string describe_support_metrics(const SupportMetrics& m) | calls str; returns out.str() · [reviewed contract](#b0054) |
| [B0055 · 320–320](../../../../../tests/unit/runtime_observation_test.cpp#L320) | Explanatory comments or spacing. |  |
| [B0056 · 321–328](../../../../../tests/unit/runtime_observation_test.cpp#L321) | Callable definition: bool same_physical_metrics(const PhysicalMetrics& left, const PhysicalMetrics& right) | calls std::tie; returns std::tie(left.work, left.source_changes, left.aliases_visited, · [reviewed contract](#b0056) |
| [B0057 · 329–329](../../../../../tests/unit/runtime_observation_test.cpp#L329) | Explanatory comments or spacing. |  |
| [B0058 · 330–335](../../../../../tests/unit/runtime_observation_test.cpp#L330) | Callable definition: const MetricDescriptor& descriptor(MetricId id) | calls observation_registry, std::runtime_error; returns item; 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 336–336](../../../../../tests/unit/runtime_observation_test.cpp#L336) | Explanatory comments or spacing. |  |
| [B0060 · 337–358](../../../../../tests/unit/runtime_observation_test.cpp#L337) | Callable definition: void check_registry() | calls observation_registry, check, size, descriptor; guard check(registry.size() == observation_metric_count,; 1 loop sites · [reviewed contract](#b0060) |
| [B0061 · 359–359](../../../../../tests/unit/runtime_observation_test.cpp#L359) | Explanatory comments or spacing. |  |
| [B0062 · 360–367](../../../../../tests/unit/runtime_observation_test.cpp#L360) | Callable definition: std::string_view availability_name(MetricAvailability availability) | calls ; returns @; @ · [reviewed contract](#b0062) |
| [B0063 · 368–368](../../../../../tests/unit/runtime_observation_test.cpp#L368) | Explanatory comments or spacing. |  |
| [B0064 · 369–386](../../../../../tests/unit/runtime_observation_test.cpp#L369) | Callable definition: void check_metric(const ObservationSummary& summary, MetricId id, MetricAvailability availability, std::uint64_t value, std::stri… | calls metric, descriptor, std::to_string, std::string · [reviewed contract](#b0064) |
| [B0065 · 387–387](../../../../../tests/unit/runtime_observation_test.cpp#L387) | Explanatory comments or spacing. |  |
| [B0066 · 388–428](../../../../../tests/unit/runtime_observation_test.cpp#L388) | Callable definition: void check_q_state(const SupportSnapshot& state, std::uint64_t sequence, bool answer) | calls check, size, values, edge; guard check(state.sequence == sequence && state.has_answer == answer, · [reviewed contract](#b0066) |
| [B0067 · 429–429](../../../../../tests/unit/runtime_observation_test.cpp#L429) | Explanatory comments or spacing. |  |
| [B0068 · 430–439](../../../../../tests/unit/runtime_observation_test.cpp#L430) | Callable definition: void check_q_initial_physical(const PhysicalSnapshot& state, const Database& initial) | calls check, check_q_state, size, values; guard check(state.sequence == 0 && state.physical.tables == initial.tables, · [reviewed contract](#b0068) |
| [B0069 · 440–440](../../../../../tests/unit/runtime_observation_test.cpp#L440) | Explanatory comments or spacing. |  |
| [B0070 · 441–463](../../../../../tests/unit/runtime_observation_test.cpp#L441) | Callable definition: void check_constraint_q_rollback(const PhysicalSnapshot& state, const ConstraintQFixture& fixture) | calls check, size, values, edge; guard check(state.sequence == 0 && state.physical.tables == fixture.initial.tables &&; 1 loop sites · [reviewed contract](#b0070) |
| [B0071 · 464–464](../../../../../tests/unit/runtime_observation_test.cpp#L464) | Explanatory comments or spacing. |  |
| [B0072 · 465–495](../../../../../tests/unit/runtime_observation_test.cpp#L465) | Callable definition: void check_q_journal(const SupportEpoch& epoch) | calls check, size, empty, tuple; guard check(epoch.journal && epoch.journal-&gt;sequence == epoch.sequence &&; returns true; false; 2 loop sites · [reviewed contract](#b0072) |
| [B0073 · 496–496](../../../../../tests/unit/runtime_observation_test.cpp#L496) | Explanatory comments or spacing. |  |
| [B0074 · 497–512](../../../../../tests/unit/runtime_observation_test.cpp#L497) | Callable definition: void check_observation_header(const ObservationSnapshot& snapshot, ObservationMode mode, std::uint64_t sequence, ObservationLayer… | calls check; guard check(snapshot.mandatory_accounting && snapshot.options.mode == mode, · [reviewed contract](#b0074) |
| [B0075 · 513–513](../../../../../tests/unit/runtime_observation_test.cpp#L513) | Explanatory comments or spacing. |  |
| [B0076 · 514–554](../../../../../tests/unit/runtime_observation_test.cpp#L514) | Callable definition: void check_q_physical_observation(const ObservationSnapshot& snapshot, ObservationMode mode, std::uint64_t owner) | calls check, check_observation_header, check_metric, descriptor; guard check(snapshot.options.mode == ObservationMode::off && snapshot.mandatory_accounting && · [reviewed contract](#b0076) |
| [B0077 · 555–555](../../../../../tests/unit/runtime_observation_test.cpp#L555) | Explanatory comments or spacing. |  |
| [B0078 · 556–561](../../../../../tests/unit/runtime_observation_test.cpp#L556) | Type/record definition: struct PhysicalModeRun |  · [reviewed contract](#b0078) |
| [B0079 · 562–562](../../../../../tests/unit/runtime_observation_test.cpp#L562) | Explanatory comments or spacing. |  |
| [B0080 · 563–685](../../../../../tests/unit/runtime_observation_test.cpp#L563) | Callable definition: PhysicalModeRun run_q_physical_mode(ObservationMode mode, BuildMethod method, std::size_t trace_capacity = 256, std::uint64_t sam… | calls observation_options, PhysicalRuntime::initialize, check, observations; guard check(!runtime.observations().last && runtime.observations().attempts == 0,; returns {epoch.support.metrics, epoch.input.metrics, allocations, std::move(trace)}; growth emplace, insert; 1 loop sites · [reviewed contract](#b0080) |
| [B0081 · 686–686](../../../../../tests/unit/runtime_observation_test.cpp#L686) | Explanatory comments or spacing. |  |
| [B0082 · 687–709](../../../../../tests/unit/runtime_observation_test.cpp#L687) | Callable definition: void test_q_observation_modes() | calls check_registry, run_q_physical_mode, emplace, std::move; guard check(same_support_metrics(baseline-&gt;support, run.support) &&; growth emplace; 2 loop sites · [reviewed contract](#b0082) |
| [B0083 · 710–710](../../../../../tests/unit/runtime_observation_test.cpp#L710) | Explanatory comments or spacing. |  |
| [B0084 · 711–789](../../../../../tests/unit/runtime_observation_test.cpp#L711) | Callable definition: void test_direct_support_modes_and_allocations() | calls observation_options, runtime, apply, edge; guard check(seed.native_changed && !seed.has_answer && seed.sequence == 1,; growth emplace, insert; 2 loop sites · [reviewed contract](#b0084) |
| [B0085 · 790–790](../../../../../tests/unit/runtime_observation_test.cpp#L790) | Explanatory comments or spacing. |  |
| [B0086 · 791–1083](../../../../../tests/unit/runtime_observation_test.cpp#L791) | Callable definition: void test_work_limit_boundaries_and_rollback_allocations() | calls observation_options, support, apply, edge; guard check(support.sequence() == 1 && support.ready() && !support.has_answer(),; growth insert; 1 loop sites; source comment (unverified): // Literal physical prefix: source change 1 + 102 constraint rows + one · [reviewed contract](#b0086) |
| [B0087 · 1084–1084](../../../../../tests/unit/runtime_observation_test.cpp#L1084) | Explanatory comments or spacing. |  |
| [B0088 · 1085–1096](../../../../../tests/unit/runtime_observation_test.cpp#L1085) | Callable definition: ObservationTrace run_q_trace_capacity(std::size_t capacity) | calls observation_options, PhysicalRuntime::initialize, apply, row; returns runtime.observation_trace(); growth insert · [reviewed contract](#b0088) |
| [B0089 · 1097–1097](../../../../../tests/unit/runtime_observation_test.cpp#L1097) | Explanatory comments or spacing. |  |
| [B0090 · 1098–1166](../../../../../tests/unit/runtime_observation_test.cpp#L1098) | Callable definition: void test_trace_caps_sampling_and_release() | calls run_q_trace_capacity, check, size, empty; guard check(!full.snapshot.trace_truncated && full.snapshot.trace_dropped == 0 &&; growth insert · [reviewed contract](#b0090) |
| [B0091 · 1167–1170](../../../../../tests/unit/runtime_observation_test.cpp#L1167) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0091) |
| [B0092 · 1171–1175](../../../../../tests/unit/runtime_observation_test.cpp#L1171) | Callable definition: std::uint64_t counting_clock() noexcept | calls ; returns injected_clock_value · [reviewed contract](#b0092) |
| [B0093 · 1176–1176](../../../../../tests/unit/runtime_observation_test.cpp#L1176) | Explanatory comments or spacing. |  |
| [B0094 · 1177–1181](../../../../../tests/unit/runtime_observation_test.cpp#L1177) | Callable definition: void reset_clock() noexcept | calls detail::set_observation_clock_for_testing · [reviewed contract](#b0094) |
| [B0095 · 1182–1182](../../../../../tests/unit/runtime_observation_test.cpp#L1182) | Explanatory comments or spacing. |  |
| [B0096 · 1183–1185](../../../../../tests/unit/runtime_observation_test.cpp#L1183) | Type/record definition: struct ClockReset |  · [reviewed contract](#b0096) |
| [B0097 · 1186–1186](../../../../../tests/unit/runtime_observation_test.cpp#L1186) | Explanatory comments or spacing. |  |
| [B0098 · 1187–1265](../../../../../tests/unit/runtime_observation_test.cpp#L1187) | Callable definition: void test_optional_clock_reads() | calls observation_options, DeltaRuntime::initialize, reset_clock, apply; guard check(expected == Relation{row(7)} && signed_result &&; growth insert; 1 loop sites · [reviewed contract](#b0098) |
| [B0099 · 1266–1266](../../../../../tests/unit/runtime_observation_test.cpp#L1266) | Explanatory comments or spacing. |  |
| [B0100 · 1267–1369](../../../../../tests/unit/runtime_observation_test.cpp#L1267) | Callable definition: void test_multi_alias_generalized_projection() | calls check, nodes, size, inputs; guard check(fixture.plan.nodes().size() == 3 &&; growth emplace, insert, resize; 2 loop sites · [reviewed contract](#b0100) |
| [B0101 · 1370–1370](../../../../../tests/unit/runtime_observation_test.cpp#L1370) | Explanatory comments or spacing. |  |
| [B0102 · 1371–1420](../../../../../tests/unit/runtime_observation_test.cpp#L1371) | Callable definition: void test_session_retained_summary() | calls resize, insert, edge, row; guard check(session-&gt;begin_next_result() == SessionBegin::pending,; growth insert, make_unique, push_back, resize; 1 loop sites · [reviewed contract](#b0102) |
| [B0103 · 1421–1423](../../../../../tests/unit/runtime_observation_test.cpp#L1421) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0103) |
| [B0104 · 1424–1433](../../../../../tests/unit/runtime_observation_test.cpp#L1424) | Callable definition: template &lt;class Action&gt; void run_scenario(std::string_view name, Action&& action) | calls std::runtime_error, std::string, what · [reviewed contract](#b0104) |
| [B0105 · 1434–1434](../../../../../tests/unit/runtime_observation_test.cpp#L1434) | Explanatory comments or spacing. |  |
| [B0106 · 1435–1450](../../../../../tests/unit/runtime_observation_test.cpp#L1435) | Callable definition: int main() | calls run_scenario, what; returns 0; 1 · [reviewed contract](#b0106) |

## B0001

[Lines 1–33](../../../../../tests/unit/runtime_observation_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/api/error.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile the observation integration test against ingestion, planning, physical/delta/session/support, and evaluator interfaces. |
| inputs / outputs | The includes provide error, plan/runtime, observation, evaluator, and test-container declarations. Lines 30–33 also declare the probe’s atomic active flag and count; the adjacent \`note()\` helper increments only while active, before ordinary \`malloc\` or aligned \`posix_memalign\`. |
| invariants | The include set declares dependencies only; tests compare selected runtime results with the independent evaluator and inspect observations through public snapshots. |
| ownership | No objects or callback state are owned by these includes. The following probe state is separate test-executable storage. |
| failure | Missing declarations or an unavailable runtime feature fail compilation; no runtime failure is caught by this include block. |
| cost | The probe exists only in this test executable. Its ordinary and aligned replacement \`new\`/\`new\[\]\` hooks count attempts while active, before the underlying allocation succeeds or fails; they do not report bytes or elapsed time and do not cover allocation APIs called directly instead of those hooks, RSS, or CPU. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp) |

## B0002

[Lines 34–37](../../../../../tests/unit/runtime_observation_test.cpp#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void note() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Increment the optional global replacement-new counter while a measurement window is active. |
| inputs / outputs | No input/output; if active, relaxed atomic count increases by one. |
| invariants | Inactive operation is a no-op; this counter records intercepted C++ new calls, not allocated bytes. |
| ownership | Mutates test-process atomics only. |
| failure | No throw; noexcept. |
| cost | One active load and conditional atomic increment per intercepted allocation; direct malloc/syscalls bypass the counter. |
| Design | tests/unit/runtime_observation_test.cpp:34, docs/memory_accounts.md:52, docs/observability.md:163 |

## B0004

[Lines 39–43](../../../../../tests/unit/runtime_observation_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide ordinary replacement new storage through malloc while counting the request. |
| inputs / outputs | Accepts byte count; zero maps to a one-byte request; returns memory or throws bad_alloc. |
| invariants | Calls note before malloc, so count measures the request even if system allocation fails. |
| ownership | Caller owns returned raw memory until matching replacement delete calls free. |
| failure | malloc failure throws bad_alloc; no injected failure threshold in this test. |
| cost | One conditional count plus malloc; count is not MemoryAccount requested-byte or payload-byte measurement. |
| Design | tests/unit/runtime_observation_test.cpp:39, docs/memory_accounts.md:52, docs/observability.md:163 |

## B0006

[Lines 45–51](../../../../../tests/unit/runtime_observation_test.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate_aligned(std::size_t bytes, std::size_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide aligned replacement-new storage with posix_memalign and count the C++ request. |
| inputs / outputs | Accepts bytes/alignment and returns raw aligned pointer; zero maps to alignment-sized storage. |
| invariants | The count increments before posix_memalign; nonzero return becomes bad_alloc. |
| ownership | Caller owns raw storage until matching aligned delete overload uses free. |
| failure | posix_memalign failure throws bad_alloc. |
| cost | One conditional counter increment plus aligned allocation; this does not count direct allocator/syscall paths. |
| Design | tests/unit/runtime_observation_test.cpp:45, docs/memory_accounts.md:52 |

## B0008

[Lines 53–65](../../../../../tests/unit/runtime_observation_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
std::size_t count_during(Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count replacement-new calls around one action and reliably disarm on both success and exception. |
| inputs / outputs | Forwards Action once and returns the number of new calls during the window. |
| invariants | Resets count before arming; catch-all disarms then rethrows; success disarms before reading the count. |
| ownership | Does not own Action state; process-global counter is isolated by synchronous window assumptions. |
| failure | Action exceptions propagate after active=false cleanup. |
| cost | Measures C++ new request count only; direct malloc/syscalls bypass it and there is no byte/CPU/MemoryAccount reading. |
| Design | tests/unit/runtime_observation_test.cpp:53, docs/verification/o07-observation-test-proposal/README.md:11, docs/memory_accounts.md:52 |

## B0009

[Lines 66–67](../../../../../tests/unit/runtime_observation_test.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L67:sha256:0b226b9db70fd75a395d7251fe9828ab661cf302ee86deb2878e9c14f4055be8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_observation_test.cpp: namespace allocation_probe. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 68–68](../../../../../tests/unit/runtime_observation_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar allocations through the test executable replacement new for mode-allocation comparisons. |
| inputs / outputs | Passes byte count, and alignment for aligned forms, to the matching probe allocator. |
| invariants | Only C++ allocation expressions dispatched to these replacements are counted; allocation bytes are not measured. |
| ownership | Replacement is global to this test executable; returned storage is released by its sized/unsized/aligned delete overloads. |
| failure | System allocation failure becomes bad_alloc; the probe itself is nonthrowing and has no failure threshold. |
| cost | One count increment if active and one malloc/posix_memalign; not a global heap or syscall seam. |
| Design | tests/unit/runtime_observation_test.cpp:68, docs/memory_accounts.md:52, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0011

[Lines 69–69](../../../../../tests/unit/runtime_observation_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array allocations through the test executable replacement new for mode-allocation comparisons. |
| inputs / outputs | Passes byte count, and alignment for aligned forms, to the matching probe allocator. |
| invariants | Only C++ allocation expressions dispatched to these replacements are counted; allocation bytes are not measured. |
| ownership | Replacement is global to this test executable; returned storage is released by its sized/unsized/aligned delete overloads. |
| failure | System allocation failure becomes bad_alloc; the probe itself is nonthrowing and has no failure threshold. |
| cost | One count increment if active and one malloc/posix_memalign; not a global heap or syscall seam. |
| Design | tests/unit/runtime_observation_test.cpp:69, docs/memory_accounts.md:52, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0012

[Lines 70–72](../../../../../tests/unit/runtime_observation_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned scalar allocations through the test executable replacement new for mode-allocation comparisons. |
| inputs / outputs | Passes byte count, and alignment for aligned forms, to the matching probe allocator. |
| invariants | Only C++ allocation expressions dispatched to these replacements are counted; allocation bytes are not measured. |
| ownership | Replacement is global to this test executable; returned storage is released by its sized/unsized/aligned delete overloads. |
| failure | System allocation failure becomes bad_alloc; the probe itself is nonthrowing and has no failure threshold. |
| cost | One count increment if active and one malloc/posix_memalign; not a global heap or syscall seam. |
| Design | tests/unit/runtime_observation_test.cpp:70, docs/memory_accounts.md:52, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0013

[Lines 73–75](../../../../../tests/unit/runtime_observation_test.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned array allocations through the test executable replacement new for mode-allocation comparisons. |
| inputs / outputs | Passes byte count, and alignment for aligned forms, to the matching probe allocator. |
| invariants | Only C++ allocation expressions dispatched to these replacements are counted; allocation bytes are not measured. |
| ownership | Replacement is global to this test executable; returned storage is released by its sized/unsized/aligned delete overloads. |
| failure | System allocation failure becomes bad_alloc; the probe itself is nonthrowing and has no failure threshold. |
| cost | One count increment if active and one malloc/posix_memalign; not a global heap or syscall seam. |
| Design | tests/unit/runtime_observation_test.cpp:73, docs/memory_accounts.md:52, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0014

[Lines 76–76](../../../../../tests/unit/runtime_observation_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:76, docs/memory_accounts.md:52 |

## B0015

[Lines 77–77](../../../../../tests/unit/runtime_observation_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:77, docs/memory_accounts.md:52 |

## B0016

[Lines 78–78](../../../../../tests/unit/runtime_observation_test.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized scalar replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:78, docs/memory_accounts.md:52 |

## B0017

[Lines 79–79](../../../../../tests/unit/runtime_observation_test.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized array replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:79, docs/memory_accounts.md:52 |

## B0018

[Lines 80–80](../../../../../tests/unit/runtime_observation_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free aligned scalar replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:80, docs/memory_accounts.md:52 |

## B0019

[Lines 81–81](../../../../../tests/unit/runtime_observation_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free aligned array replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:81, docs/memory_accounts.md:52 |

## B0020

[Lines 82–84](../../../../../tests/unit/runtime_observation_test.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized aligned scalar replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:82, docs/memory_accounts.md:52 |

## B0021

[Lines 85–87](../../../../../tests/unit/runtime_observation_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free sized aligned array replacement-new storage with free; size/alignment parameters are ABI-only. |
| inputs / outputs | Accepts pointer and the matching optional size/alignment arguments; returns void. |
| invariants | All replacement allocation paths use malloc/posix_memalign, so one free family is sufficient. |
| ownership | Pointer remains caller-owned until this delete call, then is released. |
| failure | No expected throwing path; delete is noexcept. |
| cost | One free call; no counter increment is performed on deallocation. |
| Design | tests/unit/runtime_observation_test.cpp:85, docs/memory_accounts.md:52 |

## B0022

[Lines 88–98](../../../../../tests/unit/runtime_observation_test.cpp#L88); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_trivially_copyable_v<TraceRecord>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep trace records a plain numeric value suitable for the observation buffer and enforce the selected representation assumptions at compile time. |
| inputs / outputs | The block opens the anonymous test namespace, imports crown/runtime names, and asserts trivial copyability, standard layout, and \`uint64_t\` types for event, cause, and tuple IDs. |
| invariants | Only those listed type properties are asserted; they do not establish trace completeness, retention, or allocation behavior. |
| ownership | TraceRecord values are copied by value in the test; the assertions introduce no owning handle or payload lifetime. |
| failure | A representation change violating an assertion fails compilation. There is no runtime error path. |
| cost | Compile-time type checks only; no trace append, clock read, heap allocation, or product runtime cost. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [include/crown/runtime/observation.hpp §TraceRecord](../../../../../include/crown/runtime/observation.hpp) |

## B0023

[Lines 99–101](../../../../../tests/unit/runtime_observation_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a test assertion by throwing with its message. |
| inputs / outputs | Accepts bool and borrowed string_view; no return. |
| invariants | False always raises; true returns without constructing a diagnostic string. |
| ownership | Does not retain the message. |
| failure | Throws runtime_error for false; formatting allocation failure can propagate. |
| cost | Constant predicate work; diagnostic string is formed on failure only. |
| Design | tests/unit/runtime_observation_test.cpp:99 |

## B0025

[Lines 103–112](../../../../../tests/unit/runtime_observation_test.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void expect_resource_limit(Action&& action, std::string_view label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an action raises Error(resource_limit) for the budget boundary under test. |
| inputs / outputs | Forwards and invokes Action once, then checks the error code; label identifies the failed boundary. |
| invariants | Wrong Error codes are treated as failure because caught is true only for resource_limit; other exception types propagate. |
| ownership | Action is borrowed for the synchronous call; no result state retained. |
| failure | If the required resource_limit is missing/wrong, check() throws runtime_error. |
| cost | One action call and exception-code comparison; no budget measurement beyond the runtime result. |
| Design | tests/unit/runtime_observation_test.cpp:103, docs/observability.md:71 |

## B0027

[Lines 114–114](../../../../../tests/unit/runtime_observation_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value integer(std::int64_t value) { return Value{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct typed int64 fixture value. |
| inputs / outputs | Takes int64, returns Value. |
| invariants | Value remains typed integer for independent relation equality. |
| ownership | Returns owning Value/Row; no caller storage is borrowed. |
| failure | Container/string allocation may throw and propagates. |
| cost | Small fixture construction outside count_during windows unless explicitly called by a measured action. |
| Design | tests/unit/runtime_observation_test.cpp:114, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0028

[Lines 115–115](../../../../../tests/unit/runtime_observation_test.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value string(std::string value) { return Value{std::move(value)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct owned string fixture value. |
| inputs / outputs | Takes string by value and moves it into Value. |
| invariants | Returned Value owns the bytes; caller string can be moved from. |
| ownership | Returns owning Value/Row; no caller storage is borrowed. |
| failure | Container/string allocation may throw and propagates. |
| cost | Small fixture construction outside count_during windows unless explicitly called by a measured action. |
| Design | tests/unit/runtime_observation_test.cpp:115, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0029

[Lines 116–116](../../../../../tests/unit/runtime_observation_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t value) { return Row{integer(value)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one-column int64 relation row. |
| inputs / outputs | Takes int64 and returns Row{integer(value)}. |
| invariants | Matches S(y) schema. |
| ownership | Returns owning Value/Row; no caller storage is borrowed. |
| failure | Container/string allocation may throw and propagates. |
| cost | Small fixture construction outside count_during windows unless explicitly called by a measured action. |
| Design | tests/unit/runtime_observation_test.cpp:116, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0030

[Lines 117–117](../../../../../tests/unit/runtime_observation_test.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t x, std::int64_t y) { return Row{integer(x), integer(y)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct two-column int64 edge row. |
| inputs / outputs | Takes x,y int64 and returns Row{x,y}. |
| invariants | Matches R(x,y) fixture field order. |
| ownership | Returns owning Value/Row; no caller storage is borrowed. |
| failure | Container/string allocation may throw and propagates. |
| cost | Small fixture construction outside count_during windows unless explicitly called by a measured action. |
| Design | tests/unit/runtime_observation_test.cpp:117, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0031

[Lines 118–133](../../../../../tests/unit/runtime_observation_test.cpp#L118); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the small R(x,y) join S(y) plan used by query observation, clock, and session scenarios. |
| inputs / outputs | The fixture has two tables, projects x, lowers an R-to-S tree, and seeds R with (7,9) while S starts empty. The clock caller inserts S(9) and checks the emitted row is 7. |
| invariants | The plan/query use deterministic IDs and the fixture’s initial database contains only the R row. This is scenario setup, not a promise about arbitrary join workloads. |
| ownership | Catalog/query/plan/database are fixture-owned values. Runtime instances constructed from the plan own their runtime state separately. |
| failure | Plan lowering or runtime setup may throw on invalid fixture construction; the fixture has no catch or fallback. |
| cost | Small fixed test input and one plan lowering per fixture construction. It does not measure production runtime costs; allocation counts in callers wrap selected operations separately. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/unit/runtime_observation_test.cpp §clock and session callers](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0032

[Lines 134–144](../../../../../tests/unit/runtime_observation_test.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  QFixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build Q(x)=R(x,y),S(y) with R={(7,9)} and S empty, native R root/S child. |
| inputs / outputs | Constructor initializes catalog/query/plan and source database for the hand-counted update case. |
| invariants | Query head is x; one insertion S(9) creates answer {7}; plan nodes/occurrences align with literal IDs 0 and 1. |
| ownership | Fixture owns catalog, query, plan and initial Database; tests pass const references or copy initial state. |
| failure | Planner lowering or fixture allocations may fail and propagate. |
| cost | Constructs one physical plan and one-row base database; initialization is outside mutation allocation probes. |
| Design | tests/unit/runtime_observation_test.cpp:134, docs/verification/o07-observation-test-proposal/README.md:11, docs/observability.md:71 |

## B0033

[Lines 145–146](../../../../../tests/unit/runtime_observation_test.cpp#L145); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L145-L146:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_observation_test.cpp: struct QFixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0034

[Lines 147–156](../../../../../tests/unit/runtime_observation_test.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog constrained_q_catalog() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the same Q catalog with enforced unique constraint on S.y for coordinator charge/rollback tests. |
| inputs / outputs | No input; returns Catalog with R/S and named S_y_unique constraint on S column 0. |
| invariants | Constraint is enforced; the failure test inserts value 9 while 100 unrelated values 100..199 exist, so its expected failure is work budget, not uniqueness violation. |
| ownership | Catalog return owns tables and constraint descriptors. |
| failure | Construction allocation can fail; later planner or constraint operations may report their own errors. |
| cost | Creates small catalog metadata; the 100-row scan cost belongs to the later update fixture. |
| Design | tests/unit/runtime_observation_test.cpp:147, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0035

[Lines 157–177](../../../../../tests/unit/runtime_observation_test.cpp#L157); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ConstraintQFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a constraint-heavy Q input for a work-cap rollback boundary test. |
| inputs / outputs | The fixture uses the Q query with enforced unique S.y, seeds R(7,9), and fills S with values 100 through 199. A caller tries S(9) under work cap 130 and expects the coordinator prefix to run while the next support charge aborts. |
| invariants | The unrelated S rows exclude 9; the test checks sequence/readiness and the committed before-state after the rejected update. The fixture itself does not perform or catch that update. |
| ownership | Catalog, query, plan, and initial rows are owned by the test fixture; a PhysicalRuntime receives copies/compiled references through its normal initialization API. |
| failure | Construction/lowering errors propagate. The caller catches the expected \`resource_limit\` through \`expect_resource_limit\` and separately asserts rollback; this struct does not guarantee rollback by itself. |
| cost | Creates 100 unrelated initial S rows for the one bounded integration scenario. The 107 prefix and 40 support charge are test work counters, not measured CPU time. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp §work-limit admission](../../../../../src/runtime/physical.cpp), [tests/unit/runtime_observation_test.cpp §work-limit rollback caller](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0036

[Lines 178–183](../../../../../tests/unit/runtime_observation_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ConstraintQFixture() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build constraint-heavy Q initial state with R(7,9) and all 100 unrelated S values in \[100,200). |
| inputs / outputs | Default constructor builds constrained catalog/query/plan and fills initial DB. |
| invariants | Static endpoints define exactly 100 rows; this set is unique and excludes S(9), while the later cap 130 admits coordinator prefix 107 but not prefix+support 40. |
| ownership | Fixture owns all database rows and typed plan metadata. |
| failure | Fixture setup/lowering allocation failures propagate. |
| cost | Inserts 100 setup rows; measured coordinator work occurs only when the later update is applied. |
| Design | tests/unit/runtime_observation_test.cpp:178, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0037

[Lines 184–200](../../../../../tests/unit/runtime_observation_test.cpp#L184); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct AliasFixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Model a self-join with two aliases over one edge table for generalized projection observation checks. |
| inputs / outputs | The fixture maps \`forward\` to (x,y) and \`reverse\` to (y,z), ignores payload in both atoms, and projects y. Its constructor completes a generalized root with two native children; a caller inserts a self-loop and compares against the evaluator. |
| invariants | Both aliases reference source table 0 with distinct variable mappings. The ignored payload does not bind a query variable, but remains part of full physical row identity; distinct payloads can provide separate support for the same projected result. The caller computes its expected answer separately with the evaluator. |
| ownership | The fixture owns its catalog, query, and plan values. After the caller applies the update, the PhysicalRuntime owns its stored source row; the caller’s update value and evaluator’s expected database/result are separate test values. |
| failure | Lowering can reject an invalid plan and the fixture does not catch it. The independent comparison reports caller assertion failure if the generalized result differs. |
| cost | One small plan fixture; a separate test probe counts allocations around the chosen update. No timing or general alias-processing bound follows from this setup. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/unit/runtime_observation_test.cpp §multi-alias caller](../../../../../tests/unit/runtime_observation_test.cpp), [docs/semantics.md §Tables, occurrences and values](../../../../semantics.md) |

## B0038

[Lines 201–210](../../../../../tests/unit/runtime_observation_test.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  AliasFixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a generalized projected self-join over one edge table aliased forward and reverse, joining on y and projecting y. |
| inputs / outputs | Constructor initializes catalog/query/plan; physical update inserts edge(3,3,"edge"). |
| invariants | Two aliases visit the same base table; generalized root and both native children each retain one visible E(y=3) key; output remains one row. |
| ownership | Owns plan/catalog/query; runtime owns source and support state after construction. |
| failure | Lowering/allocation failures propagate. |
| cost | One source row drives two aliases and one generalized candidate; allocation comparison captures only the update action. |
| Design | tests/unit/runtime_observation_test.cpp:201, docs/verification/o07-observation-test-proposal/README.md:20, docs/observability.md:71 |

## B0039

[Lines 211–212](../../../../../tests/unit/runtime_observation_test.cpp#L211); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L211-L212:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_observation_test.cpp: struct AliasFixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0040

[Lines 213–225](../../../../../tests/unit/runtime_observation_test.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationOptions observation_options(ObservationMode mode,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct ObservationOptions with explicit mode/capacity/sampling/timing values for test scenarios. |
| inputs / outputs | Takes five values with defaults for trace capacity 256, period 1, offset 0, timings true; returns options by value. |
| invariants | Mode, trace capacity, sample rule and timing enable are passed through without runtime inference. |
| ownership | Value object copied into runtime options; contains no borrowed payload. |
| failure | No expected exception. |
| cost | Fixed scalar assignments; no measurement work. |
| Design | tests/unit/runtime_observation_test.cpp:213, docs/observability.md:71 |

## B0041

[Lines 226–230](../../../../../tests/unit/runtime_observation_test.cpp#L226); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::array<ObservationMode, 4> modes{
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | List the four observation modes exercised by the integration scenarios. |
| inputs / outputs | The constexpr array contains \`off\`, \`counters\`, \`timed\`, and \`trace\`; the helper immediately above supplies trace capacity 256, sample period 1, offset 0, and timing enabled unless overridden. |
| invariants | This is a test enumeration of the declared modes. Test results cover the listed scenarios and overrides, not every possible trace capacity or workload. |
| ownership | Static array values only; each test loop reads the array and constructs its own options/runtime. |
| failure | Invalid mode or sampling settings are rejected by \`ObservationState::create\` before it constructs the state; the four enumerated values and the helper’s default settings are valid test inputs. |
| cost | The array itself has no runtime allocation; each caller’s four mode-specific runs and any fixture/runtime setup are separate test work. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [include/crown/runtime/observation.hpp §ObservationMode and ObservationOptions](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp §option validation](../../../../../src/runtime/observation.cpp) |

## B0042

[Lines 231–236](../../../../../tests/unit/runtime_observation_test.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a logical support cursor into an independent set relation. |
| inputs / outputs | Takes ResultCursor by value, repeatedly next()s, exports tuple values and returns Relation. |
| invariants | Duplicate output rows fail the test; by-value cursor owns its lease for the drain and closes on terminal next/destruction. |
| ownership | Returned Relation owns row values; input cursor is a local moved/copied facade. |
| failure | Cursor errors or duplicate assertion failures propagate. |
| cost | Full output traversal allocates set rows; abstract cursor work is separate and is not CPU/bytes. |
| Design | tests/unit/runtime_observation_test.cpp:231, docs/result_cursors.md:18, docs/result_cursors.md:76, docs/result_cursors.md:101 |

## B0044

[Lines 238–240](../../../../../tests/unit/runtime_observation_test.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain_physical(SupportRuntime::ResultCursor cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a PhysicalRuntime result cursor to the same set-drain oracle. |
| inputs / outputs | Accepts support-cursor base type by value and forwards it to drain(std::move(cursor)). |
| invariants | No extra row mapping is introduced; caller supplied cursor view determines layout. |
| ownership | Ownership is transferred into drain by move; returned relation owns output values. |
| failure | Underlying drain errors propagate. |
| cost | No extra traversal beyond drain; forwarding itself has no observation semantics. |
| Design | tests/unit/runtime_observation_test.cpp:238, docs/result_cursors.md:18 |

## B0046

[Lines 242–246](../../../../../tests/unit/runtime_observation_test.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation expected_q(const QFixture& fixture) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calculate the independent expected Q answer after adding S(9) to a copy of initial source state. |
| inputs / outputs | Takes const QFixture; returns reference evaluator relation. |
| invariants | Copies initial database, inserts S(9) into table 1, then evaluates catalog/query; literal expected result is {7}. |
| ownership | Fixture remains unchanged; evaluator owns any temporary/output relation. |
| failure | Evaluator/container failures propagate. |
| cost | Copies small initial database and runs independent A04 evaluation outside counted mutation window. |
| Design | tests/unit/runtime_observation_test.cpp:242, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0048

[Lines 248–264](../../../../../tests/unit/runtime_observation_test.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_q_metrics(const SupportMetrics& m) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin every mandatory support counter for the Q S(9) update to the hand trace. |
| inputs / outputs | Takes SupportMetrics const ref; no return. |
| invariants | Requires work40, no historical copies/candidates, exact native/event/transitions/storage/metadata/journal counts. |
| ownership | Borrows one epoch metric value; no state copy or mutation. |
| failure | Any changed literal counter fails through check(). |
| cost | Fixed scalar comparisons; work is abstract mandatory accounting, not CPU duration or heap bytes. |
| Design | tests/unit/runtime_observation_test.cpp:248, docs/observability.md:71, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0050

[Lines 266–273](../../../../../tests/unit/runtime_observation_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_q_physical_metrics(const PhysicalMetrics& m) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin physical Q coordinator work and source/alias/derivation/crossing counts. |
| inputs / outputs | Takes PhysicalMetrics const ref. |
| invariants | Requires work44 and one source/alias/derivation/native crossing with zero constraints; this outer work includes support work only after successful charge. |
| ownership | Borrows metrics from one PhysicalEpoch. |
| failure | Counter mismatch fails test; incomplete nested charge cases separately expect inclusive/exclusive unavailable. |
| cost | Fixed comparisons of abstract charges, not elapsed CPU. |
| Design | tests/unit/runtime_observation_test.cpp:266, docs/observability.md:71 |

## B0052

[Lines 275–294](../../../../../tests/unit/runtime_observation_test.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_support_metrics(const SupportMetrics& left, const SupportMetrics& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all SupportMetrics fields for equality across observation modes. |
| inputs / outputs | Takes two const metric references; returns bool. |
| invariants | Includes work, copy, native, candidate, storage, journal, event and queue fields. |
| ownership | Borrows both epoch values. |
| failure | No expected error. |
| cost | Fixed tuple comparisons; no runtime operation. |
| Design | tests/unit/runtime_observation_test.cpp:275, docs/observability.md:71 |

## B0054

[Lines 296–319](../../../../../tests/unit/runtime_observation_test.cpp#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string describe_support_metrics(const SupportMetrics& m) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Format support counters into a diagnostic string for generalized self-join failures. |
| inputs / outputs | Takes SupportMetrics const ref and returns owning std::string. |
| invariants | Names selected counter values; it is a failure diagnostic, not a serialized API report. |
| ownership | Copies numeric text into returned string; does not retain metric reference. |
| failure | String allocation can throw and propagates. |
| cost | Formats every listed field with stream operations; only reached on candidate/transition assertion diagnostics. |
| Design | tests/unit/runtime_observation_test.cpp:296, docs/observability.md:71 |

## B0056

[Lines 321–328](../../../../../tests/unit/runtime_observation_test.cpp#L321); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_physical_metrics(const PhysicalMetrics& left, const PhysicalMetrics& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all PhysicalMetrics fields when requiring mode-independent mandatory coordinator accounting. |
| inputs / outputs | Takes two const PhysicalMetrics refs; returns bool. |
| invariants | Compares work and source/alias/derivation/crossing/constraint counts. |
| ownership | Borrows two value objects. |
| failure | No expected failure except assertion at caller. |
| cost | Fixed scalar comparisons. |
| Design | tests/unit/runtime_observation_test.cpp:321, docs/observability.md:71 |

## B0058

[Lines 330–335](../../../../../tests/unit/runtime_observation_test.cpp#L330); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const MetricDescriptor& descriptor(MetricId id) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a metric descriptor by typed MetricId in the observation registry. |
| inputs / outputs | Takes MetricId; returns const reference to descriptor. |
| invariants | Throws if registry omits the requested declared ID; no copied descriptor fallback. |
| ownership | Returns registry-owned borrowed descriptor; caller must not outlive registry storage. |
| failure | Missing ID throws runtime_error. |
| cost | Linear scan over fixed metric registry. |
| Design | tests/unit/runtime_observation_test.cpp:330, docs/observability.md:71 |

## B0060

[Lines 337–358](../../../../../tests/unit/runtime_observation_test.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_registry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check registry completeness, ID ordering, accounting scope and inclusive/exclusive semantics. |
| inputs / outputs | No inputs; reads observation_registry and selected descriptors. |
| invariants | IDs are contiguous; support.work is mandatory support attempt scope; inclusive=successfully charged support plus exclusive while exclusive excludes support. |
| ownership | Registry references borrowed only during checks. |
| failure | Mismatch fails with runtime_error through check(). |
| cost | Fixed registry iteration and descriptor lookups; no actual observation attempt. |
| Design | tests/unit/runtime_observation_test.cpp:337, docs/observability.md:71 |

## B0062

[Lines 360–367](../../../../../tests/unit/runtime_observation_test.cpp#L360); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view availability_name(MetricAvailability availability) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render MetricAvailability as its stable diagnostic spelling. |
| inputs / outputs | Takes enum; returns string_view into static literals. |
| invariants | Covers unavailable/disabled/available and provides unknown for an invalid enum representation. |
| ownership | Returned view refers to static storage, no ownership transfer. |
| failure | No expected exception. |
| cost | Small switch; no allocation. |
| Design | tests/unit/runtime_observation_test.cpp:360, docs/observability.md:71 |

## B0064

[Lines 369–386](../../../../../tests/unit/runtime_observation_test.cpp#L369); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_metric(const ObservationSummary& summary, MetricId id,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a metric has the expected availability and compare value only when available. |
| inputs / outputs | Takes ObservationSummary, MetricId, availability, expected uint64, and label. |
| invariants | Nonavailable numeric scratch payload is deliberately not asserted; mismatch diagnostics include descriptor name and both availability/value views. |
| ownership | Borrows summary/label and registry descriptor; constructs owning diagnostic only on mismatch. |
| failure | Mismatch throws runtime_error; expected value is ignored for disabled/unavailable metrics. |
| cost | One registry lookup and scalar compare on success; formatting cost is failure-only. |
| Design | tests/unit/runtime_observation_test.cpp:369, docs/observability.md:71 |

## B0066

[Lines 388–428](../../../../../tests/unit/runtime_observation_test.cpp#L388); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_q_state(const SupportSnapshot& state, std::uint64_t sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert the full Q support before/after state representation, including records, survivors, parent/E keys and child presence. |
| inputs / outputs | Takes SupportSnapshot, expected sequence, and answer bool. |
| invariants | Answer=true has root R(7,9), child S(9), satisfied count1, survivor/parent/visible key values; false requires rolled-back root flags, empty E and no child state. |
| ownership | Borrows snapshot; snapshot owns copied rows/vectors for the assertion duration. |
| failure | Shape/value mismatch fails assertion. |
| cost | Scans the fixture snapshot and compares owning rows; this validates state, not runtime allocation cost. |
| Design | tests/unit/runtime_observation_test.cpp:388, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0068

[Lines 430–439](../../../../../tests/unit/runtime_observation_test.cpp#L430); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_q_initial_physical(const PhysicalSnapshot& state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert initial physical source and support state before Q publication. |
| inputs / outputs | Takes PhysicalSnapshot and expected initial Database. |
| invariants | Requires sequence0, same physical tables, false Q state, and exactly initial R derivation with no S derivation. |
| ownership | Borrows values; snapshot/database own copied rows. |
| failure | Any before-state mutation fails. |
| cost | Compares the small initial fixture; no work limit or CPU claim. |
| Design | tests/unit/runtime_observation_test.cpp:430, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0070

[Lines 441–463](../../../../../tests/unit/runtime_observation_test.cpp#L441); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_constraint_q_rollback(const PhysicalSnapshot& state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert constraint-heavy budget rollback preserves all 100 prior S rows and omits staged S(9). |
| inputs / outputs | Takes PhysicalSnapshot and ConstraintQFixture. |
| invariants | Sequence/source/support stay at zero; R remains unsatisfied; child record/survivor/parent-key counts are 100 and no tuple is row(9). |
| ownership | Borrows original fixture and rollback snapshot; does not mutate either. |
| failure | Called only after resource-limit rejection; shape changes fail the test. |
| cost | Checks 100 child records; this inspects rollback state and is separate from charged work. |
| Design | tests/unit/runtime_observation_test.cpp:441, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0072

[Lines 465–495](../../../../../tests/unit/runtime_observation_test.cpp#L465); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_q_journal(const SupportEpoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin the seven mandatory support journal records and their exact Q insertion causes. |
| inputs / outputs | Takes SupportEpoch const ref. |
| invariants | Requires journal sequence/current sequence, 7 records, no events; inserted S records caused by 1, root survivor/parent/visible by2, and root child flag transition false→true by2. |
| ownership | Borrows immutable epoch journal for validation. |
| failure | Missing/wrong record or before/after values fails check(). |
| cost | Scans at most seven journal records for key/cause matches; journal record count is an abstract change count, not output rows. |
| Design | tests/unit/runtime_observation_test.cpp:465, docs/observability.md:71, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0074

[Lines 497–512](../../../../../tests/unit/runtime_observation_test.cpp#L497); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_observation_header(const ObservationSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an admitted observation snapshot header for mode, mandatory marker, owner, last attempt and lifetime totals. |
| inputs / outputs | Takes snapshot, expected mode/sequence/layer/owner. |
| invariants | Requires committed last attempt with nonzero attempt, attempts&gt;=last attempt, commits&gt;0, aborts=0, no dropped saturation. |
| ownership | Snapshot is value-owned; no runtime state is borrowed after call. |
| failure | Any nonordinary lifecycle status fails. |
| cost | Fixed scalar checks. |
| Design | tests/unit/runtime_observation_test.cpp:497, docs/observability.md:71 |

## B0076

[Lines 514–554](../../../../../tests/unit/runtime_observation_test.cpp#L514); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_q_physical_observation(const ObservationSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exact Q observation values and availability for off/counters/timed/trace modes. |
| inputs / outputs | Takes ObservationSnapshot, mode and runtime owner. |
| invariants | Off publishes no attempts; enabled modes check support40, reverse visits1, native visits2, physical inclusive44/exclusive4, explicit zeros, unentered delta unavailable, and trace disposition by mode. |
| ownership | Borrows snapshot and registry descriptors; no mutation. |
| failure | Missing/wrong metric availability or trace state fails; unavailable scratch value is not asserted. |
| cost | Fixed metric lookups; totals describe abstract update work, while optional timing is separate from CPU. |
| Design | tests/unit/runtime_observation_test.cpp:514, docs/observability.md:71 |

## B0078

[Lines 556–561](../../../../../tests/unit/runtime_observation_test.cpp#L556); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalModeRun {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return grouped physical-mode evidence from one Q mutation run. |
| inputs / outputs | Owns SupportMetrics, PhysicalMetrics, size_t C++ new count, and ObservationTrace as value fields. |
| invariants | Defaults trace value empty; direct/insertion replay and selected trace runs fill actual update metrics/call count/trace. |
| ownership | Value owns trace records; contains no runtime reference or borrowed storage. |
| failure | Construction/moves can fail only through member operations; no custom failure path. |
| cost | Struct is test result storage; trace copy/move and counters are not measured mutation cost. |
| Design | tests/unit/runtime_observation_test.cpp:556, docs/observability.md:71, docs/observability.md:126 |

## B0080

[Lines 563–685](../../../../../tests/unit/runtime_observation_test.cpp#L563); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalModeRun run_q_physical_mode(ObservationMode mode, BuildMethod method,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the literal Q update under one observation mode and return its actual work/allocation/trace evidence. |
| inputs / outputs | Parameters select mode, direct/replay initialization, trace capacity and sampling; returns PhysicalModeRun. |
| invariants | Checks init is not an update; applies S(9), validates support40/physical44/journal/state/A04 {7}; trace mode validates exact causal event kinds; then duplicate S(9) is zero-work no-op with correct mode sampling. |
| ownership | Runtime/epochs/cursors live through function; returned trace owns numeric records, not tuple strings or runtime. |
| failure | Work/constraint and serializer errors propagate; duplicate no-op must not change state. |
| cost | count_during covers only runtime.apply(update); expected evaluation, result drain, trace copy and duplicate update are outside the measured action; new-call count is not byte/CPU/account usage. |
| Design | tests/unit/runtime_observation_test.cpp:563, docs/observability.md:71, docs/result_cursors.md:101, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0082

[Lines 687–709](../../../../../tests/unit/runtime_observation_test.cpp#L687); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_q_observation_modes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare mandatory Q metrics and C++ new-call counts across off/counters/timed/trace and both build methods. |
| inputs / outputs | No parameters; invokes run_q_physical_mode for each BuildMethod and ObservationMode. |
| invariants | Each mode must have identical SupportMetrics/PhysicalMetrics and allocation count to baseline; trace sequence 1 is selected under period2/offset1. |
| ownership | PhysicalModeRun baseline owns copied values only. |
| failure | Assertion failure reports a mode-dependent counter/allocation or missing trace. |
| cost | Runs eight fixture/update cases; allocation is a C++ replacement-new count during apply only, not a global no-heap claim. |
| Design | tests/unit/runtime_observation_test.cpp:687, docs/observability.md:71, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0084

[Lines 711–789](../../../../../tests/unit/runtime_observation_test.cpp#L711); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_direct_support_modes_and_allocations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare direct SupportRuntime update, exact work40 state and no-op behavior across all observation modes. |
| inputs / outputs | No parameters; loops four modes and emits no report. |
| invariants | Seed R then insert S(9); metrics/state/journal/A04 match; off suppresses attempt history; enabled modes expose support40 and physical unavailable; duplicate insert/absent erase each zero work/no journal and no mode-added counted allocations. |
| ownership | SupportRuntime owns its fixture state; drained rows/epoch are copied values; count probe surrounds successful update or each no-op separately. |
| failure | Expected runtime errors propagate; any work/journal/mode allocation change fails. |
| cost | Compares C++ new call counts around action scopes only; does not require zero baseline allocations and direct malloc/syscalls are invisible. |
| Design | tests/unit/runtime_observation_test.cpp:711, docs/observability.md:71, docs/result_cursors.md:101, docs/verification/o07-observation-test-proposal/README.md:11 |

## B0086

[Lines 791–1083](../../../../../tests/unit/runtime_observation_test.cpp#L791); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_work_limit_boundaries_and_rollback_allocations() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise support/physical/nested-support/constraint charge failures plus explicit rollback across four modes and compare new-call counts. |
| inputs / outputs | No params; constructs separate runtimes for support cap39, physical cap43, nested support cap39, constraint coordinator cap130, and cancellation. |
| invariants | Support40 and physical44 endpoints are independently successful elsewhere; rejected operations preserve committed state; incomplete nested charge makes physical inclusive/exclusive unavailable; constraint prefix is 1+102+1+1+1+1=107 and budget130 fails when support40 is charged; rollback has completed 40 or44 scope as asserted. |
| ownership | Prepared epoch owns private mutations until rollback; runtime retains committed before-state; snapshots/observation values copied for assertions. |
| failure | Each boundary expects resource_limit; off records no attempt, other modes record aborted attempt; trace ends abort where enabled. |
| cost | count_during wraps apply or begin/stage/rollback actions; it compares request counts across modes, not zero allocation, bytes, MemoryAccount usage, CPU or direct syscalls. |
| Design | tests/unit/runtime_observation_test.cpp:791, docs/observability.md:71, docs/verification/o07-observation-test-proposal/README.md:20 |

## B0088

[Lines 1085–1096](../../../../../tests/unit/runtime_observation_test.cpp#L1085); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTrace run_q_trace_capacity(std::size_t capacity) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run and return an actual Q trace for a selected capacity. |
| inputs / outputs | Takes capacity; configures trace mode, work caps 40/44, applies one S(9) update, returns ObservationTrace by value. |
| invariants | Sequence1 is selected by default period1/offset0; trace owns copied records. |
| ownership | Local runtime dies on return; returned records survive independently. |
| failure | Apply/trace copy failures propagate. |
| cost | One update plus trace capture; record capacity bounds retained numeric rows, not total capture allocation/CPU. |
| Design | tests/unit/runtime_observation_test.cpp:1085, docs/observability.md:126 |

## B0090

[Lines 1098–1166](../../../../../tests/unit/runtime_observation_test.cpp#L1098); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_trace_caps_sampling_and_release() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check trace full/zero/one/exact capacities, sampling, aborted terminal retention and copy beyond runtime lifetime. |
| inputs / outputs | No params; runs Q trace helper repeatedly and captures one aborted pending scope. |
| invariants | Capacity0/1 report exact dropped counts, exact-full preserves commit; period2/offset1 selects seq1 and omits seq2 duplicate; rollback trace ends abort and retained numeric records survive runtime destruction. |
| ownership | ObservationTrace owns numeric records and snapshot; it contains IDs/enums rather than row pointers or tuple values. |
| failure | Trace loss is an expected disposition, not exception; update/trace failures propagate. |
| cost | Creates/copies trace vectors outside mutation counts; capacity bounds retained record count only, not whole process heap/CPU. |
| Design | tests/unit/runtime_observation_test.cpp:1098, docs/observability.md:126, docs/observability.md:182 |

## B0091

[Lines 1167–1170](../../../../../tests/unit/runtime_observation_test.cpp#L1167); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t injected_clock_calls = 0;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a deterministic test clock state for checking when optional observation timing reads occur. |
| inputs / outputs | The adjacent \`counting_clock()\` increments the call count, advances a synthetic counter by 10, and returns it; \`reset_clock()\` installs it through the \`CROWN_RUNTIME_TESTING\` setter. The caller checks off/counters and trace-without-timings avoid reads, while timed/trace reads reconcile with counters. |
| invariants | The callback is \`noexcept\` and this fixture uses small bounded call counts; returned increments are synthetic ticks, not wall-clock duration or CPU time. |
| ownership | The scalar state and setter are test-only and require exclusive test use. The callback owns no runtime or observation buffer. |
| failure | No exception is thrown by the callback. The testing setter is available only under \`CROWN_RUNTIME_TESTING\`; production builds use the normal steady clock. |
| cost | Each injected read is an integer increment only. The read count tests optional clock behavior; it does not quantify work time or production overhead. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [include/crown/runtime/observation.hpp §test clock hook](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp §clock gate and read](../../../../../src/runtime/observation.cpp), [tests/unit/runtime_observation_test.cpp §test_optional_clock_reads](../../../../../tests/unit/runtime_observation_test.cpp) |

## B0092

[Lines 1171–1175](../../../../../tests/unit/runtime_observation_test.cpp#L1171); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t counting_clock() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a deterministic noexcept clock that counts reads and advances by ten per call. |
| inputs / outputs | No input; returns updated uint64 clock value. |
| invariants | Each call increments injected_clock_calls once and returns prior value+10. |
| ownership | Uses test-global scalar state and no runtime-owned clock object. |
| failure | No throw; noexcept. |
| cost | Constant scalar operations, test-only; clock values are synthetic durations, not CPU. |
| Design | tests/unit/runtime_observation_test.cpp:1171, docs/observability.md:71 |

## B0094

[Lines 1177–1181](../../../../../tests/unit/runtime_observation_test.cpp#L1177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reset_clock() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset deterministic clock counters and install the test callback. |
| inputs / outputs | No input/result; zeros call/value globals and installs counting_clock. |
| invariants | Must occur after each test mode setup so counters measure only subsequent observation reads. |
| ownership | Mutates global test hook; ClockReset removes it at scope exit. |
| failure | No throw; noexcept. |
| cost | Few scalar writes and hook update. |
| Design | tests/unit/runtime_observation_test.cpp:1177, docs/observability.md:71 |

## B0096

[Lines 1183–1185](../../../../../tests/unit/runtime_observation_test.cpp#L1183); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ClockReset {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use RAII to remove the test clock callback at scope exit. |
| inputs / outputs | Type has no data; destructor resets callback to null. |
| invariants | Normal and exceptional exits both clear injected clock state. |
| ownership | Stack-owned guard borrows no data; does not own runtime. |
| failure | Destructor is implicitly noexcept; no expected failure. |
| cost | One hook reset at scope exit. |
| Design | tests/unit/runtime_observation_test.cpp:1183, docs/observability.md:71 |

## B0098

[Lines 1187–1265](../../../../../tests/unit/runtime_observation_test.cpp#L1187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_optional_clock_reads() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify optional delta clock behavior in all modes and with trace timings disabled. |
| inputs / outputs | No params; initializes ordered-replay DeltaRuntime per mode, applies Q update, drains one signed result, checks summary. |
| invariants | Off/counters invoke no optional clock; timed/trace do; nested cursor and delta reads sum to injected calls; support/physical work remain40/44; trace_timings=false keeps trace but clock reads0 and timing disabled. |
| ownership | ClockReset owns hook cleanup; delta epoch/result and ObservationSnapshot own their values. |
| failure | Runtime errors propagate; missing work/clock observations fail check. |
| cost | Measures fake clock invocation counts only; deterministic +10 timestamps are not elapsed CPU, nested timing intervals are not additive. |
| Design | tests/unit/runtime_observation_test.cpp:1187, docs/observability.md:71, docs/result_cursors.md:101 |

## B0100

[Lines 1267–1369](../../../../../tests/unit/runtime_observation_test.cpp#L1267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_multi_alias_generalized_projection() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one source table aliased twice in generalized projection across all modes. |
| inputs / outputs | No params; applies edge(3,3,"edge") to AliasFixture and compares A04 relation/state/metrics. |
| invariants | Two aliases visited, one physical source change, two derivations, one candidate and three E transitions, one projected result row; mode does not change mandatory metrics or apply-window new count. |
| ownership | AliasFixture owns plan; runtime owns committed source/support; snapshot and diagnostic metrics copied for check. |
| failure | Any relation/state/counter divergence or allocation delta fails. |
| cost | Count probe wraps only runtime.apply; C++ new calls compared, while output/reference snapshots outside window; not a no-allocation/byte-cost theorem. |
| Design | tests/unit/runtime_observation_test.cpp:1267, docs/observability.md:71, docs/verification/o07-observation-test-proposal/README.md:20 |

## B0102

[Lines 1371–1420](../../../../../tests/unit/runtime_observation_test.cpp#L1371); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void test_session_retained_summary() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check QuerySession retains committed observation summary after draining, stopping and dropping runtime trace rows. |
| inputs / outputs | No parameters; creates input JSON stream/session, steps one prepared Q event, commits and drains signed output. |
| invariants | Output is insert row7; retained summary/session sequence remains committed at1 after drop; observation_trace changes to released and records become empty while summary remains. |
| ownership | Session owns input stream/runtime/retained summary; returned trace is value copy and owns records while held. |
| failure | Session state/input/commit errors propagate; expected trace release is a value-state transition. |
| cost | Runs one session update and trace capture; no operator-new count window or CPU assertion. |
| Design | tests/unit/runtime_observation_test.cpp:1371, docs/observability.md:126, docs/memory_accounts.md:722 |

## B0103

[Lines 1421–1423](../../../../../tests/unit/runtime_observation_test.cpp#L1421); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1421-L1423:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_observation_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_observation_test.cpp](../../../../../tests/unit/runtime_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0104

[Lines 1424–1433](../../../../../tests/unit/runtime_observation_test.cpp#L1424); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
void run_scenario(std::string_view name, Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a named scenario and add its name to any propagated exception for test diagnostics. |
| inputs / outputs | Accepts borrowed name and forwarding callable; returns void. |
| invariants | Prints start/PASS markers only on success; wraps standard exceptions as runtime_error(name + error.what()). |
| ownership | Borrows name/callable during call; error text becomes owning string only on failure. |
| failure | Any std::exception from scenario is rethrown with scenario name; non-std exception propagates unchanged. |
| cost | Two short output writes plus one scenario invocation; name formatting occurs only on failure. |
| Design | tests/unit/runtime_observation_test.cpp:1424 |

## B0106

[Lines 1435–1450](../../../../../tests/unit/runtime_observation_test.cpp#L1435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the seven named runtime observation scenarios and return process status. |
| inputs / outputs | No args; calls Q modes, direct support, budget rollback, trace caps, clocks, aliases and session checks. |
| invariants | Returns 0 only after every group; catches std::exception at top and prints error then returns1. |
| ownership | Each scenario owns its runtime/fixture; main owns only execution sequence and streams. |
| failure | First failing scenario aborts later groups; process-level diagnostics preserve its scenario name. |
| cost | Executes all runtime tests; allocation and clock claims apply only to the explicitly instrumented scopes, not the process globally. |
| Design | tests/unit/runtime_observation_test.cpp:1435, [CMakeLists.txt](../../../../../CMakeLists.txt), docs/observability.md:71, docs/verification/o07-observation-test-proposal/README.md:11 |
