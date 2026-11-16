# `src/ir/program.cpp` — block usage map

[Source](../../../../../src/ir/program.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Describe typed conjunctive queries, checked trees, physical relations and immutable executable programs.

Snapshot SHA-256: `e84bd3a533f0cc2b0ad77ee15a38a577f8b363aaf8201327f6f1031e663d0c9c`. 647 lines partitioned into 118 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/ir/program.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 20–24](../../../../../src/ir/program.cpp#L20) | Type/record definition: struct Allocation |  · [reviewed contract](#b0002) |
| [B0003 · 25–25](../../../../../src/ir/program.cpp#L25) | declares types or opens a type body. |  · [reviewed contract](#b0003) |
| [B0004 · 26–29](../../../../../src/ir/program.cpp#L26) | Type/record definition: struct JsonNode |  · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../src/ir/program.cpp#L30) | Type/record definition: struct JsonMember |  · [reviewed contract](#b0005) |
| [B0006 · 31–31](../../../../../src/ir/program.cpp#L31) | Type/record definition: template&lt;class T&gt; struct Type |  · [reviewed contract](#b0006) |
| [B0007 · 32–67](../../../../../src/ir/program.cpp#L32) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 68–75](../../../../../src/ir/program.cpp#L68) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0008) |
| [B0009 · 76–76](../../../../../src/ir/program.cpp#L76) | Type/record definition: template&lt;class T,class A&gt; struct Type&lt;std::vector&lt;T,A&gt;&gt; |  · [reviewed contract](#b0009) |
| [B0010 · 77–77](../../../../../src/ir/program.cpp#L77) | Type/record definition: template&lt;class T,class L,class A&gt; struct Type&lt;std::set&lt;T,L,A&gt;&gt; |  · [reviewed contract](#b0010) |
| [B0011 · 78–78](../../../../../src/ir/program.cpp#L78) | Type/record definition: template&lt;class T&gt; struct Type&lt;std::optional&lt;T&gt;&gt; |  · [reviewed contract](#b0011) |
| [B0012 · 79–79](../../../../../src/ir/program.cpp#L79) | Type/record definition: template&lt;class... T&gt; struct Type&lt;std::variant&lt;T...&gt;&gt; |  · [reviewed contract](#b0012) |
| [B0013 · 80–81](../../../../../src/ir/program.cpp#L80) | Imports dependencies; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0013) |
| [B0014 · 82–82](../../../../../src/ir/program.cpp#L82) | Callable definition: void require(bool value) | calls storage::IndexFailure; guard void require(bool value) {if(!value)throw storage::IndexFailure(storage::IndexFault::contract);} · [reviewed contract](#b0014) |
| [B0015 · 83–85](../../../../../src/ir/program.cpp#L83) | Callable definition: void step(storage::IndexWorkAllowance* work,std::uint64_t amount=1) | calls admit · [reviewed contract](#b0015) |
| [B0016 · 86–91](../../../../../src/ir/program.cpp#L86) | Callable definition: template&lt;class T&gt; void words(storage::IndexWorkAllowance* work,std::size_t count) | calls storage::IndexFailure, admit · [reviewed contract](#b0016) |
| [B0017 · 92–103](../../../../../src/ir/program.cpp#L92) | Callable definition: storage::AccountedLayout make_layout(const resource::MemoryAccount& account,resource::MemoryAttribution owner, LayoutId id,std::s… | calls size, storage::IndexFailure, admit, binding; returns storage::AccountedLayout::make(account,id,fields,{version,{binding.data(),binding.size()}},origin,o…; growth insert, reserve · [reviewed contract](#b0017) |
| [B0018 · 104–114](../../../../../src/ir/program.cpp#L104) | Callable definition: ScalarType sql_scalar(frontend::SqlKind kind) | calls storage::IndexFailure; returns ScalarType::int64; ScalarType::string · [reviewed contract](#b0018) |
| [B0019 · 115–148](../../../../../src/ir/program.cpp#L115) | declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::program::detail · [reviewed contract](#b0019) |
| [B0020 · 149–151](../../../../../src/ir/program.cpp#L149) | Callable definition: Data(storage::AccountedPlanStorage::Binding value,resource::MemoryAttribution owner) :account(value.account()),binding(std::move(… | calls account, binding, std::move, attribution · [reviewed contract](#b0020) |
| [B0021 · 152–154](../../../../../src/ir/program.cpp#L152) | Callable definition: Data(const resource::MemoryAccount& value,resource::MemoryAttribution owner,CompiledProgram source) :account(value),basis(std::mo… | calls account, basis, std::move, attribution · [reviewed contract](#b0021) |
| [B0022 · 155–161](../../../../../src/ir/program.cpp#L155) | Callable definition: ~Data() | calls rbegin, rend, destroy, data; 1 loop sites; source comment (unverified): // Destroy completed arena prefixes before member/block release. Flat · [reviewed contract](#b0022) |
| [B0023 · 162–170](../../../../../src/ir/program.cpp#L162) | declares namespace scope; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown · [reviewed contract](#b0023) |
| [B0024 · 171–171](../../../../../src/ir/program.cpp#L171) | Type/record definition: struct Memo |  · [reviewed contract](#b0024) |
| [B0025 · 172–172](../../../../../src/ir/program.cpp#L172) | Type/record definition: struct NativeMemo |  · [reviewed contract](#b0025) |
| [B0026 · 173–174](../../../../../src/ir/program.cpp#L173) | Member/declaration region. |  · [reviewed contract](#b0026) |
| [B0027 · 175–188](../../../../../src/ir/program.cpp#L175) | Callable definition: public: Builder(CompiledProgram::Data& data,const PhysicalPlan& source,storage::IndexWorkAllowance* work) :data_(data),source_(&s… | calls data_, source_, work_, projections_; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0027) |
| [B0028 · 189–192](../../../../../src/ir/program.cpp#L189) | Callable definition: Builder(CompiledProgram::Data& data,storage::IndexWorkAllowance* work) :data_(data),source_(nullptr),work_(work),projections_(res… | calls data_, source_, work_, projections_ · [reviewed contract](#b0028) |
| [B0029 · 193–202](../../../../../src/ir/program.cpp#L193) | Callable definition: Builder(CompiledProgram::Data& data,const CompiledProgram& source,storage::IndexWorkAllowance* work) :data_(data),source_(nullptr… | calls data_, source_, native_source_, work_; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0029) |
| [B0030 · 203–219](../../../../../src/ir/program.cpp#L203) | Callable definition: template&lt;class T&gt; std::pair&lt;T*,std::size_t&gt; allocate(std::size_t n) | calls static_assert, storage::IndexFailure, data, size; guard static_assert(std::is_nothrow_destructible_v&lt;T&gt;);; returns {pointer,index}; growth allocate, push_back, reserve · [reviewed contract](#b0030) |
| [B0031 · 220–222](../../../../../src/ir/program.cpp#L220) | Callable definition: template&lt;class T&gt; void constructed(std::size_t index,std::size_t count) | calls  · [reviewed contract](#b0031) |
| [B0032 · 223–228](../../../../../src/ir/program.cpp#L223) | Callable definition: template&lt;class T&gt; T* defaults(std::size_t n) | calls std::construct_at; returns nullptr; pointer; growth allocate; 1 loop sites · [reviewed contract](#b0032) |
| [B0033 · 229–235](../../../../../src/ir/program.cpp#L229) | Callable definition: std::string_view freeze(std::string_view value) | calls admit, size, empty, std::uninitialized_copy; returns {}; {pointer,value.size()}; growth allocate · [reviewed contract](#b0033) |
| [B0034 · 236–236](../../../../../src/ir/program.cpp#L236) | Callable definition: std::string_view freeze(const std::string& value) | calls std::string_view; returns freeze(std::string_view(value)) · [reviewed contract](#b0034) |
| [B0035 · 237–237](../../../../../src/ir/program.cpp#L237) | Callable definition: storage::InlineDecimal freeze(const Decimal& value) | calls storage::InlineDecimal::copy_of; returns storage::InlineDecimal::copy_of(value); growth copy_of · [reviewed contract](#b0035) |
| [B0036 · 238–242](../../../../../src/ir/program.cpp#L238) | Callable definition: storage::AccountedLayout freeze(const storage::TupleLayout& source) | calls step, id, require, layouts; guard require(id.value&lt;source_-&gt;layouts().size() && source.same_token(source_-&gt;layouts()\[id.value\]));; returns data_.binding.layout(id) · [reviewed contract](#b0036) |
| [B0037 · 243–250](../../../../../src/ir/program.cpp#L243) | Callable definition: storage::AccountedProjection freeze(const storage::Projection& source) | calls step, same_token, source, target; returns old.projection; result; growth push_back; 1 loop sites · [reviewed contract](#b0037) |
| [B0038 · 251–253](../../../../../src/ir/program.cpp#L251) | Explanatory comments or spacing. | source comment (unverified): // Native construction already owns every nested span/token through this · [reviewed contract](#b0038) |
| [B0039 · 254–258](../../../../../src/ir/program.cpp#L254) | Callable definition: storage::AccountedLayout freeze(const storage::AccountedLayout& value) | calls step, id, require, layouts; guard step(work_);const auto id=value.id();require(id.value&lt;native_source_-&gt;layouts().size() && value.sam…; returns value; data_.binding.layout(id); source comment (unverified): // Native construction already owns every nested span/token through this · [reviewed contract](#b0039) |
| [B0040 · 259–266](../../../../../src/ir/program.cpp#L259) | Callable definition: storage::AccountedProjection freeze(const storage::AccountedProjection& value) | calls step, same_token, fields, size; returns value; old.projection; growth push_back; 1 loop sites · [reviewed contract](#b0040) |
| [B0041 · 267–267](../../../../../src/ir/program.cpp#L267) | Callable definition: program::PhysicalRelation freeze(const program::PhysicalRelation& value) | calls aggregate; returns native_source_?aggregate(value):value · [reviewed contract](#b0041) |
| [B0042 · 268–268](../../../../../src/ir/program.cpp#L268) | Callable definition: program::PhysicalInput freeze(const program::PhysicalInput& value) | calls aggregate; returns native_source_?aggregate(value):value · [reviewed contract](#b0042) |
| [B0043 · 269–269](../../../../../src/ir/program.cpp#L269) | Callable definition: program::PhysicalNode freeze(const program::PhysicalNode& value) | calls aggregate; returns native_source_?aggregate(value):value · [reviewed contract](#b0043) |
| [B0044 · 270–270](../../../../../src/ir/program.cpp#L270) | Callable definition: program::PhysicalEdge freeze(const program::PhysicalEdge& value) | calls aggregate; returns native_source_?aggregate(value):value · [reviewed contract](#b0044) |
| [B0045 · 271–271](../../../../../src/ir/program.cpp#L271) | Callable definition: program::EnumerationStep freeze(const program::EnumerationStep& value) | calls aggregate; returns native_source_?aggregate(value):value · [reviewed contract](#b0045) |
| [B0046 · 272–277](../../../../../src/ir/program.cpp#L272) | Callable definition: template&lt;class T,class A&gt; Frozen&lt;std::vector&lt;T,A&gt;&gt; freeze(const std::vector&lt;T,A&gt;& source) | calls empty, size, std::construct_at; returns {}; {pointer,source.size()}; growth allocate; 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 278–283](../../../../../src/ir/program.cpp#L278) | Callable definition: template&lt;class T,class L,class A&gt; Frozen&lt;std::set&lt;T,L,A&gt;&gt; freeze(const std::set&lt;T,L,A&gt;& source) | calls empty, size, std::construct_at; returns {}; {pointer,source.size()}; growth allocate; 1 loop sites · [reviewed contract](#b0047) |
| [B0048 · 284–288](../../../../../src/ir/program.cpp#L284) | Callable definition: template&lt;class T&gt; Span&lt;Frozen&lt;T&gt;&gt; freeze(Span&lt;T&gt; source) | calls empty, size, std::construct_at; returns {}; {pointer,source.size()}; growth allocate; 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 289–289](../../../../../src/ir/program.cpp#L289) | Callable definition: template&lt;class T&gt; Set&lt;Frozen&lt;T&gt;&gt; freeze(Set&lt;T&gt; source) | calls data, size; returns {value.data(),value.size()} · [reviewed contract](#b0049) |
| [B0050 · 290–293](../../../../../src/ir/program.cpp#L290) | Callable definition: template&lt;class T&gt; Frozen&lt;std::optional&lt;T&gt;&gt; freeze(const std::optional&lt;T&gt;& source) | calls ; returns {}; Frozen&lt;std::optional&lt;T&gt;&gt;(std::in_place,freeze(*source)) · [reviewed contract](#b0050) |
| [B0051 · 294–299](../../../../../src/ir/program.cpp#L294) | Callable definition: template&lt;std::size_t I=0,class... T&gt; Frozen&lt;std::variant&lt;T...&gt;&gt; freeze_variant(const std::variant&lt;T...&gt;& source) | calls constexpr, index, freeze, storage::IndexFailure; returns Frozen&lt;std::variant&lt;T...&gt;&gt;(std::in_place_index&lt;I&gt;,freeze(std::get&lt;I&gt;(source))); freeze_variant&lt;I+1&gt;… · [reviewed contract](#b0051) |
| [B0052 · 300–300](../../../../../src/ir/program.cpp#L300) | Callable definition: template&lt;class... T&gt; Frozen&lt;std::variant&lt;T...&gt;&gt; freeze(const std::variant&lt;T...&gt;& source) | calls freeze_variant; returns freeze_variant(source) · [reviewed contract](#b0052) |
| [B0053 · 301–330](../../../../../src/ir/program.cpp#L301) | Callable definition: JsonView freeze(const io::Json& source) | calls pending, size, capacity, storage::IndexFailure; guard else require(input-&gt;is_null());; returns JsonView(root); growth push_back, reserve; 3 loop sites · [reviewed contract](#b0053) |
| [B0054 · 331–362](../../../../../src/ir/program.cpp#L331) | Callable definition: JsonView freeze(JsonView source) | calls pending, size, capacity, storage::IndexFailure; returns JsonView(root); growth push_back, reserve; 3 loop sites · [reviewed contract](#b0054) |
| [B0055 · 363–388](../../../../../src/ir/program.cpp#L363) | Callable definition: template&lt;class T&gt; Frozen&lt;T&gt; aggregate(const T& source) | calls constexpr, static_assert, step, freeze; guard static_assert(std::is_same_v&lt;T,R&gt; && std::is_trivially_copyable_v&lt;T&gt;,"a retained owning field needs…; returns source; R{freeze(f0)}; source comment (unverified): // A new trivial view still needs a reviewed backing owner; trivial copy · [reviewed contract](#b0055) |
| [B0056 · 389–389](../../../../../src/ir/program.cpp#L389) | Callable definition: template&lt;class T&gt; Frozen&lt;T&gt; freeze(const T& source) | calls aggregate; returns aggregate(source) · [reviewed contract](#b0056) |
| [B0057 · 390–392](../../../../../src/ir/program.cpp#L390) | Callable definition: void run() | calls run_source, require; guard if(native_source_)run_source(*native_source_);else {require(source_!=nullptr);run_source(*source_);} · [reviewed contract](#b0057) |
| [B0058 · 393–404](../../../../../src/ir/program.cpp#L393) | Callable definition: template&lt;class Source&gt; void run_source(const Source& source) | calls route, freeze, catalog, query · [reviewed contract](#b0058) |
| [B0059 · 405–437](../../../../../src/ir/program.cpp#L405) | Callable definition: void finish_native_auxiliary() | calls fields, size, reserve, push_back; guard require(catalog.tables.size()&lt;=SIZE_MAX-data_.layouts.size() && catalog.tables.size()&lt;=SIZE_MAX-dat…; returns relation.role==RelationRole::physical_base && relation.base==TableId{i}; growth allocate, push_back, reserve; 3 loop sites · [reviewed contract](#b0059) |
| [B0060 · 438–443](../../../../../src/ir/program.cpp#L438) | Imports dependencies; declares namespace scope. | source comment (unverified): // namespace crown::program::detail · [reviewed contract](#b0060) |
| [B0061 · 444–447](../../../../../src/ir/program.cpp#L444) | Callable definition: CompiledProgram CompiledProgram::standalone(const PhysicalPlan& source) | calls resource::MemoryAccount::create, compile; returns compile(account,source) · [reviewed contract](#b0061) |
| [B0062 · 448–456](../../../../../src/ir/program.cpp#L448) | Callable definition: CompiledProgram CompiledProgram::compile(const resource::MemoryAccount& account,const PhysicalPlan& source) | calls compiler_work, storage::AccountedPlanStorage::freeze_binding, storage::detail::try_new_storage_owner, storage::IndexFailure; returns CompiledProgram(std::move(result)); growth make_accounted_shared · [reviewed contract](#b0062) |
| [B0063 · 457–459](../../../../../src/ir/program.cpp#L457) | Callable definition: CompiledProgram CompiledProgram::freeze(const resource::MemoryAccount& account,const PhysicalPlan& source,storage::IndexWorkAllow… | calls freeze_impl; returns freeze_impl(account,source,work,storage::MetadataWork::execution) · [reviewed contract](#b0063) |
| [B0064 · 460–469](../../../../../src/ir/program.cpp#L460) | Callable definition: CompiledProgram CompiledProgram::freeze_impl(const resource::MemoryAccount& account,const PhysicalPlan& source, storage::IndexWor… | calls storage::AccountedPlanStorage::freeze_binding, storage::detail::try_new_storage_owner, storage::IndexFailure, std::move; returns CompiledProgram(std::move(result)); growth make_accounted_shared · [reviewed contract](#b0064) |
| [B0065 · 470–473](../../../../../src/ir/program.cpp#L470) | Callable definition: CompiledProgram CompiledProgram::freeze(const resource::MemoryAccount& account,const CompiledProgram& source,storage::IndexWorkAl… | calls freeze_program, data; returns freeze_program(account,source,work,source.data().prepared_inputs? · [reviewed contract](#b0065) |
| [B0066 · 474–478](../../../../../src/ir/program.cpp#L474) | Callable definition: CompiledProgram CompiledProgram::prepare_inputs(const resource::MemoryAccount& account,const CompiledProgram& source, const progr… | calls program::detail::require, normalized, has_value, freeze_program; guard program::detail::require(source.normalized().has_value());; returns freeze_program(account,source,work,limits) · [reviewed contract](#b0066) |
| [B0067 · 479–502](../../../../../src/ir/program.cpp#L479) | Callable definition: CompiledProgram CompiledProgram::freeze_program(const resource::MemoryAccount& account,const CompiledProgram& source, storage::In… | calls local, options, remaining, storage::AccountedPlanStorage::clone_binding; returns CompiledProgram(std::move(result)); growth make_accounted_shared; source comment (unverified): // Indexed admission still requires the caller's existing capped allowance. · [reviewed contract](#b0067) |
| [B0068 · 503–505](../../../../../src/ir/program.cpp#L503) | Callable definition: program::InputExecution CompiledProgram::input_execution() const | calls data; returns data().prepared_inputs?program::InputExecution::threaded_v1:program::InputExecution::interpreted_v1 · [reviewed contract](#b0068) |
| [B0069 · 506–508](../../../../../src/ir/program.cpp#L506) | Callable definition: std::string_view CompiledProgram::input_execution_key() const | calls data; returns data().prepared_inputs?@ :@ · [reviewed contract](#b0069) |
| [B0070 · 509–511](../../../../../src/ir/program.cpp#L509) | Callable definition: program::InputPreparationUsage CompiledProgram::input_preparation() const | calls data; returns d.prepared_inputs?d.prepared_inputs-&gt;usage:program::InputPreparationUsage{} · [reviewed contract](#b0070) |
| [B0071 · 512–514](../../../../../src/ir/program.cpp#L512) | Callable definition: std::optional&lt;program::InputPreparationLimits&gt; CompiledProgram::input_preparation_limits() const | calls data; returns d.prepared_inputs?std::optional{d.prepared_inputs-&gt;limits}:std::nullopt · [reviewed contract](#b0071) |
| [B0072 · 515–519](../../../../../src/ir/program.cpp#L515) | Callable definition: CompiledProgram CompiledProgram::replan(const CompiledProgram& basis,const planner::MinimumHeightCandidate& candidate, const prog… | calls program::ReplanFailure, program::detail::NativeLowering::run, account; returns program::detail::NativeLowering::run(basis.account(),basis,candidate,limits) · [reviewed contract](#b0072) |
| [B0073 · 520–523](../../../../../src/ir/program.cpp#L520) | Callable definition: CompiledProgram CompiledProgram::replan_into(const resource::MemoryAccount& account,const CompiledProgram& basis, const planner::… | calls program::detail::NativeLowering::run; returns program::detail::NativeLowering::run(account,basis,candidate,limits) · [reviewed contract](#b0073) |
| [B0074 · 524–527](../../../../../src/ir/program.cpp#L524) | Callable definition: const CompiledProgram::Data& CompiledProgram::data() const | calls storage::IndexFailure; returns *data_ · [reviewed contract](#b0074) |
| [B0075 · 528–528](../../../../../src/ir/program.cpp#L528) | Callable definition: const resource::MemoryAccount& CompiledProgram::account() const & | calls data; returns data().account · [reviewed contract](#b0075) |
| [B0076 · 529–529](../../../../../src/ir/program.cpp#L529) | Callable definition: PhysicalRoute CompiledProgram::route() const | calls data; returns data().route · [reviewed contract](#b0076) |
| [B0077 · 530–530](../../../../../src/ir/program.cpp#L530) | Callable definition: const program::Catalog& CompiledProgram::catalog() const & | calls data; returns data().catalog · [reviewed contract](#b0077) |
| [B0078 · 531–531](../../../../../src/ir/program.cpp#L531) | Callable definition: const program::Query& CompiledProgram::query() const & | calls data; returns data().query · [reviewed contract](#b0078) |
| [B0079 · 532–532](../../../../../src/ir/program.cpp#L532) | Callable definition: const program::FreeConnexTree& CompiledProgram::tree() const & | calls data; returns data().tree · [reviewed contract](#b0079) |
| [B0080 · 533–533](../../../../../src/ir/program.cpp#L533) | Callable definition: const std::optional&lt;program::NormalizedSql&gt;& CompiledProgram::normalized() const & | calls data; returns data().normalized · [reviewed contract](#b0080) |
| [B0081 · 534–534](../../../../../src/ir/program.cpp#L534) | Callable definition: const program::ValidationReport& CompiledProgram::validation() const & | calls data; returns data().validation · [reviewed contract](#b0081) |
| [B0082 · 535–535](../../../../../src/ir/program.cpp#L535) | Callable definition: const program::QueryIdentity& CompiledProgram::identity() const & | calls data; returns data().identity · [reviewed contract](#b0082) |
| [B0083 · 536–536](../../../../../src/ir/program.cpp#L536) | Callable definition: const program::PhysicalOptions& CompiledProgram::options() const & | calls data; returns data().options · [reviewed contract](#b0083) |
| [B0084 · 537–537](../../../../../src/ir/program.cpp#L537) | Callable definition: const program::GuaranteeProfile& CompiledProgram::guarantee() const & | calls data; returns data().guarantee · [reviewed contract](#b0084) |
| [B0085 · 538–538](../../../../../src/ir/program.cpp#L538) | Callable definition: const program::EnumerationProgram& CompiledProgram::enumeration() const & | calls data; returns data().enumeration · [reviewed contract](#b0085) |
| [B0086 · 539–539](../../../../../src/ir/program.cpp#L539) | Callable definition: const storage::AccountedLayout& CompiledProgram::result_layout() const & | calls data; returns data().result_layout · [reviewed contract](#b0086) |
| [B0087 · 540–540](../../../../../src/ir/program.cpp#L540) | Callable definition: const storage::AccountedLayout& CompiledProgram::sql_result_layout() const & | calls data; returns data().sql_result_layout · [reviewed contract](#b0087) |
| [B0088 · 541–541](../../../../../src/ir/program.cpp#L541) | Callable definition: const program::Span&lt;program::SourceTable&gt;& CompiledProgram::sources() const & | calls data; returns data().sources · [reviewed contract](#b0088) |
| [B0089 · 542–551](../../../../../src/ir/program.cpp#L542) | Callable definition: storage::AccountedLayout CompiledProgram::scope_layout(LayoutId id,std::span&lt;const VariableId&gt; variables, std::string_view suffix… | calls data, size, fields, account; guard program::detail::require(variable.value&lt;d.query.variables.size());fields.push_back({d.query.variabl…; returns program::detail::make_layout(account(),d.attribution,id,fields,d.catalog.version,d.physical_sha256,…; growth push_back, reserve; 1 loop sites · [reviewed contract](#b0089) |
| [B0090 · 552–552](../../../../../src/ir/program.cpp#L552) | Callable definition: const program::Catalog& CompiledProgram::source_catalog() const & | calls data; returns d.normalized?d.normalized-&gt;binding.catalog:d.catalog · [reviewed contract](#b0090) |
| [B0091 · 553–553](../../../../../src/ir/program.cpp#L553) | Callable definition: std::shared_ptr&lt;const program::Catalog&gt; CompiledProgram::source_catalog_owner() const | calls source_catalog; returns {data_,&source_catalog()} · [reviewed contract](#b0091) |
| [B0092 · 554–554](../../../../../src/ir/program.cpp#L554) | Callable definition: std::string_view CompiledProgram::physical_sha256() const & | calls data; returns data().physical_sha256 · [reviewed contract](#b0092) |
| [B0093 · 555–555](../../../../../src/ir/program.cpp#L555) | Callable definition: std::string_view CompiledProgram::physical_source_sha256() const & | calls data, size; returns {value.data(),value.size()} · [reviewed contract](#b0093) |
| [B0094 · 556–556](../../../../../src/ir/program.cpp#L556) | Callable definition: const program::Span&lt;storage::AccountedLayout&gt;& CompiledProgram::layouts() const & | calls data; returns data().layouts · [reviewed contract](#b0094) |
| [B0095 · 557–557](../../../../../src/ir/program.cpp#L557) | Callable definition: const program::Span&lt;program::PhysicalRelation&gt;& CompiledProgram::relations() const & | calls data; returns data().relations · [reviewed contract](#b0095) |
| [B0096 · 558–558](../../../../../src/ir/program.cpp#L558) | Callable definition: const program::Span&lt;program::IndexRequirement&gt;& CompiledProgram::indexes() const & | calls data; returns data().indexes · [reviewed contract](#b0096) |
| [B0097 · 559–559](../../../../../src/ir/program.cpp#L559) | Callable definition: const program::Span&lt;program::PhysicalInput&gt;& CompiledProgram::inputs() const & | calls data; returns data().inputs · [reviewed contract](#b0097) |
| [B0098 · 560–560](../../../../../src/ir/program.cpp#L560) | Callable definition: const program::Span&lt;program::PhysicalNode&gt;& CompiledProgram::nodes() const & | calls data; returns data().nodes · [reviewed contract](#b0098) |
| [B0099 · 561–561](../../../../../src/ir/program.cpp#L561) | Callable definition: const program::Span&lt;program::PhysicalEdge&gt;& CompiledProgram::edges() const & | calls data; returns data().edges · [reviewed contract](#b0099) |
| [B0100 · 562–562](../../../../../src/ir/program.cpp#L562) | Callable definition: const program::Span&lt;program::Span&lt;OccurrenceId&gt;&gt;& CompiledProgram::base_routes() const & | calls data; returns data().base_routes · [reviewed contract](#b0100) |
| [B0101 · 563–563](../../../../../src/ir/program.cpp#L563) | Callable definition: std::uint64_t CompiledProgram::work() const | calls data; returns data().work · [reviewed contract](#b0101) |
| [B0102 · 564–564](../../../../../src/ir/program.cpp#L564) | Callable definition: storage::AccountedPlanStorage CompiledProgram::make_storage(storage::IndexWorkAllowance* work) const | calls storage::AccountedPlanStorage, data; returns storage::AccountedPlanStorage(data().binding,work) · [reviewed contract](#b0102) |
| [B0103 · 565–571](../../../../../src/ir/program.cpp#L565) | Callable definition: CompiledProgram runtime::detail::SqlColdRebuild::freeze(const resource::MemoryAccount& account, const PhysicalPlan& source,storag… | calls CompiledProgram::freeze_impl, options; returns CompiledProgram::freeze_impl(account,source,work,; source comment (unverified): // The real lowering result remains the only input. Existing compiler binding · [reviewed contract](#b0103) |
| [B0104 · 572–576](../../../../../src/ir/program.cpp#L572) | Callable definition: storage::AccountedPlanStorage runtime::detail::SqlColdRebuild::storage(const CompiledProgram& source, storage::IndexWorkAllowance… | calls storage::AccountedPlanStorage, data; returns storage::AccountedPlanStorage(source.data().binding,work, · [reviewed contract](#b0104) |
| [B0105 · 577–582](../../../../../src/ir/program.cpp#L577) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0105) |
| [B0106 · 583–629](../../../../../src/ir/program.cpp#L583) | Callable definition: std::optional&lt;storage::AccountedTuple&gt; CompiledProgram::adapt_input(OccurrenceId occurrence, storage::RowView physical,storage::I… | calls data, at, validation_issue, ok; guard program::detail::require(column-&gt;occurrence==occurrence);values.at(id.value)=physical.at(column-&gt;co…; returns {}; {}; growth push_back, reserve; 9 loop sites · [reviewed contract](#b0106) |
| [B0107 · 630–632](../../../../../src/ir/program.cpp#L630) | declares namespace scope. | source comment (unverified): // namespace crown · [reviewed contract](#b0107) |
| [B0108 · 633–633](../../../../../src/ir/program.cpp#L633) | Callable definition: JsonKind JsonView::kind() const noexcept | calls index; returns node_?static_cast&lt;JsonKind&gt;(node_-&gt;value.index()):JsonKind::null · [reviewed contract](#b0108) |
| [B0109 · 634–638](../../../../../src/ir/program.cpp#L634) | Callable definition: std::size_t JsonView::size() const noexcept | calls is_array, size, is_object, is_null; returns std::get&lt;Span&lt;detail::JsonNode&gt;&gt;(node_-&gt;value).size(); std::get&lt;Span&lt;detail::JsonMember&gt;&gt;(node_-&gt;va… · [reviewed contract](#b0109) |
| [B0110 · 639–639](../../../../../src/ir/program.cpp#L639) | Callable definition: JsonView JsonView::at(std::size_t i) const | calls detail::require, is_array, JsonView, at; guard JsonView JsonView::at(std::size_t i) const {detail::require(is_array());return JsonView(&std::get&lt;S…; returns JsonView(&std::get&lt;Span&lt;detail::JsonNode&gt;&gt;(node_-&gt;value).at(i)) · [reviewed contract](#b0110) |
| [B0111 · 640–640](../../../../../src/ir/program.cpp#L640) | Callable definition: std::string_view JsonView::key(std::size_t i) const | calls detail::require, is_object, at; guard std::string_view JsonView::key(std::size_t i) const {detail::require(is_object());return std::get&lt;S…; returns std::get&lt;Span&lt;detail::JsonMember&gt;&gt;(node_-&gt;value).at(i).key · [reviewed contract](#b0111) |
| [B0112 · 641–641](../../../../../src/ir/program.cpp#L641) | Callable definition: JsonView JsonView::member(std::size_t i) const | calls detail::require, is_object, JsonView, at; guard JsonView JsonView::member(std::size_t i) const {detail::require(is_object());return JsonView(&std::…; returns JsonView(&std::get&lt;Span&lt;detail::JsonMember&gt;&gt;(node_-&gt;value).at(i).value) · [reviewed contract](#b0112) |
| [B0113 · 642–642](../../../../../src/ir/program.cpp#L642) | Callable definition: bool JsonView::boolean() const | calls detail::require, kind; guard bool JsonView::boolean() const {detail::require(kind()==JsonKind::boolean);return std::get&lt;bool&gt;(no…; returns std::get&lt;bool&gt;(node_-&gt;value) · [reviewed contract](#b0113) |
| [B0114 · 643–643](../../../../../src/ir/program.cpp#L643) | Callable definition: std::int64_t JsonView::integer() const | calls detail::require, kind; guard std::int64_t JsonView::integer() const {detail::require(kind()==JsonKind::integer);return std::get&lt;…; returns std::get&lt;std::int64_t&gt;(node_-&gt;value) · [reviewed contract](#b0114) |
| [B0115 · 644–644](../../../../../src/ir/program.cpp#L644) | Callable definition: std::uint64_t JsonView::unsigned_integer() const | calls detail::require, kind; guard std::uint64_t JsonView::unsigned_integer() const {detail::require(kind()==JsonKind::unsigned_intege…; returns std::get&lt;std::uint64_t&gt;(node_-&gt;value) · [reviewed contract](#b0115) |
| [B0116 · 645–645](../../../../../src/ir/program.cpp#L645) | Callable definition: double JsonView::number() const | calls detail::require, kind; guard double JsonView::number() const {detail::require(kind()==JsonKind::number);return std::get&lt;double&gt;(…; returns std::get&lt;double&gt;(node_-&gt;value) · [reviewed contract](#b0116) |
| [B0117 · 646–646](../../../../../src/ir/program.cpp#L646) | Callable definition: std::string_view JsonView::text() const | calls detail::require, kind; guard std::string_view JsonView::text() const {detail::require(kind()==JsonKind::string);return std::get&lt;…; returns std::get&lt;std::string_view&gt;(node_-&gt;value) · [reviewed contract](#b0117) |
| [B0118 · 647–647](../../../../../src/ir/program.cpp#L647) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::program · [reviewed contract](#b0118) |

## B0001

[Lines 1–19](../../../../../src/ir/program.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using Vector=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind native builder arrays and scratch vectors to a MemoryAccount allocator. |
| inputs / outputs | T selects vector element type; each construction supplies purpose and attribution. |
| invariants | Empty vectors still retain allocator identity; an alias alone does not supply an account or cap. |
| ownership | Vector owns allocated capacity and destroys elements through its funded allocator. |
| failure | Growth can throw memory/length failures; callers retain RAII cleanup. |
| cost | Normal vector capacity, relocation and element teardown costs apply; alias definition itself has no runtime work. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
@source-span:L1-L19:sha256:59b90f7460db7df6308f7be8351b16b77a992e4948ce3a6719b660ac763356c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wire the private prepared-input implementation into the existing immutable program compiler. |
| inputs / outputs | Existing public/model/storage/compiler includes plus private input_program.hpp. |
| invariants | The helper uses the unchanged shared SQL scalar evaluator; physical/source serialization stays identical. |
| ownership | Includes/namespace aliases create no runtime object. |
| failure | Only compiler/link diagnostics at this region. |
| cost | Compile-time inclusion; fixed workers share one executable image. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0002

[Lines 20–24](../../../../../src/ir/program.cpp#L20); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Allocation {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track an arena block and exactly the elements whose construction completed. |
| inputs / outputs | MemoryBlock, constructed prefix count and noexcept type-erased destroy callback. |
| invariants | Count starts at zero and advances after successful construct_at; callback destroys objects before block deallocation. |
| ownership | Record owns the raw block; Data owns records and final release. |
| failure | Noexcept element destruction is required at allocation instantiation; partial builds remain destructible. |
| cost | Record movement transfers block ownership; callback cost scales with constructed elements and nested descriptor releases. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0003

[Lines 25–25](../../../../../src/ir/program.cpp#L25); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L25:sha256:50265827dceeaf1c0a1789fc3bc595ec8f58c29e10e35285310736109e3d3c19
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Forward-declares internal JsonMember so JsonNode can refer to flat object-member spans before the member type is defined. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/code_specs/files/src/ir/program.cpp.md](program.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0004

[Lines 26–29](../../../../../src/ir/program.cpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct JsonNode {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store one flat immutable JSON value without recursive child ownership. |
| inputs / outputs | Variant ordering matches JsonKind: null/bool/signed/unsigned/double/text/array/object. |
| invariants | Child spans and text are arena borrows; variant order must stay synchronized with JsonView::kind(). |
| ownership | Data arena owns all admitted nodes, members and text; JsonNode does not retain a separate owner. |
| failure | Primitive node lifecycle does not validate referenced spans; Builder must establish their backing storage. |
| cost | Fixed variant storage; copying a node copies views rather than traversing JSON children. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0005

[Lines 30–30](../../../../../src/ir/program.cpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct JsonMember {std::string_view key;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an object key view alongside its flat child value. |
| inputs / outputs | Borrowed key bytes and an embedded JsonNode. |
| invariants | Object admission freezes keys and fills each child in place. |
| ownership | Backing Data arena owns key/child allocations; the member contains no recursive owner. |
| failure | Member default construction supports partial arena cleanup; invalid backing views remain a caller contract. |
| cost | Fixed view/variant object work; key byte copying occurs in freeze(string). |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0006

[Lines 31–31](../../../../../src/ir/program.cpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Type {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use identity representation only for explicitly safe unmapped leaf values. |
| inputs / outputs | Default Result=T and fields=0 select aggregate() leaf handling. |
| invariants | aggregate() requires same type and trivially copyable; this does not detect dangling pointers inside a newly introduced trivial view type. |
| ownership | No implicit deep ownership conversion is provided; owning/container/view types need reviewed overloads or mappings. |
| failure | Unsupported nontrivial unmapped leaves fail static_assert when instantiated. |
| cost | Compile-time selection; accepted leaves copy their value representation. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0007

[Lines 32–67](../../../../../src/ir/program.cpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<> struct Type<::crown::Column> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map column name, scalar kind, nullability, collation and decimal domain into the native program representation. |
| inputs / outputs | The ::crown::Column aggregate is decomposed in its declared 5-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns name bytes; scalar kind, nullability, collation and DecimalSpec remain inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Name-byte copy plus five fixed fields; no layout/projection descriptor is constructed. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::UniqueConstraint> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map constraint name, ordered columns and trust status into the native program representation. |
| inputs / outputs | The ::crown::UniqueConstraint aggregate is decomposed in its declared 3-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns constraint-name bytes and ordered source-column array; trust tag is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Name bytes and column count determine arena payload; preserving order performs no uniqueness proof or destination tree insertion. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::ForeignKeyConstraint> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map foreign-key name, source columns, referenced table/columns and trust status into the native program representation. |
| inputs / outputs | The ::crown::ForeignKeyConstraint aggregate is decomposed in its declared 5-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns name bytes plus separate source/referenced column arrays; table ID and trust tag are inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies both column sequences and name bytes; does not probe referenced catalog rows or verify referential integrity. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::DistinctEstimate> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map ordered distinct-count column key and its estimate into the native program representation. |
| inputs / outputs | The ::crown::DistinctEstimate aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns ordered estimate-key column array; estimate value is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. One fixed aggregate checkpoint plus column-array admission; numeric estimate is copied without statistics collection. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::TableStatistics> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map optional row count and distinct-count inventory into the native program representation. |
| inputs / outputs | The ::crown::TableStatistics aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns distinct-estimate array and each nested column key; optional row count is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Cost follows number of distinct estimates and total key columns; no relation/census scan occurs. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::KeyHint> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map hint columns and explanatory reason into the native program representation. |
| inputs / outputs | The ::crown::KeyHint aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns column-ID array and reason bytes. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies selected column IDs and explanatory bytes; it does not prove a key or build an index. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::Table> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map table name, columns, source version, constraints, statistics and key hints into the native program representation. |
| inputs / outputs | The ::crown::Table aggregate is decomposed in its declared 6-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns table/name/column/constraint/hint bytes and arrays plus nested statistics payload. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Scans all six nested field families, including both foreign-key column lists, distinct-count keys and hint reasons; size includes all admitted arrays/text and arena-record overhead. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::Catalog> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map catalog version and ordered table inventory into the native program representation. |
| inputs / outputs | The ::crown::Catalog aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns ordered table array and every nested table payload; version remains inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Visits every table and nested schema/statistics/constraint/hint field and byte; no query/database semantic validation is rerun. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::Variable> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map variable name and scalar kind into the native program representation. |
| inputs / outputs | The ::crown::Variable aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns variable-name bytes; ScalarType is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Name-byte admission plus two fixed fields; does not allocate a layout or check variable incidence. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::Atom> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map occurrence spelling, table identity and ordered term variant sequence into the native program representation. |
| inputs / outputs | The ::crown::Atom aggregate is decomposed in its declared 3-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns occurrence-name bytes, ordered term array and any string scalar constants. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Visits terms and scalar alternatives, copying variable-width constant/name bytes; preserves repeated variables, constants and ignored positions without normalization. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::Output> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map head variable and output alias into the native program representation. |
| inputs / outputs | The ::crown::Output aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns output alias bytes; VariableId is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Alias-byte copy plus fixed variable identity; no head deduplication or value projection occurs. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::Query> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map variables, occurrences, ordered head and contradiction bit into the native program representation. |
| inputs / outputs | The ::crown::Query aggregate is decomposed in its declared 4-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns variable/atom/ordered-head arrays and their nested text/constants; contradiction is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Scans every declared variable, occurrence/term and repeated/ordered head plus text; contradiction does not elide this original-model admission. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::TreeNode> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map display ID, kind, scope, children, occurrence and optional separator claim into the native program representation. |
| inputs / outputs | The ::crown::TreeNode aggregate is decomposed in its declared 6-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns display-ID bytes, scope/child arrays and optional claimed-separator array; kind/occurrence are inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate tree or diagnostic proof claims. |
| cost | Trait selection is compile-time. Copies listed scope, ordered children, separator claim and ID bytes; it does not traverse children recursively or establish topology. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::FreeConnexTree> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map root, nodes, optional connex claim and optional native-height claim into the native program representation. |
| inputs / outputs | The ::crown::FreeConnexTree aggregate is decomposed in its declared 4-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns node array with each nested node payload and optional claimed-connex array; root/height claim are inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate tree or diagnostic proof claims. |
| cost | Trait selection is compile-time. Cost follows complete flat node/scope/child/claim inventory and ID bytes; empty tree keeps null/present-empty optional distinctions without node payload. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::planner::PlanViolation> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map rule/message and optional node, variable, occurrence and related-node coordinates into the native program representation. |
| inputs / outputs | The ::crown::planner::PlanViolation aggregate is decomposed in its declared 6-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns rule/message bytes; optional diagnostic coordinates are inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate tree or diagnostic proof claims. |
| cost | Trait selection is compile-time. Copies diagnostic text and coordinates; does not format a new error or validate the reported violation. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::planner::ValidationReport> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map validity, native height, edge depth, maximal connex, separators and violations into the native program representation. |
| inputs / outputs | The ::crown::planner::ValidationReport aggregate is decomposed in its declared 6-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns maximal-connex, separator-set and violation arrays, with nested diagnostic text. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate tree or diagnostic proof claims. |
| cost | Trait selection is compile-time. Visits stored separator widths/diagnostics and text; this is report admission, not P02 or certificate replay. Fresh constant-operator report has no array/text payload. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::BoundLiteral> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map nullable SQL literal value into the native program representation. |
| inputs / outputs | The ::crown::frontend::BoundLiteral aggregate is decomposed in its declared 1-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns engaged scalar string bytes, or inline scalar/decimal data; SQL null stays disengaged. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Absent literal uses fixed optional handling; present scalar dispatch copies strings by byte width and Decimal coefficients within 38 digits. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::BoundOperation> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map SQL opcode and ordered expression arguments into the native program representation. |
| inputs / outputs | The ::crown::frontend::BoundOperation aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns ordered expression-argument ID array; opcode is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies argument IDs and operation code; executes no SQL opcode or dependency traversal. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::BoundExpression> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map SQL type, tagged expression node and optional location into the native program representation. |
| inputs / outputs | The ::crown::frontend::BoundExpression aggregate is decomposed in its declared 3-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns active literal/operation payload; type and optional source location remain inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Fixed tagged-node dispatch plus active scalar/argument payload; does not evaluate or rebind the expression. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::BoundOccurrence> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map table, alias, resolved column names, location and descendants policy into the native program representation. |
| inputs / outputs | The ::crown::frontend::BoundOccurrence aggregate is decomposed in its declared 5-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns alias bytes and column-name view array plus each name’s bytes. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Visits resolved column names/alias text; table/location/descendant flag are copied without catalog resolution. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::BoundOutput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map output name and expression identity into the native program representation. |
| inputs / outputs | The ::crown::frontend::BoundOutput aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns output-name bytes; expression ID is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies the name and expression ID; computes no expression result. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::BoundSql> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map source SQL, catalog, parameter types, outer/inner semantics, wrapper/alias, occurrences, expressions, predicates, outputs, limits and work into the native program representation. |
| inputs / outputs | The ::crown::frontend::BoundSql aggregate is decomposed in its declared 13-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns SQL source/wrapper alias, catalog and all occurrence/expression/output names/arrays/literals; limits/work remain values. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Visits all 13 field families including catalog, parameter types, expression arguments/literals and source text; no parse, bind or recursion-limited producer is rerun. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::ColumnConstant> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map physical column identity and exact guard value into the native program representation. |
| inputs / outputs | The ::crown::frontend::ColumnConstant aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns string guard bytes or inline exact scalar value; column ID is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies one typed guard including its variable-width text; performs no row comparison. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::OccurrenceAdapter> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map occurrence/base, predicate/non-null/equality/class/projection/program arrays and constant guards into the native program representation. |
| inputs / outputs | The ::crown::frontend::OccurrenceAdapter aggregate is decomposed in its declared 9-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns predicate/non-null/equality/class/projection/program/constant-guard arrays and nested string guards. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Visits all nine fields and all instruction/guard entries; no physical row is adapted during metadata admission. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::ConstantOutput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map one normalized literal output into the native program representation. |
| inputs / outputs | The ::crown::frontend::ConstantOutput aggregate is decomposed in its declared 1-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns string output bytes or inline exact scalar/decimal value. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies one exact output constant; does not map a core result row or format decimal text. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::NormalizedOutput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map output name, SQL type and core-or-constant output variant into the native program representation. |
| inputs / outputs | The ::crown::frontend::NormalizedOutput aggregate is decomposed in its declared 3-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns output-name bytes and active constant payload; SQL type/core-output coordinate are inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Name-byte and tagged constant/core-field handling; repeated/constant output mapping is preserved without result evaluation. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::frontend::NormalizedSql> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map binding, parameters, constants, core catalog/query, adapters, routes, outputs, limits, work and schema version into the native program representation. |
| inputs / outputs | The ::crown::frontend::NormalizedSql aggregate is decomposed in its declared 11-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns binding, parameter/constant scalars, core catalog/query, adapters/routes and output payload. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Visits all 11 field families, including repeated nested core/catalog copies and SQL source bytes; limits/work are copied rather than producer work being rerun. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::io::CachePolicy> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map arithmetic, planner, optimization and cost-model labels into the native program representation. |
| inputs / outputs | The ::crown::io::CachePolicy aggregate is decomposed in its declared 4-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns arithmetic/planner/optimization/cost-model label bytes. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies exactly four labels; policy spelling is retained without proving compatibility, optimality or a cost model. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::PhysicalOptions> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map cache policy, physical limits and optional indexed-backend specification into the native program representation. |
| inputs / outputs | The ::crown::PhysicalOptions aggregate is decomposed in its declared 3-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns four policy label byte strings; physical limits and optional indexed spec remain inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Policy bytes plus fixed finite option fields; no execution allowance or mutable backend is created. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::GuaranteeProfile> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map semantics/query/update/arithmetic/backend/execution/height/state/maintenance/cursor labels and mode/assumption/output inventories into the native program representation. |
| inputs / outputs | The ::crown::GuaranteeProfile aggregate is decomposed in its declared 15-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns 12 profile-label strings and operation-mode/assumption/output string arrays. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Scans all 15 fields and nested label bytes; copied status labels establish no measured bound or independent proof. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::io::QueryIdentity> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map canonical JSON, semantic/output/cost/cache digests, occurrence/variable order and producer work into the native program representation. |
| inputs / outputs | The ::crown::io::QueryIdentity aggregate is decomposed in its declared 8-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns flat canonical JSON, four digest strings and occurrence/variable permutation arrays; producer work is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Visits all canonical JSON nodes/member names/string bytes, digests and ID orders using funded iterative pending scratch; identity generation/hash/replay is not performed by this mapping. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::PhysicalRelation> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map relation ID/role, canonical layout and optional node/base into the native program representation. |
| inputs / outputs | The ::crown::PhysicalRelation aggregate is decomposed in its declared 5-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Returned value owns a remapped AccountedLayout handle and numeric coordinates; it contains no borrowed nested span. A reference to its containing Data array still needs that array owner. |
| failure | The mapping itself is compile-time. Instantiated field admission can reject source descriptor IDs/tokens or projection domains and can fail on grant, memory or overflow; no live storage operation is committed. |
| cost | Trait selection is compile-time. Fixed aggregate/ID work plus canonical source-layout membership/remap; layout metadata was deep-admitted by storage binding, not cloned per relation. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::IndexRequirement> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map index requirement ID, source relation, projection and declared uses into the native program representation. |
| inputs / outputs | The ::crown::IndexRequirement aggregate is decomposed in its declared 4-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Result owns the remapped projection control (including endpoint descriptors); uses remains a destination-arena span that needs Data. Copying the projection alone does not retain the use array. |
| failure | The mapping itself is compile-time. Instantiated field admission can reject source descriptor IDs/tokens or projection domains and can fail on grant, memory or overflow; no live storage operation is committed. |
| cost | Trait selection is compile-time. Projection-token memo scan and possible selected-field descriptor freeze plus use-array copy; no mutable index registration. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::InputConstant> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map logical source field and exact core constant guard into the native program representation. |
| inputs / outputs | The ::crown::InputConstant aggregate is decomposed in its declared 2-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Destination Data owns string guard bytes or inline scalar/decimal value; FieldId is inline. Any returned native text/span views require that Data owner; scalar fields are values. |
| failure | The mapping itself is compile-time. Aggregate/array/text admission can fail on work, memory or size overflow; it does not independently validate the retained semantic values. |
| cost | Trait selection is compile-time. Copies one logical constant guard; performs no input comparison or tuple allocation. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::PhysicalInput> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map occurrence/node/base/logical-table, physical layout, projection, equality and constant guards into the native program representation. |
| inputs / outputs | The ::crown::PhysicalInput aggregate is decomposed in its declared 8-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Layout/projection handles retain their remapped controls; equality/constant spans and any constant string views borrow destination Data. Copying the instruction does not acquire the guard-array owner. |
| failure | The mapping itself is compile-time. Instantiated field admission can reject source descriptor IDs/tokens or projection domains and can fail on grant, memory or overflow; no live storage operation is committed. |
| cost | Trait selection is compile-time. Descriptor-token lookup/memo scans, selected-field freeze when needed and complete guard payload; does not run the row adapter. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::PhysicalNode> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map node ID/kind/occurrence/parent, children/scopes/connex flag, layout/projections and four relation roles into the native program representation. |
| inputs / outputs | The ::crown::PhysicalNode aggregate is decomposed in its declared 15-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Layout and parent/visible projection handles retain their controls; child/scope/visible-scope spans borrow destination Data. Copying a node is not an owning copy of those arrays. |
| failure | The mapping itself is compile-time. Instantiated field admission can reject source descriptor IDs/tokens or projection domains and can fail on grant, memory or overflow; no live storage operation is committed. |
| cost | Trait selection is compile-time. Flat topology/scope copies and descriptor remapping/memo work across 15 fields; no recursive child walk or live operator state. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0008

[Lines 68–75](../../../../../src/ir/program.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<> struct Type<::crown::PhysicalEdge> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map parent/child/child slot, parent projection and optional reverse requirement into the native program representation. |
| inputs / outputs | The ::crown::PhysicalEdge aggregate is decomposed in its declared 5-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Result owns its remapped parent-key projection control; parent/child/slot/reverse-index coordinates are values. It contains no borrowed child array. |
| failure | The mapping itself is compile-time. Instantiated field admission can reject source descriptor IDs/tokens or projection domains and can fail on grant, memory or overflow; no live storage operation is committed. |
| cost | Trait selection is compile-time. Projection memo lookup or selected-field freeze plus fixed edge coordinates; child slot preserves arbitrary fanout. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::EnumerationStep> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map node/relation, depth, parent step, optional parent key and bucket requirement into the native program representation. |
| inputs / outputs | The ::crown::EnumerationStep aggregate is decomposed in its declared 6-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | An engaged parent-key handle retains its remapped projection and endpoint controls; remaining coordinates are inline. There is no nested assignment span in one step. |
| failure | The mapping itself is compile-time. Instantiated field admission can reject source descriptor IDs/tokens or projection domains and can fail on grant, memory or overflow; no live storage operation is committed. |
| cost | Trait selection is compile-time. Optional projection memo/freeze work plus fixed node/relation/depth/bucket fields; no cursor frame or index bucket is opened. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<::crown::EnumerationProgram> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map steps, ordered assignment output, equality checks and depth into the native program representation. |
| inputs / outputs | The ::crown::EnumerationProgram aggregate is decomposed in its declared 4-field order to the matching program type. |
| invariants | Field count and order must agree with both DTO and native definitions; this conversion preserves existing values rather than validating their semantics. |
| ownership | Step/output/equality arrays borrow destination Data; individual embedded projection handles can be copied to retain their own controls. Copying this header does not retain those arrays. |
| failure | The mapping itself is compile-time. Instantiated field admission can reject source descriptor IDs/tokens or projection domains and can fail on grant, memory or overflow; no live storage operation is committed. |
| cost | Trait selection is compile-time. Visits all step/assignment/equality entries and projection memo operations; recorded depth is copied without recursive cursor startup. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<std::string> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace an owning DTO string with destination-arena text. |
| inputs / outputs | std::string maps to std::string_view. |
| invariants | String bytes are copied by freeze(string_view); the result borrows Data. |
| ownership | Representation ownership is established by the corresponding Builder freeze overload. |
| failure | Compile-time trait itself cannot throw; actual conversion propagates its type-specific work/memory/domain faults. |
| cost | Trait selection is compile-time. Linear in string bytes plus one arena block/record. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<Decimal> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep exact bounded decimal coefficients inline in native scalar variants. |
| inputs / outputs | Decimal maps to storage::InlineDecimal. |
| invariants | InlineDecimal::copy_of copies the already valid bounded Decimal coefficient/scale/sign without parsing or revalidation; no DTO coefficient owner survives. |
| ownership | Representation ownership is established by the corresponding Builder freeze overload. |
| failure | Trait selection is compile-time; the selected Decimal copy_of conversion is noexcept and adds no allowance debit. |
| cost | Compile-time representation selection; conversion copies at most 38 existing coefficient digits and inline scale/sign. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<storage::TupleLayout> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a compiler layout with its admitted canonical descriptor. |
| inputs / outputs | storage::TupleLayout maps to storage::AccountedLayout. |
| invariants | TupleLayout overload checks the source token against source layouts and returns binding.layout(id). |
| ownership | Representation ownership is established by the corresponding Builder freeze overload. |
| failure | Compile-time trait itself cannot throw; actual conversion propagates its type-specific work/memory/domain faults. |
| cost | Trait selection is compile-time. Token/ID lookup here; descriptor deep-admission cost was paid by freeze_binding. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<storage::Projection> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace a compiler projection with an accounted canonical projection. |
| inputs / outputs | storage::Projection maps to storage::AccountedProjection. |
| invariants | Projection overload reuses token aliases or freezes fields against remapped endpoints. |
| ownership | Representation ownership is established by the corresponding Builder freeze overload. |
| failure | Compile-time trait itself cannot throw; actual conversion propagates its type-specific work/memory/domain faults. |
| cost | Trait selection is compile-time. Linear memo-token search plus selected-field admission on a miss. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<> struct Type<io::Json> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replace recursive compiler JSON with flat native JSON views. |
| inputs / outputs | io::Json maps to JsonView. |
| invariants | The iterative JSON packer allocates destination node/member/text arrays; returned JsonView borrows Data. |
| ownership | Representation ownership is established by the corresponding Builder freeze overload. |
| failure | Compile-time trait itself cannot throw; actual conversion propagates its type-specific work/memory/domain faults. |
| cost | Trait selection is compile-time. All JSON nodes/member keys/string bytes and funded pending-list growth. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0009

[Lines 76–76](../../../../../src/ir/program.cpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T,class A> struct Type<std::vector<T,A>>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a DTO vector to a native contiguous immutable span. |
| inputs / outputs | Maps template arguments through Type&lt;T&gt;::Result. |
| invariants | Element Result applies recursively; size/order are preserved. |
| ownership | Destination arena owns element storage; caller vector and allocator are borrowed only during freeze. |
| failure | Trait definition is compile-time; corresponding recursive freeze can fail on work/memory/contract conditions. |
| cost | Allocated element count and recursive element payload determine construction and teardown cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0010

[Lines 77–77](../../../../../src/ir/program.cpp#L77); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T,class L,class A> struct Type<std::set<T,L,A>>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map an ordered DTO set to a native ordered contiguous Set view. |
| inputs / outputs | Maps template arguments through Type&lt;T&gt;::Result. |
| invariants | Iteration order is preserved; Set membership assumes its ordering matches the native comparison. |
| ownership | Arena owns the frozen sequence; no source tree nodes or comparator are retained. |
| failure | Trait definition is compile-time; corresponding recursive freeze can fail on work/memory/contract conditions. |
| cost | One element pass and recursive payload admission; no destination ordered-tree node allocation. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0011

[Lines 78–78](../../../../../src/ir/program.cpp#L78); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> struct Type<std::optional<T>>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map nullable retained metadata while preserving engagement. |
| inputs / outputs | Maps template arguments through Type&lt;T&gt;::Result. |
| invariants | Absent stays absent; engaged value uses recursive native mapping. |
| ownership | Engaged native payload belongs to the destination or an accounted descriptor control. |
| failure | Trait definition is compile-time; corresponding recursive freeze can fail on work/memory/contract conditions. |
| cost | Absent branch is fixed work; engaged branch has nested conversion cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0012

[Lines 79–79](../../../../../src/ir/program.cpp#L79); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class... T> struct Type<std::variant<T...>>
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve tagged alternatives while replacing each owning representation. |
| inputs / outputs | Maps template arguments through Type&lt;T&gt;::Result. |
| invariants | Alternative order/index is unchanged; valueless input has no valid mapped alternative. |
| ownership | Only the active alternative is admitted; its resulting views borrow destination Data. |
| failure | Trait definition is compile-time; corresponding recursive freeze can fail on work/memory/contract conditions. |
| cost | Dispatch scans up to the compile-time alternative count plus active-payload conversion. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0013

[Lines 80–81](../../../../../src/ir/program.cpp#L80); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using Frozen=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the reviewed native result type used by every Builder conversion. |
| inputs / outputs | Frozen&lt;T&gt; is Type&lt;T&gt;::Result, including native mappings pulled from program_native_types.inc. |
| invariants | The included self-mappings preserve field-wise admission of native source views rather than blindly retaining them. |
| ownership | Alias provides no owner; overloads and destination Data determine lifetime. |
| failure | Missing or inconsistent mapping is a compile-time/instantiation problem. |
| cost | Compile-time alias; conversion runtime is described by the selected overload. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0014

[Lines 82–82](../../../../../src/ir/program.cpp#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool value) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject violated native metadata assumptions with a storage contract fault. |
| inputs / outputs | True returns; false throws IndexFailure(contract). |
| invariants | Does not translate memory/work faults or return a partial success. |
| ownership | No source or program ownership. |
| failure | False throws a fixed storage failure. |
| cost | One boolean branch plus exception-runtime work on failure. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0015

[Lines 83–85](../../../../../src/ir/program.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void step(storage::IndexWorkAllowance* work,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit explicit structural units from the caller metadata/adaptation grant. |
| inputs / outputs | Optional work pointer and amount, default one. |
| invariants | Null pointer disables this logical debit; grants are shared and not rolled back by this helper. |
| ownership | Borrows allowance synchronously. |
| failure | Allowance exhaustion propagates IndexFailure. |
| cost | Fixed allowance admission; amount is a counter, not a traversal bound. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0016

[Lines 86–91](../../../../../src/ir/program.cpp#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void words(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit controlled storage in pointer-sized units before allocation/growth. |
| inputs / outputs | Optional allowance and element count; ceil(sizeof(T)/sizeof(void*)) words per element. |
| invariants | Checks product overflow before admit; null allowance returns before arithmetic checks. |
| ownership | No buffer ownership or reservation; caller performs actual allocation. |
| failure | Overflow or allowance admission failure propagates. |
| cost | Fixed arithmetic/admission; actual element construction, allocator and relocation costs occur separately. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0017

[Lines 92–103](../../../../../src/ir/program.cpp#L92); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedLayout make_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze a funded layout with an owned identity-plus-suffix binding. |
| inputs / outputs | Account/attribution, layout ID, field span, catalog version, identity, suffix, optional origin and allowance; returns AccountedLayout. |
| invariants | Checks concatenation overflow and charges field/byte/pointer units before scratch assembly; AccountedLayout makes its own retained descriptor metadata. |
| ownership | Scratch binding vector and returned descriptor use supplied account; input spans/text need survive only the call. |
| failure | Overflow, work/memory denial and descriptor domain/contract faults propagate with RAII cleanup. |
| cost | Copies identity+suffix bytes and field metadata, with descriptor validation/derived metadata costs and funded allocations. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0018

[Lines 104–114](../../../../../src/ir/program.cpp#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ScalarType sql_scalar(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the physical scalar kind for a normalized SQL result field. |
| inputs / outputs | int32/int64 both yield int64; string/bool/date/decimal preserve kind. |
| invariants | This does not cast a value or erase the separately supplied DecimalSpec. |
| ownership | Pure enum mapping. |
| failure | unknown or unsupported kind throws IndexFailure(contract). |
| cost | Fixed switch dispatch. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0019

[Lines 115–148](../../../../../src/ir/program.cpp#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CompiledProgram::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the flat native arena, immutable binding and canonical source backing executable views. |
| inputs / outputs | Accounted control contains model/SQL/identity views, physical arrays, digests, layouts, source tables and producer work. |
| invariants | Published Data is const. Imported programs own admitted views; replans retain one canonical admitted source, not previous candidate graphs. Nonempty contradiction stores empty operator tree and a zero-height/depth valid report while retaining the original core Query; original candidate/proof is never rewritten. |
| ownership | Arena records own blocks, binding owns funded layout/projection controls, auxiliary layouts own their descriptors, and basis retains any aliased source views. Account can differ from the supplied canonical source account. |
| failure | Unpublished partial state must remain destructible; checked public access is unavailable until a factory returns. |
| cost | Control header is fixed size; retained cost includes all arena capacity, binding/descriptor controls and shared canonical source. Last release can destroy the full graph and source. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
resource::MemoryAccount account;
  // Replanned programs
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep receiver accounting separate from source retention and shared binding ownership. |
| inputs / outputs | Account, canonical basis, binding, attribution, allocation ledger and borrowed layout span precede immutable metadata fields. |
| invariants | layouts points into binding metadata for admission or the destination arena for native lowering; all other spans must point to arena or retained basis storage. |
| ownership | Field destruction follows the explicit arena-object destruction pass; allocation blocks and binding/source controls remain members until normal member teardown. |
| failure | Member construction or later filling can fail while Data remains private. |
| cost | Account and shared-handle field operations can release prior controls; metadata views themselves do not clone their payload. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
@source-span:L115-L148:sha256:25af9f1e6bc4676fffa337440074e0c31d9a56e3558dd216dcd4c1600c075a90
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain an optional prepared owner alongside existing immutable executable metadata. |
| inputs / outputs | Data retains its original account/binding/basis/arena/graph and a nullable shared_ptr&lt;const PreparedInputs&gt;. |
| invariants | Interpreted programs retain no instruction/range vectors. Replanned Data retains canonical source ownership; prepared argument spans borrow the resulting Data normalized payload. |
| ownership | Data owns the prepared owner and every arena block or retained basis needed by borrowed views. Prepared destruction does not dereference released argument spans. |
| failure | Member allocation/construction faults unwind unpublished Data through existing RAII; the field adds no new exception framework. |
| cost | One shared_ptr-sized default overhead plus opted-in accounted owner/tables; Data destruction remains proportional to owned metadata. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0020

[Lines 149–151](../../../../../src/ir/program.cpp#L149); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(storage::AccountedPlanStorage::Binding value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start an admitted program around an already funded canonical storage binding. |
| inputs / outputs | Consumes Binding plus attribution; account comes from binding, layouts borrows binding.layouts(). |
| invariants | A valid binding is required before account()/layouts() access; remaining metadata is initially empty. |
| ownership | Moves binding into Data and configures immutable arena-ledger allocator under its account. |
| failure | Invalid binding access or allocator/account validation can fail during construction; argument/member RAII releases unpublished state. |
| cost | Shared binding transfer and allocator/header initialization; no payload walk or new descriptor clone here. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0021

[Lines 152–154](../../../../../src/ir/program.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Data(const resource::MemoryAccount& value,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start a receiver-funded candidate graph while retaining its canonical source. |
| inputs / outputs | Account, attribution and source CompiledProgram; initializes empty native graph and arena ledger. |
| invariants | NativeLowering::run chooses the canonical source before this constructor, so replacing replans does not build a candidate chain. |
| ownership | Stores receiver account and moves the source handle into basis; source payload stays in its original funded controls. |
| failure | Account/allocator validation can fail before publication; no source payload mutation. |
| cost | Fixed handle/header setup; eventual last-source release can traverse that graph. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0022

[Lines 155–161](../../../../../src/ir/program.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
~Data() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy completed arena objects in reverse allocation order before releasing raw blocks. |
| inputs / outputs | For every ledger entry invokes its destroy callback on the recorded constructed prefix. |
| invariants | Partially built arrays destroy only completed elements; flat JSON/SQL spans do not recursively own child nodes. Every recorded allocation has a valid callback. |
| ownership | After the body, member RAII frees blocks/ledger capacity, descriptors/binding and any last canonical basis owner. |
| failure | Destruction is nonthrowing and requires nothrow element destructors; no error translation or rebuild work occurs. |
| cost | Visits every allocation record and constructed element; descriptor/member release and final canonical-source release add their actual teardown costs. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0023

[Lines 162–170](../../../../../src/ir/program.cpp#L162); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Builder {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pack compiler or native metadata into one unpublished flat Data arena. |
| inputs / outputs | Three modes: borrow DTO source, borrow native source for deep admission, or arena-only native instruction construction. |
| invariants | DTO/native admission remaps canonical tokens; arena-only mode copies already owned native instruction handles/views. Work allowance is shared, not refilled or rolled back. |
| ownership | Borrows destination/source/allowance; funded projection memo vectors are construction scratch. Published program never retains these source pointers. |
| failure | All construction failures unwind private arena objects via Data and scratch RAII; this synchronous packer offers no continuation/cancellation API. |
| cost | Copies retained bytes/arrays, scans projection memo prefixes and allocates arena blocks/ledger growth; nested field freeze depth follows the fixed type structure while JSON traversal is iterative. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
CompiledProgram::Data& data_;
  const PhysicalPlan* source_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track packing mode and borrow the source only while native storage is constructed. |
| inputs / outputs | Destination reference, nullable DTO/native source pointers and nullable work pointer. |
| invariants | Exactly the constructor-selected source mode is used by run(); arena-only methods must not call the DTO-only layout overload. |
| ownership | No source owner is retained here; caller must keep it alive throughout Builder use. |
| failure | Bad mode assumptions can become contract or invalid access; public factory construction supplies the valid mode. |
| cost | Fixed pointer/reference state, independent of graph size. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0024

[Lines 171–171](../../../../../src/ir/program.cpp#L171); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Memo {const storage::Projection* source;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve compiler projection token aliases during native admission. |
| inputs / outputs | Borrowed compiler Projection address plus owning AccountedProjection result. |
| invariants | Lookup compares source.same_token(), not address/value equality; original indexes seed canonical binding projections. |
| ownership | Source pointer is temporary; result shares funded descriptor metadata; memo vector is scratch. |
| failure | Insertion/growth can fail and must leave private Data destructible. |
| cost | Each lookup scans the memo prefix; copied result handle can retain/release a descriptor control. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0025

[Lines 172–172](../../../../../src/ir/program.cpp#L172); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct NativeMemo {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve native projection aliases while cloning a program into another account. |
| inputs / outputs | Borrowed original AccountedProjection pointer and receiving-account projection handle. |
| invariants | Token identity, rather than field equality alone, selects reuse; seeded binding projections stay canonical. |
| ownership | Original pointer is not published; receiving descriptor handle owns its accounted control. |
| failure | Funded scratch growth and descriptor admission failures propagate. |
| cost | Linear memo-prefix token scan per lookup; a miss remaps endpoints by ID/token and freezes selected fields. Endpoint descriptor metadata was already cloned by clone_binding; memo result copies share the receiving controls. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0026

[Lines 173–174](../../../../../src/ir/program.cpp#L173); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Vector<Memo> projections_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain separate compiler/native projection alias maps in funded construction scratch. |
| inputs / outputs | Projection and NativeMemo vectors, selected by source mode. |
| invariants | Reserve estimates cover index plus node/edge/input/enumeration uses but do not make lookup constant-time. |
| ownership | Both vectors retain allocator identity; handles release with Builder and source pointers expire at its end. |
| failure | Reserve/push can fail without publishing a graph. |
| cost | Capacity storage and element release are charged; repeated scans can be quadratic in distinct projection count. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0027

[Lines 175–188](../../../../../src/ir/program.cpp#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Builder(CompiledProgram::Data& data,const PhysicalPlan& source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed compiler-token admission with canonical projections from the admitted storage binding. |
| inputs / outputs | Borrows Data, DTO and allowance; reserves index+two-node+edge+input+enumeration memo capacity. |
| invariants | Every capacity addition is checked before words debit/reserve; original index IDs resolve admitted binding projections. |
| ownership | Memo pointers borrow source indexes; vector capacity uses Data account and scratch attribution. |
| failure | Overflow, work denial, invalid IDs or funded allocation failure stop construction before run(). |
| cost | Scans indexes once and reserves the conservative projection-use capacity; no recursive payload admission yet. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
const auto add=[&](std::size_t n) {if(n>SIZE_MAX-capacity)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accumulate the DTO projection-use reserve bound without overflowing size_t. |
| inputs / outputs | Borrowed capacity variable plus one size increment; rejects n greater than remaining size_t headroom. |
| invariants | Each node count is deliberately added twice for parent/visible projection uses; this is a reserve estimate, not proof of a fixed maximum memo count. |
| ownership | Closure borrows constructor-local capacity and never escapes. |
| failure | IndexFailure overflow precedes mutation when the addition does not fit. |
| cost | Fixed checked arithmetic per dimension; vector reserve remains a separate allocation. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0028

[Lines 189–192](../../../../../src/ir/program.cpp#L189); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Builder(CompiledProgram::Data& data,storage::IndexWorkAllowance* work)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure an arena-only packer for native lowering instructions. |
| inputs / outputs | Borrows Data and optional allowance; both source pointers are null. |
| invariants | Accounted native handles already belong to receiver or retained source and may pass through their specialized overloads. |
| ownership | Empty scratch vectors retain Data account/attribution; Builder does not own Data. |
| failure | Allocator/account construction can fail; generic run() would reject absent source. |
| cost | Header/allocator setup only; no source traversal. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0029

[Lines 193–202](../../../../../src/ir/program.cpp#L193); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Builder(CompiledProgram::Data& data,const CompiledProgram& source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed deep native admission with the receiving binding token aliases. |
| inputs / outputs | Borrows native source, destination and allowance; reserves native memo capacity using physical-use dimensions. |
| invariants | Checks capacity sums before debit/reserve, then pairs each original index token with destination binding projection. |
| ownership | Native source pointers remain temporary; memo/result descriptors are receiving-account handles. |
| failure | Empty source, bad binding ID, overflow, work or memory failure abort before program publication. |
| cost | Index scan plus funded reserve; payload remapping is deferred to run(). |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
const auto add=[&](std::size_t n){if(n>SIZE_MAX-capacity)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each term of the native-source projection memo reserve estimate. |
| inputs / outputs | Updates constructor-local capacity after checked addition. |
| invariants | The estimate accounts for indexes, two node uses, edges, inputs and enumeration steps without inspecting their payload bytes. |
| ownership | Closure is borrowed local state only. |
| failure | Overflow is reported before this increment; no work grant is replenished. |
| cost | Fixed arithmetic per count; memo lookups remain linear after reserve. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0030

[Lines 203–219](../../../../../src/ir/program.cpp#L203); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> std::pair<T*,std::size_t> allocate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate an arena array and register its not-yet-constructed elements for cleanup. |
| inputs / outputs | Element count yields raw T pointer plus ledger index; object lifetime starts later. |
| invariants | Checks byte multiplication, debits pointer words, allocates block, then grows ledger and records a zero constructed count. T must be nothrow-destructible. |
| ownership | Local MemoryBlock owns storage until successful ledger insertion; Data then owns it. Callback destroys only the prefix recorded later. |
| failure | Overflow, grant or memory failure releases any local block and leaves existing records valid; no caller work rollback. |
| cost | Allocator request plus amortized ledger growth/relocation; destroying T may release nested descriptor metadata. Does not initialize array elements. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
[](void* p,std::size_t count) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy the completed prefix for the allocation record’s concrete element type. |
| inputs / outputs | Raw block address and recorded count; calls destroy_n&lt;T&gt;. |
| invariants | Only constructed objects may be counted; allocate&lt;T&gt; rejects throwing destructors at compile time. |
| ownership | Callback does not free the raw MemoryBlock; its owning record releases bytes after object destruction. |
| failure | Noexcept; corrupted pointer/count would violate the construction ledger contract. |
| cost | Linear in the number of objects destroyed plus their member/control teardown; trivial element destruction may be optimized away. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0031

[Lines 220–222](../../../../../src/ir/program.cpp#L220); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> void constructed(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance an arena record’s known-live prefix after successful placement construction. |
| inputs / outputs | Ledger index and count; stores constructed count. |
| invariants | Caller supplies a valid record and completed prefix; this helper does not check monotonicity/bounds or construct objects. |
| ownership | Updates private destination ledger only. |
| failure | No checks or throws in the scalar store under its internal precondition. |
| cost | Fixed indexed store. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0032

[Lines 223–228](../../../../../src/ir/program.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> T* defaults(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Default-construct an arena array with precise cleanup after any partial failure. |
| inputs / outputs | Count zero returns null; otherwise allocate and construct each element, advancing the ledger after success. |
| invariants | The failed element is never included in the constructed prefix. |
| ownership | Data owns the block and completed objects; returned pointer is an internal arena borrow. |
| failure | Allocation/work/overflow or T default-construction failure propagates; Data later destroys completed prefix. |
| cost | One allocation/ledger insertion and n default constructions/stores plus their actual member costs. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0033

[Lines 229–235](../../../../../src/ir/program.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view freeze(std::string_view value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy retained text into destination-account arena bytes. |
| inputs / outputs | Borrowed byte view becomes an equally sized arena string_view; empty input returns empty view. |
| invariants | Scalar byte debit precedes empty check/allocation; byte contents and length are preserved without terminator addition. |
| ownership | Caller bytes need survive only the call; output borrows Data arena. |
| failure | Grant, overflow or memory failure propagates; previously admitted work is not rolled back. |
| cost | Linear byte copy plus char block/ledger overhead; nonempty strings are not interned. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0034

[Lines 236–236](../../../../../src/ir/program.cpp#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view freeze(const std::string& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit an owning compiler string through the native text copier. |
| inputs / outputs | Borrows std::string as string_view, returning destination-arena bytes. |
| invariants | Does not retain the compiler string, its capacity or allocator. |
| ownership | Returned view needs destination program ownership. |
| failure | Same grant/memory/overflow faults as text freeze. |
| cost | Linear in byte length plus arena allocation/ledger cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0035

[Lines 237–237](../../../../../src/ir/program.cpp#L237); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::InlineDecimal freeze(const Decimal& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert an exact compiler Decimal into the native bounded inline representation. |
| inputs / outputs | Returns InlineDecimal::copy_of(value). |
| invariants | Copies the already valid Decimal coefficient, scale and sign exactly; this overload does not parse, validate or round a new decimal spelling. |
| ownership | Inline result has no dependency on compiler Decimal storage. |
| failure | InlineDecimal::copy_of is noexcept; this overload adds no work-allowance debit or checked failure path. |
| cost | Copies the existing bounded coefficient digits (at most 38) plus scale/sign into inline storage; no destination arena block. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0036

[Lines 238–242](../../../../../src/ir/program.cpp#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedLayout freeze(const storage::TupleLayout& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a compiler layout token to its admitted canonical descriptor. |
| inputs / outputs | Reads source.id(), verifies source token against DTO layouts, returns binding.layout(id). |
| invariants | Requires DTO packing mode and exact token membership; equal field values alone do not authorize remapping. |
| ownership | Returns shared receiving-account descriptor control; no source layout owner retained. |
| failure | Work denial, invalid token/ID or binding lookup fault propagates. |
| cost | One structural debit, token/ID checks and handle copy; earlier freeze_binding paid descriptor-copy cost. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0037

[Lines 243–250](../../../../../src/ir/program.cpp#L243); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedProjection freeze(const storage::Projection& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve or construct a compiler projection against admitted endpoint tokens. |
| inputs / outputs | Token scan returns existing memo result; miss remaps source/target layouts then freezes selected fields and appends memo. |
| invariants | Reuse is source token identity; newly frozen endpoint IDs/tokens come from destination binding. |
| ownership | Memo borrows original token only during construction; result owns funded projection control. |
| failure | Work/memory/overflow, token membership or projection-domain fault aborts the private build. |
| cost | Linear memo-prefix scan; miss copies selected fields and performs AccountedProjection validation/derived-metadata work plus memo growth. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0038

[Lines 251–253](../../../../../src/ir/program.cpp#L251); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Native construction already owns every nested span/token through this
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require backing native ownership before shallow instruction copying in arena-only construction. |
| inputs / outputs | Documents the specialized AccountedLayout/Projection and five native instruction overloads immediately below. |
| invariants | Only arena-only mode bypasses field-wise remapping. Deep native admission must still copy nested views and remap tokens; the generic fallback remains strict for unmapped owning types. |
| ownership | Nested spans borrow destination arena or canonical retained basis, while descriptors share existing accounted Data controls. |
| failure | This precondition is supplied by NativeLowering construction; pass-through overloads do not independently check every nested view. |
| cost | Shallow copy avoids repeated payload admission but retains handle copy/release costs; it does not erase original storage cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0039

[Lines 254–258](../../../../../src/ir/program.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedLayout freeze(const storage::AccountedLayout& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share a native construction token or remap it during deep admission. |
| inputs / outputs | Arena-only mode returns the existing handle; native-source mode verifies its ID/token against original layouts and returns receiver binding.layout(id). |
| invariants | Passing through in arena mode is valid only because its controls already belong to new graph or canonical source; it is not deep admission. |
| ownership | AccountedLayout handle copies retain existing funded Data controls, including in arena mode. |
| failure | Native-source branch can fail on work/ID/token/binding checks; pass-through performs no validation. |
| cost | Fixed handle/token work here; cloning descriptor bytes was done by clone_binding in admission mode. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0040

[Lines 259–266](../../../../../src/ir/program.cpp#L259); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedProjection freeze(const storage::AccountedProjection& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share arena-owned projection controls or reconstruct native-source tokens in the receiver. |
| inputs / outputs | Arena-only returns the handle; deep admission scans native memo and freezes fields with remapped endpoints on a miss. |
| invariants | Alias reuse follows exact original projection token; selected field equality alone is insufficient. |
| ownership | Pass-through shares the existing accounted control; newly built projection and memo scratch use destination attribution/account. |
| failure | Grant/memory/overflow, original endpoint membership or projection validity faults propagate. |
| cost | Pass-through is handle copy; admission miss adds linear memo scan, selected-field copy and descriptor validation/construction. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0041

[Lines 267–267](../../../../../src/ir/program.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
program::PhysicalRelation freeze(const program::PhysicalRelation& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze native PhysicalRelation while preserving its layout descriptor and numeric relation role/coordinates. |
| inputs / outputs | Native-source admission recursively maps the aggregate; arena-only lowering returns a value copy. |
| invariants | Deep admission remaps the layout token into receiver binding; arena-only copying preserves the already owned descriptor control. |
| ownership | Its layout handle shares the existing funded control and all other fields are values; this result has no nested borrowed arrays. |
| failure | Deep branch can fail on field work/memory/token checks; shallow branch uses the value/member copy operations. |
| cost | Fixed relation header/handle copy in arena mode; native admission adds aggregate checkpoint and canonical layout membership lookup, not per-relation descriptor metadata cloning. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0042

[Lines 268–268](../../../../../src/ir/program.cpp#L268); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
program::PhysicalInput freeze(const program::PhysicalInput& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze native PhysicalInput while preserving its physical layout, projection and guard spans. |
| inputs / outputs | Native-source admission recursively maps the aggregate; arena-only lowering returns a value copy. |
| invariants | Arena-only pass-through requires guard arrays/strings already retained by Data or canonical basis; deep admission recursively copies guard payload and remaps descriptors. |
| ownership | Layout/projection handles retain existing funded controls; equality/constant spans and constant strings still need destination/canonical backing Data. |
| failure | Deep branch can fail on field work/memory/token checks; shallow branch uses the value/member copy operations. |
| cost | Arena mode copies fixed header/handles; admission scans/copies equality and constant payload plus projection memo/selected-field work. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0043

[Lines 269–269](../../../../../src/ir/program.cpp#L269); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
program::PhysicalNode freeze(const program::PhysicalNode& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze native PhysicalNode while preserving its child/scope/visible spans and layout/projection handles. |
| inputs / outputs | Native-source admission recursively maps the aggregate; arena-only lowering returns a value copy. |
| invariants | Arena-only copying is valid only after backing span ownership exists; deep admission recursively copies these arrays and remaps descriptors. |
| ownership | Layout/projection controls are shared owners; child/scope/visible spans remain borrows into destination arena or retained canonical source. |
| failure | Deep branch can fail on field work/memory/token checks; shallow branch uses the value/member copy operations. |
| cost | Arena mode copies fixed header and descriptor handles; admission visits child/scope arrays and performs layout/projection token remapping/memo work. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0044

[Lines 270–270](../../../../../src/ir/program.cpp#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
program::PhysicalEdge freeze(const program::PhysicalEdge& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze native PhysicalEdge while preserving its parent-key projection and edge coordinates. |
| inputs / outputs | Native-source admission recursively maps the aggregate; arena-only lowering returns a value copy. |
| invariants | Arena-only copies its funded projection control; deep admission remaps it through the receiving canonical descriptor inventory. |
| ownership | Parent-key projection is an owning shared funded handle; all edge coordinates are inline and there is no nested borrowed child sequence. |
| failure | Deep branch can fail on field work/memory/token checks; shallow branch uses the value/member copy operations. |
| cost | Arena mode is a fixed edge/handle copy; admission adds aggregate dispatch, projection memo scan and selected-field freeze on a miss. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0045

[Lines 271–271](../../../../../src/ir/program.cpp#L271); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
program::EnumerationStep freeze(const program::EnumerationStep& value)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze native EnumerationStep while preserving its optional parent projection, bucket requirement and depth. |
| inputs / outputs | Native-source admission recursively maps the aggregate; arena-only lowering returns a value copy. |
| invariants | Arena-only copies already funded optional projection control; native admission remaps an engaged projection and preserves exact optional absence. |
| ownership | Optional parent-key projection is an owning shared handle; node/relation/depth/parent/bucket coordinates are inline. |
| failure | Deep branch can fail on field work/memory/token checks; shallow branch uses the value/member copy operations. |
| cost | Arena mode is fixed step/optional handle work; admission adds optional projection memo lookup/freeze, without cursor or assignment-array traversal. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0046

[Lines 272–277](../../../../../src/ir/program.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T,class A> Frozen<std::vector<T,A>> freeze(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy an ordered compiler vector into constructed native arena elements. |
| inputs / outputs | Empty input returns empty span; nonempty input preserves length/order and recursively freezes every element. |
| invariants | Element lifetime is recorded only after successful construction; source capacity/allocator never become output ownership. |
| ownership | Input is borrowed synchronously; output span borrows a Data-owned block with constructed-prefix cleanup. |
| failure | Allocation/work/overflow or nested element failure propagates; partially constructed elements remain tracked for teardown. |
| cost | Linear element pass plus all nested byte/descriptor work and one array block/ledger entry. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0047

[Lines 278–283](../../../../../src/ir/program.cpp#L278); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T,class L,class A> Frozen<std::set<T,L,A>> freeze(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pack ordered compiler set iteration into a contiguous native Set. |
| inputs / outputs | Empty input returns empty view; nonempty input preserves comparator iteration order while mapping elements. |
| invariants | Set&lt;T&gt; later expects the frozen order to support its native comparison; no semantic sort or comparator retention occurs here. |
| ownership | Input is borrowed synchronously; output span borrows a Data-owned block with constructed-prefix cleanup. |
| failure | Allocation/work/overflow or nested element failure propagates; partially constructed elements remain tracked for teardown. |
| cost | One source-node iteration pass and recursive element admission; no destination tree insertion. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0048

[Lines 284–288](../../../../../src/ir/program.cpp#L284); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> Span<Frozen<T>> freeze(Span<T> source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-copy a native span into the receiver arena for source admission. |
| inputs / outputs | Empty input returns empty; nonempty maps each element to Frozen&lt;T&gt; and preserves position. |
| invariants | The element-specific overload can deliberately share already funded handles in arena-only mode, while every new span array belongs to destination. |
| ownership | Input is borrowed synchronously; output span borrows a Data-owned block with constructed-prefix cleanup. |
| failure | Allocation/work/overflow or nested element failure propagates; partially constructed elements remain tracked for teardown. |
| cost | Linear element pass plus nested admission and descriptor-handle costs. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0049

[Lines 289–289](../../../../../src/ir/program.cpp#L289); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> Set<Frozen<T>> freeze(Set<T> source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit a native ordered Set through the contiguous span packer. |
| inputs / outputs | Freezes Span&lt;T&gt;(source), then wraps identical destination pointer/count as Set&lt;Frozen&lt;T&gt;&gt;. |
| invariants | Preserves original order and does not rerun set normalization or sorting. |
| ownership | Output borrows Data arena; input view and any source owner need survive only the call. |
| failure | Span packing faults propagate. |
| cost | Linear element conversion with the same nested costs as native span freeze. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0050

[Lines 290–293](../../../../../src/ir/program.cpp#L290); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> Frozen<std::optional<T>> freeze(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve nullable metadata and admit only its engaged payload. |
| inputs / outputs | Empty optional returns empty; engaged input recursively freezes *source in place. |
| invariants | Null versus present-empty container remains distinguishable. |
| ownership | Output uses the nested result representation and its destination/descriptor ownership. |
| failure | Only engaged nested conversion can fail. |
| cost | Fixed branch plus engaged payload conversion cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0051

[Lines 294–299](../../../../../src/ir/program.cpp#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<std::size_t I=0,class... T> Frozen<std::variant<T...>> freeze_variant(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the active compiler/native variant alternative without changing its index. |
| inputs / outputs | Template index advances until it equals source.index(), then freezes that alternative in place. |
| invariants | Alternative order is preserved; a valueless variant falls through to contract rejection. |
| ownership | Only active payload ownership is converted; dispatcher retains no source reference after return. |
| failure | Valueless/unsupported index throws IndexFailure(contract); active conversion failures propagate. |
| cost | At most the fixed alternative count of dispatch calls plus active payload cost; depth does not follow query/tree size. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0052

[Lines 300–300](../../../../../src/ir/program.cpp#L300); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class... T> Frozen<std::variant<T...>> freeze(const std::variant<T...>& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enter indexed native mapping of a retained variant value. |
| inputs / outputs | Returns freeze_variant(source) with unchanged active alternative index. |
| invariants | No alternative is selected by value coercion or scalar ordering. |
| ownership | Result ownership follows the chosen nested freeze operation. |
| failure | Valueless or nested work/memory/domain faults propagate. |
| cost | Fixed wrapper plus bounded alternative dispatch and active payload conversion. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0053

[Lines 301–330](../../../../../src/ir/program.cpp#L301); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
JsonView freeze(const io::Json& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Flatten compiler JSON into arena nodes, object members and owned text without recursive traversal. |
| inputs / outputs | Borrowed JSON produces a root JsonView; pending entries pair source addresses with already constructed target nodes. |
| invariants | Processes every queued node once; preserves unsigned before signed numeric classification, ordered object keys and array order. Binary/discarded values are rejected by the null check. |
| ownership | Pending vector is funded scratch; all retained nodes/member arrays/key/string bytes belong to Data, with no source JSON owner retained. |
| failure | Grant/memory/overflow or unsupported JSON-kind faults abort; all default-constructed nodes are ledger tracked. |
| cost | Linear nodes/members/string bytes plus capacity growth and allocation records; queue retains all scheduled entries until completion, so scratch scales with graph size rather than only depth. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
struct Pending {const io::Json* source;JsonNode* target;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair one borrowed compiler JSON node with its flat arena destination. |
| inputs / outputs | Raw const source pointer and live JsonNode target pointer. |
| invariants | Source graph stays stable for the whole freeze call; destination arrays are allocated before enqueue. |
| ownership | Entry owns neither endpoint; Data owns target, caller owns source. |
| failure | Entry copy itself has no checks; valid endpoint lifetime is an internal precondition. |
| cost | Fixed two-pointer record; vector growth accounts for its storage. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
const auto enqueue=[&](const io::Json* input,JsonNode* target)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Schedule a compiler JSON node after admitting pending-list capacity growth. |
| inputs / outputs | Checks doubling, debits words for new capacity, reserves and appends the source/target pair. |
| invariants | Target already exists; failing queue growth leaves it default constructed and covered by the arena ledger. |
| ownership | Closure borrows pending vector, Data and allowance through Builder; source pointer is temporary. |
| failure | Capacity overflow, work or funded reserve failure propagates before this enqueue completes. |
| cost | Amortized append with occasional linear pending-record relocation; old entries stay retained until end. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0054

[Lines 331–362](../../../../../src/ir/program.cpp#L331); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
JsonView freeze(JsonView source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deep-admit a flat native JSON view into receiver-owned arena storage. |
| inputs / outputs | Every node kind is copied; arrays and object members enqueue borrowed subviews and strings/keys are separately frozen. |
| invariants | Default/null view becomes an allocated null root; native tree shape and numeric alternatives remain unchanged. |
| ownership | Result owns no source control itself but is backed wholly by destination Data; caller must keep original Data alive during packing. |
| failure | Grant/memory/overflow or inconsistent source view access faults propagate with private graph cleanup. |
| cost | Traverses nodes/member keys/string bytes; pending scratch is O(total scheduled nodes) and traversal stack depth is fixed. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
struct Pending {JsonView input;JsonNode* output;};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain a borrowed native JSON subview beside its allocated destination node. |
| inputs / outputs | Input JsonView and output JsonNode pointer. |
| invariants | A copied JsonView does not acquire source ownership; the external source program must remain alive. |
| ownership | Entry owns neither source nor destination control; Data owns output bytes. |
| failure | No validation in record copying; later source access enforces kind/bounds. |
| cost | Fixed view/pointer copy and queue storage. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
const auto enqueue=[&](JsonView input,JsonNode* output)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append a native JSON traversal task under funded scratch capacity. |
| inputs / outputs | Doubles checked capacity, debits pointer words, reserves and appends input/output. |
| invariants | Does not recurse or retain source ownership; output node is already arena constructed. |
| ownership | Closure and queued views borrow during one synchronous freeze. |
| failure | Overflow/work/memory failure propagates while existing queued/arena state remains RAII-owned. |
| cost | Amortized append with linear relocation when capacity grows; aggregate queue memory follows all scheduled nodes. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0055

[Lines 363–388](../../../../../src/ir/program.cpp#L363); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> Frozen<T> aggregate(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze each declared aggregate field while rejecting unmapped nontrivial ownership. |
| inputs / outputs | Type&lt;T&gt;::fields selects structured bindings from one through fifteen; zero fields requires same-type trivially-copyable leaf. |
| invariants | Mapped field order/count must match actual declarations. This is a conversion mechanism and does not validate tree/model/proof semantics or automatically recognize a new trivial borrowed owner. |
| ownership | Nested overloads own/admit payload; local aggregate result contains native views and shared accounted handles. |
| failure | Unsupported nontrivial leaves fail compilation; instantiated nested field operations can throw and Data ledger covers their allocations. |
| cost | One structural debit for mapped aggregate plus sum of nested fields; leaf copy scales with its value representation and recursive dispatch depth follows fixed type nesting. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0056

[Lines 389–389](../../../../../src/ir/program.cpp#L389); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> Frozen<T> freeze(const T& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply reviewed aggregate/native-leaf mapping when no specialized ownership conversion matches. |
| inputs / outputs | Returns aggregate(source). |
| invariants | Specific text/container/descriptor/JSON overloads must take precedence over generic mapping. |
| ownership | Does not supply an independent owner; output follows aggregate and nested overload lifetimes. |
| failure | Compile-time mapping checks or nested construction faults propagate. |
| cost | Wrapper cost plus aggregate dispatch/field costs. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0057

[Lines 390–392](../../../../../src/ir/program.cpp#L390); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pack the source selected by the Builder constructor. |
| inputs / outputs | Native source wins when present; otherwise requires a DTO source and calls run_source. |
| invariants | Arena-only Builders use individual freeze/auxiliary methods and must not call run(). |
| ownership | Both sources are borrowed for the synchronous build; destination remains private. |
| failure | Absent source throws contract; all run_source construction faults propagate. |
| cost | Fixed source-mode branch followed by full source admission. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0058

[Lines 393–404](../../../../../src/ir/program.cpp#L393); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Source> void run_source(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit executable model, SQL, identity and physical metadata from a checked compiler/native source. |
| inputs / outputs | Copies route/core/tree/normalization/report/identity/options/profile/instructions/result token and work, then source digest and auxiliary descriptors. |
| invariants | Producer work and validation values are copied, not recomputed as independent proof checks. Source digest contract is exactly 64 bytes; this trusted-source routine does not recheck that length. |
| ownership | Frozen text/arrays belong to receiver; canonical descriptors come from admitted binding. No caller source pointer is published. |
| failure | Any nested memory/work/contract/overflow failure leaves only an unpublished, destructible Data graph. |
| cost | Sum of all retained payload bytes/arrays, projection memo scans, JSON nodes and auxiliary metadata work; not just physical node count. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0059

[Lines 405–437](../../../../../src/ir/program.cpp#L405); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void finish_native_auxiliary() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct normalized SQL result and complete physical-source descriptors needed beyond active instructions. |
| inputs / outputs | Uses original SQL catalog when normalized; EXISTS creates one boolean output field, otherwise normalized output kinds/domains. Every source table gets a descriptor/relation coordinate. |
| invariants | Used physical-base relations reuse their active relation ID and layout token. Unused tables receive new source-origin descriptors and auxiliary relation/layout coordinates outside the active binding inventory. SQL result descriptor is separate when normalized. None of these auxiliary descriptors registers a mutable runtime table by itself. |
| ownership | Data owns auxiliary SourceTable array and result/source descriptor controls; scratch field vector uses Data account. |
| failure | ID arithmetic, unsupported SQL kind, allowance/memory or layout construction faults abort private build. |
| cost | For each catalog table performs a linear relation search, up to O(tables*relations); also scans SQL outputs/unused-table columns and copies binding bytes/descriptor metadata. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
[&](const auto& relation) {
          step(work_);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find an existing physical-base relation for one complete source table. |
| inputs / outputs | Predicate matches physical_base role and current table ID; each inspected relation debits structural work. |
| invariants | Stops at the first exact role/base match; logical/internal relations do not stand in for a source table. |
| ownership | Borrows current table index and Data relation span during auxiliary construction. |
| failure | Allowance exhaustion propagates from step(). |
| cost | Fixed predicate work per relation, repeated for each table; total search can be tables times relations. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0060

[Lines 438–443](../../../../../src/ir/program.cpp#L438); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L438-L443:sha256:47d7a2956658d11b89106bb20420cfd9d21d0fe04434507f3dea35daa056357f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the NativeBuilder type and program::detail namespace, textually includes program_replan.inc into the same translation unit, then opens crown for the following public compiler definitions. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The included .inc definitions compile in the enclosing program.cpp translation unit and rely on its private declarations; they do not form a separate link unit. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | Compilation failures from the included definitions are reported while compiling program.cpp; their runtime errors remain those of the included callables. |
| cost | Textual inclusion adds no runtime dispatch or per-call wrapper; work belongs to the included definitions. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/code_specs/files/src/ir/program.cpp.md](program.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0061

[Lines 444–447](../../../../../src/ir/program.cpp#L444); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram CompiledProgram::standalone(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a self-owned native compiler program before any execution account exists. |
| inputs / outputs | Borrowed PhysicalPlan; creates a UINT64_MAX-capacity account and delegates to compile(). |
| invariants | The maximum account cap does not bypass later runtime admission into its receiving account/grant. |
| ownership | Published Data retains the component account; compiler DTO is not retained. |
| failure | Account/control/compile failures propagate; no partial artifact is returned. |
| cost | Account construction plus full native compile traversal, descriptor admission and allocations. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0062

[Lines 448–456](../../../../../src/ir/program.cpp#L448); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram CompiledProgram::compile(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pack a lowered compiler DTO under compiler work counters in the supplied account. |
| inputs / outputs | freeze_binding(mode=compiler), new owner tag, Data word debit/control allocation and DTO Builder run; complete program returned. |
| invariants | Internal fixed diagnostics grant is UINT64_MAX per dimension, separate from indexed execution cap. Trusts source lowering/validation instead of rerunning P02 or a minimum proof. |
| ownership | All new immutable metadata and canonical descriptor controls are receiver funded; private result owns cleanup until publication. |
| failure | Owner exhaustion, grant counter overflow, descriptor contracts, MemoryFailure or nested admission faults unwind the private result. |
| cost | Full source payload and descriptor scans/copies; binding freeze and projection memo alias scans can be quadratic in descriptor count. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0063

[Lines 457–459](../../../../../src/ir/program.cpp#L457); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram CompiledProgram::freeze(const resource::MemoryAccount& account,const PhysicalPlan& source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep public plan freeze in execution metadata mode while sharing the existing builder body. |
| inputs / outputs | A receiver, actual PhysicalPlan and optional canonical execution allowance enter public \`freeze\`; it delegates to \`freeze_impl(..., MetadataWork::execution)\`. |
| invariants | Only the closed SqlColdRebuild friend selects compiler metadata mode, and only from the authentic backend of an actual lowering result. |
| ownership | The returned CompiledProgram owns receiver-funded immutable metadata; input plan is borrowed for the call. |
| failure | Existing binding, owner, allowance, allocation and Builder failures still unwind the unpublished result. |
| cost | One construction-only helper call; existing metadata/Builder costs remain, with no execution-record field or hot path branch. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0064

[Lines 460–469](../../../../../src/ir/program.cpp#L460); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram CompiledProgram::freeze_impl(const resource::MemoryAccount& account,const PhysicalPlan& source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Centralize native program construction while selecting its metadata accounting mode explicitly. |
| inputs / outputs | Accepts an actual PhysicalPlan and MetadataWork mode, freezes the storage binding, allocates Data and runs the existing Builder. |
| invariants | It has no separate descriptor import route; public API always supplies execution mode and private cold bridge selects mode by authentic backend. |
| ownership | All retained Data stays in receiving MemoryAccount. |
| failure | Existing freeze_binding, owner allocation, words admission and Builder failures unwind private Data. |
| cost | Same builder arrays/descriptors/work plus selected binding mode; caller still supplies the actual root allowance. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0065

[Lines 470–473](../../../../../src/ir/program.cpp#L470); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L470-L473:sha256:abd14943a5c8a71f5ef0527a2ebe273f1a465facc46e3fa784e884942a419d87
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Freeze a compiled program while preserving its actual input execution mode. |
| inputs / outputs | Receiving account, immutable compiled source and borrowed work grant; prepared source passes its retained finite limits to freeze_program. |
| invariants | Prepared views are rebuilt against receiving metadata, never copied as dangling spans. Plain sources keep interpreter mode. Original indexed cap validation precedes preparation. |
| ownership | Result independently owns copied metadata; source remains valid and unchanged. |
| failure | Existing storage/resource/overflow/logical failures propagate with unpublished receiver storage released; grant consumption is not rolled back. |
| cost | Full cold base copy plus finite rebuild only for opted-in prepared input; no global reuse cache. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0066

[Lines 474–478](../../../../../src/ir/program.cpp#L474); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L474-L478:sha256:a6894ef65e5a0bfe240cecbb60a841a2363f53997ce34462a80b861ac65561e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject non-SQL sources before constructing an automatically prepared copy. |
| inputs / outputs | Receiving account, genuine CompiledProgram, limits and optional native grant; returns a SQL-threaded program. |
| invariants | Requires normalized metadata even for a constant SQL operator. Plain CQ cannot receive a misleading threaded label; source identity and defaults remain unchanged. |
| ownership | Borrows source and grant; success transfers only newly receiver-funded metadata. |
| failure | SQL contract denial precedes receiving allocation; later failures unwind via freeze_program. |
| cost | One normalized-presence guard then cold receiving preparation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0067

[Lines 479–502](../../../../../src/ir/program.cpp#L479); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L479-L502:sha256:fa25c6c9fbe1dd73da838b180d9b300f18bf923e2bb5b6d822cf6e8ec70f3e0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate and copy the receiving base before charging or publishing optional prepared inputs. |
| inputs / outputs | Account/source/work/optional limits in; immutable owning CompiledProgram out. A reference-only local work meter is used if opted-in preparation has no caller grant. |
| invariants | clone_binding validates original indexed allowance before analyze can reduce it. No indexed grant is synthesized. Base-freeze five-domain counters exclude analyze/build. Publication follows complete base and prepared construction. |
| ownership | Account-backed binding, Data/control, copied arena and PreparedInputs use one receiving attribution; views bind to result normalized storage. Borrowed source is never mutated. |
| failure | Contract/cap/memory/overflow/allocation failure destroys unpublished copy. Current retained account bytes return; used logical/native work and account peak remain charged. |
| cost | Base copying and analysis/write passes scale with admitted metadata and adapter arguments; extra table capacity reported separately from complete account allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0068

[Lines 503–505](../../../../../src/ir/program.cpp#L503); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L503-L505:sha256:c5754b047ade79fb271f09b21e400143b9040abaf3515f828f1e1d0d8c52ee62
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the actual immutable input execution enum. |
| inputs / outputs | Valid program handle in; threaded_v1 iff private prepared owner exists, otherwise interpreted_v1. |
| invariants | No descriptor label can substitute for actual prepared owner presence. |
| ownership | Borrows Data; returns a value. |
| failure | Empty handle raises existing invalid_storage. |
| cost | Constant time, no allocation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0069

[Lines 506–508](../../../../../src/ir/program.cpp#L506); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L506-L508:sha256:8ec7ce2ebca1c8b20f6b38182c61f9184a5b43d6e54ec91bd7b6e93114a3ae85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a versioned execution key separate from physical identity. |
| inputs / outputs | Valid program in; crown-input-threaded-v1 or crown-input-interpreted-v1 string_view out. |
| invariants | Mode is observed from immutable prepared ownership, not inferred from source/tree hash. |
| ownership | View points to static literal and needs no new owner. |
| failure | Empty handle raises invalid_storage. |
| cost | Constant time, no allocation. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp) |

## B0070

[Lines 509–511](../../../../../src/ir/program.cpp#L509); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L509-L511:sha256:7b1acb7d404db96026cd6e1b8cd1f3d20b4820fafac2f17b5662fe90b84ac3e4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report retained preparation usage without a mutable diagnostics handle. |
| inputs / outputs | Valid program in; value copy of prepared usage or all-zero unprepared usage out. |
| invariants | Reported table capacity does not claim complete query memory; base-freeze and prep work remain separate scopes. |
| ownership | Returned scalar record owns its values; no instruction span escapes. |
| failure | Empty handle raises invalid_storage. |
| cost | Constant-size copy, no allocation. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0071

[Lines 512–514](../../../../../src/ir/program.cpp#L512); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L512-L514:sha256:dd242b216698288619c1754b5b232fe1bd805b61c30c7493f9119579b5eac88a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the retained input preparation resource policy for cold exact cache/source binding. |
| inputs / outputs | Valid immutable program in; optional copied InputPreparationLimits out, absent for interpreter. |
| invariants | Returns actual stored finite limits rather than observed usage/base-freeze counters. This lets cache/admission consumers distinguish execution policy while preserving ordinary physical/source hashes and interpreted encoding. |
| ownership | Returns plain value fields; no instruction view, mutable diagnostics handle or allocation escapes. |
| failure | Empty compiled handle raises existing invalid_storage; otherwise no allocation or denial. |
| cost | Constant-time optional scalar copy in cold consumers; no runtime update hook. |
| Design | [docs/selection_binding.md](../../../../selection_binding.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0072

[Lines 515–519](../../../../../src/ir/program.cpp#L515); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram CompiledProgram::replan(const CompiledProgram& basis,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a new native candidate program in the basis account. |
| inputs / outputs | Rejects absent basis, then invokes NativeLowering::run(basis.account(),basis,candidate,limits). |
| invariants | Exact catalog/query binding and typed candidate valid/native-height consistency are checked before source-credit admission and operator construction. Nonempty contradiction uses the canonical empty operator tree and valid zero-height/depth report, preserving original candidate/proof; ordinary and empty-body inputs retain candidate tree/report. No independent optimum replay occurs. |
| ownership | Returned graph keeps canonical source alive and funds fresh metadata/scratch under basis account; basis remains usable. |
| failure | Absent basis yields ReplanFailure(binding); all NativeLowering logical/storage/memory faults propagate. |
| cost | Wrapper check plus full synchronous binding/lowering/digest work; no stop/depth/time continuation is exposed. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0073

[Lines 520–523](../../../../../src/ir/program.cpp#L520); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram CompiledProgram::replan_into(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Lower a supplied immutable source/candidate pair in the receiving query account. |
| inputs / outputs | Passes account,basis,candidate,limits to NativeLowering::run. |
| invariants | Exact catalog/query binding and typed candidate valid/native-height consistency are checked before source-credit admission and operator construction. Nonempty contradiction uses the canonical empty operator tree and valid zero-height/depth report, preserving original candidate/proof; ordinary and empty-body inputs retain candidate tree/report. No independent optimum replay occurs. |
| ownership | Fresh Data/instructions/tokens/scratch use receiver; canonical source is a retained supplied artifact funded by its existing account. |
| failure | Invalid input, binding/limits, memory/storage/overflow failures propagate before result publication. |
| cost | Full actual native lowering work, including complete binding encodes and physical digest byte scans; source credit checks are only part of this. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0074

[Lines 524–527](../../../../../src/ir/program.cpp#L524); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const CompiledProgram::Data& CompiledProgram::data() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject empty handles before exposing native metadata. |
| inputs / outputs | Returns *data_ when present; throws invalid_storage otherwise. |
| invariants | Default and implicit-moved-from handles have no valid Data. |
| ownership | Returned reference borrows shared Data; function does not acquire an owner. |
| failure | IndexFailure(invalid_storage) for absence. |
| cost | One presence check and pointer dereference. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0075

[Lines 528–528](../../../../../src/ir/program.cpp#L528); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const resource::MemoryAccount& CompiledProgram::account() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the receiver account for this program’s fresh allocations. |
| inputs / outputs | Returns Data.account by const reference; account() does not copy its payload. |
| invariants | Does not imply a retained supplied canonical source used this same account. |
| ownership | The returned account reference borrows Data. Explicitly copying MemoryAccount retains its controller/cap, not the program metadata or source-view lifetime. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0076

[Lines 529–529](../../../../../src/ir/program.cpp#L529); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRoute CompiledProgram::route() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the selected tree or constant execution route. |
| inputs / outputs | Returns Data.route by value. |
| invariants | constant_false executes an empty operator while the retained original Query may still contain atoms/head. Its zero operator height does not establish an original structural minimum. |
| ownership | Scalar return requires no retained borrow after the call. |
| failure | Empty handle throws invalid_storage. |
| cost | Checked scalar lookup. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0077

[Lines 530–530](../../../../../src/ir/program.cpp#L530); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Catalog& CompiledProgram::catalog() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the core catalog consumed by physical instructions. |
| inputs / outputs | Returns Data.catalog by const reference; catalog() does not copy its payload. |
| invariants | Normalized original physical catalog is exposed by source_catalog(), separately. |
| ownership | Catalog/table/name/constraint/statistics views borrow Data or its retained canonical basis. Copying program::Catalog copies those views and does not acquire an owner. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0078

[Lines 531–531](../../../../../src/ir/program.cpp#L531); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Query& CompiledProgram::query() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained original core occurrence/head model including contradiction metadata. |
| inputs / outputs | Returns Data.query by const reference; query() does not copy its payload. |
| invariants | Does not canonicalize a contradictory nonempty body to an empty structural query. |
| ownership | Variable/atom/term/head arrays and string constants borrow Data or retained basis. A copied program::Query header does not retain them. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0079

[Lines 532–532](../../../../../src/ir/program.cpp#L532); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::FreeConnexTree& CompiledProgram::tree() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the executable operator tree while retaining original structural authority separately. |
| inputs / outputs | Returns Data.tree by const reference without copying nodes, scopes or claims. |
| invariants | For nonempty contradiction replans this is the canonical empty executable operator tree, while query() retains original atoms/head and the supplied candidate keeps its original structural tree/proof. Ordinary and empty-body replans preserve the candidate raw tree, including optional claims. The view alone establishes no independently replayed optimum. |
| ownership | Node/ID/scope/child/claim views borrow Data; its empty constant operator has no node payload. A copied tree header is not an owner of a nonempty tree. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0080

[Lines 533–533](../../../../../src/ir/program.cpp#L533); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<program::NormalizedSql>& CompiledProgram::normalized() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the optional admitted SQL binding, constants and compiled adapter metadata. |
| inputs / outputs | Returns Data.normalized by const reference; normalized() does not copy its payload. |
| invariants | Absence distinguishes direct CQ input; access does not rerun parsing or normalization. |
| ownership | All nested SQL source/catalog/expression/adapter/output views borrow Data or retained basis. Copying this optional native program does not retain those backing owners. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0081

[Lines 534–534](../../../../../src/ir/program.cpp#L534); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::ValidationReport& CompiledProgram::validation() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained validation report for executable operator metadata. |
| inputs / outputs | Returns Data.validation by const reference; no diagnostic or array copy. |
| invariants | Nonempty contradiction replans expose a fresh valid operator report with native height and edge depth zero and empty connex/separator/violation arrays; this does not replace the original candidate validation or proof. Other routes retain the admitted compiler/candidate report. Observing a report creates no checked capability. |
| ownership | Diagnostic text, connex and separator views borrow Data; scalar validity/heights are values. Copying the native report does not retain its arrays or establish proof authority. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0082

[Lines 535–535](../../../../../src/ir/program.cpp#L535); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::QueryIdentity& CompiledProgram::identity() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained semantic/output/cost/cache identity and permutations. |
| inputs / outputs | Returns Data.identity by const reference; identity() does not copy its payload. |
| invariants | Producer work is retained credit; reading it does not regenerate canonical JSON or hashes. |
| ownership | Canonical JsonView, digests and ID-order spans borrow Data or retained basis. Neither copied identity header nor JsonView acquires a source owner. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0083

[Lines 536–536](../../../../../src/ir/program.cpp#L536); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::PhysicalOptions& CompiledProgram::options() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the retained policy, producer limits and indexed-backend configuration. |
| inputs / outputs | Returns Data.options by const reference; options() does not copy its payload. |
| invariants | Replan host-limit intersections are local construction state and do not rewrite these producer options. |
| ownership | Policy label views borrow Data or retained basis; limits/backend spec are inline values. Copying native options does not own the policy text. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0084

[Lines 537–537](../../../../../src/ir/program.cpp#L537); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::GuaranteeProfile& CompiledProgram::guarantee() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the stored execution/height/backend/accounting profile labels. |
| inputs / outputs | Returns Data.guarantee by const reference; guarantee() does not copy its payload. |
| invariants | Labels do not grant independently checked optimum, completed runtime initialization or measured performance. |
| ownership | Profile labels and string inventories borrow Data or retained basis. Copying the native profile does not retain the backing label bytes. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0085

[Lines 538–538](../../../../../src/ir/program.cpp#L538); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::EnumerationProgram& CompiledProgram::enumeration() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the immutable assignment steps, output slots, equalities and recorded depth. |
| inputs / outputs | Returns Data.enumeration by const reference; enumeration() does not copy its payload. |
| invariants | This is instruction metadata, not a started cursor or materialized answer set. |
| ownership | Step/output/equality arrays borrow Data. A copied parent-key projection can retain its descriptor controls, but not the containing instruction/assignment arrays. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0086

[Lines 539–539](../../../../../src/ir/program.cpp#L539); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::AccountedLayout& CompiledProgram::result_layout() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the core ordered-head result descriptor. |
| inputs / outputs | Returns Data.result_layout by const reference; result_layout() does not copy its payload. |
| invariants | Duplicate output variables keep their tuple equality constraints; SQL wrapper/output layout may differ. |
| ownership | The returned reference needs Data; explicitly copying AccountedLayout retains its own funded descriptor/control and context/fields independently of this program. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0087

[Lines 540–540](../../../../../src/ir/program.cpp#L540); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::AccountedLayout& CompiledProgram::sql_result_layout() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the SQL-visible result descriptor or core result descriptor for direct CQ. |
| inputs / outputs | Returns Data.sql_result_layout by const reference; sql_result_layout() does not copy its payload. |
| invariants | EXISTS uses a single boolean field and normalized outputs preserve their SQL domains. |
| ownership | The reference borrows Data; copying AccountedLayout retains the SQL/core descriptor’s existing funded control, so that descriptor can outlive the program. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0088

[Lines 541–541](../../../../../src/ir/program.cpp#L541); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<program::SourceTable>& CompiledProgram::sources() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the complete source-table relation coordinates and layouts including unused tables. |
| inputs / outputs | Returns Data.sources by const reference; sources() does not copy its payload. |
| invariants | Auxiliary unused-table coordinates need not be entries in the active storage binding. |
| ownership | The SourceTable array borrows Data. Copying one SourceTable value retains its AccountedLayout control and relation value independently of the containing array. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0089

[Lines 542–551](../../../../../src/ir/program.cpp#L542); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedLayout CompiledProgram::scope_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an independent funded descriptor for an ordered sequence of core variables. |
| inputs / outputs | Caller layout ID, variable span, binding suffix and optional allowance; returns AccountedLayout bound to physical digest plus suffix. |
| invariants | Checks variable IDs and preserves duplicates/order. Caller chooses ID/suffix; this does not insert or validate membership in primary binding layouts. |
| ownership | Scratch fields and returned descriptor use program account/attribution; descriptor owns its fields/binding after program release. |
| failure | Empty program, bad variable ID, work/size/memory or descriptor failure propagates without altering program. |
| cost | Scans variables, constructs field metadata and copies digest/suffix bytes; pointer/scalar debits and descriptor validation/allocation are additional. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0090

[Lines 552–552](../../../../../src/ir/program.cpp#L552); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Catalog& CompiledProgram::source_catalog() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow original physical source schemas for normalized SQL or core schemas for direct CQ. |
| inputs / outputs | Returns normalized.binding.catalog when present, otherwise Data.catalog. |
| invariants | Distinct from core catalog when normalization introduced logical tables or projections. |
| ownership | View may live in canonical basis on replans; owning Data retains that source. |
| failure | Empty handle throws invalid_storage. |
| cost | Checked branch/member lookup. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0091

[Lines 553–553](../../../../../src/ir/program.cpp#L553); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<const program::Catalog> CompiledProgram::source_catalog_owner() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an owning alias to the physical source catalog using the existing native Data control. |
| inputs / outputs | Aliasing shared_ptr stores &source_catalog() and shares data_ control. |
| invariants | A replanned catalog may point into canonical basis, which Data.basis retains; no catalog mirror or replacement control is constructed. |
| ownership | Alias keeps Data and its canonical source alive independently of the original CompiledProgram handle. |
| failure | Empty program throws through source_catalog(); successful alias construction is a nonallocating shared-control operation. |
| cost | Checked source-catalog lookup and reference-count increment; final alias release can destroy full Data and source graphs. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0092

[Lines 554–554](../../../../../src/ir/program.cpp#L554); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view CompiledProgram::physical_sha256() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the physical artifact identity for the selected executable operator. |
| inputs / outputs | Returns the Data.physical_sha256 view, backed by admitted text or the fixed native_physical_digest array. |
| invariants | Native replan hashes the selected operator tree with source digest, plan-cache identity and ID-order maps; indexed v2 also includes full physical options. Reference v1 does not directly hash every finite physical option, so full source/options equality is a separate binding check. Hash equality itself grants no proof authority. |
| ownership | View borrows Data and any retained arena; caller keeps a program owner. |
| failure | Empty handle throws invalid_storage. |
| cost | Checked pointer/length return; no byte hashing or comparison. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0093

[Lines 555–555](../../../../../src/ir/program.cpp#L555); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view CompiledProgram::physical_source_sha256() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original compiler physical-source digest. |
| inputs / outputs | Returns string_view over Data.physical_source_digest; physical_source_sha256 explicitly spans the fixed 64-byte array. |
| invariants | Replan preserves the canonical admitted source digest while building a fresh candidate physical digest. Hash text is identity metadata, not checked proof authority. |
| ownership | View borrows Data and any retained arena; caller keeps a program owner. |
| failure | Empty handle throws invalid_storage. |
| cost | Checked pointer/length return; no byte hashing or comparison. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0094

[Lines 556–556](../../../../../src/ir/program.cpp#L556); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<storage::AccountedLayout>& CompiledProgram::layouts() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the primary canonical layout inventory for the storage binding. |
| inputs / outputs | Returns Data.layouts by const reference; layouts() does not copy its payload. |
| invariants | Auxiliary SQL-result/unused-source descriptors are exposed through their dedicated accessors. |
| ownership | The inventory span borrows Data/binding ownership. Each explicitly copied AccountedLayout retains only its own descriptor control and can outlive the inventory. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0095

[Lines 557–557](../../../../../src/ir/program.cpp#L557); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<program::PhysicalRelation>& CompiledProgram::relations() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the active physical-base and internal relation instructions. |
| inputs / outputs | Returns Data.relations by const reference; relations() does not copy its payload. |
| invariants | These immutable bindings do not contain mutable runtime table contents. |
| ownership | The relation array borrows Data. Copied PhysicalRelation values retain their layout controls and inline coordinates, not the array owner. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0096

[Lines 558–558](../../../../../src/ir/program.cpp#L558); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<program::IndexRequirement>& CompiledProgram::indexes() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the shared canonical projection requirements and use labels. |
| inputs / outputs | Returns Data.indexes by const reference; indexes() does not copy its payload. |
| invariants | Requirements are not registrations of mutable runtime indexes. |
| ownership | Requirement/use arrays borrow Data. Copying an AccountedProjection retains its endpoints/control, while a copied requirement still borrows its uses span. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0097

[Lines 559–559](../../../../../src/ir/program.cpp#L559); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<program::PhysicalInput>& CompiledProgram::inputs() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the occurrence routes, layout/projection tokens and core guard instructions. |
| inputs / outputs | Returns Data.inputs by const reference; inputs() does not copy its payload. |
| invariants | Adapt_input() executes these separately; reading does not validate any row. Constant routes expose an empty instruction collection even when query().atoms is nonempty. |
| ownership | The input array and guard spans/text borrow Data or retained basis. Copied layout/projection handles retain descriptor controls, not the guard arrays. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0098

[Lines 560–560](../../../../../src/ir/program.cpp#L560); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<program::PhysicalNode>& CompiledProgram::nodes() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the physical node scope, topology, layout/projection and relation-role instructions. |
| inputs / outputs | Returns Data.nodes by const reference; nodes() does not copy its payload. |
| invariants | Fields borrow the program arena or retained canonical source; no operator state is materialized. Constant routes expose an empty instruction collection even when query().atoms is nonempty. |
| ownership | Node and child/scope/visible arrays borrow Data or retained basis. Copied descriptors retain their controls, but copying PhysicalNode does not own its nested spans. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0099

[Lines 561–561](../../../../../src/ir/program.cpp#L561); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<program::PhysicalEdge>& CompiledProgram::edges() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the child-slot and parent-key/reverse-index instructions. |
| inputs / outputs | Returns Data.edges by const reference; edges() does not copy its payload. |
| invariants | Child slots preserve arbitrary fanout ordering and are not binary-tree positions. Constant routes expose an empty instruction collection even when query().atoms is nonempty. |
| ownership | The edge array borrows Data. A copied PhysicalEdge owns its projection control plus scalar coordinates and can outlive that array. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0100

[Lines 562–562](../../../../../src/ir/program.cpp#L562); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Span<program::Span<OccurrenceId>>& CompiledProgram::base_routes() const &
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the source-table to occurrence fanout arrays. |
| inputs / outputs | Returns Data.base_routes by const reference; base_routes() does not copy its payload. |
| invariants | On tree routes these arrays map each physical source table to its routed logical occurrences. Constant routes retain empty route entries even when the original contradiction-marked Query has atoms; this is not a live subscription list. |
| ownership | Both the outer route array and inner occurrence spans borrow Data. Copying either span/header acquires no program/source ownership. |
| failure | Empty/default/moved-from handle throws IndexFailure(invalid_storage). |
| cost | Checked Data/member lookup only; any later traversal, descriptor copy or final owner teardown has its own cost. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0101

[Lines 563–563](../../../../../src/ir/program.cpp#L563); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t CompiledProgram::work() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read retained physical-lowering logical work for this artifact. |
| inputs / outputs | Returns Data.work; admission copies source.work(), while native replan counts its own charge() checkpoints. |
| invariants | Counter excludes reused identity/replay/normalization credits, internal IndexWorkAllowance units and unmetered per-byte/map/allocator work; it is not elapsed time. |
| ownership | Scalar result has independent lifetime. |
| failure | Empty handle throws invalid_storage. |
| cost | Checked scalar lookup. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0102

[Lines 564–564](../../../../../src/ir/program.cpp#L564); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedPlanStorage CompiledProgram::make_storage(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize empty mutable native relation tables and required indexes from immutable binding. |
| inputs / outputs | Optional existing execution allowance; returns AccountedPlanStorage(binding,work). |
| invariants | Shares canonical layout/projection metadata and account while creating a distinct mutable storage owner; no input tuples or runtime operators are populated here. |
| ownership | New table/index arrays and underlying native controls are funded by binding account; returned storage owns them independently of program handle. |
| failure | Empty program, owner exhaustion, indexed grant-contract/work limits or memory/storage faults unwind partial storage. |
| cost | Visits relations and index requirements, allocates table/index storage and registers projections; descriptor width/derived index initialization costs are delegated, not a simple handle copy. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0103

[Lines 565–571](../../../../../src/ir/program.cpp#L565); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram runtime::detail::SqlColdRebuild::freeze(const resource::MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route only the closed cold bridge through the existing CompiledProgram builder. |
| inputs / outputs | Genuine PhysicalPlan plus receiver/work -&gt; freeze_impl, with compiler MetadataWork only when the authentic plan has indexed storage. |
| invariants | This cannot fabricate CompiledProgram::Data or rewrite plan limits; ordered storage uses the prior execution metadata mode. |
| ownership | Returned CompiledProgram owns copied receiving metadata. |
| failure | Mode-specific binding/work/allocation faults propagate before owner publication. |
| cost | No second compiler implementation; selected storage metadata admission is part of the one cold indexed lease when indexed. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/runtime/sql_cold_rebuild.hpp](../../../../../src/runtime/sql_cold_rebuild.hpp), [build/verification/w06-sql-aggregate-cold-rebuild-design-v1/design.md §The two actual indexed admission seams](../../../../../build/verification/w06-sql-aggregate-cold-rebuild-design-v1/design.md) |

## B0104

[Lines 572–576](../../../../../src/ir/program.cpp#L572); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedPlanStorage runtime::detail::SqlColdRebuild::storage(const CompiledProgram& source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize actual storage from the genuine compiled program binding through the private tag. |
| inputs / outputs | A real \`CompiledProgram\` and the active cold work root yield AccountedPlanStorage using ColdRebuild. |
| invariants | The bridge reads the existing binding; it does not synthesize relation/index descriptors or change backend, per-table or identity settings. |
| ownership | Result owns new empty table/index structures while sharing immutable binding metadata. |
| failure | Materialization errors abort unpublished storage; grant is borrowed for construction. |
| cost | Charges actual native table/index materialization against the active cold work balance. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/storage/accounted_plan.cpp](../../../../../src/storage/accounted_plan.cpp), [docs/memory_accounts.md §Accounted compiled-plan storage binding](../../../../memory_accounts.md) |

## B0105

[Lines 577–582](../../../../../src/ir/program.cpp#L577); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using NativeSqlValue=program::SqlValue;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name nullable native expression slots and reuse the private scalar helpers in compiled input adaptation. |
| inputs / outputs | NativeSqlValue remains optional&lt;ScalarView&gt;; using declarations import admit_value and truth from the shared private evaluator. |
| invariants | The aliases add no SQL AST, owning DTO mirror or new nullable/core admission. Old normalization and physical source checks still govern adapt_input. |
| ownership | Scratch vector owns only its slot array. Scalar string views borrow caller/program payload during the synchronous call; final projection copies any retained tuple bytes. |
| failure | Alias declarations add no failure boundary; the imported helpers propagate their existing allowance and fixed contract failures. |
| cost | No runtime setup, grant, allocation or dispatch object is introduced by the using declarations; slot and comparison costs remain with their actual helpers. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0106

[Lines 583–629](../../../../../src/ir/program.cpp#L583); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L583-L629:sha256:6bb5f0d4f7d13dc7ac0f40f24227c896a4096e66beb6132450cd61e2ff613e0e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt a physical occurrence using either interpreter or admitted prebound workers with identical SQL semantics. |
| inputs / outputs | OccurrenceId, borrowed physical RowView and optional existing IndexWork allowance; accepted projected AccountedTuple or rejection/nullopt. |
| invariants | Physical validation, scalar admission, constants/equalities, predicate truth, projection and physical CP input checks retain their previous order. Only expression-node decoding changes. Threaded instruction execution admits the same structural/scalar work and calls unchanged sql_scalar; NULL/unsupported projection semantics stay shared. |
| ownership | Scratch values/logical projection use program account. Prepared argument spans require Data lifetime; returned tuple owns its projection storage. Caller row and grant stay borrowed. |
| failure | Existing tuple validation, contract, scalar/domain, work, overflow and account faults propagate before publication; no caller tuple escapes partial adaptation. Rejected predicate returns no tuple. |
| cost | Same physical/scalar/project work plus one optional prepared-owner branch. Prepared path iterates flat per-port instructions; interpreter decodes each bound expression. Neither adds runtime clocks/cache lookups. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0107

[Lines 630–632](../../../../../src/ir/program.cpp#L630); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L630-L632:sha256:4df05081f07596848fdcc103b78c8e1d952040881b2e2aeae1eac7f0968d6a34
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes crown and opens crown::program for JsonView accessors implemented after the core CompiledProgram code. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/code_specs/files/src/ir/program.cpp.md](program.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0108

[Lines 633–633](../../../../../src/ir/program.cpp#L633); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
JsonKind JsonView::kind() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the native JSON variant tag, treating an empty view as null. |
| inputs / outputs | Returns JsonKind equal to JsonNode variant index, or null for node_==nullptr. |
| invariants | JsonKind ordering must match JsonNode alternatives exactly. |
| ownership | Reading a nonempty JsonView requires a surviving backing Data owner; the returned tag/count/scalar is a value and can outlive it. The input JsonView itself owns no control. |
| failure | Noexcept; a nonnull pointer must refer to a live arena node. |
| cost | Fixed pointer/tag read. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0109

[Lines 634–638](../../../../../src/ir/program.cpp#L634); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::size_t JsonView::size() const noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read child count or scalar/null cardinality for a borrowed JSON value. |
| inputs / outputs | Array/object returns span length; null returns zero; other scalars return one. |
| invariants | String size here is one scalar, not its byte length. |
| ownership | Reading a nonempty JsonView requires a surviving backing Data owner; the returned tag/count/scalar is a value and can outlive it. The input JsonView itself owns no control. |
| failure | Noexcept under a valid live view and synchronized variant/kind tags. |
| cost | Fixed tag tests and stored-length read; does not traverse children/text. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0110

[Lines 639–639](../../../../../src/ir/program.cpp#L639); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
JsonView JsonView::at(std::size_t i) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one array child by position. |
| inputs / outputs | Requires array and returns JsonView pointing to its i-th arena node. |
| invariants | No object lookup or implicit scalar-to-array conversion. |
| ownership | Input and returned child JsonView borrow the same arena and own no control; a backing Data owner must survive child use. |
| failure | Wrong kind or out-of-range index throws IndexFailure(contract). |
| cost | Fixed kind check and bounded indexed access. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0111

[Lines 640–640](../../../../../src/ir/program.cpp#L640); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view JsonView::key(std::size_t i) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an ordered object member key by position. |
| inputs / outputs | Requires object and returns its i-th member key view. |
| invariants | Does not search, normalize or copy key bytes. |
| ownership | Returned string_view borrows arena bytes and has no owner; a Data owner must survive every byte access, even after copying this JsonView/string_view. |
| failure | Wrong kind or invalid member position throws IndexFailure(contract). |
| cost | Fixed kind/index lookup, independent of key byte length. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0112

[Lines 641–641](../../../../../src/ir/program.cpp#L641); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
JsonView JsonView::member(std::size_t i) const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow an ordered object member value by position. |
| inputs / outputs | Requires object and returns JsonView pointing into its i-th embedded value. |
| invariants | Object order is preserved by native admission; no key-based map lookup occurs. |
| ownership | Input and returned child JsonView borrow the same arena and own no control; a backing Data owner must survive child use. |
| failure | Wrong kind or invalid position throws IndexFailure(contract). |
| cost | Fixed kind/index/pointer lookup. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0113

[Lines 642–642](../../../../../src/ir/program.cpp#L642); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool JsonView::boolean() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an exact native JSON boolean. |
| inputs / outputs | Requires JsonKind::boolean and returns stored bool. |
| invariants | Null/numeric/string values do not coerce to bool. |
| ownership | Reading a nonempty JsonView requires a surviving backing Data owner; the returned tag/count/scalar is a value and can outlive it. The input JsonView itself owns no control. |
| failure | Wrong kind throws IndexFailure(contract). |
| cost | Fixed kind check and scalar extraction. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0114

[Lines 643–643](../../../../../src/ir/program.cpp#L643); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::int64_t JsonView::integer() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the exact signed JSON integer alternative. |
| inputs / outputs | Requires JsonKind::integer and returns int64. |
| invariants | Unsigned and floating alternatives are distinct and do not coerce. |
| ownership | Reading a nonempty JsonView requires a surviving backing Data owner; the returned tag/count/scalar is a value and can outlive it. The input JsonView itself owns no control. |
| failure | Wrong kind throws IndexFailure(contract). |
| cost | Fixed tag check and scalar extraction. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0115

[Lines 644–644](../../../../../src/ir/program.cpp#L644); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t JsonView::unsigned_integer() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the exact unsigned JSON integer alternative. |
| inputs / outputs | Requires JsonKind::unsigned_integer and returns uint64. |
| invariants | Signed storage is not accepted even for nonnegative values. |
| ownership | Reading a nonempty JsonView requires a surviving backing Data owner; the returned tag/count/scalar is a value and can outlive it. The input JsonView itself owns no control. |
| failure | Wrong kind throws IndexFailure(contract). |
| cost | Fixed tag check and scalar extraction. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0116

[Lines 645–645](../../../../../src/ir/program.cpp#L645); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
double JsonView::number() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the exact floating JSON number alternative. |
| inputs / outputs | Requires JsonKind::number and returns double. |
| invariants | Integer alternatives do not convert to floating-point on read. |
| ownership | Reading a nonempty JsonView requires a surviving backing Data owner; the returned tag/count/scalar is a value and can outlive it. The input JsonView itself owns no control. |
| failure | Wrong kind throws IndexFailure(contract). |
| cost | Fixed tag check and scalar extraction. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0117

[Lines 646–646](../../../../../src/ir/program.cpp#L646); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view JsonView::text() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow exact string bytes from a native JSON scalar. |
| inputs / outputs | Requires JsonKind::string and returns its string_view. |
| invariants | No formatting of other JSON scalar kinds or null is performed. |
| ownership | Returned string_view borrows arena bytes and has no owner; a Data owner must survive every byte access, even after copying this JsonView/string_view. |
| failure | Wrong kind throws IndexFailure(contract). |
| cost | Fixed tag/view read; later byte traversal is caller work. |
| Design | [docs/physical_plans.md §Identity and versioned artifacts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0118

[Lines 647–647](../../../../../src/ir/program.cpp#L647); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L647-L647:sha256:774e0e57e452387e8b836521923bfa4cdc6e11df831614d813437c520633a71a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::program at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/ir/program.cpp](../../../../../src/ir/program.cpp), [docs/code_specs/files/src/ir/program.cpp.md](program.cpp.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |
