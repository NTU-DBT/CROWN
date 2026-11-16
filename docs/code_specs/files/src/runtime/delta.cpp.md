# `src/runtime/delta.cpp` — block usage map

[Source](../../../../../src/runtime/delta.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain live visible-factor indexes, canonical delta producers and retained delivery epochs.

Snapshot SHA-256: `ee82f62530b87577db545f674448bd3370fe2f758211e45faa682b376f926d0c`. 1915 lines partitioned into 219 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [delta](../../../subsystem_contracts.md#delta). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/delta_transition_spec.md](../../../../delta_transition_spec.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/anchored_delta.md](../../../../anchored_delta.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–26](../../../../../src/runtime/delta.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Node IDs are valid vector positions; UINT64_MAX is reserved for coordinator · [reviewed contract](#b0001) |
| [B0002 · 27–29](../../../../../src/runtime/delta.cpp#L27) | Callable definition: void require(bool condition,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 30–32](../../../../../src/runtime/delta.cpp#L30) | Callable definition: template&lt;class Failure&gt; \[\[noreturn\]\] void delta_present(const Failure& failure) | calls Error, std::string, code, what · [reviewed contract](#b0003) |
| [B0004 · 33–36](../../../../../src/runtime/delta.cpp#L33) | Callable definition: std::size_t add_size(std::size_t left,std::size_t right) | calls require, max; guard require(right&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-left,"resource_limit","delta size accounting…; returns left+right · [reviewed contract](#b0004) |
| [B0005 · 37–40](../../../../../src/runtime/delta.cpp#L37) | Callable definition: std::size_t slots_size(std::size_t count,std::size_t width) | calls require, max; guard require(count&lt;=std::numeric_limits&lt;std::size_t&gt;::max()/width,"resource_limit","delta slot accountin…; returns count*width · [reviewed contract](#b0005) |
| [B0006 · 41–60](../../../../../src/runtime/delta.cpp#L41) | Type/record definition: struct PhaseTimer | source comment (unverified): // No clock expression is evaluated in off/counters. · [reviewed contract](#b0006) |
| [B0007 · 61–63](../../../../../src/runtime/delta.cpp#L61) | declares types or opens a type body. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 64–74](../../../../../src/runtime/delta.cpp#L64) | Type/record definition: struct Factor |  · [reviewed contract](#b0008) |
| [B0009 · 75–82](../../../../../src/runtime/delta.cpp#L75) | Type/record definition: struct LiveParentSupport |  · [reviewed contract](#b0009) |
| [B0010 · 83–84](../../../../../src/runtime/delta.cpp#L83) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0010) |
| [B0011 · 85–102](../../../../../src/runtime/delta.cpp#L85) | Type/record definition: struct LiveImage | growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0011) |
| [B0012 · 103–107](../../../../../src/runtime/delta.cpp#L103) | Type/record definition: struct ProductiveQueue |  · [reviewed contract](#b0012) |
| [B0013 · 108–129](../../../../../src/runtime/delta.cpp#L108) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 130–131](../../../../../src/runtime/delta.cpp#L130) | Callable definition: template&lt;class Source&gt; Impl(Source plan,DeltaOptions value,std::shared_ptr&lt;detail::StorageWorkContext&gt; context) :Impl(PhysicalRun… | calls PhysicalRuntime, std::move · [reviewed contract](#b0014) |
| [B0015 · 132–174](../../../../../src/runtime/delta.cpp#L132) | Callable definition: Impl(PhysicalRuntime owner,DeltaOptions value) :options(value),physical(std::move(owner)),observation(physical.observation_state(… | calls options, physical, std::move, observation; guard require(options.mode==DeltaMode::maintenance \|\| options.mode==DeltaMode::delta,"invalid_options","u…; returns output.variable==variable; growth push_back, reserve, resize; 3 loop sites · [reviewed contract](#b0015) |
| [B0016 · 175–177](../../../../../src/runtime/delta.cpp#L175) | Explanatory comments or spacing. | source comment (unverified): // Called only after successful construction or a semantic mode switch. · [reviewed contract](#b0016) |
| [B0017 · 178–195](../../../../../src/runtime/delta.cpp#L178) | Callable definition: void observe_configuration(bool initial=false) noexcept | calls modes, sequence, configuration, generation; source comment (unverified): // Called only after successful construction or a semantic mode switch. · [reviewed contract](#b0017) |
| [B0018 · 196–196](../../../../../src/runtime/delta.cpp#L196) | Callable definition: void readable() const | calls require; guard void readable() const { require(!processing,"runtime_busy","delta epoch preparation is active"); } · [reviewed contract](#b0018) |
| [B0019 · 197–199](../../../../../src/runtime/delta.cpp#L197) | Callable definition: void writable() const | calls readable, require, ready; guard readable(); require(!output_active && physical.ready(),"runtime_busy","query readers or committed d… · [reviewed contract](#b0019) |
| [B0020 · 200–206](../../../../../src/runtime/delta.cpp#L200) | Callable definition: void charge(DeltaMetrics& metrics,std::uint64_t amount=1) const | calls require, max; guard require(amount&lt;=std::numeric_limits&lt;std::uint64_t&gt;::max()-used && · [reviewed contract](#b0020) |
| [B0021 · 207–209](../../../../../src/runtime/delta.cpp#L207) | Callable definition: void metric(DeltaMetrics& metrics,std::uint64_t& counter,std::uint64_t amount=1) const | calls charge · [reviewed contract](#b0021) |
| [B0022 · 210–210](../../../../../src/runtime/delta.cpp#L210) | Callable definition: const resource::MemoryAccount& memory() const noexcept | calls plan, account; returns physical.plan().account() · [reviewed contract](#b0022) |
| [B0023 · 211–217](../../../../../src/runtime/delta.cpp#L211) | Callable definition: RowSets row_sets(std::size_t count,resource::MemoryPurpose purpose=resource::MemoryPurpose::delta_state, resource::AllocationLife… | calls result, memory, reserve, emplace_back; returns result; growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0023) |
| [B0024 · 218–218](../../../../../src/runtime/delta.cpp#L218) | Callable definition: static storage::ScalarView scalar(const Row& row,std::size_t field) | calls storage::borrow_scalar, at; returns storage::borrow_scalar(row.at(field)) · [reviewed contract](#b0024) |
| [B0025 · 219–219](../../../../../src/runtime/delta.cpp#L219) | Callable definition: static storage::ScalarView scalar(storage::RowView row,std::size_t field) | calls at; returns row.at(field) · [reviewed contract](#b0025) |
| [B0026 · 220–220](../../../../../src/runtime/delta.cpp#L220) | Callable definition: static storage::ScalarView scalar(const storage::AccountedRow& row,std::size_t field) | calls view, at; returns row.view().at(field) · [reviewed contract](#b0026) |
| [B0027 · 221–227](../../../../../src/runtime/delta.cpp#L221) | Callable definition: template&lt;class Source&gt; storage::AccountedRow project(const Source& row,std::span&lt;const std::size_t&gt; fields,DeltaMetrics& metrics,… | calls result, memory, reserve, size; returns storage::AccountedRow::copy_of(memory(),storage::RowView::borrow(result),delta_metadata); growth copy_of, push_back, reserve; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 228–230](../../../../../src/runtime/delta.cpp#L228) | Callable definition: void cursor_start(const SupportRuntime::ResultCursor& cursor,DeltaMetrics& metrics) const | calls metric, metrics · [reviewed contract](#b0028) |
| [B0029 · 231–235](../../../../../src/runtime/delta.cpp#L231) | Callable definition: std::optional&lt;storage::AccountedTuple&gt; cursor_next(SupportRuntime::ResultCursor& cursor,DeltaMetrics& metrics) const | calls next_native, metric, metrics; returns row · [reviewed contract](#b0029) |
| [B0030 · 236–278](../../../../../src/runtime/delta.cpp#L236) | Callable definition: std::shared_ptr&lt;LiveImage&gt; build_live(const SupportRuntime::EpochView& view,DeltaMetrics& metrics,std::size_t retained, std::size… | calls memory, std::max, size, metric; guard require(count.value!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"support_overflow","live-parent sepa…; returns result; growth insert, make_accounted_shared; 3 loop sites · [reviewed contract](#b0030) |
| [B0031 · 279–282](../../../../../src/runtime/delta.cpp#L279) | Callable definition: bool scalar_sql() const | calls plan, normalized; returns options.view==ResultView::sql && normalized && normalized-&gt;binding.wrapper==frontend::SqlWrapper::e… · [reviewed contract](#b0031) |
| [B0032 · 283–298](../../../../../src/runtime/delta.cpp#L283) | Callable definition: storage::Tuple map_result(storage::AccountedTuple core,DeltaMetrics& metrics) const | calls plan, normalized, metric, values; returns storage::Tuple::from_accounted(std::move(core)); storage::Tuple::from_accounted(physical.plan().sql…; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 299–303](../../../../../src/runtime/delta.cpp#L299) | Callable definition: storage::Tuple scalar_result(bool answer) const | calls storage::Tuple::from_accounted, plan, sql_result_layout, tuple; returns storage::Tuple::from_accounted(physical.plan().sql_result_layout().tuple( · [reviewed contract](#b0033) |
| [B0034 · 304–306](../../../../../src/runtime/delta.cpp#L304) | declares types or opens a type body. |  · [reviewed contract](#b0034) |
| [B0035 · 307–307](../../../../../src/runtime/delta.cpp#L307) | Type/record definition: enum class Kind |  · [reviewed contract](#b0035) |
| [B0036 · 308–322](../../../../../src/runtime/delta.cpp#L308) | Type/record definition: struct Undo |  · [reviewed contract](#b0036) |
| [B0037 · 323–323](../../../../../src/runtime/delta.cpp#L323) | Type/record definition: struct Event |  · [reviewed contract](#b0037) |
| [B0038 · 324–333](../../../../../src/runtime/delta.cpp#L324) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0038) |
| [B0039 · 334–342](../../../../../src/runtime/delta.cpp#L334) | Callable definition: LiveTransaction(const Impl& owner,DeltaMetrics& work,std::shared_ptr&lt;LiveImage&gt; state) :runtime(owner),metrics(work),image(std::m… | calls runtime, metrics, image, std::move; growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0039) |
| [B0040 · 343–343](../../../../../src/runtime/delta.cpp#L343) | Callable definition: ~LiveTransaction() | calls rollback · [reviewed contract](#b0040) |
| [B0041 · 344–351](../../../../../src/runtime/delta.cpp#L344) | Callable definition: resource::AccountedUnique&lt;Undo&gt; prepare(Kind kind,std::size_t factor,bool child_side=false) | calls metric, memory; returns item; growth make_accounted_unique · [reviewed contract](#b0041) |
| [B0042 · 352–354](../../../../../src/runtime/delta.cpp#L352) | Callable definition: void record(resource::AccountedUnique&lt;Undo&gt; item) noexcept | calls std::move · [reviewed contract](#b0042) |
| [B0043 · 355–355](../../../../../src/runtime/delta.cpp#L355) | Callable definition: void prepare_commit() | calls metric · [reviewed contract](#b0043) |
| [B0044 · 356–363](../../../../../src/runtime/delta.cpp#L356) | Callable definition: void peak() | calls std::max, add_size · [reviewed contract](#b0044) |
| [B0045 · 364–395](../../../../../src/runtime/delta.cpp#L364) | Callable definition: void rollback() noexcept | calls clear, std::move, std::terminate, erase; growth insert; 1 loop sites · [reviewed contract](#b0045) |
| [B0046 · 396–403](../../../../../src/runtime/delta.cpp#L396) | Callable definition: void commit() noexcept | calls std::move, std::terminate, clear; 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 404–444](../../../../../src/runtime/delta.cpp#L404) | Callable definition: template&lt;class Source&gt; void change(std::size_t factor,const Source& key,bool add,RowSets& removed,ProductiveQueue* productive=nul… | calls metric, find, end, add_size; guard require(fresh,"runtime_contract","live key insertion duplicated membership");; growth insert, push_back · [reviewed contract](#b0047) |
| [B0048 · 445–499](../../../../../src/runtime/delta.cpp#L445) | Callable definition: template&lt;class ParentRow&gt; bool separator(std::size_t child,const storage::AccountedRow& key,const ParentRow& parent_row,bool add,… | calls find, end, require, max; guard if (add) require(before!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"support_overflow","live-parent …; returns false; true; growth insert; source comment (unverified): // Own the outer insertion before the inner row copy can throw. · [reviewed contract](#b0048) |
| [B0049 · 500–507](../../../../../src/runtime/delta.cpp#L500) | Callable definition: void end_stage() | calls metric, size, clear, peak; 1 loop sites · [reviewed contract](#b0049) |
| [B0050 · 508–511](../../../../../src/runtime/delta.cpp#L508) | Callable definition: void begin_stage() | calls end_stage, clear, peak · [reviewed contract](#b0050) |
| [B0051 · 512–538](../../../../../src/runtime/delta.cpp#L512) | Callable definition: void apply(const RowSets& changed,const SupportRuntime::EpochView& context, bool add,RowSets& removed) | calls begin_stage, size, project, metric; 5 loop sites; source comment (unverified): // Copy the pointer record: appending child events may move the vector. · [reviewed contract](#b0051) |
| [B0052 · 539–566](../../../../../src/runtime/delta.cpp#L539) | Callable definition: void on_output(storage::RowView row,const RowSets& changed,bool add,RowSets& removed, std::optional&lt;std::size_t&gt; anchor={},Produc… | calls size, project, metric, contains; 3 loop sites; source comment (unverified): // Parent support changes must precede the descendant projection in this · [reviewed contract](#b0052) |
| [B0053 · 567–571](../../../../../src/runtime/delta.cpp#L567) | declares types or opens a type body. | source comment (unverified): // A delta-only full-key cursor; partial/hidden D02 completion is separate. · [reviewed contract](#b0053) |
| [B0054 · 572–572](../../../../../src/runtime/delta.cpp#L572) | Type/record definition: struct Step |  · [reviewed contract](#b0054) |
| [B0055 · 573–578](../../../../../src/runtime/delta.cpp#L573) | Type/record definition: struct Frame |  · [reviewed contract](#b0055) |
| [B0056 · 579–592](../../../../../src/runtime/delta.cpp#L579) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0056) |
| [B0057 · 593–598](../../../../../src/runtime/delta.cpp#L593) | Callable definition: void note(std::uint64_t& counter,std::uint64_t amount=1) | calls require, max, metric; guard require(amount&lt;=std::numeric_limits&lt;std::uint64_t&gt;::max()-work && · [reviewed contract](#b0057) |
| [B0058 · 599–604](../../../../../src/runtime/delta.cpp#L599) | Callable definition: storage::AccountedRow project(storage::RowView row,std::span&lt;const std::size_t&gt; fields) | calls result, memory, reserve, size; returns storage::AccountedRow::copy_of(runtime.memory(),storage::RowView::borrow(result),delta_metadata); growth copy_of, push_back, reserve; 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 605–608](../../../../../src/runtime/delta.cpp#L605) | Callable definition: const storage::AccountedLayout& layout(std::size_t factor) const | calls plan, relations, nodes; returns plan.relations()\[plan.nodes()\[runtime.factors\[factor\].node.value\].visible_relation-&gt;value\].layout · [reviewed contract](#b0059) |
| [B0060 · 609–644](../../../../../src/runtime/delta.cpp#L609) | Callable definition: AnchoredCursor(const Impl& owner,const SupportRuntime::EpochView& view,const LiveImage& state, const RemovedParents* restored,Del… | calls runtime, target, image, removed; guard require(steps.size()==size,"runtime_contract","anchored program does not cover C*");; growth push_back, reserve, resize; 4 loop sites · [reviewed contract](#b0060) |
| [B0061 · 645–667](../../../../../src/runtime/delta.cpp#L645) | Callable definition: std::optional&lt;storage::AccountedTuple&gt; indexed_next(const Step& step,Frame& frame,bool child_side) | calls note, find, end, upper_bound; returns {}; layout(step.factor).tuple(selected-&gt;view()); 1 loop sites · [reviewed contract](#b0061) |
| [B0062 · 668–686](../../../../../src/runtime/delta.cpp#L668) | Callable definition: std::optional&lt;storage::AccountedTuple&gt; select(std::size_t index) | calls note, project, values, emplace; returns indexed_next(step,frame,live_child); {}; growth emplace · [reviewed contract](#b0062) |
| [B0063 · 687–714](../../../../../src/runtime/delta.cpp#L687) | Callable definition: std::optional&lt;storage::AccountedTuple&gt; next() | calls note, size, output, memory; guard require(!first \|\| row.has_value(),"runtime_contract","live anchored factor has an empty first bucke…; returns {}; result; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0063) |
| [B0064 · 715–718](../../../../../src/runtime/delta.cpp#L715) | declares types or opens a type body. |  · [reviewed contract](#b0064) |
| [B0065 · 719–723](../../../../../src/runtime/delta.cpp#L719) | Type/record definition: struct Node |  · [reviewed contract](#b0065) |
| [B0066 · 724–727](../../../../../src/runtime/delta.cpp#L724) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0066) |
| [B0067 · 728–729](../../../../../src/runtime/delta.cpp#L728) | Callable definition: explicit Spool(const resource::MemoryAccount& account) :allocator(account,resource::MemoryPurpose::output_buffer,{resource::Memor… | calls allocator · [reviewed contract](#b0067) |
| [B0068 · 730–731](../../../../../src/runtime/delta.cpp#L730) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0068) |
| [B0069 · 732–732](../../../../../src/runtime/delta.cpp#L732) | Callable definition: ~Spool() | calls clear · [reviewed contract](#b0069) |
| [B0070 · 733–733](../../../../../src/runtime/delta.cpp#L733) | Callable definition: \[\[nodiscard\]\] std::size_t size() const noexcept | calls ; returns count · [reviewed contract](#b0070) |
| [B0071 · 734–734](../../../../../src/runtime/delta.cpp#L734) | Callable definition: \[\[nodiscard\]\] bool empty() const noexcept | calls ; returns count==0 · [reviewed contract](#b0071) |
| [B0072 · 735–735](../../../../../src/runtime/delta.cpp#L735) | Callable definition: SignedResult& front() noexcept | calls ; returns head-&gt;value · [reviewed contract](#b0072) |
| [B0073 · 736–743](../../../../../src/runtime/delta.cpp#L736) | Callable definition: void push_back(SignedResult value) | calls allocate, static_assert, std::construct_at, std::move; guard static_assert(std::is_nothrow_constructible_v&lt;Node,SignedResult&gt;);; growth allocate, push_back; source comment (unverified): // SignedResult transfers an already prepared owning row without throwing. · [reviewed contract](#b0073) |
| [B0074 · 744–747](../../../../../src/runtime/delta.cpp#L744) | Callable definition: void pop_front() noexcept | calls std::destroy_at, deallocate · [reviewed contract](#b0074) |
| [B0075 · 748–748](../../../../../src/runtime/delta.cpp#L748) | Callable definition: void clear() noexcept | calls pop_front; 1 loop sites · [reviewed contract](#b0075) |
| [B0076 · 749–763](../../../../../src/runtime/delta.cpp#L749) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0076) |
| [B0077 · 764–766](../../../../../src/runtime/delta.cpp#L764) | Callable definition: void observe_output() noexcept | calls output · [reviewed contract](#b0077) |
| [B0078 · 767–770](../../../../../src/runtime/delta.cpp#L767) | Callable definition: explicit Data(std::shared_ptr&lt;Impl&gt; runtime):owner(std::move(runtime)),observation(owner-&gt;observation),layout(owner-&gt;output_layou… | calls owner, std::move, observation, layout; growth reserve · [reviewed contract](#b0078) |
| [B0079 · 771–771](../../../../../src/runtime/delta.cpp#L771) | Callable definition: ~Data() | calls finish · [reviewed contract](#b0079) |
| [B0080 · 772–790](../../../../../src/runtime/delta.cpp#L772) | Callable definition: void observe() const noexcept | calls set · [reviewed contract](#b0080) |
| [B0081 · 791–791](../../../../../src/runtime/delta.cpp#L791) | Explanatory comments or spacing. |  |
| [B0082 · 792–808](../../../../../src/runtime/delta.cpp#L792) | Callable definition: void finish() noexcept | calls empty, observe_output, std::terminate, add · [reviewed contract](#b0082) |
| [B0083 · 809–837](../../../../../src/runtime/delta.cpp#L809) | Callable definition: void append(SetOperation operation,storage::Tuple tuple) | calls add, event, metric, require; guard require(rows.size()&lt;options.spool_row_limit && rows.size()&lt;std::numeric_limits&lt;std::uint64_t&gt;::max(…; growth push_back · [reviewed contract](#b0083) |
| [B0084 · 838–855](../../../../../src/runtime/delta.cpp#L838) | Callable definition: void disable_output() | calls observe_output, metric, size, charge; 1 loop sites · [reviewed contract](#b0084) |
| [B0085 · 856–883](../../../../../src/runtime/delta.cpp#L856) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // A heap-stable route owns endpoint views and its cursor across pause/resume. · [reviewed contract](#b0085) |
| [B0086 · 884–936](../../../../../src/runtime/delta.cpp#L884) | Callable definition: Stage(const Impl& owner,Epoch::Data& result,std::shared_ptr&lt;LiveImage&gt;& state,LiveTransaction* live, const SupportRuntime::EpochV… | calls runtime, output, working, transaction; guard require(record.after.member==(operation==SetOperation::insert),"runtime_contract","E membership con…; growth emplace, insert; 3 loop sites · [reviewed contract](#b0086) |
| [B0087 · 937–938](../../../../../src/runtime/delta.cpp#L937) | Explanatory comments or spacing. | source comment (unverified): // Lifecycle-only cleanup is finalization, not producer work. Keep its · [reviewed contract](#b0087) |
| [B0088 · 939–939](../../../../../src/runtime/delta.cpp#L939) | Callable definition: void exclude_work(std::uint64_t amount) noexcept | calls ; source comment (unverified): // Lifecycle-only cleanup is finalization, not producer work. Keep its · [reviewed contract](#b0088) |
| [B0089 · 940–992](../../../../../src/runtime/delta.cpp#L940) | Callable definition: bool open() | calls size, metric, begin, empty; guard require(productive-&gt;rows!=0,"runtime_contract","productive queue underflow");; returns true; false; growth emplace, insert, make_accounted_unique, push_back, reserve; 2 loop sites · [reviewed contract](#b0089) |
| [B0090 · 993–1033](../../../../../src/runtime/delta.cpp#L993) | Callable definition: bool next() | calls open, finish, cursor_next, reset; guard require(produced,"runtime_contract","productive witness emitted no replay answer");; returns false; false; growth insert; 2 loop sites · [reviewed contract](#b0090) |
| [B0091 · 1034–1067](../../../../../src/runtime/delta.cpp#L1034) | Callable definition: void finish() | calls end_stage, require, std::max, metric; guard require(productive-&gt;rows==0,"runtime_contract","productive queue did not drain");; growth push_back; 3 loop sites · [reviewed contract](#b0091) |
| [B0092 · 1068–1084](../../../../../src/runtime/delta.cpp#L1068) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0092) |
| [B0093 · 1085–1103](../../../../../src/runtime/delta.cpp#L1085) | Callable definition: Data(std::shared_ptr&lt;Impl&gt; runtime,const PhysicalUpdateView& update) :owner(std::move(runtime)),storage_lease(detail::storage_lea… | calls owner, std::move, storage_lease, detail::storage_lease; growth emplace, make_accounted_shared · [reviewed contract](#b0093) |
| [B0094 · 1104–1104](../../../../../src/runtime/delta.cpp#L1104) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0094) |
| [B0095 · 1105–1105](../../../../../src/runtime/delta.cpp#L1105) | Callable definition: bool active() const noexcept | calls ; returns owner && physical && physical-&gt;active() · [reviewed contract](#b0095) |
| [B0096 · 1106–1106](../../../../../src/runtime/delta.cpp#L1106) | Callable definition: void validate() const | calls require, active; guard void validate() const { require(active(),"invalid_delta_epoch","pending delta epoch is closed"); } · [reviewed contract](#b0096) |
| [B0097 · 1107–1107](../../../../../src/runtime/delta.cpp#L1107) | Callable definition: void set_phase(DeltaState value) noexcept | calls  · [reviewed contract](#b0097) |
| [B0098 · 1108–1124](../../../../../src/runtime/delta.cpp#L1108) | Callable definition: void rollback() noexcept | calls timing, reset, finish, observe; source comment (unverified): // Cursors and endpoint leases must close before the physical undo and · [reviewed contract](#b0098) |
| [B0099 · 1125–1159](../../../../../src/runtime/delta.cpp#L1125) | Callable definition: void finalize() | calls scalar_sql, support, timing, metric; growth insert · [reviewed contract](#b0099) |
| [B0100 · 1160–1180](../../../../../src/runtime/delta.cpp#L1160) | Callable definition: DeltaStep step() | calls timing, next, reset, memory; returns DeltaStep::core_result; DeltaStep::progress; growth make_accounted_unique · [reviewed contract](#b0100) |
| [B0101 · 1181–1182](../../../../../src/runtime/delta.cpp#L1181) | Closes surrounding scope/type. |  · [reviewed contract](#b0101) |
| [B0102 · 1183–1183](../../../../../src/runtime/delta.cpp#L1183) | Callable definition: DeltaRuntime::PendingEpoch::PendingEpoch(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0102) |
| [B0103 · 1184–1184](../../../../../src/runtime/delta.cpp#L1184) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0103) |
| [B0104 · 1185–1188](../../../../../src/runtime/delta.cpp#L1185) | Callable definition: DeltaRuntime::PendingEpoch& DeltaRuntime::PendingEpoch::operator=(PendingEpoch&& other) noexcept | calls ; returns *this · [reviewed contract](#b0104) |
| [B0105 · 1189–1189](../../../../../src/runtime/delta.cpp#L1189) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0105) |
| [B0106 · 1190–1190](../../../../../src/runtime/delta.cpp#L1190) | Callable definition: bool DeltaRuntime::PendingEpoch::active() const noexcept | calls active; returns data_ && data_-&gt;active() · [reviewed contract](#b0106) |
| [B0107 · 1191–1191](../../../../../src/runtime/delta.cpp#L1191) | Callable definition: DeltaState DeltaRuntime::PendingEpoch::state() const noexcept | calls ; returns data_?data_-&gt;phase:DeltaState::aborted · [reviewed contract](#b0107) |
| [B0108 · 1192–1194](../../../../../src/runtime/delta.cpp#L1192) | Callable definition: std::uint64_t DeltaRuntime::PendingEpoch::sequence() const | calls require, bool; guard require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); return data_-&gt;sequence;; returns data_-&gt;sequence · [reviewed contract](#b0108) |
| [B0109 · 1195–1197](../../../../../src/runtime/delta.cpp#L1195) | Callable definition: const DeltaMetrics& DeltaRuntime::PendingEpoch::metrics() const | calls require; guard require(data_ && data_-&gt;output,"invalid_delta_epoch","pending delta output is closed"); return data…; returns data_-&gt;output-&gt;metrics · [reviewed contract](#b0109) |
| [B0110 · 1198–1200](../../../../../src/runtime/delta.cpp#L1198) | Callable definition: const DeltaTimings& DeltaRuntime::PendingEpoch::timings() const | calls require; guard require(data_ && data_-&gt;output,"invalid_delta_epoch","pending delta output is closed"); return data…; returns data_-&gt;output-&gt;timings · [reviewed contract](#b0110) |
| [B0111 · 1201–1203](../../../../../src/runtime/delta.cpp#L1201) | Callable definition: std::span&lt;const DeltaStage&gt; DeltaRuntime::PendingEpoch::stages() const | calls require; guard require(data_ && data_-&gt;output,"invalid_delta_epoch","pending delta output is closed"); return data…; returns data_-&gt;output-&gt;stages · [reviewed contract](#b0111) |
| [B0112 · 1204–1213](../../../../../src/runtime/delta.cpp#L1204) | Callable definition: DeltaStep DeltaRuntime::PendingEpoch::step() | calls require, bool, validate, storage_operation; guard require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_-&gt;validate();; returns DeltaStep::prepared; result · [reviewed contract](#b0112) |
| [B0113 · 1214–1218](../../../../../src/runtime/delta.cpp#L1214) | Callable definition: void DeltaRuntime::PendingEpoch::pause() | calls require, bool, validate, set_phase; guard require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_-&gt;validate(); · [reviewed contract](#b0113) |
| [B0114 · 1219–1223](../../../../../src/runtime/delta.cpp#L1219) | Callable definition: void DeltaRuntime::PendingEpoch::resume() | calls require, bool, validate, set_phase; guard require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_-&gt;validate(); · [reviewed contract](#b0114) |
| [B0115 · 1224–1234](../../../../../src/runtime/delta.cpp#L1224) | Callable definition: void DeltaRuntime::PendingEpoch::start_drain() | calls require, bool, validate, timing; guard require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_-&gt;validate(); · [reviewed contract](#b0115) |
| [B0116 · 1235–1242](../../../../../src/runtime/delta.cpp#L1235) | Callable definition: void DeltaRuntime::PendingEpoch::drain() | calls require, bool, validate, observe_output; guard require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_-&gt;validate();; 1 loop sites · [reviewed contract](#b0116) |
| [B0117 · 1243–1278](../../../../../src/runtime/delta.cpp#L1243) | Callable definition: DeltaRuntime::Epoch DeltaRuntime::PendingEpoch::commit() | calls require, bool, validate, static_assert; guard require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_-&gt;validate();; returns Epoch(std::move(output)); growth emplace; source comment (unverified): // All throwing preparation and cleanup precharges finished before this barrier. · [reviewed contract](#b0117) |
| [B0118 · 1279–1279](../../../../../src/runtime/delta.cpp#L1279) | Callable definition: DeltaRuntime::Epoch DeltaRuntime::PendingEpoch::discard() | calls start_drain, drain, commit; returns commit() · [reviewed contract](#b0118) |
| [B0119 · 1280–1280](../../../../../src/runtime/delta.cpp#L1280) | Callable definition: void DeltaRuntime::PendingEpoch::rollback() noexcept | calls rollback · [reviewed contract](#b0119) |
| [B0120 · 1281–1281](../../../../../src/runtime/delta.cpp#L1281) | Explanatory comments or spacing. |  |
| [B0121 · 1282–1282](../../../../../src/runtime/delta.cpp#L1282) | Callable definition: DeltaRuntime::Epoch::Epoch(std::shared_ptr&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0121) |
| [B0122 · 1283–1283](../../../../../src/runtime/delta.cpp#L1283) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0122) |
| [B0123 · 1284–1287](../../../../../src/runtime/delta.cpp#L1284) | Callable definition: DeltaRuntime::Epoch& DeltaRuntime::Epoch::operator=(Epoch&& other) noexcept | calls ; returns *this · [reviewed contract](#b0123) |
| [B0124 · 1288–1288](../../../../../src/runtime/delta.cpp#L1288) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0124) |
| [B0125 · 1289–1289](../../../../../src/runtime/delta.cpp#L1289) | Callable definition: bool DeltaRuntime::Epoch::active() const noexcept | calls ; returns data_ && data_-&gt;leased · [reviewed contract](#b0125) |
| [B0126 · 1290–1290](../../../../../src/runtime/delta.cpp#L1290) | Callable definition: std::uint64_t DeltaRuntime::Epoch::sequence() const | calls input; returns input().input.sequence · [reviewed contract](#b0126) |
| [B0127 · 1291–1293](../../../../../src/runtime/delta.cpp#L1291) | Callable definition: const PhysicalEpoch& DeltaRuntime::Epoch::input() const | calls require; guard require(data_ && data_-&gt;input,"invalid_delta_epoch","moved-from delta epoch"); return *data_-&gt;input;; returns *data_-&gt;input · [reviewed contract](#b0127) |
| [B0128 · 1294–1294](../../../../../src/runtime/delta.cpp#L1294) | Callable definition: const DeltaMetrics& DeltaRuntime::Epoch::metrics() const | calls require, bool; guard const DeltaMetrics& DeltaRuntime::Epoch::metrics() const { require(bool(data_),"invalid_delta_epoch…; returns data_-&gt;metrics · [reviewed contract](#b0128) |
| [B0129 · 1295–1295](../../../../../src/runtime/delta.cpp#L1295) | Callable definition: const DeltaTimings& DeltaRuntime::Epoch::timings() const | calls require, bool; guard const DeltaTimings& DeltaRuntime::Epoch::timings() const { require(bool(data_),"invalid_delta_epoch…; returns data_-&gt;timings · [reviewed contract](#b0129) |
| [B0130 · 1296–1296](../../../../../src/runtime/delta.cpp#L1296) | Callable definition: std::span&lt;const DeltaStage&gt; DeltaRuntime::Epoch::stages() const | calls require, bool; guard std::span&lt;const DeltaStage&gt; DeltaRuntime::Epoch::stages() const { require(bool(data_),"invalid_delt…; returns data_-&gt;stages · [reviewed contract](#b0130) |
| [B0131 · 1297–1297](../../../../../src/runtime/delta.cpp#L1297) | Callable definition: const storage::TupleLayout& DeltaRuntime::Epoch::layout() const | calls require, bool; guard const storage::TupleLayout& DeltaRuntime::Epoch::layout() const { require(bool(data_),"invalid_delt…; returns data_-&gt;layout · [reviewed contract](#b0131) |
| [B0132 · 1298–1298](../../../../../src/runtime/delta.cpp#L1298) | Callable definition: std::size_t DeltaRuntime::Epoch::remaining() const | calls require, bool, size; guard std::size_t DeltaRuntime::Epoch::remaining() const { require(bool(data_),"invalid_delta_epoch","mov…; returns data_-&gt;rows.size() · [reviewed contract](#b0132) |
| [B0133 · 1299–1311](../../../../../src/runtime/delta.cpp#L1299) | Callable definition: std::optional&lt;SignedResult&gt; DeltaRuntime::Epoch::next() | calls require, bool, empty, std::move; guard require(bool(data_),"invalid_delta_epoch","moved-from delta epoch");; returns {}; result · [reviewed contract](#b0133) |
| [B0134 · 1312–1316](../../../../../src/runtime/delta.cpp#L1312) | Callable definition: void DeltaRuntime::Epoch::visit_complete(void(*visitor)(const SignedResult&,void*),void* context) const | calls void, require, size, visitor; guard require(data_ && !data_-&gt;delivering,"runtime_busy","epoch output is unavailable");; 1 loop sites · [reviewed contract](#b0134) |
| [B0135 · 1317–1327](../../../../../src/runtime/delta.cpp#L1317) | Callable definition: void DeltaRuntime::Epoch::acknowledge_complete() noexcept | calls size, std::terminate, empty, add; 1 loop sites · [reviewed contract](#b0135) |
| [B0136 · 1328–1330](../../../../../src/runtime/delta.cpp#L1328) | Callable definition: bool DeltaRuntime::Epoch::deliver_one(const std::function&lt;void(const SignedResult&)&gt;& sink) | calls void, deliver_one; returns deliver_one({},sink) · [reviewed contract](#b0136) |
| [B0137 · 1331–1384](../../../../../src/runtime/delta.cpp#L1331) | Callable definition: bool DeltaRuntime::Epoch::deliver_one(const std::function&lt;void(const SignedResult&)&gt;& serialize, const std::function&lt;void(const S… | calls void, require, bool, empty; guard require(bool(data_),"invalid_delta_epoch","moved-from delta epoch");; returns false; true; source comment (unverified): // Keeps the borrowed row alive across facade moves. · [reviewed contract](#b0137) |
| [B0138 · 1385–1385](../../../../../src/runtime/delta.cpp#L1385) | Callable definition: void DeltaRuntime::Epoch::discard() noexcept | calls finish · [reviewed contract](#b0138) |
| [B0139 · 1386–1386](../../../../../src/runtime/delta.cpp#L1386) | Explanatory comments or spacing. |  |
| [B0140 · 1387–1393](../../../../../src/runtime/delta.cpp#L1387) | Callable definition: DeltaRuntime::DeltaRuntime(PhysicalPlan plan,DeltaOptions options) :impl_(\[&\] { auto context=detail::storage_context(plan,options… | calls impl_, detail::storage_context, storage_operation, memory; returns data; growth make_accounted_shared · [reviewed contract](#b0140) |
| [B0141 · 1394–1402](../../../../../src/runtime/delta.cpp#L1394) | Callable definition: DeltaRuntime::DeltaRuntime(CompiledProgram source,DeltaOptions options) try :impl_(\[&\] { auto context=detail::new_storage_context… | calls impl_, detail::new_storage_context, operation, CompiledProgram::freeze; returns data; growth make_accounted_shared · [reviewed contract](#b0141) |
| [B0142 · 1403–1423](../../../../../src/runtime/delta.cpp#L1403) | Callable definition: DeltaRuntime::DeltaRuntime(PhysicalRuntime physical,DeltaOptions options,BuildOptions build) :impl_(\[&\] { auto context=physical.s… | calls impl_, storage_context, memory, std::move; returns resource::make_accounted_shared&lt;Impl&gt;(context-&gt;memory(),resource::MemoryPurpose::delta_state,std::m…; growth make_accounted_shared; source comment (unverified): // Only this unpublished owner uses build limits. Ordinary updates retain · [reviewed contract](#b0142) |
| [B0143 · 1424–1428](../../../../../src/runtime/delta.cpp#L1424) | Callable definition: DeltaRuntime DeltaRuntime::initialize(PhysicalPlan plan,const Database& database,DeltaOptions options,BuildOptions build) | calls detail::storage_context, storage_operation, PhysicalRuntime::initialize_at, std::move; returns DeltaRuntime(std::move(physical),options,build) · [reviewed contract](#b0143) |
| [B0144 · 1429–1435](../../../../../src/runtime/delta.cpp#L1429) | Callable definition: DeltaRuntime DeltaRuntime::initialize(CompiledProgram source,const Database& database,DeltaOptions options,BuildOptions build) try | calls detail::new_storage_context, operation, CompiledProgram::freeze, memory; returns DeltaRuntime(std::move(physical),options,build) · [reviewed contract](#b0144) |
| [B0145 · 1436–1446](../../../../../src/runtime/delta.cpp#L1436) | Callable definition: DeltaRuntime DeltaRuntime::rebuilt(BuildOptions build) const | calls impl, writable, detail::storage_context, plan; returns result; source comment (unverified): // New owner; restore requested initial options. · [reviewed contract](#b0145) |
| [B0146 · 1447–1458](../../../../../src/runtime/delta.cpp#L1447) | Callable definition: DeltaRuntime DeltaRuntime::rebuilt_for(const planner::MinimumHeightCandidate& candidate,BuildOptions build, const program::Replan… | calls impl, writable, detail::storage_context, plan; returns result · [reviewed contract](#b0146) |
| [B0147 · 1459–1459](../../../../../src/runtime/delta.cpp#L1459) | declares namespace scope. |  · [reviewed contract](#b0147) |
| [B0148 · 1460–1470](../../../../../src/runtime/delta.cpp#L1460) | Callable definition: recovery::ImageBinding image_binding(const CompiledProgram& program,const DeltaOptions& options,DeltaMode mode) | calls size, recovery::ImageFailure, std::copy, begin; returns result · [reviewed contract](#b0148) |
| [B0149 · 1471–1471](../../../../../src/runtime/delta.cpp#L1471) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0149) |
| [B0150 · 1472–1475](../../../../../src/runtime/delta.cpp#L1472) | Callable definition: recovery::EncodedImage DeltaRuntime::checkpoint_image(recovery::ImageLimits limits) const | calls impl, writable, checkpoint_image, image_binding; returns d.physical.checkpoint_image(image_binding(d.physical.compiled_program(),d.options,d.mode),limits) · [reviewed contract](#b0150) |
| [B0151 · 1476–1478](../../../../../src/runtime/delta.cpp#L1476) | Callable definition: recovery::ImageBinding DeltaRuntime::checkpoint_binding() const | calls impl, image_binding, compiled_program; returns image_binding(d.physical.compiled_program(),d.options,d.mode) · [reviewed contract](#b0151) |
| [B0152 · 1479–1482](../../../../../src/runtime/delta.cpp#L1479) | Callable definition: DeltaRuntime DeltaRuntime::restore_image(CompiledProgram program,std::string_view bytes, DeltaOptions options,BuildOptions build,… | calls restore_session_image, std::move; returns restore_session_image(std::move(program),bytes,options,build,limits,nullptr,0,nullptr) · [reviewed contract](#b0152) |
| [B0153 · 1483–1498](../../../../../src/runtime/delta.cpp#L1483) | Callable definition: DeltaRuntime DeltaRuntime::restore_session_image(CompiledProgram program,std::string_view bytes, DeltaOptions options,BuildOption… | calls image_binding, detail::new_storage_context, options, indexed; returns result · [reviewed contract](#b0153) |
| [B0154 · 1499–1499](../../../../../src/runtime/delta.cpp#L1499) | Callable definition: InitializationContext DeltaRuntime::initialization_context() const | calls impl, initialization_context; returns impl().physical.initialization_context() · [reviewed contract](#b0154) |
| [B0155 · 1500–1500](../../../../../src/runtime/delta.cpp#L1500) | Callable definition: const BuildMetrics& DeltaRuntime::initialization_metrics() const | calls impl; returns impl().initialization · [reviewed contract](#b0155) |
| [B0156 · 1501–1502](../../../../../src/runtime/delta.cpp#L1501) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0156) |
| [B0157 · 1503–1503](../../../../../src/runtime/delta.cpp#L1503) | Callable definition: DeltaRuntime& DeltaRuntime::operator=(DeltaRuntime&& other) noexcept | calls ; returns *this · [reviewed contract](#b0157) |
| [B0158 · 1504–1504](../../../../../src/runtime/delta.cpp#L1504) | Callable definition: DeltaRuntime::Impl& DeltaRuntime::impl() const | calls require, bool; guard DeltaRuntime::Impl& DeltaRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved-from …; returns *impl_ · [reviewed contract](#b0158) |
| [B0159 · 1505–1505](../../../../../src/runtime/delta.cpp#L1505) | Callable definition: const CompiledProgram& DeltaRuntime::plan() const | calls impl, plan; returns impl().physical.plan() · [reviewed contract](#b0159) |
| [B0160 · 1506–1506](../../../../../src/runtime/delta.cpp#L1506) | Callable definition: const CompiledProgram& DeltaRuntime::compiled_program() const | calls impl, compiled_program; returns impl().physical.compiled_program() · [reviewed contract](#b0160) |
| [B0161 · 1507–1507](../../../../../src/runtime/delta.cpp#L1507) | Callable definition: const DeltaOptions& DeltaRuntime::options() const | calls impl; returns impl().options · [reviewed contract](#b0161) |
| [B0162 · 1508–1508](../../../../../src/runtime/delta.cpp#L1508) | Callable definition: resource::MemoryStatistics DeltaRuntime::accounted_memory_statistics() const | calls impl, accounted_memory_statistics; returns impl().physical.accounted_memory_statistics() · [reviewed contract](#b0162) |
| [B0163 · 1509–1509](../../../../../src/runtime/delta.cpp#L1509) | Callable definition: DeltaCompletion DeltaRuntime::completion() const | calls impl; returns impl().selected_completion · [reviewed contract](#b0163) |
| [B0164 · 1510–1549](../../../../../src/runtime/delta.cpp#L1510) | Callable definition: DeltaRuntimeProfile DeltaRuntime::profile() const | calls impl, size, plan, options; returns result; result · [reviewed contract](#b0164) |
| [B0165 · 1550–1550](../../../../../src/runtime/delta.cpp#L1550) | Callable definition: SupportOwnerId DeltaRuntime::owner() const | calls impl, owner; returns impl().physical.owner() · [reviewed contract](#b0165) |
| [B0166 · 1551–1551](../../../../../src/runtime/delta.cpp#L1551) | Callable definition: std::uint64_t DeltaRuntime::sequence() const | calls impl, sequence; returns impl().physical.sequence() · [reviewed contract](#b0166) |
| [B0167 · 1552–1552](../../../../../src/runtime/delta.cpp#L1552) | Callable definition: DeltaMode DeltaRuntime::mode() const | calls impl; returns impl().mode · [reviewed contract](#b0167) |
| [B0168 · 1553–1553](../../../../../src/runtime/delta.cpp#L1553) | Callable definition: bool DeltaRuntime::ready() const | calls impl, ready; returns !d.processing && !d.output_active && d.physical.ready() · [reviewed contract](#b0168) |
| [B0169 · 1554–1556](../../../../../src/runtime/delta.cpp#L1554) | Callable definition: DeltaState DeltaRuntime::state() const | calls impl; returns d.processing?d.lifecycle:d.output_active?DeltaState::committed_output:DeltaState::ready · [reviewed contract](#b0169) |
| [B0170 · 1557–1557](../../../../../src/runtime/delta.cpp#L1557) | Callable definition: bool DeltaRuntime::has_answer() const | calls impl, readable, has_answer; returns d.physical.has_answer() · [reviewed contract](#b0170) |
| [B0171 · 1558–1558](../../../../../src/runtime/delta.cpp#L1558) | Callable definition: const storage::TupleLayout& DeltaRuntime::result_layout() const | calls impl; returns impl().output_layout · [reviewed contract](#b0171) |
| [B0172 · 1559–1559](../../../../../src/runtime/delta.cpp#L1559) | Callable definition: const DeltaMetrics& DeltaRuntime::bootstrap_metrics() const | calls impl; returns impl().bootstrap · [reviewed contract](#b0172) |
| [B0173 · 1560–1560](../../../../../src/runtime/delta.cpp#L1560) | controls preprocessing. |  · [reviewed contract](#b0173) |
| [B0174 · 1561–1563](../../../../../src/runtime/delta.cpp#L1561) | Callable definition: std::optional&lt;RuntimeStorageWork&gt; RuntimeTestProbe::index_work(const DeltaRuntime& runtime) | calls index_work, impl; returns index_work(runtime.impl().physical) · [reviewed contract](#b0174) |
| [B0175 · 1564–1564](../../../../../src/runtime/delta.cpp#L1564) | controls preprocessing. |  · [reviewed contract](#b0175) |
| [B0176 · 1565–1567](../../../../../src/runtime/delta.cpp#L1565) | Callable definition: DeltaMetrics DeltaRuntime::set_mode(DeltaMode mode) | calls impl, storage_operation, storage_context, change_mode; returns d.change_mode(mode) · [reviewed contract](#b0176) |
| [B0177 · 1568–1581](../../../../../src/runtime/delta.cpp#L1568) | Callable definition: DeltaMetrics DeltaRuntime::Impl::change_mode(DeltaMode mode) | calls writable, require, reset, observe_configuration; guard require(mode==DeltaMode::maintenance \|\| mode==DeltaMode::delta,"invalid_mode","unknown delta mainte…; returns metrics; metrics · [reviewed contract](#b0177) |
| [B0178 · 1582–1584](../../../../../src/runtime/delta.cpp#L1582) | Callable definition: DeltaRuntime::PendingEpoch DeltaRuntime::begin(const PhysicalSetUpdate& update) | calls begin_view, PhysicalUpdateView::borrow; returns begin_view(PhysicalUpdateView::borrow(update)) · [reviewed contract](#b0178) |
| [B0179 · 1585–1589](../../../../../src/runtime/delta.cpp#L1585) | Callable definition: DeltaRuntime::PendingEpoch DeltaRuntime::begin_view(const PhysicalUpdateView& update) | calls storage_operation, impl, storage_context, writable; returns PendingEpoch(resource::make_accounted_unique&lt;PendingEpoch::Data&gt;(delta_metadata,d.memory(),resource…; growth make_accounted_unique · [reviewed contract](#b0179) |
| [B0180 · 1590–1592](../../../../../src/runtime/delta.cpp#L1590) | Callable definition: DeltaRuntime::Epoch DeltaRuntime::apply(const PhysicalSetUpdate& update) | calls begin, drain, commit; returns pending.commit() · [reviewed contract](#b0180) |
| [B0181 · 1593–1595](../../../../../src/runtime/delta.cpp#L1593) | Callable definition: DeltaRuntime::Epoch DeltaRuntime::apply_view(const PhysicalUpdateView& update) | calls begin_view, drain, commit; returns pending.commit() · [reviewed contract](#b0181) |
| [B0182 · 1596–1599](../../../../../src/runtime/delta.cpp#L1596) | Callable definition: SupportRuntime::ResultCursor DeltaRuntime::results(ResultCursorOptions options) const | calls impl, readable, core_results, results; returns d.options.view==ResultView::core?d.physical.core_results(options):d.physical.results(options) · [reviewed contract](#b0182) |
| [B0183 · 1600–1600](../../../../../src/runtime/delta.cpp#L1600) | Callable definition: SupportRuntime::ResultCursor DeltaRuntime::core_results(ResultCursorOptions options) const | calls impl, readable, core_results; returns d.physical.core_results(options) · [reviewed contract](#b0183) |
| [B0184 · 1601–1601](../../../../../src/runtime/delta.cpp#L1601) | Callable definition: SupportRuntime::EpochView DeltaRuntime::current_view(EpochViewOptions options) const | calls impl, readable, current_view; returns d.physical.current_view(options) · [reviewed contract](#b0184) |
| [B0185 · 1602–1602](../../../../../src/runtime/delta.cpp#L1602) | Callable definition: PhysicalSnapshot DeltaRuntime::snapshot() const | calls impl, readable, snapshot; returns d.physical.snapshot() · [reviewed contract](#b0185) |
| [B0186 · 1603–1608](../../../../../src/runtime/delta.cpp#L1603) | Callable definition: std::optional&lt;LiveSnapshot&gt; DeltaRuntime::live_snapshot() const | calls impl, readable, reserve, size; returns {}; result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0186) |
| [B0187 · 1609–1609](../../../../../src/runtime/delta.cpp#L1609) | Callable definition: PhysicalStorageStatistics DeltaRuntime::storage_statistics() const | calls impl, readable, storage_statistics; returns d.physical.storage_statistics() · [reviewed contract](#b0187) |
| [B0188 · 1610–1627](../../../../../src/runtime/delta.cpp#L1610) | Callable definition: CanonicalDeltaState DeltaRuntime::canonical_state() const | calls storage_operation, impl, storage_context, readable; returns output; result; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0188) |
| [B0189 · 1628–1784](../../../../../src/runtime/delta.cpp#L1628) | Callable definition: InvariantReport DeltaRuntime::inspect_invariants(InspectionOptions options) const | calls storage_operation, impl, storage_context, readable; returns std::move(context.report); std::move(context.report); growth copy_of, insert, push_back, reserve; 14 loop sites; source comment (unverified): // Derive expected L top-down from actual E, independently of build_live. · [reviewed contract](#b0189) |
| [B0190 · 1785–1785](../../../../../src/runtime/delta.cpp#L1785) | controls preprocessing. |  · [reviewed contract](#b0190) |
| [B0191 · 1786–1789](../../../../../src/runtime/delta.cpp#L1786) | Callable definition: void RuntimeTestProbe::seed_delta_sequence(DeltaRuntime& runtime,std::uint64_t sequence) | calls impl, writable, seed_physical_sequence · [reviewed contract](#b0191) |
| [B0192 · 1790–1790](../../../../../src/runtime/delta.cpp#L1790) | Callable definition: PhysicalRuntime& RuntimeTestProbe::physical(DeltaRuntime& runtime) | calls impl; returns runtime.impl().physical · [reviewed contract](#b0192) |
| [B0193 · 1791–1798](../../../../../src/runtime/delta.cpp#L1791) | Callable definition: std::uint64_t RuntimeTestProbe::set_live_bucket(DeltaRuntime& runtime,NodeId node,bool child,const Row& key,std::uint64_t value) | calls impl, writable, require, bool; guard require(bool(d.live),"invalid_probe","delta live image is absent");; returns std::exchange(bucket.value,value) · [reviewed contract](#b0193) |
| [B0194 · 1799–1808](../../../../../src/runtime/delta.cpp#L1799) | Callable definition: std::size_t RuntimeTestProbe::set_live_total(DeltaRuntime& runtime,InvariantComponent component,std::size_t value) | calls impl, writable, require, bool; guard require(bool(d.live),"invalid_probe","delta live image is absent");; returns std::exchange(d.live-&gt;rows,value); std::exchange(d.live-&gt;parent_rows,value) · [reviewed contract](#b0194) |
| [B0195 · 1809–1810](../../../../../src/runtime/delta.cpp#L1809) | controls preprocessing. |  · [reviewed contract](#b0195) |
| [B0196 · 1811–1821](../../../../../src/runtime/delta.cpp#L1811) | Callable definition: void DeltaRuntime::check_invariants() const | calls storage_operation, impl, storage_context, readable; guard if (d.mode==DeltaMode::maintenance) { require(!d.live,"runtime_contract","maintenance mode retained… · [reviewed contract](#b0196) |
| [B0197 · 1822–1825](../../../../../src/runtime/delta.cpp#L1822) | Callable definition: void DeltaRuntime::declare_benchmark_context(std::shared_ptr&lt;const DeclaredBenchmarkContext&gt; value) | calls impl, std::move, declare_benchmark · [reviewed contract](#b0197) |
| [B0198 · 1826–1826](../../../../../src/runtime/delta.cpp#L1826) | Callable definition: std::optional&lt;CursorObservation&gt; DeltaRuntime::last_cursor_observation() const | calls impl, last_cursor_observation; returns impl().physical.last_cursor_observation() · [reviewed contract](#b0198) |
| [B0199 · 1827–1827](../../../../../src/runtime/delta.cpp#L1827) | Callable definition: CommittedStateGauges DeltaRuntime::committed_state_gauges() const | calls impl, readable, committed_state_gauges; returns d.physical.committed_state_gauges() · [reviewed contract](#b0199) |
| [B0200 · 1828–1828](../../../../../src/runtime/delta.cpp#L1828) | Callable definition: CapturedStateGauges DeltaRuntime::capture_state_gauges() const | calls impl, readable, capture_state_gauges; returns d.physical.capture_state_gauges() · [reviewed contract](#b0200) |
| [B0201 · 1829–1833](../../../../../src/runtime/delta.cpp#L1829) | Callable definition: ObservationSnapshot DeltaRuntime::observations() const | calls impl, observations, initialization_context; returns result · [reviewed contract](#b0201) |
| [B0202 · 1834–1836](../../../../../src/runtime/delta.cpp#L1834) | Callable definition: ObservationTrace DeltaRuntime::observation_trace() const | calls impl, observation_trace, observations; returns result · [reviewed contract](#b0202) |
| [B0203 · 1837–1839](../../../../../src/runtime/delta.cpp#L1837) | Callable definition: CapturedObservationTrace DeltaRuntime::capture_observation_trace() const | calls impl, capture_observation_trace, observations; returns result · [reviewed contract](#b0203) |
| [B0204 · 1840–1843](../../../../../src/runtime/delta.cpp#L1840) | Callable definition: bool DeltaRuntime::same_sources(const DeltaRuntime& other,reoptimization::detail::Budget& budget) const | calls impl, writable, same_sources; returns left.physical.same_sources(right.physical,budget) · [reviewed contract](#b0204) |
| [B0205 · 1844–1846](../../../../../src/runtime/delta.cpp#L1844) | declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0205) |
| [B0206 · 1847–1849](../../../../../src/runtime/delta.cpp#L1847) | Callable definition: void DeltaRuntime::configure_workload_statistics(const workload::Options& options) | calls impl, writable, configure_workload_statistics · [reviewed contract](#b0206) |
| [B0207 · 1850–1852](../../../../../src/runtime/delta.cpp#L1850) | Callable definition: void DeltaRuntime::reset_workload_statistics() | calls impl, writable, reset_workload_statistics · [reviewed contract](#b0207) |
| [B0208 · 1853–1855](../../../../../src/runtime/delta.cpp#L1853) | Callable definition: workload::Snapshot DeltaRuntime::workload_statistics() const | calls impl, snapshot, compiled_program, owner; returns d.workload-&gt;snapshot(d.physical.compiled_program(),d.physical.owner(),d.physical.sequence(),d.proce… · [reviewed contract](#b0208) |
| [B0209 · 1856–1856](../../../../../src/runtime/delta.cpp#L1856) | Callable definition: workload::Options DeltaRuntime::workload_statistics_options() const | calls impl, options; returns impl().workload-&gt;options() · [reviewed contract](#b0209) |
| [B0210 · 1857–1857](../../../../../src/runtime/delta.cpp#L1857) | controls preprocessing. |  · [reviewed contract](#b0210) |
| [B0211 · 1858–1860](../../../../../src/runtime/delta.cpp#L1858) | Callable definition: void RuntimeTestProbe::seed_c01_report_saturation(DeltaRuntime& runtime) | calls impl, writable, seed_report_saturation · [reviewed contract](#b0211) |
| [B0212 · 1861–1864](../../../../../src/runtime/delta.cpp#L1861) | Imports dependencies; controls preprocessing; declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0212) |
| [B0213 · 1865–1867](../../../../../src/runtime/delta.cpp#L1865) | Callable definition: statistics::OwnerCapture DeltaRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const | calls capture_statistics_view; returns capture_statistics_view(request,limits) · [reviewed contract](#b0213) |
| [B0214 · 1868–1873](../../../../../src/runtime/delta.cpp#L1868) | Callable definition: statistics::OwnerCapture DeltaRuntime::capture_statistics_view(statistics::OwnerRequestView request,statistics::Limits limits) co… | calls storage_operation, impl, storage_context, owner; returns pending.finish(); d.physical.capture_statistics_view(request,limits) · [reviewed contract](#b0214) |
| [B0215 · 1874–1876](../../../../../src/runtime/delta.cpp#L1874) | Callable definition: statistics::Freshness DeltaRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) co… | calls impl, statistics_freshness; returns impl().physical.statistics_freshness(captured,max_event_lag) · [reviewed contract](#b0215) |
| [B0216 · 1877–1879](../../../../../src/runtime/delta.cpp#L1877) | declares namespace scope. |  · [reviewed contract](#b0216) |
| [B0217 · 1880–1905](../../../../../src/runtime/delta.cpp#L1880) | Callable definition: void Access::append(Builder& builder,const DeltaRuntime& owner) | calls impl, append, operation, bool; 3 loop sites · [reviewed contract](#b0217) |
| [B0218 · 1906–1914](../../../../../src/runtime/delta.cpp#L1906) | Callable definition: Attempt Access::capture(const DeltaRuntime& owner,Limits limits) noexcept | calls attempt, impl, plan, builder; returns attempt(\[&\](Usage& usage) {; builder.finish() · [reviewed contract](#b0218) |
| [B0219 · 1915–1915](../../../../../src/runtime/delta.cpp#L1915) | Closes surrounding scope/type. |  · [reviewed contract](#b0219) |

## B0001

[Lines 1–26](../../../../../src/runtime/delta.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/delta.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble the Boolean Delta coordinator and native ordered-row state. |
| inputs / outputs | Public Delta, storage-work, checkpoint, observation, inspection and memory helpers; accounted-vector aliases and coordinator attribution. |
| invariants | UINT64_MAX distinguishes coordinator arrays/control/scratch from factor node zero; local support S/P/E and global L have separate owners. |
| ownership | Aliases retain nothing until instantiated; native allocations use the original query account. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Includes/aliases/constants add no dynamic work. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 27–29](../../../../../src/runtime/delta.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,std::string_view code,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce explicit runtime preconditions. |
| inputs / outputs | Boolean plus code/message views; returns or throws public Error. |
| invariants | No retry, fallback or state repair occurs here. |
| ownership | Borrows diagnostics; Error owns copied code/message. |
| failure | False conditions throw; diagnostic construction may itself fail. |
| cost | One branch on success; copied diagnostic bytes/allocation on failure. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 30–32](../../../../../src/runtime/delta.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Failure> [[noreturn]] void delta_present(const Failure& failure) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present typed native failure at existing public construction/restore boundaries. |
| inputs / outputs | Failure with code()/what(); never returns. |
| invariants | Preserves its code and message; does not perform rollback. |
| ownership | Copies diagnostics into public Error after owning scopes unwind. |
| failure | Throws Error; allocating diagnostic copies can fail. |
| cost | Error-message/code copy only on failure. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 33–36](../../../../../src/runtime/delta.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t add_size(std::size_t left,std::size_t right) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add host size accounting without wrap. |
| inputs / outputs | Two size_t operands return their checked sum. |
| invariants | Used before spool/image cardinality publication. |
| ownership | Plain private descriptors; this declaration creates no runtime work authority. |
| failure | resource_limit when addition overflows. |
| cost | Constant comparison/addition. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 37–40](../../../../../src/runtime/delta.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t slots_size(std::size_t count,std::size_t width) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Multiply spool slot count by nonzero allocation width without wrap. |
| inputs / outputs | Count and internal nonzero width return bytes. |
| invariants | Current caller passes allocation_bytes(sizeof(Spool::Node),alignof(Node)); width is never zero. |
| ownership | Plain private descriptors; this declaration creates no runtime work authority. |
| failure | resource_limit when product overflows; zero width is outside this private helper contract. |
| cost | Constant division/check/multiply. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 41–60](../../../../../src/runtime/delta.cpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhaseTimer {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate optional disjoint phase timing with scoped RAII. |
| inputs / outputs | Counter reference, shared observer and optional nested counter; destructor adds clamped elapsed-minus-child duration. |
| invariants | Off/counters never read a clock; pause time outside scoped calls is absent. Parent subtraction prevents additive double counting; metrics are diagnostic. |
| ownership | Borrows counters valid for scope; retains observer while timing. |
| failure | Constructor/destructor use the observer noexcept clock interface and saturating arithmetic; no catch or production retry. |
| cost | Fixed optional start/stop clock reads and integer work; excludes uninstrumented API/final-owner teardown. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0007

[Lines 61–63](../../../../../src/runtime/delta.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRuntime::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own Delta coordination around one physical Boolean runtime. |
| inputs / outputs | Private Impl type; subordinate factors/L/pending stages and public facade definitions follow. |
| invariants | PhysicalRuntime owns source/derivation/local S/P/E; Impl owns global live-factor state and output barrier. |
| ownership | Shared Impl keeps physical/program/account alive across pending/output facade moves. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Type boundary only; retained members and algorithms are specified separately. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 64–74](../../../../../src/runtime/delta.cpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Factor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one parent-before-child C* factor descriptor. |
| inputs / outputs | Node/scope/parent plus separator positions, head positions and ordered child ranks. |
| invariants | Node ID is not enumeration rank; scope and head map concern full visible E keys. |
| ownership | Scope borrows retained CompiledProgram; native metadata vectors use factor-attributed original account. |
| failure | Later vector growth can reject allocation; partial construction unwinds. |
| cost | Empty vector setup; constructor loop fills per-factor widths/children in Impl. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 75–82](../../../../../src/runtime/delta.cpp#L75); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LiveParentSupport {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store an exact live separator bucket and its complete keys. |
| inputs / outputs | uint64 value and accounted row set, optional lifetime classification, equality. |
| invariants | value equals distinct rows.size() at callback boundaries; this live-parent/child count differs from local support P. |
| ownership | Bucket rows own account-funded complete keys; classification visits nested rows. |
| failure | Creation/growth follows account limits; invariant-preserving undo uses compatible allocation-free node transfers. |
| cost | Empty setup is fixed; set_lifetime and equality can visit the entire bucket. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0010

[Lines 83–84](../../../../../src/runtime/delta.cpp#L83); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using ParentCounts=detail::AccountedRowMap<LiveParentSupport>;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name live separator maps and stage-before restoration maps. |
| inputs / outputs | ParentCounts maps separators to count/complete-key sets; RemovedParents holds one map per factor. |
| invariants | Parent maps group L-parent keys; child_index groups L-child keys; removed maps are stage-local comparison-policy inverses. |
| ownership | All map/key/row nodes retain their supplied original account. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Aliases have no execution cost; ordered operations and key widths remain explicit. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 85–102](../../../../../src/runtime/delta.cpp#L85); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LiveImage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct empty global L and both live separator indexes. |
| inputs / outputs | Original account plus factor span allocates three per-factor container arrays; totals start zero. |
| invariants | Root index slots exist but remain empty; factors are filled top-down by build_live or affected updates. |
| ownership | Arrays use coordinator attribution; each nested set/map uses its factor node attribution. |
| failure | Reserve/metadata allocation failure unwinds the unpublished image. |
| cost | O(number of factors) empty-container setup and retained descriptors; no E population scan. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 103–107](../../../../../src/runtime/delta.cpp#L103); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProductiveQueue {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own ordered productive replay witnesses. |
| inputs / outputs | Moves factor row sets and tracks total queued keys. |
| invariants | Queue tracks eligible unprocessed C keys, excluding the separately extracted active witness. |
| ownership | Native queued keys and container arrays are stage-owned. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Move construction transfers established arrays; later queue work follows changed keys. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 108–129](../../../../../src/runtime/delta.cpp#L108); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct LiveTransaction;
  struct AnchoredCursor;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain configuration, physical owner and live-cache authority. |
| inputs / outputs | Requested/resolved completion, physical/observer/workload, layouts, factor/rank arrays, L pointer/tag, mode/build metrics and lifecycle/barrier flags. |
| invariants | processing blocks tentative reads; output_active blocks writes after commit. options.mode is requested initial mode while mode is current. |
| ownership | Physical/program/account outlive borrowed workload and factor spans; shared live image retains native keys. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Per-node/rank immutable descriptors plus actual L/P/B state; no full answer relation. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 130–131](../../../../../src/runtime/delta.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Source> Impl(Source plan,DeltaOptions value,std::shared_ptr<detail::StorageWorkContext> context)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate plan construction into the Delta owner. |
| inputs / outputs | Source plan, DeltaOptions and existing storage context construct PhysicalRuntime then Impl. |
| invariants | Reuses context authority; no nested independent account or work refill. |
| ownership | Moves source/physical state into an unpublished Impl. |
| failure | Physical validation/allocation errors unwind complete members. |
| cost | Physical admission plus factor metadata construction; no populated live bootstrap here. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 132–174](../../../../../src/runtime/delta.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Impl(PhysicalRuntime owner,DeltaOptions value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate Delta policies and compile factor/separator/head routing. |
| inputs / outputs | Physical owner and options initialize layouts, factors, node-to-rank map and child lists. |
| invariants | Automatic replay requires row-coupled live maintenance; explicit replay rejects other policies. Factor order must be parent-before-child and every visible variable must appear in core head. |
| ownership | Retains physical/account; all metadata vectors use that account, while scopes borrow immutable compiled spans. |
| failure | invalid_options/runtime_contract and allocation failures unwind the unpublished owner. |
| cost | O(plan node count) rank sizing; head searches per visible variable and parent-scope lower_bound per child variable; O(factor scopes+edges) retained routing. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 175–177](../../../../../src/runtime/delta.cpp#L175); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L177:sha256:1faa1d25c5548dccf56208e6da6ea7bfdb33bd48867dfe6863d1b85580900c0b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void observe_configuration(bool initial=false) noexcept\`: Called only after successful construction or a semantic mode switch. Bootstrap runs before initial binding, with temporarily adjusted build budgets; those temporary budgets must never become the retained identity. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/delta.cpp:L178; use that declaration for the actual input/output shape. |
| invariants | The source note states: Called only after successful construction or a semantic mode switch. Bootstrap runs before initial binding, with temporarily adjusted build budgets; those temporary budgets must never become the retained identity. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Called only after successful construction or a semantic mode switch. Bootstrap runs before initial binding, with temporarily adjusted build budgets; those temporary budgets must never become the retained identity. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0017

[Lines 178–195](../../../../../src/runtime/delta.cpp#L178); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observe_configuration(bool initial=false) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish effective requested/resolved mode identity after successful construction/switch. |
| inputs / outputs | initial flag captures fixed ObservationConfiguration and workload modes. |
| invariants | Constructor bootstrap skips an absent prior observation identity; semantic switch increments generation with saturation. Restored ordinary options identify the runtime. |
| ownership | Mutates established observer/workload only; no row or new grant. |
| failure | noexcept observer/configuration capture path; impossible internal contract failures terminate. |
| cost | Fixed registry/configuration-size work; test builds may seed initial generation. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0018

[Lines 196–196](../../../../../src/runtime/delta.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void readable() const { require(!processing,"runtime_busy","delta epoch preparation is active"); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject public state reads during tentative preparation. |
| inputs / outputs | Reads processing flag. |
| invariants | Committed output alone does not block ordinary reads. |
| ownership | Borrows Impl. |
| failure | runtime_busy when processing is true. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 197–199](../../../../../src/runtime/delta.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void writable() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require the full writer barrier. |
| inputs / outputs | Combines readable(), no committed-output owner and physical.ready(). |
| invariants | Pending epoch, committed output and result/view leases all prevent writes, including mode changes. |
| ownership | Borrows existing state. |
| failure | runtime_busy; guard failure itself does not abort any existing owner. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 200–206](../../../../../src/runtime/delta.cpp#L200); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge(DeltaMetrics& metrics,std::uint64_t amount=1) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit the cumulative per-epoch Delta work cap. |
| inputs / outputs | Metrics and amount; checked work increases on success. |
| invariants | No overflow and no limit refill between steps; zero remains a real zero allowance. |
| ownership | Mutates caller metrics only; nested storage/cursor/build grants remain separate. |
| failure | resource_limit before this increment; outer pending failure owner aborts unpublished mutation. |
| cost | Constant arithmetic; this logical debit does not account every comparison/byte/destructor cost. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 207–209](../../../../../src/runtime/delta.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metric(DeltaMetrics& metrics,std::uint64_t& counter,std::uint64_t amount=1) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit one named Delta work category. |
| inputs / outputs | Metrics, referenced counter and amount increase after charge succeeds. |
| invariants | Category is a subset of cumulative work; no double-grant creation. |
| ownership | Counter must belong to this metrics instance. |
| failure | charge failure propagates before category increment. |
| cost | Fixed arithmetic; category units are abstract actions rather than allocator bytes. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 210–210](../../../../../src/runtime/delta.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& memory() const noexcept{return physical.plan().account();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original query memory account. |
| inputs / outputs | Returns physical.plan().account(). |
| invariants | Delta does not create an independent account/cap. |
| ownership | Borrow requires the corresponding retained owner; scalar returns are copied. |
| failure | noexcept; valid private Impl/physical owner required. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 211–217](../../../../../src/runtime/delta.cpp#L211); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RowSets row_sets(std::size_t count,resource::MemoryPurpose purpose=resource::MemoryPurpose::delta_state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create factor-attributed empty row sets for live/changed/removed queues. |
| inputs / outputs | Count, purpose and lifetime; returns accounted vector of native row sets. |
| invariants | Private caller supplies count &lt;= factors.size(); purpose/lifetime classify real allocations. |
| ownership | Coordinator-funded array; each nested set retains original account and factor attribution. |
| failure | Array reserve/allocation failures unwind the partial vector. |
| cost | O(count) empty containers; no copied rows. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 218–218](../../../../../src/runtime/delta.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static storage::ScalarView scalar(const Row& row,std::size_t field){return storage::borrow_scalar(row.at(field));}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one caller Row scalar for projection. |
| inputs / outputs | Bounds-checked field returns ScalarView. |
| invariants | Value is borrowed only until AccountedRow copies it. |
| ownership | Row/string storage must survive the immediate projection call. |
| failure | std::out_of_range for invalid internal field. |
| cost | Constant descriptor access; string bytes are not copied by this helper. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 219–219](../../../../../src/runtime/delta.cpp#L219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static storage::ScalarView scalar(storage::RowView row,std::size_t field){return row.at(field);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one native row-view scalar for projection. |
| inputs / outputs | RowView and field return bounds-checked ScalarView. |
| invariants | Compiled field positions must match row layout. |
| ownership | Borrows tuple payload during call. |
| failure | RowView bounds/contract errors propagate. |
| cost | Constant scalar descriptor access. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 220–220](../../../../../src/runtime/delta.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static storage::ScalarView scalar(const storage::AccountedRow& row,std::size_t field){return row.view().at(field);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one owned accounted-row scalar for projection. |
| inputs / outputs | AccountedRow and field return view().at(field). |
| invariants | No intermediate standard Row export. |
| ownership | ScalarView borrows the retained row payload. |
| failure | Native row bounds/contract errors propagate. |
| cost | Constant scalar descriptor access. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 221–227](../../../../../src/runtime/delta.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Source>
  storage::AccountedRow project(const Source& row,std::span<const std::size_t> fields,DeltaMetrics& metrics,std::uint64_t& counter) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a typed selected-field key into the original account. |
| inputs / outputs | Row-like source, field positions, metrics/category; returns AccountedRow. |
| invariants | Positions preserve the compiled separator/head order; counts every projected field. |
| ownership | Scratch ScalarView array is account-funded; returned row owns copied compact scalar/string payload. |
| failure | Work/field/allocation failure propagates to owning pending/bootstrap/inspection boundary. |
| cost | O(projected fields + copied scalar payload bytes), scratch allocation and exact ordered-key costs at consumers. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 228–230](../../../../../src/runtime/delta.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_start(const SupportRuntime::ResultCursor& cursor,DeltaMetrics& metrics) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge a nested D02 cursor startup into Delta work. |
| inputs / outputs | Cursor startup.work is added to cursor_startup_work and work. |
| invariants | Cursor startup has already happened; Delta exhaustion still aborts the unpublished owner. |
| ownership | Borrows cursor and caller metrics. |
| failure | Delta work cap rejection propagates; no cursor retry/refill. |
| cost | Constant metric transfer, plus the separately executed D02 startup. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0029

[Lines 231–235](../../../../../src/runtime/delta.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::AccountedTuple> cursor_next(SupportRuntime::ResultCursor& cursor,DeltaMetrics& metrics) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a nested D02 cursor and debit its last action. |
| inputs / outputs | next_native() returns owning tuple or end; increments result or termination work. |
| invariants | Termination is charged too; no output-history retention. |
| ownership | Returned native payload owns original-account values independently of cursor. |
| failure | Cursor/native/Delta resource failures propagate; outer pending abort handles mutations. |
| cost | Actual cursor traversal plus fixed accounting; row width/storage comparisons remain additional. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 236–278](../../../../../src/runtime/delta.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<LiveImage> build_live(const SupportRuntime::EpochView& view,DeltaMetrics& metrics,std::size_t retained,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bootstrap/rebuild exact global L and enumerable live indexes top-down. |
| inputs / outputs | Pinned E view, metrics and retained-image sizes return a new unpublished LiveImage. |
| invariants | L_root=E_root; L_child is E_child semijoin L_parent on separator under admitted downward totality. Each nonroot P/B bucket count equals its complete-key set size; local S/P/E are not modified. |
| ownership | Owns new full L/P/B image in original account; old committed/working images remain retained until chosen publication. |
| failure | Support/count/work/allocation failure discards the new image; mode/committed owner changes only after success. |
| cost | Scans each E factor and each live parent once per outgoing factor edge; projects/copies complete keys into L and indexes. Charge ordered comparisons, widths, allocation and retained old/new images even when output delta is empty. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.2 Live views, Lemma 5.5, PDF p. 7](https://arxiv.org/pdf/2301.04003v2) |

## B0031

[Lines 279–282](../../../../../src/runtime/delta.cpp#L279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool scalar_sql() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect normalized scalar EXISTS SQL output. |
| inputs / outputs | Requested view plus normalized wrapper return Boolean. |
| invariants | Core view and unnormalized direct CQ use ordinary core-row mapping. |
| ownership | Borrows immutable plan/options. |
| failure | Valid private Impl assumed; no allocation/recovery. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 283–298](../../../../../src/runtime/delta.cpp#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::Tuple map_result(storage::AccountedTuple core,DeltaMetrics& metrics) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map one accepted core assignment to owning selected output. |
| inputs / outputs | Core tuple and metrics; returns core transfer or ordered/repeated SQL columns/constants. |
| invariants | DISTINCT normalized head mapping preserves complete admitted core assignments; scalar EXISTS is handled once at epoch finalization. |
| ownership | Core branch transfers existing payload; SQL branch builds account-funded ScalarView scratch and a native output tuple. |
| failure | Field/layout/work/allocation failures remain unpublished and propagate to pending rollback. |
| cost | O(output fields + copied payload bytes); mapping scratch can allocate before spool quota admission. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/delta_transition_spec.md §SQL output and event order](../../../../delta_transition_spec.md) |

## B0033

[Lines 299–303](../../../../../src/runtime/delta.cpp#L299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::Tuple scalar_result(bool answer) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the scalar EXISTS replacement value. |
| inputs / outputs | Truth Boolean returns one-field native SQL tuple. |
| invariants | Finalization emits erase old truth then insert new truth, independently of input sign. |
| ownership | Returned tuple owns original-account output payload. |
| failure | Native layout/resource failure aborts preparation before publication. |
| cost | One scalar tuple/control allocation; no result enumeration. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0034

[Lines 304–306](../../../../../src/runtime/delta.cpp#L304); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRuntime::Impl::LiveTransaction {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own affected global-live undo separately from physical/local support undo. |
| inputs / outputs | Private LiveTransaction definition. |
| invariants | One same-sign physical epoch spans all stages; reverse order restores exact live keys and index counts. |
| ownership | Pending owner retains LiveTransaction and image; destructor aborts uncommitted work. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Type boundary only; affected undo and native row payloads follow real mutations. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0035

[Lines 307–307](../../../../../src/runtime/delta.cpp#L307); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Kind { insert_live, erase_live, insert_separator, change_separator, erase_separator };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish exact live and separator inverse forms. |
| inputs / outputs | Five enum cases for inserted/extracted live and outer/inner separator mutations. |
| invariants | Positive count changes differ from membership zero crossings. |
| ownership | Plain private descriptors; this declaration creates no runtime work authority. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Compile-time enum only. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 308–322](../../../../../src/runtime/delta.cpp#L308); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Undo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one inverse record without copying whole live state. |
| inputs / outputs | Linked previous node; live/index iterators or extracted nodes, mapped pointer, prior count and child-side tag. |
| invariants | Reverse undo restores later extracted outer nodes before older mapped addresses are used. |
| ownership | Original account owns record/extracted keys; iterators/pointers refer to stable tree nodes retained by image or later undo. |
| failure | Record allocation precedes protected mutation; impossible inverse mismatch terminates during noexcept cleanup. |
| cost | One affected record; extracted node transfer avoids bucket/full-state copies. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0037

[Lines 323–323](../../../../../src/runtime/delta.cpp#L323); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Event { std::size_t factor; const storage::AccountedRow* row; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Queue a stable changed live key for child propagation. |
| inputs / outputs | Factor rank plus pointer to inserted row or undo-owned extracted row. |
| invariants | Event is copied before appending to pending vector; vector growth cannot invalidate row owner. |
| ownership | Borrowed row pointer remains valid under image/undo until stage drain/abort. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Fixed pointer/rank event; capacity growth is accounted. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0038

[Lines 324–333](../../../../../src/runtime/delta.cpp#L324); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Impl& runtime;
  DeltaMetrics& metrics;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain live image, affected events and stage-before comparison keys. |
| inputs / outputs | Runtime/metrics borrows, image, undo chain, pending vector, removed maps and peak/closed counters. |
| invariants | Replay sets retain_before=false and avoids stage-before row copies; comparison paths retain only affected removed rows. |
| ownership | Vectors/maps/undo use original account; image is shared with working/committed owner behind busy barrier. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | O(affected mutations/events/removed keys) retention; no committed full-state copy for non-eager paths. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0039

[Lines 334–342](../../../../../src/runtime/delta.cpp#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
LiveTransaction(const Impl& owner,DeltaMetrics& work,std::shared_ptr<LiveImage> state)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize affected-live transaction ownership. |
| inputs / outputs | Runtime, metrics and current live image; sets replay restoration policy and per-factor removed maps. |
| invariants | Valid Delta mode supplies a current image; no live rows change at construction. |
| ownership | Retains image; all scratch/undo/restoration maps share original account. |
| failure | Reserve/setup failure unwinds members before processing starts. |
| cost | O(number of factors) empty-map construction; no L population copy. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0040

[Lines 343–343](../../../../../src/runtime/delta.cpp#L343); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~LiveTransaction() { rollback(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort uncommitted live mutations on owner destruction. |
| inputs / outputs | Destructor invokes idempotent rollback. |
| invariants | Committed/previously rolled-back transaction is closed and does nothing. |
| ownership | Destroys affected undo/event/restoration storage after inverse restoration. |
| failure | noexcept cleanup; corrupt private inverse invariants terminate. |
| cost | O(affected undo with ordered restore and owned-payload cleanup); no throwing production. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0041

[Lines 344–351](../../../../../src/runtime/delta.cpp#L344); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::AccountedUnique<Undo> prepare(Kind kind,std::size_t factor,bool child_side=false) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate and charge one live inverse before mutation. |
| inputs / outputs | Kind, factor and side return an unlinked AccountedUnique&lt;Undo&gt;. |
| invariants | Record is not attached until protected mutation can be reversed. |
| ownership | Factor-attributed original-account journal_undo control; local token destroys unused preparation. |
| failure | Work/account/allocation failure leaves this protected state unchanged; enclosing pending still aborts prior work. |
| cost | Fixed record allocation/action; caller later stores affected node/key state. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0042

[Lines 352–354](../../../../../src/runtime/delta.cpp#L352); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void record(resource::AccountedUnique<Undo> item) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish a prepared inverse to the intrusive undo chain. |
| inputs / outputs | Owning Undo becomes new head; entry count increments. |
| invariants | No allocation/throw lies between protected mutation and record publication. |
| ownership | Moves unique owners; previous records remain retained. |
| failure | noexcept; caller supplies a prepared valid record and bounded entry count. |
| cost | Constant pointer moves, no recursive teardown. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0043

[Lines 355–355](../../../../../src/runtime/delta.cpp#L355); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare_commit() { runtime.metric(metrics,metrics.finalization_undo_entries,undo_entries); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Precharge later live undo disposal before the commit barrier. |
| inputs / outputs | Adds undo_entries to finalization_undo_entries/work. |
| invariants | Does not clear undo or commit state yet. |
| ownership | Borrows chain count. |
| failure | Delta cap rejection still permits complete rollback. |
| cost | Constant aggregate debit representing affected entries; actual node/key destruction follows commit. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0044

[Lines 356–363](../../../../../src/runtime/delta.cpp#L356); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void peak() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record retained live/index high-water sizes. |
| inputs / outputs | Current plus extracted/copied counts update peak metrics. |
| invariants | Retained deleted nodes and stage-before comparison copies count in peaks. |
| ownership | Scalar metrics only; does not allocate extra state. |
| failure | add_size overflow propagates to pending failure owner. |
| cost | Constant checked arithmetic. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0045

[Lines 364–395](../../../../../src/runtime/delta.cpp#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback() noexcept {
    if (closed) return;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reverse all uncommitted L/P/B changes without allocation. |
| inputs / outputs | Iteratively consumes inverse chain; clears pending and marks closed. |
| invariants | Reinserts extracted nodes into original domain, restores prior counts and updates image totals. Later outer extractions reverse before older saved mapped pointers. |
| ownership | Transfers retained node ownership back; closes each record iteratively. |
| failure | noexcept; missing count or duplicate reinsertion terminates instead of hiding corruption. |
| cost | O(undo entries times ordered-tree/key costs) plus payload cleanup; no complete L scan/copy. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0046

[Lines 396–403](../../../../../src/runtime/delta.cpp#L396); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retire committed live undo. |
| inputs / outputs | Iteratively releases inverse chain and pending events; closes transaction. |
| invariants | Live image already reflects final state; no inverse is applied. |
| ownership | Extracted dead rows/index nodes are finally destroyed under original account. |
| failure | noexcept; impossible undo count inconsistency terminates. |
| cost | O(affected undo and nested payload destruction), precharged before publication. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0047

[Lines 404–444](../../../../../src/runtime/delta.cpp#L404); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Source>
  void change(std::size_t factor,const Source& key,bool add,RowSets& removed,ProductiveQueue* productive=nullptr) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one real global live-key membership crossing. |
| inputs / outputs | Factor/key/sign, stage removed sets and optional productive queue. |
| invariants | No-op membership stops locally. Real crossing updates L totals, child B index, deletion queue pruning and stable outgoing event. |
| ownership | Inserted rows are image-owned; extracted deleted rows remain undo-owned; comparison copies are stage-owned. |
| failure | Every protected mutation has its inverse; later work/allocation failure requires whole pending rollback. |
| cost | Ordered membership/insert/extract, one affected inverse, key payload copy on insertion/comparison deletion, B separator projection and optional queue lookup; no unrelated E scan. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0048

[Lines 445–499](../../../../../src/runtime/delta.cpp#L445); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class ParentRow>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Change one live parent/child separator support and complete-key index. |
| inputs / outputs | Child rank, separator, complete row, sign and side; returns whether support crossed zero. |
| invariants | value equals row count after success. New outer node is journaled before inner insertion; positive-to-positive change does not trigger bucket propagation. Local Support P is unrelated. |
| ownership | Retains exact extracted inner/outer nodes and previous scalar for nonallocating undo; only comparison parent deletion copies stage-before rows. |
| failure | Overflow/missing/duplicate/work/resource failures propagate to complete pending rollback. |
| cost | O(ordered separator and row-tree operations + projected/complete key widths); affected inverse/copies only. Outer extract at last support holds one row; general lifetime classification itself visits nested rows. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0049

[Lines 500–507](../../../../../src/runtime/delta.cpp#L500); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void end_stage() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release stage-before parent restoration keys after producer closes. |
| inputs / outputs | Clears removed_parents and resets its copied-row total. |
| invariants | Restoration belongs only to this route; replay has no retained restoration rows but charges per-factor cleanup. |
| ownership | Frees copied separator/parent keys; physical epoch undo remains retained. |
| failure | Work precharges may throw; pending failure boundary then rolls back all state. |
| cost | Visits factor maps and actual copied rows/payloads; records cleanup separately. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0050

[Lines 508–511](../../../../../src/runtime/delta.cpp#L508); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void begin_stage() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a route with no prior restoration/event state. |
| inputs / outputs | Runs end_stage, clears pending, resets per-stage removed-copy count and peak gauges. |
| invariants | Physical driver cannot advance while old stage views/cursors survive. |
| ownership | Retains epoch-wide inverse nodes; only prior-stage scratch is released. |
| failure | Cleanup charge failure aborts pending epoch. |
| cost | O(factors + previous stage restoration payloads), no whole L rebuild. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0051

[Lines 512–538](../../../../../src/runtime/delta.cpp#L512); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void apply(const RowSets& changed,const SupportRuntime::EpochView& context,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain L by affected separator buckets for the incremental policy. |
| inputs / outputs | Changed E keys, immutable selected endpoint view, sign and removed sets. |
| invariants | Insertion admits changed key only with live parent support; real outgoing parent support zero crossings open child E buckets. Pending events grow iteratively. |
| ownership | All state changes journal through change/separator; bucket cursor owns endpoint lease until exhausted. |
| failure | Cursor/work/allocation errors require outer pending rollback; no local retry. |
| cost | Changed-key probes plus all affected E bucket rows/edges and projections, L/index inverses and ordered costs. Bucket policy can do substantial pre-enumeration work even with no emitted delta. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0052

[Lines 539–566](../../../../../src/runtime/delta.cpp#L539); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void on_output(storage::RowView row,const RowSets& changed,bool add,RowSets& removed,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Couple exact L/P/B maintenance to one accepted core answer. |
| inputs / outputs | Answer row, changed sets/sign, removed sets, optional replay anchor and productive queue. |
| invariants | Visits factors parent-before-child; updates outgoing parent support before descendant projection. Replay own-E erasure tests only active anchor, preserving future queued anchors; zero parent support also removes descendants. |
| ownership | Projects owning accounted keys; every live/index crossing is epoch-journaled; no result-history cache. |
| failure | Work/projection/allocation failure aborts whole unpublished epoch. |
| cost | Projects each factor and updates only real L/P/B crossings/queues; no E bucket scan. Deletion completeness relies on local freshness/mixed-state proof, not witness count suppression. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.2 Live views, Lemma 5.5, PDF p. 7](https://arxiv.org/pdf/2301.04003v2) |

## B0053

[Lines 567–571](../../../../../src/runtime/delta.cpp#L567); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRuntime::Impl::AnchoredCursor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement full-key Delta completions with rerooted traversal. |
| inputs / outputs | Private AnchoredCursor type for anchored canonical and ordered replay. |
| invariants | General partial/hidden D02 completion semantics stay in SupportRuntime; copied indexed keys survive live mutation. |
| ownership | Stage owns heap-stable cursor; runtime/view/image are valid borrows for its lifetime. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Type boundary; descriptor setup and advances follow below. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0054

[Lines 572–572](../../../../../src/runtime/delta.cpp#L572); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Step { std::size_t factor; std::optional<std::size_t> from; std::size_t edge; bool upward; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe one rerooted C* traversal edge. |
| inputs / outputs | Factor rank, prior step index, original child-edge rank and upward flag. |
| invariants | Every factor appears once; prior step already selected. |
| ownership | Fixed private descriptor; no rows. |
| failure | Declaration only. |
| cost | O(number of factors) descriptor array. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0055

[Lines 573–578](../../../../../src/runtime/delta.cpp#L573); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one anchored traversal frame. |
| inputs / outputs | Owning selected tuple/separator and optional downward E cursor; opened flag. |
| invariants | No live-index iterator survives callbacks; successor lookup is reconstructed from last owned tuple. |
| ownership | Selected payload and endpoint cursor keep original account/lease alive. |
| failure | Frame destruction releases cursor/payload without producing rows. |
| cost | One frame per factor plus actual open cursor and selected widths. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0056

[Lines 579–592](../../../../../src/runtime/delta.cpp#L579); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Impl& runtime;
  const SupportRuntime::EpochView& target;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Save full-key cursor position without output history. |
| inputs / outputs | Runtime/target/image/restoration borrows, metrics, steps/positions/frames/subtree mask, replay/work/carry flags. |
| invariants | Live index outside active replay anchor subtree stays exact/immutable; target E is pinned chosen endpoint. |
| ownership | Native cursor arrays are original-account funded; borrowed context belongs to Stage/transaction. |
| failure | Valid owner/view lifetime is required; public failure boundary closes cursor. |
| cost | O(number of factors + selected key widths/open D02 frames) retained state. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0057

[Lines 593–598](../../../../../src/runtime/delta.cpp#L593); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void note(std::uint64_t& counter,std::uint64_t amount=1) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit anchored cursor lifetime and enclosing Delta work. |
| inputs / outputs | Counter/amount increase only after both caps pass. |
| invariants | Cursor work is cumulative across next calls; storage allowance and Delta grant are not refilled. |
| ownership | Mutates established cursor and epoch metrics. |
| failure | resource_limit before this increment; underlying cursor may already have spent work. |
| cost | Constant checked arithmetic; ordered comparisons and payload bytes are additional. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0058

[Lines 599–604](../../../../../src/runtime/delta.cpp#L599); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedRow project(storage::RowView row,std::span<const std::size_t> fields) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a separator projection for anchored traversal. |
| inputs / outputs | Native row and compiled positions return AccountedRow. |
| invariants | Counts fields in anchor_fields and both work limits. |
| ownership | Scratch descriptor array and returned compact key use original account. |
| failure | Projection/work/allocation errors propagate to public pending rollback. |
| cost | O(fields + payload bytes) and scratch allocation. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0059

[Lines 605–608](../../../../../src/runtime/delta.cpp#L605); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::AccountedLayout& layout(std::size_t factor) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a factor visible-relation layout. |
| inputs / outputs | Rank maps through compiled node visible relation. |
| invariants | Admitted C* node has a visible relation and matching full-key scope. |
| ownership | Layout belongs to retained immutable program. |
| failure | Valid compiled metadata/rank required; no independent guard or allocation. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0060

[Lines 609–644](../../../../../src/runtime/delta.cpp#L609); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
AnchoredCursor(const Impl& owner,const SupportRuntime::EpochView& view,const LiveImage& state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a full-key rerooted cursor and anchor frame. |
| inputs / outputs | Owner/view/live/restoration, metrics, full anchor key and replay selector. |
| invariants | Iterative undirected-tree traversal covers C* once; replay marks original anchor subtree so outside downward edges read child L indexes. |
| ownership | Account funds O(factors) arrays/scratch and owning anchor tuple; endpoint/image are borrowed. |
| failure | Bad coverage, work cap or allocation failure unwinds partial arrays/cursors before enclosing abort. |
| cost | Visits factor topology; replay adds subtree scan; O(factors+anchor width) startup actions and native allocations. No full answer materialization. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0061

[Lines 645–667](../../../../../src/runtime/delta.cpp#L645); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::AccountedTuple> indexed_next(const Step& step,Frame& frame,bool child_side) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the next complete indexed key without retaining an iterator. |
| inputs / outputs | Step/frame and index side; returns copied tuple or end. |
| invariants | Fresh successor lookup merges current and comparison deletion-restored parent buckets by strict upper_bound(last); replay child reads current B only. |
| ownership | Frame owns separator/last tuple; selected tree row is borrowed only until layout tuple copy. |
| failure | Work/native tuple allocation failure propagates; undo remains available. |
| cost | Fixed number of separator/successor tree probes and key comparison/copy bytes per selection; O(log bucket/state) comparisons. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0062

[Lines 668–686](../../../../../src/runtime/delta.cpp#L668); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::AccountedTuple> select(std::size_t index) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open or advance one rerooted factor frame. |
| inputs / outputs | Step index chooses parent L, replay outside child L, or pinned endpoint E bucket. |
| invariants | A newly opened productive bucket has a first row by admitted totality/live invariant; root-first general searches use another path. |
| ownership | Downward cursor retains endpoint lease; all returned tuples own payload. |
| failure | Work/cursor/resource errors propagate to pending failure owner. |
| cost | Separator projection and bounded index/cursor actions; actual D02 action and value widths counted separately. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0063

[Lines 687–714](../../../../../src/runtime/delta.cpp#L687); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::AccountedTuple> next() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate one complete assignment from a full-key fragment. |
| inputs / outputs | Saved carry position returns native core tuple or repeated end. |
| invariants | Each suffix starts productive; backtracking carries across at most fixed-query frames. Output slots preserve ordered/repeated core head. |
| ownership | Owns frames/tuples, no emitted-answer history; successful next retains carry state across pause. |
| failure | Failed invariant/work/allocation leaves cleanup to enclosing pending rollback. |
| cost | Fixed-query bounded candidate actions after construction, including suffix/output-field walks; O(log indexed populations), widths/allocation and O(frames) termination release remain explicit. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0064

[Lines 715–718](../../../../../src/runtime/delta.cpp#L715); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRuntime::Epoch::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own prepared/committed output and its physical input artifact. |
| inputs / outputs | Epoch::Data with nested FIFO Spool. |
| invariants | Rows stay private until PendingEpoch commit; delivery lease is independent of retained input/journal history. |
| ownership | Shared Data can outlive facade during callbacks; account-funded spool and native tuple payloads. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Type boundary only; per-record and final-owner costs below. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0065

[Lines 719–723](../../../../../src/runtime/delta.cpp#L719); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Node {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one prepared signed record and FIFO link. |
| inputs / outputs | SignedResult and next pointer; noexcept move construction. |
| invariants | Ordinal/value are prepared before linking; no result-dependent contiguous buffer reallocation. |
| ownership | Node owns native tuple payload through SignedResult. |
| failure | Move trait asserted before node construction; incompatible type change fails compilation. |
| cost | One node plus prepared native payload per retained record. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0066

[Lines 724–727](../../../../../src/runtime/delta.cpp#L724); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAllocator<Node> allocator;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain FIFO allocation authority and endpoints. |
| inputs / outputs | Original-account Node allocator, head/tail and count. |
| invariants | count matches linked nodes; empty implies no head/tail. |
| ownership | Allocator retains original query account independently of runtime facade. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Fixed FIFO control; actual nodes are accounted output_buffer storage. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0067

[Lines 728–729](../../../../../src/runtime/delta.cpp#L728); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Spool(const resource::MemoryAccount& account)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind output FIFO to original account. |
| inputs / outputs | MemoryAccount constructs an empty Spool. |
| invariants | No per-spool account/cap is created; row/byte sublimits are enforced by append. |
| ownership | Allocator owns account authority; nodes start absent. |
| failure | Allocator construction follows account validity; no node allocated yet. |
| cost | Fixed empty setup. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0068

[Lines 730–731](../../../../../src/runtime/delta.cpp#L730); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Spool(const Spool&)=delete;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forbid accidental FIFO copying. |
| inputs / outputs | Deleted copy constructor and assignment. |
| invariants | Only Epoch Data owns/deletes each raw linked node. |
| ownership | No shared raw-node ownership is introduced. |
| failure | Copy attempts fail compilation. |
| cost | No runtime work. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0069

[Lines 732–732](../../../../../src/runtime/delta.cpp#L732); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Spool() { clear(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release all unread FIFO nodes on destruction. |
| inputs / outputs | Destructor invokes iterative clear. |
| invariants | No exception starts production/draining. |
| ownership | Destroys each SignedResult and deallocates its node. |
| failure | noexcept cleanup. |
| cost | Linear in unread nodes and last-owner payload destruction. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0070

[Lines 733–733](../../../../../src/runtime/delta.cpp#L733); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::size_t size() const noexcept { return count; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained FIFO row count. |
| inputs / outputs | Returns count size_t. |
| invariants | Prepared high-water metrics are separate from remaining count. |
| ownership | Scalar copy. |
| failure | noexcept. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0071

[Lines 734–734](../../../../../src/runtime/delta.cpp#L734); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] bool empty() const noexcept { return count==0; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether FIFO has unread rows. |
| inputs / outputs | Returns count==0. |
| invariants | head/tail/count invariant is maintained internally. |
| ownership | Scalar copy. |
| failure | noexcept. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0072

[Lines 735–735](../../../../../src/runtime/delta.cpp#L735); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SignedResult& front() noexcept { return head->value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the first unread signed record. |
| inputs / outputs | Returns head-&gt;value by mutable reference. |
| invariants | Private callers ensure nonempty; next/delivery borrowing is serialized by delivering flag. |
| ownership | Borrow lasts only until pop/clear and callback guard end. |
| failure | noexcept; empty access violates private precondition. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0073

[Lines 736–743](../../../../../src/runtime/delta.cpp#L736); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void push_back(SignedResult value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one already prepared record without copying history. |
| inputs / outputs | SignedResult moves into a fresh account-funded node and links FIFO tail. |
| invariants | All potentially throwing node allocation occurs before link publication; SignedResult transfer is statically noexcept. |
| ownership | Node owns tuple; original account funds allocation. |
| failure | Allocation failure leaves FIFO topology/count unchanged. |
| cost | One allocation and fixed pointer updates; native tuple was built before this operation. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0074

[Lines 744–747](../../../../../src/runtime/delta.cpp#L744); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pop_front() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release the first unread FIFO node. |
| inputs / outputs | Private nonempty FIFO advances head, destroys/deallocates old node, updates tail/count. |
| invariants | No other retained-node relocation or allocation. |
| ownership | Moved-out result can keep payload alive after node deletion. |
| failure | noexcept; nonempty private precondition. |
| cost | Fixed link/node work plus final payload-owner destruction if still stored. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0075

[Lines 748–748](../../../../../src/runtime/delta.cpp#L748); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear() noexcept { while (head) pop_front(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Iteratively discard remaining FIFO output. |
| inputs / outputs | Repeated pop_front until head is null. |
| invariants | No recursive next-link destruction or implicit producer drain. |
| ownership | Releases unread node/payload ownership. |
| failure | noexcept. |
| cost | O(unread node count + final native payload teardown), no allocation. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0076

[Lines 749–763](../../../../../src/runtime/delta.cpp#L749); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<Impl> owner;
  std::shared_ptr<detail::ObservationState> observation;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain output lease, artifact, summaries and delivery disposition. |
| inputs / outputs | Runtime/observer, optional PhysicalEpoch, layout, metrics/timings, FIFO, stage vector, byte count and callback/discard flags. |
| invariants | Output lease blocks writers only while committed rows remain. Metrics retain prepared high-water after consumption/discard. |
| ownership | Input/journal/layout can outlive runtime delivery lease; native output arrays and payloads retain original account. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Prepared record/stage/affected-input storage; no extra answer-history set. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0077

[Lines 764–766](../../../../../src/runtime/delta.cpp#L764); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observe_output() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish fixed output-disposition metadata when enabled. |
| inputs / outputs | Existing ticket/disposition update observer if not closed. |
| invariants | Once output observation closes, later lifecycle calls cannot change its outcome. |
| ownership | No tuple or new owning history retained. |
| failure | noexcept observer update. |
| cost | Fixed optional registry work. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0078

[Lines 767–770](../../../../../src/runtime/delta.cpp#L767); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
explicit Data(std::shared_ptr<Impl> runtime):owner(std::move(runtime)),observation(owner->observation),layout(owner->output_layout),rows(owner->memory()),
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create output owner and preallocate route summaries. |
| inputs / outputs | Shared Impl constructs Data, account FIFO and stage vector sized to physical inputs. |
| invariants | At most one summary per real route crossing; output remains unpublished. |
| ownership | Retains runtime, observer and owning layout token; original account funds summaries/control. |
| failure | Reserve failure unwinds members before tentative ownership begins. |
| cost | O(physical input routes) summary capacity; no result rows yet. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0079

[Lines 771–771](../../../../../src/runtime/delta.cpp#L771); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data() { finish(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release output owner on final Data destruction. |
| inputs / outputs | Destructor calls finish. |
| invariants | Abort/drain/committed discard semantics are decided earlier; destructor releases retained output only. |
| ownership | Final shared Data release can also destroy input/journals/layout. |
| failure | noexcept cleanup; private lease corruption terminates. |
| cost | Unread FIFO plus any final physical/program/account-owned teardown costs. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0080

[Lines 772–790](../../../../../src/runtime/delta.cpp#L772); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observe() const noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy Delta counters/timings into optional observer. |
| inputs / outputs | Fixed metric registry set calls. |
| invariants | Observations are separate from deterministic work caps; no output payload capture. |
| ownership | Mutates established observer only. |
| failure | noexcept. |
| cost | Fixed number of assignments, immediate return if disabled. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0082

[Lines 792–808](../../../../../src/runtime/delta.cpp#L792); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release committed-output lease and unread records safely. |
| inputs / outputs | If delivering, marks deferred discard; otherwise publishes release, clears owner/barrier and FIFO. |
| invariants | Committed input remains accepted; no source/support/live rollback. Lease ownership mismatch terminates. |
| ownership | Returned rows remain independently owned; input/layout/journals retained until Data destruction. |
| failure | noexcept; callback borrow defers clearing until it ends. |
| cost | Linear unread cleanup and possible final runtime/program destruction; observer counts are diagnostic, not a work grant. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0083

[Lines 809–837](../../../../../src/runtime/delta.cpp#L809); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void append(SetOperation operation,storage::Tuple tuple) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one owning mapped signed record to bounded private output. |
| inputs / outputs | Operation/tuple; appends next one-based ordinal or counts a deliberately discarded mapped record. |
| invariants | Retained tuple must belong to original account; finite row and byte limits include real node allocation request and native tuple request. No record publishes before whole epoch succeeds. |
| ownership | FIFO owns prepared tuple; query account remains authority beyond spool sublimit. |
| failure | Overflow/quota/work/account/allocation rejection propagates to pending rollback. Discard mode skips future spool quota/allocation. |
| cost | Fixed append actions plus tuple accounting; byte formula uses allocation_bytes(Node) and tuple.memory_usage requested bytes. Candidate/mapping scratch, shared metadata and retained input journals are additional. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0084

[Lines 838–855](../../../../../src/runtime/delta.cpp#L838); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void disable_output() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable output retention while preserving required internal drain. |
| inputs / outputs | Precharges unread rows/stages, clears private FIFO, zeroes stage ranges, retains high-water metrics. |
| invariants | Subsequent accepted core rows still couple L/indexes/queues and finish all aliases; this never commits by itself. |
| ownership | Drops owning unread rows, retains pending transaction and summaries. |
| failure | Charge failure occurs before retention state changes and outer start_drain aborts whole pending epoch. |
| cost | O(unread rows+stage count+payload release); charged as finalization and excluded from active replay transition interval. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0085

[Lines 856–883](../../../../../src/runtime/delta.cpp#L856); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRuntime::Impl::Stage {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one heap-stable private route producer across pause/resume. |
| inputs / outputs | Runtime/output/working borrows; endpoint views, selected side, full changed/removed sets, eligibility image, queues and one cursor/witness. |
| invariants | Alias prefix advances only after all these views/cursors retire; changed keys are true E membership crossings. |
| ownership | Stage owns endpoint leases, native key sets and cursor; pending owner outlives its borrows. |
| failure | Partial construction unwinds owned members; later failure uses public pending abort. |
| cost | O(factors + changed/affected keys + active traversal) retention; eager may additionally retain complete images. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md) |

## B0086

[Lines 884–936](../../../../../src/runtime/delta.cpp#L884); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Stage(const Impl& owner,Epoch::Data& result,std::shared_ptr<LiveImage>& state,LiveTransaction* live,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare delta discovery for one private alias prefix from visible E membership changes. |
| inputs / outputs | Before/after views, support journal records, polarity and prefix identity in; changed-factor sets and selected producer state out. |
| invariants | Ignore non-E and unchanged-membership records. E polarity must match this prefix. Ordered replay requires a live transaction and queues only keys productive in the relevant context. |
| ownership | Stage borrows runtime/output/working state and retains epoch views/changed rows/cursors under the pending owner. |
| failure | Constructor may allocate, project and spend work; failure leaves publication to the enclosing pending-epoch rollback boundary. Its partially constructed members unwind normally. |
| cost | Scan journal records; deduplicate changed E keys; replay setup visits factors/changed keys and may populate a productive queue. Startup is not necessarily constant in the public eager-spool API. |
| Design | [docs/delta_transition_spec.md](../../../../delta_transition_spec.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [P1 arXiv:2301.04003v2 §5.2 Algorithm 6, PDF p. 6](https://arxiv.org/pdf/2301.04003v2) |

## B0087

[Lines 937–938](../../../../../src/runtime/delta.cpp#L937); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L937-L938:sha256:3285018f10d1f38d6a2bc7d78bfd0423d5e2a6db6615cedfe816cc56498c79a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void exclude_work(std::uint64_t amount) noexcept\`: Lifecycle-only cleanup is finalization, not producer work. Keep its separately charged cost out of the next/last transition interval. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/delta.cpp:L939; use that declaration for the actual input/output shape. |
| invariants | The source note states: Lifecycle-only cleanup is finalization, not producer work. Keep its separately charged cost out of the next/last transition interval. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Lifecycle-only cleanup is finalization, not producer work. Keep its separately charged cost out of the next/last transition interval. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0088

[Lines 939–939](../../../../../src/runtime/delta.cpp#L939); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exclude_work(std::uint64_t amount) noexcept { if (replay) transition_begin+=amount; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep lifecycle-only drain cleanup outside replay producer intervals. |
| inputs / outputs | Adds already charged cleanup amount to transition_begin only in replay. |
| invariants | Does not refund metrics.work or either work grant. |
| ownership | Scalar accounting under existing stage. |
| failure | noexcept; amount is the actual preceding cleanup debit. |
| cost | Constant arithmetic. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0089

[Lines 940–992](../../../../../src/runtime/delta.cpp#L940); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool open() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the next productive changed full-key witness. |
| inputs / outputs | Saved factor/key/queue position opens anchored or root-first cursor; returns false after all factors. |
| invariants | Replay insertion reverses ranks, deletion uses forward ranks; queues hold eligible keys and extract active witness before cursor creation. Canonical policies skip dead changes and preserve earliest-rank ownership. |
| ownership | Owns extracted active node/cursor and fixed binding scratch; borrows immutable target and eligible live image. |
| failure | Invariant/cursor/resource errors propagate to public step rollback; no hidden skip of a supposedly productive replay anchor. |
| cost | Replay avoids a dead-key tail after preparation; canonical path may scan many changed keys. Cursor setup traverses query descriptors/bindings; root-first may scan unrelated E rows. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0090

[Lines 993–1033](../../../../../src/runtime/delta.cpp#L993); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool next() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce at most one accepted private core row per successful stage next. |
| inputs / outputs | Opens/advances fragment; canonical earlier-factor rejection or replay acceptance; couples L, maps/appends output, records interval work. |
| invariants | Replay has no canonical rejections and preserves conceptual mixed-state ownership; core_result is progress, not publicly delivered SQL record. Scalar EXISTS defers mapping. |
| ownership | Retains traversal/witness across calls; emitted rows are native owned spool payloads only. |
| failure | Any cursor/work/projection/mapping/spool failure reaches public step handler and aborts all aliases. |
| cost | Replay post-preparation first/next/last bounded fixed-query actions, with ordered/value/allocation costs extra. Canonical rejection runs are unbounded in accepted-output terms. |
| Design | [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md) |

## B0091

[Lines 1034–1067](../../../../../src/runtime/delta.cpp#L1034); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish route maintenance and precharge retirement before advancing aliases. |
| inputs / outputs | Drained queue/cursors, view/changed-key/image sizes, stage deltas and range become one summary. |
| invariants | Replay queue must be empty; eager working image changes only after route finishes. All endpoint leases retire when Stage resets. |
| ownership | Clears replay changed keys, retains summary scalars and epoch-wide live undo; replaces working image for eager. |
| failure | Work/account/summary-allocation failure aborts pending epoch before publication. |
| cost | O(changed keys/view-entry bound + compiled tables/indexes), replaced eager image teardown and stage-before cleanup; distinct from producer interval and includes the explicit conservative entry bounds. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md) |

## B0092

[Lines 1068–1084](../../../../../src/runtime/delta.cpp#L1068); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DeltaRuntime::PendingEpoch::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one unpublished physical epoch with independent live/output coordination. |
| inputs / outputs | Shared runtime/output/working image, original StorageWorkLease, optional LiveTransaction/Physical PendingUpdate, stage, sequence/sign/truth/phase/tickets. |
| invariants | One pending owner serializes all routes; processing blocks public state readers until commit/abort. |
| ownership | Native control and live inverse ownership persist across facade moves/destruction. |
| failure | Declaration/default scalar setup has no recovery path. |
| cost | Affected physical/live journals, queued/changed keys, bounded output and one route; no general full database rollback copy. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0093

[Lines 1085–1103](../../../../../src/runtime/delta.cpp#L1085); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<Impl> runtime,const PhysicalUpdateView& update)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire tentative Delta ownership and prepare the physical source event. |
| inputs / outputs | Runtime/update borrow creates output/control, optional non-eager live transaction and physical staged update. |
| invariants | processing/lifecycle become active before begin_staged; constructor catch must reset them because a failed object constructor never runs its destructor. |
| ownership | Retains original storage lease/account, runtime and owned source pin through physical owner. |
| failure | Preactivation member failures unwind normally; begin_staged failure explicitly rolls back Delta flags/tickets/output then rethrows. |
| cost | Control/output/factor scratch setup plus physical source validation/import/probe/constraints. No alias route production yet. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0094

[Lines 1104–1104](../../../../../src/runtime/delta.cpp#L1104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data() { rollback(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort an unpublished pending owner during destruction. |
| inputs / outputs | Destructor invokes rollback. |
| invariants | Never drains or publishes on destruction. |
| ownership | Retained runtime permits abort after facade destruction. |
| failure | noexcept, idempotent after commit/abort. |
| cost | Affected stage/view/physical/live undo and output teardown. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0095

[Lines 1105–1105](../../../../../src/runtime/delta.cpp#L1105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool active() const noexcept { return owner && physical && physical->active(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether pending Data still owns an active physical transaction. |
| inputs / outputs | Requires owner, physical token and physical.active(). |
| invariants | Committed/aborted Data stays inspectable but inactive. |
| ownership | Scalar copy. |
| failure | noexcept; established token ownership assumed. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0096

[Lines 1106–1106](../../../../../src/runtime/delta.cpp#L1106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate() const { require(active(),"invalid_delta_epoch","pending delta epoch is closed"); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an open pending transaction. |
| inputs / outputs | active() check before public lifecycle action. |
| invariants | Closing tokens cannot be restarted/refilled. |
| ownership | Borrows Data. |
| failure | invalid_delta_epoch when closed. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0097

[Lines 1107–1107](../../../../../src/runtime/delta.cpp#L1107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void set_phase(DeltaState value) noexcept { phase=value; owner->lifecycle=value; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish pending phase to both token and runtime lifecycle. |
| inputs / outputs | Assigns phase and owner-&gt;lifecycle. |
| invariants | Only active Data calls it; no source/live mutation. |
| ownership | Scalar updates under single writer. |
| failure | noexcept; active owner required. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0098

[Lines 1108–1124](../../../../../src/runtime/delta.cpp#L1108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback() noexcept {
    if (!owner) return;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort entire unpublished Delta epoch in dependency order. |
| inputs / outputs | Closes stage/cursors/views, physical source/count/support undo, then independent live undo; clears working/output/flags and finishes aborted tickets. |
| invariants | Public ready/previous sequence reappear only after complete restoration. Repeated abort after owner reset is harmless. |
| ownership | Releases original account-backed controls/events/keys and final runtime owner as applicable. |
| failure | noexcept; impossible private ownership/inverse faults terminate. |
| cost | O(affected physical/live/view/output cleanup), plus final-owner teardown; no result enumeration or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0099

[Lines 1125–1159](../../../../../src/runtime/delta.cpp#L1125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finalize() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare final mapped output and all commit cleanup debits. |
| inputs / outputs | If scalar truth flips, appends erase-old/insert-new; updates gauges and precharges physical/live/eager retirement. |
| invariants | Only after all physical routes and stage producers retire can phase become epoch_prepared. Every throwing check remains before publication. |
| ownership | Retains complete private spool and affected input/undo until commit. |
| failure | Mapping/quota/work/resource failure aborts through public step. |
| cost | Output mapping for at most two EXISTS records; aggregate debit of physical journal/driver/undo/replaced-image sizes, followed by actual nonthrowing cleanup at commit. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0100

[Lines 1160–1180](../../../../../src/runtime/delta.cpp#L1160); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaStep step() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one pending producer/physical route or prepare the epoch. |
| inputs / outputs | Existing stage next yields core_result or retirement progress; otherwise observer creates Stage after drained native crossing; no more routes finalizes. |
| invariants | At most one heap-stable Stage; physical alias cannot advance while it remains. Filter/count-only routes still advance physical prefix. |
| ownership | Observer captures pending Data only for synchronous stage_next call; new Stage owns endpoint views thereafter. |
| failure | Uncaught failures are owned by public PendingEpoch::step abort handler; physical stage handler alone cannot restore independent live/output ownership. |
| cost | One accepted core action, full route support/preparation, retirement, or finalization; not every progress step is constant-cost. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0101

[Lines 1181–1182](../../../../../src/runtime/delta.cpp#L1181); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1181-L1182:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct DeltaRuntime::PendingEpoch::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct DeltaRuntime::PendingEpoch::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct DeltaRuntime::PendingEpoch::Data\` at its lexical source position in src/runtime/delta.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct DeltaRuntime::PendingEpoch::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0102

[Lines 1183–1183](../../../../../src/runtime/delta.cpp#L1183); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::PendingEpoch::PendingEpoch(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer new private pending control into the public token. |
| inputs / outputs | AccountedUnique&lt;Data&gt; moves into data_. |
| invariants | Move-only token is the abort authority until successful commit. |
| ownership | Unique owner retains runtime/account and all pending state. |
| failure | noexcept ownership move. |
| cost | Constant pointer transfer. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0103

[Lines 1184–1184](../../../../../src/runtime/delta.cpp#L1184); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::PendingEpoch::PendingEpoch(PendingEpoch&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move pending abort authority without rebuilding progress. |
| inputs / outputs | Default noexcept move constructor. |
| invariants | Moved-from token becomes empty; active producer/leases stay heap-stable. |
| ownership | Transfers unique Data ownership. |
| failure | noexcept. |
| cost | Constant pointer move. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0104

[Lines 1185–1188](../../../../../src/runtime/delta.cpp#L1185); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::PendingEpoch& DeltaRuntime::PendingEpoch::operator=(PendingEpoch&& other) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace pending ownership with self-move protection. |
| inputs / outputs | Rvalue PendingEpoch transfers data_ unless same object. |
| invariants | Replacing an active prior token aborts that old epoch through Data destructor before transfer. |
| ownership | Unique Data move, no cloning of journals/cursors. |
| failure | noexcept; impossible cleanup invariants terminate. |
| cost | Constant transfer plus affected old epoch rollback/teardown when present. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0105

[Lines 1189–1189](../../../../../src/runtime/delta.cpp#L1189); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::PendingEpoch::~PendingEpoch()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort pending epoch when its public token dies. |
| inputs / outputs | Default destructor releases unique Data. |
| invariants | No automatic drain/commit; closed token cleanup is idempotent. |
| ownership | Data/runtime/account may have outlived facade. |
| failure | noexcept destructor chain. |
| cost | Actual affected rollback and retained payload teardown; no constant-destruction claim. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0106

[Lines 1190–1190](../../../../../src/runtime/delta.cpp#L1190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool DeltaRuntime::PendingEpoch::active() const noexcept { return data_ && data_->active(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Poll public pending liveness. |
| inputs / outputs | Checks data_ and Data::active(). |
| invariants | Moved/closed tokens return false without production. |
| ownership | Scalar copy. |
| failure | noexcept. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0107

[Lines 1191–1191](../../../../../src/runtime/delta.cpp#L1191); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaState DeltaRuntime::PendingEpoch::state() const noexcept { return data_?data_->phase:DeltaState::aborted; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Poll saved pending terminal or active phase. |
| inputs / outputs | Returns saved phase or aborted for empty token. |
| invariants | Committed/aborted pending state differs from runtime ready/committed_output state. |
| ownership | Scalar copy. |
| failure | noexcept. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0108

[Lines 1192–1194](../../../../../src/runtime/delta.cpp#L1192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t DeltaRuntime::PendingEpoch::sequence() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the pending event sequence even after closure. |
| inputs / outputs | Guarded Data sequence return. |
| invariants | Only missing/moved token rejects; no active() requirement. |
| ownership | Scalar copy. |
| failure | invalid_delta_epoch for empty token. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0109

[Lines 1195–1197](../../../../../src/runtime/delta.cpp#L1195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const DeltaMetrics& DeltaRuntime::PendingEpoch::metrics() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow cumulative pending Delta metrics. |
| inputs / outputs | Requires Data and retained output. |
| invariants | Available through abort while output remains; commit transfers output to Epoch. No producer work or refill. |
| ownership | Borrow valid while token/output retained; stepping can update values. |
| failure | invalid_delta_epoch when token/output absent. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0110

[Lines 1198–1200](../../../../../src/runtime/delta.cpp#L1198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const DeltaTimings& DeltaRuntime::PendingEpoch::timings() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow cumulative pending phase timing. |
| inputs / outputs | Requires Data and retained output. |
| invariants | Pausing excludes wait intervals; diagnostic timing does not control deterministic grants. |
| ownership | Borrow under pending output lifetime; later work can update it. |
| failure | invalid_delta_epoch when token/output absent. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0111

[Lines 1201–1203](../../../../../src/runtime/delta.cpp#L1201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const DeltaStage> DeltaRuntime::PendingEpoch::stages() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow completed pending route summaries. |
| inputs / outputs | Returns span over retained output stages. |
| invariants | Only completed real native crossings appear; later steps may add summaries. |
| ownership | Span lifetime tied to pending output; callers must not keep a stale view through mutation/commit. |
| failure | invalid_delta_epoch when token/output absent. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0112

[Lines 1204–1213](../../../../../src/runtime/delta.cpp#L1204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaStep DeltaRuntime::PendingEpoch::step() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drive one active pending action with immediate all-epoch failure closure. |
| inputs / outputs | Validates token/pause/prepared state then installs original leased StorageOperation and calls private step. |
| invariants | Paused-step rejection and prepared polling occur before aborting try scope and preserve token; production failure closes it immediately even when caller retains handle. |
| ownership | Retains unique Data and operation authority; never manufactures another grant. |
| failure | Any failure from operation/production invokes Data::rollback then rethrows; no retry or silent partial prefix. |
| cost | Actual stage/route/finalization cost; selected producer profile only bounds qualified post-preparation transitions. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0113

[Lines 1214–1218](../../../../../src/runtime/delta.cpp#L1214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::PendingEpoch::pause() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pause a producing pending epoch without losing cursor position. |
| inputs / outputs | Active pending_delta transitions to paused. |
| invariants | Only producer phase may pause; data/queue/views remain unchanged. |
| ownership | Retains all pending native owners. |
| failure | invalid_delta_epoch or invalid_delta_state; rejection preserves active owner. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0114

[Lines 1219–1223](../../../../../src/runtime/delta.cpp#L1219); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::PendingEpoch::resume() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resume a paused epoch at its saved producer position. |
| inputs / outputs | Active paused phase transitions to pending_delta. |
| invariants | No cursor reconstruction or work refill. |
| ownership | Existing pending owners continue. |
| failure | invalid_delta_epoch or invalid_delta_state; rejection preserves active owner. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0115

[Lines 1224–1234](../../../../../src/runtime/delta.cpp#L1224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::PendingEpoch::start_drain() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start explicit discard-drain and keep replay intervals honest. |
| inputs / outputs | Disable output retention, exclude its cleanup debit from open replay interval, enter draining unless already prepared. |
| invariants | Irreversible within this token: internal production still finishes every required update/route before commit. |
| ownership | Releases only private output rows; retains stage/cursors/undo for drain. |
| failure | Work/cleanup failure catches and immediately aborts whole pending epoch; validation outside try leaves token semantics intact. |
| cost | O(existing output + completed summaries) cleanup, with no producer restart. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0116

[Lines 1235–1242](../../../../../src/runtime/delta.cpp#L1235); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::PendingEpoch::drain() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Finish preparation using the current retention policy. |
| inputs / outputs | Records drain intent, resumes paused token and repeatedly calls public step until prepared. |
| invariants | Ordinary drain retains output; start_drain/discard disable retention separately. |
| ownership | Same cumulative token/account/work authority across loop. |
| failure | Step production failure immediately aborts and propagates; never commits automatically. |
| cost | All remaining routes/answers/live work and finalization; may be output/population dependent. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0117

[Lines 1243–1278](../../../../../src/runtime/delta.cpp#L1243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch DeltaRuntime::PendingEpoch::commit() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish prepared physical/live/output state under one writer barrier. |
| inputs / outputs | Only active epoch_prepared token; returns committed Epoch. |
| invariants | All throwing construction/quota/precharges precede valid commit. Physical and live undo retire without allocating; sequence/L tag/output lease update atomically under single owner. |
| ownership | Transfers physical artifact and output Data; committed rows retain runtime barrier until consumed/discarded; empty output releases owner. |
| failure | Invalid/early commit rejects before publication and preserves token. Valid prepared ownership path transfers nonthrowing native state; no durable external transaction is established. |
| cost | Precharged affected undo/image teardown and fixed ownership transfer; actual cleanup is not zero-time despite no allocation. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0118

[Lines 1279–1279](../../../../../src/runtime/delta.cpp#L1279); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch DeltaRuntime::PendingEpoch::discard() { start_drain(); drain(); return commit(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept an input after complete internal drain while discarding output. |
| inputs / outputs | Combines start_drain, drain and commit. |
| invariants | Does not skip live/index/queue maintenance or later aliases. |
| ownership | Returns committed empty artifact retaining input/metrics as applicable. |
| failure | Prepublication drain/resource failures abort; successful discard leaves input committed. |
| cost | All required internal work plus existing private output cleanup. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0119

[Lines 1280–1280](../../../../../src/runtime/delta.cpp#L1280); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::PendingEpoch::rollback() noexcept { if (data_) data_->rollback(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly abort a pending epoch. |
| inputs / outputs | If Data exists invokes idempotent rollback. |
| invariants | Previous committed sequence/source/S/P/E/L restored; empty token no-op. |
| ownership | Releases pending leases/undo/output and runtime authority. |
| failure | noexcept; private restoration corruption terminates. |
| cost | Affected cleanup, no producer enumeration. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0121

[Lines 1282–1282](../../../../../src/runtime/delta.cpp#L1282); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch::Epoch(std::shared_ptr<Data> data) noexcept:data_(std::move(data)) {}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer committed output owner into Epoch. |
| inputs / outputs | Shared Data pointer moves into facade. |
| invariants | Artifact is already published; constructor performs no production. |
| ownership | Shared Data retains input/layout/native output and possibly writer barrier. |
| failure | noexcept. |
| cost | Constant pointer move. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0122

[Lines 1283–1283](../../../../../src/runtime/delta.cpp#L1283); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch::Epoch(Epoch&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move committed artifact without moving row storage. |
| inputs / outputs | Default noexcept Epoch move constructor. |
| invariants | Outstanding callback borrow remains valid under its strong Data owner. |
| ownership | Transfers shared Data facade ownership. |
| failure | noexcept. |
| cost | Constant pointer move. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0123

[Lines 1284–1287](../../../../../src/runtime/delta.cpp#L1284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch& DeltaRuntime::Epoch::operator=(Epoch&& other) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace committed artifact ownership safely. |
| inputs / outputs | Self-move guarded shared Data assignment. |
| invariants | Old final owner discards unread committed output; its input is never rolled back. Active callback may keep old Data alive until borrow ends. |
| ownership | Shared pointer move; existing returned records remain independent. |
| failure | noexcept cleanup; no throwing production. |
| cost | Pointer transfer plus conditional unread/final-owner teardown. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0124

[Lines 1288–1288](../../../../../src/runtime/delta.cpp#L1288); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch::~Epoch()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release committed artifact on facade destruction. |
| inputs / outputs | Default destructor releases shared Data. |
| invariants | Unread committed output is discarded on final Data release; active callback can delay that release. |
| ownership | Returned tuples and journal pins can outlive artifact independently. |
| failure | noexcept destructor chain. |
| cost | Unread rows/retained input and possible final runtime/program teardown. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0125

[Lines 1289–1289](../../../../../src/runtime/delta.cpp#L1289); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool DeltaRuntime::Epoch::active() const noexcept { return data_ && data_->leased; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Poll whether committed output owns the delivery barrier. |
| inputs / outputs | Returns Data && leased. |
| invariants | Empty/exhausted/discarded artifact is inactive even while input/metrics remain accessible. |
| ownership | Scalar copy. |
| failure | noexcept. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0126

[Lines 1290–1290](../../../../../src/runtime/delta.cpp#L1290); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t DeltaRuntime::Epoch::sequence() const { return input().input.sequence; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read accepted physical event sequence. |
| inputs / outputs | Delegates to input().input.sequence. |
| invariants | No producer/input mutation. |
| ownership | Scalar copy. |
| failure | invalid_delta_epoch when input artifact absent. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0127

[Lines 1291–1293](../../../../../src/runtime/delta.cpp#L1291); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const PhysicalEpoch& DeltaRuntime::Epoch::input() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow committed physical input artifact. |
| inputs / outputs | Requires Data and optional input, returns PhysicalEpoch reference. |
| invariants | Artifact history does not imply active output lease or current membership. |
| ownership | Borrow tied to shared Data; journal/source pins own deleted values. |
| failure | invalid_delta_epoch on absent/moved artifact. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0128

[Lines 1294–1294](../../../../../src/runtime/delta.cpp#L1294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const DeltaMetrics& DeltaRuntime::Epoch::metrics() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->metrics; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow prepared Delta metrics after commit/consumption. |
| inputs / outputs | Guarded Data metrics reference. |
| invariants | Prepared spool high-water is not remaining() and survives output discard. |
| ownership | Borrow requires artifact lifetime. |
| failure | invalid_delta_epoch for empty facade. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0129

[Lines 1295–1295](../../../../../src/runtime/delta.cpp#L1295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const DeltaTimings& DeltaRuntime::Epoch::timings() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->timings; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow postcommit timing diagnostics. |
| inputs / outputs | Guarded Data timings reference. |
| invariants | Callbacks may add serialization/sink time after preparation. |
| ownership | Borrow requires artifact lifetime; synchronous delivery can mutate timing. |
| failure | invalid_delta_epoch for empty facade. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0130

[Lines 1296–1296](../../../../../src/runtime/delta.cpp#L1296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const DeltaStage> DeltaRuntime::Epoch::stages() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->stages; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow committed route summary spans. |
| inputs / outputs | Guarded span over Data stages. |
| invariants | Prefix can have filtered/count-only gaps; scalar EXISTS replacement records fall outside core route ranges. |
| ownership | Data owns account-funded summary array. |
| failure | invalid_delta_epoch for empty facade. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0131

[Lines 1297–1297](../../../../../src/runtime/delta.cpp#L1297); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& DeltaRuntime::Epoch::layout() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->layout; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow selected output TupleLayout. |
| inputs / outputs | Guarded Data layout reference. |
| invariants | Layout retained independently after delivery barrier releases. |
| ownership | Data retains native immutable layout token. |
| failure | invalid_delta_epoch for empty facade. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0132

[Lines 1298–1298](../../../../../src/runtime/delta.cpp#L1298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t DeltaRuntime::Epoch::remaining() const { require(bool(data_),"invalid_delta_epoch","moved-from delta epoch"); return data_->rows.size(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count unread committed records. |
| inputs / outputs | Guarded FIFO size return. |
| invariants | Does not enumerate, consume or use prepared high-water as remaining count. |
| ownership | Scalar copy. |
| failure | invalid_delta_epoch for empty facade. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0133

[Lines 1299–1311](../../../../../src/runtime/delta.cpp#L1299); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SignedResult> DeltaRuntime::Epoch::next() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer one committed owning result to caller. |
| inputs / outputs | Rejects callback reentrancy; moves front result, pops node, updates disposition, releases output lease at last row. |
| invariants | Exhausted/discarded artifact repeatedly returns null; committed input never rewinds. |
| ownership | Caller retains native tuple/account payload independently; only FIFO node is freed. |
| failure | Moved token/reentrant next errors occur before consumption; valid row move/pop does not allocate. |
| cost | Fixed FIFO transfer plus per-node/final-owner cleanup; final row may release complete runtime/program if last owner. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0134

[Lines 1312–1316](../../../../../src/runtime/delta.cpp#L1312); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::Epoch::visit_complete(void(*visitor)(const SignedResult&,void*),void* context) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit whole unconsumed spool for private session coordination. |
| inputs / outputs | Function pointer/context receive each const SignedResult; requires all prepared rows still present. |
| invariants | Private visitor must preserve traversal ownership and not consume/mutate nodes; method checks unavailable/reentrant and partial output but installs no delivery lock. |
| ownership | Borrows Data/rows for call; callback does not receive owning transfer. |
| failure | runtime_busy/partial_epoch_output before loop; visitor exception propagates with rows unacknowledged. |
| cost | Linear in records plus actual visitor work; no new output copy. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0135

[Lines 1317–1327](../../../../../src/runtime/delta.cpp#L1317); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::Epoch::acknowledge_complete() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acknowledge complete private whole-epoch delivery. |
| inputs / outputs | Requires non-delivering full spool; pops every row and publishes release. |
| invariants | Used after successful whole-artifact protocol; partial/in-flight misuse terminates. |
| ownership | Consumes FIFO ownership, retaining input/metrics until artifact destruction. |
| failure | noexcept; invalid private preconditions terminate. |
| cost | O(spool nodes + native payload destruction), optional per-record observation. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0136

[Lines 1328–1330](../../../../../src/runtime/delta.cpp#L1328); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool DeltaRuntime::Epoch::deliver_one(const std::function<void(const SignedResult&)>& sink) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deliver one row using the single sink callback interface. |
| inputs / outputs | Delegates to two-callback overload with absent serializer. |
| invariants | Same postcommit borrow/acknowledgement and retry semantics. |
| ownership | Borrowed const record is valid only during callback. |
| failure | Delegated callback/runtime failures propagate; retained row follows explicit discard/final-owner rules. |
| cost | Callback work plus fixed delegation. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0137

[Lines 1331–1384](../../../../../src/runtime/delta.cpp#L1331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool DeltaRuntime::Epoch::deliver_one(const std::function<void(const SignedResult&)>& serialize,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize and deliver a borrowed committed row before acknowledging it. |
| inputs / outputs | Strong local Data, delivering flag, optional serializer then sink; true if a row was attempted successfully. |
| invariants | Serializer failure never invokes sink. Row is popped only after success; catch clears delivering, records failure and honors deferred discard. External side effects can repeat on retry. |
| ownership | Local shared owner keeps row valid through facade moves/destruction. Reentrant consumption rejects; discard defers until borrow ends. |
| failure | Any callback exception rethrows after borrow cleanup; tuple/ordinal remain retryable unless explicit discard/final-owner loss releases them. Committed input remains accepted. |
| cost | Fixed FIFO/observer work plus arbitrary caller serialization/sink cost; enabled phase clocks include CPU/wait. Final discard/owner teardown is additional. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0138

[Lines 1385–1385](../../../../../src/runtime/delta.cpp#L1385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::Epoch::discard() noexcept { if (data_) data_->finish(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard unread committed output. |
| inputs / outputs | If Data exists invokes finish. |
| invariants | Input remains committed; callback borrow defers release. |
| ownership | Clears unread rows/output owner, retains input/layout/metrics through facade. |
| failure | noexcept; empty facade is a no-op. |
| cost | Linear unread/final-owner cleanup. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0140

[Lines 1387–1393](../../../../../src/runtime/delta.cpp#L1387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::DeltaRuntime(PhysicalPlan plan,DeltaOptions options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty Delta owner from external physical plan. |
| inputs / outputs | Admits plan context, enters one StorageOperation, builds Impl and optional initial live bootstrap. |
| invariants | Initial configuration published only after successful construction; original requested options survive bootstrap. |
| ownership | Creates one original account/context and shared native Impl; program/physical members own metadata. |
| failure | Any plan/options/build/bootstrap failure unwinds unpublished local owner; no extra catch needed around RAII. |
| cost | Physical admission/factor metadata plus initial E/live bootstrap (empty source state); not constant query-metadata setup. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0141

[Lines 1394–1402](../../../../../src/runtime/delta.cpp#L1394); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::DeltaRuntime(CompiledProgram source,DeltaOptions options) try
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an admitted Delta owner from immutable CompiledProgram. |
| inputs / outputs | Creates receiving context, freezes program there, builds physical/Delta state and optional initial bootstrap. |
| invariants | Source is not reused with a second independent cap; new context owns actual received allocations. |
| ownership | Original receiving account funds frozen metadata and shared native owner. |
| failure | Function-try clauses translate native IndexFailure/TableValidationFailure after RAII cleanup; other validation/resource errors propagate. |
| cost | Program freeze/admission + factor routing + optional live bootstrap; value/key widths and allocator requests remain visible. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0142

[Lines 1403–1423](../../../../../src/runtime/delta.cpp#L1403); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::DeltaRuntime(PhysicalRuntime physical,DeltaOptions options,BuildOptions build)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete Delta construction around an initialized physical owner. |
| inputs / outputs | PhysicalRuntime, ordinary options and BuildOptions; merges initialization metrics and optional live bootstrap. |
| invariants | Only unpublished bootstrap uses remaining build limit for Delta/cursor/view budgets; ordinary update options are restored before final configuration. |
| ownership | Moves existing physical/account ownership; no copied database or new cap. |
| failure | Build/bootstrap failure destroys unpublished Impl; temporary option restoration is unnecessary for an owner that cannot publish. |
| cost | Initialized physical cost plus full live bootstrap; all live/index rows retained under existing account. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0143

[Lines 1424–1428](../../../../../src/runtime/delta.cpp#L1424); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime DeltaRuntime::initialize(PhysicalPlan plan,const Database& database,DeltaOptions options,BuildOptions build) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize physical data and Delta state from external plan/database. |
| inputs / outputs | Creates context, calls PhysicalRuntime::initialize_at sequence zero then private Delta constructor. |
| invariants | BuildOptions govern direct physical build plus live bootstrap; ordinary update grants remain retained options. |
| ownership | Database is borrowed for import; result owns native source/support/live state. |
| failure | Admission/build/allocation failure discards unpublished result through RAII. |
| cost | Population-dependent source/derivation/support initialization and E/L/index bootstrap; no answer-history materialization. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0144

[Lines 1429–1435](../../../../../src/runtime/delta.cpp#L1429); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime DeltaRuntime::initialize(CompiledProgram source,const Database& database,DeltaOptions options,BuildOptions build) try {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize Delta from native program under one receiving account. |
| inputs / outputs | Freeze CompiledProgram in new context, initialize physical database, complete Delta bootstrap. |
| invariants | Same initialization semantics as external plan path; nested context does not refill receiving authority. |
| ownership | Original account funds frozen program and all native state. |
| failure | Native typed failures translated only after owners unwind; remaining failures propagate. |
| cost | Program copy/admission plus full physical/direct build and live bootstrap. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0145

[Lines 1436–1446](../../../../../src/runtime/delta.cpp#L1436); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime DeltaRuntime::rebuilt(BuildOptions build) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a fresh owner for current committed sources. |
| inputs / outputs | Quiescent runtime and BuildOptions return rebuilt DeltaRuntime. |
| invariants | Uses current effective mode during rebuild, then preserves requested original options/declared benchmark identity. Original owner/state remains unchanged. |
| ownership | New owner shares the original funding account with simultaneously retained old state; no split replacement memory cap. |
| failure | Writer barrier/build/resource failure preserves source owner; unpublished target unwinds. |
| cost | Full source/support rebuild and optional L/index bootstrap, old+new retained peak, owner metadata/configuration. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0146

[Lines 1447–1458](../../../../../src/runtime/delta.cpp#L1447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime DeltaRuntime::rebuilt_for(const planner::MinimumHeightCandidate& candidate,BuildOptions build,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild committed sources under an admitted alternative candidate. |
| inputs / outputs | Candidate, build/replan limits return fresh owner with selected physical topology. |
| invariants | Checks occur through physical replan; current mode and requested options retained independently. |
| ownership | Existing query account funds replacement while old owner remains; result carries benchmark context. |
| failure | Readiness/replan/admission/resource errors leave original state intact. |
| cost | Replan metadata + population-dependent physical rebuild and optional live bootstrap; no in-place mutation. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0147

[Lines 1459–1459](../../../../../src/runtime/delta.cpp#L1459); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1459-L1459:sha256:cf04d99c0f5d3521f67f7c587d20dd3592a5024b903529e1e468844f7fae8135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: opens anonymous namespace with translation-unit-local linkage. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0148

[Lines 1460–1470](../../../../../src/runtime/delta.cpp#L1460); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::ImageBinding image_binding(const CompiledProgram& program,const DeltaOptions& options,DeltaMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind recovery bytes to exact program/source/catalog and Delta policy. |
| inputs / outputs | CompiledProgram/options/effective mode return fixed ImageBinding. |
| invariants | Both digests must be exactly64 characters; checkpoint_policy includes requested/resolved runtime settings. |
| ownership | Fixed arrays own copied digest characters; program is borrowed for call. |
| failure | ImageFailure(binding) for malformed digest width; no repair. |
| cost | Fixed digest/policy copy, independent of database size. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0149

[Lines 1471–1471](../../../../../src/runtime/delta.cpp#L1471); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1471-L1471:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/delta.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/delta.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/delta.cpp\` at its lexical source position in src/runtime/delta.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/delta.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0150

[Lines 1472–1475](../../../../../src/runtime/delta.cpp#L1472); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::EncodedImage DeltaRuntime::checkpoint_image(recovery::ImageLimits limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode a quiescent committed physical checkpoint for this Delta policy. |
| inputs / outputs | ImageLimits and exact image_binding; delegates physical checkpoint encoding. |
| invariants | Writer-ready/output-free barrier required; live cache is derived on restoration, not serialized as independent authority. |
| ownership | Returned encoded image owns bytes under explicit recovery policy. |
| failure | Busy/binding/encoding/resource failures propagate without modifying runtime. |
| cost | Explicit source/image encoding work and byte limits; no ordinary-update checkpoint overhead. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0151

[Lines 1476–1478](../../../../../src/runtime/delta.cpp#L1476); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::ImageBinding DeltaRuntime::checkpoint_binding() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read exact recovery binding without encoding state. |
| inputs / outputs | Returns fixed program/source/catalog/policy binding. |
| invariants | No Delta readable/writable barrier here; binding concerns immutable identity and current effective mode. |
| ownership | Fixed returned value owns arrays. |
| failure | Moved runtime or malformed digest width rejects. |
| cost | Fixed identity/policy copy. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0152

[Lines 1479–1482](../../../../../src/runtime/delta.cpp#L1479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime DeltaRuntime::restore_image(CompiledProgram program,std::string_view bytes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore a public image with ordinary session-independent defaults. |
| inputs / outputs | Program/bytes/options/build/image limits delegate to restore_session_image without window/workload override. |
| invariants | Bindings must match; creates fresh unpublished owner. |
| ownership | Input bytes/program borrowed/moved as declared; result owns restored native state. |
| failure | Delegated binding/limit/native/build failures propagate. |
| cost | Image decode/validation + source/support restoration and optional live bootstrap. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0153

[Lines 1483–1498](../../../../../src/runtime/delta.cpp#L1483); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime DeltaRuntime::restore_session_image(CompiledProgram program,std::string_view bytes,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore under validated original context and optional session metadata. |
| inputs / outputs | Program, bytes/options/build/image limits, optional window/matching work/workload/context. |
| invariants | Existing context must match indexed backend, per-operation allowance and original memory limit before restore; no independent grant/cap. |
| ownership | Owns new physical/Delta result; supplied context retains original account. |
| failure | Context contract mismatch throws MemoryFailure; native failures translated at function boundary after target cleanup; no partial result publishes. |
| cost | Image decoding and physical initialization + L/index bootstrap + optional workload configuration. |
| Design | [docs/checkpoints.md](../../../../checkpoints.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md), [docs/statistics.md](../../../../statistics.md) |

## B0154

[Lines 1499–1499](../../../../../src/runtime/delta.cpp#L1499); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InitializationContext DeltaRuntime::initialization_context() const { return impl().physical.initialization_context(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read physical initialization provenance. |
| inputs / outputs | Delegates physical initialization_context(). |
| invariants | Initialization is fixed provenance, not fresh snapshot/diagnostic scan. |
| ownership | Returned context owns scalar/value metadata. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0155

[Lines 1500–1500](../../../../../src/runtime/delta.cpp#L1500); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const BuildMetrics& DeltaRuntime::initialization_metrics() const { return impl().initialization; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow combined physical/live build metrics. |
| inputs / outputs | Returns Impl initialization. |
| invariants | Includes live_bootstrap_work when initialized in Delta mode; not ordinary update counters. |
| ownership | Reference requires retained runtime. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0156

[Lines 1501–1502](../../../../../src/runtime/delta.cpp#L1501); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::~DeltaRuntime()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy or move the Delta facade by shared-owner transfer. |
| inputs / outputs | Default destructor and noexcept move constructor. |
| invariants | Pending/output/cursor owners may retain runtime; moved facade has no impl. Destruction does not implicitly drain a pending producer. |
| ownership | Shared Impl move/release; final release destroys actual physical/live/program state. |
| failure | Noexcept default ownership operations; private cleanup contract corruption terminates. |
| cost | Constant move; conditional complete retained-state/final-program destruction on final release. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0157

[Lines 1503–1503](../../../../../src/runtime/delta.cpp#L1503); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime& DeltaRuntime::operator=(DeltaRuntime&& other) noexcept { if (this!=&other) impl_=std::move(other.impl_); return *this; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move-assign runtime facade with self-move guard. |
| inputs / outputs | Transfers shared impl unless same facade. |
| invariants | Existing pending/output ownership survives independently; old final state can be destroyed. |
| ownership | No database/live clone or grant refill. |
| failure | noexcept. |
| cost | Constant pointer transfer plus potential full old final-owner teardown. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0158

[Lines 1504–1504](../../../../../src/runtime/delta.cpp#L1504); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Impl& DeltaRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved-from delta runtime"); return *impl_; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Guard access to private runtime implementation. |
| inputs / outputs | Returns Impl& through logically const facade. |
| invariants | Single-writer APIs, not C++ constness, govern mutations. |
| ownership | Borrow requires facade or another retained shared owner. |
| failure | invalid_runtime for moved-from/empty facade. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0159

[Lines 1505–1505](../../../../../src/runtime/delta.cpp#L1505); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& DeltaRuntime::plan() const { return impl().physical.plan(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow native compiled program through plan API. |
| inputs / outputs | Returns physical.plan(). |
| invariants | Immutable metadata remains readable during pending lifecycle. |
| ownership | Reference valid while runtime/program owner retained. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0160

[Lines 1506–1506](../../../../../src/runtime/delta.cpp#L1506); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& DeltaRuntime::compiled_program() const { return impl().physical.compiled_program(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow authoritative CompiledProgram. |
| inputs / outputs | Delegates physical.compiled_program(). |
| invariants | No lowering/reconstruction or DTO export. |
| ownership | Reference tied to retained frozen program. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0161

[Lines 1507–1507](../../../../../src/runtime/delta.cpp#L1507); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const DeltaOptions& DeltaRuntime::options() const { return impl().options; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow requested original DeltaOptions. |
| inputs / outputs | Returns Impl options. |
| invariants | options.mode/completion can differ from effective mode()/completion(); initialization restores ordinary grants. |
| ownership | Reference tied to runtime; private unpublished bootstrap can temporarily adjust options. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0162

[Lines 1508–1508](../../../../../src/runtime/delta.cpp#L1508); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics DeltaRuntime::accounted_memory_statistics() const { return impl().physical.accounted_memory_statistics(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read original-account requested-byte statistics. |
| inputs / outputs | Delegates physical.accounted_memory_statistics(). |
| invariants | Not process RSS or per-spool usage; includes simultaneously retained owners under account. |
| ownership | Returned fixed statistics copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0163

[Lines 1509–1509](../../../../../src/runtime/delta.cpp#L1509); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaCompletion DeltaRuntime::completion() const { return impl().selected_completion; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read resolved completion strategy. |
| inputs / outputs | Returns selected_completion. |
| invariants | Automatic maps to replay only with row-coupled live maintenance; requested option remains in options(). |
| ownership | Scalar enum copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0164

[Lines 1510–1549](../../../../../src/runtime/delta.cpp#L1510); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntimeProfile DeltaRuntime::profile() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose qualified guarantee profile for effective strategy. |
| inputs / outputs | Returns fixed scalar/string_view descriptor with mode, strategy, query size and spool limits. |
| invariants | Backend follows admitted immutable plan options before every mode-specific return. Only replay claims bounded accepted transitions after route preparation. Canonical anchors bound candidates; root-first may scan unrelated E; public startup includes the whole epoch. Output accounting includes native node/value/payload requests and account framing, with query/scratch/journal costs separate. The output_accounting string retains legacy v2 descriptive bytes; accurate current quota wording lives in DeltaOptions comments and docs/delta_runtime.md. |
| ownership | All text references static literals and can outlive facade. |
| failure | Moved facade rejects; otherwise fixed metadata construction, no state scan. |
| cost | Fixed descriptor selection; state/preparation/finalization fields state real affected/eager costs, ordered/value/allocator/arena cleanup remains additional. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/anchored_delta.md](../../../../anchored_delta.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [docs/epoch_views.md](../../../../epoch_views.md) |

## B0165

[Lines 1550–1550](../../../../../src/runtime/delta.cpp#L1550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOwnerId DeltaRuntime::owner() const { return impl().physical.owner(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read logical runtime owner identity. |
| inputs / outputs | Delegates physical.owner(). |
| invariants | Identity is stable under facade moves; new rebuild has a new owner. |
| ownership | Scalar identity copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0166

[Lines 1551–1551](../../../../../src/runtime/delta.cpp#L1551); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t DeltaRuntime::sequence() const { return impl().physical.sequence(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last committed physical sequence. |
| inputs / outputs | Delegates physical.sequence(). |
| invariants | Pending event sequence is private; this remains last commit. |
| ownership | Scalar copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0167

[Lines 1552–1552](../../../../../src/runtime/delta.cpp#L1552); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMode DeltaRuntime::mode() const { return impl().mode; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read current effective maintenance/Delta mode. |
| inputs / outputs | Returns Impl mode. |
| invariants | Current mode differs from initial options.mode after switches. |
| ownership | Scalar copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0168

[Lines 1553–1553](../../../../../src/runtime/delta.cpp#L1553); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool DeltaRuntime::ready() const { const auto& d=impl(); return !d.processing && !d.output_active && d.physical.ready(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Poll complete readiness for new input/mode change. |
| inputs / outputs | Combines no processing, no output lease and physical.ready(). |
| invariants | Read leases and unread committed output can keep readiness false; polling performs no draining. |
| ownership | Scalar Boolean copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0169

[Lines 1554–1556](../../../../../src/runtime/delta.cpp#L1554); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaState DeltaRuntime::state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report runtime lifecycle and committed-output ownership. |
| inputs / outputs | Processing returns saved phase, otherwise output_active selects committed_output or ready. |
| invariants | ready state here does not imply physical read leases absent; ready() is full write readiness. |
| ownership | Scalar enum copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0170

[Lines 1557–1557](../../../../../src/runtime/delta.cpp#L1557); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool DeltaRuntime::has_answer() const { const auto& d=impl(); d.readable(); return d.physical.has_answer(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed core truth behind tentative-state barrier. |
| inputs / outputs | readable() then physical.has_answer(). |
| invariants | Unread committed output permits this read; tentative preparation rejects. |
| ownership | Scalar Boolean copy. |
| failure | invalid_runtime/runtime_busy or delegated owner failure. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0171

[Lines 1558–1558](../../../../../src/runtime/delta.cpp#L1558); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& DeltaRuntime::result_layout() const { return impl().output_layout; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow selected output layout. |
| inputs / outputs | Returns Impl output_layout. |
| invariants | Immutable layout is readable during pending state; no result enumeration. |
| ownership | Retained layout token is owned by Impl. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0172

[Lines 1559–1559](../../../../../src/runtime/delta.cpp#L1559); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const DeltaMetrics& DeltaRuntime::bootstrap_metrics() const { return impl().bootstrap; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow last successful live bootstrap metrics. |
| inputs / outputs | Returns Impl bootstrap. |
| invariants | Maintenance no-op switch does not fabricate new bootstrap work. |
| ownership | Reference tied to runtime. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0173

[Lines 1560–1560](../../../../../src/runtime/delta.cpp#L1560); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1560-L1560:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0174

[Lines 1561–1563](../../../../../src/runtime/delta.cpp#L1561); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(const DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose current indexed-work test probe through Delta. |
| inputs / outputs | Testing build delegates to physical index_work. |
| invariants | Does not copy/refill storage allowance or become production observation API. |
| ownership | Returned optional fixed test value. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0175

[Lines 1564–1564](../../../../../src/runtime/delta.cpp#L1564); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1564-L1564:sha256:9a349bbd1a21104f051e34b2c8a9e70cc7fbb50bc19a67781f2a140c386d9438
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: closes the matching compile-time guard. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0176

[Lines 1565–1567](../../../../../src/runtime/delta.cpp#L1565); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMetrics DeltaRuntime::set_mode(DeltaMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Switch mode under existing storage operation authority. |
| inputs / outputs | Mode selector enters StorageOperation and delegates Impl change_mode. |
| invariants | No independently funded nested storage grant. |
| ownership | Existing context/account only. |
| failure | Busy/invalid-mode/bootstrap resource failure propagates without partial cache install. |
| cost | Mode-dependent full live bootstrap or live-image destruction, not a uniformly constant switch. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0177

[Lines 1568–1581](../../../../../src/runtime/delta.cpp#L1568); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaMetrics DeltaRuntime::Impl::change_mode(DeltaMode mode) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install or remove derived live cache at quiescent barrier. |
| inputs / outputs | Validated mode; no-op returns zero metrics, maintenance drops L, Delta builds from committed E then installs tag/mode/bootstrap. |
| invariants | Bootstrap failure preserves old mode/cache; maintenance updates never reuse stale L. Effective configuration publishes only after success. |
| ownership | New image owns account-funded L/P/B; leaving mode releases old image and payloads. |
| failure | Writer/invalid-mode/view/work/resource failures reject before install; temporary view unwinds. |
| cost | Entry scans all E/parent-L for full bootstrap; exit may destroy full L/index state; no-op guard is fixed. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0178

[Lines 1582–1584](../../../../../src/runtime/delta.cpp#L1582); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::PendingEpoch DeltaRuntime::begin(const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow public owning update for immediate pending admission. |
| inputs / outputs | PhysicalSetUpdate delegates through PhysicalUpdateView::borrow. |
| invariants | Input lifetime needed only during begin; physical source pin then owns complete row. |
| ownership | No caller Row copy at delegation; native import happens below. |
| failure | Delegated admission errors propagate. |
| cost | Fixed borrow plus begin_view costs. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0179

[Lines 1585–1589](../../../../../src/runtime/delta.cpp#L1585); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::PendingEpoch DeltaRuntime::begin_view(const PhysicalUpdateView& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the owning pending Delta transaction. |
| inputs / outputs | PhysicalUpdateView installs existing StorageOperation, checks writer barrier and allocates native Pending Data. |
| invariants | One original account/storage authority; no active reader/output/pending input allowed. |
| ownership | Returned unique pending owner retains source pin, runtime and all private progress. |
| failure | Guard/admission/control/source preparation errors unwind unpublished ownership; constructor explicitly restores activated flags. |
| cost | Control/factor scratch + physical validation/import/probe/constraints; begin is not a bounded producer result action. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0180

[Lines 1590–1592](../../../../../src/runtime/delta.cpp#L1590); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch DeltaRuntime::apply(const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one owning physical event with eager atomic public output. |
| inputs / outputs | begin, retaining drain, commit return Epoch. |
| invariants | All alias support/live/Delta production finishes before any public record. |
| ownership | Local pending token aborts automatically if drain throws. |
| failure | Precommit failure preserves prior input/sequence; postcommit delivery belongs to Epoch. |
| cost | Complete physical maintenance, all route preparation/production/mapping/spool/finalization before first public record. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0181

[Lines 1593–1595](../../../../../src/runtime/delta.cpp#L1593); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DeltaRuntime::Epoch DeltaRuntime::apply_view(const PhysicalUpdateView& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one borrowed physical event synchronously. |
| inputs / outputs | begin_view, drain, commit return committed Epoch. |
| invariants | Borrowed source values need only admission call; same eager atomic semantics as apply. |
| ownership | Local pending and source pin own progress after import. |
| failure | Failure unwinds pending rollback; caller input is never retained by raw RowView. |
| cost | Full eager-atomic epoch cost, no constant public startup. |
| Design | [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0182

[Lines 1596–1599](../../../../../src/runtime/delta.cpp#L1596); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor DeltaRuntime::results(ResultCursorOptions options) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed results in configured core/SQL view. |
| inputs / outputs | ResultCursorOptions, readable guard, then physical core_results/results. |
| invariants | Pending state rejects; committed-output ownership permits read and reader lease can prevent next write. |
| ownership | Returned cursor retains underlying physical/runtime/program lease. |
| failure | Busy/invalid options/cursor/storage/resource failures propagate. |
| cost | D02 cursor startup/traversal costs, independent from Delta spool. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/result_cursors.md](../../../../result_cursors.md) |

## B0183

[Lines 1600–1600](../../../../../src/runtime/delta.cpp#L1600); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor DeltaRuntime::core_results(ResultCursorOptions options) const { const auto& d=impl(); d.readable(); return d.physical.core_results(options); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed core results independently of selected output mapping. |
| inputs / outputs | readable guard then physical.core_results. |
| invariants | No tentative prefix exposure or Delta history scan. |
| ownership | Returned cursor owns physical read lease and native payloads. |
| failure | Busy/cursor/native/resource failures propagate. |
| cost | Actual D02 startup and subsequent cursor work; output width/ordered costs remain. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/result_cursors.md](../../../../result_cursors.md) |

## B0184

[Lines 1601–1601](../../../../../src/runtime/delta.cpp#L1601); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::EpochView DeltaRuntime::current_view(EpochViewOptions options) const { const auto& d=impl(); d.readable(); return d.physical.current_view(options); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed factor view. |
| inputs / outputs | EpochViewOptions, readable guard, physical.current_view. |
| invariants | View has existing owner/sequence identity and prevents conflicting writes. |
| ownership | Returned view owns shared read lease; metadata/program retained. |
| failure | Busy/view/resource errors propagate. |
| cost | Committed view setup; explicit later factor/result walks cost actual rows. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/epoch_views.md](../../../../epoch_views.md) |

## B0185

[Lines 1602–1602](../../../../../src/runtime/delta.cpp#L1602); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSnapshot DeltaRuntime::snapshot() const { const auto& d=impl(); d.readable(); return d.physical.snapshot(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export explicit full physical/support snapshot. |
| inputs / outputs | readable guard then physical.snapshot. |
| invariants | Diagnostic export is not ordinary update or Delta live-cache algorithm. |
| ownership | Caller-owned diagnostic DTO retains copied populations/pins as defined by physical snapshot. |
| failure | Busy/native/allocation failure propagates without state mutation. |
| cost | Population-dependent source/support/metadata copying, outside normal update cost. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0186

[Lines 1603–1608](../../../../../src/runtime/delta.cpp#L1603); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<LiveSnapshot> DeltaRuntime::live_snapshot() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export complete current L sets for explicit diagnostics. |
| inputs / outputs | readable guard; absent live image returns null, otherwise sequence plus each factor export_rows. |
| invariants | Reports global L complete keys in parent-before-child order, distinct from E snapshot and full answer relation. |
| ownership | Caller-owned standard vector/Relations and exported scalar strings; no new retained runtime cache. |
| failure | Busy/export/allocation failure propagates. |
| cost | Traverses and copies all L keys/bytes plus ordered diagnostic relation insertion. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0187

[Lines 1609–1609](../../../../../src/runtime/delta.cpp#L1609); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalStorageStatistics DeltaRuntime::storage_statistics() const { const auto& d=impl(); d.readable(); return d.physical.storage_statistics(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read explicit physical storage statistics behind tentative barrier. |
| inputs / outputs | readable guard delegates storage_statistics. |
| invariants | Does not infer full result or Delta live cardinalities. |
| ownership | Returned statistics follow physical diagnostic DTO ownership. |
| failure | Busy/native/diagnostic errors propagate. |
| cost | Delegated storage metadata/statistics traversal; not implicitly charged as producer work. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0188

[Lines 1610–1627](../../../../../src/runtime/delta.cpp#L1610); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CanonicalDeltaState DeltaRuntime::canonical_state() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export canonical physical/live state for independent comparison. |
| inputs / outputs | Original StorageOperation plus readable guard; copies L and every P/B separator/count/complete-key set. |
| invariants | Does not recompute/repair state; global L and local physical S/P/E remain distinguishable. |
| ownership | Caller-owned canonical DTO/vector/Rows; native runtime remains unchanged. |
| failure | Busy/storage/export/allocation errors propagate. |
| cost | Full source/support/live/index population and key-byte export with ordinary DTO allocation; explicit diagnostic operation. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0189

[Lines 1628–1784](../../../../../src/runtime/delta.cpp#L1628); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InvariantReport DeltaRuntime::inspect_invariants(InspectionOptions options) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect committed physical/E/L/index invariants independently. |
| inputs / outputs | Inspection limits; first physical inspector then top-down expected L from actual E and regrouped indexes from observed L. |
| invariants | Checks dimensions/tag/membership/support/aggregate counts. Corrupt L still gets independent index regroup checks; incomplete traversal never claims validity. |
| ownership | Original account funds scratch expected sets/groups/issues; returned report owns funded keys/issues. |
| failure | InspectionStop, public Error and out_of_range mark incomplete (bounded issue insertion); allocation/native failures outside those catches propagate. No update rollback/recovery occurs. |
| cost | Explicit full physical plus E/live/index scans/projections/ordered comparisons and expected-state allocation under diagnostic cap; no incremental-update bound. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp) |

## B0190

[Lines 1785–1785](../../../../../src/runtime/delta.cpp#L1785); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1785-L1785:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0191

[Lines 1786–1789](../../../../../src/runtime/delta.cpp#L1786); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void RuntimeTestProbe::seed_delta_sequence(DeltaRuntime& runtime,std::uint64_t sequence) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed committed Delta/physical sequence for tests. |
| inputs / outputs | Writable testing owner updates physical and live tag if present. |
| invariants | Keeps live sequence aligned while exercising sequence overflow; excluded from production. |
| ownership | Mutates existing scalar state only. |
| failure | Moved/busy/test-probe guard failures propagate. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0192

[Lines 1790–1790](../../../../../src/runtime/delta.cpp#L1790); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime& RuntimeTestProbe::physical(DeltaRuntime& runtime) { return runtime.impl().physical; }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose underlying physical owner to test harness. |
| inputs / outputs | Returns mutable physical runtime reference. |
| invariants | Testing-only authority bypasses public Delta coordination; harness must preserve/restore intended invariants. |
| ownership | Borrow tied to Delta owner. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0193

[Lines 1791–1798](../../../../../src/runtime/delta.cpp#L1791); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t RuntimeTestProbe::set_live_bucket(DeltaRuntime& runtime,NodeId node,bool child,const Row& key,std::uint64_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Corrupt and return one live index count for inspection tests. |
| inputs / outputs | Node/rank/side/key/value; exchange count. |
| invariants | Requires L and valid factor/bucket; deliberately does not update rows/totals. |
| ownership | Test-only borrowed bucket; old scalar returned. |
| failure | invalid_probe, bounds or absent-key errors; busy guard precedes mutation. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0194

[Lines 1799–1808](../../../../../src/runtime/delta.cpp#L1799); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t RuntimeTestProbe::set_live_total(DeltaRuntime& runtime,InvariantComponent component,std::size_t value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Corrupt and return a selected live aggregate for tests. |
| inputs / outputs | Writable owner, component and new total exchange L/P/B row counter. |
| invariants | Only three live aggregate components admitted; intentionally violates population aggregate for inspector fixtures. |
| ownership | Scalar state mutation only. |
| failure | invalid_probe for absent image/bad component; busy guard before mutation. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0195

[Lines 1809–1810](../../../../../src/runtime/delta.cpp#L1809); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1809-L1810:sha256:8b63d4e2e6cce4baf5403993210754bed64f3d3fa8e57007f2c3eeff4491a972
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: closes the matching compile-time guard. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0196

[Lines 1811–1821](../../../../../src/runtime/delta.cpp#L1811); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::check_invariants() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform strong explicit physical/live consistency check. |
| inputs / outputs | Original StorageOperation/readable guard; physical checks then full build_live and equality against current L/P/B/totals. |
| invariants | Maintenance must have no L; Delta tag must match sequence. Comparison shares build algorithm, unlike inspect_invariants independent expected derivation. |
| ownership | Temporary complete rebuilt image is original-account funded alongside existing image/view. |
| failure | Busy/work/resource/invariant mismatch propagates; no state repair. |
| cost | Full physical check plus eager E/L/index rebuild and equality, widths/allocator/destruction costs included separately from ordinary maintenance. |
| Design | [docs/incremental_live.md](../../../../incremental_live.md), [docs/ordered_delta.md](../../../../ordered_delta.md), [src/runtime/accounted_ordered_rows.hpp](../../../../../src/runtime/accounted_ordered_rows.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0197

[Lines 1822–1825](../../../../../src/runtime/delta.cpp#L1822); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::declare_benchmark_context(std::shared_ptr<const DeclaredBenchmarkContext> value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain caller-declared benchmark context for reporting. |
| inputs / outputs | Shared immutable context moves to Impl and observer. |
| invariants | This is declared provenance, not measured fact or validity proof; no busy guard here. |
| ownership | Shares immutable caller-supplied record. |
| failure | Moved facade rejects; shared pointer/observer transfer has no recovery wrapper. |
| cost | Fixed shared-owner update; final prior context release may destroy its payload. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0198

[Lines 1826–1826](../../../../../src/runtime/delta.cpp#L1826); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CursorObservation> DeltaRuntime::last_cursor_observation() const { return impl().physical.last_cursor_observation(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last optional physical cursor lifecycle observation. |
| inputs / outputs | Delegates physical.last_cursor_observation. |
| invariants | No Delta producer row history or fresh scan; result may be absent. |
| ownership | Returns fixed optional snapshot copy. |
| failure | Empty or moved facade rejects through the stated owner guard. |
| cost | Constant guard/access; no allocation or grant refill. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0199

[Lines 1827–1827](../../../../../src/runtime/delta.cpp#L1827); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CommittedStateGauges DeltaRuntime::committed_state_gauges() const { const auto& d=impl();d.readable();return d.physical.committed_state_gauges(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export committed physical/support gauges. |
| inputs / outputs | readable guard delegates physical.committed_state_gauges. |
| invariants | Local relation cardinalities do not claim global L or full answer cardinality. |
| ownership | Caller-owned gauge vectors under explicit export contract. |
| failure | Busy/native/allocation failure propagates. |
| cost | O(compiled sources/nodes) size reads and result vector construction; no answer enumeration. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0200

[Lines 1828–1828](../../../../../src/runtime/delta.cpp#L1828); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedStateGauges DeltaRuntime::capture_state_gauges() const {const auto& d=impl();d.readable();return d.physical.capture_state_gauges();}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture account-funded committed physical/support gauges. |
| inputs / outputs | readable guard delegates capture_state_gauges. |
| invariants | Same logical local facts as DTO gauge export, with native retained ownership. |
| ownership | Returned capture arrays retain original account; no new account/cap. |
| failure | Busy/resource/capture errors propagate. |
| cost | Per-source/node gauge reads/copy, not Delta live/full-result enumeration. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0201

[Lines 1829–1833](../../../../../src/runtime/delta.cpp#L1829); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationSnapshot DeltaRuntime::observations() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return observation snapshot with current declared provenance. |
| inputs / outputs | Physical observations plus initialization context and declared benchmark pointer. |
| invariants | Reads optional counters/configuration, not a logical state snapshot or new experiment. |
| ownership | Returned snapshot owns fixed values/shared immutable context. |
| failure | Moved facade/delegated report errors propagate. |
| cost | Fixed/registry report work; no tuple population scan. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0202

[Lines 1834–1836](../../../../../src/runtime/delta.cpp#L1834); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTrace DeltaRuntime::observation_trace() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export optional physical observation trace with Delta snapshot. |
| inputs / outputs | Delegates physical trace then replaces snapshot via observations. |
| invariants | Trace retains only configured bounded diagnostic events, never substitute for mandatory E journal discovery. |
| ownership | Caller trace DTO owns copied events and report metadata. |
| failure | Export/allocation errors propagate. |
| cost | O(retained trace entries) copy plus fixed snapshot. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md) |

## B0203

[Lines 1837–1839](../../../../../src/runtime/delta.cpp#L1837); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedObservationTrace DeltaRuntime::capture_observation_trace() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture retained native observation trace with Delta snapshot. |
| inputs / outputs | Delegates account-funded physical capture then fills observations. |
| invariants | Same event facts, original account remains retained owner. |
| ownership | Capture event arrays/payloads funded by original query account. |
| failure | Capture/allocation errors propagate. |
| cost | O(retained trace entries) native copy and fixed snapshot. |
| Design | [docs/observability.md](../../../../observability.md), [docs/delta_lifecycle.md](../../../../delta_lifecycle.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0204

[Lines 1840–1843](../../../../../src/runtime/delta.cpp#L1840); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool DeltaRuntime::same_sources(const DeltaRuntime& other,reoptimization::detail::Budget& budget) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare committed physical sources under caller reoptimization budget. |
| inputs / outputs | Both Delta owners require writer barrier, then physical.same_sources. |
| invariants | Does not compare L caches or fabricate candidate correctness from fingerprints alone. |
| ownership | Borrows both retained owners and mutable budget; no new state cache. |
| failure | Either busy owner or budget/native/resource failure propagates. |
| cost | Delegated source comparison population/key-byte work under shared supplied budget. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/reoptimization.md](../../../../reoptimization.md) |

## B0205

[Lines 1844–1846](../../../../../src/runtime/delta.cpp#L1844); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1844-L1846:sha256:8a289c52265f032d42385d65af77db38f02dd5350de0eb04b777a405216fc9ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: opens namespace \`crown::runtime\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0206

[Lines 1847–1849](../../../../../src/runtime/delta.cpp#L1847); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::configure_workload_statistics(const workload::Options& options) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure workload statistics at writer barrier. |
| inputs / outputs | Options delegate to physical.configure_workload_statistics. |
| invariants | No pending/output/read lease permitted; configuration does not change logical query results. |
| ownership | Existing physical workload state/account remains authority. |
| failure | Busy/invalid options/resource errors propagate. |
| cost | Configuration validation and any bounded retained-report setup; not propagation. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0207

[Lines 1850–1852](../../../../../src/runtime/delta.cpp#L1850); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void DeltaRuntime::reset_workload_statistics() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset workload statistics at writer barrier. |
| inputs / outputs | Delegates physical reset after writable guard. |
| invariants | Resets reporting history, not sequence/source/support/live state or work grants. |
| ownership | Mutates established workload state only. |
| failure | Busy/delegated reset errors propagate. |
| cost | Fixed/bounded registry reset and retained report cleanup. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0208

[Lines 1853–1855](../../../../../src/runtime/delta.cpp#L1853); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::Snapshot DeltaRuntime::workload_statistics() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read workload snapshot with explicit pending availability. |
| inputs / outputs | Program/owner/committed sequence/processing passed to workload.snapshot. |
| invariants | Pending state is represented in report instead of exposing tentative source facts; no Delta readable guard. |
| ownership | Returned report retains its specified native/caller metadata only. |
| failure | Moved/report resource failures propagate. |
| cost | Explicit report construction over retained workload/query descriptors; no answer enumeration. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0209

[Lines 1856–1856](../../../../../src/runtime/delta.cpp#L1856); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::Options DeltaRuntime::workload_statistics_options() const { return impl().workload->options(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read workload reporting options. |
| inputs / outputs | Returns workload-&gt;options(). |
| invariants | Does not mutate/reset capture or deterministic production caps. |
| ownership | Fixed value copy. |
| failure | Moved facade rejects. |
| cost | Fixed metadata copy. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0210

[Lines 1857–1857](../../../../../src/runtime/delta.cpp#L1857); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1857-L1857:sha256:c4b9c3fab52d74ef772a80090ef4a35760b5a3b41ee88be876eed0db22a2fcbd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0211

[Lines 1858–1860](../../../../../src/runtime/delta.cpp#L1858); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void RuntimeTestProbe::seed_c01_report_saturation(DeltaRuntime& runtime) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed workload report saturation in tests. |
| inputs / outputs | Writable test owner calls workload seed. |
| invariants | Diagnostic saturation fixture only; source/query state unchanged. |
| ownership | Existing report state. |
| failure | Busy/moved owner rejects. |
| cost | Fixed testing mutation. |
| Design | [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp), [docs/statistics.md](../../../../statistics.md) |

## B0212

[Lines 1861–1864](../../../../../src/runtime/delta.cpp#L1861); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "owner_statistics_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import private owner-statistics builder for delegated capture. |
| inputs / outputs | owner_statistics_detail.hpp include following namespace closure. |
| invariants | Reporting authority remains explicit, separate from Delta update primitive. |
| ownership | Compile-time declarations only. |
| failure | Missing/type-incompatible dependency fails compilation. |
| cost | No runtime work for include. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0213

[Lines 1865–1867](../../../../../src/runtime/delta.cpp#L1865); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::OwnerCapture DeltaRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture statistics from owning request form. |
| inputs / outputs | OwnerRequest/limits delegate to request-view overload. |
| invariants | Does not copy/refill budgets or inspect tentative state. |
| ownership | Request borrowed for synchronous capture; returned capture owns retained report. |
| failure | Delegated capture/resource errors propagate. |
| cost | Fixed wrapper plus actual requested components. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0214

[Lines 1868–1873](../../../../../src/runtime/delta.cpp#L1868); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::OwnerCapture DeltaRuntime::capture_statistics_view(statistics::OwnerRequestView request,statistics::Limits limits) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture committed statistics or explicit pending-unavailable report. |
| inputs / outputs | Original StorageOperation and request view/limits. processing uses pending OwnerBuilder; otherwise physical native capture. |
| invariants | Pending prefix never leaks through statistic capture; committed output alone permits committed facts. |
| ownership | Builder/results funded by original query account as specified; request borrow lasts call. |
| failure | Storage/request/budget/resource failure follows statistics partial/report contract; no mutation rollback. |
| cost | Requested report/component work; pending branch creates metadata-only availability report, not full logical scan. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0215

[Lines 1874–1876](../../../../../src/runtime/delta.cpp#L1874); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::Freshness DeltaRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assess captured statistics freshness. |
| inputs / outputs | Capture and max event lag delegate to physical.statistics_freshness. |
| invariants | Freshness checks owner/sequence/availability; it does not silently recapture or validate full values. |
| ownership | Borrows capture; returns fixed freshness value. |
| failure | Moved/delegated validation failure propagates. |
| cost | Fixed freshness metadata comparison. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0216

[Lines 1877–1879](../../../../../src/runtime/delta.cpp#L1877); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1877-L1879:sha256:9e2f18da6f8adce73571e3f18b38528116ccefb4e7fba17887471ac59051fd9b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/delta.cpp: opens namespace \`crown::runtime::memory::detail\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0217

[Lines 1880–1905](../../../../../src/runtime/delta.cpp#L1880); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Access::append(Builder& builder,const DeltaRuntime& owner) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append physical and Delta live ownership rows to memory report. |
| inputs / outputs | Builder and Delta owner; checks mode/tag/dimensions, bucket value-vs-size and aggregate totals. |
| invariants | Reports account-attributed L/P/B cardinalities; equal sizes are consistency checks, not complete semantic membership proof. Local S/P/E reported by physical layer. |
| ownership | Builder owns funded report rows; scans existing native maps without copying full key sets. |
| failure | Inconsistent private state or report work/record limits throw internal Failure to capture adapter; never repairs source state. |
| cost | Visits factors and every live parent/child separator bucket plus delegated physical report; nested rows.size() is constant. No full answer enumeration. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0218

[Lines 1906–1914](../../../../../src/runtime/delta.cpp#L1906); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt Access::capture(const DeltaRuntime& owner,Limits limits) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a bounded memory report without throwing through public noexcept adapter. |
| inputs / outputs | Limits and Delta owner; attempt builds committed append report or pending availability header. |
| invariants | Invalid moved facade reported as invalid_handle; pending skips committed table/operator walks but still captures the account partition. |
| ownership | Original account funds retained report; usage/attempt captures explicit completeness/failure status. |
| failure | noexcept attempt owns Failure/resource/error translation; callback itself allocates/throws normally within that adapter. |
| cost | Explicit physical/bucket/factor report work when committed; pending still scans/sorts resident account attribution. Allocator/report payload costs remain real. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0219

[Lines 1915–1915](../../../../../src/runtime/delta.cpp#L1915); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1915-L1915:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::memory::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::memory::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::memory::detail\` at its lexical source position in src/runtime/delta.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::memory::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/delta_runtime.md](../../../../delta_runtime.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
