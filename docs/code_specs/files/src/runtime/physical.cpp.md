# `src/runtime/physical.cpp` — block usage map

[Source](../../../../../src/runtime/physical.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Compose one full physical source update across all its aliases into one atomic logical support epoch.

Snapshot SHA-256: `c2c24df75773ef1ed6523cd55279745a88c5e4c378da3c95a6f243ba526ee78c`. 1067 lines partitioned into 137 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [physical](../../../subsystem_contracts.md#physical). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–28](../../../../../src/runtime/physical.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // This explicit image operation has one selected balance. Indexed traversal · [reviewed contract](#b0001) |
| [B0002 · 29–42](../../../../../src/runtime/physical.cpp#L29) | Type/record definition: struct SourceImageBudget | 1 loop sites; source comment (unverified): // This explicit image operation has one selected balance. Indexed traversal · [reviewed contract](#b0002) |
| [B0003 · 43–48](../../../../../src/runtime/physical.cpp#L43) | Callable definition: template&lt;class T&gt; void source_image_slots(storage::IndexWorkAllowance* work,std::size_t count) | calls storage::IndexFailure, admit · [reviewed contract](#b0003) |
| [B0004 · 49–51](../../../../../src/runtime/physical.cpp#L49) | Callable definition: void require(bool condition,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view code,std::string_view message) { · [reviewed contract](#b0004) |
| [B0005 · 52–55](../../../../../src/runtime/physical.cpp#L52) | Callable definition: void add_size(std::size_t& target,std::size_t amount) | calls require, max; guard require(amount&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-target,"storage_overflow","physical storage… · [reviewed contract](#b0005) |
| [B0006 · 56–60](../../../../../src/runtime/physical.cpp#L56) | Callable definition: void add_statistics(storage::ArenaStatistics& target,const storage::ArenaStatistics& value) | calls add_size · [reviewed contract](#b0006) |
| [B0007 · 61–62](../../../../../src/runtime/physical.cpp#L61) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0007) |
| [B0008 · 63–65](../../../../../src/runtime/physical.cpp#L63) | Callable definition: physical::SourceImage::SourceImage(const resource::MemoryAccount& account,std::uint64_t epoch,const CompiledProgram& source) :seq… | calls sequence, program, tables · [reviewed contract](#b0008) |
| [B0009 · 66–67](../../../../../src/runtime/physical.cpp#L66) | declares namespace scope. |  · [reviewed contract](#b0009) |
| [B0010 · 68–74](../../../../../src/runtime/physical.cpp#L68) | Callable definition: std::uint64_t new_source_memory_owner() | calls load, resource::MemoryFailure, compare_exchange_weak; returns value+1; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 75–75](../../../../../src/runtime/physical.cpp#L75) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |
| [B0012 · 76–83](../../../../../src/runtime/physical.cpp#L76) | Type/record definition: struct CompactRowLess | returns a.view()&lt;b.view(); a.view()&lt;b · [reviewed contract](#b0012) |
| [B0013 · 84–84](../../../../../src/runtime/physical.cpp#L84) | Callable definition: template&lt;class Failure&gt; \[\[noreturn\]\] void present(const Failure& failure) | calls Error, std::string, code, what · [reviewed contract](#b0013) |
| [B0014 · 85–92](../../../../../src/runtime/physical.cpp#L85) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Per-occurrence std::map counts, distinct from the exact-node AVL helper. · [reviewed contract](#b0014) |
| [B0015 · 93–93](../../../../../src/runtime/physical.cpp#L93) | Callable definition: \[\[nodiscard\]\] storage::IndexWorkAllowance* work() const | calls detail::compact_storage_work; returns detail::compact_storage_work(storage_context) · [reviewed contract](#b0015) |
| [B0016 · 94–105](../../../../../src/runtime/physical.cpp#L94) | declares values/defaults or compile-time conditions. | source comment (unverified): // Readable handles share the program's actual accounted native layouts. · [reviewed contract](#b0016) |
| [B0017 · 106–143](../../../../../src/runtime/physical.cpp#L106) | Callable definition: template&lt;class Source&gt; Impl(Source plan,PhysicalRuntimeOptions value,std::shared_ptr&lt;detail::StorageWorkContext&gt; context):options… | calls options, storage_context, std::move, kernel; guard require(options.derivation_limit&gt;0,"invalid_options","physical derivation limit must be positive");; returns item.status==ConstraintStatus::enforced; growth emplace_back, push_back, reserve; 4 loop sites · [reviewed contract](#b0017) |
| [B0018 · 144–144](../../../../../src/runtime/physical.cpp#L144) | Callable definition: void readable() const | calls require; guard void readable() const { require(!updating,"runtime_busy","a prepared physical update is active"); } · [reviewed contract](#b0018) |
| [B0019 · 145–145](../../../../../src/runtime/physical.cpp#L145) | Callable definition: void writable() const | calls readable, require, ready; guard void writable() const { readable(); require(kernel.ready(),"runtime_busy","result cursors pin the c… · [reviewed contract](#b0019) |
| [B0020 · 146–148](../../../../../src/runtime/physical.cpp#L146) | Callable definition: storage::AccountedStorageTable& source(TableId table) | calls require, size; guard require(table.value&lt;sources.size(),"invalid_physical_update","source table is outside the catalog")…; returns sources\[table.value\] · [reviewed contract](#b0020) |
| [B0021 · 149–152](../../../../../src/runtime/physical.cpp#L149) | Callable definition: const program::PhysicalInput& input(OccurrenceId occurrence) const | calls require, compiled_program, inputs, size; guard require(occurrence.value&lt;kernel.compiled_program().inputs().size(),"invalid_input_port","physical p…; returns kernel.compiled_program().inputs()\[occurrence.value\] · [reviewed contract](#b0021) |
| [B0022 · 153–189](../../../../../src/runtime/physical.cpp#L153) | Callable definition: physical::SourceImage source_image(physical::SourceImageLimits limits,std::uint64_t epoch, const std::optional&lt;storage::Accounted… | calls take, size, Error, work; returns image; growth emplace_back, push_back, reserve; 3 loop sites; source comment (unverified): // Admit directory/row capacity before allocation. Each payload is scanned · [reviewed contract](#b0022) |
| [B0023 · 190–191](../../../../../src/runtime/physical.cpp#L190) | Explanatory comments or spacing. | source comment (unverified): // Snapshots deep-copy funded tuples, then sort full values to preserve · [reviewed contract](#b0023) |
| [B0024 · 192–202](../../../../../src/runtime/physical.cpp#L192) | Callable definition: detail::NativeDatabase native_database() const | calls result, memory, reserve, size; returns a.values()&lt;b.values(); result; growth push_back, reserve; 1 loop sites; source comment (unverified): // Snapshots deep-copy funded tuples, then sort full values to preserve · [reviewed contract](#b0024) |
| [B0025 · 203–208](../../../../../src/runtime/physical.cpp#L203) | Callable definition: Database database() const | calls resize, size, snapshot, work; returns result; growth insert, resize; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 209–218](../../../../../src/runtime/physical.cpp#L209) | Callable definition: PhysicalSnapshot snapshot(SupportSnapshot support) const | calls database, std::move, resize, size; returns result; growth push_back, reserve, resize; 2 loop sites · [reviewed contract](#b0026) |
| [B0027 · 219–226](../../../../../src/runtime/physical.cpp#L219) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;PhysicalPreview&gt;); · [reviewed contract](#b0027) |
| [B0028 · 227–227](../../../../../src/runtime/physical.cpp#L227) | Type/record definition: enum class CountKind |  · [reviewed contract](#b0028) |
| [B0029 · 228–234](../../../../../src/runtime/physical.cpp#L228) | Type/record definition: struct CountUndo |  · [reviewed contract](#b0029) |
| [B0030 · 235–250](../../../../../src/runtime/physical.cpp#L235) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;CountUndo&gt;);; source comment (unverified): // Optional bookkeeping records successful nested charges, never an inference · [reviewed contract](#b0030) |
| [B0031 · 251–258](../../../../../src/runtime/physical.cpp#L251) | Callable definition: Data(std::shared_ptr&lt;Impl&gt; value,const PhysicalUpdateView& update) :owner(std::move(value)),storage_lease(detail::storage_lease(o… | calls owner, std::move, storage_lease, detail::storage_lease · [reviewed contract](#b0031) |
| [B0032 · 259–259](../../../../../src/runtime/physical.cpp#L259) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0032) |
| [B0033 · 260–262](../../../../../src/runtime/physical.cpp#L260) | Callable definition: Impl& active() const | calls require; guard require(owner && logical && logical-&gt;active(),"invalid_epoch","prepared physical update is closed")…; returns *owner · [reviewed contract](#b0033) |
| [B0034 · 263–287](../../../../../src/runtime/physical.cpp#L263) | Callable definition: void observe() const noexcept | calls set, unavailable; source comment (unverified): // Every successful charge is part of metrics.work, so this subtraction · [reviewed contract](#b0034) |
| [B0035 · 288–294](../../../../../src/runtime/physical.cpp#L288) | Callable definition: void charge(std::uint64_t amount=1) | calls require, max; guard require(amount&lt;=std::numeric_limits&lt;std::uint64_t&gt;::max()-work,"resource_limit","physical work coun… · [reviewed contract](#b0035) |
| [B0036 · 295–299](../../../../../src/runtime/physical.cpp#L295) | Callable definition: void metric(std::uint64_t& counter,std::uint64_t amount=1) | calls charge; source comment (unverified): // Every managed category is a subset of cumulative charged work. · [reviewed contract](#b0036) |
| [B0037 · 300–321](../../../../../src/runtime/physical.cpp#L300) | Callable definition: void rollback() noexcept | calls observe, rbegin, rend, erase; growth insert; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 322–335](../../../../../src/runtime/physical.cpp#L322) | Callable definition: void validate_constraints() | calls after, memory, reserve, size; growth push_back, reserve; 1 loop sites; source comment (unverified): // Complete after-state, including unused tables and self-FKs. All compact · [reviewed contract](#b0038) |
| [B0039 · 336–339](../../../../../src/runtime/physical.cpp#L336) | Explanatory comments or spacing. | source comment (unverified): // One alias prefix of one physical set input. Full source rows determine · [reviewed contract](#b0039) |
| [B0040 · 340–396](../../../../../src/runtime/physical.cpp#L340) | Callable definition: void route(OccurrenceId occurrence,std::uint64_t prefix,storage::RowView row,const RouteObserver& observer,EpochViewOptions view_… | calls metric, event, input, compiled_program; guard if (add) require(before&lt;owner-&gt;options.derivation_limit,"derivation_overflow","native tuple derivat…; growth copy_of, emplace, insert, push_back; source comment (unverified): // One alias prefix of one physical set input. Full source rows determine · [reviewed contract](#b0040) |
| [B0041 · 397–420](../../../../../src/runtime/physical.cpp#L397) | Callable definition: void prepare(const storage::AccountedTuple& tuple,std::optional&lt;TupleHandle&gt; existing) | calls emplace, begin_epoch, physical_fact, has_value; guard require(inserted.inserted,"runtime_contract","physical source insertion duplicated membership");; growth emplace, insert, reserve; source comment (unverified): // begin_staged owns this complete Data until preparation succeeds. Any · [reviewed contract](#b0041) |
| [B0042 · 421–422](../../../../../src/runtime/physical.cpp#L421) | Closes surrounding scope/type. |  · [reviewed contract](#b0042) |
| [B0043 · 423–423](../../../../../src/runtime/physical.cpp#L423) | Callable definition: PhysicalRuntime::PendingUpdate::PendingUpdate(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0043) |
| [B0044 · 424–424](../../../../../src/runtime/physical.cpp#L424) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0044) |
| [B0045 · 425–428](../../../../../src/runtime/physical.cpp#L425) | Callable definition: PhysicalRuntime::PendingUpdate& PhysicalRuntime::PendingUpdate::operator=(PendingUpdate&& other) noexcept | calls ; returns *this · [reviewed contract](#b0045) |
| [B0046 · 429–429](../../../../../src/runtime/physical.cpp#L429) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0046) |
| [B0047 · 430–430](../../../../../src/runtime/physical.cpp#L430) | Callable definition: bool PhysicalRuntime::PendingUpdate::active() const noexcept | calls active; returns data_ && data_-&gt;owner && data_-&gt;logical && data_-&gt;logical-&gt;active() · [reviewed contract](#b0047) |
| [B0048 · 431–442](../../../../../src/runtime/physical.cpp#L431) | Callable definition: bool PhysicalRuntime::PendingUpdate::stage_next(const RouteObserver& observer,EpochViewOptions options) try | calls require, bool, active, storage_operation; guard require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast&lt;void&gt;(data_-&gt;active(…; returns false; true; source comment (unverified): // The source pin owns the complete input row across calls and facade moves. · [reviewed contract](#b0048) |
| [B0049 · 443–443](../../../../../src/runtime/physical.cpp#L443) | Callable definition: void PhysicalRuntime::PendingUpdate::rollback() noexcept | calls rollback · [reviewed contract](#b0049) |
| [B0050 · 444–446](../../../../../src/runtime/physical.cpp#L444) | Callable definition: const PhysicalPreview& PhysicalRuntime::PendingUpdate::preview() const | calls require, bool, active; guard require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast&lt;void&gt;(data_-&gt;active(…; returns data_-&gt;output · [reviewed contract](#b0050) |
| [B0051 · 447–449](../../../../../src/runtime/physical.cpp#L447) | Callable definition: const SupportEpoch& PhysicalRuntime::PendingUpdate::support() const | calls require, bool, active, preview; guard require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast&lt;void&gt;(data_-&gt;active(…; returns data_-&gt;logical-&gt;preview() · [reviewed contract](#b0051) |
| [B0052 · 450–454](../../../../../src/runtime/physical.cpp#L450) | Callable definition: PhysicalSnapshot PhysicalRuntime::PendingUpdate::snapshot() const try | calls require, bool, storage_operation, active; guard require(bool(data_),"invalid_epoch","moved-from physical update");; returns data_-&gt;active().snapshot(data_-&gt;logical-&gt;snapshot()) · [reviewed contract](#b0052) |
| [B0053 · 455–460](../../../../../src/runtime/physical.cpp#L455) | Callable definition: physical::SourceImage PhysicalRuntime::PendingUpdate::source_image(physical::SourceImageLimits limits) const | calls require, bool, active, operation; guard require(bool(data_),"invalid_epoch","moved-from physical update");auto& d=data_-&gt;active();; returns d.source_image(limits,data_-&gt;output.sequence,&data_-&gt;source,data_-&gt;output.table) · [reviewed contract](#b0053) |
| [B0054 · 461–464](../../../../../src/runtime/physical.cpp#L461) | Callable definition: SupportRuntime::EpochView PhysicalRuntime::PendingUpdate::view(SnapshotSide side,EpochViewOptions options) | calls require, bool, active, view; guard require(bool(data_),"invalid_epoch","moved-from physical update"); static_cast&lt;void&gt;(data_-&gt;active(…; returns data_-&gt;logical-&gt;view(side,options) · [reviewed contract](#b0054) |
| [B0055 · 465–481](../../../../../src/runtime/physical.cpp#L465) | Callable definition: PhysicalEpoch PhysicalRuntime::PendingUpdate::commit() | calls require, bool, active, observe; guard require(bool(data_),"invalid_epoch","moved-from physical update"); auto& d=data_-&gt;active();; returns result; source comment (unverified): // The logical token is private and validated above. All operations from this · [reviewed contract](#b0055) |
| [B0056 · 482–482](../../../../../src/runtime/physical.cpp#L482) | Explanatory comments or spacing. |  |
| [B0057 · 483–484](../../../../../src/runtime/physical.cpp#L483) | Callable definition: PhysicalRuntime::PhysicalRuntime(PhysicalPlan plan,PhysicalRuntimeOptions options) :PhysicalRuntime(plan,options,detail::storage_… | calls PhysicalRuntime, detail::storage_context · [reviewed contract](#b0057) |
| [B0058 · 485–493](../../../../../src/runtime/physical.cpp#L485) | Callable definition: PhysicalRuntime::PhysicalRuntime(CompiledProgram source,PhysicalRuntimeOptions options) try :impl_(\[&\] { auto context=detail::new… | calls impl_, detail::new_storage_context, operation, CompiledProgram::freeze; returns resource::make_accounted_shared&lt;Impl&gt;(context-&gt;memory(),resource::MemoryPurpose::support_metadata,s…; growth make_accounted_shared · [reviewed contract](#b0058) |
| [B0059 · 494–497](../../../../../src/runtime/physical.cpp#L494) | Callable definition: PhysicalRuntime::PhysicalRuntime(PlanSource plan,PhysicalRuntimeOptions options,std::shared_ptr&lt;detail::StorageWorkContext&gt; conte… | calls impl_, std::visit, detail::validate_storage_context, operation; returns std::visit(\[&\](auto& source) {detail::validate_storage_context(source,context,options.support.memor…; growth make_accounted_shared · [reviewed contract](#b0059) |
| [B0060 · 498–501](../../../../../src/runtime/physical.cpp#L498) | Callable definition: PhysicalRuntime PhysicalRuntime::initialize(PhysicalPlan plan,const Database& database, PhysicalRuntimeOptions options,BuildOptio… | calls initialize_at, std::move; returns initialize_at(std::move(plan),database,options,build,0) · [reviewed contract](#b0060) |
| [B0061 · 502–507](../../../../../src/runtime/physical.cpp#L502) | Callable definition: PhysicalRuntime PhysicalRuntime::initialize(CompiledProgram source,const Database& database, PhysicalRuntimeOptions options,Build… | calls detail::new_storage_context, operation, CompiledProgram::freeze, memory; returns initialize_at(std::move(plan),database,options,build,0,{},std::move(context)) · [reviewed contract](#b0061) |
| [B0062 · 508–512](../../../../../src/runtime/physical.cpp#L508) | Callable definition: PhysicalRuntime PhysicalRuntime::initialize_at(PlanSource plan,const Database& database, PhysicalRuntimeOptions options,BuildOpti… | calls initialize_data, std::move; returns initialize_data(std::move(plan),database,options,build,sequence,prefix,std::move(context)) · [reviewed contract](#b0062) |
| [B0063 · 513–582](../../../../../src/runtime/physical.cpp#L513) | Callable definition: template&lt;class DatabaseView&gt; PhysicalRuntime PhysicalRuntime::initialize_data(PlanSource plan,const DatabaseView& database, Physi… | calls std::visit, detail::storage_context, storage_operation, require; guard require(build.method==BuildMethod::direct \|\| build.method==BuildMethod::insertion_replay,; returns detail::storage_context(source,options.support.memory_limit_bytes); result; growth copy_of, emplace, insert, push_back, reserve; 6 loop sites; source comment (unverified): // Validate the complete final snapshot before either unpublished build path. · [reviewed contract](#b0063) |
| [B0064 · 583–586](../../../../../src/runtime/physical.cpp#L583) | Callable definition: PhysicalRuntime PhysicalRuntime::rebuilt(BuildOptions build) const | calls impl, writable, rebuilt, detail::storage_context; returns rebuilt(build,detail::storage_context(d.kernel.plan(),d.options.support.memory_limit_bytes,d.storag… · [reviewed contract](#b0064) |
| [B0065 · 587–614](../../../../../src/runtime/physical.cpp#L587) | Callable definition: recovery::EncodedImage PhysicalRuntime::checkpoint_image(const recovery::ImageBinding& binding, recovery::ImageLimits limits) con… | calls impl, writable, operation, size; returns recovery::encode_image(account,{binding,d.sequence},tables,limits); growth emplace_back, push_back, reserve; 3 loop sites; source comment (unverified): // Codec work accounting excludes this deep snapshot/sort. The original · [reviewed contract](#b0065) |
| [B0066 · 615–658](../../../../../src/runtime/physical.cpp#L615) | Callable definition: PhysicalRuntime PhysicalRuntime::restore_image(CompiledProgram source,std::string_view bytes, PhysicalRuntimeOptions options,Buil… | calls operation, recovery::decode_image, memory, recovery::ImageFailure; guard const auto charge=\[&\](std::uint64_t amount) {check(amount&lt;=remaining,recovery::ImageFault::work);re…; returns a.table&lt;b.table; a.values&lt;b.values; growth insert; 4 loop sites · [reviewed contract](#b0066) |
| [B0067 · 659–661](../../../../../src/runtime/physical.cpp#L659) | Callable definition: PhysicalRuntime PhysicalRuntime::rebuilt(BuildOptions build,std::shared_ptr&lt;detail::StorageWorkContext&gt; context) const try | calls rebuilt_with_program, impl, plan, std::move; returns rebuilt_with_program(impl().kernel.plan(),build,std::move(context)) · [reviewed contract](#b0067) |
| [B0068 · 662–670](../../../../../src/runtime/physical.cpp#L662) | Callable definition: PhysicalRuntime PhysicalRuntime::rebuilt_for(const planner::MinimumHeightCandidate& candidate,BuildOptions build, const program::… | calls impl, writable, CompiledProgram::replan, plan; returns rebuilt_with_program(std::move(target),build,std::move(context)); source comment (unverified): // Native lowering independently checks typed candidate/source identity. It · [reviewed contract](#b0068) |
| [B0069 · 671–695](../../../../../src/runtime/physical.cpp#L671) | Callable definition: PhysicalRuntime PhysicalRuntime::rebuilt_with_program(CompiledProgram target,BuildOptions build, std::shared_ptr&lt;detail::StorageW… | calls impl, writable, detail::validate_storage_context, memory; guard require(build.method==BuildMethod::direct \|\| build.method==BuildMethod::insertion_replay,; returns result; 1 loop sites; source comment (unverified): // Consult the cumulative budget before materializing either the intermediate · [reviewed contract](#b0069) |
| [B0070 · 696–697](../../../../../src/runtime/physical.cpp#L696) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0070) |
| [B0071 · 698–701](../../../../../src/runtime/physical.cpp#L698) | Callable definition: PhysicalRuntime& PhysicalRuntime::operator=(PhysicalRuntime&& other) noexcept | calls ; returns *this · [reviewed contract](#b0071) |
| [B0072 · 702–702](../../../../../src/runtime/physical.cpp#L702) | Callable definition: PhysicalRuntime::Impl& PhysicalRuntime::impl() const | calls require, bool; guard PhysicalRuntime::Impl& PhysicalRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved…; returns *impl_ · [reviewed contract](#b0072) |
| [B0073 · 703–703](../../../../../src/runtime/physical.cpp#L703) | Callable definition: const CompiledProgram& PhysicalRuntime::plan() const | calls impl, plan; returns impl().kernel.plan() · [reviewed contract](#b0073) |
| [B0074 · 704–704](../../../../../src/runtime/physical.cpp#L704) | Callable definition: const CompiledProgram& PhysicalRuntime::compiled_program() const | calls impl, compiled_program; returns impl().kernel.compiled_program() · [reviewed contract](#b0074) |
| [B0075 · 705–705](../../../../../src/runtime/physical.cpp#L705) | Callable definition: resource::MemoryStatistics PhysicalRuntime::accounted_memory_statistics() const | calls impl, accounted_memory_statistics; returns impl().kernel.accounted_memory_statistics() · [reviewed contract](#b0075) |
| [B0076 · 706–706](../../../../../src/runtime/physical.cpp#L706) | Callable definition: const PhysicalRuntimeOptions& PhysicalRuntime::options() const | calls impl; returns impl().options · [reviewed contract](#b0076) |
| [B0077 · 707–707](../../../../../src/runtime/physical.cpp#L707) | Callable definition: SupportOwnerId PhysicalRuntime::owner() const | calls impl, owner; returns impl().kernel.owner() · [reviewed contract](#b0077) |
| [B0078 · 708–708](../../../../../src/runtime/physical.cpp#L708) | Callable definition: std::uint64_t PhysicalRuntime::sequence() const | calls impl; returns impl().sequence · [reviewed contract](#b0078) |
| [B0079 · 709–709](../../../../../src/runtime/physical.cpp#L709) | Callable definition: bool PhysicalRuntime::ready() const | calls impl, ready; returns !d.updating && d.kernel.ready() · [reviewed contract](#b0079) |
| [B0080 · 710–710](../../../../../src/runtime/physical.cpp#L710) | Callable definition: bool PhysicalRuntime::has_answer() const | calls impl, readable, has_answer; returns d.kernel.has_answer() · [reviewed contract](#b0080) |
| [B0081 · 711–711](../../../../../src/runtime/physical.cpp#L711) | Callable definition: const storage::TupleLayout& PhysicalRuntime::source_layout(TableId table) const | calls impl, source; returns d.source_layouts\[table.value\] · [reviewed contract](#b0081) |
| [B0082 · 712–712](../../../../../src/runtime/physical.cpp#L712) | Callable definition: const storage::TupleLayout& PhysicalRuntime::result_layout(ResultView view) const | calls impl, result_layout; returns impl().kernel.result_layout(view) · [reviewed contract](#b0082) |
| [B0083 · 713–715](../../../../../src/runtime/physical.cpp#L713) | Callable definition: PhysicalRuntime::PendingUpdate PhysicalRuntime::prepare(const PhysicalSetUpdate& update) | calls prepare_observed; returns prepare_observed(update,{},{}) · [reviewed contract](#b0083) |
| [B0084 · 716–720](../../../../../src/runtime/physical.cpp#L716) | Callable definition: PhysicalRuntime::PendingUpdate PhysicalRuntime::prepare_observed(const PhysicalSetUpdate& update,const RouteObserver& observer,Ep… | calls begin_staged, stage_next; returns pending; 1 loop sites · [reviewed contract](#b0084) |
| [B0085 · 721–723](../../../../../src/runtime/physical.cpp#L721) | Callable definition: PhysicalRuntime::PendingUpdate PhysicalRuntime::begin_staged(const PhysicalSetUpdate& update) | calls begin_staged, PhysicalUpdateView::borrow; returns begin_staged(PhysicalUpdateView::borrow(update)) · [reviewed contract](#b0085) |
| [B0086 · 724–734](../../../../../src/runtime/physical.cpp#L724) | Callable definition: PhysicalRuntime::PendingUpdate PhysicalRuntime::begin_staged(const PhysicalUpdateView& update) try | calls storage_operation, impl, writable, require; guard require(d.sequence!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"sequence_overflow","physical update …; returns PendingUpdate(std::move(data)); growth insert, make_accounted_unique · [reviewed contract](#b0086) |
| [B0087 · 735–736](../../../../../src/runtime/physical.cpp#L735) | Explanatory comments or spacing. | source comment (unverified): // Even a physical no-op pays row validation/import/probe/owner admission; · [reviewed contract](#b0087) |
| [B0088 · 737–737](../../../../../src/runtime/physical.cpp#L737) | Callable definition: PhysicalEpoch PhysicalRuntime::apply(const PhysicalSetUpdate& update) | calls prepare, commit; returns prepare(update).commit(); source comment (unverified): // Even a physical no-op pays row validation/import/probe/owner admission; · [reviewed contract](#b0088) |
| [B0089 · 738–740](../../../../../src/runtime/physical.cpp#L738) | Callable definition: PhysicalEpoch PhysicalRuntime::apply_view(const PhysicalUpdateView& update) | calls begin_staged, stage_next, commit; returns pending.commit(); 1 loop sites · [reviewed contract](#b0089) |
| [B0090 · 741–743](../../../../../src/runtime/physical.cpp#L741) | Callable definition: SupportRuntime::ResultCursor PhysicalRuntime::results(ResultCursorOptions options) const | calls impl, readable, results; returns d.kernel.results(options,ResultView::sql) · [reviewed contract](#b0090) |
| [B0091 · 744–746](../../../../../src/runtime/physical.cpp#L744) | Callable definition: SupportRuntime::ResultCursor PhysicalRuntime::core_results(ResultCursorOptions options) const | calls impl, readable, results; returns d.kernel.results(options,ResultView::core) · [reviewed contract](#b0091) |
| [B0092 · 747–749](../../../../../src/runtime/physical.cpp#L747) | Callable definition: SupportRuntime::EpochView PhysicalRuntime::current_view(EpochViewOptions options) const | calls impl, readable, current_view; returns d.kernel.current_view(options) · [reviewed contract](#b0092) |
| [B0093 · 750–752](../../../../../src/runtime/physical.cpp#L750) | Callable definition: SupportRuntime::ResultCursor PhysicalRuntime::completions(const FixedAssignment& fixed,VisibleFragment fragment,ResultCursorOptio… | calls impl, readable, completions; returns d.kernel.completions(fixed,fragment,options) · [reviewed contract](#b0093) |
| [B0094 · 753–755](../../../../../src/runtime/physical.cpp#L753) | Callable definition: SupportRuntime::ResultCursor PhysicalRuntime::witnesses(const FixedAssignment& fixed,WitnessFragment fragment,ResultCursorOptions… | calls impl, readable, witnesses, std::move; returns d.kernel.witnesses(fixed,std::move(fragment),options) · [reviewed contract](#b0094) |
| [B0095 · 756–757](../../../../../src/runtime/physical.cpp#L756) | Callable definition: PhysicalSnapshot PhysicalRuntime::snapshot() const try | calls storage_operation, impl, readable, snapshot; returns d.snapshot(d.kernel.snapshot()) · [reviewed contract](#b0095) |
| [B0096 · 758–761](../../../../../src/runtime/physical.cpp#L758) | Callable definition: physical::SourceImage PhysicalRuntime::source_image(physical::SourceImageLimits limits) const | calls impl, readable, operation, source_image; returns d.source_image(limits,d.sequence) · [reviewed contract](#b0096) |
| [B0097 · 762–765](../../../../../src/runtime/physical.cpp#L762) | Callable definition: std::uint64_t PhysicalRuntime::derivation_count(OccurrenceId occurrence,const Row& values) const | calls impl, readable, input, plan; returns found==counts.end()?0:found-&gt;second · [reviewed contract](#b0097) |
| [B0098 · 766–769](../../../../../src/runtime/physical.cpp#L766) | Callable definition: std::optional&lt;TupleHandle&gt; PhysicalRuntime::find_source(TableId table,const Row& values) const try | calls storage_operation, impl, readable, source; returns source.find(source.layout().tuple(values), d.work()) · [reviewed contract](#b0098) |
| [B0099 · 770–775](../../../../../src/runtime/physical.cpp#L770) | Callable definition: std::optional&lt;storage::AccountedTuple&gt; PhysicalRuntime::get_source(TableId table,TupleHandle handle) const try | calls storage_operation, impl, readable, source; returns {}; tuple-&gt;layout().tuple(tuple-&gt;values(),{resource::MemoryOwnerKind::output,source.owner().value}) · [reviewed contract](#b0099) |
| [B0100 · 776–778](../../../../../src/runtime/physical.cpp#L776) | Callable definition: std::optional&lt;SupportHandle&gt; PhysicalRuntime::find_support(NodeId node,SupportRole role,const Row& values) const | calls impl, readable, find; returns d.kernel.find(node,role,values) · [reviewed contract](#b0100) |
| [B0101 · 779–781](../../../../../src/runtime/physical.cpp#L779) | Callable definition: std::optional&lt;storage::Tuple&gt; PhysicalRuntime::get_support(SupportHandle handle) const | calls impl, readable, get; returns d.kernel.get(handle) · [reviewed contract](#b0101) |
| [B0102 · 782–787](../../../../../src/runtime/physical.cpp#L782) | Callable definition: PhysicalStorageStatistics PhysicalRuntime::storage_statistics() const | calls impl, readable, storage_statistics, add_statistics; returns result; 2 loop sites · [reviewed contract](#b0102) |
| [B0103 · 788–788](../../../../../src/runtime/physical.cpp#L788) | Callable definition: InitializationContext PhysicalRuntime::initialization_context() const | calls impl; returns impl().initialization_context · [reviewed contract](#b0103) |
| [B0104 · 789–789](../../../../../src/runtime/physical.cpp#L789) | Callable definition: const BuildMetrics& PhysicalRuntime::initialization_metrics() const | calls impl; returns impl().build_metrics · [reviewed contract](#b0104) |
| [B0105 · 790–798](../../../../../src/runtime/physical.cpp#L790) | Callable definition: CanonicalPhysicalState PhysicalRuntime::canonical_state() const try | calls storage_operation, impl, readable, canonical_state; returns result; growth push_back, resize; 2 loop sites · [reviewed contract](#b0105) |
| [B0106 · 799–800](../../../../../src/runtime/physical.cpp#L799) | Explanatory comments or spacing. | source comment (unverified): // Independently recompute projected counts from sources, including a · [reviewed contract](#b0106) |
| [B0107 · 801–890](../../../../../src/runtime/physical.cpp#L801) | Callable definition: InvariantReport PhysicalRuntime::inspect_invariants(InspectionOptions options) const try | calls storage_operation, impl, readable, inspect_invariants; guard require(widest&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-2,"resource_limit","inspection row-width ac…; returns support; a.values()&lt;b.values(); growth push_back, reserve; 11 loop sites; source comment (unverified): // Independently recompute projected counts from sources, including a · [reviewed contract](#b0107) |
| [B0108 · 891–891](../../../../../src/runtime/physical.cpp#L891) | controls preprocessing. |  · [reviewed contract](#b0108) |
| [B0109 · 892–894](../../../../../src/runtime/physical.cpp#L892) | Callable definition: void RuntimeTestProbe::seed_physical_sequence(PhysicalRuntime& runtime,std::uint64_t sequence) | calls impl, writable, seed_sequence · [reviewed contract](#b0109) |
| [B0110 · 895–895](../../../../../src/runtime/physical.cpp#L895) | Callable definition: SupportRuntime& RuntimeTestProbe::support(PhysicalRuntime& runtime) | calls impl; returns runtime.impl().kernel · [reviewed contract](#b0110) |
| [B0111 · 896–901](../../../../../src/runtime/physical.cpp#L896) | Callable definition: std::uint64_t RuntimeTestProbe::set_derivation(PhysicalRuntime& runtime,OccurrenceId occurrence,const Row& key,std::uint64_t coun… | calls impl, readable, input, find; guard require(found!=d.counts\[occurrence.value\].end(),"invalid_probe","derivation corruption probe key is…; returns std::exchange(found-&gt;second,count) · [reviewed contract](#b0111) |
| [B0112 · 902–904](../../../../../src/runtime/physical.cpp#L902) | controls preprocessing. | source comment (unverified): // Full fail-fast recomputation, not a cheap flag check. Native snapshots, · [reviewed contract](#b0112) |
| [B0113 · 905–932](../../../../../src/runtime/physical.cpp#L905) | Callable definition: void PhysicalRuntime::check_invariants() const try | calls storage_operation, impl, readable, require; guard require(d.sequence==d.kernel.sequence(),"runtime_contract","physical and logical sequence differ");; 5 loop sites; source comment (unverified): // Full fail-fast recomputation, not a cheap flag check. Native snapshots, · [reviewed contract](#b0113) |
| [B0114 · 933–933](../../../../../src/runtime/physical.cpp#L933) | Callable definition: std::shared_ptr&lt;detail::ObservationState&gt; PhysicalRuntime::observation_state() const | calls impl; returns impl().observation · [reviewed contract](#b0114) |
| [B0115 · 934–934](../../../../../src/runtime/physical.cpp#L934) | Callable definition: std::optional&lt;CursorObservation&gt; PhysicalRuntime::last_cursor_observation() const | calls impl, last_cursor_observation; returns impl().kernel.last_cursor_observation() · [reviewed contract](#b0115) |
| [B0116 · 935–944](../../../../../src/runtime/physical.cpp#L935) | Callable definition: CommittedStateGauges PhysicalRuntime::committed_state_gauges() const | calls impl, readable, committed_state_gauges, reserve; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0116) |
| [B0117 · 945–954](../../../../../src/runtime/physical.cpp#L945) | Callable definition: CapturedStateGauges PhysicalRuntime::capture_state_gauges() const | calls impl, readable, capture_state_gauges, reserve; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0117) |
| [B0118 · 955–957](../../../../../src/runtime/physical.cpp#L955) | Callable definition: ObservationSnapshot PhysicalRuntime::observations() const | calls impl, observations; returns result · [reviewed contract](#b0118) |
| [B0119 · 958–960](../../../../../src/runtime/physical.cpp#L958) | Callable definition: ObservationTrace PhysicalRuntime::observation_trace() const | calls impl, observation_trace; returns result · [reviewed contract](#b0119) |
| [B0120 · 961–963](../../../../../src/runtime/physical.cpp#L961) | Callable definition: CapturedObservationTrace PhysicalRuntime::capture_observation_trace() const | calls impl, capture_observation_trace; returns result · [reviewed contract](#b0120) |
| [B0121 · 964–989](../../../../../src/runtime/physical.cpp#L964) | Callable definition: bool PhysicalRuntime::same_sources(const PhysicalRuntime& other,reoptimization::detail::Budget& budget) const | calls impl, writable, left_operation, right_operation; returns false; false; growth copy_of, insert; 3 loop sites · [reviewed contract](#b0121) |
| [B0122 · 990–992](../../../../../src/runtime/physical.cpp#L990) | declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0122) |
| [B0123 · 993–995](../../../../../src/runtime/physical.cpp#L993) | Callable definition: void PhysicalRuntime::configure_workload_statistics(const workload::Options& options) | calls impl, writable, configure, compiled_program · [reviewed contract](#b0123) |
| [B0124 · 996–998](../../../../../src/runtime/physical.cpp#L996) | Callable definition: void PhysicalRuntime::reset_workload_statistics() | calls impl, writable, reset · [reviewed contract](#b0124) |
| [B0125 · 999–1001](../../../../../src/runtime/physical.cpp#L999) | Callable definition: workload::Snapshot PhysicalRuntime::workload_statistics() const | calls impl, snapshot, compiled_program, owner; returns d.workload-&gt;snapshot(d.kernel.compiled_program(),d.kernel.owner(),d.sequence,d.updating) · [reviewed contract](#b0125) |
| [B0126 · 1002–1002](../../../../../src/runtime/physical.cpp#L1002) | Callable definition: workload::detail::State& PhysicalRuntime::workload_state() const | calls impl; returns *impl().workload · [reviewed contract](#b0126) |
| [B0127 · 1003–1003](../../../../../src/runtime/physical.cpp#L1003) | Callable definition: std::shared_ptr&lt;detail::StorageWorkContext&gt; PhysicalRuntime::storage_context() const | calls impl; returns impl().storage_context · [reviewed contract](#b0127) |
| [B0128 · 1004–1004](../../../../../src/runtime/physical.cpp#L1004) | controls preprocessing. |  · [reviewed contract](#b0128) |
| [B0129 · 1005–1007](../../../../../src/runtime/physical.cpp#L1005) | Callable definition: std::optional&lt;RuntimeStorageWork&gt; RuntimeTestProbe::index_work(const PhysicalRuntime& runtime) | calls index_work, impl; returns index_work(runtime.impl().kernel) · [reviewed contract](#b0129) |
| [B0130 · 1008–1011](../../../../../src/runtime/physical.cpp#L1008) | Imports dependencies; controls preprocessing; declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0130) |
| [B0131 · 1012–1014](../../../../../src/runtime/physical.cpp#L1012) | Callable definition: statistics::OwnerCapture PhysicalRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) c… | calls capture_statistics_view; returns capture_statistics_view(request,limits) · [reviewed contract](#b0131) |
| [B0132 · 1015–1040](../../../../../src/runtime/physical.cpp#L1015) | Callable definition: statistics::OwnerCapture PhysicalRuntime::capture_statistics_view(statistics::OwnerRequestView request,statistics::Limits limits)… | calls storage_operation, impl, owner, compiled_program; guard require(scope-&gt;table.value&lt;d.sources.size(),"invalid_statistics_request","source outside catalog");; returns builder.finish(); 2 loop sites · [reviewed contract](#b0132) |
| [B0133 · 1041–1043](../../../../../src/runtime/physical.cpp#L1041) | Callable definition: statistics::Freshness PhysicalRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag)… | calls impl, statistics::compare_freshness, stamp, owner; returns statistics::compare_freshness(captured.stamp(),{d.kernel.owner(),d.sequence,statistics::OwnerLayer:… · [reviewed contract](#b0133) |
| [B0134 · 1044–1046](../../../../../src/runtime/physical.cpp#L1044) | declares namespace scope. |  · [reviewed contract](#b0134) |
| [B0135 · 1047–1057](../../../../../src/runtime/physical.cpp#L1047) | Callable definition: void Access::append(Builder& builder,const PhysicalRuntime& owner) | calls impl, append, operation, size; 2 loop sites · [reviewed contract](#b0135) |
| [B0136 · 1058–1066](../../../../../src/runtime/physical.cpp#L1058) | Callable definition: Attempt Access::capture(const PhysicalRuntime& owner,Limits limits) noexcept | calls attempt, impl, plan, builder; returns attempt(\[&\](Usage& usage) {; builder.finish() · [reviewed contract](#b0136) |
| [B0137 · 1067–1067](../../../../../src/runtime/physical.cpp#L1067) | Closes surrounding scope/type. |  · [reviewed contract](#b0137) |

## B0001

[Lines 1–28](../../../../../src/runtime/physical.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include mutable runtime probe declarations only in testing compilation. |
| inputs / outputs | CROWN_RUNTIME_TESTING selects tests/support/runtime_probe.hpp through the testing target include path. |
| invariants | Production compilation excludes the probe include/body branches; test and production libraries must keep their separate build/link contracts. |
| ownership | Compile-time include protocol, no runtime owner. |
| failure | Missing/mismatched testing declarations are build errors, not a recovery branch. |
| cost | No production runtime overhead. |
| Design | [CMakeLists.txt](../../../../../CMakeLists.txt), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

```text
@source-span:L1-L28:sha256:6b0bd592b74ad0497e3805b5453979e65fee129a394b22d792cb5910de1373fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add compact indexed-copy admission and source-image attribution within existing runtime includes/private setup. |
| inputs / outputs | Combined include/private namespace span adds accounted_index_scalar_work.hpp, source_image_owner(capture,16) and explanatory lease comment. |
| invariants | Existing dependency/conditional testing setup is exact. Attribution labels capture allocations only; no process-global source state, original-query policy or new lease ceiling is created. |
| ownership | Static inline attribution contains no retained account; real account arrives from the producing runtime. |
| failure | Compile errors remain ordinary; no runtime handler added. |
| cost | Compile-time setup and fixed attribution descriptor. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp) |

## B0002

[Lines 29–42](../../../../../src/runtime/physical.cpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L42:sha256:809bb0707a2bd19993a29937d92b166186695f6652f23786893ea0b03485a85d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend one explicit source-image selected-work grant over traversal and deep-copy payload extents. |
| inputs / outputs | SourceImageBudget limit/used plus take/payload requests in; updated used out. |
| invariants | Refuse before used exceeds limit. Count every scalar field plus exact string/decimal digit extent before clone. Indexed pointer/scalar/traversal costs additionally spend original operation allowance, without refilling it. |
| ownership | Stack-local counters and borrowed RowView cells only during capture; no pointer escapes. |
| failure | Exhaustion throws source_image_work_limit directly; no retry or owner mutation. |
| cost | O(fields) payload admission plus exact width charges; counters are selected units, not elapsed time or all allocation CPU. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [docs/source_images.md](../../../../source_images.md) |

## B0003

[Lines 43–48](../../../../../src/runtime/physical.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L48:sha256:7cbad1d9cf08d750f84d47cc653e2c67996d5aa78f7ef3c4ca2f00a4e9198577
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pre-admit image directory/tuple capacity in indexed pointer-slot units. |
| inputs / outputs | Optional original IndexWorkAllowance pointer and descriptor count in; no returned storage. |
| invariants | Reference backend null pointer is a no-op. Round sizeof(T) to pointer words, check multiplication before admit. Never substitute a new allowance; memory allocation remains separately accounted. |
| ownership | Borrows original active allowance synchronously; no grant/context retained. |
| failure | Count overflow throws IndexFailure(overflow); insufficient native pointer slots propagates typed refusal before capacity allocation. |
| cost | O(1) checked capacity arithmetic plus one native allowance admission. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0004

[Lines 49–51](../../../../../src/runtime/physical.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,std::string_view code,std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present a typed public coordinator precondition/invariant failure. |
| inputs / outputs | True returns; false copies code/message into Error. |
| invariants | No semantic check beyond supplied predicate. |
| ownership | Borrows diagnostic text; failed Error owns copies. |
| failure | Public Error or failed diagnostic allocation propagates. |
| cost | Constant successful branch; error string construction is explicit failed-path cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 52–55](../../../../../src/runtime/physical.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_size(std::size_t& target,std::size_t amount) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate storage diagnostic counts without size_t wrap. |
| inputs / outputs | Check amount &lt;= max-target then add. |
| invariants | This is diagnostic aggregation, not native allocation admission. |
| ownership | Mutates borrowed count only. |
| failure | storage_overflow Error before addition; earlier different fields may already be summed. |
| cost | Constant arithmetic. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 56–60](../../../../../src/runtime/physical.cpp#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void add_statistics(storage::ArenaStatistics& target,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge six arena statistic components with checked sums. |
| inputs / outputs | Add slots/live/retained/pins/free/exhausted using add_size. |
| invariants | No atomic multi-field rollback; local result is abandoned on failure. |
| ownership | Borrows value and mutable target snapshots. |
| failure | Overflow/presentation failures propagate. |
| cost | Fixed six checked additions; does not scan arena slots. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 61–62](../../../../../src/runtime/physical.cpp#L61); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L62:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the translation-unit-private namespace containing physical helpers and the new source-image budget/capacity admission helpers. |
| inputs / outputs | The lexical namespace terminator precedes SourceImage constructor definition in crown::runtime. |
| invariants | SourceImage constructor follows outside this anonymous namespace; the next private namespace is separately opened after that constructor. This span itself performs no runtime work. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0008

[Lines 63–65](../../../../../src/runtime/physical.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L63-L65:sha256:404f33246e03593589c84d504eaa66d7de65d022624351734b0b4a383f5f25d1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize an empty owning source image using the producing runtime account and genuine program. |
| inputs / outputs | MemoryAccount, epoch and CompiledProgram in; sequence/program/capture-attributed directory owner constructed. |
| invariants | No rows are exported or cloned yet; public constructor is an editable DTO boundary and does not authenticate arbitrary caller account/program matches. Runtime calls pass its exact original account. |
| ownership | CompiledProgram shared native ownership and OwnerAllocator retain the supplied original account; no ordinary directory allocator. |
| failure | Normal handle/allocator construction failures propagate; no source state changes. |
| cost | Fixed handle/allocator construction; row/directory reserves occur in producer. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [docs/source_images.md](../../../../source_images.md) |

## B0009

[Lines 66–67](../../../../../src/runtime/physical.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L67:sha256:f4f8121dd2388b30f27a1454c1f3bd3ed0db6b42a9f01bb0e4cc53e5a048e339
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen the existing private helper namespace after the additive public SourceImage constructor. |
| inputs / outputs | Blank line and anonymous namespace opening at L66-L67. |
| invariants | This is the second context fragment of an old namespace span split by the new public constructor. Existing following private helpers retain their scope; no new public authority, state or behavior is introduced. |
| ownership | No live owner or allocation. |
| failure | No executable branch or recovery logic. |
| cost | No runtime work. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [build/verification/v71-fallback-root-v1/core-addition-proof.json](../../../../../build/verification/v71-fallback-root-v1/core-addition-proof.json) |

## B0010

[Lines 68–74](../../../../../src/runtime/physical.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t new_source_memory_owner() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mint a nonreused process-local physical allocation-attribution ID. |
| inputs / outputs | Relaxed atomic CAS increments last from zero; max uint64 is exhaustion. |
| invariants | ID identifies diagnostic owner domain, not proof, account grant or synchronization of runtime data. |
| ownership | Static scalar state; result owns no resource. |
| failure | Fixed MemoryFailure(overflow) when IDs exhausted. |
| cost | Atomic retry loop can contend/spuriously fail; no fixed retry/time bound or heap allocation. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp) |

## B0011

[Lines 75–75](../../../../../src/runtime/physical.cpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using MemoryVector=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the existing query account for physical temporary/retained arrays. |
| inputs / outputs | std::vector&lt;T,MemoryAllocator&lt;T&gt;&gt; alias. |
| invariants | Allocator is nonpropagating; every nested owned element must also receive correct account explicitly. |
| ownership | Vector owns capacity and elements; alias itself owns nothing. |
| failure | Allocation/member failures follow instantiated vector paths. |
| cost | No alias runtime cost; growth/relocation/teardown scale with actual elements/capacity. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 76–83](../../../../../src/runtime/physical.cpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CompactRowLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enable heterogeneous lexical lookup in per-occurrence std::map counts. |
| inputs / outputs | Compare AccountedRow, ordinary Row or RowView without creating an owning probe key. |
| invariants | Complete scalar/byte-string values determine order, not hash or pointer identity. This is distinct from custom AccountedRowMap. |
| ownership | Comparisons synchronously borrow operands. |
| failure | Ordinary scalar-borrow contract errors may propagate; no stored comparator state. |
| cost | Examined row/string prefixes per comparison; map operations require logarithmically many comparisons. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

```text
  bool operator()(const storage::AccountedRow& a,const storage::AccountedRow& b) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two accounted keys lexically. |
| inputs / outputs | a.view()&lt;b.view(). |
| invariants | Uses scalar variant/value order and examined raw string bytes; no owning row export. |
| ownership | Borrowed operands only. |
| failure | Underlying valid native comparisons allocate nothing; ordinary probe conversion may reject invalid scalar state. |
| cost | Variable examined row-field/string prefix cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

```text
  bool operator()(const storage::AccountedRow& a,const Row& b) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare accounted key and ordinary probe lexically. |
| inputs / outputs | a.view()&lt;b. |
| invariants | Uses scalar variant/value order and examined raw string bytes; no owning row export. |
| ownership | Borrowed operands only. |
| failure | Underlying valid native comparisons allocate nothing; ordinary probe conversion may reject invalid scalar state. |
| cost | Variable examined row-field/string prefix cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

```text
  bool operator()(const Row& a,const storage::AccountedRow& b) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare ordinary probe and accounted key lexically. |
| inputs / outputs | a&lt;b.view(). |
| invariants | Uses scalar variant/value order and examined raw string bytes; no owning row export. |
| ownership | Borrowed operands only. |
| failure | Underlying valid native comparisons allocate nothing; ordinary probe conversion may reject invalid scalar state. |
| cost | Variable examined row-field/string prefix cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

```text
  bool operator()(const storage::AccountedRow& a,storage::RowView b) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare accounted key and native probe lexically. |
| inputs / outputs | a.view()&lt;b. |
| invariants | Uses scalar variant/value order and examined raw string bytes; no owning row export. |
| ownership | Borrowed operands only. |
| failure | Underlying valid native comparisons allocate nothing; ordinary probe conversion may reject invalid scalar state. |
| cost | Variable examined row-field/string prefix cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

```text
  bool operator()(storage::RowView a,const storage::AccountedRow& b) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare native probe and accounted key lexically. |
| inputs / outputs | a&lt;b.view(). |
| invariants | Uses scalar variant/value order and examined raw string bytes; no owning row export. |
| ownership | Borrowed operands only. |
| failure | Underlying valid native comparisons allocate nothing; ordinary probe conversion may reject invalid scalar state. |
| cost | Variable examined row-field/string prefix cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/storage/accounted_row.cpp](../../../../../src/storage/accounted_row.cpp) |

## B0013

[Lines 84–84](../../../../../src/runtime/physical.cpp#L84); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Failure> [[noreturn]] void present(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate fixed native storage failures at the public coordinator boundary. |
| inputs / outputs | Copy native failure.code()/what() into Error and throw. |
| invariants | Called after private operation RAII/rollback has unwound where required; not a recovery algorithm. |
| ownership | Borrows fixed failure text for Error construction. |
| failure | Always throws public Error; diagnostic allocation can itself fail. |
| cost | Failed-path text allocation only; no successful row/route overhead. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0014

[Lines 85–92](../../../../../src/runtime/physical.cpp#L85); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalRuntime::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own physical source sets, per-occurrence projection multiplicities and logical support behind one facade. |
| inputs / outputs | Options/context/kernel, optional observation/workload state, source/layout/count vectors, sequence/build metadata and busy flags. |
| invariants | One logical epoch plus source/count inverses coordinates each update. Every catalog table has full-row source storage; aliases keep distinct derivation maps. No global query output delta is manufactured here. |
| ownership | Shared Impl survives pending facade moves/destruction; kernel/program/native state and new arrays use the original query account. |
| failure | Fallible construction stays private; public operations enforce busy/sequence/schema and rollback boundaries. |
| cost | Full source/support/count state plus native metadata/capacity. std::map count lookup is logarithmic with deep comparisons; its lifetime reclassification can scan account allocations. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
  using Counts=std::map<storage::AccountedRow,std::uint64_t,CompactRowLess,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store positive final-native derivation counts separately for each occurrence. |
| inputs / outputs | Ordered map of copied AccountedRow keys to uint64 multiplicity with query MemoryAllocator rebound node storage. |
| invariants | Counts represent physical-source projection multiplicity; zero crossings alone change logical Boolean support. This is std::map, not the custom exact-node AVL type. |
| ownership | Each occurrence map has its own physical_source attribution; keys and map nodes retain original account. |
| failure | Allocating insert can throw; extracted same-allocator nodes support no-allocation undo reinsertion. |
| cost | O(log distinct keys) variable-width comparisons; map-node allocation and set_lifetime_containing ledger scans remain explicit costs. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/resource/memory.cpp](../../../../../src/resource/memory.cpp) |

## B0015

[Lines 93–93](../../../../../src/runtime/physical.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  [[nodiscard]] storage::IndexWorkAllowance* work() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current compact native storage allowance for this operation. |
| inputs / outputs | Return compact_storage_work(storage_context), null for reference backend. |
| invariants | Indexed callers must bind the same active or retained lease; no fresh allowance is created here. |
| ownership | Pointer borrows lease-owned allowance. |
| failure | Missing indexed operation/lease throws storage contract Error. |
| cost | Constant context/lease checks; actual admission occurs in storage calls. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0016

[Lines 94–105](../../../../../src/runtime/physical.cpp#L94); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  SupportRuntime kernel;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain physical state fields beside the logical kernel and its instrumentation. |
| inputs / outputs | Kernel, observation owner/workload pointer, attribution, source/layout/count arrays, sequence/build context and update/constraint flags. |
| invariants | Workload pointer borrows the still-owned kernel collector. Source/count vectors do not resize during pending updates, preserving stored map pointers/iterators. |
| ownership | Native vectors own account-backed elements/capacity; layout descriptors share actual native metadata. |
| failure | Field destruction is ordinary RAII; no replacement grant or hidden ordinary source database is cached. |
| cost | State includes per-source storage and per-occurrence count maps; final release can destroy large native state. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 106–143](../../../../../src/runtime/physical.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  template<class Source> Impl(Source plan,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct empty source/count state using the same admitted program/account as support. |
| inputs / outputs | Create kernel, retain instrumentation/context, validate derivation limit/descriptor ID room, reserve vectors, create each occurrence count map and each source table/layout. |
| invariants | All catalog tables participate, including unused and constant-route tables; non-null column restriction remains explicit. Enforced-constraint flag is derived from immutable catalog statuses. |
| ownership | Source program is moved into kernel; all new vectors/map nodes/storage share context account, with distinct source attribution tags. |
| failure | Policy/schema/overflow/storage-work/memory/allocation failure destroys private partial Impl; no runtime is published. |
| cost | Visits source columns/constraints and occurrences, admits source metadata, allocates table/descriptor/container controls. No source rows or full database copy yet. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0018

[Lines 144–144](../../../../../src/runtime/physical.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void readable() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject committed-state reads while a private physical update is active. |
| inputs / outputs | Require !updating. |
| invariants | Kernel reader leases do not forbid ordinary committed reads; pending source/count state does. |
| ownership | Reads scalar flag only. |
| failure | runtime_busy Error on active update. |
| cost | Constant successful check. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 145–145](../../../../../src/runtime/physical.cpp#L145); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void writable() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require no pending physical update and no logical reader/view pin before mutation/build. |
| inputs / outputs | Call readable then require kernel.ready(). |
| invariants | Pinning logical epoch blocks updates; checking readiness does not allocate or change readers. |
| ownership | Borrows kernel metadata only. |
| failure | runtime_busy on pending token or outstanding reader/view group. |
| cost | Constant state/reader checks. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 146–148](../../../../../src/runtime/physical.cpp#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  storage::AccountedStorageTable& source(TableId table) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow source storage in the physical catalog domain. |
| inputs / outputs | Range-check table ID then index sources. |
| invariants | Does not itself call readable/writable; enclosing operation controls isolation. |
| ownership | Reference borrows Impl-owned table. |
| failure | invalid_physical_update on out-of-range ID. |
| cost | Constant check/index. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0021

[Lines 149–152](../../../../../src/runtime/physical.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const program::PhysicalInput& input(OccurrenceId occurrence) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the compiled input descriptor for one logical occurrence. |
| inputs / outputs | Range-check occurrence against compiled inputs then return descriptor. |
| invariants | Occurrence identity is separate from base table and node scope identity. |
| ownership | Borrow into retained compiled program. |
| failure | invalid_input_port on absent occurrence. |
| cost | Constant range/handle access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
@source-span:L149-L152:sha256:0a0b079c5f441a099b37e166c7e0be88f171ac032a8d54e50e990fa98509a5e5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the full existing occurrence-input guard at the repeated-brace insertion boundary. |
| inputs / outputs | OccurrenceId in; checked const program::PhysicalInput reference out. |
| invariants | The semantic function body is unchanged. Additive line proof happens to assign L152 closing brace to insertion because a repeated later brace can match old text; this card records the full combined boundary, not new input behavior. Out-of-range ID is never accepted. |
| ownership | Reference borrows existing compiled program. No source-image owner/grant is created here. |
| failure | invalid_input_port on out-of-range occurrence; inherited behavior retained. |
| cost | O(1) bounds check/reference access. Candidate may overlap an existing V70 input card; root must select one during relocation, preserving prior semantic authority. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [build/verification/v71-fallback-root-v1/core-addition-proof.json](../../../../../build/verification/v71-fallback-root-v1/core-addition-proof.json) |

## B0022

[Lines 153–189](../../../../../src/runtime/physical.cpp#L153); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L189:sha256:3ae33bf17015586aaf4a211c71fb171feb44c2d7c88602970a36e406b87a79e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-capture all native physical source rows from committed or journal-private after-state without ordinary exports. |
| inputs / outputs | Limits, requested epoch and optional changed-table source journal in; owning SourceImage with actual selected work out. |
| invariants | Count every source including unused; pre-admit total rows, directory and row capacities before clone. Per-table order follows backend. Changed table reads its exact active journal; other tables use live traversal. Scan/admit scalar payload then indexed tuple copy before original-layout deep clone. No source mutation, answer evaluation, sorting, checkpoint authority or shared-query storage is introduced. |
| ownership | Directory, row vectors and tuple payload/layout/program retain storage_context original account. Source cursors/views remain local; no borrowed table/journal view escapes. Serial caller supplies valid owner/token access and retained active native lease. |
| failure | source_image_row_limit/work_limit, indexed-domain, tuple/memory allocation errors unwind partial image; sources/journal remain unchanged and pending token can continue. No catch resets/refills indexed grant. |
| cost | O(tables + physical rows + scalar fields/payload extents) selected scans/clones, real backend traversal and all directory/row/payload allocation/cleanup costs. Peak original sources plus complete image coexist; no constant-delay or CPU ceiling proof from counters. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [src/storage/accounted_index_scalar_work.hpp](../../../../../src/storage/accounted_index_scalar_work.hpp), [docs/source_images.md](../../../../source_images.md) |

## B0023

[Lines 190–191](../../../../../src/runtime/physical.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L191:sha256:5156731b25bdf97f00c0972d38483c9887d44e6b97bc32b88bc2a0a1d3d48cb6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`detail::NativeDatabase native_database() const\`: Snapshots deep-copy funded tuples, then sort full values to preserve historical ordered input replay across both storage backends. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/physical.cpp:L127; use that declaration for the actual input/output shape. |
| invariants | The source note states: Snapshots deep-copy funded tuples, then sort full values to preserve historical ordered input replay across both storage backends. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment itself retains nothing. It documents this neighboring ownership/account boundary: Snapshots deep-copy funded tuples, then sort full values to preserve historical ordered input replay across both storage backends. Actual lifetime is determined by the declared members and owners. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Snapshots deep-copy funded tuples, then sort full values to preserve historical ordered input replay across both storage backends. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0024

[Lines 192–202](../../../../../src/runtime/physical.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  detail::NativeDatabase native_database() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clone and sort the complete physical source snapshot for native operational consumers. |
| inputs / outputs | Each source.snapshot deep-copies AccountedTuples; sort tuples lexically and append their native vector to NativeDatabase. |
| invariants | Preserves the earlier ordered full-row Database traversal order for either backend/rebuild method. No ordinary Row/set graph is exported. |
| ownership | Full temporary row blocks/vectors/layout handles funded under existing account; source state remains unchanged. |
| failure | Storage allowance, tuple clone/comparison or allocation failure propagates; local partial snapshot dies. |
| cost | All rows/deep bytes copied, plus O(sum R_t log R_t) variable-width sorting and peak coexistence with live state; no size-independent snapshot claim. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0025

[Lines 203–208](../../../../../src/runtime/physical.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Database database() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly export all physical source rows as ordinary owning database sets. |
| inputs / outputs | Native source snapshots are exported row by row into ordered Relation sets. |
| invariants | Diagnostic/export boundary; source identity remains complete row, including unused fields/tables. |
| ownership | Result owns ordinary row/string/set nodes; transient source.snapshot deep copies remain query-account funded. |
| failure | Storage/row export/allocation/comparison failures propagate without source mutation. |
| cost | Native deep snapshots plus ordinary deep row copies and O(sum R_t log R_t) ordered insertion comparisons; explicit extra storage. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 209–218](../../../../../src/runtime/physical.cpp#L209); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  PhysicalSnapshot snapshot(SupportSnapshot support) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine support snapshot, complete ordinary source database and derivation explanations. |
| inputs / outputs | Use support sequence, export database, then build per-occurrence tuple/count vectors with native descriptor tuples. |
| invariants | Caller supplies the correct committed or owner-only pending support view; snapshot is diagnostic, not an independent invariant proof. |
| ownership | Owns ordinary database/support vectors and funded immutable derivation tuple payloads; native descriptor handles retain metadata. |
| failure | Snapshot/export/tuple/allocation failures propagate; no source/count mutation. |
| cost | Full source/support/count traversal. Derivation export can materialize an ordinary Row then reimport through native descriptor callback, adding explicit copies. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 219–226](../../../../../src/runtime/physical.cpp#L219); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_nothrow_move_constructible_v<PhysicalPreview>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce nonthrowing ownership movement at the physical publication barrier. |
| inputs / outputs | Compile-time checks cover move construction/assignment of PhysicalPreview and PhysicalEpoch. |
| invariants | Changing nested output fields must preserve these traits before barrier logic remains valid. |
| ownership | No runtime owner or output created by assertion. |
| failure | Compilation fails if required move guarantees change. |
| cost | No runtime check or overhead. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

```text
struct PhysicalRuntime::PendingUpdate::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one private multi-alias physical transaction and its retained storage grant. |
| inputs / outputs | Shared runtime owner, storage lease, output preview, source/logical journals, reserved count inverses, route cursor and instrumentation tickets. |
| invariants | No private prefix is committed until all routes/output preparation finish. ~Data rolls back when owner remains; close resets owner to make later cleanup inert. |
| ownership | Pending owner retains source pin/imported tuples, exact std::map node inverses, kernel token and original account/lease across caller pauses/facade moves. |
| failure | Preparation unwind and explicit active-route catch restore state; formatted presentation occurs outside restoration. |
| cost | Touched journals/output/inverses plus retained erased rows; rollback may scan account ledger for erased std::map nodes. No full-query mirror. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0028

[Lines 227–227](../../../../../src/runtime/physical.cpp#L227); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  enum class CountKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the exact inverse for a per-occurrence count edit. |
| inputs / outputs | inserted, changed or erased. |
| invariants | Undo kind describes only count state, independent of source journal/kernel support changes. |
| ownership | Inline tag in already reserved undo vector. |
| failure | No validation/allocation in enum. |
| cost | Constant storage. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0029

[Lines 228–234](../../../../../src/runtime/physical.cpp#L228); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CountUndo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the exact inverse of one per-occurrence derivation-count edit. |
| inputs / outputs | Tag, count-map pointer, stable iterator/old value or extracted map node select one inverse. |
| invariants | Prepare reserves at least one slot per routed occurrence; CountUndo moves cannot throw. Erasures retain the exact node and its accounted row key. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. |
| failure | Rollback reuses retained nodes and values; invariant violations terminate rather than allocate a recovery path. |
| cost | Fixed inverse metadata per alias; erased payload remains retained. Map rebalance/ledger classification are real costs. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0030

[Lines 235–250](../../../../../src/runtime/physical.cpp#L235); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<Impl> owner;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain mutable pending state and instrumentation completeness metadata. |
| inputs / outputs | Owner/lease, output, journals, undo, route position/completion, tickets and charged-support subset plus completeness flag. |
| invariants | Undo/output capacity reserved before alias mutation; observation subset tracks accepted nested charge rather than inferred counter magnitude. |
| ownership | All operational storage funded by original account; output OwnerAllocator preserves original account on moves. |
| failure | Members unwind via Data rollback/destructors; active-route failures make accounting completeness sticky until close. |
| cost | Fixed state plus touched row/output/journal payload; vector capacity persists until pending Data destruction. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

```text
  static_assert(std::is_nothrow_move_constructible_v<CountUndo>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ensure reserved inverse publication cannot throw while moving CountUndo. |
| inputs / outputs | Compile-time assertion on CountUndo move construction. |
| invariants | Undo vector capacity is reserved before alias count mutation; fixed inverse/node moves complete without allocating a second journal. |
| ownership | No object ownership created by assertion. |
| failure | Build failure if inverse fields lose required move guarantee. |
| cost | No runtime check. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0031

[Lines 251–258](../../../../../src/runtime/physical.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<Impl> value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare the physical pending owner and optional observation/workload tickets. |
| inputs / outputs | Shared Impl and borrowed update identity produce retained grant, empty source/logical tokens, output metadata and inverse vector. |
| invariants | Caller sets updating only after complete Data construction; source-row values are imported and pinned before a public token escapes. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. |
| failure | Constructor failure leaves the runtime unpublished; already constructed tickets/members release through RAII. |
| cost | Fixed owner/ticket setup and empty vectors; no source or query-state mirror. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0032

[Lines 259–259](../../../../../src/runtime/physical.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Data() { rollback(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Automatically restore an uncommitted physical token during owner destruction/unwind. |
| inputs / outputs | Call idempotent rollback; closed/committed owner is inert. |
| invariants | No extra local preparation catch is required when the sole unique Data owner unwinds. |
| ownership | Releases retained journals/pins/output/accounted members after restoration. |
| failure | Implicit noexcept; valid funded restoration cannot allocate. |
| cost | Actual inverse/native journal cleanup and possible ledger scans/final-owner teardown, not constant destructor cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0033

[Lines 260–262](../../../../../src/runtime/physical.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl& active() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate that pending Data still owns an active logical epoch. |
| inputs / outputs | Require owner and logical present and logical.active(), then borrow Impl. |
| invariants | Commit/rollback reset closes validity; no reopened token state. |
| ownership | Returns borrow held by Data shared owner. |
| failure | invalid_epoch Error on closed state. |
| cost | Constant owner/flag checks. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0034

[Lines 263–287](../../../../../src/runtime/physical.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void observe() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish fixed physical counters and honest inclusive/exclusive work availability into the current observation attempt. |
| inputs / outputs | If owner/observer present set work and category metrics; subtract only known accepted nested support charge subset, otherwise mark work unavailable. |
| invariants | Does not infer successful nested work from total magnitudes. Instrumentation is descriptive, not transactional source authority. |
| ownership | Borrow optional observer; no retained row/owner allocation. |
| failure | Noexcept observer metric updates; missing observation is inert. |
| cost | Fixed metric registry calls; no row scan or clock sampling in this method. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp) |

## B0035

[Lines 288–294](../../../../../src/runtime/physical.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit one cumulative physical update work budget. |
| inputs / outputs | Nonnegative amount increments physical work only after uint64 and configured-limit admission. |
| invariants | All alias routes and charged nested support work share this total across resumed calls. |
| ownership | Inline pending metric state; no fresh native grant. |
| failure | resource_limit rejection leaves the addition unperformed; the enclosing route/owner unwinding restores private state. |
| cost | Fixed arithmetic/comparisons; this is an abstract work budget, not CPU-time accounting. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0036

[Lines 295–299](../../../../../src/runtime/physical.cpp#L295); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metric(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count a physical work category once after shared budget admission. |
| inputs / outputs | Reference to a managed category counter and amount increment work and that category. |
| invariants | Every managed category starts at zero and only increments through this helper; its value is bounded by cumulative work. A second category overflow check is unnecessary. |
| ownership | Inline scalars only; observation phase summaries are not passed here. |
| failure | charge rejects before either addition; no additional exception boundary. |
| cost | One cumulative admission followed by scalar additions; no allocation or second overflow guard. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0037

[Lines 300–321](../../../../../src/runtime/physical.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore one uncommitted physical update, including alias counts and support. |
| inputs / outputs | An active Data rolls back logical support, reverses count inverses, releases source journal/pins/output, finishes tickets and clears updating. |
| invariants | Idempotent after owner reset. Logical and count/source authority are private until commit; extracted nodes retain original keys and attribution. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. |
| failure | Noexcept using funded native journals/inverse state; no diagnostic result construction on this path. |
| cost | O(actual inverses and native journal cleanup); lifetime classification may scan outstanding account allocations. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0038

[Lines 322–335](../../../../../src/runtime/physical.cpp#L322); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void validate_constraints()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the complete proposed source database when enforced constraints exist. |
| inputs / outputs | An already journaled source mutation yields native snapshots of every source table and runs the catalog validator. |
| invariants | No enforced constraints means an immediate return. Otherwise unused tables, self/cyclic FKs and full after-state participate; input row validation already ran. |
| ownership | Native compact snapshots/projected keys/ordered nodes use the same original finite account. |
| failure | Constraint/allocation failure propagates before publication; owner/route rollback restores source and kernel. |
| cost | O(all proposed source rows/deep bytes plus constraint validation), not merely changed-row cost; scratch is temporary. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0039

[Lines 336–339](../../../../../src/runtime/physical.cpp#L336); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L336-L339:sha256:874b03bfbe59251d42a7817914bb7fc0ecaade311b9d4dbccbcea1da6bb5960f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`void route(OccurrenceId occurrence,std::uint64_t prefix,storage::RowView row,const RouteObserver& observer,EpochViewOptions view_options)\`: One alias prefix of one physical set input. Full source rows determine source identity; each accepted projection changes its own derivation count. Only 0&lt;-&gt;1 changes reach logical support. Prefixes share this pending owner, so self-join new-new terms see prior aliases without publishing an epoch. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/physical.cpp:L275; use that declaration for the actual input/output shape. |
| invariants | The source note states: One alias prefix of one physical set input. Full source rows determine source identity; each accepted projection changes its own derivation count. Only 0&lt;-&gt;1 changes reach logical support. Prefixes share this pending owner, so self-join new-new terms see prior aliases without publishing an epoch. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The comment creates or retains no runtime owner. Its prose documents sharing the pending owner across alias prefixes before publishing the atomic epoch; that lifetime rule must be checked in the adjacent implementation, not inferred from the comment alone. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0040

[Lines 340–396](../../../../../src/runtime/physical.cpp#L340); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void route(OccurrenceId occurrence,std::uint64_t prefix,storage::RowView row,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one occurrence adapter/count change within a physical input transaction. |
| inputs / outputs | Occurrence ID, alias prefix, borrowed complete source row, observer and view options in; derivation preview and optional logical membership stage out. |
| invariants | Counts are per occurrence, not per base table or repeated scope. Only 0↔1 changes stage Boolean support. Alias prefixes remain private and ordered for self-join cross terms. |
| ownership | Input is borrowed during adaptation; the pending owner retains imported tuples, output values, extracted map nodes and logical/source journals. |
| failure | Validate count precondition/limit before changing it. Undo capacity is owned by the pending update; any later route/observer failure restores all aliases and source state. |
| cost | Adapter visits fields, ordered count lookup costs O(log distinct projected rows) comparisons, output capture copies a tuple; erase/revive uses set_lifetime_containing and can scan outstanding allocations. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/support_invariants.md](../../../../support_invariants.md) |

```text
void route(OccurrenceId occurrence,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route one physical source event through one compiled logical occurrence. |
| inputs / outputs | Occurrence, alias prefix, pinned full source row and optional observer update its projection derivation count and stage only zero crossings. |
| invariants | Complete physical source identity differs from logical projection identity. Aliases run sequentially behind one barrier; reserved inverse/output capacity covers one entry per route. Positive-to-positive counts do not restage support. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. Public derivation records own funded tuple payloads; observer views borrow their documented prefix group. |
| failure | Any route/adapter/output/observer failure must abort the retained physical token; stage_next supplies that boundary. |
| cost | Actual adapter/projection/deep fields, ordered count lookup, local output tuple/pin, inverse and affected support work. Observer before/after views are explicit extra work. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0041

[Lines 397–420](../../../../../src/runtime/physical.cpp#L397); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void prepare(const storage::AccountedTuple& tuple,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare physical source membership and reserve all alias inverse/output slots. |
| inputs / outputs | Validated tuple and optional existing handle open logical/source journals, enforce proposed constraints and prepare route capacity. |
| invariants | Sole caller begin_staged owns this fully constructed Data in AccountedUnique until success. Its destructor rolls back on unwind before the public translation catch; a local rollback/rethrow catch would duplicate that action. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. |
| failure | Preparation failure unwinds the unique owner and runs Data::~Data rollback; no partial token escapes. |
| cost | Actual source journal/membership/pin, optional complete-database constraint check and O(route count) capacity reserve; no alias work yet. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0042

[Lines 421–422](../../../../../src/runtime/physical.cpp#L421); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L421-L422:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct PhysicalRuntime::PendingUpdate::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct PhysicalRuntime::PendingUpdate::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct PhysicalRuntime::PendingUpdate::Data\` at its lexical source position in src/runtime/physical.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct PhysicalRuntime::PendingUpdate::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0043

[Lines 423–423](../../../../../src/runtime/physical.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate::PendingUpdate(resource::AccountedUnique<Data> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a completely prepared private physical token. |
| inputs / outputs | Move AccountedUnique&lt;Data&gt; into facade. |
| invariants | Only begin_staged creates valid prepared Data; constructor does not replay admission. |
| ownership | Unique owner/retained grant transfer. |
| failure | Noexcept; no allocation. |
| cost | Constant owner move. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0044

[Lines 424–424](../../../../../src/runtime/physical.cpp#L424); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate::PendingUpdate(PendingUpdate&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move pending ownership without moving its native source/count/journal payload. |
| inputs / outputs | Default unique owner move empties source facade. |
| invariants | Borrowed caller update is no longer needed; Data retains imported source pin and owner. |
| ownership | Exclusive Data transfer. |
| failure | Noexcept. |
| cost | Constant move construction. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0045

[Lines 425–428](../../../../../src/runtime/physical.cpp#L425); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate& PhysicalRuntime::PendingUpdate::operator=(PendingUpdate&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a pending token while restoring any old destination transaction first. |
| inputs / outputs | Self-check then unique owner move assignment. |
| invariants | Old destination Data destructor rolls back if still active; source facade becomes empty. |
| ownership | Transfers exclusive token/lease; old payload may release final owners. |
| failure | Noexcept with funded destructor/rollback preconditions. |
| cost | Fixed handle transfer plus potentially large old rollback/inverse/ledger cleanup. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0046

[Lines 429–429](../../../../../src/runtime/physical.cpp#L429); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate::~PendingUpdate()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close pending ownership and automatically rollback an unfinished update. |
| inputs / outputs | Default AccountedUnique destruction invokes Data::~Data. |
| invariants | Committed/rolled-back Data rollback is inert; no implicit commit. |
| ownership | Releases Data/lease/owner and retained capacities. |
| failure | Noexcept native ownership destruction. |
| cost | Size-dependent rollback and payload release; no new scratch allocation. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0047

[Lines 430–430](../../../../../src/runtime/physical.cpp#L430); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool PhysicalRuntime::PendingUpdate::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether this facade retains an unclosed logical/physical token. |
| inputs / outputs | Require nonnull Data/owner/logical and logical.active(). |
| invariants | False for moved-from/closed token; does not claim routes complete. |
| ownership | Reads owned pointer/flags only. |
| failure | Noexcept; no diagnostic allocation. |
| cost | Constant checks. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0048

[Lines 431–442](../../../../../src/runtime/physical.cpp#L431); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool PhysicalRuntime::PendingUpdate::stage_next(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one remaining alias prefix through a retained public token. |
| inputs / outputs | Open PendingUpdate and optional observer/options return true after one route, or false once routes are complete. |
| invariants | The token survives this method, so active-route failure needs an explicit rollback catch. Native fixed failures are presented as public Error only after rollback. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. |
| failure | Invalid/closed token rejects access; any active route failure closes and restores the complete physical update. |
| cost | One route plus actual observer/support work under original grant; no per-call budget refill or source-row export. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0049

[Lines 443–443](../../../../../src/runtime/physical.cpp#L443); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void PhysicalRuntime::PendingUpdate::rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly abort the full pending physical update if owned. |
| inputs / outputs | Delegate Data rollback when data_ exists; moved-from no-op. |
| invariants | Restores every staged alias/source/support edit; idempotent after owner reset. |
| ownership | Keeps facade shell but releases private row/journal/output ownership. |
| failure | Noexcept; no new recovery allocation. |
| cost | All inverse/native journal cleanup and possible std::map allocation-ledger classification. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0050

[Lines 444–446](../../../../../src/runtime/physical.cpp#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const PhysicalPreview& PhysicalRuntime::PendingUpdate::preview() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the owner-only tentative physical preview. |
| inputs / outputs | Check facade/Data active, return output. |
| invariants | Not externally published epoch; borrow expires on commit/rollback/replacement. |
| ownership | Data owns tuples/pins/vector; returned reference owns nothing. |
| failure | invalid_epoch on moved/closed token. |
| cost | Constant checks/reference. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0051

[Lines 447–449](../../../../../src/runtime/physical.cpp#L447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SupportEpoch& PhysicalRuntime::PendingUpdate::support() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow tentative local logical changes for this physical input. |
| inputs / outputs | Check active token, return logical preview. |
| invariants | Local support journal changes are not full-query output deltas or committed state. |
| ownership | Borrow expires when pending logical owner closes/changes. |
| failure | invalid_epoch or logical preview contract errors propagate. |
| cost | Constant checks/reference. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0052

[Lines 450–454](../../../../../src/runtime/physical.cpp#L450); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSnapshot PhysicalRuntime::PendingUpdate::snapshot() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a complete owner-only tentative diagnostic snapshot. |
| inputs / outputs | Rebind retained storage lease, obtain logical snapshot then combine source/count snapshot. |
| invariants | May capture a partially drained alias prefix: source membership is already staged while other alias counts/support can still be old. It is an owner-only diagnostic, not a committed full-query after-state. Snapshot failure leaves token active for caller decision. |
| ownership | Returned diagnostic owns ordinary data and funded tuple payload; retained lease is reused without refill. |
| failure | Native fixed failures present as Error; allocation/snapshot failures propagate without an explicit abort catch here. |
| cost | Complete source/support/count export and deep allocation costs, not constant preview access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0053

[Lines 455–460](../../../../../src/runtime/physical.cpp#L455); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L455-L460:sha256:a85f2522195fa5d8b9557139dbcdb98165a47e6b87a2ab6a9555aaaec665d010
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose pending source after-state capture only after alias routes are fully drained. |
| inputs / outputs | Live PendingUpdate plus SourceImageLimits in; private after-image at pending output sequence out. |
| invariants | Require valid active token and routes_complete. Bind retained storage_lease through StorageOperation, never mint a fresh indexed allowance. Pass only the exact changed-table journal and table ID; source image itself remains unpublished data. |
| ownership | Token retains journal/owner/lease; returned image independently owns copied original-account data. StorageOperation restores suspended lease binding on exit; access remains serial. |
| failure | Moved/closed token gives invalid_epoch, undrained routes runtime_busy. Capture failure propagates without invoking rollback or closing token; its existing destructor/explicit rollback still owns abandonment. |
| cost | Constant validity/lease binding plus complete source capture and remaining original indexed grant. Repeated calls freshen only explicit selected image work, never native allowance. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [docs/source_images.md](../../../../source_images.md) |

## B0054

[Lines 461–464](../../../../../src/runtime/physical.cpp#L461); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::EpochView PhysicalRuntime::PendingUpdate::view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owner-only before/after logical epoch view of the current private prefix. |
| inputs / outputs | Check active facade, delegate logical.view(side,options). |
| invariants | View/group leases seal pending prefix; caller must retire them before further staging/commit according to support protocol. |
| ownership | Returned owning view retains logical group/native rows; facade itself keeps full physical Data. |
| failure | Invalid token/options/resource/view construction failures propagate; this accessor does not auto-abort. |
| cost | Delegated view preparation/retained journal/index work and allocation; no complete database snapshot by this wrapper. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0055

[Lines 465–481](../../../../../src/runtime/physical.cpp#L465); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalEpoch PhysicalRuntime::PendingUpdate::commit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish fully prepared source/count/logical state as one physical epoch. |
| inputs / outputs | Open token with all routes drained produces owning PhysicalEpoch and advances the committed sequence. |
| invariants | Logical/source commits, inverse cleanup, output moves and ticket completion allocate nothing after the barrier begins. Partial route preparation is rejected before publication. |
| ownership | Moves owning output/journal handles into the result and clears pending ownership. |
| failure | Closed/not-drained tokens reject before commit; publication relies on funded nonthrowing native operations. |
| cost | O(touched journals/inverse destruction/output owner moves); no global validation or output enumeration at commit. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0057

[Lines 483–484](../../../../../src/runtime/physical.cpp#L483); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PhysicalRuntime(PhysicalPlan plan,PhysicalRuntimeOptions options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an empty physical owner from a public compiler artifact. |
| inputs / outputs | Create matching storage context/account with configured memory limit, then delegate PlanSource constructor. |
| invariants | Source artifact is input only; owned native program/state is admitted before publication. Empty source state differs from initialize(database). |
| ownership | New query account funds native metadata/state; caller plan handle is not retained as an unaccounted graph. |
| failure | Context/compiler/storage/option/allocation errors propagate from construction; no runtime escapes. |
| cost | Complete native plan admission plus empty support/source/count structures, not constant handle wrapping. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0058

[Lines 485–493](../../../../../src/runtime/physical.cpp#L485); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PhysicalRuntime(CompiledProgram source,PhysicalRuntimeOptions options)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a compiler/cache program into a fresh receiving runtime account and empty physical owner. |
| inputs / outputs | Create new_storage_context, open one storage operation, deep freeze native source into receiving account, validate context, construct Impl. |
| invariants | Public new query does not adopt source account as a fresh runtime allowance; internal rebuilds use separate existing-account path. |
| ownership | New metadata/state under receiving account; supplied immutable native source remains external input only. |
| failure | Native Index/Table failures are formatted after constructor unwind; memory/compiler errors propagate. |
| cost | Full native metadata/binding clone plus empty state construction and optional observation initialization. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0059

[Lines 494–497](../../../../../src/runtime/physical.cpp#L494); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PhysicalRuntime(PlanSource plan,PhysicalRuntimeOptions options,std::shared_ptr<detail::StorageWorkContext> context)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose a private physical owner using an explicitly existing account/backend work context. |
| inputs / outputs | Visit PhysicalPlan/CompiledProgram, validate context/account/backend/limit, bind storage operation and construct accounted Impl. |
| invariants | Nested operations reuse the active grant; native source account must equal context account. |
| ownership | Retains context and admitted source through kernel/Impl; new state is funded there. |
| failure | Native fixed failures format only after private construction unwinds; context/member/allocation errors propagate. |
| cost | Variant dispatch plus complete relevant source/kernel/physical admission; no per-helper budget refill. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0060

[Lines 498–501](../../../../../src/runtime/physical.cpp#L498); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::initialize(PhysicalPlan plan,const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a ready physical owner from a complete caller database and compiler plan. |
| inputs / outputs | Delegate initialize_at at sequence0 with no public input epoch. |
| invariants | Complete final-state constraint validation precedes both direct/insertion-replay build paths, permitting valid cyclic FKs. |
| ownership | Caller Database borrowed for build; result owns funded native state. |
| failure | Build/schema/constraint/storage/resource/allocation failures return no partial owner. |
| cost | Whole database validation/import/adaptation/count/support build; cumulative BuildOptions limit separate from per-update limits. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0061

[Lines 502–507](../../../../../src/runtime/physical.cpp#L502); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::initialize(CompiledProgram source,const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build from complete caller database after admitting supplied native source into a fresh query account. |
| inputs / outputs | New context/operation, CompiledProgram::freeze then initialize_at at sequence0. |
| invariants | Uses complete final snapshot, no public insertion-prefix constraint artifacts or fabricated external updates. |
| ownership | New native source/state account; caller source/database remain unchanged. |
| failure | Native failures format after unwind; all build/admission/allocation errors propagate before publication. |
| cost | Full source freeze plus complete database build; does not merely share compiler/cache metadata. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0062

[Lines 508–512](../../../../../src/runtime/physical.cpp#L508); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::initialize_at(PlanSource plan,const Database& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward a complete database build with explicit committed sequence, carried metrics and optional existing context. |
| inputs / outputs | Call generic initialize_data on ordinary Database. |
| invariants | Private rebuild/restore composition preserves sequence and aggregate build credits. |
| ownership | Moves source/context; borrows database only during build. |
| failure | Delegated build failures propagate; no local recovery layer. |
| cost | Fixed delegation plus complete initialize_data work. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0063

[Lines 513–582](../../../../../src/runtime/physical.cpp#L513); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::initialize_data(PlanSource plan,const DatabaseView& database,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build complete native physical/support state privately from ordinary or native database views. |
| inputs / outputs | Validate method/table count/all rows/enforced constraints; insert full source rows, adapt each route, accumulate positive native counts and first-key seeds, initialize kernel then publish metrics/sequence/context. |
| invariants | Both build methods start from validated full final snapshot. Unique source membership and derivation limits are exact; each occurrence key seeds logical support only once. No externally visible prefix or epoch is committed. |
| ownership | Temporary native seeds and all target state use context account. Source views are borrowed; target rows/count keys are copied into funded ownership. |
| failure | Any work/memory/schema/constraint/duplicate/count/storage/support failure destroys private target; original owner/database untouched. Native Index/Table failures are presented after unwind. |
| cost | All row/deep payload import plus per-route adaptation/map lookup; whole-database constraints and support initialization can be large. Seed vector doubles with explicit pointer-slot credits; comparison/capacity costs are additional. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

```text
  const auto append_seed=[&](NodeId node,storage::AccountedTuple tuple) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Grow initialization seed storage geometrically before appending a first native key. |
| inputs / outputs | On full vector double capacity or start8 with size/pointer-word overflow checks and native allowance precharge, reserve, then move tuple. |
| invariants | Only newly distinct occurrence keys reach this helper; build failure abandons target rather than retrying a partly published owner. |
| ownership | Moves AccountedTuple ownership into account-backed scratch; closure borrows build locals synchronously. |
| failure | Overflow/work/storage/allocation/length errors propagate before target publication. |
| cost | Amortized linear handle relocation across seeds, individual reserve can move full prefix; pointer-slot credit uses requested capacity, not exact allocator bytes/CPU. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0064

[Lines 583–586](../../../../../src/runtime/physical.cpp#L583); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::rebuilt(BuildOptions build) const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a separate rebuilt owner from a quiescent committed snapshot. |
| inputs / outputs | Require writable source, create compatible existing-account context and delegate private rebuild. |
| invariants | Original owner remains unchanged and committed sequence/options preserved; old/new state coexist under original query cap. |
| ownership | Target and operational source snapshots share original account, not a fresh grant. |
| failure | Busy/context/build/resource/allocation failures leave original usable. |
| cost | Whole source snapshot/sort/import and support reconstruction; peak overlap is real funded memory. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0065

[Lines 587–614](../../../../../src/runtime/physical.cpp#L587); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
recovery::EncodedImage PhysicalRuntime::checkpoint_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode complete committed physical source rows and epoch into a bound recovery image. |
| inputs / outputs | Require quiescence, precheck table/row/field/zero-work bounds, build sorted native snapshot and RowView table arrays, call encode_image with supplied binding/limits. |
| invariants | Image stores source/epoch, not trusted live derived state. Supplied expected binding is a private recovery protocol input; codec validates its image envelope. |
| ownership | Snapshot, view arrays and encoded output consume existing account; RowViews borrow snapshot until encoding returns. |
| failure | Image/storage/memory errors propagate without mutating runtime. Codec work/byte limits do not cap all earlier snapshot/sort work. |
| cost | Deep copies/sorts all sources and builds full view inventory before encoding; live state/snapshot/encoded output can overlap. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp) |

## B0066

[Lines 615–658](../../../../../src/runtime/physical.cpp#L615); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::restore_image(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode a bound source image, optionally match managed window set membership, and rebuild native state at restored epoch. |
| inputs / outputs | Decode under receiving account/limits; validate managed table IDs, unique window row keys and set equality for managed sources; freeze supplied native source then initialize_data at manifest epoch. |
| invariants | Window matching counts distinct keys, not event multiplicities/time order. Private caller supplies admitted source/context/binding and separately validated window checkpoint; derived support/count state is recomputed. |
| ownership | Decoded rows, matching sets/flags/counts and fresh target all funded under context account; borrowed window RowViews remain local. |
| failure | Corrupt/binding/limit/matching-work or native build/allocation errors return no target; formatted native storage failures occur after unwind. |
| cost | Full decode and optional ordered-key set scans with deep variable-width comparisons, plus source clone/full rebuild. Matching charges fields/counts, not all compared string bytes. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [include/crown/recovery/image.hpp](../../../../../include/crown/recovery/image.hpp), [include/crown/runtime/window.hpp](../../../../../include/crown/runtime/window.hpp) |

```text
    struct Key {TableId table;storage::RowView values;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a table-qualified window/source row during restore matching. |
| inputs / outputs | TableId plus nonowning native values; comparator charges table and field counts then compares exact rows. |
| invariants | Only managed table keys enter expected set; uniqueness ignores positive window multiplicity because physical source identity is set membership. |
| ownership | Local set nodes funded under recovery scratch; row bytes owned by decoded database/window checkpoint, never by Key. |
| failure | Matching work exhaustion/corruption/allocator failures propagate; no key/view escapes restore. |
| cost | O(log keys) field/string comparisons per insert/probe; nominal field debits do not make variable scalar bytes constant. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0067

[Lines 659–661](../../../../../src/runtime/physical.cpp#L659); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::rebuilt(BuildOptions build,std::shared_ptr<detail::StorageWorkContext> context) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild under the supplied original-account context using the current compiled program. |
| inputs / outputs | Delegate rebuilt_with_program(kernel.plan(),build,context). |
| invariants | Source/account/schema policy unchanged; private callee checks quiescence and receiving context. |
| ownership | Retains native source handle; no ordinary export. |
| failure | Native fixed errors format after delegated unwind; other failures propagate. |
| cost | Fixed handle/call work plus complete rebuilt_with_program cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0068

[Lines 662–670](../../../../../src/runtime/physical.cpp#L662); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::rebuilt_for(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild against one checked minimum-height alternative without an ordinary compiler/source mirror. |
| inputs / outputs | Require quiescence, native replan original program/candidate, then rebuild target with supplied context. |
| invariants | Replan independently compares exact candidate/core binding and aliases admitted SQL/CQ source; this wrapper does not rerun SQL/P02/identity producer passes. |
| ownership | Fresh graph and rebuild state use original account; original runtime/source retained and unchanged. |
| failure | Replan/busy/context/build/resource errors propagate with no replacement publication. |
| cost | Full native exact-binding/new graph construction plus sorted source snapshot and target rebuild; immutable source work credits remain separate from actual recomputation. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc) |

## B0069

[Lines 671–695](../../../../../src/runtime/physical.cpp#L671); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime PhysicalRuntime::rebuilt_with_program(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct replacement state under the same account while retaining the original committed owner. |
| inputs / outputs | Validate target/context/account equality and build method, precharge snapshot dimensions, native snapshot/sort, initialize target at same sequence, set rebuilt context. |
| invariants | No account-limit reset or ordinary source Row graph. Equivalence/current publication is an outer reoptimization responsibility; this method only builds a candidate owner. |
| ownership | Original and target plus native snapshot coexist under original cap; target retains its program/context. |
| failure | Any admission/snapshot/import/support/observation failure destroys target; original remains untouched. |
| cost | All source deep copy/sort, constraint/adaptation/count/support rebuilding and overlap memory; abstract precharges do not bound comparison/allocator CPU. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0070

[Lines 696–697](../../../../../src/runtime/physical.cpp#L696); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::~PhysicalRuntime()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release facade ownership of physical source/count/kernel state. |
| inputs / outputs | Default shared Impl owner destruction. |
| invariants | Pending tokens can keep Impl alive; logical cursors/outputs can retain their separate kernel/row/account owners. |
| ownership | Final Impl release destroys large source/count/native state; borrowed metadata needs a surviving owner. |
| failure | Noexcept member destruction under native contracts; no implicit commit. |
| cost | Fixed shared-owner decrement or complete size-dependent final-state teardown. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
PhysicalRuntime::PhysicalRuntime(PhysicalRuntime&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move facade ownership without relocating runtime state. |
| inputs / outputs | Default shared-pointer move empties source facade. |
| invariants | Pending Data and reader/output owners remain valid independently; node/row addresses do not move. |
| ownership | Transfers one Impl shared owner. |
| failure | Noexcept, nonallocating. |
| cost | Constant handle movement. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0071

[Lines 698–701](../../../../../src/runtime/physical.cpp#L698); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime& PhysicalRuntime::operator=(PhysicalRuntime&& other) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace runtime facade ownership while preserving separately retained pending/readers. |
| inputs / outputs | Self-check then move shared Impl; old destination owner released. |
| invariants | Moved-from source rejects impl access; does not force commit/rollback of a token held separately. |
| ownership | Transfers facade owner; old Impl may remain through pending token or lose final owner. |
| failure | Noexcept shared-owner transfer. |
| cost | Constant transfer plus potentially full old physical state destruction. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0072

[Lines 702–702](../../../../../src/runtime/physical.cpp#L702); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::Impl& PhysicalRuntime::impl() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate facade ownership and borrow mutable implementation for controlled const APIs. |
| inputs / outputs | Require impl_ then return Impl&. |
| invariants | Moved-from facade has no implementation; individual methods enforce pending/read isolation separately. |
| ownership | Borrow requires a surviving Impl owner. |
| failure | invalid_runtime Error on moved-from; valid access allocates nothing. |
| cost | Constant pointer check. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0073

[Lines 703–703](../../../../../src/runtime/physical.cpp#L703); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& PhysicalRuntime::plan() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable admitted native program. |
| inputs / outputs | Return kernel.plan(). |
| invariants | Program metadata can be observed while physical state is pending; not a DTO export. |
| ownership | Borrow into retained kernel/program. |
| failure | Moved-from facade/kernel access can reject. |
| cost | Constant handle/reference access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0074

[Lines 704–704](../../../../../src/runtime/physical.cpp#L704); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& PhysicalRuntime::compiled_program() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow native program for trusted internal composition. |
| inputs / outputs | Return kernel.compiled_program(). |
| invariants | No ordinary compiler graph is exported or retained by this getter. |
| ownership | Borrow into retained kernel/program. |
| failure | Moved-from facade/kernel access can reject. |
| cost | Constant reference access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0075

[Lines 705–705](../../../../../src/runtime/physical.cpp#L705); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics PhysicalRuntime::accounted_memory_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy actual query-account allocation statistics. |
| inputs / outputs | Return kernel account statistics. |
| invariants | Account totals include held generations/outputs/scratch, distinct from RSS or logical row/slot counts; no quiescent row scan required. |
| ownership | Fixed numeric snapshot. |
| failure | Invalid facade/account contract can reject. |
| cost | Constant fixed-category counter copy, no ledger scan. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0076

[Lines 706–706](../../../../../src/runtime/physical.cpp#L706); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const PhysicalRuntimeOptions& PhysicalRuntime::options() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow immutable configured runtime options. |
| inputs / outputs | Return Impl options. |
| invariants | No live collector reconfiguration or validation occurs. |
| ownership | Borrow requires surviving Impl. |
| failure | Moved-from invalid_runtime. |
| cost | Constant reference access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0077

[Lines 707–707](../../../../../src/runtime/physical.cpp#L707); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOwnerId PhysicalRuntime::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read logical owner identity for physical handles/reports. |
| inputs / outputs | Return kernel.owner(). |
| invariants | Owner ID is not freshness or query equivalence proof. |
| ownership | Scalar value copy. |
| failure | Moved-from invalid_runtime. |
| cost | Constant access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0078

[Lines 708–708](../../../../../src/runtime/physical.cpp#L708); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t PhysicalRuntime::sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last committed physical sequence. |
| inputs / outputs | Return Impl sequence. |
| invariants | Tentative update does not advance this value; no implicit read of pending preview. |
| ownership | Scalar copy. |
| failure | Moved-from invalid_runtime. |
| cost | Constant access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0079

[Lines 709–709](../../../../../src/runtime/physical.cpp#L709); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool PhysicalRuntime::ready() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether a new update may proceed without pending/reader conflict. |
| inputs / outputs | Return !updating && kernel.ready(). |
| invariants | False while private physical token or kernel reader/view leases pin epoch; not a lock or concurrency primitive. |
| ownership | Reads scalar/reader metadata only. |
| failure | Moved-from facade rejects; otherwise bool. |
| cost | Constant checks. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0080

[Lines 710–710](../../../../../src/runtime/physical.cpp#L710); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool PhysicalRuntime::has_answer() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed core CQ truth. |
| inputs / outputs | Require physical readable, delegate kernel.has_answer(). |
| invariants | SQL EXISTS still returns a Boolean row even when core truth false; this bool is core truth only. |
| ownership | Scalar result. |
| failure | Busy pending update/moved-from rejects. |
| cost | Constant route/root survivor-count access under valid program. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0081

[Lines 711–711](../../../../../src/runtime/physical.cpp#L711); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& PhysicalRuntime::source_layout(TableId table) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow original source-table typed descriptor. |
| inputs / outputs | Range-check source then return shared native descriptor from source_layouts. |
| invariants | Metadata observation does not require readable(); native token is shared with actual source layout. |
| ownership | Borrow into Impl vector; copying descriptor retains metadata independently. |
| failure | Invalid table/moved-from rejects. |
| cost | Constant range/descriptor access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0082

[Lines 712–712](../../../../../src/runtime/physical.cpp#L712); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& PhysicalRuntime::result_layout(ResultView view) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow core or SQL mapped result descriptor. |
| inputs / outputs | Delegate kernel.result_layout(view). |
| invariants | Selects valid core/sql domain; metadata can be read without snapshotting result rows. |
| ownership | Borrow into retained kernel metadata. |
| failure | Moved-from or invalid ResultView rejects. |
| cost | Constant view/descriptor access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0083

[Lines 713–715](../../../../../src/runtime/physical.cpp#L713); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate PhysicalRuntime::prepare(const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare and fully route one source input without publishing it. |
| inputs / outputs | Call prepare_observed with empty observer/options. |
| invariants | Caller receives active token; source/count/support tentative state remains private until commit. All alias work is drained before return. |
| ownership | Token owns imported row/pin/journals and original account/lease; input borrowed during admission only. |
| failure | Admission or route failure restores complete previous state and returns no active token. |
| cost | Complete input validation/import/probe, optional database constraints and all alias/support work; even physical no-op pays admission costs. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0084

[Lines 716–720](../../../../../src/runtime/physical.cpp#L716); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate PhysicalRuntime::prepare_observed(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Drain every alias prefix while preserving one private update barrier. |
| inputs / outputs | Owning physical update, observer and options return a completely routed pending token. |
| invariants | Uses begin_staged/stage_next without an alternate routing or error-recovery implementation. |
| ownership | Local token owns all private state until moved to caller. |
| failure | Route failure has already rolled back; local token destruction remains idempotent RAII. |
| cost | Sum of actual route work, not full-query result enumeration or a second support pass. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0085

[Lines 721–723](../../../../../src/runtime/physical.cpp#L721); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate PhysicalRuntime::begin_staged(const PhysicalSetUpdate& update) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow caller-owned row only for native staged-input admission. |
| inputs / outputs | Convert to PhysicalUpdateView::borrow and delegate view overload. |
| invariants | No caller Row pointer survives successful admission; changed source input is imported/pinned, no-op needs no later row. |
| ownership | Nonowning temporary view then owning pending token. |
| failure | Delegated sequence/schema/busy/resource failures propagate with restoration. |
| cost | Constant view wrapping plus complete begin_staged(view) preparation. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0086

[Lines 724–734](../../../../../src/runtime/physical.cpp#L724); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRuntime::PendingUpdate PhysicalRuntime::begin_staged(const PhysicalUpdateView&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire a private physical update before exposing its alias prefixes. |
| inputs / outputs | Borrowed sequence/table/operation/full row produce an owning prepared PendingUpdate. |
| invariants | Check quiescence, contiguous sequence, operation, typed row and membership first; fully construct Data, then set updating, then prepare under that unique owner. |
| ownership | One original account, pending owner and retained storage grant fund all private source/count/kernel state. Caller row is borrowed only during admission; pending state retains native tuples/pins. |
| failure | Any preparation exception destroys local Data and rolls back before typed public presentation; invalid admission changes no sequence/state. |
| cost | Input validation/probe, funded owner/grant, then source/constraint/reserve work; no owning Row export. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0087

[Lines 735–736](../../../../../src/runtime/physical.cpp#L735); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L735-L736:sha256:b2041131564f488807da90a7fe992d35a0ae7a29187deb788dce1f928e46881c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`PhysicalEpoch PhysicalRuntime::apply(const PhysicalSetUpdate& update)\`: Even a physical no-op pays row validation/import/probe/owner admission; the selected coordinator metrics can remain zero for that committed input. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/physical.cpp:L666; use that declaration for the actual input/output shape. |
| invariants | The source note states: Even a physical no-op pays row validation/import/probe/owner admission; the selected coordinator metrics can remain zero for that committed input. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0088

[Lines 737–737](../../../../../src/runtime/physical.cpp#L737); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalEpoch PhysicalRuntime::apply(const PhysicalSetUpdate& update)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare, route and commit one complete physical set input synchronously. |
| inputs / outputs | prepare(update).commit() returns owning epoch. |
| invariants | No partial alias prefix is published; physical no-op still advances contiguous committed sequence. |
| ownership | Epoch retains source pin/derivation tuples/support journal under original account. |
| failure | Throwing preparation aborts; valid final commit uses prepared nonallocating barrier. |
| cost | All prepare/route work plus touched-journal commit cleanup; not full-query delta enumeration. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0089

[Lines 738–740](../../../../../src/runtime/physical.cpp#L738); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalEpoch PhysicalRuntime::apply_view(const PhysicalUpdateView& update)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a borrowed native/ordinary row view without a retained ordinary Row mirror. |
| inputs / outputs | begin_staged(view), drain stage_next with no observer, commit. |
| invariants | Caller row needed only during admission; all later routes use pinned imported source. |
| ownership | Returned epoch owns funded outputs; token/local view does not retain caller storage. |
| failure | Any preparation/stage failure restores whole update before return/formatting. |
| cost | Input validation/copy/probe plus full routing/support/constraint costs and commit cleanup. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp) |

## B0090

[Lines 741–743](../../../../../src/runtime/physical.cpp#L741); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor PhysicalRuntime::results(ResultCursorOptions options) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed SQL-mapped result cursor. |
| inputs / outputs | Require physical readable then delegate kernel.results(options,ResultView::sql). |
| invariants | SQL output order/repetition/constants/EXISTS mapping applies; direct CQ keeps core order. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0091

[Lines 744–746](../../../../../src/runtime/physical.cpp#L744); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor PhysicalRuntime::core_results(ResultCursorOptions options) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed core-head result cursor. |
| inputs / outputs | Require physical readable then delegate kernel.results(options,ResultView::core). |
| invariants | No SQL final output mapping; ordered/repeated core head preserved. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0092

[Lines 747–749](../../../../../src/runtime/physical.cpp#L747); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::EpochView PhysicalRuntime::current_view(EpochViewOptions options) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pin a committed logical epoch view. |
| inputs / outputs | Require physical readable then delegate kernel.current_view(options). |
| invariants | View leases block future writes; this factory cannot observe a pending physical update. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0093

[Lines 750–752](../../../../../src/runtime/physical.cpp#L750); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor PhysicalRuntime::completions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed completion cursor under fixed assignments and visible fragment. |
| inputs / outputs | Require physical readable then delegate kernel.completions(fixed,fragment,options). |
| invariants | Uses documented core fragment semantics, not final SQL mapping or a fresh snapshot copy. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0094

[Lines 753–755](../../../../../src/runtime/physical.cpp#L753); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor PhysicalRuntime::witnesses(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open committed witness cursor for fixed assignments/factor fragment. |
| inputs / outputs | Require physical readable then delegate kernel.witnesses(fixed,move(fragment),options). |
| invariants | Witness semantics remain distinct from duplicate-free output enumeration. No provider/background work; actual reader/group lifetime enforces update exclusion. |
| ownership | Returned cursor/view retains kernel/group/index/tuple ownership; caller must release it before writable() succeeds. |
| failure | Busy/moved-from/options/startup/storage/resource/allocation failures propagate from delegated factory; no physical state mutation. |
| cost | Constant wrapper plus delegated cursor/view startup and retained metadata; producing rows/deep output bytes is later cursor work. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0095

[Lines 756–757](../../../../../src/runtime/physical.cpp#L756); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalSnapshot PhysicalRuntime::snapshot() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a complete committed diagnostic snapshot. |
| inputs / outputs | Bind storage operation, require readable, obtain kernel snapshot then combine source/counts. |
| invariants | Owning diagnostic copy, not a cheap view or independent proof. Cannot read private physical state through public facade. |
| ownership | Ordinary database/support export plus funded derivation tuples; native snapshot temporaries consume original account. |
| failure | Native storage failures format after unwind; busy/export/allocation failures propagate without committed mutation. |
| cost | Full source/support/count traversal, deep copies and ordered-set work; no constant-time or strict export-temporary byte claim. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0096

[Lines 758–761](../../../../../src/runtime/physical.cpp#L758); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L758-L761:sha256:1695893b15d488661dab2f2f361f01352bca2af492b1c3fd03a6d881e664be09
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one committed source-only native capture under existing physical readability and backend-work rules. |
| inputs / outputs | Readable PhysicalRuntime and SourceImageLimits in; owning image of committed sequence out. |
| invariants | readable rejects prepared-source busy state before traversal. One StorageOperation uses original storage context; no source/result mutation, ordinary Database/string export or original-query guarantee is performed. |
| ownership | Runtime remains owner of sources; returned image owns original-account copies/program after facade teardown. Local operation/cursors retire before return; no concurrent-writer support is added. |
| failure | runtime_busy/source_image limits/indexed/memory errors propagate without source mutation. No broad wrapper converts a resource refusal into a success. |
| cost | Fresh explicit operation admission plus full source capture; indexed construction/traversal/pointer/scalar costs share that operation ceiling, and cleanup is real. |
| Design | [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp), [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [include/crown/runtime/source_image.hpp](../../../../../include/crown/runtime/source_image.hpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [tests/unit/source_image_test.cpp](../../../../../tests/unit/source_image_test.cpp), [docs/source_images.md](../../../../source_images.md) |

## B0097

[Lines 762–765](../../../../../src/runtime/physical.cpp#L762); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t PhysicalRuntime::derivation_count(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read positive native projection multiplicity for one occurrence/key. |
| inputs / outputs | Require readable, validate native key against compiled node descriptor, heterogeneous std::map lookup; absent returns0. |
| invariants | Value domain is final native-node scope, not physical full row or earlier SQL projection; per-occurrence identity matters. |
| ownership | Borrows ordinary probe synchronously; scalar result only. |
| failure | Busy/invalid occurrence/arity/type/domain or comparison/presentation failures propagate. |
| cost | Key validation plus O(log distinct projected keys) variable-width comparisons; successful lookup creates no owned probe. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0098

[Lines 766–769](../../../../../src/runtime/physical.cpp#L766); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> PhysicalRuntime::find_source(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find full physical source membership by complete typed row. |
| inputs / outputs | Bind storage operation, require readable/range, validate public descriptor, construct native probe tuple and call source.find. |
| invariants | Handle identity includes source owner/relation/generation; ignored columns still distinguish source rows. |
| ownership | Input borrowed for native copy; returned handle is scalar identity and does not pin row. |
| failure | Busy/schema/native work/memory failures propagate; typed native Index/Table failures present after probe cleanup. |
| cost | Public validation plus native tuple validation/copy and backend lookup; temporary key allocation/deep bytes are real costs. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/accounted_table.hpp](../../../../../include/crown/storage/accounted_table.hpp) |

## B0099

[Lines 770–775](../../../../../src/runtime/physical.cpp#L770); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::AccountedTuple> PhysicalRuntime::get_source(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clone a live source tuple by its typed generation handle. |
| inputs / outputs | Require readable/table range, source.get(handle); absent returns empty, present clones row under output attribution. |
| invariants | Does not expose a raw table borrow. Foreign/stale handle behavior is delegated to native source validation. |
| ownership | Result uniquely owns a deep copied row and shared layout/account, independent of later source erase/facade destruction. |
| failure | Busy/handle/storage work/validation/allocation failures propagate; public translation after cleanup. |
| cost | Backend handle lookup plus complete deep tuple copy/allocation for a present row, not constant owning output. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/storage/accounted_layout.hpp](../../../../../include/crown/storage/accounted_layout.hpp) |

## B0100

[Lines 776–778](../../../../../src/runtime/physical.cpp#L776); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SupportHandle> PhysicalRuntime::find_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a logical support-role row by typed values. |
| inputs / outputs | Require physical readable then delegate kernel.find(node,role,values). |
| invariants | Returned support handle is owner/node/role/generation qualified and does not pin a tuple. |
| ownership | Probe borrowed; scalar optional handle result. |
| failure | Busy or delegated node/role/layout/storage/resource failures propagate. |
| cost | Delegated row validation/native probe construction and backend lookup; wrapper adds constant checks. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0101

[Lines 779–781](../../../../../src/runtime/physical.cpp#L779); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::Tuple> PhysicalRuntime::get_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return immutable owning output for a live logical support handle. |
| inputs / outputs | Require physical readable then delegate kernel.get(handle). |
| invariants | No raw support table/tuple reference is exposed; wrong owner and stale handle are distinguished by kernel/storage. |
| ownership | Present result deep-copies native row into funded tuple/public payload owner; descriptor shares native metadata. |
| failure | Busy/foreign/invalid/resource/allocation failures propagate from kernel. |
| cost | Handle lookup plus native deep clone/output control allocation when present. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0102

[Lines 782–787](../../../../../src/runtime/physical.cpp#L782); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalStorageStatistics PhysicalRuntime::storage_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate committed source/support arena and derivation-key counts. |
| inputs / outputs | Require readable, read kernel storage stats, checked-sum each source arena and count-map size. |
| invariants | Counts reflect allocated/live/retained/free slots and key populations, not allocator byte totals or a captured consistent future epoch. |
| ownership | Fixed aggregate returned by value; no row payload copy. |
| failure | Busy/native stats/checked size overflow failures propagate. |
| cost | Linear in source tables, support relation descriptors and occurrence maps; does not traverse all row keys to count them. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0103

[Lines 788–788](../../../../../src/runtime/physical.cpp#L788); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InitializationContext PhysicalRuntime::initialization_context() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read how this owner was constructed/rebuilt. |
| inputs / outputs | Return copied initialization route/build options. |
| invariants | Historical setup metadata, not current row state or proof. |
| ownership | Fixed-size value copy. |
| failure | Moved-from invalid_runtime. |
| cost | Constant field copy. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0104

[Lines 789–789](../../../../../src/runtime/physical.cpp#L789); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const BuildMetrics& PhysicalRuntime::initialization_metrics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow cumulative completed construction metrics. |
| inputs / outputs | Return build_metrics. |
| invariants | Abstract build debits separate from per-event metrics, current memory and CPU time. |
| ownership | Borrow into Impl; survives only while owned. |
| failure | Moved-from invalid_runtime. |
| cost | Constant reference access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0105

[Lines 790–798](../../../../../src/runtime/physical.cpp#L790); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CanonicalPhysicalState PhysicalRuntime::canonical_state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export canonical committed source/derivation/support values for diagnostics/comparison. |
| inputs / outputs | Bind operation, require readable, copy kernel canonical state, sequence, ordinary source database and per-occurrence sorted key/count vectors. |
| invariants | Exact value snapshot is explicit export, not import or runtime-state mutation authority. |
| ownership | Owns ordinary deep row/string/vector/set copies; native source snapshot temporaries stay account funded. |
| failure | Storage fixed failures format after cleanup; export/allocation/busy failures leave state unchanged. |
| cost | Whole physical/logical state copies and sorted-set traversal; byte widths/ordered insert comparisons and peak temporaries are additional. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp) |

## B0106

[Lines 799–800](../../../../../src/runtime/physical.cpp#L799); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L799-L800:sha256:8d68317c8ebc31bb32efa3d2e2e07c3458bf46d09eda01e327fcad49ee178766
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`InvariantReport PhysicalRuntime::inspect_invariants(InspectionOptions options) const try\`: Independently recompute projected counts from sources, including a repeated base snapshot/adaptation per alias. Report limits are coarse. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/physical.cpp:L726; use that declaration for the actual input/output shape. |
| invariants | The source note states: Independently recompute projected counts from sources, including a repeated base snapshot/adaptation per alias. Report limits are coarse. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | The note describes a failure or stop boundary: Independently recompute projected counts from sources, including a repeated base snapshot/adaptation per alias. Report limits are coarse. The comment adds no handler; the surrounding code determines the outcome. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0107

[Lines 801–890](../../../../../src/runtime/physical.cpp#L801); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InvariantReport PhysicalRuntime::inspect_invariants(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently recompute committed physical-source/derivation relations into a bounded diagnostic report. |
| inputs / outputs | Inspect support first; charge/check source storage and constraints, build native source snapshots, re-adapt each occurrence into expected counts, compare actual maps and native record sets. |
| invariants | Incomplete support/charge/issue-budget stops retain complete=false. Reports distinguish checked failures from success; they do not establish fresh planner proof or arbitrary memory-corruption safety. |
| ownership | Accounted report/key/expected-map/native snapshot storage uses original report/query account; no ordinary database mirror. |
| failure | InspectionStop yields incomplete report. Recognized source invariant errors become issues; other native failures are translated, allocation/contracts can propagate. Prior committed state unchanged. |
| cost | May resnapshot/adapt the same base per alias, sort all sources, perform complete constraints and lexical map/set comparisons. Coarse charges omit comparison/string/capacity overhead; scratch can be large. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp) |

## B0108

[Lines 891–891](../../../../../src/runtime/physical.cpp#L891); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#ifdef CROWN_RUNTIME_TESTING
void RuntimeTestProbe::seed_physical_sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile controlled sequence/count/kernel mutation probes only for runtime tests. |
| inputs / outputs | Preprocessor guard encloses the corresponding RuntimeTestProbe body group. |
| invariants | Not part of the production client mutation/read API; no fallback changes when probes are absent. |
| ownership | Compilation selection only. |
| failure | Macro/target inconsistency fails compilation/linking; no runtime exception behavior. |
| cost | No production runtime work. |
| Design | [CMakeLists.txt](../../../../../CMakeLists.txt), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0109

[Lines 892–894](../../../../../src/runtime/physical.cpp#L892); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void RuntimeTestProbe::seed_physical_sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Testing-only seed of physical and logical committed sequence. |
| inputs / outputs | Require writable runtime, seed kernel and assign physical counter. |
| invariants | Compiled only with CROWN_RUNTIME_TESTING; not a production mutation API. |
| ownership | Mutates scalar test state only. |
| failure | Busy/moved-from/kernel test-contract failures propagate. |
| cost | Constant delegation/scalar assignment. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0110

[Lines 895–895](../../../../../src/runtime/physical.cpp#L895); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime& RuntimeTestProbe::support(PhysicalRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose internal logical kernel only to testing bridge. |
| inputs / outputs | Return runtime.impl().kernel. |
| invariants | CROWN_RUNTIME_TESTING only; production clients receive no mutable table/kernel reference. |
| ownership | Borrow into test runtime owner. |
| failure | Moved-from runtime rejects. |
| cost | Constant access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0111

[Lines 896–901](../../../../../src/runtime/physical.cpp#L896); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t RuntimeTestProbe::set_derivation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Testing-only corruption hook for an existing native count entry. |
| inputs / outputs | Require readable/valid occurrence/existing key, exchange count and return old value. |
| invariants | Intentionally bypasses positive-count/support consistency to exercise independent inspection; production code cannot call it. |
| ownership | Borrows key and mutates one existing map scalar; no node insertion. |
| failure | Busy/missing-key/invalid occurrence/comparison failures propagate before exchange. |
| cost | Logarithmic variable-width map lookup plus constant exchange. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0112

[Lines 902–904](../../../../../src/runtime/physical.cpp#L902); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L902-L904:sha256:f6f35d32b33f01631496310d432cf23c678a968d9ca0319dcd2d157939c4bbfd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/physical.cpp: closes the matching compile-time guard. Source comment: Full fail-fast recomputation, not a cheap flag check. Native snapshots, expected row maps and record sets all use the original account. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. The source note says: Full fail-fast recomputation, not a cheap flag check. Native snapshots, expected row maps and record sets all use the original account. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Full fail-fast recomputation, not a cheap flag check. Native snapshots, expected row maps and record sets all use the original account. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0113

[Lines 905–932](../../../../../src/runtime/physical.cpp#L905); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void PhysicalRuntime::check_invariants() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail-fast independently verify complete committed source/count/native consistency. |
| inputs / outputs | Require readable/equal sequences, check logical/source storage, full source constraints, re-adapt every occurrence into expected counts, compare map/native-key populations and values. |
| invariants | Does not rely on stored derivation counts as expected truth; trusted immutable compiled adapters still define semantics. No bounded InvariantReport partial-success wrapper. |
| ownership | Native snapshots/expected AVL maps/record sets allocated in original account; source remains unchanged. |
| failure | Detected mismatch throws runtime_contract; native Index/Table failures format after unwind; resource/allocation failures propagate rather than claiming successful verification. |
| cost | Complete support/source scans, repeated per-alias adaptation/snapshots and ordered deep-key comparisons; may sort/copy all rows and consume substantial temporary capacity. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md), [src/runtime/constraint_validation.hpp](../../../../../src/runtime/constraint_validation.hpp), [src/runtime/validation_work.hpp](../../../../../src/runtime/validation_work.hpp), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp) |

## B0114

[Lines 933–933](../../../../../src/runtime/physical.cpp#L933); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<detail::ObservationState> PhysicalRuntime::observation_state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share optional internal observation owner with coordinating layers. |
| inputs / outputs | Return Impl observation shared_ptr copy. |
| invariants | Does not create/configure an observer or snapshot rows. |
| ownership | Adds observer owner, independent of facade lifetime. |
| failure | Moved-from facade rejects. |
| cost | Constant refcount copy. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0115

[Lines 934–934](../../../../../src/runtime/physical.cpp#L934); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CursorObservation> PhysicalRuntime::last_cursor_observation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read last recorded cursor diagnostic. |
| inputs / outputs | Delegate kernel.last_cursor_observation(). |
| invariants | No cursor is executed/restarted; availability remains as recorded. |
| ownership | Value/optional diagnostic copy. |
| failure | Moved-from facade/kernel rejects. |
| cost | Fixed diagnostic copy. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0116

[Lines 935–944](../../../../../src/runtime/physical.cpp#L935); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CommittedStateGauges PhysicalRuntime::committed_state_gauges() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export ordinary committed population gauges. |
| inputs / outputs | Require readable; Start kernel committed gauges, overwrite physical base total and append table counts. |
| invariants | Base total saturates at UINT64_MAX with explicit saturated flag; source/support node gauges remain separate. These are current committed counts, not CPU/bytes. |
| ownership | Owns ordinary vectors copied/allocated for caller; no row payloads. |
| failure | Busy/moved-from/allocation failures propagate; no committed state mutation. |
| cost | Linear source-table/support-node metadata scans and gauge vector allocations, not all source row scans. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0117

[Lines 945–954](../../../../../src/runtime/physical.cpp#L945); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedStateGauges PhysicalRuntime::capture_state_gauges() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture funded committed population gauges. |
| inputs / outputs | Require readable; Start account-backed kernel captured gauges, overwrite physical base total and append table counts. |
| invariants | Base total saturates at UINT64_MAX with explicit saturated flag; source/support node gauges remain separate. These are current committed counts, not CPU/bytes. |
| ownership | Owns account-backed retained vectors/metadata; no row payloads. |
| failure | Busy/moved-from/allocation failures propagate; no committed state mutation. |
| cost | Linear source-table/support-node metadata scans and gauge vector allocations, not all source row scans. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/support.cpp](../../../../../src/runtime/support.cpp) |

## B0118

[Lines 955–957](../../../../../src/runtime/physical.cpp#L955); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationSnapshot PhysicalRuntime::observations() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy current observation summary. |
| inputs / outputs | Kernel observations with physical initialization context overwritten. |
| invariants | Instrumentation may describe an active attempt; no readable() guard or source-row snapshot is added by this wrapper. |
| ownership | Fixed summary value; no new observer owner. |
| failure | Moved-from/delegated trace allocation failures can propagate; summary valid-path copy is nonallocating. |
| cost | Fixed metric-registry snapshot copy. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp) |

## B0119

[Lines 958–960](../../../../../src/runtime/physical.cpp#L958); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTrace PhysicalRuntime::observation_trace() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export ordinary observation trace. |
| inputs / outputs | Kernel trace with snapshot initialization context overwritten. |
| invariants | Instrumentation may describe an active attempt; no readable() guard or source-row snapshot is added by this wrapper. |
| ownership | Ordinary output trace copies records. |
| failure | Moved-from/delegated trace allocation failures can propagate; summary valid-path copy is nonallocating. |
| cost | Trace-record copy/allocation proportional to retained trace length. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp) |

## B0120

[Lines 961–963](../../../../../src/runtime/physical.cpp#L961); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedObservationTrace PhysicalRuntime::capture_observation_trace() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture funded observation trace. |
| inputs / outputs | Kernel captured trace with physical initialization context overwritten. |
| invariants | Instrumentation may describe an active attempt; no readable() guard or source-row snapshot is added by this wrapper. |
| ownership | Account-backed owning output record array. |
| failure | Moved-from/delegated trace allocation failures can propagate; summary valid-path copy is nonallocating. |
| cost | Trace-record copy/accounted allocation proportional to captured length. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/observation.cpp](../../../../../src/runtime/observation.cpp) |

## B0121

[Lines 964–989](../../../../../src/runtime/physical.cpp#L964); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool PhysicalRuntime::same_sources(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare two quiescent source databases exactly within one reoptimization budget. |
| inputs / outputs | Check sequence/table/population agreement, collect left rows in budgeted lexical set, probe/erase each right row, require set empty. |
| invariants | Full physical row identity including unused fields/tables is compared; equality is not inferred from hashes/counts. Both owners must be writable/quiescent. |
| ownership | Temporary keys from both sides are deep-copied into left account; sets/iterators stay local and source states remain unchanged. |
| failure | Budget row/work or storage/memory/comparison failures propagate; false mismatch is distinct from resource failure. |
| cost | Copies all left rows and each right probe, O(R log R) lexical comparisons plus scalar/string byte budget charging. Coexists with both owners and retains no global query result. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp) |

## B0122

[Lines 990–992](../../../../../src/runtime/physical.cpp#L990); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L990-L992:sha256:8a289c52265f032d42385d65af77db38f02dd5350de0eb04b777a405216fc9ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/physical.cpp: opens namespace \`crown::runtime\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0123

[Lines 993–995](../../../../../src/runtime/physical.cpp#L993); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void PhysicalRuntime::configure_workload_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace workload collector configuration at a quiescent physical boundary. |
| inputs / outputs | Require writable, configure collector from compiled physical program/options/current sequence. |
| invariants | Explicit caller action changes collection interval/configuration; it is not performed implicitly by capture/ranking. |
| ownership | Collector owns native configuration/routes/slabs under existing account. |
| failure | Busy/invalid options/budget/memory/configuration failures propagate per collector contract. |
| cost | Potential descriptor/route/configured-slab construction and allocation, not a constant assignment. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp) |

## B0124

[Lines 996–998](../../../../../src/runtime/physical.cpp#L996); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void PhysicalRuntime::reset_workload_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly reset workload interval at the committed physical sequence. |
| inputs / outputs | Require writable then collector.reset(sequence). |
| invariants | Reset is caller-authorized state change; reset saturation/availability remain explicit collector metadata. |
| ownership | Reuses existing collector ownership/configured storage. |
| failure | Busy/moved-from/collector contract failures propagate. |
| cost | Collector reset work depends on configured statistics slabs; no row database scan. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp) |

## B0125

[Lines 999–1001](../../../../../src/runtime/physical.cpp#L999); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::Snapshot PhysicalRuntime::workload_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture as-of workload evidence with committed stamp and pending flag. |
| inputs / outputs | Collector.snapshot(compiled program,owner,sequence,updating). |
| invariants | Allowed during private update but marked pending; copied statistics do not authorize reading private source state or assert future freshness. |
| ownership | Retains native plan and funded copied configured descriptor/counter slabs; source epoch not advanced. |
| failure | Snapshot allocation/collector/moved-from failures propagate. |
| cost | Copies configured workload arrays/slabs even if source table is small; collector bounds and account cap are separate from later rank budget. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/workload_statistics.cpp](../../../../../src/runtime/workload_statistics.cpp) |

## B0126

[Lines 1002–1002](../../../../../src/runtime/physical.cpp#L1002); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::detail::State& PhysicalRuntime::workload_state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow kernel-owned internal workload collector. |
| inputs / outputs | Dereference Impl workload pointer. |
| invariants | Only trusted composition uses it; kernel owns the pointed state for Impl lifetime. |
| ownership | Nonowning mutable reference; no fresh collector. |
| failure | Moved-from rejects; retained internal pointer validity assumed. |
| cost | Constant access. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0127

[Lines 1003–1003](../../../../../src/runtime/physical.cpp#L1003); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<detail::StorageWorkContext> PhysicalRuntime::storage_context() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share existing account/backend operation context for nested coordination. |
| inputs / outputs | Return Impl storage_context shared_ptr. |
| invariants | Copying context does not replenish any finite operation lease or memory grant. |
| ownership | Shared owner transfer by copy. |
| failure | Moved-from invalid_runtime. |
| cost | Constant refcount work. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0128

[Lines 1004–1004](../../../../../src/runtime/physical.cpp#L1004); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#ifdef CROWN_RUNTIME_TESTING
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile native grant observation probe only for runtime tests. |
| inputs / outputs | Preprocessor guard encloses the corresponding RuntimeTestProbe body group. |
| invariants | Not part of the production client mutation/read API; no fallback changes when probes are absent. |
| ownership | Compilation selection only. |
| failure | Macro/target inconsistency fails compilation/linking; no runtime exception behavior. |
| cost | No production runtime work. |
| Design | [CMakeLists.txt](../../../../../CMakeLists.txt), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0129

[Lines 1005–1007](../../../../../src/runtime/physical.cpp#L1005); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(const PhysicalRuntime& runtime)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Testing-only inspect kernel native operation grant consumption. |
| inputs / outputs | Delegate index_work(runtime.impl().kernel). |
| invariants | CROWN_RUNTIME_TESTING only; does not mint/replenish a grant. |
| ownership | Fixed optional work snapshot. |
| failure | Moved-from runtime rejects. |
| cost | Fixed counters/optional delegation. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0130

[Lines 1008–1011](../../../../../src/runtime/physical.cpp#L1008); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1008-L1011:sha256:9b30c7050419b4d612c4618acde68c399494ec4ca84fa69b0958dd92d89674d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/physical.cpp: imports \`"owner_statistics_detail.hpp"\` for compilation; closes the matching compile-time guard; opens namespace \`crown::runtime\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: namespace crown::runtime Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0131

[Lines 1012–1014](../../../../../src/runtime/physical.cpp#L1012); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::OwnerCapture PhysicalRuntime::capture_statistics(const statistics::OwnerRequest& request,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture selected committed physical/support facts from an owning request. |
| inputs / outputs | Delegate request view to capture_statistics_view. |
| invariants | No collector reconfiguration/reset or hidden ranking fallback; pending/partial availability is explicit. |
| ownership | Request borrowed synchronously; returned capture owns funded selected descriptors/facts. |
| failure | Delegated request/schema/storage/allocation failures propagate. |
| cost | Fixed view conversion plus complete requested capture cost. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp) |

## B0132

[Lines 1015–1040](../../../../../src/runtime/physical.cpp#L1015); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::OwnerCapture PhysicalRuntime::capture_statistics_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build bounded typed source/occurrence/support fact capture at one physical owner stamp. |
| inputs / outputs | Bind operation, initialize OwnerBuilder with pending flag, dispatch source table selections, full-native derivation distributions or logical selections, then finish. |
| invariants | Pending private state returns marked unavailable facts through inactive builder, not a source read. Occurrence distributions require complete native keys, never arbitrary field projections. Exhausted detail remains explicitly partial. |
| ownership | Request views borrowed during call; captured selections/layouts/native distribution data funded by existing program account. |
| failure | Invalid request/occurrence/fields reject. Statistics Exhausted marks component budget_exhausted; native fixed failures format; allocation/other errors propagate. |
| cost | Requested component traversal and weighted derivation-map scan, row/key/string comparisons and native capture allocations. Builder may stop early with partial metadata; not a full database snapshot. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [docs/statistics.md](../../../../statistics.md) |

## B0133

[Lines 1041–1043](../../../../../src/runtime/physical.cpp#L1041); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::Freshness PhysicalRuntime::statistics_freshness(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare captured owner/layer/sequence stamp to current physical boundary. |
| inputs / outputs | Call compare_freshness(old,{owner,sequence,physical},max_event_lag). |
| invariants | Classifies foreign/layer/future/current/within-lag/stale; does not validate capture completeness, workload interval/mode or private-state availability. |
| ownership | Borrows capture and copies fixed stamps only. |
| failure | Moved-from runtime or capture handle contract errors can reject. |
| cost | Constant scalar stamp arithmetic; no row scan or allocation. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/owner_statistics.cpp](../../../../../src/runtime/owner_statistics.cpp) |

## B0134

[Lines 1044–1046](../../../../../src/runtime/physical.cpp#L1044); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1044-L1046:sha256:9e2f18da6f8adce73571e3f18b38528116ccefb4e7fba17887471ac59051fd9b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/physical.cpp: opens namespace \`crown::runtime::memory::detail\`; closes \`namespace crown::runtime\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0135

[Lines 1047–1057](../../../../../src/runtime/physical.cpp#L1047); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Access::append(Builder& builder,const PhysicalRuntime& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append physical operator/table/count ownership partition into memory report builder. |
| inputs / outputs | Append logical kernel first, coordinator attribution, every source table, then occurrence count-map attribution/key count after matching native record population. |
| invariants | Checks per-occurrence derivation key population agrees with corresponding logical records; not a full row/value or multiplicity recomputation. |
| ownership | Builder retains funded report values, owner remains borrowed; existing allocation owners are described without retagging. |
| failure | Builder resource/inconsistent population failures propagate to outer memory attempt boundary. |
| cost | Complete support/source table, resident arena/index and repeated account-ledger memory-statistics scans, plus report-table searches for each occurrence. This is a full diagnostic traversal, not a row-free metadata read. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../memory_reports.md) |

## B0136

[Lines 1058–1066](../../../../../src/runtime/physical.cpp#L1058); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt Access::capture(const PhysicalRuntime& owner,Limits limits) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture native memory report or explicit failure without publishing a partial Report. |
| inputs / outputs | Use common noexcept attempt boundary, validate facade, create Builder with account/stamp/hash and pending/committed availability; append details only when committed. |
| invariants | Pending report advertises availability and omits private table/count partition rather than inventing committed totals. |
| ownership | Returned immutable report data funded by existing query account; no ordinary graph/row export. |
| failure | Common attempt maps fixed budget, memory overflow/contract/limit, bad_alloc and unexpected failures to typed stops. |
| cost | Committed capture pays complete append table/arena/index/ledger traversals; pending skips that partition but finish still inventories actual account allocations/attributions. Funded output growth, logical report limits and actual account capacity are separate. |
| Design | [include/crown/runtime/physical.hpp](../../../../../include/crown/runtime/physical.hpp), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp), [docs/memory_reports.md](../../../../memory_reports.md) |

## B0137

[Lines 1067–1067](../../../../../src/runtime/physical.cpp#L1067); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1067-L1067:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::memory::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::memory::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::memory::detail\` at its lexical source position in src/runtime/physical.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::memory::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
