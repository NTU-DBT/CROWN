# `src/runtime/support.cpp` — block usage map

[Source](../../../../../src/runtime/support.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain record/S/P/E support state and current/epoch cursor leases.

Snapshot SHA-256: `3e6b46b7705464f9684b1be4046412c5645aabca069a4cbc166f7066a7dd53f6`. 2164 lines partitioned into 253 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [support](../../../subsystem_contracts.md#support). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../src/runtime/support.cpp#L1) | Imports dependencies; controls preprocessing; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 24–26](../../../../../src/runtime/support.cpp#L24) | Callable definition: void require(bool condition,std::string_view code,std::string_view message) | calls Error, std::string; guard void require(bool condition,std::string_view code,std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 27–27](../../../../../src/runtime/support.cpp#L27) | Callable definition: template&lt;class Failure&gt; \[\[noreturn\]\] void support_present(const Failure& failure) | calls Error, std::string, code, what · [reviewed contract](#b0003) |
| [B0004 · 28–34](../../../../../src/runtime/support.cpp#L28) | Callable definition: SupportOwnerId new_owner() | calls load, require, max, compare_exchange_weak; guard require(value!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"support_overflow","runtime owner IDs exha…; returns {value+1}; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 35–35](../../../../../src/runtime/support.cpp#L35) | Explanatory comments or spacing. | source comment (unverified): // Internal metadata IDs must not consume the public runtime-owner sequence. · [reviewed contract](#b0005) |
| [B0006 · 36–42](../../../../../src/runtime/support.cpp#L36) | Callable definition: std::uint64_t new_metadata_owner() | calls load, max, resource::MemoryFailure, compare_exchange_weak; returns value+1; 1 loop sites; source comment (unverified): // Internal metadata IDs must not consume the public runtime-owner sequence. · [reviewed contract](#b0006) |
| [B0007 · 43–46](../../../../../src/runtime/support.cpp#L43) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 47–49](../../../../../src/runtime/support.cpp#L47) | Callable definition: template&lt;class Map&gt; Map memory_map(const resource::MemoryAccount& account,resource::MemoryPurpose purpose=resource::MemoryPurpose… | calls Map, Map::allocator_type; returns Map(typename Map::key_compare{},typename Map::allocator_type(account,purpose)) · [reviewed contract](#b0008) |
| [B0009 · 50–55](../../../../../src/runtime/support.cpp#L50) | Type/record definition: struct CompactRowLess | returns a.view()&lt;b.view(); a.view()&lt;b · [reviewed contract](#b0009) |
| [B0010 · 56–56](../../../../../src/runtime/support.cpp#L56) | Explanatory comments or spacing. |  |
| [B0011 · 57–63](../../../../../src/runtime/support.cpp#L57) | Callable definition: template&lt;class T&gt; void program_words(storage::IndexWorkAllowance* work,std::size_t count) | calls max, storage::IndexFailure, admit · [reviewed contract](#b0011) |
| [B0012 · 64–72](../../../../../src/runtime/support.cpp#L64) | Type/record definition: struct RecordState |  · [reviewed contract](#b0012) |
| [B0013 · 73–75](../../../../../src/runtime/support.cpp#L73) | Callable definition: std::vector&lt;bool&gt; export_flags(const RecordState& record) | calls begin, end; returns std::vector&lt;bool&gt;(record.present.begin(),record.present.end()) · [reviewed contract](#b0013) |
| [B0014 · 76–80](../../../../../src/runtime/support.cpp#L76) | Callable definition: std::vector&lt;bool,resource::OwnerAllocator&lt;bool&gt;&gt; retained_flags(const RecordState& record) | calls get_allocator, begin, end, account; returns {record.present.begin(),record.present.end(),resource::OwnerAllocator&lt;bool&gt;(allocator.account(), · [reviewed contract](#b0014) |
| [B0015 · 81–85](../../../../../src/runtime/support.cpp#L81) | Callable definition: auto transition_buffer(const resource::MemoryAccount& account) | calls ; returns std::vector&lt;MembershipTransition,resource::OwnerAllocator&lt;MembershipTransition&gt;&gt;( · [reviewed contract](#b0015) |
| [B0016 · 86–89](../../../../../src/runtime/support.cpp#L86) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_nothrow_move_constructible_v&lt;SupportValueState&gt;); · [reviewed contract](#b0016) |
| [B0017 · 90–104](../../../../../src/runtime/support.cpp#L90) | Type/record definition: struct NodeState | returns {records.get_allocator().account(),attribution,children} · [reviewed contract](#b0017) |
| [B0018 · 105–107](../../../../../src/runtime/support.cpp#L105) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0018) |
| [B0019 · 108–122](../../../../../src/runtime/support.cpp#L108) | Type/record definition: struct SupportEnumerationProgram | returns borrowed; view() · [reviewed contract](#b0019) |
| [B0020 · 123–139](../../../../../src/runtime/support.cpp#L123) | Type/record definition: struct State | growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 140–140](../../../../../src/runtime/support.cpp#L140) | Explanatory comments or spacing. |  |
| [B0022 · 141–150](../../../../../src/runtime/support.cpp#L141) | Callable definition: RelationId relation(const auto& node,SupportRole role) | calls require, has_value, Error; guard require(node.visible_relation.has_value(),"invalid_support_role","node is outside the enumeration s…; returns node.records; node.survivors · [reviewed contract](#b0022) |
| [B0023 · 151–164](../../../../../src/runtime/support.cpp#L151) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0023) |
| [B0024 · 165–168](../../../../../src/runtime/support.cpp#L165) | Callable definition: bool cursor_clocks(const CursorObservation& value) noexcept | calls ; returns value.options.mode==ObservationMode::timed \|\| · [reviewed contract](#b0024) |
| [B0025 · 169–174](../../../../../src/runtime/support.cpp#L169) | Callable definition: void cursor_add(CursorObservation& value,CursorMetricId id,std::uint64_t amount=1) noexcept | calls  · [reviewed contract](#b0025) |
| [B0026 · 175–178](../../../../../src/runtime/support.cpp#L175) | Callable definition: std::uint64_t cursor_now(CursorObservation& value,const std::shared_ptr&lt;detail::ObservationState&gt;& observer) noexcept | calls cursor_clocks, cursor_add, note_cursor_clock_read, detail::read_observation_clock; returns 0; detail::read_observation_clock() · [reviewed contract](#b0026) |
| [B0027 · 179–184](../../../../../src/runtime/support.cpp#L179) | Callable definition: void cursor_elapsed(CursorObservation& value,CursorMetricId id,std::uint64_t start,const std::shared_ptr&lt;detail::ObservationState… | calls cursor_clocks, cursor_now, cursor_add · [reviewed contract](#b0027) |
| [B0028 · 185–186](../../../../../src/runtime/support.cpp#L185) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0028) |
| [B0029 · 187–187](../../../../../src/runtime/support.cpp#L187) | Callable definition: std::span&lt;const CursorMetricDescriptor&gt; cursor_observation_registry() noexcept | calls ; returns cursor_registry · [reviewed contract](#b0029) |
| [B0030 · 188–189](../../../../../src/runtime/support.cpp#L188) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_copyable_v&lt;CursorObservation&gt;); · [reviewed contract](#b0030) |
| [B0031 · 190–193](../../../../../src/runtime/support.cpp#L190) | Callable definition: ProjectionSupportCount increment_support(ProjectionSupportCount value,std::uint64_t limit) | calls require; guard require(value.value&lt;limit,"support_overflow","projection support exceeds its configured exact count…; returns {value.value+1} · [reviewed contract](#b0031) |
| [B0032 · 194–196](../../../../../src/runtime/support.cpp#L194) | Callable definition: ProjectionSupportCount decrement_support(ProjectionSupportCount value) | calls require; guard require(value.value&gt;0,"runtime_contract","projection support underflow"); return {value.value-1};; returns {value.value-1} · [reviewed contract](#b0032) |
| [B0033 · 197–200](../../../../../src/runtime/support.cpp#L197) | declares types or opens a type body. |  · [reviewed contract](#b0033) |
| [B0034 · 201–201](../../../../../src/runtime/support.cpp#L201) | Callable definition: \[\[nodiscard\]\] storage::IndexWorkAllowance* work() const | calls detail::compact_storage_work; returns detail::compact_storage_work(storage_context) · [reviewed contract](#b0034) |
| [B0035 · 202–216](../../../../../src/runtime/support.cpp#L202) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0035) |
| [B0036 · 217–233](../../../../../src/runtime/support.cpp#L217) | Callable definition: template&lt;class Source&gt; Impl(Source p,SupportOptions o,std::shared_ptr&lt;detail::StorageWorkContext&gt; context):options(o),storage_con… | calls options, storage_context, std::move, observation; guard require(!(options.observation.mode==ObservationMode::off && options.capture_transitions),"invalid_o…; growth emplace_back, make_accounted_unique, reserve; 2 loop sites · [reviewed contract](#b0036) |
| [B0037 · 234–234](../../../../../src/runtime/support.cpp#L234) | Callable definition: void readable() const | calls require; guard void readable() const { require(!updating,"runtime_busy","a prepared logical epoch is active"); } · [reviewed contract](#b0037) |
| [B0038 · 235–235](../../../../../src/runtime/support.cpp#L235) | Callable definition: void writable() const | calls readable, require; guard void writable() const { readable(); require(readers==0,"runtime_busy","result cursors pin the commi… · [reviewed contract](#b0038) |
| [B0039 · 236–258](../../../../../src/runtime/support.cpp#L236) | Callable definition: void observe(const SupportMetrics& metrics) const noexcept | calls set · [reviewed contract](#b0039) |
| [B0040 · 259–260](../../../../../src/runtime/support.cpp#L259) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0040) |
| [B0041 · 261–261](../../../../../src/runtime/support.cpp#L261) | Callable definition: const program::Span&lt;SupportNodeProgram&gt;& program_nodes() const | calls ; returns state-&gt;program_nodes · [reviewed contract](#b0041) |
| [B0042 · 262–262](../../../../../src/runtime/support.cpp#L262) | Callable definition: const program::Span&lt;SupportEdgeProgram&gt;& program_edges() const | calls ; returns state-&gt;program_edges · [reviewed contract](#b0042) |
| [B0043 · 263–265](../../../../../src/runtime/support.cpp#L263) | Callable definition: const SupportNodeProgram& node(NodeId id) const | calls require, program_nodes, size; guard require(id.value&lt;program_nodes().size(),"invalid_native_update","node is outside the physical plan"…; returns program_nodes()\[id.value\] · [reviewed contract](#b0043) |
| [B0044 · 266–266](../../../../../src/runtime/support.cpp#L266) | Callable definition: SupportHandle handle(NodeId node,SupportRole role,TupleHandle value) const | calls ; returns {owner,node,role,value.tuple} · [reviewed contract](#b0044) |
| [B0045 · 267–271](../../../../../src/runtime/support.cpp#L267) | Callable definition: bool answer(const State& current) const | calls route, table, program_nodes, tree; returns true; false · [reviewed contract](#b0045) |
| [B0046 · 272–275](../../../../../src/runtime/support.cpp#L272) | Callable definition: storage::Tuple plan_tuple(const storage::AccountedTuple& tuple) const | calls storage::Tuple::from_accounted, layouts, at, layout; returns storage::Tuple::from_accounted(state-&gt;compiled.layouts().at(tuple.layout().id().value) · [reviewed contract](#b0046) |
| [B0047 · 276–276](../../../../../src/runtime/support.cpp#L276) | Type/record definition: struct Pending |  · [reviewed contract](#b0047) |
| [B0048 · 277–288](../../../../../src/runtime/support.cpp#L277) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0048) |
| [B0049 · 289–289](../../../../../src/runtime/support.cpp#L289) | Type/record definition: enum class MetaKind |  · [reviewed contract](#b0049) |
| [B0050 · 290–299](../../../../../src/runtime/support.cpp#L290) | Type/record definition: struct MetaUndo |  · [reviewed contract](#b0050) |
| [B0051 · 300–300](../../../../../src/runtime/support.cpp#L300) | Member/declaration region. |  · [reviewed contract](#b0051) |
| [B0052 · 301–305](../../../../../src/runtime/support.cpp#L301) | Callable definition: Transaction(Impl& r,State& s,SupportEpoch& o,std::shared_ptr&lt;SupportJournal&gt; j) :runtime(r),state(s),output(o),journal(std::move(… | calls runtime, state, output, journal · [reviewed contract](#b0052) |
| [B0053 · 306–330](../../../../../src/runtime/support.cpp#L306) | Callable definition: ~Transaction() | calls rbegin, rend, erase, lifetime; growth insert; 2 loop sites · [reviewed contract](#b0053) |
| [B0054 · 331–336](../../../../../src/runtime/support.cpp#L331) | Callable definition: void commit() noexcept | calls clear; 1 loop sites; source comment (unverified): // Public record pins cover every membership/counter change. Undo nodes · [reviewed contract](#b0054) |
| [B0055 · 337–344](../../../../../src/runtime/support.cpp#L337) | Callable definition: void charge(std::uint64_t amount=1) | calls detail::build_metric, require, max; guard require(amount&lt;=std::numeric_limits&lt;std::uint64_t&gt;::max()-used,"resource_limit","support work count… · [reviewed contract](#b0055) |
| [B0056 · 345–349](../../../../../src/runtime/support.cpp#L345) | Callable definition: void metric(std::uint64_t& value,std::uint64_t amount=1) | calls charge; source comment (unverified): // Every managed category starts at zero and increments only after charge, · [reviewed contract](#b0056) |
| [B0057 · 350–356](../../../../../src/runtime/support.cpp#L350) | Callable definition: storage::AccountedStorageTable::Journal& writer(RelationId id) | calls table, journal, detail::owning_storage_work, emplace_back; returns table; journal-&gt;storage_.back().second; growth emplace_back; 1 loop sites; source comment (unverified): // Reuse existing journals: linear in the number of touched relations. · [reviewed contract](#b0057) |
| [B0058 · 357–361](../../../../../src/runtime/support.cpp#L357) | Callable definition: TupleHandle insert(RelationId id,const storage::AccountedTuple& tuple) | calls metric, writer, require; guard require(result.inserted,"runtime_contract","internal insert duplicated membership"); return result.…; returns result.handle; growth insert · [reviewed contract](#b0058) |
| [B0059 · 362–365](../../../../../src/runtime/support.cpp#L362) | Callable definition: void erase(RelationId id,TupleHandle handle) | calls metric, require, writer; guard require(writer(id).erase(handle),"runtime_contract","internal erase lost membership"); · [reviewed contract](#b0059) |
| [B0060 · 366–375](../../../../../src/runtime/support.cpp#L366) | Callable definition: resource::AccountedUnique&lt;MetaUndo&gt; prepare(MetaKind kind,const SupportNodeProgram& node,SupportRole role,TupleId id) | calls metric, memory, get_deleter, set_lifetime; returns item; growth make_accounted_unique, reserve · [reviewed contract](#b0060) |
| [B0061 · 376–378](../../../../../src/runtime/support.cpp#L376) | Callable definition: static SupportValueState record_value(const RecordState& record) | calls retained_flags; returns {true,record.satisfied,retained_flags(record),{}} · [reviewed contract](#b0061) |
| [B0062 · 379–379](../../../../../src/runtime/support.cpp#L379) | Callable definition: static SupportValueState count_value(ProjectionSupportCount value) | calls ; returns {true,{}, {},value} · [reviewed contract](#b0062) |
| [B0063 · 380–398](../../../../../src/runtime/support.cpp#L380) | Callable definition: void note(const SupportNodeProgram& node,SupportRole role,TupleHandle handle,SupportValueState before,SupportValueState after) | calls metric, table, relation, pin; returns value.support?value.support-&gt;value:value.satisfied?; growth push_back · [reviewed contract](#b0063) |
| [B0064 · 399–420](../../../../../src/runtime/support.cpp#L399) | Callable definition: void record(const SupportNodeProgram& node,TupleHandle handle,std::optional&lt;RecordState&gt; desired) | calls find, require, end, has_value; guard require(found!=records.end() \|\| desired.has_value(),"runtime_contract","erasing absent record metad…; growth emplace, push_back · [reviewed contract](#b0064) |
| [B0065 · 421–438](../../../../../src/runtime/support.cpp#L421) | Callable definition: void counter(const SupportNodeProgram& node,SupportRole role,TupleHandle handle,std::optional&lt;ProjectionSupportCount&gt; desired) | calls find, require, end, has_value; guard require(found!=counts.end() \|\| desired.has_value(),"runtime_contract","erasing absent count metadat…; growth emplace, push_back · [reviewed contract](#b0065) |
| [B0066 · 439–441](../../../../../src/runtime/support.cpp#L439) | Callable definition: void event(const SupportNodeProgram& node,SupportRole role,TupleHandle handle,SetOperation operation,const storage::AccountedTupl… | calls push_back, handle, plan_tuple; growth push_back · [reviewed contract](#b0066) |
| [B0067 · 442–445](../../../../../src/runtime/support.cpp#L442) | Callable definition: void start() | calls metric, push_back; growth push_back · [reviewed contract](#b0067) |
| [B0068 · 446–452](../../../../../src/runtime/support.cpp#L446) | Callable definition: void native_trace(const SupportNodeProgram& node,TupleHandle handle,const storage::AccountedTuple& tuple,bool add) | calls event, push_back, handle, plan_tuple; growth insert, push_back · [reviewed contract](#b0068) |
| [B0069 · 453–466](../../../../../src/runtime/support.cpp#L453) | Callable definition: void enqueue(std::size_t edge_id,bool add,const storage::AccountedTuple& key,TupleHandle source) | calls metric, push_back, clone, event; growth clone, insert, push_back · [reviewed contract](#b0069) |
| [B0070 · 467–471](../../../../../src/runtime/support.cpp#L467) | Explanatory comments or spacing. | source comment (unverified): // Boolean support primitive: add/remove one surviving local witness. · [reviewed contract](#b0070) |
| [B0071 · 472–489](../../../../../src/runtime/support.cpp#L472) | Callable definition: std::optional&lt;TupleHandle&gt; count(const SupportNodeProgram& node,SupportRole role,const storage::AccountedTuple& key,bool add) | calls charge, relation, table, find; guard require(found.has_value(),"runtime_contract","removing an absent projected support key");; returns {}; {}; growth insert; source comment (unverified): // Boolean support primitive: add/remove one surviving local witness. · [reviewed contract](#b0071) |
| [B0072 · 490–492](../../../../../src/runtime/support.cpp#L490) | Explanatory comments or spacing. | source comment (unverified): // Change S once, then adjust its parent-key P and output-key E projections. · [reviewed contract](#b0072) |
| [B0073 · 493–508](../../../../../src/runtime/support.cpp#L493) | Callable definition: void survivor(const SupportNodeProgram& node,const storage::AccountedTuple& tuple,bool add) | calls charge, table, insert, note; guard const auto found=table.find(tuple, runtime.work()); require(found.has_value(),"runtime_contract","s…; growth insert; source comment (unverified): // Change S once, then adjust its parent-key P and output-key E projections. · [reviewed contract](#b0073) |
| [B0074 · 509–532](../../../../../src/runtime/support.cpp#L509) | Callable definition: void native(const SupportNodeProgram& node,const storage::AccountedTuple& tuple,bool add) | calls table, metric, record, size; guard const auto found=records.find(tuple, runtime.work()); require(found.has_value(),"runtime_contract",…; growth insert; 1 loop sites · [reviewed contract](#b0074) |
| [B0075 · 533–536](../../../../../src/runtime/support.cpp#L533) | Explanatory comments or spacing. | source comment (unverified): // Consume one child-presence bit transition, never its witness count. · [reviewed contract](#b0075) |
| [B0076 · 537–549](../../../../../src/runtime/support.cpp#L537) | Callable definition: void presence(const SupportNodeProgram& node,TupleHandle handle,RecordState& value,std::size_t slot,bool add,const storage::Accou… | calls charge, require, size, record; guard charge(); require(slot&lt;value.present.size() && value.present\[slot\]!=add,"runtime_contract","child m…; source comment (unverified): // Consume one child-presence bit transition, never its witness count. · [reviewed contract](#b0076) |
| [B0077 · 550–581](../../../../../src/runtime/support.cpp#L550) | Callable definition: void child(const Pending& event) | calls metric, program_edges, program_nodes, table; guard require(tuple!=nullptr,"runtime_contract","reverse separator index contains a stale native handle");; growth insert; 1 loop sites; source comment (unverified): // This update path materializes O(matching rows) accounted handles; · [reviewed contract](#b0077) |
| [B0078 · 582–597](../../../../../src/runtime/support.cpp#L582) | Callable definition: void drain() | calls empty, std::move, front, back; guard require(event.id&gt;0 && event.id&lt;=applied.size() && !applied\[static_cast&lt;std::size_t&gt;(event.id-1)\],"r…; 2 loop sites · [reviewed contract](#b0078) |
| [B0079 · 598–601](../../../../../src/runtime/support.cpp#L598) | declares types or opens a type body. |  · [reviewed contract](#b0079) |
| [B0080 · 602–602](../../../../../src/runtime/support.cpp#L602) | Type/record definition: enum class Phase |  · [reviewed contract](#b0080) |
| [B0081 · 603–624](../../../../../src/runtime/support.cpp#L603) | Type/record definition: struct Patch | returns restored.get_allocator().account(); found-&gt;second; growth copy_of, emplace · [reviewed contract](#b0081) |
| [B0082 · 625–637](../../../../../src/runtime/support.cpp#L625) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0082) |
| [B0083 · 638–680](../../../../../src/runtime/support.cpp#L638) | Callable definition: Group(std::shared_ptr&lt;Impl&gt; owner,std::shared_ptr&lt;const SupportJournal&gt; changes, std::uint64_t before,std::uint64_t after,bool ol… | calls runtime, std::move, storage_lease, detail::storage_lease; guard require(amount&lt;=std::numeric_limits&lt;std::uint64_t&gt;::max()-metrics.work &&; growth copy_of, emplace, emplace_back, insert, reserve; 3 loop sites · [reviewed contract](#b0083) |
| [B0084 · 681–684](../../../../../src/runtime/support.cpp#L681) | Callable definition: void acquire() | calls require, max; guard require(runtime-&gt;readers!=std::numeric_limits&lt;std::size_t&gt;::max(),"resource_limit","epoch view read… · [reviewed contract](#b0084) |
| [B0085 · 685–690](../../../../../src/runtime/support.cpp#L685) | Callable definition: void release() noexcept | calls std::terminate · [reviewed contract](#b0085) |
| [B0086 · 691–691](../../../../../src/runtime/support.cpp#L691) | declares callable signatures. |  · [reviewed contract](#b0086) |
| [B0087 · 692–692](../../../../../src/runtime/support.cpp#L692) | Callable definition: ~Group() | calls std::terminate, release · [reviewed contract](#b0087) |
| [B0088 · 693–693](../../../../../src/runtime/support.cpp#L693) | Closes surrounding scope/type. |  · [reviewed contract](#b0088) |
| [B0089 · 694–699](../../../../../src/runtime/support.cpp#L694) | Type/record definition: struct SupportRuntime::EpochView::Data | guard void readable() const { require(group-&gt;phase!=Group::Phase::aborted,"invalid_snapshot","epoch view … · [reviewed contract](#b0089) |
| [B0090 · 700–701](../../../../../src/runtime/support.cpp#L700) | declares types or opens a type body. |  · [reviewed contract](#b0090) |
| [B0091 · 702–707](../../../../../src/runtime/support.cpp#L702) | Type/record definition: struct Source |  · [reviewed contract](#b0091) |
| [B0092 · 708–708](../../../../../src/runtime/support.cpp#L708) | Type/record definition: struct Condition |  · [reviewed contract](#b0092) |
| [B0093 · 709–723](../../../../../src/runtime/support.cpp#L709) | Type/record definition: struct Frame |  · [reviewed contract](#b0093) |
| [B0094 · 724–736](../../../../../src/runtime/support.cpp#L724) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0094) |
| [B0095 · 737–741](../../../../../src/runtime/support.cpp#L737) | Callable definition: void publish() noexcept | calls lock · [reviewed contract](#b0095) |
| [B0096 · 742–776](../../../../../src/runtime/support.cpp#L742) | Callable definition: template&lt;class Make&gt; static resource::AccountedUnique&lt;Data&gt; create(const std::shared_ptr&lt;Impl&gt;& owner, ResultCursorOptions limits… | calls bool, configuration, cursor_clocks, cursor_now; returns cursor; 1 loop sites · [reviewed contract](#b0096) |
| [B0097 · 777–792](../../../../../src/runtime/support.cpp#L777) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0097) |
| [B0098 · 793–793](../../../../../src/runtime/support.cpp#L793) | Callable definition: const program::EnumerationProgram& program() const | calls view; returns fragment_program?fragment_program-&gt;view():runtime-&gt;state-&gt;enumeration · [reviewed contract](#b0098) |
| [B0099 · 794–797](../../../../../src/runtime/support.cpp#L794) | Callable definition: void resize_frames(Frames& target,std::size_t size) | calls reserve, size, emplace_back, memory; growth emplace_back, reserve; 1 loop sites · [reviewed contract](#b0099) |
| [B0100 · 798–798](../../../../../src/runtime/support.cpp#L798) | Explanatory comments or spacing. |  |
| [B0101 · 799–815](../../../../../src/runtime/support.cpp#L799) | Callable definition: Data(std::shared_ptr&lt;Impl&gt; owner,ResultCursorOptions limits,ResultView mode,bool initialize=true,ResultCursorMetrics* startup=nul… | calls runtime, std::move, storage_lease, detail::storage_lease · [reviewed contract](#b0101) |
| [B0102 · 816–873](../../../../../src/runtime/support.cpp#L816) | Callable definition: template&lt;class Bindings&gt; Data(std::shared_ptr&lt;EpochView::Data&gt; context,const Bindings& bindings,VisibleFragment fragment,ResultCu… | calls bind_values, std::move, require, program_nodes; guard require(fragment.root-&gt;value&lt;runtime-&gt;program_nodes().size() && runtime-&gt;program_nodes()\[fragment.r…; growth emplace, emplace_back, insert, push_back, reserve; 12 loop sites · [reviewed contract](#b0102) |
| [B0103 · 874–886](../../../../../src/runtime/support.cpp#L874) | Callable definition: Data(std::shared_ptr&lt;EpochView::Data&gt; context,const FixedAssignment& bindings,WitnessFragment fragment,ResultCursorOptions limits… | calls bind, std::move, survivors, variables; guard require(plan.layouts().size()!=std::numeric_limits&lt;std::size_t&gt;::max(),"storage_overflow","fragment…; growth push_back; 1 loop sites · [reviewed contract](#b0103) |
| [B0104 · 887–899](../../../../../src/runtime/support.cpp#L887) | Callable definition: Data(std::shared_ptr&lt;EpochView::Data&gt; context,NodeId id,ResultCursorOptions limits,ResultCursorMetrics* startup=nullptr) :Data(co… | calls bind, std::move, require, program_nodes; guard require(id.value&lt;runtime-&gt;program_nodes().size() && runtime-&gt;program_nodes()\[id.value\].visible_rela…; growth emplace, push_back; 1 loop sites; source comment (unverified): // A local E factor can contain rows even when the global answer is empty. · [reviewed contract](#b0104) |
| [B0105 · 900–926](../../../../../src/runtime/support.cpp#L900) | Callable definition: template&lt;class Separator&gt; Data(std::shared_ptr&lt;EpochView::Data&gt; context,NodeId id,const Separator& separator,ResultCursorOptions … | calls bind, std::move, require, program_nodes; guard require(id.value&lt;runtime-&gt;program_nodes().size() && runtime-&gt;program_nodes()\[id.value\].visible_rela…; growth emplace, push_back; 2 loop sites · [reviewed contract](#b0105) |
| [B0106 · 927–929](../../../../../src/runtime/support.cpp#L927) | Callable definition: void bind(std::shared_ptr&lt;EpochView::Data&gt; context,const FixedAssignment& bindings) | calls bind_values, std::move · [reviewed contract](#b0106) |
| [B0107 · 930–930](../../../../../src/runtime/support.cpp#L930) | Callable definition: static storage::ScalarView binding_value(const Value& value) | calls storage::borrow_scalar; returns storage::borrow_scalar(value) · [reviewed contract](#b0107) |
| [B0108 · 931–931](../../../../../src/runtime/support.cpp#L931) | Callable definition: static storage::ScalarView binding_value(const storage::ScalarView& value) | calls ; returns value · [reviewed contract](#b0108) |
| [B0109 · 932–949](../../../../../src/runtime/support.cpp#L932) | Callable definition: template&lt;class Bindings&gt; void bind_values(std::shared_ptr&lt;EpochView::Data&gt; context,const Bindings& bindings) | calls std::move, readable, metric, require; guard require(binding.variable.value&lt;plan.query().variables.size(),"invalid_binding","fixed variable is o…; growth copy_of, emplace; 1 loop sites · [reviewed contract](#b0109) |
| [B0110 · 950–980](../../../../../src/runtime/support.cpp#L950) | Callable definition: SupportEnumerationProgram survivors(const WitnessFragment& fragment) | calls require, program_nodes, size, selected; guard require(!(fragment.root && fragment.nodes),"invalid_fragment","fragment root and factor set are mut…; returns result; growth emplace, insert, push_back; 5 loop sites · [reviewed contract](#b0110) |
| [B0111 · 981–984](../../../../../src/runtime/support.cpp#L981) | Callable definition: void initialize(program::EnumerationProgram walk,Frames& target) | calls memory · [reviewed contract](#b0111) |
| [B0112 · 985–1008](../../../../../src/runtime/support.cpp#L985) | Callable definition: void initialize(program::EnumerationProgram walk,Frames& target,const MemoryMap&lt;VariableId,AssignmentSlot&gt;& outer) | calls metric, size, resize_frames, memory; growth emplace, push_back; 2 loop sites · [reviewed contract](#b0112) |
| [B0113 · 1009–1013](../../../../../src/runtime/support.cpp#L1009) | Callable definition: void link() noexcept | calls  · [reviewed contract](#b0113) |
| [B0114 · 1014–1017](../../../../../src/runtime/support.cpp#L1014) | Callable definition: ~Data() | calls close · [reviewed contract](#b0114) |
| [B0115 · 1018–1024](../../../../../src/runtime/support.cpp#L1018) | Callable definition: void metric(CursorWork& work,std::uint64_t CursorWork::* field,std::uint64_t amount=1) | calls require, max; guard require(amount&lt;=std::numeric_limits&lt;std::uint64_t&gt;::max()-used,"resource_limit","result cursor work… · [reviewed contract](#b0115) |
| [B0116 · 1025–1034](../../../../../src/runtime/support.cpp#L1025) | Callable definition: static void merge(CursorWork& target,const CursorWork& value) noexcept | calls ; 1 loop sites; source comment (unverified): // Every component is bounded by the already checked aggregate work. · [reviewed contract](#b0116) |
| [B0117 · 1035–1054](../../../../../src/runtime/support.cpp#L1035) | Callable definition: void close(ResultCursorState state,CursorTerminalReason reason) noexcept | calls cursor_now, cursor_add, clear, reset; 2 loop sites · [reviewed contract](#b0117) |
| [B0118 · 1055–1055](../../../../../src/runtime/support.cpp#L1055) | Callable definition: const storage::ScalarView& value(AssignmentSlot slot) const | calls at, values; returns frames.at(slot.step).selected-&gt;values().at(slot.field.value) · [reviewed contract](#b0118) |
| [B0119 · 1056–1056](../../../../../src/runtime/support.cpp#L1056) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0119) |
| [B0120 · 1057–1084](../../../../../src/runtime/support.cpp#L1057) | Callable definition: template&lt;bool Native&gt; EmittedTuple&lt;Native&gt; emit(CursorWork& work) | calls program, metric, require, value; guard require(value(equality.left)==value(equality.right),"runtime_contract","enumeration separator trave…; returns native; storage::Tuple::from_accounted(std::move(native)); growth push_back, reserve; 3 loop sites · [reviewed contract](#b0120) |
| [B0121 · 1085–1089](../../../../../src/runtime/support.cpp#L1085) | Callable definition: const storage::AccountedStorageTable::Journal* writer(RelationId relation) const | calls ; returns nullptr; &journal; 1 loop sites · [reviewed contract](#b0121) |
| [B0122 · 1090–1095](../../../../../src/runtime/support.cpp#L1090) | Callable definition: storage::ScalarView bound(const Source& source,const Frames& selected) const | calls at, view, require, values; guard require(rows\[source.slot.step\].selected!=nullptr,"runtime_contract","fragment binding refers to an …; returns fixed.at(source.variable).view()\[0\]; rows\[source.slot.step\].selected-&gt;values()\[source.slot.field.va… · [reviewed contract](#b0122) |
| [B0123 · 1096–1112](../../../../../src/runtime/support.cpp#L1096) | Callable definition: bool compatible(const storage::AccountedTuple& tuple,const Frame& frame,const SupportEnumerationStep& step,CursorWork& work,const… | calls indexes, fields, size, metric; returns false; false; 2 loop sites · [reviewed contract](#b0123) |
| [B0124 · 1113–1183](../../../../../src/runtime/support.cpp#L1113) | Callable definition: const storage::AccountedTuple* select(Frame& frame,const SupportEnumerationStep& step,CursorWork& work,const Frames& selected) | calls table, values, memory, reserve; guard require(bool(frame.key),"runtime_contract","bucketed visible factor has no bound separator key");; returns nullptr; tuple; growth clone, emplace, push_back, reserve; 3 loop sites · [reviewed contract](#b0124) |
| [B0125 · 1184–1189](../../../../../src/runtime/support.cpp#L1184) | Callable definition: void close_frame(Frame& frame,CursorWork& work) | calls metric, reset · [reviewed contract](#b0125) |
| [B0126 · 1190–1216](../../../../../src/runtime/support.cpp#L1190) | Callable definition: bool has_witness(CursorWork& work) | calls metric, select, close_frame, size; returns false; true; 1 loop sites; source comment (unverified): // This program is one complete survivor subtree. Running intersection · [reviewed contract](#b0126) |
| [B0127 · 1217–1242](../../../../../src/runtime/support.cpp#L1217) | Callable definition: template&lt;bool Native&gt; std::optional&lt;EmittedTuple&lt;Native&gt;&gt; advance(CursorWork& work) | calls metric, route, empty, require; guard require(!frames.empty(),"runtime_contract","tree enumeration has no root frame");; returns {}; emit&lt;Native&gt;(work); 1 loop sites · [reviewed contract](#b0127) |
| [B0128 · 1243–1265](../../../../../src/runtime/support.cpp#L1243) | Callable definition: template&lt;bool Native&gt; std::optional&lt;EmittedTuple&lt;Native&gt;&gt; produce() | calls require, cursor_now, storage_operation, merge; guard require(status!=ResultCursorState::failed,"invalid_cursor","result cursor failed and is closed");; returns {}; result · [reviewed contract](#b0128) |
| [B0129 · 1266–1266](../../../../../src/runtime/support.cpp#L1266) | Closes surrounding scope/type. |  · [reviewed contract](#b0129) |
| [B0130 · 1267–1271](../../../../../src/runtime/support.cpp#L1267) | Callable definition: void SupportRuntime::EpochView::Group::abort() noexcept | calls close, release, clear, reset; 1 loop sites · [reviewed contract](#b0130) |
| [B0131 · 1272–1272](../../../../../src/runtime/support.cpp#L1272) | Callable definition: SupportRuntime::ResultCursor::ResultCursor(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0131) |
| [B0132 · 1273–1273](../../../../../src/runtime/support.cpp#L1273) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0132) |
| [B0133 · 1274–1280](../../../../../src/runtime/support.cpp#L1274) | Callable definition: SupportRuntime::ResultCursor& SupportRuntime::ResultCursor::operator=(ResultCursor&& other) noexcept | calls std::move; returns *this · [reviewed contract](#b0133) |
| [B0134 · 1281–1281](../../../../../src/runtime/support.cpp#L1281) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0134) |
| [B0135 · 1282–1282](../../../../../src/runtime/support.cpp#L1282) | Callable definition: bool SupportRuntime::ResultCursor::active() const noexcept | calls ; returns data_ && data_-&gt;status==ResultCursorState::active · [reviewed contract](#b0135) |
| [B0136 · 1283–1283](../../../../../src/runtime/support.cpp#L1283) | Callable definition: ResultCursorState SupportRuntime::ResultCursor::state() const | calls require, bool; guard ResultCursorState SupportRuntime::ResultCursor::state() const { require(bool(data_),"invalid_cursor…; returns data_-&gt;status · [reviewed contract](#b0136) |
| [B0137 · 1284–1284](../../../../../src/runtime/support.cpp#L1284) | Callable definition: std::uint64_t SupportRuntime::ResultCursor::sequence() const | calls require, bool; guard std::uint64_t SupportRuntime::ResultCursor::sequence() const { require(bool(data_),"invalid_cursor"…; returns data_-&gt;epoch · [reviewed contract](#b0137) |
| [B0138 · 1285–1285](../../../../../src/runtime/support.cpp#L1285) | Callable definition: SupportOwnerId SupportRuntime::ResultCursor::owner() const | calls require, bool; guard SupportOwnerId SupportRuntime::ResultCursor::owner() const { require(bool(data_),"invalid_cursor","…; returns data_-&gt;identity · [reviewed contract](#b0138) |
| [B0139 · 1286–1286](../../../../../src/runtime/support.cpp#L1286) | Callable definition: const storage::TupleLayout& SupportRuntime::ResultCursor::layout() const | calls require, bool; guard const storage::TupleLayout& SupportRuntime::ResultCursor::layout() const { require(bool(data_),"inv…; returns data_-&gt;output_layout · [reviewed contract](#b0139) |
| [B0140 · 1287–1287](../../../../../src/runtime/support.cpp#L1287) | Callable definition: const ResultCursorMetrics& SupportRuntime::ResultCursor::metrics() const | calls require, bool; guard const ResultCursorMetrics& SupportRuntime::ResultCursor::metrics() const { require(bool(data_),"inv…; returns data_-&gt;metrics · [reviewed contract](#b0140) |
| [B0141 · 1288–1291](../../../../../src/runtime/support.cpp#L1288) | Callable definition: CursorObservation SupportRuntime::ResultCursor::observation() const | calls require, bool; guard require(bool(data_),"invalid_cursor","moved-from result cursor");; returns result · [reviewed contract](#b0141) |
| [B0142 · 1292–1297](../../../../../src/runtime/support.cpp#L1292) | Callable definition: void SupportRuntime::ResultCursor::cancel() noexcept | calls cursor_add, close · [reviewed contract](#b0142) |
| [B0143 · 1298–1301](../../../../../src/runtime/support.cpp#L1298) | Callable definition: std::optional&lt;storage::Tuple&gt; SupportRuntime::ResultCursor::next() try | calls require, bool, support_present; guard require(bool(data_),"invalid_cursor","moved-from result cursor");; returns data_-&gt;produce&lt;false&gt;() · [reviewed contract](#b0143) |
| [B0144 · 1302–1305](../../../../../src/runtime/support.cpp#L1302) | Callable definition: std::optional&lt;storage::AccountedTuple&gt; SupportRuntime::ResultCursor::next_native() try | calls require, bool, support_present; guard require(bool(data_),"invalid_cursor","moved-from result cursor");; returns data_-&gt;produce&lt;true&gt;() · [reviewed contract](#b0144) |
| [B0145 · 1306–1314](../../../../../src/runtime/support.cpp#L1306) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::results(ResultCursorOptions options,ResultView view) const try | calls storage_operation, impl, readable, require; guard require(view==ResultView::core \|\| view==ResultView::sql,"invalid_cursor_options","unknown result vi…; returns resource::make_accounted_unique&lt;ResultCursor::Data&gt;(d.storage_context-&gt;memory(),resource::MemoryPur…; growth make_accounted_unique · [reviewed contract](#b0145) |
| [B0146 · 1315–1315](../../../../../src/runtime/support.cpp#L1315) | Callable definition: SupportRuntime::EpochView::EpochView(std::shared_ptr&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0146) |
| [B0147 · 1316–1316](../../../../../src/runtime/support.cpp#L1316) | Callable definition: bool SupportRuntime::EpochView::valid() const noexcept | calls ; returns data_ && data_-&gt;group-&gt;phase!=Group::Phase::aborted · [reviewed contract](#b0147) |
| [B0148 · 1317–1317](../../../../../src/runtime/support.cpp#L1317) | Callable definition: bool SupportRuntime::EpochView::tentative() const noexcept | calls valid; returns valid() && data_-&gt;group-&gt;phase==Group::Phase::tentative · [reviewed contract](#b0148) |
| [B0149 · 1318–1318](../../../../../src/runtime/support.cpp#L1318) | Callable definition: SnapshotSide SupportRuntime::EpochView::side() const | calls require, bool; guard SnapshotSide SupportRuntime::EpochView::side() const { require(bool(data_),"invalid_snapshot","clos…; returns data_-&gt;side · [reviewed contract](#b0149) |
| [B0150 · 1319–1322](../../../../../src/runtime/support.cpp#L1319) | Callable definition: std::uint64_t SupportRuntime::EpochView::sequence() const | calls require, bool; guard require(bool(data_),"invalid_snapshot","closed epoch view");; returns data_-&gt;side==SnapshotSide::before?data_-&gt;group-&gt;before_sequence:data_-&gt;group-&gt;after_sequence · [reviewed contract](#b0150) |
| [B0151 · 1323–1325](../../../../../src/runtime/support.cpp#L1323) | Callable definition: SupportOwnerId SupportRuntime::EpochView::owner() const | calls require, bool; guard require(bool(data_),"invalid_snapshot","closed epoch view"); return data_-&gt;group-&gt;identity;; returns data_-&gt;group-&gt;identity · [reviewed contract](#b0151) |
| [B0152 · 1326–1326](../../../../../src/runtime/support.cpp#L1326) | Callable definition: const EpochViewMetrics& SupportRuntime::EpochView::metrics() const | calls require, bool; guard const EpochViewMetrics& SupportRuntime::EpochView::metrics() const { require(bool(data_),"invalid_s…; returns data_-&gt;group-&gt;metrics · [reviewed contract](#b0152) |
| [B0153 · 1327–1330](../../../../../src/runtime/support.cpp#L1327) | Callable definition: bool SupportRuntime::EpochView::has_answer() const | calls require, bool, readable; guard require(bool(data_),"invalid_snapshot","closed epoch view"); data_-&gt;readable();; returns data_-&gt;side==SnapshotSide::before?data_-&gt;group-&gt;before_answer:data_-&gt;group-&gt;after_answer · [reviewed contract](#b0153) |
| [B0154 · 1331–1331](../../../../../src/runtime/support.cpp#L1331) | Callable definition: void SupportRuntime::EpochView::close() noexcept | calls reset · [reviewed contract](#b0154) |
| [B0155 · 1332–1332](../../../../../src/runtime/support.cpp#L1332) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::EpochView::results(ResultCursorOptions options) const | calls completions; returns completions({}, {},options) · [reviewed contract](#b0155) |
| [B0156 · 1333–1340](../../../../../src/runtime/support.cpp#L1333) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::EpochView::completions(const FixedAssignment& fixed,VisibleFragment fragment,ResultC… | calls require, bool, readable, storage_operation; guard require(bool(data_),"invalid_snapshot","closed epoch view"); data_-&gt;readable();; returns resource::make_accounted_unique&lt;ResultCursor::Data&gt;(data_-&gt;group-&gt;runtime-&gt;storage_context-&gt;memory(…; growth make_accounted_unique · [reviewed contract](#b0156) |
| [B0157 · 1341–1348](../../../../../src/runtime/support.cpp#L1341) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::EpochView::completions_native(std::span&lt;const VariableBindingView&gt; fixed,VisibleFrag… | calls require, bool, readable, storage_operation; guard require(bool(data_),"invalid_snapshot","closed epoch view"); data_-&gt;readable();; returns resource::make_accounted_unique&lt;ResultCursor::Data&gt;(data_-&gt;group-&gt;runtime-&gt;storage_context-&gt;memory(…; growth make_accounted_unique · [reviewed contract](#b0157) |
| [B0158 · 1349–1356](../../../../../src/runtime/support.cpp#L1349) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::EpochView::witnesses(const FixedAssignment& fixed,WitnessFragment fragment,ResultCur… | calls require, bool, readable, storage_operation; guard require(bool(data_),"invalid_snapshot","closed epoch view"); data_-&gt;readable();; returns resource::make_accounted_unique&lt;ResultCursor::Data&gt;(data_-&gt;group-&gt;runtime-&gt;storage_context-&gt;memory(…; growth make_accounted_unique · [reviewed contract](#b0158) |
| [B0159 · 1357–1364](../../../../../src/runtime/support.cpp#L1357) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_keys(NodeId node,ResultCursorOptions options) const try | calls require, bool, readable, storage_operation; guard require(bool(data_),"invalid_snapshot","closed epoch view"); data_-&gt;readable();; returns resource::make_accounted_unique&lt;ResultCursor::Data&gt;(data_-&gt;group-&gt;runtime-&gt;storage_context-&gt;memory(…; growth make_accounted_unique · [reviewed contract](#b0159) |
| [B0160 · 1365–1372](../../../../../src/runtime/support.cpp#L1365) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_bucket(NodeId node,const Row& separator,ResultCursorOptions optio… | calls require, bool, readable, storage_operation; guard require(bool(data_),"invalid_snapshot","closed epoch view"); data_-&gt;readable();; returns resource::make_accounted_unique&lt;ResultCursor::Data&gt;(data_-&gt;group-&gt;runtime-&gt;storage_context-&gt;memory(…; growth make_accounted_unique · [reviewed contract](#b0160) |
| [B0161 · 1373–1380](../../../../../src/runtime/support.cpp#L1373) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_bucket_native(NodeId node,storage::RowView separator,ResultCursor… | calls require, bool, readable, storage_operation; guard require(bool(data_),"invalid_snapshot","closed epoch view"); data_-&gt;readable();; returns resource::make_accounted_unique&lt;ResultCursor::Data&gt;(data_-&gt;group-&gt;runtime-&gt;storage_context-&gt;memory(…; growth make_accounted_unique · [reviewed contract](#b0161) |
| [B0162 · 1381–1386](../../../../../src/runtime/support.cpp#L1381) | Callable definition: SupportRuntime::EpochView SupportRuntime::current_view(EpochViewOptions options) const try | calls storage_operation, impl, readable, answer; returns EpochView(std::move(data)); growth make_accounted_shared · [reviewed contract](#b0162) |
| [B0163 · 1387–1389](../../../../../src/runtime/support.cpp#L1387) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::completions(const FixedAssignment& fixed,VisibleFragment fragment,ResultCursorOption… | calls current_view, completions; returns current_view().completions(fixed,fragment,options) · [reviewed contract](#b0163) |
| [B0164 · 1390–1392](../../../../../src/runtime/support.cpp#L1390) | Callable definition: SupportRuntime::ResultCursor SupportRuntime::witnesses(const FixedAssignment& fixed,WitnessFragment fragment,ResultCursorOptions … | calls current_view, witnesses, std::move; returns current_view().witnesses(fixed,std::move(fragment),options) · [reviewed contract](#b0164) |
| [B0165 · 1393–1403](../../../../../src/runtime/support.cpp#L1393) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0165) |
| [B0166 · 1404–1411](../../../../../src/runtime/support.cpp#L1404) | Callable definition: Data(std::shared_ptr&lt;Impl&gt; value,std::uint64_t sequence,SetOperation sign) :owner(std::move(value)),storage_lease(detail::storage… | calls owner, std::move, storage_lease, detail::storage_lease; growth make_accounted_shared, make_accounted_unique · [reviewed contract](#b0166) |
| [B0167 · 1412–1413](../../../../../src/runtime/support.cpp#L1412) | Member/declaration region. |  · [reviewed contract](#b0167) |
| [B0168 · 1414–1414](../../../../../src/runtime/support.cpp#L1414) | Callable definition: ~Data() | calls rollback · [reviewed contract](#b0168) |
| [B0169 · 1415–1417](../../../../../src/runtime/support.cpp#L1415) | Callable definition: Impl& active() const | calls require, bool; guard require(bool(owner) && bool(transaction),"invalid_epoch","prepared epoch is closed"); return *owner;; returns *owner · [reviewed contract](#b0169) |
| [B0170 · 1418–1427](../../../../../src/runtime/support.cpp#L1418) | Callable definition: void rollback() noexcept | calls observe, abort, reset, clear · [reviewed contract](#b0170) |
| [B0171 · 1428–1438](../../../../../src/runtime/support.cpp#L1428) | Callable definition: bool stage_tuple(const SupportNodeProgram& node,const storage::AccountedTuple& tuple) | calls storage_operation, active, table, find; guard require(prefix!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"sequence_overflow","logical stage prefix…; returns false; true; growth insert · [reviewed contract](#b0171) |
| [B0172 · 1439–1439](../../../../../src/runtime/support.cpp#L1439) | Closes surrounding scope/type. |  · [reviewed contract](#b0172) |
| [B0173 · 1440–1440](../../../../../src/runtime/support.cpp#L1440) | Callable definition: SupportRuntime::PendingEpoch::PendingEpoch(resource::AccountedUnique&lt;Data&gt; data) noexcept:data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0173) |
| [B0174 · 1441–1441](../../../../../src/runtime/support.cpp#L1441) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0174) |
| [B0175 · 1442–1445](../../../../../src/runtime/support.cpp#L1442) | Callable definition: SupportRuntime::PendingEpoch& SupportRuntime::PendingEpoch::operator=(PendingEpoch&& other) noexcept | calls ; returns *this · [reviewed contract](#b0175) |
| [B0176 · 1446–1446](../../../../../src/runtime/support.cpp#L1446) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0176) |
| [B0177 · 1447–1447](../../../../../src/runtime/support.cpp#L1447) | Callable definition: bool SupportRuntime::PendingEpoch::active() const noexcept | calls ; returns data_ && data_-&gt;owner && data_-&gt;transaction · [reviewed contract](#b0177) |
| [B0178 · 1448–1448](../../../../../src/runtime/support.cpp#L1448) | Callable definition: void SupportRuntime::PendingEpoch::rollback() noexcept | calls rollback · [reviewed contract](#b0178) |
| [B0179 · 1449–1461](../../../../../src/runtime/support.cpp#L1449) | Callable definition: bool SupportRuntime::PendingEpoch::stage(NodeId id,const Row& values) try | calls require, bool, use_count, reset; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch");; returns data_-&gt;stage_tuple(node,tuple) · [reviewed contract](#b0179) |
| [B0180 · 1462–1464](../../../../../src/runtime/support.cpp#L1462) | Callable definition: const SupportEpoch& SupportRuntime::PendingEpoch::preview() const | calls require, bool, active; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch"); static_cast&lt;void&gt;(data_-&gt;active()…; returns data_-&gt;output · [reviewed contract](#b0180) |
| [B0181 · 1465–1478](../../../../../src/runtime/support.cpp#L1465) | Callable definition: bool SupportRuntime::PendingEpoch::stage_native(NodeId id,const storage::AccountedTuple& tuple) try | calls require, bool, use_count, reset; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch");; returns data_-&gt;stage_tuple(node,tuple) · [reviewed contract](#b0181) |
| [B0182 · 1479–1483](../../../../../src/runtime/support.cpp#L1479) | Callable definition: SupportSnapshot SupportRuntime::PendingEpoch::snapshot() const try | calls require, bool, storage_operation, active; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch");; returns data_-&gt;active().snapshot(data_-&gt;output.sequence) · [reviewed contract](#b0182) |
| [B0183 · 1484–1497](../../../../../src/runtime/support.cpp#L1484) | Callable definition: SupportRuntime::EpochView SupportRuntime::PendingEpoch::view(SnapshotSide side,EpochViewOptions options) try | calls require, bool, storage_operation, active; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch");; returns EpochView(std::move(view)); growth make_accounted_shared · [reviewed contract](#b0183) |
| [B0184 · 1498–1501](../../../../../src/runtime/support.cpp#L1498) | Callable definition: SupportRuntime::PendingEpoch::Checkpoint SupportRuntime::PendingEpoch::checkpoint() const | calls require, bool, active, size; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch"); const auto& d=data_-&gt;active();; returns {d.owner,data_-&gt;output.sequence,data_-&gt;prefix,data_-&gt;journal-&gt;records.size(),data_-&gt;output.has_answ… · [reviewed contract](#b0184) |
| [B0185 · 1502–1508](../../../../../src/runtime/support.cpp#L1502) | Callable definition: std::span&lt;const JournalRecord&gt; SupportRuntime::PendingEpoch::stage_records(const Checkpoint& before) const | calls require, bool, active, size; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch"); const auto& d=data_-&gt;active();; returns std::span&lt;const JournalRecord&gt;{data_-&gt;journal-&gt;records}.subspan(before.records) · [reviewed contract](#b0185) |
| [B0186 · 1509–1523](../../../../../src/runtime/support.cpp#L1509) | Callable definition: SupportRuntime::EpochView SupportRuntime::PendingEpoch::stage_view(const Checkpoint& before,SnapshotSide side,EpochViewOptions op… | calls stage_records, storage_operation, active, require; guard require(side==SnapshotSide::before \|\| side==SnapshotSide::after,"invalid_snapshot","unknown snapsho…; returns EpochView(std::move(view)); growth make_accounted_shared · [reviewed contract](#b0186) |
| [B0187 · 1524–1539](../../../../../src/runtime/support.cpp#L1524) | Callable definition: SupportEpoch SupportRuntime::PendingEpoch::commit() | calls require, bool, active, observe; guard require(bool(data_),"invalid_epoch","moved-from prepared epoch"); auto& d=data_-&gt;active();; returns result; source comment (unverified): // Validation above is the only throwing path. All output already exists; · [reviewed contract](#b0187) |
| [B0188 · 1540–1548](../../../../../src/runtime/support.cpp#L1540) | Callable definition: SupportRuntime::PendingEpoch SupportRuntime::begin_epoch(std::uint64_t sequence,SetOperation operation) try | calls storage_operation, impl, writable, require; guard require(d.sequence!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"sequence_overflow","logical update s…; returns PendingEpoch(std::move(data)); growth insert, make_accounted_unique · [reviewed contract](#b0188) |
| [B0189 · 1549–1549](../../../../../src/runtime/support.cpp#L1549) | Explanatory comments or spacing. |  |
| [B0190 · 1550–1661](../../../../../src/runtime/support.cpp#L1550) | Callable definition: void SupportRuntime::initialize_native(std::span&lt;const detail::NativeSeed&gt; seeds,BuildOptions options,BuildMetrics& metrics) | calls storage_operation, impl, writable, ~RestoreObservation; guard require(d.sequence==0,"runtime_contract","initialization requires an unpublished empty support owne…; growth emplace, emplace_back, insert, make_accounted_unique, push_back; 13 loop sites; source comment (unverified): // Initialization is not a sequence-zero stream of ordinary observed updates. · [reviewed contract](#b0190) |
| [B0191 · 1662–1662](../../../../../src/runtime/support.cpp#L1662) | Explanatory comments or spacing. |  |
| [B0192 · 1663–1663](../../../../../src/runtime/support.cpp#L1663) | Callable definition: void SupportRuntime::seed_sequence(std::uint64_t sequence) noexcept | calls  · [reviewed contract](#b0192) |
| [B0193 · 1664–1664](../../../../../src/runtime/support.cpp#L1664) | Explanatory comments or spacing. |  |
| [B0194 · 1665–1666](../../../../../src/runtime/support.cpp#L1665) | Callable definition: SupportRuntime::SupportRuntime(PhysicalPlan plan,SupportOptions options) :SupportRuntime(plan,options,detail::storage_context(pla… | calls SupportRuntime, detail::storage_context · [reviewed contract](#b0194) |
| [B0195 · 1667–1673](../../../../../src/runtime/support.cpp#L1667) | Callable definition: SupportRuntime::SupportRuntime(CompiledProgram source,SupportOptions options) try :impl_(\[&\] { auto context=detail::new_storage_c… | calls impl_, detail::new_storage_context, operation, CompiledProgram::freeze; returns resource::make_accounted_shared&lt;Impl&gt;(context-&gt;memory(),resource::MemoryPurpose::support_metadata,s…; growth make_accounted_shared · [reviewed contract](#b0195) |
| [B0196 · 1674–1675](../../../../../src/runtime/support.cpp#L1674) | Callable definition: SupportRuntime::SupportRuntime(PhysicalPlan plan,SupportOptions options,std::shared_ptr&lt;detail::StorageWorkContext&gt; context) try … | calls impl_, detail::validate_storage_context, operation, memory; returns resource::make_accounted_shared&lt;Impl&gt;(context-&gt;memory(),resource::MemoryPurpose::support_metadata,s…; growth make_accounted_shared · [reviewed contract](#b0196) |
| [B0197 · 1676–1677](../../../../../src/runtime/support.cpp#L1676) | Callable definition: SupportRuntime::SupportRuntime(CompiledProgram plan,SupportOptions options,std::shared_ptr&lt;detail::StorageWorkContext&gt; context) t… | calls impl_, detail::validate_storage_context, operation, memory; returns resource::make_accounted_shared&lt;Impl&gt;(context-&gt;memory(),resource::MemoryPurpose::support_metadata,s…; growth make_accounted_shared · [reviewed contract](#b0197) |
| [B0198 · 1678–1679](../../../../../src/runtime/support.cpp#L1678) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0198) |
| [B0199 · 1680–1680](../../../../../src/runtime/support.cpp#L1680) | Callable definition: SupportRuntime& SupportRuntime::operator=(SupportRuntime&& other) noexcept | calls ; returns *this · [reviewed contract](#b0199) |
| [B0200 · 1681–1681](../../../../../src/runtime/support.cpp#L1681) | Callable definition: SupportRuntime::Impl& SupportRuntime::impl() const | calls require, bool; guard SupportRuntime::Impl& SupportRuntime::impl() const { require(bool(impl_),"invalid_runtime","moved-f…; returns *impl_ · [reviewed contract](#b0200) |
| [B0201 · 1682–1682](../../../../../src/runtime/support.cpp#L1682) | Callable definition: const CompiledProgram& SupportRuntime::plan() const | calls impl; returns impl().plan · [reviewed contract](#b0201) |
| [B0202 · 1683–1683](../../../../../src/runtime/support.cpp#L1683) | Callable definition: const SupportOptions& SupportRuntime::options() const | calls impl; returns impl().options · [reviewed contract](#b0202) |
| [B0203 · 1684–1684](../../../../../src/runtime/support.cpp#L1684) | Callable definition: resource::MemoryStatistics SupportRuntime::accounted_memory_statistics() const | calls impl, memory, statistics; returns impl().storage_context-&gt;memory().statistics() · [reviewed contract](#b0203) |
| [B0204 · 1685–1685](../../../../../src/runtime/support.cpp#L1685) | Callable definition: SupportOwnerId SupportRuntime::owner() const | calls impl; returns impl().owner · [reviewed contract](#b0204) |
| [B0205 · 1686–1686](../../../../../src/runtime/support.cpp#L1686) | Callable definition: std::uint64_t SupportRuntime::sequence() const | calls impl; returns impl().sequence · [reviewed contract](#b0205) |
| [B0206 · 1687–1687](../../../../../src/runtime/support.cpp#L1687) | Callable definition: bool SupportRuntime::ready() const | calls impl; returns !d.updating && d.readers==0 · [reviewed contract](#b0206) |
| [B0207 · 1688–1688](../../../../../src/runtime/support.cpp#L1688) | Callable definition: bool SupportRuntime::has_answer() const | calls impl, readable, answer; returns d.answer(*d.state) · [reviewed contract](#b0207) |
| [B0208 · 1689–1692](../../../../../src/runtime/support.cpp#L1689) | Callable definition: const storage::TupleLayout& SupportRuntime::result_layout(ResultView view) const | calls impl, require; guard const auto& d=impl(); require(view==ResultView::core \|\| view==ResultView::sql,"invalid_cursor_optio…; returns view==ResultView::sql?d.sql_output:d.core_output · [reviewed contract](#b0208) |
| [B0209 · 1693–1716](../../../../../src/runtime/support.cpp#L1693) | Callable definition: SupportEpoch SupportRuntime::apply(const NativeSetUpdate& update) try | calls storage_operation, impl, writable, require; guard auto& d=impl(); d.writable(); require(d.sequence!=std::numeric_limits&lt;std::uint64_t&gt;::max(),"sequen…; returns output; pending.commit(); growth insert · [reviewed contract](#b0209) |
| [B0210 · 1717–1717](../../../../../src/runtime/support.cpp#L1717) | Explanatory comments or spacing. |  |
| [B0211 · 1718–1723](../../../../../src/runtime/support.cpp#L1718) | Callable definition: std::optional&lt;SupportHandle&gt; SupportRuntime::find(NodeId id,SupportRole role,const Row& values) const try | calls storage_operation, impl, readable, node; returns found ? std::optional&lt;SupportHandle&gt;{d.handle(id,role,*found)} : std::nullopt · [reviewed contract](#b0211) |
| [B0212 · 1724–1726](../../../../../src/runtime/support.cpp#L1724) | Callable definition: const storage::AccountedLayout& SupportRuntime::relation_layout(NodeId id,SupportRole role) const & | calls impl, readable, table, relation; returns d.state-&gt;storage.table(relation(d.node(id),role)).layout() · [reviewed contract](#b0212) |
| [B0213 · 1727–1733](../../../../../src/runtime/support.cpp#L1727) | Callable definition: std::optional&lt;storage::Tuple&gt; SupportRuntime::get(SupportHandle handle) const try | calls storage_operation, impl, readable, require; guard auto& d=impl(); d.readable(); require(handle.owner==d.owner,"foreign_support_handle","support handl…; returns tuple ? std::optional&lt;storage::Tuple&gt;{d.plan_tuple(*tuple)} : std::nullopt · [reviewed contract](#b0213) |
| [B0214 · 1734–1745](../../../../../src/runtime/support.cpp#L1734) | Callable definition: storage::ArenaStatistics SupportRuntime::storage_statistics() const | calls impl, readable, require, max; guard require(value&lt;=std::numeric_limits&lt;std::size_t&gt;::max()-target,"storage_overflow","aggregate arena s…; returns total; 1 loop sites · [reviewed contract](#b0214) |
| [B0215 · 1746–1746](../../../../../src/runtime/support.cpp#L1746) | Callable definition: std::optional&lt;CursorObservation&gt; SupportRuntime::last_cursor_observation() const | calls impl; returns impl().last_cursor · [reviewed contract](#b0215) |
| [B0216 · 1747–1759](../../../../../src/runtime/support.cpp#L1747) | Callable definition: template&lt;class Gauges&gt; Gauges SupportRuntime::Impl::state_gauges(Gauges result) const | calls readable, reserve, program_nodes, size; returns result; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0216) |
| [B0217 · 1760–1762](../../../../../src/runtime/support.cpp#L1760) | Callable definition: CommittedStateGauges SupportRuntime::committed_state_gauges() const | calls impl, state_gauges; returns impl().state_gauges(CommittedStateGauges{}) · [reviewed contract](#b0217) |
| [B0218 · 1763–1765](../../../../../src/runtime/support.cpp#L1763) | Callable definition: CapturedStateGauges SupportRuntime::capture_state_gauges() const | calls impl, state_gauges, CapturedStateGauges, account; returns d.state_gauges(CapturedStateGauges(d.state-&gt;compiled.account())) · [reviewed contract](#b0218) |
| [B0219 · 1766–1769](../../../../../src/runtime/support.cpp#L1766) | Callable definition: SupportSnapshot SupportRuntime::snapshot() const try | calls storage_operation, impl, readable, snapshot; returns d.snapshot(d.sequence) · [reviewed contract](#b0219) |
| [B0220 · 1770–1776](../../../../../src/runtime/support.cpp#L1770) | Callable definition: detail::AccountedRowSet SupportRuntime::record_rows(NodeId id) const try | calls storage_operation, impl, readable, node; returns result; growth insert; 1 loop sites · [reviewed contract](#b0220) |
| [B0221 · 1777–1799](../../../../../src/runtime/support.cpp#L1777) | Callable definition: SupportSnapshot SupportRuntime::Impl::snapshot(std::uint64_t visible_sequence) const | calls storage_operation, answer, program_nodes, table; returns values; result; growth push_back; 4 loop sites · [reviewed contract](#b0221) |
| [B0222 · 1800–1800](../../../../../src/runtime/support.cpp#L1800) | Explanatory comments or spacing. |  |
| [B0223 · 1801–1829](../../../../../src/runtime/support.cpp#L1801) | Callable definition: CanonicalSupportState SupportRuntime::canonical_state() const try | calls storage_operation, impl, readable, std::string; returns a.values&lt;b.values; a.key&lt;b.key; growth insert, push_back; 4 loop sites · [reviewed contract](#b0223) |
| [B0224 · 1830–1830](../../../../../src/runtime/support.cpp#L1830) | Explanatory comments or spacing. |  |
| [B0225 · 1831–1974](../../../../../src/runtime/support.cpp#L1831) | Callable definition: InvariantReport SupportRuntime::inspect_invariants(InspectionOptions options) const try | calls storage_operation, impl, readable, context; guard require(table.relation()==definition.id && table.layout().same_token(d.state-&gt;storage.layout(defini…; returns std::move(context.report); growth insert; 19 loop sites; source comment (unverified): // Storage checks are independent of support metadata. These precharges · [reviewed contract](#b0225) |
| [B0226 · 1975–1976](../../../../../src/runtime/support.cpp#L1975) | controls preprocessing. |  · [reviewed contract](#b0226) |
| [B0227 · 1977–1981](../../../../../src/runtime/support.cpp#L1977) | Callable definition: std::optional&lt;RuntimeStorageWork&gt; RuntimeTestProbe::index_work(const SupportRuntime& runtime) | calls impl, indexed, limit, observed_work; returns {}; RuntimeStorageWork{context-&gt;limit(),context-&gt;observed_work(),context-&gt;fresh_operations()} · [reviewed contract](#b0227) |
| [B0228 · 1982–1982](../../../../../src/runtime/support.cpp#L1982) | Callable definition: resource::MemoryAccount RuntimeTestProbe::memory_account(const SupportRuntime& runtime) | calls impl, memory; returns runtime.impl().storage_context-&gt;memory() · [reviewed contract](#b0228) |
| [B0229 · 1983–1990](../../../../../src/runtime/support.cpp#L1983) | Callable definition: SupportValueState RuntimeTestProbe::record_metadata(const SupportRuntime& runtime,SupportHandle handle) | calls impl, readable, require, node; guard require(handle.owner==d.owner && handle.role==SupportRole::records,"invalid_probe","metadata probe …; returns {true,found-&gt;second.satisfied,retained_flags(found-&gt;second),{}} · [reviewed contract](#b0229) |
| [B0230 · 1991–1998](../../../../../src/runtime/support.cpp#L1991) | Callable definition: std::size_t RuntimeTestProbe::set_satisfied(SupportRuntime& runtime,NodeId id,const Row& row,std::size_t value) | calls storage_operation, impl, writable, node; guard require(handle.has_value(),"runtime_contract","probe record is absent");; returns std::exchange(count,value) · [reviewed contract](#b0230) |
| [B0231 · 1999–2006](../../../../../src/runtime/support.cpp#L1999) | Callable definition: std::uint64_t RuntimeTestProbe::set_projection(SupportRuntime& runtime,NodeId id,bool visible,const Row& row,std::uint64_t value) | calls storage_operation, impl, writable, node; guard const auto handle=table.find(table.layout().tuple(row), d.work()); require(handle.has_value(),"runt…; returns std::exchange(count,value) · [reviewed contract](#b0231) |
| [B0232 · 2007–2008](../../../../../src/runtime/support.cpp#L2007) | controls preprocessing. |  · [reviewed contract](#b0232) |
| [B0233 · 2009–2053](../../../../../src/runtime/support.cpp#L2009) | Callable definition: void SupportRuntime::check_invariants() const try | calls storage_operation, impl, readable, check_invariants; guard require(records.size()==metadata.records.size(),"runtime_contract","record metadata cardinality dif…; growth insert; 7 loop sites · [reviewed contract](#b0233) |
| [B0234 · 2054–2054](../../../../../src/runtime/support.cpp#L2054) | Callable definition: std::shared_ptr&lt;detail::ObservationState&gt; SupportRuntime::observation_state() const | calls impl; returns impl().observation · [reviewed contract](#b0234) |
| [B0235 · 2055–2057](../../../../../src/runtime/support.cpp#L2055) | Callable definition: ObservationSnapshot SupportRuntime::observations() const | calls impl, detail::observation_snapshot; returns detail::observation_snapshot(d.observation,d.options.observation) · [reviewed contract](#b0235) |
| [B0236 · 2058–2060](../../../../../src/runtime/support.cpp#L2058) | Callable definition: ObservationTrace SupportRuntime::observation_trace() const | calls impl, detail::observation_trace; returns detail::observation_trace(d.observation,d.options.observation) · [reviewed contract](#b0236) |
| [B0237 · 2061–2063](../../../../../src/runtime/support.cpp#L2061) | Callable definition: CapturedObservationTrace SupportRuntime::capture_observation_trace() const | calls impl, detail::capture_observation_trace, account; returns detail::capture_observation_trace(d.observation,d.options.observation,d.state-&gt;compiled.account()) · [reviewed contract](#b0237) |
| [B0238 · 2064–2066](../../../../../src/runtime/support.cpp#L2064) | declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0238) |
| [B0239 · 2067–2069](../../../../../src/runtime/support.cpp#L2067) | Callable definition: void SupportRuntime::configure_workload_statistics(const workload::Options& options) | calls impl, writable, configure · [reviewed contract](#b0239) |
| [B0240 · 2070–2072](../../../../../src/runtime/support.cpp#L2070) | Callable definition: void SupportRuntime::reset_workload_statistics() | calls impl, writable, reset · [reviewed contract](#b0240) |
| [B0241 · 2073–2075](../../../../../src/runtime/support.cpp#L2073) | Callable definition: workload::Snapshot SupportRuntime::workload_statistics() const | calls impl, snapshot; returns d.workload.snapshot(d.state-&gt;compiled,d.owner,d.sequence,d.updating) · [reviewed contract](#b0241) |
| [B0242 · 2076–2076](../../../../../src/runtime/support.cpp#L2076) | Callable definition: workload::detail::State& SupportRuntime::workload_state() const | calls impl; returns impl().workload · [reviewed contract](#b0242) |
| [B0243 · 2077–2077](../../../../../src/runtime/support.cpp#L2077) | Callable definition: const CompiledProgram& SupportRuntime::compiled_program() const | calls impl; returns impl().state-&gt;compiled · [reviewed contract](#b0243) |
| [B0244 · 2078–2078](../../../../../src/runtime/support.cpp#L2078) | Callable definition: std::shared_ptr&lt;detail::StorageWorkContext&gt; SupportRuntime::storage_context() const | calls impl; returns impl().storage_context · [reviewed contract](#b0244) |
| [B0245 · 2079–2081](../../../../../src/runtime/support.cpp#L2079) | Imports dependencies; declares namespace scope. | source comment (unverified): // namespace crown::runtime · [reviewed contract](#b0245) |
| [B0246 · 2082–2120](../../../../../src/runtime/support.cpp#L2082) | Callable definition: void SupportRuntime::append_statistics(statistics::detail::OwnerBuilder& builder,const statistics::Selection& selection) const try | calls storage_operation, impl, append, node; guard require(!selection.fields,"invalid_statistics_request","support distribution uses complete stored s…; 1 loop sites; source comment (unverified): // Exhaustion is an incomplete distribution; corruption/ownership faults · [reviewed contract](#b0246) |
| [B0247 · 2121–2123](../../../../../src/runtime/support.cpp#L2121) | Callable definition: statistics::OwnerCapture SupportRuntime::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) co… | calls capture_statistics_view; returns capture_statistics_view(request,limits) · [reviewed contract](#b0247) |
| [B0248 · 2124–2129](../../../../../src/runtime/support.cpp#L2124) | Callable definition: statistics::OwnerCapture SupportRuntime::capture_statistics_view(statistics::OwnerRequestView request,statistics::Limits limits) … | calls storage_operation, impl, active, append_statistics; returns builder.finish(); 1 loop sites · [reviewed contract](#b0248) |
| [B0249 · 2130–2132](../../../../../src/runtime/support.cpp#L2130) | Callable definition: statistics::Freshness SupportRuntime::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) … | calls impl, statistics::compare_freshness, stamp; returns statistics::compare_freshness(captured.stamp(),{d.owner,d.sequence,statistics::OwnerLayer::support}… · [reviewed contract](#b0249) |
| [B0250 · 2133–2135](../../../../../src/runtime/support.cpp#L2133) | declares namespace scope. |  · [reviewed contract](#b0250) |
| [B0251 · 2136–2154](../../../../../src/runtime/support.cpp#L2136) | Callable definition: void Access::append(Builder& builder,const SupportRuntime& owner) | calls impl, operation, relations, table; 3 loop sites · [reviewed contract](#b0251) |
| [B0252 · 2155–2163](../../../../../src/runtime/support.cpp#L2155) | Callable definition: Attempt Access::capture(const SupportRuntime& owner,Limits limits) noexcept | calls attempt, impl, builder, account; returns attempt(\[&\](Usage& usage) {; builder.finish() · [reviewed contract](#b0252) |
| [B0253 · 2164–2164](../../../../../src/runtime/support.cpp#L2164) | Closes surrounding scope/type. |  · [reviewed contract](#b0253) |

## B0001

[Lines 1–23](../../../../../src/runtime/support.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "crown/runtime/support.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble Boolean support coordination, native storage, inspection and statistics implementations. |
| inputs / outputs | Includes public and private helpers and optional test probe. |
| invariants | No nullable/bag kernel or global live-view relation is introduced by this translation unit. |
| ownership | Compile-time declarations only. |
| failure | Dependency/type mismatch is a compilation error. |
| cost | No runtime work for includes. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0002

[Lines 24–26](../../../../../src/runtime/support.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise the established public diagnostic when a local precondition fails. |
| inputs / outputs | Boolean, code and message return normally when true; otherwise throw owning Error. |
| invariants | Success never constructs diagnostic strings. |
| ownership | String views are borrowed only during the call; Error owns the failure text. |
| failure | False allocates/throws the established diagnostic; this helper performs no recovery. |
| cost | O(1) success; text/exception costs belong to failure. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 27–27](../../../../../src/runtime/support.cpp#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Failure> [[noreturn]] void support_present(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate a typed native failure at a public support boundary. |
| inputs / outputs | Native failure code/what become public Error strings. |
| invariants | Only native typed failures are translated; public Error and bad_alloc are not swallowed. |
| ownership | Failure text is copied into the public diagnostic. |
| failure | Always throws; callers use function-try handlers after cleanup/unwinding. |
| cost | Failure-path string/exception construction; no successful operation invokes this helper. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 28–34](../../../../../src/runtime/support.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOwnerId new_owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign a unique public logical runtime identity. |
| inputs / outputs | Process-wide atomic scalar produces a positive SupportOwnerId. |
| invariants | IDs never wrap or reuse; ordering does not synchronize runtime data. |
| ownership | Static atomic only, no registry or per-owner allocation. |
| failure | support_overflow rejects exhaustion before publishing an ID. |
| cost | Compare/exchange retry loop; admission only, not a per-row operation. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 35–35](../../../../../src/runtime/support.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Internal metadata IDs must not consume the public runtime-owner sequence.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document independent metadata and public-runtime identity sequences. |
| inputs / outputs | The following new_metadata_owner has a separate atomic authority. |
| invariants | Metadata allocation must not perturb public SupportOwnerId numbering. |
| ownership | Comment only. |
| failure | No runtime behavior. |
| cost | No runtime work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 36–42](../../../../../src/runtime/support.cpp#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t new_metadata_owner()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assign internal support-node accounting attribution independently of public IDs. |
| inputs / outputs | Process-wide private atomic produces a positive metadata ID. |
| invariants | Does not consume or authorize a public support handle. |
| ownership | Static scalar; each NodeState stores its attribution. |
| failure | MemoryFailure overflow on exhaustion. |
| cost | Admission compare/exchange retry, not a table scan or mutation-time map. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 43–46](../../../../../src/runtime/support.cpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using MemoryVector=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind private vectors/maps/sets to actual original-account allocation. |
| inputs / outputs | MemoryAllocator aliases for flat and nested container nodes. |
| invariants | Nested owning members still propagate their account explicitly; aliases create no cap. |
| ownership | Allocator instances retain the supplied account. |
| failure | Later container growth may fail at the account/upstream allocation boundary. |
| cost | Aliases have no dispatch cost; real node/capacity requests are charged. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0008

[Lines 47–49](../../../../../src/runtime/support.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Map> Map memory_map(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an empty ordered container with the intended account and memory purpose. |
| inputs / outputs | Account and optional purpose return an empty Map with matching allocator. |
| invariants | Nested payloads must separately use appropriate allocators. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Only ordinary empty-container construction applies; later insertions fund their nodes. |
| cost | Fixed empty-map metadata; no resident-node allocation. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0009

[Lines 50–55](../../../../../src/runtime/support.cpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CompactRowLess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare accounted keys without exporting owning Rows. |
| inputs / outputs | AccountedRow/RowView pairs produce a transparent exact lexicographic order. |
| invariants | All overloads order the same ScalarView sequence. |
| ownership | Arguments are borrowed; comparator retains nothing. |
| failure | Requires valid borrowed views. |
| cost | May inspect all compared fields/deep bytes; no owning row copy. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 57–63](../../../../../src/runtime/support.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void program_words(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit immutable-metadata pointer-slot work before reserving it. |
| inputs / outputs | Optional work allowance and element count debit rounded pointer words for T. |
| invariants | Null allowance means no indexed-work debit; multiplication cannot overflow. |
| ownership | Borrows the operation allowance without creating another grant. |
| failure | IndexFailure overflow/work rejection before admitted work. |
| cost | Fixed size arithmetic and allowance debit; actual allocation/initialization remains separate. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 64–72](../../../../../src/runtime/support.cpp#L64); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct RecordState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one row child-presence vector and its exact satisfied count. |
| inputs / outputs | Account, node attribution and arity create all-false flags; lifetime() reclassifies that allocation. |
| invariants | Satisfied count equals true flags after a drained stage; full copies must preserve allocator ownership. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Flag allocation can fail before publication; lifetime changes require a live allocation. |
| cost | O(child arity) initialization/copy; lifetime classification follows native account lookup costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 73–75](../../../../../src/runtime/support.cpp#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<bool> export_flags(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export child bits into a caller-owned diagnostic DTO. |
| inputs / outputs | RecordState returns an owning standard vector&lt;bool&gt;. |
| invariants | Export does not alias mutable live flags. |
| ownership | Caller DTO allocator is explicit; this result is not a retained native metadata cache. |
| failure | Allocation failure leaves the source record unchanged. |
| cost | O(child arity) bit packing and allocation; snapshot/inspection only. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 76–80](../../../../../src/runtime/support.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<bool,resource::OwnerAllocator<bool>> retained_flags(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an original-account copy of child bits in a journal record. |
| inputs / outputs | RecordState produces an owning bit vector with journal-undo purpose and the same node attribution. |
| invariants | Before/after inspection images do not alias live flags. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | O(child arity) bit copy/allocation for each captured value; real Boolean updates retain these public record images. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0015

[Lines 81–85](../../../../../src/runtime/support.cpp#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
auto transition_buffer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare optional output membership-transition storage. |
| inputs / outputs | Original account returns an empty OwnerAllocator transition vector. |
| invariants | An empty result is still associated with output attribution. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Appends may fail inside the transaction; no-op apply retains no transition payload. |
| cost | Fixed empty-container construction; capture appends/deep values are explicit additional costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0016

[Lines 86–89](../../../../../src/runtime/support.cpp#L86); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_nothrow_move_constructible_v<SupportValueState>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove moves used at commit and undo-vector publication cannot allocate/throw. |
| inputs / outputs | Compile-time move traits for SupportValueState and SupportEpoch. |
| invariants | The no-allocation commit boundary relies on these exact member ownership moves. |
| ownership | Compile-time checks only. |
| failure | Incompatible member changes fail compilation. |
| cost | Zero runtime work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0017

[Lines 90–104](../../../../../src/runtime/support.cpp#L90); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NodeState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep tuple-ID keyed row metadata and distinct P/E support counters. |
| inputs / outputs | Account produces empty records/parent/visible maps and a unique support-node attribution. |
| invariants | Maps describe separate compiled relations even when layouts match; metadata owner IDs are internal. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Unpublished construction failure destroys prepared members; invalid lifetime pointer is an internal contract fault. |
| cost | Ordered map lookup O(log resident entries); record() allocates child-arity flags; lifetime classification can scan account allocations. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0018

[Lines 105–107](../../../../../src/runtime/support.cpp#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using SupportNodeProgram=program::PhysicalNode;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the retained native node/edge/enumeration descriptors. |
| inputs / outputs | Aliases to immutable CompiledProgram record types. |
| invariants | Program spans borrow their owning frozen program; no physical DTO mirror is retained. |
| ownership | Aliases retain nothing by themselves. |
| failure | Compile-time type resolution only. |
| cost | Zero runtime work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0019

[Lines 108–122](../../../../../src/runtime/support.cpp#L108); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportEnumerationProgram {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a derived fragment traversal and expose borrowed compiled-style spans. |
| inputs / outputs | Account-funded steps/output/equalities plus depth produce a non-owning EnumerationProgram view. |
| invariants | Returned spans remain valid only while vectors are unchanged and this owner lives; clear() empties them. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Growth can fail during cursor preparation; view/clear are noexcept. |
| cost | Fixed view assembly; retained storage proportional to selected descriptors/fields; clear destroys descriptor/key owners. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 123–139](../../../../../src/runtime/support.cpp#L123); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct State {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind immutable executable metadata, native relations and per-node support maps. |
| inputs / outputs | Checked shape/program, account and allowance produce empty account-owned storage and node metadata. |
| invariants | Program spans and enumeration borrow compiled; node vector is reserved before mutation inverses can point into it. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Admission/allocation failure publishes no State. |
| cost | O(program nodes and native initial storage/import capacity); no copied live query image. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0022

[Lines 141–150](../../../../../src/runtime/support.cpp#L141); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId relation(const auto& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a semantic support role to its compiled native relation. |
| inputs / outputs | Compiled node and SupportRole return records/S/P/E RelationId. |
| invariants | Visible role is valid only inside C*. |
| ownership | Returns an ID scalar; owns no relation. |
| failure | invalid_support_role rejects absent E or an unknown enum. |
| cost | Fixed switch/optional check, no allocation on success. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0023

[Lines 151–164](../../../../../src/runtime/support.cpp#L151); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
constexpr std::array<CursorMetricDescriptor,cursor_metric_count> cursor_registry
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define exact optional lifecycle metric names, units and scopes. |
| inputs / outputs | Static entries for timings/calls/cleanup/clocks. |
| invariants | Cursor intervals may nest in propagation; startup/next/cleanup are distinct and unavailable/disabled facts remain explicit. |
| ownership | Static arrays and string literals. |
| failure | No runtime recovery. |
| cost | Fixed read-only program data. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0024

[Lines 165–168](../../../../../src/runtime/support.cpp#L165); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool cursor_clocks(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decide whether this observation configuration permits clock reads. |
| inputs / outputs | Returns true for timed mode or trace with trace_timings. |
| invariants | Counters/off paths do not invoke the clock. |
| ownership | Borrows established runtime/cursor metadata; scalar returns own no row or grant. |
| failure | Noexcept enum/Boolean checks. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0025

[Lines 169–174](../../../../../src/runtime/support.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_add(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate an enabled optional cursor metric with explicit saturation. |
| inputs / outputs | Metric ID and amount update one values slot. |
| invariants | Unavailable/disabled metrics remain unchanged; overflow clamps UINT64_MAX and sets saturated. |
| ownership | Mutates caller-owned fixed report only. |
| failure | Noexcept; callers supply a valid internal metric ID. |
| cost | Constant availability/overflow branches. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0026

[Lines 175–178](../../../../../src/runtime/support.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t cursor_now(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read optional clock and account for that cursor-local read. |
| inputs / outputs | Observation plus optional shared observer; returns clock or zero when disabled. |
| invariants | Disabled path does not read clock or increment counts. |
| ownership | Borrows observer; no owner creation. |
| failure | Noexcept observation-clock interface. |
| cost | Fixed checks; actual clock call only when enabled. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0027

[Lines 179–184](../../../../../src/runtime/support.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cursor_elapsed(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add a clock interval or invalidate a regressed timing. |
| inputs / outputs | Metric ID/start plus observation/observer. |
| invariants | Backward clocks increment regression count and mark timing unavailable; no unsigned wrap. |
| ownership | Mutates fixed optional report. |
| failure | Noexcept, no diagnostic allocation. |
| cost | One optional finish read and fixed arithmetic. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0028

[Lines 185–186](../../../../../src/runtime/support.cpp#L185); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L185-L186:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`anonymous namespace in src/runtime/support.cpp\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`anonymous namespace in src/runtime/support.cpp\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`anonymous namespace in src/runtime/support.cpp\` at its lexical source position in src/runtime/support.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`anonymous namespace in src/runtime/support.cpp\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0029

[Lines 187–187](../../../../../src/runtime/support.cpp#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const CursorMetricDescriptor> cursor_observation_registry()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the static lifecycle metric registry. |
| inputs / outputs | Immutable span over cursor_registry. |
| invariants | No dynamic registration or per-runtime copy. |
| ownership | Program-lifetime view. |
| failure | Noexcept. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0030

[Lines 188–189](../../../../../src/runtime/support.cpp#L188); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static_assert(std::is_trivially_copyable_v<CursorObservation>);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep cursor lifecycle snapshots trivially copyable. |
| inputs / outputs | Compile-time trait on report type. |
| invariants | Publishing last_cursor remains fixed metadata copying. |
| ownership | Compile-time check. |
| failure | A nontrivial member addition fails compilation. |
| cost | Zero runtime work. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0031

[Lines 190–193](../../../../../src/runtime/support.cpp#L190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProjectionSupportCount increment_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add one exact surviving local witness to a projection count. |
| inputs / outputs | Current count and positive configured limit produce count+1. |
| invariants | No wrap or approximation; membership is tracked separately at zero crossings. |
| ownership | Inline value only. |
| failure | support_overflow when current value already reaches the admitted limit. |
| cost | Fixed integer comparison/addition. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0032

[Lines 194–196](../../../../../src/runtime/support.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ProjectionSupportCount decrement_support(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one exact local witness from a positive projection count. |
| inputs / outputs | Positive count produces count-1. |
| invariants | Callers handle resulting zero by erasing key membership. |
| ownership | Inline value only. |
| failure | runtime_contract rejects underflow. |
| cost | Fixed scalar check/subtraction. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0033

[Lines 197–200](../../../../../src/runtime/support.cpp#L197); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportRuntime::Impl {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the logical runtime configuration and one existing storage work context. |
| inputs / outputs | Private Impl begins with options and shared storage_context. |
| invariants | Context carries original query account and active indexed operation authority. |
| ownership | Impl owns context; public facade/readers/pending tokens share Impl lifetime. |
| failure | Construction is unpublished until complete. |
| cost | Fixed owner fields; full state initialized in constructor. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0034

[Lines 201–201](../../../../../src/runtime/support.cpp#L201); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] storage::IndexWorkAllowance* work() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the current native storage balance from the original context. |
| inputs / outputs | Returns compact_storage_work(storage_context). |
| invariants | Nested calls do not copy/refill allowance; reference backend can return null. |
| ownership | Call-lifetime borrowed pointer to context authority. |
| failure | Context operation rules are enforced by storage-work helper. |
| cost | Direct context lookup. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0035

[Lines 202–216](../../../../../src/runtime/support.cpp#L202); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<detail::ObservationState> observation;
  workload::detail::State workload;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store observation/workload state, identity, writer/read leases and native state. |
| inputs / outputs | Fixed counters/owners plus State, CompiledProgram/output tokens and edge lookup arrays. |
| invariants | State owns actual relations; plan shares frozen executable metadata; children/incoming are compiled numeric routing arrays. |
| ownership | All native state/metadata buffers use original account; immutable descriptors share funded controls. |
| failure | Member cleanup releases incomplete construction. |
| cost | Per-node/edge retained routing metadata and actual table/support state. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0036

[Lines 217–233](../../../../../src/runtime/support.cpp#L217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Source> Impl(Source p,SupportOptions o,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one empty admitted Boolean support runtime. |
| inputs / outputs | Native/physical source, options and existing validated context build State, outputs, observer and child-edge routing. |
| invariants | Checks observation/capture conflict, positive support cap and valid schedule; compiled nodes/edges drive numeric routing. |
| ownership | Account funds State/Impl and nested metadata; borrowed layouts are retained native tokens, not legacy plan copies. |
| failure | Construction/resource/validation failure unwinds members; no published writer/reader state exists. |
| cost | Visits compiled nodes/edges and imported metadata, constructs empty tables, allocates O(nodes+edges) routing. No source population scan. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0037

[Lines 234–234](../../../../../src/runtime/support.cpp#L234); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void readable() const { require(!updating,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Protect committed readers from a private prepared epoch. |
| inputs / outputs | updating=false returns normally; active writer rejects read access. |
| invariants | Read leases permit other committed reads. |
| ownership | Read-only flag; no synchronization or owner copy. |
| failure | runtime_busy during a prepared writer. |
| cost | O(1) success. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0038

[Lines 235–235](../../../../../src/runtime/support.cpp#L235); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void writable() const { readable();
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require exclusive writer readiness before even no-op updates. |
| inputs / outputs | Readable state and zero readers permit mutation. |
| invariants | A reader is a single-caller lifetime guard, not a mutex. |
| ownership | Only scalar checks. |
| failure | runtime_busy when writer or any reader is active. |
| cost | O(1) success. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0039

[Lines 236–258](../../../../../src/runtime/support.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void observe(const SupportMetrics& metrics) const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish mandatory support work into optional observation counters. |
| inputs / outputs | Copies every named SupportMetrics field when observation exists. |
| invariants | No event history/payload capture occurs here; off path returns immediately. |
| ownership | Mutates established observer only. |
| failure | Noexcept; no resource reservation. |
| cost | Fixed registry-sized assignments, zero when disabled. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0040

[Lines 259–260](../../../../../src/runtime/support.cpp#L259); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  SupportSnapshot snapshot(std::uint64_t visible_sequence) const;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare explicit complete snapshot and gauge helpers. |
| inputs / outputs | Diagnostic sequence and caller/native gauge result forms. |
| invariants | Population-dependent inspection is separate from ordinary propagation. |
| ownership | Definitions allocate owning diagnostic output explicitly. |
| failure | Declared resource/busy errors propagate. |
| cost | No declaration cost; implementations traverse state. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0041

[Lines 261–261](../../../../../src/runtime/support.cpp#L261); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<SupportNodeProgram>& program_nodes() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained immutable node program. |
| inputs / outputs | Returns State program_nodes span object. |
| invariants | No repeated lowering, source-plan access or node copy. |
| ownership | Borrows established runtime/cursor metadata; scalar returns own no row or grant. |
| failure | The stated owner guard rejects an empty/moved handle; no mutation or silent repair. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0042

[Lines 262–262](../../../../../src/runtime/support.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<SupportEdgeProgram>& program_edges() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained immutable edge program. |
| inputs / outputs | Returns State program_edges span object. |
| invariants | Numeric edge topology was frozen at admission. |
| ownership | Borrows established runtime/cursor metadata; scalar returns own no row or grant. |
| failure | The stated owner guard rejects an empty/moved handle; no mutation or silent repair. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0043

[Lines 263–265](../../../../../src/runtime/support.cpp#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SupportNodeProgram& node(NodeId id) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate a native node ID before private routing. |
| inputs / outputs | NodeId offset returns program node. |
| invariants | Out-of-range IDs reject before array dereference. |
| ownership | Borrows established runtime/cursor metadata; scalar returns own no row or grant. |
| failure | invalid_native_update on bad ID. |
| cost | Constant bounds check/access. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0044

[Lines 266–266](../../../../../src/runtime/support.cpp#L266); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportHandle handle(NodeId node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a public logical support identity from a native table handle. |
| inputs / outputs | Node, role and native TupleHandle produce public owner/node/role/TupleId. |
| invariants | Public owner differs from private native table ownership; handle validity still depends on membership. |
| ownership | Inline copied IDs; no pin is acquired. |
| failure | Requires established node/relation agreement. |
| cost | O(1). |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0045

[Lines 267–271](../../../../../src/runtime/support.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool answer(const State& current)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read Boolean query existence without enumerating full output. |
| inputs / outputs | Constant routes return their truth; tree route tests root S cardinality. |
| invariants | This tests existence only, not full result cardinality or a delta. |
| ownership | Borrows native State; no output owner. |
| failure | Requires checked route/root metadata. |
| cost | O(1) cardinality read. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0046

[Lines 272–275](../../../../../src/runtime/support.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::Tuple plan_tuple(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy a native tuple into an owning public output payload under its plan layout. |
| inputs / outputs | AccountedTuple produces storage::Tuple with the authoritative compiled layout token. |
| invariants | Output does not borrow mutable table memory after return. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Output allocation/copy failure propagates; caller determines rollback/read-only disposition. |
| cost | O(selected fields and variable-width bytes), plus funded immutable payload-owner allocation. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0047

[Lines 276–276](../../../../../src/runtime/support.cpp#L276); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Pending { std::size_t edge;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one child P membership crossing through the propagation queue. |
| inputs / outputs | Edge, polarity, owning separator key and causal ID identify one pending event. |
| invariants | Values are presence transitions, not numerical witness-count deltas. |
| ownership | Deque retains cloned account-owned key until event destruction. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Fixed event fields plus actual key clone/deque block allocation; queue length tracks affected crossings. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0048

[Lines 277–288](../../../../../src/runtime/support.cpp#L277); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  struct Transaction {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain affected-state undo and iterative event coordination for one pending epoch. |
| inputs / outputs | References runtime/state/output; owns journal, pending deque, applied flags, cause/prefix accounting and optional build budget pointers. |
| invariants | One coordinator spans all same-polarity stages. Queue events own keys; logical and native work remain separate. |
| ownership | All retained transaction buffers use original account; pointers to runtime/state/build options are scoped borrows. |
| failure | Destructor reverses uncommitted metadata then native table journals. |
| cost | Retained space follows affected events/metadata, not a complete copied database. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0049

[Lines 289–289](../../../../../src/runtime/support.cpp#L289); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class MetaKind {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the exact row/count metadata inverse. |
| inputs / outputs | Six tags distinguish insert/change/extracted-erase for row and counter maps. |
| invariants | Undo tag, role and saved value/node must agree. |
| ownership | Inline discriminator inside funded MetaUndo. |
| failure | Invalid internal tag is a contract defect. |
| cost | Constant enum; no polymorphic inverse dispatch. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0050

[Lines 290–299](../../../../../src/runtime/support.cpp#L290); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct MetaUndo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund restoration information before changing one metadata entry. |
| inputs / outputs | Tag/node/role/TupleId plus old row/count or detached map node reverse one mutation. |
| invariants | Stable NodeState pointers and extracted nodes remain valid through reverse rollback. |
| ownership | One accounted unique object per inverse, owned by undo vector; old row flags can allocate. |
| failure | Preparation failure precedes mutation; restore uses already funded state. |
| cost | Fixed object per edit plus O(child arity) saved flags for a row change; no query-wide state copy. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0051

[Lines 300–300](../../../../../src/runtime/support.cpp#L300); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    MemoryVector<resource::AccountedUnique<MetaUndo>> undo;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep individually owned affected metadata inverse records. |
| inputs / outputs | Accounted vector of AccountedUnique&lt;MetaUndo&gt;. |
| invariants | Capacity is prepared before each metadata change; saved nodes/flags make reverse restore nonallocating. |
| ownership | Original account owns vector and inverse controls/child state. |
| failure | Growth/creation errors occur before protected metadata mutation. |
| cost | O(affected mutations + saved child widths), plus actual map/lifetime-ledger cleanup. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0052

[Lines 301–305](../../../../../src/runtime/support.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Transaction(Impl& r,State& s,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one private support propagation/undo coordinator. |
| inputs / outputs | Impl, State, output and shared public journal produce empty FIFO/applied/undo containers. |
| invariants | One Transaction spans every staged native operation and all resulting child events. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Unpublished construction failure leaves no active transaction. |
| cost | Fixed owners/empty-container setup; subsequent touched work is funded lazily. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0053

[Lines 306–330](../../../../../src/runtime/support.cpp#L306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Transaction()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore uncommitted metadata and native table memberships in reverse. |
| inputs / outputs | Destruction skips committed transactions; otherwise applies all metadata inverses then storage journals. |
| invariants | Metadata is restored while original table handles still exist; insertion of detached nodes allocates nothing. |
| ownership | Owns saved row arrays/counts/extracted nodes until commit or rollback. |
| failure | Noexcept destruction; impossible duplicate restore terminates as an internal invariant violation. |
| cost | O(actual inverse/table cleanup), including lifetime-ledger classification scans; no whole-state rebuild. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0054

[Lines 331–336](../../../../../src/runtime/support.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void commit() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Discard prepared inverses after native tables commit. |
| inputs / outputs | Commit each touched table journal, clear its private ownership and mark metadata transaction committed. |
| invariants | Public record pins already retain values needed by callers; no further preparation is allowed. |
| ownership | Releases private journals/undo while shared public record history survives. |
| failure | Noexcept/nonallocating; caller validates token and prepares all throwing output first. |
| cost | O(touched journals and undo destruction), not a full query scan. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0055

[Lines 337–344](../../../../../src/runtime/support.cpp#L337); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge(std::uint64_t amount=1)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit cumulative abstract update work before charging a category. |
| inputs / outputs | Amount updates build replay work when enabled and then the epoch work count. |
| invariants | One total spans stages; uint64 and optional cap cannot wrap/refill. |
| ownership | Inline work counters and borrowed optional build metrics. |
| failure | resource_limit or build limit fails before the update total increment; enclosing stage rolls back. |
| cost | Fixed arithmetic/guards; not a complete CPU-time or memory model. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0056

[Lines 345–349](../../../../../src/runtime/support.cpp#L345); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metric(std::uint64_t& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count one maintenance category under the same cumulative work cap. |
| inputs / outputs | Category reference and amount charge work then increment the category. |
| invariants | Every managed category begins at zero and increments only through charged calls, including queue_peak increments, so category &lt;= work. |
| ownership | Borrows inline output counters only. |
| failure | Budget/total overflow is rejected before the category increment; category room follows the cumulative-work invariant. |
| cost | Fixed scalar admission and category additions; no key/result copy. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0057

[Lines 350–356](../../../../../src/runtime/support.cpp#L350); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedStorageTable::Journal& writer(RelationId id)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse one native journal for each relation touched by this transaction. |
| inputs / outputs | Relation ID returns existing journal or lazily opens and retains one. |
| invariants | All table journals use the retained operation allowance; no per-stage grant refill. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Linear search in touched-relation count plus first-open allocation/preparation; no relation snapshot. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0058

[Lines 357–361](../../../../../src/runtime/support.cpp#L357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TupleHandle insert(RelationId id,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish one absent native relation member through its journal. |
| inputs / outputs | Relation and typed tuple return a new member handle. |
| invariants | Duplicate internal insert is inconsistent with support metadata. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | One storage_changes charge plus actual hash/order/key/growth/inverse costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0059

[Lines 362–365](../../../../../src/runtime/support.cpp#L362); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void erase(RelationId id,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one known relation member with funded native inverse state. |
| inputs / outputs | Relation ID and exact handle erase membership. |
| invariants | Absent internal member is a contract fault. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | One storage_changes charge and actual native journal/index/retained-node work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0060

[Lines 366–375](../../../../../src/runtime/support.cpp#L366); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::AccountedUnique<MetaUndo> prepare(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve a standalone metadata inverse and vector room before mutation. |
| inputs / outputs | Kind/node/role/TupleId return a funded empty MetaUndo with retained allocation lifetime. |
| invariants | A later undo push cannot allocate because capacity is reserved here. |
| ownership | AccountedUnique owns the inverse until moved into the undo vector; caller fills the payload. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | One accounted inverse allocation per metadata edit plus amortized vector growth; no full metadata-map clone. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0061

[Lines 376–378](../../../../../src/runtime/support.cpp#L376); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static SupportValueState record_value(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture a present row metadata value for the public affected-record journal. |
| inputs / outputs | RecordState becomes member=true, satisfied count and an owning child-bit vector. |
| invariants | Journal state is immutable to callers and does not alias live flags. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | O(child arity) retained bit-vector copy; performed for before/after images on real updates. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0062

[Lines 379–379](../../../../../src/runtime/support.cpp#L379); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static SupportValueState count_value(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe a present projection count without row flags. |
| inputs / outputs | Inline ProjectionSupportCount becomes a member=true SupportValueState. |
| invariants | Projection support is distinct from satisfied-child count. |
| ownership | Inline optional scalars only. |
| failure | No allocation or user-input failure. |
| cost | O(1). |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0063

[Lines 380–398](../../../../../src/runtime/support.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void note(const SupportNodeProgram& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one causal affected-record description after its images are prepared. |
| inputs / outputs | Node/role/handle and before/after values append ordinal/cause/public handle and a tuple pin. |
| invariants | Pins preserve deleted tuples; records describe local changes, not full query deltas. |
| ownership | Public journal owns images and original-account pin; workload/observation updates are separate diagnostics. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Actual pin and append costs, plus optional observation work; image-copy costs belong to record_value. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0064

[Lines 399–420](../../../../../src/runtime/support.cpp#L399); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void record(const SupportNodeProgram& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace or erase one row metadata value while retaining exact inverse state. |
| inputs / outputs | Record handle and optional desired RecordState select insertion/change/extraction. |
| invariants | Reserve inverse/vector and construct both public images before mutation; mutation is followed only by prepaid undo push. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Ordered map work, one inverse allocation, O(child arity) old-flag copy and journal images; no O(1) per-row claim. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0065

[Lines 421–438](../../../../../src/runtime/support.cpp#L421); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void counter(const SupportNodeProgram& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one exact P or E numeric support counter. |
| inputs / outputs | Node/role/handle and optional count select insertion/change/extracted erasure. |
| invariants | Caller uses parent_support or visible role; old count and public images are prepared before mutation. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Ordered ID-map access, one funded inverse and capture/pin work; erasure lifetime lookup can scan allocations. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0066

[Lines 439–441](../../../../../src/runtime/support.cpp#L439); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void event(const SupportNodeProgram& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain optional owning local membership transitions. |
| inputs / outputs | Node/role/handle/polarity/key append MembershipTransition only with capture_transitions. |
| invariants | Transitions are local role crossings, not complete-answer deltas. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Disabled path is a flag check; enabled path exports a tuple and grows the owning vector. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0067

[Lines 442–445](../../../../../src/runtime/support.cpp#L442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void start()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Account one changed native stage as an applied root causal event. |
| inputs / outputs | Appends an applied flag, increments enqueued/applied totals and sets cause to its event ID. |
| invariants | Only changed native stages call start; no-op stages leave event counts zero. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Fixed charges plus amortized applied-flag append; no child work yet. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0068

[Lines 446–452](../../../../../src/runtime/support.cpp#L446); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_trace(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture optional native-event details for the current changed stage. |
| inputs / outputs | Native node, handle, key and polarity publish observation/event-trace information. |
| invariants | Native event has cause zero; full trace exists only when capture_transitions is enabled. |
| ownership | Observation stores bounded diagnostics; full causal event owns a public tuple only when requested. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Optional observer work and enabled key copy/vector append; no extra support propagation. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0069

[Lines 453–466](../../../../../src/runtime/support.cpp#L453); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void enqueue(std::size_t edge_id,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Queue one parent-directed P membership transition. |
| inputs / outputs | Edge, appearance/disappearance, key and source handle append a fresh event ID and unapplied flag. |
| invariants | Key is cloned before its source membership can disappear; each event will be popped once. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Actual key clone/deque/appended-flag work and optional tracing; queue peak is a charged increase. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0070

[Lines 467–471](../../../../../src/runtime/support.cpp#L467); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    // Boolean support primitive: add/remove one surviving local witness.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain local survivor-to-projection support counting. |
| inputs / outputs | The following count applies one S contribution to P or E. |
| invariants | Only0&lt;-&gt;1 membership crossings return handles; positive-to-positive changes do not propagate. |
| ownership | Comments retain no runtime state; following transaction owns actual undo. |
| failure | No runtime error path in comment. |
| cost | Documentation only; actual map/flag/journal costs are in the primitive cards. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4, printed/PDF p.5; accounting/undo are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0071

[Lines 472–489](../../../../../src/runtime/support.cpp#L472); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<TupleHandle> count(const SupportNodeProgram& node,SupportRole role,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adjust one projected S-witness count for P or E and report only a Boolean membership crossing. |
| inputs / outputs | Node, parent/visible role, projected key and add/remove in; optional crossing handle out. |
| invariants | Stored projected key iff count&gt;0. Positive-to-positive changes update count only; zero-to-one inserts and one-to-zero erases exactly once. |
| ownership | The stage owns table journals, metadata inverses and output state. Returned handles are stage/runtime identities, not owning payloads. |
| failure | Absent erasure, overflow, allocation or work failure unwind through the stage; counters and table membership have paired inverses. |
| cost | One table probe plus count-map access, optional row/journal insertion or erase, key hashing/projection costs. Boolean suppression is not valid for future numeric weighted messages. |
| Design | [docs/support_invariants.md](../../../../support_invariants.md), [docs/runtime_support.md](../../../../runtime_support.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4, PDF p. 5](https://arxiv.org/pdf/2301.04003v2) |

## B0072

[Lines 490–492](../../../../../src/runtime/support.cpp#L490); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    // Change S once, then adjust its parent-key P and output-key E projections.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain S membership and two distinct projection roles. |
| inputs / outputs | The following survivor changes local S then applicable P/E. |
| invariants | Only P crossing queues ancestor work; E is local enumeration state, not global live L. |
| ownership | Comments retain no runtime state; following transaction owns actual undo. |
| failure | No runtime error path in comment. |
| cost | Documentation only; actual map/flag/journal costs are in the primitive cards. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4, printed/PDF p.5; accounting/undo are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0073

[Lines 493–508](../../../../../src/runtime/support.cpp#L493); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void survivor(const SupportNodeProgram& node,const storage::AccountedTuple& tuple,bool add)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one local survivor membership change and maintain its parent/output projections. |
| inputs / outputs | Supported full node tuple and membership polarity in; S updated, P/E counts changed, optional ancestor event queued. |
| invariants | An S membership change contributes once to each applicable projection. Only a P key zero crossing propagates upward; E is visible enumeration state. |
| ownership | The stage retains journals/metadata inverses and queued cloned keys; public observation/capture values retain their accounted payloads. |
| failure | Every throwing projection, table or queue step is inside the pending stage rollback boundary. |
| cost | One S insert/erase, up to two projected-count operations, and queue work only on P crossings; deep fields and journaling are real costs. |
| Design | [docs/support_invariants.md](../../../../support_invariants.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4, PDF p. 5](https://arxiv.org/pdf/2301.04003v2) |

## B0074

[Lines 509–532](../../../../../src/runtime/support.cpp#L509); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native(const SupportNodeProgram& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one changed external logical tuple insertion or erasure. |
| inputs / outputs | Native compiled node and typed complete tuple create/remove row metadata and conditional survivor membership. |
| invariants | Insertion probes each child P before deciding survival; erasure removes S before record membership. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Insertion O(child arity) probes plus native/journal work; erasure uses cached satisfaction then actual projected changes. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4; native journals and accounting are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0075

[Lines 533–536](../../../../../src/runtime/support.cpp#L533); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
    // Consume one child-presence bit transition, never its witness count.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the child-slot recurrence and affected inverse. |
| inputs / outputs | The following presence replaces one RecordState child bit. |
| invariants | S requires all child presences; generalized candidate reclamation requires zero child presences. Fan-out flag copying is explicit. |
| ownership | Comments retain no runtime state; following transaction owns actual undo. |
| failure | No runtime error path in comment. |
| cost | Documentation only; actual map/flag/journal costs are in the primitive cards. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4, printed/PDF p.5; accounting/undo are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0076

[Lines 537–549](../../../../../src/runtime/support.cpp#L537); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void presence(const SupportNodeProgram& node,TupleHandle handle,RecordState& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume one child-key presence change for a candidate/native row. |
| inputs / outputs | Node, row handle/current flags, child slot, presence polarity and row in; copied next flags, survivor crossing and possible generalized reclamation out. |
| invariants | Reject duplicate bit transitions. satisfied counts true child slots. Survivor iff every child is present; generalized candidate disappears only when no child supplies its key. |
| ownership | record saves metadata inverse and installs the next RecordState. Table/journal ownership keeps the tuple valid during this private stage. |
| failure | Validate slot/old bit before mutation; all allocation, work and contract failures unwind the stage. Do not remove saved metadata because storage has its own journal. |
| cost | auto next=value copies the entire present array: O(fan-out) scalar copy and potential allocation per touched row, plus journal work. This explicit set-runtime overhead is separate from the root W02 compact scalar/slot undo. |
| Design | [docs/support_invariants.md](../../../../support_invariants.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4, PDF p. 5](https://arxiv.org/pdf/2301.04003v2) |

## B0077

[Lines 550–581](../../../../../src/runtime/support.cpp#L550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void child(const Pending& event)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one child P crossing to only matching parent records or one generalized candidate. |
| inputs / outputs | Edge/key/polarity visit native reverse-bucket matches or create/update/reclaim the generalized full-key candidate. |
| invariants | Generalized candidates are the union of child keys and survive only at all-child support; no Cartesian candidate materialization. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | Native path first materializes an accounted handle vector of size matching fan-out, then visits it. O(matches) scratch/copy plus row-arity metadata/journal costs; generalized path performs one key lookup. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4; native journals and accounting are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0078

[Lines 582–597](../../../../../src/runtime/support.cpp#L582); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void drain()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Iteratively finish all queued child crossings under FIFO or LIFO order. |
| inputs / outputs | Pending deque is popped until empty; applied flags and totals verify exactly-once processing. |
| invariants | Each later stage starts drained; checked_events avoids rescanning already checked IDs. |
| ownership | Borrows the private transaction owner, stable node metadata and its retained storage grant. |
| failure | Allocation, work or contract failure unwinds the existing stage boundary; all earlier stages roll back. |
| cost | O(actual pending events/affected rows plus newly checked flags); no C++ recursion by tree height. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §4.2 Algorithms 2–4; native journals and accounting are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0079

[Lines 598–601](../../../../../src/runtime/support.cpp#L598); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
};

struct SupportRuntime::EpochView::Group {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin shared journal-overlay context ownership after private transaction definitions. |
| inputs / outputs | Closes Impl and declares EpochView::Group. |
| invariants | Group owns one reader lease across copied views/cursors. |
| ownership | Type boundary only; members below own overlay state. |
| failure | No standalone runtime operation. |
| cost | No runtime cost for scope/type declaration. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0080

[Lines 602–602](../../../../../src/runtime/support.cpp#L602); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  enum class Phase { tentative, committed, aborted };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track whether a shared epoch context is tentative, committed or invalidated. |
| inputs / outputs | Three lifecycle tags. |
| invariants | Commit preserves views; rollback changes phase before closing linked cursors. |
| ownership | Value only. |
| failure | No throwing enum operation. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0081

[Lines 603–624](../../../../../src/runtime/support.cpp#L603); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Patch {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Index journal-retained before-side rows and excluded after-side members. |
| inputs / outputs | Account-owned ID sets/maps provide full-key and per-index restored lookup. |
| invariants | Tuple pointers borrow the retained immutable journal pins; excluded IDs mask rows inserted after the before side. |
| ownership | Group owns maps/accounted copied keys and retains the journal; it does not copy the entire relation. |
| failure | Map/key allocation failure aborts view construction before reader acquisition. |
| cost | O(changed memberships and affected index entries) overlay storage, ordered/deep-key lookup costs; bucket() lazily creates each restored key container. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0082

[Lines 625–637](../../../../../src/runtime/support.cpp#L625); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<Impl> runtime;
  detail::StorageWorkLease storage_lease;
  CompiledProgram plan;
  std::shared_ptr<const SupportJournal> journal;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain runtime/program/affected history and shared before/after overlay state. |
| inputs / outputs | Patches, sequence/prefix stamps, answers, reader flag, phase, construction metrics and intrusive cursor head. |
| invariants | One group lease is shared; before-side patches restore deleted memberships and exclude inserted ones. |
| ownership | Runtime/journal/program strongly retained; cursor list borrows Data that retains this group. |
| failure | Unpublished construction failure releases fields; invalidation closes cursors before dropping journal. |
| cost | Per-relation patch descriptors plus actual changed keys/buckets. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0083

[Lines 638–680](../../../../../src/runtime/support.cpp#L638); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Group(std::shared_ptr<Impl> owner,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one immutable before/after epoch context and its affected-membership overlays. |
| inputs / outputs | Runtime, optional journal/suffix, sequences/prefixes/truth values/options produce patches for compiled relations. |
| invariants | Pure-polarity staged epochs ensure a membership ID is restored at most once; index overlays are built only for changed relations. |
| ownership | Original account owns patches; group retains runtime, journal and one storage lease. |
| failure | Work/memory/contract rejection publishes no acquired reader. |
| cost | Initializes one Patch per plan relation; scans selected journal suffix and matching plan indexes for restored memberships, copying exact key bytes. No complete old-state snapshot. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0084

[Lines 681–684](../../../../../src/runtime/support.cpp#L681); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void acquire()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the one reader lease shared by an epoch-view group. |
| inputs / outputs | Prepared Group increments runtime readers and marks leased. |
| invariants | Called only once after group and public view construction succeed. |
| ownership | One shared Group lease covers its copies and linked cursors. |
| failure | Reader overflow rejects before increment. |
| cost | O(1), no allocation. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0085

[Lines 685–690](../../../../../src/runtime/support.cpp#L685); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void release() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release this group reader exactly once. |
| inputs / outputs | A leased Group decrements readers; already released groups do nothing. |
| invariants | Runtime exists and reader count is positive while leased. |
| ownership | Does not destroy sibling view/cursor ownership; those share this group. |
| failure | Noexcept; invalid internal reader state terminates. |
| cost | O(1) accounting; final member destruction is separate. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0086

[Lines 691–691](../../../../../src/runtime/support.cpp#L691); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void abort() noexcept;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare prepaid epoch-view invalidation. |
| inputs / outputs | No arguments; definition closes all linked cursors and releases leases/patches. |
| invariants | Must run before rollback releases tuples borrowed through overlays. |
| ownership | Releases, never replaces, existing context authority. |
| failure | Noexcept private cleanup. |
| cost | Actual linked cursor and affected overlay teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0087

[Lines 692–692](../../../../../src/runtime/support.cpp#L692); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Group()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce cursor unlinking and release the final shared epoch lease. |
| inputs / outputs | Destruction requires no linked cursor and calls idempotent release. |
| invariants | Every linked cursor retains the Group; its close must unlink before releasing that reference. |
| ownership | Ordinary member destruction releases overlay maps, journal pins and runtime. |
| failure | Noexcept; a remaining intrusive cursor link is an internal lifetime fault. |
| cost | Actual overlay/journal/runtime release cost; potentially proportional to retained state. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0088

[Lines 693–693](../../../../../src/runtime/support.cpp#L693); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L693-L693:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct SupportRuntime::EpochView::Group\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct SupportRuntime::EpochView::Group\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct SupportRuntime::EpochView::Group\` at its lexical source position in src/runtime/support.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct SupportRuntime::EpochView::Group\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0089

[Lines 694–699](../../../../../src/runtime/support.cpp#L694); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportRuntime::EpochView::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair a shared epoch context with one requested snapshot side. |
| inputs / outputs | Shared Group and before/after enum produce the small view payload; readable rejects aborted group. |
| invariants | Multiple before/after Data objects can share one prepared group and lease. |
| ownership | Data owns only its shared Group reference and side scalar. |
| failure | Aborted relation reads raise invalid_snapshot; scalar identity metadata remains inspectable. |
| cost | O(1) access, no relation copy. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0090

[Lines 700–701](../../../../../src/runtime/support.cpp#L700); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportRuntime::ResultCursor::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define one native funded iterative cursor owner. |
| inputs / outputs | Source/Frame descriptors and lifecycle/traversal fields follow. |
| invariants | No whole-result or whole-relation snapshot is constructed. |
| ownership | AccountedUnique Data retains runtime or epoch group plus original grant lease. |
| failure | Startup cleanup occurs before cursor link/reader publication. |
| cost | Per-cursor selected frame/condition metadata. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0091

[Lines 702–707](../../../../../src/runtime/support.cpp#L702); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Source {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe where a fragment field constraint obtains its comparison scalar. |
| inputs / outputs | Fixed/local/outer kind plus variable/assignment slot identifies a bound value source. |
| invariants | Local/outer slots refer to already selected factors established by initialization. |
| ownership | Inline descriptors borrow the owning cursor fixed map/frames. |
| failure | Unselected internal source is a runtime_contract failure at bound(). |
| cost | Fixed descriptor; no per-field polymorphic object. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0092

[Lines 708–708](../../../../../src/runtime/support.cpp#L708); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Condition {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one tuple field with one compiled binding/equality source. |
| inputs / outputs | FieldId and Source describe a compatibility comparison. |
| invariants | Exact scalar equality is preserved; hidden bindings do not become output fields. |
| ownership | Inline element in the cursor-owned original-account conditions vector. |
| failure | Allocated during initialization before linking the cursor. |
| cost | One fixed descriptor per relevant constraint. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0093

[Lines 709–723](../../../../../src/runtime/support.cpp#L709); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Frame {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one lazy factor traversal with optional direct/overlay/key state. |
| inputs / outputs | Frame stores one cursor, selected borrowed tuple, bound keys, ghost iterator and startup conditions. |
| invariants | selected remains valid under the group/runtime read lease; before-side ghost pointers borrow retained journal tuples. |
| ownership | Original account owns condition/lookup/key storage; frame does not own an emitted-output history. |
| failure | Startup/read failure is handled by factory/produce boundaries; close destroys borrowed state before releasing owners. |
| cost | Fixed frame plus exact key/constraint widths; overlay rows remain shared in Group. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0094

[Lines 724–736](../../../../../src/runtime/support.cpp#L724); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<Impl> runtime;
  detail::StorageWorkLease storage_lease;
  CompiledProgram plan;
  ResultCursorOptions options;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain query/storage authority, immutable output schema and lifecycle observations. |
| inputs / outputs | Runtime/lease/program/options/view, native/readable output handles, mandatory work, startup sink and optional observer. |
| invariants | Diagnostics weakly reference owner so retained closed report does not keep old data alive; plan/output metadata may remain. |
| ownership | All controls/tokens refer to already funded original account; no second work grant. |
| failure | Field ownership unwinds on failed construction. |
| cost | Fixed fields/shared refs; output descriptors share tokens. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0095

[Lines 737–741](../../../../../src/runtime/support.cpp#L737); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void publish() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the latest optional cursor diagnostics without retaining the runtime. |
| inputs / outputs | Admitted diagnostic copies current mandatory metrics/status to a still-live weak diagnostic owner. |
| invariants | Disabled observation is a no-op; closed cursors can publish cleanup without owning mutable state. |
| ownership | Weak owner prevents a diagnostic cycle; published value contains no relation snapshots. |
| failure | Noexcept; expired diagnostic owner simply receives no update. |
| cost | Fixed metric/option copies and weak lock, no allocation. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0096

[Lines 742–776](../../../../../src/runtime/support.cpp#L742); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Make> static resource::AccountedUnique<Data> create(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a complete cursor before publishing its reader or intrusive link. |
| inputs / outputs | Owner/options/source/side/sequence plus a constructor callback return one funded Data and optional startup diagnostic. |
| invariants | Committed readers increment only after make succeeds; epoch cursors link only after full construction. Startup failure is reported without a reader. |
| ownership | Original account owns Data; diagnostic_owner is weak and startup_sink is cleared before return. |
| failure | One catch records optional startup failure then rethrows the original exception; it is not query rollback. |
| cost | Actual cursor preparation plus fixed optional observation/timing; no result scan in the committed constructor. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0097

[Lines 777–792](../../../../../src/runtime/support.cpp#L777); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ResultCursorState status=ResultCursorState::active;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain iterative traversal, fixed restrictions and optional witness-probe state. |
| inputs / outputs | Status/epoch/identity, leases/resume flags, main/probe frames, snapshot links, fragment program and fixed native rows. |
| invariants | Selected row pointers borrow leased state; fixed string values are owned in account; linked-list pointers do not own cursors. |
| ownership | Original account owns vectors/maps/fragment metadata; Group or runtime retains source tables. |
| failure | close destroys frame borrows before releasing source authority. |
| cost | Space follows frame/condition widths and imported fixed payloads, not output history. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0098

[Lines 793–793](../../../../../src/runtime/support.cpp#L793); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::EnumerationProgram& program() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the active complete or derived fragment traversal descriptor. |
| inputs / outputs | Returns the fragment-owned view when present, otherwise the runtime compiled enumeration. |
| invariants | Caller uses this only while its cursor still retains runtime/fragment state. |
| ownership | Borrowed spans point to immutable compiled data or cursor-owned vectors. |
| failure | Requires an active internal owner; closed public next rejects before traversal. |
| cost | O(1) descriptor selection. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0099

[Lines 794–797](../../../../../src/runtime/support.cpp#L794); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void resize_frames(Frames& target,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund exactly the required traversal-frame count before reading rows. |
| inputs / outputs | Target vector and size reserve room and construct missing original-account Frames. |
| invariants | This helper grows startup scratch; it does not reset or copy a live relation. |
| ownership | Every retained native allocation uses the existing query account; no new state owner/account is created here. |
| failure | Allocation failure occurs during cursor preparation before reader publication/linking. |
| cost | O(new frame count) construction and actual vector allocation; constraint/key payloads are separate. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0101

[Lines 799–815](../../../../../src/runtime/support.cpp#L799); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<Impl> owner,ResultCursorOptions limits,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a committed-result cursor over compiled E factors. |
| inputs / outputs | Runtime/options/core-or-SQL view retain layouts, sequence, truth and optional C* frames. |
| invariants | SQL EXISTS is scalar and needs no relation frames; root truth is captured under the reader contract. |
| ownership | Retains immutable compiled program and original owner/lease, not a deep plan or result copy. |
| failure | Startup allocation/work failure is handled by factory before reader publication. |
| cost | O(C*) frame preparation except scalar EXISTS; fixed shared metadata retention, no data-row scan. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0102

[Lines 816–873](../../../../../src/runtime/support.cpp#L816); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<EpochView::Data> context,const Bindings& bindings,VisibleFragment fragment,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile a visible completion cursor with optional subtree and hidden restrictions. |
| inputs / outputs | Epoch view, fixed values and optional C* root prepare projected traversal and existential witness probes. |
| invariants | Visible output keeps the original core head or sorted selected fragment variables; hidden bindings restrict existence without multiplying output rows. |
| ownership | Original account owns derived descriptors, fixed values, frames and probe child lists; retains the shared epoch Group. |
| failure | Invalid fragment/binding or startup limit failure creates no linked cursor and leaves a pending view owner active. |
| cost | Plan/field/map scans and ancestor walks during startup; selected/probe frame and binding storage. Hidden restrictions can require actual survivor witness searches per projected assignment. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0103

[Lines 874–886](../../../../../src/runtime/support.cpp#L874); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<EpochView::Data> context,const FixedAssignment& bindings,WitnessFragment fragment,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile full local survivor-factor assignments for a selected witness fragment. |
| inputs / outputs | Bindings plus whole-tree/root/exact-factor selection return a sorted union-variable output schema. |
| invariants | Witness rows retain hidden variables; they are distinct from projected answers and need not satisfy an outside-parent restriction. |
| ownership | Derived traversal/layout and copied bindings use the original account; Group lease protects selected factors. |
| failure | Selection/binding/work/allocation failures occur before linking. |
| cost | Actual selected-descriptor/field preparation; later general factor joins can visit rejected combinations. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0104

[Lines 887–899](../../../../../src/runtime/support.cpp#L887); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<EpochView::Data> context,NodeId id,ResultCursorOptions limits,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a local visible-factor key scan independent of global answer truth. |
| inputs / outputs | C* node ID produces a one-step E traversal with the complete sorted E-key schema. |
| invariants | Local E may be nonempty when the full query has no answer, so answer is set true for this factor scan. |
| ownership | Shares epoch Group; owns only one derived step/layout/frame and copied bindings. |
| failure | Rejects unknown/outside-C* node; startup failure publishes no linked cursor. |
| cost | Fixed one-step setup plus output-width descriptors; later visits actual E keys only. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0105

[Lines 900–926](../../../../../src/runtime/support.cpp#L900); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(std::shared_ptr<EpochView::Data> context,NodeId id,const Separator& separator,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a local visible-factor bucket scan under its compiled parent separator. |
| inputs / outputs | Nonroot C* node and exact separator values produce a one-step traversal with prebound key. |
| invariants | Compiled separator index must target that E relation; output remains the complete E-key layout. |
| ownership | Copies the validated separator into an original-account tuple and retains the Group. |
| failure | Invalid root/index/typed separator or preparation failure creates no linked cursor. |
| cost | Scans compiled enumeration to locate the node; copies separator/output descriptors, not a relation bucket. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0106

[Lines 927–929](../../../../../src/runtime/support.cpp#L927); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bind(std::shared_ptr<EpochView::Data> context,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward owning fixed assignments to the common typed binding importer. |
| inputs / outputs | Context and FixedAssignment delegate to bind_values. |
| invariants | Uses the same copying/validation rules as borrowed native bindings. |
| ownership | Moves the context reference into this cursor and imports values into the original account. |
| failure | Validation/allocation failure remains a startup failure. |
| cost | Only forwarding plus common importer work. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0107

[Lines 930–930](../../../../../src/runtime/support.cpp#L930); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static storage::ScalarView binding_value(const Value& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one caller DTO scalar during startup import. |
| inputs / outputs | Value returns a ScalarView without copying the payload. |
| invariants | Caller value lives through immediate validation/copy. |
| ownership | Temporary borrowed view; bind_values retains its own accounted copy. |
| failure | Requires a valid Value. |
| cost | O(1) borrow; deep copy occurs separately. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0108

[Lines 931–931](../../../../../src/runtime/support.cpp#L931); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static storage::ScalarView binding_value(const storage::ScalarView& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pass a native borrowed scalar through startup import. |
| inputs / outputs | ScalarView returns the same borrowed scalar view. |
| invariants | No borrowed input is retained without a subsequent accounted copy. |
| ownership | No ownership acquisition. |
| failure | Input view must remain valid through startup. |
| cost | O(1), no allocation. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0109

[Lines 932–949](../../../../../src/runtime/support.cpp#L932); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void bind_values(std::shared_ptr<EpochView::Data> context,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and retain exact fixed-variable values for a fragment cursor. |
| inputs / outputs | Context/bindings select side sequence/truth, validate variable/type and merge equal duplicate bindings. |
| invariants | Conflicting duplicates reject; every unique variable receives a one-cell accounted copy. |
| ownership | Retains Group side and native copied values, never caller DTO/view lifetimes. |
| failure | Aborted view, unknown variable/type/conflict or funding/work failure prevents cursor publication. |
| cost | O(bindings) charged imports with ordered map lookups and deep scalar copies. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0110

[Lines 950–980](../../../../../src/runtime/support.cpp#L950); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportEnumerationProgram survivors(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a survivor-factor traversal for whole-tree, subtree or exact node selection. |
| inputs / outputs | WitnessFragment returns selected survivor steps, repeated-variable equalities and sorted variable output slots. |
| invariants | Root and exact node set are mutually exclusive; node IDs are unique/valid. Empty exact set is nullary identity. |
| ownership | Descriptors/maps/DFS stack use original-account scratch and cursor storage. |
| failure | Malformed selection or startup resource rejection leaves no published cursor. |
| cost | Visits nodes reachable from selected root (whole tree for an exact set) and selected fields; map/equality construction is explicit startup work. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0111

[Lines 981–984](../../../../../src/runtime/support.cpp#L981); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialize(program::EnumerationProgram walk,Frames& target)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize cursor constraints without an outer assignment. |
| inputs / outputs | Traversal and target frames delegate with an empty original-account outer map. |
| invariants | Fixed/local constraints use the same common initializer. |
| ownership | Empty temporary outer map owns no relation rows. |
| failure | Preparation failures propagate to factory. |
| cost | Empty map setup plus common descriptor/field initialization. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0112

[Lines 985–1008](../../../../../src/runtime/support.cpp#L985); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initialize(program::EnumerationProgram walk,Frames& target,const MemoryMap<VariableId,AssignmentSlot>& outer)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile fixed, prior-local and projected-outer constraints for each frame. |
| inputs / outputs | Walk/frames/optional outer variable slots produce conditions and a full-key direct lookup recipe when every field is bound. |
| invariants | Exact scalar equalities are checked when selecting rows; before-side frames reference the corresponding relation patch. |
| ownership | Original account owns all retained condition/lookup vectors; outer map itself is borrowed only during startup. |
| failure | Allocation/work failure is pre-link startup failure. |
| cost | O(selected fields and their ordered-map probes) descriptor preparation; no data-row scan. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0113

[Lines 1009–1013](../../../../../src/runtime/support.cpp#L1009); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void link() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Register an epoch cursor for synchronous rollback invalidation. |
| inputs / outputs | Prepared Data links at the head of Group first/previous/next list. |
| invariants | Called only once after successful construction; Group must remain alive through snapshot. |
| ownership | Intrusive links borrow cursor objects; each cursor owns a Group reference. |
| failure | Noexcept/prepaid pointer publication. |
| cost | O(1) pointer writes, no list allocation. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0114

[Lines 1014–1017](../../../../../src/runtime/support.cpp#L1014); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data() {
    close(ResultCursorState::cancelled,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close abandoned cursor traversal and capture partially completed startup metrics. |
| inputs / outputs | Destructor closes active state and writes startup_sink if construction unwinding retained one. |
| invariants | Closed/moved cursors do not release a reader twice. |
| ownership | Destroys borrowed frame state before shared owner/Group release; metadata members then release normally. |
| failure | Noexcept close; optional startup sink is valid only within create/make lifetime. |
| cost | O(frame/probe/binding/descriptor cleanup), possibly final native owner destruction; no output history. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0115

[Lines 1018–1024](../../../../../src/runtime/support.cpp#L1018); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void metric(CursorWork& work,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend one cumulative cursor work amount and one action category. |
| inputs / outputs | Action CursorWork field and amount update total, action total/category and optional startup sink. |
| invariants | All managed categories are subsets of the checked total; the cap spans startup and every next. |
| ownership | Inline diagnostics only; no grant refill. |
| failure | Budget/total overflow is rejected before the category increment; category room follows the cumulative-work invariant. |
| cost | Fixed scalar admission and category additions; no key/result copy. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0116

[Lines 1025–1034](../../../../../src/runtime/support.cpp#L1025); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static void merge(CursorWork& target,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate one completed action into its result/termination/failure phase. |
| inputs / outputs | CursorWork action adds each explicit field to the phase accumulator. |
| invariants | Components remain bounded by already checked cumulative work; phase aggregation cannot overflow independently. |
| ownership | Inline fixed-sized diagnostic structures. |
| failure | Noexcept, no allocation. |
| cost | Fixed number of scalar additions. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0117

[Lines 1035–1054](../../../../../src/runtime/support.cpp#L1035); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void close(ResultCursorState state,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release a cursor lease and all borrowed traversal state exactly once. |
| inputs / outputs | Active cursor becomes the specified terminal state/reason; closed state is idempotent. |
| invariants | Unlink from Group before dropping snapshot; clear both main/probe frames before runtime release. |
| ownership | Releases mutable state and bindings; retains plan/layout/identity/metrics for terminal inspection. |
| failure | Noexcept/nonallocating cleanup; impossible reader-count state terminates. |
| cost | Scans all main/probe frames, including unopened frames; clears fixed maps/fragment metadata. Last runtime/Group destruction can additionally release full maintained/overlay state. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0118

[Lines 1055–1055](../../../../../src/runtime/support.cpp#L1055); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::ScalarView& value(AssignmentSlot slot)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a selected output/equality scalar by compiled slot. |
| inputs / outputs | Step/field returns const view from a selected main frame. |
| invariants | emit uses this only after complete compatible assignment selection. |
| ownership | Borrowed from leased table/journal tuple, never returned as an owning result by itself. |
| failure | Invalid internal slot/selection violates the checked program contract. |
| cost | O(1), no scalar export. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0119

[Lines 1056–1056](../../../../../src/runtime/support.cpp#L1056); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<bool Native> using EmittedTuple=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select native owning tuple versus public retaining tuple at compile time. |
| inputs / outputs | Boolean template chooses AccountedTuple or Tuple. |
| invariants | Both outputs preserve exact native layout/payload ownership. |
| ownership | Alias creates no object. |
| failure | Compile-time selection only. |
| cost | No runtime branch or allocation from alias. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0120

[Lines 1057–1084](../../../../../src/runtime/support.cpp#L1057); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<bool Native> EmittedTuple<Native> emit(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble one owning core/SQL/EXISTS output from the selected assignment. |
| inputs / outputs | Complete selected frames and work counters produce AccountedTuple or public Tuple. |
| invariants | Check compiled equalities; preserve SQL repeated columns/constants; EXISTS emits one truth scalar. |
| ownership | Per-result original-account ScalarView scratch and owning output payload; no result retention inside cursor. |
| failure | Allocation, equality or work failure closes active cursor through produce while earlier results remain valid. |
| cost | O(equalities+ordered output width+deep bytes), with fresh row-view vector reserve and actual owning payload construction per result. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0121

[Lines 1085–1089](../../../../../src/runtime/support.cpp#L1085); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::AccountedStorageTable::Journal* writer(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Locate the private table journal for a tentative epoch relation. |
| inputs / outputs | Relation ID returns its current journal pointer or null for committed/untouched state. |
| invariants | A tentative cursor must see journal membership; committed views use native tables. |
| ownership | Borrowed pointer valid under retained Group/journal. |
| failure | Requires readable active snapshot; lookup itself does not throw. |
| cost | Linear search in touched journals; no table copy or new grant. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0122

[Lines 1090–1095](../../../../../src/runtime/support.cpp#L1090); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::ScalarView bound(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a fragment constraint from fixed, outer or prior-local state. |
| inputs / outputs | Source and current selected-frame vector return its scalar view. |
| invariants | Non-fixed sources must refer to already selected rows. |
| ownership | Borrowed fixed-row/frame scalar under cursor/Group lifetime. |
| failure | Missing internal selection is runtime_contract; invalid compiled positions are defects. |
| cost | One ordered map lookup for fixed values or direct slot access for frame values. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0123

[Lines 1096–1112](../../../../../src/runtime/support.cpp#L1096); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool compatible(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check bound separator and exact binding/join constraints on one candidate. |
| inputs / outputs | Tuple/frame/step/selected state returns true only when all relevant fields match. |
| invariants | Direct/restored rows must also satisfy the separator; native bucket members already satisfy the native key. |
| ownership | Borrows candidate/key/fixed values only; creates no owning row. |
| failure | Work failure propagates to cursor closure; ordinary mismatch is false, not an exception. |
| cost | Visits separator fields for direct/ghost selection and each compiled condition; scalar equality may inspect deep values. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0124

[Lines 1113–1183](../../../../../src/runtime/support.cpp#L1113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::AccountedTuple* select(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the next compatible native or before-overlay row for one factor. |
| inputs / outputs | Frame/step/constraints use direct full-key lookup when possible, otherwise lazy live/bucket cursor then restored rows. |
| invariants | Before patches exclude inserted IDs and restore removed rows; no whole-relation or emitted-output dedup history. |
| ownership | Selected tuple pointer borrows table or journal under the reader Group; keys/direct probes are cursor-owned. |
| failure | Read/allocation/work failures close the outer active cursor; address-of-entry tuple cannot be null after entry success. |
| cost | Actual direct/map/bucket probes, advances, rejected comparisons and key construction; restored lookups are ordered maps. Native next_entry already yields its borrowed tuple without another handle-to-row lookup. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0125

[Lines 1184–1189](../../../../../src/runtime/support.cpp#L1184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void close_frame(Frame& frame,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset an exhausted traversal factor before backtracking. |
| inputs / outputs | Frame clears native cursor, transient keys/direct tuple and selected pointer/open flag. |
| invariants | A prebound separator key remains for reopening the fixed bucket. |
| ownership | Releases only that frame resources, retaining cursor/Group owner. |
| failure | Work charge can fail before reset and is caught by produce mandatory cleanup. |
| cost | One charged close plus actual key/cursor destruction; no relation scan. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0126

[Lines 1190–1216](../../../../../src/runtime/support.cpp#L1190); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool has_witness(CursorWork& work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check existential hidden restrictions without enumerating the hidden Cartesian product. |
| inputs / outputs | Selected visible assignment seeds one complete survivor-subtree probe; returns whether some compatible witness exists. |
| invariants | Running intersection makes children independent after their parent row is fixed; failed child rejects that row without revisiting successful sibling combinations. |
| ownership | Reuses original-account probe frames/child lists and the same epoch Group. |
| failure | Actual work/read failure closes the parent cursor; ordinary absence returns false. |
| cost | Visits actually attempted survivor rows/constraints; potentially unbounded relative to one projected output and not a constant public delay theorem. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0127

[Lines 1217–1242](../../../../../src/runtime/support.cpp#L1217); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<bool Native> std::optional<EmittedTuple<Native>> advance(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Iteratively enumerate one next complete projected or witness assignment. |
| inputs / outputs | Cursor position/resume state returns one owning row or exhaustion; constants/nullary witnesses use the identity branch. |
| invariants | No recursion by plan depth; a complete projected assignment with hidden bindings must pass has_witness. |
| ownership | Reuses main/probe frames; only emit creates output ownership. |
| failure | Read/work/output failure is handled by produce; ordinary backtracking is normal control flow. |
| cost | Actual selected/rejected factor combinations and optional hidden probe work; no result-set materialization. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0128

[Lines 1243–1265](../../../../../src/runtime/support.cpp#L1243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<bool Native> std::optional<EmittedTuple<Native>> produce()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one next call under its original grant with one cleanup failure boundary. |
| inputs / outputs | Active cursor returns native/public owning tuple or null, updating action/phase/optional timing diagnostics. |
| invariants | Exhausted/cancelled calls stay null; failed calls reject before observation/work. Last successful row still holds the lease. |
| ownership | Prior owning rows survive failure; close releases selected borrowed state then runtime/Group. |
| failure | Catch records spent failure work, closes as failed and rethrows original typed error for public presentation. |
| cost | Actual advance/emit work plus fixed phase metrics/optional clocks; one retained storage lease across all calls. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0129

[Lines 1266–1266](../../../../../src/runtime/support.cpp#L1266); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1266-L1266:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct SupportRuntime::ResultCursor::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct SupportRuntime::ResultCursor::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct SupportRuntime::ResultCursor::Data\` at its lexical source position in src/runtime/support.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct SupportRuntime::ResultCursor::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0130

[Lines 1267–1271](../../../../../src/runtime/support.cpp#L1267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::EpochView::Group::abort()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invalidate every tentative cursor before restoring transaction state. |
| inputs / outputs | Group becomes aborted, intrusive cursors close as failed, reader is released and patches/journal/runtime references clear. |
| invariants | Next on invalidated cursors cannot access rolled-back rows; later view relation reads reject. |
| ownership | Clear borrowed cursor state before releasing retained pins/runtime. |
| failure | Noexcept/prepaid rollback preparation. |
| cost | O(linked cursors and their frame/binding cleanup plus overlay release). |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0131

[Lines 1272–1272](../../../../../src/runtime/support.cpp#L1272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor::ResultCursor(resource::AccountedUnique<Data> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt fully prepared cursor state. |
| inputs / outputs | Moves Data owner into token. |
| invariants | Factory completed preparation/linking before return. |
| ownership | Token uniquely owns Data. |
| failure | Noexcept move. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0132

[Lines 1273–1273](../../../../../src/runtime/support.cpp#L1273); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor::ResultCursor(ResultCursor&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer the complete cursor token. |
| inputs / outputs | Default move of accounted unique Data. |
| invariants | Does not open another lease or clone rows. |
| ownership | Destination owns source Data; source is empty. |
| failure | Noexcept move. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0133

[Lines 1274–1280](../../../../../src/runtime/support.cpp#L1274); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor& SupportRuntime::ResultCursor::operator=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace one cursor token and close its previous reader. |
| inputs / outputs | Move assignment transfers unique Data; self-move is a no-op. |
| invariants | Previous active Data records move_replacement cleanup before transfer. |
| ownership | Closes prior active traversal before releasing its borrowed rows/lease; existing owning outputs and other readers remain valid. Move transfers the unique Data with its original account. |
| failure | Noexcept and nonallocating: moved/closed cancel is a no-op; move self-assignment is a no-op. Impossible private lease/list ownership faults terminate instead of propagating an exception. |
| cost | O(previous cursor cleanup); transfer itself is O(1). |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0134

[Lines 1281–1281](../../../../../src/runtime/support.cpp#L1281); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor::~ResultCursor()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release token and close any active cursor. |
| inputs / outputs | Default unique-owner destruction invokes Data cleanup. |
| invariants | Data close unlinks/releases before source owners drop. |
| ownership | Final Data release destroys traversal buffers. |
| failure | Noexcept destruction; private ownership corruption terminates. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0135

[Lines 1282–1282](../../../../../src/runtime/support.cpp#L1282); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::ResultCursor::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether a cursor is currently active. |
| inputs / outputs | False for empty or terminal token. |
| invariants | No throwing validity demand. |
| ownership | Scalar only. |
| failure | Noexcept. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0136

[Lines 1283–1283](../../../../../src/runtime/support.cpp#L1283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ResultCursorState SupportRuntime::ResultCursor::state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect retained lifecycle state. |
| inputs / outputs | Returns status after Data presence check. |
| invariants | Terminal/failed state remains inspectable. |
| ownership | Scalar only. |
| failure | Empty/moved token throws invalid_cursor. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0137

[Lines 1284–1284](../../../../../src/runtime/support.cpp#L1284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t SupportRuntime::ResultCursor::sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the pinned cursor epoch stamp. |
| inputs / outputs | Returns epoch. |
| invariants | Stamp remains available after terminal close. |
| ownership | Scalar only. |
| failure | Empty/moved token throws invalid_cursor. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0138

[Lines 1285–1285](../../../../../src/runtime/support.cpp#L1285); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOwnerId SupportRuntime::ResultCursor::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the pinned logical owner identity. |
| inputs / outputs | Returns identity. |
| invariants | No membership lookup or live-runtime requirement after close. |
| ownership | Scalar only. |
| failure | Empty/moved token throws invalid_cursor. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0139

[Lines 1286–1286](../../../../../src/runtime/support.cpp#L1286); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& SupportRuntime::ResultCursor::layout() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow retained output layout descriptor. |
| inputs / outputs | Returns output_layout. |
| invariants | Descriptor remains after traversal closes. |
| ownership | Reference needs live Data token. |
| failure | Empty/moved token throws invalid_cursor. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0140

[Lines 1287–1287](../../../../../src/runtime/support.cpp#L1287); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const ResultCursorMetrics& SupportRuntime::ResultCursor::metrics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow final/current mandatory cursor accounting. |
| inputs / outputs | Returns metrics. |
| invariants | Closed cursor retains action and cleanup evidence. |
| ownership | Reference borrows Data. |
| failure | Empty/moved token throws invalid_cursor. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0141

[Lines 1288–1291](../../../../../src/runtime/support.cpp#L1288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CursorObservation SupportRuntime::ResultCursor::observation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy lifecycle report with current mandatory work/state. |
| inputs / outputs | Copies diagnostic, overwrites mandatory/status. |
| invariants | Latest work is returned even when optional metrics are disabled. |
| ownership | Fixed-size copied report. |
| failure | Empty/moved token throws invalid_cursor. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0142

[Lines 1292–1297](../../../../../src/runtime/support.cpp#L1292); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::ResultCursor::cancel()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explicitly stop an active cursor early. |
| inputs / outputs | Active token records optional cancel count and closes; closed/moved tokens are no-ops. |
| invariants | Returned owning rows and other readers remain valid. |
| ownership | Closes prior active traversal before releasing its borrowed rows/lease; existing owning outputs and other readers remain valid. Move transfers the unique Data with its original account. |
| failure | Noexcept and nonallocating: moved/closed cancel is a no-op; move self-assignment is a no-op. Impossible private lease/list ownership faults terminate instead of propagating an exception. |
| cost | O(all main/probe frames and retained binding/descriptor cleanup). |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0143

[Lines 1298–1301](../../../../../src/runtime/support.cpp#L1298); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::Tuple> SupportRuntime::ResultCursor::next()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one owning public result and translate only native boundary failures. |
| inputs / outputs | Delegates to produce&lt;false&gt; after token-presence validation. |
| invariants | Terminal/failure/lease behavior is implemented once in produce. |
| ownership | Original account owns prepared state; returned token/group retains only required shared owners. |
| failure | Invalid token/options/busy/work/memory failure propagates; typed native failures become public Error only at the boundary. |
| cost | Actual traversal/output work; wrapper adds no result copy. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0144

[Lines 1302–1305](../../../../../src/runtime/support.cpp#L1302); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::AccountedTuple> SupportRuntime::ResultCursor::next_native()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose one owning native result under the original account. |
| inputs / outputs | Delegates to produce&lt;true&gt; after token validation. |
| invariants | Retains native layout/payload; no caller Row export. |
| ownership | Original account owns prepared state; returned token/group retains only required shared owners. |
| failure | Invalid token/options/busy/work/memory failure propagates; typed native failures become public Error only at the boundary. |
| cost | Actual traversal/output work; no public Tuple payload-owner construction. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0145

[Lines 1306–1314](../../../../../src/runtime/support.cpp#L1306); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::results(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire a committed reader only after cursor startup succeeds. |
| inputs / outputs | Validated core/SQL options prepare Data through create and return a move-only token. |
| invariants | Private writer and reader overflow reject before publication; active committed readers may coexist. |
| ownership | Original account owns prepared state; returned token/group retains only required shared owners. |
| failure | Invalid token/options/busy/work/memory failure propagates; typed native failures become public Error only at the boundary. |
| cost | Actual C* startup frames; no result scan. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0146

[Lines 1315–1315](../../../../../src/runtime/support.cpp#L1315); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::EpochView::EpochView(std::shared_ptr<Data> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared shared epoch context. |
| inputs / outputs | Moves shared Data into view. |
| invariants | Factory acquired group reader lease after construction. |
| ownership | View copies share Data/Group. |
| failure | Noexcept shared-owner move. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0147

[Lines 1316–1316](../../../../../src/runtime/support.cpp#L1316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::EpochView::valid() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check presence and nonaborted group phase. |
| inputs / outputs | False for closed or aborted view. |
| invariants | Does not dereference released runtime after abort. |
| ownership | Scalar only. |
| failure | Noexcept. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0148

[Lines 1317–1317](../../../../../src/runtime/support.cpp#L1317); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::EpochView::tentative() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether valid context is still pending. |
| inputs / outputs | valid() and tentative phase. |
| invariants | Commit changes result while preserving context. |
| ownership | Scalar only. |
| failure | Noexcept. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0149

[Lines 1318–1318](../../../../../src/runtime/support.cpp#L1318); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SnapshotSide SupportRuntime::EpochView::side() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect selected side stamp. |
| inputs / outputs | Returns Data side. |
| invariants | Aborted view identity metadata remains inspectable. |
| ownership | Scalar only. |
| failure | Closed view throws invalid_snapshot. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0150

[Lines 1319–1322](../../../../../src/runtime/support.cpp#L1319); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t SupportRuntime::EpochView::sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect selected before/after sequence stamp. |
| inputs / outputs | Uses group before_sequence or after_sequence. |
| invariants | Requires Data, not nonaborted relation-read authority. |
| ownership | Scalar only. |
| failure | Closed view throws invalid_snapshot. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0151

[Lines 1323–1325](../../../../../src/runtime/support.cpp#L1323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOwnerId SupportRuntime::EpochView::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inspect the original logical owner identity. |
| inputs / outputs | Returns group identity. |
| invariants | Identity survives abort while Data remains. |
| ownership | Scalar only. |
| failure | Closed view throws invalid_snapshot. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0152

[Lines 1326–1326](../../../../../src/runtime/support.cpp#L1326); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const EpochViewMetrics& SupportRuntime::EpochView::metrics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow overlay-construction accounting. |
| inputs / outputs | Returns group metrics. |
| invariants | No relation read is attempted after invalidation. |
| ownership | Reference needs live view/group owner. |
| failure | Closed view throws invalid_snapshot. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0153

[Lines 1327–1330](../../../../../src/runtime/support.cpp#L1327); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::EpochView::has_answer() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read selected context existence. |
| inputs / outputs | After readable() guard selects before/after cached answer. |
| invariants | Aborted relation context rejects. |
| ownership | Copied Boolean. |
| failure | Closed/aborted view throws invalid_snapshot. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0154

[Lines 1331–1331](../../../../../src/runtime/support.cpp#L1331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::EpochView::close() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release this view reference. |
| inputs / outputs | Resets data_. |
| invariants | Other view/cursor references preserve shared group lease. |
| ownership | May trigger final overlay/journal/runtime release. |
| failure | Noexcept. |
| cost | Constant wrapper/access or shared/unique transfer; destruction/last release includes actual retained-state teardown. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0155

[Lines 1332–1332](../../../../../src/runtime/support.cpp#L1332); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::EpochView::results(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create unbound projected results for this epoch side. |
| inputs / outputs | Delegates to completions with empty bindings/default visible fragment. |
| invariants | Core schema; no scalar SQL mapping in this helper. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Direct delegation. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0156

[Lines 1333–1340](../../../../../src/runtime/support.cpp#L1333); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::EpochView::completions(const FixedAssignment&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create projected completions under owning exact restrictions. |
| inputs / outputs | FixedAssignment, VisibleFragment and limits -&gt; cursor. |
| invariants | Hidden fixed values restrict existential S witnesses without extra output. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Copies restriction values at startup. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0157

[Lines 1341–1348](../../../../../src/runtime/support.cpp#L1341); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::EpochView::completions_native(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create projected completions from call-only borrowed restrictions. |
| inputs / outputs | Span&lt;VariableBindingView&gt;, fragment and limits -&gt; cursor. |
| invariants | Same restrictions as owning form; no borrowed string outlives startup without a native copy. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Freezes restrictions without legacy owning Value mirror. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0158

[Lines 1349–1356](../../../../../src/runtime/support.cpp#L1349); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::EpochView::witnesses(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create complete local survivor-factor assignments. |
| inputs / outputs | FixedAssignment, WitnessFragment and limits -&gt; cursor. |
| invariants | Outputs sorted union of selected S-factor variables; no outside-parent restriction. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Builds selected survivor traversal at startup. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0159

[Lines 1357–1364](../../../../../src/runtime/support.cpp#L1357); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_keys(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one local E-factor cursor. |
| inputs / outputs | Visible C* NodeId and limits -&gt; cursor. |
| invariants | May emit local keys even when global answer is false; does not join other factors. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; One-factor traversal. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0160

[Lines 1365–1372](../../../../../src/runtime/support.cpp#L1365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_bucket(NodeId node,const Row&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a local E cursor restricted by its compiled parent separator. |
| inputs / outputs | Nonroot C* node, owning Row separator and limits -&gt; cursor. |
| invariants | Separator order/domain follow compiled index; node must have parent-key index. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Validates legacy Row before native freeze. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0161

[Lines 1373–1380](../../../../../src/runtime/support.cpp#L1373); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::EpochView::visible_bucket_native(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a local E cursor from a borrowed native separator. |
| inputs / outputs | Node, RowView separator and limits -&gt; cursor. |
| invariants | Same compiled separator relation; source view survives startup only. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Native tuple validation failures are translated here as well. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0162

[Lines 1381–1386](../../../../../src/runtime/support.cpp#L1381); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::EpochView SupportRuntime::current_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Acquire an immutable committed relation context. |
| inputs / outputs | Current sequence/truth and empty patches produce one shared Group/view lease. |
| invariants | Group acquires only after both owners are constructed; read lease blocks writers. |
| ownership | Original account owns prepared state; returned token/group retains only required shared owners. |
| failure | Invalid token/options/busy/work/memory failure propagates; typed native failures become public Error only at the boundary. |
| cost | O(plan relation count) empty Patch preparation, not O(1) nor a full data snapshot. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md), [P1 arXiv:2301.04003v2 §5.1 Algorithm 5; native ownership, overlays and work counters are local engineering contracts](https://arxiv.org/pdf/2301.04003v2) |

## B0163

[Lines 1387–1389](../../../../../src/runtime/support.cpp#L1387); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::completions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create projected completions on a newly retained committed context. |
| inputs / outputs | Bindings/fragment/limits -&gt; current_view().completions. |
| invariants | Committed reader context survives temporary view facade. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Current group creation precedes cursor setup. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0164

[Lines 1390–1392](../../../../../src/runtime/support.cpp#L1390); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::ResultCursor SupportRuntime::witnesses(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create local S-factor assignments on a committed context. |
| inputs / outputs | Bindings/fragment/limits -&gt; current_view().witnesses. |
| invariants | Moves factor selection; cursor retains shared context after temporary view dies. |
| ownership | Native funded cursor owns prepared frame/restriction metadata and retains one existing group/work lease. |
| failure | Closed/aborted view, invalid selections/bindings or work/account/allocation failure rejects before cursor publication; fixed storage failures translate to public Error at defined boundary. |
| cost | Actual startup descriptor/field/map work plus later lazy traversal; Current group creation precedes cursor setup. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0165

[Lines 1393–1403](../../../../../src/runtime/support.cpp#L1393); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SupportRuntime::PendingEpoch::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one prepared single-polarity logical epoch across stages. |
| inputs / outputs | Owner/next sequence/polarity retain one grant, output/public journal, transaction and optional drained-prefix views. |
| invariants | Changed stages alone increment prefix; token is published only after construction, observation and workload preparation succeed. |
| ownership | Original account owns transaction/journal/keys; token retains runtime, views and grant until commit/destruction. |
| failure | stage_tuple failure aborts all stages; rollback first invalidates views then destroys transaction inverses; commit publishes sequence once. |
| cost | Fixed initial owners/containers plus actual affected-record journals; no whole-state copy. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0166

[Lines 1404–1411](../../../../../src/runtime/support.cpp#L1404); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Data(std::shared_ptr<Impl> value,std::uint64_t sequence,SetOperation sign)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare one pending epoch owner before the writer flag is published. |
| inputs / outputs | Existing Impl/sequence/polarity construct output, journal, transaction and observation/workload tickets. |
| invariants | Initial has_answer is cached; prefix starts zero; all stages share one transaction and original lease. |
| ownership | Original account funds Data/journal/transaction; owner strongly retains runtime. |
| failure | Unpublished construction failure releases members; factory has not set updating yet. |
| cost | Fixed controls/empty buffers and optional ticket setup; no full state clone. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0167

[Lines 1412–1413](../../../../../src/runtime/support.cpp#L1412); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  detail::ObservationTicket observation_ticket; workload::detail::Ticket workload_ticket;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain logical operation observations until one commit/abort outcome. |
| inputs / outputs | Observation and workload tickets. |
| invariants | Tickets span entire pending epoch, not individual aliases/stages. |
| ownership | Scoped ticket values reference existing observer/workload state. |
| failure | Finish calls occur on commit/rollback. |
| cost | Fixed fields. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0168

[Lines 1414–1414](../../../../../src/runtime/support.cpp#L1414); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Data() { rollback(); }
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Automatically abort an uncommitted pending epoch at final owner release. |
| inputs / outputs | Invokes idempotent rollback. |
| invariants | Committed/closed owner is empty, so destruction does not reverse published state. |
| ownership | Releases pending resources/runtime after restoring logical state. |
| failure | Noexcept destructor cleanup. |
| cost | Actual affected undo and retained-output release. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0169

[Lines 1415–1417](../../../../../src/runtime/support.cpp#L1415); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Impl& active() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a live writer token. |
| inputs / outputs | Returns Impl reference only with owner and transaction. |
| invariants | Closed committed/aborted state cannot stage/read tentative output. |
| ownership | Borrowed pending-owned runtime. |
| failure | invalid_epoch on closed state. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0170

[Lines 1418–1427](../../../../../src/runtime/support.cpp#L1418); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void rollback() noexcept {
    if (!owner) return;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Abort pending views and reverse all unpublished logical stages. |
| inputs / outputs | Idempotent owner test; publishes failure metrics, aborts Group, destroys Transaction/output/history, finishes tickets and clears updating. |
| invariants | Views close borrowed cursors before undo; metadata then table undo restores committed contents/sequence. Existing allocated capacity/history statistics may remain visible. |
| ownership | Owns affected transaction/history and runtime; clears all private tuple borrows and writer authority. |
| failure | Noexcept; private ownership/inverse inconsistency terminates rather than hiding partial recovery. |
| cost | Affected metadata/table inverse work plus actual last-owner cleanup; no new allocation or query-wide clone. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0171

[Lines 1428–1438](../../../../../src/runtime/support.cpp#L1428); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  bool stage_tuple(const SupportNodeProgram& node,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage one validated native tuple and completely drain upward propagation. |
| inputs / outputs | Native node/tuple under fixed polarity; returns false for duplicate insertion/absent erasure. |
| invariants | Changed stage allocates one epoch-wide event, restores invariants before prefix increments; no-op adds no event/prefix. All native calls reuse retained storage lease. |
| ownership | Pending owns transaction and original account; tuple borrows caller until synchronous native copying/journaling. |
| failure | No private catch: the two public staging entry points abort retained tokens; apply and insertion replay own local RAII tokens whose destruction rolls back before failure presentation. Original exception types and consumed grants remain unchanged. |
| cost | One membership probe plus affected propagation/undo/capture. No-op skips logical event work but still performs actual native lookup. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0172

[Lines 1439–1439](../../../../../src/runtime/support.cpp#L1439); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1439-L1439:sha256:aa1d1a63390229c798347e83a0405441c9400035284ad168c1bf6cdf1d70a370
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`struct SupportRuntime::PendingEpoch::Data\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`struct SupportRuntime::PendingEpoch::Data\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`struct SupportRuntime::PendingEpoch::Data\` at its lexical source position in src/runtime/support.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`struct SupportRuntime::PendingEpoch::Data\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0173

[Lines 1440–1440](../../../../../src/runtime/support.cpp#L1440); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::PendingEpoch::PendingEpoch(resource::AccountedUnique<Data> data) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt a prepared exclusive epoch token. |
| inputs / outputs | Moves Data owner. |
| invariants | Factory sets writer flag only after Data preparation. |
| ownership | Token uniquely owns Data. |
| failure | Noexcept move. |
| cost | Fixed transfer. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0174

[Lines 1441–1441](../../../../../src/runtime/support.cpp#L1441); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::PendingEpoch::PendingEpoch(PendingEpoch&&) noexcept=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Transfer exclusive pending ownership. |
| inputs / outputs | Moves accounted unique Data. |
| invariants | No new transaction/grant or published sequence. |
| ownership | Destination adopts original Data. |
| failure | Noexcept move. |
| cost | Fixed transfer. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0175

[Lines 1442–1445](../../../../../src/runtime/support.cpp#L1442); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::PendingEpoch& SupportRuntime::PendingEpoch::operator=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace this pending token with another. |
| inputs / outputs | Self guard then unique-owner move. |
| invariants | Old uncommitted token is rolled back by destruction. |
| ownership | Transfers original account/Data; source empty. |
| failure | Noexcept under affected rollback invariants. |
| cost | Affected old rollback plus fixed transfer. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0176

[Lines 1446–1446](../../../../../src/runtime/support.cpp#L1446); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::PendingEpoch::~PendingEpoch()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Release or roll back pending work automatically. |
| inputs / outputs | Default Data owner destruction. |
| invariants | Published epoch has no remaining owner/transaction to undo. |
| ownership | Releases original Data and buffers. |
| failure | Noexcept cleanup. |
| cost | Actual pending rollback/destruction work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0177

[Lines 1447–1447](../../../../../src/runtime/support.cpp#L1447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::PendingEpoch::active() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test pending writer validity without throwing. |
| inputs / outputs | Checks Data, owner and transaction. |
| invariants | False for moved/committed/aborted token. |
| ownership | Scalar only. |
| failure | Noexcept. |
| cost | Fixed pointer tests. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0178

[Lines 1448–1448](../../../../../src/runtime/support.cpp#L1448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::PendingEpoch::rollback() noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose idempotent explicit epoch abort. |
| inputs / outputs | Calls Data.rollback if Data exists. |
| invariants | Empty/closed token is a safe no-op. |
| ownership | Releases pending-only ownership; restores runtime writability. |
| failure | Noexcept cleanup. |
| cost | Actual affected undo; no allocation. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0179

[Lines 1449–1461](../../../../../src/runtime/support.cpp#L1449); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::PendingEpoch::stage(NodeId id,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and stage one owning logical row under the token polarity. |
| inputs / outputs | Native node ID and caller Row return true only if membership changes after propagation drains. |
| invariants | A held prefix view rejects busy before the abort scope and leaves the epoch active; all other staged validation/mutation failures abort every prior stage. |
| ownership | Imports caller row into authoritative original-account layout; transaction retains needed inverses. |
| failure | The public catch covers validation and staging, aborting all prior stages and closing a caller-held token before presentation. Direct private callers use their local RAII token for abort; pinned-prefix busy rejection remains outside this abort scope. |
| cost | Exact validation/tuple import and affected propagation; no-op returns without event work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0180

[Lines 1462–1464](../../../../../src/runtime/support.cpp#L1462); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SupportEpoch& SupportRuntime::PendingEpoch::preview() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow unpublished drained epoch output. |
| inputs / outputs | Requires Data and active owner. |
| invariants | Caller must not publish tentative values as committed; later stage can change output. |
| ownership | Reference borrows pending Data. |
| failure | invalid_epoch for moved/closed token. |
| cost | Fixed guard/reference. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0181

[Lines 1465–1478](../../../../../src/runtime/support.cpp#L1465); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::PendingEpoch::stage_native(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stage a native accounted tuple through the same atomic transaction. |
| inputs / outputs | Node and native tuple enforce layout token identity before stage_tuple. |
| invariants | Prefix-busy rejection preserves active epoch; incompatible token or mutation failure aborts all previous stages. |
| ownership | Borrows/imports no caller Row; shared grant and private undo remain token-owned. |
| failure | Layout failure is typed native error before public translation; rollback is allocation-free. |
| cost | Fixed token/layout checks plus actual lookup/affected work; no diagnostic export. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0182

[Lines 1479–1483](../../../../../src/runtime/support.cpp#L1479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportSnapshot SupportRuntime::PendingEpoch::snapshot() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export tentative logical diagnostic state. |
| inputs / outputs | Requires active token; uses its retained storage lease and pending sequence. |
| invariants | Explicit unpublished diagnostic, not immutable versioned state or rollback authority. |
| ownership | Caller owns outer DTO; tuples retain original account. |
| failure | Closed/work/account/export allocation failure propagates; token remains active. |
| cost | Complete snapshot traversal and payload/flag copies. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0183

[Lines 1484–1497](../../../../../src/runtime/support.cpp#L1484); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::EpochView SupportRuntime::PendingEpoch::view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze the drained whole-epoch before/after relation context. |
| inputs / outputs | Side/options -&gt; reused or new tentative Group/Data. |
| invariants | Different pinned prefix rejects busy; construction failure leaves pending epoch active. Group acquisition is published only after Data exists. |
| ownership | Group strongly owns runtime/history and original storage lease; view/cursor references share one reader. |
| failure | Invalid marker/side, pinned-prefix busy or resource failure propagates without aborting pending epoch. Public fixed storage diagnostics translate at boundary. |
| cost | O(plan relations + selected journal history and affected index overlay keys), no complete copied database. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0184

[Lines 1498–1501](../../../../../src/runtime/support.cpp#L1498); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::PendingEpoch::Checkpoint SupportRuntime::PendingEpoch::checkpoint() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stamp one drained private stage prefix. |
| inputs / outputs | Copies owner/sequence/prefix/journal length/answer. |
| invariants | Does not acquire reader or freeze tables. |
| ownership | Scalar marker only. |
| failure | Closed token rejects invalid_epoch. |
| cost | Fixed reads. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0185

[Lines 1502–1508](../../../../../src/runtime/support.cpp#L1502); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::span<const JournalRecord> SupportRuntime::PendingEpoch::stage_records(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow exactly one changed-stage journal suffix. |
| inputs / outputs | Checkpoint must match owner/sequence and precede current prefix by exactly one. |
| invariants | Unrelated/multiple/no-op stage markers cannot authorize suffix reading. |
| ownership | Span borrows pending journal; later staging/growth may invalidate it. |
| failure | Invalid/closed/mismatched marker throws. |
| cost | Fixed checks and subspan. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0186

[Lines 1509–1523](../../../../../src/runtime/support.cpp#L1509); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::EpochView SupportRuntime::PendingEpoch::stage_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze one exact changed-stage before/after context. |
| inputs / outputs | Validated Checkpoint, side/options -&gt; suffix Group/Data. |
| invariants | Reuses only matching journal-begin/prefix context; another retained context rejects busy. |
| ownership | Group strongly owns runtime/history and original storage lease; view/cursor references share one reader. |
| failure | Invalid marker/side, pinned-prefix busy or resource failure propagates without aborting pending epoch. Public fixed storage diagnostics translate at boundary. |
| cost | Same overlay costs restricted to selected journal suffix, plus exact marker validation. |
| Design | [docs/result_cursors.md](../../../../result_cursors.md), [docs/epoch_views.md](../../../../epoch_views.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0187

[Lines 1524–1539](../../../../../src/runtime/support.cpp#L1524); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportEpoch SupportRuntime::PendingEpoch::commit()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Publish the fully drained prepared epoch without throwing work. |
| inputs / outputs | Active token returns prepared SupportEpoch, commits native journals and advances the logical sequence once. |
| invariants | Validate token before barrier; existing views become committed and keep readers until their final release. |
| ownership | Moves prepared output/journal to caller, destroys private inverses and releases writer owner. |
| failure | Only token validation throws; all later publication/destruction/diagnostic completion is nonallocating. |
| cost | O(touched journals and undo release), no new row propagation or result construction. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0188

[Lines 1540–1548](../../../../../src/runtime/support.cpp#L1540); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::PendingEpoch SupportRuntime::begin_epoch(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare an exclusive writer for one contiguous sequence and polarity. |
| inputs / outputs | Next sequence/insert-or-erase produce a move-only pending token. |
| invariants | Reject writer/readers, sequence overflow/gaps and unknown polarity before setting updating. |
| ownership | Original account funds Data and one retained grant; writer flag publishes after construction. |
| failure | Preparation failure leaves committed state and writer readiness unchanged. |
| cost | Fixed admission plus actual transaction/journal-owner preparation; no live-state clone. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0190

[Lines 1550–1661](../../../../../src/runtime/support.cpp#L1550); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::initialize_native(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build initial support state on an empty unpublished logical owner. |
| inputs / outputs | Native seeds plus direct/insertion_replay BuildOptions and cumulative BuildMetrics. |
| invariants | Requires sequence zero/empty relations. Observation is temporarily moved out and restored. Replay uses one cumulative build budget; direct mode derives postorder from edges and child keys, not numeric ID order. |
| ownership | Original account funds records/support/cold scratch. Restorer objects restore observation/options on every exit; no source/caller span retained. |
| failure | Malformed seeds/options or work/counter/account failure abort initialization of this unpublished owner. Direct mode does not promise per-call rollback to empty; coordinator must discard failed owner. Replay per-input transaction rolls back its affected stage. |
| cost | Full seed/node/postorder/storage population construction, child probes and projected counting. Replay creates/releases per-seed undo immediately. Final retained census visits nodes/relations/indexes. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [docs/runtime_initialization.md](../../../../runtime_initialization.md) |

## B0192

[Lines 1663–1663](../../../../../src/runtime/support.cpp#L1663); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::seed_sequence(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install a coordinator-supplied sequence after private unpublished initialization. |
| inputs / outputs | Writes impl_-&gt;sequence. |
| invariants | Private precondition: valid initialized Impl and externally established sequence; no public admission checks here. |
| ownership | Existing runtime only. |
| failure | Noexcept; invalid private owner violates precondition. |
| cost | One scalar store. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0194

[Lines 1665–1666](../../../../../src/runtime/support.cpp#L1665); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::SupportRuntime(PhysicalPlan plan,SupportOptions options)

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an admitted support owner from a checked physical plan. |
| inputs / outputs | Plan/options delegate with a new finite context at options memory cap. |
| invariants | Imported executable metadata/tables use that receiving account. |
| ownership | Impl/state/tables/metadata and scratch are funded by receiver; caller artifact survives independently. |
| failure | Unpublished construction unwinds; fixed storage errors become public Error while MemoryFailure/allocation failures propagate. |
| cost | Cold native import/materialization and O(nodes+edges) routing metadata; constructor copies handle values but not runtime population. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0195

[Lines 1667–1673](../../../../../src/runtime/support.cpp#L1667); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::SupportRuntime(CompiledProgram source,SupportOptions options) try
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an admitted owner from an existing native compiler artifact. |
| inputs / outputs | Creates receiver context, freezes source into it, validates matching limits, allocates Impl. |
| invariants | Original compiler account remains separate; no uncharged retained executable mirror. |
| ownership | Impl/state/tables/metadata and scratch are funded by receiver; caller artifact survives independently. |
| failure | Unpublished construction unwinds; fixed storage errors become public Error while MemoryFailure/allocation failures propagate. |
| cost | Cold native import/materialization and O(nodes+edges) routing metadata; constructor copies handle values but not runtime population. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0196

[Lines 1674–1675](../../../../../src/runtime/support.cpp#L1674); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::SupportRuntime(PhysicalPlan plan,SupportOptions options,std::shared_ptr
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose support with an existing physical coordinator context. |
| inputs / outputs | Validated context, plan/options allocate Impl. |
| invariants | Reuses same account/cap and active storage operation, no replacement grant. |
| ownership | Impl/state/tables/metadata and scratch are funded by receiver; caller artifact survives independently. |
| failure | Unpublished construction unwinds; fixed storage errors become public Error while MemoryFailure/allocation failures propagate. |
| cost | Cold native import/materialization and O(nodes+edges) routing metadata; constructor copies handle values but not runtime population. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0197

[Lines 1676–1677](../../../../../src/runtime/support.cpp#L1676); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::SupportRuntime(CompiledProgram plan,SupportOptions options,std::shared_ptr
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compose a native program with existing query authority. |
| inputs / outputs | Validates context/limits and constructs Impl from native metadata. |
| invariants | Program is already authoritative under matching query context; no independent cap is minted. |
| ownership | Impl/state/tables/metadata and scratch are funded by receiver; caller artifact survives independently. |
| failure | Unpublished construction unwinds; fixed storage errors become public Error while MemoryFailure/allocation failures propagate. |
| cost | Cold native import/materialization and O(nodes+edges) routing metadata; constructor copies handle values but not runtime population. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0198

[Lines 1678–1679](../../../../../src/runtime/support.cpp#L1678); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::~SupportRuntime()=default;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use shared Impl destruction and move for runtime facade lifetime. |
| inputs / outputs | Default destructor and noexcept move constructor. |
| invariants | Retained readers/pending tokens can keep Impl alive after facade destruction. |
| ownership | Shared ownership transfer/release. |
| failure | Noexcept cleanup. |
| cost | Fixed reference transfer; final release destroys actual state. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0199

[Lines 1680–1680](../../../../../src/runtime/support.cpp#L1680); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime& SupportRuntime::operator=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace runtime facade by transferring its shared owner. |
| inputs / outputs | Self guard then shared_ptr move. |
| invariants | Existing retained cursors/pending tokens keep their original owner. |
| ownership | Releases old facade reference then adopts source. |
| failure | Noexcept transfer. |
| cost | Fixed move plus possible complete old-state final destruction. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0200

[Lines 1681–1681](../../../../../src/runtime/support.cpp#L1681); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportRuntime::Impl& SupportRuntime::impl() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a live facade before private access. |
| inputs / outputs | Returns Impl reference. |
| invariants | Moved facade never dereferences null. |
| ownership | Reference borrows shared Impl. |
| failure | invalid_runtime when empty. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0201

[Lines 1682–1682](../../../../../src/runtime/support.cpp#L1682); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& SupportRuntime::plan() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow current admitted immutable executable metadata. |
| inputs / outputs | Returns Impl plan. |
| invariants | Does not lower/export a PhysicalPlan or query state. |
| ownership | Reference needs facade/Impl owner. |
| failure | Moved facade rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0202

[Lines 1683–1683](../../../../../src/runtime/support.cpp#L1683); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const SupportOptions& SupportRuntime::options() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow established support configuration. |
| inputs / outputs | Returns Impl options. |
| invariants | No new configuration/grant is constructed. |
| ownership | Reference needs live facade. |
| failure | Moved facade rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0203

[Lines 1684–1684](../../../../../src/runtime/support.cpp#L1684); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryStatistics SupportRuntime::accounted_memory_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy actual original-query allocation counters. |
| inputs / outputs | Returns account.statistics(). |
| invariants | Requested-byte scope differs from process RSS and explicit caller DTO exports. |
| ownership | Fixed value copy. |
| failure | Moved facade rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0204

[Lines 1685–1685](../../../../../src/runtime/support.cpp#L1685); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportOwnerId SupportRuntime::owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read public logical owner identity. |
| inputs / outputs | Returns Impl owner. |
| invariants | No storage/table identity substitution. |
| ownership | Scalar value. |
| failure | Moved facade rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0205

[Lines 1686–1686](../../../../../src/runtime/support.cpp#L1686); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t SupportRuntime::sequence() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read latest committed sequence. |
| inputs / outputs | Returns Impl sequence. |
| invariants | Pending prefix has not advanced committed sequence. |
| ownership | Scalar value. |
| failure | Moved facade rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0206

[Lines 1687–1687](../../../../../src/runtime/support.cpp#L1687); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::ready() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check writer/reader exclusion status. |
| inputs / outputs | True iff not updating and readers==0. |
| invariants | False even for no-op writer intent when a reader lease is held. |
| ownership | Scalar value; not synchronization. |
| failure | Moved facade rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0207

[Lines 1688–1688](../../../../../src/runtime/support.cpp#L1688); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool SupportRuntime::has_answer() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read committed existence through constant/tree route. |
| inputs / outputs | Requires readable; returns root-S nonemptiness or route constant. |
| invariants | Busy prepared owner rejects; this is no full answer enumeration. |
| ownership | Scalar value. |
| failure | Moved/busy owner rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0208

[Lines 1689–1692](../../../../../src/runtime/support.cpp#L1689); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& SupportRuntime::result_layout(ResultView view) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow core or SQL output schema. |
| inputs / outputs | Checks view tag then selects retained descriptor. |
| invariants | Schema inspection does not enumerate data. |
| ownership | Reference needs live facade/descriptor owner. |
| failure | Moved/invalid view rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0209

[Lines 1693–1716](../../../../../src/runtime/support.cpp#L1693); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportEpoch SupportRuntime::apply(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one logical set update with the historical no-op fast path. |
| inputs / outputs | Contiguous sequence/native node/polarity/typed row return committed epoch. |
| invariants | No-op still requires writer-ready state, consumes sequence, has zero support metrics/null journal; real change uses begin/stage/commit. |
| ownership | No physical table routing or alias derivation counts; those belong to PhysicalRuntime. |
| failure | Validation failures precede publication; transaction destructor protects real-change failures before public native-error translation. |
| cost | One validation/lookup for no-op; real path may repeat checked admission/lookup plus actual affected-record maintenance. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/prepared_epochs.md](../../../../prepared_epochs.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0211

[Lines 1718–1723](../../../../../src/runtime/support.cpp#L1718); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<SupportHandle> SupportRuntime::find(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an exact typed row/key in one committed logical relation. |
| inputs / outputs | Node/role/caller Row -&gt; optional logical SupportHandle. |
| invariants | Validates layout and readable state; source Row is imported to authoritative native token before lookup. |
| ownership | Temporary native probe uses original account; returned scalar handle owns no row. |
| failure | Bad node/role/layout, busy, grant/account or allocation failure propagates; fixed native failures translate at public boundary. |
| cost | Native row validation/copy/hash/ordered lookup plus direct handle construction; not allocation-free. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0212

[Lines 1724–1726](../../../../../src/runtime/support.cpp#L1724); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::AccountedLayout& SupportRuntime::relation_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow a committed relation's authoritative native layout token. |
| inputs / outputs | Node/role resolve table layout. |
| invariants | Rejects active prepared writer through readable guard; descriptor does not authorize another runtime's tuple. |
| ownership | Reference requires runtime/table generation to survive. |
| failure | Moved/busy/bad node/role rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0213

[Lines 1727–1733](../../../../../src/runtime/support.cpp#L1727); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::Tuple> SupportRuntime::get(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve an owned logical handle to an independent owning tuple. |
| inputs / outputs | Checks runtime owner then node/role/table-local ID; absent same-owner row returns null. |
| invariants | Foreign owner is rejected; tuple ID alone does not authorize cross-runtime lookup. |
| ownership | plan_tuple deep-copies native payload under output attribution and public tuple retains its own account owner. |
| failure | Moved/busy/foreign/invalid handle and native work/account/allocator failure propagates; no stale raw pointer escapes. |
| cost | ID lookup plus actual owning tuple field/byte copy and shared control; no complete relation scan. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0214

[Lines 1734–1745](../../../../../src/runtime/support.cpp#L1734); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::ArenaStatistics SupportRuntime::storage_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Aggregate exact arena record/slot/pin state across compiled relations. |
| inputs / outputs | Checked sums of each table's current arena counters. |
| invariants | Counts include retained/free/exhausted arena metadata; not allocator bytes or process memory. |
| ownership | Fixed copied aggregate. |
| failure | Moved/busy state or aggregate size overflow rejects. |
| cost | O(compiled relations) fixed counter reads; no row payload copy. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0215

[Lines 1746–1746](../../../../../src/runtime/support.cpp#L1746); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<CursorObservation> SupportRuntime::last_cursor_observation() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the latest enabled lifecycle publication. |
| inputs / outputs | Returns optional last_cursor. |
| invariants | Neither cumulative cursor totals nor support update metrics; no data-read guard needed. |
| ownership | Fixed copied report; no lease. |
| failure | Moved facade rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0216

[Lines 1747–1759](../../../../../src/runtime/support.cpp#L1747); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Gauges> Gauges SupportRuntime::Impl::state_gauges(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture local committed relation sizes into the chosen ownership form. |
| inputs / outputs | Caller/native empty gauge result -&gt; stamped node cardinalities. |
| invariants | Requires readable state. E availability only on C*; unsupported base/global result/memory/recovery facts remain unavailable. |
| ownership | Ordinary DTO vectors or supplied native OwnerAllocator vectors own output according to concrete Gauges type. |
| failure | Busy/memory/capacity failure returns no partial public report; live relations unchanged. |
| cost | O(plan nodes) cardinality reads and output vector capacity; no tuple/answer enumeration. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0217

[Lines 1760–1762](../../../../../src/runtime/support.cpp#L1760); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CommittedStateGauges SupportRuntime::committed_state_gauges() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export caller-owned committed local cardinalities. |
| inputs / outputs | Delegates to state_gauges with ordinary DTO. |
| invariants | Explicit read works even when optional observation is off. |
| ownership | Outer arrays are caller/export storage; no retained row ownership. |
| failure | Moved/busy or ordinary allocation failure propagates. |
| cost | O(nodes) vector population, no answer traversal. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0218

[Lines 1763–1765](../../../../../src/runtime/support.cpp#L1763); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedStateGauges SupportRuntime::capture_state_gauges() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture retained native-funded local cardinalities. |
| inputs / outputs | Constructs gauge allocator from admitted program account then delegates. |
| invariants | Same facts as ordinary DTO; source query cap remains authoritative. |
| ownership | OwnerAllocator capture arrays retain original account after runtime release. |
| failure | Moved/busy/account/allocation failures propagate; no fresh allowance. |
| cost | O(nodes) metadata copy and actual funded capacity. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0219

[Lines 1766–1769](../../../../../src/runtime/support.cpp#L1766); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportSnapshot SupportRuntime::snapshot() const try
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export complete owning committed logical diagnostic state. |
| inputs / outputs | Opens one composed storage operation, requires readable and stamps sequence. |
| invariants | Snapshot is explicit inspection; ordinary updates use affected journals. |
| ownership | Caller owns outer DTO; copied tuple payloads use original account. |
| failure | Busy/native-work/account/export allocation failure propagates; source unchanged. |
| cost | Visits all node relations/metadata and copies keys/flags; full population cost. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0220

[Lines 1770–1776](../../../../../src/runtime/support.cpp#L1770); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
detail::AccountedRowSet SupportRuntime::record_rows(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a native-funded complete record-row set for diagnostics. |
| inputs / outputs | Node -&gt; AccountedRowSet from table snapshot values. |
| invariants | Private explicit read, not ordinary update state or uncharged legacy snapshot. |
| ownership | Original program account funds row-set nodes/payloads and table snapshot temporaries. |
| failure | Invalid/busy/work/account/allocation failure unwinds private set. |
| cost | Full selected record table snapshot plus ordered set insertion/copies. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp) |

## B0221

[Lines 1777–1799](../../../../../src/runtime/support.cpp#L1777); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportSnapshot SupportRuntime::Impl::snapshot(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct the owning complete logical diagnostic graph. |
| inputs / outputs | Visible sequence stamp -&gt; existence and every node record/S/P/E/metadata snapshot. |
| invariants | Stored rows are joined back to their numeric metadata; optional E list absent outside C*. No rollback authority is replaced. |
| ownership | Outer standard vectors/flags are caller export; native snapshots and copied output tuples consume original account. |
| failure | Resource/lookup invariant failures propagate; no source mutation. |
| cost | Full relation snapshots plus repeated membership/ID probes and field/byte/child-flag copies; not constant work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0223

[Lines 1801–1829](../../../../../src/runtime/support.cpp#L1801); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CanonicalSupportState SupportRuntime::canonical_state() const try
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a deterministic logical state for comparison/debugging. |
| inputs / outputs | Physical digest/catalog version/sequence plus sorted records, sets and key/count arrays. |
| invariants | Sorts by exact values/node IDs, so backend iteration/insertion history does not define canonical output. |
| ownership | Explicit ordinary owning DTO/string/Row containers; native traversal uses original storage operation. |
| failure | Busy/work/native/account/export allocation failure propagates; no mutation. |
| cost | Visits all state, exports every scalar/string and sorts rows/keys; O(population log population) comparison costs plus value width. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [include/crown/runtime/inspection.hpp](../../../../../include/crown/runtime/inspection.hpp) |

## B0225

[Lines 1831–1974](../../../../../src/runtime/support.cpp#L1831); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
InvariantReport SupportRuntime::inspect_invariants(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute independently derived logical expectations and collect bounded diagnostic issues. |
| inputs / outputs | InspectionOptions -&gt; native-funded InvariantReport with complete/truncated status. |
| invariants | Checks storage separately, reconstructs generalized union and child-derived S then expected P/E counts. Presence/count/metadata discrepancies become issues, not repaired state. |
| ownership | InspectionContext funds copied issue keys and expected sets/count maps under original account. |
| failure | InspectionStop is normal explicit truncation. Specific structural errors become storage issues; allocation and unrelated failures propagate. Public fixed failures translate after cleanup. |
| cost | Full storage/index/record scans and ordered expected-state recomputation. Lower-level diagnostics may contain extra quadratic scans beyond coarse precharges; no ordinary-update complexity claim. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [docs/invariant_memory.md](../../../../invariant_memory.md), [src/runtime/inspection_detail.hpp](../../../../../src/runtime/inspection_detail.hpp) |

## B0226

[Lines 1975–1976](../../../../../src/runtime/support.cpp#L1975); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1975-L1976:sha256:49a0204a55486ff5ff627d17889c8c42573ed57aa854aef5e271007e96b9c377
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/support.cpp: opens/branches compile-time guard \`#ifdef CROWN_RUNTIME_TESTING\`. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0227

[Lines 1977–1981](../../../../../src/runtime/support.cpp#L1977); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose original indexed grant accounting to test fixtures. |
| inputs / outputs | Returns null for reference, otherwise configured/observed/fresh-operation counters. |
| invariants | Testing-only compilation; does not create a new grant. |
| ownership | Copied counters. |
| failure | Moved runtime rejected. |
| cost | Fixed context reads. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0228

[Lines 1982–1982](../../../../../src/runtime/support.cpp#L1982); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount RuntimeTestProbe::memory_account(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the real runtime account for allocation tests. |
| inputs / outputs | Returns existing shared account. |
| invariants | No cap refill or replacement. |
| ownership | Shared account copy. |
| failure | Moved runtime rejected. |
| cost | Fixed account retain. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0229

[Lines 1983–1990](../../../../../src/runtime/support.cpp#L1983); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
SupportValueState RuntimeTestProbe::record_metadata(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one owned record's exact flags for test assertions. |
| inputs / outputs | Owned record handle -&gt; satisfied/retained flags. |
| invariants | Owner/role/node/presence validated; no direct metadata mutation. |
| ownership | Funded flag copy. |
| failure | Bad/busy/missing record or allocation fails. |
| cost | Map lookup and O(child count) copy. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0230

[Lines 1991–1998](../../../../../src/runtime/support.cpp#L1991); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t RuntimeTestProbe::set_satisfied(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject a deliberate satisfied-count inconsistency for tests. |
| inputs / outputs | Writable node/row and count -&gt; prior count. |
| invariants | Testing-only hook bypasses support recurrence; caller restores value. |
| ownership | Mutates existing metadata only. |
| failure | Missing/busy/invalid node/row rejects. |
| cost | Native probe/temporary tuple then scalar exchange. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0231

[Lines 1999–2006](../../../../../src/runtime/support.cpp#L1999); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t RuntimeTestProbe::set_projection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject a deliberate P/E counter inconsistency for tests. |
| inputs / outputs | Writable node/role/key and count -&gt; prior count. |
| invariants | Testing-only hook does not publish a sequence or propagate; caller restores value. |
| ownership | Mutates existing map count. |
| failure | Bad/busy/missing key rejects. |
| cost | Native probe/temporary tuple then scalar exchange. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [tests/support/runtime_probe.hpp](../../../../../tests/support/runtime_probe.hpp) |

## B0232

[Lines 2007–2008](../../../../../src/runtime/support.cpp#L2007); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L2007-L2008:sha256:8b63d4e2e6cce4baf5403993210754bed64f3d3fa8e57007f2c3eeff4491a972
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/runtime/support.cpp: closes the matching compile-time guard. |
| inputs / outputs | Preprocessor definitions select which tokens compile; any members or declarations in this span are those explicitly listed in its source lines. |
| invariants | The preprocessor guard pairs with its matching directive; it is a compile-time boundary, not a runtime mode. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | This span changes compile/link structure and type layout. Runtime initialization, allocation, exceptions and operation work follow the declared owner/callable code; no absence is inferred from declaration syntax. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0233

[Lines 2009–2053](../../../../../src/runtime/support.cpp#L2009); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::check_invariants() const try
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Perform the explicit throwing full-state invariant check. |
| inputs / outputs | Readable owner -&gt; validates storage, record flag/count/S recurrence, generalized unions and exact projected P/E counts. |
| invariants | Recomputes support from actual children and survivor projections; no mutation/repair or automatic invocation in ordinary apply. |
| ownership | Expected row/count sets and table snapshots are original-account scratch. |
| failure | First mismatch throws; native-work/account/allocation failure also propagates through public presentation boundary. |
| cost | Complete relation/child/projection scans, snapshots and ordered expected maps; lower-level storage diagnostic scans can be quadratic. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [docs/invariant_memory.md](../../../../invariant_memory.md) |

## B0234

[Lines 2054–2054](../../../../../src/runtime/support.cpp#L2054); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<detail::ObservationState> SupportRuntime::observation_state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the established optional observer with private composition. |
| inputs / outputs | Returns existing observation shared_ptr, possibly empty. |
| invariants | Does not enable instrumentation or create its controls. |
| ownership | Shared observer handle, no data reader. |
| failure | Moved runtime rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0235

[Lines 2055–2057](../../../../../src/runtime/support.cpp#L2055); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationSnapshot SupportRuntime::observations() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy enabled observation counters/status. |
| inputs / outputs | Delegates with established observer/options. |
| invariants | Disabled/unavailable facts remain explicit; no observation configuration or query cap is replaced. |
| ownership | Explicit copied report. |
| failure | Moved/trace capture allocation or byte-budget failure propagates according to helper. |
| cost | Registry/report copy, no data enumeration. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0236

[Lines 2058–2060](../../../../../src/runtime/support.cpp#L2058); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ObservationTrace SupportRuntime::observation_trace() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export optional trace through the caller DTO boundary. |
| inputs / outputs | Delegates with established observer/options. |
| invariants | Disabled/unavailable facts remain explicit; no observation configuration or query cap is replaced. |
| ownership | Ordinary explicit caller trace container. |
| failure | Moved/trace capture allocation or byte-budget failure propagates according to helper. |
| cost | Copies retained trace entries; no result recomputation. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0237

[Lines 2061–2063](../../../../../src/runtime/support.cpp#L2061); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CapturedObservationTrace SupportRuntime::capture_observation_trace() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture retained native observation trace. |
| inputs / outputs | Delegates with observer/options and original program account. |
| invariants | Disabled/unavailable facts remain explicit; no observation configuration or query cap is replaced. |
| ownership | Funded capture owner survives runtime. |
| failure | Moved/trace capture allocation or byte-budget failure propagates according to helper. |
| cost | Copies retained trace into original-account arrays. |
| Design | [docs/observability.md](../../../../observability.md), [include/crown/runtime/observation.hpp](../../../../../include/crown/runtime/observation.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0238

[Lines 2064–2066](../../../../../src/runtime/support.cpp#L2064); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
}  // namespace crown::runtime

namespace crown::runtime {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reopen runtime scope for workload-statistics methods. |
| inputs / outputs | Namespace boundary only. |
| invariants | No new runtime owner or operation is started. |
| ownership | No instance. |
| failure | Compile-time syntax only. |
| cost | Zero runtime cost. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0239

[Lines 2067–2069](../../../../../src/runtime/support.cpp#L2067); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::configure_workload_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure workload statistics under exclusive committed access. |
| inputs / outputs | Options and admitted program reset/configure metadata at current sequence. |
| invariants | writable rejects active readers/writer; optional statistics use their existing runtime account. |
| ownership | Workload state owns funded observation metadata. |
| failure | Busy/invalid options/account/allocation failure propagates before configured publication per helper. |
| cost | Explicit program/statistics initialization; not an ordinary propagation primitive. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp) |

## B0240

[Lines 2070–2072](../../../../../src/runtime/support.cpp#L2070); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::reset_workload_statistics()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reset configured workload facts at a writable committed boundary. |
| inputs / outputs | Uses current committed sequence. |
| invariants | Does not rebuild tables, change query sequence or refill memory/work budgets. |
| ownership | Existing workload state retains its account/configuration. |
| failure | Moved/busy or helper failure propagates. |
| cost | Explicit workload-state reset cost; no answer enumeration. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp) |

## B0241

[Lines 2073–2075](../../../../../src/runtime/support.cpp#L2073); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::Snapshot SupportRuntime::workload_statistics() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot current workload evidence with correct pending status. |
| inputs / outputs | Passes admitted program, owner, sequence and updating flag. |
| invariants | Pending state is reported by helper instead of inventing committed statistics. |
| ownership | Retained snapshot ownership follows workload helper; original account stays authoritative. |
| failure | Moved/capture resource failure propagates. |
| cost | Explicit evidence copying/aggregation, separate from updates. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/workload_statistics_detail.hpp](../../../../../src/runtime/workload_statistics_detail.hpp) |

## B0242

[Lines 2076–2076](../../../../../src/runtime/support.cpp#L2076); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
workload::detail::State& SupportRuntime::workload_state() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow private workload state for coordinator composition. |
| inputs / outputs | Returns existing mutable workload State reference. |
| invariants | Private caller uses owner's established operation scope. |
| ownership | Borrowed state requires retained Impl. |
| failure | Moved runtime rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0243

[Lines 2077–2077](../../../../../src/runtime/support.cpp#L2077); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram& SupportRuntime::compiled_program() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow State's authoritative frozen program. |
| inputs / outputs | Returns state-&gt;compiled. |
| invariants | No PhysicalPlan export or planner reconstruction. |
| ownership | Reference borrows retained State. |
| failure | Moved runtime rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0244

[Lines 2078–2078](../../../../../src/runtime/support.cpp#L2078); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<detail::StorageWorkContext> SupportRuntime::storage_context() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share original storage/account authority with private composition. |
| inputs / outputs | Returns existing context handle. |
| invariants | No replacement cap, balance clone or new operation grant. |
| ownership | Shared existing context. |
| failure | Moved runtime rejects. |
| cost | Constant guard/access or fixed-size value copy; no allocation or grant refill. |
| Design | [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0245

[Lines 2079–2081](../../../../../src/runtime/support.cpp#L2079); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace crown::runtime
#include "owner_statistics_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Connect explicit owner-statistics implementation after workload methods. |
| inputs / outputs | Scope close, private helper include and runtime namespace reopening. |
| invariants | No instrumentation owner or capture occurs merely through include. |
| ownership | Compile-time dependency. |
| failure | Missing helper fails compilation. |
| cost | Zero runtime work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0246

[Lines 2082–2120](../../../../../src/runtime/support.cpp#L2082); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void SupportRuntime::append_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one selected node/index support component with explicit incomplete distributions. |
| inputs / outputs | OwnerBuilder/Selection -&gt; appended component/cardinality/distribution or unavailable/not_applicable. |
| invariants | records/S can use field selection; P/E support distributions require complete stored keys. Weighted masses are local support counts. Only explicit budget/index-work exhaustion becomes incomplete; corruption/ownership failures still propagate. |
| ownership | Builder original account funds retained distributions and scratch; table/key references borrow current owner operation. |
| failure | Nested Exhausted handlers preserve partial/capped report. Specific IndexFailure(storage_work_limit) stops distribution; other native failures rethrow to public presentation. No arbitrary error is reported as successful exact output. |
| cost | Explicit selected relation/index scan, scalar field/key copies and distribution aggregation; not per-update automatic capture. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp), [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp) |

## B0247

[Lines 2121–2123](../../../../../src/runtime/support.cpp#L2121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::OwnerCapture SupportRuntime::capture_statistics(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward owning statistics request to borrowed-view implementation. |
| inputs / outputs | OwnerRequest and limits -&gt; capture_statistics_view. |
| invariants | One common builder enforces selection/budget semantics. |
| ownership | Request is call-only; retained result uses original account. |
| failure | View implementation failures propagate. |
| cost | Direct delegation plus explicit selected capture work. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp) |

## B0248

[Lines 2124–2129](../../../../../src/runtime/support.cpp#L2124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::OwnerCapture SupportRuntime::capture_statistics_view(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a stamped native statistics capture under the original account. |
| inputs / outputs | Borrowed request and limits -&gt; OwnerBuilder result. |
| invariants | Builder sees updating flag; visits selections only while active and preserves explicit availability/completion. |
| ownership | Result owns funded metadata/keys; source request not retained. |
| failure | Malformed request/resource failures follow builder's explicit stopped/error contract; no new allowance. |
| cost | Requested component census/aggregation plus output ownership, bounded in declared builder units. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/query_memory.md](../../../../query_memory.md), [src/runtime/owner_statistics_detail.hpp](../../../../../src/runtime/owner_statistics_detail.hpp) |

## B0249

[Lines 2130–2132](../../../../../src/runtime/support.cpp#L2130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
statistics::Freshness SupportRuntime::statistics_freshness(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare a captured stamp with current logical owner/epoch. |
| inputs / outputs | Capture stamp plus max_event_lag -&gt; Freshness. |
| invariants | Does not reuse an incompatible owner/layer or assert unchanged data from scalar IDs alone. |
| ownership | Copied freshness value; capture remains caller-owned. |
| failure | Moved runtime rejects; comparison handles mismatch explicitly. |
| cost | Fixed stamp/lag checks. |
| Design | [include/crown/runtime/statistics.hpp](../../../../../include/crown/runtime/statistics.hpp), [docs/query_memory.md](../../../../query_memory.md) |

## B0250

[Lines 2133–2135](../../../../../src/runtime/support.cpp#L2133); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
}

namespace crown::runtime::memory::detail {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Begin the private native memory-report adapter. |
| inputs / outputs | Runtime scope closure and memory::detail namespace. |
| invariants | Reporting bridge is separate from support recurrence. |
| ownership | No instance. |
| failure | Compile-time syntax only. |
| cost | Zero runtime work. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0251

[Lines 2136–2154](../../../../../src/runtime/support.cpp#L2136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Access::append(Builder& builder,const SupportRuntime& owner)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append actual support storage/operators to a native memory reconciliation report. |
| inputs / outputs | Builder plus owner enumerate compiled relations then per-node metadata/count/flag census. |
| invariants | Checks flag width and table/map cardinality agreement; inconsistent native state stops report instead of inventing counts. |
| ownership | Builder original account funds report; traversal borrows established runtime/state. |
| failure | Builder work/budget or Failure(inconsistent) propagates to outer attempt; no state repair. |
| cost | Explicit O(relations + nodes + record metadata) census and underlying table report costs; no answer enumeration. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0252

[Lines 2155–2163](../../../../../src/runtime/support.cpp#L2155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Attempt Access::capture(const SupportRuntime& owner,Limits limits) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a stopped-or-complete native memory report without leaking exceptions. |
| inputs / outputs | Limits -&gt; attempt-wrapped Usage/Builder result. |
| invariants | Empty owner becomes invalid_handle. Pending owner reports pending availability and skips committed logical census; actual account remains original. |
| ownership | Native funded report retains captured metadata; source runtime is borrowed only during call. |
| failure | Noexcept attempt boundary classifies declared stop/resource errors; this is an explicit reporting API, not a hot-path exception fallback. |
| cost | Explicit builder/report census and allocation proportional to captured owners/components, according to Limits. |
| Design | [docs/memory_reports.md](../../../../memory_reports.md), [src/runtime/memory_report_detail.hpp](../../../../../src/runtime/memory_report_detail.hpp) |

## B0253

[Lines 2164–2164](../../../../../src/runtime/support.cpp#L2164); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L2164-L2164:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::runtime::memory::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::runtime::memory::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::runtime::memory::detail\` at its lexical source position in src/runtime/support.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::runtime::memory::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/runtime_support.md](../../../../runtime_support.md), [docs/support_invariants.md](../../../../support_invariants.md), [docs/result_cursors.md](../../../../result_cursors.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
