# `src/ir/program_replan.inc` — block usage map

[Source](../../../../../src/ir/program_replan.inc) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rebind and lower checked candidates into native metadata without retaining an ordinary DTO graph.

Snapshot SHA-256: `9e89e685e757d331e6bd1a4d240e9ede3243644ea844096c9e56e20d1fabf840`. 256 lines partitioned into 23 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ir](../../../subsystem_contracts.md#ir). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/physical_runtime.md](../../../../physical_runtime.md), [docs/query_identity.md](../../../../query_identity.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/ir/program_replan.inc#L1) | declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Included after CompiledProgram::Data and its native packer are defined. · [reviewed contract](#b0001) |
| [B0002 · 8–10](../../../../../src/ir/program_replan.inc#L8) | Type/record definition: struct Index |  · [reviewed contract](#b0002) |
| [B0003 · 11–29](../../../../../src/ir/program_replan.inc#L11) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 30–32](../../../../../src/ir/program_replan.inc#L30) | Callable definition: template&lt;class T&gt; resource::MemoryAllocator&lt;T&gt; allocator() const | calls ; returns resource::MemoryAllocator&lt;T&gt;(data_.account,resource::MemoryPurpose::scratch,data_.attribution) · [reviewed contract](#b0004) |
| [B0005 · 33–35](../../../../../src/ir/program_replan.inc#L33) | Callable definition: static std::optional&lt;std::uint64_t&gt; capped(std::optional&lt;std::uint64_t&gt; a,std::optional&lt;std::uint64_t&gt; b) | calls ; returns b && (!a \|\| *b&lt;*a)?b:a · [reviewed contract](#b0005) |
| [B0006 · 36–38](../../../../../src/ir/program_replan.inc#L36) | Callable definition: static void admit(std::uint64_t amount,const std::optional&lt;std::uint64_t&gt;& cap,ReplanFault fault) | calls ReplanFailure · [reviewed contract](#b0006) |
| [B0007 · 39–43](../../../../../src/ir/program_replan.inc#L39) | Callable definition: void charge() | calls ReplanFailure · [reviewed contract](#b0007) |
| [B0008 · 44–44](../../../../../src/ir/program_replan.inc#L44) | Callable definition: const program::Catalog& source_catalog() const | calls ; returns data_.normalized?data_.normalized-&gt;binding.catalog:data_.catalog · [reviewed contract](#b0008) |
| [B0009 · 45–55](../../../../../src/ir/program_replan.inc#L45) | Callable definition: storage::AccountedLayout scope(std::span&lt;const VariableId&gt; variables) | calls charge, key, begin, end; guard charge();require(variable.value&lt;data_.query.variables.size());fields.push_back({data_.query.variabl…; returns found-&gt;second; layout; growth emplace, push_back, reserve; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 56–64](../../../../../src/ir/program_replan.inc#L56) | Callable definition: storage::AccountedLayout table_layout(TableId table,bool physical) | calls charge, find, end, source_catalog; guard const auto& catalog=physical?source_catalog():data_.catalog;require(table.value&lt;catalog.tables.size…; returns found-&gt;second; layout; growth emplace, push_back, reserve; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 65–71](../../../../../src/ir/program_replan.inc#L65) | Callable definition: storage::AccountedProjection project(const storage::AccountedLayout& source,std::span&lt;const VariableId&gt; variables) | calls charge, positions, fields, size; guard for(const auto variable:variables){charge();const auto found=positions.find(variable);require(found…; returns storage::AccountedProjection::freeze(source,scope(variables),fields,data_.attribution); growth emplace, push_back; 2 loop sites · [reviewed contract](#b0011) |
| [B0012 · 72–74](../../../../../src/ir/program_replan.inc#L72) | Callable definition: RelationId relation(RelationRole role,const storage::AccountedLayout& layout,std::optional&lt;NodeId&gt; node={},std::optional&lt;TableId&gt;… | calls charge, size, push_back; returns id; growth push_back · [reviewed contract](#b0012) |
| [B0013 · 75–84](../../../../../src/ir/program_replan.inc#L75) | Callable definition: IndexRequirementId index(RelationId relation,storage::AccountedProjection projection,IndexUse use) | calls charge, std::make_pair, fields, begin; guard auto& value=indexes_\[found-&gt;second.value\];require(value.projection.target().same_token(projection.t…; returns found-&gt;second; id; growth emplace, push_back · [reviewed contract](#b0013) |
| [B0014 · 85–92](../../../../../src/ir/program_replan.inc#L85) | Callable definition: void preflight() | calls charge, source_catalog; 9 loop sites · [reviewed contract](#b0014) |
| [B0015 · 93–115](../../../../../src/ir/program_replan.inc#L93) | Callable definition: void compile_nodes() | calls bases, size, charge, push_back; guard for(std::size_t i=0;i&lt;data_.tree.nodes.size();++i)for(const auto child:data_.tree.nodes\[i\].children…; growth push_back; 8 loop sites · [reviewed contract](#b0015) |
| [B0016 · 116–135](../../../../../src/ir/program_replan.inc#L116) | Callable definition: void compile_inputs() | calls nodes, size, require, charge; guard for(const auto& node:nodes_)if(node.occurrence){require(node.occurrence-&gt;value&lt;nodes.size());nodes\[…; growth emplace, push_back; 4 loop sites · [reviewed contract](#b0016) |
| [B0017 · 136–147](../../../../../src/ir/program_replan.inc#L136) | Callable definition: void compile_edges() | calls size, charge, require, separator; guard charge();const auto child_id=parent.children\[slot\];require(child_id.value&lt;nodes_.size());const auto…; growth push_back; 3 loop sites · [reviewed contract](#b0017) |
| [B0018 · 148–169](../../../../../src/ir/program_replan.inc#L148) | Callable definition: void compile_enumeration() | calls positions, size, first, charge; guard charge();const auto& node=nodes_\[id.value\];require(node.visible_projection.has_value());const auto&…; growth emplace, push_back; 3 loop sites · [reviewed contract](#b0018) |
| [B0019 · 170–186](../../../../../src/ir/program_replan.inc#L170) | Callable definition: void freeze_instructions() | calls freeze, size, bindings, reserve; growth push_back, reserve; 2 loop sites · [reviewed contract](#b0019) |
| [B0020 · 187–195](../../../../../src/ir/program_replan.inc#L187) | Callable definition: NativeLowering(CompiledProgram::Data& data,const planner::MinimumHeightCandidate& candidate,const ReplanLimits& limits) :data_(da… | calls data_, candidate_, limits_, work_ · [reviewed contract](#b0020) |
| [B0021 · 196–237](../../../../../src/ir/program_replan.inc#L196) | Callable definition: void compile() | calls planner::binding_detail::encode, catalog, query, ReplanFailure; guard require(checked.valid && checked.native_height==candidate_.height());; growth emplace_back, push_back; 2 loop sites; source comment (unverified): // The checked candidate binds exact catalog/query structure. Policy labels · [reviewed contract](#b0021) |
| [B0022 · 238–254](../../../../../src/ir/program_replan.inc#L238) | Callable definition: public: static CompiledProgram run(const resource::MemoryAccount& account,const CompiledProgram& basis, const planner::MinimumHei… | calls valid, ReplanFailure, storage::detail::try_new_storage_owner, storage::IndexFailure; returns CompiledProgram(std::move(result)); growth make_accounted_shared · [reviewed contract](#b0022) |
| [B0023 · 255–256](../../../../../src/ir/program_replan.inc#L255) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::program::detail · [reviewed contract](#b0023) |

## B0001

[Lines 1–7](../../../../../src/ir/program_replan.inc#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> using V=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind native lowering sequences and map keys to receiver-funded scratch vectors. |
| inputs / outputs | V&lt;T&gt; uses MemoryAllocator&lt;T&gt;; allocator() supplies account/purpose/attribution. |
| invariants | Zero-size vectors preserve allocator identity; this alias does not turn element or byte traversal into one work unit. |
| ownership | Vectors own capacity and member handles until scratch destruction. |
| failure | Growth/element construction failures propagate to the synchronous caller. |
| cost | Capacity growth/relocation and element teardown costs apply; returned immutable spans are separately arena-admitted. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
template<class K,class T> using M=
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fund ordered native lowering caches without host-default map allocations. |
| inputs / outputs | std::map uses std::less&lt;K&gt; and MemoryAllocator&lt;pair&lt;const K,T&gt;&gt;. |
| invariants | Vector keys compare lexicographically, so logarithmic tree search alone does not bound key comparison width. |
| ownership | Cache owns allocated nodes/keys and shared descriptor handles in receiver scratch attribution. |
| failure | Node/key allocation failure propagates; RAII releases completed cache entries. |
| cost | O(log entries) ordered comparisons per lookup/insertion, each including key-prefix scans; vector key construction and map-node teardown add work. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

```text
@source-span:L1-L7:sha256:347167361788c9b376b1dabb8cb321f28c2bfd88640b65101eaafbeb9a2076a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain the native candidate-lowering compiler boundary and canonical source ownership while actual execution policy is reconstructed separately. |
| inputs / outputs | Private NativeLowering definition and its account-backed vector/map aliases; actual entry is run(account,basis,candidate,limits). |
| invariants | Existing exact candidate/source binding, P02/native-height checks, physical/identity/normalization limits and canonical source flattening stay authoritative. Preparation is a separate local optimization after successful native lowering; no paper theorem, parser/proof replay bypass or source-mode inference is added. |
| ownership | Unpublished Data retains canonical source for every borrowed immutable view; fresh graph/descriptors/scratch and opted-in prepared tables use receiver account/attribution. Actual basis mode is consulted before it can be lost by canonical owner flattening. |
| failure | Existing ReplanFailure/storage/resource exceptions release unpublished graph; preparation denial additionally releases its private tables. Earlier basis is unchanged and used work/peak is not refunded. |
| cost | Existing model encodes, tree freezing, map/vector/digest/descriptor work remain; actual prepared basis adds finite adapter analysis/table writes, reported separately. No base clone occurs in this path. |
| Design | [docs/physical_plans.md](../../../../physical_plans.md), [docs/query_memory.md](../../../../query_memory.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [docs/sql_normalization.md](../../../../sql_normalization.md) |

## B0002

[Lines 8–10](../../../../../src/ir/program_replan.inc#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Index {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one canonical index requirement and deduplicated uses before final arena freeze. |
| inputs / outputs | Dense requirement ID, relation ID, AccountedProjection and funded IndexUse vector. |
| invariants | Index cache key is relation plus ordered selected fields; cache hits also require exact target layout token. |
| ownership | Projection shares existing funded descriptor control; uses own receiver-funded scratch capacity. |
| failure | Use/vector growth or projection-domain faults propagate before publication. |
| cost | Fixed header/handle plus variable use-vector storage and handle-release cost; no mutable runtime index is created. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0003

[Lines 11–29](../../../../../src/ir/program_replan.inc#L11); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
CompiledProgram::Data& data_;
  const planner::MinimumHeightCandidate& candidate_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep in-progress native construction separate from published immutable Data. |
| inputs / outputs | Borrowed Data/candidate, copied caps, compiler work grant, Builder, scope/table/index caches, instruction and assignment vectors, depth. |
| invariants | data_.work counts charge() checkpoints; work_ counts separate metadata dimensions. scopes_ keys preserve ordered variables, including repeated result-head variables. |
| ownership | All scratch allocators derive Data.account; handles/spans copied into graph must retain backing Data arena or canonical basis. |
| failure | No partial caller publication or catch/retry state is stored; failure unwinds entire construction. |
| cost | Scratch peak includes duplicate map keys/arrays and final graph overlap. Map comparison, vector reallocation and descriptor destruction costs remain real beyond charge() counters. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0004

[Lines 30–32](../../../../../src/ir/program_replan.inc#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T> resource::MemoryAllocator<T> allocator() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Propagate receiving program account and attribution into each lowering scratch container. |
| inputs / outputs | Returns MemoryAllocator&lt;T&gt;(data_.account,scratch,data_.attribution). |
| invariants | Never creates a new MemoryAccount or changes its byte cap. |
| ownership | Allocator retains the existing account; allocated storage remains scratch until its own container releases it. |
| failure | Invalid account/allocator preconditions can propagate at construction; allocation denial occurs on use. |
| cost | Allocator/account handle setup; future allocation and element costs are separate. |
| Design | [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0005

[Lines 33–35](../../../../../src/ir/program_replan.inc#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static std::optional<std::uint64_t> capped(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intersect producer and host logical limits while retaining unbounded semantics. |
| inputs / outputs | Returns smaller present cap, or the sole cap, or null when both absent. |
| invariants | A host request cannot enlarge a producer work or identity bound. |
| ownership | Inline optional values only. |
| failure | No checked failure or allocation in the comparison. |
| cost | Fixed optional/uint64 comparisons. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0006

[Lines 36–38](../../../../../src/ir/program_replan.inc#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
static void admit(std::uint64_t amount,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an unchanged producer work credit against an optional host/producer cap. |
| inputs / outputs | amount greater than a present cap throws the specified ReplanFault; equal amount succeeds. |
| invariants | No producer work is executed and no counter is incremented here; source identity/binding/normalization are already admitted immutable artifacts. |
| ownership | Borrows cap and copies scalar fault. |
| failure | ReplanFailure(fault) only when amount exceeds cap. |
| cost | Fixed comparison and optional exception-runtime cost. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0007

[Lines 39–43](../../../../../src/ir/program_replan.inc#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void charge() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit one fresh physical-lowering logical checkpoint before incrementing Data.work. |
| inputs / outputs | Rejects UINT64_MAX counter or a counter already at its present physical cap; otherwise increments once. |
| invariants | Exact cap is allowed after its final admitted increment; a subsequent checkpoint rejects. Does not debit work_ metadata dimensions. |
| ownership | Mutates only private candidate Data work. |
| failure | ReplanFailure(lowering_work) occurs before increment on exhaustion/overflow. |
| cost | Fixed counter admission; variable loop/comparison/byte work between checkpoints is not intrinsically bounded. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0008

[Lines 44–44](../../../../../src/ir/program_replan.inc#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const program::Catalog& source_catalog() const
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose original physical schemas for base tables while preserving core logical schemas separately. |
| inputs / outputs | Returns normalized.binding.catalog when present, otherwise Data.catalog. |
| invariants | compile() must initialize aliased source metadata before this helper is used. |
| ownership | Reference borrows private Data and its retained canonical source. |
| failure | No independent validity check; valid initialized lowering state is required. |
| cost | Fixed optional/member branch. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0009

[Lines 45–55](../../../../../src/ir/program_replan.inc#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedLayout scope(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize ordered variable scopes into receiver-owned layout tokens. |
| inputs / outputs | Copies variables into a funded key, looks up scope cache, or builds fields and a new dense LayoutId bound to physical digest. |
| invariants | Order and repeated variables are preserved, including ordered result heads. Field variables/types come from core query; internal variable-scope decimal domain is unspecified here. |
| ownership | Cache/vector and returned handles share the fresh AccountedLayout control; key/field scratch is receiver funded. |
| failure | Lowering cap, bad variable ID, work/memory/overflow or descriptor-domain failure propagates. |
| cost | Always copies scope key, then ordered-map comparisons scan key prefixes; misses scan fields, create descriptor metadata/binding bytes and insert funded cache/vector entries. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0010

[Lines 56–64](../../../../../src/ir/program_replan.inc#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedLayout table_layout(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build separate cached physical-source and logical-core table layouts. |
| inputs / outputs | TableId and physical flag select catalog/cache; miss copies all nonnullable column kinds/decimal domains with source origin. |
| invariants | Physical/logical caches are distinct even when IDs coincide; every constructed primary layout gets next dense ID and current physical digest context. |
| ownership | Descriptor control and field scratch use receiver account; cache/layout vector share its handle. |
| failure | Bad table ID, nullable column, cap/work/memory or descriptor faults propagate; no new layout is published outside the private build. |
| cost | Scalar-key map lookup plus complete column scan/descriptor construction on miss; field scan is not one charge() per column here, though preflight and metadata counters cover separate dimensions. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0011

[Lines 65–71](../../../../../src/ir/program_replan.inc#L65); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
storage::AccountedProjection project(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct an exact ordered projection from source variables into a canonical target scope. |
| inputs / outputs | Builds variable-to-first-field positions, resolves requested variables and freezes AccountedProjection(source,scope(variables),fields). |
| invariants | Every requested variable must exist; repeated source variable occurrences use the first mapped position, preserving canonical target token sharing through scope cache. |
| ownership | Position map/field vector are receiver scratch; result descriptor owns funded metadata and shares source/target controls. |
| failure | Missing variable, cap/work/memory or projection-domain failure aborts build. |
| cost | Scans source fields and selected variables with ordered-map operations, copies selected fields and performs target-scope and projection descriptor validation. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0012

[Lines 72–74](../../../../../src/ir/program_replan.inc#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
RelationId relation(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one immutable relation role with dense numeric identity. |
| inputs / outputs | Role/layout plus optional node/base; returns RelationId equal to previous relations_.size(). |
| invariants | This helper appends metadata only; final binding checks role/layout compatibility before publication. |
| ownership | Scratch relation owns shared layout handle; mutable table instances are created later by make_storage(). |
| failure | charge() or vector allocation/size/member construction faults propagate. |
| cost | One checkpoint and amortized vector append, with relocation/handle work on growth. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0013

[Lines 75–84](../../../../../src/ir/program_replan.inc#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexRequirementId index(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse an index requirement only for identical relation and ordered selected-field key. |
| inputs / outputs | Copies projection fields into a funded map key; hit verifies target token and adds a new use once; miss appends dense requirement and cache entry. |
| invariants | Field/relation equality is necessary but target-token identity is also required; requirements are still immutable plans rather than live runtime indexes. |
| ownership | Key/use vectors, map nodes and index array use receiver scratch; projection control is shared and retained. |
| failure | Cap, target-token mismatch or allocation failure aborts the private build; a partial cache update is discarded with the builder. |
| cost | Even hits copy the ordered field vector; ordered-map key-prefix comparisons, use scan and possible vector/node allocations add actual work. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0014

[Lines 85–92](../../../../../src/ir/program_replan.inc#L85); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void preflight() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Debit coarse native dimensions before constructing physical instructions. |
| inputs / outputs | Visits physical tables/columns, retained core variables/atoms/terms/head and Data.tree nodes/scopes/children; nonempty contradiction has an empty selected operator tree. |
| invariants | Listed checkpoints do not validate original topology or meter string byte scans, later map comparisons or complete binding/digest work. Retained contradiction-marked body dimensions are still charged even though operator nodes are empty. |
| ownership | Read-only views are backed by private arena or retained basis; only Data.work changes. |
| failure | Lowering cap or work counter overflow yields ReplanFailure before the next checkpoint. |
| cost | Linear in listed metadata counts; scalar width and later lowering/descriptor work are separate. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0015

[Lines 93–115](../../../../../src/ir/program_replan.inc#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compile_nodes() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Derive base relations and per-node record/survivor/support/visible instructions from checked candidate topology. |
| inputs / outputs | Deduplicates physical base tables, builds parent/connex/head flags, full and visible scopes/projections and dense physical nodes. |
| invariants | Called by compile() only for the tree route; constant routes skip this helper. Relies on typed candidate’s complete checked report for topology, separator indexing and root-first maximal connex. Preserves ordered child spans and native occurrence coordinates; this function does not independently revalidate the tree. |
| ownership | Temporary bases/flags/parents/visible fields are receiver funded; copied node child/scope spans borrow new Data.tree and visible scopes are arena copied. |
| failure | Lowering cap, bad referenced IDs/token contracts or memory/descriptor failures abort the whole build. |
| cost | Atom collection and sort/unique, node-child/head/connex/scope scans, scope-map/project calls and relation append costs; sort comparisons and variable-width map work are not each charged by charge(). |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0016

[Lines 116–135](../../../../../src/ir/program_replan.inc#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compile_inputs() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile physical occurrences into guarded logical projections and base-event fanout routes. |
| inputs / outputs | Maps each checked native occurrence to node, builds physical/logical layouts, repeated-variable equalities, constants and selected-field projection. |
| invariants | Called by compile() only for the tree route; constant routes skip this helper. Uses normalized adapters to select physical base and logical table; typed checked tree ensures every occurrence is present exactly once. Constants preserve exact scalar representation and source views. |
| ownership | Scratch maps/vectors and projection descriptors use receiver account; guard arrays are arena copied and borrowed string constants are retained through canonical basis. |
| failure | Bad occurrence/base/variable membership, lowering cap, memory or descriptor fault aborts private build. |
| cost | Node/atom/term/scope scans with ordered first-variable maps, table-layout cache lookups, guard array copies, projection validation and route-vector growth. |
| Design | [docs/physical_plans.md §Compiled input adapters](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0017

[Lines 136–147](../../../../../src/ir/program_replan.inc#L136); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compile_edges() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create child-slot support edges and native reverse-index requirements for arbitrary fanout. |
| inputs / outputs | For each ordered child builds parent separator projection, checks shared target token, and creates/reuses native reverse index when required. |
| invariants | Called by compile() only for the tree route; constant routes skip this helper. Generalized parent must already have its parent-key target equal to full layout; child slot remains the actual ordered slot, not a binary-tree encoding. |
| ownership | Separator scratch and edges/index metadata are receiver funded; projections retain canonical controls. |
| failure | Invalid child/field variable, mismatched token, lowering cap or allocation/descriptor failure aborts graph. |
| cost | One visit per edge plus child separator width, source projection-map scans and index field-key comparisons/copies. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0018

[Lines 148–169](../../../../../src/ir/program_replan.inc#L148); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compile_enumeration() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile checked maximal-connex order into visible assignment steps and repeated-head equalities. |
| inputs / outputs | Builds step parent/depth/key/bucket requirements, first variable slots, equality checks, ordered output slots and maximum step depth. |
| invariants | Called by compile() only for the tree route; constant routes skip this helper. Consumes checked parent-before-child maximal_connex; every head variable needs a visible assignment. Repeated head positions are preserved and repeated visible variable assignments generate equality tests. |
| ownership | All construction maps/arrays are receiver scratch; final arena freeze owns output instructions and shared projection controls. |
| failure | Missing parent position/visible projection/head variable, token/cap/work/memory/descriptor failure propagates; no cursor is started. |
| cost | Connex node/visible field/head scans with ordered maps, projection and shared-index key construction. Stored enumeration depth does not imply recursive native construction stack depth. |
| Design | [docs/physical_plans.md §Enumeration and result assembly](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0019

[Lines 170–186](../../../../../src/ir/program_replan.inc#L170); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void freeze_instructions() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Move native instruction ownership from funded scratch into the private immutable arena and binding. |
| inputs / outputs | Freezes layouts/relations/inputs/routes/nodes/edges/enumeration, constructs index records/use spans, then native binding and auxiliary source/result descriptors. |
| invariants | Arena-only instruction overloads share already owned nested spans/descriptor controls. freeze_native_binding checks dense layout identities, account/context, relation roles and projection source/target tokens in compiler metadata mode. |
| ownership | Final arrays and binding control are receiver funded; scratch vectors remain alive during overlap and release after success. Binding shares funded descriptor controls rather than cloning them again. |
| failure | Work/memory/overflow, binding/token or auxiliary descriptor faults unwind Data; no partially frozen program is externally visible. |
| cost | Copies all instruction arrays/use spans and numeric bindings, visits layouts/relations/indexes, validates contexts/tokens and performs auxiliary table-by-relation searches and descriptor construction. |
| Design | [docs/physical_plans.md §Node state and relation layouts](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md) |

## B0020

[Lines 187–195](../../../../../src/ir/program_replan.inc#L187); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
NativeLowering(CompiledProgram::Data& data,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize receiver-funded native lowering scratch and a separate compiler metadata allowance. |
| inputs / outputs | Borrows Data/candidate, copies ReplanLimits, gives work_ fixed diagnostics with UINT64_MAX in all five dimensions, initializes empty caches/vectors and arena-only Builder. |
| invariants | Logical physical/identity/binding/normalization caps remain distinct from work_ metadata counters and are enforced in compile()/charge()/admit(). |
| ownership | Every scratch allocator uses Data.account/attribution; source/candidate lifetime is borrowed for this blocking construction. |
| failure | Account/allocator/member construction failures propagate before compile(); no traversal or caller publication yet. |
| cost | Fixed set of allocator/map/vector headers and handles; container implementation may initialize sentinel/header state, while payload growth comes later. |
| Design | [docs/memory_accounts.md §Native ranking results and physical selection](../../../../memory_accounts.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0021

[Lines 196–237](../../../../../src/ir/program_replan.inc#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void compile() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the typed candidate to canonical source and build its complete native graph in order. |
| inputs / outputs | Encodes candidate then canonical basis Catalog/Query and compares exact bytes; checks candidate valid/native height; aliases admitted source metadata, intersects physical/identity caps and admits inherited identity/SQL credits; selects and freezes operator tree/report; preflights, computes digest, result layout, routes, instructions, binding and auxiliary descriptors. |
| invariants | For admitted query.contradiction && !query.atoms.empty(), freezes default public FreeConnexTree and a fresh valid report with native_height=0, edge_depth=0 and empty arrays. Otherwise freezes candidate tree/report unchanged, preserving ordinary and empty-body claims. Original candidate/proof is untouched. Route comes from canonical basis; constant routes skip nodes/inputs/edges/enumeration and set constant_result. No source producer or proof replay is rerun. |
| ownership | Both exact binding buffers stay receiver-funded scratch until return. Data.basis retains aliased source fields. Selected operator tree/report, digest, descriptors/instruction arrays and all scratch are receiver-funded; freeze completes before temporary empty tree/local report dies. |
| failure | Exact binding mismatch precedes candidate report consistency and source-credit checks. Existing identity/binding/normalization credit checks precede either tree/report branch; physical charge() checks begin in preflight. Later work/memory/overflow/domain/digest faults discard private Data without changing basis, candidate or proof. |
| cost | Two full model encodes and byte comparison precede credited source reuse. Selected tree/report copy, retained-body preflight scans, exact native digest spelling/hash, ordered-key/container work and descriptor/arena construction are fresh costs. Nonempty contradiction avoids structural node/report payload admission but still scans original binding/body and creates funded result/source metadata. Data.work counts only explicit physical checkpoints, not all byte, allocator or metadata work. |
| Design | [docs/physical_plans.md §Admission and routes](../../../../physical_plans.md), [docs/query_memory.md §Boundaries](../../../../query_memory.md), [docs/selection_accounting.md §Delegated budget equation](../../../../selection_accounting.md) |

## B0022

[Lines 238–254](../../../../../src/ir/program_replan.inc#L238); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L238-L254:sha256:91716e42c3781df849bd5859a7530e917002c1c382f8308afb409df068fa2fa6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild prepared input tables from the actual replan basis after native candidate lowering. |
| inputs / outputs | Receiving account, actual CompiledProgram basis, typed minimum-height candidate and existing replan limits; new owning graph/program. |
| invariants | Existing exact source/candidate proof binding remains authoritative. Canonical source flattening does not erase actual basis execution mode. Prepared limits are inherited from actual basis, and new views refer to completed result normalized metadata. No base-freeze copy occurs here, so its usage field is zero. |
| ownership | Receiver owns new graph, scratch and tables; retained canonical source keeps aliased normalized payload alive. No growing chain of candidate graph owners is added. |
| failure | Invalid basis/candidate, replan limits, logical preparation, account, allocation and overflow faults release unpublished result. Prior basis remains unchanged. |
| cost | Existing native lowering plus finite analysis/table-write work when basis is prepared; separate preparation usage is not a new P02/height or CPU theorem. |
| Design | [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_support.md](../../../../sql_support.md), [docs/scalars.md](../../../../scalars.md), [src/frontend/sql_scalar.hpp](../../../../../src/frontend/sql_scalar.hpp), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp) |

## B0023

[Lines 255–256](../../../../../src/ir/program_replan.inc#L255); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L255-L256:sha256:e7f4f1f15e960a2383278e42e629469b1d1a20922dc01932c82c6459ed1a6566
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Ends the private NativeLowering builder and program::detail namespace. This include fragment is compiled inside program.cpp and has no independent translation-unit link boundary. |
| inputs / outputs | No external runtime input/output is performed by the declaration itself; callable signatures in the block describe future use. |
| invariants | The declaration fixes the source-local names and member/type shape; runtime validation and authority remain with the actual implementations. |
| ownership | No owner is added merely by a declaration. Typed fields keep the ownership behavior of their C++ types and any explicit account allocator. |
| failure | No runtime catch or translation is added here; constructor/member failures remain in their implementation. |
| cost | Declaration-only compile/link work, except that constructing a declared type later may initialize or allocate its members. |
| Design | [src/ir/program_replan.inc](../../../../../src/ir/program_replan.inc), [docs/code_specs/files/src/ir/program_replan.inc.md](program_replan.inc.md), [docs/semantics.md](../../../../semantics.md), [docs/physical_plans.md](../../../../physical_plans.md) |
