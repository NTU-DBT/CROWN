# `src/runtime/session.cpp` — block usage map

[Source](../../../../../src/runtime/session.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Own input-to-output and durable lifecycle transitions for one creator-thread query session.

Snapshot SHA-256: `052062305174e21be994277a8488f88ab2899dcca6971546a7ca5ae59c2c96cd`. 1776 lines partitioned into 214 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [session](../../../subsystem_contracts.md#session). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/reoptimization.md](../../../../reoptimization.md), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–34](../../../../../src/runtime/session.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 35–37](../../../../../src/runtime/session.cpp#L35) | Callable definition: void require(bool condition,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 38–41](../../../../../src/runtime/session.cpp#L38) | Callable definition: std::size_t add(std::size_t left,std::size_t right) | calls require, max; guard require(right&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-left,"resource_limit","snapshot size account…; returns left+right · [reviewed contract](#b0003) |
| [B0004 · 42–47](../../../../../src/runtime/session.cpp#L42) | Callable definition: std::size_t payload(const storage::Tuple& tuple) | calls require, is_accounted, memory_usage, max; guard require(tuple.is_accounted(),"runtime_contract","snapshot output has no query-account payload");; returns static_cast&lt;std::size_t&gt;(bytes) · [reviewed contract](#b0004) |
| [B0005 · 48–55](../../../../../src/runtime/session.cpp#L48) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;DeltaRuntime::PendingEpoch&gt;);; source comment (unverified): // namespace · [reviewed contract](#b0005) |
| [B0006 · 56–62](../../../../../src/runtime/session.cpp#L56) | Type/record definition: struct SessionRows::Data |  · [reviewed contract](#b0006) |
| [B0007 · 63–63](../../../../../src/runtime/session.cpp#L63) | Callable definition: std::size_t SessionRows::size() const noexcept | calls size; returns data_?data_-&gt;values.size():0 · [reviewed contract](#b0007) |
| [B0008 · 64–64](../../../../../src/runtime/session.cpp#L64) | Callable definition: std::size_t SessionRows::capacity() const noexcept | calls capacity; returns data_?data_-&gt;values.capacity():0 · [reviewed contract](#b0008) |
| [B0009 · 65–65](../../../../../src/runtime/session.cpp#L65) | Callable definition: const storage::Tuple* SessionRows::data() const noexcept | calls data; returns data_?data_-&gt;values.data():nullptr · [reviewed contract](#b0009) |
| [B0010 · 66–69](../../../../../src/runtime/session.cpp#L66) | Callable definition: const storage::Tuple& SessionRows::at(std::size_t i) const | calls size, std::out_of_range; returns (*this)\[i\] · [reviewed contract](#b0010) |
| [B0011 · 70–70](../../../../../src/runtime/session.cpp#L70) | Callable definition: resource::MemoryUsage SessionRows::owner_usage() const noexcept | calls ; returns data_?data_-&gt;control_usage:resource::MemoryUsage{} · [reviewed contract](#b0011) |
| [B0012 · 71–78](../../../../../src/runtime/session.cpp#L71) | Callable definition: resource::MemoryUsage SessionRows::memory_usage() const | calls owner_usage, get_allocator, allocation_usage, data; returns usage · [reviewed contract](#b0012) |
| [B0013 · 79–92](../../../../../src/runtime/session.cpp#L79) | Callable definition: void SessionRows::prepare() | calls require, use_count, statistics, std::move; guard require(data_.use_count()==1,"runtime_contract","snapshot collection already published");return;; growth make_accounted_shared; source comment (unverified): // Data's constructor only installs an empty allocator-aware vector. This is · [reviewed contract](#b0013) |
| [B0014 · 93–93](../../../../../src/runtime/session.cpp#L93) | Callable definition: void SessionRows::reserve(std::size_t capacity) | calls prepare, reserve; growth reserve · [reviewed contract](#b0014) |
| [B0015 · 94–99](../../../../../src/runtime/session.cpp#L94) | Callable definition: void SessionRows::append(storage::Tuple tuple) | calls prepare, require, is_accounted, account_statistics; guard require(tuple.is_accounted() && tuple.account_statistics().owner==account_.statistics().owner,; growth push_back · [reviewed contract](#b0015) |
| [B0016 · 100–100](../../../../../src/runtime/session.cpp#L100) | Explanatory comments or spacing. |  |
| [B0017 · 101–109](../../../../../src/runtime/session.cpp#L101) | Type/record definition: struct SessionStatisticsContext::Data |  · [reviewed contract](#b0017) |
| [B0018 · 110–110](../../../../../src/runtime/session.cpp#L110) | Callable definition: const SessionReportMetadata& SessionStatisticsContext::metadata() const noexcept | calls ; returns data_-&gt;metadata · [reviewed contract](#b0018) |
| [B0019 · 111–111](../../../../../src/runtime/session.cpp#L111) | Callable definition: const SessionStatus& SessionStatisticsContext::status() const noexcept | calls ; returns data_-&gt;status · [reviewed contract](#b0019) |
| [B0020 · 112–112](../../../../../src/runtime/session.cpp#L112) | Callable definition: const CapturedObservationTrace& SessionStatisticsContext::trace() const noexcept | calls ; returns data_-&gt;trace · [reviewed contract](#b0020) |
| [B0021 · 113–113](../../../../../src/runtime/session.cpp#L113) | Callable definition: const std::optional&lt;statistics::CombinedCapture&gt;& SessionStatisticsContext::combined() const noexcept | calls ; returns data_-&gt;combined · [reviewed contract](#b0021) |
| [B0022 · 114–114](../../../../../src/runtime/session.cpp#L114) | Callable definition: const workload::Options& SessionStatisticsContext::workload_options() const noexcept | calls ; returns data_-&gt;options · [reviewed contract](#b0022) |
| [B0023 · 115–115](../../../../../src/runtime/session.cpp#L115) | Callable definition: const std::optional&lt;CursorObservation&gt;& SessionStatisticsContext::cursor() const noexcept | calls ; returns data_-&gt;cursor · [reviewed contract](#b0023) |
| [B0024 · 116–116](../../../../../src/runtime/session.cpp#L116) | Callable definition: bool SessionStatisticsContext::state_requested() const noexcept | calls ; returns data_-&gt;requested · [reviewed contract](#b0024) |
| [B0025 · 117–118](../../../../../src/runtime/session.cpp#L117) | declares namespace scope. |  · [reviewed contract](#b0025) |
| [B0026 · 119–127](../../../../../src/runtime/session.cpp#L119) | Type/record definition: struct ManagedPlan | returns {encoded.bytes.data(),encoded.bytes.size()}; bytes().substr(encoded.bytes.size()-64-artifact_size,a… · [reviewed contract](#b0026) |
| [B0027 · 128–130](../../../../../src/runtime/session.cpp#L128) | Callable definition: bool logical_binding(const recovery::ImageBinding& a,const recovery::ImageBinding& b) | calls ; returns a.source_sha256==b.source_sha256 && a.catalog_version==b.catalog_version && a.policy==b.policy · [reviewed contract](#b0027) |
| [B0028 · 131–131](../../../../../src/runtime/session.cpp#L131) | Callable definition: template&lt;std::size_t N&gt; std::string_view view(const std::array&lt;char,N&gt;& value) noexcept | calls data, size; returns {value.data(),value.size()} · [reviewed contract](#b0028) |
| [B0029 · 132–134](../../../../../src/runtime/session.cpp#L132) | Callable definition: void generation_binding(bool condition) | calls recovery::GenerationFailure · [reviewed contract](#b0029) |
| [B0030 · 135–139](../../../../../src/runtime/session.cpp#L135) | Callable definition: std::array&lt;char,64&gt; result_schema(const resource::MemoryAccount& account,const DeltaRuntime& runtime) | calls fields, reserve, result_layout, size; returns recovery::sink::schema_sha256(account,fields); growth push_back, reserve; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 140–147](../../../../../src/runtime/session.cpp#L140) | Type/record definition: struct PublicationPreparation | returns candidate.publication_prepared(started) · [reviewed contract](#b0031) |
| [B0032 · 148–154](../../../../../src/runtime/session.cpp#L148) | Type/record definition: struct ManagedGeneration |  · [reviewed contract](#b0032) |
| [B0033 · 155–166](../../../../../src/runtime/session.cpp#L155) | Type/record definition: struct ManagedLocalSink |  · [reviewed contract](#b0033) |
| [B0034 · 167–171](../../../../../src/runtime/session.cpp#L167) | Callable definition: void generation_checkpoint_policy(std::string_view path,const recovery::CheckpointFileLimits& limits) | calls size, max, recovery::GenerationFailure · [reviewed contract](#b0034) |
| [B0035 · 172–175](../../../../../src/runtime/session.cpp#L172) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0035) |
| [B0036 · 176–176](../../../../../src/runtime/session.cpp#L176) | Callable definition: explicit RecoveryOutput(const resource::MemoryAccount& account):rows(recovery::image_allocator&lt;RecoveredResult&gt;(account)) | calls rows · [reviewed contract](#b0036) |
| [B0037 · 177–180](../../../../../src/runtime/session.cpp#L177) | Callable definition: std::uint64_t retained_bytes() const | calls resource::MemoryAccount::allocation_bytes, get_allocator, allocation_usage, data; returns resource::MemoryAccount::allocation_bytes(sizeof(RecoveryOutput),alignof(RecoveryOutput))+ · [reviewed contract](#b0037) |
| [B0038 · 181–194](../../../../../src/runtime/session.cpp#L181) | Callable definition: void append(RecoveredResult row,std::size_t max_rows,std::size_t max_bytes) | calls size, recovery::ImageFailure, is_accounted, account_statistics; growth push_back, reserve · [reviewed contract](#b0038) |
| [B0039 · 195–196](../../../../../src/runtime/session.cpp#L195) | Closes surrounding scope/type. |  · [reviewed contract](#b0039) |
| [B0040 · 197–206](../../../../../src/runtime/session.cpp#L197) | Type/record definition: struct LockedGenerationRecovery::Data |  · [reviewed contract](#b0040) |
| [B0041 · 207–207](../../../../../src/runtime/session.cpp#L207) | Callable definition: LockedGenerationRecovery::LockedGenerationRecovery(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0041) |
| [B0042 · 208–208](../../../../../src/runtime/session.cpp#L208) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0042) |
| [B0043 · 209–209](../../../../../src/runtime/session.cpp#L209) | Callable definition: bool LockedGenerationRecovery::has_plan() const noexcept | calls bool; returns bool(data_-&gt;plan) · [reviewed contract](#b0043) |
| [B0044 · 210–212](../../../../../src/runtime/session.cpp#L210) | Callable definition: std::string_view LockedGenerationRecovery::compiler_artifact() const & noexcept | calls artifact; returns data_-&gt;plan?data_-&gt;plan-&gt;artifact():std::string_view{} · [reviewed contract](#b0044) |
| [B0045 · 213–213](../../../../../src/runtime/session.cpp#L213) | Callable definition: resource::MemoryStatistics LockedGenerationRecovery::accounted_memory_statistics() const | calls memory, statistics; returns data_-&gt;context-&gt;memory().statistics() · [reviewed contract](#b0045) |
| [B0046 · 214–235](../../../../../src/runtime/session.cpp#L214) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0046) |
| [B0047 · 236–236](../../../../../src/runtime/session.cpp#L236) | Callable definition: bool delivery_pending() const noexcept | calls ; returns local_sink && (local_sink-&gt;failed \|\| !local_sink-&gt;file \|\| local_sink-&gt;verified_sequence&lt;committed_s… · [reviewed contract](#b0047) |
| [B0048 · 237–237](../../../../../src/runtime/session.cpp#L237) | Callable definition: bool recovery_output_pending() const noexcept | calls size; returns recovered_output && recovered_output-&gt;position&lt;recovered_output-&gt;rows.size() · [reviewed contract](#b0048) |
| [B0049 · 238–238](../../../../../src/runtime/session.cpp#L238) | Callable definition: std::size_t output_remaining() const | calls remaining, size; returns output?output-&gt;remaining():recovered_output?recovered_output-&gt;rows.size()-recovered_output-&gt;positio… · [reviewed contract](#b0049) |
| [B0050 · 239–239](../../../../../src/runtime/session.cpp#L239) | Callable definition: void clear_recovered_output() noexcept | calls reset · [reviewed contract](#b0050) |
| [B0051 · 240–247](../../../../../src/runtime/session.cpp#L240) | Callable definition: void prepare_local_sink(const recovery::journal::Header& journal,const SessionLocalSinkOptions& options,bool replaying) | calls compiled_program, account, result_layout, fields; guard const auto fields=runtime-&gt;result_layout().fields();require(fields.size()&lt;=options.file.record.fiel…; growth make_accounted_unique, push_back, reserve; 1 loop sites · [reviewed contract](#b0051) |
| [B0052 · 248–257](../../../../../src/runtime/session.cpp#L248) | Callable definition: void establish_sink_prefix(const recovery::sink::File& file,const recovery::journal::Header& journal, const std::optional&lt;recover… | calls state, prefix, require, matches; guard if(expected)require(expected-&gt;sequence==journal.physical_sequence && matches(*expected),"local_sink…; returns anchor.sink_id==state.header.sink_id && anchor.bytes==prefix.bytes && anchor.content_sha256==prefix… · [reviewed contract](#b0052) |
| [B0053 · 258–260](../../../../../src/runtime/session.cpp#L258) | Callable definition: void advance_sink_prefix(std::uint64_t sequence) | calls prefix · [reviewed contract](#b0053) |
| [B0054 · 261–286](../../../../../src/runtime/session.cpp#L261) | Callable definition: void collect_recovered_output(const recovery::journal::Header& header,const SessionJournalRecoveryOptions& options) | calls state, require, remaining, recovery::ImageFailure; guard require(sequence&gt;sink.verified_sequence && sequence-sink.verified_sequence==1,"local_sink_binding",…; growth make_accounted_unique, push_back, reserve; 1 loop sites · [reviewed contract](#b0054) |
| [B0055 · 287–287](../../../../../src/runtime/session.cpp#L287) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0055) |
| [B0056 · 288–288](../../../../../src/runtime/session.cpp#L288) | Type/record definition: struct ReplayContext |  · [reviewed contract](#b0056) |
| [B0057 · 289–289](../../../../../src/runtime/session.cpp#L289) | Explanatory comments or spacing. |  |
| [B0058 · 290–292](../../../../../src/runtime/session.cpp#L290) | Callable definition: void journal_available() const | calls SessionJournalFailure · [reviewed contract](#b0058) |
| [B0059 · 293–296](../../../../../src/runtime/session.cpp#L293) | Callable definition: void require_recovery() noexcept | calls cancel · [reviewed contract](#b0059) |
| [B0060 · 297–301](../../../../../src/runtime/session.cpp#L297) | Callable definition: void journal_confirm() noexcept | calls state · [reviewed contract](#b0060) |
| [B0061 · 302–305](../../../../../src/runtime/session.cpp#L302) | Callable definition: void journal_append(std::string_view frame) | calls append, journal_confirm, require_recovery · [reviewed contract](#b0061) |
| [B0062 · 306–326](../../../../../src/runtime/session.cpp#L306) | Callable definition: void journal_input(const io::InputItemView& item) | calls journal_available, state, std::visit, constexpr; guard static_assert(std::is_same_v&lt;std::size_t,std::uint64_t&gt;); // Supported Linux64 ABI.; returns input.update.sequence; input.sequence; source comment (unverified): // Immutable reader/queue head is retained through retries/substeps. · [reviewed contract](#b0062) |
| [B0063 · 327–338](../../../../../src/runtime/session.cpp#L327) | Callable definition: void journal_decision() | calls journal_available, state, SessionJournalFailure, completes_command · [reviewed contract](#b0063) |
| [B0064 · 339–349](../../../../../src/runtime/session.cpp#L339) | Callable definition: void finish(bool discard) | calls journal_decision, has_value, sequence, publish · [reviewed contract](#b0064) |
| [B0065 · 350–367](../../../../../src/runtime/session.cpp#L350) | declares values/defaults or compile-time conditions. | source comment (unverified): // Reader borrows this owned stream. Reverse destruction preserves lifetime, · [reviewed contract](#b0065) |
| [B0066 · 368–379](../../../../../src/runtime/session.cpp#L368) | Type/record definition: struct Guard | guard require(std::this_thread::get_id()==data.writer,"session_wrong_thread","session operations belong t…; source comment (unverified): // Check immutable writer identity before accessing any mutable state. · [reviewed contract](#b0066) |
| [B0067 · 380–382](../../../../../src/runtime/session.cpp#L380) | Explanatory comments or spacing. | source comment (unverified): // Durable root selection can be uncertain after an I/O failure. Preserve · [reviewed contract](#b0067) |
| [B0068 · 383–395](../../../../../src/runtime/session.cpp#L383) | Type/record definition: struct SelectionGuard | source comment (unverified): // Durable root selection can be uncertain after an I/O failure. Preserve · [reviewed contract](#b0068) |
| [B0069 · 396–397](../../../../../src/runtime/session.cpp#L396) | Explanatory comments or spacing. | source comment (unverified): // Admission uses the original query cap and a finite metadata grant. No · [reviewed contract](#b0069) |
| [B0070 · 398–415](../../../../../src/runtime/session.cpp#L398) | Callable definition: static std::optional&lt;patterns::Declaration&gt; capture_patterns(const CompiledProgram& program, const std::optional&lt;UpdatePatternOpt… | calls require, bool, patterns::Failure, charge; guard require(bool(options-&gt;declaration),"invalid_update_pattern","update pattern declaration is empty");; returns {}; patterns::Declaration::copy_of(program.account(),options-&gt;declaration,remaining); growth copy_of; 1 loop sites; source comment (unverified): // Admission uses the original query cap and a finite metadata grant. No · [reviewed contract](#b0070) |
| [B0071 · 416–418](../../../../../src/runtime/session.cpp#L416) | Explanatory comments or spacing. | source comment (unverified): // Snapshot only committed counters and the actual owning tree. Copying the · [reviewed contract](#b0071) |
| [B0072 · 419–431](../../../../../src/runtime/session.cpp#L419) | Callable definition: \[\[nodiscard\]\] UpdatePatternStatus pattern_status() const | calls accepted_sequence, compiled_program, physical_sha256, std::copy; returns out; out; source comment (unverified): // Snapshot only committed counters and the actual owning tree. Copying the · [reviewed contract](#b0072) |
| [B0073 · 432–433](../../../../../src/runtime/session.cpp#L432) | Explanatory comments or spacing. | source comment (unverified): // Cheap nonwindow policy: reject every erase command, including set no-ops, · [reviewed contract](#b0073) |
| [B0074 · 434–439](../../../../../src/runtime/session.cpp#L434) | Callable definition: void check_pattern(const PhysicalUpdateView& update,PatternViolation& violation) const | calls find, pattern_detail::require; guard pattern_detail::require(!rule \|\| !rule-&gt;insertion_only,PatternViolationKind::erase_command,; source comment (unverified): // Cheap nonwindow policy: reject every erase command, including set no-ops, · [reviewed contract](#b0074) |
| [B0075 · 440–455](../../../../../src/runtime/session.cpp#L440) | Callable definition: Impl(DeltaRuntime value,std::unique_ptr&lt;std::istream&gt; stream,std::optional&lt;io::QueueLimits&gt; limits, SessionOptions options,resour… | calls snapshot_limits, input, std::move, window; growth emplace, make_accounted_shared · [reviewed contract](#b0075) |
| [B0076 · 456–505](../../../../../src/runtime/session.cpp#L456) | Callable definition: Impl(DeltaRuntime value,std::unique_ptr&lt;std::istream&gt; stream,const SessionCheckpoint& state,const SessionCheckpointLimits& limits… | calls control, committed_sequence, input_failed, end_of_input; guard check(runtime-&gt;sequence()==committed_sequence);; growth emplace, make_accounted_shared, make_accounted_unique · [reviewed contract](#b0076) |
| [B0077 · 506–506](../../../../../src/runtime/session.cpp#L506) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0077) |
| [B0078 · 507–514](../../../../../src/runtime/session.cpp#L507) | Callable definition: \[\[nodiscard\]\] std::shared_ptr&lt;const SessionRunContext&gt; replacement_context(const DeltaRuntime& target) const | calls require, matches, compiled_program, account; guard require(!previous.update_patterns \|\| previous.update_patterns-&gt;matches(target.compiled_program()),; returns resource::make_accounted_shared&lt;SessionRunContext&gt;({resource::MemoryOwnerKind::session,0},target.co…; growth make_accounted_shared · [reviewed contract](#b0078) |
| [B0079 · 515–520](../../../../../src/runtime/session.cpp#L515) | Callable definition: void install_reoptimization(reoptimization::detail::State& candidate,std::shared_ptr&lt;const SessionRunContext&gt; context, recovery::… | calls std::move, emplace, take_target, reset; growth emplace · [reviewed contract](#b0079) |
| [B0080 · 521–521](../../../../../src/runtime/session.cpp#L521) | Callable definition: ~Impl() | calls drop · [reviewed contract](#b0080) |
| [B0081 · 522–522](../../../../../src/runtime/session.cpp#L522) | Callable definition: bool has_private() const noexcept | calls has_value; returns pending.has_value() \|\| window_pending.has_value() · [reviewed contract](#b0081) |
| [B0082 · 523–530](../../../../../src/runtime/session.cpp#L523) | Callable definition: void admission_available() const | calls journal_available, require, frozen, has_value; guard require(control!=SessionState::dropped,"session_dropped","the query session has been dropped"); · [reviewed contract](#b0082) |
| [B0083 · 531–537](../../../../../src/runtime/session.cpp#L531) | Callable definition: void available(bool paused_ok=false) const | calls journal_available, require; guard require(control!=SessionState::dropped,"session_dropped","the query session has been dropped"); · [reviewed contract](#b0083) |
| [B0084 · 538–553](../../../../../src/runtime/session.cpp#L538) | Callable definition: SessionPhase phase() const noexcept | calls state, recovery_output_pending, delivery_pending; returns SessionPhase::paused_pending; SessionPhase::draining · [reviewed contract](#b0084) |
| [B0085 · 554–558](../../../../../src/runtime/session.cpp#L554) | Callable definition: std::uint64_t accepted_sequence() const | calls progress; returns reader-&gt;progress().sequence; queue-&gt;progress().sequence · [reviewed contract](#b0085) |
| [B0086 · 559–563](../../../../../src/runtime/session.cpp#L559) | Callable definition: io::InputProgress export_accepted() const | calls progress, export_value; returns reader-&gt;progress().export_value(); queue-&gt;progress().export_value() · [reviewed contract](#b0086) |
| [B0087 · 564–566](../../../../../src/runtime/session.cpp#L564) | Callable definition: void need_pending() const | calls require, has_private; guard require(has_private(),"session_no_pending_epoch","the query session has no private pending input"); · [reviewed contract](#b0087) |
| [B0088 · 567–571](../../../../../src/runtime/session.cpp#L567) | Callable definition: void abort() noexcept | calls rollback, reset, rollback_stage · [reviewed contract](#b0088) |
| [B0089 · 572–575](../../../../../src/runtime/session.cpp#L572) | Callable definition: void retain_report_metadata() noexcept | calls SessionReportMetadata, compiled_program, options, profile · [reviewed contract](#b0089) |
| [B0090 · 576–585](../../../../../src/runtime/session.cpp#L576) | Callable definition: void retain_observation() noexcept | calls retain_report_metadata, observations, last_cursor_observation · [reviewed contract](#b0090) |
| [B0091 · 586–598](../../../../../src/runtime/session.cpp#L586) | Callable definition: void publish(DeltaRuntime::Epoch epoch,std::uint64_t sequence,bool discard) noexcept | calls acknowledge, reset, committed, discard; growth emplace; source comment (unverified): // Source/window preparation reserved acknowledgement storage before engine · [reviewed contract](#b0091) |
| [B0092 · 599–610](../../../../../src/runtime/session.cpp#L599) | Callable definition: void acknowledge() noexcept | calls completes_command, publish, reset · [reviewed contract](#b0092) |
| [B0093 · 611–615](../../../../../src/runtime/session.cpp#L611) | Callable definition: bool admitted_input() const | calls records_read, progress, empty; returns reader?reader-&gt;records_read()&gt;reader-&gt;progress().sequence:queue && !queue-&gt;empty(); source comment (unverified): // A cached decoded stream row is already admitted, including after an · [reviewed contract](#b0093) |
| [B0094 · 616–619](../../../../../src/runtime/session.cpp#L616) | Callable definition: void prepare_update(const PhysicalUpdateView& update) | calls stage, emplace, begin_view; growth emplace · [reviewed contract](#b0094) |
| [B0095 · 620–666](../../../../../src/runtime/session.cpp#L620) | Callable definition: SessionBegin begin(bool replay=false,bool paused_ok=false) | calls available, require, has_private, delivery_pending; guard require(!has_private(),"session_pending_epoch","finish the private pending input before reading ano…; returns SessionBegin::would_block; SessionBegin::would_block; growth emplace · [reviewed contract](#b0095) |
| [B0096 · 667–682](../../../../../src/runtime/session.cpp#L667) | Callable definition: void stop() noexcept | calls abort, clear_recovered_output, cancel, discard · [reviewed contract](#b0096) |
| [B0097 · 683–691](../../../../../src/runtime/session.cpp#L683) | Callable definition: void drop() noexcept | calls stop, clear_recovered_output, reset · [reviewed contract](#b0097) |
| [B0098 · 692–693](../../../../../src/runtime/session.cpp#L692) | Closes surrounding scope/type. |  · [reviewed contract](#b0098) |
| [B0099 · 694–721](../../../../../src/runtime/session.cpp#L694) | Callable definition: void QuerySession::Impl::replay_frame(std::string_view frame,const recovery::journal::Scanned& after,void* context) | calls std::min, recovery::journal::inspect, recovery::ImageFailure, recovery::journal::decode; 1 loop sites; source comment (unverified): // decode inspection plus bounded body materialization · [reviewed contract](#b0099) |
| [B0100 · 722–722](../../../../../src/runtime/session.cpp#L722) | Explanatory comments or spacing. |  |
| [B0101 · 723–723](../../../../../src/runtime/session.cpp#L723) | Callable definition: QuerySession::QuerySession(resource::AccountedUnique&lt;Impl&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0101) |
| [B0102 · 724–724](../../../../../src/runtime/session.cpp#L724) | controls preprocessing. |  · [reviewed contract](#b0102) |
| [B0103 · 725–728](../../../../../src/runtime/session.cpp#L725) | Callable definition: std::optional&lt;RuntimeStorageWork&gt; RuntimeTestProbe::index_work(const QuerySession& session) | calls guard, index_work; returns d.runtime?index_work(*d.runtime):std::nullopt · [reviewed contract](#b0103) |
| [B0104 · 729–733](../../../../../src/runtime/session.cpp#L729) | Callable definition: void RuntimeTestProbe::seed_session_physical_sequence(QuerySession& runtime,std::uint64_t sequence) | calls guard, require, has_private, seed_delta_sequence; guard require(d.window && !d.has_private() && !d.output,"invalid_probe","sequence probe needs a ready win… · [reviewed contract](#b0104) |
| [B0105 · 734–734](../../../../../src/runtime/session.cpp#L734) | controls preprocessing. |  · [reviewed contract](#b0105) |
| [B0106 · 735–762](../../../../../src/runtime/session.cpp#L735) | Callable definition: QuerySession::Owner QuerySession::create_impl(PlanSource plan,const Database* initial,std::unique_ptr&lt;std::istream&gt; input, std::o… | calls require, empty, bool, std::visit; guard require(profile.format==io::InputFormat::jsonl && !profile.table && profile.delimiter==',' &&; returns initial?DeltaRuntime::initialize(std::move(source),*initial,options.delta,build):DeltaRuntime(std::…; growth allocate, insert, make_accounted_unique, new; 1 loop sites · [reviewed contract](#b0106) |
| [B0107 · 763–765](../../../../../src/runtime/session.cpp#L763) | Callable definition: QuerySession::Owner QuerySession::create(PhysicalPlan plan,std::unique_ptr&lt;std::istream&gt; input,SessionOptions options) | calls create_impl, std::move; returns create_impl(std::move(plan),nullptr,std::move(input),{},std::move(options),{},{}) · [reviewed contract](#b0107) |
| [B0108 · 766–769](../../../../../src/runtime/session.cpp#L766) | Callable definition: QuerySession::Owner QuerySession::create(PhysicalPlan plan,const Database& initial, std::unique_ptr&lt;std::istream&gt; input,SessionOp… | calls create_impl, std::move; returns create_impl(std::move(plan),&initial,std::move(input),{},std::move(options),{},build) · [reviewed contract](#b0108) |
| [B0109 · 770–772](../../../../../src/runtime/session.cpp#L770) | Callable definition: QuerySession::Owner QuerySession::create_typed(PhysicalPlan plan,io::QueueLimits limits,SessionOptions options) | calls create_impl, std::move; returns create_impl(std::move(plan),nullptr,{},limits,std::move(options),{},{}) · [reviewed contract](#b0109) |
| [B0110 · 773–776](../../../../../src/runtime/session.cpp#L773) | Callable definition: QuerySession::Owner QuerySession::create_typed(PhysicalPlan plan,const Database& initial, io::QueueLimits limits,SessionOptions o… | calls create_impl, std::move; returns create_impl(std::move(plan),&initial,{},limits,std::move(options),{},build) · [reviewed contract](#b0110) |
| [B0111 · 777–780](../../../../../src/runtime/session.cpp#L777) | Callable definition: QuerySession::Owner QuerySession::create_windowed(PhysicalPlan plan,WindowOptions window, io::QueueLimits limits,SessionOptions o… | calls create_impl, std::move; returns create_impl(std::move(plan),nullptr,{},limits,std::move(options),std::move(window),{}) · [reviewed contract](#b0111) |
| [B0112 · 781–784](../../../../../src/runtime/session.cpp#L781) | Callable definition: QuerySession::Owner QuerySession::create_windowed(PhysicalPlan plan,const Database& initial, WindowOptions window,io::QueueLimits… | calls create_impl, std::move; returns create_impl(std::move(plan),&initial,{},limits,std::move(options),std::move(window),build) · [reviewed contract](#b0112) |
| [B0113 · 785–787](../../../../../src/runtime/session.cpp#L785) | Callable definition: QuerySession::Owner QuerySession::create(CompiledProgram plan,std::unique_ptr&lt;std::istream&gt; input,SessionOptions options) | calls create_impl, std::move; returns create_impl(std::move(plan),nullptr,std::move(input),{},std::move(options),{},{}) · [reviewed contract](#b0113) |
| [B0114 · 788–791](../../../../../src/runtime/session.cpp#L788) | Callable definition: QuerySession::Owner QuerySession::create(CompiledProgram plan,const Database& initial, std::unique_ptr&lt;std::istream&gt; input,Sessio… | calls create_impl, std::move; returns create_impl(std::move(plan),&initial,std::move(input),{},std::move(options),{},build) · [reviewed contract](#b0114) |
| [B0115 · 792–794](../../../../../src/runtime/session.cpp#L792) | Callable definition: QuerySession::Owner QuerySession::create_typed(CompiledProgram plan,io::QueueLimits limits,SessionOptions options) | calls create_impl, std::move; returns create_impl(std::move(plan),nullptr,{},limits,std::move(options),{},{}) · [reviewed contract](#b0115) |
| [B0116 · 795–798](../../../../../src/runtime/session.cpp#L795) | Callable definition: QuerySession::Owner QuerySession::create_typed(CompiledProgram plan,const Database& initial, io::QueueLimits limits,SessionOption… | calls create_impl, std::move; returns create_impl(std::move(plan),&initial,{},limits,std::move(options),{},build) · [reviewed contract](#b0116) |
| [B0117 · 799–801](../../../../../src/runtime/session.cpp#L799) | Callable definition: QuerySession::Owner QuerySession::create_windowed(CompiledProgram plan,WindowOptions window,io::QueueLimits limits,SessionOptions… | calls create_impl, std::move; returns create_impl(std::move(plan),nullptr,{},limits,std::move(options),std::move(window),{}) · [reviewed contract](#b0117) |
| [B0118 · 802–805](../../../../../src/runtime/session.cpp#L802) | Callable definition: QuerySession::Owner QuerySession::create_windowed(CompiledProgram plan,const Database& initial, WindowOptions window,io::QueueLim… | calls create_impl, std::move; returns create_impl(std::move(plan),&initial,{},limits,std::move(options),std::move(window),build) · [reviewed contract](#b0118) |
| [B0119 · 806–810](../../../../../src/runtime/session.cpp#L806) | Callable definition: QuerySession::~QuerySession() | calls drop; source comment (unverified): // Exclusive lifetime is required. Keep Impl alive and reentrancy blocked · [reviewed contract](#b0119) |
| [B0120 · 811–825](../../../../../src/runtime/session.cpp#L811) | Callable definition: void QuerySession::enable_journal(std::string_view checkpoint_path,std::string_view journal_path,const SessionJournalOptions& opt… | calls guard, journal_available, SessionJournalFailure, checkpoint; growth emplace · [reviewed contract](#b0120) |
| [B0121 · 826–828](../../../../../src/runtime/session.cpp#L826) | Callable definition: SessionJournalState QuerySession::journal_state() const | calls guard; returns d.journal_confirmed · [reviewed contract](#b0121) |
| [B0122 · 829–832](../../../../../src/runtime/session.cpp#L829) | Callable definition: QuerySession::Owner QuerySession::restore_journal(CompiledProgram program,std::string_view checkpoint_path,std::string_view journ… | calls restore_journal_selected, std::move; returns restore_journal_selected(std::move(program),checkpoint_path,journal_path,requested,std::move(contin… · [reviewed contract](#b0122) |
| [B0123 · 833–836](../../../../../src/runtime/session.cpp#L833) | Callable definition: QuerySession::Owner QuerySession::restore_journal_with_local_sink(CompiledProgram program,std::string_view checkpoint_path,std::s… | calls restore_journal_selected, std::move; returns restore_journal_selected(std::move(program),checkpoint_path,journal_path,requested,std::move(contin… · [reviewed contract](#b0123) |
| [B0124 · 837–911](../../../../../src/runtime/session.cpp#L837) | Callable definition: QuerySession::Owner QuerySession::restore_journal_selected(CompiledProgram program,std::string_view checkpoint_path,std::string_v… | calls static_assert, require, checkpoint, value_or; guard static_assert(std::is_trivially_copy_constructible_v&lt;SessionJournalRecoveryOptions&gt;);; returns result; growth emplace; source comment (unverified): // Replay is still private. Repair either tail only after complete native, · [reviewed contract](#b0124) |
| [B0125 · 912–916](../../../../../src/runtime/session.cpp#L912) | Callable definition: SessionJournalRecoveryStatus QuerySession::recovery_status() const | calls guard, size, retained_bytes; returns status · [reviewed contract](#b0125) |
| [B0126 · 917–925](../../../../../src/runtime/session.cpp#L917) | Callable definition: std::optional&lt;RecoveredResult&gt; QuerySession::next_recovered_output() | calls guard, available, require, has_private; guard auto& d=*data_;Impl::Guard guard(d);d.available(true);require(!d.has_private(),"session_pending_epo…; returns {}; value · [reviewed contract](#b0126) |
| [B0127 · 926–926](../../../../../src/runtime/session.cpp#L926) | Callable definition: void QuerySession::discard_recovered_output() | calls guard, available, require, clear_recovered_output; guard void QuerySession::discard_recovered_output() {auto& d=*data_;Impl::Guard guard(d);d.available(true… · [reviewed contract](#b0127) |
| [B0128 · 927–927](../../../../../src/runtime/session.cpp#L927) | Explanatory comments or spacing. |  |
| [B0129 · 928–928](../../../../../src/runtime/session.cpp#L928) | Callable definition: void QuerySession::create_local_sink(std::string_view path,const SessionLocalSinkOptions& options) | calls local_sink_impl · [reviewed contract](#b0129) |
| [B0130 · 929–929](../../../../../src/runtime/session.cpp#L929) | Callable definition: void QuerySession::open_local_sink(std::string_view path,const SessionLocalSinkOptions& options) | calls local_sink_impl · [reviewed contract](#b0130) |
| [B0131 · 930–955](../../../../../src/runtime/session.cpp#L930) | Callable definition: void QuerySession::local_sink_impl(std::string_view path,const SessionLocalSinkOptions& requested,bool create) | calls guard, journal_available, require, has_private; guard require(d.journal && d.runtime && d.control!=SessionState::stopped && d.control!=SessionState::drop…; growth emplace · [reviewed contract](#b0131) |
| [B0132 · 956–961](../../../../../src/runtime/session.cpp#L956) | Callable definition: SessionLocalSinkState QuerySession::local_sink_state() const | calls guard, state, has_value; returns {}; {true,sink.failed \|\| !sink.file \|\| persisted.recovery_required,sink.replaying,sink.verified_seq… · [reviewed contract](#b0132) |
| [B0133 · 962–992](../../../../../src/runtime/session.cpp#L962) | Callable definition: LocalDelivery QuerySession::deliver_local_epoch() | calls guard, available, require, has_private; guard auto& d=*data_;Impl::Guard guard(d);d.available(true);require(d.local_sink && d.local_sink-&gt;file &&…; returns {}; {published?LocalDeliveryKind::published:LocalDeliveryKind::duplicate,generation,sequence,rows.s…; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0133) |
| [B0134 · 993–996](../../../../../src/runtime/session.cpp#L993) | Callable definition: recovery::sink::Epoch QuerySession::read_local_epoch(std::uint64_t sequence) | calls guard, available, require, read_epoch; guard auto& d=*data_;Impl::Guard guard(d);d.available(true);require(d.local_sink && d.local_sink-&gt;file &&…; returns d.local_sink-&gt;file-&gt;read_epoch(sequence) · [reviewed contract](#b0134) |
| [B0135 · 997–999](../../../../../src/runtime/session.cpp#L997) | Callable definition: recovery::sink::Receipt QuerySession::local_sink_receipt() const | calls guard, journal_available, require, delivery_pending; guard auto& d=*data_;Impl::Guard guard(d);d.journal_available();require(d.local_sink && d.local_sink-&gt;fil…; returns d.local_sink-&gt;file-&gt;receipt() · [reviewed contract](#b0135) |
| [B0136 · 1000–1000](../../../../../src/runtime/session.cpp#L1000) | Explanatory comments or spacing. |  |
| [B0137 · 1001–1028](../../../../../src/runtime/session.cpp#L1001) | Callable definition: void QuerySession::enable_generation(std::string_view root_path,const SessionGenerationOptions& requested) | calls guard, journal_available, SessionJournalFailure, checkpoint; growth emplace, make_accounted_unique · [reviewed contract](#b0137) |
| [B0138 · 1029–1053](../../../../../src/runtime/session.cpp#L1029) | Callable definition: void QuerySession::promote_journal(std::string_view root_path,const SessionGenerationOptions& requested) | calls guard, journal_available, require, failed; guard require(d.journal && !d.generation && d.runtime && d.control!=SessionState::stopped && d.control!=S…; growth emplace, make_accounted_unique · [reviewed contract](#b0138) |
| [B0139 · 1054–1087](../../../../../src/runtime/session.cpp#L1054) | Callable definition: void QuerySession::rotate_generation() | calls guard, journal_available, state, SessionJournalFailure; guard require(!d.local_sink \|\| d.local_sink-&gt;verified_prefix.has_value(),"local_sink_unverified","rotatio…; growth emplace, make_accounted_unique · [reviewed contract](#b0139) |
| [B0140 · 1088–1111](../../../../../src/runtime/session.cpp#L1088) | Callable definition: void QuerySession::retire_generation_history() | calls guard, journal_available, require, has_private; guard require(d.generation && d.journal && d.runtime && d.control!=SessionState::stopped && d.control!=Se… · [reviewed contract](#b0140) |
| [B0141 · 1112–1116](../../../../../src/runtime/session.cpp#L1112) | Callable definition: SessionGenerationState QuerySession::generation_state() const | calls guard, retirement, selected, operations; returns {}; {true,d.journal_confirmed.recovery_required,file.selected(),file.operations(),file.validation_w… · [reviewed contract](#b0141) |
| [B0142 · 1117–1120](../../../../../src/runtime/session.cpp#L1117) | Callable definition: QuerySession::Owner QuerySession::restore_generation(CompiledProgram program,std::string_view root_path, const SessionGenerationR… | calls restore_generation_impl, std::move; returns restore_generation_impl(std::move(program),root_path,requested,std::move(continuation),{},nullptr) · [reviewed contract](#b0142) |
| [B0143 · 1121–1124](../../../../../src/runtime/session.cpp#L1121) | Callable definition: QuerySession::Owner QuerySession::restore_generation_with_local_sink(CompiledProgram program,std::string_view root_path, const Se… | calls restore_generation_impl, std::move; returns restore_generation_impl(std::move(program),root_path,requested,std::move(continuation),sink_path,&s… · [reviewed contract](#b0143) |
| [B0144 · 1125–1155](../../../../../src/runtime/session.cpp#L1125) | Callable definition: QuerySession::Owner QuerySession::restore_generation_impl(CompiledProgram program,std::string_view root_path, const SessionGenera… | calls static_assert, SessionJournalFailure, owner, selected; guard static_assert(std::is_trivially_copy_constructible_v&lt;SessionGenerationRecoveryOptions&gt;);const auto …; returns result; growth make_accounted_unique; source comment (unverified): // v3 needs descriptor-aware admission and immutable sink-origin lineage. · [reviewed contract](#b0144) |
| [B0145 · 1156–1156](../../../../../src/runtime/session.cpp#L1156) | Explanatory comments or spacing. |  |
| [B0146 · 1157–1183](../../../../../src/runtime/session.cpp#L1157) | Callable definition: LockedGenerationRecovery::Owner QuerySession::lock_generation_recovery(CompiledProgram expected,std::string_view root_path, const… | calls require, bool, owner, selected; guard require(bool(expected) && options.retained_generations&gt;0,"generation_recovery_source","supply the e…; returns LockedGenerationRecovery::Owner(facade,resource::MemoryDelete&lt;LockedGenerationRecovery&gt;(allocator)); growth allocate, make_accounted_unique, new · [reviewed contract](#b0146) |
| [B0147 · 1184–1187](../../../../../src/runtime/session.cpp#L1184) | Callable definition: QuerySession::Owner QuerySession::restore_selected_generation(LockedGenerationRecovery::Owner input, const io::CompilerPlanArtifa… | calls restore_locked_generation, std::move; returns restore_locked_generation(std::move(input),artifact,std::move(continuation),{},nullptr) · [reviewed contract](#b0147) |
| [B0148 · 1188–1191](../../../../../src/runtime/session.cpp#L1188) | Callable definition: QuerySession::Owner QuerySession::restore_selected_generation_with_local_sink(LockedGenerationRecovery::Owner input, const io::Co… | calls restore_locked_generation, std::move; returns restore_locked_generation(std::move(input),artifact,std::move(continuation),sink_path,&sink_options) · [reviewed contract](#b0148) |
| [B0149 · 1192–1215](../../../../../src/runtime/session.cpp#L1192) | Callable definition: QuerySession::Owner QuerySession::restore_locked_generation(LockedGenerationRecovery::Owner input,const io::CompilerPlanArtifact&… | calls require, bool, program, selected; guard require(bool(input) && bool(artifact.program()),"generation_recovery_input","consume a live locked …; returns result; growth make_accounted_unique · [reviewed contract](#b0149) |
| [B0150 · 1216–1216](../../../../../src/runtime/session.cpp#L1216) | Explanatory comments or spacing. |  |
| [B0151 · 1217–1217](../../../../../src/runtime/session.cpp#L1217) | Callable definition: SessionCheckpoint QuerySession::checkpoint_state() const | calls checkpoint_state; returns checkpoint_state(SessionCheckpointLimits{}) · [reviewed contract](#b0151) |
| [B0152 · 1218–1254](../../../../../src/runtime/session.cpp#L1218) | Callable definition: SessionCheckpoint QuerySession::Impl::checkpoint(const SessionCheckpointLimits& limits,const DeltaRuntime* replacement) const | calls journal_available, require, has_value, has_private; guard require(d.runtime.has_value(),"session_dropped","a dropped session has no checkpoint state");; returns result · [reviewed contract](#b0152) |
| [B0153 · 1255–1257](../../../../../src/runtime/session.cpp#L1255) | Callable definition: SessionCheckpoint QuerySession::checkpoint_state(const SessionCheckpointLimits& limits) const | calls guard, checkpoint; returns d.checkpoint(limits) · [reviewed contract](#b0153) |
| [B0154 · 1258–1258](../../../../../src/runtime/session.cpp#L1258) | Callable definition: recovery::SessionImage QuerySession::checkpoint_image() const | calls checkpoint_image; returns checkpoint_image(SessionCheckpointLimits{},recovery::SessionImageLimits{}) · [reviewed contract](#b0154) |
| [B0155 · 1259–1262](../../../../../src/runtime/session.cpp#L1259) | Callable definition: recovery::SessionImage QuerySession::checkpoint_image(const SessionCheckpointLimits& native,const recovery::SessionImageLimits& l… | calls guard, checkpoint, recovery::encode_session_image, compiled_program; returns recovery::encode_session_image(d.runtime-&gt;compiled_program().account(),state,native,limits) · [reviewed contract](#b0155) |
| [B0156 · 1263–1265](../../../../../src/runtime/session.cpp#L1263) | Callable definition: QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,std::unique_ptr&lt;std::istream&gt; cont… | calls restore_image, std::move; returns restore_image(std::move(program),bytes,SessionRestoreOptions{},recovery::SessionImageLimits{},std::… · [reviewed contract](#b0156) |
| [B0157 · 1266–1269](../../../../../src/runtime/session.cpp#L1266) | Callable definition: QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,const SessionRestoreOptions& optio… | calls restore_image, std::move; returns restore_image(std::move(program),bytes,options,recovery::SessionImageLimits{},std::move(continuatio… · [reviewed contract](#b0157) |
| [B0158 · 1270–1280](../../../../../src/runtime/session.cpp#L1270) | Callable definition: QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,const SessionRestoreOptions& optio… | calls recovery::detail::validate_session_image, bool, recovery::ImageFailure, value_or; returns restore_funded(std::move(program),decoded.state,options,std::move(continuation),context,decoded.run… · [reviewed contract](#b0158) |
| [B0159 · 1281–1284](../../../../../src/runtime/session.cpp#L1281) | Callable definition: QuerySession::Owner QuerySession::restore_state(CompiledProgram program,const SessionCheckpoint& state, std::unique_ptr&lt;std::istr… | calls restore_state, std::move; returns restore_state(std::move(program),state,SessionRestoreOptions{},std::move(continuation)) · [reviewed contract](#b0159) |
| [B0160 · 1285–1287](../../../../../src/runtime/session.cpp#L1285) | Callable definition: recovery::PublishedCheckpoint QuerySession::checkpoint_file(std::string_view path) const | calls checkpoint_file; returns checkpoint_file(path,SessionCheckpointLimits{},recovery::CheckpointFileLimits{}) · [reviewed contract](#b0160) |
| [B0161 · 1288–1294](../../../../../src/runtime/session.cpp#L1288) | Callable definition: recovery::PublishedCheckpoint QuerySession::checkpoint_file(std::string_view path,const SessionCheckpointLimits& native, const re… | calls guard, SessionJournalFailure, checkpoint, recovery::encode_session_image; returns recovery::publish_session_image(path,image,native,limits) · [reviewed contract](#b0161) |
| [B0162 · 1295–1297](../../../../../src/runtime/session.cpp#L1295) | Callable definition: QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,std::unique_ptr&lt;std::istream&gt; contin… | calls restore_file, std::move; returns restore_file(std::move(program),path,SessionRestoreOptions{},recovery::CheckpointFileLimits{},std::… · [reviewed contract](#b0162) |
| [B0163 · 1298–1301](../../../../../src/runtime/session.cpp#L1298) | Callable definition: QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,const SessionRestoreOptions& options… | calls restore_file, std::move; returns restore_file(std::move(program),path,options,recovery::CheckpointFileLimits{},std::move(continuatio… · [reviewed contract](#b0163) |
| [B0164 · 1302–1313](../../../../../src/runtime/session.cpp#L1302) | Callable definition: QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,const SessionRestoreOptions& options… | calls reader, value_or, memory_limit_bytes, detail::new_storage_context; returns restore_funded(std::move(program),decoded.state,options,std::move(continuation),context,decoded.run… · [reviewed contract](#b0164) |
| [B0165 · 1314–1318](../../../../../src/runtime/session.cpp#L1314) | Callable definition: QuerySession::Owner QuerySession::restore_state(CompiledProgram program,const SessionCheckpoint& state, const SessionRestoreOptio… | calls restore_funded, std::move, data, size; returns restore_funded(std::move(program),state,options,std::move(continuation),{},{encoded.data(),encoded.… · [reviewed contract](#b0165) |
| [B0166 · 1319–1377](../../../../../src/runtime/session.cpp#L1319) | Callable definition: QuerySession::Owner QuerySession::restore_funded(CompiledProgram program,const SessionCheckpoint& state, const SessionRestoreOpti… | calls recovery::ImageFailure, check, matches, bool; guard check(state.version==(state.update_patterns?SessionCheckpoint::current_version:SessionCheckpoint::l…; returns Owner(facade,resource::MemoryDelete&lt;QuerySession&gt;(allocator)); growth allocate, insert, make_accounted_unique, new; source comment (unverified): // Session-owned reader record ordinals start at zero. No unacknowledged · [reviewed contract](#b0166) |
| [B0167 · 1378–1386](../../../../../src/runtime/session.cpp#L1378) | Callable definition: SessionStatus QuerySession::status() const | calls guard, phase, failed, sequence; returns {d.control,d.phase(),d.committed_sequence,d.input_failed \|\| (d.reader && d.reader-&gt;failed()) \|\| (d.… · [reviewed contract](#b0167) |
| [B0168 · 1387–1391](../../../../../src/runtime/session.cpp#L1387) | Callable definition: UpdatePatternStatus QuerySession::update_pattern_status() const | calls guard, require, has_value, pattern_status; guard require(d.runtime.has_value(),"session_dropped","a dropped session has no active monitor");; returns d.pattern_status() · [reviewed contract](#b0168) |
| [B0169 · 1392–1395](../../../../../src/runtime/session.cpp#L1392) | Callable definition: io::InputProgress QuerySession::progress() const | calls guard, require, export_accepted; guard require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped"); r…; returns d.export_accepted() · [reviewed contract](#b0169) |
| [B0170 · 1396–1398](../../../../../src/runtime/session.cpp#L1396) | Callable definition: void QuerySession::begin_reoptimization(const planner::MinimumHeightCandidate& candidate,reoptimization::Options options) | calls begin_reoptimization_with_cost, std::move · [reviewed contract](#b0170) |
| [B0171 · 1399–1411](../../../../../src/runtime/session.cpp#L1399) | Callable definition: void QuerySession::begin_reoptimization_with_cost(const planner::MinimumHeightCandidate& candidate,reoptimization::Options option… | calls guard, available, require, active; guard require(!d.reoptimization \|\| !d.reoptimization-&gt;active(),"reoptimization_active","cancel the active…; growth make_accounted_unique · [reviewed contract](#b0171) |
| [B0172 · 1412–1416](../../../../../src/runtime/session.cpp#L1412) | Callable definition: void QuerySession::request_reoptimization_barrier() | calls guard, available, require, active; guard require(d.reoptimization && d.reoptimization-&gt;active(),"reoptimization_inactive","prepare a candida… · [reviewed contract](#b0172) |
| [B0173 · 1417–1450](../../../../../src/runtime/session.cpp#L1417) | Callable definition: reoptimization::Status QuerySession::advance_reoptimization(std::uint64_t quantum) | calls guard, available, active, verified; returns {}; candidate.status(); 1 loop sites; source comment (unverified): // Keep the existing checkpoint's empty-queue and complete-command guards. · [reviewed contract](#b0173) |
| [B0174 · 1451–1455](../../../../../src/runtime/session.cpp#L1451) | Callable definition: void QuerySession::cancel_reoptimization() | calls guard, journal_available, cancel · [reviewed contract](#b0174) |
| [B0175 · 1456–1458](../../../../../src/runtime/session.cpp#L1456) | Callable definition: reoptimization::Status QuerySession::reoptimization_status() const | calls guard, status; returns d.reoptimization?d.reoptimization-&gt;status():reoptimization::Status{} · [reviewed contract](#b0175) |
| [B0176 · 1459–1511](../../../../../src/runtime/session.cpp#L1459) | Callable definition: reoptimization::Status QuerySession::publish_reoptimization(const io::CompilerPlanArtifact& artifact,reoptimization::PublicationO… | calls guard, available, require, verified; guard require(d.reoptimization && d.reoptimization-&gt;verified(),"reoptimization_not_verified","verify the …; returns candidate.status(); growth make_accounted_unique · [reviewed contract](#b0176) |
| [B0177 · 1512–1518](../../../../../src/runtime/session.cpp#L1512) | Callable definition: void QuerySession::start() | calls guard, require, state, resume; guard require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped"); · [reviewed contract](#b0177) |
| [B0178 · 1519–1526](../../../../../src/runtime/session.cpp#L1519) | Callable definition: void QuerySession::pause() | calls guard, available, state, pause; source comment (unverified): // Draining/prepared/output do not have a D06 pause state. Admission and · [reviewed contract](#b0178) |
| [B0179 · 1527–1529](../../../../../src/runtime/session.cpp#L1527) | Callable definition: io::Admission QuerySession::enqueue(io::TransportBatch& batch) | calls guard, admission_available, enqueue; returns d.queue-&gt;enqueue(batch) · [reviewed contract](#b0179) |
| [B0180 · 1530–1532](../../../../../src/runtime/session.cpp#L1530) | Callable definition: void QuerySession::finish_input() | calls guard, admission_available, finish · [reviewed contract](#b0180) |
| [B0181 · 1533–1535](../../../../../src/runtime/session.cpp#L1533) | Callable definition: SessionBegin QuerySession::begin_next_result() | calls guard, begin; returns d.begin() · [reviewed contract](#b0181) |
| [B0182 · 1536–1541](../../../../../src/runtime/session.cpp#L1536) | Callable definition: bool QuerySession::begin_next() | calls guard, begin, require; guard require(result!=SessionBegin::would_block,"input_would_block","input is temporarily blocked by an e…; returns result==SessionBegin::pending · [reviewed contract](#b0182) |
| [B0183 · 1542–1546](../../../../../src/runtime/session.cpp#L1542) | Callable definition: DeltaStep QuerySession::step() | calls guard, available, need_pending, step; returns DeltaStep::prepared; d.pending-&gt;step() · [reviewed contract](#b0183) |
| [B0184 · 1547–1555](../../../../../src/runtime/session.cpp#L1547) | Callable definition: void QuerySession::commit() | calls guard, available, need_pending, require; guard require(d.metadata_ready,"session_epoch_not_prepared","finish private preparation before committing… · [reviewed contract](#b0184) |
| [B0185 · 1556–1561](../../../../../src/runtime/session.cpp#L1556) | Callable definition: void QuerySession::start_drain() | calls guard, available, need_pending, require; guard require(!d.local_sink,"local_sink_attached","attached local output must be retained or cancelled by… · [reviewed contract](#b0185) |
| [B0186 · 1562–1575](../../../../../src/runtime/session.cpp#L1562) | Callable definition: void QuerySession::drain() | calls guard, available, require, sequence; guard require(!d.local_sink,"local_sink_attached","attached local output must be delivered or cancelled b… · [reviewed contract](#b0186) |
| [B0187 · 1576–1583](../../../../../src/runtime/session.cpp#L1576) | Callable definition: std::optional&lt;SignedResult&gt; QuerySession::next_output() | calls guard, available, require, has_private; guard require(!d.local_sink,"local_sink_attached","deliver whole epochs through the attached local sink");; returns {}; row · [reviewed contract](#b0187) |
| [B0188 · 1584–1617](../../../../../src/runtime/session.cpp#L1584) | Callable definition: SessionSnapshot QuerySession::snapshot(std::optional&lt;SnapshotLimits&gt; limits) const | calls guard, journal_available, require, has_private; guard require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped");; returns result; growth reserve; 1 loop sites · [reviewed contract](#b0188) |
| [B0189 · 1618–1624](../../../../../src/runtime/session.cpp#L1618) | Callable definition: std::optional&lt;WindowCanonicalState&gt; QuerySession::window_state() const | calls guard, require, has_private, canonical_state; guard require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped");; returns std::nullopt; d.window-&gt;canonical_state() · [reviewed contract](#b0189) |
| [B0190 · 1625–1625](../../../../../src/runtime/session.cpp#L1625) | Callable definition: void QuerySession::stop() | calls guard, stop · [reviewed contract](#b0190) |
| [B0191 · 1626–1626](../../../../../src/runtime/session.cpp#L1626) | Callable definition: void QuerySession::drop() | calls guard, drop · [reviewed contract](#b0191) |
| [B0192 · 1627–1629](../../../../../src/runtime/session.cpp#L1627) | Callable definition: std::shared_ptr&lt;const SessionRunContext&gt; QuerySession::run_context() const | calls guard; returns d.run_context · [reviewed contract](#b0192) |
| [B0193 · 1630–1636](../../../../../src/runtime/session.cpp#L1630) | Callable definition: SessionReportMetadata QuerySession::report_metadata() const | calls guard, SessionReportMetadata, compiled_program, options; returns SessionReportMetadata(d.runtime-&gt;compiled_program(),d.runtime-&gt;options(),; SessionReportMetadata(sa… · [reviewed contract](#b0193) |
| [B0194 · 1637–1641](../../../../../src/runtime/session.cpp#L1637) | Callable definition: std::optional&lt;CommittedStateGauges&gt; QuerySession::report_gauges() const | calls guard, has_private, committed_state_gauges; returns {}; d.runtime-&gt;committed_state_gauges() · [reviewed contract](#b0194) |
| [B0195 · 1642–1646](../../../../../src/runtime/session.cpp#L1642) | Callable definition: std::optional&lt;CapturedStateGauges&gt; QuerySession::capture_state_gauges() const | calls guard, has_private, capture_state_gauges; returns {}; d.runtime-&gt;capture_state_gauges() · [reviewed contract](#b0195) |
| [B0196 · 1647–1650](../../../../../src/runtime/session.cpp#L1647) | Callable definition: std::optional&lt;CursorObservation&gt; QuerySession::last_cursor_observation() const | calls guard, last_cursor_observation; returns d.runtime?d.runtime-&gt;last_cursor_observation():d.retained_cursor_observation · [reviewed contract](#b0196) |
| [B0197 · 1651–1654](../../../../../src/runtime/session.cpp#L1651) | Callable definition: std::optional&lt;resource::MemoryStatistics&gt; QuerySession::accounted_memory_statistics() const | calls guard, accounted_memory_statistics; returns d.runtime?std::optional{d.runtime-&gt;accounted_memory_statistics()}:std::nullopt · [reviewed contract](#b0197) |
| [B0198 · 1655–1661](../../../../../src/runtime/session.cpp#L1655) | Callable definition: ObservationSnapshot QuerySession::observations() const | calls guard, observations; returns result · [reviewed contract](#b0198) |
| [B0199 · 1662–1671](../../../../../src/runtime/session.cpp#L1662) | Callable definition: ObservationTrace QuerySession::observation_trace() const | calls guard, observation_trace; returns result; source comment (unverified): // Drop releases trace payload; summaries still share immutable program and · [reviewed contract](#b0199) |
| [B0200 · 1672–1679](../../../../../src/runtime/session.cpp#L1672) | Callable definition: CapturedObservationTrace QuerySession::capture_observation_trace() const | calls guard, compiled_program, account, plan; returns result · [reviewed contract](#b0200) |
| [B0201 · 1680–1682](../../../../../src/runtime/session.cpp#L1680) | declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0201) |
| [B0202 · 1683–1689](../../../../../src/runtime/session.cpp#L1683) | Callable definition: void QuerySession::configure_workload_statistics(const workload::Options& options) | calls guard, require, has_value, has_private; guard require(d.runtime.has_value(),"session_dropped","statistics owner has been released"); · [reviewed contract](#b0202) |
| [B0203 · 1690–1695](../../../../../src/runtime/session.cpp#L1690) | Callable definition: void QuerySession::reset_workload_statistics() | calls guard, require, has_value, has_private; guard require(d.runtime.has_value(),"session_dropped","statistics owner has been released"); · [reviewed contract](#b0203) |
| [B0204 · 1696–1699](../../../../../src/runtime/session.cpp#L1696) | Callable definition: workload::Options QuerySession::workload_statistics_options() const | calls guard, workload_statistics_options; returns d.runtime?d.runtime-&gt;workload_statistics_options():d.retained_workload_options · [reviewed contract](#b0204) |
| [B0205 · 1700–1705](../../../../../src/runtime/session.cpp#L1700) | Callable definition: std::optional&lt;workload::Snapshot&gt; QuerySession::workload_statistics() const | calls guard, workload_statistics, has_private, with_pending; returns {}; d.has_private()?result.with_pending():std::move(result) · [reviewed contract](#b0205) |
| [B0206 · 1706–1708](../../../../../src/runtime/session.cpp#L1706) | declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0206) |
| [B0207 · 1709–1713](../../../../../src/runtime/session.cpp#L1709) | Callable definition: std::optional&lt;statistics::OwnerCapture&gt; QuerySession::capture_statistics(const statistics::OwnerRequest& request,statistics::Limi… | calls guard, has_private, owner, sequence; returns {}; pending.finish() · [reviewed contract](#b0207) |
| [B0208 · 1714–1717](../../../../../src/runtime/session.cpp#L1714) | Callable definition: std::optional&lt;statistics::Freshness&gt; QuerySession::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t ma… | calls guard, statistics_freshness; returns {}; d.runtime-&gt;statistics_freshness(captured,max_event_lag) · [reviewed contract](#b0208) |
| [B0209 · 1718–1724](../../../../../src/runtime/session.cpp#L1718) | Callable definition: std::optional&lt;statistics::CombinedCapture&gt; QuerySession::capture_combined_statistics(const statistics::OwnerRequest& request,stat… | calls guard, has_private, capture_combined_statistics, owner; returns {}; d.runtime-&gt;capture_combined_statistics(request,limits) · [reviewed contract](#b0209) |
| [B0210 · 1725–1729](../../../../../src/runtime/session.cpp#L1725) | Callable definition: SessionStatisticsContext QuerySession::capture_statistics_context( const std::optional&lt;statistics::OwnerRequest&gt;& selections,stat… | calls emplace, capture_statistics_context_view; returns capture_statistics_context_view(view,limits); growth emplace · [reviewed contract](#b0210) |
| [B0211 · 1730–1758](../../../../../src/runtime/session.cpp#L1730) | Callable definition: SessionStatisticsContext QuerySession::capture_statistics_context_view( const std::optional&lt;statistics::OwnerRequestView&gt;& select… | calls guard, SessionReportMetadata, compiled_program, options; returns SessionStatisticsContext(resource::make_accounted_shared&lt;SessionStatisticsContext::Data&gt;(; growth make_accounted_shared · [reviewed contract](#b0211) |
| [B0212 · 1759–1761](../../../../../src/runtime/session.cpp#L1759) | declares namespace scope. |  · [reviewed contract](#b0212) |
| [B0213 · 1762–1775](../../../../../src/runtime/session.cpp#L1762) | Callable definition: Attempt Access::capture(const QuerySession& owner,Limits limits) noexcept | calls attempt, guard, compiled_program, plan; returns attempt(\[&\](Usage& usage) {; builder.finish() · [reviewed contract](#b0213) |
| [B0214 · 1776–1776](../../../../../src/runtime/session.cpp#L1776) | Closes surrounding scope/type. |  · [reviewed contract](#b0214) |

## B0001

[Lines 1–34](../../../../../src/runtime/session.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/session.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the private session lifecycle, durable storage and diagnostic dependencies. |
| inputs / outputs | Public session types plus internal replay, storage-work, memory-report, owner-statistics and reoptimization helpers. |
| invariants | This translation unit coordinates existing native kernels; imports and namespace scopes do not establish a paper theorem. |
| ownership | Compile-time declarations; includes retain no per-session storage. |
| failure | Missing or incompatible declarations fail compilation. |
| cost | No runtime work for preprocessing/declarations. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 35–37](../../../../../src/runtime/session.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,std::string_view code,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a public session precondition with its existing code/message. |
| inputs / outputs | Boolean plus borrowed diagnostic strings; returns on success or throws owning Error. |
| invariants | Does not catch, retry, roll back or convert failed state to success. |
| ownership | Error copies code/message only on the failing path. |
| failure | Error construction may allocate and can itself fail; callers preserve their own state boundaries. |
| cost | One branch on success; string and exception construction on failure. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 38–41](../../../../../src/runtime/session.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t add(std::size_t left,std::size_t right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add snapshot sizes without host-size overflow. |
| inputs / outputs | Two size_t counts produce their checked sum. |
| invariants | The subtraction check precedes addition and rejects overflow as resource_limit. |
| ownership | Scalar arguments/results only. |
| failure | require may throw; no snapshot state has changed. |
| cost | Fixed arithmetic and one precondition check. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 42–47](../../../../../src/runtime/session.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t payload(const storage::Tuple& tuple) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual retained native tuple requests for snapshot payload accounting. |
| inputs / outputs | An accounted Tuple yields its requested bytes as size_t. |
| invariants | Unaccounted tuples and bytes unrepresentable by size_t reject; this is neither row width nor process RSS. |
| ownership | Borrows the tuple and reads its existing allocation metadata. |
| failure | require reports runtime_contract/resource_limit; no tuple is changed. |
| cost | Constant reads of stored Tuple payload usage and scalar bounds; no traversal/copy of field bytes. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 48–55](../../../../../src/runtime/session.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::PendingEpoch>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check nonthrowing moves required by publication and cleanup. |
| inputs / outputs | Static traits for pending/committed epochs, signed rows, progress and snapshots. |
| invariants | These exact moves cannot introduce allocation failure after native publication. |
| ownership | Compile-time checks only. |
| failure | A member change that violates a checked move property fails compilation. |
| cost | Zero runtime work. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 56–62](../../../../../src/runtime/session.cpp#L56); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionRows::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the immutable snapshot row directory and its control-allocation usage. |
| inputs / outputs | A receiving account creates an empty allocator-aware vector; control_usage is filled by prepare. |
| invariants | Directory storage is output_buffer attributed to output:0; each tuple carries its own accounted payload. |
| ownership | Data is shared by SessionRows copies; its vector uses the original MemoryAllocator. |
| failure | Empty vector construction does not allocate nested storage; later capacity and control allocation can fail. |
| cost | Fixed empty setup; retained directory capacity and tuple payloads are separately charged. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 63–63](../../../../../src/runtime/session.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t SessionRows::size() const noexcept {return data_?data_->values.size():0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read immutable snapshot row count. |
| inputs / outputs | Returns values.size(), or zero for an unprepared collection. |
| invariants | An empty/unprepared handle has zero size. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 64–64](../../../../../src/runtime/session.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t SessionRows::capacity() const noexcept {return data_?data_->values.capacity():0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained snapshot directory capacity. |
| inputs / outputs | Returns values.capacity(), or zero before prepare. |
| invariants | Spare capacity remains retained query-account storage. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 65–65](../../../../../src/runtime/session.cpp#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::Tuple* SessionRows::data() const noexcept {return data_?data_->values.data():nullptr;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable snapshot directory. |
| inputs / outputs | Returns its data pointer, or nullptr before prepare. |
| invariants | Only positions below size are readable; owner lifetime bounds the borrow. |
| ownership | Pointer does not independently retain Data or tuple payloads. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 66–69](../../../../../src/runtime/session.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::Tuple& SessionRows::at(std::size_t i) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one snapshot row with range checking. |
| inputs / outputs | Index i returns const Tuple& when i&lt;size. |
| invariants | No null/empty vector is dereferenced for an out-of-range request. |
| ownership | Reference borrows the immutable collection. |
| failure | Throws std::out_of_range for invalid i; no collection mutation. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 70–70](../../../../../src/runtime/session.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage SessionRows::owner_usage() const noexcept {return data_?data_->control_usage:resource::MemoryUsage{};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read snapshot shared-object/control allocation usage. |
| inputs / outputs | Returns stored control_usage, or all-zero usage before prepare. |
| invariants | Excludes vector capacity and row payload allocations. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 71–78](../../../../../src/runtime/session.cpp#L71); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryUsage SessionRows::memory_usage() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute current collection/control and directory-capacity requests. |
| inputs / outputs | Returns control usage plus allocator allocation_usage(data,capacity). |
| invariants | Row payloads are excluded here and added by snapshot; spare vector capacity is included. |
| ownership | Reads existing allocations without creating another owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Fixed control/allocator metadata lookup; no result-row scan. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 79–92](../../../../../src/runtime/session.cpp#L79); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SessionRows::prepare() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund a private snapshot collection once and prohibit mutation after sharing. |
| inputs / outputs | An unprepared SessionRows receives an accounted shared Data; an existing unique Data is reused. |
| invariants | Existing use_count must be one. Account current differences describe only Data/control because its empty vector allocates nothing nested. |
| ownership | The new Data/control belongs to the original account and is published to data_ only after construction succeeds. |
| failure | Shared-collection mutation rejects; allocation failure leaves data_ unchanged. No catch or copy-on-write layer is added. |
| cost | One control allocation on first use, scalar account reads thereafter; no tuple scan. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 93–93](../../../../../src/runtime/session.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SessionRows::reserve(std::size_t capacity) {prepare();data_->values.reserve(capacity);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve private snapshot directory capacity. |
| inputs / outputs | Requested capacity first prepares Data, then calls its vector.reserve. |
| invariants | Only the private uniquely held collection may grow; requested capacity is not a new memory allowance. |
| ownership | The original account funds the new directory; temporary old/new capacities can coexist. |
| failure | prepare/reserve failure propagates; vector strong guarantee preserves prior rows. |
| cost | May allocate capacity and move existing Tuple owners; amortization/growth is chosen by snapshot. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 94–99](../../../../../src/runtime/session.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SessionRows::append(storage::Tuple tuple) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one original-account tuple to the private snapshot collection. |
| inputs / outputs | Owning Tuple argument is moved into values after private preparation and account-identity validation. |
| invariants | Unaccounted/foreign payload cannot enter the collection; tuple account ownership is exact, not a byte-count estimate. |
| ownership | Moves native tuple ownership; on rejection the local argument releases its payload. |
| failure | Validation/allocation errors propagate with prior rows unchanged; an empty Data may already have been prepared. |
| cost | Fixed account/ownership checks plus vector growth/moves if required; no deep row export. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 101–109](../../../../../src/runtime/session.cpp#L101); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionStatisticsContext::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one coherent captured session diagnostic context. |
| inputs / outputs | Metadata, fixed status, native trace, optional combined statistics, options, cursor observation and requested flag. |
| invariants | Private pending state is represented by diagnostic availability; no captured value exposes a pending token. |
| ownership | The shared Data retains accounted trace/statistics and immutable program metadata independently of the session. |
| failure | Capture factory funds construction before publishing the context; failed construction unwinds its owning fields. |
| cost | Field moves plus one shared control; trace/statistics capture costs are charged by the factory. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0018

[Lines 110–110](../../../../../src/runtime/session.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SessionReportMetadata& SessionStatisticsContext::metadata() const noexcept{return data_->metadata;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the captured immutable session metadata. |
| inputs / outputs | Returns const reference to Data.metadata. |
| invariants | Captures are immutable; later session progress/reset/drop does not update this value. |
| ownership | Reference borrows the context; copies and custom move operations retain the same shared Data. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0019

[Lines 111–111](../../../../../src/runtime/session.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SessionStatus& SessionStatisticsContext::status() const noexcept{return data_->status;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the fixed captured session status. |
| inputs / outputs | Returns const reference to Data.status. |
| invariants | Captures are immutable; later session progress/reset/drop does not update this value. |
| ownership | Reference borrows the context; copies and custom move operations retain the same shared Data. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0020

[Lines 112–112](../../../../../src/runtime/session.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CapturedObservationTrace& SessionStatisticsContext::trace() const noexcept{return data_->trace;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the captured native observation trace. |
| inputs / outputs | Returns const reference to Data.trace. |
| invariants | Captures are immutable; later session progress/reset/drop does not update this value. |
| ownership | Reference borrows the context; copies and custom move operations retain the same shared Data. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0021

[Lines 113–113](../../../../../src/runtime/session.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<statistics::CombinedCapture>& SessionStatisticsContext::combined() const noexcept{return data_->combined;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional captured state/workload pair. |
| inputs / outputs | Returns const reference to Data.combined. |
| invariants | Captures are immutable; later session progress/reset/drop does not update this value. |
| ownership | Reference borrows the context; copies and custom move operations retain the same shared Data. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0022

[Lines 114–114](../../../../../src/runtime/session.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const workload::Options& SessionStatisticsContext::workload_options() const noexcept{return data_->options;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow captured workload configuration. |
| inputs / outputs | Returns const reference to Data.options. |
| invariants | Captures are immutable; later session progress/reset/drop does not update this value. |
| ownership | Reference borrows the context; copies and custom move operations retain the same shared Data. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0023

[Lines 115–115](../../../../../src/runtime/session.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<CursorObservation>& SessionStatisticsContext::cursor() const noexcept{return data_->cursor;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional last-cursor report. |
| inputs / outputs | Returns const reference to Data.cursor. |
| invariants | Captures are immutable; later session progress/reset/drop does not update this value. |
| ownership | Reference borrows the context; copies and custom move operations retain the same shared Data. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0024

[Lines 116–116](../../../../../src/runtime/session.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SessionStatisticsContext::state_requested() const noexcept{return data_->requested;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read whether state selections were explicitly requested. |
| inputs / outputs | Returns the captured requested Boolean. |
| invariants | An omitted selection request remains distinguishable from an explicitly empty request. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0025

[Lines 117–118](../../../../../src/runtime/session.cpp#L117); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L117-L118:sha256:f4f8121dd2388b30f27a1454c1f3bd3ed0db6b42a9f01bb0e4cc53e5a048e339
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/session.cpp: opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0026

[Lines 119–127](../../../../../src/runtime/session.cpp#L119); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ManagedPlan {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a validated selected-plan descriptor and locate its embedded artifact. |
| inputs / outputs | Owning encoded bytes, PlanSelection and artifact_size yield borrowed descriptor/artifact views. |
| invariants | artifact() assumes a validated encoding: artifact_size bytes immediately precede the final 64-byte checksum. It does not parse arbitrary bytes. |
| ownership | ManagedPlan owns account-funded bytes and scalar selection; views borrow that owner. |
| failure | Valid construction provenance is required; no unchecked caller bytes enter this private record. |
| cost | Owner moves and constant subspan arithmetic; descriptor validation/encoding is paid upstream. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0027

[Lines 128–130](../../../../../src/runtime/session.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool logical_binding(const recovery::ImageBinding& a,const recovery::ImageBinding& b) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare source/catalog/policy compatibility independent of a physical tree. |
| inputs / outputs | Two ImageBindings return equality of source_sha256, catalog_version and policy. |
| invariants | Intentionally omits physical_sha256; exact physical binding is checked separately where required. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Fixed-size hash/enum comparisons. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0028

[Lines 131–131](../../../../../src/runtime/session.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t N> std::string_view view(const std::array<char,N>& value) noexcept {return {value.data(),value.size()};}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow every byte of a fixed array. |
| inputs / outputs | array&lt;char,N&gt; becomes string_view of length N, without NUL trimming. |
| invariants | The view is raw exact bytes and requires the array lifetime. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0029

[Lines 132–134](../../../../../src/runtime/session.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generation_binding(bool condition) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a generation binding mismatch using a fixed native failure. |
| inputs / outputs | Boolean; false throws GenerationFailure(binding,state,unchanged). |
| invariants | This helper has performed no root publication; unchanged describes this check, not earlier arbitrary I/O. |
| ownership | Fixed exception payload; no string copy. |
| failure | Propagates the fixed failure without retry or state repair. |
| cost | One branch; no query allocation. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0030

[Lines 135–139](../../../../../src/runtime/session.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::array<char,64> result_schema(const resource::MemoryAccount& account,const DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the exact ordered result scalar schema for a plan switch. |
| inputs / outputs | Runtime result-layout field types produce a fixed 64-byte sink schema hash. |
| invariants | Order and full ScalarType matter; logical source compatibility alone cannot authorize a changed output schema. |
| ownership | A temporary ImageVector uses the supplied original/target account and releases after hashing. |
| failure | Reservation/hash/limit errors propagate before root selection. |
| cost | O(output fields) type visits and temporary capacity, plus schema codec/hash work. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0031

[Lines 140–147](../../../../../src/runtime/session.cpp#L140); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PublicationPreparation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account candidate publication-preparation time across success and exceptions. |
| inputs / outputs | Candidate reference and start clock; finish records preparation once and returns policy eligibility. |
| invariants | Destructor records only unfinished active candidates. This guard reports policy/time, not durable selection or rollback. |
| ownership | Borrows the live candidate; adds no durable owner. |
| failure | Cleanup/finish use the candidate nonthrowing reporting path; exceptions in preparation still unwind normally. |
| cost | Clock reads and policy/reporting bookkeeping; never traverses query rows itself. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0032

[Lines 148–154](../../../../../src/runtime/session.cpp#L148); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ManagedGeneration {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the authoritative generation lock and optional selected plan. |
| inputs / outputs | GenerationOwner plus copied policy; optional plan installed by the coordinator. |
| invariants | Holding this owner preserves root-selection authority across publication uncertainty. |
| ownership | Moves the existing file/directory/lock owner; account-funded wrapper retains descriptor if present. |
| failure | Unpublished construction unwinds members; root I/O failures are handled by the surrounding selection boundary. |
| cost | Constant moves/control fields; final release closes descriptors and releases retained plan bytes. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0033

[Lines 155–166](../../../../../src/runtime/session.cpp#L155); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ManagedLocalSink {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain sink binding, file ownership and cumulative delivery progress. |
| inputs / outputs | Header/options, schema, optional file, verification sequence/work, blockage count and authenticated prefix. |
| invariants | failed or absent file blocks delivery; descriptive counters/prefix flag do not mint a Receipt or retirement authority. |
| ownership | Schema, file/index/buffers and wrapper use the existing query account; no copied per-retry grant. |
| failure | Constructor creates only an empty allocator-aware schema; later attachment/recovery owns errors. |
| cost | Fixed controls plus O(schema fields) schema and actual sink file/index buffers. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0034

[Lines 167–171](../../../../../src/runtime/session.cpp#L167); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void generation_checkpoint_policy(std::string_view path,const recovery::CheckpointFileLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate checkpoint transfer/path policy before generation publication. |
| inputs / outputs | Path view and CheckpointFileLimits; rejects path&gt;limit, path limit&gt;=4096, zero transfer/operations or oversized signed transfer. |
| invariants | Failure is unchanged at path stage before candidate checkpoint publication. |
| ownership | Borrows inputs; no file acquisition. |
| failure | Throws fixed GenerationFailure(limit,path,unchanged). |
| cost | Constant bounds checks. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0035

[Lines 172–175](../../../../../src/runtime/session.cpp#L172); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RecoveryOutput {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain bounded identity-bearing replay output awaiting transfer/delivery. |
| inputs / outputs | Account-funded RecoveredResult vector, next unread position and retained tuple payload total. |
| invariants | position&lt;=rows.size; payload_bytes counts unread tuples still owned by this buffer, while moved slots retain directory capacity. |
| ownership | Wrapper/directory and each tuple use the receiving query account. |
| failure | Limits and owner identity are enforced by append; destruction releases all remaining storage. |
| cost | Retains vector capacity plus actual tuple payloads; explicit transfer/discard pays ownership cleanup. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 176–176](../../../../../src/runtime/session.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit RecoveryOutput(const resource::MemoryAccount& account):rows(recovery::image_allocator<RecoveredResult>(account)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind an empty replay-output directory to the receiving account. |
| inputs / outputs | MemoryAccount constructs ImageVector allocator. |
| invariants | Creates no new cap or work grant. |
| ownership | Allocator retains the supplied account; no vector capacity allocated yet. |
| failure | Construction of scalar fields does not allocate or need an error handler. |
| cost | Fixed-size field initialization/copy; no state scan. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0037

[Lines 177–180](../../../../../src/runtime/session.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t retained_bytes() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count actual retained replay-output requests. |
| inputs / outputs | Wrapper allocation_bytes plus allocated directory capacity plus payload_bytes. |
| invariants | Already transferred tuples are excluded from payload total; unused directory slots stay included. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant allocator metadata reads and scalar addition; no tuple scan. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0038

[Lines 181–194](../../../../../src/runtime/session.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append(RecoveredResult row,std::size_t max_rows,std::size_t max_bytes) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append bounded replay output under exact receiving-account ownership. |
| inputs / outputs | Owning identity-bearing row, row cap and byte cap. |
| invariants | Checks row count, matching account, addition/capacity overflow, wrapper+directory+payload cap before insertion; actual post-reserve directory bytes are checked again. |
| ownership | Moves the row into receiving-account ImageVector; no public output escapes the unpublished recovery owner. |
| failure | Fixed ImageFailure or MemoryFailure/resource allocation propagates; failure rejects whole recovery construction. A successful reserve can precede a later byte rejection. |
| cost | Per-row ownership/size checks; bounded geometric reserve may move prior records and transiently overlap capacities. Tuple byte storage is native. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0039

[Lines 195–196](../../../../../src/runtime/session.cpp#L195); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L195-L196:sha256:45a72745b4f8b621b712b810c5a28b5a793a155c9f9da8ca632d3766652b59b1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/session.cpp: closes \`struct RecoveryOutput\`, \`anonymous namespace\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0040

[Lines 197–206](../../../../../src/runtime/session.cpp#L197); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LockedGenerationRecovery::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the original selected-generation lock through descriptor-aware recovery admission. |
| inputs / outputs | GenerationOwner, copied options, expected source program, receiving StorageWorkContext and optional ManagedPlan. |
| invariants | Expected source identity constrains artifact recovery but does not choose the selected physical plan. |
| ownership | Data owns the original root lock and admitted account/context; descriptor views remain inside that lifetime. |
| failure | Failed allocation/construction releases the same owner before returning any session; no reacquired root lock. |
| cost | Constant owner moves/copies plus admitted descriptor storage; no native replay in this constructor. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0041

[Lines 207–207](../../../../../src/runtime/session.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LockedGenerationRecovery::LockedGenerationRecovery(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install funded locked-recovery Data in its public facade. |
| inputs / outputs | AccountedUnique&lt;Data&gt; moved into data_. |
| invariants | Only factories construct this nonempty facade; it does not reopen the root. |
| ownership | Unique transfer; facade deleter retains its allocator account. |
| failure | Noexcept owner move. |
| cost | Constant transfer. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0042

[Lines 208–208](../../../../../src/runtime/session.cpp#L208); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LockedGenerationRecovery::~LockedGenerationRecovery()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release locked recovery ownership when it is abandoned or consumed. |
| inputs / outputs | Default destructor releases Data and its owned root lock/context/descriptor. |
| invariants | No recovery session is fabricated and no durable tail is repaired by destruction. |
| ownership | Final unique owner destroys descriptor/account allocations and native root owner. |
| failure | Member destruction is nonthrowing; no public Guard is called. |
| cost | Closes native owner and releases retained allocations; cost follows retained descriptor/context ownership. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0043

[Lines 209–209](../../../../../src/runtime/session.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool LockedGenerationRecovery::has_plan() const noexcept {return bool(data_->plan);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether the locked root requires an embedded selected plan. |
| inputs / outputs | Returns whether Data.plan exists. |
| invariants | A live factory-produced recovery facade is required; false denotes a legacy selection. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0044

[Lines 210–212](../../../../../src/runtime/session.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view LockedGenerationRecovery::compiler_artifact() const & noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the compiler artifact required by the locked selected root. |
| inputs / outputs | Returns ManagedPlan.artifact(), or empty view for a legacy root. |
| invariants | Caller must not outlive/consume the locked owner while using the view. |
| ownership | Borrow only; consuming the Owner ends this facade lifetime. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0045

[Lines 213–213](../../../../../src/runtime/session.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics LockedGenerationRecovery::accounted_memory_statistics() const {return data_->context->memory().statistics();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read receiving-account statistics during locked recovery admission. |
| inputs / outputs | Returns StorageWorkContext.memory().statistics(). |
| invariants | Counts actual admitted native requests, not compiler-account memory or RSS. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Fixed account-ledger snapshot; no replay or allocation-attribution scan. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0046

[Lines 214–235](../../../../../src/runtime/session.cpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct QuerySession::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one creator-thread session and all durable/replay coordination state. |
| inputs / outputs | Immutable writer ID, reentrancy/control flags, committed physical sequence, sticky source flags, contexts and optional durable/candidate/output owners. Fixed pattern origins/history/first violation share the existing semantic-input-failure latch. |
| invariants | committed_sequence tracks physical epochs; accepted commands and journal substeps can differ for windows. Descriptive journal state is not resumability authority after uncertainty. |
| ownership | Stable funded Impl uniquely owns mutable session state; immutable contexts can be shared by reports. The declaration belongs to immutable run context; no additional row/history graph is retained. |
| failure | Constructors publish no partially constructed Impl; ordinary operations use Guard and specific recovery gates. |
| cost | Fixed controls plus retained native/file/candidate/output allocations; no per-update full-state copy. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0047

[Lines 236–236](../../../../../src/runtime/session.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool delivery_pending() const noexcept {return local_sink && (local_sink->failed || !local_sink->file || local_sink->verified_sequence<committed_sequence);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Determine whether actual local delivery blocks further input. |
| inputs / outputs | True if an attached sink is failed, absent its file, or verified behind committed_sequence. |
| invariants | Even an empty-output physical epoch must receive durable closure before admission advances. |
| ownership | Reads established sink controls. |
| failure | Noexcept scalar/optional checks. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0048

[Lines 237–237](../../../../../src/runtime/session.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool recovery_output_pending() const noexcept {return recovered_output && recovered_output->position<recovered_output->rows.size();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test for unread retained replay rows. |
| inputs / outputs | True only when recovered_output exists and position&lt;rows.size(). |
| invariants | An allocated empty/exhausted directory alone is not pending output. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Noexcept fixed field reads. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0049

[Lines 238–238](../../../../../src/runtime/session.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t output_remaining() const {return output?output->remaining():recovered_output?recovered_output->rows.size()-recovered_output->position:0;}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report retained committed row count without consuming it. |
| inputs / outputs | Live output.remaining() takes precedence; otherwise replay buffer size-position, else zero. |
| invariants | This count can be zero while empty-epoch local delivery still blocks input. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Constant epoch/buffer metadata reads; no row traversal. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0050

[Lines 239–239](../../../../../src/runtime/session.cpp#L239); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear_recovered_output() noexcept {recovered_output.reset();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the complete recovered-output owner. |
| inputs / outputs | Resets recovered_output without changing committed native state. |
| invariants | Caller separately manages coverage/admission flags; dropping this buffer is not durable acknowledgement. |
| ownership | Destroys unread tuple owners, directory and wrapper; returned rows retain their own payloads. |
| failure | Noexcept destruction; no new allocation. |
| cost | O(retained rows) element cleanup and actual allocation release; final shared tuple/layout owners can add teardown. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0051

[Lines 240–247](../../../../../src/runtime/session.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_local_sink(const recovery::journal::Header& journal,const SessionLocalSinkOptions& options,bool replaying) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an attached sink descriptor before opening or replaying its file. |
| inputs / outputs | Journal header, copied sink options and replay flag build schema/header and initial verified sequence. |
| invariants | Schema width respects configured fields; header binds query, sink, exact journal binding, generation, physical base and scalar schema hash. |
| ownership | Unpublished wrapper/schema is funded by the runtime original account, then moved to local_sink. |
| failure | Allocation, schema-limit/hash failures propagate with any existing local_sink unchanged. |
| cost | O(result fields) schema copies/hash work plus one funded wrapper; does not scan outputs or acquire the file. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0052

[Lines 248–257](../../../../../src/runtime/session.cpp#L248); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void establish_sink_prefix(const recovery::sink::File& file,const recovery::journal::Header& journal,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Authenticate the sink prefix underlying a checkpoint boundary. |
| inputs / outputs | Admitted sink File, journal header and optional durable root delivery anchor. |
| invariants | Expected root anchor must match journal physical base and actual sink ID/prefix bytes/hash; existing verified_prefix must still match. Without an anchor only an exact base or expected binding establishes one. |
| ownership | Borrows file/session; stores a scalar verified prefix, not a detachable authority object. |
| failure | Binding failures preserve prior prefix and reject attachment/recovery; File.prefix errors remain visible. |
| cost | Fixed checks and admitted prefix-index lookup; no reread/materialization of every epoch. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0053

[Lines 258–260](../../../../../src/runtime/session.cpp#L258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void advance_sink_prefix(std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance an already authenticated sink-prefix fingerprint. |
| inputs / outputs | Physical sequence queries File.prefix and replaces verified_prefix only if a prior basis exists. |
| invariants | It never upgrades an unauthenticated two-step attachment into retirement authority. |
| ownership | Copies fixed hash/frontier fields; sink file remains the authoritative owner. |
| failure | Prefix lookup may reject invalid/unavailable file state; no error is silently ignored. |
| cost | Fixed metadata/index lookup at the accepted sequence, with no new output encoding. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0054

[Lines 261–286](../../../../../src/runtime/session.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void collect_recovered_output(const recovery::journal::Header& header,const SessionJournalRecoveryOptions& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify durable replay output or retain only missing epochs. |
| inputs / outputs | Journal identity/options and freshly committed private recovery output. |
| invariants | Persisted epochs must be contiguous after verified_sequence and match complete native canonical output, including empty closure. Bare suppression discards only caller-selected older output and grants no delivery authority. |
| ownership | Borrowed RowViews retain output while verifying; missing native tuples move into one receiving-account RecoveryOutput. |
| failure | Delivery-work/row/byte/native/file mismatch aborts whole unpublished recovery; no owner/output escapes. Verified output is acknowledged only after comparison. |
| cost | Persisted replay still pays bounded producer spool, row-view capacity, canonical verification and cumulative epoch+row work; missing replay pays buffer capacity/payload storage. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0055

[Lines 287–287](../../../../../src/runtime/session.cpp#L287); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static void replay_frame(std::string_view frame,const recovery::journal::Scanned& after,void* context);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the synchronous native journal replay callback. |
| inputs / outputs | Frame bytes, scanned post-frame prefix and private ReplayContext. |
| invariants | Callback reconstructs an unpublished owner; it has no public delivery or thread-switch authority. |
| ownership | All arguments borrow the surrounding open_replay construction. |
| failure | Callback failures propagate through construction; no callback retry wrapper. |
| cost | Declaration only; body has full native decode/replay costs. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0056

[Lines 288–288](../../../../../src/runtime/session.cpp#L288); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayContext {Impl& data;const SessionJournalRecoveryOptions& options;recovery::journal::Header header;std::uint64_t remaining,source_remaining;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one recovery operation and its cumulative decode/source balances. |
| inputs / outputs | Impl/options/header borrows and remaining/source_remaining u64 values. |
| invariants | Balances span the complete file replay and do not reset per frame. |
| ownership | Stack/context object borrows the still-live unpublished session and entry-copied options. |
| failure | Construction of scalar fields does not allocate or need an error handler. |
| cost | Fixed fields, no nested allocation. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0058

[Lines 290–292](../../../../../src/runtime/session.cpp#L290); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_available() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject use of a poisoned journal coordinator. |
| inputs / outputs | Throws when journal_confirmed.recovery_required is latched. |
| invariants | A confirmed durable lower bound cannot authorize resuming an uncertain writer. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Fixed SessionJournalFailure(recovery_required); no repair/retry. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0059

[Lines 293–296](../../../../../src/runtime/session.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require_recovery() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Latch authoritative recovery and cancel any candidate resources. |
| inputs / outputs | Sets recovery_required and cancels reoptimization with native_failure if present. |
| invariants | Candidate cancellation cannot undo a possibly selected root or durable journal decision. |
| ownership | Retains journal/root locks and controls; candidate cancels its private target/ledger. |
| failure | Noexcept cleanup and scalar updates. |
| cost | Fixed latch plus destruction of candidate-owned state/ledger, potentially population-sized. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0060

[Lines 297–301](../../../../../src/runtime/session.cpp#L297); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_confirm() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot the last confirmed journal prefix into fixed session metadata. |
| inputs / outputs | Reads attached File.state and copies records/physical/command/frontier fields. |
| invariants | Called only after successful creation/append/reconstruction; clears recovery flag only at that confirmed healthy boundary. |
| ownership | Copies scalar/optional metadata; no file read or new allocation. |
| failure | Noexcept on a live attached journal. |
| cost | Constant fixed-state copy. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0061

[Lines 302–305](../../../../../src/runtime/session.cpp#L302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_append(std::string_view frame) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a durable journal frame and confirm its accepted prefix. |
| inputs / outputs | Encoded frame view is passed once to attached journal.append. |
| invariants | Only successful append updates journal_confirmed; native journal FileFailure poisons the session. |
| ownership | Borrows encoded bytes for synchronous append; retains attached writer and root ownership. |
| failure | Catches FileFailure solely to latch require_recovery, then rethrows. Other prepublication codec/memory categories are not rewritten. |
| cost | Actual synchronous write/fsync/file work plus fixed confirmation; no constant latency claim. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0062

[Lines 306–326](../../../../../src/runtime/session.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_input(const io::InputItemView& item) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist one immutable logical input before native physical begin. |
| inputs / outputs | InputItemView plus current source decoder position produces one encoded Input frame, unless the matching pending input already exists. |
| invariants | Pending ordinal/input survives retries and window substeps. A different input sequence rejects; a reader records raw consumed position and CSV permutation, not just accepted progress. |
| ownership | Source reader/queue keeps the head; encoded frame is temporary original-account storage. |
| failure | State/encoding/append failures propagate; caller aborts private native/window work. Uncertain file append latches recovery in journal_append. |
| cost | No-op without a journal; otherwise encode complete row/command/source metadata and synchronous WAL I/O. Existing pending input requires fixed identity checks. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0063

[Lines 327–338](../../../../../src/runtime/session.cpp#L327); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void journal_decision() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Persist the exact prepared physical or metadata decision. |
| inputs / outputs | Attached journal pending input plus native/window state yields Commit(kind,physical sequence,accepted command,substep,completion). |
| invariants | Physical sequence advances only for pending physical epochs; incomplete window metadata preserves accepted command until its final substep. |
| ownership | Temporary encoded decision uses the original account; no input/output ownership transfer here. |
| failure | Missing pending input rejects. Encoding/append failures propagate before native publication; append uncertainty latches recovery. |
| cost | Fixed decision metadata plus bounded encoding/hash and synchronous durable append. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0064

[Lines 339–349](../../../../../src/runtime/session.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish(bool discard)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order durable commit decision before native epoch publication/input acknowledgement. |
| inputs / outputs | Discard-output choice and already prepared session state in; committed/deliverable epoch or acknowledged metadata step out. |
| invariants | If a journal decision is durably accepted, a later failure cannot be represented as an ordinary retry of an undecided input. |
| ownership | The session keeps journal, pending native/window/input owners until publication or abort; abort releases private pending state. |
| failure | The catch calls require_recovery when a durable decision existed, then aborts and rethrows. journal_append separately latches uncertain append outcomes. These boundaries protect different failure stages. |
| cost | Potential encoding and synchronous WAL I/O precede nonallocating native commit; output publication/acknowledgement adds lifecycle work. No constant latency claim. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [docs/session_lifecycle.md](../../../../session_lifecycle.md) |

## B0065

[Lines 350–367](../../../../../src/runtime/session.cpp#L350); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Reader borrows this owned stream. Reverse destruction preserves lifetime,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare physical/source/private ownership in safe destruction order. |
| inputs / outputs | Owned input precedes borrowed EventReader, then queue/window, runtime/pending/output and retained diagnostics. |
| invariants | Reverse destruction keeps stream alive through reader cleanup, including a later constructor failure. At most one physical pending/output token is session-private; window Prepared can represent metadata-only work. |
| ownership | Unique source/runtime/token owners remain inside Impl; retained report/run/trace summaries can share immutable account-backed metadata after mutable-state release. |
| failure | Unpublished construction unwinds members; explicit abort/stop/drop resolve private tokens and source lifetime without allocating. |
| cost | Actual source/output/runtime storage and retained metadata, not a parallel session-wide undo image; final destruction can traverse all retained elements. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0066

[Lines 368–379](../../../../../src/runtime/session.cpp#L368); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Guard {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard every public operation against wrong-thread and same-thread reentry. |
| inputs / outputs | Impl reference; constructor checks immutable writer identity before mutable busy, then marks busy until destruction. |
| invariants | No mutex/multiwriter support is implied. Wrong thread is rejected before reading mutable session state. |
| ownership | Stack RAII borrows Impl and owns only its operation busy interval. |
| failure | Precondition Error may allocate before acquisition; destructor clears busy without throwing. |
| cost | Thread-ID comparison and fixed flag work; no state copy or query allocation on success. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0067

[Lines 380–382](../../../../../src/runtime/session.cpp#L380); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L380-L382:sha256:bb5326a49526f91ed49b72f2af32c6e7baec63964e677bfa2560a5da9cf2ddd5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct SelectionGuard\`: Durable root selection can be uncertain after an I/O failure. Preserve the authority-bearing file/lock owner and latch recovery_required; do not treat this guard as ordinary rollback of an in-memory tentative mutation. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/session.cpp:L379; use that declaration for the actual input/output shape. |
| invariants | The source note states: Durable root selection can be uncertain after an I/O failure. Preserve the authority-bearing file/lock owner and latch recovery_required; do not treat this guard as ordinary rollback of an in-memory tentative mutation. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment creates or retains no runtime owner. Its prose documents preserving the authority-bearing file/lock owner when durable root selection is uncertain; that lifetime rule must be checked in the adjacent implementation, not inferred from the comment alone. |
| failure | The note describes a failure or stop boundary: Durable root selection can be uncertain after an I/O failure. Preserve the authority-bearing file/lock owner and latch recovery_required; do not treat this guard as ordinary rollback of an in-memory tentative mutation. The comment adds no handler; the surrounding code determines the outcome. |
| cost | The note states a local cost boundary: Durable root selection can be uncertain after an I/O failure. Preserve the authority-bearing file/lock owner and latch recovery_required; do not treat this guard as ordinary rollback of an in-memory tentative mutation. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0068

[Lines 383–395](../../../../../src/runtime/session.cpp#L383); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SelectionGuard
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain durable generation authority and latch recovery when root selection may have changed. |
| inputs / outputs | Session, managed generation and optional newly created holder in; destructor handles incomplete selection outcome. |
| invariants | An attempted or changed root can authorize new durable state even when the caller received an error; do not revert it as a normal in-memory mutation. |
| ownership | The guard borrows session/managed owner and can transfer a fresh holder into the session so its file/lock authority survives failure. |
| failure | If selection was not attempted and root is unchanged, do nothing; otherwise require recovery unless completion was marked. |
| cost | Fixed outcome comparisons and owner move on cleanup; no new file acquisition, allocation or generic transaction wrapper. |
| Design | [docs/generations.md](../../../../generations.md), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0069

[Lines 396–397](../../../../../src/runtime/session.cpp#L396); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L396-L397:sha256:60adbb91086a7b8abc4025d8ce82a07d4ee6ba210c26f2542eb526bed45452b3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent capture_patterns usage, ownership and cost boundary. |
| inputs / outputs | Source comment documents the neighboring implementation; it accepts no runtime input or output. |
| invariants | The note is guidance, not executable enforcement or independent proof. Detailed callable contracts describe the actual checks. |
| ownership | No runtime owner is created by prose. |
| failure | The comment itself cannot throw or change admission. |
| cost | No runtime work or allocation; the adjacent operation retains its actual costs. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0070

[Lines 398–415](../../../../../src/runtime/session.cpp#L398); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L398-L415:sha256:82281f972aa16ed176b4d891d7384ed56933a9f0709293489af40bf38484539e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture optional source-bound rules for the actual Session owner. |
| inputs / outputs | Absent options return none; otherwise admit 64 source-hash work, check matches(program), visit R rules for managed FIFO origin, and use bounded receiving copy. |
| invariants | Positive FIFO scopes require a managed window table with a known origin. Nonwindow FIFO is refused. Declaration import alone does not establish history; no retroactive live attach is exposed. |
| ownership | Program/options/window are borrowed synchronously. New declaration data uses the actual program account; no row or history copy is retained. |
| failure | Invalid/foreign requests and unsupported origins use existing Error; metadata grants use patterns::Failure; native allocation can fail before publication. |
| cost | O(R) validation/copy plus fixed source binding, two existing fixed-work debits and O(R) retained rule storage. No per-update execution here. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0071

[Lines 416–418](../../../../../src/runtime/session.cpp#L416); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L416-L418:sha256:e702f14f06dc174fc654ca98c8ee8b3a3ec80258e5a3a95e23d3631625d49bff
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent pattern_status usage, ownership and cost boundary. |
| inputs / outputs | Source comment documents the neighboring implementation; it accepts no runtime input or output. |
| invariants | The note is guidance, not executable enforcement or independent proof. Detailed callable contracts describe the actual checks. |
| ownership | No runtime owner is created by prose. |
| failure | The comment itself cannot throw or change admission. |
| cost | No runtime work or allocation; the adjacent operation retains its actual costs. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0072

[Lines 419–431](../../../../../src/runtime/session.cpp#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L419-L431:sha256:c5baf9957bc7381189ec243866f8ee873dd1ddfd8dc2b129735e8ff12973d83f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a committed monitor diagnostic from the actual Session state. |
| inputs / outputs | Return declaration/history/insertion policy, physical and command origins, current committed counters, actual runtime physical hash and first fixed violation. |
| invariants | Called while runtime/context are available under the Session guard. Private command preparation is excluded. Window metadata-only progress uses the command domain. Restored history explicitly assumes a trusted checkpoint. |
| ownership | Result owns fixed fields and a copied immutable declaration handle; that handle can retain its original account owner. No rule vector or rows are cloned. |
| failure | The valid guarded body has no new allocation or semantic failure path. Public availability checks belong to its caller. |
| cost | Fixed fields/hash/refcount work; no scan, clock or allocation. Last-owner declaration destruction can be O(R). |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0073

[Lines 432–433](../../../../../src/runtime/session.cpp#L432); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L432-L433:sha256:359819ac4187742a0cc50eadea14ed656f23fba550d8b252d9c22206c5424a8e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent check_pattern usage, ownership and cost boundary. |
| inputs / outputs | Source comment documents the neighboring implementation; it accepts no runtime input or output. |
| invariants | The note is guidance, not executable enforcement or independent proof. Detailed callable contracts describe the actual checks. |
| ownership | No runtime owner is created by prose. |
| failure | The comment itself cannot throw or change admission. |
| cost | No runtime work or allocation; the adjacent operation retains its actual costs. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0074

[Lines 434–439](../../../../../src/runtime/session.cpp#L434); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L434-L439:sha256:6f50e3ecaf8f740dde48d915c063a7c1a3b6580cfe0c79a5b6fc0646544431bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject insertion-only erase commands before nonwindow journal/native preparation. |
| inputs / outputs | Borrow PhysicalUpdateView and caller-owned scalar diagnostic; skip absent declaration/non-erase, otherwise find the table rule and require it not insertion-only. |
| invariants | This policy intentionally rejects absent-row erase no-ops. It tests commands, not a native membership scan. Window final-reference enforcement belongs to window preparation. |
| ownership | No row/rule storage is retained; the declaration owns the borrowed rule. Diagnostic output is caller stack scratch. |
| failure | Completed semantic Error is latched by the existing begin boundary. Error-object allocation failure is a retryable bad_alloc without a violation latch. |
| cost | Fixed skip or O(log R) fixed-ID comparisons; no row copy, secondary index or successful-check allocation. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0075

[Lines 440–455](../../../../../src/runtime/session.cpp#L440); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(DeltaRuntime value,std::unique_ptr<std::istream> stream,std::optional<io::QueueLimits> limits,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit runtime/source ownership and immutable run context. |
| inputs / outputs | Constructed DeltaRuntime, owned stream or typed limits, SessionOptions and optional WindowController. |
| invariants | Typed limits choose physical/window queue mode; stream reader borrows input declared earlier. Initialization context/actual resolved mode remain exact. Optional declaration capture validates actual source, managed FIFO origin and metadata limits before publishing the context. |
| ownership | Impl owns stream, decoder/queue/window/runtime; funded shared SessionRunContext retains account-backed input/window policies. |
| failure | Any context/reader/queue/benchmark setup failure unwinds members in lifetime-safe reverse order; no session facade is published. |
| cost | Visits/copies option metadata, allocates context and queue/reader buffers as needed; no fabricated input events or result scan. Opt-in declaration binding/copy adds O(R) work and receiving-account immutable storage. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0076

[Lines 456–505](../../../../../src/runtime/session.cpp#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(DeltaRuntime value,std::unique_ptr<std::istream> stream,const SessionCheckpoint& state,const SessionCheckpointLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct source/window controls around an admitted checkpoint runtime. |
| inputs / outputs | Runtime, continuation stream, validated SessionCheckpoint and native limits. |
| invariants | Runtime sequence equals saved physical sequence; source variants/options/EOF/closure and window completed-command frontier must agree. Created state must be epoch zero and healthy. Re-admit declaration into the actual receiving account, preserve origins/violation, and label the prefix trusted_restored_checkpoint. |
| ownership | Restored source/window/context storage uses the receiving runtime account; stream remains owned before reader. |
| failure | Corrupt identity/progress/profile and source/window/resource failures reject construction; all members unwind before exposure. |
| cost | Explicit source/window reconstruction and option/progress copies under saved limits; work scales with source metadata and window state, beyond fixed session setup. Declared restore additionally validates/copies R rules under receiving pattern limits; binary decoding has separate funded scratch/import costs. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0077

[Lines 506–506](../../../../../src/runtime/session.cpp#L506); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] SessionCheckpoint checkpoint(const SessionCheckpointLimits&,const DeltaRuntime* replacement=nullptr) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare full quiescent session checkpoint capture and optional target substitution. |
| inputs / outputs | Native limits and optional already verified replacement runtime. |
| invariants | Replacement keeps the same committed source/window barrier; this hook does not admit queued/private work. |
| ownership | Declaration retains no state; result capture owns its native image. |
| failure | Definition enforces busy/resource/sequence checks. |
| cost | No declaration runtime work; definition materializes complete state. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0078

[Lines 507–514](../../../../../src/runtime/session.cpp#L507); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::shared_ptr<const SessionRunContext> replacement_context(const DeltaRuntime& target) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare immutable run metadata for an admitted replacement plan. |
| inputs / outputs | Target DeltaRuntime reuses existing source/queue/window policy and snapshot limits with target initialization/options/mode/completion. |
| invariants | Does not replace reader/queue/window or accepted progress; metadata preparation precedes durable selection. Require an unchanged declared physical source and retain the same immutable declaration. Progress/violation stay in the Session; status reads the installed tree. |
| ownership | Funded shared SessionRunContext uses target original account, while exact compatible source policy owners can remain shared. The replacement context shares the declaration metadata owner; no rule-vector copy is made here. |
| failure | Allocation failure leaves existing context/runtime untouched. |
| cost | One shared control allocation and immutable owner/scalar copies; no result/source scan. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0079

[Lines 515–520](../../../../../src/runtime/session.cpp#L515); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void install_reoptimization(reoptimization::detail::State& candidate,std::shared_ptr<const SessionRunContext> context,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a durably selected target without throwing. |
| inputs / outputs | Verified candidate target plus prebuilt run context, new journal File and ManagedPlan. |
| invariants | Called only after successful root publication at the same committed physical barrier; source/window/delivery owners stay stable. |
| ownership | Moves old runtime aside, installs prepared owners, snapshots fixed metadata then releases old runtime; source-catalog aliases can retain old immutable metadata. |
| failure | Noexcept; impossible violations terminate rather than create a recoverable postselection allocation failure. |
| cost | Fixed owner transfers plus potentially large old-runtime teardown. Old/target/image overlap and retained aliases remain real memory costs. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0080

[Lines 521–521](../../../../../src/runtime/session.cpp#L521); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Impl() { drop(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy session implementation through private terminal cleanup. |
| inputs / outputs | Destructor calls idempotent drop(). |
| invariants | Facade destruction establishes exclusive lifetime/reentrancy protection before Impl release; never calls a throwing public Guard. |
| ownership | Releases remaining unique native/file/source owners through drop and subsequent member destruction. |
| failure | Implicit noexcept destructor; member cleanup must not throw. |
| cost | Actual retained-state/output/source/file destruction; no cleanup allocation. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0081

[Lines 522–522](../../../../../src/runtime/session.cpp#L522); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool has_private() const noexcept { return pending.has_value() || window_pending.has_value(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether any unpublished physical or window work exists. |
| inputs / outputs | Returns pending.has_value() \|\| window_pending.has_value(). |
| invariants | Metadata-only window preparation still counts as private state. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Noexcept fixed optional checks. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0082

[Lines 523–530](../../../../../src/runtime/session.cpp#L523); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void admission_available() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate typed admission without requiring start. |
| inputs / outputs | Reads journal health, terminal/paused control, candidate freeze and queue presence. |
| invariants | Created typed sessions may enqueue/finish input; paused/terminal/frozen/stream sessions reject admission. |
| ownership | Reads the established session, does not consume a caller batch. |
| failure | Guard-specific Error or fixed recovery failure precedes queue mutation. |
| cost | Fixed preconditions; no peek, decoding, engine work or allocation on success. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0083

[Lines 531–537](../../../../../src/runtime/session.cpp#L531); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void available(bool paused_ok=false) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate operations that require a started live session. |
| inputs / outputs | paused_ok selects whether paused control is admitted after journal health/terminal/start checks. |
| invariants | State errors precede operation-specific phase errors; recovery-required remains authoritative. |
| ownership | Reads controls only. |
| failure | Throws for dropped/stopped/created/forbidden paused state; no private work is aborted by an invalid call. |
| cost | Fixed branches; no source/runtime scan. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0084

[Lines 538–553](../../../../../src/runtime/session.cpp#L538); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionPhase phase() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive work phase independently of session control state. |
| inputs / outputs | Pending DeltaState, metadata window flags and output/delivery state yield SessionPhase. |
| invariants | Private physical state has precedence; output includes replay backlog or undelivered empty closure, and paused control need not change a prepared/draining token. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Noexcept existing-token state reads. |
| cost | Fixed optional/state checks. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0085

[Lines 554–558](../../../../../src/runtime/session.cpp#L554); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t accepted_sequence() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the last acknowledged logical source command. |
| inputs / outputs | Reader progress.sequence, queue progress.sequence or final stopped progress. |
| invariants | For windows accepted commands can lag physical expiration epochs; peeking a row does not advance this value. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Fixed progress accessor; does not export/copy the source-position map. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0086

[Lines 559–563](../../../../../src/runtime/session.cpp#L559); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputProgress export_accepted() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export acknowledged source progress as a caller value. |
| inputs / outputs | Current reader/queue/final AccountedInputProgress becomes owning InputProgress. |
| invariants | Only accepted positions are exported; cached unacknowledged input remains excluded. |
| ownership | Explicit export copies source-position/name data into caller-owned DTO storage. |
| failure | Allocation can fail; session/source progress remains unchanged. |
| cost | O(retained source-position entries and name bytes) copy, not a fixed-cost status read. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0087

[Lines 564–566](../../../../../src/runtime/session.cpp#L564); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void need_pending() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one private input before step/commit/drain-start. |
| inputs / outputs | has_private must be true. |
| invariants | Metadata-only window work is a valid private pending input. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Throws session_no_pending_epoch without altering legitimate existing state. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0088

[Lines 567–571](../../../../../src/runtime/session.cpp#L567); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void abort() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort all unpublished physical/window/candidate-stage work. |
| inputs / outputs | Rolls back and destroys pending epoch; rolls back candidate stage and clears window/private metadata flags. |
| invariants | Does not acknowledge reader/queue or erase the durable pending input; committed sequence/output remain authoritative. |
| ownership | Pending tokens own prepaid inverses; destroying window Prepared restores private window staging. |
| failure | Noexcept rollback/cleanup; no resource refill or full-state backup. |
| cost | Proportional to affected staged inverses and released payloads, not full committed-state copying. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0089

[Lines 572–575](../../../../../src/runtime/session.cpp#L572); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retain_report_metadata() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain lightweight metadata before releasing or replacing runtime state. |
| inputs / outputs | Live runtime program/options/profile/owner/sequence/state form SessionReportMetadata. |
| invariants | This shares actual immutable CompiledProgram and does not compute gauges, rows or report text. |
| ownership | Retains immutable program/account after runtime drop; no mutable table lease. |
| failure | Noexcept metadata owner/scalar copies. |
| cost | Fixed shared-owner copies and optional replacement; final old metadata release may deallocate. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0090

[Lines 576–585](../../../../../src/runtime/session.cpp#L576); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void retain_observation() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain fixed observation and cursor summaries with current session identity. |
| inputs / outputs | Live runtime summaries plus run_context and committed_sequence update retained_observation. |
| invariants | No trace payload export or report construction is invoked; session attachment/sequence are refreshed. |
| ownership | Summary retains immutable context/program-related owners; no separate state snapshot. |
| failure | Noexcept existing summary reads/copies. |
| cost | Fixed metric-registry-sized copy and shared-owner updates; no native population scan. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0091

[Lines 586–598](../../../../../src/runtime/session.cpp#L586); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publish(DeltaRuntime::Epoch epoch,std::uint64_t sequence,bool discard) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one already committed native epoch and acknowledge its prepared source. |
| inputs / outputs | Epoch owner, exact physical sequence and discard flag. |
| invariants | Acknowledgement/window publication and subsequent sequence/token/output changes are nonthrowing. No user callback/report creation may follow engine publication. |
| ownership | Moves Epoch into output or discards it; reset even inactive epochs so PhysicalEpoch journals/source pins are released. |
| failure | Noexcept publication boundary; all potentially failing source preparation and WAL decisions precede entry. |
| cost | Fixed bookkeeping plus actual journal/pin/output release and optional candidate commit; cleanup can scale with retained epoch state. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0092

[Lines 599–610](../../../../../src/runtime/session.cpp#L599); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void acknowledge() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish prepared window state and accept only a complete logical command. |
| inputs / outputs | Window Prepared, reader/queue cached head and metadata flags. |
| invariants | Nonfinal watermark substeps publish window progress without source acknowledgement; final or nonwindow input is acknowledged once. |
| ownership | Destroys published window token and clears private command flags; source owns prepaid acknowledgement node. |
| failure | Noexcept; prepared source/window ownership is required. This function never parses or allocates progress copies. |
| cost | Fixed coordinator work plus prepaid source/window publication and staged-node cleanup. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0093

[Lines 611–615](../../../../../src/runtime/session.cpp#L611); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool admitted_input() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect already admitted cached input without consuming another byte. |
| inputs / outputs | Reader records_read &gt; accepted sequence, or nonempty typed queue. |
| invariants | A decoded row retained after engine abort remains admitted and must drain before a candidate barrier freezes future input. |
| ownership | Reads existing source counters only. |
| failure | Reads only the stated valid source metadata; no validation, allocation or recovery path. |
| cost | Fixed counters/queue-empty query; no peek or allocation. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0094

[Lines 616–619](../../../../../src/runtime/session.cpp#L616); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_update(const PhysicalUpdateView& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage candidate catch-up bookkeeping before beginning the old native update. |
| inputs / outputs | Borrowed PhysicalUpdateView is staged into optional reoptimization ledger, then runtime.begin_view creates pending. |
| invariants | The original update sequence and account/grant remain shared with existing native owner; ledger follows its candidate cancellation policy. |
| ownership | Session owns pending; candidate owns any funded tentative ledger entry. |
| failure | Runtime begin failure propagates to begin caller, which aborts both pending/window and candidate stage. |
| cost | Actual ledger descriptor/row-byte staging if active plus native begin/preparation work; no whole runtime copy. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0095

[Lines 620–666](../../../../../src/runtime/session.cpp#L620); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionBegin begin(bool replay=false,bool paused_ok=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin exactly the current validated source command or window substep. |
| inputs / outputs | Replay/paused flags plus current source yield pending, would_block or end. |
| invariants | Requires healthy started state, no private/output conflict, writer-ready runtime and source/physical frontier match. Delivery blocks before peek; frozen barrier may drain only admitted input. Pattern guards precede journal/native preparation. Whole-window commands preflight before any effect. Only a fully constructed semantic Error latches a fixed violation; resource/error-construction failure uses existing abort and remains retryable. |
| ownership | Reader/queue keeps immutable cached head; private window token prepares before WAL; native pending remains session-owned. |
| failure | Error path preserves sticky window/source validation failures then aborts; generic failure also aborts. Cached input and durable pending frame remain for valid retry, unless recovery is latched. |
| cost | At most one source peek and physical/window begin, with decode/semantic/ledger/WAL/native preparation costs. Watermark may require multiple calls; no arbitrary read-ahead. Nonwindow erase lookup adds O(log R); window cost belongs to the bounded private preflight. No new catch/retry layer or retained row mirror. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0096

[Lines 667–682](../../../../../src/runtime/session.cpp#L667); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stop() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop input terminally while retaining committed runtime for inspection. |
| inputs / outputs | Idempotent unless already stopped/dropped; aborts private work, discards outputs, cancels candidate and closes source. |
| invariants | Unfinished input is not acknowledged; final progress is moved from close before source/stream release. File/root/sink owners remain until drop/destruction. |
| ownership | Destroys source buffers/window activity/output and moves accepted progress; retains runtime, contexts and durable writer locks. |
| failure | Noexcept cleanup; exclusive operation/lifetime guard prevents reentrant access through stream destruction. |
| cost | Proportional to retained input/output/private work and candidate teardown; source-position storage transfers without copying. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0097

[Lines 683–691](../../../../../src/runtime/session.cpp#L683); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drop() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drop mutable native state and durable owners while keeping diagnostics. |
| inputs / outputs | Calls idempotent stop then releases candidate/window/runtime/journal/generation/sink and accepted progress. |
| invariants | Sets journal enabled false and dropped control. Optional trace is marked released; retained immutable report/run metadata can still keep the original account and program alive. |
| ownership | Releases file/root/sink descriptors/locks and mutable state; external native tuples/captures remain independently owned. |
| failure | Noexcept cleanup; neither drop nor cancellation repairs uncertain durable state. |
| cost | Full retained mutable-state/buffer/progress teardown can be population-sized; no allocation or concealed full-state undo copy. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0098

[Lines 692–693](../../../../../src/runtime/session.cpp#L692); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L692-L693:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct QuerySession::Impl\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct QuerySession::Impl\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct QuerySession::Impl\` at its lexical source position in src/runtime/session.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct QuerySession::Impl\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0099

[Lines 694–721](../../../../../src/runtime/session.cpp#L694); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::Impl::replay_frame(std::string_view frame,const recovery::journal::Scanned& after,void* context) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct one validated journal frame inside an unpublished session. |
| inputs / outputs | Frame, scanned prefix and cumulative ReplayContext; Input stages source replay, Commit reproduces/prepares/commits the exact native transition. |
| invariants | Checks physical/metadata kind, completion and command/physical frontiers against actual preparation. Journal is unattached during replay, so finish does not append another decision. |
| ownership | Decoded input and row views are temporary original-account values; cached source and output remain inside receiving session. |
| failure | Decode/source/work/transition/native/output mismatch propagates and destroys the whole recovery owner before exposure/repair. |
| cost | Bulk reconstruction inspects/decodes rows, stages source, may run producer steps to completion and verifies/buffers output. Cumulative decode/source budgets supplement actual native/file grants; callback has no constant latency. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0101

[Lines 723–723](../../../../../src/runtime/session.cpp#L723); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::QuerySession(resource::AccountedUnique<Impl> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a fully constructed stable session implementation. |
| inputs / outputs | AccountedUnique&lt;Impl&gt; transferred into facade. |
| invariants | Factory allocates the facade first and the placement constructor cannot fail afterward. |
| ownership | Unique Impl transfer; AccountedUnique facade deleter retains original account. |
| failure | Noexcept owner move. |
| cost | Constant transfer. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0102

[Lines 724–724](../../../../../src/runtime/session.cpp#L724); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L724-L724:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/session.cpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0103

[Lines 725–728](../../../../../src/runtime/session.cpp#L725); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(const QuerySession& session) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the existing native storage-work context to tests. |
| inputs / outputs | Testing-only session reference returns optional RuntimeStorageWork through guarded runtime probe. |
| invariants | No runtime after drop yields null; probe does not grant new storage work or production API authority. |
| ownership | Borrows session; copies diagnostic allowance facts. |
| failure | Thread/reentrancy guard errors remain visible; lower-level probe preconditions apply. |
| cost | Fixed delegate/access; compiled only with CROWN_RUNTIME_TESTING. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0104

[Lines 729–733](../../../../../src/runtime/session.cpp#L729); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void RuntimeTestProbe::seed_session_physical_sequence(QuerySession& runtime,std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed physical/window sequence together for boundary tests. |
| inputs / outputs | Testing-only session and u64 sequence. |
| invariants | Requires a window owner and no pending physical/window work or output; test-only probe deliberately bypasses normal monotone input protocol. |
| ownership | Mutates existing Delta/window/session sequence fields only. |
| failure | Invalid probe conditions reject before seeding; valid internal test owner required. |
| cost | Fixed scalar seeding; no fabricated source events or production operation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0105

[Lines 734–734](../../../../../src/runtime/session.cpp#L734); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L734-L734:sha256:9a349bbd1a21104f051e34b2c8a9e70cc7fbb50bc19a67781f2a140c386d9438
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/session.cpp: closes the matching compile-time guard. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0106

[Lines 735–762](../../../../../src/runtime/session.cpp#L735); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_impl(PlanSource plan,const Database* initial,std::unique_ptr<std::istream> input,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one admitted empty/initialized physical-input session. |
| inputs / outputs | PhysicalPlan or CompiledProgram, optional initial Database, owned stream or typed limits, options/window policy and build method. |
| invariants | Typed wire-profile overrides reject; stream mode needs an owned stream. Initial rows are epoch-zero state, not accepted events; managed window tables must initially be empty. |
| ownership | Runtime owns original admitted account; that account funds WindowController, Impl and facade. Initial Database is borrowed only during construction; stream moves into Impl. |
| failure | Validation/build/allocation failure unwinds every unpublished owner. Facade allocation precedes noexcept placement construction. |
| cost | Actual lowering/import/build/source validation and window checks plus funded controls; initial bulk/stream build work is explicit and not ordinary one-update cost. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md § Snapshot initialization](../../../../runtime_initialization.md) |

## B0107

[Lines 763–765](../../../../../src/runtime/session.cpp#L763); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create(PhysicalPlan plan,std::unique_ptr<std::istream> input,SessionOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty stream session from PhysicalPlan. |
| inputs / outputs | PhysicalPlan, owned input stream plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; no initial Database is fabricated. |
| ownership | Moves plan and stream into construction; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0108

[Lines 766–769](../../../../../src/runtime/session.cpp#L766); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create(PhysicalPlan plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create initialized stream session from PhysicalPlan. |
| inputs / outputs | PhysicalPlan, borrowed initial Database/build options, owned input stream plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; supplied initial rows preserve accepted sequence zero. |
| ownership | Moves plan and stream into construction; initial Database is borrowed synchronously; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import/initial-build costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0109

[Lines 770–772](../../../../../src/runtime/session.cpp#L770); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_typed(PhysicalPlan plan,io::QueueLimits limits,SessionOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty typed physical session from PhysicalPlan. |
| inputs / outputs | PhysicalPlan, queue limits plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; no initial Database is fabricated. |
| ownership | Moves plan and options into construction; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0110

[Lines 773–776](../../../../../src/runtime/session.cpp#L773); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_typed(PhysicalPlan plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create initialized typed physical session from PhysicalPlan. |
| inputs / outputs | PhysicalPlan, borrowed initial Database/build options, queue limits plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; supplied initial rows preserve accepted sequence zero. |
| ownership | Moves plan and options into construction; initial Database is borrowed synchronously; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import/initial-build costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0111

[Lines 777–780](../../../../../src/runtime/session.cpp#L777); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_windowed(PhysicalPlan plan,WindowOptions window,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty typed window session from PhysicalPlan. |
| inputs / outputs | PhysicalPlan, queue limits and WindowOptions plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; no initial Database is fabricated. Managed window tables begin empty. |
| ownership | Moves plan and window policy into construction; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0112

[Lines 781–784](../../../../../src/runtime/session.cpp#L781); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_windowed(PhysicalPlan plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create initialized typed window session from PhysicalPlan. |
| inputs / outputs | PhysicalPlan, borrowed initial Database/build options, queue limits and WindowOptions plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; supplied initial rows preserve accepted sequence zero. Managed window tables begin empty. |
| ownership | Moves plan and window policy into construction; initial Database is borrowed synchronously; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import/initial-build costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0113

[Lines 785–787](../../../../../src/runtime/session.cpp#L785); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create(CompiledProgram plan,std::unique_ptr<std::istream> input,SessionOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty stream session from CompiledProgram. |
| inputs / outputs | CompiledProgram, owned input stream plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; no initial Database is fabricated. |
| ownership | Moves plan and stream into construction; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0114

[Lines 788–791](../../../../../src/runtime/session.cpp#L788); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create(CompiledProgram plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create initialized stream session from CompiledProgram. |
| inputs / outputs | CompiledProgram, borrowed initial Database/build options, owned input stream plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; supplied initial rows preserve accepted sequence zero. |
| ownership | Moves plan and stream into construction; initial Database is borrowed synchronously; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import/initial-build costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0115

[Lines 792–794](../../../../../src/runtime/session.cpp#L792); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_typed(CompiledProgram plan,io::QueueLimits limits,SessionOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty typed physical session from CompiledProgram. |
| inputs / outputs | CompiledProgram, queue limits plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; no initial Database is fabricated. |
| ownership | Moves plan and options into construction; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0116

[Lines 795–798](../../../../../src/runtime/session.cpp#L795); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_typed(CompiledProgram plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create initialized typed physical session from CompiledProgram. |
| inputs / outputs | CompiledProgram, borrowed initial Database/build options, queue limits plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; supplied initial rows preserve accepted sequence zero. |
| ownership | Moves plan and options into construction; initial Database is borrowed synchronously; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import/initial-build costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0117

[Lines 799–801](../../../../../src/runtime/session.cpp#L799); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_windowed(CompiledProgram plan,WindowOptions window,io::QueueLimits limits,SessionOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create empty typed window session from CompiledProgram. |
| inputs / outputs | CompiledProgram, queue limits and WindowOptions plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; no initial Database is fabricated. Managed window tables begin empty. |
| ownership | Moves plan and window policy into construction; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0118

[Lines 802–805](../../../../../src/runtime/session.cpp#L802); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::create_windowed(CompiledProgram plan,const Database& initial,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create initialized typed window session from CompiledProgram. |
| inputs / outputs | CompiledProgram, borrowed initial Database/build options, queue limits and WindowOptions plus SessionOptions delegate to create_impl. |
| invariants | The common factory enforces source policy and account admission; supplied initial rows preserve accepted sequence zero. Managed window tables begin empty. |
| ownership | Moves plan and window policy into construction; initial Database is borrowed synchronously; returned AccountedUnique owns stable facade/Impl. |
| failure | Delegated validation/build/resource failures propagate before a session is returned; no catch or fallback build. |
| cost | Constant forwarding plus full create_impl/import/initial-build costs; not a new execution primitive. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0119

[Lines 806–810](../../../../../src/runtime/session.cpp#L806); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::~QuerySession() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy the session with exclusive lifetime and reentry blocked. |
| inputs / outputs | Destructor marks busy then privately drops all mutable resources while Impl is still alive. |
| invariants | Owned-stream destruction may reenter but cannot run a second operation; a caller must never destroy the in-use owner from its own callback. |
| ownership | Facade member later releases Impl/control; immutable returned tuples/captures retain their own account ownership. |
| failure | Noexcept destruction; bypasses throwing public thread checks and uses nonallocating private cleanup. |
| cost | Population-dependent runtime/source/output/candidate destruction and descriptor closure; no cleanup allocation. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0120

[Lines 811–825](../../../../../src/runtime/session.cpp#L811); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::enable_journal(std::string_view checkpoint_path,std::string_view journal_path,const SessionJournalOptions& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach a new journal only to the exact durable baseline. |
| inputs / outputs | Checkpoint path, new journal path and options; current quiescent native image must byte-match stored checkpoint. |
| invariants | Rejects attached/terminal/failed/ended state. Header binds exact image/program/source/policy plus physical/accepted/input-kind bases; File.create never replaces an existing entry. |
| ownership | Current image, loaded bytes and journal use original query account. Session installs File only after create succeeds. |
| failure | Capture/load/equality/create errors propagate; enable cannot claim success with a different baseline. Existing runtime is not advanced. |
| cost | Complete checkpoint encoding and file read/hash/byte comparison, then durable exclusive journal creation. This explicit operation scans state and performs synchronous I/O. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0121

[Lines 826–828](../../../../../src/runtime/session.cpp#L826); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionJournalState QuerySession::journal_state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the last confirmed durable journal lower bound. |
| inputs / outputs | Guarded copy of journal_confirmed, including recovery latch. |
| invariants | During uncertainty this is diagnostic metadata, not permission to resume or retire history. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Public thread/reentrancy errors only; no journal health gate or file scan. |
| cost | Constant field access; no allocation, traversal or state change. |
| Design | [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0122

[Lines 829–832](../../../../../src/runtime/session.cpp#L829); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_journal(CompiledProgram program,std::string_view checkpoint_path,std::string_view journal_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a bound checkpoint/journal without a selected-generation root. |
| inputs / outputs | Expected CompiledProgram, paths, copied replay options and continuation forward to restore_journal_selected with selected=null. |
| invariants | The common factory validates the full prefix and returns paused only after admission; caller output frontier is not durable acknowledgement. |
| ownership | Transfers program/stream; receiving factory owns all funded native/file/output storage. |
| failure | All restore validation/resource/file failures propagate; no partial owner/output returned. |
| cost | Constant forwarding plus complete checkpoint/source/native replay costs. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0123

[Lines 833–836](../../../../../src/runtime/session.cpp#L833); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_journal_with_local_sink(CompiledProgram program,std::string_view checkpoint_path,std::string_view journal_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a bound checkpoint/journal with native durable-sink verification. |
| inputs / outputs | Expected CompiledProgram, paths, copied replay options and continuation, sink path/options forward to restore_journal_selected with selected=null. |
| invariants | The common factory validates the full prefix and returns paused only after admission and actual persisted sink comparison. |
| ownership | Transfers program/stream; receiving factory owns all funded native/file/output storage. |
| failure | All restore validation/resource/file failures propagate; no partial owner/output returned. |
| cost | Constant forwarding plus complete checkpoint/source/native replay/sink verification costs. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0124

[Lines 837–911](../../../../../src/runtime/session.cpp#L837); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_journal_selected(CompiledProgram program,std::string_view checkpoint_path,std::string_view journal_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit and reconstruct a full journal prefix before exposing or repairing state. |
| inputs / outputs | Program, paths, entry-copied options, optional selected root/sink/origin/binding and existing funded root context. |
| invariants | Validates baseline identity and exact selected hashes/frontiers, source/native transitions and sink coverage; stream seek and all semantic checks precede WAL/sink torn-tail repair. Full corrupt frames never authorize repair. |
| ownership | One receiving account funds image/source/runtime/facade/files/backlog. Existing generation context/root owner stays authoritative; sink opens before replay and no output escapes. |
| failure | Any preadmission/native/source/seek/sink/work/heap failure destroys unpublished session before repair. Tail repair I/O may be uncertain; caller must reopen. No persistent final-holder allocation follows successful repairs. |
| cost | Whole image read/validation/materialization/native reconstruction, full journal scan/decode/replay, optional canonical sink verification and bounded missing-output buffering. Separate cumulative budgets do not imply wall-time/RSS bounds. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md), [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0125

[Lines 912–916](../../../../../src/runtime/session.cpp#L912); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionJournalRecoveryStatus QuerySession::recovery_status() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read fixed recovery handoff counters plus current backlog usage. |
| inputs / outputs | Returns recovered_status with live unread output count and retained wrapper/capacity/payload bytes when allocated. |
| invariants | Replay records/work/pending-source fields describe construction, not later journal progress. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Thread/reentrancy checks only; no healthy-writer requirement. |
| cost | Fixed metadata/allocator reads; no output scan or copy. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0126

[Lines 917–925](../../../../../src/runtime/session.cpp#L917); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<RecoveredResult> QuerySession::next_recovered_output() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one identity-bearing recovered output row. |
| inputs / outputs | Healthy started/paused bare recovered session yields optional RecoveredResult. |
| invariants | Rejects private work or attached sink; consuming even one row invalidates complete replay coverage for later sink attachment. |
| ownership | Moves tuple ownership out without allocation; subtracts unread payload bytes and frees buffer when exhausted. |
| failure | Public state/recovery/sink checks can throw before movement; normal move/cleanup is nonthrowing. |
| cost | Fixed record transfer, plus final vector/wrapper/remaining-slot teardown on exhaustion. Returned native row survives session drop. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0127

[Lines 926–926](../../../../../src/runtime/session.cpp#L926); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::discard_recovered_output() {auto& d=*data_;Impl::Guard guard(d);d.available(true);require(!d.local_sink,"local_sink_attached","attached local delivery cannot be discarded");d.recovery_output_complete=false;d.clear_recovered_output();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard retained bare recovery rows explicitly. |
| inputs / outputs | Live/paused session releases complete recovered-output owner and marks coverage incomplete. |
| invariants | Attached local sink prohibits discard; no durable acknowledgement or committed epoch advance. |
| ownership | Releases unread tuples/directory while independent returned rows remain owned by caller. |
| failure | Invalid state/recovery/sink conditions reject before discard. |
| cost | O(retained row slots) cleanup; no new source read or native execution. |
| Design | [docs/native-replay.md](../../../../native-replay.md), [docs/session-journal.md](../../../../session-journal.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0129

[Lines 928–928](../../../../../src/runtime/session.cpp#L928); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::create_local_sink(std::string_view path,const SessionLocalSinkOptions& options) {local_sink_impl(path,options,true);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a new local epoch sink at the journal baseline. |
| inputs / outputs | Path and SessionLocalSinkOptions delegate to local_sink_impl with create=true. |
| invariants | Exclusive sink creation requires exact journal checkpoint boundary. |
| ownership | Common implementation retains original-account sink/schema/file ownership. |
| failure | Delegated state/binding/file/resource failures propagate; no silent fallback. |
| cost | Constant forwarding plus common file creation/scan/validation costs. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0130

[Lines 929–929](../../../../../src/runtime/session.cpp#L929); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::open_local_sink(std::string_view path,const SessionLocalSinkOptions& options) {local_sink_impl(path,options,false);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open or reopen the bound local epoch sink. |
| inputs / outputs | Path and SessionLocalSinkOptions delegate to local_sink_impl with create=false. |
| invariants | Reopen must preserve bound identity and actual durable coverage; it may recover a poisoned attachment. |
| ownership | Common implementation retains original-account sink/schema/file ownership. |
| failure | Delegated state/binding/file/resource failures propagate; no silent fallback. |
| cost | Constant forwarding plus common file creation/scan/validation costs. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0131

[Lines 930–955](../../../../../src/runtime/session.cpp#L930); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::local_sink_impl(std::string_view path,const SessionLocalSinkOptions& requested,bool create) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach/reopen an actual sink while retaining all undelivered output. |
| inputs / outputs | Path, entry-copied options and creation flag; healthy committed journal/source barrier plus complete replay coverage when attaching late. |
| invariants | Creation is only at baseline with no output and no selected delivery anchor. Existing sink identity is preserved; trusted selected-plan origin and authenticated root prefix cannot be replaced by descriptive claims. |
| ownership | Keeps schema/header/work controls; closes old file then marks failed before any replacement file acquisition. Installs new File and clears failed only after all checks/repair succeed. |
| failure | The failed latch is set before replacement file acquisition/check/prefix/repair; every throwing exit leaves it true and ordinary local File unwinding closes the private descriptor. Header/options copies and File move cannot throw; failed=false is the final success statement. The redundant catch has been removed; durable uncertainty and outer session guards remain. |
| cost | Creation/open performs actual file/schema/index validation and possible tail repair; no copy of committed engine state or loss of retained outputs. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0132

[Lines 956–961](../../../../../src/runtime/session.cpp#L956); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionLocalSinkState QuerySession::local_sink_state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe attached sink health, coverage and cumulative delivery costs. |
| inputs / outputs | No attachment gives default state; otherwise copies actual file state or header/base fallback, verification counters and prefix-basis flag. |
| invariants | retirement_verified is descriptive authenticated-basis metadata; healthy current delivery/quiescence/receipt still gate actual retirement. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Thread/reentrancy checks and any File.state contract failure propagate; does not silently reopen the sink. |
| cost | Fixed metadata reads; not a fresh file scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0133

[Lines 962–992](../../../../../src/runtime/session.cpp#L962); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LocalDelivery QuerySession::deliver_local_epoch() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Durably accept exactly the next complete committed physical output epoch. |
| inputs / outputs | Healthy sink and committed barrier; replay backlog or complete live epoch produces RowViews and an append/duplicate result. |
| invariants | Charges cumulative delivery work once per attempt epoch/row, enforces physical order and generation. Empty epochs also append closure; rows are consumed only after successful append/verification. |
| ownership | Borrowed views keep live/replay tuples resident until acceptance; sink owns actual canonical encoding/index/file storage. |
| failure | Typed sink FileFailure marks failed and rethrows; earlier view/work/resource errors retain output. Unknown append is retried only through reopened/verified bound sink. |
| cost | O(epoch rows plus typed wire bytes and canonical sorting/comparison), temporary views/buffers, fsync and cleanup. Actual spent work is retained across failed attempts/reopen. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0134

[Lines 993–996](../../../../../src/runtime/session.cpp#L993); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::sink::Epoch QuerySession::read_local_epoch(std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an accepted local epoch through the attached native sink. |
| inputs / outputs | Physical sequence returns owning native sink::Epoch. |
| invariants | Requires live/paused healthy attached file; does not acknowledge new output or advance session input. |
| ownership | Returned row array/payloads use sink receiving account; file retains original descriptor/index. |
| failure | Typed sink Failure poisons attachment and propagates; resource/codec failures retain their native categories. |
| cost | Explicit file/codec read and typed row materialization; not fixed-cost state inspection. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0135

[Lines 997–999](../../../../../src/runtime/session.cpp#L997); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::sink::Receipt QuerySession::local_sink_receipt() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain a receipt only for fully verified current local delivery. |
| inputs / outputs | Healthy bound sink, no private work and no delivery backlog yield private-constructor Receipt. |
| invariants | A receipt describes actual complete durable prefix, but root checkpoint/native lineage still govern retirement. |
| ownership | Copies fixed immutable authority metadata from the live file; does not detach root/file ownership. |
| failure | State/recovery/sink prefix failures propagate; no caller-constructed frontier substitution. |
| cost | Fixed gate and admitted-prefix metadata access; no full epoch output scan. |
| Design | [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0137

[Lines 1001–1028](../../../../../src/runtime/session.cpp#L1001); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::enable_generation(std::string_view root_path,const SessionGenerationOptions& requested) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the first managed checkpoint/journal/root selection. |
| inputs / outputs | Entry-copied generation policy and root path at a healthy quiescent session. |
| invariants | Requires positive initial generation/retained allowance and no attached writer/root. Complete image and new WAL exist before durable root selects them. |
| ownership | Funds ManagedGeneration before publication; retains original lock/file owner after relevant I/O failure. |
| failure | GenerationFailure or FileFailure latches recovery and preserves managed owner; other failures retain it when selection was attempted. No blind retry after uncertain selection. |
| cost | Full checkpoint/image/hash plus durable checkpoint, WAL and root publication; fixed owner moves only after selection. Unselected candidate files may remain on failed publication. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0138

[Lines 1029–1053](../../../../../src/runtime/session.cpp#L1029); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::promote_journal(std::string_view root_path,const SessionGenerationOptions& requested) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Promote a direct journal into a managed root at a complete input barrier. |
| inputs / outputs | New root path/policy, exact query identity and existing journal generation. |
| invariants | Rejects pending/cached/queued input, failed/ended source and unverified sink prefix. Next generation=old+1, not arbitrary requested starting generation. |
| ownership | Preallocates new generation holder/files; SelectionGuard preserves fresh holder/lock on selection uncertainty. |
| failure | Preselection preparation errors retain old writer; root selection attempt/change requires recovery, with original authority preserved. |
| cost | Full quiescent image materialization plus checkpoint/WAL/root I/O; no input event or output epoch is fabricated. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp) |

## B0139

[Lines 1054–1087](../../../../../src/runtime/session.cpp#L1054); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::rotate_generation() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rotate to a new pair under the same authoritative root. |
| inputs / outputs | Healthy managed session, no pending journal input and retained-generation capacity. |
| invariants | Quiescent checkpoint capture enforces private/output/delivery/queue barriers; selected plan descriptors and sink prefix lineage are carried into next root. |
| ownership | Same ManagedGeneration/root lock owns candidate files; optional new plan bytes are funded before selection. |
| failure | SelectionGuard latches recovery after attempted/changed root; before selection, preparation can fail with old selected owner intact. |
| cost | Complete image/optional descriptor encode/hash and file publications; retains old history and actual old/new buffers. No automatic retirement. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0140

[Lines 1088–1111](../../../../../src/runtime/session.cpp#L1088); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::retire_generation_history() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire history only after actual native checkpoint and durable sink proof. |
| inputs / outputs | Quiescent managed writer plus healthy authenticated sink receipt through committed boundary. |
| invariants | Checks query/plan/sink lineage, exact receipt bytes/hash, selected checkpoint sequences/binding and private root anchor. Caller reports cannot authorize deletion. |
| ownership | Existing generation/root lock drives recoverable retirement intent and cleanup; no reacquisition or external acknowledgement assumption. |
| failure | Typed GenerationFailure latches recovery and rethrows; validation/resource failures before retirement do not guess success. |
| cost | Explicit checkpoint read/validation and durable intent/root/history deletion work proportional to retained files/bytes; never an ordinary commit side effect. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/local-sink.md](../../../../local-sink.md), [include/crown/runtime/session_local_sink.hpp](../../../../../include/crown/runtime/session_local_sink.hpp), [include/crown/recovery/local_sink.hpp](../../../../../include/crown/recovery/local_sink.hpp), [docs/history-retirement.md](../../../../history-retirement.md) |

## B0141

[Lines 1112–1116](../../../../../src/runtime/session.cpp#L1112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionGenerationState QuerySession::generation_state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe selected generation and pending retirement state. |
| inputs / outputs | Default when absent; else selected root, recovery flag, cumulative I/O/validation work and intent frontiers. |
| invariants | An uncertain selected value is diagnostic; it does not authorize retry/retirement/resume. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Guard errors only on valid internal owner; no journal health gate. |
| cost | Fixed metadata copies from existing owner, not directory enumeration. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0142

[Lines 1117–1120](../../../../../src/runtime/session.cpp#L1117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_generation(CompiledProgram program,std::string_view root_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a legacy managed generation. |
| inputs / outputs | Expected program/root/options/continuation delegate to restore_generation_impl. |
| invariants | Authoritative root chooses generation; legacy entry rejects descriptor-bearing selected roots and pending retirement requires sink-aware recovery. |
| ownership | Moves program/stream to common factory, which preserves original root lock and receiving account. |
| failure | Delegated admission/replay/file/native failures propagate with no partial owner exposed. |
| cost | Constant forwarding plus root/checkpoint/full replay costs. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0143

[Lines 1121–1124](../../../../../src/runtime/session.cpp#L1121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_generation_with_local_sink(CompiledProgram program,std::string_view root_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a legacy managed generation with durable sink verification. |
| inputs / outputs | Expected program/root/options/continuation plus sink path/options delegate to restore_generation_impl. |
| invariants | Authoritative root chooses generation; legacy entry rejects descriptor-bearing selected roots and validates attached sink/retirement. |
| ownership | Moves program/stream to common factory, which preserves original root lock and receiving account. |
| failure | Delegated admission/replay/file/native failures propagate with no partial owner exposed. |
| cost | Constant forwarding plus root/checkpoint/full replay/sink costs. |
| Design | [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0144

[Lines 1125–1155](../../../../../src/runtime/session.cpp#L1125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_generation_impl(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reconstruct a legacy selected generation while retaining its original root lock and funding final owners before tail repair. |
| inputs / outputs | Expected native program, root/replay limits, optional sink and continuation stream in; ready recovered session owner out. |
| invariants | Reject descriptor-bearing v3 roots on this legacy entry point. Enforce retained-generation limits and sink requirements before reconstruction. |
| ownership | Move GenerationOwner into a receiving-account ManagedGeneration before restore_journal_selected; pass that same file/context through reconstruction; install the holder by move. |
| failure | Final-holder allocation and native reconstruction admission precede validated WAL/sink tail repair. Rejected admission unwinds the same lock; final holder installation is nonthrowing. If retirement intent exists, the later retire_generation_history call can independently fail after reconstruction/repair and follows its separately recoverable intent protocol. |
| cost | Full checkpoint/replay I/O and native reconstruction plus funded metadata setup. Pending retirement resumption is a later explicit checkpoint-validation/history-cleanup cost and can have its own failure; no ordinary update or constant-latency claim. |
| Design | [docs/generations.md](../../../../generations.md), [docs/native-replay.md](../../../../native-replay.md), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0146

[Lines 1157–1183](../../../../../src/runtime/session.cpp#L1157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LockedGenerationRecovery::Owner QuerySession::lock_generation_recovery(CompiledProgram expected,std::string_view root_path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lock and inspect selected recovery authority before caller artifact replay. |
| inputs / outputs | Expected admitted source, root path and immutable recovery policy. |
| invariants | Authoritative selected root and retained generations are checked; descriptor must bind expected source/catalog, frontiers and sink presence/identity. No caller-selected physical override. |
| ownership | Acquires root once; funds receiving context, selected ManagedPlan, Data and facade while retaining that same GenerationOwner. Artifact view borrows this owner. |
| failure | Read/descriptor/binding/cap/allocation errors unwind original lock before native replay or any tail repair. |
| cost | Root/checkpoint-header/descriptor file validation, hashing and native descriptor retention plus control admission; no query state reconstruction yet. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp), [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0147

[Lines 1184–1187](../../../../../src/runtime/session.cpp#L1184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_selected_generation(LockedGenerationRecovery::Owner input,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume locked selected-plan recovery. |
| inputs / outputs | LockedGenerationRecovery::Owner and checked CompilerPlanArtifact forward with continuation to restore_locked_generation. |
| invariants | Consumes the same root-lock owner; artifact must reproduce selected descriptor/source exactly, not just a compatible query. |
| ownership | Unique recovery input transfers into common reconstruction; facade/stream and native receiving storage are not copied. |
| failure | Common factory errors propagate and release consumed input; no relock or fallback plan selection. |
| cost | Constant forwarding plus complete selected native replay costs. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0148

[Lines 1188–1191](../../../../../src/runtime/session.cpp#L1188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_selected_generation_with_local_sink(LockedGenerationRecovery::Owner input,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume locked selected-plan recovery with an actual local sink. |
| inputs / outputs | LockedGenerationRecovery::Owner and checked CompilerPlanArtifact plus sink path/options forward with continuation to restore_locked_generation. |
| invariants | Consumes the same root-lock owner; artifact must reproduce selected descriptor/source exactly, not just a compatible query. |
| ownership | Unique recovery input transfers into common reconstruction; facade/stream and native receiving storage are not copied. |
| failure | Common factory errors propagate and release consumed input; no relock or fallback plan selection. |
| cost | Constant forwarding plus complete selected native replay/sink verification costs. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0149

[Lines 1192–1215](../../../../../src/runtime/session.cpp#L1192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_locked_generation(LockedGenerationRecovery::Owner input,const io::CompilerPlanArtifact& artifact,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the descriptor-selected artifact and reconstruct while retaining the original lock. |
| inputs / outputs | Consumed locked owner, CompilerPlanArtifact, optional sink policy and continuation. |
| invariants | Checks source/index options and exact artifact/physical hash; legacy root requires expected physical hash. Selected sink-origin/retirement cannot bypass sink-aware recovery. |
| ownership | Funds final ManagedGeneration in locked receiving context before replay, moves original root/plan into it, installs holder by noexcept move after restore. |
| failure | Binding/admission/allocation failures precede repair; native replay rejects without exposing owner. Pending retirement resumes as its separate recoverable cleanup before final return. |
| cost | Complete selected checkpoint/source/journal/native/sink reconstruction plus descriptor matching; no late final-holder allocation or new memory allowance after repair. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp), [docs/generations.md](../../../../generations.md), [include/crown/runtime/session_generation.hpp](../../../../../include/crown/runtime/session_generation.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0151

[Lines 1217–1217](../../../../../src/runtime/session.cpp#L1217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionCheckpoint QuerySession::checkpoint_state() const {return checkpoint_state(SessionCheckpointLimits{});}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a session checkpoint with default native limits. |
| inputs / outputs | Delegates to checkpoint_state(SessionCheckpointLimits{}). |
| invariants | Same quiescent/sequence rules as the explicit-limits overload; defaults are not a hidden recovery shortcut. |
| ownership | Returns owning native checkpoint/image storage under runtime account. |
| failure | Delegated state/resource failure propagates without changing execution. |
| cost | Constant forwarding plus complete checkpoint capture cost. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0152

[Lines 1218–1254](../../../../../src/runtime/session.cpp#L1218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionCheckpoint QuerySession::Impl::checkpoint(const SessionCheckpointLimits& limits,const DeltaRuntime* replacement) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture the exact quiescent source/window/native checkpoint boundary. |
| inputs / outputs | Native limits and optional same-sequence replacement runtime yield SessionCheckpoint with native runtime image. Select state version from declaration presence and capture immutable declaration/origins/first violation. |
| invariants | Requires healthy journal, retained writer-ready runtime, no private/live/replay output, no undelivered closure and empty queue. Validates source/runtime and completed-window frontiers; no serialized private/cached input is invented. Validate copy_usage against finite pattern limits before returning; the native checkpoint shares the original immutable declaration rather than cloning it. |
| ownership | Retains native option/context metadata and copies source/window/checkpoint storage using original account. Replacement changes only runtime image/options, not source/window ownership. |
| failure | Busy/sequence/options/window/source/image/resource failures propagate; no input is acknowledged, drained or repaired. |
| cost | Explicit full source/window checkpoint and runtime image encoding; population/bytes-dependent with simultaneous images and fixed control overhead. Pattern metadata adds fixed grant checks/handle and scalar copies; subsequent serialization/receiving import has its own O(R) costs. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0153

[Lines 1255–1257](../../../../../src/runtime/session.cpp#L1255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionCheckpoint QuerySession::checkpoint_state(const SessionCheckpointLimits& limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard and capture a session checkpoint with caller limits. |
| inputs / outputs | Public native limits are forwarded to Impl.checkpoint under one writer/reentry Guard. |
| invariants | Thread/state/barrier checks precede full checkpoint materialization. |
| ownership | Returned native checkpoint owns its image/options/progress; session remains live. |
| failure | Capture/guard/resource errors propagate; no fallback snapshot. |
| cost | Fixed guard plus full checkpoint traversal/copy/encoding. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0154

[Lines 1258–1258](../../../../../src/runtime/session.cpp#L1258); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::SessionImage QuerySession::checkpoint_image() const {return checkpoint_image(SessionCheckpointLimits{},recovery::SessionImageLimits{});}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a session envelope with default native and wire limits. |
| inputs / outputs | Delegates to checkpoint_image with the two default limit records. |
| invariants | Defaults preserve the same quiescent capture and exact binding rules. |
| ownership | Returns original-account SessionImage bytes. |
| failure | Delegated capture/codec/resource failures propagate. |
| cost | Constant forwarding plus full checkpoint/envelope encoding. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0155

[Lines 1259–1262](../../../../../src/runtime/session.cpp#L1259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::SessionImage QuerySession::checkpoint_image(const SessionCheckpointLimits& native,const recovery::SessionImageLimits& limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a complete native session checkpoint envelope. |
| inputs / outputs | Caller native/wire limits, guarded Impl.checkpoint and original account produce SessionImage. |
| invariants | All source/window/runtime state is validated at one committed barrier before encoding. |
| ownership | Temporary checkpoint/native image and final envelope coexist under same query cap. |
| failure | Barrier/capture/codec/resource failure preserves session and unread output; no file publication. |
| cost | Full native snapshot and envelope byte visits, allocations/hash work; explicit diagnostic/persistence operation. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0156

[Lines 1263–1265](../../../../../src/runtime/session.cpp#L1263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore encoded session bytes with default restore and image limits. |
| inputs / outputs | Program, borrowed envelope bytes and owned continuation delegate to explicit-limits restore_image. |
| invariants | Same complete validation/funded reconstruction; byte view must outlive synchronous call. |
| ownership | Moves program/continuation; caller retains borrowed bytes until return; returned owner uses admitted receiving account. |
| failure | Delegated validation/admission/native failures propagate; no exposed partial state. |
| cost | Constant forwarding plus complete decode/reconstruction cost. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0157

[Lines 1266–1269](../../../../../src/runtime/session.cpp#L1266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,const SessionRestoreOptions& options,
    std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore encoded session bytes with caller restore options and default image limits. |
| inputs / outputs | Program, borrowed envelope bytes and owned continuation delegate to explicit-limits restore_image. |
| invariants | Same complete validation/funded reconstruction; byte view must outlive synchronous call. |
| ownership | Moves program/continuation; caller retains borrowed bytes until return; returned owner uses admitted receiving account. |
| failure | Delegated validation/admission/native failures propagate; no exposed partial state. |
| cost | Constant forwarding plus complete decode/reconstruction cost. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0158

[Lines 1270–1280](../../../../../src/runtime/session.cpp#L1270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,const SessionRestoreOptions& options,
    const recovery::SessionImageLimits& limits,std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and reconstruct an encoded session in a receiving account. |
| inputs / outputs | Program, envelope view, restore options/wire limits and optional continuation. |
| invariants | Full session validation precedes materialization; stream continuation exists exactly for a nonstopped owned-stream input. Saved cap applies unless explicitly overridden. |
| ownership | New StorageWorkContext funds decoded envelope and runtime; restore_funded receives native runtime-byte view valid through synchronous reconstruction. |
| failure | Corrupt envelope/stream mismatch, cap/admission/materialization/restore failure unwinds unpublished owners; no durable file or source repair. |
| cost | Envelope validation and full native materialization/reconstruction; memory includes encoded input plus receiving native temporaries and final state. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0159

[Lines 1281–1284](../../../../../src/runtime/session.cpp#L1281); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_state(CompiledProgram program,const SessionCheckpoint& state,
    std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore native checkpoint state with default receiving options. |
| inputs / outputs | Program, native SessionCheckpoint and optional owned continuation delegate to restore_state(options={}). |
| invariants | Same saved-version/source/runtime identity checks; not a merge into an existing session. |
| ownership | Borrowed state remains caller-owned; new receiving runtime imports it. |
| failure | Delegated restore errors propagate before owner return. |
| cost | Constant forwarding plus full native reconstruction. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0160

[Lines 1285–1287](../../../../../src/runtime/session.cpp#L1285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::PublishedCheckpoint QuerySession::checkpoint_file(std::string_view path) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a standalone session checkpoint with default limits. |
| inputs / outputs | Path delegates to checkpoint_file(default native,file limits). |
| invariants | The guarded explicit method rejects an attached journal. |
| ownership | Public file publisher owns durable publication; returned metadata describes that result. |
| failure | Delegated state/file/native/resource failures propagate. |
| cost | Constant forwarding plus full image capture and durable file publication. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0161

[Lines 1288–1294](../../../../../src/runtime/session.cpp#L1288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::PublishedCheckpoint QuerySession::checkpoint_file(std::string_view path,const SessionCheckpointLimits& native,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish an unjournaled quiescent session checkpoint file. |
| inputs / outputs | Path/native/file limits produce captured image then publish_session_image result. |
| invariants | Attached journal rejects before capture, protecting its active baseline/log pair from replacement. |
| ownership | Image bytes and temporary native checkpoint use original account; publisher performs its own durable file ownership. |
| failure | Busy/codec/allocation/file failure propagates. A file publication outcome is governed by publisher; no session update occurred. |
| cost | Complete native/image materialization plus durable file write/hash/fsync/publication; no per-update cost claim. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [include/crown/recovery/session_file.hpp](../../../../../include/crown/recovery/session_file.hpp) |

## B0162

[Lines 1295–1297](../../../../../src/runtime/session.cpp#L1295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a standalone checkpoint file with default restore and file limits. |
| inputs / outputs | Program/path/continuation delegate to full restore_file. |
| invariants | No journal replay, root selection or raw stream-position guessing is implied. |
| ownership | Moves program/stream; common factory admits receiving account/native owner. |
| failure | Delegated path/file/image/source/native failures propagate. |
| cost | Constant forwarding plus full file validation/materialization/reconstruction. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0163

[Lines 1298–1301](../../../../../src/runtime/session.cpp#L1298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,const SessionRestoreOptions& options,
    std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a standalone checkpoint file with caller restore options and default file limits. |
| inputs / outputs | Program/path/continuation delegate to full restore_file. |
| invariants | No journal replay, root selection or raw stream-position guessing is implied. |
| ownership | Moves program/stream; common factory admits receiving account/native owner. |
| failure | Delegated path/file/image/source/native failures propagate. |
| cost | Constant forwarding plus full file validation/materialization/reconstruction. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0164

[Lines 1302–1313](../../../../../src/runtime/session.cpp#L1302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,const SessionRestoreOptions& options,
    const recovery::CheckpointFileLimits& limits,std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load a standalone session image and reconstruct its admitted native owner. |
| inputs / outputs | Program/path/options/file limits and continuation. |
| invariants | File reader validates its bounded trusted file; explicit memory cap or saved cap funds all receiving bytes. Continuation presence matches source kind/control. |
| ownership | Receiving context owns file byte buffer, decoded state and final runtime/source/facade; caller continuation is moved. |
| failure | Path/file/image/stream/admission/resource errors destroy unpublished construction; this API does not repair a journal tail. |
| cost | Full file read/hash/validation plus full envelope/native reconstruction; not lazy restore or constant metadata work. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0165

[Lines 1314–1318](../../../../../src/runtime/session.cpp#L1314); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_state(CompiledProgram program,const SessionCheckpoint& state,
    const SessionRestoreOptions& options,std::unique_ptr<std::istream> continuation) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore caller-owned native checkpoint state with explicit options. |
| inputs / outputs | Program/state/options/continuation; passes state.runtime_image bytes directly to restore_funded. |
| invariants | Native state still requires full source/version/profile/binding validation; it is not trusted merely because it is a C++ object. |
| ownership | State/byte view borrowed for synchronous call; receiving factory funds imported native state. |
| failure | Delegated restore failures propagate with caller checkpoint unchanged. |
| cost | Constant forwarding plus complete native reconstruction; no intermediate owning byte export. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0166

[Lines 1319–1377](../../../../../src/runtime/session.cpp#L1319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
QuerySession::Owner QuerySession::restore_funded(CompiledProgram program,const SessionCheckpoint& state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate native session shape and fund the final reconstructed session. |
| inputs / outputs | Expected program, native checkpoint/options/continuation, optional already-funded StorageWorkContext and native runtime-byte view. |
| invariants | Checks version/control/source variants, continuation, no failed live source/private window command, accepted/frontier consistency and typed default profile. Runtime restores exact program/window identity and matching under finite limits. Require version/declaration agreement, actual source binding, bounded ordered origins (equal domains without window), and a failed next-command violation whose kind/label agrees with the declaration and source kind. Public checkpoint history is trusted, not authenticated. |
| ownership | All restored runtime/source/window/context/Impl/facade allocations use one receiving account; runtime context can be reused from locked recovery. |
| failure | Corrupt/source/native/build/cap/allocation failures unwind before returning any owner. Facade allocation precedes noexcept placement construction. |
| cost | Full native runtime/source/window image validation/reconstruction and source-position option copies; no fresh allowance per replay input. Fixed pattern checks/source hash and O(log R) violation rule lookup precede funded reconstruction; restore constructor separately validates/copies R rules. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session_checkpoint.hpp](../../../../../include/crown/runtime/session_checkpoint.hpp), [docs/native-replay.md](../../../../native-replay.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0167

[Lines 1378–1386](../../../../../src/runtime/session.cpp#L1378); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionStatus QuerySession::status() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current fixed session control/phase/progress diagnostics. |
| inputs / outputs | Guarded status includes physical sequence, sticky failure/EOF, optional pending sequence/work, output count and queue/window progress. |
| invariants | Private diagnostics do not expose tentative query rows; empty closure can be output phase with output_remaining=0. |
| ownership | Returns fixed-size values/optionals only, retaining no mutable token. Optional pattern status retains an immutable declaration handle and fixed current-tree/progress metadata; it clones no rule vector. |
| failure | Thread/reentry guard errors propagate; status is readable after stop/drop and does not require journal health. |
| cost | Fixed access to existing metrics/counts; no source-map export, output scan or native drain. Pattern-status copy adds fixed fields/refcount, with O(R) teardown only on final declaration-owner release. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0168

[Lines 1387–1391](../../../../../src/runtime/session.cpp#L1387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1387-L1391:sha256:aa99ef02b26f98611c55e178db70f472e341da27b3086d31d277848849d3d2f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the current committed pattern diagnostic through the Session guard. |
| inputs / outputs | Require an active owning runtime and return Impl::pattern_status(). |
| invariants | Dropped Sessions cannot manufacture an actual current-tree profile. An undeclared active Session returns an empty declaration; it has no enforcement claim. |
| ownership | Return fixed data plus immutable declaration handle; no runtime row ownership escapes. |
| failure | Existing availability/creator-thread/reentry Error paths; no extra translation or catch. |
| cost | Fixed guard/status copy; no rule cloning or clock, with possible O(R) final metadata-owner teardown. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md) |

## B0169

[Lines 1392–1395](../../../../../src/runtime/session.cpp#L1392); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::InputProgress QuerySession::progress() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export accepted input progress without advancing source. |
| inputs / outputs | Non-dropped session returns export_accepted(). |
| invariants | Cached decoded/queued input is excluded until whole logical command completion. |
| ownership | Caller-owned InputProgress copies source-position/name values. |
| failure | Dropped rejects; allocation can fail while native progress/output remains intact. |
| cost | O(accepted position entries/name bytes) export, even though status() is fixed metadata. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0170

[Lines 1396–1398](../../../../../src/runtime/session.cpp#L1396); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::begin_reoptimization(const planner::MinimumHeightCandidate& candidate,reoptimization::Options options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an explicit reoptimization candidate with zero external selection cost. |
| inputs / outputs | MinimumHeightCandidate and Options delegate to begin_reoptimization_with_cost(selection_ns=0). |
| invariants | Candidate preparation does not authorize publication or recovery plan substitution. |
| ownership | Common operation keeps old owner and target/ledger on original query account. |
| failure | Delegated barrier/admission/rebuild failures propagate without publishing a new runtime. |
| cost | Constant forwarding plus full candidate snapshot/rebuild costs. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0171

[Lines 1399–1411](../../../../../src/runtime/session.cpp#L1399); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::begin_reoptimization_with_cost(const planner::MinimumHeightCandidate& candidate,reoptimization::Options options,std::uint64_t selection_ns) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an unpublished target from the delivered committed old-plan barrier. |
| inputs / outputs | Checked candidate/options and selection_ns. |
| invariants | Requires no active candidate, private work, live/replay output or delivery backlog; runtime must be writer-ready at committed sequence. Old session can process after preparation until freeze. |
| ownership | Funds one candidate State on original account; builds target/ledger while retaining old runtime. Installs only completely constructed State. |
| failure | Guard/state/candidate/budget/resource errors propagate; failed unpublished construction preserves existing old runtime and any prior inactive diagnostic state. |
| cost | Full source snapshot/rebuild/bootstrap plus control admission/selection timing, real old/target overlap; no per-update background rebuild is implied. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0172

[Lines 1412–1416](../../../../../src/runtime/session.cpp#L1412); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::request_reoptimization_barrier() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze future admission through the active candidate barrier. |
| inputs / outputs | Active candidate receives request_barrier(). |
| invariants | Already admitted cached/typed/window commands still need old-plan completion and ordinary output delivery; this does not itself drain them. |
| ownership | Mutates candidate phase only; keeps original source/runtime/file owners. |
| failure | Inactive/state/recovery errors reject without fabricated verification. |
| cost | Fixed candidate phase/policy bookkeeping; no source read. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0173

[Lines 1417–1450](../../../../../src/runtime/session.cpp#L1417); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Status QuerySession::advance_reoptimization(std::uint64_t quantum) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance target/catch-up work and drain only already admitted old-plan input. |
| inputs / outputs | Quantum limits coordinator iterations and delegates remaining candidate work. |
| invariants | Frozen progress waits for all old output/delivery and admitted/private/pending-WAL/window commands; only caught-up frozen target is verified. Each old drain uses normal journaling/publication obligations. |
| ownership | Old source/runtime and candidate remain session-owned; no private target output escapes. |
| failure | Any old begin/step/finish failure aborts session private work, cancels candidate with failed/recovery_required phase and rethrows; candidate internal policy remains authoritative. |
| cost | Each quantum unit can trigger real native begin/step/commit/WAL work; final verification compares full source/SQL results under its own bounds. Quantum is not a time or constant-work guarantee. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0174

[Lines 1451–1455](../../../../../src/runtime/session.cpp#L1451); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::cancel_reoptimization() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel an active/inactive candidate without bypassing old-plan recovery. |
| inputs / outputs | Healthy journal guard then optional candidate.cancel(). |
| invariants | Cancellation does not reset authoritative recovery_required or commit/acknowledge source. |
| ownership | Releases candidate private runtime/ledger per State policy, retains diagnostic control and old owner. |
| failure | Thread/reentry/recovery failures precede cancellation; valid cancellation is nonthrowing cleanup. |
| cost | Actual target/ledger teardown can be population-sized; no input read or full-state rollback of old committed owner. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0175

[Lines 1456–1458](../../../../../src/runtime/session.cpp#L1456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Status QuerySession::reoptimization_status() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read existing candidate phase/cost diagnostics. |
| inputs / outputs | Returns candidate.status() or default when no candidate exists. |
| invariants | verified/phase diagnostics are not root selection, durable output receipt or minimum-height proof authority. |
| ownership | Returns copied scalar metadata or a view borrowing the live stated owner. |
| failure | Thread/reentry guard errors only; no healthy-writer gate. |
| cost | Fixed status copy; no rebuild/verification/advancement. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0176

[Lines 1459–1511](../../../../../src/runtime/session.cpp#L1459); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
reoptimization::Status QuerySession::publish_reoptimization(const io::CompilerPlanArtifact& artifact,reoptimization::PublicationOptions requested) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Durably select and install a verified replacement physical runtime. |
| inputs / outputs | Checked CompilerPlanArtifact and descriptor limits at healthy complete old input/window/output/delivery boundary. |
| invariants | Requires managed root, unfinished healthy source and matching target artifact. Prepares target checkpoint/context/plan/WAL and immutable sink lineage before root selection; verified alone is insufficient. |
| ownership | Original account bears old/target/checkpoint/descriptor overlap. SelectionGuard retains root authority; prepared owner moves install target without replacing source/window/delivery ownership. |
| failure | Preselection allocation/codec/policy failure keeps old owner. Attempted/changed durable root latches recovery; successful selection is followed only by noexcept install/cleanup, never ordinary rollback. |
| cost | Full image/descriptor/schema work, candidate policy clocks, durable file/fsync/root operations and old-runtime/image teardown. Costs include irreversible prepared files even if policy declines selection. |
| Design | [docs/reoptimization.md § Required session protocol](../../../../reoptimization.md), [docs/reoptimization.md § Durable selection and sink lineage](../../../../reoptimization.md), [include/crown/runtime/session_reoptimization.hpp](../../../../../include/crown/runtime/session_reoptimization.hpp) |

## B0177

[Lines 1512–1518](../../../../../src/runtime/session.cpp#L1512); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::start() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start or resume admission and private producer stepping. |
| inputs / outputs | Created/running/paused control becomes running; paused pending Delta token resumes when applicable. |
| invariants | Stopped/dropped remain terminal. This method does not check/reset journal recovery, consume source, or publish output; subsequent advancement still enforces health. |
| ownership | Retains the same pending token and source/runtime owners. |
| failure | Terminal/Guard errors propagate; resume uses existing native pause-state contract. |
| cost | Fixed control/state work; no replay/rebuild. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0178

[Lines 1519–1526](../../../../../src/runtime/session.cpp#L1519); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::pause() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pause session admission and producer stepping. |
| inputs / outputs | Live started/paused control; actual pending_delta token is paused, then control becomes paused. |
| invariants | Draining/prepared/output have no Delta pause state; explicit drain/output operations can remain allowed. Paused call is idempotent. |
| ownership | Keeps private/committed output and source ownership. |
| failure | Journal/control/Guard errors reject before mutation; no rollback of a valid private token. |
| cost | Fixed control/pending-state work; no output scan or source read. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0179

[Lines 1527–1529](../../../../../src/runtime/session.cpp#L1527); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
io::Admission QuerySession::enqueue(io::TransportBatch& batch) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a bounded typed transport batch. |
| inputs / outputs | Caller-owned TransportBatch passes guarded admission_available then TypedQueue.enqueue. |
| invariants | Created allowed; paused/terminal/frozen/stream/recovery-required reject. Queue handles full without consuming caller ownership. |
| ownership | Accepted queue imports native items under original account; rejected/full batch stays with caller. |
| failure | Queue semantic/resource/admission failures retain existing native source rules; no engine begin/acknowledgement. |
| cost | Batch validation/import visits rows/values with bounded queue storage; not a constant scalar operation. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/batches_windows.md](../../../../batches_windows.md), [docs/session_lifecycle.md § Native typed input ownership](../../../../session_lifecycle.md) |

## B0180

[Lines 1530–1532](../../../../../src/runtime/session.cpp#L1530); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::finish_input() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close typed input admission at an allowed boundary. |
| inputs / outputs | Healthy unpaused typed session calls queue.finish(). |
| invariants | Does not consume queued commands or mark session EOF until begin observes closed-empty queue. |
| ownership | Queue/source remain owned for later processing. |
| failure | Admission/queue state errors propagate without fabricating EOF. |
| cost | Fixed queue closure; no native update or read-ahead. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0181

[Lines 1533–1535](../../../../../src/runtime/session.cpp#L1533); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionBegin QuerySession::begin_next_result() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose tri-state begin without conflating backpressure with EOF. |
| inputs / outputs | One Guard delegates Impl.begin(). |
| invariants | pending creates private work; would_block covers empty-open queue/delivery/freeze; end is validated source exhaustion. |
| ownership | Retains cached source and any pending work inside session. |
| failure | All begin state/decode/native errors propagate after documented abort/sticky handling. |
| cost | Fixed forwarding plus current-command decode/WAL/native preparation. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0182

[Lines 1536–1541](../../../../../src/runtime/session.cpp#L1536); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool QuerySession::begin_next() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose legacy Boolean begin with explicit would-block error. |
| inputs / outputs | Impl.begin() result becomes true for pending, false for end. |
| invariants | would_block throws input_would_block rather than reporting EOF; this can include candidate freeze as well as empty queue or delivery. |
| ownership | Same private/cached source ownership as tri-state begin. |
| failure | State/begin errors propagate; would-block Error is constructed after no new private work was admitted. |
| cost | Current-command begin costs plus fixed result check. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0183

[Lines 1542–1546](../../../../../src/runtime/session.cpp#L1542); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaStep QuerySession::step() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one private physical producer step or prepare metadata-only window work. |
| inputs / outputs | Started unpaused pending input returns DeltaStep; no physical token marks metadata_ready=true. |
| invariants | Public output remains inaccessible until later prepared commit; invalid phase checks do not abort existing work. |
| ownership | Session retains native/window tokens and original work allowance. |
| failure | Any native step failure aborts all session private/candidate-stage state then rethrows; cached input stays unacknowledged. |
| cost | One actual Delta producer step, including its qualified preparation/finalization costs; metadata-only step is fixed. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0184

[Lines 1547–1555](../../../../../src/runtime/session.cpp#L1547); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::commit() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit exactly one prepared private input/substep. |
| inputs / outputs | Physical token must be epoch_prepared, or metadata_ready must be true; calls finish(false). |
| invariants | finish writes/syncs decision before nonthrowing native/window publication and source acknowledgement; nonfinal watermark preserves accepted command. |
| ownership | Moves retained committed output into session; source/pending lifetime is resolved only at publication. |
| failure | Invalid preparation rejects without abort; actual finish failure aborts and applies journal recovery latch as required. |
| cost | Durable decision encoding/I/O plus nonallocating publication and actual staged-owner cleanup; no constant latency. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0185

[Lines 1556–1561](../../../../../src/runtime/session.cpp#L1556); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::start_drain() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable private output retention before completing the current input. |
| inputs / outputs | Healthy started/paused private input; metadata-only marks draining or native token.start_drain. |
| invariants | Attached sink rejects discarding; no later input is read and paused control remains paused. |
| ownership | Keeps current native/window owner; releases native output retention per producer policy. |
| failure | Native start_drain failure aborts all session private work and rethrows; phase/state/sink rejection does not abort. |
| cost | Native retained-output cleanup and fixed mode change; maintenance completion remains owed. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0186

[Lines 1562–1575](../../../../../src/runtime/session.cpp#L1562); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::drain() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete/discard only the current native/window/output artifact. |
| inputs / outputs | Healthy started/paused bare session; pending physical drains, metadata finishes, published output discards, otherwise replay buffer clears. |
| invariants | Never reads another source event. Journaled physical drain still syncs a decision before publication; attached sink prohibits this path. |
| ownership | Retains source head through failure, transfers committed progress only on successful finish, releases output/journals/pins on discard. |
| failure | Producer/journal failure aborts private work and preserves original diagnostic; recovery latch remains authoritative. Invalid calls do not silently cancel sink obligations. |
| cost | Potential complete affected-update production/draining and WAL fsync, plus buffer/token destruction; not bounded by one producer quantum. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/session-journal.md](../../../../session-journal.md), [include/crown/runtime/session_journal.hpp](../../../../../include/crown/runtime/session_journal.hpp), [docs/native-replay.md](../../../../native-replay.md) |

## B0187

[Lines 1576–1583](../../../../../src/runtime/session.cpp#L1576); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SignedResult> QuerySession::next_output() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one committed ordinary signed result row. |
| inputs / outputs | Live/paused session without sink/private/replay backlog returns optional owning SignedResult. |
| invariants | Cannot observe prepared private rows or bypass identity-bearing replay API; exhaustion destroys even the inactive epoch owner. |
| ownership | Moves native tuple to caller; session releases final output journals/source pins when inactive. |
| failure | State/recovery/Guard errors occur before access; underlying committed Epoch owns its documented next/cleanup failure behavior. |
| cost | One output transfer and fixed summary copy; final epoch cleanup can release retained journals/source pins. No result-history copy. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0188

[Lines 1584–1617](../../../../../src/runtime/session.cpp#L1584); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionSnapshot QuerySession::snapshot(std::optional<SnapshotLimits> limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize a bounded immutable snapshot of actual committed results. |
| inputs / outputs | Optional SnapshotLimits override defaults; result contains physical sequence, exported accepted progress, layout, rows, bytes and optional window progress. |
| invariants | Rejects dropped/private state; allows epoch-zero, stopped and committed unread output. Counts actual control/capacity/native tuple requests; byte sublimit excludes shared metadata/progress/cursor scratch while full query cap includes them. |
| ownership | Local result cursor borrows committed runtime under its reader lease; returned native tuples/directory retain original account. Session output is neither consumed nor drained. |
| failure | Row/byte/overflow/cursor/resource failure releases local lease/partial snapshot and preserves source/committed output. |
| cost | Explicit full result enumeration plus source-map export and bounded geometric directory growth, native payloads, cursor scratch and cleanup; no constant public delay or ordinary update cost claim. |
| Design | [docs/session_lifecycle.md § Bounded owning snapshots](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0189

[Lines 1618–1624](../../../../../src/runtime/session.cpp#L1618); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<WindowCanonicalState> QuerySession::window_state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export current committed operational window state. |
| inputs / outputs | Non-dropped/private-free session returns null for ordinary input or owning WindowCanonicalState. |
| invariants | Window metadata reflects a committed substep; this method never commits/drains a pending command. |
| ownership | Returned export owns its copied window labels/rows/progress; session controller remains unchanged. |
| failure | State/Guard/export allocation errors propagate. |
| cost | Population/label/row-byte traversal and copy when windowed; fixed null result otherwise. |
| Design | [docs/session_lifecycle.md § Control states and work phases](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/batches_windows.md](../../../../batches_windows.md) |

## B0190

[Lines 1625–1625](../../../../../src/runtime/session.cpp#L1625); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::stop() { auto& d=*data_; Impl::Guard guard(d); d.stop(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard public terminal stop. |
| inputs / outputs | Creator-thread/reentry Guard delegates to private nonthrowing stop(). |
| invariants | Terminal cleanup is idempotent; committed runtime remains inspectable. |
| ownership | Private cleanup owns all pending/source/output/native/file release; independent returned native values remain live. |
| failure | Public Guard may throw before cleanup; private stop allocates nothing and cannot throw. |
| cost | Fixed guard plus full retained cleanup, potentially population-sized. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0191

[Lines 1626–1626](../../../../../src/runtime/session.cpp#L1626); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::drop() { auto& d=*data_; Impl::Guard guard(d); d.drop(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard public terminal drop. |
| inputs / outputs | Creator-thread/reentry Guard delegates to private nonthrowing drop(). |
| invariants | Terminal cleanup is idempotent; mutable runtime/durable locks release, while immutable report metadata can remain. |
| ownership | Private cleanup owns all pending/source/output/native/file release; independent returned native values remain live. |
| failure | Public Guard may throw before cleanup; private drop allocates nothing and cannot throw. |
| cost | Fixed guard plus full retained cleanup, potentially population-sized. |
| Design | [docs/session_lifecycle.md § Ownership, commitment and failure](../../../../session_lifecycle.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0192

[Lines 1627–1629](../../../../../src/runtime/session.cpp#L1627); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const SessionRunContext> QuerySession::run_context() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain immutable native session admission metadata. |
| inputs / outputs | Guarded shared_ptr&lt;const SessionRunContext&gt; copy. |
| invariants | Available after drop; no source/runtime token or mutable configuration is exposed. |
| ownership | Caller shares the original funded context/input/window policy metadata and therefore its query account lifetime. |
| failure | Thread/reentry guard errors only; shared_ptr copy is nonthrowing. |
| cost | Constant shared-owner copy; last release can destroy retained policy metadata. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0193

[Lines 1630–1636](../../../../../src/runtime/session.cpp#L1630); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionReportMetadata QuerySession::report_metadata() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture lightweight current or released session report identity. |
| inputs / outputs | Live runtime yields plan/options/profile/owner/sequence/state; dropped runtime uses retained metadata with absent state. |
| invariants | Does not revive a dropped engine or enumerate rows; retained owner ID/sequence remain historical. |
| ownership | Shares actual immutable CompiledProgram/account; no mutable table or public DTO plan clone. |
| failure | Thread/reentry checks only with valid factory invariants; metadata constructor is noexcept. |
| cost | Fixed metadata/shared-owner copies; full release later may free last program metadata. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0194

[Lines 1637–1641](../../../../../src/runtime/session.cpp#L1637); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CommittedStateGauges> QuerySession::report_gauges() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture caller-owned committed state gauges. |
| inputs / outputs | Returns null without runtime or while any session private work exists; otherwise delegates current gauges. |
| invariants | Committed unread output is allowed; no pending tables are inspected and no work is drained to obtain a report. |
| ownership | CommittedStateGauges is explicit caller DTO vector storage. Session/native state stays unchanged. |
| failure | Guard/delegated busy/resource errors propagate; absent runtime/private state is explicit null, not fabricated zero. |
| cost | Visits plan base/node relations and copies gauge arrays; no full answer enumeration, but not constant in query size. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0195

[Lines 1642–1646](../../../../../src/runtime/session.cpp#L1642); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CapturedStateGauges> QuerySession::capture_state_gauges() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture native funded committed state gauges. |
| inputs / outputs | Returns null without runtime or while any session private work exists; otherwise delegates current gauges. |
| invariants | Committed unread output is allowed; no pending tables are inspected and no work is drained to obtain a report. |
| ownership | CapturedStateGauges arrays use the original query account. Session/native state stays unchanged. |
| failure | Guard/delegated busy/resource errors propagate; absent runtime/private state is explicit null, not fabricated zero. |
| cost | Visits plan base/node relations and copies gauge arrays; no full answer enumeration, but not constant in query size. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0196

[Lines 1647–1650](../../../../../src/runtime/session.cpp#L1647); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CursorObservation> QuerySession::last_cursor_observation() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the last cursor lifecycle report without advancing it. |
| inputs / outputs | Current runtime or retained optional CursorObservation after runtime release. |
| invariants | Absent observation stays absent; no clock/state/result sampling is fabricated. |
| ownership | Copies fixed optional metrics; no reader lease or mutable cursor. |
| failure | Thread/reentry guard errors only. |
| cost | Fixed report copy; no trace scan. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0197

[Lines 1651–1654](../../../../../src/runtime/session.cpp#L1651); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<resource::MemoryStatistics> QuerySession::accounted_memory_statistics() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read actual native query-account ledger statistics. |
| inputs / outputs | Returns optional MemoryStatistics from live runtime, null after runtime release. |
| invariants | Retained snapshots/reports/metadata in that account affect counts; values are requested bytes, not RSS. Null does not assert zero residual memory after drop. |
| ownership | Copies scalar account ledger; no detached memory authority. |
| failure | Thread/reentry guard/delegated handle errors propagate. |
| cost | Fixed ledger snapshot; does not run a complete owner-attribution/table scan. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0198

[Lines 1655–1661](../../../../../src/runtime/session.cpp#L1655); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationSnapshot QuerySession::observations() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current/retained optional observation summary with session attachment. |
| inputs / outputs | Runtime summary or saved summary is returned with run_context/attached/committed sequence refreshed. |
| invariants | Dropped summary retains fixed historical metrics and immutable context; no trace payload or hidden state traversal. |
| ownership | Shares funded context/benchmark/initialization metadata through summary owners. |
| failure | Thread/reentry guard errors only; valid runtime summary access is fixed metadata. |
| cost | Fixed metric-registry-sized copy plus shared-owner operations. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0199

[Lines 1662–1671](../../../../../src/runtime/session.cpp#L1662); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTrace QuerySession::observation_trace() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export optional observation trace as a caller value. |
| inputs / outputs | Live runtime trace or dropped summary with empty trace records. |
| invariants | Drop releases runtime trace payload; immutable session/program context can remain shared. Reading trace does not advance/drain execution. |
| ownership | Explicit ObservationTrace export uses caller-owned record vector and copied summaries; it does not change native trace ownership. |
| failure | Guard/export allocation failure leaves runtime and previous captures intact. |
| cost | O(retained trace records) copy while live; fixed summary after drop. Final metadata release may deallocate. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0200

[Lines 1672–1679](../../../../../src/runtime/session.cpp#L1672); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedObservationTrace QuerySession::capture_observation_trace() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture optional trace into native retained storage. |
| inputs / outputs | Live runtime trace or released summary-only CapturedObservationTrace built with retained plan account. |
| invariants | No runtime after drop yields empty records and retained summary; unavailable timing remains unavailable. |
| ownership | Native trace arrays/control and context owners retain original account independently of session. |
| failure | Guard/resource/capture failure propagates without advancing execution. |
| cost | O(retained trace records) funded copy when live; fixed empty setup after drop. Retaining captures consumes original query cap. |
| Design | [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0201

[Lines 1680–1682](../../../../../src/runtime/session.cpp#L1680); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1680-L1682:sha256:8a289c52265f032d42385d65af77db38f02dd5350de0eb04b777a405216fc9ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/session.cpp: opens namespace \`crown::runtime\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0202

[Lines 1683–1689](../../../../../src/runtime/session.cpp#L1683); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::configure_workload_statistics(const workload::Options& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure optional workload collection at a writer barrier. |
| inputs / outputs | Options, retained runtime and no session private work delegate to runtime configure. |
| invariants | Lower native writable/read-lease/output constraints also apply. Failed configuration keeps prior configuration/counters; no event-clock collection is invented. |
| ownership | Collector descriptor/route/slab storage uses original query account; retained_workload_options refreshes only after successful configure. |
| failure | Guard/drop/private/delegated writer/resource errors propagate; no catch or automatic fallback mode. |
| cost | Explicit descriptor/route/cell allocation/configuration and temporary old/new overlap; hooks during later updates remain their separate native cost. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0203

[Lines 1690–1695](../../../../../src/runtime/session.cpp#L1690); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void QuerySession::reset_workload_statistics() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset workload observation intervals without changing committed data. |
| inputs / outputs | Retained runtime and no session private work delegate reset_workload_statistics. |
| invariants | Underlying writable/read/output barriers remain; reset changes collection interval/sample ordinals, not physical/source sequence. |
| ownership | Existing collector owns its cells; caller-retained earlier snapshots remain immutable. |
| failure | Drop/private/Guard/native writer errors propagate before reset. |
| cost | Visits configured collector cells/interval state; no query result/source reconstruction. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0204

[Lines 1696–1699](../../../../../src/runtime/session.cpp#L1696); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::Options QuerySession::workload_statistics_options() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read live or retained workload configuration. |
| inputs / outputs | Runtime options when retained, otherwise saved retained_workload_options. |
| invariants | Options describe configured collection, not exactness/availability of a particular snapshot. |
| ownership | Copies scalar configuration only. |
| failure | Thread/reentry guard errors only. |
| cost | Fixed options copy; no descriptor or histogram scan. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0205

[Lines 1700–1705](../../../../../src/runtime/session.cpp#L1700); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<workload::Snapshot> QuerySession::workload_statistics() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture committed workload observations with session-private availability. |
| inputs / outputs | Returns null after runtime release; otherwise runtime snapshot, marked with_pending for physical or metadata-only private work. |
| invariants | Committed cell facts are copied without merging or draining private work. Live diagnostic Metadata can include the unfinished attempt; pending/status/sample/loss scopes remain explicit. |
| ownership | Native Snapshot owns its funded copied plan/descriptors/cells and survives later reset/drop. |
| failure | Guard/snapshot allocation/resource errors propagate without changing collector state. |
| cost | Explicit copy of configured descriptors/cell payloads, possibly allocation; no C01 clock reads or extra ordinary-update capture. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0206

[Lines 1706–1708](../../../../../src/runtime/session.cpp#L1706); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1706-L1708:sha256:221c80f3590b4b823e204d298c1d00f4daaae3c191db4462fcb6c24862bf2186
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/session.cpp: opens namespace \`crown::runtime\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0207

[Lines 1709–1713](../../../../../src/runtime/session.cpp#L1709); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::OwnerCapture> QuerySession::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture selected committed owner statistics or pending metadata. |
| inputs / outputs | Request/limits yield null after drop, metadata-only pending OwnerBuilder for session private state, otherwise native capture. |
| invariants | Window metadata-only preparation also prevents reading tentative tables; request budgets are shared across selected components. |
| ownership | Returned OwnerCapture owns original-account plan/selection/distribution payloads; caller request is borrowed during capture. |
| failure | Guard/invalid request/allocation errors propagate; bounded component exhaustion is represented by explicit native availability, not exact zero. |
| cost | Pending metadata still validates/copies requested descriptors; committed distribution capture scans requested populations/keys under finite budgets. No capture on ordinary update path. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0208

[Lines 1714–1717](../../../../../src/runtime/session.cpp#L1714); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::Freshness> QuerySession::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a capture owner/sequence/layer stamp with current native owner. |
| inputs / outputs | OwnerCapture plus max_event_lag yield optional Freshness, null after runtime release. |
| invariants | Equal results/plan do not make foreign/rebuilt owners current; native stamp semantics remain authoritative even during session private work. |
| ownership | Borrows capture and runtime; creates no table snapshot. |
| failure | Guard/native handle/contract errors propagate; statuses distinguish stale/foreign/future/scope mismatch. |
| cost | Fixed owner/frontier comparisons, no distribution scan or refresh. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0209

[Lines 1718–1724](../../../../../src/runtime/session.cpp#L1718); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<statistics::CombinedCapture> QuerySession::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture compatible owner-state and workload reports under one session guard. |
| inputs / outputs | Request/limits yield null after drop; otherwise combined native capture or pending owner metadata plus committed workload with_pending. |
| invariants | Owner/layer/physical epoch/plan/pending status must agree; state and workload availability/sample semantics are not merged. |
| ownership | Owns two original-account immutable captures; no mutable runtime lease is returned. |
| failure | Guard/request/resource/combination consistency errors propagate; no partial pair is exposed. |
| cost | Full requested owner distribution plus configured workload snapshot costs; pending path avoids tentative-table traversal but still copies metadata/cells. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0210

[Lines 1725–1729](../../../../../src/runtime/session.cpp#L1725); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionStatisticsContext QuerySession::capture_statistics_context(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt an owning statistics request to the borrowed-view capture boundary. |
| inputs / outputs | Optional OwnerRequest becomes optional OwnerRequestView then delegates capture_statistics_context_view. |
| invariants | Absent request remains distinguishable from explicit empty request; view lifetime spans the synchronous delegate. |
| ownership | Borrowed selections do not deep-copy caller request fields; result owns its native diagnostic data. |
| failure | View/delegated capture errors propagate with session unchanged. |
| cost | Fixed view construction plus complete context-capture costs; no second guard or temporary owning request copy. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp) |

## B0211

[Lines 1730–1758](../../../../../src/runtime/session.cpp#L1730); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SessionStatisticsContext QuerySession::capture_statistics_context_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one coherent session diagnostic context under one guard. |
| inputs / outputs | Optional borrowed selection view and native limits; gathers current/released metadata, fixed status, native trace, optional combined statistics, workload options and cursor. |
| invariants | Private state produces pending metadata and committed workload, never reads tentative tables. Dropped state has retained metadata/summary and no combined native owner; optional-request flag preserves intent. |
| ownership | One original-account shared Data retains all native capture/control/plan/context owners; no public formatting/EXPLAIN DTO dependency. Optional pattern status retains an immutable declaration handle and fixed current-tree/progress metadata; it clones no rule vector. |
| failure | Request/guard/trace/statistics/allocation/consistency failures unwind the unexposed context; prior session/captures remain intact. |
| cost | Explicit trace/cell/selected-population capture plus one funded shared control. Empty selection still captures metadata/workload, and retained context consumes original account. Pattern-status copy adds fixed fields/refcount, with O(R) teardown only on final declaration-owner release. |
| Design | [docs/statistics.md § Freshness and lifecycle](../../../../statistics.md), [docs/statistics.md § Native retained report graphs](../../../../statistics.md), [include/crown/runtime/session.hpp](../../../../../include/crown/runtime/session.hpp), [docs/observability.md § Reports, ownership, and committed gauges](../../../../observability.md), [docs/observability.md § Native retained report ownership](../../../../observability.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0212

[Lines 1759–1761](../../../../../src/runtime/session.cpp#L1759); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1759-L1761:sha256:9e2f18da6f8adce73571e3f18b38528116ccefb4e7fba17887471ac59051fd9b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/session.cpp: opens namespace \`crown::runtime::memory::detail\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0213

[Lines 1762–1775](../../../../../src/runtime/session.cpp#L1762); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt Access::capture(const QuerySession& owner,Limits limits) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a bounded native memory report without throwing at its public attempt boundary. |
| inputs / outputs | QuerySession and Limits become Attempt with fixed stop or immutable report. |
| invariants | Availability is released after drop, pending for any private work, committed otherwise. Only committed reports append actual runtime/table/operator data; all modes include actual account partition. |
| ownership | Builder/report and scratch use original plan account; released session can still hold immutable metadata and older external allocations. |
| failure | attempt translates invalid handle/typed memory/bad_alloc/other errors to fixed stop and no partial report; thread/reentry Guard errors become inconsistent, not a propagated Error. |
| cost | Explicit allocation-attribution partition/sort and committed native table/operator traversal under separate diagnostic bounds; never called automatically during an update. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0214

[Lines 1776–1776](../../../../../src/runtime/session.cpp#L1776); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1776-L1776:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::memory::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::memory::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::memory::detail\` at its lexical source position in src/runtime/session.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::memory::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/session_lifecycle.md](../../../../session_lifecycle.md), [docs/session-journal.md](../../../../session-journal.md), [docs/checkpoints.md](../../../../checkpoints.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
