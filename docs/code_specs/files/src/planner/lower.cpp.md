# `src/planner/lower.cpp` — block usage map

[Source](../../../../../src/planner/lower.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `d7df5bd54a5beea9a85f381700316d486ba2675e96a56c935a6443191d971bac`. 418 lines partitioned into 71 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../src/planner/lower.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // nlohmann's ordinary object/array destructor allocates a flattening stack. · [reviewed contract](#b0001) |
| [B0002 · 20–27](../../../../../src/planner/lower.cpp#L20) | Callable definition: void clear_identity_without_allocation(io::Json& root) noexcept | calls is_structured, empty, begin, erase; 2 loop sites; source comment (unverified): // nlohmann's ordinary object/array destructor allocates a flattening stack. · [reviewed contract](#b0002) |
| [B0003 · 28–56](../../../../../src/planner/lower.cpp#L28) | declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace · [reviewed contract](#b0003) |
| [B0004 · 57–62](../../../../../src/planner/lower.cpp#L57) | Callable definition: void prepare_identity_cleanup() | calls is_structured, push_back, size; growth push_back; 2 loop sites; source comment (unverified): // One-shot after identity reaches its final address. Freeze that JSON · [reviewed contract](#b0004) |
| [B0005 · 63–69](../../../../../src/planner/lower.cpp#L63) | Callable definition: ~Data() | calls rbegin, rend, clear, clear_identity_without_allocation; 1 loop sites; source comment (unverified): // Parent containers remain valid until all descendants have been cleared. · [reviewed contract](#b0005) |
| [B0006 · 70–71](../../../../../src/planner/lower.cpp#L70) | declares namespace scope. |  · [reviewed contract](#b0006) |
| [B0007 · 72–74](../../../../../src/planner/lower.cpp#L72) | Callable definition: void require(bool condition, std::string_view code, std::string_view message) | calls Error, std::string; guard void require(bool condition, std::string_view code, std::string_view message) { · [reviewed contract](#b0007) |
| [B0008 · 75–77](../../../../../src/planner/lower.cpp#L75) | Callable definition: std::optional&lt;std::uint64_t&gt; capped(std::optional&lt;std::uint64_t&gt; producer, std::optional&lt;std::uint64_t&gt; host) | calls ; returns host && (!producer \|\| *host &lt; *producer) ? host : producer · [reviewed contract](#b0008) |
| [B0009 · 78–79](../../../../../src/planner/lower.cpp#L78) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 80–80](../../../../../src/planner/lower.cpp#L80) | Callable definition: PhysicalPlan::PhysicalPlan(std::shared_ptr&lt;const Data&gt; data) : data_(std::move(data)) | calls data_, std::move · [reviewed contract](#b0010) |
| [B0011 · 81–82](../../../../../src/planner/lower.cpp#L81) | Explanatory comments or spacing. | source comment (unverified): // Explicit caller export, not native internal replanning. Copy ordinary · [reviewed contract](#b0011) |
| [B0012 · 83–109](../../../../../src/planner/lower.cpp#L83) | Callable definition: PhysicalPlan PhysicalPlan::from_compiled(const CompiledProgram& source) | calls planner::compiler_source_detail::export_program, std::move, prepare_identity_cleanup, PhysicalPlan; returns PhysicalPlan(std::move(result)); growth make_shared; source comment (unverified): // Explicit caller export, not native internal replanning. Copy ordinary · [reviewed contract](#b0012) |
| [B0013 · 110–112](../../../../../src/planner/lower.cpp#L110) | Callable definition: const PhysicalPlan::Data& PhysicalPlan::data() const | calls require, bool; guard require(bool(data_), "invalid_physical_plan", "moved-from physical plan"); return *data_;; returns *data_ · [reviewed contract](#b0013) |
| [B0014 · 113–113](../../../../../src/planner/lower.cpp#L113) | Callable definition: PhysicalRoute PhysicalPlan::route() const | calls data; returns data().route · [reviewed contract](#b0014) |
| [B0015 · 114–114](../../../../../src/planner/lower.cpp#L114) | Callable definition: const Catalog& PhysicalPlan::catalog() const | calls data; returns data().catalog · [reviewed contract](#b0015) |
| [B0016 · 115–115](../../../../../src/planner/lower.cpp#L115) | Callable definition: const Catalog& PhysicalPlan::source_catalog() const | calls data; returns d.normalized ? d.normalized-&gt;binding.catalog : d.catalog · [reviewed contract](#b0016) |
| [B0017 · 116–116](../../../../../src/planner/lower.cpp#L116) | Callable definition: const Query& PhysicalPlan::query() const | calls data; returns data().query · [reviewed contract](#b0017) |
| [B0018 · 117–117](../../../../../src/planner/lower.cpp#L117) | Callable definition: const FreeConnexTree& PhysicalPlan::tree() const | calls data; returns data().tree · [reviewed contract](#b0018) |
| [B0019 · 118–118](../../../../../src/planner/lower.cpp#L118) | Callable definition: const std::optional&lt;frontend::NormalizedSql&gt;& PhysicalPlan::normalized() const | calls data; returns data().normalized · [reviewed contract](#b0019) |
| [B0020 · 119–119](../../../../../src/planner/lower.cpp#L119) | Callable definition: const planner::ValidationReport& PhysicalPlan::validation() const | calls data; returns data().validation · [reviewed contract](#b0020) |
| [B0021 · 120–120](../../../../../src/planner/lower.cpp#L120) | Callable definition: const io::QueryIdentity& PhysicalPlan::identity() const | calls data; returns data().identity · [reviewed contract](#b0021) |
| [B0022 · 121–121](../../../../../src/planner/lower.cpp#L121) | Callable definition: const std::string& PhysicalPlan::physical_sha256() const | calls data; returns data().physical_sha256 · [reviewed contract](#b0022) |
| [B0023 · 122–122](../../../../../src/planner/lower.cpp#L122) | Callable definition: std::string_view PhysicalPlan::physical_source_sha256() const | calls data, size; returns {value.data(),value.size()} · [reviewed contract](#b0023) |
| [B0024 · 123–123](../../../../../src/planner/lower.cpp#L123) | Callable definition: const PhysicalOptions& PhysicalPlan::options() const | calls data; returns data().options · [reviewed contract](#b0024) |
| [B0025 · 124–124](../../../../../src/planner/lower.cpp#L124) | Callable definition: const GuaranteeProfile& PhysicalPlan::guarantee() const | calls data; returns data().guarantee · [reviewed contract](#b0025) |
| [B0026 · 125–125](../../../../../src/planner/lower.cpp#L125) | Callable definition: const std::vector&lt;storage::TupleLayout&gt;& PhysicalPlan::layouts() const | calls data; returns data().layouts · [reviewed contract](#b0026) |
| [B0027 · 126–126](../../../../../src/planner/lower.cpp#L126) | Callable definition: const std::vector&lt;PhysicalRelation&gt;& PhysicalPlan::relations() const | calls data; returns data().relations · [reviewed contract](#b0027) |
| [B0028 · 127–127](../../../../../src/planner/lower.cpp#L127) | Callable definition: const std::vector&lt;IndexRequirement&gt;& PhysicalPlan::indexes() const | calls data; returns data().indexes · [reviewed contract](#b0028) |
| [B0029 · 128–128](../../../../../src/planner/lower.cpp#L128) | Callable definition: const std::vector&lt;PhysicalInput&gt;& PhysicalPlan::inputs() const | calls data; returns data().inputs · [reviewed contract](#b0029) |
| [B0030 · 129–129](../../../../../src/planner/lower.cpp#L129) | Callable definition: const std::vector&lt;std::vector&lt;OccurrenceId&gt;&gt;& PhysicalPlan::base_routes() const | calls data; returns data().base_routes · [reviewed contract](#b0030) |
| [B0031 · 130–130](../../../../../src/planner/lower.cpp#L130) | Callable definition: const std::vector&lt;PhysicalNode&gt;& PhysicalPlan::nodes() const | calls data; returns data().nodes · [reviewed contract](#b0031) |
| [B0032 · 131–131](../../../../../src/planner/lower.cpp#L131) | Callable definition: const std::vector&lt;PhysicalEdge&gt;& PhysicalPlan::edges() const | calls data; returns data().edges · [reviewed contract](#b0032) |
| [B0033 · 132–132](../../../../../src/planner/lower.cpp#L132) | Callable definition: const EnumerationProgram& PhysicalPlan::enumeration() const | calls data; returns data().enumeration · [reviewed contract](#b0033) |
| [B0034 · 133–133](../../../../../src/planner/lower.cpp#L133) | Callable definition: const storage::TupleLayout& PhysicalPlan::result_layout() const | calls data; returns *data().result_layout · [reviewed contract](#b0034) |
| [B0035 · 134–134](../../../../../src/planner/lower.cpp#L134) | Callable definition: std::uint64_t PhysicalPlan::work() const | calls data; returns data().work · [reviewed contract](#b0035) |
| [B0036 · 135–138](../../../../../src/planner/lower.cpp#L135) | Explanatory comments or spacing. | source comment (unverified): // Run the retained SQL/local CQ adapter for one occurrence. This produces · [reviewed contract](#b0036) |
| [B0037 · 139–154](../../../../../src/planner/lower.cpp#L139) | Callable definition: std::optional&lt;storage::Tuple&gt; PhysicalPlan::adapt_input(OccurrenceId occurrence, const Row& row) const | calls data, require, size, frontend::adapt_row; guard require(occurrence.value&lt;d.inputs.size(), "invalid_input_port", "physical plan has no such native o…; returns {}; {}; 2 loop sites; source comment (unverified): // Run the retained SQL/local CQ adapter for one occurrence. This produces · [reviewed contract](#b0037) |
| [B0038 · 155–156](../../../../../src/planner/lower.cpp#L155) | Explanatory comments or spacing. | source comment (unverified): // Check compiled tokens and shared-variable equalities. The caller owns · [reviewed contract](#b0038) |
| [B0039 · 157–171](../../../../../src/planner/lower.cpp#L157) | Callable definition: storage::Tuple PhysicalPlan::assemble_result(std::span&lt;const storage::Tuple&gt; assignments) const | calls data, require, size, same_token; guard require(d.route!=PhysicalRoute::constant_false, "empty_plan", "constant-false operator has no resul…; returns assignments\[slot.step\].values()\[slot.field.value\]; d.result_layout-&gt;tuple(std::move(result)); growth push_back, reserve; 3 loop sites; source comment (unverified): // Check compiled tokens and shared-variable equalities. The caller owns · [reviewed contract](#b0039) |
| [B0040 · 172–176](../../../../../src/planner/lower.cpp#L172) | declares namespace scope; declares types or opens a type body. | source comment (unverified): // Fallible private build, followed by one immutable publication. Errors · [reviewed contract](#b0040) |
| [B0041 · 177–185](../../../../../src/planner/lower.cpp#L177) | Callable definition: public: static PhysicalPlan run(Catalog catalog, Query query, FreeConnexTree tree, std::optional&lt;frontend::NormalizedSql&gt; normali… | calls builder, std::move, compile, PhysicalPlan; returns PhysicalPlan(std::move(builder.d_)) · [reviewed contract](#b0041) |
| [B0042 · 186–191](../../../../../src/planner/lower.cpp#L186) | declares callable signatures; declares values/defaults or compile-time conditions. | growth make_shared · [reviewed contract](#b0042) |
| [B0043 · 192–204](../../../../../src/planner/lower.cpp#L192) | Callable definition: Lowering(const PhysicalOptions& options,const std::optional&lt;PhysicalLimits&gt;& host) : limits_(options.limits) | calls limits_, capped · [reviewed contract](#b0043) |
| [B0044 · 205–206](../../../../../src/planner/lower.cpp#L205) | Explanatory comments or spacing. | source comment (unverified): // Selected construction checkpoints only. Copies, P02, JSON/hash work, · [reviewed contract](#b0044) |
| [B0045 · 207–211](../../../../../src/planner/lower.cpp#L207) | Callable definition: void charge() | calls max, Error; source comment (unverified): // Selected construction checkpoints only. Copies, P02, JSON/hash work, · [reviewed contract](#b0045) |
| [B0046 · 212–212](../../../../../src/planner/lower.cpp#L212) | Callable definition: const Catalog& source_catalog() const | calls ; returns d_-&gt;normalized ? d_-&gt;normalized-&gt;binding.catalog : d_-&gt;catalog · [reviewed contract](#b0046) |
| [B0047 · 213–213](../../../../../src/planner/lower.cpp#L213) | Callable definition: storage::LayoutContext context() const | calls ; returns {d_-&gt;catalog.version,d_-&gt;physical_sha256} · [reviewed contract](#b0047) |
| [B0048 · 214–215](../../../../../src/planner/lower.cpp#L214) | Explanatory comments or spacing. | source comment (unverified): // Ordered vector identity preserves repeated/output fields. A set key · [reviewed contract](#b0048) |
| [B0049 · 216–221](../../../../../src/planner/lower.cpp#L216) | Callable definition: storage::TupleLayout scope(const std::vector&lt;VariableId&gt;& variables) | calls charge, find, end, storage::scope_layout; returns found-&gt;second; layout; growth emplace, push_back; 1 loop sites; source comment (unverified): // Ordered vector identity preserves repeated/output fields. A set key · [reviewed contract](#b0049) |
| [B0050 · 222–223](../../../../../src/planner/lower.cpp#L222) | Explanatory comments or spacing. | source comment (unverified): // Physical and core table IDs use different catalog domains under SQL. · [reviewed contract](#b0050) |
| [B0051 · 224–230](../../../../../src/planner/lower.cpp#L224) | Callable definition: storage::TupleLayout table_layout(TableId table,bool physical) | calls charge, find, end, source_catalog; returns found-&gt;second; layout; growth emplace, push_back; source comment (unverified): // Physical and core table IDs use different catalog domains under SQL. · [reviewed contract](#b0051) |
| [B0052 · 231–243](../../../../../src/planner/lower.cpp#L231) | Callable definition: storage::Projection project(const storage::TupleLayout& source,const std::vector&lt;VariableId&gt;& variables) | calls charge, fields, size, emplace; guard require(found!=positions.end(),"lowering_contract","projection variable is outside its source layou…; returns {source,scope(variables),std::move(fields)}; growth emplace, push_back; 2 loop sites · [reviewed contract](#b0052) |
| [B0053 · 244–246](../../../../../src/planner/lower.cpp#L244) | Callable definition: RelationId relation(RelationRole role,const storage::TupleLayout& layout,std::optional&lt;NodeId&gt; node={},std::optional&lt;TableId&gt; bas… | calls charge, size, push_back; returns id; growth push_back · [reviewed contract](#b0053) |
| [B0054 · 247–248](../../../../../src/planner/lower.cpp#L247) | Explanatory comments or spacing. | source comment (unverified): // Reuse requires the same relation, ordered fields and target token. · [reviewed contract](#b0054) |
| [B0055 · 249–259](../../../../../src/planner/lower.cpp#L249) | Callable definition: IndexRequirementId index(RelationId relation,storage::Projection projection,IndexUse use) | calls charge, std::make_pair, fields, begin; guard require(existing.projection.target().same_token(projection.target()),"lowering_contract","shared in…; returns found-&gt;second; id; growth emplace, push_back; source comment (unverified): // Reuse requires the same relation, ordered fields and target token. · [reviewed contract](#b0055) |
| [B0056 · 260–261](../../../../../src/planner/lower.cpp#L260) | Explanatory comments or spacing. | source comment (unverified): // Coarse dimension charges before semantic validation; these loops do · [reviewed contract](#b0056) |
| [B0057 · 262–272](../../../../../src/planner/lower.cpp#L262) | Callable definition: void preflight() | calls charge, source_catalog; 9 loop sites; source comment (unverified): // Coarse dimension charges before semantic validation; these loops do · [reviewed contract](#b0057) |
| [B0058 · 273–308](../../../../../src/planner/lower.cpp#L273) | Callable definition: void compile() | calls preflight, validate, require, empty; guard require(!d_-&gt;tree.root && d_-&gt;tree.nodes.empty() && (!d_-&gt;tree.claimed_connex \|\| d_-&gt;tree.claimed_c…; growth push_back, resize; 1 loop sites; source comment (unverified): // Canonical constant operator, not a tree certificate for the retained · [reviewed contract](#b0058) |
| [B0059 · 309–310](../../../../../src/planner/lower.cpp#L309) | Explanatory comments or spacing. | source comment (unverified): // Scope may contain hidden root variables. Only P02 connex members get · [reviewed contract](#b0059) |
| [B0060 · 311–339](../../../../../src/planner/lower.cpp#L311) | Callable definition: void compile_nodes() | calls size, charge, insert, relation; growth insert, push_back; 7 loop sites; source comment (unverified): // Scope may contain hidden root variables. Only P02 connex members get · [reviewed contract](#b0060) |
| [B0061 · 340–341](../../../../../src/planner/lower.cpp#L340) | Explanatory comments or spacing. | source comment (unverified): // Preserve independent native occurrences even when aliases share a base. · [reviewed contract](#b0061) |
| [B0062 · 342–362](../../../../../src/planner/lower.cpp#L342) | Callable definition: void compile_inputs() | calls nodes, size, charge, table_layout; growth emplace, push_back; 4 loop sites; source comment (unverified): // Preserve independent native occurrences even when aliases share a base. · [reviewed contract](#b0062) |
| [B0063 · 363–364](../../../../../src/planner/lower.cpp#L363) | Explanatory comments or spacing. | source comment (unverified): // Both endpoints share an exact separator token. Guard makes a · [reviewed contract](#b0063) |
| [B0064 · 365–377](../../../../../src/planner/lower.cpp#L365) | Callable definition: void compile_edges() | calls size, charge, target, fields; guard require(key.target().same_token(child.parent_key.target()),"lowering_contract","edge endpoints do n…; growth push_back; 3 loop sites; source comment (unverified): // Both endpoints share an exact separator token. Guard makes a · [reviewed contract](#b0064) |
| [B0065 · 378–379](../../../../../src/planner/lower.cpp#L378) | Explanatory comments or spacing. | source comment (unverified): // P02 supplies root-connected parent-before-child C* order and output · [reviewed contract](#b0065) |
| [B0066 · 380–402](../../../../../src/planner/lower.cpp#L380) | Callable definition: void compile_enumeration() | calls positions, size, charge, target; guard require(step.parent_key-&gt;target().same_token(node.parent_key.target()),"lowering_contract","enumera…; growth emplace, push_back; 3 loop sites; source comment (unverified): // P02 supplies root-connected parent-before-child C* order and output · [reviewed contract](#b0066) |
| [B0067 · 403–404](../../../../../src/planner/lower.cpp#L403) | Closes surrounding scope/type. |  · [reviewed contract](#b0067) |
| [B0068 · 405–407](../../../../../src/planner/lower.cpp#L405) | Callable definition: PhysicalPlan lower_tree(const Catalog& catalog,const Query& query,const FreeConnexTree& tree,const PhysicalOptions& options,const… | calls Lowering::run; returns Lowering::run(catalog,query,tree,{},options,host) · [reviewed contract](#b0068) |
| [B0069 · 408–409](../../../../../src/planner/lower.cpp#L408) | Explanatory comments or spacing. | source comment (unverified): // Replay the entire artifact and ground v1 before reading its core. · [reviewed contract](#b0069) |
| [B0070 · 410–416](../../../../../src/planner/lower.cpp#L410) | Callable definition: PhysicalPlan lower_normalized(const frontend::NormalizedSql& program,const FreeConnexTree& tree,const PhysicalOptions& options, c… | calls io::read_sql_normalization, io::write_sql_normalization, dump, io::upgrade_sql_normalization; returns Lowering::run(std::move(catalog),std::move(query),tree,std::move(owned),options,host); source comment (unverified): // Replay the entire artifact and ground v1 before reading its core. · [reviewed contract](#b0070) |
| [B0071 · 417–418](../../../../../src/planner/lower.cpp#L417) | Closes surrounding scope/type. | source comment (unverified): // namespace planner · [reviewed contract](#b0071) |

## B0001

[Lines 1–19](../../../../../src/planner/lower.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:df0cf7d6bf43105f2dfc8090dee2c329335010713dd73763ca5ed51e39dc215b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | make #include "crown/planner/lower.hpp", #include "crown/api/error.hpp", #include "crown/io/tree.hpp", #include "crown/io/physical.hpp", #include "crown/ir/digest.hpp", #include "compiled_source.hpp", #include &lt;algorithm&gt;, #include &lt;limits&gt;, #include &lt;map&gt;, #include &lt;utility&gt; available to src/planner/lower.cpp; open crown and anonymous helper namespace. Attached note: nlohmann's ordinary object/array destructor allocates a flattening stack. A plan can lose its final owner in noexcept cursor/output cleanup. Remove leaves without a stack if preparation of its fast teardown inventory failed. Slow construction-failure fallback: repeated descent/first-child erase may be quadratic, but needs neither heap scratch nor recursion. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0002

[Lines 20–27](../../../../../src/planner/lower.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void clear_identity_without_allocation(io::Json& root) noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Empty the compiler identity JSON if its fast teardown inventory was never completed. |
| inputs / outputs | Mutable root is pruned from its first leaf until no structured children remain, then cleared. |
| invariants | Each erased value is scalar or an empty container, so its destructor needs no flattening allocation. This is teardown, not semantic identity traversal. |
| ownership | Mutates only the owned canonical JSON; retains no pointer after return. |
| failure | Noexcept. Assumes the concrete default map/vector JSON type and a valid owned value; does not allocate diagnostics or a traversal stack. |
| cost | No extra heap/recursive stack. Repeated descent and first-array-element erasure can be quadratic in JSON nodes/depth; scalar payload deallocation is additional. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [third_party/nlohmann/README.crown.md](../../../../../third_party/nlohmann/README.crown.md), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0003

[Lines 28–56](../../../../../src/planner/lower.cpp#L28); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct PhysicalPlan::Data {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the immutable public physical-plan artifact and its teardown preparation. |
| inputs / outputs | Catalog/query/tree, optional normalized source, checked-upper or constant-operator report, identities/options/guarantee, layouts/wiring/enumeration, result layout and construction count. |
| invariants | Only factories populate mutable Data before publication as shared const. Result layout is always set. Identity cleanup pointers refer to the final unchanged canonical JSON graph. |
| ownership | Owns ordinary containers/JSON and shared layout/projection descriptor handles. A from_compiled export can share account-backed descriptor metadata without retaining the entire CompiledProgram. |
| failure | Unpublished partial state is destroyed on failure; destructor uses prepared reverse cleanup or the allocation-free fallback. |
| cost | Full compiler DTO/source/graph storage plus one pointer per structured identity value; this public artifact has no allocator-byte quota. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/storage/descriptor.hpp](../../../../../src/storage/descriptor.hpp) |

## B0004

[Lines 57–62](../../../../../src/planner/lower.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void prepare_identity_cleanup() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare descendant-before-parent identity JSON destruction during fallible construction. |
| inputs / outputs | Breadth-first append structured root/children to the pointer vector; mark ready only after the complete traversal succeeds. |
| invariants | Call once after canonical identity reaches its final address and before publication. JSON containers remain unchanged afterwards; vector growth does not move the referenced JSON values. |
| ownership | Owns an auxiliary vector of borrows into this same Data identity. Its entries are never exported. |
| failure | Vector allocation may throw. ready remains false, so Data destruction ignores any partial pointer inventory and uses the fallback. |
| cost | O(JSON values) visits and O(structured values) pointers with amortized vector growth; no lowering charge per JSON value. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0005

[Lines 63–69](../../../../../src/planner/lower.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  ~Data() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Destroy the identity without new allocation when a plan loses its final shared owner. |
| inputs / outputs | If inventory ready, clear its pointers in reverse breadth-first order; otherwise prune root without a stack. |
| invariants | All descendants are empty before a parent clears their storage; no stale pointer is dereferenced after its parent clears. Member teardown then sees empty identity containers. |
| ownership | Releases Data-owned DTOs and descriptor handles; shared external descriptors/tuples may retain their own metadata. |
| failure | Implicitly noexcept; no catches or allocating diagnostics. Prepared inventory is trusted only after ready. |
| cost | Prepared path is linear in identity graph/payload plus ordinary member cleanup. Fallback may be quadratic; final-owner release can occur outside work grants. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [third_party/nlohmann/json.hpp](../../../../../third_party/nlohmann/json.hpp) |

## B0006

[Lines 70–71](../../../../../src/planner/lower.cpp#L70); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L71:sha256:16f0e7aad7b0582c74ac9da9ab922e083115eee8c6aa8498670e4330c85e4d60
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | close the surrounding helper scope and open anonymous helper namespace in src/planner/lower.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0007

[Lines 72–74](../../../../../src/planner/lower.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void require(bool condition, std::string_view code, std::string_view message) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a public typed lowering/adapter diagnostic only on a failed predicate. |
| inputs / outputs | Successful condition returns; failure constructs Error from copied code/message. |
| invariants | Does not perform validation beyond the supplied predicate and never substitutes a boolean/report for actual factory admission. |
| ownership | Borrows diagnostic text during call; Error owns copies on failure. |
| failure | Error or its allocation failure propagates to the caller. |
| cost | Constant success path; failed-path strings may allocate and scale with diagnostic length. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0008

[Lines 75–77](../../../../../src/planner/lower.cpp#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<std::uint64_t> capped(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intersect producer and optional host ceilings without granting extra work. |
| inputs / outputs | Return the smaller finite optional ceiling, or producer when host is absent/non-stricter. |
| invariants | nullopt means unlimited. A finite host always caps an unlimited producer; zero remains a real zero ceiling. |
| ownership | Copies fixed optional integers only. |
| failure | No allocation or throw with these value types. |
| cost | Constant comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0009

[Lines 78–79](../../../../../src/planner/lower.cpp#L78); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L78-L79:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the lexical scope identified by the source span. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0010

[Lines 80–80](../../../../../src/planner/lower.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan::PhysicalPlan(std::shared_ptr<const Data> data)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adopt private prepared immutable Data into a public plan handle. |
| inputs / outputs | Moves the supplied shared owner into data_. |
| invariants | Caller factory has completed admission/construction; constructor does not validate or grant new authority. |
| ownership | Shared const Data ownership; no graph copy. |
| failure | Shared-pointer move is nonallocating; no local error handling. |
| cost | Constant owner transfer. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0011

[Lines 81–82](../../../../../src/planner/lower.cpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L82:sha256:23b9d434a5b1ff9f716c0b77dad1fedfcf5f88e52dd808e7d350c0d3e0c36b9d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for PhysicalPlan: Explicit caller export, not native internal replanning. Copy ordinary payload, share descriptor metadata, then prepare nonallocating teardown. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies PhysicalPlan; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for PhysicalPlan come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0012

[Lines 83–109](../../../../../src/planner/lower.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan PhysicalPlan::from_compiled(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export an immutable native compiled artifact as a caller-owned public PhysicalPlan. |
| inputs / outputs | Copy ProgramExport, move ordinary fields into a new Data, prepare its identity teardown inventory, then return shared const plan. |
| invariants | Does not relower/revalidate or create a new proof. Existing digests/work/guarantees are copied; native internal candidate lowering uses CompiledProgram::replan. |
| ownership | Owns copied ordinary graph/source/JSON. Layout/projection handles share original accounted Data and may retain selected metadata blocks/account state after native program destruction. |
| failure | Invalid source, conversion/allocation or cleanup-inventory failure propagates; no partially exported plan is returned. |
| cost | Copies full ordinary artifact and allocates wrappers/JSON/inventory. Descriptor conversion is O(1) per handle with no metadata clone; outside native lowering work/byte grants. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/planner/compiled_source.cpp](../../../../../src/planner/compiled_source.cpp), [src/planner/compiled_source.hpp](../../../../../src/planner/compiled_source.hpp), [include/crown/ir/program.hpp](../../../../../include/crown/ir/program.hpp) |

## B0013

[Lines 110–112](../../../../../src/planner/lower.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const PhysicalPlan::Data& PhysicalPlan::data() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the facade still owns a plan and borrow its immutable Data. |
| inputs / outputs | Returns const Data reference or throws invalid_physical_plan for moved-from handle. |
| invariants | All ordinary public getters route through this check; validity is handle lifetime, not rerun structural validation. |
| ownership | Reference is valid while some plan owner retains this Data. |
| failure | Moved-from failure uses allocating public Error; valid access does not allocate. |
| cost | Constant null check/dereference. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0014

[Lines 113–113](../../../../../src/planner/lower.cpp#L113); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalRoute PhysicalPlan::route()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read tree/constant_true/constant_false operator route. |
| inputs / outputs | Scalar route value. |
| invariants | Constant routes describe operators, not a tree certificate for a retained contradictory body. |
| ownership | No borrowed result; scalar copy. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0015

[Lines 114–114](../../../../../src/planner/lower.cpp#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Catalog& PhysicalPlan::catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the core catalog used by numeric physical instructions. |
| inputs / outputs | Core Catalog reference. |
| invariants | Normalized source catalog is available separately; do not interpret core table IDs in the original source catalog. |
| ownership | Plan-owned core catalog borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0016

[Lines 115–115](../../../../../src/planner/lower.cpp#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Catalog& PhysicalPlan::source_catalog()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the original physical source catalog when normalized SQL is retained. |
| inputs / outputs | Normalized binding.catalog, otherwise core catalog. |
| invariants | Physical input/base_routes IDs refer to this catalog; logical table IDs refer to catalog(). |
| ownership | Plan-owned source/core catalog borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0017

[Lines 116–116](../../../../../src/planner/lower.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Query& PhysicalPlan::query()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the compiled numeric core query. |
| inputs / outputs | Core Query reference. |
| invariants | Head order and repeated variables are preserved; normalized SQL output mapping is a separate frontend step. |
| ownership | Plan-owned query borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0018

[Lines 117–117](../../../../../src/planner/lower.cpp#L117); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const FreeConnexTree& PhysicalPlan::tree()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the supplied checked tree or canonical empty constant-operator tree. |
| inputs / outputs | FreeConnexTree reference. |
| invariants | A valid tree is an upper bound; this getter does not establish minimum height. |
| ownership | Plan-owned tree borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0019

[Lines 118–118](../../../../../src/planner/lower.cpp#L118); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::optional<frontend::NormalizedSql>& PhysicalPlan::normalized()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Observe whether the plan retains a replayed normalized SQL program. |
| inputs / outputs | Optional normalized source/adapters reference. |
| invariants | Presence identifies SQL input adapters; direct CQ has no normalized payload. |
| ownership | Plan-owned optional/program borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0020

[Lines 119–119](../../../../../src/planner/lower.cpp#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const planner::ValidationReport& PhysicalPlan::validation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the factory-produced upper/constant-operator report. |
| inputs / outputs | ValidationReport reference. |
| invariants | Editable report copies cannot create plan authority. Contradiction route validity describes its constant operator. |
| ownership | Plan-owned report borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0021

[Lines 120–120](../../../../../src/planner/lower.cpp#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const io::QueryIdentity& PhysicalPlan::identity()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow semantic/output/cost/cache identities and canonical-to-local ID maps. |
| inputs / outputs | QueryIdentity reference including canonical JSON. |
| invariants | Digest matches alone do not authorize importing compiled instructions or bypass replay. |
| ownership | Plan-owned identity graph borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0022

[Lines 121–121](../../../../../src/planner/lower.cpp#L121); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::string& PhysicalPlan::physical_sha256()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the exact physical source/tree/version binding digest. |
| inputs / outputs | 64-character physical SHA-256 string reference. |
| invariants | Physical identity differs from semantic alpha canonicalization and does not include live database contents. |
| ownership | Plan-owned digest text borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0023

[Lines 122–122](../../../../../src/planner/lower.cpp#L122); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::string_view PhysicalPlan::physical_source_sha256()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the prepared physical source digest without reserializing source. |
| inputs / outputs | View of all 64 stored array bytes. |
| invariants | Width is fixed by construction; this accessor neither recomputes nor verifies contents. |
| ownership | View expires with Data; it retains no owner. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0024

[Lines 123–123](../../../../../src/planner/lower.cpp#L123); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const PhysicalOptions& PhysicalPlan::options()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the producer-declared lowering policy/limits/backend options. |
| inputs / outputs | PhysicalOptions reference. |
| invariants | Host ceilings applied during construction do not rewrite producer options; producer limits are not host authorization. |
| ownership | Plan-owned options borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0025

[Lines 124–124](../../../../../src/planner/lower.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const GuaranteeProfile& PhysicalPlan::guarantee()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow explicit backend/stage capability labels. |
| inputs / outputs | GuaranteeProfile reference. |
| invariants | Compile-time lowered_not_started/valid_upper_bound labels do not prove runtime performance or optimum selection. |
| ownership | Plan-owned profile borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0026

[Lines 125–125](../../../../../src/planner/lower.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<storage::TupleLayout>& PhysicalPlan::layouts()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow all immutable plan-local layout tokens. |
| inputs / outputs | Layout handle vector reference. |
| invariants | Ordered field identities and token sharing matter; descriptor equality alone is not token equality. |
| ownership | Vector borrow; copying an individual layout retains its own metadata. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0027

[Lines 126–126](../../../../../src/planner/lower.cpp#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<PhysicalRelation>& PhysicalPlan::relations()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow role-specific relation wiring. |
| inputs / outputs | Relation descriptor vector indexed by RelationId. |
| invariants | Equal layouts do not merge relation state or roles. |
| ownership | Plan-owned vector borrow; descriptors retain layout owners. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0028

[Lines 127–127](../../../../../src/planner/lower.cpp#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<IndexRequirement>& PhysicalPlan::indexes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow numeric index projections and their uses. |
| inputs / outputs | IndexRequirement vector indexed by requirement ID. |
| invariants | Shared requirements keep exact relation, field selection and target token; no live index exists merely from this list. |
| ownership | Plan-owned vector borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0029

[Lines 128–128](../../../../../src/planner/lower.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<PhysicalInput>& PhysicalPlan::inputs()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one input adapter descriptor per native occurrence. |
| inputs / outputs | PhysicalInput vector in occurrence order. |
| invariants | Aliases/self-joins keep separate occurrences even when base tables match. |
| ownership | Plan-owned vector borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0030

[Lines 129–129](../../../../../src/planner/lower.cpp#L129); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<std::vector<OccurrenceId>>& PhysicalPlan::base_routes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow physical-base to occurrence fan-out routes. |
| inputs / outputs | Vector indexed in source_catalog table domain. |
| invariants | A base can feed several independent occurrence adapters; constant routes may have empty entries. |
| ownership | Plan-owned nested vector borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0031

[Lines 130–130](../../../../../src/planner/lower.cpp#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<PhysicalNode>& PhysicalPlan::nodes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow numeric S/P/E node state descriptors. |
| inputs / outputs | PhysicalNode vector in supplied tree node order. |
| invariants | Native/generalized node roles and connex visibility remain distinct; hidden root variables are legal. |
| ownership | Plan-owned vector borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0032

[Lines 131–131](../../../../../src/planner/lower.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const std::vector<PhysicalEdge>& PhysicalPlan::edges()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow ordered parent-child separator wiring. |
| inputs / outputs | PhysicalEdge vector with original child slots. |
| invariants | Endpoint separator target tokens agree; reverse indexes exist only where the parent role requires them. |
| ownership | Plan-owned vector borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0033

[Lines 132–132](../../../../../src/planner/lower.cpp#L132); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const EnumerationProgram& PhysicalPlan::enumeration()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the parent-before-child program over the maximal root-connected connex part. |
| inputs / outputs | Steps, cross-assignment equalities, ordered output slots and depth. |
| invariants | Visible variables outside the connex component do not create enumeration steps. |
| ownership | Plan-owned program borrow. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0034

[Lines 133–133](../../../../../src/planner/lower.cpp#L133); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const storage::TupleLayout& PhysicalPlan::result_layout()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the always-populated core-head tuple layout. |
| inputs / outputs | Reference to result_layout optional payload. |
| invariants | Both tree and constant factories set it before publication; output repetition/order is preserved. SQL constants/EXISTS wrappers are separate. |
| ownership | Plan-owned descriptor borrow; copying the handle retains metadata. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0035

[Lines 134–134](../../../../../src/planner/lower.cpp#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::uint64_t PhysicalPlan::work()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read the completed coarse construction checkpoint count. |
| inputs / outputs | Unsigned work count. |
| invariants | Includes selected preflight/build checkpoints; excludes copies, independent validation, JSON/hash and other physical costs. |
| ownership | Scalar copy; no borrowed result. Borrowed results require Data remain owned. |
| failure | Moved-from handle throws through data(); valid getter does not allocate or rerun work. |
| cost | Constant field access; consumers pay separately for scans, copies or comparisons. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0036

[Lines 135–138](../../../../../src/planner/lower.cpp#L135); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L135-L138:sha256:be152e059f9dd47affa933856f9f74168fd3eeae5f8cc95881c687a3e035a135
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for PhysicalPlan: Run the retained SQL/local CQ adapter for one occurrence. This produces a typed core tuple; it neither maintains joins nor maps SQL result rows. The frontend adapter copies query-wide constant slots before local evaluation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies PhysicalPlan; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for PhysicalPlan come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0037

[Lines 139–154](../../../../../src/planner/lower.cpp#L139); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<storage::Tuple> PhysicalPlan::adapt_input(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one compiled occurrence input adapter and return its numeric core tuple when accepted. |
| inputs / outputs | Occurrence and physical Row pass normalized F04 adaptation or direct physical layout construction, repeated-variable/constant guards, then compiled projection; filtered rows return empty. |
| invariants | Checks occurrence range and typed layout/domain constraints. No join maintenance, source membership or output SQL mapping is performed; numeric positions are already resolved. |
| ownership | Borrows plan/row for call; result owns tuple payload and layout. Native exported descriptors preserve their account-backed factory callbacks rather than becoming detached legacy layouts. |
| failure | Invalid port/shape/type/domain or frontend/storage failure propagates. Filtering is an ordinary empty result; no partial tuple is returned. |
| cost | Normalized frontend::adapt_row copies query-wide constant slots after its initial guards, then pays local expression/guard work. Add row validation/copies, scalar-width equality/constants and projection. May allocate ordinary temporaries and, with native descriptors, funded tuple payloads; outside construction work count. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/frontend/normalize.cpp](../../../../../src/frontend/normalize.cpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp) |

## B0038

[Lines 155–156](../../../../../src/planner/lower.cpp#L155); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L155-L156:sha256:1a63d8dbd04895a73aa29ea0ff87caf6ce83f346ca6684e9e675d3ce0df548bb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for PhysicalPlan: Check compiled tokens and shared-variable equalities. The caller owns membership in the live visible relations; assembly does not verify it. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies PhysicalPlan; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for PhysicalPlan come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0039

[Lines 157–171](../../../../../src/planner/lower.cpp#L157); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::Tuple PhysicalPlan::assemble_result(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble an ordered core-head tuple from one visible assignment per enumeration step. |
| inputs / outputs | Reject constant_false, wrong assignment count/layout tokens or disagreeing compiled shared-variable slots; export selected scalar slots to a Row and construct result tuple. |
| invariants | Checks layouts/equalities only. Caller ensures assignments came from the intended live visible relations; this is not a database membership or join witness verifier. Repeated outputs follow original head order. |
| ownership | Borrows assignments/plan; returns owning tuple. Exported native result descriptor may allocate through its retained account callback. |
| failure | Public Error and storage/scalar/allocation failures propagate with no returned partial result. Internal slot bounds rely on the factory-built immutable program. |
| cost | O(steps + equality slots + output slots), weighted by scalar comparison/export widths and tuple validation/copy costs; may allocate and is not charged to construction work. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp), [include/crown/storage/accounted_row.hpp](../../../../../include/crown/storage/accounted_row.hpp) |

## B0040

[Lines 172–176](../../../../../src/planner/lower.cpp#L172); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Lowering {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a complete public physical artifact privately before immutable publication. |
| inputs / outputs | Copies/moves actual source/query/tree/options, validates them, computes identities, interns layouts and emits numeric relation/input/edge/enumeration descriptors. |
| invariants | Never accepts caller validity flags as authority. P02 supplies upper feasibility; construction is not optimum selection or installation of a maintained runtime. |
| ownership | Builder owns mutable Data and local standard-container caches; only finished const Data escapes. |
| failure | Failures propagate directly. Abandoning the private builder discards partial state instead of per-stage rollback/catch frameworks. |
| cost | Ordinary compiler graph/caches/JSON with variable-width comparisons/allocations; coarse checkpoints are separate from CPU time and memory. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0041

[Lines 177–185](../../../../../src/planner/lower.cpp#L177); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  static PhysicalPlan run(Catalog catalog, Query query, FreeConnexTree tree,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a fallible private builder and publish only after compile finishes. |
| inputs / outputs | Owned catalog/query/tree/optional normalized record plus policy/host ceilings become Data; successful compile returns PhysicalPlan. |
| invariants | By-value parameters isolate caller inputs; immutable publication is the final step. |
| ownership | Moves source objects into builder; no builder/cache reference escapes. |
| failure | Input copying before entry, builder allocation and compilation may throw. No partial plan is returned and caller source is unchanged. |
| cost | Parameter ownership/copies plus entire compile; no asynchronous or hidden background work. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0042

[Lines 186–191](../../../../../src/planner/lower.cpp#L186); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  std::shared_ptr<PhysicalPlan::Data> d_=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep mutable output and construction-only interning maps in one unpublished builder. |
| inputs / outputs | Data owner, effective limits, ordered-variable scope cache, separate physical/logical table caches and relation/field-vector index cache. |
| invariants | Scope keys preserve field order/repetition. Cache IDs refer only to this Data; physical/logical table domains never alias by accidental equal integer IDs. |
| ownership | Local maps own copied key vectors/layout handles; publication retains Data only, not these caches. |
| failure | Map/vector/data allocation can fail; private partial graph is discarded. |
| cost | Extra compiler cache storage and logarithmic variable-width key comparison; no native MemoryAccount claim. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0043

[Lines 192–204](../../../../../src/planner/lower.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  Lowering(const PhysicalOptions& options,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize producer options, effective host ceilings and backend capability labels. |
| inputs / outputs | Copy options/limits; indexed storage changes backend/assumption/operation-mode labels; cap work/identity ceilings by host when present. |
| invariants | Host can tighten but never raise producer ceilings. Stored producer options remain unchanged; no backend/runtime state is installed. |
| ownership | Owns copied option/profile strings in private Data. |
| failure | Copies and initial Data allocation may throw; deeper policy/input checks occur in compile/query_identity. |
| cost | Fixed field operations plus string/vector copies; no source traversal here. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0044

[Lines 205–206](../../../../../src/planner/lower.cpp#L205); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L205-L206:sha256:4485d3b86f230389b6bc73800c19edc8dc63a0d84bc60133b3eb0b7dbe23135a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for charge: Selected construction checkpoints only. Copies, P02, JSON/hash work, container comparisons/capacity and allocator bytes are separate costs. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies charge; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for charge come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0045

[Lines 207–211](../../../../../src/planner/lower.cpp#L207); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void charge() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Consume one selected abstract construction checkpoint without wrap. |
| inputs / outputs | Reject max uint64 or reached finite effective work ceiling; otherwise increment Data work. |
| invariants | Counts selected checkpoints only. Failed construction never publishes a partial plan; this is not a refundable or allocator-byte meter. |
| ownership | Mutates private scalar count only. |
| failure | Throws resource_limit Error, which may allocate, before increment when no room remains. |
| cost | Constant successful arithmetic; excludes body work between charges and all physical-time guarantees. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0046

[Lines 212–212](../../../../../src/planner/lower.cpp#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  const Catalog& source_catalog() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select physical source catalog for compiler base tables. |
| inputs / outputs | Return normalized binding catalog when present, otherwise Data catalog. |
| invariants | Logical core tables remain in Data catalog even for normalized SQL. |
| ownership | Borrows builder-owned source; used only during build. |
| failure | No allocation or independent validation. |
| cost | Constant optional branch. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0047

[Lines 213–213](../../../../../src/planner/lower.cpp#L213); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  storage::LayoutContext context() const {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a plan-bound context for scope layout tokens. |
| inputs / outputs | Return core catalog version and copied physical SHA-256 binding. |
| invariants | Called after the physical digest is computed; scope/projection layouts must share this context. |
| ownership | Owns a small copy of digest text in returned context. |
| failure | String copy allocation may throw. |
| cost | Fixed digest width plus string construction. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0048

[Lines 214–215](../../../../../src/planner/lower.cpp#L214); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L214-L215:sha256:7a016738fb41ea9883eb388161c8f2cd4289586a4effab3585f64bf828e09c8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for scope: Ordered vector identity preserves repeated/output fields. A set key would incorrectly merge distinct result layouts. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies scope; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for scope come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0049

[Lines 216–221](../../../../../src/planner/lower.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  storage::TupleLayout scope(const std::vector<VariableId>& variables) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intern one exact ordered variable-field layout in this plan. |
| inputs / outputs | Charge lookup; return cached handle or charge variables, construct typed scope layout, append to Data and cache key. |
| invariants | Keys are ordered vectors, preserving output repetition/order; equal scopes with different order are distinct layouts. Layout IDs follow successful insertion order. |
| ownership | Returns shared descriptor; cache and output retain owners. Cache copies the vector key. |
| failure | Work, variable/layout validation or allocations propagate. Partial private append/map insertion is discarded with builder on failure. |
| cost | Logarithmic map lookup with variable-width vector comparisons; miss adds field construction/validation and key/vector allocation. Layout constructor may scan/sort variable metadata; checkpoints are coarser. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp) |

## B0050

[Lines 222–223](../../../../../src/planner/lower.cpp#L222); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L222-L223:sha256:347abfffc908f89aa91b91d5bac29e02b33a8fbf7a3befe618d15dbdc809cfcf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for table_layout: Physical and core table IDs use different catalog domains under SQL. On a miss, storage::table_layout revalidates the selected whole catalog. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies table_layout; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for table_layout come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0051

[Lines 224–230](../../../../../src/planner/lower.cpp#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  storage::TupleLayout table_layout(TableId table,bool physical) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intern a physical-source or logical-core table layout in separate caches. |
| inputs / outputs | Charge lookup, select catalog/cache, return hit or create table layout with plan digest, append and cache. |
| invariants | Physical TableId uses source catalog; logical TableId uses core. Equal numeric IDs across catalogs cannot reuse the wrong token. |
| ownership | Returns shared descriptor; builder/Data own handles and construction-only map entries. |
| failure | Work, catalog/table/nullability/domain validation or allocation errors propagate without publication. |
| cost | Logarithmic scalar-key lookup; miss calls storage::table_layout, which revalidates the selected whole catalog and builds table fields. Those validation/allocator costs are not individually charged. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp) |

## B0052

[Lines 231–243](../../../../../src/planner/lower.cpp#L231); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  storage::Projection project(const storage::TupleLayout& source,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile a numeric field selector into the interned ordered target variable layout. |
| inputs / outputs | Build first-position map for source variable fields, resolve requested variable IDs, then construct Projection(source, scope(variables), fields). |
| invariants | Requested variables must exist. Repeated target variables reuse the first source occurrence; target token comes from the same plan-local scope cache. |
| ownership | Local maps/vectors own scratch; returned projection owns source/target descriptor handles. |
| failure | Missing variable is lowering_contract; work and projection/layout/allocation errors propagate. No partial projection returned. |
| cost | O(source width log source width + target width log source width), plus scope cache and projection constructor validation, field copies and allocation. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp) |

## B0053

[Lines 244–246](../../../../../src/planner/lower.cpp#L244); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  RelationId relation(RelationRole role,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate a distinct plan-local relation descriptor for a semantic state role. |
| inputs / outputs | Charge once, assign next vector index as ID, append role/layout/optional node/base and return ID. |
| invariants | Equal layout tokens do not coalesce relation roles or owners; IDs are local numeric vector positions. |
| ownership | Data vector owns descriptor and shared layout handle. |
| failure | Work or vector allocation errors propagate; no relation is externally visible before whole-plan publication. |
| cost | Amortized vector append with possible full-prefix relocation; fixed descriptor/owner operations. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0054

[Lines 247–248](../../../../../src/planner/lower.cpp#L247); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L247-L248:sha256:460dc101b2ccef1b3c2e3656d30aea213cafd1231d4a7f4323f4cf748342af9a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for index: Reuse requires the same relation, ordered fields and target token. Even a cache hit builds/copies a temporary vector of selected fields. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies index; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for index come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0055

[Lines 249–259](../../../../../src/planner/lower.cpp#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  IndexRequirementId index(RelationId relation,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Deduplicate index requirements by exact relation and ordered selected field IDs. |
| inputs / outputs | Charge, allocate key vector and search map; hit verifies same target token and merges a new use once; miss appends requirement and caches ID. |
| invariants | Reuse requires exact relation/field key and target token. Equal descriptor shape without token identity is insufficient. |
| ownership | Local cache owns copied key vectors; Data owns projection/uses and stable numeric IDs. |
| failure | Target mismatch is lowering_contract. Work or any key/map/vector allocation failure aborts private build; no public rollback wrapper needed. |
| cost | Copies fields into a temporary key vector even on hits; nonempty selectors normally allocate. Logarithmic variable-width map comparison and linear use search; miss also copies cache key/uses and may relocate output vector. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0056

[Lines 260–261](../../../../../src/planner/lower.cpp#L260); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L260-L261:sha256:a76d3d71a09eeeb9571072c4e6909484360b71033a46554d6bde1e5234adda39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for preflight: Coarse dimension charges before semantic validation; these loops do not establish topology, bound scalar widths or meter later validation. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies preflight; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for preflight come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0057

[Lines 262–272](../../../../../src/planner/lower.cpp#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void preflight() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge a coarse visit over retained source/query/tree dimensions before semantic compilation. |
| inputs / outputs | Visit source tables/columns, variables, atoms/terms, outputs and tree nodes/scopes/edges, calling charge at selected entries. |
| invariants | Traversal does not validate referenced IDs, topology or SQL semantics; validate/validate_tree and normalization replay are independent later work. |
| ownership | Borrows builder-owned containers; no new scratch beyond loop scalars. |
| failure | Work exhaustion throws and discards builder. Underlying input copies already occurred before these checks. |
| cost | Linear in visited dimensions, not scalar byte lengths; does not bound separate validation/hash/copy/allocator work. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0058

[Lines 273–308](../../../../../src/planner/lower.cpp#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void compile() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate actual source/tree, compute bindings and emit a complete route-specific physical program. |
| inputs / outputs | Preflight/core validation; contradiction requires canonical empty tree; otherwise P02 and empty-body route selection. Compute query identity/source+physical hashes, result layout/base routes, then compile tree wiring. |
| invariants | Contradiction report describes constant operator, not a valid tree for retained body. P02 is upper feasibility only. Physical hash binds exact source/tree/local maps/version, including indexed options only in v2 compatibility envelope. |
| ownership | Private Data owns outputs. Identity graph is frozen before cleanup inventory; local JSON binding/source serializations are temporary ordinary allocations. |
| failure | Validation, policy/identity/resource, serialization/UTF-8/hash, layout or allocation errors propagate. Only completed artifact escapes run(). |
| cost | Selected checkpoint count plus independent P02, canonical identity search and full source/tree JSON/hash costs. No wall-time/allocator-byte bound; constant routes skip node/input/edge/enumeration construction. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/io/identity.cpp](../../../../../src/io/identity.cpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [src/ir/digest.cpp](../../../../../src/ir/digest.cpp) |

## B0059

[Lines 309–310](../../../../../src/planner/lower.cpp#L309); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L309-L310:sha256:0cccb61f8f9f54f574c9144206bcaabff82814fc284db68c746cf6355e5bd1b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for compile_nodes: Scope may contain hidden root variables. Only P02 connex members get visible relations, each using the head intersection of its full scope. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies compile_nodes; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for compile_nodes come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0060

[Lines 311–339](../../../../../src/planner/lower.cpp#L311); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void compile_nodes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Emit base relations and per-tree-node state/visibility descriptors. |
| inputs / outputs | Collect distinct physical bases, compute parents and connex set, derive scope and head intersection, parent separator projection, optional visible projection, and role-specific relation IDs. |
| invariants | Validated tree supplies unique parents/occurrences/separators. Root scope may include hidden variables. Visible projection/relation exists only for maximal root-connected connex members, not every node with an output variable. |
| ownership | Data owns copied children/scopes/layout projections/relations; local sets/parent vector die after construction. |
| failure | Work, layout/projection/relation or allocation errors abort private build. Internal indexing relies on prior P02. |
| cost | Visits atoms/nodes/edges/scopes plus ordered-set/map work, repeated projection construction, descriptor copies and output growth; charges do not count all comparisons/bytes. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md) |

## B0061

[Lines 340–341](../../../../../src/planner/lower.cpp#L340); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L340-L341:sha256:15f4e0cc3d6651d5087f39b4996fe203a746e1b35c97b1cc4d7db88e044468df
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for compile_inputs: Preserve independent native occurrences even when aliases share a base. Resolved numeric fields replace name lookup in the maintained kernel. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies compile_inputs; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for compile_inputs come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0062

[Lines 342–362](../../../../../src/planner/lower.cpp#L342); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void compile_inputs() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile one numeric input adapter and physical-base route per native occurrence. |
| inputs / outputs | Map occurrence to checked native node; select source/logical layouts; record first variable columns, repeated-variable equalities and constants; project node scope and append route. |
| invariants | Each occurrence remains distinct for aliases/self-joins. Native scope variables exist in that atom by P02. Ignored columns add no variable/constant guard; normalized F04 adaptation precedes this logical core projection. |
| ownership | Data owns equality/constant/projection descriptors and occurrence routes; local maps/vectors are construction scratch. |
| failure | Work/layout/projection/allocation errors propagate; missing first.at variable would indicate broken prior validation and abort construction. |
| cost | Occurrence lookup plus term/scope visits with logarithmic variable-map operations, scalar constant copies, layout construction/cache and vector growth. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/frontend/normalize.hpp](../../../../../include/crown/frontend/normalize.hpp), [src/storage/layout.cpp](../../../../../src/storage/layout.cpp) |

## B0063

[Lines 363–364](../../../../../src/planner/lower.cpp#L363); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L363-L364:sha256:d1f4795cda253c27545f99eefd61a5da5a6954b9f68215fc3dfdb421a9275854
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for compile_edges: Both endpoints share an exact separator token. Guard makes a generalized parent use its whole scope rather than a reverse index. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies compile_edges; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for compile_edges come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0064

[Lines 365–377](../../../../../src/planner/lower.cpp#L365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void compile_edges() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile each ordered tree edge into exact separator projection and optional reverse lookup requirement. |
| inputs / outputs | Read child parent-support target fields, project parent layout to those variables, require same target token; native parents obtain reverse support index, generalized parents require whole-scope support identity. |
| invariants | Preserves original child slot/fan-out. P02 Guard makes a generalized parent scope a subset of each child scope, so its edge separator is its whole scope; each endpoint uses the same separator token even when source layouts differ. |
| ownership | Data owns edge projections/index IDs; local separator vectors/projection wrappers are temporary. |
| failure | Token/whole-scope mismatch is lowering_contract; work/projection/index/allocation errors abort build. |
| cost | Edge/separator visits plus parent-width projection compilation, cache-key comparisons and output growth. No fixed per-edge physical cost. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md) |

## B0065

[Lines 378–379](../../../../../src/planner/lower.cpp#L378); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L378-L379:sha256:7f1581e7e2a530e869856bc45751982b02c27a75325092dedeebb8ba903ec07a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for compile_enumeration: P02 supplies root-connected parent-before-child C* order and output coverage. This records traversal/slots; it does not enumerate results. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies compile_enumeration; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for compile_enumeration come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0066

[Lines 380–402](../../../../../src/planner/lower.cpp#L380); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
  void compile_enumeration() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile parent-before-child visible enumeration, cross-assignment equalities and ordered core output reads. |
| inputs / outputs | Walk P02 maximal_connex order, set parent step/depth and separator key/index for nonroots, record first visible variable slot and equalities, then map every original head position. |
| invariants | Prior P02 guarantees root-connected parent-before-child order, visible projections and output coverage. Hidden root fields are excluded from visible tuples; repeated outputs retain repeated slots. |
| ownership | Data owns step/output/equality vectors and projection handles; local position/first maps remain private scratch. |
| failure | Work, token contract, projection/index/map/vector failures abort build. Optional/index accesses rely on validated immutable wiring. |
| cost | Connex/visible/output visits, logarithmic variable-map operations and projection/index construction. Stores program only; does not enumerate or materialize query results. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md) |

## B0067

[Lines 403–404](../../../../../src/planner/lower.cpp#L403); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L403-L404:sha256:cdbb10f75f6890449819c9d57e5ae7b786fb73c5111c5d829c37bc18f3e053e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close the current class or struct and its enclosing lexical scope. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0068

[Lines 405–407](../../../../../src/planner/lower.cpp#L405); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan lower_tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile a supplied actual CQ tree through the independent public lowering factory. |
| inputs / outputs | Const catalog/query/tree plus options and optional host limits are copied into Lowering::run without a normalized program. |
| invariants | No caller validation flag is consumed. Successful tree plan certifies upper feasibility, not original minimum height or cheapest maintenance cost. |
| ownership | Caller inputs are borrowed only during their copies; returned plan owns source/graph and shared descriptor tokens. |
| failure | Copy, validation, work/identity, serialization/layout/allocation failures propagate directly; no partial plan. |
| cost | Whole source/tree copies before private build, plus full lowering/identity/hash costs; no runtime state is installed. |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md) |

## B0069

[Lines 408–409](../../../../../src/planner/lower.cpp#L408); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L408-L409:sha256:3c0364a224c19a1b9bea62ea5bb702e5f08bfc3fd26cf277de1e93b06e5ec6b9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for lower_normalized: Replay the entire artifact and ground v1 before reading its core. Serialization/replay/copies have costs beyond lowering checkpoints. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies lower_normalized; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for lower_normalized come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |

## B0070

[Lines 410–416](../../../../../src/planner/lower.cpp#L410); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PhysicalPlan lower_normalized(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay a complete normalized SQL artifact before compiling its grounded numeric core tree. |
| inputs / outputs | Serialize program, read/replay under program_limits, upgrade legacy v1 to grounded v2, copy grounded core catalog/query, then build with owned normalized source. |
| invariants | Supplied tree must describe the replayed/grounded core, not stale producer data. Constant false requires canonical empty tree. Stored normalized validity flags are not authority. |
| ownership | Owns the replayed normalized record and copied core in result; caller program/tree may expire after return. |
| failure | Serialization, parse/replay/upgrade, copying or lowering errors propagate. No partial plan; program read limits and host physical ceilings are separate. |
| cost | Full JSON serialization/parse/semantic replay and optional grounding, source/core copies, then lowering. These costs are not all bounded by Lowering::work(). |
| Design | [include/crown/planner/lower.hpp](../../../../../include/crown/planner/lower.hpp), [include/crown/ir/physical.hpp](../../../../../include/crown/ir/physical.hpp), [docs/physical_plans.md](../../../../physical_plans.md), [include/crown/io/normalization.hpp](../../../../../include/crown/io/normalization.hpp), [src/io/normalization.cpp](../../../../../src/io/normalization.cpp) |

## B0071

[Lines 417–418](../../../../../src/planner/lower.cpp#L417); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L417-L418:sha256:5cfdcc1902fa2f8f6bf4654a5244fb1f7b50e0c49177a4313d693f54dafeb136
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | close namespace planner and namespace crown in src/planner/lower.cpp. |
| inputs / outputs | This namespace, scope, or declaration boundary has no runtime call inputs or outputs. |
| invariants | It changes compile-time visibility or declaration identity only; attached comments do not enforce or prove the described behavior. |
| ownership | This span creates no runtime owner. Later object definitions and calls determine storage and lifetimes. |
| failure | An invalid declaration or scope boundary fails compilation; no runtime exception or resource stop comes from this span. |
| cost | Compile-time parsing and preprocessor bookkeeping only; no runtime branch, allocation, clock read, counter debit, or engine hook. |
| Design | [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/selection.md](../../../../selection.md) |
