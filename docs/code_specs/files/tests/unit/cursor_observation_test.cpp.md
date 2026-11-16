# `tests/unit/cursor_observation_test.cpp` — block usage map

[Source](../../../../../tests/unit/cursor_observation_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a60268561d3c1a4333a41b54c25d6e1ef62f1872ae0cbf5657c578fa73325eb2`. 1516 lines partitioned into 120 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–36](../../../../../tests/unit/cursor_observation_test.cpp#L1) | Imports dependencies. | growth new · [reviewed contract](#b0001) |
| [B0002 · 37–42](../../../../../tests/unit/cursor_observation_test.cpp#L37) | declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 43–47](../../../../../tests/unit/cursor_observation_test.cpp#L43) | Callable definition: void note() | calls load, fetch_add · [reviewed contract](#b0003) |
| [B0004 · 48–48](../../../../../tests/unit/cursor_observation_test.cpp#L48) | Explanatory comments or spacing. |  |
| [B0005 · 49–53](../../../../../tests/unit/cursor_observation_test.cpp#L49) | Callable definition: void* allocate(std::size_t bytes) | calls note, std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0005) |
| [B0006 · 54–54](../../../../../tests/unit/cursor_observation_test.cpp#L54) | Explanatory comments or spacing. |  |
| [B0007 · 55–61](../../../../../tests/unit/cursor_observation_test.cpp#L55) | Callable definition: void* allocate_aligned(std::size_t bytes, std::size_t alignment) | calls note, posix_memalign; returns result · [reviewed contract](#b0007) |
| [B0008 · 62–62](../../../../../tests/unit/cursor_observation_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0009 · 63–67](../../../../../tests/unit/cursor_observation_test.cpp#L63) | Callable definition: void arm(std::size_t threshold) noexcept | calls store · [reviewed contract](#b0009) |
| [B0010 · 68–68](../../../../../tests/unit/cursor_observation_test.cpp#L68) | Explanatory comments or spacing. |  |
| [B0011 · 69–72](../../../../../tests/unit/cursor_observation_test.cpp#L69) | Callable definition: void disarm() noexcept | calls store · [reviewed contract](#b0011) |
| [B0012 · 73–74](../../../../../tests/unit/cursor_observation_test.cpp#L73) | Closes surrounding scope/type. | source comment (unverified): // namespace allocation_probe · [reviewed contract](#b0012) |
| [B0013 · 75–75](../../../../../tests/unit/cursor_observation_test.cpp#L75) | Callable definition: void* operator new(std::size_t bytes) | calls allocation_probe::allocate; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0013) |
| [B0014 · 76–76](../../../../../tests/unit/cursor_observation_test.cpp#L76) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0014) |
| [B0015 · 77–79](../../../../../tests/unit/cursor_observation_test.cpp#L77) | Callable definition: void* operator new(std::size_t bytes, std::align_val_t alignment) | calls allocation_probe::allocate_aligned; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0015) |
| [B0016 · 80–82](../../../../../tests/unit/cursor_observation_test.cpp#L80) | Callable definition: void* operator new\[\](std::size_t bytes, std::align_val_t alignment) | calls ; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0016) |
| [B0017 · 83–83](../../../../../tests/unit/cursor_observation_test.cpp#L83) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0017) |
| [B0018 · 84–84](../../../../../tests/unit/cursor_observation_test.cpp#L84) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0018) |
| [B0019 · 85–85](../../../../../tests/unit/cursor_observation_test.cpp#L85) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0019) |
| [B0020 · 86–86](../../../../../tests/unit/cursor_observation_test.cpp#L86) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0020) |
| [B0021 · 87–87](../../../../../tests/unit/cursor_observation_test.cpp#L87) | Callable definition: void operator delete(void* pointer, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0021) |
| [B0022 · 88–88](../../../../../tests/unit/cursor_observation_test.cpp#L88) | Callable definition: void operator delete\[\](void* pointer, std::align_val_t) noexcept | calls  · [reviewed contract](#b0022) |
| [B0023 · 89–91](../../../../../tests/unit/cursor_observation_test.cpp#L89) | Callable definition: void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0023) |
| [B0024 · 92–94](../../../../../tests/unit/cursor_observation_test.cpp#L92) | Callable definition: void operator delete\[\](void* pointer, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0024) |
| [B0025 · 95–115](../../../../../tests/unit/cursor_observation_test.cpp#L95) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_copy_constructible_v&lt;ObservationConfiguration&gt;); · [reviewed contract](#b0025) |
| [B0026 · 116–122](../../../../../tests/unit/cursor_observation_test.cpp#L116) | Callable definition: std::uint64_t fake_clock() noexcept | calls ; returns scripted_clock\[scripted_clock_position++\]; fake_clock_value · [reviewed contract](#b0026) |
| [B0027 · 123–123](../../../../../tests/unit/cursor_observation_test.cpp#L123) | Explanatory comments or spacing. |  |
| [B0028 · 124–130](../../../../../tests/unit/cursor_observation_test.cpp#L124) | Callable definition: void reset_clock(std::uint64_t first = 100) noexcept | calls detail::set_observation_clock_for_testing · [reviewed contract](#b0028) |
| [B0029 · 131–131](../../../../../tests/unit/cursor_observation_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0030 · 132–139](../../../../../tests/unit/cursor_observation_test.cpp#L132) | Callable definition: void script_clock(std::initializer_list&lt;std::uint64_t&gt; values) noexcept | calls std::min, size, std::copy_n, begin · [reviewed contract](#b0030) |
| [B0031 · 140–140](../../../../../tests/unit/cursor_observation_test.cpp#L140) | Explanatory comments or spacing. |  |
| [B0032 · 141–146](../../../../../tests/unit/cursor_observation_test.cpp#L141) | Callable definition: void clear_clock() noexcept | calls detail::set_observation_clock_for_testing · [reviewed contract](#b0032) |
| [B0033 · 147–147](../../../../../tests/unit/cursor_observation_test.cpp#L147) | Explanatory comments or spacing. |  |
| [B0034 · 148–153](../../../../../tests/unit/cursor_observation_test.cpp#L148) | Callable definition: void group_complete(std::string_view label) | calls allocation_probe::disarm, clear_clock, detail::set_observation_initial_generation_for_testing · [reviewed contract](#b0034) |
| [B0035 · 154–154](../../../../../tests/unit/cursor_observation_test.cpp#L154) | Explanatory comments or spacing. |  |
| [B0036 · 155–158](../../../../../tests/unit/cursor_observation_test.cpp#L155) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0036) |
| [B0037 · 159–159](../../../../../tests/unit/cursor_observation_test.cpp#L159) | Explanatory comments or spacing. |  |
| [B0038 · 160–171](../../../../../tests/unit/cursor_observation_test.cpp#L160) | Callable definition: template &lt;class Action&gt; void expect_error(std::string_view code, Action&& action, std::string_view label) | calls code, std::runtime_error, std::string · [reviewed contract](#b0038) |
| [B0039 · 172–172](../../../../../tests/unit/cursor_observation_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0040 · 173–176](../../../../../tests/unit/cursor_observation_test.cpp#L173) | Callable definition: void self_move(SupportRuntime::ResultCursor& cursor) | calls std::move · [reviewed contract](#b0040) |
| [B0041 · 177–177](../../../../../tests/unit/cursor_observation_test.cpp#L177) | Explanatory comments or spacing. |  |
| [B0042 · 178–178](../../../../../tests/unit/cursor_observation_test.cpp#L178) | Callable definition: Value integer(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0042) |
| [B0043 · 179–179](../../../../../tests/unit/cursor_observation_test.cpp#L179) | Callable definition: Row int_row(std::int64_t value) | calls integer; returns Row{integer(value)} · [reviewed contract](#b0043) |
| [B0044 · 180–182](../../../../../tests/unit/cursor_observation_test.cpp#L180) | Callable definition: Row edge(std::int64_t left, std::int64_t right) | calls integer; returns Row{integer(left), integer(right)} · [reviewed contract](#b0044) |
| [B0045 · 183–187](../../../../../tests/unit/cursor_observation_test.cpp#L183) | declares types or opens a type body. |  · [reviewed contract](#b0045) |
| [B0046 · 188–198](../../../../../tests/unit/cursor_observation_test.cpp#L188) | Callable definition: void cursor(std::string label, const CursorObservation& report) | calls io::write_cursor_observation_json, check, empty, size; guard check(!json.empty(), "cursor exporter returned an empty document");; growth emplace_back · [reviewed contract](#b0046) |
| [B0047 · 199–199](../../../../../tests/unit/cursor_observation_test.cpp#L199) | Explanatory comments or spacing. |  |
| [B0048 · 200–210](../../../../../tests/unit/cursor_observation_test.cpp#L200) | Callable definition: void gauge(std::string label, const CommittedStateGauges& value) | calls io::write_committed_state_gauges_json, check, empty, size; guard check(!json.empty(), "gauge exporter returned an empty document");; growth emplace_back · [reviewed contract](#b0048) |
| [B0049 · 211–212](../../../../../tests/unit/cursor_observation_test.cpp#L211) | Closes surrounding scope/type. |  · [reviewed contract](#b0049) |
| [B0050 · 213–224](../../../../../tests/unit/cursor_observation_test.cpp#L213) | Callable definition: Relation drain(SupportRuntime::ResultCursor& cursor) | calls next, check, layout, same_token; guard check(row-&gt;layout().same_token(cursor.layout()),; returns rows; growth insert; 1 loop sites · [reviewed contract](#b0050) |
| [B0051 · 225–225](../../../../../tests/unit/cursor_observation_test.cpp#L225) | Explanatory comments or spacing. |  |
| [B0052 · 226–234](../../../../../tests/unit/cursor_observation_test.cpp#L226) | Callable definition: PhysicalPlan unary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0052) |
| [B0053 · 235–235](../../../../../tests/unit/cursor_observation_test.cpp#L235) | Explanatory comments or spacing. |  |
| [B0054 · 236–245](../../../../../tests/unit/cursor_observation_test.cpp#L236) | Callable definition: PhysicalPlan projected_many_to_one_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0054) |
| [B0055 · 246–246](../../../../../tests/unit/cursor_observation_test.cpp#L246) | Explanatory comments or spacing. |  |
| [B0056 · 247–256](../../../../../tests/unit/cursor_observation_test.cpp#L247) | Callable definition: PhysicalPlan unary_with_ignored_text_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0056) |
| [B0057 · 257–257](../../../../../tests/unit/cursor_observation_test.cpp#L257) | Explanatory comments or spacing. |  |
| [B0058 · 258–264](../../../../../tests/unit/cursor_observation_test.cpp#L258) | Callable definition: PhysicalPlan nullary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0058) |
| [B0059 · 265–265](../../../../../tests/unit/cursor_observation_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0060 · 266–270](../../../../../tests/unit/cursor_observation_test.cpp#L266) | Callable definition: PhysicalPlan constant_plan(bool contradiction) | calls planner::lower_tree; returns planner::lower_tree(catalog, query, FreeConnexTree{}) · [reviewed contract](#b0060) |
| [B0061 · 271–271](../../../../../tests/unit/cursor_observation_test.cpp#L271) | Explanatory comments or spacing. |  |
| [B0062 · 272–294](../../../../../tests/unit/cursor_observation_test.cpp#L272) | Callable definition: PhysicalPlan disconnected_product_plan(std::size_t arity) | calls check, std::to_string, push_back, planner::lower_tree; guard check(arity == 3 \|\| arity == 8, "product fixture arity is outside the literal test set");; returns planner::lower_tree(catalog, query, tree); growth push_back; 2 loop sites · [reviewed contract](#b0062) |
| [B0063 · 295–295](../../../../../tests/unit/cursor_observation_test.cpp#L295) | Explanatory comments or spacing. |  |
| [B0064 · 296–308](../../../../../tests/unit/cursor_observation_test.cpp#L296) | Callable definition: PhysicalPlan joined_visible_factor_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0064) |
| [B0065 · 309–309](../../../../../tests/unit/cursor_observation_test.cpp#L309) | Explanatory comments or spacing. |  |
| [B0066 · 310–324](../../../../../tests/unit/cursor_observation_test.cpp#L310) | Callable definition: PhysicalPlan aliased_generalized_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0066) |
| [B0067 · 325–325](../../../../../tests/unit/cursor_observation_test.cpp#L325) | Explanatory comments or spacing. |  |
| [B0068 · 326–341](../../../../../tests/unit/cursor_observation_test.cpp#L326) | Callable definition: PhysicalPlan three_factor_y_head_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0068) |
| [B0069 · 342–342](../../../../../tests/unit/cursor_observation_test.cpp#L342) | Explanatory comments or spacing. |  |
| [B0070 · 343–346](../../../../../tests/unit/cursor_observation_test.cpp#L343) | Callable definition: std::optional&lt;VariableId&gt; term_variable(const Term& term) | calls ; returns *variable; {} · [reviewed contract](#b0070) |
| [B0071 · 347–347](../../../../../tests/unit/cursor_observation_test.cpp#L347) | Explanatory comments or spacing. |  |
| [B0072 · 348–375](../../../../../tests/unit/cursor_observation_test.cpp#L348) | Callable definition: FreeConnexTree sql_tree(const Query& query) | calls empty, scopes, size, term_variable; returns tree; tree; growth insert, push_back; 5 loop sites · [reviewed contract](#b0072) |
| [B0073 · 376–376](../../../../../tests/unit/cursor_observation_test.cpp#L376) | Explanatory comments or spacing. |  |
| [B0074 · 377–387](../../../../../tests/unit/cursor_observation_test.cpp#L377) | Callable definition: PhysicalPlan exists_sql_plan(const Catalog& catalog) | calls frontend::bind_sql, std::runtime_error, frontend::normalize_sql, std::move; returns planner::lower_normalized(program, tree) · [reviewed contract](#b0074) |
| [B0075 · 388–388](../../../../../tests/unit/cursor_observation_test.cpp#L388) | Explanatory comments or spacing. |  |
| [B0076 · 389–402](../../../../../tests/unit/cursor_observation_test.cpp#L389) | Callable definition: Relation normalized_core_reference(const PhysicalPlan& plan, const Database& physical) | calls normalized, resize, size, at; returns reference::evaluate(program.core_catalog, program.core, logical); growth insert, resize; 2 loop sites · [reviewed contract](#b0076) |
| [B0077 · 403–403](../../../../../tests/unit/cursor_observation_test.cpp#L403) | Explanatory comments or spacing. |  |
| [B0078 · 404–414](../../../../../tests/unit/cursor_observation_test.cpp#L404) | Callable definition: void apply(PhysicalRuntime& runtime, Database& database, std::uint64_t& sequence, TableId table, SetOperation operation, Row valu… | calls check, at, contains, insert; guard check(result.input.physical_changed ==; growth insert · [reviewed contract](#b0078) |
| [B0079 · 415–415](../../../../../tests/unit/cursor_observation_test.cpp#L415) | Explanatory comments or spacing. |  |
| [B0080 · 416–433](../../../../../tests/unit/cursor_observation_test.cpp#L416) | Callable definition: bool same_work(const CursorWork& a, const CursorWork& b) | calls std::tie; returns std::tie(a.work, a.calls, a.route_checks, a.descriptor_steps, · [reviewed contract](#b0080) |
| [B0081 · 434–434](../../../../../tests/unit/cursor_observation_test.cpp#L434) | Explanatory comments or spacing. |  |
| [B0082 · 435–440](../../../../../tests/unit/cursor_observation_test.cpp#L435) | Callable definition: bool same_metrics(const ResultCursorMetrics& a, const ResultCursorMetrics& b) | calls same_work; returns same_work(a.startup, b.startup) && same_work(a.results, b.results) && · [reviewed contract](#b0082) |
| [B0083 · 441–441](../../../../../tests/unit/cursor_observation_test.cpp#L441) | Explanatory comments or spacing. |  |
| [B0084 · 442–459](../../../../../tests/unit/cursor_observation_test.cpp#L442) | Callable definition: bool same_lifecycle_values(const CursorObservation& a, const CursorObservation& b) | calls ; returns false; false; 1 loop sites · [reviewed contract](#b0084) |
| [B0085 · 460–460](../../../../../tests/unit/cursor_observation_test.cpp#L460) | Explanatory comments or spacing. |  |
| [B0086 · 461–479](../../../../../tests/unit/cursor_observation_test.cpp#L461) | Callable definition: void check_registry() | calls cursor_observation_registry, check, size, empty; guard check(registry.size() == names.size(), "cursor registry length differs from literal v1 set");; 1 loop sites · [reviewed contract](#b0086) |
| [B0087 · 480–480](../../../../../tests/unit/cursor_observation_test.cpp#L480) | Explanatory comments or spacing. |  |
| [B0088 · 481–553](../../../../../tests/unit/cursor_observation_test.cpp#L481) | Callable definition: void compare_reference_and_scalar_routes(ReportCollection& reports) | calls projected_many_to_one_plan, runtime, resize, apply; guard check(expected == Relation{{integer(1)}, {integer(2)}},; growth insert, resize; 2 loop sites · [reviewed contract](#b0088) |
| [B0089 · 554–554](../../../../../tests/unit/cursor_observation_test.cpp#L554) | Explanatory comments or spacing. |  |
| [B0090 · 555–604](../../../../../tests/unit/cursor_observation_test.cpp#L555) | Callable definition: void product_reference_and_factor_gauges(ReportCollection& reports) | calls disconnected_product_plan, runtime, resize, apply; guard check(expected.size() == expected_count,; growth insert, resize; 3 loop sites · [reviewed contract](#b0090) |
| [B0091 · 605–605](../../../../../tests/unit/cursor_observation_test.cpp#L605) | Explanatory comments or spacing. |  |
| [B0092 · 606–667](../../../../../tests/unit/cursor_observation_test.cpp#L606) | Callable definition: void observation_mode_matrix(ReportCollection& reports) | calls unary_with_ignored_text_plan, resize, insert, integer; guard check(expected == Relation{{integer(7)}}, "unary A04 mode-matrix fixture changed");; growth insert, resize; 1 loop sites · [reviewed contract](#b0092) |
| [B0093 · 668–668](../../../../../tests/unit/cursor_observation_test.cpp#L668) | Explanatory comments or spacing. |  |
| [B0094 · 669–765](../../../../../tests/unit/cursor_observation_test.cpp#L669) | Callable definition: void epoch_cursor_sources_and_invalidation(ReportCollection& reports) | calls joined_visible_factor_plan, runtime, resize, apply; guard check(expected == Relation{{integer(1)}}, "visible-factor A04 fixture changed its literal answer");; growth insert, resize · [reviewed contract](#b0094) |
| [B0095 · 766–766](../../../../../tests/unit/cursor_observation_test.cpp#L766) | Explanatory comments or spacing. |  |
| [B0096 · 767–934](../../../../../tests/unit/cursor_observation_test.cpp#L767) | Callable definition: void lifecycle_caps_and_failed_startup(ReportCollection& reports) | calls reset_clock, runtime, unary_plan, apply; guard check(!runtime.last_cursor_observation().has_value(),; growth insert · [reviewed contract](#b0096) |
| [B0097 · 935–935](../../../../../tests/unit/cursor_observation_test.cpp#L935) | Explanatory comments or spacing. |  |
| [B0098 · 936–944](../../../../../tests/unit/cursor_observation_test.cpp#L936) | Callable definition: PhysicalPlan string_unary_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0098) |
| [B0099 · 945–945](../../../../../tests/unit/cursor_observation_test.cpp#L945) | Explanatory comments or spacing. |  |
| [B0100 · 946–1016](../../../../../tests/unit/cursor_observation_test.cpp#L946) | Callable definition: void persistent_oom_and_nonallocating_copies(ReportCollection& reports) | calls runtime, string_unary_plan, apply, owner; guard check(factory_failed && runtime.ready() && runtime.owner() == owner,; growth insert · [reviewed contract](#b0100) |
| [B0101 · 1017–1017](../../../../../tests/unit/cursor_observation_test.cpp#L1017) | Explanatory comments or spacing. |  |
| [B0102 · 1018–1066](../../../../../tests/unit/cursor_observation_test.cpp#L1018) | Callable definition: void detached_cursor_and_query_session(ReportCollection& reports) | calls unary_plan, apply, int_row, owner; guard check(detached && detached-&gt;active() && detached-&gt;owner().value == owner,; growth emplace, insert, make_unique, resize · [reviewed contract](#b0102) |
| [B0103 · 1067–1067](../../../../../tests/unit/cursor_observation_test.cpp#L1067) | Explanatory comments or spacing. |  |
| [B0104 · 1068–1072](../../../../../tests/unit/cursor_observation_test.cpp#L1068) | Callable definition: bool same_observation_options(const ObservationOptions& a, const ObservationOptions& b) | calls ; returns a.mode == b.mode && a.trace_capacity == b.trace_capacity && · [reviewed contract](#b0104) |
| [B0105 · 1073–1073](../../../../../tests/unit/cursor_observation_test.cpp#L1073) | Explanatory comments or spacing. |  |
| [B0106 · 1074–1087](../../../../../tests/unit/cursor_observation_test.cpp#L1074) | Callable definition: bool same_delta_options(const DeltaOptions& a, const DeltaOptions& b) | calls same_observation_options; returns as.work_limit == bs.work_limit && as.support_limit == bs.support_limit && · [reviewed contract](#b0106) |
| [B0107 · 1088–1088](../../../../../tests/unit/cursor_observation_test.cpp#L1088) | Explanatory comments or spacing. |  |
| [B0108 · 1089–1112](../../../../../tests/unit/cursor_observation_test.cpp#L1089) | Callable definition: DeltaOptions exact_binding_options(ObservationMode mode = ObservationMode::timed) | calls ; returns options · [reviewed contract](#b0108) |
| [B0109 · 1113–1113](../../../../../tests/unit/cursor_observation_test.cpp#L1113) | Explanatory comments or spacing. |  |
| [B0110 · 1114–1131](../../../../../tests/unit/cursor_observation_test.cpp#L1114) | Callable definition: void check_binding(const ObservationConfiguration& actual, const DeltaOptions& requested, DeltaMode mode, DeltaCompletion complet… | calls requested_options, check, same_delta_options, mode; guard check(same_delta_options(copied, requested), · [reviewed contract](#b0110) |
| [B0111 · 1132–1132](../../../../../tests/unit/cursor_observation_test.cpp#L1132) | Explanatory comments or spacing. |  |
| [B0112 · 1133–1277](../../../../../tests/unit/cursor_observation_test.cpp#L1133) | Callable definition: void mode_binding_and_bootstrap_cursors(ReportCollection& reports) | calls unary_plan, exact_binding_options, runtime, owner; guard check(initial.has_value(), "enabled DeltaRuntime did not capture its initial configuration"); · [reviewed contract](#b0112) |
| [B0113 · 1278–1278](../../../../../tests/unit/cursor_observation_test.cpp#L1278) | Explanatory comments or spacing. |  |
| [B0114 · 1279–1337](../../../../../tests/unit/cursor_observation_test.cpp#L1279) | Callable definition: void delta_nested_clock_and_unsampled_trace(ReportCollection& reports) | calls exact_binding_options, runtime, joined_visible_factor_plan, apply; guard check(after_attempt.last.has_value() &&; growth insert · [reviewed contract](#b0114) |
| [B0115 · 1338–1338](../../../../../tests/unit/cursor_observation_test.cpp#L1338) | Explanatory comments or spacing. |  |
| [B0116 · 1339–1364](../../../../../tests/unit/cursor_observation_test.cpp#L1339) | Callable definition: void fake_clock_zero_and_regression(ReportCollection& reports) | calls runtime, unary_plan, apply, int_row; guard check(regression_report.metric(CursorMetricId::startup_ns).availability ==; growth insert · [reviewed contract](#b0116) |
| [B0117 · 1365–1365](../../../../../tests/unit/cursor_observation_test.cpp#L1365) | Explanatory comments or spacing. |  |
| [B0118 · 1366–1460](../../../../../tests/unit/cursor_observation_test.cpp#L1366) | Callable definition: void committed_gauges_and_private_guards(ReportCollection& reports) | calls aliased_generalized_plan, runtime, resize, edge; guard check(expected == Relation{{integer(1)}, {integer(10)}, {integer(2)}},; growth insert, resize; 1 loop sites · [reviewed contract](#b0118) |
| [B0119 · 1461–1463](../../../../../tests/unit/cursor_observation_test.cpp#L1461) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0119) |
| [B0120 · 1464–1516](../../../../../tests/unit/cursor_observation_test.cpp#L1464) | Callable definition: int main() | calls check_registry, group_complete, compare_reference_and_scalar_routes, product_reference_and_factor_gauges; returns 0; 1; 2 loop sites · [reviewed contract](#b0120) |

## B0001

[Lines 1–36](../../../../../tests/unit/cursor_observation_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L36:sha256:d58532b6db4c69f679b5576a33097576cbeec8b05b089a18cb092e81df960ffc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare cursor_observation_test.cpp: include "crown/api/error.hpp", "crown/frontend/bind.hpp", "crown/frontend/normalize.hpp", "crown/io/cursor_observation.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "crown/runtime/observation.hpp", "crown/runtime/physical.hpp", "crown/runtime/session.hpp", "crown/runtime/support.hpp", "evaluator.hpp", &lt;algorithm&gt;, &lt;array&gt;, &lt;atomic&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;initializer_list&gt;, &lt;iterator&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;tuple&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;variant&gt;, &lt;vector&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/cursor_observation_test.cpp](../../../../../tests/unit/cursor_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 37–42](../../../../../tests/unit/cursor_observation_test.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L42:sha256:631721d1dc576c7c902351fd8a1b210f8cab6e364f864a209a9c24a8f8534927
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare cursor_observation_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. Atomic counter storage and later atomic accesses belong to the test probe, not an engine timing or allocation measure. |
| Design | [tests/unit/cursor_observation_test.cpp](../../../../../tests/unit/cursor_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 43–47](../../../../../tests/unit/cursor_observation_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void note() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count an armed replacement-new request and inject std::bad_alloc once its zero-based threshold is reached. |
| inputs / outputs | No arguments; increments the atomic call counter only while armed and throws at index &gt;= fail_at. |
| invariants | The counter is reset by arm(); the exception happens before malloc/posix_memalign is attempted for the thresholded allocation. |
| ownership | Owns only atomic probe state; the allocation result and its eventual free remain with the matching replacement operator. |
| failure | An armed threshold produces std::bad_alloc; atomic counter arithmetic is relaxed and has no test assertion of thread synchronization. |
| cost | Adds one atomic fetch/load to each armed C++ new request; this is not MemoryAccount byte accounting and does not observe direct allocation syscalls. |
| Design | tests/unit/cursor_observation_test.cpp:43, docs/result_cursors.md:76, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0005

[Lines 49–53](../../../../../tests/unit/cursor_observation_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back ordinary global scalar/array replacement new with malloc and the injectable allocation counter. |
| inputs / outputs | Accepts byte count, maps zero bytes to a one-byte malloc request, returns raw storage or throws bad_alloc. |
| invariants | Calls note() before malloc; a threshold failure prevents the underlying request, while malloc failure also becomes bad_alloc. |
| ownership | Returns raw storage to the caller; matching replacement delete overloads release it with free. |
| failure | Can fail through the armed probe or malloc exhaustion. |
| cost | One probe call plus malloc; it only sees C++ calls routed through these global replacement operators, not arbitrary malloc/syscalls. |
| Design | tests/unit/cursor_observation_test.cpp:49, docs/memory_accounts.md:52, docs/observability.md:163 |

## B0007

[Lines 55–61](../../../../../tests/unit/cursor_observation_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate_aligned(std::size_t bytes, std::size_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Back over-aligned global scalar/array replacement new using posix_memalign. |
| inputs / outputs | Accepts byte count and requested alignment; maps zero bytes to alignment-sized storage and returns raw aligned memory. |
| invariants | Runs the same allocation failure probe as ordinary new and only returns after posix_memalign reports success. |
| ownership | Returned storage belongs to the C++ caller and is released by the global replacement delete family through free. |
| failure | Probe threshold or posix_memalign failure throws bad_alloc. |
| cost | One armed probe call plus one aligned allocator call; this is global-new seam evidence, not a proof about all native allocations. |
| Design | tests/unit/cursor_observation_test.cpp:55, docs/memory_accounts.md:52, docs/observability.md:163 |

## B0009

[Lines 63–67](../../../../../tests/unit/cursor_observation_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void arm(std::size_t threshold) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset the test replacement-new counter and arm persistent fail-at-threshold behavior. |
| inputs / outputs | Takes a size_t threshold; zero makes the next intercepted new fail, larger values permit that many requests. |
| invariants | Stores calls=0 and fail_at before publishing armed=true; callers explicitly disarm after each failure window. |
| ownership | Mutates only process-global test atomics; no runtime or MemoryAccount state is changed. |
| failure | No throwing path; arm is noexcept. |
| cost | Three relaxed atomic stores; subsequent intercepted C++ new calls pay note() instrumentation while armed. |
| Design | tests/unit/cursor_observation_test.cpp:63, docs/result_cursors.md:76 |

## B0011

[Lines 69–72](../../../../../tests/unit/cursor_observation_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void disarm() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable replacement-new failure injection after an allocation-sensitive operation. |
| inputs / outputs | No inputs or result; clears armed and restores the disabled threshold. |
| invariants | Does not reset the accumulated call count, allowing callers to inspect calls after disarming. |
| ownership | Resets only process-global test atomics. |
| failure | No throwing path; noexcept. |
| cost | Two relaxed atomic stores; no production accounting or allocator cost. |
| Design | tests/unit/cursor_observation_test.cpp:69, docs/result_cursors.md:76 |

## B0012

[Lines 73–74](../../../../../tests/unit/cursor_observation_test.cpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L74:sha256:0b226b9db70fd75a395d7251fe9828ab661cf302ee86deb2878e9c14f4055be8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in cursor_observation_test.cpp: namespace allocation_probe. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/cursor_observation_test.cpp](../../../../../tests/unit/cursor_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 75–75](../../../../../tests/unit/cursor_observation_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept scalar allocations in the test executable so startup/next/copy probes can inject persistent OOM. |
| inputs / outputs | Uses the ordinary C++ scalar allocation form and returns allocate(bytes). |
| invariants | The replacement delegates to the single probe allocator; corresponding delete overloads call free. |
| ownership | Global replacement functions are linked only into this test executable; they do not wrap C allocations outside C++ new. |
| failure | An armed threshold throws std::bad_alloc before the underlying allocation; underlying allocator exhaustion also throws. |
| cost | One probe and one malloc or posix_memalign operation per intercepted request; not an accounted-byte measurement. |
| Design | tests/unit/cursor_observation_test.cpp:75, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55, docs/memory_accounts.md:52 |

## B0014

[Lines 76–76](../../../../../tests/unit/cursor_observation_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept array allocations in the test executable so startup/next/copy probes can inject persistent OOM. |
| inputs / outputs | Uses the ordinary C++ array allocation form and returns allocate(bytes). |
| invariants | The replacement delegates to the single probe allocator; corresponding delete overloads call free. |
| ownership | Global replacement functions are linked only into this test executable; they do not wrap C allocations outside C++ new. |
| failure | An armed threshold throws std::bad_alloc before the underlying allocation; underlying allocator exhaustion also throws. |
| cost | One probe and one malloc or posix_memalign operation per intercepted request; not an accounted-byte measurement. |
| Design | tests/unit/cursor_observation_test.cpp:76, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55, docs/memory_accounts.md:52 |

## B0015

[Lines 77–79](../../../../../tests/unit/cursor_observation_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept over-aligned scalar allocations in the test executable so startup/next/copy probes can inject persistent OOM. |
| inputs / outputs | Uses the aligned scalar form and passes std::align_val_t as a size_t alignment. |
| invariants | The replacement delegates to the single probe allocator; corresponding delete overloads call free. |
| ownership | Global replacement functions are linked only into this test executable; they do not wrap C allocations outside C++ new. |
| failure | An armed threshold throws std::bad_alloc before the underlying allocation; underlying allocator exhaustion also throws. |
| cost | One probe and one malloc or posix_memalign operation per intercepted request; not an accounted-byte measurement. |
| Design | tests/unit/cursor_observation_test.cpp:77, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55, docs/memory_accounts.md:52 |

## B0016

[Lines 80–82](../../../../../tests/unit/cursor_observation_test.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intercept over-aligned array allocations in the test executable so startup/next/copy probes can inject persistent OOM. |
| inputs / outputs | Uses the aligned array form and passes std::align_val_t as a size_t alignment. |
| invariants | The replacement delegates to the single probe allocator; corresponding delete overloads call free. |
| ownership | Global replacement functions are linked only into this test executable; they do not wrap C allocations outside C++ new. |
| failure | An armed threshold throws std::bad_alloc before the underlying allocation; underlying allocator exhaustion also throws. |
| cost | One probe and one malloc or posix_memalign operation per intercepted request; not an accounted-byte measurement. |
| Design | tests/unit/cursor_observation_test.cpp:80, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55, docs/memory_accounts.md:52 |

## B0017

[Lines 83–83](../../../../../tests/unit/cursor_observation_test.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release scalar replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:83, docs/memory_accounts.md:52 |

## B0018

[Lines 84–84](../../../../../tests/unit/cursor_observation_test.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release array replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:84, docs/memory_accounts.md:52 |

## B0019

[Lines 85–85](../../../../../tests/unit/cursor_observation_test.cpp#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized scalar replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:85, docs/memory_accounts.md:52 |

## B0020

[Lines 86–86](../../../../../tests/unit/cursor_observation_test.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized array replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:86, docs/memory_accounts.md:52 |

## B0021

[Lines 87–87](../../../../../tests/unit/cursor_observation_test.cpp#L87); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release aligned scalar replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:87, docs/memory_accounts.md:52 |

## B0022

[Lines 88–88](../../../../../tests/unit/cursor_observation_test.cpp#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release aligned array replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:88, docs/memory_accounts.md:52 |

## B0023

[Lines 89–91](../../../../../tests/unit/cursor_observation_test.cpp#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized aligned scalar replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:89, docs/memory_accounts.md:52 |

## B0024

[Lines 92–94](../../../../../tests/unit/cursor_observation_test.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release sized aligned array replacement-new storage with free, matching the malloc/posix_memalign probe backend. |
| inputs / outputs | Accepts pointer plus the ABI-specific size/alignment parameters; returns void. |
| invariants | The size and alignment metadata do not alter the underlying free action; no ownership bookkeeping is retained. |
| ownership | The pointer is owned by the C++ allocation caller until deallocation; this helper releases it immediately. |
| failure | No exception path is specified; delete is noexcept. |
| cost | One free call; this exists to make the test-wide replacement allocator correctly deallocatable. |
| Design | tests/unit/cursor_observation_test.cpp:92, docs/memory_accounts.md:52 |

## B0025

[Lines 95–115](../../../../../tests/unit/cursor_observation_test.cpp#L95); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L95-L115:sha256:e9346cf7b428f5eebe598fe2a9bbc1616dec9a3bf5e43f40aa6c607d932945e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare cursor_observation_test.cpp: bind local aliases/name imports; require 8 compile-time type/ABI conditions; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/cursor_observation_test.cpp](../../../../../tests/unit/cursor_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 116–122](../../../../../tests/unit/cursor_observation_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t fake_clock() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply a deterministic optional observation clock, counting calls and consuming scripted samples first. |
| inputs / outputs | No inputs; returns the next scripted uint64 value or advances the fallback by 10. |
| invariants | Script position advances only within its bounded count; all clock calls are counted for exact reconciliation. |
| ownership | The clock is installed through the runtime testing hook; its globals live for the test process. |
| failure | No throw; noexcept. |
| cost | One increment per clock read and a bounded array lookup; it measures requested clock-read behavior, not elapsed CPU time. |
| Design | tests/unit/cursor_observation_test.cpp:116, docs/observability.md:71, docs/observability.md:163 |

## B0028

[Lines 124–130](../../../../../tests/unit/cursor_observation_test.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void reset_clock(std::uint64_t first = 100) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install the fake clock with a call counter, fallback starting value, and an empty scripted sequence. |
| inputs / outputs | Takes first fallback value, defaulting to 100; resets calls/script indices and installs the test hook. |
| invariants | Fallback values increase by ten; script and fallback tests therefore distinguish exact zero/backward readings from ordinary timing. |
| ownership | Mutates test globals and the process-global observation testing hook; clear_clock() removes the hook. |
| failure | No throw; noexcept. |
| cost | Fixed scalar resets and one hook write; no timer or runtime work is performed until a consumer calls the clock. |
| Design | tests/unit/cursor_observation_test.cpp:124, docs/observability.md:71 |

## B0030

[Lines 132–139](../../../../../tests/unit/cursor_observation_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void script_clock(std::initializer_list<std::uint64_t> values) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install up to eight deterministic clock samples for regression and zero-duration cases. |
| inputs / outputs | Copies min(initializer_list size, fixed array size) uint64 samples and resets script position/call count. |
| invariants | Samples beyond the fixed test array are ignored; after consumed samples the fake clock resumes +10 increments. |
| ownership | Copies values into a fixed test-owned array; it does not retain the caller initializer_list backing storage. |
| failure | No throw; noexcept and bounded storage avoids dynamic allocation in the clock setup helper. |
| cost | O(min(sample count, 8)) copy into a fixed array; this is test setup, not runtime timing cost. |
| Design | tests/unit/cursor_observation_test.cpp:132, docs/observability.md:71 |

## B0032

[Lines 141–146](../../../../../tests/unit/cursor_observation_test.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear_clock() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove the fake clock and clear its counters after a scenario. |
| inputs / outputs | No inputs or result; sets the observation clock hook to null and resets script/call indices. |
| invariants | Called between scenario groups and on the main exception path to avoid clock-state leakage. |
| ownership | Mutates only process-global testing state. |
| failure | No throw; noexcept. |
| cost | Fixed global writes and no runtime measurement. |
| Design | tests/unit/cursor_observation_test.cpp:141, docs/observability.md:71 |

## B0034

[Lines 148–153](../../../../../tests/unit/cursor_observation_test.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void group_complete(std::string_view label) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close allocation, clock, and generation-test overrides at a named scenario boundary and print a PASS marker. |
| inputs / outputs | Accepts a label string_view; no result. |
| invariants | Each successful preceding group reaches this cleanup; exception cleanup in main independently clears clock/allocation state. |
| ownership | Borrows the label only for immediate stderr output; resets process-global test hooks. |
| failure | Output stream failure is not explicitly asserted; function itself can propagate stream exceptions only if enabled. |
| cost | Resets test globals and writes one short line; no runtime operation is measured. |
| Design | tests/unit/cursor_observation_test.cpp:148, docs/observability.md:71 |

## B0036

[Lines 155–158](../../../../../tests/unit/cursor_observation_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed test predicate into an exception carrying a short diagnostic. |
| inputs / outputs | Accepts boolean and borrowed message; increments the global check count and returns normally for true. |
| invariants | A false predicate aborts the current group through std::runtime_error. |
| ownership | Does not retain the string_view; constructs an owning error string only on failure. |
| failure | Throws runtime_error on false; any allocation failure while forming the diagnostic is also possible. |
| cost | One integer increment per assertion; success avoids diagnostic-string construction. |
| Design | tests/unit/cursor_observation_test.cpp:155 |

## B0038

[Lines 160–171](../../../../../tests/unit/cursor_observation_test.cpp#L160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that an action throws crown::Error with the requested exact error code. |
| inputs / outputs | Templated callable, expected code, and diagnostic label; invokes the callable once. |
| invariants | Wrong code and no Error are distinct failures; unrelated exception types propagate. |
| ownership | Forwards the callable by reference category for the call; label/code are borrowed during checking. |
| failure | Throws runtime_error for wrong or missing Error; preserves other exceptions from the action. |
| cost | One invocation and error-code comparison; formatting allocates only on failure. |
| Design | tests/unit/cursor_observation_test.cpp:160, docs/result_cursors.md:76 |

## B0040

[Lines 173–176](../../../../../tests/unit/cursor_observation_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void self_move(SupportRuntime::ResultCursor& cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise self-move assignment on the exact same live ResultCursor object. |
| inputs / outputs | Borrows a ResultCursor; assigns std::move(*same_object) back to itself. |
| invariants | The lifecycle suite checks the cursor remains active after self-move. |
| ownership | Does not transfer or destroy the caller-owned cursor object. |
| failure | Any invalid-cursor behavior would propagate, but this helper has no expected failure. |
| cost | One self-move assignment, not a cursor start or next operation. |
| Design | tests/unit/cursor_observation_test.cpp:173, docs/result_cursors.md:76 |

## B0042

[Lines 178–178](../../../../../tests/unit/cursor_observation_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value integer(std::int64_t value) { return Value{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the scalar integer value used by independent expected rows. |
| inputs / outputs | Takes int64 and returns Value{value}. |
| invariants | Tests use typed integer equality; this helper does not allocate a string payload. |
| ownership | Returns an owning value/row; source integers are copied into the returned value. |
| failure | No domain failure path; allocation failure, if any, propagates from the value/container construction. |
| cost | Constructs one Value or a small Row; this is test-fixture setup outside observation measurement windows. |
| Design | tests/unit/cursor_observation_test.cpp:178, docs/result_cursors.md:18 |

## B0043

[Lines 179–179](../../../../../tests/unit/cursor_observation_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row int_row(std::int64_t value) { return Row{integer(value)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-column integer Row for the unary and child-S fixtures. |
| inputs / outputs | Takes int64, wraps integer(value), returns a one-cell Row. |
| invariants | The same row shape is used in Q child S and one-column table operations. |
| ownership | Returns an owning value/row; source integers are copied into the returned value. |
| failure | No domain failure path; allocation failure, if any, propagates from the value/container construction. |
| cost | Constructs one Value or a small Row; this is test-fixture setup outside observation measurement windows. |
| Design | tests/unit/cursor_observation_test.cpp:179, docs/result_cursors.md:18 |

## B0044

[Lines 180–182](../../../../../tests/unit/cursor_observation_test.cpp#L180); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t left, std::int64_t right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-column integer edge row for R/alias fixtures. |
| inputs / outputs | Takes left/right int64 and returns a two-cell Row. |
| invariants | Field order is left then right and matches the literal catalog declarations. |
| ownership | Returns an owning value/row; source integers are copied into the returned value. |
| failure | No domain failure path; allocation failure, if any, propagates from the value/container construction. |
| cost | Constructs one Value or a small Row; this is test-fixture setup outside observation measurement windows. |
| Design | tests/unit/cursor_observation_test.cpp:180, docs/result_cursors.md:18 |

## B0045

[Lines 183–187](../../../../../tests/unit/cursor_observation_test.cpp#L183); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L183-L187:sha256:c632d67426876b6a76e39d1883de84749c155a19b014bc82d3273bec88a11a28
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare cursor_observation_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/cursor_observation_test.cpp](../../../../../tests/unit/cursor_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0046

[Lines 188–198](../../../../../tests/unit/cursor_observation_test.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void cursor(std::string label, const CursorObservation& report) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a real cursor observation for the machine-readable independent test output. |
| inputs / outputs | Accepts an owning case label and borrowed CursorObservation; returns void after appending label/JSON pair. |
| invariants | Uses a 16 MiB ceiling, requires nonempty JSON, accepts exact encoded byte count, and expects resource_limit at N-1. |
| ownership | JSON and moved label are owned by ReportCollection; observation is borrowed synchronously and not retained. |
| failure | Serializer errors propagate; N-1 must specifically raise resource_limit or the test fails. |
| cost | Builds a JSON string and stores a copy/move in vectors; export allocations are not under the mutation allocation probe and the byte cap is not a heap/CPU cap. |
| Design | tests/unit/cursor_observation_test.cpp:188, docs/observability.md:126, docs/observability.md:182 |

## B0048

[Lines 200–210](../../../../../tests/unit/cursor_observation_test.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void gauge(std::string label, const CommittedStateGauges& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize committed-state gauge values into the test output with encoded-size boundary checks. |
| inputs / outputs | Accepts owning label and borrowed CommittedStateGauges; appends exported JSON. |
| invariants | Uses the same 16 MiB, exact-size accepted, and N-1 resource_limit checks as cursor reports. |
| ownership | The stored JSON owns copied text; gauge input is borrowed for the synchronous writer call. |
| failure | Writer failures propagate; N-1 must raise resource_limit. |
| cost | Gauge JSON construction/storage can allocate and is deliberately outside mutation/OOM windows; byte cap bounds encoded output only. |
| Design | tests/unit/cursor_observation_test.cpp:200, docs/observability.md:126, docs/observability.md:182 |

## B0049

[Lines 211–212](../../../../../tests/unit/cursor_observation_test.cpp#L211); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L211-L212:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in cursor_observation_test.cpp: struct ReportCollection. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/cursor_observation_test.cpp](../../../../../tests/unit/cursor_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0050

[Lines 213–224](../../../../../tests/unit/cursor_observation_test.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor& cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume a support cursor to terminal exhaustion and validate owning row/layout/lifecycle behavior. |
| inputs / outputs | Takes a cursor by reference, repeatedly calls next(), exports returned tuple values into a Relation, returns that set. |
| invariants | Every row carries the cursor layout token; duplicate exported set rows fail; terminal null leaves state exhausted/inactive and repeated next remains null. |
| ownership | The cursor stays caller-owned; returned rows in Relation own exported values rather than borrowing cursor tuples. |
| failure | Cursor errors and duplicate/layout assertion failures propagate; this is not a failure-injection wrapper. |
| cost | Traverses the complete answer and allocates Relation/set rows; cursor abstract work is available separately and is not CPU/heap size. |
| Design | tests/unit/cursor_observation_test.cpp:213, docs/result_cursors.md:18, docs/result_cursors.md:76, docs/result_cursors.md:101 |

## B0052

[Lines 226–234](../../../../../tests/unit/cursor_observation_test.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-table unary native physical plan for lifecycle, clocks and budget boundaries. |
| inputs / outputs | No arguments; returns lowered plan for r(x), head x. |
| invariants | Literal single native node and variable x; initial rows are supplied separately. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:226, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0054

[Lines 236–245](../../../../../tests/unit/cursor_observation_test.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan projected_many_to_one_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one-table projection x from (x,w), allowing multiple witnesses to collapse to the same output. |
| inputs / outputs | No arguments; returns lowered plan over r(x,w) with head x. |
| invariants | The scalar-route test inserts (1,10),(1,11),(2,20) and expects exactly {1,2}. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:236, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0056

[Lines 247–256](../../../../../tests/unit/cursor_observation_test.cpp#L247); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_with_ignored_text_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build unary x while marking a string payload as ignored by the query. |
| inputs / outputs | No arguments; returns plan r(x,payload) with ignored second term and head x. |
| invariants | The mode matrix retains the ignored string in source rows but result remains integer 7. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:247, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0058

[Lines 258–264](../../../../../tests/unit/cursor_observation_test.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan nullary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a nullary Boolean/existence query over a table with an ignored string field. |
| inputs / outputs | No arguments; returns query with no variables or head and one ignored atom. |
| invariants | The A04 oracle expects empty relation before a source row and the nullary identity row afterward. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:258, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0060

[Lines 266–270](../../../../../tests/unit/cursor_observation_test.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan constant_plan(bool contradiction) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build constant-true or contradiction constant-false plan. |
| inputs / outputs | Takes contradiction flag and lowers an empty catalog/query with that flag. |
| invariants | Independent reference expects {empty row} for true and empty relation for false. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:266, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0062

[Lines 272–294](../../../../../tests/unit/cursor_observation_test.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan disconnected_product_plan(std::size_t arity) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build disconnected generalized product with exactly three or eight native factors. |
| inputs / outputs | Takes arity, accepts only 3 or 8, creates one int table/variable per factor and a generalized root. |
| invariants | The product test inserts two rows per table and expects exactly 2^arity rows; other arities fail fixture validation. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:272, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0064

[Lines 296–308](../../../../../tests/unit/cursor_observation_test.cpp#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan joined_visible_factor_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build native a(x) joined to b(x,z), exposing the x separator for committed visible-key and bucket queries. |
| inputs / outputs | No args; returns two-node native plan with root a and child b. |
| invariants | Fixture inserts a={1,2}, b={(1,10),(1,11),(3,30)}; expected query output is {1}, while child key 3 is locally visible but globally unlive. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:296, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0066

[Lines 310–324](../../../../../tests/unit/cursor_observation_test.cpp#L310); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan aliased_generalized_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-alias generalized self-join over one physical r(a,b) table and project x. |
| inputs / outputs | No args; returns r_left(x,y) joined to r_right(y,z), head x. |
| invariants | One physical source backs both aliases; gauge tests distinguish base count from per-alias node counts. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:310, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0068

[Lines 326–341](../../../../../tests/unit/cursor_observation_test.cpp#L326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan three_factor_y_head_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build G{y} over native R(x,y),S(y,z) with head y to verify C* query-factor count. |
| inputs / outputs | No args; returns three-node generalized/native tree. |
| invariants | Configuration is expected to report three factors; this is a fixture-specific count, not inferred from physical node or head count. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:326, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0070

[Lines 343–346](../../../../../tests/unit/cursor_observation_test.cpp#L343); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VariableId> term_variable(const Term& term) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract a variable term from a normalized SQL Term variant, returning empty for an ignored/non-variable term. |
| inputs / outputs | Takes borrowed Term; returns optional VariableId. |
| invariants | Uses std::get_if&lt;VariableId&gt;; does not reinterpret constants as variables. |
| ownership | Returns a scalar optional by value and keeps no reference to term storage. |
| failure | No expected exception path. |
| cost | One variant type check and optional construction. |
| Design | tests/unit/cursor_observation_test.cpp:343, docs/result_cursors.md:18 |

## B0072

[Lines 348–375](../../../../../tests/unit/cursor_observation_test.cpp#L348); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree sql_tree(const Query& query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a simple FreeConnexTree for the query shapes used by the SQL EXISTS fixture. |
| inputs / outputs | Takes normalized Query; returns empty tree for contradiction/no atoms, native single node for one atom, else generalized product with common variable intersection and native children. |
| invariants | Scope sets contain only VariableId terms; product separator is intersection across atom scopes; table occurrence ordering follows query atom order. |
| ownership | Returns an owning tree; reads query by const reference only during construction. |
| failure | Container allocation/planner validation may fail and propagate; this helper is not a general SQL planner proof. |
| cost | Scans terms and builds scope/child vectors and sets; its simple intersection construction is only used by the literal EXISTS case. |
| Design | tests/unit/cursor_observation_test.cpp:348, docs/result_cursors.md:18 |

## B0074

[Lines 377–387](../../../../../tests/unit/cursor_observation_test.cpp#L377); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan exists_sql_plan(const Catalog& catalog) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind and normalize SELECT EXISTS(SELECT NULL FROM r), then lower it through the test-built SQL tree. |
| inputs / outputs | Takes a Catalog; returns PhysicalPlan with normalized SQL metadata. |
| invariants | Converts each BindingDiagnostic into a runtime_error; successful result is specifically Boolean EXISTS over r. |
| ownership | Moves NormalizedSql into the plan; returned plan owns normalized program metadata. |
| failure | Binding/normalization diagnostic codes and messages are surfaced as runtime_error; lower_tree errors propagate. |
| cost | Runs binder, normalizer and planner for fixture setup; not part of cursor observation cost. |
| Design | tests/unit/cursor_observation_test.cpp:377, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0076

[Lines 389–402](../../../../../tests/unit/cursor_observation_test.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation normalized_core_reference(const PhysicalPlan& plan, const Database& physical) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the independent logical-core database from physical rows through each normalized adapter and evaluate the core query. |
| inputs / outputs | Takes PhysicalPlan and physical Database; returns Relation from reference::evaluate. |
| invariants | Each row is adapted only when frontend::adapt_row succeeds; occurrence/table mapping comes from normalized program adapter metadata. |
| ownership | Constructs an owning logical database and output relation; borrows plan and physical input during evaluation. |
| failure | Invalid normalized metadata/index access or evaluator failures propagate. |
| cost | Copies/adapts source rows and runs the independent reference evaluator; this is test oracle work, not production cursor work. |
| Design | tests/unit/cursor_observation_test.cpp:389, docs/result_cursors.md:18 |

## B0078

[Lines 404–414](../../../../../tests/unit/cursor_observation_test.cpp#L404); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(PhysicalRuntime& runtime, Database& database, std::uint64_t& sequence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a physical set update while maintaining an independent sequence and source-table set oracle. |
| inputs / outputs | Takes runtime/database/sequence by reference plus table/op/row by value; returns void. |
| invariants | Increments sequence before apply and asserts physical_changed equals set membership expectation before updating the oracle. |
| ownership | Oracle database is mutated only after the runtime result agrees; update row is moved into insert set or looked up for erase. |
| failure | Runtime apply or assertion failure stops before the oracle update. |
| cost | Runs one physical update and an independent set membership check; does not measure allocation or CPU. |
| Design | tests/unit/cursor_observation_test.cpp:404, docs/result_cursors.md:18 |

## B0080

[Lines 416–433](../../../../../tests/unit/cursor_observation_test.cpp#L416); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_work(const CursorWork& a, const CursorWork& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every CursorWork counter field so observation-mode tests can require exact mandatory work equality. |
| inputs / outputs | Takes two const CursorWork references and returns bool. |
| invariants | Compares work, calls, route/frame/cursor/tuple/key/output/binding/witness fields and join rejections individually. |
| ownership | Borrows both counter objects and retains no state. |
| failure | No expected throw. |
| cost | Fixed tuple of scalar comparisons; it does not estimate CPU work from the abstract counter. |
| Design | tests/unit/cursor_observation_test.cpp:416, docs/result_cursors.md:101 |

## B0082

[Lines 435–440](../../../../../tests/unit/cursor_observation_test.cpp#L435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_metrics(const ResultCursorMetrics& a, const ResultCursorMetrics& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all five cursor phase work records and cumulative summary counters. |
| inputs / outputs | Takes two ResultCursorMetrics const references and returns bool. |
| invariants | Requires same startup/results/termination/failed/last work, total_work, max_result_work, and cleanup frame count. |
| ownership | Borrows metrics only; no runtime cursor is retained. |
| failure | No expected throw. |
| cost | Fixed bounded comparisons over value structs. |
| Design | tests/unit/cursor_observation_test.cpp:435, docs/result_cursors.md:101 |

## B0084

[Lines 442–459](../../../../../tests/unit/cursor_observation_test.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_lifecycle_values(const CursorObservation& a, const CursorObservation& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare saved lifecycle reports by mandatory counters, metric value/availability/saturation and identity/state fields. |
| inputs / outputs | Takes two CursorObservation const references; returns bool. |
| invariants | Compares mandatory total/max/cleanup and phase work fields, every cursor metric value/availability/saturation, and state/terminal/id/owner/sequence; deliberately does not compare configuration/source/side fields. |
| ownership | Saved observations are value copies; later cursor transitions cannot mutate either input copy. |
| failure | No expected throw. |
| cost | Loops over fixed cursor_metric_count and scalar fields; it is a test equality oracle, not measurement. |
| Design | tests/unit/cursor_observation_test.cpp:442, docs/observability.md:71, docs/result_cursors.md:76 |

## B0086

[Lines 461–479](../../../../../tests/unit/cursor_observation_test.cpp#L461); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_registry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin the cursor metric registry to a literal v1 name/order/unit/scope and timing-counter partition. |
| inputs / outputs | No arguments; obtains cursor_observation_registry and returns void after assertions. |
| invariants | Registry length/order/contiguous IDs match 12 literal metric names; first five are timing, rest counters, each unit/scope nonempty. |
| ownership | Registry descriptors are borrowed from the API; no registry copy is retained. |
| failure | Any schema/name/order drift fails the test via check(). |
| cost | Fixed descriptor iteration and string comparisons; no runtime cursor work is performed. |
| Design | tests/unit/cursor_observation_test.cpp:461, docs/observability.md:71 |

## B0088

[Lines 481–553](../../../../../tests/unit/cursor_observation_test.cpp#L481); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compare_reference_and_scalar_routes(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare core cursor results with independent A04 evaluation across projected many-witness, constants, nullary, and SQL EXISTS routes. |
| inputs / outputs | Takes ReportCollection; constructs literal plans/runtimes and exports named cursor observations. |
| invariants | Projection must dedupe witnesses to {1,2}; constants yield identity/empty; nullary changes from empty to identity; SQL EXISTS maps false/true independently through normalized-core reference and mapper. |
| ownership | Each runtime/cursor is local to a case; report collection owns only serialized JSON. |
| failure | Reference/planner/cursor/export errors propagate; all row mismatches fail check(). |
| cost | Runs A04 evaluation plus full cursor drains and JSON capture; traversal work is checked by the runtime but this helper makes no CPU claim. |
| Design | tests/unit/cursor_observation_test.cpp:481, docs/result_cursors.md:18, docs/observability.md:126, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0090

[Lines 555–604](../../../../../tests/unit/cursor_observation_test.cpp#L555); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void product_reference_and_factor_gauges(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check generalized 3- and 8-factor product rows and committed C* gauges, then the three-factor head-y binding. |
| inputs / outputs | Takes report accumulator; emits two product cursor/gauge pairs and one cancelled DeltaRuntime cursor report. |
| invariants | Each factor has two rows so output cardinality is 2^arity; base tuples=2*arity, each native leaf factor count=2, full-result count remains unavailable; G{y} test expects query_factors=3. |
| ownership | Runtime/cursors are local; accumulator retains serialized output; gauges/reports are values copied before storage. |
| failure | Reference evaluator or observation failures propagate; cursor is explicitly cancelled after reading its configuration. |
| cost | Exponential result drain is intentionally restricted to arity 3 and 8; gauge and cursor work are separate from product cardinality/CPU. |
| Design | tests/unit/cursor_observation_test.cpp:555, docs/observability.md:126, docs/result_cursors.md:101 |

## B0092

[Lines 606–667](../../../../../tests/unit/cursor_observation_test.cpp#L606); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observation_mode_matrix(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one unary physical result cursor through off, counters, timed, and trace timing combinations. |
| inputs / outputs | Takes ReportCollection; constructs one runtime per five rows of the mode matrix and emits each report. |
| invariants | Output and mandatory ResultCursorMetrics must be identical; off/counters/trace without timings call no clock; timed and trace-with-timings reconcile calls; only enabled modes publish runtime history. |
| ownership | Each cursor is consumed locally; report collection owns serialized JSON snapshots, not runtime state. |
| failure | Any discrepancy or writer cap failure throws; fake clock is cleared on normal completion. |
| cost | Five full cursor traversals plus fake-clock reads; clocks measure observation timing inputs, not CPU. JSON export allocations are outside mutation counters. |
| Design | tests/unit/cursor_observation_test.cpp:606, docs/observability.md:71, docs/observability.md:126, docs/result_cursors.md:101 |

## B0094

[Lines 669–765](../../../../../tests/unit/cursor_observation_test.cpp#L669); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void epoch_cursor_sources_and_invalidation(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise committed epoch-visible completions, witnesses, root/child visible keys, separator bucket, gauges, and rollback invalidation. |
| inputs / outputs | Takes report accumulator; starts committed view cursors and a staged after-view cursor, exporting each observation. |
| invariants | A04 outputs distinguish projected answers from witnesses and child-local E key 3; reports retain source/side/tentative identity; rollback after tentative row makes cursor failed/invalidated and releases lease. |
| ownership | Epoch view owns a read lease; each ResultCursor independently owns its logical runtime reference; report accumulator keeps JSON copies only. |
| failure | Invalidation is expected after pending.rollback; explicit view.close is used to release remaining view ownership; source query errors propagate. |
| cost | Drains multiple cursor routes and performs one staged update/rollback; gauge capture is committed-state inspection and never claims full answer cardinality. |
| Design | tests/unit/cursor_observation_test.cpp:669, docs/result_cursors.md:49, docs/result_cursors.md:76, docs/observability.md:126 |

## B0096

[Lines 767–934](../../../../../tests/unit/cursor_observation_test.cpp#L767); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifecycle_caps_and_failed_startup(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check admission guards, cursor copy/move/destruction, work-cap boundaries, failed startup/next, and invalid view construction. |
| inputs / outputs | Takes reports; uses unary committed row 5 plus separate cap fixture row 17 and exports lifecycle observations. |
| invariants | Pre-admission invalid/closed-view errors create no identity; saved observations remain immutable; exact measured work ceiling passes while N-1 fails; zero startup cap and next cap fail/release leases; constructor failure records admitted unconstructed startup failure. |
| ownership | Each cursor owns a read lease until exhaustion/cancel/failure/destruction; moved-from source no longer owns the lease; copied CursorObservation values remain independent. |
| failure | Checks exact error codes invalid_cursor_options, invalid_snapshot, invalid_cursor, resource_limit and invalid_fragment at their respective phases. |
| cost | Many cursor starts and next calls with abstract work limits; limits count runtime abstract operations, not elapsed CPU or bytes. Report serialization is separate. |
| Design | tests/unit/cursor_observation_test.cpp:767, docs/result_cursors.md:49, docs/result_cursors.md:76, docs/result_cursors.md:101, docs/observability.md:126 |

## B0098

[Lines 936–944](../../../../../tests/unit/cursor_observation_test.cpp#L936); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan string_unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one-column string unary plan for persistent new-failure and detached-owner cases. |
| inputs / outputs | No args; returns s(text) plan with text in the head. |
| invariants | The inserted payload string must be returned unchanged after OOM recovery. |
| ownership | The returned PhysicalPlan owns its catalog/query/tree metadata; fixture locals and runtime rows are separate values. |
| failure | Planner/lowering exceptions propagate; arity check explicitly rejects unsupported product fixtures. |
| cost | Constructs small test catalog/query/tree objects and lowers once; plan construction is outside measured cursor operations. |
| Design | tests/unit/cursor_observation_test.cpp:936, docs/result_cursors.md:18, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |

## B0100

[Lines 946–1016](../../../../../tests/unit/cursor_observation_test.cpp#L946); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void persistent_oom_and_nonallocating_copies(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject persistent C++ new failure at cursor factory and next, then verify fixed snapshots/cancel and same-owner retry. |
| inputs / outputs | Takes reports; arms threshold zero around runtime.core_results(), observation copies/cancel(), and next(). |
| invariants | Factory OOM is unconstructed startup failure with owner preserved; CursorObservation/ObservationSnapshot/config option copies and cancel() cause zero intercepted new calls; next OOM closes failed lease and retry returns payload on same owner. |
| ownership | Probe atomics and runtime owner are test-local; observations are owning value snapshots; cursor retains runtime state only while its lease is live. |
| failure | Expected std::bad_alloc is caught at factory/next; unexpected exceptions or failure to release lease fail the group. |
| cost | Counts/blocks calls through replaced C++ scalar/array/aligned new only; does not prove zero malloc/syscalls or zero MemoryAccount bytes; retry drain and report JSON are outside armed windows. |
| Design | tests/unit/cursor_observation_test.cpp:946, docs/result_cursors.md:76, docs/memory_accounts.md:52, docs/observability.md:126 |

## B0102

[Lines 1018–1066](../../../../../tests/unit/cursor_observation_test.cpp#L1018); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void detached_cursor_and_query_session(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a cursor remains usable after PhysicalRuntime facade destruction and QuerySession preserves the latest snapshot cursor summary through stop/drop. |
| inputs / outputs | Takes report collection; returns no direct result, stores two cursor observation JSON cases. |
| invariants | Detached cursor keeps stable owner and reaches exhausted; session snapshot cursor identity/owner survive stop/drop unchanged. |
| ownership | Detached cursor retains its logical support state through its shared owner while the physical facade dies; session retains fixed observation values, while report collection stores JSON. |
| failure | Cursor operations after facade destruction must succeed; session lifecycle errors propagate. |
| cost | One full result enumeration after facade destruction and a QuerySession snapshot; cursor abstract work excludes whole-state teardown costs. |
| Design | tests/unit/cursor_observation_test.cpp:1018, docs/result_cursors.md:49, docs/result_cursors.md:76, docs/observability.md:126 |

## B0104

[Lines 1068–1072](../../../../../tests/unit/cursor_observation_test.cpp#L1068); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_observation_options(const ObservationOptions& a, const ObservationOptions& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare all five requested ObservationOptions fields for exact retained configuration equality. |
| inputs / outputs | Takes mode, trace capacity, sample period/offset and trace_timings from two options; returns bool. |
| invariants | Equality includes mode, capacity, period, offset and timing toggle; no defaulting or normalization occurs here. |
| ownership | Borrows both option objects; no configuration or runtime state is retained. |
| failure | No expected exception. |
| cost | Fixed scalar comparisons; no observation clock reads. |
| Design | tests/unit/cursor_observation_test.cpp:1068, docs/observability.md:71 |

## B0106

[Lines 1074–1087](../../../../../tests/unit/cursor_observation_test.cpp#L1074); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_delta_options(const DeltaOptions& a, const DeltaOptions& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every nested DeltaOptions setting so the configuration snapshot test detects dropped options. |
| inputs / outputs | Takes two DeltaOptions references and returns bool after comparing support, physical, delta, cursor, epoch-view and spool limits. |
| invariants | Includes support work/support limit/order/capture/observation, physical work/derivation, mode/view/live-maintenance/completion, cursor/epoch-view limits, and spool row/byte limits. |
| ownership | Borrows both values and nested options; no runtime ownership. |
| failure | No expected exception. |
| cost | Fixed field comparisons plus same_observation_options; no allocation or measurement. |
| Design | tests/unit/cursor_observation_test.cpp:1074, docs/observability.md:71 |

## B0108

[Lines 1089–1112](../../../../../tests/unit/cursor_observation_test.cpp#L1089); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions exact_binding_options(ObservationMode mode = ObservationMode::timed) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct exact nested DeltaOptions sentinels for testing immutable cursor binding. |
| inputs / outputs | Takes optional ObservationMode default timed; returns value with literal work/support/physical/derivation, trace, view/mode/completion, cursor/epoch and spool settings. |
| invariants | Sentinel constants 713, 911, 1409, 1601, 1801, 1901 and 2003 make omitted/mutated nested settings observable; capture_transitions false and trace capacity19/period3/offset1/timing false are explicit. |
| ownership | Returned options own only scalar/value fields and are copied into runtime configuration. |
| failure | No expected exception. |
| cost | Fixed option initialization; no runtime operation. |
| Design | tests/unit/cursor_observation_test.cpp:1089, docs/observability.md:71 |

## B0110

[Lines 1114–1131](../../../../../tests/unit/cursor_observation_test.cpp#L1114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_binding(const ObservationConfiguration& actual, const DeltaOptions& requested,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that one ObservationConfiguration preserved exact request values and resolved owner/generation/mode/factors. |
| inputs / outputs | Takes configuration, requested options, expected mode/completion/owner/generation/saturation/factor count; returns void after checks. |
| invariants | Compares copied requested options, resolved mode/completion/live-maintenance/view, nonzero physical support owner, generation flags, and fixture C* factor count. |
| ownership | Configuration is borrowed; requested_options() produces value copy; no reference is retained. |
| failure | Any mismatch fails via check(); option-copy exception would propagate. |
| cost | Copies and compares fixed option values; separate persistent-OOM case checks these snapshot reads under replacement-new failure. |
| Design | tests/unit/cursor_observation_test.cpp:1114, docs/observability.md:71 |

## B0112

[Lines 1133–1277](../../../../../tests/unit/cursor_observation_test.cpp#L1133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void mode_binding_and_bootstrap_cursors(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin DeltaRuntime cursor configuration across mode switches, bootstrap, failure, no-op switches and generation saturation. |
| inputs / outputs | Takes report collection; builds exact nested DeltaOptions, starts cursors and mode transitions, then emits saved reports. |
| invariants | Options preserve nested support/physical/work/trace/spool values; owner and C* factor count bind at cursor start; bootstrap cursor is epoch keys; no-op switch keeps generation; failed bootstrap preserves current mode/config; max generation distinguishes exact unsaturated max from saturated diagnostic state. |
| ownership | Configuration and CursorObservation are immutable value snapshots; runtime owns active lease/config; test generation hook is reset by local destructor and group cleanup. |
| failure | Mode switch while leased returns runtime_busy; failed bootstrap expects resource_limit and remains ready; moved-from cursors elsewhere are separate lifecycle tests. |
| cost | Mode transitions, bootstrap cursor and test seam change only diagnostic generation; snapshot copies are separately checked under intercepted new=0; no CPU theorem. |
| Design | tests/unit/cursor_observation_test.cpp:1133, docs/observability.md:71, docs/result_cursors.md:49, docs/result_cursors.md:76 |

## B0114

[Lines 1279–1337](../../../../../tests/unit/cursor_observation_test.cpp#L1279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void delta_nested_clock_and_unsampled_trace(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconcile clocks nested in a timed DeltaRuntime update and prove cursor timing remains enabled for an unsampled trace sequence. |
| inputs / outputs | Takes report accumulator; applies an update after switching to delta, then enumerates current results and runs a sampled-control trace config. |
| invariants | Within attempt, global calls equal delta_clock_reads+nested_cursor_clock_reads with nested reads positive; later current cursor reads do not alter saved attempt; sequence 1 is unsampled for period17/offset16 but cursor clock reads remain available. |
| ownership | Delta attempt summary and cursor observations are independent copies; runtime owns histories; reports serialize copied values. |
| failure | No synthetic failure is expected; clock hook is cleared after each branch. |
| cost | Counts test fake-clock calls; elapsed values are fake and not CPU; nested cursor read count is already within cursor clock reads and is not added twice. |
| Design | tests/unit/cursor_observation_test.cpp:1279, docs/observability.md:71, docs/result_cursors.md:101 |

## B0116

[Lines 1339–1364](../../../../../tests/unit/cursor_observation_test.cpp#L1339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fake_clock_zero_and_regression(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish backward test-clock timing from an available exact-zero startup duration. |
| inputs / outputs | Takes ReportCollection; scripts {10,5} and {11,11} for separate timed cursors. |
| invariants | Backward clock makes startup timing unavailable and increments regression metric; equal endpoints keep availability=available and value=0. |
| ownership | Each report is a value copy; scripted clock array is test-owned and cleared after capture. |
| failure | Clock regression is an observed result, not thrown; writer failures propagate. |
| cost | Two small cursor starts/cancels and fixed fake samples; no wall-clock/CPU measurement. |
| Design | tests/unit/cursor_observation_test.cpp:1339, docs/observability.md:71, docs/observability.md:126 |

## B0118

[Lines 1366–1460](../../../../../tests/unit/cursor_observation_test.cpp#L1366); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void committed_gauges_and_private_guards(ReportCollection& reports) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check committed gauges across aliases, rollback, insert/no-op/delete, exact zero, and support-only scope. |
| inputs / outputs | Takes report accumulator; runs physical self-join and support-only runtime with observation off, writing gauge JSON. |
| invariants | One physical table counts once despite aliases; per-node records/survivors/projected keys and E-factor values match literals; unsupported answer/memory/durable gauges unavailable; pending writer blocks read; rollback unchanged; insert/no-op/delete update counts exactly; zero differs from unavailable. |
| ownership | Gauge result is a copied value; pending transaction owns private work until rollback; report collection owns JSON only. |
| failure | Gauge read while pending throws runtime_busy; all successful reads occur at committed barrier. |
| cost | Uses fixed state/table scans and JSON capture; gauges are not query answer cardinality and byte cap does not bound capture memory/CPU. |
| Design | tests/unit/cursor_observation_test.cpp:1366, docs/observability.md:126, docs/result_cursors.md:49, docs/memory_accounts.md:722 |

## B0119

[Lines 1461–1463](../../../../../tests/unit/cursor_observation_test.cpp#L1461); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1461-L1463:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in cursor_observation_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/cursor_observation_test.cpp](../../../../../tests/unit/cursor_observation_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0120

[Lines 1464–1516](../../../../../tests/unit/cursor_observation_test.cpp#L1464); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all cursor observation scenario groups and emit one JSON object with cases, reports, and gauge reports. |
| inputs / outputs | No arguments; returns process status, writes machine-readable stdout and progress/failure stderr. |
| invariants | Every group completes before final JSON; main-level catch clears clock/new/generation hooks and returns 1; normal completion clears clock and returns 0. |
| ownership | ReportCollection owns serialized strings until process output; runtimes/cursors are destroyed by group scopes. |
| failure | Any assertion/serialization/standard exception aborts remaining scenarios and yields status 1. |
| cost | Runs all fixture/test costs in one executable; output generation can allocate; it does not itself prove an external consumer schema check ran. |
| Design | tests/unit/cursor_observation_test.cpp:1464, docs/observability.md:126, docs/verification/o07-cursor-observation-test-fixture-proposal/README.md:55 |
