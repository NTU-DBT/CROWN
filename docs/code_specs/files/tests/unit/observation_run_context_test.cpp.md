# `tests/unit/observation_run_context_test.cpp` — block usage map

[Source](../../../../../tests/unit/observation_run_context_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f5ed5112547a898d3ac10c576a1d2829c7cae4124353c3aa86526c255b7fbf9e`. 1537 lines partitioned into 120 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–30](../../../../../tests/unit/observation_run_context_test.cpp#L1) | Imports dependencies. | growth new · [reviewed contract](#b0001) |
| [B0002 · 31–38](../../../../../tests/unit/observation_run_context_test.cpp#L31) | declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 39–47](../../../../../tests/unit/observation_run_context_test.cpp#L39) | Callable definition: void note() | calls load, fetch_add, store · [reviewed contract](#b0003) |
| [B0004 · 48–48](../../../../../tests/unit/observation_run_context_test.cpp#L48) | Explanatory comments or spacing. |  |
| [B0005 · 49–53](../../../../../tests/unit/observation_run_context_test.cpp#L49) | Callable definition: void* allocate(std::size_t bytes) | calls note, std::malloc; returns result; growth allocate, malloc · [reviewed contract](#b0005) |
| [B0006 · 54–54](../../../../../tests/unit/observation_run_context_test.cpp#L54) | Explanatory comments or spacing. |  |
| [B0007 · 55–61](../../../../../tests/unit/observation_run_context_test.cpp#L55) | Callable definition: void* allocate_aligned(std::size_t bytes, std::size_t alignment) | calls note, posix_memalign; returns result · [reviewed contract](#b0007) |
| [B0008 · 62–62](../../../../../tests/unit/observation_run_context_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0009 · 63–67](../../../../../tests/unit/observation_run_context_test.cpp#L63) | Type/record definition: struct Measurement |  · [reviewed contract](#b0009) |
| [B0010 · 68–68](../../../../../tests/unit/observation_run_context_test.cpp#L68) | Explanatory comments or spacing. |  |
| [B0011 · 69–89](../../../../../tests/unit/observation_run_context_test.cpp#L69) | Callable definition: template &lt;class Action&gt; void measure(Action&& action, std::size_t fail_index, Measurement& result) | calls store, load · [reviewed contract](#b0011) |
| [B0012 · 90–90](../../../../../tests/unit/observation_run_context_test.cpp#L90) | Explanatory comments or spacing. |  |
| [B0013 · 91–96](../../../../../tests/unit/observation_run_context_test.cpp#L91) | Callable definition: void disarm() noexcept | calls store · [reviewed contract](#b0013) |
| [B0014 · 97–98](../../../../../tests/unit/observation_run_context_test.cpp#L97) | Closes surrounding scope/type. | source comment (unverified): // namespace allocation_probe · [reviewed contract](#b0014) |
| [B0015 · 99–99](../../../../../tests/unit/observation_run_context_test.cpp#L99) | Callable definition: void* operator new(std::size_t bytes) | calls allocation_probe::allocate; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0015) |
| [B0016 · 100–100](../../../../../tests/unit/observation_run_context_test.cpp#L100) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns allocation_probe::allocate(bytes); growth allocate, new · [reviewed contract](#b0016) |
| [B0017 · 101–103](../../../../../tests/unit/observation_run_context_test.cpp#L101) | Callable definition: void* operator new(std::size_t bytes, std::align_val_t alignment) | calls allocation_probe::allocate_aligned; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0017) |
| [B0018 · 104–106](../../../../../tests/unit/observation_run_context_test.cpp#L104) | Callable definition: void* operator new\[\](std::size_t bytes, std::align_val_t alignment) | calls ; returns allocation_probe::allocate_aligned(bytes, static_cast&lt;std::size_t&gt;(alignment)); growth new · [reviewed contract](#b0018) |
| [B0019 · 107–107](../../../../../tests/unit/observation_run_context_test.cpp#L107) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0019) |
| [B0020 · 108–108](../../../../../tests/unit/observation_run_context_test.cpp#L108) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0020) |
| [B0021 · 109–109](../../../../../tests/unit/observation_run_context_test.cpp#L109) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0021) |
| [B0022 · 110–110](../../../../../tests/unit/observation_run_context_test.cpp#L110) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0022) |
| [B0023 · 111–111](../../../../../tests/unit/observation_run_context_test.cpp#L111) | Callable definition: void operator delete(void* pointer, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0023) |
| [B0024 · 112–112](../../../../../tests/unit/observation_run_context_test.cpp#L112) | Callable definition: void operator delete\[\](void* pointer, std::align_val_t) noexcept | calls  · [reviewed contract](#b0024) |
| [B0025 · 113–115](../../../../../tests/unit/observation_run_context_test.cpp#L113) | Callable definition: void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept | calls std::free · [reviewed contract](#b0025) |
| [B0026 · 116–118](../../../../../tests/unit/observation_run_context_test.cpp#L116) | Callable definition: void operator delete\[\](void* pointer, std::size_t, std::align_val_t) noexcept | calls  · [reviewed contract](#b0026) |
| [B0027 · 119–125](../../../../../tests/unit/observation_run_context_test.cpp#L119) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0027) |
| [B0028 · 126–126](../../../../../tests/unit/observation_run_context_test.cpp#L126) | Callable definition: std::uint64_t fake_clock() noexcept | calls ; returns ++optional_clock_reads · [reviewed contract](#b0028) |
| [B0029 · 127–127](../../../../../tests/unit/observation_run_context_test.cpp#L127) | Explanatory comments or spacing. |  |
| [B0030 · 128–130](../../../../../tests/unit/observation_run_context_test.cpp#L128) | Callable definition: void check(bool condition, std::string_view message) | calls std::runtime_error, std::string; guard void check(bool condition, std::string_view message) { · [reviewed contract](#b0030) |
| [B0031 · 131–131](../../../../../tests/unit/observation_run_context_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0032 · 132–142](../../../../../tests/unit/observation_run_context_test.cpp#L132) | Callable definition: template &lt;class Action&gt; void expect_error(std::string_view code, Action&& action, std::string_view message) | calls check, code; guard check(error.code() == code, message); · [reviewed contract](#b0032) |
| [B0033 · 143–143](../../../../../tests/unit/observation_run_context_test.cpp#L143) | Explanatory comments or spacing. |  |
| [B0034 · 144–144](../../../../../tests/unit/observation_run_context_test.cpp#L144) | Callable definition: Value integer(std::int64_t value) | calls ; returns Value{value} · [reviewed contract](#b0034) |
| [B0035 · 145–145](../../../../../tests/unit/observation_run_context_test.cpp#L145) | Callable definition: Row row(std::int64_t value) | calls integer; returns Row{integer(value)} · [reviewed contract](#b0035) |
| [B0036 · 146–146](../../../../../tests/unit/observation_run_context_test.cpp#L146) | Callable definition: Row edge(std::int64_t x, std::int64_t y) | calls integer; returns Row{integer(x), integer(y)} · [reviewed contract](#b0036) |
| [B0037 · 147–161](../../../../../tests/unit/observation_run_context_test.cpp#L147) | declares types or opens a type body. |  · [reviewed contract](#b0037) |
| [B0038 · 162–171](../../../../../tests/unit/observation_run_context_test.cpp#L162) | Callable definition: QFixture() : plan(planner::lower_tree(catalog, query, FreeConnexTree{ NodeId{0}, {{"R", NodeKind::native, {VariableId{0}, Variabl… | calls plan, planner::lower_tree, resize, insert; growth insert, resize · [reviewed contract](#b0038) |
| [B0039 · 172–172](../../../../../tests/unit/observation_run_context_test.cpp#L172) | Explanatory comments or spacing. |  |
| [B0040 · 173–177](../../../../../tests/unit/observation_run_context_test.cpp#L173) | Callable definition: \[\[nodiscard\]\] Database with_s() const | calls insert, row; returns result; growth insert · [reviewed contract](#b0040) |
| [B0041 · 178–178](../../../../../tests/unit/observation_run_context_test.cpp#L178) | Explanatory comments or spacing. |  |
| [B0042 · 179–183](../../../../../tests/unit/observation_run_context_test.cpp#L179) | Callable definition: \[\[nodiscard\]\] Database two_roots() const | calls insert, edge; returns result; growth insert · [reviewed contract](#b0042) |
| [B0043 · 184–185](../../../../../tests/unit/observation_run_context_test.cpp#L184) | Closes surrounding scope/type. |  · [reviewed contract](#b0043) |
| [B0044 · 186–194](../../../../../tests/unit/observation_run_context_test.cpp#L186) | Callable definition: ObservationOptions observation_options(ObservationMode mode) | calls ; returns result · [reviewed contract](#b0044) |
| [B0045 · 195–195](../../../../../tests/unit/observation_run_context_test.cpp#L195) | Explanatory comments or spacing. |  |
| [B0046 · 196–216](../../../../../tests/unit/observation_run_context_test.cpp#L196) | Callable definition: DeltaOptions exact_delta_options(ObservationMode mode = ObservationMode::counters) | calls observation_options; returns result · [reviewed contract](#b0046) |
| [B0047 · 217–217](../../../../../tests/unit/observation_run_context_test.cpp#L217) | Explanatory comments or spacing. |  |
| [B0048 · 218–222](../../../../../tests/unit/observation_run_context_test.cpp#L218) | Callable definition: bool same_observation_options(const ObservationOptions& a, const ObservationOptions& b) | calls ; returns a.mode == b.mode && a.trace_capacity == b.trace_capacity && · [reviewed contract](#b0048) |
| [B0049 · 223–223](../../../../../tests/unit/observation_run_context_test.cpp#L223) | Explanatory comments or spacing. |  |
| [B0050 · 224–240](../../../../../tests/unit/observation_run_context_test.cpp#L224) | Callable definition: bool same_delta_options(const DeltaOptions& a, const DeltaOptions& b) | calls same_observation_options; returns a.physical.support.work_limit == b.physical.support.work_limit && · [reviewed contract](#b0050) |
| [B0051 · 241–241](../../../../../tests/unit/observation_run_context_test.cpp#L241) | Explanatory comments or spacing. |  |
| [B0052 · 242–247](../../../../../tests/unit/observation_run_context_test.cpp#L242) | Callable definition: bool same_input_limits(const io::InputLimits& a, const io::InputLimits& b) | calls ; returns a.record_bytes == b.record_bytes && a.field_bytes == b.field_bytes && · [reviewed contract](#b0052) |
| [B0053 · 248–248](../../../../../tests/unit/observation_run_context_test.cpp#L248) | Explanatory comments or spacing. |  |
| [B0054 · 249–255](../../../../../tests/unit/observation_run_context_test.cpp#L249) | Callable definition: bool same_input_options(const io::InputOptions& a, const io::InputOptions& b) | calls same_input_limits; returns a.format == b.format && same_input_limits(a.limits, b.limits) && · [reviewed contract](#b0054) |
| [B0055 · 256–256](../../../../../tests/unit/observation_run_context_test.cpp#L256) | Explanatory comments or spacing. |  |
| [B0056 · 257–260](../../../../../tests/unit/observation_run_context_test.cpp#L257) | Callable definition: bool same_snapshot_limits(const SnapshotLimits& a, const SnapshotLimits& b) | calls ; returns a.rows == b.rows && a.bytes == b.bytes && · [reviewed contract](#b0056) |
| [B0057 · 261–261](../../../../../tests/unit/observation_run_context_test.cpp#L261) | Explanatory comments or spacing. |  |
| [B0058 · 262–267](../../../../../tests/unit/observation_run_context_test.cpp#L262) | Callable definition: bool same_build(const std::optional&lt;BuildOptions&gt;& a, const std::optional&lt;BuildOptions&gt;& b) | calls has_value; returns false; true · [reviewed contract](#b0058) |
| [B0059 · 268–268](../../../../../tests/unit/observation_run_context_test.cpp#L268) | Explanatory comments or spacing. |  |
| [B0060 · 269–274](../../../../../tests/unit/observation_run_context_test.cpp#L269) | Callable definition: void check_initialization(const InitializationContext& actual, InitializationRoute route, std::optional&lt;BuildOptions&gt; applied, st… | calls check, same_build; guard check(actual.route == route && same_build(actual.applied_build, applied), label); · [reviewed contract](#b0060) |
| [B0061 · 275–275](../../../../../tests/unit/observation_run_context_test.cpp#L275) | Explanatory comments or spacing. |  |
| [B0062 · 276–281](../../../../../tests/unit/observation_run_context_test.cpp#L276) | Callable definition: Relation drain(SupportRuntime::ResultCursor cursor) | calls next, check, insert, crown::storage::export_row; guard check(rows.insert(crown::storage::export_row(tuple-&gt;values())).second, "Q result cursor emitted a d…; returns rows; growth insert; 1 loop sites · [reviewed contract](#b0062) |
| [B0063 · 282–282](../../../../../tests/unit/observation_run_context_test.cpp#L282) | Explanatory comments or spacing. |  |
| [B0064 · 283–285](../../../../../tests/unit/observation_run_context_test.cpp#L283) | Callable definition: Relation evaluate(const QFixture& fixture, const Database& database) | calls reference::evaluate; returns reference::evaluate(fixture.catalog, fixture.query, database) · [reviewed contract](#b0064) |
| [B0065 · 286–286](../../../../../tests/unit/observation_run_context_test.cpp#L286) | Explanatory comments or spacing. |  |
| [B0066 · 287–291](../../../../../tests/unit/observation_run_context_test.cpp#L287) | Callable definition: DeltaOptions mode_options(ObservationMode mode) | calls exact_delta_options; returns result · [reviewed contract](#b0066) |
| [B0067 · 292–292](../../../../../tests/unit/observation_run_context_test.cpp#L292) | Explanatory comments or spacing. |  |
| [B0068 · 293–296](../../../../../tests/unit/observation_run_context_test.cpp#L293) | Callable definition: DeltaRuntime make_delta_runtime(const QFixture& fixture, const Database& initial, DeltaOptions options = mode_options(Observation… | calls mode_options, DeltaRuntime::initialize; returns DeltaRuntime::initialize(fixture.plan, initial, options) · [reviewed contract](#b0068) |
| [B0069 · 297–297](../../../../../tests/unit/observation_run_context_test.cpp#L297) | Explanatory comments or spacing. |  |
| [B0070 · 298–310](../../../../../tests/unit/observation_run_context_test.cpp#L298) | Callable definition: void check_output(const ObservationSummary& summary, const OutputDisposition& expected, std::string_view message) | calls check, has_value; guard check(summary.output.has_value(), message); · [reviewed contract](#b0070) |
| [B0071 · 311–311](../../../../../tests/unit/observation_run_context_test.cpp#L311) | Explanatory comments or spacing. |  |
| [B0072 · 312–318](../../../../../tests/unit/observation_run_context_test.cpp#L312) | Callable definition: OutputDisposition disposition(bool discard_requested, bool completion_drain, bool retention_disabled, bool prepared, bool publish… | calls ; returns {discard_requested, completion_drain, retention_disabled, prepared, · [reviewed contract](#b0072) |
| [B0073 · 319–319](../../../../../tests/unit/observation_run_context_test.cpp#L319) | Explanatory comments or spacing. |  |
| [B0074 · 320–325](../../../../../tests/unit/observation_run_context_test.cpp#L320) | Callable definition: void check_metric(const ObservationSummary& summary, MetricId id, std::uint64_t value, std::string_view message) | calls metric, check; guard check(metric.availability == MetricAvailability::available && metric.value == value, · [reviewed contract](#b0074) |
| [B0075 · 326–326](../../../../../tests/unit/observation_run_context_test.cpp#L326) | Explanatory comments or spacing. |  |
| [B0076 · 327–362](../../../../../tests/unit/observation_run_context_test.cpp#L327) | Callable definition: void check_context(const std::shared_ptr&lt;const SessionRunContext&gt;& context, SessionInputKind kind, const io::InputOptions& input,… | calls check, same_input_options, export_value, has_value; guard check(context != nullptr, "session run context handle is null"); · [reviewed contract](#b0076) |
| [B0077 · 363–363](../../../../../tests/unit/observation_run_context_test.cpp#L363) | Explanatory comments or spacing. |  |
| [B0078 · 364–397](../../../../../tests/unit/observation_run_context_test.cpp#L364) | Callable definition: void check_json_delta(const Json& actual, const DeltaOptions& expected) | calls check, is_null, check_optional; guard check(actual\["requested_mode"\] == "delta" && · [reviewed contract](#b0078) |
| [B0079 · 398–398](../../../../../tests/unit/observation_run_context_test.cpp#L398) | Explanatory comments or spacing. |  |
| [B0080 · 399–454](../../../../../tests/unit/observation_run_context_test.cpp#L399) | Callable definition: void check_json_input(const Json& actual, const io::InputOptions& expected) | calls check, name, is_null, is_array; guard check(actual\["format"\] == name(), "exported input format differs from run context");; returns @; @; growth insert; 1 loop sites · [reviewed contract](#b0080) |
| [B0081 · 455–455](../../../../../tests/unit/observation_run_context_test.cpp#L455) | Explanatory comments or spacing. |  |
| [B0082 · 456–510](../../../../../tests/unit/observation_run_context_test.cpp#L456) | Callable definition: void verify_session_export(const std::string& encoded, const SessionRunContext& expected, std::string_view input_kind, std::strin… | calls Json::parse, check, check_json_input, export_value; guard check(parsed\["format"\] == "crown_run_context" && parsed\["version"\] == 1 &&; 1 loop sites · [reviewed contract](#b0082) |
| [B0083 · 511–511](../../../../../tests/unit/observation_run_context_test.cpp#L511) | Explanatory comments or spacing. |  |
| [B0084 · 512–593](../../../../../tests/unit/observation_run_context_test.cpp#L512) | Callable definition: void scenario_initialization_routes_and_build_options() | calls exact_delta_options, resize, empty_constructor, check_initialization; guard check(evaluate(fixture, direct_empty.snapshot().physical) ==; growth resize · [reviewed contract](#b0084) |
| [B0085 · 594–594](../../../../../tests/unit/observation_run_context_test.cpp#L594) | Explanatory comments or spacing. |  |
| [B0086 · 595–605](../../../../../tests/unit/observation_run_context_test.cpp#L595) | Callable definition: io::InputLimits custom_limits() | calls ; returns limits · [reviewed contract](#b0086) |
| [B0087 · 606–606](../../../../../tests/unit/observation_run_context_test.cpp#L606) | Explanatory comments or spacing. |  |
| [B0088 · 607–613](../../../../../tests/unit/observation_run_context_test.cpp#L607) | Callable definition: SnapshotLimits custom_snapshot() | calls ; returns result · [reviewed contract](#b0088) |
| [B0089 · 614–614](../../../../../tests/unit/observation_run_context_test.cpp#L614) | Explanatory comments or spacing. |  |
| [B0090 · 615–617](../../../../../tests/unit/observation_run_context_test.cpp#L615) | Callable definition: io::QueueLimits custom_queue(std::size_t salt) | calls ; returns {5 + salt, 17 + salt, 12001 + salt} · [reviewed contract](#b0090) |
| [B0091 · 618–618](../../../../../tests/unit/observation_run_context_test.cpp#L618) | Explanatory comments or spacing. |  |
| [B0092 · 619–626](../../../../../tests/unit/observation_run_context_test.cpp#L619) | Callable definition: std::shared_ptr&lt;const DeclaredBenchmarkContext&gt; session_label() | calls std::string, std::move; returns std::make_shared&lt;const DeclaredBenchmarkContext&gt;(std::move(labels)); growth make_shared · [reviewed contract](#b0092) |
| [B0093 · 627–627](../../../../../tests/unit/observation_run_context_test.cpp#L627) | Explanatory comments or spacing. |  |
| [B0094 · 628–648](../../../../../tests/unit/observation_run_context_test.cpp#L628) | Callable definition: void check_session_survived_drop( std::shared_ptr&lt;const SessionRunContext&gt; saved, SessionInputKind kind, const io::InputOptions& … | calls check_context, check, io::write_run_context_json, verify_session_export; guard check(after_drop.session_attached && after_drop.session_context == saved && · [reviewed contract](#b0094) |
| [B0095 · 649–649](../../../../../tests/unit/observation_run_context_test.cpp#L649) | Explanatory comments or spacing. |  |
| [B0096 · 650–816](../../../../../tests/unit/observation_run_context_test.cpp#L650) | Callable definition: void scenario_session_context_owned_stream_typed_window_and_admission_oom() | calls exact_delta_options, custom_snapshot, custom_limits, session_label; guard check(context-&gt;window-&gt;fifo==policy && encoded\["session"\]\["window"\]\["fifo"\]==token,; growth insert, make_unique; 2 loop sites; source comment (unverified): // Typed queues use queue/batch byte limits. · [reviewed contract](#b0096) |
| [B0097 · 817–817](../../../../../tests/unit/observation_run_context_test.cpp#L817) | Explanatory comments or spacing. |  |
| [B0098 · 818–820](../../../../../tests/unit/observation_run_context_test.cpp#L818) | Callable definition: PhysicalSetUpdate insert_s(std::uint64_t sequence) | calls row; returns {sequence, TableId{1}, SetOperation::insert, row(9)}; growth insert · [reviewed contract](#b0098) |
| [B0099 · 821–821](../../../../../tests/unit/observation_run_context_test.cpp#L821) | Explanatory comments or spacing. |  |
| [B0100 · 822–824](../../../../../tests/unit/observation_run_context_test.cpp#L822) | Callable definition: PhysicalSetUpdate erase_s(std::uint64_t sequence) | calls row; returns {sequence, TableId{1}, SetOperation::erase, row(9)} · [reviewed contract](#b0100) |
| [B0101 · 825–825](../../../../../tests/unit/observation_run_context_test.cpp#L825) | Explanatory comments or spacing. |  |
| [B0102 · 826–1009](../../../../../tests/unit/observation_run_context_test.cpp#L826) | Callable definition: void scenario_actual_output_disposition_lifecycle() | calls make_delta_runtime, begin, insert_s, start_drain; guard check(epoch.remaining() == 0 && !epoch.active(),; growth insert · [reviewed contract](#b0102) |
| [B0103 · 1010–1010](../../../../../tests/unit/observation_run_context_test.cpp#L1010) | Explanatory comments or spacing. |  |
| [B0104 · 1011–1022](../../../../../tests/unit/observation_run_context_test.cpp#L1011) | Callable definition: std::shared_ptr&lt;const DeclaredBenchmarkContext&gt; benchmark_context( std::optional&lt;std::string&gt; run, std::optional&lt;std::string&gt; inp… | calls std::move; returns std::make_shared&lt;const DeclaredBenchmarkContext&gt;(std::move(labels)); growth make_shared · [reviewed contract](#b0104) |
| [B0105 · 1023–1023](../../../../../tests/unit/observation_run_context_test.cpp#L1023) | Explanatory comments or spacing. |  |
| [B0106 · 1024–1027](../../../../../tests/unit/observation_run_context_test.cpp#L1024) | Callable definition: bool same_labels(const BenchmarkLabels& a, const BenchmarkLabels& b) | calls ; returns a.run == b.run && a.input_adapter == b.input_adapter && · [reviewed contract](#b0106) |
| [B0107 · 1028–1028](../../../../../tests/unit/observation_run_context_test.cpp#L1028) | Explanatory comments or spacing. |  |
| [B0108 · 1029–1037](../../../../../tests/unit/observation_run_context_test.cpp#L1029) | Callable definition: void check_attempt_labels(const ObservationSummary& summary, const BenchmarkLabels& expected, std::uint64_t sequence, Observation… | calls check, same_labels, labels; guard check(summary.sequence == sequence && summary.outcome == outcome && · [reviewed contract](#b0108) |
| [B0109 · 1038–1038](../../../../../tests/unit/observation_run_context_test.cpp#L1038) | Explanatory comments or spacing. |  |
| [B0110 · 1039–1168](../../../../../tests/unit/observation_run_context_test.cpp#L1039) | Callable definition: void scenario_callbacks_begin_bound_labels_and_utf8_export() | calls make_delta_runtime, mode_options, benchmark_context, std::string; guard check(same_labels(runtime.observations().current_declared_benchmark-&gt;labels(),; growth insert · [reviewed contract](#b0110) |
| [B0111 · 1169–1169](../../../../../tests/unit/observation_run_context_test.cpp#L1169) | Explanatory comments or spacing. |  |
| [B0112 · 1170–1298](../../../../../tests/unit/observation_run_context_test.cpp#L1170) | Callable definition: void scenario_callback_retries_deferred_discard_and_oom() | calls make_delta_runtime, two_roots, mode_options, apply; guard check(epoch.remaining() == 2,; growth insert; source comment (unverified): // Deferred until the currently borrowed row's callback returns. · [reviewed contract](#b0112) |
| [B0113 · 1299–1299](../../../../../tests/unit/observation_run_context_test.cpp#L1299) | Explanatory comments or spacing. |  |
| [B0114 · 1300–1304](../../../../../tests/unit/observation_run_context_test.cpp#L1300) | Type/record definition: struct ModeMatrixResult |  · [reviewed contract](#b0114) |
| [B0115 · 1305–1305](../../../../../tests/unit/observation_run_context_test.cpp#L1305) | Explanatory comments or spacing. |  |
| [B0116 · 1306–1505](../../../../../tests/unit/observation_run_context_test.cpp#L1306) | Callable definition: void scenario_mode_parity_work_failures_clock_and_rollback() | calls detail::set_observation_clock_for_testing, ~RestoreClock, mode_options, DeltaRuntime::initialize; guard check(epoch && epoch-&gt;remaining() == 1,; returns record.kind == TraceKind::commit; record.kind == TraceKind::commit; growth emplace, insert; 1 loop sites; source comment (unverified): // Closing an already prepared result and rolling back an unpublished · [reviewed contract](#b0116) |
| [B0117 · 1506–1506](../../../../../tests/unit/observation_run_context_test.cpp#L1506) | Explanatory comments or spacing. |  |
| [B0118 · 1507–1512](../../../../../tests/unit/observation_run_context_test.cpp#L1507) | Callable definition: template &lt;class Action&gt; void run_group(std::string_view name, Action&& action) | calls  · [reviewed contract](#b0118) |
| [B0119 · 1513–1514](../../../../../tests/unit/observation_run_context_test.cpp#L1513) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0119) |
| [B0120 · 1515–1537](../../../../../tests/unit/observation_run_context_test.cpp#L1515) | Callable definition: int main() | calls run_group, allocation_probe::disarm, detail::set_observation_clock_for_testing, what; returns 0; 1 · [reviewed contract](#b0120) |

## B0001

[Lines 1–30](../../../../../tests/unit/observation_run_context_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L30:sha256:55f520fe593412516e47a59c2c3046f53e41acf0afd745f3f15d146a43e452a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare observation_run_context_test.cpp: include "crown/api/error.hpp", "crown/io/batch.hpp", "crown/io/ingest.hpp", "crown/io/run_context.hpp", "crown/planner/lower.hpp", "crown/runtime/delta.hpp", "crown/runtime/observation.hpp", "crown/runtime/session.hpp", "crown/runtime/window.hpp", "evaluator.hpp", &lt;nlohmann/json.hpp&gt;, &lt;atomic&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;set&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 31–38](../../../../../tests/unit/observation_run_context_test.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L38:sha256:2723bdbd7a3ee59f15c14e7dfc233b3836e9ac7523191d4f848bffa82daf55e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare observation_run_context_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. Atomic counter storage and later atomic accesses belong to the test probe, not an engine timing or allocation measure. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 39–47](../../../../../tests/unit/observation_run_context_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void note() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record and apply the atomic allocation probe to one replaced allocation request. |
| inputs / outputs | No inputs; if inactive returns; if active it increments count, compares the pre-increment index with fail_at, and updates failures/injected before throwing std::bad_alloc. |
| invariants | With fail_at=i, calls at indices below i pass the probe and the call at i throws; subsequent active calls also fail because count remains &gt;= i. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0005

[Lines 49–53](../../../../../tests/unit/observation_run_context_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate storage for ordinary scalar/array replacement new. |
| inputs / outputs | Byte size enters; note() runs, malloc(1) is used for size zero, and a pointer or std::bad_alloc exits. |
| invariants | The wrapper uses malloc-backed storage and counts only when the probe is active. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0007

[Lines 55–61](../../../../../tests/unit/observation_run_context_test.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* allocate_aligned(std::size_t bytes, std::size_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate aligned storage for the aligned replacement new family. |
| inputs / outputs | Byte size and alignment enter; note() runs, then posix_memalign returns storage or failure becomes std::bad_alloc. |
| invariants | For size zero it requests alignment bytes; direct posix_memalign calls do not pass through this function. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0009

[Lines 63–67](../../../../../tests/unit/observation_run_context_test.cpp#L63); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Measurement {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the measured allocation-call count, injected-failure count, and whether injection occurred. |
| inputs / outputs | Three fields default to zero/false and receive a snapshot from measure(). |
| invariants | These are request counts/flags, not byte totals or account memory statistics. |
| ownership | The aggregate owns three scalar measurements and no allocation or runtime. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Three scalar fields. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0011

[Lines 69–89](../../../../../tests/unit/observation_run_context_test.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void measure(Action&& action, std::size_t fail_index, Measurement& result) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Measure one action with the allocation probe armed at a chosen request index. |
| inputs / outputs | Action, fail index, and output Measurement enter; resets atomic counters/flags, arms probe, executes action, then stores call/failure/injected counts and disables active on either exit. |
| invariants | On any exception the probe becomes inactive before the original exception is rethrown; fail_at remains until disarm or the next measure call. |
| ownership | Borrows the action and output Measurement; action-created objects remain owned by the caller/action scope. |
| failure | Catches all exceptions only to disarm and record counters, then immediately rethrows. In successful calibration, no injected fault is requested using no_failure. |
| cost | Counts every replaced new request in the action; it does not measure bytes or calls outside those replacement overloads. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0013

[Lines 91–96](../../../../../tests/unit/observation_run_context_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void disarm() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable allocation injection and clear failure indicators after an admission attempt. |
| inputs / outputs | No inputs; active=false, fail_at=no_failure, failures=0, injected=false. |
| invariants | It leaves count unchanged; subsequent measure resets count before use. |
| ownership | Touches only executable-local atomic probe state; it owns no runtime, context, report, or allocation result. |
| failure | Disarm disables the probe and restores no_failure; measure disables active on both success and exception, records counts, then propagates the original exception. |
| cost | Constant atomic bookkeeping per probe transition plus one atomic note/count update per intercepted request. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0014

[Lines 97–98](../../../../../tests/unit/observation_run_context_test.cpp#L97); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L98:sha256:0b226b9db70fd75a395d7251fe9828ab661cf302ee86deb2878e9c14f4055be8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in observation_run_context_test.cpp: namespace allocation_probe. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0015

[Lines 99–99](../../../../../tests/unit/observation_run_context_test.cpp#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route scalar ordinary global new through the probe and malloc backing. |
| inputs / outputs | Requested byte size enters; malloc-backed storage or std::bad_alloc exits. |
| invariants | This replacement catches ordinary scalar new requests only while the probe is active. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0016

[Lines 100–100](../../../../../tests/unit/observation_run_context_test.cpp#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route array ordinary global new\[\] through the probe and malloc backing. |
| inputs / outputs | Requested byte size enters; malloc-backed storage or std::bad_alloc exits. |
| invariants | Array and scalar ordinary new share allocation_probe::note. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0017

[Lines 101–103](../../../../../tests/unit/observation_run_context_test.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned scalar global new through the aligned probe. |
| inputs / outputs | Size and std::align_val_t enter; posix_memalign-backed pointer or std::bad_alloc exits. |
| invariants | The alignment argument is converted to size_t and the request is counted by note. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0018

[Lines 104–106](../../../../../tests/unit/observation_run_context_test.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes, std::align_val_t alignment) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route aligned array global new\[\] through the aligned probe. |
| inputs / outputs | Size and alignment enter; delegates to allocate_aligned and returns pointer or throws. |
| invariants | It shares the aligned allocation counter/fail point with scalar aligned new. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0019

[Lines 107–107](../../../../../tests/unit/observation_run_context_test.cpp#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free scalar storage from the replacement allocation families. |
| inputs / outputs | A compatible pointer enters; no output. |
| invariants | Calls std::free and does not inspect probe state. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0020

[Lines 108–108](../../../../../tests/unit/observation_run_context_test.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Free array storage from the replacement allocation families. |
| inputs / outputs | A compatible pointer enters; no output. |
| invariants | Calls std::free and does not inspect probe state. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0021

[Lines 109–109](../../../../../tests/unit/observation_run_context_test.cpp#L109); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized scalar delete for malloc-backed replacement storage. |
| inputs / outputs | Pointer and size enter; no output. |
| invariants | The size is ignored and pointer is freed. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0022

[Lines 110–110](../../../../../tests/unit/observation_run_context_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized array delete for malloc-backed replacement storage. |
| inputs / outputs | Pointer and size enter; no output. |
| invariants | The size is ignored and pointer is freed. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0023

[Lines 111–111](../../../../../tests/unit/observation_run_context_test.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide aligned scalar delete for aligned replacement storage. |
| inputs / outputs | Pointer and alignment enter; no output. |
| invariants | Alignment is ignored; pointer is freed. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0024

[Lines 112–112](../../../../../tests/unit/observation_run_context_test.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::align_val_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide aligned array delete for aligned replacement storage. |
| inputs / outputs | Pointer and alignment enter; no output. |
| invariants | Alignment is ignored; pointer is freed. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0025

[Lines 113–115](../../../../../tests/unit/observation_run_context_test.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized aligned scalar delete. |
| inputs / outputs | Pointer, size, and alignment enter; no output. |
| invariants | Size/alignment are ignored and pointer is freed. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0026

[Lines 116–118](../../../../../tests/unit/observation_run_context_test.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide sized aligned array delete. |
| inputs / outputs | Pointer, size, and alignment enter; no output. |
| invariants | Size/alignment are ignored and pointer is freed. |
| ownership | The executable-local probe owns atomic counters/flags only; each successful replacement allocation returns malloc/posix_memalign-backed storage to its C++ caller and matching delete frees it. |
| failure | The probe is active only inside measure(). It intercepts the supplied ordinary and aligned throwing scalar/array global-new overloads. Direct malloc/realloc/posix_memalign calls, system calls, account admission rejection before global new, and unprovided overloads are outside. |
| cost | Counts intercepted allocation calls, not requested bytes, accounted bytes, RSS, CPU time, or all heap activity. A real backing allocator null is also converted to bad_alloc. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0027

[Lines 119–125](../../../../../tests/unit/observation_run_context_test.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L125:sha256:fb4493883a5f95029be929a77a53c90e41f99aa167cd4e1e48b3bcdf26a56307
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare observation_run_context_test.cpp: bind local aliases/name imports; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 126–126](../../../../../tests/unit/observation_run_context_test.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t fake_clock() noexcept { return ++optional_clock_reads; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply one deterministic optional-clock tick and count how often it is read. |
| inputs / outputs | No input; increments optional_clock_reads and returns the incremented value. |
| invariants | This is a fake counter source; its units are not wall-clock nanoseconds. |
| ownership | Mutates only the executable-local optional_clock_reads scalar. |
| failure | A limit rejection is crown::api::Error resource_limit; the measured allocation path is not the same as an injected failed allocation. Probe scopes count only replaced global new requests. |
| cost | One increment and return; it does not sample real time. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0030

[Lines 128–130](../../../../../tests/unit/observation_run_context_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a failed test condition into std::runtime_error. |
| inputs / outputs | Boolean and borrowed message enter; true returns, false throws. |
| invariants | The helper catches no product error. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0032

[Lines 132–142](../../../../../tests/unit/observation_run_context_test.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void expect_error(std::string_view code, Action&& action, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw a crown Error with one exact code. |
| inputs / outputs | Expected code, action, and message enter; matching Error returns; otherwise throws from check. |
| invariants | Only crown::api::Error is caught; a wrong code is a failed assertion, and other exceptions propagate. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0034

[Lines 144–144](../../../../../tests/unit/observation_run_context_test.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value integer(std::int64_t value) { return Value{value}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap an int64 fixture value as a Value. |
| inputs / outputs | Integer enters by value; an integer Value exits. |
| invariants | No view into the argument escapes. |
| ownership | By-value Value/Row outputs own their scalar contents; input scalars are copied into the returned variants/rows. |
| failure | Variant/Row allocation or construction failures propagate; no product error is caught. |
| cost | Constructs one or two fixed scalar fields. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0035

[Lines 145–145](../../../../../tests/unit/observation_run_context_test.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row row(std::int64_t value) { return Row{integer(value)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a one-column Row for the fixture value. |
| inputs / outputs | Integer enters; Row containing the corresponding Value exits. |
| invariants | Returned Row owns its value. |
| ownership | By-value Value/Row outputs own their scalar contents; input scalars are copied into the returned variants/rows. |
| failure | Variant/Row allocation or construction failures propagate; no product error is caught. |
| cost | Constructs one or two fixed scalar fields. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0036

[Lines 146–146](../../../../../tests/unit/observation_run_context_test.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Row edge(std::int64_t x, std::int64_t y) { return Row{integer(x), integer(y)}; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a two-column edge Row for one R tuple. |
| inputs / outputs | Two integers enter; Row(x,y) exits. |
| invariants | Field order is x then y. |
| ownership | By-value Value/Row outputs own their scalar contents; input scalars are copied into the returned variants/rows. |
| failure | Variant/Row allocation or construction failures propagate; no product error is caught. |
| cost | Constructs one or two fixed scalar fields. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp) |

## B0037

[Lines 147–161](../../../../../tests/unit/observation_run_context_test.cpp#L147); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L161:sha256:b6f4a567673445990f58f80c51fac9dc00e027eb5b9115e195ebe364bcbbf8b5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare observation_run_context_test.cpp: declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. Actual object construction and explicit initializers keep the failure contracts of their declared types/called helpers; this card supplies no extra rollback. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. Member/global initialization follows the shown C++ types and expressions when its enclosing object/program is constructed; owning containers can allocate. Default member declarations do not themselves instantiate a fixture. Copies and teardown follow the owning types. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0038

[Lines 162–171](../../../../../tests/unit/observation_run_context_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QFixture()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the fixed R/S catalog, CQ query, lowered plan, and initial database. |
| inputs / outputs | QFixture contains R(x,y), S(y), query R(x,y) join S(y) projecting x, a two-node native tree, compiled plan, and initial R row (7,9) with S empty. |
| invariants | The initial answer is empty; with_s adds S(9) to produce result x=7; two_roots adds R(8,9) for results 7 and 8. |
| ownership | Owns all catalog/query/tree/plan/database values; no runtime or cursor is retained. |
| failure | Construction lowers the fixed plan and inserts the literal base row; errors propagate. |
| cost | One fixed two-table, two-variable query and one base row. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0040

[Lines 173–177](../../../../../tests/unit/observation_run_context_test.cpp#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Database with_s() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a copy of the initial database with S(9) inserted. |
| inputs / outputs | QFixture is borrowed; copied Database with row (9) in table 1 exits. |
| invariants | The fixture’s own initial database remains unchanged. |
| ownership | Fixture objects own catalog/query/plan/database values. Helper-returned Database and PhysicalPlan values are independent copies/moves; no runtime is retained. |
| failure | Planner lowering, evaluator, and ordinary allocation errors propagate; these fixture builders install no fault or clock hook. |
| cost | Builds the fixed two-table, two-variable Q fixture and small literal databases. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0042

[Lines 179–183](../../../../../tests/unit/observation_run_context_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Database two_roots() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a copy of the initial database with a second R root row. |
| inputs / outputs | QFixture is borrowed; copied Database with R(8,9) added exits. |
| invariants | S remains empty unless supplied by another helper; expected result roots are tested elsewhere. |
| ownership | Fixture objects own catalog/query/plan/database values. Helper-returned Database and PhysicalPlan values are independent copies/moves; no runtime is retained. |
| failure | Planner lowering, evaluator, and ordinary allocation errors propagate; these fixture builders install no fault or clock hook. |
| cost | Builds the fixed two-table, two-variable Q fixture and small literal databases. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0043

[Lines 184–185](../../../../../tests/unit/observation_run_context_test.cpp#L184); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L184-L185:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in observation_run_context_test.cpp: struct QFixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0044

[Lines 186–194](../../../../../tests/unit/observation_run_context_test.cpp#L186); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationOptions observation_options(ObservationMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set exact observation mode and trace sampling/timing options. |
| inputs / outputs | ObservationMode enters; ObservationOptions exits with capacity 41, period 1, offset 0, trace_timings=true. |
| invariants | No clock hook is installed by this options builder. |
| ownership | Fixture objects own catalog/query/plan/database values. Helper-returned Database and PhysicalPlan values are independent copies/moves; no runtime is retained. |
| failure | Planner lowering, evaluator, and ordinary allocation errors propagate; these fixture builders install no fault or clock hook. |
| cost | Builds the fixed two-table, two-variable Q fixture and small literal databases. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0046

[Lines 196–216](../../../../../tests/unit/observation_run_context_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions exact_delta_options(ObservationMode mode = ObservationMode::counters) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build exact nested delta/physical/support/cursor/epoch-view/spool options. |
| inputs / outputs | Optional ObservationMode enters; DeltaOptions exits with literal configured work/space limits and requested delta/eager/automatic/sql defaults. |
| invariants | \`memory_limit_bytes\` is 1 MiB; caps are options only and do not claim bytes consumed or CPU duration. |
| ownership | Fixture objects own catalog/query/plan/database values. Helper-returned Database and PhysicalPlan values are independent copies/moves; no runtime is retained. |
| failure | Planner lowering, evaluator, and ordinary allocation errors propagate; these fixture builders install no fault or clock hook. |
| cost | Builds the fixed two-table, two-variable Q fixture and small literal databases. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0048

[Lines 218–222](../../../../../tests/unit/observation_run_context_test.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_observation_options(const ObservationOptions& a, const ObservationOptions& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every observation option field. |
| inputs / outputs | Two ObservationOptions values are borrowed; returns equality of mode, trace capacity, sample period/offset, and trace_timings. |
| invariants | The comparison performs no runtime observation or clock read. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0050

[Lines 224–240](../../../../../tests/unit/observation_run_context_test.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_delta_options(const DeltaOptions& a, const DeltaOptions& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the delta/physical/support option fields used by the run-context fixtures. |
| inputs / outputs | Two DeltaOptions values are borrowed; returns equality across nested work/derivation/support settings, observation settings, mode/view/completion, spool limits. |
| invariants | Every listed field is checked; omitted fields are outside this helper’s equality oracle. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0052

[Lines 242–247](../../../../../tests/unit/observation_run_context_test.cpp#L242); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_input_limits(const io::InputLimits& a, const io::InputLimits& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every typed-input limit field. |
| inputs / outputs | Two InputLimits values are borrowed; returns equality for record/field/column/source/total byte and record/source-count limits. |
| invariants | Optional total_bytes and records compare by exact optional value. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0054

[Lines 249–255](../../../../../tests/unit/observation_run_context_test.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_input_options(const io::InputOptions& a, const io::InputOptions& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare input format and all declared input fields. |
| inputs / outputs | Two InputOptions values are borrowed; compares format, limits, table, delimiter, header, operation, relation token map, null token, source, and offset. |
| invariants | It compares caller request values, not parser progress or input bytes. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0056

[Lines 257–260](../../../../../tests/unit/observation_run_context_test.cpp#L257); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_snapshot_limits(const SnapshotLimits& a, const SnapshotLimits& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare snapshot row/byte/cursor limits. |
| inputs / outputs | Two SnapshotLimits values are borrowed; exact equality bool exits. |
| invariants | Does not compare any actual snapshot contents. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0058

[Lines 262–267](../../../../../tests/unit/observation_run_context_test.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_build(const std::optional<BuildOptions>& a,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare optional BuildOptions by presence, method, and work limit. |
| inputs / outputs | Two optional BuildOptions values enter; absent equals absent, otherwise exact method/optional work-limit equality exits. |
| invariants | No initialization is performed. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0060

[Lines 269–274](../../../../../tests/unit/observation_run_context_test.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_initialization(const InitializationContext& actual,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an InitializationContext to match one exact route and applied BuildOptions. |
| inputs / outputs | Borrowed context, expected route, optional BuildOptions, and label enter; returns void or throws. |
| invariants | Presence, BuildMethod, and work_limit must all match; an empty constructor is expected to have no applied build. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0062

[Lines 276–281](../../../../../tests/unit/observation_run_context_test.cpp#L276); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation drain(SupportRuntime::ResultCursor cursor) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain a SupportRuntime result cursor into an owning set Relation. |
| inputs / outputs | Cursor is consumed by value; each \`next()\` tuple is exported to Row and inserted; Relation exits. |
| invariants | Duplicate set rows fail the test assertion; cursor errors propagate. |
| ownership | Runtime/fixture inputs are borrowed for the call. Returned Relations and exported Rows own their row values; cursor handles are passed/consumed according to the API. |
| failure | Cursor/evaluator errors propagate; duplicate rows or oracle mismatches throw runtime_error via check. |
| cost | Visits the small literal fixture result only; no query performance or wall-clock bound is asserted. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0064

[Lines 283–285](../../../../../tests/unit/observation_run_context_test.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation evaluate(const QFixture& fixture, const Database& database) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the fixture query using the independent reference evaluator. |
| inputs / outputs | QFixture and Database are borrowed; reference::evaluate returns expected Relation. |
| invariants | This is the fixture oracle independent of DeltaRuntime result traversal. |
| ownership | Runtime/fixture inputs are borrowed for the call. Returned Relations and exported Rows own their row values; cursor handles are passed/consumed according to the API. |
| failure | Cursor/evaluator errors propagate; duplicate rows or oracle mismatches throw runtime_error via check. |
| cost | Visits the small literal fixture result only; no query performance or wall-clock bound is asserted. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0066

[Lines 287–291](../../../../../tests/unit/observation_run_context_test.cpp#L287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaOptions mode_options(ObservationMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build mode-specific options with support transition capture disabled. |
| inputs / outputs | ObservationMode enters; starts from exact_delta_options and returns with capture_transitions=false. |
| invariants | The requested mode is the only caller-selected option beyond the fixed fixture values. |
| ownership | Fixture objects own catalog/query/plan/database values. Helper-returned Database and PhysicalPlan values are independent copies/moves; no runtime is retained. |
| failure | Planner lowering, evaluator, and ordinary allocation errors propagate; these fixture builders install no fault or clock hook. |
| cost | Builds the fixed two-table, two-variable Q fixture and small literal databases. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0068

[Lines 293–296](../../../../../tests/unit/observation_run_context_test.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime make_delta_runtime(const QFixture& fixture, const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a DeltaRuntime from the fixture plan/database and supplied options. |
| inputs / outputs | Fixture, initial Database, and DeltaOptions are borrowed; initialized DeltaRuntime exits. |
| invariants | Build route uses DeltaRuntime::initialize; no allocation probe is installed inside this wrapper. |
| ownership | Runtime/fixture inputs are borrowed for the call. Returned Relations and exported Rows own their row values; cursor handles are passed/consumed according to the API. |
| failure | Cursor/evaluator errors propagate; duplicate rows or oracle mismatches throw runtime_error via check. |
| cost | Visits the small literal fixture result only; no query performance or wall-clock bound is asserted. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0070

[Lines 298–310](../../../../../tests/unit/observation_run_context_test.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_output(const ObservationSummary& summary, const OutputDisposition& expected,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare every actual output-disposition flag with the expected lifecycle facts. |
| inputs / outputs | ObservationSummary and expected OutputDisposition are borrowed; missing output or field mismatch throws. |
| invariants | Checks discard request, completion drain, retention, prepared/published/released, transferred, serialization/sink invocation, and unread discard separately. |
| ownership | The runtime owns pending/retained epoch spool until transfer, discard, or release; a \`next()\` result is a caller-owned SignedResult value. Oracle Relations are separate expected copies. |
| failure | Tests inspect actual OutputDisposition/MetricId state after commit, rollback, callback, or resource rejection. Product resource errors are caught only by the specific expected-error helper; no durable sink or system I/O is exercised here. |
| cost | Fixed one- or two-row Q fixtures with exact counters. Work metrics are algorithmic counters; no wall-clock or CPU time is inferred except injected-clock checks in the dedicated mode scenario. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0072

[Lines 312–318](../../../../../tests/unit/observation_run_context_test.cpp#L312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OutputDisposition disposition(bool discard_requested, bool completion_drain,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the expected ten-flag OutputDisposition value. |
| inputs / outputs | Ten bool inputs enter; OutputDisposition value exits. |
| invariants | Pure oracle construction; it does not cause any lifecycle action. |
| ownership | The runtime owns pending/retained epoch spool until transfer, discard, or release; a \`next()\` result is a caller-owned SignedResult value. Oracle Relations are separate expected copies. |
| failure | Tests inspect actual OutputDisposition/MetricId state after commit, rollback, callback, or resource rejection. Product resource errors are caught only by the specific expected-error helper; no durable sink or system I/O is exercised here. |
| cost | Fixed one- or two-row Q fixtures with exact counters. Work metrics are algorithmic counters; no wall-clock or CPU time is inferred except injected-clock checks in the dedicated mode scenario. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0074

[Lines 320–325](../../../../../tests/unit/observation_run_context_test.cpp#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_metric(const ObservationSummary& summary, MetricId id,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one metric to be available with an exact value. |
| inputs / outputs | ObservationSummary, MetricId, expected uint64, and message enter; returns void or throws. |
| invariants | Availability must equal available and value must equal the literal; no unit conversion or timing interpretation occurs. |
| ownership | The runtime owns pending/retained epoch spool until transfer, discard, or release; a \`next()\` result is a caller-owned SignedResult value. Oracle Relations are separate expected copies. |
| failure | Tests inspect actual OutputDisposition/MetricId state after commit, rollback, callback, or resource rejection. Product resource errors are caught only by the specific expected-error helper; no durable sink or system I/O is exercised here. |
| cost | Fixed one- or two-row Q fixtures with exact counters. Work metrics are algorithmic counters; no wall-clock or CPU time is inferred except injected-clock checks in the dedicated mode scenario. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0076

[Lines 327–362](../../../../../tests/unit/observation_run_context_test.cpp#L327); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_context(const std::shared_ptr<const SessionRunContext>& context,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-check a shared session run context against independently supplied input, queue/window, snapshot, initialization, and delta options. |
| inputs / outputs | Shared const context plus expected input kind/options, optional QueueLimits/WindowOptions, SnapshotLimits, route/BuildOptions, and requested DeltaOptions enter. |
| invariants | Checks exact applicability, input export/options, optional queue/window fields, snapshot caps, route/build, requested DeltaOptions, and resolved delta/anchored values. |
| ownership | Borrows shared_ptr&lt;const SessionRunContext&gt; and expected inputs; it neither retains nor mutates the context. |
| failure | Null context or any mismatch throws runtime_error; option copy/serialization failures propagate. |
| cost | Compares a fixed metadata object and its configured fields; no session or query is advanced. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md) |

## B0078

[Lines 364–397](../../../../../tests/unit/observation_run_context_test.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_json_delta(const Json& actual, const DeltaOptions& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exported JSON fields for the requested DeltaOptions. |
| inputs / outputs | Parsed JSON object and expected DeltaOptions are borrowed; no output. |
| invariants | Checks requested enum names, work limits, spool rows/accounted bytes, physical/derivation/support options, propagation order, and nested observation values. |
| ownership | Borrows ObservationSnapshot/SessionRunContext during serialization; returned JSON string owns encoded bytes. No callback object, live input row, or runtime payload is retained by the exporter. |
| failure | Missing/wrong JSON values fail via check; malformed JSON parsing is the caller’s responsibility. |
| cost | Reads a fixed list of parsed metadata fields. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md) |

## B0080

[Lines 399–454](../../../../../tests/unit/observation_run_context_test.cpp#L399); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_json_input(const Json& actual, const io::InputOptions& expected) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate exported JSON fields for exact InputOptions, including absent-versus-present values. |
| inputs / outputs | Parsed JSON and expected InputOptions are borrowed; no output. |
| invariants | Checks format/table, delimiter/header/operation/offset, ordered relation tokens, optional null/source, and each limit including optional total bytes/records. |
| ownership | Borrows ObservationSnapshot/SessionRunContext during serialization; returned JSON string owns encoded bytes. No callback object, live input row, or runtime payload is retained by the exporter. |
| failure | Any mismatch throws runtime_error; it does not decode or execute input records. |
| cost | Walks fixed option fields and the small ordered relation-token map. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md) |

## B0082

[Lines 456–510](../../../../../tests/unit/observation_run_context_test.cpp#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify_session_export(const std::string& encoded,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a run-context JSON export and verify provenance/applicability/options against one admitted session context. |
| inputs / outputs | Encoded string, expected SessionRunContext, expected input-kind name, and wire-scope name enter; parsed JSON is local and no value exits. |
| invariants | Requires version-1 crown_run_context header, recorded admission provenance, exact input/queue/window/snapshot/build/delta metadata and resolved settings; absent queue/window fields stay null. |
| ownership | Encoded source string is borrowed; parser’s JSON object owns parsed copies for the call only. |
| failure | JSON parse/field errors fail through runtime_error/check; strict text validation and encoded-byte limits are exercised by the caller scenario. |
| cost | Parses and compares one small session metadata artifact; not a session-memory/account measurement. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md) |

## B0084

[Lines 512–593](../../../../../tests/unit/observation_run_context_test.cpp#L512); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_initialization_routes_and_build_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise direct/replay database initialization, empty construction, rebuild routes, and failed-build caller-state preservation. |
| inputs / outputs | Constructs empty and populated DeltaRuntime instances with direct/replay BuildOptions, rebuilds a direct runtime with new BuildOptions, repeats empty/init/rebuild routes with PhysicalRuntime, and attempts a direct build with work limit zero. |
| invariants | InitializationContext must preserve exact route and applied BuildOptions. Direct/replay snapshots equal their literal source databases and independent Q evaluator result; rebuild reports rebuilt_snapshot, a new Delta owner, and unchanged result. The zero-work build throws resource_limit and leaves the caller-owned fixture database unchanged. |
| ownership | The scenario owns fixture, source Database values, and each returned runtime/snapshot; initialize copies/constructs runtime state from the borrowed input database. No runtime is retained across helper calls. |
| failure | Only the impossible direct build expects crown::api::Error resource_limit. Other route/result mismatches throw runtime_error via check; planner/runtime errors propagate. |
| cost | One fixed two-table fixture, several empty/populated initialization and rebuild paths, one rejected build; no timing or memory-use claim. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/physical_runtime.md § Work and resource limits](../../../../physical_runtime.md) |

## B0086

[Lines 595–605](../../../../../tests/unit/observation_run_context_test.cpp#L595); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputLimits custom_limits() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build exact typed InputLimits for run-context assertions. |
| inputs / outputs | No input; limits record_bytes 4096, field_bytes 512, columns 13, source_bytes 29, sources 7, total_bytes 9011, records 31 exit. |
| invariants | These are declared ceilings, not observed consumption. |
| ownership | Option structs are returned by value and own their option values; comparison helpers borrow option references. |
| failure | Invalid or absent optional values compare literally; no runtime error is caught or translated. |
| cost | Copies or compares a fixed number of scalar/optional option fields, not the runtime work they configure. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0088

[Lines 607–613](../../../../../tests/unit/observation_run_context_test.cpp#L607); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotLimits custom_snapshot() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build exact snapshot row/byte/cursor ceilings. |
| inputs / outputs | No input; SnapshotLimits rows=37, bytes=8009, cursor work_limit=401 exits. |
| invariants | The values describe the configured snapshot policy, not actual rows/bytes used. |
| ownership | Option structs are returned by value and own their option values; comparison helpers borrow option references. |
| failure | Invalid or absent optional values compare literally; no runtime error is caught or translated. |
| cost | Copies or compares a fixed number of scalar/optional option fields, not the runtime work they configure. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0090

[Lines 615–617](../../../../../tests/unit/observation_run_context_test.cpp#L615); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::QueueLimits custom_queue(std::size_t salt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build queue admission limits adjusted by one fixture salt. |
| inputs / outputs | Salt enters; batches/events/accounted bytes are 5+salt, 17+salt, 12001+salt. |
| invariants | These are requested limits; not byte counts consumed by a session. |
| ownership | Option structs are returned by value and own their option values; comparison helpers borrow option references. |
| failure | Invalid or absent optional values compare literally; no runtime error is caught or translated. |
| cost | Copies or compares a fixed number of scalar/optional option fields, not the runtime work they configure. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0092

[Lines 619–626](../../../../../tests/unit/observation_run_context_test.cpp#L619); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const DeclaredBenchmarkContext> session_label() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build session benchmark labels with NUL, empty, null, and present values. |
| inputs / outputs | No input; shared const DeclaredBenchmarkContext exits with run="session\0run", empty input_adapter, absent codec, sink="typed-sink". |
| invariants | The strings are caller declarations and carry no measurement/durability/proof authority. |
| ownership | Option structs are returned by value and own their option values; comparison helpers borrow option references. |
| failure | Invalid or absent optional values compare literally; no runtime error is caught or translated. |
| cost | Copies or compares a fixed number of scalar/optional option fields, not the runtime work they configure. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0094

[Lines 628–648](../../../../../tests/unit/observation_run_context_test.cpp#L628); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_session_survived_drop(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a saved immutable session context and its post-drop run-context export. |
| inputs / outputs | Saved shared context, expected kind/input/queue/window/snapshot/build/delta, post-drop ObservationSnapshot, and scope strings enter. |
| invariants | After drop, snapshot remains session_attached with the same context handle and no last attempt; exact encoded size succeeds and one byte less raises resource_limit. |
| ownership | The shared context handle is copied into this call and outlives the destroyed session owner; the ObservationSnapshot is borrowed. |
| failure | Checks context and JSON export; resource_limit is expected only for output cap size-1. |
| cost | Re-serializes one bounded context artifact at exact output-size and one-byte-short caps. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md) |

## B0096

[Lines 650–816](../../../../../tests/unit/observation_run_context_test.cpp#L650); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_session_context_owned_stream_typed_window_and_admission_oom() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check immutable run-context admission for owned stream, typed queue, windowed queue, and persistent admission OOM. |
| inputs / outputs | Builds distinct stream/typed/window admission fixtures, saves shared contexts across drop, round-trips metadata, additionally checks both physical FIFO policy names through actual session context/export, then calibrates typed-session allocation requests and sweeps persistent OOM. |
| invariants | Each successful context must reflect exact admission request and survive drop with no history. Every injected bad_alloc must leave Owner empty and caller database/options unchanged; later creation after disarm succeeds with empty-constructor route. Calibration is explicitly allowed to allocate. |
| ownership | Each inner session owns its stream or typed/window queue until stop/drop; saved shared const run-context handles survive session destruction. OOM attempts own a local optional Owner; none is published on failure. |
| failure | The OOM seam counts ordinary and aligned throwing global new/new\[\] calls. Fail-at i lets earlier calls through and throws at i; because measure stays active until unwinding ends, later attempted new calls remain rejected. Raw malloc/realloc and system calls are outside. Not an account-denial test or a no-allocation construction test. |
| cost | Five metadata fixture sessions (three original kinds plus two physical policy exports), one successful allocation calibration and one failed constructor attempt per observed request. No timing or resource bound is inferred. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0098

[Lines 818–820](../../../../../tests/unit/observation_run_context_test.cpp#L818); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate insert_s(std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an insert update for S(9) at an explicit sequence. |
| inputs / outputs | Sequence enters; PhysicalSetUpdate(table 1, insert, row 9) exits with owned Row. |
| invariants | The sequence is supplied by caller; helper does not apply update. |
| ownership | Fixture objects own catalog/query/plan/database values. Helper-returned Database and PhysicalPlan values are independent copies/moves; no runtime is retained. |
| failure | Planner lowering, evaluator, and ordinary allocation errors propagate; these fixture builders install no fault or clock hook. |
| cost | Builds the fixed two-table, two-variable Q fixture and small literal databases. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0100

[Lines 822–824](../../../../../tests/unit/observation_run_context_test.cpp#L822); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSetUpdate erase_s(std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an erase update for S(9) at an explicit sequence. |
| inputs / outputs | Sequence enters; PhysicalSetUpdate(table 1, erase, row 9) exits with owned Row. |
| invariants | The update is a value; runtime state is unchanged. |
| ownership | Fixture objects own catalog/query/plan/database values. Helper-returned Database and PhysicalPlan values are independent copies/moves; no runtime is retained. |
| failure | Planner lowering, evaluator, and ordinary allocation errors propagate; these fixture builders install no fault or clock hook. |
| cost | Builds the fixed two-table, two-variable Q fixture and small literal databases. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0102

[Lines 826–1009](../../../../../tests/unit/observation_run_context_test.cpp#L826); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_actual_output_disposition_lifecycle() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise actual output suppression, retention, transfer, discard, rollback, stale-close, paused drain, and spool-cap disposition. |
| inputs / outputs | Runs independent DeltaRuntime cases for suppressed one-row output, retained row transfer, duplicate empty epoch, two-row partial transfer plus discard, explicit rollback, late close of an older empty epoch after a newer commit, paused completion drain, and spool_row_limit=0. |
| invariants | Checks the exact ten disposition flags and literal transferred/discarded/serialization/sink/ack metrics where relevant; uses reference::evaluate and physical snapshots to prove query state. Spool cap throws resource_limit and leaves prior sequence/result unchanged. |
| ownership | Each case owns its runtime and pending/committed Epoch. Epoch owns its output spool; next() returns a caller-owned SignedResult, while \`discard()\` closes remaining runtime-owned rows. |
| failure | Assertions read actual observation summaries; only the zero-spool case expects Error resource_limit. Transfer/discard/commit distinctions are observed separately; no durable sink is involved. |
| cost | Small one- or two-row fixtures with literal counters. Work, bytes, and callbacks are not timed or treated as global resource totals. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0104

[Lines 1011–1022](../../../../../tests/unit/observation_run_context_test.cpp#L1011); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const DeclaredBenchmarkContext> benchmark_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a shared immutable caller-declared benchmark-label object. |
| inputs / outputs | Four optional strings enter by value and move into BenchmarkLabels/DeclaredBenchmarkContext; shared_ptr&lt;const ...&gt; exits. |
| invariants | Labels preserve missing versus empty and arbitrary native string bytes; declarations do not assert measurement or callback identity. |
| ownership | Moves the optional owned strings into an immutable shared context value; callers retain a shared const handle. |
| failure | Allocation errors propagate; the builder performs no validation/UTF-8 normalization. |
| cost | Allocates one small shared label record plus its present strings. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md) |

## B0106

[Lines 1024–1027](../../../../../tests/unit/observation_run_context_test.cpp#L1024); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool same_labels(const BenchmarkLabels& a, const BenchmarkLabels& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare exact optional declared benchmark labels. |
| inputs / outputs | Two BenchmarkLabels values are borrowed; compares all four optional strings. |
| invariants | Empty, absent, embedded NUL, and invalid UTF-8 are distinct values. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0108

[Lines 1029–1037](../../../../../tests/unit/observation_run_context_test.cpp#L1029); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_attempt_labels(const ObservationSummary& summary,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that one attempt bound the expected caller labels and sequence/outcome. |
| inputs / outputs | ObservationSummary and expected labels/sequence/outcome are borrowed; returns or throws. |
| invariants | Requires the attempt summary to retain the labels captured at begin; current declaration is not substituted. |
| ownership | Borrows compared objects and returns a bool or no value; it retains no references. |
| failure | No errors are caught. Any error from a nested comparison/read propagates. |
| cost | Compares the explicitly named fixed option/metric fields; it does not run the query. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md) |

## B0110

[Lines 1039–1168](../../../../../tests/unit/observation_run_context_test.cpp#L1039); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_callbacks_begin_bound_labels_and_utf8_export() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that caller declarations bind at begin, survive commit/abort historically, and serialize with strict text boundaries. |
| inputs / outputs | Uses labels A/B/C/D with embedded NUL, empty/null fields, and invalid UTF-8; begins/commits A, changes current B mid-attempt, switches mode, begins/aborts B, rejects strict JSON of invalid bytes, retries/commits C, then declares D and exports current/history. |
| invariants | A stays on attempt 1 while current becomes B; config generation increments on actual mode switch and history remains gen0. B is retained on aborted seq2 and C on retry commit seq2; D remains current only. Native bytes remain unchanged; JSON escapes NUL, preserves null-vs-empty/provenance/authority, includes initialized route, exact encoded cap succeeds and cap-1 raises resource_limit. Runtime/query state is checked independently. |
| ownership | The runtime holds current shared const declaration and immutable per-attempt shared label snapshots; ObservationSnapshot copies handles. Strings own native bytes. Encoded JSON is a separate returned string. |
| failure | Invalid UTF-8 is accepted natively but \`write_run_context_json\` throws text_encoding; the runtime remains sequence1 and committed query result unchanged. Encoded-size one-byte-short separately throws resource_limit. |
| cost | Three small output attempts and metadata exports; fake clock is not enabled here and no timing/bytes consumed by the runtime are claimed. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/io/run_context.hpp](../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp](../../../../../src/io/run_context.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md), [docs/observability.md § Encodings and schemas](../../../../observability.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0112

[Lines 1170–1298](../../../../../tests/unit/observation_run_context_test.cpp#L1170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_callback_retries_deferred_discard_and_oom() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise serializer/sink callback retries, acknowledgment counts, and callback-requested deferred discard. |
| inputs / outputs | Two-row fixture; serializer throws bad_alloc twice for first row then succeeds; sink throws once then succeeds; sink calls discard while second row is borrowed. |
| invariants | Failed serialization/sink leaves same first row retryable and unacknowledged; successful sink acknowledges one row, not transferred/released; deferred discard occurs after callback returns and marks second unread row discarded. Exact serializer/sink/ack metrics are checked and evaluator result is unchanged. |
| ownership | The epoch retains each unacknowledged spool row; callbacks borrow the current SignedResult for one call. discard from callback is deferred until its borrowed-row invocation returns. |
| failure | Test callbacks deliberately throw std::bad_alloc and std::runtime_error. These are callback exceptions, not injected global allocation faults or durable I/O failures. |
| cost | Five serializer attempts over two output rows with exact callback counters; not a timing or sink throughput measurement. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md), [docs/delta_runtime.md § Output, mapping and ownership](../../../../delta_runtime.md) |

## B0114

[Lines 1300–1304](../../../../../tests/unit/observation_run_context_test.cpp#L1300); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ModeMatrixResult {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store three allocation-call counts from a mode-parity trial. |
| inputs / outputs | apply, rollback, and failed apply allocation counts default to zero. |
| invariants | Fields count intercepted new requests, not bytes or account charge. |
| ownership | Owns three scalar counts only. |
| failure | A limit rejection is crown::api::Error resource_limit; the measured allocation path is not the same as an injected failed allocation. Probe scopes count only replaced global new requests. |
| cost | Three size_t fields. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0116

[Lines 1306–1505](../../../../../tests/unit/observation_run_context_test.cpp#L1306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void scenario_mode_parity_work_failures_clock_and_rollback() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare observation modes for mandatory work, fake-clock reads, trace events, allocation-call parity, rollback, and resource-limit behavior. |
| inputs / outputs | With fake_clock installed, runs off/counters/timed/trace runtimes; measures apply, discard, rollback, and support-work-limit 39 failure; compares to literal Q evaluator result and exact counters. |
| invariants | Every mode preserves support work 40 and physical input work 44; exclusive physical work 4. Off retains no optional history/clock; counters reads no optional clock; timed/trace read fake ticks and positive timing is tick-derived. Trace capacity 41 bounds records and commit precedes transfer. Release and rollback each count zero intercepted allocations; limit 39 rejects work 40, restores sequence/state, and enabled modes retain abort/partial support work. Allocation request counts match across modes. |
| ownership | Each mode owns its runtime/Epoch and snapshots; the injected fake-clock callback and global allocation-probe counters are executable-local. RestoreClock resets the hook on scope exit. |
| failure | Resource rejection expects \`resource_limit\`; no allocation fault is selected here. \`measure\` observes allocation calls during each named action only. Runtime state and result are checked independently of optional telemetry. |
| cost | Compares request counts and deterministic work/fake-clock counters. Tick values are synthetic and not elapsed wall-clock time; counts are not bytes/RSS, and no benchmark conclusion is made. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp), [docs/observability.md § Observation modes and metric values](../../../../observability.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [src/runtime/delta.cpp](../../../../../src/runtime/delta.cpp), [docs/delta_runtime.md § Modes and bounded spool](../../../../delta_runtime.md), [docs/delta_runtime.md § Work and space accounting](../../../../delta_runtime.md) |

## B0118

[Lines 1507–1512](../../../../../tests/unit/observation_run_context_test.cpp#L1507); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run_group(std::string_view name, Action&& action) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Print a group banner, invoke one supplied scenario, then print success. |
| inputs / outputs | Name and action enter; writes RUN/OK lines and returns if action succeeds. |
| invariants | Action exceptions propagate to main; no group result is synthesized. |
| ownership | The helper borrows its name/action for the synchronous call and retains no fixture or runtime. |
| failure | The scenario exception propagates to main; this banner helper catches and translates nothing. |
| cost | Writes two short diagnostic lines around one supplied action; no runtime work is added by the helper. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp) |

## B0119

[Lines 1513–1514](../../../../../tests/unit/observation_run_context_test.cpp#L1513); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1513-L1514:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in observation_run_context_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp), [docs/observability.md](../../../../observability.md), [docs/code_review.md](../../../../code_review.md) |

## B0120

[Lines 1515–1537](../../../../../tests/unit/observation_run_context_test.cpp#L1515); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run six observation/run-context groups and report failure through stderr/status. |
| inputs / outputs | No input; invokes initialization, session-context/OOM, output-disposition, labels/export, callback, and mode-parity groups. |
| invariants | Catch-all scenario error is std::exception; handler disarms allocator and clears clock hook then returns 1. Success returns 0. This packet did not execute main. |
| ownership | main owns no long-lived runtime; each scenario controls its own fixture lifetime. |
| failure | The outer handler catches std::exception, disarms allocation probe, clears test clock, and returns 1. It does not claim a run passed. |
| cost | Runs all six deterministic groups if invoked; no duration threshold or total-memory claim. |
| Design | [tests/unit/observation_run_context_test.cpp](../../../../../tests/unit/observation_run_context_test.cpp) |
