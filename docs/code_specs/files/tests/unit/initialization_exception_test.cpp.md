# `tests/unit/initialization_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/initialization_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fedb755bdd0312e8221bce5559076b8dc49c85c7f7f914074913ca53dd8e09e1`. 1209 lines partitioned into 134 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–32](../../../../../tests/unit/initialization_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Keep allocation failures armed while unpublished runtime state and owned · [reviewed contract](#b0001) |
| [B0002 · 33–42](../../../../../tests/unit/initialization_exception_test.cpp#L33) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::max, std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 43–43](../../../../../tests/unit/initialization_exception_test.cpp#L43) | Explanatory comments or spacing. |  |
| [B0004 · 44–50](../../../../../tests/unit/initialization_exception_test.cpp#L44) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0004) |
| [B0005 · 51–52](../../../../../tests/unit/initialization_exception_test.cpp#L51) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 53–53](../../../../../tests/unit/initialization_exception_test.cpp#L53) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 54–54](../../../../../tests/unit/initialization_exception_test.cpp#L54) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 55–55](../../../../../tests/unit/initialization_exception_test.cpp#L55) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 56–56](../../../../../tests/unit/initialization_exception_test.cpp#L56) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 57–57](../../../../../tests/unit/initialization_exception_test.cpp#L57) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 58–58](../../../../../tests/unit/initialization_exception_test.cpp#L58) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 59–69](../../../../../tests/unit/initialization_exception_test.cpp#L59) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;PhysicalRuntime&gt;); · [reviewed contract](#b0012) |
| [B0013 · 70–72](../../../../../tests/unit/initialization_exception_test.cpp#L70) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0013) |
| [B0014 · 73–73](../../../../../tests/unit/initialization_exception_test.cpp#L73) | Explanatory comments or spacing. |  |
| [B0015 · 74–84](../../../../../tests/unit/initialization_exception_test.cpp#L74) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0015) |
| [B0016 · 85–85](../../../../../tests/unit/initialization_exception_test.cpp#L85) | Explanatory comments or spacing. |  |
| [B0017 · 86–86](../../../../../tests/unit/initialization_exception_test.cpp#L86) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0017) |
| [B0018 · 87–87](../../../../../tests/unit/initialization_exception_test.cpp#L87) | Callable definition: Value s(std::string value) | calls ; returns value · [reviewed contract](#b0018) |
| [B0019 · 88–88](../../../../../tests/unit/initialization_exception_test.cpp#L88) | Explanatory comments or spacing. |  |
| [B0020 · 89–107](../../../../../tests/unit/initialization_exception_test.cpp#L89) | Callable definition: PhysicalPlan make_plan() | calls n, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0020) |
| [B0021 · 108–108](../../../../../tests/unit/initialization_exception_test.cpp#L108) | Explanatory comments or spacing. |  |
| [B0022 · 109–121](../../../../../tests/unit/initialization_exception_test.cpp#L109) | Callable definition: Database make_database() | calls n, s; returns {{Relation{ · [reviewed contract](#b0022) |
| [B0023 · 122–122](../../../../../tests/unit/initialization_exception_test.cpp#L122) | Explanatory comments or spacing. |  |
| [B0024 · 123–126](../../../../../tests/unit/initialization_exception_test.cpp#L123) | Callable definition: const Database& database() | calls make_database; returns value · [reviewed contract](#b0024) |
| [B0025 · 127–127](../../../../../tests/unit/initialization_exception_test.cpp#L127) | Explanatory comments or spacing. |  |
| [B0026 · 128–130](../../../../../tests/unit/initialization_exception_test.cpp#L128) | Callable definition: bool same_database(const Database& left, const Database& right) | calls ; returns left.tables == right.tables · [reviewed contract](#b0026) |
| [B0027 · 131–131](../../../../../tests/unit/initialization_exception_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0028 · 132–132](../../../../../tests/unit/initialization_exception_test.cpp#L132) | Callable definition: PhysicalRuntimeOptions physical_options() | calls ; returns {} · [reviewed contract](#b0028) |
| [B0029 · 133–133](../../../../../tests/unit/initialization_exception_test.cpp#L133) | Explanatory comments or spacing. |  |
| [B0030 · 134–140](../../../../../tests/unit/initialization_exception_test.cpp#L134) | Callable definition: DeltaOptions delta_options() | calls ; returns result · [reviewed contract](#b0030) |
| [B0031 · 141–141](../../../../../tests/unit/initialization_exception_test.cpp#L141) | Explanatory comments or spacing. |  |
| [B0032 · 142–146](../../../../../tests/unit/initialization_exception_test.cpp#L142) | Callable definition: BuildOptions build_options(BuildMethod method) | calls ; returns result · [reviewed contract](#b0032) |
| [B0033 · 147–147](../../../../../tests/unit/initialization_exception_test.cpp#L147) | Explanatory comments or spacing. |  |
| [B0034 · 148–151](../../../../../tests/unit/initialization_exception_test.cpp#L148) | Callable definition: PhysicalSetUpdate prefix_update() | calls n, s; returns {1, TableId{0}, SetOperation::insert,; growth insert · [reviewed contract](#b0034) |
| [B0035 · 152–152](../../../../../tests/unit/initialization_exception_test.cpp#L152) | Explanatory comments or spacing. |  |
| [B0036 · 153–156](../../../../../tests/unit/initialization_exception_test.cpp#L153) | Callable definition: PhysicalSetUpdate suffix_update(std::uint64_t sequence) | calls n, s; returns {sequence, TableId{0}, SetOperation::insert,; growth insert · [reviewed contract](#b0036) |
| [B0037 · 157–157](../../../../../tests/unit/initialization_exception_test.cpp#L157) | Explanatory comments or spacing. |  |
| [B0038 · 158–163](../../../../../tests/unit/initialization_exception_test.cpp#L158) | Callable definition: std::set&lt;Row&gt; collect_results(PhysicalRuntime& runtime) | calls results, next, insert, crown::storage::export_row; returns result; growth insert; 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 164–164](../../../../../tests/unit/initialization_exception_test.cpp#L164) | Explanatory comments or spacing. |  |
| [B0040 · 165–170](../../../../../tests/unit/initialization_exception_test.cpp#L165) | Callable definition: std::set&lt;Row&gt; collect_results(DeltaRuntime& runtime) | calls results, next, insert, crown::storage::export_row; returns result; growth insert; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 171–171](../../../../../tests/unit/initialization_exception_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0042 · 172–177](../../../../../tests/unit/initialization_exception_test.cpp#L172) | Type/record definition: struct OutputImage |  · [reviewed contract](#b0042) |
| [B0043 · 178–178](../../../../../tests/unit/initialization_exception_test.cpp#L178) | Explanatory comments or spacing. |  |
| [B0044 · 179–185](../../../../../tests/unit/initialization_exception_test.cpp#L179) | Callable definition: std::vector&lt;OutputImage&gt; drain(DeltaRuntime::Epoch& epoch) | calls next, push_back, crown::storage::export_row, values; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0044) |
| [B0045 · 186–186](../../../../../tests/unit/initialization_exception_test.cpp#L186) | Explanatory comments or spacing. |  |
| [B0046 · 187–193](../../../../../tests/unit/initialization_exception_test.cpp#L187) | Type/record definition: struct SupportProbe |  · [reviewed contract](#b0046) |
| [B0047 · 194–194](../../../../../tests/unit/initialization_exception_test.cpp#L194) | Explanatory comments or spacing. |  |
| [B0048 · 195–200](../../../../../tests/unit/initialization_exception_test.cpp#L195) | Type/record definition: struct SourceProbe |  · [reviewed contract](#b0048) |
| [B0049 · 201–201](../../../../../tests/unit/initialization_exception_test.cpp#L201) | Explanatory comments or spacing. |  |
| [B0050 · 202–206](../../../../../tests/unit/initialization_exception_test.cpp#L202) | Type/record definition: struct PublicHandles |  · [reviewed contract](#b0050) |
| [B0051 · 207–207](../../../../../tests/unit/initialization_exception_test.cpp#L207) | Explanatory comments or spacing. |  |
| [B0052 · 208–232](../../../../../tests/unit/initialization_exception_test.cpp#L208) | Callable definition: std::vector&lt;SupportProbe&gt; support_handles(const SupportSnapshot& snapshot, PhysicalRuntime& runtime) | calls find_support, check, has_value, get_support; guard check(handle.has_value(), "initialized support row has no public handle");; returns result; growth push_back; 5 loop sites · [reviewed contract](#b0052) |
| [B0053 · 233–233](../../../../../tests/unit/initialization_exception_test.cpp#L233) | Explanatory comments or spacing. |  |
| [B0054 · 234–250](../../../../../tests/unit/initialization_exception_test.cpp#L234) | Callable definition: PublicHandles public_handles(PhysicalRuntime& runtime) | calls snapshot, size, find_source, check; guard check(handle.has_value(), "initialized source row has no public handle");; returns result; growth push_back; 2 loop sites · [reviewed contract](#b0054) |
| [B0055 · 251–251](../../../../../tests/unit/initialization_exception_test.cpp#L251) | Explanatory comments or spacing. |  |
| [B0056 · 252–262](../../../../../tests/unit/initialization_exception_test.cpp#L252) | Callable definition: std::vector&lt;SupportHandle&gt; support_handles(const PhysicalSnapshot& snapshot) | calls push_back; returns result; growth push_back; 4 loop sites · [reviewed contract](#b0056) |
| [B0057 · 263–263](../../../../../tests/unit/initialization_exception_test.cpp#L263) | Explanatory comments or spacing. |  |
| [B0058 · 264–268](../../../../../tests/unit/initialization_exception_test.cpp#L264) | Callable definition: void check_public_handles(PhysicalRuntime& runtime, const PublicHandles& expected) | calls check, public_handles; guard check(public_handles(runtime) == expected, · [reviewed contract](#b0058) |
| [B0059 · 269–269](../../../../../tests/unit/initialization_exception_test.cpp#L269) | Explanatory comments or spacing. |  |
| [B0060 · 270–272](../../../../../tests/unit/initialization_exception_test.cpp#L270) | Callable definition: std::vector&lt;SupportHandle&gt; delta_support_handles(DeltaRuntime& runtime) | calls support_handles, snapshot; returns support_handles(runtime.snapshot()) · [reviewed contract](#b0060) |
| [B0061 · 273–273](../../../../../tests/unit/initialization_exception_test.cpp#L273) | Explanatory comments or spacing. |  |
| [B0062 · 274–283](../../../../../tests/unit/initialization_exception_test.cpp#L274) | Callable definition: void check_physical_state(PhysicalRuntime& runtime, const CanonicalPhysicalState& expected, std::uint64_t sequence) | calls check, ready, sequence, canonical_state; guard check(runtime.ready() && runtime.sequence() == sequence, · [reviewed contract](#b0062) |
| [B0063 · 284–284](../../../../../tests/unit/initialization_exception_test.cpp#L284) | Explanatory comments or spacing. |  |
| [B0064 · 285–295](../../../../../tests/unit/initialization_exception_test.cpp#L285) | Callable definition: void check_delta_state(DeltaRuntime& runtime, const CanonicalDeltaState& expected, std::uint64_t sequence, DeltaMode mode) | calls check, ready, sequence, mode; guard check(runtime.ready() && runtime.sequence() == sequence && · [reviewed contract](#b0064) |
| [B0065 · 296–296](../../../../../tests/unit/initialization_exception_test.cpp#L296) | Explanatory comments or spacing. |  |
| [B0066 · 297–300](../../../../../tests/unit/initialization_exception_test.cpp#L297) | Type/record definition: struct SweepStats |  · [reviewed contract](#b0066) |
| [B0067 · 301–304](../../../../../tests/unit/initialization_exception_test.cpp#L301) | Explanatory comments or spacing. | source comment (unverified): // Calibrate the successful operation's allocation count, then inject each · [reviewed contract](#b0067) |
| [B0068 · 305–354](../../../../../tests/unit/initialization_exception_test.cpp#L305) | Callable definition: template &lt;class Context, class Result, class Prepare, class Invoke, class CheckSuccess, class CheckFailure&gt; SweepStats sweep_allo… | calls prepare, invoke, check_success, check; guard check(successful_allocation_calls &lt;; returns {failures, successful_allocation_calls}; growth emplace; 1 loop sites; source comment (unverified): // Calibrate the successful operation's allocation count, then inject each · [reviewed contract](#b0068) |
| [B0069 · 355–355](../../../../../tests/unit/initialization_exception_test.cpp#L355) | Explanatory comments or spacing. |  |
| [B0070 · 356–388](../../../../../tests/unit/initialization_exception_test.cpp#L356) | Callable definition: void check_build_metrics(std::string_view label, const BuildMetrics& metrics, BuildMethod method, bool expect_live) | calls check, std::string; guard check(metrics.work &gt; 0 && metrics.source_rows &gt; 0 && · [reviewed contract](#b0070) |
| [B0071 · 389–389](../../../../../tests/unit/initialization_exception_test.cpp#L389) | Explanatory comments or spacing. |  |
| [B0072 · 390–390](../../../../../tests/unit/initialization_exception_test.cpp#L390) | Type/record definition: struct PhysicalInitAttempt |  · [reviewed contract](#b0072) |
| [B0073 · 391–391](../../../../../tests/unit/initialization_exception_test.cpp#L391) | Explanatory comments or spacing. |  |
| [B0074 · 392–425](../../../../../tests/unit/initialization_exception_test.cpp#L392) | Callable definition: void sweep_physical_initialization(BuildMethod method) | calls build_options, make_plan, PhysicalRuntime::initialize, std::move; guard check(runtime.ready() && runtime.sequence() == 0,; returns PhysicalInitAttempt{make_plan()}; PhysicalRuntime::initialize(std::move(context.plan), database(), · [reviewed contract](#b0074) |
| [B0075 · 426–426](../../../../../tests/unit/initialization_exception_test.cpp#L426) | Explanatory comments or spacing. |  |
| [B0076 · 427–427](../../../../../tests/unit/initialization_exception_test.cpp#L427) | Type/record definition: struct DeltaInitAttempt |  · [reviewed contract](#b0076) |
| [B0077 · 428–428](../../../../../tests/unit/initialization_exception_test.cpp#L428) | Explanatory comments or spacing. |  |
| [B0078 · 429–467](../../../../../tests/unit/initialization_exception_test.cpp#L429) | Callable definition: void sweep_delta_initialization(BuildMethod method) | calls build_options, delta_options, make_plan, DeltaRuntime::initialize; guard check(runtime.ready() && runtime.sequence() == 0 &&; returns DeltaInitAttempt{make_plan()}; DeltaRuntime::initialize(std::move(context.plan), database(), option… · [reviewed contract](#b0078) |
| [B0079 · 468–468](../../../../../tests/unit/initialization_exception_test.cpp#L468) | Explanatory comments or spacing. |  |
| [B0080 · 469–483](../../../../../tests/unit/initialization_exception_test.cpp#L469) | Type/record definition: struct PhysicalRebuildAttempt |  · [reviewed contract](#b0080) |
| [B0081 · 484–484](../../../../../tests/unit/initialization_exception_test.cpp#L484) | Explanatory comments or spacing. |  |
| [B0082 · 485–543](../../../../../tests/unit/initialization_exception_test.cpp#L485) | Callable definition: void sweep_physical_rebuild(BuildMethod method) | calls build_options, rebuilt, check_physical_state, check_public_handles; guard check(context.runtime.owner() == context.owner,; returns PhysicalRebuildAttempt{}; context.runtime.rebuilt(build) · [reviewed contract](#b0082) |
| [B0083 · 544–544](../../../../../tests/unit/initialization_exception_test.cpp#L544) | Explanatory comments or spacing. |  |
| [B0084 · 545–561](../../../../../tests/unit/initialization_exception_test.cpp#L545) | Callable definition: bool same_delta_options(const DeltaOptions& left, const DeltaOptions& right) | calls ; returns left.physical.work_limit == right.physical.work_limit && · [reviewed contract](#b0084) |
| [B0085 · 562–562](../../../../../tests/unit/initialization_exception_test.cpp#L562) | Explanatory comments or spacing. |  |
| [B0086 · 563–579](../../../../../tests/unit/initialization_exception_test.cpp#L563) | Type/record definition: struct DeltaRebuildAttempt |  · [reviewed contract](#b0086) |
| [B0087 · 580–580](../../../../../tests/unit/initialization_exception_test.cpp#L580) | Explanatory comments or spacing. |  |
| [B0088 · 581–639](../../../../../tests/unit/initialization_exception_test.cpp#L581) | Callable definition: void sweep_delta_rebuild(BuildMethod method) | calls build_options, rebuilt, check_delta_state, check; guard check(context.runtime.owner() == context.owner &&; returns DeltaRebuildAttempt{}; context.runtime.rebuilt(build); growth insert · [reviewed contract](#b0088) |
| [B0089 · 640–640](../../../../../tests/unit/initialization_exception_test.cpp#L640) | Explanatory comments or spacing. |  |
| [B0090 · 641–676](../../../../../tests/unit/initialization_exception_test.cpp#L641) | Callable definition: void check_late_build_work_failures() | calls PhysicalRuntime::initialize, make_plan, database, physical_options; guard check(physical_work &gt; 1, "physical build fixture has too little cumulative work");; 1 loop sites · [reviewed contract](#b0090) |
| [B0091 · 677–677](../../../../../tests/unit/initialization_exception_test.cpp#L677) | Explanatory comments or spacing. |  |
| [B0092 · 678–682](../../../../../tests/unit/initialization_exception_test.cpp#L678) | Callable definition: PhysicalPlan make_constant_unused_source_plan(const Catalog& catalog) | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0092) |
| [B0093 · 683–683](../../../../../tests/unit/initialization_exception_test.cpp#L683) | Explanatory comments or spacing. |  |
| [B0094 · 684–689](../../../../../tests/unit/initialization_exception_test.cpp#L684) | Callable definition: Database constrained_unused_database() | calls insert, n, std::move; returns {{std::move(rows)}}; growth insert; 1 loop sites · [reviewed contract](#b0094) |
| [B0095 · 690–690](../../../../../tests/unit/initialization_exception_test.cpp#L690) | Explanatory comments or spacing. |  |
| [B0096 · 691–723](../../../../../tests/unit/initialization_exception_test.cpp#L691) | Callable definition: void check_constraint_projection_work_budgets() | calls constrained_unused_database, push_back, std::to_string, std::move; guard check(unlimited.ready() && unlimited.sequence() == 0 &&; growth push_back; 1 loop sites · [reviewed contract](#b0096) |
| [B0097 · 724–726](../../../../../tests/unit/initialization_exception_test.cpp#L724) | declares callable signatures. |  · [reviewed contract](#b0097) |
| [B0098 · 727–753](../../../../../tests/unit/initialization_exception_test.cpp#L727) | Callable definition: void check_rebuild_budget_precedes_large_source_copy() | calls payload, n, s, PhysicalRuntime::initialize; guard check(handle.has_value(), "large-string source row has no public handle"); · [reviewed contract](#b0098) |
| [B0099 · 754–754](../../../../../tests/unit/initialization_exception_test.cpp#L754) | Explanatory comments or spacing. |  |
| [B0100 · 755–773](../../../../../tests/unit/initialization_exception_test.cpp#L755) | Callable definition: void check_exact_support_and_derivation_caps() | calls physical_options, expect_error, PhysicalRuntime::initialize, make_plan; guard check(same_database(database(), make_database()),; 1 loop sites · [reviewed contract](#b0100) |
| [B0101 · 774–774](../../../../../tests/unit/initialization_exception_test.cpp#L774) | Explanatory comments or spacing. |  |
| [B0102 · 775–816](../../../../../tests/unit/initialization_exception_test.cpp#L775) | Callable definition: void check_update_limits_are_separate_from_build_limits() | calls physical_options, PhysicalRuntime::initialize, make_plan, database; guard check(physical.ready() && physical.sequence() == 0 &&; 1 loop sites · [reviewed contract](#b0102) |
| [B0103 · 817–817](../../../../../tests/unit/initialization_exception_test.cpp#L817) | Explanatory comments or spacing. |  |
| [B0104 · 818–838](../../../../../tests/unit/initialization_exception_test.cpp#L818) | Callable definition: PhysicalPlan make_cyclic_fk_plan() | calls push_back, std::move, planner::lower_tree; returns planner::lower_tree(catalog, query, tree); growth push_back · [reviewed contract](#b0104) |
| [B0105 · 839–839](../../../../../tests/unit/initialization_exception_test.cpp#L839) | Explanatory comments or spacing. |  |
| [B0106 · 840–842](../../../../../tests/unit/initialization_exception_test.cpp#L840) | Callable definition: Database cyclic_fk_database() | calls n; returns {{Relation{{n(1), n(10)}}, Relation{{n(10), n(1)}}}} · [reviewed contract](#b0106) |
| [B0107 · 843–843](../../../../../tests/unit/initialization_exception_test.cpp#L843) | Explanatory comments or spacing. |  |
| [B0108 · 844–871](../../../../../tests/unit/initialization_exception_test.cpp#L844) | Callable definition: void check_complete_cyclic_foreign_key_bootstrap() | calls cyclic_fk_database, empty, make_cyclic_fk_plan, expect_error; guard check(empty.ready() && empty.sequence() == 0 &&; growth insert; 1 loop sites · [reviewed contract](#b0108) |
| [B0109 · 872–872](../../../../../tests/unit/initialization_exception_test.cpp#L872) | Explanatory comments or spacing. |  |
| [B0110 · 873–885](../../../../../tests/unit/initialization_exception_test.cpp#L873) | Type/record definition: class OwnedStream final : public std::istringstream |  · [reviewed contract](#b0110) |
| [B0111 · 886–886](../../../../../tests/unit/initialization_exception_test.cpp#L886) | Explanatory comments or spacing. |  |
| [B0112 · 887–895](../../../../../tests/unit/initialization_exception_test.cpp#L887) | Type/record definition: struct SessionInitAttempt | growth make_unique · [reviewed contract](#b0112) |
| [B0113 · 896–896](../../../../../tests/unit/initialization_exception_test.cpp#L896) | Explanatory comments or spacing. |  |
| [B0114 · 897–902](../../../../../tests/unit/initialization_exception_test.cpp#L897) | Callable definition: std::string suffix_input() | calls make_plan, suffix_update, io::write_input_json, source_catalog; returns io::write_input_json(input, plan.source_catalog()) + @ · [reviewed contract](#b0114) |
| [B0115 · 903–903](../../../../../tests/unit/initialization_exception_test.cpp#L903) | Explanatory comments or spacing. |  |
| [B0116 · 904–908](../../../../../tests/unit/initialization_exception_test.cpp#L904) | Callable definition: std::set&lt;Row&gt; snapshot_rows(const SessionSnapshot& snapshot) | calls insert, crown::storage::export_row, values; returns result; growth insert; 1 loop sites · [reviewed contract](#b0116) |
| [B0117 · 909–909](../../../../../tests/unit/initialization_exception_test.cpp#L909) | Explanatory comments or spacing. |  |
| [B0118 · 910–959](../../../../../tests/unit/initialization_exception_test.cpp#L910) | Callable definition: void sweep_initialized_session_creation(BuildMethod method) | calls suffix_input, delta_options, build_options, QuerySession::create; guard check(session != nullptr && !context.stream_destroyed,; returns SessionInitAttempt{bytes}; QuerySession::create(std::move(context.plan), database(), · [reviewed contract](#b0118) |
| [B0119 · 960–960](../../../../../tests/unit/initialization_exception_test.cpp#L960) | Explanatory comments or spacing. |  |
| [B0120 · 961–998](../../../../../tests/unit/initialization_exception_test.cpp#L961) | Callable definition: void check_rebuild_barriers() | calls PhysicalRuntime::initialize, make_plan, database, physical_options; guard check(physical.ready() && physical.sequence() == 0, · [reviewed contract](#b0120) |
| [B0121 · 999–999](../../../../../tests/unit/initialization_exception_test.cpp#L999) | Explanatory comments or spacing. |  |
| [B0122 · 1000–1068](../../../../../tests/unit/initialization_exception_test.cpp#L1000) | Callable definition: void check_no_allocation_moves_and_pin_cleanup() | calls prefix_update, emplace, PhysicalRuntime::initialize, make_plan; guard check(pin-&gt;input.source &&; growth emplace, insert · [reviewed contract](#b0122) |
| [B0123 · 1069–1069](../../../../../tests/unit/initialization_exception_test.cpp#L1069) | Explanatory comments or spacing. |  |
| [B0124 · 1070–1070](../../../../../tests/unit/initialization_exception_test.cpp#L1070) | Type/record definition: struct WriterAttempt |  · [reviewed contract](#b0124) |
| [B0125 · 1071–1071](../../../../../tests/unit/initialization_exception_test.cpp#L1071) | Explanatory comments or spacing. |  |
| [B0126 · 1072–1084](../../../../../tests/unit/initialization_exception_test.cpp#L1072) | Callable definition: template &lt;class Writer&gt; void sweep_writer_allocations(std::string_view label, Writer writer, std::string_view expected_marker) | calls writer, check, find, std::string; guard check(output.find(expected_marker) != std::string::npos,; returns WriterAttempt{}; writer() · [reviewed contract](#b0126) |
| [B0127 · 1085–1085](../../../../../tests/unit/initialization_exception_test.cpp#L1085) | Explanatory comments or spacing. |  |
| [B0128 · 1086–1096](../../../../../tests/unit/initialization_exception_test.cpp#L1086) | Callable definition: PhysicalPlan make_long_string_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0128) |
| [B0129 · 1097–1097](../../../../../tests/unit/initialization_exception_test.cpp#L1097) | Explanatory comments or spacing. |  |
| [B0130 · 1098–1135](../../../../../tests/unit/initialization_exception_test.cpp#L1098) | Callable definition: void check_inspection_writer_failures_and_byte_bound() | calls PhysicalRuntime::initialize, make_plan, database, DeltaRuntime::initialize; guard check(report.valid(), "writer fixture invariant report is not valid");; returns io::write_runtime_state(physical_state); io::write_runtime_state(delta_state) · [reviewed contract](#b0130) |
| [B0131 · 1136–1136](../../../../../tests/unit/initialization_exception_test.cpp#L1136) | Explanatory comments or spacing. |  |
| [B0132 · 1137–1172](../../../../../tests/unit/initialization_exception_test.cpp#L1137) | Callable definition: void check_no_fabricated_input_and_suffix_equivalence() | calls PhysicalRuntime::initialize, make_plan, database, check; guard check(physical.sequence() == 0 && physical.ready() && · [reviewed contract](#b0132) |
| [B0133 · 1173–1175](../../../../../tests/unit/initialization_exception_test.cpp#L1173) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0133) |
| [B0134 · 1176–1209](../../../../../tests/unit/initialization_exception_test.cpp#L1176) | Callable definition: int main() | calls database, sweep_physical_initialization, sweep_delta_initialization, sweep_physical_rebuild; guard check(same_database(database(), original),; returns 1 · [reviewed contract](#b0134) |

## B0001

[Lines 1–32](../../../../../tests/unit/initialization_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L32:sha256:d71dfc10473fb01f83a266fc0f71a3dc96326f829cfcc4a02d653c670610574b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare initialization_exception_test.cpp: include "crown/api/error.hpp", "crown/io/ingest.hpp", "crown/io/inspection.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 33–42](../../../../../tests/unit/initialization_exception_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count and optionally reject calls through this executable’s replaced ordinary C++ new/new\[\] family, using malloc as the backing store. |
| inputs / outputs | Byte size, fail_after, allocation_count and largest_allocation enter; every call increments the count and updates the maximum before either injected bad_alloc or malloc-backed storage. |
| invariants | Zero-sized requests call malloc(1); fail_after==0 throws before malloc; positive fail_after is decremented; malloc null also throws. |
| ownership | Only thread-local counters are borrowed; returned malloc storage is paired with this file’s scalar/array sized or unsized delete. |
| failure | Injection is at the replaced ordinary C++ new/new\[\] boundary. It does not fail raw malloc/realloc or system calls, and does not force MemoryAccount limit denial; aligned/nothrow overloads are not replaced here. |
| cost | One counter/max update and branch plus one malloc on admitted calls; largest_allocation is a requested-size observation, not account bytes, usable size, RSS or syscall cost. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0004

[Lines 44–50](../../../../../tests/unit/initialization_exception_test.cpp#L44); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set or disable the thread-local fail-after position for one scope and expose a zero-point forbidding mode for teardown checks. |
| inputs / outputs | Construction accepts an optional point defaulting to -1; forbid_allocations sets fail_after to zero; destruction resets it to -1. |
| invariants | The scope always disables injection on exit; it is not a nested state-restoring guard. |
| ownership | Owns no product resources and borrows only thread-local scalar state. |
| failure | No failure is thrown by its noexcept operations; while forbidden, any call through the replaced ordinary C++ new/new\[\] family throws before malloc. |
| cost | Constant-time scalar changes. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp) |

## B0005

[Lines 51–52](../../../../../tests/unit/initialization_exception_test.cpp#L51); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L52:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in initialization_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 53–53](../../../../../tests/unit/initialization_exception_test.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary scalar operator new calls through the initialization executable’s counted malloc_new seam. |
| inputs / outputs | A byte count enters; malloc-backed pointer or bad_alloc exits. |
| invariants | Count and largest request size are recorded before fail-after injection. |
| ownership | Storage is released by replacement scalar delete. |
| failure | Selected C++ new calls are injected; raw malloc, account-limit denial and system calls are not. |
| cost | One seam call and one malloc attempt if admitted. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0007

[Lines 54–54](../../../../../tests/unit/initialization_exception_test.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route ordinary array operator new\[\] calls through the same counted malloc_new seam. |
| inputs / outputs | An array byte count enters; malloc-backed pointer or bad_alloc exits. |
| invariants | Shares the scalar fail index, request count and largest-size observation. |
| ownership | Storage is released by replacement array delete. |
| failure | This does not intercept raw malloc or system-call failures and does not synthesize a MemoryAccount limit error. |
| cost | One seam call and one malloc attempt if admitted. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0008

[Lines 55–55](../../../../../tests/unit/initialization_exception_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed scalar unsized storage produced by the replacement allocation seam. |
| inputs / outputs | A pointer from a compatible scalar allocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free(pointer) and does not alter fail_after/allocation_count/largest_allocation. |
| ownership | The supplied pointer is consumed here; no owner or view escapes. |
| failure | Deallocation itself is not fault-injected and makes no assertion about unrelated native/accounted cleanup. |
| cost | One std::free call; no allocation. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0009

[Lines 56–56](../../../../../tests/unit/initialization_exception_test.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed array unsized storage produced by the replacement allocation seam. |
| inputs / outputs | A pointer from a compatible array allocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free(pointer) and does not alter fail_after/allocation_count/largest_allocation. |
| ownership | The supplied pointer is consumed here; no owner or view escapes. |
| failure | Deallocation itself is not fault-injected and makes no assertion about unrelated native/accounted cleanup. |
| cost | One std::free call; no allocation. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0010

[Lines 57–57](../../../../../tests/unit/initialization_exception_test.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed scalar sized storage produced by the replacement allocation seam. |
| inputs / outputs | A pointer from a compatible scalar allocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free(pointer) and does not alter fail_after/allocation_count/largest_allocation. |
| ownership | The supplied pointer is consumed here; no owner or view escapes. |
| failure | Deallocation itself is not fault-injected and makes no assertion about unrelated native/accounted cleanup. |
| cost | One std::free call; no allocation. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0011

[Lines 58–58](../../../../../tests/unit/initialization_exception_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed array sized storage produced by the replacement allocation seam. |
| inputs / outputs | A pointer from a compatible array allocation form enters; no value is returned. |
| invariants | The noexcept body calls std::free(pointer) and does not alter fail_after/allocation_count/largest_allocation. |
| ownership | The supplied pointer is consumed here; no owner or view escapes. |
| failure | Deallocation itself is not fault-injected and makes no assertion about unrelated native/accounted cleanup. |
| cost | One std::free call; no allocation. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0012

[Lines 59–69](../../../../../tests/unit/initialization_exception_test.cpp#L59); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L59-L69:sha256:62a347fdc11083d0ab57aa332f57a4eee8ec171680e20299b083787a9335040a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare initialization_exception_test.cpp: bind local aliases/name imports; require 5 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 70–72](../../../../../tests/unit/initialization_exception_test.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a test assertion failure when an expected condition is false. |
| inputs / outputs | A boolean and borrowed std::string message enter; true returns and false throws std::runtime_error. |
| invariants | The helper neither catches product Error nor alters the runtime state being checked. |
| ownership | The message is borrowed through exception construction; no reference escapes. |
| failure | A failed check propagates std::runtime_error; constructing it may call the replaced new seam when armed. |
| cost | One condition branch on success; an exception object/message is built on failure. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp) |

## B0015

[Lines 74–84](../../../../../tests/unit/initialization_exception_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one action to throw crown::Error with a particular diagnostic code. |
| inputs / outputs | A forwarded callable and expected string_view code enter; normal return or a wrong exception throws a test failure, while matching Error returns. |
| invariants | Only crown::Error is accepted; a mismatch is checked before returning; an action that completes normally fails the helper. |
| ownership | The action is invoked synchronously; expected code is borrowed only during comparison; no callable/result is retained. |
| failure | A non-Error exception propagates; wrong/missing Error becomes std::runtime_error. No error is converted or retried. |
| cost | One action invocation and one code comparison; failure formatting may allocate. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0017

[Lines 86–86](../../../../../tests/unit/initialization_exception_test.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert one signed integer test value into the public scalar Value alternative. |
| inputs / outputs | An int64 value enters by value; an owning Value holding that integer exits. |
| invariants | No schema, range or database validation is performed by this fixture helper. |
| ownership | The returned variant owns its scalar value. |
| failure | No product error is handled here; ordinary variant construction may propagate its exception behavior. |
| cost | Constant scalar construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0018

[Lines 87–87](../../../../../tests/unit/initialization_exception_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value s(std::string value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move a test string into the public scalar Value alternative. |
| inputs / outputs | An owning std::string enters by value and is moved into the returned Value. |
| invariants | No encoding/SQL validation or borrowed string view is created. |
| ownership | Returned Value owns its string alternative; caller’s moved-from argument remains a valid string object. |
| failure | String construction before entry or variant construction may throw allocation failure; this helper does not catch it. |
| cost | Moves the string representation; size/capacity storage depends on the value and standard library. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/ir/scalar.hpp](../../../../../include/crown/ir/scalar.hpp) |

## B0020

[Lines 89–107](../../../../../tests/unit/initialization_exception_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the projected reciprocal-edge PhysicalPlan used to exercise source, support, live and result construction. |
| inputs / outputs | No inputs; lower_tree receives a one-table catalog, a three-occurrence query and a five-node native/generalized tree; an owning PhysicalPlan exits. |
| invariants | The query projects x from forward(x,z), reverse(z,x), and zero(x,0); source row physical columns include an ignored string column. |
| ownership | Catalog/query/tree values are local owning values moved or copied into the lowered plan; the returned plan owns its compiled/source data. |
| failure | lower_tree validation and allocation failures propagate; this fixture does not inject them unless the caller surrounds the invocation with FaultScope. |
| cost | Constructs a small fixed-shape plan; lowering work is separate from runtime initialization sweep measurements. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0022

[Lines 109–121](../../../../../tests/unit/initialization_exception_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database make_database() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the one-table, ten-row source database for initialization and rebuild oracles. |
| inputs / outputs | No inputs; returns one Relation of full three-field int64/int64/string rows, including reciprocal edges and duplicate projected keys with distinct notes. |
| invariants | Rows are full physical identities; the two (9,8) rows differ in note text and therefore remain distinct input rows. |
| ownership | Returned Database owns all Relation rows and strings. |
| failure | Owning string/container construction may throw; no allocation failure is translated here. |
| cost | Fixed ten-row fixture construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0024

[Lines 123–126](../../../../../tests/unit/initialization_exception_test.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Database& database() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share one immutable lazily constructed source database across runtime sweeps. |
| inputs / outputs | No inputs; returns const Database& to a function-local static initialized once from make_database(). |
| invariants | The static object outlives all test trials; callers must not mutate it. |
| ownership | The function retains ownership of the static Database; returned reference is borrowed and valid for program lifetime. |
| failure | First initialization may propagate an allocation exception; no copy is returned by this accessor. |
| cost | One reference access after one-time fixed-size construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp) |

## B0026

[Lines 128–130](../../../../../tests/unit/initialization_exception_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_database(const Database& left, const Database& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare caller database tables exactly to detect mutation during initialization/error paths. |
| inputs / outputs | Two Database values enter; table-vector equality determines the bool. |
| invariants | This relies on Relation/Row value equality and checks the whole table contents. |
| ownership | Both databases are borrowed for the comparison; no values escape. |
| failure | Unequal state returns false; nested equality exceptions propagate; no error or allocation fault is injected by the comparator itself. |
| cost | Proportional to compared tables and rows, with container equality short-circuiting. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0028

[Lines 132–132](../../../../../tests/unit/initialization_exception_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntimeOptions physical_options() { return {}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return default PhysicalRuntimeOptions for fixture builds. |
| inputs / outputs | No inputs; default options value exits. |
| invariants | This helper supplies no custom update cap or alternate MemoryAccount injection. |
| ownership | Options are returned by value and are independent of a runtime until passed to it. |
| failure | No failure path is handled here. |
| cost | Constant-size value return. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0030

[Lines 134–140](../../../../../tests/unit/initialization_exception_test.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions delta_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure delta-mode fixtures with live maintenance on output and ordered replay completion. |
| inputs / outputs | No inputs; returns DeltaOptions by value with the three named mode/completion choices and other default fields. |
| invariants | Options preserve explicit delta mode, on-output live maintenance and ordered replay for every call. |
| ownership | Returned options are an owned value; later runtime options copies are checked separately. |
| failure | No failure path is handled here. |
| cost | Constant-size option initialization. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0032

[Lines 142–146](../../../../../tests/unit/initialization_exception_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
BuildOptions build_options(BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select direct or insertion-replay construction without changing other BuildOptions defaults. |
| inputs / outputs | A BuildMethod enters; BuildOptions with method assigned exits. |
| invariants | This helper does not set a work limit; tests that need one assign it afterwards. |
| ownership | Options are returned by value. |
| failure | No failure is injected or translated here. |
| cost | Constant-size option construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0034

[Lines 148–151](../../../../../tests/unit/initialization_exception_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate prefix_update() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the real sequence-one prefix insert used to establish rebuild state. |
| inputs / outputs | No inputs; returns a full-row insert into table zero at sequence 1 with values (8,9,"prefix-row"). |
| invariants | The event has a real contiguous sequence and complete physical row including the ignored note column. |
| ownership | Returned update owns its values. |
| failure | No failure path is handled here. |
| cost | Fixed three-value event construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0036

[Lines 153–156](../../../../../tests/unit/initialization_exception_test.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate suffix_update(std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a caller-selected real suffix insert for clean-oracle comparison. |
| inputs / outputs | A sequence enters; returns a full-row insert into table zero with values (4,3,"suffix-row"). |
| invariants | The caller supplies sequence; rebuild callers pass 2 after the committed sequence-one prefix. |
| ownership | Returned update owns its values. |
| failure | No failure path is handled here. |
| cost | Fixed three-value event construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0038

[Lines 158–163](../../../../../tests/unit/initialization_exception_test.cpp#L158); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<Row> collect_results(PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect a physical owner’s result cursor into an owning set of exported rows. |
| inputs / outputs | PhysicalRuntime& enters; results().next() is drained and each tuple values view is exported to Row; a deduplicating std::set&lt;Row&gt; exits. |
| invariants | The local cursor and tuple/view are consumed before return; set membership compares exported full rows. |
| ownership | The runtime or snapshot is borrowed during traversal; export_row creates owning standard Row values that the returned set/vector retains. No TupleValuesView or tuple pointer escapes. |
| failure | Cursor/export/container allocation errors propagate; this helper has no catch or fault injection of its own. Any caller FaultScope reaches only the replaced C++ new/new\[\] calls. |
| cost | Visits each emitted result/output once and stores a full exported Row per returned value; work/storage scale with outputs and row widths, outside runtime logical build-work metrics. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md) |

## B0040

[Lines 165–170](../../../../../tests/unit/initialization_exception_test.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<Row> collect_results(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect a delta owner’s current result cursor into an owning set of exported rows. |
| inputs / outputs | DeltaRuntime& enters; its results cursor is drained and each tuple view is exported into a std::set&lt;Row&gt;. |
| invariants | No runtime-bound view escapes; result order is intentionally collapsed by the set oracle. |
| ownership | The runtime or snapshot is borrowed during traversal; export_row creates owning standard Row values that the returned set/vector retains. No TupleValuesView or tuple pointer escapes. |
| failure | Cursor/export/container allocation errors propagate; this helper has no catch or fault injection of its own. Any caller FaultScope reaches only the replaced C++ new/new\[\] calls. |
| cost | Visits each emitted result/output once and stores a full exported Row per returned value; work/storage scale with outputs and row widths, outside runtime logical build-work metrics. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md) |

## B0042

[Lines 172–177](../../../../../tests/unit/initialization_exception_test.cpp#L172); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct OutputImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one detached delta output item for exact suffix comparison. |
| inputs / outputs | Stores ordinal, SetOperation and owning Row; equality compares all three fields. |
| invariants | Row bytes are a value copy, not a borrowed TupleValuesView or live epoch handle. |
| ownership | The aggregate owns the Row; ordinal/operation are scalar values. |
| failure | Row construction/copy can allocate and propagate std::bad_alloc; no product error is caught. |
| cost | Storage proportional to the output row and standard-container placement. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0044

[Lines 179–185](../../../../../tests/unit/initialization_exception_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<OutputImage> drain(DeltaRuntime::Epoch& epoch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain committed delta output into value-only ordinal/operation/row images. |
| inputs / outputs | A mutable DeltaRuntime::Epoch enters; repeated next() results append ordinal, operation and export_row(tuple.values()) to a vector. |
| invariants | TupleValuesView is exported while the optional output is alive; returned OutputImage rows own their bytes and do not borrow the epoch. |
| ownership | The runtime or snapshot is borrowed during traversal; export_row creates owning standard Row values that the returned set/vector retains. No TupleValuesView or tuple pointer escapes. |
| failure | Cursor/export/container allocation errors propagate; this helper has no catch or fault injection of its own. Any caller FaultScope reaches only the replaced C++ new/new\[\] calls. |
| cost | Visits each emitted result/output once and stores a full exported Row per returned value; work/storage scale with outputs and row widths, outside runtime logical build-work metrics. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md) |

## B0046

[Lines 187–193](../../../../../tests/unit/initialization_exception_test.cpp#L187); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportProbe {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one public support-row identity and its value image for rebuild preservation checks. |
| inputs / outputs | Stores node id, support role, owning exported Row and SupportHandle; default equality compares all fields. |
| invariants | A handle is an owner-scoped identifier and is validated by the same live PhysicalRuntime; the row is copied separately. |
| ownership | The type owns the Row but not the runtime/owner behind SupportHandle. |
| failure | Copying the row may allocate; stale/wrong-owner handles are not self-validating in this record. |
| cost | Storage proportional to one exported support row. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0048

[Lines 195–200](../../../../../tests/unit/initialization_exception_test.cpp#L195); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SourceProbe {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one public source-row identity and its full-row value image. |
| inputs / outputs | Stores TableId, owning Row and TupleHandle; default equality compares all fields. |
| invariants | TupleHandle is meaningful for resolving the row through its original owner; row bytes are copied for the comparison. |
| ownership | The type owns the Row, not the PhysicalRuntime or tuple storage identified by the handle. |
| failure | Copying the row may allocate; a numeric handle alone does not retain its owner. |
| cost | Storage proportional to one full source row. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0050

[Lines 202–206](../../../../../tests/unit/initialization_exception_test.cpp#L202); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PublicHandles {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group expected source and support handle images for one physical owner. |
| inputs / outputs | Contains vectors of SourceProbe and SupportProbe gathered from the runtime’s source/support snapshot. |
| invariants | Vector order follows the snapshot traversal; equality requires exact row/handle records. |
| ownership | Vectors own their exported Rows and handle values but do not retain the runtime whose owner issued each handle. |
| failure | Copying/growing either vector may allocate; this record does not validate handle lifetime. |
| cost | O(number of source/support records plus copied row bytes). |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0052

[Lines 208–232](../../../../../tests/unit/initialization_exception_test.cpp#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<SupportProbe> support_handles(const SupportSnapshot& snapshot,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve every listed support snapshot row through the same PhysicalRuntime and capture its public handle. |
| inputs / outputs | A SupportSnapshot and mutable runtime are borrowed; records, survivors, parent keys and present visible keys are converted to rows, found, fetched and returned as SupportProbe values. |
| invariants | Each found handle must resolve through get_support to the same row; the output preserves node/role/value/handle for every traversed category. |
| ownership | Snapshot/runtime are borrowed during the walk; returned rows are exported copies. SupportHandle does not own the runtime. |
| failure | Missing lookup/get correspondence triggers the named test assertion; normal runtime/handle lookup exceptions propagate. No MemoryAccount limit or raw malloc/syscall failure is injected by this oracle. |
| cost | Traverses the rows/records in the supplied owning snapshot and copies exported row values plus handles into standard vectors. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0054

[Lines 234–250](../../../../../tests/unit/initialization_exception_test.cpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PublicHandles public_handles(PhysicalRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture every physical source handle and all public support handles from one runtime snapshot. |
| inputs / outputs | A PhysicalRuntime is borrowed; runtime.snapshot supplies a local source/support image, source rows are resolved by table/full row, then support_handles handles support rows. |
| invariants | Every source handle must resolve to the same full row; support values are checked the same way; returned image is used only against this owner. |
| ownership | Local snapshot is owned only until return; returned Rows are exported copies, while handles do not extend runtime lifetime. |
| failure | Missing lookup/get correspondence triggers the named test assertion; normal runtime/handle lookup exceptions propagate. No MemoryAccount limit or raw malloc/syscall failure is injected by this oracle. |
| cost | Traverses the rows/records in the supplied owning snapshot and copies exported row values plus handles into standard vectors. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0056

[Lines 252–262](../../../../../tests/unit/initialization_exception_test.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<SupportHandle> support_handles(const PhysicalSnapshot& snapshot) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Flatten record, parent-key and optional visible SupportHandles from a PhysicalSnapshot. |
| inputs / outputs | A snapshot is borrowed; returns handle values from each node’s records, parent_keys and present visible_keys. |
| invariants | Traversal order is node/record/key order; survivors are not included by this overload. |
| ownership | Output vector owns copied handle values, not the runtime or snapshot payload. |
| failure | Vector growth allocation can propagate; no lookup or handle revalidation occurs here. |
| cost | O(number of enumerated handles); no row export. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0058

[Lines 264–268](../../../../../tests/unit/initialization_exception_test.cpp#L264); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_public_handles(PhysicalRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that rebuilding or failure handling preserved exact public source/support handle images. |
| inputs / outputs | Mutable PhysicalRuntime and an expected PublicHandles image enter; newly captured handles/rows must compare equal. |
| invariants | Equality includes handle ids and exported full rows in traversal order. |
| ownership | Expected values are borrowed; fresh snapshot/export temporaries are local and do not escape. |
| failure | Missing lookup/get correspondence triggers the named test assertion; normal runtime/handle lookup exceptions propagate. No MemoryAccount limit or raw malloc/syscall failure is injected by this oracle. |
| cost | Traverses the rows/records in the supplied owning snapshot and copies exported row values plus handles into standard vectors. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0060

[Lines 270–272](../../../../../tests/unit/initialization_exception_test.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<SupportHandle> delta_support_handles(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture public support handle values from a DeltaRuntime snapshot. |
| inputs / outputs | DeltaRuntime is borrowed; snapshot() is consumed by support_handles(PhysicalSnapshot) and its SupportHandle vector exits. |
| invariants | The output reflects records/parent/visible handles in the delta owner’s current snapshot and is compared only with that owner. |
| ownership | The snapshot is a temporary owning value; returned handle ids do not own the runtime or its tuple payload. |
| failure | Snapshot/vector allocation failures propagate; no account/syscall failpoint is installed here. |
| cost | O(number of selected support handles) plus snapshot construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0062

[Lines 274–283](../../../../../tests/unit/initialization_exception_test.cpp#L274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_physical_state(PhysicalRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check physical owner readiness, sequence, canonical state and actual invariant report against a saved baseline. |
| inputs / outputs | Mutable PhysicalRuntime, expected CanonicalPhysicalState and sequence enter; returns normally only when all three observations agree. |
| invariants | Requires ready()==true, exact sequence, exact canonical state and inspect_invariants().valid(); the baseline contains copied typed state. |
| ownership | Runtime/baseline are borrowed during checking; canonical state and inspection report are local values. |
| failure | A mismatch raises std::runtime_error; runtime inspection errors propagate; this helper does not translate allocator or account failures. |
| cost | Cost includes a canonical-state snapshot plus full invariant inspection and is proportional to runtime state/work. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Canonical state and localized inspection](../../../../runtime_initialization.md) |

## B0064

[Lines 285–295](../../../../../tests/unit/initialization_exception_test.cpp#L285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_delta_state(DeltaRuntime& runtime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check delta readiness/state/mode/sequence, canonical typed state and actual invariant report. |
| inputs / outputs | Mutable DeltaRuntime, expected CanonicalDeltaState, expected sequence and DeltaMode enter; returns normally only on complete equality. |
| invariants | Requires ready state, matching mode and sequence, matching canonical state and a valid invariant report including live state where present. |
| ownership | Runtime/baseline are borrowed; canonical state and invariant report are temporary owning observations. |
| failure | A mismatch raises std::runtime_error; inspection or allocation errors propagate without translation. |
| cost | Builds a canonical snapshot and runs full invariant inspection; cost scales with physical/support/live/index state. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Canonical state and localized inspection](../../../../runtime_initialization.md) |

## B0066

[Lines 297–300](../../../../../tests/unit/initialization_exception_test.cpp#L297); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SweepStats {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the number of injected failure positions and the successful operation’s observed new-call count. |
| inputs / outputs | Stores two std::size_t values from sweep_allocations; no runtime state is retained. |
| invariants | failure_points counts failed fresh trials; successful_allocation_calls is a measured C++ new request count for the successful invoke path. |
| ownership | Only scalar values are owned. |
| failure | No failure handling is part of this value type. |
| cost | Constant-size value. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp) |

## B0067

[Lines 301–304](../../../../../tests/unit/initialization_exception_test.cpp#L301); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L301-L304:sha256:f6d735fa8bab8b0cb37f68682c1fbe0941b735bcfa8a08ec93d322d26dc24575
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Calibrate the successful operation's allocation count, then inject each consecutive allocation failure until that same operation completes. Counts are observations of this path, not a uniform allocation or byte limit. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0068

[Lines 305–354](../../../../../tests/unit/initialization_exception_test.cpp#L305); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Context, class Result, class Prepare, class Invoke,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Calibrate one allocation-producing action, inject consecutive global-new failures from fresh prepared contexts, and stop at the first successful action. |
| inputs / outputs | Prepare creates Context outside injection; Invoke produces Result; check_success/check_failure inspect each outcome; SweepStats exits when a post-failure attempt succeeds. |
| invariants | The successful baseline counts calls after prepare; configured fault indices are tried in order through successful_count+2 until the first success. On bad_alloc the fail index is set to zero before unwinding completes, then the scope disarms before failure oracle checks; failed attempts are not separately asserted against allocation_count==point+1. |
| ownership | Each Context/Result owns its local data according to its type; a partially constructed Result never escapes, and captured runtime/source values remain caller-owned. |
| failure | Only std::bad_alloc is treated as an injected allocation cut. The replacement observes ordinary scalar/array global C++ new calls, including calls made under an account allocator, but does not induce MemoryAccount limit denial or direct malloc/syscall failure. Init/rebuild trials use fresh contexts; this is not a same-owner retry. |
| cost | One baseline action plus up to successful-call-count+2 fresh preparations/invocations; measured count is allocation-call count, not bytes or uniform budget. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0070

[Lines 356–388](../../../../../tests/unit/initialization_exception_test.cpp#L356); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_build_metrics(std::string_view label, const BuildMetrics& metrics,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check build metrics against the direct/replay fixture’s required phases and print observed counters. |
| inputs / outputs | A label, BuildMetrics, BuildMethod and live-bootstrap expectation enter; assertions enforce positive source/adapter/derivation/native/generalized/support work and method-specific replay/live fields. |
| invariants | Direct requires replay counters zero; insertion_replay requires positive replay inputs/events/work; expect_live additionally requires live bootstrap work/rows/parent rows. |
| ownership | Metrics are borrowed during the check; label is a borrowed string_view and is only used in diagnostics/output. |
| failure | Missing expected metric raises std::runtime_error; no production failure is changed or retried. |
| cost | Constant-field checks and formatted output; metric generation cost is in initialization, not this helper. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/runtime_initialization.md § Work budgets and build metrics](../../../../runtime_initialization.md) |

## B0072

[Lines 390–390](../../../../../tests/unit/initialization_exception_test.cpp#L390); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalInitAttempt { PhysicalPlan plan; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the plan prepared before one physical initialization allocation sweep. |
| inputs / outputs | Contains one owned PhysicalPlan moved into PhysicalRuntime::initialize by the sweep invoke closure. |
| invariants | Each fault point gets a fresh attempt/context; no runtime owner is retained in this carrier. |
| ownership | The plan is owned by this struct until moved; moved-from plan remains a valid object. |
| failure | Plan construction may allocate before injection; init failures do not publish a partially built PhysicalRuntime. |
| cost | Storage is proportional to the fixture plan and shared immutable metadata. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0074

[Lines 392–425](../../../../../tests/unit/initialization_exception_test.cpp#L392); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_physical_initialization(BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep physical snapshot initialization for both direct and insertion-replay builders. |
| inputs / outputs | BuildMethod selects BuildOptions; each fresh PhysicalInitAttempt plan is moved into initialize against the static database; success/failure callbacks assert state. |
| invariants | Success requires ready sequence/support sequence zero, result set {2}, valid invariant report, method-consistent metrics and unchanged caller database; each injected failure checks the caller database remains unchanged. |
| ownership | The caller database is borrowed; a successful runtime is owned by the sweep Result only. Failure destroys the unpublished runtime inside initialize. |
| failure | The generic sweep injects only selected C++ new/new\[\] calls. It verifies cleanup of failed unpublished construction and the database oracle; it does not retry that same initialization owner or force account/malloc/syscall errors. |
| cost | Two build methods each calibrate and sweep observed new-call positions; full initialization work is separate and reported through BuildMetrics. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0076

[Lines 427–427](../../../../../tests/unit/initialization_exception_test.cpp#L427); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaInitAttempt { PhysicalPlan plan; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the plan prepared before one delta initialization allocation sweep. |
| inputs / outputs | Contains an owned PhysicalPlan moved into DeltaRuntime::initialize for the current trial. |
| invariants | A fresh plan/context is prepared for each allocation point; the carrier does not own a partially returned runtime. |
| ownership | The plan remains owned until moved into initialize. |
| failure | Plan construction is outside the injected operation; failed delta construction unwinds its unpublished physical/live state. |
| cost | Storage scales with the fixture plan only. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp) |

## B0078

[Lines 429–467](../../../../../tests/unit/initialization_exception_test.cpp#L429); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_delta_initialization(BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep initialized DeltaRuntime creation in delta mode for both physical build methods. |
| inputs / outputs | BuildMethod selects BuildOptions; each fresh plan initializes against the static database with delta_options; success/failure callbacks inspect it. |
| invariants | Success requires ready DeltaState, sequence and physical/live sequence zero, mode delta, result set {2}, valid invariant report, live build metrics and unchanged database; failure only checks caller database unchanged. |
| ownership | The database is borrowed; only successful returned DeltaRuntime is owned by the sweep result. Partial delta/live owner is destroyed during failed initialization. |
| failure | The sweep catches injected bad_allocs from replaced new/new\[\] only. There is no same-owner initialization retry, direct malloc/syscall fault, or native account-limit denial claim. |
| cost | Runs the full build twice by method and sweeps observed C++ allocation-call positions; live bootstrap and support work are separate metrics. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0080

[Lines 469–483](../../../../../tests/unit/initialization_exception_test.cpp#L469); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalRebuildAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a physical runtime at sequence one plus saved canonical state, public handles, owner id and a retained committed source pin. |
| inputs / outputs | Constructor initializes make_plan/database, applies prefix_update, then captures canonical_state/public_handles/owner; held_epoch retains the committed source tuple. |
| invariants | State baseline is after exactly one real update; source pin row must match prefix update across rebuild success/failure. |
| ownership | Carrier owns runtime, epoch pin, copied canonical state and handle/value images; database fixture reference remains static borrowed input. |
| failure | Setup allocation exceptions propagate before the sweep; no allocation failure is injected during this type’s constructor. |
| cost | Construction includes one runtime initialization, update, canonical snapshot and exported handle snapshots. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0082

[Lines 485–543](../../../../../tests/unit/initialization_exception_test.cpp#L485); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_physical_rebuild(BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep rebuilding a committed physical owner through direct and insertion-replay construction. |
| inputs / outputs | A prepared PhysicalRebuildAttempt invokes runtime.rebuilt(build); each fault position starts from a fresh ready owner with sequence-one prefix. |
| invariants | Success preserves the old owner/state/handles/pin, returns a distinct ready owner at sequence one, matches clean initialization plus prefix, then matches a real sequence-two suffix and result {2,3}; failure preserves the old state, owner id, handles and source pin. |
| ownership | Each attempt owns old runtime, held epoch pin and expected state; new owner is returned by value only on success. Old owner is never replaced. |
| failure | Injected allocation failure unwinds only the unpublished rebuilt owner; this sweep does not retry rebuilt() on that same owner after disarm. Work-limit errors are covered separately. |
| cost | Two builder methods each sweep allocation positions; successful oracle additionally builds a clean owner and applies prefix/suffix updates. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0084

[Lines 545–561](../../../../../tests/unit/initialization_exception_test.cpp#L545); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_delta_options(const DeltaOptions& left, const DeltaOptions& right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the full set of DeltaOptions fields that a rebuild is required to preserve. |
| inputs / outputs | Two options values enter; physical/support limits/order/capture/derivation, mode/view/live/completion, delta work/cursor/view/spool limits determine equality. |
| invariants | Every field explicitly listed in the helper is required to match; unlisted future option fields would need a source review before relying on this oracle. |
| ownership | Both options are borrowed values; no storage escapes. |
| failure | Unequal option returns false; no fault injection or translation occurs here. |
| cost | Constant number of field comparisons. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0086

[Lines 563–579](../../../../../tests/unit/initialization_exception_test.cpp#L563); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRebuildAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a DeltaRuntime at sequence one with pre-update options, canonical state and support-handle baseline. |
| inputs / outputs | Constructor initializes directly, commits prefix_update by discarding its output epoch, then captures canonical state and support handles. |
| invariants | The prefix is a real sequence-one event; options are captured from runtime after construction and before rebuild. |
| ownership | Carrier owns the runtime, canonical copy, handle vector and options value; handles remain owner-scoped. |
| failure | Setup can propagate allocation errors before the sweep; no injection is armed during carrier construction. |
| cost | Includes delta initialization, one update and state/handle snapshot cost. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0088

[Lines 581–639](../../../../../tests/unit/initialization_exception_test.cpp#L581); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_delta_rebuild(BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep delta rebuilds while preserving the original owner and options and comparing a clean real-event oracle. |
| inputs / outputs | Each prepared DeltaRebuildAttempt calls runtime.rebuilt(build); success runs direct/replay metrics and applies a sequence-two suffix to both rebuilt and clean owners. |
| invariants | Failure preserves sequence-one ready state, mode, options, owner id and support handles. Success yields a distinct owner with the same committed state/options and expected output image {ordinal 1, insert, row {3}} for the suffix. |
| ownership | Old runtime and expected handles remain owned by the attempt; rebuilt/clean owners are local success-oracle values, and drained rows are exported into OutputImage. |
| failure | Only the new C++ allocation seam is swept; failed new owner unwinds and old owner survives. The exact failed rebuilt call is not retried on the same instance. |
| cost | Two build methods; each successful check initializes a clean comparator and commits an additional update. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0090

[Lines 641–676](../../../../../tests/unit/initialization_exception_test.cpp#L641); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_late_build_work_failures() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove cumulative physical and delta/live build work limits reject one unit before measured successful work. |
| inputs / outputs | For direct and replay, successful runtimes provide total work; initialization with work_limit=total-1 must throw Error code resource_limit. |
| invariants | Physical and delta totals are measured independently; delta total is checked to exceed live bootstrap work, and caller database remains unchanged after each rejection. |
| ownership | Databases and plans are supplied by value/reference as written; no failed runtime is returned or retained. |
| failure | Expected failure is a build-work resource_limit, not injected bad_alloc; no same-owner retry or account/malloc/syscall failure is tested. |
| cost | Per method constructs physical and delta baseline builds plus one-unit-short trials; metric counters are abstract build work, not wall time. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/runtime_initialization.md § Work budgets and build metrics](../../../../runtime_initialization.md) |

## B0092

[Lines 678–682](../../../../../tests/unit/initialization_exception_test.cpp#L678); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_constant_unused_source_plan(const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower an empty query/tree against a supplied catalog so a source table can remain unused by the query plan. |
| inputs / outputs | Catalog is borrowed; lower_tree receives empty Query and FreeConnexTree and returns an owning PhysicalPlan. |
| invariants | The catalog still carries source schemas/constraints even though the empty query has no atoms/head. |
| ownership | The returned plan owns lowered program state; caller’s catalog remains unchanged. |
| failure | Planner validation/allocation errors propagate; no fault injection is armed here. |
| cost | Cost scales with catalog fields despite constant empty query/tree. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0094

[Lines 684–689](../../../../../tests/unit/initialization_exception_test.cpp#L684); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database constrained_unused_database() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create 64 distinct one-column source rows for repeated enforced-unique-constraint projection checks. |
| inputs / outputs | No inputs; returns a Database containing one Relation with integer rows 0 through 63. |
| invariants | Rows are unique and cover a deterministic full range; source table is intentionally unused by the empty query. |
| ownership | Returned Database owns the relation and rows. |
| failure | Container allocations can propagate std::bad_alloc; no product error is handled. |
| cost | Inserts 64 fixed-width rows into a set-backed Relation. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0096

[Lines 691–723](../../../../../tests/unit/initialization_exception_test.cpp#L691); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_constraint_projection_work_budgets() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise initialization and invariant-inspection work budgets on an unused source with twelve enforced unique projections. |
| inputs / outputs | Builds a 64-row source, one-column catalog with 12 same-key unique constraints and empty plan; unlimited init succeeds, work cap 500 rejects and inspection cap returns incomplete/invalid. |
| invariants | The unlimited physical snapshot must retain all source tables at sequence zero; 500 build work must yield resource_limit; bounded inspection must report incomplete with work&lt;=500; unlimited inspection is valid and caller source is unchanged. |
| ownership | Source/catalog/plan are local owning fixtures; runtime and inspection report are local values; the assertion uses snapshots, not an exported borrowed view. |
| failure | Expected cap outcomes are Error(resource_limit) or incomplete inspection, not bad_alloc. Repeated constraint projection is a work-budget test, not a MemoryAccount failure test. |
| cost | Build/inspection work scales with 64 rows times repeated constraints; configured work cap is an abstract counter. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Work budgets and build metrics](../../../../runtime_initialization.md) |

## B0097

[Lines 724–726](../../../../../tests/unit/initialization_exception_test.cpp#L724); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L724-L726:sha256:a13f5dfb2ed9ba83b0e1578a75901a70e824640c63ad1400d2546ca89c7a72eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare initialization_exception_test.cpp: declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0098

[Lines 727–753](../../../../../tests/unit/initialization_exception_test.cpp#L727); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_rebuild_budget_precedes_large_source_copy() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check zero-work physical rebuild rejection occurs before a payload-sized source copy. |
| inputs / outputs | Creates one 32 KiB string row/runtime, saves canonical state and source handle, resets largest_allocation, then calls rebuilt with work_limit zero. |
| invariants | Must receive resource_limit, observe largest C++ new request below half payload size, preserve ready sequence-zero canonical state and same source handle/value, and leave caller Database unchanged. |
| ownership | Payload/database and runtime own their string values; saved canonical state and source handle are separate copies/IDs. |
| failure | This is a work-precharge check. largest_allocation sees request sizes routed through replaced operator new/new\[\] only; it does not inspect raw malloc, MemoryAccount counters or syscalls. The oracle rejects any observed request at least half the payload length, not every smaller copy. |
| cost | Setup creates a large payload once; measured rebuild rejection compares maximum intercepted C++ new request against half the payload length, not total allocated bytes. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0100

[Lines 755–773](../../../../../tests/unit/initialization_exception_test.cpp#L755); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_exact_support_and_derivation_caps() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check exact support and derivation count limits for both physical build methods. |
| inputs / outputs | For direct and replay, initializes the same source/plan with support_limit=1 and derivation_limit=1; each action must raise its named Error code. |
| invariants | Support overflow and derivation overflow remain distinct diagnostics; static caller database compares unchanged after the cap trials. |
| ownership | Options/plan/database are values or borrowed caller state; failed partial runtime does not escape. |
| failure | Expected support_overflow/derivation_overflow are exact logical counter failures, not allocation failures or native account denial. |
| cost | Two builders times two cap attempts on the fixed fixture; count limits are exact configured counters. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/runtime_initialization.md § Work budgets and build metrics](../../../../runtime_initialization.md) |

## B0102

[Lines 775–816](../../../../../tests/unit/initialization_exception_test.cpp#L775); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_update_limits_are_separate_from_build_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show ordinary physical/delta update ceilings remain caller options after bootstrap and reject later updates. |
| inputs / outputs | For both build methods, sets physical/support/delta/cursor/view update caps to zero, initializes with unlimited BuildOptions work, then applies the real prefix update. |
| invariants | Initialization succeeds at sequence zero and preserves all configured option values; update raises resource_limit and leaves canonical state/sequence/options unchanged. |
| ownership | Runtime/options and saved canonical states are locally owned; update rows are owning values. |
| failure | The expected failure is update resource_limit, distinguishing build work limits from update limits; it does not inject bad_alloc or account denial. |
| cost | Two builders each perform physical and delta initialization plus one rejected event; build metrics are separate from update-cap behavior. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/runtime_initialization.md § Work budgets and build metrics](../../../../runtime_initialization.md) |

## B0104

[Lines 818–838](../../../../../tests/unit/initialization_exception_test.cpp#L818); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_cyclic_fk_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a one-table query whose catalog includes two enforced unique and two cyclic foreign-key constraints. |
| inputs / outputs | No inputs; local A/B tables define primary keys and reciprocal foreign keys; query reads only A.id and a one-leaf native tree is lowered into PhysicalPlan. |
| invariants | The query omits B and the FK column from its projection, but the complete catalog constraint graph remains in the plan. |
| ownership | Local table/catalog/query/tree values are owned by the construction and lowered plan. |
| failure | lower_tree errors/allocations propagate; no allocation injection occurs in this fixture builder. |
| cost | Fixed two-table schema and one-node tree construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0106

[Lines 840–842](../../../../../tests/unit/initialization_exception_test.cpp#L840); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Database cyclic_fk_database() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide a complete two-table snapshot satisfying both directions of the cyclic foreign key. |
| inputs / outputs | No inputs; returns rows A(1,10) and B(10,1) in their respective relations. |
| invariants | The rows are valid together although either individual public insert into the empty owner violates the opposite table’s FK. |
| ownership | Returned Database owns both relations. |
| failure | Container allocation can propagate; no failure translation. |
| cost | Fixed two-row database construction. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0108

[Lines 844–871](../../../../../tests/unit/initialization_exception_test.cpp#L844); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_complete_cyclic_foreign_key_bootstrap() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Contrast invalid one-at-a-time cyclic-FK insertion with valid complete-snapshot initialization. |
| inputs / outputs | For direct and replay, applies each cyclic row alone to an empty owner and expects constraint_violation, then initializes the full snapshot and checks sequence, rows, constraint metrics and invariants. |
| invariants | Each rejected prefix insert leaves the empty owner ready at sequence zero with two empty source relations; full snapshot bootstrap succeeds at sequence zero and caller data is unchanged. |
| ownership | Original Database value is retained for equality; initialized/empty runtimes own their source tables. |
| failure | Expected failures are constraint_violation from real update validation; initialization is not an injected allocation retry test. |
| cost | Two builders test two failed event validations and one complete snapshot build each. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0110

[Lines 873–885](../../../../../tests/unit/initialization_exception_test.cpp#L873); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class OwnedStream final : public std::istringstream {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an in-memory owned input stream observable at destruction in session-construction sweeps. |
| inputs / outputs | A serialized byte string and borrowed bool pointer enter; istringstream initializes; destruction sets the pointed-to flag true. |
| invariants | Constructor sets the flag false; the flag pointer must remain valid through stream destruction. |
| ownership | The stream owns its buffer through istringstream; destroyed_ borrows a bool in SessionInitAttempt. |
| failure | String/stream construction can allocate; destructor only writes the flag and is noexcept by base contract. |
| cost | Memory-backed input; no file or operating-system stream syscall is involved. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0112

[Lines 887–895](../../../../../tests/unit/initialization_exception_test.cpp#L887); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionInitAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one plan and OwnedStream plus a destruction flag for each initialized-session factory attempt. |
| inputs / outputs | Constructed from serialized bytes; make_plan builds the plan and make_unique constructs OwnedStream referring to this attempt’s bool. |
| invariants | Member declaration order places stream input after bool so reverse member destruction destroys input before the flag; create moves the unique_ptr into QuerySession. |
| ownership | Attempt owns the plan, bool and unique_ptr stream; stream’s raw bool pointer is borrowed from the still-live attempt. |
| failure | Plan/stream allocations may fail during prepare outside the armed sweep; if create fails, stream must be destroyed before failure callback. |
| cost | Owns one plan plus an in-memory stream buffer; bytes scale with input text. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0114

[Lines 897–902](../../../../../tests/unit/initialization_exception_test.cpp#L897); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string suffix_input() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize the actual sequence-one suffix update as one newline-terminated JSONL input event. |
| inputs / outputs | No inputs; constructs a plan for source catalog, an InputEvent at SourcePosition init-source:41 and returns write_input_json output plus newline. |
| invariants | Input event sequence is one and its full physical row matches suffix_update(1); this encoded stream is handed to session creation but no event is accepted during initialization. |
| ownership | Plan/event/string output are local owning values; returned string owns all bytes. |
| failure | Plan construction and JSON writer allocation failures propagate; no file or syscall is involved. |
| cost | Serializes one fixed event plus schema metadata; string size depends on encoded fields. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0116

[Lines 904–908](../../../../../tests/unit/initialization_exception_test.cpp#L904); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::set<Row> snapshot_rows(const SessionSnapshot& snapshot) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert SessionSnapshot native tuple values into an owning set of standard Rows. |
| inputs / outputs | A SessionSnapshot is borrowed; each snapshot row values view is exported into a std::set&lt;Row&gt; that exits. |
| invariants | The tuple/view is consumed while the snapshot collection is alive; returned rows are copies and duplicate rows collapse by set equality. |
| ownership | Snapshot remains borrowed for the function call; returned Rows own exported values and do not depend on session/runtime lifetime. |
| failure | Export and set allocation failures propagate; no catch or fault injection is installed here. |
| cost | Visits and copies every snapshot row plus row widths; this is an explicit external export cost. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/memory_accounts.md § Native public result tuples](../../../../memory_accounts.md) |

## B0118

[Lines 910–959](../../../../../tests/unit/initialization_exception_test.cpp#L910); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sweep_initialized_session_creation(BuildMethod method) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep initialized QuerySession::create for both physical builder methods while checking stream ownership, zero input progress and snapshot lifetime. |
| inputs / outputs | Serialized suffix bytes are prepared; each fresh SessionInitAttempt owns plan and OwnedStream; create moves plan/input using initial database, delta options and selected build method. |
| invariants | Success retains the stream, starts created/ready at committed sequence zero with empty input progress/output, snapshots only result {2}, then session.reset under fail_after=0 destroys the stream while saved snapshot remains readable. Failure checks stream destruction and unchanged database. |
| ownership | QuerySession::Owner owns facade/runtime/stream; initial Database is borrowed; SessionSnapshot independently owns exported tuple state. SessionInitAttempt keeps the stream-destruction flag alive. |
| failure | Every selected global new/new\[\] failure during create unwinds the unpublished session and owned stream; teardown is forced to fail any intercepted new calls. Each trial starts fresh; there is no same-owner session-construction retry and no direct stream syscall injection. |
| cost | Two build methods calibrate and sweep session construction allocation calls; success also captures a snapshot and tears down session under the C++ new failure seam. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md), [docs/memory_accounts.md § Native session and snapshot owners](../../../../memory_accounts.md) |

## B0120

[Lines 961–998](../../../../../tests/unit/initialization_exception_test.cpp#L961); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_rebuild_barriers() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check rebuild rejection while physical/delta owners have pending updates, result-reader leases or unread delta output. |
| inputs / outputs | Creates physical and delta owners; prepare/begin and result cursors must make rebuilt() throw runtime_busy; after rollback/cancel, unread output also blocks until discard and successful rebuild follows. |
| invariants | Owners return to ready state after rollback/cancel; delta committed sequence is one after suffix event, output remaining is positive before discard, and rebuilt delta stays in delta mode at that sequence. |
| ownership | Pending tokens, cursors, output epochs and runtimes are local owning values; clean-up calls close each barrier before local destruction. |
| failure | Expected failures are runtime_busy guard errors; this helper does not inject allocation failure or assert a same-owner rebuild retry after bad_alloc. |
| cost | Runs a fixed series of barrier checks and one successful delta rebuild after readers/output are closed. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md) |

## B0122

[Lines 1000–1068](../../../../../tests/unit/initialization_exception_test.cpp#L1000); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_no_allocation_moves_and_pin_cleanup() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check no-intercepted-new moves/destruction and that externally retained physical source pins and delta output survive owner teardown. |
| inputs / outputs | Creates physical/delta owners and retained epochs under fail_after disabled; move/destruction sequences then run after forbid_allocations sets fail_after=0. |
| invariants | Physical source pin still reads the inserted row after final owner destruction; stored delta SignedResult still reads insert row {3} after runtime teardown; move assignment and cleanup complete while ordinary global new is forbidden. |
| ownership | Optional owners and epoch/result handles are moved/reset explicitly; source pin and SignedResult retain their tuple payloads independently of runtime facade lifetime. |
| failure | The fixture requires these operations to complete while fail_after=0 makes any replaced ordinary C++ new/new\[\] request throw. This is not direct malloc/syscall interception or coverage of paths outside the scoped move/destruction fixture. |
| cost | Fixed owner/pin setup plus move/destroy operations; any payload retention is owned by returned handles. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Rebuild and ownership](../../../../runtime_initialization.md), [docs/memory_accounts.md § Native public result tuples](../../../../memory_accounts.md) |

## B0124

[Lines 1070–1070](../../../../../tests/unit/initialization_exception_test.cpp#L1070); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WriterAttempt {};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the no-state Context type required by the generic writer allocation sweep. |
| inputs / outputs | Default construction/destruction carry no fields; sweep_writer_allocations uses it as a fresh empty preparation value. |
| invariants | Writer inputs are captured by the callable, not stored in this type. |
| ownership | No values or references are retained. |
| failure | No failure behavior is defined by this empty type. |
| cost | Zero payload state. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp) |

## B0126

[Lines 1072–1084](../../../../../tests/unit/initialization_exception_test.cpp#L1072); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Writer>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one inspection/state writer through the generic global-new failure sweep and validate a version marker on success. |
| inputs / outputs | Label, writer callable and expected marker enter; each fresh WriterAttempt invokes writer to create std::string; success requires marker substring. |
| invariants | Failed allocation returns no string to caller; failure callback is intentionally empty because writer inputs are immutable local values; successful output must contain the marker. |
| ownership | Writer callable captures its immutable canonical state or invariant report by reference in the enclosing test and is invoked synchronously. |
| failure | Only replaced global C++ new/new\[\] bad_alloc positions are swept; no stateful output transaction, direct malloc/syscall or account-limit behavior is asserted. |
| cost | Same generic calibration plus successive fresh in-memory string writes; output cost scales with encoded state/report. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [docs/runtime_initialization.md § Canonical state and localized inspection](../../../../runtime_initialization.md) |

## B0128

[Lines 1086–1096](../../../../../tests/unit/initialization_exception_test.cpp#L1086); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan make_long_string_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the one-column long-string plan used to test writer byte admission. |
| inputs / outputs | No inputs; catalog has int64 id/string payload, query projects only id, and a native leaf tree lowers to PhysicalPlan. |
| invariants | The string payload is physically stored in source rows but omitted from the query result, so runtime-state serialization is the measured owner of the long source value. |
| ownership | Plan owns compiled source schema/program state. |
| failure | lower_tree validation or allocation errors propagate; no injector is active in this fixture helper itself. |
| cost | Fixed schema/tree construction independent of the 32 KiB row payload created by caller. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp) |

## B0130

[Lines 1098–1135](../../../../../tests/unit/initialization_exception_test.cpp#L1098); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_inspection_writer_failures_and_byte_bound() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep physical/delta canonical-state and invariant-report writers, then check an in-memory byte-limited long-string write rejects before a payload-sized request. |
| inputs / outputs | Captures physical/delta Canonical*State and valid report, sweeps writers for their versioned kind/valid markers; separately serializes a 32 KiB source string, sets byte cap after encoded prefix and records largest new request. |
| invariants | Successful writer outputs must contain exact markers; byte-limited write must raise resource_limit; largest intercepted C++ new request must be below half payload, while full output proves payload lies after a small prefix. |
| ownership | Canonical states/report and long string/runtime own their values; writers return owning std::string on success; no file stream or syscall is used. |
| failure | Writer sweeps catch selected global-new bad_allocs; byte-limit test expects a writer resource_limit. Largest size sees replaced operator new/new\[\] requests only, not raw malloc, account counters or syscalls. |
| cost | Three state/report string sweeps plus one full baseline encoding and one capped encode; time and allocator bytes are not inferred from string byte cap. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/io/inspection.hpp](../../../../../include/crown/io/inspection.hpp), [src/io/inspection.cpp](../../../../../src/io/inspection.cpp), [docs/runtime_initialization.md § Canonical state and localized inspection](../../../../runtime_initialization.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0132

[Lines 1137–1172](../../../../../tests/unit/initialization_exception_test.cpp#L1137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_no_fabricated_input_and_suffix_equivalence() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check initialization starts at zero and the first actual physical/delta update matches a clean owner that received the same prefix. |
| inputs / outputs | Creates initialized physical/delta runtimes, saves their zero-sequence canonical states, commits prefix_update to each and to separately initialized clean owners. |
| invariants | Before updates both result sets are {2}, ready and sequence/live/physical sequence are zero; after the real sequence-one update states equal clean oracles and saved pre-update state remains zero. |
| ownership | Runtime and canonical state values are locally owned; each update returns an epoch that is committed/discarded according to the runtime API. |
| failure | No failure is injected here; mismatched initialization/update state raises test runtime_error. |
| cost | Builds paired physical/delta clean and tested owners and compares full canonical state after one input. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0133

[Lines 1173–1175](../../../../../tests/unit/initialization_exception_test.cpp#L1173); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1173-L1175:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in initialization_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/code_review.md](../../../../code_review.md) |

## B0134

[Lines 1176–1209](../../../../../tests/unit/initialization_exception_test.cpp#L1176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orchestrate every initialization, rebuild, budget, cyclic-FK, session, teardown and writer fixture in this executable. |
| inputs / outputs | No external input; saves the static Database baseline, invokes both builder methods across allocation sweeps and fixed semantic checks, then returns zero if all checks complete. |
| invariants | At the end the static caller database must equal its original copy; exceptions print a failure diagnostic and return one. |
| ownership | All fixture/runtime/session/snapshot owners are local; no persistent external state or real file I/O is created. |
| failure | The catch handles std::exception but does not claim any test was executed in this review. FaultScope scopes disarm through RAII; no system-call injector is installed. |
| cost | Runs bounded allocation/fixture loops and full initialization/inspection work; no benchmark or theorem claim follows. |
| Design | [tests/unit/initialization_exception_test.cpp](../../../../../tests/unit/initialization_exception_test.cpp), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |
