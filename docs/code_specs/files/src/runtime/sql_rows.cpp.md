# `src/runtime/sql_rows.cpp` — block usage map

[Source](../../../../../src/runtime/sql_rows.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain Boolean CROWN record/survivor/projected-support state and enumerate current answers from factorized visible relations.

Snapshot SHA-256: `9e16a0ef2f575807b5f1466c312b281b996406fd54629d747bf93eeeed6cacf6`. 751 lines partitioned into 104 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../src/runtime/sql_rows.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 15–16](../../../../../src/runtime/sql_rows.cpp#L15) | Callable definition: template&lt;class T&gt; auto allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose) | calls ; returns resource::MemoryAllocator&lt;T&gt;(account, purpose) · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../src/runtime/sql_rows.cpp#L17) | Callable definition: \[\[noreturn\]\] void fail(const char* code, const char* message) | calls Error · [reviewed contract](#b0003) |
| [B0004 · 18–20](../../../../../src/runtime/sql_rows.cpp#L18) | Explanatory comments or spacing. | source comment (unverified): // Immutable nullable keys support borrowed probes. NULL sorts first; all · [reviewed contract](#b0004) |
| [B0005 · 21–29](../../../../../src/runtime/sql_rows.cpp#L21) | Type/record definition: struct Less | returns std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()); compare(a.view(), b.view()); source comment (unverified): // Immutable nullable keys support borrowed probes. NULL sorts first; all · [reviewed contract](#b0005) |
| [B0006 · 30–34](../../../../../src/runtime/sql_rows.cpp#L30) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // A detached node uses the receiving map's allocator. Insertion after native · [reviewed contract](#b0006) |
| [B0007 · 35–38](../../../../../src/runtime/sql_rows.cpp#L35) | Callable definition: Counts::node_type node_for(Counts& target, Tuple key, std::uint64_t value) | calls prepared, key_comp, get_allocator, extract; returns prepared.extract(prepared.emplace(std::move(key), value).first); growth emplace; source comment (unverified): // A detached node uses the receiving map's allocator. Insertion after native · [reviewed contract](#b0007) |
| [B0008 · 39–41](../../../../../src/runtime/sql_rows.cpp#L39) | Callable definition: std::uint64_t count(const Counts& values, std::span&lt;const Cell&gt; key) | calls find, end; returns found == values.end() ? 0 : found-&gt;second · [reviewed contract](#b0008) |
| [B0009 · 42–47](../../../../../src/runtime/sql_rows.cpp#L42) | Callable definition: std::uint64_t replace_count(std::uint64_t current, std::uint64_t before, std::uint64_t after) | calls fail; returns base + after · [reviewed contract](#b0009) |
| [B0010 · 48–52](../../../../../src/runtime/sql_rows.cpp#L48) | Callable definition: storage::IndexWork consumed(storage::IndexWork limit, const storage::IndexWork& remaining) noexcept | calls ; returns {limit.structural_steps - remaining.structural_steps, · [reviewed contract](#b0010) |
| [B0011 · 53–57](../../../../../src/runtime/sql_rows.cpp#L53) | Callable definition: PhysicalPlan lower(const frontend::SqlRowsProgram& program, const FreeConnexTree& tree, const PhysicalOptions& options) | calls export_core, planner::lower_tree; returns planner::lower_tree(core.catalog, core.query, tree, options) · [reviewed contract](#b0011) |
| [B0012 · 58–60](../../../../../src/runtime/sql_rows.cpp#L58) | declares types or opens a type body. | source comment (unverified): // namespace · [reviewed contract](#b0012) |
| [B0013 · 61–66](../../../../../src/runtime/sql_rows.cpp#L61) | Type/record definition: struct Edit |  · [reviewed contract](#b0013) |
| [B0014 · 67–77](../../../../../src/runtime/sql_rows.cpp#L67) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0014) |
| [B0015 · 78–89](../../../../../src/runtime/sql_rows.cpp#L78) | Callable definition: Data(const resource::MemoryAccount& owner, frontend::SqlRowsProgram source, const FreeConnexTree& tree, const PhysicalOptions& ph… | calls account, program, frontend::SqlRowsProgram::freeze, options · [reviewed contract](#b0015) |
| [B0016 · 90–100](../../../../../src/runtime/sql_rows.cpp#L90) | Callable definition: Data(const resource::MemoryAccount& owner,frontend::SqlRowsProgram source,WeightedRuntime prepared,Options requested) : account(o… | calls account, program, frontend::SqlRowsProgram::freeze, options · [reviewed contract](#b0016) |
| [B0017 · 101–124](../../../../../src/runtime/sql_rows.cpp#L101) | Callable definition: void initialize() | calls statistics, reserve, sources, size; growth emplace_back, reserve, resize; 5 loop sites; source comment (unverified): // Contradiction has no executable nodes. Every other exported atom must · [reviewed contract](#b0017) |
| [B0018 · 125–125](../../../../../src/runtime/sql_rows.cpp#L125) | Explanatory comments or spacing. |  |
| [B0019 · 126–129](../../../../../src/runtime/sql_rows.cpp#L126) | Callable definition: const frontend::SqlRowsSource& source(TableId id) const | calls sources, size, fail; returns program.sources()\[id.value\] · [reviewed contract](#b0019) |
| [B0020 · 130–139](../../../../../src/runtime/sql_rows.cpp#L130) | Callable definition: void validate(const frontend::SqlRowsSource& table, std::span&lt;const Cell&gt; input, storage::IndexWorkAllowance* work) const | calls size, fail, frontend::rows_detail::step, frontend::sql_detail::admit_value; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 140–141](../../../../../src/runtime/sql_rows.cpp#L140) | Explanatory comments or spacing. | source comment (unverified): // Both UNIQUE (NULLS DISTINCT) and MATCH SIMPLE foreign keys omit any key · [reviewed contract](#b0021) |
| [B0022 · 142–152](../../../../../src/runtime/sql_rows.cpp#L142) | Callable definition: std::optional&lt;std::span&lt;const Cell&gt;&gt; project_key(const frontend::SqlRowsConstraint& constraint, std::span&lt;const Cell&gt; input, Item… | calls std::max, size, frontend::rows_detail::step, frontend::sql_detail::admit_value; returns std::nullopt; std::span&lt;const Cell&gt;(target.data(), constraint.columns.size()); 1 loop sites; source comment (unverified): // Both UNIQUE (NULLS DISTINCT) and MATCH SIMPLE foreign keys omit any key · [reviewed contract](#b0022) |
| [B0023 · 153–158](../../../../../src/runtime/sql_rows.cpp#L153) | Callable definition: bool same_key(std::span&lt;const Cell&gt; left, std::span&lt;const Cell&gt; right, storage::IndexWorkAllowance& work) const | calls size, frontend::rows_detail::same; returns false; false; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 159–161](../../../../../src/runtime/sql_rows.cpp#L159) | Explanatory comments or spacing. | source comment (unverified): // Probe the proposed single-row state without publishing it. This handles · [reviewed contract](#b0024) |
| [B0025 · 162–175](../../../../../src/runtime/sql_rows.cpp#L162) | Callable definition: std::uint64_t proposed_count(std::size_t index, std::span&lt;const Cell&gt; probe, const Update& update, storage::IndexWorkAllowance& w… | calls frontend::rows_detail::step, count, constraints, project_key; returns result; source comment (unverified): // Probe the proposed single-row state without publishing it. This handles · [reviewed contract](#b0025) |
| [B0026 · 176–201](../../../../../src/runtime/sql_rows.cpp#L176) | Callable definition: void prepare_keys(const frontend::SqlRowsSource& table, const Update& update, storage::IndexWorkAllowance& work) | calls frontend::rows_detail::step, constraints, project_key, find; growth copy_of, push_back; 2 loop sites · [reviewed contract](#b0026) |
| [B0027 · 202–204](../../../../../src/runtime/sql_rows.cpp#L202) | Explanatory comments or spacing. | source comment (unverified): // Only touched scratch prefixes are cleared. Detached edits own private · [reviewed contract](#b0027) |
| [B0028 · 205–213](../../../../../src/runtime/sql_rows.cpp#L205) | Type/record definition: struct Scratch | source comment (unverified): // Only touched scratch prefixes are cleared. Detached edits own private · [reviewed contract](#b0028) |
| [B0029 · 214–255](../../../../../src/runtime/sql_rows.cpp#L214) | Callable definition: Epoch apply(const Update& update) | calls begin_epoch, work, frontend::rows_detail::step, source; returns {update.before != update.after, spent, std::move(result)}; growth copy_of, insert; 2 loop sites; source comment (unverified): // All throwing work is finished. Node handles share their destination · [reviewed contract](#b0029) |
| [B0030 · 256–262](../../../../../src/runtime/sql_rows.cpp#L256) | declares types or opens a type body. | source comment (unverified): // All SQL source/key state remains committed while one native token is private. · [reviewed contract](#b0030) |
| [B0031 · 263–263](../../../../../src/runtime/sql_rows.cpp#L263) | Type/record definition: struct Probe |  · [reviewed contract](#b0031) |
| [B0032 · 264–264](../../../../../src/runtime/sql_rows.cpp#L264) | Type/record definition: struct Key |  · [reviewed contract](#b0032) |
| [B0033 · 265–276](../../../../../src/runtime/sql_rows.cpp#L265) | Type/record definition: struct Order | returns a.domain!=b.domain?a.domain&lt;b.domain:Less::compare(a.row.view(),b.row.view()); a.domain!=b.domain?a… · [reviewed contract](#b0033) |
| [B0034 · 277–282](../../../../../src/runtime/sql_rows.cpp#L277) | Type/record definition: struct Proposal |  · [reviewed contract](#b0034) |
| [B0035 · 283–292](../../../../../src/runtime/sql_rows.cpp#L283) | declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // Fixed opt-in metadata; no output-row mirror. · [reviewed contract](#b0035) |
| [B0036 · 293–297](../../../../../src/runtime/sql_rows.cpp#L293) | Callable definition: Data(std::shared_ptr&lt;SqlRowsRuntime::Data&gt; sql,const NetBatch& batch,WeightedRuntime::PendingEpoch native) :owner(std::move(sql))… | calls owner, std::move, pending, work · [reviewed contract](#b0036) |
| [B0037 · 298–302](../../../../../src/runtime/sql_rows.cpp#L298) | Callable definition: Data(std::shared_ptr&lt;SqlRowsRuntime::Data&gt; sql,const NetBatch& batch,WeightedRuntime::PendingEpoch native, storage::IndexWorkAllo… | calls owner, std::move, pending, work · [reviewed contract](#b0037) |
| [B0038 · 303–331](../../../../../src/runtime/sql_rows.cpp#L303) | Callable definition: void prepare(const NetBatch& batch) | calls frontend::rows_detail::step, source, validate, find; 2 loop sites; source comment (unverified): // A no-op validates its chain but needs no new key/payload. · [reviewed contract](#b0038) |
| [B0039 · 332–342](../../../../../src/runtime/sql_rows.cpp#L332) | Callable definition: std::optional&lt;std::size_t&gt; output_size() const | calls wrapper, preview, present, semantics; returns std::nullopt; epoch.before.present()!=epoch.after.present()?2:0 · [reviewed contract](#b0039) |
| [B0040 · 343–371](../../../../../src/runtime/sql_rows.cpp#L343) | Callable definition: OutputChangeView output_change(std::size_t index,std::span&lt;Cell&gt; scratch) | calls output_size, fail, size, outputs; returns {scratch,{index==0,{1}}}; {scratch,change.change}; 1 loop sites; source comment (unverified): // One selected row unit and one field unit per call, across all codec passes. · [reviewed contract](#b0040) |
| [B0041 · 372–372](../../../../../src/runtime/sql_rows.cpp#L372) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0041) |
| [B0042 · 373–373](../../../../../src/runtime/sql_rows.cpp#L373) | Callable definition: bool active() const noexcept | calls bool; returns bool(owner)&&pending.active() · [reviewed contract](#b0042) |
| [B0043 · 374–399](../../../../../src/runtime/sql_rows.cpp#L374) | Callable definition: Proposal& touch(Touched& touched,std::size_t id,Counts& target,std::span&lt;const Cell&gt; row, std::optional&lt;std::uint64_t&gt; expected=s… | calls frontend::rows_detail::step, find, end, fail; returns queued-&gt;second; touched.emplace(Key{id,std::move(owned)},Proposal{&target,position,current,current,…; growth copy_of, emplace; 1 loop sites; source comment (unverified): // Actual shared immutable Tuple copy. · [reviewed contract](#b0043) |
| [B0044 · 400–416](../../../../../src/runtime/sql_rows.cpp#L400) | Callable definition: void update_keys(bool decreasing) | calls frontend::rows_detail::step, source, constraints, std::uint64_t; 2 loop sites; source comment (unverified): // NULLS DISTINCT / MATCH SIMPLE; empty key is present. · [reviewed contract](#b0044) |
| [B0045 · 417–421](../../../../../src/runtime/sql_rows.cpp#L417) | Callable definition: std::uint64_t final_count(std::size_t id,std::span&lt;const Cell&gt; row) | calls frontend::rows_detail::step, find, end, count; returns found-&gt;second.after; count(owner-&gt;keys\[id\],row) · [reviewed contract](#b0045) |
| [B0046 · 422–437](../../../../../src/runtime/sql_rows.cpp#L422) | Callable definition: void validate_keys() | calls frontend::rows_detail::step, constraints, final_count, view; 2 loop sites · [reviewed contract](#b0046) |
| [B0047 · 438–444](../../../../../src/runtime/sql_rows.cpp#L438) | Callable definition: void prepare_nodes(Touched& touched) | calls frontend::rows_detail::step, end, node_for; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 445–461](../../../../../src/runtime/sql_rows.cpp#L445) | Callable definition: void stage_native(bool decreasing) | calls frontend::rows_detail::step, contradiction, source, occurrences; 2 loop sites · [reviewed contract](#b0048) |
| [B0049 · 462–471](../../../../../src/runtime/sql_rows.cpp#L462) | Callable definition: static void publish(Touched& touched) noexcept | calls end, insert, std::move, erase; growth insert; 1 loop sites · [reviewed contract](#b0049) |
| [B0050 · 472–478](../../../../../src/runtime/sql_rows.cpp#L472) | Callable definition: Epoch commit() | calls consumed, remaining, publish, std::move; returns result; source comment (unverified): // No throwing preparation remains after this barrier. · [reviewed contract](#b0050) |
| [B0051 · 479–482](../../../../../src/runtime/sql_rows.cpp#L479) | Callable definition: void rollback() noexcept | calls clear, reset · [reviewed contract](#b0051) |
| [B0052 · 483–491](../../../../../src/runtime/sql_rows.cpp#L483) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0052) |
| [B0053 · 492–495](../../../../../src/runtime/sql_rows.cpp#L492) | Callable definition: Data(const resource::MemoryAccount& owner, frontend::SqlRowsProgram source, WeightedRuntime::ResultCursor cursor, bool present) :… | calls account, program, std::move, native · [reviewed contract](#b0053) |
| [B0054 · 496–496](../../../../../src/runtime/sql_rows.cpp#L496) | Explanatory comments or spacing. |  |
| [B0055 · 497–526](../../../../../src/runtime/sql_rows.cpp#L497) | Callable definition: std::optional&lt;Result&gt; next() | calls fail, wrapper, cancel, Tuple::copy_of; returns std::nullopt; std::nullopt; growth copy_of; 1 loop sites; source comment (unverified): // Decode/copy can fail after native next() succeeds. This one boundary · [reviewed contract](#b0055) |
| [B0056 · 527–531](../../../../../src/runtime/sql_rows.cpp#L527) | Closes surrounding scope/type. | source comment (unverified): // Copy only the genuine immutable tree/options recipe; the source export and · [reviewed contract](#b0056) |
| [B0057 · 532–545](../../../../../src/runtime/sql_rows.cpp#L532) | Callable definition: std::shared_ptr&lt;detail::StorageWorkContext&gt; detail::SqlColdRebuild::context(const resource::MemoryAccount& account, const SourceS… | calls resource::MemoryFailure, fail, size, empty; returns resource::make_accounted_shared&lt;StorageWorkContext&gt;(account,resource::MemoryPurpose::support_metada…; growth make_accounted_shared; source comment (unverified): // Copy only the genuine immutable tree/options recipe; the source export and · [reviewed contract](#b0057) |
| [B0058 · 546–576](../../../../../src/runtime/sql_rows.cpp#L546) | Callable definition: SqlRowsRuntime detail::SqlColdRebuild::empty(const resource::MemoryAccount& account,const SourceSnapshot& image, frontend::SqlRow… | calls frontend::rows_detail::step, admit, source, size; returns SqlRowsRuntime(resource::make_accounted_shared&lt;SqlRowsRuntime::Data&gt;(account,; growth make_accounted_shared; 1 loop sites; source comment (unverified): // Selected cold recipe admissions precede its owning export. Map/set sorting · [reviewed contract](#b0058) |
| [B0059 · 577–599](../../../../../src/runtime/sql_rows.cpp#L577) | Callable definition: SqlRowsRuntime::PreparedBatch detail::SqlColdRebuild::seed(SqlRowsRuntime& target,const SourceSnapshot& image, storage::IndexWork… | calls data, edits, size, fail; returns SqlRowsRuntime::PreparedBatch(resource::make_accounted_unique&lt;SqlRowsRuntime::PreparedBatch::Data&gt;(; growth make_accounted_unique, push_back, reserve; 1 loop sites; source comment (unverified): // One owned descriptor vector; row payloads borrow the immutable image only · [reviewed contract](#b0059) |
| [B0060 · 600–603](../../../../../src/runtime/sql_rows.cpp#L600) | Callable definition: void detail::SqlColdRebuild::close_source(SqlRowsRuntime& target,Options options) | calls data, close_native, statistics · [reviewed contract](#b0060) |
| [B0061 · 604–622](../../../../../src/runtime/sql_rows.cpp#L604) | Callable definition: SqlRowsRuntime SqlRowsRuntime::rebuild_into(const resource::MemoryAccount& account,const SourceSnapshot& image, Options options,c… | calls source_work, detail::SqlColdRebuild::context, operation, detail::SqlColdRebuild::empty; returns result; rebuilt; source comment (unverified): // Every cold token, journal, result and operation closes before replacement. · [reviewed contract](#b0061) |
| [B0062 · 623–623](../../../../../src/runtime/sql_rows.cpp#L623) | Explanatory comments or spacing. |  |
| [B0063 · 624–624](../../../../../src/runtime/sql_rows.cpp#L624) | Callable definition: SqlRowsRuntime::SqlRowsRuntime(std::shared_ptr&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0063) |
| [B0064 · 625–628](../../../../../src/runtime/sql_rows.cpp#L625) | Callable definition: sql_rows::SourceSnapshot::SourceSnapshot(const resource::MemoryAccount& account, std::uint64_t epoch, const frontend::SqlRowsProg… | calls sequence, program, native_program, native_binding · [reviewed contract](#b0064) |
| [B0065 · 629–632](../../../../../src/runtime/sql_rows.cpp#L629) | Callable definition: SqlRowsRuntime::SqlRowsRuntime(frontend::SqlRowsProgram source, const FreeConnexTree& tree, const PhysicalOptions& physical, Opti… | calls SqlRowsRuntime, create_into, resource::MemoryAccount::create, std::move · [reviewed contract](#b0065) |
| [B0066 · 633–638](../../../../../src/runtime/sql_rows.cpp#L633) | Callable definition: SqlRowsRuntime SqlRowsRuntime::create_into(const resource::MemoryAccount& account, frontend::SqlRowsProgram source, const FreeCon… | calls resource::MemoryFailure, SqlRowsRuntime, std::move; returns SqlRowsRuntime(resource::make_accounted_shared&lt;Data&gt;(account, resource::MemoryPurpose::support_meta…; growth make_accounted_shared · [reviewed contract](#b0066) |
| [B0067 · 639–641](../../../../../src/runtime/sql_rows.cpp#L639) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0067) |
| [B0068 · 642–645](../../../../../src/runtime/sql_rows.cpp#L642) | Callable definition: SqlRowsRuntime::Data& SqlRowsRuntime::data() const | calls fail; returns *data_ · [reviewed contract](#b0068) |
| [B0069 · 646–646](../../../../../src/runtime/sql_rows.cpp#L646) | Callable definition: const frontend::SqlRowsProgram& SqlRowsRuntime::program() const & | calls data; returns data().program · [reviewed contract](#b0069) |
| [B0070 · 647–647](../../../../../src/runtime/sql_rows.cpp#L647) | Callable definition: std::uint64_t SqlRowsRuntime::sequence() const | calls data, sequence; returns data().native.sequence() · [reviewed contract](#b0070) |
| [B0071 · 648–648](../../../../../src/runtime/sql_rows.cpp#L648) | Callable definition: bool SqlRowsRuntime::ready() const | calls ready; returns data_ && data_-&gt;native.ready() · [reviewed contract](#b0071) |
| [B0072 · 649–649](../../../../../src/runtime/sql_rows.cpp#L649) | Callable definition: weighted::Multiplicity SqlRowsRuntime::root_weight() const | calls data, root_weight; returns data().native.root_weight() · [reviewed contract](#b0072) |
| [B0073 · 650–650](../../../../../src/runtime/sql_rows.cpp#L650) | Callable definition: resource::MemoryStatistics SqlRowsRuntime::accounted_memory_statistics() const | calls data, statistics; returns data().account.statistics() · [reviewed contract](#b0073) |
| [B0074 · 651–651](../../../../../src/runtime/sql_rows.cpp#L651) | Callable definition: Epoch SqlRowsRuntime::apply(const Update& update) | calls data, apply; returns data().apply(update) · [reviewed contract](#b0074) |
| [B0075 · 652–655](../../../../../src/runtime/sql_rows.cpp#L652) | Callable definition: std::uint64_t SqlRowsRuntime::source_weight(TableId id, std::span&lt;const Cell&gt; values) const | calls data, root_weight, validate, source; returns count(d.sources\[id.value\], values); source comment (unverified): // Reject private batch state; readers remain allowed. · [reviewed contract](#b0075) |
| [B0076 · 656–686](../../../../../src/runtime/sql_rows.cpp#L656) | Callable definition: sql_rows::SourceSnapshot SqlRowsRuntime::source_snapshot(sql_rows::SourceSnapshotLimits limits) const | calls data, ready, fail, work; returns result; growth push_back, reserve; 4 loop sites · [reviewed contract](#b0076) |
| [B0077 · 687–691](../../../../../src/runtime/sql_rows.cpp#L687) | Callable definition: SqlRowsRuntime::ResultCursor SqlRowsRuntime::results(weighted::CursorOptions options) const | calls data, results, root_weight, ResultCursor; returns ResultCursor(resource::make_accounted_unique&lt;ResultCursor::Data&gt;(d.account,; growth make_accounted_unique · [reviewed contract](#b0077) |
| [B0078 · 692–697](../../../../../src/runtime/sql_rows.cpp#L692) | Callable definition: SqlRowsRuntime::PreparedBatch SqlRowsRuntime::prepare_batch(const NetBatch& batch,weighted::DeltaCapture capture) | calls data, begin_epoch, PreparedBatch, std::move; returns PreparedBatch(resource::make_accounted_unique&lt;PreparedBatch::Data&gt;(d.account,; growth make_accounted_unique · [reviewed contract](#b0078) |
| [B0079 · 698–706](../../../../../src/runtime/sql_rows.cpp#L698) | Callable definition: SqlRowsRuntime::PreparedBatch SqlRowsRuntime::prepare_output_batch(const NetBatch& batch,OutputLimits limits) | calls data, wrapper, semantics, prepare_batch; returns prepared · [reviewed contract](#b0079) |
| [B0080 · 707–707](../../../../../src/runtime/sql_rows.cpp#L707) | Callable definition: SqlRowsRuntime::PreparedBatch::PreparedBatch(resource::AccountedUnique&lt;Data&gt; value) noexcept:data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0080) |
| [B0081 · 708–710](../../../../../src/runtime/sql_rows.cpp#L708) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0081) |
| [B0082 · 711–714](../../../../../src/runtime/sql_rows.cpp#L711) | Callable definition: SqlRowsRuntime::PreparedBatch::Data& SqlRowsRuntime::PreparedBatch::data() const | calls active, fail; returns *data_ · [reviewed contract](#b0082) |
| [B0083 · 715–715](../../../../../src/runtime/sql_rows.cpp#L715) | Callable definition: bool SqlRowsRuntime::PreparedBatch::active() const noexcept | calls active; returns data_ && data_-&gt;active() · [reviewed contract](#b0083) |
| [B0084 · 716–716](../../../../../src/runtime/sql_rows.cpp#L716) | Callable definition: std::uint64_t SqlRowsRuntime::PreparedBatch::sequence() const | calls data, preview; returns data().pending.preview().sequence · [reviewed contract](#b0084) |
| [B0085 · 717–717](../../../../../src/runtime/sql_rows.cpp#L717) | Callable definition: bool SqlRowsRuntime::PreparedBatch::changed() const | calls data; returns data().changed · [reviewed contract](#b0085) |
| [B0086 · 718–718](../../../../../src/runtime/sql_rows.cpp#L718) | Callable definition: const frontend::SqlRowsProgram& SqlRowsRuntime::PreparedBatch::program() const & | calls data; returns data().owner-&gt;program · [reviewed contract](#b0086) |
| [B0087 · 719–721](../../../../../src/runtime/sql_rows.cpp#L719) | Callable definition: storage::IndexWork SqlRowsRuntime::PreparedBatch::source_work() const | calls data, consumed, remaining; returns consumed(d.owner-&gt;options.source_work_limit,d.work.remaining()) · [reviewed contract](#b0087) |
| [B0088 · 722–722](../../../../../src/runtime/sql_rows.cpp#L722) | Callable definition: const weighted::Epoch& SqlRowsRuntime::PreparedBatch::native_preview() const & | calls data, preview; returns data().pending.preview() · [reviewed contract](#b0088) |
| [B0089 · 723–725](../../../../../src/runtime/sql_rows.cpp#L723) | Callable definition: std::optional&lt;std::span&lt;const weighted::BagDelta&gt;&gt; SqlRowsRuntime::PreparedBatch::native_bag_delta_preview() const & | calls data, bag_delta_preview; returns data().pending.bag_delta_preview() · [reviewed contract](#b0089) |
| [B0090 · 726–726](../../../../../src/runtime/sql_rows.cpp#L726) | Callable definition: std::optional&lt;std::size_t&gt; SqlRowsRuntime::PreparedBatch::output_size() const | calls data, output_size; returns data().output_size() · [reviewed contract](#b0090) |
| [B0091 · 727–729](../../../../../src/runtime/sql_rows.cpp#L727) | Callable definition: OutputChangeView SqlRowsRuntime::PreparedBatch::output_change(std::size_t index,std::span&lt;Cell&gt; scratch) const & | calls data, output_change; returns data().output_change(index,scratch) · [reviewed contract](#b0091) |
| [B0092 · 730–730](../../../../../src/runtime/sql_rows.cpp#L730) | Callable definition: std::uint64_t SqlRowsRuntime::PreparedBatch::output_work() const | calls data; returns data().output_spent · [reviewed contract](#b0092) |
| [B0093 · 731–733](../../../../../src/runtime/sql_rows.cpp#L731) | Callable definition: Epoch SqlRowsRuntime::PreparedBatch::commit() | calls data, commit, reset; returns result · [reviewed contract](#b0093) |
| [B0094 · 734–734](../../../../../src/runtime/sql_rows.cpp#L734) | Callable definition: void SqlRowsRuntime::PreparedBatch::rollback() noexcept | calls reset · [reviewed contract](#b0094) |
| [B0095 · 735–735](../../../../../src/runtime/sql_rows.cpp#L735) | Explanatory comments or spacing. |  |
| [B0096 · 736–736](../../../../../src/runtime/sql_rows.cpp#L736) | Callable definition: SqlRowsRuntime::ResultCursor::ResultCursor(resource::AccountedUnique&lt;Data&gt; value) noexcept : data_(std::move(value)) | calls data_, std::move · [reviewed contract](#b0096) |
| [B0097 · 737–739](../../../../../src/runtime/sql_rows.cpp#L737) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0097) |
| [B0098 · 740–743](../../../../../src/runtime/sql_rows.cpp#L740) | Callable definition: SqlRowsRuntime::ResultCursor::Data& SqlRowsRuntime::ResultCursor::data() const | calls fail; returns *data_ · [reviewed contract](#b0098) |
| [B0099 · 744–744](../../../../../src/runtime/sql_rows.cpp#L744) | Callable definition: bool SqlRowsRuntime::ResultCursor::active() const noexcept | calls ; returns data_ && data_-&gt;state == weighted::CursorState::active · [reviewed contract](#b0099) |
| [B0100 · 745–745](../../../../../src/runtime/sql_rows.cpp#L745) | Callable definition: weighted::CursorState SqlRowsRuntime::ResultCursor::state() const | calls data; returns data().state · [reviewed contract](#b0100) |
| [B0101 · 746–746](../../../../../src/runtime/sql_rows.cpp#L746) | Callable definition: std::uint64_t SqlRowsRuntime::ResultCursor::sequence() const | calls data, sequence; returns data().native.sequence() · [reviewed contract](#b0101) |
| [B0102 · 747–747](../../../../../src/runtime/sql_rows.cpp#L747) | Callable definition: std::optional&lt;Result&gt; SqlRowsRuntime::ResultCursor::next() | calls data, next; returns data().next() · [reviewed contract](#b0102) |
| [B0103 · 748–750](../../../../../src/runtime/sql_rows.cpp#L748) | Callable definition: void SqlRowsRuntime::ResultCursor::cancel() noexcept | calls active, cancel · [reviewed contract](#b0103) |
| [B0104 · 751–751](../../../../../src/runtime/sql_rows.cpp#L751) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0104) |

## B0001

[Lines 1–14](../../../../../src/runtime/sql_rows.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:206641c6852813470074fbee62c4f135f2c4a57adff0ef292760d4bd5a8e6d25
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include the closed bridge and owning tree copier in source-row implementation only. |
| inputs / outputs | The runtime TU can use internal cold factory definitions and exact compiler source conversion. |
| invariants | Neither implementation header is made part of the public runtime header surface. |
| ownership | No runtime ownership from includes. |
| failure | Missing implementation declarations fail compile. |
| cost | No runtime cost. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../src/runtime/sql_cold_rebuild.hpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp) |

## B0002

[Lines 15–16](../../../../../src/runtime/sql_rows.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L16:sha256:88dee7cbc5592a2152e731a28e56bd3a8bf254d9d824ddc055c93aa11916ea3a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a runtime container to its receiving account. |
| inputs / outputs | Existing account and purpose to typed allocator. |
| invariants | No nested allocation authority is minted. |
| ownership | Allocator shares the receiver. |
| failure | Invalid authority/purpose propagates fixed MemoryFailure. |
| cost | Constant descriptor work, no payload request. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0003

[Lines 17–17](../../../../../src/runtime/sql_rows.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:8cc688def484437cdbb904146b8b45bacb8598bfe6467b06162bd8bb5c5da37b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present one public SQL runtime rejection. |
| inputs / outputs | Fixed text to owning Error. |
| invariants | No success-path message formatting or catch wrapper. |
| ownership | Exception owns diagnostic strings. |
| failure | Always throws; diagnostic allocation can itself fail and unwind RAII. |
| cost | Error-path string/exception cost only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0004

[Lines 18–20](../../../../../src/runtime/sql_rows.cpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L20:sha256:1f968706a532272dd143bdf1fec3a8f4aade764305c93637ed418954663f6cc4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct Less\`: Immutable nullable keys support borrowed probes. NULL sorts first; all present alternatives use the same exact scalar order as the native core. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/sql_rows.cpp:L21; use that declaration for the actual input/output shape. |
| invariants | The source note states: Immutable nullable keys support borrowed probes. NULL sorts first; all present alternatives use the same exact scalar order as the native core. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Immutable nullable keys support borrowed probes. NULL sorts first; all present alternatives use the same exact scalar order as the native core. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 21–29](../../../../../src/runtime/sql_rows.cpp#L21); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L29:sha256:7f02212601069c0218339c8f5c86566db1f2e7a2a6ed8b8dd95072833e06d98e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order immutable nullable physical/key tuples with borrowed probes. |
| inputs / outputs | Owned Tuple or borrowed cell spans to strict ordering. |
| invariants | NULL sorts before present alternatives for identity, not SQL join truth; all retained keys are valid owning tuples. |
| ownership | No key/text copies; probes borrow synchronous caller/scratch. |
| failure | Comparator is nonthrowing for valid internal tuples. |
| cost | Lexicographic fields plus compared text/decimal widths; map lookup adds logarithmic tree comparisons, not constant time. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0006

[Lines 30–34](../../../../../src/runtime/sql_rows.cpp#L30); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L30-L34:sha256:fc6b8b12269d62fcb2a491cafa4a2b669a91256a765afcc8340237fdd1b54a14
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/sql_rows.cpp: imports or aliases \`Counts = std::map&lt;Tuple, std::uint64_t, Less, resource::MemoryAllocator&lt;std::pair&lt;const Tuple, std::uint64_t&gt;&gt;&gt;\`. Source comment: A detached node uses the receiving map's allocator. Insertion after native commit therefore allocates nothing; the comparator is nonthrowing. |
| inputs / outputs | The span supplies the listed source-level type/member/alias surface to its consumers; exact fields and parameters are the declarations shown here. |
| invariants | The source note says: A detached node uses the receiving map's allocator. Insertion after native commit therefore allocates nothing; the comparator is nonthrowing. Prose alone does not enforce the rule. |
| ownership | Allocator-backed storage uses the explicit account/purpose/attribution shown in the declaration or constructor. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0007

[Lines 35–38](../../../../../src/runtime/sql_rows.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L38:sha256:dfeeced1314e051ca3cae649f4b6a1dd541b8b8123ca7f9c9577ff2b3f9fdf6c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a map insertion before publication. |
| inputs / outputs | Destination allocator, owned key and count to detached node. |
| invariants | The temporary map uses exactly the destination allocator; a later node transfer needs no allocation. |
| ownership | Returned node owns key and its funded node memory. |
| failure | Allocation failure leaves destination unchanged. |
| cost | One map node allocation; constant-size empty temporary tree bookkeeping. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0008

[Lines 39–41](../../../../../src/runtime/sql_rows.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L41:sha256:a72aecbb5ada1ebada5daec402cdc0487597c6d1daccf58632d7e38406ac1b72
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Probe one committed full-row/key count. |
| inputs / outputs | Map and borrowed cell span to zero or stored count. |
| invariants | Absence is zero; live entries have positive counts. |
| ownership | Read-only borrowed probe. |
| failure | No expected failure on valid internal keys. |
| cost | O(log live keys) full lexicographic comparisons; no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0009

[Lines 42–47](../../../../../src/runtime/sql_rows.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L47:sha256:47e5efa39172e2e7876f057329a2dec8582c7fe30a666bf2fd822ce3b162b83d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one exact source/key count replacement. |
| inputs / outputs | Current total and removed/added share to next total. |
| invariants | Subtraction cannot underflow and addition cannot exceed uint64; UNIQUE applies its tighter bound separately. |
| ownership | Inline arithmetic only. |
| failure | Contract/overflow rejection precedes caller publication. |
| cost | Constant checked integer arithmetic. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0010

[Lines 48–52](../../../../../src/runtime/sql_rows.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L52:sha256:56a5f7fedd5e289e524aae3e8f83674e8672158f0d9d680b6e9cb6aadedda365
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report source admissions without refilling authority. |
| inputs / outputs | Original limit and remaining balance to per-domain consumption. |
| invariants | Both values belong to the same allowance; remaining never exceeds limit. |
| ownership | Value snapshots only. |
| failure | Noexcept. |
| cost | Five fixed subtractions, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0011

[Lines 53–57](../../../../../src/runtime/sql_rows.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L57:sha256:6f6d264458e09130f59dd0c9856174b0689e52d849eda25ed948d23e0deeeac2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a tree against a fresh actual program export. |
| inputs / outputs | Immutable program, supplied tree and physical options to plan. |
| invariants | A caller-mutated earlier DTO is not authority; lowering proves an upper bound only. |
| ownership | Cold DTO owns its ordinary workspace; returned plan owns/shares lowered metadata. |
| failure | Export/lowering failure occurs before runtime publication. |
| cost | Complete cold export/validation/lowering, with their own logical limits and copies. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0012

[Lines 58–60](../../../../../src/runtime/sql_rows.cpp#L58); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L60:sha256:f2e681b3b23f7185a533be5fc2ecf41be209a1e0df4906882d80395c5cd1ca3d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/sql_rows.cpp: defines/starts \`struct SqlRowsRuntime::Data\` in this range; closes \`anonymous namespace\` Member/state declarations in this range include \`} struct SqlRowsRuntime::Data {\`. |
| inputs / outputs | This span declares/carries these members or local values: \`} struct SqlRowsRuntime::Data {\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0013

[Lines 61–66](../../../../../src/runtime/sql_rows.cpp#L61); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L66:sha256:89c8c5df0255645905d88f2ea4913a3e3eee6563670095c3ddfda143044326a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep one source-constraint edit private until native commit. |
| inputs / outputs | Map pointer, stable iterator, next count and optional detached node. |
| invariants | Per-source constraints name distinct maps; container addresses remain fixed after construction. |
| ownership | Detached node owns new key; existing iterator borrows the owner map. |
| failure | Destroying an unpublished edit only frees private state. |
| cost | Fixed descriptor; new nodes pay separately. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0014

[Lines 67–77](../../../../../src/runtime/sql_rows.cpp#L67); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L77:sha256:abf70a47ee8deb9daa32c10eed0bd341079833a0fb100ea6b23b12042d07ce24
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/sql_rows.cpp: this range contains member/state declarations Member/state declarations in this range include \`resource::MemoryAccount account\`; \`frontend::SqlRowsProgram program\`; \`Options options\`; \`Items&lt;storage::ScalarView&gt; projected\`; \`std::size_t key_used = 0, other_used = 0, projected_used = 0\`. |
| inputs / outputs | This span declares/carries these members or local values: \`resource::MemoryAccount account\`; \`frontend::SqlRowsProgram program\`; \`Options options\`; \`Items&lt;storage::ScalarView&gt; projected\`; \`std::size_t key_used = 0, other_used = 0, projected_used = 0\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | The declared MemoryAccount field/owner shares the query account supplied at construction. Items is the local vector alias using resource::MemoryAllocator; its constructor binds storage to the passed account. Span/view members borrow their source; retain the source owner for the full use window. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0015

[Lines 78–89](../../../../../src/runtime/sql_rows.cpp#L78); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L89:sha256:39e7b25a72c146e712ece5a20d1b94129d8600a7226d951592fc72f0f8733b49
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve normal source-owner construction while sharing its receiver-funded setup with the cold constructor. |
| inputs / outputs | The normal constructor still imports the genuine source with its actual tree/options/native runtime, then calls the common \`initialize()\` helper. The cold overload supplies an already authenticated native child and calls that same helper. |
| invariants | Occurrence/node, schema-width scratch and enforced-constraint setup run once per new owner; no rows or cold grants are retained by this helper. |
| ownership | The source Data owns its frozen program, native child and receiver-allocated maps/scratch. |
| failure | Freeze, member allocation, contract checks or initialization errors destroy only the unpublished Data. |
| cost | One constructor-time helper call; existing O(tables/constraints/occurrences/schema width) setup, with no per-row steady-state work. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_source_images.md §Closed cold reconstruction](../../../../sql_source_images.md) |

## B0016

[Lines 90–100](../../../../../src/runtime/sql_rows.cpp#L90); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L100:sha256:cbae8641040e77a1db5a3fd56d7d31814a85e08734024e1df2283f2108f98d35
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the same physical source Data around an already genuine cold WeightedRuntime. |
| inputs / outputs | Same receiver/source/options plus a fully built native child -&gt; source/key maps, nodes, fixed scratch, then shared initialize. |
| invariants | Native child is not synthesized from descriptors here; its authentic binding was checked earlier. The original normal constructor path is separate. |
| ownership | Outer Data moves in the child WeightedRuntime, freezes source metadata in receiver and owns all map/scratch state. |
| failure | Program freeze or member/initialize failure unwinds both owners in reverse lifetime order. |
| cost | Construction-sized metadata/scratch only; child program/control handle transfers and receiver cap is authoritative. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [docs/sql_rows_runtime.md §Ownership, costs and failure boundaries](../../../../sql_rows_runtime.md) |

## B0017

[Lines 101–124](../../../../../src/runtime/sql_rows.cpp#L101); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L124:sha256:5aa16c3e6749e092136330be403e6cad9e4a67e764abf7c6049da4411ed5fbbb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share exact source-map, key-map, occurrence-node and scratch initialization across normal and cold constructors. |
| inputs / outputs | A fully member-initialized \`Data\` -&gt; pre-sized source/key maps, occurrence-to-native-node map and maximum-width scratch. |
| invariants | Every noncontradictory SQL occurrence must map to the already checked native shape; same source setup runs once for either constructor. |
| ownership | All vectors/maps use the established receiver account; no input rows are borrowed. |
| failure | Contract or allocation failure aborts only unpublished owner construction. |
| cost | O(tables+constraints+occurrences+maximum schema width) setup and existing indexed storage reads; no per-row steady-state overhead. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/frontend/sql_rows.cpp](../../../../../src/frontend/sql_rows.cpp), [docs/sql_rows_runtime.md §Representation and SQL semantics](../../../../sql_rows_runtime.md) |

## B0019

[Lines 126–129](../../../../../src/runtime/sql_rows.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L126-L129:sha256:dce8d8bef43afaa1b1dcb36b60cd6394560ed3ac9ce088488114292cc3758562
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a physical source port. |
| inputs / outputs | Table ID to borrowed schema. |
| invariants | All catalog table IDs index the compiled source array. |
| ownership | Reference borrows program. |
| failure | Out-of-catalog ID rejects before source mutation. |
| cost | Constant bound check/read. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0020

[Lines 130–139](../../../../../src/runtime/sql_rows.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L130-L139:sha256:8e26d9ef8465e02c1e8b2a74c86364a8feef00fa869cc79d1dd22f6b925eaf51
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the complete physical row, including unused columns. |
| inputs / outputs | Source schema, borrowed cells and optional allowance. |
| invariants | Arity, nullability, exact scalar kind, int/decimal range and UTF8/no-NUL domain hold before lookup. |
| ownership | Reads caller values without freezing/copying. |
| failure | Work/type rejection propagates; pending epoch RAII aborts any held epoch. |
| cost | O(full width plus text/domain bytes); present scalars and selected visits debit the one source grant, not map comparison time. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0021

[Lines 140–141](../../../../../src/runtime/sql_rows.cpp#L140); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L141:sha256:014b869315912f1d72bc4adf668b642f9356e1e750f9f3005379199bf66eb83f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`std::optional&lt;std::span&lt;const Cell&gt;&gt; project_key(const frontend::SqlRowsConstraint& constraint, std::span&lt;const Cell&gt; input, Items&lt;Cell&gt;& target, std::size_t& used, storage::IndexW\`: Both UNIQUE (NULLS DISTINCT) and MATCH SIMPLE foreign keys omit any key containing NULL. A zero-column key is present and denotes the unit key. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/sql_rows.cpp:L142; use that declaration for the actual input/output shape. |
| invariants | The source note states: Both UNIQUE (NULLS DISTINCT) and MATCH SIMPLE foreign keys omit any key containing NULL. A zero-column key is present and denotes the unit key. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0022

[Lines 142–152](../../../../../src/runtime/sql_rows.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L152:sha256:51f83ea7adb5e70c036d33e38aa44bc29290ad1ea38fe6c7d2c068aa3ca0626f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project an enforced nullable key into reusable scratch. |
| inputs / outputs | Admitted columns/input to present key span or NULL exemption. |
| invariants | Any NULL exempts UNIQUE/MATCH SIMPLE; an empty key is engaged and participates. |
| ownership | Span/text borrow scratch/input; used prefix is tracked before writes for cleanup. |
| failure | Admission failure leaves only private scratch, later cleared by Scratch. |
| cost | Key-width visits and scalar-byte admissions; copies inline views, not string bytes. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0023

[Lines 153–158](../../../../../src/runtime/sql_rows.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L158:sha256:43baa60a9a7022c709645a2afd493c69dcc23706c603389911db9abcdd8af8e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an adjusted self-row key against an indexed probe. |
| inputs / outputs | Two key spans and existing allowance to equality. |
| invariants | Unequal arities reject; comparisons preserve exact scalar identity. |
| ownership | Borrowed cells/grant only. |
| failure | Partial debit remains on work failure. |
| cost | Linear compared key fields/bytes, no allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0024

[Lines 159–161](../../../../../src/runtime/sql_rows.cpp#L159); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L161:sha256:50bc13cd0a2b3cf0743ce678442d5cb98f0aa92236f623b628219266f023d887
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`std::uint64_t proposed_count(std::size_t index, std::span&lt;const Cell&gt; probe, const Update& update, storage::IndexWorkAllowance& work)\`: Probe the proposed single-row state without publishing it. This handles self-referencing inserts/deletes and last-parent deletion using indexes, rather than scanning source tables or special-casing self references away. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/sql_rows.cpp:L162; use that declaration for the actual input/output shape. |
| invariants | The source note states: Probe the proposed single-row state without publishing it. This handles self-referencing inserts/deletes and last-parent deletion using indexes, rather than scanning source tables or special-casing self references away. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Probe the proposed single-row state without publishing it. This handles self-referencing inserts/deletes and last-parent deletion using indexes, rather than scanning source tables or special-casing self references away. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0025

[Lines 162–175](../../../../../src/runtime/sql_rows.cpp#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L162-L175:sha256:655f59add9a1f1f783caf86d6ffa1c3e2f3f6c428df58d06224b416e8d6a4c67
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the proposed single-row constraint state. |
| inputs / outputs | Constraint/probe/update to adjusted indexed count. |
| invariants | Self-source matching keys replace weighted UNIQUE share or one live-row FK share; other sources/keys stay committed-old. |
| ownership | Reads index and reusable other-key scratch; publishes nothing. |
| failure | Checked arithmetic/work failures unwind private preparation. |
| cost | One indexed probe and, for the updated source, one key projection/equality; no full table scan. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0026

[Lines 176–201](../../../../../src/runtime/sql_rows.cpp#L176); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L176-L201:sha256:4fae73ecf6d85d0727921e42aa7bb4e625e7754516c0174b5595d7e64cc940c0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce and privately prepare all affected source constraints. |
| inputs / outputs | Source/update to funded edit list. |
| invariants | UNIQUE stays at most one; positive FK rows see a proposed parent; last-parent deletion sees proposed reverse references, including self references. |
| ownership | Only new key nodes/tuples are owned privately; existing counts remain unchanged. |
| failure | Any constraint/allocation/work failure precedes native commit and source/key publication. |
| cost | Affected constraints/key widths plus relevant reverse-FK index probes; no database scan; unchanged counters need no new node. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0027

[Lines 202–204](../../../../../src/runtime/sql_rows.cpp#L202); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L202-L204:sha256:430910ef73b33fc189575b9cb3e141c0f0acc06fc8829850aea3888ecfdfe07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct Scratch\`: Only touched scratch prefixes are cleared. Detached edits own private nodes until publication; clearing them also handles failed preparation. The native PendingEpoch owns all rollback of tentative native changes. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/sql_rows.cpp:L205; use that declaration for the actual input/output shape. |
| invariants | The source note states: Only touched scratch prefixes are cleared. Detached edits own private nodes until publication; clearing them also handles failed preparation. The native PendingEpoch owns all rollback of tentative native changes. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | The note describes a failure or stop boundary: Only touched scratch prefixes are cleared. Detached edits own private nodes until publication; clearing them also handles failed preparation. The native PendingEpoch owns all rollback of tentative native changes. The comment adds no handler; the surrounding code determines the outcome. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0028

[Lines 205–213](../../../../../src/runtime/sql_rows.cpp#L205); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L205-L213:sha256:a42dd7e772994c7bfdb7c1dea0525bc64fb9d8035ada7d8fe0a68f175f5c17e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release only transient source borrows and unpublished nodes. |
| inputs / outputs | Reference to this serialized owner. |
| invariants | Clears only recorded scratch prefixes and edits; native rollback belongs to PendingEpoch. |
| ownership | Does not own caller text or committed keys. |
| failure | Noexcept destructor on all exits. |
| cost | Linear touched scratch descriptors/edit count and private node destruction; no query-wide value-slot sweep. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0029

[Lines 214–255](../../../../../src/runtime/sql_rows.cpp#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L255:sha256:4584ad07ba5884b4edd7071012225cc627e1dc2d13de5a12b753b14a6980caf7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one atomic source-to-all-alias weight replacement. |
| inputs / outputs | Validated next sequence/full row/before/after to source work and native epoch. |
| invariants | Authenticate full source weight, prepare keys, drain every admitted alias, then commit native and publish only funded nonthrowing source/key edits. No-op advances sequence without adapters. |
| ownership | New full source tuple/node only for new positive identities; existing native transaction freezes projections and owns rollback. |
| failure | RAII preserves old sequence/source/key/native state on every precommit failure; no extra catch, cloned state or source undo. |
| cost | Full validation/map probes/constraints plus affected alias and native work; no full result recomputation or extra native count map. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0030

[Lines 256–262](../../../../../src/runtime/sql_rows.cpp#L256); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L256-L262:sha256:b254e8323c84aeb61c21f58a492350f743ac822939b51fe23a2d00c039899daf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold the complete private SQL proposal and its single native transaction. |
| inputs / outputs | Shared SqlRowsRuntime::Data owner, one PendingEpoch, one source allowance, touched source/key maps, and final changed flag. |
| invariants | All committed SQL rows/keys remain old until commit. No caller span or per-row native token is retained; \`changed\` compares final consolidated source weights to committed weights. |
| ownership | Owner keeps Count maps, iterators, program and tuple handles alive. PendingEpoch owns native rollback/journal; Touched maps use the same receiver account. |
| failure | Member unwinding keeps native PendingEpoch alive until rollback while owner is still retained. No catch/retry layer is introduced. |
| cost | Accounted token plus native epoch state; O(T+K) map/control nodes, key payload copies only for new identities, plus actual native-stage/capture cost. |
| Design | src/runtime/sql_rows.cpp:247, include/crown/runtime/sql_rows.hpp:53-80, src/runtime/weighted.cpp:123-273, include/crown/resource/ownership.hpp:40-74 |

## B0031

[Lines 263–263](../../../../../src/runtime/sql_rows.cpp#L263); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L263-L263:sha256:334891f8800902c205ece57a7670492fbf8f8d5f0d5ada9f92748099a82f05dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a transparent lookup of one source-row or constraint-key proposal. |
| inputs / outputs | A domain ID and borrowed nullable Cell span used to find an owned Key. |
| invariants | Domain is part of identity, so equal cell tuples in different source/constraint domains do not collide. Probe ordering uses the same exact nullable scalar ordering as committed Counts. |
| ownership | Borrows caller or owner scratch only during synchronous map lookup; never retained. |
| failure | No validation or ownership change. Invalid row/source input is rejected before or by the caller’s preceding validation path. |
| cost | Fixed domain/span descriptors; each map probe still costs logarithmic node comparisons and compared field/text work, none of which is a constant-time claim. |
| Design | src/runtime/sql_rows.cpp:248, src/runtime/sql_rows.cpp:19-27, include/crown/storage/index_work.hpp:10-44 |

## B0032

[Lines 264–264](../../../../../src/runtime/sql_rows.cpp#L264); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L264-L264:sha256:ab2764887463a9aa130051083c641cfa345f866c3b162ab2f445dd50921b29b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the identity of one touched proposal key. |
| inputs / outputs | Domain ID and immutable nullable Tuple for one physical source row or projected enforced key. |
| invariants | Key ordering compares domain first and complete tuple identity second; rows and constraints use separate Touched maps. |
| ownership | An existing committed Tuple copy shares its immutable payload; a new identity owns a Tuple frozen into the receiving account. |
| failure | New payload/account allocation or Touched node allocation can fail during preparation before publication. |
| cost | Fixed Tuple handle plus one Touched map node; only absent committed keys copy cell descriptors/string bytes into a new accounted tuple. Comparisons retain field/byte cost. |
| Design | src/runtime/sql_rows.cpp:249, src/runtime/aggregate_tuple.cpp:21-49, include/crown/resource/ownership.hpp:22-38 |

## B0033

[Lines 265–276](../../../../../src/runtime/sql_rows.cpp#L265); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L265-L276:sha256:e4f213ff8f826247310222753b3a21f18783c7d0568a35f2c171f01c9dc169c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide strict transparent ordering for owned proposal keys and borrowed probes. |
| inputs / outputs | Compares Key/Key, Key/Probe, or Probe/Key by domain then Less over nullable cell spans. |
| invariants | All overloads use the same tuple order as Counts, so a borrowed probe matches the exact full tuple without constructing an owning temporary. |
| ownership | Comparator borrows both operands; it owns no key and allocates nothing. |
| failure | Declared noexcept for valid internal scalar tuples; no SQL exception boundary or fallback comparator is added. |
| cost | Each std::map operation performs logarithmically many comparisons, each potentially visiting tuple fields and string/decimal widths; this work is not fully metered by source_work_limit. |
| Design | src/runtime/sql_rows.cpp:250, src/runtime/sql_rows.cpp:19-27, include/crown/storage/index_work.hpp:10-44 |

## B0034

[Lines 277–282](../../../../../src/runtime/sql_rows.cpp#L277); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L277-L282:sha256:bbd0e31a39eb79d2e0802953720c1db853d0c6b1ae0845383ced3e996758f8a2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one destination map edit until the common commit barrier. |
| inputs / outputs | Destination Counts pointer, committed iterator/end marker, committed before, final after, and optional detached node handle. |
| invariants | Before is captured from committed Counts; after is consolidated from the input chain or key-share updates. No writer can invalidate the iterator or prepared-absence proof while the native epoch is active. |
| ownership | Target pointer/iterator borrow the shared SQL owner. A genuinely new destination node owns its key and destination allocator. |
| failure | Node creation may fail before staging/commit; destroying an unpublished Proposal only releases private state. |
| cost | Fixed descriptors per touched identity; one destination map node is allocated only for a new nonzero final publication. |
| Design | src/runtime/sql_rows.cpp:262, src/runtime/sql_rows.cpp:247-275, src/runtime/sql_rows.cpp:375-380 |

## B0035

[Lines 283–292](../../../../../src/runtime/sql_rows.cpp#L283); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L283-L292:sha256:1cb6aa3756430651f0d31884df70832ff95737a2e1f505afc3e90519eb025d46
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare touched-row/key maps, retained native ownership and fixed opt-in output metadata. |
| inputs / outputs | Touched aliases an account-allocated Key-&gt;Proposal map; fields retain shared SQL owner, pending native epoch, source allowance, rows/keys maps, changed, optional OutputLimits and output_spent=0. |
| invariants | Field declarations do not populate maps or capture/decode output. One output_spent belongs to the token, and disengaged output_limits denotes native-only preparation. |
| ownership | Map backing is allocated later with the account allocator; owner/pending retain real SQL/native state. Added optional limits/counter contain no output-row graph. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | src/runtime/sql_rows.cpp:268, include/crown/resource/ownership.hpp:22-38, include/crown/storage/index_work.hpp:10-21, [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0036

[Lines 293–297](../../../../../src/runtime/sql_rows.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L293-L297:sha256:4022ca8fcbcf262851d4d05afd8b6098fc548e30ce7f0a4ea167a8107a0bc3e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep ordinary net-batch validation unchanged while moving its shared preparation loop into one helper. |
| inputs / outputs | The normal constructor creates its ordinary source allowance and calls \`prepare(batch)\`; the cold overload aliases the one fixed-diagnostic cold root and calls the same helper. |
| invariants | Both paths keep the same complete physical-row chain consolidation, type/null/UTF8 checks, final UNIQUE/FK view and decrease-before-increase native staging. |
| ownership | Input rows borrow through synchronous preparation; only the active PreparedBatch token owns private proposals/native rollback, and the caller’s cold root outlives its alias. |
| failure | Validation/work/allocation/native failure leaves source proposals unpublished; the existing PendingEpoch rolls back. Token destruction remains the rollback boundary. |
| cost | The moved body is token-equivalent to the prior preparation loop; a cold alias adds no independent balance or heap allocation. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md) |

## B0037

[Lines 298–302](../../../../../src/runtime/sql_rows.cpp#L298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L298-L302:sha256:9829eccfbf2056da206f811ee959f90a0e4d60491be46b179ab990a854a23ef8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the one outer cold source-work root for the same preparation algorithm. |
| inputs / outputs | Closed cold bridge passes its canonical allowance by reference; this constructor wraps it in the existing nonowning fixed-diagnostic alias then calls prepare. |
| invariants | No new grant/refill/copy; root remains alive through seed/commit/token destruction; same source validation and final-constraint path as normal batches. |
| ownership | Alias does not own root; its lifetime is bounded by prepared token, while the outer rebuild scope keeps root alive. |
| failure | A failed prepare unwinds alias/token and native pending transaction; cold factory publishes nothing. |
| cost | Nonallocating alias view plus the same proposal/work cost as one complete source seed. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/storage/index_work_alias.hpp](../../../../../src/storage/index_work_alias.hpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md) |

## B0038

[Lines 303–331](../../../../../src/runtime/sql_rows.cpp#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L303-L331:sha256:d24988b4d29a18e8a60cb583d248b0d43f96141561b71944b7e403c917c2f824
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a no-op link in a repeated source-row chain without adding proposal ownership. |
| inputs / outputs | Checks edit.before against the latest queued after value, or the committed row count when no proposal exists. |
| invariants | A no-op does not create a Touched key or Tuple payload; later non-no-op links still chain against the same proposed/committed value. |
| ownership | Reads borrowed replacement and a borrowed Probe; retains neither. |
| failure | A mismatched expected weight rejects the whole prepare before SQL/native publication. |
| cost | Row validation and a touched/committed map probe plus selected work admissions; no new Touched node or tuple copy for this branch. |
| Design | src/runtime/sql_rows.cpp:286, src/runtime/sql_rows.cpp:284-295, Refactor.md:874-878 |

```text
      if(proposal.after>owner->options.native.multiplicity_limit)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cap only each consolidated final physical source weight. |
| inputs / outputs | Final Proposal.after against the configured native multiplicity limit. |
| invariants | Intermediate chain endpoints can exceed the cap when the same row’s final weight fits; no intermediate endpoint is staged or published. |
| ownership | Reads token-owned proposal scalar values only. |
| failure | A final over-cap weight throws sql_rows_overflow before key/node/native preparation. |
| cost | One selected source structural admission per touched source proposal; constant integer comparison. No new map or tuple allocation. |
| Design | src/runtime/sql_rows.cpp:299, src/runtime/sql_rows.cpp:296-304, include/crown/runtime/weighted.hpp:19-34 |

```text
    update_keys(true);update_keys(false);validate_keys();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one final constraint view in decrease, increase, then validation phases. |
| inputs / outputs | All consolidated source proposals feed touched key counters before final checks. |
| invariants | Every key decrease is applied before any increase, preventing transient counter overflow for final-valid states; all final key proposals exist before UNIQUE/FK validation. |
| ownership | Mutates only token-owned proposal maps and scratch; committed Counts maps remain unchanged. |
| failure | Checked counter underflow/uint64 overflow, source-work, allocation, UNIQUE, or FK failure precedes native staging and publication. |
| cost | Two affected-constraint passes and one touched-key validation pass; no catalog-wide source scan. |
| Design | src/runtime/sql_rows.cpp:305, src/runtime/sql_rows.cpp:302-306, Refactor.md:874-878 |

```text
void prepare(const NetBatch& batch)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize the complete cold image through the ordinary net-source preparation algorithm. |
| inputs / outputs | One NetBatch of every physical image row at C, each expected from zero to a positive count -&gt; touched source/key proposals plus one native pending epoch. |
| invariants | Rows are full physical identities, not ordered transport fragments; duplicate positive keys fail expected-zero chaining. Validate types/UTF8, final multiplicity and final UNIQUE/FK state, then remove key shares before additions and stage native removals before additions. |
| ownership | Replacement spans borrow immutable image Tuples only during synchronous prepare; inserted source rows copy into receiver-owned state. |
| failure | Validation, expected-weight, constraint, native work or allocation failure leaves source counts uncommitted; PendingEpoch destructor rolls back. |
| cost | One pass over edits plus touched maps/constraints and actual native stages; work counters are selected and map ordering/comparison costs remain separate. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_rows_batches.md §Native staging and publication](../../../../sql_rows_batches.md) |

## B0039

[Lines 332–342](../../../../../src/runtime/sql_rows.cpp#L332); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L332-L342:sha256:dd86a4f0818f606dd505fe536fb1b5645859319fe67df49e02a30776d9b88bd5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the final SQL-presented change count of this active prepared token. |
| inputs / outputs | Active token and immutable bound presentation in; nullopt on old preparation, else native bag/support change count or zero/two EXISTS rows. |
| invariants | Numeric/source/root state is unchanged. DISTINCT support facts and plain bag facts remain different native authorities; EXISTS tests only full-root before/after presence. |
| ownership | The count borrows no output storage and allocates no result mirror; the token retains the genuine program/native capture. |
| failure | Missing expected native capture is an internal SQL contract error. Public forwarding retains the existing active-token guard. |
| cost | O(1) mode/root/span reads; no tuple decode, source scan or grant refill. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0040

[Lines 343–371](../../../../../src/runtime/sql_rows.cpp#L343); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L343-L371:sha256:554448088350481d0e40469c1397b75374f33da373b18879a00d8b05683ad4d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one correctly presented SQL tuple change through exact-width caller scratch under the single retained decode allowance. |
| inputs / outputs | Admitted output index and scratch width equal to program.outputs().size() in; nullable ordered cells plus exact signed uint64 magnitude out. |
| invariants | Every call spends one row plus one field unit per output, across all codec passes. Bag preserves numeric magnitude; DISTINCT preserves unit support; EXISTS returns -oldBoolean then +newBoolean. Payload/presence/constants mapping is the genuine injective SQL output mapping. |
| ownership | The returned cells borrow caller scratch and live token program/native payloads. Reuse/close invalidates the view; no output tuple vector, string copy, snapshot or persistent graph is created. |
| failure | Disabled/wrong-index/wrong-width/work-limit errors occur before scratch mutation; budget failure leaves the active unpublished token for caller rollback. No catch/refill/fallback is added. |
| cost | Selected 1+width decode work per call, O(width) scalar descriptors and O(1) per string descriptor. Serialized byte visits/canonical sorting remain separately bounded codec work. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0041

[Lines 372–372](../../../../../src/runtime/sql_rows.cpp#L372); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L372-L372:sha256:4ef6cf874f092f1249b159bfe7f616fb3f9680e2eafc77bc60b1f1c29de26e63
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make token destruction roll back any still-active preparation. |
| inputs / outputs | Destructor delegates to the idempotent noexcept rollback path. |
| invariants | An already committed/rolled-back token has no owner and requires no source inverse; SQL state was not changed before commit. |
| ownership | Destroying token Data releases its native token and shared owner after proposal cleanup. |
| failure | Noexcept RAII cleanup; native rollback is the only inverse for staged query edits. |
| cost | Destroys remaining Touched nodes/native undo and releases account residents; this is actual cleanup work proportional to retained private state. |
| Design | src/runtime/sql_rows.cpp:309, src/runtime/sql_rows.cpp:311-312, src/runtime/weighted.cpp:300-310 |

## B0042

[Lines 373–373](../../../../../src/runtime/sql_rows.cpp#L373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L373-L373:sha256:dbcf25718ebf938d046fbd137206dd278ef497e72851b1d7c07ba51fae8d786c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report whether both the SQL owner and native pending epoch remain live. |
| inputs / outputs | Returns true only while owner is retained and PendingEpoch is active. |
| invariants | A moved/closed/committed/rolled-back token reports false; no committed sequence is inferred from this flag. |
| ownership | Reads shared owner and token state without extending lifetime or returning a reference. |
| failure | Noexcept scalar check. |
| cost | Constant pointer/token-state checks. |
| Design | src/runtime/sql_rows.cpp:310, src/runtime/weighted.cpp:680-686 |

## B0043

[Lines 374–399](../../../../../src/runtime/sql_rows.cpp#L374); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L374-L399:sha256:f2a85dcb261a44b9b3ad2d5f1476ab528c4b1f8c273f8115254078f66dd82d71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find or create one proposal after authenticating its expected before weight. |
| inputs / outputs | Touched map/domain, destination Counts map, borrowed full row, and optional expected weight to mutable Proposal. |
| invariants | Existing proposal requires exact queued-after match; first touch requires expected equal committed count. Existing committed Tuple handles are copied shared; only absent keys are frozen. |
| ownership | Returned Proposal is a reference into the token-owned Touched map; source/constraint destination iterators borrow the retained owner. |
| failure | Mismatch fails before a new key copy. Source-work exhaustion and accounted Tuple/map allocation fail before publication. |
| cost | Two logarithmic map probes on first touch; new keys pay per-cell/string-byte admission plus Tuple and map-node allocation. Existing hits share payload, while comparator comparisons still cost actual fields/bytes. |
| Design | src/runtime/sql_rows.cpp:311, src/runtime/sql_rows.cpp:311-336, src/runtime/aggregate_tuple.cpp:21-49, include/crown/storage/index_work.hpp:10-44 |

## B0044

[Lines 400–416](../../../../../src/runtime/sql_rows.cpp#L400); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L400-L416:sha256:7801005c429b12d0ea8c729e66770fba3395240450e45e44beb2b5f1b04f603f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply the requested sign of each source row’s share to its affected constraint keys. |
| inputs / outputs | Source proposals and compiled source.constraints, with \`decreasing\` selecting all removals or additions. |
| invariants | UNIQUE counters use full before/after weights; FK reverse counters use positive-row presence. NULL-containing projected keys are exempt; zero-column keys remain present. Checked replace_count updates private final values. |
| ownership | Projection spans borrow owner scratch/source tuple; key proposals own/share Tuple handles in token maps. |
| failure | Source-work, key copy/account, or uint64 counter errors abort before publication. |
| cost | Visits touched rows × their compiled constraints in each pass, projects only affected widths, and performs touched/committed ordered-map work; no source-table scan. |
| Design | src/runtime/sql_rows.cpp:337, src/runtime/sql_rows.cpp:337-353, docs/sql_rows_runtime.md:133-150, include/crown/storage/index_work.hpp:10-44 |

## B0045

[Lines 417–421](../../../../../src/runtime/sql_rows.cpp#L417); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L417-L421:sha256:e099825104b334c27956b9e38ce1dd4bf61aa82dc74331e8e9b353c46def097f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a constraint count from the proposed final view. |
| inputs / outputs | Constraint domain and borrowed key to touched proposal after-value or committed Counts count. |
| invariants | Touched proposals shadow committed counts; untouched identities remain committed. Lookup allocates no temporary Tuple. |
| ownership | The probe borrows tuple/scratch bytes; returned count is by value. |
| failure | Work-limit exhaustion can fail during lookup before native staging. |
| cost | One or two source-work steps plus logarithmic touched/resident map comparisons with actual field/text costs; no tuple allocation. |
| Design | src/runtime/sql_rows.cpp:354, src/runtime/sql_rows.cpp:354-358 |

## B0046

[Lines 422–437](../../../../../src/runtime/sql_rows.cpp#L422); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L422-L437:sha256:24bedb16ed723c00e5551e8b9fb484c8a61447bcf5dad72fc3f1deccba437c29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce UNIQUE and MATCH SIMPLE FK invariants on the complete proposed final state. |
| inputs / outputs | Each touched constraint key Proposal and compiled parent/referenced_by metadata. |
| invariants | Positive final child count requires a positive final parent; final UNIQUE count is at most one; when a parent key becomes absent, every reverse child index is checked through final_count, including untouched child rows. All key proposals exist first, so swaps, self references and cycles use the same final view. |
| ownership | Reads immutable program arrays and token-owned proposal maps; publishes nothing. |
| failure | UNIQUE/FK/work errors precede all native staging and source publication. |
| cost | O(touched key identities plus reverse references of removed parent keys) final probes; does not scan source tables or copy the catalog. |
| Design | src/runtime/sql_rows.cpp:359, src/runtime/sql_rows.cpp:359-374, docs/sql_rows_runtime.md:133-150 |

## B0047

[Lines 438–444](../../../../../src/runtime/sql_rows.cpp#L438); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L438-L444:sha256:5f19023a2aa6ee7c0bf76b3b7ffa15a5abe7271cab7cf594f441a7ef00e96b64
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate detached destination nodes before the commit decision. |
| inputs / outputs | Touched proposals whose final nonzero key is absent from its destination Counts map. |
| invariants | Only changed new keys with positive after-values get a node; existing keys use stable iterators, deleted/unchanged keys need none. |
| ownership | Node handle uses the exact destination map allocator and existing immutable Tuple handle. |
| failure | Account or allocator failure occurs before native staging/commit; proposal cleanup releases detached nodes. |
| cost | One destination map-node allocation per genuinely new publication, plus a selected work step per touched entry; no full-map copy. |
| Design | src/runtime/sql_rows.cpp:375, src/runtime/sql_rows.cpp:375-381, src/runtime/sql_rows.cpp:33-36 |

## B0048

[Lines 445–461](../../../../../src/runtime/sql_rows.cpp#L445); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L445-L461:sha256:8d3681ca55c0568e67d3a4a3a8ae4284ac13f395144ce96e108b9c76142fb481
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route all changed physical source shares through compiled aliases in one native epoch. |
| inputs / outputs | Consolidated source proposals, their direction, compiled occurrences/nodes, and one pending native contribution port. |
| invariants | The first full pass stages every decrease across all rows/aliases; the second stages increases. Contribution before/after is authenticated by the source ledger; native adapter replaces that share in its existing total. Contradiction/filter paths may have no native calls while source/constraints still commit. |
| ownership | Adapt borrows source/program/scratch only for the call; WeightedRuntime freezes native scope before returning. Same PendingEpoch and indexed grant span all calls. |
| failure | Adapt/work/native stage failure aborts the sole PendingEpoch and unwinds all private source/key proposals; no SQL publication has happened. |
| cost | Visits touched rows and actual compiled aliases/adapter steps twice by direction; native delta capture, if enabled, adds weighted traversal/collector work. No per-native-tuple source mirror or per-row grant. |
| Design | src/runtime/sql_rows.cpp:382, src/runtime/sql_rows.cpp:382-398, src/runtime/weighted.cpp:687-718, include/crown/runtime/weighted.hpp:228-249 |

## B0049

[Lines 462–471](../../../../../src/runtime/sql_rows.cpp#L462); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L462-L471:sha256:a0583f9aa4dc1f75cd7d36f578f3ee929a115abf28b39d80daa6bdc3b01359cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply already prepared net key/source edits after native commit. |
| inputs / outputs | Touched proposals with before/after, retained destination map/iterator, and optional detached node. |
| invariants | Only same-allocator node insertion, iterator erase, or scalar assignment occurs. No comparator can throw for admitted immutable tuples; prepared distinct-key identities and exclusive writer state preserve insert absence. |
| ownership | Maps/iterators belong to retained SQL owner; detached nodes own their destination allocator until inserted. |
| failure | Declared noexcept; required allocations, validation and native arithmetic have already completed before this barrier. |
| cost | One visit per touched entry, plus logarithmic destination-map typed-key comparisons for each new node insertion and actual old-node/tuple/account teardown. Detached nodes prevent new allocation; they do not remove search or cleanup work. |
| Design | src/runtime/sql_rows.cpp:399, src/runtime/sql_rows.cpp:399-408, src/runtime/sql_rows.cpp:33-36 |

## B0050

[Lines 472–478](../../../../../src/runtime/sql_rows.cpp#L472); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L472-L478:sha256:190ab661bfeeaebc685f899255a88fe1f62dab9944fd5a45e895d60fa641e1fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit the native token and then publish the SQL final counters as one serialized decision. |
| inputs / outputs | No caller input; returns Epoch with source changed flag, consumed source-work snapshot, and owning native Epoch. |
| invariants | Samples source work before native commit; after that barrier publishes keys then rows using nonallocating edits, clears touched proposals, and releases shared SQL owner. No external callback/concurrent observer runs inside the brief internal order. |
| ownership | Returned native result owns output/journal/captured facts. This internal method clears proposals/releases the shared SQL owner; the public PreparedBatch::commit wrapper immediately resets data_ before returning, destroying the embedded PendingEpoch and its retained capacities. |
| failure | Calling on inactive token is rejected by the public data() accessor. All preparation failures occurred earlier; native commit is the existing native decision boundary. |
| cost | Traverses touched proposals, performs logarithmic destination-map typed comparisons for each new insertion, and runs native prepared commit plus node cleanup and prompt wrapper reset. No full state copy, new allocation, sort or final key validation follows the decision. |
| Design | src/runtime/sql_rows.cpp:409, src/runtime/sql_rows.cpp:409-415, src/runtime/weighted.cpp:727-732 |

## B0051

[Lines 479–482](../../../../../src/runtime/sql_rows.cpp#L479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L479-L482:sha256:d79e58b910c386ec2a96c9fffceaec4e36686fb108cd207b52a02514233f0915
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard private proposals and restore the one native epoch without changing SQL source/key state. |
| inputs / outputs | No arguments; rolls back if owner is still retained. |
| invariants | Idempotent after first close. Pending native undo runs before proposals/owner are released; committed SQL maps never needed inverse edits because publication was deferred. |
| ownership | The Data destructor calls this rollback, which clears proposals and releases the shared SQL owner; member destruction immediately follows and destroys native PendingEpoch Data, including retained vector capacities/journal members. |
| failure | Noexcept; no error translation or retry handler. |
| cost | Native inverse and private map/node destruction scale with actually staged/touched state; no SQL table scan or clone. |
| Design | src/runtime/sql_rows.cpp:416, src/runtime/sql_rows.cpp:416-421, src/runtime/weighted.cpp:205-243 |

## B0052

[Lines 483–491](../../../../../src/runtime/sql_rows.cpp#L483); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L483-L491:sha256:bef40f0c446313f65f26719edb17ceb5c5731fd731df639ebb72ed7e569c21b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/sql_rows.cpp: defines/starts \`struct SqlRowsRuntime::ResultCursor::Data\` in this range; closes \`struct SqlRowsRuntime::PreparedBatch::Data\` Member/state declarations in this range include \`frontend::SqlRowsProgram program\`; \`weighted::CursorState state = weighted::CursorState::active\`; \`bool exists, emitted = false\`. |
| inputs / outputs | This span declares/carries these members or local values: \`frontend::SqlRowsProgram program\`; \`weighted::CursorState state = weighted::CursorState::active\`; \`bool exists, emitted = false\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | The declared MemoryAccount field/owner shares the query account supplied at construction. Items is the local vector alias using resource::MemoryAllocator; its constructor binds storage to the passed account. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0053

[Lines 492–495](../../../../../src/runtime/sql_rows.cpp#L492); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L492-L495:sha256:a698adfef2054b192553aabcc96994fcaf41a6bd5e927bccacd6389b42b0edb9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain reader/program and fund one reusable nullable output buffer. |
| inputs / outputs | Receiver, shared program, native cursor and sampled presence. |
| invariants | Cursor lifetime is independent of wrapper source maps; sampled EXISTS presence is protected by its reader lease. |
| ownership | Owns native reader and program handle; output scratch uses receiver. |
| failure | Partial member construction closes the moved native reader through RAII. |
| cost | Fixed handle moves plus one output-width descriptor buffer; no result materialization at construction. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0055

[Lines 497–526](../../../../../src/runtime/sql_rows.cpp#L497); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L497-L526:sha256:c8cbb1b5af5212708f68323dabbbce1ddb831a9654deced21a8dc3a9fa8a8dd7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one compressed native row or one EXISTS Boolean. |
| inputs / outputs | Active cursor to owning tuple/weight/schema or terminal absence. |
| invariants | Injective head decoder consolidates NULL/repeated/constants correctly; DISTINCT emits one; EXISTS always emits one and retains its lease through the last result. Output thresholding does not replace the maintained bounded weighted arithmetic or remove intermediate overflow. |
| ownership | Copies SQL payload into receiver-owned Tuple before native row destruction; shares program schema; scoped cleanup removes output borrows. |
| failure | One required catch cancels/fails the cursor if native traversal/decoding/copy fails; already returned outputs stay valid. |
| cost | Native cursor work plus O(SQL width + copied text bytes) and nullable tuple ownership. This is an additional freeze of an owned core row; not allocation-free. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0056

[Lines 527–531](../../../../../src/runtime/sql_rows.cpp#L527); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L527-L531:sha256:bfab84f30580e073f198f9a6363051afba7b256aaaddf5cb0c36f8c65918ab0d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State which selected admissions the cold recipe explicitly charges. |
| inputs / outputs | The new source implementation applies recipe-field/text admissions before copying actual tree/options and lower_tree input. |
| invariants | Only selected source_work charges are claimed; map/set sorting, JSON, identity, compiler DTO and planner validation retain their own documented scopes. |
| ownership | Comment documents transient recipe data; no recipe retained in owner. |
| failure | No failure behavior from comment; actual allowance exhaustion is reported by the existing work path. |
| cost | No CPU/allocation bound follows from the selected IndexWork charges. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_source_images.md §Limits and measured work](../../../../sql_source_images.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0057

[Lines 532–545](../../../../../src/runtime/sql_rows.cpp#L532); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L532-L545:sha256:c239a73e08b78384fd6a7ad7cbff0e4c7327920f6cb2263fb2a4f86c5c25680f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate basic image/receiver limits and construct the cold native work context. |
| inputs / outputs | Requires a real receiver, source/native programs, distinct-row count within limit, no rows at C=0, finite lowering+identity work and indexed-grant presence exactly matching the native plan. |
| invariants | This initial check does not authenticate editable row payloads or durable provenance; later actual lowerer/binding and source path do that. Ordered images get no indexed work context. |
| ownership | Returns one receiver-accounted shared StorageWorkContext with the optional immutable indexed ceiling. |
| failure | Empty account, malformed handles/sequence/rows, invalid finite lowering, or backend/grant mismatch fail before owner construction. |
| cost | One context/control allocation and scalar checks; no row payload scan or work lease yet. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md) |

## B0058

[Lines 546–576](../../../../../src/runtime/sql_rows.cpp#L546); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L546-L576:sha256:b48fe5c5f1f7bd873816b346c1775064c367796818cacfa1be01bd9b593829e3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recreate an empty source/native owner from the genuine source core and captured physical recipe. |
| inputs / outputs | Source program, actual native snapshot and receiver -&gt; copy actual tree/options DTOs, lower genuine source core, compare physical and source hashes, check operational multiplicity binding, construct at base C−1 or zero, then compare complete weighted Binding. |
| invariants | No editable DTO is accepted as authority; actual lower_tree and source validation are repeated. Ordinary source/native capture flags are reset for the cold child. Only recipe text/node fields are selected into source_work; compiler DTO/identity/validation work remain separate. |
| ownership | New compiled/source/native structures use the receiving account; input program/tree handles are borrowed for synchronous import. |
| failure | Lowering, digest, binding/domain, account/work or allocation errors destroy unpublished empty state. |
| cost | Recipe field/byte counters, lower_tree.work, native work and indexed work are separate; no whole-compiler CPU or malloc theorem. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/planner_proofs.md §Independent tree verification (P02)](../../../../planner_proofs.md), build/verification/w06-sql-aggregate-cold-rebuild-design-v1/cost-and-lifetime.md:18 |

## B0059

[Lines 577–599](../../../../../src/runtime/sql_rows.cpp#L577); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L577-L599:sha256:88ecd303fc6249c8ad28d59c25a36ced7a588439a749bbc1955b694a19002770
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed every complete physical row in one authentic source transaction at the image sequence. |
| inputs / outputs | Image entries -&gt; receiver-accounted SourceReplacement descriptors with expected weight zero and positive after weight; one native PendingEpoch uses requested capture mode. |
| invariants | Input order is accepted; duplicate complete row identities fail chain checks. Existing row/type/null/UTF8 and final UNIQUE/FK validations remain the authority. |
| ownership | Temporary descriptor spans borrow image tuples through \`prepare\` only; new persistent full tuple keys/payloads copy into receiving account. |
| failure | Zero weight/overflow/validation/work/allocation/native failures discard staged source proposals and roll back pending epoch. |
| cost | One accounted descriptor vector with admitted pointer slots, one source row pass, then normal proposal/constraint/native seed work; no expanded copies by multiplicity. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_rows_batches.md §Expected chains and final constraints](../../../../sql_rows_batches.md), [docs/sql_source_images.md §Limits and measured work](../../../../sql_source_images.md) |

## B0060

[Lines 600–603](../../../../../src/runtime/sql_rows.cpp#L600); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L600-L603:sha256:2a672c403c9e99d58214f332b4dea83359b26d41467bbe839f63f3e0b1c2335c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace the cold native context with the normal operational source/native context after teardown. |
| inputs / outputs | A closed reconstructed SqlRowsRuntime plus original Options -&gt; fresh validated normal storage context and restored source options. |
| invariants | Must have no active cold lease/readers/writer; retain original multiplicity/plan context, do not mutate immutable Context.limit. Receiver cap is authoritative. |
| ownership | The runtime keeps only new normal context/options; old cold allowance is no longer retained by journals/cursors. |
| failure | Context validation/allocation can fail while the outer runtime is still private to rebuild_into. |
| cost | One fresh Context/control allocation and validation after cold state closure; no per-row cost. |
| Design | [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md), [build/verification/w06-sql-aggregate-cold-rebuild-design-v1/cost-and-lifetime.md §Close ordering audit](../../../../../build/verification/w06-sql-aggregate-cold-rebuild-design-v1/cost-and-lifetime.md) |

## B0061

[Lines 604–622](../../../../../src/runtime/sql_rows.cpp#L604); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L604-L622:sha256:4735633ff8db1f46f67139500338d1b673c365993efc1f986ccc483648822a07
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild a complete source image through one cold operation and publish only a normal owner. |
| inputs / outputs | Receiver/image/options/cold limits -&gt; source rows, root frontier, optional selected metrics. At C=0 create empty source; at C&gt;0 seed one batch at C. |
| invariants | Actual image program/plan/binding and input rows revalidate; source_work stays one root, indexed work is one lease, normal options restored after the lambda closes all temporary token/journal/result/operation owners. No durable authenticity is inferred from \`sequence\`. |
| ownership | Returned SqlRowsRuntime owns all receiving state; image/caller storage remains separate. Borrowed source Tuple spans end at prepare return. |
| failure | Any earlier failure destroys unpublished owner and leaves report untouched; successful metric write is last before return. |
| cost | Reports source/native/indexed/lowering distinct admissions; selected counters exclude full compiler/JSON/allocator/cpu work and comparison bounds. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [docs/sql_source_images.md §Recovery boundary](../../../../sql_source_images.md), build/verification/w06-sql-aggregate-cold-rebuild-design-v1/cost-and-lifetime.md:18 |

## B0063

[Lines 624–624](../../../../../src/runtime/sql_rows.cpp#L624); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L624-L624:sha256:76423d1bea9136590e92dd15ee56bf2e9049e5862c74656f3a28e3686ce98792
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the fully constructed shared SQL runtime owner. |
| inputs / outputs | Private shared Data handle to runtime facade. |
| invariants | Construction authority stays inside the factory. PreparedBatch may retain the same Data after the facade moves or dies. |
| ownership | Moves one shared owner reference into the facade; no source/native state clone. |
| failure | Noexcept. |
| cost | Constant shared_ptr move; shared control allocation was funded once by create_into, with actual later reference-count operations. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), include/crown/resource/ownership.hpp:60-74, src/runtime/sql_rows.cpp:471-475 |

## B0064

[Lines 625–628](../../../../../src/runtime/sql_rows.cpp#L625); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L625-L628:sha256:b706fe076e637e139e591f588d110211efdb4367447a54df47882672846a9c2e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize the owning physical-source image’s immutable handles, sequence and account-bound row vector. |
| inputs / outputs | Copies sequence, SqlRowsProgram, CompiledProgram and weighted::Binding inputs; constructs an empty OwnerAllocator-backed SourceEntry vector using output_buffer purpose. |
| invariants | Copies existing shared immutable handles and the fixed binding value; the constructor neither scans source rows nor proves that caller-supplied fields match. |
| ownership | The row vector allocator retains the receiving MemoryAccount; program/native handles share their own immutable account owners. |
| failure | Allocator/account construction can fail. This initializer has no catch or state rollback responsibility. |
| cost | Copies handles/scalars without cloning compiler or row payloads; vector storage is allocated only when the capture later reserves entries. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/resource/owner_allocator.hpp](../../../../../include/crown/resource/owner_allocator.hpp), [include/crown/runtime/weighted.hpp](../../../../../include/crown/runtime/weighted.hpp) |

## B0065

[Lines 629–632](../../../../../src/runtime/sql_rows.cpp#L629); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L629-L632:sha256:74516f290933db9f4ab14da88aa62fc76c1bd87cf03827d25218c8ac3cd97e79
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an explicit standalone execution cap. |
| inputs / outputs | Program/tree/options to runtime. |
| invariants | Creates one requested account then delegates to create_into. |
| ownership | Creates one requested MemoryAccount then delegates to create_into; the runtime facade and a later PreparedBatch can share the funded Data owner. |
| failure | Construction failures unwind account/member ownership. |
| cost | One account plus create_into’s accounted shared Data/control allocation, complete cold constructor costs, and later shared refcount operations; no second account/grant. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), include/crown/resource/ownership.hpp:60-74 |

## B0066

[Lines 633–638](../../../../../src/runtime/sql_rows.cpp#L633); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L633-L638:sha256:243f475135f397440af0b4d692137d8a85bf69b7d83f4e3c85372037b454e447
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct execution in the caller receiver. |
| inputs / outputs | Nonempty account/program/checked tree/options to runtime. |
| invariants | No new cap is created; existing residents consume the same limit. |
| ownership | One accounted combined shared Data/control allocation retains the SQL program, native state and source/key maps; active prepared tokens can share that owner. |
| failure | Empty account rejects fixed MemoryFailure before construction; RAII handles partial failure. |
| cost | One combined shared Data/control allocation plus complete cold constructor costs and later reference-count operations; compiler/source DTO work remains explicit. No new account or byte grant is created. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0067

[Lines 639–641](../../../../../src/runtime/sql_rows.cpp#L639); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L639-L641:sha256:4ab75c468d547f14f8eb1015cdaeab959939d3616c4713affbb1da26ba5fae84
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move a move-only SQL facade or release its retained shared-owner reference through defaulted special members. |
| inputs / outputs | Move construction/assignment and destruction of Data ownership. |
| invariants | Moves transfer only the facade shared_ptr; an active PreparedBatch can retain the old owner across facade move/assignment/destruction. No source/native state is cloned. |
| ownership | Shared Data reference moves. Replacing/destroying a facade releases its reference; last-token/last-facade release performs the actual Data cleanup. |
| failure | Declared noexcept. |
| cost | Move construction is constant; assignment/destruction may decrement shared refs and, if last, release source/key/native state and program metadata. An active token delays that cleanup. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), include/crown/runtime/sql_rows.hpp:129-132, src/runtime/sql_rows.cpp:247-273 |

## B0068

[Lines 642–645](../../../../../src/runtime/sql_rows.cpp#L642); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L642-L645:sha256:d00e7ee2f273cbcfec57a09fb4307f9e731a06b72b50149033ae33fdcb96ab5c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Access a live wrapper owner. |
| inputs / outputs | Facade to Data reference. |
| invariants | Moved-from facade cannot perform stateful access. |
| ownership | Returned reference borrows the facade’s shared Data owner for the synchronous call; an active PreparedBatch may hold an additional shared reference. |
| failure | Empty/moved-from facade throws invalid_sql_rows_runtime even if a separate token still retains the owner. |
| cost | Constant check/read. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), include/crown/runtime/sql_rows.hpp:131-133 |

## B0069

[Lines 646–646](../../../../../src/runtime/sql_rows.cpp#L646); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L646-L646:sha256:159733cd1d7e88f4a63f6d68ca6388fb681583431797d18544c80cfa2e8106c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow SQL schema/source binding. |
| inputs / outputs | Program reference. |
| invariants | Does not export or deep-copy metadata. |
| ownership | Scalar/descriptor read or synchronous Data delegation; no new account or ownership mirror. |
| failure | Moved-from facade rejects through data(). |
| cost | Constant wrapper work; delegated apply has its documented affected-state cost. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0070

[Lines 647–647](../../../../../src/runtime/sql_rows.cpp#L647); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L647-L647:sha256:37d6663eef77b5b19c4d0fa5dfbe05425da5b14666352fb4ece0153af9b0ee3c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect committed source epoch. |
| inputs / outputs | Sequence value. |
| invariants | Returns the committed native sequence, including filtered/no-op commits. While a batch is prepared it remains at the previous sequence; token.sequence() reports the proposed next one. |
| ownership | Scalar/descriptor read or synchronous Data delegation; no new account or ownership mirror. |
| failure | Moved-from facade rejects. |
| cost | Fixed owner validation and committed native sequence read; no apply delegation, allocation or work grant. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), src/runtime/sql_rows.cpp:514-515 |

## B0071

[Lines 648–648](../../../../../src/runtime/sql_rows.cpp#L648); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L648-L648:sha256:3da1b8605f8e0e73dc66ba3dcb13b943483184833a12c261d2b2238fff38cfcd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check reader/update exclusion. |
| inputs / outputs | Boolean. |
| invariants | Moved-from is false; active native readers and active PreparedBatch epochs both make the runtime not ready. One owner still requires serialized calls. |
| ownership | Scalar/descriptor read or synchronous Data delegation; no new account or ownership mirror. |
| failure | No expected failure for a factory-created live owner. |
| cost | Fixed shared-handle and native updating/reader-count checks; no apply delegation, allocation or grant. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), src/runtime/weighted.cpp:659-667 |

## B0072

[Lines 649–649](../../../../../src/runtime/sql_rows.cpp#L649); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L649-L649:sha256:fac21154b1a70cab4a2a76b3d0b6c13d5fd855e04a6bf917c2879b33bdd84f19
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect inner full-root multiplicity. |
| inputs / outputs | Exact native root weight. |
| invariants | Exact native full-root multiplicity before SQL DISTINCT/EXISTS, only readable outside a private prepared epoch; active token produces runtime_busy. |
| ownership | Scalar/descriptor read or synchronous Data delegation; no new account or ownership mirror. |
| failure | Moved-from facade rejects; native readable check rejects private batch state with runtime_busy. Existing reader leases permit the committed summary read. |
| cost | Fixed owner/readable checks and committed native root-summary read; no apply delegation or tuple allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), src/runtime/weighted.cpp:100-100, src/runtime/weighted.cpp:659-667 |

## B0073

[Lines 650–650](../../../../../src/runtime/sql_rows.cpp#L650); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L650-L650:sha256:9387c2b5bfbbfc15ac80c1a375fa8ebf7e2c9c179a0888909cd81be94b27ced8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect actual receiving-account counters. |
| inputs / outputs | Account statistics snapshot. |
| invariants | Returns actual receiver-account counters, including active token/proposal/native residents funded from that same account; it is account-wide, not wrapper-only. |
| ownership | Value snapshot; no new account or ownership mirror. |
| failure | Moved-from facade rejects. |
| cost | Constant wrapper/statistics read; reflects additional batch resident allocations without estimating them. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), src/runtime/sql_rows.cpp:477-477, include/crown/resource/ownership.hpp:60-74 |

## B0074

[Lines 651–651](../../../../../src/runtime/sql_rows.cpp#L651); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L651-L651:sha256:0dabbe2e0c1eeab2b21fe5c528d3f344c40fe5e0dcfeba0eb4c14c0353a48a69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward one synchronous physical replacement. |
| inputs / outputs | Update to Epoch. |
| invariants | Private Data preserves existing single-row immediate constraints, one source allowance per invocation, all-alias atomic publication; an active PreparedBatch makes native begin_epoch reject runtime_busy before SQL source changes. |
| ownership | Scalar/descriptor read or synchronous Data delegation; no new account or ownership mirror. |
| failure | Propagates the existing apply/resource/constraint failures; active pending batch is rejected at the native exclusivity boundary. |
| cost | Constant wrapper work; delegated apply has its documented affected-state cost. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), src/runtime/weighted.cpp:663-674 |

## B0075

[Lines 652–655](../../../../../src/runtime/sql_rows.cpp#L652); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L652-L655:sha256:97fecc127761fc17bf3cb6ca341803f2ebd27bde1b5f9e8f00bfc6a85363ffab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one committed full physical-row weight while respecting active native epoch exclusivity. |
| inputs / outputs | Source ID/full borrowed cells to exact committed count. |
| invariants | Calls native.root_weight/readable first: an active PreparedBatch rejects with runtime_busy, while committed readers remain allowed. Then validates the entire row and probes the committed ledger; no proposed weight is exposed. |
| ownership | Borrows caller cells/text through return; source validation uses no allowance and map probe creates no owning key. |
| failure | Moved-from, active private batch (runtime_busy), invalid source, arity or type/domain rejects before returning a count. |
| cost | One fixed native readable/root-summary guard plus full row-domain validation and logarithmic borrowed full-key map comparison; no runtime tuple/map allocation or new grant. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), src/runtime/weighted.cpp:100-100, src/runtime/weighted.cpp:659-667, src/runtime/sql_rows.cpp:112-124 |

## B0076

[Lines 656–686](../../../../../src/runtime/sql_rows.cpp#L656); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L656-L686:sha256:92b02253b31a30ac7707c2f5edca34aa3ef644de045c1e994d1d0ff140ad2211
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the current validated per-table source maps into an explicit bounded immutable-row image. |
| inputs / outputs | Checks native readiness, counts distinct rows against limits, copies the actual source/native handles, reserves the output vector, then appends (TableId, Tuple handle, weight) in table/map order and returns consumed work. |
| invariants | The first pass counts row entries, not multiplicity. The second pass includes every table and complete nullable cell, including filtered or SQL-unused tables. Each field is admitted; each string extent contributes size bytes without UTF8 rescan. Row handles share the source map’s owned tuple. |
| ownership | Reads the owner’s committed source maps; returned vector is charged to its MemoryAccount while copied row/program handles retain their immutable owners. No lease or mutation of source maps is performed. |
| failure | Not-ready owner raises sql_rows_busy; row cap raises sql_rows_source_limit; IndexWorkFailure and allocation errors propagate. A local partial image is destroyed, leaving sequence/maps unchanged. |
| cost | O(T+R+F) table/row/field traversal; row-count pass uses map size; one reserve for O(R) descriptors and shared Tuple handles, without string payload clone or weighted-row expansion. Work is selected admission accounting, not CPU or full allocator cost. |
| Design | [src/runtime/sql_rows.cpp](../../../../../src/runtime/sql_rows.cpp), [include/crown/runtime/sql_rows.hpp](../../../../../include/crown/runtime/sql_rows.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/unit/sql_source_snapshot_test.cpp](../../../../../tests/unit/sql_source_snapshot_test.cpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md) |

## B0077

[Lines 687–691](../../../../../src/runtime/sql_rows.cpp#L687); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L687-L691:sha256:c6f8eb8cf2f8f6165009c79945448a43ee6dfc8b335a48b03d1ea19394c33ab9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire a writer-excluding SQL reader. |
| inputs / outputs | Native cursor options to owning wrapper cursor. |
| invariants | Acquires native reader before wrapper publication and samples EXISTS while leased. A prepared native epoch rejects results with runtime_busy; an existing reader prevents prepare/apply. |
| ownership | Native reader/program/account and output buffer are retained independently of wrapper. |
| failure | An active prepared epoch is rejected by native exclusivity; failed wrapper allocation/construction releases the newly acquired native lease by RAII. |
| cost | Native startup plus funded cursor Data/output-width scratch; no whole-result copy. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md), src/runtime/weighted.cpp:663-674 |

## B0078

[Lines 692–697](../../../../../src/runtime/sql_rows.cpp#L692); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L692-L697:sha256:8e2b020204509dd462550858116c27e8c77daa6a873ad2cc24adebe25bb3902a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the native logical sequence and construct one accounted SQL PreparedBatch. |
| inputs / outputs | NetBatch and optional capture policy to active source/native proposal. |
| invariants | Calls begin_epoch exactly once, then passes the shared facade owner and transferred PendingEpoch into one unique token Data. If allocation or constructor preparation fails, pending RAII rollback closes native exclusivity. |
| ownership | Token Data retains data_; input spans remain synchronous borrows only. |
| failure | Invalid sequence/runtime busy, account, source-work, validation, constraint or native stage errors propagate with committed source/native sequence preserved. |
| cost | One shared_ptr copy/refcount operation plus token Data allocation; all entry proposals share one source allowance and native grant. Enabled capture adds native collector/walk cost. |
| Design | src/runtime/sql_rows.cpp:499, src/runtime/weighted.cpp:663-674, include/crown/resource/ownership.hpp:40-74 |

## B0079

[Lines 698–706](../../../../../src/runtime/sql_rows.cpp#L698); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L698-L706:sha256:1330a06ef098d287fa8bfa9c428ec84722b9ebaec773422fd7a32d478c275f8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a genuine SQL net batch and explicitly select only its correct SQL output capture policy before public return. |
| inputs / outputs | NetBatch and finite OutputLimits{rows,work} in; existing move-only PreparedBatch with SQL preview enabled out. |
| invariants | Bag chooses numeric capture, DISTINCT support capture, EXISTS disabled native capture plus root endpoint rendering. Existing prepare_batch defaults/native APIs and arithmetic/source constraints are unchanged. Final SQL change count must fit the supplied rows cap. |
| ownership | Call the existing real preparation; retain only fixed optional limits/counter in its original-account token. No second SQL result state or account is constructed. |
| failure | Any count admission failure destroys the local prepared token and invokes its existing RAII rollback; source sequence/weights remain committed. No new catch is needed. |
| cost | Existing native preparation/capture plus constant presentation selection/count admission; output decode work starts at zero and cannot refill per row. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0080

[Lines 707–707](../../../../../src/runtime/sql_rows.cpp#L707); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L707-L707:sha256:9723ea60c64bbe851382d74860a4e9544a7a039680d2079a4c8a423f70f877f4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt the fully constructed account-backed token Data. |
| inputs / outputs | One AccountedUnique&lt;Data&gt; to PreparedBatch facade. |
| invariants | Factory is private to SqlRowsRuntime; adoption performs no second preparation or source mutation. |
| ownership | Moves unique ownership of the token shell; token Data owns the shared SQL Data reference. |
| failure | Noexcept ownership transfer. |
| cost | Constant handle transfer; no new account or payload copy. |
| Design | src/runtime/sql_rows.cpp:505, include/crown/runtime/sql_rows.hpp:74-80, include/crown/resource/ownership.hpp:16-39 |

## B0081

[Lines 708–710](../../../../../src/runtime/sql_rows.cpp#L708); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L708-L710:sha256:1c3efedd4913115f544a26ee76ad9e765e1d44ecbc6aa467bfc509053c3bc76f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer or retire one PreparedBatch through its defaulted lifecycle operations. |
| inputs / outputs | Move construction/assignment or destruction of AccountedUnique&lt;Data&gt;. |
| invariants | Only one facade owns token Data. Replacing/destroying an active old token invokes Data rollback; the retained SQL owner stays alive until the token is closed/released. |
| ownership | Unique token pointer moves; source/key maps and native epoch remain in place. |
| failure | Declared noexcept; destructor path uses noexcept native rollback. |
| cost | Move construction is constant; assignment/destruction can roll back native undo and release O(T+K) proposals. |
| Design | src/runtime/sql_rows.cpp:506, src/runtime/sql_rows.cpp:505-508, include/crown/runtime/sql_rows.hpp:53-80 |

## B0082

[Lines 711–714](../../../../../src/runtime/sql_rows.cpp#L711); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L711-L714:sha256:a5e55acf3a011ce8b69db18f78c4255aadf24c4665cc6dbd7f14f4e3312d1921
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Gate every stateful token accessor on a live, active preparation. |
| inputs / outputs | PreparedBatch facade to private Data reference. |
| invariants | Moved-from, committed, or rolled-back token rejects before owner/native preview dereference. |
| ownership | Returned reference borrows unique token Data and is used synchronously. |
| failure | Throws invalid_sql_rows_batch for empty/inactive token. |
| cost | Constant pointer and active-state checks. |
| Design | src/runtime/sql_rows.cpp:509, src/runtime/sql_rows.cpp:509-512 |

## B0083

[Lines 715–715](../../../../../src/runtime/sql_rows.cpp#L715); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L715-L715:sha256:db90554a9a215efc18f8f557d08950fe4739936372144e5593dba713e972908e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect whether a token still owns an active SQL/native decision. |
| inputs / outputs | Returns pointer-present and Data::active. |
| invariants | False after move, commit, or rollback; does not say that source state was changed. |
| ownership | No reference or owner copy escapes. |
| failure | Noexcept. |
| cost | Constant state checks. |
| Design | src/runtime/sql_rows.cpp:513, src/runtime/sql_rows.cpp:513-513 |

## B0084

[Lines 716–716](../../../../../src/runtime/sql_rows.cpp#L716); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L716-L716:sha256:725f0fd83332b798305733405eced97210907d1adc5fcae2c49874a2848dfbfb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the sequence that this prepared token would commit. |
| inputs / outputs | Returns PendingEpoch preview sequence. |
| invariants | This is the proposed next sequence; SqlRowsRuntime::sequence() remains the prior committed value until commit. |
| ownership | Scalar snapshot borrowed from no external storage. |
| failure | Closed/moved token rejects through data(). |
| cost | Constant preview access; no source work or allocation. |
| Design | src/runtime/sql_rows.cpp:514, src/runtime/sql_rows.cpp:514-514, src/runtime/weighted.cpp:721-721 |

## B0085

[Lines 717–717](../../../../../src/runtime/sql_rows.cpp#L717); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L717-L717:sha256:112746aef87f1bb6faf81c9278ded60c4cc3de93394b19b4b3525bc1391e40c2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the genuine normalized physical-source batch changed flag for outer preview. |
| inputs / outputs | Active PreparedBatch -&gt; existing Data::changed bool. |
| invariants | Includes filtered/unused physical changes; expected chains were normalized by genuine source preparation; no extra mirror or source mutation. |
| ownership | Reads private retained source Data only. |
| failure | Existing data() rejects closed/moved token before access. |
| cost | O(1), no allocation on valid access. |
| Design | src/runtime/sql_rows.cpp:274, src/runtime/sql_rows.cpp:299, src/runtime/sql_rows.cpp:515, [build/verification/w06-sql-aggregate-runtime-design-v1/design.md](../../../../../build/verification/w06-sql-aggregate-runtime-design-v1/design.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0086

[Lines 718–718](../../../../../src/runtime/sql_rows.cpp#L718); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L718-L718:sha256:72483461489e0df5c6feaca6c6e41aaa5db163b096c4306250c09ea83ac456c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable compiler-bound SQL metadata while the token is active. |
| inputs / outputs | Returns const SqlRowsProgram reference retained by the SQL owner. |
| invariants | Does not create an export/clone or confer source/proof mutation authority; rvalue accessor is deleted. |
| ownership | Reference lifetime is bounded by active token lifetime; shared owner keeps program alive after facade move/destruction. |
| failure | Closed/moved token rejects through data(). |
| cost | Constant reference access; no new account or work grant. |
| Design | src/runtime/sql_rows.cpp:515, include/crown/runtime/sql_rows.hpp:62-64, src/runtime/sql_rows.cpp:515-515 |

## B0087

[Lines 719–721](../../../../../src/runtime/sql_rows.cpp#L719); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L719-L721:sha256:88dbbffaf8da0b044505c4d5bb3159fab9b971317ee70c93ca7e7b5b29588019
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a value snapshot of source-work already spent by the whole batch. |
| inputs / outputs | Computes configured source limit minus the token’s remaining allowance. |
| invariants | Never returns/refills/copies a mutable allowance. All edits, row/key probes, constraint checks and aliases share this one allowance. |
| ownership | Value contains five scalar domains; allowance stays owned by Data. |
| failure | Closed/moved token rejects; no new debit occurs while sampling. |
| cost | Five scalar subtractions; it does not measure every map comparison, elapsed time, or allocator bytes. |
| Design | src/runtime/sql_rows.cpp:516, src/runtime/sql_rows.cpp:516-518, include/crown/storage/index_work.hpp:10-45 |

## B0088

[Lines 722–722](../../../../../src/runtime/sql_rows.cpp#L722); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L722-L722:sha256:26a859dc7f84fee32bd4c6f03ad7b074a9e1168b329e33a6ff04f44f8d213b04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the prepared native weighted epoch result before SQL wrapper presentation. |
| inputs / outputs | Returns PendingEpoch preview by const reference. |
| invariants | Describes native core/full-root sequence and metrics, not a SQL DISTINCT/EXISTS transformed result or aggregate proposal; rvalue access is deleted. |
| ownership | Reference borrows active token and expires at commit/rollback/destruction. |
| failure | Closed/moved token rejects through data(). |
| cost | Constant read of already prepared output; no additional native traversal or capture. |
| Design | src/runtime/sql_rows.cpp:519, include/crown/runtime/sql_rows.hpp:66-67, src/runtime/sql_rows.cpp:519-519, include/crown/runtime/weighted.hpp:228-249, src/runtime/sql_rows.cpp:440-461, include/crown/runtime/weighted.hpp:118-125 |

## B0089

[Lines 723–725](../../../../../src/runtime/sql_rows.cpp#L723); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L723-L725:sha256:9de32a80886e24e0e0a3772952f54afcd81e19d13cf2cf395bcb7feedcbf5cca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow optional encoded native core bag facts for the active prepared epoch. |
| inputs / outputs | Returns nullopt when capture is disabled, otherwise a span of signed weighted BagDelta records. |
| invariants | Facts encode the weighted native output before SQL DISTINCT/EXISTS. They do not represent SQL result deltas, aggregate contributions, source authority, or a proof token; an enabled empty span means no net native fact. |
| ownership | Tuple facts are native-owned; returned span borrows PendingEpoch and token through close. Rvalue accessor is deleted. |
| failure | Closed/moved token rejects. Capture failures occurred during preparation and prevent a token from escaping. |
| cost | Disabled path adds no collector; enabled path retains native BagDeltas/DeltaWalk map/vector and weighted walk/query-shape/factor/row/output costs under the existing native policy/grant. |
| Design | src/runtime/sql_rows.cpp:520, include/crown/runtime/sql_rows.hpp:68-71, src/runtime/weighted.cpp:254-267, src/runtime/weighted.cpp:709-718, src/runtime/weighted.cpp:710-719, src/runtime/sql_rows.cpp:440-461, include/crown/runtime/weighted.hpp:118-125 |

## B0090

[Lines 726–726](../../../../../src/runtime/sql_rows.cpp#L726); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L726-L726:sha256:559115f0012ae4dde8d2d099be23ae3acfb790298cbc01af282eea9dc61574ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward the SQL-presented output count query to the active token data. |
| inputs / outputs | This PreparedBatch -&gt; data().output_size(): nullopt for native-only preparation or the retained presentation count. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Returns a copied optional count; retains and exports no row storage. |
| failure | The existing active-token guard in data() rejects an empty or closed token. |
| cost | O(1) guard and delegated mode/span/root-presence reads; no tuple decode or allocation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0091

[Lines 727–729](../../../../../src/runtime/sql_rows.cpp#L727); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L727-L729:sha256:a6c79157b4ab56baa1f90d942dd0737860552a0c1e0812a1834c218923b02c67
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one correctly presented SQL tuple change through exact-width caller scratch under the single retained decode allowance. |
| inputs / outputs | Admitted output index and scratch width equal to program.outputs().size() in; nullable ordered cells plus exact signed uint64 magnitude out. |
| invariants | Every call spends one row plus one field unit per output, across all codec passes. Bag preserves numeric magnitude; DISTINCT preserves unit support; EXISTS returns -oldBoolean then +newBoolean. Payload/presence/constants mapping is the genuine injective SQL output mapping. |
| ownership | The returned cells borrow caller scratch and live token program/native payloads. Reuse/close invalidates the view; no output tuple vector, string copy, snapshot or persistent graph is created. |
| failure | Disabled/wrong-index/wrong-width/work-limit errors occur before scratch mutation; budget failure leaves the active unpublished token for caller rollback. No catch/refill/fallback is added. |
| cost | Selected 1+width decode work per call, O(width) scalar descriptors and O(1) per string descriptor. Serialized byte visits/canonical sorting remain separately bounded codec work. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0092

[Lines 730–730](../../../../../src/runtime/sql_rows.cpp#L730); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L730-L730:sha256:07b1c7ea45b9d9532767274f877698b4ce2fda8341e84da7f6753c81a0ff67a6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read cumulative selected SQL output decode work. |
| inputs / outputs | This active PreparedBatch -&gt; data().output_spent as uint64; native-only preparation leaves it zero. |
| invariants | Returns the named retained value; this accessor performs no preparation, publication or revalidation. |
| ownership | Returns a scalar; no output borrow or new owner. |
| failure | The existing active-token guard in data() rejects an empty or closed token. |
| cost | O(1) field/view read; no allocation, decode, scan or grant refill. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06](../../../../../Refactor.md) |

## B0093

[Lines 731–733](../../../../../src/runtime/sql_rows.cpp#L731); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L731-L733:sha256:3f7d95ddbc321267cbdbf90b1740803a01d58f0d1fc3ea8bc997d04dd7c69f69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Commit the active token and return one source/native Epoch. |
| inputs / outputs | No arguments to one Epoch result. |
| invariants | Calls Data::commit to cross the native decision and publish the prepared source/key state, then resets data_ before returning the already owning Epoch. Borrowed program/native-preview references and bag spans expire at this close. |
| ownership | Returned Epoch owns native output/journal/captured facts. data_.reset destroys PreparedBatch::Data and its embedded PendingEpoch immediately after success; if the facade had moved/died, this also releases its retained SQL owner. The AccountedUnique deleter still carries its fixed allocator/account handle while the empty wrapper lives. |
| failure | Inactive access rejects through data(). Preparation failures occurred before token return. If Data::commit throws before completion, reset is not reached and later token destruction still rolls back the active Data. |
| cost | Prepared publication/cleanup is O(T+K); after successful native commit, reset deallocates token and native pending workspace/capacity immediately. No post-decision source allocation is added. |
| Design | src/runtime/sql_rows.cpp:523, src/runtime/sql_rows.cpp:523-523, src/runtime/sql_rows.cpp:409-415 |

## B0094

[Lines 734–734](../../../../../src/runtime/sql_rows.cpp#L734); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L734-L734:sha256:12b0cd1dbeab6a25398b6aec49ef981c875b2c5b9f2d9244480cafe444dd263a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the prepared decision without publishing SQL source/key counters. |
| inputs / outputs | No arguments; forwards rollback when token Data exists. |
| invariants | Resetting data_ is idempotent: destruction invokes Data::~Data, which runs its noexcept rollback while active; after reset active is false and stateful access rejects. |
| ownership | The token Data destructor rolls back native state, clears proposals and releases the shared SQL owner; resetting AccountedUnique then destroys native PendingEpoch Data and its retained workspace. Only the empty unique_ptr deleter’s fixed allocator/account handle remains with the facade. |
| failure | Noexcept destructor-driven rollback; no exception translation or retry handler. |
| cost | Immediate native inverse, proposal destruction and account deallocation for the actually staged/touched state; no SQL source scan. No native workspace capacity remains through the closed token. |
| Design | src/runtime/sql_rows.cpp:524, src/runtime/sql_rows.cpp:524-524, src/runtime/sql_rows.cpp:416-421 |

## B0096

[Lines 736–736](../../../../../src/runtime/sql_rows.cpp#L736); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L736-L736:sha256:3265901ce0edabdc46cfab46abb693297676715ef6f4dc9cb22aa2361e22e99d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a fully funded SQL reader. |
| inputs / outputs | Private unique Data to cursor. |
| invariants | No additional admission or account. |
| ownership | Moves exclusive cursor Data. |
| failure | Noexcept. |
| cost | Constant ownership transfer. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0097

[Lines 737–739](../../../../../src/runtime/sql_rows.cpp#L737); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L737-L739:sha256:6ed7c11e7a72742b0d5f509558f91feb029bf27f556713f073e33927c527c5d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer or retire a SQL cursor through defaulted special members. |
| inputs / outputs | Move construction/assignment and destruction of cursor Data. |
| invariants | Only one cursor facade owns this Data; replacing/destroying it closes the old native reader. |
| ownership | Moves unique cursor ownership; owning emitted rows/schema remain independent. |
| failure | Declared noexcept. |
| cost | Move construction is constant; old-cursor cleanup can traverse open native frames and release output/program ownership. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0098

[Lines 740–743](../../../../../src/runtime/sql_rows.cpp#L740); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L740-L743:sha256:b56d0f702fc0f3c66453392b85d648e9164d4b3693db5a71922d6f968d63cebc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read cursor state through a live handle. |
| inputs / outputs | Cursor facade to Data reference. |
| invariants | Moved-from stateful methods reject. |
| ownership | Borrowed internal reference. |
| failure | Empty cursor throws invalid_cursor. |
| cost | Constant check/read. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0099

[Lines 744–744](../../../../../src/runtime/sql_rows.cpp#L744); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L744-L744:sha256:8bbd91b9d06d56ea057e31fcbf10ed4758e78dd96afdd5654c7843931d9e87dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect whether this cursor can advance. |
| inputs / outputs | Boolean. |
| invariants | Moved-from and terminal cursors are false. |
| ownership | Uses existing unique cursor/native/program ownership; does not clone it. |
| failure | Noexcept. |
| cost | Constant state read. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0100

[Lines 745–745](../../../../../src/runtime/sql_rows.cpp#L745); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L745-L745:sha256:4039fe7e429651b0c95cb38dc7e4242f2f0e6f10c78eb8155c2bc750bebe8120
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect public cursor terminal state. |
| inputs / outputs | Active/exhausted/cancelled/failed value. |
| invariants | A failed output copy stays failed. |
| ownership | Uses existing unique cursor/native/program ownership; does not clone it. |
| failure | Moved-from cursor rejects. |
| cost | Constant state read. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0101

[Lines 746–746](../../../../../src/runtime/sql_rows.cpp#L746); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L746-L746:sha256:cb95eb780ee1bb21b5a7411dc01270a4acda1d9dcfaf0d5496d9c532351e23af
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect captured reader epoch. |
| inputs / outputs | Native sequence. |
| invariants | Reader pins that epoch independently of later wrapper lifetime. |
| ownership | Uses existing unique cursor/native/program ownership; does not clone it. |
| failure | Moved-from cursor rejects. |
| cost | Constant native getter. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0102

[Lines 747–747](../../../../../src/runtime/sql_rows.cpp#L747); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L747-L747:sha256:2656ac43887f202f9b7e404accf983edca8d7a69c399deded0f3d62fca8c0b22
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance the SQL reader once. |
| inputs / outputs | Owning SQL result or terminal absence. |
| invariants | All decoding/lifetime/failure policy lives in Data::next. |
| ownership | Uses existing unique cursor/native/program ownership; does not clone it. |
| failure | Propagates the original Data::next failure. |
| cost | Constant forwarding plus documented cursor/output costs. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0103

[Lines 748–750](../../../../../src/runtime/sql_rows.cpp#L748); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L748-L750:sha256:b5547e1583cf6fa635d49e7812fa4469f6c9aa6616b51c96b2e6800cb17dfec9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release an active native reader idempotently. |
| inputs / outputs | Cursor to cancelled state. |
| invariants | Moved-from/terminal cursor is a no-op; active cancellation excludes later output. |
| ownership | Uses existing unique cursor/native/program ownership; does not clone it. |
| failure | Noexcept. |
| cost | Native frame/lease cleanup plus state write; no output copy. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows.md](../../../../sql_rows.md), [Refactor.md §W05](../../../../../Refactor.md) |

## B0104

[Lines 751–751](../../../../../src/runtime/sql_rows.cpp#L751); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L751-L751:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in src/runtime/sql_rows.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
