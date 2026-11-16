# `tests/unit/batch_window_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/batch_window_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d7ae447f5f353a5fbd80a8c1c9135a2648b3471c03a7664b758510d219ebcfae`. 958 lines partitioned into 113 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../tests/unit/batch_window_exception_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // This executable owns global new so injected failures stay armed while · [reviewed contract](#b0001) |
| [B0002 · 27–35](../../../../../tests/unit/batch_window_exception_test.cpp#L27) | Callable definition: \[\[gnu::noinline\]\] void* malloc_new(std::size_t bytes) | calls std::malloc; returns result; growth malloc · [reviewed contract](#b0002) |
| [B0003 · 36–36](../../../../../tests/unit/batch_window_exception_test.cpp#L36) | Explanatory comments or spacing. |  |
| [B0004 · 37–43](../../../../../tests/unit/batch_window_exception_test.cpp#L37) | Type/record definition: struct FaultScope |  · [reviewed contract](#b0004) |
| [B0005 · 44–45](../../../../../tests/unit/batch_window_exception_test.cpp#L44) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 46–46](../../../../../tests/unit/batch_window_exception_test.cpp#L46) | Callable definition: void* operator new(std::size_t bytes) | calls malloc_new; returns malloc_new(bytes); growth new · [reviewed contract](#b0006) |
| [B0007 · 47–47](../../../../../tests/unit/batch_window_exception_test.cpp#L47) | Callable definition: void* operator new\[\](std::size_t bytes) | calls ; returns malloc_new(bytes); growth new · [reviewed contract](#b0007) |
| [B0008 · 48–48](../../../../../tests/unit/batch_window_exception_test.cpp#L48) | Callable definition: void operator delete(void* pointer) noexcept | calls std::free · [reviewed contract](#b0008) |
| [B0009 · 49–49](../../../../../tests/unit/batch_window_exception_test.cpp#L49) | Callable definition: void operator delete\[\](void* pointer) noexcept | calls  · [reviewed contract](#b0009) |
| [B0010 · 50–50](../../../../../tests/unit/batch_window_exception_test.cpp#L50) | Callable definition: void operator delete(void* pointer, std::size_t) noexcept | calls std::free · [reviewed contract](#b0010) |
| [B0011 · 51–51](../../../../../tests/unit/batch_window_exception_test.cpp#L51) | Callable definition: void operator delete\[\](void* pointer, std::size_t) noexcept | calls  · [reviewed contract](#b0011) |
| [B0012 · 52–58](../../../../../tests/unit/batch_window_exception_test.cpp#L52) | declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_destructible_v&lt;QuerySession&gt;); · [reviewed contract](#b0012) |
| [B0013 · 59–61](../../../../../tests/unit/batch_window_exception_test.cpp#L59) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { · [reviewed contract](#b0013) |
| [B0014 · 62–62](../../../../../tests/unit/batch_window_exception_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0015 · 63–73](../../../../../tests/unit/batch_window_exception_test.cpp#L63) | Callable definition: template &lt;class Action&gt; void expect_error(Action&& action, std::string_view code) | calls check, code, std::string, std::runtime_error; guard check(failure.code() == code, · [reviewed contract](#b0015) |
| [B0016 · 74–74](../../../../../tests/unit/batch_window_exception_test.cpp#L74) | Explanatory comments or spacing. |  |
| [B0017 · 75–75](../../../../../tests/unit/batch_window_exception_test.cpp#L75) | Callable definition: Value n(std::int64_t value) | calls ; returns value · [reviewed contract](#b0017) |
| [B0018 · 76–76](../../../../../tests/unit/batch_window_exception_test.cpp#L76) | Explanatory comments or spacing. |  |
| [B0019 · 77–79](../../../../../tests/unit/batch_window_exception_test.cpp#L77) | Callable definition: Catalog unary_catalog() | calls ; returns {91, {{@ , {{@ , ScalarType::int64}}}}} · [reviewed contract](#b0019) |
| [B0020 · 80–80](../../../../../tests/unit/batch_window_exception_test.cpp#L80) | Explanatory comments or spacing. |  |
| [B0021 · 81–89](../../../../../tests/unit/batch_window_exception_test.cpp#L81) | Callable definition: PhysicalPlan unary_plan() | calls unary_catalog, planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0021) |
| [B0022 · 90–90](../../../../../tests/unit/batch_window_exception_test.cpp#L90) | Explanatory comments or spacing. |  |
| [B0023 · 91–104](../../../../../tests/unit/batch_window_exception_test.cpp#L91) | Callable definition: PhysicalPlan alias_plan() | calls planner::lower_tree; returns planner::lower_tree(catalog, query, tree) · [reviewed contract](#b0023) |
| [B0024 · 105–105](../../../../../tests/unit/batch_window_exception_test.cpp#L105) | Explanatory comments or spacing. |  |
| [B0025 · 106–112](../../../../../tests/unit/batch_window_exception_test.cpp#L106) | Callable definition: io::InputItem physical_item(std::uint64_t sequence, Row row, std::string source = "source-A", std::uint64_t offset = 0) | calls std::move; returns io::InputEvent{{sequence, TableId{0}, SetOperation::insert,; growth insert · [reviewed contract](#b0025) |
| [B0026 · 113–113](../../../../../tests/unit/batch_window_exception_test.cpp#L113) | Explanatory comments or spacing. |  |
| [B0027 · 114–120](../../../../../tests/unit/batch_window_exception_test.cpp#L114) | Callable definition: io::InputItem window_insert(std::uint64_t sequence, std::uint64_t label, Row row, std::uint64_t timestamp, std::string source = "… | calls std::move; returns io::WindowCommand{sequence, · [reviewed contract](#b0027) |
| [B0028 · 121–121](../../../../../tests/unit/batch_window_exception_test.cpp#L121) | Explanatory comments or spacing. |  |
| [B0029 · 122–126](../../../../../tests/unit/batch_window_exception_test.cpp#L122) | Callable definition: io::InputItem watermark(std::uint64_t sequence, std::uint64_t time, std::string source = "window-source") | calls std::move; returns io::WindowCommand{sequence, io::AdvanceWatermark{time}, · [reviewed contract](#b0029) |
| [B0030 · 127–127](../../../../../tests/unit/batch_window_exception_test.cpp#L127) | Explanatory comments or spacing. |  |
| [B0031 · 128–130](../../../../../tests/unit/batch_window_exception_test.cpp#L128) | Callable definition: io::TransportBatch batch(std::vector&lt;io::InputItem&gt; items) | calls io::TransportBatch, std::move; returns io::TransportBatch(std::move(items)) · [reviewed contract](#b0031) |
| [B0032 · 131–131](../../../../../tests/unit/batch_window_exception_test.cpp#L131) | Explanatory comments or spacing. |  |
| [B0033 · 132–138](../../../../../tests/unit/batch_window_exception_test.cpp#L132) | Type/record definition: struct SessionImage |  · [reviewed contract](#b0033) |
| [B0034 · 139–139](../../../../../tests/unit/batch_window_exception_test.cpp#L139) | Explanatory comments or spacing. |  |
| [B0035 · 140–148](../../../../../tests/unit/batch_window_exception_test.cpp#L140) | Callable definition: SessionImage image(const QuerySession& session) | calls snapshot, push_back, crown::storage::export_row, values; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0035) |
| [B0036 · 149–149](../../../../../tests/unit/batch_window_exception_test.cpp#L149) | Explanatory comments or spacing. |  |
| [B0037 · 150–152](../../../../../tests/unit/batch_window_exception_test.cpp#L150) | Callable definition: std::optional&lt;io::QueueStats&gt; queue_stats(const QuerySession& session) | calls status; returns session.status().queue · [reviewed contract](#b0037) |
| [B0038 · 153–153](../../../../../tests/unit/batch_window_exception_test.cpp#L153) | Explanatory comments or spacing. |  |
| [B0039 · 154–160](../../../../../tests/unit/batch_window_exception_test.cpp#L154) | Callable definition: WindowOptions window_options() | calls ; returns options · [reviewed contract](#b0039) |
| [B0040 · 161–161](../../../../../tests/unit/batch_window_exception_test.cpp#L161) | Explanatory comments or spacing. |  |
| [B0041 · 162–164](../../../../../tests/unit/batch_window_exception_test.cpp#L162) | Callable definition: void drain_output(QuerySession& session) | calls next_output; 1 loop sites · [reviewed contract](#b0041) |
| [B0042 · 165–165](../../../../../tests/unit/batch_window_exception_test.cpp#L165) | Explanatory comments or spacing. |  |
| [B0043 · 166–170](../../../../../tests/unit/batch_window_exception_test.cpp#L166) | Callable definition: void prepare_current(QuerySession& session) | calls step; 1 loop sites · [reviewed contract](#b0043) |
| [B0044 · 171–171](../../../../../tests/unit/batch_window_exception_test.cpp#L171) | Explanatory comments or spacing. |  |
| [B0045 · 172–176](../../../../../tests/unit/batch_window_exception_test.cpp#L172) | Callable definition: void finish_current(QuerySession& session) | calls prepare_current, commit, drain_output · [reviewed contract](#b0045) |
| [B0046 · 177–177](../../../../../tests/unit/batch_window_exception_test.cpp#L177) | Explanatory comments or spacing. |  |
| [B0047 · 178–181](../../../../../tests/unit/batch_window_exception_test.cpp#L178) | Callable definition: void accept(QuerySession& session, io::TransportBatch& input) | calls check, enqueue; guard check(session.enqueue(input) == io::Admission::accepted, · [reviewed contract](#b0047) |
| [B0048 · 182–182](../../../../../tests/unit/batch_window_exception_test.cpp#L182) | Explanatory comments or spacing. |  |
| [B0049 · 183–217](../../../../../tests/unit/batch_window_exception_test.cpp#L183) | Callable definition: template &lt;class Context, class Factory, class Operation, class AfterFailure, class AfterSuccess&gt; std::size_t sweep_fault_position… | calls factory, fault, operation, forbid_allocations; guard check(failures &gt; 0,; returns failures; 1 loop sites; source comment (unverified): // Leave failures armed through all stack unwinding, then inspect only · [reviewed contract](#b0049) |
| [B0050 · 218–218](../../../../../tests/unit/batch_window_exception_test.cpp#L218) | Explanatory comments or spacing. |  |
| [B0051 · 219–223](../../../../../tests/unit/batch_window_exception_test.cpp#L219) | Type/record definition: struct CreateAttempt |  · [reviewed contract](#b0051) |
| [B0052 · 224–224](../../../../../tests/unit/batch_window_exception_test.cpp#L224) | Explanatory comments or spacing. |  |
| [B0053 · 225–264](../../../../../tests/unit/batch_window_exception_test.cpp#L225) | Callable definition: void typed_session_construction_unwinds_cleanly() | calls unary_plan, QuerySession::create_typed, std::move, check; guard check(!attempt.session, "failed typed construction published a session");; returns CreateAttempt{unary_plan()}; CreateAttempt{unary_plan()} · [reviewed contract](#b0053) |
| [B0054 · 265–265](../../../../../tests/unit/batch_window_exception_test.cpp#L265) | Explanatory comments or spacing. |  |
| [B0055 · 266–271](../../../../../tests/unit/batch_window_exception_test.cpp#L266) | Type/record definition: struct QueueAttempt |  · [reviewed contract](#b0055) |
| [B0056 · 272–272](../../../../../tests/unit/batch_window_exception_test.cpp#L272) | Explanatory comments or spacing. |  |
| [B0057 · 273–276](../../../../../tests/unit/batch_window_exception_test.cpp#L273) | Callable definition: QueueAttempt queue_attempt(io::QueueLimits limits = {}) | calls QuerySession::create_typed, unary_plan, std::move, batch; returns {std::move(session), batch({physical_item(1, {n(7)}, @ , 50)})} · [reviewed contract](#b0057) |
| [B0058 · 277–277](../../../../../tests/unit/batch_window_exception_test.cpp#L277) | Explanatory comments or spacing. |  |
| [B0059 · 278–315](../../../../../tests/unit/batch_window_exception_test.cpp#L278) | Callable definition: void queue_admission_is_transactional_and_retriable() | calls queue_attempt, enqueue, check, size; guard check(attempt.input.size() == 1 && !attempt.input.empty() &&; returns queue_attempt() · [reviewed contract](#b0059) |
| [B0060 · 316–316](../../../../../tests/unit/batch_window_exception_test.cpp#L316) | Explanatory comments or spacing. |  |
| [B0061 · 317–328](../../../../../tests/unit/batch_window_exception_test.cpp#L317) | Type/record definition: struct PeekAttempt | guard check(queue.enqueue(input) == io::Admission::accepted, · [reviewed contract](#b0061) |
| [B0062 · 329–329](../../../../../tests/unit/batch_window_exception_test.cpp#L329) | Explanatory comments or spacing. |  |
| [B0063 · 330–355](../../../../../tests/unit/batch_window_exception_test.cpp#L330) | Callable definition: void new_source_peek_node_allocation_is_retriable() | calls peek, check, failed, progress; guard check(!attempt.queue.failed() && attempt.queue.progress() == io::InputProgress{} &&; returns PeekAttempt{} · [reviewed contract](#b0063) |
| [B0064 · 356–356](../../../../../tests/unit/batch_window_exception_test.cpp#L356) | Explanatory comments or spacing. |  |
| [B0065 · 357–362](../../../../../tests/unit/batch_window_exception_test.cpp#L357) | Type/record definition: struct PhysicalRetryAttempt |  · [reviewed contract](#b0065) |
| [B0066 · 363–363](../../../../../tests/unit/batch_window_exception_test.cpp#L363) | Explanatory comments or spacing. |  |
| [B0067 · 364–378](../../../../../tests/unit/batch_window_exception_test.cpp#L364) | Callable definition: PhysicalRetryAttempt alias_retry_attempt() | calls QuerySession::create_typed, alias_plan, batch, physical_item; guard check(session-&gt;begin_next(), "alias seed input did not begin");; returns attempt · [reviewed contract](#b0067) |
| [B0068 · 379–379](../../../../../tests/unit/batch_window_exception_test.cpp#L379) | Explanatory comments or spacing. |  |
| [B0069 · 380–390](../../../../../tests/unit/batch_window_exception_test.cpp#L380) | Callable definition: void check_alias_rollback(const PhysicalRetryAttempt& attempt) | calls status, check, progress, image; guard check(status.phase == SessionPhase::ready && !status.pending_sequence && · [reviewed contract](#b0069) |
| [B0070 · 391–391](../../../../../tests/unit/batch_window_exception_test.cpp#L391) | Explanatory comments or spacing. |  |
| [B0071 · 392–404](../../../../../tests/unit/batch_window_exception_test.cpp#L392) | Callable definition: void retry_alias_input(PhysicalRetryAttempt& attempt) | calls check, begin_next, finish_current, image; guard check(attempt.session-&gt;begin_next(), "same alias input was lost on retry");; returns std::find(after.rows.begin(), after.rows.end(), row) != after.rows.end() · [reviewed contract](#b0071) |
| [B0072 · 405–405](../../../../../tests/unit/batch_window_exception_test.cpp#L405) | Explanatory comments or spacing. |  |
| [B0073 · 406–437](../../../../../tests/unit/batch_window_exception_test.cpp#L406) | Callable definition: void self_join_pending_epoch_begin_and_step_failures_retry() | calls alias_retry_attempt, begin_next, check_alias_rollback, retry_alias_input; guard check(rows.size() == 2,; returns alias_retry_attempt(); attempt · [reviewed contract](#b0073) |
| [B0074 · 438–438](../../../../../tests/unit/batch_window_exception_test.cpp#L438) | Explanatory comments or spacing. |  |
| [B0075 · 439–444](../../../../../tests/unit/batch_window_exception_test.cpp#L439) | Type/record definition: struct WindowAttempt |  · [reviewed contract](#b0075) |
| [B0076 · 445–445](../../../../../tests/unit/batch_window_exception_test.cpp#L445) | Explanatory comments or spacing. |  |
| [B0077 · 446–458](../../../../../tests/unit/batch_window_exception_test.cpp#L446) | Callable definition: WindowAttempt initial_window_attempt(WindowOptions options = window_options()) | calls window_options, QuerySession::create_windowed, unary_plan, std::move; returns attempt · [reviewed contract](#b0077) |
| [B0078 · 459–459](../../../../../tests/unit/batch_window_exception_test.cpp#L459) | Explanatory comments or spacing. |  |
| [B0079 · 460–470](../../../../../tests/unit/batch_window_exception_test.cpp#L460) | Callable definition: void check_window_rollback(const WindowAttempt& attempt) | calls status, check, progress, image; guard check(status.phase == SessionPhase::ready && !status.pending_sequence && · [reviewed contract](#b0079) |
| [B0080 · 471–471](../../../../../tests/unit/batch_window_exception_test.cpp#L471) | Explanatory comments or spacing. |  |
| [B0081 · 472–481](../../../../../tests/unit/batch_window_exception_test.cpp#L472) | Callable definition: void retry_first_window_insert(WindowAttempt& attempt) | calls check, begin_next, finish_current, window_state; guard check(attempt.session-&gt;begin_next(), "same window insertion was lost on retry"); · [reviewed contract](#b0081) |
| [B0082 · 482–482](../../../../../tests/unit/batch_window_exception_test.cpp#L482) | Explanatory comments or spacing. |  |
| [B0083 · 483–512](../../../../../tests/unit/batch_window_exception_test.cpp#L483) | Callable definition: void window_new_label_and_count_nodes_rollback() | calls initial_window_attempt, begin_next, check_window_rollback, retry_first_window_insert; guard check(attempt.session-&gt;window_state()-&gt;labels.size() == 1,; returns initial_window_attempt(); attempt · [reviewed contract](#b0083) |
| [B0084 · 513–513](../../../../../tests/unit/batch_window_exception_test.cpp#L513) | Explanatory comments or spacing. |  |
| [B0085 · 514–529](../../../../../tests/unit/batch_window_exception_test.cpp#L514) | Callable definition: WindowAttempt duplicate_window_attempt() | calls QuerySession::create_windowed, unary_plan, window_options, batch; guard check(session-&gt;begin_next(), "duplicate window seed did not begin");; returns attempt · [reviewed contract](#b0085) |
| [B0086 · 530–530](../../../../../tests/unit/batch_window_exception_test.cpp#L530) | Explanatory comments or spacing. |  |
| [B0087 · 531–548](../../../../../tests/unit/batch_window_exception_test.cpp#L531) | Callable definition: void finish_duplicate_metadata_command(QuerySession& session,bool begin_input=true) | calls check, begin_next, status, step; guard check(session.begin_next(), "duplicate full-row command did not retry"); · [reviewed contract](#b0087) |
| [B0088 · 549–549](../../../../../tests/unit/batch_window_exception_test.cpp#L549) | Explanatory comments or spacing. |  |
| [B0089 · 550–584](../../../../../tests/unit/batch_window_exception_test.cpp#L550) | Callable definition: void duplicate_row_metadata_prepare_and_commit() | calls duplicate_window_attempt, begin_next, check_window_rollback, finish_duplicate_metadata_command; guard check(attempt.session-&gt;begin_next(), "duplicate no-allocation fixture did not begin");; returns duplicate_window_attempt() · [reviewed contract](#b0089) |
| [B0090 · 585–585](../../../../../tests/unit/batch_window_exception_test.cpp#L585) | Explanatory comments or spacing. |  |
| [B0091 · 586–613](../../../../../tests/unit/batch_window_exception_test.cpp#L586) | Callable definition: WindowAttempt watermark_attempt(bool partial_prefix, bool prepare_second) | calls window_options, QuerySession::create_windowed, unary_plan, batch; guard check(session-&gt;begin_next(), "watermark fixture did not begin its first insert");; returns attempt · [reviewed contract](#b0091) |
| [B0092 · 614–614](../../../../../tests/unit/batch_window_exception_test.cpp#L614) | Explanatory comments or spacing. |  |
| [B0093 · 615–625](../../../../../tests/unit/batch_window_exception_test.cpp#L615) | Callable definition: void check_watermark_prefix_rollback(const WindowAttempt& attempt) | calls status, check, progress, image; guard check(status.phase == SessionPhase::ready && !status.pending_sequence && · [reviewed contract](#b0093) |
| [B0094 · 626–626](../../../../../tests/unit/batch_window_exception_test.cpp#L626) | Explanatory comments or spacing. |  |
| [B0095 · 627–638](../../../../../tests/unit/batch_window_exception_test.cpp#L627) | Callable definition: void retry_watermark_step(WindowAttempt& attempt) | calls check, begin_next, finish_current, status; guard check(attempt.session-&gt;begin_next(), "watermark command head was lost on retry"); · [reviewed contract](#b0095) |
| [B0096 · 639–639](../../../../../tests/unit/batch_window_exception_test.cpp#L639) | Explanatory comments or spacing. |  |
| [B0097 · 640–673](../../../../../tests/unit/batch_window_exception_test.cpp#L640) | Callable definition: void watermark_preflight_and_first_step_failures_retry() | calls watermark_attempt, begin_next, check_watermark_prefix_rollback, retry_watermark_step; guard check(state && state-&gt;active_command &&; returns watermark_attempt(false, false); attempt · [reviewed contract](#b0097) |
| [B0098 · 674–674](../../../../../tests/unit/batch_window_exception_test.cpp#L674) | Explanatory comments or spacing. |  |
| [B0099 · 675–724](../../../../../tests/unit/batch_window_exception_test.cpp#L675) | Callable definition: void later_watermark_step_failure_preserves_real_prefix_and_retries() | calls watermark_attempt, begin_next, check_watermark_prefix_rollback, check; guard check(attempt.before.sequence == 3 && attempt.before.progress.sequence == 2 &&; returns watermark_attempt(true, false); watermark_attempt(true, true) · [reviewed contract](#b0099) |
| [B0100 · 725–725](../../../../../tests/unit/batch_window_exception_test.cpp#L725) | Explanatory comments or spacing. |  |
| [B0101 · 726–799](../../../../../tests/unit/batch_window_exception_test.cpp#L726) | Callable definition: void resource_limits_preserve_last_committed_window_state() | calls window_options, QuerySession::create_windowed, unary_plan, batch; guard check(session-&gt;begin_next(), "max-label fixture did not begin its seed"); · [reviewed contract](#b0101) |
| [B0102 · 800–800](../../../../../tests/unit/batch_window_exception_test.cpp#L800) | Explanatory comments or spacing. |  |
| [B0103 · 801–824](../../../../../tests/unit/batch_window_exception_test.cpp#L801) | Callable definition: void prepared_window_publication_and_ack_are_allocation_free() | calls QuerySession::create_windowed, unary_plan, window_options, batch; guard check(session-&gt;begin_next(), "no-allocation physical window step did not begin"); · [reviewed contract](#b0103) |
| [B0104 · 825–825](../../../../../tests/unit/batch_window_exception_test.cpp#L825) | Explanatory comments or spacing. |  |
| [B0105 · 826–829](../../../../../tests/unit/batch_window_exception_test.cpp#L826) | Type/record definition: struct CleanupAttempt |  · [reviewed contract](#b0105) |
| [B0106 · 830–830](../../../../../tests/unit/batch_window_exception_test.cpp#L830) | Explanatory comments or spacing. |  |
| [B0107 · 831–849](../../../../../tests/unit/batch_window_exception_test.cpp#L831) | Callable definition: CleanupAttempt prepared_window_cleanup_attempt() | calls QuerySession::create_windowed, unary_plan, window_options, batch; guard check(session-&gt;begin_next(), "cleanup fixture did not begin its retained insert");; returns attempt · [reviewed contract](#b0107) |
| [B0108 · 850–850](../../../../../tests/unit/batch_window_exception_test.cpp#L850) | Explanatory comments or spacing. |  |
| [B0109 · 851–880](../../../../../tests/unit/batch_window_exception_test.cpp#L851) | Callable definition: void stop_drop_and_final_owner_cleanup_allocate_nothing() | calls prepared_window_cleanup_attempt, forbid_allocations, stop, drop; guard check(cleanup_allocations == 0 && attempt.returned && · [reviewed contract](#b0109) |
| [B0110 · 881–881](../../../../../tests/unit/batch_window_exception_test.cpp#L881) | Explanatory comments or spacing. |  |
| [B0111 · 882–934](../../../../../tests/unit/batch_window_exception_test.cpp#L882) | Callable definition: void partial_watermark_stop_releases_prepared_tail_without_allocation() | calls n, QuerySession::create_windowed, unary_plan, window_options; guard check(session-&gt;begin_next(), "partial-stop fixture did not begin insert one");; source comment (unverified): // The first committed insert output is retained independently of the session. · [reviewed contract](#b0111) |
| [B0112 · 935–937](../../../../../tests/unit/batch_window_exception_test.cpp#L935) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0112) |
| [B0113 · 938–958](../../../../../tests/unit/batch_window_exception_test.cpp#L938) | Callable definition: int main() | calls typed_session_construction_unwinds_cleanly, queue_admission_is_transactional_and_retriable, new_source_peek_node_allocation_is_retriable, self_join_pending_epoch_begin_and_step_failures_retry; returns 1; 0 · [reviewed contract](#b0113) |

## B0001

[Lines 1–26](../../../../../tests/unit/batch_window_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L26:sha256:c68cb6e751fddec1cc76adb2cd66cc8f8667fd6275b6a0b7d3a9e1d35bd2ae90
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare batch_window_exception_test.cpp: include "crown/api/error.hpp", "crown/planner/lower.hpp", "crown/runtime/session.hpp", &lt;algorithm&gt;, &lt;cstddef&gt;, &lt;cstdint&gt;, &lt;cstdlib&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;, &lt;type_traits&gt;, &lt;utility&gt;, &lt;vector&gt;; declare fixture state/default initializers. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. The source span lists the exact member/global names, types and initial values; initializers run when the enclosing object/program/thread is initialized. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. Thread-local fault/countdown state belongs to this test executable and each thread; it is not a field added to a production owner. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. This span initializes fixed scalar/atomic/TLS probe state. Storage and later probe accesses are test costs; no native factory or filesystem operation is implied by these scalar initializers. TLS storage and later injector accesses are test instrumentation costs. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 27–35](../../../../../tests/unit/batch_window_exception_test.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the test-local malloc-backed ordinary-new fault point. |
| inputs / outputs | A requested size and thread-local fail_after enter; an admitted request returns std::malloc storage (one byte for size zero), while selected index zero or malloc null throws std::bad_alloc. |
| invariants | Each call increments allocation_count; a positive index decrements exactly once before malloc, and zero throws before malloc. |
| ownership | The seam borrows only thread-local fail_after/allocation_count. Successful storage is returned to the C++ caller and released through the replacement delete overloads. |
| failure | Only requests routed through this ordinary global new/new\[\] replacement are selected. Raw malloc/realloc, aligned/nothrow new, account admission denial, and syscalls are outside. |
| cost | One index/count update and at most one malloc attempt per intercepted C++ allocation call. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0004

[Lines 37–43](../../../../../tests/unit/batch_window_exception_test.cpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct FaultScope {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Arm, disable, or forbid intercepted allocations for one test scope. |
| inputs / outputs | An optional signed fault position enters construction; destruction resets fail_after to -1; forbid_allocations() sets it to zero. |
| invariants | Copy and assignment are deleted. A guard resets injection instead of restoring a prior nested state. |
| ownership | Borrows and mutates only the executable-local thread-local failure/index scalars; owns no runtime, input, or allocation result. |
| failure | Guard construction sets the requested index, destruction disables injection by setting -1, and forbid_allocations() sets zero. It is not a nested-state stack and catches no exception. |
| cost | Constant scalar bookkeeping; the optional allocation_count is incremented only by malloc_new calls. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0005

[Lines 44–45](../../../../../tests/unit/batch_window_exception_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L45:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in batch_window_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 46–46](../../../../../tests/unit/batch_window_exception_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new(std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch scalar ordinary operator new through malloc_new. |
| inputs / outputs | A byte count enters; malloc_new returns malloc-backed storage or throws bad_alloc. |
| invariants | Scalar and array ordinary allocations share one thread-local fail_after index and one allocation counter. |
| ownership | The test executable owns only thread-local fail_after and allocation_count scalars. A successful replacement request returns malloc-backed storage to its caller; the matching replacement delete releases it. |
| failure | A selected fail_after position throws std::bad_alloc at ordinary global operator new or operator new\[\]; a null std::malloc result also throws. The harness does not replace aligned or nothrow overloads and does not inject raw malloc/realloc, system-call, or MemoryAccount admission failures. Accounted allocations are intercepted only if admission succeeds and execution reaches one of these replaced ordinary new overloads. |
| cost | One thread-local index check and, when admitted, one std::malloc attempt. Fault positions count intercepted C++ allocation calls, not requested bytes, account charges, RSS, abstract work, or CPU time. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0007

[Lines 47–47](../../../../../tests/unit/batch_window_exception_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch array ordinary operator new\[\] through malloc_new. |
| inputs / outputs | A byte count enters; malloc_new returns malloc-backed storage or throws bad_alloc. |
| invariants | Scalar and array ordinary allocations share one thread-local fail_after index and one allocation counter. |
| ownership | The test executable owns only thread-local fail_after and allocation_count scalars. A successful replacement request returns malloc-backed storage to its caller; the matching replacement delete releases it. |
| failure | A selected fail_after position throws std::bad_alloc at ordinary global operator new or operator new\[\]; a null std::malloc result also throws. The harness does not replace aligned or nothrow overloads and does not inject raw malloc/realloc, system-call, or MemoryAccount admission failures. Accounted allocations are intercepted only if admission succeeds and execution reaches one of these replaced ordinary new overloads. |
| cost | One thread-local index check and, when admitted, one std::malloc attempt. Fault positions count intercepted C++ allocation calls, not requested bytes, account charges, RSS, abstract work, or CPU time. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0008

[Lines 48–48](../../../../../tests/unit/batch_window_exception_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage through scalar unsized delete. |
| inputs / outputs | A pointer previously returned from compatible replacement allocation enters; the function returns no value. |
| invariants | The body calls std::free and does not change the failure position or allocation counter. |
| ownership | The pointer is borrowed for this call and released here; it must be storage compatible with this executable’s malloc-backed new replacement. |
| failure | Delete itself is not fault injected; these four overloads cover ordinary scalar/array sized and unsized forms only. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0009

[Lines 49–49](../../../../../tests/unit/batch_window_exception_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage through array unsized delete. |
| inputs / outputs | A pointer previously returned from compatible replacement allocation enters; the function returns no value. |
| invariants | The body calls std::free and does not change the failure position or allocation counter. |
| ownership | The pointer is borrowed for this call and released here; it must be storage compatible with this executable’s malloc-backed new replacement. |
| failure | Delete itself is not fault injected; these four overloads cover ordinary scalar/array sized and unsized forms only. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0010

[Lines 50–50](../../../../../tests/unit/batch_window_exception_test.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage through scalar sized delete. |
| inputs / outputs | A pointer previously returned from compatible replacement allocation enters; the function returns no value. |
| invariants | The body calls std::free and does not change the failure position or allocation counter. |
| ownership | The pointer is borrowed for this call and released here; it must be storage compatible with this executable’s malloc-backed new replacement. |
| failure | Delete itself is not fault injected; these four overloads cover ordinary scalar/array sized and unsized forms only. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0011

[Lines 51–51](../../../../../tests/unit/batch_window_exception_test.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release malloc-backed storage through array sized delete. |
| inputs / outputs | A pointer previously returned from compatible replacement allocation enters; the function returns no value. |
| invariants | The body calls std::free and does not change the failure position or allocation counter. |
| ownership | The pointer is borrowed for this call and released here; it must be storage compatible with this executable’s malloc-backed new replacement. |
| failure | Delete itself is not fault injected; these four overloads cover ordinary scalar/array sized and unsized forms only. |
| cost | One std::free call and no allocation request. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0012

[Lines 52–58](../../../../../tests/unit/batch_window_exception_test.cpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L58:sha256:8b28c7985a28e23d57289a2c6b7140ad9ca93b886ee45d283d0263995beca077
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare batch_window_exception_test.cpp: bind local aliases/name imports; require 1 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0013

[Lines 59–61](../../../../../tests/unit/batch_window_exception_test.cpp#L59); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a false test predicate into a named runtime_error. |
| inputs / outputs | A bool and diagnostic string enter; true returns, false throws with that message. |
| invariants | No product exception is caught or retried. |
| ownership | Arguments are borrowed for the call; any constructed diagnostic string belongs to the throwing runtime_error. |
| failure | A false predicate throws std::runtime_error. The helper catches no product exception and performs no retry. |
| cost | One boolean branch and, on failure, message construction; no runtime budget is measured. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp) |

## B0015

[Lines 63–73](../../../../../tests/unit/batch_window_exception_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Action>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a forwarded action to throw crown::api::Error with the expected code. |
| inputs / outputs | An action and expected code view enter; a matching Error returns normally. |
| invariants | Wrong code and no Error both fail through check/runtime_error; other exception types propagate. |
| ownership | Arguments are borrowed for the call; any constructed diagnostic string belongs to the throwing runtime_error. |
| failure | Catches only crown::api::Error. A code mismatch is reported as runtime_error and std::bad_alloc is not accepted as an expected product error. |
| cost | One boolean branch and, on failure, message construction; no runtime budget is measured. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0017

[Lines 75–75](../../../../../tests/unit/batch_window_exception_test.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Value n(std::int64_t value) { return value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap one int64 fixture value in Value. |
| inputs / outputs | An int64 enters by value; a Value with that integer exits. |
| invariants | The returned variant stores the scalar value without retaining a view. |
| ownership | By-value return objects own their fixture members. Local catalog/query/tree values are destroyed after lowering; the returned plan owns its compiled fixture representation. |
| failure | Ordinary allocation, planner, or standard-library failures propagate; these fixture factories install no fault scope and translate no error. |
| cost | Constructs one fixed, small schema/query/tree or value; not a planner benchmark or resource-limit assertion. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0019

[Lines 77–79](../../../../../tests/unit/batch_window_exception_test.cpp#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Catalog unary_catalog() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the one-relation catalog used by the unary session fixture. |
| inputs / outputs | No input; Catalog version 91 with relation R and int64 column x exits. |
| invariants | The schema has one table/column and is consumed by unary_plan. |
| ownership | By-value return objects own their fixture members. Local catalog/query/tree values are destroyed after lowering; the returned plan owns its compiled fixture representation. |
| failure | Ordinary allocation, planner, or standard-library failures propagate; these fixture factories install no fault scope and translate no error. |
| cost | Constructs one fixed, small schema/query/tree or value; not a planner benchmark or resource-limit assertion. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0021

[Lines 81–89](../../../../../tests/unit/batch_window_exception_test.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan unary_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower the one-column unary query used by typed/window session tests. |
| inputs / outputs | No input; local Catalog, Query, and FreeConnexTree enter lower_tree; an owning PhysicalPlan exits. |
| invariants | Table/variable/node identifiers are the fixed zero IDs and the output is x. |
| ownership | By-value return objects own their fixture members. Local catalog/query/tree values are destroyed after lowering; the returned plan owns its compiled fixture representation. |
| failure | Ordinary allocation, planner, or standard-library failures propagate; these fixture factories install no fault scope and translate no error. |
| cost | Constructs one fixed, small schema/query/tree or value; not a planner benchmark or resource-limit assertion. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0023

[Lines 91–104](../../../../../tests/unit/batch_window_exception_test.cpp#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan alias_plan() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a two-occurrence self-join plan for alias-route retry tests. |
| inputs / outputs | No input; catalog E(x,z), repeated forward/reverse atoms, output x,z, and generalized/native tree enter lower_tree; an owning PhysicalPlan exits. |
| invariants | Both native occurrences route to the same physical table with opposite variable order; fixture IDs are fixed. |
| ownership | By-value return objects own their fixture members. Local catalog/query/tree values are destroyed after lowering; the returned plan owns its compiled fixture representation. |
| failure | Ordinary allocation, planner, or standard-library failures propagate; these fixture factories install no fault scope and translate no error. |
| cost | Constructs one fixed, small schema/query/tree or value; not a planner benchmark or resource-limit assertion. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0025

[Lines 106–112](../../../../../tests/unit/batch_window_exception_test.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputItem physical_item(std::uint64_t sequence, Row row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a physical InputEvent with an explicit source position. |
| inputs / outputs | Sequence, owning Row, source string, and offset enter; an InputItem containing an insert on table 0 exits. |
| invariants | The input row and source string are moved into the event; default source and offset are source-A and zero. |
| ownership | Input rows and source strings are passed by value and moved into the returned owning input variant or transport batch. |
| failure | Validation and ordinary construction failures propagate. These builders do not enqueue, acknowledge, or catch failures. |
| cost | Constructs one fixed input item/batch and its row/source-position values. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md) |

## B0027

[Lines 114–120](../../../../../tests/unit/batch_window_exception_test.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputItem window_insert(std::uint64_t sequence, std::uint64_t label,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one typed window-insert command with a deterministic source position. |
| inputs / outputs | Sequence, label, owning Row, timestamp, and source enter; an InputItem/WindowCommand exits with offset sequence*10. |
| invariants | The operation is an insert to table 0 and the row/source strings are moved into the command. |
| ownership | Input rows and source strings are passed by value and moved into the returned owning input variant or transport batch. |
| failure | Validation and ordinary construction failures propagate. These builders do not enqueue, acknowledge, or catch failures. |
| cost | Constructs one fixed input item/batch and its row/source-position values. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0029

[Lines 122–126](../../../../../tests/unit/batch_window_exception_test.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputItem watermark(std::uint64_t sequence, std::uint64_t time,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one typed watermark command with a deterministic source position. |
| inputs / outputs | Sequence, watermark time, and source enter; an InputItem/WindowCommand exits with offset sequence*10. |
| invariants | Only the watermark command is constructed; this helper does not execute or complete it. |
| ownership | Input rows and source strings are passed by value and moved into the returned owning input variant or transport batch. |
| failure | Validation and ordinary construction failures propagate. These builders do not enqueue, acknowledge, or catch failures. |
| cost | Constructs one fixed input item/batch and its row/source-position values. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0031

[Lines 128–130](../../../../../tests/unit/batch_window_exception_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::TransportBatch batch(std::vector<io::InputItem> items) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move a vector of input items into a transport batch. |
| inputs / outputs | An owning vector enters by value; one owning TransportBatch exits. |
| invariants | The helper performs no admission or queue acknowledgement. |
| ownership | Input rows and source strings are passed by value and moved into the returned owning input variant or transport batch. |
| failure | Validation and ordinary construction failures propagate. These builders do not enqueue, acknowledge, or catch failures. |
| cost | Constructs one fixed input item/batch and its row/source-position values. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [docs/batches_windows.md § Typed ordered input](../../../../batches_windows.md) |

## B0033

[Lines 132–138](../../../../../tests/unit/batch_window_exception_test.cpp#L132); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the detached session image used for rollback comparisons. |
| inputs / outputs | Stores sequence, InputProgress, exported Row vector, optional WindowProgress, and value equality. |
| invariants | Equality compares all four saved components; it does not retain a QuerySession or accounted tuple. |
| ownership | The aggregate owns its progress/window copies and exported Row values; it holds no session, snapshot, or tuple references. |
| failure | Snapshot, tuple export, vector growth, or ordinary allocation errors propagate; this oracle does not catch product errors or install a fault scope. |
| cost | Copies every row in one session snapshot and copies its fixed progress/window metadata; this oracle is not a runtime cost bound. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0035

[Lines 140–148](../../../../../tests/unit/batch_window_exception_test.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionImage image(const QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture sequence, progress, window metadata, and exported rows from a session snapshot. |
| inputs / outputs | A QuerySession is borrowed; snapshot() supplies sequence/progress/window and each tuple is exported into an owned Row in SessionImage. |
| invariants | No result ordering normalization is performed; the image reflects snapshot row iteration order. |
| ownership | The session is borrowed. Returned SessionImage owns exported Row copies and copied progress/window metadata; no reference into the snapshot escapes. |
| failure | Snapshot, tuple export, vector growth, or ordinary allocation errors propagate; this oracle does not catch product errors or install a fault scope. |
| cost | Copies every row in one session snapshot and copies its fixed progress/window metadata; this oracle is not a runtime cost bound. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0037

[Lines 150–152](../../../../../tests/unit/batch_window_exception_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<io::QueueStats> queue_stats(const QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read optional typed-queue statistics from session status. |
| inputs / outputs | A QuerySession is borrowed; its optional QueueStats is copied out. |
| invariants | A session without a typed queue yields nullopt; no queue head is consumed. |
| ownership | Borrows the session during status(); returns a value copy of QueueStats or an empty optional. |
| failure | Session-state errors and allocation failures propagate. These helpers contain no recovery catch unless the called test says otherwise. |
| cost | One status read and optional statistics copy. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0039

[Lines 154–160](../../../../../tests/unit/batch_window_exception_test.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowOptions window_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the fixed five-unit per-relation window policy for table zero. |
| inputs / outputs | No input; WindowOptions with managed table 0, width 5, and per_relation FIFO exits. |
| invariants | Other option limits retain their declared defaults. |
| ownership | By-value return objects own their fixture members. Local catalog/query/tree values are destroyed after lowering; the returned plan owns its compiled fixture representation. |
| failure | Ordinary allocation, planner, or standard-library failures propagate; these fixture factories install no fault scope and translate no error. |
| cost | Constructs one fixed, small schema/query/tree or value; not a planner benchmark or resource-limit assertion. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0041

[Lines 162–164](../../../../../tests/unit/batch_window_exception_test.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drain_output(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard all currently available SignedResult output from a session. |
| inputs / outputs | A QuerySession is borrowed; repeatedly calls next_output() until empty and returns void. |
| invariants | Every returned result is discarded in the loop; it does not start or consume another input event. |
| ownership | Borrows the session; each returned optional/SignedResult is a temporary owner destroyed by the loop iteration. |
| failure | next_output errors propagate. It catches no product or allocation error. |
| cost | One next_output call per available result and one terminal empty read. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0043

[Lines 166–170](../../../../../tests/unit/batch_window_exception_test.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_current(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Step the current session input until the prepared barrier is reached. |
| inputs / outputs | A QuerySession is borrowed; repeated step() calls exit when DeltaStep::prepared is observed. |
| invariants | Requires a current pending input that can make progress; it neither commits nor acknowledges it. |
| ownership | Borrows and mutates session progress; no pending token escapes. |
| failure | step/API errors propagate; the loop has no local error recovery. |
| cost | At least one step call; number of persistent engine steps depends on the fixed input fixture and is not a CPU bound. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0045

[Lines 172–176](../../../../../tests/unit/batch_window_exception_test.cpp#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish_current(QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare, commit, then drain output for the current session input. |
| inputs / outputs | A QuerySession is borrowed; no value exits. |
| invariants | Commit occurs after prepare_current; drain_output consumes only that command’s result output. |
| ownership | Mutates a caller-owned session; output results are discarded by drain_output. |
| failure | Preparation, commit, or output errors propagate and are not translated. |
| cost | Completes the current input and drains its currently available results; internal work is not timed. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0047

[Lines 178–181](../../../../../tests/unit/batch_window_exception_test.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void accept(QuerySession& session, io::TransportBatch& input) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that typed batch admission returns accepted. |
| inputs / outputs | A session and caller-owned TransportBatch are borrowed mutably; no value exits. |
| invariants | Any other Admission outcome throws; successful admission transfers the complete batch to queue ownership. |
| ownership | Borrows both inputs for this call; enqueue mutates/transfers the batch on success. |
| failure | An unaccepted batch throws via check; queue errors propagate. |
| cost | One enqueue attempt for the supplied batch. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/batches_windows.md § Native typed queue admission](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0049

[Lines 183–217](../../../../../tests/unit/batch_window_exception_test.cpp#L183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class Context, class Factory, class Operation, class AfterFailure,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep successive ordinary-new failure indices around one supplied operation. |
| inputs / outputs | Label, Context factory, operation, after-failure callback, and after-success callback enter; number of injected bad_alloc positions exits and is printed. |
| invariants | Each iteration creates Context before arming the index; operation alone runs under FaultScope. It requires at least one injected failure before first success and guards ptrdiff index exhaustion. |
| ownership | Each loop iteration owns a newly constructed Context from factory(); that Context remains alive through the operation and post-failure/post-success oracle. |
| failure | Only std::bad_alloc is caught. It is kept armed through operation stack unwinding, then the guard disables it before callbacks. Every fault index rebuilds a fresh Context; only the callbacks decide whether an operation is retried on that same Context. |
| cost | The loop increases one C++ allocation-call index until a first success and can rebuild the fixture at each position. It has no byte, work, wall-clock, or CPU-time bound. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md) |

## B0051

[Lines 219–223](../../../../../tests/unit/batch_window_exception_test.cpp#L219); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CreateAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the plan and optional session returned by constructor-failure attempts. |
| inputs / outputs | Stores a PhysicalPlan and default-empty QuerySession::Owner; constructor moves the plan into the attempt. |
| invariants | A failed factory must leave session empty; a successful attempt owns the session until reset/destruction. |
| ownership | Owns the moved PhysicalPlan and optional shared session Owner; no session is published unless construction completes. |
| failure | The sweep injects ordinary new/new\[\] failures only in create_typed/create_windowed. A failed construction must leave the optional Owner empty; the next loop iteration is a fresh-owner attempt, not a same-owner constructor retry. |
| cost | Traverses all intercepted ordinary C++ allocation points in the selected constructor, repeating fixed plan construction each time; no account-limit or system-resource limit is set. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md) |

## B0053

[Lines 225–264](../../../../../tests/unit/batch_window_exception_test.cpp#L225); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void typed_session_construction_unwinds_cleanly() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fault-sweep typed and windowed QuerySession construction and verify empty successful state. |
| inputs / outputs | Each fresh CreateAttempt constructs create_typed or create_windowed under successive allocation indices; success checks created state/progress, plus empty window canonical state for the windowed case. |
| invariants | Failure requires no published Owner. Each injected index uses a newly built plan/context, not retry of construction on the failed owner; successful Owner reset is done with ordinary new forbidden. |
| ownership | Each create attempt owns its PhysicalPlan and optional session owner. The factory rebuilds a fresh plan/context at every fault index. |
| failure | The sweep injects ordinary new/new\[\] failures only in create_typed/create_windowed. A failed construction must leave the optional Owner empty; the next loop iteration is a fresh-owner attempt, not a same-owner constructor retry. |
| cost | Traverses all intercepted ordinary C++ allocation points in the selected constructor, repeating fixed plan construction each time; no account-limit or system-resource limit is set. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md) |

## B0055

[Lines 266–271](../../../../../tests/unit/batch_window_exception_test.cpp#L266); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QueueAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one typed session and one caller batch for queue-admission cases. |
| inputs / outputs | Stores a QuerySession::Owner plus TransportBatch by move. |
| invariants | Session and batch lifetimes cover the enqueue attempt/retry; queue ownership transfer is checked by the test. |
| ownership | Owns the session Owner and input batch until accepted enqueue transfers the input. |
| failure | The ordinary-new sweep catches bad_alloc, verifies the same batch and queue statistics remain, then retries that same batch on the same session. A separate full-queue case checks Admission::full and retries the rejected batch after the first event is consumed. Queue admission limits are tested as admission outcomes, not allocator fault injection. |
| cost | A one-event batch and fixed queue; the sweep rebuilds a session for each global-new fault position. No throughput, byte, or CPU bound is asserted. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/batches_windows.md § Native typed queue admission](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0057

[Lines 273–276](../../../../../tests/unit/batch_window_exception_test.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QueueAttempt queue_attempt(io::QueueLimits limits = {}) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a fresh session and one-event physical batch for queue sweeps. |
| inputs / outputs | Optional QueueLimits enter; typed session and one event (sequence 1, row 7, source new-source, offset 50) exit inside QueueAttempt. |
| invariants | Input begins caller-owned and is not enqueued until the test operation. |
| ownership | QueueAttempt owns its session and caller TransportBatch. On accepted enqueue, input ownership transfers to the session queue; on rejection/failure, the batch remains with the caller. |
| failure | Fixture creation and event construction occur before FaultScope in the sweep; errors propagate. |
| cost | One unary plan/session plus one physical event. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/batches_windows.md § Native typed queue admission](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0059

[Lines 278–315](../../../../../tests/unit/batch_window_exception_test.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void queue_admission_is_transactional_and_retriable() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check transactional queue admission under allocation failure and full-queue rejection. |
| inputs / outputs | Runs an indexed enqueue sweep over one event, then a one-batch/one-event limit scenario with two caller batches. |
| invariants | On bad_alloc same batch/session retry must succeed with one event; on full, second batch/stats remain unchanged until first event is processed, then same batch is accepted. |
| ownership | QueueAttempt owns its session and caller TransportBatch. On accepted enqueue, input ownership transfers to the session queue; on rejection/failure, the batch remains with the caller. |
| failure | The ordinary-new sweep catches bad_alloc, verifies the same batch and queue statistics remain, then retries that same batch on the same session. A separate full-queue case checks Admission::full and retries the rejected batch after the first event is consumed. Queue admission limits are tested as admission outcomes, not allocator fault injection. |
| cost | A one-event batch and fixed queue; the sweep rebuilds a session for each global-new fault position. No throughput, byte, or CPU bound is asserted. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/batches_windows.md § Native typed queue admission](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0061

[Lines 317–328](../../../../../tests/unit/batch_window_exception_test.cpp#L317); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PeekAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a queue, its admitted source-position batch, and before statistics for peek tests. |
| inputs / outputs | Constructor creates a physical TypedQueue, admits one event from peek-new-source at offset 51, and saves QueueStats. |
| invariants | The queue head remains queued until explicit acknowledge; no query session is involved. |
| ownership | PeekAttempt owns the typed queue and queued batch; the queue borrows/copies according to its admission API, and returned InputItemView is borrowed from the queue until its head changes. |
| failure | A new-source queue peek node allocation may throw bad_alloc. The test checks unchanged progress/stats and a nonfailed queue, retries peek on the same queue, then acknowledges exactly once. It does not inject an account cap or raw malloc failure. |
| cost | One queued event and one source-position map-node insertion attempt per fault point; no work or CPU budget is measured. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/batches_windows.md § Native typed queue admission](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0063

[Lines 330–355](../../../../../tests/unit/batch_window_exception_test.cpp#L330); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void new_source_peek_node_allocation_is_retriable() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep allocation of the new source-position node during TypedQueue::peek. |
| inputs / outputs | Each fresh PeekAttempt fault-sweeps queue.peek(); failure compares failed/progress/stats, retries peek and acknowledges the same head; success checks a borrowed head and unchanged accepted progress. |
| invariants | The source offset 51 is acknowledged once after retry; successful peek alone does not acknowledge or alter queue stats/progress. |
| ownership | PeekAttempt owns the typed queue and queued batch; the queue borrows/copies according to its admission API, and returned InputItemView is borrowed from the queue until its head changes. |
| failure | A new-source queue peek node allocation may throw bad_alloc. The test checks unchanged progress/stats and a nonfailed queue, retries peek on the same queue, then acknowledges exactly once. It does not inject an account cap or raw malloc failure. |
| cost | One queued event and one source-position map-node insertion attempt per fault point; no work or CPU budget is measured. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/io/ingest.hpp](../../../../../include/crown/io/ingest.hpp), [src/io/ingest.cpp](../../../../../src/io/ingest.cpp), [docs/batches_windows.md § Native typed queue admission](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0065

[Lines 357–362](../../../../../tests/unit/batch_window_exception_test.cpp#L357); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalRetryAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a session and detached committed-state baselines for self-join retry. |
| inputs / outputs | PhysicalRetryAttempt contains Owner, SessionImage, optional canonical window state, and optional QueueStats. |
| invariants | All baselines are captured after seed sequence 1 commits and before the second source event begins. |
| ownership | Owns the session; saved image, canonical window, and statistics are value snapshots. |
| failure | Plan, session, input admission, first event processing, or oracle errors propagate during fixture setup, outside the selected operation fault scope. |
| cost | Builds a fixed two-alias self-join fixture and commits one seed event. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0067

[Lines 364–378](../../../../../tests/unit/batch_window_exception_test.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRetryAttempt alias_retry_attempt() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the self-join fixture with one committed seed and one still-queued event. |
| inputs / outputs | Creates alias_plan, enqueues rows (1,2) then (2,1), starts, processes/commits first event, and captures current state. |
| invariants | The faulted operation targets the second event; expected saved sequence/progress are 1 and the queued head is retained. |
| ownership | PhysicalRetryAttempt owns the QuerySession Owner and detached SessionImage/window/queue snapshots; enqueue transfers the input batch to that session. |
| failure | Plan, session, input admission, first event processing, or oracle errors propagate during fixture setup, outside the selected operation fault scope. |
| cost | Builds a fixed two-alias self-join fixture and commits one seed event. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

## B0069

[Lines 380–390](../../../../../tests/unit/batch_window_exception_test.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_alias_rollback(const PhysicalRetryAttempt& attempt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert begin/step allocation failure preserved the committed alias prefix. |
| inputs / outputs | Borrows PhysicalRetryAttempt; compares status, progress, SessionImage, window state, and queue stats against captured state. |
| invariants | Requires ready phase, no pending sequence/command, input_failed false, committed sequence 1, and unchanged engine image/head. |
| ownership | Borrows the attempt/session and compares against detached snapshots captured before the faulted event. |
| failure | Any changed status, sequence, progress, snapshot, window state, or queue stats throws runtime_error; no product exception is caught here. |
| cost | Takes and compares one small deterministic session snapshot plus canonical window/queue metadata. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md) |

## B0071

[Lines 392–404](../../../../../tests/unit/batch_window_exception_test.cpp#L392); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retry_alias_input(PhysicalRetryAttempt& attempt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retry the same queued self-join event and require both joined rows. |
| inputs / outputs | Mutates the same session through begin_next, finish_current, and image read; checks rows (1,2) and (2,1), sequence/progress 2, queue events zero. |
| invariants | The retry consumes the previously queued event once and leaves no queue event. |
| ownership | Mutates the same attempt-owned session by processing the still-queued second input; local image/row checks own their exported copies. |
| failure | A missing queue head or incomplete result throws runtime_error. Session errors propagate; the helper performs no catch around the retry. |
| cost | Completes one self-join input and scans the small result rows; this is not an engine work/CPU limit. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0073

[Lines 406–437](../../../../../tests/unit/batch_window_exception_test.cpp#L406); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void self_join_pending_epoch_begin_and_step_failures_retry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep self-join begin and persistent-step failures, then retry on the same session. |
| inputs / outputs | First sweep faults begin_next; second begins the same pending event before faulting prepare_current. |
| invariants | Both failure callbacks verify sequence-1 rollback then retry/commit the same queue head. Successful begin is explicitly finished; successful step is committed and output drained. |
| ownership | Each fault position owns a fresh initialized self-join QuerySession. The queued second event remains owned by the same session across the failure oracle and explicit retry. |
| failure | Separate sweeps fault begin_next and persistent step preparation. bad_alloc must preserve the committed seed prefix; after failure the same owner re-begins, prepares, commits, drains output, and acknowledges the same event. Success paths finish/commit that same pending input. |
| cost | Repeatedly rebuilds a fixed self-join with one committed seed and sweeps ordinary new/new\[\] calls through begin or step until one point succeeds. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [tests/unit/physical_runtime_exception_test.cpp](../../../../../tests/unit/physical_runtime_exception_test.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [docs/physical_runtime.md § Input and source-row identity](../../../../physical_runtime.md), [docs/physical_runtime.md § Compiled alias routing and final-native counts](../../../../physical_runtime.md), [docs/physical_runtime.md § Prepare, busy reads, and commit](../../../../physical_runtime.md) |

## B0075

[Lines 439–444](../../../../../tests/unit/batch_window_exception_test.cpp#L439); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WindowAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store the session and committed-state values used by window retry checks. |
| inputs / outputs | WindowAttempt contains Owner, SessionImage, optional WindowCanonicalState, and optional QueueStats. |
| invariants | Snapshots describe one committed prefix and queue head before the target window command. |
| ownership | Owns the session and detached copies of its image/canonical state/queue statistics. |
| failure | Window creation, queue admission, start, and snapshot errors propagate during setup, outside the operation fault scope. |
| cost | Constructs a fixed two-command window fixture and captures one small empty committed prefix. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0077

[Lines 446–458](../../../../../tests/unit/batch_window_exception_test.cpp#L446); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowAttempt initial_window_attempt(WindowOptions options = window_options()) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a windowed session with two queued inserts and capture its empty prefix. |
| inputs / outputs | Optional WindowOptions enter; two inserts (labels 1 and 2, rows 7 and 8, timestamp 0) are admitted, session starts, and baseline state is saved. |
| invariants | No command is begun before the baseline; retry target is label 1. |
| ownership | WindowAttempt owns the windowed session; captured images, canonical state, and queue stats are values detached from the live owner. |
| failure | Window creation, queue admission, start, and snapshot errors propagate during setup, outside the operation fault scope. |
| cost | Constructs a fixed two-command window fixture and captures one small empty committed prefix. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0079

[Lines 460–470](../../../../../tests/unit/batch_window_exception_test.cpp#L460); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_window_rollback(const WindowAttempt& attempt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert a failed first window command left committed engine, canonical, and queue state intact. |
| inputs / outputs | Borrows WindowAttempt; checks status/progress/image/window state/queue statistics. |
| invariants | Requires ready, no pending physical/command sequence, no input failure, and all saved committed values equal. |
| ownership | Borrows the same WindowAttempt; saved SessionImage, WindowCanonicalState, and optional QueueStats are detached before-operation values. |
| failure | A changed committed prefix, progress, canonical window state, queue head/stats, pending status, or input_failed flag throws runtime_error. |
| cost | Compares one small session image, canonical label/count/expiration state, and queue statistics. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0081

[Lines 472–481](../../../../../tests/unit/batch_window_exception_test.cpp#L472); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retry_first_window_insert(WindowAttempt& attempt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retry and commit the same first window insertion after rollback. |
| inputs / outputs | Mutates the same session with begin_next and finish_current; reads WindowCanonicalState and SessionImage. |
| invariants | Requires label 1 and one retained row count, progress sequence 1, and output row 7. |
| ownership | Mutates the same attempt-owned session by reprocessing its queued first window insertion; copied image/state values are local test oracles. |
| failure | The same input must still begin and commit; missing labels/counts/row or unexpected progress throws runtime_error. Errors propagate without being reclassified as allocation failures. |
| cost | Commits one row/label insertion and inspects fixed-size canonical state and rows. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0083

[Lines 483–512](../../../../../tests/unit/batch_window_exception_test.cpp#L483); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void window_new_label_and_count_nodes_rollback() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep new window label/count-node allocation failures in begin and persistent step. |
| inputs / outputs | Fresh initial_window_attempt contexts fault begin_next and prepare_current in separate sweeps. |
| invariants | After bad_alloc, committed baseline and queue must be unchanged, then same session retries first insert. Success paths publish/commit that first insertion. |
| ownership | Each fault point owns a fresh session with two queued window inserts and an unchanged committed prefix; the same session and head are used by the failure callback retry. |
| failure | Separate sweeps fault begin_next and a persistent step. A caught bad_alloc must leave committed state/head untouched; the callback retries and commits the same first insert. The terminal-success callback finishes the first insert. Only replacement global new is injected. |
| cost | Rebuilds the small window fixture for each C++ allocation fault position until the first success; no label/byte/work cap is being injected by this sweep. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0085

[Lines 514–529](../../../../../tests/unit/batch_window_exception_test.cpp#L514); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowAttempt duplicate_window_attempt() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a duplicate full-row command after committing one window label. |
| inputs / outputs | Creates queued label-1 row 7, label-2 same row 7, and watermark 5; commits only the first insertion and snapshots the remaining queue. |
| invariants | The second command is metadata-only for physical multiplicity because its row already exists; watermark remains queued after it. |
| ownership | The attempt owns a windowed session with its input batch admitted; snapshots and stats are detached copies. |
| failure | Fixture creation, seed admission, and seed commit errors propagate before the target operation fault scope. |
| cost | Commits one window label and queues one duplicate-row command plus one watermark command. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0087

[Lines 531–548](../../../../../tests/unit/batch_window_exception_test.cpp#L531); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish_duplicate_metadata_command(QuerySession& session,bool begin_input=true) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish a duplicate-row metadata command and check ordinary-new-free commit. |
| inputs / outputs | Optionally begins queued command; requires pending command 2 without physical pending sequence, steps to prepared, then commits with fail_after=0 and allocation_count reset. |
| invariants | Commit must report zero replaced ordinary-new calls; successful command advances metadata/source progress without running a physical epoch. |
| ownership | Borrows the same session and completes its pending metadata-only command. The queued input remains session-owned after begin_next. |
| failure | Checks command sequence 2 has no pending physical sequence, steps to prepared, then blocks replacement new calls during commit. A mismatch or any intercepted C++ allocation fails the oracle; direct malloc/account/system-call activity is outside the replacement seam. |
| cost | One metadata barrier and one commit over an already prepared duplicate-row command; only replaced ordinary new calls are counted. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0089

[Lines 550–584](../../../../../tests/unit/batch_window_exception_test.cpp#L550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void duplicate_row_metadata_prepare_and_commit() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep duplicate-row metadata preparation and check prepared metadata publication. |
| inputs / outputs | Fault-sweeps begin_next on a same-row second label; also runs an independent no-fault prepared commit with new forbidden. |
| invariants | Failure preserves prior window prefix and retries same command; commit keeps two labels/count 2 but one physical row, physical sequence 1, completed command/progress sequence 2, and one queued watermark event. |
| ownership | Each sweep context owns its session and queued commands; the standalone no-allocation case owns its independent session until assertions complete. |
| failure | bad_alloc during duplicate metadata begin must preserve the prior prefix; retry occurs on the same owner. Prepared metadata commit is separately run with ordinary new forbidden and its allocation counter at zero. It checks two labels refer to one retained physical row/count of two and command/source progress advances. |
| cost | One fixed duplicate-row fixture plus an indexed global-new sweep; the explicit commit oracle counts intercepted ordinary global-new calls only, not raw/account allocation or CPU work. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0091

[Lines 586–613](../../../../../tests/unit/batch_window_exception_test.cpp#L586); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
WindowAttempt watermark_attempt(bool partial_prefix, bool prepare_second) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a two-label watermark fixture with optional committed first expiration prefix. |
| inputs / outputs | Builds rows 1 and 2 at timestamp 0, watermark sequence 3/time 5, and later row command 4; commits the two inserts, optionally one watermark step, and optionally begins the next step. |
| invariants | With partial_prefix, saved progress is sequence 2 while active command 3 has one committed expiration step; prepare_second controls whether that pending step exists. |
| ownership | The helper owns a windowed session with the whole input batch admitted; snapshots returned in WindowAttempt are detached copies. |
| failure | Fixture setup errors propagate before injected scope. Boolean options decide whether one watermark expiration step is committed and whether the next is begun. |
| cost | Commits two inserts and optionally one of the watermark command’s two expiration steps. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0093

[Lines 615–625](../../../../../tests/unit/batch_window_exception_test.cpp#L615); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check_watermark_prefix_rollback(const WindowAttempt& attempt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a failed watermark operation preserves the saved committed prefix and command state. |
| inputs / outputs | Borrows WindowAttempt; compares phase/pending metadata/progress/image/window canonical state/queue stats. |
| invariants | Requires ready, no pending sequence/command, input_failed false, and exact before-image equality, including an active watermark prefix if present. |
| ownership | Borrows the attempt/session and compares with the saved prefix plus saved canonical active-command metadata. |
| failure | Any changed committed sequence/progress, active command, image, canonical state, queue head/stats, or input_failed flag throws runtime_error. |
| cost | Compares one fixed window prefix and its small expiration state. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0095

[Lines 627–638](../../../../../tests/unit/batch_window_exception_test.cpp#L627); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retry_watermark_step(WindowAttempt& attempt) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retry and commit exactly one watermark expiration step on the same session. |
| inputs / outputs | Calls begin_next and finish_current; checks active command state, progress, and remaining queue event count. |
| invariants | After the step, active command sequence is 3, completed_steps is 1, progress remains sequence 2, and queue has two events (watermark plus tail). |
| ownership | Advances the same attempt-owned session and queue head; no separate session is constructed for the retry. |
| failure | Requires begin_next and completion of one expiration step; checks command sequence 3, completed_steps=1, progress remains at sequence 2, and the watermark command plus tail remain queued. Errors propagate. |
| cost | One expiration step and a fixed-size state check; work metrics are not interpreted as CPU time. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0097

[Lines 640–673](../../../../../tests/unit/batch_window_exception_test.cpp#L640); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void watermark_preflight_and_first_step_failures_retry() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep watermark preflight and first persistent-step allocation failures. |
| inputs / outputs | One sweep faults begin_next before preflight; another begins the command and faults prepare_current. |
| invariants | Each bad_alloc preserves the zero-expiration committed prefix, then retries one step on same owner. Successful callbacks commit only the first expiration step. |
| ownership | Each position owns a fresh windowed session. The state snapshot records either the pre-watermark state or a previously committed first-step prefix; retry operates on that same session. |
| failure | Sweeps preflight begin and first persistent step separately, then later-command begin and step separately. On bad_alloc, verifies rollback to the saved committed prefix and retries the same watermark input. Later-step cases require the real completed_steps=1 prefix remain; retry finishes that same command. No account/resource limit is used as the injector. |
| cost | Four indexed sweeps rebuild two-row/two-expiration fixtures until their first success; ordinary new/new\[\] call count only, with no CPU/work/byte bound. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0099

[Lines 675–724](../../../../../tests/unit/batch_window_exception_test.cpp#L675); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void later_watermark_step_failure_preserves_real_prefix_and_retries() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep a later watermark step after one expiration step has already committed. |
| inputs / outputs | One sweep faults later begin_next; another faults prepare_current after beginning the second expiration. |
| invariants | Failure retains the real prefix (snapshot sequence 3, input progress 2, active command 3/completed_steps 1). Same command retry finishes progress 3 and empties rows; success does likewise. |
| ownership | Each position owns a fresh windowed session. The state snapshot records either the pre-watermark state or a previously committed first-step prefix; retry operates on that same session. |
| failure | Sweeps preflight begin and first persistent step separately, then later-command begin and step separately. On bad_alloc, verifies rollback to the saved committed prefix and retries the same watermark input. Later-step cases require the real completed_steps=1 prefix remain; retry finishes that same command. No account/resource limit is used as the injector. |
| cost | Four indexed sweeps rebuild two-row/two-expiration fixtures until their first success; ordinary new/new\[\] call count only, with no CPU/work/byte bound. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md) |

## B0101

[Lines 726–799](../../../../../tests/unit/batch_window_exception_test.cpp#L726); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resource_limits_preserve_last_committed_window_state() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check three window resource-limit rejections preserve the last committed state. |
| inputs / outputs | Separate fixtures exercise max_labels=1, max_accounted_bytes equal to calibrated first-insert accounted_bytes, and command_work_limit=3 on a two-expiration watermark. |
| invariants | Each begin_next must throw Error code resource_limit and leave image/canonical/progress/queue stats unchanged with input_failed false. No bad_alloc fault scope is used. |
| ownership | Each subcase owns its own session, admitted input, and detached before-state images/canonical/queue stats. |
| failure | Checks three explicit resource_limit paths: max_labels=1, max_accounted_bytes calibrated from the first committed insert’s metrics, and command_work_limit=3 for watermark expansion. Each rejection must preserve the last committed image/window/progress/queue and leave input_failed false. These are product resource errors, not injected bad_allocs. |
| cost | Uses small fixed fixtures and compares the reported accounted-byte/work admission behavior; does not time the operation or equate command work with CPU instructions. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [docs/memory_accounts.md § Account and ownership contract](../../../../memory_accounts.md) |

## B0103

[Lines 801–824](../../../../../tests/unit/batch_window_exception_test.cpp#L801); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepared_window_publication_and_ack_are_allocation_free() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require prepared physical/window publication and queue acknowledgement to pass the new seam. |
| inputs / outputs | One queued window insert is begun/prepared; allocation counter resets and fail_after becomes zero around session.commit(). |
| invariants | Requires zero intercepted ordinary new calls and committed window physical/command sequence 1, input progress 1, queue events 0, and row 7 visible. |
| ownership | The session owns the pending window command and engine epoch until commit; the test reads detached state after publication. |
| failure | Prepares one insert, sets fail_after=0 for ordinary new/new\[\], and requires commit plus source acknowledgement to complete without a replaced allocation. It then checks physical/window sequence, progress, empty queue and row result. Other allocation APIs are not faulted. |
| cost | One prepared one-row publication; allocation_count is not used here, so the evidence is successful passage through the ordinary-new failure seam only. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [docs/query_memory.md § Boundaries](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0105

[Lines 826–829](../../../../../tests/unit/batch_window_exception_test.cpp#L826); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CleanupAttempt {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a session plus a previously returned result for cleanup tests. |
| inputs / outputs | CleanupAttempt stores QuerySession::Owner and optional SignedResult. |
| invariants | The result is kept outside session-owned unread output while later input is pending. |
| ownership | Owns both session Owner and optional returned SignedResult; the result tuple is an owning value separate from the session’s output queue. |
| failure | Window preparation/commit, next_output, and queue begin errors propagate during setup, before the no-allocation scope. |
| cost | Commits one row, retains one output result, and starts one queued tail command. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0107

[Lines 831–849](../../../../../tests/unit/batch_window_exception_test.cpp#L831); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CleanupAttempt prepared_window_cleanup_attempt() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a queued tail while retaining one committed result outside the session. |
| inputs / outputs | Admits insert labels 1/2, watermark 3, later insert 4; prepares/commits label 1, obtains row-7 next_output, then begins the queued tail. |
| invariants | Returned result is already detached/owning before cleanup; a later command is pending in the session. |
| ownership | CleanupAttempt owns the QuerySession Owner and a returned SignedResult whose storage::Tuple remains owned after it is removed from session output. |
| failure | Window preparation/commit, next_output, and queue begin errors propagate during setup, before the no-allocation scope. |
| cost | Commits one row, retains one output result, and starts one queued tail command. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0109

[Lines 851–880](../../../../../tests/unit/batch_window_exception_test.cpp#L851); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stop_drop_and_final_owner_cleanup_allocate_nothing() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check stop/drop and final-owner destruction with a pending tail and saved result. |
| inputs / outputs | Runs prepared_window_cleanup_attempt twice; first stop+drop, second resets the last Owner, each with fail_after=0 and allocation_count reset. |
| invariants | Requires zero calls through replaced ordinary global new and saved row 7 remains readable; first case reaches dropped state. It does not count raw/account allocations. |
| ownership | Each fixture retains an owning SignedResult outside the session owner while the session has a pending window tail. The session owner is stopped/dropped or reset; the result tuple remains separately owned by the local optional. |
| failure | With fail_after=0, stop/drop or final Owner reset must not call replaced ordinary new/new\[\]. The oracle checks the returned tuple still contains row 7. Direct malloc, account admission, and system calls are not intercepted, so “no allocation” is scoped to this replacement seam. |
| cost | One fixed pending-window teardown path per case; no allocation-count byte total or CPU time is inferred. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp), [docs/query_memory.md § Boundaries](../../../../query_memory.md) |

## B0111

[Lines 882–934](../../../../../tests/unit/batch_window_exception_test.cpp#L882); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void partial_watermark_stop_releases_prepared_tail_without_allocation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop during a partially committed watermark and check the retained prefix/result. |
| inputs / outputs | Commits insert rows 1 and 2 and one of two watermark expirations, starts the next expiration, then stops and drops under fail_after=0. |
| invariants | After stop, progress remains 2 and row 2 is retained; previously returned row 1 remains readable; active command 3 reports completed 1/total 2 with expiration_labels emptied. |
| ownership | The session owns the active watermark metadata and pending next expiration; \`saved\` owns a returned SignedResult tuple independently of session output/session owner. |
| failure | After one watermark expiration step is committed, stop is called while the next step is pending under fail_after=0. The test requires stopped state, progress 2, row 2 retained, saved row 1 still readable, and active command sequence 3 with completed_steps 1/total_steps 2 but an empty expiration_labels vector. It then drops/resets under the same ordinary-new seam. |
| cost | One partially completed two-label watermark and its stop/drop cleanup; this asserts no replaced global-new calls, not absence of raw/account allocations or CPU work. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [src/runtime/session.cpp](../../../../../src/runtime/session.cpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp), [src/runtime/window.cpp](../../../../../src/runtime/window.cpp), [docs/batches_windows.md § Native window memory ownership](../../../../batches_windows.md), [docs/batches_windows.md § Steps, source progress and failure](../../../../batches_windows.md), [include/crown/runtime/delta.hpp](../../../../../include/crown/runtime/delta.hpp) |

## B0112

[Lines 935–937](../../../../../tests/unit/batch_window_exception_test.cpp#L935); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L935-L937:sha256:9e375a3cb3a2cbe2f9ded9c8296a6ab66848cc826fd71f919246acb17e0bd455
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in batch_window_exception_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/code_review.md](../../../../code_review.md) |

## B0113

[Lines 938–958](../../../../../tests/unit/batch_window_exception_test.cpp#L938); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the batch/window exception-test checks and report std::exception failure. |
| inputs / outputs | Calls all construction, queue, peek, alias, window, watermark, resource, publication, and cleanup helpers; returns 1 after catch or implicit success otherwise. |
| invariants | The source main catches std::exception and writes its diagnostic. This packet inspected control flow only and does not claim the executable was run. |
| ownership | Owns no long-lived fixture; calls each test helper, whose local owners are destroyed before return. |
| failure | Catches std::exception, writes the test diagnostic and returns 1; otherwise falling off main returns success. This card records source control flow only; no test execution is claimed. |
| cost | Invokes the listed deterministic fixture checks and allocation sweeps; no runtime performance assertion is made. |
| Design | [tests/unit/batch_window_exception_test.cpp](../../../../../tests/unit/batch_window_exception_test.cpp) |
