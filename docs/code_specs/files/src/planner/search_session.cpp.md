# `src/planner/search_session.cpp` — block usage map

[Source](../../../../../src/planner/search_session.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Advance a resumable exact/fast-path planner session under explicit transition/depth/time limits.

Snapshot SHA-256: `cf82015fc6b2acbdab41625d5b1d1c2f5c03393f78a822b66597d94c60c94fdf`. 667 lines partitioned into 111 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../src/planner/search_session.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. | growth new; source comment (unverified): // Require a live artifact owner before borrowing payload; this does not revalidate its proof. · [reviewed contract](#b0001) |
| [B0002 · 16–19](../../../../../src/planner/search_session.cpp#L16) | Callable definition: template &lt;class T&gt; const T& require_handle(const std::shared_ptr&lt;const T&gt;& value) | calls Error; returns *value; source comment (unverified): // Require a live artifact owner before borrowing payload; this does not revalidate its proof. · [reviewed contract](#b0002) |
| [B0003 · 20–21](../../../../../src/planner/search_session.cpp#L20) | Explanatory comments or spacing. | source comment (unverified): // Freeze the exact supplied model; no normalization or prefix-to-original authority · [reviewed contract](#b0003) |
| [B0004 · 22–26](../../../../../src/planner/search_session.cpp#L22) | Callable definition: std::shared_ptr&lt;const cd::BindingData&gt; admit(Catalog catalog, Query query) | calls validate, std::move; returns std::make_shared&lt;const cd::BindingData&gt;(cd::BindingData{; growth make_shared; source comment (unverified): // Freeze the exact supplied model; no normalization or prefix-to-original authority · [reviewed contract](#b0004) |
| [B0005 · 27–28](../../../../../src/planner/search_session.cpp#L27) | Explanatory comments or spacing. | source comment (unverified): // Validate both phase durations before creating a search owner. See · [reviewed contract](#b0005) |
| [B0006 · 29–32](../../../../../src/planner/search_session.cpp#L29) | Callable definition: void validate_limits(const ContinuationLimits& limits) | calls cd::valid_ceiling, Error; source comment (unverified): // Validate both phase durations before creating a search owner. See · [reviewed contract](#b0006) |
| [B0007 · 33–34](../../../../../src/planner/search_session.cpp#L33) | Explanatory comments or spacing. | source comment (unverified): // Admit nonnegative replay time ceilings; zero remains an operational ceiling. See · [reviewed contract](#b0007) |
| [B0008 · 35–38](../../../../../src/planner/search_session.cpp#L35) | Callable definition: void validate_limits(const ReplayOptions& limits) | calls cd::valid_ceiling, Error; source comment (unverified): // Admit nonnegative replay time ceilings; zero remains an operational ceiling. See · [reviewed contract](#b0008) |
| [B0009 · 39–40](../../../../../src/planner/search_session.cpp#L39) | Explanatory comments or spacing. | source comment (unverified): // Return static stop text; allocating compatibility messages are assembled by the caller. See · [reviewed contract](#b0009) |
| [B0010 · 41–54](../../../../../src/planner/search_session.cpp#L41) | Callable definition: std::string_view reason_text(StopReason reason) noexcept | calls ; returns @; @; source comment (unverified): // Return static stop text; allocating compatibility messages are assembled by the caller. See · [reviewed contract](#b0010) |
| [B0011 · 55–56](../../../../../src/planner/search_session.cpp#L55) | Explanatory comments or spacing. | source comment (unverified): // Check legacy time range before multiplying milliseconds into nanoseconds. See · [reviewed contract](#b0011) |
| [B0012 · 57–64](../../../../../src/planner/search_session.cpp#L57) | Callable definition: std::optional&lt;std::chrono::nanoseconds&gt; legacy_time(const SearchLimits& limits) | calls count, max, Error; returns {}; std::chrono::nanoseconds{value * 1'000'000}; source comment (unverified): // Check legacy time range before multiplying milliseconds into nanoseconds. See · [reviewed contract](#b0012) |
| [B0013 · 65–66](../../../../../src/planner/search_session.cpp#L65) | Explanatory comments or spacing. | source comment (unverified): // Map legacy work/time independently to both phase ledgers; literal_scope_limit belongs to · [reviewed contract](#b0013) |
| [B0014 · 67–70](../../../../../src/planner/search_session.cpp#L67) | Callable definition: ContinuationLimits legacy_limits(const SearchLimits& limits) | calls legacy_time; returns {phase, phase, limits.recursion_limit}; source comment (unverified): // Map legacy work/time independently to both phase ledgers; literal_scope_limit belongs to · [reviewed contract](#b0014) |
| [B0015 · 71–71](../../../../../src/planner/search_session.cpp#L71) | Explanatory comments or spacing. |  |
| [B0016 · 72–119](../../../../../src/planner/search_session.cpp#L72) | Callable definition: template &lt;class Owner&gt; // Charge attempted units, preserve retryable allocation/depth stops and keep per-call grants // separate … | calls count, terminal, terminal_reason, std::chrono::steady_clock::now; guard const auto ceiling = ledger.check();; returns StopReason::invalid_quantum; StopReason::quantum_work; 1 loop sites; source comment (unverified): // Charge attempted units, preserve retryable allocation/depth stops and keep per-call grants · [reviewed contract](#b0016) |
| [B0017 · 120–124](../../../../../src/planner/search_session.cpp#L120) | declares namespace scope. | source comment (unverified): // namespace · [reviewed contract](#b0017) |
| [B0018 · 125–131](../../../../../src/planner/search_session.cpp#L125) | Type/record definition: struct ArtifactFactory | returns SearchBinding(std::move(p)); ValidatedIncumbent(std::move(p)); source comment (unverified): // Private wrapping does not perform validation; callers must already hold the matching · [reviewed contract](#b0018) |
| [B0019 · 132–132](../../../../../src/planner/search_session.cpp#L132) | Closes surrounding scope/type. |  · [reviewed contract](#b0019) |
| [B0020 · 133–133](../../../../../src/planner/search_session.cpp#L133) | Callable definition: SearchBinding::SearchBinding(std::shared_ptr&lt;const cd::BindingData&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0020) |
| [B0021 · 134–134](../../../../../src/planner/search_session.cpp#L134) | Callable definition: bool SearchBinding::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0021) |
| [B0022 · 135–135](../../../../../src/planner/search_session.cpp#L135) | Callable definition: const Catalog& SearchBinding::catalog() const | calls require_handle; returns require_handle(data_).catalog · [reviewed contract](#b0022) |
| [B0023 · 136–136](../../../../../src/planner/search_session.cpp#L136) | Callable definition: const Query& SearchBinding::query() const | calls require_handle; returns require_handle(data_).query · [reviewed contract](#b0023) |
| [B0024 · 137–137](../../../../../src/planner/search_session.cpp#L137) | Callable definition: AccountingVersion SearchBinding::accounting() const | calls require_handle; returns require_handle(data_).accounting · [reviewed contract](#b0024) |
| [B0025 · 138–138](../../../../../src/planner/search_session.cpp#L138) | Callable definition: ValidatedIncumbent::ValidatedIncumbent(std::shared_ptr&lt;const cd::IncumbentData&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0025) |
| [B0026 · 139–139](../../../../../src/planner/search_session.cpp#L139) | Callable definition: bool ValidatedIncumbent::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0026) |
| [B0027 · 140–140](../../../../../src/planner/search_session.cpp#L140) | Callable definition: SearchBinding ValidatedIncumbent::binding() const | calls cd::ArtifactFactory::binding, require_handle; returns cd::ArtifactFactory::binding(require_handle(data_).upper-&gt;binding) · [reviewed contract](#b0027) |
| [B0028 · 141–141](../../../../../src/planner/search_session.cpp#L141) | Callable definition: const FreeConnexTree& ValidatedIncumbent::tree() const | calls require_handle; returns *require_handle(data_).upper-&gt;tree · [reviewed contract](#b0028) |
| [B0029 · 142–142](../../../../../src/planner/search_session.cpp#L142) | Callable definition: std::size_t ValidatedIncumbent::height() const | calls require_handle; returns require_handle(data_).upper-&gt;height · [reviewed contract](#b0029) |
| [B0030 · 143–143](../../../../../src/planner/search_session.cpp#L143) | Callable definition: VerifiedOptimum::VerifiedOptimum(std::shared_ptr&lt;const cd::OptimumData&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0030) |
| [B0031 · 144–144](../../../../../src/planner/search_session.cpp#L144) | Callable definition: bool VerifiedOptimum::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0031) |
| [B0032 · 145–145](../../../../../src/planner/search_session.cpp#L145) | Callable definition: SearchBinding VerifiedOptimum::binding() const | calls cd::ArtifactFactory::binding, require_handle; returns cd::ArtifactFactory::binding(require_handle(data_).upper-&gt;upper-&gt;binding) · [reviewed contract](#b0032) |
| [B0033 · 146–146](../../../../../src/planner/search_session.cpp#L146) | Callable definition: ValidatedIncumbent VerifiedOptimum::upper() const | calls cd::ArtifactFactory::incumbent, require_handle; returns cd::ArtifactFactory::incumbent(require_handle(data_).upper) · [reviewed contract](#b0033) |
| [B0034 · 147–147](../../../../../src/planner/search_session.cpp#L147) | Callable definition: std::size_t VerifiedOptimum::height() const | calls require_handle; returns require_handle(data_).upper-&gt;upper-&gt;height · [reviewed contract](#b0034) |
| [B0035 · 148–148](../../../../../src/planner/search_session.cpp#L148) | Callable definition: const HeightCertificate& VerifiedOptimum::certificate() const | calls require_handle; returns *require_handle(data_).proof · [reviewed contract](#b0035) |
| [B0036 · 149–149](../../../../../src/planner/search_session.cpp#L149) | Callable definition: VerifiedInfeasible::VerifiedInfeasible(std::shared_ptr&lt;const cd::InfeasibleData&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0036) |
| [B0037 · 150–150](../../../../../src/planner/search_session.cpp#L150) | Callable definition: bool VerifiedInfeasible::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0037) |
| [B0038 · 151–151](../../../../../src/planner/search_session.cpp#L151) | Callable definition: SearchBinding VerifiedInfeasible::binding() const | calls cd::ArtifactFactory::binding, require_handle; returns cd::ArtifactFactory::binding(require_handle(data_).binding) · [reviewed contract](#b0038) |
| [B0039 · 152–152](../../../../../src/planner/search_session.cpp#L152) | Callable definition: const HeightCertificate& VerifiedInfeasible::certificate() const | calls require_handle; returns *require_handle(data_).proof · [reviewed contract](#b0039) |
| [B0040 · 153–153](../../../../../src/planner/search_session.cpp#L153) | Callable definition: CheckedCertificate::CheckedCertificate(std::shared_ptr&lt;const cd::CheckedCertificateData&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0040) |
| [B0041 · 154–154](../../../../../src/planner/search_session.cpp#L154) | Callable definition: bool CheckedCertificate::valid() const noexcept | calls ; returns static_cast&lt;bool&gt;(data_) · [reviewed contract](#b0041) |
| [B0042 · 155–155](../../../../../src/planner/search_session.cpp#L155) | Callable definition: SearchBinding CheckedCertificate::binding() const | calls cd::ArtifactFactory::binding, require_handle; returns cd::ArtifactFactory::binding(require_handle(data_).checked-&gt;binding) · [reviewed contract](#b0042) |
| [B0043 · 156–156](../../../../../src/planner/search_session.cpp#L156) | Callable definition: const HeightCertificate& CheckedCertificate::certificate() const | calls require_handle; returns *require_handle(data_).checked-&gt;proof · [reviewed contract](#b0043) |
| [B0044 · 157–161](../../../../../src/planner/search_session.cpp#L157) | Callable definition: std::optional&lt;VerifiedOptimum&gt; CheckedCertificate::optimum() const | calls require_handle, cd::ArtifactFactory::optimum; returns {}; cd::ArtifactFactory::optimum(p) · [reviewed contract](#b0044) |
| [B0045 · 162–166](../../../../../src/planner/search_session.cpp#L162) | Callable definition: std::optional&lt;VerifiedInfeasible&gt; CheckedCertificate::infeasibility() const | calls require_handle, cd::ArtifactFactory::infeasibility; returns {}; cd::ArtifactFactory::infeasibility(p) · [reviewed contract](#b0045) |
| [B0046 · 167–172](../../../../../src/planner/search_session.cpp#L167) | declares types or opens a type body. | source comment (unverified): // Retain worker state and separate upper publication from final independent-proof authority. · [reviewed contract](#b0046) |
| [B0047 · 173–177](../../../../../src/planner/search_session.cpp#L173) | Type/record definition: enum class Stage | source comment (unverified): // Keep allocation-safe driver stages and withhold prepared final authority until · [reviewed contract](#b0047) |
| [B0048 · 178–201](../../../../../src/planner/search_session.cpp#L178) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0048) |
| [B0049 · 202–203](../../../../../src/planner/search_session.cpp#L202) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; value, SearchOptions opts) : input(std::move(value)), options(opts), producer_ledger(… | calls input, std::move, options, producer_ledger · [reviewed contract](#b0049) |
| [B0050 · 204–204](../../../../../src/planner/search_session.cpp#L204) | Callable definition: bool terminal() const noexcept | calls ; returns stage == Stage::complete \|\| stage == Stage::failed \|\| stage == Stage::cancelled · [reviewed contract](#b0050) |
| [B0051 · 205–208](../../../../../src/planner/search_session.cpp#L205) | Callable definition: StopReason terminal_reason() const noexcept | calls ; returns stage == Stage::complete ? StopReason::complete : · [reviewed contract](#b0051) |
| [B0052 · 209–209](../../../../../src/planner/search_session.cpp#L209) | Callable definition: bool replay_phase() const noexcept | calls ; returns stage &gt;= Stage::replay_shell · [reviewed contract](#b0052) |
| [B0053 · 210–210](../../../../../src/planner/search_session.cpp#L210) | Callable definition: cd::ResourceLedger& ledger() noexcept | calls replay_phase; returns replay_phase() ? replay_ledger : producer_ledger · [reviewed contract](#b0053) |
| [B0054 · 211–212](../../../../../src/planner/search_session.cpp#L211) | Explanatory comments or spacing. | source comment (unverified): // Report active-worker depth only; parked owners remain retained separately. See · [reviewed contract](#b0054) |
| [B0055 · 213–219](../../../../../src/planner/search_session.cpp#L213) | Callable definition: std::size_t current_depth() const noexcept | calls ; returns producer-&gt;current_depth(); witness-&gt;current_depth(); source comment (unverified): // Report active-worker depth only; parked owners remain retained separately. See · [reviewed contract](#b0055) |
| [B0056 · 220–220](../../../../../src/planner/search_session.cpp#L220) | Callable definition: void fail(StopReason reason) noexcept | calls  · [reviewed contract](#b0056) |
| [B0057 · 221–338](../../../../../src/planner/search_session.cpp#L221) | Callable definition: cd::UnitResult unit() | calls std::move, step, candidate, fail; returns result; result; growth make_shared, make_unique; source comment (unverified): // Prepare the producer before installing its stage. See docs/planner_continuations.md, · [reviewed contract](#b0057) |
| [B0058 · 339–351](../../../../../src/planner/search_session.cpp#L339) | Callable definition: SearchPhase phase() const noexcept | calls ; returns SearchPhase::admitted; producer-&gt;phase() · [reviewed contract](#b0058) |
| [B0059 · 352–352](../../../../../src/planner/search_session.cpp#L352) | Closes surrounding scope/type. |  · [reviewed contract](#b0059) |
| [B0060 · 353–353](../../../../../src/planner/search_session.cpp#L353) | Callable definition: ExactSearch::ExactSearch(std::unique_ptr&lt;Impl&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0060) |
| [B0061 · 354–362](../../../../../src/planner/search_session.cpp#L354) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Release retained workers and payloads; separately retained immutable artifacts survive. See · [reviewed contract](#b0061) |
| [B0062 · 363–369](../../../../../src/planner/search_session.cpp#L363) | Callable definition: ExactSearch ExactSearch::create(Catalog catalog, Query query, SearchOptions options) | calls validate_limits, Error, admit, std::move; returns ExactSearch(std::make_unique&lt;Impl&gt;(std::move(input), options)); growth make_unique; source comment (unverified): // Admit the exact supplied query after validating options; physical normalization and · [reviewed contract](#b0062) |
| [B0063 · 370–371](../../../../../src/planner/search_session.cpp#L370) | Explanatory comments or spacing. | source comment (unverified): // Advance only saved work; moved-from detection precedes quantum validation and snapshots · [reviewed contract](#b0063) |
| [B0064 · 372–376](../../../../../src/planner/search_session.cpp#L372) | Callable definition: SearchAdvance ExactSearch::advance(WorkQuantum quantum) noexcept | calls progress, run_quantum; returns {StopReason::moved_from, progress()}; {stopped, progress()}; source comment (unverified): // Advance only saved work; moved-from detection precedes quantum validation and snapshots · [reviewed contract](#b0064) |
| [B0065 · 377–378](../../../../../src/planner/search_session.cpp#L377) | Explanatory comments or spacing. | source comment (unverified): // Report universal versus complete lower evidence explicitly; moved-from has no model-bound · [reviewed contract](#b0065) |
| [B0066 · 379–404](../../../../../src/planner/search_session.cpp#L379) | Callable definition: SearchProgress ExactSearch::progress() const noexcept | calls phase, empty, statistics; returns report; report; source comment (unverified): // Report universal versus complete lower evidence explicitly; moved-from has no model-bound · [reviewed contract](#b0066) |
| [B0067 · 405–408](../../../../../src/planner/search_session.cpp#L405) | Callable definition: SearchBinding ExactSearch::binding() const | calls Error, cd::ArtifactFactory::binding; returns cd::ArtifactFactory::binding(data_-&gt;input) · [reviewed contract](#b0067) |
| [B0068 · 409–412](../../../../../src/planner/search_session.cpp#L409) | Callable definition: SearchPolicy ExactSearch::policy() const | calls Error; returns data_-&gt;options.policy · [reviewed contract](#b0068) |
| [B0069 · 413–416](../../../../../src/planner/search_session.cpp#L413) | Callable definition: ContinuationLimits ExactSearch::limits() const | calls Error; returns data_-&gt;options.limits · [reviewed contract](#b0069) |
| [B0070 · 417–418](../../../../../src/planner/search_session.cpp#L417) | Explanatory comments or spacing. | source comment (unverified): // Expose best_found checked uppers across pauses/failure/cancellation; strict always · [reviewed contract](#b0070) |
| [B0071 · 419–422](../../../../../src/planner/search_session.cpp#L419) | Callable definition: std::optional&lt;ValidatedIncumbent&gt; ExactSearch::incumbent() const noexcept | calls cd::ArtifactFactory::incumbent; returns {}; cd::ArtifactFactory::incumbent(data_-&gt;incumbent); source comment (unverified): // Expose best_found checked uppers across pauses/failure/cancellation; strict always · [reviewed contract](#b0071) |
| [B0072 · 423–424](../../../../../src/planner/search_session.cpp#L423) | Explanatory comments or spacing. | source comment (unverified): // Expose optimum only after final publication and only for this exact query scope. See · [reviewed contract](#b0072) |
| [B0073 · 425–428](../../../../../src/planner/search_session.cpp#L425) | Callable definition: std::optional&lt;VerifiedOptimum&gt; ExactSearch::optimum() const noexcept | calls cd::ArtifactFactory::optimum; returns {}; cd::ArtifactFactory::optimum(data_-&gt;optimum); source comment (unverified): // Expose optimum only after final publication and only for this exact query scope. See · [reviewed contract](#b0073) |
| [B0074 · 429–430](../../../../../src/planner/search_session.cpp#L429) | Explanatory comments or spacing. | source comment (unverified): // Expose no-tree authority only at complete publication, never from a resource stop or absent · [reviewed contract](#b0074) |
| [B0075 · 431–434](../../../../../src/planner/search_session.cpp#L431) | Callable definition: std::optional&lt;VerifiedInfeasible&gt; ExactSearch::infeasibility() const noexcept | calls cd::ArtifactFactory::infeasibility; returns {}; cd::ArtifactFactory::infeasibility(data_-&gt;infeasibility); source comment (unverified): // Expose no-tree authority only at complete publication, never from a resource stop or absent · [reviewed contract](#b0075) |
| [B0076 · 435–436](../../../../../src/planner/search_session.cpp#L435) | Explanatory comments or spacing. | source comment (unverified): // Apply only monotone ceilings above consumed values; accepted equality still advances · [reviewed contract](#b0076) |
| [B0077 · 437–448](../../../../../src/planner/search_session.cpp#L437) | Callable definition: LimitChange ExactSearch::raise_limits(ContinuationLimits value) noexcept | calls terminal, cd::valid_ceiling, cd::monotone_phase, cd::monotone_ceiling; returns LimitChange::terminal; LimitChange::invalid; source comment (unverified): // Apply only monotone ceilings above consumed values; accepted equality still advances · [reviewed contract](#b0077) |
| [B0078 · 449–450](../../../../../src/planner/search_session.cpp#L449) | Explanatory comments or spacing. | source comment (unverified): // Cancel only nonterminal work; preserve incumbent/input/counters, and leave already terminal · [reviewed contract](#b0078) |
| [B0079 · 451–460](../../../../../src/planner/search_session.cpp#L451) | Callable definition: void ExactSearch::cancel() noexcept | calls terminal, statistics, reset, depth; source comment (unverified): // Cancel only nonterminal work; preserve incumbent/input/counters, and leave already terminal · [reviewed contract](#b0079) |
| [B0080 · 461–464](../../../../../src/planner/search_session.cpp#L461) | declares types or opens a type body. | source comment (unverified): // Retain checking separately from final artifact preparation; checked() stays empty until · [reviewed contract](#b0080) |
| [B0081 · 465–465](../../../../../src/planner/search_session.cpp#L465) | Type/record definition: enum class Stage |  · [reviewed contract](#b0081) |
| [B0082 · 466–481](../../../../../src/planner/search_session.cpp#L466) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0082) |
| [B0083 · 482–483](../../../../../src/planner/search_session.cpp#L482) | Callable definition: Impl(std::shared_ptr&lt;const cd::BindingData&gt; value, std::shared_ptr&lt;const HeightCertificate&gt; claim, ReplayOptions opts) : input(st… | calls input, std::move, proof, options · [reviewed contract](#b0083) |
| [B0084 · 484–484](../../../../../src/planner/search_session.cpp#L484) | Callable definition: bool terminal() const noexcept | calls ; returns stage == Stage::complete \|\| stage == Stage::failed \|\| stage == Stage::cancelled · [reviewed contract](#b0084) |
| [B0085 · 485–485](../../../../../src/planner/search_session.cpp#L485) | Callable definition: StopReason terminal_reason() const noexcept | calls ; returns stage == Stage::complete ? StopReason::complete : stage == Stage::cancelled ? StopReason::cancelled… · [reviewed contract](#b0085) |
| [B0086 · 486–486](../../../../../src/planner/search_session.cpp#L486) | Callable definition: cd::ResourceLedger& ledger() noexcept | calls ; returns resource · [reviewed contract](#b0086) |
| [B0087 · 487–488](../../../../../src/planner/search_session.cpp#L487) | Explanatory comments or spacing. | source comment (unverified): // Report active checker depth; post-check owner preparation is depth zero while evidence · [reviewed contract](#b0087) |
| [B0088 · 489–489](../../../../../src/planner/search_session.cpp#L489) | Callable definition: std::size_t current_depth() const noexcept | calls ; returns stage == Stage::replay && replay ? replay-&gt;current_depth() : 0; source comment (unverified): // Report active checker depth; post-check owner preparation is depth zero while evidence · [reviewed contract](#b0088) |
| [B0089 · 490–490](../../../../../src/planner/search_session.cpp#L490) | Callable definition: void fail(StopReason reason) noexcept | calls  · [reviewed contract](#b0089) |
| [B0090 · 491–539](../../../../../src/planner/search_session.cpp#L491) | Callable definition: cd::UnitResult unit() | calls std::move, step, fail, checked; returns result; {}; growth make_shared, make_unique; source comment (unverified): // Prepare independent claim-checking worker. See docs/planner_continuations.md, grants. · [reviewed contract](#b0090) |
| [B0091 · 540–540](../../../../../src/planner/search_session.cpp#L540) | Closes surrounding scope/type. |  · [reviewed contract](#b0091) |
| [B0092 · 541–541](../../../../../src/planner/search_session.cpp#L541) | Callable definition: CertificateReplay::CertificateReplay(std::unique_ptr&lt;Impl&gt; p) noexcept : data_(std::move(p)) | calls data_, std::move · [reviewed contract](#b0092) |
| [B0093 · 542–550](../../../../../src/planner/search_session.cpp#L542) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Release unfinished replay while externally retained checked artifacts survive. See · [reviewed contract](#b0093) |
| [B0094 · 551–556](../../../../../src/planner/search_session.cpp#L551) | Callable definition: CertificateReplay CertificateReplay::create(Catalog catalog, Query query, HeightCertificate proof, ReplayOptions options) | calls validate_limits, admit, std::move, CertificateReplay; returns CertificateReplay(std::make_unique&lt;Impl&gt;(std::move(input), std::move(claim), options)); growth make_shared, make_unique; source comment (unverified): // Own the supplied claim and exact model; structural checking waits for advance and · [reviewed contract](#b0094) |
| [B0095 · 557–558](../../../../../src/planner/search_session.cpp#L557) | Explanatory comments or spacing. | source comment (unverified): // Advance retained replay only; moved-from detection precedes quantum handling. See · [reviewed contract](#b0095) |
| [B0096 · 559–563](../../../../../src/planner/search_session.cpp#L559) | Callable definition: ReplayAdvance CertificateReplay::advance(WorkQuantum quantum) noexcept | calls progress, run_quantum; returns {StopReason::moved_from, progress()}; {stopped, progress()}; source comment (unverified): // Advance retained replay only; moved-from detection precedes quantum handling. See · [reviewed contract](#b0096) |
| [B0097 · 564–565](../../../../../src/planner/search_session.cpp#L564) | Explanatory comments or spacing. | source comment (unverified): // Keep checked-prefix progress separate from final valid artifact; failed may be complete but · [reviewed contract](#b0097) |
| [B0098 · 566–579](../../../../../src/planner/search_session.cpp#L566) | Callable definition: ReplayProgress CertificateReplay::progress() const noexcept | calls checked_claims, phase; returns report; report; source comment (unverified): // Keep checked-prefix progress separate from final valid artifact; failed may be complete but · [reviewed contract](#b0098) |
| [B0099 · 580–583](../../../../../src/planner/search_session.cpp#L580) | Callable definition: SearchBinding CertificateReplay::binding() const | calls Error, cd::ArtifactFactory::binding; returns cd::ArtifactFactory::binding(data_-&gt;input) · [reviewed contract](#b0099) |
| [B0100 · 584–585](../../../../../src/planner/search_session.cpp#L584) | Explanatory comments or spacing. | source comment (unverified): // Expose only the fully published artifact, not a successful checker prefix or private · [reviewed contract](#b0100) |
| [B0101 · 586–589](../../../../../src/planner/search_session.cpp#L586) | Callable definition: std::optional&lt;CheckedCertificate&gt; CertificateReplay::checked() const noexcept | calls cd::ArtifactFactory::checked; returns {}; cd::ArtifactFactory::checked(data_-&gt;published); source comment (unverified): // Expose only the fully published artifact, not a successful checker prefix or private · [reviewed contract](#b0101) |
| [B0102 · 590–593](../../../../../src/planner/search_session.cpp#L590) | Callable definition: ReplayOptions CertificateReplay::limits() const | calls Error; returns data_-&gt;options · [reviewed contract](#b0102) |
| [B0103 · 594–595](../../../../../src/planner/search_session.cpp#L594) | Explanatory comments or spacing. | source comment (unverified): // Raise only monotone ceilings above consumption without replacing the claim or resetting · [reviewed contract](#b0103) |
| [B0104 · 596–605](../../../../../src/planner/search_session.cpp#L596) | Callable definition: LimitChange CertificateReplay::raise_limits(ReplayOptions value) noexcept | calls terminal, cd::valid_ceiling, cd::monotone_phase, cd::monotone_ceiling; returns LimitChange::terminal; LimitChange::invalid; source comment (unverified): // Raise only monotone ceilings above consumption without replacing the claim or resetting · [reviewed contract](#b0104) |
| [B0105 · 606–607](../../../../../src/planner/search_session.cpp#L606) | Explanatory comments or spacing. | source comment (unverified): // Cancel nonterminal replay and retain diagnostics; already terminal owners remain unchanged. · [reviewed contract](#b0105) |
| [B0106 · 608–615](../../../../../src/planner/search_session.cpp#L608) | Callable definition: void CertificateReplay::cancel() noexcept | calls terminal, checked_claims, reset, depth; source comment (unverified): // Cancel nonterminal replay and retain diagnostics; already terminal owners remain unchanged. · [reviewed contract](#b0106) |
| [B0107 · 616–618](../../../../../src/planner/search_session.cpp#L616) | Explanatory comments or spacing. | source comment (unverified): // Keep the owner alive while borrowing its final proof for allocating strict export; resource · [reviewed contract](#b0107) |
| [B0108 · 619–644](../../../../../src/planner/search_session.cpp#L619) | Callable definition: OracleResult minimum_tree(const Catalog& catalog, const Query& query, const SearchLimits& limits) | calls ExactSearch::create, legacy_limits, advance, progress; returns result; 2 loop sites; source comment (unverified): // Keep the owner alive while borrowing its final proof for allocating strict export; resource · [reviewed contract](#b0108) |
| [B0109 · 645–646](../../../../../src/planner/search_session.cpp#L645) | Explanatory comments or spacing. | source comment (unverified): // Summarize independent replay without exposing partial authority; finite and no-tree success · [reviewed contract](#b0109) |
| [B0110 · 647–666](../../../../../src/planner/search_session.cpp#L647) | Callable definition: CertificateReport verify_height_certificate(const Catalog& catalog, const Query& query, const HeightCertificate& proof, const Sea… | calls legacy_limits, CertificateReplay::create, advance, progress; returns result; 2 loop sites; source comment (unverified): // Summarize independent replay without exposing partial authority; finite and no-tree success · [reviewed contract](#b0110) |
| [B0111 · 667–667](../../../../../src/planner/search_session.cpp#L667) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner · [reviewed contract](#b0111) |

## B0001

[Lines 1–15](../../../../../src/planner/search_session.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:b51a803955ebad84f3210b2257b4004ae1bcdf09f215ee8d9d9ad7966f80be0b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "crown/planner/search.hpp", #include "crown/api/error.hpp", #include "continuation_budget.hpp", #include "continuation_machine.hpp", #include &lt;limits&gt;, #include &lt;new&gt;, #include &lt;utility&gt; available to src/planner/search_session.cpp; open crown::planner and anonymous helper namespace. Attached note: Require a live artifact owner before borrowing payload; this does not revalidate its proof. In this span, bind cd = continuation_detail. |
| inputs / outputs | Includes supply declarations; the listed namespace aliases bind names, and any listed constexpr bounds are constant-initialized metadata. These declarations do not run a planner search or validate a query. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | Namespace aliases own no runtime object. Any constexpr bounds in this span are fixed scalar metadata; no query owner, mutable counter or allocation grant is created by them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Preprocessing, name lookup and compile-time constant evaluation; constexpr bounds require no dynamic initialization and can occupy fixed constant storage when used. Included definitions retain their own call/construction costs. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0002

[Lines 16–19](../../../../../src/planner/search_session.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template <class T> const T& require_handle(const std::shared_ptr<const T>& value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject content access through an emptied immutable artifact handle. |
| inputs / outputs | Borrows a shared handle and returns its pointee reference when present. |
| invariants | Presence is the only check here; trusted construction establishes nested authority invariants. |
| ownership | The returned reference needs some surviving owner of that pointee. |
| failure | Null throws invalid_search_handle; diagnostic Error construction can itself allocate. |
| cost | One pointer test on success; exception construction/runtime cost occurs only on empty access. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0003

[Lines 20–21](../../../../../src/planner/search_session.cpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:d19df8aa1897065102fc0049c210cb0d8a3ef021eacdde25c8b1cfbcb024dce5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for admit: Freeze the exact supplied model; no normalization or prefix-to-original authority conversion happens at admission. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies admit; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for admit come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0004

[Lines 22–26](../../../../../src/planner/search_session.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const cd::BindingData> admit(Catalog catalog, Query query) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and freeze exactly the model supplied to session creation. |
| inputs / outputs | Owns by-value catalog/query arguments, validates them, then moves them into shared const BindingData with continuation_v1. |
| invariants | No normalization, canonical hashing, prefix-to-original conversion or physical source-program admission occurs here. Contradiction metadata is retained without replacing the body tree problem. |
| ownership | Shared BindingData owns deep standard model containers; it borrows no caller input. |
| failure | Model validation or allocation can throw before owner publication; by-value caller copies can fail before entering the function. |
| cost | Full validation and model copy/move admission are outside advance grants and can scale with complete model size. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0005

[Lines 27–28](../../../../../src/planner/search_session.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L28:sha256:89f6234c914bcb09e1a01892109a25516a2cb8129c31b7f36a24d7913041945d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for validate_limits: Validate both phase durations before creating a search owner. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies validate_limits; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for validate_limits come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 29–32](../../../../../src/planner/search_session.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_limits(const ContinuationLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject negative cumulative search phase times before admission. |
| inputs / outputs | Checks producer and replay active-time ceilings through valid_ceiling. |
| invariants | Zero, null and all work/depth values are admitted here; this is not a consumed-resource or monotonicity check. |
| ownership | Borrows options only for the call. |
| failure | Throws invalid_search_limits on a negative duration; Error allocation can propagate. |
| cost | Two scalar optional-duration checks plus failure formatting. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0007

[Lines 33–34](../../../../../src/planner/search_session.cpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L34:sha256:3edcabec26ed8833595a0e6acea2f09e48f64603501419f8d7931aa54c41c619
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for validate_limits: Admit nonnegative replay time ceilings; zero remains an operational ceiling. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies validate_limits; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for validate_limits come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0008

[Lines 35–38](../../../../../src/planner/search_session.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_limits(const ReplayOptions& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject negative standalone replay active time. |
| inputs / outputs | Checks only limits.limits active_time. |
| invariants | Work/depth zero are operational stops, not invalid options. |
| ownership | Borrows ReplayOptions without retaining it. |
| failure | Negative duration throws invalid_search_limits; no replay starts. |
| cost | One optional-duration check and possible error construction. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0009

[Lines 39–40](../../../../../src/planner/search_session.cpp#L39); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L40:sha256:3761f4fa18a01c780e888d9a16436008ce65cd3816ed17b694296688dabf9d81
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for reason_text: Return static stop text; allocating compatibility messages are assembled by the caller. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies reason_text; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for reason_text come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0010

[Lines 41–54](../../../../../src/planner/search_session.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view reason_text(StopReason reason) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map blocking-adapter stop enums to stable diagnostic text. |
| inputs / outputs | Returns a literal view for selected stops and search incomplete for other values. |
| invariants | Text is descriptive; it neither changes owner state nor validates evidence. |
| ownership | Borrows static literals, so the view survives this call. |
| failure | Noexcept mapping; callers may allocate when copying/concatenating the returned text. |
| cost | Fixed enum dispatch without per-call string allocation. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0011

[Lines 55–56](../../../../../src/planner/search_session.cpp#L55); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L56:sha256:906df956930d74911e446f31e75fda15f869f74615b6fcc28aa6f3f766954173
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for legacy_time: Check legacy time range before multiplying milliseconds into nanoseconds. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies legacy_time; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for legacy_time come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0012

[Lines 57–64](../../../../../src/planner/search_session.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::chrono::nanoseconds> legacy_time(const SearchLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert legacy milliseconds into a representable active-nanosecond ceiling. |
| inputs / outputs | Absent time stays absent; valid signed millisecond count multiplies by one million. |
| invariants | The maximum precheck ensures the multiplication fits int64; negative time rejects instead of silently wrapping. |
| ownership | Returns a scalar optional; borrows the legacy options only during conversion. |
| failure | Throws invalid_search_limits for negative/too-large values before multiplication. |
| cost | Fixed scalar checks/arithmetic; error message allocation is a separate failure cost. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0013

[Lines 65–66](../../../../../src/planner/search_session.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L66:sha256:530cbb4bfe855ab87be5267858466f196c060c8f44f8451b74b6b3700a0e66a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for legacy_limits: Map legacy work/time independently to both phase ledgers; literal_scope_limit belongs to the literal oracle. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies legacy_limits; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for legacy_limits come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0014

[Lines 67–70](../../../../../src/planner/search_session.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ContinuationLimits legacy_limits(const SearchLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map blocking compatibility ceilings to the retained owner model. |
| inputs / outputs | Copies one work/time PhaseCeiling independently to producer and replay, with recursion_limit as logical depth. |
| invariants | literal_scope_limit is intentionally not mapped because production partition search does not materialize the literal power-set universe. |
| ownership | Returns value-owned options, not a live ledger. |
| failure | legacy_time errors propagate before owner creation. |
| cost | Fixed configuration construction; no query or proof work. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0016

[Lines 72–119](../../../../../src/planner/search_session.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StopReason run_quantum(Owner& owner, WorkQuantum quantum) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run retained owner units under per-call and cumulative resource accounting. |
| inputs / outputs | Checks invalid/zero grants and terminal state, samples active ledgers, charges an attempt, executes one owner unit, records depth/commit or a stop. |
| invariants | Negative time precedes zero work/time; inert/invalid paths do not mutate last_stop or sample clocks. Attempts include depth-blocked and allocation-failed units; commits exclude those. Phase changes redirect the next unit ledger without double charging. |
| ownership | Borrows the exclusive owner for this call; ActiveMeter retains a ledger pointer only within the call. |
| failure | bad_alloc increments saturating failure diagnostics and returns allocation_failure with retained pending work; all other exceptions mark terminal internal_failure. Counter overflow is terminal; resource/depth stops are resumable. |
| cost | One loop per attempted unit plus clock samples; worker/container/allocator costs remain variable and time checks are cooperative. Meter destruction accounts the final active segment before progress is returned. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
const auto stop = [&](StopReason reason) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit the last stop reason for active-loop exits. |
| inputs / outputs | Assigns owner.last_stop and returns the same enum. |
| invariants | Invalid, zero and already-terminal early paths bypass this closure, preserving stored progress. |
| ownership | Captures the live exclusive owner by reference for this call only. |
| failure | Noexcept scalar assignment; it allocates no diagnostic. |
| cost | Fixed state update; final ActiveMeter sampling still runs on return. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0017

[Lines 120–124](../../../../../src/planner/search_session.cpp#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L124:sha256:5536854ccd191fd9a1c2f6343fe351081c103978469f9d994ef410d85f2d0bc2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace, then open continuation_detail within crown::planner. The attached note is caller guidance: Private wrapping does not perform validation; callers must already hold the matching checked authority. See docs/planner_continuations.md, authority. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0018

[Lines 125–131](../../../../../src/planner/search_session.cpp#L125); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ArtifactFactory {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Limit public authority-handle construction to trusted private owners. |
| inputs / outputs | Five static adapters wrap internal shared payloads using friend-only constructors. |
| invariants | Factory itself performs no validity, binding or proof checks; callers must supply the corresponding completed authority. |
| ownership | Moves shared owners into public immutable handles without copying payloads. |
| failure | Noexcept wrappers assume trusted nested invariants; a null payload yields an empty handle rather than manufacturing evidence. |
| cost | Small handle transfers; releasing unrelated last owners remains a lifetime cost. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

```text
static SearchBinding binding(std::shared_ptr<const BindingData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap trusted exact admitted model ownership as SearchBinding. |
| inputs / outputs | Moves the private shared payload into the friend-only constructor. |
| invariants | This adapter does not prove exact admitted model or compare bindings; calling stage establishes that invariant. |
| ownership | Returned handle retains the supplied payload; no tree/query/claim is recopied. |
| failure | Noexcept wrapper; null remains an empty handle and is checked by later content access. |
| cost | Shared ownership transfer without payload/control-block allocation. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

```text
static ValidatedIncumbent incumbent(std::shared_ptr<const IncumbentData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap trusted P02 checked upper only ownership as ValidatedIncumbent. |
| inputs / outputs | Moves the private shared payload into the friend-only constructor. |
| invariants | This adapter does not prove P02 checked upper only or compare bindings; calling stage establishes that invariant. |
| ownership | Returned handle retains the supplied payload; no tree/query/claim is recopied. |
| failure | Noexcept wrapper; null remains an empty handle and is checked by later content access. |
| cost | Shared ownership transfer without payload/control-block allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

```text
static VerifiedOptimum optimum(std::shared_ptr<const OptimumData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap trusted matching completed upper/lower proof ownership as VerifiedOptimum. |
| inputs / outputs | Moves the private shared payload into the friend-only constructor. |
| invariants | This adapter does not prove matching completed upper/lower proof or compare bindings; calling stage establishes that invariant. |
| ownership | Returned handle retains the supplied payload; no tree/query/claim is recopied. |
| failure | Noexcept wrapper; null remains an empty handle and is checked by later content access. |
| cost | Shared ownership transfer without payload/control-block allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

```text
static VerifiedInfeasible infeasibility(std::shared_ptr<const InfeasibleData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap trusted completed infinite-root proof for this binding ownership as VerifiedInfeasible. |
| inputs / outputs | Moves the private shared payload into the friend-only constructor. |
| invariants | This adapter does not prove completed infinite-root proof for this binding or compare bindings; calling stage establishes that invariant. |
| ownership | Returned handle retains the supplied payload; no tree/query/claim is recopied. |
| failure | Noexcept wrapper; null remains an empty handle and is checked by later content access. |
| cost | Shared ownership transfer without payload/control-block allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

```text
static CheckedCertificate checked(std::shared_ptr<const CheckedCertificateData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap trusted fully published independent replay result ownership as CheckedCertificate. |
| inputs / outputs | Moves the private shared payload into the friend-only constructor. |
| invariants | This adapter does not prove fully published independent replay result or compare bindings; calling stage establishes that invariant. |
| ownership | Returned handle retains the supplied payload; no tree/query/claim is recopied. |
| failure | Noexcept wrapper; null remains an empty handle and is checked by later content access. |
| cost | Shared ownership transfer without payload/control-block allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0019

[Lines 132–132](../../../../../src/planner/search_session.cpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L132:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0020

[Lines 133–133](../../../../../src/planner/search_session.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchBinding::SearchBinding(std::shared_ptr<const cd::BindingData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private model snapshot ownership into a public SearchBinding handle. |
| inputs / outputs | Moves one shared payload into data_; no traversal or validation occurs. |
| invariants | Only ArtifactFactory can invoke this constructor; trusted publishing stages establish the payload meaning. |
| ownership | Retains model snapshot through shared ownership; input caller storage is not borrowed. |
| failure | Declared noexcept; it can hold null only as a private empty handle, whose content getters reject. |
| cost | One shared-handle move without payload allocation. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0021

[Lines 134–134](../../../../../src/planner/search_session.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SearchBinding::valid() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether this SearchBinding handle retains its payload. |
| inputs / outputs | Returns the Boolean presence of data_. |
| invariants | This is a moved/empty-handle test, not a fresh proof or nested-payload validator. |
| ownership | Reads the shared owner and returns a scalar. |
| failure | Noexcept; safe after move. |
| cost | One pointer-presence read without traversal/allocation. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0022

[Lines 135–135](../../../../../src/planner/search_session.cpp#L135); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Catalog& SearchBinding::catalog() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact admitted catalog metadata. |
| inputs / outputs | Returns BindingData.catalog after require_handle. |
| invariants | Catalog content, schemas, constraints and statistics remain as admitted; no physical-program conversion occurs. |
| ownership | Reference survives while any binding/evidence owner retains BindingData; a temporary SearchBinding alone is not a lifetime guarantee. |
| failure | Empty handle throws invalid_search_handle. |
| cost | Reference return without catalog copy; invalid-access error may allocate. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0023

[Lines 136–136](../../../../../src/planner/search_session.cpp#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Query& SearchBinding::query() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact admitted query, including its local occurrence/head identity. |
| inputs / outputs | Returns BindingData.query after presence checking. |
| invariants | An induced prefix remains that prefix; later consumers must not treat it as the original query. |
| ownership | Reference needs a surviving binding/evidence owner, not the source caller object. |
| failure | Empty/moved handle throws invalid_search_handle. |
| cost | Reference return without copying query vectors or terms. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0024

[Lines 137–137](../../../../../src/planner/search_session.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AccountingVersion SearchBinding::accounting() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the admitted controlled-transition accounting version. |
| inputs / outputs | Returns BindingData.accounting by value. |
| invariants | Current admission sets continuation_v1; this is not a runtime-byte or historical-work equivalence claim. |
| ownership | Scalar return owns no binding data. |
| failure | require_handle rejects an empty artifact. |
| cost | One checked scalar read; error construction only on empty access. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0025

[Lines 138–138](../../../../../src/planner/search_session.cpp#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ValidatedIncumbent::ValidatedIncumbent(std::shared_ptr<const cd::IncumbentData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private checked upper tree/report/binding ownership into a public ValidatedIncumbent handle. |
| inputs / outputs | Moves one shared payload into data_; no traversal or validation occurs. |
| invariants | Only ArtifactFactory can invoke this constructor; trusted publishing stages establish the payload meaning. |
| ownership | Retains checked upper tree/report/binding through shared ownership; input caller storage is not borrowed. |
| failure | Declared noexcept; it can hold null only as a private empty handle, whose content getters reject. |
| cost | One shared-handle move without payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0026

[Lines 139–139](../../../../../src/planner/search_session.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool ValidatedIncumbent::valid() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether this ValidatedIncumbent handle retains its payload. |
| inputs / outputs | Returns the Boolean presence of data_. |
| invariants | This is a moved/empty-handle test, not a fresh proof or nested-payload validator. |
| ownership | Reads the shared owner and returns a scalar. |
| failure | Noexcept; safe after move. |
| cost | One pointer-presence read without traversal/allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0027

[Lines 140–140](../../../../../src/planner/search_session.cpp#L140); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchBinding ValidatedIncumbent::binding() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the checked upper exact model independently of the incumbent handle. |
| inputs / outputs | Builds SearchBinding from CheckedUpper.binding. |
| invariants | Upper validity does not permit binding substitution or prefix-to-original transport. |
| ownership | Returned shared owner outlives the incumbent/facade if retained. |
| failure | Empty outer handle rejects; nested authority is trusted from publication. |
| cost | Shared-handle copy/wrap without model copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0028

[Lines 141–141](../../../../../src/planner/search_session.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const FreeConnexTree& ValidatedIncumbent::tree() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the complete P02-checked upper witness. |
| inputs / outputs | Returns the retained CheckedUpper.tree by const reference. |
| invariants | The witness is valid for its exact binding; it supplies no lower-bound evidence. |
| ownership | Reference requires some surviving owner of that CheckedUpper/tree; returning it does not add ownership. |
| failure | Empty incumbent rejects; trusted upper must have non-null tree. |
| cost | Reference return without traversal or copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0029

[Lines 142–142](../../../../../src/planner/search_session.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t ValidatedIncumbent::height() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the native-height upper bound measured by P02. |
| inputs / outputs | Returns CheckedUpper.height. |
| invariants | Generalized weight is zero; this height alone is not a structural optimum or a latency score. |
| ownership | Returns an independent scalar. |
| failure | Empty handle rejects through require_handle. |
| cost | Checked scalar read without recalculation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/tree_plans.md §What is checked](../../../../tree_plans.md) |

## B0030

[Lines 143–143](../../../../../src/planner/search_session.cpp#L143); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedOptimum::VerifiedOptimum(std::shared_ptr<const cd::OptimumData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private matching upper and complete certificate ownership into a public VerifiedOptimum handle. |
| inputs / outputs | Moves one shared payload into data_; no traversal or validation occurs. |
| invariants | Only ArtifactFactory can invoke this constructor; trusted publishing stages establish the payload meaning. |
| ownership | Retains matching upper and complete certificate through shared ownership; input caller storage is not borrowed. |
| failure | Declared noexcept; it can hold null only as a private empty handle, whose content getters reject. |
| cost | One shared-handle move without payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0031

[Lines 144–144](../../../../../src/planner/search_session.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool VerifiedOptimum::valid() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether this VerifiedOptimum handle retains its payload. |
| inputs / outputs | Returns the Boolean presence of data_. |
| invariants | This is a moved/empty-handle test, not a fresh proof or nested-payload validator. |
| ownership | Reads the shared owner and returns a scalar. |
| failure | Noexcept; safe after move. |
| cost | One pointer-presence read without traversal/allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0032

[Lines 145–145](../../../../../src/planner/search_session.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchBinding VerifiedOptimum::binding() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the exact query model whose optimum was proved. |
| inputs / outputs | Wraps the binding reachable through the optimum checked upper. |
| invariants | A prefix optimum proves only the admitted prefix, even if a caller knows an enclosing original query. |
| ownership | Returned SearchBinding shares the immutable model. |
| failure | Empty optimum rejects; trusted publication guarantees nested upper owners. |
| cost | Shared ownership copy without model traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0033

[Lines 146–146](../../../../../src/planner/search_session.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ValidatedIncumbent VerifiedOptimum::upper() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract an owning checked-upper view from a proved optimum. |
| inputs / outputs | Returns a ValidatedIncumbent wrapping the retained optimum upper. |
| invariants | Extraction retains its original checked tree and binding; it does not generate alternative trees. |
| ownership | Returned upper owner remains usable after optimum/facade destruction. |
| failure | Empty optimum rejects. |
| cost | Shared-handle copy/wrap without witness copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0034

[Lines 147–147](../../../../../src/planner/search_session.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t VerifiedOptimum::height() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the height matched by upper and complete independent lower proof. |
| inputs / outputs | Returns the optimum checked upper native height. |
| invariants | Typed publication, not this accessor, established minimality for the exact binding. |
| ownership | Returns a scalar detached from artifact lifetime. |
| failure | Empty handle throws invalid_search_handle. |
| cost | Checked scalar read without replay. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0035

[Lines 148–148](../../../../../src/planner/search_session.cpp#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const HeightCertificate& VerifiedOptimum::certificate() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the complete certificate retained by optimum authority. |
| inputs / outputs | Returns the original proof document stored with the optimum. |
| invariants | The owning optimum supplies the exact admitted binding for this document; editing a copied aggregate cannot create authority. |
| ownership | Borrow requires a surviving proof/optimum owner; the reference itself does not retain it. |
| failure | Empty optimum rejects before dereference. |
| cost | Reference return without proof-table copying. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0036

[Lines 149–149](../../../../../src/planner/search_session.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
VerifiedInfeasible::VerifiedInfeasible(std::shared_ptr<const cd::InfeasibleData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private binding and complete infinite-root proof ownership into a public VerifiedInfeasible handle. |
| inputs / outputs | Moves one shared payload into data_; no traversal or validation occurs. |
| invariants | Only ArtifactFactory can invoke this constructor; trusted publishing stages establish the payload meaning. |
| ownership | Retains binding and complete infinite-root proof through shared ownership; input caller storage is not borrowed. |
| failure | Declared noexcept; it can hold null only as a private empty handle, whose content getters reject. |
| cost | One shared-handle move without payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0037

[Lines 150–150](../../../../../src/planner/search_session.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool VerifiedInfeasible::valid() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether this VerifiedInfeasible handle retains its payload. |
| inputs / outputs | Returns the Boolean presence of data_. |
| invariants | This is a moved/empty-handle test, not a fresh proof or nested-payload validator. |
| ownership | Reads the shared owner and returns a scalar. |
| failure | Noexcept; safe after move. |
| cost | One pointer-presence read without traversal/allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0038

[Lines 151–151](../../../../../src/planner/search_session.cpp#L151); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchBinding VerifiedInfeasible::binding() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the exact model independently proved to have no admissible tree. |
| inputs / outputs | Wraps InfeasibleData.binding. |
| invariants | No-tree proof for a residual/prefix does not imply no-tree proof for the complete original query. |
| ownership | Returned handle shares binding ownership. |
| failure | Empty infeasibility handle rejects. |
| cost | Shared-handle copy without model copying. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0039

[Lines 152–152](../../../../../src/planner/search_session.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const HeightCertificate& VerifiedInfeasible::certificate() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the complete infinite-root certificate. |
| inputs / outputs | Returns InfeasibleData.proof with absent finite minimum/upper tree. |
| invariants | Infeasibility follows completed root replay, not a resource stop or absent incumbent. |
| ownership | Reference needs a retained proof/infeasibility owner. |
| failure | Empty handle rejects. |
| cost | Reference return; explicit certificate copies may allocate and traverse claims. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0040

[Lines 153–153](../../../../../src/planner/search_session.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CheckedCertificate::CheckedCertificate(std::shared_ptr<const cd::CheckedCertificateData> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private checked replay and typed outcome ownership into a public CheckedCertificate handle. |
| inputs / outputs | Moves one shared payload into data_; no traversal or validation occurs. |
| invariants | Only ArtifactFactory can invoke this constructor; trusted publishing stages establish the payload meaning. |
| ownership | Retains checked replay and typed outcome through shared ownership; input caller storage is not borrowed. |
| failure | Declared noexcept; it can hold null only as a private empty handle, whose content getters reject. |
| cost | One shared-handle move without payload allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0041

[Lines 154–154](../../../../../src/planner/search_session.cpp#L154); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool CheckedCertificate::valid() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether this CheckedCertificate handle retains its payload. |
| inputs / outputs | Returns the Boolean presence of data_. |
| invariants | This is a moved/empty-handle test, not a fresh proof or nested-payload validator. |
| ownership | Reads the shared owner and returns a scalar. |
| failure | Noexcept; safe after move. |
| cost | One pointer-presence read without traversal/allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0042

[Lines 155–155](../../../../../src/planner/search_session.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchBinding CheckedCertificate::binding() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the model used by independent external-certificate replay. |
| inputs / outputs | Wraps CheckedProof.binding from the published artifact. |
| invariants | Checking relates the typed claim to this model; serialized exact-source binding is an IO contract. |
| ownership | Returned owner retains BindingData independently of the replay facade. |
| failure | Empty artifact rejects. |
| cost | Shared-handle copy/wrap without model copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0043

[Lines 156–156](../../../../../src/planner/search_session.cpp#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const HeightCertificate& CheckedCertificate::certificate() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact independently replayed claim document. |
| inputs / outputs | Returns CheckedProof.proof by const reference. |
| invariants | No mutable aggregate supplied by a caller can replace this retained proof through the public API. |
| ownership | Reference lives with some surviving checked/proof owner. |
| failure | Empty artifact rejects. |
| cost | Reference return without claim-table copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0044

[Lines 157–161](../../../../../src/planner/search_session.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VerifiedOptimum> CheckedCertificate::optimum() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract finite optimum authority when the replayed claim has a checked upper. |
| inputs / outputs | Returns an owning VerifiedOptimum if stored, otherwise nullopt. |
| invariants | The absence may mean checked infeasibility; it is not an incomplete-claim success path. |
| ownership | Returned optional handle shares immutable upper/lower evidence. |
| failure | Empty outer CheckedCertificate rejects; no proof is replayed here. |
| cost | Optional/shared-handle construction without evidence allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0045

[Lines 162–166](../../../../../src/planner/search_session.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VerifiedInfeasible> CheckedCertificate::infeasibility() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract empty-family authority from an independently checked infinite claim. |
| inputs / outputs | Returns owning VerifiedInfeasible when stored, otherwise nullopt. |
| invariants | A finite checked optimum has no infeasibility artifact; absent upper alone outside this type is insufficient. |
| ownership | Returned optional retains model/proof independently. |
| failure | Empty outer handle rejects. |
| cost | Optional/shared ownership copy without certificate traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0046

[Lines 167–172](../../../../../src/planner/search_session.cpp#L167); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ExactSearch::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the complete producer-to-proof handshake and its independent resource ledgers. |
| inputs / outputs | Retains admitted input/options, four worker owners, candidate/tree/check/proof scratch and published or prepared artifacts. |
| invariants | Only stage complete exposes optimum/infeasibility. Incumbent publication follows P02; final owner preparation follows complete independent replay. |
| ownership | Owns workers exclusively and artifacts through shared handles. Parked workers remain retained until cancellation/destruction, so logical active depth is not total retained frame count. |
| failure | Per-stage throwing preparation precedes stage changes; terminal failure retains scratch, and cancel is a no-op once terminal. |
| cost | Retained worker/memo/proof payloads may be exponential; driver fields add fixed ownership overhead. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0047

[Lines 173–177](../../../../../src/planner/search_session.cpp#L173); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stage {
    producer_shell, producer, witness_shell, witness, validation_shell, validation,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode the exact driver handshake and allocation-safe publication boundaries. |
| inputs / outputs | Transitions from inert worker shells through candidate/P02/incumbent, proof replay and typed result preparation to terminal states. |
| invariants | Ordinal order at replay_shell selects replay accounting; prepared optimum/infeasibility stays private until publish_final completes. |
| ownership | Enum is owned by Impl; it owns no worker itself. |
| failure | Failed preparation leaves the same stage; terminal failure/cancellation cannot resume. |
| cost | Fixed stage state; not a bound on how many worker units execute. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0048

[Lines 178–201](../../../../../src/planner/search_session.cpp#L178); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L178-L201:sha256:22494ddf577efc8801648706c729d1851bef3c9872629cb394eb3bfe35957b2c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain input, options, producer_ledger, replay_ledger, stage, last_stop, failure, revision, producer_finished, retained_statistics, producer, witness, validation, replay, candidate, tree, checked_upper, proof, checked_proof, incumbent, final_upper, optimum, infeasibility in ExactSearch::Impl across its lifetime. |
| inputs / outputs | These are stored fields for ExactSearch::Impl, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | shared_ptr members retain their pointees through shared ownership; this span does not deep-copy them; unique_ptr members exclusively own their implementation or child-machine objects. |
| failure | The declarations add no exception path by themselves. Constructing owner/container members or growing them later can fail through the surrounding object-creation or update path. |
| cost | Adds fixed per-instance storage for the listed values and owner/container handles; shared_ptr members retain shared payloads without a deep copy at this declaration; child implementation allocation occurs in its factory or constructor. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0049

[Lines 202–203](../../../../../src/planner/search_session.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(std::shared_ptr<const cd::BindingData> value, SearchOptions opts)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create inert exact-driver state and zeroed phase ledgers. |
| inputs / outputs | Moves binding, copies options and initializes producer/replay ResourceLedgers from their respective ceilings. |
| invariants | No workers, coroutine frames or search traversal start here. |
| ownership | Owns the binding and value options; worker/artifact owners begin empty. |
| failure | Outer implementation allocation can fail; constructor assumes prior admission/option validation. |
| cost | Fixed ownership/ledger setup without query traversal; model admission happened separately. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0050

[Lines 204–204](../../../../../src/planner/search_session.cpp#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool terminal() const noexcept { return stage == Stage::complete || stage == Stage::failed || stage == Stage::cancelled; }
  StopReason terminal_reason() const noexcept {

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify all exact-driver states that cannot advance further. |
| inputs / outputs | Returns true for complete, failed or cancelled, false for saved work/resource stops. |
| invariants | A failed terminal still owns its scratch; terminal does not imply a valid result or memory release. |
| ownership | Reads Impl stage and returns a scalar. |
| failure | Noexcept; this helper supplies no evidence by itself. |
| cost | Fixed enum comparisons. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0051

[Lines 205–208](../../../../../src/planner/search_session.cpp#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StopReason terminal_reason() const noexcept {
    return stage == Stage::complete ? StopReason::complete :
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate an already-terminal exact stage to its stable stop reason. |
| inputs / outputs | Complete maps complete, cancelled maps cancelled, otherwise returns saved failure. |
| invariants | Caller uses it after terminal(); it does not clear last_stop or publish artifacts. |
| ownership | Returns a scalar from retained state. |
| failure | Noexcept; misuse on nonterminal may return none and is outside driver control flow. |
| cost | Fixed stage tests. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0052

[Lines 209–209](../../../../../src/planner/search_session.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool replay_phase() const noexcept { return stage >= Stage::replay_shell; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the replay accounting side for the nonterminal exact driver. |
| inputs / outputs | Compares stage ordinal with replay_shell. |
| invariants | Preparation after lower replay is replay work; terminal failed/cancelled ordinals also compare true but run_quantum stops before executing them. |
| ownership | Reads owned stage, retains no ledger borrow. |
| failure | Noexcept scalar classifier; it is not evidence of where a prior failure occurred. |
| cost | One ordinal comparison. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0053

[Lines 210–210](../../../../../src/planner/search_session.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
cd::ResourceLedger& ledger() noexcept { return replay_phase() ? replay_ledger : producer_ledger; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the active exact phase ledger for one metered unit. |
| inputs / outputs | Returns producer or replay ledger according to saved stage. |
| invariants | run_quantum keeps a reference to the ledger charged for the current unit even if that unit changes stage. |
| ownership | Reference is backed by Impl and must not outlive it. |
| failure | Noexcept; terminal early-return avoids advancing an arbitrary terminal ledger. |
| cost | Fixed dispatch; no ledger copying. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0054

[Lines 211–212](../../../../../src/planner/search_session.cpp#L211); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L211-L212:sha256:cf33a44917eb52d089b9ee0cf5825c84e3682330c113430a61a0fed98c1ed84c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for current_depth: Report active-worker depth only; parked owners remain retained separately. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies current_depth; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for current_depth come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0055

[Lines 213–219](../../../../../src/planner/search_session.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t current_depth() const noexcept {
    if (stage == Stage::producer && producer)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read logical depth from the currently executing exact worker. |
| inputs / outputs | Delegates to producer, witness, validator or replay only in its active stage; shell/publication stages return zero. |
| invariants | Parked producer frames and BFS width are retained memory, not added simultaneous active-worker depth. |
| ownership | Returns a scalar without taking ownership. |
| failure | Noexcept with private stage/worker consistency assumptions. |
| cost | At most four stage tests plus saved-depth observation; no frame traversal. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0056

[Lines 220–220](../../../../../src/planner/search_session.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fail(StopReason reason) noexcept { failure = reason; stage = Stage::failed; }
  cd::UnitResult unit() {
    const cd::UnitContext
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make an exact-driver invariant failure terminal without replacing prior checked uppers. |
| inputs / outputs | Stores failure and selects failed stage. |
| invariants | No optimum/infeasibility is exposed; already checked best-found incumbent can remain valid and retrievable. |
| ownership | Retains worker scratch and published owners until destruction or owner replacement. |
| failure | Noexcept; cancel later does nothing because this state is terminal. |
| cost | Two scalar writes; no eager teardown or diagnostic allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0057

[Lines 221–338](../../../../../src/planner/search_session.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
cd::UnitResult unit() {
    const cd::UnitContext context{options.limits.logical_depth};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one exact-driver stage or one delegated saved worker action. |
| inputs / outputs | Creates inert shells, performs candidate/P02 handshake, drives producer/replay, prepares typed owners and publishes final completion. |
| invariants | Every allocating shell/control block is prepared locally before stage change. Checked upper publication precedes producer acknowledgment; complete lower replay precedes final authority. |
| ownership | Mutates the exclusive Impl and retains all shared inputs/artifacts through the handshake. |
| failure | Allocation propagates to run_quantum for same-stage retry; malformed internal events become terminal internal_failure. |
| cost | Delegated work is metered once by the facade. Shell creation and artifact releases still have actual allocator/lifetime costs. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::producer_shell: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the producer before installing its stage. |
| inputs / outputs | make_unique ProducerMachine(input), then assign producer and stage. |
| invariants | No preprocessing runs inside the inert shell constructor. |
| ownership | Local next owns construction until commit; Impl then owns it. |
| failure | Allocation failure leaves producer_shell pending. |
| cost | Implementation/default-container allocations, without query traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::producer: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate one producer unit and receive candidate or completed certificate. |
| inputs / outputs | Candidate event retains candidate then starts witness shell; producer_complete retains proof and marks producer_finished. |
| invariants | Missing required event payload becomes internal_failure. Producer completion does not imply independent lower replay. |
| ownership | Shares candidate/proof ownership supplied by producer. |
| failure | Worker allocation/depth events propagate; stage changes only after a non-null payload is retained. |
| cost | One delegated transition plus handle reads. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::witness_shell: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an arena-retaining candidate materializer. |
| inputs / outputs | Creates WitnessMachine(input,candidate), then commits worker/stage. |
| invariants | The producer remains parked with pending candidate until checked upper publication. |
| ownership | Local construction owns next; candidate retains its arena. |
| failure | Allocation leaves this shell stage pending. |
| cost | Inert copier allocation, with no hidden tree traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::witness: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy one saved candidate-tree action before P02 checking. |
| inputs / outputs | On witness_complete retains a non-null concrete tree and selects validation_shell. |
| invariants | Complete copying alone does not establish structural validity. |
| ownership | Shared tree survives copier and retains copied payload. |
| failure | Null completion is internal_failure; worker allocation/depth stops retain copying state. |
| cost | One delegated materialization transition plus ownership transfer. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::validation_shell: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the independent P02 validator for the whole candidate. |
| inputs / outputs | Creates ValidationMachine(input,tree) locally, then installs it. |
| invariants | No producer claim substitutes for the independent rule checks. |
| ownership | Retains binding and concrete candidate tree in the validator. |
| failure | Constructor allocation leaves the stage unadvanced. |
| cost | Inert implementation/report/default-container allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::validation: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive independent upper checking before incumbent preparation. |
| inputs / outputs | upper_invalid fails; upper_valid retains checked authority and selects publish_incumbent. |
| invariants | A tree/progress Boolean alone cannot satisfy the required checked owner. |
| ownership | Shares CheckedUpper only after ValidationMachine publication. |
| failure | Missing checked payload or invalid producer witness is terminal internal_failure; depth/allocations retain the pending check. |
| cost | One independent validation transition and handle observation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::publish_incumbent: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare complete owning upper publication before acknowledging the producer. |
| inputs / outputs | Allocates IncumbentData{checked_upper}, replaces incumbent, then selects accept_incumbent. |
| invariants | Failure preserves the previous published upper; strict withholds the handle but still records its scalar height. |
| ownership | Shared immutable owner retains checked tree/report/input. |
| failure | Control-block allocation propagates before incumbent/stage replacement. |
| cost | One owner allocation/refcount assembly; prior-owner release follows actual lifetime costs. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::accept_incumbent:
        producer->accept_upper
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete the producer handshake only after incumbent ownership is ready. |
| inputs / outputs | Supplies checked upper, clears producer pending, drops candidate and resumes producer. |
| invariants | The candidate is never acknowledged before independent validation and owning publication succeed. |
| ownership | Producer and facade retain the checked upper; other candidate owners can retain the arena. |
| failure | Nonthrowing handle/reset protocol; input invariants were checked in prior stages. |
| cost | Handle replacement/release and producer reset, with no new tree traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::replay_shell: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare independent whole-certificate replay after producer completion. |
| inputs / outputs | Creates ReplayMachine(input,proof) then selects replay. |
| invariants | The new worker rebuilds semantics independently; producer_complete does not grant optimum authority. |
| ownership | Shares the exact admitted binding and complete immutable certificate. |
| failure | Allocation retains replay_shell for retry. |
| cost | Inert replay implementation/default-container allocations. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::replay: {
        const auto result = replay->step(context);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive one saved independent lower-proof action. |
| inputs / outputs | proof_invalid fails; proof_valid retains non-null CheckedProof and starts final owner preparation. |
| invariants | This internal search treats its own rejected certificate as internal_failure, distinct from standalone external invalid_certificate. |
| ownership | Retains CheckedProof and all checked input/evidence owners. |
| failure | Invalid/missing authority is terminal; worker depth/allocating actions retain retryable state. |
| cost | One checker transition without double charging its internal jobs. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::final_incumbent:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the final independently replayed upper wrapper when finite. |
| inputs / outputs | If CheckedProof has upper, allocate IncumbentData into final_upper; otherwise proceed without one. |
| invariants | An infinite-root proof has no final upper. Existing incumbent is not overwritten during failed preparation. |
| ownership | Private final_upper owns the replay-checked upper. |
| failure | Allocation leaves final_incumbent pending. |
| cost | One optional owner allocation; evidence payload is shared. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::final_result:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare finite optimum or infeasibility data for the admitted model. |
| inputs / outputs | Uses final_upper with proof for OptimumData, or input with proof for InfeasibleData; then selects publish_final. |
| invariants | Prepared typed payload remains inaccessible through public optimum/infeasibility getters until stage complete. |
| ownership | Owns result data privately while proof/input are shared. |
| failure | Allocation leaves the same preparation stage and prior public authority unchanged. |
| cost | One owner/control-block allocation and fixed handle assembly. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::publish_final:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit completed exact authority after every required owner exists. |
| inputs / outputs | If finite replace incumbent with final_upper, then set complete. |
| invariants | Only this commit lets public final accessors expose the already prepared optimum/infeasibility. |
| ownership | Retains final artifacts independently of workers/facade lifetime. |
| failure | Nonthrowing shared-handle/scalar publication under trusted invariants. |
| cost | Handle replacement plus any actual prior release; no proof replay or allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::complete: case Stage::failed: case Stage::cancelled: break;
    }
    return {};
  }
  SearchPhase
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep terminal driver unit dispatch inert. |
| inputs / outputs | No stage body runs for complete/failed/cancelled. |
| invariants | run_quantum normally returns before calling unit in a terminal state. |
| ownership | Retains all existing owner fields unchanged. |
| failure | No new failure or authority is produced. |
| cost | Fixed dispatch/no-op; final teardown belongs to lifetime operations. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0058

[Lines 339–351](../../../../../src/planner/search_session.cpp#L339); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchPhase phase() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate private driver/worker stage into public progress phase. |
| inputs / outputs | Delegates active producer phase, groups witness/P02 stages, maps terminal stages and reports replay for remaining proof/result stages. |
| invariants | Phase can say replay after independent root checking while typed owner preparation is still unfinished. |
| ownership | Returns a scalar without exposing worker state. |
| failure | Noexcept; private stage/worker correspondence is assumed. |
| cost | Fixed switch plus optional saved producer phase read. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0059

[Lines 352–352](../../../../../src/planner/search_session.cpp#L352); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L352-L352:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0060

[Lines 353–353](../../../../../src/planner/search_session.cpp#L353); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExactSearch::ExactSearch(std::unique_ptr<Impl> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the fully admitted exclusive exact-driver implementation. |
| inputs / outputs | Moves a prepared unique_ptr into data_. |
| invariants | Only create invokes this private constructor; no search unit executes here. |
| ownership | Takes exclusive Impl ownership without moving its payload. |
| failure | Noexcept pointer adoption. |
| cost | One unique_ptr move with no query/frame traversal. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0061

[Lines 354–362](../../../../../src/planner/search_session.cpp#L354); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExactSearch::~ExactSearch() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release an exact session and every unfinished owner it still retains. |
| inputs / outputs | Destroys Impl and its worker/artifact fields. |
| invariants | Published handles held elsewhere remain valid; destruction does not imply no-tree evidence. |
| ownership | Last shared owners may release input/tree/proof payload; producer/witness destruction cancels owned frames. |
| failure | Nonthrowing RAII under contained model/worker destructor contracts. |
| cost | Potentially size-dependent worker, arena, memo and artifact teardown outside grant accounting. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
ExactSearch::ExactSearch(ExactSearch&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one saved exact-session owner without relocating Impl. |
| inputs / outputs | Moves unique_ptr; a distinct source becomes empty. |
| invariants | Worker/borrowed internal addresses stay stable; source progress becomes moved_from. |
| ownership | Transfers exclusive ownership with no state copy. |
| failure | Noexcept; moved-from binding/policy/limits reject while progress/advance have explicit moved behavior. |
| cost | One pointer transfer without search traversal. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
ExactSearch& ExactSearch::operator=(ExactSearch&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace an exact-session owner with another saved session. |
| inputs / outputs | Default unique_ptr move assignment releases the old destination Impl before taking source ownership. |
| invariants | Any separately retained artifacts survive old-session teardown; no query state merges. |
| ownership | Transfers exclusive ownership and may synchronously destroy previous destination state. |
| failure | Noexcept under owned destructors; self-move follows unique_ptr semantics. |
| cost | Pointer transfer plus potentially full old-worker/memo/artifact teardown. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0062

[Lines 363–369](../../../../../src/planner/search_session.cpp#L363); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ExactSearch ExactSearch::create(Catalog catalog, Query query, SearchOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one immutable exact-search binding and inert driver. |
| inputs / outputs | Validates limits and policy before model admission, then creates Impl and returns its exclusive facade. |
| invariants | Body is optimized as supplied, including nonempty contradiction-marked queries; no prefix/original substitution or SQL/physical normalization occurs. |
| ownership | By-value inputs become owned BindingData; caller mutations after successful admission cannot change the owner. |
| failure | Option/model validation and copies/allocations may throw before any session is returned. |
| cost | Full by-value model copying/validation plus ownership allocations outside advance grants; no search traversal runs here. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0063

[Lines 370–371](../../../../../src/planner/search_session.cpp#L370); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L370-L371:sha256:d2d29959396f6fe076546aecbadd04d4f007a3ce182ed2e7ddb068bb4590ab1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ExactSearch: Advance only saved work; moved-from detection precedes quantum validation and snapshots allocate no evidence. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ExactSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ExactSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0064

[Lines 372–376](../../../../../src/planner/search_session.cpp#L372); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchAdvance ExactSearch::advance(WorkQuantum quantum) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Grant one call of saved exact execution and return its scalar snapshot. |
| inputs / outputs | Moved-from owner returns moved_from first; otherwise delegates run_quantum and snapshots afterward. |
| invariants | Nonnegative zero grants on live owners are inert, even when complete. Negative grants return invalid_quantum without stored mutation. |
| ownership | Exclusive caller owns the facade; no callbacks or asynchronous work escape. |
| failure | Noexcept: run_quantum converts allocation/internal exceptions into fixed stops. Returned report has no allocating text. |
| cost | Per-call loop budget plus fixed snapshot copy; work inside container/allocator operations and active-meter sampling remains actual cost. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0065

[Lines 377–378](../../../../../src/planner/search_session.cpp#L377); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L377-L378:sha256:cee2eae6f872bc7ab44ee6754219fcdf3e471d4308685b2385c3b2dc90df2eae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ExactSearch: Report universal versus complete lower evidence explicitly; moved-from has no model-bound lower and strict may show scalar upper. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ExactSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ExactSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0066

[Lines 379–404](../../../../../src/planner/search_session.cpp#L379); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchProgress ExactSearch::progress() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a scalar search snapshot from saved state without granting work. |
| inputs / outputs | Sets universal lower from admitted body, checked scalar upper from incumbent, final lower/infeasibility only at complete, counters/structural aliases and revision. |
| invariants | Strict still exposes scalar upper. Moved-from has no binding-derived lower; cancelled retains unfinished result and any upper. Prepared final payloads do not set proof_complete until complete. |
| ownership | Owns copied scalar report; it borrows no worker collections. |
| failure | Noexcept; moved-from is explicitly represented rather than dereferenced. |
| cost | Fixed snapshot/counter copy and saved worker getter; no traversal, clock sample or evidence allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0067

[Lines 405–408](../../../../../src/planner/search_session.cpp#L405); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchBinding ExactSearch::binding() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the exact session binding independently of facade lifetime. |
| inputs / outputs | Returns a SearchBinding wrapping Impl.input. |
| invariants | No original-query authority is added when this model is an induced prefix. |
| ownership | Returned shared owner outlives movement/cancellation/destruction of the facade. |
| failure | Moved-from facade throws invalid_search_handle. |
| cost | Shared-handle copy without model copy. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0068

[Lines 409–412](../../../../../src/planner/search_session.cpp#L409); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchPolicy ExactSearch::policy() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the immutable admitted upper-exposure policy. |
| inputs / outputs | Returns options.policy. |
| invariants | Resource raising never changes strict versus best_found. |
| ownership | Returns scalar option only. |
| failure | Moved-from owner rejects with invalid_search_handle. |
| cost | Checked scalar read; failure message may allocate. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0069

[Lines 413–416](../../../../../src/planner/search_session.cpp#L413); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ContinuationLimits ExactSearch::limits() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the current accepted phase/depth ceilings. |
| inputs / outputs | Returns options.limits after presence checking. |
| invariants | A snapshot is not a mutable backdoor into the owner; changes require raise_limits. |
| ownership | Returns independent scalar configuration. |
| failure | Moved-from owner rejects. |
| cost | Small option copy without worker access. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0070

[Lines 417–418](../../../../../src/planner/search_session.cpp#L417); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L417-L418:sha256:517e8c813d00961c1cf9f9d1ab7355390e0cea1603cc7ad9b8ec0c6ad25def68
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ExactSearch: Expose best_found checked uppers across pauses/failure/cancellation; strict always withholds this handle. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ExactSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ExactSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0071

[Lines 419–422](../../../../../src/planner/search_session.cpp#L419); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ValidatedIncumbent> ExactSearch::incumbent() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the latest checked upper only when best_found policy permits it. |
| inputs / outputs | Returns null for moved/strict/no-upper; otherwise wraps incumbent regardless of unfinished, failed or cancelled stage. |
| invariants | A prior checked upper remains feasible even if later search/replay fails; it never proves a minimum. |
| ownership | Returned handle retains tree/report/input independently. |
| failure | Noexcept and no validation; current upper was already published after P02. |
| cost | Optional/shared-handle copy without new payload/control-block allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0072

[Lines 423–424](../../../../../src/planner/search_session.cpp#L423); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L423-L424:sha256:f9e98acfb8173107258cc6c047acd40ae68a8e2f13b7887d46eae09c4b2ac833
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ExactSearch: Expose optimum only after final publication and only for this exact query scope. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ExactSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ExactSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0073

[Lines 425–428](../../../../../src/planner/search_session.cpp#L425); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VerifiedOptimum> ExactSearch::optimum() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain finite optimum authority only after final public completion. |
| inputs / outputs | Requires non-null owner, complete stage and prepared optimum. |
| invariants | Private result allocation before publish_final is insufficient; authority stays scoped to this exact admitted model. |
| ownership | Returned optional shares final evidence beyond facade lifetime. |
| failure | Noexcept null result for unfinished/failed/cancelled/moved or infeasible outcomes. |
| cost | Shared-handle wrap without replay or tree copy. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0074

[Lines 429–430](../../../../../src/planner/search_session.cpp#L429); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L429-L430:sha256:9a3f23ef3b26a4561ddbb3825c44443029ee98380631acae8b0edda31b1ed474
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ExactSearch: Expose no-tree authority only at complete publication, never from a resource stop or absent upper. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ExactSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ExactSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0075

[Lines 431–434](../../../../../src/planner/search_session.cpp#L431); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<VerifiedInfeasible> ExactSearch::infeasibility() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain completed whole-binding no-tree authority. |
| inputs / outputs | Requires complete stage and an InfeasibleData owner. |
| invariants | Resource stops, prefix results outside this binding, absent upper and private prepared result are insufficient. |
| ownership | Optional shared handle retains model/certificate. |
| failure | Noexcept absence for every nonmatching state. |
| cost | Handle copy without claim-table traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0076

[Lines 435–436](../../../../../src/planner/search_session.cpp#L435); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L435-L436:sha256:a5ec5db5b117d6a0798ab3702742fb6efaa66c87d2ef254bf64e3e2e78a6d9e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ExactSearch: Apply only monotone ceilings above consumed values; accepted equality still advances revision and never resets work. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ExactSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ExactSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0077

[Lines 437–448](../../../../../src/planner/search_session.cpp#L437); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LimitChange ExactSearch::raise_limits(ContinuationLimits value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically extend exact-session resource ceilings without replacing execution. |
| inputs / outputs | Rejects terminal/moved, invalid times, decreases, values below consumed work/time and exhausted revision; otherwise updates options/ledgers and increments revision. |
| invariants | Finite-to-unbounded is allowed, unbounded-to-finite is not. Equal accepted requests increment revision. No counters, last_stop, binding, policy or pending cursor reset. |
| ownership | Copies scalar values into existing driver/ledgers. |
| failure | Noexcept rejection leaves all accepted state unchanged. |
| cost | Fixed scalar comparisons/copies with no search work, allocation or clock sample. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0078

[Lines 449–450](../../../../../src/planner/search_session.cpp#L449); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L449-L450:sha256:cf253fce1708c0abfec49a30a15993f6aa62b231fe8f162c532b5a53cffa1e67
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ExactSearch: Cancel only nonterminal work; preserve incumbent/input/counters, and leave already terminal owners unchanged. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ExactSearch; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ExactSearch come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0079

[Lines 451–460](../../../../../src/planner/search_session.cpp#L451); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void ExactSearch::cancel() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cancel nonterminal exact work while preserving already published uppers and diagnostics. |
| inputs / outputs | Snapshots producer statistics, marks cancelled, releases workers/drafts/proofs/prepared results and zeroes current depths. |
| invariants | Moved-from and every terminal owner, including failed or complete, are unchanged. Incumbent/input/options/counters/peaks remain; cancelled result stays unfinished with universal lower. |
| ownership | Releases unfinished ownership; externally retained artifacts and retained incumbent keep needed payloads alive. |
| failure | Noexcept; cancellation establishes no infeasibility. A failed terminal owner releases its scratch only on destruction/replacement. |
| cost | Can traverse frames, arenas, memo/proof/tree payloads and container storage; explicit cancellation is outside active-time/work grants. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0080

[Lines 461–464](../../../../../src/planner/search_session.cpp#L461); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CertificateReplay::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own standalone claim replay and private typed-artifact preparation. |
| inputs / outputs | Retains admitted model/proof, one ledger, checker, checked proof, outcome owners, prepared and published artifact. |
| invariants | Checker success alone is not public checked(); all typed/result wrappers are prepared before publish stage. |
| ownership | Owns checker exclusively and evidence by immutable shared ownership; caller claim is not borrowed. |
| failure | Allocation retries preserve stage; invalid external claim is terminal invalid_certificate; failed terminal scratch remains until destruction/replacement. |
| cost | Checker/claim/cache payloads may be exponential; outer driver adds fixed fields/control blocks. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0081

[Lines 465–465](../../../../../src/planner/search_session.cpp#L465); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Stage { shell, replay, upper, result, artifact, publish, complete, failed, cancelled };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode standalone replay and final-owner publication steps. |
| inputs / outputs | Separates checker shell/actions from upper, outcome, artifact preparation and publish. |
| invariants | Prepared checked data remains private; terminal stages never restart replay. |
| ownership | Stored discriminator owns no evidence by itself. |
| failure | Failed allocations keep the same preparation stage; rejected proof selects failed. |
| cost | Fixed stage tag; many checker units can occur in replay. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0082

[Lines 466–481](../../../../../src/planner/search_session.cpp#L466); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L466-L481:sha256:6d9995ce281a920d747f13bec3a5d40f20e5abb818b7cfe67625b3933ec6cbd9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain input, proof, options, resource, stage, last_stop, failure, revision, retained_checked_claims, replay, checked_proof, upper, optimum, infeasibility, prepared, published in CertificateReplay::Impl across its lifetime. |
| inputs / outputs | These are stored fields for CertificateReplay::Impl, not callable parameters or results; constructors and later methods set or consume them. |
| invariants | The fields preserve the named machine or owner state between calls; counters, cursors, and stored claims remain data until adjacent methods update or validate them. |
| ownership | shared_ptr members retain their pointees through shared ownership; this span does not deep-copy them; unique_ptr members exclusively own their implementation or child-machine objects. |
| failure | The declarations add no exception path by themselves. Constructing owner/container members or growing them later can fail through the surrounding object-creation or update path. |
| cost | Adds fixed per-instance storage for the listed values and owner/container handles; shared_ptr members retain shared payloads without a deep copy at this declaration; child implementation allocation occurs in its factory or constructor. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0083

[Lines 482–483](../../../../../src/planner/search_session.cpp#L482); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(std::shared_ptr<const cd::BindingData> value, std::shared_ptr<const HeightCertificate> claim, ReplayOptions opts)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize inert standalone replay and its cumulative ledger. |
| inputs / outputs | Moves immutable model/claim owners, copies options and initializes the resource ledger. |
| invariants | No structural checks or algorithm dispatch happen in construction. |
| ownership | Retains complete admission snapshots independent of caller input lifetime. |
| failure | Outer implementation allocation can fail before facade publication. |
| cost | Fixed owner/ledger setup; complete model/claim copying occurred during admission. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0084

[Lines 484–484](../../../../../src/planner/search_session.cpp#L484); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool terminal() const noexcept { return stage == Stage::complete || stage == Stage::failed || stage == Stage::cancelled; }
  StopReason terminal_reason() const noexcept { return
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify standalone replay states that no grant can advance. |
| inputs / outputs | Complete, failed and cancelled are terminal. |
| invariants | Complete may mean valid artifact; failed means no authority and may still retain substantial scratch. |
| ownership | Reads only saved stage. |
| failure | Noexcept Boolean observation. |
| cost | Fixed enum comparisons. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0085

[Lines 485–485](../../../../../src/planner/search_session.cpp#L485); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StopReason terminal_reason() const noexcept { return stage == Stage::complete ? StopReason::complete : stage == Stage::cancelled ? StopReason::cancelled : failure; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the stable stop corresponding to terminal standalone replay. |
| inputs / outputs | Returns complete, cancelled or saved failure. |
| invariants | Does not create an artifact, reset ledgers or overwrite last_stop. |
| ownership | Returns scalar state. |
| failure | Noexcept; called after terminal() by run_quantum. |
| cost | Fixed stage dispatch. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0086

[Lines 486–486](../../../../../src/planner/search_session.cpp#L486); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
cd::ResourceLedger& ledger() noexcept { return resource; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the sole standalone replay resource ledger. |
| inputs / outputs | Returns the retained resource object for charging/checking. |
| invariants | Upper validation, lower jobs and final typed wrapper preparation share this ledger. |
| ownership | Reference lives only with Impl; ActiveMeter borrows it within advance. |
| failure | Noexcept reference getter. |
| cost | Reference return without ledger copy. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0087

[Lines 487–488](../../../../../src/planner/search_session.cpp#L487); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L487-L488:sha256:3425af91c9f2f41be078a1a035428379b8e04a089834ab09be8b58d8ca97469d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for current_depth: Report active checker depth; post-check owner preparation is depth zero while evidence remains retained. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies current_depth; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for current_depth come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0088

[Lines 489–489](../../../../../src/planner/search_session.cpp#L489); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t current_depth() const noexcept { return stage == Stage::replay && replay ? replay->current_depth() : 0; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe active independent checker nesting for standalone accounting. |
| inputs / outputs | Delegates only during replay; shell/result/artifact/publication stages report zero. |
| invariants | Retained checker memory is not erased when its active logical depth becomes zero. |
| ownership | Returns a scalar while Impl keeps all owners. |
| failure | Noexcept with stage/worker consistency supplied by private driver. |
| cost | One stage test and saved-depth getter. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0089

[Lines 490–490](../../../../../src/planner/search_session.cpp#L490); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void fail(StopReason reason) noexcept { failure = reason; stage = Stage::failed; }
  cd::UnitResult unit() {
    switch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make malformed external evidence or internal failure terminal. |
| inputs / outputs | Stores reason and changes stage to failed. |
| invariants | No published CheckedCertificate exists on this path. A failed owner cannot be resumed or cleared by cancel. |
| ownership | Retains unfinished checker/claim scratch until destruction/replacement. |
| failure | Noexcept scalar mutation; all exception-to-stop handling is in run_quantum. |
| cost | Fixed writes without eager scratch destruction. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0090

[Lines 491–539](../../../../../src/planner/search_session.cpp#L491); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
cd::UnitResult unit() {
    switch (stage) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one standalone checker action or owner-publication stage. |
| inputs / outputs | Creates the checker, drives independent proof, prepares finite/infinite outcome and artifact, then publishes complete. |
| invariants | Every potentially allocating owner is local before stage advance; only publish makes checked() nonempty. |
| ownership | Owns checker and all prepared/published evidence handles. |
| failure | External proof_invalid maps invalid_certificate; missing expected checked payload maps internal_failure; allocations propagate for retry. |
| cost | One metered unit; actual checker/container/allocator work remains variable. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

```text
case Stage::shell: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare independent claim-checking worker. |
| inputs / outputs | Construct ReplayMachine(input,proof) locally and then commit replay stage. |
| invariants | No algorithm/upper/lower work runs in the inert shell constructor. |
| ownership | Shares immutable admission snapshots through the checker. |
| failure | Allocation leaves shell pending. |
| cost | Implementation/default-container allocation without claim traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::replay: {
        const auto result = replay->step(cd::UnitContext{options.logical_depth});
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive a saved independent certificate-check action. |
| inputs / outputs | proof_invalid fails with invalid_certificate; proof_valid retains non-null checked proof and selects upper. |
| invariants | Claim failure is distinct from a resource stop. Checker success still precedes public artifact publication. |
| ownership | Shared checked proof retains exact model and optional upper. |
| failure | Missing expected authority is internal_failure; worker allocating/depth actions retain state. |
| cost | One checker transition, charged once by the outer ledger. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::upper:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare finite checked-upper owner when present. |
| inputs / outputs | Wrap CheckedProof.upper in IncumbentData, otherwise proceed without upper. |
| invariants | Infinite-root evidence has no upper wrapper. |
| ownership | Owns a private shared upper handle. |
| failure | Control-block failure leaves upper stage pending. |
| cost | Optional owner allocation and fixed shared references. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::result:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the typed optimum or empty-family result. |
| inputs / outputs | Finite upper produces OptimumData; absent upper produces InfeasibleData, then artifact stage. |
| invariants | Result is scoped to admitted input; its owner remains private. |
| ownership | Shares complete certificate/input and checked upper when finite. |
| failure | Allocation preserves this stage and all checked evidence. |
| cost | One outcome owner allocation without copying proof/table payload. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::artifact: {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the complete replay artifact control block. |
| inputs / outputs | Creates CheckedCertificateData{checked_proof,optimum,infeasibility} and saves prepared before publish. |
| invariants | No public checked handle exists until the next publish commit. |
| ownership | Private prepared owner shares the full typed outcome. |
| failure | Allocation leaves artifact stage pending. |
| cost | One control-block allocation and fixed handle retention. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::publish: published = std::move(prepared); stage = Stage::complete; break;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit fully prepared independent replay authority. |
| inputs / outputs | Moves prepared into published and marks complete. |
| invariants | No throwing preparation follows this publication; checked() can now expose the artifact. |
| ownership | Shared artifact ownership survives facade destruction when retained externally. |
| failure | Nonthrowing handle/scalar move under private stage invariants. |
| cost | Fixed owner transfer with no new allocation or claim walk. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

```text
case Stage::complete: case Stage::failed: case Stage::cancelled: break;
    }
    return {};
  }
};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep terminal standalone unit dispatch inert. |
| inputs / outputs | No unit action for complete, failed or cancelled. |
| invariants | run_quantum checks terminal state before the active loop. |
| ownership | Retains owners exactly as they stand. |
| failure | No new proof or failure is emitted here. |
| cost | Fixed no-op dispatch; ownership release is separate. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0091

[Lines 540–540](../../../../../src/planner/search_session.cpp#L540); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L540-L540:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0092

[Lines 541–541](../../../../../src/planner/search_session.cpp#L541); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CertificateReplay::CertificateReplay(std::unique_ptr<Impl> p) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the fully admitted standalone replay implementation. |
| inputs / outputs | Moves unique_ptr into facade data_. |
| invariants | Only create invokes it; no proof checking occurs here. |
| ownership | Takes exclusive ownership without moving Impl payload. |
| failure | Noexcept pointer adoption. |
| cost | One pointer move without proof traversal. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md) |

## B0093

[Lines 542–550](../../../../../src/planner/search_session.cpp#L542); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CertificateReplay::~CertificateReplay() = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release standalone replay and any unpublished claim/worker scratch. |
| inputs / outputs | Destroys Impl and its retained evidence fields. |
| invariants | Externally retained checked outcomes keep their immutable payload alive; destruction proves no claim. |
| ownership | Releases exclusive checker and shared input/proof/result owners. |
| failure | Nonthrowing under contained model/worker destructor contracts. |
| cost | May traverse large claim maps/caches and last-owned payloads outside advance accounting. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
CertificateReplay::CertificateReplay(CertificateReplay&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer saved independent replay without relocating its driver. |
| inputs / outputs | Moves unique_ptr; a distinct source becomes empty. |
| invariants | Internal job/cache pointers retain their addresses; moved-from progress is explicitly marked. |
| ownership | Transfers exclusive driver/evidence ownership. |
| failure | Noexcept; moved-from content getters reject. |
| cost | One pointer transfer with no claim copying. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

```text
CertificateReplay& CertificateReplay::operator=(CertificateReplay&&) noexcept = default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace replay ownership and release any prior destination driver. |
| inputs / outputs | Default unique_ptr move assignment transfers source after destroying old destination state. |
| invariants | No certificate/binding merging occurs; existing external artifacts remain valid. |
| ownership | May drop final owners of old checker/claim/model payloads synchronously. |
| failure | Noexcept under owned destructors; self-move follows unique_ptr semantics. |
| cost | Pointer transfer plus potentially size-dependent prior-driver teardown. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0094

[Lines 551–556](../../../../../src/planner/search_session.cpp#L551); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CertificateReplay CertificateReplay::create(Catalog catalog, Query query, HeightCertificate proof, ReplayOptions options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit immutable model and untrusted typed claim before any replay grant. |
| inputs / outputs | Validates option time, admits model, moves/copies the complete certificate into shared const storage and creates inert Impl. |
| invariants | Algorithm, upper and lower checks are deferred; typed input is a claim about supplied model, while serialized exact binding is checked by IO separately. |
| ownership | Owns deep model/claim payload through shared snapshots; no caller references escape. |
| failure | By-value copies, option/model validation and allocations can throw before facade return. |
| cost | Full admission/copy costs are outside grants; construction runs no replay traversal. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md) |

## B0095

[Lines 557–558](../../../../../src/planner/search_session.cpp#L557); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L557-L558:sha256:41be4252bd26a42ca56516cfa7fda3c6c4ed4cf337d950b4f471e692e7245781
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CertificateReplay: Advance retained replay only; moved-from detection precedes quantum handling. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CertificateReplay; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CertificateReplay come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0096

[Lines 559–563](../../../../../src/planner/search_session.cpp#L559); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayAdvance CertificateReplay::advance(WorkQuantum quantum) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Grant saved standalone replay and return its scalar state. |
| inputs / outputs | Moved-from returns moved_from first; live owner delegates run_quantum then progress. |
| invariants | Inert/invalid quanta preserve stored fields; final valid publication can still await owner preparation after checker success. |
| ownership | Requires exclusive caller; no background work or callback. |
| failure | Noexcept fixed stops convert worker allocation/internal exceptions while retaining resumable resource failures. |
| cost | Controlled loop budget plus fixed report copy, with actual container/clock/lifetime costs separate. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md), [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md) |

## B0097

[Lines 564–565](../../../../../src/planner/search_session.cpp#L564); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L564-L565:sha256:0566051ee094ae016f6e79bc9f5598aa2f17138e562b1cc60f0d2c654bc2a829
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CertificateReplay: Keep checked-prefix progress separate from final valid artifact; failed may be complete but invalid. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CertificateReplay; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CertificateReplay come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0098

[Lines 566–579](../../../../../src/planner/search_session.cpp#L566); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayProgress CertificateReplay::progress() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot checker and final-owner preparation without advancing it. |
| inputs / outputs | Copies ledger/revision/checked prefix; maps complete to complete+valid, failed to complete but invalid, cancelled to cancelled, and wrapper preparation to match_root. |
| invariants | checked_claims can be complete while public valid remains false; failure complete is terminal rejection, not proof authority. |
| ownership | Owns numeric snapshot only and borrows no checker scratch. |
| failure | Noexcept moved-from snapshot is explicit; cancellation uses retained prefix count after checker release. |
| cost | Saved scalar/counter reads without proof traversal or clock sampling. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0099

[Lines 580–583](../../../../../src/planner/search_session.cpp#L580); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SearchBinding CertificateReplay::binding() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the standalone replay model independently of the facade. |
| inputs / outputs | Wraps Impl.input in an immutable SearchBinding. |
| invariants | It is exactly the supplied typed model and confers no authority on a different source/prefix/original binding. |
| ownership | Returned shared handle owns model lifetime. |
| failure | Moved-from owner throws invalid_search_handle. |
| cost | Shared-handle copy without model traversal. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/residual_candidates.md §Exactness and owning artifacts](../../../../residual_candidates.md) |

## B0100

[Lines 584–585](../../../../../src/planner/search_session.cpp#L584); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L584-L585:sha256:5b91a38603ebe969e87d4f8324f5041b1f10a28d9cfbcb31313640a566d7a615
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CertificateReplay: Expose only the fully published artifact, not a successful checker prefix or private prepared result. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CertificateReplay; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CertificateReplay come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0101

[Lines 586–589](../../../../../src/planner/search_session.cpp#L586); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CheckedCertificate> CertificateReplay::checked() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain fully published independent replay authority. |
| inputs / outputs | Returns null unless Impl.published exists, then wraps it. |
| invariants | Internal CheckedProof or prepared outcome before publish is insufficient; invalid/cancelled/moved cases provide no checked artifact. |
| ownership | Returned optional shares all immutable checked evidence beyond facade lifetime. |
| failure | Noexcept handle observation; no replay occurs here. |
| cost | Optional/shared-owner copy without payload/control-block allocation. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md) |

## B0102

[Lines 590–593](../../../../../src/planner/search_session.cpp#L590); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ReplayOptions CertificateReplay::limits() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current accepted standalone replay ceilings. |
| inputs / outputs | Returns Impl.options after presence check. |
| invariants | Edits to returned value cannot change an admitted proof or active ledger. |
| ownership | Owns copied scalar options. |
| failure | Moved-from rejects invalid_search_handle. |
| cost | Small option copy without worker action. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0103

[Lines 594–595](../../../../../src/planner/search_session.cpp#L594); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L594-L595:sha256:a952ecbcca8e3c75cfef526d17fa086de740bb45fa9aafc0d52affccf56af023
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CertificateReplay: Raise only monotone ceilings above consumption without replacing the claim or resetting counters. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CertificateReplay; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CertificateReplay come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0104

[Lines 596–605](../../../../../src/planner/search_session.cpp#L596); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LimitChange CertificateReplay::raise_limits(ReplayOptions value) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Atomically extend retained replay resources. |
| inputs / outputs | Rejects terminal/moved, negative time, nonmonotone values, below-consumed work/time and exhausted revision; otherwise updates options/ledger and revision. |
| invariants | Equal values can be applied and increment revision; finite-to-unbounded is allowed. Claim, model, counters, pending stage and last_stop remain intact. |
| ownership | Copies scalar configuration into existing owners. |
| failure | Noexcept rejected requests perform no mutation. |
| cost | Fixed comparisons/assignments without allocation, clocks or replay. |
| Design | [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0105

[Lines 606–607](../../../../../src/planner/search_session.cpp#L606); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L606-L607:sha256:05a8325a5184c3ac19add4b5e70e177b1cc8d53f4a161b793701be68a37df7cb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CertificateReplay: Cancel nonterminal replay and retain diagnostics; already terminal owners remain unchanged. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CertificateReplay; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CertificateReplay come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0106

[Lines 608–615](../../../../../src/planner/search_session.cpp#L608); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void CertificateReplay::cancel() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release nonterminal independent replay while retaining scalar history. |
| inputs / outputs | Saves checked_claims, marks cancelled, resets worker/proof/private outcome/prepared owners and zeroes current depth. |
| invariants | All terminal owners, including failed/complete, are unchanged; a complete published artifact survives. Cancellation establishes no claim validity. |
| ownership | Retains admitted input/options/ledger/revision and releases unpublished evidence; external checked artifacts have independent ownership. |
| failure | Noexcept; terminal failed scratch is released only by destruction/replacement. |
| cost | Can destroy large worker/cache/proof payloads; explicit cancellation is outside active-time/work grants. |
| Design | [docs/planner_continuations.md §Lifetime and output](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md) |

## B0107

[Lines 616–618](../../../../../src/planner/search_session.cpp#L616); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L616-L618:sha256:6d0d205b44c370afbd4d95a818c9105ead5ae9bfd57edc12764a867c81506e33
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for minimum_tree: Keep the owner alive while borrowing its final proof for allocating strict export; resource stops expose no partial certificate. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies minimum_tree; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for minimum_tree come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0108

[Lines 619–644](../../../../../src/planner/search_session.cpp#L619); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OracleResult minimum_tree(const Catalog& catalog, const Query& query, const SearchLimits& limits) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run strict exact ownership to completion or a cumulative stop, then construct a legacy aggregate. |
| inputs / outputs | Admits model with mapped limits, repeatedly grants 4096 work units, extracts only completed optimum/infeasible proof and copies its payload into OracleResult. |
| invariants | Resource stop returns no minimum/tree/partial proof. A local borrowed certificate pointer remains backed by the live owner after temporary extraction handles expire. |
| ownership | Owns the search through return conversion; returned aggregate owns copied tree/claims/strings. |
| failure | Internal proof failure throws invalid_search_invariant; option/admission/result allocation errors may throw. Ordinary resource stops return resource_limit. |
| cost | Potentially exponential producer/replay plus full admission and allocating legacy export; literal_scope_limit has no production effect. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0109

[Lines 645–646](../../../../../src/planner/search_session.cpp#L645); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L645-L646:sha256:f6066cd154ec49aac55037ff5387c792fce49e9e1f57240de7cb8b56e8069e5e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for verify_height_certificate: Summarize independent replay without exposing partial authority; finite and no-tree success need distinct diagnostic wording. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies verify_height_certificate; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for verify_height_certificate come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0110

[Lines 647–666](../../../../../src/planner/search_session.cpp#L647); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CertificateReport verify_height_certificate(const Catalog& catalog, const Query& query,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run independent owned replay of a caller claim and summarize its outcome. |
| inputs / outputs | Maps limits, admits model/claim, grants 4096 units until stop, and reports checked presence, attempted work, resource classification and message. |
| invariants | Only final checked artifact makes valid true. Invalid proof differs from cumulative/depth/allocation/counter resource outcomes; diagnostic text does not substitute for the retained finite or infinite checked authority. Success wording is selected from the admitted checked certificate after replay: finite claims mention the upper tree; infinite-root claims report the independently verified empty admissible family. |
| ownership | Owner retains admitted snapshots; returned report owns message/scalars but no artifact. |
| failure | Limit/admission/report allocation may throw; replay errors/resources become summary fields under the driver contract. |
| cost | Independent replay can be exponential; final string/report conversion is allocating outside grants. |
| Design | [docs/planner_continuations.md §Authority and policies](../../../../planner_continuations.md), [docs/planner_continuations.md §Resource accounting](../../../../planner_continuations.md), [docs/planner_proofs.md §Independent lower-bound evidence and strict limits](../../../../planner_proofs.md) |

## B0111

[Lines 667–667](../../../../../src/planner/search_session.cpp#L667); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L667-L667:sha256:acb95521e5c8cc117a4f60f87ae076d39f48ab1ff02f31d3b8a4ada933fd3da0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/search_session.cpp](../../../../../src/planner/search_session.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
