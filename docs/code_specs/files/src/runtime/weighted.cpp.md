# `src/runtime/weighted.cpp` — block usage map

[Source](../../../../../src/runtime/weighted.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Execute weighted logical replacements and projected tuple/multiplicity enumeration with separate full messages, local visible factors and compact undo.

Snapshot SHA-256: `f0e3ca853017df5b55ced4d2cf97748e70ebaa99c74ef47576134afba1a9259b`. 796 lines partitioned into 107 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [weighted](../../../subsystem_contracts.md#weighted). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/runtime/weighted.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. | source comment (unverified): // Full-subtree equations and usage contracts: docs/weighted_messages.md, · [reviewed contract](#b0001) |
| [B0002 · 20–28](../../../../../src/runtime/weighted.cpp#L20) | Callable definition: std::shared_ptr&lt;RecordValue&gt; capture_record(const resource::MemoryAccount& account, const RecordValue& source) | calls size, std::copy, begin, end; returns result; growth make_accounted_shared; source comment (unverified): // Explicit diagnostics only: never share mutable live arrays with a caller. · [reviewed contract](#b0002) |
| [B0003 · 29–42](../../../../../src/runtime/weighted.cpp#L29) | Callable definition: Binding bind(const CompiledProgram& program, std::uint64_t limit) | calls physical_sha256, require, size, std::copy; guard require(shape.size()==64,"weighted_contract","structural program has no physical binding");; returns result; source comment (unverified): // Fixed-stack, domain-separated identity; structural set identity stays intact. · [reviewed contract](#b0003) |
| [B0004 · 43–44](../../../../../src/runtime/weighted.cpp#L43) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 45–50](../../../../../src/runtime/weighted.cpp#L45) | Callable definition: weighted_detail::Node::Node(const resource::MemoryAccount& account, NodeId id, std::size_t arity) :attribution{resource::MemoryOw… | calls records, allocator_type, messages, factors · [reviewed contract](#b0005) |
| [B0006 · 51–53](../../../../../src/runtime/weighted.cpp#L51) | Callable definition: void weighted_detail::Node::lifetime(const void* pointer, resource::AllocationLifetime value) const | calls get_allocator, account, set_lifetime_containing · [reviewed contract](#b0006) |
| [B0007 · 54–54](../../../../../src/runtime/weighted.cpp#L54) | Explanatory comments or spacing. |  |
| [B0008 · 55–57](../../../../../src/runtime/weighted.cpp#L55) | Callable definition: weighted::RecordValue::RecordValue(const resource::MemoryAccount& account, resource::MemoryAttribution owner, std::size_t arity, … | calls children · [reviewed contract](#b0008) |
| [B0009 · 58–60](../../../../../src/runtime/weighted.cpp#L58) | Callable definition: weighted::Journal::Journal(const resource::MemoryAccount& account, std::uint64_t epoch) :sequence(epoch),records(resource::OwnerA… | calls sequence, records, events · [reviewed contract](#b0009) |
| [B0010 · 61–64](../../../../../src/runtime/weighted.cpp#L61) | Callable definition: weighted::NodeSnapshot::NodeSnapshot(const resource::MemoryAccount& account, NodeId id) :node(id),records(resource::OwnerAllocato… | calls node, records, messages, factors · [reviewed contract](#b0010) |
| [B0011 · 65–66](../../../../../src/runtime/weighted.cpp#L65) | Explanatory comments or spacing. | source comment (unverified): // Freeze once; full messages and local output factors have separate maps. · [reviewed contract](#b0011) |
| [B0012 · 67–68](../../../../../src/runtime/weighted.cpp#L67) | Callable definition: WeightedRuntime::Impl::Impl(CompiledProgram shape, weighted::Options opts, std::shared_ptr&lt;detail::StorageWorkContext&gt; work) :Imp… | calls Impl, make_storage, detail::compact_storage_work; source comment (unverified): // Freeze once; full messages and local output factors have separate maps. · [reviewed contract](#b0012) |
| [B0013 · 69–102](../../../../../src/runtime/weighted.cpp#L69) | Callable definition: WeightedRuntime::Impl::Impl(CompiledProgram shape,weighted::Options opts,std::shared_ptr&lt;detail::StorageWorkContext&gt; work, storag… | calls options, context, std::move, program; guard require(admission.admitted(),"unsupported_annotation","weighted subtree backend is unavailable");; growth emplace_back, push_back, reserve; 6 loop sites; source comment (unverified): // Compile outside-child positions once. One flat immutable array avoids · [reviewed contract](#b0013) |
| [B0014 · 103–103](../../../../../src/runtime/weighted.cpp#L103) | Callable definition: const resource::MemoryAccount& WeightedRuntime::Impl::account() const | calls memory; returns context-&gt;memory() · [reviewed contract](#b0014) |
| [B0015 · 104–104](../../../../../src/runtime/weighted.cpp#L104) | Callable definition: storage::IndexWorkAllowance* WeightedRuntime::Impl::allowance() const | calls detail::compact_storage_work; returns detail::compact_storage_work(context) · [reviewed contract](#b0015) |
| [B0016 · 105–105](../../../../../src/runtime/weighted.cpp#L105) | Callable definition: void WeightedRuntime::Impl::readable() const | calls require; guard void WeightedRuntime::Impl::readable() const { require(!updating,"runtime_busy","a weighted logical… · [reviewed contract](#b0016) |
| [B0017 · 106–111](../../../../../src/runtime/weighted.cpp#L106) | Callable definition: Multiplicity WeightedRuntime::Impl::summary() const noexcept | calls route, tree, empty, begin; returns {1}; {} · [reviewed contract](#b0017) |
| [B0018 · 112–126](../../../../../src/runtime/weighted.cpp#L112) | Callable definition: template&lt;class Shape&gt; std::shared_ptr&lt;WeightedRuntime::Impl&gt; WeightedRuntime::Impl::create(const Shape& shape, weighted::Options … | calls require, normalized, checked, resource::MemoryAccount::create; guard require(!shape.normalized(),"unsupported_weighted_sql","weighted runtime requires a direct-CQ struc…; returns resource::make_accounted_shared&lt;Impl&gt;(context-&gt;memory(),resource::MemoryPurpose::support_metadata,; growth make_accounted_shared · [reviewed contract](#b0018) |
| [B0019 · 127–127](../../../../../src/runtime/weighted.cpp#L127) | Explanatory comments or spacing. |  |
| [B0020 · 128–141](../../../../../src/runtime/weighted.cpp#L128) | Callable definition: WeightedRuntime detail::SqlColdRebuild::native(const resource::MemoryAccount& account,const PhysicalPlan& shape, weighted::Option… | calls require, bool, memory, statistics; guard require(bool(account) && context && context-&gt;memory().statistics().owner==account.statistics().owne…; returns WeightedRuntime(resource::make_accounted_shared&lt;WeightedRuntime::Impl&gt;(account,; growth make_accounted_shared · [reviewed contract](#b0020) |
| [B0021 · 142–153](../../../../../src/runtime/weighted.cpp#L142) | Callable definition: void detail::SqlColdRebuild::close_native(WeightedRuntime& runtime,weighted::Options options) | calls impl, readable, require, active; guard require(owner.readers==0 && !owner.context-&gt;active(),"storage_contract","cold native grant is still…; source comment (unverified): // Allocate before replacing anything. No live token/cursor/storage journal · [reviewed contract](#b0021) |
| [B0022 · 154–164](../../../../../src/runtime/weighted.cpp#L154) | declares types or opens a type body. | source comment (unverified): // One exclusive transaction and grant across stages. Fund each inverse before · [reviewed contract](#b0022) |
| [B0023 · 165–165](../../../../../src/runtime/weighted.cpp#L165) | Type/record definition: enum class PendingKind | source comment (unverified): // Contribution replacement uses the existing native lookup. This private · [reviewed contract](#b0023) |
| [B0024 · 166–166](../../../../../src/runtime/weighted.cpp#L166) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(sizeof(PendingKind)==sizeof(EventKind)); · [reviewed contract](#b0024) |
| [B0025 · 167–174](../../../../../src/runtime/weighted.cpp#L167) | Type/record definition: struct Pending |  · [reviewed contract](#b0025) |
| [B0026 · 175–175](../../../../../src/runtime/weighted.cpp#L175) | Type/record definition: enum class UndoKind |  · [reviewed contract](#b0026) |
| [B0027 · 176–189](../../../../../src/runtime/weighted.cpp#L176) | Type/record definition: struct Undo | source comment (unverified): // The node's message or visible-factor map. · [reviewed contract](#b0027) |
| [B0028 · 190–198](../../../../../src/runtime/weighted.cpp#L190) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Only the opt-in path owns these buffers. Selected rows borrow private table · [reviewed contract](#b0028) |
| [B0029 · 199–204](../../../../../src/runtime/weighted.cpp#L199) | Type/record definition: struct Frame |  · [reviewed contract](#b0029) |
| [B0030 · 205–212](../../../../../src/runtime/weighted.cpp#L205) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0030) |
| [B0031 · 213–220](../../../../../src/runtime/weighted.cpp#L213) | Callable definition: DeltaWalk(Data& value):epoch(value),bag(*value.deltas), frames(resource::MemoryAllocator&lt;Frame&gt;(value.owner-&gt;account(),resource::… | calls epoch, bag, frames, account; growth emplace_back, reserve; 1 loop sites; source comment (unverified): // Init and failure cleanup. · [reviewed contract](#b0031) |
| [B0032 · 221–225](../../../../../src/runtime/weighted.cpp#L221) | Callable definition: storage::AccountedTuple project(const storage::AccountedProjection& projection, const storage::AccountedTuple& tuple) | calls fields, charge, bytes, values; returns projection.apply(tuple); 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 226–250](../../../../../src/runtime/weighted.cpp#L226) | Callable definition: bool select(Frame& frame, const program::EnumerationStep& step) | calls charge, project, compare, values; guard require(frame.factor.present(),"weighted_contract","private visible key has no positive factor");; returns false; false; source comment (unverified): // Open and its eventual allocation-free cursor close. · [reviewed contract](#b0033) |
| [B0034 · 251–251](../../../../../src/runtime/weighted.cpp#L251) | Callable definition: void close_frame(Frame& frame) noexcept | calls reset · [reviewed contract](#b0034) |
| [B0035 · 252–252](../../../../../src/runtime/weighted.cpp#L252) | Callable definition: storage::ScalarView value(AssignmentSlot slot) const | calls values; returns frames\[slot.step\].selected-&gt;values()\[slot.field.value\] · [reviewed contract](#b0035) |
| [B0036 · 253–289](../../../../../src/runtime/weighted.cpp#L253) | Callable definition: void collect(NodeId node, const storage::AccountedTuple& key, Multiplicity before, Multiplicity after) | calls present, enumeration, reset, size; guard require(anchor_step&lt;frames.size(),"weighted_contract","factor is outside the checked visible traver…; growth push_back; 5 loop sites; source comment (unverified): // A positive-to-positive factor change cannot alter DISTINCT support. · [reviewed contract](#b0036) |
| [B0037 · 290–292](../../../../../src/runtime/weighted.cpp#L290) | Member/declaration region. |  · [reviewed contract](#b0037) |
| [B0038 · 293–306](../../../../../src/runtime/weighted.cpp#L293) | Callable definition: Data(std::shared_ptr&lt;Impl&gt; value, std::uint64_t sequence, DeltaCapture capture) :owner(std::move(value)),lease(detail::storage_le… | calls owner, std::move, lease, detail::storage_lease; growth make_accounted_shared, make_accounted_unique · [reviewed contract](#b0038) |
| [B0039 · 307–307](../../../../../src/runtime/weighted.cpp#L307) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0039) |
| [B0040 · 308–310](../../../../../src/runtime/weighted.cpp#L308) | Callable definition: Impl& active() const | calls require, bool; guard require(bool(owner),"invalid_epoch","weighted epoch is closed");return *owner;; returns *owner · [reviewed contract](#b0040) |
| [B0041 · 311–317](../../../../../src/runtime/weighted.cpp#L311) | Callable definition: void charge(std::uint64_t amount=1) | calls require; guard require(amount&lt;=UINT64_MAX-used && (!owner-&gt;options.work_limit \|\| · [reviewed contract](#b0041) |
| [B0042 · 318–322](../../../../../src/runtime/weighted.cpp#L318) | Callable definition: void metric(std::uint64_t& value, std::uint64_t amount=1) | calls charge; source comment (unverified): // Each such counter is a subset of cumulative work; charge proves room · [reviewed contract](#b0042) |
| [B0043 · 323–328](../../../../../src/runtime/weighted.cpp#L323) | Callable definition: void sample_grant() noexcept | calls limit, get, remaining · [reviewed contract](#b0043) |
| [B0044 · 329–361](../../../../../src/runtime/weighted.cpp#L329) | Callable definition: void rollback() noexcept | calls reset, rbegin, rend, erase; growth insert; 2 loop sites; source comment (unverified): // Release private readers before inverse table work. · [reviewed contract](#b0044) |
| [B0045 · 362–367](../../../../../src/runtime/weighted.cpp#L362) | Callable definition: storage::AccountedStorageTable::Journal& writer(RelationId id) | calls table, journal, detail::owning_storage_work, emplace_back; returns table; tables.back().second; growth emplace_back; 1 loop sites; source comment (unverified): // Reuse the table journal and the epoch grant; neither creates a refill. · [reviewed contract](#b0045) |
| [B0046 · 368–371](../../../../../src/runtime/weighted.cpp#L368) | Callable definition: storage::AccountedStorageTable::Cursor live(RelationId id) | calls table, allowance; returns table.live(); owner-&gt;storage.table(id).live(owner-&gt;allowance()); 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 372–375](../../../../../src/runtime/weighted.cpp#L372) | Callable definition: storage::AccountedStorageTable::Cursor delta_live(RelationId id) | calls charge, live, table, allowance; returns table.live(); owner-&gt;storage.table(id).live(owner-&gt;allowance()); 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 376–379](../../../../../src/runtime/weighted.cpp#L376) | Callable definition: storage::AccountedStorageTable::Cursor bucket(RelationId id, IndexId index, const storage::AccountedTuple& key) | calls charge, bucket_cursor, table, allowance; returns table.bucket_cursor(index,key); owner-&gt;storage.table(id).bucket_cursor(index,key,owner-&gt;allowance()); 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 380–383](../../../../../src/runtime/weighted.cpp#L380) | Callable definition: TupleHandle insert(RelationId id, const storage::AccountedTuple& tuple) | calls metric, writer, require; guard require(result.inserted,"weighted_contract","weighted storage duplicated membership");return result…; returns result.handle; growth insert · [reviewed contract](#b0049) |
| [B0050 · 384–386](../../../../../src/runtime/weighted.cpp#L384) | Callable definition: void erase(RelationId id, TupleHandle handle) | calls metric, require, writer; guard metric(output.metrics.storage_changes);require(writer(id).erase(handle),"weighted_contract","weight… · [reviewed contract](#b0050) |
| [B0051 · 387–390](../../../../../src/runtime/weighted.cpp#L387) | Callable definition: Undo& prepare(UndoKind action, Node& node, TupleId id) | calls metric, emplace_back; returns undo.emplace_back(action,node,id); growth emplace_back · [reviewed contract](#b0051) |
| [B0052 · 391–395](../../../../../src/runtime/weighted.cpp#L391) | Callable definition: Multiplicity message_at(NodeId id, const storage::AccountedTuple& key) | calls metric, nodes, table, find; returns found?owner-&gt;nodes\[id.value\].messages.at(found-&gt;tuple):Multiplicity{} · [reviewed contract](#b0052) |
| [B0053 · 396–406](../../../../../src/runtime/weighted.cpp#L396) | Callable definition: void initialize_children(const program::PhysicalNode& shape, RecordValue& value, const storage::AccountedTuple& row, std::optiona… | calls size, edges, message_at, apply; 1 loop sites · [reviewed contract](#b0053) |
| [B0054 · 407–417](../../../../../src/runtime/weighted.cpp#L407) | Callable definition: Multiplicity product(const RecordValue& value, Multiplicity local, std::size_t supported, std::optional&lt;std::size_t&gt; slot={}, Mul… | calls size, metric, multiply; returns {}; result; 1 loop sites; source comment (unverified): // Missing support makes the complete product zero before any overflow-prone · [reviewed contract](#b0054) |
| [B0055 · 418–422](../../../../../src/runtime/weighted.cpp#L418) | Callable definition: std::shared_ptr&lt;RecordValue&gt; image(const RecordValue* source) | calls metric, size, capture_record, account; returns {}; capture_record(owner-&gt;account(),*source) · [reviewed contract](#b0055) |
| [B0056 · 423–437](../../../../../src/runtime/weighted.cpp#L423) | Callable definition: Multiplicity local_factor(const program::PhysicalNode& shape, const RecordValue& value, Multiplicity local, Multiplicity subtree,… | calls present, metric, multiply; returns {}; result; 1 loop sites; source comment (unverified): // Surviving rows contribute only their own native weight and outside-C* · [reviewed contract](#b0056) |
| [B0057 · 438–444](../../../../../src/runtime/weighted.cpp#L438) | Callable definition: void factor_change(const program::PhysicalNode& shape, const storage::AccountedTuple& tuple, Multiplicity before, Multiplicity af… | calls require, replace_projection, apply; guard require(shape.connex && shape.visible_projection && shape.visible_relation,; source comment (unverified): /*visible=*/ · [reviewed contract](#b0057) |
| [B0058 · 445–450](../../../../../src/runtime/weighted.cpp#L445) | Callable definition: void note_row(const program::PhysicalNode& shape, TupleHandle handle, Record before, Record after) | calls metric, table, pin, allowance; growth emplace_back · [reviewed contract](#b0058) |
| [B0059 · 451–460](../../../../../src/runtime/weighted.cpp#L451) | Callable definition: void insert_row(const program::PhysicalNode& shape, TupleHandle handle, const storage::AccountedTuple& tuple, RecordValue value) | calls local_factor, note_row, image, prepare; guard require(node.records.emplace(handle.tuple,std::move(value)).second,"weighted_contract","weighted ro…; growth emplace · [reviewed contract](#b0059) |
| [B0060 · 461–484](../../../../../src/runtime/weighted.cpp#L461) | Callable definition: void change_row(const program::PhysicalNode& shape, TupleHandle handle, const storage::AccountedTuple& tuple, Multiplicity local,… | calls at, nodes, present, local_factor; source comment (unverified): // Default numeric path changes only inline fields/one slot. Full before/after · [reviewed contract](#b0060) |
| [B0061 · 485–495](../../../../../src/runtime/weighted.cpp#L485) | Callable definition: void remove_row(const program::PhysicalNode& shape, TupleHandle handle, const storage::AccountedTuple& tuple) | calls find, note_row, image, prepare · [reviewed contract](#b0061) |
| [B0062 · 496–505](../../../../../src/runtime/weighted.cpp#L496) | Callable definition: void enqueue(Pending event) | calls metric, push_back, std::move, size; growth push_back; source comment (unverified): // Same-key numeric deltas are causal, unlike coalescible presence flags. · [reviewed contract](#b0062) |
| [B0063 · 506–542](../../../../../src/runtime/weighted.cpp#L506) | Callable definition: void replace_projection(const program::PhysicalNode& shape, storage::AccountedTuple key, Multiplicity old, Multiplicity next, boo… | calls metric, table, find, allowance; guard if (!found) require(values.emplace(handle.tuple,after).second,"weighted_contract","weighted project…; growth emplace, emplace_back, insert; source comment (unverified): // Both projections replace one row contribution in an exact sum. Only a · [reviewed contract](#b0063) |
| [B0064 · 543–556](../../../../../src/runtime/weighted.cpp#L543) | Callable definition: void value_change(const program::PhysicalNode& shape, const storage::AccountedTuple& tuple, Multiplicity before, Multiplicity aft… | calls metric, present, insert, table; guard require(handle.has_value(),"weighted_contract","positive weighted row has no survivor");erase(shape…; growth insert; source comment (unverified): /*visible=*/ · [reviewed contract](#b0064) |
| [B0065 · 557–592](../../../../../src/runtime/weighted.cpp#L557) | Callable definition: void native(Pending& event) | calls metric, charge, add, nodes; guard } else require(current==event.before,"weight_conflict","expected native weight differs from the cur…; growth insert; source comment (unverified): // The caller supplies its own old/new share. Normalize exactly once at · [reviewed contract](#b0065) |
| [B0066 · 593–606](../../../../../src/runtime/weighted.cpp#L593) | Callable definition: void child_row(const program::PhysicalNode& shape, TupleHandle handle, const storage::AccountedTuple& tuple, const program::Physi… | calls metric, at, require, present; guard require(before.children\[edge.child_slot\]==event.before,"weighted_contract","numeric child events mu… · [reviewed contract](#b0066) |
| [B0067 · 607–627](../../../../../src/runtime/weighted.cpp#L607) | Callable definition: void child(Pending& event) | calls edges, nodes, require, has_value; guard require(edge.reverse_index.has_value(),"weighted_contract","native parent lacks a reverse separator…; growth insert; 1 loop sites; source comment (unverified): // The child table may already contain a later queued total. Seed this · [reviewed contract](#b0067) |
| [B0068 · 628–638](../../../../../src/runtime/weighted.cpp#L628) | Callable definition: void drain() | calls size, std::move, metric, at; guard require(output.metrics.events_applied==output.metrics.events_enqueued,"weighted_contract","weighted…; 1 loop sites; source comment (unverified): // Moving first keeps the current event valid if propagation grows queue. · [reviewed contract](#b0068) |
| [B0069 · 639–641](../../../../../src/runtime/weighted.cpp#L639) | declares namespace scope. |  · [reviewed contract](#b0069) |
| [B0070 · 642–674](../../../../../src/runtime/weighted.cpp#L642) | Callable definition: template&lt;class Owner, class Cursor&gt; Snapshot capture_weighted(Owner& owner, std::uint64_t sequence, bool tentative, SnapshotLimit… | calls account, statistics, summary, reserve; guard require(rows&lt;limits.rows,"snapshot_limit","weighted snapshot row limit exceeded");++rows;; returns result; growth emplace_back, push_back, reserve; 4 loop sites; source comment (unverified): // Explicit bounded copy, not an automatic update side effect or import proof. · [reviewed contract](#b0070) |
| [B0071 · 675–676](../../../../../src/runtime/weighted.cpp#L675) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0071) |
| [B0072 · 677–681](../../../../../src/runtime/weighted.cpp#L677) | Callable definition: WeightedRuntime WeightedRuntime::create_into(const resource::MemoryAccount& account, const PhysicalPlan& shape, weighted::Options… | calls resource::MemoryFailure, WeightedRuntime, Impl::create; returns WeightedRuntime(Impl::create(shape,options,account)) · [reviewed contract](#b0072) |
| [B0073 · 682–686](../../../../../src/runtime/weighted.cpp#L682) | Callable definition: WeightedRuntime WeightedRuntime::create_into(const resource::MemoryAccount& account, const CompiledProgram& shape, weighted::Opti… | calls resource::MemoryFailure, WeightedRuntime, Impl::create; returns WeightedRuntime(Impl::create(shape,options,account)) · [reviewed contract](#b0073) |
| [B0074 · 687–687](../../../../../src/runtime/weighted.cpp#L687) | Callable definition: WeightedRuntime::WeightedRuntime(PhysicalPlan shape, weighted::Options options):impl_(Impl::create(shape,options)) | calls impl_, Impl::create · [reviewed contract](#b0074) |
| [B0075 · 688–688](../../../../../src/runtime/weighted.cpp#L688) | Callable definition: WeightedRuntime::WeightedRuntime(CompiledProgram shape, weighted::Options options):impl_(Impl::create(shape,options)) | calls impl_, Impl::create · [reviewed contract](#b0075) |
| [B0076 · 689–691](../../../../../src/runtime/weighted.cpp#L689) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0076) |
| [B0077 · 692–692](../../../../../src/runtime/weighted.cpp#L692) | Callable definition: WeightedRuntime::Impl& WeightedRuntime::impl() const | calls require, bool; guard WeightedRuntime::Impl& WeightedRuntime::impl() const {require(bool(impl_),"invalid_runtime","weight…; returns *impl_ · [reviewed contract](#b0077) |
| [B0078 · 693–693](../../../../../src/runtime/weighted.cpp#L693) | Callable definition: const CompiledProgram& WeightedRuntime::structural_program() const & | calls impl; returns impl().program · [reviewed contract](#b0078) |
| [B0079 · 694–694](../../../../../src/runtime/weighted.cpp#L694) | Callable definition: const weighted::Binding& WeightedRuntime::binding() const & | calls impl; returns impl().binding · [reviewed contract](#b0079) |
| [B0080 · 695–695](../../../../../src/runtime/weighted.cpp#L695) | Callable definition: const weighted::Options& WeightedRuntime::options() const | calls impl; returns impl().options · [reviewed contract](#b0080) |
| [B0081 · 696–696](../../../../../src/runtime/weighted.cpp#L696) | Callable definition: std::uint64_t WeightedRuntime::owner() const | calls impl, account, statistics; returns impl().account().statistics().owner · [reviewed contract](#b0081) |
| [B0082 · 697–697](../../../../../src/runtime/weighted.cpp#L697) | Callable definition: std::uint64_t WeightedRuntime::sequence() const | calls impl; returns impl().sequence · [reviewed contract](#b0082) |
| [B0083 · 698–698](../../../../../src/runtime/weighted.cpp#L698) | Callable definition: bool WeightedRuntime::ready() const | calls impl; returns !d.updating && d.readers==0 · [reviewed contract](#b0083) |
| [B0084 · 699–699](../../../../../src/runtime/weighted.cpp#L699) | Callable definition: Multiplicity WeightedRuntime::root_weight() const | calls impl, readable, summary; returns d.summary() · [reviewed contract](#b0084) |
| [B0085 · 700–700](../../../../../src/runtime/weighted.cpp#L700) | Callable definition: std::optional&lt;Attempt&gt; WeightedRuntime::last_attempt() const | calls impl; returns impl().last · [reviewed contract](#b0085) |
| [B0086 · 701–701](../../../../../src/runtime/weighted.cpp#L701) | Callable definition: resource::MemoryStatistics WeightedRuntime::accounted_memory_statistics() const | calls impl, account, statistics; returns impl().account().statistics() · [reviewed contract](#b0086) |
| [B0087 · 702–704](../../../../../src/runtime/weighted.cpp#L702) | Callable definition: WeightedRuntime::PendingEpoch WeightedRuntime::begin_epoch(std::uint64_t sequence) | calls begin_epoch; returns begin_epoch(sequence,DeltaCapture::disabled) · [reviewed contract](#b0087) |
| [B0088 · 705–712](../../../../../src/runtime/weighted.cpp#L705) | Callable definition: WeightedRuntime::PendingEpoch WeightedRuntime::begin_epoch(std::uint64_t sequence, DeltaCapture capture) | calls impl, readable, require, operation; guard require(d.readers==0,"runtime_busy","a weighted result cursor has leased the epoch");; returns PendingEpoch(std::move(data)); growth make_accounted_unique · [reviewed contract](#b0088) |
| [B0089 · 713–715](../../../../../src/runtime/weighted.cpp#L713) | Callable definition: Epoch WeightedRuntime::apply(const Update& update) | calls begin_epoch, stage, commit; returns pending.commit() · [reviewed contract](#b0089) |
| [B0090 · 716–719](../../../../../src/runtime/weighted.cpp#L716) | Callable definition: Snapshot WeightedRuntime::snapshot(SnapshotLimits limits) const | calls impl, readable, operation, capture_weighted; returns capture_weighted(d,d.sequence,false,limits,\[&\](RelationId id){return d.storage.table(id).live(d.all… · [reviewed contract](#b0090) |
| [B0091 · 720–720](../../../../../src/runtime/weighted.cpp#L720) | Callable definition: WeightedRuntime::PendingEpoch::PendingEpoch(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0091) |
| [B0092 · 721–723](../../../../../src/runtime/weighted.cpp#L721) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0092) |
| [B0093 · 724–724](../../../../../src/runtime/weighted.cpp#L724) | Callable definition: bool WeightedRuntime::PendingEpoch::active() const noexcept | calls bool; returns data_ && bool(data_-&gt;owner) · [reviewed contract](#b0093) |
| [B0094 · 725–725](../../../../../src/runtime/weighted.cpp#L725) | Callable definition: void WeightedRuntime::PendingEpoch::rollback() noexcept | calls rollback · [reviewed contract](#b0094) |
| [B0095 · 726–729](../../../../../src/runtime/weighted.cpp#L726) | Callable definition: bool WeightedRuntime::PendingEpoch::stage(const Replacement& replacement) | calls stage_native, storage::TupleValuesView::borrow; returns stage_native(replacement.node,storage::TupleValuesView::borrow(replacement.values), · [reviewed contract](#b0095) |
| [B0096 · 730–733](../../../../../src/runtime/weighted.cpp#L730) | Callable definition: bool WeightedRuntime::PendingEpoch::stage_contribution(NodeId node, storage::TupleValuesView values, Multiplicity before, Multipl… | calls stage_native, std::move; returns stage_native(node,std::move(values),before,after,true) · [reviewed contract](#b0096) |
| [B0097 · 734–748](../../../../../src/runtime/weighted.cpp#L734) | Callable definition: bool WeightedRuntime::PendingEpoch::stage_native(NodeId id, storage::TupleValuesView values, Multiplicity old, Multiplicity next,… | calls require, active, operation, nodes; guard require(active(),"invalid_epoch","weighted epoch is closed");; returns data_-&gt;output.metrics.native_changes!=before; source comment (unverified): // The sole abort boundary; preserve error type. · [reviewed contract](#b0097) |
| [B0098 · 749–753](../../../../../src/runtime/weighted.cpp#L749) | Callable definition: std::optional&lt;std::span&lt;const BagDelta&gt;&gt; WeightedRuntime::PendingEpoch::bag_delta_preview() const | calls require, active; guard require(active(),"invalid_epoch","weighted epoch is closed");; returns std::nullopt; std::span&lt;const BagDelta&gt;(data_-&gt;deltas-&gt;rows) · [reviewed contract](#b0098) |
| [B0099 · 754–758](../../../../../src/runtime/weighted.cpp#L754) | Callable definition: std::optional&lt;std::span&lt;const BagDelta&gt;&gt; WeightedRuntime::PendingEpoch::support_delta_preview() const | calls require, active; guard require(active(),"invalid_epoch","weighted epoch is closed");; returns std::nullopt; std::span&lt;const BagDelta&gt;(data_-&gt;deltas-&gt;rows) · [reviewed contract](#b0099) |
| [B0100 · 759–761](../../../../../src/runtime/weighted.cpp#L759) | Callable definition: std::span&lt;const BagDelta&gt; weighted::SupportDeltas::entries() const & | calls require, bool; guard require(bool(data_),"support_capture_disabled","weighted support capture was disabled");return data…; returns data_-&gt;rows · [reviewed contract](#b0100) |
| [B0101 · 762–764](../../../../../src/runtime/weighted.cpp#L762) | Callable definition: const BagDeltaMetrics& weighted::SupportDeltas::metrics() const & | calls require, bool; guard require(bool(data_),"support_capture_disabled","weighted support capture was disabled");return data…; returns data_-&gt;metrics · [reviewed contract](#b0101) |
| [B0102 · 765–767](../../../../../src/runtime/weighted.cpp#L765) | Callable definition: std::span&lt;const BagDelta&gt; weighted::BagDeltas::entries() const & | calls require, bool; guard require(bool(data_),"delta_capture_disabled","weighted delta capture was disabled");return data_-&gt;r…; returns data_-&gt;rows · [reviewed contract](#b0102) |
| [B0103 · 768–770](../../../../../src/runtime/weighted.cpp#L768) | Callable definition: const BagDeltaMetrics& weighted::BagDeltas::metrics() const & | calls require, bool; guard require(bool(data_),"delta_capture_disabled","weighted delta capture was disabled");return data_-&gt;m…; returns data_-&gt;metrics · [reviewed contract](#b0103) |
| [B0104 · 771–771](../../../../../src/runtime/weighted.cpp#L771) | Callable definition: const Epoch& WeightedRuntime::PendingEpoch::preview() const | calls require, active; guard const Epoch& WeightedRuntime::PendingEpoch::preview() const {require(active(),"invalid_epoch","weig…; returns data_-&gt;output · [reviewed contract](#b0104) |
| [B0105 · 772–776](../../../../../src/runtime/weighted.cpp#L772) | Callable definition: Snapshot WeightedRuntime::PendingEpoch::snapshot(SnapshotLimits limits) const | calls require, active, operation, capture_weighted; guard require(active(),"invalid_epoch","weighted epoch is closed");auto& d=data_-&gt;active();detail::Storag…; returns data_-&gt;live(id); result · [reviewed contract](#b0105) |
| [B0106 · 777–795](../../../../../src/runtime/weighted.cpp#L777) | Callable definition: Epoch WeightedRuntime::PendingEpoch::commit() | calls require, active, sample_grant, reset; guard require(active(),"invalid_epoch","weighted epoch is closed");auto& d=data_-&gt;active();; returns result; 1 loop sites; source comment (unverified): // All arithmetic/allocation/draining finished in stage(). Publication and · [reviewed contract](#b0106) |
| [B0107 · 796–796](../../../../../src/runtime/weighted.cpp#L796) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0107) |

## B0001

[Lines 1–19](../../../../../src/runtime/weighted.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:83d56b691df197c0c78c7ba1cbec778af742927cb087ffd534196a9a337de450
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect numeric maintenance implementation to its private state and exact binding helper. |
| inputs / outputs | Private maintenance state, optional delta consolidation definition and exact binding helper. |
| invariants | Full subtree messages differ from P1 projected output factors; no Boolean update bound is claimed. |
| ownership | All mutable/query-retained state uses selected original/receiving account. |
| failure | Compile-time setup adds no runtime exception mechanism. |
| cost | No initialization registry or runtime overhead. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 supplies aggregation context; these ownership, adapter and work contracts are local engineering, not a theorem of the paper](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

```text
#include "weighted_delta_detail.hpp" #include "sql_cold_rebuild.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Make the closed cold bridge visible only to the weighted runtime implementation. |
| inputs / outputs | Source-private include provides bridge definitions for the real weighted owner. |
| invariants | Normal weighted logic and public headers stay unchanged. |
| ownership | No owner from include. |
| failure | Compile-time dependency only. |
| cost | No runtime cost. |
| Design | [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../src/runtime/sql_cold_rebuild.hpp) |

## B0002

[Lines 20–28](../../../../../src/runtime/weighted.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L28:sha256:03be1f3a3ae43827f3c672b69d3b1c07268a4ae5a2315ebea32394a451588ec1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a live record only for explicit snapshot or change diagnostics. |
| inputs / outputs | Account plus source record to independently owned immutable-facing Record. |
| invariants | Copy all scalar values and cached child factors before publication. |
| ownership | Control block and child array use original account with capture attribution. |
| failure | Allocation rejection propagates; live record is unchanged. |
| cost | O(child arity), explicit diagnostic path only. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0003

[Lines 29–42](../../../../../src/runtime/weighted.cpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L42:sha256:58710598cdf194ed1534cb6a7a6ac96c57a640e59f81b50f7515dd85f6bfe942
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash structural shape, weighted semantics version and configured numeric limit. |
| inputs / outputs | Compiled program and uint64 limit to fixed-size Binding. |
| invariants | Domain separation prevents accidental reuse of set execution identity. |
| ownership | Stack buffer only; result belongs to owner. |
| failure | Invalid shape hash or fixed encoding is a contract failure. |
| cost | Fixed upper-bound input, no dynamic encoding buffer. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0004

[Lines 43–44](../../../../../src/runtime/weighted.cpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L43-L44:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/weighted.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/weighted.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/weighted.cpp\` at its lexical source position in src/runtime/weighted.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/weighted.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 45–50](../../../../../src/runtime/weighted.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L50:sha256:41e875383291c10ee7d96a507a165ee3bfd0dda5e2b8a1d20bba2ff5d70dd7c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the numeric metadata containers for one compiled node. |
| inputs / outputs | Original account, node ID and child arity produce empty row/message/factor maps and a zeroed child-to-edge array. |
| invariants | One array entry per compiled child; three maps have distinct roles and start empty. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | Construction failure destroys already prepared members; no runtime is published. |
| cost | O(child arity) array initialization; empty maps allocate no payload nodes. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0006

[Lines 51–53](../../../../../src/runtime/weighted.cpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L51-L53:sha256:1e3776e0e46363bd86a8a2e12850abd973e2e00cdd5ac2c4c797268ebe93a8bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Classify an extracted numeric map node as active or retained. |
| inputs / outputs | An interior pointer into this node account plus the desired allocation lifetime updates accounting metadata. |
| invariants | The pointed allocation still exists, and its support-node attribution matches this node. |
| ownership | No transfer or copy of the map value; only its original allocation ledger changes. |
| failure | An invalid internal pointer/attribution is a contract failure, not an input recovery path. |
| cost | Original account lookup may scan outstanding allocations; not an O(1) map operation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0008

[Lines 55–57](../../../../../src/runtime/weighted.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L55-L57:sha256:519570a869f98a1328a4e2792e38e3b30fe0645ffd496d62c2c7df6fbe9c952c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund one child-weight cache for a full row or explicit diagnostic copy. |
| inputs / outputs | Account, attribution, child arity and memory purpose produce zeroed child weights and inline default scalars. |
| invariants | Cache arity matches the compiled node; the caller sets local/subtree/factor values before publication. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | Allocation failure constructs no complete RecordValue. |
| cost | O(child arity) requested bytes and initialization; no allocation for zero arity. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0009

[Lines 58–60](../../../../../src/runtime/weighted.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L60:sha256:ffca0d5e57f35c159e9c8a09fc0a59e9e2956ab2b3de6475aec8768515c0a198
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare optional owning change/event capture for one epoch. |
| inputs / outputs | Original account and epoch sequence produce empty funded change and event vectors in pending phase. |
| invariants | This is an inspection history, not the compact inverse log or a durable recovery journal. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | Construction failure leaves no captured journal published. |
| cost | Fixed empty vector owners; actual append/copy/pin costs are paid only when capture is enabled. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0010

[Lines 61–64](../../../../../src/runtime/weighted.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L64:sha256:95ccc0ed7a933acb1e59ae51608e274e805914fe9f03a9d80860115fb80caa45
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owning snapshot containers for one node. |
| inputs / outputs | Account and node ID produce empty row, full-message and visible-factor output vectors. |
| invariants | Full separator messages and projected factor keys remain distinct. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | A partial snapshot is destroyed on failure. |
| cost | Fixed empty containers; reserve/row/deep-value costs belong to explicit capture. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0011

[Lines 65–66](../../../../../src/runtime/weighted.cpp#L65); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L65-L66:sha256:59f1409811706a831b2ceb745fd5cd09c689a16165865a88477756cdb0406fb2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain separate full-message and local-output-factor metadata. |
| inputs / outputs | Guidance for Impl construction. |
| invariants | Do not multiply an enumerated child both through its parent factor and its own result factor. |
| ownership | Comment only; maps use the runtime account. |
| failure | Not an external proof or import authority. |
| cost | No executable work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 supplies aggregation context; these ownership, adapter and work contracts are local engineering, not a theorem of the paper](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0012

[Lines 67–68](../../../../../src/runtime/weighted.cpp#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L68:sha256:7ed6d97ad5927299746ad753b6aff1b7cd993b4f49a745771cc627e6d1b30766
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep ordinary WeightedRuntime creation at sequence zero with its original ordinary storage allowance. |
| inputs / outputs | The public normal constructor delegates to the shared Impl initializer with \`shape.make_storage(compact_storage_work(work))\` and base sequence zero. |
| invariants | Normal storage still obeys immutable plan per_operation limits; only the private cold bridge selects the second prebuilt-storage constructor and C−1 base for a fresh unpublished owner. |
| ownership | The Impl owns the same program/context/storage/maps as before; the initial sequence is an inline field value already present in the record. |
| failure | Delegated construction, annotation, storage or allocation errors unwind the same unpublished owner. |
| cost | Normal table materialization and common metadata setup remain constructor costs; no update-path admission or record field was added. |
| Design | [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [src/runtime/weighted_detail.hpp](../../../../../src/runtime/weighted_detail.hpp), [docs/weighted_messages.md §Ownership, transaction and identity](../../../../weighted_messages.md) |

## B0013

[Lines 69–102](../../../../../src/runtime/weighted.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L102:sha256:b5e83e0272973c8970a5993a4c7ed200069e52bd0b216c1a35850babedaedb88
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize common weighted state from prebuilt cold tables and a private base sequence. |
| inputs / outputs | Actual CompiledProgram, original options/context, pre-materialized AccountedPlanStorage and initial_sequence initialize one Impl. |
| invariants | Same annotation/direct-CQ/root checks and node/factor maps as normal; only fresh unpublished cold owner can begin at C−1 before its one seed. |
| ownership | Moves authentic program/context/tables into shared Impl; all retained state uses its account. |
| failure | Backend/contract/work/allocation failure aborts unpublished creation. |
| cost | Same node/edge/factor-slot construction as normal; base sequence is an inline scalar and not an operational bypass port. |
| Design | [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [src/runtime/weighted_detail.hpp](../../../../../src/runtime/weighted_detail.hpp), [docs/weighted_messages.md §Ownership, transaction and identity](../../../../weighted_messages.md) |

## B0014

[Lines 103–103](../../../../../src/runtime/weighted.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L103:sha256:edd4ad9c542da886e55d9704f1233a88d6ebd672f64c652c5cb6718f59b98bdd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the single admitted native memory account. |
| inputs / outputs | A live Impl returns its context account by const reference. |
| invariants | Context lifetime covers this Impl. |
| ownership | Borrowed reference; it does not create an account or retain an extra owner. |
| failure | Requires a valid Impl/context. |
| cost | O(1), no allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0015

[Lines 104–104](../../../../../src/runtime/weighted.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L104-L104:sha256:206bfc0d30d9a1068404a1f3363163f00651df8853c75d8e27fc0f093387e428
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Access the currently activated native storage allowance. |
| inputs / outputs | The Impl context returns the allowance pointer used by this storage operation. |
| invariants | Storage operations activate the appropriate retained lease before accessing indexed storage. |
| ownership | Borrowed allowance; this accessor creates no refill or lease. |
| failure | Requires the storage-context operation contract. |
| cost | O(1), no allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0016

[Lines 105–105](../../../../../src/runtime/weighted.cpp#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L105:sha256:82b087408c546dc44f729dc3851dc3061b3db9baaf73d78010d20730f4068e13
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject committed reads while an epoch is private. |
| inputs / outputs | Inspect the updating flag; return normally only for committed state. |
| invariants | Active result readers are compatible with committed reads; they are excluded by begin_epoch instead. |
| ownership | Read-only inline flag access. |
| failure | Raises runtime_busy for a private epoch, without changing it. |
| cost | O(1); success allocates nothing. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0017

[Lines 106–111](../../../../../src/runtime/weighted.cpp#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L111:sha256:49b5461bd3c1a73b44806e587bb9c7219d8b74380d0ba1176bfdd63e50ecbfb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the complete witness count without enumerating projected output. |
| inputs / outputs | Constant routes return one/zero; a tree returns its only empty-key root message or zero. |
| invariants | Checked tree root has empty parent separator, hence at most one root-message key. |
| ownership | Copies one inline multiplicity; no table/snapshot/result cursor is created. |
| failure | Noexcept under established root/message invariants. |
| cost | O(1), including ordered-map begin; no lookup by output tuple. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0018

[Lines 112–126](../../../../../src/runtime/weighted.cpp#L112); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L112-L126:sha256:d0249516cbdb6699d54075b536a568f23e4bf67b7be23be87b4c5ad837d9d05c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import a checked direct-CQ shape into the selected weighted allocation authority. |
| inputs / outputs | PhysicalPlan/CompiledProgram and options, optionally an internal receiver, produce Impl. A nonempty receiver supplies the true cap; the default internal argument selects standalone account creation. |
| invariants | Public create_into rejects empty accounts before this helper. Reject normalized SQL and invalid multiplicity limit before import. One context/outer indexed admission grant funds freeze and storage initialization. |
| ownership | All new retained metadata/state uses the selected account. Foreign source statistics remain unchanged; deliberately shared source/receiver ownership is valid and visible in that one account. |
| failure | No runtime publishes on failure. RAII releases only new partial state; existing account residents survive. Public empty-receiver rejection is fixed MemoryFailure(contract), with no fallback or allocation. |
| cost | Same account/context/grant/freeze/Impl admission structure as before, plus a fixed statistics copy for the cap. Import cost depends on plan metadata and actual native capacities; no new hot-loop allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0020

[Lines 128–141](../../../../../src/runtime/weighted.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L128-L141:sha256:641b12b8ec86ed1b931d68fec81a7f7953ce9aa69b2e08cbbb3cdb162a6ee8d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the genuine weighted runtime over actual lower_tree output under one cold context. |
| inputs / outputs | Receiver, actual PhysicalPlan, normal multiplicity/options, cold StorageWorkContext and private base -&gt; CompiledProgram, ColdRebuild storage tables, one Impl. |
| invariants | Require same account/context and backend match; preserve per-table and multiplicity domain; indexed lease is borrowed from outer StorageOperation; no live setter or generic mode flag. |
| ownership | Impl owns storage/program/context; cold context outlives the active outer operation only until explicit close. |
| failure | Account/owner/backend/policy/storage/work failures discard unpublished Impl. |
| cost | Native metadata/table/index work charges the single indexed root for indexed plans; ordered plan has no synthetic indexed charge. |
| Design | [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [docs/memory_accounts.md §Accounted compiled-plan storage binding](../../../../memory_accounts.md) |

## B0021

[Lines 142–153](../../../../../src/runtime/weighted.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L142-L153:sha256:35e763cf331df6dff6b74460c08db45f0e63e8d52e9e4356953c56dfd0aa2771
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private cold weighted grant and install a validated normal context. |
| inputs / outputs | Closed runtime/options -&gt; require no update/readers/active operation, match multiplicity binding, create normal storage_context with actual receiver limit, validate it, then replace options/context. |
| invariants | No change to immutable cold Context.limit; no journal/cursor may retain old allowance; tables retain no work grant. It does not reset plan identity. |
| ownership | Runtime retains the fresh normal context; old cold context is released after local references leave. |
| failure | Any precondition or fresh context allocation/validation failure occurs before new context is assigned. |
| cost | One context creation/validation at close; no journal scan or row operation. |
| Design | [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/weighted_messages.md §Ownership, transaction and identity](../../../../weighted_messages.md) |

## B0022

[Lines 154–164](../../../../../src/runtime/weighted.cpp#L154); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L154-L164:sha256:4ffca535d01597c5ec69d18fb1d37a35923449d5ac60cca33ffb847ed1543e40
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the concrete prepared-epoch owner/declarations and add only a fixed capture policy scalar in this region. |
| inputs / outputs | Existing private owner/lease/journal/output members plus DeltaCapture in; no callable execution or new public graph out. |
| invariants | The numeric Epoch output is unchanged in meaning; support mode is separate opt-in metadata, not numeric count state. |
| ownership | All existing owning members keep their prior lifetime/order; the new enum owns no allocation. |
| failure | Declaration/scope region adds no failure, catch, retry or rollback operation. |
| cost | Fixed scalar storage only; no work proportional to source or result size in declarations. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0023

[Lines 165–165](../../../../../src/runtime/weighted.cpp#L165); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L165-L165:sha256:ae327152a42ccacb2a4ae547b31ff256a727b1059a57155d319f239f1f12b988
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish absolute native totals, adapter shares and propagated child totals internally. |
| inputs / outputs | Three private scoped-enum tags route the existing FIFO event payload. |
| invariants | Only native_contribution invokes checked normalization; public EventKind remains two-valued. |
| ownership | Inline tag, no source ID or polymorphic object. |
| failure | Private malformed tags are unreachable through the public staging ports. |
| cost | Scoped enums retain int underlying representation; fixed dispatch cost. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0024

[Lines 166–166](../../../../../src/runtime/weighted.cpp#L166); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L166-L166:sha256:766bdc2167be99bf2a603b83872eac757483ab0a0367890e7c9fe1242d2b6d59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a target build that would enlarge the existing event kind representation. |
| inputs / outputs | Compare private PendingKind and public predecessor EventKind sizes at compile time. |
| invariants | Both are scoped enums with default int underlying type. All other Pending fields remain identical. |
| ownership | No object storage or ownership. |
| failure | A representation mismatch is a compile error, not a runtime fallback. |
| cost | Zero runtime instructions; source field-list proof accompanies this assertion. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0025

[Lines 167–174](../../../../../src/runtime/weighted.cpp#L167); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L167-L174:sha256:2c7d2d30926a9303fb4ae310496a01344dacbbe04552fe4510dcd1f76035e87f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one causal numeric FIFO event until application. |
| inputs / outputs | Private kind, target, optional edge/capture index, owning key, two multiplicities and causal IDs. Absolute/child weights are totals; contribution weights are shares until native normalization. |
| invariants | Numeric same-key changes remain FIFO. Only the private tag changes; the same fixed-underlying-int enum size is asserted. No source-identity slot, second count map or new per-event field. |
| ownership | Queue owns one original-account key and inline scalars. Captures retain separate diagnostic values only when requested. |
| failure | Queue/key allocation failure is handled by the enclosing stage abort. |
| cost | Same field layout/payload shape as the predecessor after replacing EventKind with PendingKind. Contribution normalization mutates existing scalars; no extra state allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0026

[Lines 175–175](../../../../../src/runtime/weighted.cpp#L175); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L175-L175:sha256:8045cffc2f1f4449d262104d5112e7127dbaa7e1f73eb9821d8304a783beb17b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discriminate the six exact metadata inverses. |
| inputs / outputs | Row/counter insertion, scalar change or detached erasure selects rollback behavior. |
| invariants | Each prepared Undo is interpreted only by its tag; counters also retain the exact target message/factor map. |
| ownership | Inline enum inside an original-account inverse vector. |
| failure | Internal invalid tag/state is a contract violation. |
| cost | Fixed scalar tag; no exception-dispatch or polymorphic inverse objects. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0027

[Lines 176–189](../../../../../src/runtime/weighted.cpp#L176); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L176-L189:sha256:1ae9594cf4ec768931e8252e528fea8847727d0f138da6651289c762683a98fb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record enough old state to reverse one numeric or membership mutation. |
| inputs / outputs | Action, stable node/map pointer, tuple ID, old local/subtree/factor scalars and one child slot, or extracted row/counter nodes. |
| invariants | Prepare before mutation and reverse in order. Counter inverses target the exact message/factor map. Admitted node storage never relocates during execution. |
| ownership | Amortized vector owns entries; extracted node retains original child array. |
| failure | Vector growth may fail before mutation; rollback allocates nothing. |
| cost | Constant payload per numeric edit, no per-entry heap object or full child-array copy. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0028

[Lines 190–198](../../../../../src/runtime/weighted.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L198:sha256:07edb37b193fb9337e6c9c34ef675b60459a56fe8942e0f0a9ca4aaa951ef200
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the existing inverse, touched-table and FIFO containers for one private epoch. |
| inputs / outputs | Three original-account vectors, queue head and current causal ID. |
| invariants | No added count/contribution/source map; undo is funded before mutation; FIFO drains after each stage. |
| ownership | Data owns vectors and their original native key/journal/node resources. |
| failure | Growth failure reaches the one stage abort boundary; rollback uses prepared state. |
| cost | Amortized vector storage/work; touched-table lookup and queue capacity remain explicit. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

```text
  struct DeltaWalk {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep optional traversal scratch private to one pending epoch. |
| inputs / outputs | Checked visible program and current factor maps; forced anchor may be absent from the before table. |
| invariants | All borrowed readers close before factor mutation or rollback. |
| ownership | Epoch owns account-backed frames/output descriptors; selected tuples borrow current table/journal payloads. |
| failure | Construction or traversal failure reaches token setup or the existing stage abort. |
| cost | O(visible steps + output arity) scratch, plus temporary projected separator keys; conservative prefix visits remain. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0029

[Lines 199–204](../../../../../src/runtime/weighted.cpp#L199); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L199-L204:sha256:82ffbc79b8d9eee2f6156f6f830c374861cc30f640f5662edee5a32bfee3f529
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track one selected step without copying a table row. |
| inputs / outputs | Optional private cursor/key, borrowed selected tuple and its scalar factor. |
| invariants | Forced anchor is selected once per compatible prefix; ordinary steps require positive factor membership. |
| ownership | Cursor/key are owned; selected pointer borrows the table journal or anchor for this walk. |
| failure | Frame teardown is nonthrowing. |
| cost | Fixed descriptor per checked visible step. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0030

[Lines 205–212](../../../../../src/runtime/weighted.cpp#L205); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L205-L212:sha256:389a478b8550040956dc3d3f156d130e6b199020d9f169d04d5f5caeed640071
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted.cpp: this range contains member/state declarations Member/state declarations in this range include \`Data& epoch\`; \`weighted::BagDeltas::Data& bag\`; \`Vector&lt;Frame&gt; frames\`; \`Vector&lt;storage::ScalarView&gt; row\`; \`std::size_t position=0,anchor_step=0\`; \`bool resume=false\`; \`const storage::AccountedTuple* anchor=nullptr\`. |
| inputs / outputs | This span declares/carries these members or local values: \`Data& epoch\`; \`weighted::BagDeltas::Data& bag\`; \`Vector&lt;Frame&gt; frames\`; \`Vector&lt;storage::ScalarView&gt; row\`; \`std::size_t position=0,anchor_step=0\`; \`bool resume=false\`; \`const storage::AccountedTuple* anchor=nullptr\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Vector is the runtime account-backed vector alias; the enclosing constructor selects the account and purpose. Span/view members borrow their source; retain the source owner for the full use window. Accounted row/tuple values own compact payload under their associated account. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | Visible container/member storage can allocate on construction or growth according to its allocator and account binding; method traversal cost occurs where callers use it. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0031

[Lines 213–220](../../../../../src/runtime/weighted.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L213-L220:sha256:ad44cbaca6bed2224b1d4c48d71d214d7cb8b863b829c04a6e4d89c0849813a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund frames and output capacity once for enabled capture. |
| inputs / outputs | One pending Data; prepare one empty frame per compiled step and reserve output cells. |
| invariants | Uses the original account and cumulative work; initialization/failure cleanup units are prefunded. |
| ownership | Owning scratch dies before native inverse work. |
| failure | Allocation/admission failure occurs before publication. |
| cost | O(visible steps) initialization and actual capacity allocations; no per-row frame allocation. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0032

[Lines 221–225](../../../../../src/runtime/weighted.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L221-L225:sha256:51d196c299396f590915ec2097f2571bf657c75c5db87ccdeba40b95e43be7ab
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project a canonical separator key with explicit copy admission. |
| inputs / outputs | Compiled AccountedProjection and source tuple produce an owned receiving-account key. |
| invariants | Charge projected fields/string bytes before copying them. |
| ownership | Temporary key owns its layout/payload under the original account. |
| failure | Projection/allocation/work errors propagate to the sole stage abort. |
| cost | Actual projected fields/bytes plus layout copy cost; no legacy Row export. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0033

[Lines 226–250](../../../../../src/runtime/weighted.cpp#L226); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L226-L250:sha256:d62576572a7c391d42ecf47dfb71e7691ff5caf4be0251d9c7a2215a708d89ed
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the forced changed key or advance a current private visible bucket. |
| inputs / outputs | Step and already selected parent; store tuple/factor or signal exhaustion. |
| invariants | Anchor separator must match; other rows read positive current factors. Multiplication is deferred until assignment completion. |
| ownership | Cursors route to existing journals or committed tables using the retained allowance; no fresh writer/reader/grant. |
| failure | Storage, projection, work or invariant errors abort the existing pending token. |
| cost | Actual bucket/live advances, selected rows and factor reads; earlier unrelated prefixes may be visited. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0034

[Lines 251–251](../../../../../src/runtime/weighted.cpp#L251); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L251-L251:sha256:929c1f7c0c5cd7164676a42c4c7eefabf4597765e59eb302d48cd559a5715547
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release one exhausted private traversal frame. |
| inputs / outputs | Reset cursor, projected key and selected borrower. |
| invariants | Cleanup precedes changing or undoing factors. |
| ownership | Destroys only owned cursor/key handles. |
| failure | Nonthrowing; open/setup charges prefund cleanup. |
| cost | Fixed frame cleanup plus native cursor/key deallocation bookkeeping. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0035

[Lines 252–252](../../../../../src/runtime/weighted.cpp#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L252-L252:sha256:50cace9be2fd20f0d5b24ad76409807499a6d962004bdcfdbbc02cb282cfe893
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one cell from the current complete assignment. |
| inputs / outputs | Checked compiled slot yields a borrowed ScalarView. |
| invariants | Caller has selected the referenced frame and valid field. |
| ownership | Returned string view borrows that selected payload. |
| failure | No allocating conversion or local error translation. |
| cost | Fixed descriptor read; no payload copy. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0036

[Lines 253–289](../../../../../src/runtime/weighted.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L289:sha256:0ad1ace20ac0ebd439842d0d274ba4f598dd26f3949b182e672b09e4f4e5a084
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture exact numeric bag differences or unit DISTINCT support changes at the genuine pre-publication visible-factor hook. |
| inputs / outputs | Changed visible key and numeric factor before/after in; current-epoch consolidated encoded output facts out. |
| invariants | Support mode skips only equal zero/nonzero states and emits unit changes through compatible positive factor assignments; numeric mode retains magnitude products. Per-assignment Boolean support differences telescope across private stages; native arithmetic/root totals are unchanged. |
| ownership | Reuse the original token/account/grant, existing anchor-walk scratch and transient accumulator; selected table rows borrow active private journals. No result graph or native-state copy is retained. |
| failure | Any traversal/encoding/arithmetic/work/allocation failure reaches the existing stage abort boundary and rolls back; no new catch/retry is introduced. |
| cost | Support avoids numeric factor multiplications and all positive-to-positive capture walks. Charge actual visited assignments, keys/strings, map comparisons/growth and cleanup; intermediate work may exceed final net changes. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0037

[Lines 290–292](../../../../../src/runtime/weighted.cpp#L290); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L290-L292:sha256:73b662c7dbd4186a8d41ca375a3a333868c49a12852b99bf2b3e05c79bf16ff0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted.cpp: closes \`struct DeltaWalk\` Member/state declarations in this range include \`std::shared_ptr&lt;weighted::BagDeltas::Data&gt; deltas\`; \`resource::AccountedUnique&lt;DeltaWalk&gt; delta_walk\`. |
| inputs / outputs | This span declares/carries these members or local values: \`std::shared_ptr&lt;weighted::BagDeltas::Data&gt; deltas\`; \`resource::AccountedUnique&lt;DeltaWalk&gt; delta_walk\`. Constructor/function input and output shapes remain those written in this same source range. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | AccountedUnique retains one owned object and its account-aware deleter. shared_ptr members retain shared state for the handle lifetime. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0038

[Lines 293–306](../../../../../src/runtime/weighted.cpp#L293); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L293-L306:sha256:8717ea7b5aa01a1e55210dab9b38f5fdd283123f448c79351e413038bea8849a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one native prepared epoch with fixed capture policy and unchanged numeric before/after root totals. |
| inputs / outputs | Genuine owner, next sequence and disabled/numeric/support request in; original-account private journal/token out. |
| invariants | Capture policy is fixed per token; only enabled/support allocate the existing accumulator/walker. Optional diagnostic capture is independent and defaults remain off. |
| ownership | Owner, storage lease, undo and capture buffers retain the original account; no second account or grant refill is created. |
| failure | Construction failure unwinds already-owned RAII members; ordinary stage/rollback behavior remains authoritative. |
| cost | Fixed owner/policy work plus requested O(visible steps/output width) scratch; uncaptured tokens allocate no capture buffers. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0039

[Lines 307–307](../../../../../src/runtime/weighted.cpp#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L307-L307:sha256:37b44536d2ae3dc7217311eee77524236f3aba9c7a2e2efbaaaee0e05697753d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore an abandoned private transaction automatically. |
| inputs / outputs | Destruction invokes idempotent rollback on any still-active owner. |
| invariants | Committed/already rolled-back Data has no active owner and does nothing. |
| ownership | RAII ends all private inverses, keys, journals and the exclusive owner lease. |
| failure | Destructor uses the prepaid nonallocating rollback contract. |
| cost | Actual inverse/table destruction work only; no new snapshot or copy. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0040

[Lines 308–310](../../../../../src/runtime/weighted.cpp#L308); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L308-L310:sha256:59e62b930f30fc7195dc110aeaea42c21892d0a11fe25162d766e15f569924e2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the owner of an open private epoch. |
| inputs / outputs | An active Data returns Impl by reference. |
| invariants | Closed Data cannot be reused as a new transaction. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | Raises invalid_epoch when closed. |
| cost | O(1), no allocation on success. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0041

[Lines 311–317](../../../../../src/runtime/weighted.cpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L311-L317:sha256:d2856323011640bbcdc42dae6ed81310ef184d39562c12a8b204dc2042871b96
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit cumulative abstract maintenance work before executing that category. |
| inputs / outputs | A nonnegative amount increments work only if uint64 and optional configured capacity allow it. |
| invariants | One work total spans every stage; it is not reset by resumption. Work is an explicit category count, not CPU instructions. |
| ownership | Inline epoch scalar only. |
| failure | Raises resource_limit before the increment; the stage boundary aborts the epoch. |
| cost | Fixed scalar checks/addition; no success-path allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0042

[Lines 318–322](../../../../../src/runtime/weighted.cpp#L318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L318-L322:sha256:7f335a83f0d9dfe78bdb3b51417355e4222df91aebc990eafd2ae072aad3a1dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count one performed category of work under the same cumulative budget. |
| inputs / outputs | A reference to a metric-managed category counter and a nonnegative increment; updates total and category once. |
| invariants | Managed counters begin at zero and increment only here, so each is at most cumulative work. Successful charge proves both additions fit; phase summaries, queue peaks and cleanup counts are not passed here. |
| ownership | Borrows inline cursor/epoch counters; no memory allocation on success. |
| failure | Budget or total-overflow rejection happens in charge before the category increment; the existing outer boundary handles rollback or cursor closure. |
| cost | Fixed-width budget/overflow checks once in charge, then two scalar additions; no second category overflow guard. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0043

[Lines 323–328](../../../../../src/runtime/weighted.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L323-L328:sha256:03a46e2f80398bda7dc1c395b51094bcb955aea333692815498f022b25062b69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe native work consumed from the original epoch lease. |
| inputs / outputs | Configured limits minus the retained allowance remainder update five diagnostic counters. |
| invariants | Sampling neither runs storage operations nor resets the remainder. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | Noexcept; no-op if no retained lease. |
| cost | Five fixed subtractions, no traversal or allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0044

[Lines 329–361](../../../../../src/runtime/weighted.cpp#L329); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L329-L361:sha256:8c6f616d96f32971e8c7ab931fb8decde61f7f5790e62b96c55fb4b6437f9342
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore all private metadata, then native tables, then release the exclusive owner. |
| inputs / outputs | Close/drop private delta readers and facts first, then reverse prepared metadata/table journals, retain spent attempt metrics and release exclusive owner. |
| invariants | No arithmetic recomputation/allocation. Diagnostic records are retained attempted history, not undone public transitions; a failing contribution event may contain shares and an execution-entry ordinal. |
| ownership | Detached nodes and table journals fund reversal under original account. |
| failure | Only invariant corruption can terminate a noexcept reversal. |
| cost | Actual delta/frame destruction, undo and table cleanup, including existing lifetime-ledger work; no reconstruction mirror. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0045

[Lines 362–367](../../../../../src/runtime/weighted.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L362-L367:sha256:1eaf5b391992fc9008b78e2ab250e26d1f12062a71debc6289dc42953d934379
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open each mutated native table journal once under the same retained work grant. |
| inputs / outputs | Relation ID to existing/new writable journal. |
| invariants | No per-table fresh native allowance. |
| ownership | Epoch table vector owns journals; journal rollback retains exact native handles. |
| failure | Allocation/work failures abort stage at outer boundary. |
| cost | Linear search in touched-table count; opens on first write. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0046

[Lines 368–371](../../../../../src/runtime/weighted.cpp#L368); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L368-L371:sha256:b43989d8124c292ce035e11da09b08159bfbfccd80e882db5e22f1a89db3225e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read a native table consistently inside the pending epoch. |
| inputs / outputs | Relation ID returns a cursor from its already-open table journal, or from the committed table if untouched. |
| invariants | A touched table must expose its private state rather than stale committed membership. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | Storage/cursor funding failures propagate to the caller; an explicit snapshot failure does not itself call stage rollback. |
| cost | O(number of touched table journals) search plus actual cursor-startup work. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0047

[Lines 372–375](../../../../../src/runtime/weighted.cpp#L372); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L372-L375:sha256:6edb46b320bb2cb201f03a6706785baa55eb42675ebd774b801f122363e70543
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the current private live list without creating a journal. |
| inputs / outputs | Relation resolves an existing table journal or the underlying committed table. |
| invariants | Charge each examined journal route; retain the original indexed allowance. |
| ownership | Returned cursor borrows that selected current table. |
| failure | Native cursor errors propagate to the pending abort. |
| cost | Linear in examined touched journals plus actual live traversal. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0048

[Lines 376–379](../../../../../src/runtime/weighted.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L376-L379:sha256:128b30527dbd4c615bc3d5be165713710a610a7c97b18eabc71ec4fbeaeb2505
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the checked current private separator bucket. |
| inputs / outputs | Relation/index/canonical key produce a current journal or table bucket cursor. |
| invariants | No separate grant, state mirror or read-only writer is created. |
| ownership | Cursor borrows current private membership; caller owns the projected probe key. |
| failure | Storage/key/work failure propagates. |
| cost | Examined journal routes plus native bucket lookup/traversal. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0049

[Lines 380–383](../../../../../src/runtime/weighted.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L380-L383:sha256:687a92b5fc30e7f0f4fe98d308b293a2f1f76508093f031d8aa388a02e36587c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert one previously absent native relation membership. |
| inputs / outputs | Relation ID and an accounted tuple return the newly inserted handle. |
| invariants | A duplicate indicates inconsistent runtime metadata; native journal preparation precedes publication. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | An exception reaches the existing stage abort boundary, which restores the complete private epoch. |
| cost | One charged membership operation plus actual journal/index/hash/deep-field work. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0050

[Lines 384–386](../../../../../src/runtime/weighted.cpp#L384); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L384-L386:sha256:e2a925573eda705874e5f8fa37d9d14cc02a69f2f3f65a6eefa4fb68c6bceee6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one known native relation membership under its table journal. |
| inputs / outputs | Relation ID and handle erase that membership. |
| invariants | Missing membership is an internal weighted_contract failure. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | An exception reaches the existing stage abort boundary, which restores the complete private epoch. |
| cost | One charged membership operation plus actual indexed/ordered erase and prepaid inverse retention. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0051

[Lines 387–390](../../../../../src/runtime/weighted.cpp#L387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L387-L390:sha256:afd812f5a53872d3ce8b84a3ee3b984dc766b6a3218abe1ae106430bbf89a5f5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund and append an inverse before its associated metadata mutation. |
| inputs / outputs | Inverse tag, stable Node reference and tuple ID return a new zero/default-initialized inverse slot. |
| invariants | Caller fills old scalars/map pointer or detached node before it can be needed by rollback. |
| ownership | Original-account inverse vector owns the entry; returned reference is used before another append can reallocate. |
| failure | An exception reaches the existing stage abort boundary, which restores the complete private epoch. |
| cost | Amortized vector append of fixed inverse metadata; no full child-array copy. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0052

[Lines 391–395](../../../../../src/runtime/weighted.cpp#L391); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L391-L395:sha256:43b37a7d282d8bbd162c6320fd8af6c86cad4978488a7079bf572397cfb33e2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Look up the full subtree sum for one compiled child separator. |
| inputs / outputs | Child node ID and typed separator key return its stored sum, or zero when absent. |
| invariants | Native parent-support membership and numeric message map agree. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | An exception reaches the existing stage abort boundary, which restores the complete private epoch. |
| cost | One separator probe, actual backend key lookup and ordered tuple-ID lookup when present; key/deep-field costs remain explicit. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0053

[Lines 396–406](../../../../../src/runtime/weighted.cpp#L396); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L396-L406:sha256:48a02327d98a2da3c4238405fab7815a42aa3d72c72b71e801180f3c306c368c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Populate the child cache of a newly created full row. |
| inputs / outputs | Compiled shape/new RecordValue/full tuple and optional causing slot/value populate all child weights and support count. |
| invariants | The causing slot is seeded with the supplied event value (child creation supplies event.after), avoiding a later table total. Other slots read unchanged sibling messages. Each event is applied once. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | An exception reaches the existing stage abort boundary, which restores the complete private epoch. |
| cost | O(child arity) slots and actual projected-key/message probes; performed on row creation, not every scalar edit. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0054

[Lines 407–417](../../../../../src/runtime/weighted.cpp#L407); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L407-L417:sha256:46d17dae18d849787be10a48fc3549dd7297d9aaec3d2834e3bf4d7d4f238eb6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute a full subtree product without division. |
| inputs / outputs | Cached factors plus desired local, supported count and optional changed child slot. |
| invariants | Return zero before multiplying if any child is missing; all performed products checked. |
| ownership | Borrows live record, returns scalar. |
| failure | Overflow aborts epoch without publishing partial arithmetic. |
| cost | O(child arity) for supported rows; O(1) for known-zero products. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0055

[Lines 418–422](../../../../../src/runtime/weighted.cpp#L418); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L418-L422:sha256:3c80a77f30f0dd86ba318d7f6dd349cd39d0568905273e1d5802ea8a63269e61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an immutable full row-value image for requested inspection. |
| inputs / outputs | Null input returns null; a live record produces an original-account deep child-cache copy. |
| invariants | Callers invoke this only when capture is enabled; live mutable arrays are never shared with callers. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | An exception reaches the existing stage abort boundary, which restores the complete private epoch. |
| cost | O(child arity) copy and allocation, explicitly charged; default numeric updates do not call it. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0056

[Lines 423–437](../../../../../src/runtime/weighted.cpp#L423); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L423-L437:sha256:037e62d7f05de39ab15ded0cfa613e8ab1e3597b7a66c87e7a247bd6eeffd4d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the contribution of one supported full row to its local visible sum. |
| inputs / outputs | Compiled node, old cache, desired local/subtree and optional changed child slot to one exact scalar, using its immutable range in the flat outside-slot array. |
| invariants | Return0 for non-C* or unsupported rows. Otherwise multiply local weight only by outside-C* messages; enumerated child weights are excluded. |
| ownership | Borrows the live cache; creates no array, row or owner. |
| failure | Checked arithmetic/work failure reaches stage rollback before publication. |
| cost | O(outside-child count), with each visited slot/product charged; all-inside nodes take O(1). The flat slot list is compiled once in O(nodes+edges), original-account storage proportional to outside edges, and no extra per-row array. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0057

[Lines 438–444](../../../../../src/runtime/weighted.cpp#L438); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L438-L444:sha256:7608ea90220cb0ba965ee118625ee080e3a21343bc6cbb86f0b4ae32407fc11e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Project one changed row contribution to its compiled visible key. |
| inputs / outputs | Full typed row and old/new contribution to terminal E-key sum replacement. |
| invariants | Equal values skip projection; changed factors require a checked C* visible relation/projection. |
| ownership | Projection key, native table work and metadata undo retain the original account/grant. |
| failure | Key/heap/work/domain failure aborts all private stages. |
| cost | Only unequal values allocate/project a key. Deep visible fields and map lookup have explicit costs. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0058

[Lines 445–450](../../../../../src/runtime/weighted.cpp#L445); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L445-L450:sha256:50c24113d38edfc951ae571e1078dc5a34a1efb187855ef929b09544c7483b4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a typed row transition and retaining tuple pin. |
| inputs / outputs | Node, handle and optional owning before/after images append one RowChange when a capture journal exists. |
| invariants | Null images mean absence, distinct from a present zero-valued candidate; causal ID links this record to its event. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | An exception reaches the existing stage abort boundary, which restores the complete private epoch. |
| cost | No-op without a journal; otherwise actual pin/append work, while image-copy costs are charged separately. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0059

[Lines 451–460](../../../../../src/runtime/weighted.cpp#L451); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L451-L460:sha256:974aa43d1e7333d6f22b52369bba48d19322c2f9e4d92f95e6cc2ffc7964250c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a new inline record, cache its local factor and add that contribution to E. |
| inputs / outputs | Native handle/full tuple and movable cache image to live row metadata and optional visible key. |
| invariants | Compute factor from full support; prepare inverse before metadata insertion. Storage membership is still private under its table journal. |
| ownership | Map owns one original child array; captures own copies only when requested. |
| failure | Failure at capture/map/E insertion reverses table and metadata state through the outer stage boundary. |
| cost | One row metadata allocation/child array plus actual factor/projection work; no complete-state copy. |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0060

[Lines 461–484](../../../../../src/runtime/weighted.cpp#L461); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L461-L484:sha256:21fe4a70de7c4d594e2a5a155c8b7a3b8ec8dc129fbe718de483834d3a860303
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Update full numeric row state and its cached local contribution with compact inverse data. |
| inputs / outputs | Desired local/subtree/supported values and optional changed factor. |
| invariants | Fund inverse scalars/one slot before mutation. An inside child numeric change with unchanged positive support/local weight reuses the old factor; other required factors are recomputed without division. |
| ownership | Live map keeps its original array; optional diagnostic records own copies. |
| failure | Allocation/capture failure triggers outer epoch rollback. |
| cost | O(1) scalar/slot mutation and fixed undo payload. Recomputed factors scan only precompiled outside-child slots; projection/map/deep-key costs are separate. Only requested diagnostics copy child arrays. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0061

[Lines 485–495](../../../../../src/runtime/weighted.cpp#L485); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L485-L495:sha256:803b73a131cc953b0b4ef35cad79c6b0cd6135a60c56eb40628a72a34bde406e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detach a full row and subtract its cached visible contribution. |
| inputs / outputs | Exact native handle/tuple to retained map node and numerical E replacement. |
| invariants | The inverse owns the exact removed node/array; factor subtraction uses the old cached scalar before extraction. |
| ownership | Extracted node survives until commit or nonallocating reverse insertion; diagnostic pins are optional. |
| failure | Fund inverse first; any later E/table error rolls back the entire logical epoch. |
| cost | Ordered lookup/extract and original-account lifetime classification; the interior-node ledger scan is O(outstanding allocations). |
| Design | [Refactor.md §10.2 and W03](../../../../../Refactor.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); lifecycle/allocator/cost contracts are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0062

[Lines 496–505](../../../../../src/runtime/weighted.cpp#L496); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L496-L505:sha256:6e1bcab2b31184ea4414d741e58c10cc9c60cee2ef90f79f6b1afef6279513c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a causal numeric event to FIFO without recursive propagation. |
| inputs / outputs | Assign monotonic ID, map the private tag to public native_weight/child_message, optionally append the raw attempted event, then append its owning queue entry. |
| invariants | Same-key chains preserve enqueue order. A contribution initially captures shares; successful native normalization rewrites them to totals. Public EventKind has no new child semantics. |
| ownership | Accounted vector owns keys until drain; moved current event survives queue growth. |
| failure | Metric/work/capture/queue failure aborts the whole epoch. Capture can already include an unqueued/unfinished attempted event; aborted journals are partial traces. |
| cost | Amortized funded appends, one fixed kind selection; requested captures copy inline metadata. queue_peak measures pending entries, not reserved vector capacity. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0063

[Lines 506–542](../../../../../src/runtime/weighted.cpp#L506); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L506-L542:sha256:edd328b0898771fb95f4f87f7e8b4121f03ba3dfc9851d335e782e6fc195c43e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one full-row contribution in either a full separator message or a local visible-factor sum. |
| inputs / outputs | Compiled node, exact key, old/new row contribution and projection role produce a checked sum, native membership change and optional owning diagnostic. |
| invariants | The sum exists iff positive. Full messages and visible factors remain separate. Only full-message changes enqueue an ancestor event, tagged private child_message; visible factors remain terminal values. For enabled visible capture, telescope immediately before factor membership/scalar publication against other current factors. |
| ownership | The original account and epoch own native table journal, scalar/map-node undo and optional pinned MessageChange or FactorChange. Undo targets the exact map. |
| failure | Fund counter undo before changing a map; final-value arithmetic, key/index, allocation and work failures reach the one stage rollback boundary. |
| cost | Typed probe/map update and native zero-crossing work; disabled hook adds one branch. Enabled capture additionally visits actual visible prefixes/assignments and consolidates projected facts under the same grant. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0064

[Lines 543–556](../../../../../src/runtime/weighted.cpp#L543); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L543-L556:sha256:8cb864dff17cd20416d59b6525fabf19852fbc8e402996d8bd7a27d1e4a76855
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Maintain positive row membership and adjust its parent separator sum. |
| inputs / outputs | Old and new full subtree values for one complete row. |
| invariants | Survivor membership changes only across zero; numeric sums change at any unequal value. |
| ownership | Uses owner native storage and epoch journals. |
| failure | Missing survivor is an internal contract violation. |
| cost | Only actual value changes touch survivor/sum state; no work for equal products. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0065

[Lines 557–592](../../../../../src/runtime/weighted.cpp#L557); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L557-L592:sha256:a38e3697df49e2898a92c442fc6c9797fb37702fa22b890ff768b81b981003bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize a native contribution or validate an absolute total, then apply the existing native-row maintenance. |
| inputs / outputs | Validate both caller weights against the multiplicity limit, find the row once, read current local total, then either require absolute before==current or compute current-before+after with checked uint64 policy. |
| invariants | The adapter owns physical source identity and old/new share correctness. Native arithmetic enforces old&lt;=current and final&lt;=limit, but authenticates no source row. Equality is checked only after normalization. Successful captured native events expose actual totals. |
| ownership | Borrowed input has already become one owned native key. Existing rows keep their child array; deletion detaches original map/table state for funded rollback. |
| failure | Preserve existing bound-charge ordering before lookup. Contribution alone precharges one replace; underflow/overflow/work failure before normalization may leave raw shares in an aborted capture. Whole epoch rolls back; original typed failure propagates. |
| cost | One existing records lookup and ordered TupleId-map access. Contribution adds O(1) checked subtraction/addition plus one abstract work charge, without another lookup/map/payload. Existing supported products scan children; changed row propagation is unchanged. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0066

[Lines 593–606](../../../../../src/runtime/weighted.cpp#L593); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L593-L606:sha256:a00a0430635e39a070ea155deaf26791d85163b507fd18e8e31a4a48d732e5ba
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply a child message delta to one matched parent row. |
| inputs / outputs | Expected cached before, new child value, compiled child slot and row handle. |
| invariants | Require causal before match; generalized candidate removed only when last child support vanishes. |
| ownership | Inline slot edit plus compact undo; removed node/array retained for rollback. |
| failure | Causal mismatch is a contract error; numeric/resource errors abort stage. |
| cost | One affected row visit, supported count update and checked product; no division. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0067

[Lines 607–627](../../../../../src/runtime/weighted.cpp#L607); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L607-L627:sha256:2a8106bf12aefa310d4773b8abc620c1067c78528dc632a91d247a2b2401b52e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route child deltas through native reverse bucket or generalized full-scope candidate. |
| inputs / outputs | Compiled edge and event key to all matching parent rows. |
| invariants | Generalized candidate union retains partial support; product represents intersection. |
| ownership | Cursor uses epoch journal and original grant; candidates are accounted rows. |
| failure | Native reverse index required by checked shape; inconsistent candidate is contract error. |
| cost | O(matching bucket plus factors); unrelated rows are not scanned. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0068

[Lines 628–638](../../../../../src/runtime/weighted.cpp#L628); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L628-L638:sha256:3e49b588c4eba19be7f1adb69a2dadf6041b8d98b3be989b56f1662221c10b08
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Iteratively apply all causal events before exposing stage result. |
| inputs / outputs | FIFO vector/head and causal IDs; record execution-entry ordinals, dispatch private child_message to child and either native kind to native. |
| invariants | Each successfully drained event is applied once. applied_ordinal is set before processing and is not completion proof on abort. Successful stages leave all full messages/local factors consistent and empty the queue. |
| ownership | Move event before append can reallocate; clear queue after each stage. |
| failure | Processing errors reach the sole stage_native rollback boundary; previously captured attempted events can remain in an aborted journal. |
| cost | O(actual affected events/rows/products); no recursion by tree depth. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0069

[Lines 639–641](../../../../../src/runtime/weighted.cpp#L639); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L639-L641:sha256:bdc5bcd62f660d4f95a20971e85c469f760e01726d594e3b021872d5921f2367
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/weighted.cpp: opens anonymous namespace with translation-unit-local linkage; closes \`struct WeightedRuntime::PendingEpoch::Data\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0070

[Lines 642–674](../../../../../src/runtime/weighted.cpp#L642); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L642-L674:sha256:2763dd9fd738e16f81b6a68957e6fe34c761e7b7b78ed2835903bdaf8257ab58
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build an owning bounded view of rows/messages using committed or journal cursors. |
| inputs / outputs | Owner, sequence/tentative flag, row limit and cursor provider to Snapshot. |
| invariants | All rows and arrays copied; later edits cannot mutate snapshot values. |
| ownership | Captured tuples/record arrays and metadata charged to original account. |
| failure | Row/heap/native-grant failure rejects capture; private capture shares retained grant. |
| cost | O(rows plus child factors); not executed automatically on updates. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0071

[Lines 675–676](../../../../../src/runtime/weighted.cpp#L675); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L675-L676:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/weighted.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/weighted.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/weighted.cpp\` at its lexical source position in src/runtime/weighted.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/weighted.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0072

[Lines 677–681](../../../../../src/runtime/weighted.cpp#L677); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L677-L681:sha256:fc2b0efa4f74d5b295b3581418812094b37f9a5f71bfd4edadd585200ecdd1f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce nonempty public receiver authority before physical-plan admission. |
| inputs / outputs | Account/PhysicalPlan/options produce the private adoption constructor result. |
| invariants | Reject empty account before Impl::create can select its standalone default. |
| ownership | Only selected receiver funds newly frozen metadata and runtime state. |
| failure | MemoryFailure(contract) is fixed and allocation-free; other import failures propagate without a wrapper. |
| cost | One bool check plus normal import/adoption; no replacement account or duplicated pass. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0073

[Lines 682–686](../../../../../src/runtime/weighted.cpp#L682); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L682-L686:sha256:12cc39cd34330eafd8689e1a5cf0b0f1dca452bc448e2b601e36a83d215e414e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce nonempty receiver authority for compiled-artifact import. |
| inputs / outputs | Account/CompiledProgram/options yield an independently retained weighted runtime. |
| invariants | The receiver cap remains authoritative even if caller options request more/less. Existing standalone constructors remain separate. |
| ownership | New metadata is owned by receiver; foreign source is borrowed only for import. |
| failure | Empty account rejects with fixed MemoryFailure(contract) before allocation; RAII handles import failure. |
| cost | Fixed authority check and same native clone/import path, no new exception boundary. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0074

[Lines 687–687](../../../../../src/runtime/weighted.cpp#L687); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L687-L687:sha256:9c153f56d68381b7754bb88d5eb4769d9cafc4122550e9813adfd2c3f3ae8da5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a weighted direct-CQ runtime in a new query account. |
| inputs / outputs | A checked physical shape plus options produce the new facade through Impl::create. |
| invariants | Constructors share the same admission path and reject normalized SQL. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | Admission/allocation failure leaves no facade. |
| cost | One admission/import; no additional wrapper copy or validation framework. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0075

[Lines 688–688](../../../../../src/runtime/weighted.cpp#L688); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L688-L688:sha256:5a5297e62249857c51958f98c44601a3e051b66c7accb011342bdc14b689a597
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a weighted direct-CQ runtime in a new query account. |
| inputs / outputs | An immutable compiled shape plus options produce the new facade through Impl::create. |
| invariants | Constructors share the same admission path and reject normalized SQL. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | Admission/allocation failure leaves no facade. |
| cost | One admission/import; no additional wrapper copy or validation framework. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0076

[Lines 689–691](../../../../../src/runtime/weighted.cpp#L689); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L689-L691:sha256:9ea8c3ace8159f356b86cfa1513da6ffa6a521b5428785d0e2fdbb8bf54cd13f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use default facade move/destruction semantics for the shared implementation owner. |
| inputs / outputs | Move transfers impl_; assignment releases prior facade ownership; destruction releases one owner. |
| invariants | Pending tokens/readers retain their actual owner independently of facade movement. |
| ownership | shared_ptr supplies the existing lifetime; no second state copy. |
| failure | Move operations are noexcept; final release follows native nonallocating cleanup. |
| cost | Fixed owner move/release except actual last-owner state destruction. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0077

[Lines 692–692](../../../../../src/runtime/weighted.cpp#L692); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L692-L692:sha256:8e5b41297ccd144cf477006cfb587b95f6f91b0747186a6825c65078353bf1d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate facade presence and borrow its stable implementation. |
| inputs / outputs | A non-moved facade returns Impl by reference. |
| invariants | Moving empties only the facade; pending/cursor tokens retain their own shared owner. |
| ownership | Borrowed internal reference; no new shared-owner copy. |
| failure | Moved-from access raises invalid_runtime. |
| cost | O(1), allocation-free success. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0078

[Lines 693–693](../../../../../src/runtime/weighted.cpp#L693); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L693-L693:sha256:e5f6f4c428ae9b98e82652036e49cc8765cb59fbc071f74ea2401470a5c2deb9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the checked structural program. |
| inputs / outputs | Returns const lvalue reference; it carries structural identity, not weighted semantics. |
| invariants | The reference is valid only while its retained program owner exists. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0079

[Lines 694–694](../../../../../src/runtime/weighted.cpp#L694); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L694-L694:sha256:ec6e55988b060d57a14bfe758dc76a0c2873c066122efda4fc02a75788463be0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the versioned weighted identity. |
| inputs / outputs | Returns shape digest, weighted digest and multiplicity limit. |
| invariants | Structural identity alone cannot authorize weighted execution. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0080

[Lines 695–695](../../../../../src/runtime/weighted.cpp#L695); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L695-L695:sha256:4be62f89829cb377437b475e8880047c3ad14e05236e0226a2ebe5503ec91f37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect admitted weighted configuration. |
| inputs / outputs | Return admitted options by const reference. memory_limit_bytes is the actual selected-account limit, including create_into receivers. |
| invariants | Immutable after admission; caller options cannot enlarge or replace receiving authority. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0081

[Lines 696–696](../../../../../src/runtime/weighted.cpp#L696); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L696-L696:sha256:adc8bc1b590e66a5c802a0ad6009803262ce5cdb6f515cea1219503878f75db9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect native query ownership. |
| inputs / outputs | Returns the original account owner ID. |
| invariants | ID identifies the selected original/receiving account. A separately funded compiler can differ; an intentionally shared compiler/receiver has the same account ID. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0082

[Lines 697–697](../../../../../src/runtime/weighted.cpp#L697); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L697-L697:sha256:5cab4c43c266444f0f70964406edee61c52b08de614a9f9242972ec93bc4d98a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the last committed logical sequence. |
| inputs / outputs | Returns the committed scalar sequence, initially zero. |
| invariants | A private stage does not advance it. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0083

[Lines 698–698](../../../../../src/runtime/weighted.cpp#L698); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L698-L698:sha256:a05b9767e14154f26224f8cf252032449cf543035a2d3844d5121566367c0760
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether a new exclusive epoch can start. |
| inputs / outputs | Returns true only with no private epoch and no active readers. |
| invariants | This is a single-caller state query, not a thread lock. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0084

[Lines 699–699](../../../../../src/runtime/weighted.cpp#L699); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L699-L699:sha256:b5550ca3b9f704d9da9dd706747edd7938af0244a9c60b55c7aecaccc1444b85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the committed complete witness count. |
| inputs / outputs | Returns the empty-key full-root summary or constant route count. |
| invariants | Private epochs reject this read; active committed cursors permit it. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | O(1), no result enumeration. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0085

[Lines 700–700](../../../../../src/runtime/weighted.cpp#L700); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L700-L700:sha256:6638d7ea325953736bed81e8d0f8bb1c20d87c9d68683530187fee70e357d684
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the most recently closed logical attempt. |
| inputs / outputs | Returns an optional copy of sequence, committed/aborted phase and inline metrics. |
| invariants | No attempt means none has closed; a live private epoch is not reported as closed. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | Fixed metric copy. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0086

[Lines 701–701](../../../../../src/runtime/weighted.cpp#L701); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L701-L701:sha256:5a2523e7ad4b29c9822dc05b1b7f5a1e21ee029b0d48d25c99c2cebd4f6ca81e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect actual native account usage. |
| inputs / outputs | Returns the existing account statistics by value. |
| invariants | Requested bytes include native ownership/allocator overhead and retained outputs. |
| ownership | Returned values own scalars; returned references borrow the facade implementation. |
| failure | Moved-from access raises invalid_runtime; root_weight also raises runtime_busy during a private epoch. |
| cost | Fixed diagnostic structure copy; no row traversal. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0087

[Lines 702–704](../../../../../src/runtime/weighted.cpp#L702); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L702-L704:sha256:1f3e81ddb02d3de74e588b3ee6750cbab03863a58be59663700444f55ab7b587
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the existing capture-disabled epoch entry point. |
| inputs / outputs | Next contiguous sequence delegates to the typed overload with DeltaCapture::disabled. |
| invariants | Reject any private epoch or reader before creating the grant/token; set updating only after preparation succeeds. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | Invalid sequence/busy/admission failure changes no committed state and publishes no token. |
| cost | One direct forwarding call; no delta control/frame/output allocation or capture-work debit. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0088

[Lines 705–712](../../../../../src/runtime/weighted.cpp#L705); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L705-L712:sha256:82d6ef35cc8e6cc4c9116271356fda693d94b8fc1c94b3c27dfe1b76282a084d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire one exclusive epoch with optional genuine output capture. |
| inputs / outputs | Next contiguous sequence and capture mode; fully funded move-only token. |
| invariants | Reject busy/sequence first, fund capture before setting updating, and retain one indexed allowance across all stages. |
| ownership | Shared Impl survives facade moves/death; original account owns every enabled control/scratch block. |
| failure | Setup failure leaves committed state visible and publishes no token. |
| cost | Disabled fixed controls only; enabled O(visible steps/output capacity) preparation and actual allocations. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0089

[Lines 713–715](../../../../../src/runtime/weighted.cpp#L713); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L713-L715:sha256:217892ab21f3bf653352cd65c7809300f4a0927ec6a092d7239355a312747431
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one replacement as one complete atomic logical epoch. |
| inputs / outputs | Update sequence and expected-weight replacement return a committed Epoch. |
| invariants | Uses the same begin/stage/commit protocol as multiple-stage callers. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | Stage failure rolls back through its sole abort boundary; the wrapper adds no exception handler. |
| cost | Only underlying admission/affected-row work; no second maintenance pass. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0090

[Lines 716–719](../../../../../src/runtime/weighted.cpp#L716); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L716-L719:sha256:4417936347762eb37a84414d7e100715fd608fbae61f5b75e8af199e80c0186b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a bounded owning view of committed weighted state. |
| inputs / outputs | SnapshotLimits cap total captured row/message/factor entries; result identifies owner, binding and sequence. |
| invariants | Private state is rejected, while committed readers may coexist. This is inspection, not import/checkpoint authority. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | Failure destroys the partial result and leaves committed query state unchanged. |
| cost | Explicit O(captured rows, child arrays, keys and deep bytes); no automatic call from an update or result cursor. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0091

[Lines 720–720](../../../../../src/runtime/weighted.cpp#L720); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L720-L720:sha256:6f7bc571171edf20c9a4256f7c8ec5300a37844dfaecb8100751751b2ee3d321
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt an already prepared exclusive epoch token. |
| inputs / outputs | Accounted unique Data moves into the public token. |
| invariants | The caller has already marked this owner updating. |
| ownership | Move transfers the sole token owner; no copy of runtime state. |
| failure | Noexcept token construction. |
| cost | O(1), no allocation. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0092

[Lines 721–723](../../../../../src/runtime/weighted.cpp#L721); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L721-L723:sha256:761946ce53827bab0ced3aa64350302c03249be4bf64be0c7819f10a54fb7d1e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer exclusive pending-token ownership and abort an overwritten/abandoned token by RAII. |
| inputs / outputs | Default accounted-unique move constructor/assignment and destructor. |
| invariants | Moved-from token is inactive; Data destructor performs idempotent rollback if still open. |
| ownership | Exactly one token owns each Data; shared Impl still belongs to that Data until close. |
| failure | Noexcept movement/destruction uses prepaid inverse cleanup. |
| cost | Fixed pointer move; replacing/destroying an open token pays actual rollback work. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0093

[Lines 724–724](../../../../../src/runtime/weighted.cpp#L724); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L724-L724:sha256:cfb8cb2dda0ddb1e5cccdc469629bad0ca5259758989ebf3f6bb318dd315d1a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check token openness without throwing on moved-from tokens. |
| inputs / outputs | Returns true only if Data and its active owner both remain. |
| invariants | Commit/rollback/failed stage makes it false. |
| ownership | Inline checks; no owner acquisition. |
| failure | Noexcept, including moved-from access. |
| cost | O(1). |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0094

[Lines 725–725](../../../../../src/runtime/weighted.cpp#L725); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L725-L725:sha256:dfca8e3e5cd03dca57eb1a7755fdcfa445031e3769cf31efb9db0f66a9abbebf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly abandon every private stage. |
| inputs / outputs | Open token restores committed state; closed/moved-from token is a no-op. |
| invariants | Same inverse protocol as RAII destruction; it never advances committed sequence. |
| ownership | Borrows the active private epoch owner and its original grant; caller cannot publish intermediate state. |
| failure | Noexcept and nonallocating using prepared inverse state. |
| cost | O(actual inverse/table cleanup), no full-state reconstruction. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0095

[Lines 726–729](../../../../../src/runtime/weighted.cpp#L726); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L726-L729:sha256:74d557a97766572e040e58050562f89b4e3cc37ddb2febbe4385eb4ae8b4716e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Delegate the existing absolute expected-total port to the shared native stage boundary. |
| inputs / outputs | Replacement node/Row/before/after become a noexcept borrowed TupleValuesView and contribution=false; return whether native_changes increased. |
| invariants | Absolute before must match the current local total. The legacy Row route of AccountedLayout::tuple_view calls the same former tuple(Row const&) validation/copy path. |
| ownership | Caller retains input Row through this synchronous call. stage_native copies funded native key bytes before queuing; the token retains owner/grant. |
| failure | Forwarding adds no catch or error translation. All fallible validation/maintenance stays inside stage_native, which aborts/rethrows on error. |
| cost | Fixed borrowed-view forwarding; no new allocation, scan, native lookup or abstract work charge on the old absolute path. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0096

[Lines 730–733](../../../../../src/runtime/weighted.cpp#L730); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L730-L733:sha256:8d4909d2c7ec2d094e7fc2ed50bdb4cefeb61bba84c5fe4531840197b196c764
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward the new share port through the existing synchronous transaction boundary. |
| inputs / outputs | Node/view/two shares become stage_native(...,true); return its native-change flag. |
| invariants | Adapter authenticates physical identity and contribution history. Native code implements arithmetic only. |
| ownership | Move the view owner/borrow representation; stage_native owns copied keys before returning. |
| failure | No catch or translation here; the sole shared boundary aborts the whole epoch. |
| cost | Fixed forwarding; no map/allocation or added lookup in this wrapper. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0097

[Lines 734–748](../../../../../src/runtime/weighted.cpp#L734); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L734-L748:sha256:bf3dcedf7688e72a6f5965db4edfb54385650c8cdc12308cad7366bb3a199588
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share validation, owned-key creation, FIFO drain and the sole rollback catch between native ports. |
| inputs / outputs | NodeId, complete TupleValuesView, old/next weights and private contribution bool return whether native_changes increased. |
| invariants | Check active token before entering. Rebind the same retained lease, validate native node, copy typed key, choose private tag, enqueue/drain exactly once. No generalized external port. |
| ownership | Caller view lives through synchronous copy. Queue/native tables retain original-account owned key bytes; no borrowed input escapes. |
| failure | One catch-all rolls back every stage and rethrows original type. Closed-token rejection is outside because it has no active epoch to restore. |
| cost | Same key-validation/copy and one existing native lookup. Legacy Row dispatch reaches the former exact tuple(Row const&) implementation; only contribution normalization adds a charged O(1) arithmetic step. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0098

[Lines 749–753](../../../../../src/runtime/weighted.cpp#L749); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L749-L753:sha256:589797999e0c36ce7c85ae17f1435403c41c8252efe814250210175cf48bbe9b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow only exact numeric bag differences from the matching active capture mode. |
| inputs / outputs | Active token in; nullopt for another/disabled mode, otherwise a borrowed span that may be empty. |
| invariants | The differently named capture mode cannot impersonate this preview; root counts and native state are untouched. |
| ownership | Span borrows the active existing accumulator and expires on mutation/commit/rollback/token destruction. |
| failure | Closed/moved token throws the existing invalid_epoch error; no allocation/fallback is attempted. |
| cost | O(1) active/mode checks and span construction; no copy, lookup or grant refill. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0099

[Lines 754–758](../../../../../src/runtime/weighted.cpp#L754); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L754-L758:sha256:a4137e96afa59b92215f21be520ebca99e02956578e2b24c5541631a484a26ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow only unit support changes from the matching active capture mode. |
| inputs / outputs | Active token in; nullopt for another/disabled mode, otherwise a borrowed span that may be empty. |
| invariants | The differently named capture mode cannot impersonate this preview; root counts and native state are untouched. |
| ownership | Span borrows the active existing accumulator and expires on mutation/commit/rollback/token destruction. |
| failure | Closed/moved token throws the existing invalid_epoch error; no allocation/fallback is attempted. |
| cost | O(1) active/mode checks and span construction; no copy, lookup or grant refill. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0100

[Lines 759–761](../../../../../src/runtime/weighted.cpp#L759); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L759-L761:sha256:ad74b7e764499253e2c2f79c4fe97e21814c949516cf39430ceee4fdeb5d311f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable unit support facts from an owning support handle. |
| inputs / outputs | Live SupportDeltas in; borrowed span of unit BagDelta records out. |
| invariants | This handle represents DISTINCT support changes only, separate from numeric BagDeltas and aggregate group replacements. |
| ownership | The shared immutable accumulator pins tuple payloads and original receiving account; the returned view requires the handle lifetime. |
| failure | An empty handle throws support_capture_disabled; rvalue borrows remain deleted. |
| cost | O(1), no allocation, scan, arithmetic or accounting refill. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0101

[Lines 762–764](../../../../../src/runtime/weighted.cpp#L762); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L762-L764:sha256:db4f09bb4966193c8d586e26055e3c5b88c119423e6b70b4ac4ca5d85e0c6004
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose immutable actual capture work metrics from an owning support handle. |
| inputs / outputs | Live SupportDeltas in; borrowed BagDeltaMetrics reference out. |
| invariants | This handle represents DISTINCT support changes only, separate from numeric BagDeltas and aggregate group replacements. |
| ownership | The shared immutable accumulator pins tuple payloads and original receiving account; the returned view requires the handle lifetime. |
| failure | An empty handle throws support_capture_disabled; rvalue borrows remain deleted. |
| cost | O(1), no allocation, scan, arithmetic or accounting refill. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0102

[Lines 765–767](../../../../../src/runtime/weighted.cpp#L765); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L765-L767:sha256:bfb10475a2af554fe07ef51a7fbc4e4844908bc1360c853f0a0c42f1b62e0753
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow committed unique nonzero output facts. |
| inputs / outputs | Engaged immutable owner to const fact span. |
| invariants | Order unspecified; borrow must not outlive the owning handle. |
| ownership | Shared const owner retains original-account payloads and vector capacity. |
| failure | Empty handle raises delta_capture_disabled. |
| cost | Fixed span; no scan/copy/allocation. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0103

[Lines 768–770](../../../../../src/runtime/weighted.cpp#L768); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L768-L770:sha256:79a45d2f1d9ed2f47660e4894034eefb9153398c143e2206d5b5d568e926c4d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read immutable capture-specific admission counters. |
| inputs / outputs | Engaged owner to borrowed Metrics reference. |
| invariants | Counters remain capture subset of the committed epoch work, not wall time. |
| ownership | Reference borrows the handle. |
| failure | Empty handle raises delta_capture_disabled. |
| cost | Fixed reference; no allocation. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0104

[Lines 771–771](../../../../../src/runtime/weighted.cpp#L771); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L771-L771:sha256:6c3f6332d777d2e0e54aefc46beb65e12aa403d8504acc10967d2e326ee91c27
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow tentative epoch summaries and metrics. |
| inputs / outputs | Open token returns its current Epoch by const reference. |
| invariants | Tentative summaries are inspection only; they are not committed deltas or durable publication. |
| ownership | Reference borrows Data and must not outlive or be used after its token closes. |
| failure | Raises invalid_epoch if closed. |
| cost | O(1), no snapshot or history copy. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0105

[Lines 772–776](../../../../../src/runtime/weighted.cpp#L772); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L772-L776:sha256:39b43af3435d727cd63f6ff6c09dff03a50c8d2c7df69d07e368f145a0438642
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture bounded tentative state using the retained epoch grant. |
| inputs / outputs | Open token and entry limit produce an owning Snapshot marked tentative at the pending sequence. |
| invariants | Touched tables read through their journals; snapshot work spends the same original grant and does not refill it. |
| ownership | All retained allocations use the original query account; no second account or state mirror. |
| failure | A snapshot failure destroys its partial output; it does not itself call stage rollback or publish any state. |
| cost | Actual rows/keys/child arrays copied plus touched-journal searches; explicit inspection overhead only. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0106

[Lines 777–795](../../../../../src/runtime/weighted.cpp#L777); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L777-L795:sha256:b02762fae56317252c045ba6f5d477e80afa8ee32696a6df824e532c831dfebe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the already prepared numeric state and exactly one separately typed capture handle. |
| inputs / outputs | Active token with all work/output preparation complete in; committed Epoch with unchanged numeric sequence/root totals and mode-appropriate owning handle out. |
| invariants | Only support mode publishes SupportDeltas; enabled publishes BagDeltas. Pending views expire; no source/kernel arithmetic is replaced by support values. |
| ownership | Move/share the existing funded accumulator into the chosen handle, release traversal scratch, commit table journals and release undo/lease; emitted tuple payloads retain their original account. |
| failure | Existing active-token contract errors precede publication; funded publication adds no allocation, serialization, retry or exception translation. |
| cost | Existing funded commit/cleanup plus fixed mode branch/shared-handle move. No full scan/snapshot or capture conversion buffer. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §W02-W03/W05-W06](../../../../../Refactor.md) |

## B0107

[Lines 796–796](../../../../../src/runtime/weighted.cpp#L796); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L796-L796:sha256:97734ee3ed73fbf0bd112ff8fee5fae528737ea20327081d48b1efcf3f9b9a5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime\` at its lexical source position in src/runtime/weighted.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
